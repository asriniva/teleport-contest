// Pure-JS counterparts of the OBJECTS and MONST test fixtures. The actual
// catalogue bytes and initialization routines come from production providers.
import {readFileSync} from 'node:fs';
import {environment,probeModule,withoutWasm} from './common.mjs';
export default async function createCatalogueProbe(name,layouts){
 const env=await environment(),L=layouts[name],m=env.memory;
 withoutWasm(()=>env[name==='objects'?'enableObjects':'enableMonst'](L));
 const source=readFileSync(new URL(`../tu-${name}-probe.c`,import.meta.url),'utf8');
 const fields=JSON.parse('['+source.match(/field_names\[\]\s*=\s*\{([^}]+)\}/)[1]+']');
 const unsigned=JSON.parse('['+source.match(/field_unsigned\[\]\s*=\s*\{([^}]+)\}/)[1]+']');
 const fieldNames=fields.map(k=>m.cstring(k)),keys=Object.keys(L).filter(k=>k!=='size'),layoutNames=keys.map(k=>m.cstring(k));
 const type=name==='objects'?'struct objclass':'struct permonst',base=env.requireGlobal(name==='objects'?'objects':'mons'),stride=L[name==='objects'?'objectSize':'monsterSize'];
 const get=(row,key)=>{const info=env.ctypes.record(type).fields[key],ctype=info.ctype.replace(new RegExp('\\s+'+key+'$'),'');return env.ctypes.getField(type,base+row*stride,key,ctype);};
 const set=(row,key,v)=>{const info=env.ctypes.record(type).fields[key],ctype=info.ctype.replace(new RegExp('\\s+'+key+'$'),'');env.ctypes.setField(type,base+row*stride,key,ctype,v);};
 const ptr=(at,p)=>m.view.setBigUint64(at,BigInt(p),true),pointer=at=>m.view.getBigUint64(at,true);
 const poison=(at,n,seed)=>{for(let i=0;i<n;i++){seed=(Math.imul(seed,1664525)+1013904223)>>>0;m.HEAPU8[at+i]=seed>>>24;}return seed;};
 const methods={_probe_init:()=>env.call(name,name+'_globals_init'),_probe_count:()=>L.rowCount,_probe_field_count:()=>fields.length,_probe_field_name:i=>BigInt(fieldNames[i]),_probe_field_kind:i=>unsigned[i],_probe_value:(row,f)=>BigInt.asIntN(64,BigInt(get(row,fields[f]))),_probe_mutate:(row,f,v)=>set(row,fields[f],v),_probe_layout_count:()=>keys.length,_probe_layout_name:i=>BigInt(layoutNames[i]),_probe_layout_value:i=>BigInt.asIntN(64,BigInt(L[keys[i]]))};
 if(name==='objects'){
  const descriptors=env.requireGlobal('obj_descr'),text=['','fixture description','fixture user name'].map(s=>m.cstring(s));
  Object.assign(methods,{_probe_objects:()=>BigInt(base),_probe_descriptors:()=>BigInt(descriptors),_probe_string:(r,f)=>pointer(f===2?base+r*stride+L.oc_uname:descriptors+r*L.descriptorSize+L[f?'oc_descr':'oc_name']),_probe_strings(r,mode){ptr(base+r*stride+L.oc_uname,mode?text[2]:0);ptr(descriptors+r*L.descriptorSize+L.oc_name,mode?text[0]:0);ptr(descriptors+r*L.descriptorSize+L.oc_descr,mode===2?text[0]:mode?text[1]:0);},_probe_poison(seed){seed=poison(base,L.sizeof_objects,seed);poison(descriptors,L.sizeof_obj_descr,seed);}});
 }else{
  const text=['','fixture name','second fixture name'].map(s=>m.cstring(s)),attackFields=['aatyp','adtyp','damn','damd'];
  const attack=(at,a,f)=>m.HEAPU8[at+a*L.attackSize+L[attackFields[f]]];
  Object.assign(methods,{_probe_monsters:()=>BigInt(base),_probe_constants:w=>BigInt(env.requireGlobal(w?'c_sa_yes':'c_sa_no')),_probe_constant_attack:(w,a,f)=>attack(env.requireGlobal(w?'c_sa_yes':'c_sa_no'),a,f),_probe_attack:(r,a,f)=>attack(base+r*stride+L.mattk,a,f),_probe_mutate_attack:(r,a,f,v)=>{m.HEAPU8[base+r*stride+L.mattk+a*L.attackSize+L[attackFields[f]]]=v;},_probe_name:(r,g)=>pointer(base+r*stride+L.pmnames+g*8),_probe_names(r,mode){[mode?text[0]:0,mode?text[1]:0,mode===2?text[1]:mode?text[2]:0].forEach((p,g)=>ptr(base+r*stride+L.pmnames+g*8,p));},_probe_poison:seed=>poison(base,L.sizeof_mons,seed)});
 }
 return probeModule(env,methods);
}
