// This test deliberately loads no C oracle and forbids Wasm/network globals
// before importing the standalone production entry point.
import assert from 'node:assert/strict';
import fs from 'node:fs';
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
for(const key of ['WebAssembly','fetch','Worker','WebSocket','XMLHttpRequest'])Object.defineProperty(globalThis,key,{get(){throw new Error('Forbidden standalone capability '+key);},configurable:true});
const {createStandaloneEnvironment}=await import('../js/standalone/environment.js');
const env=createStandaloneEnvironment({environment:{NOMUX_MARKERS:'1'}});
env.enableStdio();env.enableDecl(layouts.decl);env.enableHacklib(layouts.hacklib);env.enableDrawing(layouts.drawing);env.enableObjects(layouts.objects);env.enableMonst(layouts.monst);
env.enableSerialization(layouts);env.enableTrack(layouts);env.enableRnd(layouts.rnd,{seed:123n});env.enableCommandGeometry();env.enableDependencies();
env.call('objects','objects_globals_init');
env.enableAddressPort('dungeon',{only:['ledger_no','maxledgerno']});env.enableObjectState(layouts);env.call('object-state','init_objects');
// Entire object state -> real serializer callbacks -> CVFS -> restored state,
// under the same forbidden-capability guard as the production import.
const type=layouts.o_init.POT_HEALING,cls=env.requireGlobal('objects')+type*layouts.o_init.objectClassSize;
env.ctypes.setField('struct objclass',cls,'oc_uname','char *',env.memory.cstring('isolated name'));
const fp=env.memory.calloc(1,layouts.sfstruct.nhfileSize),B=layouts.sfbase,S=layouts.sfstruct;
const file=(fd,mode)=>{env.memory.memset(fp,0,S.nhfileSize);env.memory.view.setInt32(fp+S.nhf_fd,fd,true);env.memory.view.setInt32(fp+B.nhf_fnidx,B.historical,true);env.memory.view.setInt8(fp+B.nhf_structlevel,1);env.memory.view.setInt32(fp+B.nhf_mode,mode,true);};
let fd=env.services.open('/object-names',578,0o600);file(fd,B.WRITING|B.FREEING);env.call('object-state','savenames',fp);env.call('sfstruct','bclose',fd);
fd=env.services.open('/object-names',0);file(fd,0);env.call('object-state','restnames',fp);env.call('sfstruct','bclose',fd);env.memory.free(fp);
assert.equal(env.memory.readString(Number(env.ctypes.getField('struct objclass',cls,'oc_uname','char *'))),'isolated name');
env.call('monst','monst_globals_init');env.enableObjectRecords(layouts);
const item=env.memory.malloc(env.ctypes.size('struct obj'));
env.call('mkobj','init_dummyobj',item,layouts.mkobj.APPLE,7n);assert.ok(env.call('mkobj','weight',item)>0);
env.call('mkobj','newomonst',item);env.call('mkobj','new_omailcmd',item,env.services.literal('isolated command'));
env.call('mkobj','dealloc_obj_real',item);assert.ok(!env.memory.live.has(item));
env.services.svc.context.ident=2;env.enableItemInventory(layouts);
const generated=env.call('mkobj','mksobj',layouts.o_init.POT_HEALING,1,0);
assert.equal(env.call('invent','addinv',generated),generated);env.call('invent','freeinv',generated);env.call('mkobj','dealloc_obj_real',generated);
env.enableTimers(layouts);const selection=env.enableMonsterSelection(layouts),world=selection.environment;
// Explicit valid component input; full dungeon startup is a later group.
env.ctypes.setField('struct instance_globals_saved_n',env.requireGlobal('svn'),'n_dgns','int',3);
world.svd.dungeon_topology.d_quest_dnum=1;world.svd.dungeon_topology.d_astral_level.dnum=2;
for(let i=0;i<3;i++){world.svd.dungeons[i].num_dunlevs=30;world.svd.dungeons[i].entry_lev=1;world.svd.dungeons[i].depth_start=1;}
world.u.ulevel=10;world.u.uz.dnum=0;world.u.uz.dlevel=5;
for(const type of [layouts.mkobj.GLOB_OF_GRAY_OOZE,layouts.mkobj.CORPSE,layouts.mkobj.EGG,layouts.mkobj.FIGURINE,layouts.mkobj.STATUE,layouts.mkobj.TIN,layouts.mkobj.CANDY_BAR]){
 const p=env.services.mksobj(type,1,0);assert.ok(p);env.services.obj_stop_timers(p);env.services.obfree(p,0);env.services.dobjsfree();assert.ok(!env.memory.live.has(p));
}
env.enableItemNaming(layouts);
for(const type of [layouts.mkobj.CHEST,layouts.mkobj.ICE_BOX,layouts.mkobj.BAG_OF_HOLDING,layouts.mkobj.SPE_NOVEL]){
 const p=env.services.mksobj(type,1,0);assert.ok(p);env.services.obfree(p,0);env.services.dobjsfree();assert.ok(!env.memory.live.has(p));
}
const sword=env.services.mksobj(layouts.earlyarg.LONG_SWORD,1,0);
assert.equal(env.address(env.services.mk_artifact(sword,layouts.artifact.A_NONE,99,1)),sword);
assert.ok(env.ctypes.getField('struct obj',sword,'oartifact','char')>0);env.services.obfree(sword,0);env.services.dobjsfree();
const creatures=env.enableMonsterCreation(layouts);env.enableMonsterInventory(layouts);
const w=creatures.environment,Lm=layouts.makemon;
w.gi.in_mklev=1;w.svl.level.flags.rndmongen=1;w.u.ux=40;w.u.uy=10;
const vision=env.memory.calloc(Lm.ROWNO,Lm.COLNO),rows=env.memory.calloc(Lm.ROWNO,8);
for(let y=0;y<Lm.ROWNO;y++)env.memory.view.setBigUint64(rows+y*8,BigInt(vision+y*Lm.COLNO),true);w.gv.viz_array=rows;
const pm=layouts.earlyarg.PM_ORC,mon=env.services.makemon(env.requireGlobal('mons')+pm*env.ctypes.size('struct permonst'),10,10,Lm.MM_NOGRP|Lm.MM_NONAME|Lm.MM_NOMSG);
assert.ok(mon);assert.equal(env.address(w.svl.level.monsters[10][10]),env.address(mon));
env.services.discard_minvent(mon,0);env.services.dobjsfree();w.svl.level.monsters[10][10]=0;w.fmon=0;env.services.dealloc_monst(mon);assert.ok(!env.memory.live.has(env.address(mon)));
env.enableWorldPosition(layouts);
env.services.make_engr_at(10,10,'Elbereth',0,0n,layouts.engrave.DUST);assert.ok(env.services.engr_at(10,10));env.services.del_engr_at(10,10);
for(let x=0;x<Lm.COLNO;x++)for(let y=0;y<Lm.ROWNO;y++)w.levl[x][y].typ=Lm.ROOM;
const ant=Object.values(layouts).find(p=>p&&p.PM_GIANT_ANT!==undefined).PM_GIANT_ANT,flags=Lm.NO_MINVENT|Lm.MM_NOGRP|Lm.MM_NONAME|Lm.MM_NOMSG;
const random=env.services.makemon(env.requireGlobal('mons')+ant*env.ctypes.size('struct permonst'),0,0,flags);assert.ok(random);
const am=creatures.views.record('struct monst',random);env.services.m_initgrp(random,am.mx,am.my,4,flags);assert.ok(w.fmon.nmon);
while(w.fmon){const m=w.fmon;w.fmon=m.nmon;m.nmon=0;w.svl.level.monsters[m.mx][m.my]=0;env.services.dealloc_monst(m);}
const terminal=env.enableTerminal(layouts.termcap);
env.call('termcap','nomux_clear_screen');env.call('termcap','nomux_capture_write_input_boundary');assert.equal(terminal.frames.length,1);
const lua=env.enableLua(),L=lua.api.luaL_newstate();assert.equal(lua.api.luaL_loadstring(L,'return 21*2'),0);assert.equal(lua.api.lua_pcallk(L,0,1,0,0n,0n),0);assert.equal(lua.api.lua_tointegerx(L,-1,0),42n);lua.api.lua_close(L);
env.filesystem.mkdir('/nethack');env.filesystem.writeFile('/nethack/base',Uint8Array.of(1));const baseline=env.fileBaseline();
env.filesystem.unlink('/nethack/base');env.filesystem.writeFile('/nethack/bonD0.3',Uint8Array.of(0,255,17));
const state=env.captureFiles(baseline),other=createStandaloneEnvironment();other.filesystem.mkdir('/nethack');other.filesystem.writeFile('/nethack/base',Uint8Array.of(1));other.restoreFiles(state);
assert.deepEqual([...other.filesystem.readFile('/nethack/bonD0.3')],[0,255,17]);assert.throws(()=>other.filesystem.stat('/nethack/base'));
// Original compress returns status 2 when a tiny input does not shrink; the
// encoded bytes and that status both remain part of its transport contract.
const p=env.memory.cstring('/nethack/bonD0.3'),q=env.memory.cstring('/nethack/bonD0.3.Z');assert.equal(env.services.compressFile(p,q,false),2);env.filesystem.unlink('/nethack/bonD0.3');assert.equal(env.services.compressFile(p,q,true),0);assert.deepEqual([...env.filesystem.readFile('/nethack/bonD0.3')],[0,255,17]);
assert.equal(env.call('cmd-geometry','isok',1,0),1);assert.equal(env.call('cmd-geometry','isok',0,0),0);
console.log('PASS: standalone source modules, Lua, recorder capture, compression and persistence run with Wasm and network capabilities forbidden.');
