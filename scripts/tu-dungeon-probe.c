/* Controlled DUNGEON dependency fixture, not native Lua or a full game. */
#include "hack.h"
#include "dgn_file.h"
#include "dlb.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <setjmp.h>
#include <errno.h>
__typeof__(svd) svd;
__typeof__(svn) svn;
__typeof__(svs) svs;
__typeof__(svb) svb;
__typeof__(svt) svt;
__typeof__(svl) svl;
__typeof__(svi) svi;
__typeof__(svm) svm;
__typeof__(flags) flags;
char emptystr[1]="";
__typeof__(iflags) iflags;
__typeof__(gu) gu;
__typeof__(WIN_MAP) WIN_MAP;
__typeof__(windowprocs) windowprocs;
__typeof__(u) u;
__typeof__(svu) svu;
__typeof__(cg) cg;
__typeof__(nul_glyphinfo) nul_glyphinfo;
__typeof__(gf) gf;
__typeof__(sve) sve;
__typeof__(svq) svq;
__typeof__(svr) svr;
const char vowels[6]="aeiou";
const struct shclass shtypes[12]={{.name="general store",.annotation="store"},{.name="armor shop",.annotation="armor"},{.name="scroll shop"},{.name="potion shop"}};

static char tracebuf[4194304],text[4096]="fixture",input[256]="fixture annotation",roomstr[16];static size_t traceused;static int options[128],errorcode,draws,callerline;static uint32_t seed=1;static const char*callerfile,*callerfn;static jmp_buf panicframe;
static unsigned char scratch[65536],serial[262144],luaworld[16];static size_t serialused,serialpos;static int nevents,eventtype[4096];static size_t eventat[4096],eventsize[4096];static void*allocations[4096];static size_t allocsizes[4096];static int nalloc,alloclive[4096];static d_level levels[8];static struct monst monsters[8];static struct permonst species[8];static stairway stairs[8];static struct cemetery graves[8];static NHFILE nhfile;
static int luatop,luatypes[128],luaval[128],luakind[128],luaiter,luaindex,luadgn;static const char*luastr[128];
static void logfmt(const char*fmt,...){va_list ap;va_start(ap,fmt);int n=vsnprintf(tracebuf+traceused,sizeof tracebuf-traceused,fmt,ap);va_end(ap);if(n<0||(size_t)n>=sizeof tracebuf-traceused)abort();traceused+=n;}
static void ptrlog(const void*p){if(!p){logfmt("0");return;}

if((uintptr_t)p>=(uintptr_t)(&svd)&&(uintptr_t)p<(uintptr_t)(&svd)+(sizeof svd)){logfmt("svd+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&svd)));return;}
if((uintptr_t)p>=(uintptr_t)(&svn)&&(uintptr_t)p<(uintptr_t)(&svn)+(sizeof svn)){logfmt("svn+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&svn)));return;}
if((uintptr_t)p>=(uintptr_t)(&svs)&&(uintptr_t)p<(uintptr_t)(&svs)+(sizeof svs)){logfmt("svs+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&svs)));return;}
if((uintptr_t)p>=(uintptr_t)(&svb)&&(uintptr_t)p<(uintptr_t)(&svb)+(sizeof svb)){logfmt("svb+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&svb)));return;}
if((uintptr_t)p>=(uintptr_t)(&svt)&&(uintptr_t)p<(uintptr_t)(&svt)+(sizeof svt)){logfmt("svt+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&svt)));return;}
if((uintptr_t)p>=(uintptr_t)(&svl)&&(uintptr_t)p<(uintptr_t)(&svl)+(sizeof svl)){logfmt("svl+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&svl)));return;}
if((uintptr_t)p>=(uintptr_t)(&svi)&&(uintptr_t)p<(uintptr_t)(&svi)+(sizeof svi)){logfmt("svi+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&svi)));return;}
if((uintptr_t)p>=(uintptr_t)(&svm)&&(uintptr_t)p<(uintptr_t)(&svm)+(sizeof svm)){logfmt("svm+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&svm)));return;}
if((uintptr_t)p>=(uintptr_t)(&flags)&&(uintptr_t)p<(uintptr_t)(&flags)+(sizeof flags)){logfmt("flags+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&flags)));return;}
if((uintptr_t)p>=(uintptr_t)(&emptystr)&&(uintptr_t)p<(uintptr_t)(&emptystr)+(sizeof emptystr)){logfmt("emptystr+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&emptystr)));return;}
if((uintptr_t)p>=(uintptr_t)(&iflags)&&(uintptr_t)p<(uintptr_t)(&iflags)+(sizeof iflags)){logfmt("iflags+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&iflags)));return;}
if((uintptr_t)p>=(uintptr_t)(&gu)&&(uintptr_t)p<(uintptr_t)(&gu)+(sizeof gu)){logfmt("gu+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&gu)));return;}
if((uintptr_t)p>=(uintptr_t)(&WIN_MAP)&&(uintptr_t)p<(uintptr_t)(&WIN_MAP)+(sizeof WIN_MAP)){logfmt("WIN_MAP+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&WIN_MAP)));return;}
if((uintptr_t)p>=(uintptr_t)(&windowprocs)&&(uintptr_t)p<(uintptr_t)(&windowprocs)+(sizeof windowprocs)){logfmt("windowprocs+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&windowprocs)));return;}
if((uintptr_t)p>=(uintptr_t)(&u)&&(uintptr_t)p<(uintptr_t)(&u)+(sizeof u)){logfmt("u+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&u)));return;}
if((uintptr_t)p>=(uintptr_t)(&svu)&&(uintptr_t)p<(uintptr_t)(&svu)+(sizeof svu)){logfmt("svu+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&svu)));return;}
if((uintptr_t)p>=(uintptr_t)(&cg)&&(uintptr_t)p<(uintptr_t)(&cg)+(sizeof cg)){logfmt("cg+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&cg)));return;}
if((uintptr_t)p>=(uintptr_t)(&nul_glyphinfo)&&(uintptr_t)p<(uintptr_t)(&nul_glyphinfo)+(sizeof nul_glyphinfo)){logfmt("nul_glyphinfo+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&nul_glyphinfo)));return;}
if((uintptr_t)p>=(uintptr_t)(&gf)&&(uintptr_t)p<(uintptr_t)(&gf)+(sizeof gf)){logfmt("gf+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&gf)));return;}
if((uintptr_t)p>=(uintptr_t)(&sve)&&(uintptr_t)p<(uintptr_t)(&sve)+(sizeof sve)){logfmt("sve+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&sve)));return;}
if((uintptr_t)p>=(uintptr_t)(&svq)&&(uintptr_t)p<(uintptr_t)(&svq)+(sizeof svq)){logfmt("svq+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&svq)));return;}
if((uintptr_t)p>=(uintptr_t)(&svr)&&(uintptr_t)p<(uintptr_t)(&svr)+(sizeof svr)){logfmt("svr+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&svr)));return;}
if((uintptr_t)p>=(uintptr_t)(&vowels)&&(uintptr_t)p<(uintptr_t)(&vowels)+(sizeof vowels)){logfmt("vowels+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&vowels)));return;}
if((uintptr_t)p>=(uintptr_t)(&shtypes)&&(uintptr_t)p<(uintptr_t)(&shtypes)+(sizeof shtypes)){logfmt("shtypes+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&shtypes)));return;}
if((uintptr_t)p>=(uintptr_t)(scratch)&&(uintptr_t)p<(uintptr_t)(scratch)+(sizeof scratch)){logfmt("scratch+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(scratch)));return;}
if((uintptr_t)p>=(uintptr_t)(text)&&(uintptr_t)p<(uintptr_t)(text)+(sizeof text)){logfmt("text+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(text)));return;}
if((uintptr_t)p>=(uintptr_t)(input)&&(uintptr_t)p<(uintptr_t)(input)+(sizeof input)){logfmt("input+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(input)));return;}
if((uintptr_t)p>=(uintptr_t)(roomstr)&&(uintptr_t)p<(uintptr_t)(roomstr)+(sizeof roomstr)){logfmt("roomstr+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(roomstr)));return;}
if((uintptr_t)p>=(uintptr_t)(serial)&&(uintptr_t)p<(uintptr_t)(serial)+(sizeof serial)){logfmt("serial+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(serial)));return;}
if((uintptr_t)p>=(uintptr_t)(luaworld)&&(uintptr_t)p<(uintptr_t)(luaworld)+(sizeof luaworld)){logfmt("luaworld+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(luaworld)));return;}
if((uintptr_t)p>=(uintptr_t)(levels)&&(uintptr_t)p<(uintptr_t)(levels)+(sizeof levels)){logfmt("levels+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(levels)));return;}
if((uintptr_t)p>=(uintptr_t)(monsters)&&(uintptr_t)p<(uintptr_t)(monsters)+(sizeof monsters)){logfmt("monsters+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(monsters)));return;}
if((uintptr_t)p>=(uintptr_t)(species)&&(uintptr_t)p<(uintptr_t)(species)+(sizeof species)){logfmt("species+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(species)));return;}
if((uintptr_t)p>=(uintptr_t)(stairs)&&(uintptr_t)p<(uintptr_t)(stairs)+(sizeof stairs)){logfmt("stairs+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(stairs)));return;}
if((uintptr_t)p>=(uintptr_t)(graves)&&(uintptr_t)p<(uintptr_t)(graves)+(sizeof graves)){logfmt("graves+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(graves)));return;}
if((uintptr_t)p>=(uintptr_t)(&nhfile)&&(uintptr_t)p<(uintptr_t)(&nhfile)+(sizeof nhfile)){logfmt("nhfile+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&nhfile)));return;}

for(int i=0;i<nalloc;i++)if(alloclive[i]&&(uintptr_t)p>=(uintptr_t)allocations[i]&&(uintptr_t)p<(uintptr_t)allocations[i]+allocsizes[i]){logfmt("A%d+%llu",i,(unsigned long long)((uintptr_t)p-(uintptr_t)allocations[i]));return;}logfmt("UNKNOWN:%llu",(unsigned long long)(uintptr_t)p);}
void*__real_malloc(size_t);void __real_free(void*);
void*__wrap_malloc(size_t n){if(nalloc==4096)abort();void*p=__real_malloc(n);if(p)memset(p,0,n);allocations[nalloc]=p;allocsizes[nalloc]=n;alloclive[nalloc++]=1;return p;}
void __wrap_free(void*p){logfmt("free(");ptrlog(p);logfmt(")\n");for(int i=0;i<nalloc;i++)if(alloclive[i]&&allocations[i]==p){alloclive[i]=0;break;}__real_free(p);}
static void*newallocation(size_t n){return __wrap_malloc(n);}static char*copystr(const char*s){if(!s)return 0;size_t n=strlen(s)+1;char*p=newallocation(n);memcpy(p,s,n);return p;}
static int roll(const char*n,int bound){if(bound<=0){logfmt("BADRNG %d\n",bound);longjmp(panicframe,2);}seed=seed*1664525U+1013904223U;int v=seed%(unsigned)bound;draws++;logfmt("%s[%s:%d:%s](%d)=%d\n",n,callerfile?callerfile:"",callerline,callerfn?callerfn:"",bound,v);return v;}
static int lslot(int i){return i<0?luatop+i:i-1;}static void lpush(int type,int val,int kind,const char*str){if(luatop==128)abort();luatypes[luatop]=type;luaval[luatop]=val;luakind[luatop]=kind;luastr[luatop++]=str;}
static void win_clear(winid w){logfmt("window.clear(%d)\n",w);}static void win_clip(int x,int y){logfmt("window.clip(%d,%d)\n",x,y);}static void win_put(winid w,int a,const char*s){logfmt("window.put(%d,%d,%s)\n",w,a,s?s:"NULL");}static winid win_create(int k){logfmt("window.create(%d)\n",k);return 7;}static void win_start(winid w,unsigned long f){logfmt("window.start(%d,%llu)\n",w,(unsigned long long)f);}static void win_end(winid w,const char*s){logfmt("window.end(%d,%s)\n",w,s?s:"NULL");}static void win_destroy(winid w){logfmt("window.destroy(%d)\n",w);}static void win_display(winid w,boolean b){logfmt("window.display(%d,%d)\n",w,b);}
static void io_bytes(void*p,size_t n,int read){if(read){if(serialpos+n>serialused){logfmt("SERIAL_EOF\n");longjmp(panicframe,6);}memcpy(p,serial+serialpos,n);serialpos+=n;}else{if(serialused+n>sizeof serial)abort();memcpy(serial+serialused,p,n);serialused+=n;}}

static void io_event(void*p,size_t n,int type){if(nevents==4096)abort();eventtype[nevents]=type;eventat[nevents]=serialused;eventsize[nevents++]=n;io_bytes(p,n,0);}
boolean (debugcore)(const char * a0,boolean a1){logfmt("debugcore(");logfmt("%s",a0?a0:"NULL");logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return options[0];}
int (getchar)(void){logfmt("getchar(");logfmt(")\n");return 0;}
void (sfo_int)(NHFILE * a0,int * a1,const char * a2){logfmt("sfo_int(");ptrlog(a0);logfmt(",");logfmt("IN:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_event(a1,sizeof(*a1)*(1),1);}
void (sfo_dungeon)(NHFILE * a0,struct dungeon * a1,const char * a2){logfmt("sfo_dungeon(");ptrlog(a0);logfmt(",");logfmt("IN:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_event(a1,sizeof(*a1)*(1),7);}
void (sfo_dgn_topology)(NHFILE * a0,struct dgn_topology * a1,const char * a2){logfmt("sfo_dgn_topology(");ptrlog(a0);logfmt(",");logfmt("IN:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_event(a1,sizeof(*a1)*(1),6);}
void (sfo_char)(NHFILE * a0,char * a1,const char * a2,int a3){logfmt("sfo_char(");ptrlog(a0);logfmt(",");logfmt("IN:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(",");logfmt("%lld",(long long)a3);logfmt(")\n");io_event(a1,sizeof(*a1)*(a3),0);}
void (sfo_branch)(NHFILE * a0,struct branch * a1,const char * a2){logfmt("sfo_branch(");ptrlog(a0);logfmt(",");logfmt("IN:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_event(a1,sizeof(*a1)*(1),3);}
void (sfo_linfo)(NHFILE * a0,struct linfo * a1,const char * a2){logfmt("sfo_linfo(");ptrlog(a0);logfmt(",");logfmt("IN:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_event(a1,sizeof(*a1)*(1),8);}
void (sfo_nhcoord)(NHFILE * a0,struct nhcoord * a1,const char * a2){logfmt("sfo_nhcoord(");ptrlog(a0);logfmt(",");logfmt("IN:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_event(a1,sizeof(*a1)*(1),12);}
void (savecemetery)(NHFILE * a0,struct cemetery ** a1){logfmt("savecemetery(");ptrlog(a0);logfmt(",");logfmt("cemetery-chain");logfmt(")\n");int n=0;for(struct cemetery*p=*a1;p;p=p->next)n++;io_bytes(&n,sizeof n,0);for(struct cemetery*p=*a1;p;p=p->next)io_event(p,sizeof*p,4);}
void (sfi_int)(NHFILE * a0,int * a1,const char * a2){logfmt("sfi_int(");ptrlog(a0);logfmt(",");logfmt("OUT:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_bytes(a1,sizeof(*a1)*(1),1);}
void (sfi_dungeon)(NHFILE * a0,struct dungeon * a1,const char * a2){logfmt("sfi_dungeon(");ptrlog(a0);logfmt(",");logfmt("OUT:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_bytes(a1,sizeof(*a1)*(1),1);}
void (sfi_dgn_topology)(NHFILE * a0,struct dgn_topology * a1,const char * a2){logfmt("sfi_dgn_topology(");ptrlog(a0);logfmt(",");logfmt("OUT:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_bytes(a1,sizeof(*a1)*(1),1);}
void (sfi_char)(NHFILE * a0,char * a1,const char * a2,int a3){logfmt("sfi_char(");ptrlog(a0);logfmt(",");logfmt("OUT:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(",");logfmt("%lld",(long long)a3);logfmt(")\n");io_bytes(a1,sizeof(*a1)*(a3),1);}
long * (alloc)(unsigned int a0){logfmt("alloc(");logfmt("%lld",(long long)a0);logfmt(")\n");return(long*)newallocation(a0);}
void (sfi_branch)(NHFILE * a0,struct branch * a1,const char * a2){logfmt("sfi_branch(");ptrlog(a0);logfmt(",");logfmt("OUT:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_bytes(a1,sizeof(*a1)*(1),1);}
void (sfi_linfo)(NHFILE * a0,struct linfo * a1,const char * a2){logfmt("sfi_linfo(");ptrlog(a0);logfmt(",");logfmt("OUT:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_bytes(a1,sizeof(*a1)*(1),1);}
void (sfi_nhcoord)(NHFILE * a0,struct nhcoord * a1,const char * a2){logfmt("sfi_nhcoord(");ptrlog(a0);logfmt(",");logfmt("OUT:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_bytes(a1,sizeof(*a1)*(1),1);}
int (strncmpi)(const char * a0,const char * a1,int a2){logfmt("strncmpi(");logfmt("%s",a0?a0:"NULL");logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(",");logfmt("%lld",(long long)a2);logfmt(")\n");for(int i=0;i<a2;i++){int x=tolower((unsigned char)a0[i]),y=tolower((unsigned char)a1[i]);if(x!=y||!x||!y)return x-y;}return 0;}
boolean (rng_log_enabled)(void){return TRUE;}
void (rng_log_set_caller)(const char * a0,int a1,const char * a2){callerfile=a0;callerline=a1;callerfn=a2;}
int (rn2)(int a0){return roll("rn2",a0);}
int (lua_getfield)(lua_State * a0,int a1,const char * a2){logfmt("lua_getfield(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");int k=!strcmp(a2,"levels")?3:!strcmp(a2,"branches")?4:!strcmp(a2,"flags")?5:0;if(k==5){if(options[28])lpush(LUA_TSTRING,0,0,"unconnected");else if(options[5]==1)lpush(LUA_TSTRING,0,0,"hellish");else if(options[5]==2)lpush(LUA_TTABLE,0,5,0);else lpush(LUA_TNIL,0,0,0);}else if(k==3||k==4)lpush(LUA_TTABLE,0,k,0);else lpush(LUA_TNIL,0,0,0);return luatypes[luatop-1];}
int (lua_type)(lua_State * a0,int a1){logfmt("lua_type(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");int i=lslot(a1);return i>=0&&i<luatop?luatypes[i]:LUA_TNONE;}
void (lua_len)(lua_State * a0,int a1){logfmt("lua_len(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");int k=luakind[lslot(a1)];lpush(LUA_TNUMBER,k==3?(options[3]?options[3]:2):k==4?options[4]:k==5?2:k==1?6:1,0,0);}
lua_Integer (lua_tointegerx)(lua_State * a0,int a1,int * a2){logfmt("lua_tointegerx(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");ptrlog(a2);logfmt(")\n");if(a2)*a2=1;return luaval[lslot(a1)];}
void (lua_settop)(lua_State * a0,int a1){logfmt("lua_settop(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");luatop=a1<0?luatop+a1+1:a1;if(luatop<0||luatop>128)abort();}
void (lua_pushinteger)(lua_State * a0,lua_Integer a1){logfmt("lua_pushinteger(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");lpush(LUA_TNUMBER,(int)a1,0,0);}
int (lua_gettable)(lua_State * a0,int a1){logfmt("lua_gettable(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");int index=luaval[luatop-1],k=luakind[lslot(a1)];luatop--;luaindex=index;if(k==5)lpush(LUA_TSTRING,0,0,index==1?"town":"mazelike");else lpush(options[6]?LUA_TSTRING:LUA_TTABLE,index,k==3?6:7,0);return luatypes[luatop-1];}
int (luaL_checkoption)(lua_State * a0,int a1,const char * a2,const char *const * a3){logfmt("luaL_checkoption(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(",");logfmt("STR-TABLE");logfmt(")\n");const char*value=luastr[lslot(a1)];if(!value)value=a2;for(int i=0;a3[i];i++)if(value&&!strcmp(a3[i],value))return i;return 0;}
int (get_table_option)(lua_State * a0,const char * a1,const char * a2,const char *const * a3){logfmt("get_table_option(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(",");logfmt("STR-TABLE");logfmt(")\n");const char*value=!strcmp(a1,"alignment")?(options[7]==1?"lawful":options[7]==2?"chaotic":"unaligned"):!strcmp(a1,"direction")?(options[8]?"up":"down"):!strcmp(a1,"branchtype")?(options[9]?"portal":"stair"):a2;for(int i=0;a3[i];i++)if(value&&!strcmp(a3[i],value))return i;return 0;}
char * (get_table_str)(lua_State * a0,const char * a1){logfmt("get_table_str(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(")\n");int k=luatop?luakind[luatop-1]:2;const char*name=k==6?(luaindex==1?"oracle":"castle"):k==7?"The Gnomish Mines":(const char*[]){"Dungeons of Doom","The Quest","Sokoban","The Gnomish Mines","Vlad's Tower","The Tutorial"}[luadgn];return copystr(name);}
char * (get_table_str_opt)(lua_State * a0,const char * a1,char * a2){logfmt("get_table_str_opt(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");const char*v=a2;if(!strcmp(a1,"bonetag"))v="D";else if(!strcmp(a1,"chainlevel"))v=options[10]?"oracle":0;else if(!strcmp(a1,"protofile"))v="fixture";return copystr(v);}
int (get_table_int)(lua_State * a0,const char * a1){logfmt("get_table_int(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(")\n");int k=luatop?luakind[luatop-1]:2;return k==6?2+luaindex*3:12;}
int (get_table_int_opt)(lua_State * a0,const char * a1,int a2){logfmt("get_table_int_opt(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(",");logfmt("%lld",(long long)a2);logfmt(")\n");if(!strcmp(a1,"range"))return options[11];if(!strcmp(a1,"chance"))return options[12]?options[12]:a2;if(!strcmp(a1,"entry"))return options[13];if(!strcmp(a1,"nlevels"))return options[14];return a2;}
lua_State * (nhl_init)(nhl_sandbox_info * a0){logfmt("nhl_init(");logfmt("sandbox:%u,%u,%u,%u",a0->flags,a0->memlimit,a0->steps,a0->perpcall);logfmt(")\n");luatop=luaiter=0;return options[1]?0:(lua_State*)luaworld;}
boolean (nhl_loadlua)(lua_State * a0,const char * a1){logfmt("nhl_loadlua(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(")\n");return !options[2];}
int (lua_getglobal)(lua_State * a0,const char * a1){logfmt("lua_getglobal(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(")\n");lpush(LUA_TTABLE,0,1,0);return LUA_TTABLE;}
int (lua_gettop)(lua_State * a0){logfmt("lua_gettop(");ptrlog(a0);logfmt(")\n");return luatop;}
void (lua_pushnil)(lua_State * a0){logfmt("lua_pushnil(");ptrlog(a0);logfmt(")\n");lpush(LUA_TNIL,0,0,0);}
int (lua_next)(lua_State * a0,int a1){logfmt("lua_next(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");luatop--;if(luaiter<6){luadgn=luaiter++;lpush(LUA_TNUMBER,luadgn+1,0,0);lpush(LUA_TTABLE,0,2,0);return 1;}return 0;}
void (nhl_done)(lua_State * a0){logfmt("nhl_done(");ptrlog(a0);logfmt(")\n");luatop=0;}
stairway * (stairway_at)(coordxy a0,coordxy a1){logfmt("stairway_at(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return options[15]?&stairs[0]:0;}
void (goto_level)(d_level * a0,boolean a1,boolean a2,boolean a3){logfmt("goto_level(");logfmt("level:%d,%d",a0->dnum,a0->dlevel);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(",");logfmt("%lld",(long long)a3);logfmt(")\n");logfmt("target:%d,%d\n",a0->dnum,a0->dlevel);u.uz=*a0;}
void (done)(int a0){logfmt("done(");logfmt("%lld",(long long)a0);logfmt(")\n");longjmp(panicframe,4);}
const char * (body_part)(int a0){logfmt("body_part(");logfmt("%lld",(long long)a0);logfmt(")\n");return "head";}
char * (makeplural)(const char * a0){logfmt("makeplural(");logfmt("%s",a0?a0:"NULL");logfmt(")\n");snprintf(text,sizeof text,"%ss",a0);return text;}
int (isok)(coordxy a0,coordxy a1){logfmt("isok(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return a0>=1&&a0<COLNO&&a1>=0&&a1<ROWNO;}
void (map_location)(coordxy a0,coordxy a1,int a2){logfmt("map_location(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(")\n");}
void (see_nearby_objects)(void){logfmt("see_nearby_objects(");logfmt(")\n");}
void (place_lregion)(coordxy a0,coordxy a1,coordxy a2,coordxy a3,coordxy a4,coordxy a5,coordxy a6,coordxy a7,xint16 a8,d_level * a9){logfmt("place_lregion(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(",");logfmt("%lld",(long long)a3);logfmt(",");logfmt("%lld",(long long)a4);logfmt(",");logfmt("%lld",(long long)a5);logfmt(",");logfmt("%lld",(long long)a6);logfmt(",");logfmt("%lld",(long long)a7);logfmt(",");logfmt("%lld",(long long)a8);logfmt(",");ptrlog(a9);logfmt(")\n");if(options[16]){u.ux=41;u.uy=10;}}
void (switch_terrain)(void){logfmt("switch_terrain(");logfmt(")\n");}
stairway * (stairway_find_special_dir)(boolean a0){logfmt("stairway_find_special_dir(");logfmt("%lld",(long long)a0);logfmt(")\n");return options[15]?&stairs[0]:0;}
char * (in_rooms)(coordxy a0,coordxy a1,int a2){logfmt("in_rooms(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(")\n");roomstr[0]=options[17]?ROOMOFFSET:0;roomstr[1]=0;return roomstr;}
schar (db_under_typ)(int a0){logfmt("db_under_typ(");logfmt("%lld",(long long)a0);logfmt(")\n");return ROOM;}
struct attack * (dmgtype_fromattack)(struct permonst * a0,int a1,int a2){logfmt("dmgtype_fromattack(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(")\n");return options[18]?&species[0].mattk[0]:0;}
boolean (is_pool)(coordxy a0,coordxy a1){logfmt("is_pool(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return levl[a0][a1].typ==POOL||levl[a0][a1].typ==MOAT;}
const char * (hliquid)(const char * a0){logfmt("hliquid(");logfmt("%s",a0?a0:"NULL");logfmt(")\n");return "water";}
boolean (is_ice)(coordxy a0,coordxy a1){logfmt("is_ice(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return levl[a0][a1].typ==ICE;}
boolean (is_lava)(coordxy a0,coordxy a1){logfmt("is_lava(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return levl[a0][a1].typ==LAVAPOOL;}
boolean (On_stairs)(coordxy a0,coordxy a1){logfmt("On_stairs(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return options[15];}
int (rnd)(int a0){return roll("rnd",a0)+1;}
char * (strstri)(const char * a0,const char * a1){logfmt("strstri(");logfmt("%s",a0?a0:"NULL");logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(")\n");for(const char*p=a0;*p;p++)if(!strncasecmp(p,a1,strlen(a1)))return(char*)p;return 0;}
char * (eos)(char * a0){logfmt("eos(");logfmt("%s",a0?a0:"NULL");logfmt(")\n");return a0+strlen(a0);}
void (add_menu)(winid a0,const glyph_info * a1,const union any * a2,char a3,char a4,int a5,int a6,const char * a7,unsigned int a8){logfmt("add_menu(");logfmt("%lld",(long long)a0);logfmt(",");ptrlog(a1);logfmt(",");logfmt("scalar-menu-id:%d,raw8:",a2->a_int);for(int i=0;i<8;i++)logfmt("%02x",((const unsigned char*)a2)[i]);logfmt(",");logfmt("%lld",(long long)a3);logfmt(",");logfmt("%lld",(long long)a4);logfmt(",");logfmt("%lld",(long long)a5);logfmt(",");logfmt("%lld",(long long)a6);logfmt(",");logfmt("%s",a7?a7:"NULL");logfmt(",");logfmt("%lld",(long long)a8);logfmt(")\n");}
void (add_menu_heading)(winid a0,const char * a1){logfmt("add_menu_heading(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(")\n");}
int (select_menu)(winid a0,int a1,menu_item ** a2){logfmt("select_menu(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("OUT:menu_item**");logfmt(")\n");*a2=0;if(!options[27])return 0;menu_item*p=newallocation(sizeof*p);p->item.a_int=options[27];p->count=1;*a2=p;return 1;}
void (getlin)(const char * a0,char * a1){logfmt("getlin(");logfmt("%s",a0?a0:"NULL");logfmt(",");logfmt("OUT:char256");logfmt(")\n");strcpy(a1,input);}
int (describe_level)(char * a0,int a1){logfmt("describe_level(");logfmt("OUT:char256");logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");sprintf(a0,"Dlvl:%-2d",u.uz.dlevel);return TRUE;}
char * (strsubst)(char * a0,const char * a1,const char * a2){logfmt("strsubst(");logfmt("%s",a0?a0:"NULL");logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");char*p=strstr(a0,a1);if(!p)return a0;size_t x=strlen(a1),y=strlen(a2);memmove(p+y,p+x,strlen(p+x)+1);memcpy(p,a2,y);return a0;}
char * (trimspaces)(char * a0){logfmt("trimspaces(");logfmt("%s",a0?a0:"NULL");logfmt(")\n");while(*a0&&isspace((unsigned char)*a0))memmove(a0,a0+1,strlen(a0));size_t n=strlen(a0);while(n&&isspace((unsigned char)a0[n-1]))a0[--n]=0;return a0;}
char * (mungspaces)(char * a0){logfmt("mungspaces(");logfmt("%s",a0?a0:"NULL");logfmt(")\n");char*p=a0,*out=a0;int space=0;while(*p){if(isspace((unsigned char)*p)){if(out!=a0)space=1;}else{if(space)*out++=' ';*out++=*p;space=0;}p++;}*out=0;return a0;}
char * (dupstr)(const char * a0){logfmt("dupstr(");logfmt("%s",a0?a0:"NULL");logfmt(")\n");return copystr(a0);}
void (sfo_xint16)(NHFILE * a0,xint16 * a1,const char * a2){logfmt("sfo_xint16(");ptrlog(a0);logfmt(",");logfmt("IN:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_event(a1,sizeof(*a1)*(1),2);}
void (sfo_int16)(NHFILE * a0,int16 * a1,const char * a2){logfmt("sfo_int16(");ptrlog(a0);logfmt(",");logfmt("IN:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_event(a1,sizeof(*a1)*(1),2);}
void (sfi_xint16)(NHFILE * a0,xint16 * a1,const char * a2){logfmt("sfi_xint16(");ptrlog(a0);logfmt(",");logfmt("OUT:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_bytes(a1,sizeof(*a1)*(1),1);}
void (sfi_int16)(NHFILE * a0,int16 * a1,const char * a2){logfmt("sfi_int16(");ptrlog(a0);logfmt(",");logfmt("OUT:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_bytes(a1,sizeof(*a1)*(1),1);}
void (sfo_d_level)(NHFILE * a0,struct d_level * a1,const char * a2){logfmt("sfo_d_level(");ptrlog(a0);logfmt(",");logfmt("IN:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_event(a1,sizeof(*a1)*(1),5);}
void (sfo_mapseen_feat)(NHFILE * a0,struct mapseen_feat * a1,const char * a2){logfmt("sfo_mapseen_feat(");ptrlog(a0);logfmt(",");logfmt("IN:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_event(a1,sizeof(*a1)*(1),9);}
void (sfo_mapseen_flags)(NHFILE * a0,struct mapseen_flags * a1,const char * a2){logfmt("sfo_mapseen_flags(");ptrlog(a0);logfmt(",");logfmt("IN:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_event(a1,sizeof(*a1)*(1),10);}
void (sfo_unsigned)(NHFILE * a0,unsigned int * a1,const char * a2){logfmt("sfo_unsigned(");ptrlog(a0);logfmt(",");logfmt("IN:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_event(a1,sizeof(*a1)*(1),13);}
void (sfo_mapseen_rooms)(NHFILE * a0,struct mapseen_rooms * a1,const char * a2){logfmt("sfo_mapseen_rooms(");ptrlog(a0);logfmt(",");logfmt("IN:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_event(a1,sizeof(*a1)*(1),11);}
void (sfi_d_level)(NHFILE * a0,struct d_level * a1,const char * a2){logfmt("sfi_d_level(");ptrlog(a0);logfmt(",");logfmt("OUT:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_bytes(a1,sizeof(*a1)*(1),1);}
void (sfi_mapseen_feat)(NHFILE * a0,struct mapseen_feat * a1,const char * a2){logfmt("sfi_mapseen_feat(");ptrlog(a0);logfmt(",");logfmt("OUT:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_bytes(a1,sizeof(*a1)*(1),1);}
void (sfi_mapseen_flags)(NHFILE * a0,struct mapseen_flags * a1,const char * a2){logfmt("sfi_mapseen_flags(");ptrlog(a0);logfmt(",");logfmt("OUT:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_bytes(a1,sizeof(*a1)*(1),1);}
void (sfi_unsigned)(NHFILE * a0,unsigned int * a1,const char * a2){logfmt("sfi_unsigned(");ptrlog(a0);logfmt(",");logfmt("OUT:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_bytes(a1,sizeof(*a1)*(1),1);}
void (sfi_mapseen_rooms)(NHFILE * a0,struct mapseen_rooms * a1,const char * a2){logfmt("sfi_mapseen_rooms(");ptrlog(a0);logfmt(",");logfmt("OUT:typed-record");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(")\n");io_bytes(a1,sizeof(*a1)*(1),1);}
void (restcemetery)(NHFILE * a0,struct cemetery ** a1){logfmt("restcemetery(");ptrlog(a0);logfmt(",");logfmt("OUT:cemetery**");logfmt(")\n");int n;io_bytes(&n,sizeof n,1);struct cemetery**out=a1;for(int i=0;i<n;i++){*out=newallocation(sizeof**out);io_bytes(*out,sizeof**out,1);out=&(*out)->next;}*out=0;}
int (canseemon)(struct monst * a0){logfmt("canseemon(");ptrlog(a0);logfmt(")\n");return options[19];}
int (cmap_to_type)(int a0){logfmt("cmap_to_type(");logfmt("%lld",(long long)a0);logfmt(")\n");return options[20]?options[20]:a0;}
int (altarmask_at)(coordxy a0,coordxy a1){logfmt("altarmask_at(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return options[21];}
int (is_drawbridge_wall)(coordxy a0,coordxy a1){logfmt("is_drawbridge_wall(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return options[22];}
struct monst * (shop_keeper)(char a0){logfmt("shop_keeper(");logfmt("%lld",(long long)a0);logfmt(")\n");return options[23]?&monsters[0]:0;}
int (inhishop)(struct monst * a0){logfmt("inhishop(");ptrlog(a0);logfmt(")\n");return options[24];}
struct monst * (findpriest)(char a0){logfmt("findpriest(");logfmt("%lld",(long long)a0);logfmt(")\n");return options[25]?&monsters[1]:0;}
boolean (inhistemple)(struct monst * a0){logfmt("inhistemple(");ptrlog(a0);logfmt(")\n");return options[26];}
char * (an)(const char * a0){logfmt("an(");logfmt("%s",a0?a0:"NULL");logfmt(")\n");snprintf(text,sizeof text,"a %s",a0);return text;}
const char * (align_gname)(aligntyp a0){logfmt("align_gname(");logfmt("%lld",(long long)a0);logfmt(")\n");return "fixture god";}
char (highc)(char a0){logfmt("highc(");logfmt("%lld",(long long)a0);logfmt(")\n");return toupper((unsigned char)a0);}
void (add_menu_str)(winid a0,const char * a1){logfmt("add_menu_str(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(")\n");}
const char * (ldrname)(void){logfmt("ldrname(");logfmt(")\n");return "fixture leader";}
void (formatkiller)(char * a0,unsigned int a1,int a2,boolean a3){logfmt("formatkiller(");logfmt("OUT:char");logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(",");logfmt("%lld",(long long)a3);logfmt(")\n");snprintf(a0,a1,"fixture death");}
void You(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[4096];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("You:%s\n",b);}
void impossible(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[4096];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("impossible:%s\n",b);}
void panic(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[4096];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("panic:%s\n",b);longjmp(panicframe,1);}
void pline(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[4096];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("pline:%s\n",b);}
void nh_snprintf(const char*f,int line,char*b,size_t n,const char*fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(b,n,fmt,ap);va_end(ap);logfmt("nh_snprintf[%s:%d]:%s\n",f,line,b);}
#ifdef HYBRID_DUNGEON
struct proto_dungeon {
    struct tmpdungeon tmpdungeon[MAXDUNGEON];
    struct tmplevel tmplevel[LEV_LIMIT];
    s_level *final_lev[LEV_LIMIT]; /* corresponding level pointers */
    struct tmpbranch tmpbranch[BRANCH_LIMIT];

    int start;  /* starting index of current dungeon sp levels */
    int n_levs; /* number of tmplevel entries */
    int n_brs;  /* number of tmpbranch entries */
};
struct lchoice {
    int idx;
    schar lev[MAXLINFO];
    schar playerlev[MAXLINFO];
    xint16 dgn[MAXLINFO];
    char menuletter;
};
struct level_map {
    const char *lev_name;
    d_level *lev_spec;
};
extern void teleport_dungeon_dumpit(void);
extern void save_dungeon(NHFILE * a0,boolean a1,boolean a2);
extern void restore_dungeon(NHFILE * a0);
extern xint16 teleport_dungeon_dname_to_dnum(const char * a0);
extern s_level * find_level(const char * a0);
extern int teleport_dungeon_find_branch(const char * a0,struct proto_dungeon * a1);
extern xint16 teleport_dungeon_parent_dnum(const char * a0,struct proto_dungeon * a1);
extern int teleport_dungeon_level_range(xint16 a0,int a1,int a2,int a3,struct proto_dungeon * a4,int * a5);
extern xint16 teleport_dungeon_parent_dlevel(const char * a0,struct proto_dungeon * a1);
extern int teleport_dungeon_correct_branch_type(struct tmpbranch * a0);
extern void insert_branch(branch * a0,boolean a1);
extern branch * teleport_dungeon_add_branch(int a0,int a1,struct proto_dungeon * a2);
extern void teleport_dungeon_add_level(s_level * a0);
extern void teleport_dungeon_init_level(int a0,int a1,struct proto_dungeon * a2);
extern int teleport_dungeon_possible_places(int a0,boolean * a1,struct proto_dungeon * a2);
extern xint16 teleport_dungeon_pick_level(boolean * a0,int a1);
extern boolean teleport_dungeon_place_level(int a0,struct proto_dungeon * a1);
extern int teleport_dungeon_get_dgn_flags(lua_State * a0);
extern int teleport_dungeon_get_dgn_align(lua_State * a0);
extern void teleport_dungeon_init_dungeon_levels(lua_State * a0,struct proto_dungeon * a1,int a2);
extern void teleport_dungeon_init_dungeon_branches(lua_State * a0,struct proto_dungeon * a1,int a2);
extern void teleport_dungeon_init_dungeon_set_entry(struct proto_dungeon * a0,int a1);
extern void teleport_dungeon_init_dungeon_set_depth(struct proto_dungeon * a0,int a1);
extern boolean teleport_dungeon_init_dungeon_dungeons(lua_State * a0,struct proto_dungeon * a1,int a2);
extern void teleport_dungeon_init_castle_tune(void);
extern void teleport_dungeon_fixup_level_locations(void);
extern void teleport_dungeon_free_proto_dungeon(struct proto_dungeon * a0);
extern void init_dungeons(void);
extern xint16 dunlev(d_level * a0);
extern xint16 dunlevs_in_dungeon(d_level * a0);
extern xint16 deepest_lev_reached(boolean a0);
extern xint16 ledger_no(d_level * a0);
extern xint16 maxledgerno(void);
extern xint16 ledger_to_dnum(xint16 a0);
extern xint16 ledger_to_dlev(xint16 a0);
extern schar depth(d_level * a0);
extern boolean on_level(d_level * a0,d_level * a1);
extern s_level * Is_special(d_level * a0);
extern branch * Is_branchlev(d_level * a0);
extern boolean builds_up(d_level * a0);
extern void next_level(boolean a0);
extern void prev_level(boolean a0);
extern void teleport_dungeon_earth_sense(void);
extern void u_on_newpos(coordxy a0,coordxy a1);
extern void u_on_rndspot(int a0);
extern boolean Is_botlevel(d_level * a0);
extern boolean Can_dig_down(d_level * a0);
extern boolean Can_fall_thru(d_level * a0);
extern boolean Can_rise_up(coordxy a0,coordxy a1,d_level * a2);
extern boolean has_ceiling(d_level * a0);
extern boolean avoid_ceiling(d_level * a0);
extern const char * ceiling(coordxy a0,coordxy a1);
extern const char * surface(coordxy a0,coordxy a1);
extern void get_level(d_level * a0,int a1);
extern boolean In_quest(d_level * a0);
extern boolean In_mines(d_level * a0);
extern branch * dungeon_branch(const char * a0);
extern boolean at_dgn_entrance(const char * a0);
extern boolean In_V_tower(d_level * a0);
extern boolean On_W_tower_level(d_level * a0);
extern boolean In_W_tower(coordxy a0,coordxy a1,d_level * a2);
extern boolean In_hell(d_level * a0);
extern void find_hell(d_level * a0);
extern void goto_hell(boolean a0,boolean a1);
extern boolean single_level_branch(d_level * a0);
extern void assign_level(d_level * a0,d_level * a1);
extern void assign_rnd_level(d_level * a0,d_level * a1,int a2);
extern unsigned int induced_align(int a0);
extern boolean Invocation_lev(d_level * a0);
extern xint16 level_difficulty(void);
extern schar lev_by_name(const char * a0);
extern boolean teleport_dungeon_unplaced_floater(struct dungeon * a0);
extern boolean teleport_dungeon_unreachable_level(d_level * a0,boolean a1);
extern void teleport_dungeon_tport_menu(winid a0,char * a1,struct lchoice * a2,d_level * a3,boolean a4);
extern const char * teleport_dungeon_br_string(int a0);
extern char teleport_dungeon_chr_u_on_lvl(d_level * a0);
extern void teleport_dungeon_print_branch(winid a0,int a1,int a2,int a3,boolean a4,struct lchoice * a5);
extern schar print_dungeon(boolean a0,schar * a1,xint16 * a2);
extern void recbranch_mapseen(d_level * a0,d_level * a1);
extern char * teleport_dungeon_get_annotation(d_level * a0);
extern void print_level_annotation(void);
extern void teleport_dungeon_query_annotation(d_level * a0);
extern int donamelevel(void);
extern void free_exclusions(void);
extern void save_exclusions(NHFILE * a0);
extern void load_exclusions(NHFILE * a0);
extern mapseen * teleport_dungeon_find_mapseen(d_level * a0);
extern mapseen * teleport_dungeon_find_mapseen_by_str(const char * a0);
extern void rm_mapseen(int a0);
extern void teleport_dungeon_save_mapseen(NHFILE * a0,mapseen * a1);
extern mapseen * teleport_dungeon_load_mapseen(NHFILE * a0);
extern void overview_stats(winid a0,const char * a1,long * a2,long * a3);
extern void remdun_mapseen(int a0);
extern void init_mapseen(d_level * a0);
extern boolean teleport_dungeon_interest_mapseen(mapseen * a0);
extern void update_lastseentyp(coordxy a0,coordxy a1);
extern int update_mapseen_for(coordxy a0,coordxy a1);
extern void teleport_dungeon_count_feat_lastseentyp(mapseen * a0,coordxy a1,coordxy a2);
extern void recalc_mapseen(void);
extern void mapseen_temple(struct monst * a0);
extern void room_discovered(int a0);
extern int dooverview(void);
extern void show_overview(int a0,int a1);
extern void teleport_dungeon_traverse_mapseenchn(int a0,winid a1,int a2,int a3,int * a4);
extern const char * teleport_dungeon_seen_string(xint16 a0,const char * a1);
extern const char * teleport_dungeon_br_string2(branch * a0);
extern const char * endgamelevelname(char * a0,int a1);
extern const char * teleport_dungeon_shop_string(int a0);
extern char * teleport_dungeon_tunesuffix(mapseen * a0,char * a1,size_t a2);
extern void teleport_dungeon_print_mapseen(winid a0,mapseen * a1,int a2,int a3,boolean a4);
#else
#define teleport_dungeon_dumpit dumpit
#define teleport_dungeon_dname_to_dnum dname_to_dnum
#define teleport_dungeon_find_branch find_branch
#define teleport_dungeon_parent_dnum parent_dnum
#define teleport_dungeon_level_range level_range
#define teleport_dungeon_parent_dlevel parent_dlevel
#define teleport_dungeon_correct_branch_type correct_branch_type
#define teleport_dungeon_add_branch add_branch
#define teleport_dungeon_add_level add_level
#define teleport_dungeon_init_level init_level
#define teleport_dungeon_possible_places possible_places
#define teleport_dungeon_pick_level pick_level
#define teleport_dungeon_place_level place_level
#define teleport_dungeon_get_dgn_flags get_dgn_flags
#define teleport_dungeon_get_dgn_align get_dgn_align
#define teleport_dungeon_init_dungeon_levels init_dungeon_levels
#define teleport_dungeon_init_dungeon_branches init_dungeon_branches
#define teleport_dungeon_init_dungeon_set_entry init_dungeon_set_entry
#define teleport_dungeon_init_dungeon_set_depth init_dungeon_set_depth
#define teleport_dungeon_init_dungeon_dungeons init_dungeon_dungeons
#define teleport_dungeon_init_castle_tune init_castle_tune
#define teleport_dungeon_fixup_level_locations fixup_level_locations
#define teleport_dungeon_free_proto_dungeon free_proto_dungeon
#define teleport_dungeon_earth_sense earth_sense
#define teleport_dungeon_unplaced_floater unplaced_floater
#define teleport_dungeon_unreachable_level unreachable_level
#define teleport_dungeon_tport_menu tport_menu
#define teleport_dungeon_br_string br_string
#define teleport_dungeon_chr_u_on_lvl chr_u_on_lvl
#define teleport_dungeon_print_branch print_branch
#define teleport_dungeon_get_annotation get_annotation
#define teleport_dungeon_query_annotation query_annotation
#define teleport_dungeon_find_mapseen find_mapseen
#define teleport_dungeon_find_mapseen_by_str find_mapseen_by_str
#define teleport_dungeon_save_mapseen save_mapseen
#define teleport_dungeon_load_mapseen load_mapseen
#define teleport_dungeon_interest_mapseen interest_mapseen
#define teleport_dungeon_count_feat_lastseentyp count_feat_lastseentyp
#define teleport_dungeon_traverse_mapseenchn traverse_mapseenchn
#define teleport_dungeon_seen_string seen_string
#define teleport_dungeon_br_string2 br_string2
#define teleport_dungeon_shop_string shop_string
#define teleport_dungeon_tunesuffix tunesuffix
#define teleport_dungeon_print_mapseen print_mapseen
#include "/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/wasm64-build/tree/src/dungeon.c"
#endif
int64_t probe_action(int i,int64_t a0,int64_t a1,int64_t a2,int64_t a3,int64_t a4,int64_t a5,int64_t a6,int64_t a7,int64_t a8,int64_t a9){errorcode=0;int jump=setjmp(panicframe);if(jump){errorcode=jump;return -999;}switch(i){
case 0:teleport_dungeon_dumpit();return 0;
case 1:save_dungeon((NHFILE *)a0,(boolean)a1,(boolean)a2);return 0;
case 2:restore_dungeon((NHFILE *)a0);return 0;
case 3:return(int64_t)teleport_dungeon_dname_to_dnum((const char *)a0);
case 4:return(int64_t)find_level((const char *)a0);
case 5:return(int64_t)teleport_dungeon_find_branch((const char *)a0,(struct proto_dungeon *)a1);
case 6:return(int64_t)teleport_dungeon_parent_dnum((const char *)a0,(struct proto_dungeon *)a1);
case 7:return(int64_t)teleport_dungeon_level_range((xint16)a0,(int)a1,(int)a2,(int)a3,(struct proto_dungeon *)a4,(int *)a5);
case 8:return(int64_t)teleport_dungeon_parent_dlevel((const char *)a0,(struct proto_dungeon *)a1);
case 9:return(int64_t)teleport_dungeon_correct_branch_type((struct tmpbranch *)a0);
case 10:insert_branch((branch *)a0,(boolean)a1);return 0;
case 11:return(int64_t)teleport_dungeon_add_branch((int)a0,(int)a1,(struct proto_dungeon *)a2);
case 12:teleport_dungeon_add_level((s_level *)a0);return 0;
case 13:teleport_dungeon_init_level((int)a0,(int)a1,(struct proto_dungeon *)a2);return 0;
case 14:return(int64_t)teleport_dungeon_possible_places((int)a0,(boolean *)a1,(struct proto_dungeon *)a2);
case 15:return(int64_t)teleport_dungeon_pick_level((boolean *)a0,(int)a1);
case 16:return(int64_t)teleport_dungeon_place_level((int)a0,(struct proto_dungeon *)a1);
case 17:return(int64_t)teleport_dungeon_get_dgn_flags((lua_State *)a0);
case 18:return(int64_t)teleport_dungeon_get_dgn_align((lua_State *)a0);
case 19:teleport_dungeon_init_dungeon_levels((lua_State *)a0,(struct proto_dungeon *)a1,(int)a2);return 0;
case 20:teleport_dungeon_init_dungeon_branches((lua_State *)a0,(struct proto_dungeon *)a1,(int)a2);return 0;
case 21:teleport_dungeon_init_dungeon_set_entry((struct proto_dungeon *)a0,(int)a1);return 0;
case 22:teleport_dungeon_init_dungeon_set_depth((struct proto_dungeon *)a0,(int)a1);return 0;
case 23:return(int64_t)teleport_dungeon_init_dungeon_dungeons((lua_State *)a0,(struct proto_dungeon *)a1,(int)a2);
case 24:teleport_dungeon_init_castle_tune();return 0;
case 25:teleport_dungeon_fixup_level_locations();return 0;
case 26:teleport_dungeon_free_proto_dungeon((struct proto_dungeon *)a0);return 0;
case 27:init_dungeons();return 0;
case 28:return(int64_t)dunlev((d_level *)a0);
case 29:return(int64_t)dunlevs_in_dungeon((d_level *)a0);
case 30:return(int64_t)deepest_lev_reached((boolean)a0);
case 31:return(int64_t)ledger_no((d_level *)a0);
case 32:return(int64_t)maxledgerno();
case 33:return(int64_t)ledger_to_dnum((xint16)a0);
case 34:return(int64_t)ledger_to_dlev((xint16)a0);
case 35:return(int64_t)depth((d_level *)a0);
case 36:return(int64_t)on_level((d_level *)a0,(d_level *)a1);
case 37:return(int64_t)Is_special((d_level *)a0);
case 38:return(int64_t)Is_branchlev((d_level *)a0);
case 39:return(int64_t)builds_up((d_level *)a0);
case 40:next_level((boolean)a0);return 0;
case 41:prev_level((boolean)a0);return 0;
case 42:teleport_dungeon_earth_sense();return 0;
case 43:u_on_newpos((coordxy)a0,(coordxy)a1);return 0;
case 44:u_on_rndspot((int)a0);return 0;
case 45:return(int64_t)Is_botlevel((d_level *)a0);
case 46:return(int64_t)Can_dig_down((d_level *)a0);
case 47:return(int64_t)Can_fall_thru((d_level *)a0);
case 48:return(int64_t)Can_rise_up((coordxy)a0,(coordxy)a1,(d_level *)a2);
case 49:return(int64_t)has_ceiling((d_level *)a0);
case 50:return(int64_t)avoid_ceiling((d_level *)a0);
case 51:return(int64_t)ceiling((coordxy)a0,(coordxy)a1);
case 52:return(int64_t)surface((coordxy)a0,(coordxy)a1);
case 53:get_level((d_level *)a0,(int)a1);return 0;
case 54:return(int64_t)In_quest((d_level *)a0);
case 55:return(int64_t)In_mines((d_level *)a0);
case 56:return(int64_t)dungeon_branch((const char *)a0);
case 57:return(int64_t)at_dgn_entrance((const char *)a0);
case 58:return(int64_t)In_V_tower((d_level *)a0);
case 59:return(int64_t)On_W_tower_level((d_level *)a0);
case 60:return(int64_t)In_W_tower((coordxy)a0,(coordxy)a1,(d_level *)a2);
case 61:return(int64_t)In_hell((d_level *)a0);
case 62:find_hell((d_level *)a0);return 0;
case 63:goto_hell((boolean)a0,(boolean)a1);return 0;
case 64:return(int64_t)single_level_branch((d_level *)a0);
case 65:assign_level((d_level *)a0,(d_level *)a1);return 0;
case 66:assign_rnd_level((d_level *)a0,(d_level *)a1,(int)a2);return 0;
case 67:return(int64_t)induced_align((int)a0);
case 68:return(int64_t)Invocation_lev((d_level *)a0);
case 69:return(int64_t)level_difficulty();
case 70:return(int64_t)lev_by_name((const char *)a0);
case 71:return(int64_t)teleport_dungeon_unplaced_floater((struct dungeon *)a0);
case 72:return(int64_t)teleport_dungeon_unreachable_level((d_level *)a0,(boolean)a1);
case 73:teleport_dungeon_tport_menu((winid)a0,(char *)a1,(struct lchoice *)a2,(d_level *)a3,(boolean)a4);return 0;
case 74:return(int64_t)teleport_dungeon_br_string((int)a0);
case 75:return(int64_t)teleport_dungeon_chr_u_on_lvl((d_level *)a0);
case 76:teleport_dungeon_print_branch((winid)a0,(int)a1,(int)a2,(int)a3,(boolean)a4,(struct lchoice *)a5);return 0;
case 77:return(int64_t)print_dungeon((boolean)a0,(schar *)a1,(xint16 *)a2);
case 78:recbranch_mapseen((d_level *)a0,(d_level *)a1);return 0;
case 79:return(int64_t)teleport_dungeon_get_annotation((d_level *)a0);
case 80:print_level_annotation();return 0;
case 81:teleport_dungeon_query_annotation((d_level *)a0);return 0;
case 82:return(int64_t)donamelevel();
case 83:free_exclusions();return 0;
case 84:save_exclusions((NHFILE *)a0);return 0;
case 85:load_exclusions((NHFILE *)a0);return 0;
case 86:return(int64_t)teleport_dungeon_find_mapseen((d_level *)a0);
case 87:return(int64_t)teleport_dungeon_find_mapseen_by_str((const char *)a0);
case 88:rm_mapseen((int)a0);return 0;
case 89:teleport_dungeon_save_mapseen((NHFILE *)a0,(mapseen *)a1);return 0;
case 90:return(int64_t)teleport_dungeon_load_mapseen((NHFILE *)a0);
case 91:overview_stats((winid)a0,(const char *)a1,(long *)a2,(long *)a3);return 0;
case 92:remdun_mapseen((int)a0);return 0;
case 93:init_mapseen((d_level *)a0);return 0;
case 94:return(int64_t)teleport_dungeon_interest_mapseen((mapseen *)a0);
case 95:update_lastseentyp((coordxy)a0,(coordxy)a1);return 0;
case 96:return(int64_t)update_mapseen_for((coordxy)a0,(coordxy)a1);
case 97:teleport_dungeon_count_feat_lastseentyp((mapseen *)a0,(coordxy)a1,(coordxy)a2);return 0;
case 98:recalc_mapseen();return 0;
case 99:mapseen_temple((struct monst *)a0);return 0;
case 100:room_discovered((int)a0);return 0;
case 101:return(int64_t)dooverview();
case 102:show_overview((int)a0,(int)a1);return 0;
case 103:teleport_dungeon_traverse_mapseenchn((int)a0,(winid)a1,(int)a2,(int)a3,(int *)a4);return 0;
case 104:return(int64_t)teleport_dungeon_seen_string((xint16)a0,(const char *)a1);
case 105:return(int64_t)teleport_dungeon_br_string2((branch *)a0);
case 106:return(int64_t)endgamelevelname((char *)a0,(int)a1);
case 107:return(int64_t)teleport_dungeon_shop_string((int)a0);
case 108:return(int64_t)teleport_dungeon_tunesuffix((mapseen *)a0,(char *)a1,(size_t)a2);
case 109:teleport_dungeon_print_mapseen((winid)a0,(mapseen *)a1,(int)a2,(int)a3,(boolean)a4);return 0;
default:abort();}}

const char*probe_trace(void){return tracebuf;}void probe_clear(void){traceused=0;tracebuf[0]=0;}int probe_draws(void){return draws;}int probe_error(void){return errorcode;}int probe_errno(void){return errno;}
void probe_seed(uint32_t n){seed=n;draws=0;}void probe_option(int i,int v){options[i]=v;}void probe_input(const char*s){strncpy(input,s,sizeof input-1);}
void*probe_pointer(int i){switch(i){case 0:return scratch;case 1:return text;case 2:return levels;case 3:return luaworld;case 4:return serial;case 5:return &nhfile;case 6:return stairs;case 7:return graves;case 8:return monsters;case 9:return species;case 10:return input;default:abort();}}
void*probe_grid(void){return levl;}void probe_map(int x,int y,int typ,int seen){memset(&levl[x][y],0,sizeof levl[x][y]);levl[x][y].typ=typ;levl[x][y].seenv=seen;svl.lastseentyp[x][y]=typ;}
int probe_count(void){return nalloc;}void*probe_alloc_pointer(int i){return allocations[i];}size_t probe_alloc_size(int i){return allocsizes[i];}int probe_alloc_live(int i){return alloclive[i];}void*probe_growth(void){return __real_malloc(50000000);}
size_t probe_serial_length(void){return serialused;}void probe_serial_rewind(void){serialpos=0;}int probe_luatop(void){return luatop;}
void probe_lua(int kind,int index){luatop=luaiter=0;luaindex=index;lpush(LUA_TTABLE,index,kind,0);}
void probe_reset(void){for(int i=0;i<nalloc;i++)if(alloclive[i])__real_free(allocations[i]);nalloc=0;memset(alloclive,0,sizeof alloclive);memset(options,0,sizeof options);

memset((void*)&svd,0,sizeof svd);
memset((void*)&svn,0,sizeof svn);
memset((void*)&svs,0,sizeof svs);
memset((void*)&svb,0,sizeof svb);
memset((void*)&svt,0,sizeof svt);
memset((void*)&svl,0,sizeof svl);
memset((void*)&svi,0,sizeof svi);
memset((void*)&svm,0,sizeof svm);
memset((void*)&flags,0,sizeof flags);
memset((void*)&iflags,0,sizeof iflags);
memset((void*)&gu,0,sizeof gu);
memset((void*)&WIN_MAP,0,sizeof WIN_MAP);
memset((void*)&windowprocs,0,sizeof windowprocs);
memset((void*)&u,0,sizeof u);
memset((void*)&svu,0,sizeof svu);
memset((void*)&gf,0,sizeof gf);
memset((void*)&sve,0,sizeof sve);
memset((void*)&svq,0,sizeof svq);
memset((void*)&svr,0,sizeof svr);

memset(scratch,0,sizeof scratch);memset(levels,0,sizeof levels);memset(monsters,0,sizeof monsters);memset(species,0,sizeof species);memset(stairs,0,sizeof stairs);memset(graves,0,sizeof graves);memset(serial,0,sizeof serial);memset(&nhfile,0,sizeof nhfile);serialused=serialpos=0;nevents=0;
for(int i=0;i<3;i++){snprintf(svd.dungeons[i].dname,sizeof svd.dungeons[i].dname,"Dungeon %d",i);svd.dungeons[i].num_dunlevs=20;svd.dungeons[i].depth_start=1+i*20;svd.dungeons[i].ledger_start=i*20;svd.dungeons[i].entry_lev=1;levels[i].dnum=i;levels[i].dlevel=3;}
svn.n_dgns=3;u.ux=40;u.uy=10;u.uz=levels[0];u.ulevel=5;u.uhp=u.uhpmax=50;svd.dungeon_topology.d_knox_level.dnum=2;svd.dungeon_topology.d_astral_level.dnum=2;svq.quest_status.got_quest=1;
windowprocs.win_clear_nhwindow=win_clear;windowprocs.win_cliparound=win_clip;windowprocs.win_putstr=win_put;windowprocs.win_create_nhwindow=win_create;windowprocs.win_start_menu=win_start;windowprocs.win_end_menu=win_end;windowprocs.win_destroy_nhwindow=win_destroy;windowprocs.win_display_nhwindow=win_display;
for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++){levl[x][y].typ=ROOM;svl.lastseentyp[x][y]=ROOM;}
monsters[0].data=&species[0];monsters[1].data=&species[1];strcpy(text,"fixture");strcpy(input,"fixture annotation");roomstr[0]=0;seed=1;draws=0;callerfile=callerfn=0;callerline=errorcode=luatop=luaiter=luadgn=0;errno=0;probe_clear();}
size_t probe_global_size(int i){switch(i){

case 0:return sizeof svd;
case 1:return sizeof svn;
case 2:return sizeof stderr;
case 3:return sizeof svs;
case 4:return sizeof svb;
case 5:return sizeof svt;
case 6:return sizeof svl;
case 7:return sizeof svi;
case 8:return sizeof svm;
case 9:return sizeof flags;
case 10:return sizeof emptystr;
case 11:return sizeof iflags;
case 12:return sizeof gu;
case 13:return sizeof WIN_MAP;
case 14:return sizeof windowprocs;
case 15:return sizeof u;
case 16:return sizeof svu;
case 17:return sizeof cg;
case 18:return sizeof nul_glyphinfo;
case 19:return sizeof gf;
case 20:return sizeof sve;
case 21:return sizeof svq;
case 22:return sizeof svr;
case 23:return sizeof vowels;
case 24:return sizeof shtypes;
default:abort();}}
size_t probe_region_size(int i){switch(i){
case 0:return sizeof scratch;
case 1:return sizeof text;
case 2:return sizeof levels;
case 3:return sizeof luaworld;
case 4:return sizeof serial;
case 5:return sizeof nhfile;
case 6:return sizeof stairs;
case 7:return sizeof graves;
case 8:return sizeof monsters;
case 9:return sizeof species;
case 10:return sizeof input;
default:abort();}}
size_t probe_type_size(int i){switch(i){case 0:return sizeof(struct proto_dungeon);case 1:return sizeof(struct lchoice);case 2:return sizeof(struct cemetery);case 3:return sizeof(mapseen);case 4:return sizeof(branch);case 5:return sizeof(s_level);default:abort();}}
void*probe_alloc(int size){return newallocation(size);}
int probe_event_count(void){return nevents;}int probe_event_type(int i){return eventtype[i];}size_t probe_event_at(int i){return eventat[i];}size_t probe_event_size(int i){return eventsize[i];}
