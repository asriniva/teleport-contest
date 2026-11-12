import { Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('minion', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/minion-reference.mjs';
import hybridFactory from '../.cache/tu-probes/minion-hybrid.mjs';
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
import {elementals_initial} from '../js/ported/minion.js';
import {C,R,T} from '../js/c-runtime/context.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),layout=layouts.minion;
const modules=[await referenceFactory(),await hybridFactory({nethackPorted:createPortedRuntime(layouts)})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function bytes(m,p,n){p=Number(p);if(n===undefined){if(!p)return null;let e=p;while(m.HEAPU8[e])e++;n=e-p;}if(!p)return null;return Buffer.from(m.HEAPU8.slice(p,p+n));}
function snapshot(m){return {monsters:Array.from({length:32},(_,i)=>({fields:Array.from({length:14},(_,f)=>m._probe_mon_field(i,f)),strategy:BigInt.asUintN(64,m._probe_strategy(i)),emin:bytes(m,m._probe_emin_pointer(i),Number(m._probe_emin_size()))})),equipment:[0,1,2,3].map(i=>bytes(m,m._probe_object_pointer(i),Number(m._probe_object_size()))),cash:m._probe_cash_value(),pets:m._probe_pets(),botl:m._probe_botl(),created:m._probe_count(),rng:m._probe_rng_count(),random:m._probe_rng_state()>>>0,trace:bytes(m,m._probe_trace()).toString('hex')};}
function state(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m, stacks[i]));comparisons++;}
function call(name,...args){const result=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(result[1],result[0],`${name}(${args})`);state();comparisons++;return result[0];}
function reset(seed=1){call('reset',seed);}
function rng(values){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});state();}
function input(text){modules.forEach(m=>{const b=Buffer.from(text),p=m._malloc(BigInt(b.length+1));m.HEAPU8.set(b,Number(p));m.HEAPU8[Number(p)+b.length]=0;m._probe_input(BigInt(p));m._free(p);});state();}
function victim(pm=layout.PM_HORNED_DEVIL,{index=0,peace=1,hp=20,guard=0,x=9,invisible=0,cham=layout.NON_PM,id=100,strategy=0xffffffffffffffffn}={}){call('victim',index,pm,peace,hp,guard,x,invisible,cham,id,strategy);}
function trace(){return bytes(modules[0],modules[0]._probe_trace()).toString();}
function act(n,v=0){return call('action',n,v);}
reset();
for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const key=bytes(m,m._probe_layout_name(i)).toString();assert.equal(Number(BigInt.asIntN(64,m._probe_layout_value(i))),layout[key],key);}
for(const key of ['PM_HUMAN','PM_HORNED_DEVIL','PM_VROCK','PM_ANGEL','NON_PM','A_NONE','A_CHAOTIC','A_LAWFUL','A_NEUTRAL'])assert.ok(Number.isSafeInteger(layout[key]),key);
assert.deepEqual(elementals_initial.map(k=>layout[k]),[0,1,2,3].map(n=>modules[0]._probe_elemental(n)));
// EMIN's complete bytes, parent ID and existing allocation are preserved until
// free_emin clears the pointer; independent assertions establish reachability.
for(const id of [0,100,0x80000000,0xffffffff]){reset();victim(undefined,{id});call('emin',0,0);assert.equal(call('parent',0)>>>0,id);const first=modules.map(m=>m._probe_emin_pointer(0));call('emin_flags',0,1,90);call('emin',0,0);modules.forEach((m,i)=>assert.equal(m._probe_emin_pointer(0),first[i]));call('emin',0,1);assert.equal(call('mon_field',0,4),0);assert.equal(call('mon_field',0,2),0);call('emin',0,1);}
reset();call('emin_flags',0,1,0);call('emin',0,1);assert.equal(call('mon_field',0,3),0);
for(const spotted of [0,1,2,256]){reset();victim(layout.PM_HUMAN,{index:0,hp:20});victim(layout.PM_HUMAN,{index:1,hp:0});victim(layout.PM_GUARD,{index:2,hp:20,guard:1,x:0});victim(layout.PM_HUMAN,{index:3,hp:20,invisible:1});call('chain',4);call('option',3,0);assert.equal(act(0,spotted),spotted%256?1:2);}
// Candidate selection uses real monster traits, native fallback callbacks,
// extinct records and the original twenty-attempt limits.
for(const align of [layout.A_NONE,layout.A_CHAOTIC,layout.A_NEUTRAL,layout.A_LAWFUL])for(const endgame of [0,1])for(const gone of [0,1]){reset();call('endgame',endgame);for(let pm=layout.PM_ORCUS;pm<=layout.PM_DEMOGORGON;pm++)call('vital',pm,gone);for(let pm=layout.PM_JUIBLEX;pm<=layout.PM_YEENOGHU;pm++)call('vital',pm,gone);rng(Array(64).fill(0));act(4,align);act(5,align);}
for(const chosen of [-1,layout.PM_ARCHON,layout.PM_ANGEL]){reset();call('option',5,chosen);act(7);}
for(const chosen of [-1,layout.PM_HUMAN,layout.PM_HORNED_DEVIL,layout.PM_VROCK])for(const align of [layout.A_NONE,layout.A_LAWFUL,layout.A_CHAOTIC]){reset();call('option',6,chosen);act(8,align);}
reset();call('vital',layout.PM_ARCHON,1);call('option',5,-1);assert.equal(act(6),layout.NON_PM);
// Summoning counts include native group generation, failures and cloud/light
// callbacks. Native makemon reenters the imported newemin function.
for(const pm of [layout.PM_DEMOGORGON,layout.PM_JUIBLEX,layout.PM_BONE_DEVIL,layout.PM_HORNED_DEVIL,layout.PM_ARCHON,layout.PM_ANGEL,layout.PM_HUMAN])for(const roll of [0,1,19])for(const failure of [0,1,2]){reset();victim(pm);call('option',0,failure);call('option',2,1);rng(Array(128).fill(roll));act(1,1);}
for(const fallback of [-1,layout.PM_HORNED_DEVIL]){reset();victim(layout.PM_BONE_DEVIL);call('vital',layout.PM_SKELETON,1);call('option',6,fallback);assert.equal(act(1,1),fallback<0?0:1);if(fallback>=0)assert.equal(call('mon_field',1,0),fallback);}
reset();victim(layout.PM_DEMOGORGON);call('unique',layout.PM_HORNED_DEVIL,1);rng([1,1,0]);assert.equal(act(1,1),1);assert.equal(call('count'),1);
reset();call('copy_monster',layout.PM_HORNED_DEVIL);rng([1,1]);assert.equal(act(1,1),1);assert.equal(call('mon_field',1,0),layout.PM_HORNED_DEVIL);
for(const minionAlign of [layout.A_LAWFUL,layout.A_NEUTRAL,layout.A_CHAOTIC,layout.A_NONE])for(const priest of [0,1])for(const peace of [0,1]){reset();victim(layout.PM_ANGEL,{peace});call('minion',0,minionAlign,1);if(priest)call('priest',0,layout.A_NEUTRAL);call('option',1,peace);rng(Array(64).fill(0));act(1,1);}
for(const blind of [0n,1n]){reset();victim(layout.PM_ANGEL);call('properties',0n,blind,0n,0,0,0);act(1,1);}
reset();victim(layout.PM_BONE_DEVIL);call('option',2,2);assert.equal(act(1,1),3);assert.equal(call('count'),3);assert.ok(trace().includes('environ:'));
reset();call('wield',layout.ART_DEMONBANE);assert.equal(act(1,1),0);assert.equal(call('count'),0);
reset();rng(Array(64).fill(1));act(1,0);
for(const chosen of [layout.PM_ANGEL,layout.PM_SHOPKEEPER,layout.PM_GUARD,layout.PM_ALIGNED_CLERIC,layout.PM_HIGH_CLERIC,-1])for(const talk of [0,1])for(const deaf of [0n,1n]){reset();call('option',5,chosen);call('properties',deaf,0n,0n,0,0,0);call('summon',layout.A_LAWFUL,talk);}
for(const alignment of [layout.A_NEUTRAL,layout.A_CHAOTIC,layout.A_NONE,127,128]){reset();rng([0]);call('summon',alignment,1);}
// Native sscanf retains whitespace, prefix, trailing text, and overflow behavior.
for(const text of ['', 'abc','-1','0','+1','  12 trailing','0x10','01','9007199254740993','9223372036854775807','9223372036854775808','-9223372036854775809','9'.repeat(200),'\t\n+5x','\x1b'])for(const money of [0n,100n,9007199254740995n,9223372036854775807n]){reset();call('cash',money);input(text);call('bribe');}
reset();call('cash',9007199254740995n);input('9007199254740993 rest');assert.equal(call('bribe'),9007199254740993n);assert.equal(call('cash_value'),2n);assert.equal(call('botl'),1);
for(const weapon of [layout.ART_EXCALIBUR,layout.ART_DEMONBANE])for(const see of [0,1]){reset();call('wield',weapon);call('option',3,0);call('option',4,see);assert.equal(act(3),0);assert.equal(call('mon_field',0,1),0);}
for(const faint of [0,1])for(const multi of [-1,0,5])for(const demon of [0,1])for(const deaf of [0n,1n])for(const restricted of [0,1]){reset();call('option',9,faint);call('option',10,restricted);call('hero',1,20,10,multi,1n);call('properties',deaf,0n,0n,0,demon,1);input('1000');rng([0,0]);act(3);}
for(const invisible of [0,1])for(const sensed of [0,1]){reset();victim(layout.PM_DEMOGORGON,{invisible});call('option',3,sensed);call('properties',0n,0n,0n,0,1,0);act(3);}
for(const money of [0n,1n,100n,9007199254740993n,9223372036854775807n])for(const roll of [0,79])for(const hell of [0,1])for(const cham of [layout.NON_PM,layout.PM_HUMAN]){reset();victim(undefined,{cham});call('cash',money);call('option',8,hell);input('1');rng([roll,0,0]);act(3);}
for(const amulet of [0,1])for(const deaf of [0n,1n])for(const offer of ['0','1','10','100','1000']){reset();call('option',11,amulet);call('properties',deaf,0n,0n,0,0,0);call('cash',100n);input(offer);rng([79,0,89]);act(3);}
reset();call('cash',100n);input('100');rng([79]);assert.equal(act(3),1);assert.equal(call('mon_field',0,9),0);assert.ok(trace().includes('bribed a fixture demon'));
for(const exists of [0,1])for(const deaf of [0n,1n])for(const fail of [0,1]){reset();call('properties',deaf,0n,0n,0,0,0);call('option',13,fail);rng([0]);act(9,exists);}
for(const conflict of [0n,1n])for(const record of [8,9])for(const pets of [-1n,0n,1n,9007199254740993n,9223372036854775807n])for(const fail of [0,1]){reset();call('properties',0n,0n,conflict,0,0,0);call('hero',1,record,20,0,pets);call('option',7,fail);rng(Array(128).fill(0));act(10);}
for(const deaf of [0n,1n])for(const roledeaf of [0,1])for(const cure of [0,1])for(const blind of [0n,1n])for(const weapon of [0,1])for(const shield of [0,1])for(const spe of [-128,3,4,127]){reset();call('properties',deaf,blind,0n,roledeaf,0,0);call('option',14,cure);call('option',15,weapon);call('option',16,shield);call('equip',spe,shield?layout.SILVER_SABER:layout.SHIELD_OF_REFLECTION);rng(Array(128).fill(0));act(10);}
reset();rng(Array(128).fill(0));act(10);assert.equal(call('count'),1);assert.equal(call('mon_field',1,5),10);assert.equal(call('pets'),2n);assert.ok(call('mon_field',1,9)>30);assert.ok(trace().includes('bless:0;'));
reset();call('option',19,0);rng(Array(64).fill(1));act(1,1);
reset();const saved=snapshot(modules[0]);modules[1]._probe_cash(1n);assert.deepEqual(snapshot(modules[0]),saved);reset();call('emin',0,0);const pointers=modules.map(m=>m._probe_emin_pointer(0)),sizes=modules.map(m=>allocationMetric(m)),grown=modules.map(m=>m._malloc(40n*1024n*1024n));assert.ok(grown.every(Boolean));modules.forEach((m,i)=>{assert.ok(allocationMetric(m)>sizes[i]);assert.equal(m._probe_emin_pointer(0),pointers[i]);});act(1,1);call('emin',0,1);input('7');call('bribe');modules.forEach((m,i)=>m._free(grown[i]));state();
console.log(`MINION: ${comparisons} ${referenceLabel}/hybrid emin, summoning, demon-money, scanf, guardian and callback/RNG-site comparisons checked.`);
