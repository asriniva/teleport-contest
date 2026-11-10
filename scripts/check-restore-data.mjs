// Read-only source/ABI fidelity guard. No restoration policy or save data.
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
const read=p=>readFileSync(new URL('../'+p,import.meta.url),'utf8');
const source=read('nethack-c/upstream/src/restore.c'),js=read('js/ported/restore.js');
const comments=text=>{const out=new Map();for(const c of text.match(/\/\*[\s\S]*?\*\//g)||[])out.set(c,(out.get(c)||0)+1);return [...out].sort(([a],[b])=>a.localeCompare(b));};
assert.deepEqual(comments(js),comments(source),'all original block comments and multiplicities');
const clean=text=>text.replace(/\/\*[\s\S]*?\*\//g,'');
const original=[...clean(source).matchAll(/^(?:staticfn\s+)?(?:struct\s+\w+\s*\*|void|int|boolean)\s*\n?(\w+)\(([^{};]*?)\)\s*\{/gm)].map(m=>({name:m[1],params:m[2].split(',').map(s=>s.trim()).filter(s=>s&&s!=='void').map(s=>s.match(/\w+$/)?.[0])}));
const translated=[...clean(js).matchAll(/^export function (\w+)\(([^)]*)\)/gm)].map(m=>({name:m[1],params:m[2].split(',').map(s=>s.trim()).filter(Boolean)}));
assert.equal(original.length,32,'configured original source inventory');assert.deepEqual(translated,original,'original function order, boundaries and parameter names');
const bucket=source.match(/^#define N_PER_BUCKET (\d+)$/m);assert.ok(bucket,'original private bucket constant');assert.equal(Number(bucket[1]),64);
const native=read('nethack-c/wasm/tu-restore-types.h');assert.match(native,/unsigned gid; unsigned nid;/);assert.match(native,/map\[64\]/);
assert.match(js,/counter = C\.int\(dmgcount\)/,'original explicit unsigned-to-int conversion');
assert.match(js,/C\.localStruct\("stairway", true\)/,'original UNDEFINED_VALUES zero initialization');
assert.match(js,/C\.assign_level\(ltmp, C\.addressOf\(br, "end2"\)\)/,'branch-local d_level pointer retains native struct storage');
console.log('RESTORE all32 function boundaries/order/parameters and original comments, private bucket layout, narrowing and zero initialization match.');
