import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/standalone/environment.js';
import {C,R,T} from '../js/ported/c-runtime.js';
const directory=path.resolve(process.env.STANDALONE_SPECIAL_ITEMS_ORACLE||'.cache/standalone-special-items');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json')));
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const [p,h]of Object.entries(receipt.sourceSha256))assert.equal(sha(p),h,'Changed C source '+p);
for(const [p,h]of Object.entries(receipt.artifactSha256))assert.equal(sha(path.join(directory,p)),h,'Changed C artifact '+p);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs')));
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L=layouts.makemon,M=layouts.mkobj;
const metadata=JSON.parse(fs.readFileSync('js/standalone/records.json')).records;
let comparisons=0,constructors=0,contentRecords=0;const nonempty=new Set();
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
 // Real container generation and recursive lifetime; all pointer identities
 // are accounted for, including nested containers and their contents.
 function objectAddresses(heap,start){
  const rows=[],seen=new Set(),dv=new DataView(heap.buffer),field=(p,k)=>Number(dv.getBigUint64(Number(p)+metadata.obj.fields[k].offset,true));
  function visit(p){p=Number(p);if(!p||seen.has(p))return;seen.add(p);rows.push(p);visit(field(p,'cobj'));visit(field(p,'nobj'));}
  visit(start);
  return rows;
 }
 function objectGraph(heap,start){
  const rows=objectAddresses(heap,start),ids=new Map(rows.map((p,i)=>[p,i+1]));
  return rows.map(p=>{const b=Buffer.from(heap.slice(p,p+metadata.obj.size));for(const key of ['nobj','v','cobj']){const at=metadata.obj.fields[key].offset,q=Number(b.readBigUInt64LE(at));assert.ok(!q||ids.has(q),'all object pointer identities must be accounted for');b.writeBigUInt64LE(BigInt(q?ids.get(q):0),at);}assert.equal(b.readBigUInt64LE(metadata.obj.fields.oextra.offset),0n,'unnamed profile has no hidden extra');return b;});
 }
 const types=[M.LARGE_BOX,M.CHEST,M.ICE_BOX,M.SACK,M.OILSKIN_SACK,M.BAG_OF_HOLDING];
 for(const [turn,inMklev]of [[1n,0],[100n,0],[1n,1]]){
  const moves=ctypes.locate('struct instance_globals_saved_m',env.requireGlobal('svm'),'moves').at;
  memory.view.setBigInt64(moves,turn,true);new DataView(ref.HEAPU8.buffer).setBigInt64(Number(ref._probe_timer_global(2)),turn,true);
  ctypes.setField('struct instance_globals_i',env.requireGlobal('gi'),'in_mklev','signed char',inMklev);
  ref.HEAPU8[Number(ref._probe_item_global(0))+metadata.instance_globals_i.fields.in_mklev.offset]=inMklev;
 for(let i=0;i<24;i++)for(const type of types){
  const p=env.services.mksobj(type,1,0),q=BigInt(ref._probe_item_create(0,type,1,0));
  const graph=objectGraph(memory.HEAPU8,p);constructors++;contentRecords+=graph.length-1;if(graph.length>1)nonempty.add(type);
  assert.deepEqual(graph,objectGraph(ref.HEAPU8,q),'object graph '+type);comparisons++;
  const root=ctypes.locate('struct instance_globals_t',env.requireGlobal('gt'),'timer_base').at;
  const readQueue=(heap,start,object)=>{const objects=objectAddresses(heap,object),rows=[],seen=new Set();let at=Number(new DataView(heap.buffer).getBigUint64(start,true));while(at){assert.ok(!seen.has(at),'acyclic timer queue');seen.add(at);const b=Buffer.from(heap.slice(at,at+metadata.fe.size)),next=b.readBigUInt64LE(metadata.fe.fields.next.offset),arg=b.readBigUInt64LE(metadata.fe.fields.arg.offset),index=objects.indexOf(Number(arg));b.writeBigUInt64LE(next?1n:0n,metadata.fe.fields.next.offset);assert.ok(index>=0,'timer belongs to reachable content');b.writeBigUInt64LE(BigInt(index+1),metadata.fe.fields.arg.offset);rows.push(b);at=Number(next);}return rows;};
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
 }
 const actualLog=Buffer.from(env.filesystem.readFile('/rng.log')).toString('latin1').split('\n'),expectedLog=Buffer.from(ref.FS.readFile('/rng.log')).toString('latin1').split('\n');
 assert.equal(actualLog.length,expectedLog.length,'RNG log length');
 for(let i=0;i<actualLog.length;i++)assert.equal(actualLog[i],expectedLog[i],'RNG stream/caller log line '+i);comparisons++;
 let p=Number(ref._probe_diagnostics()),end=p;while(ref.HEAPU8[end])end++;assert.equal(env.diagnostics.join(''),Buffer.from(ref.HEAPU8.slice(p,end)).toString('latin1'));comparisons++;
}
for(const type of [M.LARGE_BOX,M.CHEST,M.ICE_BOX,M.SACK,M.OILSKIN_SACK,M.BAG_OF_HOLDING])assert.ok(nonempty.has(type),'nonempty coverage '+type);
console.log(`PASS: ${comparisons} original-C container/contents/timer/deletion/RNG comparisons; ${constructors} constructors with ${contentRecords} contained records across initial-inventory, normal-turn and map-generation inputs. Novel and artifact constructors remain separate.`);
