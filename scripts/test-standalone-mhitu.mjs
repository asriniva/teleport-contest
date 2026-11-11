// Genuine original main/world, then original MHITU queries on both heaps.
import assert from 'node:assert/strict';import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import{pathToFileURL}from'node:url';
import{C,R,T}from'../js/ported/c-runtime.js';
import{createStandaloneProgram}from'../js/standalone/program.js';import{enableWere}from'../js/standalone/were.js';import{enableDogmove}from'../js/standalone/dogmove.js';
const directory=path.resolve(process.env.STANDALONE_FULL_C_REFERENCE??'.cache/full-original-c-v1'),layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L=layouts.were,records=JSON.parse(fs.readFileSync('js/standalone/records.json')).records;
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex'),receipt=JSON.parse(fs.readFileSync(directory+'/receipt.json'));let hashes=0,checks=0;
for(const[p,h]of Object.entries(receipt.sourceSha256)){assert.equal(sha(p),h,p);hashes++;}for(const[p,h]of Object.entries(receipt.artifactSha256)){assert.equal(sha(directory+'/'+p),h,p);hashes++;}
const abi=JSON.parse(fs.readFileSync('js/standalone/mhitu-abi.json'));for(const[p,h]of Object.entries(abi.sourceSha256)){assert.equal(sha(p),h,p);hashes++;}
function js(fn){const keys=['WebAssembly','fetch','XMLHttpRequest','WebSocket','Worker'],saved=keys.map(k=>Object.getOwnPropertyDescriptor(globalThis,k));const forbidden=()=>{throw new Error('Forbidden production Wasm/network during MHITU');};for(const k of keys)Object.defineProperty(globalThis,k,{configurable:true,value:k==='WebAssembly'?new Proxy({},{get:forbidden}):forbidden});try{return fn();}finally{keys.forEach((k,i)=>saved[i]?Object.defineProperty(globalThis,k,saved[i]):delete globalThis[k]);assert.deepEqual([C,R,T],[undefined,undefined,undefined]);}}
const equal=(a,b,label)=>{assert.deepEqual(a,b,label);checks++;},epoch=1777723200000,profile={NETHACKDIR:'/nethack',HACKDIR:'/nethack',HOME:'/home/player',USER:'root',LOGNAME:'root',MAIL:'/nethack/mailbox',TERM:'xterm-256color',TERMINFO:'/nethack/terminfo',LINES:'24',COLUMNS:'80',TZ:'America/Los_Angeles',NETHACK_NO_DELAY:'1',NOMUX_MARKERS:'1',NETHACK_RAW_KEYS:'1',NETHACK_SEED:'1',NETHACK_FIXED_DATETIME:'20260102030405',NETHACK_RECORDING_EPOCH:'1777723200',NETHACK_RNGLOG:'/rng.log',NETHACK_RNGLOG_DISP:'/rng-display.log'};
const savedNow=Date.now,savedTZ=process.env.TZ;Date.now=()=>epoch;process.env.TZ=profile.TZ;
const keys='  n',argv=['-u','Ada-male-lawful','-p','Archeologist','-r','human'];let ji=0,ci=0,program;const stop=new Error('finite input exhausted'),entries=[];
const dirs=new Set();function dir(p){if(dirs.has(p))return;dirs.add(p);const parent=path.posix.dirname(p);if(parent!==p)dir(parent);entries.push({path:p,type:'dir',mode:0o777,atime:epoch,mtime:epoch,ctime:epoch});}
function asset(from,to){dir(to);for(const n of fs.readdirSync(from)){const a=from+'/'+n,b=to+'/'+n,s=fs.statSync(a);if(s.isDirectory())asset(a,b);else entries.push({path:b,type:'file',mode:s.mode&0o777,atime:epoch,mtime:epoch,ctime:epoch,base64:fs.readFileSync(a).toString('base64')});}}
try{
 asset(directory+'/assets','/nethack');dir('/nethack/save');dir('/home/player');entries.push({path:'/home/player/.nethackrc',type:'file',mode:0o666,atime:epoch,mtime:epoch,ctime:epoch,base64:''});
 program=js(()=>createStandaloneProgram({layouts,runtime:{initialBytes:1024,maximumBytes:128*1024*1024,environment:profile,now:()=>epoch},filesystemSnapshot:{version:1,cwd:'/nethack',entries},readKey(){if(ji===keys.length)throw stop;return keys.charCodeAt(ji++);}}));
 const env=program.environment,S=new Proxy(env.services,{get:(o,k)=>{const v=Reflect.get(o,k);return typeof v==='function'?(...a)=>js(()=>v(...a)):v;}});if(!env.hasFunction('were_change'))js(()=>enableWere(env,layouts));if(!env.hasFunction('dog_move'))js(()=>enableDogmove(env,layouts));
 try{js(()=>program.run(argv,{programName:'nethack'}));assert.fail('JS must reach input boundary');}catch(e){if(e!==stop)throw e;}
 const{default:factory}=await import(pathToFileURL(directory+'/out/game.mjs'));
 const ref=await factory({noInitialRun:true,thisProgram:'nethack',teleportCapture(){},teleportReadKey(){if(ci===keys.length)throw'unwind';return keys.charCodeAt(ci++);},print(){},printErr(){},preRun:[m=>{Object.assign(m.ENV,profile);m.FS.mkdirTree('/home/player');m.FS.writeFile('/home/player/.nethackrc','');}]});ref.FS.mkdirTree('/nethack/save');ref.FS.chdir('/nethack');ref.callMain([...argv]);
 equal([ji,ci],[3,3],'actual source main reaches first gameplay input');
 const cstring=p=>{p=Number(p);let n=p;while(ref.HEAPU8[n])n++;return Buffer.from(ref.HEAPU8.slice(p,n)).toString();},globals={};for(let i=0;i<ref._full_global_count();i++)globals[cstring(ref._full_global_name(i))]=Number(ref._full_global_address(i));
 const cv=()=>new DataView(ref.HEAPU8.buffer),jf=(type,p,key,ctype)=>env.ctypes.getField('struct '+type,p,key,ctype),cf=(type,p,key,ctype)=>{const f=records[type].fields[key];if(ctype==='pointer')return Number(cv().getBigUint64(p+f.offset,true));return ctype==='long'?cv().getBigInt64(p+f.offset,true):cv().getInt32(p+f.offset,true);};
 const rng=()=>{const state=env.state('rnd');return state.rnglist.map(({rng_state:s})=>{const b=Buffer.alloc(layouts.rnd.size);b.writeBigUInt64LE(BigInt(s.n),layouts.rnd.n);for(const k of['r','m'])for(let i=0;i<256;i++)b.writeBigUInt64LE(s[k][i],layouts.rnd[k]+8*i);for(const k of['a','b','c'])b.writeBigUInt64LE(s[k],layouts.rnd[k]);return b;});};
 const compareRng=label=>equal(rng(),[0,1].map(i=>{const p=Number(ref._full_rng_state(i));return Buffer.from(ref.HEAPU8.slice(p,p+Number(ref._full_rng_size())));}),label+' complete two RNG states');
 compareRng('startup');
 const mons=(heap,root)=>{const v=new DataView(heap.buffer),rows=[];let p=Number(v.getBigUint64(root,true));while(p){rows.push(p);p=Number(v.getBigUint64(p+records.monst.fields.nmon.offset,true));}return rows;};
 const listOffset=records.instance_globals_saved_l.fields.level.offset+records.dlevel_t.fields.monlist.offset,jroot=env.requireGlobal('svl')+listOffset,croot=globals.svl+listOffset;
 const jmons=mons(env.memory.HEAPU8,jroot),cmons=mons(ref.HEAPU8,croot);equal(jmons.length,cmons.length,'real starter monster count');assert.ok(jmons.length);

 for(let i=0;i<jmons.length;i++){
  for(const name of ['ranged_attk_available','mtrapped_in_pit','magic_negation']){
   equal(S[name](jmons[i]),ref['_'+name](BigInt(cmons[i])),name+' genuine monster '+i);compareRng(name+' '+i);
  }
  for(let j=0;j<jmons.length;j++)equal(S.could_seduce(jmons[i],jmons[j],0),ref._could_seduce(BigInt(cmons[i]),BigInt(cmons[j]),0n),'source general seduction capability '+i+':'+j);
 }
 compareRng('all MHITU queries');
 const result={checks,hashes,scope:'Actual main plus starter-monster ranged attack, pit, magic negation and general seduction queries with both full RNG states',fullCombatAccepted:false,limitation:'MHITU policy/factory transport only; attacking, damage, swallowing, gaze, theft, special forms and fatal effects remain unaccepted.'};
 fs.writeFileSync(directory+'/mhitu-evidence.json',JSON.stringify(result,null,2)+'\n');console.log('PASS '+JSON.stringify(result));
}finally{Date.now=savedNow;if(savedTZ===undefined)delete process.env.TZ;else process.env.TZ=savedTZ;}
