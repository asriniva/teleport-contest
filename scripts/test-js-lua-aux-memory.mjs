// Independent original Lua5.4.8 full allocator/refusal traces for Lua auxiliary diagnostics.
// Production formatting uses neither this native compiler nor file access.
import assert from 'node:assert/strict';
import { createHash } from 'node:crypto';
import { mkdirSync, readFileSync, writeFileSync, readdirSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { fileURLToPath } from 'node:url';
import { resolve } from 'node:path';
import { createLuaCState } from '../js/lua/lapi.js';
import { createLuaBytecodeVM } from '../js/lua/bytecode-vm.js';
import { openBase } from '../js/lua/lbaselib.js';
import { openString } from '../js/lua/lstrlib.js';
import { createBaseIOFunctions } from '../js/lua/base-io.js';
import { isLuaString, luaStringBytes } from '../js/lua/lobject.js';
import {luaAuxError,luaArgError,luaTypeError,luaCheckInteger,luaCheckNumber,luaCheckString} from '../js/lua/aux-error.js';
import {openLuaOS} from '../js/lua/os-library.js';
import {createLuaOSServices} from '../js/lua/os-abi.js';
process.env.TZ='UTC';
const root = fileURLToPath(new URL('../', import.meta.url));
const work = resolve(root, '.cache/js-lua-aux-memory'); mkdirSync(work, { recursive: true });
const archive = resolve(root, '.cache/lua-5.4.8.tar.gz');
assert.equal(createHash('sha256').update(readFileSync(archive)).digest('hex'), '4f18ddae154e793e46eeab727c59ef1c0c0c2b744e7b94219710d76f530629ae');
execFileSync('python3', ['-c', 'import tarfile,sys\nwith tarfile.open(sys.argv[1]) as t:t.extractall(sys.argv[2],filter="data")', archive, work]);
const source = resolve(work, 'lua-5.4.8/src'), oracle = resolve(work, 'oracle');
writeFileSync(resolve(work, 'oracle.c'), String.raw`
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
typedef struct Block {void*p;size_t n;unsigned id;struct Block*next;} Block;
typedef struct Mem {Block*blocks;size_t bytes,attempt,fail;unsigned nextid;} Mem;
static void*alloc(void*ud,void*p,size_t old,size_t n){
 Mem*m=ud;Block**at=&m->blocks,*b=NULL;while(*at&&(*at)->p!=p)at=&(*at)->next;
 if(p){b=*at;if(!b||b->n!=old)abort();}
 if(n&&++m->attempt>=m->fail){printf("{\"event\":\"refused\",\"attempt\":%zu,\"old\":%zu,\"size\":%zu,\"bytes\":%zu}\n",m->attempt,old,n,m->bytes);return NULL;}
 void*q=n?realloc(p,n):(free(p),(void*)NULL);if(n&&!q)abort();
 unsigned id=b?b->id:n?++m->nextid:0;size_t previous=b?b->n:0;m->bytes+=n-previous;
 if(!n){if(b){*at=b->next;free(b);}}else{if(!b){b=malloc(sizeof(*b));b->id=id;b->next=m->blocks;m->blocks=b;}b->p=q;b->n=n;}
 printf("{\"event\":\"alloc\",\"id\":%u,\"old\":%zu,\"size\":%zu,\"bytes\":%zu}\n",id,old,n,m->bytes);return q;
}
static void phase(Mem*m,const char*name,int status){printf("{\"phase\":\"%s\",\"status\":%d,\"bytes\":%zu,\"attempts\":%zu}\n",name,status,m->bytes,m->attempt);}
static int writer(lua_State*L,const void*p,size_t n,void*ud){return fwrite(p,1,n,ud)!=n;}
static int aux_error(lua_State*L){return luaL_error(L,"%s:%d:%s",lua_tostring(L,1),(int)lua_tointeger(L,2),lua_tostring(L,3));}
static int aux_arg(lua_State*L){return luaL_argerror(L,(int)lua_tointeger(L,1),lua_tostring(L,2));}
static int aux_type(lua_State*L){return luaL_typeerror(L,1,"number");}
static int aux_int(lua_State*L){luaL_checkinteger(L,1);return 0;}
static int aux_num(lua_State*L){luaL_checknumber(L,1);return 0;}
static int aux_str(lua_State*L){luaL_checkstring(L,1);return 0;}
int main(int argc,char**argv){
 if(argc<3)return 2;FILE*f=fopen(argv[2],"rb");if(!f)return 3;fseek(f,0,SEEK_END);size_t n=ftell(f);rewind(f);char*data=malloc(n?n:1);if(fread(data,1,n,f)!=n)return 4;fclose(f);
 if(!strcmp(argv[1],"dump")){lua_State*L=luaL_newstate();int rc=luaL_loadbufferx(L,data,n,"@fixture.lua","t");if(rc){fprintf(stderr,"%s",lua_tostring(L,-1));return rc;}f=fopen(argv[3],"wb");rc=lua_dump(L,writer,f,0);fclose(f);lua_close(L);free(data);return rc;}
 Mem m={0};m.fail=(size_t)-1;lua_State*L=lua_newstate(alloc,&m);if(!L)abort();
 lua_pushcfunction(L,luaopen_base);lua_call(L,0,1);lua_pop(L,1);
 lua_pushcfunction(L,luaopen_string);lua_call(L,0,1);lua_setglobal(L,"string");
 lua_pushcfunction(L,luaopen_os);lua_call(L,0,1);lua_setglobal(L,"os");
 luaL_requiref(L,"_G",luaopen_base,1);lua_pop(L,1);luaL_requiref(L,"string",luaopen_string,1);lua_pop(L,1);
#define REG(n,f) lua_pushcfunction(L,f);lua_setglobal(L,n)
 REG("auxError",aux_error);REG("auxArg",aux_arg);REG("auxType",aux_type);REG("auxInt",aux_int);REG("auxNum",aux_num);REG("auxStr",aux_str);
 lua_pushlightuserdata(L,(void*)1);lua_setglobal(L,"light");
 int rc=luaL_loadbufferx(L,data,n,"@fixture.lua","b");phase(&m,"load",rc);if(rc)abort();
 if(argc>3&&strtoull(argv[3],NULL,10))m.fail=m.attempt+strtoull(argv[3],NULL,10);
 rc=lua_pcall(L,0,LUA_MULTRET,0);phase(&m,"run",rc);
 if(!rc){size_t len;const unsigned char*s=(const unsigned char*)lua_tolstring(L,-1,&len);if(!s)abort();printf("{\"resultLength\":%zu,\"resultHex\":\"",len);for(size_t i=0;i<len;i++)printf("%02x",s[i]);puts("\"}");}
 lua_close(L);phase(&m,"close",0);if(m.blocks||m.bytes)abort();free(data);return 0;
}
`);
execFileSync(resolve(root, '.cache/wasm64-build/host-cc'), ['-O2','-DLUA_USE_POSIX', '-I'+source, resolve(work,'oracle.c'), ...readdirSync(source).filter(n=>n.endsWith('.c')&&!['lua.c','luac.c'].includes(n)).map(n=>resolve(source,n)), '-lm', '-o', oracle]);
function traceJS(data, offset = 0) {
  const events = [], blocks = new Map(); let nextid = 0, bytes = 0, attempts = 0, fail = Infinity;
  const allocator = (_ud,p,old,n) => {
    if (p !== null) assert.equal(blocks.get(p)?.size,old);
    if (n && ++attempts >= fail) { events.push({event:'refused',attempt:attempts,old,size:n,bytes}); return null; }
    const id = p === null ? n ? ++nextid : 0 : blocks.get(p).id;
    bytes += n - (p === null ? 0 : old);
    events.push({event:'alloc',id,old,size:n,bytes});
    if (!n) { blocks.delete(p); return null; }
    const q = p ?? {id}; blocks.set(q,{id,size:n}); return q;
  };
  const L = createLuaCState({vmFactory:createLuaBytecodeVM,memoryAllocator:allocator});
  const phase = (name,status) => events.push({phase:name,status,bytes,attempts});
  L.lua_pushcfunction(S=>{openBase(S.vm,{baseError:true,baseMeta:true,baseGC:true,baseFunctions:createBaseIOFunctions(S.vm),nativeRegistration:true});S.push(S.vm.globals);return 1;});L.lua_call(0,1);L.lua_pop(1);
  L.lua_pushcfunction(S=>{S.push(openString(S.vm,{publish:false}));return 1;});L.lua_call(0,1);L.lua_setglobal('string');
  L.lua_pushcfunction(S=>{S.push(openLuaOS(S.vm,createLuaOSServices({osTimezone:()=>"UTC",osTMLayout:()=>0}),{publish:false,nativeRegistration:true}));return 1;});L.lua_call(0,1);L.lua_setglobal('os');
  L.luaL_requiref('_G',S=>{openBase(S.vm,{baseError:true,baseMeta:true,baseGC:true,baseFunctions:createBaseIOFunctions(S.vm),nativeRegistration:true});S.push(S.vm.globals);return 1;},1);L.lua_pop(1);
  L.luaL_requiref('string',S=>{S.push(openString(S.vm,{publish:false}));return 1;},1);L.lua_pop(1);
  for(const[name,fn]of Object.entries({auxError:S=>luaAuxError(S.vm,'%s:%d:%s',S.value(1),S.value(2),S.value(3)),auxArg:S=>luaArgError(S.vm,Number(S.value(1)),S.value(2)),auxType:S=>luaTypeError(S.vm,1,'number',S.has(1)?S.value(1):undefined),auxInt:S=>luaCheckInteger(S.vm,S.has(1)?S.value(1):undefined,1),auxNum:S=>luaCheckNumber(S.vm,S.has(1)?S.value(1):undefined,1),auxStr:S=>luaCheckString(S.vm,S.has(1)?S.value(1):undefined,1)})){L.lua_pushcfunction(fn);L.lua_setglobal(name);}
  L.lua_pushlightuserdata(1n);L.lua_setglobal('light');
  const loaded=L.luaL_loadbuffer(data,data.length,'@fixture.lua','b');phase('load',loaded);assert.equal(loaded,0);
  if(offset)fail=attempts+offset;
  const status=L.lua_pcall(0,-1);phase('run',status);
  if(!status){assert.ok(isLuaString(L.value(-1)));const result=luaStringBytes(L.value(-1));events.push({resultLength:result.length,resultHex:Array.from(result,c=>c.charCodeAt(0).toString(16).padStart(2,'0')).join('')});}
  L.lua_close();phase('close',0);assert.equal(bytes,0);assert.equal(blocks.size,0);return events;
}
const literal = s => '"'+s.replace(/[\x00-\x1f\\"]/g,c=>c==='\\'||c==='"'?'\\'+c:'\\'+String(c.charCodeAt(0)).padStart(3,'0'))+'"';
const rejected=expression=>`local ok,e=pcall(function()return ${expression} end);assert(not ok);return e`;
const cases = [
 ['message',rejected('auxError("hello",17,"world")')],
 ['long-message',rejected(`auxError(${literal('a'.repeat(500))},17,${literal('b'.repeat(500))})`)],
 ['arg',rejected('auxArg(2,"detail")')],
 ['int-bool',rejected('auxInt(false)')],
 ['int-fraction',rejected('auxInt(1.5)')],
 ['number-table',rejected('auxNum({})')],
 ['string-bool',rejected('auxStr(false)')],
 ['missing',rejected('auxStr()')],
 ['light',rejected('auxType(light)')],
 ['type-name',rejected('auxType(setmetatable({},{__name="widget"}))')],
 ['type-name-number',rejected('auxType(setmetatable({},{__name=17}))')],
 ['type-name-long',rejected(`auxType(setmetatable({},{__name=${literal('widget'.repeat(100))}}))`)],
 ['long-global-alias',`local name=${literal('alias'.repeat(100))};_G[name]=auxInt;auxInt=nil;local ok,e=pcall(_G[name],false);return e`],
 ['pcall-name','local ok,e=pcall(auxInt,false);return e'],
 ['local-alias','local alias=auxInt;local ok,e=pcall(function()return alias(false) end);return e'],
 ['method','local t={f=auxInt};local ok,e=pcall(function()return t:f() end);return e'],
];
const report=[];let refusals=0;
const selected=process.argv.find(a=>a.startsWith('--case='))?.slice(7),successOnly=process.argv.includes('--success-only');
for(const[name,text]of cases.filter(([name])=>!selected||name===selected)){
 const input=resolve(work,'fixture.lua'),binary=resolve(work,'fixture.luac');writeFileSync(input,text);execFileSync(oracle,['dump',input,binary]);const data=new Uint8Array(readFileSync(binary));
 const native=(offset=0)=>execFileSync(oracle,['run',binary,String(offset)],{encoding:'utf8',maxBuffer:16*1024*1024}).trim().split('\n').map(JSON.parse);
 const expected=native(),actual=traceJS(data);writeFileSync(resolve(work,name+'.json'),JSON.stringify({native:expected,js:actual},null,2));assert.deepEqual(actual,expected,'complete allocator/result transcript '+name);
 const loads=expected.find(e=>e.phase==='load').attempts,runs=expected.find(e=>e.phase==='run').attempts;
 for(let offset=1;!successOnly&&offset<=runs-loads+1;offset++){const expectedFailure=native(offset),actualFailure=traceJS(data,offset);if(JSON.stringify(expectedFailure)!==JSON.stringify(actualFailure))writeFileSync(resolve(work,'failure.json'),JSON.stringify({name,offset,native:expectedFailure,js:actualFailure},null,2));assert.deepEqual(actualFailure,expectedFailure,'allocation refusal '+name+'/'+offset);refusals++;}
 report.push({name,events:expected.length,runtimeAllocations:runs-loads});
}
writeFileSync(resolve(work,'summary.json'),JSON.stringify({cases:report,refusals},null,2)+'\n');
console.log(`PASS: ${report.length} native Lua auxiliary diagnostics full allocator/result transcripts and ${refusals} allocation refusal schedules${successOnly?' (success-only diagnostic)':''}, including native buffer growth and finalizer cleanup.`);
