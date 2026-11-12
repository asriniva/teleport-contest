// A combined original-C dependency group, not synthetic per-call RNG/IO stubs.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/standalone/environment.js';
import {C,R,T} from '../js/c-runtime/context.js';
const directory=path.resolve(process.env.STANDALONE_OBJECT_STATE_ORACLE||'.cache/standalone-object-state');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json')));
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const [p,digest]of Object.entries(receipt.sourceSha256))assert.equal(sha(p),digest,'C reference source changed: '+p);
for(const [p,digest]of Object.entries(receipt.artifactSha256))assert.equal(sha(path.join(directory,p)),digest,'C oracle artifact changed: '+p);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs')));
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L=layouts.o_init,B=layouts.sfbase,S=layouts.sfstruct;
let comparisons=0;
function create(seed){
 const env=createStandaloneEnvironment({initialBytes:1024,maximumBytes:64*1024*1024,environment:{NETHACK_RNGLOG:'/rng.log'}});
 env.enableStdio();env.enableDecl(layouts.decl);env.enableDrawing(layouts.drawing);env.enableObjects(layouts.objects);env.enableHacklib(layouts.hacklib);
 env.call('objects','objects_globals_init');env.enableSerialization(layouts);env.enableRnd(layouts.rnd,{seed});env.call('rnd','rng_log_init');
 env.enableAddressPort('dungeon',{only:['ledger_no','maxledgerno']});
 const component=env.enableObjectState(layouts);assert.equal(component.exports.length,13);
 assert.throws(()=>env.resolve('dodiscovered'),/Unresolved/);assert.equal(typeof env.resolve('init_dungeons'),'function');assert.throws(()=>env.resolve('nhl_init'),/Unresolved/);
 const {ctypes}=env;
 const set=(type,p,field,v)=>ctypes.setField(type,p,field,field==='num_dunlevs'?'short':'int',v);
 // Explicit input dungeon map; both sides use the real ledger functions.
 set('struct instance_globals_saved_n',env.requireGlobal('svn'),'n_dgns',2);
 const d=ctypes.locate('struct instance_globals_saved_d',env.requireGlobal('svd'),'dungeons').at;
 for(let i=0;i<2;i++){
  set('struct dungeon',d+i*ctypes.size('struct dungeon'),'ledger_start',i?30:0);
  set('struct dungeon',d+i*ctypes.size('struct dungeon'),'num_dunlevs',i?20:30);
 }
 env.services.u.uz.dnum=0;env.services.u.uz.dlevel=1;
 return env;
}
function text(m,p){if(!p)return null;let end=Number(p);while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(Number(p),end)).toString('latin1');}
function normalized(bytes,offset=0){const b=Buffer.from(bytes);for(let i=0;i<L.NUM_OBJECTS;i++){const at=offset+i*L.objectClassSize+L.cls_oc_uname;b.writeBigUInt64LE(b.readBigUInt64LE(at)?1n:0n,at);}return b;}
function rows(env){return normalized(env.memory.readBytes(env.requireGlobal('objects'),L.NUM_OBJECTS*L.objectClassSize));}
function state(env,ref,label){
 assert.deepEqual(rows(env),normalized(ref.HEAPU8.slice(Number(ref._probe_pointer(0)),Number(ref._probe_pointer(0))+L.NUM_OBJECTS*L.objectClassSize)),label+' objects');
 for(const [kind,name,field,size]of [[1,'svb','bases',(L.MAXOCLASSES+2)*4],[2,'svd','disco',L.NUM_OBJECTS*2],[3,'go','oclass_prob_totals',L.MAXOCLASSES*2]]){
  const at=env.ctypes.locate('struct '+({svb:'instance_globals_saved_b',svd:'instance_globals_saved_d',go:'instance_globals_o'})[name],env.requireGlobal(name),field).at;
  assert.deepEqual(env.memory.readBytes(at,size),ref.HEAPU8.slice(Number(ref._probe_pointer(kind)),Number(ref._probe_pointer(kind))+size),label+' '+field);
 }
 assert.equal(Buffer.from(env.filesystem.readFile('/rng.log')).toString('latin1'),Buffer.from(ref.FS.readFile('/rng.log')).toString('latin1'),label+' actual RNG log');
 assert.equal(env.diagnostics.join(''),text(ref,ref._probe_diagnostics()),label+' diagnostics');
 assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);comparisons+=6;
}
function frame(env,fd,mode){const p=env.memory.calloc(1,S.nhfileSize),v=env.memory.view;v.setInt32(p+S.nhf_fd,fd,true);v.setInt32(p+B.nhf_fnidx,B.historical,true);v.setInt8(p+B.nhf_structlevel,1);v.setInt32(p+B.nhf_mode,mode,true);return p;}
const offset=(L.MAXOCLASSES+2)*4+L.NUM_OBJECTS*2;
for(const seed of [0n,1n,0x12345678n,0xffffffffffffffffn]){
 const env=create(seed),ref=await factory();ref._probe_init(seed);
 for(let i=0;i<ref._probe_layout_count();i++)assert.equal(L[text(ref,ref._probe_layout_name(i))],Number(ref._probe_layout_value(i)),'actual measured O_INIT layout');
 const act=(op,name,...args)=>{ref._probe_action(op,...[...args,0,0,0].slice(0,3));env.call('object-state',name,...args);state(env,ref,name);};
 act(0,'init_objects');act(1,'init_oclass_probs');act(2,'shuffle_all');act(3,'randomize_gem_colors');
 const lo=env.services.svb.bases[L.POTION_CLASS],hi=lo+3;
 for(const material of [-1,0,1,256,257])act(4,'shuffle',lo,hi,material);
 const a=env.memory.malloc(4),b=env.memory.malloc(4);
 for(let type=0;type<L.NUM_OBJECTS;type++){
  ref._probe_action(5,type,0,0);env.call('object-state','obj_shuffle_range',type,a,b);
  assert.equal(env.memory.view.getInt32(a,true),ref._probe_low());assert.equal(env.memory.view.getInt32(b,true),ref._probe_high());comparisons+=2;
 }
 env.memory.free(a);env.memory.free(b);
 for(const [dnum,dlevel]of [[0,1],[0,27],[1,3],[1,20],[1,25]]){
  ref._probe_action(8,dnum,dlevel,0);env.services.u.uz.dnum=dnum;env.services.u.uz.dlevel=dlevel;act(6,'oinit');
 }
 act(7,'setgemprobs',0);
 // Description lookup and its null-object diagnostic use the real catalogue.
 const object=env.memory.calloc(1,L.objectSize),type=L.POT_HEALING;
 env.ctypes.setField('struct obj',object,'otyp','short',type);
 const descriptorIndex=env.ctypes.getField('struct objclass',env.requireGlobal('objects')+type*L.objectClassSize,'oc_descr_idx','short');
 const description=env.ctypes.getField('struct objdescr',env.requireGlobal('obj_descr')+descriptorIndex*L.descriptorSize,'oc_descr','char *');
 for(const [item,value]of [[type,env.memory.readString(Number(description))],[type,'wrong description'],[-1,'']]){
  const bytes=Buffer.from(value+'\0','latin1'),p=ref._malloc(BigInt(bytes.length));ref.HEAPU8.set(bytes,Number(p));
  const expected=ref._probe_descr(item,BigInt(p));ref._free(BigInt(p));
  env.memory.withScope(scope=>assert.equal(env.call('object-state','objdescr_is',item<0?0:object,scope.cstring(value)),expected));comparisons++;
 }
 env.memory.free(object);state(env,ref,'description lookup');
 // Defined failure/recovery branch: zero probability class is repaired by
 // original init_oclass_probs, including its diagnostic and scalar truncation.
 const first=env.services.svb.bases[L.VENOM_CLASS],last=env.services.svb.bases[L.VENOM_CLASS+1];
 for(let i=first;i<last;i++){ref._probe_action(9,i,0,0);env.ctypes.setField('struct objclass',env.requireGlobal('objects')+i*L.objectClassSize,'oc_prob','short',0);}
 act(1,'init_oclass_probs');
 // A nonempty, empty and high-byte name test allocation/pointer ownership.
 for(const [type,value]of [[L.POT_HEALING,'called\x80name'],[L.SCR_IDENTIFY,''],[L.DIAMOND,'diamond']]){
  const ptr=env.memory.cstring(value);env.ctypes.setField('struct objclass',env.requireGlobal('objects')+type*L.objectClassSize,'oc_uname','char *',ptr);
  const bytes=Buffer.from(value+'\0','latin1'),p=ref._malloc(BigInt(bytes.length));ref.HEAPU8.set(bytes,Number(p));ref._probe_name(type,BigInt(p));ref._free(BigInt(p));
 }
 const original=rows(env),fd=env.services.open('/names',578,0o600),fp=frame(env,fd,B.WRITING|B.FREEING);
 env.call('object-state','savenames',fp);env.call('sfstruct','bclose',fd);env.memory.free(fp);ref._probe_save(B.WRITING|B.FREEING);
 const saved=env.filesystem.readFile('/names');assert.deepEqual(normalized(saved,offset),normalized(ref.FS.readFile('/names'),offset),'combined actual C serialization');comparisons++;
 state(env,ref,'save and release');
 const input=env.services.open('/names',0),rf=frame(env,input,0);env.call('object-state','restnames',rf);env.call('sfstruct','bclose',input);env.memory.free(rf);ref._probe_restore();
 assert.deepEqual(rows(env),original,'name-state restore');state(env,ref,'restored names');
 for(let type=0;type<L.NUM_OBJECTS;type++){
  const ptr=env.ctypes.getField('struct objclass',env.requireGlobal('objects')+type*L.objectClassSize,'oc_uname','char *');
  assert.equal(ptr?env.memory.readString(Number(ptr)):null,text(ref,ref._probe_get_name(type)));comparisons++;
 }
 // Continued RNG draws prove stream position, not only shuffled output.
 for(const n of [2,3,17,1000,2147483647]){assert.equal(env.services.rn2(n),ref._probe_next(n));comparisons++;}
 state(env,ref,'continued stream');
 // Run the full production group with Wasm/network forbidden before import in
 // the separate isolation suite; this differential process uses C only here.
 assert.ok(env.memory.generation>0);
}
console.log(`PASS: ${comparisons} combined original-C object startup/name-save comparisons; actual canonical RNG/logs, shared dungeon ledger, catalogues, SFBASE/SFSTRUCT and files; 11 O_INIT functions, no discovery UI claim.`);
