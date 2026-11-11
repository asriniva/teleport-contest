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
