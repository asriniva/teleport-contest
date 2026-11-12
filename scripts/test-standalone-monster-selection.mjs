import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/standalone/environment.js';
import {C,R,T} from '../js/c-runtime/context.js';
const directory=path.resolve(process.env.STANDALONE_SPECIAL_ITEMS_ORACLE||'.cache/standalone-special-items');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json')));
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const [p,h]of Object.entries(receipt.sourceSha256))assert.equal(sha(p),h,'Changed C source '+p);
for(const [p,h]of Object.entries(receipt.artifactSha256))assert.equal(sha(path.join(directory,p)),h,'Changed C artifact '+p);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs')));
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L=layouts.makemon,M=layouts.mkobj;
const metadata=JSON.parse(fs.readFileSync('js/standalone/records.json')).records;
let comparisons=0;
for(const seed of [1n,0x12345678n,0xffffffffffffffffn]){
 const env=createStandaloneEnvironment({initialBytes:1024,maximumBytes:64*1024*1024,environment:{NETHACK_RNGLOG:'/rng.log'}}),ref=await factory();
 env.enableStdio();env.enableDecl(layouts.decl);env.enableDrawing(layouts.drawing);env.enableObjects(layouts.objects);env.call('objects','objects_globals_init');env.enableMonst(layouts.monst);env.call('monst','monst_globals_init');env.enableSerialization(layouts);env.enableRnd(layouts.rnd,{seed});env.call('rnd','rng_log_init');env.enableAddressPort('dungeon',{only:['ledger_no','maxledgerno']});env.enableObjectState(layouts);env.call('object-state','init_objects');env.enableObjectRecords(layouts);env.services.svc.context.ident=2;env.services.svc.context.current_fruit=19;env.enableItemInventory(layouts);env.enableTimers(layouts);const group=env.enableMonsterSelection(layouts);
 ref._probe_init(seed);ref._probe_item_prepare();ref._probe_action(0,0,0,0);
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
 // Every original species and growth mapping, including current vital and egg
 // alternates, is checked against actual MON/MONDATA, not a lookup oracle.
 const functions=['zombie_form','undead_to_corpse','can_be_hatched','dead_species','little_to_big','big_to_little'];
 for(let pm=0;pm<L.NUMMONS;pm++)for(let op=0;op<functions.length;op++){
  const args=op===0?[env.requireGlobal('mons')+pm*metadata.permonst.size]:op===3?[pm,1]:[pm];
  const actual=env.resolve(functions[op])(...args);assert.equal(actual,ref._probe_species_biology(op,pm,1),functions[op]+' '+pm);comparisons++;
 }
 // Reservoir selection: ordinary/hell/alignment/temperature/elemental inputs
 // use the actual dungeon difficulty and real RNG on both sides.
 for(const [level,depth,align,temp,hell,plane]of [
  [1,1,L.AM_NONE,0,0,0],[10,5,L.AM_LAWFUL,0,0,0],[20,15,L.AM_NEUTRAL,1,0,0],[30,25,L.AM_CHAOTIC,-1,1,0],
  [20,20,L.AM_NONE,0,0,1],[20,20,L.AM_NONE,0,0,2],[20,20,L.AM_NONE,0,0,3],[20,20,L.AM_NONE,0,0,4],
 ]){
  config(level,depth,align,temp,hell,plane);
  for(let i=0;i<40;i++){const low=i%4,high=i%11;const actual=env.services.rndmonst_adj(low,high);assert.equal(actual?actual.pmidx:L.NON_PM,ref._probe_species_select(low,high),'species '+[level,depth,align,temp,hell,plane,i]);comparisons++;}
 }
 config(10,5,L.AM_NONE,0,0);
 // Real corpse/figurine/egg/statue generation, including newly attached timer
 // records. C pointers in timer arguments are normalized to object identity.
 function objectGraph(heap,start){
  const rows=[],ids=new Map(),dv=new DataView(heap.buffer),field=(p,k)=>Number(dv.getBigUint64(Number(p)+metadata.obj.fields[k].offset,true));
  function visit(p){p=Number(p);if(!p||ids.has(p))return;ids.set(p,ids.size+1);rows.push(p);visit(field(p,'cobj'));visit(field(p,'nobj'));}
  visit(start);
  return rows.map(p=>{const b=Buffer.from(heap.slice(p,p+metadata.obj.size));for(const key of ['nobj','v','cobj']){const at=metadata.obj.fields[key].offset,q=Number(b.readBigUInt64LE(at));assert.ok(!q||ids.has(q),'all object pointer identities must be accounted for');b.writeBigUInt64LE(BigInt(q?ids.get(q):0),at);}assert.equal(b.readBigUInt64LE(metadata.obj.fields.oextra.offset),0n,'unnamed profile has no hidden extra');return b;});
 }
 for(let i=0;i<24;i++)for(const type of [M.CORPSE,M.FIGURINE,M.EGG,M.STATUE,M.TIN,M.CANDY_BAR]){
  const p=env.services.mksobj(type,1,0),q=BigInt(ref._probe_item_create(0,type,1,0));
  assert.deepEqual(objectGraph(memory.HEAPU8,p),objectGraph(ref.HEAPU8,q),'object graph '+type);comparisons++;
  const root=ctypes.locate('struct instance_globals_t',env.requireGlobal('gt'),'timer_base').at;
  const readQueue=(heap,start,object)=>{const rows=[];let at=Number(new DataView(heap.buffer).getBigUint64(start,true));while(at){const b=Buffer.from(heap.slice(at,at+metadata.fe.size)),next=b.readBigUInt64LE(metadata.fe.fields.next.offset),arg=b.readBigUInt64LE(metadata.fe.fields.arg.offset);b.writeBigUInt64LE(next?1n:0n,metadata.fe.fields.next.offset);assert.equal(arg,BigInt(object));b.writeBigUInt64LE(1n,metadata.fe.fields.arg.offset);rows.push(b);at=Number(next);}return rows;};
  assert.deepEqual(readQueue(memory.HEAPU8,root,p),readQueue(ref.HEAPU8,Number(ref._probe_timer_global(0)),q),'queue '+type);comparisons++;
  // Use real recursive deletion, including automatic timer cancellation.
  env.services.obfree(p,0);ref._probe_special_dispose();
  const deleted=ctypes.getField('struct instance_globals_o',env.requireGlobal('go'),'objs_deleted','struct obj *');
  const cdeleted=new DataView(ref.HEAPU8.buffer).getBigUint64(Number(ref._probe_item_global(1))+metadata.instance_globals_o.fields.objs_deleted.offset,true);
  assert.deepEqual(objectGraph(memory.HEAPU8,deleted),objectGraph(ref.HEAPU8,cdeleted),'complete deletion queue '+type);
  assert.equal(memory.view.getBigUint64(root,true),0n,'recursive deletion cancels timers');
  assert.equal(new DataView(ref.HEAPU8.buffer).getBigUint64(Number(ref._probe_timer_global(0)),true),0n);comparisons++;
  env.services.dobjsfree();ref._probe_item_flush();assert.ok(!memory.live.has(p));
  assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);
 }
 const actualLog=Buffer.from(env.filesystem.readFile('/rng.log')).toString('latin1').split('\n'),expectedLog=Buffer.from(ref.FS.readFile('/rng.log')).toString('latin1').split('\n');
 assert.equal(actualLog.length,expectedLog.length,'RNG log length');
 for(let i=0;i<actualLog.length;i++)assert.equal(actualLog[i],expectedLog[i],'RNG stream/caller log line '+i);comparisons++;
 let p=Number(ref._probe_diagnostics()),end=p;while(ref.HEAPU8[end])end++;assert.equal(env.diagnostics.join(''),Buffer.from(ref.HEAPU8.slice(p,end)).toString('latin1'));comparisons++;
}
console.log(`PASS: ${comparisons} original-C species/biology/growth/elemental/hell/difficulty/RNG and corpse/figurine/egg/statue/tin/candy constructor/contents/timer comparisons. Full monster placement and quest-owner integration remain separate.`);
