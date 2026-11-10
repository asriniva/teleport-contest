/* Controlled DISPLAY world/window dependencies; no terminal transport. */
#include "hack.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <setjmp.h>
#include <errno.h>
__typeof__(u) u;
__typeof__(svc) svc;
__typeof__(gv) gv;
__typeof__(flags) flags;
__typeof__(svl) svl;
__typeof__(svd) svd;
__typeof__(iflags) iflags;
__typeof__(go) go;
__typeof__(cg) cg;
__typeof__(gi) gi;
__typeof__(program_state) program_state;
__typeof__(uball) uball;
__typeof__(uchain) uchain;
__typeof__(gy) gy;
__typeof__(gu) gu;
const int shield_static[21]={0};
__typeof__(windowprocs) windowprocs;
__typeof__(gd) gd;
__typeof__(gw) gw;
__typeof__(gf) gf;
__typeof__(gg) gg;
__typeof__(disp) disp;
__typeof__(WIN_MAP) WIN_MAP;
__typeof__(gs) gs;
__typeof__(a11y) a11y;
__typeof__(WIN_MESSAGE) WIN_MESSAGE;
__typeof__(gc) gc;
__typeof__(sysopt) sysopt;
__typeof__(mons) mons;
__typeof__(objects) objects;
__typeof__(def_warnsyms) def_warnsyms;
__typeof__(defsyms) defsyms;
__typeof__(svm) svm;
extern const glyph_info nul_glyphinfo;
extern glyph_map glyphmap[9624];
extern const int zapcolors[8];
extern const int altarcolors[5];
extern const int explodecolors[7];
extern int wallcolors[5];
extern const seenV seenv_matrix[3][3];

extern glyph_map glyphmap[MAX_GLYPH];extern const seenV seenv_matrix[3][3];
static const char detailtext[]="fixture detail";static char tracebuf[4194304];static size_t traceused;static int options[64],errorcode,draws;static uint32_t seed=1;static jmp_buf panicframe;
static unsigned char scratch[65536],startup[400000],glyph_events[16384][96];static int nglyph_events;static size_t startupused;static int startupcalls;
static struct monst monsters[8];static struct obj objlist[8];static struct trap traps[8];static struct engr engravings[8];static NhRegion regions[8];static stairway stairs[8];
static unsigned char vision[ROWNO][COLNO];static unsigned char*visionrows[ROWNO];
static void*allocations[4096];static size_t allocsizes[4096];static int nalloc,alloclive[4096];static coord*callercoord;
static void logfmt(const char*fmt,...){va_list ap;va_start(ap,fmt);int n=vsnprintf(tracebuf+traceused,sizeof tracebuf-traceused,fmt,ap);va_end(ap);if(n<0||(size_t)n>=sizeof tracebuf-traceused)abort();traceused+=n;}
static void ptrlog(const void*p){if(!p){logfmt("0");return;}

if((uintptr_t)p>=(uintptr_t)(&u)&&(uintptr_t)p<(uintptr_t)(&u)+(sizeof u)){logfmt("u+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&u)));return;}
if((uintptr_t)p>=(uintptr_t)(&svc)&&(uintptr_t)p<(uintptr_t)(&svc)+(sizeof svc)){logfmt("svc+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&svc)));return;}
if((uintptr_t)p>=(uintptr_t)(&gv)&&(uintptr_t)p<(uintptr_t)(&gv)+(sizeof gv)){logfmt("gv+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&gv)));return;}
if((uintptr_t)p>=(uintptr_t)(&flags)&&(uintptr_t)p<(uintptr_t)(&flags)+(sizeof flags)){logfmt("flags+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&flags)));return;}
if((uintptr_t)p>=(uintptr_t)(&svl)&&(uintptr_t)p<(uintptr_t)(&svl)+(sizeof svl)){logfmt("svl+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&svl)));return;}
if((uintptr_t)p>=(uintptr_t)(&svd)&&(uintptr_t)p<(uintptr_t)(&svd)+(sizeof svd)){logfmt("svd+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&svd)));return;}
if((uintptr_t)p>=(uintptr_t)(&iflags)&&(uintptr_t)p<(uintptr_t)(&iflags)+(sizeof iflags)){logfmt("iflags+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&iflags)));return;}
if((uintptr_t)p>=(uintptr_t)(&go)&&(uintptr_t)p<(uintptr_t)(&go)+(sizeof go)){logfmt("go+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&go)));return;}
if((uintptr_t)p>=(uintptr_t)(&cg)&&(uintptr_t)p<(uintptr_t)(&cg)+(sizeof cg)){logfmt("cg+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&cg)));return;}
if((uintptr_t)p>=(uintptr_t)(&gi)&&(uintptr_t)p<(uintptr_t)(&gi)+(sizeof gi)){logfmt("gi+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&gi)));return;}
if((uintptr_t)p>=(uintptr_t)(&program_state)&&(uintptr_t)p<(uintptr_t)(&program_state)+(sizeof program_state)){logfmt("program_state+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&program_state)));return;}
if((uintptr_t)p>=(uintptr_t)(&uball)&&(uintptr_t)p<(uintptr_t)(&uball)+(sizeof uball)){logfmt("uball+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&uball)));return;}
if((uintptr_t)p>=(uintptr_t)(&uchain)&&(uintptr_t)p<(uintptr_t)(&uchain)+(sizeof uchain)){logfmt("uchain+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&uchain)));return;}
if((uintptr_t)p>=(uintptr_t)(&gy)&&(uintptr_t)p<(uintptr_t)(&gy)+(sizeof gy)){logfmt("gy+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&gy)));return;}
if((uintptr_t)p>=(uintptr_t)(&gu)&&(uintptr_t)p<(uintptr_t)(&gu)+(sizeof gu)){logfmt("gu+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&gu)));return;}
if((uintptr_t)p>=(uintptr_t)(&shield_static)&&(uintptr_t)p<(uintptr_t)(&shield_static)+(sizeof shield_static)){logfmt("shield_static+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&shield_static)));return;}
if((uintptr_t)p>=(uintptr_t)(&windowprocs)&&(uintptr_t)p<(uintptr_t)(&windowprocs)+(sizeof windowprocs)){logfmt("windowprocs+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&windowprocs)));return;}
if((uintptr_t)p>=(uintptr_t)(&gd)&&(uintptr_t)p<(uintptr_t)(&gd)+(sizeof gd)){logfmt("gd+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&gd)));return;}
if((uintptr_t)p>=(uintptr_t)(&gw)&&(uintptr_t)p<(uintptr_t)(&gw)+(sizeof gw)){logfmt("gw+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&gw)));return;}
if((uintptr_t)p>=(uintptr_t)(&gf)&&(uintptr_t)p<(uintptr_t)(&gf)+(sizeof gf)){logfmt("gf+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&gf)));return;}
if((uintptr_t)p>=(uintptr_t)(&gg)&&(uintptr_t)p<(uintptr_t)(&gg)+(sizeof gg)){logfmt("gg+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&gg)));return;}
if((uintptr_t)p>=(uintptr_t)(&disp)&&(uintptr_t)p<(uintptr_t)(&disp)+(sizeof disp)){logfmt("disp+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&disp)));return;}
if((uintptr_t)p>=(uintptr_t)(&WIN_MAP)&&(uintptr_t)p<(uintptr_t)(&WIN_MAP)+(sizeof WIN_MAP)){logfmt("WIN_MAP+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&WIN_MAP)));return;}
if((uintptr_t)p>=(uintptr_t)(&gs)&&(uintptr_t)p<(uintptr_t)(&gs)+(sizeof gs)){logfmt("gs+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&gs)));return;}
if((uintptr_t)p>=(uintptr_t)(&a11y)&&(uintptr_t)p<(uintptr_t)(&a11y)+(sizeof a11y)){logfmt("a11y+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&a11y)));return;}
if((uintptr_t)p>=(uintptr_t)(&WIN_MESSAGE)&&(uintptr_t)p<(uintptr_t)(&WIN_MESSAGE)+(sizeof WIN_MESSAGE)){logfmt("WIN_MESSAGE+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&WIN_MESSAGE)));return;}
if((uintptr_t)p>=(uintptr_t)(&gc)&&(uintptr_t)p<(uintptr_t)(&gc)+(sizeof gc)){logfmt("gc+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&gc)));return;}
if((uintptr_t)p>=(uintptr_t)(&sysopt)&&(uintptr_t)p<(uintptr_t)(&sysopt)+(sizeof sysopt)){logfmt("sysopt+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&sysopt)));return;}
if((uintptr_t)p>=(uintptr_t)(&mons)&&(uintptr_t)p<(uintptr_t)(&mons)+(sizeof mons)){logfmt("mons+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&mons)));return;}
if((uintptr_t)p>=(uintptr_t)(&objects)&&(uintptr_t)p<(uintptr_t)(&objects)+(sizeof objects)){logfmt("objects+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&objects)));return;}
if((uintptr_t)p>=(uintptr_t)(&def_warnsyms)&&(uintptr_t)p<(uintptr_t)(&def_warnsyms)+(sizeof def_warnsyms)){logfmt("def_warnsyms+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&def_warnsyms)));return;}
if((uintptr_t)p>=(uintptr_t)(&defsyms)&&(uintptr_t)p<(uintptr_t)(&defsyms)+(sizeof defsyms)){logfmt("defsyms+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&defsyms)));return;}
if((uintptr_t)p>=(uintptr_t)(&svm)&&(uintptr_t)p<(uintptr_t)(&svm)+(sizeof svm)){logfmt("svm+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&svm)));return;}
if((uintptr_t)p>=(uintptr_t)(scratch)&&(uintptr_t)p<(uintptr_t)(scratch)+(sizeof scratch)){logfmt("scratch+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(scratch)));return;}
if((uintptr_t)p>=(uintptr_t)(monsters)&&(uintptr_t)p<(uintptr_t)(monsters)+(sizeof monsters)){logfmt("monsters+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(monsters)));return;}
if((uintptr_t)p>=(uintptr_t)(objlist)&&(uintptr_t)p<(uintptr_t)(objlist)+(sizeof objlist)){logfmt("objlist+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(objlist)));return;}
if((uintptr_t)p>=(uintptr_t)(traps)&&(uintptr_t)p<(uintptr_t)(traps)+(sizeof traps)){logfmt("traps+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(traps)));return;}
if((uintptr_t)p>=(uintptr_t)(engravings)&&(uintptr_t)p<(uintptr_t)(engravings)+(sizeof engravings)){logfmt("engravings+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(engravings)));return;}
if((uintptr_t)p>=(uintptr_t)(regions)&&(uintptr_t)p<(uintptr_t)(regions)+(sizeof regions)){logfmt("regions+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(regions)));return;}
if((uintptr_t)p>=(uintptr_t)(stairs)&&(uintptr_t)p<(uintptr_t)(stairs)+(sizeof stairs)){logfmt("stairs+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(stairs)));return;}
if((uintptr_t)p>=(uintptr_t)(vision)&&(uintptr_t)p<(uintptr_t)(vision)+(sizeof vision)){logfmt("vision+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(vision)));return;}
if((uintptr_t)p>=(uintptr_t)(visionrows)&&(uintptr_t)p<(uintptr_t)(visionrows)+(sizeof visionrows)){logfmt("visionrows+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(visionrows)));return;}
if((uintptr_t)p>=(uintptr_t)(detailtext)&&(uintptr_t)p<(uintptr_t)(detailtext)+(sizeof detailtext)){logfmt("detailtext+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(detailtext)));return;}
if((uintptr_t)p>=(uintptr_t)(glyph_events)&&(uintptr_t)p<(uintptr_t)(glyph_events)+(sizeof glyph_events)){logfmt("glyph_events+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(glyph_events)));return;}
if((uintptr_t)p>=(uintptr_t)(&nul_glyphinfo)&&(uintptr_t)p<(uintptr_t)(&nul_glyphinfo)+(sizeof nul_glyphinfo)){logfmt("nul_glyphinfo+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(&nul_glyphinfo)));return;}
if((uintptr_t)p>=(uintptr_t)(glyphmap)&&(uintptr_t)p<(uintptr_t)(glyphmap)+(sizeof glyphmap)){logfmt("glyphmap+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(glyphmap)));return;}
if((uintptr_t)p>=(uintptr_t)(zapcolors)&&(uintptr_t)p<(uintptr_t)(zapcolors)+(sizeof zapcolors)){logfmt("zapcolors+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(zapcolors)));return;}
if((uintptr_t)p>=(uintptr_t)(altarcolors)&&(uintptr_t)p<(uintptr_t)(altarcolors)+(sizeof altarcolors)){logfmt("altarcolors+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(altarcolors)));return;}
if((uintptr_t)p>=(uintptr_t)(explodecolors)&&(uintptr_t)p<(uintptr_t)(explodecolors)+(sizeof explodecolors)){logfmt("explodecolors+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(explodecolors)));return;}
if((uintptr_t)p>=(uintptr_t)(wallcolors)&&(uintptr_t)p<(uintptr_t)(wallcolors)+(sizeof wallcolors)){logfmt("wallcolors+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(wallcolors)));return;}
if((uintptr_t)p>=(uintptr_t)(seenv_matrix)&&(uintptr_t)p<(uintptr_t)(seenv_matrix)+(sizeof seenv_matrix)){logfmt("seenv_matrix+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)(seenv_matrix)));return;}

for(int i=0;i<nalloc;i++)if(alloclive[i]&&(uintptr_t)p>=(uintptr_t)allocations[i]&&(uintptr_t)p<(uintptr_t)allocations[i]+allocsizes[i]){logfmt("A%d+%llu",i,(unsigned long long)((uintptr_t)p-(uintptr_t)allocations[i]));return;}logfmt("UNKNOWN:%llu",(unsigned long long)(uintptr_t)p);}
void*__real_malloc(size_t);void __real_free(void*);
void*__wrap_malloc(size_t n){if(nalloc==4096)abort();void*p=__real_malloc(n);if(p)memset(p,0,n);allocations[nalloc]=p;allocsizes[nalloc]=n;alloclive[nalloc++]=1;return p;}
void __wrap_free(void*p){logfmt("free(");ptrlog(p);logfmt(")\n");for(int i=0;i<nalloc;i++)if(alloclive[i]&&allocations[i]==p){alloclive[i]=0;break;}__real_free(p);}
static void win_delay(void){logfmt("window.delay\n");}static void win_clear(winid w){logfmt("window.clear(%d)\n",w);}static void win_display(winid w,boolean b){logfmt("window.display(%d,%d)\n",w,b);}static void win_curs(winid w,int x,int y){logfmt("window.curs(%d,%d,%d)\n",w,x,y);}
static void win_print(winid w,coordxy x,coordxy y,const glyph_info*fg,const glyph_info*bg){if(nglyph_events==16384)abort();logfmt("window.print(%d,%d,%d)\n",w,x,y);memcpy(glyph_events[nglyph_events],fg,sizeof*fg);memcpy(glyph_events[nglyph_events]+sizeof*fg,bg,sizeof*bg);nglyph_events++;if(options[14]){options[14]=0;glyph_info saved=*bg;if(fg!=&gg.gbuf[y][x].glyphinfo)abort();logfmt("window.native-reentry-borrowed\n");(show_glyph)(x,y,GLYPH_MON_MALE_OFF+1);(flush_screen)(0);if(memcmp(&saved,bg,sizeof saved))abort();if(nglyph_events==16384)abort();memcpy(glyph_events[nglyph_events],fg,sizeof*fg);memcpy(glyph_events[nglyph_events]+sizeof*fg,bg,sizeof*bg);nglyph_events++;}}

void display_observe_startup(const void*p,size_t n){if(startupused+n>sizeof startup)abort();memcpy(startup+startupused,p,n);startupused+=n;startupcalls++;}
void display_mutate_caller_coord(void){if(callercoord){callercoord->x=-123;callercoord->y=234;}}

#ifdef HYBRID_DISPLAY
extern void teleport_display_mimic_light_blocking(struct monst*);
#define EXPECTED_MIMIC_CALLBACK teleport_display_mimic_light_blocking
#else
static void mimic_light_blocking(struct monst*);
#define EXPECTED_MIMIC_CALLBACK mimic_light_blocking
#endif
int (dist2)(coordxy a0,coordxy a1,coordxy a2,coordxy a3){logfmt("dist2(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(",");logfmt("%lld",(long long)a3);logfmt(")\n");return(a0-a2)*(a0-a2)+(a1-a3)*(a1-a3);}
boolean (is_pool)(coordxy a0,coordxy a1){logfmt("is_pool(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return levl[a0][a1].typ==POOL||levl[a0][a1].typ==MOAT;}
boolean (worm_known)(struct monst * a0){logfmt("worm_known(");ptrlog(a0);logfmt(")\n");return options[0];}
boolean (In_mines)(d_level * a0){logfmt("In_mines(");ptrlog(a0);logfmt(")\n");return options[1];}
boolean (In_hell)(d_level * a0){logfmt("In_hell(");ptrlog(a0);logfmt(")\n");return options[2];}
boolean (on_level)(d_level * a0,d_level * a1){logfmt("on_level(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");return a0->dnum==a1->dnum&&a0->dlevel==a1->dlevel;}
void (update_lastseentyp)(coordxy a0,coordxy a1){logfmt("update_lastseentyp(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");svl.lastseentyp[a0][a1]=levl[a0][a1].typ;}
int (rn2_on_display_rng)(int a0){if(a0<=0)abort();seed=seed*1664525U+1013904223U;int v=seed%(unsigned)a0;draws++;logfmt("displayRNG(%d)=%d\n",a0,v);return v;}
void (observe_object)(struct obj * a0){logfmt("observe_object(");ptrlog(a0);logfmt(")\n");a0->dknown=1;}
int (isok)(coordxy a0,coordxy a1){logfmt("isok(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return a0>=1&&a0<COLNO&&a1>=0&&a1<ROWNO;}
struct trap * (t_at)(coordxy a0,coordxy a1){logfmt("t_at(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return options[3]?&traps[0]:0;}
struct engr * (engr_at)(coordxy a0,coordxy a1){logfmt("engr_at(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return options[4]?&engravings[0]:0;}
NhRegion * (visible_region_at)(coordxy a0,coordxy a1){logfmt("visible_region_at(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return options[5]?&regions[0]:0;}
void (show_region)(NhRegion * a0,coordxy a1,coordxy a2){logfmt("show_region(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(")\n");}
int (cmap_to_type)(int a0){logfmt("cmap_to_type(");logfmt("%lld",(long long)a0);logfmt(")\n");return options[6]?options[6]:ROOM;}
boolean (is_pool_or_lava)(coordxy a0,coordxy a1){logfmt("is_pool_or_lava(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return levl[a0][a1].typ==POOL||levl[a0][a1].typ==MOAT||levl[a0][a1].typ==LAVAPOOL;}
boolean (is_ice)(coordxy a0,coordxy a1){logfmt("is_ice(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return levl[a0][a1].typ==ICE;}
boolean (can_reach_floor)(boolean a0){logfmt("can_reach_floor(");logfmt("%lld",(long long)a0);logfmt(")\n");return !options[7];}
struct obj * (sobj_at)(int a0,coordxy a1,coordxy a2){logfmt("sobj_at(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(")\n");return options[8]?&objlist[0]:0;}
boolean (engr_can_be_felt)(struct engr * a0){logfmt("engr_can_be_felt(");ptrlog(a0);logfmt(")\n");return options[9];}
int (sgn)(int a0){logfmt("sgn(");logfmt("%lld",(long long)a0);logfmt(")\n");return(a0>0)-(a0<0);}
long * (alloc)(unsigned int a0){logfmt("alloc(");logfmt("%lld",(long long)a0);logfmt(")\n");return(long*)__wrap_malloc(a0);}
void (bot)(void){logfmt("bot(");logfmt(")\n");}
void (see_wsegs)(struct monst * a0){logfmt("see_wsegs(");ptrlog(a0);logfmt(")\n");}
void (Sting_effects)(int a0){logfmt("Sting_effects(");logfmt("%lld",(long long)a0);logfmt(")\n");}
void (block_point)(int a0,int a1){logfmt("block_point(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");}
void (unblock_point)(int a0,int a1){logfmt("unblock_point(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");}
void (iter_mons)(void (*a0)(struct monst *)){logfmt("iter_mons(");logfmt("native-source-callback");logfmt(")\n");if(a0!=EXPECTED_MIMIC_CALLBACK)abort();for(int i=0;i<options[10];i++)a0(&monsters[i]);}
void (update_inventory)(void){logfmt("update_inventory(");logfmt(")\n");}
void (vision_recalc)(int a0){logfmt("vision_recalc(");logfmt("%lld",(long long)a0);logfmt(")\n");}
int (glyph_to_cmap)(int a0){logfmt("glyph_to_cmap(");logfmt("%lld",(long long)a0);logfmt(")\n");return a0-GLYPH_CMAP_OFF;}
int (do_screen_description)(coord a0,boolean a1,int a2,char * a3,const char ** a4,struct permonst ** a5){logfmt("do_screen_description(");logfmt("coord:%d,%d",a0.x,a0.y);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(",");logfmt("char * output:present");logfmt(",");logfmt("const char ** output:present");logfmt(",");logfmt("struct permonst ** output:%s",a5?"present":"null");logfmt(")\n");logfmt("coord-before:%d,%d\n",a0.x,a0.y);display_mutate_caller_coord();logfmt("coord-after:%d,%d\n",a0.x,a0.y);strcpy(a3,"fixture description");*a4=detailtext;if(a5)*a5=&mons[0];return 1;}
void (timebot)(void){logfmt("timebot(");logfmt(")\n");}
stairway * (stairway_at)(coordxy a0,coordxy a1){logfmt("stairway_at(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return options[11]?&stairs[0]:0;}
boolean (known_branch_stairs)(stairway * a0){logfmt("known_branch_stairs(");ptrlog(a0);logfmt(")\n");return options[12];}
boolean (mapxy_valid)(coordxy a0,coordxy a1){logfmt("mapxy_valid(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return a0>=1&&a0<COLNO&&a1>=0&&a1<ROWNO;}
int (has_color)(int a0){logfmt("has_color(");logfmt("%lld",(long long)a0);logfmt(")\n");return options[13]?0:1;}
void impossible(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[4096];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("impossible:%s\n",b);}
void panic(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[4096];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("panic:%s\n",b);longjmp(panicframe,1);}
void pline_xy(coordxy x,coordxy y,const char*fmt,...){va_list ap;va_start(ap,fmt);char b[4096];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("pline_xy:%d,%d:%s\n",x,y,b);}
#ifdef HYBRID_DISPLAY
#define TMP_AT_MAX_GLYPHS (COLNO*2)
struct tmp_glyph {
    coord saved[TMP_AT_MAX_GLYPHS]; /* previously updated positions */
    int sidx;                       /* index of next unused slot in saved[] */
    int style; /* either DISP_BEAM or DISP_FLASH or DISP_ALWAYS */
    int glyph; /* glyph to use when printing */
    struct tmp_glyph *prev;
};
extern int tp_sensemon(struct monst * a0);
extern int sensemon(struct monst * a0);
extern int mon_warning(struct monst * a0);
extern int mon_visible(struct monst * a0);
extern int see_with_infrared(struct monst * a0);
extern int canseemon(struct monst * a0);
extern int knowninvisible(struct monst * a0);
extern int is_safemon(struct monst * a0);
extern void magic_map_background(coordxy a0,coordxy a1,int a2);
extern void map_background(coordxy a0,coordxy a1,int a2);
extern void map_trap(struct trap * a0,int a1);
extern void map_engraving(struct engr * a0,int a1);
extern void map_object(struct obj * a0,int a1);
extern void map_invisible(coordxy a0,coordxy a1);
extern boolean unmap_invisible(coordxy a0,coordxy a1);
extern void unmap_object(coordxy a0,coordxy a1);
extern void map_location(coordxy a0,coordxy a1,int a2);
extern void teleport_display_show_mon_or_warn(coordxy a0,coordxy a1,int a2);
extern void teleport_display_display_monster(coordxy a0,coordxy a1,struct monst * a2,int a3,boolean a4);
extern void teleport_display_display_warning(struct monst * a0);
extern int warning_of(struct monst * a0);
extern boolean teleport_display_mon_overrides_region(struct monst * a0,coordxy a1,coordxy a2);
extern boolean suppress_map_output(void);
extern void feel_newsym(coordxy a0,coordxy a1);
extern void feel_location(coordxy a0,coordxy a1);
extern void newsym(coordxy a0,coordxy a1);
extern void shieldeff(coordxy a0,coordxy a1);
extern int teleport_display_tether_glyph(coordxy a0,coordxy a1);
extern void tmp_at(coordxy a0,coordxy a1);
extern void flash_glyph_at(coordxy a0,coordxy a1,int a2,int a3);
extern void swallowed(int a0);
extern void under_water(int a0);
extern void under_ground(int a0);
extern void see_monsters(void);
extern void teleport_display_mimic_light_blocking(struct monst * a0);
extern void set_mimic_blocking(void);
extern void see_objects(void);
extern void see_nearby_objects(void);
extern void see_traps(void);
extern void curs_on_u(void);
extern int doredraw(void);
extern void docrt(void);
extern void docrt_flags(int a0);
extern void redraw_map(boolean a0);
extern void reglyph_darkroom(void);
extern void newsym_force(coordxy a0,coordxy a1);
extern void show_glyph(coordxy a0,coordxy a1,int a2);
extern void clear_glyph_buffer(void);
extern void row_refresh(coordxy a0,coordxy a1,coordxy a2);
extern void cls(void);
extern void flush_screen(int a0);
extern int back_to_glyph(coordxy a0,coordxy a1);
extern int teleport_display_swallow_to_glyph(int a0,int a1);
extern int zapdir_to_glyph(int a0,int a1,int a2);
extern int glyph_at(coordxy a0,coordxy a1);
extern void teleport_display_get_bkglyph_and_framecolor(coordxy a0,coordxy a1,int * a2,uint32 * a3);
extern void map_glyphinfo(coordxy a0,coordxy a1,int a2,unsigned int a3,glyph_info * a4);
extern int teleport_display_cmap_to_roguecolor(int a0);
extern void reset_glyphmap(enum glyphmap_change_triggers a0);
extern int teleport_display_check_pos(coordxy a0,coordxy a1,int a2);
extern int teleport_display_set_twall(coordxy a0,coordxy a1,coordxy a2,coordxy a3,coordxy a4,coordxy a5,coordxy a6,coordxy a7);
extern int teleport_display_set_wall(coordxy a0,coordxy a1,int a2);
extern int teleport_display_set_corn(coordxy a0,coordxy a1,coordxy a2,coordxy a3,coordxy a4,coordxy a5,coordxy a6,coordxy a7);
extern int teleport_display_set_crosswall(coordxy a0,coordxy a1);
extern void xy_set_wall_state(coordxy a0,coordxy a1);
extern void set_wall_state(void);
extern void teleport_display_set_seenv(struct rm * a0,coordxy a1,coordxy a2,coordxy a3,coordxy a4);
extern void unset_seenv(struct rm * a0,coordxy a1,coordxy a2,coordxy a3,coordxy a4);
extern void teleport_display_t_warn(struct rm * a0);
extern int teleport_display_wall_angle(struct rm * a0);
extern int fn_cmap_to_glyph(int a0);
#else
#define teleport_display_show_mon_or_warn show_mon_or_warn
#define teleport_display_display_monster display_monster
#define teleport_display_display_warning display_warning
#define teleport_display_mon_overrides_region mon_overrides_region
#define teleport_display_tether_glyph tether_glyph
#define teleport_display_mimic_light_blocking mimic_light_blocking
#define teleport_display_swallow_to_glyph swallow_to_glyph
#define teleport_display_get_bkglyph_and_framecolor get_bkglyph_and_framecolor
#define teleport_display_cmap_to_roguecolor cmap_to_roguecolor
#define teleport_display_check_pos check_pos
#define teleport_display_set_twall set_twall
#define teleport_display_set_wall set_wall
#define teleport_display_set_corn set_corn
#define teleport_display_set_crosswall set_crosswall
#define teleport_display_set_seenv set_seenv
#define teleport_display_t_warn t_warn
#define teleport_display_wall_angle wall_angle
#include "/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/wasm64-build/tree/src/display.c"
#undef teleport_display_mimic_light_blocking
void teleport_display_mimic_light_blocking(struct monst*m){mimic_light_blocking(m);}
#endif
__attribute__((noinline))static void probe_poison(void){volatile unsigned char p[65536];for(int i=0;i<sizeof p;i++)p[i]=0;}
int64_t probe_action(int i,int64_t a0,int64_t a1,int64_t a2,int64_t a3,int64_t a4,int64_t a5,int64_t a6,int64_t a7,int64_t a8,int64_t a9){probe_poison();errorcode=0;int jump=setjmp(panicframe);if(jump){errorcode=jump;return -999;}switch(i){
case 0:return(int64_t)(tp_sensemon)((struct monst *)a0);
case 1:return(int64_t)(sensemon)((struct monst *)a0);
case 2:return(int64_t)(mon_warning)((struct monst *)a0);
case 3:return(int64_t)(mon_visible)((struct monst *)a0);
case 4:return(int64_t)(see_with_infrared)((struct monst *)a0);
case 5:return(int64_t)(canseemon)((struct monst *)a0);
case 6:return(int64_t)(knowninvisible)((struct monst *)a0);
case 7:return(int64_t)(is_safemon)((struct monst *)a0);
case 8:(magic_map_background)((coordxy)a0,(coordxy)a1,(int)a2);return 0;
case 9:(map_background)((coordxy)a0,(coordxy)a1,(int)a2);return 0;
case 10:(map_trap)((struct trap *)a0,(int)a1);return 0;
case 11:(map_engraving)((struct engr *)a0,(int)a1);return 0;
case 12:(map_object)((struct obj *)a0,(int)a1);return 0;
case 13:(map_invisible)((coordxy)a0,(coordxy)a1);return 0;
case 14:return(int64_t)(unmap_invisible)((coordxy)a0,(coordxy)a1);
case 15:(unmap_object)((coordxy)a0,(coordxy)a1);return 0;
case 16:(map_location)((coordxy)a0,(coordxy)a1,(int)a2);return 0;
case 17:(teleport_display_show_mon_or_warn)((coordxy)a0,(coordxy)a1,(int)a2);return 0;
case 18:(teleport_display_display_monster)((coordxy)a0,(coordxy)a1,(struct monst *)a2,(int)a3,(boolean)a4);return 0;
case 19:(teleport_display_display_warning)((struct monst *)a0);return 0;
case 20:return(int64_t)(warning_of)((struct monst *)a0);
case 21:return(int64_t)(teleport_display_mon_overrides_region)((struct monst *)a0,(coordxy)a1,(coordxy)a2);
case 22:return(int64_t)(suppress_map_output)();
case 23:(feel_newsym)((coordxy)a0,(coordxy)a1);return 0;
case 24:(feel_location)((coordxy)a0,(coordxy)a1);return 0;
case 25:(newsym)((coordxy)a0,(coordxy)a1);return 0;
case 26:(shieldeff)((coordxy)a0,(coordxy)a1);return 0;
case 27:return(int64_t)(teleport_display_tether_glyph)((coordxy)a0,(coordxy)a1);
case 28:(tmp_at)((coordxy)a0,(coordxy)a1);return 0;
case 29:(flash_glyph_at)((coordxy)a0,(coordxy)a1,(int)a2,(int)a3);return 0;
case 30:(swallowed)((int)a0);return 0;
case 31:(under_water)((int)a0);return 0;
case 32:(under_ground)((int)a0);return 0;
case 33:(see_monsters)();return 0;
case 34:(teleport_display_mimic_light_blocking)((struct monst *)a0);return 0;
case 35:(set_mimic_blocking)();return 0;
case 36:(see_objects)();return 0;
case 37:(see_nearby_objects)();return 0;
case 38:(see_traps)();return 0;
case 39:(curs_on_u)();return 0;
case 40:return(int64_t)(doredraw)();
case 41:(docrt)();return 0;
case 42:(docrt_flags)((int)a0);return 0;
case 43:(redraw_map)((boolean)a0);return 0;
case 44:(reglyph_darkroom)();return 0;
case 45:(newsym_force)((coordxy)a0,(coordxy)a1);return 0;
case 46:(show_glyph)((coordxy)a0,(coordxy)a1,(int)a2);return 0;
case 47:(clear_glyph_buffer)();return 0;
case 48:(row_refresh)((coordxy)a0,(coordxy)a1,(coordxy)a2);return 0;
case 49:(cls)();return 0;
case 50:(flush_screen)((int)a0);return 0;
case 51:return(int64_t)(back_to_glyph)((coordxy)a0,(coordxy)a1);
case 52:return(int64_t)(teleport_display_swallow_to_glyph)((int)a0,(int)a1);
case 53:return(int64_t)(zapdir_to_glyph)((int)a0,(int)a1,(int)a2);
case 54:return(int64_t)(glyph_at)((coordxy)a0,(coordxy)a1);
case 55:(teleport_display_get_bkglyph_and_framecolor)((coordxy)a0,(coordxy)a1,(int *)a2,(uint32 *)a3);return 0;
case 56:(map_glyphinfo)((coordxy)a0,(coordxy)a1,(int)a2,(unsigned int)a3,(glyph_info *)a4);return 0;
case 57:return(int64_t)(teleport_display_cmap_to_roguecolor)((int)a0);
case 58:(reset_glyphmap)((enum glyphmap_change_triggers)a0);return 0;
case 59:return(int64_t)(teleport_display_check_pos)((coordxy)a0,(coordxy)a1,(int)a2);
case 60:return(int64_t)(teleport_display_set_twall)((coordxy)a0,(coordxy)a1,(coordxy)a2,(coordxy)a3,(coordxy)a4,(coordxy)a5,(coordxy)a6,(coordxy)a7);
case 61:return(int64_t)(teleport_display_set_wall)((coordxy)a0,(coordxy)a1,(int)a2);
case 62:return(int64_t)(teleport_display_set_corn)((coordxy)a0,(coordxy)a1,(coordxy)a2,(coordxy)a3,(coordxy)a4,(coordxy)a5,(coordxy)a6,(coordxy)a7);
case 63:return(int64_t)(teleport_display_set_crosswall)((coordxy)a0,(coordxy)a1);
case 64:(xy_set_wall_state)((coordxy)a0,(coordxy)a1);return 0;
case 65:(set_wall_state)();return 0;
case 66:(teleport_display_set_seenv)((struct rm *)a0,(coordxy)a1,(coordxy)a2,(coordxy)a3,(coordxy)a4);return 0;
case 67:(unset_seenv)((struct rm *)a0,(coordxy)a1,(coordxy)a2,(coordxy)a3,(coordxy)a4);return 0;
case 68:(teleport_display_t_warn)((struct rm *)a0);return 0;
case 69:return(int64_t)(teleport_display_wall_angle)((struct rm *)a0);
case 70:return(int64_t)(fn_cmap_to_glyph)((int)a0);
default:abort();}}

const char*probe_trace(void){return tracebuf;}void probe_clear(void){traceused=0;tracebuf[0]=0;}int probe_draws(void){return draws;}int probe_error(void){return errorcode;}int probe_errno(void){return errno;}
void probe_seed(uint32_t n){seed=n;draws=0;}void probe_option(int i,int v){options[i]=v;}
void*probe_pointer(int i){switch(i){case 0:return scratch;case 1:return monsters;case 2:return objlist;case 3:return traps;case 4:return engravings;case 5:return regions;case 6:return stairs;case 7:return vision;case 8:return visionrows;case 9:return(void*)detailtext;case 10:return glyph_events;default:abort();}}
void*probe_grid(void){return levl;}void probe_map(int x,int y,int typ,int seen){memset(&levl[x][y],0,sizeof levl[x][y]);levl[x][y].typ=typ;levl[x][y].seenv=seen;svl.lastseentyp[x][y]=typ;}
int probe_count(void){return nalloc;}void*probe_alloc_pointer(int i){return allocations[i];}size_t probe_alloc_size(int i){return allocsizes[i];}int probe_alloc_live(int i){return alloclive[i];}void*probe_growth(void){return __real_malloc(50000000);}
const void*probe_startup(void){return startup;}size_t probe_startup_size(void){return startupused;}int probe_startup_calls(void){return startupcalls;}
void probe_coord(coord*p){callercoord=p;}int probe_coord_call(coord*p){return do_screen_description(*p,0,0,(char*)scratch+1024,(const char**)(scratch+512),0);}
void probe_wallcolor(int i,int v){wallcolors[i]=v;}
void probe_reset(void){for(int i=0;i<nalloc;i++)if(alloclive[i])__real_free(allocations[i]);nalloc=0;memset(alloclive,0,sizeof alloclive);memset(options,0,sizeof options);

memset((void*)&u,0,sizeof u);
memset((void*)&svc,0,sizeof svc);
memset((void*)&gv,0,sizeof gv);
memset((void*)&flags,0,sizeof flags);
memset((void*)&svl,0,sizeof svl);
memset((void*)&svd,0,sizeof svd);
memset((void*)&iflags,0,sizeof iflags);
memset((void*)&go,0,sizeof go);
memset((void*)&gi,0,sizeof gi);
memset((void*)&program_state,0,sizeof program_state);
memset((void*)&uball,0,sizeof uball);
memset((void*)&uchain,0,sizeof uchain);
memset((void*)&gy,0,sizeof gy);
memset((void*)&gu,0,sizeof gu);
memset((void*)&windowprocs,0,sizeof windowprocs);
memset((void*)&gd,0,sizeof gd);
memset((void*)&gw,0,sizeof gw);
memset((void*)&gf,0,sizeof gf);
memset((void*)&gg,0,sizeof gg);
memset((void*)&disp,0,sizeof disp);
memset((void*)&WIN_MAP,0,sizeof WIN_MAP);
memset((void*)&gs,0,sizeof gs);
memset((void*)&a11y,0,sizeof a11y);
memset((void*)&WIN_MESSAGE,0,sizeof WIN_MESSAGE);
memset((void*)&gc,0,sizeof gc);
memset((void*)&sysopt,0,sizeof sysopt);
memset((void*)&mons,0,sizeof mons);
memset((void*)&objects,0,sizeof objects);
memset((void*)&svm,0,sizeof svm);

memset(scratch,0,sizeof scratch);memset(glyph_events,0,sizeof glyph_events);nglyph_events=0;memset(monsters,0,sizeof monsters);memset(objlist,0,sizeof objlist);memset(traps,0,sizeof traps);memset(engravings,0,sizeof engravings);memset(regions,0,sizeof regions);memset(stairs,0,sizeof stairs);memset(vision,0,sizeof vision);
for(int y=0;y<ROWNO;y++)visionrows[y]=vision[y];gv.viz_array=visionrows;
u.ux=40;u.uy=10;u.uz.dlevel=3;u.ulevel=5;u.uhp=u.uhpmax=50;u.umonnum=0;gy.youmonst.data=&mons[0];
for(int i=0;i<8;i++){monsters[i].data=&mons[i];monsters[i].mx=35+i;monsters[i].my=10;monsters[i].mcansee=1;monsters[i].mhp=10;objlist[i].otyp=1;objlist[i].oclass=WEAPON_CLASS;objlist[i].ox=40;objlist[i].oy=10;}
windowprocs.win_delay_output=win_delay;windowprocs.win_clear_nhwindow=win_clear;windowprocs.win_display_nhwindow=win_display;windowprocs.win_curs=win_curs;windowprocs.win_print_glyph=win_print;
for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++){levl[x][y].typ=ROOM;svl.lastseentyp[x][y]=ROOM;}
traps[0].tx=40;traps[0].ty=10;traps[0].ttyp=1;engravings[0].engr_x=40;engravings[0].engr_y=10;WIN_MAP=1;WIN_MESSAGE=2;seed=1;draws=errorcode=0;callercoord=0;errno=0;probe_clear();}
size_t probe_global_size(int i){switch(i){

case 0:return sizeof u;
case 1:return sizeof svc;
case 2:return sizeof gv;
case 3:return sizeof flags;
case 4:return sizeof svl;
case 5:return sizeof svd;
case 6:return sizeof iflags;
case 7:return sizeof go;
case 8:return sizeof cg;
case 9:return sizeof gi;
case 10:return sizeof program_state;
case 11:return sizeof uball;
case 12:return sizeof uchain;
case 13:return sizeof gy;
case 14:return sizeof gu;
case 15:return sizeof shield_static;
case 16:return sizeof windowprocs;
case 17:return sizeof gd;
case 18:return sizeof gw;
case 19:return sizeof gf;
case 20:return sizeof gg;
case 21:return sizeof disp;
case 22:return sizeof WIN_MAP;
case 23:return sizeof gs;
case 24:return sizeof a11y;
case 25:return sizeof WIN_MESSAGE;
case 26:return sizeof gc;
case 27:return sizeof sysopt;
case 28:return sizeof mons;
case 29:return sizeof objects;
case 30:return sizeof def_warnsyms;
case 31:return sizeof defsyms;
case 32:return sizeof svm;
default:abort();}}
size_t probe_region_size(int i){switch(i){
case 0:return sizeof scratch;
case 1:return sizeof monsters;
case 2:return sizeof objlist;
case 3:return sizeof traps;
case 4:return sizeof engravings;
case 5:return sizeof regions;
case 6:return sizeof stairs;
case 7:return sizeof vision;
case 8:return sizeof visionrows;
case 9:return sizeof detailtext;
case 10:return sizeof glyph_events;
default:abort();}}
int probe_glyph_events(void){return nglyph_events;}
void*probe_alloc(int size){return __wrap_malloc(size);}
size_t probe_public_size(int i){switch(i){
case 9:return sizeof nul_glyphinfo;
case 10:return sizeof glyphmap;
case 15:return sizeof zapcolors;
case 16:return sizeof altarcolors;
case 17:return sizeof explodecolors;
case 18:return sizeof wallcolors;
case 19:return sizeof seenv_matrix;
default:abort();}}
extern void*teleport_display_storage(int);
void*probe_private(int i){switch(i){
case 0:
#ifdef HYBRID_DISPLAY
return teleport_display_storage(i);
#else
return(void*)&tgfirst;
#endif
case 8:
#ifdef HYBRID_DISPLAY
return teleport_display_storage(i);
#else
return(void*)&no_ginfo;
#endif
case 11:
#ifdef HYBRID_DISPLAY
return teleport_display_storage(i);
#else
return(void*)&nul_gbuf;
#endif
case 20:
#ifdef HYBRID_DISPLAY
return teleport_display_storage(i);
#else
return(void*)&wall_matrix;
#endif
case 21:
#ifdef HYBRID_DISPLAY
return teleport_display_storage(i);
#else
return(void*)&cross_matrix;
#endif
default:abort();}}
size_t probe_private_size(int i){switch(i){
case 0:return sizeof(struct tmp_glyph);
case 8:return sizeof(glyph_info);
case 11:return sizeof(gbuf_entry);
case 20:return sizeof(const int[4][5]);
case 21:return sizeof(const int[4][6]);
default:abort();}}
