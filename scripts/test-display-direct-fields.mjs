// Differential checks against the existing scalar adapter and measured C types.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {CMemory} from '../js/c-runtime/heap.js';
import {createCTypes} from '../js/c-runtime/types.js';
import {createBitfields} from '../js/c-runtime/bitfields.js';
import {createScalarAdapter,createImmutableFieldMetadata} from '../js/c-runtime/adapter-factories.js';
import {installDirectDisplayFields} from '../js/nethack/bindings/display-direct.js';
import metadata from '../js/nethack/records.json' with {type:'json'};
import fields from '../js/nethack/display-direct-fields.json' with {type:'json'};
const schema=JSON.parse(fs.readFileSync(new URL('../nethack-c/wasm/tu-fragments/display-schema.json',import.meta.url)));
const ptr=v=>{if(typeof v==='number'&&Number.isSafeInteger(v))return v;const n=Number(v);if(!Number.isSafeInteger(n)||BigInt(n)!==BigInt(v))throw Error('DISPLAY pointer exceeds exact address range');return n;};
function fixture(){
 const memory=new CMemory({initialBytes:65536,maximumBytes:262144});
 const ctypes=createCTypes(memory,metadata,createBitfields(memory,metadata)),kinds=Object.keys(schema.schema);
 const declaration=(k,i)=>[schema.schema[kinds[k]].ctype,schema.schema[kinds[k]].fields[i]];
 let genericCalls=0;
 const services={heap:()=>memory.HEAPU8,global:()=>64,
 address:(k,p,i)=>{genericCalls++;const[t,f]=declaration(k,i);return ctypes.fieldAddress(t,p,f.name);},
 read:(k,p,i)=>{genericCalls++;const[t,f]=declaration(k,i);return ctypes.getField(t,p,f.name,f.canonical);},
 write:(k,p,i,v)=>{const[t,f]=declaration(k,i);return ctypes.setField(t,p,f.name,f.canonical,v);}};
 const generic=createScalarAdapter(services,{},schema,ptr,{profile:'cached-fields',errors:['scalar ','cell ','field '],fieldMetadata:createImmutableFieldMetadata(schema)});
 const direct={};installDirectDisplayFields(direct,generic.memory,ptr);
 return {memory,generic:generic.env,direct,calls:()=>genericCalls};
}
let checks=0;
const outcome=fn=>{try{return {value:fn()};}catch(e){return {error:e.name,message:e.message};}};
for(const seed of [0,1,127,128,255]){
 const f=fixture();
 for(let i=16;i<f.memory.HEAPU8.length;i++)f.memory.HEAPU8[i]=(i*seed+seed)&255;
 for(const row of fields){
  // Pointer reads must stay within the adapter's exactly representable range.
  const field=metadata.records[row.kind].fields[row.field];
  if(row.canonical.includes('*')&&row.op==='read')f.memory.view.setBigUint64(1024+field.offset,0x123456789abn,true);
  for(const at of [1024,1024n,0,-1,Number.MAX_SAFE_INTEGER,65535]){
   const old=()=>f.generic.field(at,row.kind,row.field)[row.op==='read'?'value':'address'];
   const count=f.calls();const actual=outcome(()=>f.direct[row.name](at));
   assert.equal(f.calls(),count,'direct access must not dispatch through services');
   assert.deepEqual(actual,outcome(old),row.name+' @ '+at);checks++;
  }
 }
 // A held direct function must observe heap replacement and subsequent writes.
 const row=fields.find(x=>x.op==='read'&&x.canonical==='int'),field=metadata.records[row.kind].fields[row.field];
 const read=f.direct[row.name];f.memory.grow(131072);f.memory.view.setInt32(1024+field.offset,-1234567,true);
 assert.equal(read(1024),f.generic.field(1024,row.kind,row.field).value);checks++;
 const other=fixture();other.memory.view.setInt32(1024+field.offset,42,true);
 assert.equal(other.direct[row.name](1024),42);assert.equal(read(1024),-1234567);checks+=2;
}
console.log(JSON.stringify({passed:true,checks,operations:fields.length,scope:'Existing adapter differential; boundary errors, signed values, exact pointers, heap growth and independent heaps; zero generic service calls on direct operations.'}));
