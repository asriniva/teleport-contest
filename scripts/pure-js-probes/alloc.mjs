// The original allocation-failure fixture, implemented against JS-owned memory.
import {environment,probeModule} from './common.mjs';
export default async function createAllocProbe(){
 const env=await environment(),memory=env.memory,services=env.services,panic=memory.calloc(1,512);
 let active=false,failMalloc=0,failRealloc=0,mallocCalls=0,reallocCalls=0,requested=0,result=0,signed=0,unsigned=0;
 // alloc() executes with base.services, inherited by the assembled environment.
 const base=Object.getPrototypeOf(services);
 const originalMalloc=base.malloc,originalRealloc=base.realloc;
 base.malloc=n=>{if(active){mallocCalls++;requested=n;if(failMalloc){failMalloc=0;return 0;}}return originalMalloc(n);};
 base.realloc=(p,n)=>{if(active){reallocCalls++;requested=n;if(failRealloc){failRealloc=0;return 0;}}return originalRealloc(p,n);};
 const begin=(fm,fr,fn)=>{result=signed=unsigned=requested=mallocCalls=reallocCalls=0;memory.HEAPU8[panic]=0;failMalloc=fm;failRealloc=fr;active=true;try{fn();return 0;}catch(e){if(e.name!=='CPanic')throw e;memory.HEAPU8.set(Buffer.from(e.message+'\0'),panic);return -1;}finally{active=false;}};
 return probeModule(env,{
  _probe_long_size:()=>8,_probe_int_size:()=>4,_probe_lua_integer_size:()=>8,_probe_ull_size:()=>8,_probe_monitor_heap:()=>0,_probe_ptrbuf_count:()=>4,_probe_ptrbuf_size:()=>32,
  _probe_alloc:(n,fail)=>begin(fail,0,()=>{result=env.alloc('alloc',n>>>0);}),
  _probe_realloc:(p,n,fail)=>begin(0,fail,()=>{result=env.alloc('re_alloc',Number(p),n>>>0);}),
  _probe_dup:(p,fail)=>begin(fail,0,()=>{result=env.alloc('dupstr',Number(p));}),
  _probe_signed:(v,file,line)=>begin(0,0,()=>{signed=env.alloc('FITSint_',BigInt.asIntN(64,v),memory.readString(Number(file)),line);}),
  _probe_unsigned:(v,file,line)=>begin(0,0,()=>{unsigned=env.alloc('FITSuint_',BigInt.asUintN(64,v),memory.readString(Number(file)),line)|0;}),
  _probe_format:p=>BigInt(env.alloc('fmt_ptr',p)),_probe_result:()=>BigInt(result),_probe_signed_result:()=>signed,_probe_unsigned_result:()=>unsigned,
  _probe_malloc_calls:()=>mallocCalls,_probe_realloc_calls:()=>reallocCalls,_probe_requested:()=>BigInt(requested),_probe_panic_message:()=>BigInt(panic),
 });
}
