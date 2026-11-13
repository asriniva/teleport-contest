// Runs generated fixture JavaScript with production JS policies and services.
// No Wasm binary/loader, C policy unit or native helper is executed on this side.
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';
import {environment,probeModule,withoutWasm,forceMemoryGrowth} from '../pure-js-probes/common.mjs';
import {createPortedRuntime} from '../../js/backends/emscripten/runtime.js';
import {createErrnoStrings} from '../../js/c-runtime/errno.js';
import {scanFormatted} from '../../js/c-runtime/scanf.js';
import {enableSdkDirectory} from '../../js/nethack/sdk-directory.js';
import {enableSdkBoundary} from '../../js/nethack/sdk-boundary.js';
import {connectMailSdk} from '../../js/nethack/mail.js';
import {connectUnixPlatformSyscalls} from '../../js/nethack/unix-platform-syscalls.js';
import {createCTypes} from '../../js/nethack/c-types.js';
import unixAbi from '../../js/nethack/unix-platform-abi.json' with {type:'json'};
import records from '../../js/nethack/records.json' with {type:'json'};
import {createSignals} from '../../js/nethack/signals.js';
import {createPosixregexEnvironment} from '../../js/nethack/bindings/posixregex.js';
import {withCEnvironment} from '../../js/c-runtime/context.js';
import * as regexPolicy from '../../js/ported/posixregex.js';
import {nativeQsort} from '../../js/platform/darwin/qsort.js';
const root=path.resolve(new URL('../..',import.meta.url).pathname);
export default async function createGeneratedProbe(name,options={}){
 return withoutWasm(async()=>{
 const directory=path.join(root,'.cache/pure-js-fixtures',name),manifest=JSON.parse(fs.readFileSync(directory+'/manifest.json'));
 if(crypto.createHash('sha256').update(fs.readFileSync(path.join(root,'scripts/pure-js-fixtures/build.py'))).digest('hex')!==manifest.builderSha256)throw Error('Stale generated fixture builder '+name);
 if(manifest.gameTranslationUnitsCompiled.length||manifest.runtimeWasmRequired)throw Error('Fixture includes a forbidden game/compiler runtime');
 for(const[p,h]of Object.entries(manifest.sourceSha256))if(crypto.createHash('sha256').update(fs.readFileSync(path.join(root,p))).digest('hex')!==h)throw Error('Stale generated fixture input '+p);
 for(const[file,hash]of Object.entries(manifest.outputSha256??{}))if(crypto.createHash('sha256').update(fs.readFileSync(path.join(directory,file))).digest('hex')!==hash)throw Error('Modified generated fixture output '+file);
 const abi=JSON.parse(fs.readFileSync(directory+'/abi.json','utf8'));
 const headers=new Map(Object.entries(abi.headers)),imports=new Map(Object.entries(abi.imports)),exports=new Map(Object.entries(abi.exports)),heapBase=abi.heapBase;
 if(!Number.isSafeInteger(heapBase)||heapBase<1048576)throw Error('Missing fixture heap boundary');
 const nativeProfile=name!=='sfstruct'&&fs.existsSync(path.join(root,'.cache/tu-probes/native-oracles',name+'-native.node'));
 const env=await environment({environment:nativeProfile?{}:{USER:'web_user',LOGNAME:'web_user',PATH:'/',PWD:'/',HOME:'/home/web_user',LANG:'C.UTF-8',_:'./this.program'},initialBytes:16*1024*1024,maximumBytes:1024*1024*1024,libc:{floatPolicy:nativeProfile?'darwin':'musl'}}),m=env.memory;
 // Reserve linked fixture data and stack before any dynamic allocation can use it.
 m.malloc(heapBase+16);const lineWriter=callback=>{const bytes=[];return chunk=>{for(const value of chunk)if(value===0||value===10){callback(new TextDecoder().decode(Uint8Array.from(bytes)));bytes.length=0;}else bytes.push(value);};};
 const stdio=env.enableStdio({...options.stdin?{readStdin:n=>{const values=[];for(let i=0;i<n;i++){const value=options.stdin();if(value===null||value===undefined)break;values.push(value);}return Uint8Array.from(values);}}:{},...options.stdout?{stdout:bytes=>{for(const byte of bytes)options.stdout((byte<<24)>>24);}}:options.print?{stdout:lineWriter(options.print)}:{},...options.printErr?{stderr:lineWriter(options.printErr)}:{}});
 connectUnixPlatformSyscalls(env,createCTypes(m,{...records,aliases:{...records.aliases,...unixAbi.aliases},records:{...records.records,...unixAbi.records}},env.bitfields));
 connectMailSdk(env);enableSdkBoundary(env);enableSdkDirectory(env);if(['termcap','wintty'].includes(name))env.enableDependencies();
 const layouts=JSON.parse(fs.readFileSync(path.join(root,'js/wasm/tu-layouts.json'))),Module={...options,environment:env},baseRuntime=createPortedRuntime(layouts);let activeRuntime;
 Object.defineProperty(Module,'nethackPorted',{enumerable:true,get:()=>activeRuntime,set(value){activeRuntime=Object.defineProperties(Object.create(baseRuntime),Object.getOwnPropertyDescriptors(value??{}));if(name!=='drawing')delete activeRuntime.initializeDrawing;}});
 Module.nethackPorted=options.nethackPorted;
 if(nativeProfile&&name==='coloratt')Module.nethackPorted.posixregex=(services,key,...args)=>{const context=createPosixregexEnvironment({...services,regcomp:(a,b,flags)=>env.services.regcomp(Number(a),Number(b),flags===9?5:flags),regexec:(...v)=>env.services.regexec(...v.map(Number)),regerror:(...v)=>env.services.regerror(...v.map(Number)),regfree:p=>env.services.regfree(Number(p))},layouts.posixregex);if(key==='regex_compile'||key==='regex_match')args[1]=context.regex(args[1]);else if(key!=='regex_init')args[0]=context.regex(args[0]);return withCEnvironment(context,regexPolicy[key],...args);};
 const library={},postsets=[],initializers=[];let rawExports,tempRet=0;
 const decode=(sig,args)=>{let i=0;return sig.params.map(t=>t==='i64'?BigInt.asIntN(64,BigInt(args[i++]>>>0)|(BigInt(args[i++]>>>0)<<32n)):args[i++]);};
 const encode=(sig,args)=>sig.params.flatMap((t,i)=>{if(t!=='i64')return [args[i]??0];const n=BigInt.asUintN(64,BigInt(args[i]?.address??args[i]??0));return [Number(n&0xffffffffn)|0,Number(n>>32n)|0];});
 const result=(sig,value)=>{if(sig.result!=='i64')return value;const n=BigInt.asUintN(64,BigInt(value?.address??value??0));tempRet=Number(n>>32n)|0;return Number(n&0xffffffffn)|0;};
 const exported=(key,...args)=>{const sig=headers.get(exports.get(key));if(!sig)throw Error('Missing fixture export signature '+key);const low=rawExports[key](...encode(sig,args));return sig.result==='i64'?BigInt.asIntN(64,BigInt(low>>>0)|(BigInt(tempRet>>>0)<<32n)):low;};
 const stackSave=()=>Number(rawExports.__stack_pointer.value),stackRestore=p=>{rawExports.__stack_pointer.value=Number(p);},stackAlloc=n=>{const p=(stackSave()-Number(n))&-16;if(p<1048576)throw Error('Fixture C stack overflow');stackRestore(p);return p;};
 const utf8=new TextEncoder(),cstring=p=>m.readString(Number(p)),text=v=>typeof v==='string'?v:cstring(v);
 const vaArgs=(format,ap)=>{let at=Number(ap);const values=[];
 const read=(size,fn)=>{at=Math.ceil(at/size)*size;const value=fn(at);at+=size;return value;};
 for(const match of text(format).matchAll(/%([-+ #0]*)(\*|\d+)?(?:\.(\*|\d+))?(hh|ll|[hljztL])?([%csdiuoxXpfFeEgGaAn])/g)){
  if(match[5]==='%')continue;for(const item of [match[2],match[3]])if(item==='*')values.push(read(4,p=>m.view.getInt32(p,true)));
  const code=match[5],long=match[4];if(/[fFeEgGaA]/.test(code)){if(long==='L')throw Error('Unsupported fixture long-double vararg');values.push(read(8,p=>m.view.getFloat64(p,true)));}
  else if(/[sn]/.test(code))values.push(read(8,p=>Number(m.view.getBigUint64(p,true))));
  else if(code==='p'||/[diuoxX]/.test(code)&&long&&['l','ll','j','z','t'].includes(long))values.push(read(8,p=>m.view.getBigInt64(p,true)));
  else values.push(read(4,p=>/[uoxX]/.test(code)?m.view.getUint32(p,true):m.view.getInt32(p,true)));
 }return values;};
 const snprintf=(out,n,fmt,values)=>env.libc.snprintf(Number(out),BigInt.asUintN(64,BigInt(n)),Number(fmt),...values);
 const scanOutputs=(fmt,ap)=>{const count=[...text(fmt).matchAll(/%(?!%)(?!\*)(?:\d+)?(?:hh|ll|[hljztL])?[diuoxXscn\[]/g)].length;return Array.from({length:count},(_,i)=>Number(m.view.getBigUint64(Number(ap)+i*8,true)));};

 const longjmp=Symbol('fixture longjmp');
 const setThrew=(p,v)=>{if(!m.view.getBigUint64(Number(rawExports.__THREW__.value),true)){m.view.setBigUint64(Number(rawExports.__THREW__.value),BigInt(p),true);m.view.setInt32(Number(rawExports.__threwValue.value),v,true);}};
 const builtins={setTempRet0:v=>{tempRet=v;},getTempRet0:()=>tempRet,teleport_fixture_grow:()=>forceMemoryGrowth(m,16*1024*1024+64),
 __wasm_setjmp:(p,label,id)=>{p=Number(p);m.view.setBigUint64(p,BigInt(id),true);m.view.setUint32(p+8,label,true);},
 __wasm_setjmp_test:(p,id)=>m.view.getBigUint64(Number(p),true)===BigInt(id)?m.view.getUint32(Number(p)+8,true):0,
 emscripten_longjmp:(p,v)=>{setThrew(p,v||1);throw longjmp;},
 exit:status=>{status=Number(status);options.onExit?.(status);const e=new Error('Program terminated with exit('+status+')');e.name='ExitStatus';e.status=status;throw e;},abort(){throw Error('Fixture abort');},malloc:n=>m.malloc(Number(n)),calloc:(n,size)=>m.calloc(Number(n),Number(size)),realloc:(p,n)=>m.realloc(Number(p),Number(n)),free:p=>m.free(Number(p)),emscripten_stack_get_current:()=>BigInt(stackSave()),emscripten_get_heap_size:()=>BigInt(m.buffer.byteLength),emscripten_resize_heap:n=>Number(m.grow(Number(n))),
  memcpy:(a,b,n)=>m.memcpy(Number(a),Number(b),Number(n)),memmove:(a,b,n)=>m.memmove(Number(a),Number(b),Number(n)),memset:(p,v,n)=>m.memset(Number(p),v,Number(n)),
  vsnprintf:(out,n,fmt,ap)=>snprintf(out,n,fmt,vaArgs(fmt,ap)),snprintf:(out,n,fmt,ap)=>snprintf(out,n,fmt,vaArgs(fmt,ap)),
  vsprintf:(out,fmt,ap)=>env.libc.sprintf(Number(out),Number(fmt),...vaArgs(fmt,ap)),sprintf:(out,fmt,ap)=>env.libc.sprintf(Number(out),Number(fmt),...vaArgs(fmt,ap)),
  fscanf:(fp,fmt,ap)=>stdio.fscanf(Number(fp),Number(fmt),...scanOutputs(fmt,ap)),
  printf:(fmt,ap)=>stdio.printf(Number(fmt),...vaArgs(fmt,ap)),fprintf:(fp,fmt,ap)=>stdio.fprintf(Number(fp),Number(fmt),...vaArgs(fmt,ap)),vfprintf:(fp,fmt,ap)=>stdio.fprintf(Number(fp),Number(fmt),...vaArgs(fmt,ap)),
  qsort:(p,n,size,fn)=>nativeProfile?nativeQsort(()=>m.HEAPU8,Number(p),Number(n),Number(size),(a,b)=>tableEntry(Number(fn))(BigInt(a),BigInt(b))):env.services.qsort(Number(p),Number(n),Number(size),(a,b)=>tableEntry(Number(fn))(BigInt(a),BigInt(b))),
  tgetent:(buffer,terminal)=>{const value=env.services.tgetent(Number(buffer),Number(terminal));if(value===1&&exports.has('teleport_termcap_global')){const globals=JSON.parse(fs.readFileSync(path.join(root,'nethack-c/wasm/tu-fragments/termcap-schema.json'))).globals,index=globals.findIndex(g=>g.name==='ospeed');m.view.setInt16(Number(exported('teleport_termcap_global',index)),15,true);}return value;},
  open:(p,flags,ap)=>stdio.open(Number(p),Number(flags),Number(flags)&64?m.view.getInt32(Number(ap),true):0),
  read:(fd,p,n)=>BigInt(stdio.read(Number(fd),Number(p),Number(n))),write:(fd,p,n)=>BigInt(stdio.write(Number(fd),Number(p),Number(n))),__errno_location:env.services.__errno_location,
  sscanf:(input,fmt,ap)=>{const format=text(fmt),count=[...format.matchAll(/%(?!%)(?!\*)(?:\d+)?(?:hh|ll|[hljztL])?[diuoxXscn\[]/g)].length;const outputs=Array.from({length:count},(_,i)=>Number(m.view.getBigUint64(Number(ap)+i*8,true)));let at=0;const value=text(input);return scanFormatted(m,env.libc,{get:()=>at<value.length?value.charCodeAt(at++):-1,unget:()=>at--},format,outputs,{signedSaturation:nativeProfile});},
 };
 builtins.vsscanf=builtins.sscanf;
 builtins.siprintf=builtins.sprintf;builtins.fiprintf=builtins.fprintf;builtins.iprintf=builtins.printf;
 const tableEntry=i=>{if(!abi.callbacks[i])throw Error('Unknown fixture callback signature '+i);return (...args)=>exported('__fixture_callback_'+i,...args);};
 const resolveInvoke=(key,...args)=>{const abi=library[key+'__sig'];if(abi)args=args.map((v,i)=>abi[i+1]==='p'?Number(v?.address??v):v);if(key.startsWith('invoke_')){const mark=stackSave();try{return tableEntry(Number(args[0]))(...args.slice(1));}catch(e){stackRestore(mark);if(e!==longjmp)throw e;setThrew(1,0);return 0;}}if(exports.has(key))return exported(key,...args);if(typeof library[key]==='function')return library[key](...args);if(typeof builtins[key]==='function')return builtins[key](...args);if(!key.startsWith('teleport_')&&typeof library['teleport_nhlua_js_'+key]==='function')return resolveInvoke('teleport_nhlua_js_'+key,...args);if(key.startsWith('__real_'))return resolveInvoke(key.slice(7),...args);if(key==='difftime')return env.services.difftime(...args);const service=env.services[key]??env.libc[key];if(typeof service==='function'){return service(...(key.startsWith('lua')?args:args.map(v=>typeof v==='bigint'?Number(v):v)));}throw Error('Unresolved pure-JS fixture service '+key);};
 const invoke=(key,...args)=>{const value=resolveInvoke(key,...args),returns=imports.get(key)?.result??(['strlen','strspn','strcspn'].includes(key)?'i64':undefined);return returns==='i64'?BigInt(value?.address??value??0):value;};
 const scope={Module,addToLibrary:values=>Object.assign(library,values),addOnInit:fn=>initializers.push(fn),stackSave,stackRestore,stackAlloc,getWasmTableEntry:tableEntry,
  lengthBytesUTF8:s=>utf8.encode(s).length,stringToUTF8(s,p,n){const bytes=utf8.encode(s).subarray(0,Number(n)-1);m.HEAPU8.set(bytes,Number(p));m.HEAPU8[Number(p)+bytes.length]=0;},stringToUTF8OnStack(s){const bytes=utf8.encode(s),p=stackAlloc(bytes.length+1);m.HEAPU8.set(bytes,p);m.HEAPU8[p+bytes.length]=0;return p;},UTF8ToString:p=>new TextDecoder().decode(m.readBytes(Number(p),m.strlen(Number(p)))),abort:builtins.abort,
 };
 const proxy=new Proxy(scope,{has:()=>true,get(o,k){if(k===Symbol.unscopables)return undefined;if(k in o)return o[k];if(/^HEAP/.test(String(k)))return m[k];if(k==='_free'&&exports.has('teleport_probe_free'))return p=>exported('teleport_probe_free',p);if(typeof k==='string'&&k.startsWith('_'))return (...args)=>exports.has('__wrap_'+k.slice(1))?exported('__wrap_'+k.slice(1),...args):invoke(k.slice(1),...args);if('$'+k in library)return library['$'+k];if(k in globalThis)return globalThis[k];return undefined;},set:(o,k,v)=>(o[k]=v,true)});
 for(const[key,entry]of Object.entries(abi.emJs))builtins[key]=new Function('scope',`with(scope){return function(${entry.parameters.join(',')})${entry.body};}`)(proxy);
 const dynamicCallbacks=new Map();let nextCallback=1073741824;
 const callback=id=>abi.callbacks[Number(id)]?tableEntry(Number(id)):dynamicCallbacks.get(Number(id))?.fn??(()=>{throw Error('Unknown JS fixture callback '+id);})();
 env.functions.callback=callback;env.services.callback=callback;
 env.functions.functionPointer=(fn,signature)=>{if(typeof fn!=='function')throw TypeError('Invalid JS fixture callback');const id=nextCallback++;dynamicCallbacks.set(id,{fn,signature});return BigInt(id);};
 env.functions.indirect=(id,signature,...args)=>{const record=dynamicCallbacks.get(Number(id));if(record&&record.signature!==signature)throw TypeError('Incompatible JS fixture callback');return callback(id)(...args);};
 const lua=env.enableLua();Object.assign(env.services,lua.api);
 builtins.luaL_error=(L,fmt,ap)=>lua.api.luaL_error_text(Number(L),env.libc.format(Number(fmt),...vaArgs(fmt,ap)));
 builtins.teleport_fixture_open_lua_libraries=L=>{for(const name of ['base','coroutine','table','string','math','utf8','os','debug','io']){const key=name==='base'?'_G':name,fn=env.functions.functionPointer(state=>lua.api['luaopen_'+name](state),'ip');lua.api.luaL_requiref(Number(L),key,fn,1);lua.api.lua_settop(Number(L),-2);}};
 env.services.lua_tocfunction=(L,index)=>Number(lua.dispatch(Number(L),'lua_tocfunction',index));
 env.services.lua_setallocf=(L,fn,ud)=>lua.dispatch(Number(L),'lua_setallocf',fn,ud);
 const signals=createSignals(env);Object.assign(env.services,{signal:signals.signal,sigaction:signals.sigaction},createErrnoStrings(m));
 for(const file of manifest.libraries){let source=fs.readFileSync(path.join(root,file),'utf8');if(['cmd','mkobj'].includes(name)&&file.endsWith('/'+name+'.js'))source=source.replace('free:(a0)=>_free(pointer(a0))','free:(a0)=>___wrap_free(pointer(a0))');new Function('scope',`with(scope){${source}\n}`)(proxy);}
 for(const [key,value]of Object.entries(library))if(key.endsWith('__postset'))postsets.push(value);
 const importEnv={memory:{get buffer(){return m.buffer;},set buffer(value){m.buffer=value;m.generation++;}},setTempRet0:v=>{tempRet=v;},getTempRet0:()=>tempRet};
 for(const [key,sig]of imports)importEnv[key]=(...args)=>result(sig,invoke(key,...decode(sig,args)));
 let code=fs.readFileSync(directory+'/fixture.js','utf8');code=code.replace(/^import .*?;\n/gm,'');code=code.slice(0,code.indexOf('var memasmFunc ='));
 code=code.replace(/ return \{\n(?=  ")/,` return {\n  "__refresh":function(){buffer=memory.buffer;HEAP8=new Int8Array(buffer);HEAP16=new Int16Array(buffer);HEAP32=new Int32Array(buffer);HEAPU8=new Uint8Array(buffer);HEAPU16=new Uint16Array(buffer);HEAPU32=new Uint32Array(buffer);HEAPF32=new Float32Array(buffer);HEAPF64=new Float64Array(buffer);bufferView=HEAPU8;},\n`);
 if(!code.includes('"__refresh"'))throw Error('Unknown fixture emitter memory shape');
 rawExports=new Function('imports',code+'\nreturn asmFunc(imports);')({env:importEnv});
 const grow=m.grow.bind(m);m.grow=required=>{const ok=grow(required);if(ok)rawExports.__refresh();return ok;};
 for(const postset of postsets)new Function('scope',`with(scope){${postset}\n}`)(proxy);
 for(const key of ['stdin','stdout','stderr'])m.view.setBigUint64(Number(rawExports[key].value),BigInt(stdio[key]),true);
 for(const fn of initializers)fn();
 exported('__wasm_call_ctors');
 const methods={};for(const key of exports.keys())methods['_'+key]=(...args)=>exported(key,...args);
 if(name==='unixmain')methods._main=(...args)=>exported('teleport_fixture_main',...args);
 Object.assign(methods,{_malloc:n=>BigInt(m.malloc(Number(n))),_free:p=>m.free(Number(p))});
 Object.defineProperties(Module,Object.getOwnPropertyDescriptors(probeModule(env,methods)));
 Object.assign(Module,{ENV:new Proxy(env.services.ENV,{set:(o,k,v)=>{env.setEnvironment(k,v);return true;}}),FS:env.FS,stackSave,stackRestore,stackAlloc,UTF8ToString:scope.UTF8ToString,stringToUTF8:scope.stringToUTF8,lengthBytesUTF8:scope.lengthBytesUTF8});
 if(name==='unixmain')Module.callMain=args=>{const values=[options.thisProgram??'nethack',...args].map(s=>{const bytes=utf8.encode(s),p=m.malloc(bytes.length+1);m.HEAPU8.set(bytes,p);m.HEAPU8[p+bytes.length]=0;return p;}),argv=m.calloc(values.length+1,8);values.forEach((p,i)=>m.view.setBigUint64(argv+i*8,BigInt(p),true));try{return Number(Module._main(values.length,BigInt(argv)));}catch(e){if(e.name==='ExitStatus')return e.status;throw e;}};
 for(const fn of options.preRun??[])fn(Module);
 return Module;
 });
}
