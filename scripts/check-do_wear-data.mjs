// Read-only original-boundary and static-data guard; no equipment policy.
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
const read=p=>readFileSync(new URL('../'+p,import.meta.url),'utf8');
const original=read('nethack-c/upstream/src/do_wear.c'),js=read('js/ported/do_wear.js'),runtime=read('js/nethack/bindings/do_wear.js');
const comments=text=>{const out=new Map();for(const c of text.match(/\/\*[\s\S]*?\*\//g)||[])out.set(c,(out.get(c)||0)+1);return [...out].sort(([a],[b])=>a.localeCompare(b));};
assert.deepEqual(comments(js),comments(original),'all original block comments and multiplicities');
const clean=s=>s.replace(/\/\*[\s\S]*?\*\//g,'');
const c=[...clean(original).matchAll(/^(?:staticfn\s+)?(?:const char\s*\*|struct\s+\w+\s*\*|void|int|boolean)\s*\n?(\w+)\(([^{};]*?)\)\s*\{/gm)].map(m=>({name:m[1],params:m[2].split(',').map(x=>x.replace(/\bUNUSED\b/g,'').trim()).filter(x=>x&&x!=='void').map(x=>x.match(/\w+$/)?.[0])}));
const j=[...clean(js).matchAll(/^export function (\w+)\(([^)]*)\)/gm)].map(m=>({name:m[1],params:m[2].split(',').map(x=>x.trim()).filter(Boolean)}));
assert.equal(c.length,79);assert.deepEqual(j,c,'original function order/boundaries/parameter names');
const a=original.match(/static NEARDATA const long takeoff_order\[\] = \{([\s\S]*?)\};/),b=js.match(/export const takeoff_order = \[([\s\S]*?)\];/);assert.ok(a);assert.ok(b);
const expected=a[1].split(',').map(x=>x.trim()).filter(Boolean).map(x=>x==='0L'?0:x),actual=JSON.parse('['+b[1]+']');assert.equal(expected.length,15);assert.deepEqual(actual,expected,'original immutable takeoff ordering');
for(const name of ['see_yourself','unknown_type','c_armor','c_suit','c_shirt','c_cloak','c_gloves','c_boots','c_helmet','c_shield','c_weapon','c_sword','c_axe','c_that_','need_to_take_off_outer_armor']){
 const pattern=new RegExp('\\b'+name+'(?:\\[\\])?\\s*=\\s*("(?:\\\\.|[^"\\\\])*")');const x=original.match(pattern),y=js.match(pattern);assert.ok(x,name+' C string');assert.ok(y,name+' JS string');assert.equal(y[1],x[1],name+' original bytes');
}
assert.match(js,/const offdelaybuf = C\.staticBuffer\(60\)/,'persistent delayed-message storage');
assert.match(runtime,/env\.Narmorpieces=0;env\.Naccessories=0/,'per-Module original private counters');
assert.doesNotMatch(clean(js),/\bgoto\s/);
console.log('DO_WEAR all79 original boundaries/order/parameters and all351 block comments; 15-row takeoff table/static strings/native delayed buffer match.');
