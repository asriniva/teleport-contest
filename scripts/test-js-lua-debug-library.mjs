/** Native5.4.8 comparisons for NetHack's actual retained wizard libraries. */
import assert from 'node:assert/strict';
import { readFileSync, writeFileSync, mkdirSync, readdirSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { fileURLToPath } from 'node:url';
import { resolve } from 'node:path';
import { createLuaBytecodeVM } from '../js/lua/bytecode-vm.js';
import { openDebugLibrary } from '../js/lua/debug-library.js';
import { openBaseIO } from '../js/lua/base-io.js';
import { LuaTable, LuaUserdata, LuaLightUserdata, isLuaString, luaStringBytes, luaType } from '../js/lua/lobject.js';
const root = fileURLToPath(new URL('../', import.meta.url)), scratch = resolve(root, '.cache/js-lua-debug/library'); mkdirSync(scratch, { recursive: true });
const lua = resolve(root, '.cache/js-dependency-lua/lua-5.4.8/src');
let c = readFileSync(resolve(root, 'scripts/test-js-lua.mjs'), 'utf8').match(/writeFileSync\(resolve\(scratch, 'oracle.c'\), String.raw`([\s\S]*?)`\);/)[1];
c = c.replace('int main(int argc,char **argv)', 'static int host_userdata(lua_State *L){lua_newuserdatauv(L,4,2);return 1;}\nstatic int host_capture(lua_State *L){lua_pushvalue(L,lua_upvalueindex(1));return 1;}\nint main(int argc,char **argv)');
c = c.replace('if(argc<2)', 'lua_pushinteger(L,17);lua_pushcclosure(L,host_capture,1);lua_setglobal(L,"host_capture");if(argc<2)');
c = c.replace('lua_State *L=luaL_newstate(); luaL_openlibs(L);', 'lua_State *L=luaL_newstate(); luaL_openlibs(L); lua_pushcfunction(L,host_userdata);lua_setglobal(L,"host_userdata");lua_getglobal(L,"debug");const char *drop[]={"debug","gethook","sethook",NULL};for(int i=0;drop[i];i++){lua_pushnil(L);lua_setfield(L,-2,drop[i]);}lua_pop(L,1);lua_pushnil(L);lua_setglobal(L,"print");lua_pushnil(L);lua_setglobal(L,"warn");');
writeFileSync(resolve(scratch, 'oracle.c'), c);
execFileSync(resolve(root, '.cache/wasm64-build/host-cc'), ['-O2', '-I' + lua, resolve(scratch, 'oracle.c'), ...readdirSync(lua).filter(n => n.endsWith('.c') && !['lua.c', 'luac.c'].includes(n)).map(n => resolve(lua, n)), '-lm', '-o', resolve(scratch, 'oracle')]);
const cases = [
 ['exports', 'local t={};for k in pairs(debug)do t[#t+1]=k end;table.sort(t);return table.concat(t,","),type(load),type(loadfile),type(dofile),print,warn'],
 ['getinfo-function', 'local function f(a,b,...)return a end;local t=debug.getinfo(f);return t.what,t.linedefined,t.lastlinedefined,t.nups,t.nparams,t.isvararg,t.currentline,t.name,t.namewhat,t.istailcall,t.ftransfer,t.ntransfer,t.func==f'],
 ['getinfo-c', 'local t=debug.getinfo(debug.getinfo,"SuL");return t.what,t.source,t.short_src,t.linedefined,t.nups,t.nparams,t.isvararg,t.activelines'],
 ['getinfo-stack', 'local function f(a)local b=debug.getinfo(1,"nSluf");return b.name,b.namewhat,b.what,b.currentline,b.func==f,b.nparams,b.isvararg end;return f(1)'],
 ['getinfo-depth', 'return debug.getinfo(999),debug.getinfo(-1)'],
 ['getinfo-lines', 'local function f(a)\nlocal b=a+1\nreturn b\nend;local t=debug.getinfo(f,"L").activelines;return t[1],t[2],t[3],t[4],t[5]'],
 ['locals-functions', 'local function f(a,b,...)local c=1;return a end;return debug.getlocal(f,1),debug.getlocal(f,2),debug.getlocal(f,3),debug.getlocal(host_pair,1)'],
 ['locals-live', 'local function f(a,...)local b=17;local x,y=debug.getlocal(1,1);local q,r=debug.getlocal(1,2);local v,w=debug.getlocal(1,-1);return x,y,q,r,v,w end;return f(3,9)'],
 ['locals-mutate', 'local function f(a,...)local b=17;local x=debug.setlocal(1,1,33);local y=debug.setlocal(1,2,44);local z=debug.setlocal(1,-1,55);return a,b,...,x,y,z end;return f(3,9)'],
 ['locals-suspended', 'local co=coroutine.create(function(a,...)local b=17;coroutine.yield();return a,b,... end);coroutine.resume(co,3,9);local a,b=debug.getlocal(co,1,2);local n=debug.setlocal(co,1,2,44);return a,b,n,coroutine.resume(co)'],
 ['locals-invalid', 'local a,b=debug.getlocal(1,999);return a,b,debug.setlocal(1,999,1)'],
 ['upvalues', 'local x=17;local function f()return x end;local n,v=debug.getupvalue(f,1);local z=debug.setupvalue(f,1,33);return n,v,z,f(),debug.getupvalue(f,2),debug.setupvalue(f,2,1)'],
 ['upvalues-join', 'local x,y=17,33;local function f()return x end;local function g()return y end;local a=debug.upvalueid(f,1);local b=debug.upvalueid(g,1);debug.upvaluejoin(f,1,g,1);debug.setupvalue(g,1,44);return type(a),a==b,debug.upvalueid(f,1)==debug.upvalueid(g,1),f(),g(),debug.upvalueid(f,99)'],
 ['upvalues-env', 'local function f()return _VERSION end;local n=debug.setupvalue(f,1,{_VERSION="new"});return n,f()'],
 ['upvalues-c', 'local n,v=debug.getupvalue(host_capture,1);local a=debug.upvalueid(host_capture,1);debug.setupvalue(host_capture,1,33);return n,v,host_capture(),a==debug.upvalueid(host_capture,1),debug.upvalueid(host_pair,1)'],
 ['registry', 'return debug.getregistry()[2]==_G,type(debug.getregistry()[1]),debug.getregistry()==debug.getregistry()'],
 ['userdata', 'local u=host_userdata();local a,b=debug.getuservalue(u,1);local c=debug.setuservalue(u,17,1);local d,e=debug.getuservalue(u,1);return a,b,c==u,d,e,debug.getuservalue(u,3),debug.setuservalue(u,2,3),debug.getuservalue({},1)'],
 ['metatables', 'local t={};local m={__metatable="hidden"};debug.setmetatable(t,m);local a=getmetatable(t);local b=debug.getmetatable(t)==m;debug.setmetatable(1,{__index={x=17}});local x=(2).x;local c=getmetatable(3)==debug.getmetatable(1);debug.setmetatable(1,nil);return a,b,x,c,getmetatable(1)'],
 ['type-metatables', 'debug.setmetatable(false,{__index={x=17}});debug.setmetatable(nil,{__index={x=33}});local a=false;local b=nil;local x,y=a.x,b.x;debug.setmetatable(false,nil);debug.setmetatable(nil,nil);return x,y'],
 ['cstack', 'return debug.setcstacklimit(1),debug.setcstacklimit(-1),debug.setcstacklimit(10000)'],
 ['load-environment', 'local f,e=load("return x, _ENV", "=custom", "t", {x=17});local x,t=f();return e,x,t.x,debug.getinfo(f,"S").source'],
 ['load-reader', 'local t={"return ","17",",33"};local i=0;local f,e=load(function()i=i+1;return t[i]end);return e,f()'],
 ['load-reader-number', 'local i=0;local f,e=load(function()i=i+1;if i==1 then return "return " elseif i==2 then return 17 end end);return e,f()'],
 ['load-reader-early-unknown', 'local n=0;local f,e=load(function()n=n+1;if n==1 then return "@ trailing" end error("late reader")end);return f,e,n'],
 ['load-reader-early-local', 'local n=0;local f,e=load(function()n=n+1;if n==1 then return "local = trailing" end error("late reader")end);return f,e,n'],
 ['load-reader-early-return', 'local n=0;local f,e=load(function()n=n+1;if n==1 then return "return + trailing" end error("late reader")end);return f,e,n'],
 ['load-reader-lookahead', 'local n=0;local f,e=load(function()n=n+1;if n==1 then return "@" end error("late reader")end);return f,e,n'],
 ['load-reader-failure', 'local f,e=load(function()return {}end);return f,e'],
 ['load-mode', 'local f,e=load("return 1",nil,"b");return f,e'],
 ['load-binary', 'local f=load(string.dump(function(a)return a+1 end));return f(17),load(string.dump(function()end),nil,"t")'],
 ['invalid-options', 'local a,b=pcall(debug.getinfo,1,"z");local c,d=pcall(debug.getinfo,1,">S");return a,b,c,d'],
 ['invalid-level', 'local a,b=pcall(debug.getlocal,999,1);local c,d=pcall(debug.setlocal,999,1,2);return a,b,c,d'],
 ['invalid-upvaluejoin', 'local function f()return 1 end;local a,b=pcall(debug.upvaluejoin,f,1,f,1);return a,b'],
 ['invalid-integer', 'local a,b=pcall(debug.setcstacklimit,1.5);local c,d=pcall(debug.getlocal,1,1.5);return a,b,c,d'],
 ['invalid-metatable', 'local a,b=pcall(debug.setmetatable,{});return a,b'],
 ['base-retained-exports', 'local names={"assert","error","print","warn","collectgarbage","load","loadfile","dofile","getmetatable","rawget","setmetatable","xpcall"};local t={};for _,k in ipairs(names)do t[#t+1]=k..":"..type(_G[k])end;return table.concat(t,",")'],
 ['traceback-stack', 'local function f()return debug.traceback("message")end;return f()'],
 ['load-syntax','local f,e=load("return function(","=bad");return f,e'],
 ['load-empty-reader', 'local n=0;local f,e=load(function()n=n+1;return ""end);return e,n,f()'],
 ['traceback-nonstring', 'local t={};return debug.traceback(t)==t,debug.traceback(nil,999),debug.traceback(17,999)'],
 ['traceback-negative', 'return debug.traceback(nil,-1)'],
];
const file = resolve(scratch, 'file.lua'), bom = resolve(scratch, 'bom.lua');
for (const [index, source] of ['return "a', 'return 0xg', 'local =1', 'return +', 'function f( end', 'local function f(a) return a', 'local a<const> =1;a=2', 'local x<bad> =1', 'local x<close>,y<close> = nil,nil', 'break', 'goto a', '::a:: ::a::', 'goto a;local x;::a:: return x', 'return 1;local x=2', 'return [[unfinished'].entries()) cases.push(['invalid-source-' + index, `local f,e=load(${JSON.stringify(source)},"=bad");return f,e`]);
writeFileSync(file, 'return x,17'); writeFileSync(bom, Buffer.from('\xef\xbb\xbf#!/usr/bin/lua\nreturn 33', 'latin1'));
cases.push(['loadfile', `local f,e=loadfile(${JSON.stringify(file)},"t",{x=44});return e,f()`]);
cases.push(['stdin-loadfile','local f,e=loadfile();return e,f()']);
cases.push(['stdin-dofile','return dofile()']);
cases.push(['missing-file',`return loadfile(${JSON.stringify(resolve(scratch,'absent.lua'))})`]);
cases.push(['directory-file',`return loadfile(${JSON.stringify(scratch)})`]);
cases.push(['dofile', `return dofile(${JSON.stringify(bom)})`]);
function encode(value) { if (value === null) return 'nil'; if (typeof value === 'boolean') return 'boolean:' + +value; if (typeof value === 'bigint') return 'integer:' + value; if (typeof value === 'number') { const v = new DataView(new ArrayBuffer(8)); v.setFloat64(0, value); return 'float:' + v.getBigUint64(0).toString(16).padStart(16, '0'); } if (isLuaString(value)) return 'string:' + Buffer.from(luaStringBytes(value), 'latin1').toString('hex'); return 'type:' + luaType(value); }
let values = 0;
for (const [name, source] of cases) {
  const input = resolve(scratch, 'input.lua'); writeFileSync(input, source);
  const native = execFileSync(resolve(scratch, 'oracle'), [input], { encoding: 'utf8', input:'return 99' }).trimEnd();
  const vm = createLuaBytecodeVM({ baseError: true, baseMeta: true, baseGC: true });
  openDebugLibrary(vm); openBaseIO(vm, { readFile: path => {try{return new Uint8Array(readFileSync(path));}catch(e){e.strerror=e.code==='ENOENT'?'No such file or directory':e.code==='EISDIR'?'Is a directory':e.message;if(e.code==='EISDIR')e.luaOperation='read';throw e;}}, readStdin: () => 'return 99' });
  vm.setGlobal('host_pair',n=>[n+1n,n+2n]);
  const capture=()=>[capture.upvalues[0]];capture.upvalues=[17n];capture.luaGcRoots=capture.upvalues;vm.setGlobal('host_capture',capture);
  vm.setGlobal('host_userdata', () => [vm.heap.with(() => new LuaUserdata(new Uint8Array(4), null, [null, null]))]);
  // Native NetHack removes these NEVER entries after opening the base table.
  vm.setGlobal('print', null); vm.setGlobal('warn', null);
  let actual; try { actual = vm.execute(source, '@' + input).map(encode).join('\n'); } catch (error) { console.error('CASE',name,error.message,error.luaDebugFrames?.map(f=>({pc:f.pc,line:f.currentline})));process.exit(1); }
  assert.equal(actual, native, name); values += actual ? actual.split('\n').length : 0;
}
console.log(`PASS: ${cases.length} native retained debug/base-load cases / ${values} values; real closure cells, active/suspended locals, primitive metatables, userdata, file/BOM loading.`);
