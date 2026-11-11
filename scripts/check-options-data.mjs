// Read-only provenance, original boundary/comment, and data representation guard.
// Values are independently checked against the original native tables by the unit.
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import {createHash} from 'node:crypto';
import {optionsStaticInitializers} from '../js/ported/options-data.js';
const read=p=>readFileSync(new URL('../'+p,import.meta.url),'utf8');
const pins={"nethack-c/upstream/src/options.c": "494772974500aa9b42df179b4e090def15fd0bc8148f09a9c392bbadd05dd940", "nethack-c/upstream/include/optlist.h": "23dafb109132dd63bbfe704b39fac8cccaaeee31a0dbd895c7ba928bd92af9b8"};
for(const[p,h]of Object.entries(pins))assert.equal(createHash('sha256').update(read(p)).digest('hex'),h,'review original source changes '+p);
const source=read('nethack-c/upstream/src/options.c'),js=read('js/ported/options.js'),schema=JSON.parse(read('nethack-c/wasm/tu-fragments/options-schema.json'));
const lex=/"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'|\/\*[\s\S]*?\*\/|\/\/[^\n]*/g;
const comments=s=>[...s.matchAll(lex)].filter(m=>m[0].startsWith('/*')&&!/^\/\* source goto \w+ \*\/$/.test(m[0])).map(m=>m[0]).sort();
const clean=s=>s.replace(lex,m=>m.startsWith('/*')||m.startsWith('//')?' '.repeat(m.length):m);
assert.equal(comments(source).length,693);assert.deepEqual(comments(js),comments(source),'all original block comments including inactive branches');
const j=[...clean(js).matchAll(/^export function (\w+)\(([^)]*)\)/gm)].map(m=>({name:m[1],params:m[2].split(',').map(x=>x.trim()).filter(Boolean)}));
const c=[...clean(source).matchAll(/^(\w+)\(([^{}]*?)\)\s*\{/gm)].filter(m=>schema.names.includes(m[1])).map(m=>({name:m[1],params:m[2].split(',').map(x=>x.replace(/\bUNUSED\b/g,'').trim()).filter(x=>x&&x!=='void').map(x=>x.match(/\b(\w+)\s*(?:\[[^\]]*\])?$/)?.[1])}));
assert.equal(c.length,224);assert.deepEqual(j,c,'all configured original functions, order and formal names');
assert.doesNotMatch(clean(js),/\bgoto\s/);
assert.equal((js.match(/\/\* source goto /g)||[]).length,12,'every original forward/retry edge retained');
assert.deepEqual(schema.statics.map(x=>x.name).filter(x=>!x.includes('.')).length,36);
// Evaluate representation metadata with inert tokens, not a second initializer.
const constants=new Map();let next=1024;
const C=new Proxy({sizes:new Proxy({},{get:()=>32}),literal:s=>s,functionAddress:s=>({function:s}),field:()=>({address:64})},{get(t,k){if(k in t)return t[k];if(/^[iu](8|16|32|64)$/.test(k))return v=>k.endsWith('64')?BigInt(v):Number(v);if(!constants.has(k))constants.set(k,next++);return constants.get(k);}});
const rows=optionsStaticInitializers(C);assert.equal(rows.length,66);assert.deepEqual(rows.map(x=>[x.name,x.type]),schema.statics.map(x=>[x.name,x.type]));
assert.equal(rows[0].values.length,218);assert.equal(rows[1].values,null);
const handlers=new Set(rows[0].values.map(r=>r[14]?.function).filter(Boolean));assert.equal(handlers.size,105);
assert.ok(handlers.has('optfn_boolean'));assert.equal(rows[0].values.at(-1)[0],0);assert.equal(rows[0].values.at(-1)[14],0);
assert.doesNotMatch(read('nethack-c/wasm/tu-fragments/options-support.c'),/\bteleport_options_test_\w+\s*\(/,'production callbacks have distinct names from fixture entry aliases');
console.log('OPTIONS 224 original functions/formals/order, 693 comments, 12 goto edges, 66 initializer representations and 105 real callback identities guarded.');
