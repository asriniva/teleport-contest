/** Private native5.4.8 oracle for implemented stack/registry/callback behavior. */
import assert from 'node:assert/strict';
import { mkdirSync, writeFileSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { fileURLToPath } from 'node:url';
import { resolve } from 'node:path';
import { createLuaCState, LUA_REGISTRYINDEX, lua_upvalueindex, LUA_MULTRET, LUA_OK, LUA_ERRRUN, LUA_ERRSYNTAX, LUA_TNUMBER, LUA_TSTRING } from '../js/services/lua/lapi.js';
import { LuaError, isLuaString, luaStringBytes } from '../js/services/lua/lobject.js';
const root = fileURLToPath(new URL('../', import.meta.url));
const scratch = resolve(root, '.cache/js-dependency-lua'); mkdirSync(scratch, { recursive: true });
const output = [];
function dump(L, label) {
  const values = [];
  for (let i = 1; i <= L.lua_gettop(); i++) {
    const type = L.lua_type(i), value = L.value(i);
    if (typeof value === 'bigint') values.push(`i${value}`);
    else if (isLuaString(value)) values.push('s' + Array.from(luaStringBytes(value), c => c.charCodeAt(0).toString(16).padStart(2, '0')).join(''));
    else if (typeof value === 'number') values.push(`f${value}`);
    else if (typeof value === 'boolean') values.push(`b${Number(value)}`);
    else values.push(`t${type}`);
  }
  output.push(`${label}:${values.join(',')}`);
}
const source = String.raw`
#include <stdio.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
static void dump(lua_State *L,const char *label) {
  printf("%s:",label);
  for(int i=1;i<=lua_gettop(L);i++) {
    if(i>1) printf(",");
    if(lua_isinteger(L,i)) printf("i%lld",(long long)lua_tointeger(L,i));
    else if(lua_type(L,i)==LUA_TSTRING) { size_t n;const unsigned char *s=(const unsigned char*)lua_tolstring(L,i,&n);printf("s");for(size_t j=0;j<n;j++)printf("%02x",s[j]); }
    else if(lua_type(L,i)==LUA_TNUMBER) printf("f%g",lua_tonumber(L,i));
    else if(lua_type(L,i)==LUA_TBOOLEAN) printf("b%d",lua_toboolean(L,i));
    else printf("t%d",lua_type(L,i));
  }
  puts("");
}
static int capture(lua_State *L) {
  lua_Integer a=luaL_checkinteger(L,1),u=lua_tointeger(L,lua_upvalueindex(1));
  lua_pushinteger(L,a+u);lua_pushinteger(L,a-u);return 2;
}
static int recurse(lua_State *L) {
  lua_Integer n=luaL_checkinteger(L,1);if(n==0){lua_pushinteger(L,1);return 1;}
  lua_getglobal(L,"recurse");lua_pushinteger(L,n-1);lua_call(L,1,1);lua_pushinteger(L,n*lua_tointeger(L,-1));return 1;
}
static int broken(lua_State *L) {lua_pushliteral(L,"broken");return lua_error(L);}
static int handler(lua_State *L) {lua_pushliteral(L,"handled");return 1;}
static int increment(lua_State *L) {lua_Integer x=lua_tointeger(L,lua_upvalueindex(1))+1;lua_pushinteger(L,x);lua_copy(L,-1,lua_upvalueindex(1));return 1;}
static int opener(lua_State *L) {lua_newtable(L);lua_pushinteger(L,17);lua_setfield(L,-2,"x");return 1;}
static int finalized=0;
static int gc_cb(lua_State *L){finalized++;return 0;}
static int check_absent(lua_State *L) {luaL_checkudata(L,1,"unregistered");return 0;}
int main(void){
  lua_State *L=luaL_newstate();luaL_openlibs(L);
  lua_pushinteger(L,10);lua_pushinteger(L,20);lua_pushinteger(L,30);dump(L,"push");
  lua_insert(L,1);dump(L,"insert");lua_remove(L,2);dump(L,"remove");lua_settop(L,4);dump(L,"grow-nil");lua_settop(L,-2);dump(L,"negative-top");lua_pushinteger(L,7);lua_replace(L,1);dump(L,"replace");lua_replace(L,-1);dump(L,"replace-top");lua_settop(L,0);
  lua_pushinteger(L,17);size_t len;lua_tolstring(L,-1,&len);lua_pushinteger(L,len);dump(L,"number-to-string");lua_pushlstring(L,"a\0b",3);dump(L,"embedded-nul");lua_settop(L,0);
  lua_newtable(L);lua_pushinteger(L,11);lua_setfield(L,-2,"a");lua_pushliteral(L,"b");lua_pushinteger(L,12);lua_settable(L,-3);lua_getfield(L,-1,"a");lua_getfield(L,-2,"b");dump(L,"table-fields");lua_settop(L,1);lua_pushliteral(L,"missing");lua_gettable(L,-2);dump(L,"missing-key");lua_settop(L,0);
  lua_pushinteger(L,5);lua_pushcclosure(L,capture,1);lua_pushinteger(L,12);lua_call(L,1,LUA_MULTRET);dump(L,"closure-upvalue-multi");lua_settop(L,0);
  lua_pushcfunction(L,recurse);lua_setglobal(L,"recurse");lua_getglobal(L,"recurse");lua_pushinteger(L,6);lua_call(L,1,1);dump(L,"reentrant-native");lua_settop(L,0);
  lua_pushinteger(L,40);lua_pushcclosure(L,increment,1);lua_pushvalue(L,-1);lua_call(L,0,1);lua_pushvalue(L,-2);lua_call(L,0,1);lua_remove(L,1);dump(L,"mutable-upvalue");lua_settop(L,0);
  lua_pushcfunction(L,broken);int rc=lua_pcall(L,0,2,0);lua_pushinteger(L,rc);dump(L,"protected-error");lua_settop(L,0);
  lua_pushcfunction(L,handler);lua_pushcfunction(L,broken);rc=lua_pcall(L,0,1,1);lua_pushinteger(L,rc);dump(L,"error-handler");lua_settop(L,0);
  luaL_loadstring(L,"return 7,8");rc=lua_pcall(L,0,3,0);lua_pushinteger(L,rc);dump(L,"load-results-padding");lua_settop(L,0);
  luaL_loadstring(L,"return 9,10");lua_call(L,0,0);dump(L,"discard-results");
  luaL_newmetatable(L,"payload");lua_pushliteral(L,"tag");lua_setfield(L,-2,"kind");lua_pop(L,1);lua_newuserdatauv(L,8,1);luaL_getmetatable(L,"payload");lua_setmetatable(L,-2);lua_getmetatable(L,-1);lua_getfield(L,-1,"kind");dump(L,"userdata-metatable");lua_settop(L,0);
  luaL_requiref(L,"testmodule",opener,1);lua_getfield(L,-1,"x");lua_getglobal(L,"testmodule");lua_getfield(L,-1,"x");dump(L,"require-registry");lua_settop(L,0);
  lua_pushinteger(L,123);lua_rawseti(L,LUA_REGISTRYINDEX,17);lua_rawgeti(L,LUA_REGISTRYINDEX,17);dump(L,"registry-index");lua_settop(L,0);
  luaL_loadstring(L,"_ENV={x=17}");lua_call(L,0,0);luaL_loadstring(L,"return x");lua_call(L,0,1);dump(L,"fresh-chunk-environment");lua_settop(L,0);
  luaL_loadstring(L,"shared=23");lua_call(L,0,0);luaL_loadstring(L,"return shared");lua_call(L,0,1);dump(L,"shared-global-table");lua_settop(L,0);
  lua_pushcfunction(L,check_absent);lua_newuserdatauv(L,4,0);rc=lua_pcall(L,1,0,0);lua_pushinteger(L,lua_type(L,-1));lua_pushinteger(L,rc);lua_remove(L,1);dump(L,"unregistered-userdata-rejected");lua_settop(L,0);
  lua_pushliteral(L,"identity");lua_pushboolean(L,lua_topointer(L,-1)!=NULL);lua_pushvalue(L,-2);lua_pushboolean(L,lua_topointer(L,-1)==lua_topointer(L,1));dump(L,"string-pointer");lua_settop(L,0);
  lua_pushthread(L);lua_pushboolean(L,lua_topointer(L,-1)!=NULL);dump(L,"thread-pointer");lua_settop(L,0);
  lua_newuserdatauv(L,4,0);lua_newtable(L);lua_pushcfunction(L,gc_cb);lua_setfield(L,-2,"__gc");lua_setmetatable(L,-2);lua_settop(L,0);lua_gc(L,LUA_GCCOLLECT);lua_pushinteger(L,finalized);dump(L,"userdata-finalization");lua_settop(L,0);
  lua_pushinteger(L,17);rc=lua_resetthread(L);lua_pushinteger(L,rc);dump(L,"reset-main-stack");lua_settop(L,0);
  lua_gc(L,LUA_GCSTOP);lua_checkstack(L,20);char longs[101];for(int i=0;i<100;i++)longs[i]='Q';longs[100]=0;
  lua_pushlstring(L,longs,100);int before=lua_gc(L,LUA_GCCOUNT)*1024+lua_gc(L,LUA_GCCOUNTB);lua_pushlstring(L,longs,100);int after=lua_gc(L,LUA_GCCOUNT)*1024+lua_gc(L,LUA_GCCOUNTB);lua_pushboolean(L,lua_topointer(L,1)!=lua_topointer(L,2));lua_pushboolean(L,lua_rawequal(L,1,2));lua_pushinteger(L,after-before);dump(L,"long-string-identity-allocation");lua_settop(L,0);
  lua_pushlstring(L,longs,40);before=lua_gc(L,LUA_GCCOUNT)*1024+lua_gc(L,LUA_GCCOUNTB);lua_pushlstring(L,longs,40);after=lua_gc(L,LUA_GCCOUNT)*1024+lua_gc(L,LUA_GCCOUNTB);lua_pushboolean(L,lua_topointer(L,1)==lua_topointer(L,2));lua_pushinteger(L,after-before);dump(L,"short-string-intern");lua_settop(L,0);
  lua_pushlstring(L,longs,100);lua_pushlstring(L,longs,100);lua_newtable(L);lua_pushvalue(L,1);lua_pushinteger(L,17);lua_rawset(L,3);lua_pushvalue(L,2);lua_rawget(L,3);lua_pushnil(L);lua_next(L,3);lua_pushboolean(L,lua_topointer(L,-2)==lua_topointer(L,1));dump(L,"long-string-content-key");lua_settop(L,0);
  lua_pushlightuserdata(L,(void*)0x1234);lua_pushlightuserdata(L,(void*)0x1234);lua_newtable(L);lua_pushvalue(L,1);lua_pushinteger(L,23);lua_rawset(L,3);lua_pushvalue(L,2);lua_rawget(L,3);lua_pushboolean(L,lua_rawequal(L,1,2));dump(L,"lightuserdata-content-key");lua_settop(L,0);
  lua_pushboolean(L,1);lua_newtable(L);lua_newtable(L);lua_pushinteger(L,29);lua_setfield(L,-2,"x");lua_setfield(L,-2,"__index");lua_setmetatable(L,-2);lua_settop(L,0);lua_gc(L,LUA_GCCOLLECT);lua_pushboolean(L,0);lua_getfield(L,-1,"x");dump(L,"primitive-type-metatable");lua_settop(L,0);
  int rotate_growth=lua_checkstack(L,150000);for(int i=1;i<=150000;i++)lua_pushinteger(L,i);lua_rotate(L,1,1);lua_Integer r1=lua_tointeger(L,1),r2=lua_tointeger(L,2),r3=lua_tointeger(L,150000);lua_rotate(L,1,-70000);lua_Integer r4=lua_tointeger(L,1),r5=lua_tointeger(L,150000);lua_settop(L,0);lua_pushinteger(L,rotate_growth);lua_pushinteger(L,r1);lua_pushinteger(L,r2);lua_pushinteger(L,r3);lua_pushinteger(L,r4);lua_pushinteger(L,r5);dump(L,"large-stack-rotation");lua_settop(L,0);
  int bigbefore=lua_gc(L,LUA_GCCOUNT)*1024+lua_gc(L,LUA_GCCOUNTB);unsigned char*largepayload=lua_newuserdatauv(L,10000001,0);largepayload[0]=42;largepayload[10000000]=99;int bigafter=lua_gc(L,LUA_GCCOUNT)*1024+lua_gc(L,LUA_GCCOUNTB);lua_pushinteger(L,lua_rawlen(L,1));lua_pushinteger(L,bigafter-bigbefore);lua_pushboolean(L,largepayload[0]==42&&largepayload[10000000]==99);dump(L,"large-userdata-no-artificial-cap");lua_settop(L,0);
  lua_close(L);return 0;
}
`;
writeFileSync(resolve(scratch, 'oracle-api.c'), source);
execFileSync('python3', [resolve(root, 'scripts/test-js-lua-native.py'), 'oracle-api'], { stdio: 'inherit' });
const expected = execFileSync(resolve(scratch, 'oracle-api'), [], { encoding: 'utf8' }).trimEnd();
const L = createLuaCState({ libraries: true, baseError: true, baseMeta: true });
L.lua_pushinteger(10n); L.lua_pushinteger(20n); L.lua_pushinteger(30n); dump(L, 'push');
L.lua_insert(1); dump(L, 'insert'); L.lua_remove(2); dump(L, 'remove'); L.lua_settop(4); dump(L, 'grow-nil'); L.lua_settop(-2); dump(L, 'negative-top'); L.lua_pushinteger(7n); L.lua_replace(1); dump(L, 'replace'); L.lua_replace(-1); dump(L, 'replace-top'); L.lua_settop(0);
L.lua_pushinteger(17n); const length = {}; L.lua_tolstring(-1, length); L.lua_pushinteger(length.value); dump(L, 'number-to-string'); L.lua_pushlstring('a\0b', 3); dump(L, 'embedded-nul'); L.lua_settop(0);
L.lua_newtable(); L.lua_pushinteger(11n); L.lua_setfield(-2, 'a'); L.lua_pushliteral('b'); L.lua_pushinteger(12n); L.lua_settable(-3); L.lua_getfield(-1, 'a'); L.lua_getfield(-2, 'b'); dump(L, 'table-fields'); L.lua_settop(1); L.lua_pushliteral('missing'); L.lua_gettable(-2); dump(L, 'missing-key'); L.lua_settop(0);
const capture = S => { const a = S.luaL_checkinteger(1), u = S.lua_tointeger(lua_upvalueindex(1)); S.lua_pushinteger(a + u); S.lua_pushinteger(a - u); return 2; };
L.lua_pushinteger(5n); L.lua_pushcclosure(capture, 1); L.lua_pushinteger(12n); L.lua_call(1, LUA_MULTRET); dump(L, 'closure-upvalue-multi'); L.lua_settop(0);
const recurse = S => { const n = S.luaL_checkinteger(1); if (n === 0n) { S.lua_pushinteger(1n); return 1; } S.lua_getglobal('recurse'); S.lua_pushinteger(n - 1n); S.lua_call(1, 1); S.lua_pushinteger(n * S.lua_tointeger(-1)); return 1; };
L.lua_pushcfunction(recurse); L.lua_setglobal('recurse'); L.lua_getglobal('recurse'); L.lua_pushinteger(6n); L.lua_call(1, 1); dump(L, 'reentrant-native'); L.lua_settop(0);
const increment = S => { const n = S.lua_tointeger(lua_upvalueindex(1)) + 1n; S.lua_pushinteger(n); S.lua_copy(-1, lua_upvalueindex(1)); return 1; };
L.lua_pushinteger(40n); L.lua_pushcclosure(increment, 1); L.lua_pushvalue(-1); L.lua_call(0, 1); L.lua_pushvalue(-2); L.lua_call(0, 1); L.lua_remove(1); dump(L, 'mutable-upvalue'); L.lua_settop(0);
const broken = S => { S.lua_pushliteral('broken'); return S.lua_error(); };
const handler = S => { S.lua_pushliteral('handled'); return 1; };
L.lua_pushcfunction(broken); let rc = L.lua_pcall(0, 2, 0); L.lua_pushinteger(rc); dump(L, 'protected-error'); L.lua_settop(0);
L.lua_pushcfunction(handler); L.lua_pushcfunction(broken); rc = L.lua_pcall(0, 1, 1); L.lua_pushinteger(rc); dump(L, 'error-handler'); L.lua_settop(0);
L.luaL_loadstring('return 7,8'); rc = L.lua_pcall(0, 3, 0); L.lua_pushinteger(rc); dump(L, 'load-results-padding'); L.lua_settop(0);
L.luaL_loadstring('return 9,10'); L.lua_call(0, 0); dump(L, 'discard-results');
L.luaL_newmetatable('payload'); L.lua_pushliteral('tag'); L.lua_setfield(-2, 'kind'); L.lua_pop(1); const userdata = L.lua_newuserdatauv(8, 1); L.luaL_getmetatable('payload'); L.lua_setmetatable(-2); L.lua_getmetatable(-1); L.lua_getfield(-1, 'kind'); dump(L, 'userdata-metatable'); assert.equal(L.luaL_checkudata(1, 'payload'), userdata); L.lua_settop(0);
const opener = S => { S.lua_newtable(); S.lua_pushinteger(17n); S.lua_setfield(-2, 'x'); return 1; };
L.luaL_requiref('testmodule', opener, 1); L.lua_getfield(-1, 'x'); L.lua_getglobal('testmodule'); L.lua_getfield(-1, 'x'); dump(L, 'require-registry'); L.lua_settop(0);
L.lua_pushinteger(123n); L.lua_rawseti(LUA_REGISTRYINDEX, 17); L.lua_rawgeti(LUA_REGISTRYINDEX, 17); dump(L, 'registry-index'); L.lua_settop(0);
L.luaL_loadstring('_ENV={x=17}'); L.lua_call(0, 0); L.luaL_loadstring('return x'); L.lua_call(0, 1); dump(L, 'fresh-chunk-environment'); L.lua_settop(0);
L.luaL_loadstring('shared=23'); L.lua_call(0, 0); L.luaL_loadstring('return shared'); L.lua_call(0, 1); dump(L, 'shared-global-table'); L.lua_settop(0);
L.lua_pushcfunction(S => { S.luaL_checkudata(1, 'unregistered'); return 0; }); L.lua_newuserdatauv(4, 0); rc = L.lua_pcall(1, 0, 0); L.lua_pushinteger(L.lua_type(-1)); L.lua_pushinteger(rc); L.lua_remove(1); dump(L, 'unregistered-userdata-rejected'); L.lua_settop(0);
L.lua_pushliteral('identity'); L.lua_pushboolean(L.lua_topointer(-1)!==null); L.lua_pushvalue(-2); L.lua_pushboolean(L.lua_topointer(-1)===L.lua_topointer(1)); dump(L,'string-pointer');L.lua_settop(0);
L.push(L.vm.mainThread);L.lua_pushboolean(L.lua_topointer(-1)!==null);dump(L,'thread-pointer');L.lua_settop(0);
let finalized=0;L.lua_newuserdatauv(4,0);L.lua_newtable();L.lua_pushcfunction(()=>{finalized++;return 0});L.lua_setfield(-2,'__gc');L.lua_setmetatable(-2);L.lua_settop(0);L.lua_gc(2);L.lua_pushinteger(finalized);dump(L,'userdata-finalization');L.lua_settop(0);
L.lua_pushinteger(17);const reset=L.lua_resetthread();L.lua_pushinteger(reset);dump(L,'reset-main-stack');L.lua_settop(0);
L.lua_gc(0);L.lua_checkstack(20);const longs='Q'.repeat(100);L.lua_pushlstring(longs,100);const before=L.lua_gc(3)*1024+L.lua_gc(4);L.lua_pushlstring(longs,100);const after=L.lua_gc(3)*1024+L.lua_gc(4);L.lua_pushboolean(L.lua_topointer(1)!==L.lua_topointer(2));L.lua_pushboolean(L.lua_rawequal(1,2));L.lua_pushinteger(after-before);dump(L,'long-string-identity-allocation');L.lua_settop(0);
L.lua_pushlstring(longs,40);const sb=L.lua_gc(3)*1024+L.lua_gc(4);L.lua_pushlstring(longs,40);const sa=L.lua_gc(3)*1024+L.lua_gc(4);L.lua_pushboolean(L.lua_topointer(1)===L.lua_topointer(2));L.lua_pushinteger(sa-sb);dump(L,'short-string-intern');L.lua_settop(0);
L.lua_pushlstring(longs,100);L.lua_pushlstring(longs,100);L.lua_newtable();L.lua_pushvalue(1);L.lua_pushinteger(17);L.lua_rawset(3);L.lua_pushvalue(2);L.lua_rawget(3);L.lua_pushnil();L.lua_next(3);L.lua_pushboolean(L.lua_topointer(-2)===L.lua_topointer(1));dump(L,'long-string-content-key');L.lua_settop(0);
L.lua_pushlightuserdata(0x1234n);L.lua_pushlightuserdata(0x1234n);L.lua_newtable();L.lua_pushvalue(1);L.lua_pushinteger(23);L.lua_rawset(3);L.lua_pushvalue(2);L.lua_rawget(3);L.lua_pushboolean(L.lua_rawequal(1,2));dump(L,'lightuserdata-content-key');L.lua_settop(0);
L.lua_pushboolean(true);L.lua_newtable();L.lua_newtable();L.lua_pushinteger(29);L.lua_setfield(-2,'x');L.lua_setfield(-2,'__index');L.lua_setmetatable(-2);L.lua_settop(0);L.lua_gc(2);L.lua_pushboolean(false);L.lua_getfield(-1,'x');dump(L,'primitive-type-metatable');L.lua_settop(0);
const rotateGrowth=L.lua_checkstack(150000);for(let i=1;i<=150000;i++)L.lua_pushinteger(i);L.lua_rotate(1,1);const r1=L.lua_tointeger(1),r2=L.lua_tointeger(2),r3=L.lua_tointeger(150000);L.lua_rotate(1,-70000);const r4=L.lua_tointeger(1),r5=L.lua_tointeger(150000);L.lua_settop(0);for(const value of [rotateGrowth,r1,r2,r3,r4,r5])L.lua_pushinteger(value);dump(L,'large-stack-rotation');L.lua_settop(0);
const bigBefore=L.lua_gc(3)*1024+L.lua_gc(4),largePayload=L.lua_newuserdatauv(10000001,0);largePayload[0]=42;largePayload[10000000]=99;const bigAfter=L.lua_gc(3)*1024+L.lua_gc(4);L.lua_pushinteger(L.lua_rawlen(1));L.lua_pushinteger(bigAfter-bigBefore);L.lua_pushboolean(largePayload[0]===42&&largePayload[10000000]===99);dump(L,'large-userdata-no-artificial-cap');L.lua_settop(0);
assert.equal(output.join('\n'), expected);
assert.equal(L.luaL_loadstring('local ='), LUA_ERRSYNTAX); assert.equal(L.lua_type(-1), LUA_TSTRING); L.lua_pop(1);
L.lua_pushcfunction(broken); assert.equal(L.lua_pcall(0, 0), LUA_ERRRUN); assert.equal(L.lua_tostring(-1), 'broken'); L.lua_pop(1);
assert.equal(L.luaL_loadstring('return 17'), LUA_OK); L.lua_call(0, 1); assert.equal(L.lua_type(-1), LUA_TNUMBER); assert.equal(L.lua_tointeger(-1), 17n);
assert.equal(L.lua_absindex(-1), 1); assert.equal(L.lua_type(2), -1); assert.equal(L.lua_toboolean(2), false);
assert.equal(L.lua_checkstack(5000), 1); L.lua_settop(5000); assert.equal(L.lua_gettop(), 5000); assert.equal(L.lua_type(5000), 0);
for (const method of [ 'lua_sethook', 'lua_getstack', 'lua_getinfo', 'lua_getallocf', 'lua_atpanic', 'lua_setwarnf', 'luaL_traceback', 'luaL_openlibs']) assert.throws(() => L[method](), LuaError, method);
L.lua_close(); assert.equal(L.vm.heap.memoryTracker.bytes,0);
console.log(`PASS: ${output.length} native Lua5.4.8 stack/registry/callback snapshots, plus load-error status, missing-index conversion, growth and explicit unsupported-facility errors.`);
console.log('Scope: logical C-API stack/registry/callback behavior. The separate ABI, debug, native allocator and buffer gates cover their own paths; C continuations remain outside the configured symbol contract.');
