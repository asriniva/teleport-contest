import assert from 'node:assert/strict';
import {installNativeIntegerCasts} from '../js/nethack/native/execution.js';
import {createNativeScalarLocal} from '../js/nethack/native/scalar-local.js';
let checks=0;
for(const kind of ['Int16','Int32'])for(const initial of [-9007199254740991n,-65537,-32769,-1,0,1,32768,65536,2147483648,9007199254740991n,3.75,NaN,Infinity]){
 let heap=new Uint8Array(64),allocations=0;
 const view=()=>new DataView(heap.buffer),allocate=width=>{allocations++;assert.equal(width,kind==='Int16'?2:4);return 16;};
 const local=createNativeScalarLocal(initial,kind,allocate,view),expected=new DataView(new ArrayBuffer(8));expected['set'+kind](0,Number(initial),true);
 assert.equal(local.value,expected['get'+kind](0,true));assert.equal(allocations,0);checks+=2;
 for(const next of [initial,7,-32769,4294967295n]){local.value=next;expected['set'+kind](0,Number(next),true);assert.equal(local.value,expected['get'+kind](0,true));assert.equal(allocations,0);checks+=2;}
 const p=local.address;assert.equal(allocations,1);assert.equal(local.address,p);assert.equal(local.value,expected['get'+kind](0,true));checks+=3;
 // Byte aliases, nested consumers and a changed heap remain observable.
 view()['set'+kind](p,-123,true);assert.equal(local.value,-123);
 const grown=new Uint8Array(128);grown.set(heap);heap=grown;assert.equal(local.value,-123);
 local.value=32769;expected['set'+kind](0,32769,true);assert.equal(view()['get'+kind](p,true),expected['get'+kind](0,true));assert.equal(allocations,1);checks+=4;
}
let attempts=0;const retryView=new DataView(new ArrayBuffer(64));const local=createNativeScalarLocal(8,'Int32',()=>{if(++attempts===1)throw Error('allocation marker');return 16;},()=>retryView);
assert.throws(()=>local.address,/allocation marker/);assert.equal(local.value,8);assert.equal(local.address,16);assert.equal(local.value,8);assert.equal(attempts,2);checks+=5;
assert.throws(()=>createNativeScalarLocal(0,'Int8',()=>0,()=>0),/Unsupported/);checks++;
// Inspect only declared helpers on strict dependency namespaces.
let legacyCasts=0;const strict=new Proxy(Object.create(null),{get(_target,key){throw Error('missing helper '+String(key));}}),scope=Object.assign(Object.create(strict),{int:value=>{legacyCasts++;return Number(BigInt.asIntN(32,value));}});
installNativeIntegerCasts(scope);assert.equal(scope.int(4294967295),-1);assert.equal(legacyCasts,0);assert.equal(scope.int(4294967295n),-1);assert.equal(legacyCasts,1);assert.throws(()=>scope.char,/missing helper char/);checks+=5;
// The UHITM byte helper addresses memory; it is not an integer cast.
const byteAccessor=p=>({address:p}),pointerScope={byte:byteAccessor,int:v=>Number(v)};installNativeIntegerCasts(pointerScope,['byte']);assert.equal(pointerScope.byte,byteAccessor);assert.deepEqual(pointerScope.byte(1024),{address:1024});checks+=2;
console.log(JSON.stringify({passed:true,checks,nativeReadsAllocate:false,lateByteAliasing:true,growth:true,allocationRetry:true}));
