/* MKOBJ controlled external dependencies; original algorithms execute in C or JS. */
#include "hack.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <emscripten.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
__typeof__(cg) cg={0};
__typeof__(svm) svm;
__typeof__(gi) gi;
__typeof__(objects) objects;
__typeof__(svd) svd;
__typeof__(u) u;
__typeof__(svb) svb;
__typeof__(go) go;
__typeof__(obj_descr) obj_descr;
__typeof__(mons) mons={[PM_HUMAN]={.pmidx=PM_HUMAN,.mlet=S_HUMAN,.mflags2=M2_HUMAN,.mmove=12,.difficulty=10}};
__typeof__(svc) svc;
__typeof__(svl) svl;
__typeof__(flags) flags;
__typeof__(gu) gu;
__typeof__(gz) gz;
__typeof__(iflags) iflags;
__typeof__(gv) gv;
__typeof__(uwep) uwep;
__typeof__(uswapwep) uswapwep;
__typeof__(gm) gm;
__typeof__(gb) gb;
__typeof__(hands_obj) hands_obj;
__typeof__(gt) gt;
__typeof__(gk) gk;
__typeof__(program_state) program_state;
__typeof__(c_common_strings) c_common_strings={.c_nothing_happens="fixture"};
__typeof__(gc) gc;
__typeof__(uchain) uchain;
__typeof__(uball) uball;
__typeof__(genders) genders={{.he="their",.him="their",.his="their"},{.he="their",.him="their",.his="their"},{.he="their",.him="their",.his="their"}};
__typeof__(uskin) uskin;
__typeof__(uarm) uarm;
__typeof__(uarmc) uarmc;
__typeof__(uarmh) uarmh;
__typeof__(uarms) uarms;
__typeof__(uarmg) uarmg;
__typeof__(uarmf) uarmf;
__typeof__(uarmu) uarmu;
__typeof__(uquiver) uquiver;
__typeof__(uamul) uamul;
__typeof__(uleft) uleft;
__typeof__(uright) uright;
__typeof__(ublindf) ublindf;
__typeof__(def_oc_syms) def_oc_syms={{.name="fixture"},{.name="fixture"},{.name="fixture"},{.name="fixture"},{.name="fixture"},{.name="fixture"},{.name="fixture"},{.name="fixture"},{.name="fixture"},{.name="fixture"},{.name="fixture"},{.name="fixture"},{.name="fixture"},{.name="fixture"},{.name="fixture"},{.name="fixture"},{.name="fixture"},{.name="fixture"}};
static struct obj objpool[24];static struct monst monpool[8];static struct oextra extrapool[8];static struct obj*headcells[8];static union any anycells[8];static _Alignas(void*) char bufferpool[8192];static char tracebuf[262144];static size_t traceused;static int result,rngvalue,query,grow,reentry,pointer_out,replace_named,rng_mutate,depth_calls;static unsigned rngcursor;static jmp_buf escape;static union any timer_arg;static long timer_when;static short timer_func;
struct allocation{void*p;size_t n;int live,kind;void*saved;};static struct allocation blocks[512];static int blockcount;
static void append(const char*fmt,...){va_list ap;va_start(ap,fmt);int n=vsnprintf(tracebuf+traceused,sizeof tracebuf-traceused,fmt,ap);va_end(ap);if(n<0||(size_t)n>=sizeof tracebuf-traceused)abort();traceused+=(size_t)n;}
static uint64_t token(const void*p){uintptr_t a=(uintptr_t)p;if(!p)return 0;
if(a>=(uintptr_t)&objpool&&a<(uintptr_t)&objpool+sizeof objpool)return 100000+a-(uintptr_t)&objpool;
if(a>=(uintptr_t)&monpool&&a<(uintptr_t)&monpool+sizeof monpool)return 200000+a-(uintptr_t)&monpool;
if(a>=(uintptr_t)&bufferpool&&a<(uintptr_t)&bufferpool+sizeof bufferpool)return 300000+a-(uintptr_t)&bufferpool;
if(a>=(uintptr_t)&headcells&&a<(uintptr_t)&headcells+sizeof headcells)return 400000+a-(uintptr_t)&headcells;
if(a>=(uintptr_t)&anycells&&a<(uintptr_t)&anycells+sizeof anycells)return 500000+a-(uintptr_t)&anycells;
if(a>=(uintptr_t)&timer_arg&&a<(uintptr_t)&timer_arg+sizeof timer_arg)return 600000+a-(uintptr_t)&timer_arg;
if(a>=(uintptr_t)&extrapool&&a<(uintptr_t)&extrapool+sizeof extrapool)return 700000+a-(uintptr_t)&extrapool;
if(a>=(uintptr_t)&cg&&a<(uintptr_t)&cg+sizeof cg)return 2000000+a-(uintptr_t)&cg;
if(a>=(uintptr_t)&svm&&a<(uintptr_t)&svm+sizeof svm)return 2100000+a-(uintptr_t)&svm;
if(a>=(uintptr_t)&gi&&a<(uintptr_t)&gi+sizeof gi)return 2200000+a-(uintptr_t)&gi;
if(a>=(uintptr_t)&objects&&a<(uintptr_t)&objects+sizeof objects)return 2300000+a-(uintptr_t)&objects;
if(a>=(uintptr_t)&svd&&a<(uintptr_t)&svd+sizeof svd)return 2400000+a-(uintptr_t)&svd;
if(a>=(uintptr_t)&u&&a<(uintptr_t)&u+sizeof u)return 2500000+a-(uintptr_t)&u;
if(a>=(uintptr_t)&svb&&a<(uintptr_t)&svb+sizeof svb)return 2600000+a-(uintptr_t)&svb;
if(a>=(uintptr_t)&go&&a<(uintptr_t)&go+sizeof go)return 2700000+a-(uintptr_t)&go;
if(a>=(uintptr_t)&obj_descr&&a<(uintptr_t)&obj_descr+sizeof obj_descr)return 2800000+a-(uintptr_t)&obj_descr;
if(a>=(uintptr_t)&mons&&a<(uintptr_t)&mons+sizeof mons)return 2900000+a-(uintptr_t)&mons;
if(a>=(uintptr_t)&svc&&a<(uintptr_t)&svc+sizeof svc)return 3000000+a-(uintptr_t)&svc;
if(a>=(uintptr_t)&svl&&a<(uintptr_t)&svl+sizeof svl)return 3100000+a-(uintptr_t)&svl;
if(a>=(uintptr_t)&flags&&a<(uintptr_t)&flags+sizeof flags)return 3200000+a-(uintptr_t)&flags;
if(a>=(uintptr_t)&gu&&a<(uintptr_t)&gu+sizeof gu)return 3300000+a-(uintptr_t)&gu;
if(a>=(uintptr_t)&gz&&a<(uintptr_t)&gz+sizeof gz)return 3400000+a-(uintptr_t)&gz;
if(a>=(uintptr_t)&iflags&&a<(uintptr_t)&iflags+sizeof iflags)return 3500000+a-(uintptr_t)&iflags;
if(a>=(uintptr_t)&gv&&a<(uintptr_t)&gv+sizeof gv)return 3600000+a-(uintptr_t)&gv;
if(a>=(uintptr_t)&uwep&&a<(uintptr_t)&uwep+sizeof uwep)return 3700000+a-(uintptr_t)&uwep;
if(a>=(uintptr_t)&uswapwep&&a<(uintptr_t)&uswapwep+sizeof uswapwep)return 3800000+a-(uintptr_t)&uswapwep;
if(a>=(uintptr_t)&gm&&a<(uintptr_t)&gm+sizeof gm)return 3900000+a-(uintptr_t)&gm;
if(a>=(uintptr_t)&gb&&a<(uintptr_t)&gb+sizeof gb)return 4000000+a-(uintptr_t)&gb;
if(a>=(uintptr_t)&hands_obj&&a<(uintptr_t)&hands_obj+sizeof hands_obj)return 4100000+a-(uintptr_t)&hands_obj;
if(a>=(uintptr_t)&gt&&a<(uintptr_t)&gt+sizeof gt)return 4200000+a-(uintptr_t)&gt;
if(a>=(uintptr_t)&gk&&a<(uintptr_t)&gk+sizeof gk)return 4300000+a-(uintptr_t)&gk;
if(a>=(uintptr_t)&program_state&&a<(uintptr_t)&program_state+sizeof program_state)return 4400000+a-(uintptr_t)&program_state;
if(a>=(uintptr_t)&c_common_strings&&a<(uintptr_t)&c_common_strings+sizeof c_common_strings)return 4500000+a-(uintptr_t)&c_common_strings;
if(a>=(uintptr_t)&gc&&a<(uintptr_t)&gc+sizeof gc)return 4600000+a-(uintptr_t)&gc;
if(a>=(uintptr_t)&uchain&&a<(uintptr_t)&uchain+sizeof uchain)return 4700000+a-(uintptr_t)&uchain;
if(a>=(uintptr_t)&uball&&a<(uintptr_t)&uball+sizeof uball)return 4800000+a-(uintptr_t)&uball;
if(a>=(uintptr_t)&uskin&&a<(uintptr_t)&uskin+sizeof uskin)return 5000000+a-(uintptr_t)&uskin;
if(a>=(uintptr_t)&uarm&&a<(uintptr_t)&uarm+sizeof uarm)return 5100000+a-(uintptr_t)&uarm;
if(a>=(uintptr_t)&uarmc&&a<(uintptr_t)&uarmc+sizeof uarmc)return 5200000+a-(uintptr_t)&uarmc;
if(a>=(uintptr_t)&uarmh&&a<(uintptr_t)&uarmh+sizeof uarmh)return 5300000+a-(uintptr_t)&uarmh;
if(a>=(uintptr_t)&uarms&&a<(uintptr_t)&uarms+sizeof uarms)return 5400000+a-(uintptr_t)&uarms;
if(a>=(uintptr_t)&uarmg&&a<(uintptr_t)&uarmg+sizeof uarmg)return 5500000+a-(uintptr_t)&uarmg;
if(a>=(uintptr_t)&uarmf&&a<(uintptr_t)&uarmf+sizeof uarmf)return 5600000+a-(uintptr_t)&uarmf;
if(a>=(uintptr_t)&uarmu&&a<(uintptr_t)&uarmu+sizeof uarmu)return 5700000+a-(uintptr_t)&uarmu;
if(a>=(uintptr_t)&uquiver&&a<(uintptr_t)&uquiver+sizeof uquiver)return 5800000+a-(uintptr_t)&uquiver;
if(a>=(uintptr_t)&uamul&&a<(uintptr_t)&uamul+sizeof uamul)return 5900000+a-(uintptr_t)&uamul;
if(a>=(uintptr_t)&uleft&&a<(uintptr_t)&uleft+sizeof uleft)return 6000000+a-(uintptr_t)&uleft;
if(a>=(uintptr_t)&uright&&a<(uintptr_t)&uright+sizeof uright)return 6100000+a-(uintptr_t)&uright;
if(a>=(uintptr_t)&ublindf&&a<(uintptr_t)&ublindf+sizeof ublindf)return 6200000+a-(uintptr_t)&ublindf;
if(a>=(uintptr_t)&def_oc_syms&&a<(uintptr_t)&def_oc_syms+sizeof def_oc_syms)return 6300000+a-(uintptr_t)&def_oc_syms;
for(int i=blockcount-1;i>=0;i--)if(a>=(uintptr_t)blocks[i].p&&a<(uintptr_t)blocks[i].p+blocks[i].n)return 10000000+(uint64_t)i*100000+a-(uintptr_t)blocks[i].p;return a;}
void __real_free(void*);void __wrap_free(void*p){if(!p)return;for(int i=blockcount-1;i>=0;i--)if(blocks[i].p==p){if(!blocks[i].live)abort();blocks[i].saved=malloc(blocks[i].n);if(!blocks[i].saved)abort();memcpy(blocks[i].saved,p,blocks[i].n);blocks[i].live=0;append("free:%d;",i);__real_free(p);return;}for(int i=0;i<24;i++)if(p==&objpool[i])abort();__real_free(p);}
static void*tracked(size_t n,int kind){if(blockcount==512)abort();void*p=malloc(n);if(!p)abort();memset(p,0x5a,n);blocks[blockcount]=(struct allocation){p,n,1,kind,0};append("alloc:%d:%zu:%d;",blockcount,n,kind);blockcount++;return p;}
static void hook(void){if(grow){grow=0;emscripten_resize_heap(emscripten_get_heap_size()+65536);}if(reentry){reentry=0;(void)bcsign(&objpool[0]);}}
long * (alloc)(unsigned int a0){return tracked(a0,0);}
void (dealloc_mextra)(struct monst * a0){if(a0->mextra){free(a0->mextra);a0->mextra=0;}}
char * (dupstr)(const char * a0){size_t n=strlen(a0)+1;char*p=tracked(n,1);memcpy(p,a0,n);return p;}
boolean (erosion_matters)(struct obj * a0){append("erosion_matters:%lld;",(long long)token(a0));return 0;}
boolean (rng_log_enabled)(void){return 1;}
void (rng_log_set_caller)(const char * a0,int a1,const char * a2){append("rngcaller:%s:%d:%s;",a0,a1,a2);}
int (rn2)(int a0){if(a0<=0)abort();int v=rngvalue>=0?rngvalue%a0:(int)(rngcursor++%(unsigned)a0);append("rn2:%d:%d;",a0,v);if(rng_mutate&&a0==5){objects[WAN_FIRE].oc_dir=NODIR;rng_mutate=0;append("mutated-dir;");}hook();return v;}
boolean (on_level)(d_level * a0,d_level * a1){return a0->dnum==a1->dnum&&a0->dlevel==a1->dlevel;}
boolean (In_hell)(d_level * a0){return result==2;}
int (rnd)(int a0){if(a0<=0)abort();int v=1+(rngvalue>=0?rngvalue%a0:(int)(rngcursor++%(unsigned)a0));append("rnd:%d:%d;",a0,v);hook();return v;}
int (rnd_class)(int a0,int a1){return a0;}
anything * (obj_to_any)(struct obj * a0){timer_arg.a_obj=a0;return &timer_arg;}
long (stop_timer)(short a0,union any * a1){append("stoptimer:%d:%llu;",a0,(unsigned long long)token(a1->a_obj));if(a1->a_obj)a1->a_obj->timed=0;return timer_when;}
xint16 (level_difficulty)(void){return 10;}
struct permonst * (rndmonst_adj)(int a0,int a1){return pointer_out?0:&mons[PM_HUMAN];}
struct obj * (oname)(struct obj * a0,const char * a1,unsigned int a2){if(replace_named){struct obj*p=tracked(sizeof *p,2);*p=*a0;free(a0);a0=p;}append("oname:%llu:%s;",(unsigned long long)token(a0),a1);return a0;}
void (copy_mextra)(struct monst * a0,struct monst * a1){if(a1->mextra){a0->mextra=tracked(sizeof(struct mextra),0);memcpy(a0->mextra,a1->mextra,sizeof(struct mextra));}else a0->mextra=0;}
void (splitbill)(struct obj * a0,struct obj * a1){append("splitbill:%lld:%lld;",(long long)token(a0),(long long)token(a1));}
void (obj_split_timers)(struct obj * a0,struct obj * a1){append("obj_split_timers:%lld:%lld;",(long long)token(a0),(long long)token(a1));}
boolean (obj_sheds_light)(struct obj * a0){return 0;}
void (obj_split_light_source)(struct obj * a0,struct obj * a1){append("obj_split_light_source:%lld:%lld;",(long long)token(a0),(long long)token(a1));}
int (oid_price_adjustment)(struct obj * a0,unsigned int a1){append("oid_price_adjustment:%lld:%lld;",(long long)token(a0),(long long)a1);return 0;}
int (merged)(struct obj ** a0,struct obj ** a1){if(result!=4)return 0;append("merged:%llu:%llu;",(unsigned long long)token(*a0),(unsigned long long)token(*a1));(*a0)->quan+=(*a1)->quan;free(*a1);*a1=0;return 1;}
long (unpaid_cost)(struct obj * a0,uchar a1){append("unpaid_cost:%lld:%lld;",(long long)token(a0),(long long)a1);return 0;}
struct monst * (shop_keeper)(char a0){return pointer_out?&monpool[0]:0;}
void (subfrombill)(struct obj * a0,struct monst * a1){append("subfrombill:%lld:%lld;",(long long)token(a0),(long long)token(a1));}
void (addtobill)(struct obj * a0,boolean a1,boolean a2,boolean a3){append("addtobill:%lld:%lld:%lld:%lld;",(long long)token(a0),(long long)a1,(long long)a2,(long long)a3);}
void (alter_cost)(struct obj * a0,long a1){append("alter_cost:%lld:%lld;",(long long)token(a0),(long long)a1);}
boolean (get_obj_location)(struct obj * a0,coordxy * a1,coordxy * a2,int a3){*a1=a0->ox;*a2=a0->oy;return query;}
boolean (costly_spot)(coordxy a0,coordxy a1){append("costly_spot:%lld:%lld;",(long long)a0,(long long)a1);return 0;}
char * (in_rooms)(coordxy a0,coordxy a1,int a2){return result?"r":"";}
boolean (billable)(struct monst ** a0,struct obj * a1,char a2,boolean a3){*a0=pointer_out?&monpool[0]:0;return query;}
char * (simpleonames)(struct obj * a0){return "items";}
long (stolen_value)(struct obj * a0,coordxy a1,coordxy a2,boolean a3,boolean a4){append("stolen_value:%lld:%lld:%lld:%lld:%lld;",(long long)token(a0),(long long)a1,(long long)a2,(long long)a3,(long long)a4);return 0;}
int (rne)(int a0){return 1;}
boolean (permapoisoned)(struct obj * a0){append("permapoisoned:%lld;",(long long)token(a0));return 0;}
int (nartifact_exist)(void){append("nartifact_exist:;");return 0;}
struct obj * (mk_artifact)(struct obj * a0,aligntyp a1,uchar a2,boolean a3){return a0;}
int (undead_to_corpse)(int a0){return a0;}
int (can_be_hatched)(int a0){return a0;}
boolean (dead_species)(int a0,boolean a1){append("dead_species:%lld:%lld;",(long long)a0,(long long)a1);return 0;}
void (set_tin_variety)(struct obj * a0,int a1){append("set_tin_variety:%lld:%lld;",(long long)token(a0),(long long)a1);}
void (assign_candy_wrapper)(struct obj * a0){append("assign_candy_wrapper:%lld;",(long long)token(a0));}
boolean (In_quest)(d_level * a0){return 0;}
const char * (noveltitle)(int * a0){*a0=0;return "a title";}
void (obj_stop_timers)(struct obj * a0){append("stoptimers:%llu;",(unsigned long long)token(a0));a0->timed=0;}
void (attach_fig_transform_timeout)(struct obj * a0){append("attach_fig_transform_timeout:%lld;",(long long)token(a0));}
void (attach_egg_hatch_timeout)(struct obj * a0,long a1){append("attach_egg_hatch_timeout:%lld:%lld;",(long long)token(a0),(long long)a1);}
int (rnz)(int a0){return a0;}
int (zombie_form)(struct permonst * a0){return NON_PM;}
boolean (start_timer)(long a0,short a1,short a2,union any * a3){append("starttimer:%ld:%d:%d:%llu;",a0,a1,a2,(unsigned long long)token(a3->a_obj));timer_when=a0;timer_func=a2;if(a3->a_obj)a3->a_obj->timed++;hook();return 1;}
boolean (is_ice)(coordxy a0,coordxy a1){return result==3;}
boolean (eating_glob)(struct obj * a0){append("eating_glob:%lld;",(long long)token(a0));return 0;}
char * (Yname2)(struct obj * a0){return "Item";}
int (near_capacity)(void){append("near_capacity:;");return 0;}
void (newsym)(coordxy a0,coordxy a1){append("newsym:%lld:%lld;",(long long)a0,(long long)a1);}
char * (strsubst)(char * a0,const char * a1,const char * a2){return a0;}
void (update_inventory)(void){append("update_inventory:;");}
void (encumber_msg)(void){append("encumber_msg:;");}
void (remove_worn_item)(struct obj * a0,boolean a1){append("remove_worn_item:%lld:%lld;",(long long)token(a0),(long long)a1);}
void (stop_occupation)(void){append("stop_occupation:;");}
void (useupall)(struct obj * a0){append("useupall:%llu;",(unsigned long long)token(a0));free(a0);}
void (setmnotwielded)(struct monst * a0,struct obj * a1){append("setmnotwielded:%lld:%lld;",(long long)token(a0),(long long)token(a1));}
void (maybe_unhide_at)(coordxy a0,coordxy a1){append("maybe_unhide_at:%lld:%lld;",(long long)a0,(long long)a1);}
void (obfree)(struct obj * a0,struct obj * a1){append("obfree:%llu;",(unsigned long long)token(a0));free(a0);}
int (arti_light_radius)(struct obj * a0){append("arti_light_radius:%lld;",(long long)token(a0));return 0;}
void (obj_adjust_light_radius)(struct obj * a0,int a1){append("obj_adjust_light_radius:%lld:%lld;",(long long)token(a0),(long long)a1);}
char * (otense)(struct obj * a0,const char * a1){return (char*)a1;}
boolean (confers_luck)(struct obj * a0){append("confers_luck:%lld;",(long long)token(a0));return 0;}
void (set_moreluck)(void){append("set_moreluck:;");}
void (reset_remarm)(void){append("reset_remarm:;");}
void (drop_uswapwep)(void){append("drop_uswapwep:;");}
void (book_cursed)(struct obj * a0){append("book_cursed:%lld;",(long long)token(a0));}
int (eaten_stat)(int a0,struct obj * a1){return a0;}
struct obj * (g_at)(coordxy a0,coordxy a1){return 0;}
schar (depth)(d_level * a0){depth_calls++;append("depth:%d;",a0->dlevel);return a0->dlevel;}
boolean (rloco)(struct obj * a0){append("rloco:%lld;",(long long)token(a0));return 0;}
void (forget_temple_entry)(struct monst * a0){append("forget_temple_entry:%lld;",(long long)token(a0));}
struct obj * (tt_oname)(struct obj * a0){return a0;}
int (isok)(coordxy a0,coordxy a1){return a0>0&&a0<COLNO&&a1>=0&&a1<ROWNO;}
char * (safe_typename)(int a0){return "item";}
void (obj_no_longer_held)(struct obj * a0){append("obj_no_longer_held:%lld;",(long long)token(a0));}
void (block_point)(int a0,int a1){append("block_point:%lld:%lld;",(long long)a0,(long long)a1);}
struct monst * (find_objowner)(struct obj * a0,coordxy a1,coordxy a2){return pointer_out?&monpool[0]:0;}
boolean (costly_adjacent)(struct monst * a0,coordxy a1,coordxy a2){append("costly_adjacent:%lld:%lld:%lld;",(long long)token(a0),(long long)a1,(long long)a2);return 0;}
boolean (debugcore)(const char * a0,boolean a1){return result;}
char * (doname)(struct obj * a0){return "an item";}
char * (s_suffix)(const char * a0){return (char*)a0;}
char * (xname)(struct obj * a0){return "item";}
char * (The)(const char * a0){return (char*)a0;}
void (recalc_block_point)(coordxy a0,coordxy a1){append("recalc_block_point:%lld:%lld;",(long long)a0,(long long)a1);}
void (extract_from_minvent)(struct monst * a0,struct obj * a1,boolean a2,boolean a3){append("extract:%llu:%llu;",(unsigned long long)token(a0),(unsigned long long)token(a1));if(a0->minvent==a1)a0->minvent=a1->nobj;a1->nobj=0;}
const char * (safe_oname)(struct obj * a0){return "item";}
void (artifact_exists)(struct obj * a0,const char * a1,boolean a2,unsigned int a3){append("artifact_exists:%lld:%s:%lld:%lld;",(long long)token(a0),(a1?a1:"NULL"),(long long)a2,(long long)a3);}
void (freeinv)(struct obj * a0){append("freeinv:%lld;",(long long)token(a0));}
void (maybe_reset_pick)(struct obj * a0){append("maybe_reset_pick:%lld;",(long long)token(a0));}
void (del_light_source)(int a0,union any * a1){append("del_light_source:%lld:%lld;",(long long)a0,(long long)token(a1));}
void (consume_obj_charge)(struct obj * a0,boolean a1){append("consume_obj_charge:%lld:%lld;",(long long)token(a0),(long long)a1);}
char * (vtense)(const char * a0,const char * a1){return (char*)a1;}
char * (aobjnam)(struct obj * a0,const char * a1){return "item moves";}
struct obj * (hold_another_object)(struct obj * a0,const char * a1,const char * a2,const char * a3){return a0;}
boolean (can_reach_floor)(boolean a0){append("can_reach_floor:%lld;",(long long)a0);return 0;}
void (hitfloor)(struct obj * a0,boolean a1){append("hitfloor:%lld:%lld;",(long long)token(a0),(long long)a1);}
void (doaltarobj)(struct obj * a0){append("doaltarobj:%lld;",(long long)token(a0));}
char * (Doname2)(struct obj * a0){return "an item";}
const char * (surface)(coordxy a0,coordxy a1){return "floor";}
void (dropy)(struct obj * a0){append("dropy:%lld;",(long long)token(a0));}
void (discover_object)(int a0,boolean a1,boolean a2,boolean a3){append("discover_object:%lld:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2,(long long)a3);}
boolean (is_pool_or_lava)(coordxy a0,coordxy a1){append("is_pool_or_lava:%lld:%lld;",(long long)a0,(long long)a1);return 0;}
boolean (is_pool)(coordxy a0,coordxy a1){append("is_pool:%lld:%lld;",(long long)a0,(long long)a1);return 0;}
struct monst * (find_mid)(unsigned int a0,unsigned int a1){return pointer_out?&monpool[0]:0;}
const char * (mon_pmname)(struct monst * a0){return "monster";}
boolean (onshopbill)(struct obj * a0,struct monst * a1,boolean a2){append("onshopbill:%lld:%lld:%lld;",(long long)token(a0),(long long)token(a1),(long long)a2);return 0;}
int (Mgender)(struct monst * a0){append("Mgender:%lld;",(long long)token(a0));return 0;}
const char * (pmname)(struct permonst * a0,int a1){return "human";}
int (pronoun_gender)(struct monst * a0,unsigned int a1){return 0;}
char * (strstri)(const char * a0,const char * a1){return (char*)strstr(a0,a1);}
char * (x_monnam)(struct monst * a0,int a1,const char * a2,int a3,boolean a4){return "Monster";}
char * (fmt_ptr)(const void * a0){static char b[64];snprintf(b,sizeof b,"ptr%llu",(unsigned long long)token(a0));return b;}
char * (eos)(char * a0){return a0+strlen(a0);}
void (copynchars)(char * a0,const char * a1,int a2){int i=0;while(i<a2&&a1[i]){a0[i]=a1[i];i++;}a0[i]=0;}
char * (makesingular)(const char * a0){return (char*)a0;}
struct obj * (sobj_at)(int a0,coordxy a1,coordxy a2){for(struct obj*p=svl.level.objects[a1][a2];p;p=p->nexthere)if(p->otyp==a0)return p;return 0;}
boolean (mergable)(struct obj * a0,struct obj * a1){return query;}
struct obj * (nxtobj)(struct obj * a0,int a1,boolean a2){append("nxtobj:%lld:%lld:%lld;",(long long)token(a0),(long long)a1,(long long)a2);return 0;}
void (globby_bill_fixup)(struct obj * a0,struct obj * a1){append("globby_bill_fixup:%lld:%lld;",(long long)token(a0),(long long)token(a1));}
char * (obj_typename)(int a0){return "item";}
char * (makeplural)(const char * a0){return (char*)a0;}
void (You_hear)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("You_hear:%s;",b);}
void (You_see)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("You_see:%s;",b);}
void (Your)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("Your:%s;",b);}
void (impossible)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("impossible:%s;",b);}
void (panic)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("panic:%s;",b);longjmp(escape,1);}
void (pline)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("pline:%s;",b);}
void (verbalize)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("verbalize:%s;",b);}
#ifdef HYBRID_MKOBJ
#include "../nethack-c/wasm/tu-fragments/mkobj-types.h"
extern void teleport_mkobj_init_oextra(struct oextra * oex);
#define init_oextra teleport_mkobj_init_oextra
extern boolean teleport_mkobj_may_generate_eroded(struct obj * otmp);
#define may_generate_eroded teleport_mkobj_may_generate_eroded
extern void teleport_mkobj_mkobj_erosions(struct obj * otmp);
#define mkobj_erosions teleport_mkobj_mkobj_erosions
extern void teleport_mkobj_mkbox_cnts(struct obj * box);
#define mkbox_cnts teleport_mkobj_mkbox_cnts
extern unsigned int teleport_mkobj_nextoid(struct obj * oldobj,struct obj * newobj);
#define nextoid teleport_mkobj_nextoid
extern void teleport_mkobj_mksobj_init(struct obj ** obj,boolean artif);
#define mksobj_init teleport_mkobj_mksobj_init
extern int teleport_mkobj_item_on_ice(struct obj * item);
#define item_on_ice teleport_mkobj_item_on_ice
extern void teleport_mkobj_shrinking_glob_gone(struct obj * obj);
#define shrinking_glob_gone teleport_mkobj_shrinking_glob_gone
extern struct obj * teleport_mkobj_save_mtraits(struct obj * obj,struct monst * mtmp);
#define save_mtraits teleport_mkobj_save_mtraits
extern void teleport_mkobj_obj_timer_checks(struct obj * otmp,coordxy x,coordxy y,int force);
#define obj_timer_checks teleport_mkobj_obj_timer_checks
extern void teleport_mkobj_dealloc_obj_real(struct obj * obj);
#define dealloc_obj_real teleport_mkobj_dealloc_obj_real
extern void teleport_mkobj_objlist_sanity(struct obj * objlist,int wheretype,const char * mesg);
#define objlist_sanity teleport_mkobj_objlist_sanity
extern void teleport_mkobj_shop_obj_sanity(struct obj * obj,const char * mesg);
#define shop_obj_sanity teleport_mkobj_shop_obj_sanity
extern void teleport_mkobj_mon_obj_sanity(struct monst * monlist,const char * mesg);
#define mon_obj_sanity teleport_mkobj_mon_obj_sanity
extern void teleport_mkobj_insane_obj_bits(struct obj * obj,struct monst * mon);
#define insane_obj_bits teleport_mkobj_insane_obj_bits
extern boolean teleport_mkobj_nomerge_exception(struct obj * obj);
#define nomerge_exception teleport_mkobj_nomerge_exception
extern const char * teleport_mkobj_where_name(struct obj * obj);
#define where_name teleport_mkobj_where_name
extern void teleport_mkobj_insane_object(struct obj * obj,const char * fmt,const char * mesg,struct monst * mon);
#define insane_object teleport_mkobj_insane_object
extern void teleport_mkobj_check_contained(struct obj * container,const char * mesg);
#define check_contained teleport_mkobj_check_contained
extern void teleport_mkobj_check_glob(struct obj * obj,const char * mesg);
#define check_glob teleport_mkobj_check_glob
extern void teleport_mkobj_sanity_check_worn(struct obj * obj);
#define sanity_check_worn teleport_mkobj_sanity_check_worn
#else
#include "../.cache/wasm64-build/tree/src/mkobj.c"
#define TELEPORT_MKOBJ_TYPES_H
#endif
#include "../nethack-c/wasm/tu-fragments/mkobj-support.c"
#include "../nethack-c/wasm/tu-fragments/mkobj-abi-asserts.h"
#include "tu-mkobj-layout.h"
uintptr_t probe_pool(int k,int i){return(uintptr_t)(k==0?(void*)&objpool[i]:k==1?(void*)&monpool[i]:k==2?(void*)&bufferpool[i]:k==3?(void*)&headcells[i]:k==4?(void*)&anycells[i]:(void*)&extrapool[i]);}
int probe_block_count(void){return blockcount;}
uintptr_t probe_block_bytes(int i){return(uintptr_t)(blocks[i].live?blocks[i].p:blocks[i].saved);}
uintptr_t probe_block(int i){return(uintptr_t)blocks[i].p;}
size_t probe_block_size(int i){return blocks[i].n;}
int probe_block_live(int i){return blocks[i].live;}
int probe_block_kind(int i){return blocks[i].kind;}
uintptr_t probe_heap_obj(int i){struct obj*p=tracked(sizeof(struct obj),2);*p=objpool[i];return(uintptr_t)p;}
int probe_layout_count(void){return sizeof mkobj_layout/sizeof mkobj_layout[0];}
const char*probe_layout_name(int i){return mkobj_layout[i].name;}
int64_t probe_layout_value(int i){return(int64_t)mkobj_layout[i].value;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
const char*probe_trace(void){return tracebuf;}
void probe_option(int k,int64_t v){switch(k){case 0:result=v;break;case 1:rngvalue=v;rngcursor=0;break;case 2:query=v;break;case 3:grow=v;break;case 4:reentry=v;break;case 5:pointer_out=v;break;case 6:replace_named=v;break;case 7:rng_mutate=v;break;case 8:timer_when=v;break;default:abort();}}
uint64_t probe_action(int which,uint64_t a,uint64_t b,uint64_t c,uint64_t d,uint64_t e,uint64_t f){if(setjmp(escape))return 0x70000000;switch(which){
case 0:init_oextra((struct oextra *)(uintptr_t)a);return 0;
case 1:return(uint64_t)(uintptr_t)(newoextra());
case 2:dealloc_oextra((struct obj *)(uintptr_t)a);return 0;
case 3:newomonst((struct obj *)(uintptr_t)a);return 0;
case 4:free_omonst((struct obj *)(uintptr_t)a);return 0;
case 5:newomid((struct obj *)(uintptr_t)a);return 0;
case 6:free_omid((struct obj *)(uintptr_t)a);return 0;
case 7:new_omailcmd((struct obj *)(uintptr_t)a,(const char *)(uintptr_t)b);return 0;
case 8:free_omailcmd((struct obj *)(uintptr_t)a);return 0;
case 9:return(uint64_t)(uintptr_t)(may_generate_eroded((struct obj *)(uintptr_t)a));
case 10:mkobj_erosions((struct obj *)(uintptr_t)a);return 0;
case 11:return(uint64_t)(uintptr_t)(mkobj_at((char)(uintptr_t)a,(coordxy)(uintptr_t)b,(coordxy)(uintptr_t)c,(boolean)(uintptr_t)d));
case 12:return(uint64_t)(uintptr_t)(mksobj_at((int)(uintptr_t)a,(coordxy)(uintptr_t)b,(coordxy)(uintptr_t)c,(boolean)(uintptr_t)d,(boolean)(uintptr_t)e));
case 13:return(uint64_t)(uintptr_t)(mksobj_migr_to_species((int)(uintptr_t)a,(unsigned int)(uintptr_t)b,(boolean)(uintptr_t)c,(boolean)(uintptr_t)d));
case 14:return(uint64_t)(uintptr_t)(mkobj((int)(uintptr_t)a,(boolean)(uintptr_t)b));
case 15:mkbox_cnts((struct obj *)(uintptr_t)a);return 0;
case 16:return(uint64_t)(uintptr_t)(rndmonnum());
case 17:return(uint64_t)(uintptr_t)(rndmonnum_adj((int)(uintptr_t)a,(int)(uintptr_t)b));
case 18:copy_oextra((struct obj *)(uintptr_t)a,(struct obj *)(uintptr_t)b);return 0;
case 19:return(uint64_t)(uintptr_t)(splitobj((struct obj *)(uintptr_t)a,(long)(uintptr_t)b));
case 20:return(uint64_t)(uintptr_t)(next_ident());
case 21:return(uint64_t)(uintptr_t)(nextoid((struct obj *)(uintptr_t)a,(struct obj *)(uintptr_t)b));
case 22:return(uint64_t)(uintptr_t)(unsplitobj((struct obj *)(uintptr_t)a));
case 23:clear_splitobjs();return 0;
case 24:replace_object((struct obj *)(uintptr_t)a,(struct obj *)(uintptr_t)b);return 0;
case 25:return(uint64_t)(uintptr_t)(unknwn_contnr_contents((struct obj *)(uintptr_t)a));
case 26:bill_dummy_object((struct obj *)(uintptr_t)a);return 0;
case 27:costly_alteration((struct obj *)(uintptr_t)a,(int)(uintptr_t)b);return 0;
case 28:clear_dknown((struct obj *)(uintptr_t)a);return 0;
case 29:unknow_object((struct obj *)(uintptr_t)a);return 0;
case 30:mksobj_init((struct obj **)(uintptr_t)a,(boolean)(uintptr_t)b);return 0;
case 31:return(uint64_t)(uintptr_t)(mksobj((int)(uintptr_t)a,(boolean)(uintptr_t)b,(boolean)(uintptr_t)c));
case 32:return(uint64_t)(uintptr_t)(stone_object_type((unsigned int)(uintptr_t)a));
case 33:return(uint64_t)(uintptr_t)(stone_furniture_type((unsigned int)(uintptr_t)a));
case 34:set_corpsenm((struct obj *)(uintptr_t)a,(int)(uintptr_t)b);return 0;
case 35:return(uint64_t)(uintptr_t)(rider_revival_time((struct obj *)(uintptr_t)a,(boolean)(uintptr_t)b));
case 36:start_corpse_timeout((struct obj *)(uintptr_t)a);return 0;
case 37:return(uint64_t)(uintptr_t)(item_on_ice((struct obj *)(uintptr_t)a));
case 38:start_glob_timeout((struct obj *)(uintptr_t)a,(long)(uintptr_t)b);return 0;
case 39:shrink_glob((anything *)(uintptr_t)a,(long)(uintptr_t)b);return 0;
case 40:shrinking_glob_gone((struct obj *)(uintptr_t)a);return 0;
case 41:maybe_adjust_light((struct obj *)(uintptr_t)a,(int)(uintptr_t)b);return 0;
case 42:bless((struct obj *)(uintptr_t)a);return 0;
case 43:unbless((struct obj *)(uintptr_t)a);return 0;
case 44:curse((struct obj *)(uintptr_t)a);return 0;
case 45:uncurse((struct obj *)(uintptr_t)a);return 0;
case 46:blessorcurse((struct obj *)(uintptr_t)a,(int)(uintptr_t)b);return 0;
case 47:return(uint64_t)(uintptr_t)(bcsign((struct obj *)(uintptr_t)a));
case 48:set_bknown((struct obj *)(uintptr_t)a,(unsigned int)(uintptr_t)b);return 0;
case 49:return(uint64_t)(uintptr_t)(weight((struct obj *)(uintptr_t)a));
case 50:return(uint64_t)(uintptr_t)(rnd_treefruit_at((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b));
case 51:return(uint64_t)(uintptr_t)(is_treefruit((struct obj *)(uintptr_t)a));
case 52:return(uint64_t)(uintptr_t)(mkgold((long)(uintptr_t)a,(coordxy)(uintptr_t)b,(coordxy)(uintptr_t)c));
case 53:fixup_oil((struct obj *)(uintptr_t)a,(struct obj *)(uintptr_t)b);return 0;
case 54:return(uint64_t)(uintptr_t)(mkcorpstat((int)(uintptr_t)a,(struct monst *)(uintptr_t)b,(struct permonst *)(uintptr_t)c,(coordxy)(uintptr_t)d,(coordxy)(uintptr_t)e,(unsigned int)(uintptr_t)f));
case 55:return(uint64_t)(uintptr_t)(corpse_revive_type((struct obj *)(uintptr_t)a));
case 56:return(uint64_t)(uintptr_t)(obj_attach_mid((struct obj *)(uintptr_t)a,(unsigned int)(uintptr_t)b));
case 57:return(uint64_t)(uintptr_t)(save_mtraits((struct obj *)(uintptr_t)a,(struct monst *)(uintptr_t)b));
case 58:return(uint64_t)(uintptr_t)(get_mtraits((struct obj *)(uintptr_t)a,(boolean)(uintptr_t)b));
case 59:return(uint64_t)(uintptr_t)(mk_tt_object((int)(uintptr_t)a,(coordxy)(uintptr_t)b,(coordxy)(uintptr_t)c));
case 60:return(uint64_t)(uintptr_t)(mk_named_object((int)(uintptr_t)a,(struct permonst *)(uintptr_t)b,(coordxy)(uintptr_t)c,(coordxy)(uintptr_t)d,(const char *)(uintptr_t)e));
case 61:return(uint64_t)(uintptr_t)(is_flammable((struct obj *)(uintptr_t)a));
case 62:return(uint64_t)(uintptr_t)(is_rottable((struct obj *)(uintptr_t)a));
case 63:place_object((struct obj *)(uintptr_t)a,(coordxy)(uintptr_t)b,(coordxy)(uintptr_t)c);return 0;
case 64:recreate_pile_at((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b);return 0;
case 65:obj_ice_effects((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b,(boolean)(uintptr_t)c);return 0;
case 66:return(uint64_t)(uintptr_t)(peek_at_iced_corpse_age((struct obj *)(uintptr_t)a));
case 67:obj_timer_checks((struct obj *)(uintptr_t)a,(coordxy)(uintptr_t)b,(coordxy)(uintptr_t)c,(int)(uintptr_t)d);return 0;
case 68:remove_object((struct obj *)(uintptr_t)a);return 0;
case 69:discard_minvent((struct monst *)(uintptr_t)a,(boolean)(uintptr_t)b);return 0;
case 70:obj_extract_self((struct obj *)(uintptr_t)a);return 0;
case 71:extract_nobj((struct obj *)(uintptr_t)a,(struct obj **)(uintptr_t)b);return 0;
case 72:extract_nexthere((struct obj *)(uintptr_t)a,(struct obj **)(uintptr_t)b);return 0;
case 73:return(uint64_t)(uintptr_t)(add_to_minv((struct monst *)(uintptr_t)a,(struct obj *)(uintptr_t)b));
case 74:return(uint64_t)(uintptr_t)(add_to_container((struct obj *)(uintptr_t)a,(struct obj *)(uintptr_t)b));
case 75:add_to_migration((struct obj *)(uintptr_t)a);return 0;
case 76:add_to_buried((struct obj *)(uintptr_t)a);return 0;
case 77:container_weight((struct obj *)(uintptr_t)a);return 0;
case 78:dealloc_obj((struct obj *)(uintptr_t)a);return 0;
case 79:dealloc_obj_real((struct obj *)(uintptr_t)a);return 0;
case 80:dobjsfree();return 0;
case 81:return(uint64_t)(uintptr_t)(hornoplenty((struct obj *)(uintptr_t)a,(boolean)(uintptr_t)b,(struct obj *)(uintptr_t)c));
case 82:obj_sanity_check();return 0;
case 83:objlist_sanity((struct obj *)(uintptr_t)a,(int)(uintptr_t)b,(const char *)(uintptr_t)c);return 0;
case 84:shop_obj_sanity((struct obj *)(uintptr_t)a,(const char *)(uintptr_t)b);return 0;
case 85:mon_obj_sanity((struct monst *)(uintptr_t)a,(const char *)(uintptr_t)b);return 0;
case 86:insane_obj_bits((struct obj *)(uintptr_t)a,(struct monst *)(uintptr_t)b);return 0;
case 87:return(uint64_t)(uintptr_t)(nomerge_exception((struct obj *)(uintptr_t)a));
case 88:return(uint64_t)(uintptr_t)(where_name((struct obj *)(uintptr_t)a));
case 89:insane_object((struct obj *)(uintptr_t)a,(const char *)(uintptr_t)b,(const char *)(uintptr_t)c,(struct monst *)(uintptr_t)d);return 0;
case 90:return(uint64_t)(uintptr_t)(init_dummyobj((struct obj *)(uintptr_t)a,(short)(uintptr_t)b,(long)(uintptr_t)c));
case 91:check_contained((struct obj *)(uintptr_t)a,(const char *)(uintptr_t)b);return 0;
case 92:check_glob((struct obj *)(uintptr_t)a,(const char *)(uintptr_t)b);return 0;
case 93:sanity_check_worn((struct obj *)(uintptr_t)a);return 0;
case 94:return(uint64_t)(uintptr_t)(obj_nexto((struct obj *)(uintptr_t)a));
case 95:return(uint64_t)(uintptr_t)(obj_nexto_xy((struct obj *)(uintptr_t)a,(coordxy)(uintptr_t)b,(coordxy)(uintptr_t)c,(boolean)(uintptr_t)d));
case 96:return(uint64_t)(uintptr_t)(obj_absorb((struct obj **)(uintptr_t)a,(struct obj **)(uintptr_t)b));
case 97:return(uint64_t)(uintptr_t)(obj_meld((struct obj **)(uintptr_t)a,(struct obj **)(uintptr_t)b));
case 98:pudding_merge_message((struct obj *)(uintptr_t)a,(struct obj *)(uintptr_t)b);return 0;
default:abort();}}
size_t probe_pointer_offset(int k,int f){if(k==0){switch(f){case 0:return offsetof(struct obj,nobj);case 1:return offsetof(struct obj,v);case 2:return offsetof(struct obj,cobj);case 3:return offsetof(struct obj,oextra);}}if(k==1){switch(f){case 0:return offsetof(struct monst,nmon);case 1:return offsetof(struct monst,data);case 2:return offsetof(struct monst,mextra);}}abort();}
void probe_reset(void){for(int i=0;i<blockcount;i++){if(blocks[i].live)__real_free(blocks[i].p);if(blocks[i].saved)__real_free(blocks[i].saved);}blockcount=0;traceused=0;tracebuf[0]=0;result=0;rngvalue=0;rngcursor=0;query=1;grow=reentry=pointer_out=replace_named=rng_mutate=depth_calls=0;timer_when=0;timer_func=0;memset(&timer_arg,0,sizeof timer_arg);memset(objpool,0,sizeof objpool);memset(extrapool,0x5a,sizeof extrapool);memset(monpool,0,sizeof monpool);memset(bufferpool,0,sizeof bufferpool);memset(headcells,0,sizeof headcells);memset(anycells,0,sizeof anycells);
memset((void*)&svm,0,sizeof svm);
memset((void*)&gi,0,sizeof gi);
memset((void*)&objects,0,sizeof objects);
memset((void*)&svd,0,sizeof svd);
memset((void*)&u,0,sizeof u);
memset((void*)&svb,0,sizeof svb);
memset((void*)&go,0,sizeof go);
memset((void*)&obj_descr,0,sizeof obj_descr);
memset((void*)&svc,0,sizeof svc);
memset((void*)&svl,0,sizeof svl);
memset((void*)&flags,0,sizeof flags);
memset((void*)&gu,0,sizeof gu);
memset((void*)&gz,0,sizeof gz);
memset((void*)&iflags,0,sizeof iflags);
memset((void*)&gv,0,sizeof gv);
memset((void*)&uwep,0,sizeof uwep);
memset((void*)&uswapwep,0,sizeof uswapwep);
memset((void*)&gm,0,sizeof gm);
memset((void*)&gb,0,sizeof gb);
memset((void*)&hands_obj,0,sizeof hands_obj);
memset((void*)&gt,0,sizeof gt);
memset((void*)&gk,0,sizeof gk);
memset((void*)&program_state,0,sizeof program_state);
memset((void*)&gc,0,sizeof gc);
memset((void*)&uchain,0,sizeof uchain);
memset((void*)&uball,0,sizeof uball);
memset((void*)&uskin,0,sizeof uskin);
memset((void*)&uarm,0,sizeof uarm);
memset((void*)&uarmc,0,sizeof uarmc);
memset((void*)&uarmh,0,sizeof uarmh);
memset((void*)&uarms,0,sizeof uarms);
memset((void*)&uarmg,0,sizeof uarmg);
memset((void*)&uarmf,0,sizeof uarmf);
memset((void*)&uarmu,0,sizeof uarmu);
memset((void*)&uquiver,0,sizeof uquiver);
memset((void*)&uamul,0,sizeof uamul);
memset((void*)&uleft,0,sizeof uleft);
memset((void*)&uright,0,sizeof uright);
memset((void*)&ublindf,0,sizeof ublindf);
for(int i=0;i<NUMMONS;i++){mons[i].mlet=0;mons[i].mflags1=mons[i].mflags2=0;mons[i].mcolor=0;mons[i].difficulty=10;mons[i].mmove=12;mons[i].cwt=1450;mons[i].msize=MZ_HUMAN;}mons[PM_HUMAN].mlet=S_HUMAN;mons[PM_HUMAN].mflags2=M2_HUMAN;for(int i=0;i<NUM_OBJECTS;i++){objects[i].oc_class=FOOD_CLASS;objects[i].oc_descr_idx=objects[i].oc_name_idx=i;objects[i].oc_prob=1;objects[i].oc_weight=10;objects[i].oc_material=WOOD;obj_descr[i].oc_name="fixture";obj_descr[i].oc_descr="fixture";}
int types[]={DAGGER,LEATHER_ARMOR,FOOD_RATION,CHEST,ROCK,POT_HEALING,SCR_IDENTIFY,SPE_MAGIC_MISSILE,WAN_FIRE,RIN_PROTECTION,AMULET_OF_LIFE_SAVING,GOLD_PIECE};int classes[]={WEAPON_CLASS,ARMOR_CLASS,FOOD_CLASS,TOOL_CLASS,GEM_CLASS,POTION_CLASS,SCROLL_CLASS,SPBOOK_CLASS,WAND_CLASS,RING_CLASS,AMULET_CLASS,COIN_CLASS};for(int i=0;i<12;i++){svb.bases[classes[i]]=types[i];go.oclass_prob_totals[classes[i]]=100;objects[types[i]].oc_prob=100;objects[types[i]].oc_class=classes[i];}for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++)levl[x][y].typ=ROOM;u.ux=u.uy=10;u.uz.dnum=1;u.uz.dlevel=5;u.ulevel=10;u.uhp=u.uhpmax=20;u.umonnum=u.umonster=PM_HUMAN;gu.urace.noun="human";gu.urace.adj="human";gu.urace.mnum=PM_HUMAN;svm.moves=100;svc.context.ident=1;for(int i=0;i<24;i++){objpool[i].otyp=FOOD_RATION;objpool[i].oclass=FOOD_CLASS;objpool[i].corpsenm=NON_PM;objpool[i].quan=3;objpool[i].age=1;objpool[i].owt=10;objpool[i].o_id=i+1;objpool[i].where=OBJ_FREE;objpool[i].ox=11;objpool[i].oy=10;}for(int i=0;i<8;i++){monpool[i].data=&mons[PM_HUMAN];monpool[i].mx=11+i;monpool[i].my=10;monpool[i].mhp=monpool[i].mhpmax=20;monpool[i].m_lev=10;monpool[i].mcanmove=monpool[i].mcansee=1;monpool[i].cham=NON_PM;}}
const char*probe_string(int i){switch(i){
case 0:return "fixture";
case 1:return "their";
case 2:return "human";
case 3:return "monster";
case 4:return "Monster";
case 5:return "an item";
case 6:return "item";
case 7:return "Item";
case 8:return "items";
case 9:return "a monster";
case 10:return "A monster";
case 11:return "hallucination";
case 12:return "floor";
case 13:return "ceiling";
case 14:return "trap";
case 15:return "hand";
case 16:return "!";
case 17:return "r";
case 18:return "";
case 19:return "a title";
case 20:return "item moves";
case 21:return "";
case 22:return " bypass";
case 23:return " glob %d,quan=%ld,owt=%u ";
case 24:return " held by mon %s (%s)";
case 25:return " in_use";
case 26:return " inside your pack";
case 27:return " nomerge";
case 28:return " nxtbldr";
case 29:return " obj ";
case 30:return " slightly";
case 31:return "%%s boulder@<%d,%d> %%s %%s: not on top";
case 32:return "%%s boulder@<%d,%d> %%s %%s: on/in %s";
case 33:return "%%s obj@<%d,%d> %%s %%s: %%s@<%d,%d>";
case 34:return "%s";
case 35:return "%s %s %s%s.";
case 36:return "%s %s out.";
case 37:return "%s %s to the %s.";
case 38:return "%s %s%s lighter.";
case 39:return "%s %s.";
case 40:return "%s [not null] %s %s: %s";
case 41:return "%s fades away.";
case 42:return "%s is no longer on ice at <%d,%d>.";
case 43:return "%s is now on ice at <%d,%d>.";
case 44:return "%s no_charge obj inside untended shop! %s %s: %s";
case 45:return "%s no_charge obj not inside tended shop! %s %s: %s";
case 46:return "%s no_charge obj not on floor! %s %s: %s";
case 47:return "%s no_charge obj on shop bill! %s %s: %s";
case 48:return "%s obj %s %s (%s)";
case 49:return "%s obj %s %s (%s) *not*";
case 50:return "%s obj %s %s: %s";
case 51:return "%s obj %s in container %s, not %s";
case 52:return "%s obj both unpaid and no_charge! %s %s: %s";
case 53:return "%s obj contains something! %s %s: %s";
case 54:return "%s unpaid obj inside untended shop! %s %s: %s";
case 55:return "%s unpaid obj not carried! %s %s: %s";
case 56:return "%s unpaid obj not inside tended shop! %s %s: %s";
case 57:return "%s unpaid obj not on shop bill! %s %s: %s";
case 58:return "(null)";
case 59:return "A ";
case 60:return "A potion";
case 61:return "Calculating weight of %ld %s?";
case 62:return "Effective age of corpse: %ld.";
case 63:return "It";
case 64:return "Oops!  %s away from you!";
case 65:return "Oops!  %s out of your reach!";
case 66:return "Oops!  %s to the floor!";
case 67:return "Some food";
case 68:return "Some potions";
case 69:return "The ";
case 70:return "The %s age has ice modifications: otmp->age = %ld, returning %ld.";
case 71:return "The %s%s coalesce%s.";
case 72:return "They";
case 73:return "You %s %s %s, you pay for %s!";
case 74:return "You %s %s, you pay for %s!";
case 75:return "a faint sloshing sound.";
case 76:return "add_to_buried: obj where=%d, not free";
case 77:return "add_to_container: obj where=%d, not free";
case 78:return "add_to_migration: obj where=%d, not free";
case 79:return "add_to_minv: obj where=%d, not free";
case 80:return "adjacent ";
case 81:return "alt weapon";
case 82:return "alternate weapon";
case 83:return "amulet";
case 84:return "armor";
case 85:return "bad horn o' plenty";
case 86:return "ball";
case 87:return "becomes";
case 88:return "bill sanity";
case 89:return "bite";
case 90:return "blessorcurse";
case 91:return "blindfold";
case 92:return "boots";
case 93:return "boulder sanity";
case 94:return "break the lock on";
case 95:return "brighter";
case 96:return "buried";
case 97:return "buried sanity";
case 98:return "burn";
case 99:return "cancel";
case 100:return "chain";
case 101:return "chained ball";
case 102:return "cloak";
case 103:return "contained";
case 104:return "contained ";
case 105:return "copy_oextra";
case 106:return "crack";
case 107:return "current_wand sanity";
case 108:return "dealloc_obj with cobj";
case 109:return "dealloc_obj with hands_obj";
case 110:return "dealloc_obj with nobj";
case 111:return "dealloc_obj: obj already deleted (type=%d)";
case 112:return "dealloc_obj: obj not free (type=%d, where=%d)";
case 113:return "degrade";
case 114:return "deleted";
case 115:return "deleted object sanity";
case 116:return "destroy";
case 117:return "dilute";
case 118:return "disenchant";
case 119:return "dissolves completely";
case 120:return "dobjsfree: obj where=%d, not OBJ_DELETED";
case 121:return "drain";
case 122:return "drop";
case 123:return "erase";
case 124:return "extract_nexthere: object lost";
case 125:return "extract_nobj: object lost";
case 126:return "failed sanity check: container holds its parent";
case 127:return "failed sanity check: container holds itself";
case 128:return "flagged%s%s%s%s";
case 129:return "floor";
case 130:return "floor sanity";
case 131:return "free";
case 132:return "gloves";
case 133:return "gm.mydogs sanity [not empty]";
case 134:return "has_omonst(obj2)";
case 135:return "helm";
case 136:return "hornoplenty";
case 137:return "how_lost=%d obj in inventory!";
case 138:return "invalid alteration type (%d)";
case 139:return "invent";
case 140:return "invent sanity";
case 141:return "it";
case 142:return "kickedobj sanity";
case 143:return "lava";
case 144:return "leashmon:%u %s leashed by %s leash,";
case 145:return "leashmon:%u no monst for %s leash,";
case 146:return "leashmon=%u %s not leashed,";
case 147:return "leashmon=%u no monst,";
case 148:return "left ring";
case 149:return "less brightly";
case 150:return "location sanity";
case 151:return "luafree";
case 152:return "making corpstat type %d";
case 153:return "migrating";
case 154:return "migrating minvent sanity";
case 155:return "migrating sanity";
case 156:return "minvent";
case 157:return "minvent sanity";
case 158:return "mk_tt_object";
case 159:return "mkbox_cnts";
case 160:return "mkgold";
case 161:return "mkobj";
case 162:return "mkobj.c";
case 163:return "mkobj_erosions";
case 164:return "mksobj";
case 165:return "mksobj tried to make type %d, class %d.";
case 166:return "mksobj_init";
case 167:return "monst (%s: %u) wielding %s (%u) not in %s inventory";
case 168:return "monst alt weapon?";
case 169:return "monst quiver?";
case 170:return "much ";
case 171:return "mydogs minvent sanity";
case 172:return "nested ";
case 173:return "neutralize";
case 174:return "next_ident";
case 175:return "non-empty container";
case 176:return "nowhere";
case 177:return "null!";
case 178:return "obj_absorb: not called with two actual objects";
case 179:return "obj_extract_self, where=%d";
case 180:return "obj_meld";
case 181:return "obj_meld: not called with two actual objects";
case 182:return "obj_nexto: wasn't given an object to check";
case 183:return "obj_nexto_xy";
case 184:return "onbill";
case 185:return "open";
case 186:return "pack reaches out and grabs something!";
case 187:return "parts of the floor melting!";
case 188:return "place_object";
case 189:return "place_object: \"%s\" [%d] off map <%d,%d>";
case 190:return "place_object: obj \"%s\" [%d] not free";
case 191:return "primary weapon";
case 192:return "probtype error, oclass=%d i=%d";
case 193:return "quiver";
case 194:return "remove_object: obj where=%d, not on floor";
case 195:return "replace_object: obj position";
case 196:return "returning_missile sanity";
case 197:return "rider_revival_time";
case 198:return "right ring";
case 199:return "ring";
case 200:return "rnd_treefruit_at";
case 201:return "rndmonnum_adj";
case 202:return "rot";
case 203:return "rust";
case 204:return "saddle";
case 205:return "secondary weapon";
case 206:return "seems";
case 207:return "shield";
case 208:return "shine";
case 209:return "shirt";
case 210:return "shrink obj ";
case 211:return "shrink_glob for non-glob [%d: %s]?";
case 212:return "shrinks";
case 213:return "skin";
case 214:return "slip";
case 215:return "spill";
case 216:return "splatter";
case 217:return "splitobj [cobj=%s num=%ld quan=%ld]";
case 218:return "start_corpse_timeout";
case 219:return "start_glob_timeout";
case 220:return "start_glob_timeout for non-glob [%d: %s]?";
case 221:return "suit";
case 222:return "tarnish";
case 223:return "that";
case 224:return "them";
case 225:return "those";
case 226:return "thrownobj sanity";
case 227:return "unbless";
case 228:return "uncharge";
case 229:return "uncurse";
case 230:return "unknown[%d]";
case 231:return "unpaid object migrating to another level? [%s]";
case 232:return "water";
case 233:return "weapon";
case 234:return "worn (%s %s)";
case 235:return "worn mask (bogus)) 0x%08lx";
case 236:return "worn mask (multiple) 0x%08lx";
case 237:return "worn mask 0x%08lx";
case 238:return "worn mask 0x%08lx != %s";
case 239:return "x >= 0 && x < COLNO && y >= 0 && y < ROWNO";
default:return 0;}}
int probe_string_count(void){return 240;}
size_t probe_string_capacity(int i){const char*p=probe_string(i);return p?strlen(p)+1:0;}
uintptr_t probe_data(int i){switch(i){
case 0:
#ifdef HYBRID_MKOBJ
return(uintptr_t)&mkobj_data_mkobjprobs;
#else
return(uintptr_t)&mkobjprobs;
#endif
case 1:
#ifdef HYBRID_MKOBJ
return(uintptr_t)&mkobj_data_boxiprobs;
#else
return(uintptr_t)&boxiprobs;
#endif
case 2:
#ifdef HYBRID_MKOBJ
return(uintptr_t)&mkobj_data_rogueprobs;
#else
return(uintptr_t)&rogueprobs;
#endif
case 3:
#ifdef HYBRID_MKOBJ
return(uintptr_t)&mkobj_data_hellprobs;
#else
return(uintptr_t)&hellprobs;
#endif
case 4:
#ifdef HYBRID_MKOBJ
return(uintptr_t)&mkobj_data_zerooextra;
#else
return(uintptr_t)&zerooextra;
#endif
case 5:
#ifdef HYBRID_MKOBJ
return(uintptr_t)&mkobj_data_alteration_verbs;
#else
return(uintptr_t)&alteration_verbs;
#endif
case 6:
#ifdef HYBRID_MKOBJ
return(uintptr_t)&mkobj_data_dknowns;
#else
return(uintptr_t)&dknowns;
#endif
case 7:
#ifdef HYBRID_MKOBJ
return(uintptr_t)&mkobj_data_treefruits;
#else
return(uintptr_t)&treefruits;
#endif
case 8:
#ifdef HYBRID_MKOBJ
return(uintptr_t)&mkobj_data_ofmt0;
#else
return(uintptr_t)&ofmt0;
#endif
case 9:
#ifdef HYBRID_MKOBJ
return(uintptr_t)&mkobj_data_ofmt3;
#else
return(uintptr_t)&ofmt3;
#endif
case 10:
#ifdef HYBRID_MKOBJ
return(uintptr_t)&mkobj_data_mfmt1;
#else
return(uintptr_t)&mfmt1;
#endif
case 11:
#ifdef HYBRID_MKOBJ
return(uintptr_t)&mkobj_data_mfmt2;
#else
return(uintptr_t)&mfmt2;
#endif
case 12:
#ifdef HYBRID_MKOBJ
return(uintptr_t)&mkobj_data_obj_state_names;
#else
return(uintptr_t)&obj_state_names;
#endif
default:abort();}}
int64_t probe_constant(int i){switch(i){
case 0:return(int64_t)OBJ_FREE;
case 1:return(int64_t)OBJ_FLOOR;
case 2:return(int64_t)OBJ_CONTAINED;
case 3:return(int64_t)OBJ_INVENT;
case 4:return(int64_t)OBJ_MINVENT;
case 5:return(int64_t)OBJ_MIGRATING;
case 6:return(int64_t)OBJ_BURIED;
case 7:return(int64_t)WEAPON_CLASS;
case 8:return(int64_t)ARMOR_CLASS;
case 9:return(int64_t)FOOD_CLASS;
case 10:return(int64_t)TOOL_CLASS;
case 11:return(int64_t)GEM_CLASS;
case 12:return(int64_t)POTION_CLASS;
case 13:return(int64_t)SCROLL_CLASS;
case 14:return(int64_t)SPBOOK_CLASS;
case 15:return(int64_t)WAND_CLASS;
case 16:return(int64_t)RING_CLASS;
case 17:return(int64_t)AMULET_CLASS;
case 18:return(int64_t)COIN_CLASS;
case 19:return(int64_t)PM_HUMAN;
case 20:return(int64_t)PM_LIZARD;
case 21:return(int64_t)FOOD_RATION;
case 22:return(int64_t)CHEST;
case 23:return(int64_t)BAG_OF_HOLDING;
case 24:return(int64_t)CORPSE;
case 25:return(int64_t)STATUE;
case 26:return(int64_t)GOLD_PIECE;
case 27:return(int64_t)WAN_FIRE;
case 28:return(int64_t)NODIR;
case 29:return(int64_t)ROOM;
case 30:return(int64_t)DOOR;
case 31:return(int64_t)D_CLOSED;
case 32:return(int64_t)GLOB_OF_GRAY_OOZE;
case 33:return(int64_t)GLOB_OF_BLACK_PUDDING;
case 34:return(int64_t)ROT_CORPSE;
case 35:return(int64_t)SHRINK_GLOB;
case 36:return(int64_t)TIMER_OBJECT;
case 37:return(int64_t)W_WEP;
case 38:return(int64_t)W_ARM;
case 39:return(int64_t)FIGURINE;
case 40:return(int64_t)APPLE;
case 41:return(int64_t)STRANGE_OBJECT;
case 42:return(int64_t)POT_OIL;
case 43:return(int64_t)MAXOCLASSES;
case 44:return(int64_t)HORN_OF_PLENTY;
case 45:return(int64_t)SPE_NOVEL;
case 46:return(int64_t)RANDOM_CLASS;
case 47:return(int64_t)SPBOOK_no_NOVEL;
case 48:return(int64_t)DAGGER;
case 49:return(int64_t)LEATHER_ARMOR;
case 50:return(int64_t)ROCK;
case 51:return(int64_t)W_BALL;
case 52:return(int64_t)W_CHAIN;
case 53:return(int64_t)W_SADDLE;
case 54:return(int64_t)OBJ_LUAFREE;
case 55:return(int64_t)OBJ_DELETED;
default:abort();}}
