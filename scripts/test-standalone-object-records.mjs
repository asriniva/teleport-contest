import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/standalone/environment.js';
import {C,R,T} from '../js/ported/c-runtime.js';
const directory=path.resolve(process.env.STANDALONE_OBJECT_RECORDS_ORACLE||'.cache/standalone-object-records');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json')));
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const [p,h]of Object.entries(receipt.sourceSha256))assert.equal(sha(p),h,'Changed original-C input '+p);
for(const [p,h]of Object.entries(receipt.artifactSha256))assert.equal(sha(path.join(directory,p)),h,'Changed original-C oracle '+p);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs')));
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L=layouts.mkobj,O=layouts.o_init;
const metadata=JSON.parse(fs.readFileSync('js/standalone/records.json')).records;
const env=createStandaloneEnvironment({initialBytes:1024,maximumBytes:64*1024*1024,environment:{NETHACK_RNGLOG:'/rng.log'}});
env.enableStdio();env.enableDecl(layouts.decl);env.enableDrawing(layouts.drawing);env.enableObjects(layouts.objects);env.call('objects','objects_globals_init');
env.enableMonst(layouts.monst);env.call('monst','monst_globals_init');env.enableSerialization(layouts);env.enableRnd(layouts.rnd,{seed:0x12345678n});env.call('rnd','rng_log_init');
env.enableAddressPort('dungeon',{only:['ledger_no','maxledgerno']});env.enableObjectState(layouts);env.call('object-state','init_objects');
const component=env.enableObjectRecords(layouts);assert.equal(component.exports.length,21);assert.equal(env.hasFunction('mksobj'),false);assert.equal(typeof env.resolve('mksobj'),'function');assert.throws(()=>env.resolve('nhl_init'),/Unresolved/);
const ref=await factory();ref._probe_init(0x12345678n);ref._probe_record_prepare();ref._probe_action(0,0,0,0);
env.services.svc.context.current_fruit=19;
const {memory,ctypes}=env,js=[],native=[],heads=Array.from({length:4},()=>memory.calloc(1,8));let comparisons=0;
const fields=(type,key)=>{const f=metadata[type].fields[key];assert.ok(f,type+'.'+key);return f;};
const nativeRead=(type,p,key,scalar)=>{
 const f=fields(type,key),at=Number(p)+f.offset,dv=new DataView(ref.HEAPU8.buffer);
 if(f.bits!==undefined){let n=0n;for(let i=0;i<Math.ceil((f.shift+f.bits)/8);i++)n|=BigInt(ref.HEAPU8[at+i])<<BigInt(8*i);return Number(n>>BigInt(f.shift)&((1n<<BigInt(f.bits))-1n));}
 return dv['get'+scalar](at,true);
};
const nativeWrite=(type,p,key,scalar,v)=>{
 const f=fields(type,key),at=Number(p)+f.offset,dv=new DataView(ref.HEAPU8.buffer);
 if(f.bits!==undefined){let n=0n;const count=Math.ceil((f.shift+f.bits)/8),mask=((1n<<BigInt(f.bits))-1n)<<BigInt(f.shift);for(let i=0;i<count;i++)n|=BigInt(ref.HEAPU8[at+i])<<BigInt(8*i);n=n&~mask|BigInt(v)<<BigInt(f.shift)&mask;for(let i=0;i<count;i++)ref.HEAPU8[at+i]=Number(n>>BigInt(i*8)&255n);}
 else dv['set'+scalar](at,scalar.startsWith('Big')?BigInt(v):Number(v),true);
};
const scalarMap={Int8:'char',Int16:'short',Int32:'int',Uint32:'unsigned int',BigInt64:'long',BigUint64:'void *'};
function set(i,key,scalar,value){ctypes.setField('struct obj',js[i],key,scalarMap[scalar],value);nativeWrite('obj',native[i],key,scalar,value);}
function ptr(i,key,target){ctypes.setField('struct obj',js[i],key,'void *',target<0?0:js[target]);nativeWrite('obj',native[i],key,'BigUint64',target<0?0:native[target]);}
function union(i,target){const a=ctypes.locate('struct obj',js[i],'v').at,b=Number(native[i])+fields('obj','v').offset;memory.view.setBigUint64(a,BigInt(target<0?0:js[target]),true);new DataView(ref.HEAPU8.buffer).setBigUint64(b,BigInt(target<0?0:native[target]),true);}
const string=(m,p)=>{if(!p)return null;let end=Number(p);while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(Number(p),end)).toString('latin1');};
function token(p,list){p=Number(p);if(!p)return 0;const i=list.findIndex(q=>Number(q)===p);assert.ok(i>=0,'Unexpected object pointer '+p);return i+1;}
function snapshot(m,list){
 const dv=new DataView(m.HEAPU8.buffer),read=(t,p,k,s)=>m===memory?ctypes.getField('struct '+t,p,k,scalarMap[s]):nativeRead(t,p,k,s);
 return list.map(p=>{if(!p)return null;
  const bytes=Buffer.from(m.HEAPU8.slice(Number(p),Number(p)+metadata.obj.size));
  for(const key of ['nobj','v','cobj']){const at=fields('obj',key).offset;bytes.writeBigUInt64LE(BigInt(token(dv.getBigUint64(Number(p)+at,true),list)),at);}
  const extra=Number(read('obj',p,'oextra','BigUint64'));bytes.writeBigUInt64LE(extra?1n:0n,fields('obj','oextra').offset);
  let info=null;
  if(extra){
   const monster=Number(read('oextra',extra,'omonst','BigUint64'));let mon=null;
   if(monster){const b=Buffer.from(m.HEAPU8.slice(monster,monster+metadata.monst.size)),mx=Number(read('monst',monster,'mextra','BigUint64'));b.writeBigUInt64LE(mx?1n:0n,fields('monst','mextra').offset);
    const x=mx?Buffer.from(m.HEAPU8.slice(mx,mx+metadata.mextra.size)):null;
    if(x)for(const key of ['mgivenname','egd','epri','eshk','emin','edog','ebones']){const at=fields('mextra',key).offset;x.writeBigUInt64LE(x.readBigUInt64LE(at)?1n:0n,at);}
    mon={bytes:b,extra:x};}
   info={name:string(m,read('oextra',extra,'oname','BigUint64')),mail:string(m,read('oextra',extra,'omailcmd','BigUint64')),id:read('oextra',extra,'omid','Uint32'),monster:mon};
  }
  return{bytes,extra:info};
 });
}
function check(label){assert.deepEqual(snapshot(memory,js),snapshot(ref,native),label);for(let i=0;i<heads.length;i++)assert.equal(token(memory.view.getBigUint64(heads[i],true),js),token(new DataView(ref.HEAPU8.buffer).getBigUint64(Number(ref._probe_record_head(i)),true),native),label+' head');assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);comparisons++;}
function create(i,type,quantity=1n){assert.ok(!js[i]);js[i]=memory.malloc(metadata.obj.size);assert.equal(env.call('mkobj','init_dummyobj',js[i],type,quantity),js[i]);native[i]=BigInt(ref._probe_record_new(i,type,quantity));check('init_dummyobj');}
const operations={init_oextra:1,dealloc_oextra:2,newomonst:3,free_omonst:4,newomid:5,free_omid:6,free_omailcmd:7,weight:8,container_weight:9,extract_nobj:10,extract_nexthere:11,add_to_buried:12,bcsign:13,next_ident:14,is_flammable:15,is_rottable:16,is_treefruit:17,dealloc_obj_real:18};
function op(name,i=0,arg=0){let args=[js[i]];if(name==='init_oextra')args=[Number(ctypes.getField('struct obj',js[i],'oextra','void *'))];if(name==='next_ident')args=[];if(name==='extract_nobj'||name==='extract_nexthere')args.push(heads[arg]);const expected=ref._probe_record_op(operations[name],i,arg),actual=env.call('mkobj',name,...args);if(['weight','bcsign','next_ident','is_flammable','is_rottable','is_treefruit'].includes(name)){assert.equal(BigInt(actual),expected,name);comparisons++;}if(name==='dealloc_obj_real'){assert.ok(!memory.live.has(js[i]));js[i]=native[i]=0;}check(name);return actual;}
// Every catalogue type exercises source initialization, material/fruit predicates
// and normal positive-quantity weight. Integer narrowing remains target-specific.
for(let type=0;type<O.NUM_OBJECTS;type++){
 create(0,type);op('weight');op('is_flammable');op('is_rottable');op('is_treefruit');op('bcsign');op('dealloc_obj_real');
}
// Corpse/statue weight uses the actual shared monster catalogue; partial food
// calls the original EAT functions, including their clamp diagnostic branch.
for(const type of [L.CORPSE,L.STATUE,L.APPLE,O.POT_HEALING,L.HEAVY_IRON_BALL,L.CANDELABRUM_OF_INVOCATION]){
 create(0,type,17n);
 for(const pm of [0,1,100,L.NUMMONS-1])for(const eaten of [0,1,17,0xffffffff]){
  set(0,'corpsenm','Int32',pm);set(0,'oeaten','Uint32',eaten);set(0,'owt','Uint32',357);set(0,'spe','Int8',5);op('weight');
  if(type===L.CORPSE||type===L.APPLE){
   assert.equal(BigInt(env.call('object-nutrition','obj_nutrition',js[0])),BigInt.asUintN(32,BigInt(ref._obj_nutrition(native[0]))));comparisons++;
   assert.equal(BigInt(env.call('object-nutrition','eaten_stat',357,js[0])),BigInt(ref._eaten_stat(357,native[0])));comparisons++;
  }
 }
 op('dealloc_obj_real');
}
create(0,L.GOLD_PIECE);
for(const quantity of [1n,49n,50n,51n,99n,100n,101n,149n,150n,151n,1000000000000n]){set(0,'quan','BigInt64',quantity);op('weight');}
op('dealloc_obj_real');create(0,L.APPLE);set(0,'globby','Uint32',1);
for(const wt of [0,1,357,0xffffffff]){set(0,'owt','Uint32',wt);op('weight');assert.equal(BigInt(env.call('object-nutrition','obj_nutrition',js[0])),BigInt.asUintN(32,BigInt(ref._obj_nutrition(native[0]))));comparisons++;}
op('dealloc_obj_real');
create(0,L.BAG_OF_HOLDING);create(1,L.LARGE_BOX);create(2,L.APPLE,7n);create(3,L.GOLD_PIECE,101n);
ptr(0,'cobj',1);ptr(1,'cobj',2);ptr(2,'nobj',3);union(1,0);union(2,1);union(3,1);for(const i of [1,2,3])set(i,'where','Int8',2);
for(const blessed of [0,1])for(const cursed of [0,1]){set(0,'blessed','Uint32',blessed);set(0,'cursed','Uint32',cursed);op('weight');op('container_weight',2);}
// Alias-preserving nobj and nexthere extraction, including head/middle/tail.
for(const order of [[2,1,3],[3,2,1]]){
 for(let i=0;i<order.length;i++){ptr(order[i],'nobj',i+1<order.length?order[i+1]:-1);union(order[i],i+1<order.length?order[i+1]:-1);}
 memory.view.setBigUint64(heads[0],BigInt(js[order[0]]),true);memory.view.setBigUint64(heads[1],BigInt(js[order[0]]),true);
 for(const h of [0,1])new DataView(ref.HEAPU8.buffer).setBigUint64(Number(ref._probe_record_head(h)),native[order[0]],true);
 for(const i of [1,2,3]){op('extract_nobj',i,0);op('extract_nexthere',i,1);}
}
ptr(0,'cobj',-1);ptr(1,'cobj',-1);for(const i of [1,2,3]){set(i,'where','Int8',0);op('add_to_buried',i);}
const buried=ctypes.locate('dlevel_t',ctypes.locate('struct instance_globals_saved_l',env.requireGlobal('svl'),'level').at,'buriedobjlist').at;
assert.equal(token(memory.view.getBigUint64(buried,true),js),token(new DataView(ref.HEAPU8.buffer).getBigUint64(Number(ref._probe_record_global(1))+fields('dlevel_t','buriedobjlist').offset,true),native));comparisons++;
// Lifetime and idempotence of nested extra data, command strings and monster
// extras. Every owned payload must be freed once by the original source.
const extra=env.call('mkobj','newoextra');ctypes.setField('struct obj',js[0],'oextra','void *',extra);ref._probe_record_op(0,0,0);check('newoextra');
const cextra=nativeRead('obj',native[0],'oextra','BigUint64');memory.memset(extra,165,metadata.oextra.size);ref.HEAPU8.fill(165,Number(cextra),Number(cextra)+metadata.oextra.size);
op('init_oextra');op('newomid');op('newomid');op('free_omid');
for(const value of ['','mail\x80command','replacement']){
 memory.withScope(scope=>env.call('mkobj','new_omailcmd',js[0],scope.cstring(value)));
 const bytes=Buffer.from(value+'\0','latin1'),p=ref._malloc(BigInt(bytes.length));ref.HEAPU8.set(bytes,Number(p));ref._probe_record_mail(0,BigInt(p));ref._free(BigInt(p));check('new_omailcmd');
}
op('free_omailcmd');op('free_omailcmd');op('newomonst');const count=memory.live.size;op('newomonst');assert.equal(memory.live.size,count);
const monster=Number(ctypes.getField('struct oextra',extra,'omonst','void *')),cmonster=BigInt(nativeRead('oextra',nativeRead('obj',native[0],'oextra','BigUint64'),'omonst','BigUint64'));
function attach(){const p=memory.calloc(1,metadata.mextra.size),q=BigInt(ref._malloc(BigInt(metadata.mextra.size)));ref.HEAPU8.fill(0,Number(q),Number(q)+metadata.mextra.size);ctypes.setField('struct monst',monster,'mextra','void *',p);nativeWrite('monst',cmonster,'mextra','BigUint64',q);const owned=[p];for(const field of ['mgivenname','egd','epri','eshk','emin','edog','ebones']){const a=memory.calloc(1,8),b=BigInt(ref._malloc(8n));ref.HEAPU8.fill(0,Number(b),Number(b)+8);ctypes.setField('struct mextra',p,field,'void *',a);nativeWrite('mextra',q,field,'BigUint64',b);owned.push(a);}return owned;}
let owned=attach();check('nested mextra');env.call('monster-extra','dealloc_mextra',monster);ref._dealloc_mextra(cmonster);check('dealloc_mextra');for(const p of owned)assert.ok(!memory.live.has(p));
env.call('monster-extra','dealloc_mextra',monster);ref._dealloc_mextra(cmonster);check('empty mextra');
owned=attach();op('free_omonst');for(const p of [...owned,monster])assert.ok(!memory.live.has(p));op('free_omonst');
// Source dealloc_obj_real owns the entire remaining graph, including oname
// and command bytes, and must clear/deallocate every live allocation once.
const name=memory.cstring('owned\x80name'),nameBytes=Buffer.from('owned\x80name\0','latin1'),cname=BigInt(ref._malloc(BigInt(nameBytes.length)));ref.HEAPU8.set(nameBytes,Number(cname));
ctypes.setField('struct oextra',extra,'oname','void *',name);nativeWrite('oextra',cextra,'oname','BigUint64',cname);check('owned name');
op('newomonst');const ownedMonster=Number(ctypes.getField('struct oextra',extra,'omonst','void *'));
op('dealloc_obj_real');for(const p of [extra,name,ownedMonster])assert.ok(!memory.live.has(p));
op('dealloc_oextra',1);
// ID overflow crosses UINT_MAX using the real shared RND implementation.
const context=ctypes.locate('struct instance_globals_saved_c',env.requireGlobal('svc'),'context').at;
for(const id of [1,0xfffffffe,0xffffffff]){ctypes.setField('struct context_info',context,'ident','unsigned int',id);nativeWrite('context_info',ref._probe_record_global(0),'ident','Uint32',id);for(let i=0;i<8;i++)op('next_ident');assert.equal(ctypes.getField('struct context_info',context,'ident','unsigned int'),nativeRead('context_info',ref._probe_record_global(0),'ident','Uint32'));comparisons++;}
assert.equal(env.diagnostics.join(''),string(ref,ref._probe_diagnostics()));assert.equal(Buffer.from(env.filesystem.readFile('/rng.log')).toString('latin1'),Buffer.from(ref.FS.readFile('/rng.log')).toString('latin1'));comparisons+=2;
assert.ok(memory.generation>0);
console.log(`PASS: ${comparisons} original-C object-record/nutrition/ownership/container/list/ID comparisons with real shared catalogues and RNG; 21 MKOBJ + 2 EAT + 1 MON functions, full generation/UI unlinked.`);
