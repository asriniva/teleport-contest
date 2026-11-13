import assert from 'node:assert/strict';
import {CMemory} from '../js/c-runtime/heap.js';
import {NativeTypedState} from '../js/nethack/native/typed-state.js';
import {NativeStateBridge} from '../js/nethack/native/state-bridge.js';

const memory=new CMemory({initialBytes:257,maximumBytes:4097});
const arena=new NativeTypedState(memory);
const reference=new DataView(new ArrayBuffer(257));
let checks=0;
for(const kind of ['Int8','Uint8','Int16','Uint16','Int32','Uint32','BigInt64','BigUint64','Float32','Float64']){
 const wide=kind.startsWith('Big');
 const values=wide?[0n,-1n,0x123456789abcdefn,2n**80n]:[0,-1,32768,4294967297,NaN,Infinity,1.5];
 for(const at of [16,17,24,25])for(const little of [false,true])for(const value of values){
  arena.view['set'+kind](at,value,little);reference['set'+kind](at,value,little);
  assert.equal(arena.view['get'+kind](at,little),reference['get'+kind](at,little));checks++;
 }
 for(const at of [-1,257,NaN,'16',16.5]){
  let expected,actual;
  try{expected=reference['get'+kind](at,true);}catch(e){expected=e.constructor;}
  try{actual=arena.view['get'+kind](at,true);}catch(e){actual=e.constructor;}
  assert.equal(actual,expected);checks++;
 }
 if(!kind.startsWith('Float')){
  for(const at of [32,33,256]){
   const cell=arena.scalar(kind,at),value=wide?-123456789012345n:-123456789;
   let expected,actual;
   try{reference['set'+kind](at,value,true);expected=reference['get'+kind](at,true);}catch(e){expected=e.constructor;}
   try{cell.set(value);actual=cell.get();}catch(e){actual=e.constructor;}
   assert.equal(actual,expected);checks++;
  }
 }
}
for(const at of [48,49,52])for(const value of [0,16,2**32+19,Number.MAX_SAFE_INTEGER,2n**53n,2n**64n-1n,-1n]){
 arena.storePointer(at,value);
 const raw=BigInt.asUintN(64,BigInt(value));
 assert.equal(memory.view.getBigUint64(at,true),raw);
 assert.equal(arena.pointer(at),raw<=BigInt(Number.MAX_SAFE_INTEGER)?Number(raw):raw);checks++;
}
const signed=arena.scalar('BigInt64',64),unsigned=arena.scalar('BigUint64',64);
signed.set(-1n);assert.equal(signed.get(),-1n);assert.equal(unsigned.get(),2n**64n-1n);
memory.view.setUint32(64,7,true);assert.equal(signed.get(),-4294967289n);
memory.view.setBigUint64(64,19n,true);assert.equal(unsigned.get(),19n);assert.equal(signed.get(),19n);
const held=arena.scalar('Int32',80);held.set(1234);
const before=arena.Int32;let notifications=0;
const unsubscribe=memory.onGrow(()=>notifications++);
assert.equal(memory.grow(1000),true);assert.notEqual(arena.Int32,before);
assert.equal(held.get(),1234);held.set(9876);assert.equal(memory.view.getInt32(80,true),9876);
assert.equal(signed.get(),19n);assert.equal(arena.view.byteLength,1000);
assert.equal(memory.grow(999),true);assert.equal(notifications,1);
assert.equal(memory.grow(5000),false);assert.equal(notifications,1);
unsubscribe();assert.equal(memory.grow(2001),true);assert.equal(notifications,1);
assert.equal(arena.Uint32.length,500);assert.equal(held.get(),9876);
assert.throws(()=>memory.onGrow(null),TypeError);
const removeThrower=memory.onGrow(()=>{throw new RangeError('listener failure');});
assert.throws(()=>memory.grow(4097),/listener failure/);removeThrower();
assert.equal(memory.buffer.byteLength,4097);assert.equal(arena.view.byteLength,4097);
assert.equal(held.get(),9876);
assert.throws(()=>arena.pointer(4095),RangeError);
assert.throws(()=>arena.storePointer(4095,16),RangeError);
// Lazy native modules extend an existing pointer target without changing its
// address. A memoized reference must still run the newly registered providers.
const owner=new NativeStateBridge();owner.nativeArena=arena;
const target={address:128};
const decode=raw=>{if(!raw)return 0;owner.enrich(target,'struct permonst',raw);return target;};
arena.storePointer(96,128);
const referenceField=owner.pointer(96,decode,v=>v);
assert.equal(referenceField.get(),target);assert.equal(Object.hasOwn(target,'msound'),false);
owner.registerSchemas(new Map([['struct permonst',()=>{target.msound=3;}]]));
assert.equal(referenceField.get(),target);assert.equal(target.msound,3);
console.log(JSON.stringify({passed:true,checks,byteAliases:true,heldFieldsAcrossGrowth:true,oddCapacities:true,growthNotifications:true,lateProviderEnrichment:true}));
