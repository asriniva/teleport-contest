/** Actual native and configured-C Lua OS comparisons through the C ABI.
 * Original libc operations remain platform services; all Lua OS policy is JS. */
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import {spawnSync} from 'node:child_process';
import {fileURLToPath,pathToFileURL} from 'node:url';
import {createLuaAbi} from '../js/lua/abi.js';
import {createLuaBytecodeVM} from '../js/lua/bytecode-vm.js';
const root=fileURLToPath(new URL('../',import.meta.url)),scratch=path.join(root,'.cache/js-lua-os');fs.mkdirSync(scratch,{recursive:true});
const sdk=process.env.EMSDK??path.join(root,'.cache/emsdk');
const env={...process.env,TZ:process.env.TZ??'America/New_York',PATH:path.join(sdk,'node/24.19.0_64bit/bin')+path.delimiter+process.env.PATH};
function command(program,args,options={}){const result=spawnSync(program,args,{encoding:'utf8',env,timeout:120000,maxBuffer:8*1024*1024,...options});assert.equal(result.status,0,`${program}: ${result.error??result.stderr}`);return result.stdout.trimEnd();}
const src=path.join(root,'.cache/wasm64-build/tree/lib/lua-5.4.8/src');
const driver=path.join(scratch,'oracle.c');
fs.writeFileSync(driver,String.raw`
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
static void fixture(void){
 mkdir("fixture",0700);remove("fixture/a");remove("fixture/b");remove("fixture/empty");mkdir("fixture/empty",0700);
 mkdir("fixture/notempty",0700);FILE*f=fopen("fixture/a","wb");fputs("abc",f);fclose(f);
 f=fopen("fixture/notempty/item","wb");fputs("x",f);fclose(f);
}
int oracle_source(const char *source){
 fixture();lua_State*L=luaL_newstate();
 luaL_requiref(L,"_G",luaopen_base,1);lua_pop(L,1);luaL_requiref(L,"table",luaopen_table,1);lua_pop(L,1);
 luaL_requiref(L,"string",luaopen_string,1);lua_pop(L,1);luaL_requiref(L,"os",luaopen_os,1);lua_pop(L,1);
 int status=luaL_loadbuffer(L,source,strlen(source),"@os.lua");if(!status)status=lua_pcall(L,0,LUA_MULTRET,0);
 if(status){fprintf(stderr,"status%d:%s",status,lua_tostring(L,-1));lua_close(L);return status;}
 for(int i=1;i<=lua_gettop(L);i++)switch(lua_type(L,i)){
 case LUA_TNIL:puts("nil");break;
 case LUA_TBOOLEAN:printf("boolean:%d\n",lua_toboolean(L,i));break;
 case LUA_TNUMBER:if(lua_isinteger(L,i))printf("integer:%lld\n",(long long)lua_tointeger(L,i));else{double n=lua_tonumber(L,i);uint64_t bits;memcpy(&bits,&n,8);printf("float:%016llx\n",(unsigned long long)bits);}break;
 case LUA_TSTRING:{size_t n;const unsigned char*s=(const unsigned char*)lua_tolstring(L,i,&n);fputs("string:",stdout);for(size_t j=0;j<n;j++)printf("%02x",s[j]);putchar('\n');break;}
 default:printf("type:%s\n",lua_typename(L,lua_type(L,i)));}
 lua_close(L);return 0;
}
int main(int argc,char**argv){if(argc!=2)return 1;FILE*f=fopen(argv[1],"rb");if(!f)return 2;fseek(f,0,SEEK_END);long n=ftell(f);rewind(f);char text[n+1];fread(text,1,n,f);text[n]=0;fclose(f);return oracle_source(text);}
`);
const sources=fs.readdirSync(src).filter(name=>name.endsWith('.c')&&!['lua.c','luac.c'].includes(name)).map(name=>path.join(src,name));
const host=path.join(scratch,'oracle');command(path.join(root,'.cache/wasm64-build/host-cc'),['-O2','-DLUA_USE_POSIX','-I'+src,driver,...sources,'-lm','-o',host]);
const flags=['-O2','-g','-DLUA_USE_POSIX','-I'+src,'-sMEMORY64=1','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sINVOKE_RUN=0','-sALLOW_MEMORY_GROWTH=1','-sEXPORTED_FUNCTIONS=_oracle_source,_malloc,_free','-sEXPORTED_RUNTIME_METHODS=FS,ENV,HEAPU8'];
for(const mode of ['native','javascript'])command(path.join(sdk,'upstream/emscripten/emcc'),[driver,...(mode==='native'?sources:[path.join(root,'nethack-c/wasm/lua-bridge.c'),'--js-library',path.join(root,'nethack-c/wasm/lua-library.js')]),...flags,'-lm','-o',path.join(scratch,mode+'.mjs')]);
const modules={},output={};
for(const mode of ['native','javascript']){
 output[mode]=[];const factory=(await import(pathToFileURL(path.join(scratch,mode+'.mjs')))).default;
 modules[mode]=await factory({nethackLua:createLuaAbi({vmFactory:createLuaBytecodeVM}),print:line=>output[mode].push(line),printErr:line=>{throw Error(line)},preRun:[m=>{m.ENV.TZ=env.TZ;}]});
}
const tableValues=`local function values(t)return t.year,t.month,t.day,t.hour,t.min,t.sec,t.wday,t.yday,t.isdst end;`;
const cases=[];const add=(name,source)=>cases.push([name,source]);
for(const time of [-2208988800n,-1n,0n,1n,951782400n,1583650800n,1604210400n,1710054000n,1730613600n,2147483647n,4102444800n]){
 for(const utc of ['', '!'])add('date-'+utc+time,`${tableValues}return os.date(${JSON.stringify(utc+'%Y-%m-%d %H:%M:%S %w %j %z %Z')},${time}),values(os.date(${JSON.stringify(utc+'*t')},${time}))`);
}
for(const spec of 'aAbBcCdDeFgGhHIjmMnprRStTuUVwWxXyYzZ%')add('strftime-'+spec,`return os.date('!%${spec}',951827696)`);
for(const spec of ['Ec','EC','Ex','EX','Ey','EY','Od','Oe','OH','OI','Om','OM','OS','Ou','OU','OV','Ow','OW','Oy'])add('strftime-'+spec,`return os.date('!%${spec}',951827696)`);
// Native time_t/tm covers years outside Date's range, including year zero.
for(const time of [-62198755200n,-62167219200n,-62135596800n,-2209075201n,253402300799n,253402300800n,8640000000001n,67768036160140800n])
 add('date-wide-'+time,`${tableValues}return os.date('!%c|%C|%Y|%y|%G|%g|%V|%U|%W|%F|%z|%Z',${time}),values(os.date('!*t',${time}))`);
for(const time of [-9223372036854775808n,9223372036854775807n])
 add('date-range-'+time,`local ok,e=pcall(os.date,'!*t',${time<0?'(-9223372036854775807-1)':time});return ok,e`);
for(const source of ['{year=2000,month=2,day=29}','{year=2024,month=3,day=10,hour=2,min=30}','{year=2024,month=11,day=3,hour=1,min=30}','{year=2024,month=11,day=3,hour=1,min=30,isdst=true}','{year=2024,month=11,day=3,hour=1,min=30,isdst=false}','{year=2000,month=13,day=0,hour=-1,min=100,sec=-3}','{year="2000",month="2",day="29"}','{year=1900,month=1,day=1}'])add('time-'+source,`${tableValues}local t=${source};return os.time(t),values(t)`);
for(const [a,b]of [[0n,1n],[951827696n,951782400n],[-9223372036854775808n,9223372036854775807n],[9007199254740993n,9007199254740992n]])add('difftime-'+a,`return os.difftime(${a===-9223372036854775808n?'(-9223372036854775807-1)':a},${b})`);
for(const source of ["os.remove('fixture/a')","os.remove('fixture/missing')","os.remove('fixture/a/child')","os.remove('fixture/empty')","os.remove('fixture/notempty')","os.rename('fixture/a','fixture/b')","os.rename('fixture/missing','fixture/b')","os.rename('fixture/a','fixture/notempty')","os.remove('fixture/a\\0trailing')"])add(source,'return '+source);
for(const source of ["os.date('%Q',0)","os.date('%',0)","os.date(true,0)","os.date('%c',1.5)","os.date('%c',false)","os.time({year=2000,month=2})","os.time({year=2000.5,month=2,day=1})","os.time({year=2147485548,month=2,day=1})","os.time(false)","os.difftime(false,1)","os.difftime(0,'x')","os.difftime(0,1.5)","os.remove()","os.remove(nil)","os.rename('a')","os.rename('a',nil)"])add('error-'+source,`local ok,e=pcall(function()return ${source}end);return ok,e`);
add('error-alias',`local r=os.remove;local ok,e=pcall(function()return r(true)end);return ok,e`);
add('field-get-error',`local t=setmetatable({},{__index=function()error('get-failed')end});local ok,e=pcall(os.time,t);return ok,e`);
add('field-set-error',`local t=setmetatable({year=2000,month=2,day=29},{__newindex=function()error('set-failed')end});local ok,e=pcall(os.time,t);return ok,e,t.year,t.month,t.day,t.hour`);
add('clock-current','local c=os.clock();local t=os.time();return type(c),c>=0,c<1e6,type(t),t>1700000000,t<3000000000');
add('binary-format',String.raw`return os.date('!a\0b%Y',0),os.date('!*t\0ignored',0).year`);
let passed=0;const differences=[],mismatches=[];
for(const [name,source]of cases){
 const input=path.join(scratch,'input.lua');fs.writeFileSync(input,source);const native=command(host,[input],{cwd:scratch});
 const results={};
 for(const mode of ['native','javascript']){
  const m=modules[mode],bytes=Buffer.from(source+'\0'),p=m._malloc(BigInt(bytes.length));m.HEAPU8.set(bytes,Number(p));output[mode].length=0;
  try{assert.equal(m._oracle_source(BigInt(p)),0,name);}finally{m._free(p);}results[mode]=output[mode].join('\n');
 }
 if(native!==results.native)differences.push({name,source,native,emscripten:results.native});
 if(results.javascript!==native){mismatches.push({name,source,native,javascript:results.javascript});if(!process.argv.includes('--report'))assert.equal(results.javascript,native,name);}else passed++;
}
fs.writeFileSync(path.join(scratch,'results.json'),JSON.stringify({passed,total:cases.length,timezone:env.TZ,mismatches,measuredPlatformDifferences:differences},null,2)+'\n');
assert.equal(mismatches.length,0,'Native Lua OS parity: see .cache/js-lua-os/results.json');
console.log(`PASS: ${passed} actual native macOS Lua OS comparisons through the memory64 C ABI; ${differences.length} explicit Emscripten platform differences. Clock/date/strftime/time normalization/difftime and real remove/rename lifecycle.`);
