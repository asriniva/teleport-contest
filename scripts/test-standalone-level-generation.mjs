import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/standalone/environment.js';
import {C,R,T} from '../js/c-runtime/context.js';
const directory=path.resolve(process.env.STANDALONE_LEVEL_STARTUP_ORACLE||'.cache/standalone-level-startup-v9');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json')));
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const [p,h]of Object.entries(receipt.sourceSha256))assert.equal(sha(p),h,'Changed C source '+p);
for(const [p,h]of Object.entries(receipt.artifactSha256))assert.equal(sha(path.join(directory,p)),h,'Changed C artifact '+p);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs')));
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L=layouts.makemon,M=layouts.mkobj;
const abi=JSON.parse(fs.readFileSync('js/standalone/display-abi.json'));
const metadata=JSON.parse(fs.readFileSync('js/standalone/records.json')).records;

const dataRoot=path.join(process.env.STANDALONE_REFERENCE_ROOT,'.cache/wasm64-build/tree/dat');
const files=fs.readdirSync(dataRoot).filter(n=>n.endsWith('.lua')).map(name=>[name,fs.readFileSync(path.join(dataRoot,name))]);
let comparisons=0;const aliases=new WeakMap();
function snapshot(heap,at,type,count=1){
 at=Number(at);const record=metadata[type]??(['short','long'].includes(type)?{size:type==='short'?2:8,fields:{}}:null);assert.ok(record,'Measured snapshot '+type);const bytes=Buffer.from(heap.slice(at,at+record.size*count)),strings={};
 function walk(type,offset,label){for(const [name,f]of Object.entries(metadata[type]?.fields??{})){
  const arr=f.ctype.match(/\[(\d+)\]/),n=arr?Number(arr[1]):1,child=f.record||f.ctype.match(/struct (\w+)/)?.[1];
  if(f.ctype.includes('*')||(['luacore','luathemes'].includes(name)&&f.ctype.startsWith('genericptr_t')))for(let i=0;i<n;i++){
   const pos=offset+f.offset+i*8,p=Number(bytes.readBigUInt64LE(pos));
   if(/char\s*\*/.test(f.ctype)){let end=p;if(p){while(heap[end])end++;strings[label+'.'+name+'['+i+']']=Buffer.from(heap.slice(p,end)).toString('latin1');}else strings[label+'.'+name+'['+i+']']=null;}
   else if(p){const target=f.ctype.replace(/^struct /,'').split(' *')[0];const alias=aliases.get(heap.buffer)?.find(row=>p>=row.at&&p<row.at+row.bytes);if(alias){strings[label+'.'+name+'['+i+']']={global:alias.name,offset:p-alias.at};}else if(['luacore','luathemes'].includes(name)){strings[label+'.'+name+'['+i+']']='Lua state';}else if(target==='permonst'){const pm=new DataView(heap.buffer).getInt32(p+metadata.permonst.fields.pmidx.offset,true);strings[label+'.'+name+'['+i+']']={species:pm};}else{assert.ok(['s_level','branch','mapseen','sp_coder'].includes(target),'Unmodeled non-string pointer '+label+'.'+name);strings[label+'.'+name+'['+i+']']=snapshot(heap,p,target);}}
   bytes.writeBigUInt64LE(p?1n:0n,pos);
  }else if(child&&metadata[child])for(let i=0;i<n;i++)walk(child,offset+f.offset+i*metadata[child].size,label+'.'+name+'['+i+']');
 }}
 // create_des_coder initializes every field, while C allocation padding is
 // unspecified. Compare all defined bytes using measured offsets/ABI widths.
 if(type==='sp_coder'){
  const mask=new Uint8Array(record.size);
  for(const [key,f]of Object.entries(record.fields)){const n=Number(f.ctype.match(/\[(\d+)\]/)?.[1]??1),width=f.ctype.includes('*')?8:f.ctype.startsWith('boolean')?1:4;mask.fill(1,f.offset,f.offset+n*width);}
  for(let i=0;i<count;i++)for(let j=0;j<record.size;j++)if(!mask[j])bytes[i*record.size+j]=0;
 }
 for(let i=0;i<count;i++)walk(type,i*record.size,type+'['+i+']');return {bytes,strings};
}

for(const seed of [1n,0x12345678n,0xffffffffffffffffn])for(const role of [0,6,11,12]){
 const env=createStandaloneEnvironment({initialBytes:1024,maximumBytes:64*1024*1024,environment:{NETHACK_RNGLOG:'/rng.log',NETHACK_FIXED_DATETIME:'20260102030405'}});
 env.enableStdio();env.enableDecl(layouts.decl);env.call('decl','program_state_init');env.call('decl','decl_globals_init');env.enableDrawing(layouts.drawing);env.enableObjects(layouts.objects);env.call('objects','objects_globals_init');env.enableMonst(layouts.monst);env.call('monst','monst_globals_init');env.enableSerialization(layouts);env.enableRnd(layouts.rnd,{seed});env.call('rnd','rng_log_init');env.enableAddressPort('dungeon',{only:['ledger_no','maxledgerno']});env.enableObjectState(layouts);env.enableObjectRecords(layouts);env.enableItemInventory(layouts);env.enableTimers(layouts);env.enableItemNaming(layouts);const group=env.enableMonsterSelection(layouts);const decl=JSON.parse(fs.readFileSync('js/standalone/decl-storage.json')).globals,before=decl.map(r=>env.memory.readBytes(env.requireGlobal(r.name),r.bytes));const creation=env.enableMonsterCreation(layouts);decl.forEach((r,i)=>assert.deepEqual(env.memory.readBytes(env.requireGlobal(r.name),r.bytes),before[i],'enabling creation preserves '+r.name));

 const startup=env.enableGameStartup(layouts);env.call('sys','sys_early_init');
 const errors=[];const ref=await factory({printErr:s=>errors.push(s)});ref._probe_level_init(seed);const timeKey=ref._malloc(23n),timeValue=ref._malloc(15n);ref.HEAPU8.set(Buffer.from('NETHACK_FIXED_DATETIME\0'),Number(timeKey));ref.HEAPU8.set(Buffer.from('20260102030405\0'),Number(timeValue));ref._setenv(BigInt(timeKey),BigInt(timeValue),1);ref._free(BigInt(timeKey));ref._free(BigInt(timeValue));

 const display=env.enableDisplayStartup(layouts),{signals}=display,wp=display.environment.windowprocs;
 const cActions=Number(ref._probe_signal_global()),cPointers=Array.from({length:5},(_,i)=>BigInt.asUintN(64,BigInt(ref._probe_signal_pointer(i))));
 let seen=0;const first=sig=>{seen=100+sig;},second=sig=>{seen=200+sig;},jPointers=[BigInt(abi.SIG_DFL),BigInt(abi.SIG_IGN),signals.handler(first),signals.handler(second),display.done1];
 assert.ok(!jPointers.slice(0,2).includes(jPointers[2])&&!jPointers.slice(0,2).includes(jPointers[3]),'callback IDs distinct from measured signal sentinels');
 function token(p,pointers){p=BigInt.asUintN(64,BigInt(p));if(p===0xffffffffffffffffn)return -1;const i=pointers.indexOf(p);assert.ok(i>=0,'known signal identity '+p);return i;}
 function actions(heap,p,pointers){const out=[];for(let sig=0;sig<abi.signalCount;sig++){
  const at=Number(p)+sig*abi.actionSize,b=Buffer.from(heap.slice(at,at+abi.actionSize));
  out.push({handler:token(b.readBigUInt64LE(abi.handler),pointers),mask:b.subarray(abi.mask,abi.mask+abi.maskSize),flags:b.readInt32LE(abi.flags),restorer:b.readBigUInt64LE(abi.restorer)});
 }return out;}
 const compareActions=()=>{assert.deepEqual(actions(env.memory.HEAPU8,signals.actions,jPointers),actions(ref.HEAPU8,cActions,cPointers),'complete defined action fields');comparisons++;};
 const set=(g,type,field,value)=>env.ctypes.setField(type,env.requireGlobal(g),field,env.ctypes.record(type).fields[field].ctype.replace(new RegExp(' '+field+'$'),''),value);
 function config(use,named,caps,mask,graphics=0,handling=0,nocolor=0){
  set('iflags','struct instance_flags','wc_color',use);wp.name=named?env.services.literal('standalone-test'):0;wp.wincap=caps;for(let i=0;i<16;i++)wp.has_color[i]=(mask>>i)&1;
  const gc=env.ctypes.record('struct instance_globals_c'),gs=env.ctypes.record('struct instance_globals_s');set('gc','struct instance_globals_c','currentgraphics',graphics);
  const at=env.requireGlobal('gs')+gs.fields.symset.offset+graphics*metadata.symsetentry.size;env.ctypes.setField('struct symsetentry',at,'handling','enum symset_handling_types',handling);env.ctypes.setField('struct symsetentry',at,'nocolor','unsigned int',nocolor);
  ref._probe_display_config(use,named,BigInt(caps),mask,graphics,handling,nocolor);
 }
 if(role===0)for(const use of [0,1])for(const named of [0,1])for(const caps of [0n,1n,2n,3n])for(const mask of [0,0xaaaa,0xffff]){config(use,named,caps,mask);for(let color=0;color<16;color++){assert.equal(Number(env.services.has_color(color)),ref._has_color(color),'color '+color);comparisons++;}}
 // Complete real newgame prefix, with ordinary color-enabled caller settings.
 config(1,1,1n,0xffff);
 const flags=env.services.flags;Object.assign(flags,{initrole:role,initrace:0,initgend:0,initalign:0,female:0,pantheon:-1});env.services.strcpy(startup.role.svp.plname,env.services.literal('Ada'));
 const name=ref._malloc(4n);ref.HEAPU8.set(Buffer.from('Ada\0'),Number(name));ref._probe_startup_role_config(role,0,0,0,BigInt(name));ref._free(BigInt(name));
 env.enableHeroStartup(layouts);env.enableWorldPosition(layouts);env.enableLuaSandbox(layouts);for(const [name,bytes]of files){env.filesystem.writeFile(name,bytes);ref.FS.writeFile(name,bytes);}
 env.enableLevelStartup(layouts);
 const entries=[['flags','flag',1],['gu','instance_globals_u',1],['svq','instance_globals_saved_q',1],['svp','instance_globals_saved_p',1],['gr','instance_globals_r',1],['gp','instance_globals_p',1],['mons','permonst',layouts.makemon.NUMMONS+1],['objects','objclass',layouts.objects.NUM_OBJECTS+1],['a11y','accessibility_data',1],['svc','instance_globals_saved_c',1],['roles','Role',14],['races','Race',6],['genders','Gender',4],['aligns','Align',4],['svd','instance_globals_saved_d',1],['svn','instance_globals_saved_n',1],['svm','instance_globals_saved_m',1],['disp','display_hints',1],['sysopt','sysopt_s',1],['program_state','sinfo',1],['iflags','instance_flags',1]];
 const pointers=entries.map((_,i)=>ref._probe_startup_global(i));
 for(const [i,row]of [['svs','instance_globals_saved_s',1],['gl','instance_globals_l',1],['svb','instance_globals_saved_b',1],['svt','instance_globals_saved_t',1]].entries()){entries.push(row);pointers.push(ref._probe_dungeon_global(i));}
 for(const [i,row]of [['artilist','artifact',35],['artiexist','arti_info',34],['artidisco','short',33],['u','you',1],['gy','instance_globals_y',1],['gm','instance_globals_m',1],['gw','instance_globals_w',1],['ubirthday','long',1],['urealtime','u_realtime',1],['svl','instance_globals_saved_l',1]].entries()){entries.push(row);pointers.push(ref._probe_hero_global(i));}
 for(const [i,row]of [['display.glyphmap','glyph_map_entry',abi.glyphCount],['gg','instance_globals_g',1],['windowprocs','window_procs',1],['gc','instance_globals_c',1],['gs','instance_globals_s',1],['go','instance_globals_o',1]].entries()){entries.push(row);pointers.push(ref._probe_display_global(i));}
 entries.push(['svr','instance_globals_saved_r',1]);pointers.push(ref._probe_decl_global(JSON.parse(fs.readFileSync('js/standalone/decl-storage.json')).globals.findIndex(r=>r.name==='svr')));
 function compare(label){const decl=JSON.parse(fs.readFileSync('js/standalone/decl-storage.json')).globals;for(const [heap,isJS]of [[env.memory.HEAPU8,true],[ref.HEAPU8,false]])aliases.set(heap.buffer,[...decl.map((row,i)=>({name:row.name,bytes:row.bytes,at:isJS?env.requireGlobal(row.name):Number(cDecl[i])})),...entries.map(([name,type,n],i)=>({name,bytes:(metadata[type]?.size??(type==='short'?2:8))*n,at:isJS?env.requireGlobal(name):Number(pointers[i])}))]);for(const [i,[name,type,n]]of entries.entries()){assert.deepEqual(snapshot(env.memory.HEAPU8,env.requireGlobal(name),type,n),snapshot(ref.HEAPU8,pointers[i],type,n),label+' '+name);comparisons++;}}
 const cDecl=JSON.parse(fs.readFileSync('js/standalone/decl-storage.json')).globals.map((_,i)=>ref._probe_decl_global(i));
 compare('before');let boundary;
 assert.throws(()=>env.services.newgame(),error=>{const match=error.message.match(/^Unresolved standalone function (maketrap|has_dnstairs)$/);if(!match)return false;boundary=match[1];return true;});
 assert.throws(()=>ref._probe_startup_newgame(),/abort|unreachable/i);assert.ok(errors.some(s=>s.includes('Unconnected C boundary: '+boundary)),errors.join('\n'));compare('newgame');compareActions();
 const themeField=metadata.instance_globals_l.fields.luathemes.offset;
 const jgl=env.requireGlobal('gl'),cgl=Number(ref._probe_dungeon_global(1));
 for(let i=0;i<16;i++){
  const jl=Number(new DataView(env.memory.HEAPU8.buffer).getBigUint64(jgl+themeField+8*i,true)),cl=Number(new DataView(ref.HEAPU8.buffer).getBigUint64(cgl+themeField+8*i,true));
  assert.equal(Boolean(jl),Boolean(cl),'theme state presence');comparisons++;
  if(!jl)continue;
  for(const global of ['themerooms','themeroom_fills','nh','selection','des','post_level_generate']){
   const key=ref._malloc(BigInt(global.length+1));ref.HEAPU8.set(Buffer.from(global+'\0'),Number(key));
   const actual=env.services.lua_getglobal(jl,global),expected=ref._lua_getglobal(BigInt(cl),BigInt(key));
   assert.equal(actual,expected,'theme '+i+' global '+global);assert.equal(actual,global==='post_level_generate'?6:5);comparisons+=2;
   ref._free(BigInt(key));env.services.lua_settop(jl,0);ref._lua_settop(BigInt(cl),0);
  }
 }
 const actual=Buffer.from(env.filesystem.readFile('/rng.log')).toString('latin1').split('\n'),expected=Buffer.from(ref.FS.readFile('/rng.log')).toString('latin1').split('\n');assert.equal(actual.length,expected.length);actual.forEach((line,i)=>assert.equal(line,expected[i],'RNG '+i));comparisons++;
 assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);
}
console.log('PASS: '+comparisons+' original-C connected level-startup shared-state/RNG comparisons; actual newgame reaches matching unconnected maketrap/has_dnstairs boundaries. No full-game acceptance.');
