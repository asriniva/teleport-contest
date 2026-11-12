// Candidate guards only; no production or policy edits.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {performance} from 'node:perf_hooks';
import {execFileSync} from 'node:child_process';
import {pathToFileURL} from 'node:url';
const baselineCommit='32d7615adb8338891bc29c0f73638fbee3bab830';
let baselineSource=execFileSync('git',['show',baselineCommit+':js/c-runtime/adapter-factories.js'],{encoding:'utf8'});
for(const name of ['adapter-memory.js','records.js'])baselineSource=baselineSource.replace("'./"+name+"'",JSON.stringify(new URL('../js/c-runtime/'+name,import.meta.url).href));
const {exactAddress,createScalarAdapter,createDescriptorMemory}=await import('data:text/javascript;base64,'+Buffer.from(baselineSource).toString('base64'));
import {exactAddress as candidateAddress,createScalarAdapter as candidateScalarAdapter,createDescriptorMemory as candidateDescriptorMemory} from '../js/c-runtime/adapter-factories.js';

const values=[0,-0,1,-1,127,128,255,256,32767,32768,65535,65536,2**31,2**32,-(2**32),2**53-1,2**53,Number.MAX_VALUE,Number.MIN_VALUE,0n,-1n,2n**99n,'42','0xff','1.0','',true,false,null,undefined,NaN,Infinity,-Infinity,1.5,-1.5,Symbol('value')];
for(let exponent=-1074;exponent<=1023;exponent+=23)values.push(2**exponent,-(2**exponent),1.5*(2**exponent));
const outcome=fn=>{try{return{value:fn()};}catch(e){return{error:e.constructor.name,message:e.message};}};
let checks=0,sink=0;
const equal=(a,b,label)=>{assert.deepEqual(a,b,label);checks++;};

for(const coalesce of [false,true])for(const v of values)
  equal(outcome(()=>candidateAddress(v,'exact-address error',coalesce)),outcome(()=>exactAddress(v,'exact-address error',coalesce)),'exactAddress');
for(const factory of [
  trace=>({[Symbol.toPrimitive](hint){trace.push(hint);return 17;}}),
  trace=>({[Symbol.toPrimitive](hint){trace.push(hint);return trace.length===1?17:18;}}),
  trace=>({valueOf(){trace.push('valueOf');return 17;}}),
  trace=>({valueOf(){trace.push('valueOf');throw Error('custom address failure');}}),
]) {
  const run=fn=>{const trace=[],v=factory(trace),result=outcome(()=>fn(v,'exact-address error'));return{trace,result};};
  equal(run(candidateAddress),run(exactAddress),'address coercion side effects/errors');
}
const schema={schema:{},globals:[]},services={heap:()=>new Uint8Array(128)},profiles=['signed-enum','cached-fields','declared-enum','address-cells','abi-globals'];
const fast=(sign,bits,value)=>bits===32?sign==='i'?value|0:value>>>0:sign==='i'?value<<(32-bits)>>(32-bits):(value>>>0)&(2**bits-1);
for(const profile of profiles)for(const enumSigned of [0,1]) {
  const options={profile,errors:['scalar ','cell ','field '],address:Number,fieldMetadata:new Map()},layout={'enumSigned:test':enumSigned};
  const baseline=createScalarAdapter(services,layout,schema,Number,options),candidate=candidateScalarAdapter(services,layout,schema,Number,options);
  for(const sign of ['i','u'])for(const bits of [8,16,32]) {
    const key=sign+bits;
    for(const v of values)equal(outcome(()=>candidate.env[key](v)),outcome(()=>baseline.env[key](v)),profile+' '+key);
  }
  for(const v of values)equal(outcome(()=>candidate.decode('enum test',v)),outcome(()=>baseline.decode('enum test',v)),profile+' enumSigned='+enumSigned);
}
const descriptor=createDescriptorMemory({services:{},layout:{},addr:Number,raw:BigInt,memory:()=>new DataView(new ArrayBuffer(128)),cache:new Map(),view:(name,v)=>({name,v})});
const candidateDecode=candidateDescriptorMemory({services:{},layout:{},addr:Number,raw:BigInt,memory:()=>new DataView(new ArrayBuffer(128)),cache:new Map(),view:(name,v)=>({name,v})}).decode;

for(const sign of ['i','u'])for(const bits of [8,16,32,64])for(const v of values)
  equal(outcome(()=>candidateDecode({t:sign+bits},v)),outcome(()=>descriptor.decode({t:sign+bits},v)),'descriptor '+sign+bits);
for(const d of [{p:0},{p:'record'},{s:'record'},{f:true},{t:'i32',p:0},{t:'u0'},{}])for(const v of [0,1,2n])
  equal(outcome(()=>candidateDecode(d,v)),outcome(()=>descriptor.decode(d,v)),'descriptor precedence/fallback');
function bench(fn,n=500000) {
  for(let i=0;i<10000;i++)sink^=fn(i);
  const samples=[];for(let trial=0;trial<5;trial++){const start=performance.now();for(let i=0;i<n;i++)sink^=fn(i);samples.push(performance.now()-start);}return samples.sort((a,b)=>a-b)[2];
}
const timings=[];
for(const [name,oldFn,newFn]of [
  ['exactAddress Number',i=>exactAddress(i+16,'address'),i=>candidateAddress(i+16,'address')],
  ['descriptor i32 Number',i=>descriptor.decode({t:'i32'},i*65537),i=>candidateDecode({t:'i32'},i*65537)],
  ['descriptor u32 Number',i=>descriptor.decode({t:'u32'},i*65537),i=>candidateDecode({t:'u32'},i*65537)],
]) {
  const baselineMs=bench(oldFn),candidateMs=bench(newFn);timings.push({name,baselineMs,candidateMs,speedup:baselineMs/candidateMs});
}
const result={node:process.version,checks,timings,sink,scope:'Synthetic outcome/side-effect checks and microbenchmarks; no C/recorder acceptance. Production candidate versus immutable '+baselineCommit+'.'};
fs.writeFileSync(new URL('../.cache/numeric-guards-results.json',import.meta.url),JSON.stringify(result,null,2)+'\n');console.log(JSON.stringify(result,null,2));
