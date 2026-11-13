import assert from 'node:assert/strict';
import {CMemory,createMemoryServices,createBitfields,createCTypes,createRecordViews} from '../js/c-runtime/index.js';
const memory=new CMemory({initialBytes:4096,maximumBytes:32768}),transport=createMemoryServices(memory);
const metadata={aliases:{tiny:'short',Point:'struct point',loop:'loop'},enums:{'enum kind':{size:4,signed:true}},records:{point:{size:4,fields:{x:{offset:0,ctype:'short'},y:{offset:2,ctype:'short'}}}}};
const ctypes=createCTypes(memory,metadata,createBitfields(memory,metadata));
const expected=type=>{try{return ctypes.record(type);}catch{return null;}};
const classified=type=>{try{return ctypes.isRecord(type)?ctypes.record(type):null;}catch{return null;}};
const environment={memory,ctypes,address:transport.address,services:transport};
const a=createRecordViews({...environment,ctypes:{...ctypes,isRecord:type=>Boolean(expected(type))}}),b=createRecordViews(environment);
let checks=0;const eq=(x,y,label)=>{assert.deepEqual(x,y,label);checks++;};
const types=['char','signed char','unsigned char','short','unsigned short','int','unsigned int','long','unsigned long','long long','unsigned long long','float','double','enum kind','tiny','Point','const struct point','loop','unknown','void','char *','struct point *','short[2]',null,undefined,42];
for(const type of types)eq(classified(type),expected(type),'classification '+type);
const p=memory.calloc(1,128);for(let i=0;i<128;i++)memory.HEAPU8[p+i]=(i*37)&255;
const normalize=value=>typeof value==='object'&&value!==null?{address:value.address,length:value.length}:value;
const outcome=fn=>{try{return {value:normalize(fn())};}catch(e){return {error:e.name,message:e.message};}};
for(const type of types.filter(t=>typeof t==='string'))eq(outcome(()=>b.value(type,p)),outcome(()=>a.value(type,p)),'value '+type);
for(const type of ['char *','struct point *','unknown *','enum kind *'])for(const value of [0n,BigInt(p+32),BigInt(Number.MAX_SAFE_INTEGER)+1n]){
 memory.view.setBigUint64(p,value,true);eq(outcome(()=>b.value(type,p)),outcome(()=>a.value(type,p)),'pointer '+type+' '+value);
}
for(const type of ['short[2]','struct point[2]','unknown[2]','enum kind[2]'])for(const i of[0,1,2,3])eq(outcome(()=>b.value(type,p)[i]),outcome(()=>a.value(type,p)[i]),'array '+type+' '+i);
const av=a.record('struct point',p),bv=b.record('struct point',p);
bv.x=-123;eq(av.x,-123,'shared scalar alias');av.y=32767;eq(bv.y,32767,'reverse alias');
const old=memory.buffer;memory.grow(8192);assert.notEqual(memory.buffer,old);checks++;eq(bv.x,av.x,'growth');
// Compare declaration changes within the same type environment. Previously
// canonicalized aliases retain main's existing cache behavior.
metadata.aliases.tiny='struct point';eq(classified('tiny'),expected('tiny'));
metadata.records.unknown={size:4,fields:{}};eq(classified('unknown'),expected('unknown'));
delete metadata.records.unknown;eq(classified('unknown'),null);
const descriptor=Object.getOwnPropertyDescriptor(metadata.records,'point');Object.defineProperty(metadata.records,'point',{configurable:true,get(){throw Error('metadata access');}});eq(classified('point'),expected('point'));Object.defineProperty(metadata.records,'point',descriptor);
console.log(JSON.stringify({status:'PASS',checks,classification:'same result as caught record lookup',fixedTypeEnvironment:true,pointerAndArrayBounds:true,growthAndAliasing:true}));
