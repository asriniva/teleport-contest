// JS equivalent of tu-rect-probe.c's fixture, using the production RECT binding.
import {environment,probeModule,withoutWasm} from './common.mjs';
import records from '../../js/standalone/records.json' with {type:'json'};
export default async function createRectProbe(layouts){
 const env=await environment(),L=layouts.rect;let seed=0,calls=0,bound=0,diagnostics=0;
 const caller=env.memory.calloc(1,128),message=env.memory.calloc(1,128);
 const put=(p,s)=>{env.memory.HEAPU8.fill(0,p,p+128);env.memory.HEAPU8.set(Buffer.from(s),p);};
 const state=withoutWasm(()=>env.enableRect(L,{rn2(n){bound=n;calls++;seed=(Math.imul(seed,1664525)+1013904223)>>>0;put(caller,`${records.rngSites.rect.file.split('/').at(-1)}:${records.rngSites.rect.line}:${records.rngSites.rect.function}`);return seed%n;},impossible(s){diagnostics++;put(message,s);}}));
 const methods={_probe_seed(n){seed=n>>>0;calls=bound=diagnostics=0;put(caller,'');put(message,'');},_probe_rng_count:()=>calls,_probe_rng_bound:()=>bound,_probe_rng_caller:()=>BigInt(caller),_probe_diagnostic_count:()=>diagnostics,_probe_diagnostic_message:()=>BigInt(message),_probe_count:()=>state.rect_cnt,_probe_capacity:()=>state.n_rects,_probe_data:()=>BigInt(state.rect?.address??0)};
 for(const[op,fn]of Object.entries({init:'init_rect',free:'free_rect',index:'get_rect_ind',get:'get_rect',random:'rnd_rect',bounds:'rect_bounds',remove:'remove_rect',add:'add_rect',split:'split_rects'}))methods['_probe_'+op]=(...args)=>{const v=env.call('rect',fn,...args.map(Number));return ['get','random'].includes(op)?BigInt(v?.address??v??0):v;};
 return probeModule(env,methods);
}
