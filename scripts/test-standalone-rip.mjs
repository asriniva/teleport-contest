// Genuine original main then original RIP tombstone on real TTY windows.
import assert from 'node:assert/strict';import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import{pathToFileURL}from'node:url';
import{C,R,T}from'../js/c-runtime/context.js';
import{createStandaloneProgram}from'../js/standalone/program.js';import{enableRip}from'../js/standalone/rip.js';import{encodeRecorderScreen}from'../js/wasm-replay-support.js';
const directory=path.resolve(process.env.STANDALONE_FULL_C_REFERENCE??'.cache/full-original-c-v1'),layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L=layouts.were,records=JSON.parse(fs.readFileSync('js/standalone/records.json')).records;
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex'),receipt=JSON.parse(fs.readFileSync(directory+'/receipt.json'));let hashes=0,checks=0;
for(const[p,h]of Object.entries(receipt.sourceSha256)){assert.equal(sha(p),h,p);hashes++;}for(const[p,h]of Object.entries(receipt.artifactSha256)){assert.equal(sha(directory+'/'+p),h,p);hashes++;}
const abi=JSON.parse(fs.readFileSync('js/standalone/rip-abi.json'));for(const[p,h]of Object.entries(abi.sourceSha256)){assert.equal(sha(p),h,p);hashes++;}
function js(fn){const keys=['WebAssembly','fetch','XMLHttpRequest','WebSocket','Worker'],saved=keys.map(k=>Object.getOwnPropertyDescriptor(globalThis,k));const forbidden=()=>{throw new Error('Forbidden production Wasm/network during RIP');};for(const k of keys)Object.defineProperty(globalThis,k,{configurable:true,value:k==='WebAssembly'?new Proxy({},{get:forbidden}):forbidden});try{return fn();}finally{keys.forEach((k,i)=>saved[i]?Object.defineProperty(globalThis,k,saved[i]):delete globalThis[k]);assert.deepEqual([C,R,T],[undefined,undefined,undefined]);}}
const equal=(a,b,label)=>{assert.deepEqual(a,b,label);checks++;},epoch=1777723200000,profile={NETHACKDIR:'/nethack',HACKDIR:'/nethack',HOME:'/home/player',USER:'root',LOGNAME:'root',MAIL:'/nethack/mailbox',TERM:'xterm-256color',TERMINFO:'/nethack/terminfo',LINES:'24',COLUMNS:'80',TZ:'UTC',NETHACK_NO_DELAY:'1',NOMUX_MARKERS:'1',NETHACK_RAW_KEYS:'1',NETHACK_SEED:'1',NETHACK_FIXED_DATETIME:'20260102030405',NETHACK_RECORDING_EPOCH:'1777723200',NETHACK_RNGLOG:'/rng.log',NETHACK_RNGLOG_DISP:'/rng-display.log'};
const savedNow=Date.now,savedTZ=process.env.TZ;Date.now=()=>epoch;process.env.TZ=profile.TZ;
const keys='  n',argv=['-u','Ada-male-lawful','-p','Archeologist','-r','human'];let ji=0,ci=0,program,inMain=true,jpost=0,cpost=0;const cframes=[],cstdout=[],cstderr=[];const stop=new Error('finite input exhausted'),entries=[];
const dirs=new Set();function dir(p){if(dirs.has(p))return;dirs.add(p);const parent=path.posix.dirname(p);if(parent!==p)dir(parent);entries.push({path:p,type:'dir',mode:0o777,atime:epoch,mtime:epoch,ctime:epoch});}
function asset(from,to){dir(to);for(const n of fs.readdirSync(from)){const a=from+'/'+n,b=to+'/'+n,s=fs.statSync(a);if(s.isDirectory())asset(a,b);else entries.push({path:b,type:'file',mode:s.mode&0o777,atime:epoch,mtime:epoch,ctime:epoch,base64:fs.readFileSync(a).toString('base64')});}}
try{
 asset(directory+'/assets','/nethack');dir('/nethack/save');dir('/home/player');entries.push({path:'/home/player/.nethackrc',type:'file',mode:0o666,atime:epoch,mtime:epoch,ctime:epoch,base64:''});
 program=js(()=>createStandaloneProgram({layouts,runtime:{initialBytes:1024,maximumBytes:128*1024*1024,environment:profile,now:()=>epoch},filesystemSnapshot:{version:1,cwd:'/nethack',entries},readKey(){if(!inMain){assert.ok(++jpost<100,'bounded real window input');return 32;}if(ji===keys.length)throw stop;return keys.charCodeAt(ji++);}}));
 const env=program.environment,S=new Proxy(env.services,{get:(o,k)=>{const v=Reflect.get(o,k);return typeof v==='function'?(...a)=>js(()=>v(...a)):v;}});if(!env.hasFunction('genl_outrip'))js(()=>enableRip(env,layouts));
 try{js(()=>program.run(argv,{programName:'nethack'}));assert.fail('JS must reach input boundary');}catch(e){if(e!==stop)throw e;}
 const{default:factory}=await import(pathToFileURL(directory+'/out/game.mjs'));
 const ref=await factory({noInitialRun:true,thisProgram:'nethack',teleportCapture(screen,x,y,animation){cframes.push({screen:encodeRecorderScreen(screen),cursor:[x,y,1],animation:Boolean(animation)});},teleportReadKey(){if(!inMain){assert.ok(++cpost<100,'bounded native window input');return 32;}if(ci===keys.length)throw'unwind';return keys.charCodeAt(ci++);},print(){},printErr(){},preRun:[m=>{Object.assign(m.ENV,profile);m.FS.mkdirTree('/home/player');m.FS.writeFile('/home/player/.nethackrc','');}]});for(const fd of [1,2]){const tty=ref.FS.getStream(fd).tty,original=tty.ops.put_char;tty.ops={...tty.ops,put_char:(t,c)=>{if(c!==null)(fd===1?cstdout:cstderr).push(c);return original(t,c);}};}ref.FS.mkdirTree('/nethack/save');ref.FS.chdir('/nethack');ref.callMain([...argv]);inMain=false;
 equal([ji,ci],[3,3],'actual source main reaches first gameplay input');
 const cstring=p=>{p=Number(p);let n=p;while(ref.HEAPU8[n])n++;return Buffer.from(ref.HEAPU8.slice(p,n)).toString();},globals={};for(let i=0;i<ref._full_global_count();i++)globals[cstring(ref._full_global_name(i))]=Number(ref._full_global_address(i));
 const cv=()=>new DataView(ref.HEAPU8.buffer),jf=(type,p,key,ctype)=>env.ctypes.getField('struct '+type,p,key,ctype),cf=(type,p,key,ctype)=>{const f=records[type].fields[key];if(ctype==='pointer')return Number(cv().getBigUint64(p+f.offset,true));return ctype==='long'?cv().getBigInt64(p+f.offset,true):cv().getInt32(p+f.offset,true);};
 const rng=()=>{const state=env.state('rnd');return state.rnglist.map(({rng_state:s})=>{const b=Buffer.alloc(layouts.rnd.size);b.writeBigUInt64LE(BigInt(s.n),layouts.rnd.n);for(const k of['r','m'])for(let i=0;i<256;i++)b.writeBigUInt64LE(s[k][i],layouts.rnd[k]+8*i);for(const k of['a','b','c'])b.writeBigUInt64LE(s[k],layouts.rnd[k]);return b;});};
 const compareRng=label=>equal(rng(),[0,1].map(i=>{const p=Number(ref._full_rng_state(i));return Buffer.from(ref.HEAPU8.slice(p,p+Number(ref._full_rng_size())));}),label+' complete two RNG states');
 compareRng('startup');
 const jwin=S.tty_create_nhwindow(layouts.wintty.NHW_TEXT),cwin=ref._tty_create_nhwindow(layouts.wintty.NHW_TEXT);
 equal(jwin,cwin,'real source text window identity');
 const jwhen=S.getnow(),cwhen=ref._getnow();equal(jwhen,cwhen,'actual source fixed death time');
 S.genl_outrip(jwin,layouts.end.STARVING,jwhen);ref._genl_outrip(cwin,layouts.end.STARVING,cwhen);
 equal(env.ctypes.getField('struct instance_globals_r',env.requireGlobal('gr'),'rip','char **'),BigInt(cv().getBigUint64(globals.gr+records.instance_globals_r.fields.rip.offset,true)),'source frees and clears original tombstone array');
 equal(cv().getBigUint64(globals.gr+records.instance_globals_r.fields.rip.offset,true),0n,'native tombstone head released');
 S.tty_display_nhwindow(jwin,1);ref._tty_display_nhwindow(cwin,1);
 S.tty_destroy_nhwindow(jwin);ref._tty_destroy_nhwindow(cwin);
 equal(jpost,cpost,'actual display prompt input consumption');compareRng('tombstone render');
 equal(Buffer.from(program.stdio.captured(1)),Buffer.from(cstdout),'complete actual TTY output including tombstone');
 equal(Buffer.from(program.stdio.captured(2)),Buffer.from(cstderr),'complete actual TTY errors');
 equal(program.terminal.frames,cframes,'complete encoded recorder frames/cursors/animation');
 const result={checks,hashes,scope:'Genuine original startup then source genl_outrip STARVING on actual text window, real display input, formatting/calendar, pointer release, TTY/recorder and dual RNG state',completeDeathAccepted:false,limitation:'This ordinary zero-money Ada starvation tombstone only; dedication/dumplog compile profiles and other killer/name/wealth cases remain unaccepted.'};
 fs.mkdirSync('.cache/standalone-rip',{recursive:true});fs.writeFileSync('.cache/standalone-rip/evidence.json',JSON.stringify(result,null,2)+'\n');console.log('PASS '+JSON.stringify(result));
}finally{Date.now=savedNow;if(savedTZ===undefined)delete process.env.TZ;else process.env.TZ=savedTZ;}
