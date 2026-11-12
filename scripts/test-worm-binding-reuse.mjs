import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {createWormState,withWormEnvironment} from '../js/nethack/bindings/worm.js';
const layouts=JSON.parse(await readFile(new URL('../js/wasm/tu-layouts.json',import.meta.url)));
let builds=0,heap=new Uint8Array(65536),stack=256;
const layout=new Proxy(Object.freeze({...layouts.worm}),{get(o,key){if(key==='pointerSize')builds++;return o[key];}});
const services={heap:()=>heap,global:()=>0,stackAlloc:n=>{const at=stack;stack+=n;return at;},rn2_on_display_rng:()=>1};
const state=createWormState(services,layout);
function call(provider,fn){const saved=stack;try{return withWormEnvironment(provider,layout,state,fn);}finally{stack=saved;}}
let first;
call(services,env=>{first=env;assert.equal(env.newsym_rn2(9),1);assert.equal(env.coordxyLocal('x').address,256);});
const firstBuilds=builds;assert.ok(firstBuilds>0);
stack=1024;
call(services,env=>{assert.equal(env,first);assert.equal(env.coordxyLocal('x').address,1024);});
assert.equal(builds,firstBuilds,'sequential calls reuse validated bindings');
const other={...services,rn2_on_display_rng:()=>2},failure=Error('nested failure');
call(services,outer=>{
    assert.equal(outer.newsym_rn2(9),1);
    assert.throws(()=>call(other,inner=>{assert.notEqual(inner,outer);assert.equal(inner.newsym_rn2(9),2);throw failure;}),e=>e===failure);
    assert.equal(outer.newsym_rn2(9),1,'nested service binding leaves outer intact');
});
call(other,env=>{assert.equal(env,first);assert.equal(env.newsym_rn2(9),2);});
let firstBorrow;
const serialized={...services,Sfo_long(fp,ref){firstBorrow=ref.address;new DataView(heap.buffer).setBigInt64(ref.address,77n,true);}};
stack=2048;call(serialized,env=>env.Sfo_long(0,env.growtimeRef(1),'growth'));
assert.equal(state.wgrowtime[1],77n);
stack=4096;call({...serialized,Sfo_long(fp,ref){assert.notEqual(ref.address,firstBorrow,'stack-backed serialization buffer is allocated for each invocation');}},env=>env.Sfo_long(0,env.growtimeRef(1),'growth'));
call(services,env=>{
    const cell=env.coordxyLocal('grow');cell.value=123;
    const replacement=new Uint8Array(heap.length*2);replacement.set(heap);heap=replacement;
    cell.value=-321;assert.equal(cell.value,-321);
    assert.equal(new DataView(heap.buffer).getInt16(cell.address,true),-321);
});
withWormEnvironment(services,layout,createWormState(services,layout),env=>assert.notEqual(env,first));
const mutable={...layout};withWormEnvironment(services,mutable,state,()=>{});mutable.pointerSize=4;
assert.throws(()=>withWormEnvironment(services,mutable,state,()=>{}),/worm ABI/);
assert.equal(state.growtimeBorrows.size,0);
console.log('WORM binding reuse: frame/state isolation, service changes, exception cleanup, heap replacement and fresh stack temporaries PASS');
