// Independent original Lua5.4.8 full allocator/refusal traces for string.format and UTF8 diagnostics.
// Production formatting uses neither this native compiler nor file access.
import assert from 'node:assert/strict';
import { createHash } from 'node:crypto';
import { mkdirSync, readFileSync, writeFileSync, readdirSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { fileURLToPath } from 'node:url';
import { resolve } from 'node:path';
import { createLuaCState } from '../js/services/lua/lapi.js';
import { createLuaBytecodeVM } from '../js/services/lua-bytecode-vm.js';
import { openUtf8 } from '../js/services/lua/lutf8lib.js';
import { openTable } from '../js/services/lua/lbaselib.js';
import { openBase } from '../js/services/lua/lbaselib.js';
import { openString } from '../js/services/lua/lstrlib.js';
import { createBaseIOFunctions } from '../js/services/lua-base-io.js';
import { isLuaString, luaStringBytes } from '../js/services/lua/lobject.js';
const root = fileURLToPath(new URL('../', import.meta.url));
const work = resolve(root, '.cache/js-lua-format-utf8-errors'); mkdirSync(work, { recursive: true });
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
static int call_library(lua_State*L,const char*lib,const char*field){int n=lua_gettop(L);lua_getglobal(L,lib);lua_getfield(L,-1,field);lua_remove(L,-2);for(int i=1;i<=n;i++)lua_pushvalue(L,i);lua_call(L,n,1);return 1;}
static int call_format(lua_State*L){return call_library(L,"string","format");}
static int call_utf8(lua_State*L){return call_library(L,"utf8","len");}
int main(int argc,char**argv){
 if(argc<3)return 2;FILE*f=fopen(argv[2],"rb");if(!f)return 3;fseek(f,0,SEEK_END);size_t n=ftell(f);rewind(f);char*data=malloc(n?n:1);if(fread(data,1,n,f)!=n)return 4;fclose(f);
 if(!strcmp(argv[1],"dump")){lua_State*L=luaL_newstate();int rc=luaL_loadbufferx(L,data,n,"@fixture.lua","t");if(rc){fprintf(stderr,"%s",lua_tostring(L,-1));return rc;}f=fopen(argv[3],"wb");rc=lua_dump(L,writer,f,0);fclose(f);lua_close(L);free(data);return rc;}
 Mem m={0};m.fail=(size_t)-1;lua_State*L=lua_newstate(alloc,&m);if(!L)abort();
 luaL_requiref(L,"_G",luaopen_base,1);lua_pop(L,1);
 luaL_requiref(L,"string",luaopen_string,1);lua_pop(L,1);
 luaL_requiref(L,"utf8",luaopen_utf8,1);lua_pop(L,1);
 lua_pushcfunction(L,call_format);lua_setglobal(L,"callFormat");
 lua_pushcfunction(L,call_utf8);lua_setglobal(L,"callUTF8");
 int rc=luaL_loadbufferx(L,data,n,"@fixture.lua","b");phase(&m,"load",rc);if(rc)abort();
 if(argc>3&&strtoull(argv[3],NULL,10))m.fail=m.attempt+strtoull(argv[3],NULL,10);
 rc=lua_pcall(L,0,LUA_MULTRET,0);phase(&m,"run",rc);
 if(!rc){size_t len;const unsigned char*s=(const unsigned char*)lua_tolstring(L,-1,&len);if(!s)abort();printf("{\"resultLength\":%zu,\"resultHex\":\"",len);for(size_t i=0;i<len;i++)printf("%02x",s[i]);puts("\"}");}
 lua_close(L);phase(&m,"close",0);if(m.blocks||m.bytes)abort();free(data);return 0;
}
`);
execFileSync(resolve(root, '.cache/wasm64-build/host-cc'), ['-O2', '-I'+source, resolve(work,'oracle.c'), ...readdirSync(source).filter(n=>n.endsWith('.c')&&!['lua.c','luac.c'].includes(n)).map(n=>resolve(source,n)), '-lm', '-o', oracle]);
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
  L.luaL_requiref('_G',S=>{openBase(S.vm,{baseError:true,baseMeta:true,baseGC:true,baseFunctions:createBaseIOFunctions(S.vm),nativeRegistration:true});S.push(S.vm.globals);return 1;},1);L.lua_pop(1);
  L.luaL_requiref('string',S=>{S.push(openString(S.vm,{publish:false}));return 1;},1);L.lua_pop(1);
  L.luaL_requiref('utf8',S=>{S.push(openUtf8(S.vm,{publish:false}));return 1;},1);L.lua_pop(1);
  for(const[name,lib,key]of [['callFormat','string','format'],['callUTF8','utf8','len']]){L.lua_pushcfunction(S=>{const n=S.lua_gettop();S.lua_getglobal(lib);S.lua_getfield(-1,key);S.lua_remove(-2);for(let i=1;i<=n;i++)S.lua_pushvalue(i);S.lua_call(n,1);return 1;});L.lua_setglobal(name);}
  const loaded=L.luaL_loadbuffer(data,data.length,'@fixture.lua','b');phase('load',loaded);assert.equal(loaded,0);
  if(offset)fail=attempts+offset;
  const status=L.lua_pcall(0,-1);phase('run',status);
  if(!status){assert.ok(isLuaString(L.value(-1)));const result=luaStringBytes(L.value(-1));events.push({resultLength:result.length,resultHex:Buffer.from(result,'latin1').toString('hex')});}
  L.lua_close();phase('close',0);assert.equal(bytes,0);assert.equal(blocks.size,0);return events;
}
const literal=s=>'"'+s.replace(/[\x00-\x1f\\"]/g,c=>c==='\\'||c==='"'?'\\'+c:'\\'+String(c.charCodeAt(0)).padStart(3,'0'))+'"';
const rejected=expression=>`local ok,e=pcall(function()return ${expression} end);assert(not ok);return e`;
const cases = [
 ['format-noformat',rejected('string.format()')],
 ['format-badformat',rejected('string.format(false)')],
 ['format-missing',rejected('string.format("%d")')],
 ['format-intbool',rejected('string.format("%d",false)')],
 ['format-intfraction',rejected('string.format("%d",1.5)')],
 ['format-floatbool',rejected('string.format("%f",false)')],
 ['format-int-check-order',rejected('string.format("%..d",{})')],
 ['format-float-check-order',rejected('string.format("%..f",{})')],
 ['format-hex-check-order',rejected('string.format("%..a",{})')],
 ['format-invalid',rejected('string.format("%y",17)')],
 ['format-invalid-char',rejected('string.format("%.2c",17)')],
 ['format-longform',rejected('string.format("%----------------------d",17)')],
 ['format-quote-modifiers',rejected('string.format("%9q",17)')],
 ['format-quote-table',rejected('string.format("%q",{})')],
 ['format-zeros',rejected('string.format("%5s","a\\0b")')],
 ['format-string-check-order',rejected('string.format("%..s",true)')],
 ['format-tostring',rejected('string.format("%s",setmetatable({},{__tostring=function()return false end}))')],
 ['format-custom-type',rejected('string.format("%d",setmetatable({},{__name="widget"}))')],
 ['format-long-type',rejected(`string.format("%d",setmetatable({},{__name=${literal('kind'.repeat(100))}}))`)],
 ['format-local-alias','local alias=string.format;local ok,e=pcall(function()return alias("%d",false)end);return e'],
 ['format-plain-pcall','local ok,e=pcall(string.format,"%d",false);return e'],
 ['format-method','local t={format=string.format};local ok,e=pcall(function()return t:format("%d",17)end);return e'],
 ['format-C-caller','local ok,e=pcall(callFormat,"%d",false);return e'],
 ['format-source-lines','local x=1\n\n'+rejected('string.format("%d",false)')],
 ['format-grown',rejected(`string.format(${literal('x'.repeat(1050)+'%d')},false)`) ],
 ['utf8-char-range',rejected('utf8.char(-1)')],
 ['utf8-char-bool',rejected('utf8.char(false)')],
 ['utf8-char-fraction',rejected('utf8.char(1.5)')],
 ['utf8-char-second',rejected('utf8.char(65,false)')],
 ['utf8-char-grown',rejected('utf8.char('+Array(171).fill(2147483647).concat('false').join(',')+')')],
 ['utf8-len-type',rejected('utf8.len(false)')],
 ['utf8-len-position',rejected('utf8.len("a",0)')],
 ['utf8-len-final',rejected('utf8.len("a",1,2)')],
 ['utf8-len-integer',rejected('utf8.len("a",1.5)')],
 ['utf8-point-position',rejected('utf8.codepoint("a",0)')],
 ['utf8-point-final',rejected('utf8.codepoint("a",1,2)')],
 ['utf8-point-code',rejected('utf8.codepoint("a\\192\\128",1,-1)')],
 ['utf8-offset-count',rejected('utf8.offset("a",false)')],
 ['utf8-offset-position',rejected('utf8.offset("a",1,0)')],
 ['utf8-offset-cont',rejected('utf8.offset("a\\128",1,2)')],
 ['utf8-codes-cont',rejected('utf8.codes("\\128")')],
 ['utf8-iterator-code',rejected('(function()local it,s,p=utf8.codes("a\\128");return it(s,p)end)()')],
 ['utf8-method','local t={char=utf8.char};local ok,e=pcall(function()return t:char()end);return e'],
 ['utf8-plain-pcall','local ok,e=pcall(utf8.char,false);return e'],
 ['utf8-C-caller','local ok,e=pcall(callUTF8,false);return e'],
];
const report=[];let refusals=0;
const selected=process.argv.find(a=>a.startsWith('--case='))?.slice(7),successOnly=process.argv.includes('--success-only');
const chosen=cases.filter(([name])=>!selected||name===selected||selected.endsWith('*')&&name.startsWith(selected.slice(0,-1)));assert.ok(chosen.length,'unknown diagnostic fixture selection');
for(const[name,text]of chosen){
 const input=resolve(work,'fixture.lua'),binary=resolve(work,'fixture.luac');writeFileSync(input,text);execFileSync(oracle,['dump',input,binary]);const data=new Uint8Array(readFileSync(binary));
 const native=(offset=0)=>execFileSync(oracle,['run',binary,String(offset)],{encoding:'utf8',maxBuffer:16*1024*1024}).trim().split('\n').map(JSON.parse);
 const expected=native(),actual=traceJS(data);writeFileSync(resolve(work,name+'.json'),JSON.stringify({native:expected,js:actual},null,2));assert.deepEqual(actual,expected,'complete allocator/result transcript '+name);
 const loads=expected.find(e=>e.phase==='load').attempts,runs=expected.find(e=>e.phase==='run').attempts;
 for(let offset=1;!successOnly&&offset<=runs-loads+1;offset++){const expectedFailure=native(offset),actualFailure=traceJS(data,offset);if(JSON.stringify(expectedFailure)!==JSON.stringify(actualFailure))writeFileSync(resolve(work,'failure.json'),JSON.stringify({name,offset,native:expectedFailure,js:actualFailure},null,2));assert.deepEqual(actualFailure,expectedFailure,'allocation refusal '+name+'/'+offset);refusals++;}
 report.push({name,events:expected.length,runtimeAllocations:runs-loads});
}
writeFileSync(resolve(work,'summary.json'),JSON.stringify({cases:report,refusals},null,2)+'\n');
console.log(`PASS: ${report.length} native string.format/UTF8 diagnostic full allocator/result transcripts and ${refusals} allocation refusal schedules${successOnly?' (success-only diagnostic)':''}, including native buffer growth and finalizer cleanup.`);
