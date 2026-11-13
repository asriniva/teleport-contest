import assert from 'node:assert/strict';
import {execFileSync} from 'node:child_process';
import {CMemory} from '../js/c-runtime/heap.js';
import {createMemoryServices} from '../js/c-runtime/memory.js';
const baseCommit='7962216',source=execFileSync('git',['show',baseCommit+':js/c-runtime/memory.js'],{encoding:'utf8'}).replace("'./records.js'",JSON.stringify(new URL('../js/c-runtime/records.js',import.meta.url).href));
const baseline=await import('data:text/javascript;base64,'+Buffer.from(source).toString('base64'));
const reference=baseline.createMemoryServices(new CMemory()),candidate=createMemoryServices(new CMemory());
const values=[0,-0,-1,127,128,255,256,32767,32768,65535,65536,2**31,2**32,2**53-1,2**53,Number.MAX_VALUE,-Number.MAX_VALUE,Number.MIN_VALUE,NaN,Infinity,-Infinity,1.5,-1.5,0n,-1n,2n**100n+3n,'17','1.0','bad',true,false,null,undefined,Symbol('integer')];
for(let exponent=-1074;exponent<=1023;exponent+=7)for(const sign of [1,-1])for(const factor of [1,1.5])values.push(sign*factor*2**exponent);
const result=fn=>{try{return{value:fn()};}catch(e){return{error:e.constructor.name,message:e.message};}};
let checks=0;
for(const name of ['int','uint','short','ushort','char','uchar','long','ulong']){
 for(const value of values){assert.deepEqual(result(()=>candidate[name](value)),result(()=>reference[name](value)),name+' '+String(value));checks++;}
 for(const kind of ['primitive','valueOf','getter','failure']){
  const run=api=>{const trace=[];let value;
   if(kind==='primitive')value={[Symbol.toPrimitive](hint){trace.push(hint);return 255;}};
   if(kind==='valueOf')value={valueOf(){trace.push('valueOf');return 17;}};
   if(kind==='getter')value={get [Symbol.toPrimitive](){trace.push('get primitive');return hint=>{trace.push(hint);return 65537n;};}};
   if(kind==='failure')value={[Symbol.toPrimitive](){trace.push('failed');throw new RangeError('coercion failure');}};
   return{trace,result:result(()=>api[name](value))};
  };assert.deepEqual(run(candidate),run(reference),name+' '+kind);checks++;
 }
}
console.log(JSON.stringify({passed:true,checks,baseCommit,widths:[8,16,32,64],hugeNumbers:true,errorsAndCoercionOrder:true,scope:'Actual transport against the pinned prior transport; standard JS intrinsics. Synthetic correctness only; no baseline timing or profiling.'}));
