import assert from 'node:assert/strict';
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import {pathToFileURL} from 'node:url';
import {encodeRecorderScreen} from '../js/wasm-replay-support.js';
import {C,R,T} from '../js/c-runtime/context.js';
import {createStandaloneEnvironment} from '../js/standalone/environment.js';
import {createNativeTerminal} from '../js/platform/darwin/terminal.js';
import {createTerminalDevices} from '../js/standalone/unix-terminal.js';
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
const directory=path.resolve(process.env.STANDALONE_PAGER_STARTUP_ORACLE||'.cache/standalone-pager-startup-v1');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json'))),sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const [p,h]of Object.entries(receipt.sourceSha256))assert.equal(sha(p),h,'Changed reference input '+p);
for(const [p,h]of Object.entries(receipt.artifactSha256))assert.equal(sha(path.join(directory,p)),h,'Changed reference artifact '+p);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs')));
let totalChecks=0;
const seeds=process.env.STANDALONE_PAGER_SEED?[BigInt(process.env.STANDALONE_PAGER_SEED)]:[1n,0x12345678n,0xffffffffffffffffn],roles=process.env.STANDALONE_PAGER_ROLE?[Number(process.env.STANDALONE_PAGER_ROLE)]:Array.from({length:13},(_,i)=>i);
const selectedMasks=process.env.STANDALONE_PAGER_ROLEPLAY?[Number(process.env.STANDALONE_PAGER_ROLEPLAY)]:[0],inputs=seeds.flatMap(seed=>roles.flatMap(role=>selectedMasks.map(roleplay=>({seed,role,roleplay}))));
if(process.env.STANDALONE_PAGER_TARGETED)inputs.length=0;
if(!['STANDALONE_PAGER_SEED','STANDALONE_PAGER_ROLE','STANDALONE_PAGER_ROLEPLAY'].some(name=>process.env[name]))for(const [role,roleplay]of [[0,1],[0,2],[0,4],[4,8],[5,8],[6,8],[12,8],[12,15]])inputs.push({seed:1n,role,roleplay});
for(const {seed,role,roleplay} of inputs){
const errors=[],entry=fs.readFileSync('nethack-c/wasm/terminfo/x/xterm-256color');
const nativeTerminal=createNativeTerminal();
// Explicit finite host-boundary input for actual source More prompts.
const keySequence=Array.from({length:16},(_,i)=>i%2===0?32:13),ckeys=[],jkeys=[],ccaptures=[];
const nextKey=(seen,output)=>{assert.ok(seen.length<keySequence.length,'Pager exhausted its explicit input sequence');const bytes=Buffer.from(output);assert.match(bytes.toString('latin1').slice(-256),/--More--|\(end\)/,'A real source More prompt precedes each key request');const key=keySequence[seen.length];seen.push({key,terminalBytes:bytes.length,terminalSha256:crypto.createHash('sha256').update(bytes).digest('hex')});return key;};
// SDK TCGETS leaves speed fields untouched. Initialize the transport scratch
// identically on both sides; this defines inputs, without masking policy output.
const ref=await factory({teleportCapture:(screen,x,y,animation)=>ccaptures.push({screen:encodeRecorderScreen(screen),cursor:[x,y,1],animation:Boolean(animation)}),teleportReadKey:()=>nextKey(ckeys,coutput),nethackPorted:{nativeTerminal:(services,name,...args)=>nativeTerminal({...services,stackAlloc:n=>{const p=services.stackAlloc(n);services.heap().fill(0,p,p+n);return p;}},name,...args)},print:()=>{},printErr:s=>errors.push(s),preRun:[m=>{m.FS.mkdirTree('/nethack/terminfo/x');m.FS.writeFile('/nethack/terminfo/x/xterm-256color',entry);} ]});
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
for(const name of fs.readdirSync('/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/wasm64-build/tree/dat').filter(n=>n.endsWith('.lua')))env.filesystem.writeFile(name,fs.readFileSync('/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/wasm64-build/tree/dat/'+name));
for(const name of ['epitaph','engrave','rumors','bogusmon','oracles'])env.filesystem.writeFile(name,fs.readFileSync('/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/wasm64-build/tree/dat/'+name));
env.filesystem.writeFile('sysconf',fs.readFileSync(process.env.STANDALONE_REFERENCE_ROOT+'/.cache/wasm64-build/assets/sysconf'));
Object.assign(env.services.flags,{initrole:role,initrace:0,initgend:0,initalign:0,female:0,pantheon:-1});env.services.strcpy(startup.role.svp.plname,env.services.literal('Ada'));
env.enableLevelStartup(layouts);const contents=env.enableLevelContents(layouts);env.services.vision_init();const window=env.enableWindowSystem(layouts);env.enableVersionInfo(layouts);env.enableOptions(layouts);env.enableSymbols(layouts);env.enableGlyphs(layouts);env.enableCommands(layouts);env.enableConfiguration(layouts);env.enableFiles(layouts);env.enableStatus(layouts);env.enableGameWindows(layouts);env.enableMovement(layouts);env.enablePets(layouts);env.enableMonsterMovement(layouts);env.enableMonsterLifecycle(layouts);env.enableHeroEquipment(layouts);env.enableQuestPager(layouts);env.enableTerminalInput(layouts,{readKey:()=>nextKey(jkeys,stdio.captured(1))});env.enableTerminalMessages(layouts);env.enableMessages(layouts);env.services.choose_windows('tty');env.services.initoptions();Object.assign(env.services.flags,{initrole:role,initrace:0,initgend:0,initalign:0,female:0,pantheon:-1});
for(const [i,name]of ['blind','nudist','deaf','pauper','reroll','reserved1','reserved2','reserved3'].entries())env.services.u.uroleplay[name]=(roleplay>>i)&1;
const argc=env.memory.calloc(1,4),argv=env.memory.calloc(2,8);env.memory.view.setInt32(argc,1,true);env.memory.view.setBigUint64(argv,BigInt(env.services.literal('nethack')),true);env.services.tty_init_nhwindows(argc,argv);env.services.init_sound_disp_gamewindows();const stackBefore=env.transport.stackSave().index;assert.throws(()=>env.services.newgame(),/Unresolved standalone function save_currentstate/);assert.equal(env.transport.stackSave().index,stackBefore,'Source input/window callback frames restore the JS automatic stack');assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);checks+=4;env.services.fflush(stdio.stdout);assert.equal(forbiddenCalls,0,'Pure JS startup invokes no Wasm/network capability');checks++;for(const [name,descriptor]of capabilities){if(descriptor)Object.defineProperty(globalThis,name,descriptor);else delete globalThis[name];}

ref._probe_level_init(seed);const assets=process.env.STANDALONE_REFERENCE_ROOT+'/.cache/wasm64-build/tree/dat/';for(const name of fs.readdirSync(assets).filter(n=>n.endsWith('.lua')).concat(['epitaph','engrave','rumors','bogusmon','oracles']))ref.FS.writeFile(name,fs.readFileSync(assets+name));
for(const [key,value]of Object.entries({NETHACK_FIXED_DATETIME:'20260102030405',NETHACK_RNGLOG:'/rng.log',NETHACK_SEED:seed.toString()})){const p=ref._malloc(BigInt(key.length+value.length+2));ref.HEAPU8.set(Buffer.from(key+'\0'+value+'\0'),Number(p));ref._setenv(BigInt(p),BigInt(Number(p)+key.length+1),1);ref._free(BigInt(p));}
ref.FS.writeFile('sysconf',fs.readFileSync(process.env.STANDALONE_REFERENCE_ROOT+'/.cache/wasm64-build/assets/sysconf'));
const player=ref._malloc(4n);ref.HEAPU8.set(Buffer.from('Ada\0'),Number(player));ref._probe_startup_role_config(role,0,0,0,BigInt(player));ref._free(player);ref._vision_init();const type=ref._malloc(4n);ref.HEAPU8.set(Buffer.from('tty\0'),Number(type));ref._probe_window_select(BigInt(type));ref._free(type);ref._initoptions();const chosen=ref._malloc(4n);ref.HEAPU8.set(Buffer.from('Ada\0'),Number(chosen));ref._probe_startup_role_config(role,0,0,0,BigInt(chosen));ref._free(chosen);ref._probe_window_init();ref._init_sound_disp_gamewindows();
const metadata=JSON.parse(fs.readFileSync('js/standalone/records.json')).records;
function snapshot(heap,at,type,count=1){
 at=Number(at);const record=metadata[type]??(['short','long'].includes(type)?{size:type==='short'?2:8,fields:{}}:null);assert.ok(record,'Measured snapshot '+type);const bytes=Buffer.from(heap.slice(at,at+record.size*count)),strings={};
 function walk(type,offset,label){for(const [name,f]of Object.entries(metadata[type]?.fields??{})){
  const arr=f.ctype.match(/\[(\d+)\]/),n=arr?Number(arr[1]):1,child=f.record||f.ctype.match(/struct (\w+)/)?.[1];
  if(f.ctype.includes('*')||(name==='luacore'&&f.ctype==='genericptr_t luacore'))for(let i=0;i<n;i++){
   const pos=offset+f.offset+i*8,p=Number(bytes.readBigUInt64LE(pos));
   if(/char\s*\*/.test(f.ctype)){let end=p;if(p){while(heap[end])end++;strings[label+'.'+name+'['+i+']']=Buffer.from(heap.slice(p,end)).toString('latin1');}else strings[label+'.'+name+'['+i+']']=null;}
   else if(p){const target=f.ctype.replace(/^struct /,'').split(' *')[0];if(name==='luacore'){strings[label+'.'+name+'['+i+']']='Lua state';}else if(target==='permonst'){const pm=new DataView(heap.buffer).getInt32(p+metadata.permonst.fields.pmidx.offset,true);strings[label+'.'+name+'['+i+']']={species:pm};}else if(target==='monst'){strings[label+'.'+name+'['+i+']']={monsterId:new DataView(heap.buffer).getUint32(p+metadata.monst.fields.m_id.offset,true)};}else{assert.ok(['s_level','branch'].includes(target),'Unmodeled non-string pointer '+label+'.'+name);strings[label+'.'+name+'['+i+']']=snapshot(heap,p,target);}}
   bytes.writeBigUInt64LE(p?1n:0n,pos);
  }else if(child&&metadata[child])for(let i=0;i<n;i++)walk(child,offset+f.offset+i*metadata[child].size,label+'.'+name+'['+i+']');
 }}
 for(let i=0;i<count;i++)walk(type,i*record.size,type+'['+i+']');return {bytes,strings};
}
const visionRows=contents.vision.rows.map((row,i)=>({...row,bytes:Number(ref._probe_vision_storage_size(i)),j:contents.vision.storage[i],c:Number(ref._probe_vision_storage(i))}));
const gv=env.requireGlobal('gv'),cgv=Number(ref._probe_decl_global(decl.findIndex(r=>r.name==='gv'))),svl=env.requireGlobal('svl'),csvl=Number(ref._probe_hero_global(9));
// Explicit roleplay input bytes: eight compiler-measured boolean fields.
const rp=metadata.you.fields.uroleplay.offset;for(const [i,name]of ['blind','nudist','deaf','pauper','reroll','reserved1','reserved2','reserved3'].entries())ref.HEAPU8[Number(ref._probe_hero_global(3))+rp+metadata.u_roleplay.fields[name].offset]=(roleplay>>i)&1;
assert.throws(()=>ref._probe_startup_newgame(),/abort|unreachable/i);assert.ok(errors.some(s=>s.includes('Observed C boundary: save_currentstate')),errors.join('\n'));
assert.ok(window.terminal,'Fixture owns the actual terminal recorder');assert.deepEqual(window.terminal.frames,ccaptures,'Actual recorder-shadow frames/cursors/animation at input boundaries');assert.equal(ccaptures.length,ckeys.length,'Source input bridge captures each real key boundary');checks+=2;
assert.ok(jkeys.length>0,'Real legacy pager consumes explicit More input');assert.deepEqual(jkeys,ckeys,'Same key sequence and exact rendered boundaries consumed by source More prompts');assert.deepEqual(jkeys.map(row=>row.key),keySequence.slice(0,jkeys.length));checks+=3;
const cglobal=name=>{if(name==='objects')return Number(ref._probe_startup_global(7));const i=decl.findIndex(row=>row.name===name);assert.ok(i>=0,'Known DECL global '+name);return Number(ref._probe_decl_global(i));};
for(const [name,type,count]of [['u','you',1],['flags','flag',1],['disp','display_hints',1],['svs','instance_globals_saved_s',1],['svb','instance_globals_saved_b',1],['objects','objclass',layouts.o_init.NUM_OBJECTS]]){assert.deepEqual(snapshot(env.memory.HEAPU8,env.requireGlobal(name),type,count),snapshot(ref.HEAPU8,cglobal(name),type,count),'source activated equipment/skills/discovery state '+name);checks++;}
const pointer=(heap,p)=>Number(new DataView(heap.buffer).getBigUint64(p,true));
const winttyGlobals=Object.keys(JSON.parse(fs.readFileSync('js/standalone/window-abi.json')).wintty.schema.globals),ttyGlobal=name=>{const i=winttyGlobals.indexOf(name);assert.ok(i>=0,'Known original WINTTY global '+name);return Number(ref._probe_wintty_global(i));};
function displayState(heap,at){const view=new DataView(heap.buffer);return Object.fromEntries(Object.entries(metadata.DisplayDesc.fields).map(([name,field])=>[name,field.ctype.startsWith('short ')?view.getInt16(at+field.offset,true):field.ctype.startsWith('char ')?view.getInt8(at+field.offset):field.ctype.startsWith('uint32 ')?view.getUint32(at+field.offset,true):view.getInt32(at+field.offset,true)]));}
assert.deepEqual(displayState(env.memory.HEAPU8,pointer(env.memory.HEAPU8,env.requireGlobal('ttyDisplay'))),displayState(ref.HEAPU8,pointer(ref.HEAPU8,ttyGlobal('ttyDisplay'))),'Source display callback/input fields after actual pager');checks++;
assert.equal(env.memory.view.getInt8(env.requireGlobal('morc')),new DataView(ref.HEAPU8.buffer).getInt8(ttyGlobal('morc')),'Source More dismissal character');checks++;
function messageState(heap,gs,gt,wins,winMessage){
 const view=new DataView(heap.buffer),string=p=>{if(!p)return null;let end=p;while(heap[end])end++;return Buffer.from(heap.slice(p,end)).toString('latin1');};
 const saved=metadata.instance_globals_s.fields.saved_plines.offset,index=view.getUint32(gs+metadata.instance_globals_s.fields.saved_pline_index.offset,true);
 const win=pointer(heap,wins+winMessage*8),fields=metadata.WinDesc.fields,rows=Number(view.getBigInt64(win+fields.rows.offset,true));assert.ok(Number.isSafeInteger(rows)&&rows>=0,'Measured history row count');
 const data=pointer(heap,win+fields.data.offset),datlen=pointer(heap,win+fields.datlen.offset);
 return {index,saved:Array.from({length:layouts.pline.DUMPLOG_MSG_COUNT},(_,i)=>string(pointer(heap,gs+saved+i*8))),topline:string(gt+metadata.instance_globals_t.fields.toplines.offset),flags:view.getInt32(win+fields.flags.offset,true),maxcol:view.getBigInt64(win+fields.maxcol.offset,true),maxrow:view.getBigInt64(win+fields.maxrow.offset,true),rows,entries:Array.from({length:rows},(_,i)=>({text:string(pointer(heap,data+i*8)),capacity:datlen?view.getInt16(datlen+i*2,true):null}))};
}
const winMessage=env.memory.view.getInt32(env.requireGlobal('WIN_MESSAGE'),true),cWinMessage=new DataView(ref.HEAPU8.buffer).getInt32(cglobal('WIN_MESSAGE'),true);
assert.deepEqual(messageState(env.memory.HEAPU8,env.requireGlobal('gs'),env.requireGlobal('gt'),env.requireGlobal('wins'),winMessage),messageState(ref.HEAPU8,cglobal('gs'),cglobal('gt'),ttyGlobal('wins'),cWinMessage),'Source legacy synopsis, tty history ring and PLINE saved-message ring');checks++;


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
const actual=Buffer.from(stdio.captured(1)),expected=Buffer.from(coutput);fs.writeFileSync('.cache/pager-startup-'+seed+'-'+role+'-'+roleplay+'-js.stdout',actual);fs.writeFileSync('.cache/pager-startup-'+seed+'-'+role+'-'+roleplay+'-c.stdout',expected);
assert.deepEqual(actual,expected,'actual original-C legacy pager and first-display terminal bytes');checks++;
assert.ok(!actual.includes(0),'First-display acceptance requires initialized symbols; matching NUL map output is incomplete bootstrap');assert.ok(actual.includes(64),'Default first display must contain the visible hero glyph');
assert.deepEqual(Buffer.from(env.filesystem.readFile('/rng.log')),Buffer.from(ref.FS.readFile('/rng.log')),'actual full startup prefix RNG sequence');checks++;
function pointerAlias(p,isJS){if(!p)return null;const row=visionRows.find(r=>r.c&&p>=(isJS?r.j:r.c)&&p<(isJS?r.j:r.c)+r.bytes);assert.ok(row,'Known vision buffer address');return {storage:row.name,offset:p-(isJS?row.j:row.c)};}
function visionImage(row,heap,isJS){const p=isJS?row.j:row.c,bytes=Buffer.from(heap.slice(p,p+row.bytes)),refs=[];let d=row.d,n=1;if(d.a){n=d.a.reduce((n,k)=>n*k,1);d=d.e;}if(d.q||d.p!==undefined||d.f)for(let i=0;i<n;i++){const ptr=Number(bytes.readBigUInt64LE(8*i));if(d.f){assert.equal(ptr,0,'No active traversal callback');refs.push(null);}else refs.push(pointerAlias(ptr,isJS));bytes.fill(0,8*i,8*i+8);}return {bytes,refs};}
for(const row of visionRows)if(row.c){assert.deepEqual(visionImage(row,env.memory.HEAPU8,true),visionImage(row,ref.HEAPU8,false),'source vision storage '+row.name);checks++;}
for(const key of ['viz_array','viz_rmin','viz_rmax']){const off=metadata.instance_globals_v.fields[key].offset,j=Number(env.memory.view.getBigUint64(gv+off,true)),c=Number(new DataView(ref.HEAPU8.buffer).getBigUint64(cgv+off,true));assert.deepEqual(pointerAlias(j,true),pointerAlias(c,false),'source live vision root '+key);checks++;}
const locations=metadata.instance_globals_saved_l.fields.level.offset+metadata.dlevel_t.fields.locations.offset,count=80*21*metadata.rm.size;
assert.deepEqual(env.memory.readBytes(svl+locations,count),ref.HEAPU8.slice(csvl+locations,csvl+locations+count),'source complete terrain/seen/glyph matrix');checks++;
assert.deepEqual(env.memory.readBytes(env.requireGlobal('seenv_matrix'),9),ref.HEAPU8.slice(Number(ref._probe_first_display_matrix()),Number(ref._probe_first_display_matrix())+9),'source shared directional seen matrix');checks++;
totalChecks+=checks;console.log('Compared pager startup for seed '+seed+' role '+role+' roleplay '+roleplay+' ('+actual.length+' bytes, '+jkeys.length+' keys)');
}
console.log(`PASS: ${totalChecks} connected pager/input/equipment/terminal/startup comparisons over${inputs.length} explicit startup cases; later startup and full-game recordings remain unfinished.`);
