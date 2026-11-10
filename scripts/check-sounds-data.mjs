// Independent development-only projection of original active text/data and ABI context.
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import {pathToFileURL,fileURLToPath} from 'node:url';
import {resolve} from 'node:path';
const root=fileURLToPath(new URL('../',import.meta.url));
const {parse}=await import(pathToFileURL(resolve(process.env.EMSDK??root+'/.cache/emsdk','upstream/emscripten/node_modules/acorn/dist/acorn.mjs')));
const c=readFileSync(new URL('../.cache/wasm64-build/tree/src/sounds.c',import.meta.url),'utf8'),js=readFileSync(new URL('../js/ported/sounds.js',import.meta.url),'utf8');
const support=readFileSync(new URL('../nethack-c/wasm/tu-sounds-support.inc',import.meta.url),'utf8'),header=readFileSync(new URL('../scripts/tu-sounds-layout.h',import.meta.url),'utf8');
const cleanC=c.replace(/\/\*[\s\S]*?\*\/|\/\/[^\n]*/g,m=>' '.repeat(m.length));
function declarations(source){const result=new Map();function walk(n){if(!n||typeof n!=='object')return;if(n.type==='VariableDeclarator'&&n.id.type==='Identifier')result.set(n.id.name,n.init);for(const v of Object.values(n))if(Array.isArray(v))v.forEach(walk);else if(v&&typeof v==='object')walk(v);}walk(parse(source,{ecmaVersion:'latest',sourceType:'module'}));return result;}
function sourceArray(name){const body=cleanC.match(new RegExp('\\b'+name+'\\s*\\[[^\\]]*\\]\\s*=\\s*\\{([^}]+)\\}'))?.[1];assert.ok(body,name);const result=[];let current='';for(const m of body.matchAll(/"(?:\\.|[^"\\])*"|,/g)){if(m[0]===','){result.push(current);current='';}else current+=JSON.parse(m[0]);}if(current)result.push(current);return result;}
function check(source){const declarations_=declarations(source);let count=0;for(const[name,node]of declarations_)if(node?.type==='ArrayExpression'&&name!=='soundlib_choices'){const values=node.elements.map(n=>{assert.equal(n.type,'Literal',name);assert.equal(typeof n.value,'string',name);return n.value;});assert.deepEqual(values,sourceArray(name),name);count++;}
    const suffix=declarations_.get('suffix').value,original=cleanC.match(/static const char suffix\[\]\s*=\s*("[^"]+")/)[1];assert.equal(suffix,JSON.parse(original));assert.ok(header.includes('sizeof '+original));
    const data=declarations_.get('nosound_procs');assert.equal(data.type,'ObjectExpression');const rows=data.properties.map(p=>[p.key.name,p.value.value]);assert.deepEqual(rows,[['soundname','nosound'],['soundlib_id','soundlib_nosound'],['sound_triggers',0n],['sound_init_nhsound',0],['sound_exit_nhsound',0],['sound_achievement',0],['sound_soundeffect',0],['sound_hero_playnotes',0],['sound_play_usersound',0],['sound_ambience',0],['sound_verbal',0]]);
    const originalProc=cleanC.match(/static struct sound_procs nosound_procs\s*=\s*\{([\s\S]*?)\};/)[1];assert.match(originalProc,/SOUNDID\(nosound\)/);assert.equal((originalProc.match(/\)\s*0\s*,/g)??[]).length,8);assert.match(originalProc,/SOUNDID\(nosound\),\s*0L,/);
    const choices=declarations_.get('soundlib_choices');assert.equal(choices.elements.length,1);assert.equal(choices.elements[0].properties[0].key.name,'sndprocs');assert.equal(choices.elements[0].properties[0].value.name,'nosound_procs');return count;
}
const count=check(js);assert.throws(()=>check(js.replace('"beep",   "boing"','"boing",   "beep"')));assert.throws(()=>check(js.replace('soundname:"nosound"','soundname:"changed"')));assert.throws(()=>check(js.replace('const suffix = ".wav"','const suffix = ".ogg"')));
const definitions=Array.from(cleanC.matchAll(/^([A-Za-z_]\w*)\(/gm));
const rng=Array.from(cleanC.matchAll(/\b(rn1|rn2|ROLL_FROM)\(/g),m=>[m[1]==='ROLL_FROM'?'rn2':m[1],c.slice(0,m.index).split('\n').length,definitions.filter(d=>d.index<m.index).at(-1)[1]]);
const actual=Array.from(js.replace(/\/\*[\s\S]*?\*\//g,'').matchAll(/\bC\.(rn1|rn2)\([^;]+?, (\d+), '(\w+)'\)/g),m=>[m[1],Number(m[2]),m[3]]);assert.deepEqual(actual,rng);
const start=cleanC.indexOf('base_soundname_to_filename('),snprintf=Array.from(cleanC.slice(start).matchAll(/\bSnprintf\([^;]+?\);/gs),m=>c.slice(0,start+m.index+m[0].length).split('\n').length);assert.deepEqual(snprintf,[2144,2146]);assert.ok(support.includes(`site?${snprintf[1]}:${snprintf[0]}`));
console.log('SOUNDS '+count+' original text arrays, sound tables/suffix, '+rng.length+' RNG sites and Snprintf context passed (three rejected data mutations).');
