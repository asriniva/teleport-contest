// Direct original lcode.c kernels, independent of both JavaScript parsers.
import assert from 'node:assert/strict';
import { mkdirSync,readFileSync,writeFileSync,readdirSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import { createHash } from 'node:crypto';
import { LuaCodeGenerator, Exp, ExpKind as K, BinOpr as B, UnOpr as U, initExp } from '../js/lua/incremental-codegen.js';
import { LUA_OP as O } from '../js/lua/codegen.js';
import { isLuaString,luaStringBytes } from '../js/lua/lobject.js';
const root=fileURLToPath(new URL('../',import.meta.url)),work=resolve(root,'.cache/js-lua-debug/incremental-codegen');mkdirSync(work,{recursive:true});
const archive=resolve(root,'.cache/lua-5.4.8.tar.gz');assert.equal(createHash('sha256').update(readFileSync(archive)).digest('hex'),'4f18ddae154e793e46eeab727c59ef1c0c0c2b744e7b94219710d76f530629ae');
execFileSync('python3',['-c','import tarfile,sys\nwith tarfile.open(sys.argv[1]) as t:t.extractall(sys.argv[2],filter="data")',archive,work]);
const source=resolve(work,'lua-5.4.8/src'),oracle=resolve(work,'oracle');
writeFileSync(resolve(work,'oracle.c'),String.raw`
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lfunc.h"
#include "ltable.h"
#include "lstring.h"
#include "lcode.c"
static void val(TValue*v){
 if(ttisnil(v))printf("[\"nil\"]");else if(ttisboolean(v))printf("[\"bool\",%s]",ttistrue(v)?"true":"false");
 else if(ttisinteger(v))printf("[\"int\",\"%lld\"]",(long long)ivalue(v));
 else if(ttisfloat(v)){uint64_t bits;double d=fltvalue(v);memcpy(&bits,&d,8);printf("[\"float\",\"%016llx\"]",(unsigned long long)bits);}
 else if(ttisstring(v)){printf("[\"str\",\"");const unsigned char*s=(void*)getstr(tsvalue(v));for(size_t n=0;n<tsslen(tsvalue(v));n++)printf("%02x",s[n]);printf("\"]");}else abort();
}
static void expression(expdesc*e){printf("{\"k\":%d,\"t\":%d,\"f\":%d",e->k,e->t,e->f);
 if(e->k==VKINT)printf(",\"ival\":\"%lld\"",(long long)e->u.ival);
 else if(e->k==VKFLT){uint64_t b;memcpy(&b,&e->u.nval,8);printf(",\"nval\":\"%016llx\"",(unsigned long long)b);}
 else if(e->k==VKSTR){printf(",\"strval\":\"");for(size_t n=0;n<tsslen(e->u.strval);n++)printf("%02x",(unsigned char)getstr(e->u.strval)[n]);printf("\"");}
 else if(e->k==VLOCAL)printf(",\"ridx\":%d,\"vidx\":%d",e->u.var.ridx,e->u.var.vidx);
 else if(vkisindexed(e->k))printf(",\"table\":%d,\"index\":%d",e->u.ind.t,e->u.ind.idx);
 else if(e->k!=VTRUE&&e->k!=VFALSE&&e->k!=VNIL)printf(",\"info\":%d",e->u.info);printf("}");}
int main(int argc,char**argv){
 if(argc!=2)return 2;FILE*input=fopen(argv[1],"rb");if(!input)return 3;lua_State*L=luaL_newstate();LexState ls={0};FuncState fs={0};Dyndata dyd={0};Vardesc locals[255]={0};expdesc e[32]={0};int active=0;
 Proto*p=luaF_newproto(L);p->maxstacksize=2;ls.L=L;ls.fs=&fs;ls.h=luaH_new(L);ls.dyd=&dyd;ls.lastline=ls.linenumber=1;ls.source=luaS_newliteral(L,"@kernel.lua");dyd.actvar.arr=locals;dyd.actvar.n=255;fs.f=p;fs.ls=&ls;
 for(int n=0;n<255;n++){locals[n].vd.kind=VDKREG;locals[n].vd.ridx=n;}for(int n=0;n<32;n++)e[n].t=e[n].f=NO_JUMP;
 char op[64],arg[4096];int a,b,c,d,x;
 while(fscanf(input,"%63s",op)==1){
  if(!strcmp(op,"E")){fscanf(input,"%d%d%4095s%d",&a,&b,arg,&c);e[a].k=b;e[a].t=e[a].f=NO_JUMP;e[a].u.info=0;if(a>=active)active=a+1;
   if(b==VKINT)e[a].u.ival=strtoll(arg,NULL,10);else if(b==VKFLT){uint64_t bits=strtoull(arg,NULL,16);memcpy(&e[a].u.nval,&bits,8);}else if(b==VKSTR){char bytes[2048];size_t n=strlen(arg)/2;for(size_t i=0;i<n;i++){unsigned byte;sscanf(arg+i*2,"%2x",&byte);bytes[i]=byte;}e[a].u.strval=luaS_newlstr(L,bytes,n);}else if(b==VLOCAL){e[a].u.var.ridx=atoi(arg);e[a].u.var.vidx=c;}else if(vkisindexed(b)){e[a].u.ind.t=atoi(arg);e[a].u.ind.idx=c;}else e[a].u.info=atoi(arg);
  }
  else if(!strcmp(op,"locals")){fscanf(input,"%d",&a);fs.freereg=fs.nactvar=a;}
  else if(!strcmp(op,"line")){fscanf(input,"%d",&a);ls.lastline=ls.linenumber=a;}
  else if(!strcmp(op,"infix")){fscanf(input,"%d%d",&a,&b);luaK_infix(&fs,a,&e[b]);}
  else if(!strcmp(op,"posfix")){fscanf(input,"%d%d%d%d",&a,&b,&c,&d);luaK_posfix(&fs,a,&e[b],&e[c],d);}
  else if(!strcmp(op,"prefix")){fscanf(input,"%d%d%d",&a,&b,&c);luaK_prefix(&fs,a,&e[b],c);}
  else if(!strcmp(op,"exp2nextreg")){fscanf(input,"%d",&a);luaK_exp2nextreg(&fs,&e[a]);}
  else if(!strcmp(op,"exp2anyreg")){fscanf(input,"%d",&a);luaK_exp2anyreg(&fs,&e[a]);}
  else if(!strcmp(op,"goiftrue")){fscanf(input,"%d",&a);luaK_goiftrue(&fs,&e[a]);}
  else if(!strcmp(op,"goiffalse")){fscanf(input,"%d",&a);luaK_goiffalse(&fs,&e[a]);}
  else if(!strcmp(op,"indexed")){fscanf(input,"%d%d",&a,&b);luaK_indexed(&fs,&e[a],&e[b]);}
  else if(!strcmp(op,"self")){fscanf(input,"%d%d",&a,&b);luaK_self(&fs,&e[a],&e[b]);}
  else if(!strcmp(op,"storevar")){fscanf(input,"%d%d",&a,&b);luaK_storevar(&fs,&e[a],&e[b]);}
  else if(!strcmp(op,"nil")){fscanf(input,"%d%d",&a,&b);luaK_nil(&fs,a,b);}
  else if(!strcmp(op,"codeABC")){fscanf(input,"%d%d%d%d",&a,&b,&c,&d);luaK_codeABC(&fs,a,b,c,d);}
  else if(!strcmp(op,"codeABCk")){fscanf(input,"%d%d%d%d%d",&a,&b,&c,&d,&x);luaK_codeABCk(&fs,a,b,c,d,x);}
  else if(!strcmp(op,"codeABx")){fscanf(input,"%d%d%d",&a,&b,&c);luaK_codeABx(&fs,a,b,c);}
  else if(!strcmp(op,"codek")){fscanf(input,"%d%d",&a,&b);luaK_codek(&fs,a,b);}
  else if(!strcmp(op,"reserveregs")){fscanf(input,"%d",&a);luaK_reserveregs(&fs,a);}
  else if(!strcmp(op,"setreturns")){fscanf(input,"%d%d",&a,&b);luaK_setreturns(&fs,&e[a],b);}
  else if(!strcmp(op,"setoneret")){fscanf(input,"%d",&a);luaK_setoneret(&fs,&e[a]);}
  else if(!strcmp(op,"setlist")){fscanf(input,"%d%d%d",&a,&b,&c);luaK_setlist(&fs,a,b,c);}
  else if(!strcmp(op,"settablesize")){fscanf(input,"%d%d%d%d",&a,&b,&c,&d);luaK_settablesize(&fs,a,b,c,d);}
  else if(!strcmp(op,"ret")){fscanf(input,"%d%d",&a,&b);luaK_ret(&fs,a,b);}
  else if(!strcmp(op,"fixline")){fscanf(input,"%d",&a);luaK_fixline(&fs,a);}
  else if(!strcmp(op,"remove"))removelastinstruction(&fs);
  else if(!strcmp(op,"label"))luaK_getlabel(&fs);
  else if(!strcmp(op,"jump")){fscanf(input,"%d",&a);e[a].k=VJMP;e[a].u.info=luaK_jump(&fs);e[a].t=e[a].f=NO_JUMP;if(a>=active)active=a+1;}
  else if(!strcmp(op,"concat")){fscanf(input,"%d%d",&a,&b);luaK_concat(&fs,&e[a].u.info,e[b].u.info);}
  else if(!strcmp(op,"patchhere")){fscanf(input,"%d",&a);luaK_patchtohere(&fs,e[a].u.info);}
  else if(!strcmp(op,"cache")){fscanf(input,"%d",&a);luaK_exp2K(&fs,&e[a]);}
  else if(!strcmp(op,"vararg")){fscanf(input,"%d",&a);p->is_vararg=1;p->numparams=a;}
  else if(!strcmp(op,"needclose"))fs.needclose=1;
  else if(!strcmp(op,"finish"))luaK_finish(&fs);
  else abort();
 }
 fclose(input);printf("{\"pc\":%d,\"freereg\":%d,\"maxstacksize\":%d,\"previousline\":%d,\"iwthabs\":%d,\"lasttarget\":%d,\"code\":[",fs.pc,fs.freereg,p->maxstacksize,fs.previousline,fs.iwthabs,fs.lasttarget);
 for(int i=0;i<fs.pc;i++)printf("%s%u",i?",":"",p->code[i]);printf("],\"lineinfo\":[");for(int i=0;i<fs.pc;i++)printf("%s%d",i?",":"",p->lineinfo[i]);
 printf("],\"abslineinfo\":[");for(int i=0;i<fs.nabslineinfo;i++)printf("%s{\"pc\":%d,\"line\":%d}",i?",":"",p->abslineinfo[i].pc,p->abslineinfo[i].line);
 printf("],\"constants\":[");for(int i=0;i<fs.nk;i++){if(i)printf(",");val(&p->k[i]);}printf("],\"expressions\":[");for(int i=0;i<active;i++){if(i)printf(",");expression(&e[i]);}puts("]}");lua_close(L);return 0;
}
`);
execFileSync(resolve(root,'.cache/wasm64-build/host-cc'),['-O2','-I'+source,resolve(work,'oracle.c'),...readdirSync(source).filter(n=>n.endsWith('.c')&&!['lua.c','luac.c','lcode.c'].includes(n)).map(n=>resolve(source,n)),'-lm','-o',oracle]);
const bits=n=>{const d=new DataView(new ArrayBuffer(8));d.setFloat64(0,n);return d.getBigUint64(0).toString(16).padStart(16,'0');};
const value=v=>typeof v==='bigint'?['int',String(v)]:typeof v==='number'?['float',bits(v)]:isLuaString(v)?['str',Buffer.from(luaStringBytes(v),'latin1').toString('hex')]:v===null?['nil']:['bool',v];
const E=(id,k,v=0,b=0)=>['E',id,k,k===K.VKFLT?bits(v):k===K.VKSTR?Buffer.from(v,'latin1').toString('hex')||'-':v,b];
function runJS(commands){const p={linedefined:0,maxstacksize:2},ls={lastline:1,linenumber:1},fs={p,ls,nactvar:0,variableStack:()=>fs.nactvar},cg=new LuaCodeGenerator(fs),expressions=[];
 for(const[op,...a]of commands){
  if(op==='E'){const[id,k,v,b]=a,e=new Exp(k);if(k===K.VKINT)e.u.ival=BigInt(v);else if(k===K.VKFLT){const d=new DataView(new ArrayBuffer(8));d.setBigUint64(0,BigInt('0x'+v));e.u.nval=d.getFloat64(0);}else if(k===K.VKSTR)e.u.strval=v==='-'?'':Buffer.from(v,'hex').toString('latin1');else if(k===K.VLOCAL)e.u.var={ridx:Number(v),vidx:b};else if(k>=K.VINDEXED&&k<=K.VINDEXSTR)e.u.ind={t:Number(v),idx:b};else e.u.info=Number(v);expressions[id]=e;}
  else if(op==='locals')fs.freereg=fs.nactvar=a[0];else if(op==='line')ls.lastline=ls.linenumber=a[0];
  else if(op==='infix')cg.infix(a[0],expressions[a[1]]);else if(op==='posfix')cg.posfix(a[0],expressions[a[1]],expressions[a[2]],a[3]);else if(op==='prefix')cg.prefix(a[0],expressions[a[1]],a[2]);
  else if(['exp2nextreg','exp2anyreg','goiftrue','goiffalse','setoneret','cache'].includes(op))cg[op==='cache'?'exp2K':op](expressions[a[0]]);
  else if(['indexed','self','storevar'].includes(op))cg[op](expressions[a[0]],expressions[a[1]]);
  else if(op==='setreturns')cg.setreturns(expressions[a[0]],a[1]);else if(op==='remove')cg.removelastinstruction();else if(op==='label')cg.getlabel();
  else if(op==='jump')expressions[a[0]]=new Exp(K.VJMP,cg.jump());else if(op==='concat')expressions[a[0]].u.info=cg.concat(expressions[a[0]].u.info,expressions[a[1]].u.info);else if(op==='patchhere')cg.patchtohere(expressions[a[0]].u.info);
  else if(op==='vararg'){p.is_vararg=true;p.numparams=a[0];}else if(op==='needclose')fs.needclose=true;else cg[op](...a);
 }
 const exps=Array.from({length:expressions.length},(_,id)=>{const e=expressions[id]??new Exp(),out={k:e.k,t:e.t,f:e.f};if(e.k===K.VKINT)out.ival=String(e.u.ival);else if(e.k===K.VKFLT)out.nval=bits(e.u.nval);else if(e.k===K.VKSTR)out.strval=Buffer.from(e.u.strval,'latin1').toString('hex');else if(e.k===K.VLOCAL){out.ridx=e.u.var.ridx;out.vidx=e.u.var.vidx;}else if(e.k>=K.VINDEXED&&e.k<=K.VINDEXSTR){out.table=e.u.ind.t;out.index=e.u.ind.idx;}else if(![K.VTRUE,K.VFALSE,K.VNIL].includes(e.k))out.info=e.u.info;return out;});
 return {pc:fs.pc,freereg:fs.freereg,maxstacksize:p.maxstacksize,previousline:fs.previousline,iwthabs:fs.iwthabs,lasttarget:fs.lasttarget,code:p.code,lineinfo:p.lineinfo,abslineinfo:p.abslineinfo,constants:p.constants.map(value),expressions:exps};
}
const cases=[],add=(name,commands)=>cases.push([name,commands]);
const local=id=>E(id,K.VLOCAL,id);
const finish=[['exp2nextreg',0],['ret',2,1],['finish']];
for(let op=0;op<B.OPR_NOBINOPR;op++)for(const[kind,val]of [[K.VKINT,3n],[K.VKFLT,3.0],[K.VKINT,-127n],[K.VKINT,128n],[K.VLOCAL,1]]){
 add(`binary-${op}-${kind}-${val}`,[['locals',2],local(0),['infix',op,0],kind===K.VLOCAL?local(1):E(1,kind,val),['posfix',op,0,1,1],...finish]);
 if(op<=B.OPR_SHR)add(`reversed-${op}-${kind}-${val}`,[['locals',2],kind===K.VLOCAL?local(0):E(0,kind,val),['infix',op,0],local(1),['posfix',op,0,1,1],...finish]);
}
for(let op=0;op<=B.OPR_SHR;op++)for(const[x,y]of [[17n,3n],[-17n,3n],[17n,0n],[1.5,2.0],[0.0,-0.0],[9223372036854775807n,1n],[17n,64n]])add(`fold-${op}-${x}-${y}`,[['locals',2],E(0,typeof x==='bigint'?K.VKINT:K.VKFLT,x),['infix',op,0],E(1,typeof y==='bigint'?K.VKINT:K.VKFLT,y),['posfix',op,0,1,1],...finish]);
for(let op=0;op<U.OPR_NOUNOPR;op++)for(const[kind,val]of [[K.VLOCAL,0],[K.VKINT,17n],[K.VKFLT,0],[K.VKSTR,'a'],[K.VNIL,0],[K.VFALSE,0],[K.VTRUE,0]])add(`unary-${op}-${kind}`,[['locals',2],E(0,kind,val),['prefix',op,0,1],...finish]);
for(const key of [E(1,K.VKINT,17n),E(1,K.VKINT,256n),E(1,K.VKSTR,'field'),E(1,K.VKSTR,'x'.repeat(80)),local(1)])for(const kind of[K.VLOCAL,K.VUPVAL])add(`indexed-${kind}-${key.join('-')}`,[['locals',2],E(0,kind,0),key,['indexed',0,1],...finish]);
for(const op of[B.OPR_EQ,B.OPR_NE,B.OPR_LT,B.OPR_LE,B.OPR_GT,B.OPR_GE])for(const [x,y]of[[3n,300.0],[9007199254740993n,9007199254740992.0],[300.0,3n],[-129.0,-127n]])add(`float-outparam-${op}-${x}-${y}`,[['locals',2],E(0,typeof x==='bigint'?K.VKINT:K.VKFLT,x),['infix',op,0],E(1,typeof y==='bigint'?K.VKINT:K.VKFLT,y),['posfix',op,0,1,1],...finish]);
for(const kind of[K.VLOCAL,K.VUPVAL,K.VINDEXUP,K.VINDEXI,K.VINDEXSTR,K.VINDEXED])add('store-'+kind,[['locals',2],E(2,K.VKSTR,'field'),['cache',2],E(0,kind,0,kind===K.VINDEXED?1:0),E(1,K.VKINT,17n),['storevar',0,1],['ret',0,0],['finish']]);
for(const n of[0,1,3,-1])add('call-results-'+n,[['locals',2],['reserveregs',1],['codeABC',O.CALL,2,1,2],E(0,K.VCALL,0),['setreturns',0,n],['finish']]);
add('call-one',[['locals',2],['reserveregs',1],['codeABC',O.CALL,2,1,2],E(0,K.VCALL,0),['setoneret',0],...finish]);
for(const n of[0,1,3,-1])add('vararg-results-'+n,[['locals',2],['codeABC',O.VARARG,0,0,2],E(0,K.VVARARG,0),['setreturns',0,n],['finish']]);
add('vararg-one',[['locals',2],['codeABC',O.VARARG,0,0,0],E(0,K.VVARARG,0),['setoneret',0],...finish]);
add('constant-load-extraarg',[['codek',0,131071],['codek',1,131072],['codek',2,33554431],['finish']]);
add('rk-limit',[['locals',2],...Array.from({length:257},(_,i)=>[E(0,K.VKSTR,'constant'+i),['cache',0]]).flat(),...finish]);
add('nil-coalescing',[['nil',0,1],['nil',1,3],['nil',0,2],['label'],['nil',2,1],['ret',0,0],['finish']]);
add('concat-merge',[['locals',2],local(0),['infix',B.OPR_CONCAT,0],local(1),['infix',B.OPR_CONCAT,1],E(2,K.VKSTR,'end'),['posfix',B.OPR_CONCAT,1,2,1],['posfix',B.OPR_CONCAT,0,1,1],...finish]);
add('self',[['locals',2],local(0),E(1,K.VKSTR,'method'),['self',0,1],['ret',2,2],['finish']]);
add('jump-list',[['jump',0],['codeABC',O.MOVE,0,0,0],['jump',1],['concat',0,1],['codeABC',O.MOVE,0,0,0],['patchhere',0],['ret',0,0],['finish']]);
add('line-deltas',[...Array.from({length:400},(_,i)=>[['line',i===128?500:i===200?1:2+i],['codeABC',O.MOVE,0,0,0]]).flat(),['fixline',10000],['remove'],['line',4],['codeABC',O.MOVE,0,0,0],['ret',0,0],['finish']]);
add('absolute-line-period',[...Array.from({length:270},()=>['codeABC',O.MOVE,0,0,0]),['fixline',1000],['remove'],['line',1],['codeABC',O.MOVE,0,0,0],['finish']]);
add('tables',[['codeABC',O.NEWTABLE,0,0,0],['codeABC',O.EXTRAARG,0,0,0],['settablesize',0,0,257,7],['locals',1],['setlist',0,256,50],['setlist',0,300,-1],['ret',0,1],['finish']]);
for(const close of[false,true])add('return-adjust-'+close,[['vararg',2],...(close?[['needclose']]:[]),['ret',0,0],['ret',0,1],['ret',0,2],['codeABC',O.TAILCALL,0,1,0],['finish']]);
const cache=[];for(const[k,v]of[[K.VKINT,0n],[K.VKFLT,0],[K.VKFLT,-0],[K.VKINT,3n],[K.VKFLT,3],[K.VKFLT,3+3*2**-52],[K.VKFLT,3],[K.VKSTR,'foo'],[K.VKSTR,'foo'],[K.VNIL,0],[K.VTRUE,0],[K.VFALSE,0]])cache.push(E(0,k,v),['cache',0]);add('constant-cache',cache);
for(const[name,commands]of cases){const input=resolve(work,'commands.txt');writeFileSync(input,commands.map(row=>row.map(String).join(' ')).join('\n')+'\n');const native=JSON.parse(execFileSync(oracle,[input],{encoding:'utf8'})),js=runJS(commands);if(JSON.stringify(native)!==JSON.stringify(js))writeFileSync(resolve(work,'failure.json'),JSON.stringify({name,commands,native,js},(_,v)=>typeof v==='bigint'?String(v):v,2));assert.deepEqual(js,native,name);}
writeFileSync(resolve(work,'summary.json'),JSON.stringify({cases:cases.length,originalSourceSha256:createHash('sha256').update(readFileSync(resolve(source,'lcode.c'))).digest('hex')},null,2)+'\n');
console.log(`PASS: ${cases.length} independent original lcode.c expression/register/jump/line/constant kernels, exact instructions, descriptors, line metadata and register state.`);
