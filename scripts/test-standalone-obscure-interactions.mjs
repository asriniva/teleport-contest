// Genuine original C main/world, then optional interactions on both live heaps.
import assert from 'node:assert/strict';import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import{pathToFileURL}from'node:url';
import {worldGraph} from './restoration-world-graph.mjs';
import {encodeRecorderScreen} from '../js/wasm-replay-support.js';
import{C,R,T}from'../js/c-runtime/context.js';
import{createStandaloneProgram}from'../js/standalone/program.js';import{enableWere}from'../js/standalone/were.js';import{enableDogmove}from'../js/standalone/dogmove.js';
const directory=path.resolve(process.env.STANDALONE_FULL_C_REFERENCE??'.cache/full-original-c-v1'),layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L=layouts.were,records=JSON.parse(fs.readFileSync('js/standalone/records.json')).records;
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex'),receipt=JSON.parse(fs.readFileSync(directory+'/receipt.json'));let hashes=0,checks=0;
for(const[p,h]of Object.entries(receipt.sourceSha256)){assert.equal(sha(p),h,p);hashes++;}for(const[p,h]of Object.entries(receipt.artifactSha256)){assert.equal(sha(directory+'/'+p),h,p);hashes++;}
const abi=JSON.parse(fs.readFileSync('js/standalone/special-interactions-abi.json'));for(const[p,h]of Object.entries(abi.sourceSha256)){assert.equal(sha(p),h,p);hashes++;}
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



 const mode=process.argv[2];if(!['riding','menus','music','rogue'].includes(mode))throw new Error('Choose riding, menus, music or rogue');
 const output='.cache/obscure-'+mode+'-evidence.json';
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
 function action(name,jargs=[],cargs=jargs){console.log('ACTION',mode,name);const a=js(()=>env.resolve(name)(...jargs)),b=ref['_'+name](...cargs);equal(Number(a??0),Number(b??0),name+' return');equal(ji,ci,name+' input consumption');compare(name);return a;}
 function input(value){equal(ji,ci,'same input boundary');keys=keys.slice(0,ji)+value;}
 function set(type,j,c,key,ctype,value){env.ctypes.setField('struct '+type,j,key,ctype,value);const f=records[type].fields[key];if(f.bits!==undefined){let n=Math.ceil((f.shift+f.bits)/8),bits=0n;for(let i=0;i<n;i++)bits|=BigInt(ref.HEAPU8[Number(c)+f.offset+i])<<BigInt(i*8);const mask=((1n<<BigInt(f.bits))-1n)<<BigInt(f.shift);bits=bits&~mask|BigInt(value)<<BigInt(f.shift)&mask;for(let i=0;i<n;i++)ref.HEAPU8[Number(c)+f.offset+i]=Number(bits>>BigInt(i*8)&255n);}else{const p=Number(c)+f.offset;if(/char/.test(ctype))cv().setInt8(p,Number(value));else if(/short/.test(ctype))cv().setInt16(p,Number(value),true);else if(/long|\*/.test(ctype))cv().setBigInt64(p,BigInt(value),true);else cv().setInt32(p,Number(value),true);}}
 function item(type){const j=Number(js(()=>env.resolve('mksobj')(type,0,0))),c=BigInt(ref._mksobj(type,0,0));equal(Buffer.from(env.memory.HEAPU8.slice(j,j+records.obj.size)),Buffer.from(ref.HEAPU8.slice(Number(c),Number(c)+records.obj.size)),'source-created object');compare('mksobj '+type);return[j,c];}
 function inventory(type){const pair=item(type),j=Number(js(()=>env.resolve('addinv')(pair[0]))),c=BigInt(ref._addinv(pair[1]));compare('addinv');return[j,c];}
 // The finite-input stop interrupts tty_nhgetch after incrementing this
 // counter. Direct calls below emulate its normal return before the next read.
 equal(jf('sinfo',env.requireGlobal('program_state'),'getting_char','int'),1,'paused input counter');set('sinfo',env.requireGlobal('program_state'),globals.program_state,'getting_char','int',0);
 const hJ=env.requireGlobal('u'),hC=globals.u,x=jf('you',hJ,'ux','short'),y=jf('you',hJ,'uy','short');
 if(mode==='riding'){
  input(' '.repeat(200));
  const L=layouts.steed,pmJ=env.requireGlobal('mons')+L.PM_PONY*records.permonst.size,firstData=Number(cv().getBigUint64(cmons[0]+records.monst.fields.data.offset,true)),speciesBase=firstData-cv().getInt32(firstData+records.permonst.fields.pmidx.offset,true)*records.permonst.size,pmC=speciesBase+L.PM_PONY*records.permonst.size;
  // Real source creation supplies the complete monster and inventory state.
  const ponyJ=Number(js(()=>env.resolve('makemon')(pmJ,x+1,y,0))),ponyC=BigInt(ref._makemon(BigInt(pmC),x+1,y,0));assert.ok(ponyJ&&ponyC);compare('pony creation');
  set('monst',ponyJ,ponyC,'mtame','signed char',20);set('monst',ponyJ,ponyC,'mpeaceful','unsigned int',1);
  action('can_saddle',[ponyJ],[ponyC]);action('can_ride',[ponyJ],[ponyC]);
  action('put_saddle_on_mon',[0,ponyJ],[0n,ponyC]);
  // Normal mount with a healthy, tame, saddled pony and adequate riding skill.
  set('you',hJ,hC,'ulevel','int',30);
  action('mount_steed',[ponyJ,0],[ponyC,0]);assert.ok(jf('you',hJ,'usteed','void *'));
  action('exercise_steed');action('kick_steed');action('rider_cant_reach');action('stucksteed',[0]);
  // maybewakesteed is source-private and already exercised by mounting.
  action('dismount_steed',[L.DISMOUNT_BYCHOICE]);equal(Number(jf('you',hJ,'usteed','void *')),0,'actually dismounted');
  const [sJ,sC]=inventory(L.SADDLE);action('tty_clear_nhwindow',[Number(env.ctypes.load('int',env.requireGlobal('WIN_MESSAGE')))]);input('\x1b');action('use_saddle',[sJ],[sC]);action('tty_clear_nhwindow',[Number(env.ctypes.load('int',env.requireGlobal('WIN_MESSAGE')))]);input('\x1b');action('doride');
 }
 if(mode==='menus'){
  const L=layouts.iactions,command=JSON.parse(fs.readFileSync('js/standalone/command-abi.json'));
  const queue=heap=>{const j=heap.buffer===env.memory.buffer,v=new DataView(heap.buffer),ptr=p=>Number(v.getBigUint64(p,true)),base=(j?env.requireGlobal('gc'):globals.gc)+records.instance_globals_c.fields.command_queue.offset,rows=[];for(let q=0;q<2;q++){let p=ptr(base+q*8),list=[];while(p){const f=records._cmd_queue.fields,type=v.getInt32(p+f.typ.offset,true),entry=ptr(p+f.ec_entry.offset);let ec=null;if(type===layouts.cmd.CMDQ_EXTCMD&&entry){const offset=command.records.ext_func_tab.fields.ef_txt.offset,at=ptr(entry+offset);ec=j?env.memory.readString(at):cstring(at);}list.push({type,key:type===layouts.cmd.CMDQ_KEY?v.getInt8(p+f.key.offset):null,ec});p=ptr(p+f.next.offset);}rows.push(list);}return rows;};
  const wieldJ=Number(env.ctypes.load('struct obj *',env.requireGlobal('uwep'))),wieldC=cv().getBigUint64(globals.uwep,true);assert.ok(wieldJ&&wieldC);input('-\n');action('itemactions',[wieldJ],[wieldC]);equal(queue(env.memory.HEAPU8),queue(ref.HEAPU8),'unwield menu command identity');assert.ok(queue(env.memory.HEAPU8)[layouts.cmd.CQ_CANNED].length>0,'actual unwield selection queued');action('cmdq_clear',[layouts.cmd.CQ_CANNED]);
  for(const name of ['SADDLE','OIL_LAMP','SCR_BLANK_PAPER','DAGGER','FOOD_RATION']){
   const [j,c]=inventory(L[name]??layouts.apply[name]??layouts.write[name]??layouts.extralev[name]);
   input('\x1b');action('itemactions',[j],[c]);equal(queue(env.memory.HEAPU8),queue(ref.HEAPU8),'cancelled menu queues');
   input(name==='SADDLE'?'a\n':'d\n');action('itemactions',[j],[c]);equal(queue(env.memory.HEAPU8),queue(ref.HEAPU8),'selected menu exact command/key queues');assert.ok(queue(env.memory.HEAPU8)[layouts.cmd.CQ_CANNED].length>0,'actual menu action queued');
   action('cmdq_clear',[layouts.cmd.CQ_CANNED]);
  }
 }
 if(mode==='music'){
  const L=layouts.music;
  for(const name of ['MAGIC_FLUTE','MAGIC_HARP','TOOLED_HORN','BUGLE','FIRE_HORN','FROST_HORN','LEATHER_DRUM','DRUM_OF_EARTHQUAKE']){
   action('tty_clear_nhwindow',[Number(env.ctypes.load('int',env.requireGlobal('WIN_MESSAGE')))]);
   const [j,c]=inventory(L[name]);set('obj',j,c,'spe','signed char',5);
   input((name.includes('DRUM')?'':name.endsWith('HORN')&&name!=='TOOLED_HORN'?'yl':'y')+' '.repeat(30));
   action('do_play_instrument',[j],[c]);
   if(['MAGIC_FLUTE','MAGIC_HARP','FIRE_HORN','FROST_HORN','DRUM_OF_EARTHQUAKE'].includes(name))equal(jf('obj',j,'spe','signed char'),4,name+' actually used a magical charge');
  }
 }
 if(mode==='rogue'){
  action('makeroguerooms');
  const offset=records.instance_globals_r.fields.r.offset,size=9*records.rogueroom.size;
  equal(Buffer.from(env.memory.HEAPU8.slice(env.requireGlobal('gr')+offset,env.requireGlobal('gr')+offset+size)),Buffer.from(ref.HEAPU8.slice(globals.gr+offset,globals.gr+offset+size)),'complete private 3x3 rogue room grid');
  action('corr',[1,1]);action('makerogueghost');
 }
 const result={checks,hashes,cases,complete:true,fullGameAccepted:false,mode};fs.writeFileSync(output,JSON.stringify(result,null,2)+'\n');console.log('PASS '+JSON.stringify(result));
}finally{Date.now=savedNow;if(savedTZ===undefined)delete process.env.TZ;else process.env.TZ=savedTZ;}
