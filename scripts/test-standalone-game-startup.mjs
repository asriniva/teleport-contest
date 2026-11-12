import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/standalone/environment.js';
import {C,R,T} from '../js/c-runtime/context.js';
const directory=path.resolve(process.env.STANDALONE_STARTUP_ORACLE||'.cache/standalone-startup-v4');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json')));
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const [p,h]of Object.entries(receipt.sourceSha256))assert.equal(sha(p),h,'Changed C source '+p);
for(const [p,h]of Object.entries(receipt.artifactSha256))assert.equal(sha(path.join(directory,p)),h,'Changed C artifact '+p);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs')));
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L=layouts.makemon,M=layouts.mkobj;
const metadata=JSON.parse(fs.readFileSync('js/standalone/records.json')).records;

let comparisons=0;
function snapshot(heap,at,type,count=1){
 at=Number(at);const record=metadata[type],bytes=Buffer.from(heap.slice(at,at+record.size*count)),strings={};
 function walk(type,offset,label){for(const [name,f]of Object.entries(metadata[type].fields)){
  const arr=f.ctype.match(/\[(\d+)\]/),n=arr?Number(arr[1]):1,child=f.record||f.ctype.match(/struct (\w+)/)?.[1];
  if(f.ctype.includes('*'))for(let i=0;i<n;i++){
   const pos=offset+f.offset+i*8,p=Number(bytes.readBigUInt64LE(pos));
   if(/char\s*\*/.test(f.ctype)){let end=p;if(p){while(heap[end])end++;strings[label+'.'+name+'['+i+']']=Buffer.from(heap.slice(p,end)).toString('latin1');}else strings[label+'.'+name+'['+i+']']=null;}
   else assert.equal(p,0,'Unmodeled non-string pointer '+label+'.'+name);
   bytes.writeBigUInt64LE(p?1n:0n,pos);
  }else if(child&&metadata[child])for(let i=0;i<n;i++)walk(child,offset+f.offset+i*metadata[child].size,label+'.'+name+'['+i+']');
 }}
 for(let i=0;i<count;i++)walk(type,i*record.size,type+'['+i+']');return {bytes,strings};
}
for(const seed of [1n,0x12345678n,0xffffffffffffffffn])for(const input of [
 ...Array.from({length:13},(_,i)=>[i,0,0,0,'Ada']),[-1,-1,-1,-1,'Ada'],[-2,-2,-2,-2,'Ada'],[99,99,99,99,'Ada'],[-1,-1,-1,-1,'Ada-Wiz-Elf-Fem-Cha']
])for(const phase of ['role','startup-prefix']){
 const env=createStandaloneEnvironment({initialBytes:1024,maximumBytes:64*1024*1024,environment:{NETHACK_RNGLOG:'/rng.log'}});
 env.enableStdio();env.enableDecl(layouts.decl);env.call('decl','program_state_init');env.call('decl','decl_globals_init');env.enableDrawing(layouts.drawing);env.enableObjects(layouts.objects);env.call('objects','objects_globals_init');env.enableMonst(layouts.monst);env.call('monst','monst_globals_init');env.enableSerialization(layouts);env.enableRnd(layouts.rnd,{seed});env.call('rnd','rng_log_init');env.enableAddressPort('dungeon',{only:['ledger_no','maxledgerno']});env.enableObjectState(layouts);env.enableObjectRecords(layouts);env.enableItemInventory(layouts);env.enableTimers(layouts);env.enableItemNaming(layouts);const group=env.enableMonsterSelection(layouts);const decl=JSON.parse(fs.readFileSync('js/standalone/decl-storage.json')).globals,before=decl.map(r=>env.memory.readBytes(env.requireGlobal(r.name),r.bytes));const creation=env.enableMonsterCreation(layouts);decl.forEach((r,i)=>assert.deepEqual(env.memory.readBytes(env.requireGlobal(r.name),r.bytes),before[i],'enabling creation preserves '+r.name));

 const startup=env.enableGameStartup(layouts);env.call('sys','sys_early_init');
 const errors=[];const ref=await factory({printErr:s=>errors.push(s)});ref._probe_startup_init(seed);
 const [r,race,g,a,name]=input,flags=env.services.flags;
 Object.assign(flags,{initrole:r,initrace:race,initgend:g,initalign:a,female:0,pantheon:-1});
 for(const field of ['plname','pl_character'])env.memory.HEAPU8.fill(0,startup.role.svp[field],startup.role.svp[field]+(field==='plname'?layouts.role.PL_NSIZ:layouts.role.PL_CSIZ));
 env.services.strcpy(startup.role.svp.plname,env.services.literal(name));
 const p=ref._malloc(BigInt(name.length+1));ref.HEAPU8.set(Buffer.from(name+'\0'),Number(p));ref._probe_startup_role_config(r,race,g,a,BigInt(p));ref._free(BigInt(p));
 const entries=[['flags','flag',1],['gu','instance_globals_u',1],['svq','instance_globals_saved_q',1],['svp','instance_globals_saved_p',1],['gr','instance_globals_r',1],['gp','instance_globals_p',1],['mons','permonst',layouts.makemon.NUMMONS+1],['objects','objclass',layouts.objects.NUM_OBJECTS+1],['a11y','accessibility_data',1],['svc','instance_globals_saved_c',1],['roles','Role',14],['races','Race',6],['genders','Gender',4],['aligns','Align',4],['svd','instance_globals_saved_d',1],['svn','instance_globals_saved_n',1],['svm','instance_globals_saved_m',1],['disp','display_hints',1],['sysopt','sysopt_s',1],['program_state','sinfo',1],['iflags','instance_flags',1]];
 const pointers=entries.map((_,i)=>ref._probe_startup_global(i));
 function compare(phase){for(const [i,[name,type,n]]of entries.entries()){
  assert.ok(Number.isInteger(n),name+' count');const actual=snapshot(env.memory.HEAPU8,env.requireGlobal(name),type,n),expected=snapshot(ref.HEAPU8,pointers[i],type,n);assert.deepEqual(actual.strings,expected.strings,phase+' strings '+name+' '+input);const diffs=[];actual.bytes.forEach((v,i)=>{if(v!==expected.bytes[i])diffs.push([i,v,expected.bytes[i]]);});assert.deepEqual(diffs.slice(0,20),[],phase+' bytes '+name+' '+input+' total '+diffs.length);comparisons++;
 }}
 compare('before');if(phase==='role'){env.services.role_init();ref._probe_startup_role();}else{assert.throws(()=>env.services.newgame(),/Unresolved standalone function nhl_init/);assert.throws(()=>ref._probe_startup_newgame(),/abort|unreachable/i);assert.ok(errors.some(s=>s.includes('Unconnected C boundary: nhl_init')),errors.join('\n'));}compare(phase);
 const log=e=>Buffer.from(e).toString('latin1').split('\n'),actual=log(env.filesystem.readFile('/rng.log')),expected=log(ref.FS.readFile('/rng.log'));
 assert.equal(actual.length,expected.length,'RNG length '+input);actual.forEach((line,i)=>assert.equal(line,expected[i],'RNG '+i+' '+input));comparisons++;
 assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);
}
console.log('PASS: '+comparisons+' original-C startup role/table/shared-state and RNG comparisons. Full newgame remains under integration.');
