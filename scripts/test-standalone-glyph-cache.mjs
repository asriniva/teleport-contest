import assert from 'node:assert/strict';
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/standalone/environment.js';
import {createNativeTerminal} from '../js/platform/darwin/terminal.js';
import {createTerminalDevices} from '../js/standalone/unix-terminal.js';
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),seed=1n;
const directory=path.resolve(process.env.STANDALONE_GLYPH_CACHE_ORACLE||'.cache/standalone-glyph-cache-v1');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json'))),sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const [p,h]of Object.entries(receipt.sourceSha256))assert.equal(sha(p),h,'Changed reference input '+p);
for(const [p,h]of Object.entries(receipt.artifactSha256))assert.equal(sha(path.join(directory,p)),h,'Changed reference artifact '+p);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs')));
const errors=[],entry=fs.readFileSync('nethack-c/wasm/terminfo/x/xterm-256color');
const nativeTerminal=createNativeTerminal();
// SDK TCGETS leaves speed fields untouched. Initialize the transport scratch
// identically on both sides; this defines inputs, without masking policy output.
const ref=await factory({nethackPorted:{nativeTerminal:(services,name,...args)=>nativeTerminal({...services,stackAlloc:n=>{const p=services.stackAlloc(n);services.heap().fill(0,p,p+n);return p;}},name,...args)},print:()=>{},printErr:s=>errors.push(s),preRun:[m=>{m.FS.mkdirTree('/nethack/terminfo/x');m.FS.writeFile('/nethack/terminfo/x/xterm-256color',entry);} ]});
for(const [name,value]of Object.entries({NOMUX_MARKERS:'1',TERM:'xterm-256color',TERMINFO:'/nethack/terminfo',LINES:'24',COLUMNS:'80'})){const p=ref._malloc(BigInt(name.length+value.length+2));ref.HEAPU8.set(Buffer.from(name+'\0'+value+'\0'),Number(p));ref._setenv(BigInt(p),BigInt(Number(p)+name.length+1),1);ref._free(BigInt(p));}
let checks=0;
const deviceEnv=createStandaloneEnvironment(),devices=createTerminalDevices(deviceEnv,layouts),cp=Number(ref._malloc(96n)),jp=deviceEnv.memory.malloc(96),bytes=()=>ref.HEAPU8.slice(cp,cp+96);
for(const fill of [0,0xa5,0xff])for(const fd of [0,1,2,99]){
 for(const op of ['attr','size']){
  ref.HEAPU8.fill(fill,cp,cp+96);deviceEnv.memory.memset(jp,fill,96);ref._probe_tty_errno(73);deviceEnv.libc.errno=73;
  assert.equal(op==='attr'?devices.tcgetattr(fd,jp):devices.ioctl(fd,layouts.ioctl.TIOCGWINSZ,jp),op==='attr'?ref._probe_tty_attr(fd,BigInt(cp)):ref._probe_tty_winsize(fd,BigInt(cp)),`device ${op} fd=${fd}`);
  assert.deepEqual(deviceEnv.memory.readBytes(jp,96),bytes(),'device preserves unspecified bytes');assert.equal(deviceEnv.libc.errno,ref._probe_tty_errno(73));checks+=3;
 }
 for(const action of [-1,0,1,2,3]){
  ref._probe_tty_errno(73);deviceEnv.libc.errno=73;
  assert.equal(devices.tcsetattr(fd,action,jp),ref._probe_tty_setattr(fd,action,BigInt(cp)));assert.equal(deviceEnv.libc.errno,ref._probe_tty_errno(73));checks+=2;
 }
 assert.equal(devices.cfgetospeed(jp),Number(ref._probe_tty_speed(BigInt(cp))));checks++;
}
for(let name=0;name<23;name++){
 ref._probe_tty_errno(73);deviceEnv.libc.errno=73;
 assert.equal(devices.fpathconf(0,name),BigInt(ref._probe_tty_pathconf(0,name)),'SDK pathconf '+name);assert.equal(deviceEnv.libc.errno,ref._probe_tty_errno(73));checks+=2;
}
 const env=createStandaloneEnvironment({initialBytes:1024,maximumBytes:64*1024*1024,environment:{TERM:'xterm-256color',NOMUX_MARKERS:'1',NETHACK_RNGLOG:'/rng.log',NETHACK_FIXED_DATETIME:'20260102030405'}});
 env.enableStdio();env.enableDecl(layouts.decl);env.call('decl','program_state_init');env.call('decl','decl_globals_init');env.enableDrawing(layouts.drawing);env.enableObjects(layouts.objects);env.call('objects','objects_globals_init');env.enableMonst(layouts.monst);env.call('monst','monst_globals_init');env.enableSerialization(layouts);env.enableRnd(layouts.rnd,{seed});env.call('rnd','rng_log_init');env.enableAddressPort('dungeon',{only:['ledger_no','maxledgerno']});env.enableObjectState(layouts);env.enableObjectRecords(layouts);env.enableItemInventory(layouts);env.enableTimers(layouts);env.enableItemNaming(layouts);const group=env.enableMonsterSelection(layouts);const decl=JSON.parse(fs.readFileSync('js/standalone/decl-storage.json')).globals,before=decl.map(r=>env.memory.readBytes(env.requireGlobal(r.name),r.bytes));const creation=env.enableMonsterCreation(layouts);decl.forEach((r,i)=>assert.deepEqual(env.memory.readBytes(env.requireGlobal(r.name),r.bytes),before[i],'enabling creation preserves '+r.name));

 env.enableGameStartup(layouts);env.call('sys','sys_early_init');
const hero=env.enableHeroStartup(layouts);env.enableWorldPosition(layouts);env.enableLuaSandbox(layouts);env.enableDisplayStartup(layouts);

ref._probe_level_init(seed);
env.enableWindowSystem(layouts);env.enableVersionInfo(layouts);env.enableOptions(layouts);env.enableSymbols(layouts);const glyphs=env.enableGlyphs(layouts),abi=JSON.parse(fs.readFileSync('js/standalone/glyph-abi.json'));
for(const g of [-2147483648,-1,...Array.from({length:layouts.glyphs.MAX_GLYPH+2},(_,i)=>i),2147483647])for(let i=0;i<abi.headers.length;i++){assert.equal(glyphs.services.header(i,g),ref._teleport_glyphs_header(i,g),'original glyph header '+abi.headers[i]+':'+g);checks++;}
const jbuf=env.memory.malloc(256),cbuf=Number(ref._malloc(256n));for(let i=0;i<256;i++){env.memory.HEAPU8[jbuf+i]=i;ref.HEAPU8[cbuf+i]=i;}
for(const n of [0,1,7,63,255,256])for(const byte of [-257,-1,0,1,7,63,254,255,256,511]){const j=env.services.memchr(jbuf,byte,n),c=Number(ref._memchr(BigInt(cbuf),byte,BigInt(n)));assert.equal(j?j-jbuf:-1,c?c-cbuf:-1,'original libc bounded byte search '+byte+':'+n);checks++;}
assert.equal(env.services.glyphid_cache_status(),ref._glyphid_cache_status(),'initial cache absence');checks++;
env.services.fill_glyphid_cache();ref._fill_glyphid_cache();assert.equal(env.services.glyphid_cache_status(),ref._glyphid_cache_status(),'source cache construction');checks++;
const count=Number(ref._probe_glyph_cache_count()),cachePointer=Number(glyphs.services.get(0,9,glyphs.finds));assert.ok(cachePointer&&count);assert.equal(env.memory.live.get(cachePointer).size,count*layouts.glyphs.cacheEntrySize,'source allocated cache extent');checks++;
const text=(heap,p)=>{p=Number(p);if(!p)return null;let end=p;while(heap[end])end++;return Buffer.from(heap.slice(p,end)).toString('latin1');};let entries=0;const ownedIds=[];
for(let i=0;i<count;i++){const cp=Number(ref._probe_glyph_cache_entry(BigInt(i))),j=cachePointer+i*layouts.glyphs.cacheEntrySize,cv=new DataView(ref.HEAPU8.buffer);assert.equal(Number(glyphs.services.get(1,0,j)),cv.getInt32(cp,true),'source hash table slot '+i);checks++;const idPointer=Number(glyphs.services.get(1,1,j)),id=text(env.memory.HEAPU8,idPointer),cid=text(ref.HEAPU8,cv.getBigUint64(cp+8,true));assert.equal(id,cid,'source cache ID '+i);if(id){entries++;assert.ok(env.memory.live.has(idPointer),'source cache ID allocation is owned');ownedIds.push(idPointer);checks++;}checks++;}
assert.ok(entries>0&&entries<=layouts.glyphs.MAX_GLYPH,'source ID catalogue has populated entries and skips unsupported IDs');checks++;
env.services.free_glyphid_cache();ref._free_glyphid_cache();assert.equal(env.services.glyphid_cache_status(),ref._glyphid_cache_status(),'cache cleanup state');assert.ok(!env.memory.live.has(cachePointer),'cache allocation freed');checks+=2;for(const p of ownedIds){assert.ok(!env.memory.live.has(p),'source cache ID freed during cleanup');checks++;}
console.log(`PASS: ${checks} original-C glyph headers, full cache slots/${entries} IDs, cleanup and bounded memchr comparisons; full options/display remain unfinished.`);
