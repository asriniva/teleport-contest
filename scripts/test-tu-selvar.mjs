import './pure-js-probes/deny-wasm.mjs';
import { Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('selvar', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/selvar-reference.mjs';
import createGeneratedProbe from './pure-js-fixtures/runtime.mjs';
const hybridFactory=options=>createGeneratedProbe('selvar',options);
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
import {C,R,T} from '../js/c-runtime/context.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),layout=layouts.selvar;
const runtime=createPortedRuntime(layouts),factoryServices=new Map(),originalSelvar=runtime.selvar;
runtime.selvar=(services,...args)=>{let seen=factoryServices.get(services.moduleKey);if(!seen)factoryServices.set(services.moduleKey,seen=new Set());seen.add(services);return originalSelvar(services,...args);};
const modules=[await referenceFactory(),await hybridFactory({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function bytes(m,p,n){p=Number(p);if(!p)return null;return Buffer.from(m.HEAPU8.slice(p,p+n));}
function text(m,p){let a=Number(p),e=a;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(a,e));}
function snapshot(m){return {slots:Array.from({length:8},(_,i)=>({exists:m._probe_pointer(i)!==0n,fields:Array.from({length:7},(_,f)=>m._probe_field(i,f)),map:bytes(m,m._probe_map(i),layout.COLNO*layout.ROWNO+1)})),rect:bytes(m,m._probe_rect(),Number(m._probe_rect_size())),coords:[m._probe_coord(0),m._probe_coord(1)],description:bytes(m,m._probe_description_pointer(),Number(m._probe_description_size())),random:m._probe_rng_state()>>>0,count:m._probe_rng_count(),trace:text(m,m._probe_trace()).toString('hex')};}
function state(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));const ref=modules[0]._probe_callback_identity(),raw=BigInt(runtime.selvarState.selection_flood_check_func);assert.equal(raw===0n?0:raw===modules[1]._probe_callback_pointer(1)?1:raw===modules[1]._probe_callback_pointer(2)?2:99,ref);assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m, stacks[i]));comparisons++;}
function call(name,...args){const result=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(result[1],result[0],`${name}(${args})`);state();comparisons++;return result[0];}
function both(name,...args){modules.forEach(m=>m['_probe_'+name](...args));}
function reset(seed=1){call('reset',seed);}
function fresh(seed=1){reset(seed);call('new',0);}
function rng(values){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});state();}
function rect(lx,ly,hx,hy,value=1,slot=0){for(let x=lx;x<=hx;x++)for(let y=ly;y<=hy;y++)both('set',slot,x,y,value);state();}
function terrain(lx,ly,hx,hy,checker=false){for(let x=lx;x<=hx;x++)for(let y=ly;y<=hy;y++)both('cell',x,y,checker&&((x+y)&1)?layout.STONE:layout.ROOM,(x+y)&1,0,0);state();}
function selected(m,slot=0){const map=bytes(m,m._probe_map(slot),layout.COLNO*layout.ROWNO);return map?Array.from(map).filter(v=>v!==1).length:0;}
reset();for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const key=text(m,m._probe_layout_name(i)).toString();assert.equal(Number(BigInt.asIntN(64,m._probe_layout_value(i))),layout[key],key);}
for(const key of ['ROOM','STONE','COLNO','ROWNO','selectionSize','sel_map','SEL_GRADIENT_RADIAL','SEL_GRADIENT_SQUARE'])assert.ok(Number.isSafeInteger(layout[key]),key);
call('set',-1,1,1,1);assert.equal(call('get',-1,1,1),0);call('bounds',-1,0);call('bounds',-1,1);call('grow',-1,0);call('ellipse',-1,0,0,0,0,0);call('iterate',-1,0);call('filter',-1,1,50);call('mapfilter',-1,2,0,-2);call('free',3,1);
fresh();assert.equal(selected(modules[0]),0);assert.equal(call('get',0,0,0),0);call('set',0,0,0,0);assert.equal(call('field',0,2),1);call('bounds',0,0);call('recalc',0);
for(const val of [-257,-256,-129,-128,-1,0,1,2,126,127,128,254,255,256,257,2147483647,-2147483648]){fresh();call('clear',0,val);call('get',0,2,3);call('set',0,4,5,val);call('get',0,4,5);call('bounds',0,0);}
for(const x of [-32768,-1,0,1,79,80,32767,65536])for(const y of [-1,0,20,21]){fresh();call('set',0,x,y,1);call('get',0,x,y);call('bounds',0,0);}
// A copied struct must preserve padding bytes as well as all defined fields.
fresh();rect(2,3,4,5);modules.forEach(m=>{const p=Number(m._probe_pointer(0)),defined=new Set();for(const f of ['wid','hei','bounds_dirty','bounds','map'])for(let i=0;i<layout['sel_'+f+'_size'];i++)defined.add(layout['sel_'+f]+i);for(let i=0;i<layout.selectionSize;i++)if(!defined.has(i))m.HEAPU8[p+i]=0x5a;});call('clone',0,1);modules.forEach(m=>{const a=bytes(m,m._probe_pointer(0),layout.selectionSize),b=bytes(m,m._probe_pointer(1),layout.selectionSize);a.fill(0,layout.sel_map,layout.sel_map+layout.pointerSize);b.fill(0,layout.sel_map,layout.sel_map+layout.pointerSize);assert.deepEqual(a,b);assert.notEqual(m._probe_map(0),m._probe_map(1));});call('set',1,2,3,0);assert.equal(call('get',0,2,3),1);call('free',1,0);modules.forEach(m=>assert.deepEqual(bytes(m,m._probe_pointer(1),layout.selectionSize),Buffer.alloc(layout.selectionSize)));call('get',1,2,3);call('free',1,1);
for(const full of [0,1]){fresh();call('clear',0,full);assert.equal(call('not',0),1);call('bounds',0,0);call('not',0);}
for(const percent of [-1,0,1,50,99,100,101]){fresh(17);rect(2,2,8,7);call('filter',0,1,percent);assert.equal(call('rng_count'),42);if(percent<=0)assert.equal(selected(modules[0],1),0);if(percent>=100)assert.equal(selected(modules[0],1),42);}
for(const typ of [-1,layout.ROOM,layout.STONE])for(const lit of [-2,-1,0,1,2,99]){fresh(29);rect(2,2,7,6);terrain(2,2,7,6,true);call('mapfilter',0,1,typ,lit);}
fresh();assert.equal(call('rndcoord',0,1),0);assert.deepEqual([call('coord',0),call('coord',1)],[-1,-1]);rect(3,3,4,4);for(let i=0;i<4;i++){rng([0]);assert.equal(call('rndcoord',0,1),1);}assert.equal(selected(modules[0]),0);
for(const remove of [0,1,2,256]){fresh();rect(2,4,4,7);rng([11]);call('rndcoord',0,remove);call('bounds',0,0);}
for(let mask=0;mask<16;mask++){fresh();call('set',0,1,0,1);call('set',0,40,10,1);call('set',0,79,20,1);call('grow',0,mask);}
fresh();call('set',0,4,4,1);call('option',0,layout.W_NORTH|layout.W_WEST);call('grow',0,layout.W_RANDOM);
for(const callback of [0,1,2])for(const diagonals of [0,1,2,256])for(const checker of [false,true]){fresh();call('new',1);call('option',1,1);terrain(2,2,8,8,checker);call('flood_callback',callback);call('flood',0,4,4,diagonals);if(callback===0)assert.equal(selected(modules[0]),0);else assert.ok(selected(modules[0])>0);}
fresh();call('flood_callback',1);terrain(1,0,3,2);call('flood',0,0,0,1);
for(const n of [-1,0,1,3,32]){reset();for(let i=0;i<32;i++)call('array',i,i-10,10-i);for(const point of [[-10,10],[-8,8],[21,-21],[0,0],[32768,32768]])call('have',...point,n);}
for(const [x,y] of [[0,0],[40,10],[79,20],[-3,4]])for(const a of [-1,0,1,2,9])for(const b of [-1,0,1,3,7])for(const fill of [0,1,2]){fresh();call('ellipse',0,x,y,a,b,fill);}
// Direct scalar probes isolate exact i64 input preservation and binary32
// arithmetic; extreme casts document the pinned Wasm oracle, not portable C UB.
const LONG_MIN=-(1n<<63n),LONG_MAX=(1n<<63n)-1n,large=(1n<<53n)+1n;
const distances=[[0n,0n,4n,3n,2n,2n],[0n,0n,0n,0n,32768n,65536n],[large,0n,large+4n,3n,large+2n,2n],[(1n<<24n)+1n,1n,(1n<<24n)+7n,4n,(1n<<24n)+3n,8n],[LONG_MIN,0n,LONG_MIN,0n,LONG_MAX,1n],[LONG_MAX-4n,0n,LONG_MAX,3n,LONG_MAX-2n,2n],[LONG_MIN,1n,LONG_MIN+4n,5n,LONG_MIN+2n,2n]];
// These i64 values straddle a binary32 midpoint while binary64 rounds
// away the last unit; converting through Number would choose the wrong f32.
const midpoint=(1n<<62n)+(1n<<38n);
for(const sign of [1n,-1n])for(const delta of [-1n,0n,1n]){const n=sign*(midpoint+delta);distances.push([n,0n,n+4n,3n,n+2n,2n]);}
// Wrapped squared segment length is zero: the pinned Wasm oracle then
// exercises NaN and infinity conversion through its saturating i64 cast.
distances.push([0n,0n,1n<<32n,0n,0n,0n],[0n,0n,1n<<32n,0n,1n,0n]);
reset();for(const args of distances)call('distance',...args);let seed=123;for(let i=0;i<200;i++){const args=Array.from({length:6},()=>{seed=(Math.imul(seed,1664525)+1013904223)>>>0;return BigInt((seed%20001)-10000);});call('distance',...args);}
for(const type of [layout.SEL_GRADIENT_RADIAL,layout.SEL_GRADIENT_SQUARE,99])for(const bounds of [[0n,0n],[1n,5n],[8n,2n],[3n,3n]])for(const points of [[10n,5n,10n,5n],[2n,3n,21n,12n]]){fresh(41);call('gradient',0,...points,BigInt(type),...bounds);}
for(const [x1,y1,x2,y2] of [[0,0,0,0],[0,0,79,20],[79,20,0,0],[4,18,50,1],[50,1,4,18],[2,10,70,10],[20,1,20,19],[-3,3,4,-3]]){fresh();call('line',0,x1,y1,x2,y2);assert.ok(selected(modules[0])>0);}
for(const rough of [-128,-1,0,1,2,8,127,128,255])for(const rec of [0,1,3,5,128,255]){fresh(77);call('randline',0,2,2,75,18,rough,rec);}
for(const valid of [0,1]){fresh();call('new',1);rect(0,2,3,4);call('option',1,1);call('iterate',0,valid);assert.equal(selected(modules[0],1),9);}
fresh();rect(2,3,4,5);assert.equal(call('irregular',0),0);assert.equal(call('description',0),1);assert.equal(text(modules[0],modules[0]._probe_description_pointer()).toString(),'square 3 by 3');call('set',0,3,4,0);assert.equal(call('irregular',0),1);call('description',0);call('newsyms',0);
for(const coder of [0,1])for(const fallback of [-1,2])for(const room of [-1,0,2]){fresh();call('room',0,2,2,6,6);call('room',2,10,4,13,8);call('coder',coder,fallback);for(let x=2;x<=13;x++)for(let y=2;y<=8;y++)both('cell',x,y,layout.ROOM,0,(x+y)%3===0?1:0,x>=10?5:3);state();call('fromroom',2,room);}
fresh();call('new',1);terrain(2,2,6,6);call('flood_callback',1);call('option',1,1);call('option',2,1);const before=modules.map(m=>allocationMetric(m));call('flood',0,3,3,1);modules.forEach((m,i)=>assert.ok(allocationMetric(m)>before[i]));assert.ok(selected(modules[0])>0);
fresh();call('option',3,0);rect(2,2,4,4);call('filter',0,1,50);
fresh();const saved=snapshot(modules[0]);modules[1]._probe_set(0,3,3,1);assert.deepEqual(snapshot(modules[0]),saved);reset();
console.log(`SELVAR: ${comparisons} ${referenceLabel}/pure-JS selection-map, bounds, geometry, float32, callback and RNG-site comparisons checked.`);

for(const seen of factoryServices.values())assert.equal(seen.size,1,'SELVAR factory reuses module-owned services');
