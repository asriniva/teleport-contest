/* Differential scheduler test against ORIGINAL pinned Lua5.4.8 scheduling.
 * Two deterministic native graphs: original C scheduler controls one, the JS
 * scheduler controls actual C mark/atomic/sweep kernels in the other. This
 * tests real collector phases, not a full-collection replacement or hand-
 * written C copy of the JS algorithm. Production JS graph integration has
 * its own tests; these private C kernels are never production dependencies. */
import assert from 'node:assert/strict';import fs from 'node:fs';import path from 'node:path';
import {fileURLToPath,pathToFileURL} from 'node:url';import {spawnSync} from 'node:child_process';
import {LuaGCScheduler,LuaGCGenerational,GC,GC_MODE,GC_OP,GC_AGE} from '../js/services/lua-gc-scheduler.js';
import {createLua,LuaTable,LuaUserdata} from '../js/services/lua/lua.js';
const root=fileURLToPath(new URL('../',import.meta.url)),work=path.join(root,'.cache/js-lua-gc-scheduler');fs.mkdirSync(work,{recursive:true});
const sdk=process.env.EMSDK||path.join(root,'.cache/emsdk'),env={...process.env,PATH:path.join(sdk,'node/24.19.0_64bit/bin')+path.delimiter+process.env.PATH};
function run(program,args,options={}){const r=spawnSync(program,args,{encoding:'utf8',env,timeout:120000,maxBuffer:8000000,...options});assert.equal(r.status,0,`${program}: ${r.error||r.stderr||r.stdout}`);return r.stdout;}
run('python3',['-c',`import pathlib,tarfile,hashlib
r=pathlib.Path(${JSON.stringify(root)});a=r/'.cache/lua-5.4.8.tar.gz'
assert hashlib.sha256(a.read_bytes()).hexdigest()=='4f18ddae154e793e46eeab727c59ef1c0c0c2b744e7b94219710d76f530629ae'
with tarfile.open(a) as t:t.extractall(r/'.cache/js-lua-gc-scheduler',filter='data')`]);
const src=path.join(work,'lua-5.4.8/src');let c=fs.readFileSync(path.join(src,'lgc.c'),'utf8');
c=c.replace('#include "ltm.h"','#include "ltm.h"\nstatic int teleport_probe_skip_finish, teleport_probe_skip_fin;');
assert.equal((c.match(/  finishgencycle\(L, g\);/g)||[]).length,2);
c=c.replaceAll('  finishgencycle(L, g);','  if (!teleport_probe_skip_finish) finishgencycle(L, g);');
c=c.replace('if (!g->gcemergency)\n    callallpendingfinalizers(L);','if (!g->gcemergency && !teleport_probe_skip_fin)\n    callallpendingfinalizers(L);');
c+=String.raw`
#include "lauxlib.h"
#include "lapi.h"
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#define API EMSCRIPTEN_KEEPALIVE
#else
#define API
#endif
static lua_State *probe_states[4];static int probe_finalized[4],probe_serial[4];
static int probe_finalize(lua_State *L){for(int i=0;i<4;i++)if(probe_states[i]&&G(probe_states[i])==G(L)){probe_finalized[i]++;break;}return 0;}
API void probe_init(int slot){lua_State *L=probe_states[slot]=luaL_newstate();lua_gc(L,LUA_GCSTOP);lua_createtable(L,2048,0);luaL_newmetatable(L,"probe");lua_pushcfunction(L,probe_finalize);lua_setfield(L,-2,"__gc");lua_pop(L,1);}
API long long probe_read(int slot,int field){lua_State *L=probe_states[slot];global_State *g=G(L);switch(field){
case 0:return gettotalbytes(g);case 1:return g->GCdebt;case 2:return g->GCestimate;case 3:return g->gcstate;case 4:return g->gckind;case 5:return g->gcstp;case 6:return g->gcstopem;case 7:return g->gcemergency;case 8:return g->lastatomic;case 9:return getgcparam(g->gcpause);case 10:return getgcparam(g->gcstepmul);case 11:return g->gcstepsize;case 12:return g->genminormul;case 13:return getgcparam(g->genmajormul);case 14:return probe_finalized[slot];case 15:return g->currentwhite;}return -999;}
API void probe_sync(int slot,int state,int kind,int stop,int emergency,int stopem,long long debt,unsigned long long estimate,unsigned long long lastatomic,int pause,int mul,int size,int minor,int major){global_State *g=G(probe_states[slot]);luaE_setdebt(g,debt);g->GCestimate=estimate;g->lastatomic=lastatomic;g->gcstate=state;g->gckind=kind;g->gcstp=stop;g->gcemergency=emergency;g->gcstopem=stopem;setgcparam(g->gcpause,pause);setgcparam(g->gcstepmul,mul);g->gcstepsize=size;g->genminormul=minor;setgcparam(g->genmajormul,major);}
API int probe_control(int slot,int op,int a,int b,int d){return lua_gc(probe_states[slot],op,a,b,d);}
API void probe_allocate(int slot,int count,int base){lua_State *L=probe_states[slot];for(int i=0;i<count;i++){Table *t=luaH_new(L);sethvalue(L,s2v(L->top.p),t);L->top.p++;luaH_resizearray(L,t,(i+base)%5);for(unsigned j=0;j<t->alimit;j++)setivalue(&t->array[j],j+base);lua_rawseti(L,1,1+(base+i)%2048);probe_serial[slot]++;}}
API void probe_drop(int slot,int count,int base){lua_State *L=probe_states[slot];for(int i=0;i<count;i++){lua_pushnil(L);lua_rawseti(L,1,1+(base+i)%2048);}}
API void probe_finalizers(int slot,int count){lua_State *L=probe_states[slot];luaL_getmetatable(L,"probe");Table *mt=hvalue(s2v(L->top.p-1));for(int i=0;i<count;i++){Udata *u=luaS_newudata(L,8,0);u->metatable=mt;luaC_checkfinalizer(L,obj2gco(u),mt);}lua_pop(L,1);}
API void probe_check(int slot){luaC_checkGC(probe_states[slot]);}
API void probe_emergency(int slot){luaC_fullgc(probe_states[slot],1);}
API void probe_mutate(int slot,int index){lua_State *L=probe_states[slot];lua_rawgeti(L,1,1+index%2048);if(lua_istable(L,-1)){Table *t=luaH_new(L);sethvalue(L,s2v(L->top.p),t);L->top.p++;lua_rawseti(L,-2,1);}lua_pop(L,1);}
API unsigned long long probe_kernel(int slot,int op){lua_State *L=probe_states[slot];global_State *g=G(L);switch(op){
case 0:restartcollection(g);return 0;case 1:return g->gray!=NULL;case 2:return propagatemark(g);case 3:return atomic(L);case 4:entersweep(L);return 0;
case 5:case 6:case 7:{int before=g->gcstate;unsigned count=op==5?sweepstep(L,g,GCSswpfinobj,&g->finobj):op==6?sweepstep(L,g,GCSswptobefnz,&g->tobefnz):sweepstep(L,g,GCSswpend,NULL);return count|((unsigned long long)(g->gcstate!=before)<<32);}
case 8:g->sweepgc=&g->finobj;return 0;case 9:g->sweepgc=&g->tobefnz;return 0;case 10:checkSizes(L,g);return 0;case 11:return g->tobefnz!=NULL;case 12:GCTM(L);return 0;case 13:enterinc(g);return 0;
case 14:teleport_probe_skip_finish=1;atomic2gen(L,g);teleport_probe_skip_finish=0;return 0;
case 15:teleport_probe_skip_finish=1;youngcollection(L,g);teleport_probe_skip_finish=0;return 0;
case 16:teleport_probe_skip_fin=1;finishgencycle(L,g);teleport_probe_skip_fin=0;return 0;
}return 0;}
API void probe_close(int slot){lua_close(probe_states[slot]);probe_states[slot]=NULL;}
static GCObject *age_objects[12],*age_head,*age_gray,*age_first;static UpVal *age_open[12];static int age_count;
API void probe_age_init(int count,int kinds){probe_init(3);lua_State *L=probe_states[3];global_State *g=G(L);GCObject *old=g->allgc;age_count=count;age_first=NULL;
 for(int i=0;i<count;i++){int kind=(kinds>>(2*i))&3;if(kind==1){lua_State *thread=lua_newthread(L);age_objects[i]=obj2gco(thread);lua_pop(L,1);}else if(kind>=2){UpVal *uv=gco2upv(luaC_newobj(L,LUA_VUPVAL,sizeof(UpVal)));setnilvalue(&uv->u.value);uv->v.p=kind==2?&g->nilvalue:&uv->u.value;if(kind==2){age_open[i]=uv;uv->u.open.previous=&age_open[i];uv->u.open.next=NULL;}age_objects[i]=obj2gco(uv);}else age_objects[i]=obj2gco(luaH_new(L));}
 g->allgc=old;for(int i=0;i<count;i++)age_objects[i]->next=i+1<count?age_objects[i+1]:NULL;age_head=count?age_objects[0]:NULL;age_gray=age_head;
}
API void probe_age_set(int index,int age,int color){global_State *g=G(probe_states[3]);GCObject *o=age_objects[index];o->marked=age|(color==0?otherwhite(g):color==2?bitmask(BLACKBIT):0);}
API void probe_age_run(int which){lua_State *L=probe_states[3];global_State *g=G(L);switch(which){case 0:markold(g,age_head,NULL);break;case 1:sweepgen(L,g,&age_head,NULL,&age_first);break;case 2:sweep2old(L,&age_head);break;case 3:for(int i=0;i<age_count;i++)*getgclist(age_objects[i])=i+1<age_count?age_objects[i+1]:NULL;correctgraylist(&age_gray);break;}}
static int age_contains(GCObject *head,GCObject *o,int gray){for(GCObject *p=head;p;p=gray?*getgclist(p):p->next)if(p==o)return 1;return 0;}
API int probe_age_read(int index,int field){GCObject *o=age_objects[index];int alive=age_contains(age_head,o,0);switch(field){case 0:return alive;case 1:return age_contains(age_gray,o,1);case 2:return alive?getage(o):-1;case 3:return alive?(o->marked&WHITEBITS):-1;case 4:return alive?!!isblack(o):-1;case 5:for(int i=0;i<age_count;i++)if(age_first==age_objects[i])return i;return -1;}return -99;}
API void probe_age_close(void){global_State *g=G(probe_states[3]);if(age_head){GCObject *last=age_head;while(last->next)last=last->next;last->next=g->allgc;g->allgc=age_head;}probe_close(3);}
`;
fs.writeFileSync(path.join(src,'lgc.c'),c);
const target=path.join(work,'oracle.mjs');const sources=fs.readdirSync(src).filter(n=>n.endsWith('.c')&&!['lua.c','luac.c'].includes(n)).map(n=>path.join(src,n));
run(path.join(sdk,'upstream/emscripten/emcc'),['-O2','-g','-Dluai_makeseed(L)=0','-sMEMORY64=1','-I'+src,...sources,'-lm','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sINVOKE_RUN=0','--no-entry','-o',target]);
const factory=(await import(pathToFileURL(target).href+'?gc='+Date.now())).default,wasm=await factory();
const read=(slot,field)=>BigInt(wasm._probe_read(slot,field));let scheduler;
function sync(){wasm._probe_sync(1,scheduler.state,scheduler.mode,scheduler.stop,Number(scheduler.emergency),Number(scheduler.gcstopem),scheduler.debt,scheduler.estimate,scheduler.lastatomic,scheduler.pause*4,scheduler.stepmul*4,scheduler.stepsize,scheduler.minormul,scheduler.majormul*4);}
function kernel(op){sync();const before=read(1,0),result=BigInt(wasm._probe_kernel(1,op));scheduler.allocated(read(1,0)-before);return result;}
const graph={restartCollection:()=>kernel(0),hasGray:()=>Boolean(kernel(1)),propagateOne:()=>kernel(2),atomic:()=>kernel(3),enterSweep:()=>kernel(4),beginSweepList:n=>kernel(n==='finobj'?8:9),sweep:n=>{const result=kernel(n==='allgc'?5:n==='finobj'?6:7);return{count:Number(result&0xffffffffn),done:Boolean(result>>32n)};},checkSizes:()=>kernel(10),hasFinalizers:()=>Boolean(kernel(11)),finalizeOne:()=>kernel(12),enterIncremental:()=>kernel(13),sweepToOld:()=>kernel(14),youngCollection:()=>kernel(15),finishGeneration:()=>kernel(16)};
wasm._probe_init(0);wasm._probe_init(1);
scheduler=new LuaGCScheduler({graph,getBytes:()=>read(1,0),debt:read(1,1),estimate:read(1,2),state:Number(read(1,3)),mode:Number(read(1,4)),stop:Number(read(1,5))});
const names=['bytes','debt','estimate','state','mode','stop','stopem','emergency','lastatomic','pause','stepmul','stepsize','minor','major','finalizers'];let comparisons=0,steps=0;const phases=new Set();const actions=[],nativeOperations=[],nativeSnapshots=[];
function compare(label,operation='I'){nativeOperations.push(operation);nativeSnapshots.push(names.map((_,field)=>read(0,field).toString()));sync();for(let field=0;field<names.length;field++){assert.equal(read(1,field),read(0,field),`${label}: ${names[field]} JS${read(1,field)} native${read(0,field)}`);comparisons++;}phases.add(scheduler.state);}
function control(op,a=0,b=0,c=0){const want=wasm._probe_control(0,op,a,b,c),got=scheduler.control(op,a,b,c);actions.push([op,a,b,c]);assert.equal(got,want,`control${actions.length} ${op}(${a},${b},${c}) stepsize${scheduler.stepsize} phase${scheduler.state}/${read(0,3)} debt${scheduler.debt}/${read(0,1)} return`);compare(`control${actions.length}:${op}`,`C ${op} ${a} ${b} ${c}`);if(op===GC_OP.STEP)steps++;}
function allocate(count,base){wasm._probe_allocate(0,count,base);sync();const before=read(1,0);wasm._probe_allocate(1,count,base);scheduler.allocated(read(1,0)-before);compare(`allocate${count}:${base}`,`A ${count} ${base}`);}
function drop(count,base){wasm._probe_drop(0,count,base);sync();const before=read(1,0);wasm._probe_drop(1,count,base);scheduler.allocated(read(1,0)-before);compare(`drop${count}:${base}`,`D ${count} ${base}`);}
function finalizers(count){wasm._probe_finalizers(0,count);sync();const before=read(1,0);wasm._probe_finalizers(1,count);scheduler.allocated(read(1,0)-before);compare(`finalizers${count}`,`F ${count}`);}
function check(){wasm._probe_check(0);scheduler.check();compare('automatic allocation checkpoint','K');}
function mutate(index){wasm._probe_mutate(0,index);sync();const before=read(1,0);wasm._probe_mutate(1,index);scheduler.allocated(read(1,0)-before);compare('old-to-young barrier',`M ${index}`);}
compare('initial');control(GC_OP.COLLECT);control(GC_OP.INC,200,100,1);allocate(350,0);finalizers(27);drop(175,0);
for(let i=0;i<450;i++)control(GC_OP.STEP,0);
for(const value of [0,1,3,4,5,199,201,1023,1024,-1,-5,-2147483648,2147483647]){control(GC_OP.SETPAUSE,value);control(GC_OP.SETSTEPMUL,value);}
control(GC_OP.INC,200,100,13);control(GC_OP.RESTART);
for(let i=0;i<120;i++){allocate(1,400+i);check();}
control(GC_OP.STOP);allocate(12,900);check();control(GC_OP.ISRUNNING);control(GC_OP.STEP,-1);control(GC_OP.STEP,1);control(GC_OP.RESTART);
control(GC_OP.GEN,20,100);for(let i=0;i<30;i++){allocate(4,1000+i*4);if(i%3===0)drop(2,1000+i*4);check();if(i%5===0)mutate(1000);}
finalizers(23);control(GC_OP.STEP,0);allocate(1000,0);check();drop(900,0);control(GC_OP.STEP,1024);control(GC_OP.STEP,0);control(GC_OP.COLLECT);
control(GC_OP.INC,200,100,1);finalizers(13);wasm._probe_emergency(0);scheduler.fullCollect(true);compare('emergency suppresses finalizers','E');control(GC_OP.COLLECT);
for(const size of [1,4,13,62,63,64,255,-1]){control(GC_OP.INC,200,100,size);allocate(1,1600);control(GC_OP.STEP,0);control(GC_OP.COLLECT);}
for(const args of [[-1,-1],[256,1024],[0,0],[1,1]]){control(GC_OP.GEN,...args);control(GC_OP.GEN,0,0);control(GC_OP.INC,0,0,0);}
control(GC_OP.COUNT);control(GC_OP.COUNTB);control(12345);
wasm._probe_close(0);wasm._probe_close(1);
// The same unmodified C scheduler trace is also executed by the actual macOS
// compiler/libc, rather than inferring host equivalence from configured Wasm.
const hostSource=path.join(work,'host-probe.c'),hostPath=path.join(work,'host-probe');
fs.writeFileSync(hostSource,`#include <stdio.h>
void probe_init(int);void probe_close(int);long long probe_read(int,int);int probe_control(int,int,int,int,int);
void probe_allocate(int,int,int);void probe_drop(int,int,int);void probe_finalizers(int,int);void probe_check(int);void probe_mutate(int,int);void probe_emergency(int);
int main(void){char op;int a,b,c,d;probe_init(0);while(scanf(" %c",&op)==1){switch(op){
case 'C':scanf("%d%d%d%d",&a,&b,&c,&d);probe_control(0,a,b,c,d);break;
case 'A':scanf("%d%d",&a,&b);probe_allocate(0,a,b);break;case 'D':scanf("%d%d",&a,&b);probe_drop(0,a,b);break;
case 'F':scanf("%d",&a);probe_finalizers(0,a);break;case 'K':probe_check(0);break;
case 'M':scanf("%d",&a);probe_mutate(0,a);break;case 'E':probe_emergency(0);break;}
for(int i=0;i<15;i++)printf(i?" %lld":"%lld",probe_read(0,i));puts("");}probe_close(0);return 0;}`);
run(process.env.CC||path.join(root,'.cache/wasm64-build/host-cc'),['-O2','-Dluai_makeseed(L)=0','-I'+src,...sources,hostSource,'-lm','-o',hostPath]);
const hostLines=run(hostPath,[],{input:nativeOperations.join('\n')+'\n'}).trimEnd().split('\n');assert.equal(hostLines.length,nativeSnapshots.length);
let nativeHostComparisons=0;for(let i=0;i<hostLines.length;i++){const fields=hostLines[i].split(' ');for(let field=0;field<names.length;field++){assert.equal(fields[field],nativeSnapshots[i][field],`macOS scheduler ${nativeOperations[i]} field${names[field]} trace${i}`);nativeHostComparisons++;}}

// Independently compare generation age/list helpers to the actual C static
// functions, including open/closed upvalues and retained thread gray links.
let ageCases=0,randomState=0x51a82c6f;function random(){randomState^=randomState<<13;randomState^=randomState>>>17;randomState^=randomState<<5;return randomState>>>0;}
for(let which=0;which<4;which++)for(let sample=0;sample<160;sample++){
 if(process.env.GC_PROBE_TRACE)console.error("age-case",which,sample);const count=8,kinds=Array.from({length:count},()=>random()%(which===3?2:4)),kindBits=kinds.reduce((v,k,i)=>v|(k<<(2*i)),0);wasm._probe_age_init(count,kindBits);
 const current=Number(read(3,15)),other=current===8?16:current===16?8:current^3;
 const records=kinds.map((kind,i)=>{const age=random()%7;let color=age<2?0:random()%2+1;if(which===0&&age===3)color=2;if(which===2&&kind===1)color=1;if(which===3&&age===5)color=1;
  wasm._probe_age_set(i,age,color);return{id:i,kind:kind===0?'table':kind===1?'thread':'upvalue',open:kind===2,age,white:color===0?other:0,black:color===2,next:null,grayNext:null};});
 records.forEach((r,i)=>{r.next=records[i+1]??null;r.grayNext=records[i+1]??null;});const freed=new Set(),model={lists:{allgc:records[0]},boundaries:{},grayLists:{grayagain:records[0]},currentWhite:current,freeRecord:r=>freed.add(r),reallyMark:r=>{r.white=0;r.black=r.kind==='upvalue'&&!r.open;},linkGrayAgain:r=>{r.grayNext=model.grayLists.grayagain;model.grayLists.grayagain=r;}};
 const helper=new LuaGCGenerational(model);let first=null;
 if(which===0)helper.markOld(records[0],null);else if(which===1)first=helper.sweepGen(helper.cursor('allgc'),null).firstOld1;else if(which===2)helper.sweepToOldList('allgc');else helper.correctGrayList({object:model.grayLists,key:'grayagain'});
 wasm._probe_age_run(which);
 for(const record of records){const alive=!freed.has(record);assert.equal(alive,Boolean(wasm._probe_age_read(record.id,0)),`age${which}/${sample} alive`);comparisons++;
  if(alive){for(const[field,want]of[[2,record.age],[3,record.white],[4,Number(record.black)]]){assert.equal(wasm._probe_age_read(record.id,field),want,`age${which}/${sample} record${record.id} field${field}`);comparisons++;}}
  if(which===3){let present=false;for(let r=model.grayLists.grayagain;r;r=r.grayNext)if(r===record)present=true;assert.equal(wasm._probe_age_read(record.id,1),Number(present));comparisons++;}
 }
 if(which===1){assert.equal(wasm._probe_age_read(0,5),first?.id??-1);comparisons++;}
 wasm._probe_age_close();ageCases++;
}
// Drive the production JS graph one real phase at a time, with mutations
// between calls. Host references deliberately do not constitute Lua roots.
let graphChecks=0;
function checkGraph(value,message){assert.ok(value,message);graphChecks++;}
function untilPhase(s,phase){let guard=0;while(s.state!==phase){s.singleStep();assert.ok(++guard<20000,'phase progress');}}
function finishCycle(s){if(s.state===GC.PAUSE)s.singleStep();untilPhase(s,GC.PAUSE);}
for(const mode of [GC_MODE.INC,GC_MODE.GEN]){
 const vm=createLua({baseError:true,baseMeta:true,baseGC:true}),heap=vm.heap,s=heap.attachScheduler();
 const table=()=>heap.with(()=>new LuaTable());const parent=table();vm.setGlobal('parent',parent);
 const discarded=Array.from({length:451},table);s.singleStep();
 checkGraph(discarded.every(v=>!v.luaFreed),'starting a cycle does not substitute full collection');
 untilPhase(s,GC.PROPAGATE);let guard=0;while(!heap.records.get(parent).black){s.singleStep();assert.ok(++guard<20000);}
 const child=table();child.rawset('value',71n);parent.rawset('child',child);
 checkGraph(!heap.records.get(parent).black,'black table mutation regrays its record');
 untilPhase(s,GC.SWPALLGC);const duringSweep=table();finishCycle(s);
 checkGraph(discarded.every(v=>v.luaFreed),'incremental sweep frees unreachable records');
 checkGraph(!child.luaFreed&&parent.rawget('child').rawget('value')===71n,'backward barrier preserves newly linked child');
 checkGraph(!duringSweep.luaFreed,'allocation during sweep survives the current cycle');
 finishCycle(s);checkGraph(duringSweep.luaFreed,'next cycle collects unrooted sweep allocation');
 if(mode===GC_MODE.GEN)s.control(GC_OP.GEN);
 const weak=table(),weakMode=table();weakMode.rawset('__mode','kv');weak.metatable=weakMode;vm.setGlobal('weak',weak);
 const key=table(),value=table();value.rawset('key',key);weak.rawset(key,value);
 if(mode===GC_MODE.GEN)s.control(GC_OP.STEP,0);else finishCycle(s);
 checkGraph(weak.values.size===0&&key.luaFreed&&value.luaFreed,'ephemeron cycle is unreachable');
 const retained=table();parent.rawset('retained',retained);
 for(let i=0;i<4;i++){if(mode===GC_MODE.GEN)s.control(GC_OP.STEP,0);else finishCycle(s);}
 const young=table();young.rawset('value',97n);retained.rawset('young',young);
 if(mode===GC_MODE.GEN)s.control(GC_OP.STEP,0);else finishCycle(s);
 checkGraph(!young.luaFreed&&retained.rawget('young').rawget('value')===97n,'old-to-young graph edge survives minor or incremental collection');
 parent.rawset('retained',null);s.control(GC_OP.COLLECT);
 checkGraph(retained.luaFreed&&young.luaFreed,'major collection frees disconnected old graph');
 heap.close();checkGraph(heap.memoryTracker.bytes===0,'phased graph close releases all owned storage');
}
// Finalizer execution must be bounded separately from atomic/sweep work.
{
 const vm=createLua({baseError:true,baseMeta:true,baseGC:true}),heap=vm.heap,s=heap.attachScheduler();let finalized=0;
 const mt=heap.with(()=>new LuaTable());mt.rawset('__gc',()=>{finalized++;return[];});vm.setGlobal('mt',mt);
 const values=heap.with(()=>Array.from({length:25},()=>new LuaUserdata(new Uint8Array(1),mt)));
 untilPhase(s,GC.CALLFIN);checkGraph(finalized===0,'marking and sweeping do not execute finalizers');
 s.singleStep();checkGraph(finalized===10&&s.state===GC.CALLFIN,'one finalizer step calls at most ten callbacks');
 s.singleStep();checkGraph(finalized===20,'second finalizer batch preserves per-step limit');
 finishCycle(s);checkGraph(finalized===25&&values.every(v=>!v.luaFreed),'finalized objects remain until a following cycle');
 finishCycle(s);checkGraph(values.every(v=>v.luaFreed),'following cycle reclaims finalized userdata');
 const emergency=heap.with(()=>new LuaUserdata(new Uint8Array(1),mt));s.fullCollect(true);
 checkGraph(finalized===25&&!emergency.luaFreed,'emergency collection queues but does not run finalizers');
 s.control(GC_OP.COLLECT);checkGraph(finalized===26,'normal collection runs the pending emergency finalizer');
 heap.close();checkGraph(heap.memoryTracker.bytes===0,'finalizer graph close releases all storage');
}
fs.writeFileSync(path.join(work,'validated.json'),JSON.stringify({comparisons,nativeHostComparisons,steps,ageCases,graphChecks,phases:[...phases],actions},null,2)+'\n');
console.log(`PASS: ${comparisons} configured-C collector fields/returns + ${nativeHostComparisons} actual macOS collector fields; ${steps} real incremental steps, ${ageCases} native generation/list cases, ${graphChecks} production JS graph checks, automatic allocation checkpoints, minors/majors, barriers, finalizers, emergency policy, byte debt and parameter wrapping. Graph kernels are private native-oracle helpers, not production dependencies.`);
