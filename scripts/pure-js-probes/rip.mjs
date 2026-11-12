import abi from '../../js/nethack/rip-abi.json' with {type:'json'};
import {environment,probeModule,withoutWasm} from './common.mjs';
export default async function createRipProbe(layouts){
 const env=await environment(),L=layouts.rip,m=env.memory;
 withoutWasm(()=>env.enableDecl(layouts.decl));
 env.allocateGlobal('windowprocs',env.ctypes.size('struct window_procs'));
 let death=Buffer.alloc(0),date=0n,dateArgument=0n,killerHow=0,killerFormat=0,killerCalls=0,killerSize=0,dateCalls=0,lines=[];
 const at=key=>{const f=abi.fields[key];return env.requireGlobal(f.global)+f.offset;},head=at('head'),name=at('name'),money=at('money'),buffers=Array.from({length:64},()=>m.calloc(1,L.BUFSZ));
 const capture=(window,attribute,text,dump)=>{if(lines.length>=64)throw Error('RIP fixture output overflow');const value=typeof text==='string'?Buffer.from(text,'latin1'):m.readBytes(Number(text),m.strlen(Number(text))),p=buffers[lines.length],bytes=value.subarray(0,L.BUFSZ-1);m.HEAPU8.set(bytes,p);m.HEAPU8[p+bytes.length]=0;lines.push({window,attribute,dump,live:Number(m.view.getBigUint64(head,true)!==0n),text:p});};
 env.services.dupstr=p=>env.alloc('dupstr',Number(p));
 env.services.formatkiller=(out,size,how,format)=>{killerHow=how;killerFormat=format;killerSize=size;killerCalls++;if(size){const bytes=death.subarray(0,size-1);m.HEAPU8.set(bytes,Number(out));m.HEAPU8[Number(out)+bytes.length]=0;}};
 env.services.yyyymmdd=when=>{dateArgument=when;dateCalls++;return date;};env.services.dump_forward_putstr=(w,a,t,f)=>capture(w,a,t,f?1:2);
 const callback=env.functionPointer('probe::rip-putstr','viip',(w,a,t)=>capture(w,a,t,0)),put=env.ctypes.locate('struct window_procs',env.requireGlobal('windowprocs'),'win_putstr');m.view.setBigUint64(put.at,callback,true);
 withoutWasm(()=>env.enableRip(layouts));
 const plnameSize=env.ctypes.size(env.ctypes.record(abi.fields.name.type).fields[abi.fields.name.field].ctype.replace(/\s+plname$/,''));
 const methods={_probe_context_size:()=>BigInt(L.pointerSize),_probe_bufsz:()=>L.BUFSZ,_probe_plname_size:()=>plnameSize,_probe_long_size:()=>8,_probe_time_size:()=>8,_probe_dumplog:()=>L.DUMPLOG,_probe_dedication:()=>L.NH320_DEDICATION,
 _probe_inputs(n,value,d,when){const bytes=m.readBytes(Number(n),Math.min(m.strlen(Number(n)),plnameSize-1));m.HEAPU8.set(bytes,name);m.HEAPU8[name+bytes.length]=0;m.view.setBigInt64(money,value,true);death=m.readBytes(Number(d),Math.min(m.strlen(Number(d)),L.BUFSZ-1));date=when;},_probe_run(w,how,when){lines=[];killerCalls=dateCalls=0;env.call('rip','genl_outrip',w,how,when);},_probe_head:()=>m.view.getBigUint64(head,true),_probe_line_count:()=>lines.length,_probe_killer_how:()=>killerHow,_probe_killer_format:()=>killerFormat,_probe_killer_calls:()=>killerCalls,_probe_killer_size:()=>killerSize,_probe_date_calls:()=>dateCalls,_probe_date_argument:()=>dateArgument};
 for(const k of ['window','attribute','dump','live','text'])methods['_probe_line_'+k]=i=>k==='text'?BigInt(lines[i][k]):lines[i][k];
 return probeModule(env,methods);
}
