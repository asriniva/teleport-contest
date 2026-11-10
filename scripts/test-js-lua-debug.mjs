/** Native Lua5.4.8 hook/disassembly event replay and NetHack resource contracts. */
import assert from 'node:assert/strict';
import { mkdirSync, readFileSync, writeFileSync, readdirSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { fileURLToPath } from 'node:url';
import { resolve } from 'node:path';
import { LuaDebugState, LuaAllocationTracker, LuaMemoryError, LuaDiagnostics, NethackLuaBudget, LuaTimeLimitError, luaChunkId, luaFunctionLine, createNethackWarningHandler } from '../js/services/lua-debug.js';
const root = fileURLToPath(new URL('../', import.meta.url)), scratch = resolve(root, '.cache/js-lua-debug'); mkdirSync(scratch, { recursive: true });
const src = resolve(root, '.cache/js-dependency-lua/lua-5.4.8/src');
const c = String.raw`
#include <stdio.h>
#include <stdlib.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "lstate.h"
#include "ldebug.h"
#include "lobject.h"
static void hook(lua_State *L,lua_Debug *ar){
 int event=ar->event, eventline=ar->currentline;
 lua_getinfo(L,"nSlut",ar);
 CallInfo *ci=L->ci; int pc=isLua(ci)?(int)(ci->u.l.savedpc-clLvalue(s2v(ci->func.p))->p->code)-1:-1;
 Proto *p=isLua(ci)?clLvalue(s2v(ci->func.p))->p:NULL;
 printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s\t%s\t%s\t%d\t",event,eventline,pc,ar->currentline,ar->linedefined,ar->lastlinedefined,ar->nparams,ar->isvararg,ar->source,ar->namewhat,ar->name?ar->name:"",ar->istailcall);
 if(p)for(int i=0;i<p->sizecode;i++)printf("%s%d",i?",":"",luaG_getfuncline(p,i)); puts("");
}
int main(int argc,char **argv){
 if(argc>1 && argv[1][0]=='s'){char out[60];const char *v[]={"=literal","@/long/path/test.lua","first\nsecond","abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", "@abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", "=abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};for(int i=0;i<6;i++){luaO_chunkid(out,v[i],strlen(v[i]));puts(out);}return 0;}
 lua_State *L=luaL_newstate();luaL_openlibs(L);
 const char *program="local function add(a,b)\n local c=a+b\n return c\nend\nlocal s=0\nfor i=1,8 do\n s=add(s,i)\nend\nlocal function tail(x)\n if x>0 then return tail(x-1) end\n return s\nend\nreturn tail(3)";
 if(luaL_loadbuffer(L,program,strlen(program),"@debug-test.lua"))return 2;
 lua_sethook(L,hook,atoi(argv[1]),atoi(argv[2]));int rc=lua_pcall(L,0,0,0);lua_sethook(L,NULL,0,0);if(rc)fprintf(stderr,"%s\n",lua_tostring(L,-1));lua_close(L);return rc;
}`;
writeFileSync(resolve(scratch, 'probe.c'), '#include <string.h>\n'+c);
execFileSync(resolve(root,'.cache/wasm64-build/host-cc'), ['-O2', '-I'+src, resolve(scratch,'probe.c'), ...readdirSync(src).filter(n=>n.endsWith('.c')&&!['lua.c','luac.c'].includes(n)).map(n=>resolve(src,n)), '-lm', '-o', resolve(scratch,'probe')]);
const run = (mask,count)=>execFileSync(resolve(scratch,'probe'),[String(mask),String(count)],{encoding:'utf8'}).trimEnd().split('\n').filter(Boolean).map(line=>{const x=line.split('\t');return {event:+x[0],eventline:+x[1],pc:+x[2],currentline:+x[3],linedefined:+x[4],lastlinedefined:+x[5],numparams:+x[6],is_vararg:+x[7],source:x[8],namewhat:x[9],name:x[10]||null,istailcall:+x[11],lines:x[12].split(',').map(Number)};});
const trace=run(11,1); let comparisons=0;
for(const mask of [1,2,3,4,8,12,15])for(const count of [1,2,3,7,1000]){
 const expected=run(mask,count), thread={}, debug=new LuaDebugState({mainThread:thread}), actual=[];
 debug.sethook(thread,(_t,ar)=>{const eventline=ar.currentline;debug.getinfo(thread,'nSlut',ar);actual.push({event:ar.event,eventline,currentline:ar.currentline,source:ar.source,name:ar.name,namewhat:ar.namewhat,istailcall:ar.istailcall});},mask,count);
 for(const step of trace){
  if(step.event===0||step.event===4){
   const details={prototype:{...step,code:step.lines},source:step.source,name:step.name,namewhat:step.namewhat,what:step.linedefined===0?'main':step.linedefined<0?'C':'Lua',deferCallHook:true};
   let frame;
   if(step.event===4)frame=debug.frameTailcall(thread,debug.thread(thread).frames.at(-1),details);else frame=debug.frameEnter(thread,details);
   frame.pc=step.pc;frame.currentline=step.currentline;debug.callHook(thread,step.event===4);
  }else if(step.event===3)debug.opcode(thread,step.pc,step.currentline);
  else if(step.event===1){const f=debug.thread(thread).frames.at(-1);f.pc=step.pc;f.currentline=step.currentline;debug.frameLeave(thread,f);}
 }
 assert.deepEqual(actual,expected.map(({event,eventline,currentline,source,name,namewhat,istailcall})=>({event,eventline,currentline,source,name,namewhat,istailcall})),`mask ${mask} count ${count}`);comparisons+=actual.length;
}
const nativeIds=execFileSync(resolve(scratch,'probe'),['s'],{encoding:'utf8'}).trimEnd().split('\n');
assert.deepEqual(['=literal','@/long/path/test.lua','first\nsecond','abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz','@abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz','=abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'].map(v=>luaChunkId(v)),nativeIds);
const t={}, d=new LuaDebugState({mainThread:t});
const f=d.frameEnter(t,{prototype:{source:'@test.lua',linedefined:2,lastlinedefined:4,numparams:1,lines:[2,3,4]},name:'foo',namewhat:'local'});d.frameLine(f,3);
assert.equal(d.traceback(t,'failure',0),"failure\nstack traceback:\n\ttest.lua:3: in local 'foo'");assert.equal(d.where(t,0),'test.lua:3: ');
const ar={};assert.equal(d.getstack(t,0,ar),1);assert.equal(d.getstack(t,-1,{}),0);assert.equal(d.getstack(t,1,{}),0);assert.equal(d.getinfo(t,'SluL',ar),1);assert.deepEqual([...ar.activelines],[2,3,4]);assert.equal(d.getinfo(t,'invalid',ar),0);
const thrown={};d.captureError(t,thrown);d.frameLeave(t,f,0,{error:true});assert.equal(thrown.luaDebugFrames.length,1);
// Hook callbacks are nonrecursive; hook count still advances when they run Lua.
const g=d.frameEnter(t,{prototype:{lines:[1,1,1],code:[0,0,0]}});let hooks=0;
d.sethook(t,()=>{hooks++;d.opcode(t,0,1);},8,1);d.opcode(t,0,1);assert.equal(hooks,1);d.frameLeave(t,g);
assert.equal(luaFunctionLine({linedefined:10,lineinfo:[0,1,255,128,1],abslineinfo:[{pc:3,line:200}]},4),201);
const blocks=new Map();let id=0,fail=false,collects=0;const allocator=(_u,p,_old,n)=>{if(!n){blocks.delete(p);return null;}if(fail)return null;const next={id:++id};blocks.delete(p);blocks.set(next,n);return next;};
const deltas=[];const a=new LuaAllocationTracker({allocator,userdata:17,memlimit:100,onAllocated:n=>deltas.push(n)});let p=a.realloc(null,6,120);a.ready=true;
assert.equal(a.bytes,120);assert.equal(a.realloc(p,120,10,{safe:false}),null);assert.equal(a.bytes,120);p=a.realloc(p,120,0);assert.equal(a.bytes,0);
p=a.realloc(null,0,100);const q=a.realloc(null,0,1);assert.equal(a.bytes,101);assert.throws(()=>a.realloc(null,0,1),LuaMemoryError);a.realloc(q,1,0);a.realloc(p,100,0);
a.collect=()=>{collects++;fail=false;};fail=true;p=a.realloc(null,0,2048);assert.equal(collects,1);assert.equal(a.count(),2);assert.equal(a.countb(),0);a.realloc(p,2048,0);
a.collect=()=>{collects++;};fail=true;assert.throws(()=>a.realloc(null,0,2),LuaMemoryError);assert.equal(a.bytes,0);assert.equal(collects,2);const out={};assert.equal(a.getallocf(out),allocator);assert.equal(out.value,17);
assert.deepEqual(deltas,[120,-120,100,1,-1,-100,2048,-2048]);
const budget=new NethackLuaBudget({steps:2000,sid:3,name:'test'});budget.hook();assert.equal(budget.steps,1000);assert.throws(()=>budget.hook(),e=>e instanceof LuaTimeLimitError&&e.message==='Lua time exceeded 3:test');assert.equal(budget.statctr,1);
const per=new NethackLuaBudget({perpcall:1500});per.beginPcall('one');per.hook();assert.equal(per.steps,500);per.beginPcall('two');assert.equal(per.steps,1500);assert.equal(per.statctr,0);
const diagnostics=new LuaDiagnostics(),warnings=[];diagnostics.setwarnf(createNethackWarningHandler((...v)=>warnings.push(v),8));diagnostics.warning('abc',true);diagnostics.warning('defghij');diagnostics.warning('next');assert.deepEqual(warnings,[['[lua]','abcdefg'],['[lua]','next']]);let panic;diagnostics.atpanic((_L,e)=>{panic=e;});const error=new Error('panic');assert.throws(()=>diagnostics.unprotected({},error),e=>e===error);assert.equal(panic,error);
console.log(`PASS: ${comparisons} native Lua5.4.8 hook events across 35 mask/count combinations, source IDs, debug frames, allocation failure/retry, exact NetHack budget/warning contracts.`);
