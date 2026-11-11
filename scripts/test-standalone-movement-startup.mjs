import assert from 'node:assert/strict';
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/standalone/environment.js';
import {createNativeTerminal} from '../js/services/native-terminal.js';
import {createTerminalDevices} from '../js/standalone/unix-terminal.js';
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),seed=1n;
const directory=path.resolve(process.env.STANDALONE_MOVEMENT_STARTUP_ORACLE||'.cache/standalone-movement-startup-v2');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json'))),sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const [p,h]of Object.entries(receipt.sourceSha256))assert.equal(sha(p),h,'Changed reference input '+p);
for(const [p,h]of Object.entries(receipt.artifactSha256))assert.equal(sha(path.join(directory,p)),h,'Changed reference artifact '+p);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs')));
const errors=[],entry=fs.readFileSync('nethack-c/wasm/terminfo/x/xterm-256color');
const nativeTerminal=createNativeTerminal();
// SDK TCGETS leaves speed fields untouched. Initialize the transport scratch
// identically on both sides; this defines inputs, without masking policy output.
const ref=await factory({nethackPorted:{nativeTerminal:(services,name,...args)=>nativeTerminal({...services,stackAlloc:n=>{const p=services.stackAlloc(n);services.heap().fill(0,p,p+n);return p;}},name,...args)},print:()=>{},printErr:s=>errors.push(s),preRun:[m=>{m.FS.mkdirTree('/nethack/terminfo/x');m.FS.writeFile('/nethack/terminfo/x/xterm-256color',entry);} ]});
for(const [name,value]of Object.entries({NOMUX_MARKERS:'1',TERM:'xterm-256color',TERMINFO:'/nethack/terminfo',LINES:'24',COLUMNS:'80'})){const p=ref._malloc(BigInt(name.length+value.length+2));ref.HEAPU8.set(Buffer.from(name+'\0'+value+'\0'),Number(p));ref._setenv(BigInt(p),BigInt(Number(p)+name.length+1),1);ref._free(BigInt(p));}
let checks=0;
const deviceEnv=createStandaloneEnvironment(),devices=createTerminalDevices(deviceEnv,layouts),cp=Number(ref._malloc(96n)),jp=deviceEnv.memory.malloc(96),bytes=()=>ref.HEAPU8.slice(cp,cp+96);
for(const fill of [0,0xa5,0xff])for(const fd of [0,1,2,99]){
 for(const op of ['attr','size']){
  ref.HEAPU8.fill(fill,cp,cp+96);deviceEnv.memory.memset(jp,fill,96);ref._probe_tty_errno(73);deviceEnv.libc.errno=73;
  assert.equal(op==='attr'?devices.tcgetattr(fd,jp):devices.ioctl(fd,layouts.ioctl.TIOCGWINSZ,jp),op==='attr'?ref._probe_tty_attr(fd,BigInt(cp)):ref._probe_tty_winsize(fd,BigInt(cp)),`device ${op} fd=${fd}`);
  assert.deepEqual(deviceEnv.memory.readBytes(jp,96),bytes(),'device preserves unspecified bytes');assert.equal(deviceEnv.libc.errno,ref._probe_tty_errno(73));checks+=3;
 }
 for(const action of [-1,0,1,2,3]){
  ref._probe_tty_errno(73);deviceEnv.libc.errno=73;
  assert.equal(devices.tcsetattr(fd,action,jp),ref._probe_tty_setattr(fd,action,BigInt(cp)));assert.equal(deviceEnv.libc.errno,ref._probe_tty_errno(73));checks+=2;
 }
 assert.equal(devices.cfgetospeed(jp),Number(ref._probe_tty_speed(BigInt(cp))));checks++;
}
for(let name=0;name<23;name++){
 ref._probe_tty_errno(73);deviceEnv.libc.errno=73;
 assert.equal(devices.fpathconf(0,name),BigInt(ref._probe_tty_pathconf(0,name)),'SDK pathconf '+name);assert.equal(deviceEnv.libc.errno,ref._probe_tty_errno(73));checks+=2;
}
 const env=createStandaloneEnvironment({initialBytes:1024,maximumBytes:64*1024*1024,environment:{TERM:'xterm-256color',NOMUX_MARKERS:'1',NETHACK_RNGLOG:'/rng.log',NETHACK_FIXED_DATETIME:'20260102030405'}});
 env.enableStdio();env.enableDecl(layouts.decl);env.call('decl','program_state_init');env.call('decl','decl_globals_init');env.enableDrawing(layouts.drawing);env.enableObjects(layouts.objects);env.call('objects','objects_globals_init');env.enableMonst(layouts.monst);env.call('monst','monst_globals_init');env.enableSerialization(layouts);env.enableRnd(layouts.rnd,{seed});env.call('rnd','rng_log_init');env.enableAddressPort('dungeon',{only:['ledger_no','maxledgerno']});env.enableObjectState(layouts);env.enableObjectRecords(layouts);env.enableItemInventory(layouts);env.enableTimers(layouts);env.enableItemNaming(layouts);const group=env.enableMonsterSelection(layouts);const decl=JSON.parse(fs.readFileSync('js/standalone/decl-storage.json')).globals,before=decl.map(r=>env.memory.readBytes(env.requireGlobal(r.name),r.bytes));const creation=env.enableMonsterCreation(layouts);decl.forEach((r,i)=>assert.deepEqual(env.memory.readBytes(env.requireGlobal(r.name),r.bytes),before[i],'enabling creation preserves '+r.name));

 env.enableGameStartup(layouts);env.call('sys','sys_early_init');
env.enableHeroStartup(layouts);env.enableWorldPosition(layouts);env.enableLuaSandbox(layouts);env.enableDisplayStartup(layouts);

ref._probe_level_init(seed);const window=env.enableWindowSystem(layouts),versionInfo=env.enableVersionInfo(layouts),options=env.enableOptions(layouts),metadata=JSON.parse(fs.readFileSync('js/standalone/records.json')).records;
const statusBefore=decl.map(row=>env.memory.readBytes(env.requireGlobal(row.name),row.bytes)),status=env.enableStatus(layouts),gameWindows=env.enableGameWindows(layouts),movement=env.enableMovement(layouts);decl.forEach((row,i)=>{assert.deepEqual(env.memory.readBytes(env.requireGlobal(row.name),row.bytes),statusBefore[i],'status/window constructors preserve '+row.name);checks++;});
const windowAbi=JSON.parse(fs.readFileSync('js/standalone/window-abi.json')),publicFunctions=JSON.parse(fs.readFileSync('js/standalone/public-functions.json')).functions;
const callbacks=new Map();for(const module of ['windows','wintty'])for(const [i,name]of JSON.parse(fs.readFileSync(path.join(directory,module+'-callbacks.json'))).entries())callbacks.set(BigInt(ref['_probe_'+module+'_callback'](i)),{module,name});
function text(heap,p){p=Number(p);let end=p;while(heap[end])end++;return Buffer.from(heap.slice(p,end)).toString('latin1');}
function table(c,j,label){
 c=Number(c);const ct=Buffer.from(ref.HEAPU8.slice(c,c+layouts.windows.procsSize)),jt=Buffer.from(env.memory.readBytes(j,layouts.windows.procsSize));
 for(const [key,f]of Object.entries(metadata.window_procs.fields))if(f.ctype.includes('*')){
  const native=ct.readBigUInt64LE(f.offset),own=jt.readBigUInt64LE(f.offset);
  if(key==='name')assert.equal(own?text(env.memory.HEAPU8,own):null,native?text(ref.HEAPU8,native):null,label+' name');
  else if(native&&callbacks.has(native)){
   const {module,name}=callbacks.get(native),row=windowAbi.callbacks[module][name],code=t=>{t=env.ctypes.canonical(t);return t.includes('*')?'p':t==='void'?'v':env.ctypes.size(t)===8?'j':'i';};const signature=[row.result,...row.parameters].map(code).join(''),identity=Object.hasOwn(publicFunctions,name)?name:module+'::'+name;assert.equal(own,BigInt(env.functionPointer(identity,signature)),label+' '+key+' exact callback '+name);
  }else assert.equal(!!own,!!native,label+' '+key+' foreign callback presence');
  ct.fill(0,f.offset,f.offset+8);jt.fill(0,f.offset,f.offset+8);checks++;
 }
 assert.deepEqual(jt,ct,label+' complete nonpointer procedure image');checks++;
}
table(ref._probe_windows_storage(0),env.requireGlobal('windowprocs'),'default window');
table(ref._probe_windows_storage(2),window.storage[2],'original hangup procedures');
table(ref._probe_windows_storage(3),window.storage[3],'initial dump backup');
const names=JSON.parse(fs.readFileSync('js/standalone/window-abi.json')).wintty.schema.globals;
const ttyIndex=Object.keys(names).indexOf('tty_procs');table(ref._probe_wintty_global(ttyIndex),env.requireGlobal('tty_procs'),'tty initializer');
const name=ref._malloc(4n);ref.HEAPU8.set(Buffer.from('tty\0'),Number(name));ref._probe_window_select(BigInt(name));env.services.choose_windows('tty');table(ref._probe_window_table(),env.requireGlobal('windowprocs'),'selected tty');
const p=window.platform,allocate=p.wire.stackAlloc;p.wire.stackAlloc=n=>{const at=allocate(n);env.memory.memset(at,0,n);return at;};
function platform(label){
 for(const [i,j]of [p.initial,p.current,p.termio,...p.scalars].entries()){
  const count=i<3?layouts.unixtty.termioSize:i===3?2:1,at=Number(ref._probe_unix_terminal_storage(i));
  assert.deepEqual(env.memory.readBytes(j,count),ref.HEAPU8.slice(at,at+count),label+' storage '+i);checks++;
 }
 const nativeFlags=Number(ref._probe_startup_global(20));assert.deepEqual(env.memory.readBytes(env.requireGlobal('iflags'),metadata.instance_flags.size),ref.HEAPU8.slice(nativeFlags,nativeFlags+metadata.instance_flags.size),label+' complete iflags');checks++;
}
platform('initial');
for(const call of ['gettty','setftty','introff','intron','tty_utf8graphics_fixup','getioctls','setioctls','getwindowsz']){env.services[call]();ref['_'+call]();platform(call);}
// Full tty startup remains bounded by the next actual unconnected owner.
const argc=env.memory.calloc(1,4),argv=env.memory.calloc(2,8);env.memory.view.setInt32(argc,1,true);env.memory.view.setBigUint64(argv,BigInt(env.services.literal('nethack')),true);
env.services.tty_init_nhwindows(argc,argv);ref._probe_window_init();assert.deepEqual(errors,[],'native tty initialization completed');
platform('tty init prefix');
function nativeGlobal(name){return Number(ref._probe_wintty_global(Object.keys(names).indexOf(name)));}
const ptr=(heap,at)=>Number(new DataView(heap.buffer,heap.byteOffset,heap.byteLength).getBigUint64(at,true));
const cd=ptr(ref.HEAPU8,nativeGlobal('ttyDisplay')),jd=ptr(env.memory.HEAPU8,env.requireGlobal('ttyDisplay'));
// Source alloc does not initialize these three fields or struct padding yet.
for(const [name,f]of Object.entries(metadata.DisplayDesc.fields))if(!['rawprint','framecolor','colorflags'].includes(name)){
 const width=name==='dismiss_more'?1:['rows','cols','curx','cury'].includes(name)?2:4;
 assert.deepEqual(env.memory.readBytes(jd+f.offset,width),ref.HEAPU8.slice(cd+f.offset,cd+f.offset+width),'initialized DisplayDesc '+name);checks++;
}
const cbase=new DataView(ref.HEAPU8.buffer).getInt32(nativeGlobal('BASE_WINDOW'),true),jbase=env.memory.view.getInt32(env.requireGlobal('BASE_WINDOW'),true);assert.equal(jbase,cbase);checks++;
assert.equal(layouts.wintty.MAXWIN,20,'defined configured window slot coverage');
for(let i=0;i<layouts.wintty.MAXWIN;i++){
 const c=ptr(ref.HEAPU8,nativeGlobal('wins')+i*8),j=ptr(env.memory.HEAPU8,env.requireGlobal('wins')+i*8);assert.equal(!!j,!!c,'window slot '+i);checks++;
 if(c){assert.equal(i,cbase,'only source base window allocated');assert.deepEqual(env.memory.readBytes(j,metadata.WinDesc.size),ref.HEAPU8.slice(c,c+metadata.WinDesc.size),'source base window complete image');checks++;}
}


const nativeDate=Number(ref._probe_version_storage(3)),dateLayout=layouts.date;
for(const [name,f]of Object.entries(dateLayout.fields)){
 const j=env.memory.view.getBigUint64(versionInfo.nomakedefs+f.offset,true),c=new DataView(ref.HEAPU8.buffer).getBigUint64(nativeDate+f.offset,true);
 assert.deepEqual(f.kind==='pointer'?(j?text(env.memory.HEAPU8,j):null):j,f.kind==='pointer'?(c?text(ref.HEAPU8,c):null):c,'source DATE initializer '+name);checks++;
}
for(let i=-2;i<=7;i++){const j=env.services.copyright_banner_line(i),c=ref._copyright_banner_line(i);assert.equal(text(env.memory.HEAPU8,j),text(ref.HEAPU8,c),'banner line '+i);checks++;}
const V=layouts.version;
for(let i=0;i<V.criticalCount;i++){
 const j=versionInfo.storage[0]+i*V.criticalSize,c=Number(ref._probe_version_storage(0))+i*V.criticalSize;
 assert.equal(env.memory.HEAPU8[j+V.critical_ucsize],ref.HEAPU8[c+V.critical_ucsize],'critical ABI size '+i);
 assert.equal(text(env.memory.HEAPU8,ptr(env.memory.HEAPU8,j+V.critical_nm)),text(ref.HEAPU8,ptr(ref.HEAPU8,c+V.critical_nm)),'critical ABI name '+i);checks+=2;
}
assert.equal(env.services.get_critical_size_count(),ref._get_critical_size_count());checks++;
const buffer=env.memory.calloc(1,1024),cb=ref._malloc(1024n);
for(const call of ['version_string','getversionstring']){
 env.services[call](buffer,1024);ref['_'+call](BigInt(cb),1024n);assert.equal(text(env.memory.HEAPU8,buffer),text(ref.HEAPU8,cb),call);checks++;
}
for(let i=0;i<V.rtOptCount;i++)for(const field of ['rt_token','rt_value']){
 const j=ptr(env.memory.HEAPU8,versionInfo.storage[2]+i*V.rtOptSize+V[field]),c=ptr(ref.HEAPU8,Number(ref._probe_version_storage(2))+i*V.rtOptSize+V[field]);assert.equal(text(env.memory.HEAPU8,j),text(ref.HEAPU8,c),'runtime option '+i+'.'+field);checks++;
}
for(const value of [null,'','1.2.3','5.0.7','256.1.2','1.2','a.2.3','1..3','.2.3','1.2.3-tail']){
 const j=value===null?0:env.services.literal(value),c=value===null?0:Number(cb);if(value!==null)ref.HEAPU8.set(Buffer.from(value+'\0'),c);
 assert.equal(BigInt(env.services.get_feature_notice_ver(j)),BigInt(ref._get_feature_notice_ver(BigInt(c))),'feature version '+value);checks++;
}
assert.equal(BigInt(env.services.get_current_feature_ver()),BigInt(ref._get_current_feature_ver()));checks++;
for(const mask of [0,1,4,5])for(const indent of [0,1]){
 env.ctypes.setField('struct flag',env.requireGlobal('flags'),'versinfo','unsigned int',mask);new DataView(ref.HEAPU8.buffer).setUint32(Number(ref._probe_startup_global(0))+V.versinfo,mask,true);
 env.services.status_version(buffer,1024,indent);ref._status_version(BigInt(cb),1024n,indent);assert.equal(text(env.memory.HEAPU8,buffer),text(ref.HEAPU8,cb),'number-only status version');checks++;
}
const O=JSON.parse(fs.readFileSync('js/standalone/options-abi.json')).schema,declRows=JSON.parse(fs.readFileSync('js/standalone/decl-storage.json')).globals;
const globals=declRows.map((row,i)=>({name:row.name,bytes:row.bytes,j:env.requireGlobal(row.name),c:Number(ref._probe_decl_global(i))}));
const callbackNames=new Map(O.functionAddresses.map((name,i)=>[BigInt(ref._probe_banner_options_function(i)),name]));
function optionTable(name,slot){
 const index=O.statics.findIndex(row=>row.name===name),row=O.statics[index],m=row.type.match(/^(.*)\[(\d+)\]$/);assert.ok(m,row.type);
 const record=options.ctypes.record(m[1]),count=Number(m[2]),js=options.storage[index],cs=Number(ref._probe_banner_options_storage(slot));
 for(let i=0;i<count;i++){
  const j=js+i*record.size,c=cs+i*record.size,jb=Buffer.from(env.memory.readBytes(j,record.size)),cb=Buffer.from(ref.HEAPU8.slice(c,c+record.size));
  for(const [key,f]of Object.entries(record.fields))if(f.ctype.includes('*')){
   const jp=jb.readBigUInt64LE(f.offset),cp=cb.readBigUInt64LE(f.offset);let jvalue,cvalue;
   if(key!=='optfn'&&/char\s*\*/.test(f.ctype)){jvalue=jp?text(env.memory.HEAPU8,jp):null;cvalue=cp?text(ref.HEAPU8,cp):null;}
   else if(key==='optfn'){
    if(cp){const name=callbackNames.get(cp);assert.ok(name,'known original option callback '+cp);assert.equal(jp,BigInt(options.pointer(name)),'exact option callback '+name);}else assert.equal(jp,0n);
   }else{
    const native=globals.find(g=>Number(cp)>=g.c&&Number(cp)<g.c+g.bytes),own=globals.find(g=>Number(jp)>=g.j&&Number(jp)<g.j+g.bytes);
    if(cp){assert.ok(native&&own,'shared option target '+name+'.'+key);jvalue=[own.name,Number(jp)-own.j];cvalue=[native.name,Number(cp)-native.c];}else {jvalue=jp;cvalue=cp;}
   }
   assert.deepEqual(jvalue,cvalue,name+' pointer '+i+'.'+key);jb.fill(0,f.offset,f.offset+8);cb.fill(0,f.offset,f.offset+8);checks++;
  }
  assert.deepEqual(jb,cb,name+' defined nonpointer image '+i);checks++;
 }
}
for(const [i,name]of ['allopt_init','allopt','wc_options','wc2_options'].entries())optionTable(name,i);
// Controlled source-table input; this does not substitute for allopt_array_init,
// which also invokes the complete option-handler lifecycle.
const optionIndex=O.statics.findIndex(row=>row.name==='allopt'),initIndex=O.statics.findIndex(row=>row.name==='allopt_init');
env.memory.memcpy(options.storage[optionIndex],options.storage[initIndex],options.ctypes.record('struct allopt_t').size*218);ref._probe_banner_options_copy();
for(const status of [layouts.options.set_in_config,layouts.options.set_in_game,layouts.options.set_wiznofuz])for(const mask of [0n,1n,BigInt(layouts.wintty.WC2_STATUSLINES),0xffffffffffffffffn]){
 env.services.set_wc2_option_mod_status(mask,status);ref._set_wc2_option_mod_status(mask,status);optionTable('allopt',1);
 env.services.set_wc_option_mod_status(mask,status);ref._set_wc_option_mod_status(mask,status);optionTable('allopt',1);
}

function snapshot(heap,at,type,count=1){
 at=Number(at);const record=metadata[type],raw=Buffer.from(heap.slice(at,at+record.size*count)),strings={};
 function walk(type,offset,label){for(const [name,f]of Object.entries(metadata[type].fields)){
  const n=[...f.ctype.matchAll(/\[(\d+)\]/g)].reduce((n,m)=>n*Number(m[1]),1),child=f.record??f.ctype.match(/(?:struct|union) (\w+)/)?.[1];
  if(f.ctype.includes('*'))for(let i=0;i<n;i++){
   const pos=offset+f.offset+i*8,p=raw.readBigUInt64LE(pos);strings[label+'.'+name+'['+i+']']=p?/char\s*\*(?!\s*\*)/.test(f.ctype)?text(heap,p):'allocated':null;raw.writeBigUInt64LE(p?1n:0n,pos);
  }else if(child&&metadata[child])for(let i=0;i<n;i++)walk(child,offset+f.offset+i*metadata[child].size,label+'.'+name+'['+i+']');
 }}
 for(let i=0;i<count;i++)walk(type,i*record.size,type+'['+i+']');
 if(type==='WinDesc'){
  const mask=new Uint8Array(record.size);
  for(const [key,f]of Object.entries(record.fields))if(!['blanked','menu_ch'].includes(key)){
   const width=key==='type'||key==='offx'||key==='offy'||key==='how'?2:key==='active'?1:key==='flags'?4:8;mask.fill(1,f.offset,f.offset+width);
  }
  for(let i=0;i<count;i++)for(let n=0;n<record.size;n++)if(!mask[n])raw[i*record.size+n]=0;
 }
 return {raw,strings};
}
const owned=[['initblstats','istat_s',27],['conditions','conditions_t',30],['condtests','condtests_t',30],['cond_idx',null,30*4],['enc_stat',null,6*8],['terrain_descr',null,47*8],['gb','instance_globals_b',1],['iflags','instance_flags',1],['gu','instance_globals_u',1],['disp','display_hints',1]];
const allocatedAliases=new Map(),reverseAllocatedAliases=new Map();
function allocation(c,j,label){if(!c){assert.equal(j,0,label);return;}if(allocatedAliases.has(c))assert.equal(j,allocatedAliases.get(c),label+' stable pointer identity');else {assert.ok(!reverseAllocatedAliases.has(j),label+' distinct allocation');allocatedAliases.set(c,j);reverseAllocatedAliases.set(j,c);}checks++;}
function statusState(label){
 for(const [i,[name,type,count]]of owned.entries()){
  const c=Number(ref._probe_status_storage(i)),j=name==='initblstats'?status.context.initblstats.address:env.requireGlobal(name),size=Number(ref._probe_status_size(i));assert.equal(size,type?metadata[type].size*count:count,label+' owner size '+name);
  if(type)assert.deepEqual(snapshot(env.memory.HEAPU8,j,type,count),snapshot(ref.HEAPU8,c,type,count),label+' owner '+name);
  else if(name==='cond_idx')assert.deepEqual(env.memory.readBytes(j,size),ref.HEAPU8.slice(c,c+size),label+' condition ordering');
  else for(let n=0;n<size/8;n++)assert.equal(text(env.memory.HEAPU8,ptr(env.memory.HEAPU8,j+n*8)),text(ref.HEAPU8,ptr(ref.HEAPU8,c+n*8)),label+' text '+name+n);checks++;
 }
 for(const [i,name]of ['WIN_MESSAGE','WIN_STATUS','WIN_MAP','WIN_INVEN'].entries()){assert.deepEqual(env.memory.readBytes(env.requireGlobal(name),4),ref.HEAPU8.slice(Number(ref._probe_status_storage(i+10)),Number(ref._probe_status_storage(i+10))+4),label+' '+name);checks++;}
 for(const [slot,name]of [[6,'status_fieldnm'],[7,'status_fieldfmt'],[8,'status_vals']]){
  const c=Number(ref._probe_windows_storage(slot)),j=env.requireGlobal(name);for(let i=0;i<27;i++){const jp=ptr(env.memory.HEAPU8,j+i*8),cp=ptr(ref.HEAPU8,c+i*8);assert.equal(jp?text(env.memory.HEAPU8,jp):null,cp?text(ref.HEAPU8,cp):null,label+' general window status '+name+i);checks++;}
 }
 for(let i=0;i<54;i++){
 const offset=metadata.instance_globals_b.fields.blstats.offset+i*metadata.istat_s.size+metadata.istat_s.fields.val.offset;
 allocation(ptr(ref.HEAPU8,Number(ref._probe_status_storage(6))+offset),ptr(env.memory.HEAPU8,env.requireGlobal('gb')+offset),label+' allocated field '+i);
}
for(let i=0;i<27;i++)allocation(ptr(ref.HEAPU8,Number(ref._probe_windows_storage(8))+i*8),ptr(env.memory.HEAPU8,env.requireGlobal('status_vals')+i*8),label+' allocated window text '+i);
const cActive=Number(ref._probe_windows_storage(9));assert.deepEqual(env.memory.readBytes(env.requireGlobal('status_activefields'),27),ref.HEAPU8.slice(cActive,cActive+27),label+' active window fields');checks++;
 const tty=Object.keys(names).indexOf('tty_status'),ctty=Number(ref._probe_wintty_global(tty));assert.deepEqual(env.memory.readBytes(env.requireGlobal('tty_status'),metadata.tty_status_fields.size*54),ref.HEAPU8.slice(ctty,ctty+metadata.tty_status_fields.size*54),label+' complete tty field state');checks++;
 for(let i=0;i<20;i++){
  const c=ptr(ref.HEAPU8,nativeGlobal('wins')+i*8),j=ptr(env.memory.HEAPU8,env.requireGlobal('wins')+i*8);assert.equal(!!j,!!c,label+' window slot '+i);checks++;
  if(!c)continue;assert.deepEqual(snapshot(env.memory.HEAPU8,j,'WinDesc'),snapshot(ref.HEAPU8,c,'WinDesc'),label+' initialized window descriptor '+i);checks++;
  const wf=metadata.WinDesc.fields,cv=new DataView(ref.HEAPU8.buffer),jv=env.memory.view,type=cv.getInt16(c+wf.type.offset,true),rows=Number(cv.getBigInt64(c+wf.rows.offset,true)),maxrow=Number(cv.getBigInt64(c+wf.maxrow.offset,true)),n=type===layouts.wintty.NHW_MESSAGE?rows:maxrow;
  const cd=ptr(ref.HEAPU8,c+wf.datlen.offset),jd=ptr(env.memory.HEAPU8,j+wf.datlen.offset),ca=ptr(ref.HEAPU8,c+wf.data.offset),ja=ptr(env.memory.HEAPU8,j+wf.data.offset);
  if(cd&&n){assert.deepEqual(env.memory.readBytes(jd,n*2),ref.HEAPU8.slice(cd,cd+n*2),label+' buffered window row lengths '+i);checks++;for(let k=0;k<n;k++){assert.equal(!!ptr(env.memory.HEAPU8,ja+k*8),!!ptr(ref.HEAPU8,ca+k*8),label+' buffered window row allocation '+i+':'+k);checks++;}}
 }
 for(let i=0;i<2;i++){assert.deepEqual(snapshot(env.memory.HEAPU8,i?gameWindows.nosound:gameWindows.procs,'sound_procs'),snapshot(ref.HEAPU8,ref._probe_status_sound(i),'sound_procs'),label+' original sound state '+i);checks++;}
}
statusState('before game windows');
env.services.init_sound_disp_gamewindows();ref._init_sound_disp_gamewindows();statusState('after game windows');
assert.equal(env.memory.view.getInt8(env.requireGlobal('gb')+metadata.instance_globals_b.fields.blinit.offset),1,'real status initialization ran');
for(const [poly,show,bar]of [[0,0,0],[1,1,1],[0,1,0]]){
 for(const name of ['showexp','showvers','weaponstatus','armorstatus','terrainstatus','time']){
  const f=metadata.flag.fields[name];env.ctypes.setField('struct flag',env.requireGlobal('flags'),name,f.ctype.replace(new RegExp(' '+name+'$'),''),show);ref.HEAPU8[Number(ref._probe_startup_global(0))+f.offset]=show;
 }
 const hpf=metadata.instance_flags.fields.wc2_hitpointbar;env.ctypes.setField('struct instance_flags',env.requireGlobal('iflags'),'wc2_hitpointbar','boolean',bar);ref.HEAPU8[Number(ref._probe_startup_global(20))+hpf.offset]=bar;
 const u=env.requireGlobal('u'),cu=Number(ref._probe_hero_global(3)),um=metadata.you.fields.umonnum.offset;env.memory.view.setInt32(u+um,poly,true);new DataView(ref.HEAPU8.buffer).setInt32(cu+um,poly,true);
 env.services.status_initialize(1);ref._status_initialize(1);statusState('reassess '+poly+':'+show);
}

const H=layouts.hack,rd=metadata.mkroom,ud=metadata.you,svr=env.requireGlobal('svr'),csr=Number(ref._probe_decl_global(declRows.findIndex(row=>row.name==='svr'))),svl=env.requireGlobal('svl');
function room(i,lx,hx,ly,hy,type){ref._probe_movement_room(i,lx,hx,ly,hy,type);const p=env.ctypes.locate('struct instance_globals_saved_r',svr,'rooms').at+i*rd.size;env.memory.memset(p,0,rd.size);for(const [name,v]of Object.entries({lx,hx,ly,hy,rtype:type}))env.ctypes.setField('struct mkroom',p,name,rd.fields[name].ctype.replace(new RegExp(' '+name+'$'),''),v);}
function cell(x,y,type,room,edge){ref._probe_movement_cell(x,y,type,room,edge);const locations=env.ctypes.locate('struct instance_globals_saved_l',svl,'level').at+metadata.dlevel_t.fields.locations.offset,p=locations+(x*H.ROWNO+y)*metadata.rm.size;for(const [name,value]of Object.entries({typ:type,roomno:room,edge}))env.ctypes.setField('struct rm',p,name,metadata.rm.fields[name].ctype.replace(new RegExp(' '+name+'$'),''),value);}
const ju=env.requireGlobal('u'),cu=Number(ref._probe_hero_global(3));
function hero(x,y){for(const [name,v]of Object.entries({ux:x,uy:y})){env.ctypes.setField('struct you',ju,name,'short',v);new DataView(ref.HEAPU8.buffer).setInt16(cu+ud.fields[name].offset,v,true);}}
function roomState(label){for(const name of ['urooms','urooms0','uentered','ushops','ushops0','ushops_entered','ushops_left']){const off=ud.fields[name].offset;assert.deepEqual(env.memory.readBytes(ju+off,5),ref.HEAPU8.slice(cu+off,cu+off+5),label+' '+name);checks++;}}
for(let i=0;i<3;i++)room(i,2+i*8,7+i*8,2,8,i===1?H.SHOPBASE:H.OROOM);
for(let x=1;x<=25;x++)for(let y=1;y<=10;y++)cell(x,y,H.ROOM,0,0);
for(let i=0;i<3;i++)for(let x=2+i*8;x<=7+i*8;x++)for(let y=2;y<=8;y++)cell(x,y,H.ROOM,H.ROOMOFFSET+i,0);
for(const [x,y]of [[1,1],[3,3],[11,3],[19,3],[3,3],[1,1],[11,3]]){
 hero(x,y);
 for(const type of [0,H.SHOPBASE,H.OROOM]){const j=env.services.in_rooms(x,y,type),c=ref._in_rooms(x,y,type);assert.equal(text(env.memory.HEAPU8,j),text(ref.HEAPU8,c),'source room membership '+x+':'+y+':'+type);checks++;}
 movement.call('move_update',0);ref._probe_movement_update(0);roomState('move '+x+':'+y);
}
movement.call('move_update',1);ref._probe_movement_update(1);roomState('new-level room reset');
hero(3,3);env.services.check_special_room(0);ref._check_special_room(0);roomState('ordinary-room entry');
hero(1,1);env.services.check_special_room(1);ref._check_special_room(1);roomState('new-level entry');
for(const [x,y,shared]of [[8,4,H.SHARED],[9,4,H.SHARED_PLUS],[16,5,H.SHARED],[17,5,H.SHARED_PLUS]]){
 cell(x,y,H.DOOR,shared,1);hero(x,y);
 for(const type of [0,H.SHOPBASE,H.SHOPBASE+1]){const j=movement.call('in_rooms',x,y,type),c=ref._in_rooms(x,y,type);assert.equal(text(env.memory.HEAPU8,j),text(ref.HEAPU8,c),'shared/edge source room membership');checks++;}
 movement.call('move_update',0);ref._probe_movement_update(0);roomState('shared edge '+x+':'+y);
}
for(const n of [-25,-10,-1,0,1,10,25])for(const d of [1,2,3,7]){assert.equal(env.services.rounddiv(n,d),ref._rounddiv(BigInt(n),d),'source rounded division');checks++;}
for(const n of [0,1,0xffffffff]){const j=env.services.uint_to_any(n),c=ref._uint_to_any(n);assert.deepEqual(env.memory.readBytes(j,8),ref.HEAPU8.slice(Number(c),Number(c)+8),'shared uint_to_any union');checks++;}
for(const n of [-1n,0n,0x123456789abcdefn]){const j=env.services.long_to_any(n),c=ref._long_to_any(n);assert.deepEqual(env.memory.readBytes(j,8),ref.HEAPU8.slice(Number(c),Number(c)+8),'shared long_to_any union');checks++;}
const buffers=[...reverseAllocatedAliases.keys()];assert.ok(buffers.length>54,'independent source allocations observed');for(const p of buffers)assert.ok(env.memory.live.has(p),'status buffer is live before finish');
env.services.status_finish();ref._status_finish();statusState('source status cleanup');
for(const p of buffers){assert.ok(!env.memory.live.has(p),'source status cleanup freed each owned allocation');checks++;}
console.log(`PASS: ${checks} original-C room membership/entry/bookkeeping, movement data and connected window/status comparisons; full-game lifecycle remains unfinished.`);
