import assert from 'node:assert/strict';
import {pathToFileURL} from 'node:url';
import {resolve} from 'node:path';
import {createSfctool} from '../js/ported-utilities/sfctool-runtime.js';
import {createUtility} from '../js/ported-utilities/tile2bmp/runtime.mjs';
if(process.argv.length!==4)throw Error('Usage: test-utility-byteops.mjs <sfctool-pair> <tile2bmp-pair>');
const [sfdir,tbdir]=process.argv.slice(2).map(p=>resolve(p));
const sf=(await import(pathToFileURL(sfdir+'/reference-full.mjs'))).default;
const tb=(await import(pathToFileURL(tbdir+'/reference.mjs'))).default;
let checks=0;
const equal=(a,b)=>{assert.deepEqual(a,b);checks++;};
for(let instance=0;instance<2;instance++){
 const m=await sf({print(){},printErr(){}}),h=createSfctool(m),native=m._utility_memset;
 const p=Number(m._malloc(1024n));
 for(const grow of [false,true]){
  if(grow){const old=m.HEAPU8.buffer;m._malloc(BigInt(m.HEAPU8.length*2));assert.notEqual(m.HEAPU8.buffer,old);checks++;}
  for(const offset of [0,1,7,16])for(const n of [0,1,7,64,255])for(const c of [-257,-1,0,1,255,256,0x12345678]){
   m.HEAPU8.fill(0xa5,p,p+1024);
   const result=native(BigInt(p+offset),c,BigInt(n)),expected=m.HEAPU8.slice(p,p+1024);
   m.HEAPU8.fill(0xa5,p,p+1024);
   m._utility_memset=()=>{throw Error('fast memset entered C');};
   try{equal(h.C.memset({address:p+offset},c,n),result);equal(m.HEAPU8.slice(p,p+1024),expected);}finally{m._utility_memset=native;}
  }
  for(const [name,key,size]of [['sfoprocs',15,h.L[27]],['sfiprocs',16,h.L[27]],['sfoflprocs',17,h.L[28]],['sfiflprocs',18,h.L[28]]]){
   const to=Number(m._utility_global(key)),source=Number(m._malloc(BigInt(size)));
   for(let i=0;i<size;i++)m.HEAPU8[source+i]=(i*73+instance*11)&255;
   const before=m.HEAPU8.slice(to-8,to+size+8);
   m._utility_memcpy(BigInt(to),BigInt(source),BigInt(size));const expected=m.HEAPU8.slice(to-8,to+size+8);
   m.HEAPU8.set(before,to-8);const copy=m._utility_memcpy;m._utility_memcpy=()=>{throw Error('fast table copy entered C');};
   try{equal(Reflect.set(h.C[name],'0',source),true);equal(m.HEAPU8.slice(to-8,to+size+8),expected);}finally{m._utility_memcpy=copy;}
  }
 }
 // Invalid ranges must reach the original operation, rather than silently clamp.
 const copy=m._utility_memcpy;let fallback=0;
 m._utility_memcpy=()=>{fallback++;};
 const base=Number(m._utility_global(15));
 equal(Reflect.set(h.C.sfoprocs,'0',base),true);
 equal(Reflect.set(h.C.sfoprocs,'0',-1),true);equal(fallback,2);m._utility_memcpy=copy;
 m._utility_memset=(...args)=>{equal(args,[-1n,0,3n]);return 123n;};equal(h.C.memset(-1,0,3),123n);
}
for(let instance=0;instance<2;instance++){
 const m=await tb({print(){},printErr(){}}),h=createUtility(m),native=m._memcpy;
 for(const grow of [false,true]){
  const out=Number(m._malloc(BigInt(h.L.bmpSize+32))),to=out+8,from=Number(m._tb_storage(0));
  if(grow){const old=m.HEAPU8.buffer;m._malloc(BigInt(m.HEAPU8.length*2));assert.notEqual(old,m.HEAPU8.buffer);checks++;}
  for(let i=0;i<h.L.bmpSize;i++)m.HEAPU8[from+i]=(i*37+instance)&255;
  m.HEAPU8.fill(0xa5,out,out+h.L.bmpSize+32);
  const result=native(BigInt(to),BigInt(from),BigInt(h.L.bmpSize)),expected=m.HEAPU8.slice(out,out+h.L.bmpSize+32);
  m.HEAPU8.fill(0xa5,out,out+h.L.bmpSize+32);m._memcpy=()=>{throw Error('fast bitmap copy entered C');};
  try{equal(h.C.copyBmp({address:to}),result);equal(m.HEAPU8.slice(out,out+h.L.bmpSize+32),expected);}finally{m._memcpy=native;}
 }
 let overlap=0;m._memcpy=()=>{overlap++;return 456;};equal(h.C.copyBmp(Number(m._tb_storage(0))),456);equal(overlap,1);
 m._memcpy=(...args)=>{equal(args,[-1n,BigInt(Number(m._tb_storage(0))),BigInt(h.L.bmpSize)]);return 321n;};equal(h.C.copyBmp(-1),321n);
}
console.log(JSON.stringify({status:'PASS',checks,actualCOracle:true,heapGrowth:true,twoModules:true,noCOnFastPaths:true}));
