/* MUSE controlled dependency fixture; no original monster item algorithm fallback. */
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
__typeof__(gv) gv;
__typeof__(svm) svm;
__typeof__(mons) mons={[PM_HUMAN]={.pmidx=PM_HUMAN,.mlet=S_HUMAN,.mflags2=M2_HUMAN,.mmove=12,.difficulty=10}};
__typeof__(u) u;
__typeof__(c_common_strings) c_common_strings={.c_something="fixture",.c_Something="fixture",.c_fakename="fixture"};
__typeof__(gm) gm;
__typeof__(gy) gy;
__typeof__(genders) genders={{.he="their",.him="their"},{.he="their",.him="their"},{.he="their",.him="their"}};
__typeof__(svl) svl;
__typeof__(gt) gt;
__typeof__(svd) svd;
__typeof__(uwep) uwep;
__typeof__(svc) svc;
__typeof__(gz) gz;
__typeof__(iflags) iflags;
__typeof__(uarmu) uarmu;
__typeof__(uarm) uarm;
__typeof__(uarmh) uarmh;
__typeof__(uarms) uarms;
__typeof__(uarmg) uarmg;
__typeof__(uarmc) uarmc;
__typeof__(uarmf) uarmf;
__typeof__(gb) gb;
__typeof__(gc) gc;
__typeof__(uswapwep) uswapwep;
__typeof__(objects) objects;
__typeof__(windowprocs) windowprocs;
__typeof__(flags) flags;
__typeof__(gu) gu;
__typeof__(WIN_MAP) WIN_MAP;
__typeof__(gn) gn;
__typeof__(uskin) uskin;
__typeof__(cg) cg={.zeroobj={.otyp=STRANGE_OBJECT,.quan=9007199254741001L,.spe=-7,.known=1}};
__typeof__(hands_obj) hands_obj;
__typeof__(c_color_names) c_color_names={.c_green="fixture"};
__typeof__(gi) gi;
static struct obj objpool[24];static struct monst monpool[8];static struct trap trappool[8];static struct mextra extras[8];static struct edog dogs[8];static struct attack attack;static stairway stairs;static int objlive[24],objnext=8;static char bufferpool[8192],tracebuf[262144];static size_t traceused;static int result=0,rngvalue=0,query=1,grow=0,reentry=0,pointer_out=0;static unsigned rngcursor;static seenV viz[ROWNO][COLNO];static seenV*vizrows[ROWNO];static jmp_buf escape;
static coord*coordrefs[32];static int coordcount;
static void append(const char*fmt,...){va_list ap;va_start(ap,fmt);int n=vsnprintf(tracebuf+traceused,sizeof tracebuf-traceused,fmt,ap);va_end(ap);if(n<0||(size_t)n>=sizeof tracebuf-traceused)abort();traceused+=(size_t)n;}
static uint64_t token(const void*p){uintptr_t a=(uintptr_t)p;if(!p)return 0;
if(a>=(uintptr_t)&objpool&&a<(uintptr_t)&objpool+sizeof objpool)return 100000+a-(uintptr_t)&objpool;
if(a>=(uintptr_t)&monpool&&a<(uintptr_t)&monpool+sizeof monpool)return 200000+a-(uintptr_t)&monpool;
if(a>=(uintptr_t)&bufferpool&&a<(uintptr_t)&bufferpool+sizeof bufferpool)return 300000+a-(uintptr_t)&bufferpool;
if(a>=(uintptr_t)&trappool&&a<(uintptr_t)&trappool+sizeof trappool)return 400000+a-(uintptr_t)&trappool;
if(a>=(uintptr_t)&extras&&a<(uintptr_t)&extras+sizeof extras)return 500000+a-(uintptr_t)&extras;
if(a>=(uintptr_t)&dogs&&a<(uintptr_t)&dogs+sizeof dogs)return 600000+a-(uintptr_t)&dogs;
if(a>=(uintptr_t)&stairs&&a<(uintptr_t)&stairs+sizeof stairs)return 700000+a-(uintptr_t)&stairs;
if(a>=(uintptr_t)&gv&&a<(uintptr_t)&gv+sizeof gv)return 2000000+a-(uintptr_t)&gv;
if(a>=(uintptr_t)&svm&&a<(uintptr_t)&svm+sizeof svm)return 2100000+a-(uintptr_t)&svm;
if(a>=(uintptr_t)&mons&&a<(uintptr_t)&mons+sizeof mons)return 2200000+a-(uintptr_t)&mons;
if(a>=(uintptr_t)&u&&a<(uintptr_t)&u+sizeof u)return 2300000+a-(uintptr_t)&u;
if(a>=(uintptr_t)&c_common_strings&&a<(uintptr_t)&c_common_strings+sizeof c_common_strings)return 2400000+a-(uintptr_t)&c_common_strings;
if(a>=(uintptr_t)&gm&&a<(uintptr_t)&gm+sizeof gm)return 2500000+a-(uintptr_t)&gm;
if(a>=(uintptr_t)&gy&&a<(uintptr_t)&gy+sizeof gy)return 2600000+a-(uintptr_t)&gy;
if(a>=(uintptr_t)&svl&&a<(uintptr_t)&svl+sizeof svl)return 2800000+a-(uintptr_t)&svl;
if(a>=(uintptr_t)&gt&&a<(uintptr_t)&gt+sizeof gt)return 2900000+a-(uintptr_t)&gt;
if(a>=(uintptr_t)&svd&&a<(uintptr_t)&svd+sizeof svd)return 3000000+a-(uintptr_t)&svd;
if(a>=(uintptr_t)&uwep&&a<(uintptr_t)&uwep+sizeof uwep)return 3100000+a-(uintptr_t)&uwep;
if(a>=(uintptr_t)&svc&&a<(uintptr_t)&svc+sizeof svc)return 3200000+a-(uintptr_t)&svc;
if(a>=(uintptr_t)&gz&&a<(uintptr_t)&gz+sizeof gz)return 3300000+a-(uintptr_t)&gz;
if(a>=(uintptr_t)&iflags&&a<(uintptr_t)&iflags+sizeof iflags)return 3400000+a-(uintptr_t)&iflags;
if(a>=(uintptr_t)&uarmu&&a<(uintptr_t)&uarmu+sizeof uarmu)return 3500000+a-(uintptr_t)&uarmu;
if(a>=(uintptr_t)&uarm&&a<(uintptr_t)&uarm+sizeof uarm)return 3600000+a-(uintptr_t)&uarm;
if(a>=(uintptr_t)&uarmh&&a<(uintptr_t)&uarmh+sizeof uarmh)return 3700000+a-(uintptr_t)&uarmh;
if(a>=(uintptr_t)&uarms&&a<(uintptr_t)&uarms+sizeof uarms)return 3800000+a-(uintptr_t)&uarms;
if(a>=(uintptr_t)&uarmg&&a<(uintptr_t)&uarmg+sizeof uarmg)return 3900000+a-(uintptr_t)&uarmg;
if(a>=(uintptr_t)&uarmc&&a<(uintptr_t)&uarmc+sizeof uarmc)return 4000000+a-(uintptr_t)&uarmc;
if(a>=(uintptr_t)&uarmf&&a<(uintptr_t)&uarmf+sizeof uarmf)return 4100000+a-(uintptr_t)&uarmf;
if(a>=(uintptr_t)&gb&&a<(uintptr_t)&gb+sizeof gb)return 4200000+a-(uintptr_t)&gb;
if(a>=(uintptr_t)&gc&&a<(uintptr_t)&gc+sizeof gc)return 4300000+a-(uintptr_t)&gc;
if(a>=(uintptr_t)&uswapwep&&a<(uintptr_t)&uswapwep+sizeof uswapwep)return 4400000+a-(uintptr_t)&uswapwep;
if(a>=(uintptr_t)&objects&&a<(uintptr_t)&objects+sizeof objects)return 4500000+a-(uintptr_t)&objects;
if(a>=(uintptr_t)&windowprocs&&a<(uintptr_t)&windowprocs+sizeof windowprocs)return 4600000+a-(uintptr_t)&windowprocs;
if(a>=(uintptr_t)&flags&&a<(uintptr_t)&flags+sizeof flags)return 4700000+a-(uintptr_t)&flags;
if(a>=(uintptr_t)&gu&&a<(uintptr_t)&gu+sizeof gu)return 4800000+a-(uintptr_t)&gu;
if(a>=(uintptr_t)&WIN_MAP&&a<(uintptr_t)&WIN_MAP+sizeof WIN_MAP)return 4900000+a-(uintptr_t)&WIN_MAP;
if(a>=(uintptr_t)&gn&&a<(uintptr_t)&gn+sizeof gn)return 5000000+a-(uintptr_t)&gn;
if(a>=(uintptr_t)&uskin&&a<(uintptr_t)&uskin+sizeof uskin)return 5100000+a-(uintptr_t)&uskin;
if(a>=(uintptr_t)&cg&&a<(uintptr_t)&cg+sizeof cg)return 5200000+a-(uintptr_t)&cg;
if(a>=(uintptr_t)&hands_obj&&a<(uintptr_t)&hands_obj+sizeof hands_obj)return 5300000+a-(uintptr_t)&hands_obj;
if(a>=(uintptr_t)&c_color_names&&a<(uintptr_t)&c_color_names+sizeof c_color_names)return 5400000+a-(uintptr_t)&c_color_names;
return a;}
static void hook(void){if(grow){grow=0;emscripten_resize_heap(emscripten_get_heap_size()+65536);}if(reentry){reentry=0;(void)searches_for_item(&monpool[0],&objpool[0]);}}
static void fixture_window(winid id,boolean b){append("window:%d:%d;",id,b);hook();}
static void fixture_cursor(int a,int b){append("cursor:%d:%d;",a,b);hook();}
static struct obj*fixture_newobj(void){if(objnext>=24)abort();struct obj*p=&objpool[objnext++];memset(p,0,sizeof *p);p->quan=1;objlive[p-objpool]=1;return p;}
boolean (objdescr_is)(struct obj * a0,const char * a1){return pointer_out&&strcmp(a1,pointer_out==1?"milky":"smoky")==0;}
boolean (rng_log_enabled)(void){return 1;}
void (rng_log_set_caller)(const char * a0,int a1,const char * a2){append("rngcaller:%s:%d:%s;",a0,a1,a2);}
int (rn2)(int a0){if(a0<=0)abort();int v=rngvalue>=0?rngvalue%a0:(int)(rngcursor++%(unsigned)a0);append("rn2:%d:%d;",a0,v);return v;}
boolean (enexto)(coord * a0,coordxy a1,coordxy a2,struct permonst * a3){a0->x=a1+1;a0->y=a2+1;return query;}
void (m_useup)(struct monst * a0,struct obj * a1){append("useup:%llu:%llu;",(unsigned long long)token(a0),(unsigned long long)token(a1));if(a1->quan>1)a1->quan--;else{objlive[a1-objpool]=0;a1->quan=0;if(a0->minvent==a1)a0->minvent=a1->nobj;if(a0->mw==a1)a0->mw=0;}hook();}
struct monst * (makemon)(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){if(!pointer_out)return 0;monpool[3].data=a0;monpool[3].mx=a1;monpool[3].my=a2;return &monpool[3];}
char * (mon_nam)(struct monst * a0){return "monster";}
char * (rndmonnam)(char * a0){return "hallucination";}
char * (Monnam)(struct monst * a0){return "Monster";}
void (paralyze_monst)(struct monst * a0,int a1){a0->mcanmove=0;a0->mfrozen=a1;append("paralyze:%d;",a1);}
char * (a_monnam)(struct monst * a0){return "a monster";}
void (set_malign)(struct monst * a0){append("set_malign:%lld;",(long long)token(a0));}
void (mongone)(struct monst * a0){append("mongone:%lld;",(long long)token(a0));}
int (d)(int a0,int a1){int v=a0*(1+(rngvalue>=0?rngvalue%a1:0));append("dice:%d:%d:%d;",a0,a1,v);return v;}
char * (xname)(struct obj * a0){return "item";}
char * (an)(const char * a0){return (char*)a0;}
int (dist2)(coordxy a0,coordxy a1,coordxy a2,coordxy a3){return(a0-a2)*(a0-a2)+(a1-a3)*(a1-a3);}
void (monkilled)(struct monst * a0,const char * a1,int a2){append("monkilled:%lld:%s:%lld;",(long long)token(a0),(a1?a1:"NULL"),(long long)a2);}
int (canseemon)(struct monst * a0){return result;}
void (unknow_object)(struct obj * a0){append("unknow_object:%lld;",(long long)token(a0));}
char * (monverbself)(struct monst * a0,char * a1,const char * a2,const char * a3){return "monster uses item";}
char * (doname)(struct obj * a0){return "an item";}
void (stop_occupation)(void){append("stop_occupation:;");}
void (observe_object)(struct obj * a0){append("observe_object:%lld;",(long long)token(a0));}
char * (simpleonames)(struct obj * a0){return "items";}
void (discover_object)(int a0,boolean a1,boolean a2,boolean a3){append("discover_object:%lld:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2,(long long)a3);}
int (sensemon)(struct monst * a0){return 0;}
char * (ansimpleoname)(struct obj * a0){return "an item";}
const char * (singular)(struct obj * a0,char *(*a1)(struct obj *)){return a1(a0);}
boolean (same_race)(struct permonst * a0,struct permonst * a1){append("same_race:%lld:%lld;",(long long)token(a0),(long long)token(a1));return 0;}
void (map_invisible)(coordxy a0,coordxy a1){append("map_invisible:%lld:%lld;",(long long)a0,(long long)a1);}
char * (strsubst)(char * a0,const char * a1,const char * a2){return a0;}
char * (x_monnam)(struct monst * a0,int a1,const char * a2,int a3,boolean a4){return "Monster";}
void (flash_mon)(struct monst * a0){append("flash_mon:%lld;",(long long)token(a0));}
int (pronoun_gender)(struct monst * a0,unsigned int a1){return 0;}
struct obj * (m_carrying)(struct monst * a0,int a1){for(struct obj*p=a0->minvent;p;p=p->nobj)if(p->otyp==a1)return p;return 0;}
int (isok)(coordxy a0,coordxy a1){return a0>0&&a0<COLNO&&a1>=0&&a1<ROWNO;}
boolean (tele_restrict)(struct monst * a0){append("tele_restrict:%lld;",(long long)token(a0));return 0;}
boolean (noteleport_level)(struct monst * a0){return pointer_out==1;}
void (mon_learns_traps)(struct monst * a0,int a1){append("mon_learns_traps:%lld:%lld;",(long long)token(a0),(long long)a1);}
int (mon_has_amulet)(struct monst * a0){append("mon_has_amulet:%lld;",(long long)token(a0));return 0;}
boolean (On_W_tower_level)(d_level * a0){append("On_W_tower_level:%lld;",(long long)token(a0));return 0;}
boolean (rloc)(struct monst * a0,unsigned int a1){append("rloc:%lld:%lld;",(long long)token(a0),(long long)a1);return 0;}
int (mintrap)(struct monst * a0,unsigned int a1){append("mintrap:%lld:%lld;",(long long)token(a0),(long long)a1);return 0;}
boolean (on_level)(d_level * a0,d_level * a1){return a0->dnum==a1->dnum&&a0->dlevel==a1->dlevel;}
boolean (poly_when_stoned)(struct permonst * a0){append("poly_when_stoned:%lld;",(long long)token(a0));return 0;}
boolean (Resists_Elem)(struct monst * a0,int a1){append("Resists_Elem:%lld:%lld;",(long long)token(a0),(long long)a1);return 0;}
boolean (lined_up)(struct monst * a0){return query;}
stairway * (stairway_at)(coordxy a0,coordxy a1){return stairs.sx==a0&&stairs.sy==a1?&stairs:0;}
struct trap * (t_at)(coordxy a0,coordxy a1){for(int i=0;i<8;i++)if(trappool[i].ttyp&&trappool[i].tx==a0&&trappool[i].ty==a1)return &trappool[i];return 0;}
struct obj * (sobj_at)(int a0,coordxy a1,coordxy a2){for(struct obj*p=svl.level.objects[a1][a2];p;p=p->nexthere)if(p->otyp==a0)return p;return 0;}
boolean (onscary)(coordxy a0,coordxy a1,struct monst * a2){append("onscary:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)token(a2));return 0;}
boolean (Can_fall_thru)(d_level * a0){append("Can_fall_thru:%lld;",(long long)token(a0));return 0;}
boolean (Is_botlevel)(d_level * a0){append("Is_botlevel:%lld;",(long long)token(a0));return 0;}
boolean (is_ice)(coordxy a0,coordxy a1){append("is_ice:%lld:%lld;",(long long)a0,(long long)a1);return 0;}
boolean (is_pool)(coordxy a0,coordxy a1){append("is_pool:%lld:%lld;",(long long)a0,(long long)a1);return 0;}
boolean (is_lava)(coordxy a0,coordxy a1){append("is_lava:%lld:%lld;",(long long)a0,(long long)a1);return 0;}
boolean (In_V_tower)(d_level * a0){append("In_V_tower:%lld;",(long long)token(a0));return 0;}
boolean (mon_knows_traps)(struct monst * a0,int a1){append("mon_knows_traps:%lld:%lld;",(long long)token(a0),(long long)a1);return 0;}
int (inhishop)(struct monst * a0){append("inhishop:%lld;",(long long)token(a0));return 0;}
void (unblock_point)(int a0,int a1){append("unblock_point:%lld:%lld;",(long long)a0,(long long)a1);}
void (seetrap)(struct trap * a0){append("seetrap:%lld;",(long long)token(a0));}
int (mon_has_special)(struct monst * a0){append("mon_has_special:%lld;",(long long)token(a0));return 0;}
void (awaken_soldiers)(struct monst * a0){append("awaken_soldiers:%lld;",(long long)token(a0));}
void (monflee)(struct monst * a0,int a1,boolean a2,boolean a3){a0->mflee=1;append("flee:%d:%d:%d;",a1,a2,a3);}
int (bhito)(struct obj * a0,struct obj * a1){append("bhito:%lld:%lld;",(long long)token(a0),(long long)token(a1));return 0;}
struct obj * (splitobj)(struct obj * a0,long a1){append("split:%llu:%ld;",(unsigned long long)token(a0),a1);struct obj*p=fixture_newobj();*p=*a0;p->quan=a1;a0->quan-=a1;p->nobj=0;return p;}
void (extract_from_minvent)(struct monst * a0,struct obj * a1,boolean a2,boolean a3){append("extract:%llu:%llu;",(unsigned long long)token(a0),(unsigned long long)token(a1));if(a0->minvent==a1)a0->minvent=a1->nobj;a1->nobj=0;}
int (random_teleport_level)(void){append("random_teleport_level:;");return 0;}
schar (depth)(d_level * a0){return a0->dlevel;}
void (get_level)(d_level * a0,int a1){a0->dnum=u.uz.dnum;a0->dlevel=pointer_out==2?u.uz.dlevel:a1;append("get_level:%d;",a1);}
xint16 (ledger_no)(d_level * a0){return a0->dlevel;}
void (migrate_to_level)(struct monst * a0,xint16 a1,xint16 a2,coord * a3){append("migrate:%llu:%d:%d;",(unsigned long long)token(a0),a1,a2);}
void (trycall)(struct obj * a0){append("trycall:%lld;",(long long)token(a0));}
void (obfree)(struct obj * a0,struct obj * a1){append("obfree:%llu;",(unsigned long long)token(a0));if(a0>=objpool&&a0<objpool+24)objlive[a0-objpool]=0;}
int (is_drawbridge_wall)(coordxy a0,coordxy a1){append("is_drawbridge_wall:%lld:%lld;",(long long)a0,(long long)a1);return 0;}
boolean (Can_dig_down)(d_level * a0){append("Can_dig_down:%lld;",(long long)token(a0));return 0;}
struct trap * (maketrap)(coordxy a0,coordxy a1,int a2){trappool[0].tx=a0;trappool[0].ty=a1;trappool[0].ttyp=a2;return &trappool[0];}
const char * (surface)(coordxy a0,coordxy a1){return "floor";}
void (fill_pit)(coordxy a0,coordxy a1){append("fill_pit:%lld:%lld;",(long long)a0,(long long)a1);}
void (recalc_block_point)(coordxy a0,coordxy a1){append("recalc_block_point:%lld:%lld;",(long long)a0,(long long)a1);}
int (rnd)(int a0){if(a0<=0)abort();int v=1+(rngvalue>=0?rngvalue%a0:(int)(rngcursor++%(unsigned)a0));append("rnd:%d:%d;",a0,v);return v;}
const char * (locomotion)(const struct permonst * a0,const char * a1){return a1;}
char * (vtense)(const char * a0,const char * a1){return (char*)a1;}
const char * (trapname)(int a0,boolean a1){return "trap";}
void (newsym)(coordxy a0,coordxy a1){append("newsym:%lld:%lld;",(long long)a0,(long long)a1);}
void (place_monster)(struct monst * a0,coordxy a1,coordxy a2){append("place_monster:%lld:%lld:%lld;",(long long)token(a0),(long long)a1,(long long)a2);}
void (worm_move)(struct monst * a0){append("worm_move:%lld;",(long long)token(a0));}
boolean (In_hell)(d_level * a0){append("In_hell:%lld;",(long long)token(a0));return 0;}
xint16 (dunlev)(d_level * a0){return a0->dlevel;}
xint16 (dunlevs_in_dungeon)(d_level * a0){return 20;}
void (maybe_unhide_at)(coordxy a0,coordxy a1){append("maybe_unhide_at:%lld:%lld;",(long long)a0,(long long)a1);}
int (bcsign)(struct obj * a0){return a0->blessed?1:a0->cursed?-1:0;}
int (healmon)(struct monst * a0,int a1,int a2){a0->mhp+=a1;if(a0->mhp>a0->mhpmax)a0->mhp=a0->mhpmax;append("heal:%d:%d;",a1,a2);return a1;}
void (unbless)(struct obj * a0){a0->blessed=0;}
boolean (attacktype)(struct permonst * a0,int a1){append("attacktype:%lld:%lld;",(long long)token(a0),(long long)a1);return 0;}
int (sgn)(int a0){return(a0>0)-(a0<0);}
struct obj * (carrying)(int a0){for(struct obj*p=gi.invent;p;p=p->nobj)if(p->otyp==a0)return p;return 0;}
boolean (linedup_callback)(coordxy a0,coordxy a1,coordxy a2,coordxy a3,boolean (*a4)(coordxy, coordxy)){append("linedcb:%d:%d:%d:%d;",a0,a1,a2,a3);return a4(a2,a3);}
int (xytodir)(int a0,int a1){append("xytodir:%lld:%lld;",(long long)a0,(long long)a1);return 0;}
void (dirtocoord)(coord * a0,int a1){static const coordxy dx[8]={-1,-1,0,1,1,1,0,-1},dy[8]={0,-1,-1,-1,0,1,1,1};a0->x=dx[a1&7];a0->y=dy[a1&7];int id=0;while(id<coordcount&&coordrefs[id]!=a0)id++;if(id==coordcount){if(coordcount==32)abort();coordrefs[coordcount++]=a0;}append("dirtocoord:ref%d:%d:%d:%d;",id,a1,a0->x,a0->y);}
boolean (accessible)(coordxy a0,coordxy a1){return isok(a0,a1)&&levl[a0][a1].typ==ROOM;}
boolean (mon_would_take_item)(struct monst * a0,struct obj * a1){return query;}
boolean (in_your_sanctuary)(struct monst * a0,coordxy a1,coordxy a2){append("in_your_sanctuary:%lld:%lld:%lld;",(long long)token(a0),(long long)a1,(long long)a2);return 0;}
boolean (dmgtype)(struct permonst * a0,int a1){append("dmgtype:%lld:%lld;",(long long)token(a0),(long long)a1);return 0;}
boolean (monnear)(struct monst * a0,coordxy a1,coordxy a2){append("monnear:%lld:%lld:%lld;",(long long)token(a0),(long long)a1,(long long)a2);return 0;}
struct obj * (which_armor)(struct monst * a0,long a1){return pointer_out?&objpool[1]:0;}
boolean (can_blow)(struct monst * a0){return query;}
boolean (hard_helmet)(struct obj * a0){append("hard_helmet:%lld;",(long long)token(a0));return 0;}
boolean (resists_blnd)(struct monst * a0){append("resists_blnd:%lld;",(long long)token(a0));return 0;}
void (seemimic)(struct monst * a0){append("seemimic:%lld;",(long long)token(a0));}
void (monstseesu)(unsigned long a0){append("monstseesu:%lld;",(long long)a0);}
void (shieldeff)(coordxy a0,coordxy a1){append("shieldeff:%lld:%lld;",(long long)a0,(long long)a1);}
void (monstunseesu)(unsigned long a0){append("monstunseesu:%lld;",(long long)a0);}
void (losehp)(int a0,const char * a1,schar a2){append("losehp:%lld:%s:%lld;",(long long)a0,(a1?a1:"NULL"),(long long)a2);}
void (nomul)(int a0){gm.multi=a0;append("nomul:%d;",a0);}
boolean (resists_magm)(struct monst * a0){append("resists_magm:%lld;",(long long)token(a0));return 0;}
int (find_mac)(struct monst * a0){append("find_mac:%lld;",(long long)token(a0));return 0;}
const char * (exclam)(int a0){return "!";}
void (hit)(const char * a0,struct monst * a1,const char * a2){append("hit:%s:%lld:%s;",a0,(long long)token(a1),a2);}
int (resist)(struct monst * a0,char a1,int a2,int a3){append("resist:%lld:%lld:%lld:%lld;",(long long)token(a0),(long long)a1,(long long)a2,(long long)a3);return 0;}
void (miss)(const char * a0,struct monst * a1){append("miss:%s:%lld;",a0,(long long)token(a1));}
void (tele)(void){append("tele:;");}
char * (in_rooms)(coordxy a0,coordxy a1,int a2){return result?"r":"";}
boolean (cancel_monst)(struct monst * a0,struct obj * a1,boolean a2,boolean a3,boolean a4){append("cancel_monst:%lld:%lld:%lld:%lld:%lld;",(long long)token(a0),(long long)token(a1),(long long)a2,(long long)a3,(long long)a4);return 0;}
void (unturn_you)(void){append("unturn_you:;");}
int (unturn_dead)(struct monst * a0){append("unturn_dead:%lld;",(long long)token(a0));return 0;}
void (wakeup)(struct monst * a0,boolean a1){a0->msleeping=0;append("wake:%llu;",(unsigned long long)token(a0));}
boolean (find_drawbridge)(coordxy * a0,coordxy * a1){if(!pointer_out)return 0;*a0+=1;*a1-=1;append("drawbridgeout:%d:%d;",*a0,*a1);return 1;}
void (destroy_drawbridge)(coordxy a0,coordxy a1){append("destroy_drawbridge:%lld:%lld;",(long long)a0,(long long)a1);}
boolean (doorlock)(struct obj * a0,coordxy a1,coordxy a2){if(result){levl[a1][a2].doormask=D_BROKEN;append("doorlock:%d:%d;",a1,a2);}return result;}
void (add_damage)(coordxy a0,coordxy a1,long a2){append("add_damage:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2);}
void (dobuzz)(int a0,int a1,coordxy a2,coordxy a3,int a4,int a5,boolean a6,boolean a7,boolean a8){append("dobuzz:%d:%d:%d:%d:%d:%d:%d:%d:%d;",a0,a1,a2,a3,a4,a5,a6,a7,a8);hook();}
void (buzz)(int a0,int a1,coordxy a2,coordxy a3,int a4,int a5){append("buzz:%d:%d:%d:%d:%d:%d;",a0,a1,a2,a3,a4,a5);hook();}
const char * (ceiling)(coordxy a0,coordxy a1){return "ceiling";}
boolean (closed_door)(coordxy a0,coordxy a1){append("closed_door:%lld:%lld;",(long long)a0,(long long)a1);return 0;}
boolean (drop_boulder_on_monster)(coordxy a0,coordxy a1,boolean a2,boolean a3){append("drop_boulder_on_monster:%lld:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2,(long long)a3);return 0;}
int (distmin)(coordxy a0,coordxy a1,coordxy a2,coordxy a3){int x=abs(a0-a2),y=abs(a1-a3);return x>y?x:y;}
void (drop_boulder_on_player)(boolean a0,boolean a1,boolean a2,boolean a3){append("drop_boulder_on_player:%lld:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2,(long long)a3);}
void (make_blinded)(long a0,boolean a1){u.uprops[BLINDED].intrinsic=a0;append("blind:%ld:%d;",a0,a1);}
int (lightdamage)(struct obj * a0,boolean a1,int a2){append("lightdamage:%lld:%lld:%lld;",(long long)token(a0),(long long)a1,(long long)a2);return 0;}
void (m_throw)(struct monst * a0,coordxy a1,coordxy a2,coordxy a3,coordxy a4,int a5,struct obj * a6){append("m_throw:%lld:%lld:%lld:%lld:%lld:%lld:%lld;",(long long)token(a0),(long long)a1,(long long)a2,(long long)a3,(long long)a4,(long long)a5,(long long)token(a6));}
boolean (wearing_iron_shoes)(struct monst * a0){append("wearing_iron_shoes:%lld;",(long long)token(a0));return 0;}
boolean (canletgo)(struct obj * a0,const char * a1){append("canletgo:%lld:%s;",(long long)token(a0),a1);return 0;}
struct permonst * (rndmonst)(void){return &mons[PM_HUMAN];}
char * (distant_name)(struct obj * a0,char *(*a1)(struct obj *)){return a1(a0);}
void (obj_extract_self)(struct obj * a0){append("extractself:%llu;",(unsigned long long)token(a0));if(a0->where==OBJ_CONTAINED&&a0->ocontainer){struct obj**p=&a0->ocontainer->cobj;while(*p&&*p!=a0)p=&(*p)->nobj;if(*p)*p=a0->nobj;}a0->nobj=0;a0->where=OBJ_FREE;}
int (can_carry)(struct monst * a0,struct obj * a1){return query;}
char * (upstart)(char * a0){return a0;}
void (removed_from_icebox)(struct obj * a0){append("removed_from_icebox:%lld;",(long long)token(a0));}
int (mpickobj)(struct monst * a0,struct obj * a1){a1->nobj=a0->minvent;a0->minvent=a1;a1->where=OBJ_MINVENT;a1->ocarry=a0;append("pickup:%llu:%llu;",(unsigned long long)token(a0),(unsigned long long)token(a1));return 0;}
struct obj * (add_to_container)(struct obj * a0,struct obj * a1){a1->nobj=a0->cobj;a0->cobj=a1;a1->ocontainer=a0;a1->where=OBJ_CONTAINED;append("addcontainer:%llu:%llu;",(unsigned long long)token(a0),(unsigned long long)token(a1));return a1;}
int (weight)(struct obj * a0){return 7;}
boolean (Can_rise_up)(coordxy a0,coordxy a1,d_level * a2){return query;}
struct permonst * (grow_up)(struct monst * a0,struct monst * a1){a0->m_lev++;return a0->data;}
void (mon_set_minvis)(struct monst * a0,boolean a1){append("mon_set_minvis:%lld:%lld;",(long long)token(a0),(long long)a1);}
char * (s_suffix)(const char * a0){return (char*)a0;}
void (mon_adjust_speed)(struct monst * a0,int a1,struct obj * a2){append("mon_adjust_speed:%lld:%lld:%lld;",(long long)token(a0),(long long)a1,(long long)token(a2));}
int (newcham)(struct monst * a0,struct permonst * a1,unsigned int a2){if(a1)a0->data=a1;append("newcham:%llu:%u;",(unsigned long long)token(a1),a2);return 1;}
char * (Some_Monnam)(struct monst * a0){return "A monster";}
char * (the)(const char * a0){return (char*)a0;}
const char * (body_part)(int a0){return "hand";}
char * (makeplural)(const char * a0){return (char*)a0;}
int (welded)(struct obj * a0){append("welded:%lld;",(long long)token(a0));return 0;}
boolean (undiscovered_artifact)(xint16 a0){append("undiscovered_artifact:%lld;",(long long)a0);return 0;}
boolean (mon_hates_silver)(struct monst * a0){append("mon_hates_silver:%lld;",(long long)token(a0));return 0;}
void (remove_worn_item)(struct obj * a0,boolean a1){append("remove_worn_item:%lld:%lld;",(long long)token(a0),(long long)a1);}
void (freeinv)(struct obj * a0){append("freeinv:%lld;",(long long)token(a0));}
void (place_object)(struct obj * a0,coordxy a1,coordxy a2){append("place_object:%lld:%lld:%lld;",(long long)token(a0),(long long)a1,(long long)a2);}
void (dropy)(struct obj * a0){append("dropy:%lld;",(long long)token(a0));}
char * (noit_mon_nam)(struct monst * a0){return "monster";}
void (cls)(void){append("cls:;");}
int (rn2_on_display_rng)(int a0){int v=a0?result%a0:0;append("display:%d:%d;",a0,v);return v;}
void (show_glyph)(coordxy a0,coordxy a1,int a2){append("show_glyph:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2);}
int (mon_visible)(struct monst * a0){return result;}
boolean (In_mines)(d_level * a0){append("In_mines:%lld;",(long long)token(a0));return 0;}
void (docrt)(void){append("docrt:;");}
boolean (unconscious)(void){append("unconscious:;");return 0;}
boolean (arti_reflects)(struct obj * a0){append("arti_reflects:%lld;",(long long)token(a0));return 0;}
int (dog_nutrition)(struct monst * a0,struct obj * a1){a0->meating=3;return 7;}
void (xkilled)(struct monst * a0,int a1){append("xkilled:%lld:%lld;",(long long)token(a0),(long long)a1);}
void (mondead)(struct monst * a0){append("mondead:%lld;",(long long)token(a0));}
boolean (mwelded)(struct obj * a0){append("mwelded:%lld;",(long long)token(a0));return 0;}
struct attack * (attacktype_fordmg)(struct permonst * a0,int a1,int a2){return pointer_out?&attack:0;}
const char * (hcolor)(const char * a0){return a0;}
int (zhitm)(struct monst * a0,int a1,int a2,struct obj ** a3){*a3=&objpool[7];append("zhitm:%llu:%d:%d:%llu;",(unsigned long long)token(a0),a1,a2,(unsigned long long)token(*a3));a0->mhp-=result;hook();return result;}
void (explode)(coordxy a0,coordxy a1,int a2,int a3,char a4,int a5){append("explode:%lld:%lld:%lld:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2,(long long)a3,(long long)a4,(long long)a5);}
void (begin_burn)(struct obj * a0,boolean a1){append("begin_burn:%lld:%lld;",(long long)token(a0),(long long)a1);}
boolean (is_fainted)(void){append("is_fainted:;");return 0;}
void (Norep)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("Norep:%s;",b);}
void (You)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("You:%s;",b);}
void (You_feel)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("You_feel:%s;",b);}
void (You_hear)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("You_hear:%s;",b);}
void (impossible)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("impossible:%s;",b);}
void (panic)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("panic:%s;",b);longjmp(escape,1);}
void (pline)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("pline:%s;",b);}
void (pline_The)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("pline_The:%s;",b);}
void (pline_mon)(struct monst * a0,const char * a1,...){char b[4096];va_list ap;va_start(ap,a1);vsnprintf(b,sizeof b,a1,ap);va_end(ap);append("pline_mon:%llu:%s;",(unsigned long long)token(a0),b);}
void (urgent_pline)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("urgent_pline:%s;",b);}
void (verbalize)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("verbalize:%s;",b);}
void (nh_snprintf)(const char*f,int line,char*out,size_t n,const char*fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(out,n,fmt,ap);va_end(ap);append("snprintf:%s:%d:%zu;",f,line,n);}
#ifdef HYBRID_MUSE
#include "../nethack-c/wasm/tu-fragments/muse-types.h"
extern int teleport_muse_precheck(struct monst * mon,struct obj * obj);
#define precheck teleport_muse_precheck
extern void teleport_muse_mzapwand(struct monst * mtmp,struct obj * otmp,boolean self);
#define mzapwand teleport_muse_mzapwand
extern void teleport_muse_mplayhorn(struct monst * mtmp,struct obj * otmp,boolean self);
#define mplayhorn teleport_muse_mplayhorn
extern void teleport_muse_mreadmsg(struct monst * mtmp,struct obj * otmp);
#define mreadmsg teleport_muse_mreadmsg
extern void teleport_muse_mquaffmsg(struct monst * mtmp,struct obj * otmp);
#define mquaffmsg teleport_muse_mquaffmsg
extern boolean teleport_muse_m_use_healing(struct monst * mtmp);
#define m_use_healing teleport_muse_m_use_healing
extern boolean teleport_muse_m_sees_sleepy_soldier(struct monst * mtmp);
#define m_sees_sleepy_soldier teleport_muse_m_sees_sleepy_soldier
extern void teleport_muse_m_tele(struct monst * mtmp,boolean vismon,boolean oseen,int how);
#define m_tele teleport_muse_m_tele
extern boolean teleport_muse_m_next2m(struct monst * mtmp);
#define m_next2m teleport_muse_m_next2m
extern void teleport_muse_reveal_trap(struct trap * t,boolean seeit);
#define reveal_trap teleport_muse_reveal_trap
extern int teleport_muse_mon_escape(struct monst * mtmp,boolean vismon);
#define mon_escape teleport_muse_mon_escape
extern boolean teleport_muse_linedup_chk_corpse(coordxy x,coordxy y);
#define linedup_chk_corpse teleport_muse_linedup_chk_corpse
extern void teleport_muse_m_use_undead_turning(struct monst * mtmp,struct obj * obj);
#define m_use_undead_turning teleport_muse_m_use_undead_turning
extern boolean teleport_muse_hero_behind_chokepoint(struct monst * mtmp);
#define hero_behind_chokepoint teleport_muse_hero_behind_chokepoint
extern boolean teleport_muse_mon_has_friends(struct monst * mtmp);
#define mon_has_friends teleport_muse_mon_has_friends
extern boolean teleport_muse_mon_likes_objpile_at(struct monst * mtmp,coordxy x,coordxy y);
#define mon_likes_objpile_at teleport_muse_mon_likes_objpile_at
extern int teleport_muse_mbhitm(struct monst * mtmp,struct obj * otmp);
#define mbhitm teleport_muse_mbhitm
extern boolean teleport_muse_fhito_loc(struct obj * obj,coordxy tx,coordxy ty,int (*fhito)(struct obj *, struct obj *));
#define fhito_loc teleport_muse_fhito_loc
extern void teleport_muse_mbhit(struct monst * mon,int range,int (*fhitm)(struct monst *, struct obj *),int (*fhito)(struct obj *, struct obj *),struct obj * obj);
#define mbhit teleport_muse_mbhit
extern void teleport_muse_buzz_force_miss(int type,int nd,coordxy sx,coordxy sy,int dx,int dy);
#define buzz_force_miss teleport_muse_buzz_force_miss
extern struct permonst * teleport_muse_muse_newcham_mon(struct monst * mon);
#define muse_newcham_mon teleport_muse_muse_newcham_mon
extern int teleport_muse_mloot_container(struct monst * mon,struct obj * container,boolean vismon);
#define mloot_container teleport_muse_mloot_container
extern void teleport_muse_you_aggravate(struct monst * mtmp);
#define you_aggravate teleport_muse_you_aggravate
extern void teleport_muse_mon_consume_unstone(struct monst * mon,struct obj * obj,boolean by_you,boolean stoning);
#define mon_consume_unstone teleport_muse_mon_consume_unstone
extern boolean teleport_muse_cures_stoning(struct monst * mon,struct obj * obj,boolean tinok);
#define cures_stoning teleport_muse_cures_stoning
extern boolean teleport_muse_mcould_eat_tin(struct monst * mon);
#define mcould_eat_tin teleport_muse_mcould_eat_tin
extern boolean teleport_muse_muse_unslime(struct monst * mon,struct obj * obj,struct trap * trap,boolean by_you);
#define muse_unslime teleport_muse_muse_unslime
extern int teleport_muse_cures_sliming(struct monst * mon,struct obj * obj);
#define cures_sliming teleport_muse_cures_sliming
extern boolean teleport_muse_green_mon(struct monst * mon);
#define green_mon teleport_muse_green_mon
#else
#include "../.cache/wasm64-build/tree/src/muse.c"
#define TELEPORT_MUSE_TYPES_H
#define teleport_muse_mbhitm mbhitm
#define teleport_muse_linedup_chk_corpse linedup_chk_corpse
#define teleport_muse_buzz_force_miss buzz_force_miss
#endif
#include "../nethack-c/wasm/tu-fragments/muse-support.c"
#include "tu-muse-layout.h"
uintptr_t probe_pool(int kind,int i){return(uintptr_t)(kind==0?(void*)&objpool[i]:kind==1?(void*)&monpool[i]:kind==2?(void*)&bufferpool[i]:kind==3?(void*)&trappool[i]:kind==4?(void*)&extras[i]:kind==5?(void*)&dogs[i]:(void*)&stairs);}
int probe_live(int i){return objlive[i];}
int probe_layout_count(void){return sizeof muse_layout/sizeof muse_layout[0];}
const char*probe_layout_name(int i){return muse_layout[i].name;}
int64_t probe_layout_value(int i){return(int64_t)muse_layout[i].value;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
const char*probe_trace(void){return tracebuf;}
void probe_option(int k,int64_t v){switch(k){case 0:result=v;break;case 1:rngvalue=v;rngcursor=0;break;case 2:query=v;break;case 3:grow=v;break;case 4:reentry=v;break;case 5:pointer_out=v;break;default:abort();}}
uintptr_t probe_function(int i){switch(i){
case 0:return(uintptr_t)doname;
case 1:return(uintptr_t)ansimpleoname;
case 2:return(uintptr_t)mbhitm;
case 3:return(uintptr_t)bhito;
case 4:return(uintptr_t)linedup_chk_corpse;
case 5:return(uintptr_t)buzz;
case 6:return(uintptr_t)buzz_force_miss;
case 7:return(uintptr_t)xname;
case 8:return(uintptr_t)rn2_on_display_rng;
case 20:return(uintptr_t)fixture_window;case 21:return(uintptr_t)fixture_cursor;default:abort();}}
uint64_t probe_action(int which,uint64_t a,uint64_t b,uint64_t c,uint64_t d,uint64_t e,uint64_t f){if(setjmp(escape))return 0x70000000;switch(which){
case 0:return(uint64_t)(uintptr_t)(precheck((struct monst *)(uintptr_t)a,(struct obj *)(uintptr_t)b));
case 1:mzapwand((struct monst *)(uintptr_t)a,(struct obj *)(uintptr_t)b,(boolean)(uintptr_t)c);return 0;
case 2:mplayhorn((struct monst *)(uintptr_t)a,(struct obj *)(uintptr_t)b,(boolean)(uintptr_t)c);return 0;
case 3:mreadmsg((struct monst *)(uintptr_t)a,(struct obj *)(uintptr_t)b);return 0;
case 4:mquaffmsg((struct monst *)(uintptr_t)a,(struct obj *)(uintptr_t)b);return 0;
case 5:return(uint64_t)(uintptr_t)(m_use_healing((struct monst *)(uintptr_t)a));
case 6:return(uint64_t)(uintptr_t)(m_sees_sleepy_soldier((struct monst *)(uintptr_t)a));
case 7:m_tele((struct monst *)(uintptr_t)a,(boolean)(uintptr_t)b,(boolean)(uintptr_t)c,(int)(uintptr_t)d);return 0;
case 8:return(uint64_t)(uintptr_t)(m_next2m((struct monst *)(uintptr_t)a));
case 9:return(uint64_t)(uintptr_t)(find_defensive((struct monst *)(uintptr_t)a,(boolean)(uintptr_t)b));
case 10:reveal_trap((struct trap *)(uintptr_t)a,(boolean)(uintptr_t)b);return 0;
case 11:return(uint64_t)(uintptr_t)(mon_escape((struct monst *)(uintptr_t)a,(boolean)(uintptr_t)b));
case 12:return(uint64_t)(uintptr_t)(use_defensive((struct monst *)(uintptr_t)a));
case 13:return(uint64_t)(uintptr_t)(rnd_defensive_item((struct monst *)(uintptr_t)a));
case 14:return(uint64_t)(uintptr_t)(linedup_chk_corpse((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b));
case 15:m_use_undead_turning((struct monst *)(uintptr_t)a,(struct obj *)(uintptr_t)b);return 0;
case 16:return(uint64_t)(uintptr_t)(hero_behind_chokepoint((struct monst *)(uintptr_t)a));
case 17:return(uint64_t)(uintptr_t)(mon_has_friends((struct monst *)(uintptr_t)a));
case 18:return(uint64_t)(uintptr_t)(mon_likes_objpile_at((struct monst *)(uintptr_t)a,(coordxy)(uintptr_t)b,(coordxy)(uintptr_t)c));
case 19:return(uint64_t)(uintptr_t)(find_offensive((struct monst *)(uintptr_t)a));
case 20:return(uint64_t)(uintptr_t)(mbhitm((struct monst *)(uintptr_t)a,(struct obj *)(uintptr_t)b));
case 21:return(uint64_t)(uintptr_t)(fhito_loc((struct obj *)(uintptr_t)a,(coordxy)(uintptr_t)b,(coordxy)(uintptr_t)c,(int (*)(struct obj *, struct obj *))(uintptr_t)d));
case 22:mbhit((struct monst *)(uintptr_t)a,(int)(uintptr_t)b,(int (*)(struct monst *, struct obj *))(uintptr_t)c,(int (*)(struct obj *, struct obj *))(uintptr_t)d,(struct obj *)(uintptr_t)e);return 0;
case 23:buzz_force_miss((int)(uintptr_t)a,(int)(uintptr_t)b,(coordxy)(uintptr_t)c,(coordxy)(uintptr_t)d,(int)(uintptr_t)e,(int)(uintptr_t)f);return 0;
case 24:return(uint64_t)(uintptr_t)(use_offensive((struct monst *)(uintptr_t)a));
case 25:return(uint64_t)(uintptr_t)(rnd_offensive_item((struct monst *)(uintptr_t)a));
case 26:return(uint64_t)(uintptr_t)(find_misc((struct monst *)(uintptr_t)a));
case 27:return(uint64_t)(uintptr_t)(muse_newcham_mon((struct monst *)(uintptr_t)a));
case 28:return(uint64_t)(uintptr_t)(mloot_container((struct monst *)(uintptr_t)a,(struct obj *)(uintptr_t)b,(boolean)(uintptr_t)c));
case 29:return(uint64_t)(uintptr_t)(use_misc((struct monst *)(uintptr_t)a));
case 30:you_aggravate((struct monst *)(uintptr_t)a);return 0;
case 31:return(uint64_t)(uintptr_t)(rnd_misc_item((struct monst *)(uintptr_t)a));
case 32:return(uint64_t)(uintptr_t)(searches_for_item((struct monst *)(uintptr_t)a,(struct obj *)(uintptr_t)b));
case 33:return(uint64_t)(uintptr_t)(mon_reflects((struct monst *)(uintptr_t)a,(const char *)(uintptr_t)b));
case 34:return(uint64_t)(uintptr_t)(ureflects((const char *)(uintptr_t)a,(const char *)(uintptr_t)b));
case 35:mcureblindness((struct monst *)(uintptr_t)a,(boolean)(uintptr_t)b);return 0;
case 36:return(uint64_t)(uintptr_t)(munstone((struct monst *)(uintptr_t)a,(boolean)(uintptr_t)b));
case 37:mon_consume_unstone((struct monst *)(uintptr_t)a,(struct obj *)(uintptr_t)b,(boolean)(uintptr_t)c,(boolean)(uintptr_t)d);return 0;
case 38:return(uint64_t)(uintptr_t)(cures_stoning((struct monst *)(uintptr_t)a,(struct obj *)(uintptr_t)b,(boolean)(uintptr_t)c));
case 39:return(uint64_t)(uintptr_t)(mcould_eat_tin((struct monst *)(uintptr_t)a));
case 40:return(uint64_t)(uintptr_t)(munslime((struct monst *)(uintptr_t)a,(boolean)(uintptr_t)b));
case 41:return(uint64_t)(uintptr_t)(muse_unslime((struct monst *)(uintptr_t)a,(struct obj *)(uintptr_t)b,(struct trap *)(uintptr_t)c,(boolean)(uintptr_t)d));
case 42:return(uint64_t)(uintptr_t)(cures_sliming((struct monst *)(uintptr_t)a,(struct obj *)(uintptr_t)b));
case 43:return(uint64_t)(uintptr_t)(green_mon((struct monst *)(uintptr_t)a));
default:abort();}}
size_t probe_pointer_offset(int kind,int field){switch(kind){case 0:switch(field){case 0:return offsetof(struct obj,nobj);case 1:return offsetof(struct obj,v);case 2:return offsetof(struct obj,cobj);case 3:return offsetof(struct obj,oextra);}break;case 1:switch(field){case 0:return offsetof(struct monst,nmon);case 1:return offsetof(struct monst,data);case 2:return offsetof(struct monst,mextra);}break;}abort();}
void probe_reset(void){traceused=0;tracebuf[0]=0;coordcount=0;objnext=8;memset(&gi,0,sizeof gi);result=0;rngvalue=0;rngcursor=0;query=1;grow=reentry=pointer_out=0;memset(objpool,0,sizeof objpool);memset(monpool,0,sizeof monpool);memset(trappool,0,sizeof trappool);memset(extras,0,sizeof extras);memset(dogs,0,sizeof dogs);memset(&stairs,0,sizeof stairs);memset(bufferpool,0,sizeof bufferpool);memset(viz,0,sizeof viz);for(int y=0;y<ROWNO;y++)vizrows[y]=viz[y];
memset((void*)&gv,0,sizeof gv);
memset((void*)&svm,0,sizeof svm);
memset((void*)&u,0,sizeof u);
memset((void*)&gm,0,sizeof gm);
memset((void*)&gy,0,sizeof gy);
memset((void*)&svl,0,sizeof svl);
memset((void*)&gt,0,sizeof gt);
memset((void*)&svd,0,sizeof svd);
memset((void*)&uwep,0,sizeof uwep);
memset((void*)&svc,0,sizeof svc);
memset((void*)&gz,0,sizeof gz);
memset((void*)&iflags,0,sizeof iflags);
memset((void*)&uarmu,0,sizeof uarmu);
memset((void*)&uarm,0,sizeof uarm);
memset((void*)&uarmh,0,sizeof uarmh);
memset((void*)&uarms,0,sizeof uarms);
memset((void*)&uarmg,0,sizeof uarmg);
memset((void*)&uarmc,0,sizeof uarmc);
memset((void*)&uarmf,0,sizeof uarmf);
memset((void*)&gb,0,sizeof gb);
memset((void*)&gc,0,sizeof gc);
memset((void*)&uswapwep,0,sizeof uswapwep);
memset((void*)&objects,0,sizeof objects);
memset((void*)&windowprocs,0,sizeof windowprocs);
memset((void*)&flags,0,sizeof flags);
memset((void*)&gu,0,sizeof gu);
memset((void*)&WIN_MAP,0,sizeof WIN_MAP);
memset((void*)&gn,0,sizeof gn);
memset((void*)&uskin,0,sizeof uskin);
memset((void*)&hands_obj,0,sizeof hands_obj);
for(int i=0;i<NUMMONS;i++){mons[i].mlet=0;mons[i].mflags1=mons[i].mflags2=0;mons[i].mcolor=0;mons[i].difficulty=10;mons[i].mmove=12;}mons[PM_HUMAN].mlet=S_HUMAN;mons[PM_HUMAN].mflags2=M2_HUMAN;for(int i=0;i<NUM_OBJECTS;i++){objects[i].oc_class=FOOD_CLASS;objects[i].oc_descr_idx=i;}for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++){levl[x][y].typ=ROOM;levl[x][y].glyph=GLYPH_NOTHING;}gv.viz_array=vizrows;windowprocs.win_display_nhwindow=fixture_window;windowprocs.win_cliparound=fixture_cursor;u.ux=u.uy=10;u.uz.dnum=1;u.uz.dlevel=5;u.ulevel=10;u.uhp=u.uhpmax=20;u.uhs=NOT_HUNGRY;u.umonnum=u.umonster=PM_HUMAN;gy.youmonst.data=&mons[PM_HUMAN];gu.urace.noun="human";gu.urace.adj="human";gu.urace.mnum=PM_HUMAN;gu.urace.selfmask=M2_HUMAN;for(int i=0;i<24;i++){objpool[i].otyp=CORPSE;objpool[i].oclass=FOOD_CLASS;objpool[i].corpsenm=PM_LIZARD;objpool[i].quan=1;objpool[i].spe=2;objpool[i].where=OBJ_FLOOR;objpool[i].ox=11;objpool[i].oy=10;objlive[i]=1;}for(int i=0;i<8;i++){monpool[i].data=&mons[PM_HUMAN];monpool[i].mx=11+i;monpool[i].my=10;monpool[i].mhp=monpool[i].mhpmax=20;monpool[i].m_lev=10;monpool[i].mcanmove=monpool[i].mcansee=1;monpool[i].cham=NON_PM;}svl.level.monsters[11][10]=&monpool[0];}
static const char*fixture_string(int i){switch(i){
case 0:return "fixture";
case 1:return "their";
case 2:return "human";
case 3:return "monster";
case 4:return "Monster";
case 5:return "an item";
case 6:return "item";
case 7:return "items";
case 8:return "a monster";
case 9:return "A monster";
case 10:return "hallucination";
case 11:return "floor";
case 12:return "ceiling";
case 13:return "trap";
case 14:return "hand";
case 15:return "!";
case 16:return "r";
case 17:return "";
default:return 0;}}
const char*probe_string(int i){const char*p=fixture_string(i);if(p)return p;i-=18;
#ifndef HYBRID_MUSE
switch(i){
case 0:return "";
case 1:return "%s";
case 2:return "%s %s %s %s fire trap!";
case 3:return "%s %s %s directed at you!";
case 4:return "%s %s %s.";
case 5:return "%s %s into a %s!";
case 6:return "%s %s onto a %s!";
case 7:return "%s %s through...";
case 8:return "%s %s.";
case 9:return "%s body takes on a %s transparency.";
case 10:return "%s briefly seems to be transparent.";
case 11:return "%s can see again.";
case 12:return "%s crash through the %s.";
case 13:return "%s deliberately %s onto a %s!";
case 14:return "%s dies!";
case 15:return "%s drinks %s!";
case 16:return "%s escapes %sstairs!";
case 17:return "%s escapes down the ladder!";
case 18:return "%s escapes downstairs!";
case 19:return "%s escapes the dungeon!";
case 20:return "%s escapes up the ladder!";
case 21:return "%s escapes upstairs!";
case 22:return "%s fails to wrap around %s.";
case 23:return "%s flicks a bullwhip towards your %s!";
case 24:return "%s has a very bad case of stomach acid.";
case 25:return "%s has made a hole in the %s.";
case 26:return "%s has made a pit in the %s.";
case 27:return "%s here is too hard to dig in.";
case 28:return "%s hurls %s!";
case 29:return "%s ignites %s.";
case 30:return "%s is %s by the fire!";
case 31:return "%s is burned%s";
case 32:return "%s is frightened to death, and unable to move.";
case 33:return "%s looks better.";
case 34:return "%s looks completely healed.";
case 35:return "%s looks much better.";
case 36:return "%s looks uneasy.";
case 37:return "%s plays %s!";
case 38:return "%s quaffs a burning %s";
case 39:return "%s reads %s!";
case 40:return "%s removes %s from %s.";
case 41:return "%s removes %s.";
case 42:return "%s resists the magic!";
case 43:return "%s rises up, through the %s!";
case 44:return "%s rumbles %s %s!";
case 45:return "%s rumbles in the middle of nowhere!";
case 46:return "%s rummages through %s.";
case 47:return "%s seems disoriented for a moment.";
case 48:return "%s seems limber!";
case 49:return "%s seems more experienced.";
case 50:return "%s seems steadier now.";
case 51:return "%s seems very disoriented for a moment.";
case 52:return "%s shudders for a moment.";
case 53:return "%s slime is burned away!";
case 54:return "%s snatches %s!";
case 55:return "%s speaks.";
case 56:return "%s starts turning %s.";
case 57:return "%s suddenly appears!";
case 58:return "%s suddenly mutates!";
case 59:return "%s takes a picture of you with %s!";
case 60:return "%s triggers %s fire trap!";
case 61:return "%s uses a unicorn horn!";
case 62:return "%s vanishes.";
case 63:return "%s wanted to perform action %d?";
case 64:return "%s welded to your %s%c";
case 65:return "%s with %s!";
case 66:return "%s wraps around %s you're wielding!";
case 67:return "%s yanks %s from your %s!";
case 68:return "%s yanks %s to the %s!";
case 69:return "%s zaps %s!";
case 70:return "%s zaps %s, which suddenly explodes!";
case 71:return "%s!";
case 72:return "%s.";
case 73:return "A whip";
case 74:return "Aggravated, you are jolted into full consciousness.";
case 75:return "As %s climbs the stairs, a mysterious force momentarily surrounds %s...";
case 76:return "As %s opens the bottle, an enormous %s emerges!";
case 77:return "Being confused, %s mispronounces the magic words...";
case 78:return "Boing!";
case 79:return "For some reason, %s presence is known to you.";
case 80:return "In a cloud of smoke, %s emerges!";
case 81:return "It is";
case 82:return "It is about time.";
case 83:return "Mon zapping wand with %d charges?";
case 84:return "No need for unicorn horn?";
case 85:return "Oh, what a pretty fire!";
case 86:return "Say cheese!";
case 87:return "Suddenly you cannot see %s.";
case 88:return "The bullwhip";
case 89:return "The potion turns out to be empty.";
case 90:return "They are";
case 91:return "What a pity - %s just ruined a future piece of art!";
case 92:return "You freed me!";
case 93:return "a";
case 94:return "a %s directed at";
case 95:return "a %s zap.";
case 96:return "a bugle playing reveille!";
case 97:return "a chugging sound.";
case 98:return "a horn being played %s.";
case 99:return "a zap and an explosion %s.";
case 100:return "above";
case 101:return "aggravated at %s.";
case 102:return "amulet";
case 103:return "are blinded by the flash of light!";
case 104:return "armor";
case 105:return "around";
case 106:return "attempting to incant";
case 107:return "breath";
case 108:return "bugle";
case 109:return "chewing";
case 110:return "container";
case 111:return "destroyed";
case 112:return "digging ray is ineffective.";
case 113:return "distant";
case 114:return "dives";
case 115:return "down";
case 116:return "drinking";
case 117:return "eats";
case 118:return "falls";
case 119:return "find_defensive";
case 120:return "find_misc";
case 121:return "find_offensive";
case 122:return "fire";
case 123:return "fire on";
case 124:return "ghost";
case 125:return "hidden trap";
case 126:return "in the distance";
case 127:return "incant";
case 128:return "into ooze";
case 129:return "jump";
case 130:return "killed";
case 131:return "lizard corpse";
case 132:return "luster";
case 133:return "m_tele";
case 134:return "mbhitm";
case 135:return "medallion";
case 136:return "milky";
case 137:return "mloot_container";
case 138:return "mon_consume_unstone";
case 139:return "move";
case 140:return "mreadmsg";
case 141:return "munslime";
case 142:return "muse.c";
case 143:return "muse_unslime";
case 144:return "nearby";
case 145:return "normal";
case 146:return "onto";
case 147:return "opens and eats the contents of";
case 148:return "over";
case 149:return "play";
case 150:return "plays";
case 151:return "potioh of extra healing";
case 152:return "potioh of full healing";
case 153:return "potioh of healing";
case 154:return "potion of gain level";
case 155:return "potion of invisibility";
case 156:return "potion of polymorph";
case 157:return "potion of speed";
case 158:return "precheck";
case 159:return "quaffs";
case 160:return "reading %s";
case 161:return "reading a scroll labeled";
case 162:return "rnd_defensive_item";
case 163:return "rnd_misc_item";
case 164:return "rnd_offensive_item";
case 165:return "scales";
case 166:return "scroll of create monster";
case 167:return "scroll of teleportation";
case 168:return "shield";
case 169:return "smoky";
case 170:return "strange";
case 171:return "the";
case 172:return "tip of %s's horn glows!";
case 173:return "up";
case 174:return "use_defensive";
case 175:return "use_defensive: no %s";
case 176:return "use_misc";
case 177:return "use_misc: no %s";
case 178:return "use_offensive";
case 179:return "wand";
case 180:return "wand hits you!";
case 181:return "wand misses you.";
case 182:return "wand of create monster";
case 183:return "wand of digging";
case 184:return "wand of polymorph";
case 185:return "wand of speed monster";
case 186:return "wand of teleportation";
case 187:return "wand of undead turning";
case 188:return "weapon";
case 189:return "whip slips free.";
case 190:return "xobj != NULL";
case 191:return "zap";
default:return 0;}
#else
return 0;
#endif
}
int probe_string_count(void){return 18
#ifndef HYBRID_MUSE
+192
#endif
;}
size_t probe_string_capacity(int i){const char*p=probe_string(i);return p?strlen(p)+1:0;}

/* Native header constants and reference-only source choice values. */
int64_t probe_constant(int i){switch(i){
case 0:return(int64_t)WAND_CLASS;
case 1:return(int64_t)TOOL_CLASS;
case 2:return(int64_t)POTION_CLASS;
case 3:return(int64_t)SCROLL_CLASS;
case 4:return(int64_t)FOOD_CLASS;
case 5:return(int64_t)OBJ_MINVENT;
case 6:return(int64_t)OBJ_CONTAINED;
case 7:return(int64_t)OBJ_FLOOR;
case 8:return(int64_t)D_CLOSED;
case 9:return(int64_t)D_LOCKED;
case 10:return(int64_t)D_BROKEN;
case 11:return(int64_t)D_ISOPEN;
case 12:return(int64_t)ROOM;
case 13:return(int64_t)DOOR;
case 14:return(int64_t)SDOOR;
case 15:return(int64_t)FIRE_TRAP;
case 16:return(int64_t)TELEP_TRAP;
case 17:return(int64_t)PIT;
case 18:return(int64_t)STAIRS;
case 19:return(int64_t)M1_NOHANDS;
case 20:return(int64_t)M1_ANIMAL;
case 21:return(int64_t)M1_ACID;
case 22:return(int64_t)REFLECTING;
case 23:return(int64_t)W_ARMS;
case 24:return(int64_t)W_AMUL;
case 25:return(int64_t)W_ARM;
case 26:return(int64_t)STRAT_WAITFORU;
case 27:return(int64_t)TIMEOUT;
case 28:return(int64_t)IN_SIGHT;
case 29:return(int64_t)COULD_SEE;
case 30:return(int64_t)PM_LIZARD;
case 31:return(int64_t)PM_HUMAN;
default:abort();}}
int probe_choice(int i){
#ifndef HYBRID_MUSE
switch(i){
case 0:return MUSE_POT_HEALING;
case 1:return MUSE_POT_EXTRA_HEALING;
case 2:return MUSE_POT_FULL_HEALING;
case 3:return MUSE_WAN_CREATE_MONSTER;
case 4:return MUSE_SCR_CREATE_MONSTER;
case 5:return MUSE_UNICORN_HORN;
case 6:return MUSE_UPSTAIRS;
case 7:return MUSE_WAN_FIRE;
case 8:return MUSE_WAN_COLD;
case 9:return MUSE_WAN_STRIKING;
case 10:return MUSE_FIRE_HORN;
case 11:return MUSE_WAN_UNDEAD_TURNING;
case 12:return MUSE_POT_GAIN_LEVEL;
case 13:return MUSE_POT_INVISIBILITY;
case 14:return MUSE_POT_SPEED;
case 15:return MUSE_WAN_POLYMORPH;
case 16:return MUSE_POT_POLYMORPH;
case 17:return MUSE_BAG;
case 18:return MUSE_BULLWHIP;
default:abort();}
#else
return 0;
#endif
}
void probe_setup(int k,int64_t v){switch(k){case 0:objpool[4].otyp=CHEST;objpool[4].cobj=&objpool[0];objpool[4].where=OBJ_MINVENT;objpool[4].ocarry=&monpool[0];for(int i=0;i<3;i++){objpool[i].nobj=i<2?&objpool[i+1]:0;objpool[i].where=OBJ_CONTAINED;objpool[i].ocontainer=&objpool[4];}monpool[0].minvent=&objpool[4];break;case 1:monpool[0].mextra=&extras[0];extras[0].edog=&dogs[0];dogs[0].hungrytime=v;monpool[0].mtame=3;break;case 2:stairs.sx=11;stairs.sy=10;stairs.up=1;stairs.tolev=u.uz;levl[11][10].typ=STAIRS;break;case 3:for(int y=0;y<ROWNO;y++)for(int x=0;x<COLNO;x++)viz[y][x]=v;break;default:abort();}}
