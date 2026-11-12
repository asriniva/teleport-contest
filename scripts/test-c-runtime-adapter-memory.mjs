import assert from 'node:assert/strict';
import {CMemory,address} from '../js/c-runtime/index.js';
import {descriptorArray,writeDescriptor,readIntegerCell,writeIntegerCell,narrowInteger,defineScalarField,defineScalarValue,definePointerField,initializeRecord,scalarMethod,typeSize,formatShape,indexedArray,pointerSequence} from '../js/c-runtime/adapter-memory.js';
const memory=new CMemory({initialBytes:128,maximumBytes:8192}),cache=new Map();
const services={heap:()=>memory.HEAPU8},view=()=>memory.view,raw=v=>BigInt.asUintN(64,BigInt(v));
const at=memory.calloc(1,48),width=d=>d.a?d.a.reduce((a,b)=>a*b,1)*width(d.e):d.s?8:Number(d.t.slice(1))/8;
const decode=(type,bits)=>type[0]==='i'?BigInt.asIntN(Number(type.slice(1)),BigInt(bits)):BigInt(bits);
const read=(d,p)=>d.a?descriptorArray(cache,width,read,write,d,p):Number(decode(d.t,view()['getUint'+d.t.slice(1)](p,true)));
const write=(d,p,v)=>writeDescriptor(services,address,width,view,raw,d,p,v);
const descriptor={a:[2,3],e:{t:'i16'}},array=descriptorArray(cache,width,read,write,descriptor,at);
assert.equal(array.byteLength,12);assert.equal(array.descriptor,descriptor);
assert.equal(array,descriptorArray(cache,width,read,write,{a:[2,3],e:{t:'i16'}},at));
array[1][2]=-123;assert.equal(view().getInt16(at+10,true),-123);
// This legacy pointer-array profile deliberately has no JS array-length guard.
array[2][0]=45;assert.equal(view().getInt16(at+12,true),45);
assert.equal(array['01'][2],-123);
const before=memory.buffer;memory.malloc(512);assert.notEqual(memory.buffer,before);
assert.equal(array[1][2],-123);array[1][2]=67;assert.equal(view().getInt16(at+10,true),67);
view().setBigUint64(at+24,0xffffffffffffffffn,true);
assert.equal(readIntegerCell(view,(t,v)=>BigInt.asIntN(64,v),'long',64,at+24),-1n);
writeIntegerCell(view,at+24,64,-2n);assert.equal(view().getBigInt64(at+24,true),-2n);
writeIntegerCell(view,at+20,32,-3);assert.equal(readIntegerCell(view,(t,v)=>v|0,'int',32,at+20),-3);
for(const signed of ['i','u'])for(const bits of [8,16,32,64]){
 const value=narrowInteger(signed,bits,-1.75);
 assert.equal(typeof value,bits===64?'bigint':'number');
 assert.equal(BigInt(value),signed==='i'?-1n:(1n<<BigInt(bits))-1n);
}
// Overlapping record assignment retains the original copyWithin/memmove order.
for(let i=0;i<12;i++)memory.HEAPU8[at+i]=i;
write({s:'record'},at+2,{address:at});assert.deepEqual([...memory.HEAPU8.slice(at+2,at+10)],[0,1,2,3,4,5,6,7]);
const separate=descriptorArray(new Map(),width,read,write,descriptor,at);assert.notEqual(separate,array);
const fields={};defineScalarField(view,fields,'short',()=>at,'Int16');fields.short=65535;assert.equal(fields.short,-1);
defineScalarValue(view,fields,'wide',()=>at+24,'BigInt64');fields.wide=-123n;assert.equal(fields.wide,-123n);
definePointerField(p=>Number(view().getBigUint64(p,true)),view,raw,fields,'pointer',()=>at+32,p=>({address:p}));
fields.pointer=at+4;const held=fields.pointer;fields.pointer=at+8;assert.equal(fields.pointer.address,at+8);assert.equal(held.address,at+4);
assert.equal(scalarMethod('unsigned long'),'BigUint64');
const sizes={'int':'i32'},typeEnv={sizes:{'struct pair':4}},size=t=>typeSize(sizes,typeEnv,size,t);
assert.equal(size('int[2][3]'),24);assert.equal(size('struct pair *'),8);assert.equal(size('struct pair'),4);
assert.equal(formatShape(x=>x,'%*.*lld %s %p %.2f %%'),'iijppd');
const calls=[],indexed=indexedArray(2,i=>i+10,(i,v)=>calls.push([i,v]));
assert.equal(indexed.length,2);assert.equal(indexed[3],13);indexed[1]=7;assert.deepEqual(calls,[[1,7]]);
const sequence=pointerSequence((t,p)=>view().getInt16(p,true),(t,p,v)=>view().setInt16(p,v,true),{},()=>{},at,'short',2);
sequence[1]=-12;assert.equal(sequence[1],-12);assert.equal(sequence.address,at);
// An explicit C aggregate initializer zeroes its complete storage, then writes
// scalar/array fields and delegates bitfields to the original typed service.
const aggregate=memory.malloc(8),i16={scalar:'Int16'},i32={scalar:'Int32'},aggregateType={record:'packet'};
const sizeof=t=>t.record?8:t.array?t.array[0]*2:t.scalar==='Int32'?4:2;
const descriptions={number:{offset:0,type:i32,bits:null},values:{offset:4,type:{array:[2],of:i16},bits:null}};
const initializerWrites=[];
memory.memset(aggregate,0xaa,8);
initializeRecord(address,services,sizeof,(p,t,v)=>{initializerWrites.push([p-aggregate,v]);view()['set'+t.scalar](p,v,true);},(t,k)=>descriptions[k],{setBit(){throw new Error('Unexpected bitfield');}},v=>v,aggregate,aggregateType,{number:123,values:[7,-8]});
assert.deepEqual(initializerWrites,[[0,123],[4,7],[6,-8]]);assert.equal(view().getInt32(aggregate,true),123);assert.equal(view().getInt16(aggregate+6,true),-8);
console.log('PASS: shared descriptor-adapter profile: nested/cache/unchecked pointer arrays, growth, integer cells/narrowing, overlap copies and instance-local cache identities.');
