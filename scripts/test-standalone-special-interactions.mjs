import {layoutSourceSha} from './nethack-layout.mjs';
// Genuine original C main/world, then optional interactions on both live heaps.
import assert from 'node:assert/strict';import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import{pathToFileURL}from'node:url';
import {worldGraph} from './restoration-world-graph.mjs';
import {encodeRecorderScreen} from '../js/wasm-replay-support.js';
import{C,R,T}from'../js/c-runtime/context.js';
import{createStandaloneProgram}from'../js/nethack/program.js';import{enableWere}from'../js/nethack/were.js';import{enableDogmove}from'../js/nethack/dogmove.js';
const directory=path.resolve(process.env.STANDALONE_FULL_C_REFERENCE??'.cache/full-original-c-v1'),layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L=layouts.were,records=JSON.parse(fs.readFileSync('js/nethack/records.json')).records;
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex'),receipt=JSON.parse(fs.readFileSync(directory+'/receipt.json'));let hashes=0,checks=0;
for(const[p,h]of Object.entries(receipt.sourceSha256)){assert.equal(layoutSourceSha(p,h),h,p);hashes++;}for(const[p,h]of Object.entries(receipt.artifactSha256)){assert.equal(layoutSourceSha(directory+'/'+p,h),h,p);hashes++;}
const abi=JSON.parse(fs.readFileSync('js/nethack/special-interactions-abi.json'));for(const[p,h]of Object.entries(abi.sourceSha256)){assert.equal(layoutSourceSha(p,h),h,p);hashes++;}
const reference=process.env.STANDALONE_REFERENCE_ROOT;if(!reference)throw new Error('Missing STANDALONE_REFERENCE_ROOT');for(const[p,h]of Object.entries(abi.referenceHeaderSha256)){assert.equal(sha(path.resolve(reference,p)),h,p);hashes++;}
function js(fn){const keys=['WebAssembly','fetch','XMLHttpRequest','WebSocket','Worker'],saved=keys.map(k=>Object.getOwnPropertyDescriptor(globalThis,k));const forbidden=()=>{throw new Error('Forbidden production Wasm/network during special interactions');};for(const k of keys)Object.defineProperty(globalThis,k,{configurable:true,value:k==='WebAssembly'?new Proxy({},{get:forbidden}):forbidden});try{return fn();}finally{keys.forEach((k,i)=>saved[i]?Object.defineProperty(globalThis,k,saved[i]):delete globalThis[k]);assert.deepEqual([C,R,T],[undefined,undefined,undefined]);}}
const equal=(a,b,label)=>{assert.deepEqual(a,b,label);checks++;},epoch=1777723200000,profile={NETHACKDIR:'/nethack',HACKDIR:'/nethack',HOME:'/home/player',USER:'root',LOGNAME:'root',MAIL:'/nethack/mailbox',TERM:'xterm-256color',TERMINFO:'/nethack/terminfo',LINES:'24',COLUMNS:'80',TZ:'America/Los_Angeles',NETHACK_NO_DELAY:'1',NOMUX_MARKERS:'1',NETHACK_RAW_KEYS:'1',NETHACK_SEED:'1',NETHACK_FIXED_DATETIME:'20260102030405',NETHACK_RECORDING_EPOCH:'1777723200',NETHACK_RNGLOG:'/rng.log',NETHACK_RNGLOG_DISP:'/rng-display.log'};
const savedNow=Date.now,savedTZ=process.env.TZ;Date.now=()=>epoch;process.env.TZ=profile.TZ;
let keys='  n',argv=['-u','Ada-male-lawful','-p','Archeologist','-r','human'];let ji=0,ci=0,program;const stop=new Error('finite input exhausted'),entries=[];
const coutput=[[],[]],cframes=[];
const dirs=new Set();function dir(p){if(dirs.has(p))return;dirs.add(p);const parent=path.posix.dirname(p);if(parent!==p)dir(parent);entries.push({path:p,type:'dir',mode:0o777,atime:epoch,mtime:epoch,ctime:epoch});}
function asset(from,to){dir(to);for(const n of fs.readdirSync(from)){const a=from+'/'+n,b=to+'/'+n,s=fs.statSync(a);if(s.isDirectory())asset(a,b);else entries.push({path:b,type:'file',mode:s.mode&0o777,atime:epoch,mtime:epoch,ctime:epoch,base64:fs.readFileSync(a).toString('base64')});}}
try{
 asset(directory+'/assets','/nethack');dir('/nethack/save');dir('/home/player');entries.push({path:'/home/player/.nethackrc',type:'file',mode:0o666,atime:epoch,mtime:epoch,ctime:epoch,base64:''});
 program=js(()=>createStandaloneProgram({layouts,runtime:{initialBytes:1024,maximumBytes:128*1024*1024,environment:profile,now:()=>epoch},filesystemSnapshot:{version:1,cwd:'/nethack',entries},readKey(){if(ji===keys.length)throw stop;return keys.charCodeAt(ji++);}}));
 const env=program.environment,S=new Proxy(env.services,{get:(o,k)=>{const v=Reflect.get(o,k);return typeof v==='function'?(...a)=>js(()=>v(...a)):v;}});if(!env.hasFunction('were_change'))js(()=>enableWere(env,layouts));if(!env.hasFunction('dog_move'))js(()=>enableDogmove(env,layouts));
 js(()=>env.enableSpecialInteractions(layouts));
 try{js(()=>program.run(argv,{programName:'nethack'}));assert.fail('JS must reach input boundary');}catch(e){if(e!==stop)throw e;}
 const{default:factory}=await import(pathToFileURL(directory+'/out/game.mjs'));
 const ref=await factory({noInitialRun:true,thisProgram:'nethack',teleportCapture(screen,x,y,animation){cframes.push({screen:encodeRecorderScreen(screen),cursor:[x,y,1],animation:Boolean(animation)});},teleportReadKey(){if(ci===keys.length)throw'unwind';return keys.charCodeAt(ci++);},print(){},printErr(){},preRun:[m=>{Object.assign(m.ENV,profile);m.FS.mkdirTree('/home/player');m.FS.writeFile('/home/player/.nethackrc','');}]});for(const fd of [1,2]){const tty=ref.FS.getStream(fd).tty,put=tty.ops.put_char;tty.ops={...tty.ops,put_char(t,c){if(c!==null)coutput[fd-1].push(c);return put(t,c);}};}ref.FS.mkdirTree('/nethack/save');ref.FS.chdir('/nethack');ref.callMain([...argv]);
 equal([ji,ci],[3,3],'actual source main reaches first gameplay input');
 const cstring=p=>{p=Number(p);let n=p;while(ref.HEAPU8[n])n++;return Buffer.from(ref.HEAPU8.slice(p,n)).toString();},globals={};for(let i=0;i<ref._full_global_count();i++)globals[cstring(ref._full_global_name(i))]=Number(ref._full_global_address(i));
 const cv=()=>new DataView(ref.HEAPU8.buffer),jf=(type,p,key,ctype)=>env.ctypes.getField('struct '+type,p,key,ctype),cf=(type,p,key,ctype)=>{const f=records[type].fields[key];if(ctype==='pointer')return Number(cv().getBigUint64(p+f.offset,true));return ctype==='long'?cv().getBigInt64(p+f.offset,true):cv().getInt32(p+f.offset,true);};
 const rng=()=>{const state=env.state('rnd');return state.rnglist.map(({rng_state:s})=>{const b=Buffer.alloc(layouts.rnd.size);b.writeBigUInt64LE(BigInt(s.n),layouts.rnd.n);for(const k of['r','m'])for(let i=0;i<256;i++)b.writeBigUInt64LE(s[k][i],layouts.rnd[k]+8*i);for(const k of['a','b','c'])b.writeBigUInt64LE(s[k],layouts.rnd[k]);return b;});};
 const compareRng=label=>equal(rng(),[0,1].map(i=>{const p=Number(ref._full_rng_state(i));return Buffer.from(ref.HEAPU8.slice(p,p+Number(ref._full_rng_size())));}),label+' complete two RNG states');
 compareRng('startup');
 const mons=(heap,root)=>{const v=new DataView(heap.buffer),rows=[];let p=Number(v.getBigUint64(root,true));while(p){rows.push(p);p=Number(v.getBigUint64(p+records.monst.fields.nmon.offset,true));}return rows;};
 const listOffset=records.instance_globals_saved_l.fields.level.offset+records.dlevel_t.fields.monlist.offset,jroot=env.requireGlobal('svl')+listOffset,croot=globals.svl+listOffset;
 const jmons=mons(env.memory.HEAPU8,jroot),cmons=mons(ref.HEAPU8,croot);equal(jmons.length,cmons.length,'real starter monster count');assert.ok(jmons.length);



 const output=process.env.SPECIAL_INTERACTIONS_OUTPUT??'.cache/special-interactions-evidence.json';
 const cases=[];
 const compare=label=>{
  compareRng(label);
  for(const file of ['/rng.log','/rng-display.log']){const jexists=env.filesystem.exportSnapshot().entries.some(row=>row.path===file),cexists=ref.FS.analyzePath(file).exists;equal(jexists,cexists,label+' log presence '+file);if(jexists)equal(Buffer.from(env.filesystem.readFile(file)),Buffer.from(ref.FS.readFile(file)),label+' complete '+file);}
  equal(Buffer.from(program.stdio.captured(1)),Buffer.from(coutput[0]),label+' complete terminal bytes');
  equal(Buffer.from(program.stdio.captured(2)),Buffer.from(coutput[1]),label+' complete stderr');
  equal(program.terminal.frames,cframes,label+' complete recording frames');
  equal(worldGraph({environment:env}),worldGraph({module:ref}),label+' complete normalized world/identity graph');
  cases.push(label);fs.writeFileSync(output,JSON.stringify({checks,hashes,cases,complete:false},null,2)+'\n');
 };
 compare('genuine first command boundary');
 // Finite input interrupts tty_nhgetch before its normal decrement.
 // Restore that caller bookkeeping on both fixtures before direct UI calls.
 const getting=records.sinfo.fields.getting_char.offset;equal(env.memory.view.getInt32(env.requireGlobal('program_state')+getting,true),1,'paused input counter');equal(cv().getInt32(globals.program_state+getting,true),1,'native paused input counter');env.memory.view.setInt32(env.requireGlobal('program_state')+getting,0,true);cv().setInt32(globals.program_state+getting,0,true);
 function action(name,jargs=[],cargs=jargs){console.log('ACTION',name);const a=js(()=>env.resolve(name)(...jargs)),b=ref['_'+name](...cargs);equal(a??0,b??0,name+' return');equal(ji,ci,name+' consumed input');compare(name);}
 const clearMessage=()=>action('tty_clear_nhwindow',[Number(env.ctypes.load('int',env.requireGlobal('WIN_MESSAGE')))]);
 const cstr=value=>{const b=Buffer.from(value+'\0'),p=ref._malloc(BigInt(b.length));ref.HEAPU8.set(b,Number(p));return p;};
 const bufferJ=env.memory.calloc(1,1024),bufferC=BigInt(ref._malloc(1024n));
 // RUMORS file parsing, cookie filtering and deterministic repeated selection.
 for(const truth of [1,-1,0,1,-1]){
  const a=js(()=>env.resolve('getrumor')(truth,bufferJ,0)),b=ref._getrumor(truth,bufferC,0);
  equal(env.memory.readString(a),cstring(b),'rumor truth '+truth);compare('rumor '+truth);
 }
 // MUSIC on genuine starter monsters; full graph comparison detects changes.
 action('awaken_soldiers',[env.requireGlobal('gy')+records.instance_globals_y.fields.youmonst.offset],[BigInt(globals.gy+records.instance_globals_y.fields.youmonst.offset)]);
 const created=[];
 function item(type){const j=Number(js(()=>env.resolve('mksobj')(type,0,0))),c=BigInt(ref._mksobj(type,0,0));created.push([j,c]);equal(Buffer.from(env.memory.HEAPU8.slice(j,j+records.obj.size)),Buffer.from(ref.HEAPU8.slice(Number(c),Number(c)+records.obj.size)),'source-created object '+type);compare('mksobj '+type);return[j,c];}
 const [instrumentJ,instrumentC]=item(abi.ports.music.layout.WOODEN_FLUTE);
 action('obj_to_instr',[instrumentJ],[instrumentC]);
 // Genuine underwater guard, then the original interactive cancellation path.
 const jhero=env.requireGlobal('u'),chero=globals.u;
 function heroBit(field,value){env.ctypes.setField('struct you',jhero,field,'unsigned int',value);const f=records.you.fields[field],n=Math.ceil((f.shift+f.bits)/8);let bits=0n;for(let i=0;i<n;i++)bits|=BigInt(ref.HEAPU8[chero+f.offset+i])<<BigInt(i*8);const mask=((1n<<BigInt(f.bits))-1n)<<BigInt(f.shift);bits=(bits&~mask)|((BigInt(value)<<BigInt(f.shift))&mask);for(let i=0;i<n;i++)ref.HEAPU8[chero+f.offset+i]=Number(bits>>BigInt(i*8)&255n);}
 heroBit('uinwater',1);action('do_play_instrument',[instrumentJ],[instrumentC]);heroBit('uinwater',0);
 clearMessage();keys=keys.slice(0,ji)+'q';action('do_play_instrument',[instrumentJ],[instrumentC]);

 // SIT ordinary floor path; rare throne/pit/elemental effects are not accepted.
 action('dosit');
 clearMessage();keys=keys.slice(0,ji)+' '.repeat(20);action('outoracle',[0,0]);
 clearMessage();keys=keys.slice(0,ji)+' '.repeat(20);action('outrumor',[1,abi.ports.rumors.layout.BY_COOKIE]);
 const [penJ,penC]=item(layouts.apply.MAGIC_MARKER);
 clearMessage();keys=keys.slice(0,ji)+'\x1b'+' '.repeat(10);action('dowrite',[penJ],[penC]);
 const x=jf('you',jhero,'ux','short'),y=jf('you',jhero,'uy','short');
 action('set_levltyp',[x,y,abi.ports.fountain.layout.SINK]);
 // Explicit fixture RNG draw selects a non-polymorph sink case. The toxic
 // waste/polyself branch is currently an unresolved separate owner.
 action('rn2',[20]);action('drinksink');
 action('set_levltyp',[x,y,abi.ports.fountain.layout.FOUNTAIN]);action('drinkfountain');
 // WRITE uses the real private selection callback through public getobj.
 for(const word of ['Archon','Archon corpse','Medusa','orc','Archonish'])action('CapitalMon',[S.literal(word)],[BigInt(cstr(word))]);
 // Real inventory selection and successful writing of a known scroll.
 const [paperJ,paperC]=item(abi.ports.write.layout.SCR_BLANK_PAPER);
 for(const [j,c]of [[penJ,penC],[paperJ,paperC]]){js(()=>env.resolve('addinv')(j));ref._addinv(c);compare('addinv');}
 env.ctypes.setField('struct obj',penJ,'spe','signed char',100);cv().setInt8(Number(penC)+records.obj.fields.spe.offset,100);
 action('discover_object',[abi.ports.write.layout.SCR_IDENTIFY,1,0,0]);
 const letter=jf('obj',paperJ,'invlet','char');equal(letter,ref.HEAPU8[Number(paperC)+records.obj.fields.invlet.offset],'paper selection letter');
 clearMessage();keys=keys.slice(0,ji)+String.fromCharCode(letter)+'identify\n'+ ' '.repeat(10);action('dowrite',[penJ],[penC]);assert.ok(jf('obj',penJ,'spe','signed char')<100,'successful writing consumed actual marker ink');
 clearMessage();keys=keys.slice(0,ji)+'y'+' '.repeat(10);action('do_play_instrument',[instrumentJ],[instrumentC]);
 equal(Buffer.from(env.memory.HEAPU8.slice(instrumentJ,instrumentJ+records.obj.size)),Buffer.from(ref.HEAPU8.slice(Number(instrumentC),Number(instrumentC)+records.obj.size)),'detached wooden flute state after playing');
 action('free_CapMons');action('CapitalMon',[S.literal('Archon')],[BigInt(cstr('Archon'))]);
 clearMessage();keys=keys.slice(0,ji)+' '.repeat(20);action('outoracle',[1,1]);
 console.log('PASS '+JSON.stringify({checks,hashes,cases,complete:true,scope:'Explicit optional interaction subset; polymorph and other rare effects remain unaccepted'}));
 fs.writeFileSync(output,JSON.stringify({checks,hashes,cases,complete:true},null,2)+'\n');
}finally{Date.now=savedNow;if(savedTZ===undefined)delete process.env.TZ;else process.env.TZ=savedTZ;}
