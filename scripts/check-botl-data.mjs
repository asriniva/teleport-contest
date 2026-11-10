// Read-only source boundary and initializer projection. No status algorithms.
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import * as data from '../js/ported/botl-data.js';
const read=p=>readFileSync(new URL('../'+p,import.meta.url),'utf8');
const source=read('nethack-c/upstream/src/botl.c'),js=read('js/ported/botl.js');
// Strings must be lexed before comments: the original strength string "18/**"
// contains a comment opener which is not a C comment.
const lex=/"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'|\/\*[\s\S]*?\*\/|\/\/[^\n]*/g;
const comments=s=>[...s.matchAll(lex)].filter(m=>m[0].startsWith('/*')).map(m=>m[0]).sort();
const clean=s=>s.replace(lex,m=>m.startsWith('/*')||m.startsWith('//')?' '.repeat(m.length):m);
assert.deepEqual(comments(js),comments(source),'all original block comments and multiplicities');
const c=[...clean(source).matchAll(/^(?:staticfn\s+)?(?:enum statusfields|unsigned long|const char\s*\*|char\s*\*|struct hilite_s\s*\*|void|boolean|int)\s*(?:QSORTCALLBACK\s+)?\n?(\w+)\(([^{};]*?)\)\s*\{/gm)].map(m=>({name:m[1],params:m[2].split(',').map(s=>s.trim()).filter(s=>s&&s!=='void').map(s=>s.match(/\b(\w+)\s*(?:\)\[QBUFSZ\])?$/)?.[1])}));
const j=[...clean(js).matchAll(/^export function (\w+)\(([^)]*)\)/gm)].map(m=>({name:m[1],params:m[2].split(',').map(s=>s.trim()).filter(Boolean)}));
assert.equal(c.length,76);assert.deepEqual(j,c,'all configured original boundaries, order and formal names');
const original=clean(source),header=clean(read('nethack-c/upstream/include/botl.h'));
const values={FALSE:0,TRUE:1,NULL:0,c_Wall:'Wall'};
for(const m of header.matchAll(/^#define\s+(BL_MASK_\w+|MAXVALWIDTH)\s+(0x[\da-fA-F]+|\d+)[LU]*\b/gm))values[m[1]]=Number(m[2]);
function initializer(name){const m=new RegExp('\\b'+name+'\\s*\\[[^\\]]*\\]\\s*=\\s*\\{').exec(original);assert.ok(m,name+' original initializer');let pos=m.index+m[0].length,depth=1,start=pos;for(;depth;pos++){if(original[pos]==='"'){pos++;while(original[pos]!=='"'){if(original[pos]==='\\')pos++;pos++;}}else if(original[pos]==='{')depth++;else if(original[pos]==='}')depth--;}return original.slice(start,pos-1);}
const scalar=s=>{s=s.trim();if(s.startsWith('"'))return JSON.parse(s);if(s in values)return values[s];if(/^-?\d+[LU]*$|^0x[\da-fA-F]+[LU]*$/.test(s))return Number(s.replace(/[LU]+$/,''));return {constant:s};};
const normalized=v=>v?.operator==='-'?-normalized(v.value):v?.operator==='|'?Number(BigInt(normalized(v.left))|BigInt(normalized(v.right))):v?.constant?(v.constant in values?values[v.constant]:v):Array.isArray(v)?v.map(normalized):v&&typeof v==='object'?Object.fromEntries(Object.entries(v).map(([k,v])=>[k,normalized(v)])):v;
function parse(text){const tokens=text.match(/"(?:\\.|[^"\\])*"|0x[\da-fA-F]+[LU]*|-?\d+[LU]*|[A-Za-z_]\w*|[{},|]/g)||[];let at=0;function val(){let result;if(tokens[at]==='{'){at++;result=[];while(tokens[at]!=='}'){result.push(expr());if(tokens[at]===',')at++;else assert.equal(tokens[at],'}');}at++;}else result=scalar(tokens[at++]);return result;}function expr(){let v=val();while(tokens[at]==='|'){at++;v=Number(BigInt(v)|BigInt(val()));}return v;}const out=[];while(at<tokens.length){out.push(expr());if(tokens[at]===',')at++;}return out;}
for(const name of ['enc_stat','terrain_descr','cond_idx']){let expected=parse(initializer(name));if(name==='cond_idx')expected=Array(30).fill(0);assert.deepEqual(normalized(data[name+'_initial']),expected,name+' complete original order');}
for(const[name,fields]of [['conditions',['ranking','mask','c','text']],['condtests',['c','useroption','opt','enabled','choice','test']],['condition_aliases',['id','bitmask']],['fieldids_alias',['fieldname','fldid']]]){
 const expected=parse(initializer(name)).map(row=>Object.fromEntries(fields.map((f,i)=>[f,row[i]])));
 assert.deepEqual(normalized(data[name+'_initial']),expected,name+' every original initializer field');
}
const rows=[...initializer('initblstats').matchAll(/INIT_BLSTAT(P?)\(((?:"(?:\\.|[^"\\])*"|[^)])*)\)/g)].map(m=>{const args=m[2].match(/"(?:\\.|[^"\\])*"|[^,]+/g).map(scalar);assert.equal(args.length,m[1]?6:5);return {fldname:args[0],fldfmt:args[1],time:0,chg:0,percent_matters:m[1]?1:0,percent_value:0,anytype:args[2],a:{a_void:0},rawval:{a_void:0},val:0,valwidth:args[3],idxmax:m[1]?args[4]:-1,fld:args[m[1]?5:4],hilite_rule:0,thresholds:0};});
assert.equal(rows.length,27);assert.deepEqual(normalized(data.initblstats_initial),rows,'all 27 complete native status initializers');
for(const n of ['c_Wall','threshold_value','is_out_of_range']){const m=new RegExp('\\b'+n+'\\[\\]\\s*=\\s*("(?:\\\\.|[^"\\\\])*")').exec(source);assert.ok(m,n);assert.equal(data[n+'_initial'],JSON.parse(m[1]));}
for(const n of ['menutitle','aligntxt','hutxt']){const pattern=new RegExp('\\b'+n+'\\[[^\\]]*\\]\\s*=\\s*\\{([\\s\\S]*?)\\};'),a=pattern.exec(source);assert.ok(a,n);const strings=a[1].match(/"(?:\\.|[^"\\])*"/g);assert.ok(strings.length);for(const value of strings)assert.ok(js.includes(value),n+' original scoped text '+value);}
assert.doesNotMatch(clean(js),/\bgoto\s/);
console.log('BOTL 76 original functions/formals/order, all 361 true block comments, all 11 initializer datasets and three local text tables match.');
