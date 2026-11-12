import './pure-js-probes/deny-wasm.mjs';
import { Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('fountain', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/fountain-reference.mjs';
import createGeneratedProbe from './pure-js-fixtures/runtime.mjs';
const hybridFactory=options=>createGeneratedProbe('fountain',options);
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
import {C,R,T} from '../js/c-runtime/context.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),L=layouts.fountain,runtime=createPortedRuntime(layouts),modules=[await referenceFactory(),await hybridFactory({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function text(m,p){p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');}
function snapshot(m){return {state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),count:m._probe_rng_count(),rng:m._probe_rng_state()>>>0};}
function state(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m, stacks[i]));comparisons++;}
const longs={obj:[2],obit:[2],hero:[1],prop:[2]};
function call(name,...args){args=args.map((v,i)=>longs[name]?.includes(i)?BigInt(v):v);const out=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(out[1],out[0],`${name}(${args})`);state();comparisons++;return out[0];}
function reset(seed=1){call('reset',seed);}
function rng(values){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});state();}
function act(op,a=0,b=0,c=0){return call('action',op,a,b,c);}
function obj(i,type,q=1n,where=L.OBJ_INVENT){call('obj',i,type,q,where);}
function inventory(indices){indices.forEach((v,i)=>call('next',v,indices[i+1]??-1));call('inventory',indices[0]??-1);}
function trace(){return text(modules[0],modules[0]._probe_trace());}
function fields(key){return text(modules[0],modules[0]._probe_snapshot()).split(';').find(s=>s.startsWith(key+':')).split(':').slice(1);}
function hero(i){return BigInt(fields('hero')[i]);}
function of(i,f){return BigInt(fields('o'+i)[f]);}
function mf(i,f){return BigInt(fields('m'+i)[f]);}
function prop(i,f=0){return BigInt(fields('p'+i)[f]);}
function cell(x=10,y=10){return fields('map').join(':').split('/').filter(Boolean).map(s=>s.split(',').map(Number)).find(v=>v[0]===x&&v[1]===y);}
function fate(n,tail=[]){rng([n-1,...tail,...Array(80).fill(1)]);}
function gushArea(){for(const [i,x,y] of [[0,12,12],[1,14,12],[2,12,14]]){call('area',i,x,y);call('terrain',x,y,L.ROOM,31,0);}}
reset();for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const k=text(m,m._probe_layout_name(i));assert.equal(Number(BigInt.asIntN(64,m._probe_layout_value(i))),L[k],k);}
for(const key of ['FOUNTAIN','SINK','ROOM','POOL','OBJ_INVENT','OBJ_FLOOR','OBJ_DELETED','GOLD_PIECE','LONG_SWORD','POT_HEALING','PM_WATCHMAN','PM_WATER_DEMON','PM_WATER_NYMPH','PM_WATER_MOCCASIN','A_LAWFUL','ER_NOTHING','ER_DESTROYED','ER_GREASED'])assert.ok(Number.isSafeInteger(L[key]),key);
// Floating above water still distinguishes floor/lava entrapment.
for(const trapped of [0,1])for(const type of [L.TT_INFLOOR,L.TT_LAVA,L.TT_PIT])for(const what of [0,1,2]){reset();call('hero',0,trapped);call('hero',1,type);act(0,what);assert.equal(trace().includes('are trapped'),Boolean(trapped&&(type===L.TT_INFLOOR||type===L.TT_LAVA)));}
// Every summoning branch uses actual initialized monster records.
for(const kind of [1,2,3])for(const gone of [0,1])for(const fail of [0,1])for(const blind of [0,1]){reset(5);const pm={1:L.PM_WATER_MOCCASIN,2:L.PM_WATER_DEMON,3:L.PM_WATER_NYMPH}[kind];call('vital',pm,gone?L.G_GONE:0);call('option',1,fail);call('trap',L.PIT);if(blind)call('prop',L.BLINDED,0,1);rng([0,0,0,0,0]);act(kind);if(!gone&&!fail){assert.match(trace(),/make:/);if(kind===3)assert.equal(mf(0,2),0n);}if(gone)assert.ok(!trace().includes('make:'));}
reset();call('prop',L.HALLUC,0,1);rng([0]);act(1);assert.match(trace(),/purple hippos/);
for(const difficulty of [0,19,20])for(const roll of [0,79,99])for(const gender of [0,1,2,3]){reset();call('option',4,difficulty);call('option',3,gender);call('trap',L.PIT);rng([roll]);act(2);const wished=roll+1>80+difficulty;assert.equal(trace().includes('grant:'),wished);if(wished)assert.equal(mf(0,1),0n);}
// Native callback pointer receives one shared madepool int across all points.
for(const drinking of [0,1,2]){reset();act(4,drinking);assert.equal(call('counter'),0);assert.match(trace(),drinking?/thirst is quenched/:/sprays all over/);reset();gushArea();rng(Array(12).fill(0));act(4,drinking);assert.equal(call('counter'),3);assert.equal((trace().match(/Water gushes forth/g)||[]).length,1);assert.match(trace(),/before:0;.*after:1;before:1;.*after:2;before:2;.*after:3;/);assert.equal(cell(12,12)[2],L.POOL);assert.equal(cell(12,12)[3],0);}
for(const guard of ['odd','hero','random','terrain','boulder','door','trap']){reset();call('terrain',12,12,L.ROOM,31,0);let x=12,y=12;if(guard==='odd')x=13;if(guard==='hero')x=y=10;if(guard==='random')rng([1]);else rng([0]);if(guard==='terrain')call('terrain',12,12,L.SINK,1,0);if(guard==='boulder')call('option',5,1);if(guard==='door')call('option',6,1);if(guard==='trap'){call('trap',L.PIT);call('option',7,0);}act(5,x,y);assert.equal(call('counter'),0);}
reset();call('terrain',12,12,L.ROOM,31,0);obj(0,L.LONG_SWORD,1n,L.OBJ_FLOOR);call('obit',0,10,1);call('mbit',0,3,1);call('trap',L.PIT);rng([0]);act(5,12,12);assert.equal(call('counter'),1);assert.match(trace(),/deltrap:.*water-chain:1:1;liquid:1;/);assert.equal(mf(0,1),19n);
reset();gushArea();call('prop',L.GLIB,0,123);call('option',28,1);call('option',29,1);rng(Array(20).fill(0));const before=modules.map(m=>allocationMetric(m));act(4,1);modules.forEach((m,i)=>assert.ok(allocationMetric(m)>before[i]));assert.equal(call('counter'),3);assert.equal(prop(L.GLIB),0n);assert.match(trace(),/nested-wash:.*grew;/);
// Gem loot flag and watch warnings, including deaf/group pronouns.
for(const blind of [0,1]){reset();if(blind)call('prop',L.BLINDED,0,1);act(6);assert.equal(of(22,3),BigInt(L.OBJ_FLOOR));assert.ok(cell()[4]&L.F_LOOTED);}
for(const watch of [0,1])for(const peaceful of [0,1])for(const visible of [0,1])for(const deaf of [0,1]){reset();call('mon',0,watch?L.PM_WATCHMAN:L.PM_HUMAN);call('mbit',0,1,peaceful);call('option',22,visible);if(deaf)call('hero',8,1);call('option',3,3);assert.equal(act(7,0),watch&&peaceful&&visible?1:0);if(watch&&peaceful&&visible&&deaf)assert.match(trace(),/their arms/);}
for(const warned of [0,1])for(const town of [0,1])for(const isyou of [0,1,256]){reset();call('terrain',10,10,L.FOUNTAIN,warned?L.F_WARNED:0,1);call('option',9,town);rng([0]);act(8,10,10,isyou);if(town&&(isyou&255)&&!warned){assert.equal(cell()[2],L.FOUNTAIN);assert.ok(cell()[3]&L.F_WARNED);}else{assert.equal(cell()[2],L.ROOM);assert.equal(cell()[5],0);}}
reset();call('option',9,1);call('mon',0,L.PM_WATCHMAN);rng([0]);act(8,10,10,1);assert.match(trace(),/iterate-watch;.*stop using/);
for(const answer of ['y','n'])for(const cloud of [0,1]){reset();call('hero',7,1);call('option',10,answer.charCodeAt(0));call('option',11,cloud);rng([0]);act(8,10,10,1);assert.equal(cell()[2],answer==='y'?L.ROOM:L.FOUNTAIN);if(cloud&&answer==='y')assert.ok(!trace().includes('fountain dries up!'));}
// All30 drinking fates, fresh and looted gems, magic luck and resistance.
for(let n=1;n<=30;n++){reset(41);obj(0,L.LONG_SWORD);obj(1,L.GOLD_PIECE,100n);inventory([0,1]);gushArea();fate(n);act(9);if(n===19)assert.match(trace(),/enlighten:/);if(n===20)assert.match(trace(),/vomit;/);if(n===21)assert.match(trace(),/poison:/);if(n===25)assert.ok(prop(L.SEE_INVIS)&BigInt(L.FROMOUTSIDE));if(n===27)assert.ok(cell()[4]&L.F_LOOTED);if(n===29)assert.equal((trace().match(/flee:/g)||[]).length,8);}
for(const luck of [-1,0,3,4,10])for(const roll of [1,9,10,30])for(const fail of [0,1]){reset();call('terrain',10,10,L.FOUNTAIN,0,1);call('hero',2,luck);call('option',12,fail);fate(roll);act(9);if(luck>=0&&roll>=10){assert.equal(cell()[5],0);assert.match(trace(),/makes you feel great/);if(luck<4&&!fail)assert.equal((trace().match(/attribute:/g)||[]).length,1);else assert.equal((trace().match(/attribute:/g)||[]).length,6);}if(roll<10)assert.equal(cell()[2],L.FOUNTAIN);}
reset();call('prop',L.LEVITATION,0,1);fate(30);act(9);assert.equal(call('rng_count'),1);assert.match(trace(),/floating/);
for(const poison of [0,1]){reset();if(poison)call('prop',L.POISON_RES,0,1);fate(21);act(9);assert.equal(trace().includes('poison:'),!poison);}
for(const blind of [0,1])for(const invisible of [0,1]){reset();if(blind)call('prop',L.BLINDED,0,1);if(invisible)call('prop',L.INVIS,0,1);fate(25);act(9);assert.ok(prop(L.SEE_INVIS)&BigInt(L.FROMOUTSIDE));}
reset();call('terrain',10,10,L.FOUNTAIN,L.F_LOOTED,0);fate(27);act(9);assert.match(trace(),/attract/);
reset();obj(0,L.LONG_SWORD);obj(1,L.LONG_SWORD);obj(2,L.GOLD_PIECE,20n);inventory([0,1,2]);call('prop',L.GLIB,0,77);call('option',28,1);call('option',29,1);fate(24,[0,0,0,1]);act(9);assert.equal(of(0,5),1n);assert.equal(of(1,5),1n);assert.equal(of(2,5),0n);assert.equal(prop(L.GLIB),0n);assert.match(trace(),/grew;/);
// Excalibur, replacement returned pointers, alignment denial and early guards.
for(const align of [L.A_LAWFUL,L.A_NEUTRAL,L.A_CHAOTIC])for(const knight of [0,1])for(const replacement of [0,1])for(const female of [0,1]){reset();obj(0,L.LONG_SWORD);inventory([0]);call('obit',0,3,2);call('obit',0,4,3);call('obit',0,2,1);call('hero',4,align);call('hero',5,knight?L.PM_KNIGHT:L.PM_HUMAN);call('hero',6,female);call('option',15,replacement);rng([0,0]);act(10,0);assert.equal(cell()[2],L.ROOM);if(align===L.A_LAWFUL){const target=replacement?23:0;assert.equal(of(target,11),BigInt(L.ART_EXCALIBUR));assert.equal(of(target,6),1n);assert.equal(of(target,8),0n);assert.equal(of(target,9),0n);assert.equal(of(target,7),1n);}else{assert.equal(of(0,5),1n);assert.equal(of(0,7),0n);assert.equal(of(0,12),-1n);}}
for(const quantity of [2n,(1n<<53n)+1n]){reset();obj(0,L.LONG_SWORD,quantity);rng([0,0]);act(10,0);assert.ok(!trace().includes('oname:'));}
reset();obj(0,L.LONG_SWORD);call('option',14,1);rng([0,0]);act(10,0);assert.ok(!trace().includes('oname:'));
reset();obj(0,L.LONG_SWORD);call('prop',L.LEVITATION,0,1);act(10,0);assert.equal(call('rng_count'),0);
// Generic dipping branches use ordinary objects to skip artifact RNG.
for(let n=1;n<=30;n++)for(const cursed of [0,1]){reset(57);obj(0,L.LEATHER_GLOVES);call('obit',0,0,cursed);obj(1,L.GOLD_PIECE,100n);inventory([0,1]);gushArea();fate(n);act(10,0);if(n===16&&!cursed)assert.equal(of(0,5),1n);if(n>=17&&n<=20)assert.equal(of(0,5),0n);if(n===28)assert.equal(of(1,2),90n);}
for(const er of [L.ER_NOTHING,L.ER_DESTROYED,L.ER_GREASED])for(const stop of [0,1]){reset();obj(0,L.LEATHER_GLOVES);call('option',17,er);rng([stop,0,1]);act(10,0);if(er===L.ER_DESTROYED)assert.equal(call('rng_count'),0);}
for(const gloves of [0,1])for(const greasy of [0,1])for(const er of [L.ER_NOTHING,L.ER_GREASED,L.ER_DESTROYED]){reset();obj(0,L.LEATHER_GLOVES);if(gloves)call('obit',0,9,1);if(greasy)call('prop',L.GLIB,0,123);call('option',17,er);const result=act(11);assert.equal(prop(L.GLIB),0n);assert.equal(result,gloves?(greasy&&er===L.ER_NOTHING?L.ER_GREASED:er):greasy?L.ER_GREASED:L.ER_NOTHING);}
reset();call('prop',L.GLIB,0,1);fate(16);act(10,-1);assert.equal(prop(L.GLIB),0n);
// Sink conversion,20drinks, water rejection and potion lifecycle.
reset();call('terrain',10,10,L.SINK,31,1);act(12,10,10);assert.equal(cell()[2],L.FOUNTAIN);assert.equal(cell()[5],0);assert.ok(cell()[4]&L.F_LOOTED);
for(let fate=0;fate<20;fate++)for(const resist of [0,1]){reset();call('terrain',10,10,L.SINK,0,0);if(resist){call('prop',L.FIRE_RES,0,1);call('prop',L.UNCHANGING,0,1);}rng([fate,...Array(30).fill(1)]);act(13);if(fate===4){assert.match(trace(),/potion:22:2:0:0:1;free:22:0;/);assert.equal(of(21,2),1n);}if(fate===6)assert.equal(cell()[2],L.FOUNTAIN);if(fate===8)assert.equal(hero(8),1n);if(fate===13)assert.match(trace(),/cloud:10:10:1:4/);}
reset();call('option',18,3);rng([4]);act(13);assert.equal((trace().match(/mkobj:/g)||[]).length,4);assert.equal((trace().match(/free:22:0/g)||[]).length,4);
for(const halluc of [0,1]){reset();if(halluc)call('prop',L.HALLUC,0,1);rng([19,0]);act(13);assert.equal(trace().includes('--oops--'),Boolean(halluc));}
for(const pm of [L.PM_SEWER_RAT,L.PM_WATER_ELEMENTAL]){reset();call('vital',pm,L.G_GONE);rng([pm===L.PM_SEWER_RAT?3:7]);act(13);assert.ok(!trace().includes('make:'));}
// All potion dip routes, blind/deaf knowledge and once-per-sink loot.
const potions=[L.POT_POLYMORPH,L.POT_OIL,L.POT_ACID,L.POT_LEVITATION,L.POT_OBJECT_DETECTION,L.POT_GAIN_LEVEL,L.POT_GAIN_ENERGY,L.POT_MONSTER_DETECTION,L.POT_FRUIT_JUICE,L.POT_WATER,L.POT_HEALING];
for(const potion of potions)for(const blind of [0,1])for(const deaf of [0,1])for(const looted of [0,1]){reset();call('terrain',10,10,L.SINK,looted?L.S_LRING:0,0);obj(0,potion,2n);if(blind)call('prop',L.BLINDED,0,1);if(deaf)call('hero',8,1);rng([1]);act(14,0);assert.equal(of(0,2),1n);assert.match(trace(),/useup:1/);if(potion===L.POT_POLYMORPH)assert.match(trace(),/poly-sink/);}
for(const hands of [0,1]){reset();call('terrain',10,10,L.SINK,0,0);call('prop',L.GLIB,0,12);obj(0,L.LEATHER_GLOVES);if(!hands)call('obit',0,9,1);rng([0]);act(14,hands?-1:0);assert.equal(cell()[2],L.FOUNTAIN);assert.equal(prop(L.GLIB),12n);assert.match(trace(),/still slippery/);}
reset();obj(0,L.LEATHER_GLOVES);rng([1]);act(14,0);assert.match(trace(),/hold the fixture item/);
for(const blind of [0,1])for(const deaf of [0,1])for(const looted of [0,1]){reset();call('terrain',10,10,L.SINK,looted?L.S_LRING:0,0);if(blind)call('prop',L.BLINDED,0,1);if(deaf)call('hero',8,1);act(15,10,10);assert.ok(cell()[4]&L.S_LRING);assert.equal(trace().includes('mkobj-at:'),!looted);if(blind&&deaf)assert.match(trace(),/splashes you in the face/);}
reset();call('option',0,0);rng([1]);act(13);const saved=snapshot(modules[0]);modules[1]._probe_hero(2,-3n);assert.deepEqual(snapshot(modules[0]),saved);reset();
console.log(`FOUNTAIN: ${comparisons} ${referenceLabel}/pure-JS fountain, sink, callback, property, inventory and RNG-site comparisons checked.`);
