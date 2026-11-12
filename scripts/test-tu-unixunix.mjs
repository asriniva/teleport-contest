// Emscripten diagnostic only: actual prepared C vs imported JS in a controlled dependency world.
import assert from 'node:assert/strict';
import {readFileSync,writeFileSync} from 'node:fs';
import {resolve} from 'node:path';
import {fileURLToPath,pathToFileURL} from 'node:url';
if(process.env.TELEPORT_NATIVE_TESTS!=='0') throw Error('UNIXUNIX has no native reference fixture; Emscripten results cannot be labeled native.');
const artifactDir=resolve(process.env.UNIXUNIX_PROBE_DIR??fileURLToPath(new URL('../.cache/tu-probes',import.meta.url)));
const {default:refFactory}=await import(pathToFileURL(resolve(artifactDir,'unixunix-reference.mjs')));
const {default:hybridFactory}=await import(pathToFileURL(resolve(artifactDir,'unixunix-hybrid.mjs')));
const {callUnixunix,createUnixunixEnvironment}=await import(process.env.UNIXUNIX_RUNTIME??'../js/nethack/bindings/unixunix.js');
const read=p=>JSON.parse(readFileSync(new URL(p,import.meta.url))),schema=read('../nethack-c/wasm/tu-fragments/unixunix-schema.json'),functions=read('../nethack-c/wasm/tu-fragments/unixunix-source-metadata.json').functions,names=functions.map(f=>f.name),kinds=Object.keys(schema.schema),regionNames=['scratch','env_shell','env_home','markers','fullpath','authorized','name','fixture_tty_name','files','fds','statevents'],covered=new Set();
let dispatchHook=null,lastServices;
const dispatch=(services,name,...args)=>{lastServices=services;return dispatchHook?dispatchHook(services,name,...args):callUnixunix(services,name,...args);};
const output=[[],[]],ref=await refFactory({print:s=>output[0].push(s),printErr:s=>output[0].push(s)}),hybrid=await hybridFactory({nethackPorted:{unixunix:dispatch},print:s=>output[1].push(s),printErr:s=>output[1].push(s)}),mods=[ref,hybrid];
const L=Object.fromEntries(schema.layoutKeys.map((k,i)=>[k,Number(ref._teleport_unixunix_layout(i))]));for(let i=0;i<schema.layoutKeys.length;i++)assert.equal(hybrid._teleport_unixunix_layout(i),ref._teleport_unixunix_layout(i));
assert.equal(L['size:struct stat'],104);assert.equal(L['size:struct timespec'],16);
const global=(m,n)=>Number(m._teleport_unixunix_global(schema.globals.findIndex(g=>g.name===n))),ptr=(m,i)=>Number(m._probe_pointer(i));
const fi=(k,f)=>{const i=schema.schema[k]?.fields.findIndex(x=>x.name===f);assert.ok(i>=0,k+'.'+f);return i;};
const addr=(m,p,k,f)=>Number(m._teleport_unixunix_address(kinds.indexOf(k),BigInt(p),fi(k,f)));
const get=(m,p,k,f)=>m._teleport_unixunix_read(kinds.indexOf(k),BigInt(p),fi(k,f));
const set=(m,p,k,f,v)=>m._teleport_unixunix_write(kinds.indexOf(k),BigInt(p),fi(k,f),BigInt.asUintN(64,BigInt(v)));
const setter=fn=>mods.forEach(fn),option=(i,v)=>setter(m=>m._probe_option(i,v)),text=(m,s,p=ptr(m,0)+2048)=>(m.stringToUTF8(s,p,1024),p),answer=c=>setter(m=>m._probe_answer(typeof c==='string'?c.charCodeAt(0):c)),chars=s=>setter(m=>{for(const c of s)m._probe_char(c.codePointAt(0));}),root=(m,n,k,f)=>addr(m,global(m,n),k,f),lock=(m,s)=>m.stringToUTF8(s,root(m,'gl','instance_globals_l','lock'),46),now=n=>setter(m=>m._probe_now(BigInt(n)));
const file=(m,path,stamp,bytes=4)=>m._probe_file(BigInt(text(m,path)),1,BigInt(stamp),bytes),fileBoth=(path,stamp,bytes=4)=>mods.map(m=>file(m,path,stamp,bytes));
const knownRegions=m=>[...schema.globals.filter(g=>!['stdout','windowprocs'].includes(g.name)).map(g=>({name:g.name,p:global(m,g.name),size:Number(m._probe_global_size(schema.globals.indexOf(g)))})),...regionNames.map((name,i)=>({name,p:ptr(m,i),size:Number(m._probe_region_size(i))})),{name:'source.buf',p:Number(m._probe_sourcebuf()),size:104}];
function snapshot(m){const rs=knownRegions(m),regions=rs.map(r=>({...r,bytes:m.HEAPU8.slice(r.p,r.p+r.size),pointers:[]}));
 // Only the selected compiler-typed sysopt.shellers pointer is mutable here.
 // All filesystem/stat/fd/scratch scalar and padding bytes remain raw.
 const at=addr(m,global(m,'sysopt'),'sysopt_s','shellers'),v=new DataView(m.HEAPU8.buffer).getBigUint64(at,true),target=v===0n?null:rs.find(r=>v>=BigInt(r.p)&&v<BigInt(r.p+r.size)),region=regions.find(r=>at>=r.p&&at+8<=r.p+r.size);
 if(v===0n||target){region.pointers.push([at-region.p,v===0n?'0':target.name+'+'+(v-BigInt(target.p))]);region.bytes.fill(0,at-region.p,at-region.p+8);}
 const handlers=Array.from({length:64},(_,i)=>{const kind=m._probe_handler(i);return kind===3?'UNKNOWN:'+BigInt.asUintN(64,m._probe_handler_raw(i)):kind;});
 return{regions:regions.map(r=>({name:r.name,bytes:Buffer.from(r.bytes).toString('hex'),pointers:r.pointers})),trace:m.UTF8ToString(Number(m._probe_trace())),errno:m._probe_errno(),outcome:m._probe_outcome(),files:m._probe_file_count(),fds:Array.from({length:m._probe_fd_count()},(_,i)=>m._probe_fd_open(i)),events:m._probe_event_count(),handlers};
}
let checks=0;function reset(){setter(m=>m._probe_reset());output.forEach(a=>a.length=0);}
function compare(label){const a=snapshot(ref),b=snapshot(hybrid);try{assert.deepEqual(b,a,label);assert.deepEqual(output[1],output[0],label+' native output');checks++;}catch(e){writeFileSync(resolve(artifactDir,'unixunix-mismatch.json'),JSON.stringify({label,ref:a,hybrid:b},null,2));throw e;}}
function action(name,args=[]){covered.add(name);const result=mods.map((m,i)=>{const a=typeof args==='function'?args(m,i):args,sp=m.stackSave();try{return m._probe_action(names.indexOf(name),BigInt(a[0]??0),BigInt(a[1]??0));}catch(e){console.error('UNIXUNIX unexpected',name,i,a,e);throw e;}finally{assert.equal(m.stackSave(),sp,name+' stack cleanup');}});assert.equal(result[1],result[0],name+' result');compare(name);return result;}
mods.forEach(m=>assert.ok(m._probe_done_id()>1n,'actual native done1 ID distinct from NULL/SIG_IGN'));
console.log('UNIXUNIX controlled signal function IDs',mods.map(m=>String(m._probe_done_id())).join(','),'NULL=0 SIG_IGN=1; diagnostic table-base=2 only');
reset();compare('initial controlled Unix state');
reset();const ids=fileBoth('/old',0);setter((m,i)=>m._probe_open(ids[i]));action('veryold',[3]);
reset();fileBoth('/1/fixture.0',0);action('eraseoldlocks');
reset();action('getlock');
reset();setter(m=>lock(m,'fixture.0'));fileBoth('/1/fixture.0',999999);chars('y');action('ask_about_panic_save');
reset();action('regularize',m=>[text(m,'a.b/c d')]);
reset();option(17,-1);action('dosh');
reset();option(17,99);action('child',[1]);
reset();fileBoth('/present',23);action('file_exists',m=>[text(m,'/present')]);
assert.equal(covered.size,8);console.log('PASS UNIXUNIX baseline',checks,'comparisons; all8 actual configured functions; extended cases pending.');
// Time64 threshold, short/error reads, ignored INSURANCE size and persistent
// stat backing. NETWORK deliberately suppresses any kill(pid,0) dependency.
for(const delta of [259199n,259200n,259201n])for(const base of [1000000n,0x20000000000001n]){reset();now(base);fileBoth('/lock',base-delta);setter(m=>m._probe_open(0));assert.equal(action('veryold',[3])[0],delta<259200n?0n:1n);}
for(const failure of [1,2,3]){reset();fileBoth('/lock',999999);setter(m=>m._probe_open(0));option(failure,failure===3?2:1);action('veryold',[3]);}
reset();fileBoth('/lock',0,17);setter(m=>m._probe_open(0));action('veryold',[3]);option(1,1);action('veryold',[3]);
for(const fail of [0,1]){reset();fileBoth('/1/fixture.0',0);fileBoth('/1/fixture.3',0);option(4,fail);setter(m=>set(m,global(m,'program_state'),'sinfo','preserve_locks',1));action('eraseoldlocks');assert.equal((ref.UTF8ToString(Number(ref._probe_trace())).match(/unlink\(/g)??[]).length,514,'513 levels then lock0');}
// TTY/environment bypass retains the inherited NOMUX patch and short circuit.
for(const [notty,markers,other]of [[1,0,0],[1,1,0],[1,1,1],[0,0,0]]){reset();option(5,notty);option(6,markers);if(other)setter(m=>m.stringToUTF8('other',ptr(m,7),16));action('getlock');}
for(const opt of [9,11,13,14,15,12]){reset();option(opt,opt===15?2:1);action('getlock');}
reset();option(10,-1);setter(m=>m.stringToUTF8('hero.x /',root(m,'svp','instance_globals_saved_p','plname'),32));action('getlock');
// Five source gotos: missing numbered lock, stale numbered/uid lock, ordinary
// missing uid lock (baseline), and the native UI/raw destroy-confirmed join.
reset();setter(m=>set(m,global(m,'gl'),'instance_globals_l','locknum',2));fileBoth('/1/aixture.0',999999);action('getlock');
reset();setter(m=>set(m,global(m,'gl'),'instance_globals_l','locknum',1));fileBoth('/1/aixture.0',0);action('getlock');
reset();fileBoth('/1/0hero.0',0);action('getlock');
for(const ui of [0,1])for(const destroy of [0,1]){reset();fileBoth('/1/0hero.0',999999);setter(m=>set(m,global(m,'iflags'),'instance_flags','window_inited',ui));if(ui)answer(destroy?'y':'n');else chars(destroy?'y extra\n':'n\n');action('getlock');}
reset();fileBoth('/1/0hero.0',999999);option(4,1);setter(m=>set(m,global(m,'iflags'),'instance_flags','window_inited',1));answer('y');action('getlock');
reset();setter(m=>set(m,global(m,'gl'),'instance_globals_l','locknum',26));for(let i=0;i<25;i++)fileBoth('/1/'+String.fromCharCode(97+i)+'ixture.0',999999);action('getlock');assert.equal(get(ref,global(ref,'gl'),'instance_globals_l','locknum'),25n);assert.equal((ref.UTF8ToString(Number(ref._probe_trace())).match(/open\(/g)??[]).length,25,'native25 lock cap');
// Valid panic-save caller has already acquired the native level0 lock.
for(const ui of [0,1])for(const choice of ['y','Y','n','q','\x1b','']){reset();setter(m=>{lock(m,'fixture.0');set(m,global(m,'iflags'),'instance_flags','window_inited',ui);});fileBoth('/1/fixture.0',999999);if(ui)answer(choice||-1);else chars(choice);action('ask_about_panic_save');}
for(const s of ['','abc','... / //  abc','a_very_long_name_with_more_than_fourteen_characters . /','./././']){reset();action('regularize',m=>[text(m,s)]);}
// Process primitives are native fixture results; no actual host process executes.
for(const authorization of ['null','empty','deny','yes'])for(const forkResult of [-1,0,47]){reset();if(authorization==='null')setter(m=>set(m,global(m,'sysopt'),'sysopt_s','shellers',0));if(authorization==='empty')setter(m=>m.HEAPU8[ptr(m,5)]=0);if(authorization==='deny')option(16,1);option(17,forkResult);action('dosh');}
reset();option(17,0);option(7,1);action('dosh');
for(const f of [-1,0,47])for(const wt of [0,1])for(const wizard of [0,1]){reset();option(17,f);option(19,-1);option(10,-1);setter(m=>set(m,global(m,'flags'),'flag','debug',wizard));action('child',[wt]);if(f>0){assert.equal(ref._probe_handler(2),2,'real retained done1 identity');assert.equal(ref._probe_handler(3),wizard?0:1);setter(m=>m._probe_signal_run(2,9));compare('retained native done1 callback after return');}}
for(const present of [0,1]){reset();if(present)fileBoth('/file',0);action('file_exists',m=>[text(m,'/file')]);}
console.log('PASS UNIXUNIX extended',checks,'comparisons; time64/stat104/514 cleanup/native lock cap/gotos/raw+UI/TTY+NOMUX/process+retained signals/regularize.');

// Actual native fstat reentry writes the shared source-owned buf, then the
// outer veryold reads that same backing rather than a copied/stat-projected value.
reset();fileBoth('/outer',0);fileBoth('/inner',999999);setter(m=>{m._probe_open(0);m._probe_open(1);});option(71,4);assert.equal(action('veryold',[3])[0],0n);assert.equal(ref._probe_event_count(),2);
// A native window callback reenters with changed services. A deliberately
// thrown nested memory access also checks both stack and services restoration.
reset();option(17,47);option(70,1);setter(m=>m.stringToUTF8('a.b/c d',ptr(m,0),32));let nested=0,outerReads=0,throws=0;
dispatchHook=(services,name,...args)=>{
 if(name==='child')return callUnixunix({...services,abiRead:(...a)=>{outerReads++;return services.abiRead(...a);}},name,...args);
 if(name==='regularize'){
  nested++;const sp=services.stackSave();
  assert.throws(()=>callUnixunix({...services,heap:()=>{throws++;throw Error('UNIXUNIX nested exception witness');}},name,...args),/nested exception witness/);
  assert.equal(services.stackSave(),sp,'exception restores nested native stack');
  return callUnixunix({...services,abiRead:()=>{throw Error('UNIXUNIX stale nested services');}},name,...args);
 }
 return callUnixunix(services,name,...args);
};
try{action('child',[1]);}finally{dispatchHook=null;}assert.equal(nested,1);assert.ok(outerReads>1);assert.equal(throws,1);
reset();action('getlock');
// Memory grows inside the real native dependency call, invalidating old views.
reset();fileBoth('/growth',999999);setter(m=>m._probe_open(0));const oldBuffers=mods.map(m=>m.HEAPU8.buffer);let grew=false;
dispatchHook=(services,name,...args)=>callUnixunix({...services,fstat:(...a)=>{hybrid._probe_growth();grew=true;return services.fstat(...a);}},name,...args);
// Grow the reference at the matching boundary through its explicit allocator;
// the reference's fstat has no JS hook and the contents remain unchanged.
ref._probe_growth();try{action('veryold',[3]);}finally{dispatchHook=null;}assert.ok(grew);mods.forEach((m,i)=>assert.notEqual(m.HEAPU8.buffer,oldBuffers[i]));
// Raw scalar and padding bytes are never interpreted as selected pointers.
reset();setter(m=>new DataView(m.HEAPU8.buffer).setBigUint64(ptr(m,0)+4080,0xfedcba9876543210n,true));compare('unknown raw64 scalar witness');
const scalarNativeAddress=BigInt(ptr(ref,0));setter(m=>new DataView(m.HEAPU8.buffer).setBigUint64(ptr(m,0)+4072,scalarNativeAddress,true));compare('scalar numerically equal to native address remains raw');assert.equal(new DataView(hybrid.HEAPU8.buffer).getBigUint64(ptr(hybrid,0)+4072,true),scalarNativeAddress);
const witness=ptr(hybrid,0)+4080;hybrid.HEAPU8[witness]^=1;assert.throws(()=>assert.deepEqual(snapshot(hybrid),snapshot(ref)),assert.AssertionError);hybrid.HEAPU8[witness]^=1;
// Unsafe native addresses are rejected before dereference; no Number rounding.
const high={...lastServices,abiGlobal:()=>0x20000000000001n};assert.throws(()=>callUnixunix(high,'getlock'),/exact address range/);
reset();action('getlock');
reset();fileBoth('/per-module',999999);setter(m=>m._probe_open(0));action('veryold',[3]);const beforeSeparate=snapshot(hybrid).regions.find(x=>x.name==='source.buf').bytes;
const fresh=await hybridFactory({nethackPorted:{unixunix:dispatch},print:()=>{},printErr:()=>{}});fresh._probe_reset();fresh.stringToUTF8('x.y/z q',Number(fresh._probe_pointer(0)),32);fresh._probe_action(names.indexOf('regularize'),fresh._probe_pointer(0),0n);assert.equal(fresh.UTF8ToString(Number(fresh._probe_pointer(0))),'x_y_z_q');
assert.equal(Buffer.from(hybrid.HEAPU8.slice(Number(hybrid._probe_sourcebuf()),Number(hybrid._probe_sourcebuf())+104)).toString('hex'),beforeSeparate,'Module backing remains separate');
console.log('PASS UNIXUNIX Emscripten diagnostic',checks,'top-level comparisons; all8; controlled reentry/exception/growth/Module/raw64/native callback lifetimes. Native reference pending.');

reset();option(17,47);setter(m=>set(m,global(m,'flags'),'flag','debug',1));let signalReturns=0;
dispatchHook=(services,name,...args)=>callUnixunix({...services,teleport_native_signal:(sig,fn)=>{const old=hybrid._probe_handler_raw(sig),result=services.teleport_native_signal(sig,fn);assert.equal(BigInt(result),old,'typed actual native previous-handler return');signalReturns++;return result;}},name,...args);
try{action('child',[1]);}finally{dispatchHook=null;}assert.equal(signalReturns,4);setter(m=>m._probe_signal_run(2,11));compare('actual retained done1 plus native function-pointer return');
console.log('PASS UNIXUNIX final Emscripten-only diagnostic',checks,'top-level comparisons; native-host authoritative proof PENDING.');

// Separate JS allocation-contract witness on explicitly seeded native memory.
// This does not assign a portable value to original C uninitialized autos.
const contractModule=await hybridFactory({nethackPorted:{unixunix:dispatch},print:()=>{},printErr:()=>{}});contractModule._probe_reset();const contractServices=lastServices,contractFrame=contractServices.stackSave();
try{
 const at=contractServices.stackAlloc(16),env=createUnixunixEnvironment({...contractServices,stackAlloc:()=>at});
 const seed=()=>contractModule.HEAPU8.fill(0xA7,at,at+16),bytes=()=>Array.from(contractModule.HEAPU8.slice(at,at+16));
 for(const t of ['long long','int']){seed();assert.equal(env.local(t).address,at);assert.deepEqual(bytes(),Array(16).fill(0xA7),'uninitialized cell allocation must not write seeded native bytes');}
 seed();env.local('int',0);assert.deepEqual(bytes(),[0,0,0,0,...Array(12).fill(0xA7)],'explicit zero initializer writes exactly int4');
 seed();env.local('long long',0x20000000000001n);assert.equal(new DataView(contractModule.HEAPU8.buffer).getBigInt64(at,true),0x20000000000001n);assert.deepEqual(bytes().slice(8),Array(8).fill(0xA7));
}finally{contractServices.stackRestore(contractFrame);}
console.log('PASS UNIXUNIX seeded native-memory JS local allocation contract; uninitialized preserves bytes, explicit int4/time8 initializer writes exact extent. Separate from100 C/JS comparisons.');
