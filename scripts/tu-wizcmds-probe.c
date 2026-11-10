/* Controlled WIZCMDS fixture: original configured C and JS share dependencies.
 * This is an EmC first-pass oracle; native macOS parity remains a separate gate.
 */
#include "hack.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
#include "tu-wizcmds-layout.h"
extern glyph_map glyphmap[MAX_GLYPH];
extern const char *const known_handling[];
extern const char unavailcmd[];
extern const char *levltyp[MAX_TYPE+2];
__typeof__(flags) flags;
__typeof__(iflags) iflags;
__typeof__(svm) svm;
__typeof__(u) u;
__typeof__(svl) svl;
__typeof__(gm) gm;
__typeof__(a11y) a11y;
__typeof__(gf) gf;
__typeof__(head_engr) head_engr;
__typeof__(gu) gu;
__typeof__(svk) svk;
__typeof__(mons) mons;
__typeof__(svc) svc;
__typeof__(windowprocs) windowprocs;
__typeof__(gv) gv;
__typeof__(svd) svd;
__typeof__(gy) gy;
__typeof__(disp) disp;
__typeof__(gi) gi;
__typeof__(objects) objects;
__typeof__(WIN_MESSAGE) WIN_MESSAGE;
__typeof__(program_state) program_state;
__typeof__(gb) gb;
__typeof__(svn) svn;
__typeof__(obj_descr) obj_descr;
__typeof__(gs) gs;
__typeof__(gc) gc;
__typeof__(glyphmap) glyphmap;
const char unavailcmd[]="Unavailable %s";
const char ynqchars[]="ynq",ynchars[]="yn";
const struct Gender genders[4]={{.his="his"},{.his="her"},{.his="its"},{.his="their"}};
const struct c_common_strings c_common_strings={.c_Never_mind="Never mind."};
const struct const_globals cg={0};
const struct symdef defsyms[MAXPCHARS+1]={0};
const glyph_info nul_glyphinfo={0};
const char *const known_handling[]={"unknown","IBM","DEC","MAC","CURS"};
const char *levltyp[MAX_TYPE+2];
static struct monst mpool[8];static struct obj opool[16];static struct mextra mextras[8];static struct oextra oextras[16];static struct trap traps[4];static struct engr engrs[4];static struct damage damages[4];static struct kinfo killers[4];static struct cemetery bones[4];static struct unicode_representation unicodes[4];static s_level special;static d_level levelarg;static long counters[8];static menu_item selections[8];static anything any;
static char input[2048],labels[32][80],tracebuf[4194304],stringbuf[256];static int tracepos,options[256],seed,readcount,reentered;static void*growth;
static seenV vis[ROWNO][COLNO],*visrows[ROWNO];
static uint64_t canonical(uint64_t);
static void append(const char*fmt,...){if(tracepos>sizeof tracebuf-4096)abort();va_list ap;va_start(ap,fmt);tracepos+=vsnprintf(tracebuf+tracepos,sizeof tracebuf-tracepos,fmt,ap);va_end(ap);}
static void grow(void){if(options[200]&&!growth){growth=malloc(emscripten_get_heap_size()+16*1024*1024);if(!growth)abort();append("growth;");}}
static void message(const char*kind,const char*fmt,va_list ap){char b[4096];vsnprintf(b,sizeof b,fmt,ap);append("%s:%s;",kind,b);grow();}
void (makewish)(void){append("dependency:makewish;");}
void (encumber_msg)(void){append("dependency:encumber_msg;");}
void (pline)(const char * a0,...){va_list ap;va_start(ap,a0);message("pline",a0,ap);va_end(ap);}
const char * (ecname_from_fn)(int (*a0)(void)){snprintf(stringbuf,sizeof stringbuf,"command%d",a0==wiz_wish?1:a0==wiz_identify?2:a0==wiz_makemap?3:a0==wiz_map?4:a0==wiz_genesis?5:a0==wiz_where?6:a0==wiz_detect?7:a0==wiz_load_lua?8:a0==wiz_load_splua?9:a0==wiz_level_tele?10:a0==wiz_intrinsic?11:a0==wiz_custom?12:99);return stringbuf;}
char (cmd_from_func)(int (*a0)(void)){append("cmd_from_func:%s;",ecname_from_fn(a0));return options[201];}
char (display_inventory)(const char * a0,boolean a1){append("dependency:display_inventory:%s:%d;",a0?a0:"(null)",(int)a1);return options[21];}
boolean (on_level)(d_level * a0,d_level * a1){return a0->dnum==a1->dnum&&a0->dlevel==a1->dlevel;}
void (setpaid)(struct monst * a0){append("dependency:setpaid:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (mongone)(struct monst * a0){append("mongone:%llu;",(unsigned long long)canonical((uintptr_t)a0));a0->mhp=0;}
void (keepdogs)(boolean a0){append("dependency:keepdogs:%d;",(int)a0);}
void (dmonsfree)(void){append("dmonsfree;");fmon=0;}
void (impossible)(const char * a0,...){va_list ap;va_start(ap,a0);message("impossible",a0,ap);va_end(ap);}
boolean (In_W_tower)(coordxy a0,coordxy a1,d_level * a2){append("dependency:In_W_tower:%d:%d:%llu;",(int)a0,(int)a1,(unsigned long long)canonical((uintptr_t)a2));return options[0];}
void (makemap_prepost)(boolean a0,boolean a1){append("dependency:makemap_prepost:%d:%d;",(int)a0,(int)a1);}
void (mklev)(void){append("dependency:mklev;");}
void (map_trap)(struct trap * a0,int a1){append("dependency:map_trap:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);}
void (map_engraving)(struct engr * a0,int a1){append("dependency:map_engraving:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);}
void (do_mapping)(void){append("dependency:do_mapping;");}
boolean (create_particular)(void){append("dependency:create_particular;");return options[19];}
schar (print_dungeon)(boolean a0,schar * a1,xint16 * a2){append("dependency:print_dungeon:%d:%llu:%llu;",(int)a0,(unsigned long long)canonical((uintptr_t)a1),(unsigned long long)canonical((uintptr_t)a2));return options[100];}
int (findit)(void){append("dependency:findit;");return options[34];}
int (getpos)(coord * a0,boolean a1,const char * a2){if(readcount++>options[213])return -1;append("getpos:%d:%d:%d:%s;",a0->x,a0->y,a1,a2);a0->x=options[202]?options[202]:u.ux;a0->y=options[203]?options[203]:u.uy;grow();return options[204];}
char * (mon_nam)(struct monst * a0){return labels[(a0-mpool)%8];}
char (yn_function)(const char * a0,const char * a1,char a2,boolean a3){append("yn:%s:%s:%d:%d;",a0,a1,a2,a3);grow();return options[205]?options[205]:a2;}
boolean (paranoid_query)(boolean a0,const char * a1){append("dependency:paranoid_query:%d:%s;",(int)a0,a1?a1:"(null)");return options[95];}
void (done)(int a0){append("dependency:done:%d;",(int)a0);}
int (dist2)(coordxy a0,coordxy a1,coordxy a2,coordxy a3){return (a0-a2)*(a0-a2)+(a1-a3)*(a1-a3);}
boolean (unmap_invisible)(coordxy a0,coordxy a1){append("dependency:unmap_invisible:%d:%d;",(int)a0,(int)a1);return options[127];}
int (canseemon)(struct monst * a0){append("dependency:canseemon:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[15];}
int (sensemon)(struct monst * a0){append("dependency:sensemon:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[110];}
char * (x_monnam)(struct monst * a0,int a1,const char * a2,int a3,boolean a4){return labels[(a0-mpool)%8];}
void (You)(const char * a0,...){va_list ap;va_start(ap,a0);message("You",a0,ap);va_end(ap);}
void (xkilled)(struct monst * a0,int a1){append("dependency:xkilled:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);}
char * (upstart)(char * a0){if(*a0>='a'&&*a0<='z')*a0-=32;return a0;}
void (monkilled)(struct monst * a0,const char * a1,int a2){append("dependency:monkilled:%llu:%s:%d;",(unsigned long long)canonical((uintptr_t)a0),a1?a1:"(null)",(int)a2);}
void (There)(const char * a0,...){va_list ap;va_start(ap,a0);message("There",a0,ap);va_end(ap);}
void (getlin)(const char * a0,char * a1){append("getlin:%s;",a0);strcpy(a1,input);readcount++;grow();}
boolean (load_lua)(const char * a0,nhl_sandbox_info * a1){append("load_lua:%s:%u:%u:%u:%u;",a0,a1->flags,a1->memlimit,a1->steps,a1->perpcall);return options[56];}
int (lspo_reset_level)(lua_State * a0){append("dependency:lspo_reset_level:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[60];}
boolean (load_special)(const char * a0){append("dependency:load_special:%s;",a0?a0:"(null)");return options[57];}
int (lspo_finalize_level)(lua_State * a0){append("dependency:lspo_finalize_level:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[59];}
void (level_tele)(void){append("dependency:level_tele;");}
void (flip_level_rnd)(int a0,boolean a1){append("dependency:flip_level_rnd:%d:%d;",(int)a0,(int)a1);}
void (flip_level)(int a0,boolean a1){append("dependency:flip_level:%d:%d;",(int)a0,(int)a1);}
void (docrt)(void){append("dependency:docrt;");}
char * (mungspaces)(char * a0){char*p=a0;while(*p==' ')p++;memmove(a0,p,strlen(p)+1);p=a0+strlen(a0);while(p>a0&&p[-1]==' ')*--p=0;return a0;}
void (losexp)(const char * a0){append("losexp:%s;",a0);u.ulevel--;}
void (pluslvl)(boolean a0){append("pluslvl:%d;",a0);u.ulevel++;}
int (getdir)(const char * a0){append("getdir:%s;",a0?a0:"(null)");return options[206];}
void (mhurtle)(struct monst * a0,int a1,int a2,int a3){append("dependency:mhurtle:%llu:%d:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1,(int)a2,(int)a3);}
void (hurtle)(int a0,int a1,int a2,boolean a3){append("dependency:hurtle:%d:%d:%d:%d;",(int)a0,(int)a1,(int)a2,(int)a3);}
void (panic)(const char * a0,...){va_list ap;va_start(ap,a0);message("panic",a0,ap);va_end(ap);abort();}
void (polyself)(int a0){append("dependency:polyself:%d;",(int)a0);}
boolean (may_dig)(coordxy a0,coordxy a1){append("dependency:may_dig:%d:%d;",(int)a0,(int)a1);return options[76];}
s_level * (Is_special)(d_level * a0){return options[214]?&special:0;}
char * (eos)(char * a0){return a0+strlen(a0);}
boolean (Invocation_lev)(d_level * a0){append("dependency:Invocation_lev:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[1];}
boolean (On_W_tower_level)(d_level * a0){append("dependency:On_W_tower_level:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[4];}
int (strncmpi)(const char * a0,const char * a1,int a2){for(int i=0;i<a2;i++){unsigned char x=a0[i],y=a1[i];if(x>='A'&&x<='Z')x+=32;if(y>='A'&&y<='Z')y+=32;if(x!=y||!x)return x-y;}return 0;}
boolean (olfaction)(struct permonst * a0){append("dependency:olfaction:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[91];}
int (glyph_at)(coordxy a0,coordxy a1){append("dependency:glyph_at:%d:%d;",(int)a0,(int)a1);return options[45];}
const char * (body_part)(int a0){return "nose";}
boolean (usmellmon)(struct permonst * a0){append("dependency:usmellmon:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[129];}
void (map_invisible)(coordxy a0,coordxy a1){append("dependency:map_invisible:%d:%d;",(int)a0,(int)a1);}
void (add_menu_str)(winid a0,const char * a1){append("menustr:%d:%s;",a0,a1);}
const char * (property_by_index)(int a0,int * a1){append("property:%d;",a0);if(a0<0||a0>=options[207])return 0;*a1=options[208]?options[208]:a0+1;return labels[a0%32];}
void (add_menu)(winid a0,const glyph_info * a1,const union any * a2,char a3,char a4,int a5,int a6,const char * a7,unsigned int a8){append("menu:%d:%d:%d:%d:%d:%d:%s:%u;",a0,a2->a_int,a3,a4,a5,a6,a7,a8);grow();}
int (select_menu)(winid a0,int a1,menu_item ** a2){append("select_menu:%d:%d;",a0,a1);if(options[209]>0){*a2=malloc(options[209]*sizeof **a2);memcpy(*a2,selections,options[209]*sizeof **a2);}else *a2=0;return options[209];}
void (make_blinded)(long a0,boolean a1){append("dependency:make_blinded:%ld:%d;",(long)a0,(int)a1);}
void (make_deaf)(long a0,boolean a1){append("dependency:make_deaf:%ld:%d;",(long)a0,(int)a1);}
boolean (make_hallucinated)(long a0,boolean a1,long a2){append("dependency:make_hallucinated:%ld:%d:%ld;",(long)a0,(int)a1,(long)a2);return options[64];}
boolean (rng_log_enabled)(void){return options[210];}
void (rng_log_set_caller)(const char * a0,int a1,const char * a2){append("site:%s:%d:%s;",a0,a1,a2);grow();if(options[211]&&!reentered){reentered=1;wiz_show_nhuuid();append("reentered;");}}
int (rn2)(int a0){seed=(unsigned)seed*1664525U+1013904223U;int v=(unsigned)seed%a0;append("rn2:%d:%d;",a0,v);return v;}
void (make_sick)(long a0,const char * a1,boolean a2,int a3){append("dependency:make_sick:%ld:%s:%d:%d;",(long)a0,a1?a1:"(null)",(int)a2,(int)a3);}
void (make_slimed)(long a0,const char * a1){append("dependency:make_slimed:%ld:%s;",(long)a0,a1?a1:"(null)");}
void (make_stoned)(long a0,const char * a1,int a2,const char * a3){append("dependency:make_stoned:%ld:%s:%d:%s;",(long)a0,a1?a1:"(null)",(int)a2,a3?a3:"(null)");}
void (make_stunned)(long a0,boolean a1){append("dependency:make_stunned:%ld:%d;",(long)a0,(int)a1);}
void (make_vomiting)(long a0,boolean a1){append("dependency:make_vomiting:%ld:%d;",(long)a0,(int)a1);}
void (make_glib)(int a0){append("dependency:make_glib:%d;",(int)a0);}
void (incr_itimeout)(long * a0,int a1){append("incr_timeout:%ld:%d;",*a0,a1);*a0=(*a0&~TIMEOUT)|((*a0+a1)&TIMEOUT);}
void (float_vs_flight)(void){append("dependency:float_vs_flight;");}
void (rescham)(void){append("dependency:rescham;");}
boolean (pooleffects)(boolean a0){append("dependency:pooleffects:%d;",(int)a0);return options[99];}
void (rumor_check)(void){append("dependency:rumor_check;");}
int (size_wseg)(struct monst * a0){append("dependency:size_wseg:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[112];}
void (engr_stats)(const char * a0,char * a1,long * a2,long * a3){append("engr_stats:%s;",a0);snprintf(a1,QBUFSZ,a0,11L,7L);*a2=options[30];*a3=*a2*13;}
void (light_stats)(const char * a0,char * a1,long * a2,long * a3){append("light_stats:%s;",a0);snprintf(a1,QBUFSZ,a0,11L,7L);*a2=options[55];*a3=*a2*13;}
void (timer_stats)(const char * a0,char * a1,long * a2,long * a3){append("timer_stats:%s;",a0);snprintf(a1,QBUFSZ,a0,11L,7L);*a2=options[125];*a3=*a2*13;}
void (region_stats)(const char * a0,char * a1,long * a2,long * a3){append("region_stats:%s;",a0);snprintf(a1,QBUFSZ,a0,11L,7L);*a2=options[102];*a3=*a2*13;}
void (check_wornmask_slots)(void){append("dependency:check_wornmask_slots;");}
boolean (check_invent_gold)(const char * a0){append("dependency:check_invent_gold:%s;",a0?a0:"(null)");return options[16];}
int (does_block)(int a0,int a1,struct rm * a2){append("dependency:does_block:%d:%d:%llu;",(int)a0,(int)a1,(unsigned long long)canonical((uintptr_t)a2));return options[26];}
boolean (get_viz_clear)(int a0,int a1){append("dependency:get_viz_clear:%d:%d;",(int)a0,(int)a1);return options[41];}
void (obj_sanity_check)(void){append("dependency:obj_sanity_check;");}
void (timer_sanity_check)(void){append("dependency:timer_sanity_check;");}
void (mon_sanity_check)(void){append("dependency:mon_sanity_check;");}
void (light_sources_sanity_check)(void){append("dependency:light_sources_sanity_check;");}
void (bc_sanity_check)(void){append("dependency:bc_sanity_check;");}
void (trap_sanity_check)(void){append("dependency:trap_sanity_check;");}
void (engraving_sanity_check)(void){append("dependency:engraving_sanity_check;");}
char * (strkitten)(char * a0,char a1){char*p=a0+strlen(a0);p[0]=a1;p[1]=0;return a0;}
long * (alloc)(unsigned int a0){append("alloc:%u;",a0);return malloc(a0);}
void (nh_deterministic_qsort)(void * a0,size_t a1,size_t a2,int (*a3)(const void *, const void *)){append("qsort:%lu:%lu;",a1,a2);(qsort)(a0,a1,a2,a3);}
char * (minimal_monnam)(struct monst * a0,boolean a1){snprintf(stringbuf,sizeof stringbuf,"monster%ld <0,0>",(long)(a0-mpool));return stringbuf;}
char * (strsubst)(char * a0,const char * a1,const char * a2){char*p=strstr(a0,a1);if(p){size_t n=strlen(a1),m=strlen(a2);memmove(p+m,p+n,strlen(p+n)+1);memcpy(p,a2,m);}return a0;}
void (overview_stats)(winid a0,const char * a1,long * a2,long * a3){append("overview:%d:%s;",a0,a1);*a2=3;*a3=9007199254740997L;}
int (glyph_to_cmap)(int a0){append("dependency:glyph_to_cmap:%d;",(int)a0);return options[46];}
int (mstrength)(struct permonst * a0){append("dependency:mstrength:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[86];}
void (nh_snprintf)(const char * a0,int a1,char * a2,size_t a3,const char * a4,...){append("snprintf:%s:%d:%lu;",a0,a1,a3);va_list ap;va_start(ap,a4);vsnprintf(a2,a3,a4,ap);va_end(ap);}
void (assign_level)(d_level * a0,d_level * a1){*a0=*a1;}
boolean (Is_botlevel)(d_level * a0){append("dependency:Is_botlevel:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[2];}
void (get_level)(d_level * a0,int a1){a0->dnum=u.uz.dnum;a0->dlevel=a1;}
schar (depth)(d_level * a0){return a0->dlevel;}
struct permonst * (rndmonst)(void){append("rndmonst;");return options[215]?&mons[PM_HUMAN]:0;}
struct monst * (makemon)(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){append("makemon:%llu:%d:%d:%lu;",(unsigned long long)canonical((uintptr_t)a0),a1,a2,(unsigned long)a3);return options[216]?&mpool[7]:0;}
void (migrate_to_level)(struct monst * a0,xint16 a1,xint16 a2,coord * a3){append("migrate:%llu:%d:%d:%llu;",(unsigned long long)canonical((uintptr_t)a0),a1,a2,(unsigned long long)canonical((uintptr_t)a3));struct monst**p=&fmon;while(*p){if(*p==a0){*p=a0->nmon;break;}p=&(*p)->nmon;}a0->nmon=0;}
xint16 (ledger_no)(d_level * a0){append("ledger_no:%d:%d;",a0->dnum,a0->dlevel);return options[52];}
boolean (glyphid_cache_status)(void){append("dependency:glyphid_cache_status;");return options[47];}
void (fill_glyphid_cache)(void){append("dependency:fill_glyphid_cache;");}
void (add_menu_heading)(winid a0,const char * a1){append("heading:%d:%s;",a0,a1);}
void (wizcustom_glyphids)(winid a0){append("glyphids:%d;",a0);if(options[212])wizcustom_callback(a0,0,"fixture_glyph");}
void (free_glyphid_cache)(void){append("dependency:free_glyphid_cache;");}
static winid cw(int kind){append("create:%d;",kind);grow();return 7;}
static void dw(winid w){append("destroy:%d;",w);}
static void pw(winid w,int attr,const char*s){append("put:%d:%d:%s;",w,attr,s);grow();}
static void display(winid w,boolean block){append("display:%d:%d;",w,block);}
static void sm(winid w,unsigned long behavior){append("start:%d:%lu;",w,behavior);}
static void em(winid w,const char*s){append("end:%d:%s;",w,s?s:"(null)");}
static void cp(void){append("cliparound; ");}

#ifdef HYBRID_WIZCMDS
extern int wiz_wish();
extern int wiz_identify();
extern void teleport_wizcmds_test_makemap_unmakemon(struct monst * mtmp,boolean migratory);
#define makemap_unmakemon teleport_wizcmds_test_makemap_unmakemon
extern void makemap_remove_mons();
extern int wiz_makemap();
extern int wiz_map();
extern int wiz_genesis();
extern int wiz_where();
extern int wiz_detect();
extern int wiz_kill();
extern int wiz_load_lua();
extern int wiz_load_splua();
extern int wiz_level_tele();
extern int wiz_flip_level();
extern int wiz_level_change();
extern int wiz_telekinesis();
extern int wiz_panic();
extern int wiz_fuzzer();
extern int wiz_polyself();
extern int wiz_show_seenv();
extern int wiz_show_vision();
extern int wiz_show_wmodes();
extern void wiz_map_levltyp();
extern void wiz_levltyp_legend();
extern int wiz_smell();
extern int wiz_intrinsic();
extern int wiz_rumor_check();
extern int teleport_wizcmds_test_size_obj(struct obj * otmp);
#define size_obj teleport_wizcmds_test_size_obj
extern void teleport_wizcmds_test_count_obj(struct obj * chain,long * total_count,long * total_size,boolean top,boolean recurse);
#define count_obj teleport_wizcmds_test_count_obj
extern void teleport_wizcmds_test_obj_chain(winid win,const char * src,struct obj * chain,boolean force,long * total_count,long * total_size);
#define obj_chain teleport_wizcmds_test_obj_chain
extern void teleport_wizcmds_test_mon_invent_chain(winid win,const char * src,struct monst * chain,long * total_count,long * total_size);
#define mon_invent_chain teleport_wizcmds_test_mon_invent_chain
extern void teleport_wizcmds_test_contained_stats(winid win,const char * src,long * total_count,long * total_size);
#define contained_stats teleport_wizcmds_test_contained_stats
extern int teleport_wizcmds_test_size_monst(struct monst * mtmp,boolean incl_wsegs);
#define size_monst teleport_wizcmds_test_size_monst
extern void teleport_wizcmds_test_mon_chain(winid win,const char * src,struct monst * chain,boolean force,long * total_count,long * total_size);
#define mon_chain teleport_wizcmds_test_mon_chain
extern void teleport_wizcmds_test_misc_stats(winid win,long * total_count,long * total_size);
#define misc_stats teleport_wizcmds_test_misc_stats
extern void teleport_wizcmds_test_you_sanity_check();
#define you_sanity_check teleport_wizcmds_test_you_sanity_check
extern void teleport_wizcmds_test_levl_sanity_check();
#define levl_sanity_check teleport_wizcmds_test_levl_sanity_check
extern void sanity_check();
extern int teleport_wizcmds_test_migrsort_cmp(const void * vptr1,const void * vptr2);
#define migrsort_cmp teleport_wizcmds_test_migrsort_cmp
extern void teleport_wizcmds_test_list_migrating_mons(d_level * nextlevl);
#define list_migrating_mons teleport_wizcmds_test_list_migrating_mons
extern int wiz_show_stats();
extern int wiz_display_macros();
extern int wiz_show_nhuuid();
extern int wiz_mon_diff();
extern int wiz_objprobs();
extern int wiz_migrate_mons();
extern int wiz_custom();
extern void wizcustom_callback(winid win,int glyphnum,char * id);
#else
#include "../.cache/wasm64-build/tree/src/wizcmds.c"
#define TELEPORT_REFERENCE_TU 1
#endif
#include "../nethack-c/wasm/tu-fragments/wizcmds-support.c"
static uint64_t canonical(uint64_t value){
#define REGION(v,id) if(value>=(uintptr_t)&(v)&&value<(uintptr_t)&(v)+sizeof(v))return ((uint64_t)(id)<<48)+(value-(uintptr_t)&(v))
REGION(mpool,1);
REGION(opool,2);
REGION(mextras,3);
REGION(oextras,4);
REGION(traps,5);
REGION(engrs,6);
REGION(damages,7);
REGION(killers,8);
REGION(bones,9);
REGION(levelarg,10);
REGION(counters,11);
REGION(selections,12);
REGION(any,13);
REGION(input,14);
REGION(labels,15);
REGION(vis,16);
REGION(visrows,17);
REGION(unicodes,18);
REGION(special,19);
REGION(flags,20);
REGION(unavailcmd,21);
REGION(iflags,22);
REGION(svm,23);
REGION(u,24);
REGION(svl,25);
REGION(gm,26);
REGION(a11y,27);
REGION(gf,28);
REGION(head_engr,29);
REGION(ynqchars,30);
REGION(gu,31);
REGION(svk,32);
REGION(genders,33);
REGION(mons,34);
REGION(svc,35);
REGION(c_common_strings,36);
REGION(ynchars,37);
REGION(windowprocs,38);
REGION(gv,39);
REGION(defsyms,40);
REGION(svd,41);
REGION(levltyp,42);
REGION(gy,43);
REGION(cg,44);
REGION(nul_glyphinfo,45);
REGION(disp,46);
REGION(gi,47);
REGION(objects,48);
REGION(WIN_MESSAGE,49);
REGION(program_state,50);
REGION(gb,51);
REGION(svn,52);
REGION(obj_descr,53);
REGION(gs,54);
REGION(gc,55);
REGION(known_handling,56);
REGION(glyphmap,57);
#undef REGION
return value;}
void probe_reset(void){
memset((void*)&flags,0,sizeof flags);
memset((void*)&iflags,0,sizeof iflags);
memset((void*)&svm,0,sizeof svm);
memset((void*)&u,0,sizeof u);
memset((void*)&svl,0,sizeof svl);
memset((void*)&gm,0,sizeof gm);
memset((void*)&a11y,0,sizeof a11y);
memset((void*)&gf,0,sizeof gf);
memset((void*)&head_engr,0,sizeof head_engr);
memset((void*)&gu,0,sizeof gu);
memset((void*)&svk,0,sizeof svk);
memset((void*)&mons,0,sizeof mons);
memset((void*)&svc,0,sizeof svc);
memset((void*)&windowprocs,0,sizeof windowprocs);
memset((void*)&gv,0,sizeof gv);
memset((void*)&svd,0,sizeof svd);
memset((void*)&gy,0,sizeof gy);
memset((void*)&disp,0,sizeof disp);
memset((void*)&gi,0,sizeof gi);
memset((void*)&objects,0,sizeof objects);
memset((void*)&WIN_MESSAGE,0,sizeof WIN_MESSAGE);
memset((void*)&program_state,0,sizeof program_state);
memset((void*)&gb,0,sizeof gb);
memset((void*)&svn,0,sizeof svn);
memset((void*)&obj_descr,0,sizeof obj_descr);
memset((void*)&gs,0,sizeof gs);
memset((void*)&gc,0,sizeof gc);
memset((void*)&glyphmap,0,sizeof glyphmap);
memset(&mpool,0,sizeof mpool);
memset(&opool,0,sizeof opool);
memset(&mextras,0,sizeof mextras);
memset(&oextras,0,sizeof oextras);
memset(&traps,0,sizeof traps);
memset(&engrs,0,sizeof engrs);
memset(&damages,0,sizeof damages);
memset(&killers,0,sizeof killers);
memset(&bones,0,sizeof bones);
memset(&levelarg,0,sizeof levelarg);
memset(&counters,0,sizeof counters);
memset(&selections,0,sizeof selections);
memset(&any,0,sizeof any);
memset(&input,0,sizeof input);
memset(&labels,0,sizeof labels);
memset(&vis,0,sizeof vis);
memset(&visrows,0,sizeof visrows);
memset(&unicodes,0,sizeof unicodes);
memset(&special,0,sizeof special);
memset(options,0,sizeof options);tracepos=0;tracebuf[0]=0;seed=1;readcount=0;reentered=0;if(growth){free(growth);growth=0;}
windowprocs.name="tty";windowprocs.wp_id=wp_tty;windowprocs.win_create_nhwindow=cw;windowprocs.win_destroy_nhwindow=dw;windowprocs.win_putstr=pw;windowprocs.win_display_nhwindow=display;windowprocs.win_start_menu=sm;windowprocs.win_end_menu=em;
for(int i=0;i<ROWNO;i++){visrows[i]=vis[i];for(int x=0;x<COLNO;x++)levl[x][i].typ=ROOM;}gv.viz_array=visrows;
for(int i=0;i<NUMMONS+1;i++){memcpy((void*)&mons[i].pmidx,&i,sizeof i);mons[i].mlet=i==NUMMONS?0:S_HUMAN;mons[i].mlevel=5;mons[i].pmnames[NEUTRAL]="fixture species";mons[i].difficulty=5;}
for(int i=0;i<NUM_OBJECTS;i++){objects[i].oc_name_idx=i;objects[i].oc_class=WEAPON_CLASS;objects[i].oc_prob=i%7;obj_descr[i].oc_name="fixture object";}
for(int i=0;i<MAX_TYPE+2;i++)levltyp[i]="fixture terrain";
for(int i=0;i<32;i++)snprintf(labels[i],sizeof labels[i],"name%d",i);
for(int i=0;i<8;i++){mpool[i].data=&mons[PM_HUMAN];mpool[i].m_id=100+i;mpool[i].mhp=20;mpool[i].mx=20+i;mpool[i].my=10;selections[i].item.a_int=i+1;selections[i].count=-1;}
for(int i=0;i<16;i++){opool[i].quan=1;opool[i].otyp=LONG_SWORD;}
u.ux=20;u.uy=10;u.uz.dnum=1;u.uz.dlevel=3;u.ulevel=u.ulevelmax=10;u.uhp=u.uhpmax=40;u.uen=u.uenmax=30;u.mh=u.mhmax=50;u.umonnum=u.umonster=PM_HUMAN;gu.urole.mnum=PM_ARCHEOLOGIST;gy.youmonst.data=&mons[PM_HUMAN];
options[204]=-1;levelarg.dnum=1;levelarg.dlevel=4;strcpy(svn.nhuuid,"fixture-id");
}
void probe_option(int i,int v){if(i<0||i>=256)abort();options[i]=v;}
void*probe_pointer(int k,int i){switch(k){case 0:return &mpool[i];case 1:return &opool[i];case 2:return &mons[i];case 3:return &objects[i];case 4:return &traps[i];case 5:return input;case 6:return &gy.youmonst;case 7:return &engrs[i];case 8:return &mextras[i];case 9:return &oextras[i];case 10:return &levelarg;case 11:return &counters[i];case 12:return &selections[i];case 13:return &glyphmap[i];case 14:return labels[i];case 15:return &damages[i];case 16:return &killers[i];case 17:return &bones[i];case 18:return &any;case 19:return &unicodes[i];case 20:return &special;default:abort();}}
uint64_t probe_canonical(uint64_t p){return canonical(p);}
const char*probe_trace(void){return tracebuf;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
int probe_layout_count(void){return sizeof wizcmds_layout/sizeof wizcmds_layout[0];}
const char*probe_layout_name(int i){return wizcmds_layout[i].name;}
uint64_t probe_layout_value(int i){return wizcmds_layout[i].value;}
static const char*option_names[]={"In_W_tower","Invocation_lev","Is_botlevel","Is_special","On_W_tower_level","There","You","add_menu","add_menu_heading","add_menu_str","alloc","assign_level","atoi","bc_sanity_check","body_part","canseemon","check_invent_gold","check_wornmask_slots","cmd_from_func","create_particular","depth","display_inventory","dist2","dmonsfree","do_mapping","docrt","does_block","done","ecname_from_fn","encumber_msg","engr_stats","engraving_sanity_check","eos","fill_glyphid_cache","findit","flip_level","flip_level_rnd","float_vs_flight","free","free_glyphid_cache","get_level","get_viz_clear","getdir","getlin","getpos","glyph_at","glyph_to_cmap","glyphid_cache_status","hurtle","impossible","incr_itimeout","keepdogs","ledger_no","level_tele","light_sources_sanity_check","light_stats","load_lua","load_special","losexp","lspo_finalize_level","lspo_reset_level","make_blinded","make_deaf","make_glib","make_hallucinated","make_sick","make_slimed","make_stoned","make_stunned","make_vomiting","makemap_prepost","makemon","makewish","map_engraving","map_invisible","map_trap","may_dig","memset","mhurtle","migrate_to_level","minimal_monnam","mklev","mon_nam","mon_sanity_check","mongone","monkilled","mstrength","mungspaces","nh_deterministic_qsort","nh_snprintf","obj_sanity_check","olfaction","on_level","overview_stats","panic","paranoid_query","pline","pluslvl","polyself","pooleffects","print_dungeon","property_by_index","region_stats","rescham","rn2","rndmonst","rng_log_enabled","rng_log_set_caller","rumor_check","select_menu","sensemon","setpaid","size_wseg","sprintf","sscanf","strcat","strchr","strcmp","strcpy","strkitten","strlen","strncmp","strncmpi","strsubst","timer_sanity_check","timer_stats","trap_sanity_check","unmap_invisible","upstart","usmellmon","wizcustom_glyphids","x_monnam","xkilled","yn_function"};
const char*probe_option_name(int i){return i<134?option_names[i]:0;}
int probe_call_wiz_wish(){return wiz_wish();}
int probe_call_wiz_identify(){return wiz_identify();}
void probe_call_makemap_unmakemon(struct monst * mtmp,boolean migratory){makemap_unmakemon(mtmp,migratory);}
void probe_call_makemap_remove_mons(){makemap_remove_mons();}
int probe_call_wiz_makemap(){return wiz_makemap();}
int probe_call_wiz_map(){return wiz_map();}
int probe_call_wiz_genesis(){return wiz_genesis();}
int probe_call_wiz_where(){return wiz_where();}
int probe_call_wiz_detect(){return wiz_detect();}
int probe_call_wiz_kill(){return wiz_kill();}
int probe_call_wiz_load_lua(){return wiz_load_lua();}
int probe_call_wiz_load_splua(){return wiz_load_splua();}
int probe_call_wiz_level_tele(){return wiz_level_tele();}
int probe_call_wiz_flip_level(){return wiz_flip_level();}
int probe_call_wiz_level_change(){return wiz_level_change();}
int probe_call_wiz_telekinesis(){return wiz_telekinesis();}
int probe_call_wiz_panic(){return wiz_panic();}
int probe_call_wiz_fuzzer(){return wiz_fuzzer();}
int probe_call_wiz_polyself(){return wiz_polyself();}
int probe_call_wiz_show_seenv(){return wiz_show_seenv();}
int probe_call_wiz_show_vision(){return wiz_show_vision();}
int probe_call_wiz_show_wmodes(){return wiz_show_wmodes();}
void probe_call_wiz_map_levltyp(){wiz_map_levltyp();}
void probe_call_wiz_levltyp_legend(){wiz_levltyp_legend();}
int probe_call_wiz_smell(){return wiz_smell();}
int probe_call_wiz_intrinsic(){return wiz_intrinsic();}
int probe_call_wiz_rumor_check(){return wiz_rumor_check();}
int probe_call_size_obj(struct obj * otmp){return size_obj(otmp);}
void probe_call_count_obj(struct obj * chain,long * total_count,long * total_size,boolean top,boolean recurse){count_obj(chain,total_count,total_size,top,recurse);}
void probe_call_obj_chain(winid win,const char * src,struct obj * chain,boolean force,long * total_count,long * total_size){obj_chain(win,src,chain,force,total_count,total_size);}
void probe_call_mon_invent_chain(winid win,const char * src,struct monst * chain,long * total_count,long * total_size){mon_invent_chain(win,src,chain,total_count,total_size);}
void probe_call_contained_stats(winid win,const char * src,long * total_count,long * total_size){contained_stats(win,src,total_count,total_size);}
int probe_call_size_monst(struct monst * mtmp,boolean incl_wsegs){return size_monst(mtmp,incl_wsegs);}
void probe_call_mon_chain(winid win,const char * src,struct monst * chain,boolean force,long * total_count,long * total_size){mon_chain(win,src,chain,force,total_count,total_size);}
void probe_call_misc_stats(winid win,long * total_count,long * total_size){misc_stats(win,total_count,total_size);}
void probe_call_you_sanity_check(){you_sanity_check();}
void probe_call_levl_sanity_check(){levl_sanity_check();}
void probe_call_sanity_check(){sanity_check();}
int probe_call_migrsort_cmp(const void * vptr1,const void * vptr2){return migrsort_cmp(vptr1,vptr2);}
void probe_call_list_migrating_mons(d_level * nextlevl){list_migrating_mons(nextlevl);}
int probe_call_wiz_show_stats(){return wiz_show_stats();}
int probe_call_wiz_display_macros(){return wiz_display_macros();}
int probe_call_wiz_show_nhuuid(){return wiz_show_nhuuid();}
int probe_call_wiz_mon_diff(){return wiz_mon_diff();}
int probe_call_wiz_objprobs(){return wiz_objprobs();}
int probe_call_wiz_migrate_mons(){return wiz_migrate_mons();}
int probe_call_wiz_custom(){return wiz_custom();}
void probe_call_wizcustom_callback(winid win,int glyphnum,char * id){wizcustom_callback(win,glyphnum,id);}
