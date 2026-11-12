// Independent original Lua5.4.8 full allocator/refusal traces for primitive strings/table.concat.
// Production formatting uses neither this native compiler nor file access.
import assert from 'node:assert/strict';
import { createHash } from 'node:crypto';
import { mkdirSync, readFileSync, writeFileSync, readdirSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { fileURLToPath } from 'node:url';
import { resolve } from 'node:path';
import { createLuaCState } from '../js/lua/lapi.js';
import { createLuaBytecodeVM } from '../js/lua/bytecode-vm.js';
import {openUtf8} from '../js/lua/lutf8lib.js';
import {openBase,openTable} from '../js/lua/lbaselib.js';
import { openString } from '../js/lua/lstrlib.js';
import { createBaseIOFunctions } from '../js/lua/base-io.js';
import { isLuaString, luaStringBytes } from '../js/lua/lobject.js';

process.env.TZ='UTC';
const root = fileURLToPath(new URL('../', import.meta.url));
const scratch=process.argv.find(a=>a.startsWith('--scratch='))?.slice(10)??'';assert.match(scratch,/^[a-z0-9_-]*$/);
const work=resolve(root,'.cache/js-dependency-lua/consumer-memory'+(scratch?'-'+scratch:''));mkdirSync(work,{recursive:true});
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
static int sameidentity(lua_State*L){lua_pushboolean(L,lua_topointer(L,1)==lua_topointer(L,2));return 1;}
static int writer(lua_State*L,const void*p,size_t n,void*ud){return fwrite(p,1,n,ud)!=n;}
int main(int argc,char**argv){
 if(argc<3)return 2;FILE*f=fopen(argv[2],"rb");if(!f)return 3;fseek(f,0,SEEK_END);size_t n=ftell(f);rewind(f);char*data=malloc(n?n:1);if(fread(data,1,n,f)!=n)return 4;fclose(f);
 if(!strcmp(argv[1],"dump")){lua_State*L=luaL_newstate();int rc=luaL_loadbufferx(L,data,n,"@fixture.lua","t");if(rc){fprintf(stderr,"%s",lua_tostring(L,-1));return rc;}f=fopen(argv[3],"wb");rc=lua_dump(L,writer,f,0);fclose(f);lua_close(L);free(data);return rc;}
 Mem m={0};m.fail=(size_t)-1;lua_State*L=lua_newstate(alloc,&m);if(!L)abort();
 lua_pushcfunction(L,luaopen_base);lua_call(L,0,1);lua_pop(L,1);
 lua_pushcfunction(L,luaopen_string);lua_call(L,0,1);lua_setglobal(L,"string");
 lua_pushcfunction(L,luaopen_table);lua_call(L,0,1);lua_setglobal(L,"table");lua_pushcfunction(L,luaopen_utf8);lua_call(L,0,1);lua_setglobal(L,"utf8");
 lua_pushcfunction(L,sameidentity);lua_setglobal(L,"sameidentity");
 int rc=luaL_loadbufferx(L,data,n,"@fixture.lua","b");phase(&m,"load",rc);if(rc)abort();
 if(argc>3&&strtoull(argv[3],NULL,10))m.fail=m.attempt+strtoull(argv[3],NULL,10);
 rc=lua_pcall(L,0,LUA_MULTRET,0);phase(&m,"run",rc);
 if(!rc){size_t len;const unsigned char*s=(const unsigned char*)lua_tolstring(L,-1,&len);if(!s)abort();uint32_t hash=2166136261u;for(size_t i=0;i<len;i++)hash=(hash^s[i])*16777619u;printf("{\"resultLength\":%zu,\"resultHash\":%u}\n",len,hash);}
 else{size_t len=0;const unsigned char*s=(const unsigned char*)lua_tolstring(L,-1,&len);printf("{\"errorType\":%d,\"errorHex\":\"",lua_type(L,-1));if(s)for(size_t i=0;i<len;i++)printf("%02x",s[i]);puts("\"}");}
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
  L.lua_pushcfunction(S=>{S.push(openTable(S.vm,{publish:false}));return 1;});L.lua_call(0,1);L.lua_setglobal('table');L.lua_pushcfunction(S=>{S.push(openUtf8(S.vm,{publish:false}));return 1;});L.lua_call(0,1);L.lua_setglobal('utf8');
  L.lua_pushcfunction(S=>{S.lua_pushboolean(S.lua_topointer(1)===S.lua_topointer(2));return 1;});L.lua_setglobal('sameidentity');
  const loaded=L.luaL_loadbuffer(data,data.length,'@fixture.lua','b');phase('load',loaded);assert.equal(loaded,0);
  if(offset)fail=attempts+offset;
  const status=L.lua_pcall(0,-1);phase('run',status);
  if(!status){assert.ok(isLuaString(L.value(-1)));const result=luaStringBytes(L.value(-1));let hash=2166136261;for(let i=0;i<result.length;i++)hash=Math.imul(hash^result.charCodeAt(i),16777619)>>>0;events.push({resultLength:result.length,resultHash:hash});}
  if(status){const error=L.lua_tolstring(-1);events.push({errorType:L.lua_type(-1),errorHex:error===null?'':Array.from(luaStringBytes(error),c=>c.charCodeAt(0).toString(16).padStart(2,'0')).join('')});}
  L.lua_close();phase('close',0);assert.equal(bytes,0);assert.equal(blocks.size,0);return events;
}
const literal = s => '"'+s.replace(/[\x00-\x1f\\"]/g,c=>c==='\\'||c==='"'?'\\'+c:'\\'+String(c.charCodeAt(0)).padStart(3,'0'))+'"';
const cases=[
 ...[
 ['setmetatable-protected','setmetatable(setmetatable({},{__metatable="locked"}),{})'],
 ['concat-type','table.concat(false)'],['concat-value','table.concat({false})'],['concat-index','table.concat({},"",false)'],['concat-last','table.concat({},"",1,false)'],
 ['insert-type','table.insert(false,1)'],['insert-nargs','table.insert({})'],['insert-bound','table.insert({},0,1)'],['remove-type','table.remove(false)'],['remove-bound','table.remove({},-1)'],['sort-type','table.sort(false)'],
 ['type-none','type()'],['tostring-none','tostring()'],['tostring-meta-invalid','tostring(setmetatable({},{__tostring=function()return {}end}))'],
 ['tonumber-none','tonumber()'],['tonumber-base-string','tonumber(17,10)'],['tonumber-base-range','tonumber("17",1)'],
 ['select-fraction','select(1.5,1)'],['select-zero','select(0,1)'],['next-type','next(false)'],['pairs-type','(function()for k in pairs(false)do end end)()'],
 ['rawget-type','rawget(false,1)'],['rawget-none','rawget({})'],['rawset-none','rawset({},1)'],['rawlen-type','rawlen(false)'],
 ['rawequal-none','rawequal(nil)'],['getmetatable-none','getmetatable()'],['setmetatable-type','setmetatable(false,{})'],['setmetatable-arg2','setmetatable({},false)'],
 ['error-none','error()'],['error-level','error("oops",false)'],['assert-none','assert()'],['assert-false','assert(false)'],['assert-message','assert(false,"oops")'],['assert-nil','assert(false,nil)'],
 ['pcall-none','pcall()'],['xpcall-handler','xpcall(function()end,false)'],
 ['sub-type','string.sub({},1)'],['sub-index-type','string.sub("abc",false)'],['sub-index-fraction','string.sub("abc",1.5)'],['sub-last-type','string.sub("abc",1,false)'],
 ['char-range','string.char(256)'],['char-type','string.char(1,false)'],['dump-type','string.dump(false)'],['rep-count','string.rep("x",false)'],
 ['gsub-replacement','string.gsub("abc","a",false)'],['gsub-limit','string.gsub("abc","a","x",1.5)'],['gmatch-init','string.gmatch("abc","a",false)'],
 ['move-type','table.move(false,1,2,3)'],['move-destination','table.move({},1,2,3,false)'],['move-index','table.move({},1,2.5,3)'],['move-overflow','table.move({},-1,9223372036854775807,1)'],['move-wrap','table.move({},1,2,9223372036854775807)'],
 ].map(([name,expression])=>['error-'+name,'return '+expression]),
 ['metatable-field','local t=setmetatable({},{__metatable="locked"});return getmetatable(t)'],
 ['metatable-reset','local t=setmetatable({},{});setmetatable(t,{});return tostring(type(getmetatable(t)))'],
 ['insert-shift','local t={1,2,3};table.insert(t,2,17);return table.concat(t,":")'],
 ['remove-shift','local t={1,2,3,4};local x=table.remove(t,2);return x..":"..table.concat(t,":")'],
 ['concat-metatable','local t=setmetatable({},{__len=function()return 3 end,__index=function(_,i)collectgarbage();return tostring(i).."x"end});return table.concat(t,":")'],
 ['tostring-number','return tostring(1234567890123456789)'],
 ['tostring-float','return tostring(1.23456789012345)'],
 ['tostring-bool','return tostring(false)'],
 ['tostring-nil','return tostring(nil)'],
 ['tostring-meta-string','local t=setmetatable({},{__tostring=function()return "custom"end});return tostring(t)'],
 ['tostring-meta-number','local t=setmetatable({},{__tostring=function()return 123456789 end});return tostring(t)'],
 ['pack-small','local t=table.pack(1,nil,3);return table.concat({t[1],t[3],t.n},":")'],
 ['pack-large','local t={};for i=1,400 do t[i]=i end local p=table.pack(table.unpack(t));return table.concat(p,":")'],
 ['move-forward','local t={1,2,3};table.move(t,1,3,2);return table.concat(t)'],
 ['move-backward','local t={1,2,3,4};table.move(t,2,4,1);return table.concat(t)'],
 ['move-metatable','local s="";local a=setmetatable({},{__index=function(_,i)s=s..i;return i end});local b=setmetatable({},{__newindex=function(_,i,v)s=s..i..v;collectgarbage()end});table.move(a,1,3,2,b);return s'],
 ['unpack-metatable','local s="";local a=setmetatable({},{__index=function(_,i)collectgarbage();return tostring(i).."x"end});local a,b,c=table.unpack(a,1,3);return a..b..c'],
 ['rep-too-large','return string.rep("",2147483648,"x")'],
 ['unpack-stack-overflow','return table.unpack({},1,1000000)'],
 ['unpack-int-overflow','return table.unpack({},1,2147483648)'],
 ['dump-small','return string.dump(function(x)return x+1 end)'],
 ['dump-strip','return string.dump(function(x)local t={x=x};return t.x end,true)'],
 ['dump-large',`return string.dump(function()return ${literal('a'.repeat(6000))} end)`],
 ['dump-nested','return string.dump(function(x)return function(y)return x+y end end)'],
 ['dump-repeated',`local f=function()return ${literal('a'.repeat(2000))} end;local s;for i=1,3 do s=string.dump(f)end return s`],
 ['dump-Cfunction','return string.dump(string.len)'],
 ['gsub-unchanged-identity',`local s=${literal('ab'.repeat(100))};local t=string.gsub(s,"a",function()return false end);return tostring(sameidentity(s,t))`],
 ['gsub-changed-identity',`local s=${literal('ab'.repeat(100))};local t=string.gsub(s,"a","a");return tostring(not sameidentity(s,t))`],
 ['sub-long',`return string.sub(${literal('a'.repeat(1500))},2)`],
 ['sub-empty','return string.sub("abc",3,1)'],
 ['gsub-table-index',`local t=setmetatable({},{__index=function(_,x)collectgarbage();return x..x end});return (string.gsub("abcdef","(.)",t))`],
 ['gsub-repeated',`local s;for i=1,3 do s=string.gsub(${literal('ab'.repeat(1500))},"a","xxx")end return s`],
 ['gmatch-repeated','local s="";for i=1,40 do local f=string.gmatch("abc","(.)");s=s..f()end return s'],
 ['match-long',`return string.match(${literal('a'.repeat(100))},"(.+)")`],
 ['find-long',`local a,b,c=string.find(${literal('a'.repeat(100))},"(.+)");return c`],
 ['match-numeric','return string.match(12345,23)'],
 ['gsub-malformed','return string.gsub("abc","[","x")'],
 ['gmatch-malformed','local f=string.gmatch("abc","[");return f()'],
 ['gsub-invalid-capture','return string.gsub("abc","a","%2")'],
 ['gsub-invalid-value','return string.gsub("abc","a",function()return {}end)'],
 ['gsub-small','return (string.gsub("abc abc","(a)(b)","%2%1%%"))'],
 ['gsub-large',`return (string.gsub(${literal('ab'.repeat(1500))},"a","xxx"))`],
 ['gsub-unchanged',`return (string.gsub(${literal('ab'.repeat(1500))},"a",function()return false end))`],
 ['gsub-numeric','return (string.gsub(121212,"1",17))'],
 ['gsub-position','return (string.gsub("abcdef","()","%1"))'],
 ['gsub-function','return (string.gsub("abcdef","(.)",function(x)return x..x end))'],
 ['gsub-table','return (string.gsub("abcabc","(.)",{a="xx",b=17}))'],
 ['gsub-error',`return (string.gsub(${literal('a'.repeat(1500)+'b')},".",function(x)if x=="b"then error("stop")end return "xx"end))`],
 ['gmatch-empty','local f=string.gmatch("abc","(.)");return "ok"'],
 ['gmatch-captures','local s="";for x in string.gmatch("abcdef","(.)")do s=s..x end return s'],
 ['gmatch-long',`local f=string.gmatch(${literal('a'.repeat(100))},"(.+)");return f()`],
 ['gmatch-numeric','local f=string.gmatch(12345,"(.)");return f()'],
 ['rep-empty','return string.rep("x",0)'],
 ['rep-inline','return string.rep("x",1024)'],
 ['rep-overflow','return string.rep("x",1025)'],
 ['rep-large','return string.rep("xy",3000,"-")'],
 ['rep-numeric','return string.rep(17,2000,23)'],
 ['rep-repeated','local s;for i=1,3 do s=string.rep("x",6000)end return s'],
 ['reverse-small','return string.reverse("abcdef")'],
 ['reverse-large',`return string.reverse(${literal('Abcd'.repeat(1500))})`],
 ['lower-large',`return string.lower(${literal('AbCd'.repeat(1500))})`],
 ['upper-large',`return string.upper(${literal('AbCd'.repeat(1500))})`],
 ['case-numeric','return string.lower(17)'],
 ['char-small','return string.char(97,98,99,0,255)'],
 ['char-large','local t={};for i=1,2000 do t[i]=97 end return string.char(table.unpack(t))'],
 ['concat-small','return table.concat({1,2,3},":")'],
 ['concat-large',`return table.concat({${[1,2,3].map(()=>literal('x'.repeat(2000))).join(',')}} ,":")`],
 ['concat-numeric','local t={};for i=1,200 do t[i]=i end return table.concat(t,17)'],
 ['concat-repeated',`local t={${[1,2,3].map(()=>literal('x'.repeat(2000))).join(',')}};local s;for i=1,3 do s=table.concat(t)end return s`],
];
const report=[],diagnosticFailures=[];let refusals=0;
const selected=process.argv.find(a=>a.startsWith('--case='))?.slice(7),successOnly=process.argv.includes('--success-only');
for(const[name,text]of cases.filter(([name])=>!selected||name===selected)){
 const input=resolve(work,'fixture.lua'),binary=resolve(work,'fixture.luac');writeFileSync(input,text);execFileSync(oracle,['dump',input,binary]);const data=new Uint8Array(readFileSync(binary));
 const native=(offset=0)=>execFileSync(oracle,['run',binary,String(offset)],{encoding:'utf8',maxBuffer:16*1024*1024}).trim().split('\n').map(JSON.parse);
 const expected=native(),actual=traceJS(data);writeFileSync(resolve(work,name+'.json'),JSON.stringify({native:expected,js:actual},null,2));if(JSON.stringify(actual)!==JSON.stringify(expected)&&process.argv.includes('--diagnose')){diagnosticFailures.push(name);continue;}assert.deepEqual(actual,expected,'complete allocator/result transcript '+name);
 const loads=expected.find(e=>e.phase==='load').attempts,runs=expected.find(e=>e.phase==='run').attempts;
 for(let offset=1;!successOnly&&offset<=runs-loads+1;offset++){const expectedFailure=native(offset),actualFailure=traceJS(data,offset);if(JSON.stringify(expectedFailure)!==JSON.stringify(actualFailure))writeFileSync(resolve(work,'failure.json'),JSON.stringify({name,offset,native:expectedFailure,js:actualFailure},null,2));assert.deepEqual(actualFailure,expectedFailure,'allocation refusal '+name+'/'+offset);refusals++;}
 report.push({name,events:expected.length,runtimeAllocations:runs-loads});
}
if(diagnosticFailures.length)throw new Error('Native transcript differences: '+diagnosticFailures.join(', '));
writeFileSync(resolve(work,'summary.json'),JSON.stringify({cases:report,refusals},null,2)+'\n');
console.log(`PASS: ${report.length} native retained Lua library full allocator/result transcripts and ${refusals} allocation refusal schedules${successOnly?' (success-only diagnostic)':''}, including native buffer growth and finalizer cleanup.`);
