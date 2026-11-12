import {readFileSync} from 'node:fs';
import constants from '../../js/wasm/drawing-constants.json' with {type:'json'};
import {environment,probeModule,withoutWasm} from './common.mjs';
export default async function createDrawingProbe(layouts){
 const env=await environment(),L=layouts.drawing,m=env.memory;
 const storage=withoutWasm(()=>env.enableDrawing(L));
 const keys=Object.keys(L).filter(k=>k!=='size'),names=keys.map(k=>m.cstring(k));
 const header=readFileSync(new URL('../tu-drawing-layout.h',import.meta.url),'utf8');
 const ck=[...header.matchAll(/DRAWING_CONSTANT\((\w+)\)/g)].map(x=>x[1]).filter(k=>k!=='name'),cn=ck.map(k=>m.cstring(k));
 const bases=['objectSymbols','monsterSymbols','warningSymbols','symbols','rogueSymbols'].map(k=>storage[k]),counts=[L.MAXOCLASSES,L.MAXMCLASSES,L.WARNCOUNT,L.MAXPCHARS+1,L.MAXOCLASSES];
 const at=(t,i)=>bases[t]+i*(t<2?L.classSize:t===4?1:L.symdefSize),pointer=p=>m.view.getBigUint64(p,true);
 const methods={_probe_layout_count:()=>keys.length,_probe_layout_name:i=>BigInt(names[i]),_probe_layout_value:i=>BigInt(L[keys[i]]),_probe_constant_count:()=>ck.length,_probe_constant_name:i=>BigInt(cn[i]),_probe_constant_value:i=>constants[ck[i]],_probe_char_signed:()=>1,
 _probe_table_count:t=>counts[t],_probe_table_pointer:t=>BigInt(bases[t]),_probe_table_symbol:(t,i)=>t<2?m.view.getInt8(at(t,i)+L.classSym):m.HEAPU8[at(t,i)+(t===4?0:L.symdefSym)],_probe_table_name:(t,i)=>t<2?pointer(at(t,i)+L.className):0n,_probe_table_explanation:(t,i)=>t===4?0n:pointer(at(t,i)+(t<2?L.classExplain:L.symdefExplanation)),_probe_table_color:(t,i)=>t===2||t===3?m.view.getInt8(at(t,i)+L.symdefColor):-1};
 for(const[op,fn]of Object.entries({object:'def_char_to_objclass',monclass:'def_char_to_monclass',furniture:'def_char_is_furniture'}))methods['_probe_'+op]=v=>env.call('drawing',fn,v);
 return probeModule(env,methods);
}
