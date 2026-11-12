import {layoutSourceSha} from './nethack-layout.mjs';
import assert from 'node:assert/strict';
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {createNativeTerminal} from '../js/platform/darwin/terminal.js';
import {createTerminalDevices} from '../js/nethack/unix-terminal.js';
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),seed=1n;
const directory=path.resolve(process.env.STANDALONE_PET_STARTUP_ORACLE||'.cache/standalone-pet-startup-v1');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json'))),sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const [p,h]of Object.entries(receipt.sourceSha256))assert.equal(layoutSourceSha(p,h),h,'Changed reference input '+p);
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
 env.enableStdio();env.enableDecl(layouts.decl);env.call('decl','program_state_init');env.call('decl','decl_globals_init');env.enableDrawing(layouts.drawing);env.enableObjects(layouts.objects);env.call('objects','objects_globals_init');env.enableMonst(layouts.monst);env.call('monst','monst_globals_init');env.enableSerialization(layouts);env.enableRnd(layouts.rnd,{seed});env.call('rnd','rng_log_init');env.enableAddressPort('dungeon',{only:['ledger_no','maxledgerno']});env.enableObjectState(layouts);env.enableObjectRecords(layouts);env.enableItemInventory(layouts);env.enableTimers(layouts);env.enableItemNaming(layouts);const group=env.enableMonsterSelection(layouts);const decl=JSON.parse(fs.readFileSync('js/nethack/decl-storage.json')).globals,before=decl.map(r=>env.memory.readBytes(env.requireGlobal(r.name),r.bytes));const creation=env.enableMonsterCreation(layouts);decl.forEach((r,i)=>assert.deepEqual(env.memory.readBytes(env.requireGlobal(r.name),r.bytes),before[i],'enabling creation preserves '+r.name));

 env.enableGameStartup(layouts);env.call('sys','sys_early_init');
env.enableHeroStartup(layouts);env.enableWorldPosition(layouts);env.enableLuaSandbox(layouts);env.enableDisplayStartup(layouts);

ref._probe_level_init(seed);
env.enableMovement(layouts);env.enableMonsterInventory(layouts);env.enablePets(layouts);env.enableMonsterMovement(layouts);env.enableMonsterLifecycle(layouts);
const metadata=JSON.parse(fs.readFileSync('js/nethack/records.json')).records;
const cview=()=>new DataView(ref.HEAPU8.buffer),nativeGlobal=name=>Number(ref._probe_decl_global(decl.findIndex(r=>r.name===name)));
const mons=env.requireGlobal('mons'),cmons=Number(ref._probe_startup_global(6)),pm=layouts.dog.PM_LITTLE_DOG,monsterSize=metadata.monst.size;
const jm=env.memory.calloc(1,monsterSize),cm=Number(ref._malloc(BigInt(monsterSize)));ref.HEAPU8.fill(0,cm,cm+monsterSize);
function scalar(type,j,c,path,value){const f=env.ctypes.locate(type,j,path);const name=path.split('.').at(-1),t=f.field.ctype.replace(new RegExp(' '+name+'$'),'');env.ctypes.setField(type,j,path,t,value);const n=env.ctypes.size(t);ref.HEAPU8.set(env.memory.readBytes(f.at,n),c+f.at-j);}
// Source monster pointers differ while both point to the same original species.
env.ctypes.setField('struct monst',jm,'data','struct permonst *',mons+pm*metadata.permonst.size);cview().setBigUint64(cm+metadata.monst.fields.data.offset,BigInt(cmons+pm*metadata.permonst.size),true);
for(const [key,value]of Object.entries({mnum:pm,m_id:123,mx:10,my:10}))scalar('struct monst',jm,cm,key,value);
const ju=env.requireGlobal('u'),cu=Number(ref._probe_hero_global(3)),gy=env.requireGlobal('gy'),cgy=Number(ref._probe_hero_global(4));
const yp=env.ctypes.locate('struct instance_globals_y',gy,'youmonst').at,cyp=cgy+yp-gy;
env.ctypes.setField('struct monst',yp,'data','struct permonst *',mons+pm*metadata.permonst.size);cview().setBigUint64(cyp+metadata.monst.fields.data.offset,BigInt(cmons+pm*metadata.permonst.size),true);
for(const [key,value]of Object.entries({ux:11,uy:10}))scalar('struct you',ju,cu,key,value);
for(const value of [-10,0,3,10,18,25,40]){const off=metadata.you.fields.acurr.offset+metadata.attribs.fields.a.offset+5;env.memory.view.setInt8(ju+off,value);cview().setInt8(cu+off,value);assert.equal(env.services.acurr(5),ref._acurr(5),'source charisma clamp '+value);checks++;}
for(const photo of [0,1,1,0]){env.services.see_monster_closeup(jm,photo);ref._see_monster_closeup(BigInt(cm),photo);for(const [name,type,path]of [['svc','struct instance_globals_saved_c','context.lifelist'],['svm','struct instance_globals_saved_m','mvitals']]){const j=env.requireGlobal(name),c=nativeGlobal(name),f={at:j+(path==='mvitals'?metadata.instance_globals_saved_m.fields.mvitals.offset:metadata.instance_globals_saved_c.fields.context.offset+metadata.context_info.fields.lifelist.offset)},n=path==='mvitals'?metadata.mvitals.size*layouts.mon.NUMMONS:metadata.lifelists.size;assert.deepEqual(env.memory.readBytes(f.at,n),ref.HEAPU8.slice(c+f.at-j,c+f.at-j+n),'source close-up '+path);checks++;}}
env.services.set_apparxy(jm);ref._set_apparxy(BigInt(cm));for(const key of ['mux','muy']){const f=metadata.monst.fields[key];assert.deepEqual(env.memory.readBytes(jm+f.offset,2),ref.HEAPU8.slice(cm+f.offset,cm+f.offset+2),'source pet hero location '+key);checks++;}
const jx=env.memory.calloc(1,metadata.mextra.size),cx=Number(ref._malloc(BigInt(metadata.mextra.size))),jd=env.memory.calloc(1,metadata.edog.size),cd=Number(ref._malloc(BigInt(metadata.edog.size)));
ref.HEAPU8.fill(0,cx,cx+metadata.mextra.size);ref.HEAPU8.fill(0,cd,cd+metadata.edog.size);
for(const [type,j,c,key,jp,cp]of [['struct monst',jm,cm,'mextra',jx,cx],['struct mextra',jx,cx,'edog',jd,cd]]){const f=env.ctypes.record(type).fields[key];env.memory.view.setBigUint64(j+f.offset,BigInt(jp),true);cview().setBigUint64(c+f.offset,BigInt(cp),true);}
for(const [everything,tame,hungry,moves]of [[1,0,0n,1n],[0,2,2000n,10n],[0,20,0n,300n],[1,1,0n,1000n]]){
 scalar('struct monst',jm,cm,'mtame',tame);scalar('struct edog',jd,cd,'hungrytime',hungry);scalar('struct instance_globals_saved_m',env.requireGlobal('svm'),nativeGlobal('svm'),'moves',moves);
 env.services.initedog(jm,everything);ref._initedog(BigInt(cm),everything);
 assert.deepEqual(env.memory.readBytes(jd,metadata.edog.size),ref.HEAPU8.slice(cd,cd+metadata.edog.size),'source complete companion initialization');checks++;
 const jb=env.memory.readBytes(jm,monsterSize),cb=ref.HEAPU8.slice(cm,cm+monsterSize);for(const name of ['data','mextra']){const off=metadata.monst.fields[name].offset;jb.fill(0,off,off+8);cb.fill(0,off,off+8);}assert.deepEqual(jb,cb,'source pet flags/tameness/alignment');checks++;
}
// Exercise actual source allocation/placement on a defined empty room.
const jgu=env.requireGlobal('gu'),cgu=nativeGlobal('gu'),uroleOff=metadata.instance_globals_u.fields.urole.offset;
scalar('struct Role',jgu+uroleOff,cgu+uroleOff,'petnum',pm);
const jsvl=env.requireGlobal('svl'),csvl=Number(ref._probe_hero_global(9)),locations=metadata.instance_globals_saved_l.fields.level.offset+metadata.dlevel_t.fields.locations.offset;
for(let x=1;x<79;x++)for(let y=0;y<21;y++){const off=locations+(x*21+y)*metadata.rm.size;scalar('struct rm',jsvl+off,csvl+off,'typ',layouts.hack.ROOM);}
function createPet(label){
const jpet=Number(env.services.makedog()),cpet=Number(ref._makedog());assert.ok(jpet&&cpet,'source creates pet on matching room');checks++;
for(const key of ['mx','my','mnum','mtame','malign','m_id','mux','muy','mhp','mhpmax']){const f=metadata.monst.fields[key],t=f.ctype.replace(new RegExp(' '+key+'$'),''),n=env.ctypes.size(t);assert.deepEqual(env.memory.readBytes(jpet+f.offset,n),ref.HEAPU8.slice(cpet+f.offset,cpet+f.offset+n),'actual source pet '+key);checks++;}
const pointer=(heap,p)=>Number(new DataView(heap.buffer,heap.byteOffset,heap.byteLength).getBigUint64(p,true)),jxpet=pointer(env.memory.HEAPU8,jpet+metadata.monst.fields.mextra.offset),cxpet=pointer(ref.HEAPU8,cpet+metadata.monst.fields.mextra.offset),jdpet=pointer(env.memory.HEAPU8,jxpet+metadata.mextra.fields.edog.offset),cdpet=pointer(ref.HEAPU8,cxpet+metadata.mextra.fields.edog.offset);
assert.deepEqual(env.memory.readBytes(jdpet,metadata.edog.size),ref.HEAPU8.slice(cdpet,cdpet+metadata.edog.size),'actual source complete pet companion');checks++;
const jname=pointer(env.memory.HEAPU8,jxpet+metadata.mextra.fields.mgivenname.offset),cname=pointer(ref.HEAPU8,cxpet+metadata.mextra.fields.mgivenname.offset);const string=(heap,p)=>{if(!p)return null;let end=p;while(heap[end])end++;return Buffer.from(heap.slice(p,end)).toString('latin1');};assert.equal(string(env.memory.HEAPU8,jname),string(ref.HEAPU8,cname),label+' source allocated pet name');checks++;

assert.deepEqual(Buffer.from(env.filesystem.readFile('/rng.log')),Buffer.from(ref.FS.readFile('/rng.log')),'actual pet RNG call sequence');checks++;
const ji=pointer(env.memory.HEAPU8,jpet+metadata.monst.fields.minvent.offset),ci=pointer(ref.HEAPU8,cpet+metadata.monst.fields.minvent.offset);assert.equal(Boolean(ji),Boolean(ci),label+' source inventory presence');checks++;
if(ji){const jb=env.memory.readBytes(ji,metadata.obj.size),cb=ref.HEAPU8.slice(ci,ci+metadata.obj.size);for(const f of Object.values(metadata.obj.fields))if(f.ctype.includes('*')||f.record==='vptrs'){jb.fill(0,f.offset,f.offset+8);cb.fill(0,f.offset,f.offset+8);}assert.deepEqual(jb,cb,label+' complete saddle nonpointer image');checks++;
 const off=metadata.monst.fields.misc_worn_check.offset;assert.deepEqual(env.memory.readBytes(jpet+off,8),ref.HEAPU8.slice(cpet+off,cpet+off+8),label+' saddle worn mask');checks++;
 const disco=metadata.instance_globals_saved_d.fields.disco;assert.deepEqual(env.memory.readBytes(env.requireGlobal('svd')+disco.offset,2*layouts.o_init.NUM_OBJECTS),ref.HEAPU8.slice(nativeGlobal('svd')+disco.offset,nativeGlobal('svd')+disco.offset+2*layouts.o_init.NUM_OBJECTS),label+' source discovered items');checks++;
}

}
createPet('default dog');
function nested(type,j,c,path,value){const keys=path.split('.');for(const key of keys.slice(0,-1)){const f=env.ctypes.record(type).fields[key];j+=f.offset;c+=f.offset;type=f.record??f.ctype.replace(new RegExp(' '+key+'$'),'');}scalar(type,j,c,keys.at(-1),value);}
function petName(global,key,value){const type='struct instance_globals_'+global.slice(-1),j=env.requireGlobal(global),c=nativeGlobal(global),f=env.ctypes.record(type).fields[key];const bytes=Buffer.from(value+'\0');env.memory.HEAPU8.fill(0,j+f.offset,j+f.offset+32);ref.HEAPU8.fill(0,c+f.offset,c+f.offset+32);env.memory.HEAPU8.set(bytes,j+f.offset);ref.HEAPU8.set(bytes,c+f.offset);}
for(const [kind,role,name]of [[layouts.dog.PM_LITTLE_DOG,layouts.dog.PM_BARBARIAN,''],[layouts.dog.PM_LITTLE_DOG,0,'Fido'],[layouts.dog.PM_KITTEN,0,'Mittens'],[layouts.dog.PM_PONY,0,'Shadowfax'],[layouts.dog.NON_PM,0,'']]){
 nested('struct instance_globals_saved_c',env.requireGlobal('svc'),nativeGlobal('svc'),'context.startingpet_mid',0);
 scalar('struct Role',jgu+uroleOff,cgu+uroleOff,'petnum',kind);scalar('struct Role',jgu+uroleOff,cgu+uroleOff,'mnum',role);
 petName('gd','dogname',name);petName('gc','catname',name);createPet('source species/name '+kind+':'+name);
}
nested('struct you',ju,cu,'uroleplay.pauper',1);nested('struct instance_globals_saved_c',env.requireGlobal('svc'),nativeGlobal('svc'),'context.startingpet_mid',0);scalar('struct Role',jgu+uroleOff,cgu+uroleOff,'petnum',layouts.dog.PM_PONY);createPet('pauper pony without saddle');
scalar('struct instance_globals_p',env.requireGlobal('gp'),nativeGlobal('gp'),'preferred_pet','n'.charCodeAt(0));assert.equal(Number(env.services.makedog()),Number(ref._makedog()),'source no-pet preference');checks++;
const context=metadata.instance_globals_saved_c.fields.context.offset,petType=metadata.context_info.fields.startingpet_typ.offset;assert.deepEqual(env.memory.readBytes(env.requireGlobal('svc')+context+petType,4),ref.HEAPU8.slice(nativeGlobal('svc')+context+petType,nativeGlobal('svc')+context+petType+4),'source no-pet type');checks++;
console.log(`PASS: ${checks} original-C shared pet visibility, charisma and apparent hero location comparisons; companion initialization matches; actual named/random dog/cat and saddled pony match on defined room inputs; full-game lifecycle remains unverified.`);
