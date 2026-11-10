/* SHK controlled native world; original source included only in reference. */
#include "hack.h"
#include "tu-shk-layout.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <emscripten.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
__typeof__(gi) gi;
__typeof__(disp) disp;
__typeof__(svr) svr;
__typeof__(u) u;
__typeof__(svl) svl;
__typeof__(svp) svp;
__typeof__(gt) gt;
__typeof__(gk) gk;
__typeof__(gm) gm;
__typeof__(gb) gb;
__typeof__(svm) svm;
__typeof__(flags) flags;
__typeof__(gu) gu;
__typeof__(cg) cg;
__typeof__(windowprocs) windowprocs;
__typeof__(nul_glyphinfo) nul_glyphinfo;
__typeof__(gv) gv;
__typeof__(iflags) iflags;
__typeof__(gr) gr;
__typeof__(uball) uball;
__typeof__(uchain) uchain;
__typeof__(ubirthday) ubirthday;
__typeof__(uarmh) uarmh;
__typeof__(uarmu) uarmu;
__typeof__(uarm) uarm;
__typeof__(uarmc) uarmc;
__typeof__(gy) gy;
__typeof__(gs) gs;
__typeof__(ga) ga;
__typeof__(gf) gf;
__typeof__(program_state) program_state;
__typeof__(uswapwep) uswapwep;
__typeof__(gc) gc;

_Static_assert(ROWNO==21&&COLNO==80,"Review SHK native world dimensions");
const struct shclass shtypes[16]={{.name="general store",.symb=RANDOM_CLASS}};
const struct Gender genders[3]={{.he="he",.him="him",.his="his"},{.he="she",.him="her",.his="her"},{.he="it",.him="it",.his="its"}};
const char ynchars[]="yn",ynaqchars[]="ynaq";
const struct c_common_strings c_common_strings={.c_the_your={"the","your"}};
static struct obj obj[32];static struct oextra ox[32];static struct monst mon[4];static struct mextra mx[4];static struct eshk shop[4];static struct trap trapcell;static seenV vision[ROWNO][COLNO];static seenV*visionrows[ROWNO];
static unsigned char billbuf[32*64] __attribute__((aligned(8)));static menu_item menu[32];static struct obj*objcell[8];static long longs[16];static char buffers[8][8192],scratch[8][BUFSZ],input[BUFSZ];
static long opts[256];static char tracebuf[4194304],snap[4194304];static int tracepos,draws,callerline,reenter,autosp,menu_next;static unsigned rngstate;static const char*callerfile,*callerowner;
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);tracepos+=vsnprintf(tracebuf+tracepos,sizeof tracebuf-tracepos,f,ap);va_end(ap);if(tracepos>=sizeof tracebuf-8192)abort();}
static int oid(const struct obj*p){return p>=obj&&p<obj+32?(int)(p-obj)+1:0;}static int mid(const struct monst*p){return p>=mon&&p<mon+4?(int)(p-mon)+1:0;}
EM_JS(void,fixture_throw,(void),{throw new Error('SHK controlled callback');});
static void callback(void){if(opts[30]){opts[30]=0;emscripten_resize_heap(emscripten_get_heap_size()+16777216);}if(opts[31]){opts[31]=0;fixture_throw();}if(opts[32]&&!reenter){reenter=1;logmsg("reentry:%d;",oid_price_adjustment(&obj[0],obj[0].o_id));reenter=0;}}
static void vlog(const char*name,const char*f,va_list ap){logmsg("%s:",name);tracepos+=vsnprintf(tracebuf+tracepos,sizeof tracebuf-tracepos,f,ap);logmsg(";");callback();}

void Norep(const char*f,...){va_list ap;va_start(ap,f);vlog("Norep",f,ap);va_end(ap);}
void There(const char*f,...){va_list ap;va_start(ap,f);vlog("There",f,ap);va_end(ap);}
void You(const char*f,...){va_list ap;va_start(ap,f);vlog("You",f,ap);va_end(ap);}
void You_cant(const char*f,...){va_list ap;va_start(ap,f);vlog("You_cant",f,ap);va_end(ap);}
void You_feel(const char*f,...){va_list ap;va_start(ap,f);vlog("You_feel",f,ap);va_end(ap);}
void You_hear(const char*f,...){va_list ap;va_start(ap,f);vlog("You_hear",f,ap);va_end(ap);}
void Your(const char*f,...){va_list ap;va_start(ap,f);vlog("Your",f,ap);va_end(ap);}
void impossible(const char*f,...){va_list ap;va_start(ap,f);vlog("impossible",f,ap);va_end(ap);}
void livelog_printf(long kind,const char*f,...){va_list ap;logmsg("livelog:%ld;",kind);va_start(ap,f);vlog("live",f,ap);va_end(ap);}
void panic(const char*f,...){va_list ap;va_start(ap,f);vlog("panic",f,ap);va_end(ap);fixture_throw();__builtin_unreachable();}
void pline(const char*f,...){va_list ap;va_start(ap,f);vlog("pline",f,ap);va_end(ap);}
void pline_The(const char*f,...){va_list ap;va_start(ap,f);vlog("pline_The",f,ap);va_end(ap);}
void verbalize(const char*f,...){va_list ap;va_start(ap,f);vlog("verbalize",f,ap);va_end(ap);}

static winid backend_create(int t){logmsg("create:%d;",t);callback();return opts[2]?-1:17;}
static void backend_destroy(winid w){logmsg("destroy:%d;",w);callback();}
static void backend_display(winid w,boolean b){logmsg("display:%d/%d;",w,b);callback();}
static void backend_put(winid w,int attr,const char*s){if(opts[36]){int sp=emscripten_stack_get_current();if(!autosp)autosp=sp;logmsg("stack:%d;",sp-autosp);}logmsg("put:%d/%d:%s;",w,attr,s);callback();}
static void backend_start(winid w,unsigned long f){logmsg("start:%d/%lu;",w,f);callback();}
static void backend_end(winid w,const char*s){logmsg("end:%d:%s;",w,s?s:"NULL");callback();}
static void backend_sync(void){logmsg("sync;");callback();}
static void extract(struct obj*o){if(o->where==OBJ_CONTAINED&&o->ocontainer){struct obj**p=&o->ocontainer->cobj;while(*p){if(*p==o){*p=o->nobj;break;}p=&(*p)->nobj;}}struct obj**lists[]={&gi.invent,&svl.level.objlist,&svl.level.buriedobjlist,&gm.migrating_objs,&mon[0].minvent,&mon[1].minvent,&mon[2].minvent,&mon[3].minvent};for(unsigned i=0;i<sizeof lists/sizeof lists[0];i++)for(struct obj**p=lists[i];*p;p=&(*p)->nobj)if(*p==o){*p=o->nobj;goto done;}done:if(o->where==OBJ_FLOOR&&isok(o->ox,o->oy)){struct obj**p=&svl.level.objects[o->ox][o->oy];while(*p){if(*p==o){*p=o->nexthere;break;}p=&(*p)->nexthere;}}o->nobj=0;o->nexthere=0;o->where=OBJ_FREE;}
static struct obj*findid(unsigned id,struct obj*p){for(;p;p=p->nobj){if(p->o_id==id)return p;struct obj*q=findid(id,p->cobj);if(q)return q;}return 0;}
static char*objname(struct obj*p){snprintf(scratch[0],BUFSZ,"object%d[%ld:%d/%d]",p?p->otyp:-1,p?p->quan:0,p?p->unpaid:0,p?p->where:0);callback();return scratch[0];}
static char*monname(struct monst*p){snprintf(scratch[1],BUFSZ,"shopkeeper%d",mid(p));callback();return scratch[1];}
static int draw(int n,const char*which){if(n<=0)abort();rngstate=rngstate*1664525U+1013904223U;int v=(rngstate>>1)%(unsigned)n;logmsg("%s:%d/%d:%s:%d:%s;",which,n,v,callerfile?callerfile:"NULL",callerline,callerowner?callerowner:"NULL");draws++;callback();return v;}

struct obj * (findgold)(struct obj * a0){for(;a0;a0=a0->nobj)if(a0->oclass==COIN_CLASS)return a0;return 0;}
struct obj * (splitobj)(struct obj * a0,long a1){logmsg("split:%d/%ld;",oid(a0),a1);obj[31]=*a0;obj[31].quan=a1;obj[31].o_id=32;a0->quan-=a1;obj[31].nobj=a0->nobj;a0->nobj=&obj[31];return &obj[31];}
void (remove_worn_item)(struct obj * a0,boolean a1){a0->owornmask=0;}
void (freeinv)(struct obj * a0){logmsg("freeinv:%d;",oid(a0));extract(a0);callback();}
int (add_to_minv)(struct monst * a0,struct obj * a1){logmsg("add_minv:%d/%d;",mid(a0),oid(a1));a1->nobj=a0->minvent;a0->minvent=a1;a1->where=OBJ_MINVENT;a1->ocarry=a0;return 0;}
char * (a_monnam)(struct monst * a0){return monname(a0);}
void (obj_extract_self)(struct obj * a0){logmsg("extract:%d;",oid(a0));extract(a0);callback();}
struct obj * (merge_choice)(struct obj * a0,struct obj * a1){return opts[4]?a0:0;}
int (inv_cnt)(boolean a0){int n=0;for(struct obj*p=gi.invent;p;p=p->nobj)if(a0||p->oclass!=COIN_CLASS)n++;return n;}
void (dropy)(struct obj * a0){logmsg("dropy:%d;",oid(a0));a0->where=OBJ_FLOOR;}
struct obj * (addinv)(struct obj * a0){logmsg("addinv:%d;",oid(a0));a0->nobj=gi.invent;gi.invent=a0;a0->where=OBJ_INVENT;return a0;}
boolean (on_level)(d_level * a0,d_level * a1){return a0->dnum==a1->dnum&&a0->dlevel==a1->dlevel;}
struct mkroom * (search_special)(schar a0){return opts[5]?&svr.rooms[0]:0;}
void (assign_level)(d_level * a0,d_level * a1){*a0=*a1;}
boolean (get_obj_location)(struct obj * a0,coordxy * a1,coordxy * a2,int a3){*a1=a0->ox;*a2=a0->oy;return !opts[6];}
int (isok)(coordxy a0,coordxy a1){return a0>0&&a0<COLNO&&a1>=0&&a1<ROWNO;}
void (dealloc_obj)(struct obj * a0){logmsg("dealloc:%d;",oid(a0));a0->where=OBJ_FREE;callback();}
boolean (angry_guards)(boolean a0){logmsg("angry_guards;");callback();return opts[60];}
void (choose_stairs)(coordxy * a0,coordxy * a1,boolean a2){logmsg("stairs:%d;",a2);*a0=12;*a1=10;callback();}
char * (Shknam)(struct monst * a0){return monname(a0);}
const char * (currency)(long a0){logmsg("currency:%ld;",a0);return a0==1?"zorkmid":"zorkmids";}
char * (in_rooms)(coordxy a0,coordxy a1,int a2){static char room[3];room[0]=opts[7]?0:ROOMOFFSET;room[1]=opts[43]?ROOMOFFSET+1:0;room[2]=0;return room;}
char * (shkname)(struct monst * a0){return monname(a0);}
void (adjalign)(int a0){logmsg("adjalign;");callback();}
int (sensemon)(struct monst * a0){logmsg("sensemon;");callback();return opts[61];}
int (canseemon)(struct monst * a0){logmsg("canseemon;");callback();return opts[62];}
void (record_achievement)(schar a0){logmsg("record_achievement;");callback();}
int (pronoun_gender)(struct monst * a0,unsigned int a1){return opts[8];}
boolean (rng_log_enabled)(void){return !opts[9];}
void (rng_log_set_caller)(const char * a0,int a1,const char * a2){callerfile=a0;callerline=a1;callerowner=a2;}
int (rn2)(int a0){return draw(a0,"rng");}
const char * (mbodypart)(struct monst * a0,int a1){return "head";}
void (set_voice)(struct monst * a0,int32_t a1,int32_t a2,int32_t a3){logmsg("set_voice;");callback();}
const char * (Hello)(struct monst * a0){return "Hello";}
struct obj * (carrying)(int a0){for(struct obj*p=gi.invent;p;p=p->nobj)if(p->otyp==a0)return p;return 0;}
void (discover_object)(int a0,boolean a1,boolean a2,boolean a3){logmsg("discover_object;");callback();}
char * (y_monnam)(struct monst * a0){return monname(a0);}
struct obj * (sobj_at)(int a0,coordxy a1,coordxy a2){for(struct obj*p=svl.level.objects[a1][a2];p;p=p->nexthere)if(p->otyp==a0)return p;return 0;}
int (dochug)(struct monst * a0){logmsg("dochug;");callback();return opts[63];}
void (wake_nearto)(coordxy a0,coordxy a1,int a2){logmsg("wake_nearto;");callback();}
int (count_unpaid)(struct obj * a0){int n=0;for(;a0;a0=a0->nobj)n+=a0->unpaid;return n;}
void (o_unleash)(struct obj * a0){logmsg("o_unleash;");callback();}
void (food_disappears)(struct obj * a0){logmsg("food_disappears;");callback();}
void (book_disappears)(struct obj * a0){logmsg("book_disappears;");callback();}
void (maybe_reset_pick)(struct obj * a0){logmsg("maybe_reset_pick;");callback();}
void (setnotworn)(struct obj * a0){a0->owornmask=0;}
int (mnearto)(struct monst * a0,coordxy a1,coordxy a2,boolean a3,unsigned int a4){logmsg("mnear:%d/%d/%d;",mid(a0),a1,a2);a0->mx=a1;a0->my=a2;return opts[10];}
void (pacify_guards)(void){logmsg("pacify_guards;");callback();}
void (mdrop_special_objs)(struct monst * a0){logmsg("mdrop_special_objs;");callback();}
xint16 (ledger_no)(d_level * a0){logmsg("ledger_no;");callback();return opts[64];}
void (migrate_to_level)(struct monst * a0,xint16 a1,xint16 a2,coord * a3){logmsg("migrate:%d/%d/%d;",mid(a0),a1,a2);callback();}
long * (alloc)(unsigned int a0){logmsg("alloc:%u;",a0);return malloc(a0);}
void (add_menu_heading)(winid a0,const char * a1){logmsg("heading:%d:%s;",a0,a1);callback();}
char * (paydoname)(struct obj * a0){return objname(a0);}
void (add_menu)(winid a0,const glyph_info * a1,const union any * a2,char a3,char a4,int a5,int a6,const char * a7,unsigned int a8){logmsg("menu:%d:%d/%d/%d/%d/%d:%s:%u;",a0,a2?a2->a_int:0,a3,a4,a5,a6,a7,a8);callback();}
int (select_menu)(winid a0,int a1,menu_item ** a2){logmsg("select:%d/%d;",a0,a1);*a2=0;callback();if(opts[11]>0){*a2=malloc(opts[11]*sizeof **a2);memcpy(*a2,menu,opts[11]*sizeof **a2);}return opts[11];}
long (hidden_gold)(boolean a0){logmsg("hidden_gold;");callback();return opts[65];}
int (getpos)(coord * a0,boolean a1,const char * a2){logmsg("getpos:%d/%d:%s;",a0->x,a0->y,a2);a0->x=opts[12]?opts[12]:12;a0->y=opts[13]?opts[13]:10;callback();return opts[14];}
char * (Monnam)(struct monst * a0){return monname(a0);}
boolean (debugcore)(const char * a0,boolean a1){logmsg("debug:%s/%d;",a0,a1);callback();return opts[15];}
long (money_cnt)(struct obj * a0){long n=0;for(;a0;a0=a0->nobj)if(a0->oclass==COIN_CLASS)n+=a0->quan;return n;}
char * (x_monnam)(struct monst * a0,int a1,const char * a2,int a3,boolean a4){return monname(a0);}
void (update_inventory)(void){logmsg("update_inventory;");callback();}
char (yn_function)(const char * a0,const char * a1,char a2,boolean a3){logmsg("yn:%s:%s/%d/%d;",a0,a1?a1:"NULL",a2,a3);callback();return opts[16]?opts[16]:a2;}
char * (simpleonames)(struct obj * a0){return objname(a0);}
void (bot)(void){logmsg("bot;");callback();}
char * (Doname2)(struct obj * a0){return objname(a0);}
char * (doname)(struct obj * a0){return objname(a0);}
char * (ansimpleoname)(struct obj * a0){return objname(a0);}
char * (safe_qbuf)(char * a0,const char * a1,const char * a2,struct obj * a3,char *(*a4)(struct obj *),char *(*a5)(struct obj *),const char * a6){logmsg("safeq:%s/%s;",a1,a2);char*name=a4(a3);snprintf(scratch[4],BUFSZ,"%s%s%s",a1,name,a2);strcpy(a0,scratch[4]);callback();return a0;}
char * (thesimpleoname)(struct obj * a0){return objname(a0);}
void (mongone)(struct monst * a0){logmsg("mongone;");callback();}
void (unleash_all)(void){logmsg("unleash_all;");callback();}
void (drop_upon_death)(struct monst * a0,struct obj * a1,coordxy a2,coordxy a3){logmsg("drop_upon_death;");callback();}
struct obj * (o_on)(unsigned int a0,struct obj * a1){return findid(a0,a1);}
int (weight)(struct obj * a0){return a0->quan;}
schar (acurr)(int a0){logmsg("acurr;");callback();return opts[66];}
boolean (saleable)(struct monst * a0,struct obj * a1){return !opts[17];}
boolean (is_izchak)(struct monst * a0,boolean a1){return opts[18];}
void (newomid)(struct obj * a0){if(!a0->oextra)a0->oextra=&ox[oid(a0)-1];a0->oextra->omid=0;}
void (obj_stop_timers)(struct obj * a0){logmsg("stop:%d;",oid(a0));a0->timed=0;}
void (observe_object)(struct obj * a0){logmsg("observe:%d;",oid(a0));a0->dknown=1;callback();}
char * (xname)(struct obj * a0){return objname(a0);}
char * (the)(const char * a0){snprintf(scratch[6],BUFSZ,"the %s",a0);return scratch[6];}
char * (The)(const char * a0){snprintf(scratch[6],BUFSZ,"The %s",a0);return scratch[6];}
unsigned int (next_ident)(void){return 99;}
long (count_contents)(struct obj * a0,boolean a1,boolean a2,boolean a3,boolean a4){long n=0;for(struct obj*p=a0->cobj;p;p=p->nobj)n+=a2?p->quan:1;return n;}
char * (xprname)(struct obj * a0,const char * a1,char a2,boolean a3,long a4,long a5){snprintf(scratch[3],BUFSZ,"%c:%s:%ld/%ld",a2,a1?a1:objname(a0),a4,a5);return scratch[3];}
int (intrinsic_possible)(int a0,struct permonst * a1){logmsg("intrinsic:%d;",a0);callback();return opts[19];}
long (arti_cost)(struct obj * a0){logmsg("arti_cost;");callback();return opts[67];}
void (map_invisible)(coordxy a0,coordxy a1){logmsg("map_invisible;");callback();}
int (mpickobj)(struct monst * a0,struct obj * a1){logmsg("pickobj:%d/%d;",mid(a0),oid(a1));a1->nobj=a0->minvent;a0->minvent=a1;a1->where=OBJ_MINVENT;a1->ocarry=a0;return 0;}
struct trap * (t_at)(coordxy a0,coordxy a1){return opts[20]?&trapcell:0;}
void (unplacebc)(void){logmsg("unplacebc;");callback();}
void (placebc)(void){logmsg("placebc;");callback();}
void (remove_object)(struct obj * a0){extract(a0);}
void (place_object)(struct obj * a0,coordxy a1,coordxy a2){a0->nobj=fobj;fobj=a0;a0->ox=a1;a0->oy=a2;a0->where=OBJ_FLOOR;a0->nexthere=svl.level.objects[a1][a2];svl.level.objects[a1][a2]=a0;}
void (newsym)(coordxy a0,coordxy a1){logmsg("newsym;");callback();}
struct obj * (mksobj)(int a0,boolean a1,boolean a2){obj[30].otyp=a0;obj[30].oclass=objects[a0].oc_class;obj[30].quan=1;return &obj[30];}
const char * (trapname)(int a0,boolean a1){logmsg("trapname;");callback();return "controlled";}
void (deltrap)(struct trap * a0){trapcell.ttyp=0;}
void (del_engr_at)(coordxy a0,coordxy a1){logmsg("del_engr_at;");callback();}
boolean (closed_door)(coordxy a0,coordxy a1){logmsg("closed_door;");callback();return opts[69];}
boolean (picking_at)(coordxy a0,coordxy a1){logmsg("picking_at;");callback();return opts[70];}
void (block_point)(int a0,int a1){logmsg("block_point;");callback();}
void (stop_occupation)(void){logmsg("stop_occupation;");callback();}
boolean (resist_conflict)(struct monst * a0){logmsg("resist_conflict;");callback();return opts[71];}
int (mattacku)(struct monst * a0){logmsg("mattacku;");callback();return opts[72];}
int (holetime)(void){logmsg("holetime;");callback();return opts[73];}
int (move_special)(struct monst * a0,boolean a1,schar a2,boolean a3,boolean a4,coordxy a5,coordxy a6,coordxy a7,coordxy a8){logmsg("move_special;");callback();return opts[74];}
void (check_special_room)(boolean a0){logmsg("check_special_room;");callback();}
boolean (um_dist)(coordxy a0,coordxy a1,xint16 a2){logmsg("um_dist;");callback();return opts[75];}
void (mnexto)(struct monst * a0,unsigned int a1){logmsg("mnexto;");callback();}
void (growl)(struct monst * a0){logmsg("growl;");callback();}
const char * (locomotion)(const struct permonst * a0,const char * a1){return a1;}
char * (makeplural)(const char * a0){snprintf(scratch[5],BUFSZ,"%ss",a0);return scratch[5];}
schar (depth)(d_level * a0){logmsg("depth;");callback();return opts[76];}
int (rnd)(int a0){return draw(a0,"rnd")+1;}
boolean (enexto)(coord * a0,coordxy a1,coordxy a2,struct permonst * a3){logmsg("enexto:%d/%d;",a1,a2);a0->x=a1+1;a0->y=a2;callback();return !opts[21];}
struct monst * (makemon)(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){logmsg("makemon:%d/%d/%d/%u;",(int)(a0-mons),a1,a2,a3);callback();return opts[22]?0:&mon[3];}
void (yelp)(struct monst * a0){logmsg("yelp;");callback();}
unsigned int (sleep)(unsigned int a0){logmsg("sleep:%u;",a0);callback();return 0;}
const char * (body_part)(int a0){return "hand";}
void (exercise)(int a0,boolean a1){logmsg("exercise;");callback();}
boolean (the_unique_pm)(struct permonst * a0){logmsg("the_unique_pm;");callback();return opts[77];}
int (poly_gender)(void){logmsg("poly_gender;");callback();return opts[78];}
char * (mon_nam)(struct monst * a0){return monname(a0);}
char * (obj_typename)(int a0){logmsg("obj_typename;");callback();return "controlled";}
void (bill_dummy_object)(struct obj * a0){logmsg("bill_dummy_object;");callback();}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/shk.c"
#define TELEPORT_SHK_ORIGINAL_INCLUDED 1
#define TELEPORT_SHK_VALIDATE_ORIGINAL 1
struct monst * teleport_shk_next_shkp(struct monst * a0,boolean a1){return next_shkp(a0,a1);}
void teleport_shk_clear_unpaid_obj(struct monst * a0,struct obj * a1){clear_unpaid_obj(a0,a1);}
void teleport_shk_clear_unpaid(struct monst * a0,struct obj * a1){clear_unpaid(a0,a1);}
void teleport_shk_clear_no_charge_obj(struct monst * a0,struct obj * a1){clear_no_charge_obj(a0,a1);}
void teleport_shk_clear_no_charge(struct monst * a0,struct obj * a1){clear_no_charge(a0,a1);}
void teleport_shk_clear_no_charge_pets(struct monst * a0){clear_no_charge_pets(a0);}
long teleport_shk_addupbill(struct monst * a0){return addupbill(a0);}
void teleport_shk_call_kops(struct monst * a0,boolean a1){call_kops(a0,a1);}
boolean teleport_shk_rob_shop(struct monst * a0){return rob_shop(a0);}
void teleport_shk_deserted_shop(char * a0){deserted_shop(a0);}
long teleport_shk_shop_debt(struct eshk * a0){return shop_debt(a0);}
struct bill_x * teleport_shk_onbill(struct obj * a0,struct monst * a1,boolean a2){return onbill(a0,a1,a2);}
long teleport_shk_check_credit(long a0,struct monst * a1){return check_credit(a0,a1);}
void teleport_shk_pay(long a0,struct monst * a1){pay(a0,a1);}
void teleport_shk_home_shk(struct monst * a0,boolean a1){home_shk(a0,a1);}
boolean teleport_shk_angry_shk_exists(void){return angry_shk_exists();}
void teleport_shk_pacify_shk(struct monst * a0,boolean a1){pacify_shk(a0,a1);}
void teleport_shk_rile_shk(struct monst * a0){rile_shk(a0);}
void teleport_shk_rouse_shk(struct monst * a0,boolean a1){rouse_shk(a0,a1);}
int teleport_shk_sortbill_cmp(const void * a0,const void * a1){return sortbill_cmp(a0,a1);}
long teleport_shk_cheapest_item(int a0,Bill * a1){return cheapest_item(a0,a1);}
int teleport_shk_make_itemized_bill(struct monst * a0,Bill ** a1){return make_itemized_bill(a0,a1);}
int teleport_shk_menu_pick_pay_items(int a0,Bill * a1){return menu_pick_pay_items(a0,a1);}
boolean teleport_shk_pay_billed_items(struct monst * a0,int a1,Bill * a2,boolean a3,boolean * a4){return pay_billed_items(a0,a1,a2,a3,a4);}
void teleport_shk_update_bill(int a0,int a1,Bill * a2,struct eshk * a3,struct bill_x * a4,struct obj * a5){update_bill(a0,a1,a2,a3,a4,a5);}
int teleport_shk_dopayobj(struct monst * a0,struct bill_x * a1,struct obj * a2,int a3,boolean a4,boolean a5){return dopayobj(a0,a1,a2,a3,a4,a5);}
int teleport_shk_buy_container(struct monst * a0,int a1,int a2,Bill * a3){return buy_container(a0,a1,a2,a3);}
void teleport_shk_reject_purchase(struct monst * a0,struct obj * a1,long a2){reject_purchase(a0,a1,a2);}
boolean teleport_shk_insufficient_funds(struct monst * a0,struct obj * a1,long a2){return insufficient_funds(a0,a1,a2);}
boolean teleport_shk_inherits(struct monst * a0,int a1,int a2,boolean a3){return inherits(a0,a1,a2,a3);}
void teleport_shk_set_repo_loc(struct monst * a0){set_repo_loc(a0);}
struct obj * teleport_shk_bp_to_obj(struct bill_x * a0){return bp_to_obj(a0);}
long teleport_shk_get_pricing_units(struct obj * a0){return get_pricing_units(a0);}
long teleport_shk_get_cost(struct obj * a0,struct monst * a1){return get_cost(a0,a1);}
void teleport_shk_dropped_container(struct obj * a0,struct monst * a1,boolean a2){dropped_container(a0,a1,a2);}
boolean teleport_shk_special_stock(struct obj * a0,struct monst * a1,boolean a2){return special_stock(a0,a1,a2);}
long teleport_shk_set_cost(struct obj * a0,struct monst * a1){return set_cost(a0,a1);}
void teleport_shk_add_one_tobill(struct obj * a0,boolean a1,struct monst * a2){add_one_tobill(a0,a1,a2);}
void teleport_shk_add_to_billobjs(struct obj * a0){add_to_billobjs(a0);}
void teleport_shk_bill_box_content(struct obj * a0,boolean a1,boolean a2,struct monst * a3){bill_box_content(a0,a1,a2,a3);}
void teleport_shk_shk_names_obj(struct monst * a0,struct obj * a1,const char * a2,long a3,const char * a4){shk_names_obj(a0,a1,a2,a3,a4);}
void teleport_shk_append_honorific(char * a0){append_honorific(a0);}
void teleport_shk_sub_one_frombill(struct obj * a0,struct monst * a1){sub_one_frombill(a0,a1);}
long teleport_shk_stolen_container(struct obj * a0,struct monst * a1,long a2,boolean a3){return stolen_container(a0,a1,a2,a3);}
long teleport_shk_corpsenm_price_adj(struct obj * a0){return corpsenm_price_adj(a0);}
long teleport_shk_getprice(struct obj * a0,boolean a1){return getprice(a0,a1);}
boolean teleport_shk_shk_impaired(struct monst * a0){return shk_impaired(a0);}
boolean teleport_shk_repairable_damage(struct damage * a0,struct monst * a1){return repairable_damage(a0,a1);}
struct damage * teleport_shk_find_damage(struct monst * a0){return find_damage(a0);}
void teleport_shk_discard_damage_struct(struct damage * a0){discard_damage_struct(a0);}
void teleport_shk_discard_damage_owned_by(struct monst * a0){discard_damage_owned_by(a0);}
void teleport_shk_shk_fixes_damage(struct monst * a0){shk_fixes_damage(a0);}
uint8 teleport_shk_litter_getpos(uint8 * a0,coordxy a1,coordxy a2,struct monst * a3){return litter_getpos(a0,a1,a2,a3);}
void teleport_shk_litter_scatter(uint8 * a0,coordxy a1,coordxy a2,struct monst * a3){litter_scatter(a0,a1,a2,a3);}
void teleport_shk_litter_newsyms(uint8 * a0,coordxy a1,coordxy a2){litter_newsyms(a0,a1,a2);}
int teleport_shk_repair_damage(struct monst * a0,struct damage * a1,boolean a2){return repair_damage(a0,a1,a2);}
void teleport_shk_makekops(coord * a0){makekops(a0);}
void teleport_shk_getcad(struct monst * a0,const char * a1,coordxy a2,coordxy a3,boolean a4,boolean a5,boolean a6){getcad(a0,a1,a2,a3,a4,a5,a6);}
const char * teleport_shk_shk_embellish(struct obj * a0,long a1){return shk_embellish(a0,a1);}
void teleport_shk_kops_gone(boolean a0){kops_gone(a0);}
long teleport_shk_cost_per_charge(struct monst * a0,struct obj * a1,boolean a2){return cost_per_charge(a0,a1,a2);}
char * teleport_shk_shk_owns(char * a0,struct obj * a1){return shk_owns(a0,a1);}
char * teleport_shk_mon_owns(char * a0,struct obj * a1){return mon_owns(a0,a1);}
const char * teleport_shk_cad(boolean a0){return cad(a0);}
#else
#include "../nethack-c/wasm/tu-fragments/shk-types.h"
extern struct monst * teleport_shk_next_shkp(struct monst * a0,boolean a1);
extern void teleport_shk_clear_unpaid_obj(struct monst * a0,struct obj * a1);
extern void teleport_shk_clear_unpaid(struct monst * a0,struct obj * a1);
extern void teleport_shk_clear_no_charge_obj(struct monst * a0,struct obj * a1);
extern void teleport_shk_clear_no_charge(struct monst * a0,struct obj * a1);
extern void teleport_shk_clear_no_charge_pets(struct monst * a0);
extern long teleport_shk_addupbill(struct monst * a0);
extern void teleport_shk_call_kops(struct monst * a0,boolean a1);
extern boolean teleport_shk_rob_shop(struct monst * a0);
extern void teleport_shk_deserted_shop(char * a0);
extern long teleport_shk_shop_debt(struct eshk * a0);
extern struct bill_x * teleport_shk_onbill(struct obj * a0,struct monst * a1,boolean a2);
extern long teleport_shk_check_credit(long a0,struct monst * a1);
extern void teleport_shk_pay(long a0,struct monst * a1);
extern void teleport_shk_home_shk(struct monst * a0,boolean a1);
extern boolean teleport_shk_angry_shk_exists(void);
extern void teleport_shk_pacify_shk(struct monst * a0,boolean a1);
extern void teleport_shk_rile_shk(struct monst * a0);
extern void teleport_shk_rouse_shk(struct monst * a0,boolean a1);
extern int teleport_shk_sortbill_cmp(const void * a0,const void * a1);
extern long teleport_shk_cheapest_item(int a0,Bill * a1);
extern int teleport_shk_make_itemized_bill(struct monst * a0,Bill ** a1);
extern int teleport_shk_menu_pick_pay_items(int a0,Bill * a1);
extern boolean teleport_shk_pay_billed_items(struct monst * a0,int a1,Bill * a2,boolean a3,boolean * a4);
extern void teleport_shk_update_bill(int a0,int a1,Bill * a2,struct eshk * a3,struct bill_x * a4,struct obj * a5);
extern int teleport_shk_dopayobj(struct monst * a0,struct bill_x * a1,struct obj * a2,int a3,boolean a4,boolean a5);
extern int teleport_shk_buy_container(struct monst * a0,int a1,int a2,Bill * a3);
extern void teleport_shk_reject_purchase(struct monst * a0,struct obj * a1,long a2);
extern boolean teleport_shk_insufficient_funds(struct monst * a0,struct obj * a1,long a2);
extern boolean teleport_shk_inherits(struct monst * a0,int a1,int a2,boolean a3);
extern void teleport_shk_set_repo_loc(struct monst * a0);
extern struct obj * teleport_shk_bp_to_obj(struct bill_x * a0);
extern long teleport_shk_get_pricing_units(struct obj * a0);
extern long teleport_shk_get_cost(struct obj * a0,struct monst * a1);
extern void teleport_shk_dropped_container(struct obj * a0,struct monst * a1,boolean a2);
extern boolean teleport_shk_special_stock(struct obj * a0,struct monst * a1,boolean a2);
extern long teleport_shk_set_cost(struct obj * a0,struct monst * a1);
extern void teleport_shk_add_one_tobill(struct obj * a0,boolean a1,struct monst * a2);
extern void teleport_shk_add_to_billobjs(struct obj * a0);
extern void teleport_shk_bill_box_content(struct obj * a0,boolean a1,boolean a2,struct monst * a3);
extern void teleport_shk_shk_names_obj(struct monst * a0,struct obj * a1,const char * a2,long a3,const char * a4);
extern void teleport_shk_append_honorific(char * a0);
extern void teleport_shk_sub_one_frombill(struct obj * a0,struct monst * a1);
extern long teleport_shk_stolen_container(struct obj * a0,struct monst * a1,long a2,boolean a3);
extern long teleport_shk_corpsenm_price_adj(struct obj * a0);
extern long teleport_shk_getprice(struct obj * a0,boolean a1);
extern boolean teleport_shk_shk_impaired(struct monst * a0);
extern boolean teleport_shk_repairable_damage(struct damage * a0,struct monst * a1);
extern struct damage * teleport_shk_find_damage(struct monst * a0);
extern void teleport_shk_discard_damage_struct(struct damage * a0);
extern void teleport_shk_discard_damage_owned_by(struct monst * a0);
extern void teleport_shk_shk_fixes_damage(struct monst * a0);
extern uint8 teleport_shk_litter_getpos(uint8 * a0,coordxy a1,coordxy a2,struct monst * a3);
extern void teleport_shk_litter_scatter(uint8 * a0,coordxy a1,coordxy a2,struct monst * a3);
extern void teleport_shk_litter_newsyms(uint8 * a0,coordxy a1,coordxy a2);
extern int teleport_shk_repair_damage(struct monst * a0,struct damage * a1,boolean a2);
extern void teleport_shk_makekops(coord * a0);
extern void teleport_shk_getcad(struct monst * a0,const char * a1,coordxy a2,coordxy a3,boolean a4,boolean a5,boolean a6);
extern const char * teleport_shk_shk_embellish(struct obj * a0,long a1);
extern void teleport_shk_kops_gone(boolean a0);
extern long teleport_shk_cost_per_charge(struct monst * a0,struct obj * a1,boolean a2);
extern char * teleport_shk_shk_owns(char * a0,struct obj * a1);
extern char * teleport_shk_mon_owns(char * a0,struct obj * a1);
extern const char * teleport_shk_cad(boolean a0);
#endif
#include "../nethack-c/wasm/tu-fragments/shk-support.c"
long probe_call(int which,long*args){switch(which){
case 0:return(long)money2mon((struct monst *)args[0],(long)args[1]);
case 1:money2u((struct monst *)args[0],(long)args[1]);return 0;
case 2:return(long)teleport_shk_next_shkp((struct monst *)args[0],(boolean)args[1]);
case 3:shkgone((struct monst *)args[0]);return 0;
case 4:set_residency((struct monst *)args[0],(boolean)args[1]);return 0;
case 5:replshk((struct monst *)args[0],(struct monst *)args[1]);return 0;
case 6:restshk((struct monst *)args[0],(boolean)args[1]);return 0;
case 7:teleport_shk_clear_unpaid_obj((struct monst *)args[0],(struct obj *)args[1]);return 0;
case 8:teleport_shk_clear_unpaid((struct monst *)args[0],(struct obj *)args[1]);return 0;
case 9:teleport_shk_clear_no_charge_obj((struct monst *)args[0],(struct obj *)args[1]);return 0;
case 10:teleport_shk_clear_no_charge((struct monst *)args[0],(struct obj *)args[1]);return 0;
case 11:teleport_shk_clear_no_charge_pets((struct monst *)args[0]);return 0;
case 12:setpaid((struct monst *)args[0]);return 0;
case 13:record_price_quote((int)args[0],(unsigned long)args[1],(boolean)args[2]);return 0;
case 14:append_price_quote((char *)args[0],(char **)args[1],(int)args[2]);return 0;
case 15:return(long)teleport_shk_addupbill((struct monst *)args[0]);
case 16:teleport_shk_call_kops((struct monst *)args[0],(boolean)args[1]);return 0;
case 17:return(long)inside_shop((coordxy)args[0],(coordxy)args[1]);
case 18:u_left_shop((char *)args[0],(boolean)args[1]);return 0;
case 19:credit_report((struct monst *)args[0],(int)args[1],(boolean)args[2]);return 0;
case 20:remote_burglary((coordxy)args[0],(coordxy)args[1]);return 0;
case 21:return(long)teleport_shk_rob_shop((struct monst *)args[0]);
case 22:teleport_shk_deserted_shop((char *)args[0]);return 0;
case 23:u_entered_shop((char *)args[0]);return 0;
case 24:pick_pick((struct obj *)args[0]);return 0;
case 25:return(long)same_price((struct obj *)args[0],(struct obj *)args[1]);
case 26:return(long)teleport_shk_shop_debt((struct eshk *)args[0]);
case 27:shopper_financial_report();return 0;
case 28:return(long)inhishop((struct monst *)args[0]);
case 29:return(long)shop_keeper((char)args[0]);
case 30:return(long)find_objowner((struct obj *)args[0],(coordxy)args[1],(coordxy)args[2]);
case 31:return(long)tended_shop((struct mkroom *)args[0]);
case 32:noisy_shop((struct mkroom *)args[0]);return 0;
case 33:return(long)teleport_shk_onbill((struct obj *)args[0],(struct monst *)args[1],(boolean)args[2]);
case 34:return(long)onshopbill((struct obj *)args[0],(struct monst *)args[1],(boolean)args[2]);
case 35:return(long)is_unpaid((struct obj *)args[0]);
case 36:delete_contents((struct obj *)args[0]);return 0;
case 37:obfree((struct obj *)args[0],(struct obj *)args[1]);return 0;
case 38:return(long)teleport_shk_check_credit((long)args[0],(struct monst *)args[1]);
case 39:teleport_shk_pay((long)args[0],(struct monst *)args[1]);return 0;
case 40:teleport_shk_home_shk((struct monst *)args[0],(boolean)args[1]);return 0;
case 41:return(long)teleport_shk_angry_shk_exists();
case 42:teleport_shk_pacify_shk((struct monst *)args[0],(boolean)args[1]);return 0;
case 43:teleport_shk_rile_shk((struct monst *)args[0]);return 0;
case 44:teleport_shk_rouse_shk((struct monst *)args[0],(boolean)args[1]);return 0;
case 45:make_happy_shk((struct monst *)args[0],(boolean)args[1]);return 0;
case 46:make_happy_shoppers((boolean)args[0]);return 0;
case 47:hot_pursuit((struct monst *)args[0]);return 0;
case 48:make_angry_shk((struct monst *)args[0],(coordxy)args[1],(coordxy)args[2]);return 0;
case 49:return(long)teleport_shk_sortbill_cmp((const void *)args[0],(const void *)args[1]);
case 50:return(long)teleport_shk_cheapest_item((int)args[0],(Bill *)args[1]);
case 51:return(long)teleport_shk_make_itemized_bill((struct monst *)args[0],(Bill **)args[1]);
case 52:return(long)teleport_shk_menu_pick_pay_items((int)args[0],(Bill *)args[1]);
case 53:return(long)dopay();
case 54:return(long)teleport_shk_pay_billed_items((struct monst *)args[0],(int)args[1],(Bill *)args[2],(boolean)args[3],(boolean *)args[4]);
case 55:teleport_shk_update_bill((int)args[0],(int)args[1],(Bill *)args[2],(struct eshk *)args[3],(struct bill_x *)args[4],(struct obj *)args[5]);return 0;
case 56:return(long)teleport_shk_dopayobj((struct monst *)args[0],(struct bill_x *)args[1],(struct obj *)args[2],(int)args[3],(boolean)args[4],(boolean)args[5]);
case 57:return(long)teleport_shk_buy_container((struct monst *)args[0],(int)args[1],(int)args[2],(Bill *)args[3]);
case 58:teleport_shk_reject_purchase((struct monst *)args[0],(struct obj *)args[1],(long)args[2]);return 0;
case 59:return(long)teleport_shk_insufficient_funds((struct monst *)args[0],(struct obj *)args[1],(long)args[2]);
case 60:return(long)paybill((int)args[0],(boolean)args[1]);
case 61:return(long)teleport_shk_inherits((struct monst *)args[0],(int)args[1],(int)args[2],(boolean)args[3]);
case 62:teleport_shk_set_repo_loc((struct monst *)args[0]);return 0;
case 63:finish_paybill();return 0;
case 64:return(long)teleport_shk_bp_to_obj((struct bill_x *)args[0]);
case 65:return(long)find_oid((unsigned int)args[0]);
case 66:return(long)get_cost_of_shop_item((struct obj *)args[0],(int *)args[1]);
case 67:return(long)teleport_shk_get_pricing_units((struct obj *)args[0]);
case 68:return(long)oid_price_adjustment((struct obj *)args[0],(unsigned int)args[1]);
case 69:return(long)teleport_shk_get_cost((struct obj *)args[0],(struct monst *)args[1]);
case 70:return(long)contained_cost((struct obj *)args[0],(struct monst *)args[1],(long)args[2],(boolean)args[3],(boolean)args[4]);
case 71:return(long)contained_gold((struct obj *)args[0],(boolean)args[1]);
case 72:teleport_shk_dropped_container((struct obj *)args[0],(struct monst *)args[1],(boolean)args[2]);return 0;
case 73:picked_container((struct obj *)args[0]);return 0;
case 74:return(long)teleport_shk_special_stock((struct obj *)args[0],(struct monst *)args[1],(boolean)args[2]);
case 75:return(long)teleport_shk_set_cost((struct obj *)args[0],(struct monst *)args[1]);
case 76:gem_learned((int)args[0]);return 0;
case 77:alter_cost((struct obj *)args[0],(long)args[1]);return 0;
case 78:return(long)unpaid_cost((struct obj *)args[0],(uchar)args[1]);
case 79:teleport_shk_add_one_tobill((struct obj *)args[0],(boolean)args[1],(struct monst *)args[2]);return 0;
case 80:teleport_shk_add_to_billobjs((struct obj *)args[0]);return 0;
case 81:teleport_shk_bill_box_content((struct obj *)args[0],(boolean)args[1],(boolean)args[2],(struct monst *)args[3]);return 0;
case 82:teleport_shk_shk_names_obj((struct monst *)args[0],(struct obj *)args[1],(const char *)args[2],(long)args[3],(const char *)args[4]);return 0;
case 83:return(long)billable((struct monst **)args[0],(struct obj *)args[1],(char)args[2],(boolean)args[3]);
case 84:addtobill((struct obj *)args[0],(boolean)args[1],(boolean)args[2],(boolean)args[3]);return 0;
case 85:teleport_shk_append_honorific((char *)args[0]);return 0;
case 86:splitbill((struct obj *)args[0],(struct obj *)args[1]);return 0;
case 87:teleport_shk_sub_one_frombill((struct obj *)args[0],(struct monst *)args[1]);return 0;
case 88:subfrombill((struct obj *)args[0],(struct monst *)args[1]);return 0;
case 89:return(long)teleport_shk_stolen_container((struct obj *)args[0],(struct monst *)args[1],(long)args[2],(boolean)args[3]);
case 90:return(long)stolen_value((struct obj *)args[0],(coordxy)args[1],(coordxy)args[2],(boolean)args[3],(boolean)args[4]);
case 91:donate_gold((long)args[0],(struct monst *)args[1],(boolean)args[2]);return 0;
case 92:sellobj_state((int)args[0]);return 0;
case 93:sellobj((struct obj *)args[0],(coordxy)args[1],(coordxy)args[2]);return 0;
case 94:return(long)doinvbill((int)args[0]);
case 95:return(long)teleport_shk_corpsenm_price_adj((struct obj *)args[0]);
case 96:return(long)teleport_shk_getprice((struct obj *)args[0],(boolean)args[1]);
case 97:return(long)shkcatch((struct obj *)args[0],(coordxy)args[1],(coordxy)args[2]);
case 98:add_damage((coordxy)args[0],(coordxy)args[1],(long)args[2]);return 0;
case 99:return(long)teleport_shk_shk_impaired((struct monst *)args[0]);
case 100:return(long)teleport_shk_repairable_damage((struct damage *)args[0],(struct monst *)args[1]);
case 101:return(long)teleport_shk_find_damage((struct monst *)args[0]);
case 102:teleport_shk_discard_damage_struct((struct damage *)args[0]);return 0;
case 103:teleport_shk_discard_damage_owned_by((struct monst *)args[0]);return 0;
case 104:teleport_shk_shk_fixes_damage((struct monst *)args[0]);return 0;
case 105:return(long)teleport_shk_litter_getpos((uint8 *)args[0],(coordxy)args[1],(coordxy)args[2],(struct monst *)args[3]);
case 106:teleport_shk_litter_scatter((uint8 *)args[0],(coordxy)args[1],(coordxy)args[2],(struct monst *)args[3]);return 0;
case 107:teleport_shk_litter_newsyms((uint8 *)args[0],(coordxy)args[1],(coordxy)args[2]);return 0;
case 108:return(long)teleport_shk_repair_damage((struct monst *)args[0],(struct damage *)args[1],(boolean)args[2]);
case 109:fix_shop_damage();return 0;
case 110:return(long)shk_move((struct monst *)args[0]);
case 111:after_shk_move((struct monst *)args[0]);return 0;
case 112:return(long)is_fshk((struct monst *)args[0]);
case 113:shopdig((int)args[0]);return 0;
case 114:teleport_shk_makekops((coord *)args[0]);return 0;
case 115:teleport_shk_getcad((struct monst *)args[0],(const char *)args[1],(coordxy)args[2],(coordxy)args[3],(boolean)args[4],(boolean)args[5],(boolean)args[6]);return 0;
case 116:pay_for_damage((const char *)args[0],(boolean)args[1]);return 0;
case 117:return(long)costly_spot((coordxy)args[0],(coordxy)args[1]);
case 118:return(long)costly_adjacent((struct monst *)args[0],(coordxy)args[1],(coordxy)args[2]);
case 119:return(long)shop_object((coordxy)args[0],(coordxy)args[1]);
case 120:price_quote((struct obj *)args[0]);return 0;
case 121:return(long)teleport_shk_shk_embellish((struct obj *)args[0],(long)args[1]);
case 122:shk_chat((struct monst *)args[0]);return 0;
case 123:teleport_shk_kops_gone((boolean)args[0]);return 0;
case 124:return(long)teleport_shk_cost_per_charge((struct monst *)args[0],(struct obj *)args[1],(boolean)args[2]);
case 125:check_unpaid_usage((struct obj *)args[0],(boolean)args[1]);return 0;
case 126:check_unpaid((struct obj *)args[0]);return 0;
case 127:costly_gold((coordxy)args[0],(coordxy)args[1],(long)args[2],(boolean)args[3]);return 0;
case 128:return(long)block_door((coordxy)args[0],(coordxy)args[1]);
case 129:return(long)block_entry((coordxy)args[0],(coordxy)args[1]);
case 130:return(long)shk_your((char *)args[0],(struct obj *)args[1]);
case 131:return(long)Shk_Your((char *)args[0],(struct obj *)args[1]);
case 132:return(long)teleport_shk_shk_owns((char *)args[0],(struct obj *)args[1]);
case 133:return(long)teleport_shk_mon_owns((char *)args[0],(struct obj *)args[1]);
case 134:return(long)teleport_shk_cad((boolean)args[0]);
case 135:globby_bill_fixup((struct obj *)args[0],(struct obj *)args[1]);return 0;
case 136:use_unpaid_trapobj((struct obj *)args[0],(coordxy)args[1],(coordxy)args[2]);return 0;
default:abort();}}

void probe_option(int i,long v){opts[i]=v;if(i==40)rngstate=(unsigned)v;}void probe_clear(void){tracepos=draws=0;tracebuf[0]=0;callerfile=callerowner=0;callerline=autosp=0;}
void probe_reset(void){memset(&gi,0,sizeof gi);memset(&disp,0,sizeof disp);memset(&svr,0,sizeof svr);memset(&u,0,sizeof u);memset(&svl,0,sizeof svl);memset(&svp,0,sizeof svp);memset(&gt,0,sizeof gt);memset(&gk,0,sizeof gk);memset(&gm,0,sizeof gm);memset(&gb,0,sizeof gb);memset(&svm,0,sizeof svm);memset(&flags,0,sizeof flags);memset(&gu,0,sizeof gu);windowprocs=(struct window_procs){0};memset(&gv,0,sizeof gv);memset(&iflags,0,sizeof iflags);memset(&gr,0,sizeof gr);memset(&uball,0,sizeof uball);memset(&uchain,0,sizeof uchain);memset(&ubirthday,0,sizeof ubirthday);memset(&uarmh,0,sizeof uarmh);memset(&uarmu,0,sizeof uarmu);memset(&uarm,0,sizeof uarm);memset(&uarmc,0,sizeof uarmc);memset(&gy,0,sizeof gy);memset(&gs,0,sizeof gs);memset(&ga,0,sizeof ga);memset(&gf,0,sizeof gf);memset(&program_state,0,sizeof program_state);memset(&uswapwep,0,sizeof uswapwep);memset(&gc,0,sizeof gc);monst_globals_init();objects_globals_init();memset(opts,0,sizeof opts);memset(obj,0,sizeof obj);memset(ox,0,sizeof ox);memset(mon,0,sizeof mon);memset(mx,0,sizeof mx);memset(shop,0,sizeof shop);memset(billbuf,0,sizeof billbuf);memset(longs,0,sizeof longs);memset(objcell,0,sizeof objcell);memset(buffers,0,sizeof buffers);memset(menu,0,sizeof menu);memset(&u,0,sizeof u);memset(&svl,0,sizeof svl);memset(&svr,0,sizeof svr);memset(&gi,0,sizeof gi);memset(&gm,0,sizeof gm);memset(&gb,0,sizeof gb);memset(&gr,0,sizeof gr);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&disp,0,sizeof disp);memset(&program_state,0,sizeof program_state);for(int i=0;i<32;i++){obj[i].otyp=DAGGER;obj[i].oclass=WEAPON_CLASS;obj[i].quan=1;obj[i].o_id=i+1;obj[i].corpsenm=NON_PM;obj[i].invlet='a'+i;obj[i].ox=12;obj[i].oy=10;}u.ux=12;u.uy=10;u.uz.dlevel=1;u.ulevel=10;u.umonnum=PM_HUMAN;gy.youmonst.data=&mons[PM_HUMAN];for(int i=0;i<4;i++){mon[i].mextra=&mx[i];mx[i].eshk=&shop[i];mon[i].isshk=1;mon[i].mhp=10;mon[i].mcanmove=1;mon[i].mcansee=1;mon[i].mpeaceful=1;mon[i].mx=12+i;mon[i].my=10;mon[i].data=&mons[PM_SHOPKEEPER];shop[i].bill_p=shop[i].bill;shop[i].shoproom=ROOMOFFSET+i;shop[i].shoptype=SHOPBASE;shop[i].shoplevel=u.uz;shop[i].shk.x=12+i;shop[i].shk.y=10;shop[i].shd.x=10;shop[i].shd.y=10;svr.rooms[i].resident=&mon[i];svr.rooms[i].rtype=SHOPBASE;svr.rooms[i].lx=10;svr.rooms[i].hx=16;svr.rooms[i].ly=8;svr.rooms[i].hy=12;strcpy(shop[i].customer,"Tester");}for(int y=0;y<ROWNO;y++){visionrows[y]=vision[y];memset(vision[y],IN_SIGHT,COLNO);}gv.viz_array=visionrows;for(int x=1;x<COLNO;x++)for(int y=0;y<ROWNO;y++){levl[x][y].typ=ROOM;levl[x][y].roomno=ROOMOFFSET;}strcpy(svp.plname,"Tester");for(int i=0;i<64;i++){((Bill*)billbuf)[i].obj=&obj[i%32];((Bill*)billbuf)[i].cost=1;((Bill*)billbuf)[i].quan=1;((Bill*)billbuf)[i].usedup=FullyIntact;}windowprocs.name="controlled";windowprocs.win_create_nhwindow=backend_create;windowprocs.win_destroy_nhwindow=backend_destroy;windowprocs.win_display_nhwindow=backend_display;windowprocs.win_putstr=backend_put;windowprocs.win_start_menu=backend_start;windowprocs.win_end_menu=backend_end;windowprocs.win_mark_synch=backend_sync;windowprocs.win_wait_synch=backend_sync;windowprocs.win_delay_output=backend_sync;uball=uchain=uarmh=uarmu=uarm=uarmc=uswapwep=0;rngstate=1;probe_clear();}
long probe_function(int i){switch(i){case 0:return(long)Doname2;case 1:return(long)ansimpleoname;case 2:return(long)doname;case 3:return(long)simpleonames;case 4:return(long)teleport_shk_sortbill_cmp;case 5:return(long)thesimpleoname;case 6:return(long)xname;default:abort();}}
long probe_record(int k,int i){switch(k){case 0:return(long)&obj[i];case 1:return(long)&mon[i];case 2:return(long)&shop[i];case 3:return(long)&shop[0].bill[i];case 4:return(long)&((Bill*)billbuf)[i];case 5:return(long)&longs[i];case 6:return(long)&objcell[i];case 7:return(long)&menu[i];case 8:return(long)&mx[i];case 9:return(long)&ox[i];default:abort();}}
char*probe_buffer(int i){return buffers[i];}long probe_global(int i){return(long)teleport_shk_global(i);}long probe_layout(int i){return(long)teleport_shk_layout(i);}uint64_t probe_read(int k,void*p,int f){return teleport_shk_read(k,p,f);}void probe_write(int k,void*p,int f,uint64_t v){teleport_shk_write(k,p,f,v);}void*probe_address(int k,void*p,int f){return teleport_shk_address(k,p,f);}
void probe_chain(int head,int from,int to){struct obj**p=head==0?&gi.invent:head==1?&svl.level.objlist:head==2?&mon[0].minvent:head==3?&gb.billobjs:&svl.level.buriedobjlist;if(from<0)*p=to<0?0:&obj[to];else obj[from].nobj=to<0?0:&obj[to];}
void probe_bill(int s,int b,int o,long price,long quan,int used){shop[s].billct=b+1;shop[s].bill[b].bo_id=obj[o].o_id;shop[s].bill[b].price=price;shop[s].bill[b].bquan=quan;shop[s].bill[b].useup=used;obj[o].unpaid=!used;obj[o].where=used?OBJ_ONBILL:OBJ_INVENT;}
void probe_shops(int n){svl.level.monlist=n?&mon[0]:0;for(int i=0;i<4;i++)mon[i].nmon=i+1<n?&mon[i+1]:0;}
void probe_property(int p,long i,long e){u.uprops[p].intrinsic=i;u.uprops[p].extrinsic=e;}
const char*probe_trace(void){return tracebuf;}long probe_stack(void){return emscripten_stack_get_current();}
const char*probe_snapshot(void){int n=snprintf(snap,sizeof snap,"invent:%d;floor:%d;billobj:%d;botl:%d;multi:%ld;repo:%d/%d/%d;",oid(gi.invent),oid(fobj),oid(gb.billobjs),disp.botl,gm.multi,mid(gr.repo.shopkeeper),gr.repo.location.x,gr.repo.location.y);for(int s=0;s<4;s++){struct eshk*p=&shop[s];uint64_t bp=(uint64_t)(uintptr_t)p->bill_p;char id[64];if(p->bill_p==p->bill)strcpy(id,"ownbill");else snprintf(id,sizeof id,"%llu",(unsigned long long)bp);n+=snprintf(snap+n,sizeof snap-n,"s%d:%ld/%ld/%ld/%ld/%d/%s/%d/%d/%d/%d;",s,p->credit,p->debit,p->loan,p->robbed,p->billct,id,p->surcharge,p->following,mon[s].mpeaceful,mon[s].msleeping);for(int b=0;b<p->billct;b++)n+=snprintf(snap+n,sizeof snap-n,"b%d:%u/%d/%ld/%ld;",b,p->bill[b].bo_id,p->bill[b].useup,p->bill[b].price,p->bill[b].bquan);}for(int i=0;i<32;i++)n+=snprintf(snap+n,sizeof snap-n,"o%d:%d/%ld/%d/%d/%d/%d/%d;",i,oid(obj[i].nobj),obj[i].quan,obj[i].where,obj[i].unpaid,obj[i].no_charge,obj[i].ox,obj[i].oy);for(int i=0;i<16;i++)if(!(opts[41]&(1L<<i)))n+=snprintf(snap+n,sizeof snap-n,"l%d:%ld;",i,longs[i]);return snap;}

long probe_invoke(int i,void*fn,void*a,void*b){switch(i){case 0:return(long)((__typeof__(&Doname2))fn)((struct obj *)a);case 1:return(long)((__typeof__(&ansimpleoname))fn)((struct obj *)a);case 2:return(long)((__typeof__(&doname))fn)((struct obj *)a);case 3:return(long)((__typeof__(&simpleonames))fn)((struct obj *)a);case 4:return(long)((__typeof__(&teleport_shk_sortbill_cmp))fn)((const void *)a,(const void *)b);case 5:return(long)((__typeof__(&thesimpleoname))fn)((struct obj *)a);case 6:return(long)((__typeof__(&xname))fn)((struct obj *)a);default:abort();}}
void probe_valid(int which){switch(which){case 39:shop[0].credit=1;break;case 25:mon[0].nmon=0;fmon=&mon[0];shop[0].billct=2;for(int i=0;i<2;i++){obj[i].unpaid=1;obj[i].where=OBJ_INVENT;shop[0].bill[i].bo_id=i+1;shop[0].bill[i].price=1;shop[0].bill[i].bquan=1;}gi.invent=&obj[0];obj[0].nobj=&obj[1];break;case 78:u.ushops[0]=ROOMOFFSET;shop[0].billct=1;obj[0].unpaid=1;obj[0].where=OBJ_INVENT;gi.invent=&obj[0];break;case 86:u.ushops[0]=ROOMOFFSET;shop[0].billct=1;shop[0].bill[0].bo_id=1;shop[0].bill[0].price=1;shop[0].bill[0].bquan=2;obj[0].unpaid=obj[1].unpaid=1;obj[0].where=obj[1].where=OBJ_INVENT;gi.invent=&obj[0];obj[0].nobj=&obj[1];break;case 55:shop[0].billct=1;obj[0].unpaid=1;obj[0].where=OBJ_INVENT;gi.invent=&obj[0];break;case 56:shop[0].billct=1;obj[0].unpaid=1;obj[0].where=OBJ_INVENT;gi.invent=&obj[0];break;case 57:obj[0].otyp=LARGE_BOX;obj[0].oclass=TOOL_CLASS;obj[0].where=OBJ_INVENT;gi.invent=&obj[0];obj[0].cobj=&obj[1];obj[1].where=OBJ_CONTAINED;obj[1].ocontainer=&obj[0];((Bill*)billbuf)[0].usedup=KnownContainer;break;case 135:for(int i=0;i<2;i++){obj[i].otyp=GLOB_OF_GRAY_OOZE;obj[i].oclass=FOOD_CLASS;obj[i].globby=1;obj[i].owt=20;}break;case 22:svr.rooms[0].resident=0;break;case 1000:obj[0].otyp=SPE_FORCE_BOLT;obj[0].oclass=SPBOOK_CLASS;break;default:break;}}
