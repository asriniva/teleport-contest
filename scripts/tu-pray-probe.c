/* PRAY controlled world/dependency fixture; no prayer/sacrifice fallback. */
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
__typeof__(u) u;
__typeof__(svl) svl;
__typeof__(gy) gy;
__typeof__(uarmf) uarmf;
__typeof__(uleft) uleft;
__typeof__(uright) uright;
__typeof__(uwep) uwep;
__typeof__(ublindf) ublindf;
__typeof__(uball) uball;
__typeof__(uarmg) uarmg;
__typeof__(gi) gi;
__typeof__(objects) objects;
__typeof__(uarms) uarms;
__typeof__(uarmc) uarmc;
__typeof__(uarm) uarm;
__typeof__(uarmh) uarmh;
__typeof__(uarmu) uarmu;
__typeof__(uamul) uamul;
__typeof__(uswapwep) uswapwep;
__typeof__(c_color_names) c_color_names={.c_black="fixture",.c_amber="fixture",.c_golden="fixture",.c_light_blue="fixture",.c_white="fixture",.c_orange="fixture"};
__typeof__(iflags) iflags;
__typeof__(disp) disp;
__typeof__(mons) mons={[PM_HUMAN]={.pmidx=PM_HUMAN,.mlet=S_HUMAN,.mflags2=M2_HUMAN,.pmnames={"human","human","human"}}};
__typeof__(svd) svd;
__typeof__(genders) genders={{.him="their",.his="their"},{.him="their",.his="their"},{.him="their",.his="their"}};
__typeof__(flags) flags;
__typeof__(svk) svk;
__typeof__(c_common_strings) c_common_strings={.c_nothing_happens="fixture",.c_something="fixture",.c_Something="fixture",.c_You_can_move_again="fixture"};
__typeof__(gu) gu;
__typeof__(svb) svb;
__typeof__(obj_descr) obj_descr;
__typeof__(gp) gp;
__typeof__(svt) svt;
__typeof__(svm) svm;
__typeof__(WIN_MESSAGE) WIN_MESSAGE;
__typeof__(windowprocs) windowprocs;
__typeof__(gm) gm;
__typeof__(gn) gn;
__typeof__(ynchars) ynchars="yn";
__typeof__(ga) ga;
__typeof__(gv) gv;
__typeof__(roles) roles={{.lgod="_Law",.ngod="Neutral",.cgod="Chaos"},{0}};
static struct obj objpool[24];static struct monst monpool[8];static struct oextra extras[24];static char names[24][256];static int objlive[24],objnext=8,monnext=4;static char bufferpool[8192],tracebuf[262144];static size_t traceused;static unsigned seed=1;static int rngvalue=0,result=0,query=1,grow=0,reentry=0,exitcode=0,capacity=0,regiondanger=0,done_returns=0;static long wide=0;static jmp_buf escape;static seenV viz[ROWNO][COLNO];static seenV*vizrows[ROWNO];
static void append(const char*fmt,...){va_list ap;va_start(ap,fmt);int n=vsnprintf(tracebuf+traceused,sizeof tracebuf-traceused,fmt,ap);va_end(ap);if(n<0||(size_t)n>=sizeof tracebuf-traceused)abort();traceused+=(size_t)n;}
static uint64_t token(const void*p){uintptr_t a=(uintptr_t)p;if(!p)return 0;
if(a>=(uintptr_t)&objpool&&a<(uintptr_t)&objpool+sizeof objpool)return 100000+a-(uintptr_t)&objpool;
if(a>=(uintptr_t)&monpool&&a<(uintptr_t)&monpool+sizeof monpool)return 200000+a-(uintptr_t)&monpool;
if(a>=(uintptr_t)&bufferpool&&a<(uintptr_t)&bufferpool+sizeof bufferpool)return 300000+a-(uintptr_t)&bufferpool;
if(a>=(uintptr_t)&extras&&a<(uintptr_t)&extras+sizeof extras)return 400000+a-(uintptr_t)&extras;
if(a>=(uintptr_t)&names&&a<(uintptr_t)&names+sizeof names)return 500000+a-(uintptr_t)&names;
if(a>=(uintptr_t)&u&&a<(uintptr_t)&u+sizeof u)return 2000000+a-(uintptr_t)&u;
if(a>=(uintptr_t)&svl&&a<(uintptr_t)&svl+sizeof svl)return 2100000+a-(uintptr_t)&svl;
if(a>=(uintptr_t)&gy&&a<(uintptr_t)&gy+sizeof gy)return 2200000+a-(uintptr_t)&gy;
if(a>=(uintptr_t)&uarmf&&a<(uintptr_t)&uarmf+sizeof uarmf)return 2300000+a-(uintptr_t)&uarmf;
if(a>=(uintptr_t)&uleft&&a<(uintptr_t)&uleft+sizeof uleft)return 2400000+a-(uintptr_t)&uleft;
if(a>=(uintptr_t)&uright&&a<(uintptr_t)&uright+sizeof uright)return 2500000+a-(uintptr_t)&uright;
if(a>=(uintptr_t)&uwep&&a<(uintptr_t)&uwep+sizeof uwep)return 2600000+a-(uintptr_t)&uwep;
if(a>=(uintptr_t)&ublindf&&a<(uintptr_t)&ublindf+sizeof ublindf)return 2700000+a-(uintptr_t)&ublindf;
if(a>=(uintptr_t)&uball&&a<(uintptr_t)&uball+sizeof uball)return 2800000+a-(uintptr_t)&uball;
if(a>=(uintptr_t)&uarmg&&a<(uintptr_t)&uarmg+sizeof uarmg)return 2900000+a-(uintptr_t)&uarmg;
if(a>=(uintptr_t)&gi&&a<(uintptr_t)&gi+sizeof gi)return 3000000+a-(uintptr_t)&gi;
if(a>=(uintptr_t)&objects&&a<(uintptr_t)&objects+sizeof objects)return 3100000+a-(uintptr_t)&objects;
if(a>=(uintptr_t)&uarms&&a<(uintptr_t)&uarms+sizeof uarms)return 3200000+a-(uintptr_t)&uarms;
if(a>=(uintptr_t)&uarmc&&a<(uintptr_t)&uarmc+sizeof uarmc)return 3300000+a-(uintptr_t)&uarmc;
if(a>=(uintptr_t)&uarm&&a<(uintptr_t)&uarm+sizeof uarm)return 3400000+a-(uintptr_t)&uarm;
if(a>=(uintptr_t)&uarmh&&a<(uintptr_t)&uarmh+sizeof uarmh)return 3500000+a-(uintptr_t)&uarmh;
if(a>=(uintptr_t)&uarmu&&a<(uintptr_t)&uarmu+sizeof uarmu)return 3600000+a-(uintptr_t)&uarmu;
if(a>=(uintptr_t)&uamul&&a<(uintptr_t)&uamul+sizeof uamul)return 3700000+a-(uintptr_t)&uamul;
if(a>=(uintptr_t)&uswapwep&&a<(uintptr_t)&uswapwep+sizeof uswapwep)return 3800000+a-(uintptr_t)&uswapwep;
if(a>=(uintptr_t)&c_color_names&&a<(uintptr_t)&c_color_names+sizeof c_color_names)return 3900000+a-(uintptr_t)&c_color_names;
if(a>=(uintptr_t)&iflags&&a<(uintptr_t)&iflags+sizeof iflags)return 4000000+a-(uintptr_t)&iflags;
if(a>=(uintptr_t)&disp&&a<(uintptr_t)&disp+sizeof disp)return 4100000+a-(uintptr_t)&disp;
if(a>=(uintptr_t)&mons&&a<(uintptr_t)&mons+sizeof mons)return 4200000+a-(uintptr_t)&mons;
if(a>=(uintptr_t)&svd&&a<(uintptr_t)&svd+sizeof svd)return 4300000+a-(uintptr_t)&svd;
if(a>=(uintptr_t)&flags&&a<(uintptr_t)&flags+sizeof flags)return 4500000+a-(uintptr_t)&flags;
if(a>=(uintptr_t)&svk&&a<(uintptr_t)&svk+sizeof svk)return 4600000+a-(uintptr_t)&svk;
if(a>=(uintptr_t)&c_common_strings&&a<(uintptr_t)&c_common_strings+sizeof c_common_strings)return 4700000+a-(uintptr_t)&c_common_strings;
if(a>=(uintptr_t)&gu&&a<(uintptr_t)&gu+sizeof gu)return 4800000+a-(uintptr_t)&gu;
if(a>=(uintptr_t)&svb&&a<(uintptr_t)&svb+sizeof svb)return 4900000+a-(uintptr_t)&svb;
if(a>=(uintptr_t)&obj_descr&&a<(uintptr_t)&obj_descr+sizeof obj_descr)return 5000000+a-(uintptr_t)&obj_descr;
if(a>=(uintptr_t)&gp&&a<(uintptr_t)&gp+sizeof gp)return 5100000+a-(uintptr_t)&gp;
if(a>=(uintptr_t)&svt&&a<(uintptr_t)&svt+sizeof svt)return 5200000+a-(uintptr_t)&svt;
if(a>=(uintptr_t)&svm&&a<(uintptr_t)&svm+sizeof svm)return 5300000+a-(uintptr_t)&svm;
if(a>=(uintptr_t)&WIN_MESSAGE&&a<(uintptr_t)&WIN_MESSAGE+sizeof WIN_MESSAGE)return 5400000+a-(uintptr_t)&WIN_MESSAGE;
if(a>=(uintptr_t)&windowprocs&&a<(uintptr_t)&windowprocs+sizeof windowprocs)return 5500000+a-(uintptr_t)&windowprocs;
if(a>=(uintptr_t)&gm&&a<(uintptr_t)&gm+sizeof gm)return 5600000+a-(uintptr_t)&gm;
if(a>=(uintptr_t)&gn&&a<(uintptr_t)&gn+sizeof gn)return 5700000+a-(uintptr_t)&gn;
if(a>=(uintptr_t)&ga&&a<(uintptr_t)&ga+sizeof ga)return 5900000+a-(uintptr_t)&ga;
if(a>=(uintptr_t)&gv&&a<(uintptr_t)&gv+sizeof gv)return 6000000+a-(uintptr_t)&gv;
return a;}
static struct obj*fixture_newobj(int typ){if(objnext>=24)abort();struct obj*p=&objpool[objnext++];memset(p,0,sizeof *p);p->otyp=typ;p->oclass=objects[typ].oc_class;p->quan=1;p->corpsenm=PM_HUMAN;objlive[p-objpool]=1;append("allocobj:%d:%d;",(int)(p-objpool),typ);return p;}
static void hook(void){if(grow){grow=0;emscripten_resize_heap(emscripten_get_heap_size()+65536);}if(reentry){reentry=0;(void)a_gname();}}
static void fixture_window(winid id,boolean b){append("window:%d:%d;",id,b);hook();}
int (xlev_to_rank)(int a0){return a0/4;}
int (isok)(coordxy a0,coordxy a1){return a0>=1&&a0<COLNO&&a1>=0&&a1<ROWNO;}
boolean (region_danger)(void){return regiondanger;}
int (near_capacity)(void){return capacity;}
struct obj * (stuck_ring)(struct obj * a0,int a1){return a0&&a0->otyp==a1&&a0->cursed?a0:0;}
int (freehand)(void){return !(uwep&&uwep->cursed);}
int (welded)(struct obj * a0){return a0&&a0->cursed;}
struct obj * (unchanger)(void){append("unchanger:;");return 0;}
struct obj * (which_armor)(struct monst * a0,long a1){return uarm;}
struct attack * (attacktype_fordmg)(struct permonst * a0,int a1,int a2){append("attacktype_fordmg:%lld:%lld:%lld;",(long long)token(a0),(long long)a1,(long long)a2);return 0;}
boolean (confers_luck)(struct obj * a0){return result;}
void (make_glib)(int a0){append("glib:%d;",a0);Glib=a0;}
const char * (gloves_simple_name)(struct obj * a0){return "gloves";}
char * (Yobjnam2)(struct obj * a0,const char * a1){return (char*)a1;}
const char * (hcolor)(const char * a0){return "violet";}
void (uncurse)(struct obj * a0){append("uncurse:%llu;",(unsigned long long)token(a0));a0->cursed=0;hook();}
void (update_inventory)(void){append("inventory;");hook();}
void (make_stoned)(long a0,const char * a1,int a2,const char * a3){append("stoned:%ld;",a0);Stoned=a0;}
void (make_slimed)(long a0,const char * a1){append("slimed:%ld;",a0);Slimed=a0;}
void (useup)(struct obj * a0){append("useup:%llu;",(unsigned long long)token(a0));if(a0->quan>1){a0->quan--;return;}if(a0>=objpool&&a0<objpool+24)objlive[a0-objpool]=0;a0->quan=0;if(gi.invent==a0)gi.invent=a0->nobj;if(uarmf==a0)uarmf=0;if(uleft==a0)uleft=0;if(uright==a0)uright=0;if(uwep==a0)uwep=0;if(ublindf==a0)ublindf=0;if(uball==a0)uball=0;if(uarmg==a0)uarmg=0;if(uarms==a0)uarms=0;if(uarmc==a0)uarmc=0;if(uarm==a0)uarm=0;if(uarmh==a0)uarmh=0;if(uarmu==a0)uarmu=0;if(uamul==a0)uamul=0;if(uswapwep==a0)uswapwep=0;hook();}
boolean (safe_teleds)(int a0){append("safe:%d;",a0);if(result)u.ux=u.uy=15;return result;}
void (reset_utrap)(boolean a0){u.utrap=0;}
void (rescued_from_terrain)(int a0){append("rescued_from_terrain:%lld;",(long long)a0);}
const char * (body_part)(int a0){return "hand";}
void (init_uhunger)(void){u.uhunger=900;u.uhs=NOT_HUNGRY;}
void (make_sick)(long a0,const char * a1,boolean a2,int a3){append("sick:%ld:%d:%d;",a0,a2,a3);Sick=a0;}
void (region_safety)(void){append("region_safety;");regiondanger=0;}
boolean (rng_log_enabled)(void){return 1;}
void (rng_log_set_caller)(const char * a0,int a1,const char * a2){append("rng:%s:%d:%s;",a0,a1,a2);}
int (rnd)(int a0){int v=(rn2)(a0)+1;append("rnd:%d:%d;",a0,v);return v;}
void (setuhpmax)(int a0,boolean a1){append("hpmax:%d:%d;",a0,a1);if(a1)u.uhpmax=a0;else u.mhmax=a0;}
int (d)(int a0,int a1){append("d:%d:%d;",a0,a1);return a0;}
void (set_itimeout)(long * a0,long a1){append("timeout:%ld;",a1);*a0=a1;}
void (rehumanize)(void){append("rehumanize;");u.umonnum=u.umonster;}
void (you_unwere)(boolean a0){u.ulycn=NON_PM;}
void (buried_ball_to_freedom)(void){u.utrap=0;}
void (unpunish)(void){uball=0;}
void (encumber_msg)(void){append("encumber_msg:;");}
char * (makeplural)(const char * a0){return (char*)a0;}
char * (vtense)(const char * a0,const char * a1){return (char*)a1;}
void (make_blinded)(long a0,boolean a1){append("blinded:%ld:%d;",a0,a1);HBlinded=a0;}
void (make_deaf)(long a0,boolean a1){append("deaf:%ld:%d;",a0,a1);HDeaf=a0;}
char * (eos)(char * a0){return a0+strlen(a0);}
void (heal_legs)(int a0){HWounded_legs=0;EWounded_legs=0;}
void (make_stunned)(long a0,boolean a1){append("stunned:%ld:%d;",a0,a1);HStun=a0;}
void (make_confused)(long a0,boolean a1){append("confused:%ld:%d;",a0,a1);HConfusion=a0;}
boolean (make_hallucinated)(long a0,boolean a1,long a2){append("hallu:%ld:%d:%ld;",a0,a1,a2);HHallucination=a0;return 1;}
void (set_bknown)(struct obj * a0,unsigned int a1){append("set_bknown:%lld:%lld;",(long long)token(a0),(long long)a1);}
char * (mon_nam)(struct monst * a0){return "monster";}
boolean (Resists_Elem)(struct monst * a0,int a1){append("Resists_Elem:%lld:%lld;",(long long)token(a0),(long long)a1);return 0;}
char * (Monnam)(struct monst * a0){return "Monster";}
void (xkilled)(struct monst * a0,int a1){append("xkilled:%llu:%d;",(unsigned long long)token(a0),a1);a0->mhp=0;}
void (shieldeff)(coordxy a0,coordxy a1){append("shieldeff:%lld:%lld;",(long long)a0,(long long)a1);}
boolean (ureflects)(const char * a0,const char * a1){append("ureflects:%s:%s;",(a0?a0:"NULL"),(a1?a1:"NULL"));return 0;}
void (monstseesu)(unsigned long a0){append("monstseesu:%lld;",(long long)a0);}
void (monstunseesu)(unsigned long a0){append("monstunseesu:%lld;",(long long)a0);}
int (disintegrate_arm)(struct obj * a0){append("disintegrate_arm:%lld;",(long long)token(a0));return 0;}
boolean (on_level)(d_level * a0,d_level * a1){return a0->dnum==a1->dnum&&a0->dlevel==a1->dlevel;}
void (summon_minion)(aligntyp a0,boolean a1){append("summon_minion:%lld:%lld;",(long long)a0,(long long)a1);}
void (done)(int a0){exitcode=a0;append("done:%d;",a0);if(a0==DIED&&done_returns){append("lifesaved;");return;}longjmp(escape,1);}
boolean (In_hell)(d_level * a0){return a0->dnum==3;}
int (rn2)(int a0){if(a0<=0)abort();seed=seed*1664525u+1013904223u;int v=rngvalue<0?(int)(seed%(unsigned)a0):rngvalue%a0;append("rn2:%d:%d;",a0,v);return v;}
boolean (adjattrib)(int a0,int a1,int a2){append("attrib:%d:%d:%d;",a0,a1,a2);ABASE(a0)+=a1;return 1;}
void (losexp)(const char * a0){append("losexp:%s;",(a0?a0:"NULL"));}
void (punish)(struct obj * a0){append("punish:%lld;",(long long)token(a0));}
char * (An)(const char * a0){return (char*)a0;}
int (attrcurse)(void){append("attrcurse:;");return 0;}
void (rndcurse)(void){append("rndcurse:;");}
int (rnz)(int a0){append("rnz:%d;",a0);return a0;}
char * (s_suffix)(const char * a0){return (char*)a0;}
const char * (mbodypart)(struct monst * a0,int a1){return "foot";}
boolean (is_art)(struct obj * a0,int a1){return result;}
struct obj * (carrying)(int a0){return 0;}
const char * (artiname)(int a0){return "artifact";}
boolean (exist_artifact)(int a0,const char * a1){return result;}
struct obj * (mksobj)(int a0,boolean a1,boolean a2){append("mksobj:%d:%d:%d;",a0,a1,a2);return fixture_newobj(a0);}
char * (actualoname)(struct obj * a0){return "artifact";}
void (bless)(struct obj * a0){append("bless:%llu;",(unsigned long long)token(a0));a0->blessed=1;a0->cursed=0;}
void (observe_object)(struct obj * a0){append("observe_object:%lld;",(long long)token(a0));}
char * (ansimpleoname)(struct obj * a0){return "an object";}
char * (upstart)(char * a0){return a0;}
void (dropy)(struct obj * a0){append("dropy:%llu;",(unsigned long long)token(a0));a0->where=OBJ_FLOOR;}
int (known_spell)(short a0){return result;}
char * (simpleonames)(struct obj * a0){return "objects";}
struct obj * (oname)(struct obj * a0,const char * a1,unsigned int a2){append("oname:%llu:%s:%u;",(unsigned long long)token(a0),a1,a2);int i=(int)(a0-objpool);strncpy(names[i],a1,255);a0->oextra=&extras[i];extras[i].oname=names[i];return a0;}
void (unrestrict_weapon_skill)(int a0){append("unrestrict_weapon_skill:%lld;",(long long)a0);}
void (discover_artifact)(xint16 a0){append("discover_artifact:%lld;",(long long)a0);}
char * (xname)(struct obj * a0){return "object";}
int (weapon_type)(struct obj * a0){return P_DAGGER;}
void (add_weapon_skill)(int a0){append("add_weapon_skill:%lld;",(long long)a0);}
struct obj * (mkobj)(int a0,boolean a1){append("mkobj:%d:%d;",a0,a1);return fixture_newobj(SPE_BLANK_PAPER);}
int (spell_skilltype)(int a0){return P_ATTACK_SPELL;}
int (rnd_class)(int a0,int a1){return a0;}
char (force_learn_spell)(short a0){append("learn:%d;",a0);return result;}
void (obfree)(struct obj * a0,struct obj * a1){append("obfree:%llu:%llu;",(unsigned long long)token(a0),(unsigned long long)token(a1));if(a0>=objpool&&a0<objpool+24)objlive[a0-objpool]=0;}
void (discover_object)(int a0,boolean a1,boolean a2,boolean a3){append("discover_object:%lld:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2,(long long)a3);}
void (place_object)(struct obj * a0,coordxy a1,coordxy a2){append("place:%llu:%d:%d;",(unsigned long long)token(a0),a1,a2);a0->ox=a1;a0->oy=a2;a0->where=OBJ_FLOOR;}
void (newsym)(coordxy a0,coordxy a1){append("newsym:%lld:%lld;",(long long)a0,(long long)a1);}
void (adjalign)(int a0){append("align:%d;",a0);u.ualign.record+=a0;}
int (rnl)(int a0){int v=(rn2)(a0);append("rnl:%d:%d;",a0,v);return v;}
char * (otense)(struct obj * a0,const char * a1){return (char*)a1;}
char * (yname)(struct obj * a0){return "your object";}
char * (an)(const char * a0){return (char*)a0;}
void (record_achievement)(schar a0){append("record_achievement:%lld;",(long long)a0);}
void (pluslvl)(boolean a0){append("pluslvl:%lld;",(long long)a0);}
void (see_monsters)(void){append("see_monsters:;");}
void (useupf)(struct obj * a0,long a1){append("useupf:%llu:%ld;",(unsigned long long)token(a0),a1);if(a0->quan>a1){a0->quan-=a1;return;}if(a0>=objpool&&a0<objpool+24)objlive[a0-objpool]=0;a0->quan=0;}
void (exercise)(int a0,boolean a1){append("exercise:%lld:%lld;",(long long)a0,(long long)a1);}
void (Amulet_off)(void){append("Amulet_off:;");}
void (change_luck)(schar a0){append("luck:%d;",a0);u.uluck+=a0;}
void (uchangealign)(int a0,int a1){append("uchangealign:%d:%d;",a0,a1);u.ualign.type=a0;}
char (temple_occupied)(char * a0){append("temple:%s;",a0);return 0;}
struct monst * (findpriest)(char a0){append("findpriest:%lld;",(long long)a0);return 0;}
boolean (p_coaligned)(struct monst * a0){append("p_coaligned:%lld;",(long long)token(a0));return 0;}
void (angry_priest)(void){append("angry_priest:;");}
int (dlord)(aligntyp a0){append("dlord:%lld;",(long long)a0);return 0;}
struct monst * (makemon)(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){append("makemon:%lld:%lld:%lld:%lld;",(long long)token(a0),(long long)a1,(long long)a2,(long long)a3);return 0;}
char * (a_monnam)(struct monst * a0){return "a monster";}
int (strncmpi)(const char * a0,const char * a1,int a2){return strncasecmp(a0,a1,a2);}
int (sgn)(int a0){return(a0>0)-(a0<0);}
void (nomul)(int a0){append("nomul:%d;",a0);}
int (nartifact_exist)(void){return 0;}
char (yn_function)(const char * a0,const char * a1,char a2,boolean a3){append("yn:%s:%d:%d;",a0,a2,a3);return query?'y':'n';}
struct obj * (mk_artifact)(struct obj * a0,aligntyp a1,uchar a2,boolean a3){append("artifact:%llu:%d:%u:%d;",(unsigned long long)token(a0),a1,a2,a3);return result?a0:0;}
void (artifact_origin)(struct obj * a0,unsigned int a1){append("artifact_origin:%lld:%lld;",(long long)token(a0),(long long)a1);}
char * (bare_artifactname)(struct obj * a0){return "artifact";}
long (peek_at_iced_corpse_age)(struct obj * a0){return wide;}
int (eaten_stat)(int a0,struct obj * a1){return a0;}
struct obj * (floorfood)(const char * a0,int a1){return &objpool[0];}
const char * (align_str)(aligntyp a0){return "neutral";}
char * (corpse_xname)(struct obj * a0,const char * a1,unsigned int a2){return "corpse";}
void (feel_cockatrice)(struct obj * a0,boolean a1){append("feel_cockatrice:%lld:%lld;",(long long)token(a0),(long long)a1);}
boolean (rider_corpse_revival)(struct obj * a0,boolean a1){append("rider_corpse_revival:%lld:%lld;",(long long)token(a0),(long long)a1);return 0;}
struct monst * (get_mtraits)(struct obj * a0,boolean a1){return result?&monpool[0]:0;}
struct monst * (revive)(struct obj * a0,boolean a1){append("revive:%llu:%d;",(unsigned long long)token(a0),a1);return result?&monpool[0]:0;}
struct monst * (animate_statue)(struct obj * a0,coordxy a1,coordxy a2,int a3,int * a4){if(a4)*a4=0;return result?&monpool[0]:0;}
boolean (paranoid_query)(boolean a0,const char * a1){append("paranoid:%d:%s;",a0,a1);return query;}
void (wake_nearby)(boolean a0){append("wake_nearby:%lld;",(long long)a0);}
void (losehp)(int a0,const char * a1,schar a2){append("losehp:%d:%s:%d;",a0,a1,a2);u.uhp-=a0;}
int (dist2)(coordxy a0,coordxy a1,coordxy a2,coordxy a3){return(a0-a2)*(a0-a2)+(a1-a3)*(a1-a3);}
int (resist)(struct monst * a0,char a1,int a2,int a3){return result;}
void (set_malign)(struct monst * a0){append("set_malign:%lld;",(long long)token(a0));}
void (killed)(struct monst * a0){append("killed:%llu;",(unsigned long long)token(a0));a0->mhp=0;}
void (monflee)(struct monst * a0,int a1,boolean a2,boolean a3){append("flee:%llu:%d:%d:%d;",(unsigned long long)token(a0),a1,a2,a3);}
int (spelleffects)(int a0,boolean a1,boolean a2){append("spelleffects:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2);return 0;}
boolean (can_chant)(struct monst * a0){return 1;}
void (aggravate)(void){append("aggravate:;");}
void (iter_mons)(void (*a0)(struct monst *)){append("iter;");for(struct monst*m=fmon,*next;m;m=next){next=m->nmon;a0(m);}hook();}
int (randrole)(boolean a0){append("role:%d;",a0);return 0;}
int (rn2_on_display_rng)(int a0){append("displayrng:%d;",a0);return result>=0?result%a0:0;}
boolean (is_pool_or_lava)(coordxy a0,coordxy a1){append("is_pool_or_lava:%lld:%lld;",(long long)a0,(long long)a1);return 0;}
struct obj * (sobj_at)(int a0,coordxy a1,coordxy a2){append("sobj_at:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2);return 0;}
void (You)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("You:%s;",b);}
void (You_feel)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("You_feel:%s;",b);}
void (You_hear)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("You_hear:%s;",b);}
void (Your)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("Your:%s;",b);}
void (impossible)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("impossible:%s;",b);}
void (livelog_printf)(long a0,const char * a1,...){char b[4096];va_list ap;va_start(ap,a1);vsnprintf(b,sizeof b,a1,ap);va_end(ap);append("livelog_printf:%ld:%s;",a0,b);}
void (pline)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("pline:%s;",b);}
void (pline_The)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("pline_The:%s;",b);}
void (verbalize)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("verbalize:%s;",b);}
#ifdef HYBRID_PRAY
#include "../nethack-c/wasm/tu-fragments/pray-types.h"
extern int teleport_pray_in_trouble(void);
#define in_trouble teleport_pray_in_trouble
extern struct obj * teleport_pray_worst_cursed_item(void);
#define worst_cursed_item teleport_pray_worst_cursed_item
extern void teleport_pray_fix_curse_trouble(struct obj * otmp,const char * what);
#define fix_curse_trouble teleport_pray_fix_curse_trouble
extern void teleport_pray_fix_worst_trouble(int trouble);
#define fix_worst_trouble teleport_pray_fix_worst_trouble
extern void teleport_pray_god_zaps_you(aligntyp resp_god);
#define god_zaps_you teleport_pray_god_zaps_you
extern void teleport_pray_fry_by_god(aligntyp resp_god,boolean via_disintegration);
#define fry_by_god teleport_pray_fry_by_god
extern void teleport_pray_angrygods(aligntyp resp_god);
#define angrygods teleport_pray_angrygods
extern void teleport_pray_at_your_feet(const char * str);
#define at_your_feet teleport_pray_at_your_feet
extern void teleport_pray_gcrownu(void);
#define gcrownu teleport_pray_gcrownu
extern void teleport_pray_give_spell(void);
#define give_spell teleport_pray_give_spell
extern void teleport_pray_pleased(aligntyp g_align);
#define pleased teleport_pray_pleased
extern boolean teleport_pray_water_prayer(boolean bless_water);
#define water_prayer teleport_pray_water_prayer
extern void teleport_pray_godvoice(aligntyp g_align,const char * words);
#define godvoice teleport_pray_godvoice
extern void teleport_pray_gods_angry(aligntyp g_align);
#define gods_angry teleport_pray_gods_angry
extern void teleport_pray_gods_upset(aligntyp g_align);
#define gods_upset teleport_pray_gods_upset
extern void teleport_pray_consume_offering(struct obj * otmp);
#define consume_offering teleport_pray_consume_offering
extern void teleport_pray_offer_too_soon(aligntyp altaralign);
#define offer_too_soon teleport_pray_offer_too_soon
extern void teleport_pray_offer_real_amulet(struct obj * otmp,aligntyp altaralign);
#define offer_real_amulet teleport_pray_offer_real_amulet
extern void teleport_pray_offer_negative_valued(boolean highaltar,aligntyp altaralign);
#define offer_negative_valued teleport_pray_offer_negative_valued
extern void teleport_pray_offer_fake_amulet(struct obj * otmp,boolean highaltar,aligntyp altaralign);
#define offer_fake_amulet teleport_pray_offer_fake_amulet
extern void teleport_pray_offer_different_alignment_altar(struct obj * otmp,aligntyp altaralign);
#define offer_different_alignment_altar teleport_pray_offer_different_alignment_altar
extern void teleport_pray_sacrifice_your_race(struct obj * otmp,boolean highaltar,aligntyp altaralign);
#define sacrifice_your_race teleport_pray_sacrifice_your_race
extern int teleport_pray_bestow_artifact(uchar max_giftvalue);
#define bestow_artifact teleport_pray_bestow_artifact
extern int teleport_pray_sacrifice_value(struct obj * otmp);
#define sacrifice_value teleport_pray_sacrifice_value
extern int teleport_pray_eval_offering(struct obj * otmp,aligntyp altaralign);
#define eval_offering teleport_pray_eval_offering
extern void teleport_pray_offer_corpse(struct obj * otmp,boolean highaltar,aligntyp altaralign);
#define offer_corpse teleport_pray_offer_corpse
extern boolean teleport_pray_pray_revive(void);
#define pray_revive teleport_pray_pray_revive
extern int teleport_pray_prayer_done(void);
#define prayer_done teleport_pray_prayer_done
extern void teleport_pray_maybe_turn_mon_iter(struct monst * mtmp);
#define maybe_turn_mon_iter teleport_pray_maybe_turn_mon_iter
extern boolean teleport_pray_blocked_boulder(int dx,int dy);
#define blocked_boulder teleport_pray_blocked_boulder
EM_JS(int,private_pray,(int index),{return Module["nethackPorted"].prayPrivate(Module,index);});
#else
#include "../.cache/wasm64-build/tree/src/pray.c"
#define TELEPORT_PRAY_TYPES_H
#define teleport_pray_prayer_done prayer_done
#define teleport_pray_maybe_turn_mon_iter maybe_turn_mon_iter
#endif
#include "../nethack-c/wasm/tu-fragments/pray-support.c"
#include "tu-pray-layout.h"
int probe_private(int index){
#ifdef HYBRID_PRAY
return private_pray(index);
#else
return index==0?turn_undead_range:turn_undead_msg_cnt;
#endif
}
size_t probe_mon_next_offset(void){return offsetof(struct monst,nmon);}
uintptr_t probe_pool(int kind,int i){return(uintptr_t)(kind==0?(void*)&objpool[i]:kind==1?(void*)&monpool[i]:kind==2?(void*)&bufferpool[i]:kind==3?(void*)&extras[i]:(void*)&names[i]);}
int probe_live(int i){return objlive[i];}
int probe_layout_count(void){return sizeof pray_layout/sizeof pray_layout[0];}
const char*probe_layout_name(int i){return pray_layout[i].name;}
int64_t probe_layout_value(int i){return(int64_t)pray_layout[i].value;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
const char*probe_trace(void){return tracebuf;}
void probe_clear_trace(void){traceused=0;tracebuf[0]=0;}
void probe_option(int k,int64_t v){switch(k){case 0:result=v;break;case 1:rngvalue=v;break;case 2:query=v;break;case 3:grow=v;break;case 4:reentry=v;break;case 5:wide=v;break;case 6:capacity=v;break;case 7:regiondanger=v;break;case 8:done_returns=v;break;default:abort();}}
uintptr_t probe_function(int i){return(uintptr_t)(i==0?(void*)prayer_done:i==1?(void*)maybe_turn_mon_iter:(void*)fixture_window);}
uint64_t probe_action(int op,uint64_t a,uint64_t b,uint64_t c,uint64_t d){if(setjmp(escape))return 0x70000000+exitcode;switch(op){
case 0:return(uint64_t)(uintptr_t)critically_low_hp((boolean)(uintptr_t)a);
case 1:return(uint64_t)(uintptr_t)stuck_in_wall();
case 2:return(uint64_t)(uintptr_t)in_trouble();
case 3:return(uint64_t)(uintptr_t)worst_cursed_item();
case 4:fix_curse_trouble((struct obj *)(uintptr_t)a,(const char *)(uintptr_t)b);return 0;
case 5:fix_worst_trouble((int)(uintptr_t)a);return 0;
case 6:god_zaps_you((aligntyp)(uintptr_t)a);return 0;
case 7:fry_by_god((aligntyp)(uintptr_t)a,(boolean)(uintptr_t)b);return 0;
case 8:angrygods((aligntyp)(uintptr_t)a);return 0;
case 9:at_your_feet((const char *)(uintptr_t)a);return 0;
case 10:gcrownu();return 0;
case 11:give_spell();return 0;
case 12:pleased((aligntyp)(uintptr_t)a);return 0;
case 13:return(uint64_t)(uintptr_t)water_prayer((boolean)(uintptr_t)a);
case 14:godvoice((aligntyp)(uintptr_t)a,(const char *)(uintptr_t)b);return 0;
case 15:gods_angry((aligntyp)(uintptr_t)a);return 0;
case 16:gods_upset((aligntyp)(uintptr_t)a);return 0;
case 17:consume_offering((struct obj *)(uintptr_t)a);return 0;
case 18:offer_too_soon((aligntyp)(uintptr_t)a);return 0;
case 19:desecrate_altar((boolean)(uintptr_t)a,(aligntyp)(uintptr_t)b);return 0;
case 20:offer_real_amulet((struct obj *)(uintptr_t)a,(aligntyp)(uintptr_t)b);return 0;
case 21:offer_negative_valued((boolean)(uintptr_t)a,(aligntyp)(uintptr_t)b);return 0;
case 22:offer_fake_amulet((struct obj *)(uintptr_t)a,(boolean)(uintptr_t)b,(aligntyp)(uintptr_t)c);return 0;
case 23:offer_different_alignment_altar((struct obj *)(uintptr_t)a,(aligntyp)(uintptr_t)b);return 0;
case 24:sacrifice_your_race((struct obj *)(uintptr_t)a,(boolean)(uintptr_t)b,(aligntyp)(uintptr_t)c);return 0;
case 25:return(uint64_t)(uintptr_t)bestow_artifact((uchar)(uintptr_t)a);
case 26:return(uint64_t)(uintptr_t)sacrifice_value((struct obj *)(uintptr_t)a);
case 27:return(uint64_t)(uintptr_t)dosacrifice();
case 28:return(uint64_t)(uintptr_t)eval_offering((struct obj *)(uintptr_t)a,(aligntyp)(uintptr_t)b);
case 29:offer_corpse((struct obj *)(uintptr_t)a,(boolean)(uintptr_t)b,(aligntyp)(uintptr_t)c);return 0;
case 30:return(uint64_t)(uintptr_t)can_pray((boolean)(uintptr_t)a);
case 31:return(uint64_t)(uintptr_t)pray_revive();
case 32:return(uint64_t)(uintptr_t)dopray();
case 33:return(uint64_t)(uintptr_t)prayer_done();
case 34:maybe_turn_mon_iter((struct monst *)(uintptr_t)a);return 0;
case 35:return(uint64_t)(uintptr_t)doturn();
case 36:return(uint64_t)(uintptr_t)altarmask_at((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b);
case 37:return(uint64_t)(uintptr_t)a_gname();
case 38:return(uint64_t)(uintptr_t)a_gname_at((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b);
case 39:return(uint64_t)(uintptr_t)u_gname();
case 40:return(uint64_t)(uintptr_t)align_gname((aligntyp)(uintptr_t)a);
case 41:return(uint64_t)(uintptr_t)halu_gname((aligntyp)(uintptr_t)a);
case 42:return(uint64_t)(uintptr_t)align_gtitle((aligntyp)(uintptr_t)a);
case 43:altar_wrath((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b);return 0;
case 44:return(uint64_t)(uintptr_t)blocked_boulder((int)(uintptr_t)a,(int)(uintptr_t)b);
default:abort();}}
const char*probe_god(int k,int i){
#ifdef HYBRID_PRAY
return 0;
#else
return k==0?Moloch:k==1?godvoices[i]:hallu_gods[i];
#endif
}
uint64_t probe_finish(void){if(setjmp(escape))return 0x70000000+exitcode;return ga.afternmv?ga.afternmv():0;}
void probe_setup(int k,int v){if(k==0){fmon=&monpool[0];monpool[0].nmon=&monpool[1];for(int i=0;i<2;i++){monpool[i].data=&mons[PM_HUMAN+1];monpool[i].mhp=10;monpool[i].msleeping=monpool[i].mflee=1;monpool[i].mfrozen=2;viz[monpool[i].my][monpool[i].mx]=COULD_SEE;}mons[PM_HUMAN+1].mlet=S_ZOMBIE;mons[PM_HUMAN+1].mflags2=M2_UNDEAD;}else if(k==1){objpool[0].oextra=&extras[0];extras[0].omonst=&monpool[0];monpool[0].mtame=3;}else abort();}
int64_t probe_constant(int i){static const int64_t c[]={A_NONE,A_LAWFUL,A_NEUTRAL,A_CHAOTIC,AM_SHRINE,AM_LAWFUL,AM_NEUTRAL,AM_CHAOTIC,ROOM,OBJ_FLOOR,OBJ_INVENT,M2_UNDEAD,M1_NOHANDS,PM_CLERIC,PM_KNIGHT};return c[i];}
void probe_reset(void){traceused=0;tracebuf[0]=0;seed=1;rngvalue=0;result=0;query=1;grow=0;reentry=0;wide=0;exitcode=0;objnext=8;monnext=4;capacity=regiondanger=done_returns=0;memset(extras,0,sizeof extras);memset(names,0,sizeof names);memset(objpool,0,sizeof objpool);memset(monpool,0,sizeof monpool);memset(objlive,0,sizeof objlive);memset(bufferpool,0,sizeof bufferpool);memset(viz,0,sizeof viz);for(int i=0;i<ROWNO;i++)vizrows[i]=viz[i];
memset((void*)&u,0,sizeof u);
memset((void*)&svl,0,sizeof svl);
memset((void*)&gy,0,sizeof gy);
memset((void*)&uarmf,0,sizeof uarmf);
memset((void*)&uleft,0,sizeof uleft);
memset((void*)&uright,0,sizeof uright);
memset((void*)&uwep,0,sizeof uwep);
memset((void*)&ublindf,0,sizeof ublindf);
memset((void*)&uball,0,sizeof uball);
memset((void*)&uarmg,0,sizeof uarmg);
memset((void*)&gi,0,sizeof gi);
memset((void*)&objects,0,sizeof objects);
memset((void*)&uarms,0,sizeof uarms);
memset((void*)&uarmc,0,sizeof uarmc);
memset((void*)&uarm,0,sizeof uarm);
memset((void*)&uarmh,0,sizeof uarmh);
memset((void*)&uarmu,0,sizeof uarmu);
memset((void*)&uamul,0,sizeof uamul);
memset((void*)&uswapwep,0,sizeof uswapwep);
memset((void*)&iflags,0,sizeof iflags);
memset((void*)&disp,0,sizeof disp);
memset((void*)&svd,0,sizeof svd);
memset((void*)&flags,0,sizeof flags);
memset((void*)&svk,0,sizeof svk);
memset((void*)&gu,0,sizeof gu);
memset((void*)&svb,0,sizeof svb);
memset((void*)&obj_descr,0,sizeof obj_descr);
memset((void*)&gp,0,sizeof gp);
memset((void*)&svt,0,sizeof svt);
memset((void*)&svm,0,sizeof svm);
memset((void*)&WIN_MESSAGE,0,sizeof WIN_MESSAGE);
memset((void*)&windowprocs,0,sizeof windowprocs);
memset((void*)&gm,0,sizeof gm);
memset((void*)&gn,0,sizeof gn);
memset((void*)&ga,0,sizeof ga);
memset((void*)&gv,0,sizeof gv);
for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++){levl[x][y].typ=ROOM;levl[x][y].glyph=GLYPH_NOTHING;}gv.viz_array=vizrows;windowprocs.win_display_nhwindow=fixture_window;u.ux=u.uy=10;u.uz.dlevel=5;u.ulevel=10;u.uhp=u.uhpmax=u.mh=u.mhmax=20;u.uhs=NOT_HUNGRY;u.uhunger=900;u.ualign.type=A_NEUTRAL;u.ualign.record=10;u.umonnum=u.umonster=PM_HUMAN;u.ulycn=NON_PM;for(int i=0;i<A_MAX;i++){ABASE(i)=AMAX(i)=10;}gu.urole.lgod="_Law";gu.urole.ngod="Neutral";gu.urole.cgod="Chaos";gu.urole.mnum=PM_HUMAN;gu.urace.mnum=PM_HUMAN;gu.urace.selfmask=M2_HUMAN;gu.urace.noun="human";gu.urace.adj="human";gy.youmonst.data=&mons[PM_HUMAN];for(int i=0;i<NUMMONS;i++){mons[i].mlet=0;mons[i].mflags1=mons[i].mflags2=0;mons[i].difficulty=0;mons[i].maligntyp=0;}mons[PM_HUMAN].mlet=S_HUMAN;mons[PM_HUMAN].mflags2=M2_HUMAN;for(int i=0;i<NUM_OBJECTS;i++){objects[i].oc_name_idx=objects[i].oc_descr_idx=i;obj_descr[i].oc_name="fixture";obj_descr[i].oc_descr="fixture";objects[i].oc_class=FOOD_CLASS;}for(int i=0;i<24;i++){objpool[i].otyp=CORPSE;objpool[i].oclass=FOOD_CLASS;objpool[i].corpsenm=PM_HUMAN;objpool[i].quan=1;objpool[i].where=OBJ_FLOOR;objpool[i].ox=objpool[i].oy=10;objlive[i]=1;}for(int i=0;i<8;i++){monpool[i].data=&mons[PM_HUMAN];monpool[i].mx=11;monpool[i].my=10;monpool[i].mhp=10;}}

/* Exact declared-string address/capacity provenance for test snapshots only. */
static const char*fixture_string(int i){switch(i){
case 0:return "_Law";
case 1:return "Neutral";
case 2:return "Chaos";
case 3:return "fixture";
case 4:return "human";
case 5:return "their";
default:return 0;}}
const char*probe_string(int i){const char*p=fixture_string(i);if(p)return p;
i-=6;
#ifndef HYBRID_PRAY
switch(i){
case 0:return "";
case 1:return " and %s now as good as new";
case 2:return " and you";
case 3:return " named %s";
case 4:return " say";
case 5:return "\"";
case 6:return "\"Then die, %s!\"";
case 7:return "\"Thou %s, %s.\"";
case 8:return "\"and thus I grant thee the gift of %s!\"";
case 9:return "%s";
case 10:return "%s %s %s your %s!";
case 11:return "%s %s into %s %s.";
case 12:return "%s %s%s.";
case 13:return "%s %s%s:";
case 14:return "%s %s.";
case 15:return "%s accepts your allegiance.";
case 16:return "%s accepts your gift, and gains dominion over %s...";
case 17:return "%s are no longer slippery.";
case 18:return "%s as good as new!";
case 19:return "%s can hear again";
case 20:return "%s diabolical laughter all around you...";
case 21:return "%s disintegrates into a pile of dust!";
case 22:return "%s feels content.";
case 23:return "%s fries to a crisp!";
case 24:return "%s glow surrounds you.";
case 25:return "%s goes snicker-snack!";
case 26:return "%s hums ominously!";
case 27:return "%s indifference";
case 28:return "%s is enraged...";
case 29:return "%s is not deterred...";
case 30:return "%s potion%s on the altar glow%s %s for a moment.";
case 31:return "%s reflects from your %s.";
case 32:return "%s rejects your sacrifice!";
case 33:return "%s seems %s.";
case 34:return "%s seems unaffected.";
case 35:return "%s shrugs and retains dominion over %s,";
case 36:return "%s snarls and tries again...";
case 37:return "%s sword";
case 38:return "%s with %s aura%s.";
case 39:return "%s!";
case 40:return "%s.";
case 41:return "%sstronger.";
case 42:return "?) whispers";
case 43:return "A cloud of %s smoke surrounds you...";
case 44:return "A sword";
case 45:return "A voice (could it be";
case 46:return "A wide-angle disintegration beam aimed at you hits %s!";
case 47:return "A wide-angle disintegration beam hits you!";
case 48:return "An invisible choir chants, and you are bathed in darkness...";
case 49:return "An invisible choir sings, and you are bathed in radiance...";
case 50:return "AnDoR dRaKoN";
case 51:return "Are you sure you want to pray?";
case 52:return "Calling upon %s, you chant an arcane formula.";
case 53:return "Confused deity!";
case 54:return "Cthulhu";
case 55:return "Despite your deafness, you seem to hear";
case 56:return "Destroy %s, my servants!";
case 57:return "Divine knowledge of %s fills your mind!  Spell '%c'.";
case 58:return "Eris";
case 59:return "For some reason you're unaffected.";
case 60:return "For some reason, %s seems to ignore you.";
case 61:return "Force the gods to be pleased?";
case 62:return "Fortunately, %s permits you to live...";
case 63:return "Gift an artifact?";
case 64:return "Hark, %s!";
case 65:return "High Temple";
case 66:return "How darest thou desecrate my altar!";
case 67:return "I believe it not!";
case 68:return "I crown thee...  The Hand of Elbereth!";
case 69:return "In return for thy service, I grant thee the gift of Immortality!";
case 70:return "It";
case 71:return "It seems not to affect you.";
case 72:return "It sounds like:  \"%s\".";
case 73:return "It strikes %s!";
case 74:return "Looks like you are back in Kansas.";
case 75:return "Moloch";
case 76:return "Morgoth";
case 77:return "Mortal, thou hast done well!";
case 78:return "No random god name?";
case 79:return "Nothing else happens.";
case 80:return "Oh, no.";
case 81:return "Om";
case 82:return "One of the";
case 83:return "Overall, there is a smell of fried onions.";
case 84:return "Since you are in Gehennom, %s %s help you.";
case 85:return "Since you are in Gehennom, %s can't help you.";
case 86:return "So this is how you repay loyalty?";
case 87:return "So, mortal!  You dare desecrate my %s!";
case 88:return "Some of the";
case 89:return "Speed";
case 90:return "Stealth";
case 91:return "Such an action is an insult to %s!";
case 92:return "Suddenly a bolt of lightning comes down at you from the heavens!";
case 93:return "Suddenly, a bolt of lightning strikes you!";
case 94:return "Suddenly, you realize that %s has noticed you...";
case 95:return "Suffer, infidel!";
case 96:return "Telepathy";
case 97:return "The";
case 98:return "The blood floods the altar, which vanishes in %s cloud!";
case 99:return "The slime disappears.";
case 100:return "There's a tiger in your tank.";
case 101:return "Thou art chosen to %s for My Glory!";
case 102:return "Thou cannot escape my wrath, mortal!";
case 103:return "Thou durst %s me?";
case 104:return "Thou hast angered me.";
case 105:return "Thou hast pleased me with thy progress,";
case 106:return "Thou must relearn thy lessons!";
case 107:return "Thou shalt be my Envoy of Balance!";
case 108:return "Thou shalt pay, infidel!";
case 109:return "To enter the castle, thou must play the right tune!";
case 110:return "Tooth Fairy";
case 111:return "Unfortunately, your voice falters.";
case 112:return "Unluckily, you feel the power of %s decrease.";
case 113:return "Use it wisely in my name!";
case 114:return "Use my gift wisely!";
case 115:return "Vile creature, thou durst call upon me?";
case 116:return "Walk no more, perversion of nature!";
case 117:return "Xom";
case 118:return "Yawgmoth";
case 119:return "You";
case 120:return "You feel more limber.";
case 121:return "You finish your prayer.";
case 122:return "You'll regret this infamous offense!";
case 123:return "Your %s %s better";
case 124:return "Your left ring softly glows";
case 125:return "Your right ring softly glows";
case 126:return "a divine music...";
case 127:return "a doodad";
case 128:return "a nearby thunderclap.";
case 129:return "altar";
case 130:return "altar glows %s.";
case 131:return "altar is stained with %s blood.";
case 132:return "altar_wrath";
case 133:return "amulet vanishes!";
case 134:return "an object";
case 135:return "an urge to return to the surface";
case 136:return "angrygods";
case 137:return "appear";
case 138:return "appropriately %s.";
case 139:return "are";
case 140:return "are %s upon %s to turn aside evilness.";
case 141:return "are not %s an altar.";
case 142:return "are surrounded by %s aura.";
case 143:return "are surrounded by %s glow.";
case 144:return "are surrounded by a shimmering light.";
case 145:return "are terrified, and unable to move.";
case 146:return "are too impaired to perform the rite.";
case 147:return "art arrogant";
case 148:return "ascend to the status of Demigod%s...";
case 149:return "ashamed";
case 150:return "at";
case 151:return "balance";
case 152:return "bask in its %s glow for a minute...";
case 153:return "became %s Envoy of Balance";
case 154:return "begin praying to %s.";
case 155:return "being terrified of a demon";
case 156:return "beneath";
case 157:return "bestow_artifact";
case 158:return "better.";
case 159:return "blood coagulates";
case 160:return "blood covers the altar!";
case 161:return "boo-boo";
case 162:return "booms";
case 163:return "booms out";
case 164:return "bummed";
case 165:return "burst of flame";
case 166:return "call upon";
case 167:return "can breathe again.";
case 168:return "can't";
case 169:return "can_pray";
case 170:return "chain disappears.";
case 171:return "chaos";
case 172:return "cloud dissipates";
case 173:return "consume_offering";
case 174:return "cosmic (not a new fact)";
case 175:return "creature";
case 176:return "dess";
case 177:return "destiny";
case 178:return "disintegrate into a pile of dust";
case 179:return "displeased";
case 180:return "don't know how to turn undead!";
case 181:return "drop";
case 182:return "feel";
case 183:return "find the idea very satisfying.";
case 184:return "fix_curse_trouble: nothing to uncurse.";
case 185:return "fix_worst_trouble";
case 186:return "fix_worst_trouble: couldn't cure hands.";
case 187:return "flash of light";
case 188:return "fry to a crisp";
case 189:return "full";
case 190:return "give_spell";
case 191:return "glimpse a four-leaf clover at your %s.";
case 192:return "god";
case 193:return "goddess";
case 194:return "gods seem tall.";
case 195:return "godvoice";
case 196:return "gray";
case 197:return "groovy";
case 198:return "had %s wielded %s transformed into %s";
case 199:return "hast strayed from the path";
case 200:return "have a feeling of inadequacy.";
case 201:return "have a feeling of reconciliation.";
case 202:return "have a hopeful feeling.";
case 203:return "have a strong feeling that %s is angry...";
case 204:return "have summoned %s!";
case 205:return "hear";
case 206:return "homesick";
case 207:return "in good health again.";
case 208:return "incapable of calling";
case 209:return "intuit";
case 210:return "it";
case 211:return "knowledge of spell '%c' - %s is %s.";
case 212:return "land";
case 213:return "law";
case 214:return "lawful";
case 215:return "like you are falling apart.";
case 216:return "look";
case 217:return "mistake";
case 218:return "mollified";
case 219:return "mortal";
case 220:return "much ";
case 221:return "much better.";
case 222:return "much slimmer.";
case 223:return "my protection";
case 224:return "neutral";
case 225:return "not able to call";
case 226:return "offer the Amulet of Yendor to %s...";
case 227:return "offer_different_alignment_altar";
case 228:return "on";
case 229:return "over";
case 230:return "partially absolved.";
case 231:return "pleased";
case 232:return "pleased as punch";
case 233:return "plume of smoke";
case 234:return "pray.c";
case 235:return "prayer_done";
case 236:return "praying";
case 237:return "realize that the gods are not like you and I.";
case 238:return "realize you have made a %s.";
case 239:return "refreshed";
case 240:return "rejected atheism by offering %s on an altar of %s";
case 241:return "rejected atheism by turning undead";
case 242:return "rejected atheism with a prayer";
case 243:return "residual undead turning effect";
case 244:return "restored";
case 245:return "rings out";
case 246:return "rn2 broken in halu_gname?!?";
case 247:return "s";
case 248:return "sacrifice";
case 249:return "sacrifice collapses into a cloud of dancing particles and fades away!";
case 250:return "sacrifice disappears!";
case 251:return "sacrifice is consumed in a %s!";
case 252:return "sacrifice puffs up, swelling bigger and bigger, and pops!";
case 253:return "sacrifice sprouts wings and a propeller and roars away!";
case 254:return "satisfied";
case 255:return "scorn";
case 256:return "see crabgrass at your %s.  A funny thing in a dungeon.";
case 257:return "sense a conflict between %s and %s.";
case 258:return "shape becomes uncertain.";
case 259:return "slightly mollified";
case 260:return "softly glow";
case 261:return "someone";
case 262:return "something dreadful";
case 263:return "steal souls";
case 264:return "surroundings change.";
case 265:return "sword shines brightly for a moment.";
case 266:return "take lives";
case 267:return "that %s is %s.";
case 268:return "the Central Bank of Yendor";
case 269:return "the Flying Spaghetti Monster";
case 270:return "the Martians";
case 271:return "the Ori";
case 272:return "the air around you grow charged...";
case 273:return "the blessing of %s over %s.";
case 274:return "the power of %s increase.";
case 275:return "the power of %s over %s.";
case 276:return "the power of %s.";
case 277:return "the wrath of %s";
case 278:return "then mercilessly snuffs out your life.";
case 279:return "think %s brushed your %s.";
case 280:return "thunders";
case 281:return "ticklish";
case 282:return "trying to turn the monsters";
case 283:return "unknown alignment.";
case 284:return "unworthy.";
case 285:return "very idea of praying to a %s god is repugnant to you.";
case 286:return "voice of %s %s: %s%s%s";
case 287:return "was bestowed with %s";
case 288:return "was bestowed with %s by %s";
case 289:return "was chosen to %s for the Glory of %s";
case 290:return "was crowned \"The Hand of Elbereth\" by %s";
case 291:return "well-pleased";
case 292:return "won't";
case 293:return "you are thoroughly on the right path.";
case 294:return "your Friend the Computer";
default:return 0;}
#else
return 0;
#endif
}
int probe_string_count(void){return 6
#ifndef HYBRID_PRAY
+295
#endif
;}
size_t probe_string_capacity(int i){const char*p=probe_string(i);return p?strlen(p)+1:0;}
