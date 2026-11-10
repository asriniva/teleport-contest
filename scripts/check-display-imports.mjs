import {readFileSync} from 'node:fs';
import assert from 'node:assert/strict';
const functions=JSON.parse(readFileSync(new URL('../nethack-c/wasm/tu-fragments/display-source-metadata.json',import.meta.url))).functions,expected=functions.map(f=>f.linkage==='static'?'teleport_display_'+f.name:f.name);
const load=async mode=>WebAssembly.Module.imports(await WebAssembly.compile(readFileSync(new URL('../.cache/display-first-pass/display-'+mode+'.wasm',import.meta.url))));
const hybrid=await load('hybrid'),reference=await load('reference');
for(const name of expected){assert.equal(hybrid.filter(x=>x.kind==='function'&&x.name===name).length,1,name+' actual hybrid import');assert.ok(!reference.some(x=>x.name===name),name+' original C stays compiled in reference');}
assert.equal(expected.length,71);
console.log('PASS: all 71 configured DISPLAY functions are actual hybrid Wasm imports; original C reference uses compiled original bodies.');
