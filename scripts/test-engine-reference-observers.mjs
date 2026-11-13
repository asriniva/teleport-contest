import assert from 'node:assert/strict';
import {createCollector} from './branch-coverage/collector.mjs';
const runtime=createCollector(),file='synthetic.js';runtime.register(file,['site:0:1'],'hash');
const marker=new Error('observer');
assert.throws(()=>runtime.reference(()=>{runtime.hit(file,0,0);runtime.complete(file,[0]);runtime.reference(()=>runtime.hit(file,0,1));throw marker;}),error=>error===marker);
assert.deepEqual(runtime.files.get(file).counts,[]);assert.equal(runtime.files.get(file).completions,undefined);
assert.equal(runtime.reference(()=>7),7);runtime.hit(file,0,0);assert.equal(runtime.files.get(file).counts[0][0],1);
if(process.env.NETHACK_BRANCH_REFERENCE_OBSERVERS==='1'){
 const observer=await import('../js/wasm-replay-support.js');
 observer.encodeRecorderScreen('observer     text\n');
 const global=globalThis.__nethackBranchCoverage,row=global.files.get('js/wasm-replay-support.js');
 assert.ok(row);assert.ok(!row.counts.some(arms=>arms?.some(Boolean)),'reference codec cannot add implementation hits');
 // Explicit original-module import controls the production path without a
 // test-script observer wrapper. Production imports under js/ use this path.
 const actual=await import('../js/wasm-replay-support.js?implementation-control');
 assert.equal(actual.encodeRecorderScreen('x     y'),'x\u001b[5Cy');
 assert.ok(row.counts.some(arms=>arms?.some(Boolean)),'implementation codec contributes hits');
}
console.log('PASS: nested reference observations preserve results/exceptions and cannot add hits or default completions; counter scope restores.');
