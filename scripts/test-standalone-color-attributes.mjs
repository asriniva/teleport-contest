// Genuine original main/world, then original COLORATT/POSIXREGEX calls on both heaps.
import assert from 'node:assert/strict';import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import{pathToFileURL}from'node:url';
import{C,R,T}from'../js/c-runtime/context.js';
import{createStandaloneProgram}from'../js/standalone/program.js';import{enableWere}from'../js/standalone/were.js';import{enableDogmove}from'../js/standalone/dogmove.js';
const directory=path.resolve(process.env.STANDALONE_FULL_C_REFERENCE??'.cache/full-original-c-v1'),layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L=layouts.were,records=JSON.parse(fs.readFileSync('js/standalone/records.json')).records;
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex'),receipt=JSON.parse(fs.readFileSync(directory+'/receipt.json'));let hashes=0,checks=0;
for(const[p,h]of Object.entries(receipt.sourceSha256)){assert.equal(sha(p),h,p);hashes++;}for(const[p,h]of Object.entries(receipt.artifactSha256)){assert.equal(sha(directory+'/'+p),h,p);hashes++;}
const abi=JSON.parse(fs.readFileSync('js/standalone/color-attributes-abi.json'));for(const[p,h]of Object.entries(abi.sourceSha256)){assert.equal(sha(p),h,p);hashes++;}
function js(fn){const keys=['WebAssembly','fetch','XMLHttpRequest','WebSocket','Worker'],saved=keys.map(k=>Object.getOwnPropertyDescriptor(globalThis,k));const forbidden=()=>{throw new Error('Forbidden production Wasm/network during COLORATT/POSIXREGEX');};for(const k of keys)Object.defineProperty(globalThis,k,{configurable:true,value:k==='WebAssembly'?new Proxy({},{get:forbidden}):forbidden});try{return fn();}finally{keys.forEach((k,i)=>saved[i]?Object.defineProperty(globalThis,k,saved[i]):delete globalThis[k]);assert.deepEqual([C,R,T],[undefined,undefined,undefined]);}}
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


 const literal=value=>{const b=Buffer.from(value+'\0'),p=ref._malloc(BigInt(b.length));ref.HEAPU8.set(b,Number(p));return BigInt(p);};
 for(const [pattern,inputs]of [['^a[0-9]+$',['a1','a12','ba1','a']],['foo|bar',['foo','bar','xbarx','baz']],['',['','anything']],['[',['x']]]){
  const jp=S.regex_init(),cp=BigInt(ref._regex_init()),cs=literal(pattern),js=S.literal(pattern);
  const ok=S.regex_compile(js,jp);equal(ok,ref._regex_compile(cs,cp),'compile '+pattern);
  if(ok)for(const input of inputs){const ci=literal(input);equal(S.regex_match(S.literal(input),jp),ref._regex_match(ci,cp),'match '+pattern+' '+input);ref._free(ci);}
  const je=env.memory.calloc(1,256),ce=BigInt(ref._malloc(256n));ref.HEAPU8.fill(0,Number(ce),Number(ce)+256);
  S.regex_error_desc(jp,je);ref._regex_error_desc(cp,ce);equal(env.memory.readString(je),cstring(ce),'source error description '+pattern);
  S.regex_free(jp);ref._regex_free(cp);env.memory.free(je);ref._free(ce);ref._free(cs);
 }
 const coloring=(heap,root)=>{const v=new DataView(heap.buffer),rows=[];let at=Number(v.getBigUint64(root,true));while(at){const f=records.menucoloring.fields,stringAt=p=>{let n=p;while(heap[n])n++;return Buffer.from(heap.slice(p,n)).toString();};rows.push({color:v.getInt32(at+f.color.offset,true),attr:v.getInt32(at+f.attr.offset,true),pattern:stringAt(Number(v.getBigUint64(at+f.origstr.offset,true)))});at=Number(v.getBigUint64(at+f.next.offset,true));}return rows;};
 const offset=records.instance_globals_m.fields.menu_colorings.offset,jrootColor=env.requireGlobal('gm')+offset,crootColor=globals.gm+offset;
 for(const [pattern,color,attr]of [['food',1,0],['^a[0-9]+$',2,1],['foo|bar',3,2]]){
  const p=literal(pattern);equal(S.add_menu_coloring_parsed(S.literal(pattern),color,attr),ref._add_menu_coloring_parsed(p,color,attr),'actual original color rule '+pattern);ref._free(p);
  equal(coloring(env.memory.HEAPU8,jrootColor),coloring(ref.HEAPU8,crootColor),'complete live color rule list '+pattern);
 }
 S.free_menu_coloring();ref._free_menu_coloring();equal(coloring(env.memory.HEAPU8,jrootColor),coloring(ref.HEAPU8,crootColor),'nonempty source cleanup clears rule head');compareRng('all color/regex calls');
 const result={checks,hashes,scope:'Genuine startup then source regex wrappers and nonempty menu-color creation/free on shared original lists',fullColorAttributesAccepted:false,limitation:'Color UI, broad parsing/error paths and regex dialect cases outside this fixture remain unaccepted.'};
 fs.writeFileSync(directory+'/color-attributes-evidence.json',JSON.stringify(result,null,2)+'\n');console.log('PASS '+JSON.stringify(result));
}finally{Date.now=savedNow;if(savedTZ===undefined)delete process.env.TZ;else process.env.TZ=savedTZ;}
