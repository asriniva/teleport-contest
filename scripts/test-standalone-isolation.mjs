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
