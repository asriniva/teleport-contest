/* Configured original TRAP versus JS policy; controlled foreign effects. */
#include "hack.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
extern const char *const destroy_strings[][3];
__typeof__(gy) gy;
__typeof__(uarmh) uarmh;
const char *materialnm[64]={[0 ... 63]="fixture material"};
__typeof__(uarmc) uarmc;
__typeof__(uarm) uarm;
__typeof__(uarmu) uarmu;
__typeof__(uarms) uarms;
__typeof__(uarmg) uarmg;
__typeof__(uarmf) uarmf;
__typeof__(gv) gv;
__typeof__(gb) gb;
__typeof__(u) u;
__typeof__(flags) flags;
__typeof__(svd) svd;
__typeof__(svl) svl;
__typeof__(iflags) iflags;
__typeof__(svc) svc;
__typeof__(gl) gl;
__typeof__(gx) gx;
__typeof__(gf) gf;
__typeof__(WIN_MESSAGE) WIN_MESSAGE;
__typeof__(windowprocs) windowprocs;
__typeof__(gu) gu;
__typeof__(c_common_strings) c_common_strings={.c_nothing_happens="fixture c_nothing_happens",.c_nothing_seems_to_happen="fixture c_nothing_seems_to_happen",.c_thats_enough_tries="fixture c_thats_enough_tries",.c_silly_thing_to="fixture c_silly_thing_to",.c_shudder_for_moment="fixture c_shudder_for_moment",.c_something="fixture c_something",.c_Something="fixture c_Something",.c_You_can_move_again="fixture c_You_can_move_again",.c_Never_mind="fixture c_Never_mind",.c_vision_clears="fixture c_vision_clears",.c_the_your="fixture c_the_your",.c_fakename="fixture c_fakename"};
__typeof__(disp) disp;
__typeof__(uwep) uwep;
__typeof__(uswapwep) uswapwep;
__typeof__(gi) gi;
__typeof__(uball) uball;
__typeof__(gm) gm;
__typeof__(gn) gn;
__typeof__(uquiver) uquiver;
__typeof__(go) go;
const schar xdir[10]={-1,-1,0,1,1,1,0,-1,0,0};
const schar ydir[10]={0,-1,-1,-1,0,1,1,1,0,0};
__typeof__(svk) svk;
__typeof__(gs) gs;
__typeof__(uchain) uchain;
__typeof__(cg) cg;
const char *const destroy_strings[64][3]={[0 ... 63]={"destroyed","destroyed","destroyed"}};
__typeof__(gt) gt;
__typeof__(gk) gk;
__typeof__(ga) ga;
__typeof__(uamul) uamul;
__typeof__(uleft) uleft;
__typeof__(uright) uright;
__typeof__(ublindf) ublindf;
const char ynqchars[]="ynq";
__typeof__(defsyms) defsyms={[0 ... MAXPCHARS-1]={.explanation="fixture trap"}};
const char vowels[]="aeiouAEIOU";
static struct obj objects_fixture[16];static struct monst monsters_fixture[8];static struct trap *traps_fixture[16];static int traps_live[16];static d_level levels_fixture[8];static coord coords_fixture[8];static struct permonst *copies[4];static unsigned char storage_fixture[8192];static seenV vision_fixture[ROWNO][COLNO];static seenV*vision_rows[ROWNO];
static int options[512],seed=1,tracepos,reentered;static char tracebuf[1048576];static void *growth;extern void probe_js_event(void);extern void probe_js_fatal(const char*);
static void append(const char*fmt,...){va_list ap;va_start(ap,fmt);int n=vsnprintf(tracebuf+tracepos,sizeof tracebuf-tracepos,fmt,ap);va_end(ap);if(n<0||tracepos+n>=sizeof tracebuf)abort();tracepos+=n;}
static void event(void){if(options[500]&&!growth){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)abort();append("growth;");}if(options[501]&&!reentered){reentered=1;probe_js_event();}}
static void message(const char*name,const char*fmt,va_list ap){char b[8192];vsnprintf(b,sizeof b,fmt,ap);append("%s:%s;",name,b);event();}
static int random_(int n){if(n<=0)abort();seed=(unsigned)seed*1664525U+1013904223U;return(unsigned)seed%n;}
void __real_free(void*);void __wrap_free(void*p){for(int i=0;i<16;i++)if(p==traps_fixture[i]&&traps_live[i]){traps_live[i]=0;append("free-trap:%d;",i);}__real_free(p);}
static int objid(const struct obj*o){return o?(int)o->o_id:-1;}
static int monid(const struct monst*m){return m==&gy.youmonst?999:m?(int)m->m_id:-1;}
static int pmid(const struct permonst*p){if(!p)return -1;for(int i=0;i<NUMMONS;i++)if(p==&mons[i])return i;for(int i=0;i<4;i++)if(p==copies[i])return 1000+i;return 2000;}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-pointer-compare"
#pragma clang diagnostic ignored "-Wpointer-bool-conversion"
char * (Amonnam)(struct monst * a0){
append("Amonnam(");
append("m:%d,",monid(a0));
append(");");
return "fixture";
}
int (Boots_off)(void){
append("Boots_off(");
append(");");
return options[1];
}
boolean (Can_fall_thru)(d_level * a0){
append("Can_fall_thru(");
append("p:%d,",a0!=NULL);
append(");");
return options[2];
}
boolean (In_hell)(d_level * a0){
append("In_hell(");
append("p:%d,",a0!=NULL);
append(");");
return options[3];
}
boolean (In_quest)(d_level * a0){
append("In_quest(");
append("p:%d,",a0!=NULL);
append(");");
return options[4];
}
char * (Monnam)(struct monst * a0){
append("Monnam(");
append("m:%d,",monid(a0));
append(");");
return "fixture";
}
void (Norep)(const char * a0,...){
va_list ap;va_start(ap,a0);message("Norep",a0,ap);va_end(ap);

}
boolean (Resists_Elem)(struct monst * a0,int a1){
append("Resists_Elem(");
append("m:%d,",monid(a0));
append("i:%lld,",(long long)a1);
append(");");
return options[7];
}
char * (The)(const char * a0){
append("The(");
append("s:%s,",a0?a0:"(null)");
append(");");
return "fixture";
}
void (There)(const char * a0,...){
va_list ap;va_start(ap,a0);message("There",a0,ap);va_end(ap);

}
char * (Tobjnam)(struct obj * a0,const char * a1){
append("Tobjnam(");
append("o:%d,",objid(a0));
append("s:%s,",a1?a1:"(null)");
append(");");
return "fixture";
}
char * (YMonnam)(struct monst * a0){
append("YMonnam(");
append("m:%d,",monid(a0));
append(");");
return "fixture";
}
char * (Yname2)(struct obj * a0){
append("Yname2(");
append("o:%d,",objid(a0));
append(");");
return "fixture";
}
char * (Yobjnam2)(struct obj * a0,const char * a1){
append("Yobjnam2(");
append("o:%d,",objid(a0));
append("s:%s,",a1?a1:"(null)");
append(");");
return "fixture";
}
void (You)(const char * a0,...){
va_list ap;va_start(ap,a0);message("You",a0,ap);va_end(ap);

}
void (You_cant)(const char * a0,...){
va_list ap;va_start(ap,a0);message("You_cant",a0,ap);va_end(ap);

}
void (You_feel)(const char * a0,...){
va_list ap;va_start(ap,a0);message("You_feel",a0,ap);va_end(ap);

}
void (You_hear)(const char * a0,...){
va_list ap;va_start(ap,a0);message("You_hear",a0,ap);va_end(ap);

}
void (You_see)(const char * a0,...){
va_list ap;va_start(ap,a0);message("You_see",a0,ap);va_end(ap);

}
void (Your)(const char * a0,...){
va_list ap;va_start(ap,a0);message("Your",a0,ap);va_end(ap);

}
char * (a_monnam)(struct monst * a0){
append("a_monnam(");
append("m:%d,",monid(a0));
append(");");
return "fixture";
}
void (abuse_dog)(struct monst * a0){
append("abuse_dog(");
append("m:%d,",monid(a0));
append(");");

}
schar (acurr)(int a0){
append("acurr(");
append("i:%lld,",(long long)a0);
append(");");
return options[22];
}
void (add_damage)(coordxy a0,coordxy a1,long a2){
append("add_damage(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");

}
struct obj * (add_to_container)(struct obj * a0,struct obj * a1){
append("add_to_container(");
append("o:%d,",objid(a0));
append("o:%d,",objid(a1));
append(");");
a1->nobj=a0->cobj;a0->cobj=a1;a1->where=OBJ_CONTAINED;a1->ocontainer=a0;return a1;
}
void (add_to_migration)(struct obj * a0){
append("add_to_migration(");
append("o:%d,",objid(a0));
append(");");

}
void (adjalign)(int a0){
append("adjalign(");
append("i:%lld,",(long long)a0);
append(");");

}
boolean (adjattrib)(int a0,int a1,int a2){
append("adjattrib(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");
return options[27];
}
long * (alloc)(unsigned int a0){
append("alloc(");
append("i:%lld,",(long long)a0);
append(");");
void*p=calloc(1,a0);if(!p)abort();return (long*)p;
}
char * (an)(const char * a0){
append("an(");
append("s:%s,",a0?a0:"(null)");
append(");");
return "fixture";
}
char * (ansimpleoname)(struct obj * a0){
append("ansimpleoname(");
append("o:%d,",objid(a0));
append(");");
return "fixture";
}
char * (aobjnam)(struct obj * a0,const char * a1){
append("aobjnam(");
append("o:%d,",objid(a0));
append("s:%s,",a1?a1:"(null)");
append(");");
return "fixture";
}
void (assign_level)(d_level * a0,d_level * a1){
append("assign_level(");
append("p:%d,",a0!=NULL);
append("p:%d,",a1!=NULL);
append(");");
*a0=*a1;
}
boolean (at_dgn_entrance)(const char * a0){
append("at_dgn_entrance(");
append("s:%s,",a0?a0:"(null)");
append(");");
return options[33];
}
boolean (attacks)(int a0,struct obj * a1){
append("attacks(");
append("i:%lld,",(long long)a0);
append("o:%d,",objid(a1));
append(");");
return options[34];
}
boolean (attacktype)(struct permonst * a0,int a1){
append("attacktype(");
append("pm:%d,",pmid(a0));
append("i:%lld,",(long long)a1);
append(");");
return options[35];
}
boolean (bad_rock)(struct permonst * a0,coordxy a1,coordxy a2){
append("bad_rock(");
append("pm:%d,",pmid(a0));
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");
return options[36];
}
void (ballfall)(void){
append("ballfall(");
append(");");

}
char * (bare_artifactname)(struct obj * a0){
append("bare_artifactname(");
append("o:%d,",objid(a0));
append(");");
return "fixture";
}
void (blank_novel)(struct obj * a0){
append("blank_novel(");
append("o:%d,",objid(a0));
append(");");

}
const char * (body_part)(int a0){
append("body_part(");
append("i:%lld,",(long long)a0);
append(");");
return "fixture";
}
void (bot)(void){
append("bot(");
append(");");

}
struct obj * (buried_ball)(coord * a0){
append("buried_ball(");
append("p:%d,",a0!=NULL);
append(");");
return options[42]?&objects_fixture[0]:NULL;
}
void (burn_away_slime)(void){
append("burn_away_slime(");
append(");");

}
int (burn_floor_objects)(coordxy a0,coordxy a1,boolean a2,boolean a3){
append("burn_floor_objects(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append("i:%lld,",(long long)a3);
append(");");
return options[44];
}
struct obj * (bury_an_obj)(struct obj * a0,boolean * a1){
append("bury_an_obj(");
append("o:%d,",objid(a0));
append("p:%d,",a1!=NULL);
append(");");
return options[45]?&objects_fixture[1]:NULL;
}
int (calc_capacity)(int a0){
append("calc_capacity(");
append("i:%lld,",(long long)a0);
append(");");
return options[46];
}
boolean (can_reach_floor)(boolean a0){
append("can_reach_floor(");
append("i:%lld,",(long long)a0);
append(");");
return options[47];
}
int (canseemon)(struct monst * a0){
append("canseemon(");
append("m:%d,",monid(a0));
append(");");
return options[48];
}
boolean (cant_revive)(int * a0,boolean a1,struct obj * a2){
append("cant_revive(");
append("p:%d,",a0!=NULL);
append("i:%lld,",(long long)a1);
append("o:%d,",objid(a2));
append(");");
return options[49];
}
struct obj * (carrying)(int a0){
append("carrying(");
append("i:%lld,",(long long)a0);
append(");");
return options[50]?&objects_fixture[0]:NULL;
}
boolean (catch_lit)(struct obj * a0){
append("catch_lit(");
append("o:%d,",objid(a0));
append(");");
return options[51];
}
const char * (ceiling)(coordxy a0,coordxy a1){
append("ceiling(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");
return "fixture";
}
void (change_luck)(schar a0){
append("change_luck(");
append("i:%lld,",(long long)a0);
append(");");

}
boolean (check_capacity)(const char * a0){
append("check_capacity(");
append("s:%s,",a0?a0:"(null)");
append(");");
return options[54];
}
void (check_leash)(coordxy a0,coordxy a1){
append("check_leash(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");

}
struct monst * (christen_monst)(struct monst * a0,const char * a1){
append("christen_monst(");
append("m:%d,",monid(a0));
append("s:%s,",a1?a1:"(null)");
append(");");
return a0;
}
const char * (cloak_simple_name)(struct obj * a0){
append("cloak_simple_name(");
append("o:%d,",objid(a0));
append(");");
return "fixture";
}
boolean (closed_door)(coordxy a0,coordxy a1){
append("closed_door(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");
return options[58];
}
void (consume_obj_charge)(struct obj * a0,boolean a1){
append("consume_obj_charge(");
append("o:%d,",objid(a0));
append("i:%lld,",(long long)a1);
append(");");

}
void (copynchars)(char * a0,const char * a1,int a2){
append("copynchars(");
append("s:%s,",a0?a0:"(null)");
append("s:%s,",a1?a1:"(null)");
append("i:%lld,",(long long)a2);
append(");");
strncpy(a0,a1,a2);a0[a2]=0;
}
char * (corpse_xname)(struct obj * a0,const char * a1,unsigned int a2){
append("corpse_xname(");
append("o:%d,",objid(a0));
append("s:%s,",a1?a1:"(null)");
append("i:%lld,",(long long)a2);
append(");");
return "fixture";
}
void (costly_alteration)(struct obj * a0,int a1){
append("costly_alteration(");
append("o:%d,",objid(a0));
append("i:%lld,",(long long)a1);
append(");");

}
boolean (costly_spot)(coordxy a0,coordxy a1){
append("costly_spot(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");
return options[63];
}
int (count_wsegs)(struct monst * a0){
append("count_wsegs(");
append("m:%d,",monid(a0));
append(");");
return options[64];
}
boolean (crawl_destination)(coordxy a0,coordxy a1){
append("crawl_destination(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");
return options[65];
}
NhRegion * (create_gas_cloud)(coordxy a0,coordxy a1,int a2,int a3){
append("create_gas_cloud(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append("i:%lld,",(long long)a3);
append(");");
return NULL;
}
const char * (currency)(long a0){
append("currency(");
append("i:%lld,",(long long)a0);
append(");");
return "fixture";
}
void (curs_on_u)(void){
append("curs_on_u(");
append(");");

}
char * (cxname)(struct obj * a0){
append("cxname(");
append("o:%d,",objid(a0));
append(");");
return "fixture";
}
int (d)(int a0,int a1){
append("d(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");
int v=0;for(int i=0;i<a0;i++)v+=random_(a1)+1;append("draw:%d;",v);return v;
}
void (dealloc_obj)(struct obj * a0){
append("dealloc_obj(");
append("o:%d,",objid(a0));
append(");");

}
boolean (debugcore)(const char * a0,boolean a1){
append("debugcore(");
append("s:%s,",a0?a0:"(null)");
append("i:%lld,",(long long)a1);
append(");");
return options[72];
}
boolean (defended)(struct monst * a0,int a1){
append("defended(");
append("m:%d,",monid(a0));
append("i:%lld,",(long long)a1);
append(");");
return options[73];
}
boolean (defends_when_carried)(int a0,struct obj * a1){
append("defends_when_carried(");
append("i:%lld,",(long long)a0);
append("o:%d,",objid(a1));
append(");");
return options[74];
}
void (del_engr_at)(coordxy a0,coordxy a1){
append("del_engr_at(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");

}
void (delete_contents)(struct obj * a0){
append("delete_contents(");
append("o:%d,",objid(a0));
append(");");

}
void (delobj)(struct obj * a0){
append("delobj(");
append("o:%d,",objid(a0));
append(");");

}
schar (depth)(d_level * a0){
append("depth(");
append("p:%d,",a0!=NULL);
append(");");
return a0->dlevel;
}
void (destroy_drawbridge)(coordxy a0,coordxy a1){
append("destroy_drawbridge(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");

}
int (destroy_items)(struct monst * a0,int a1,int a2){
append("destroy_items(");
append("m:%d,",monid(a0));
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");
return options[80];
}
void (discover_object)(int a0,boolean a1,boolean a2,boolean a3){
append("discover_object(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append("i:%lld,",(long long)a3);
append(");");

}
void (dismount_steed)(int a0){
append("dismount_steed(");
append("i:%lld,",(long long)a0);
append(");");

}
int (dist2)(coordxy a0,coordxy a1,coordxy a2,coordxy a3){
append("dist2(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append("i:%lld,",(long long)a3);
append(");");
return (a0-a2)*(a0-a2)+(a1-a3)*(a1-a3);
}
int (distmin)(coordxy a0,coordxy a1,coordxy a2,coordxy a3){
append("distmin(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append("i:%lld,",(long long)a3);
append(");");
return abs(a0-a2)>abs(a1-a3)?abs(a0-a2):abs(a1-a3);
}
struct attack * (dmgtype_fromattack)(struct permonst * a0,int a1,int a2){
append("dmgtype_fromattack(");
append("pm:%d,",pmid(a0));
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");
return options[85]?&mons[PM_HUMAN].mattk[0]:NULL;
}
int (dmgval)(struct obj * a0,struct monst * a1){
append("dmgval(");
append("o:%d,",objid(a0));
append("m:%d,",monid(a1));
append(");");
return options[86];
}
void (domagicportal)(struct trap * a0){
append("domagicportal(");
if(a0)append("t:%d:%d:%d,",a0->tx,a0->ty,a0->ttyp);else append("t:null,");
append(");");

}
char * (doname)(struct obj * a0){
append("doname(");
append("o:%d,",objid(a0));
append(");");
return "fixture";
}
void (done)(int a0){
append("done(");
append("i:%lld,",(long long)a0);
append(");");
if(!options[498])probe_js_fatal("done");u.uhp=100;
}
int (dotele)(boolean a0){
append("dotele(");
append("i:%lld,",(long long)a0);
append(");");
return options[90];
}
schar (down_gate)(coordxy a0,coordxy a1){
append("down_gate(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");
return options[91];
}
boolean (drag_ball)(coordxy a0,coordxy a1,int * a2,coordxy * a3,coordxy * a4,coordxy * a5,coordxy * a6,boolean * a7,boolean a8){
append("drag_ball(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("p:%d,",a2!=NULL);
append("p:%d,",a3!=NULL);
append("p:%d,",a4!=NULL);
append("p:%d,",a5!=NULL);
append("p:%d,",a6!=NULL);
append("p:%d,",a7!=NULL);
append("i:%lld,",(long long)a8);
append(");");
return options[92];
}
void (dropx)(struct obj * a0){
append("dropx(");
append("o:%d,",objid(a0));
append(");");

}
void (dry_a_towel)(struct obj * a0,int a1,boolean a2){
append("dry_a_towel(");
append("o:%d,",objid(a0));
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");

}
xint16 (dunlev)(d_level * a0){
append("dunlev(");
append("p:%d,",a0!=NULL);
append(");");
return a0->dlevel;
}
xint16 (dunlevs_in_dungeon)(d_level * a0){
append("dunlevs_in_dungeon(");
append("p:%d,",a0!=NULL);
append(");");
return 10;
}
void (encumber_msg)(void){
append("encumber_msg(");
append(");");

}
char * (eos)(char * a0){
append("eos(");
append("s:%s,",a0?a0:"(null)");
append(");");
return a0+strlen(a0);
}
boolean (erosion_matters)(struct obj * a0){
append("erosion_matters(");
append("o:%d,",objid(a0));
append(");");
return TRUE;
}
void (exercise)(int a0,boolean a1){
append("exercise(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");

}
void (extract_from_minvent)(struct monst * a0,struct obj * a1,boolean a2,boolean a3){
append("extract_from_minvent(");
append("m:%d,",monid(a0));
append("o:%d,",objid(a1));
append("i:%lld,",(long long)a2);
append("i:%lld,",(long long)a3);
append(");");

}
void (fall_asleep)(int a0,boolean a1){
append("fall_asleep(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");

}
void (feel_newsym)(coordxy a0,coordxy a1){
append("feel_newsym(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");

}
schar (fillholetyp)(coordxy a0,coordxy a1,boolean a2){
append("fillholetyp(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");
return options[104];
}
boolean (find_drawbridge)(coordxy * a0,coordxy * a1){
append("find_drawbridge(");
append("p:%d,",a0!=NULL);
append("p:%d,",a1!=NULL);
append(");");
return options[105];
}
void (find_hell)(d_level * a0){
append("find_hell(");
append("p:%d,",a0!=NULL);
append(");");

}
int (find_mac)(struct monst * a0){
append("find_mac(");
append("m:%d,",monid(a0));
append(");");
return options[107];
}
void (float_vs_flight)(void){
append("float_vs_flight(");
append(");");

}
boolean (flooreffects)(struct obj * a0,coordxy a1,coordxy a2,const char * a3){
append("flooreffects(");
append("o:%d,",objid(a0));
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append("s:%s,",a3?a3:"(null)");
append(");");
return options[109];
}
void (fracture_rock)(struct obj * a0){
append("fracture_rock(");
append("o:%d,",objid(a0));
append(");");

}
void (get_level)(d_level * a0,int a1){
append("get_level(");
append("p:%d,",a0!=NULL);
append("i:%lld,",(long long)a1);
append(");");

}
boolean (get_obj_location)(struct obj * a0,coordxy * a1,coordxy * a2,int a3){
append("get_obj_location(");
append("o:%d,",objid(a0));
append("p:%d,",a1!=NULL);
append("p:%d,",a2!=NULL);
append("i:%lld,",(long long)a3);
append(");");
return options[112];
}
int (getdir)(const char * a0){
append("getdir(");
append("s:%s,",a0?a0:"(null)");
append(");");
return options[113];
}
struct obj * (getobj)(const char * a0,int (*a1)(struct obj *),unsigned int a2){
append("getobj(");
append("s:%s,",a0?a0:"(null)");
append("p:%d,",a1!=NULL);
append("i:%lld,",(long long)a2);
append(");");
return options[114]?&objects_fixture[0]:NULL;
}
const char * (gloves_simple_name)(struct obj * a0){
append("gloves_simple_name(");
append("o:%d,",objid(a0));
append(");");
return "fixture";
}
boolean (goodpos)(coordxy a0,coordxy a1,struct monst * a2,mmflags_nht a3){
append("goodpos(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("m:%d,",monid(a2));
append("i:%lld,",(long long)a3);
append(");");
return options[116];
}
boolean (hard_helmet)(struct obj * a0){
append("hard_helmet(");
append("o:%d,",objid(a0));
append(");");
return options[117];
}
boolean (has_ceiling)(d_level * a0){
append("has_ceiling(");
append("p:%d,",a0!=NULL);
append(");");
return options[118];
}
struct obj * (has_magic_key)(struct monst * a0){
append("has_magic_key(");
append("m:%d,",monid(a0));
append(");");
return options[119]?&objects_fixture[0]:NULL;
}
const char * (hcolor)(const char * a0){
append("hcolor(");
append("s:%s,",a0?a0:"(null)");
append(");");
return "fixture";
}
const char * (helm_simple_name)(struct obj * a0){
append("helm_simple_name(");
append("o:%d,",objid(a0));
append(");");
return "fixture";
}
boolean (hits_bars)(struct obj ** a0,coordxy a1,coordxy a2,coordxy a3,coordxy a4,int a5,int a6){
append("hits_bars(");
append("p:%d,",a0!=NULL);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append("i:%lld,",(long long)a3);
append("i:%lld,",(long long)a4);
append("i:%lld,",(long long)a5);
append("i:%lld,",(long long)a6);
append(");");
return options[122];
}
const char * (hliquid)(const char * a0){
append("hliquid(");
append("s:%s,",a0?a0:"(null)");
append(");");
return "fixture";
}
char * (ice_descr)(coordxy a0,coordxy a1,char * a2){
append("ice_descr(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("s:%s,",a2?a2:"(null)");
append(");");
return "fixture";
}
void (impact_drop)(struct obj * a0,coordxy a1,coordxy a2,xint16 a3){
append("impact_drop(");
append("o:%d,",objid(a0));
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append("i:%lld,",(long long)a3);
append(");");

}
void (impossible)(const char * a0,...){
va_list ap;va_start(ap,a0);message("impossible",a0,ap);va_end(ap);

}
char * (in_rooms)(coordxy a0,coordxy a1,int a2){
append("in_rooms(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");
return "";
}
void (incr_itimeout)(long * a0,int a1){
append("incr_itimeout(");
append("p:%d,",a0!=NULL);
append("i:%lld,",(long long)a1);
append(");");

}
char (inside_shop)(coordxy a0,coordxy a1){
append("inside_shop(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");
return options[129];
}
int (inv_cnt)(boolean a0){
append("inv_cnt(");
append("i:%lld,",(long long)a0);
append(");");
return options[130];
}
int (inv_weight)(void){
append("inv_weight(");
append(");");
return options[131];
}
boolean (inventory_resistance_check)(int a0){
append("inventory_resistance_check(");
append("i:%lld,",(long long)a0);
append(");");
return options[132];
}
boolean (is_art)(struct obj * a0,int a1){
append("is_art(");
append("o:%d,",objid(a0));
append("i:%lld,",(long long)a1);
append(");");
return a0?a0->oartifact:0;
}
int (is_drawbridge_wall)(coordxy a0,coordxy a1){
append("is_drawbridge_wall(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");
return options[134];
}
boolean (is_fainted)(void){
append("is_fainted(");
append(");");
return options[135];
}
boolean (is_flammable)(struct obj * a0){
append("is_flammable(");
append("o:%d,",objid(a0));
append(");");
return a0&&objects[a0->otyp].oc_material==CLOTH;
}
boolean (is_ice)(coordxy a0,coordxy a1){
append("is_ice(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");
return options[137];
}
boolean (is_lava)(coordxy a0,coordxy a1){
append("is_lava(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");
return options[138];
}
boolean (is_pool)(coordxy a0,coordxy a1){
append("is_pool(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");
return options[139];
}
boolean (is_pool_or_lava)(coordxy a0,coordxy a1){
append("is_pool_or_lava(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");
return options[140];
}
boolean (is_quest_artifact)(struct obj * a0){
append("is_quest_artifact(");
append("o:%d,",objid(a0));
append(");");
return options[141];
}
boolean (is_rottable)(struct obj * a0){
append("is_rottable(");
append("o:%d,",objid(a0));
append(");");
return a0&&objects[a0->otyp].oc_material==WOOD;
}
boolean (is_waterwall)(coordxy a0,coordxy a1){
append("is_waterwall(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");
return options[143];
}
int (isok)(coordxy a0,coordxy a1){
append("isok(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");
return a0>0&&a0<COLNO&&a1>=0&&a1<ROWNO;
}
char * (just_an)(char * a0,const char * a1){
append("just_an(");
append("s:%s,",a0?a0:"(null)");
append("s:%s,",a1?a1:"(null)");
append(");");
strcpy(a0,strchr("aefhilmnosx",tolower((unsigned char)*a1))?"an ":"a ");return a0;
}
void (killed)(struct monst * a0){
append("killed(");
append("m:%d,",monid(a0));
append(");");

}
char * (lcase)(char * a0){
append("lcase(");
append("s:%s,",a0?a0:"(null)");
append(");");
for(char*p=a0;*p;p++)if(*p>='A'&&*p<='Z')*p+=32;return a0;
}
xint16 (level_difficulty)(void){
append("level_difficulty(");
append(");");
return options[148];
}
void (level_tele_trap)(struct trap * a0,unsigned int a1){
append("level_tele_trap(");
if(a0)append("t:%d:%d:%d,",a0->tx,a0->ty,a0->ttyp);else append("t:null,");
append("i:%lld,",(long long)a1);
append(");");

}
boolean (linedup)(coordxy a0,coordxy a1,coordxy a2,coordxy a3,int a4){
append("linedup(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append("i:%lld,",(long long)a3);
append("i:%lld,",(long long)a4);
append(");");
return options[150];
}
void (liquid_flow)(coordxy a0,coordxy a1,schar a2,struct trap * a3,const char * a4){
append("liquid_flow(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
if(a3)append("t:%d:%d:%d,",a3->tx,a3->ty,a3->ttyp);else append("t:null,");
append("s:%s,",a4?a4:"(null)");
append(");");

}
void (livelog_printf)(long a0,const char * a1,...){
va_list ap;va_start(ap,a1);message("livelog_printf",a1,ap);va_end(ap);

}
void (losehp)(int a0,const char * a1,schar a2){
append("losehp(");
append("i:%lld,",(long long)a0);
append("s:%s,",a1?a1:"(null)");
append("i:%lld,",(long long)a2);
append(");");
u.uhp-=a0;
}
void (losexp)(const char * a0){
append("losexp(");
append("s:%s,",a0?a0:"(null)");
append(");");

}
struct obj * (m_carrying)(struct monst * a0,int a1){
append("m_carrying(");
append("m:%d,",monid(a0));
append("i:%lld,",(long long)a1);
append(");");
return options[155]?&objects_fixture[0]:NULL;
}
void (m_dowear)(struct monst * a0,boolean a1){
append("m_dowear(");
append("m:%d,",monid(a0));
append("i:%lld,",(long long)a1);
append(");");

}
boolean (m_in_air)(struct monst * a0){
append("m_in_air(");
append("m:%d,",monid(a0));
append(");");
return options[157];
}
void (make_angry_shk)(struct monst * a0,coordxy a1,coordxy a2){
append("make_angry_shk(");
append("m:%d,",monid(a0));
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");

}
void (make_blinded)(long a0,boolean a1){
append("make_blinded(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");

}
boolean (make_hallucinated)(long a0,boolean a1,long a2){
append("make_hallucinated(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");
return options[160];
}
void (make_stunned)(long a0,boolean a1){
append("make_stunned(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");

}
struct monst * (makemon)(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){
append("makemon(");
append("pm:%d,",pmid(a0));
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append("i:%lld,",(long long)a3);
append(");");
if(!options[162])return NULL;monsters_fixture[0].data=a0;monsters_fixture[0].mx=a1;monsters_fixture[0].my=a2;return &monsters_fixture[0];
}
char * (makeplural)(const char * a0){
append("makeplural(");
append("s:%s,",a0?a0:"(null)");
append(");");
return "fixture";
}
void (map_invisible)(coordxy a0,coordxy a1){
append("map_invisible(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");

}
void (map_trap)(struct trap * a0,int a1){
append("map_trap(");
if(a0)append("t:%d:%d:%d,",a0->tx,a0->ty,a0->ttyp);else append("t:null,");
append("i:%lld,",(long long)a1);
append(");");

}
void (maybe_dunk_boulders)(coordxy a0,coordxy a1){
append("maybe_dunk_boulders(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");

}
void (maybe_unhide_at)(coordxy a0,coordxy a1){
append("maybe_unhide_at(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");

}
const char * (mbodypart)(struct monst * a0,int a1){
append("mbodypart(");
append("m:%d,",monid(a0));
append("i:%lld,",(long long)a1);
append(");");
return "fixture";
}
void (melt_ice)(coordxy a0,coordxy a1,const char * a2){
append("melt_ice(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("s:%s,",a2?a2:"(null)");
append(");");

}
int (minuhpmax)(int a0){
append("minuhpmax(");
append("i:%lld,",(long long)a0);
append(");");
return options[170];
}
struct obj * (mkcorpstat)(int a0,struct monst * a1,struct permonst * a2,coordxy a3,coordxy a4,unsigned int a5){
append("mkcorpstat(");
append("i:%lld,",(long long)a0);
append("m:%d,",monid(a1));
append("pm:%d,",pmid(a2));
append("i:%lld,",(long long)a3);
append("i:%lld,",(long long)a4);
append("i:%lld,",(long long)a5);
append(");");
objects_fixture[1].otyp=a0;objects_fixture[1].oclass=objects[a0].oc_class;objects_fixture[1].corpsenm=PM_HUMAN;return &objects_fixture[1];
}
struct obj * (mksobj)(int a0,boolean a1,boolean a2){
append("mksobj(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");
objects_fixture[1].otyp=a0;objects_fixture[1].oclass=objects[a0].oc_class;objects_fixture[1].corpsenm=PM_HUMAN;return &objects_fixture[1];
}
int (mlevel_tele_trap)(struct monst * a0,struct trap * a1,boolean a2,int a3){
append("mlevel_tele_trap(");
append("m:%d,",monid(a0));
if(a1)append("t:%d:%d:%d,",a1->tx,a1->ty,a1->ttyp);else append("t:null,");
append("i:%lld,",(long long)a2);
append("i:%lld,",(long long)a3);
append(");");
return options[173];
}
struct obj * (mlifesaver)(struct monst * a0){
append("mlifesaver(");
append("m:%d,",monid(a0));
append(");");
return options[174]?&objects_fixture[0]:NULL;
}
void (mon_adjust_speed)(struct monst * a0,int a1,struct obj * a2){
append("mon_adjust_speed(");
append("m:%d,",monid(a0));
append("i:%lld,",(long long)a1);
append("o:%d,",objid(a2));
append(");");

}
int (mon_has_amulet)(struct monst * a0){
append("mon_has_amulet(");
append("m:%d,",monid(a0));
append(");");
return options[176];
}
boolean (mon_knows_traps)(struct monst * a0,int a1){
append("mon_knows_traps(");
append("m:%d,",monid(a0));
append("i:%lld,",(long long)a1);
append(");");
return options[177];
}
void (mon_learns_traps)(struct monst * a0,int a1){
append("mon_learns_traps(");
append("m:%d,",monid(a0));
append("i:%lld,",(long long)a1);
append(");");

}
char * (mon_nam)(struct monst * a0){
append("mon_nam(");
append("m:%d,",monid(a0));
append(");");
return "fixture";
}
const char * (mon_pmname)(struct monst * a0){
append("mon_pmname(");
append("m:%d,",monid(a0));
append(");");
return "fixture";
}
void (mon_to_stone)(struct monst * a0){
append("mon_to_stone(");
append("m:%d,",monid(a0));
append(");");

}
void (mongone)(struct monst * a0){
append("mongone(");
append("m:%d,",monid(a0));
append(");");

}
void (monkilled)(struct monst * a0,const char * a1,int a2){
append("monkilled(");
append("m:%d,",monid(a0));
append("s:%s,",a1?a1:"(null)");
append("i:%lld,",(long long)a2);
append(");");

}
void (mons_see_trap)(struct trap * a0){
append("mons_see_trap(");
if(a0)append("t:%d:%d:%d,",a0->tx,a0->ty,a0->ttyp);else append("t:null,");
append(");");

}
void (monstone)(struct monst * a0){
append("monstone(");
append("m:%d,",monid(a0));
append(");");

}
void (monstseesu)(unsigned long a0){
append("monstseesu(");
append("u:%llu,",(unsigned long long)a0);
append(");");

}
void (monstunseesu)(unsigned long a0){
append("monstunseesu(");
append("u:%llu,",(unsigned long long)a0);
append(");");

}
struct monst * (montraits)(struct obj * a0,coord * a1,boolean a2){
append("montraits(");
append("o:%d,",objid(a0));
append("p:%d,",a1!=NULL);
append("i:%lld,",(long long)a2);
append(");");
return options[188]?&monsters_fixture[0]:NULL;
}
void (more_experienced)(int a0,int a1){
append("more_experienced(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");

}
void (move_bc)(int a0,int a1,coordxy a2,coordxy a3,coordxy a4,coordxy a5){
append("move_bc(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append("i:%lld,",(long long)a3);
append("i:%lld,",(long long)a4);
append("i:%lld,",(long long)a5);
append(");");

}
void (movobj)(struct obj * a0,coordxy a1,coordxy a2){
append("movobj(");
append("o:%d,",objid(a0));
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");

}
int (mpickobj)(struct monst * a0,struct obj * a1){
append("mpickobj(");
append("m:%d,",monid(a0));
append("o:%d,",objid(a1));
append(");");
return options[192];
}
void (mtele_trap)(struct monst * a0,struct trap * a1,int a2){
append("mtele_trap(");
append("m:%d,",monid(a0));
if(a1)append("t:%d:%d:%d,",a1->tx,a1->ty,a1->ttyp);else append("t:null,");
append("i:%lld,",(long long)a2);
append(");");

}
void (mwepgone)(struct monst * a0){
append("mwepgone(");
append("m:%d,",monid(a0));
append(");");

}
int (near_capacity)(void){
append("near_capacity(");
append(");");
return options[195];
}
int (newcham)(struct monst * a0,struct permonst * a1,unsigned int a2){
append("newcham(");
append("m:%d,",monid(a0));
append("pm:%d,",pmid(a1));
append("i:%lld,",(long long)a2);
append(");");
return options[196];
}
void (newexplevel)(void){
append("newexplevel(");
append(");");

}
void (newsym)(coordxy a0,coordxy a1){
append("newsym(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");

}
boolean (next_to_u)(void){
append("next_to_u(");
append(");");
return options[199];
}
void (nh_snprintf)(const char * a0,int a1,char * a2,size_t a3,const char * a4,...){
va_list ap;va_start(ap,a4);message("nh_snprintf",a4,ap);va_end(ap);

}
char * (noit_Monnam)(struct monst * a0){
append("noit_Monnam(");
append("m:%d,",monid(a0));
append(");");
return "fixture";
}
void (nomul)(int a0){
append("nomul(");
append("i:%lld,",(long long)a0);
append(");");

}
boolean (noteleport_level)(struct monst * a0){
append("noteleport_level(");
append("m:%d,",monid(a0));
append(");");
return options[203];
}
int (number_leashed)(void){
append("number_leashed(");
append(");");
return options[204];
}
struct obj * (nxtobj)(struct obj * a0,int a1,boolean a2){
append("nxtobj(");
append("o:%d,",objid(a0));
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");
return options[205]?&objects_fixture[0]:NULL;
}
void (obfree)(struct obj * a0,struct obj * a1){
append("obfree(");
append("o:%d,",objid(a0));
append("o:%d,",objid(a1));
append(");");

}
void (obj_extract_self)(struct obj * a0){
append("obj_extract_self(");
append("o:%d,",objid(a0));
append(");");

}
void (obj_ice_effects)(coordxy a0,coordxy a1,boolean a2){
append("obj_ice_effects(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");

}
const char * (obj_pmname)(struct obj * a0){
append("obj_pmname(");
append("o:%d,",objid(a0));
append(");");
return "fixture";
}
boolean (obj_resists)(struct obj * a0,int a1,int a2){
append("obj_resists(");
append("o:%d,",objid(a0));
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");
return options[210];
}
void (observe_object)(struct obj * a0){
append("observe_object(");
append("o:%d,",objid(a0));
append(");");

}
boolean (ohitmon)(struct monst * a0,struct obj * a1,int a2,boolean a3){
append("ohitmon(");
append("m:%d,",monid(a0));
append("o:%d,",objid(a1));
append("i:%lld,",(long long)a2);
append("i:%lld,",(long long)a3);
append(");");
return options[212];
}
boolean (on_level)(d_level * a0,d_level * a1){
append("on_level(");
append("p:%d,",a0!=NULL);
append("p:%d,",a1!=NULL);
append(");");
return a0->dnum==a1->dnum&&a0->dlevel==a1->dlevel;
}
const char * (ordin)(int a0){
append("ordin(");
append("i:%lld,",(long long)a0);
append(");");
return "fixture";
}
char * (otense)(struct obj * a0,const char * a1){
append("otense(");
append("o:%d,",objid(a0));
append("s:%s,",a1?a1:"(null)");
append(");");
return "fixture";
}
void (panic)(const char * a0,...){
va_list ap;va_start(ap,a0);message("panic",a0,ap);va_end(ap);
probe_js_fatal("panic");__builtin_unreachable();
}
int (pickup)(int a0){
append("pickup(");
append("i:%lld,",(long long)a0);
append(");");
return options[217];
}
void (place_object)(struct obj * a0,coordxy a1,coordxy a2){
append("place_object(");
append("o:%d,",objid(a0));
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");

}
void (placebc)(void){
append("placebc(");
append(");");

}
void (pline)(const char * a0,...){
va_list ap;va_start(ap,a0);message("pline",a0,ap);va_end(ap);

}
void (pline_The)(const char * a0,...){
va_list ap;va_start(ap,a0);message("pline_The",a0,ap);va_end(ap);

}
void (pline_mon)(struct monst * a0,const char * a1,...){
va_list ap;va_start(ap,a1);message("pline_mon",a1,ap);va_end(ap);

}
void (pline_xy)(coordxy a0,coordxy a1,const char * a2,...){
va_list ap;va_start(ap,a2);message("pline_xy",a2,ap);va_end(ap);

}
void (poisoned)(const char * a0,int a1,const char * a2,int a3,boolean a4){
append("poisoned(");
append("s:%s,",a0?a0:"(null)");
append("i:%lld,",(long long)a1);
append("s:%s,",a2?a2:"(null)");
append("i:%lld,",(long long)a3);
append("i:%lld,",(long long)a4);
append(");");

}
struct obj * (poly_obj)(struct obj * a0,int a1){
append("poly_obj(");
append("o:%d,",objid(a0));
append("i:%lld,",(long long)a1);
append(");");
return options[225]?&objects_fixture[1]:NULL;
}
boolean (poly_when_stoned)(struct permonst * a0){
append("poly_when_stoned(");
append("pm:%d,",pmid(a0));
append(");");
return options[226];
}
int (polymon)(int a0){
append("polymon(");
append("i:%lld,",(long long)a0);
append(");");
return options[227];
}
void (polyself)(int a0){
append("polyself(");
append("i:%lld,",(long long)a0);
append(");");

}
void (prinv)(const char * a0,struct obj * a1,long a2){
append("prinv(");
append("s:%s,",a0?a0:"(null)");
append("o:%d,",objid(a1));
append("i:%lld,",(long long)a2);
append(");");

}
short (quest_info)(int a0){
append("quest_info(");
append("i:%lld,",(long long)a0);
append(");");
return options[230];
}
int (random_teleport_level)(void){
append("random_teleport_level(");
append(");");
return options[231];
}
const char * (rank_of)(int a0,short a1,boolean a2){
append("rank_of(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");
return "fixture";
}
void (recalc_block_point)(coordxy a0,coordxy a1){
append("recalc_block_point(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");

}
void (remove_worn_item)(struct obj * a0,boolean a1){
append("remove_worn_item(");
append("o:%d,",objid(a0));
append("i:%lld,",(long long)a1);
append(");");

}
void (reset_faint)(void){
append("reset_faint(");
append(");");

}
int (resist)(struct monst * a0,char a1,int a2,int a3){
append("resist(");
append("m:%d,",monid(a0));
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append("i:%lld,",(long long)a3);
append(");");
return options[236];
}
boolean (resists_blnd)(struct monst * a0){
append("resists_blnd(");
append("m:%d,",monid(a0));
append(");");
return options[237];
}
boolean (resists_magm)(struct monst * a0){
append("resists_magm(");
append("m:%d,",monid(a0));
append(");");
return options[238];
}
void (rider_cant_reach)(void){
append("rider_cant_reach(");
append(");");

}
boolean (rloco)(struct obj * a0){
append("rloco(");
append("o:%d,",objid(a0));
append(");");
return options[240];
}
int (rn2)(int a0){
append("rn2(");
append("i:%lld,",(long long)a0);
append(");");
int v=random_(a0);append("draw:%d;",v);return v;
}
int (rn2_on_display_rng)(int a0){
append("rn2_on_display_rng(");
append("i:%lld,",(long long)a0);
append(");");
int v=random_(a0);append("draw:%d;",v);return v;
}
int (rnd)(int a0){
append("rnd(");
append("i:%lld,",(long long)a0);
append(");");
int v=random_(a0)+1;append("draw:%d;",v);return v;
}
const char * (rndcolor)(void){
append("rndcolor(");
append(");");
return "fixture";
}
char * (rndmonnam)(char * a0){
append("rndmonnam(");
append("s:%s,",a0?a0:"(null)");
append(");");
return "fixture";
}
int (rndmonnum_adj)(int a0,int a1){
append("rndmonnum_adj(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");
return options[246];
}
boolean (rng_log_enabled)(void){
append("rng_log_enabled(");
append(");");
return options[499];
}
void (rng_log_set_caller)(const char * a0,int a1,const char * a2){
append("rng_log_set_caller(");
append("s:%s,",a0?a0:"(null)");
append("i:%lld,",(long long)a1);
append("s:%s,",a2?a2:"(null)");
append(");");
event();
}
int (rnl)(int a0){
append("rnl(");
append("i:%lld,",(long long)a0);
append(");");
int v=random_(a0);append("draw:%d;",v);return v;
}
char * (s_suffix)(const char * a0){
append("s_suffix(");
append("s:%s,",a0?a0:"(null)");
append(");");
return "fixture";
}
char * (safe_qbuf)(char * a0,const char * a1,const char * a2,struct obj * a3,char *(*a4)(struct obj *),char *(*a5)(struct obj *),const char * a6){
append("safe_qbuf(");
append("s:%s,",a0?a0:"(null)");
append("s:%s,",a1?a1:"(null)");
append("s:%s,",a2?a2:"(null)");
append("o:%d,",objid(a3));
append("p:%d,",a4!=NULL);
append("p:%d,",a5!=NULL);
append("s:%s,",a6?a6:"(null)");
append(");");
return "fixture";
}
boolean (safe_teleds)(int a0){
append("safe_teleds(");
append("i:%lld,",(long long)a0);
append(");");
return options[252];
}
long (scatter)(coordxy a0,coordxy a1,int a2,unsigned int a3,struct obj * a4){
append("scatter(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append("i:%lld,",(long long)a3);
append("o:%d,",objid(a4));
append(");");
return options[253];
}
void (schedule_goto)(d_level * a0,int a1,const char * a2,const char * a3){
append("schedule_goto(");
append("p:%d,",a0!=NULL);
append("i:%lld,",(long long)a1);
append("s:%s,",a2?a2:"(null)");
append("s:%s,",a3?a3:"(null)");
append(");");

}
void (seemimic)(struct monst * a0){
append("seemimic(");
append("m:%d,",monid(a0));
append(");");

}
int (seffects)(struct obj * a0){
append("seffects(");
append("o:%d,",objid(a0));
append(");");
return options[256];
}
void (self_invis_message)(void){
append("self_invis_message(");
append(");");

}
void (sellobj)(struct obj * a0,coordxy a1,coordxy a2){
append("sellobj(");
append("o:%d,",objid(a0));
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");

}
int (sensemon)(struct monst * a0){
append("sensemon(");
append("m:%d,",monid(a0));
append(");");
return options[259];
}
void (set_itimeout)(long * a0,long a1){
append("set_itimeout(");
append("p:%d,",a0!=NULL);
append("i:%lld,",(long long)a1);
append(");");

}
boolean (set_levltyp)(coordxy a0,coordxy a1,schar a2){
append("set_levltyp(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");
return options[261];svl.level.locations[a0][a1].typ=a2;
}
void (set_malign)(struct monst * a0){
append("set_malign(");
append("m:%d,",monid(a0));
append(");");

}
void (set_msg_xy)(coordxy a0,coordxy a1){
append("set_msg_xy(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");

}
void (set_uinwater)(int a0){
append("set_uinwater(");
append("i:%lld,",(long long)a0);
append(");");

}
void (set_ustuck)(struct monst * a0){
append("set_ustuck(");
append("m:%d,",monid(a0));
append(");");
u.ustuck=a0;
}
void (set_wounded_legs)(long a0,int a1){
append("set_wounded_legs(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");

}
void (setmangry)(struct monst * a0,boolean a1){
append("setmangry(");
append("m:%d,",monid(a0));
append("i:%lld,",(long long)a1);
append(");");

}
void (setnotworn)(struct obj * a0){
append("setnotworn(");
append("o:%d,",objid(a0));
append(");");

}
void (setuhpmax)(int a0,boolean a1){
append("setuhpmax(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");

}
int (sgn)(int a0){
append("sgn(");
append("i:%lld,",(long long)a0);
append(");");
return(a0>0)-(a0<0);
}
void (shieldeff)(coordxy a0,coordxy a1){
append("shieldeff(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");

}
void (shieldeff_mon)(struct monst * a0){
append("shieldeff_mon(");
append("m:%d,",monid(a0));
append(");");

}
boolean (ship_object)(struct obj * a0,coordxy a1,coordxy a2,boolean a3){
append("ship_object(");
append("o:%d,",objid(a0));
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append("i:%lld,",(long long)a3);
append(");");
return options[273];
}
char * (shk_your)(char * a0,struct obj * a1){
append("shk_your(");
append("s:%s,",a0?a0:"(null)");
append("o:%d,",objid(a1));
append(");");
return "fixture";
}
struct monst * (shop_keeper)(char a0){
append("shop_keeper(");
append("i:%lld,",(long long)a0);
append(");");
return options[275]?&monsters_fixture[0]:NULL;
}
void (shopdig)(int a0){
append("shopdig(");
append("i:%lld,",(long long)a0);
append(");");

}
char * (simpleonames)(struct obj * a0){
append("simpleonames(");
append("o:%d,",objid(a0));
append(");");
return "fixture";
}
boolean (single_level_branch)(d_level * a0){
append("single_level_branch(");
append("p:%d,",a0!=NULL);
append(");");
return options[278];
}
int (sleep_monst)(struct monst * a0,int a1,int a2){
append("sleep_monst(");
append("m:%d,",monid(a0));
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");
return options[279];
}
struct obj * (sobj_at)(int a0,coordxy a1,coordxy a2){
append("sobj_at(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");
return options[280]&&objects_fixture[0].otyp==a0&&objects_fixture[0].ox==a1&&objects_fixture[0].oy==a2?&objects_fixture[0]:NULL;
}
boolean (splash_lit)(struct obj * a0){
append("splash_lit(");
append("o:%d,",objid(a0));
append(");");
return options[281];
}
struct monst * (split_mon)(struct monst * a0,struct monst * a1){
append("split_mon(");
append("m:%d,",monid(a0));
append("m:%d,",monid(a1));
append(");");
return options[282]?&monsters_fixture[0]:NULL;
}
struct obj * (splitobj)(struct obj * a0,long a1){
append("splitobj(");
append("o:%d,",objid(a0));
append("i:%lld,",(long long)a1);
append(");");
objects_fixture[1]=*a0;objects_fixture[1].o_id=101;objects_fixture[1].quan=a1;a0->quan-=a1;return &objects_fixture[1];
}
void (spot_checks)(coordxy a0,coordxy a1,schar a2){
append("spot_checks(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");

}
void (spot_stop_timers)(coordxy a0,coordxy a1,short a2){
append("spot_stop_timers(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");

}
void (spoteffects)(boolean a0){
append("spoteffects(");
append("i:%lld,",(long long)a0);
append(");");

}
void (stackobj)(struct obj * a0){
append("stackobj(");
append("o:%d,",objid(a0));
append(");");

}
const char * (stagger)(const struct permonst * a0,const char * a1){
append("stagger(");
append("pm:%d,",pmid(a0));
append("s:%s,",a1?a1:"(null)");
append(");");
return "fixture";
}
boolean (sticks)(struct permonst * a0){
append("sticks(");
append("pm:%d,",pmid(a0));
append(");");
return options[289];
}
long (stolen_value)(struct obj * a0,coordxy a1,coordxy a2,boolean a3,boolean a4){
append("stolen_value(");
append("o:%d,",objid(a0));
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append("i:%lld,",(long long)a3);
append("i:%lld,",(long long)a4);
append(");");
return options[290];
}
void (stop_occupation)(void){
append("stop_occupation(");
append(");");

}
int (strncmpi)(const char * a0,const char * a1,int a2){
append("strncmpi(");
append("s:%s,",a0?a0:"(null)");
append("s:%s,",a1?a1:"(null)");
append("i:%lld,",(long long)a2);
append(");");
return strncasecmp(a0,a1,a2);
}
char * (strsubst)(char * a0,const char * a1,const char * a2){
append("strsubst(");
append("s:%s,",a0?a0:"(null)");
append("s:%s,",a1?a1:"(null)");
append("s:%s,",a2?a2:"(null)");
append(");");
return "fixture";
}
boolean (stumble_on_door_mimic)(coordxy a0,coordxy a1){
append("stumble_on_door_mimic(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");
return options[294];
}
void (stumble_onto_mimic)(struct monst * a0){
append("stumble_onto_mimic(");
append("m:%d,",monid(a0));
append(");");

}
const char * (suit_simple_name)(struct obj * a0){
append("suit_simple_name(");
append("o:%d,",objid(a0));
append(");");
return "fixture";
}
const char * (surface)(coordxy a0,coordxy a1){
append("surface(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");
return "fixture";
}
boolean (tamedog)(struct monst * a0,struct obj * a1,boolean a2){
append("tamedog(");
append("m:%d,",monid(a0));
append("o:%d,",objid(a1));
append("i:%lld,",(long long)a2);
append(");");
return options[298];
}
void (tele_trap)(struct trap * a0){
append("tele_trap(");
if(a0)append("t:%d:%d:%d,",a0->tx,a0->ty,a0->ttyp);else append("t:null,");
append(");");

}
void (teleds)(coordxy a0,coordxy a1,int a2){
append("teleds(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");

}
boolean (test_move)(coordxy a0,coordxy a1,coordxy a2,coordxy a3,int a4){
append("test_move(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append("i:%lld,",(long long)a3);
append("i:%lld,",(long long)a4);
append(");");
return options[301];
}
char * (the)(const char * a0){
append("the(");
append("s:%s,",a0?a0:"(null)");
append(");");
return "fixture";
}
int (thitu)(int a0,int a1,struct obj ** a2,const char * a3){
append("thitu(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("p:%d,",a2!=NULL);
append("s:%s,",a3?a3:"(null)");
append(");");
return options[303];
}
void (tmp_at)(coordxy a0,coordxy a1){
append("tmp_at(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");

}
const char * (u_locomotion)(const char * a0){
append("u_locomotion(");
append("s:%s,",a0?a0:"(null)");
append(");");
return "fixture";
}
void (u_on_newpos)(coordxy a0,coordxy a1){
append("u_on_newpos(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");

}
void (unblock_point)(int a0,int a1){
append("unblock_point(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");

}
void (under_water)(int a0){
append("under_water(");
append("i:%lld,",(long long)a0);
append(");");

}
boolean (undiscovered_artifact)(xint16 a0){
append("undiscovered_artifact(");
append("i:%lld,",(long long)a0);
append(");");
return options[309];
}
void (unearth_objs)(int a0,int a1){
append("unearth_objs(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");

}
void (unleash_all)(void){
append("unleash_all(");
append(");");

}
void (unmul)(const char * a0){
append("unmul(");
append("s:%s,",a0?a0:"(null)");
append(");");

}
void (unplacebc)(void){
append("unplacebc(");
append(");");

}
void (unpunish)(void){
append("unpunish(");
append(");");

}
void (update_inventory)(void){
append("update_inventory(");
append(");");

}
void (update_lastseentyp)(coordxy a0,coordxy a1){
append("update_lastseentyp(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");

}
void (update_mon_extrinsics)(struct monst * a0,struct obj * a1,boolean a2,boolean a3){
append("update_mon_extrinsics(");
append("m:%d,",monid(a0));
append("o:%d,",objid(a1));
append("i:%lld,",(long long)a2);
append("i:%lld,",(long long)a3);
append(");");

}
char * (upstart)(char * a0){
append("upstart(");
append("s:%s,",a0?a0:"(null)");
append(");");
return "fixture";
}
void (urgent_pline)(const char * a0,...){
va_list ap;va_start(ap,a0);message("urgent_pline",a0,ap);va_end(ap);

}
void (useup)(struct obj * a0){
append("useup(");
append("o:%d,",objid(a0));
append(");");

}
void (useupall)(struct obj * a0){
append("useupall(");
append("o:%d,",objid(a0));
append(");");

}
void (uswapwepgone)(void){
append("uswapwepgone(");
append(");");

}
void (uwepgone)(void){
append("uwepgone(");
append(");");

}
boolean (vamp_stone)(struct monst * a0){
append("vamp_stone(");
append("m:%d,",monid(a0));
append(");");
return options[324];
}
void (vision_recalc)(int a0){
append("vision_recalc(");
append("i:%lld,",(long long)a0);
append(");");

}
char * (vtense)(const char * a0,const char * a1){
append("vtense(");
append("s:%s,",a0?a0:"(null)");
append("s:%s,",a1?a1:"(null)");
append(");");
return "fixture";
}
void (wake_nearby)(boolean a0){
append("wake_nearby(");
append("i:%lld,",(long long)a0);
append(");");

}
void (wake_nearto)(coordxy a0,coordxy a1,int a2){
append("wake_nearto(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");

}
void (wakeup)(struct monst * a0,boolean a1){
append("wakeup(");
append("m:%d,",monid(a0));
append("i:%lld,",(long long)a1);
append(");");

}
void (wary_dog)(struct monst * a0,boolean a1){
append("wary_dog(");
append("m:%d,",monid(a0));
append("i:%lld,",(long long)a1);
append(");");

}
const char * (waterbody_name)(coordxy a0,coordxy a1){
append("waterbody_name(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");
return "fixture";
}
int (weight)(struct obj * a0){
append("weight(");
append("o:%d,",objid(a0));
append(");");
return options[332];
}
int (weight_cap)(void){
append("weight_cap(");
append(");");
return options[333];
}
int (welded)(struct obj * a0){
append("welded(");
append("o:%d,",objid(a0));
append(");");
return options[334];
}
void (wet_a_towel)(struct obj * a0,int a1,boolean a2){
append("wet_a_towel(");
append("o:%d,",objid(a0));
append("i:%lld,",(long long)a1);
append("i:%lld,",(long long)a2);
append(");");

}
struct obj * (which_armor)(struct monst * a0,long a1){
append("which_armor(");
append("m:%d,",monid(a0));
append("i:%lld,",(long long)a1);
append(");");
return options[336]&&(objects_fixture[0].owornmask&a1)?&objects_fixture[0]:NULL;
}
char * (x_monnam)(struct monst * a0,int a1,const char * a2,int a3,boolean a4){
append("x_monnam(");
append("m:%d,",monid(a0));
append("i:%lld,",(long long)a1);
append("s:%s,",a2?a2:"(null)");
append("i:%lld,",(long long)a3);
append("i:%lld,",(long long)a4);
append(");");
return "fixture";
}
void (xkilled)(struct monst * a0,int a1){
append("xkilled(");
append("m:%d,",monid(a0));
append("i:%lld,",(long long)a1);
append(");");

}
char * (xname)(struct obj * a0){
append("xname(");
append("o:%d,",objid(a0));
append(");");
return "fixture";
}
int (xytodir)(int a0,int a1){
append("xytodir(");
append("i:%lld,",(long long)a0);
append("i:%lld,",(long long)a1);
append(");");
for(int i=0;i<N_DIRS;i++)if(xdir[i]==a0&&ydir[i]==a1)return i;return DIR_ERR;
}
char * (y_monnam)(struct monst * a0){
append("y_monnam(");
append("m:%d,",monid(a0));
append(");");
return "fixture";
}
char (yn_function)(const char * a0,const char * a1,char a2,boolean a3){
append("yn_function(");
append("s:%s,",a0?a0:"(null)");
append("s:%s,",a1?a1:"(null)");
append("i:%lld,",(long long)a2);
append("i:%lld,",(long long)a3);
append(");");
return options[342];
}
char * (yname)(struct obj * a0){
append("yname(");
append("o:%d,",objid(a0));
append(");");
return "fixture";
}
#pragma clang diagnostic pop
static void fixture_win_display_nhwindow(winid a0,boolean a1){append("win_display_nhwindow;");event();}
static void fixture_win_delay_output(void){append("win_delay_output;");event();}
static void fixture_win_clear_nhwindow(winid a0){append("win_clear_nhwindow;");event();}
#ifdef HYBRID_TRAP
#include "../nethack-c/wasm/tu-fragments/trap-support.c"
#else
#include "../.cache/wasm64-build/tree/src/trap.c"
#endif
#ifdef HYBRID_TRAP
boolean probe_call_burnarmor(struct monst * victim){return teleport_trap_entry_burnarmor(victim);}
#else
boolean probe_call_burnarmor(struct monst * victim){return burnarmor(victim);}
#endif
#ifdef HYBRID_TRAP
int probe_call_erode_obj(struct obj * otmp,const char * ostr,int type,int ef_flags){return teleport_trap_entry_erode_obj(otmp,ostr,type,ef_flags);}
#else
int probe_call_erode_obj(struct obj * otmp,const char * ostr,int type,int ef_flags){return erode_obj(otmp,ostr,type,ef_flags);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_grease_protect(struct obj * otmp,const char * ostr,struct monst * victim){return teleport_trap_entry_grease_protect(otmp,ostr,victim);}
#else
boolean probe_call_grease_protect(struct obj * otmp,const char * ostr,struct monst * victim){return grease_protect(otmp,ostr,victim);}
#endif
#ifdef HYBRID_TRAP
void probe_call_mk_trap_statue(coordxy x,coordxy y){teleport_trap_entry_mk_trap_statue(x,y);}
#else
void probe_call_mk_trap_statue(coordxy x,coordxy y){mk_trap_statue(x,y);}
#endif
#ifdef HYBRID_TRAP
int probe_call_dng_bottom(d_level * lev){return teleport_trap_entry_dng_bottom(lev);}
#else
int probe_call_dng_bottom(d_level * lev){return dng_bottom(lev);}
#endif
#ifdef HYBRID_TRAP
void probe_call_hole_destination(d_level * dst){teleport_trap_entry_hole_destination(dst);}
#else
void probe_call_hole_destination(d_level * dst){hole_destination(dst);}
#endif
#ifdef HYBRID_TRAP
struct trap * probe_call_maketrap(coordxy x,coordxy y,int typ){return teleport_trap_entry_maketrap(x,y,typ);}
#else
struct trap * probe_call_maketrap(coordxy x,coordxy y,int typ){return maketrap(x,y,typ);}
#endif
#ifdef HYBRID_TRAP
d_level * probe_call_clamp_hole_destination(d_level * dlev){return teleport_trap_entry_clamp_hole_destination(dlev);}
#else
d_level * probe_call_clamp_hole_destination(d_level * dlev){return clamp_hole_destination(dlev);}
#endif
#ifdef HYBRID_TRAP
void probe_call_fall_through(boolean td,unsigned int ftflags){teleport_trap_entry_fall_through(td,ftflags);}
#else
void probe_call_fall_through(boolean td,unsigned int ftflags){fall_through(td,ftflags);}
#endif
#ifdef HYBRID_TRAP
struct monst * probe_call_animate_statue(struct obj * statue,coordxy x,coordxy y,int cause,int * fail_reason){return teleport_trap_entry_animate_statue(statue,x,y,cause,fail_reason);}
#else
struct monst * probe_call_animate_statue(struct obj * statue,coordxy x,coordxy y,int cause,int * fail_reason){return animate_statue(statue,x,y,cause,fail_reason);}
#endif
#ifdef HYBRID_TRAP
struct monst * probe_call_activate_statue_trap(struct trap * trap,coordxy x,coordxy y,boolean shatter){return teleport_trap_entry_activate_statue_trap(trap,x,y,shatter);}
#else
struct monst * probe_call_activate_statue_trap(struct trap * trap,coordxy x,coordxy y,boolean shatter){return activate_statue_trap(trap,x,y,shatter);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_keep_saddle_with_steedcorpse(unsigned int steed_mid,struct obj * objchn,struct obj * saddle){return teleport_trap_entry_keep_saddle_with_steedcorpse(steed_mid,objchn,saddle);}
#else
boolean probe_call_keep_saddle_with_steedcorpse(unsigned int steed_mid,struct obj * objchn,struct obj * saddle){return keep_saddle_with_steedcorpse(steed_mid,objchn,saddle);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_mu_maybe_destroy_web(struct monst * mtmp,boolean domsg,struct trap * trap){return teleport_trap_entry_mu_maybe_destroy_web(mtmp,domsg,trap);}
#else
boolean probe_call_mu_maybe_destroy_web(struct monst * mtmp,boolean domsg,struct trap * trap){return mu_maybe_destroy_web(mtmp,domsg,trap);}
#endif
#ifdef HYBRID_TRAP
struct obj * probe_call_t_missile(int otyp,struct trap * trap){return teleport_trap_entry_t_missile(otyp,trap);}
#else
struct obj * probe_call_t_missile(int otyp,struct trap * trap){return t_missile(otyp,trap);}
#endif
#ifdef HYBRID_TRAP
void probe_call_set_utrap(unsigned int tim,unsigned int typ){teleport_trap_entry_set_utrap(tim,typ);}
#else
void probe_call_set_utrap(unsigned int tim,unsigned int typ){set_utrap(tim,typ);}
#endif
#ifdef HYBRID_TRAP
void probe_call_reset_utrap(boolean msg){teleport_trap_entry_reset_utrap(msg);}
#else
void probe_call_reset_utrap(boolean msg){reset_utrap(msg);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_floor_trigger(int ttyp){return teleport_trap_entry_floor_trigger(ttyp);}
#else
boolean probe_call_floor_trigger(int ttyp){return floor_trigger(ttyp);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_check_in_air(struct monst * mtmp,unsigned int trflags){return teleport_trap_entry_check_in_air(mtmp,trflags);}
#else
boolean probe_call_check_in_air(struct monst * mtmp,unsigned int trflags){return check_in_air(mtmp,trflags);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_wearing_iron_shoes(struct monst * mtmp){return teleport_trap_entry_wearing_iron_shoes(mtmp);}
#else
boolean probe_call_wearing_iron_shoes(struct monst * mtmp){return wearing_iron_shoes(mtmp);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_m_harmless_trap(struct monst * mtmp,struct trap * ttmp){return teleport_trap_entry_m_harmless_trap(mtmp,ttmp);}
#else
boolean probe_call_m_harmless_trap(struct monst * mtmp,struct trap * ttmp){return m_harmless_trap(mtmp,ttmp);}
#endif
#ifdef HYBRID_TRAP
int probe_call_trapeffect_arrow_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_entry_trapeffect_arrow_trap(mtmp,trap,trflags);}
#else
int probe_call_trapeffect_arrow_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return trapeffect_arrow_trap(mtmp,trap,trflags);}
#endif
#ifdef HYBRID_TRAP
int probe_call_trapeffect_dart_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_entry_trapeffect_dart_trap(mtmp,trap,trflags);}
#else
int probe_call_trapeffect_dart_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return trapeffect_dart_trap(mtmp,trap,trflags);}
#endif
#ifdef HYBRID_TRAP
int probe_call_trapeffect_rocktrap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_entry_trapeffect_rocktrap(mtmp,trap,trflags);}
#else
int probe_call_trapeffect_rocktrap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return trapeffect_rocktrap(mtmp,trap,trflags);}
#endif
#ifdef HYBRID_TRAP
int probe_call_trapeffect_sqky_board(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_entry_trapeffect_sqky_board(mtmp,trap,trflags);}
#else
int probe_call_trapeffect_sqky_board(struct monst * mtmp,struct trap * trap,unsigned int trflags){return trapeffect_sqky_board(mtmp,trap,trflags);}
#endif
#ifdef HYBRID_TRAP
int probe_call_trapeffect_bear_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_entry_trapeffect_bear_trap(mtmp,trap,trflags);}
#else
int probe_call_trapeffect_bear_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return trapeffect_bear_trap(mtmp,trap,trflags);}
#endif
#ifdef HYBRID_TRAP
int probe_call_trapeffect_slp_gas_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_entry_trapeffect_slp_gas_trap(mtmp,trap,trflags);}
#else
int probe_call_trapeffect_slp_gas_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return trapeffect_slp_gas_trap(mtmp,trap,trflags);}
#endif
#ifdef HYBRID_TRAP
int probe_call_trapeffect_rust_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_entry_trapeffect_rust_trap(mtmp,trap,trflags);}
#else
int probe_call_trapeffect_rust_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return trapeffect_rust_trap(mtmp,trap,trflags);}
#endif
#ifdef HYBRID_TRAP
int probe_call_trapeffect_fire_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_entry_trapeffect_fire_trap(mtmp,trap,trflags);}
#else
int probe_call_trapeffect_fire_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return trapeffect_fire_trap(mtmp,trap,trflags);}
#endif
#ifdef HYBRID_TRAP
int probe_call_trapeffect_pit(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_entry_trapeffect_pit(mtmp,trap,trflags);}
#else
int probe_call_trapeffect_pit(struct monst * mtmp,struct trap * trap,unsigned int trflags){return trapeffect_pit(mtmp,trap,trflags);}
#endif
#ifdef HYBRID_TRAP
int probe_call_trapeffect_hole(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_entry_trapeffect_hole(mtmp,trap,trflags);}
#else
int probe_call_trapeffect_hole(struct monst * mtmp,struct trap * trap,unsigned int trflags){return trapeffect_hole(mtmp,trap,trflags);}
#endif
#ifdef HYBRID_TRAP
int probe_call_trapeffect_telep_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_entry_trapeffect_telep_trap(mtmp,trap,trflags);}
#else
int probe_call_trapeffect_telep_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return trapeffect_telep_trap(mtmp,trap,trflags);}
#endif
#ifdef HYBRID_TRAP
int probe_call_trapeffect_level_telep(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_entry_trapeffect_level_telep(mtmp,trap,trflags);}
#else
int probe_call_trapeffect_level_telep(struct monst * mtmp,struct trap * trap,unsigned int trflags){return trapeffect_level_telep(mtmp,trap,trflags);}
#endif
#ifdef HYBRID_TRAP
int probe_call_trapeffect_web(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_entry_trapeffect_web(mtmp,trap,trflags);}
#else
int probe_call_trapeffect_web(struct monst * mtmp,struct trap * trap,unsigned int trflags){return trapeffect_web(mtmp,trap,trflags);}
#endif
#ifdef HYBRID_TRAP
int probe_call_trapeffect_statue_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_entry_trapeffect_statue_trap(mtmp,trap,trflags);}
#else
int probe_call_trapeffect_statue_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return trapeffect_statue_trap(mtmp,trap,trflags);}
#endif
#ifdef HYBRID_TRAP
int probe_call_trapeffect_magic_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_entry_trapeffect_magic_trap(mtmp,trap,trflags);}
#else
int probe_call_trapeffect_magic_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return trapeffect_magic_trap(mtmp,trap,trflags);}
#endif
#ifdef HYBRID_TRAP
int probe_call_trapeffect_anti_magic(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_entry_trapeffect_anti_magic(mtmp,trap,trflags);}
#else
int probe_call_trapeffect_anti_magic(struct monst * mtmp,struct trap * trap,unsigned int trflags){return trapeffect_anti_magic(mtmp,trap,trflags);}
#endif
#ifdef HYBRID_TRAP
int probe_call_trapeffect_poly_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_entry_trapeffect_poly_trap(mtmp,trap,trflags);}
#else
int probe_call_trapeffect_poly_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return trapeffect_poly_trap(mtmp,trap,trflags);}
#endif
#ifdef HYBRID_TRAP
int probe_call_trapeffect_landmine(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_entry_trapeffect_landmine(mtmp,trap,trflags);}
#else
int probe_call_trapeffect_landmine(struct monst * mtmp,struct trap * trap,unsigned int trflags){return trapeffect_landmine(mtmp,trap,trflags);}
#endif
#ifdef HYBRID_TRAP
int probe_call_trapeffect_rolling_boulder_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_entry_trapeffect_rolling_boulder_trap(mtmp,trap,trflags);}
#else
int probe_call_trapeffect_rolling_boulder_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return trapeffect_rolling_boulder_trap(mtmp,trap,trflags);}
#endif
#ifdef HYBRID_TRAP
int probe_call_trapeffect_magic_portal(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_entry_trapeffect_magic_portal(mtmp,trap,trflags);}
#else
int probe_call_trapeffect_magic_portal(struct monst * mtmp,struct trap * trap,unsigned int trflags){return trapeffect_magic_portal(mtmp,trap,trflags);}
#endif
#ifdef HYBRID_TRAP
int probe_call_trapeffect_vibrating_square(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_entry_trapeffect_vibrating_square(mtmp,trap,trflags);}
#else
int probe_call_trapeffect_vibrating_square(struct monst * mtmp,struct trap * trap,unsigned int trflags){return trapeffect_vibrating_square(mtmp,trap,trflags);}
#endif
#ifdef HYBRID_TRAP
int probe_call_immune_to_trap(struct monst * mon,unsigned int ttype){return teleport_trap_entry_immune_to_trap(mon,ttype);}
#else
int probe_call_immune_to_trap(struct monst * mon,unsigned int ttype){return immune_to_trap(mon,ttype);}
#endif
#ifdef HYBRID_TRAP
int probe_call_trapeffect_selector(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_entry_trapeffect_selector(mtmp,trap,trflags);}
#else
int probe_call_trapeffect_selector(struct monst * mtmp,struct trap * trap,unsigned int trflags){return trapeffect_selector(mtmp,trap,trflags);}
#endif
#ifdef HYBRID_TRAP
void probe_call_dotrap(struct trap * trap,unsigned int trflags){teleport_trap_entry_dotrap(trap,trflags);}
#else
void probe_call_dotrap(struct trap * trap,unsigned int trflags){dotrap(trap,trflags);}
#endif
#ifdef HYBRID_TRAP
char * probe_call_trapnote(struct trap * trap,boolean noprefix){return teleport_trap_entry_trapnote(trap,noprefix);}
#else
char * probe_call_trapnote(struct trap * trap,boolean noprefix){return trapnote(trap,noprefix);}
#endif
#ifdef HYBRID_TRAP
int probe_call_choose_trapnote(struct trap * ttmp){return teleport_trap_entry_choose_trapnote(ttmp);}
#else
int probe_call_choose_trapnote(struct trap * ttmp){return choose_trapnote(ttmp);}
#endif
#ifdef HYBRID_TRAP
int probe_call_steedintrap(struct trap * trap,struct obj * otmp){return teleport_trap_entry_steedintrap(trap,otmp);}
#else
int probe_call_steedintrap(struct trap * trap,struct obj * otmp){return steedintrap(trap,otmp);}
#endif
#ifdef HYBRID_TRAP
void probe_call_blow_up_landmine(struct trap * trap){teleport_trap_entry_blow_up_landmine(trap);}
#else
void probe_call_blow_up_landmine(struct trap * trap){blow_up_landmine(trap);}
#endif
#ifdef HYBRID_TRAP
void probe_call_launch_drop_spot(struct obj * obj,coordxy x,coordxy y){teleport_trap_entry_launch_drop_spot(obj,x,y);}
#else
void probe_call_launch_drop_spot(struct obj * obj,coordxy x,coordxy y){launch_drop_spot(obj,x,y);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_launch_in_progress(void){return teleport_trap_entry_launch_in_progress();}
#else
boolean probe_call_launch_in_progress(void){return launch_in_progress();}
#endif
#ifdef HYBRID_TRAP
void probe_call_force_launch_placement(void){teleport_trap_entry_force_launch_placement();}
#else
void probe_call_force_launch_placement(void){force_launch_placement();}
#endif
#ifdef HYBRID_TRAP
int probe_call_launch_obj(short otyp,coordxy x1,coordxy y1,coordxy x2,coordxy y2,int style){return teleport_trap_entry_launch_obj(otyp,x1,y1,x2,y2,style);}
#else
int probe_call_launch_obj(short otyp,coordxy x1,coordxy y1,coordxy x2,coordxy y2,int style){return launch_obj(otyp,x1,y1,x2,y2,style);}
#endif
#ifdef HYBRID_TRAP
void probe_call_seetrap(struct trap * trap){teleport_trap_entry_seetrap(trap);}
#else
void probe_call_seetrap(struct trap * trap){seetrap(trap);}
#endif
#ifdef HYBRID_TRAP
void probe_call_feeltrap(struct trap * trap){teleport_trap_entry_feeltrap(trap);}
#else
void probe_call_feeltrap(struct trap * trap){feeltrap(trap);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_find_random_launch_coord(struct trap * ttmp,coord * cc){return teleport_trap_entry_find_random_launch_coord(ttmp,cc);}
#else
boolean probe_call_find_random_launch_coord(struct trap * ttmp,coord * cc){return find_random_launch_coord(ttmp,cc);}
#endif
#ifdef HYBRID_TRAP
int probe_call_mkroll_launch(struct trap * ttmp,coordxy x,coordxy y,short otyp,long ocount){return teleport_trap_entry_mkroll_launch(ttmp,x,y,otyp,ocount);}
#else
int probe_call_mkroll_launch(struct trap * ttmp,coordxy x,coordxy y,short otyp,long ocount){return mkroll_launch(ttmp,x,y,otyp,ocount);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_isclearpath(coord * cc,int distance,schar dx,schar dy){return teleport_trap_entry_isclearpath(cc,distance,dx,dy);}
#else
boolean probe_call_isclearpath(coord * cc,int distance,schar dx,schar dy){return isclearpath(cc,distance,dx,dy);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_m_easy_escape_pit(struct monst * mtmp){return teleport_trap_entry_m_easy_escape_pit(mtmp);}
#else
boolean probe_call_m_easy_escape_pit(struct monst * mtmp){return m_easy_escape_pit(mtmp);}
#endif
#ifdef HYBRID_TRAP
int probe_call_mintrap(struct monst * mtmp,unsigned int mintrapflags){return teleport_trap_entry_mintrap(mtmp,mintrapflags);}
#else
int probe_call_mintrap(struct monst * mtmp,unsigned int mintrapflags){return mintrap(mtmp,mintrapflags);}
#endif
#ifdef HYBRID_TRAP
void probe_call_instapetrify(const char * str){teleport_trap_entry_instapetrify(str);}
#else
void probe_call_instapetrify(const char * str){instapetrify(str);}
#endif
#ifdef HYBRID_TRAP
void probe_call_minstapetrify(struct monst * mon,boolean byplayer){teleport_trap_entry_minstapetrify(mon,byplayer);}
#else
void probe_call_minstapetrify(struct monst * mon,boolean byplayer){minstapetrify(mon,byplayer);}
#endif
#ifdef HYBRID_TRAP
void probe_call_selftouch(const char * arg){teleport_trap_entry_selftouch(arg);}
#else
void probe_call_selftouch(const char * arg){selftouch(arg);}
#endif
#ifdef HYBRID_TRAP
void probe_call_mselftouch(struct monst * mon,const char * arg,boolean byplayer){teleport_trap_entry_mselftouch(mon,arg,byplayer);}
#else
void probe_call_mselftouch(struct monst * mon,const char * arg,boolean byplayer){mselftouch(mon,arg,byplayer);}
#endif
#ifdef HYBRID_TRAP
void probe_call_float_up(void){teleport_trap_entry_float_up();}
#else
void probe_call_float_up(void){float_up();}
#endif
#ifdef HYBRID_TRAP
void probe_call_fill_pit(coordxy x,coordxy y){teleport_trap_entry_fill_pit(x,y);}
#else
void probe_call_fill_pit(coordxy x,coordxy y){fill_pit(x,y);}
#endif
#ifdef HYBRID_TRAP
int probe_call_float_down(long hmask,long emask){return teleport_trap_entry_float_down(hmask,emask);}
#else
int probe_call_float_down(long hmask,long emask){return float_down(hmask,emask);}
#endif
#ifdef HYBRID_TRAP
void probe_call_climb_pit(void){teleport_trap_entry_climb_pit();}
#else
void probe_call_climb_pit(void){climb_pit();}
#endif
#ifdef HYBRID_TRAP
void probe_call_dofiretrap(struct obj * box){teleport_trap_entry_dofiretrap(box);}
#else
void probe_call_dofiretrap(struct obj * box){dofiretrap(box);}
#endif
#ifdef HYBRID_TRAP
void probe_call_domagictrap(void){teleport_trap_entry_domagictrap();}
#else
void probe_call_domagictrap(void){domagictrap();}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_fire_damage(struct obj * obj,boolean force,coordxy x,coordxy y){return teleport_trap_entry_fire_damage(obj,force,x,y);}
#else
boolean probe_call_fire_damage(struct obj * obj,boolean force,coordxy x,coordxy y){return fire_damage(obj,force,x,y);}
#endif
#ifdef HYBRID_TRAP
int probe_call_fire_damage_chain(struct obj * chain,boolean force,boolean here,coordxy x,coordxy y){return teleport_trap_entry_fire_damage_chain(chain,force,here,x,y);}
#else
int probe_call_fire_damage_chain(struct obj * chain,boolean force,boolean here,coordxy x,coordxy y){return fire_damage_chain(chain,force,here,x,y);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_lava_damage(struct obj * obj,coordxy x,coordxy y){return teleport_trap_entry_lava_damage(obj,x,y);}
#else
boolean probe_call_lava_damage(struct obj * obj,coordxy x,coordxy y){return lava_damage(obj,x,y);}
#endif
#ifdef HYBRID_TRAP
void probe_call_acid_damage(struct obj * obj){teleport_trap_entry_acid_damage(obj);}
#else
void probe_call_acid_damage(struct obj * obj){acid_damage(obj);}
#endif
#ifdef HYBRID_TRAP
void probe_call_pot_acid_damage(struct obj * obj,boolean in_invent,boolean described){teleport_trap_entry_pot_acid_damage(obj,in_invent,described);}
#else
void probe_call_pot_acid_damage(struct obj * obj,boolean in_invent,boolean described){pot_acid_damage(obj,in_invent,described);}
#endif
#ifdef HYBRID_TRAP
int probe_call_water_damage(struct obj * obj,const char * ostr,boolean force){return teleport_trap_entry_water_damage(obj,ostr,force);}
#else
int probe_call_water_damage(struct obj * obj,const char * ostr,boolean force){return water_damage(obj,ostr,force);}
#endif
#ifdef HYBRID_TRAP
void probe_call_water_damage_chain(struct obj * obj,boolean here){teleport_trap_entry_water_damage_chain(obj,here);}
#else
void probe_call_water_damage_chain(struct obj * obj,boolean here){water_damage_chain(obj,here);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_emergency_disrobe(boolean * lostsome){return teleport_trap_entry_emergency_disrobe(lostsome);}
#else
boolean probe_call_emergency_disrobe(boolean * lostsome){return emergency_disrobe(lostsome);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_rnd_nextto_goodpos(coordxy * x,coordxy * y,struct monst * mtmp){return teleport_trap_entry_rnd_nextto_goodpos(x,y,mtmp);}
#else
boolean probe_call_rnd_nextto_goodpos(coordxy * x,coordxy * y,struct monst * mtmp){return rnd_nextto_goodpos(x,y,mtmp);}
#endif
#ifdef HYBRID_TRAP
void probe_call_back_on_ground(boolean rescued){teleport_trap_entry_back_on_ground(rescued);}
#else
void probe_call_back_on_ground(boolean rescued){back_on_ground(rescued);}
#endif
#ifdef HYBRID_TRAP
void probe_call_rescued_from_terrain(int how){teleport_trap_entry_rescued_from_terrain(how);}
#else
void probe_call_rescued_from_terrain(int how){rescued_from_terrain(how);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_drown(void){return teleport_trap_entry_drown();}
#else
boolean probe_call_drown(void){return drown();}
#endif
#ifdef HYBRID_TRAP
void probe_call_drain_en(int n,boolean max_already_drained){teleport_trap_entry_drain_en(n,max_already_drained);}
#else
void probe_call_drain_en(int n,boolean max_already_drained){drain_en(n,max_already_drained);}
#endif
#ifdef HYBRID_TRAP
int probe_call_dountrap(void){return teleport_trap_entry_dountrap();}
#else
int probe_call_dountrap(void){return dountrap();}
#endif
#ifdef HYBRID_TRAP
int probe_call_could_untrap(boolean verbosely,boolean check_floor){return teleport_trap_entry_could_untrap(verbosely,check_floor);}
#else
int probe_call_could_untrap(boolean verbosely,boolean check_floor){return could_untrap(verbosely,check_floor);}
#endif
#ifdef HYBRID_TRAP
int probe_call_untrap_prob(struct trap * ttmp){return teleport_trap_entry_untrap_prob(ttmp);}
#else
int probe_call_untrap_prob(struct trap * ttmp){return untrap_prob(ttmp);}
#endif
#ifdef HYBRID_TRAP
void probe_call_cnv_trap_obj(int otyp,int cnt,struct trap * ttmp,boolean bury_it){teleport_trap_entry_cnv_trap_obj(otyp,cnt,ttmp,bury_it);}
#else
void probe_call_cnv_trap_obj(int otyp,int cnt,struct trap * ttmp,boolean bury_it){cnv_trap_obj(otyp,cnt,ttmp,bury_it);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_into_vs_onto(int traptype){return teleport_trap_entry_into_vs_onto(traptype);}
#else
boolean probe_call_into_vs_onto(int traptype){return into_vs_onto(traptype);}
#endif
#ifdef HYBRID_TRAP
void probe_call_move_into_trap(struct trap * ttmp){teleport_trap_entry_move_into_trap(ttmp);}
#else
void probe_call_move_into_trap(struct trap * ttmp){move_into_trap(ttmp);}
#endif
#ifdef HYBRID_TRAP
int probe_call_try_disarm(struct trap * ttmp,boolean force_failure){return teleport_trap_entry_try_disarm(ttmp,force_failure);}
#else
int probe_call_try_disarm(struct trap * ttmp,boolean force_failure){return try_disarm(ttmp,force_failure);}
#endif
#ifdef HYBRID_TRAP
void probe_call_reward_untrap(struct trap * ttmp,struct monst * mtmp){teleport_trap_entry_reward_untrap(ttmp,mtmp);}
#else
void probe_call_reward_untrap(struct trap * ttmp,struct monst * mtmp){reward_untrap(ttmp,mtmp);}
#endif
#ifdef HYBRID_TRAP
int probe_call_disarm_holdingtrap(struct trap * ttmp){return teleport_trap_entry_disarm_holdingtrap(ttmp);}
#else
int probe_call_disarm_holdingtrap(struct trap * ttmp){return disarm_holdingtrap(ttmp);}
#endif
#ifdef HYBRID_TRAP
int probe_call_disarm_landmine(struct trap * ttmp){return teleport_trap_entry_disarm_landmine(ttmp);}
#else
int probe_call_disarm_landmine(struct trap * ttmp){return disarm_landmine(ttmp);}
#endif
#ifdef HYBRID_TRAP
int probe_call_unsqueak_ok(struct obj * obj){return teleport_trap_entry_unsqueak_ok(obj);}
#else
int probe_call_unsqueak_ok(struct obj * obj){return unsqueak_ok(obj);}
#endif
#ifdef HYBRID_TRAP
int probe_call_disarm_squeaky_board(struct trap * ttmp){return teleport_trap_entry_disarm_squeaky_board(ttmp);}
#else
int probe_call_disarm_squeaky_board(struct trap * ttmp){return disarm_squeaky_board(ttmp);}
#endif
#ifdef HYBRID_TRAP
int probe_call_disarm_shooting_trap(struct trap * ttmp,int otyp){return teleport_trap_entry_disarm_shooting_trap(ttmp,otyp);}
#else
int probe_call_disarm_shooting_trap(struct trap * ttmp,int otyp){return disarm_shooting_trap(ttmp,otyp);}
#endif
#ifdef HYBRID_TRAP
int probe_call_try_lift(struct monst * mtmp,struct trap * ttmp,int xtra_wt,boolean stuff){return teleport_trap_entry_try_lift(mtmp,ttmp,xtra_wt,stuff);}
#else
int probe_call_try_lift(struct monst * mtmp,struct trap * ttmp,int xtra_wt,boolean stuff){return try_lift(mtmp,ttmp,xtra_wt,stuff);}
#endif
#ifdef HYBRID_TRAP
int probe_call_help_monster_out(struct monst * mtmp,struct trap * ttmp){return teleport_trap_entry_help_monster_out(mtmp,ttmp);}
#else
int probe_call_help_monster_out(struct monst * mtmp,struct trap * ttmp){return help_monster_out(mtmp,ttmp);}
#endif
#ifdef HYBRID_TRAP
void probe_call_disarm_box(struct obj * box,boolean force,boolean confused){teleport_trap_entry_disarm_box(box,force,confused);}
#else
void probe_call_disarm_box(struct obj * box,boolean force,boolean confused){disarm_box(box,force,confused);}
#endif
#ifdef HYBRID_TRAP
void probe_call_untrap_box(struct obj * box,boolean force,boolean confused){teleport_trap_entry_untrap_box(box,force,confused);}
#else
void probe_call_untrap_box(struct obj * box,boolean force,boolean confused){untrap_box(box,force,confused);}
#endif
#ifdef HYBRID_TRAP
int probe_call_untrap(boolean force,coordxy rx,coordxy ry,struct obj * container){return teleport_trap_entry_untrap(force,rx,ry,container);}
#else
int probe_call_untrap(boolean force,coordxy rx,coordxy ry,struct obj * container){return untrap(force,rx,ry,container);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_openholdingtrap(struct monst * mon,boolean * noticed){return teleport_trap_entry_openholdingtrap(mon,noticed);}
#else
boolean probe_call_openholdingtrap(struct monst * mon,boolean * noticed){return openholdingtrap(mon,noticed);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_closeholdingtrap(struct monst * mon,boolean * noticed){return teleport_trap_entry_closeholdingtrap(mon,noticed);}
#else
boolean probe_call_closeholdingtrap(struct monst * mon,boolean * noticed){return closeholdingtrap(mon,noticed);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_openfallingtrap(struct monst * mon,boolean trapdoor_only,boolean * noticed){return teleport_trap_entry_openfallingtrap(mon,trapdoor_only,noticed);}
#else
boolean probe_call_openfallingtrap(struct monst * mon,boolean trapdoor_only,boolean * noticed){return openfallingtrap(mon,trapdoor_only,noticed);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_chest_trap(struct obj * obj,int bodypart,boolean disarm){return teleport_trap_entry_chest_trap(obj,bodypart,disarm);}
#else
boolean probe_call_chest_trap(struct obj * obj,int bodypart,boolean disarm){return chest_trap(obj,bodypart,disarm);}
#endif
#ifdef HYBRID_TRAP
struct trap * probe_call_t_at(coordxy x,coordxy y){return teleport_trap_entry_t_at(x,y);}
#else
struct trap * probe_call_t_at(coordxy x,coordxy y){return t_at(x,y);}
#endif
#ifdef HYBRID_TRAP
int probe_call_count_traps(int ttyp){return teleport_trap_entry_count_traps(ttyp);}
#else
int probe_call_count_traps(int ttyp){return count_traps(ttyp);}
#endif
#ifdef HYBRID_TRAP
void probe_call_deltrap(struct trap * trap){teleport_trap_entry_deltrap(trap);}
#else
void probe_call_deltrap(struct trap * trap){deltrap(trap);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_conjoined_pits(struct trap * trap2,struct trap * trap1,boolean u_entering_trap2){return teleport_trap_entry_conjoined_pits(trap2,trap1,u_entering_trap2);}
#else
boolean probe_call_conjoined_pits(struct trap * trap2,struct trap * trap1,boolean u_entering_trap2){return conjoined_pits(trap2,trap1,u_entering_trap2);}
#endif
#ifdef HYBRID_TRAP
void probe_call_clear_conjoined_pits(struct trap * trap){teleport_trap_entry_clear_conjoined_pits(trap);}
#else
void probe_call_clear_conjoined_pits(struct trap * trap){clear_conjoined_pits(trap);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_adj_nonconjoined_pit(struct trap * adjtrap){return teleport_trap_entry_adj_nonconjoined_pit(adjtrap);}
#else
boolean probe_call_adj_nonconjoined_pit(struct trap * adjtrap){return adj_nonconjoined_pit(adjtrap);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_uteetering_at_seen_pit(struct trap * trap){return teleport_trap_entry_uteetering_at_seen_pit(trap);}
#else
boolean probe_call_uteetering_at_seen_pit(struct trap * trap){return uteetering_at_seen_pit(trap);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_uescaped_shaft(struct trap * trap){return teleport_trap_entry_uescaped_shaft(trap);}
#else
boolean probe_call_uescaped_shaft(struct trap * trap){return uescaped_shaft(trap);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_delfloortrap(struct trap * ttmp){return teleport_trap_entry_delfloortrap(ttmp);}
#else
boolean probe_call_delfloortrap(struct trap * ttmp){return delfloortrap(ttmp);}
#endif
#ifdef HYBRID_TRAP
void probe_call_b_trapped(const char * item,int bodypart){teleport_trap_entry_b_trapped(item,bodypart);}
#else
void probe_call_b_trapped(const char * item,int bodypart){b_trapped(item,bodypart);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_thitm(int tlev,struct monst * mon,struct obj * obj,int d_override,boolean nocorpse){return teleport_trap_entry_thitm(tlev,mon,obj,d_override,nocorpse);}
#else
boolean probe_call_thitm(int tlev,struct monst * mon,struct obj * obj,int d_override,boolean nocorpse){return thitm(tlev,mon,obj,d_override,nocorpse);}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_unconscious(void){return teleport_trap_entry_unconscious();}
#else
boolean probe_call_unconscious(void){return unconscious();}
#endif
#ifdef HYBRID_TRAP
boolean probe_call_lava_effects(void){return teleport_trap_entry_lava_effects();}
#else
boolean probe_call_lava_effects(void){return lava_effects();}
#endif
#ifdef HYBRID_TRAP
void probe_call_sink_into_lava(void){teleport_trap_entry_sink_into_lava();}
#else
void probe_call_sink_into_lava(void){sink_into_lava();}
#endif
#ifdef HYBRID_TRAP
void probe_call_sokoban_guilt(void){teleport_trap_entry_sokoban_guilt();}
#else
void probe_call_sokoban_guilt(void){sokoban_guilt();}
#endif
#ifdef HYBRID_TRAP
void probe_call_maybe_finish_sokoban(void){teleport_trap_entry_maybe_finish_sokoban();}
#else
void probe_call_maybe_finish_sokoban(void){maybe_finish_sokoban();}
#endif
#ifdef HYBRID_TRAP
const char * probe_call_trapname(int ttyp,boolean override){return teleport_trap_entry_trapname(ttyp,override);}
#else
const char * probe_call_trapname(int ttyp,boolean override){return trapname(ttyp,override);}
#endif
#ifdef HYBRID_TRAP
void probe_call_ignite_items(struct obj * objchn){teleport_trap_entry_ignite_items(objchn);}
#else
void probe_call_ignite_items(struct obj * objchn){ignite_items(objchn);}
#endif
#ifdef HYBRID_TRAP
void probe_call_trap_ice_effects(coordxy x,coordxy y,boolean ice_is_melting){teleport_trap_entry_trap_ice_effects(x,y,ice_is_melting);}
#else
void probe_call_trap_ice_effects(coordxy x,coordxy y,boolean ice_is_melting){trap_ice_effects(x,y,ice_is_melting);}
#endif
#ifdef HYBRID_TRAP
void probe_call_trap_sanity_check(void){teleport_trap_entry_trap_sanity_check();}
#else
void probe_call_trap_sanity_check(void){trap_sanity_check();}
#endif
const char*probe_trace(void){return tracebuf;}
void probe_clear(void){tracepos=0;tracebuf[0]=0;}
void probe_option(int i,int n){options[i]=n;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
void*probe_buffer(void){return storage_fixture;}
void*probe_object(int i){return &objects_fixture[i];}
void*probe_mon_pointer(int i){return &monsters_fixture[i];}
void*probe_trap(int i){return traps_fixture[i];}
void*probe_hero(void){return &gy.youmonst;}
void*probe_level(int i){return &levels_fixture[i];}
void*probe_coord(int i){return &coords_fixture[i];}
void*probe_global(int i){switch(i){case 0:return(void*)&gy;case 1:return(void*)&uarmh;case 2:return(void*)&objects;case 3:return(void*)&materialnm;case 4:return(void*)&uarmc;case 5:return(void*)&uarm;case 6:return(void*)&uarmu;case 7:return(void*)&uarms;case 8:return(void*)&uarmg;case 9:return(void*)&uarmf;case 10:return(void*)&gv;case 11:return(void*)&gb;case 12:return(void*)&u;case 13:return(void*)&flags;case 14:return(void*)&mons;case 15:return(void*)&svd;case 16:return(void*)&svl;case 17:return(void*)&iflags;case 18:return(void*)&svc;case 19:return(void*)&gl;case 20:return(void*)&gx;case 21:return(void*)&gf;case 22:return(void*)&WIN_MESSAGE;case 23:return(void*)&windowprocs;case 24:return(void*)&gu;case 25:return(void*)&c_common_strings;case 26:return(void*)&disp;case 27:return(void*)&uwep;case 28:return(void*)&uswapwep;case 29:return(void*)&gi;case 30:return(void*)&uball;case 31:return(void*)&gm;case 32:return(void*)&gn;case 33:return(void*)&uquiver;case 34:return(void*)&go;case 35:return(void*)&xdir;case 36:return(void*)&ydir;case 37:return(void*)&svk;case 38:return(void*)&gs;case 39:return(void*)&uchain;case 40:return(void*)&cg;case 41:return(void*)&destroy_strings;case 42:return(void*)&gt;case 43:return(void*)&gk;case 44:return(void*)&ga;case 45:return(void*)&uamul;case 46:return(void*)&uleft;case 47:return(void*)&uright;case 48:return(void*)&ublindf;case 49:return(void*)&ynqchars;case 50:return(void*)&defsyms;case 51:return(void*)&vowels;default:abort();}}
void probe_seed(int n){seed=n;}
void*probe_catalogue(int mon,int i){return mon?(void*)&mons[i]:(void*)&objects[i];}
void*probe_copy_monster(int i,int species){if(copies[i])free(copies[i]);copies[i]=malloc(sizeof *copies[i]);memcpy(copies[i],&mons[species],sizeof *copies[i]);return copies[i];}
void probe_setup(void){gy=(__typeof__(gy)){0};uarmh=(__typeof__(uarmh)){0};uarmc=(__typeof__(uarmc)){0};uarm=(__typeof__(uarm)){0};uarmu=(__typeof__(uarmu)){0};uarms=(__typeof__(uarms)){0};uarmg=(__typeof__(uarmg)){0};uarmf=(__typeof__(uarmf)){0};gv=(__typeof__(gv)){0};gb=(__typeof__(gb)){0};u=(__typeof__(u)){0};flags=(__typeof__(flags)){0};svd=(__typeof__(svd)){0};svl=(__typeof__(svl)){0};iflags=(__typeof__(iflags)){0};svc=(__typeof__(svc)){0};gl=(__typeof__(gl)){0};gx=(__typeof__(gx)){0};gf=(__typeof__(gf)){0};WIN_MESSAGE=(__typeof__(WIN_MESSAGE)){0};windowprocs=(__typeof__(windowprocs)){0};gu=(__typeof__(gu)){0};disp=(__typeof__(disp)){0};uwep=(__typeof__(uwep)){0};uswapwep=(__typeof__(uswapwep)){0};gi=(__typeof__(gi)){0};uball=(__typeof__(uball)){0};gm=(__typeof__(gm)){0};gn=(__typeof__(gn)){0};uquiver=(__typeof__(uquiver)){0};go=(__typeof__(go)){0};svk=(__typeof__(svk)){0};gs=(__typeof__(gs)){0};uchain=(__typeof__(uchain)){0};gt=(__typeof__(gt)){0};gk=(__typeof__(gk)){0};ga=(__typeof__(ga)){0};uamul=(__typeof__(uamul)){0};uleft=(__typeof__(uleft)){0};uright=(__typeof__(uright)){0};ublindf=(__typeof__(ublindf)){0};memset(options,0,sizeof options);seed=1;reentered=0;objects_globals_init();monst_globals_init();for(int i=0;i<NUM_OBJECTS;i++)objects[i].oc_name_idx=objects[i].oc_descr_idx=i;u.ux=u.uy=10;u.uhp=u.uhpmax=100;u.mh=u.mhmax=100;u.ulevel=10;u.umonnum=PM_HUMAN;gy.youmonst.data=&mons[PM_HUMAN];for(int i=0;i<16;i++){objects_fixture[i]=(struct obj){0};objects_fixture[i].o_id=100+i;objects_fixture[i].quan=1;objects_fixture[i].otyp=DAGGER;objects_fixture[i].oclass=WEAPON_CLASS;if(traps_fixture[i]&&traps_live[i])free(traps_fixture[i]);traps_fixture[i]=calloc(1,sizeof *traps_fixture[i]);traps_live[i]=1;traps_fixture[i]->tx=10+i%4;traps_fixture[i]->ty=10+i/4;traps_fixture[i]->ttyp=ARROW_TRAP;}for(int i=0;i<8;i++){monsters_fixture[i]=(struct monst){0};monsters_fixture[i].m_id=200+i;monsters_fixture[i].data=&mons[PM_HUMAN];monsters_fixture[i].mx=monsters_fixture[i].my=10;monsters_fixture[i].mhp=monsters_fixture[i].mhpmax=100;levels_fixture[i].dnum=0;levels_fixture[i].dlevel=5;}windowprocs.win_display_nhwindow=fixture_win_display_nhwindow;windowprocs.win_delay_output=fixture_win_delay_output;windowprocs.win_clear_nhwindow=fixture_win_clear_nhwindow;gf.ftrap=traps_fixture[0];for(int y=0;y<ROWNO;y++){vision_rows[y]=vision_fixture[y];memset(vision_fixture[y],0,sizeof vision_fixture[y]);}gv.viz_array=vision_rows;gu.urole.name.m="Fixture Role";gu.urole.name.f="Fixture Role";gu.urole.mnum=PM_ARCHEOLOGIST;}
int probe_trap_live(int i){return traps_live[i];}
int probe_catalogue_witness(void){return objects[DAGGER].oc_material!=0&&mons[PM_HUMAN].pmnames[NEUTRAL]!=NULL&&objects[DAGGER].oc_name_idx==DAGGER;}
#ifndef HYBRID_TRAP
#include "tu-trap-layout.h"
#endif
size_t probe_layout_count(void){return sizeof teleport_trap_layout/sizeof *teleport_trap_layout;}
const char*probe_layout_name(size_t i){return teleport_trap_layout[i].name;}
uint64_t probe_layout_value(size_t i){return teleport_trap_layout[i].value;}
void*probe_data(int i){switch(i){
case 0:
#ifdef HYBRID_TRAP
return teleport_trap_storage(0);
#else
return(void*)&a_your;
#endif
case 1:
#ifdef HYBRID_TRAP
return teleport_trap_storage(1);
#else
return(void*)&A_Your;
#endif
case 2:
#ifdef HYBRID_TRAP
return teleport_trap_storage(2);
#else
return(void*)&tower_of_flame;
#endif
case 3:
#ifdef HYBRID_TRAP
return teleport_trap_storage(3);
#else
return(void*)&A_gush_of_water_hits;
#endif
case 4:
#ifdef HYBRID_TRAP
return teleport_trap_storage(4);
#else
return(void*)&blindgas;
#endif
case 5:
#ifdef HYBRID_TRAP
return teleport_trap_storage(5);
#else
return(void*)&lava_killer;
#endif
default:abort();}}
uintptr_t probe_callback(int i){switch(i){case 0:
#ifdef HYBRID_TRAP
return(uintptr_t)teleport_trap_entry_unsqueak_ok;
#else
return(uintptr_t)unsqueak_ok;
#endif
default:abort();}}
int64_t probe_enum(int which,int64_t value){switch(which){case 0:return(enum trap_types)value;case 1:return(enum trap_result)value;case 2:return(enum trap_immunities)value;case 3:return(enum monnums)value;default:abort();}}
uint64_t probe_unsigned_product(uint64_t a,uint64_t b,uint64_t divisor){return(a*b)/divisor;}
int32_t probe_compound_narrow(int32_t a,int64_t delta){a-=delta;return a;}
int64_t probe_typed_field(int which,struct trap*t,int64_t value){switch(which){case 0:t->ttyp=value;return t->ttyp;case 1:t->tseen=value;return t->tseen;case 2:t->once=value;return t->once;case 3:t->madeby_u=value;return t->madeby_u;case 4:t->launch_otyp=value;return t->launch_otyp;case 5:t->launch2.x=value;return t->launch2.x;case 6:t->launch2.y=value;return t->launch2.y;case 7:t->conjoined=value;return t->conjoined;case 8:t->tnote=value;return t->tnote;case 9:t->teledest.x=value;return t->teledest.x;case 10:t->teledest.y=value;return t->teledest.y;default:abort();}}
size_t probe_stride(int which){switch(which){case 0:return sizeof(struct rm);case 1:return sizeof(struct obj);case 2:return sizeof(struct monst);case 3:return sizeof(struct trap);case 4:return sizeof(struct permonst);case 5:return sizeof(coord);case 6:return sizeof(d_level);default:abort();}}
int64_t probe_typed_get(int which,struct trap*t){switch(which){case 0:return t->ttyp;case 1:return t->tseen;case 2:return t->once;case 3:return t->madeby_u;case 4:return t->launch_otyp;case 5:return t->launch2.x;case 6:return t->launch2.y;case 7:return t->conjoined;case 8:return t->tnote;case 9:return t->teledest.x;case 10:return t->teledest.y;default:abort();}}
int64_t probe_native_constant(int which){switch(which){case 0:return W_ARMF;case 1:return ROLL;case 2:return LAUNCH_UNSEEN;case 3:return LAUNCH_KNOWN;case 4:return DAGGER;case 5:return D_CLOSED;case 6:return D_TRAPPED;case 7:return D_ISOPEN;case 8:return D_LOCKED;case 9:return D_BROKEN;case 10:return D_NODOOR;case 11:return OBJ_FLOOR;case 12:return OBJ_INVENT;default:abort();}}
