import {layoutSourceSha} from './nethack-layout.mjs';
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {C,R,T} from '../js/c-runtime/context.js';
const directory=path.resolve(process.env.STANDALONE_WORLD_POSITION_ORACLE||'.cache/standalone-world-position');
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
 env.enableStdio();env.enableDecl(layouts.decl);env.enableDrawing(layouts.drawing);env.enableObjects(layouts.objects);env.call('objects','objects_globals_init');env.enableMonst(layouts.monst);env.call('monst','monst_globals_init');env.enableSerialization(layouts);env.enableRnd(layouts.rnd,{seed});env.call('rnd','rng_log_init');env.enableAddressPort('dungeon',{only:['ledger_no','maxledgerno']});env.enableObjectState(layouts);env.call('object-state','init_objects');env.enableObjectRecords(layouts);env.services.svc.context.ident=2;env.services.svc.context.current_fruit=19;env.enableItemInventory(layouts);env.enableTimers(layouts);env.enableItemNaming(layouts);const group=env.enableMonsterSelection(layouts);const decl=JSON.parse(fs.readFileSync('js/nethack/decl-storage.json')).globals,before=decl.map(r=>env.memory.readBytes(env.requireGlobal(r.name),r.bytes));const creation=env.enableMonsterCreation(layouts);decl.forEach((r,i)=>assert.deepEqual(env.memory.readBytes(env.requireGlobal(r.name),r.bytes),before[i],'enabling creation preserves '+r.name));env.enableWorldPosition(layouts);
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
 assert.equal(ref._probe_position_debug(),1,'configured DEBUG-on original header profile');
 const constants=name=>{const values=Object.values(layouts).filter(v=>v&&Object.hasOwn(v,name)).map(v=>Number(v[name]));assert.ok(values.length,name);assert.equal(new Set(values).size,1,name);return values[0];};
 const fake=memory.calloc(1,metadata.monst.size),coord=memory.calloc(1,metadata.nhcoord.size);
 const types=['PM_GIANT_ANT','PM_GIANT_EEL','PM_AIR_ELEMENTAL','PM_FLOATING_EYE','PM_FIRE_ELEMENTAL','PM_GHOST','PM_XORN','PM_ACID_BLOB','PM_MINOTAUR','PM_VAMPIRE','PM_ANGEL','PM_HUMAN'].map(constants);
 const gp=['NO_MM_FLAGS','GP_CHECKSCARY','MM_IGNOREWATER','MM_IGNORELAVA','GP_AVOID_MONPOS','GP_ALLOW_U'].map(constants);
 const terrains=[['ROOM',0],['STONE',0],['POOL',0],['MOAT',0],['WATER',0],['LAVAPOOL',0],['LAVAWALL',0],['DOOR',constants('D_CLOSED')],['DOOR',constants('D_ISOPEN')],['ALTAR',0],['DRAWBRIDGE_UP',constants('DB_LAVA')],['DRAWBRIDGE_UP',constants('DB_MOAT')]];
 for(const[type,flags]of terrains){world.levl[10][10].typ=constants(type);world.levl[10][10].flags=flags;ref._probe_position_cell(10,10,constants(type),flags);
  for(const pm of types){ctypes.setField('struct monst',fake,'data','struct permonst *',env.requireGlobal('mons')+pm*metadata.permonst.size);for(const flags of gp){assert.equal(env.services.goodpos(10,10,fake,flags),ref._probe_position_good(pm,10,10,flags),'goodpos '+[type,pm,flags]);comparisons++;}}
 }
 world.levl[10][10].typ=constants('ROOM');world.levl[10][10].flags=0;ref._probe_position_cell(10,10,constants('ROOM'),0);
 const out=memory.calloc(L.ROWNO*(L.COLNO-1),metadata.nhcoord.size),P=layouts.teleport;
 for(const[x,y]of [[40,10],[1,0],[79,20]])for(const radius of [1,3,0])for(const flags of [P.CC_UNSHUFFLED,0,P.CC_RING_PAIRS,P.CC_UNSHUFFLED|P.CC_INCL_CENTER,P.CC_SKIP_MONS|P.CC_SKIP_INACCS]){
  const n=env.services.collect_coords(out,x,y,radius,flags,0),expected=ref._probe_position_collect(x,y,radius,flags);assert.equal(n,expected,'collect count');
  const cp=Number(ref._probe_position_coords());assert.deepEqual(memory.readBytes(out,n*metadata.nhcoord.size),ref.HEAPU8.slice(cp,cp+n*metadata.nhcoord.size),'ordered/shuffled coordinate bytes');comparisons++;
 }
 for(const pm of types)for(const[x,y]of [[40,10],[1,0],[79,20]]){
  const actual=env.services.enexto_core(coord,x,y,env.requireGlobal('mons')+pm*metadata.permonst.size,P.GP_CHECKSCARY),expected=ref._probe_position_near(pm,x,y,P.GP_CHECKSCARY);assert.equal(actual,expected,'near return');const cp=Number(ref._probe_position_coords());assert.deepEqual(memory.readBytes(coord,metadata.nhcoord.size),ref.HEAPU8.slice(cp,cp+metadata.nhcoord.size),'near coordinate');comparisons++;
 }
 // Source debug guard: file lists, basenames, wildcard and explicit modes.
 const patterns=['','*','teleport.c','mon.c teleport.c','nope.c','tele*.c'],files=['/src/teleport.c','teleport.js','teleport.c',''];
 for(const wizard of [0,1])for(let pi=0;pi<patterns.length;pi++)for(let fi=0;fi<files.length;fi++)for(const wild of [0,1]){
  world.flags.debug=wizard;const sys=env.requireGlobal('sysopt');ctypes.setField('struct sysopt_s',sys,'debugfiles','char *',env.services.literal(patterns[pi]));
  assert.equal(env.services.debugcore(files[fi],wild),ref._probe_position_debug_match(wizard,pi,fi,wild),'source debug pattern');comparisons++;
 }
 world.flags.debug=0;ctypes.setField('struct sysopt_s',env.requireGlobal('sysopt'),'debugfiles','char *',0);
 // Actual mutable engravings, including replacement, future text and headstones.
 const engravingTexts=['Elbereth','elbereth','Elbereth test',''];
 function engraving(heap,p){if(!p)return null;p=Number(p);const b=Buffer.from(heap.slice(p,p+metadata.engr.size)),dv=new DataView(heap.buffer),texts=[];
  assert.equal(b.readBigUInt64LE(metadata.engr.fields.nxt_engr.offset),0n,'one engraving input');
  for(let i=0;i<3;i++){const at=metadata.engr.fields.engr_txt.offset+i*8,ptr=Number(b.readBigUInt64LE(at));let end=ptr;while(heap[end])end++;texts.push(Buffer.from(heap.slice(ptr,end)).toString('latin1'));b.writeBigUInt64LE(BigInt(ptr-p),at);}return {bytes:b,texts};
 }
 for(const type of [constants('DUST'),constants('HEADSTONE'),0])for(const text of [0,1,2,3])for(const when of [0n,100n]){
  env.services.make_engr_at(10,10,engravingTexts[text],0,when,type);const cp=ref._probe_position_engr(type,when,text),p=env.services.engr_at(10,10);
  assert.deepEqual(engraving(memory.HEAPU8,p),engraving(ref.HEAPU8,cp),'full engraving bytes/text state');comparisons++;
  for(const pm of types){ctypes.setField('struct monst',fake,'data','struct permonst *',env.requireGlobal('mons')+pm*metadata.permonst.size);assert.equal(env.services.goodpos(10,10,fake,P.GP_CHECKSCARY),ref._probe_position_good(pm,10,10,P.GP_CHECKSCARY),'scary engraving');comparisons++;}
 }
 env.services.del_engr_at(10,10);assert.equal(ref._probe_position_engr(-1,0n,0),0n);
 // Real exclusion and boulder queries over explicit input records.
 const zone=memory.calloc(1,metadata.exclusion_zone.size),z=creation.views.record('struct exclusion_zone',zone),sve=creation.views.record('struct instance_globals_saved_e',env.requireGlobal('sve'));
 z.zonetype=constants('LR_MONGEN');z.lx=z.ly=9;z.hx=z.hy=11;
 const boulder=memory.calloc(1,metadata.obj.size);ctypes.setField('struct obj',boulder,'otyp','short',constants('BOULDER'));
 for(const occupied of [0,1])for(const excluded of [0,1]){
  world.svl.level.objects[10][10]=occupied?creation.views.record('struct obj',boulder):0;ref._probe_position_object(occupied);sve.exclusion_zones=excluded?z:0;ref._probe_position_exclusion(excluded,z.zonetype);
  for(const pm of types){ctypes.setField('struct monst',fake,'data','struct permonst *',env.requireGlobal('mons')+pm*metadata.permonst.size);for(const flags of gp){assert.equal(env.services.goodpos(10,10,fake,flags),ref._probe_position_good(pm,10,10,flags),'object/exclusion input');comparisons++;}}
 }
 world.svl.level.objects[10][10]=0;ref._probe_position_object(0);sve.exclusion_zones=0;ref._probe_position_exclusion(0,0);memory.free(boulder);memory.free(zone);
 // The actual MAKEMON random-coordinate and group paths, with complete list
 // and map occupancy identities. These callers request no inventory.
 function monsterList(heap,first,mons){const list=[],ids=new Map(),dv=new DataView(heap.buffer);let p=Number(first);while(p){assert.ok(!ids.has(p),'acyclic monster list');ids.set(p,ids.size+1);list.push(p);p=Number(dv.getBigUint64(p+metadata.monst.fields.nmon.offset,true));}
  const rows=list.map(at=>{const b=Buffer.from(heap.slice(at,at+metadata.monst.size)),dp=Number(b.readBigUInt64LE(metadata.monst.fields.data.offset)),idx=dv.getInt32(dp+metadata.permonst.fields.pmidx.offset,true);assert.equal(dp,Number(mons)+idx*metadata.permonst.size);b.writeBigUInt64LE(BigInt(idx+1),metadata.monst.fields.data.offset);const next=Number(b.readBigUInt64LE(metadata.monst.fields.nmon.offset));b.writeBigUInt64LE(BigInt(next?ids.get(next):0),metadata.monst.fields.nmon.offset);for(const key of ['minvent','mw','mextra'])assert.equal(b.readBigUInt64LE(metadata.monst.fields[key].offset),0n,key+' accounted for');return b;});return {rows,ids};
 }
 function checkList(){const js=monsterList(memory.HEAPU8,world.fmon,env.requireGlobal('mons')),base=Number(ref._probe_monster_global(0)),rootOffset=metadata.instance_globals_saved_l.fields.level.offset+metadata.dlevel_t.fields.monlist.offset,first=new DataView(ref.HEAPU8.buffer).getBigUint64(base+rootOffset,true),native=monsterList(ref.HEAPU8,first,ref._probe_monster_global(8));assert.deepEqual(js.rows,native.rows,'all group monster bytes');const vitals=metadata.instance_globals_saved_m.fields.mvitals.offset,size=L.NUMMONS*metadata.mvitals.size,cm=Number(ref._probe_monster_global(1));assert.deepEqual(memory.readBytes(env.requireGlobal('svm')+vitals,size),ref.HEAPU8.slice(cm+vitals,cm+vitals+size),'all group birth/vital state');
  const map=metadata.instance_globals_saved_l.fields.level.offset+metadata.dlevel_t.fields.monsters.offset,dv=new DataView(ref.HEAPU8.buffer);for(let x=0;x<L.COLNO;x++)for(let y=0;y<L.ROWNO;y++){const jp=env.address(world.svl.level.monsters[x][y]),cp=Number(dv.getBigUint64(base+map+(x*L.ROWNO+y)*8,true));assert.equal(jp?js.ids.get(jp):0,cp?native.ids.get(cp):0,'map identity '+x+','+y);}comparisons++;return js.rows.length;
 }
 const ant=constants('PM_GIANT_ANT'),mm=L.NO_MINVENT|L.MM_NOGRP|L.MM_NONAME|L.MM_NOMSG;
 for(let i=0;i<12;i++){
  const p=env.services.makemon(env.requireGlobal('mons')+ant*metadata.permonst.size,0,0,mm),q=ref._probe_position_spawn(ant,0,0,mm);assert.ok(p&&q);assert.equal(checkList(),1);
  const m=creation.views.record('struct monst',p);env.services.m_initgrp(p,m.mx,m.my,7,mm);ref._probe_position_group(7,mm);assert.ok(checkList()>1,'actual group creation');
  while(world.fmon){const m=world.fmon;world.fmon=m.nmon;m.nmon=0;world.svl.level.monsters[m.mx][m.my]=0;env.services.dealloc_monst(m);}ref._probe_position_dispose_group();
 }
 const actualLog=Buffer.from(env.filesystem.readFile('/rng.log')).toString('latin1').split('\n'),expectedLog=Buffer.from(ref.FS.readFile('/rng.log')).toString('latin1').split('\n');assert.equal(actualLog.length,expectedLog.length,'RNG log length');for(let i=0;i<actualLog.length;i++)assert.equal(actualLog[i],expectedLog[i],'RNG log '+i);comparisons++;
 assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);
}
console.log(`PASS: ${comparisons} original-C terrain/goodpos/coordinate-collection/nearby-position/RNG comparisons. Full world transitions remain under integration.`);
