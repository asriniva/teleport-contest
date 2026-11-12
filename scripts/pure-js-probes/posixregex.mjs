import {environment,probeModule} from './common.mjs';
export default async function createRegexProbe(layouts){
 const env=await environment(),L=layouts.posixregex,keys=Object.keys(L),names=keys.map(k=>env.memory.cstring(k)),id=env.memory.cstring('posixregex');
 const context=p=>Number(p)?env.regexContext(Number(p)):0;
 return probeModule(env,{
  _probe_context_size:()=>BigInt(L.NhregexSize),_probe_layout_count:()=>keys.length,_probe_layout_name:i=>BigInt(names[i]),_probe_layout_value:i=>BigInt(L[keys[i]]),_probe_identifier:()=>BigInt(id),
  _probe_init:()=>BigInt(env.posixregex('regex_init')),
  _probe_compile:(p,r)=>env.posixregex('regex_compile',Number(p),context(r)),_probe_match:(p,r)=>env.posixregex('regex_match',Number(p),context(r)),
  _probe_error:(r,b)=>BigInt(env.posixregex('regex_error_desc',context(r),Number(b))),_probe_free:r=>env.posixregex('regex_free',context(r)),
  _probe_err:r=>context(r).err,_probe_set_err:(r,n)=>{context(r).err=n;},
 });
}
