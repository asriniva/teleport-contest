// Bounded source/literal/attribution guard, not a general C or JS parser.
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import {brief_feeling} from '../js/ported/mhitm.js';
const read=path=>readFileSync(new URL('../'+path,import.meta.url),'utf8');
const source=read('nethack-c/upstream/src/mhitm.c'),js=read('js/ported/mhitm.js');
const strip=text=>text.replace(/\/\*[\s\S]*?\*\//g,'').replace(/\/\/[^\n]*/g,'');
const counts=text=>{const result=new Map();for(const token of strip(text).match(/"(?:\\.|[^"\\])*"/g)??[])result.set(token,(result.get(token)??0)+1);return result;};
const original=counts(source),translated=counts(js);original.delete('"hack.h"');original.delete('"artifact.h"');
for(const[token,n]of original)assert.ok((translated.get(token)??0)>=n,'Missing original literal '+token);
assert.equal(brief_feeling,'have a %s feeling for a moment, then it passes.');
const mask=text=>text.replace(/\/\*[\s\S]*?\*\/|\/\/[^\n]*|"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'/g,match=>match.replace(/[^\n]/g,' '));
function closing(text,index){const clean=mask(text);let depth=1;for(let p=index+1;p<clean.length;p++){if(clean[p]==='(')depth++;if(clean[p]===')'&&!--depth)return p;}throw Error('Unclosed invocation');}
const clean=mask(source),functions=[...clean.matchAll(/^(\w+)\(/gm)].map(m=>({name:m[1],index:m.index}));
const calls=[...clean.matchAll(/\b(rn2|rnd|d)\(/g)];
for(const m of calls){const end=closing(source,source.indexOf('(',m.index)),line=source.slice(0,end).split('\n').length,fn=functions.findLast(f=>f.index<m.index).name;assert.match(js,new RegExp('C\\.'+m[1]+'\\([^;]*?, '+line+", '"+fn+"'\\)"),'Missing source RNG '+fn+':'+line);}
assert.equal([...mask(js).matchAll(/\bC\.(rn2|rnd|d)\(/g)].length,calls.length);
const snprintf=[...clean.matchAll(/\bSnprintf\(/g)].map(m=>source.slice(0,closing(source,source.indexOf('(',m.index))).split('\n').length);
assert.deepEqual(snprintf,[669,676,679,682,685,689,693,700]);
assert.equal([...mask(js).matchAll(/\bC\.Snprintf\(/g)].length,snprintf.length);
console.log(`MHITM: original message literals, two constant strings, ${calls.length} RNG annotations and ${snprintf.length} format sites preserved.`);
