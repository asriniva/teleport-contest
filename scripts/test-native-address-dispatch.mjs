import assert from 'node:assert/strict';
import fs from 'node:fs';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {C,withCEnvironment} from '../js/c-runtime/context.js';
import {createJsRuntime,CPanic} from '../js/nethack/runtime.js';
// Retained runtime dependencies must work from a native closure with no C
// context, and must not borrow another game's active context.
const runtime=createJsRuntime({initialBytes:1024,maximumBytes:2048});
const own=runtime.services.alloc(13);runtime.memory.bounds(own,16);
assert.equal(C,undefined);
const foreign={malloc(){throw Error('foreign allocator used');}};
withCEnvironment(foreign,()=>{
 const p=runtime.services.alloc(7);runtime.memory.bounds(p,8);
 assert.equal(C,foreign);
 assert.throws(()=>runtime.services.alloc(4096),CPanic);
 assert.equal(C,foreign,'failed retained dependency restores caller context');
});
assert.equal(C,undefined);
const L=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
const env=createStandaloneEnvironment({initialBytes:1024,maximumBytes:128*1024*1024});
env.enableDecl(L.decl);env.enableDrawing(L.drawing);env.enableObjects(L.objects);env.enableMonst(L.monst);
env.enableAddressPort('dungeon',{only:['on_level']});
assert.equal(env.status().dungeon,'registered');
const entry=env.services.on_level.nativeEntry;
assert.equal(typeof entry,'function');assert.equal(entry.nativeDirect,true);
assert.equal(env.status().dungeon,'registered','native lookup must not initialize a module');
const a=env.memory.calloc(1,env.ctypes.size('struct d_level')),b=env.memory.calloc(1,env.ctypes.size('struct d_level'));
const field=(p,n,v)=>env.ctypes.setField('struct d_level',p,n,'short',v);
field(a,'dnum',1);field(a,'dlevel',2);field(b,'dnum',1);field(b,'dlevel',2);
const marker={nativeDispatchCaller:true};
withCEnvironment(marker,()=>{assert.equal(entry(a,b),1);assert.equal(C,marker,'native dispatch retains the caller context');});
assert.equal(env.status().dungeon,'ready');assert.equal(C,undefined);
field(b,'dlevel',3);assert.equal(entry(a,b),0);assert.equal(env.services.on_level(a,b),0);
assert.equal(env.services.on_level.nativeEntry,entry);
const pointer=env.functionPointer('on_level','ipp');
assert.equal(env.functions.indirect(pointer,'ipp',a,b),0,'callback ABI still invokes the same native policy');
env.resolve('depth');assert.equal(typeof env.services.depth.nativeEntry,'function','deferred native functions expose their selected kernel');
assert.throws(()=>entry(0xfffffff8,b),RangeError);assert.equal(C,undefined);
console.log('PASS native direct/deferred lookup, lazy initialization, context isolation, callback ABI and exceptional cleanup');
