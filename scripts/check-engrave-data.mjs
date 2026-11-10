// Bounded original table/literal/context/attribution guard, not a general parser.
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import * as data from '../js/ported/engrave.js';
const read=p=>readFileSync(new URL('../'+p,import.meta.url),'utf8');
const source=read('nethack-c/upstream/src/engrave.c'),js=read('js/ported/engrave.js');
const clean=source.replace(/\/\*[\s\S]*?\*\//g,'');
const rub=clean.slice(clean.indexOf('rubouts[]'),clean.indexOf('/* degrade')<0?clean.indexOf('void\nwipeout_text'):clean.indexOf('/* degrade'));
const rows=[...rub.matchAll(/\{\s*('(?:\\.|[^'\\])*')\s*,\s*("(?:\\.|[^"\\])*")\s*\}/g)].map(m=>({wipefrom:JSON.parse('"'+m[1].slice(1,-1).replace(/\\'/g,"'").replace(/"/g,'\\"')+'"').charCodeAt(0),wipeto:JSON.parse(m[2])}));
assert.deepEqual(data.rubouts,rows);assert.equal(rows.length,48);
const blind=clean.slice(clean.indexOf('blind_writing[][21]'),clean.indexOf('staticfn const char *',clean.indexOf('blind_writing[][21]')));
const encoded=[...blind.matchAll(/\{\s*((?:0x[0-9a-fA-F]+\s*,?\s*)+)\}/g)].map(m=>m[1].match(/0x[0-9a-fA-F]+/g).map(Number));
assert.deepEqual(data.blind_writing,encoded);assert.equal(encoded.length,9);for(const row of encoded)assert.equal(row.length,21);
const ctx=source.slice(source.indexOf('struct _doengrave_ctx {'),source.indexOf('\n};',source.indexOf('struct _doengrave_ctx {'))+3).replace('_doengrave_ctx','teleport_engrave_context');
assert.ok(read('nethack-c/wasm/tu-engrave-support.h').includes(ctx),'Exact original context layout/comment mirror');
const strip=text=>text.replace(/\/\*[\s\S]*?\*\//g,'').replace(/\/\/[^\n]*/g,'');
const counts=text=>{const result=new Map();for(const token of strip(text).match(/"(?:\\.|[^"\\])*"/g)??[])result.set(token,(result.get(token)??0)+1);return result;};
const original=counts(source),translated=counts(js);original.delete('"hack.h"');
// The sizeof literal is now a compiler-generated metadata constant.
original.set('"You feel the words: \\"\\"."',Math.max(0,(original.get('"You feel the words: \\"\\"."')??0)-1));
for(const[token,n]of original)assert.ok((translated.get(token)??0)>=n,'Original literal '+token);
const mask=text=>text.replace(/\/\*[\s\S]*?\*\/|\/\/[^\n]*|"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'/g,m=>m.replace(/[^\n]/g,' '));
const code=mask(source),functions=[...code.matchAll(/^(\w+)\(/gm)].map(m=>({name:m[1],index:m.index}));
let direct=0;
for(const m of code.matchAll(/\b(rn2|rnd|rn1)\(/g)){const line=source.slice(0,m.index).split('\n').length,fn=functions.findLast(f=>f.index<m.index).name;assert.match(js,new RegExp('C\\.'+m[1]+'\\([^;]*?, '+line+", '"+fn+"'\\)"),fn+':'+line);direct++;}
assert.match(js,/C\.rn2\(C\.blind_writing\.length, 1767, 'blengr'\)/);
assert.equal([...mask(js).matchAll(/\bC\.(rn2|rnd|rn1)\(/g)].length,direct+1);
assert.deepEqual([...code.matchAll(/\bStrlen\(/g)].map(m=>source.slice(0,m.index).split('\n').length),[417,421,1163]);
for(const call of ['C.Strlen(s, 0)','C.Strlen(pristine_s, 1)','C.Strlen(de.oep.engr_txt[C.actual_text], 2)'])assert.ok(js.includes(call),call);
console.log(`ENGRAVE:48 rubouts,9 encoded rows, exact context/comments/messages and ${direct+1} source RNG annotations preserved.`);
