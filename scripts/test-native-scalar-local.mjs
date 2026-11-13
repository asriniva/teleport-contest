import {CMemory} from '../js/c-runtime/heap.js';
import {createMemoryServices} from '../js/c-runtime/memory.js';
import assert from 'node:assert/strict';
import {installNativeIntegerCasts} from '../js/nethack/native/execution.js';
import {createNativeScalarLocal} from '../js/nethack/native/scalar-local.js';
let checks=0;
for(const kind of ['Int8','Int16','Int32'])for(const initial of [-9007199254740991n,-65537,-32769,-1,0,1,32768,65536,2147483648,9007199254740991n,(1n<<63n)+5n,-(1n<<70n)+17n,3.75,NaN,Infinity]){
 let heap=new Uint8Array(64),allocations=0;
 const view=()=>new DataView(heap.buffer),allocate=width=>{allocations++;assert.equal(width,kind==='Int8'?1:kind==='Int16'?2:4);return 16;};
 const local=createNativeScalarLocal(initial,kind,allocate,view,{requireLifetime:false}),expected=new DataView(new ArrayBuffer(8));expected['set'+kind](0,typeof initial==='bigint'?Number(BigInt.asIntN(kind==='Int8'?8:kind==='Int16'?16:32,initial)):Number(initial),true);
 assert.equal(local.value,expected['get'+kind](0,true));assert.equal(allocations,0);checks+=2;
 for(const next of [initial,7,-32769,4294967295n]){local.value=next;expected['set'+kind](0,typeof next==='bigint'?Number(BigInt.asIntN(kind==='Int8'?8:kind==='Int16'?16:32,next)):Number(next),true);assert.equal(local.value,expected['get'+kind](0,true));assert.equal(allocations,0);checks+=2;}
 const p=local.address;assert.equal(allocations,1);assert.equal(local.address,p);assert.equal(local.value,expected['get'+kind](0,true));checks+=3;
 // Byte aliases, nested consumers and a changed heap remain observable.
 view()['set'+kind](p,-123,true);assert.equal(local.value,-123);
 const grown=new Uint8Array(128);grown.set(heap);heap=grown;assert.equal(local.value,-123);
 local.value=32769;expected['set'+kind](0,32769,true);assert.equal(view()['get'+kind](p,true),expected['get'+kind](0,true));assert.equal(allocations,1);checks+=4;
}
let attempts=0;const retryView=new DataView(new ArrayBuffer(64));const local=createNativeScalarLocal(8,'Int32',()=>{if(++attempts===1)throw Error('allocation marker');return 16;},()=>retryView,{requireLifetime:false});
assert.throws(()=>local.address,/allocation marker/);assert.equal(local.value,8);assert.equal(local.address,16);assert.equal(local.value,8);assert.equal(attempts,2);checks+=5;
assert.throws(()=>createNativeScalarLocal(0,'Uint8',()=>0,()=>0),/Unsupported/);checks++;
// Inspect only declared helpers on strict dependency namespaces.
let legacyCasts=0;const strict=new Proxy(Object.create(null),{get(_target,key){throw Error('missing helper '+String(key));}}),scope=Object.assign(Object.create(strict),{int:value=>{legacyCasts++;return Number(BigInt.asIntN(32,value));}});
installNativeIntegerCasts(scope);assert.equal(scope.int(4294967295),-1);assert.equal(legacyCasts,0);assert.equal(scope.int(4294967295n),-1);assert.equal(legacyCasts,1);assert.throws(()=>scope.char,/missing helper char/);checks+=5;
// The UHITM byte helper addresses memory; it is not an integer cast.
const byteAccessor=p=>({address:p}),pointerScope={byte:byteAccessor,int:v=>Number(v)};installNativeIntegerCasts(pointerScope,['byte']);assert.equal(pointerScope.byte,byteAccessor);assert.deepEqual(pointerScope.byte(1024),{address:1024});checks+=2;
// Uninitialized byte locals retain backing bytes until actually written.
let deferred=0;const uninitializedView=new DataView(new ArrayBuffer(32));uninitializedView.setInt8(16,-77);const byteLocal=createNativeScalarLocal(undefined,'Int8',()=>{deferred++;return 16;},()=>uninitializedView,{uninitialized:true,requireLifetime:false});assert.equal(deferred,0);assert.equal(byteLocal.value,-77);assert.equal(deferred,1);byteLocal.value=255;assert.equal(byteLocal.value,-1);assert.equal(uninitializedView.getInt8(16),-1);checks+=5;
const assignedFirst=createNativeScalarLocal(undefined,'Int8',()=>{deferred++;return 17;},()=>uninitializedView,{uninitialized:true,requireLifetime:false});assignedFirst.value=65;assert.equal(assignedFirst.value,65);assert.equal(deferred,1);assert.equal(assignedFirst.address,17);assert.equal(uninitializedView.getInt8(17),65);checks+=4;
// A callee must not own a caller's lazily materialized reference.
const scopedMemory=new CMemory({initialBytes:128,maximumBytes:1024*1024}),transport=createMemoryServices(scopedMemory),live=scopedMemory.live.size,caller=transport.stackSave();
const scopedLocal=createNativeScalarLocal(7,'Int32',transport.stackAlloc,()=>scopedMemory.view,{requireLifetime:true});
assert.equal(scopedMemory.live.size,live);checks++;
const callee=transport.stackSave(),scopedAt=scopedLocal.address;scopedMemory.view.setInt32(scopedAt,31,true);transport.stackAlloc(16);transport.stackRestore(callee);
assert.ok(scopedMemory.live.has(scopedAt),'callee restore preserves caller storage');assert.equal(scopedLocal.value,31);checks+=2;
const temporary=scopedMemory.malloc(16);scopedMemory.memset(temporary,0xa5,16);assert.notEqual(temporary,scopedAt);assert.equal(scopedLocal.value,31);scopedMemory.free(temporary);checks+=2;
transport.stackRestore(caller);assert.equal(scopedMemory.live.size,live);assert.throws(()=>scopedLocal.value,/Expired/);assert.throws(()=>scopedLocal.address,/Expired/);assert.throws(()=>{scopedLocal.value=9;},/Expired/);checks+=4;
const unusedFrame=transport.stackSave(),unused=createNativeScalarLocal(4,'Int16',transport.stackAlloc,()=>scopedMemory.view,{requireLifetime:true});assert.equal(scopedMemory.live.size,live);transport.stackRestore(unusedFrame);assert.equal(scopedMemory.live.size,live);assert.throws(()=>unused.address,/Expired/);checks+=3;
// Providers without reservation support allocate in the declaring frame.
const legacyFrame=transport.stackSave(),legacyAllocator=n=>transport.stackAlloc(n),legacyLocal=createNativeScalarLocal(8,'Int8',legacyAllocator,()=>scopedMemory.view,{requireLifetime:true});assert.equal(scopedMemory.live.size,live+1);const nestedFrame=transport.stackSave();assert.equal(legacyLocal.value,8);transport.stackRestore(nestedFrame);assert.equal(legacyLocal.value,8);transport.stackRestore(legacyFrame);assert.equal(scopedMemory.live.size,live);checks+=4;
// Failed materialization leaves the reserved caller slot retryable.
const retryFrame=transport.stackSave(),reservedRetry=createNativeScalarLocal(6,'Int32',transport.stackAlloc,()=>scopedMemory.view,{requireLifetime:true}),malloc=scopedMemory.malloc;
scopedMemory.malloc=()=>0;try{assert.throws(()=>reservedRetry.address,/allocation failed/);}finally{scopedMemory.malloc=malloc;}
assert.equal(reservedRetry.value,6);assert.equal(scopedMemory.live.size,live);assert.ok(reservedRetry.address);assert.equal(reservedRetry.value,6);transport.stackRestore(retryFrame);assert.equal(scopedMemory.live.size,live);checks+=6;
console.log(JSON.stringify({passed:true,checks,nativeReadsAllocate:false,lateByteAliasing:true,growth:true,allocationRetry:true}));
