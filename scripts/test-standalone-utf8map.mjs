// Genuine original C main/world, then optional interactions on both live heaps.
import assert from 'node:assert/strict';import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import{pathToFileURL}from'node:url';
import {worldGraph} from './restoration-world-graph.mjs';
import {encodeRecorderScreen} from '../js/wasm-replay-support.js';
import {enableUtf8map} from '../js/standalone/utf8map.js';
import{C,R,T}from'../js/c-runtime/context.js';
import{createStandaloneProgram}from'../js/standalone/program.js';import{enableWere}from'../js/standalone/were.js';import{enableDogmove}from'../js/standalone/dogmove.js';
const directory=path.resolve(process.env.STANDALONE_FULL_C_REFERENCE??'.cache/full-original-c-v1'),layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L=layouts.were,records=JSON.parse(fs.readFileSync('js/standalone/records.json')).records;
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex'),receipt=JSON.parse(fs.readFileSync(directory+'/receipt.json'));let hashes=0,checks=0;
for(const[p,h]of Object.entries(receipt.sourceSha256)){assert.equal(sha(p),h,p);hashes++;}for(const[p,h]of Object.entries(receipt.artifactSha256)){assert.equal(sha(directory+'/'+p),h,p);hashes++;}
const abi=JSON.parse(fs.readFileSync('js/standalone/utf8map-abi.json'));for(const[p,h]of Object.entries(abi.sourceSha256)){assert.equal(sha(p),h,p);hashes++;}
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
 js(()=>enableUtf8map(env,layouts));
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



 const output=process.env.SPECIAL_INTERACTIONS_OUTPUT??'.cache/utf8map-evidence.json';
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
 const U=layouts.utf8map,meta=abi.fields,cinfo=Number(ref._malloc(BigInt(layouts.utf8map.GlyphInfoSize)));
 const jstr=value=>{const bytes=Buffer.from(value+'\0'),p=env.memory.malloc(bytes.length);env.memory.HEAPU8.set(bytes,p);return p;};
 const cstr=value=>{const bytes=Buffer.from(value+'\0'),p=Number(ref._malloc(BigInt(bytes.length)));ref.HEAPU8.set(bytes,p);return p;};
 const cptr=(global,field)=>globals[global]+records['instance_globals_'+global.slice(1)].fields[field].offset;
 function symbols(heap,j){
  const v=new DataView(heap.buffer),ptr=p=>Number(v.getBigUint64(p,true)),str=p=>{if(!p)return null;let end=p;while(heap[end])end++;return Buffer.from(heap.slice(p,end)).toString('hex');};
  const globalsAt=n=>j?env.requireGlobal(n):globals[n],at=name=>globalsAt(meta[name].global)+meta[name].offset;
  const identity=new Map();let nextId=0;const id=p=>{if(!p)return null;if(!identity.has(p))identity.set(p,nextId++);return identity.get(p);};
  const unicode=p=>p?{id:id(p),ch:v.getUint32(p+U.unicodeUtf32ch,true),string:str(ptr(p+U.unicodeUtf8str))}:null;
  const glyph=p=>{const bytes=Buffer.from(heap.slice(p,p+U.GlyphMapSize)),u=ptr(p+U.glyphMapU);bytes.fill(0,U.glyphMapU,U.glyphMapU+8);return{bytes:bytes.toString('hex'),u:unicode(u)};};
  const maps=Array.from({length:U.MAX_GLYPH},(_,i)=>{if(!j)ref._map_glyphinfo(0,0,i,0,BigInt(cinfo));return glyph(j?globalsAt('glyphmap')+i*U.GlyphMapSize:cinfo+U.glyphInfoGm);});
  const buffer=Array.from({length:U.COLNO*U.ROWNO},(_,i)=>{const p=at('gbuf')+i*U.GbufEntrySize,bytes=Buffer.from(heap.slice(p,p+U.GbufEntrySize)),gm=U.gbufGlyphinfo+U.glyphInfoGm;bytes.fill(0,gm,gm+U.GlyphMapSize);return{bytes:bytes.toString('hex'),gm:glyph(p+gm)};});
  const custom=Array.from({length:U.NUM_GRAPHICS+1},(_,set)=>Array.from({length:U.custom_count},(_,kind)=>{const p=at('customizations')+(set*U.custom_count+kind)*U.CustomizationSize,head=ptr(p+U.customDetails),tail=ptr(p+U.customDetailsEnd),list=[];let d=head;const seen=new Set();while(d){assert.ok(!seen.has(d),'acyclic customization list');seen.add(d);const n=ptr(d+U.detailNext);list.push({id:id(d),glyph:v.getInt32(d+U.detailGlyphidx,true),u:unicode(d+U.detailUnicode),next:id(n)});d=n;}assert.equal(tail,list.length?[...seen].at(-1):0,'actual customization tail');return{name:str(ptr(p+U.customName)),count:v.getInt32(p+U.customCount,true),type:v.getInt32(p+U.customType,true),head:id(head),tail:id(tail),list};}));
  return{maps,buffer,custom};
 }
 const check=label=>{equal(symbols(env.memory.HEAPU8,true),symbols(ref.HEAPU8,false),label+' complete glyph/buffer/customization state');compare(label);};
 function action(name,jargs=[],cargs=jargs){const a=js(()=>env.resolve(name)(...jargs)),b=ref['_'+name](...cargs);equal(Number(a??0),Number(b??0),name+' return');check(name);}
 // Original codepoint parser: valid, invalid, overlong and byte cases.
 for(const value of ['', 'U+0041','u+03A9','U+1F409','U+10FFFF','U+0000','U+FFFFFFFF','U+123456789','U+GG','U+41tail','41','U-0041','\u0080']){action('unicode_val',[jstr(value)],[BigInt(cstr(value))]);}
 action('unicode_val',[0],[0n]);
 const mapJ=env.memory.malloc(U.GlyphMapSize),mapC=Number(ref._malloc(BigInt(U.GlyphMapSize)));env.memory.HEAPU8.fill(0,mapJ,mapJ+U.GlyphMapSize);ref.HEAPU8.fill(0,mapC,mapC+U.GlyphMapSize);
 for(const [ch,value]of [[0x03a9,'Ω'],[0x1f409,'🐉'],[0,'ignored'],[65,'A']])action('set_map_u',[mapJ,ch,jstr(value)],[BigInt(mapC),ch,BigInt(cstr(value))]);
 const ju=Number(env.memory.view.getBigUint64(mapJ+U.glyphMapU,true)),cu=Number(cv().getBigUint64(mapC+U.glyphMapU,true));equal(env.memory.view.getUint32(ju+U.unicodeUtf32ch,true),cv().getUint32(cu+U.unicodeUtf32ch,true),'detached map codepoint');equal(env.memory.readString(Number(env.memory.view.getBigUint64(ju+U.unicodeUtf8str,true))),cstring(cv().getBigUint64(cu+U.unicodeUtf8str,true)),'detached map string');
 // All fixture UTF-8 is encoded explicitly, preserving the existing byte-string contract.
 // The configured C declaration marks set_map_u pointers nonnull; a null
 // map is outside that contract and the optimized C can discard its guard.
 for(const [set,glyph,ch,value]of [[U.PRIMARYSET,0,0x03a9,'Ω'],[U.PRIMARYSET,1,0x1f409,'🐉'],[U.PRIMARYSET,0,66,'B'],[U.ROGUESET,0,67,'C'],[U.PRIMARYSET,1,0,''],[U.PRIMARYSET,1,0x1f409,'🐉']])action('add_custom_urep_entry',[S.literal('utf8 fixture'),glyph,ch,jstr(value),set],[BigInt(cstr('utf8 fixture')),glyph,ch,BigInt(cstr(value)),set]);
 // Enable the actual UTF-8 handling mode and customization flag on both heaps.
 const handling=records.symsetentry.fields.handling.offset,syms=records.instance_globals_s.fields.symset.offset;
 for(const set of [U.PRIMARYSET,U.ROGUESET]){const jp=env.requireGlobal('gs')+syms+set*records.symsetentry.size,cp=globals.gs+syms+set*records.symsetentry.size;env.ctypes.setField('struct symsetentry',jp,'handling','enum symset_handling_types',layouts.symbols.H_UTF8);cv().setInt32(cp+handling,layouts.symbols.H_UTF8,true);}
 env.ctypes.setField('struct instance_flags',env.requireGlobal('iflags'),'customsymbols','signed char',1);ref.HEAPU8[globals.iflags+records.instance_flags.fields.customsymbols.offset]=1;
 action('apply_customizations',[U.PRIMARYSET,U.do_custom_symbols]);
 // Live gbuf entry aliases the same mapped Unicode allocation before cleanup.
 ref._map_glyphinfo(0,0,0,0,BigInt(cinfo));const slot=3*U.COLNO+4,jo=env.requireGlobal('gg')+meta.gbuf.offset+slot*U.GbufEntrySize+U.gbufGlyphinfo+U.glyphInfoGm,co=globals.gg+meta.gbuf.offset+slot*U.GbufEntrySize+U.gbufGlyphinfo+U.glyphInfoGm;env.memory.HEAPU8.copyWithin(jo,env.requireGlobal('glyphmap'),env.requireGlobal('glyphmap')+U.GlyphMapSize);ref.HEAPU8.copyWithin(co,cinfo+U.glyphInfoGm,cinfo+U.glyphInfoGm+U.GlyphMapSize);check('live mapped-buffer alias');
 const outJ=env.memory.malloc(128),outC=Number(ref._malloc(128n)),flagJ=env.memory.malloc(4),flagC=Number(ref._malloc(4n));
 const encode=glyph=>{const j=Number(js(()=>env.resolve('encglyph')(glyph))),c=Number(ref._encglyph(glyph));equal(env.memory.readString(j),cstring(c),'source glyph encoding');return env.memory.readString(j);};
 const encoded=encode(0),multibyte=encode(1),fallback=encode(2);
 // Both actual heaps grow while the same provider/globals remain installed.
 const beforeJ=env.memory.HEAPU8.length,beforeC=ref.HEAPU8.length;assert.ok(js(()=>env.memory.malloc(beforeJ+65536)));assert.ok(Number(ref._malloc(BigInt(beforeC+65536))));assert.ok(env.memory.HEAPU8.length>beforeJ);assert.ok(ref.HEAPU8.length>beforeC);check('actual heap growth');
 for(const value of [null,'ordinary text','ends with \\','a\\\\b','\\Gbadinput',encoded+' suffix',encoded+encoded,multibyte+' suffix',multibyte+fallback])for(const size of [0,1,2,5,32]){
  env.memory.HEAPU8.fill(0xa5,outJ,outJ+128);ref.HEAPU8.fill(0xa5,outC,outC+128);env.memory.view.setInt32(flagJ,12345,true);cv().setInt32(flagC,12345,true);
  const result=js(()=>env.resolve('mixed_to_utf8')(outJ,size,value===null?0:jstr(value),flagJ)),native=Number(ref._mixed_to_utf8(BigInt(outC),BigInt(size),value===null?0n:BigInt(cstr(value)),BigInt(flagC)));
  equal(result,outJ,'mixed destination');equal(native,outC,'native mixed destination');equal(Buffer.from(env.memory.HEAPU8.slice(outJ,outJ+128)),Buffer.from(ref.HEAPU8.slice(outC,outC+128)),'mixed output and complete guard/tail');equal(env.memory.view.getInt32(flagJ,true),cv().getInt32(flagC,true),'retflags write semantics');
 }
 check('mixed conversions');
 action('free_all_glyphmap_u');action('free_all_glyphmap_u');action('reset_customsymbols');
 const result={checks,hashes,cases,complete:true,fullGameAccepted:false,scope:'Original configured Unicode symbol parser/mappings/customization lists/mixed text/cleanup on an actual initialized game; no claim for all terminal glyph sets.'};fs.writeFileSync(output,JSON.stringify(result,null,2)+'\n');console.log('PASS '+JSON.stringify(result));
}finally{Date.now=savedNow;if(savedTZ===undefined)delete process.env.TZ;else process.env.TZ=savedTZ;}
