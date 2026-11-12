import {layoutSourceSha} from './nethack-layout.mjs';
import assert from 'node:assert/strict';
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {createNativeTerminal} from '../js/platform/darwin/terminal.js';
import {createTerminalDevices} from '../js/nethack/unix-terminal.js';
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
const directory=path.resolve(process.env.STANDALONE_VISION_DISPLAY_ORACLE||'.cache/standalone-vision-display-v4');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json'))),sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const [p,h]of Object.entries(receipt.sourceSha256))assert.equal(layoutSourceSha(p,h),h,'Changed reference input '+p);
for(const [p,h]of Object.entries(receipt.artifactSha256))assert.equal(sha(path.join(directory,p)),h,'Changed reference artifact '+p);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs')));
let totalChecks=0;
const seeds=process.env.STANDALONE_VISION_SEED?[BigInt(process.env.STANDALONE_VISION_SEED)]:[1n,0x12345678n,0xffffffffffffffffn],roles=process.env.STANDALONE_VISION_ROLE?[Number(process.env.STANDALONE_VISION_ROLE)]:Array.from({length:13},(_,i)=>i);
for(const seed of seeds)for(const role of roles){
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
 const stdio=env.enableStdio();env.enableDecl(layouts.decl);env.call('decl','program_state_init');env.call('decl','decl_globals_init');env.enableDrawing(layouts.drawing);env.enableObjects(layouts.objects);env.call('objects','objects_globals_init');env.enableMonst(layouts.monst);env.call('monst','monst_globals_init');env.enableSerialization(layouts);env.enableRnd(layouts.rnd,{seed});env.call('rnd','rng_log_init');env.enableAddressPort('dungeon',{only:['ledger_no','maxledgerno']});env.enableObjectState(layouts);env.enableObjectRecords(layouts);env.enableItemInventory(layouts);env.enableTimers(layouts);env.enableItemNaming(layouts);const group=env.enableMonsterSelection(layouts);const decl=JSON.parse(fs.readFileSync('js/nethack/decl-storage.json')).globals,before=decl.map(r=>env.memory.readBytes(env.requireGlobal(r.name),r.bytes));const creation=env.enableMonsterCreation(layouts);decl.forEach((r,i)=>assert.deepEqual(env.memory.readBytes(env.requireGlobal(r.name),r.bytes),before[i],'enabling creation preserves '+r.name));

 const startup=env.enableGameStartup(layouts);env.call('sys','sys_early_init');
env.enableHeroStartup(layouts);env.enableWorldPosition(layouts);env.enableLuaSandbox(layouts);env.enableDisplayStartup(layouts);
for(const name of fs.readdirSync('/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/wasm64-build/tree/dat').filter(n=>n.endsWith('.lua')))env.filesystem.writeFile(name,fs.readFileSync('/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/wasm64-build/tree/dat/'+name));
for(const name of ['epitaph','engrave','rumors','bogusmon','oracles'])env.filesystem.writeFile(name,fs.readFileSync('/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/wasm64-build/tree/dat/'+name));
env.filesystem.writeFile('sysconf',fs.readFileSync(process.env.STANDALONE_REFERENCE_ROOT+'/.cache/wasm64-build/assets/sysconf'));
Object.assign(env.services.flags,{initrole:role,initrace:0,initgend:0,initalign:0,female:0,pantheon:-1});env.services.strcpy(startup.role.svp.plname,env.services.literal('Ada'));
env.enableLevelStartup(layouts);const contents=env.enableLevelContents(layouts);env.services.vision_init();const window=env.enableWindowSystem(layouts);env.enableVersionInfo(layouts);env.enableOptions(layouts);env.enableSymbols(layouts);env.enableGlyphs(layouts);env.enableCommands(layouts);env.enableConfiguration(layouts);env.enableFiles(layouts);env.enableStatus(layouts);env.enableGameWindows(layouts);env.enableMovement(layouts);env.enablePets(layouts);env.enableMonsterMovement(layouts);env.enableMonsterLifecycle(layouts);env.services.choose_windows('tty');env.services.initoptions();Object.assign(env.services.flags,{initrole:role,initrace:0,initgend:0,initalign:0,female:0,pantheon:-1});
const argc=env.memory.calloc(1,4),argv=env.memory.calloc(2,8);env.memory.view.setInt32(argc,1,true);env.memory.view.setBigUint64(argv,BigInt(env.services.literal('nethack')),true);env.services.tty_init_nhwindows(argc,argv);env.services.init_sound_disp_gamewindows();assert.throws(()=>env.services.newgame(),/Unresolved standalone function u_init_skills_discoveries/);env.services.fflush(stdio.stdout);assert.equal(forbiddenCalls,0,'Pure JS startup invokes no Wasm/network capability');checks++;for(const [name,descriptor]of capabilities){if(descriptor)Object.defineProperty(globalThis,name,descriptor);else delete globalThis[name];}

ref._probe_level_init(seed);const assets=process.env.STANDALONE_REFERENCE_ROOT+'/.cache/wasm64-build/tree/dat/';for(const name of fs.readdirSync(assets).filter(n=>n.endsWith('.lua')).concat(['epitaph','engrave','rumors','bogusmon','oracles']))ref.FS.writeFile(name,fs.readFileSync(assets+name));
for(const [key,value]of Object.entries({NETHACK_FIXED_DATETIME:'20260102030405',NETHACK_RNGLOG:'/rng.log',NETHACK_SEED:seed.toString()})){const p=ref._malloc(BigInt(key.length+value.length+2));ref.HEAPU8.set(Buffer.from(key+'\0'+value+'\0'),Number(p));ref._setenv(BigInt(p),BigInt(Number(p)+key.length+1),1);ref._free(BigInt(p));}
ref.FS.writeFile('sysconf',fs.readFileSync(process.env.STANDALONE_REFERENCE_ROOT+'/.cache/wasm64-build/assets/sysconf'));
const player=ref._malloc(4n);ref.HEAPU8.set(Buffer.from('Ada\0'),Number(player));ref._probe_startup_role_config(role,0,0,0,BigInt(player));ref._free(player);ref._vision_init();const type=ref._malloc(4n);ref.HEAPU8.set(Buffer.from('tty\0'),Number(type));ref._probe_window_select(BigInt(type));ref._free(type);ref._initoptions();const chosen=ref._malloc(4n);ref.HEAPU8.set(Buffer.from('Ada\0'),Number(chosen));ref._probe_startup_role_config(role,0,0,0,BigInt(chosen));ref._free(chosen);ref._probe_window_init();ref._init_sound_disp_gamewindows();
const metadata=JSON.parse(fs.readFileSync('js/nethack/records.json')).records;
const visionRows=contents.vision.rows.map((row,i)=>({...row,bytes:Number(ref._probe_vision_storage_size(i)),j:contents.vision.storage[i],c:Number(ref._probe_vision_storage(i))}));
const gv=env.requireGlobal('gv'),cgv=Number(ref._probe_decl_global(decl.findIndex(r=>r.name==='gv'))),svl=env.requireGlobal('svl'),csvl=Number(ref._probe_hero_global(9));
assert.throws(()=>ref._probe_startup_newgame(),/abort|unreachable/i);assert.ok(errors.some(s=>s.includes('Observed C boundary: u_init_skills_discoveries')),errors.join('\n'));
const actual=Buffer.from(stdio.captured(1)),expected=Buffer.from(coutput);fs.writeFileSync('.cache/vision-display-'+seed+'-'+role+'-js.stdout',actual);fs.writeFileSync('.cache/vision-display-'+seed+'-'+role+'-c.stdout',expected);
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
totalChecks+=checks;console.log('Compared first display for seed '+seed+' role '+role+' ('+actual.length+' bytes)');
}
console.log(`PASS: ${totalChecks} connected first-display/terminal/startup comparisons over${seeds.length*roles.length} role/seed cases; skills and full-game recordings remain unfinished.`);
