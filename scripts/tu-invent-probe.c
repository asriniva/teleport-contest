/* Controlled INVENT foreign world; original invent.c appears in reference only. */
#include "hack.h"
#include "tu-invent-layout.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <emscripten.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
__typeof__(u) u;
__typeof__(flags) flags;
__typeof__(program_state) program_state;
__typeof__(gs) gs;
__typeof__(gi) gi;
__typeof__(gl) gl;
__typeof__(gu) gu;
__typeof__(disp) disp;
__typeof__(svc) svc;
__typeof__(uquiver) uquiver;
__typeof__(gy) gy;
__typeof__(uwep) uwep;
__typeof__(uswapwep) uswapwep;
__typeof__(svl) svl;
__typeof__(uball) uball;
__typeof__(uchain) uchain;
__typeof__(uarmg) uarmg;
__typeof__(hands_obj) hands_obj;
__typeof__(iflags) iflags;
__typeof__(windowprocs) windowprocs;
__typeof__(uarm) uarm;
__typeof__(uarmc) uarmc;
__typeof__(uarmf) uarmf;
__typeof__(uarmh) uarmh;
__typeof__(uarms) uarms;
__typeof__(uarmu) uarmu;
__typeof__(uright) uright;
__typeof__(uleft) uleft;
__typeof__(uamul) uamul;
__typeof__(ublindf) ublindf;
__typeof__(yn_number) yn_number;
__typeof__(cg) cg;
__typeof__(nul_glyphinfo) nul_glyphinfo;
__typeof__(gd) gd;
__typeof__(go) go;
__typeof__(gc) gc;
__typeof__(WIN_INVEN) WIN_INVEN;
__typeof__(gt) gt;
__typeof__(WIN_MESSAGE) WIN_MESSAGE;
__typeof__(svd) svd;
__typeof__(uskin) uskin;
__typeof__(gp) gp;

const char quitchars[]=" \033\n\r",ynchars[]="yn",ynaqchars[]="ynaq",ynNaqchars[]="yn#aq";
const struct c_common_strings c_common_strings={.c_thats_enough_tries="That's enough tries!",.c_silly_thing_to="silly thing to",.c_Never_mind="Never mind."};
extern win_request_info zerowri;extern void invent_foreign_wri(long,int);extern void invent_foreign_copy(unsigned char*);
static struct obj obj[16];static struct monst mon[4];static struct trap trapcell;static stairway staircell;static NhRegion regioncell;
static char buffers[8][8192],scratch[8][BUFSZ],input[BUFSZ],tracebuf[2097152],snap[2097152];static struct obj*objcell[4];static Loot loot[20];static menu_item menu[20];static anything anycell;static long longs[8];static struct _cmd_queue queue[8];static int qnext,qcount,selectnext;
static long opts[256];static int tracepos,draws,callerline,reenter,automatic_sp;static unsigned rngstate;static const char*callerfile,*callerowner;static win_request_info backendwri,*heldwri;
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);tracepos+=vsnprintf(tracebuf+tracepos,sizeof tracebuf-tracepos,f,ap);va_end(ap);if(tracepos>=sizeof tracebuf-8192)abort();}
static int oid(const struct obj*p){return p==&hands_obj?99:p>=obj&&p<obj+16?(int)(p-obj)+1:0;}
EM_JS(void,fixture_throw,(void),{throw new Error('INVENT controlled callback');});
static void callback(void){if(opts[30]){opts[30]=0;emscripten_resize_heap(emscripten_get_heap_size()+16777216);}if(opts[31]){opts[31]=0;fixture_throw();}if(opts[32]&&!reenter){reenter=1;logmsg("reentry:%s;",currency(2L));reenter=0;}}
static void vlog(const char*name,const char*f,va_list ap){logmsg("%s:",name);tracepos+=vsnprintf(tracebuf+tracepos,sizeof tracebuf-tracepos,f,ap);logmsg(";");callback();}
void pline(const char*f,...){va_list ap;va_start(ap,f);vlog("pline",f,ap);va_end(ap);}
void You(const char*f,...){va_list ap;va_start(ap,f);vlog("You",f,ap);va_end(ap);}
void Your(const char*f,...){va_list ap;va_start(ap,f);vlog("Your",f,ap);va_end(ap);}
void There(const char*f,...){va_list ap;va_start(ap,f);vlog("There",f,ap);va_end(ap);}
void pline_The(const char*f,...){va_list ap;va_start(ap,f);vlog("The",f,ap);va_end(ap);}
void impossible(const char*f,...){va_list ap;va_start(ap,f);vlog("impossible",f,ap);va_end(ap);}
void panic(const char*f,...){va_list ap;va_start(ap,f);vlog("panic",f,ap);va_end(ap);fixture_throw();__builtin_unreachable();}
void livelog_printf(long ll,const char*f,...){va_list ap;logmsg("livelog:%ld;",ll);va_start(ap,f);vlog("live",f,ap);va_end(ap);}
static winid backend_create(int t){logmsg("create:%d;",t);callback();return opts[2]?-1:17;}
static void backend_clear(winid w){logmsg("clear:%d;",w);callback();}
static void backend_display(winid w,boolean b){logmsg("display:%d/%d;",w,b);callback();}
static void backend_destroy(winid w){logmsg("destroy:%d;",w);callback();}
static void backend_put(winid w,int a,const char*s){if(opts[36]){int sp=emscripten_stack_get_current();if(!automatic_sp)automatic_sp=sp;logmsg("stack:%d;",sp-automatic_sp);}logmsg("put:%d/%d:%s;",w,a,s);callback();}
static void backend_start(winid w,unsigned long f){logmsg("start:%d/%lu;",w,f);callback();}
static void backend_end(winid w,const char*s){logmsg("end:%d:%s;",w,s?s:"NULL");callback();}
static char backend_message(char c,int how,const char*s){logmsg("message:%d/%d:%s;",c,how,s);callback();return opts[3]?opts[3]:c;}
static void backend_wait(void){logmsg("wait;");callback();}
static void backend_history(const char*s,boolean b){logmsg("history:%d:%s;",b,s);callback();}
static void backend_update(int n){logmsg("update:%d;",n);callback();}
static win_request_info*backend_ctrl(winid w,int req,win_request_info*p){logmsg("ctrl:%d/%d:",w,req);for(int i=0;i<48;i++)logmsg("%02x",((unsigned char*)p)[i]);logmsg(";same:%d;",heldwri==p);heldwri=p;callback();if(opts[44]){p->tocore.maxslot=opts[45];p->tocore.tocore_flags=opts[46];}if(opts[4])return 0;if(opts[5])return &backendwri;return p;}
static char*objname(struct obj*p){snprintf(scratch[0],BUFSZ,"object%d[%ld:%d/%d/%d/%d]",p?p->otyp:-1,p?p->quan:0,p?p->blessed:0,p?p->cursed:0,p?p->odiluted:0,p?p->spe:0);callback();return scratch[0];}
static int draw(int n,const char*which){if(n<=0)abort();rngstate=rngstate*1664525U+1013904223U;int v=(rngstate>>1)%(unsigned)n;logmsg("%s:%d/%d",which,n,v);if(which[0]=='r')logmsg(":%s:%d:%s",callerfile?callerfile:"NULL",callerline,callerowner?callerowner:"NULL");logmsg(";");draws++;callback();return v;}

void (observe_object)(struct obj * a0){logmsg("observe:%d;",oid(a0));a0->dknown=1;callback();}
boolean (is_art)(struct obj * a0,int a1){logmsg("is_art;");callback();return opts[60];}
char * (cxname_singular)(struct obj * a0){return objname(a0);}
char * (dupstr)(const char * a0){return strdup(a0);}
void (maybereleaseobuf)(char * a0){logmsg("maybereleaseobuf;");callback();}
long * (alloc)(unsigned int a0){logmsg("alloc:%u;",a0);return malloc(a0);}
char (inside_shop)(coordxy a0,coordxy a1){logmsg("inside_shop;");callback();return opts[61];}
struct monst * (shop_keeper)(char a0){return opts[23]?&mon[0]:0;}
int (inhishop)(struct monst * a0){logmsg("inhishop;");callback();return opts[62];}
int (weight)(struct obj * a0){logmsg("weight:%d;",oid(a0));return opts[6]?opts[6]:a0->quan;}
struct obj * (oname)(struct obj * a0,const char * a1,unsigned int a2){logmsg("oname:%d:%s/%u;",oid(a0),a1,a2);return a0;}
void (obj_extract_self)(struct obj * a0){logmsg("extract_self:%d;",oid(a0));a0->where=OBJ_FREE;a0->nobj=0;callback();}
void (obj_merge_light_sources)(struct obj * a0,struct obj * a1){logmsg("obj_merge_light_sources;");callback();}
void (obj_stop_timers)(struct obj * a0){logmsg("obj_stop_timers;");callback();}
void (setnotworn)(struct obj * a0){logmsg("setnotworn:%d;",oid(a0));a0->owornmask=0;}
void (setworn)(struct obj * a0,long a1){logmsg("setworn:%d/%ld;",oid(a0),a1);a0->owornmask=a1;}
void (pudding_merge_message)(struct obj * a0,struct obj * a1){logmsg("pudding_merge_message;");callback();}
struct obj * (obj_absorb)(struct obj ** a0,struct obj ** a1){logmsg("absorb:%d/%d;",oid(*a0),oid(*a1));(*a0)->quan+=(*a1)->quan;(*a1)->where=OBJ_FREE;*a1=0;callback();return *a0;}
void (obfree)(struct obj * a0,struct obj * a1){logmsg("obfree:%d/%d;",oid(a0),oid(a1));a0->where=OBJ_FREE;callback();}
void (record_achievement)(schar a0){logmsg("record_achievement;");callback();}
boolean (is_quest_artifact)(struct obj * a0){logmsg("is_quest_artifact;");callback();return opts[63];}
void (artitouch)(struct obj * a0){logmsg("artitouch;");callback();}
void (set_artifact_intrinsic)(struct obj * a0,boolean a1,long a2){logmsg("set_artifact_intrinsic;");callback();}
boolean (confers_luck)(struct obj * a0){logmsg("confers_luck;");callback();return opts[64];}
void (set_moreluck)(void){logmsg("set_moreluck;");callback();}
char * (yname)(struct obj * a0){return objname(a0);}
void (discover_object)(int a0,boolean a1,boolean a2,boolean a3){logmsg("discover_object;");callback();}
void (picked_container)(struct obj * a0){logmsg("picked_container;");callback();}
void (reset_justpicked)(struct obj * a0){for(struct obj*p=a0;p;p=p->nobj)p->pickup_prev=0;}
boolean (throwing_weapon)(struct obj * a0){logmsg("throwing_weapon;");callback();return opts[65];}
void (setuqwep)(struct obj * a0){logmsg("quiver:%d;",oid(a0));uquiver=a0;}
boolean (dead_species)(int a0,boolean a1){logmsg("dead_species;");callback();return opts[66];}
void (attach_fig_transform_timeout)(struct obj * a0){logmsg("attach_fig_transform_timeout;");callback();}
void (place_object)(struct obj * a0,coordxy a1,coordxy a2){logmsg("place_object;");callback();}
int (touch_artifact)(struct obj * a0,struct monst * a1){return !opts[26];}
void (dropy)(struct obj * a0){logmsg("dropy;");callback();}
boolean (u_safe_from_fatal_corpse)(struct obj * a0,int a1){return !opts[27];}
int (near_capacity)(void){logmsg("near_capacity;");callback();return opts[67];}
int (inv_cnt)(boolean a0){int n=0;for(struct obj*p=gi.invent;p;p=p->nobj)if(a0||p->oclass!=COIN_CLASS)n++;return n;}
struct obj * (splitobj)(struct obj * a0,long a1){logmsg("split:%d/%ld;",oid(a0),a1);obj[15]=*a0;obj[15].quan=a1;a0->quan-=a1;obj[15].nobj=a0->nobj;a0->nobj=&obj[15];callback();return &obj[15];}
void (encumber_msg)(void){logmsg("encumber_msg;");callback();}
boolean (can_reach_floor)(boolean a0){return !opts[25];}
void (dropx)(struct obj * a0){logmsg("dropx;");callback();}
void (hitfloor)(struct obj * a0,boolean a1){logmsg("hitfloor;");callback();}
void (check_unpaid)(struct obj * a0){logmsg("check_unpaid;");callback();}
void (curse)(struct obj * a0){a0->blessed=0;a0->cursed=1;}
anything * (obj_to_any)(struct obj * a0){anycell.a_obj=a0;return &anycell;}
long (stop_timer)(short a0,union any * a1){logmsg("stop_timer;");callback();return opts[68];}
void (extract_nobj)(struct obj * a0,struct obj ** a1){logmsg("extract:%d;",oid(a0));for(struct obj**p=a1;*p;p=&(*p)->nobj)if(*p==a0){*p=a0->nobj;a0->nobj=0;break;}callback();}
void (unpunish)(void){logmsg("unpunish;");callback();}
boolean (obj_resists)(struct obj * a0,int a1,int a2){return opts[24];}
void (maybe_unhide_at)(coordxy a0,coordxy a1){logmsg("maybe_unhide_at;");callback();}
void (newsym)(coordxy a0,coordxy a1){logmsg("newsym;");callback();}
boolean (rng_log_enabled)(void){return !opts[12];}
void (rng_log_set_caller)(const char * a0,int a1,const char * a2){callerfile=a0;callerline=a1;callerowner=a2;}
int (rn2)(int a0){return draw(a0,"rng");}
char * (makeplural)(const char * a0){snprintf(scratch[1],BUFSZ,"%ss",a0);callback();return scratch[1];}
int (welded)(struct obj * a0){logmsg("welded;");callback();return opts[69];}
const char * (fingers_or_gloves)(boolean a0){return "fingers";}
const char * (body_part)(int a0){return "hand";}
struct _cmd_queue * (cmdq_pop)(void){if(qnext==qcount)return 0;struct _cmd_queue*p=malloc(sizeof *p);*p=queue[qnext++];return p;}
void (cmdq_clear)(int a0){logmsg("qclear:%d;",a0);qnext=qcount;}
char (readchar)(void){return opts[9]?opts[9]:27;}
char (yn_function)(const char * a0,const char * a1,char a2,boolean a3){logmsg("yn:%s:%s/%d/%d;",a0,a1?a1:"NULL",a2,a3);callback();return opts[9]?opts[9]:a2?a2:27;}
char (get_count)(const char * a0,char a1,long a2,cmdcount_nht * a3,unsigned int a4){logmsg("get_count:%d/%ld/%u;",a1,a2,a4);*a3=opts[10];return opts[11]?opts[11]:27;}
void (cmdq_add_int)(int a0,int a1){logmsg("cmdq_add_int;");callback();}
void (cmdq_add_key)(int a0,char a1){logmsg("cmdq_add_key;");callback();}
boolean (allow_category)(struct obj * a0){return !opts[17];}
char * (ansimpleoname)(struct obj * a0){return objname(a0);}
void (add_valid_menu_class)(int a0){logmsg("add_valid_menu_class;");callback();}
boolean (not_fully_identified)(struct obj * a0){return !a0->known||!a0->dknown||!a0->bknown||!a0->rknown;}
int (collect_obj_classes)(char * a0,struct obj * a1,boolean a2,boolean (*a3)(struct obj *),int * a4){int n=0,total=0;for(struct obj*p=a1;p;p=p->nobj)if(!a3||a3(p)){char c=def_oc_syms[(int)p->oclass].sym;if(!memchr(a0,c,n))a0[n++]=c;total++;}a0[n]=0;*a4=total;return n;}
int (count_justpicked)(struct obj * a0){int n=0;for(struct obj*p=a0;p;p=p->nobj)n+=p->pickup_prev;return n;}
void (getlin)(const char * a0,char * a1){logmsg("getlin:%s;",a0);strcpy(a1,input);callback();}
boolean (menu_class_present)(int a0){logmsg("menu_class_present;");callback();return opts[70];}
void (bypass_objlist)(struct obj * a0,boolean a1){for(struct obj*p=a0;p;p=p->nobj)p->bypass=a1;}
struct obj * (nxt_unbypassed_loot)(Loot * a0,struct obj * a1){for(Loot*p=a0;p->obj;p++)if(!p->obj->bypass){for(struct obj*q=a1;q;q=q->nobj)if(q==p->obj){q->bypass=1;return q;}}return 0;}
char * (doname)(struct obj * a0){return objname(a0);}
char * (safe_qbuf)(char * a0,const char * a1,const char * a2,struct obj * a3,char *(*a4)(struct obj *),char *(*a5)(struct obj *),const char * a6){logmsg("safeq:%s/%s;",a1,a2);char*p=a4(a3);snprintf(a0,QBUFSZ,"%s%s%s",a1,p,a2);callback();return a0;}
boolean (container_gone)(int (*a0)(struct obj *)){return opts[16];}
struct obj * (unsplitobj)(struct obj * a0){logmsg("unsplit:%d;",oid(a0));return &obj[0];}
void (clear_bypasses)(void){for(int i=0;i<16;i++)obj[i].bypass=0;}
void (add_menu)(winid a0,const glyph_info * a1,const union any * a2,char a3,char a4,int a5,int a6,const char * a7,unsigned int a8){if(opts[36]){int sp=emscripten_stack_get_current();if(!automatic_sp)automatic_sp=sp;logmsg("menu-stack:%d;",sp-automatic_sp);}logmsg("menu:%d:%d/%d/%d/%d:%s:%u;",a0,a3,a4,a5,a6,a7,a8);if(a1)logmsg("glyph:%d/%d;",a1->glyph,a1->ttychar);if(opts[13]&&a2)logmsg("any:%d/%ld;",a2->a_int,(long)a2->a_long);callback();}
int (rn2_on_display_rng)(int a0){return draw(a0,"displayrng");}
void (map_glyphinfo)(coordxy a0,coordxy a1,int a2,unsigned int a3,glyph_info * a4){logmsg("map:%d/%d/%d/%u;",a0,a1,a2,a3);*a4=nul_glyphinfo;a4->glyph=a2;a4->ttychar=opts[15];callback();}
char * (get_strength_str)(void){return "18";}
schar (acurr)(int a0){return opts[18]?opts[18]:10;}
int (select_menu)(winid a0,int a1,menu_item ** a2){logmsg("select:%d/%d;",a0,a1);*a2=0;callback();if(opts[14]>0){*a2=malloc(opts[14]*sizeof **a2);memcpy(*a2,menu+(opts[43]?selectnext++:0),opts[14]*sizeof **a2);}return opts[14];}
void (discover_artifact)(xint16 a0){logmsg("discover_artifact;");callback();}
void (learn_egg_type)(int a0){logmsg("learn_egg_type;");callback();}
int (query_objlist)(const char * a0,struct obj ** a1,int a2,menu_item ** a3,int a4,boolean (*a5)(struct obj *)){logmsg("query:%s/%d/%d;",a0?a0:"NULL",a2,a4);*a3=0;callback();if(opts[14]>0){*a3=malloc(opts[14]*sizeof **a3);memcpy(*a3,menu,opts[14]*sizeof **a3);}return opts[14];}
char * (xname)(struct obj * a0){return objname(a0);}
boolean (suppress_map_output)(void){logmsg("suppress_map_output;");callback();return opts[71];}
int (itemactions)(struct obj * a0){logmsg("itemactions;");callback();return opts[72];}
void (add_menu_str)(winid a0,const char * a1){logmsg("menustr:%d:%s;",a0,a1);callback();}
void (add_menu_heading)(winid a0,const char * a1){logmsg("heading:%d:%s;",a0,a1);callback();}
boolean (get_obj_location)(struct obj * a0,coordxy * a1,coordxy * a2,int a3){*a1=a0->ox;*a2=a0->oy;return !opts[8];}
boolean (costly_spot)(coordxy a0,coordxy a1){logmsg("costly_spot;");callback();return opts[73];}
struct obj * (unknwn_contnr_contents)(struct obj * a0){return opts[22]?a0:0;}
long (unpaid_cost)(struct obj * a0,uchar a1){logmsg("unpaid_cost;");callback();return opts[74];}
char * (distant_name)(struct obj * a0,char *(*a1)(struct obj *)){logmsg("distant:%d;",oid(a0));return a1(a0);}
int (doinvbill)(int a0){logmsg("doinvbill;");callback();return opts[75];}
int (query_category)(const char * a0,struct obj * a1,int a2,menu_item ** a3,int a4){logmsg("category:%s/%d/%d;",a0,a2,a4);*a3=0;callback();if(opts[14]>0){*a3=malloc(opts[14]*sizeof **a3);memcpy(*a3,menu,opts[14]*sizeof **a3);}return opts[14];}
stairway * (stairway_at)(coordxy a0,coordxy a1){return opts[19]?&staircell:0;}
int (is_drawbridge_wall)(coordxy a0,coordxy a1){logmsg("is_drawbridge_wall;");callback();return opts[76];}
boolean (is_lava)(coordxy a0,coordxy a1){logmsg("is_lava;");callback();return opts[77];}
boolean (is_ice)(coordxy a0,coordxy a1){logmsg("is_ice;");callback();return opts[78];}
char * (ice_descr)(coordxy a0,coordxy a1,char * a2){strcpy(a2,"ice");return a2;}
boolean (is_pool)(coordxy a0,coordxy a1){logmsg("is_pool;");callback();return opts[79];}
const char * (a_gname)(void){logmsg("a_gname;");callback();return "controlled";}
const char * (align_str)(aligntyp a0){logmsg("align_str;");callback();return "controlled";}
char * (stairs_description)(stairway * a0,char * a1,boolean a2){strcpy(a1,"stairs");return a1;}
char * (mon_nam)(struct monst * a0){logmsg("mon_nam;");callback();return "controlled";}
const char * (mbodypart)(struct monst * a0,int a1){logmsg("mbodypart;");callback();return "controlled";}
NhRegion * (visible_region_at)(coordxy a0,coordxy a1){return opts[20]?&regioncell:0;}
int (reg_damg)(NhRegion * a0){logmsg("reg_damg;");callback();return opts[84];}
struct trap * (t_at)(coordxy a0,coordxy a1){return opts[21]?&trapcell:0;}
const char * (trapname)(int a0,boolean a1){logmsg("trapname;");callback();return "controlled";}
char * (an)(const char * a0){logmsg("an;");callback();return "controlled";}
boolean (on_level)(d_level * a0,d_level * a1){return a0->dnum==a1->dnum&&a0->dlevel==a1->dlevel;}
schar (db_under_typ)(int a0){logmsg("db_under_typ;");callback();return opts[87];}
void (force_decor)(boolean a0){logmsg("force_decor;");callback();}
const char * (surface)(coordxy a0,coordxy a1){logmsg("surface;");callback();return "controlled";}
char * (vtense)(const char * a0,const char * a1){logmsg("vtense;");callback();return "controlled";}
void (read_engr_at)(coordxy a0,coordxy a1){logmsg("read_engr_at;");callback();}
char * (corpse_xname)(struct obj * a0,const char * a1,unsigned int a2){logmsg("corpse_xname;");callback();return "controlled";}
boolean (poly_when_stoned)(struct permonst * a0){logmsg("poly_when_stoned;");callback();return opts[91];}
char * (doname_with_price)(struct obj * a0){return objname(a0);}
void (hide_unhide_msgtypes)(boolean a0,int a1){logmsg("hide_unhide_msgtypes;");callback();}
char * (killer_xname)(struct obj * a0){return objname(a0);}
void (instapetrify)(const char * a0){logmsg("instapetrify;");callback();}
boolean (erosion_matters)(struct obj * a0){return !opts[28];}
boolean (same_price)(struct obj * a0,struct obj * a1){return !opts[7];}
const char * (safe_oname)(struct obj * a0){return a0->oextra&&a0->oextra->oname?a0->oextra->oname:"";}
long (money_cnt)(struct obj * a0){long n=0;for(struct obj*p=a0;p;p=p->nobj)if(p->oclass==COIN_CLASS)n+=p->quan;return n;}
long (hidden_gold)(boolean a0){logmsg("hidden_gold;");callback();return opts[92];}
void (shopper_financial_report)(void){logmsg("shopper_financial_report;");callback();}
const char * (empty_handed)(void){return "bare hands";}
char * (simpleonames)(struct obj * a0){return objname(a0);}
char * (in_rooms)(coordxy a0,coordxy a1,int a2){logmsg("in_rooms;");callback();return "controlled";}
void (addtobill)(struct obj * a0,boolean a1,boolean a2,boolean a3){logmsg("addtobill;");callback();}
long (stolen_value)(struct obj * a0,coordxy a1,coordxy a2,boolean a3,boolean a4){logmsg("stolen_value;");callback();return opts[94];}
boolean (hideunder)(struct monst * a0){logmsg("hideunder;");callback();return opts[95];}
void (clear_splitobjs)(void){logmsg("clear_splitobjs;");callback();}
char * (noit_Monnam)(struct monst * a0){logmsg("noit_Monnam;");callback();return "controlled";}
boolean (allow_all)(struct obj * a0){return TRUE;}
boolean (is_pool_or_lava)(coordxy a0,coordxy a1){logmsg("is_pool_or_lava;");callback();return opts[97];}
const char * (hliquid)(const char * a0){logmsg("hliquid;");callback();return "controlled";}
boolean (undiscovered_artifact)(xint16 a0){logmsg("undiscovered_artifact;");callback();return opts[99];}
void (docrt)(void){logmsg("docrt;");callback();}
void (set_option_mod_status)(const char * a0,int a1){logmsg("set_option_mod_status;");callback();}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/invent.c"
#define TELEPORT_INVENT_ORIGINAL_INCLUDED 1
#define TELEPORT_INVENT_VALIDATE_ORIGINAL 1
void teleport_invent_inuse_classify(Loot * a0,struct obj * a1){inuse_classify(a0,a1);}
char * teleport_invent_loot_xname(struct obj * a0){return loot_xname(a0);}
int teleport_invent_invletter_value(char a0){return invletter_value(a0);}
int teleport_invent_sortloot_cmp(const void * a0,const void * a1){return sortloot_cmp(a0,a1);}
void teleport_invent_reorder_invent(void){reorder_invent();}
struct obj * teleport_invent_addinv_core0(struct obj * a0,struct obj * a1,boolean a2){return addinv_core0(a0,a1,a2);}
void teleport_invent_compactify(char * a0){compactify(a0);}
boolean teleport_invent_taking_off(const char * a0){return taking_off(a0);}
void teleport_invent_mime_action(const char * a0){mime_action(a0);}
char * teleport_invent_getobj_hands_txt(const char * a0,char * a1){return getobj_hands_txt(a0,a1);}
int teleport_invent_ckvalidcat(struct obj * a0){return ckvalidcat(a0);}
int teleport_invent_ckunpaid(struct obj * a0){return ckunpaid(a0);}
char * teleport_invent_safeq_xprname(struct obj * a0){return safeq_xprname(a0);}
char * teleport_invent_safeq_shortxprname(struct obj * a0){return safeq_shortxprname(a0);}
void teleport_invent_menu_identify(int a0){menu_identify(a0);}
char teleport_invent_obj_to_let(struct obj * a0){return obj_to_let(a0);}
int teleport_invent_dispinv_with_action(char * a0,boolean a1,const char * a2){return dispinv_with_action(a0,a1,a2);}
struct obj * teleport_invent_find_unpaid(struct obj * a0,struct obj ** a1){return find_unpaid(a0,a1);}
char teleport_invent_display_pickinv(const char * a0,const char * a1,const char * a2,boolean a3,boolean a4,long * a5){return display_pickinv(a0,a1,a2,a3,a4,a5);}
char teleport_invent_display_used_invlets(char a0){return display_used_invlets(a0);}
void teleport_invent_dounpaid(int a0,int a1,int a2){dounpaid(a0,a1,a2);}
boolean teleport_invent_this_type_only(struct obj * a0){return this_type_only(a0);}
void teleport_invent_noarmor(boolean a0){noarmor(a0);}
boolean teleport_invent_tool_being_used(struct obj * a0){return tool_being_used(a0);}
int teleport_invent_adjust_ok(struct obj * a0){return adjust_ok(a0);}
int teleport_invent_adjust_gold_ok(struct obj * a0){return adjust_gold_ok(a0);}
int teleport_invent_doorganize_core(struct obj * a0){return doorganize_core(a0);}
void teleport_invent_invdisp_nothing(const char * a0,const char * a1){invdisp_nothing(a0,a1);}
boolean teleport_invent_worn_wield_only(struct obj * a0){return worn_wield_only(a0);}
char * teleport_invent_cinv_doname(struct obj * a0){return cinv_doname(a0);}
char * teleport_invent_cinv_ansimpleoname(struct obj * a0){return cinv_ansimpleoname(a0);}
boolean teleport_invent_only_here(struct obj * a0){return only_here(a0);}
#else
extern void teleport_invent_inuse_classify(Loot * a0,struct obj * a1);
extern char * teleport_invent_loot_xname(struct obj * a0);
extern int teleport_invent_invletter_value(char a0);
extern int teleport_invent_sortloot_cmp(const void * a0,const void * a1);
extern void teleport_invent_reorder_invent(void);
extern struct obj * teleport_invent_addinv_core0(struct obj * a0,struct obj * a1,boolean a2);
extern void teleport_invent_compactify(char * a0);
extern boolean teleport_invent_taking_off(const char * a0);
extern void teleport_invent_mime_action(const char * a0);
extern char * teleport_invent_getobj_hands_txt(const char * a0,char * a1);
extern int teleport_invent_ckvalidcat(struct obj * a0);
extern int teleport_invent_ckunpaid(struct obj * a0);
extern char * teleport_invent_safeq_xprname(struct obj * a0);
extern char * teleport_invent_safeq_shortxprname(struct obj * a0);
extern void teleport_invent_menu_identify(int a0);
extern char teleport_invent_obj_to_let(struct obj * a0);
extern int teleport_invent_dispinv_with_action(char * a0,boolean a1,const char * a2);
extern struct obj * teleport_invent_find_unpaid(struct obj * a0,struct obj ** a1);
extern char teleport_invent_display_pickinv(const char * a0,const char * a1,const char * a2,boolean a3,boolean a4,long * a5);
extern char teleport_invent_display_used_invlets(char a0);
extern void teleport_invent_dounpaid(int a0,int a1,int a2);
extern boolean teleport_invent_this_type_only(struct obj * a0);
extern void teleport_invent_noarmor(boolean a0);
extern boolean teleport_invent_tool_being_used(struct obj * a0);
extern int teleport_invent_adjust_ok(struct obj * a0);
extern int teleport_invent_adjust_gold_ok(struct obj * a0);
extern int teleport_invent_doorganize_core(struct obj * a0);
extern void teleport_invent_invdisp_nothing(const char * a0,const char * a1);
extern boolean teleport_invent_worn_wield_only(struct obj * a0);
extern char * teleport_invent_cinv_doname(struct obj * a0);
extern char * teleport_invent_cinv_ansimpleoname(struct obj * a0);
extern boolean teleport_invent_only_here(struct obj * a0);
#endif
#include "../nethack-c/wasm/tu-fragments/invent-support.c"
long probe_call(int which,long*args){switch(which){
case 0:teleport_invent_inuse_classify((Loot *)args[0],(struct obj *)args[1]);return 0;
case 1:loot_classify((Loot *)args[0],(struct obj *)args[1]);return 0;
case 2:return(long)teleport_invent_loot_xname((struct obj *)args[0]);
case 3:return(long)teleport_invent_invletter_value((char)args[0]);
case 4:return(long)teleport_invent_sortloot_cmp((const void *)args[0],(const void *)args[1]);
case 5:return(long)sortloot((struct obj **)args[0],(unsigned int)args[1],(boolean)args[2],(boolean (*)(struct obj *))args[3]);
case 6:unsortloot((Loot **)args[0]);return 0;
case 7:assigninvlet((struct obj *)args[0]);return 0;
case 8:teleport_invent_reorder_invent();return 0;
case 9:return(long)merge_choice((struct obj *)args[0],(struct obj *)args[1]);
case 10:return(long)merged((struct obj **)args[0],(struct obj **)args[1]);
case 11:addinv_core1((struct obj *)args[0]);return 0;
case 12:addinv_core2((struct obj *)args[0]);return 0;
case 13:return(long)teleport_invent_addinv_core0((struct obj *)args[0],(struct obj *)args[1],(boolean)args[2]);
case 14:return(long)addinv((struct obj *)args[0]);
case 15:return(long)addinv_before((struct obj *)args[0],(struct obj *)args[1]);
case 16:return(long)addinv_nomerge((struct obj *)args[0]);
case 17:carry_obj_effects((struct obj *)args[0]);return 0;
case 18:return(long)hold_another_object((struct obj *)args[0],(const char *)args[1],(const char *)args[2],(const char *)args[3]);
case 19:useupall((struct obj *)args[0]);return 0;
case 20:useup((struct obj *)args[0]);return 0;
case 21:consume_obj_charge((struct obj *)args[0],(boolean)args[1]);return 0;
case 22:freeinv_core((struct obj *)args[0]);return 0;
case 23:freeinv((struct obj *)args[0]);return 0;
case 24:delallobj((coordxy)args[0],(coordxy)args[1]);return 0;
case 25:delobj((struct obj *)args[0]);return 0;
case 26:delobj_core((struct obj *)args[0],(boolean)args[1]);return 0;
case 27:return(long)sobj_at((int)args[0],(coordxy)args[1],(coordxy)args[2]);
case 28:return(long)nxtobj((struct obj *)args[0],(int)args[1],(boolean)args[2]);
case 29:return(long)carrying((int)args[0]);
case 30:return(long)carrying_stoning_corpse();
case 31:return(long)currency((long)args[0]);
case 32:return(long)u_carried_gloves();
case 33:return(long)u_have_novel();
case 34:return(long)o_on((unsigned int)args[0],(struct obj *)args[1]);
case 35:return(long)obj_here((struct obj *)args[0],(coordxy)args[1],(coordxy)args[2]);
case 36:return(long)g_at((coordxy)args[0],(coordxy)args[1]);
case 37:teleport_invent_compactify((char *)args[0]);return 0;
case 38:return(long)splittable((struct obj *)args[0]);
case 39:return(long)teleport_invent_taking_off((const char *)args[0]);
case 40:teleport_invent_mime_action((const char *)args[0]);return 0;
case 41:return(long)any_obj_ok((struct obj *)args[0]);
case 42:return(long)teleport_invent_getobj_hands_txt((const char *)args[0],(char *)args[1]);
case 43:return(long)getobj((const char *)args[0],(int (*)(struct obj *))args[1],(unsigned int)args[2]);
case 44:silly_thing((const char *)args[0],(struct obj *)args[1]);return 0;
case 45:return(long)teleport_invent_ckvalidcat((struct obj *)args[0]);
case 46:return(long)teleport_invent_ckunpaid((struct obj *)args[0]);
case 47:return(long)wearing_armor();
case 48:return(long)is_worn((struct obj *)args[0]);
case 49:return(long)is_inuse((struct obj *)args[0]);
case 50:return(long)teleport_invent_safeq_xprname((struct obj *)args[0]);
case 51:return(long)teleport_invent_safeq_shortxprname((struct obj *)args[0]);
case 52:return(long)ggetobj((const char *)args[0],(int (*)(struct obj *))args[1],(int)args[2],(boolean)args[3],(unsigned int *)args[4]);
case 53:return(long)askchain((struct obj **)args[0],(const char *)args[1],(int)args[2],(int (*)(struct obj *))args[3],(int (*)(struct obj *))args[4],(int)args[5],(const char *)args[6]);
case 54:return(long)reroll_menu();
case 55:set_cknown_lknown((struct obj *)args[0]);return 0;
case 56:fully_identify_obj((struct obj *)args[0]);return 0;
case 57:return(long)identify((struct obj *)args[0]);
case 58:teleport_invent_menu_identify((int)args[0]);return 0;
case 59:return(long)count_unidentified((struct obj *)args[0]);
case 60:identify_pack((int)args[0],(boolean)args[1]);return 0;
case 61:learn_unseen_invent();return 0;
case 62:update_inventory();return 0;
case 63:return(long)doperminv();
case 64:return(long)teleport_invent_obj_to_let((struct obj *)args[0]);
case 65:prinv((const char *)args[0],(struct obj *)args[1],(long)args[2]);return 0;
case 66:return(long)xprname((struct obj *)args[0],(const char *)args[1],(char)args[2],(boolean)args[3],(long)args[4],(long)args[5]);
case 67:return(long)teleport_invent_dispinv_with_action((char *)args[0],(boolean)args[1],(const char *)args[2]);
case 68:return(long)ddoinv();
case 69:return(long)teleport_invent_find_unpaid((struct obj *)args[0],(struct obj **)args[1]);
case 70:free_pickinv_cache();return 0;
case 71:return(long)teleport_invent_display_pickinv((const char *)args[0],(const char *)args[1],(const char *)args[2],(boolean)args[3],(boolean)args[4],(long *)args[5]);
case 72:return(long)display_inventory((const char *)args[0],(boolean)args[1]);
case 73:repopulate_perminvent();return 0;
case 74:return(long)teleport_invent_display_used_invlets((char)args[0]);
case 75:return(long)count_unpaid((struct obj *)args[0]);
case 76:return(long)count_buc((struct obj *)args[0],(int)args[1],(boolean (*)(struct obj *))args[2]);
case 77:tally_BUCX((struct obj *)args[0],(boolean)args[1],(int *)args[2],(int *)args[3],(int *)args[4],(int *)args[5],(int *)args[6],(int *)args[7]);return 0;
case 78:return(long)count_contents((struct obj *)args[0],(boolean)args[1],(boolean)args[2],(boolean)args[3],(boolean)args[4]);
case 79:teleport_invent_dounpaid((int)args[0],(int)args[1],(int)args[2]);return 0;
case 80:return(long)teleport_invent_this_type_only((struct obj *)args[0]);
case 81:return(long)dotypeinv();
case 82:return(long)dfeature_at((coordxy)args[0],(coordxy)args[1],(char *)args[2]);
case 83:return(long)look_here((int)args[0],(unsigned int)args[1]);
case 84:return(long)dolook();
case 85:return(long)will_feel_cockatrice((struct obj *)args[0],(boolean)args[1]);
case 86:feel_cockatrice((struct obj *)args[0],(boolean)args[1]);return 0;
case 87:stackobj((struct obj *)args[0]);return 0;
case 88:return(long)mergable((struct obj *)args[0],(struct obj *)args[1]);
case 89:return(long)doprgold();
case 90:return(long)doprwep();
case 91:teleport_invent_noarmor((boolean)args[0]);return 0;
case 92:return(long)doprarm();
case 93:return(long)doprring();
case 94:return(long)dopramulet();
case 95:return(long)teleport_invent_tool_being_used((struct obj *)args[0]);
case 96:return(long)doprtool();
case 97:return(long)doprinuse();
case 98:useupf((struct obj *)args[0],(long)args[1]);return 0;
case 99:return(long)let_to_name((char)args[0],(boolean)args[1],(boolean)args[2]);
case 100:free_invbuf();return 0;
case 101:reassign();return 0;
case 102:return(long)check_invent_gold((const char *)args[0]);
case 103:return(long)teleport_invent_adjust_ok((struct obj *)args[0]);
case 104:return(long)teleport_invent_adjust_gold_ok((struct obj *)args[0]);
case 105:return(long)doorganize();
case 106:return(long)adjust_split();
case 107:return(long)teleport_invent_doorganize_core((struct obj *)args[0]);
case 108:teleport_invent_invdisp_nothing((const char *)args[0],(const char *)args[1]);return 0;
case 109:return(long)teleport_invent_worn_wield_only((struct obj *)args[0]);
case 110:return(long)display_minventory((struct monst *)args[0],(int)args[1],(char *)args[2]);
case 111:return(long)teleport_invent_cinv_doname((struct obj *)args[0]);
case 112:return(long)teleport_invent_cinv_ansimpleoname((struct obj *)args[0]);
case 113:return(long)display_cinventory((struct obj *)args[0]);
case 114:return(long)teleport_invent_only_here((struct obj *)args[0]);
case 115:return(long)display_binventory((coordxy)args[0],(coordxy)args[1],(boolean)args[2]);
case 116:prepare_perminvent((winid)args[0]);return 0;
case 117:sync_perminvent();return 0;
case 118:perm_invent_toggled((boolean)args[0]);return 0;
default:abort();}}
long probe_invoke(int index){switch(index){
case 0:return(long)((int (*)(struct obj *))teleport_invent_function(0))(&obj[0]);
case 1:return(long)((int (*)(struct obj *))teleport_invent_function(1))(&obj[0]);
case 2:return(long)((boolean (*)(struct obj *))teleport_invent_function(2))(&obj[0]);
case 3:return(long)((char * (*)(struct obj *))teleport_invent_function(3))(&obj[0]);
case 4:return(long)((char * (*)(struct obj *))teleport_invent_function(4))(&obj[0]);
case 5:return(long)((char * (*)(struct obj *))teleport_invent_function(5))(&obj[0]);
case 6:return(long)((int (*)(struct obj *))teleport_invent_function(6))(&obj[0]);
case 7:return(long)((int (*)(struct obj *))teleport_invent_function(7))(&obj[0]);
case 8:return(long)((char * (*)(struct obj *))teleport_invent_function(8))(&obj[0]);
case 9:return(long)((int (*)(struct obj *))teleport_invent_function(9))(&obj[0]);
case 10:return(long)((boolean (*)(struct obj *))teleport_invent_function(10))(&obj[0]);
case 11:return(long)((boolean (*)(struct obj *))teleport_invent_function(11))(&obj[0]);
case 12:return(long)((boolean (*)(struct obj *))teleport_invent_function(12))(&obj[0]);
case 13:return(long)((boolean (*)(struct obj *))teleport_invent_function(13))(&obj[0]);
case 14:return(long)((int (*)(int))teleport_invent_function(14))(13);
case 15:return(long)((char * (*)(struct obj *))teleport_invent_function(15))(&obj[0]);
case 16:return(long)((char * (*)(struct obj *))teleport_invent_function(16))(&obj[0]);
case 17:return(long)((int (*)(const void *,const void *))teleport_invent_function(17))(&loot[0],&loot[1]);
case 18:return(long)((boolean (*)(struct obj *))teleport_invent_function(18))(&obj[0]);
case 19:return(long)((boolean (*)(struct obj *))teleport_invent_function(19))(&obj[0]);
default:abort();}}

int probe_class(int i){return objects[i].oc_class;}
void probe_option(int i,long v){opts[i]=v;}
void probe_clear(void){tracepos=draws=0;tracebuf[0]=0;callerfile=callerowner=0;callerline=automatic_sp=0;}
void probe_reset(void){memset(opts,0,sizeof opts);memset(obj,0,sizeof obj);memset(mon,0,sizeof mon);memset(buffers,0,sizeof buffers);memset(loot,0,sizeof loot);memset(menu,0,sizeof menu);memset(objcell,0,sizeof objcell);memset(longs,0,sizeof longs);memset(&u,0,sizeof u);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&gi,0,sizeof gi);memset(&gc,0,sizeof gc);memset(&go,0,sizeof go);memset(&gt,0,sizeof gt);memset(&svc,0,sizeof svc);memset(&svl,0,sizeof svl);memset(&disp,0,sizeof disp);memset(&program_state,0,sizeof program_state);memset(&backendwri,0,sizeof backendwri);memset(&trapcell,0,sizeof trapcell);memset(&staircell,0,sizeof staircell);memset(&regioncell,0,sizeof regioncell);memset(&zerowri,0,sizeof zerowri);for(int i=0;i<16;i++){obj[i].otyp=DAGGER;obj[i].oclass=WEAPON_CLASS;obj[i].quan=1;obj[i].invlet='a'+i;obj[i].corpsenm=NON_PM;}for(int i=0;i<4;i++)mon[i].data=&mons[PM_HUMAN];gy.youmonst.data=&mons[PM_HUMAN];u.ux=12;u.uy=10;u.uz.dlevel=1;flags.invlet_constant=TRUE;flags.verbose=TRUE;const char order[]={COIN_CLASS,AMULET_CLASS,RING_CLASS,WEAPON_CLASS,ARMOR_CLASS,TOOL_CLASS,FOOD_CLASS,POTION_CLASS,SCROLL_CLASS,SPBOOK_CLASS,WAND_CLASS,GEM_CLASS,ROCK_CLASS,BALL_CLASS,CHAIN_CLASS,VENOM_CLASS,ILLOBJ_CLASS,0};memcpy(flags.inv_order,order,sizeof order);gc.cached_pickinv_win=WIN_ERR;WIN_INVEN=WIN_ERR;WIN_MESSAGE=1;windowprocs.name="controlled";windowprocs.wp_id=wp_tty;windowprocs.wincap=0;windowprocs.win_create_nhwindow=backend_create;windowprocs.win_clear_nhwindow=backend_clear;windowprocs.win_display_nhwindow=backend_display;windowprocs.win_destroy_nhwindow=backend_destroy;windowprocs.win_putstr=backend_put;windowprocs.win_start_menu=backend_start;windowprocs.win_end_menu=backend_end;windowprocs.win_message_menu=backend_message;windowprocs.win_wait_synch=backend_wait;windowprocs.win_putmsghistory=backend_history;windowprocs.win_update_inventory=backend_update;windowprocs.win_ctrl_nhwindow=backend_ctrl;uwep=uswapwep=uquiver=uball=uchain=uarmg=uarm=uarmc=uarmf=uarmh=uarms=uarmu=uright=uleft=uamul=ublindf=uskin=0;qnext=qcount=selectnext=0;heldwri=0;rngstate=1;probe_clear();}
static int obj_ok_cb(struct obj*p){logmsg("obj_ok:%d;",oid(p));callback();return opts[40];}
static boolean filter_cb(struct obj*p){logmsg("filter:%d;",oid(p));callback();return opts[41];}
static int action_cb(struct obj*p){logmsg("action:%d/%ld;",oid(p),p->quan);callback();return opts[42];}
long probe_callback(int kind){return(long)(kind==0?(void*)obj_ok_cb:kind==1?(void*)filter_cb:(void*)action_cb);}
long probe_function(int i){return(long)teleport_invent_function(i);}
long probe_record(int kind,int index){switch(kind){case 0:return(long)&obj[index];case 1:return(long)&mon[index];case 2:return(long)&objcell[index];case 3:return(long)&loot[index];case 4:return(long)&longs[index];case 5:return(long)&menu[index];case 6:return(long)&backendwri;case 7:return(long)&zerowri;case 8:return(long)&anycell;case 9:return(long)&staircell;case 10:return(long)&trapcell;case 11:return(long)&regioncell;default:abort();}}
char*probe_buffer(int i){return buffers[i];}void probe_input(const char*s){snprintf(input,sizeof input,"%s",s);}
long probe_global(int i){return(long)teleport_invent_global(i);}long probe_layout(int i){return(long)teleport_invent_layout(i);}
uint64_t probe_read(int k,void*p,int f){return teleport_invent_read(k,p,f);}void probe_write(int k,void*p,int f,uint64_t v){teleport_invent_write(k,p,f,v);}void*probe_address(int k,void*p,int f){return teleport_invent_address(k,p,f);}
void probe_chain(int from,int to,int field){if(from<0)gi.invent=to<0?0:&obj[to];else if(field==0)obj[from].nobj=to<0?0:&obj[to];else obj[from].cobj=to<0?0:&obj[to];}
void probe_queue(int type,long value){if(qcount==8)abort();memset(&queue[qcount],0,sizeof queue[qcount]);queue[qcount].typ=type;if(type==CMDQ_KEY)queue[qcount].key=value;else queue[qcount].intval=value;qcount++;}
void probe_property(int p,long i,long e){u.uprops[p].intrinsic=i;u.uprops[p].extrinsic=e;}
void probe_foreign(long flags,int marker){invent_foreign_wri(flags,marker);}
static struct observation {void*p;long scalar;unsigned char padding[8];} observed;
void*probe_observe(uint64_t pointer,long scalar){observed.p=(void*)(uintptr_t)pointer;observed.scalar=scalar;memset(observed.padding,0xa5,8);return &observed;}
int probe_offset(int i){return i==0?offsetof(struct observation,p):i==1?offsetof(struct observation,scalar):offsetof(struct observation,padding);}
long probe_held(void){return(long)heldwri;}
const char*probe_trace(void){return tracebuf;}long probe_stack(void){return emscripten_stack_get_current();}
const char*probe_snapshot(void){int n=snprintf(snap,sizeof snap,"invent:%d;weapons:%d/%d/%d;msg:%d;flags:%d/%d/%d/%d;counts:%ld/%ld;state:%d/%d/%d/%d/%d;",oid(gi.invent),oid(uwep),oid(uswapwep),oid(uquiver),iflags.last_msg,flags.sortpack,flags.sortloot,flags.invlet_constant,flags.debug,yn_number,u.uconduct.literate,gc.core_invent_state,gi.in_sync_perminvent,iflags.perm_invent,iflags.perm_invent_pending,WIN_INVEN);for(int i=0;i<16;i++)n+=snprintf(snap+n,sizeof snap-n,"o%d:%d/%d/%d/%ld/%ld/%ld/%d/%d/%d/%d/%d/%d/%d/%d/%d;",i,oid(obj[i].nobj),oid(obj[i].cobj),obj[i].otyp,obj[i].quan,obj[i].age,obj[i].owornmask,obj[i].invlet,obj[i].where,obj[i].known,obj[i].dknown,obj[i].bknown,obj[i].rknown,obj[i].blessed,obj[i].cursed,obj[i].no_charge);for(int i=0;i<8;i++)n+=snprintf(snap+n,sizeof snap-n,"l%d:%ld;",i,longs[i]);return snap;}

