/** Differential execution of the bounded Lua core against unmodified Lua5.4.8. */
import assert from 'node:assert/strict';
import { readFileSync, writeFileSync, mkdirSync, readdirSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { fileURLToPath } from 'node:url';
import { resolve } from 'node:path';
import { createLua, parse, LuaTable, LuaUserdata, LuaError, isLuaString, luaStringBytes } from '../js/services/lua/lua.js';

const root = fileURLToPath(new URL('../', import.meta.url));
const scratch = resolve(root, '.cache/js-dependency-lua'); mkdirSync(scratch, { recursive: true });
writeFileSync(resolve(scratch, 'oracle.c'), String.raw`
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
static void output(lua_State *L, int at) {
    switch(lua_type(L, at)) {
    case LUA_TNIL: puts("nil"); break;
    case LUA_TBOOLEAN: printf("boolean:%d\n",lua_toboolean(L,at)); break;
    case LUA_TNUMBER:
      if(lua_isinteger(L,at)) printf("integer:%lld\n",(long long)lua_tointeger(L,at));
      else { double number=lua_tonumber(L,at); uint64_t bits; memcpy(&bits,&number,8); printf("float:%016llx\n",(unsigned long long)bits); }
      break;
    case LUA_TSTRING: {
      size_t length; const unsigned char *s=(const unsigned char*)lua_tolstring(L,at,&length);
      printf("string:"); for(size_t i=0;i<length;i++) printf("%02x",s[i]); puts(""); break;
    }
    default: printf("type:%s\n",lua_typename(L,lua_type(L,at))); break;
    }
}
static int host_samepointer(lua_State *L) {lua_pushboolean(L,lua_topointer(L,1)==lua_topointer(L,2));return 1;}
static int host_pair(lua_State *L) { lua_Integer a=luaL_checkinteger(L,1); lua_pushinteger(L,a+1); lua_pushinteger(L,a+2); return 2; }
static int host_call(lua_State *L) { lua_pushvalue(L,1); lua_call(L,0,LUA_MULTRET); return lua_gettop(L)-1; }
int main(int argc,char **argv) {
    lua_State *L=luaL_newstate(); luaL_openlibs(L);
    lua_pushcfunction(L,host_samepointer);lua_setglobal(L,"host_samepointer");
    lua_pushcfunction(L,host_pair); lua_setglobal(L,"host_pair");
    lua_pushcfunction(L,host_call); lua_setglobal(L,"host_call");
    if(argc<2) return 3;
    int rc=luaL_loadfile(L,argv[1]);
    if(rc==LUA_OK && (argc<3 || strcmp(argv[2],"--parse"))) rc=lua_pcall(L,0,LUA_MULTRET,0);
    if(rc!=LUA_OK) { fprintf(stderr,"%s\n",lua_tostring(L,-1)); lua_close(L); return 2; }
    if(argc<3 || strcmp(argv[2],"--parse")) for(int i=1;i<=lua_gettop(L);i++) output(L,i);
    lua_close(L); return 0;
}
`);
execFileSync('python3', [resolve(root, 'scripts/test-js-lua-native.py')], { stdio: 'inherit' });
const oracle = resolve(scratch, 'oracle');
let cases = 0, values = 0;
function encoded(value) {
  if (value === null) return 'nil';
  if (typeof value === 'bigint') return `integer:${value}`;
  if (typeof value === 'boolean') return `boolean:${Number(value)}`;
  if (isLuaString(value)) return 'string:' + Array.from(luaStringBytes(value), c => c.charCodeAt(0).toString(16).padStart(2, '0')).join('');
  if (typeof value === 'number') { const buffer = new ArrayBuffer(8), view = new DataView(buffer); view.setFloat64(0, value); return 'float:' + view.getBigUint64(0).toString(16).padStart(16, '0'); }
  if (value instanceof LuaTable) return 'type:table';
  if (value instanceof LuaUserdata) return 'type:userdata';
  if (typeof value === 'function' || value?.luaClosure) return 'type:function';
  throw new Error('unhandled test value');
}
function compare(name, source, { vm = createLua({ baseError: true, baseMeta: true, instructionLimit: 3000000 }) } = {}) {
  const input = resolve(scratch, 'input.lua'); writeFileSync(input, source);
  const native = execFileSync(oracle, [input], { encoding: 'utf8', maxBuffer: 8 * 1024 * 1024 }).trimEnd();
  vm.setGlobal('host_samepointer',(a,b)=>[a===b]);
  vm.setGlobal('host_pair', value => [value + 1n, value + 2n]);
  vm.setGlobal('host_call', fn => vm.call(fn));
  const actual = vm.execute(source, name).map(encoded).join('\n');
  assert.equal(actual, native, name); cases++; values += actual ? actual.split('\n').length : 0;
  return vm;
}

const core = [
  ['nan-sign-in-pack',`return string.pack("d",-(0/0))`],
  ['nan-payload-pack',String.raw`local n=string.unpack('<d',"\x01\x00\x00\x00\x00\x00\xf0\x7f");return string.pack('<d',n),string.pack('<d',-n),math.type(n)`],
  ['longstring-identity','local a=string.rep("a",100);local b=string.rep("a",100);return a==b,rawequal(a,b),host_samepointer(a,b),host_samepointer(a,tostring(a)),#a,tonumber(string.rep("0",100).."17")'],
  ['longstring-literal-identity','local a="aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";local b="aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";local function f()return "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"end;return host_samepointer(a,b),host_samepointer(a,f())'],
  ['longstring-content-table-key','local a=string.rep("k",100);local b=string.rep("k",100);local t={[a]=17};local key=next(t);return t[b],host_samepointer(a,key),host_samepointer(b,key),table.concat({a,b})==a..b'],
  ['longstring-pattern-utf8','local s=string.rep("a",60).."17";local it=string.gmatch(s,"(%d+)");local first=it();local n=0;for i,c in utf8.codes(s)do n=n+1 end;return first,n,string.gsub(s,"a",string.rep("b",50),1),string.format("%s",s)'],
  ['many-results-unpack',String.raw`return select('#',string.unpack(string.rep('B',150000),string.rep('\0',150000)))`],
  ['many-arguments-libraries','local t={};for i=1,150000 do t[i]=65 end;return #string.char(table.unpack(t)),math.min(table.unpack(t)),#table.pack(table.unpack(t))'],
  ['tostring-name-and-pointer','local t=setmetatable({},{__name="Thing"});return string.sub(tostring(t),1,6),tostring(t)=="Thing: "..string.format("%p",t)'],
  ['xpcall-recursive-handler-recovers','local n=0;local ok,e=xpcall(function()error(17)end,function(e)n=n+1;if n<3 then error(e+1,0)end;return e+1 end);return ok,e,n'],
  ['xpcall-recursive-handler-overflow','local n=0;local ok,e=xpcall(function()error(17)end,function(e)n=n+1;error(e,0)end);return n,ok,e'],
  ['xpcall-coroutine-handler-overflow','local n=0;local co=coroutine.create(function()return xpcall(function()error(17)end,function()n=n+1;return coroutine.yield()end)end);local a,b,c=coroutine.resume(co);return n,a,b,c'],
  ['xpcall-resumed-handler-overflow','local n=0;local co=coroutine.create(function()return xpcall(function()coroutine.yield();error(17)end,function(e)n=n+1;error(e,0)end)end);coroutine.resume(co);local a,b,c=coroutine.resume(co);return n,a,b,c'],
  ['error-level-source','local function f()error("message")end;local ok,e=pcall(f);local ok2,e2=pcall(function()error("plain",0)end);return ok,type(e),string.match(e,":%d+: message$")~=nil,ok2,e2'],
  ['error-level-nonstring','local ok,e=pcall(function()error(17,10)end);return ok,e'],
  ['error-level-caller','local function f()error("message",2)end;local function g()local x=f();return x end;local ok,e=pcall(g);return ok,string.match(e,":%d+: message$")~=nil'],
  ['tostring-numeric-metamethod','return tostring(setmetatable({},{__tostring=function()return 17 end})),tostring(setmetatable({},{__tostring=function()return 1.25 end}))'],
  ['integers', 'return 9223372036854775807, 9223372036854775807+1, 0xffffffffffffffff, -0x8000000000000000, -7//3, -7%3, 7//-3, 7%-3'],
  ['shifts', 'return -1 >> 1, -1 << 63, 1 << 64, 1 >> -3, 1 << -64, ~0, (0x123456789abcdef0 & 0xff), 2^10'],
  ['float-types', 'return 1.0, 1e0, 0x1.8p1, 1/2, 7.0//2, 1+0.5, math.type(1),math.type(1.0), math.tointeger(1.5), math.tointeger(1.0)'],
  ['numeric-strings', 'return "2"+3, "0xffffffffffffffff"+1, tonumber("  -12 "), tonumber("8000000000000000",16), tonumber("bad"), tonumber("1.5"), tonumber("0x1.8p2")'],
  ['truth', 'return not nil, not false, not 0, 0 and 7, "" or 8, nil or 3, false and host_pair(4), 1<2, 1.0==1, 9007199254740993 > 9007199254740992.0'],
  ['precedence', 'return -2^2, 2^-2, 2^3^2, 2+3*4, "a"..1+2, 1|2&4, false or true and false'],
  ['parallel-assignment', 'local i,a=1,{10,20}; i,a[i]=i+1,30; a[1],a[2]=a[2],a[1]; return i,a[1],a[2]'],
  ['closure-cells', 'local x=2; local f=function() return x end; local x=3; local function g() x=x+1;return x end; return f(),g(),g(),x'],
  ['recursive', 'local function f(n) if n<2 then return 1 end return n*f(n-1) end return f(10)'],
  ['multiresults', 'local function f(...) return ... end; local a,b,c,d=f(1,2),f(3,4); local t={f(5,6)}; return a,b,c,d,#t,t[1],t[2],(f(7,8)),f(9,10)'],
  ['varargs', 'local function f(a,...) return a,select("#",...),... end return f(1,nil,3,nil)'],
  ['host-callback', 'local a,b=host_pair(41); return a,b,host_pair(b)'],
  ['loop-controls', 'local s=0; for i=10,1,-2 do s=s+i end; local j=0; while j<5 do j=j+1;if j==3 then break end;s=s+j end;repeat local q=s+1;s=q until q>40; return s,j'],
  ['loop-closures', 'local f={};for i=1,3 do f[i]=function()return i end end;return f[1](),f[2](),f[3]()'],
  ['generic-loop', 'local s=0; for i,v in ipairs({10,20,30}) do s=s+i*v end; return s'],
  ['environment', 'local _ENV={x=17}; x=x+1;return x,_ENV.x'],
  ['methods', 'local t={x=3};function t:add(y) self.x=self.x+y;return self.x end; return t:add(4),t.x'],
  ['byte-strings', 'local s="a\\0\\255\\x80b";return #s,string.byte(s,1,-1),string.sub(s,-3),string.reverse(s),string.char(0,255,65)'],
  ['escaped-strings', 'return "\\u{1F600}", "a\\z  \n  b",[=[\nlong\nstring]=], "\\065\\x42\\n"'],
  ['table-pack-nils', 'local t=table.pack(1,nil,3);return t.n,t[1],t[2],t[3]'],
  ['table-sequence', 'local t=table.pack(1,2,3);table.insert(t,2,4);local x=table.remove(t,2);return t.n,t[1],t[2],t[3],x,table.unpack({4,5,6})'],
  ['table-move', 'local t={1,2,3,4};table.move(t,1,3,2);return table.unpack(t)'],
  ['table-concat', 'return table.concat({"a",2,3.0},":"),string.rep("x",3,"-"),string.upper("aZ\\255"),string.lower("Az")'],
  ['string-format', 'return string.format("%04d:%#x:%#o:%u:%-5s",-7,255,8,-1,"xy"),("abcdef"):sub(2,4)'],
  ['metamethod-index', 'local fallback={z=7};local t=setmetatable({x=1},{__index=fallback,__newindex=function(a,k,v)rawset(a,k,v*2)end});t.y=3;t.x=2;return t.z,t.y,t.x'],
  ['metamethod-arithmetic', 'local mt={__add=function(a,b)return a.x+b.x end,__unm=function(a)return -a.x end,__len=function(a)return a.x end};local a=setmetatable({x=3},mt);local b=setmetatable({x=4},mt);return a+b,-a,#a'],
  ['metamethod-call-compare', 'local mt={__call=function(a,x)return a.x+x end,__lt=function(a,b)return a.x<b.x end,__le=function(a,b)return a.x<=b.x end,__eq=function(a,b)return a.x==b.x end};local a=setmetatable({x=3},mt);local b=setmetatable({x=3},mt);return a(4),a==b,a<=b'],
  ['lua54-no-le-fallback', 'local a=setmetatable({},{__lt=function()return false end});local ok=pcall(function()return a<=a end);return ok'],
  ['protected-errors', 'local ok,x=pcall(function()error("broken",0)end);local ok2=pcall(function()return 1//0 end);return ok,x,ok2,xpcall(function()error(17)end,function(e)return e+1 end)'],
  ['math-integers', 'return math.abs(-0x8000000000000000),math.floor(-2.5),math.ceil(-2.5),math.min(3,2.0,4),math.max(3,2.0),math.fmod(-7,3),math.ult(-1,0),math.modf(-2.75)'],
  ['const-read', 'local x<const> =17; return x'],
  ['pattern-find', 'return string.find("abc 123 def","(%a+)%s+(%d+)"),string.find("abc","^b",2),string.find("a.b",".",1,true)'],
  ['pattern-match-captures', 'return string.match("one=123 two=45","(%a+)=(%d+)"),string.match("abc","()b()"),string.match("abc","")'],
  ['pattern-greedy-minimal', 'return string.match("a123b456b","a(.*)b"),string.match("a123b456b","a(.-)b"),string.match("ab","ab?"),string.match("a","ab*")'],
  ['pattern-balanced-frontier', 'return string.match("x(a(b)c)y","%b()"),string.match("one twoword!","%f[%a]two%a*"),string.match("a.b","a%.b")'],
  ['pattern-backreference', 'return string.match("word word!","(%a+)%s+%1"),string.match("aaa","(a+)%1"),string.match("123abc","[^%d]+")'],
  ['pattern-classes', 'return string.match("A9f! ","%u%d%x%p%s"),string.match("x\\0y","%z"),string.match("\\255","%A"),string.match("]-q","[]-]+")'],
  ['pattern-gmatch', 'local t={};for a,b in string.gmatch("a=12;b=34","(%a)=(%d+)")do t[#t+1]=a..b end;return table.concat(t,"|"),string.match("foo","f(o+)$")'],
  ['pattern-empty-gmatch', 'local t={};for v in string.gmatch("ab",".-")do t[#t+1]=v end;return #t,table.concat(t,"|")'],
  ['pattern-gsub', 'return string.gsub("hello 123 world 456","(%a+)%s+(%d+)","%2:%1:%%:%0")'],
  ['pattern-gsub-function', 'local t={};local s,n=string.gsub("a1b2c3","(%a)(%d)",function(a,b)t[#t+1]=a..b;return b..a end,2);return s,n,table.concat(t,"|")'],
  ['pattern-gsub-table', 'return string.gsub("cat dog cat","%a+",{cat="lion",dog=false})'],
  ['pattern-empty-gsub', 'return string.gsub("abc","","-"),string.gsub("abc","^","+"),string.gsub("abc","a*","X")'],
  ['pattern-invalid', 'local a=pcall(string.match,"abc","[");local b=pcall(string.match,"abc","%1");local c=pcall(string.match,"abc","(abc");return a,b,c'],
  ['sort-callback-order', 'local t={7,2,5,1,9,3,8,4,6};local trace={};table.sort(t,function(a,b)trace[#trace+1]=a..":"..b;return a<b end);return table.concat(t,","),table.concat(trace,"|")'],
  ['sort-duplicates', 'local t={3,1,3,2,1,2};local trace={};table.sort(t,function(a,b)trace[#trace+1]=a..":"..b;return a>b end);return table.concat(t,","),table.concat(trace,"|")'],
  ['utf8-basic', 'local s=utf8.char(65,0xe9,0x1f600);return #s,utf8.len(s),utf8.codepoint(s,1,-1)'],
  ['utf8-offsets', 'local s=utf8.char(65,0xe9,0x1f600);return utf8.offset(s,1),utf8.offset(s,2),utf8.offset(s,3),utf8.offset(s,4),utf8.offset(s,-1),utf8.offset(s,0,4),utf8.offset(s,5)'],
  ['utf8-codes', 'local t={};for p,c in utf8.codes(utf8.char(65,0xe9,0x1f600))do t[#t+1]=p;t[#t+1]=c end;return table.unpack(t)'],
  ['utf8-strict-lax', 'local s=utf8.char(0xd800,0x110000,0x7fffffff);local n,p=utf8.len(s);return n,p,utf8.len(s,1,-1,true),utf8.codepoint(s,1,-1,true)'],
  ['utf8-invalid', 'local n,p=utf8.len("a\\128");local a=pcall(utf8.codepoint,"\\192\\128");local b=pcall(utf8.offset,"a\\128",1,2);return n,p,a,b'],
  ['float-domain-bits','return 0/0,-(0/0),math.log(-1),math.sqrt(-1),math.asin(2),math.acos(2),tostring(0/0),tostring(math.log(-1)),tostring(-(0/0))'],
  ['float-decimal-halfways','return tostring(1.00000000000005),tostring(9.99999999999995),tostring(99999999999999.5),tostring(0.0000999999999999995),tostring(2.2250738585072014e-308),tostring(4.9406564584124654e-324),tostring(1.7976931348623157e308)'],
  ['float-string-formatting', 'return tostring(0.0),tostring(-0.0),tostring(1.25),tostring(1e-5),tostring(1e-4),tostring(1e13),tostring(1e14),tostring(2.5e-5),tostring(1.234567890123456),tostring(4503599627370496.0)'],
  ['coroutine-arguments', 'local co=coroutine.create(function(a,...)local x,y=coroutine.yield(a+1,...);return x*2,y end);local a,b,c,d=coroutine.resume(co,3,4,nil);local e,f,g=coroutine.resume(co,7,8);return a,b,c,d,e,f,g,coroutine.status(co)'],
  ['coroutine-state', 'local main,ismain=coroutine.running();local co;co=coroutine.create(function()local self,m=coroutine.running();return self==co,m,coroutine.status(self),coroutine.status(main),coroutine.isyieldable()end);local before=coroutine.status(co);local a,b,c,d,e,f=coroutine.resume(co);return ismain,coroutine.isyieldable(),before,a,b,c,d,e,f,coroutine.status(co),coroutine.isyieldable(co)'],
  ['coroutine-no-replay', 'local count=0;local co=coroutine.create(function()for i=1,3 do count=count+1;local x=coroutine.yield(count,i);count=count+x end;return count end);local a,b,c=coroutine.resume(co);local d,e,f=coroutine.resume(co,10);local g,h,i=coroutine.resume(co,20);local j,k=coroutine.resume(co,30);return a,b,c,d,e,f,g,h,i,j,k,count'],
  ['coroutine-closure-upvalues', 'local x=1;local read;local co=coroutine.create(function()local y=10;read=function()return x,y end;coroutine.yield();x=x+2;y=y+3;coroutine.yield();return read()end);coroutine.resume(co);local a,b=read();x=5;coroutine.resume(co);local c,d=read();local ok,e,f=coroutine.resume(co);return a,b,c,d,ok,e,f'],
  ['coroutine-nested-calls', 'local function f(n)if n==0 then return coroutine.yield(17)end;local x=f(n-1);return x+n end;local co=coroutine.create(function()return f(4)end);local a,b=coroutine.resume(co);local c,d=coroutine.resume(co,20);return a,b,c,d'],
  ['coroutine-protected-yield', 'local co=coroutine.create(function()return pcall(function()local x=coroutine.yield(7);return x+1 end)end);local a,b=coroutine.resume(co);local c,d,e=coroutine.resume(co,9);return a,b,c,d,e'],
  ['coroutine-error-after-yield', 'local co=coroutine.create(function()local ok,x=pcall(function()coroutine.yield(3);error(17)end);return ok,x end);local a,b=coroutine.resume(co);local c,d,e=coroutine.resume(co);local f,g=coroutine.resume(co);return a,b,c,d,e,f,g'],
  ['coroutine-xpcall-yield', 'local co=coroutine.create(function()return xpcall(function()coroutine.yield(4);error(21)end,function(x)return x+1 end)end);local a,b=coroutine.resume(co);local c,d,e=coroutine.resume(co);return a,b,c,d,e'],
  ['coroutine-nested-resume', 'local a,b;a=coroutine.create(function()b=coroutine.create(function()local ok=coroutine.resume(a);return coroutine.status(a),ok end);return coroutine.resume(b)end);return coroutine.resume(a)'],
  ['coroutine-wrap', 'local w=coroutine.wrap(function(x)local y=coroutine.yield(x+1,x+2);return y+3 end);local a,b=w(10);local c=w(20);local ok=pcall(w);return a,b,c,ok'],
  ['coroutine-wrap-error', 'local w=coroutine.wrap(function()coroutine.yield(3);error(17)end);local a=w();local ok,x=pcall(w);return a,ok,x'],
  ['coroutine-metamethod-yield', 'local co=coroutine.create(function()local t=setmetatable({},{__index=function(a,k)local x=coroutine.yield(k);return x+1 end});return t.key end);local a,b=coroutine.resume(co);local c,d=coroutine.resume(co,8);return a,b,c,d'],
  ['coroutine-arithmetic-yield', 'local co=coroutine.create(function()local a=setmetatable({},{__add=function()return coroutine.yield(5)end});return (a+a)*2 end);local a,b=coroutine.resume(co);local c,d=coroutine.resume(co,8);return a,b,c,d'],
  ['coroutine-c-boundary', 'local co=coroutine.create(function()return pcall(host_call,function()coroutine.yield(4)end)end);local a,b,c=coroutine.resume(co);return a,b,string.match(c,"across a C%-call boundary")~=nil,coroutine.status(co)'],
  ['coroutine-gsub-boundary', 'local co=coroutine.create(function()local ok,e=pcall(string.gsub,"a",".",function()coroutine.yield(5)end);return ok,string.match(e,"across a C%-call boundary")~=nil end);return coroutine.resume(co)'],
  ['coroutine-rng-side-effects', 'math.randomseed(8000,17);local trace={};local co=coroutine.create(function()for i=1,5 do local r=math.random(1000);trace[#trace+1]=r;local x=coroutine.yield(r);trace[#trace+1]=x end end);for i=1,6 do coroutine.resume(co,i*10)end;return table.concat(trace,",")'],
  ['coroutine-zero-nil-results', 'local co=coroutine.create(function()coroutine.yield();return nil,17,nil end);local a,b=coroutine.resume(co);return a,b,coroutine.resume(co)'],
  ['coroutine-main-errors', 'local a=pcall(coroutine.yield);local b=pcall(coroutine.isyieldable,nil);local c=pcall(coroutine.resume,17);return a,b,c'],
  ['coroutine-nonyieldable-check', 'local co=coroutine.create(function()return host_call(function()return coroutine.isyieldable()end)end);return coroutine.resume(co)'],
  ['coroutine-xpcall-handler-boundary', 'local co=coroutine.create(function()return xpcall(function()error(17)end,function()return coroutine.yield()end)end);return coroutine.resume(co)'],
  ['pairs-delete-array-key', 'local t={10,20};local count=0;for k,v in pairs(t)do t[k]=nil;count=count+1 end;return count,next(t)==nil'],
  ['pairs-delete-hash-key', 'local t={a=1,b=2};local count=0;for k in pairs(t)do t[k]=nil;count=count+1 end;return count,next(t)==nil'],
  ['pairs-integer-node-order', 'local t={};for _,k in ipairs({-10,1000,3,1,2,0,64,17,-1,4,1001})do t[k]=k end;local s={};for k,v in pairs(t)do s[#s+1]=k end;return table.concat(s,",")'],
  ['holed-array-borders', 'local t={1,nil,3};local a=#t;t[3]=nil;local b=#t;t[2]=2;local c=#t;return a,b,c'],
  ['next-deleted-array-index', 'local t={1,nil,3};t[1]=nil;local k,v=next(t,1);return k,v,next(t,2)'],
  ['table-pack-holed-mutation', 'local t=table.pack(1,nil,3);table.insert(t,2,4);local x=table.remove(t,2);return t.n,#t,t[1],t[2],t[3],x'],
  ['table-constructor-multireturn-holes', 'local function f()return 1,nil,3 end;local t={f()};return #t,t[1],t[2],t[3]'],
  ['library-optional-nil', 'return string.sub("abc",1,nil),string.rep("a",2,nil),string.byte("abc",nil,nil),table.unpack({1,2},nil,nil)'],
  ['unicode-space-is-not-c-space', 'return tonumber("\\16012\\160"),tonumber("\\160ff\\160",16),tonumber(" \\t12\\n")'],
  ['float-modulo-infinite-zero', 'return 1.0%math.huge,-0.0%1.0,-1.0%math.huge'],
  ['for-infinite-limits', 'local a,b,c=0,0,0;for i=1,-math.huge do a=a+1 end;for i=1,math.huge do b=b+1;break end;for i=1,math.huge,-1 do c=c+1 end;return a,b,c'],
  ['for-numeric-string-control', 'local t={};for i="1","3" do t[#t+1]=math.type(i)end;return table.concat(t,",")'],
  ['for-bound-evaluation-order', 'local t={};local function f(s,n)t[#t+1]=s;return n end;for i=f("start",1),f("limit",0),f("step",1)do end;return table.concat(t,",")'],
  ['bitwise-no-string-coercion', 'local a=pcall(function()return "0xff"&3 end);local b=pcall(function()return ~"3"end);return a,b'],
  ['format-does-not-use-global-tostring', 'tostring=function()return "wrong"end;return string.format("%s",17)'],
];
for (const [name, source] of core) compare(name, source);

// Integer overflow/shift/division boundaries and exact mixed comparisons.
const integerValues = ['0', '1', '-1', '9223372036854775807', '-9223372036854775807-1', '9007199254740993'];
for (const value of integerValues) for (const other of ['1', '3', '-3', '63', '64'])
  compare(`numeric-${value}-${other}`, `local a,b=${value},${other};return a+b,a-b,a*b,a//b,a%b,a<<b,a>>b,a==b,a<b,a<=b`);
for (const seed of [0n, 1n, 42n, 8000n, -1n]) {
  let source = `local a,b=math.randomseed(${seed},17);local r={a,b};`;
  source += 'for i=1,40 do r[#r+1]=math.random(1,37);r[#r+1]=math.random(0);r[#r+1]=math.random() end;return table.unpack(r)';
  compare(`xoshiro-${seed}`, source);
}
// Array growth/shrink and integer hash collisions are independent of Lua's
// address-derived string seed, so their exact iteration can be compared.
for (const size of [1, 2, 3, 5, 7, 9, 17, 33, 65])
  compare(`integer-table-resizes-${size}`, `local t={};for i=${size},1,-1 do t[i]=i end;local a=#t;for i=2,${size},2 do t[i]=nil end;local b=#t;local s={};for k in pairs(t)do s[#s+1]=k end;return a,b,table.concat(s,",")`);

// Parsing original scripts exercises syntax only; this does not assert their
// game bindings or resulting levels are implemented.
const dat = resolve(root, 'nethack-c/upstream/dat'); let scripts = 0;
for (const filename of readdirSync(dat).filter(name => name.endsWith('.lua'))) {
  const path = resolve(dat, filename); parse(readFileSync(path, 'utf8'), filename);
  execFileSync(oracle, [path, '--parse'], { stdio: 'pipe' }); scripts++;
}

const nhlib = readFileSync(resolve(dat, 'nhlib.lua'), 'utf8');
const rngPrefix = `
local rngstate=17; rngtrace={};
nh={};
function nh.rn2(n) rngstate=(rngstate*1664525+1013904223)&0xffffffff;local r=rngstate%n;rngtrace[#rngtrace+1]=n;rngtrace[#rngtrace+1]=r;return r end
function nh.random(a,n) return a+nh.rn2(n) end
u={role="Monk",depth=10};nhc={COLNO=80,ROWNO=21};
`;
compare('original-nhlib-helpers', rngPrefix + nhlib + `
local x,y,z=d(6),d(2,6),percent(50);
return x,y,z,monkfoodshop(),align[1],align[2],align[3],table.unpack(rngtrace)
`);
compare('original-tutorial-deletes-current-key', rngPrefix + nhlib + `
local calls=0;obj={new=function()calls=calls+1;return {placeobj=function()calls=calls+1 end}end};
nh.pline=function()calls=calls+1 end;nh.eckey=function()return "e"end;
u.uhunger=100;u.ux=1;u.uy=1;tutorial_turn();tutorial_turn();return calls
`);
compare('original-nhcore-self-removing-callback', rngPrefix + nhlib + readFileSync(resolve(dat, 'nhcore.lua'), 'utf8') + `
local calls=0;function self_remove()calls=calls+1;nh_callback_rm("end_turn","self_remove");return true end
nh_callback_set("end_turn","self_remove");local a=nh_callback_run("end_turn");local b=nh_callback_run("end_turn");return a,b,calls
`);
// Original quest data is executed, not a decoded/precomputed JS replacement.
compare('original-quest-data', readFileSync(resolve(dat, 'quest.lua'), 'utf8') + '\nreturn questtext.common.TEST_PATTERN.text,questtext.Arc.assignquest.text,questtext.Wiz.offeredit.text');

// A simple original generation script is run with explicitly diagnostic mock
// bindings that record requests. This verifies script control/data flow and RNG
// ordering, NOT map generation or NetHack binding equivalence.
const diagnosticBindings = `
trace={};des={};selection={};
local function record(name,...)
  local args={...}; local s=name..":"..#args;
  for i,v in ipairs(args) do
    if type(v)=="table" then s=s..":"..(v.style or v.fromterrain or "")..":"..(v.fg or v.toterrain or "")
    elseif type(v)=="string" then s=s..":"..#v..":"..v
    else s=s..":"..tostring(v) end
  end
  trace[#trace+1]=s;
end
local names={"level_init","level_flags","map","replace_terrain","feature","region","stair","non_diggable","object","trap","monster"};
for _,name in ipairs(names) do des[name]=function(...)record(name,...)end end
function selection.area(...)record("area",...);return {}end
`;
compare('original-bigrm4-diagnostic-bindings', rngPrefix + nhlib + diagnosticBindings + readFileSync(resolve(dat, 'bigrm-4.lua'), 'utf8') + '\nreturn table.concat(trace,"|"),table.unpack(rngtrace)');

// Actual JavaScript host callbacks, state isolation and restricted-safe globals.
const hostCalls = [];
const host = createLua({ globals: { nh: new LuaTable([['rn2', n => { hostCalls.push(n); return [n - 1n]; }], ['random', (a, n) => { hostCalls.push(a, n); return [a + n - 1n]; }]]) } });
host.execute(nhlib, 'nhlib.lua');
assert.deepEqual(hostCalls, [3n, 2n]);
assert.deepEqual(host.execute('return d(6),d(2,6),percent(50)'), [6n, 12n, false]);
assert.deepEqual(hostCalls, [3n, 2n, 1n, 6n, 1n, 6n, 1n, 6n, 0n, 100n]);
for (const absent of ['print', 'warn', 'load', 'loadfile', 'dofile', 'io', 'os', 'package', 'debug', 'collectgarbage', 'setmetatable']) assert.equal(host.getGlobal(absent), null, `sandbox ${absent}`);
assert.equal(createLua().getGlobal('d'), null, 'independent states');
let nativeSideEffects = 0;
const suspended = createLua({ globals: { host_tick: () => [BigInt(++nativeSideEffects)] } });
suspended.execute('co=coroutine.create(function()coroutine.yield(host_tick());coroutine.yield(host_tick());return 17 end)');
assert.equal(nativeSideEffects, 0);
assert.deepEqual(suspended.execute('return coroutine.resume(co)'), [true, 1n]); assert.equal(nativeSideEffects, 1);
assert.deepEqual(suspended.execute('return coroutine.resume(co)'), [true, 2n]); assert.equal(nativeSideEffects, 2);
assert.deepEqual(suspended.execute('return coroutine.resume(co)'), [true, 17n]); assert.equal(nativeSideEffects, 2, 'resuming frames must never repeat host side effects');
assert.throws(() => createLua({ instructionLimit: 100 }).execute('while true do end'), LuaError);
assert.throws(() => createLua().execute('local x<const> =1;x=2'), LuaError);
const environments = createLua(); environments.execute('_ENV={x=17}'); assert.deepEqual(environments.execute('return x'), [null], 'each loaded chunk gets an independent _ENV cell');
for (const invalid of ['return "\\xQ0"', 'return 12abc', 'local = 1', 'break', 'return ... end', 'function f() return ... end'])
  assert.throws(() => parse(invalid), LuaError);
for (const unsupported of ['::label:: goto label']) assert.throws(() => parse(unsupported), LuaError);

console.log(`PASS: ${cases} execution cases / ${values} returned values match native Lua5.4.8 bit-for-bit; all ${scripts} original scripts parse in both engines.`);
console.log('PASS: original nhlib helper execution and RNG trace, original quest data and bigrm-4 diagnostic callback trace, host callbacks, sandbox globals, instruction bound and explicit unsupported-syntax rejection.');
console.log('Incomplete core: no production NetHack bindings, C continuations, full C-pointer ABI, native allocator layout/cadence, AST opcode emission or exact seeded table hash iteration. GC/close/phase controls have separate native differential suites. No game/default integration or recording-equivalence claim.');
