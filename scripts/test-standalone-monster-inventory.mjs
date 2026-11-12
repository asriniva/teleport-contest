import {layoutSourceSha} from './nethack-layout.mjs';
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {C,R,T} from '../js/c-runtime/context.js';
const directory=path.resolve(process.env.STANDALONE_MONSTER_CREATION_ORACLE||'.cache/standalone-monster-creation');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json')));
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const [p,h]of Object.entries(receipt.sourceSha256))assert.equal(layoutSourceSha(p,h),h,'Changed C source '+p);
for(const [p,h]of Object.entries(receipt.artifactSha256))assert.equal(sha(path.join(directory,p)),h,'Changed C artifact '+p);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs')));
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L=layouts.makemon,M=layouts.mkobj;
const metadata=JSON.parse(fs.readFileSync('js/nethack/records.json')).records;
let comparisons=0;
for(const seed of [1n,0x12345678n,0xffffffffffffffffn]){
 const env=createStandaloneEnvironment({initialBytes:1024,maximumBytes:64*1024*1024,environment:{NETHACK_RNGLOG:'/rng.log'}}),ref=await factory();
 env.enableStdio();env.enableDecl(layouts.decl);env.enableDrawing(layouts.drawing);env.enableObjects(layouts.objects);env.call('objects','objects_globals_init');env.enableMonst(layouts.monst);env.call('monst','monst_globals_init');env.enableSerialization(layouts);env.enableRnd(layouts.rnd,{seed});env.call('rnd','rng_log_init');env.enableAddressPort('dungeon',{only:['ledger_no','maxledgerno']});env.enableObjectState(layouts);env.call('object-state','init_objects');env.enableObjectRecords(layouts);env.services.svc.context.ident=2;env.services.svc.context.current_fruit=19;env.enableItemInventory(layouts);env.enableTimers(layouts);env.enableItemNaming(layouts);const group=env.enableMonsterSelection(layouts);const decl=JSON.parse(fs.readFileSync('js/nethack/decl-storage.json')).globals,before=decl.map(r=>env.memory.readBytes(env.requireGlobal(r.name),r.bytes));const creation=env.enableMonsterCreation(layouts);decl.forEach((r,i)=>assert.deepEqual(env.memory.readBytes(env.requireGlobal(r.name),r.bytes),before[i],'enabling creation preserves '+r.name));env.enableMonsterInventory(layouts);
 ref._probe_init(seed);ref._probe_item_prepare();ref._probe_action(0,0,0,0);ref._probe_monster_prepare();
 const {ctypes,memory}=env,c=group.environment;
 function config(level,depth,align,temperature,hell,plane=0){
  ref._probe_species_config(level,depth,align,temperature,hell,plane);
  // Exercise the original per-turn cached special-level lookup, beginning
  // with the game's nonzero move counter rather than a zero-only fixture.
  const moves=ctypes.locate('struct instance_globals_saved_m',env.requireGlobal('svm'),'moves').at;
  const turn=memory.view.getBigInt64(moves,true)+1n;memory.view.setBigInt64(moves,turn,true);
  new DataView(ref.HEAPU8.buffer).setBigInt64(Number(ref._probe_timer_global(2)),turn,true);
  ctypes.setField('struct instance_globals_saved_n',env.requireGlobal('svn'),'n_dgns','int',3);
  const t=c.svd.dungeon_topology;t.d_quest_dnum=1;t.d_astral_level.dnum=2;t.d_astral_level.dlevel=5;t.d_sanctum_level.dnum=0;t.d_sanctum_level.dlevel=25;
  for(const [name,n]of [['air',1],['fire',2],['water',3],['earth',4]]){t['d_'+name+'_level'].dnum=2;t['d_'+name+'_level'].dlevel=n;}
  for(let i=0;i<3;i++){const d=c.svd.dungeons[i];d.num_dunlevs=30;d.entry_lev=1;d.depth_start=1;d.flags.align=align;d.flags.hellish=hell;}
  c.u.ulevel=level;c.u.uz.dnum=plane?2:0;c.u.uz.dlevel=plane||depth;c.svl.level.flags.temperature=temperature;
 }
 config(10,5,L.AM_NONE,0,0);
 const world=creation.environment;world.gi.in_mklev=1;world.svl.level.flags.rndmongen=1;
 world.u.ux=40;world.u.uy=10;world.u.ualign.type=L.A_NEUTRAL;world.u.ualign.record=10;
 world.gu.urace.mnum=L.PM_HUMAN;world.gu.urace.hatemask=BigInt(L.M2_ORC);world.gu.urace.lovemask=BigInt(L.M2_HUMAN);
 for(let x=0;x<L.COLNO;x++)for(let y=0;y<L.ROWNO;y++)world.levl[x][y].typ=L.ROOM;
 const rows=memory.calloc(L.ROWNO,8),cells=memory.calloc(L.ROWNO,L.COLNO);for(let y=0;y<L.ROWNO;y++)memory.view.setBigUint64(rows+y*8,BigInt(cells+y*L.COLNO),true);world.gv.viz_array=rows;
 const read=(heap,p,field,method)=>new DataView(heap.buffer)[method](Number(p)+metadata.monst.fields[field].offset,true);
 function monster(heap,p,isJS){
  if(!p)return null;p=Number(p);const bytes=Buffer.from(heap.slice(p,p+metadata.monst.size)),data=read(heap,p,'data','getBigUint64'),pm=new DataView(heap.buffer).getInt32(Number(data)+metadata.permonst.fields.pmidx.offset,true);
  if(isJS)assert.equal(Number(data),env.requireGlobal('mons')+pm*metadata.permonst.size);
  bytes.writeBigUInt64LE(BigInt(pm+1),metadata.monst.fields.data.offset);
  for(const key of ['nmon','mw'])assert.equal(read(heap,p,key,'getBigUint64'),0n,'initial profile has no hidden '+key+' on '+(isJS?'JS':'C'));
  const ep=Number(read(heap,p,'mextra','getBigUint64'));bytes.writeBigUInt64LE(ep?1n:0n,metadata.monst.fields.mextra.offset);
  const inventory=[];const addresses=[],ids=new Map();
  function visit(at){at=Number(at);if(!at||ids.has(at))return;ids.set(at,ids.size+1);addresses.push(at);const dv=new DataView(heap.buffer);visit(dv.getBigUint64(at+metadata.obj.fields.cobj.offset,true));visit(dv.getBigUint64(at+metadata.obj.fields.nobj.offset,true));}
  visit(read(heap,p,'minvent','getBigUint64'));bytes.writeBigUInt64LE(addresses.length?1n:0n,metadata.monst.fields.minvent.offset);
  for(const at of addresses){const b=Buffer.from(heap.slice(at,at+metadata.obj.size));for(const key of ['nobj','v','cobj']){const o=metadata.obj.fields[key].offset,q=Number(b.readBigUInt64LE(o));assert.ok(!q||q===p||ids.has(q),'object/carrier identity');b.writeBigUInt64LE(BigInt(!q?0:q===p?0xffffffff:ids.get(q)),o);}const xp=Number(b.readBigUInt64LE(metadata.obj.fields.oextra.offset));b.writeBigUInt64LE(xp?1n:0n,metadata.obj.fields.oextra.offset);let extra=null,name=null;if(xp){extra=Buffer.from(heap.slice(xp,xp+metadata.oextra.size));const np=Number(extra.readBigUInt64LE(metadata.oextra.fields.oname.offset));extra.writeBigUInt64LE(np?1n:0n,metadata.oextra.fields.oname.offset);if(np){let end=np;while(heap[end])end++;name=Buffer.from(heap.slice(np,end)).toString('latin1');}for(const key of ['omonst','omailcmd'])assert.equal(extra.readBigUInt64LE(metadata.oextra.fields[key].offset),0n,'all extra ownership accounted for');}inventory.push({bytes:b,extra,name});}
  let extra=null,children={};if(ep){extra=Buffer.from(heap.slice(ep,ep+metadata.mextra.size));for(const [key,f]of Object.entries(metadata.mextra.fields))if(f.ctype.includes('*')){const child=Number(extra.readBigUInt64LE(f.offset));extra.writeBigUInt64LE(child?1n:0n,f.offset);if(child){assert.ok(metadata[key],'known extra type '+key);children[key]=Buffer.from(heap.slice(child,child+metadata[key].size));}}}
  return {bytes,extra,children,inventory};
 }
 const names=['PM_GIANT_ANT','PM_KITTEN','PM_GNOME','PM_ORC','PM_HUMAN','PM_GRID_BUG','PM_LEPRECHAUN','PM_WOOD_NYMPH','PM_YELLOW_LIGHT','PM_FIRE_ELEMENTAL','PM_GOLD_DRAGON','PM_STRAW_GOLEM','PM_IRON_GOLEM','PM_DEATH','PM_ANGEL','PM_ALIGNED_CLERIC','PM_HIGH_CLERIC','PM_WIZARD_OF_YENDOR'];
 for(const name of names)for(const extraFlags of [0,L.MM_FEMALE|L.MM_ANGRY|L.MM_ASLEEP,L.MM_MALE|L.MM_NOCOUNTBIRTH,L.MM_EDOG,L.MM_EMIN,L.MM_EPRI,L.MM_EGD,L.MM_ESHK]){
  const values=Object.values(layouts).filter(v=>v&&Object.hasOwn(v,name)).map(v=>Number(v[name]));assert.ok(values.length,name);assert.equal(new Set(values).size,1,name);const type=values[0];
  const flags=L.MM_NOGRP|L.MM_NONAME|L.MM_NOMSG|extraFlags;
  assert.equal(env.address(world.fmon),0,'list starts empty '+name+' '+extraFlags);
  const p=env.services.makemon(env.requireGlobal('mons')+type*metadata.permonst.size,10,10,flags),q=ref._probe_monster_create(type,10,10,flags);
  assert.ok(p&&q,name);const a=monster(memory.HEAPU8,p,true),b=monster(ref.HEAPU8,q,false);if(!a.bytes.equals(b.bytes))console.error(JSON.stringify({name,diff:[...a.bytes.keys()].filter(i=>a.bytes[i]!==b.bytes[i]).map(i=>({offset:i,js:a.bytes[i],c:b.bytes[i]})),jsObjects:a.inventory.length,cObjects:b.inventory.length}));assert.deepEqual(a,b,name+' full monster');comparisons++;
  assert.equal(env.address(world.fmon),env.address(p));assert.equal(env.address(world.svl.level.monsters[10][10]),env.address(p));
  const offset=ctypes.locate('struct instance_globals_saved_m',env.requireGlobal('svm'),'mvitals').at-env.requireGlobal('svm'),size=metadata.mvitals.size*L.NUMMONS;
  assert.deepEqual(memory.readBytes(env.requireGlobal('svm')+offset,size),ref.HEAPU8.slice(Number(ref._probe_monster_global(1))+offset,Number(ref._probe_monster_global(1))+offset+size));comparisons++;
  const source=world.gl.light_base;
  const co=ctypes.locate('struct instance_globals_l',env.requireGlobal('gl'),'light_base').at-env.requireGlobal('gl'),cs=new DataView(ref.HEAPU8.buffer).getBigUint64(Number(ref._probe_monster_global(6))+co,true);
  assert.equal(Boolean(source),Boolean(cs));if(source){const light=(heap,at,mon)=>{const b=Buffer.from(heap.slice(Number(at),Number(at)+metadata.ls_t.size));assert.equal(b.readBigUInt64LE(metadata.ls_t.fields.id.offset),BigInt(env.address(mon)));b.writeBigUInt64LE(1n,metadata.ls_t.fields.id.offset);return b;};assert.deepEqual(light(memory.HEAPU8,source.address,p),light(ref.HEAPU8,cs,q));env.services.del_light_source(layouts.light.LS_MONSTER,env.services.monst_to_any(p));}comparisons++;
  env.services.discard_minvent(p,0);env.services.dobjsfree();
  world.svl.level.monsters[10][10]=0;world.fmon=0;assert.equal(env.address(world.fmon),0,'teardown clears list');env.services.dealloc_monst(p);assert.equal(env.address(world.fmon),0,'free preserves cleared list');ref._probe_monster_dispose();assert.ok(!memory.live.has(env.address(p)));
 }
 const actualLog=Buffer.from(env.filesystem.readFile('/rng.log')).toString('latin1').split('\n'),expectedLog=Buffer.from(ref.FS.readFile('/rng.log')).toString('latin1').split('\n');
 assert.equal(actualLog.length,expectedLog.length,'RNG log length');for(let i=0;i<actualLog.length;i++)assert.equal(actualLog[i],expectedLog[i],'RNG log '+i);comparisons++;
 assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);
}
console.log(`PASS: ${comparisons} original-C monster inventory/equipment/construction comparisons and RNG logs; map generation with normal inventory enabled. Other world paths remain under integration.`);
