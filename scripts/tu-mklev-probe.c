/* Isolated MKLEV configured C / JS controlled-world fixture. */
#include "hack.h"
#include "sp_lev.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <setjmp.h>
__typeof__(svl) svl;
const schar xdir[N_DIRS_Z]={-1,-1,0,1,1,1,0,-1,0,0};
const schar ydir[N_DIRS_Z]={0,-1,-1,-1,0,1,1,1,0,0};
__typeof__(svr) svr;
__typeof__(svn) svn;
__typeof__(gd) gd;
__typeof__(gn) gn;
__typeof__(gs) gs;
__typeof__(svd) svd;
__typeof__(gl) gl;
__typeof__(u) u;
__typeof__(iflags) iflags;
__typeof__(gi) gi;
__typeof__(gt) gt;
__typeof__(gv) gv;
__typeof__(svm) svm;
__typeof__(gm) gm;
__typeof__(mons) mons;
__typeof__(objects) objects;
__typeof__(gc) gc;
__typeof__(gu) gu;
__typeof__(flags) flags;
int nhcb_counts[NUM_NHCB];
const char*const nhcb_name[NUM_NHCB]={"cmd_before","level_enter","level_leave","end_turn"};
__typeof__(gx) gx;
__typeof__(gy) gy;
__typeof__(defsyms) defsyms;
__typeof__(svi) svi;
__typeof__(WIN_MESSAGE) WIN_MESSAGE;
__typeof__(windowprocs) windowprocs;

static char tracebuf[4194304];static size_t traceused;static uint32_t seed=1;static int draws,enabled=1,callerline,options[128],errorcode,rects,roomcalls,checkcalls,positions;
static const char*callerfile,*callerfn;static char luafunction[128];static jmp_buf panicframe;
static struct obj opool[4096];static struct monst mpool[256];static struct trap tpool[1024];static int no,nm,nt;
static void*allocations[4096];static size_t allocsizes[4096];static int nalloc;static int allocationkinds[4096];
static char literal[256],gangbuf[256],roomstr[8];static coord ccoord;static d_level dlev;static branch testbranch;static s_level speciallevel;static NhRect testrect;
_Alignas(16) static unsigned char luastates[256],scratch[8192];static unsigned char vizrows[ROWNO][COLNO];static unsigned char*vizptrs[ROWNO];
static void logfmt(const char*f,...){va_list ap;va_start(ap,f);int n=vsnprintf(tracebuf+traceused,sizeof(tracebuf)-traceused,f,ap);va_end(ap);if(n>0)traceused+=(size_t)n;if(traceused>=sizeof(tracebuf))abort();}
static void ptrlog(const void*p){if(!p){logfmt("0");return;}

if((uintptr_t)p>=(uintptr_t)&svl&&(uintptr_t)p<(uintptr_t)&svl+sizeof svl){logfmt("G0+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&svl));return;}
if((uintptr_t)p>=(uintptr_t)&xdir&&(uintptr_t)p<(uintptr_t)&xdir+sizeof xdir){logfmt("G1+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&xdir));return;}
if((uintptr_t)p>=(uintptr_t)&ydir&&(uintptr_t)p<(uintptr_t)&ydir+sizeof ydir){logfmt("G2+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&ydir));return;}
if((uintptr_t)p>=(uintptr_t)&svr&&(uintptr_t)p<(uintptr_t)&svr+sizeof svr){logfmt("G3+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&svr));return;}
if((uintptr_t)p>=(uintptr_t)&svn&&(uintptr_t)p<(uintptr_t)&svn+sizeof svn){logfmt("G4+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&svn));return;}
if((uintptr_t)p>=(uintptr_t)&gd&&(uintptr_t)p<(uintptr_t)&gd+sizeof gd){logfmt("G5+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gd));return;}
if((uintptr_t)p>=(uintptr_t)&gn&&(uintptr_t)p<(uintptr_t)&gn+sizeof gn){logfmt("G6+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gn));return;}
if((uintptr_t)p>=(uintptr_t)&gs&&(uintptr_t)p<(uintptr_t)&gs+sizeof gs){logfmt("G7+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gs));return;}
if((uintptr_t)p>=(uintptr_t)&svd&&(uintptr_t)p<(uintptr_t)&svd+sizeof svd){logfmt("G8+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&svd));return;}
if((uintptr_t)p>=(uintptr_t)&gl&&(uintptr_t)p<(uintptr_t)&gl+sizeof gl){logfmt("G9+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gl));return;}
if((uintptr_t)p>=(uintptr_t)&u&&(uintptr_t)p<(uintptr_t)&u+sizeof u){logfmt("G10+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&u));return;}
if((uintptr_t)p>=(uintptr_t)&iflags&&(uintptr_t)p<(uintptr_t)&iflags+sizeof iflags){logfmt("G11+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&iflags));return;}
if((uintptr_t)p>=(uintptr_t)&gi&&(uintptr_t)p<(uintptr_t)&gi+sizeof gi){logfmt("G12+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gi));return;}
if((uintptr_t)p>=(uintptr_t)&gt&&(uintptr_t)p<(uintptr_t)&gt+sizeof gt){logfmt("G13+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gt));return;}
if((uintptr_t)p>=(uintptr_t)&gv&&(uintptr_t)p<(uintptr_t)&gv+sizeof gv){logfmt("G14+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gv));return;}
if((uintptr_t)p>=(uintptr_t)&svm&&(uintptr_t)p<(uintptr_t)&svm+sizeof svm){logfmt("G15+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&svm));return;}
if((uintptr_t)p>=(uintptr_t)&gm&&(uintptr_t)p<(uintptr_t)&gm+sizeof gm){logfmt("G16+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gm));return;}
if((uintptr_t)p>=(uintptr_t)&mons&&(uintptr_t)p<(uintptr_t)&mons+sizeof mons){logfmt("G17+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&mons));return;}
if((uintptr_t)p>=(uintptr_t)&objects&&(uintptr_t)p<(uintptr_t)&objects+sizeof objects){logfmt("G18+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&objects));return;}
if((uintptr_t)p>=(uintptr_t)&gc&&(uintptr_t)p<(uintptr_t)&gc+sizeof gc){logfmt("G19+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gc));return;}
if((uintptr_t)p>=(uintptr_t)&gu&&(uintptr_t)p<(uintptr_t)&gu+sizeof gu){logfmt("G20+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gu));return;}
if((uintptr_t)p>=(uintptr_t)&flags&&(uintptr_t)p<(uintptr_t)&flags+sizeof flags){logfmt("G21+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&flags));return;}
if((uintptr_t)p>=(uintptr_t)&nhcb_counts&&(uintptr_t)p<(uintptr_t)&nhcb_counts+sizeof nhcb_counts){logfmt("G22+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&nhcb_counts));return;}
if((uintptr_t)p>=(uintptr_t)&nhcb_name&&(uintptr_t)p<(uintptr_t)&nhcb_name+sizeof nhcb_name){logfmt("G23+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&nhcb_name));return;}
if((uintptr_t)p>=(uintptr_t)&gx&&(uintptr_t)p<(uintptr_t)&gx+sizeof gx){logfmt("G24+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gx));return;}
if((uintptr_t)p>=(uintptr_t)&gy&&(uintptr_t)p<(uintptr_t)&gy+sizeof gy){logfmt("G25+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gy));return;}
if((uintptr_t)p>=(uintptr_t)&defsyms&&(uintptr_t)p<(uintptr_t)&defsyms+sizeof defsyms){logfmt("G26+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&defsyms));return;}
if((uintptr_t)p>=(uintptr_t)&svi&&(uintptr_t)p<(uintptr_t)&svi+sizeof svi){logfmt("G27+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&svi));return;}
if((uintptr_t)p>=(uintptr_t)&WIN_MESSAGE&&(uintptr_t)p<(uintptr_t)&WIN_MESSAGE+sizeof WIN_MESSAGE){logfmt("G28+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&WIN_MESSAGE));return;}
if((uintptr_t)p>=(uintptr_t)&windowprocs&&(uintptr_t)p<(uintptr_t)&windowprocs+sizeof windowprocs){logfmt("G29+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&windowprocs));return;}
if((uintptr_t)p>=(uintptr_t)&opool&&(uintptr_t)p<(uintptr_t)&opool+sizeof opool){logfmt("opool+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&opool));return;}
if((uintptr_t)p>=(uintptr_t)&mpool&&(uintptr_t)p<(uintptr_t)&mpool+sizeof mpool){logfmt("mpool+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&mpool));return;}
if((uintptr_t)p>=(uintptr_t)&tpool&&(uintptr_t)p<(uintptr_t)&tpool+sizeof tpool){logfmt("tpool+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&tpool));return;}
if((uintptr_t)p>=(uintptr_t)&literal&&(uintptr_t)p<(uintptr_t)&literal+sizeof literal){logfmt("literal+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&literal));return;}
if((uintptr_t)p>=(uintptr_t)&gangbuf&&(uintptr_t)p<(uintptr_t)&gangbuf+sizeof gangbuf){logfmt("gangbuf+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gangbuf));return;}
if((uintptr_t)p>=(uintptr_t)&roomstr&&(uintptr_t)p<(uintptr_t)&roomstr+sizeof roomstr){logfmt("roomstr+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&roomstr));return;}
if((uintptr_t)p>=(uintptr_t)&ccoord&&(uintptr_t)p<(uintptr_t)&ccoord+sizeof ccoord){logfmt("ccoord+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&ccoord));return;}
if((uintptr_t)p>=(uintptr_t)&dlev&&(uintptr_t)p<(uintptr_t)&dlev+sizeof dlev){logfmt("dlev+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&dlev));return;}
if((uintptr_t)p>=(uintptr_t)&testbranch&&(uintptr_t)p<(uintptr_t)&testbranch+sizeof testbranch){logfmt("testbranch+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&testbranch));return;}
if((uintptr_t)p>=(uintptr_t)&speciallevel&&(uintptr_t)p<(uintptr_t)&speciallevel+sizeof speciallevel){logfmt("speciallevel+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&speciallevel));return;}
if((uintptr_t)p>=(uintptr_t)&testrect&&(uintptr_t)p<(uintptr_t)&testrect+sizeof testrect){logfmt("testrect+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&testrect));return;}
if((uintptr_t)p>=(uintptr_t)&luastates&&(uintptr_t)p<(uintptr_t)&luastates+sizeof luastates){logfmt("luastates+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&luastates));return;}
if((uintptr_t)p>=(uintptr_t)&scratch&&(uintptr_t)p<(uintptr_t)&scratch+sizeof scratch){logfmt("scratch+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&scratch));return;}
if((uintptr_t)p>=(uintptr_t)&vizrows&&(uintptr_t)p<(uintptr_t)&vizrows+sizeof vizrows){logfmt("vizrows+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&vizrows));return;}
if((uintptr_t)p>=(uintptr_t)&vizptrs&&(uintptr_t)p<(uintptr_t)&vizptrs+sizeof vizptrs){logfmt("vizptrs+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&vizptrs));return;}

for(int i=0;i<nalloc;i++)if(allocations[i]&&(uintptr_t)p>=(uintptr_t)allocations[i]&&(uintptr_t)p<(uintptr_t)allocations[i]+allocsizes[i]){logfmt("A%d+%llu",i,(unsigned long long)((uintptr_t)p-(uintptr_t)allocations[i]));return;}logfmt("UNKNOWN:%llu",(unsigned long long)(uintptr_t)p);}
void*__real_malloc(size_t);void __real_free(void*);
void*__wrap_malloc(size_t n){if(nalloc==4096)abort();void*p=__real_malloc(n);if(p)memset(p,0,n);allocations[nalloc]=p;allocationkinds[nalloc]=0;allocsizes[nalloc++]=n;return p;}
void __wrap_free(void*p){logfmt("free(");ptrlog(p);logfmt(")\n");for(int i=0;i<nalloc;i++)if(allocations[i]==p)allocations[i]=0;__real_free(p);}
static void*newallocation(size_t n){return __wrap_malloc(n);}
static int roll(const char*n,int bound){if(bound<=0){logfmt("BADRNG %d\n",bound);longjmp(panicframe,2);}seed=seed*1664525U+1013904223U;int v=seed%(unsigned)bound;draws++;logfmt("%s[%s:%d:%s](%d)=%d\n",n,callerfile?callerfile:"",callerline,callerfn?callerfn:"",bound,v);return v;}
static struct obj*fixture_newobj(int typ){if(no==4096)abort();struct obj*o=&opool[no++];memset(o,0,sizeof*o);o->otyp=typ;o->oclass=objects[typ].oc_class;o->quan=options[25]?INT64_C(0x20000000000001):1;o->age=options[25]?INT64_C(0x40000000000003):0;o->owt=1;o->where=OBJ_FREE;return o;}
static struct monst*newmon(struct permonst*p,int x,int y){if(nm==256)abort();struct monst*m=&mpool[nm++];memset(m,0,sizeof*m);m->data=p?p:&mons[PM_ORC];m->mx=x;m->my=y;m->mhp=m->mhpmax=10;m->nmon=svl.level.monlist;svl.level.monlist=m;if(isok(x,y))svl.level.monsters[x][y]=m;return m;}
static void fixture_room(void){int k=roomcalls++;coordxy x=4+(k%7)*10,y=3+(k/7)*8;if(y>14)y=3;add_room(x,y,x+5,y+4,TRUE,OROOM,FALSE);svr.rooms[svn.nroom-1].needfill=FILL_NORMAL;}
static void fixture_display(winid id,boolean block){logfmt("window.display(%d,%d)\n",id,block);}static void fixture_delay(void){logfmt("window.delay()\n");}

int (isok)(coordxy a0,coordxy a1){return a0>=1&&a0<COLNO&&a1>=0&&a1<ROWNO;}
boolean (rng_log_enabled)(void){return enabled;}
void (rng_log_set_caller)(const char * a0,int a1,const char * a2){callerfile=a0;callerline=a1;callerfn=a2;}
int (rn2)(int a0){return roll("rn2",a0);}
void wallification(coordxy a0,coordxy a1,coordxy a2,coordxy a3){logfmt("wallification(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(")\n");}
void nhl_done(lua_State * a0){logfmt("nhl_done(");ptrlog(a0);logfmt(")\n");}
lua_State * nhl_init(nhl_sandbox_info * a0){logfmt("nhl_init(");logfmt("sandbox:%u,%u,%u,%u",a0->flags,a0->memlimit,a0->steps,a0->perpcall);logfmt(")\n");return options[8]?0:(lua_State*)luastates;}
boolean nhl_loadlua(lua_State * a0,const char * a1){logfmt("nhl_loadlua(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"<null>");logfmt(")\n");return !options[9];}
void create_des_coder(void){logfmt("create_des_coder(");logfmt(")\n");gc.coder=newallocation(sizeof*gc.coder);}
int lua_getglobal(lua_State * a0,const char * a1){logfmt("lua_getglobal(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"<null>");logfmt(")\n");strncpy(luafunction,a1,sizeof luafunction-1);return 0;}
int nhl_pcall_handle(lua_State * a0,int a1,int a2,const char * a3,NHL_pcall_action a4){logfmt("nhl_pcall_handle(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%s",a3?a3:"<null>");logfmt(",");logfmt("%llu",(unsigned long long)a4);logfmt(")\n");if(!strcmp(luafunction,"themerooms_generate")){if(options[10])gt.themeroom_failed=TRUE;else fixture_room();}return 0;}
NhRect * rnd_rect(void){logfmt("rnd_rect(");logfmt(")\n");return rects++<(options[11]?options[11]:3)?&testrect:0;}
boolean create_room(coordxy a0,coordxy a1,coordxy a2,coordxy a3,coordxy a4,coordxy a5,xint16 a6,xint16 a7){logfmt("create_room(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(",");logfmt("%llu",(unsigned long long)a4);logfmt(",");logfmt("%llu",(unsigned long long)a5);logfmt(",");logfmt("%llu",(unsigned long long)a6);logfmt(",");logfmt("%llu",(unsigned long long)a7);logfmt(")\n");if(a6==VAULT){struct mkroom*c=&svr.rooms[svn.nroom];memset(c,0,sizeof*c);c->lx=70;c->ly=14;c->hx=71;c->hy=15;return !options[12];}if(options[13])return FALSE;fixture_room();svr.rooms[svn.nroom-1].needfill=FILL_NORMAL;return TRUE;}
void reset_xystart_size(void){logfmt("reset_xystart_size(");logfmt(")\n");}
boolean dig_corridor(coord * a0,coord * a1,int * a2,boolean a3,schar a4,schar a5){logfmt("dig_corridor(");logfmt("coord:%d,%d",a0->x,a0->y);logfmt(",");logfmt("coord:%d,%d",a1->x,a1->y);logfmt(",");logfmt("OUT:int");logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(",");logfmt("%llu",(unsigned long long)a4);logfmt(",");logfmt("%llu",(unsigned long long)a5);logfmt(")\n");*a2=abs(a0->x-a1->x)+abs(a0->y-a1->y);return !options[15];}
long * alloc(unsigned int a0){logfmt("alloc(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");return(long*)newallocation(a0);}
char * in_rooms(coordxy a0,coordxy a1,int a2){logfmt("in_rooms(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");roomstr[0]=0;for(int i=0;i<svn.nroom;i++)if(a0>=svr.rooms[i].lx&&a0<=svr.rooms[i].hx&&a1>=svr.rooms[i].ly&&a1<=svr.rooms[i].hy){roomstr[0]=i+ROOMOFFSET;break;}return roomstr;}
xint16 level_difficulty(void){logfmt("level_difficulty(");logfmt(")\n");return options[0]?options[0]:3;}
boolean on_level(d_level * a0,d_level * a1){logfmt("on_level(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");return a0->dnum==a1->dnum&&a0->dlevel==a1->dlevel;}
struct permonst * mkclass(char a0,int a1){logfmt("mkclass(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return &mons[PM_ORC];}
struct monst * makemon(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){logfmt("makemon(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(")\n");return options[20]?0:newmon(a0,a1,a2);}
void set_mimic_sym(struct monst * a0){logfmt("set_mimic_sym(");ptrlog(a0);logfmt(")\n");}
boolean Can_fall_thru(d_level * a0){logfmt("Can_fall_thru(");ptrlog(a0);logfmt(")\n");return !options[5];}
struct trap * maketrap(coordxy a0,coordxy a1,int a2){logfmt("maketrap(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");if(nt==1024)abort();struct trap*t=&tpool[nt++];memset(t,0,sizeof*t);t->tx=a0;t->ty=a1;t->ttyp=a2;return t;}
void make_engr_at(coordxy a0,coordxy a1,const char * a2,const char * a3,long a4,int a5){logfmt("make_engr_at(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%s",a2?a2:"<null>");logfmt(",");logfmt("%s",a3?a3:"<null>");logfmt(",");logfmt("%llu",(unsigned long long)a4);logfmt(",");logfmt("%llu",(unsigned long long)a5);logfmt(")\n");}
void wipe_engr_at(coordxy a0,coordxy a1,xint16 a2,boolean a3){logfmt("wipe_engr_at(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(")\n");}
boolean set_levltyp(coordxy a0,coordxy a1,schar a2){logfmt("set_levltyp(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");if(!isok(a0,a1))return FALSE;levl[a0][a1].typ=a2;return TRUE;}
struct obj * mkcorpstat(int a0,struct monst * a1,struct permonst * a2,coordxy a3,coordxy a4,unsigned int a5){logfmt("mkcorpstat(");logfmt("%llu",(unsigned long long)a0);logfmt(",");ptrlog(a1);logfmt(",");ptrlog(a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(",");logfmt("%llu",(unsigned long long)a4);logfmt(",");logfmt("%llu",(unsigned long long)a5);logfmt(")\n");struct obj*o=fixture_newobj(a0);o->ox=a3;o->oy=a4;return o;}
struct obj * mksobj_at(int a0,coordxy a1,coordxy a2,boolean a3,boolean a4){logfmt("mksobj_at(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(",");logfmt("%llu",(unsigned long long)a4);logfmt(")\n");struct obj*o=fixture_newobj(a0);place_object(o,a1,a2);return o;}
struct obj * mkobj_at(char a0,coordxy a1,coordxy a2,boolean a3){logfmt("mkobj_at(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(")\n");struct obj*o=fixture_newobj(a0==GEM_CLASS?DIAMOND:FOOD_RATION);place_object(o,a1,a2);return o;}
int (rnd)(int a0){return roll("rnd",a0)+1;}
schar depth(d_level * a0){logfmt("depth(");ptrlog(a0);logfmt(")\n");return a0->dlevel;}
boolean In_hell(d_level * a0){logfmt("In_hell(");ptrlog(a0);logfmt(")\n");return options[1];}
void init_rect(void){logfmt("init_rect(");logfmt(")\n");}
void stairway_free_all(void){logfmt("stairway_free_all(");logfmt(")\n");while(gs.stairs){stairway*t=gs.stairs;gs.stairs=t->next;free(t);}}
void clear_regions(void){logfmt("clear_regions(");logfmt(")\n");}
void free_exclusions(void){logfmt("free_exclusions(");logfmt(")\n");}
boolean somexyspace(struct mkroom * a0,coord * a1){logfmt("somexyspace(");ptrlog(a0);logfmt(",");logfmt("OUT:coord");logfmt(")\n");if(options[16])return FALSE;int width=a0->hx-a0->lx+1,height=a0->hy-a0->ly+1;if(width<1||height<1)return FALSE;a1->x=a0->lx+(positions++%width);a1->y=a0->ly+((positions/width)%height);return TRUE;}
struct obj * mkgold(long a0,coordxy a1,coordxy a2){logfmt("mkgold(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");struct obj*o=fixture_newobj(GOLD_PIECE);o->quan=a0;place_object(o,a1,a2);return o;}
branch * Is_branchlev(d_level * a0){logfmt("Is_branchlev(");ptrlog(a0);logfmt(")\n");return options[17]?&testbranch:0;}
struct obj * mksobj(int a0,boolean a1,boolean a2){logfmt("mksobj(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");return options[21]?0:fixture_newobj(a0);}
int weight(struct obj * a0){logfmt("weight(");ptrlog(a0);logfmt(")\n");return(int)(a0->quan*2);}
struct obj * add_to_container(struct obj * a0,struct obj * a1){logfmt("add_to_container(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");a1->nobj=a0->cobj;a0->cobj=a1;return a1;}
struct obj * mkobj(int a0,boolean a1){logfmt("mkobj(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return fixture_newobj(a0==GEM_CLASS?DIAMOND:FOOD_RATION);}
void dealloc_obj(struct obj * a0){logfmt("dealloc_obj(");ptrlog(a0);logfmt(")\n");}
char * random_engraving(char * a0,char * a1){logfmt("random_engraving(");logfmt("OUT:char[256]");logfmt(",");logfmt("OUT:char[256]");logfmt(")\n");strcpy(a0,"fixture graffiti");strcpy(a1,"fixture graffiti");return a0;}
void init_dungeons(void){logfmt("init_dungeons(");logfmt(")\n");}
void oinit(void){logfmt("oinit(");logfmt(")\n");}
s_level * Is_special(d_level * a0){logfmt("Is_special(");ptrlog(a0);logfmt(")\n");return options[18]?&speciallevel:0;}
void makemaz(const char * a0){logfmt("makemaz(");logfmt("%s",a0?a0:"<null>");logfmt(")\n");}
boolean In_quest(d_level * a0){logfmt("In_quest(");ptrlog(a0);logfmt(")\n");return options[2];}
s_level * find_level(const char * a0){logfmt("find_level(");logfmt("%s",a0?a0:"<null>");logfmt(")\n");return &speciallevel;}
void makeroguerooms(void){logfmt("makeroguerooms(");logfmt(")\n");fixture_room();fixture_room();}
void makerogueghost(void){logfmt("makerogueghost(");logfmt(")\n");}
void __assert_fail(const char * a0,const char * a1,int a2,const char * a3){logfmt("__assert_fail(");logfmt("%s",a0?a0:"<null>");logfmt(",");logfmt("%s",a1?a1:"<null>");logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%s",a3?a3:"<null>");logfmt(")\n");longjmp(panicframe,3);}
boolean debugcore(const char * a0,boolean a1){logfmt("debugcore(");logfmt("%s",a0?a0:"<null>");logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return options[19];}
boolean check_room(coordxy * a0,coordxy * a1,coordxy * a2,coordxy * a3,boolean a4){logfmt("check_room(");logfmt("short:%d",*a0);logfmt(",");logfmt("short:%d",*a1);logfmt(",");logfmt("short:%d",*a2);logfmt(",");logfmt("short:%d",*a3);logfmt(",");logfmt("%llu",(unsigned long long)a4);logfmt(")\n");checkcalls++;*a1=1;*a3=1;return options[14]==0||checkcalls>options[14];}
void fill_special_room(struct mkroom * a0){logfmt("fill_special_room(");ptrlog(a0);logfmt(")\n");}
char * nh_getenv(const char * a0){logfmt("nh_getenv(");logfmt("%s",a0?a0:"<null>");logfmt(")\n");return 0;}
void do_mkroom(int a0){logfmt("do_mkroom(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");}
struct permonst * antholemon(void){logfmt("antholemon(");logfmt(")\n");return &mons[PM_GIANT_ANT];}
const char * lua_pushstring(lua_State * a0,const char * a1){logfmt("lua_pushstring(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"<null>");logfmt(")\n");return a1;}
void lua_settop(lua_State * a0,int a1){logfmt("lua_settop(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");}
boolean In_V_tower(d_level * a0){logfmt("In_V_tower(");ptrlog(a0);logfmt(")\n");return options[4];}
boolean In_mines(d_level * a0){logfmt("In_mines(");ptrlog(a0);logfmt(")\n");return options[3];}
void add_to_buried(struct obj * a0){logfmt("add_to_buried(");ptrlog(a0);logfmt(")\n");a0->nobj=svl.level.buriedobjlist;svl.level.buriedobjlist=a0;}
void place_object(struct obj * a0,coordxy a1,coordxy a2){logfmt("place_object(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");a0->ox=a1;a0->oy=a2;a0->nexthere=svl.level.objects[a1][a2];svl.level.objects[a1][a2]=a0;}
xint16 dunlev(d_level * a0){logfmt("dunlev(");ptrlog(a0);logfmt(")\n");return a0->dlevel;}
void bound_digging(void){logfmt("bound_digging(");logfmt(")\n");}
void set_wall_state(void){logfmt("set_wall_state(");logfmt(")\n");}
void reseed_random(int (*a0)(int)){logfmt("reseed_random(");logfmt("%s",a0==(rn2)?"rn2":a0==(rn2_on_display_rng)?"rn2_on_display_rng":"BAD_NATIVE_RNG_ID");logfmt(")\n");}
void init_mapseen(d_level * a0){logfmt("init_mapseen(");ptrlog(a0);logfmt(")\n");}
int getbones(void){logfmt("getbones(");logfmt(")\n");return options[7];}
void mazexy(coord * a0){logfmt("mazexy(");logfmt("OUT:coord");logfmt(")\n");a0->x=40;a0->y=10;}
boolean inside_room(struct mkroom * a0,coordxy a1,coordxy a2){logfmt("inside_room(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");return a1>=a0->lx&&a1<=a0->hx&&a2>=a0->ly&&a2<=a0->hy;}
void mkportal(coordxy a0,coordxy a1,xint16 a2,xint16 a3){logfmt("mkportal(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(")\n");}
void stairway_add(coordxy a0,coordxy a1,boolean a2,boolean a3,d_level * a4){logfmt("stairway_add(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(",");logfmt("level:%d,%d",a4->dnum,a4->dlevel);logfmt(")\n");stairway*t=newallocation(sizeof*t);allocationkinds[nalloc-1]=1;t->sx=a0;t->sy=a1;t->up=a2;t->isladder=a3;t->tolev=*a4;t->next=gs.stairs;gs.stairs=t;}
struct trap * t_at(coordxy a0,coordxy a1){logfmt("t_at(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");for(int i=0;i<nt;i++)if(tpool[i].tx==a0&&tpool[i].ty==a1&&tpool[i].ttyp)return &tpool[i];return 0;}
boolean is_lava(coordxy a0,coordxy a1){logfmt("is_lava(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return isok(a0,a1)&&levl[a0][a1].typ==LAVAPOOL;}
boolean is_pool(coordxy a0,coordxy a1){logfmt("is_pool(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return isok(a0,a1)&&(levl[a0][a1].typ==POOL||levl[a0][a1].typ==MOAT||levl[a0][a1].typ==WATER);}
boolean invocation_pos(coordxy a0,coordxy a1){logfmt("invocation_pos(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return a0==svi.inv_pos.x&&a1==svi.inv_pos.y;}
void curse(struct obj * a0){logfmt("curse(");ptrlog(a0);logfmt(")\n");a0->cursed=1;}
boolean breaktest(struct obj * a0){logfmt("breaktest(");ptrlog(a0);logfmt(")\n");return options[22];}
void begin_burn(struct obj * a0,boolean a1){logfmt("begin_burn(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");}
boolean single_level_branch(d_level * a0){logfmt("single_level_branch(");ptrlog(a0);logfmt(")\n");return options[23];}
void paniclog(const char * a0,const char * a1){logfmt("paniclog(");logfmt("%s",a0?a0:"<null>");logfmt(",");logfmt("%s",a1?a1:"<null>");logfmt(")\n");}
boolean is_pool_or_lava(coordxy a0,coordxy a1){logfmt("is_pool_or_lava(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return is_pool(a0,a1)||is_lava(a0,a1);}
struct obj * sobj_at(int a0,coordxy a1,coordxy a2){logfmt("sobj_at(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");for(int i=0;i<no;i++)if(opool[i].otyp==a0&&opool[i].ox==a1&&opool[i].oy==a2)return &opool[i];return 0;}
void assign_level(d_level * a0,d_level * a1){logfmt("assign_level(");logfmt("OUT:d_level");logfmt(",");ptrlog(a1);logfmt(")\n");*a0=*a1;}
int back_to_glyph(coordxy a0,coordxy a1){logfmt("back_to_glyph(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return 0;}
int glyph_to_cmap(int a0){logfmt("glyph_to_cmap(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");return 0;}
xint16 dunlevs_in_dungeon(d_level * a0){logfmt("dunlevs_in_dungeon(");ptrlog(a0);logfmt(")\n");return 20;}
boolean has_dnstairs(struct mkroom * a0){logfmt("has_dnstairs(");ptrlog(a0);logfmt(")\n");for(stairway*t=gs.stairs;t;t=t->next)if(!t->up&&t->sx>=a0->lx&&t->sx<=a0->hx&&t->sy>=a0->ly&&t->sy<=a0->hy)return TRUE;return FALSE;}
boolean has_upstairs(struct mkroom * a0){logfmt("has_upstairs(");ptrlog(a0);logfmt(")\n");for(stairway*t=gs.stairs;t;t=t->next)if(t->up&&t->sx>=a0->lx&&t->sx<=a0->hx&&t->sy>=a0->ly&&t->sy<=a0->hy)return TRUE;return FALSE;}
boolean Is_botlevel(d_level * a0){logfmt("Is_botlevel(");ptrlog(a0);logfmt(")\n");return options[6];}
int somex(struct mkroom * a0){logfmt("somex(");ptrlog(a0);logfmt(")\n");return a0->lx;}
int somey(struct mkroom * a0){logfmt("somey(");ptrlog(a0);logfmt(")\n");return a0->ly;}
void make_grave(coordxy a0,coordxy a1,const char * a2){logfmt("make_grave(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%s",a2?a2:"<null>");logfmt(")\n");}
void buried_ball_to_punishment(void){logfmt("buried_ball_to_punishment(");logfmt(")\n");}
void reset_utrap(boolean a0){logfmt("reset_utrap(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");u.utrap=0;}
void flush_screen(int a0){logfmt("flush_screen(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");}
void newsym(coordxy a0,coordxy a1){logfmt("newsym(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");}
void deltrap(struct trap * a0){logfmt("deltrap(");ptrlog(a0);logfmt(")\n");a0->ttyp=0;}
void fracture_rock(struct obj * a0){logfmt("fracture_rock(");ptrlog(a0);logfmt(")\n");a0->otyp=ROCK;}
void obj_extract_self(struct obj * a0){logfmt("obj_extract_self(");ptrlog(a0);logfmt(")\n");a0->ox=a0->oy=0;}
void obfree(struct obj * a0,struct obj * a1){logfmt("obfree(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");}
void seemimic(struct monst * a0){logfmt("seemimic(");ptrlog(a0);logfmt(")\n");}
int mintrap(struct monst * a0,unsigned int a1){logfmt("mintrap(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return 0;}
int minliquid(struct monst * a0){logfmt("minliquid(");ptrlog(a0);logfmt(")\n");return 0;}
int does_block(int a0,int a1,struct rm * a2){logfmt("does_block(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");ptrlog(a2);logfmt(")\n");return 0;}
void unblock_point(int a0,int a1){logfmt("unblock_point(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");}
branch * dungeon_branch(const char * a0){logfmt("dungeon_branch(");logfmt("%s",a0?a0:"<null>");logfmt(")\n");return &testbranch;}
boolean at_dgn_entrance(const char * a0){logfmt("at_dgn_entrance(");logfmt("%s",a0?a0:"<null>");logfmt(")\n");return 0;}
void insert_branch(branch * a0,boolean a1){logfmt("insert_branch(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");}
int (rn2_on_display_rng)(int n){return roll("display_rng",n);}
int lua_gc(lua_State*L,int what,...){logfmt("lua_gc(");ptrlog(L);logfmt(",%d)\n",what);return 0;}
void panic(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[2048];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("panic:%s\n",b);longjmp(panicframe,1);}
void impossible(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[2048];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("impossible:%s\n",b);}
void pline(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[2048];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("pline:%s\n",b);}
void pline_The(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[2048];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("pline_The:%s\n",b);}
void You(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[2048];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("You:%s\n",b);}
void nh_snprintf(const char*f,int line,char*b,size_t n,const char*fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(b,n,fmt,ap);va_end(ap);logfmt("nh_snprintf[%s:%d]:%s\n",f,line,b);}
#ifdef HYBRID_MKLEV
extern int teleport_mklev_mkroom_cmp(const void * a0,const void * a1);
extern boolean teleport_mklev_good_rm_wall_doorpos(coordxy a0,coordxy a1,int a2,struct mkroom * a3);
extern boolean teleport_mklev_finddpos_shift(coordxy * a0,coordxy * a1,int a2,struct mkroom * a3);
extern boolean teleport_mklev_finddpos(coord * a0,int a1,struct mkroom * a2);
extern void sort_rooms();
extern void teleport_mklev_do_room_or_subroom(struct mkroom * a0,coordxy a1,coordxy a2,coordxy a3,coordxy a4,boolean a5,schar a6,boolean a7,boolean a8);
extern void add_room(coordxy a0,coordxy a1,coordxy a2,coordxy a3,boolean a4,schar a5,boolean a6);
extern void add_subroom(struct mkroom * a0,coordxy a1,coordxy a2,coordxy a3,coordxy a4,boolean a5,schar a6,boolean a7);
extern void free_luathemes(enum lua_theme_group a0);
extern void teleport_mklev_makerooms();
extern void teleport_mklev_join(int a0,int a1,boolean a2);
extern void makecorridors();
extern void teleport_mklev_alloc_doors();
extern void add_door(coordxy a0,coordxy a1,struct mkroom * a2);
extern void teleport_mklev_dosdoor(coordxy a0,coordxy a1,struct mkroom * a2,int a3);
extern boolean teleport_mklev_cardinal_nextto_room(struct mkroom * a0,coordxy a1,coordxy a2);
extern boolean teleport_mklev_place_niche(struct mkroom * a0,int * a1,coordxy * a2,coordxy * a3);
extern void teleport_mklev_makeniche(int a0);
extern void teleport_mklev_make_niches();
extern void teleport_mklev_makevtele();
extern void count_level_features();
extern void clear_level_structures();
extern void teleport_mklev_fill_ordinary_room(struct mkroom * a0,boolean a1);
extern void teleport_mklev_themerooms_post_level_generate();
extern boolean teleport_mklev_chk_okdoor(coordxy a0,coordxy a1);
extern void teleport_mklev_mklev_sanity_check();
extern void teleport_mklev_makelevel();
extern boolean teleport_mklev_water_has_kelp(coordxy a0,coordxy a1,int a2,int a3);
extern void mineralize(int a0,int a1,int a2,int a3,boolean a4);
extern void level_finalize_topology();
extern void mklev();
extern void topologize(struct mkroom * a0);
extern struct mkroom * teleport_mklev_find_branch_room(coord * a0);
extern struct mkroom * teleport_mklev_pos_to_room(coordxy a0,coordxy a1);
extern void place_branch(branch * a0,coordxy a1,coordxy a2);
extern boolean teleport_mklev_bydoor(coordxy a0,coordxy a1);
extern int okdoor(coordxy a0,coordxy a1);
extern boolean maybe_sdoor(int a0);
extern void dodoor(coordxy a0,coordxy a1,struct mkroom * a2);
extern boolean occupied(coordxy a0,coordxy a1);
extern void teleport_mklev_mktrap_victim(struct trap * a0);
extern int teleport_mklev_traptype_rnd(unsigned int a0);
extern int teleport_mklev_traptype_roguelvl();
extern void mktrap(int a0,unsigned int a1,struct mkroom * a2,coord * a3);
extern void mkstairs(coordxy a0,coordxy a1,char a2,struct mkroom * a3,boolean a4);
extern boolean teleport_mklev_generate_stairs_room_good(struct mkroom * a0,int a1);
extern struct mkroom * teleport_mklev_generate_stairs_find_room();
extern void teleport_mklev_generate_stairs();
extern void teleport_mklev_mkfount(struct mkroom * a0);
extern boolean teleport_mklev_find_okay_roompos(struct mkroom * a0,coord * a1);
extern void teleport_mklev_mksink(struct mkroom * a0);
extern void teleport_mklev_mkaltar(struct mkroom * a0);
extern void teleport_mklev_mkgrave(struct mkroom * a0);
extern void mkinvokearea();
extern void teleport_mklev_mkinvpos(coordxy a0,coordxy a1,int a2);
extern int teleport_mklev_mkinvk_check_wall(coordxy a0,coordxy a1);
extern void teleport_mklev_mk_knox_portal(coordxy a0,coordxy a1);
#else
#define teleport_mklev_mkroom_cmp mkroom_cmp
#define teleport_mklev_good_rm_wall_doorpos good_rm_wall_doorpos
#define teleport_mklev_finddpos_shift finddpos_shift
#define teleport_mklev_finddpos finddpos
#define teleport_mklev_do_room_or_subroom do_room_or_subroom
#define teleport_mklev_makerooms makerooms
#define teleport_mklev_join join
#define teleport_mklev_alloc_doors alloc_doors
#define teleport_mklev_dosdoor dosdoor
#define teleport_mklev_cardinal_nextto_room cardinal_nextto_room
#define teleport_mklev_place_niche place_niche
#define teleport_mklev_makeniche makeniche
#define teleport_mklev_make_niches make_niches
#define teleport_mklev_makevtele makevtele
#define teleport_mklev_fill_ordinary_room fill_ordinary_room
#define teleport_mklev_themerooms_post_level_generate themerooms_post_level_generate
#define teleport_mklev_chk_okdoor chk_okdoor
#define teleport_mklev_mklev_sanity_check mklev_sanity_check
#define teleport_mklev_makelevel makelevel
#define teleport_mklev_water_has_kelp water_has_kelp
#define teleport_mklev_find_branch_room find_branch_room
#define teleport_mklev_pos_to_room pos_to_room
#define teleport_mklev_bydoor bydoor
#define teleport_mklev_mktrap_victim mktrap_victim
#define teleport_mklev_traptype_rnd traptype_rnd
#define teleport_mklev_traptype_roguelvl traptype_roguelvl
#define teleport_mklev_generate_stairs_room_good generate_stairs_room_good
#define teleport_mklev_generate_stairs_find_room generate_stairs_find_room
#define teleport_mklev_generate_stairs generate_stairs
#define teleport_mklev_mkfount mkfount
#define teleport_mklev_find_okay_roompos find_okay_roompos
#define teleport_mklev_mksink mksink
#define teleport_mklev_mkaltar mkaltar
#define teleport_mklev_mkgrave mkgrave
#define teleport_mklev_mkinvpos mkinvpos
#define teleport_mklev_mkinvk_check_wall mkinvk_check_wall
#define teleport_mklev_mk_knox_portal mk_knox_portal
#include "/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/wasm64-build/tree/src/mklev.c"
#endif
int64_t probe_action(int i,int64_t a0,int64_t a1,int64_t a2,int64_t a3,int64_t a4,int64_t a5,int64_t a6,int64_t a7,int64_t a8,int64_t a9){errorcode=0;int jump=setjmp(panicframe);if(jump){errorcode=jump;return -999;}switch(i){
case 0:return(int64_t)teleport_mklev_mkroom_cmp((const void *)a0,(const void *)a1);
case 1:return(int64_t)teleport_mklev_good_rm_wall_doorpos((coordxy)a0,(coordxy)a1,(int)a2,(struct mkroom *)a3);
case 2:return(int64_t)teleport_mklev_finddpos_shift((coordxy *)a0,(coordxy *)a1,(int)a2,(struct mkroom *)a3);
case 3:return(int64_t)teleport_mklev_finddpos((coord *)a0,(int)a1,(struct mkroom *)a2);
case 4:sort_rooms();return 0;
case 5:teleport_mklev_do_room_or_subroom((struct mkroom *)a0,(coordxy)a1,(coordxy)a2,(coordxy)a3,(coordxy)a4,(boolean)a5,(schar)a6,(boolean)a7,(boolean)a8);return 0;
case 6:add_room((coordxy)a0,(coordxy)a1,(coordxy)a2,(coordxy)a3,(boolean)a4,(schar)a5,(boolean)a6);return 0;
case 7:add_subroom((struct mkroom *)a0,(coordxy)a1,(coordxy)a2,(coordxy)a3,(coordxy)a4,(boolean)a5,(schar)a6,(boolean)a7);return 0;
case 8:free_luathemes((enum lua_theme_group)a0);return 0;
case 9:teleport_mklev_makerooms();return 0;
case 10:teleport_mklev_join((int)a0,(int)a1,(boolean)a2);return 0;
case 11:makecorridors();return 0;
case 12:teleport_mklev_alloc_doors();return 0;
case 13:add_door((coordxy)a0,(coordxy)a1,(struct mkroom *)a2);return 0;
case 14:teleport_mklev_dosdoor((coordxy)a0,(coordxy)a1,(struct mkroom *)a2,(int)a3);return 0;
case 15:return(int64_t)teleport_mklev_cardinal_nextto_room((struct mkroom *)a0,(coordxy)a1,(coordxy)a2);
case 16:return(int64_t)teleport_mklev_place_niche((struct mkroom *)a0,(int *)a1,(coordxy *)a2,(coordxy *)a3);
case 17:teleport_mklev_makeniche((int)a0);return 0;
case 18:teleport_mklev_make_niches();return 0;
case 19:teleport_mklev_makevtele();return 0;
case 20:count_level_features();return 0;
case 21:clear_level_structures();return 0;
case 22:teleport_mklev_fill_ordinary_room((struct mkroom *)a0,(boolean)a1);return 0;
case 23:teleport_mklev_themerooms_post_level_generate();return 0;
case 24:return(int64_t)teleport_mklev_chk_okdoor((coordxy)a0,(coordxy)a1);
case 25:teleport_mklev_mklev_sanity_check();return 0;
case 26:teleport_mklev_makelevel();return 0;
case 27:return(int64_t)teleport_mklev_water_has_kelp((coordxy)a0,(coordxy)a1,(int)a2,(int)a3);
case 28:mineralize((int)a0,(int)a1,(int)a2,(int)a3,(boolean)a4);return 0;
case 29:level_finalize_topology();return 0;
case 30:mklev();return 0;
case 31:topologize((struct mkroom *)a0);return 0;
case 32:return(int64_t)teleport_mklev_find_branch_room((coord *)a0);
case 33:return(int64_t)teleport_mklev_pos_to_room((coordxy)a0,(coordxy)a1);
case 34:place_branch((branch *)a0,(coordxy)a1,(coordxy)a2);return 0;
case 35:return(int64_t)teleport_mklev_bydoor((coordxy)a0,(coordxy)a1);
case 36:return(int64_t)okdoor((coordxy)a0,(coordxy)a1);
case 37:return(int64_t)maybe_sdoor((int)a0);
case 38:dodoor((coordxy)a0,(coordxy)a1,(struct mkroom *)a2);return 0;
case 39:return(int64_t)occupied((coordxy)a0,(coordxy)a1);
case 40:teleport_mklev_mktrap_victim((struct trap *)a0);return 0;
case 41:return(int64_t)teleport_mklev_traptype_rnd((unsigned int)a0);
case 42:return(int64_t)teleport_mklev_traptype_roguelvl();
case 43:mktrap((int)a0,(unsigned int)a1,(struct mkroom *)a2,(coord *)a3);return 0;
case 44:mkstairs((coordxy)a0,(coordxy)a1,(char)a2,(struct mkroom *)a3,(boolean)a4);return 0;
case 45:return(int64_t)teleport_mklev_generate_stairs_room_good((struct mkroom *)a0,(int)a1);
case 46:return(int64_t)teleport_mklev_generate_stairs_find_room();
case 47:teleport_mklev_generate_stairs();return 0;
case 48:teleport_mklev_mkfount((struct mkroom *)a0);return 0;
case 49:return(int64_t)teleport_mklev_find_okay_roompos((struct mkroom *)a0,(coord *)a1);
case 50:teleport_mklev_mksink((struct mkroom *)a0);return 0;
case 51:teleport_mklev_mkaltar((struct mkroom *)a0);return 0;
case 52:teleport_mklev_mkgrave((struct mkroom *)a0);return 0;
case 53:mkinvokearea();return 0;
case 54:teleport_mklev_mkinvpos((coordxy)a0,(coordxy)a1,(int)a2);return 0;
case 55:return(int64_t)teleport_mklev_mkinvk_check_wall((coordxy)a0,(coordxy)a1);
case 56:teleport_mklev_mk_knox_portal((coordxy)a0,(coordxy)a1);return 0;
default:abort();}}

const char*probe_trace(void){return tracebuf;}void probe_clear(void){traceused=0;tracebuf[0]=0;}int probe_draws(void){return draws;}int probe_error(void){return errorcode;}
void probe_seed(uint32_t n){seed=n;draws=0;}void probe_option(int i,int v){options[i]=v;}
void*probe_pointer(int i){switch(i){case 0:return &ccoord;case 1:return &dlev;case 2:return literal;case 3:return gangbuf;case 4:return opool;case 5:return mpool;case 6:return tpool;case 7:return &testbranch;case 8:return &speciallevel;case 9:return luastates;case 10:return scratch;case 11:return vizrows;case 12:return vizptrs;default:return 0;}}
void*probe_grid(void){return levl;}void probe_coord(int x,int y){ccoord.x=x;ccoord.y=y;}
void probe_map(int x,int y,int typ,int bits){memset(&levl[x][y],0,sizeof levl[x][y]);levl[x][y].typ=typ;levl[x][y].lit=bits&1;levl[x][y].horizontal=(bits>>1)&1;levl[x][y].flags=(bits>>2)&31;}
int probe_count(int i){return i==0?no:i==1?nm:i==2?nt:i==3?nalloc:0;}void*probe_alloc_pointer(int i){return allocations[i];}size_t probe_alloc_size(int i){return allocsizes[i];}
void*probe_growth(void){return __real_malloc(50000000);}
void probe_reset(void){for(int i=0;i<nalloc;i++)if(allocations[i])__real_free(allocations[i]);nalloc=0;memset(options,0,sizeof options);memset(opool,0,sizeof opool);memset(mpool,0,sizeof mpool);memset(tpool,0,sizeof tpool);no=nm=nt=0;rects=roomcalls=checkcalls=positions=0;

memset(&svl,0,sizeof svl);
memset(&svr,0,sizeof svr);
memset(&svn,0,sizeof svn);
memset(&gd,0,sizeof gd);
memset(&gn,0,sizeof gn);
memset(&gs,0,sizeof gs);
memset(&svd,0,sizeof svd);
memset(&gl,0,sizeof gl);
memset(&u,0,sizeof u);
memset(&iflags,0,sizeof iflags);
memset(&gi,0,sizeof gi);
memset(&gt,0,sizeof gt);
memset(&gv,0,sizeof gv);
memset(&svm,0,sizeof svm);
memset(&gm,0,sizeof gm);
memset(&mons,0,sizeof mons);
memset(&objects,0,sizeof objects);
memset(&gc,0,sizeof gc);
memset(&gu,0,sizeof gu);
memset(&flags,0,sizeof flags);
memset(&nhcb_counts,0,sizeof nhcb_counts);
memset(&gx,0,sizeof gx);
memset(&gy,0,sizeof gy);
memset(&svi,0,sizeof svi);
memset(&WIN_MESSAGE,0,sizeof WIN_MESSAGE);
memset(&windowprocs,0,sizeof windowprocs);

memset(&testbranch,0,sizeof testbranch);testbranch.end1.dnum=99;testbranch.end2.dnum=1;testbranch.end2.dlevel=1;memset(&speciallevel,0,sizeof speciallevel);speciallevel.dlevel.dlevel=10;
memset(scratch,0,sizeof scratch);memset(vizrows,0,sizeof vizrows);for(int y=0;y<ROWNO;y++)vizptrs[y]=vizrows[y];gv.viz_array=vizptrs;
windowprocs.win_display_nhwindow=fixture_display;windowprocs.win_delay_output=fixture_delay;
gx.x_maze_max=COLNO-2;gy.y_maze_max=ROWNO-2;u.ux=40;u.uy=10;u.uz.dlevel=3;svi.inv_pos.x=40;svi.inv_pos.y=10;svn.n_dgns=4;
svd.dungeon_topology.d_mines_dnum=2;svd.dungeon_topology.d_quest_dnum=3;svd.dungeon_topology.d_rogue_level.dnum=9;svd.dungeon_topology.d_rogue_level.dlevel=9;svd.dungeon_topology.d_medusa_level.dlevel=25;svd.dungeon_topology.d_wiz1_level.dlevel=30;
for(int i=0;i<NUM_OBJECTS;i++){objects[i].oc_class=FOOD_CLASS;objects[i].oc_prob=1;}objects[GOLD_PIECE].oc_class=COIN_CLASS;objects[DIAMOND].oc_class=GEM_CLASS;
gs.subrooms=&svr.rooms[MAXNROFROOMS+1];svr.rooms[0].hx=-1;gs.subrooms[0].hx=-1;gv.vault_x=-1;strcpy(literal,"");strcpy(gangbuf,"");strcpy(luafunction,"");seed=1;draws=0;callerfile=callerfn=0;callerline=0;errorcode=0;memset(&ccoord,0,sizeof ccoord);memset(&dlev,0,sizeof dlev);probe_clear();}
size_t probe_region_size(int i){switch(i){case 0:return sizeof opool;case 1:return sizeof mpool;case 2:return sizeof tpool;case 3:return sizeof testbranch;case 4:return sizeof speciallevel;case 5:return sizeof vizrows;default:return 0;}}
size_t probe_global_size(int i){switch(i){

case 0:return sizeof svl;
case 1:return sizeof xdir;
case 2:return sizeof ydir;
case 3:return sizeof svr;
case 4:return sizeof svn;
case 5:return sizeof gd;
case 6:return sizeof gn;
case 7:return sizeof gs;
case 8:return sizeof svd;
case 9:return sizeof gl;
case 10:return sizeof u;
case 11:return sizeof iflags;
case 12:return sizeof gi;
case 13:return sizeof gt;
case 14:return sizeof gv;
case 15:return sizeof svm;
case 16:return sizeof gm;
case 17:return sizeof mons;
case 18:return sizeof objects;
case 19:return sizeof gc;
case 20:return sizeof gu;
case 21:return sizeof flags;
case 22:return sizeof nhcb_counts;
case 23:return sizeof nhcb_name;
case 24:return sizeof gx;
case 25:return sizeof gy;
case 26:return sizeof defsyms;
case 27:return sizeof svi;
case 28:return sizeof WIN_MESSAGE;
case 29:return sizeof windowprocs;
default:abort();}}
void*probe_identity(int i){if(i<NUM_NHCB)return(void*)nhcb_name[i];if(i==4)return(void*)fixture_display;if(i==5)return(void*)fixture_delay;abort();}
size_t probe_pointer_offset(int k,int i){switch(k){case 0:switch(i){case 0:return offsetof(struct obj,nobj);case 1:return offsetof(struct obj,v);case 2:return offsetof(struct obj,cobj);case 3:return offsetof(struct obj,oextra);}break;case 1:switch(i){case 0:return offsetof(struct monst,nmon);case 1:return offsetof(struct monst,data);case 2:return offsetof(struct monst,minvent);case 3:return offsetof(struct monst,mw);case 4:return offsetof(struct monst,mextra);}break;case 2:return offsetof(struct trap,ntrap);case 3:return offsetof(struct stairway,next);}abort();}
int probe_constant(int i){switch(i){case 0:return ALTAR;case 1:return DOOR;case 2:return FILL_NORMAL;case 3:return HWALL;case 4:return MOAT;case 5:return OROOM;case 6:return POOL;case 7:return ROOM;case 8:return SDOOR;case 9:return STONE;case 10:return TELEP_TRAP;case 11:return WATER;case 12:return all_themes;case 13:return most_themes;case 14:return tut_themes;default:abort();}}
int probe_alloc_kind(int i){return allocationkinds[i];}
