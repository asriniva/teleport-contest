// Every declared member type must resolve, including nested private records.
import fs from 'node:fs';import assert from 'node:assert/strict';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {withNetHackEnums} from '../js/nethack/c-types.js';
import raw from '../js/nethack/records.json' with {type:'json'};
import measured from '../js/nethack/supplemental-record-layouts.json' with {type:'json'};
import {createNativeRecordViews} from '../js/nethack/native/record-views.js';
import {createNativeAbiCaster} from '../js/nethack/native/execution.js';
export function checkAllRecordFieldTypes(env=createStandaloneEnvironment()){
 const metadata=withNetHackEnums(raw);let fields=0;
 for(const [type,row]of Object.entries(metadata.records))for(const [name,field]of Object.entries(row.fields)){
  const declared=field.ctype.replace(new RegExp('\\b'+name+'$'),'').trim();
  assert.doesNotThrow(()=>env.ctypes.size(declared),type+'.'+name+' '+declared);
  if(field.record)assert.ok(env.ctypes.isRecord(field.record),type+'.'+name+' aggregate');
  fields++;
 }
 return{fields,records:Object.keys(metadata.records).length,supplementalRecords:Object.keys(measured.records).length};
}
if(process.argv[1]===new URL(import.meta.url).pathname){
 const env=createStandaloneEnvironment(),result=checkAllRecordFieldTypes(env),views=createNativeRecordViews(env);let checks=0;
 for(const [type,row]of Object.entries(measured.records)){
  assert.equal(env.ctypes.size(type),row.size);checks++;
  const at=env.memory.calloc(1,row.size),src=env.memory.calloc(1,row.size);env.memory.HEAPU8.fill(0xa5,src,src+row.size);
  env.ctypes.store(type,at,src);assert.deepEqual(Buffer.from(env.memory.HEAPU8.slice(at,at+row.size)),Buffer.from(env.memory.HEAPU8.slice(src,src+row.size)));checks++;
  assert.equal(views.record(type,at).address,at);checks++;
  for(const [key,field]of Object.entries(row.fields)){assert.equal(env.ctypes.locate(type,at,key).at,at+field.offset);checks++;}
  env.memory.free(src);env.memory.free(at);
 }
 // long double occurs only in alignment records. Its measured bytes are opaque,
 // not silently narrowed through JS Number or advertised as float128 arithmetic.
 assert.equal(measured.opaqueScalars['long double'].size,16);
 for(const type of ['max_align_t','@__stddef_max_align_t.h:19:9']){
  const row=env.ctypes.record(type),key='__clang_max_align_nonce2',at=env.memory.calloc(1,row.size),src=env.memory.calloc(1,16),expected=Uint8Array.from({length:16},(_,i)=>i*13+7);
  env.memory.HEAPU8.set(expected,src);env.ctypes.setField(type,at,key,'long double',src);
  const p=env.ctypes.getField(type,at,key,'long double');assert.equal(p,BigInt(at+row.fields[key].offset));checks++;
  assert.deepEqual(env.memory.readBytes(Number(p),16),expected);checks++;
  assert.equal(views.record(type,at)[key],p);checks++;
  env.memory.free(src);env.memory.free(at);
 }
 const cast=createNativeAbiCaster(env.ctypes,env.transport,env.address);
 for(const value of [0,-0,1.25,-1.25,1/3,1e-40,1e30,1e100,NaN,Infinity,-Infinity])for(const type of ['float','double']){
  assert.ok(Object.is(cast(type)(value),type==='float'?Math.fround(value):value));checks++;
 }
 assert.throws(()=>cast('long double'),/Opaque alignment storage/);checks++;
 for(const type of ['bool','_Bool'])for(const value of [0,-0,1,-1,2,1.25,NaN,Infinity,-Infinity,0n,1n]){
  const p=env.memory.calloc(1,1),expected=Number(Number(value)!==0);
  env.ctypes.store(type,p,value);assert.equal(env.ctypes.load(type,p),expected);checks++;
  assert.equal(cast(type)(value),expected);checks++;env.memory.free(p);
 }
 const booleanAt=env.memory.calloc(1,1);env.ctypes.store('boolean',booleanAt,255);assert.equal(env.ctypes.load('boolean',booleanAt),-1);checks++;assert.equal(cast('boolean')(2),2);checks++;env.memory.free(booleanAt);
 const first=Object.keys(measured.records)[0];assert.throws(()=>withNetHackEnums({...raw,records:{...raw.records,[first]:{...measured.records[first],size:measured.records[first].size+1}}}),/Conflicting supplemental record/);checks++;
 console.log(JSON.stringify({passed:true,...result,checks,opaqueAlignmentBytes:16}));
}
