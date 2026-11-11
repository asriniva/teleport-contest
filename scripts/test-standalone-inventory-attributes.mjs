import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/standalone/environment.js';
import {C,R,T} from '../js/ported/c-runtime.js';
const directory=path.resolve(process.env.STANDALONE_INVENTORY_STARTUP_ORACLE||'.cache/standalone-inventory-startup-v1');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json')));
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const [p,h]of Object.entries(receipt.sourceSha256))assert.equal(sha(p),h,'Changed C source '+p);
for(const [p,h]of Object.entries(receipt.artifactSha256))assert.equal(sha(path.join(directory,p)),h,'Changed C artifact '+p);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs')));
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L=layouts.makemon,M=layouts.mkobj;
const metadata=JSON.parse(fs.readFileSync('js/standalone/records.json')).records;

const dataRoot=path.join(process.env.STANDALONE_REFERENCE_ROOT,'.cache/wasm64-build/tree/dat');
const files=['nhlib.lua','dungeon.lua','nhcore.lua'].map(name=>[name,fs.readFileSync(path.join(dataRoot,name))]);
let comparisons=0;
function snapshot(heap,at,type,count=1){
 at=Number(at);const record=metadata[type]??(['short','long'].includes(type)?{size:type==='short'?2:8,fields:{}}:null);assert.ok(record,'Measured snapshot '+type);const bytes=Buffer.from(heap.slice(at,at+record.size*count)),strings={};
 function walk(type,offset,label){for(const [name,f]of Object.entries(metadata[type]?.fields??{})){
  const arr=f.ctype.match(/\[(\d+)\]/),n=arr?Number(arr[1]):1,child=f.record||f.ctype.match(/struct (\w+)/)?.[1];
  if(f.ctype.includes('*')||(name==='luacore'&&f.ctype==='genericptr_t luacore'))for(let i=0;i<n;i++){
   const pos=offset+f.offset+i*8,p=Number(bytes.readBigUInt64LE(pos));
   if(/char\s*\*/.test(f.ctype)){let end=p;if(p){while(heap[end])end++;strings[label+'.'+name+'['+i+']']=Buffer.from(heap.slice(p,end)).toString('latin1');}else strings[label+'.'+name+'['+i+']']=null;}
   else if(p){const target=f.ctype.replace(/^struct /,'').split(' *')[0];if(name==='luacore'){strings[label+'.'+name+'['+i+']']='Lua state';}else if(target==='permonst'){const pm=new DataView(heap.buffer).getInt32(p+metadata.permonst.fields.pmidx.offset,true);strings[label+'.'+name+'['+i+']']={species:pm};}else{assert.ok(['s_level','branch'].includes(target),'Unmodeled non-string pointer '+label+'.'+name);strings[label+'.'+name+'['+i+']']=snapshot(heap,p,target);}} 
   bytes.writeBigUInt64LE(p?1n:0n,pos);
  }else if(child&&metadata[child])for(let i=0;i<n;i++)walk(child,offset+f.offset+i*metadata[child].size,label+'.'+name+'['+i+']');
 }}
 for(let i=0;i<count;i++)walk(type,i*record.size,type+'['+i+']');return {bytes,strings};
}
for(const seed of [1n,0x12345678n,0xffffffffffffffffn])for(const input of [...Array.from({length:13},(_,role)=>[role,0,0,0,'Ada']),[0,2,0,0,'Ada'],[0,3,1,1,'Ada'],[6,1,1,2,'Ada'],[12,4,0,2,'Ada'],[11,2,1,0,'Ada']])for(const roleplay of [0,1,2,4,8,255])for(const phase of ['hero']){
 const env=createStandaloneEnvironment({initialBytes:1024,maximumBytes:64*1024*1024,environment:{NETHACK_RNGLOG:'/rng.log',NETHACK_FIXED_DATETIME:'20260102030405'}});
 env.enableStdio();env.enableDecl(layouts.decl);env.call('decl','program_state_init');env.call('decl','decl_globals_init');env.enableDrawing(layouts.drawing);env.enableObjects(layouts.objects);env.call('objects','objects_globals_init');env.enableMonst(layouts.monst);env.call('monst','monst_globals_init');env.enableSerialization(layouts);env.enableRnd(layouts.rnd,{seed});env.call('rnd','rng_log_init');env.enableAddressPort('dungeon',{only:['ledger_no','maxledgerno']});env.enableObjectState(layouts);env.enableObjectRecords(layouts);env.enableItemInventory(layouts);env.enableTimers(layouts);env.enableItemNaming(layouts);const group=env.enableMonsterSelection(layouts);const decl=JSON.parse(fs.readFileSync('js/standalone/decl-storage.json')).globals,before=decl.map(r=>env.memory.readBytes(env.requireGlobal(r.name),r.bytes));const creation=env.enableMonsterCreation(layouts);decl.forEach((r,i)=>assert.deepEqual(env.memory.readBytes(env.requireGlobal(r.name),r.bytes),before[i],'enabling creation preserves '+r.name));

 const startup=env.enableGameStartup(layouts);env.call('sys','sys_early_init');
 const errors=[];const ref=await factory({printErr:s=>errors.push(s)});ref._probe_startup_init(seed);const timeKey=ref._malloc(23n),timeValue=ref._malloc(15n);ref.HEAPU8.set(Buffer.from('NETHACK_FIXED_DATETIME\0'),Number(timeKey));ref.HEAPU8.set(Buffer.from('20260102030405\0'),Number(timeValue));ref._setenv(BigInt(timeKey),BigInt(timeValue),1);ref._free(BigInt(timeKey));ref._free(BigInt(timeValue));
 function enableSandbox(){const rows=JSON.parse(fs.readFileSync('js/standalone/decl-storage.json')).globals,images=rows.map(row=>env.memory.readBytes(env.requireGlobal(row.name),row.bytes));env.enableLuaSandbox(layouts);rows.forEach((row,i)=>assert.deepEqual(env.memory.readBytes(env.requireGlobal(row.name),row.bytes),images[i],'sandbox construction preserves '+row.name));}
 const [r,race,g,a,name]=input,flags=env.services.flags;
 Object.assign(flags,{initrole:r,initrace:race,initgend:g,initalign:a,female:0,pantheon:-1});
 for(const field of ['plname','pl_character'])env.memory.HEAPU8.fill(0,startup.role.svp[field],startup.role.svp[field]+(field==='plname'?layouts.role.PL_NSIZ:layouts.role.PL_CSIZ));
 env.services.strcpy(startup.role.svp.plname,env.services.literal(name));
 const p=ref._malloc(BigInt(name.length+1));ref.HEAPU8.set(Buffer.from(name+'\0'),Number(p));ref._probe_startup_role_config(r,race,g,a,BigInt(p));ref._free(BigInt(p));
 const entries=[['flags','flag',1],['gu','instance_globals_u',1],['svq','instance_globals_saved_q',1],['svp','instance_globals_saved_p',1],['gr','instance_globals_r',1],['gp','instance_globals_p',1],['mons','permonst',layouts.makemon.NUMMONS+1],['objects','objclass',layouts.objects.NUM_OBJECTS+1],['a11y','accessibility_data',1],['svc','instance_globals_saved_c',1],['roles','Role',14],['races','Race',6],['genders','Gender',4],['aligns','Align',4],['svd','instance_globals_saved_d',1],['svn','instance_globals_saved_n',1],['svm','instance_globals_saved_m',1],['disp','display_hints',1],['sysopt','sysopt_s',1],['program_state','sinfo',1],['iflags','instance_flags',1]];
 const pointers=entries.map((_,i)=>ref._probe_startup_global(i));for(const [i,[name,type]]of [['svs','instance_globals_saved_s'],['gl','instance_globals_l'],['svb','instance_globals_saved_b'],['svt','instance_globals_saved_t']].entries()){entries.push([name,type,1]);pointers.push(ref._probe_dungeon_global(i));}
 const heroEntries=[['artilist','artifact',35],['artiexist','arti_info',34],['artidisco','short',33],['u','you',1],['gy','instance_globals_y',1],['gm','instance_globals_m',1],['gw','instance_globals_w',1],['ubirthday','long',1],['urealtime','u_realtime',1],['svl','instance_globals_saved_l',1]];
 for(const [i,entry]of heroEntries.entries()){entries.push(entry);pointers.push(ref._probe_hero_global(i));}
 function compare(phase){for(const [i,[name,type,n]]of entries.entries()){
  assert.ok(Number.isInteger(n),name+' count');const actual=snapshot(env.memory.HEAPU8,env.requireGlobal(name),type,n),expected=snapshot(ref.HEAPU8,pointers[i],type,n);assert.deepEqual(actual.strings,expected.strings,phase+' strings '+name+' '+input);const diffs=[];actual.bytes.forEach((v,i)=>{if(v!==expected.bytes[i])diffs.push([i,v,expected.bytes[i]]);});assert.deepEqual(diffs.slice(0,20),[],phase+' bytes '+name+' '+input+' total '+diffs.length);comparisons++;
 }}
 function compareInventory(){
  const cgi=Number(ref._probe_decl_global(decl.findIndex(r=>r.name==='gi'))),jgi=env.requireGlobal('gi'),off=metadata.instance_globals_i.fields.invent.offset;
  const ptr=(heap,p)=>Number(new DataView(heap.buffer,heap.byteOffset,heap.byteLength).getBigUint64(p,true));
  function graph(heap,start,seen=new Set()){
   const rows=[];for(let p=start;p;p=ptr(heap,p+metadata.obj.fields.nobj.offset)){
    assert.ok(!seen.has(p),'inventory graph has no cycle');seen.add(p);const bytes=Buffer.from(heap.slice(p,p+metadata.obj.size));
    for(const f of Object.values(metadata.obj.fields))if(f.ctype.includes('*')||f.record==='vptrs')bytes.fill(0,f.offset,f.offset+8);
    const contents=ptr(heap,p+metadata.obj.fields.cobj.offset),extra=ptr(heap,p+metadata.obj.fields.oextra.offset);let name=null;
    if(extra){const np=ptr(heap,extra+metadata.oextra.fields.oname.offset);if(np){let end=np;while(heap[end])end++;name=Buffer.from(heap.slice(np,end)).toString('latin1');}}
    rows.push({bytes,name,contents:contents?graph(heap,contents,seen):[]});
   }return rows;
  }
  assert.deepEqual(graph(env.memory.HEAPU8,ptr(env.memory.HEAPU8,jgi+off)),graph(ref.HEAPU8,ptr(ref.HEAPU8,cgi+off)),'source starting inventory records and contents '+input);comparisons++;
 }
 const rows=JSON.parse(fs.readFileSync('js/standalone/decl-storage.json')).globals,images=rows.map(row=>env.memory.readBytes(env.requireGlobal(row.name),row.bytes));env.enableHeroStartup(layouts);rows.forEach((row,i)=>assert.deepEqual(env.memory.readBytes(env.requireGlobal(row.name),row.bytes),images[i],'hero providers preserve '+row.name));const rp=env.services.u.uroleplay;['blind','nudist','deaf','pauper','reroll','reserved1','reserved2','reserved3'].forEach((k,i)=>rp[k]=(roleplay>>i)&1);rp.numbones=roleplay?4294967299n:0n;rp.numrerolls=roleplay?-3n:0n;ref._probe_hero_roleplay(roleplay,rp.numbones,rp.numrerolls);compare('before');env.enableWorldPosition(layouts);if(!env.status()['nhlua'])enableSandbox();for(const [name,bytes]of files){env.filesystem.writeFile(name,bytes);ref.FS.writeFile(name,bytes);}
 if(phase==='hero'){
  env.services.init_objects();env.services.role_init();env.services.init_dungeons();env.services.init_artifacts();env.services.u_init_misc();env.services.l_nhcore_init();ref._probe_hero_init();compare(phase);env.enableLevelStartup(layouts);env.enableLevelContents(layouts);env.enableMovement(layouts);const ident=metadata.instance_globals_saved_c.fields.context.offset+metadata.context_info.fields.ident.offset;env.memory.view.setUint32(env.requireGlobal('svc')+ident,2,true);new DataView(ref.HEAPU8.buffer).setUint32(Number(ref._probe_startup_global(9))+ident,2,true);env.services.u_init_inventory_attrs();ref._u_init_inventory_attrs();compare('inventory attributes');compareInventory();assert.deepEqual(errors,[],'Unexpected C output');
  const jsCore=Number(env.ctypes.getField('struct instance_globals_l',env.requireGlobal('gl'),'luacore','void *')),cCore=Number(new DataView(ref.HEAPU8.buffer).getBigUint64(Number(ref._probe_dungeon_global(1))+metadata.instance_globals_l.fields.luacore.offset,true));
  assert.ok(jsCore&&cCore,'persistent core state');
  for(const global of ['nhcore','nh','selection','obj','des']){const key=ref._malloc(BigInt(global.length+1));ref.HEAPU8.set(Buffer.from(global+'\0'),Number(key));const actual=env.services.lua_getglobal(jsCore,global),expected=ref._lua_getglobal(BigInt(cCore),BigInt(key));assert.equal(actual,5,'persistent table '+global);assert.equal(actual,expected,'core table '+global);ref._free(BigInt(key));env.services.lua_settop(jsCore,0);ref._lua_settop(BigInt(cCore),0);comparisons++;}

 }else{assert.throws(()=>env.services.newgame(),/Unresolved standalone function has_color/);assert.throws(()=>ref._probe_startup_newgame(),/abort|unreachable/i);assert.ok(errors.some(s=>s.includes('Unconnected C boundary: has_color')),errors.join('\n'));compare(phase);}
 const log=e=>Buffer.from(e).toString('latin1').split('\n'),actual=log(env.filesystem.readFile('/rng.log')),expected=log(ref.FS.readFile('/rng.log'));
 assert.equal(actual.length,expected.length,'RNG length '+input);actual.forEach((line,i)=>assert.equal(line,expected[i],'RNG '+i+' '+input));comparisons++;
 assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);
}
console.log('PASS: '+comparisons+' original-C starting inventory/attribute shared-state and RNG comparisons. Full newgame remains under integration.');
