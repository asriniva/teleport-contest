/** Native5.4.8 differential deterministic GC/lifecycle plus owned-allocation checks. */
import assert from 'node:assert/strict';
import { readFileSync,writeFileSync,mkdirSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import { createLua,LuaTable,LuaUserdata,LuaError,isLuaString,luaStringBytes } from '../js/services/lua/lua.js';
import { createLuaCState } from '../js/services/lua/lapi.js';
import { LuaMemoryError } from '../js/services/lua-debug.js';
const root=fileURLToPath(new URL('../',import.meta.url)),scratch=resolve(root,'.cache/js-dependency-lua');mkdirSync(scratch,{recursive:true});
const oracleSource=readFileSync(resolve(root,'scripts/test-js-lua.mjs'),'utf8').split('writeFileSync(resolve(scratch, \'oracle.c\'), String.raw`')[1].split('`);')[0];
writeFileSync(resolve(scratch,'oracle-gc.c'),oracleSource);
execFileSync('python3',[resolve(root,'scripts/test-js-lua-native.py'),'oracle-gc'],{stdio:'inherit'});
const encode=v=>v===null?'nil':typeof v==='bigint'?`integer:${v}`:typeof v==='boolean'?`boolean:${Number(v)}`:isLuaString(v)?'string:'+Array.from(luaStringBytes(v),c=>c.charCodeAt(0).toString(16).padStart(2,'0')).join(''):typeof v==='number'?(()=>{const b=new DataView(new ArrayBuffer(8));b.setFloat64(0,v);return 'float:'+b.getBigUint64(0).toString(16).padStart(16,'0')})():'type:table';
const cases=[
 ['longstring-weak-values',`local w=setmetatable({},{__mode='v'});w[1]=string.rep('a',100);w[2]=string.rep('a',100);local a=host_samepointer(w[1],w[2]);collectgarbage();return a,w[1]==w[2],#w[1],host_samepointer(w[1],w[2])`],
 ['longstring-weak-keys',`local w=setmetatable({},{__mode='k'});w[string.rep('a',100)]=17;collectgarbage();return w[string.rep('a',100)],next(w)~=nil`],
 ['longstring-gmatch-root',`local it=string.gmatch(string.rep('a',100),'(a+)');collectgarbage();local a=it();return #a`],
 ['weak-values',`collectgarbage('stop');local w=setmetatable({},{__mode='v'});do local t={};w[1]=t end;collectgarbage();return w[1]==nil`],
 ['weak-string-values',`local w=setmetatable({},{__mode='v'});w[1]='literal';w[2]=string.rep('a',100);collectgarbage();return w[1],#w[2]`],
 ['weak-keys',`local w=setmetatable({},{__mode='k'});do local k={};w[k]=17 end;collectgarbage();return next(w)==nil`],
 ['ephemeron-cycle',`local w=setmetatable({},{__mode='k'});do local k={};w[k]={key=k} end;collectgarbage();return next(w)==nil`],
 ['ephemeron-live-key',`local w=setmetatable({},{__mode='k'});local k={};w[k]={value=19};collectgarbage();return w[k].value`],
 ['ephemeron-fixedpoint',`local w=setmetatable({},{__mode='k'});local a,b,c={},{},{};w[a]=b;w[b]=c;local root=a;b=nil;c=nil;collectgarbage();return w[w[root]]~=nil,w[root]~=nil,w[w[root]]==nil`],
 ['finalizer-reverse-registration',`collectgarbage('stop');local out={};do local a=setmetatable({},{__gc=function()out[#out+1]='a'end});local b=setmetatable({},{__gc=function()out[#out+1]='b'end}) end;collectgarbage();collectgarbage();return table.concat(out)`],
 ['finalizer-resurrection',`collectgarbage('stop');local count=0;do local a=setmetatable({x=17},{__gc=function(t)count=count+1;_G.saved=t end})end;collectgarbage();local x=saved.x;saved=nil;collectgarbage();return count,x`],
 ['finalizer-added-late',`local n=0;local mt={};do local a=setmetatable({},mt);mt.__gc=function()n=n+1 end end;collectgarbage();return n`],
 ['weak-value-finalization-order',`local w=setmetatable({},{__mode='v'});local seen;do local a=setmetatable({},{__gc=function(t)seen=w[1]==nil end});w[1]=a end;collectgarbage();return seen,w[1]==nil`],
 ['weak-key-finalization-order',`local w=setmetatable({},{__mode='k'});local seen;do local a=setmetatable({},{__gc=function(t)seen=w[t]end});w[a]=17 end;collectgarbage();local before=next(w)~=nil;collectgarbage();return seen,before,next(w)==nil`],
 ['closure-capture-root',`local w=setmetatable({},{__mode='v'});local f;do local x={value=23};w[1]=x;f=function()return x.value end end;collectgarbage();local y=f();f=nil;collectgarbage();return y,w[1]==nil`],
 ['closure-unused-root',`local w=setmetatable({},{__mode='v'});local f;do local x={};w[1]=x;f=function()return 1 end end;collectgarbage();return w[1]==nil,f()`],
 ['suspended-coroutine-root',`local w=setmetatable({},{__mode='v'});local co=coroutine.create(function()local x={value=29};w[1]=x;coroutine.yield();return x.value end);coroutine.resume(co);collectgarbage();local a=w[1]~=nil;local ok,y=coroutine.resume(co);collectgarbage();return a,ok,y,w[1]==nil`],
 ['wrapped-coroutine-root',`local f=coroutine.wrap(function()local t={x=31};coroutine.yield(t.x);return t.x+1 end);local a=f();collectgarbage();return a,f()`],
 ['unreachable-coroutine',`local w=setmetatable({},{__mode='v'});do local co=coroutine.create(function()local t={};w[1]=t;coroutine.yield()end);coroutine.resume(co)end;collectgarbage();return w[1]==nil`],
 ['close-scope-order',`local out={};local mt={__close=function(t,e)out[#out+1]=t.x..':'..tostring(e)end};do local a <close> =setmetatable({x='a'},mt);local b <close> =setmetatable({x='b'},mt)end;return table.concat(out,',')`],
 ['close-return-values',`local n=0;local function f()local x <close> =setmetatable({},{__close=function()n=n+1 end});return 17,23 end;local a,b=f();return a,b,n`],
 ['close-error-chain',`local out={};local ok,e=pcall(function()local a <close> =setmetatable({},{__close=function(t,e)out[#out+1]=e end});local b <close> =setmetatable({},{__close=function(t,e)out[#out+1]=e;error('closer',0)end});error('body',0)end);return ok,e,table.concat(out,',')`],
 ['close-break',`local n=0;while true do local x <close> =setmetatable({},{__close=function()n=n+1 end});break end;return n`],
 ['close-false-nil',`local x <close> =false;do local y <close> =nil end;return x`],
 ['close-suspended-coroutine',`local n=0;local co=coroutine.create(function()local x <close> =setmetatable({},{__close=function()n=n+1 end});coroutine.yield()end);coroutine.resume(co);local ok,e=coroutine.close(co);return ok,e,n,coroutine.status(co),coroutine.close(co)`],
 ['close-unstarted-coroutine',`local n=0;local co=coroutine.create(function()n=n+1 end);return coroutine.close(co),n,coroutine.status(co)`],
 ['error-coroutine-delays-close',`local n=0;local co=coroutine.create(function()local x <close> =setmetatable({},{__close=function()n=n+1 end});error(17)end);local a,e=coroutine.resume(co);local before=n;local c,d=coroutine.close(co);return a,e,before,c,d,n`],
 ['pcall-coroutine-closes-error',`local n=0;local co=coroutine.create(function()local a,e=pcall(function()local x <close> =setmetatable({},{__close=function()n=n+1 end});error(17)end);return a,e,n end);return coroutine.resume(co)`],
 ['close-errored-coroutine',`local co=coroutine.create(function()error(17)end);coroutine.resume(co);local a,b=coroutine.close(co);return a,b,coroutine.close(co)`],
 ['close-yield-allowed',`local co=coroutine.create(function()local x <close> =setmetatable({},{__close=function()coroutine.yield('closing')end});return 'returned'end);local a,b=coroutine.resume(co);local c,d=coroutine.resume(co);return a,b,c,d`],
 ['close-yield-rejected',`local co=coroutine.create(function()local x <close> =setmetatable({},{__close=function()coroutine.yield('closing')end});coroutine.yield()end);coroutine.resume(co);local a,e=coroutine.close(co);return a,type(e),coroutine.status(co)`],
 ['genericfor-close',`local n=0;local function iterator(s,k)if k<2 then return k+1 end end;local function factory()return iterator,nil,0,setmetatable({},{__close=function()n=n+1 end})end;for k in factory()do break end;return n`],
 ['reentrant-finalizer-collect',`local seen;do local x=setmetatable({},{__gc=function()seen=collectgarbage('collect')end})end;collectgarbage();return seen`],
 ['finalizer-errors-continue',`local n=0;do local a=setmetatable({},{__gc=function()n=n+1 end});local b=setmetatable({},{__gc=function()error('finalizer error',0)end})end;collectgarbage();return n`],
];
const phaseCases=[
 ['automatic-finalizer',`local n=0;do local x=setmetatable({},{__gc=function()n=n+1 end})end;for i=1,5000 do local t={}end;return n`],
 ['gc-controls',`local old=collectgarbage('incremental',120,80,10);local a=collectgarbage('setpause',224);local b=collectgarbage('setstepmul',108);collectgarbage('stop');local s=collectgarbage('isrunning');collectgarbage('step',0);local s2=collectgarbage('isrunning');collectgarbage('restart');local s3=collectgarbage('isrunning');local before=collectgarbage('generational',30,200);local after=collectgarbage('incremental');return old,a,b,s,s2,s3,before,after`],
 ['gc-minor-finalization',`collectgarbage('generational');collectgarbage('stop');local n=0;do local x=setmetatable({},{__gc=function()n=n+1 end})end;collectgarbage('step',0);return n`],
 ['gc-minor-weak-values',`collectgarbage('generational');collectgarbage('stop');local w=setmetatable({},{__mode='v'});do local x={};w[1]=x end;collectgarbage('step',0);return w[1]==nil`],
 ['gc-old-table-new-value',`collectgarbage('generational');local t={};collectgarbage('step',0);collectgarbage('step',0);collectgarbage('step',0);t.x={value=17};collectgarbage('step',0);return t.x.value`],
 ['gc-old-ephemeron',`local w=setmetatable({},{__mode='k'});collectgarbage('generational');local key={};w[key]={value=23};collectgarbage('step',0);collectgarbage('step',0);local v=w[key].value;key=nil;collectgarbage('step',0);collectgarbage('step',0);collectgarbage('step',0);return v,next(w)==nil`],
];
for(const collector of ['full','incremental','generational'])for(const[name,original]of (collector==='full'?cases:[...cases,...phaseCases])){const phased=collector!=='full',source=(collector==='generational'?"collectgarbage('generational');":'')+original;const input=resolve(scratch,'gc-input.lua');writeFileSync(input,source);const native=execFileSync(resolve(scratch,'oracle-gc'),[input],{encoding:'utf8'}).trimEnd();const vm=createLua({baseError:true,baseMeta:true,baseGC:true,gcScheduler:phased});if(phased)vm.heap.attachScheduler();vm.setGlobal('host_samepointer',(a,b)=>[a===b]);assert.equal(vm.execute(source,name).map(encode).join('\n'),native,name);vm.heap.close();assert.equal(vm.heap.memoryTracker.bytes,0,name+' releases every block');}
// Actual injected allocator owns every block; failures propagate ERRMEM through protected C calls.
const blocks=new Map();let allocations=0,failed=false;
const allocator=(_ud,ptr,old,size)=>{if(ptr!==null)assert.equal(blocks.get(ptr),old);if(size&&failed)return null;if(!size){blocks.delete(ptr);return null}const p={id:++allocations};blocks.delete(ptr);blocks.set(p,size);return p};
const L=createLuaCState({memoryAllocator:allocator});const baseline=L.vm.heap.memoryTracker.bytes;assert.ok(baseline>0);assert.equal(L.lua_gc(3)*1024+L.lua_gc(4),baseline);
L.lua_newtable();for(let i=1;i<=64;i++){L.lua_pushinteger(i);L.lua_rawseti(-2,i)}assert.ok(L.vm.heap.memoryTracker.bytes>baseline);L.lua_pop(1);L.lua_gc(2);assert.ok(L.vm.heap.memoryTracker.bytes<=baseline);
L.lua_pushcfunction(S=>{S.lua_pushlstring('unique-allocation-'+allocations,30);return 1});failed=true;assert.equal(L.lua_pcall(0,1),4);failed=false;assert.equal(L.lua_tostring(-1),'not enough memory');L.lua_pop(1);
L.lua_close();assert.equal(blocks.size,0);assert.equal(L.vm.heap.memoryTracker.bytes,0);
// Userdata remains allocated during finalizer and resurrection, then releases exactly once.
let released=0,finalized=0;const U=createLuaCState({userdataFactory:size=>({value:new Uint8Array(size),release:()=>released++})});
U.lua_newuserdatauv(8,1);const object=U.value(-1);U.lua_newtable();U.lua_pushcfunction(()=>{assert.equal(released,0);finalized++;return 0});U.lua_setfield(-2,'__gc');U.lua_setmetatable(-2);U.lua_pop(1);U.lua_gc(2);assert.equal(finalized,1);assert.equal(released,0);U.lua_gc(2);assert.equal(released,1);assert.equal(object.luaFreed,true);U.lua_close();assert.equal(released,1);
console.log(`PASS: ${cases.length} native Lua5.4.8 lifecycle/weak/finalizer cases under full, phased incremental and phased generational collectors, plus real step/mode/barrier cases; injected allocator counts, ERRMEM, complete close/free and userdata release.`);
console.log('Scope: lifecycle, weak/finalizer semantics and collector phases. Native binary/source allocation transcripts and library buffer refusal boundaries are checked by separate gates; this AST fixture does not certify arbitrary native allocation traces.');
