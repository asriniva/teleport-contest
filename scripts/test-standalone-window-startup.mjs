import assert from 'node:assert/strict';
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/standalone/environment.js';
import {createNativeTerminal} from '../js/platform/darwin/terminal.js';
import {createTerminalDevices} from '../js/standalone/unix-terminal.js';
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),seed=1n;
const directory=path.resolve(process.env.STANDALONE_WINDOW_STARTUP_ORACLE||'.cache/standalone-window-startup-v8');
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

ref._probe_level_init(seed);const window=env.enableWindowSystem(layouts),metadata=JSON.parse(fs.readFileSync('js/standalone/records.json')).records;
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
assert.throws(()=>env.services.tty_init_nhwindows(argc,argv),/Unresolved standalone function copyright_banner_line/);
assert.throws(()=>ref._probe_window_init(),/Aborted/);assert.ok(errors.some(s=>s.includes('Unconnected C boundary: copyright_banner_line')),'same native version boundary');
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

console.log(`PASS: ${checks} original-C virtual device, window procedure and connected Unix terminal comparisons; startup stops at original VERSION banner owner.`);
