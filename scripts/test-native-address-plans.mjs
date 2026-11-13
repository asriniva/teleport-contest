// Compare the new direct transport to the prior transport on real game metadata.
// Original-C component/world tests remain separate independent oracles.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {compileNativeFieldPlans,createNativeAddressFields} from '../js/nethack/native/address-fields.js';
const metadata=JSON.parse(fs.readFileSync('js/nethack/address-ports.json')).ports;
const env=createStandaloneEnvironment({initialBytes:1024,maximumBytes:128*1024*1024});
let checks=0,fields=0,nativeReads=0,nativeWrites=0;
for(const[name,{schema}]of Object.entries(metadata)){
 const plans=compileNativeFieldPlans(env,schema);
 for(const[kind,[key,row]]of Object.entries(schema.schema).entries()){
  const bytes=env.ctypes.size(row.ctype),p=env.memory.calloc(1,bytes),q=env.memory.calloc(1,bytes);
  for(const[index,f]of row.fields.entries()){
   const plan=plans[kind][index];fields++;
   if(!f.bit){assert.equal(plan.address(p)-p,env.ctypes.fieldAddress(row.ctype,q,f.name)-q);checks++;}
   for(const pattern of [0,1,127,128,255]){
    env.memory.HEAPU8.fill(pattern,p,p+bytes);env.memory.HEAPU8.fill(pattern,q,q+bytes);
    const actual=plan.read(p),expected=env.ctypes.getField(row.ctype,q,f.name,f.canonical);
    const field=env.ctypes.record(row.ctype).fields[f.name],aggregate=field.record||f.canonical.includes('[')||(!f.canonical.includes('*')&&!/^(enum |char$|signed char$|unsigned char$|short$|unsigned short$|int$|unsigned int$|unsigned$|long$|unsigned long$|long long$|unsigned long long$|float$|double$)/.test(f.canonical));
    assert.equal(aggregate?Number(actual)-p:actual,aggregate?Number(expected)-q:expected,name+':'+key+'.'+f.name);checks++;
    if(plan.nativeRead){const typed=plan.nativeRead(p);assert.equal(typeof expected==='bigint'?BigInt(typed):typed,expected,name+':'+key+'.'+f.name+' native read');nativeReads++;checks++;}
   }
   const field=env.ctypes.record(row.ctype).fields[f.name],type=env.ctypes.canonical(f.canonical);
   if(!field.record&&!type.includes('[')&&(/^(enum |char$|signed char$|unsigned char$|short$|unsigned short$|int$|unsigned int$|unsigned$|long$|unsigned long$|long long$|unsigned long long$|float$|double$)/.test(type)||type.includes('*'))){
    for(const value of [0n,1n,0xffffffffffffffffn,0x8123456789abcdefn]){
     env.memory.HEAPU8.fill(165,p,p+bytes);env.memory.HEAPU8.fill(165,q,q+bytes);
     plan.write(p,value);env.ctypes.setField(row.ctype,q,f.name,f.canonical,value);
     assert.deepEqual(env.memory.readBytes(p,bytes),env.memory.readBytes(q,bytes),name+':'+key+'.'+f.name+' write');checks++;
     if(plan.nativeWrite){env.memory.HEAPU8.fill(165,p,p+bytes);plan.nativeWrite(p,value);assert.deepEqual(env.memory.readBytes(p,bytes),env.memory.readBytes(q,bytes),name+':'+key+'.'+f.name+' native write');nativeWrites++;checks++;}
    }
   }
  }
  env.memory.free(p);env.memory.free(q);
 }
}
const trace=[],services={read:()=>{trace.push('read');return 4n;},write:(_k,_p,_i,v)=>trace.push('write:'+v),address:(_k,p)=>p};
const f=createNativeAddressFields({ptr:Number},services,{schema:{x:{fields:[{canonical:'int'}]}}},(_t,v)=>Number(v));
assert.equal(f.compound(f.readers[0],f.writers[0],12,'+=',()=>{trace.push('rhs');return 3;}),7);
assert.deepEqual(trace,['read','rhs','write:7']);
trace.length=0;assert.equal(f.update(f.readers[0],f.writers[0],12,'++',false),4);assert.deepEqual(trace,['read','write:5']);
console.log(JSON.stringify({passed:true,ports:Object.keys(metadata).length,fields,checks,nativeReads,nativeWrites,evaluationOrder:true}));
