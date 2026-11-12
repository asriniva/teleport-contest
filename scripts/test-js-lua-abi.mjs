/* Private configured Lua5.4.8 C ABI differential probe. No active build writes.
 * Requires the pinned Emscripten SDK and Lua archive already used by the game.
 * Run with the SDK Node24 (memory64); native comparison never supplies JS
 * expectations and uses the same unchanged C caller. */
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath, pathToFileURL } from 'node:url';
import { spawnSync } from 'node:child_process';
import { createLuaAbi } from '../js/lua/abi.js';
import { createLuaBytecodeVM } from '../js/lua/bytecode-vm.js';

const root = fileURLToPath(new URL('../', import.meta.url));
const bytecode = process.argv.includes('--bytecode');
const work = path.join(root, '.cache/js-lua-abi'); fs.mkdirSync(work, { recursive: true });
const sdk = process.env.EMSDK || path.join(root, '.cache/emsdk');
const lua = path.join(root, '.cache/wasm64-build/tree/lib/lua-5.4.8/src');
const env = { ...process.env, EMSDK: sdk, PATH: path.join(sdk, 'node/24.19.0_64bit/bin') + path.delimiter + process.env.PATH };
function command(program, args) {
  const result = spawnSync(program, args, { encoding: 'utf8', env, timeout: 120000 });
  assert.equal(result.status, 0, `${program}: ${result.error || result.stderr || result.stdout}`); return result.stdout;
}
const source = String.raw`
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
typedef struct { int calls,fail,live; lua_State *state; size_t limit; int fail_after; } allocator_data;
static void *allocate(void *ud,void *p,size_t old,size_t n) {
  (void)old; allocator_data *data=ud;data->calls++;
  if(!n){if(p)data->live--;free(p);return NULL;}
  if(data->fail || (data->fail_after && data->calls>=data->fail_after))return NULL;
  if(data->state && data->limit && (size_t)(lua_gc(data->state,LUA_GCCOUNT)*1024+lua_gc(data->state,LUA_GCCOUNTB))>data->limit)return NULL;
  void *result=realloc(p,n);if(result && !p)data->live++;return result;
}
static void dump(lua_State *L,const char *name) {
  printf("%s:",name);
  for(int i=1;i<=lua_gettop(L);i++) {
    if(i>1)putchar(',');
    if(lua_isinteger(L,i))printf("i%lld",(long long)lua_tointeger(L,i));
    else if(lua_type(L,i)==LUA_TSTRING){size_t n;const unsigned char *s=(const unsigned char*)lua_tolstring(L,i,&n);putchar('s');for(size_t j=0;j<n;j++)printf("%02x",s[j]);}
    else if(lua_type(L,i)==LUA_TNUMBER)printf("f%.17g",lua_tonumber(L,i));
    else if(lua_type(L,i)==LUA_TBOOLEAN)printf("b%d",lua_toboolean(L,i));
    else printf("t%d",lua_type(L,i));
  } putchar('\n');
}
static int capture(lua_State *L){lua_Integer a=luaL_checkinteger(L,1),u=lua_tointeger(L,lua_upvalueindex(1));lua_pushinteger(L,a+u);lua_pushinteger(L,a-u);return 2;}
static int recurse(lua_State *L){lua_Integer n=luaL_checkinteger(L,1);if(!n){lua_pushinteger(L,1);return 1;}lua_getglobal(L,"recurse");lua_pushinteger(L,n-1);lua_call(L,1,1);lua_pushinteger(L,n*lua_tointeger(L,-1));return 1;}
static int continued;
static int broken(lua_State *L){lua_pushliteral(L,"broken");lua_error(L);continued++;return 0;}
static int handler(lua_State *L){lua_pushliteral(L,"handled");return 1;}
static int opener(lua_State *L){lua_newtable(L);lua_pushinteger(L,17);lua_setfield(L,-2,"x");return 1;}
static int sum(lua_State *L){int64_t *p=luaL_checkudata(L,1,"native");lua_pushinteger(L,p[0]+p[1]);return 1;}
static int check_absent(lua_State *L){luaL_checkudata(L,1,"missing");return 0;}
static int check_badarg(lua_State *L){luaL_checkinteger(L,1);continued++;return 0;}
static int describe(lua_State *L){lua_Debug ar;if(!lua_getstack(L,1,&ar))return 0;lua_getinfo(L,"Slu",&ar);lua_pushinteger(L,ar.currentline);lua_pushinteger(L,ar.linedefined);lua_pushinteger(L,ar.lastlinedefined);lua_pushstring(L,ar.what);lua_pushstring(L,ar.short_src);lua_pushinteger(L,ar.nparams);lua_pushboolean(L,ar.isvararg);return 7;}
static int identify(lua_State *L){lua_pushboolean(L,(void*)L==lua_topointer(L,1));return 1;}
static int traceback(lua_State *L){luaL_traceback(L,L,lua_tostring(L,1),0);return 1;}
static char warnings[100];static void warn(void *ud,const char *msg,int continued){(void)continued;strcat((char*)ud,msg);}
static int hooks[5];static void hook(lua_State *L,lua_Debug *ar){(void)L;if(ar->event>=0 && ar->event<5)hooks[ar->event]++;}
static int newblock(lua_State *L){lua_newuserdatauv(L,1024*1024,0);return 1;}
static int mirror_block(lua_State *L){char text[256];memset(text,'a',sizeof text);lua_pushlstring(L,text,sizeof text);return 1;}
int budget_probe(void){allocator_data data={0};lua_State *L=lua_newstate(allocate,&data);if(!L)return -1;data.state=L;lua_pushcfunction(L,mirror_block);int rc=lua_pcall(L,0,1,0);lua_close(L);return rc;}
static int finalized;
static int finalizer(lua_State *L){int64_t *p=luaL_checkudata(L,1,"tracked");finalized=finalized*10+(int)*p;if(*p==7){lua_pushvalue(L,1);lua_setglobal(L,"resurrected");}return 0;}
static void tracked(lua_State *L,int id,const char *name){int64_t *p=lua_newuserdatauv(L,sizeof *p,0);*p=id;luaL_getmetatable(L,"tracked");lua_setmetatable(L,-2);lua_setglobal(L,name);}
static const luaL_Reg funcs[]={{"sum",sum},{"broken",broken},{"disabled",NULL},{NULL,NULL}};
static void safe_libs(lua_State *L){
  luaL_requiref(L,"_G",luaopen_base,1);lua_pop(L,1);
  luaL_requiref(L,"table",luaopen_table,1);lua_pop(L,1);
  luaL_requiref(L,"string",luaopen_string,1);lua_pop(L,1);
  luaL_requiref(L,"math",luaopen_math,1);lua_pop(L,1);
  luaL_requiref(L,"utf8",luaopen_utf8,1);lua_pop(L,1);
  luaL_requiref(L,"coroutine",luaopen_coroutine,1);lua_pop(L,1);
}
int main(void){
  allocator_data data={0};lua_State *L=lua_newstate(allocate,&data);if(!L)return 10;data.state=L;
  void *ud=NULL;lua_Alloc af=lua_getallocf(L,&ud);
  printf("allocator:%d,%d\n",af==allocate,ud==&data);
  safe_libs(L);luaL_checkversion(L);
  lua_setwarnf(L,warn,warnings);lua_warning(L,"one",1);lua_warning(L,"two",0);printf("warning-callback:%s\n",warnings);
  lua_pushinteger(L,INT64_MIN);lua_pushinteger(L,INT64_MAX);lua_pushnumber(L,1.25);lua_pushboolean(L,0);lua_pushboolean(L,-1);dump(L,"scalars");lua_settop(L,0);
  const uintptr_t opaque_values[]={0,1,UINT64_C(0x8000000000000000),UINT64_MAX};
  for(int i=0;i<4;i++){void *opaque=(void*)opaque_values[i];lua_pushlightuserdata(L,opaque);lua_pushlightuserdata(L,opaque);
    printf("lightuserdata-%d:%d,%d,%d,%d,%d\n",i,lua_type(L,-1)==LUA_TLIGHTUSERDATA,lua_isuserdata(L,-1),lua_touserdata(L,-1)==opaque,lua_topointer(L,-1)==opaque,lua_rawequal(L,-1,-2));lua_settop(L,0);}
  lua_pushlightuserdata(L,(void*)UINT64_C(0xfedcba9876543210));lua_setglobal(L,"opaque1");lua_pushlightuserdata(L,(void*)UINT64_C(0xfedcba9876543210));lua_setglobal(L,"opaque2");
  luaL_loadstring(L,"local t={};local w=setmetatable({},{__mode='v'});do local a={};w[1]=a;t[opaque1]=a end;t[opaque2]=23;collectgarbage();return opaque1==opaque2,t[opaque1],w[1]==nil");lua_call(L,0,LUA_MULTRET);dump(L,"lightuserdata-table-key");lua_settop(L,0);
  lua_pushlightuserdata(L,(void*)0);lua_newtable(L);lua_pushinteger(L,73);lua_setfield(L,-2,"tag");lua_setmetatable(L,-2);lua_settop(L,0);
  lua_pushlightuserdata(L,(void*)UINT64_MAX);int have_mt=lua_getmetatable(L,-1);lua_getfield(L,-1,"tag");lua_pushboolean(L,have_mt);dump(L,"lightuserdata-shared-metatable");lua_settop(L,0);
  lua_pushlightuserdata(L,(void*)0);lua_pushnil(L);lua_setmetatable(L,-2);lua_pushboolean(L,lua_getmetatable(L,-1));dump(L,"lightuserdata-clear-metatable");lua_settop(L,0);
  char bytes[]={'a',0,(char)0x80,(char)0xff};const char *first=lua_pushlstring(L,bytes,4);bytes[0]='z';size_t n=0;const char *again=lua_tolstring(L,-1,&n);
  lua_pushboolean(L,first==again);lua_pushinteger(L,n);dump(L,"byte-string-copy");lua_settop(L,0);
  lua_pushinteger(L,17);size_t sn;lua_tolstring(L,-1,&sn);lua_pushinteger(L,sn);dump(L,"number-string");lua_settop(L,0);
  for(int length=40;length<=100;length=length==40?41:length==41?100:101){char text[100];memset(text,'q',sizeof text);const char *one=lua_pushlstring(L,text,length);const void *header=lua_topointer(L,-1);const char *two=lua_pushlstring(L,text,length);lua_pushvalue(L,-2);const char *same=lua_tolstring(L,-1,&sn);printf("string-identity-%d:%d,%d,%d,%d\n",length,one==two,one==same,header==lua_topointer(L,-1),(int)sn==length);lua_settop(L,0);}
  lua_pushliteral(L,"-9223372036854775808");int valid=-1;lua_Integer value=lua_tointegerx(L,-1,&valid);lua_pushinteger(L,value);lua_pushinteger(L,valid);dump(L,"integer-outparam");lua_settop(L,0);
  lua_pushliteral(L,"1.25");valid=-1;lua_Number num=lua_tonumberx(L,-1,&valid);lua_pushnumber(L,num);lua_pushinteger(L,valid);dump(L,"float-outparam");lua_settop(L,0);
  lua_pushinteger(L,5);lua_pushcclosure(L,capture,1);lua_pushinteger(L,12);lua_call(L,1,LUA_MULTRET);dump(L,"closure-capture");lua_settop(L,0);
  lua_pushcfunction(L,capture);const void *cfn=lua_topointer(L,-1);lua_setglobal(L,"same1");lua_pushcfunction(L,capture);lua_pushboolean(L,lua_topointer(L,-1)==cfn);dump(L,"light-c-function-identity");lua_settop(L,1);lua_setglobal(L,"same2");luaL_loadstring(L,"return same1==same2");lua_call(L,0,1);dump(L,"light-c-function-equality");lua_settop(L,0);
  lua_pushliteral(L,"pointer text");const char *text=lua_tostring(L,-1);printf("string-header-offset:%lld\n",(long long)(text-(const char*)lua_topointer(L,-1)));lua_settop(L,0);
  lua_pushcfunction(L,recurse);lua_setglobal(L,"recurse");lua_getglobal(L,"recurse");lua_pushinteger(L,6);lua_call(L,1,1);dump(L,"native-reentry");lua_settop(L,0);
  lua_pushcfunction(L,broken);int rc=lua_pcall(L,0,2,0);lua_pushinteger(L,rc);lua_pushinteger(L,continued);dump(L,"native-error");lua_settop(L,0);
  lua_pushcfunction(L,handler);lua_pushcfunction(L,broken);rc=lua_pcall(L,0,1,1);lua_pushinteger(L,rc);dump(L,"native-error-handler");lua_settop(L,0);
  lua_pushcfunction(L,check_badarg);lua_pushnil(L);rc=lua_pcall(L,1,0,0);lua_pushinteger(L,lua_type(L,-1));lua_pushinteger(L,rc);lua_pushinteger(L,continued);lua_remove(L,1);dump(L,"auxiliary-error");lua_settop(L,0);
  luaL_newlib(L,funcs);lua_setglobal(L,"native");
  luaL_newmetatable(L,"native");lua_pop(L,1);int64_t *p=lua_newuserdatauv(L,16,1);p[0]=17;p[1]=-4;luaL_getmetatable(L,"native");lua_setmetatable(L,-2);lua_setglobal(L,"payload");
  lua_getglobal(L,"payload");lua_pushinteger(L,lua_rawlen(L,-1));lua_pushboolean(L,lua_touserdata(L,-2)==p);lua_remove(L,1);dump(L,"native-userdata");lua_settop(L,0);
  const char *script="return native.sum(payload),native.disabled,table.concat({1,2,3},','),string.char(0,128,255),math.floor(2.9),utf8.len('abc')";
  rc=luaL_loadbuffer(L,script,strlen(script),"abi-probe");if(rc)return 11;rc=lua_pcall(L,0,LUA_MULTRET,0);if(rc)return 12;dump(L,"registered-library");lua_settop(L,0);
  volatile char *large=malloc(32*1024*1024);if(!large)return 13;large[0]=1;large[32*1024*1024-1]=2;free((void*)large);
  p[1]=25;luaL_loadstring(L,"return native.sum(payload)");lua_call(L,0,1);dump(L,"userdata-after-memory-growth");lua_settop(L,0);
  char pointer_text[80];snprintf(pointer_text,sizeof pointer_text,"%p",(void*)p);luaL_loadstring(L,"return string.format('%p',payload)");lua_call(L,0,1);printf("userdata-pointer-format:%d\n",strcmp(pointer_text,lua_tostring(L,-1))==0);lua_settop(L,0);
  lua_pushliteral(L,"pointer format");snprintf(pointer_text,sizeof pointer_text,"%p",lua_topointer(L,-1));lua_setglobal(L,"pointer_text");luaL_loadstring(L,"return string.format('%p',pointer_text)");lua_call(L,0,1);printf("string-pointer-format:%d\n",strcmp(pointer_text,lua_tostring(L,-1))==0);lua_settop(L,0);
  lua_pushcfunction(L,check_absent);lua_newuserdatauv(L,4,0);rc=lua_pcall(L,1,0,0);lua_pushinteger(L,lua_type(L,-1));lua_pushinteger(L,rc);lua_remove(L,1);dump(L,"unregistered-userdata");lua_settop(L,0);
  luaL_requiref(L,"testmodule",opener,1);lua_getfield(L,-1,"x");lua_getglobal(L,"testmodule");lua_getfield(L,-1,"x");dump(L,"require");lua_settop(L,0);
  lua_pushinteger(L,123);lua_rawseti(L,LUA_REGISTRYINDEX,17);lua_rawgeti(L,LUA_REGISTRYINDEX,17);dump(L,"registry");lua_settop(L,0);
  luaL_loadstring(L,"_ENV={x=17}");lua_call(L,0,0);luaL_loadstring(L,"return x");lua_call(L,0,1);dump(L,"fresh-environment");lua_settop(L,0);
  luaL_loadstring(L,"return coroutine.wrap(function() coroutine.yield(17);return 23 end)");lua_call(L,0,1);lua_setglobal(L,"co");luaL_loadstring(L,"return co(),co()");lua_call(L,0,LUA_MULTRET);dump(L,"coroutine");lua_settop(L,0);
  lua_pushcfunction(L,identify);lua_setglobal(L,"identify");luaL_loadstring(L,"local co=coroutine.create(function()return identify(coroutine.running())end);return identify(coroutine.running()),coroutine.resume(co)");lua_call(L,0,LUA_MULTRET);dump(L,"native-callback-thread-identity");lua_settop(L,0);
  lua_rawgeti(L,LUA_REGISTRYINDEX,LUA_RIDX_MAINTHREAD);printf("main-thread-registry:%d,%d\n",lua_type(L,-1)==LUA_TTHREAD,lua_topointer(L,-1)==(void*)L);lua_settop(L,0);
  lua_pushcfunction(L,describe);lua_setglobal(L,"describe");const char *debug="local function f()\n return describe()\nend\nreturn f()";luaL_loadbuffer(L,debug,strlen(debug),"=abi-debug");lua_call(L,0,LUA_MULTRET);dump(L,"native-debug-layout");lua_settop(L,0);
  lua_pushcfunction(L,traceback);luaL_loadbuffer(L,"native.broken()",15,"=abi-error");rc=lua_pcall(L,0,0,1);const char *trace=lua_tostring(L,-1);printf("native-traceback:%d,%d,%d\n",rc,strstr(trace,"broken\nstack traceback:")!=NULL,strstr(trace,"abi-error")!=NULL);lua_settop(L,0);
  luaL_requiref(L,"debug",luaopen_debug,1);lua_pop(L,1);luaL_loadstring(L,"local t={};return debug.traceback(t)==t,type(debug.traceback('note',0))");lua_call(L,0,LUA_MULTRET);dump(L,"debugging-library");lua_settop(L,0);
  lua_sethook(L,hook,LUA_MASKCALL|LUA_MASKRET,0);luaL_loadstring(L,"return 17");lua_call(L,0,1);lua_sethook(L,NULL,0,0);printf("native-hook-callback:%d,%d\n",hooks[LUA_HOOKCALL],hooks[LUA_HOOKRET]);lua_settop(L,0);
#ifdef TEST_BYTECODE
  luaL_loadstring(L,"return string.dump(function(a)return a*3+1 end,true)");lua_call(L,0,1);size_t binary_size;const char *binary=lua_tolstring(L,-1,&binary_size);char *copy=malloc(binary_size);memcpy(copy,binary,binary_size);lua_settop(L,0);
  rc=luaL_loadbufferx(L,copy,binary_size,"binary-copy","b");if(rc)return 20;lua_pushinteger(L,7);lua_call(L,1,1);dump(L,"late-string-dump-binary-load");lua_settop(L,0);
  rc=luaL_loadbufferx(L,copy,binary_size,"binary-copy","t");printf("binary-mode-rejection:%d,%d\n",rc,lua_type(L,-1));lua_settop(L,0);free(copy);
#endif
  luaL_newmetatable(L,"tracked");lua_pushcfunction(L,finalizer);lua_setfield(L,-2,"__gc");lua_pop(L,1);
  tracked(L,7,"t7");tracked(L,8,"t8");lua_gc(L,LUA_GCCOLLECT);printf("gc-rooted:%d\n",finalized);
  lua_pushnil(L);lua_setglobal(L,"t7");lua_pushnil(L);lua_setglobal(L,"t8");lua_gc(L,LUA_GCCOLLECT);printf("gc-order:%d\n",finalized);
  lua_gc(L,LUA_GCCOLLECT);lua_getglobal(L,"resurrected");printf("gc-resurrection:%d,%d\n",finalized,lua_type(L,-1));lua_settop(L,0);
  lua_pushnil(L);lua_setglobal(L,"resurrected");lua_gc(L,LUA_GCCOLLECT);printf("gc-no-refinalize:%d\n",finalized);
  /* Both allocation refusal and NetHack's current-count budget contract must
     produce real LUA_ERRMEM, recover, and preserve an existing stack value. */
  lua_pushliteral(L,"preserved");lua_pushcfunction(L,newblock);data.fail=1;rc=lua_pcall(L,0,1,0);data.fail=0;
  printf("allocator-failure:%d,%d,%s\n",rc,lua_type(L,-1),lua_tostring(L,1));lua_settop(L,0);
  lua_pushcfunction(L,newblock);data.limit=1;rc=lua_pcall(L,0,1,0);data.limit=0;
  printf("allocator-limit:%d,%d\n",rc,lua_type(L,-1));lua_settop(L,0);
  lua_pushinteger(L,71);dump(L,"allocation-recovery");lua_settop(L,0);
  tracked(L,9,"t9");lua_close(L);data.state=NULL;printf("close-order:%d\n",finalized);printf("close-allocations:%d\n",data.live);
  allocator_data denied={.fail=1};lua_State *missing=lua_newstate(allocate,&denied);printf("newstate-failure:%d,%d\n",missing==NULL,denied.live);
  allocator_data partial={.fail_after=3};missing=lua_newstate(allocate,&partial);printf("newstate-partial-failure:%d,%d\n",missing==NULL,partial.live);
  return 0;
}
`;
const probe = path.join(work, 'probe.c'); fs.writeFileSync(probe, source);
const compiler = process.env.CC || path.join(root, '.cache/wasm64-build/host-cc');
const nativeSources = fs.readdirSync(lua).filter(n => n.endsWith('.c') && n !== 'lua.c' && n !== 'luac.c').map(n => path.join(lua, n));
const native = path.join(work, 'native');
const defines = bytecode ? ['-DTEST_BYTECODE=1'] : [];
command(compiler, ['-O2', ...defines, '-I' + lua, probe, ...nativeSources, '-lm', '-o', native]);
const expected = command(native, []);
const factoryPath = path.join(work, 'probe.mjs');
command(path.join(sdk, 'upstream/emscripten/emcc'), ['-O2', '-g', ...defines, '-sMEMORY64=1', '-I' + lua, probe,
  path.join(root, 'nethack-c/wasm/lua-bridge.c'), '--js-library', path.join(root, 'nethack-c/wasm/lua-library.js'),
  '-sMODULARIZE=1', '-sEXPORT_ES6=1', '-sENVIRONMENT=node', '-sINVOKE_RUN=0', '-sALLOW_MEMORY_GROWTH=1',
  '-sEXPORTED_RUNTIME_METHODS=callMain', '-sEXPORTED_FUNCTIONS=_main,_malloc,_free,_budget_probe', '--emit-symbol-map', '-o', factoryPath]);
const wasm = fs.readFileSync(path.join(work, 'probe.wasm'));
const imports = WebAssembly.Module.imports(new WebAssembly.Module(wasm));
assert.ok(imports.some(i => i.name === 'teleport_lua_dispatch'));
const symbols = fs.readFileSync(path.join(work, 'probe.mjs.symbols'), 'utf8');
for (const name of ['luaV_execute', 'luaD_call', 'luaC_step', 'luaY_parser']) assert.ok(!symbols.includes(name), `compiled Lua algorithm ${name}`);
const factory = (await import(pathToFileURL(factoryPath).href + '?abi=' + Date.now())).default;
const runtimeOptions = bytecode ? {vmFactory:createLuaBytecodeVM} : {};
const runtime = createLuaAbi(runtimeOptions); const lines = [];
const module = await factory({ nethackLua: runtime, print: line => lines.push(line), printErr: line => process.stderr.write(line + '\n') });
module.callMain([]);
assert.equal(lines.join('\n') + '\n', expected);
for (const operation of ['lua_newstate','lua_pushcclosure','lua_newuserdatauv','lua_pcallk','luaL_setfuncs','luaL_loadbufferx']) assert.ok(runtime.counters[operation] > 0, operation);
const bounded = await factory({ nethackLua: createLuaAbi({...runtimeOptions,transportLimit:128}), print: () => {} });
assert.equal(bounded._budget_probe(), 4, 'bounded ABI transport must return LUA_ERRMEM through C pcall');
console.log(`PASS: ${lines.length} configured native Lua5.4.8 snapshots through actual memory64 C ABI (${bytecode?'opcode':'AST'} backend); callbacks/reentry/errors, byte strings/outparams, native userdata/memory growth, real GC/finalizers, forced allocator failures/limits and recovery; separate bounded transport error. No compiled Lua algorithms.`);
