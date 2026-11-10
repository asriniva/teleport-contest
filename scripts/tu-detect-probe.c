/* DETECT controlled dependency fixture: no detection algorithm fallback. */
#include "hack.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <emscripten.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
__typeof__(u) u;
__typeof__(iflags) iflags;
__typeof__(def_monsyms) def_monsyms={[S_GHOST]={.sym=' '}};
__typeof__(mons) mons;
__typeof__(gi) gi;
__typeof__(svl) svl;
__typeof__(objects) objects;
__typeof__(gk) gk;
__typeof__(gy) gy;
__typeof__(cg) cg={.zeroobj={.o_id=0x12345678,.quan=9007199254741007L,.owornmask=0x65432100L}};
__typeof__(c_common_strings) c_common_strings={.c_something="something",.c_Never_mind="Never mind",.c_vision_clears="vision clears"};
__typeof__(flags) flags;
__typeof__(def_oc_syms) def_oc_syms={[COIN_CLASS]={.name="coins",.sym='$'},[FOOD_CLASS]={.name="food",.sym='%'},[ROCK_CLASS]={.name="rocks",.sym='`'}};
__typeof__(gs) gs;
__typeof__(WIN_MAP) WIN_MAP;
__typeof__(windowprocs) windowprocs;
__typeof__(gu) gu;
__typeof__(svd) svd;
__typeof__(gf) gf;
__typeof__(gd) gd;
__typeof__(gm) gm;
__typeof__(gn) gn;
__typeof__(quitchars) quitchars="\033 q";
__typeof__(gv) gv;
__typeof__(WIN_MESSAGE) WIN_MESSAGE;
__typeof__(uwep) uwep;
__typeof__(ublindf) ublindf;
__typeof__(ga) ga;
static seenV viz[ROWNO][COLNO];static seenV*vizrows[ROWNO];static struct obj objpool[8],captured[32];static unsigned captured_count;static struct monst monpool[4];static struct trap trappool[4];static d_level levelpool[4];static coord coordpool[4];static int intpool[8];static struct obj*slotpool[8];static NhRegion regionpool[2];static struct engr engrpool[2];static char bufferpool[4096];static char tracebuf[262144];static size_t traceused;static unsigned seed=1;static int rngvalue=0,result=0,query='q',grow=0,reentry=0,observeCount=0;static long wide=0;static int glyph_override=-1;
static void append(const char*fmt,...){va_list ap;va_start(ap,fmt);int n=vsnprintf(tracebuf+traceused,sizeof tracebuf-traceused,fmt,ap);va_end(ap);if(n<0||(size_t)n>=sizeof tracebuf-traceused)abort();traceused+=(size_t)n;}
static int pointerid(const void*p){if(!p)return 0;for(int i=0;i<8;i++)if(p==&objpool[i])return 100+i;for(int i=0;i<4;i++){if(p==&monpool[i])return 200+i;if(p==&trappool[i])return 300+i;if(p==&levelpool[i])return 400+i;}return -1;}
static void callback_window(winid id,boolean block){append("window:%d:%d;",id,block);}
static void hook(void){if(grow){grow=0;emscripten_resize_heap(emscripten_get_heap_size()+65536);}if(reentry){reentry=0;(void)trapped_door_at(TRAPPED_DOOR,10,10);}}
static uint64_t pointertoken(const void*p){uintptr_t a=(uintptr_t)p;if(!p)return 0;
if(a>=(uintptr_t)&objpool&&a<(uintptr_t)&objpool+sizeof objpool)return 100000+a-(uintptr_t)&objpool;
if(a>=(uintptr_t)&monpool&&a<(uintptr_t)&monpool+sizeof monpool)return 200000+a-(uintptr_t)&monpool;
if(a>=(uintptr_t)&trappool&&a<(uintptr_t)&trappool+sizeof trappool)return 300000+a-(uintptr_t)&trappool;
if(a>=(uintptr_t)&levelpool&&a<(uintptr_t)&levelpool+sizeof levelpool)return 400000+a-(uintptr_t)&levelpool;
if(a>=(uintptr_t)&coordpool&&a<(uintptr_t)&coordpool+sizeof coordpool)return 500000+a-(uintptr_t)&coordpool;
if(a>=(uintptr_t)&intpool&&a<(uintptr_t)&intpool+sizeof intpool)return 600000+a-(uintptr_t)&intpool;
if(a>=(uintptr_t)&slotpool&&a<(uintptr_t)&slotpool+sizeof slotpool)return 700000+a-(uintptr_t)&slotpool;
if(a>=(uintptr_t)&bufferpool&&a<(uintptr_t)&bufferpool+sizeof bufferpool)return 800000+a-(uintptr_t)&bufferpool;
if(a>=(uintptr_t)&regionpool&&a<(uintptr_t)&regionpool+sizeof regionpool)return 900000+a-(uintptr_t)&regionpool;
if(a>=(uintptr_t)&engrpool&&a<(uintptr_t)&engrpool+sizeof engrpool)return 1000000+a-(uintptr_t)&engrpool;
if(a>=(uintptr_t)&u&&a<(uintptr_t)&u+sizeof u)return 2000000+a-(uintptr_t)&u;
if(a>=(uintptr_t)&iflags&&a<(uintptr_t)&iflags+sizeof iflags)return 2100000+a-(uintptr_t)&iflags;
if(a>=(uintptr_t)&def_monsyms&&a<(uintptr_t)&def_monsyms+sizeof def_monsyms)return 2200000+a-(uintptr_t)&def_monsyms;
if(a>=(uintptr_t)&mons&&a<(uintptr_t)&mons+sizeof mons)return 2300000+a-(uintptr_t)&mons;
if(a>=(uintptr_t)&gi&&a<(uintptr_t)&gi+sizeof gi)return 2400000+a-(uintptr_t)&gi;
if(a>=(uintptr_t)&svl&&a<(uintptr_t)&svl+sizeof svl)return 2500000+a-(uintptr_t)&svl;
if(a>=(uintptr_t)&objects&&a<(uintptr_t)&objects+sizeof objects)return 2600000+a-(uintptr_t)&objects;
if(a>=(uintptr_t)&gk&&a<(uintptr_t)&gk+sizeof gk)return 2700000+a-(uintptr_t)&gk;
if(a>=(uintptr_t)&gy&&a<(uintptr_t)&gy+sizeof gy)return 2800000+a-(uintptr_t)&gy;
if(a>=(uintptr_t)&cg&&a<(uintptr_t)&cg+sizeof cg)return 2900000+a-(uintptr_t)&cg;
if(a>=(uintptr_t)&c_common_strings&&a<(uintptr_t)&c_common_strings+sizeof c_common_strings)return 3000000+a-(uintptr_t)&c_common_strings;
if(a>=(uintptr_t)&flags&&a<(uintptr_t)&flags+sizeof flags)return 3100000+a-(uintptr_t)&flags;
if(a>=(uintptr_t)&def_oc_syms&&a<(uintptr_t)&def_oc_syms+sizeof def_oc_syms)return 3200000+a-(uintptr_t)&def_oc_syms;
if(a>=(uintptr_t)&gs&&a<(uintptr_t)&gs+sizeof gs)return 3300000+a-(uintptr_t)&gs;
if(a>=(uintptr_t)&WIN_MAP&&a<(uintptr_t)&WIN_MAP+sizeof WIN_MAP)return 3400000+a-(uintptr_t)&WIN_MAP;
if(a>=(uintptr_t)&windowprocs&&a<(uintptr_t)&windowprocs+sizeof windowprocs)return 3500000+a-(uintptr_t)&windowprocs;
if(a>=(uintptr_t)&gu&&a<(uintptr_t)&gu+sizeof gu)return 3600000+a-(uintptr_t)&gu;
if(a>=(uintptr_t)&svd&&a<(uintptr_t)&svd+sizeof svd)return 3700000+a-(uintptr_t)&svd;
if(a>=(uintptr_t)&gf&&a<(uintptr_t)&gf+sizeof gf)return 3800000+a-(uintptr_t)&gf;
if(a>=(uintptr_t)&gd&&a<(uintptr_t)&gd+sizeof gd)return 3900000+a-(uintptr_t)&gd;
if(a>=(uintptr_t)&gm&&a<(uintptr_t)&gm+sizeof gm)return 4000000+a-(uintptr_t)&gm;
if(a>=(uintptr_t)&gn&&a<(uintptr_t)&gn+sizeof gn)return 4100000+a-(uintptr_t)&gn;
if(a>=(uintptr_t)&gv&&a<(uintptr_t)&gv+sizeof gv)return 4300000+a-(uintptr_t)&gv;
if(a>=(uintptr_t)&WIN_MESSAGE&&a<(uintptr_t)&WIN_MESSAGE+sizeof WIN_MESSAGE)return 4400000+a-(uintptr_t)&WIN_MESSAGE;
if(a>=(uintptr_t)&uwep&&a<(uintptr_t)&uwep+sizeof uwep)return 4500000+a-(uintptr_t)&uwep;
if(a>=(uintptr_t)&ublindf&&a<(uintptr_t)&ublindf+sizeof ublindf)return 4600000+a-(uintptr_t)&ublindf;
if(a>=(uintptr_t)&ga&&a<(uintptr_t)&ga+sizeof ga)return 4700000+a-(uintptr_t)&ga;
return a;}
void (docrt)(void){append("docrt:;");}
void (under_water)(int a0){append("under_water:%lld;",(long long)a0);}
void (under_ground)(int a0){append("under_ground:%lld;",(long long)a0);}
int (getpos)(coord * a0,boolean a1,const char * a2){append("getpos:%d:%d:%d:%s;",a0->x,a0->y,a1,a2);a0->x=12;a0->y=13;hook();return result;}
int (rn2_on_display_rng)(int a0){if(a0<=0)abort();append("displayrng:%d;",a0);return 1%a0;}
void (show_glyph)(coordxy a0,coordxy a1,int a2){append("show:%d:%d:%d;",a0,a1,a2);levl[a0][a1].glyph=a2;}
void (detect_wsegs)(struct monst * a0,boolean a1){append("detect_wsegs:%lld:%lld;",(long long)pointertoken(a0),(long long)a1);}
int (glyph_at)(coordxy a0,coordxy a1){return glyph_override>=0?glyph_override:levl[a0][a1].glyph;}
boolean (rng_log_enabled)(void){return 1;}
void (rng_log_set_caller)(const char * a0,int a1,const char * a2){append("rng:%s:%d:%s;",a0,a1,a2);}
int (rn2)(int a0){if(a0<=0)abort();seed=seed*1664525u+1013904223u;int v=rngvalue<0?(int)(seed%(unsigned)a0):rngvalue%a0;append("rn2:%d:%d;",a0,v);return v;}
struct obj * (sobj_at)(int a0,coordxy a1,coordxy a2){for(int i=0;i<8;i++)if(objpool[i].otyp==a0&&objpool[i].ox==a1&&objpool[i].oy==a2&&objpool[i].where==OBJ_FLOOR)return &objpool[i];return 0;}
void (observe_object)(struct obj * a0){append("observe:%d;",pointerid(a0));a0->dknown=1;observeCount++;hook();}
void (unmap_object)(coordxy a0,coordxy a1){append("unmap:%d:%d;",a0,a1);levl[a0][a1].glyph=GLYPH_NOTHING;}
struct obj * (findgold)(struct obj * a0){return a0&&a0->oclass==COIN_CLASS?a0:0;}
const char * (currency)(long a0){append("currency:%ld;",a0);return "gold pieces";}
long (money_cnt)(struct obj * a0){return wide;}
long (hidden_gold)(boolean a0){append("hidden:%d;",a0);return wide;}
char * (x_monnam)(struct monst * a0,int a1,const char * a2,int a3,boolean a4){return "monster";}
char * (s_suffix)(const char * a0){return "monster's";}
void (strange_feeling)(struct obj * a0,const char * a1){append("strange_feeling:%lld:%s;",(long long)pointertoken(a0),(a1?a1:"NULL"));}
const char * (body_part)(int a0){return "skin";}
char * (makeplural)(const char * a0){return (char*)a0;}
void (cls)(void){append("cls:;");}
void (map_object)(struct obj * a0,int a1){append("mapobj:%d:%d:%d:%d:%ld:%u;",pointerid(a0),a0->otyp,a0->ox,a0->oy,a0->quan,a0->o_id);if(captured_count>=32)abort();captured[captured_count++]=*a0;levl[a0->ox][a0->oy].glyph=GLYPH_OBJ_OFF+a0->otyp;}
int (rnd)(int a0){if(a0<=0)abort();int v=(rn2)(a0)+1;append("rnd:%d:%d;",a0,v);return v;}
void (newsym)(coordxy a0,coordxy a1){append("newsym:%lld:%lld;",(long long)a0,(long long)a1);}
void (exercise)(int a0,boolean a1){append("exercise:%lld:%lld;",(long long)a0,(long long)a1);}
int (mon_visible)(struct monst * a0){return result;}
boolean (In_mines)(d_level * a0){return a0->dnum==2;}
boolean (In_hell)(d_level * a0){return a0->dnum==3;}
boolean (on_level)(d_level * a0,d_level * a1){return a0->dnum==a1->dnum&&a0->dlevel==a1->dlevel;}
void (map_trap)(struct trap * a0,int a1){append("maptrap:%d:%d:%d:%d:%d;",pointerid(a0),a0->ttyp,a0->tx,a0->ty,a1);levl[a0->tx][a0->ty].glyph=GLYPH_CMAP_B_OFF+S_arrow_trap-S_grave+a0->ttyp-1;}
boolean (get_obj_location)(struct obj * a0,coordxy * a1,coordxy * a2,int a3){append("location:%d:%d;",pointerid(a0),a3);*a1=a0->ox;*a2=a0->oy;return a0->where!=OBJ_FREE;}
int (isok)(coordxy a0,coordxy a1){return a0>=1&&a0<COLNO&&a1>=0&&a1<ROWNO;}
void (flash_glyph_at)(coordxy a0,coordxy a1,int a2,int a3){append("flash_glyph_at:%lld:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2,(long long)a3);}
int (glyph_to_cmap)(int a0){return a0-GLYPH_CMAP_B_OFF+S_grave;}
void (magic_map_background)(coordxy a0,coordxy a1,int a2){append("magic:%d:%d:%d;",a0,a1,a2);levl[a0][a1].glyph=GLYPH_CMAP_STONE_OFF;}
void (seemimic)(struct monst * a0){append("seemimic:%lld;",(long long)pointertoken(a0));}
int (canseemon)(struct monst * a0){return result;}
int (sensemon)(struct monst * a0){return result;}
void (map_invisible)(coordxy a0,coordxy a1){append("invis:%d:%d;",a0,a1);levl[a0][a1].glyph=GLYPH_INVISIBLE;}
schar (depth)(d_level * a0){return a0->dlevel;}
char * (xname)(struct obj * a0){return "crystal ball";}
char * (the)(const char * a0){return (char*)a0;}
boolean (is_quest_artifact)(struct obj * a0){return result;}
schar (acurr)(int a0){return 10;}
char * (Tobjnam)(struct obj * a0,const char * a1){append("objname:%d:%s;",pointerid(a0),a1);return (char*)a1;}
void (make_confused)(long a0,boolean a1){append("confused:%ld:%d;",a0,a1);HConfusion=a0;}
boolean (resists_blnd)(struct monst * a0){return result;}
void (make_blinded)(long a0,boolean a1){append("blinded:%ld:%d;",a0,a1);HBlinded=a0;}
boolean (make_hallucinated)(long a0,boolean a1,long a2){append("hallu:%ld:%d:%ld;",a0,a1,a2);HHallucination=a0;return 1;}
void (useup)(struct obj * a0){append("useup:%d;",pointerid(a0));a0->where=OBJ_FREE;a0->o_id=0xdeadbeef;}
void (losehp)(int a0,const char * a1,schar a2){append("losehp:%d:%s:%d;",a0,a1,a2);}
void (consume_obj_charge)(struct obj * a0,boolean a1){append("charge:%d:%d;",pointerid(a0),a1);a0->spe--;}
void (nomul)(int a0){append("nomul:%d;",a0);}
const char * (hcolor)(const char * a0){return "violet";}
int (poly_gender)(void){return result;}
char (yn_function)(const char * a0,const char * a1,char a2,boolean a3){append("query:%s:%d:%d;",a0,a2,a3);return query;}
void (discover_object)(int a0,boolean a1,boolean a2,boolean a3){append("discover_object:%lld:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2,(long long)a3);}
int (def_char_is_furniture)(char a0){return a0=='_'?S_altar:-1;}
int (def_char_to_objclass)(char a0){return a0=='$'?COIN_CLASS:a0=='%'?FOOD_CLASS:MAXOCLASSES;}
int (def_char_to_monclass)(char a0){return a0=='D'?S_DRAGON:MAXMCLASSES;}
void (unblock_point)(int a0,int a1){append("unblock_point:%lld:%lld;",(long long)a0,(long long)a1);}
struct trap * (t_at)(coordxy a0,coordxy a1){for(struct trap*t=gf.ftrap;t;t=t->ntrap)if(t->tx==a0&&t->ty==a1)return t;return 0;}
struct engr * (engr_at)(coordxy a0,coordxy a1){return 0;}
void (map_engraving)(struct engr * a0,int a1){append("map_engraving:%lld:%lld;",(long long)pointertoken(a0),(long long)a1);}
void (room_discovered)(int a0){append("room_discovered:%lld;",(long long)a0);}
void (flush_screen)(int a0){append("flush_screen:%lld;",(long long)a0);}
boolean (is_pool)(coordxy a0,coordxy a1){return levl[a0][a1].typ==POOL;}
void (see_monsters)(void){append("see_monsters:;");}
void (recalc_block_point)(coordxy a0,coordxy a1){append("recalc_block_point:%lld:%lld;",(long long)a0,(long long)a1);}
int (back_to_glyph)(coordxy a0,coordxy a1){append("back:%d:%d:%d:%u:%u;",a0,a1,levl[a0][a1].typ,levl[a0][a1].flags,levl[a0][a1].seenv);return GLYPH_CMAP_STONE_OFF;}
boolean (closed_door)(coordxy a0,coordxy a1){return levl[a0][a1].typ==DOOR&&(levl[a0][a1].doormask&(D_CLOSED|D_LOCKED));}
boolean (unmap_invisible)(coordxy a0,coordxy a1){append("uninvis:%d:%d;",a0,a1);boolean old=levl[a0][a1].glyph==GLYPH_INVISIBLE;if(old)levl[a0][a1].glyph=GLYPH_NOTHING;return old;}
int (dist2)(coordxy a0,coordxy a1,coordxy a2,coordxy a3){return (a0-a2)*(a0-a2)+(a1-a3)*(a1-a3);}
void (b_trapped)(const char * a0,int a1){append("b_trapped:%s:%d;",a0,a1);}
void (wake_nearto)(coordxy a0,coordxy a1,int a2){append("wake_nearto:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2);}
boolean (openholdingtrap)(struct monst * a0,boolean * a1){append("holding:%d;",pointerid(a0));*a1=1;return result;}
boolean (openfallingtrap)(struct monst * a0,boolean a1,boolean * a2){append("falling:%d:%d;",pointerid(a0),a1);*a2=1;return result;}
boolean (find_drawbridge)(coordxy * a0,coordxy * a1){append("drawbridge:%d:%d;",*a0,*a1);if(result){*a0=11;*a1=12;}return result;}
void (open_drawbridge)(coordxy a0,coordxy a1){append("openbridge:%d:%d;",a0,a1);}
void (do_clear_area)(coordxy a0,coordxy a1,int a2,void (*a3)(coordxy, coordxy, void *),genericptr_t a4){append("area:%d:%d:%d;",a0,a1,a2);for(int x=9;x<=11;x++)for(int y=9;y<=11;y++)a3(x,y,a4);hook();}
char * (eos)(char * a0){return a0+strlen(a0);}
struct attack * (dmgtype_fromattack)(struct permonst * a0,int a1,int a2){return 0;}
char * (Monnam)(struct monst * a0){return "Monster";}
void (expels)(struct monst * a0,struct permonst * a1,boolean a2){append("expels:%lld:%lld:%lld;",(long long)pointertoken(a0),(long long)pointertoken(a1),(long long)a2);}
void (feel_newsym)(coordxy a0,coordxy a1){append("feel_newsym:%lld:%lld;",(long long)a0,(long long)a1);}
void (set_msg_xy)(coordxy a0,coordxy a1){append("set_msg_xy:%lld:%lld;",(long long)a0,(long long)a1);}
const char * (trapname)(int a0,boolean a1){return "fixture trap";}
char * (an)(const char * a0){return (char*)a0;}
int (warning_of)(struct monst * a0){return result;}
char * (y_monnam)(struct monst * a0){return "monster";}
char * (a_monnam)(struct monst * a0){return "a monster";}
boolean (spec_ability)(struct obj * a0,unsigned long a1){return result;}
NhRegion * (visible_region_at)(coordxy a0,coordxy a1){return regionpool[0].visible?&regionpool[0]:0;}
void (feel_location)(coordxy a0,coordxy a1){append("feel:%d:%d;",a0,a1);}
int (rnl)(int a0){if(a0<=0)abort();int v=(rn2)(a0);append("rnl:%d:%d;",a0,v);return v;}
struct monst * (activate_statue_trap)(struct trap * a0,coordxy a1,coordxy a2,boolean a3){append("activate:%d:%d;",a1,a2);return result?&monpool[0]:0;}
boolean (cmd_safety_prevention)(const char * a0,const char * a1,const char * a2,int * a3){append("safety:%s:%s:%s;",a0,a1,a2);*a3=1;return result;}
void (map_background)(coordxy a0,coordxy a1,int a2){append("background:%d:%d:%d;",a0,a1,a2);levl[a0][a1].glyph=GLYPH_CMAP_STONE_OFF;}
void (xy_set_wall_state)(coordxy a0,coordxy a1){append("wallstate:%d:%d;",a0,a1);levl[a0][a1].flags=31;levl[a0][a1].glyph=0x1abcde;}
void (Norep)(const char*fmt,...){char b[4096];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("Norep:%s;",b);}
void (There)(const char*fmt,...){char b[4096];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("There:%s;",b);}
void (You)(const char*fmt,...){char b[4096];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("You:%s;",b);}
void (You_feel)(const char*fmt,...){char b[4096];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("You_feel:%s;",b);}
void (You_see)(const char*fmt,...){char b[4096];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("You_see:%s;",b);}
void (Your)(const char*fmt,...){char b[4096];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("Your:%s;",b);}
void (impossible)(const char*fmt,...){char b[4096];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("impossible:%s;",b);}
void (pline)(const char*fmt,...){char b[4096];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("pline:%s;",b);}
void (pline_The)(const char*fmt,...){char b[4096];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("pline_The:%s;",b);}
#ifdef HYBRID_DETECT
#include "../nethack-c/wasm/tu-fragments/detect-types.h"
extern boolean teleport_detect_unconstrain_map(void);
#define unconstrain_map teleport_detect_unconstrain_map
extern void teleport_detect_reconstrain_map(void);
#define reconstrain_map teleport_detect_reconstrain_map
extern void teleport_detect_map_redisplay(void);
#define map_redisplay teleport_detect_map_redisplay
extern void teleport_detect_browse_map(unsigned int ter_typ,const char * ter_explain);
#define browse_map teleport_detect_browse_map
extern void teleport_detect_map_monst(struct monst * mtmp,boolean showtail);
#define map_monst teleport_detect_map_monst
extern void teleport_detect_observe_recursively(struct obj * obj);
#define observe_recursively teleport_detect_observe_recursively
extern boolean teleport_detect_check_map_spot(coordxy x,coordxy y,char oclass,unsigned int material);
#define check_map_spot teleport_detect_check_map_spot
extern boolean teleport_detect_clear_stale_map(char oclass,unsigned int material);
#define clear_stale_map teleport_detect_clear_stale_map
extern void teleport_detect_sense_trap(struct trap * trap,coordxy x,coordxy y,int src_cursed);
#define sense_trap teleport_detect_sense_trap
extern int teleport_detect_detect_obj_traps(struct obj * objlist,boolean show_them,int how,struct found_things * ft);
#define detect_obj_traps teleport_detect_detect_obj_traps
extern void teleport_detect_display_trap_map(int cursed_src);
#define display_trap_map teleport_detect_display_trap_map
extern int teleport_detect_furniture_detect(void);
#define furniture_detect teleport_detect_furniture_detect
extern void teleport_detect_foundone(coordxy zx,coordxy zy,int glyph);
#define foundone teleport_detect_foundone
extern void teleport_detect_findone(coordxy zx,coordxy zy,genericptr_t whatfound);
#define findone teleport_detect_findone
extern void teleport_detect_openone(coordxy zx,coordxy zy,genericptr_t num);
#define openone teleport_detect_openone
extern int teleport_detect_mfind0(struct monst * mtmp,boolean via_warning);
#define mfind0 teleport_detect_mfind0
extern boolean teleport_detect_skip_premap_detect(coordxy x,coordxy y);
#define skip_premap_detect teleport_detect_skip_premap_detect
extern int teleport_detect_reveal_terrain_getglyph(coordxy x,coordxy y,unsigned int swallowed,int default_glyph,unsigned int which_subset);
#define reveal_terrain_getglyph teleport_detect_reveal_terrain_getglyph
#else
#include "../.cache/wasm64-build/tree/src/detect.c"
#define TELEPORT_DETECT_TYPES_H
#define teleport_detect_findone findone
#define teleport_detect_openone openone
#endif
#include "../nethack-c/wasm/tu-fragments/detect-support.c"
#include "tu-detect-layout.h"
#ifdef HYBRID_DETECT
static struct found_things foundpool[4];
#else
static struct found_things foundpool[4];
#endif
uintptr_t probe_pool(int kind,int index){switch(kind){case 0:return(uintptr_t)&objpool[index];case 1:return(uintptr_t)&monpool[index];case 2:return(uintptr_t)&trappool[index];case 3:return(uintptr_t)&levelpool[index];case 4:return(uintptr_t)&coordpool[index];case 5:return(uintptr_t)&intpool[index];case 6:return(uintptr_t)&slotpool[index];case 7:return(uintptr_t)&foundpool[index];case 8:return(uintptr_t)&bufferpool[index];case 9:return(uintptr_t)&captured[index];case 10:return(uintptr_t)&regionpool[index];case 11:return(uintptr_t)&engrpool[index];default:abort();}}
int probe_captured(void){return captured_count;}
int probe_layout_count(void){return sizeof detect_layout/sizeof detect_layout[0];}
const char*probe_layout_name(int i){return detect_layout[i].name;}
int64_t probe_layout_value(int i){return(int64_t)detect_layout[i].value;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
const char*probe_trace(void){return tracebuf;}
void probe_clear_trace(void){traceused=0;tracebuf[0]=0;}
void probe_option(int key,int64_t value){switch(key){case 0:result=value;break;case 1:rngvalue=value;break;case 2:query=value;break;case 3:grow=value;break;case 4:reentry=value;break;case 5:wide=value;break;case 6:glyph_override=value;break;default:abort();}}
uintptr_t probe_function(int i){switch(i){case 0:return(uintptr_t)findone;case 1:return(uintptr_t)openone;case 2:return(uintptr_t)callback_window;default:abort();}}
uint64_t probe_action(int op,uint64_t a,uint64_t b,uint64_t c,uint64_t d,uint64_t e){switch(op){
case 0:return(uint64_t)(uintptr_t)unconstrain_map();
case 1:reconstrain_map();return 0;
case 2:map_redisplay();return 0;
case 3:browse_map((unsigned int)(uintptr_t)a,(const char *)(uintptr_t)b);return 0;
case 4:map_monst((struct monst *)(uintptr_t)a,(boolean)(uintptr_t)b);return 0;
case 5:return(uint64_t)(uintptr_t)trapped_chest_at((int)(uintptr_t)a,(coordxy)(uintptr_t)b,(coordxy)(uintptr_t)c);
case 6:return(uint64_t)(uintptr_t)trapped_door_at((int)(uintptr_t)a,(coordxy)(uintptr_t)b,(coordxy)(uintptr_t)c);
case 7:return(uint64_t)(uintptr_t)o_in((struct obj *)(uintptr_t)a,(char)(uintptr_t)b);
case 8:return(uint64_t)(uintptr_t)o_material((struct obj *)(uintptr_t)a,(unsigned int)(uintptr_t)b);
case 9:observe_recursively((struct obj *)(uintptr_t)a);return 0;
case 10:return(uint64_t)(uintptr_t)check_map_spot((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b,(char)(uintptr_t)c,(unsigned int)(uintptr_t)d);
case 11:return(uint64_t)(uintptr_t)clear_stale_map((char)(uintptr_t)a,(unsigned int)(uintptr_t)b);
case 12:return(uint64_t)(uintptr_t)gold_detect((struct obj *)(uintptr_t)a);
case 13:return(uint64_t)(uintptr_t)food_detect((struct obj *)(uintptr_t)a);
case 14:return(uint64_t)(uintptr_t)object_detect((struct obj *)(uintptr_t)a,(int)(uintptr_t)b);
case 15:return(uint64_t)(uintptr_t)monster_detect((struct obj *)(uintptr_t)a,(int)(uintptr_t)b);
case 16:sense_trap((struct trap *)(uintptr_t)a,(coordxy)(uintptr_t)b,(coordxy)(uintptr_t)c,(int)(uintptr_t)d);return 0;
case 17:return(uint64_t)(uintptr_t)detect_obj_traps((struct obj *)(uintptr_t)a,(boolean)(uintptr_t)b,(int)(uintptr_t)c,(struct found_things *)(uintptr_t)d);
case 18:display_trap_map((int)(uintptr_t)a);return 0;
case 19:return(uint64_t)(uintptr_t)trap_detect((struct obj *)(uintptr_t)a);
case 20:return(uint64_t)(uintptr_t)furniture_detect();
case 21:return(uint64_t)(uintptr_t)level_distance((d_level *)(uintptr_t)a);
case 22:use_crystal_ball((struct obj **)(uintptr_t)a);return 0;
case 23:show_map_spot((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b,(boolean)(uintptr_t)c);return 0;
case 24:do_mapping();return 0;
case 25:do_vicinity_map((struct obj *)(uintptr_t)a);return 0;
case 26:cvt_sdoor_to_door((struct rm *)(uintptr_t)a);return 0;
case 27:foundone((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b,(int)(uintptr_t)c);return 0;
case 28:findone((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b,(genericptr_t)(uintptr_t)c);return 0;
case 29:openone((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b,(genericptr_t)(uintptr_t)c);return 0;
case 30:return(uint64_t)(uintptr_t)findit();
case 31:return(uint64_t)(uintptr_t)openit();
case 32:return(uint64_t)(uintptr_t)detecting((void (*)(coordxy, coordxy, genericptr_t))(uintptr_t)a);
case 33:find_trap((struct trap *)(uintptr_t)a);return 0;
case 34:return(uint64_t)(uintptr_t)mfind0((struct monst *)(uintptr_t)a,(boolean)(uintptr_t)b);
case 35:return(uint64_t)(uintptr_t)dosearch0((int)(uintptr_t)a);
case 36:return(uint64_t)(uintptr_t)dosearch();
case 37:warnreveal();return 0;
case 38:return(uint64_t)(uintptr_t)skip_premap_detect((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b);
case 39:premap_detect();return 0;
case 40:return(uint64_t)(uintptr_t)reveal_terrain_getglyph((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b,(unsigned int)(uintptr_t)c,(int)(uintptr_t)d,(unsigned int)(uintptr_t)e);
case 41:reveal_terrain((unsigned int)(uintptr_t)a);return 0;
default:abort();}}
/* Fixture reset preserves the const species index; all other bytes are mutable. */
static void teleport_detect_reset_species(struct permonst *first, size_t count)
{
    const size_t start = offsetof(struct permonst, pmidx);
    const size_t end = start + sizeof first->pmidx;
    for (size_t i = 0; i < count; ++i) {
        unsigned char *bytes = (unsigned char *) &first[i];
        memset(bytes, 0, start);
        memset(bytes + end, 0, sizeof first[i] - end);
    }
}
/* Read actual bytes through volatile access, independently of const propagation. */
int probe_const_reset(void)
{
    struct permonst specimen = { .pmidx = PM_HUMAN, .mlet = 'x', .mflags1 = 1UL };
    const size_t start = offsetof(struct permonst, pmidx);
    const size_t width = sizeof specimen.pmidx;
    unsigned char before[sizeof specimen.pmidx];
    volatile unsigned char *bytes = (volatile unsigned char *) &specimen;
    int nonzero = 0;
    for (size_t i = 0; i < width; ++i) {
        before[i] = bytes[start + i];
        nonzero |= before[i];
    }
    if (!nonzero) return 0;
    teleport_detect_reset_species(&specimen, 1);
    for (size_t i = 0; i < sizeof specimen; ++i) {
        if (i >= start && i < start + width) {
            if (bytes[i] != before[i - start]) return 0;
        } else if (bytes[i] != 0) return 0;
    }
    return 1;
}
void probe_reset(void){traceused=0;tracebuf[0]=0;seed=1;rngvalue=0;result=0;query='q';grow=0;reentry=0;observeCount=0;wide=0;glyph_override=-1;captured_count=0;memset(objpool,0,sizeof objpool);memset(monpool,0,sizeof monpool);memset(trappool,0,sizeof trappool);memset(levelpool,0,sizeof levelpool);memset(coordpool,0,sizeof coordpool);memset(intpool,0,sizeof intpool);memset(slotpool,0,sizeof slotpool);memset(foundpool,0,sizeof foundpool);memset(bufferpool,0,sizeof bufferpool);memset(captured,0,sizeof captured);memset(regionpool,0,sizeof regionpool);memset(engrpool,0,sizeof engrpool);
memset((void*)&u,0,sizeof u);
memset((void*)&iflags,0,sizeof iflags);
teleport_detect_reset_species(mons, SIZE(mons));
memset((void*)&gi,0,sizeof gi);
memset((void*)&svl,0,sizeof svl);
memset((void*)&objects,0,sizeof objects);
memset((void*)&gk,0,sizeof gk);
memset((void*)&gy,0,sizeof gy);
memset((void*)&flags,0,sizeof flags);
memset((void*)&gs,0,sizeof gs);
memset((void*)&WIN_MAP,0,sizeof WIN_MAP);
memset((void*)&windowprocs,0,sizeof windowprocs);
memset((void*)&gu,0,sizeof gu);
memset((void*)&svd,0,sizeof svd);
memset((void*)&gf,0,sizeof gf);
memset((void*)&gd,0,sizeof gd);
memset((void*)&gm,0,sizeof gm);
memset((void*)&gn,0,sizeof gn);
memset((void*)&gv,0,sizeof gv);
memset((void*)&WIN_MESSAGE,0,sizeof WIN_MESSAGE);
memset((void*)&uwep,0,sizeof uwep);
memset((void*)&ublindf,0,sizeof ublindf);
memset((void*)&ga,0,sizeof ga);
memset(viz,0,sizeof viz);for(int i=0;i<ROWNO;i++)vizrows[i]=viz[i];gv.viz_array=vizrows;for(int i=0;i<COLNO;i++)for(int k=0;k<ROWNO;k++){levl[i][k].typ=ROOM;levl[i][k].glyph=GLYPH_NOTHING;}u.ux=u.uy=10;u.uz.dnum=0;u.uz.dlevel=5;u.umonnum=u.umonster=PM_HUMAN;gy.youmonst.data=&mons[PM_HUMAN];for(int i=0;i<4;i++){monpool[i].data=&mons[PM_HUMAN];monpool[i].mx=10+i;monpool[i].my=10;monpool[i].mhp=1;trappool[i].ttyp=BEAR_TRAP;trappool[i].tx=10+i;trappool[i].ty=10;levelpool[i].dlevel=10+i;}for(int i=0;i<8;i++){objpool[i].otyp=APPLE;objpool[i].oclass=FOOD_CLASS;objpool[i].ox=10;objpool[i].oy=10;objpool[i].quan=1;objpool[i].where=OBJ_FLOOR;}windowprocs.win_display_nhwindow=callback_window;}
uintptr_t probe_dummytrap(void){
#ifdef HYBRID_DETECT
return(uintptr_t)&detect_dummytrap;
#else
return(uintptr_t)&dummytrap;
#endif
}
int64_t probe_constant(int i){static const int64_t c[]={D_NODOOR,D_BROKEN,D_ISOPEN,D_CLOSED,D_LOCKED,D_TRAPPED,W_NONDIGGABLE,W_NONPASSWALL,TER_MAP,TER_TRP,TER_OBJ,TER_MON,TER_FULL,ROOM,GLYPH_NOTHING,GLYPH_INVISIBLE,APPLE,OBJ_FREE,OBJ_FLOOR,OBJ_CONTAINED,OBJ_INVENT,BLINDFOLD,I_SPECIAL};return c[i];}
void probe_marker(int i,uint64_t v){objpool[i].o_id=(unsigned int)v;}
const char*probe_level_what(int i){
#ifdef HYBRID_DETECT
return 0;
#else
return level_detects[i].what;
#endif
}
uintptr_t probe_level_where(int i){
#ifdef HYBRID_DETECT
return 0;
#else
return(uintptr_t)level_detects[i].where;
#endif
}
