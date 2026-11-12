import {DataView,Int32Array,referenceBackend,referenceLabel,assertStackRestored,memoryCheckpoint,assertMemoryGrowth} from './native-test-backend.mjs';
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import referenceFactory from '../.cache/tu-probes/mkroom-reference.mjs';
import hybridFactory from '../.cache/tu-probes/mkroom-hybrid.mjs';
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
import {squadprob} from '../js/ported/mkroom.js';
import {C,R,T} from '../js/c-runtime/context.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),L=layouts.mkroom;
for(const key of ['roomSize','coordSize','COLNO','ROWNO','roomCount','ROOM','OROOM','COURT','ZOO','BEEHIVE','MORGUE','BARRACKS','LEPREHALL','COCKNEST','ANTHOLE','SWAMP','TEMPLE','SHOPBASE','A_NONE','NON_PM'])assert.ok(Number.isSafeInteger(L[key]),key);
const modules=[await referenceBackend('mkroom',referenceFactory)(),await hybridFactory({nethackPorted:createPortedRuntime(layouts)})];
const stacks=modules.map(m=>m._probe_stack());let comparisons=0,ioHeader=0;
function text(m,p){let end=Number(p);while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(Number(p),end)).toString();}
function bytes(m,p,n){return Buffer.from(m.HEAPU8.slice(Number(p),Number(p)+Number(n)));}
const pointerMaps=modules.map(m=>{const map=new Map([[0n,0n]]);for(let sub=0;sub<2;sub++)for(let i=0;i<L.roomCount;i++)map.set(BigInt(m._probe_pointer(sub?1:0,i)),BigInt(100+sub*1000+i));for(let i=0;i<128;i++)map.set(BigInt(m._probe_pointer(7,i)),BigInt(10000+i));return map;});
function normalizeRoomPointers(m,b,start=0){const map=pointerMaps[modules.indexOf(m)];for(const off of [L.room_resident,...Array.from({length:L.subroomCapacity},(_,i)=>L.room_sbrooms+i*8)]){const raw=b.readBigUInt64LE(start+off);b.writeBigUInt64LE(map.get(raw)??raw,start+off);}return b;}
function roomBytes(m,sub,index){return normalizeRoomPointers(m,bytes(m,m._probe_pointer(sub?1:0,index),L.roomSize));}
function normalizedIO(m){const b=bytes(m,m._probe_pointer(5,0),m._probe_io_length());for(let at=ioHeader;at+L.roomSize<=b.length;at+=L.roomSize)normalizeRoomPointers(m,b,at);return b;}
function snapshot(m){return {rooms:Array.from({length:5},(_,i)=>roomBytes(m,0,i)),subrooms:Array.from({length:5},(_,i)=>roomBytes(m,1,i)),terrain:bytes(m,m._probe_pointer(4,0),L.COLNO*L.ROWNO*L.terrainSize),counts:[0,1,2,3].map(i=>m._probe_count(i)),flags:m._probe_level_flags(),rng:[m._probe_rng_count(),m._probe_rng_state()>>>0],trace:text(m,m._probe_trace()),items:Array.from({length:m._probe_count(3)},(_,i)=>[0,1,2,3,4].map(k=>m._probe_item(i,k))),monsters:Array.from({length:m._probe_count(2)},(_,i)=>[0,1,2,3,4].map(k=>m._probe_monster_field(i,k))),io:normalizedIO(m),position:m._probe_io_position()};}
function state(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m,stacks[i]));comparisons++;}
function call(name,...args){const values=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(values[1],values[0],name+'('+args+')');state();comparisons++;return values[0];}
function reset(seed=123){ioHeader=0;call('reset',seed);}
function room(index=0,lx=5,ly=4,hx=9,hy=8,type=L.OROOM,irregular=0,doors=1){call('room',index,lx,ly,hx,hy,type,irregular,doors);}
function rng(values){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});state();}
function shop(value){modules.forEach(m=>{if(value===null)m._probe_shoptype(0n);else{const b=Buffer.from(value),p=m._malloc(BigInt(b.length+1));m.HEAPU8.set(b,Number(p));m.HEAPU8[Number(p)+b.length]=0;m._probe_shoptype(BigInt(p));m._free(BigInt(p));}});state();}
function act(op,a=0,b=0,c=0){if(op===25)ioHeader=4;return call('action',op,a,b,c);}
for(let i=0;i<modules[0]._probe_layout_count();i++){const k=text(modules[0],modules[0]._probe_layout_name(i));const raw=modules[0]._probe_layout_value(i);const value=L[k]<0?Number(BigInt.asIntN(64,raw)):Number(raw);assert.equal(value,L[k],k);comparisons++;}
for(let i=0;i<4;i++){assert.equal(modules[0]._probe_table(i,0),L[squadprob[i].pm]);assert.equal(modules[0]._probe_table(i,1),squadprob[i].prob);comparisons+=2;}
// All thirty original function entries, small-room boundaries and special types.
for(const dims of [[5,4,8,7],[5,4,9,8],[2,2,12,8]]){reset();room(0,...dims);act(0);act(16);act(17);for(const xy of [[1,1],[5,4],[8,8],[13,9]])act(18,0,...xy);}
for(const strict of [0,1,128,255]){reset();room();room(1,15,4,18,8);call('stair',0,6,5,1);rng([0,1,2,3]);act(3,strict);act(14);act(15);}
for(const type of [L.COURT,L.ZOO,L.BEEHIVE,L.MORGUE,L.BARRACKS,L.SWAMP,L.LEPREHALL,L.COCKNEST,L.ANTHOLE,L.TEMPLE,L.SHOPBASE,99]){reset();room(0,5,4,7,6);call('grid',L.ROOM,L.ROOMOFFSET);act(1,type);}
for(const choice of [null,'/','+','g','v','z','m','b','t','s','a','c','l','_','}','?']){reset();room(0,5,4,7,6);call('grid',L.ROOM,L.ROOMOFFSET);shop(choice);rng(Array(128).fill(2));act(2);}
// One-square trap at the shop entrance, then a normal branching room.
reset();room(0,5,4,6,4);call('cell',5,4,L.ROOM,L.ROOMOFFSET,0);act(29);reset();room();call('grid',L.ROOM,L.ROOMOFFSET);act(29);
for(const type of [L.COURT,L.ZOO,L.LEPREHALL,L.BEEHIVE,L.MORGUE,L.BARRACKS,L.COCKNEST,L.ANTHOLE])for(const fail of [0,1]){reset();room(0,5,4,7,6,type);call('grid',L.ROOM,L.ROOMOFFSET);call('option',2,fail);rng(Array(512).fill(1));act(6);}
// Existing throne skips fallback placement; irregular hive relocates its queen.
reset();room(0,5,4,7,6,L.COURT);call('grid',L.ROOM,L.ROOMOFFSET);call('maze',1);call('cell',6,5,L.THRONE,L.ROOMOFFSET,0);act(6);
reset();room(0,5,4,7,6,L.BEEHIVE,1);call('grid',L.ROOM,L.ROOMOFFSET);call('cell',6,5,L.ROOM,0,1);act(6);
for(const rolls of [[0,0],[19,0],[39,0],[90,11],[0,11]]){reset();rng(rolls);act(8);}
for(const value of [0n,1n,2n,-1n,9007199254740993n,9223372036854775807n]){reset();call('birth',value);act(9);}
for(const roll of [0,79,80,94,95,98,99]){reset();rng([roll,3]);act(23);}reset();call('vital',L.PM_SOLDIER,L.G_GONE);rng([0]);act(23);
for(const rolls of [[0,0],[59,100],[20,20],[30,30],[40,40]]){reset();rng(rolls);act(22);}
for(const revive of [0,1])for(const found of [0,1])for(const alive of [0,1]){reset();call('option',7,found);call('option',8,alive);rng(Array(64).fill(0));act(7,8,revive,0x1234);}
reset();room(0,5,4,7,6);call('grid',L.ROOM,L.ROOMOFFSET);act(10);act(5,6,7);
for(const n of [0,1,2,3]){reset();room(0,5,4,5+n,4+n);rng([0,1]);act(11,L.ROOMOFFSET);act(12);}
reset();room();call('cell',6,5,L.DOOR,L.ROOMOFFSET,0);act(13,5,5);act(13,0,0);
for(const irregular of [0,1]){reset();room(0,5,4,7,6,L.OROOM,irregular);call('grid',L.ROOM,L.ROOMOFFSET);act(19);act(20);}
reset();room(0,5,4,9,8);call('subroom',0,0,5,4,9,8);rng(Array(512).fill(0));act(19);act(20);
reset();room(0,5,4,7,6,L.TEMPLE);act(21,L.ANY_TYPE);act(21,L.ANY_SHOP);act(4,L.ZOO);
// Recursive raw-room serialization reconstructs subroom links and sentinels.
reset();room(0,5,4,9,8,L.COURT);room(1,15,4,19,8,L.TEMPLE);call('subroom',0,0,6,5,7,6);call('subroom',1,1,16,5,17,6);act(25);call('rewind');call('poison_rooms');act(27);
reset();room();act(24);call('rewind');act(26);
// Native serialization can mutate the exact addressable global count.
reset();room();room(1,15,4,18,7);call('option',14,2);act(25);
assert.equal(modules[1]._probe_count(0),1);
// The retained altar view must survive real allocation/growth in priestini.
reset();room(0,5,4,7,6);call('grid',L.ROOM,L.ROOMOFFSET);call('option',15,1);
const beforeGrowth=modules.map(memoryCheckpoint);act(12);
modules.forEach((m,i)=>assertMemoryGrowth(m,beforeGrowth[i]));
for(let sym=-2;sym<=160;sym++)act(28,sym);
console.log(`MKROOM: ${comparisons} ${referenceLabel}/hybrid room generation, geometry, selection, serialization and RNG comparisons checked.`);
