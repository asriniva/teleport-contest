// Independent original Lua5.4.8 full allocator/refusal traces for string.pack/os.date.
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
import {openLuaOS} from '../js/lua/os-library.js';
import {createLuaOSServices} from '../js/lua/os-abi.js';
process.env.TZ='UTC';
const root = fileURLToPath(new URL('../', import.meta.url));
const work = resolve(root, '.cache/js-lua-pack-os-memory'); mkdirSync(work, { recursive: true });
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
int main(int argc,char**argv){
 if(argc<3)return 2;FILE*f=fopen(argv[2],"rb");if(!f)return 3;fseek(f,0,SEEK_END);size_t n=ftell(f);rewind(f);char*data=malloc(n?n:1);if(fread(data,1,n,f)!=n)return 4;fclose(f);
 if(!strcmp(argv[1],"dump")){lua_State*L=luaL_newstate();int rc=luaL_loadbufferx(L,data,n,"@fixture.lua","t");if(rc){fprintf(stderr,"%s",lua_tostring(L,-1));return rc;}f=fopen(argv[3],"wb");rc=lua_dump(L,writer,f,0);fclose(f);lua_close(L);free(data);return rc;}
 Mem m={0};m.fail=(size_t)-1;lua_State*L=lua_newstate(alloc,&m);if(!L)abort();
 lua_pushcfunction(L,luaopen_base);lua_call(L,0,1);lua_pop(L,1);
 lua_pushcfunction(L,luaopen_string);lua_call(L,0,1);lua_setglobal(L,"string");
 lua_pushcfunction(L,luaopen_os);lua_call(L,0,1);lua_setglobal(L,"os");
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
  const loaded=L.luaL_loadbuffer(data,data.length,'@fixture.lua','b');phase('load',loaded);assert.equal(loaded,0);
  if(offset)fail=attempts+offset;
  const status=L.lua_pcall(0,-1);phase('run',status);
  if(!status){assert.ok(isLuaString(L.value(-1)));const result=luaStringBytes(L.value(-1));events.push({resultLength:result.length,resultHex:Array.from(result,c=>c.charCodeAt(0).toString(16).padStart(2,'0')).join('')});}
  L.lua_close();phase('close',0);assert.equal(bytes,0);assert.equal(blocks.size,0);return events;
}
const literal = s => '"'+s.replace(/[\x00-\x1f\\"]/g,c=>c==='\\'||c==='"'?'\\'+c:'\\'+String(c.charCodeAt(0)).padStart(3,'0'))+'"';
const cases = [
 ...[
  ['pack-format','string.pack("?")'],['pack-integral-size','string.pack("i0",1)'],['pack-missing-size','string.pack("c","")'],
  ['pack-next-option','string.pack("Xc1","x")'],['pack-alignment','string.pack("!3i3",1)'],
  ['pack-signed-overflow','string.pack("b",128)'],['pack-unsigned-overflow','string.pack("B",-1)'],
  ['pack-number-type','string.pack("d",false)'],['pack-integer-fraction','string.pack("i",1.5)'],
  ['pack-char-length','string.pack("c1","xx")'],['pack-string-length',`string.pack('s1',${literal('x'.repeat(256))})`],
  ['pack-zero-argument',`string.pack('z',${literal('a\0b')})`],['pack-missing-argument','string.pack("i")'],
  ['packsize-variable','string.packsize("s1")'],['packsize-overflow','string.packsize("c2000000000c2000000000")'],
  ['unpack-position','string.unpack("B","",2)'],['unpack-short','string.unpack("B","")'],
  ['unpack-zero-end','string.unpack("z","abc")'],['unpack-large-integer',`string.unpack('I16',${literal('\xff'.repeat(16))})`],
  ['date-invalid','os.date("%Q",0)'],['date-invalid-grown',`os.date(${literal('x'.repeat(1025)+'%Q')},0)`],
  ['date-type','os.date(false,0)'],['date-time-type','os.date("%c",false)'],
  ['time-table-type','os.time(false)'],['time-field-missing','os.time({year=2000})'],['time-field-fraction','os.time({year=2000.5,month=1,day=1})'],
 ].map(([name,expression])=>[name,`local ok,e=pcall(function()return ${expression} end);assert(not ok);return e`]),
 ['date-table',`local t=os.date('!*t',0);return t.year..'/'..t.month..'/'..t.day`],
 ['time-normalize',`local t={year=2000,month=13,day=0};return os.time(t)..'/'..t.year..'/'..t.month..'/'..t.day`],
 ['time-ignored-args',`local t={year=2000,month=1,day=1};return os.time(t,{payload=string.rep('x',6000)},string.rep('z',5000))..'/'..t.year`],
 ['time-ignored-args-gc',`local t=setmetatable({},{__index=function(_,k)collectgarbage();if k=='year' then return 2000 elseif k=='month' or k=='day' then return 1 end end});return os.time(t,{payload=string.rep('x',6000)},string.rep('z',5000))..'/'..t.year`],
 ['unpack-long-char',`local a=string.unpack('c6000',${literal('x'.repeat(6000))});return a`],
 ['unpack-long-zero',`local a=string.unpack('z',${literal('x'.repeat(2000)+'\0')});return a`],
 ['unpack-long-prefixed',`local a=string.unpack('s4',string.pack('s4',${literal('x'.repeat(6000))}));return a`],
 ['unpack-many',`local t={string.unpack(${literal('B'.repeat(2000))},${literal('x'.repeat(2000))})};return t[1]..'/'..t[#t]`],
 ['unpack-repeated',`local a;for i=1,3 do a=string.unpack('c6000',${literal('x'.repeat(6000))}) end return a`],
 ['pack-empty','return string.pack("")'],
 ['pack-integers','return string.pack("<bBhHi4I8jJ",-1,255,-32000,65000,-123456789,123456789,17,19)'],
 ['pack-floats','return string.pack(">fdn",1.25,-0.0,1.1)'],
 ['pack-long-char',`return string.pack('c2048',${literal('x'.repeat(1025))})`],
 ['pack-char-padding','return string.pack("c2000","")'],
 ['pack-large-string',`return string.pack('s4',${literal('x'.repeat(6000))})`],
 ['pack-zero-string',`return string.pack('z',${literal('x'.repeat(2000))})`],
 ['pack-coerce','return string.pack("c4s4zc3",17,19,23,29)'],
 ['pack-many',`return string.pack(${literal('i8'.repeat(200))},${Array.from({length:200},(_,i)=>i).join(',')})`],
 ['pack-repeated',`local x;for i=1,3 do x=string.pack('s4',${literal('x'.repeat(6000))}) end return x`],
 ['date-inline',`return os.date(${literal('!'+ 'x'.repeat(1024))},0)`],
 ['date-overflow',`return os.date(${literal('!'+ 'x'.repeat(1025))},0)`],
 ['date-prepare',`return os.date(${literal('!'+ 'x'.repeat(800)+'%Y')},0)`],
 ['date-repeated',`local x;for i=1,3 do x=os.date(${literal('!'+ 'x'.repeat(6000))},0) end return x`],
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
console.log(`PASS: ${report.length} native string.pack/os.date full allocator/result transcripts and ${refusals} allocation refusal schedules${successOnly?' (success-only diagnostic)':''}, including native buffer growth and finalizer cleanup.`);
