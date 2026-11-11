import assert from 'node:assert/strict';
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/standalone/environment.js';
import {createNativeTerminal} from '../js/services/native-terminal.js';
import {createTerminalDevices} from '../js/standalone/unix-terminal.js';
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
const directory=path.resolve(process.env.STANDALONE_ATTRIBUTE_STARTUP_ORACLE||'.cache/standalone-attribute-state-v1');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json'))),sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const [p,h]of Object.entries(receipt.sourceSha256))assert.equal(sha(p),h,'Changed reference input '+p);
for(const [p,h]of Object.entries(receipt.artifactSha256))assert.equal(sha(path.join(directory,p)),h,'Changed reference artifact '+p);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs')));
let totalChecks=0;
const seeds=process.env.STANDALONE_ATTRIBUTE_SEED?[BigInt(process.env.STANDALONE_ATTRIBUTE_SEED)]:[1n],roles=process.env.STANDALONE_ATTRIBUTE_ROLE?[Number(process.env.STANDALONE_ATTRIBUTE_ROLE)]:Array.from({length:13},(_,i)=>i);
const selectedMasks=process.env.STANDALONE_ATTRIBUTE_ROLEPLAY?[Number(process.env.STANDALONE_ATTRIBUTE_ROLEPLAY)]:[0],inputs=seeds.flatMap(seed=>roles.flatMap(role=>selectedMasks.map(roleplay=>({seed,role,roleplay}))));
if(process.env.STANDALONE_ATTRIBUTE_TARGETED)inputs.length=0;
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
for(const name of fs.readdirSync('/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/wasm64-build/tree/dat').filter(n=>n.endsWith('.lua')))env.filesystem.writeFile(name,fs.readFileSync('/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/wasm64-build/tree/dat/'+name));
for(const name of ['epitaph','engrave','rumors','bogusmon','oracles'])env.filesystem.writeFile(name,fs.readFileSync('/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/wasm64-build/tree/dat/'+name));
env.filesystem.writeFile('sysconf',fs.readFileSync(process.env.STANDALONE_REFERENCE_ROOT+'/.cache/wasm64-build/assets/sysconf'));
Object.assign(env.services.flags,{initrole:role,initrace:0,initgend:0,initalign:0,female:0,pantheon:-1});env.services.strcpy(startup.role.svp.plname,env.services.literal('Ada'));
env.enableLevelStartup(layouts);const contents=env.enableLevelContents(layouts);env.services.vision_init();const window=env.enableWindowSystem(layouts);env.enableVersionInfo(layouts);env.enableOptions(layouts);env.enableSymbols(layouts);env.enableGlyphs(layouts);env.enableCommands(layouts);env.enableConfiguration(layouts);env.enableFiles(layouts);env.enableStatus(layouts);env.enableGameWindows(layouts);env.enableMovement(layouts);env.enablePets(layouts);env.enableMonsterMovement(layouts);env.enableMonsterLifecycle(layouts);env.enableHeroEquipment(layouts);env.services.choose_windows('tty');env.services.initoptions();Object.assign(env.services.flags,{initrole:role,initrace:0,initgend:0,initalign:0,female:0,pantheon:-1});
for(const [i,name]of ['blind','nudist','deaf','pauper','reroll','reserved1','reserved2','reserved3'].entries())env.services.u.uroleplay[name]=(roleplay>>i)&1;
const argc=env.memory.calloc(1,4),argv=env.memory.calloc(2,8);env.memory.view.setInt32(argc,1,true);env.memory.view.setBigUint64(argv,BigInt(env.services.literal('nethack')),true);env.services.tty_init_nhwindows(argc,argv);env.services.init_sound_disp_gamewindows();assert.throws(()=>env.services.newgame(),/Unresolved standalone function com_pager/);env.services.fflush(stdio.stdout);assert.equal(forbiddenCalls,0,'Pure JS startup invokes no Wasm/network capability');checks++;for(const [name,descriptor]of capabilities){if(descriptor)Object.defineProperty(globalThis,name,descriptor);else delete globalThis[name];}

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
const actual=Buffer.from(stdio.captured(1)),expected=Buffer.from(coutput);fs.writeFileSync('.cache/attribute-state-'+seed+'-'+role+'-'+roleplay+'-js.stdout',actual);fs.writeFileSync('.cache/attribute-state-'+seed+'-'+role+'-'+roleplay+'-c.stdout',expected);
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

// Calls execute on the same already-connected ATTRIB owner/context/tables.
const attributeOwner=env.start('hero-attributes').environment;
const ju=env.requireGlobal('u'),cu=Number(ref._probe_hero_global(3)),jdisp=env.requireGlobal('disp'),cdisp=cglobal('disp');
function compareAttributeState(label){for(const [name,type,j,c]of [['u','you',ju,cu],['disp','display_hints',jdisp,cdisp]]){assert.deepEqual(snapshot(env.memory.HEAPU8,j,type),snapshot(ref.HEAPU8,c,type),'source ATTRIB '+label+' '+name);checks++;}}
let attributeScenario='initial wear';
function attributeAction(name,args=[],cargs=args){const actual=env.services[name](...args),expected=ref['_'+name](...cargs);assert.equal(typeof actual==='boolean'?Number(actual):actual,expected,'original ATTRIB result '+name+' '+attributeScenario);checks++;compareAttributeState(name);return actual;}
attributeAction('set_wear',[0],[0n]);
if(role===0)assert.equal(env.services.u.uluck,1,'Real initial Fedora activation invokes original change_luck');
const jHero=env.memory.readBytes(ju,metadata.you.size),cHero=ref.HEAPU8.slice(cu,cu+metadata.you.size),jHints=env.memory.readBytes(jdisp,metadata.display_hints.size),cHints=ref.HEAPU8.slice(cdisp,cdisp+metadata.display_hints.size);
function restoreAttributeInputs(){env.memory.HEAPU8.set(jHero,ju);ref.HEAPU8.set(cHero,cu);env.memory.HEAPU8.set(jHints,jdisp);ref.HEAPU8.set(cHints,cdisp);}
const cview=()=>new DataView(ref.HEAPU8.buffer);
function inputField(name,value){const f=metadata.you.fields[name],type=f.ctype.replace(new RegExp('\\s+'+name+'$'),'');env.ctypes.store(type,ju+f.offset,value);const kind=/^(?:schar|boolean|char) /.test(f.ctype)?'Int8':/^(?:xint16|short) /.test(f.ctype)?'Int16':'Int32';cview()['set'+kind](cu+f.offset,Number(value),true);}
for(const luck of [-128,-11,-10,-1,0,1,10,11,127])for(const change of [-2147483648,-257,-129,-128,-11,-1,0,1,11,127,128,129,255,256,257,2147483647]){restoreAttributeInputs();inputField('uluck',luck);attributeAction('change_luck',[change],[env.transport.char(change)]);}
restoreAttributeInputs();
const jHead=pointer(env.memory.HEAPU8,env.requireGlobal('gi')+inventoryOffset),cHead=pointer(ref.HEAPU8,cglobal('gi')+inventoryOffset),jobj=[env.memory.calloc(1,metadata.obj.size),env.memory.calloc(1,metadata.obj.size)],cobj=[Number(ref._malloc(BigInt(metadata.obj.size))),Number(ref._malloc(BigInt(metadata.obj.size)))];
function inputObject(index,type,quantity,bits,next=0){const at=jobj[index];env.memory.memset(at,0,metadata.obj.size);for(const [name,value]of Object.entries({otyp:type,oclass:creation.environment.objects[type].oc_class,quan:quantity,where:layouts.weapon.OBJ_INVENT,nobj:next?jobj[next]:0,cursed:bits&1?1:0,blessed:bits&2?1:0,dknown:bits&4?1:0})){const f=metadata.obj.fields[name],scalar=f.ctype.replace(new RegExp('\\s+'+name+'$'),'');env.ctypes.setField('struct obj',at,name,scalar,value);}ref._probe_attribute_object(BigInt(cobj[index]),type,quantity,bits,next?BigInt(cobj[next]):0n);const jb=Buffer.from(env.memory.readBytes(at,metadata.obj.size)),cb=Buffer.from(ref.HEAPU8.slice(cobj[index],cobj[index]+metadata.obj.size));jb.fill(0,metadata.obj.fields.nobj.offset,metadata.obj.fields.nobj.offset+8);cb.fill(0,metadata.obj.fields.nobj.offset,metadata.obj.fields.nobj.offset+8);assert.deepEqual(jb,cb,'Independent original-C object inputs');checks++;}
const luckCases=[[],[[layouts.mkobj.LUCKSTONE,1n,0]],[[layouts.mkobj.LUCKSTONE,1n,1]],[[layouts.mkobj.LUCKSTONE,1n,2]],[[layouts.mkobj.LUCKSTONE,4294967295n,2]],[[layouts.mkobj.LUCKSTONE,4294967296n,0]],[[layouts.mkobj.LUCKSTONE,4294967297n,0]],[[layouts.mkobj.LUCKSTONE,2n,2],[layouts.mkobj.LUCKSTONE,1n,1]],[[layouts.u_init.TOUCHSTONE,7n,0]]];
for(const items of luckCases){attributeScenario=items.map(row=>row.map(String).join(':')).join(',');restoreAttributeInputs();for(let i=items.length-1;i>=0;i--)inputObject(i,...items[i],i+1<items.length?i+1:0);const j=items.length?jobj[0]:0,c=items.length?cobj[0]:0;env.memory.view.setBigUint64(env.requireGlobal('gi')+inventoryOffset,BigInt(j),true);ref._probe_attribute_inventory(BigInt(c));for(const include of [0,1,256,257]){attributeScenario+=' include='+include;attributeAction('stone_luck',[include],[env.transport.char(include)]);}attributeAction('set_moreluck');}
env.memory.view.setBigUint64(env.requireGlobal('gi')+inventoryOffset,BigInt(jHead),true);ref._probe_attribute_inventory(BigInt(cHead));
for(const cursed of [0,1])for(const increment of [0,1,4]){restoreAttributeInputs();inputObject(0,layouts.mkobj.LUCKSTONE,1n,cursed);attributeAction('gainstr',[jobj[0],increment,0],[BigInt(cobj[0]),increment,0]);}
for(const polymorphed of [0,1])for(const even of [0,1])for(const newmax of [1,7,20,100]){restoreAttributeInputs();inputField('umonnum',polymorphed?layouts.monst.PM_KITTEN:env.services.u.umonster);inputField('uhp',30);inputField('uhpmax',30);inputField('mh',40);inputField('mhmax',40);attributeAction('setuhpmax',[newmax,even]);for(const loss of [1,5,50])attributeAction('adjuhploss',[loss,polymorphed?40:30]);}
for(const altmin of [-10,0,1,10,99])attributeAction('minuhpmax',[altmin]);
for(let stat=0;stat<layouts.attrib.A_MAX;stat++){attributeAction('extremeattr',[stat]);for(const increment of [0,1,256,257]){restoreAttributeInputs();attributeAction('exercise',[stat,increment],[stat,env.transport.char(increment)]);}}
for(const old of [-100,0,10,100])for(const delta of [0,1,7,200]){restoreAttributeInputs();env.services.u.ualign.record=old;cview().setInt32(cu+metadata.you.fields.ualign.offset+metadata.align.fields.record.offset,old,true);attributeAction('adjalign',[delta]);}
restoreAttributeInputs();attributeAction('redist_attr');
for(const name of ['FIRE_RES','FAST','BLINDED','BLND_RES','JUMPING','DRAIN_RES']){restoreAttributeInputs();attributeAction('is_innate',[layouts.attrib[name]]);const jp=env.services.from_what(layouts.attrib[name]),cp=Number(ref._from_what(layouts.attrib[name]));assert.equal(env.memory.readString(jp),(()=>{let end=cp;while(ref.HEAPU8[end])end++;return Buffer.from(ref.HEAPU8.slice(cp,end)).toString('latin1');})(),'Original stable property-provenance buffer');checks++;}
restoreAttributeInputs();for(const p of jobj)env.memory.free(p);for(const p of cobj)ref._free(BigInt(p));assert.equal(env.start('hero-attributes').environment,attributeOwner,'All public entries retain the single attribute context');checks++;
assert.deepEqual(Buffer.from(env.filesystem.readFile('/rng.log')),Buffer.from(ref.FS.readFile('/rng.log')),'Complete source ATTRIB call/RNG sequence');checks++;

totalChecks+=checks;console.log('Compared attribute state for seed '+seed+' role '+role+' roleplay '+roleplay+' ('+actual.length+' bytes)');
}
console.log(`PASS: ${totalChecks} connected attribute/initial-wear/terminal/startup comparisons over${inputs.length} explicit startup cases; later startup and full-game recordings remain unfinished.`);
