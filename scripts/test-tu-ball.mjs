import { DataView, Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('ball', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/ball-reference.mjs';
import hybridFactory from '../.cache/tu-probes/ball-hybrid.mjs';
import {createPortedRuntime} from '../js/ported/wasm-runtime.js';
import {C,R,T} from '../js/ported/c-runtime.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),L=layouts.ball,runtime=createPortedRuntime(layouts);
const modules=[await referenceFactory(),await hybridFactory({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
const text=(m,p)=>{p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');};
const snapshot=m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),rng:m._probe_rng_state()>>>0,count:m._probe_rng_count()});
function check(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m, stacks[i]));comparisons++;}
function call(name,...args){const arg={object:2,hero:1,prop:2}[name];if(arg!==undefined)args[arg]=BigInt(args[arg]);const v=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(v[1],v[0],name+':'+args);comparisons++;check();return v[0];}
const reset=(seed=1)=>call('reset',seed),opt=(k,v)=>call('option',k,v),hero=(k,v)=>call('hero',k,v),obj=(i,k,v)=>call('object',i,k,v),prop=(p,k,v)=>call('prop',p,k,v),equip=(k,v)=>call('equip',k,v),floor=(o,bx,by,cx,cy)=>call('setup_floor',o,bx,by,cx,cy);
const act=(op,a=0,b=0,c=0,d=0,e=0,f=0)=>Number(call('action',op,a,b,c,d,e,f));
const trace=()=>text(modules[0],modules[0]._probe_trace()),state=()=>text(modules[0],modules[0]._probe_snapshot());
function rng(values){for(const m of modules){new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);}check();}
function out(){const m=modules[0],p=Number(m._probe_pointer(2,0)),v=new DataView(m.HEAPU8.buffer);return {control:v.getInt32(p,true),coords:Array.from({length:4},(_,i)=>v.getInt16(p+4+2*i,true)),delay:v.getInt8(p+12)};}
function terrain(x,y,k,v){call('terrain',x,y,k,v);}
reset();for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const k=text(m,m._probe_layout_name(i)),v=m._probe_layout_value(i);assert.equal(typeof L[k]==='string'?BigInt.asUintN(64,v).toString():Number(BigInt.asIntN(64,v)),L[k],k);}
for(const k of ['OBJ_FREE','OBJ_INVENT','OBJ_FLOOR','HEAVY_IRON_BALL','IRON_CHAIN','ROOM','STONE','DOOR','D_LOCKED','POOL','MOAT','BC_BALL','BC_CHAIN','BLINDED','LEVITATION','HALF_PHDAM','TT_PIT','TT_WEB','TT_LAVA','TT_BEARTRAP','TT_INFLOOR','TT_BURIEDBALL','PIT','HOLE','override_restriction'])assert.ok(Number.isSafeInteger(L[k]),k);

// Inventory release clears each equipped alias, while welded and floor balls retain their attachment.
for(const carried of [0,1])for(const welded of [0,1])for(const message of [-1,0,1,256,257]){reset();if(carried)call('add',0,L.OBJ_INVENT,10,10);for(let k=2;k<=4;k++)equip(k,0);opt(1,welded);act(0,message);if(carried&&!welded){assert.ok(state().includes('equip:0:1:-1:-1:-1:'));assert.ok(trace().includes('freeinv:0;'));}else assert.ok(!trace().includes('freeinv:0;'));}
for(const helmet of [0,1,2])for(const half of [0,1])for(const wielded of [0,1]){reset();obj(0,0,8);obj(0,1,9);if(helmet)equip(5,2);opt(2,helmet===2);if(half)prop(L.HALF_PHDAM,0,1);if(wielded)equip(2,0);rng([1,6]);act(1);assert.equal(trace().includes('hp:'),!wielded);if(!wielded&&helmet===2)assert.ok(trace().includes(`hp:${half?2:3}:`));}
reset();equip(0,-1);act(1);

// Native floor list order and all felt-glyph combinations.
for(const order of [1,2])for(const carried of [0,1])for(const swallowed of [0,1]){reset();if(carried){call('add',0,L.OBJ_INVENT,10,10);call('add',1,L.OBJ_FLOOR,10,10);}else floor(order,10,10,10,10);hero(6,swallowed);assert.equal(act(6),carried||swallowed?0:order);for(const blind of [0,1])act(7,blind);}
for(const carried of [0,1]){reset();if(carried)call('add',0,L.OBJ_INVENT,10,10);act(14);assert.equal(act(6),carried?0:1);act(15);assert.ok(state().includes(';floor:;'));}
for(const swallowed of [0,1])for(const water of [0,1]){reset();floor(1,10,10,10,10);hero(6,swallowed);if(water)hero(12,1);act(3);assert.equal(trace().includes('extract:'),!swallowed||!!water);}
reset();act(2);act(2);assert.ok(trace().includes('bc already placed'));act(3);rng([123]);const pin=act(4);assert.equal(pin,124);assert.equal(call('state',0,0),124);assert.equal(act(16,0),0);assert.equal(act(16,123),0);assert.equal(act(16,L.override_restriction),1);act(2);act(3);act(4);act(5,125);assert.equal(call('state',0,0),124);act(5,124);assert.equal(call('state',0,0),0);assert.equal(trace().includes('paniclog:'),!!L.config_DEVELOPMENT_LOG);
for(const blind of [0,1])for(const order of [0,1,2])for(const felt of [0,1,2,3])for(const control of [0,1,2,3]){reset();floor(order===2?2:1,10,10,order?10:11,10);hero(2,order);hero(3,felt);hero(4,901);hero(5,902);if(blind)prop(L.BLINDED,0,1);act(8,1,control,12,10,11,10);act(8,0,control,12,10,11,10);}

// Geometry matrices exercise the macro's rollback and shared drag tail, with independent delayed-motion expectations.
for(const dx of [-2,-1,0,1,2])for(const dy of [-2,-1,0,1,2])for(const rock of [0,1])for(const allow of [0,1]){reset();floor(1,8,8,9,9);hero(0,9);hero(1,9);if(rock)terrain(9,8,0,L.STONE);rng([1,0,1]);act(9,8+dx,8+dy,allow);assert.ok(out().control>=0&&out().control<=3);}
reset();floor(1,8,8,9,8);hero(0,10);hero(1,9);terrain(9,9,0,L.STONE);act(9,10,10,1);assert.equal(out().control,3);assert.equal(out().delay,1);assert.ok(trace().includes('place:1:9:8;')); // SKIP_TO_DRAG restores the chain first.
reset();floor(1,8,8,9,8);hero(0,15);hero(1,15);terrain(9,9,0,L.STONE);act(9,10,10,0);assert.deepEqual(out().coords,[10,10,10,10]);assert.equal(out().delay,1);
reset();floor(1,7,7,8,8);hero(0,9);hero(1,9);opt(3,5);assert.equal(act(9,10,10,1),0);assert.ok(trace().includes('cannot drag'));
for(const levitate of [0,1])for(const kill of [0,1])for(const hit of [0,1]){reset();floor(1,7,8,8,8);hero(0,9);hero(1,8);terrain(8,8,0,L.POOL);hero(14,8);hero(15,8);opt(6,hit?30:-30);opt(8,kill);if(levitate)prop(L.LEVITATION,0,1);rng([0]);const answer=act(9,10,8,1);assert.equal(answer,levitate?1:0);assert.equal(trace().includes('spot:1;'),!levitate);if(!levitate)assert.ok(trace().includes(hit?'hit:':'miss:'));}
for(const pit of [L.PIT,L.HOLE]){reset();floor(1,7,8,8,8);hero(0,8);hero(1,8);hero(13,pit);prop(L.LEVITATION,0,1);act(9,10,8,1);assert.ok(trace().includes('tug'));}

// Native door-mask packed bits exercise the same blocked midpoint rollback as solid rock.
for(const mask of [L.D_CLOSED,L.D_LOCKED,L.D_CLOSED|L.D_LOCKED]){reset();floor(1,8,8,9,8);hero(0,10);hero(1,9);terrain(9,9,0,L.DOOR);terrain(9,9,2,mask);act(9,10,10,1);assert.equal(out().control,3);assert.equal(out().delay,1);assert.ok(trace().includes('place:1:9:8;'));}

// All coordinate outputs may refer to one genuine coordxy cell; reads observe earlier writes.
for(const carried of [0,1]){reset();if(carried){call('add',0,L.OBJ_INVENT,10,10);call('add',1,L.OBJ_FLOOR,9,9);}else floor(1,8,8,9,9);opt(16,1);act(9,10,10,1);}

// Trap escape, movement, stair damage and litter traverse actual native object chains safely while deleting entries.
for(const kind of [L.TT_PIT,L.TT_WEB,L.TT_LAVA,L.TT_BEARTRAP,L.TT_INFLOOR,L.TT_BURIEDBALL])for(const blind of [0,1]){reset();floor(1,12,10,10,10);hero(7,3);hero(8,kind);hero(13,L.PIT);if(blind)prop(L.BLINDED,0,1);hero(3,3);rng([1,999]);act(10,12,10);if(kind!==L.TT_INFLOOR&&kind!==L.TT_BURIEDBALL)assert.ok(trace().includes('resettrap:1;'));assert.ok(trace().includes('mov:1:'));}
for(const forward of [0,1])for(const letgo of [0,1])for(const half of [0,1]){reset();call('add',0,L.OBJ_INVENT,10,10);call('add',2,L.OBJ_INVENT,10,10);call('add',3,L.OBJ_INVENT,10,10);obj(3,4,2n);obj(2,5,200);obj(3,5,200);opt(9,letgo);if(!forward)equip(2,2);if(half)prop(L.HALF_PHDAM,0,1);rng(forward?[1,5,0,0]:[1,1,0,0,2,0,0]);act(12);assert.ok(trace().includes('cls;'));if(!letgo)assert.ok(trace().includes('hitfloor:'));}
reset();call('add',2,L.OBJ_INVENT,10,10);obj(2,5,200);rng([0]);act(11);assert.ok(trace().includes('hitfloor:2:0;'));assert.ok(state().includes(';inv:;'));
for(const mask of [L.W_BALL,0,1n<<60n]){reset();floor(1,10,10,10,10);obj(0,3,mask);act(13);}
reset();equip(0,-1);act(13);assert.ok(trace().includes('without being Punished'));

// HALF_PHDAM is read before evaluating the chosen damage expression, whose RNG may change the property.
for(const initial of [0,1]){reset();call('add',0,L.OBJ_INVENT,10,10);prop(L.HALF_PHDAM,0,initial);opt(32,initial?-1:1);opt(33,2);rng([1,5]);act(12);assert.ok(trace().includes('fliphalf;'));assert.ok(trace().includes(`hp:${initial?3:6}:dragged downstairs`));}
reset();floor(1,10,10,10,10);hero(6,1);hero(17,0);act(3);assert.ok(!trace().includes('extract:'));

// Native callbacks can reenter JS and grow the heap without stale views or process-global state.
for(const stage of [1,2,3,4,5,6,7,8,9]){reset();opt(30,stage);opt(31,stage);const before=modules.map(m=>allocationMetric(m));if(stage<=2){call('add',0,L.OBJ_INVENT,10,10);equip(2,0);act(0,1);}else if(stage<=6){floor(1,10,10,10,10);act(3);act(2);}else if(stage===9){obj(0,0,8);rng([1,1]);act(1);}else{floor(1,7,8,8,8);hero(0,9);hero(1,8);terrain(8,8,0,L.POOL);if(stage===8){hero(14,8);hero(15,8);opt(6,30);}rng([0]);act(9,10,8,1);}assert.ok(trace().includes(`grow:${stage};`));assert.ok(trace().includes('nested;'));modules.forEach((m,i)=>assert.ok(allocationMetric(m)>before[i]));}
reset();opt(0,0);obj(0,0,8);rng([1,1]);act(1);assert.ok(trace().includes('@;'));
reset();floor(1,10,10,10,10);act(4);const held=snapshot(modules[1]);const other=await hybridFactory({nethackPorted:runtime});other._probe_reset(9);other._probe_action(2,0,0,0,0,0,0);assert.equal(other._probe_state(0,0),0);assert.equal(other._probe_action(6,0,0,0,0,0,0),1n);other._probe_action(4,0,0,0,0,0,0);assert.notEqual(other._probe_state(0,0),0);assert.deepEqual(snapshot(modules[1]),held);comparisons+=2;check();
console.log(`BALL ${referenceLabel}/hybrid differential: ${comparisons} comparisons checked`);
