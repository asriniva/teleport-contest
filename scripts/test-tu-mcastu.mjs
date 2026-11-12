import './pure-js-probes/deny-wasm.mjs';
import { Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('mcastu', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/mcastu-reference.mjs';
import createGeneratedProbe from './pure-js-fixtures/runtime.mjs';
const hybridFactory=options=>createGeneratedProbe('mcastu',options);
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
import {C,R,T} from '../js/c-runtime/context.js';
import * as core from '../js/ported/mcastu.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),L=layouts.mcastu,runtime=createPortedRuntime(layouts),modules=[await referenceFactory(),await hybridFactory({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
const text=(m,p)=>{p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');};
const snap=m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),rng:m._probe_rng_state()>>>0,count:m._probe_rng_count()});
function check(){assert.deepEqual(snap(modules[1]),snap(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m, stacks[i]));comparisons++;}
function call(name,...args){if(['set_monster','hero'].includes(name))args[1]=BigInt(args[1]);if(name==='prop')args[2]=BigInt(args[2]);const r=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(r[1],r[0],name+':'+args);comparisons++;check();return r[0];}
const reset=(s=1)=>call('reset',s),opt=(k,v)=>call('option',k,v),mon=(k,v)=>call('set_monster',k,v),hero=(k,v)=>call('hero',k,v),prop=(p,k,v)=>call('prop',p,k,v),att=(k,v)=>call('attack',k,v),act=(op,a=0,b=0,c=0)=>Number(call('action',op,a,b,c));
const trace=()=>text(modules[0],modules[0]._probe_trace()),state=()=>text(modules[0],modules[0]._probe_snapshot());
function rng(values){for(const m of modules){new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);}check();}
reset();for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const k=text(m,m._probe_layout_name(i)),raw=m._probe_layout_value(i);assert.equal(typeof L[k]==='string'?BigInt.asUintN(64,raw).toString():Number(BigInt.asIntN(64,raw)),L[k],k);}
const required=['AD_SPEL','AD_CLRC','AD_FIRE','AD_COLD','AD_MAGM','AD_ELEC','AD_PHYS','PM_HUMAN','PM_LICH','PM_WIZARD_OF_YENDOR','PM_GHOST','PM_GIANT_ANT','PM_WATER_MOCCASIN','PM_HORNED_DEVIL','FIRE_RES','COLD_RES','SHOCK_RES','ANTIMAGIC','HALF_SPDAM','HALF_PHDAM','FREE_ACTION','HALLUC','HALLUC_RES','BLINDED','CONFUSION','STUNNED','INVIS','DISPLACED','SEE_INVIS','DEAF','DETECT_MONSTERS','MFAST','M_AP_OBJECT','STRANGE_OBJECT'];
for(const k of required)assert.ok(Number.isSafeInteger(L[k]),k);
const spellNames=['PSI_BOLT','OPEN_WOUNDS','CURE_SELF','HASTE_SELF','CONFUSE_YOU','STUN_YOU','DISAPPEAR','PARALYZE','BLIND_YOU','WEAKEN_YOU','DESTRY_ARMR','INSECTS','CURSE_ITEMS','LIGHTNING','FIRE_PILLAR','GEYSER','AGGRAVATION','SUMMON_MONS','CLONE_WIZ','DEATH_TOUCH'];
for(const s of spellNames)assert.ok(Number.isSafeInteger(L['MCAST_'+s]),s);
// All catalogue rows and list order come from the native original, not a mirrored expected initializer.
assert.equal(core.mcast_data.length,modules[0]._probe_table_count(0));for(let i=0;i<core.mcast_data.length;i++){for(const [field,k]of [['level',0],['flags',1]]){const value=core.mcast_data[i][field];assert.equal(Array.isArray(value)?value.reduce((bits,name)=>bits|L[name],0):value,modules[0]._probe_table(0,i,k));comparisons++;}}
for(const [table,index]of [[core.mon_cleric_spells,1],[core.mon_wizard_spells,2]]){assert.equal(table.length,modules[0]._probe_table_count(index));for(let i=0;i<table.length;i++){assert.equal(typeof table[i]==='string'?L[table[i]]:table[i],modules[0]._probe_table(index,i,0));comparisons++;}}

// Every directedness/usefulness entry, independent predicate states, high-bit resistance masks and retry selection.
for(let spell=0;spell<20;spell++)for(const mode of [0,1,2,3,4,5,6,7,8,9]){reset();if(mode===1)mon(8,1);if(mode===2)opt(21,0);if(mode===3)mon(5,1);if(mode===4)mon(9,L.MFAST);if(mode===5)mon(6,1);if(mode===6)mon(1,40);if(mode===7)prop(L.BLINDED,0,3);if(mode===8)prop(L.ANTIMAGIC,0,1);if(mode===9)opt(19,0);rng([0,1,99]);act(24,spell);act(25,spell);}
for(const ad of [L.AD_SPEL,L.AD_CLRC,L.AD_PHYS])for(const level of [1,2,7,20,25,100,255])for(const roll of [0,1,5,19,254]){reset();mon(0,level);rng([roll,1,2,1]);const selected=act(5,ad);assert.ok(selected>=0&&selected<20);}
reset();mon(8,1);opt(21,0);rng(Array(100).fill(0));assert.equal(act(0,1,1),0);assert.equal(modules[0]._probe_rng_count(),40); // All40 requested attack selections remain useless.
for(const stateCase of ['cancelled','cooldown','zero','seen','noncaster']){reset();if(stateCase==='cancelled')mon(3,1);if(stateCase==='cooldown')mon(10,9);if(stateCase==='zero')mon(0,0);if(stateCase==='seen'){mon(11,(1n<<60n)|1n);opt(6,1);att(0,L.AD_FIRE);}if(stateCase==='noncaster'){att(0,L.AD_PHYS);mon(0,0);}rng([0]);act(0,1,1);}

// All individual effects execute through actual native callers with all major resistance and damage thresholds.
for(const op of [17,18])for(const damage of [-3,0,1,5,6,10,11,20,21,101])for(const magic of [0,1]){reset();if(magic)prop(L.ANTIMAGIC,0,1);const actual=act(op,damage);assert.equal(actual,magic?Math.trunc((damage+1)/2):damage);}
for(const half of [0,1]){reset();if(half)prop(L.HALF_PHDAM,0,1);rng(Array(8).fill(5));assert.equal(act(14,99),half?24:48);}
for(const op of [15,16])for(const resist of [0,1])for(const half of [0,1])for(const reflects of [0,1]){reset();if(resist)prop(op===15?L.FIRE_RES:L.SHOCK_RES,0,1);if(half)prop(L.HALF_SPDAM,0,1);opt(12,reflects);rng(Array(10).fill(5));const value=act(op,99);assert.equal(value,resist||(op===16&&reflects)?0:half?24:48);assert.equal(trace().includes('spot:'),op!==16||!reflects);}
for(const op of [10,11,13,20,21,22])for(const magic of [0,1])for(const half of [0,1])for(const free of [0,1]){reset();if(magic)prop(L.ANTIMAGIC,0,1);if(half)prop(L.HALF_SPDAM,0,1);if(free)prop(L.FREE_ACTION,1,1);rng([0,1,2,3]);const value=act(op,9);if(op===21){assert.equal(value,magic||free?1:half?15:29);assert.ok(state().includes(`:${-(magic||free?1:half?15:29)}:paralyzed by a monster:`));}if(op===20)assert.ok(trace().includes(`blind:${half?100:200}:0;`));}
reset();prop(L.FREE_ACTION,0,1);assert.equal(act(21),29);assert.ok(trace().includes('nomul:-29;'));
for(const dex of [1,11,12,25]){reset();opt(9,dex);prop(L.STUNNED,0,(1n<<53n)+17n);rng(Array(6).fill(0));act(13,7);assert.ok(trace().includes(`dice:${dex<12?6:4}:4:`));}
for(const already of [0,1]){reset();if(already)prop(L.CONFUSION,0,7);prop(L.HALLUC,0,1);act(22);assert.ok(trace().includes(already?'trippier':'trippy'));}
for(const healed of [0,1]){reset();mon(1,healed?40:10);rng([5,5,5]);assert.equal(act(6,9),healed?9:0);assert.equal(trace().includes('heal:'),!healed);}
for(const blocked of [0,1])for(const seen of [0,1]){reset();mon(7,blocked);opt(1,seen);act(12);assert.equal(trace().includes('invis:0:0;'),!blocked);}
for(const count of [0,1,2])for(const wiz of [0,1]){reset();mon(5,wiz);opt(7,count);act(9);if(count&&wiz)assert.ok(trace().includes('verbalize:Destroy the thief'));}
reset();mon(5,1);act(8);assert.ok(state().includes(':2:-1;'));reset();act(8);assert.ok(trace().includes('bad wizard cloning'));
for(const body of [L.PM_HUMAN,L.PM_GHOST,L.PM_HORNED_DEVIL])for(const magic of [0,1])for(const hallu of [0,1]){reset();hero(0,body);hero(1,body);if(magic)prop(L.ANTIMAGIC,0,1);if(hallu)prop(L.HALLUC,0,1);rng([24,...Array(8).fill(0)]);act(7);}
for(const polymorph of [0,1])for(const fatal of [0,1]){reset();if(polymorph){hero(1,L.PM_LICH);hero(4,30);}hero(3,fatal?10:200);rng(Array(8).fill(0));act(1);assert.equal(trace().includes('rehumanize;'),!!polymorph);if(!polymorph)assert.equal(trace().includes('done:'),!!fatal);}
for(const hasMonster of [0,1])for(const species of [L.PM_HUMAN,L.PM_WIZARD_OF_YENDOR,L.PM_LICH]){reset();mon(14,species);mon(15,L.PM_HUMAN);act(2,hasMonster);assert.ok(state().includes('fixture death'));}

// Summoning genuine native monster records, both fallback species and all creation/failure/visibility messages.
for(const fallback of [0,1,2])for(const failure of [0,1,2])for(const sight of [0,1])for(const hallu of [0,1]){reset();opt(14,fallback);opt(16,failure===1);opt(17,failure===2);opt(1,sight);opt(21,sight?3:0);if(hallu)prop(L.HALLUC,0,1);rng([0]);act(19);if(!fallback&&!failure)assert.ok(state().includes('spawn:4:'));if(failure===1)assert.ok(!trace().includes('make:'));}
for(const unaware of [0,1,2]){reset();opt(1,0);opt(21,0);opt(15,0);hero(8,-((1n<<53n)+7n));opt(22,unaware===1);opt(23,unaware===2);rng([0]);act(19);assert.ok(trace().includes('You_hear:someone summoning'));}
// Every dispatch row and invalid policy guards, followed by all ranged damage types/target states.
for(let spell=0;spell<20;spell++){reset();mon(5,1);rng(Array(100).fill(1));act(23,17,spell);}
reset();act(23,-1,0);assert.ok(trace().includes('negative dmg'));reset();act(23,0,L.MCAST_PSI_BOLT);assert.ok(trace().includes('directed wizard spell'));reset();act(23,2,999);assert.ok(trace().includes('invalid magic spell'));
for(const ad of [L.AD_FIRE,L.AD_COLD,L.AD_MAGM,L.AD_SPEL,L.AD_CLRC])for(const found of [0,1])for(const thinks of [0,1])for(const resist of [0,1]){reset();att(0,ad);if(resist){prop(L.FIRE_RES,0,1);prop(L.COLD_RES,0,1);prop(L.ANTIMAGIC,0,1);}rng(Array(100).fill(99));act(0,thinks,found);}
for(const ad of [L.AD_FIRE,L.AD_COLD,L.AD_ELEC,L.AD_MAGM,L.AD_PHYS])for(const cancelled of [0,1])for(const lined of [0,1]){reset();att(0,ad);mon(3,cancelled);opt(20,lined);rng([1]);act(3);assert.ok(state().includes(':-1;'));if(ad===L.AD_FIRE&&!cancelled&&lined)assert.ok(trace().includes('buzz:'));}
for(const visible of [0,1])for(const mode of [0,1,2,3]){reset();opt(1,visible);opt(21,visible?3:0);hero(7,(1n<<53n)+1n);if(mode===1){prop(L.INVIS,0,1);mon(12,9);}if(mode===2){prop(L.DISPLACED,0,1);mon(12,9);}if(mode===3)hero(6,1);rng([0]);act(4,0);}

reset();opt(24,1);att(0,L.AD_FIRE);rng(Array(30).fill(99));act(0,1,1);assert.ok(trace().includes('castmu:Caster,lvl:25,spell:0'));assert.ok(state().includes(';lastmsg:0;'));

// Each native boundary reenters JS and forces actual memory growth; effects and scratch outputs remain coherent.
for(let stage=1;stage<=16;stage++){reset();opt(30,stage);opt(31,stage);const before=modules.map(m=>allocationMetric(m));rng(Array(100).fill(1));if(stage===1)act(14);else if(stage===2){prop(L.ANTIMAGIC,0,1);act(17,9);}else if(stage===3)act(23,9,L.MCAST_PSI_BOLT);else if(stage===4)act(6,9);else if(stage===5)act(11,9);else if(stage===6){opt(7,1);act(9);}else if(stage===7)act(10);else if(stage===8)act(12);else if(stage===9)act(22);else if(stage===10||stage===11||stage===12)act(15,9);else if(stage===13)act(16,9);else if(stage===14||stage===15)act(19);else{att(0,L.AD_FIRE);act(3);}assert.ok(trace().includes(`grow:${stage};`));assert.ok(trace().includes('reenter:'));modules.forEach((m,i)=>assert.ok(allocationMetric(m)>before[i]));}
reset();opt(0,0);act(14);assert.ok(trace().includes('@;'));
reset();mon(5,1);act(8);const held=snap(modules[1]),other=await hybridFactory({nethackPorted:runtime});other._probe_reset(8);other._probe_set_monster(5,1n);other._probe_action(8,0,0,0);other._probe_action(13,8,0,0);assert.ok(text(other,other._probe_trace()).includes('clone;'));assert.deepEqual(snap(modules[1]),held);comparisons+=2;check();
console.log(`MCASTU ${referenceLabel}/pure-JS differential: ${comparisons} comparisons checked`);
