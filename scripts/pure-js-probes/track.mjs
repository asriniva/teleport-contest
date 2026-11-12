// JS equivalent of the isolated serializer/equipment fixture in tu-track-probe.c.
import {environment,probeModule,withoutWasm} from './common.mjs';
export default async function createTrackProbe(layouts){
 const env=await environment(),L=layouts.track,memory=env.memory;
 const stream=memory.calloc(1,8192),trace=memory.calloc(1,8192),panic=memory.calloc(1,256),file=memory.calloc(1,layouts.sfstruct.nhfileSize);let length=0,pos=0,log='';
 const put=(p,s)=>{memory.HEAPU8.set(Buffer.from(s+'\0'),p);};
 withoutWasm(()=>{env.enableDecl(layouts.decl);env.enableHacklib(layouts.hacklib);});
 for(const[ctype,size]of [['int',4],['nhcoord',L.coordSize]])for(const reading of [false,true])env.services[`sf${reading?'i':'o'}_${ctype}`]=(_fp,p,tag)=>{
  const type=ctype==='nhcoord'?'coord':ctype;log+=`${reading?'in':'out'}:${type}:${typeof tag==='string'?tag:memory.readString(Number(tag))};`;put(trace,log);
  p=Number(p);if(reading){if(pos+size>length)throw Error('Fixture stream underflow');memory.HEAPU8.copyWithin(p,stream+pos,stream+pos+size);pos+=size;}else{if(length+size>8192)throw Error('Fixture stream overflow');memory.HEAPU8.copyWithin(stream+length,p,p+size);length+=size;}
 };
 const state=withoutWasm(()=>env.enableTrack(layouts)),objects=[0,0].map(()=>memory.calloc(1,env.ctypes.size('struct obj')));
 const mode=v=>memory.view.setInt32(file+layouts.sfbase.nhf_mode,v,true);
 return probeModule(env,{
  _probe_init:()=>env.call('track','initrack'),_probe_hero(x,y,left,right){env.services.u.ux=x;env.services.u.uy=y;[left,right].forEach((type,i)=>{env.ctypes.setField('struct obj',objects[i],'otyp','short',type);env.services[i?'uright':'uleft']=type<0?0:objects[i];});},
  _probe_set:()=>env.call('track','settrack'),_probe_get:(x,y)=>BigInt(env.call('track','gettrack',x,y)?.address??0),_probe_has:(x,y)=>env.call('track','hastrack',x,y),
  _probe_count:()=>state.utcnt,_probe_point:()=>state.utpnt,_probe_data:()=>BigInt(state.utrack.address),
  _probe_save(v){mode(v);length=pos=0;log='';put(trace,'');env.call('track','save_track',file);},
  _probe_rest(){mode(0);pos=0;log='';put(trace,'');put(panic,'');try{env.call('track','rest_track',file);return 0;}catch(e){if(e.name!=='CPanic')throw e;put(panic,e.message);return -1;}},
  _probe_corrupt_counts(count,point){memory.view.setInt32(stream,count,true);memory.view.setInt32(stream+4,point,true);length=Math.max(length,8);},
  _probe_stream:()=>BigInt(stream),_probe_stream_size:()=>BigInt(length),_probe_trace:()=>BigInt(trace),_probe_panic_message:()=>BigInt(panic),
 });
}
