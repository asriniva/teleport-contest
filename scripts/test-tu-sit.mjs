import './pure-js-probes/deny-wasm.mjs';
import { Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('sit', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/sit-reference.mjs';
import createGeneratedProbe from './pure-js-fixtures/runtime.mjs';
const hybridFactory=options=>createGeneratedProbe('sit',options);
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
import {C,R,T} from '../js/c-runtime/context.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),L=layouts.sit,runtime=createPortedRuntime(layouts),modules=[await referenceFactory(),await hybridFactory({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function text(m,p){p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');}
function snapshot(m){return {state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),count:m._probe_rng_count(),rng:m._probe_rng_state()>>>0};}
function state(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m, stacks[i]));comparisons++;}
const longs={obj:[2],obit:[2],hero:[1],prop:[2]};
function call(name,...args){args=args.map((a,i)=>longs[name]?.includes(i)?BigInt(a):a);const r=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(r[1],r[0],`${name}(${args})`);state();comparisons++;return r[0];}
function reset(seed=1){call('reset',seed);}
function rng(values){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});state();}
function input(s){modules.forEach(m=>{const bytes=Buffer.from(s+'\0','latin1'),p=Number(m._malloc(BigInt(bytes.length)));m.HEAPU8.set(bytes,p);m._probe_input(BigInt(p));m._free(p);});state();}
function obj(i,type,q=1n,where=L.OBJ_INVENT){call('obj',i,type,q,where);}
function inventory(indices){indices.forEach((v,i)=>call('next',v,indices[i+1]??-1));call('inventory',indices[0]??-1);}
function act(op,effect=0){return call('action',op,effect);}
function trace(){return text(modules[0],modules[0]._probe_trace());}
function fields(prefix){return text(modules[0],modules[0]._probe_snapshot()).split(';').find(s=>s.startsWith(prefix+':')).split(':').slice(1);}
function hero(i){return BigInt(fields('hero')[i]);}
function of(i,f){return BigInt(fields('o'+i)[f]);}
function prop(i,f=0){return BigInt(fields('p'+i)[f]);}
function cell(x=10,y=10){return fields('map').join(':').split('/').filter(Boolean).map(x=>x.split(',').map(Number)).find(v=>v[0]===x&&v[1]===y);}
function ordinary(effect,extra=[]){rng([4,effect-1,...extra,...Array(40).fill(1)]);return act(4);}
reset();for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const k=text(m,m._probe_layout_name(i));assert.equal(Number(BigInt.asIntN(64,m._probe_layout_value(i))),L[k],k);}
for(const k of ['ECMD_OK','ECMD_TIME','ROOM','THRONE','EGG','SICK','GLIB','FIRE_RES','INTRINSIC','PM_HUMAN','PM_COCKATRICE','PM_GIANT_EEL','PM_ELECTRIC_EEL','PM_GREMLIN','PM_TRAPPER','PM_VAMPIRE','PM_RED_DRAGON','PM_GREEN_SLIME'])assert.ok(Number.isSafeInteger(L[k]),k);
// Mixed coin chains test saved-next traversal, worn removal and empty sensation.
for(const pattern of [[],[L.GOLD_PIECE],[L.LONG_SWORD],[L.GOLD_PIECE,L.LONG_SWORD,L.GOLD_PIECE]]){reset();pattern.forEach((t,i)=>obj(i,t,(1n<<53n)+1n));inventory(pattern.map((_,i)=>i));act(0);pattern.forEach((t,i)=>{if(t===L.GOLD_PIECE)assert.equal(of(i,3),BigInt(L.OBJ_DELETED));});assert.equal(hero(19),pattern.includes(L.GOLD_PIECE)?1n:0n);}
// Every ordinary effect uses the native oracle's random call ordering.
for(let effect=1;effect<=13;effect++)for(const female of [0,1]){reset(13);call('hero',0,female);call('terrain',10,10,L.THRONE,31);obj(0,L.LONG_SWORD);obj(1,L.GOLD_PIECE,100n);inventory([0,1]);ordinary(effect);if(effect===5)assert.equal(of(1,3),BigInt(L.OBJ_DELETED));if(effect===6)assert.match(trace(),/wish;/);if(effect===7)assert.match(trace(),/make:/);if(effect===8)assert.match(trace(),/genocide:5/);if(effect===12)assert.match(trace(),/identify:/);}
for(const shock of [0,1]){reset();if(shock)call('prop',L.SHOCK_RES,0,1);ordinary(3);assert.match(trace(),/electric shock/);}
for(const polymorphed of [0,1]){reset();call('species',polymorphed?L.PM_COCKATRICE:L.PM_HUMAN,polymorphed);call('hero',9,38);call('hero',12,29);call('hero',14,17);call('prop',L.BLINDED,0,500);call('prop',L.SICK,0,200);ordinary(4);assert.equal(hero(6),44n);assert.equal(hero(7),44n);assert.equal(hero(8),44n);assert.equal(hero(15),0n);assert.equal(prop(L.BLINDED),0n);if(polymorphed){assert.equal(hero(9),34n);assert.equal(hero(10),34n);}}
for(const luck of [-10,0,1,2,10]){reset();call('hero',7,luck);ordinary(6,[0]);reset();call('hero',7,luck);ordinary(9,[0,0,0]);}
for(const luck of [-1,0])for(const see of [0,1])for(const blockedMap of [0,1])for(const blind of [0,1]){reset();call('hero',7,luck);call('hero',24,blockedMap);if(see)call('prop',L.SEE_INVIS,0,L.INTRINSIC);if(blind)call('prop',L.BLINDED,0,1);ordinary(10);if(luck<0||see)assert.match(trace(),blockedMap?/confused:/:/mapping;/);else assert.ok(prop(L.SEE_INVIS)&BigInt(L.FROMOUTSIDE));}
for(const [pm,message] of [[L.PM_HUMAN,/eyes/],[L.PM_FLOATING_EYE,/eye /],[L.PM_GREEN_SLIME,/very strange feeling/]]){reset();call('species',pm,1);call('prop',L.BLINDED,0,1);ordinary(10);assert.match(trace(),message);}
for(const pm of [L.PM_HUMAN,L.PM_VAMPIRE])for(const hand of [0,1]){reset();call('species',pm,1);call('hero',23,hand);rng([0,1]);act(4);assert.match(trace(),/comfortable|out of place/);}
// Wizard cancel, valid/invalid overrides, fuzzer bypass, and throne removal at tx/ty.
for(const answer of ['\x1b','0','1','13','14','-1','  5junk']){reset();call('hero',1,1);input(answer);rng([4,5,...Array(30).fill(1)]);act(4);assert.match(trace(),/getlin:/);if(answer==='\x1b')assert.match(trace(),/Never mind/);}
reset();call('hero',1,1);call('hero',2,1);ordinary(6);assert.ok(!trace().includes('getlin:'));
for(const wizard of [0,1])for(const yes of ['y','n']){reset();call('terrain',10,10,L.THRONE,31);call('terrain',20,12,L.THRONE,17);call('hero',1,wizard);call('option',2,yes.charCodeAt(0));if(wizard)input('11');rng([4,10,0]);act(4);assert.equal(hero(0),20n);assert.equal(hero(1),12n);assert.equal(cell(10,10)[2],!wizard||yes==='y'?L.ROOM:L.THRONE);assert.equal(cell(20,12)[2],L.THRONE);}
// All special effects, state restoration and controlled callbacks.
for(let effect=1;effect<=13;effect++){reset(31);call('option',1,1);call('terrain',10,10,L.THRONE,31);obj(0,L.LONG_SWORD);obj(1,L.GOLD_PIECE,99n);inventory([0,1]);rng(Array(40).fill(1));act(5,effect);if(effect<=4)assert.equal(cell()[2],L.ROOM);if(effect===5){assert.equal(hero(4),9n);assert.equal(hero(5),9n);}if(effect===6){assert.equal(of(0,8),1n);assert.equal(of(1,8),0n);assert.ok(prop(L.GLIB)>0n);}if(effect===8)assert.match(trace(),/goto:2:19:/);if(effect===9)assert.equal((trace().match(/summon:/g)||[]).length,3);if(effect===10)assert.equal(prop(L.CONFUSION),0n);if(effect===13)assert.equal((trace().match(/attribute:/g)||[]).length,6);}
for(const resist of [0,1]){reset();if(resist)call('prop',L.DRAIN_RES,0,1);act(5,5);assert.equal(hero(4),resist?10n:9n);reset();if(resist)call('prop',L.ACID_RES,0,1);act(5,12);}
reset();call('hero',22,1);act(5,8);assert.ok(!trace().includes('goto:'));assert.match(trace(),/disoriented/);
for(const pm of [L.PM_HUMAN,L.PM_VAMPIRE]){reset();call('species',pm,1);act(5,11);assert.equal(trace().includes('poly:'),pm!==L.PM_VAMPIRE);}
reset();call('option',1,1);rng([4,0]);act(4);assert.match(trace(),/wish;/);assert.ok(!trace().includes('yn:'));
reset();call('prop',L.CONFUSION,0,(1n<<53n)+1n);obj(0,L.GOLD_PIECE,7n);inventory([0]);call('option',20,1);call('option',21,1);const before=modules.map(m=>allocationMetric(m));act(5,10);assert.equal(prop(L.CONFUSION),(1n<<53n)+1n);assert.equal(of(0,3),BigInt(L.OBJ_DELETED));modules.forEach((m,i)=>assert.ok(allocationMetric(m)>before[i]));assert.match(trace(),/nested-begin;.*nested-end;grew;/);
// Egg creation checks sex, precise food boundary, species, water and timers callback.
for(const female of [0,1])for(const energy of [-1,0,1])for(const halluc of [0,1]){reset();call('hero',0,female);call('hero',27,energy);if(halluc)call('prop',L.HALLUC,0,1);const result=act(6);if(female&&energy>=0){assert.equal(result,L.ECMD_TIME);assert.equal(of(15,5),1n);assert.equal(of(15,2),1n);assert.equal(of(15,6),17n);assert.equal(of(15,10),1n);assert.match(trace(),/species:16:/);assert.equal(hero(11),BigInt(energy));}else assert.equal(result,L.ECMD_OK);}
for(const pm of [L.PM_GIANT_EEL,L.PM_ELECTRIC_EEL,L.PM_COCKATRICE])for(const water of [0,1,2])for(const poly of [0,1]){reset();call('hero',0,1);call('species',pm,poly);if(water===1)call('hero',19,1);if(water===2)call('hero',25,1);const result=act(6);if(pm!==L.PM_COCKATRICE&&water&&poly)assert.equal(result,L.ECMD_OK);}
// Command precedence: mounts, hiding, floor reach, holding and object surfaces.
reset();call('hero',16,1);assert.equal(act(1),L.ECMD_OK);assert.match(trace(),/already sitting/);
for(const pm of [L.PM_TRAPPER,L.PM_COCKATRICE]){reset();call('species',pm,1);call('hero',15,1);act(1);}
for(const swallowed of [0,1])for(const levitation of [0,1]){reset();call('option',5,0);call('hero',18,swallowed);if(levitation)call('prop',L.LEVITATION,0,1);assert.equal(act(1),L.ECMD_OK);}
for(const pm of [L.PM_HUMAN,L.PM_COCKATRICE])for(const gender of [0,1,2,3]){reset();call('hero',17,1);call('hero',26,pm);call('option',8,gender);assert.equal(act(1),L.ECMD_OK);assert.match(trace(),/lap/);if(pm===L.PM_HUMAN&&gender===3)assert.match(trace(),/their lap/);}
for(const pm of [L.PM_HUMAN,L.PM_RED_DRAGON])for(const item of [L.GOLD_PIECE,L.TOWEL,L.CORPSE,L.CREAM_PIE,L.LARGE_BOX,L.LONG_SWORD])for(const deaf of [0,1]){reset();call('species',pm,1);obj(0,item,3n,L.OBJ_FLOOR);call('obit',0,12,1);if(deaf)call('prop',L.DEAF,0,1);assert.equal(act(1),L.ECMD_TIME);if(item===L.CREAM_PIE)assert.equal(of(0,3),BigInt(L.OBJ_DELETED));}
// The overflowing sum case records the pinned Wasm result, not portable C.
for(const [floorGold,carriedGold,meager] of [[9999n,0n,true],[10000n,0n,false],[1n,(1n<<53n)+1n,false],[(1n<<63n)-1n,1n,true]]){reset();call('species',L.PM_RED_DRAGON,1);obj(0,L.GOLD_PIECE,floorGold,L.OBJ_FLOOR);obj(1,L.GOLD_PIECE,carriedGold);inventory([1]);call('obit',0,12,1);act(1);assert.equal(trace().includes('meager hoard'),meager);}
for(const roleplayDeaf of [0,1]){reset();obj(0,L.CREAM_PIE,2n,L.OBJ_FLOOR);call('obit',0,12,1);call('hero',28,roleplayDeaf);act(1);assert.equal(prop(L.DEAF),0n);assert.equal(trace().includes('Squelch!'),!roleplayDeaf);assert.equal(of(0,3),BigInt(L.OBJ_DELETED));}
// Trap branches and their nested RNG draw ordering.
for(const type of [L.TT_BEARTRAP,L.TT_PIT,L.TT_WEB,L.TT_LAVA,L.TT_INFLOOR,L.TT_BURIEDBALL])for(const half of [0,1]){reset();call('trap',type===L.TT_PIT?L.SPIKED_PIT:L.BEAR_TRAP);call('hero',20,3);call('hero',21,type);if(half)call('prop',L.HALF_PHDAM,0,1);call('prop',L.SLIMED,0,10);rng(Array(20).fill(1));assert.equal(act(1),L.ECMD_TIME);assert.ok(hero(17)>=3n);}
reset();call('trap',L.BEAR_TRAP);act(1);assert.match(trace(),/dotrap:/);
// Terrain surfaces, resistances and gremlin splitting preserve source precedence.
for(const typ of [L.ROOM,L.POOL,L.SINK,L.ALTAR,L.GRAVE,L.STAIRS,L.LADDER,L.LAVAPOOL,L.ICE,L.DRAWBRIDGE_DOWN,L.THRONE])for(const resist of [0,1]){reset();call('terrain',10,10,typ,0);if(resist){call('prop',L.FIRE_RES,0,1);call('prop',L.COLD_RES,0,1);}rng(Array(30).fill(1));assert.equal(act(1),L.ECMD_TIME);}
for(const water of [0,1]){reset();call('hero',water?25:19,1);act(1);assert.match(trace(),water?/no cushions/:/muddy bottom/);}
for(const fountain of [0,1])for(const split of [0,1]){reset();call('species',L.PM_GREMLIN,1);call('terrain',10,10,fountain?L.FOUNTAIN:L.POOL,0);call('option',9,split);act(1);assert.match(trace(),/split:/);if(fountain&&split)assert.equal(cell()[2],L.ROOM);}
reset();obj(0,L.LEATHER_ARMOR);obj(1,L.LOW_BOOTS);call('obit',0,10,1);call('obit',1,11,1);call('terrain',10,10,L.POOL,0);rng([0,0]);act(1);assert.equal((trace().match(/water-damage:1:armor:1/g)||[]).length,2);
reset();call('species',L.PM_COCKATRICE,1);call('hero',0,1);assert.equal(act(1),L.ECMD_TIME);assert.match(trace(),/an egg/);
// Curse selection excludes coins and handles blessed, cursed and intelligent items.
for(const antimagic of [0,1])for(const halfspell of [0,1])for(const status of [0,1,2,3]){reset();obj(0,L.GOLD_PIECE,100n);obj(1,L.LONG_SWORD);inventory([0,1]);if(status===1)call('obit',1,1,1);if(status===2)call('obit',1,3,1);if(status===3){call('obit',1,5,1);call('option',11,1);}if(antimagic)call('prop',L.ANTIMAGIC,0,1);if(halfspell)call('prop',L.HALF_SPDAM,0,1);rng([0,0,0,0,0,0]);act(2);assert.equal(of(0,11),0n);if(status===1)assert.equal(of(1,9),0n);if(status===0)assert.equal(of(1,11),1n);if(status===3)assert.match(trace(),/resist/);}
for(const magicbane of [0,1]){reset();call('option',10,magicbane);rng([1]);act(2);assert.equal(trace().includes('magic-absorbing blade'),Boolean(magicbane));}
for(const blind of [0,1])for(const hallu of [0,1])for(const blessed of [0,1]){reset();obj(14,L.SADDLE);call('hero',16,1);call('option',12,1);call('obit',14,1,blessed);if(blind)call('prop',L.BLINDED,0,1);if(hallu)call('prop',L.HALLUC,0,1);rng([0,0]);act(2);assert.equal(of(14,12),blind||hallu?0n:1n);}
// Every intrinsic entry and all fallthrough starts preserve unrelated property bits.
const properties=[L.FIRE_RES,L.TELEPORT,L.POISON_RES,L.TELEPAT,L.COLD_RES,L.INVIS,L.SEE_INVIS,L.FAST,L.STEALTH,L.PROTECTION,L.AGGRAVATE_MONSTER],extra=(1n<<55n)|17n;
for(let target=0;target<properties.length;target++)for(let start=0;start<11;start++){reset();call('prop',properties[target],0,BigInt(L.INTRINSIC)|extra);call('prop',L.BLINDED,0,1);rng([start]);const removed=act(3);if(start<=target){assert.equal(removed,properties[target]);assert.equal(prop(properties[target]),extra);}else{assert.equal(removed,0);assert.equal(prop(properties[target]),BigInt(L.INTRINSIC)|extra);}}
for(const property of [L.TELEPAT,L.SEE_INVIS])for(const backup of [0,1])for(const halluc of [0,1]){reset();call('prop',property,0,L.INTRINSIC);call('prop',property,1,backup);call('prop',L.BLINDED,0,1);if(halluc)call('prop',L.HALLUC,0,1);rng([properties.indexOf(property)]);assert.equal(act(3),property);assert.equal(trace().includes('see-monsters;'),!backup);if(property===L.SEE_INVIS)assert.equal(trace().includes('mimic-block;'),!backup);}
reset();for(const property of properties)call('prop',property,0,L.INTRINSIC);rng([0]);assert.equal(act(3),L.FIRE_RES);assert.ok(prop(L.TELEPORT)&BigInt(L.INTRINSIC));
reset();call('option',0,0);rng([0]);act(3);const saved=snapshot(modules[0]);modules[1]._probe_hero(7,-9n);assert.deepEqual(snapshot(modules[0]),saved);reset();
console.log(`SIT: ${comparisons} ${referenceLabel}/pure-JS throne, terrain, egg, property, curse and RNG-site comparisons checked.`);
