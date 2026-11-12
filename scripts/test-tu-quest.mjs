import './pure-js-probes/deny-wasm.mjs';
import { Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('quest', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/quest-reference.mjs';
import createGeneratedProbe from './pure-js-fixtures/runtime.mjs';
const hybridFactory=options=>createGeneratedProbe('quest',options);
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
import {C,R,T} from '../js/c-runtime/context.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),layout=layouts.quest;
const modules=[await referenceFactory(),await hybridFactory({nethackPorted:createPortedRuntime(layouts)})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function bytes(m,p,n){p=Number(p);if(n===undefined){let e=p;while(m.HEAPU8[e])e++;n=e-p;}return Buffer.from(m.HEAPU8.slice(p,p+n));}
function snapshot(m){return {raw:[0,1].map(n=>bytes(m,m._probe_state_pointer(n),Number(m._probe_state_size(n)))),quest:Array.from({length:14},(_,n)=>m._probe_qget(n)),scalars:Array.from({length:7},(_,n)=>m._probe_scalar(n)),strategy:BigInt.asUintN(64,m._probe_strategy()),traps:Array.from({length:5},(_,n)=>m._probe_trap_chain(n)),items:Array.from({length:5},(_,n)=>[0,1,2].map(k=>m._probe_item_bit(n,k))),rng:m._probe_rng_count(),random:m._probe_rng_state()>>>0,trace:bytes(m,m._probe_trace()).toString('hex')};}
function state(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m, stacks[i]));comparisons++;}
function call(name,...args){const result=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(result[1],result[0],`${name}(${args})`);state();comparisons++;return result[0];}
function reset(seed=1){call('reset',seed);}
function rng(values){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});state();}
function trace(){return bytes(modules[0],modules[0]._probe_trace()).toString();}
function action(n,arg=0){call('action',n,arg);}
function victim(sound=layout.MS_NEMESIS,prisoner=0,peace=1,sleep=0,move=1,strategy=0xfedcba9876543210n){call('victim',sound,prisoner,peace,sleep,move,strategy);}
reset();for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const key=bytes(m,m._probe_layout_name(i)).toString();assert.equal(Number(m._probe_layout_value(i)),layout[key],key);}
for(const key of ['MS_LEADER','MS_NEMESIS','MS_GUARDIAN','MS_DJINNI','MAGIC_PORTAL','STRAT_WAITMASK'])assert.ok(Number.isSafeInteger(layout[key]),key);
// Arrival messages, completed/same-level guards and all special-level dispatch.
for(const ready of [0,1,2,3,7,8,15])for(const first of [0,1])for(const [d,l,od,ol] of [[2,1,1,8],[2,1,2,0],[2,1,2,2],[2,1,2,1]]){reset();call('qset',0,first);call('qset',1,ready);call('levels',d,l,od,ol);action(0);}
for(const killed of [0,1])for(const first of [0,1])for(const previous of [2,3,4]){reset();call('qset',2,killed);call('qset',3,first);call('levels',2,3,2,previous);action(1);}
for(const killed of [0,1])for(const goal of [0,1,2,6,7,8,15])for(const artifact of [0,1]){reset();call('qset',2,killed);call('qset',4,goal);call('option',1,artifact);action(2);action(2);assert.ok(call('qget',4)<=7);}
for(const completed of [0,1])for(const special of [0,1])for(const level of [1,3,5,6])for(const previous of [0,level]){reset();call('hset',0,completed);call('option',0,special);call('levels',2,level,2,previous);action(3);}
reset();action(4);action(4);assert.equal(call('qget',2),1);assert.equal((trace().match(/qt:killed_nemesis;/g)||[]).length,1);action(5);action(5);assert.equal(call('qget',5),1);action(6,0);action(6,0);assert.equal(call('qget',6),1);assert.equal(call('item_bit',0,0),1);
// Purity includes original/current alignment, integer boundaries and wizard
// prompts whose answer can mutate the alignment before purity is computed.
for(const level of [-2147483648,0,13,14,15,2147483647]){reset();call('alignment',1,1,1,20,level);call('check',1,0);}
for(const type of [-1,0,1,127,128])for(const current of [-1,0,1])for(const record of [-2147483648,19,20,21,2147483647])for(const talk of [0,1,256]){reset();call('alignment',type,current,1,record,14);call('check',2,talk);}
for(const type of [-1,1])for(const current of [-1,1])for(const record of [0,20])for(const reply of [121,110,89,27]){reset();call('hset',5,1);call('option',2,reply);call('alignment',type,current,1,record,14);call('check',2,1);}
reset();call('hset',5,1);call('option',2,121);call('alignment',1,1,1,0,14);assert.equal(call('check',2,1),1);assert.equal(call('scalar',5),20);assert.ok(trace().includes('yn:adjust?:<null>:121:1;'));
for(const got of [0,1])for(const thanks of [0,1])for(const killed of [0,1])for(const current of [-1,1]){reset();call('qset',7,got);call('qset',8,thanks);call('qset',5,killed);call('alignment',1,current,1,20,14);call('check',0,0);}
// Opposite branch ends, current-side first portal selection, expulsion flags,
// stale already-expelled states and post-schedule callback mutation.
for(const seal of [0,1,2,256])for(const expelled of [0,1])for(const reverse of [0,1])for(const portal of [0,1]){reset();call('hset',1,expelled);call('branch',reverse?2:1,reverse?1:8,reverse?1:2,reverse?8:1);call('traps',1,portal?layout.MAGIC_PORTAL:1,layout.MAGIC_PORTAL,-1);action(7,seal);}
reset();call('traps',1,layout.MAGIC_PORTAL,layout.MAGIC_PORTAL,1);action(7,1);assert.equal(call('scalar',3),1);assert.deepEqual([0,1,2].map(n=>call('trap_chain',n)),[0,2,3]);action(7,1);assert.equal(call('scalar',3),2);action(7,1);
for(const already of [0,1])for(const callback of [0,1]){reset();call('hset',1,already);call('option',4,callback);call('traps',1,1,-1,-1);action(7,1);}
// Optional item dialogue skips deaf heroes, while quest completion does not.
for(const item of [-1,0,1,2,3,4])for(const amulet of [0,1])for(const thanks of [0,1])for(const inventory of [0,2,4,6]){reset();call('hset',2,amulet);call('qset',8,thanks);call('inventory',inventory);action(8,item);}
for(const deaf of [0,1,2,3])for(const item of [0,1,3,4]){reset();call('deaf',deaf&1?1n:0n,deaf&2?1n:0n);action(8,item);}
for(const item of [0,1,3,4]){reset();call('hset',4,1);action(8,item);}
reset();call('inventory',5);action(8,0);assert.equal(call('scalar',0),1);assert.equal(call('qget',8),1);assert.equal(call('item_bit',0,2),1);
// Leader rule precedence: previous thanks/artifact/quest outrank eligibility.
for(const peace of [0,1])for(const pissed of [0,1])for(const thanks of [0,1])for(const artifact of [0,1])for(const amulet of [0,1])for(const got of [0,1]){reset();victim(layout.MS_LEADER,0,peace);call('qset',9,pissed);call('qset',8,thanks);call('qset',7,got);call('hset',3,artifact);call('hset',2,amulet);call('inventory',7);action(9);}
for(const level of [13,14])for(const type of [-1,1])for(const current of [-1,1])for(const record of [19,20])for(const met of [0,1])for(const home of [0,1]){reset();call('alignment',type,current,1,record,level);call('qset',12,met);call('qset',1,7);if(!home)call('levels',1,8,2,1);action(9);}
reset();action(9);assert.equal(call('qget',7),1);assert.ok(trace().includes('qt:assignquest;'));assert.ok(trace().includes('has granted access'));
for(const home of [0,1])for(const pissed of [0,1])for(const peace of [0,1])for(const strategy of [0n,BigInt(layout.STRAT_WAITMASK),0xffffffffffffffffn,0x20000000000001n]){reset();victim(layout.MS_LEADER,0,peace,0,1,strategy);call('qset',9,pissed);if(!home)call('levels',1,8,2,1);action(10);}
// Nemesis 3-bit counters, duplicate encounters and both precise RNG sites.
for(const battle of [0,1])for(const goal of [0,1,2,3,4,6,7,8,15])for(const met of [0,1])for(const artifact of [0,1])for(const roll of [0,1]){reset();call('qset',13,battle);call('qset',4,goal);call('qset',10,met);call('hset',3,artifact);rng([roll,roll]);action(12);action(12);}
reset();action(11);action(11);assert.equal(call('qget',10),1);
for(const moving of [0,1,2,127,128,255,256,-1])for(const nested of [0,1]){reset();call('hset',6,moving);const before=call('scalar',2);call('option',3,nested);action(13,-32768);assert.equal(call('scalar',2),before);}
for(const artifact of [0,1])for(const killed of [0,1]){reset();call('hset',3,artifact);call('qset',2,killed);action(14);}
for(const prisoner of [0,1,2])for(const sight of [0,1])for(const strategy of [0n,BigInt(layout.STRAT_WAITMASK),0xffffffffffffffffn]){reset();victim(layout.MS_DJINNI,prisoner,0,0,1,strategy);call('option',5,sight);action(15);action(15);}
reset();victim(layout.MS_DJINNI,1,0,0,1,BigInt(layout.STRAT_WAITMASK));action(15);assert.equal(call('scalar',4),1);assert.equal(call('scalar',5),23);assert.equal(BigInt.asUintN(64,call('strategy'))&BigInt(layout.STRAT_WAITMASK),0n);
// Unsigned ID equality takes priority over sound dispatch, including zero IDs.
for(const leader of [0,17,0x80000000,0xffffffff])for(const id of [0,17,0x80000000,0xffffffff])for(const sound of [layout.MS_NEMESIS,layout.MS_GUARDIAN,layout.MS_DJINNI,0]){reset();call('ids',leader,id);victim(sound);action(16);action(17);}
for(const stale of [0,1]){reset();call('qset',9,stale);if(!stale)call('alignment',1,-1,1,20,14);action(16);assert.equal(call('scalar',4),0);assert.ok(trace().includes('angry:17:0;'));}
for(const sound of [layout.MS_NEMESIS,layout.MS_GUARDIAN])for(const sleep of [0,1])for(const move of [0,1])for(const near of [0,1,2,-1])for(const frozen of [0,7]){reset();victim(sound,0,1,sleep,move);call('hset',7,frozen);call('option',6,near);call('qset',13,1);action(18);}
reset();call('option',3,1);action(0);assert.equal(call('qget',2),1);
reset();call('option',7,0);call('qset',4,7);call('qset',10,1);rng([0]);action(12);
reset();const saved=snapshot(modules[0]);modules[1]._probe_qset(1,7);assert.deepEqual(snapshot(modules[0]),saved);reset();
const sizes=modules.map(m=>allocationMetric(m)),pointers=modules.map(m=>m._malloc(40n*1024n*1024n));assert.ok(pointers.every(Boolean));modules.forEach((m,i)=>assert.ok(allocationMetric(m)>sizes[i]));action(9);victim(layout.MS_NEMESIS);action(17);call('inventory',7);action(8,0);modules.forEach((m,i)=>m._free(pointers[i]));state();
console.log(`QUEST: ${comparisons} ${referenceLabel}/pure-JS quest-state, dispatch, dialogue, expulsion, monster and RNG-site comparisons checked.`);
