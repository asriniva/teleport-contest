Error.stackTraceLimit=40;let currentMs=1000000000;const savedNow=Date.now;Date.now=()=>currentMs;
import crypto from 'node:crypto';import path from 'node:path';import {pathToFileURL} from 'node:url';import {createNativeTerminal} from '../js/platform/darwin/terminal.js';
import {enableUnixPlatform} from '../js/standalone/unix-platform.js';import fs from 'node:fs';import assert from 'node:assert/strict';import {createStandaloneEnvironment} from '../js/standalone/environment.js';const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),seed=1n;
 const env=createStandaloneEnvironment({now:()=>currentMs/1000,filesystem:{clock:()=>currentMs},initialBytes:1024,maximumBytes:64*1024*1024,environment:{TERM:'xterm-256color',NOMUX_MARKERS:'1',HACKDIR:'/',MAIL:'/mailbox',LOGNAME:'root',NETHACK_RNGLOG:'/rng.log',NETHACK_FIXED_DATETIME:'20260102030405',NETHACK_SEED:seed.toString()}});
 const stdio=env.enableStdio({stdin:new Uint8Array(256).fill(32)});env.enableDecl(layouts.decl);env.enableDrawing(layouts.drawing);env.enableObjects(layouts.objects);env.enableMonst(layouts.monst);env.enableSerialization(layouts);env.enableRnd(layouts.rnd,{seed});env.enableAddressPort('dungeon',{only:['ledger_no','maxledgerno']});env.enableObjectState(layouts);env.enableObjectRecords(layouts);env.enableItemInventory(layouts);env.enableTimers(layouts);env.enableItemNaming(layouts);const group=env.enableMonsterSelection(layouts);const decl=JSON.parse(fs.readFileSync('js/standalone/decl-storage.json')).globals,before=decl.map(r=>env.memory.readBytes(env.requireGlobal(r.name),r.bytes));const creation=env.enableMonsterCreation(layouts);decl.forEach((r,i)=>assert.deepEqual(env.memory.readBytes(env.requireGlobal(r.name),r.bytes),before[i],'enabling creation preserves '+r.name));

 const startup=env.enableGameStartup(layouts);
env.enableHeroStartup(layouts);env.enableWorldPosition(layouts);env.enableLuaSandbox(layouts);env.enableDisplayStartup(layouts);
for(const name of fs.readdirSync(process.env.STANDALONE_REFERENCE_ROOT+'/.cache/wasm64-build/tree/dat').filter(n=>n.endsWith('.lua')))env.filesystem.writeFile(name,fs.readFileSync(process.env.STANDALONE_REFERENCE_ROOT+'/.cache/wasm64-build/tree/dat/'+name));
for(const name of ['epitaph','engrave','rumors','bogusmon','oracles'])env.filesystem.writeFile(name,fs.readFileSync(process.env.STANDALONE_REFERENCE_ROOT+'/.cache/wasm64-build/tree/dat/'+name));
env.filesystem.writeFile('sysconf',fs.readFileSync(process.env.STANDALONE_REFERENCE_ROOT+'/.cache/wasm64-build/assets/sysconf'));

env.enableLevelStartup(layouts);env.enableLevelContents(layouts);const window=env.enableWindowSystem(layouts);env.enableVersionInfo(layouts);env.enableOptions(layouts);env.enableSymbols(layouts);env.enableGlyphs(layouts);env.enableCommands(layouts);env.enableConfiguration(layouts);env.enableFiles(layouts);env.enableStatus(layouts);env.enableGameWindows(layouts);env.enableMovement(layouts);env.enablePets(layouts);env.enableMonsterMovement(layouts);env.enableMonsterLifecycle(layouts);env.enableHeroEquipment(layouts);env.enableQuestPager(layouts);env.enableTerminalInput(layouts);env.enableTerminalMessages(layouts);env.enableMessages(layouts);env.enableDoLifecycle(layouts);env.enableSaveLifecycle(layouts);env.enableLevelPersistence(layouts);env.enableWorms(layouts);env.enableRuntimeInfo(layouts);env.enableReport(layouts);env.enableTurnLoop(layouts);const platform=enableUnixPlatform(env,layouts);
const directory=path.resolve(process.env.STANDALONE_UNIX_PLATFORM_ORACLE||'.cache/standalone-unix-platform-v6'),receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json'))),sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const [p,h]of Object.entries(receipt.sourceSha256))assert.equal(sha(p),h,'Changed C input '+p);
for(const [p,h]of Object.entries(receipt.artifactSha256))assert.equal(sha(path.join(directory,p)),h,'Changed C artifact '+p);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs'))),nativeTerminal=createNativeTerminal(),errors=[],coutput=[],input=[110,10];
const ref=await factory({nethackPorted:{nativeTerminal:(services,name,...args)=>nativeTerminal(services,name,...args)},stdin:()=>input.length?input.shift():null,print:()=>{},printErr:s=>errors.push(s),preRun:[m=>{m.FS.mkdirTree('/nethack/terminfo/x');m.FS.writeFile('/nethack/terminfo/x/xterm-256color',fs.readFileSync('nethack-c/wasm/terminfo/x/xterm-256color'));}]});
const tty=ref.FS.getStream(1).tty,put=tty.ops.put_char;tty.ops={...tty.ops,put_char:(t,c)=>{if(c!==null)coutput.push(c);return put(t,c);}};
function literal(s){const at=BigInt(ref._malloc(BigInt(Buffer.byteLength(s)+1)));ref.HEAPU8.set(Buffer.from(s+'\0'),Number(at));return at;}
for(const [name,value]of Object.entries({TERM:'xterm-256color',TERMINFO:'/nethack/terminfo',HACKDIR:'/',MAIL:'/mailbox',LOGNAME:'root',NETHACK_SEED:'1',NETHACK_FIXED_DATETIME:'20260102030405',NOMUX_MARKERS:'1',NETHACK_RNGLOG:'/rng.log'})){const a=literal(name),b=literal(value);ref._setenv(a,b,1);ref._free(a);ref._free(b);}
const assets=process.env.STANDALONE_REFERENCE_ROOT+'/.cache/wasm64-build/tree/dat/';for(const name of fs.readdirSync(assets).filter(n=>n.endsWith('.lua')).concat(['epitaph','engrave','rumors','bogusmon','oracles']))ref.FS.writeFile(name,fs.readFileSync(assets+name));
ref.FS.writeFile('sysconf',fs.readFileSync(process.env.STANDALONE_REFERENCE_ROOT+'/.cache/wasm64-build/assets/sysconf'));
const args=['nethack','-uAda-male-lawful','-pArcheologist','-rhuman'],argv=env.memory.calloc(args.length+1,8),ca=BigInt(ref._malloc(BigInt((args.length+1)*8)));
args.forEach((arg,i)=>{env.ctypes.store('void *',argv+i*8,env.services.literal(arg));new DataView(ref.HEAPU8.buffer).setBigUint64(Number(ca)+i*8,literal(arg),true);});new DataView(ref.HEAPU8.buffer).setBigUint64(Number(ca)+args.length*8,0n,true);
for(const name of ['perm','record']){env.filesystem.writeFile(name,new Uint8Array());ref.FS.writeFile(name,new Uint8Array());}
// This observation ends only AFTER original getlock returns. The entire
// original main prefix, including its sole early_init and PID assignment, runs.
const observed={},originalLock=env.services.getlock;env.services.getlock=(...args)=>{originalLock(...args);throw observed;};
const capabilities=['WebAssembly','fetch','XMLHttpRequest'].map(name=>[name,Object.getOwnPropertyDescriptor(globalThis,name)]);let forbiddenCalls=0;
const forbidden=()=>{forbiddenCalls++;throw new Error('Forbidden standalone capability');};
Object.defineProperty(globalThis,'WebAssembly',{configurable:true,value:new Proxy({},{get:forbidden})});for(const name of ['fetch','XMLHttpRequest'])Object.defineProperty(globalThis,name,{configurable:true,value:forbidden});
try{assert.throws(()=>env.services.main(args.length,argv),e=>e===observed,'Original JS main completes original getlock');}finally{env.services.getlock=originalLock;for(const [name,d]of capabilities){if(d)Object.defineProperty(globalThis,name,d);else delete globalThis[name];}}
assert.equal(ref._probe_unix_platform_through_lock(args.length,ca),1,'Original C main completes original getlock');assert.equal(forbiddenCalls,0);
const meta=JSON.parse(fs.readFileSync('js/standalone/records.json')).records,declRows=JSON.parse(fs.readFileSync('js/standalone/decl-storage.json')).globals,cglobal=name=>Number(ref._probe_decl_global(declRows.findIndex(r=>r.name===name)));
let checks=3;
function project(heap,at,type){
 const record=meta[type],bytes=Buffer.from(heap.slice(at,at+record.size)),refs={};
 function walk(type,offset,label){for(const [key,f]of Object.entries(meta[type]?.fields??{})){
  const a=f.ctype.match(/\[(\d+)\]/),n=a?Number(a[1]):1;
  if(f.ctype.includes('*'))for(let i=0;i<n;i++){
   const pos=offset+f.offset+i*8,p=Number(bytes.readBigUInt64LE(pos));
   if(/char\s*\*/.test(f.ctype)&&!f.ctype.includes('**')){let end=p;while(p&&heap[end])end++;refs[label+'.'+key+'['+i+']']=p?Buffer.from(heap.slice(p,end)).toString('latin1'):null;}
   bytes.writeBigUInt64LE(p?1n:0n,pos);
  }else{const child=f.record??f.ctype.match(/struct (\w+)/)?.[1];if(child&&meta[child])for(let i=0;i<n;i++)walk(child,offset+f.offset+i*meta[child].size,label+'.'+key+'['+i+']');}
 }}walk(type,0,type);return {bytes,refs};
}
for(const [name,type]of [['flags','flag'],['iflags','instance_flags'],['program_state','sinfo'],['gl','instance_globals_l'],['svh','instance_globals_saved_h'],['svp','instance_globals_saved_p'],['gh','instance_globals_h'],['gp','instance_globals_p'],['gu','instance_globals_u'],['gr','instance_globals_r'],['svq','instance_globals_saved_q'],['svn','instance_globals_saved_n']]){
 assert.deepEqual(project(env.memory.HEAPU8,env.requireGlobal(name),type),project(ref.HEAPU8,cglobal(name),type),'Actual source main prefix '+name);checks++;
}
const lockAt=env.ctypes.locate('struct instance_globals_l',env.requireGlobal('gl'),'lock').at,lock=env.memory.readString(lockAt);
assert.deepEqual(Buffer.from(env.filesystem.readFile(lock)),Buffer.from(ref.FS.readFile(lock)),'Original main-created lock bytes');assert.equal(new DataView(env.filesystem.readFile(lock).buffer).getInt32(0,true),env.services.getpid(),'Original main assigned actual PID');assert.match(lock,/\.0$/,'Source creates level-zero lock using configured slot policy');assert.equal(env.memory.readString(env.ctypes.locate('struct instance_globals_saved_p',env.requireGlobal('svp'),'plname').at),'Ada','Original name suffix removal');checks+=4;
Date.now=savedNow;console.log('PASS: '+checks+' original-C full UNIXMAIN-prefix comparisons through actual lock creation; later main/newgame/checkpoint are not accepted.');
