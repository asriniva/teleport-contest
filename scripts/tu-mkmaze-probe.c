/* Controlled-world original C / JS differential fixture, not a game. */
#include "hack.h"
#include "sp_lev.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <setjmp.h>
__typeof__(svl) svl;
__typeof__(iflags) iflags;
__typeof__(gb) gb;
__typeof__(gx) gx;
__typeof__(gy) gy;
__typeof__(sve) sve;
__typeof__(svn) svn;
__typeof__(u) u;
__typeof__(gl) gl;
__typeof__(svd) svd;
__typeof__(gn) gn;
__typeof__(svu) svu;
__typeof__(svr) svr;
__typeof__(mons) mons;
__typeof__(gu) gu;
__typeof__(gr) gr;
__typeof__(objects) objects;
__typeof__(svi) svi;
__typeof__(flags) flags;
__typeof__(gi) gi;
__typeof__(gw) gw;
__typeof__(uball) uball;
__typeof__(svb) svb;
__typeof__(ge) ge;
__typeof__(svx) svx;
__typeof__(svy) svy;
__typeof__(gv) gv;
__typeof__(program_state) program_state;
__typeof__(gf) gf;

static int64_t quantitybase=1;static char tracebuf[1048576];static size_t traceused;static uint32_t seed=1;static int draws,enabled=1,callerline,options[128],errorcode;
static const char *callerfile,*callerfn;static void*levelout;static jmp_buf panicframe;
static struct obj opool[512];static struct monst mpool[256];static struct trap tpool[128];static int no,nm,nt;
static void*allocations[1024];static size_t allocsizes[1024];static int nalloc;
static unsigned char serial[65536];static int seriallen,serialpos;
static char literal[256],gangbuf[256];static coord ccoord;static d_level dlev;static NHFILE test_nhfile;static NhRegion gasregion;static s_level speciallevel;static struct exclusion_zone test_exclusion;_Alignas(16) static unsigned char scratch[4096];
static void logfmt(const char*f,...){va_list ap;va_start(ap,f);int n=vsnprintf(tracebuf+traceused,sizeof(tracebuf)-traceused,f,ap);va_end(ap);if(n>0)traceused+=(size_t)n;if(traceused>=sizeof(tracebuf))abort();}
static void ptrlog(const void*p){if(levelout&&(uintptr_t)p>=(uintptr_t)levelout&&(uintptr_t)p<(uintptr_t)levelout+sizeof(d_level)){logfmt("get_level-output+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)levelout));return;}if(!p){logfmt("0");return;}

if((uintptr_t)p>=(uintptr_t)&svl&&(uintptr_t)p<(uintptr_t)&svl+sizeof svl){logfmt("G0+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&svl));return;}
if((uintptr_t)p>=(uintptr_t)&iflags&&(uintptr_t)p<(uintptr_t)&iflags+sizeof iflags){logfmt("G1+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&iflags));return;}
if((uintptr_t)p>=(uintptr_t)&gb&&(uintptr_t)p<(uintptr_t)&gb+sizeof gb){logfmt("G2+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gb));return;}
if((uintptr_t)p>=(uintptr_t)&gx&&(uintptr_t)p<(uintptr_t)&gx+sizeof gx){logfmt("G3+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gx));return;}
if((uintptr_t)p>=(uintptr_t)&gy&&(uintptr_t)p<(uintptr_t)&gy+sizeof gy){logfmt("G4+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gy));return;}
if((uintptr_t)p>=(uintptr_t)&sve&&(uintptr_t)p<(uintptr_t)&sve+sizeof sve){logfmt("G5+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&sve));return;}
if((uintptr_t)p>=(uintptr_t)&svn&&(uintptr_t)p<(uintptr_t)&svn+sizeof svn){logfmt("G6+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&svn));return;}
if((uintptr_t)p>=(uintptr_t)&u&&(uintptr_t)p<(uintptr_t)&u+sizeof u){logfmt("G7+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&u));return;}
if((uintptr_t)p>=(uintptr_t)&gl&&(uintptr_t)p<(uintptr_t)&gl+sizeof gl){logfmt("G8+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gl));return;}
if((uintptr_t)p>=(uintptr_t)&svd&&(uintptr_t)p<(uintptr_t)&svd+sizeof svd){logfmt("G9+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&svd));return;}
if((uintptr_t)p>=(uintptr_t)&gn&&(uintptr_t)p<(uintptr_t)&gn+sizeof gn){logfmt("G10+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gn));return;}
if((uintptr_t)p>=(uintptr_t)&svu&&(uintptr_t)p<(uintptr_t)&svu+sizeof svu){logfmt("G11+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&svu));return;}
if((uintptr_t)p>=(uintptr_t)&svr&&(uintptr_t)p<(uintptr_t)&svr+sizeof svr){logfmt("G12+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&svr));return;}
if((uintptr_t)p>=(uintptr_t)&mons&&(uintptr_t)p<(uintptr_t)&mons+sizeof mons){logfmt("G13+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&mons));return;}
if((uintptr_t)p>=(uintptr_t)&gu&&(uintptr_t)p<(uintptr_t)&gu+sizeof gu){logfmt("G14+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gu));return;}
if((uintptr_t)p>=(uintptr_t)&gr&&(uintptr_t)p<(uintptr_t)&gr+sizeof gr){logfmt("G15+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gr));return;}
if((uintptr_t)p>=(uintptr_t)&objects&&(uintptr_t)p<(uintptr_t)&objects+sizeof objects){logfmt("G16+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&objects));return;}
if((uintptr_t)p>=(uintptr_t)&svi&&(uintptr_t)p<(uintptr_t)&svi+sizeof svi){logfmt("G17+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&svi));return;}
if((uintptr_t)p>=(uintptr_t)&flags&&(uintptr_t)p<(uintptr_t)&flags+sizeof flags){logfmt("G18+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&flags));return;}
if((uintptr_t)p>=(uintptr_t)&gi&&(uintptr_t)p<(uintptr_t)&gi+sizeof gi){logfmt("G19+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gi));return;}
if((uintptr_t)p>=(uintptr_t)&gw&&(uintptr_t)p<(uintptr_t)&gw+sizeof gw){logfmt("G20+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gw));return;}
if((uintptr_t)p>=(uintptr_t)&uball&&(uintptr_t)p<(uintptr_t)&uball+sizeof uball){logfmt("G21+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&uball));return;}
if((uintptr_t)p>=(uintptr_t)&svb&&(uintptr_t)p<(uintptr_t)&svb+sizeof svb){logfmt("G22+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&svb));return;}
if((uintptr_t)p>=(uintptr_t)&ge&&(uintptr_t)p<(uintptr_t)&ge+sizeof ge){logfmt("G23+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&ge));return;}
if((uintptr_t)p>=(uintptr_t)&svx&&(uintptr_t)p<(uintptr_t)&svx+sizeof svx){logfmt("G24+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&svx));return;}
if((uintptr_t)p>=(uintptr_t)&svy&&(uintptr_t)p<(uintptr_t)&svy+sizeof svy){logfmt("G25+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&svy));return;}
if((uintptr_t)p>=(uintptr_t)&gv&&(uintptr_t)p<(uintptr_t)&gv+sizeof gv){logfmt("G26+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gv));return;}
if((uintptr_t)p>=(uintptr_t)&program_state&&(uintptr_t)p<(uintptr_t)&program_state+sizeof program_state){logfmt("G27+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&program_state));return;}
if((uintptr_t)p>=(uintptr_t)&gf&&(uintptr_t)p<(uintptr_t)&gf+sizeof gf){logfmt("G28+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gf));return;}
if((uintptr_t)p>=(uintptr_t)&opool&&(uintptr_t)p<(uintptr_t)&opool+sizeof opool){logfmt("opool+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&opool));return;}
if((uintptr_t)p>=(uintptr_t)&mpool&&(uintptr_t)p<(uintptr_t)&mpool+sizeof mpool){logfmt("mpool+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&mpool));return;}
if((uintptr_t)p>=(uintptr_t)&tpool&&(uintptr_t)p<(uintptr_t)&tpool+sizeof tpool){logfmt("tpool+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&tpool));return;}
if((uintptr_t)p>=(uintptr_t)&literal&&(uintptr_t)p<(uintptr_t)&literal+sizeof literal){logfmt("literal+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&literal));return;}
if((uintptr_t)p>=(uintptr_t)&gangbuf&&(uintptr_t)p<(uintptr_t)&gangbuf+sizeof gangbuf){logfmt("gangbuf+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gangbuf));return;}
if((uintptr_t)p>=(uintptr_t)&ccoord&&(uintptr_t)p<(uintptr_t)&ccoord+sizeof ccoord){logfmt("ccoord+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&ccoord));return;}
if((uintptr_t)p>=(uintptr_t)&dlev&&(uintptr_t)p<(uintptr_t)&dlev+sizeof dlev){logfmt("dlev+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&dlev));return;}
if((uintptr_t)p>=(uintptr_t)&serial&&(uintptr_t)p<(uintptr_t)&serial+sizeof serial){logfmt("serial+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&serial));return;}
if((uintptr_t)p>=(uintptr_t)&test_nhfile&&(uintptr_t)p<(uintptr_t)&test_nhfile+sizeof test_nhfile){logfmt("test_nhfile+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&test_nhfile));return;}
if((uintptr_t)p>=(uintptr_t)&gasregion&&(uintptr_t)p<(uintptr_t)&gasregion+sizeof gasregion){logfmt("gasregion+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gasregion));return;}
if((uintptr_t)p>=(uintptr_t)&test_exclusion&&(uintptr_t)p<(uintptr_t)&test_exclusion+sizeof test_exclusion){logfmt("test_exclusion+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&test_exclusion));return;}
if((uintptr_t)p>=(uintptr_t)&scratch&&(uintptr_t)p<(uintptr_t)&scratch+sizeof scratch){logfmt("scratch+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&scratch));return;}
for(int i=0;i<nalloc;i++)if(allocations[i]&&(uintptr_t)p>=(uintptr_t)allocations[i]&&(uintptr_t)p<(uintptr_t)allocations[i]+allocsizes[i]){logfmt("A%d+%llu",i,(unsigned long long)((uintptr_t)p-(uintptr_t)allocations[i]));return;}logfmt("UNKNOWN:%llu",(unsigned long long)(uintptr_t)p);}

static void*newallocation(size_t size){if(nalloc==1024)abort();void*p=calloc(1,size);allocations[nalloc]=p;allocsizes[nalloc++]=size;return p;}
void __real_free(void*);void __wrap_free(void*p){logfmt("free(");ptrlog(p);logfmt(")\n");for(int i=0;i<nalloc;i++)if(allocations[i]==p)allocations[i]=0;__real_free(p);}
static void serialwrite(const void*p,size_t n){if(seriallen+n>sizeof serial)abort();memcpy(serial+seriallen,p,n);seriallen+=(int)n;}
static void serialread(void*p,size_t n){if(serialpos+n>seriallen)abort();memcpy(p,serial+serialpos,n);serialpos+=(int)n;}
static int roll(const char*name,int bound){if(bound<=0){logfmt("BADRNG %d\n",bound);longjmp(panicframe,2);}seed=seed*1664525U+1013904223U;int val=(int)(seed%(unsigned)bound);draws++;logfmt("%s[%s:%d:%s](%d)=%d\n",name,callerfile?callerfile:"",callerline,callerfn?callerfn:"",bound,val);return val;}
static struct obj*fixture_newobj(int typ){if(no==512)abort();struct obj*o=&opool[no++];memset(o,0,sizeof *o);o->otyp=typ;o->oclass=objects[typ].oc_class;o->quan=quantitybase;o->owt=1;o->where=OBJ_FREE;return o;}
static struct monst*newmon(struct permonst*p,int x,int y){if(nm==256)abort();struct monst*m=&mpool[nm++];memset(m,0,sizeof *m);m->data=p?p:&mons[PM_ORC];m->mx=x;m->my=y;m->mhp=m->mhpmax=10;m->nmon=svl.level.monlist;svl.level.monlist=m;if(isok(x,y))svl.level.monsters[x][y]=m;return m;}

int (isok)(coordxy a0,coordxy a1){return a0>=1&&a0<COLNO&&a1>=0&&a1<ROWNO;}
boolean is_ice(coordxy a0,coordxy a1){logfmt("is_ice(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return isok(a0,a1)&&levl[a0][a1].typ==ICE;}
void obj_ice_effects(coordxy a0,coordxy a1,boolean a2){logfmt("obj_ice_effects(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");}
void spot_stop_timers(coordxy a0,coordxy a1,short a2){logfmt("spot_stop_timers(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");}
void count_level_features(void){logfmt("count_level_features(");logfmt(")\n");}
boolean (rng_log_enabled)(void){return enabled;}
void (rng_log_set_caller)(const char * a0,int a1,const char * a2){callerfile=a0;callerline=a1;callerfn=a2;}
int (rn2)(int a0){return roll("rn2",a0);}
boolean occupied(coordxy a0,coordxy a1){logfmt("occupied(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return isok(a0,a1)&&(svl.level.monsters[a0][a1]!=0||levl[a0][a1].typ==STAIRS);}
branch * Is_branchlev(d_level * a0){logfmt("Is_branchlev(");ptrlog(a0);logfmt(")\n");return 0;}
void place_branch(branch * a0,coordxy a1,coordxy a2){logfmt("place_branch(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");}
struct trap * t_at(coordxy a0,coordxy a1){logfmt("t_at(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");for(int i=0;i<nt;i++)if(tpool[i].tx==a0&&tpool[i].ty==a1&&tpool[i].ttyp)return &tpool[i];return 0;}
void deltrap(struct trap * a0){logfmt("deltrap(");ptrlog(a0);logfmt(")\n");a0->ttyp=0;}
boolean rloc(struct monst * a0,unsigned int a1){logfmt("rloc(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return options[7];}
void m_into_limbo(struct monst * a0){logfmt("m_into_limbo(");ptrlog(a0);logfmt(")\n");}
void u_on_newpos(coordxy a0,coordxy a1){logfmt("u_on_newpos(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");u.ux=a0;u.uy=a1;}
void mkstairs(coordxy a0,coordxy a1,char a2,struct mkroom * a3,boolean a4){logfmt("mkstairs(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");ptrlog(a3);logfmt(",");logfmt("%llu",(unsigned long long)a4);logfmt(")\n");levl[a0][a1].typ=STAIRS;}
boolean on_level(d_level * a0,d_level * a1){logfmt("on_level(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");return a0->dnum==a1->dnum&&a0->dlevel==a1->dlevel;}
s_level * find_level(const char * a0){logfmt("find_level(");logfmt("%s",a0?a0:"<null>");logfmt(")\n");return 0;}
int (rnd)(int a0){return roll("rnd",a0)+1;}
int somex(struct mkroom * a0){logfmt("somex(");ptrlog(a0);logfmt(")\n");return a0->lx;}
int somey(struct mkroom * a0){logfmt("somey(");ptrlog(a0);logfmt(")\n");return a0->ly;}
boolean goodpos(coordxy a0,coordxy a1,struct monst * a2,mmflags_nht a3){logfmt("goodpos(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");ptrlog(a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(")\n");return 1;}
struct obj * mk_tt_object(int a0,coordxy a1,coordxy a2){logfmt("mk_tt_object(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");return fixture_newobj(a0);}
boolean poly_when_stoned(struct permonst * a0){logfmt("poly_when_stoned(");ptrlog(a0);logfmt(")\n");return 0;}
int rndmonnum(void){logfmt("rndmonnum(");logfmt(")\n");return PM_HUMAN;}
void set_corpsenm(struct obj * a0,int a1){logfmt("set_corpsenm(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");a0->corpsenm=a1;}
struct obj * mkcorpstat(int a0,struct monst * a1,struct permonst * a2,coordxy a3,coordxy a4,unsigned int a5){logfmt("mkcorpstat(");logfmt("%llu",(unsigned long long)a0);logfmt(",");ptrlog(a1);logfmt(",");ptrlog(a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(",");logfmt("%llu",(unsigned long long)a4);logfmt(",");logfmt("%llu",(unsigned long long)a5);logfmt(")\n");return fixture_newobj(a0);}
boolean In_quest(d_level * a0){logfmt("In_quest(");ptrlog(a0);logfmt(")\n");return options[1];}
s_level * Is_special(d_level * a0){logfmt("Is_special(");ptrlog(a0);logfmt(")\n");return options[5]?&speciallevel:0;}
schar depth(d_level * a0){logfmt("depth(");ptrlog(a0);logfmt(")\n");return (schar)a0->dlevel;}
xint16 dunlevs_in_dungeon(d_level * a0){logfmt("dunlevs_in_dungeon(");ptrlog(a0);logfmt(")\n");return options[0]?options[0]:12;}
void get_level(d_level * a0,int a1){logfmt("get_level(");logfmt("OUT:d_level+0");logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");levelout=a0;a0->dnum=u.uz.dnum;a0->dlevel=a1;}
xint16 ledger_no(d_level * a0){logfmt("ledger_no(");ptrlog(a0);logfmt(")\n");return (xint16)(a0->dnum*20+a0->dlevel);}
void migrate_to_level(struct monst * a0,xint16 a1,xint16 a2,coord * a3){logfmt("migrate_to_level(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");ptrlog(a3);logfmt(")\n");}
struct obj * mksobj(int a0,boolean a1,boolean a2){logfmt("mksobj(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");return options[8]?0:fixture_newobj(a0);}
int weight(struct obj * a0){logfmt("weight(");ptrlog(a0);logfmt(")\n");return(int)(a0->quan*2);}
int add_to_minv(struct monst * a0,struct obj * a1){logfmt("add_to_minv(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");a1->nobj=a0->minvent;a0->minvent=a1;return 0;}
struct obj * mkobj(int a0,boolean a1){logfmt("mkobj(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return fixture_newobj(a0==GEM_CLASS?DIAMOND:FOOD_RATION);}
void dealloc_obj(struct obj * a0){logfmt("dealloc_obj(");ptrlog(a0);logfmt(")\n");}
int shiny_obj(char a0){logfmt("shiny_obj(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");return RIN_PROTECTION;}
struct obj * mksobj_migr_to_species(int a0,unsigned int a1,boolean a2,boolean a3){logfmt("mksobj_migr_to_species(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(")\n");return fixture_newobj(a0);}
unsigned int Strlen_(const char * a0,const char * a1,int a2){logfmt("Strlen_(");logfmt("%s",a0?a0:"<null>");logfmt(",");logfmt("%s",a1?a1:"<null>");logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");return(unsigned)strlen(a0);}
void new_oname(struct obj * a0,int a1){logfmt("new_oname(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");if(!a0->oextra)a0->oextra=newallocation(sizeof *a0->oextra);a0->oextra->oname=newallocation(a1);}
int fruitadd(char * a0,struct fruit * a1){logfmt("fruitadd(");logfmt("%s",a0?a0:"<null>");logfmt(",");ptrlog(a1);logfmt(")\n");return 7;}
char * rndorcname(char * a0){logfmt("rndorcname(");logfmt("OUT:char[256]+0");logfmt(")\n");strcpy(a0,"test gang");return a0;}
struct monst * makemon(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){logfmt("makemon(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(")\n");return options[9]?0:newmon(a0,a1,a2);}
char * upstart(char * a0){logfmt("upstart(");logfmt("%s",a0?a0:"<null>");logfmt(")\n");if(*a0>='a'&&*a0<='z')*a0-=32;return a0;}
struct monst * christen_monst(struct monst * a0,const char * a1){logfmt("christen_monst(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"<null>");logfmt(")\n");return a0;}
void set_malign(struct monst * a0){logfmt("set_malign(");ptrlog(a0);logfmt(")\n");}
struct monst * christen_orc(struct monst * a0,const char * a1,const char * a2){logfmt("christen_orc(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"<null>");logfmt(",");logfmt("%s",a2?a2:"<null>");logfmt(")\n");return a0;}
boolean debugcore(const char * a0,boolean a1){logfmt("debugcore(");logfmt("%s",a0?a0:"<null>");logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return options[4];}
stairway * stairway_find_dir(boolean a0){logfmt("stairway_find_dir(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");return 0;}
int distmin(coordxy a0,coordxy a1,coordxy a2,coordxy a3){logfmt("distmin(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(")\n");int dx=abs(a0-a2),dy=abs(a1-a3);return dx>dy?dx:dy;}
struct obj * mkobj_at(char a0,coordxy a1,coordxy a2,boolean a3){logfmt("mkobj_at(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(")\n");struct obj*o=fixture_newobj(a0==GEM_CLASS?DIAMOND:FOOD_RATION);o->ox=a1;o->oy=a2;return o;}
struct obj * mksobj_at(int a0,coordxy a1,coordxy a2,boolean a3,boolean a4){logfmt("mksobj_at(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(",");logfmt("%llu",(unsigned long long)a4);logfmt(")\n");struct obj*o=fixture_newobj(a0);o->ox=a1;o->oy=a2;return o;}
struct obj * mkgold(long a0,coordxy a1,coordxy a2){logfmt("mkgold(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");struct obj*o=fixture_newobj(GOLD_PIECE);o->quan=a0;o->ox=a1;o->oy=a2;return o;}
void mktrap(int a0,unsigned int a1,struct mkroom * a2,coord * a3){logfmt("mktrap(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");ptrlog(a2);logfmt(",");ptrlog(a3);logfmt(")\n");}
xint16 dunlev(d_level * a0){logfmt("dunlev(");ptrlog(a0);logfmt(")\n");return a0->dlevel;}
boolean load_special(const char * a0){logfmt("load_special(");logfmt("%s",a0?a0:"<null>");logfmt(")\n");return options[6];}
void dmonsfree(void){logfmt("dmonsfree(");logfmt(")\n");}
boolean Invocation_lev(d_level * a0){logfmt("Invocation_lev(");ptrlog(a0);logfmt(")\n");return options[3];}
struct trap * maketrap(coordxy a0,coordxy a1,int a2){logfmt("maketrap(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");if(nt==128)abort();struct trap*t=&tpool[nt++];memset(t,0,sizeof *t);t->tx=a0;t->ty=a1;t->ttyp=a2;t->ntrap=gf.ftrap;gf.ftrap=t;return t;}
NhRegion * create_gas_cloud(coordxy a0,coordxy a1,int a2,int a3){logfmt("create_gas_cloud(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(")\n");return &gasregion;}
int dist2(coordxy a0,coordxy a1,coordxy a2,coordxy a3){logfmt("dist2(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(")\n");return(a0-a2)*(a0-a2)+(a1-a3)*(a1-a3);}
void vision_recalc(int a0){logfmt("vision_recalc(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");}
int unplacebc_and_covet_placebc(void){logfmt("unplacebc_and_covet_placebc(");logfmt(")\n");return 0;}
void remove_object(struct obj * a0){logfmt("remove_object(");ptrlog(a0);logfmt(")\n");if(isok(a0->ox,a0->oy)&&svl.level.objects[a0->ox][a0->oy]==a0)svl.level.objects[a0->ox][a0->oy]=a0->nexthere;}
long * alloc(unsigned int a0){logfmt("alloc(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");return (long*)newallocation(a0);}
void remove_worm(struct monst * a0){logfmt("remove_worm(");ptrlog(a0);logfmt(")\n");}
void newsym(coordxy a0,coordxy a1){logfmt("newsym(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");}
void block_point(int a0,int a1){logfmt("block_point(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");}
void recalc_block_point(coordxy a0,coordxy a1){logfmt("recalc_block_point(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");}
void lift_covet_and_placebc(int a0){logfmt("lift_covet_and_placebc(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");}
boolean is_pool(coordxy a0,coordxy a1){logfmt("is_pool(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return isok(a0,a1)&&(levl[a0][a1].typ==POOL||levl[a0][a1].typ==WATER);}
void sfo_int(NHFILE * a0,int * a1,const char * a2){logfmt("sfo_int(");ptrlog(a0);logfmt(",");logfmt("INT:%d",*a1);logfmt(",");logfmt("%s",a2?a2:"<null>");logfmt(")\n");serialwrite(a1,sizeof *a1);}
void sfo_bubble(NHFILE * a0,struct bubble * a1,const char * a2){logfmt("sfo_bubble(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(",");logfmt("%s",a2?a2:"<null>");logfmt(")\n");serialwrite(&a1->x,12);}
void sfi_int(NHFILE * a0,int * a1,const char * a2){logfmt("sfi_int(");ptrlog(a0);logfmt(",");logfmt("OUT:int+0");logfmt(",");logfmt("%s",a2?a2:"<null>");logfmt(")\n");serialread(a1,sizeof *a1);}
void sfi_bubble(NHFILE * a0,struct bubble * a1,const char * a2){logfmt("sfi_bubble(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(",");logfmt("%s",a2?a2:"<null>");logfmt(")\n");serialread(&a1->x,12);}
boolean In_mines(d_level * a0){logfmt("In_mines(");ptrlog(a0);logfmt(")\n");return u.uz.dnum==svd.dungeon_topology.d_mines_dnum;}
boolean In_hell(d_level * a0){logfmt("In_hell(");ptrlog(a0);logfmt(")\n");return options[2];}
int sgn(int a0){logfmt("sgn(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");return(a0>0)-(a0<0);}
void unblock_point(int a0,int a1){logfmt("unblock_point(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");}
void place_object(struct obj * a0,coordxy a1,coordxy a2){logfmt("place_object(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");a0->ox=a1;a0->oy=a2;a0->nexthere=svl.level.objects[a1][a2];svl.level.objects[a1][a2]=a0;}
void stackobj(struct obj * a0){logfmt("stackobj(");ptrlog(a0);logfmt(")\n");}
int mnearto(struct monst * a0,coordxy a1,coordxy a2,boolean a3,unsigned int a4){logfmt("mnearto(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(",");logfmt("%llu",(unsigned long long)a4);logfmt(")\n");a0->mx=a1;a0->my=a2;if(isok(a1,a2))svl.level.monsters[a1][a2]=a0;return !options[10];}
void elemental_clog(struct monst * a0){logfmt("elemental_clog(");ptrlog(a0);logfmt(")\n");}
void mnexto(struct monst * a0,unsigned int a1){logfmt("mnexto(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");a0->mx=u.ux+1;a0->my=u.uy;}
void panic(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[2048];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("panic:%s\n",b);longjmp(panicframe,1);}
void impossible(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[2048];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("impossible:%s\n",b);}
void pline(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[2048];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("pline:%s\n",b);}
void Norep(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[2048];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("Norep:%s\n",b);}
void nh_snprintf(const char*f,int line,char*b,size_t n,const char*fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(b,n,fmt,ap);va_end(ap);logfmt("nh_snprintf[%s:%d]:%s\n",f,line,b);}
#ifdef HYBRID_MKMAZE
extern int teleport_mkmaze_iswall(coordxy a0,coordxy a1);
extern int teleport_mkmaze_iswall_or_stone(coordxy a0,coordxy a1);
extern boolean teleport_mkmaze_is_solid(coordxy a0,coordxy a1);
extern boolean set_levltyp(coordxy a0,coordxy a1,schar a2);
extern boolean set_levltyp_lit(coordxy a0,coordxy a1,schar a2,schar a3);
extern int teleport_mkmaze_extend_spine(int (*a0)[3],int a1,int a2,int a3);
extern void teleport_mkmaze_wall_cleanup(coordxy a0,coordxy a1,coordxy a2,coordxy a3);
extern void fix_wall_spines(coordxy a0,coordxy a1,coordxy a2,coordxy a3);
extern void wallification(coordxy a0,coordxy a1,coordxy a2,coordxy a3);
extern boolean teleport_mkmaze_okay(coordxy a0,coordxy a1,coordxy a2);
extern void teleport_mkmaze_maze0xy(coord * a0);
extern boolean is_exclusion_zone(xint16 a0,coordxy a1,coordxy a2);
extern boolean bad_location(coordxy a0,coordxy a1,coordxy a2,coordxy a3,coordxy a4,coordxy a5);
extern void place_lregion(coordxy a0,coordxy a1,coordxy a2,coordxy a3,coordxy a4,coordxy a5,coordxy a6,coordxy a7,xint16 a8,d_level * a9);
extern boolean teleport_mkmaze_put_lregion_here(coordxy a0,coordxy a1,coordxy a2,coordxy a3,coordxy a4,coordxy a5,xint16 a6,boolean a7,d_level * a8);
extern void teleport_mkmaze_baalz_fixup();
extern void fixup_special();
extern void teleport_mkmaze_check_ransacked(const char * a0);
extern void teleport_mkmaze_migrate_orc(struct monst * a0,unsigned long a1);
extern void teleport_mkmaze_shiny_orc_stuff(struct monst * a0);
extern void teleport_mkmaze_migr_booty_item(int a0,const char * a1);
extern void teleport_mkmaze_stolen_booty();
extern boolean teleport_mkmaze_maze_inbounds(coordxy a0,coordxy a1);
extern void teleport_mkmaze_maze_remove_deadends(xint16 a0);
extern void create_maze(int a0,int a1,boolean a2);
extern void pick_vibrasquare_location();
extern void teleport_mkmaze_populate_maze();
extern void makemaz(const char * a0);
extern void walkfrom(coordxy a0,coordxy a1,schar a2);
extern void mazexy(coord * a0);
extern void get_level_extends(coordxy * a0,coordxy * a1,coordxy * a2,coordxy * a3);
extern void bound_digging();
extern void mkportal(coordxy a0,coordxy a1,xint16 a2,xint16 a3);
extern void fumaroles();
extern void movebubbles();
extern void water_friction();
extern void save_waterlevel(NHFILE * a0);
extern void restore_waterlevel(NHFILE * a0);
extern void teleport_mkmaze_set_wportal();
extern void teleport_mkmaze_setup_waterlevel();
extern void teleport_mkmaze_unsetup_waterlevel();
extern void teleport_mkmaze_mk_bubble(coordxy a0,coordxy a1,int a2);
extern void maybe_adjust_hero_bubble();
extern void teleport_mkmaze_mv_bubble(struct bubble * a0,coordxy a1,coordxy a2,boolean a3);
#else
#define teleport_mkmaze_iswall iswall
#define teleport_mkmaze_iswall_or_stone iswall_or_stone
#define teleport_mkmaze_is_solid is_solid
#define teleport_mkmaze_extend_spine extend_spine
#define teleport_mkmaze_wall_cleanup wall_cleanup
#define teleport_mkmaze_okay okay
#define teleport_mkmaze_maze0xy maze0xy
#define teleport_mkmaze_put_lregion_here put_lregion_here
#define teleport_mkmaze_baalz_fixup baalz_fixup
#define teleport_mkmaze_check_ransacked check_ransacked
#define teleport_mkmaze_migrate_orc migrate_orc
#define teleport_mkmaze_shiny_orc_stuff shiny_orc_stuff
#define teleport_mkmaze_migr_booty_item migr_booty_item
#define teleport_mkmaze_stolen_booty stolen_booty
#define teleport_mkmaze_maze_inbounds maze_inbounds
#define teleport_mkmaze_maze_remove_deadends maze_remove_deadends
#define teleport_mkmaze_populate_maze populate_maze
#define teleport_mkmaze_set_wportal set_wportal
#define teleport_mkmaze_setup_waterlevel setup_waterlevel
#define teleport_mkmaze_unsetup_waterlevel unsetup_waterlevel
#define teleport_mkmaze_mk_bubble mk_bubble
#define teleport_mkmaze_mv_bubble mv_bubble
#include "/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/wasm64-build/tree/src/mkmaze.c"
#endif
int64_t probe_action(int i,int64_t a0,int64_t a1,int64_t a2,int64_t a3,int64_t a4,int64_t a5,int64_t a6,int64_t a7,int64_t a8,int64_t a9){levelout=0;errorcode=0;int jump=setjmp(panicframe);if(jump){errorcode=jump;return -999;}switch(i){
case 0:return(int64_t)teleport_mkmaze_iswall((coordxy)a0,(coordxy)a1);
case 1:return(int64_t)teleport_mkmaze_iswall_or_stone((coordxy)a0,(coordxy)a1);
case 2:return(int64_t)teleport_mkmaze_is_solid((coordxy)a0,(coordxy)a1);
case 3:return(int64_t)set_levltyp((coordxy)a0,(coordxy)a1,(schar)a2);
case 4:return(int64_t)set_levltyp_lit((coordxy)a0,(coordxy)a1,(schar)a2,(schar)a3);
case 5:return(int64_t)teleport_mkmaze_extend_spine((int (*)[3])a0,(int)a1,(int)a2,(int)a3);
case 6:teleport_mkmaze_wall_cleanup((coordxy)a0,(coordxy)a1,(coordxy)a2,(coordxy)a3);return 0;
case 7:fix_wall_spines((coordxy)a0,(coordxy)a1,(coordxy)a2,(coordxy)a3);return 0;
case 8:wallification((coordxy)a0,(coordxy)a1,(coordxy)a2,(coordxy)a3);return 0;
case 9:return(int64_t)teleport_mkmaze_okay((coordxy)a0,(coordxy)a1,(coordxy)a2);
case 10:teleport_mkmaze_maze0xy((coord *)a0);return 0;
case 11:return(int64_t)is_exclusion_zone((xint16)a0,(coordxy)a1,(coordxy)a2);
case 12:return(int64_t)bad_location((coordxy)a0,(coordxy)a1,(coordxy)a2,(coordxy)a3,(coordxy)a4,(coordxy)a5);
case 13:place_lregion((coordxy)a0,(coordxy)a1,(coordxy)a2,(coordxy)a3,(coordxy)a4,(coordxy)a5,(coordxy)a6,(coordxy)a7,(xint16)a8,(d_level *)a9);return 0;
case 14:return(int64_t)teleport_mkmaze_put_lregion_here((coordxy)a0,(coordxy)a1,(coordxy)a2,(coordxy)a3,(coordxy)a4,(coordxy)a5,(xint16)a6,(boolean)a7,(d_level *)a8);
case 15:teleport_mkmaze_baalz_fixup();return 0;
case 16:fixup_special();return 0;
case 17:teleport_mkmaze_check_ransacked((const char *)a0);return 0;
case 18:teleport_mkmaze_migrate_orc((struct monst *)a0,(unsigned long)a1);return 0;
case 19:teleport_mkmaze_shiny_orc_stuff((struct monst *)a0);return 0;
case 20:teleport_mkmaze_migr_booty_item((int)a0,(const char *)a1);return 0;
case 21:teleport_mkmaze_stolen_booty();return 0;
case 22:return(int64_t)teleport_mkmaze_maze_inbounds((coordxy)a0,(coordxy)a1);
case 23:teleport_mkmaze_maze_remove_deadends((xint16)a0);return 0;
case 24:create_maze((int)a0,(int)a1,(boolean)a2);return 0;
case 25:pick_vibrasquare_location();return 0;
case 26:teleport_mkmaze_populate_maze();return 0;
case 27:makemaz((const char *)a0);return 0;
case 28:walkfrom((coordxy)a0,(coordxy)a1,(schar)a2);return 0;
case 29:mazexy((coord *)a0);return 0;
case 30:get_level_extends((coordxy *)a0,(coordxy *)a1,(coordxy *)a2,(coordxy *)a3);return 0;
case 31:bound_digging();return 0;
case 32:mkportal((coordxy)a0,(coordxy)a1,(xint16)a2,(xint16)a3);return 0;
case 33:fumaroles();return 0;
case 34:movebubbles();return 0;
case 35:water_friction();return 0;
case 36:save_waterlevel((NHFILE *)a0);return 0;
case 37:restore_waterlevel((NHFILE *)a0);return 0;
case 38:teleport_mkmaze_set_wportal();return 0;
case 39:teleport_mkmaze_setup_waterlevel();return 0;
case 40:teleport_mkmaze_unsetup_waterlevel();return 0;
case 41:teleport_mkmaze_mk_bubble((coordxy)a0,(coordxy)a1,(int)a2);return 0;
case 42:maybe_adjust_hero_bubble();return 0;
case 43:teleport_mkmaze_mv_bubble((struct bubble *)a0,(coordxy)a1,(coordxy)a2,(boolean)a3);return 0;
default:abort();}}
const char*probe_trace(void){return tracebuf;}void probe_clear(void){traceused=0;tracebuf[0]=0;}
int probe_draws(void){return draws;}int probe_error(void){return errorcode;}uintptr_t probe_stack(void){return(uintptr_t)__builtin_frame_address(0);}
void probe_seed(uint32_t n){seed=n;draws=0;}void probe_option(int i,int v){options[i]=v;}
void*probe_pointer(int i){switch(i){case 0:return &ccoord;case 1:return &dlev;case 2:return literal;case 3:return gangbuf;case 4:return &opool[0];case 5:return &mpool[0];case 6:return &tpool[0];case 7:return serial;case 8:return &test_exclusion;case 9:return &test_nhfile;case 10:return &gasregion;case 11:return scratch;default:return 0;}}
void probe_text(const char*s){strcpy(literal,s);}void probe_coord(int x,int y){ccoord.x=x;ccoord.y=y;}
void probe_map(int x,int y,int typ,int bits){memset(&levl[x][y],0,sizeof levl[x][y]);levl[x][y].typ=typ;levl[x][y].lit=bits&1;levl[x][y].horizontal=(bits>>1)&1;levl[x][y].flags=(bits>>2)&31;}
void*probe_grid(void){return levl;}int probe_serial_length(void){return seriallen;}void probe_rewind(void){serialpos=0;}void probe_serial_clear(void){seriallen=serialpos=0;}
void probe_plane(int air){u.uz=air?svd.dungeon_topology.d_air_level:svd.dungeon_topology.d_water_level;}
void probe_hero(int x,int y,int dx,int dy){u.ux=x;u.uy=y;u.dx=dx;u.dy=dy;}
void probe_attach(int what,int x,int y){if(what==1){struct obj*o=fixture_newobj(ROCK);place_object(o,x,y);}else if(what==2)newmon(&mons[PM_ORC],x,y);else if(what==3)maketrap(x,y,MAGIC_PORTAL);else u.ux=x,u.uy=y;}
int probe_count(int what){if(what==0)return no;if(what==1)return nm;if(what==2)return nt;if(what==3)return nalloc;return 0;}
void*probe_alloc_pointer(int i){return allocations[i];}size_t probe_alloc_size(int i){return allocsizes[i];}
void probe_reset(void){
 for(int i=0;i<nalloc;i++)if(allocations[i])__real_free(allocations[i]);nalloc=0;
 memset(options,0,sizeof options);memset(opool,0,sizeof opool);memset(mpool,0,sizeof mpool);memset(tpool,0,sizeof tpool);no=nm=nt=0;
memset(&svl,0,sizeof svl);
memset(&iflags,0,sizeof iflags);
memset(&gb,0,sizeof gb);
memset(&gx,0,sizeof gx);
memset(&gy,0,sizeof gy);
memset(&sve,0,sizeof sve);
memset(&svn,0,sizeof svn);
memset(&u,0,sizeof u);
memset(&gl,0,sizeof gl);
memset(&svd,0,sizeof svd);
memset(&gn,0,sizeof gn);
memset(&svu,0,sizeof svu);
memset(&svr,0,sizeof svr);
memset(&mons,0,sizeof mons);
memset(&gu,0,sizeof gu);
memset(&gr,0,sizeof gr);
memset(&objects,0,sizeof objects);
memset(&svi,0,sizeof svi);
memset(&flags,0,sizeof flags);
memset(&gi,0,sizeof gi);
memset(&gw,0,sizeof gw);
memset(&uball,0,sizeof uball);
memset(&svb,0,sizeof svb);
memset(&ge,0,sizeof ge);
memset(&svx,0,sizeof svx);
memset(&svy,0,sizeof svy);
memset(&gv,0,sizeof gv);
memset(&program_state,0,sizeof program_state);
memset(&gf,0,sizeof gf);

 gx.x_maze_max=COLNO-2;gy.y_maze_max=ROWNO-2;u.ux=40;u.uy=10;u.uz.dlevel=3;
 svd.dungeon_topology.d_water_level.dnum=5;svd.dungeon_topology.d_water_level.dlevel=1;svd.dungeon_topology.d_air_level.dnum=5;svd.dungeon_topology.d_air_level.dlevel=2;svd.dungeon_topology.d_mines_dnum=2;
 for(int i=0;i<NUM_OBJECTS;i++){objects[i].oc_class=FOOD_CLASS;objects[i].oc_prob=1;}
 objects[GOLD_PIECE].oc_class=COIN_CLASS;objects[DIAMOND].oc_class=GEM_CLASS;mons[PM_ORC].mflags2=M2_ORC;mons[PM_ORC_CAPTAIN].mflags2=M2_ORC;
 quantitybase=1;strcpy(literal,"");seed=1;draws=0;callerfile=callerfn=0;callerline=0;errorcode=0;seriallen=serialpos=0;memset(&ccoord,0,sizeof ccoord);memset(&dlev,0,sizeof dlev);probe_clear();}
void*probe_nhfile(int mode){memset(&test_nhfile,0,sizeof test_nhfile);test_nhfile.mode=mode;return &test_nhfile;}

void*probe_scratch(void){return scratch;}
void probe_exclusion(int type,int x1,int y1,int x2,int y2){memset(&test_exclusion,0,sizeof test_exclusion);test_exclusion.zonetype=type;test_exclusion.lx=x1;test_exclusion.ly=y1;test_exclusion.hx=x2;test_exclusion.hy=y2;sve.exclusion_zones=&test_exclusion;}
void probe_region(int type,int x,int y){lev_region*r=newallocation(sizeof *r);r->rtype=type;r->inarea.x1=r->inarea.x2=x;r->inarea.y1=r->inarea.y2=y;r->delarea.x1=r->delarea.x2=0;r->delarea.y1=r->delarea.y2=0;if(type==LR_PORTAL){r->rname.str=newallocation(2);strcpy(r->rname.str,"4");}gl.lregions=r;gn.num_lregions=1;}
void probe_quantity(int64_t n){quantitybase=n;}
size_t probe_pointer_offset(int kind,int which){if(kind==0)return which?offsetof(struct obj,v):offsetof(struct obj,nobj);if(kind==1)return offsetof(struct monst,minvent);abort();}
void probe_special(int count){memset(&speciallevel,0,sizeof speciallevel);speciallevel.rndlevs=count;options[5]=!!count;}
