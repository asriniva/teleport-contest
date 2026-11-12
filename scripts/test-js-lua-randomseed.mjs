// Original Lua5.4.8 no-argument randomseed entropy seam and exact RNG streams.
// Native time/address are supplied through the same explicit host-entropy seam
// used by the ABI; production does not compile, load, or fetch native code.
import assert from 'node:assert/strict';
import {createHash} from 'node:crypto';
import {mkdirSync,readFileSync,readdirSync,writeFileSync} from 'node:fs';
import {execFileSync} from 'node:child_process';
import {fileURLToPath} from 'node:url';
import {resolve} from 'node:path';
import {createLuaBytecodeVM} from '../js/lua/bytecode-vm.js';
import {createLua} from '../js/lua/lua.js';
const root=fileURLToPath(new URL('../',import.meta.url)),work=resolve(root,'.cache/js-dependency-lua/randomseed');mkdirSync(work,{recursive:true});
const archive=resolve(root,'.cache/lua-5.4.8.tar.gz');assert.equal(createHash('sha256').update(readFileSync(archive)).digest('hex'),'4f18ddae154e793e46eeab727c59ef1c0c0c2b744e7b94219710d76f530629ae');
execFileSync('python3',['-c','import tarfile,sys\nwith tarfile.open(sys.argv[1]) as t:t.extractall(sys.argv[2],filter="data")',archive,work]);
const src=resolve(work,'lua-5.4.8/src'),oracle=resolve(work,'oracle');
writeFileSync(resolve(work,'oracle.c'),String.raw`
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
int main(int argc,char**argv){lua_State*L=luaL_newstate();luaL_openlibs(L);int rc=luaL_loadfile(L,argv[1]);if(!rc)rc=lua_pcall(L,0,LUA_MULTRET,0);if(rc){fprintf(stderr,"%s\n",lua_tostring(L,-1));return rc;}for(int i=1;i<=lua_gettop(L);i++){if(lua_isinteger(L,i))printf("i:%lld\n",(long long)lua_tointeger(L,i));else{double d=lua_tonumber(L,i);uint64_t bits;memcpy(&bits,&d,8);printf("f:%016llx\n",(unsigned long long)bits);}}lua_close(L);return 0;}
`);
execFileSync(resolve(root,'.cache/wasm64-build/host-cc'),['-O2','-DLUA_USE_POSIX','-I'+src,resolve(work,'oracle.c'),...readdirSync(src).filter(n=>n.endsWith('.c')&&!['lua.c','luac.c'].includes(n)).map(n=>resolve(src,n)),'-lm','-o',oracle]);
const source='local a,b=math.randomseed();local t={a,b};for i=1,20 do t[#t+1]=math.random();t[#t+1]=math.random(1000000);t[#t+1]=math.random(0)end;return table.unpack(t)';
const input=resolve(work,'fixture.lua');writeFileSync(input,source);const expected=execFileSync(oracle,[input],{encoding:'utf8'}).trim().split('\n'),seeds=expected.slice(0,2).map(s=>BigInt(s.slice(2)));
const encode=value=>{if(typeof value==='bigint')return'i:'+value;const data=new DataView(new ArrayBuffer(8));data.setFloat64(0,value,false);return'f:'+data.getBigUint64(0,false).toString(16).padStart(16,'0');};
for(const factory of [createLuaBytecodeVM,createLua]){
 const vm=factory({baseError:true});let calls=0;vm.randomSeed=()=>{calls++;return seeds;};assert.deepEqual(vm.execute(source,'@fixture.lua').map(encode),expected);assert.equal(calls,1);
 assert.deepEqual(vm.execute('local a,b=math.randomseed(0,0);return a,b'),[0n,0n]);assert.equal(calls,1);
 assert.deepEqual(vm.execute('local ok=pcall(math.randomseed,nil);return ok'),[false]);assert.equal(calls,1);vm.heap.close();
}
console.log('PASS: native no-argument randomseed time/address entropy seam and 60 exact RNG results in bytecode and AST VMs; explicit seed and nil/none distinction preserved.');
