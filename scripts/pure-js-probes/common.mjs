// Test fixtures only. Production algorithms and bindings are imported under denial.
import assert from 'node:assert/strict';
const names=['WebAssembly','fetch','Worker','WebSocket','XMLHttpRequest'];
export function withoutWasm(fn){
 const saved=names.map(n=>Object.getOwnPropertyDescriptor(globalThis,n));let attempts=0;
 const deny=()=>{attempts++;throw Error('Forbidden capability in pure-JS module test');};
 for(const n of names)Object.defineProperty(globalThis,n,{configurable:true,get:deny});
 const restore=()=>{names.forEach((n,i)=>saved[i]?Object.defineProperty(globalThis,n,saved[i]):delete globalThis[n]);assert.equal(attempts,0,'Pure-JS implementation attempted a forbidden capability');};
 let result;try{result=fn();}catch(error){restore();throw error;}
 if(result?.then)return result.finally(restore);restore();return result;
}
export async function environment(options={}){
 return withoutWasm(async()=>{const {createStandaloneEnvironment}=await import('../../js/nethack/environment.js');return createStandaloneEnvironment({initialBytes:1024,maximumBytes:128*1024*1024,...options});});
}
export function probeModule(env,methods){
 const result={pureJS:true,environment:env,get HEAPU8(){return env.memory.HEAPU8;}};
 const all={_probe_stack(){const mark=env.transport.stackSave();try{return mark.index;}finally{env.transport.stackRestore(mark);}},_malloc:n=>BigInt(env.memory.malloc(Number(n))),_free:p=>env.memory.free(Number(p)),...methods};
 for(const[name,fn]of Object.entries(all))result[name]=(...args)=>withoutWasm(()=>fn(...args));
 return result;
}
// Force the same observable buffer replacement as the native fixture's large
// malloc, without doubling the entire JS heap at each successive callback.
// This still grows real addressable memory; no metric or view is simulated.
export function forceMemoryGrowth(memory,extra=16*1024*1024){
 const maximum=memory.maximumBytes,required=memory.buffer.byteLength+extra;
 if(required>maximum)throw new RangeError('Fixture exceeds configured memory limit');
 memory.maximumBytes=required;
 try{if(!memory.grow(required))throw new RangeError('Fixture memory growth failed');}
 finally{memory.maximumBytes=maximum;}
 const p=memory.malloc(16);if(!p)throw new RangeError('Fixture allocation failed');return p;
}
