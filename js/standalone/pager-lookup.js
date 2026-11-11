// Original PAGER data-file lookup bridge; no encyclopedia/menu policy is copied.
import abi from './special-interactions-abi.json' with {type:'json'};
import {createPagerBridge} from '../ported/pager-runtime.js';
import publicFunctions from './public-functions.json' with {type:'json'};
const owners=new WeakMap();
export function enablePagerLookup(environment,layouts){
 if(owners.has(environment))return owners.get(environment);
 const {services:S,memory,ctypes,transport}=environment,meta=abi.pagerLookup.meta,L=layouts.pager,address=environment.address;
 for(const[k,v]of Object.entries(abi.pagerLookup.layout))if(L[k]!==v)throw new Error('Review PAGER lookup layout '+k);
 const text=v=>typeof v==='string'?S.literal(v):address(v),resolve=n=>environment.hasFunction(n)?environment.resolve(n):typeof S[n]==='function'?S[n]:environment.resolve(n);
 const call=(n,...a)=>{const types=meta.dependencies[n]?.args??[];a=a.map((v,i)=>{const t=types[i]?.desugaredQualType??types[i]?.qualType??'';return typeof v==='string'?text(v):t.includes('*')?address(v):v?.address??v;});const out=resolve(n)(...a);return typeof out==='string'?text(out):out?.address??out;};
 const str=p=>typeof p==='string'?p:memory.readString(address(p));
 const packet=(format,p,scan=false)=>{const values=[],regex=/%(?:[-+ #0]*)(?:\d+)?(?:\.\d+)?([hljztL]*)([diuoxXcsp%])/g;for(const m of str(format).matchAll(regex)){if(m[2]==='%')continue;const at=address(p)+8*values.length;values.push(scan||'sp'.includes(m[2])?Number(memory.view.getBigUint64(at,true)):m[1]?memory.view.getBigInt64(at,true):memory.view.getInt32(at,true));}return values;};
 const storage=Object.fromEntries(Object.entries(meta.statics).map(([n,size])=>[n,environment.allocateGlobal('pager.'+n,size)])),publicAt=environment.allocateGlobal('pager.what_is_a_location',30);
 const row=(kind,i,p)=>{const [type,fields]=Object.values(meta.records)[kind],key=fields[i],f=ctypes.record(type).fields[key];if(!f)throw new Error('Unknown PAGER record '+key);return{type,key,f,at:ctypes.locate(type,address(p),key).at};};
 const locals={moduleKey:environment,heap:()=>memory.HEAPU8,stackAlloc:transport.stackAlloc,stackSave:transport.stackSave,stackRestore:transport.stackRestore,literal:text,
  staticAddress:i=>storage[Object.keys(meta.statics)[i]],publicAddress:()=>publicAt,
  copy:(a,b,n)=>memory.memmove(address(a),address(b),Number(n)),
  recordGet:(kind,i,p)=>{const r=row(kind,i,p),type=r.f.ctype.replace(new RegExp('\\s+'+r.key+'$'),'');return BigInt(/\[/.test(type)||/^struct|^union/.test(type)&&!type.includes('*')?r.at:ctypes.getField(r.type,address(p),r.key,type));},
  recordSet:(kind,i,p,v)=>{const r=row(kind,i,p),type=r.f.ctype.replace(new RegExp('\\s+'+r.key+'$'),'');return ctypes.setField(r.type,address(p),r.key,type,v);},
  array:(i,x,y)=>{const name=Object.keys(meta.arrays)[i],kind=meta.arraytypes[i];let at;if(name==='levl')at=ctypes.locate('struct instance_globals_saved_l',environment.requireGlobal('svl'),'level.locations').at;else if(name.includes('.')){const [root,...path]=name.split('.'),type=root.startsWith('sv')?'struct instance_globals_saved_'+root.slice(2):'struct instance_globals_'+root.slice(1);at=ctypes.locate(type,environment.requireGlobal(root),path.join('.')).at;}else at=environment.requireGlobal(name);const size=kind==='nhsym'||kind==='char'?1:ctypes.size(meta.records[kind][0]);return at+(name==='levl'||name==='svl.lastseentyp'?x*L.ROWNO+y:x)*size;},
  functionPointer:i=>{const name=meta.callbacks[i],proto=publicFunctions.functions[name];if(!proto)throw new Error('Unconnected PAGER callback '+name);const match=proto.match(/^(.+?)\s*\((.*)\)$/),code=t=>{t=ctypes.canonical(t.trim());return t.includes('*')?'p':t==='void'?'v':ctypes.size(t)===8?'j':'i';};return environment.functionPointer(name,[match[1],...match[2].split(',').filter(t=>t.trim()!=='void')].map(code).join(''));},
  dlb_fopen:(name,mode)=>S.fopen(text(name),text(mode)),dlb_fclose:p=>S.fclose(address(p)),dlb_fgets:(out,size,p)=>S.fgets(address(out),size,address(p)),dlb_fseek:(p,n,how)=>S.fseek(address(p),n,how),
  sprintf:(out,f,p)=>S.sprintf(address(out),text(f),...packet(f,p)),sscanfRaw:(input,f,p)=>S.sscanf(text(input),text(f),...packet(f,p,true)),
  plineRaw:(f,p)=>call('pline',text(f),...packet(f,p)),impossibleRaw:(f,p)=>call('impossible',text(f),...packet(f,p)),
  Strcpy:(out,s)=>S.strcpy(address(out),text(s)),Strcat:(out,s)=>S.strcat(address(out),text(s)),
  y_n:q=>resolve('yn_function')(text(q),environment.requireGlobal('ynchars'),110,1),
 };
 for(const[name,value]of Object.entries(abi.pagerLookup.strings))locals['string_'+name]=()=>text(value);
 const roots=new Set([...meta.globalfields,...Object.keys(meta.addresses),...Object.keys(meta.arrays)].filter(n=>n.includes('.')).map(n=>n.split('.')[0]));
 const local=new Proxy(locals,{get:(o,k)=>Reflect.has(o,k)?o[k]:roots.has(k)?undefined:typeof k==='string'?(...args)=>call(k,...args):undefined});
 const bridge=createPagerBridge(L),callLookup=(name,...args)=>transport.scoped(()=>bridge(local,name,...args));
 const names=['ia_checkfile','checkfile'].filter(n=>!environment.hasFunction(n));environment.register('special-pager-lookup',Object.fromEntries(names.map(n=>[n,(...args)=>callLookup(n,...args)])));
 const owner={call:callLookup,services:local,limitation:'Original PAGER encyclopedia lookup functions only; other pager/inspection flows are not registered or accepted.'};owners.set(environment,owner);return owner;
}
