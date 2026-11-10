/** Original5.4.8 sort with injected entropy, including comparator/table traces. */
import assert from 'node:assert/strict';
import { readFileSync, writeFileSync, mkdirSync, readdirSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { createHash } from 'node:crypto';
import { fileURLToPath } from 'node:url';
import { resolve } from 'node:path';
import { createLua, isLuaString, luaStringBytes } from '../js/services/lua/lua.js';
import { luaSortEntropy } from '../js/services/lua-table-sort.js';

const root = fileURLToPath(new URL('../', import.meta.url));
const src = resolve(root, '.cache/js-dependency-lua/lua-5.4.8/src');
const scratch = resolve(root, '.cache/js-lua-sort'); mkdirSync(scratch, {recursive:true});
assert.equal(createHash('sha256').update(readFileSync(resolve(root, '.cache/lua-5.4.8.tar.gz'))).digest('hex'), '4f18ddae154e793e46eeab727c59ef1c0c0c2b744e7b94219710d76f530629ae');
const driver = resolve(scratch, 'oracle.c'), oracle = resolve(scratch, 'oracle');
writeFileSync(driver, `
#define LUA_LIB
#include "lprefix.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
static unsigned int entropy, calls;
static unsigned int controlled_entropy(void) { ++calls; return entropy=entropy*1664525u+1013904223u; }
#define l_randomizePivot controlled_entropy
#include "ltablib.c"
int main(int argc,char **argv) {
 lua_State *L=luaL_newstate(); entropy=(unsigned int)strtoul(argv[2],NULL,10);luaL_openlibs(L);
 if(luaL_loadfile(L,argv[1]) || lua_pcall(L,0,LUA_MULTRET,0)) {fprintf(stderr,"%s",lua_tostring(L,-1));return 1;}
 for(int i=1;i<=lua_gettop(L);++i) {
  switch(lua_type(L,i)) {
   case LUA_TNIL:puts("nil");break;
   case LUA_TBOOLEAN:puts(lua_toboolean(L,i)?"true":"false");break;
   case LUA_TNUMBER:if(lua_isinteger(L,i))printf("i:%lld\\n",(long long)lua_tointeger(L,i));else return 2;break;
   case LUA_TSTRING:{size_t n;const unsigned char*s=(const unsigned char*)lua_tolstring(L,i,&n);fputs("s:",stdout);for(size_t k=0;k<n;k++)printf("%02x",s[k]);putchar('\\n');break;}
   default:return 3;
  }
 }
 printf("entropy:%u\\n",calls);lua_close(L);return 0;
}
`);
execFileSync(resolve(root,'.cache/wasm64-build/host-cc'), ['-O2', '-I'+src, driver, ...readdirSync(src).filter(n=>n.endsWith('.c')&&!['lua.c','luac.c','ltablib.c'].includes(n)).map(n=>resolve(src,n)), '-lm','-o',oracle]);
const cases = [];
function arrayCase(name, numbers, descending=false) {
  cases.push([name, `local t={${numbers.join(',')}};local h,n=0,0;table.sort(t,function(a,b)n=n+1;h=(h*65599+a*257+b);return a${descending?'>':'<'}b end);return table.concat(t,','),h,n`]);
}
for(const n of [0,1,2,3,4,5,20,99,100,101,257,1024]) {
  arrayCase('ascending-'+n, Array.from({length:n},(_,i)=>i));
  arrayCase('descending-'+n, Array.from({length:n},(_,i)=>n-i));
  arrayCase('duplicates-'+n, Array.from({length:n},(_,i)=>(i*89)%17), true);
}
let random=0x13579bdf;
for(let k=0;k<32;k++) {
  const n=k*13+4, numbers=[];
  for(let i=0;i<n;i++) {random=(Math.imul(random,1664525)+1013904223)>>>0;numbers.push((random%2047)-1024);}
  arrayCase('random-'+k,numbers,k%2===0);
}
for(const n of [1024,2048,8192]) {
  const killer=[];for(let i=1;i<n/2;i+=2)killer.push(i,i+n/2);for(let i=2;i<=n;i+=2)killer.push(i);
  arrayCase('median-killer-'+n,killer);
}
cases.push(['proxy-order', `local data={4,1,5,2,3};local tr={};local t=setmetatable({},{__len=function()tr[#tr+1]='L';return 5 end,__index=function(_,k)tr[#tr+1]='G'..k;return data[k] end,__newindex=function(_,k,v)tr[#tr+1]='S'..k..':'..v;data[k]=v end});table.sort(t);return table.concat(data,','),table.concat(tr,'|')`]);
cases.push(['bad-comparator', `local t={1,2,3,4,5};local ok,e=pcall(table.sort,t,function()return true end);return ok,string.find(e,'invalid order function for sorting',1,true)~=nil`]);
cases.push(['empty-invalid-comparator', `local a,b={},{};table.sort(a,12);table.sort(b,false);return #a,#b`]);
cases.push(['gc-temporary-stack', `collectgarbage('stop');local data={4,1,5,2,3};local tr={};local serial=0;local mt={__gc=function(t)tr[#tr+1]='F'..t.id end,__lt=function(a,b)collectgarbage();tr[#tr+1]='C'..a.id..':'..b.id;return a.n<b.n end};local t=setmetatable({},{__len=function()return #data end,__index=function(_,k)collectgarbage();serial=serial+1;return setmetatable({n=data[k],id=serial},mt)end,__newindex=function(_,k,v)collectgarbage();data[k]=v.n end});table.sort(t);collectgarbage();collectgarbage();return table.concat(data,','),table.concat(tr,'|')`]);
const encode=v=>isLuaString(v)?'s:'+Buffer.from(luaStringBytes(v),'latin1').toString('hex'):typeof v==='bigint'?'i:'+v:v===null?'nil':String(v);
let comparisons=0, randomized=0;
for(const seed of [0,1,0x12345678,0xffffffff])for(const [name,source]of cases) {
  const input=resolve(scratch,'input.lua');writeFileSync(input,source);
  const native=execFileSync(oracle,[input,String(seed)],{encoding:'utf8'}).trimEnd();
  let entropy=seed,calls=0;const vm=createLua({baseError:true,baseMeta:true,baseGC:true,instructionLimit:50000000});
  vm.sortRandomize=()=>{calls++;return entropy=(Math.imul(entropy,1664525)+1013904223)>>>0;};
  const values=vm.execute(source,name);
  assert.equal(values.map(encode).concat('entropy:'+calls).join('\n'),native,`${name}, seed=${seed}`);
  if(calls)randomized++; comparisons++;vm.heap.close();
}
assert.ok(randomized>0,'native randomized pivot branch must actually execute');
for(const [c,t]of [[0n,0n],[-1n,0n],[0x123456789abcdef0n,0xfedcba9876543210n]]) {
  const words=new Uint32Array(new BigUint64Array([BigInt.asUintN(64,c),BigInt.asUintN(64,t)]).buffer);
  assert.equal(luaSortEntropy(c,t),words.reduce((a,b)=>(a+b)>>>0,0));
}
console.log(`PASS: ${comparisons} native Lua sort value/comparator/table traces; ${randomized} randomized-pivot runs; exact entropy summation and invalid-comparator behavior.`);
