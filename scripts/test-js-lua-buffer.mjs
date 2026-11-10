/** Native LuaL_Buffer allocator lifecycle, including raw backing allocations. */
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import {execFileSync} from 'node:child_process';
import {fileURLToPath} from 'node:url';
import {createLuaCState} from '../js/services/lua/lapi.js';
import {createLuaBytecodeVM} from '../js/services/lua-bytecode-vm.js';
import {LuaBuffer} from '../js/services/lua-buffer.js';
import {LuaError} from '../js/services/lua/lobject.js';
const root=fileURLToPath(new URL('../',import.meta.url)),scratch=path.join(root,'.cache/js-lua-buffer');fs.mkdirSync(scratch,{recursive:true});
const source=path.join(root,'.cache/wasm64-build/tree/lib/lua-5.4.8/src');
const code=String.raw`
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
typedef struct Block{void*p;size_t n;unsigned id;struct Block*next;}Block;
typedef struct Mem{Block*blocks;size_t bytes,attempt,fail;unsigned next;}Mem;
static void*alloc(void*ud,void*p,size_t old,size_t n){Mem*m=ud;Block**at=&m->blocks,*b=NULL;while(*at&&(*at)->p!=p)at=&(*at)->next;if(p){b=*at;if(!b||b->n!=old)abort();}
 if(n&&++m->attempt>=m->fail){printf("R %zu %zu %zu %zu\n",m->attempt,old,n,m->bytes);return NULL;}
 unsigned id=b?b->id:n?++m->next:0;size_t previous=b?b->n:0;void*q=n?realloc(p,n):(free(p),(void*)NULL);if(n&&!q)abort();m->bytes+=n-previous;
 if(!n){if(b){*at=b->next;free(b);}}else{if(!b){b=malloc(sizeof(*b));b->id=id;b->next=m->blocks;m->blocks=b;}b->p=q;b->n=n;}
 printf("A %u %zu %zu %zu\n",id,old,n,m->bytes);return q;}
static int count,each,repeat,values,raise_error;
static int run(lua_State*L){luaL_Buffer b;luaL_buffinit(L,&b);char*text=malloc(each?each:1);memset(text,'x',each);
 for(int i=0;i<count;i++){luaL_addlstring(&b,text,each);if(values){lua_pushinteger(L,12345);luaL_addvalue(&b);}}free(text);
 if(raise_error){lua_pushliteral(L,"buffer failure");return lua_error(L);}luaL_pushresult(&b);return 1;}
int main(int argc,char**argv){count=atoi(argv[1]);each=atoi(argv[2]);repeat=atoi(argv[3]);values=atoi(argv[4]);raise_error=atoi(argv[5]);Mem m={0};m.fail=argc>6?strtoull(argv[6],NULL,10):(size_t)-1;lua_State*L=lua_newstate(alloc,&m);printf("P state %d %zu %zu\n",L?0:4,m.bytes,m.attempt);if(!L)return m.bytes?9:0;
 for(int i=0;i<repeat;i++){lua_pushcfunction(L,run);int rc=lua_pcall(L,0,1,0);printf("P run %d %zu %zu\n",rc,m.bytes,m.attempt);lua_pop(L,1);}lua_close(L);printf("P close 0 %zu %zu\n",m.bytes,m.attempt);return m.bytes?8:0;}
`;
fs.writeFileSync(path.join(scratch,'oracle.c'),code);
const sources=fs.readdirSync(source).filter(n=>n.endsWith('.c')&&!['lua.c','luac.c'].includes(n)).map(n=>path.join(source,n));
execFileSync(path.join(root,'.cache/wasm64-build/host-cc'),['-O2','-I'+source,path.join(scratch,'oracle.c'),...sources,'-lm','-o',path.join(scratch,'oracle')]);
function jsTrace([count,each,repeat,values,raise],fail=Infinity){
 const trace=[],blocks=new Map();let bytes=0,attempt=0,next=0,L;
 const allocator=(_ud,p,old,n)=>{const b=p===null?null:blocks.get(p);if(p!==null)assert.equal(b?.n,old);if(n&&++attempt>=fail){trace.push(`R ${attempt} ${old} ${n} ${bytes}`);return null;}
  const q=n?p??{id:++next}:null,id=b?.id??q?.id??0;bytes+=n-(b?.n??0);if(p!==null)blocks.delete(p);if(n)blocks.set(q,{n,id});trace.push(`A ${id} ${old} ${n} ${bytes}`);return q;};
 const mark=(name,status)=>trace.push(`P ${name} ${status} ${bytes} ${attempt}`);
 try{L=createLuaCState({vmFactory:createLuaBytecodeVM,memoryAllocator:allocator});}catch(e){assert.equal(e.status,4);mark('state',4);assert.equal(bytes,0);return trace;}
 mark('state',0);
 for(let i=0;i<repeat;i++){
  L.lua_pushcfunction(state=>{const b=new LuaBuffer(state.vm);try{for(let j=0;j<count;j++){b.add('x'.repeat(each));if(values)b.addValue(12345n);}if(raise)throw new LuaError('buffer failure');state.push(b.finish());return 1;}catch(e){b.close(e);throw e;}finally{b.close();}});
  mark('run',L.lua_pcall(0,1));L.lua_pop(1);
 }
 L.lua_close();mark('close',0);assert.equal(bytes,0);assert.equal(blocks.size,0);return trace;
}
let passed=0;
const fixtures=[[0,0,1,0,0],[1,1,1,0,0],[1,1023,1,0,0],[1,1024,1,0,0],[1,1025,1,0,0],[1,1536,1,0,0],[10,700,1,0,0],[3,2000,3,0,0],[200,17,1,1,0],[1,1,1,0,1],[1,1025,1,0,1],[10,700,1,0,1]];
for(const fixture of fixtures){
 const native=execFileSync(path.join(scratch,'oracle'),fixture.map(String),{encoding:'utf8'}).trim().split('\n'),js=jsTrace(fixture);
 fs.writeFileSync(path.join(scratch,'last.json'),JSON.stringify({fixture,native,js},null,2));
 assert.deepEqual(js,native,'complete native Lua buffer callbacks '+fixture.join('/'));passed++;
}
let refused=0;
for(const fixture of [[1,1025,1,0,0],[10,700,1,0,0],[200,17,1,1,0]])for(let fail=56;fail<=80;fail++){
 const native=execFileSync(path.join(scratch,'oracle'),[...fixture,fail].map(String),{encoding:'utf8'}).trim().split('\n'),js=jsTrace(fixture,fail);
 fs.writeFileSync(path.join(scratch,'last.json'),JSON.stringify({fixture,fail,native,js},null,2));
 assert.deepEqual(js,native,'native Lua buffer allocation refusal '+fixture.join('/')+'/'+fail);refused++;
}
console.log(`PASS: ${passed} native LuaL_Buffer complete allocator/free transcripts and ${refused} allocation refusal schedules.`);
