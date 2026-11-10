// Read-only function/comment/data guard; no visibility policy or oracle dump.
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import * as core from '../js/ported/vision.js';
const read=p=>readFileSync(new URL('../'+p,import.meta.url),'utf8');
const src=read('nethack-c/upstream/src/vision.c'),js=read('js/ported/vision.js');
const comments=s=>{const a=new Map();for(const c of s.match(/\/\*[\s\S]*?\*\//g)||[])a.set(c,(a.get(c)||0)+1);return [...a].sort(([a],[b])=>a.localeCompare(b));};
assert.deepEqual(comments(js),comments(src),'all original block comments and multiplicities');
const strip=s=>s.replace(/\/\*[\s\S]*?\*\//g,'');
const off=new Set(['new_angle','_q1_path','_q2_path','_q3_path','_q4_path']);
const orig=[...strip(src).matchAll(/^(?:staticfn\s+)?(?:void|boolean|int|unsigned)\s*\n?(\w+)\(([^{};]*?)\)\s*\{/gm)].filter(m=>!off.has(m[1])).map(m=>({name:m[1],params:m[2].replace(/void\s*\(\*(\w+)\)\([^)]*\)/g,'$1').split(',').map(p=>p.trim()).filter(p=>p&&p!=='void').map(p=>p.match(/\w+$/)?.[0])}));
const translated=[...strip(js).matchAll(/^export function (\w+)\(([^)]*)\)/gm)].map(m=>({name:m[1],params:m[2].split(',').map(x=>x.trim()).filter(Boolean)}));
assert.equal(orig.length,19);assert.deepEqual(translated,orig,'original configured function boundaries/order/parameters');
for(const[name,count]of [['circle_data',137],['circle_start',16]]){const match=src.match(new RegExp('const coordxy '+name+'\\[\\]\\s*=\\s*\\{([\\s\\S]*?)\\};'));assert.ok(match,'original '+name+' initializer');const values=strip(match[1]).split(',').map(x=>x.trim()).filter(Boolean).map(Number);assert.equal(values.length,count);assert.deepEqual(core[name],values,'complete '+name+' numeric order');}
const display=read('.cache/wasm64-build/tree/src/display.c'),fixture=read('scripts/tu-vision-probe.c');const pattern=/const seenV seenv_matrix\[3\]\[3\]\s*=\s*\{[\s\S]*?\};/;assert.ok(display.match(pattern));assert.ok(fixture.match(pattern));assert.equal(fixture.match(pattern)[0],display.match(pattern)[0],'actual external DISPLAY initializer dependency');
assert.match(js,/C\.boolean\(C\.canseemon\(mon\)\)/,'original signed boolean narrowing');assert.match(js,/return C\.boolean\(result\)/,'original boolean return conversion');
assert.equal([...js.matchAll(/^export function _q/gm)].length,0,'configured macros do not add functions');assert.doesNotMatch(strip(js),/\bgoto\s/);
const storage=read('nethack-c/wasm/tu-vision-storage.c');assert.match(storage,/const coordxy circle_data\[137\];/);assert.match(storage,/const coordxy circle_start\[16\];/);assert.doesNotMatch(storage,/circle_(?:data|start)[^;]*=/,'separate storage contains no initializer mirror');assert.doesNotMatch(read('nethack-c/wasm/tu-vision-support.inc'),/const coordxy circle_(?:data|start)\[[^;]*=/,'no same-reader constant definition');
console.log('VISION: all19 function boundaries/order/parameters, original comments, two authoritative tables, external matrix and separate native storage match.');
