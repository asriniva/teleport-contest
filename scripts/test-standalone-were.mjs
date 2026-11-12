import {layoutSourceSha} from './nethack-layout.mjs';
// Genuine original main/world, then original WERE public calls on both heaps.
import assert from 'node:assert/strict';import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import{pathToFileURL}from'node:url';
import{C,R,T}from'../js/c-runtime/context.js';
import{createStandaloneProgram}from'../js/nethack/program.js';import{enableWere}from'../js/nethack/were.js';
const directory=path.resolve(process.env.STANDALONE_WERE_ORACLE??'.cache/full-original-c-v1'),layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L=layouts.were,records=JSON.parse(fs.readFileSync('js/nethack/records.json')).records;
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex'),receipt=JSON.parse(fs.readFileSync(directory+'/receipt.json'));let hashes=0,checks=0;
for(const[p,h]of Object.entries(receipt.sourceSha256)){assert.equal(layoutSourceSha(p,h),h,p);hashes++;}for(const[p,h]of Object.entries(receipt.artifactSha256)){assert.equal(layoutSourceSha(directory+'/'+p,h),h,p);hashes++;}
const abi=JSON.parse(fs.readFileSync('js/nethack/were-abi.json'));for(const[p,h]of Object.entries(abi.sourceSha256)){assert.equal(layoutSourceSha(p,h),h,p);hashes++;}
function js(fn){const keys=['WebAssembly','fetch','XMLHttpRequest','WebSocket','Worker'],saved=keys.map(k=>Object.getOwnPropertyDescriptor(globalThis,k));const forbidden=()=>{throw new Error('Forbidden production Wasm/network during WERE');};for(const k of keys)Object.defineProperty(globalThis,k,{configurable:true,value:k==='WebAssembly'?new Proxy({},{get:forbidden}):forbidden});try{return fn();}finally{keys.forEach((k,i)=>saved[i]?Object.defineProperty(globalThis,k,saved[i]):delete globalThis[k]);assert.deepEqual([C,R,T],[undefined,undefined,undefined]);}}
const equal=(a,b,label)=>{assert.deepEqual(a,b,label);checks++;},epoch=1777723200000,profile={NETHACKDIR:'/nethack',HACKDIR:'/nethack',HOME:'/home/player',USER:'root',LOGNAME:'root',MAIL:'/nethack/mailbox',TERM:'xterm-256color',TERMINFO:'/nethack/terminfo',LINES:'24',COLUMNS:'80',TZ:'America/Los_Angeles',NETHACK_NO_DELAY:'1',NOMUX_MARKERS:'1',NETHACK_RAW_KEYS:'1',NETHACK_SEED:'1',NETHACK_FIXED_DATETIME:process.env.STANDALONE_WERE_DATETIME??'20260102030405',NETHACK_RECORDING_EPOCH:'1777723200',NETHACK_RNGLOG:'/rng.log',NETHACK_RNGLOG_DISP:'/rng-display.log'};
const savedNow=Date.now,savedTZ=process.env.TZ;Date.now=()=>epoch;process.env.TZ=profile.TZ;
const keys='  n',argv=['-u','Ada-male-lawful','-p','Archeologist','-r','human'];let ji=0,ci=0,program;const stop=new Error('finite input exhausted'),entries=[];
const dirs=new Set();function dir(p){if(dirs.has(p))return;dirs.add(p);const parent=path.posix.dirname(p);if(parent!==p)dir(parent);entries.push({path:p,type:'dir',mode:0o777,atime:epoch,mtime:epoch,ctime:epoch});}
function asset(from,to){dir(to);for(const n of fs.readdirSync(from)){const a=from+'/'+n,b=to+'/'+n,s=fs.statSync(a);if(s.isDirectory())asset(a,b);else entries.push({path:b,type:'file',mode:s.mode&0o777,atime:epoch,mtime:epoch,ctime:epoch,base64:fs.readFileSync(a).toString('base64')});}}
try{
 asset(directory+'/assets','/nethack');dir('/nethack/save');dir('/home/player');entries.push({path:'/home/player/.nethackrc',type:'file',mode:0o666,atime:epoch,mtime:epoch,ctime:epoch,base64:''});
 program=createStandaloneProgram({layouts,runtime:{initialBytes:1024,maximumBytes:128*1024*1024,environment:profile,now:()=>epoch},filesystemSnapshot:{version:1,cwd:'/nethack',entries},readKey(){if(ji===keys.length)throw stop;return keys.charCodeAt(ji++);}});
 const env=program.environment,S=new Proxy(env.services,{get:(o,k)=>{const v=Reflect.get(o,k);return typeof v==='function'?(...a)=>js(()=>v(...a)):v;}});if(!env.hasFunction('were_change'))js(()=>enableWere(env,layouts));
 try{js(()=>program.run(argv,{programName:'nethack'}));assert.fail('JS must reach input boundary');}catch(e){if(e!==stop)throw e;}
 const{default:factory}=await import(pathToFileURL(directory+'/out/game.mjs'));
 const ref=await factory({noInitialRun:true,thisProgram:'nethack',teleportCapture(){},teleportReadKey(){if(ci===keys.length)throw'unwind';return keys.charCodeAt(ci++);},print(){},printErr(){},preRun:[m=>{Object.assign(m.ENV,profile);m.FS.mkdirTree('/home/player');m.FS.writeFile('/home/player/.nethackrc','');}]});ref.FS.mkdirTree('/nethack/save');ref.FS.chdir('/nethack');ref.callMain([...argv]);
 equal([ji,ci],[3,3],'actual source main reaches first gameplay input');
 const cstring=p=>{p=Number(p);let n=p;while(ref.HEAPU8[n])n++;return Buffer.from(ref.HEAPU8.slice(p,n)).toString();},globals={};for(let i=0;i<ref._full_global_count();i++)globals[cstring(ref._full_global_name(i))]=Number(ref._full_global_address(i));
 const cv=()=>new DataView(ref.HEAPU8.buffer),jf=(type,p,key,ctype)=>env.ctypes.getField('struct '+type,p,key,ctype),cf=(type,p,key,ctype)=>{const f=records[type].fields[key];if(ctype==='pointer')return Number(cv().getBigUint64(p+f.offset,true));return ctype==='long'?cv().getBigInt64(p+f.offset,true):cv().getInt32(p+f.offset,true);};
 const rng=()=>{const state=env.state('rnd');return state.rnglist.map(({rng_state:s})=>{const b=Buffer.alloc(layouts.rnd.size);b.writeBigUInt64LE(BigInt(s.n),layouts.rnd.n);for(const k of['r','m'])for(let i=0;i<256;i++)b.writeBigUInt64LE(s[k][i],layouts.rnd[k]+8*i);for(const k of['a','b','c'])b.writeBigUInt64LE(s[k],layouts.rnd[k]);return b;});};
 const compareRng=label=>equal(rng(),[0,1].map(i=>{const p=Number(ref._full_rng_state(i));return Buffer.from(ref.HEAPU8.slice(p,p+Number(ref._full_rng_size())));}),label+' complete two RNG states');
 compareRng('startup');for(let pm=-1;pm<=L.NUMMONS;pm++){equal(S.counter_were(pm),ref._counter_were(pm),'counter '+pm);equal(S.were_beastie(pm),ref._were_beastie(pm),'beastie '+pm);}
 const mons=(heap,root)=>{const v=new DataView(heap.buffer),rows=[];let p=Number(v.getBigUint64(root,true));while(p){rows.push(p);p=Number(v.getBigUint64(p+records.monst.fields.nmon.offset,true));}return rows;};
 const listOffset=records.instance_globals_saved_l.fields.level.offset+records.dlevel_t.fields.monlist.offset,jroot=env.requireGlobal('svl')+listOffset,croot=globals.svl+listOffset;
 const jmons=mons(env.memory.HEAPU8,jroot),cmons=mons(ref.HEAPU8,croot);equal(jmons.length,cmons.length,'real starter monster count');assert.ok(jmons.length);
 const firstData=Number(cv().getBigUint64(cmons[0]+L.mon_data,true));globals.mons=firstData-cv().getInt32(firstData+L.permonstIndex,true)*L.permonstSize;
 for(let i=0;i<jmons.length;i++){S.were_change(jmons[i]);ref._were_change(BigInt(cmons[i]));}compareRng('ordinary live monsters');
 const monState=(heap,p)=>{const b=Buffer.from(heap.slice(p,p+records.monst.size));for(const name of['nmon','data','minvent','mw','mextra']){const f=records.monst.fields[name];if(f){const ptr=Number(b.readBigUInt64LE(f.offset));b.writeBigUInt64LE(name==='data'&&ptr?BigInt(new DataView(heap.buffer).getInt32(ptr+L.permonstIndex,true)+1):ptr?1n:0n,f.offset);}}return b;};
 for(let i=0;i<jmons.length;i++)equal(monState(env.memory.HEAPU8,jmons[i]),monState(ref.HEAPU8,cmons[i]),'ordinary monster complete bytes '+i);
 const setpm=(jp,cp,pm)=>{S.set_mon_data(jp,env.requireGlobal('mons')+pm*L.permonstSize);ref._set_mon_data(BigInt(cp),BigInt(globals.mons+pm*L.permonstSize));};
 const property=(id,value)=>{const offset=L.heroProps+id*L.propSize+L.propIntrinsic;env.memory.view.setBigInt64(env.requireGlobal('u')+offset,value,true);cv().setBigInt64(globals.u+offset,value,true);};
 const jp=jmons[0],cp=cmons[0];
 console.log('WERE foreign functions without registered owners:',Object.values(abi.calls).filter(n=>!env.hasFunction(n)&&typeof env.services[n]!=='function'));
 const heroBytes=(heap,p)=>{const b=Buffer.from(heap.slice(p,p+records.you.size));for(const f of Object.values(records.you.fields))if(f.ctype.includes('*'))b.writeBigUInt64LE(b.readBigUInt64LE(f.offset)?1n:0n,f.offset);return b;};
 const compareHero=label=>equal(heroBytes(env.memory.HEAPU8,env.requireGlobal('u')),heroBytes(ref.HEAPU8,globals.u),label+' full hero bytes, pointer presence normalized');
 const visibleJ=env.memory.calloc(1,4),bufferJ=env.memory.calloc(1,256),visibleC=BigInt(ref._malloc(4n)),bufferC=BigInt(ref._malloc(256n));
 for(const pm of[L.PM_HUMAN_WERERAT,L.PM_HUMAN_WEREJACKAL,L.PM_HUMAN_WEREWOLF]){
  property(L.PROT_FROM_SHAPE_CHANGERS,1n);env.memory.view.setInt32(visibleJ,123,true);cv().setInt32(Number(visibleC),123,true);S.strcpy(bufferJ,S.literal('UNCHANGED'));ref.HEAPU8.set(Buffer.from('UNCHANGED\0'),Number(bufferC));
  equal(S.were_summon(env.requireGlobal('mons')+pm*L.permonstSize,0,visibleJ,bufferJ),ref._were_summon(BigInt(globals.mons+pm*L.permonstSize),0,visibleC,bufferC),'protected summon count '+pm);
  equal(env.memory.view.getInt32(visibleJ,true),cv().getInt32(Number(visibleC),true),'addressable visible count copyback '+pm);equal(env.memory.readString(bufferJ),cstring(bufferC),'protected summon preserves buffer '+pm);compareRng('protected summon '+pm);compareHero('protected summon '+pm);
  setpm(jp,cp,pm);S.new_were(jp);ref._new_were(BigInt(cp));equal(monState(env.memory.HEAPU8,jp),monState(ref.HEAPU8,cp),'protected human no transformation '+pm);compareRng('protected human '+pm);
 }
 property(L.UNCHANGING,1n);S.you_were();ref._you_were();compareHero('unchanging source hero guard');compareRng('unchanging hero');property(L.UNCHANGING,0n);
 property(L.PROT_FROM_SHAPE_CHANGERS,0n);S.you_unwere(0);ref._you_unwere(0);compareHero('nonwere hero cure noaction');compareRng('nonwere hero');
 if(process.env.STANDALONE_WERE_EXTENDED==='1'){
 for(const pm of[L.PM_HUMAN_WERERAT,L.PM_HUMAN_WEREJACKAL,L.PM_HUMAN_WEREWOLF]){
  setpm(jp,cp,pm);property(L.PROT_FROM_SHAPE_CHANGERS,1n);S.new_were(jp);ref._new_were(BigInt(cp));equal(monState(env.memory.HEAPU8,jp),monState(ref.HEAPU8,cp),'protected human no transformation '+pm);compareRng('protected '+pm);
  property(L.PROT_FROM_SHAPE_CHANGERS,0n);S.new_were(jp);ref._new_were(BigInt(cp));equal(monState(env.memory.HEAPU8,jp),monState(ref.HEAPU8,cp),'real beast transformation '+pm);compareRng('transform '+pm);
  property(L.PROT_FROM_SHAPE_CHANGERS,1n);S.were_change(jp);ref._were_change(BigInt(cp));equal(monState(env.memory.HEAPU8,jp),monState(ref.HEAPU8,cp),'protected beast reverts '+pm);compareRng('revert '+pm);
 }
 }
 property(L.PROT_FROM_SHAPE_CHANGERS,0n);
 if(process.env.STANDALONE_WERE_SUMMON==='1'){
 const date=profile.NETHACK_FIXED_DATETIME;equal(js(()=>env.calendar('night')),ref._night(),'actual calendar night '+date);
 const cfn=BigInt(ref._full_rng_function(0)),jfn=Number(env.functionPointer('rn2','ii'));
 for(const moon of[0,L.FULL_MOON])for(const deaf of[0,1]){
  env.ctypes.setField('struct flag',env.requireGlobal('flags'),'moonphase','unsigned int',moon);cv().setUint32(globals.flags+L.flagsMoonphase,moon,true);
  const roleOffset=records.you.fields.uroleplay.offset+records.u_roleplay.fields.deaf.offset;env.memory.view.setInt8(env.requireGlobal('u')+roleOffset,deaf);cv().setInt8(globals.u+roleOffset,deaf);
  const bound=ref._night()?(moon===L.FULL_MOON?3:30):(moon===L.FULL_MOON?10:50);let seed=0n;for(;seed<1024n;seed++){ref._init_isaac64(seed,cfn);if(ref._rn2(bound)===0)break;}assert.ok(seed<1024n,'Source-seeded transformation case found');
  S.init_isaac64(seed,jfn);ref._init_isaac64(seed,cfn);setpm(jp,cp,L.PM_HUMAN_WEREWOLF);S.were_change(jp);ref._were_change(BigInt(cp));equal(monState(env.memory.HEAPU8,jp),monState(ref.HEAPU8,cp),'source day/night/moon/deaf transformation '+date+'/'+moon+'/'+deaf);equal(env.memory.view.getBigInt64(env.requireGlobal('gw')+L.wereChanges,true),cv().getBigInt64(globals.gw+L.wereChanges,true),'source were_changes counter');compareRng('night/moon/deaf '+date+'/'+moon+'/'+deaf);compareHero('roleplay deaf '+deaf);
 }
 const roleOffset=records.you.fields.uroleplay.offset+records.u_roleplay.fields.deaf.offset;env.memory.view.setInt8(env.requireGlobal('u')+roleOffset,0);cv().setInt8(globals.u+roleOffset,0);
 for(const pm of[L.PM_HUMAN_WERERAT,L.PM_HUMAN_WEREJACKAL,L.PM_HUMAN_WEREWOLF])for(const yours of[0,1]){
  equal(S.were_summon(env.requireGlobal('mons')+pm*L.permonstSize,yours,visibleJ,bufferJ),ref._were_summon(BigInt(globals.mons+pm*L.permonstSize),yours,visibleC,bufferC),'actual summon count '+pm+'/'+yours);
  equal(env.memory.view.getInt32(visibleJ,true),cv().getInt32(Number(visibleC),true),'actual summon visible count '+pm+'/'+yours);equal(env.memory.readString(bufferJ),cstring(bufferC),'actual summon buffer '+pm+'/'+yours);
  const jm=mons(env.memory.HEAPU8,jroot),cm=mons(ref.HEAPU8,croot);equal(jm.length,cm.length,'summoned list length');for(let i=0;i<jm.length;i++){equal(monState(env.memory.HEAPU8,jm[i]),monState(ref.HEAPU8,cm[i]),'summoned actual full monster '+pm+'/'+yours+'/'+i);const je=Number(env.memory.view.getBigUint64(jm[i]+records.monst.fields.mextra.offset,true)),ce=Number(cv().getBigUint64(cm[i]+records.monst.fields.mextra.offset,true));const jd=je?Number(env.memory.view.getBigUint64(je+records.mextra.fields.edog.offset,true)):0,cd=ce?Number(cv().getBigUint64(ce+records.mextra.fields.edog.offset,true)):0;equal(Boolean(jd),Boolean(cd),'summoned edog owner');if(jd)equal(Buffer.from(env.memory.readBytes(jd,records.edog.size)),Buffer.from(ref.HEAPU8.slice(cd,cd+records.edog.size)),'summoned complete edog state');}compareRng('actual summon '+pm+'/'+yours);compareHero('actual summon '+pm+'/'+yours);
 }
 }
 console.log(`PASS WERE: ${checks} comparisons; ${hashes} bound inputs/artifacts; full startup, ordinary monsters, protection/copyback and hero guards. Extended transformations: ${process.env.STANDALONE_WERE_EXTENDED==='1'}.`);
 const evidence={checks,hashes,input:{profile,argv,keys},scope:'Original main first command boundary, all mapping IDs, live ordinary monsters, protection/output pointers, hero guards; transformations if extended; actual day/night/moon and successful untamed/tamed summons if summon. Hero polymorph and remaining branches unaccepted.',extended:process.env.STANDALONE_WERE_EXTENDED==='1',summon:process.env.STANDALONE_WERE_SUMMON==='1',referenceSha256:sha(directory+'/receipt.json'),sourceSha256:Object.fromEntries(['scripts/test-standalone-were.mjs','js/nethack/were.js','js/nethack/were-abi.json'].map(p=>[p,sha(p)]))};fs.writeFileSync(directory+'/were-evidence-'+profile.NETHACK_FIXED_DATETIME+'.json',JSON.stringify(evidence,null,2)+'\n');
}finally{Date.now=savedNow;if(savedTZ===undefined)delete process.env.TZ;else process.env.TZ=savedTZ;}
