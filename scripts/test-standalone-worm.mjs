import assert from 'node:assert/strict';
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import {pathToFileURL} from 'node:url';
import {enableWorms} from '../js/standalone/worm.js';
import {createStandaloneEnvironment} from '../js/standalone/environment.js';
import {createNativeTerminal} from '../js/services/native-terminal.js';
import {createTerminalDevices} from '../js/standalone/unix-terminal.js';
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
const directory=path.resolve(process.env.STANDALONE_WORM_ORACLE||'.cache/standalone-worm-v4');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json'))),sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const [p,h]of Object.entries(receipt.sourceSha256))assert.equal(sha(p),h,'Changed reference input '+p);
for(const [p,h]of Object.entries(receipt.artifactSha256))assert.equal(sha(path.join(directory,p)),h,'Changed reference artifact '+p);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs')));
let totalChecks=0;
const seeds=process.env.STANDALONE_WORM_SEED?[BigInt(process.env.STANDALONE_WORM_SEED)]:[1n],roles=process.env.STANDALONE_WORM_ROLE?[Number(process.env.STANDALONE_WORM_ROLE)]:[0];
const selectedMasks=process.env.STANDALONE_WORM_ROLEPLAY?[Number(process.env.STANDALONE_WORM_ROLEPLAY)]:[0],inputs=seeds.flatMap(seed=>roles.flatMap(role=>selectedMasks.map(roleplay=>({seed,role,roleplay}))));
for(const {seed,role,roleplay} of inputs){
const errors=[],entry=fs.readFileSync('nethack-c/wasm/terminfo/x/xterm-256color');
const nativeTerminal=createNativeTerminal();
// SDK TCGETS leaves speed fields untouched. Initialize the transport scratch
// identically on both sides; this defines inputs, without masking policy output.
const ref=await factory({nethackPorted:{nativeTerminal:(services,name,...args)=>nativeTerminal({...services,stackAlloc:n=>{const p=services.stackAlloc(n);services.heap().fill(0,p,p+n);return p;}},name,...args)},print:()=>{},printErr:s=>errors.push(s),preRun:[m=>{m.FS.mkdirTree('/nethack/terminfo/x');m.FS.writeFile('/nethack/terminfo/x/xterm-256color',entry);} ]});
for(const [name,value]of Object.entries({NOMUX_MARKERS:'1',TERM:'xterm-256color',TERMINFO:'/nethack/terminfo',LINES:'24',COLUMNS:'80'})){const p=ref._malloc(BigInt(name.length+value.length+2));ref.HEAPU8.set(Buffer.from(name+'\0'+value+'\0'),Number(p));ref._setenv(BigInt(p),BigInt(Number(p)+name.length+1),1);ref._free(BigInt(p));}
const coutput=[],tty=ref.FS.getStream(1).tty;assert.ok(tty,'C stdout remains a real tty');const originalPut=tty.ops.put_char;tty.ops={...tty.ops,put_char:(t,c)=>{if(c!==null)coutput.push(c);return originalPut(t,c);}};
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
 const capabilityNames=['WebAssembly','fetch','XMLHttpRequest'],capabilities=capabilityNames.map(name=>[name,Object.getOwnPropertyDescriptor(globalThis,name)]);let forbiddenCalls=0;
 const forbidden=()=>{forbiddenCalls++;throw new Error('Forbidden capability during standalone startup');};
 Object.defineProperty(globalThis,'WebAssembly',{configurable:true,value:new Proxy({}, {get:forbidden})});
 for(const name of ['fetch','XMLHttpRequest'])Object.defineProperty(globalThis,name,{configurable:true,value:forbidden});
 const env=createStandaloneEnvironment({initialBytes:1024,maximumBytes:64*1024*1024,environment:{TERM:'xterm-256color',NOMUX_MARKERS:'1',NETHACK_RNGLOG:'/rng.log',NETHACK_FIXED_DATETIME:'20260102030405',NETHACK_SEED:seed.toString()}});
 const stdio=env.enableStdio();env.enableDecl(layouts.decl);env.call('decl','program_state_init');env.call('decl','decl_globals_init');env.enableDrawing(layouts.drawing);env.enableObjects(layouts.objects);env.call('objects','objects_globals_init');env.enableMonst(layouts.monst);env.call('monst','monst_globals_init');env.enableSerialization(layouts);env.enableRnd(layouts.rnd,{seed});env.call('rnd','rng_log_init');env.enableAddressPort('dungeon',{only:['ledger_no','maxledgerno']});env.enableObjectState(layouts);env.enableObjectRecords(layouts);env.enableItemInventory(layouts);env.enableTimers(layouts);env.enableItemNaming(layouts);const group=env.enableMonsterSelection(layouts);const decl=JSON.parse(fs.readFileSync('js/standalone/decl-storage.json')).globals,before=decl.map(r=>env.memory.readBytes(env.requireGlobal(r.name),r.bytes));const creation=env.enableMonsterCreation(layouts);decl.forEach((r,i)=>assert.deepEqual(env.memory.readBytes(env.requireGlobal(r.name),r.bytes),before[i],'enabling creation preserves '+r.name));

 const startup=env.enableGameStartup(layouts);env.call('sys','sys_early_init');
env.enableHeroStartup(layouts);env.enableWorldPosition(layouts);env.enableLuaSandbox(layouts);env.enableDisplayStartup(layouts);
for(const name of fs.readdirSync(process.env.STANDALONE_REFERENCE_ROOT+'/.cache/wasm64-build/tree/dat').filter(n=>n.endsWith('.lua')))env.filesystem.writeFile(name,fs.readFileSync(process.env.STANDALONE_REFERENCE_ROOT+'/.cache/wasm64-build/tree/dat/'+name));
for(const name of ['epitaph','engrave','rumors','bogusmon','oracles'])env.filesystem.writeFile(name,fs.readFileSync(process.env.STANDALONE_REFERENCE_ROOT+'/.cache/wasm64-build/tree/dat/'+name));
env.filesystem.writeFile('sysconf',fs.readFileSync(process.env.STANDALONE_REFERENCE_ROOT+'/.cache/wasm64-build/assets/sysconf'));
Object.assign(env.services.flags,{initrole:role,initrace:0,initgend:0,initalign:0,female:0,pantheon:-1});env.services.strcpy(startup.role.svp.plname,env.services.literal('Ada'));
env.enableLevelStartup(layouts);const contents=env.enableLevelContents(layouts);env.services.vision_init();const window=env.enableWindowSystem(layouts);env.enableVersionInfo(layouts);env.enableOptions(layouts);env.enableSymbols(layouts);env.enableGlyphs(layouts);env.enableCommands(layouts);env.enableConfiguration(layouts);env.enableFiles(layouts);env.enableStatus(layouts);env.enableGameWindows(layouts);env.enableMovement(layouts);env.enablePets(layouts);env.enableMonsterMovement(layouts);env.enableMonsterLifecycle(layouts);const equipment=env.enableHeroEquipment(layouts);const worms=enableWorms(env,layouts);env.services.choose_windows('tty');env.services.initoptions();Object.assign(env.services.flags,{initrole:role,initrace:0,initgend:0,initalign:0,female:0,pantheon:-1});
for(const [i,name]of ['blind','nudist','deaf','pauper','reroll','reserved1','reserved2','reserved3'].entries())env.services.u.uroleplay[name]=(roleplay>>i)&1;
const argc=env.memory.calloc(1,4),argv=env.memory.calloc(2,8);env.memory.view.setInt32(argc,1,true);env.memory.view.setBigUint64(argv,BigInt(env.services.literal('nethack')),true);env.services.tty_init_nhwindows(argc,argv);env.services.init_sound_disp_gamewindows();assert.throws(()=>env.services.newgame(),/Unresolved standalone function com_pager/);env.services.fflush(stdio.stdout);assert.equal(forbiddenCalls,0,'Pure JS startup invokes no Wasm/network capability');checks++;for(const [name,descriptor]of capabilities){if(descriptor)Object.defineProperty(globalThis,name,descriptor);else delete globalThis[name];}

ref._probe_level_init(seed);const assets=process.env.STANDALONE_REFERENCE_ROOT+'/.cache/wasm64-build/tree/dat/';for(const name of fs.readdirSync(assets).filter(n=>n.endsWith('.lua')).concat(['epitaph','engrave','rumors','bogusmon','oracles']))ref.FS.writeFile(name,fs.readFileSync(assets+name));
for(const [key,value]of Object.entries({NETHACK_FIXED_DATETIME:'20260102030405',NETHACK_RNGLOG:'/rng.log',NETHACK_SEED:seed.toString()})){const p=ref._malloc(BigInt(key.length+value.length+2));ref.HEAPU8.set(Buffer.from(key+'\0'+value+'\0'),Number(p));ref._setenv(BigInt(p),BigInt(Number(p)+key.length+1),1);ref._free(BigInt(p));}
ref.FS.writeFile('sysconf',fs.readFileSync(process.env.STANDALONE_REFERENCE_ROOT+'/.cache/wasm64-build/assets/sysconf'));
const player=ref._malloc(4n);ref.HEAPU8.set(Buffer.from('Ada\0'),Number(player));ref._probe_startup_role_config(role,0,0,0,BigInt(player));ref._free(player);ref._vision_init();const type=ref._malloc(4n);ref.HEAPU8.set(Buffer.from('tty\0'),Number(type));ref._probe_window_select(BigInt(type));ref._free(type);ref._initoptions();const chosen=ref._malloc(4n);ref.HEAPU8.set(Buffer.from('Ada\0'),Number(chosen));ref._probe_startup_role_config(role,0,0,0,BigInt(chosen));ref._free(chosen);ref._probe_window_init();ref._init_sound_disp_gamewindows();
const metadata=JSON.parse(fs.readFileSync('js/standalone/records.json')).records;
const callbackNames=JSON.parse(fs.readFileSync('js/standalone/armor-abi.json')).callbacks,jCallbacks=callbackNames.map((_,i)=>equipment.armor.callbackPointer(i)),cCallbacks=callbackNames.map((_,i)=>ref._probe_equipment_callback(i));
function callbackIdentity(heap,p){if(!p)return null;const table=heap.buffer===env.memory.HEAPU8.buffer?jCallbacks:cCallbacks,index=table.findIndex(value=>BigInt(value)===BigInt(p));assert.ok(index>=0,'Known source equipment callback');return callbackNames[index];}
function snapshot(heap,at,type,count=1){
 at=Number(at);const record=metadata[type]??(['short','long'].includes(type)?{size:type==='short'?2:8,fields:{}}:null);assert.ok(record,'Measured snapshot '+type);const bytes=Buffer.from(heap.slice(at,at+record.size*count)),strings={};
 function walk(type,offset,label){for(const [name,f]of Object.entries(metadata[type]?.fields??{})){
  const arr=f.ctype.match(/\[(\d+)\]/),n=arr?Number(arr[1]):1,child=f.record||f.ctype.match(/struct (\w+)/)?.[1];
  if(f.ctype.includes('*')||(name==='luacore'&&f.ctype==='genericptr_t luacore'))for(let i=0;i<n;i++){
   const pos=offset+f.offset+i*8,p=Number(bytes.readBigUInt64LE(pos));
   if(/char\s*\*/.test(f.ctype)){let end=p;if(p){while(heap[end])end++;strings[label+'.'+name+'['+i+']']=Buffer.from(heap.slice(p,end)).toString('latin1');}else strings[label+'.'+name+'['+i+']']=null;}
   else if(name==='afternmv'){strings[label+'.'+name+'['+i+']']=callbackIdentity(heap,p);}else if(p){const target=f.ctype.replace(/^struct /,'').split(' *')[0];if(name==='luacore'){strings[label+'.'+name+'['+i+']']='Lua state';}else if(target==='permonst'){const pm=new DataView(heap.buffer).getInt32(p+metadata.permonst.fields.pmidx.offset,true);strings[label+'.'+name+'['+i+']']={species:pm};}else if(target==='monst'){strings[label+'.'+name+'['+i+']']={monsterId:new DataView(heap.buffer).getUint32(p+metadata.monst.fields.m_id.offset,true)};}else{assert.ok(['s_level','branch'].includes(target),'Unmodeled non-string pointer '+label+'.'+name);strings[label+'.'+name+'['+i+']']=snapshot(heap,p,target);}}
   bytes.writeBigUInt64LE(p?1n:0n,pos);
  }else if(child&&metadata[child])for(let i=0;i<n;i++)walk(child,offset+f.offset+i*metadata[child].size,label+'.'+name+'['+i+']');
 }}
 for(let i=0;i<count;i++)walk(type,i*record.size,type+'['+i+']');return {bytes,strings};
}
const visionRows=contents.vision.rows.map((row,i)=>({...row,bytes:Number(ref._probe_vision_storage_size(i)),j:contents.vision.storage[i],c:Number(ref._probe_vision_storage(i))}));
const gv=env.requireGlobal('gv'),cgv=Number(ref._probe_decl_global(decl.findIndex(r=>r.name==='gv'))),svl=env.requireGlobal('svl'),csvl=Number(ref._probe_hero_global(9));
// Explicit roleplay input bytes: eight compiler-measured boolean fields.
const rp=metadata.you.fields.uroleplay.offset;for(const [i,name]of ['blind','nudist','deaf','pauper','reroll','reserved1','reserved2','reserved3'].entries())ref.HEAPU8[Number(ref._probe_hero_global(3))+rp+metadata.u_roleplay.fields[name].offset]=(roleplay>>i)&1;
assert.throws(()=>ref._probe_startup_newgame(),/abort|unreachable/i);assert.ok(errors.some(s=>s.includes('Observed C boundary: com_pager')),errors.join('\n'));
const cglobal=name=>{if(name==='objects')return Number(ref._probe_startup_global(7));const i=decl.findIndex(row=>row.name===name);assert.ok(i>=0,'Known DECL global '+name);return Number(ref._probe_decl_global(i));};
for(const [name,type,count]of [['u','you',1],['flags','flag',1],['disp','display_hints',1],['svs','instance_globals_saved_s',1],['svb','instance_globals_saved_b',1],['objects','objclass',layouts.o_init.NUM_OBJECTS]]){assert.deepEqual(snapshot(env.memory.HEAPU8,env.requireGlobal(name),type,count),snapshot(ref.HEAPU8,cglobal(name),type,count),'source activated equipment/skills/discovery state '+name);checks++;}
const pointer=(heap,p)=>Number(new DataView(heap.buffer).getBigUint64(p,true));
function inventoryGraph(heap,first,ids=new Map()){
 const rows=[];for(let p=first;p;p=pointer(heap,p+metadata.obj.fields.nobj.offset)){
  assert.ok(!ids.has(p),'Acyclic inventory');ids.set(p,ids.size+1);const bytes=Buffer.from(heap.slice(p,p+metadata.obj.size));
  for(const f of Object.values(metadata.obj.fields))if(f.ctype.includes('*')||f.record==='vptrs')bytes.fill(0,f.offset,f.offset+8);
  const extra=pointer(heap,p+metadata.obj.fields.oextra.offset),contents=pointer(heap,p+metadata.obj.fields.cobj.offset);let name=null;
  if(extra){const at=pointer(heap,extra+metadata.oextra.fields.oname.offset);if(at){let end=at;while(heap[end])end++;name=Buffer.from(heap.slice(at,end)).toString('latin1');}}
  rows.push({bytes,name,contents:contents?inventoryGraph(heap,contents,ids).rows:[]});
 }return {rows,ids};
}
const inventoryOffset=metadata.instance_globals_i.fields.invent.offset,ji=inventoryGraph(env.memory.HEAPU8,pointer(env.memory.HEAPU8,env.requireGlobal('gi')+inventoryOffset)),ci=inventoryGraph(ref.HEAPU8,pointer(ref.HEAPU8,cglobal('gi')+inventoryOffset));
assert.deepEqual(ji.rows,ci.rows,'source equipped inventory records/order/contents/names/worn masks');checks++;
for(const name of JSON.parse(fs.readFileSync('js/standalone/equipment-abi.json')).worn.equipment){const j=pointer(env.memory.HEAPU8,env.requireGlobal(name)),c=pointer(ref.HEAPU8,cglobal(name));assert.equal(j?ji.ids.get(j):null,c?ci.ids.get(c):null,'source equipment slot identity '+name);if(j)assert.ok(ji.ids.has(j),'Equipped object belongs to inventory');if(c)assert.ok(ci.ids.has(c),'C equipped object belongs to inventory');checks++;}
const actual=Buffer.from(stdio.captured(1)),expected=Buffer.from(coutput);fs.writeFileSync('.cache/worm-'+seed+'-'+role+'-'+roleplay+'-js.stdout',actual);fs.writeFileSync('.cache/worm-'+seed+'-'+role+'-'+roleplay+'-c.stdout',expected);
assert.deepEqual(actual,expected,'actual original-C first display terminal bytes');checks++;
assert.ok(!actual.includes(0),'First-display acceptance requires initialized symbols; matching NUL map output is incomplete bootstrap');assert.ok(actual.includes(64),'Default first display must contain the visible hero glyph');
assert.deepEqual(Buffer.from(env.filesystem.readFile('/rng.log')),Buffer.from(ref.FS.readFile('/rng.log')),'actual full startup prefix RNG sequence');checks++;
function pointerAlias(p,isJS){if(!p)return null;const row=visionRows.find(r=>r.c&&p>=(isJS?r.j:r.c)&&p<(isJS?r.j:r.c)+r.bytes);assert.ok(row,'Known vision buffer address');return {storage:row.name,offset:p-(isJS?row.j:row.c)};}
function visionImage(row,heap,isJS){const p=isJS?row.j:row.c,bytes=Buffer.from(heap.slice(p,p+row.bytes)),refs=[];let d=row.d,n=1;if(d.a){n=d.a.reduce((n,k)=>n*k,1);d=d.e;}if(d.q||d.p!==undefined||d.f)for(let i=0;i<n;i++){const ptr=Number(bytes.readBigUInt64LE(8*i));if(d.f){assert.equal(ptr,0,'No active traversal callback');refs.push(null);}else refs.push(pointerAlias(ptr,isJS));bytes.fill(0,8*i,8*i+8);}return {bytes,refs};}
for(const row of visionRows)if(row.c){assert.deepEqual(visionImage(row,env.memory.HEAPU8,true),visionImage(row,ref.HEAPU8,false),'source vision storage '+row.name);checks++;}
for(const key of ['viz_array','viz_rmin','viz_rmax']){const off=metadata.instance_globals_v.fields[key].offset,j=Number(env.memory.view.getBigUint64(gv+off,true)),c=Number(new DataView(ref.HEAPU8.buffer).getBigUint64(cgv+off,true));assert.deepEqual(pointerAlias(j,true),pointerAlias(c,false),'source live vision root '+key);checks++;}
const locations=metadata.instance_globals_saved_l.fields.level.offset+metadata.dlevel_t.fields.locations.offset,count=80*21*metadata.rm.size;
assert.deepEqual(env.memory.readBytes(svl+locations,count),ref.HEAPU8.slice(csvl+locations,csvl+locations+count),'source complete terrain/seen/glyph matrix');checks++;
assert.deepEqual(env.memory.readBytes(env.requireGlobal('seenv_matrix'),9),ref.HEAPU8.slice(Number(ref._probe_first_display_matrix()),Number(ref._probe_first_display_matrix())+9),'source shared directional seen matrix');checks++;

// Original WORM operations follow the fully compared source startup prefix.
function protectedJS(fn){
 Object.defineProperty(globalThis,'WebAssembly',{configurable:true,value:new Proxy({}, {get:forbidden})});
 for(const name of ['fetch','XMLHttpRequest'])Object.defineProperty(globalThis,name,{configurable:true,value:forbidden});
 try{return fn();}finally{for(const [name,descriptor]of capabilities){if(descriptor)Object.defineProperty(globalThis,name,descriptor);else delete globalThis[name];}}
}
function graphs(){return {
 j:inventoryGraph(env.memory.HEAPU8,pointer(env.memory.HEAPU8,env.requireGlobal('gi')+inventoryOffset)),
 c:inventoryGraph(ref.HEAPU8,pointer(ref.HEAPU8,cglobal('gi')+inventoryOffset)),
};}
const slotNames=JSON.parse(fs.readFileSync('js/standalone/equipment-abi.json')).worn.equipment;
const monsterRootOffset=metadata.instance_globals_saved_l.fields.level.offset+metadata.dlevel_t.fields.monlist.offset;
function monsterNodes(heap,root){
 const nodes=[],seen=new Set();for(let p=pointer(heap,root+monsterRootOffset);p;p=pointer(heap,p+metadata.monst.fields.nmon.offset)){
  assert.ok(!seen.has(p),'Acyclic live monster list');seen.add(p);const view=new DataView(heap.buffer),id=view.getUint32(p+metadata.monst.fields.m_id.offset,true);assert.ok(!nodes.some(row=>row.id===id),'Unique live monster identity');nodes.push({p,id});
 }return nodes;
}
function monsterImage(heap,root){return monsterNodes(heap,root).map(({p,id})=>{
 const bytes=Buffer.from(heap.slice(p,p+metadata.monst.size));for(const f of Object.values(metadata.monst.fields))if(f.ctype.includes('*')){const value=bytes.readBigUInt64LE(f.offset);bytes.writeBigUInt64LE(value?1n:0n,f.offset);}
 const species=pointer(heap,p+metadata.monst.fields.data.offset),pm=species?new DataView(heap.buffer).getInt32(species+metadata.permonst.fields.pmidx.offset,true):null,items=pointer(heap,p+metadata.monst.fields.minvent.offset);
 return {id,pm,bytes,inventory:items?inventoryGraph(heap,items).rows:[]};
});}
function compareAction(label){
 for(const [name,type,count]of [['u','you',1],['flags','flag',1],['disp','display_hints',1],['svs','instance_globals_saved_s',1],['svb','instance_globals_saved_b',1],['objects','objclass',layouts.o_init.NUM_OBJECTS],['ga','instance_globals_a',1],['gn','instance_globals_n',1],['gm','instance_globals_m',1],['svc','instance_globals_saved_c',1],['gu','instance_globals_u',1]]){
  assert.deepEqual(snapshot(env.memory.HEAPU8,env.requireGlobal(name),type,count),snapshot(ref.HEAPU8,cglobal(name),type,count),label+' shared '+name);checks++;
 }
 const {j,c}=graphs();assert.deepEqual(j.rows,c.rows,label+' inventory records/contents/masks');checks++;
 for(const name of slotNames){const jp=pointer(env.memory.HEAPU8,env.requireGlobal(name)),cp=pointer(ref.HEAPU8,cglobal(name));assert.equal(jp?j.ids.get(jp):null,cp?c.ids.get(cp):null,label+' equipment slot '+name);if(jp)assert.ok(j.ids.has(jp));if(cp)assert.ok(c.ids.has(cp));checks++;}
 assert.deepEqual(monsterImage(env.memory.HEAPU8,env.requireGlobal('svl')),monsterImage(ref.HEAPU8,cglobal('svl')),label+' live monster identities/nonpointer bytes/resistance memory/visibility fields/inventory');checks++;
 assert.deepEqual(Buffer.from(env.filesystem.readFile('/rng.log')),Buffer.from(ref.FS.readFile('/rng.log')),label+' RNG log');checks++;
 assert.equal(forbiddenCalls,0,label+' has no Wasm/network capability calls');checks++;
}
function callBoth(name,jArgs=[],cArgs=jArgs,result='scalar'){
 const j=protectedJS(()=>env.services[name](...jArgs)),c=ref['_'+name](...cArgs);
 if(result==='pointer'){const graph=graphs();assert.equal(j?graph.j.ids.get(Number(j)):null,c?graph.c.ids.get(Number(c)):null,name+' result identity');if(j)assert.ok(graph.j.ids.has(Number(j)));if(c)assert.ok(graph.c.ids.has(Number(c)));}
 else if(result!=='void')assert.equal(j,c,name+' result');
 checks++;return {j,c};
}
const W=layouts.worm,monSize=metadata.monst.size;
function chainImage(heap,tail,head){
 const dv=new DataView(heap.buffer),out=[],seen=new Set();
 for(let p=Number(tail);p;p=Number(dv.getBigUint64(p+W.seg_nseg,true))){
  assert.ok(!seen.has(p),'Acyclic source worm chain');seen.add(p);
  out.push({x:dv.getInt16(p+W.seg_wx,true),y:dv.getInt16(p+W.seg_wy,true),head:p===Number(head)});
 }return out;
}
function wormImage(isJS){const heap=isJS?env.memory.HEAPU8:ref.HEAPU8;return Array.from({length:W.MAX_NUM_WORMS},(_,slot)=>({
 time:isJS?worms.state.wgrowtime[slot]:ref._probe_worm_time(slot),
 chain:chainImage(heap,isJS?worms.state.wtails[slot]:ref._probe_worm_segment(0,slot),isJS?worms.state.wheads[slot]:ref._probe_worm_segment(1,slot)),
}));}
const gridOffset=metadata.instance_globals_saved_l.fields.level.offset+metadata.dlevel_t.fields.monsters.offset;
function gridImage(heap,root){const dv=new DataView(heap.buffer);return Array.from({length:W.COLNO*W.ROWNO},(_,i)=>{const p=Number(dv.getBigUint64(root+gridOffset+i*8,true));return p?dv.getUint32(p+metadata.monst.fields.m_id.offset,true):null;});}
function checkWorm(label){
 compareAction(label);assert.deepEqual(wormImage(true),wormImage(false),label+' complete source worm chains/head identities/signed growth times');checks++;
 assert.deepEqual(gridImage(env.memory.HEAPU8,env.requireGlobal('svl')),gridImage(ref.HEAPU8,cglobal('svl')),label+' every shared monster grid cell');checks++;
 assert.deepEqual(env.memory.readBytes(svl+locations,count),ref.HEAPU8.slice(csvl+locations,csvl+locations+count),label+' full terrain/seen/glyph matrix');checks++;
}
checkWorm('before worm creation');
let target;
for(let attempt=0;attempt<8&&!target;attempt++){
 const c=Number(ref._probe_worm_create()),j=Number(protectedJS(()=>env.services.makemon(env.requireGlobal('mons')+W.PM_LONG_WORM*W.permonstSize,0,0,layouts.makemon.MM_NOMSG)));
 assert.equal(Boolean(j),Boolean(c),'Source MAKEMON allocation result');assert.ok(j,'Source worm construction succeeds');
 const slot=env.ctypes.getField('struct monst',j,'wormno','unsigned int');assert.ok(slot>0,'Real worm owns a source slot');
 checkWorm('actual long worm creation '+attempt);
 if(worms.state.wtails[slot]!==worms.state.wheads[slot])target={j,c,slot};
}
assert.ok(target,'Source construction produces a nonempty segmented worm');
const {j:jm,c:cm,slot}=target;
assert.ok(wormImage(true)[slot].chain.length>1,'Tail includes real segments and hidden head');
function setTime(value){worms.state.wgrowtime[slot]=value;ref._probe_worm_set_time(slot,value);checkWorm('matched signed growth input');}
function headMove(){
 const mon=env.ctypes,at=jm,x=mon.getField('struct monst',at,'mx','short'),y=mon.getField('struct monst',at,'my','short');
 const image=gridImage(env.memory.HEAPU8,env.requireGlobal('svl'));
 const next=[[x+1,y],[x-1,y],[x,y+1],[x,y-1]].find(([nx,ny])=>nx>0&&nx<W.COLNO&&ny>=0&&ny<W.ROWNO&&!image[nx*W.ROWNO+ny]);assert.ok(next,'Available adjacent source head input');
 // The source worm_move contract says its caller already moved the head.
 protectedJS(()=>{env.memory.view.setBigUint64(env.requireGlobal('svl')+gridOffset+(x*W.ROWNO+y)*8,0n,true);env.services.place_monster(jm,...next);});
 ref._probe_worm_move_head(BigInt(cm),...next);
 callBoth('worm_move',[jm],[BigInt(cm)],'void');checkWorm('real worm_move after caller head relocation');
}
headMove();callBoth('worm_nomove',[jm],[BigInt(cm)],'void');checkWorm('real worm_nomove');
setTime(-((1n<<53n)+7n));
const frame=env.memory.calloc(1,layouts.sfstruct.nhfileSize);
function io(name,mode,input){
 const fd=env.services.open('/worm-save',input?0:578,0o600);assert.ok(fd>=0);
 env.memory.memset(frame,0,layouts.sfstruct.nhfileSize);
 env.ctypes.store('int',frame+layouts.sfstruct.nhf_fd,fd);env.ctypes.store('int',frame+layouts.sfbase.nhf_mode,mode);env.ctypes.store('int',frame+layouts.sfbase.nhf_fnidx,layouts.sfbase.historical);env.ctypes.store('signed char',frame+layouts.sfbase.nhf_structlevel,1);
 const cf=ref._probe_worm_file(mode,Number(input));
 protectedJS(()=>env.services[name](frame));ref['_'+name](cf);
 if(input)env.services.close(fd);else env.services.bclose(fd);ref._probe_worm_file_close();
 const jb=Buffer.from(env.filesystem.readFile('/worm-save')),cb=Buffer.from(ref.FS.readFile('/worm-save'));assert.deepEqual(jb,cb,name+' actual SFBASE/SFSTRUCT file bytes');checks++;
 checkWorm(name+' mode '+mode);return jb;
}
const saved=io('save_worm',W.WRITING,false);assert.ok(saved.length>W.MAX_NUM_WORMS*8,'Nonempty source segment serialization');
io('save_worm',W.COUNTING,false);
env.filesystem.writeFile('/worm-save',saved);ref.FS.writeFile('/worm-save',saved);
callBoth('remove_worm',[jm],[BigInt(cm)],'void');checkWorm('source removal before release');
io('save_worm',W.FREEING,true);assert.equal(worms.state.wtails[slot],0,'FREEING releases original chains');
io('rest_worm',W.READING,true);
const mx=env.ctypes.getField('struct monst',jm,'mx','short'),my=env.ctypes.getField('struct monst',jm,'my','short');
protectedJS(()=>env.services.place_monster(jm,mx,my));ref._probe_worm_move_head(BigInt(cm),mx,my);
callBoth('place_wsegs',[jm,0],[BigInt(cm),0n],'void');checkWorm('restored original chain grid placement');
assert.equal(worms.state.wgrowtime[slot],-((1n<<53n)+7n),'Restored signed long exceeds Number precision');
setTime((1n<<53n)+9n);headMove();
callBoth('wormgone',[jm],[BigInt(cm)],'void');checkWorm('original wormgone and shared slot release');
callBoth('get_wormno');checkWorm('original reusable slot identity');
totalChecks+=checks;console.log('Compared source nonempty worm serialization/rest_worm/movement for seed '+seed+' role '+role+' ('+checks+' comparisons)');
}
console.log('PASS: '+totalChecks+' original-C standalone WORM/startup comparisons; full gameplay lifecycle remains unaccepted.');
