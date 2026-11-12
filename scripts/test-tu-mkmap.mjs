import { Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('mkmap', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import { readFileSync } from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/mkmap-reference.mjs';
import hybridFactory from '../.cache/tu-probes/mkmap-hybrid.mjs';
import { createPortedRuntime } from '../js/backends/emscripten/runtime.js';
import { C, R, T } from '../js/c-runtime/context.js';
const layouts = JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json', import.meta.url)));
const layout = layouts.mkmap;
const modules = [await referenceFactory(), await hybridFactory({ nethackPorted: createPortedRuntime(layouts) })];
const stacks = modules.map(m => m._probe_stack());
let comparisons = 0;
function bytes(m, ptr, length) { const start = Number(ptr); if(length === undefined) { let end=start;while(m.HEAPU8[end])end++;length=end-start;}return Buffer.from(m.HEAPU8.slice(start,start+length)); }
function snapshot(m) {return {storage:Array.from({length:5},(_,i)=>bytes(m,m._probe_snapshot_pointer(i),Number(m._probe_snapshot_size(i)))),scalars:Array.from({length:7},(_,i)=>m._probe_scalar(i)),random:m._probe_rng_state()>>>0,count:m._probe_rng_count(),trace:bytes(m,m._probe_trace()).toString('hex')};}
function state() {assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m, stacks[i]));comparisons++;}
function call(name,...args) {const values=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(values[1],values[0],`${name}(${args})`);state();comparisons++;return values[0];}
function both(name,...args) {modules.forEach(m=>m['_probe_'+name](...args));}
function reset(seed=1){call('reset',seed);}
function rng(values){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});state();}
function rectangle(lx,ly,hx,hy,type,room=0,lit=0,edge=0,flags=0){for(let x=lx;x<=hx;x++)for(let y=ly;y<=hy;y++)both('cell',x,y,type,room,lit,edge,flags);}
function patterned(seed=1){reset(seed);let random=seed>>>0;for(let x=0;x<layout.COLNO;x++)for(let y=0;y<layout.ROWNO;y++){random=(Math.imul(random,1664525)+1013904223)>>>0;both('cell',x,y,(random>>>29)&1?layout.ROOM:layout.STONE,(x+y)%7,(x+y)&1,(x^y)&1,23);}state();}
reset();
for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const key=bytes(m,m._probe_layout_name(i)).toString();assert.equal(Number(m._probe_layout_value(i)),layout[key],key);}
// Initialization changes only its documented columns and bitfields.
patterned();call('init',layout.STONE);assert.equal(call('cell_field',0,0,4),23);
for(const x of [-32768,-1,0,1,2,layout.COLNO-2,layout.COLNO-1,32767])for(const y of [-1,0,1,layout.ROWNO-2,layout.ROWNO-1])call('get',x,y,layout.TREE);
for(const seed of [1,7,0xffffffff]){reset(seed);call('init',layout.STONE);call('fill',layout.STONE,layout.ROOM);let count=0;for(let x=1;x<layout.COLNO;x++)for(let y=0;y<layout.ROWNO;y++)count+=modules[0]._probe_cell_field(x,y,0)===layout.ROOM;assert.equal(count,Math.trunc((layout.COLNO-2)*(layout.ROWNO-1)*2/5));}
// Independent seeds and repeated passes catch in-place versus buffered updates,
// untouched boundary bytes, and transposed/aliased scratch-buffer rows.
for(const seed of [1,2,991])for(const pass of [1,2,3]){patterned(seed);call('pass',pass,layout.STONE,layout.ROOM);call('pass',pass,layout.STONE,layout.ROOM);}
// Diagonally connected regions exercise eight-way flood recursion.
for(const lit of [0,1,2,255])for(const any of [0,1]){
 reset();rectangle(3,3,5,5,layout.HWALL);rectangle(4,4,4,4,layout.ROOM);rectangle(5,5,5,5,layout.ROOM);rectangle(6,6,6,6,layout.ROOM);both('cell',3,4,layout.DOOR,9,1,0,17);call('bounds',4,4);call('flood',4,4,63,lit,any);
 assert.ok(call('scalar',2)>=3);assert.equal(call('cell_field',6,6,1),63);
}
// Edge columns and wide horizontal spans test left backup and upper/lower bounds.
reset();rectangle(1,0,layout.COLNO-2,0,layout.ROOM);rectangle(1,1,1,layout.ROWNO-1,layout.ROOM);call('bounds',5,0);call('flood',5,0,3,1,0);
// Cleanup resets counts/sentinels but retains all unrelated terrain flags.
patterned();call('counts',3,2);call('cleanup');assert.equal(call('scalar',0),0);assert.equal(call('scalar',1),0);assert.equal(call('cell_field',2,2,4),23);
// Distinct islands, tiny holes, failure fallback, and maximum temporary-room exit.
for(const fail of [0,1]){reset(9);call('options',1,fail,1);rectangle(3,2,5,4,layout.ROOM);rectangle(3,10,6,12,layout.ROOM);rectangle(12,4,15,6,layout.ROOM);rectangle(30,8,30,9,layout.ROOM);call('join',layout.STONE,layout.ROOM);assert.equal(call('cell_field',30,8,0),layout.STONE);assert.equal(call('scalar',0),0);}
// Reach the limit with a horizontal region: roomno has only six bits, so
// a wrapped room ID must not be revisited recursively in the original C.
reset(19);for(let n=0;n<2*layout.MAXNROFROOMS-1;n++)both('room',n,10,10,12,12,1);rectangle(2,1,5,1,layout.ROOM);call('join',layout.STONE,layout.ROOM);
// Full room structure copies are compared bytewise, including unrelated fields;
// only matching old room numbers inside the moved room are rewritten.
for(const index of [0,1,2]){reset();for(let n=0;n<3;n++){both('room',n,3+n*10,3,6+n*10,6,n&1);rectangle(3+n*10,3,6+n*10,6,layout.ROOM,n+layout.ROOMOFFSET);both('cell',4+n*10,4,layout.ROOM,42,1,1,17);}call('remove',index);assert.equal(call('scalar',0),2);}
for(const bounds of [[2,2,8,8],[4,4,8,8],[40,10,45,15]]){reset();both('room',0,3,3,6,6,0);both('room',1,20,3,25,6,1);call('remove_region',...bounds);}
// Lava lights unconditionally; ice pool/moat flags and tree/wall lighting retain
// unrelated rm flags.  Native wallify is a traced, controlled dependency.
for(const lit of [0,1,256,-1])for(const wall of [0,1])for(const ice of [0,1])for(const bg of [layout.STONE,layout.TREE]){
 reset();both('room',0,3,3,6,6,1);const types=[layout.ROOM,bg,layout.LAVAPOOL,layout.ICE,layout.HWALL,layout.CORR];types.forEach((type,i)=>both('cell',i+3,5,type,7,0,1,23));call('finish',layout.ROOM,bg,lit,wall,ice);assert.equal(call('cell_field',5,5,2),1);
}
for(const depth of [-128,-12,-1,0,1,12,127])for(const values of [[0,0],[10,1],[126,76]]){reset();call('options',1,0,depth);rng(values);call('lit',-1);}
for(const lit of [-2147483648,-2,0,1,2,127,128,255,256,257,2147483647]){reset();call('lit',lit);}
for(const seed of [1,991])for(const smooth of [0,1])for(const join of [0,1])for(const wall of [0,1]){reset(seed);call('make',layout.STONE,layout.ROOM,smooth,join,-1,wall,1);}
for(const [smooth,join,wall] of [[0,1,256],[256,256,1],[255,255,-1]]){reset(37);call('make',layout.STONE,layout.ROOM,smooth,join,256,wall,255);}
reset(17);call('options',0,0,1);call('lit',-1);call('init',layout.STONE);call('fill',layout.STONE,layout.ROOM);call('pass',2,layout.STONE,layout.ROOM);
reset(7);const isolated=snapshot(modules[0]);modules[1]._probe_init(layout.TREE);assert.deepEqual(snapshot(modules[0]),isolated);reset(7);
const grown=modules.map(m=>m._malloc(40n*1024n*1024n));assert.ok(grown.every(Boolean));call('init',layout.STONE);call('fill',layout.STONE,layout.ROOM);call('pass',2,layout.STONE,layout.ROOM);call('join',layout.STONE,layout.ROOM);modules.forEach((m,i)=>m._free(grown[i]));state();
console.log(`MKMAP: ${comparisons} ${referenceLabel}/hybrid terrain, scratch-buffer, flood, room-copy, lighting and RNG-site comparisons checked.`);
