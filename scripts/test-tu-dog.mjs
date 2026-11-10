import {Int32Array,referenceBackend,referenceLabel,assertStackRestored,assertMemoryGrowth} from './native-test-backend.mjs';
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {callDog} from '../js/ported/dog-runtime.js';
import {C,R,T} from '../js/ported/c-runtime.js';
const author=process.env.TELEPORT_DOG_PROBES,dir=author?pathToFileURL(resolve(author)+'/'):new URL('../.cache/tu-probes/',import.meta.url);
const referenceFactory=(await import(new URL('dog-reference.mjs',dir))).default,hybridFactory=(await import(new URL('dog-hybrid.mjs',dir))).default;
const ref=await referenceBackend('dog',referenceFactory)();
function text(m,p){let e=Number(p);while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(Number(p),e)).toString();}
const L={size:Number(ref._probe_context_size())};for(let i=0;i<ref._probe_layout_count();i++){const k=text(ref,ref._probe_layout_name(i)),v=ref._probe_layout_value(i);L[k]=['NON_PM'].includes(k)?Number(BigInt.asIntN(64,v)):/^(M1_|M2_|MON_|STRAT_|MIGR_LEFTOVERS$)/.test(k)?BigInt.asUintN(64,v).toString():Number(v);}
if(!author)assert.deepEqual(L,JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))).dog);
for(const k of ['edogSize','monSize','objSize','NUMMONS','NUM_OBJECTS','PM_DOG','CORPSE','TRIPE_RATION','MIGR_EXACT_XY','MIGR_RANDOM'])assert.ok(Number.isSafeInteger(L[k]),k);
const modules=[ref,await hybridFactory({nethackPorted:{dog:(s,n,...args)=>callDog(s,L,n,...args)}})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function bytes(m,p,n){return Buffer.from(m.HEAPU8.slice(Number(p),Number(p)+n));}
function snapshot(m){const count=m._probe_count(0),indices=[0,1,2,3,...Array.from({length:count},(_,i)=>32+i)];return {objects:Array.from({length:4},(_,i)=>Array.from({length:16},(_,k)=>m._probe_obj_value(i,k))),mon:indices.map(i=>Array.from({length:41},(_,k)=>m._probe_mon_value(i,k))),edog:indices.map(i=>{const p=m._probe_pointer(2,i);return p?bytes(m,p,L.edogSize):null;}),counts:Array.from({length:8},(_,k)=>m._probe_count(k)),hero:Array.from({length:5},(_,k)=>m._probe_hero_value(k)),trace:text(m,m._probe_trace()),rng:[m._probe_rng_count(),m._probe_rng_state()>>>0]};}
function state(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m,stacks[i]));comparisons++;}
function call(n,...args){const results=modules.map(m=>m['_probe_'+n](...args));assert.deepEqual(results[1],results[0],n+'('+args+')');state();comparisons++;return results[0];}
const reset=(seed=42)=>call('reset',seed),act=(op,a=0,b=0,c=0n)=>call('action',op,a,b,BigInt(c)),mon=(i,k,v)=>call('mon',i,k,BigInt(v)),hero=(k,v)=>call('hero',k,BigInt(v)),edog=(i,k,v)=>call('edog',i,k,BigInt(v));
function rolls(values){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});state();}
// All21 original function entries, actual extension allocation/reuse/free and full padding.
reset();act(0);act(0);act(2,0,1);act(2,0,0);act(1);act(1);act(7);act(13);
for(const pm of [L.PM_DOG,L.PM_HUMAN,L.PM_ANGEL])for(const all of [0,1,128,255]){reset();mon(0,0,pm);act(0);mon(0,1,-3);edog(0,0,0);edog(0,4,-1);act(2,0,all);}
for(const pets of [0n,1n,9007199254740993n,-1n]){reset();hero(4,1);hero(5,pets);act(0);act(2,0,1);}
for(const preferred of [0,99,100,110])for(const rolepet of [L.NON_PM,L.PM_PONY,L.PM_KITTEN]){reset();hero(0,rolepet);hero(1,preferred);rolls([0,1]);act(3);act(6);}
for(const role of [L.PM_CAVE_DWELLER,L.PM_SAMURAI,L.PM_BARBARIAN,L.PM_RANGER]){reset();hero(0,L.PM_LITTLE_DOG);hero(2,role);act(6);act(6);}
for(const quiet of [0,1])for(const fail of [0,1]){reset();call('option',0,fail);act(4,0,0,quiet);act(5,0,0,quiet);reset();call('option',4,fail);rolls([2]);act(4,0,-1,quiet);act(5,0,-1,quiet);}
for(const extinct of [0,L.G_EXTINCT])for(const limit of [0,3]){reset();call('vital',L.PM_DOG,extinct);call('option',7,limit);act(4,0,0);}
for(const blessed of [0,1])for(const cursed of [0,1])for(const r of [0,1,2,3,9]){reset();call('object',0,L.FIGURINE,L.PM_DOG,blessed,cursed);rolls([r]);act(5,0,0);}
for(const id of [0n,2147483648n,4294967295n]){reset();mon(0,40,id);act(0);}
for(const moves of [0n,9007199254740993n,-500n]){reset();call('moves',moves);act(0);act(2,0,1);act(19,0,1);}
// Catchup narrowing, packed timeouts, special states and long timers.
for(const time of [0n,1n,19n,20n,74n,75n,149n,150n,1000n,2147483647n,9007199254740993n]){reset();act(0);act(2,0,1);for(const k of [5,6,7,8,9,10,11,12,13])mon(0,k,k===11?100:1);rolls(Array(32).fill(1));act(11,0,0,time);}
for(const pet of [0,1,5,10])for(const time of [1n,200n,500n,1000n]){reset();act(0);mon(0,1,pet);edog(0,0,100n);mon(0,3,2);act(11,0,0,time);}
reset();call('chain',0,0,1);call('chain',2,2,-1);call('chain',1,3,-1);call('moves',1234567890123n);act(8);
for(const strategy of [0x8000000000000000n,0xa500000000000040n,0xffffffffffffffffn]){reset();mon(0,23,BigInt.asIntN(64,strategy));act(10,0,2);}
// Exact source pointer-to-link list updates and migration storage width.
for(const pm of [L.PM_DOG,L.PM_LONG_WORM])for(const when of [0,1,2,-1])for(const fail of [0,1]){reset();mon(0,0,pm);mon(0,22,5);mon(0,24,999);mon(0,31,L.MIGR_EXACT_XY);mon(0,33,8);mon(0,34,9);call('option',1,fail);call('option',15,1);act(10,0,when);}
for(const loc of [L.MIGR_RANDOM,L.MIGR_APPROX_XY,L.MIGR_EXACT_XY,L.MIGR_WITH_HERO,L.MIGR_STAIRS_UP,L.MIGR_STAIRS_DOWN,L.MIGR_LADDER_UP,L.MIGR_LADDER_DOWN,L.MIGR_SSTAIRS,L.MIGR_PORTAL]){reset();mon(0,31,loc);mon(0,33,8);mon(0,34,9);mon(0,24,999);call('chain',5,0,-1);act(10,0,2);}
for(const room of [0,1])for(const failed of [0,1]){reset();mon(0,24,900);mon(0,31,L.MIGR_APPROX_XY);mon(0,33,8);mon(0,34,9);call('option',2,room);call('option',25,failed);act(10,0,2);}
reset();call('level',0,3,1);mon(0,31,L.MIGR_PORTAL);act(10,0,2);
for(const worms of [0,1,31,63]){reset();mon(0,22,worms);call('option',16,63);call('chain',0,0,-1);act(12);act(15,0,204,L.MIGR_EXACT_XY);}
for(const bad of [0,1]){reset();call('extension',0,bad);mon(0,19,1);mon(0,27,1);mon(0,28,4);mon(0,31,L.MIGR_EXACT_XY);call('chain',2,0,1);mon(1,27,1);mon(1,28,4);mon(1,31,L.MIGR_RANDOM);call('option',1,bad);act(9);}
for(const petsOnly of [0,1])for(const follow of [0,1]){reset();act(0);act(2,0,1);call('chain',0,0,1);call('option',23,follow);call('option',24,follow);act(14,petsOnly);}
for(const keep of [0,1]){reset();mon(0,27,keep?3:1);mon(0,28,4);call('chain',2,0,1);mon(1,18,1);call('chain',3,0,-1);call('objfield',0,8,BigInt(keep?3:1));call('objfield',0,9,4n);call('objfield',0,10,-9223372036854775808n);act(16);}
// The native relmon callback reads and recursively mutates the active private head cell.
for(const nested of [0,1]){reset();call('option',1,1);call('option',30,1);call('option',31,nested);act(10,0,2);}
reset();call('chain',4,0,0);call('objfield',0,5,1n);call('objfield',0,7,2n);call('objfield',0,6,1n);call('objfield',1,6,1n);act(12);
for(const art of [0,1])for(const cursed of [0,1])for(const poison of [0,1])for(const resist of [0,1]){reset();act(0);call('object',0,L.DAGGER,L.PM_DOG,0,cursed);call('objfield',0,2,BigInt(art));call('objfield',0,0,BigInt(poison));call('option',9,resist);act(17,0,0);}
// Actual catalogue food and pet predicates; native world resistance remains observable.
for(let pm=0;pm<L.NUMMONS;pm++){reset();mon(0,0,pm);act(0);for(const type of [L.TRIPE_RATION,L.CORPSE,L.EGG,L.APPLE,L.CARROT,L.CLOVE_OF_GARLIC,L.TIN,L.DAGGER,L.CORPSE]){call('object',0,type,type===L.CORPSE?L.PM_HUMAN:L.PM_DOG,0,0);act(17,0,0);}}
for(const type of [L.CORPSE,L.EGG,L.TIN,L.LUMP_OF_ROYAL_JELLY,L.GLOB_OF_GREEN_SLIME,L.AMULET_OF_STRANGULATION,L.RIN_SLOW_DIGESTION])for(const corpse of [L.NON_PM,L.PM_COCKATRICE,L.PM_MEDUSA,L.PM_LIZARD,L.PM_LICHEN]){reset();act(0);mon(0,1,10);edog(0,1,2);call('object',0,type,corpse,0,1);call('objfield',0,3,0n);act(17,0,0);}
for(const food of [true,false])for(const tame of [0,1,5,10])for(const msg of [0,1]){reset();act(0);act(2,0,1);mon(0,1,tame);call('option',17,1);call('object',0,L.TRIPE_RATION,L.PM_DOG,0,0);rolls([0,1,5]);act(18,0,food?0:-1,msg);}
for(const pm of [L.PM_HUMAN,L.PM_MEDUSA,L.PM_ANGEL,L.PM_DOG]){reset();mon(0,0,pm);call('option',17,1);act(18,0,-1,1);}
for(const abuse of [0,1,3,9,10,-1])for(const killed of [0,1])for(const dead of [0,1]){reset();act(0);act(2,0,1);edog(0,2,abuse);edog(0,3,killed);edog(0,1,5);call('option',17,1);rolls([0,1]);act(19,0,dead);}
for(const tame of [0,1,2,10,-1])for(const aggravate of [0,1]){reset();act(0);mon(0,1,tame);hero(13,aggravate);call('option',17,1);act(20);}
reset();call('option',29,1);call('object',0,L.FIGURINE,L.PM_DOG,1,0);const before=modules.map(m=>m.HEAPU8.buffer);act(5,0,0);modules.forEach((m,i)=>assertMemoryGrowth(m,before[i]));
// A/B/A instances share JS implementation but retain independent private failed lists.
reset();const other=await hybridFactory({nethackPorted:{dog:(s,n,...args)=>callDog(s,L,n,...args)}});other._probe_reset(42);const otherStack=other._probe_stack();
assert.equal(other._probe_count(7),-1);call('option',1,1);act(10,0,2);assert.equal(other._probe_count(7),-1);
other._probe_option(1,1);other._probe_action(10,1,2,0n);assert.equal(other._probe_count(7),1);assert.equal(modules[1]._probe_count(7),0);reset();assert.equal(other._probe_count(7),1);assertStackRestored(other,otherStack);comparisons+=6;
console.log('DOG '+comparisons+' comparisons passed ('+referenceLabel+' vs JavaScript).');
