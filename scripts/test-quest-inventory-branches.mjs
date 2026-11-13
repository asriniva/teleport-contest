import './pure-js-probes/deny-wasm.mjs';
import assert from 'node:assert/strict';
import {createProbe,createReference} from './pure-js-fixtures/load.mjs';
import {C,R,T} from '../js/c-runtime/context.js';
const modules=[await createReference('quest'),await createProbe('quest')];
const bytes=(m,p,n)=>{p=Number(p);if(n===undefined){let end=p;while(m.HEAPU8[end])end++;n=end-p;}return Buffer.from(m.HEAPU8.slice(p,p+n));};
function snapshot(m){return{raw:[0,1].map(n=>bytes(m,m._probe_state_pointer(n),Number(m._probe_state_size(n)))),quest:Array.from({length:14},(_,n)=>m._probe_qget(n)),scalars:Array.from({length:7},(_,n)=>m._probe_scalar(n)),strategy:BigInt.asUintN(64,m._probe_strategy()),traps:Array.from({length:5},(_,n)=>m._probe_trap_chain(n)),items:Array.from({length:5},(_,n)=>[0,1,2].map(k=>m._probe_item_bit(n,k))),rng:m._probe_rng_count(),random:m._probe_rng_state()>>>0,trace:bytes(m,m._probe_trace()).toString()};}
let comparisons=0;
for(const metNemesis of [0,1])for(let mask=0;mask<32;mask++){
 for(const m of modules){m._probe_reset(1);m._probe_hset(3,1);m._probe_qset(10,metNemesis);m._probe_inventory(mask);}
 const stacks=modules.map(m=>m._probe_stack()),results=modules.map(m=>m._probe_action(9,0)),states=modules.map(snapshot);
 assert.deepEqual(results[1],results[0]);assert.deepEqual(states[1],states[0]);
 assert.equal(states[0].quest[11],1-metNemesis,'cheater flag follows claimed artifact and actual nemesis visit');
 assert.equal(states[0].quest[8],1,'leader thanks even when claimed artifact is missing');
 assert.equal(states[0].scalars[0],mask&1?1:0,'completion requires an actual quest artifact');
 assert.deepEqual(modules.map(m=>m._probe_stack()),stacks);assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);comparisons++;
}
assert.equal(comparisons,64);console.log('PASS:64 original-C/pure-JS leader inventory cases, including absent artifact, trailing non-artifacts, empty inventory and independent nemesis/cheater state; complete declared snapshots/trace and restored stacks.');
