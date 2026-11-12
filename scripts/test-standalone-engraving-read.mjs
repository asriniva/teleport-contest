// Real engraving reading: original ENGRAVE/DUNGEON/PLINE/TTY and shared state.
import assert from 'node:assert/strict';
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/standalone/environment.js';
import {createNativeTerminal} from '../js/platform/darwin/terminal.js';
import {encodeRecorderScreen} from '../js/wasm-replay-support.js';
import {C,R,T} from '../js/c-runtime/context.js';
Error.stackTraceLimit=50;
const referenceRoot=path.resolve(process.env.STANDALONE_REFERENCE_ROOT||'../teleport-contest'),directory=path.resolve(process.env.STANDALONE_ENGRAVING_READ_ORACLE||'.cache/standalone-engraving-read-v4');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json'))),sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');let hashes=0,comparisons=0,contracts=0;
for(const [p,h]of Object.entries(receipt.sourceSha256)){assert.equal(sha(p),h,'Changed C input '+p);hashes++;}for(const [p,h]of Object.entries(receipt.artifactSha256)){assert.equal(sha(path.join(directory,p)),h,'Changed C artifact '+p);hashes++;}
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),metadata=JSON.parse(fs.readFileSync('js/standalone/records.json')).records;
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs')));
function js(fn){const keys=['WebAssembly','fetch','XMLHttpRequest','WebSocket','Worker'],saved=keys.map(k=>Object.getOwnPropertyDescriptor(globalThis,k));let accesses=0;const forbidden=()=>{accesses++;throw new Error('Forbidden Wasm/network during engraving execution');};keys.forEach(k=>Object.defineProperty(globalThis,k,{configurable:true,value:k==='WebAssembly'?new Proxy(Object.create(null),{get:forbidden}):forbidden}));try{return fn();}finally{keys.forEach((k,i)=>saved[i]?Object.defineProperty(globalThis,k,saved[i]):delete globalThis[k]);assert.equal(accesses,0);assert.deepEqual([C,R,T],[undefined,undefined,undefined]);contracts+=2;}}
const equal=(a,b,label)=>{assert.deepEqual(a,b,label);comparisons++;};
const text=(heap,p)=>{p=Number(p);if(!p)return null;let end=p;while(heap[end])end++;return Buffer.from(heap.slice(p,end)).toString('latin1');};
async function pair(seed){const role=0,roleplay=0,entry=fs.readFileSync('nethack-c/wasm/terminfo/x/xterm-256color'),errors=[],nativeTerminal=createNativeTerminal(),ccaptures=[],ckeys=[],jkeys=[];const nextKey=(seen,output)=>{assert.ok(seen.length<256,'Bounded explicit More input');assert.match(Buffer.from(output).toString('latin1').slice(-256),/--More--|\(end\)/);seen.push({key:32,terminalBytes:output.length,sha256:crypto.createHash('sha256').update(Buffer.from(output)).digest('hex')});return 32;};
 const ref=await factory({teleportCapture:(screen,x,y,animation)=>ccaptures.push({screen:encodeRecorderScreen(screen),cursor:[x,y,1],animation:Boolean(animation)}),teleportReadKey:()=>nextKey(ckeys,coutput),nethackPorted:{nativeTerminal:(services,name,...args)=>nativeTerminal({...services,stackAlloc:n=>{const p=services.stackAlloc(n);services.heap().fill(0,p,p+n);return p;}},name,...args)},print:()=>{},printErr:s=>errors.push(s),preRun:[m=>{m.FS.mkdirTree('/nethack/terminfo/x');m.FS.writeFile('/nethack/terminfo/x/xterm-256color',entry);} ]});
 for(const [name,value]of Object.entries({NOMUX_MARKERS:'1',TERM:'xterm-256color',TERMINFO:'/nethack/terminfo',LINES:'24',COLUMNS:'80'})){const p=BigInt(ref._malloc(BigInt(name.length+value.length+2)));ref.HEAPU8.set(Buffer.from(name+'\0'+value+'\0'),Number(p));ref._setenv(p,p+BigInt(name.length+1),1);ref._free(p);}
 const coutput=[],tty=ref.FS.getStream(1).tty,put=tty.ops.put_char;tty.ops={...tty.ops,put_char:(t,c)=>{if(c!==null)coutput.push(c);return put(t,c);}};
 const inputTTY=ref.FS.getStream(0).tty;inputTTY.ops={...inputTTY.ops,get_char:()=>32};
 const built=js(()=>{
 const env=createStandaloneEnvironment({initialBytes:1024,maximumBytes:64*1024*1024,environment:{TERM:'xterm-256color',NOMUX_MARKERS:'1',NETHACK_RNGLOG:'/rng.log',NETHACK_FIXED_DATETIME:'20260102030405',NETHACK_SEED:seed.toString()}});
 const stdio=env.enableStdio();env.enableDecl(layouts.decl);env.call('decl','program_state_init');env.call('decl','decl_globals_init');env.enableDrawing(layouts.drawing);env.enableObjects(layouts.objects);env.call('objects','objects_globals_init');env.enableMonst(layouts.monst);env.call('monst','monst_globals_init');env.enableSerialization(layouts);env.enableRnd(layouts.rnd,{seed});env.call('rnd','rng_log_init');env.enableAddressPort('dungeon',{only:['ledger_no','maxledgerno']});env.enableObjectState(layouts);env.enableObjectRecords(layouts);env.enableItemInventory(layouts);env.enableTimers(layouts);env.enableItemNaming(layouts);const group=env.enableMonsterSelection(layouts);const decl=JSON.parse(fs.readFileSync('js/standalone/decl-storage.json')).globals,before=decl.map(r=>env.memory.readBytes(env.requireGlobal(r.name),r.bytes));const creation=env.enableMonsterCreation(layouts);decl.forEach((r,i)=>assert.deepEqual(env.memory.readBytes(env.requireGlobal(r.name),r.bytes),before[i],'enabling creation preserves '+r.name));

 const startup=env.enableGameStartup(layouts);env.call('sys','sys_early_init');
env.enableHeroStartup(layouts);env.enableWorldPosition(layouts);env.enableLuaSandbox(layouts);env.enableDisplayStartup(layouts);
for(const name of fs.readdirSync(referenceRoot+'/.cache/wasm64-build/tree/dat').filter(n=>n.endsWith('.lua')))env.filesystem.writeFile(name,fs.readFileSync(referenceRoot+'/.cache/wasm64-build/tree/dat/'+name));
for(const name of ['epitaph','engrave','rumors','bogusmon','oracles'])env.filesystem.writeFile(name,fs.readFileSync(referenceRoot+'/.cache/wasm64-build/tree/dat/'+name));
env.filesystem.writeFile('sysconf',fs.readFileSync(referenceRoot+'/.cache/wasm64-build/assets/sysconf'));
Object.assign(env.services.flags,{initrole:role,initrace:0,initgend:0,initalign:0,female:0,pantheon:-1});env.services.strcpy(startup.role.svp.plname,env.services.literal('Ada'));
env.enableLevelStartup(layouts);const contents=env.enableLevelContents(layouts);env.services.vision_init();const window=env.enableWindowSystem(layouts);env.enableVersionInfo(layouts);env.enableOptions(layouts);env.enableSymbols(layouts);env.enableGlyphs(layouts);env.enableCommands(layouts);env.enableConfiguration(layouts);env.enableFiles(layouts);env.enableStatus(layouts);env.enableGameWindows(layouts);env.enableMovement(layouts);env.enablePets(layouts);env.enableMonsterMovement(layouts);env.enableMonsterLifecycle(layouts);env.enableHeroEquipment(layouts);env.services.choose_windows('tty');env.services.initoptions();Object.assign(env.services.flags,{initrole:role,initrace:0,initgend:0,initalign:0,female:0,pantheon:-1});
for(const [i,name]of ['blind','nudist','deaf','pauper','reroll','reserved1','reserved2','reserved3'].entries())env.services.u.uroleplay[name]=(roleplay>>i)&1;
const argc=env.memory.calloc(1,4),argv=env.memory.calloc(2,8);env.memory.view.setInt32(argc,1,true);env.memory.view.setBigUint64(argv,BigInt(env.services.literal('nethack')),true);env.services.tty_init_nhwindows(argc,argv);env.services.init_sound_disp_gamewindows();env.enableTerminalInput(layouts,{readKey:()=>nextKey(jkeys,stdio.captured(1))});env.enableTerminalMessages(layouts);env.enableMessages(layouts);
 return {env,stdio,creation,startup,contents,window,jkeys};});
ref._probe_level_init(seed);const assets=referenceRoot+'/.cache/wasm64-build/tree/dat/';for(const name of fs.readdirSync(assets).filter(n=>n.endsWith('.lua')).concat(['epitaph','engrave','rumors','bogusmon','oracles']))ref.FS.writeFile(name,fs.readFileSync(assets+name));
for(const [key,value]of Object.entries({NETHACK_FIXED_DATETIME:'20260102030405',NETHACK_RNGLOG:'/rng.log',NETHACK_SEED:seed.toString()})){const p=ref._malloc(BigInt(key.length+value.length+2));ref.HEAPU8.set(Buffer.from(key+'\0'+value+'\0'),Number(p));ref._setenv(BigInt(p),BigInt(Number(p)+key.length+1),1);ref._free(BigInt(p));}
ref.FS.writeFile('sysconf',fs.readFileSync(referenceRoot+'/.cache/wasm64-build/assets/sysconf'));
const player=ref._malloc(4n);ref.HEAPU8.set(Buffer.from('Ada\0'),Number(player));ref._probe_startup_role_config(role,0,0,0,BigInt(player));ref._free(player);ref._vision_init();const type=ref._malloc(4n);ref.HEAPU8.set(Buffer.from('tty\0'),Number(type));ref._probe_window_select(BigInt(type));ref._free(type);ref._initoptions();const chosen=ref._malloc(4n);ref.HEAPU8.set(Buffer.from('Ada\0'),Number(chosen));ref._probe_startup_role_config(role,0,0,0,BigInt(chosen));ref._free(chosen);ref._probe_window_init();ref._init_sound_disp_gamewindows();

 return {...built,ref,coutput,errors,ccaptures,ckeys};
}
function engraving(heap,p){p=Number(p);if(!p)return null;const size=metadata.engr.size,data=Buffer.from(heap.slice(p,p+size)),texts=[];assert.equal(data.readBigUInt64LE(metadata.engr.fields.nxt_engr.offset),0n);for(let i=0;i<3;i++){const offset=metadata.engr.fields.engr_txt.offset+i*8,value=Number(data.readBigUInt64LE(offset));texts.push(text(heap,value));data.writeBigInt64LE(BigInt(value-p),offset);}return{data,texts};}
function rng(env,ref){const j=env.state('rnd').rnglist.map(row=>({init:row.init,n:row.rng_state.n,r:[...row.rng_state.r],m:[...row.rng_state.m],a:row.rng_state.a,b:row.rng_state.b,c:row.rng_state.c})),offsets=Array.from({length:7},(_,i)=>Number(ref._probe_level_rng_layout(i))),c=[0,1].map(i=>{const at=Number(ref._probe_level_rng_state(i)),v=new DataView(ref.HEAPU8.buffer);return{init:ref._probe_level_rng_initialized(i),n:Number(v.getBigUint64(at+offsets[1],true)),r:Array.from({length:256},(_,k)=>v.getBigUint64(at+offsets[2]+k*8,true)),m:Array.from({length:256},(_,k)=>v.getBigUint64(at+offsets[3]+k*8,true)),a:v.getBigUint64(at+offsets[4],true),b:v.getBigUint64(at+offsets[5],true),c:v.getBigUint64(at+offsets[6],true)};});equal(j,c,'Complete game/display ISAAC64 state and initialization');}
const seed=1n,{env,stdio,creation,startup,ref,coutput,errors,window,jkeys,ccaptures,ckeys}=await pair(seed),world=creation.environment,L=layouts.engrave;
js(()=>env.services.fflush(stdio.stdout));
const alignmentBefore=comparisons;
for(let value=-128;value<128;value++){
 const first=js(()=>env.services.align_str(value)),second=js(()=>env.services.align_str(value)),cFirst=ref._align_str(value),cSecond=ref._align_str(value);
 equal(js(()=>text(env.memory.HEAPU8,first)),text(ref.HEAPU8,cFirst),'Original INSIGHT align_str signed-char text '+value);
 equal([first===second,Boolean(first)],[cFirst===cSecond,Boolean(cFirst)],'INSIGHT repeated static pointer identity '+value);
}
for(const value of [-1024,-257,-256,255,256,257,1024,18446744073709551615n,-18446744073709551617n]){
 const input=Number(BigInt.asIntN(8,BigInt(value))),actual=js(()=>env.services.align_str(value));equal(js(()=>text(env.memory.HEAPU8,actual)),text(ref.HEAPU8,ref._align_str(input)),'INSIGHT outer C signed-char wrapping '+value);
}
const alignmentComparisons=comparisons-alignmentBefore;
function input(row){const {type,terrain=layouts.makemon.ROOM,blind=0,levitate=0,run=0,hallucinate=0,actual='test words',pristine=null,offset=0}=row;
 js(()=>{env.services.del_engr_at(10,10);Object.assign(world.u,{ux:10,uy:10,uswallow:0,uundetected:0,ustuck:0,usteed:0});world.gy.youmonst.data=creation.views.record('struct permonst',env.requireGlobal('mons')+layouts.makemon.PM_HUMAN*metadata.permonst.size);
 for(const [key,value]of [['BLINDED',blind],['LEVITATION',levitate],['FLYING',0],['HALLUC',hallucinate],['HALLUC_RES',0]]){const p=world.u.uprops[L[key]];p.intrinsic=BigInt(value);p.extrinsic=0n;p.blocked=0n;}
 world.levl[10][10].typ=terrain;world.levl[10][10].flags=0;world.svc.context.run=run;world.gm.multi=7n;if(type>=0)env.services.make_engr_at(10,10,actual,pristine===null?0:pristine,0n,type);
 });
 const cp=s=>{const bytes=Buffer.from(s+'\0'),p=BigInt(ref._malloc(BigInt(bytes.length)));ref.HEAPU8.set(bytes,Number(p));return p;},a=cp(actual),p=pristine===null?0n:cp(pristine);ref._probe_engraving_read_input(type,terrain,blind,levitate,run,hallucinate,a,p);ref._free(a);if(p)ref._free(p);
 if(offset){js(()=>{const e=env.start('world-engravings').environment.head_engr;e.engr_txt[L.actual_text]+=offset;});const c=Number(ref._probe_engraving_read_head())+metadata.engr.fields.engr_txt.offset+L.actual_text*8,v=new DataView(ref.HEAPU8.buffer);v.setBigUint64(c,v.getBigUint64(c,true)+BigInt(offset),true);}
}
const cases=[];
for(const type of [L.DUST,L.ENGRAVE,L.HEADSTONE,L.BURN,L.MARK,L.ENGR_BLOOD])for(const blind of [0,1])for(const levitate of [0,1])for(const run of [0,2])cases.push({type,blind,levitate,run});
for(const terrain of [layouts.dbridge.ICE,layouts.makemon.GRAVE,layouts.makemon.POOL,layouts.makemon.LAVAPOOL])for(const type of [L.DUST,L.ENGRAVE,L.BURN,L.MARK,L.ENGR_BLOOD])cases.push({type,terrain});
for(const actual of ['', 'x','hello.','hello!','hello?','x'.repeat(400)])cases.push({type:L.ENGRAVE,actual});
cases.push({type:L.ENGRAVE,actual:'worn?',pristine:'whole.'},{type:L.ENGRAVE,actual:' hello!',pristine:' whole.',offset:1},{type:0},{type:-1},{type:-1,terrain:layouts.makemon.POOL,hallucinate:1});
for(const terrain of [layouts.makemon.POOL,layouts.makemon.LAVAPOOL])for(const hallucinate of [1,2])cases.push({type:L.BURN,terrain,hallucinate});
if(process.env.STANDALONE_ENGRAVING_PREAMBLE_ONLY)cases.length=0;
for(const [index,row]of cases.entries()){
 const jb=js(()=>stdio.captured(1).length),cb=coutput.length;js(()=>env.services.tty_clear_nhwindow(env.services.WIN_MESSAGE));ref._probe_engraving_read_clear();input(row);
 js(()=>{env.services.read_engr_at(10,10);env.services.fflush(stdio.stdout);});ref._probe_engraving_read();
 equal(js(()=>Buffer.from(stdio.captured(1)).subarray(jb)),Buffer.from(coutput.slice(cb)),'Actual TTY bytes '+index+': '+JSON.stringify(row));
 equal(js(()=>engraving(env.memory.HEAPU8,env.start('world-engravings').environment.head_engr.address||0)),engraving(ref.HEAPU8,ref._probe_engraving_read_head()),'All engraving bytes and actual/remembered/pristine text '+index);
 equal(js(()=>[world.svc.context.run,Number(world.gm.multi),env.services.gs.saved_pline_index,env.services.disp.botl]),Array.from({length:4},(_,i)=>Number(ref._probe_engraving_read_scalar(i))),'Running cancellation/message index/status mutation '+index);
 equal(js(()=>Array.from({length:50},(_,i)=>text(env.memory.HEAPU8,env.services.gs.saved_plines[i]))),Array.from({length:50},(_,i)=>text(ref.HEAPU8,ref._probe_engraving_read_message(i))),'All original saved message payloads '+index);
 rng(env,ref);equal(js(()=>window.terminal.frames),ccaptures,'Actual recorder frames/cursors/animation '+index);equal(jkeys,ckeys,'Actual More keyboard requests '+index);
}
console.log(`PASS: ${comparisons-alignmentComparisons} original-C engraving/TTY/message/state/RNG comparisons over${cases.length} reached reading cases, ${alignmentComparisons} INSIGHT alignment comparisons, ${contracts} JS isolation checks, ${hashes} source/artifact hashes.`);
// Separate proof: intentionally interrupted original newgame prefix, then the
// actual turn preamble. This does not accept com_pager/welcome/full startup.
{
 const {env,stdio,creation,startup,ref,coutput,errors}=await pair(1n);
 js(()=>{env.enableTrack(layouts);assert.throws(()=>env.services.newgame(),/Unresolved standalone function com_pager/);env.enableTurnLoop(layouts);env.services.moveloop_preamble(0);env.services.fflush(stdio.stdout);});
 ref._probe_engraving_read_enable_preamble(1);assert.throws(()=>ref._probe_startup_newgame(),/Aborted/);assert.ok(errors.some(s=>s.includes('Observed C boundary: com_pager after optional original moveloop_preamble')),'Original C preamble completes before explicit prefix observation abort');
 equal(js(()=>Buffer.from(stdio.captured(1))),Buffer.from(coutput),'Actual original prefix + connected preamble TTY bytes');console.log('Connected interrupted-prefix/preamble terminal bytes: '+coutput.length);rng(env,ref);
 equal(js(()=>engraving(env.memory.HEAPU8,env.start('world-engravings').environment.head_engr.address||0)),engraving(ref.HEAPU8,ref._probe_engraving_read_head()),'Prefix/preamble engraving state');
 const decl=JSON.parse(fs.readFileSync('js/standalone/decl-storage.json')).globals,cglobal=name=>Number(ref._probe_decl_global(decl.findIndex(row=>row.name===name)));
 for(const [root,type,field,scalar]of [['program_state','sinfo','something_worth_saving','int'],['program_state','sinfo','in_moveloop','int'],['svm','instance_globals_saved_m','moves','long'],['gm','instance_globals_m','multi','long'],['u','you','ux','coordxy'],['u','you','uy','coordxy']]){
  const f=metadata[type].fields[field];if(!f)continue;const jp=env.requireGlobal(root)+f.offset,cp=cglobal(root)+f.offset;equal(js(()=>env.ctypes.load(scalar,jp)),scalar==='long'?new DataView(ref.HEAPU8.buffer).getBigInt64(cp,true):scalar==='coordxy'?new DataView(ref.HEAPU8.buffer).getInt16(cp,true):new DataView(ref.HEAPU8.buffer).getInt32(cp,true),'Prefix/preamble '+root+'.'+field);
 }
}
console.log(`PASS: ${comparisons} total original-C engraving and interrupted-prefix/preamble comparisons; ${contracts} JS isolation checks. Full welcome/newgame and complete turn loop remain separate.`);
