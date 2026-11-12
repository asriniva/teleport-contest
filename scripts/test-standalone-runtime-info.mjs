// Actual configured MDLIB/DATE against original C; not full-game acceptance.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {spawnSync} from 'node:child_process';
import {fileURLToPath,pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/standalone/environment.js';
import {C,R,T} from '../js/c-runtime/context.js';

const defaultZones=['UTC','America/New_York','America/Los_Angeles','Asia/Kolkata','Europe/Berlin'];
if(!process.argv.includes('--worker')){
 const zones=process.env.STANDALONE_RUNTIME_INFO_ZONES?.split(',').filter(Boolean)??defaultZones,results=[];
 assert.ok(zones.length,'At least one runtime timezone is required');
 for(const zone of zones){
  const result=spawnSync(process.execPath,[fileURLToPath(import.meta.url),'--worker'],{env:{...process.env,TZ:zone},encoding:'utf8',timeout:60000,maxBuffer:8*1024*1024});
  assert.equal(result.status,0,zone+': '+(result.error||result.stderr||result.stdout));
  process.stdout.write(result.stdout);
  const line=result.stdout.split('\n').find(line=>line.startsWith('RUNTIME_INFO_RESULT '));assert.ok(line,'Worker returned exact evidence');results.push(JSON.parse(line.slice('RUNTIME_INFO_RESULT '.length)));
 }
 const total=key=>results.reduce((sum,result)=>sum+result[key],0);
 console.log(`PASS: ${total('comparisons')} original-C MDLIB/DATE comparisons and ${total('contracts')} JS storage/ownership/isolation checks over${total('cases')} cases in${zones.length} runtime timezones. Real game bootstrap and recordings remain separate.`);
}else{
 const directory=path.resolve(process.env.STANDALONE_RUNTIME_INFO_ORACLE||'.cache/standalone-runtime-info-v1');
 const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json'))),sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
 let sourceChecks=0;
 for(const [file,hash]of Object.entries(receipt.sourceSha256)){assert.equal(sha(file),hash,'Changed reference input '+file);sourceChecks++;}
 for(const [file,hash]of Object.entries(receipt.artifactSha256)){assert.equal(sha(path.join(directory,file)),hash,'Changed reference artifact '+file);sourceChecks++;}
 assert.deepEqual(receipt.buildEnvironment,{SOURCE_DATE_EPOCH:'1777723200',TZ:'UTC'},'Build macro inputs are separate from this worker runtime timezone');
 const abi=JSON.parse(fs.readFileSync('js/standalone/runtime-info-abi.json')),layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
 const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs')));
 let comparisons=0,contracts=0;
 const pair=(actual,expected,label)=>{assert.deepEqual(actual,expected,label);comparisons++;};
 const check=(value,label)=>{assert.ok(value,label);contracts++;};
 const same=(actual,expected,label)=>{assert.deepEqual(actual,expected,label);contracts++;};
 function js(fn){
  const names=['WebAssembly','fetch','XMLHttpRequest','WebSocket','Worker'],saved=names.map(name=>[name,Object.getOwnPropertyDescriptor(globalThis,name)]);let attempts=0;
  const forbidden=()=>{attempts++;throw new Error('Forbidden capability during pure-JS MDLIB/DATE execution');};
  Object.defineProperty(globalThis,'WebAssembly',{configurable:true,value:new Proxy(Object.create(null),{get:forbidden})});
  for(const name of names.slice(1))Object.defineProperty(globalThis,name,{configurable:true,value:forbidden});
  try{return fn();}finally{
   for(const [name,descriptor]of saved){if(descriptor)Object.defineProperty(globalThis,name,descriptor);else delete globalThis[name];}
   same(attempts,0,'JS makes no Wasm/network capability access');same([C,R,T],[undefined,undefined,undefined],'Source C/rect/track scopes restored');
  }
 }
 const rawString=(heap,value)=>{let at=Number(value);if(!at)return null;let end=at;while(heap[end])end++;return Buffer.from(heap.slice(at,end)).toString('latin1');};
 for(const realBuildDate of [null,'','1']){
  const errors=[],ref=await factory({print:()=>{},printErr:message=>errors.push(message)});
  function cset(name,value){const nameBytes=Buffer.from(name+'\0'),valueBytes=value===null?null:Buffer.from(value+'\0'),pointer=ref._malloc(BigInt(nameBytes.length+(valueBytes?.length??0)));ref.HEAPU8.set(nameBytes,Number(pointer));if(valueBytes)ref.HEAPU8.set(valueBytes,Number(pointer)+nameBytes.length);const result=value===null?ref._unsetenv(BigInt(pointer)):ref._setenv(BigInt(pointer),BigInt(Number(pointer)+nameBytes.length),1);assert.equal(result,0,'Set actual C environment');ref._free(pointer);}
  cset('TZ',process.env.TZ);cset('NETHACK_REAL_BUILD_DATE',realBuildDate);
  ref._probe_startup_init(1n);
  let env,group,before;
  js(()=>{
   const environment={TZ:process.env.TZ};if(realBuildDate!==null)environment.NETHACK_REAL_BUILD_DATE=realBuildDate;
   env=createStandaloneEnvironment({initialBytes:1024,maximumBytes:64*1024*1024,environment});env.enableStdio();env.enableDecl(layouts.decl);env.call('decl','program_state_init');env.call('decl','decl_globals_init');env.enableObjects(layouts.objects);env.call('objects','objects_globals_init');env.enableMonst(layouts.monst);env.call('monst','monst_globals_init');env.enableVersionInfo(layouts);
   const at=env.requireGlobal('nomakedefs');before=env.memory.readBytes(at,abi.date.size);group=env.enableRuntimeInfo(layouts);
   same(group.nomakedefs,at,'Runtime information reuses VERSION-owned DATE storage');same(env.memory.readBytes(at,abi.date.size),before,'Enabling preserves complete96-byte DATE initializer');
  });
  const cnomakedefs=Number(ref._probe_runtime_info_nomakedefs());same(cnomakedefs,Number(ref._probe_version_storage(3)),'C observers share original DATE storage');
  function cEnvironment(name){const bytes=Buffer.from(name+'\0'),at=ref._malloc(BigInt(bytes.length));ref.HEAPU8.set(bytes,Number(at));const value=Number(ref._getenv(BigInt(at)));ref._free(at);return{present:value!==0,value:rawString(ref.HEAPU8,value)};}
  for(const [name,value]of [['TZ',process.env.TZ],['NETHACK_REAL_BUILD_DATE',realBuildDate]]){const actual=js(()=>{const p=env.services.getenv(name);return{present:p!==0,value:rawString(env.memory.HEAPU8,p)};});pair(actual,cEnvironment(name),'Same explicit raw environment '+name);same(actual,{present:value!==null,value},'Environment presence preserved, including empty strings');}
  pair(rawString(ref.HEAPU8,ref._probe_runtime_info_build_date_time()),abi.date.strings.BUILD_DATE_TIME,'Actual C compiler date macros match bound production build profile');
  const cDate=()=>{const view=new DataView(ref.HEAPU8.buffer);return Object.fromEntries(Object.entries(abi.date.fields).map(([name,f])=>{const value=view.getBigUint64(cnomakedefs+f.offset,true);return[name,f.kind==='pointer'?rawString(ref.HEAPU8,value):value];}));};
  const jDate=()=>Object.fromEntries(Object.entries(abi.date.fields).map(([name,f])=>{const value=env.memory.view.getBigUint64(group.nomakedefs+f.offset,true);return[name,f.kind==='pointer'?rawString(env.memory.HEAPU8,value):value];}));
  const jtext=value=>typeof value==='string'?value:rawString(env.memory.HEAPU8,value);
  function tablesJS(){const state=group.state;return[state.artifact_names.map(jtext),state.build_opts.map(jtext),state.window_opts.map(row=>({id:jtext(row.id),name:jtext(row.name),valid:Number(row.valid)})),state.soundlib_opts.map(row=>({id:Number(row.id),text_id:jtext(row.text_id),Url:jtext(row.Url),valid:Number(row.valid)})),[state.opt_indent]];}
  function tablesC(){return Array.from({length:5},(_,kind)=>Array.from({length:ref._probe_runtime_info_table_count(kind)},(_,index)=>kind===2?{id:rawString(ref.HEAPU8,ref._probe_runtime_info_table_text(kind,index,0)),name:rawString(ref.HEAPU8,ref._probe_runtime_info_table_text(kind,index,1)),valid:ref._probe_runtime_info_table_value(kind,index,0)}:kind===3?{id:ref._probe_runtime_info_table_value(kind,index,0),text_id:rawString(ref.HEAPU8,ref._probe_runtime_info_table_text(kind,index,0)),Url:rawString(ref.HEAPU8,ref._probe_runtime_info_table_text(kind,index,1)),valid:ref._probe_runtime_info_table_value(kind,index,1)}:rawString(ref.HEAPU8,ref._probe_runtime_info_table_text(kind,index,0))));}
  function snapshotJS(){return{date:jDate(),buffers:group.storage.map((p,i)=>Buffer.from(env.memory.readBytes(p,abi.storageBytes[i]))),scalars:[group.state.idxopttext,group.state.done_runtime_opt_init_once,group.state.date_via_env,abi.mdlib.MAXOPT],options:group.state.opttext.map(jtext),tables:tablesJS()};}
  function snapshotC(){return{date:cDate(),buffers:[0,1,2].map(i=>{const p=Number(ref._probe_runtime_info_storage(i)),n=Number(ref._probe_runtime_info_storage_size(i));return Buffer.from(ref.HEAPU8.slice(p,p+n));}),scalars:Array.from({length:4},(_,i)=>ref._probe_runtime_info_scalar(i)),options:Array.from({length:abi.mdlib.MAXOPT},(_,i)=>rawString(ref.HEAPU8,ref._probe_runtime_info_option(i))),tables:tablesC()};}
  function compare(phase){
   const actual=js(snapshotJS),expected=snapshotC(),label=process.env.TZ+' real-build='+JSON.stringify(realBuildDate)+' '+phase;
   for(const name of Object.keys(abi.date.fields))pair(actual.date[name],expected.date[name],label+' DATE '+name);
   actual.buffers.forEach((bytes,i)=>pair(bytes,expected.buffers[i],label+' complete private buffer '+i));
   actual.scalars.forEach((value,i)=>pair(value,expected.scalars[i],label+' scalar '+i));
   actual.options.forEach((value,i)=>pair(value,expected.options[i],label+' opttext '+i));
   actual.tables.forEach((table,kind)=>{pair(table.length,expected.tables[kind].length,label+' table extent '+kind);table.forEach((row,i)=>pair(row,expected.tables[kind][i],label+' source table '+kind+':'+i));});
   const aliases=rows=>{const ids=new Map();return rows.map(value=>{value=Number(value);if(!value)return null;if(!ids.has(value))ids.set(value,ids.size);return ids.get(value);});},jp=js(jPointers),cp=cPointers();pair(aliases([...jp.options,...Object.values(jp.date)]),aliases([...cp.options,...Object.values(cp.date)]),label+' normalized option/DATE pointer alias identities');
  }
  const jPointers=()=>({options:[...group.state.opttext],date:Object.fromEntries(Object.entries(abi.date.fields).filter(([,f])=>f.kind==='pointer').map(([name,f])=>[name,env.memory.view.getBigUint64(group.nomakedefs+f.offset,true)]))});
  const cPointers=()=>({options:Array.from({length:abi.mdlib.MAXOPT},(_,i)=>ref._probe_runtime_info_option(i)),date:Object.fromEntries(Object.entries(abi.date.fields).filter(([,f])=>f.kind==='pointer').map(([name,f])=>[name,new DataView(ref.HEAPU8.buffer).getBigUint64(cnomakedefs+f.offset,true)]))});
  const owned=()=>new Map([...group.state.opttext,...Object.entries(abi.date.fields).filter(([,f])=>f.kind==='pointer').map(([,f])=>Number(env.memory.view.getBigUint64(group.nomakedefs+f.offset,true)))].filter(Boolean).map(p=>{check(env.memory.live.has(p),'Dynamic option/date payload has actual JS allocation ownership');return[p,env.memory.live.get(p)];}));
  const released=allocations=>{for(const pointer of allocations.keys())check(!env.memory.live.has(pointer),'Source cleanup freed actual JS owned payload '+pointer);same(group.dateState.nomakedefs_populated,0,'JS DATE populated flag cleared');same(group.state.opttext,new Array(abi.mdlib.MAXOPT).fill(0),'All JS option pointer slots cleared');};
  function call(name){js(()=>env.resolve(name)());ref['_'+name]();}
  compare('initial');call('release_runtime_info');compare('release before population');same(js(()=>env.memory.readBytes(group.nomakedefs,abi.date.size)),before,'Unpopulated DATE release preserves initialized storage');
  call('runtime_info_init');compare('first population');same(js(()=>group.dateState.nomakedefs_populated),1,'JS DATE populated flag set');
  const firstJ=js(jPointers),firstC=cPointers(),allocations=js(owned);
  call('runtime_info_init');compare('once-only second init');same(js(jPointers),firstJ,'JS initialization preserves existing payload pointer identities');same(cPointers(),firstC,'C initialization preserves existing payload pointer identities');js(()=>{for(const [p,allocation]of allocations)same(env.memory.live.get(p),allocation,'JS once-only guard preserves allocation identity');});
  function next(initial){
   let jp=0;const cp=initial===null?0n:BigInt(ref._malloc(4n));
   if(initial!==null){js(()=>{jp=env.memory.calloc(1,4);env.memory.view.setInt32(jp,initial,true);});new DataView(ref.HEAPU8.buffer).setInt32(Number(cp),initial,true);}
   const actual=js(()=>{const value=env.resolve('do_runtime_info')(jp);return{pointer:value,text:jtext(value),next:jp?env.memory.view.getInt32(jp,true):null};});
   const value=Number(ref._do_runtime_info(cp)),expected={text:rawString(ref.HEAPU8,value),next:cp?new DataView(ref.HEAPU8.buffer).getInt32(Number(cp),true):null};
   pair({text:actual.text,next:actual.next},expected,'Actual do_runtime_info result/iterator state '+initial);
   if(initial!==null){const jExpected=initial>=0&&initial<abi.mdlib.MAXOPT?js(()=>group.state.opttext[initial]):0,cExpected=initial>=0&&initial<abi.mdlib.MAXOPT?Number(ref._probe_runtime_info_option(initial)):0;same(actual.pointer,jExpected,'JS iterator returns actual owned option identity');same(value,cExpected,'C iterator returns actual owned option identity');js(()=>env.memory.free(jp));ref._free(cp);}
  }
  function iterate(){
   const jp=js(()=>env.memory.calloc(1,4)),cp=BigInt(ref._malloc(4n));new DataView(ref.HEAPU8.buffer).setInt32(Number(cp),0,true);
   for(let step=0;step<=abi.mdlib.MAXOPT;step++){
    const actual=js(()=>{const before=env.memory.view.getInt32(jp,true),pointer=env.resolve('do_runtime_info')(jp);return{pointer,text:jtext(pointer),next:env.memory.view.getInt32(jp,true),expected:before<abi.mdlib.MAXOPT?group.state.opttext[before]:0};});
    const before=new DataView(ref.HEAPU8.buffer).getInt32(Number(cp),true),pointer=Number(ref._do_runtime_info(cp));
    pair({text:actual.text,next:actual.next},{text:rawString(ref.HEAPU8,pointer),next:new DataView(ref.HEAPU8.buffer).getInt32(Number(cp),true)},'Same retained iterator cell advances through complete option table '+step);
    same(actual.pointer,actual.expected,'Retained JS iterator returns actual option identity');same(pointer,before<abi.mdlib.MAXOPT?Number(ref._probe_runtime_info_option(before)):0,'Retained C iterator returns actual option identity');
   }
   js(()=>env.memory.free(jp));ref._free(cp);
  }
  for(const initial of [null,-2147483648,-1,0,1,37,38,59,60,61,2147483647])next(initial);
  iterate();
  compare('after complete/invalid iteration');call('release_runtime_info');js(()=>released(allocations));compare('released');const liveCount=js(()=>env.memory.live.size);call('release_runtime_info');same(js(()=>env.memory.live.size),liveCount,'Repeated release is allocation-neutral');compare('released twice');
  next(null);compare('iterator auto-reinitialization');same(js(()=>group.dateState.nomakedefs_populated),1,'Iterator reinitialization repopulates DATE');
  const secondAllocations=js(owned),secondJ=js(jPointers),secondC=cPointers();call('runtime_info_init');same(js(jPointers),secondJ,'Reinitialized JS once-only pointer identities');same(cPointers(),secondC,'Reinitialized C once-only pointer identities');
  iterate();
  compare('reinitialized iteration');call('release_runtime_info');js(()=>released(secondAllocations));compare('final cleanup');same(errors,[],'Original C emits no unexpected diagnostics');
 }
 console.log('RUNTIME_INFO_RESULT '+JSON.stringify({zone:process.env.TZ,comparisons,contracts,cases:3,sourceChecks}));
}
