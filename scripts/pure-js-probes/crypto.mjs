// Addressable test contexts; computation uses the existing production algorithms.
import {environment,probeModule,withoutWasm} from './common.mjs';
export default async function createCryptoProbe(name,layouts){
 const env=await environment(),memory=env.memory,L=layouts[name];
 const algorithms=await withoutWasm(()=>import(name==='isaac64'?'../../js/isaac64.js':'../../js/ported/nhmd4.js'));
 const context=p=>{p=Number(p);memory.bounds(p,L.size);const value={};
  const scalar=(key,kind)=>Object.defineProperty(value,key,{get:()=>memory.view['get'+kind](p+L[key],true),set:v=>memory.view['set'+kind](p+L[key],v,true)});
  if(name==='isaac64'){
   scalar('n','Uint32');for(const key of ['a','b','c'])scalar(key,'BigUint64');for(const key of ['r','m'])Object.defineProperty(value,key,{get:()=>new BigUint64Array(memory.buffer,p+L[key],256)});
  }else{
   for(const key of ['lo','hi','a','b','c','d'])scalar(key,'Uint32');
   Object.defineProperties(value,{buffer:{get:()=>memory.HEAPU8.subarray(p+L.buffer,p+L.buffer+64)},block:{get:()=>new Uint32Array(memory.buffer,p+L.block,16)},clear:{value:()=>memory.memset(p,0,L.size)}});
  }return value;
 };
 const data=(p,n)=>memory.HEAPU8.subarray(Number(p),Number(p)+Math.max(0,Number(n)));
 // The production provider owns bounded rejection sampling (the frozen utility
 // export is not the configured provider). Copy caller-owned C contexts through
 // its public handle so arbitrary byte copies/counter edits remain testable.
 const generators=new Map();
 const generator=p=>{p=Number(p);if(!generators.has(p))generators.set(p,env.createIsaac());return generators.get(p);};
 const invoke=(p,fn)=>{p=Number(p);const g=generator(p);memory.memcpy(g.address,p,L.size);try{return fn(g);}finally{memory.memcpy(p,g.address,L.size);}};
 const methods=name==='isaac64'?{
  _probe_init(p,seed,n){const g=env.createIsaac(data(seed,n));generators.set(Number(p),g);memory.memcpy(Number(p),g.address,L.size);},
  _probe_reseed:(p,seed,n)=>invoke(p,g=>g.reseed(data(seed,n))),
  _probe_next:p=>BigInt.asIntN(64,invoke(p,g=>g.next())),
  _probe_bounded:(p,n)=>BigInt.asIntN(64,invoke(p,g=>g.bounded(n))),
 }:{_probe_init:p=>algorithms.nhmd4_init(context(p)),_probe_update:(p,d,n)=>algorithms.nhmd4_update(context(p),data(d,n),Number(n)),_probe_final:(p,out)=>algorithms.nhmd4_final(context(p),memory.HEAPU8.subarray(Number(out),Number(out)+16))};
 return probeModule(env,methods);
}
