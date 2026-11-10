/* Original configured ZAP versus imported JS; foreign gameplay controlled. */
#include "hack.h"
#include "artifact.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
#include "tu-zap-layout.h"
__typeof__(u) u;
__typeof__(gu) gu;
__typeof__(gn) gn;
__typeof__(gb) gb;
__typeof__(gv) gv;
__typeof__(svc) svc;
__typeof__(gy) gy;
__typeof__(svq) svq;
__typeof__(sysopt) sysopt;
__typeof__(svl) svl;
__typeof__(iflags) iflags;
__typeof__(gi) gi;
__typeof__(disp) disp;
__typeof__(uleft) uleft;
__typeof__(uright) uright;
__typeof__(uarmh) uarmh;
__typeof__(uarmg) uarmg;
__typeof__(uball) uball;
__typeof__(uchain) uchain;
__typeof__(svm) svm;
__typeof__(go) go;
__typeof__(gp) gp;
__typeof__(uskin) uskin;
__typeof__(svb) svb;
__typeof__(uarms) uarms;
__typeof__(uwep) uwep;
__typeof__(uswapwep) uswapwep;
__typeof__(flags) flags;
__typeof__(gz) gz;
__typeof__(WIN_MESSAGE) WIN_MESSAGE;
__typeof__(windowprocs) windowprocs;
__typeof__(gc) gc;
__typeof__(uarmc) uarmc;
__typeof__(svk) svk;
__typeof__(gs) gs;
__typeof__(svd) svd;
__typeof__(gt) gt;
__typeof__(uarm) uarm;
__typeof__(uarmu) uarmu;
__typeof__(uarmf) uarmf;
__typeof__(uamul) uamul;
__typeof__(ublindf) ublindf;
__typeof__(gm) gm;
__typeof__(nul_glyphinfo) nul_glyphinfo;
int
isok(coordxy x, coordxy y)
{
    /* x corresponds to curx, so x==1 is the first column. Ach. %% */
    return x >= 1 && x <= COLNO - 1 && y >= 0 && y <= ROWNO - 1;
}
void
bypass_obj(struct obj *obj)
{
    obj->bypass = 1;
    svc.context.bypasses = TRUE;
}
void
bypass_objlist(
    struct obj *objchain,
    boolean on) /* TRUE => set, FALSE => clear */
{
    if (on && objchain)
        svc.context.bypasses = TRUE;
    while (objchain) {
        objchain->bypass = on ? 1 : 0;
        objchain = objchain->nobj;
    }
}
struct obj *
nxt_unbypassed_obj(struct obj *objchain)
{
    while (objchain) {
        if (!objchain->bypass) {
            bypass_obj(objchain);
            break;
        }
        objchain = objchain->nobj;
    }
    return objchain;
}
const schar xdir[10]={-1,-1,0,1,1,1,0,-1,0,0},ydir[10]={0,-1,-1,-1,0,1,1,1,0,0};
const struct const_globals cg={0};const char vowels[]="aeiouAEIOU",ynchars[]="yn";
struct obj hands_obj;
const struct c_common_strings c_common_strings={.c_something="something",.c_Never_mind="Never mind."};
const struct Gender genders[]={{.adj="male",.he="he",.him="him",.his="his"},{.adj="female",.he="she",.him="her",.his="her"},{.adj="neuter",.he="it",.him="it",.his="its"},{.adj="plural",.he="they",.him="them",.his="their"}};
static struct obj items[8];static struct oextra extras[8];static struct monst monsters[4];static struct mextra mextras[4];
static struct trap trap;static anything any;
static char buffers[8][4096],trace[262144],result[8192],snap[262144];static int integers[16],opts[1024];
static unsigned rng=1;static void *growth;static uintptr_t returned;static seenV visibility[ROWNO][COLNO],*visrows[ROWNO];
static void append(const char*fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(trace+strlen(trace),sizeof trace-strlen(trace),fmt,ap);va_end(ap);}
static long oid(const struct obj*p){return !p?-1:p==&hands_obj?-2:p>=items&&p<items+8?p-items:-3;}
static long mid(const struct monst*p){return !p?-1:p==&gy.youmonst?-2:p>=monsters&&p<monsters+4?p-monsters:-3;}
#ifdef TELEPORT_REFERENCE_TU
static int zaptype(int);static int zap_hit(int,int);
#else
extern int teleport_zap_test_zaptype(int);extern int teleport_zap_test_zap_hit(int,int);
#define zaptype teleport_zap_test_zaptype
#define zap_hit teleport_zap_test_zap_hit
#endif
static void callback(int stage){if(opts[1000]==stage){opts[1000]=0;append("nested:%d;",zap_hit(0,0));}if(opts[1001]==stage&&!growth){opts[1001]=0;growth=malloc(emscripten_get_heap_size()+8UL*1024*1024);if(!growth)abort();append("grow:%d;",stage);}}
void panic(const char*fmt,...){fprintf(stderr,"ZAP panic: %s\n",fmt);abort();}
boolean rng_log_enabled(void){return opts[0];}void rng_log_set_caller(const char*f,int line,const char*fn){append("caller:%s:%d:%s;",f,line,fn);}
int(rn2)(int n){rng=rng*1664525U+1013904223U;append("rn2:%d;",n);return n?(int)(rng%(unsigned)n):0;}int(rnd)(int n){return 1+(rn2)(n);}int(d)(int n,int x){int t=0;while(n-->0)t+=(rnd)(x);return t;}
void observe_object(struct obj * a0){append("observe_object;");}
void discover_object(int a0,boolean a1,boolean a2,boolean a3){append("discover_object;");}
void update_inventory(){append("update_inventory;");}
boolean resists_magm(struct monst * a0){append("resists_magm;");return (boolean)opts[33];}
boolean disguised_as_mon(struct monst * a0){append("disguised_as_mon;");return (boolean)opts[34];}
void seemimic(struct monst * a0){append("seemimic;");}
void shieldeff(coordxy a0,coordxy a1){append("shieldeff;");}
void pline(const char * a0,...){char b[8192];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("pline:%s;",b);callback(1);}
int find_mac(struct monst * a0){append("find_mac;");return (int)opts[38];}
void mon_adjust_speed(struct monst * a0,int a1,struct obj * a2){append("mon_adjust_speed;");}
void check_gear_next_turn(struct monst * a0){append("check_gear_next_turn;");}
char * mon_nam(struct monst * a0){return "monster";}
void You(const char * a0,...){char b[8192];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("You:%s;",b);callback(1);}
void expels(struct monst * a0,struct permonst * a1,boolean a2){append("expels;");}
void monflee(struct monst * a0,int a1,boolean a2,boolean a3){append("monflee;");}
void shieldeff_mon(struct monst * a0){append("shieldeff_mon;");}
int canseemon(struct monst * a0){append("canseemon;");return (int)opts[46];}
char * Monnam(struct monst * a0){return "Monster";}
void xkilled(struct monst * a0,int a1){append("xkilled;");}
int newcham(struct monst * a0,struct permonst * a1,unsigned int a2){append("newcham;");return (int)opts[49];}
int sensemon(struct monst * a0){append("sensemon;");return (int)opts[50];}
void newmcorpsenm(struct monst * a0){append("newmcorpsenm;");}
boolean u_teleport_mon(struct monst * a0,boolean a1){append("u_teleport_mon;");return (boolean)opts[52];}
void mon_set_minvis(struct monst * a0,boolean a1){append("mon_set_minvis;");}
int knowninvisible(struct monst * a0){append("knowninvisible;");return (int)opts[54];}
void that_is_a_mimic(struct monst * a0,unsigned int a1){append("that_is_a_mimic;");}
boolean closeholdingtrap(struct monst * a0,boolean * a1){append("closeholdingtrap;");return (boolean)opts[56];}
boolean openholdingtrap(struct monst * a0,boolean * a1){append("openholdingtrap;");return (boolean)opts[57];}
boolean openfallingtrap(struct monst * a0,boolean a1,boolean * a2){append("openfallingtrap;");return (boolean)opts[58];}
boolean m_is_steadfast(struct monst * a0){append("m_is_steadfast;");return (boolean)opts[59];}
void mhurtle(struct monst * a0,int a1,int a2,int a3){append("mhurtle;");}
void wakeup(struct monst * a0,boolean a1){append("wakeup;");}
void abuse_dog(struct monst * a0){append("abuse_dog;");}
struct obj * which_armor(struct monst * a0,long a1){return opts[7]?&items[1]:0;}
char * distant_name(struct obj * a0,char *(*a1)(struct obj *)){append("distant:%ld;",oid(a0));return a1(a0);}
char * An(const char * a0){append("An;");return "An";}
const char * surface(coordxy a0,coordxy a1){append("surface;");return "surface";}
void mdrop_obj(struct monst * a0,struct obj * a1,boolean a2){append("mdrop_obj;");}
int healmon(struct monst * a0,int a1,int a2){append("healmon;");return (int)opts[68];}
void mcureblindness(struct monst * a0,boolean a1){append("mcureblindness;");}
void set_mimic_sym(struct monst * a0){append("set_mimic_sym;");}
void newsym(coordxy a0,coordxy a1){append("newsym;");}
void mimic_hit_msg(struct monst * a0,short a1){append("mimic_hit_msg;");}
void more_experienced(int a0,int a1){append("more_experienced;");}
void newexplevel(){append("newexplevel;");}
void adjalign(int a0){append("adjalign;");}
int flash_hits_mon(struct monst * a0,struct obj * a1){append("flash_hits_mon;");return (int)opts[76];}
int sleep_monst(struct monst * a0,int a1,int a2){append("sleep_monst;");return (int)opts[77];}
void slept_monst(struct monst * a0){append("slept_monst;");}
boolean stone_furniture_type(unsigned int a0){append("stone_furniture_type;");return (boolean)opts[79];}
boolean stone_object_type(unsigned int a0){append("stone_object_type;");return (boolean)opts[80];}
void set_msg_xy(coordxy a0,coordxy a1){append("set_msg_xy;");}
int monhp_per_lvl(struct monst * a0){append("monhp_per_lvl;");return (int)opts[82];}
boolean resists_drli(struct monst * a0){append("resists_drli;");return (boolean)opts[83];}
void killed(struct monst * a0){append("killed;");}
void impossible(const char * a0,...){char b[8192];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("impossible:%s;",b);callback(1);}
void m_respond(struct monst * a0){append("m_respond;");}
void hot_pursuit(struct monst * a0){append("hot_pursuit;");}
void map_invisible(coordxy a0,coordxy a1){append("map_invisible;");}
struct attack * dmgtype_fromattack(struct permonst * a0,int a1,int a2){append("dmgtype_fromattack;");return 0;}
void You_feel(const char * a0,...){char b[8192];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("You_feel:%s;",b);callback(1);}
boolean sticks(struct permonst * a0){append("sticks;");return (boolean)opts[91];}
void set_ustuck(struct monst * a0){append("set_ustuck;");}
void unstuck(struct monst * a0){append("unstuck;");}
void mstatusline(struct monst * a0){append("mstatusline;");}
struct obj * display_minventory(struct monst * a0,int a1,char * a2){append("display_minventory;");return 0;}
char * noit_Monnam(struct monst * a0){append("noit_Monnam;");return "noit_Monnam";}
struct monst * get_mtraits(struct obj * a0,boolean a1){return opts[2]?&monsters[0]:0;}
struct monst * makemon(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){append("makemon:%ld:%d:%d:%lu;",a0-mons,a1,a2,(unsigned long)a3);callback(3);if(!opts[3])return 0;monsters[3].data=a0;monsters[3].mx=a1;monsters[3].my=a2;return &monsters[3];}
void dealloc_monst(struct monst * a0){append("dealloc_monst;");}
boolean dmgtype(struct permonst * a0,int a1){append("dmgtype;");return (boolean)opts[100];}
void neweshk(struct monst * a0){append("neweshk;");}
void replmon(struct monst * a0,struct monst * a1){append("replmon;");}
void restore_cham(struct monst * a0){append("restore_cham;");}
struct trap * t_at(coordxy a0,coordxy a1){return opts[9]?&trap:0;}
char * xname(struct obj * a0){return "object";}
void cant_finish_meal(struct obj * a0){append("cant_finish_meal;");}
boolean enexto(coord * a0,coordxy a1,coordxy a2,struct permonst * a3){append("enexto;");return (boolean)opts[107];}
char * corpse_xname(struct obj * a0,const char * a1,unsigned int a2){append("corpse_xname;");return "corpse_xname";}
boolean cant_revive(int * a0,boolean a1,struct obj * a2){append("cant_revive;");return (boolean)opts[109];}
void free_omid(struct obj * a0){append("free_omid;");}
void free_omonst(struct obj * a0){append("free_omonst;");}
void wary_dog(struct monst * a0,boolean a1){append("wary_dog;");}
struct obj * splitobj(struct obj * a0,long a1){append("splitobj;");return 0;}
boolean costly_spot(coordxy a0,coordxy a1){append("costly_spot;");return (boolean)opts[114];}
char * in_rooms(coordxy a0,coordxy a1,int a2){append("in_rooms;");return "in_rooms";}
struct monst * shop_keeper(char a0){append("shop_keeper;");return 0;}
char * shk_your(char * a0,struct obj * a1){append("shk_your;");return "shk_your";}
long stolen_value(struct obj * a0,coordxy a1,coordxy a2,boolean a3,boolean a4){append("stolen_value;");return (long)opts[118];}
struct monst * find_mid(unsigned int a0,unsigned int a1){return opts[5]?&monsters[0]:0;}
void obj_extract_self(struct obj * a0){append("extract:%ld;",oid(a0));a0->nobj=0;a0->nexthere=0;}
int add_to_minv(struct monst * a0,struct obj * a1){append("add_to_minv;");return (int)opts[121];}
boolean tamedog(struct monst * a0,struct obj * a1,boolean a2){append("tamedog;");return (boolean)opts[122];}
void mongone(struct monst * a0){append("mongone;");}
struct monst * christen_monst(struct monst * a0,const char * a1){append("christen_monst;");return 0;}
int eaten_stat(int a0,struct obj * a1){append("eaten_stat;");return (int)opts[125];}
void useup(struct obj * a0){append("useup;");}
void delobj_core(struct obj * a0,boolean a1){append("delobj_core;");}
void m_useup(struct monst * a0,struct obj * a1){append("m_useup;");}
void obfree(struct obj * a0,struct obj * a1){append("obfree;");}
boolean dead_species(int a0,boolean a1){append("dead_species;");return (boolean)opts[130];}
void attach_egg_hatch_timeout(struct obj * a0,long a1){append("attach_egg_hatch_timeout;");}
char * Shk_Your(char * a0,struct obj * a1){append("Shk_Your;");return "Shk_Your";}
const char * mon_pmname(struct monst * a0){append("mon_pmname;");return "mon_pmname";}
char * an(const char * a0){append("an;");return "an";}
char * Amonnam(struct monst * a0){append("Amonnam;");return "Amonnam";}
void encumber_msg(){append("encumber_msg;");}
void make_stunned(long a0,boolean a1){append("make_stunned;");}
void costly_alteration(struct obj * a0,int a1){append("costly_alteration;");}
anything * obj_to_any(struct obj * a0){any.a_obj=a0;return &any;}
long peek_timer(short a0,union any * a1){append("peek_timer;");return (long)opts[140];}
long stop_timer(short a0,union any * a1){append("stop_timer;");return (long)opts[141];}
boolean start_timer(long a0,short a1,short a2,union any * a3){append("start_timer;");return (boolean)opts[142];}
void unbless(struct obj * a0){append("unbless;");}
void uncurse(struct obj * a0){append("uncurse;");}
void free_oname(struct obj * a0){append("free_oname;");}
void container_weight(struct obj * a0){append("container_weight;");}
boolean defends(int a0,struct obj * a1){append("defends;");return (boolean)opts[147];}
boolean defends_when_carried(int a0,struct obj * a1){append("defends_when_carried;");return (boolean)opts[148];}
void bot(){append("bot;");}
void addtobill(struct obj * a0,boolean a1,boolean a2,boolean a3){append("addtobill;");}
void delobj(struct obj * a0){append("delobj;");}
char * a_monnam(struct monst * a0){append("a_monnam;");return "a_monnam";}
void sokoban_guilt(){append("sokoban_guilt;");}
struct obj * mkobj(int a0,boolean a1){items[7]=cg.zeroobj;items[7].otyp=ROCK;items[7].oclass=a0;items[7].quan=1;return &items[7];}
struct obj * mksobj(int a0,boolean a1,boolean a2){items[7]=cg.zeroobj;items[7].otyp=a0;items[7].oclass=objects[a0].oc_class;items[7].quan=1;return opts[4]?0:&items[7];}
void set_corpsenm(struct obj * a0,int a1){a0->corpsenm=a1;append("corpsenm:%ld:%d;",oid(a0),a1);}
void kill_egg(struct obj * a0){append("kill_egg;");}
int weight(struct obj * a0){return 10;}
int can_be_hatched(int a0){append("can_be_hatched;");return (int)opts[159];}
boolean erosion_matters(struct obj * a0){append("erosion_matters;");return (boolean)opts[160];}
boolean is_flammable(struct obj * a0){append("is_flammable;");return (boolean)opts[161];}
boolean is_rottable(struct obj * a0){append("is_rottable;");return (boolean)opts[162];}
boolean permapoisoned(struct obj * a0){append("permapoisoned;");return (boolean)opts[163];}
void o_unleash(struct obj * a0){append("o_unleash;");}
void delete_contents(struct obj * a0){append("delete_contents;");}
int rnd_class(int a0,int a1){append("rnd_class;");return (int)opts[166];}
void fixup_oil(struct obj * a0,struct obj * a1){append("fixup_oil;");}
void replace_object(struct obj * a0,struct obj * a1){append("replace_object;");}
void freeinv_core(struct obj * a0){append("freeinv_core;");}
void addinv_core1(struct obj * a0){append("addinv_core1;");}
void addinv_core2(struct obj * a0){append("addinv_core2;");}
long wearslot(struct obj * a0){append("wearslot;");return (long)opts[172];}
void remove_worn_item(struct obj * a0,boolean a1){append("remove_worn_item;");}
void setuwep(struct obj * a0){append("setuwep;");}
void set_twoweap(boolean a0){append("set_twoweap;");}
void setuswapwep(struct obj * a0){append("setuswapwep;");}
void setuqwep(struct obj * a0){append("setuqwep;");}
void setworn(struct obj * a0,long a1){append("setworn;");}
void set_wear(struct obj * a0){append("set_wear;");}
struct obj * wearmask_to_obj(long a0){append("wearmask_to_obj;");return 0;}
int does_block(int a0,int a1,struct rm * a2){append("does_block;");return (int)opts[181];}
void unblock_point(int a0,int a1){append("unblock_point;");}
boolean is_pool_or_lava(coordxy a0,coordxy a1){append("is_pool_or_lava;");return (boolean)opts[183];}
void block_point(int a0,int a1){append("block_point;");}
long contained_cost(struct obj * a0,struct monst * a1,long a2,boolean a3,boolean a4){append("contained_cost;");return (long)opts[185];}
int inhishop(struct monst * a0){append("inhishop;");return (int)opts[186];}
void make_angry_shk(struct monst * a0,coordxy a1,coordxy a2){append("make_angry_shk;");}
char * Shknam(struct monst * a0){append("Shknam;");return "Shknam";}
void Norep(const char * a0,...){char b[8192];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("Norep:%s;",b);callback(1);}
struct monst * animate_statue(struct obj * a0,coordxy a1,coordxy a2,int a3,int * a4){append("animate_statue;");return 0;}
void obj_stop_timers(struct obj * a0){append("obj_stop_timers;");}
void pline_The(const char * a0,...){char b[8192];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("pline_The:%s;",b);callback(1);}
void place_object(struct obj * a0,coordxy a1,coordxy a2){append("place_object;");}
boolean debugcore(const char * a0,boolean a1){append("debugcore;");return (boolean)opts[194];}
char * Tobjnam(struct obj * a0,const char * a1){append("Tobjnam;");return "Tobjnam";}
void unpunish(){append("unpunish;");}
void livelog_printf(long a0,const char * a1,...){char b[8192];va_list ap;va_start(ap,a1);vsnprintf(b,sizeof b,a1,ap);va_end(ap);append("livelog:%ld:%s;",a0,b);}
boolean boxlock(struct obj * a0,struct obj * a1){append("boxlock;");return (boolean)opts[198];}
boolean hideunder(struct monst * a0){append("hideunder;");return (boolean)opts[199];}
char * the(const char * a0){append("the;");return "the";}
char * rndmonnam(char * a0){append("rndmonnam;");return "rndmonnam";}
struct obj * display_cinventory(struct obj * a0){append("display_cinventory;");return 0;}
void set_cknown_lknown(struct obj * a0){append("set_cknown_lknown;");}
void You_hear(const char * a0,...){char b[8192];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("You_hear:%s;",b);callback(1);}
int breaks(struct obj * a0,coordxy a1,coordxy a2){append("breaks;");return (int)opts[205];}
int hero_breaks(struct obj * a0,coordxy a1,coordxy a2,unsigned int a3){append("hero_breaks;");return (int)opts[206];}
void newsym_force(coordxy a0,coordxy a1){append("newsym_force;");}
boolean rloco(struct obj * a0){append("rloco;");return (boolean)opts[208];}
void maybe_unhide_at(coordxy a0,coordxy a1){append("maybe_unhide_at;");}
int corpse_revive_type(struct obj * a0){append("corpse_revive_type;");return (int)opts[210];}
char * cxname_singular(struct obj * a0){append("cxname_singular;");return "cxname_singular";}
char * noname_monnam(struct monst * a0,int a1){append("noname_monnam;");return "noname_monnam";}
char * The(const char * a0){append("The;");return "The";}
void exercise(int a0,boolean a1){append("exercise;");}
struct monst * activate_statue_trap(struct trap * a0,coordxy a1,coordxy a2,boolean a3){append("activate_statue_trap;");return 0;}
void recreate_pile_at(coordxy a0,coordxy a1){append("recreate_pile_at;");}
void fill_pit(coordxy a0,coordxy a1){append("fill_pit;");}
void enlightenment(int a0,int a1){append("enlightenment;");}
void litroom(boolean a0,struct obj * a1){append("litroom;");}
int findit(){append("findit;");return (int)opts[220];}
boolean create_critters(int a0,struct permonst * a1,boolean a2){append("create_critters;");return (boolean)opts[221];}
void losehp(int a0,const char * a1,schar a2){append("losehp;");}
void useupall(struct obj * a0){append("useupall;");}
boolean check_capacity(const char * a0){append("check_capacity;");return (boolean)opts[224];}
struct obj * getobj(const char * a0,int (*a1)(struct obj *),unsigned int a2){append("getobj:%s:%u:%d:%d;",a0,a2,a1(0),a1(&items[0]));callback(2);return opts[1]?&items[0]:0;}
void check_unpaid(struct obj * a0){append("check_unpaid;");}
int getdir(const char * a0){append("getdir;");return (int)opts[227];}
char * killer_xname(struct obj * a0){append("killer_xname;");return "killer_xname";}
void monstseesu(unsigned long a0){append("monstseesu;");}
void monstunseesu(unsigned long a0){append("monstunseesu;");}
void ugolemeffects(int a0,int a1){append("ugolemeffects;");}
void explode(coordxy a0,coordxy a1,int a2,int a3,char a4,int a5){append("explode;");}
void burn_away_slime(){append("burn_away_slime;");}
boolean burnarmor(struct monst * a0){append("burnarmor;");return (boolean)opts[234];}
void ignite_items(struct obj * a0){append("ignite_items;");}
void polyself(int a0){append("polyself;");}
void losexp(const char * a0){append("losexp;");}
char * yname(struct obj * a0){append("yname;");return "yname";}
void incr_itimeout(long * a0,int a1){append("incr_itimeout;");}
void self_invis_message(){append("self_invis_message;");}
void speed_up(long a0){append("speed_up;");}
void fall_asleep(int a0,boolean a1){append("fall_asleep;");}
void u_slow_down(){append("u_slow_down;");}
void tele(){append("tele;");}
void urgent_pline(const char * a0,...){char b[8192];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("urgent_pline:%s;",b);callback(1);}
void done(int a0){append("done;");}
void healup(int a0,int a1,boolean a2,boolean a3){append("healup;");}
void ustatusline(){append("ustatusline;");}
int polymon(int a0){append("polymon;");return (int)opts[249];}
void fix_petrification(){append("fix_petrification;");}
int merged(struct obj ** a0,struct obj ** a1){append("merged;");return (int)opts[251];}
char * ansimpleoname(struct obj * a0){append("ansimpleoname;");return "ansimpleoname";}
char * bare_artifactname(struct obj * a0){append("bare_artifactname;");return "bare_artifactname";}
boolean resists_blnd(struct monst * a0){append("resists_blnd;");return (boolean)opts[254];}
void make_blinded(long a0,boolean a1){append("make_blinded;");}
void Your(const char * a0,...){char b[8192];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("Your:%s;",b);callback(1);}
boolean resists_blnd_by_arti(struct monst * a0){append("resists_blnd_by_arti;");return (boolean)opts[257];}
void find_ac(){append("find_ac;");}
void rehumanize(){append("rehumanize;");}
void normal_shape(struct monst * a0){append("normal_shape;");}
void monkilled(struct monst * a0,const char * a1,int a2){append("monkilled;");}
const char * ceiling(coordxy a0,coordxy a1){append("ceiling;");return "ceiling";}
int update_mapseen_for(coordxy a0,coordxy a1){append("update_mapseen_for;");return (int)opts[263];}
schar db_under_typ(int a0){append("db_under_typ;");return (schar)opts[264];}
int display_binventory(coordxy a0,coordxy a1,boolean a2){append("display_binventory;");return (int)opts[265];}
boolean is_db_wall(coordxy a0,coordxy a1){append("is_db_wall;");return (boolean)opts[266];}
boolean find_drawbridge(coordxy * a0,coordxy * a1){append("find_drawbridge;");return (boolean)opts[267];}
void open_drawbridge(coordxy a0,coordxy a1){append("open_drawbridge;");}
boolean on_level(d_level * a0,d_level * a1){return a0->dnum==a1->dnum&&a0->dlevel==a1->dlevel;}
boolean ok_to_quest(){append("ok_to_quest;");return (boolean)opts[270];}
int is_drawbridge_wall(coordxy a0,coordxy a1){append("is_drawbridge_wall;");return (int)opts[271];}
void close_drawbridge(coordxy a0,coordxy a1){append("close_drawbridge;");}
void destroy_drawbridge(coordxy a0,coordxy a1){append("destroy_drawbridge;");}
const char * body_part(int a0){return "hand";}
boolean hard_helmet(struct obj * a0){append("hard_helmet;");return (boolean)opts[275];}
struct obj * mksobj_at(int a0,coordxy a1,coordxy a2,boolean a3,boolean a4){append("mksobj_at;");return 0;}
void stackobj(struct obj * a0){append("stackobj;");}
void dotrap(struct trap * a0,unsigned int a1){append("dotrap;");}
boolean is_ice(coordxy a0,coordxy a1){append("is_ice;");return (boolean)opts[279];}
struct engr * engr_at(coordxy a0,coordxy a1){append("engr_at;");return 0;}
boolean is_pool(coordxy a0,coordxy a1){append("is_pool;");return (boolean)opts[281];}
boolean is_lava(coordxy a0,coordxy a1){append("is_lava;");return (boolean)opts[282];}
char * makeplural(const char * a0){append("makeplural;");return "makeplural";}
void zap_dig(){append("zap_dig;");}
schar acurr(int a0){append("acurr;");return (schar)opts[285];}
int spell_skilltype(int a0){append("spell_skilltype;");return (int)opts[286];}
char * vtense(const char * a0,const char * a1){append("vtense;");return "vtense";}
void deltrap(struct trap * a0){append("deltrap;");}
void del_engr(struct engr * a0){append("del_engr;");}
char * random_engraving(char * a0,char * a1){append("random_engraving;");return "random_engraving";}
void make_engr_at(coordxy a0,coordxy a1,const char * a2,const char * a3,long a4,int a5){append("make_engr_at;");}
void rloc_engr(struct engr * a0){append("rloc_engr;");}
void wipe_engr_at(coordxy a0,coordxy a1,xint16 a2,boolean a3){append("wipe_engr_at;");}
int glyph_at(coordxy a0,coordxy a1){append("glyph_at;");return (int)opts[294];}
void show_map_spot(coordxy a0,coordxy a1,boolean a2){append("show_map_spot;");}
void cvt_sdoor_to_door(struct rm * a0){append("cvt_sdoor_to_door;");}
void recalc_block_point(coordxy a0,coordxy a1){append("recalc_block_point;");}
void draft_message(boolean a0){append("draft_message;");}
void force_decor(boolean a0){append("force_decor;");}
const char * trapname(int a0,boolean a1){append("trapname;");return "trapname";}
boolean Invocation_lev(d_level * a0){append("Invocation_lev;");return (boolean)opts[301];}
boolean In_mines(d_level * a0){append("In_mines;");return (boolean)opts[302];}
boolean In_hell(d_level * a0){append("In_hell;");return (boolean)opts[303];}
void tmp_at(coordxy a0,coordxy a1){append("tmp_at;");}
int rn2_on_display_rng(int a0){append("rn2_on_display_rng;");return (int)opts[305];}
char inside_shop(coordxy a0,coordxy a1){append("inside_shop;");return (char)opts[306];}
struct monst * shkcatch(struct obj * a0,coordxy a1,coordxy a2){append("shkcatch;");return opts[14]?&monsters[0]:0;}
void show_transient_light(struct obj * a0,coordxy a1,coordxy a2){append("show_transient_light;");}
boolean hits_bars(struct obj ** a0,coordxy a1,coordxy a2,coordxy a3,coordxy a4,int a5,int a6){append("hits_bars;");return (boolean)opts[309];}
char * Yname2(struct obj * a0){append("Yname2;");return "Yname2";}
char * otense(struct obj * a0,const char * a1){append("otense;");return "otense";}
boolean shade_miss(struct monst * a0,struct monst * a1,struct obj * a2,boolean a3,boolean a4){append("shade_miss;");return (boolean)opts[312];}
void unmap_object(coordxy a0,coordxy a1){append("unmap_object;");}
boolean ship_object(struct obj * a0,coordxy a1,coordxy a2,boolean a3){append("ship_object;");return (boolean)opts[314];}
boolean doorlock(struct obj * a0,coordxy a1,coordxy a2){append("doorlock;");return (boolean)opts[315];}
void add_damage(coordxy a0,coordxy a1,long a2){append("add_damage;");}
boolean closed_door(coordxy a0,coordxy a1){append("closed_door;");return (boolean)opts[317];}
struct obj * sobj_at(int a0,coordxy a1,coordxy a2){return opts[6]?&items[0]:0;}
boolean test_move(coordxy a0,coordxy a1,coordxy a2,coordxy a3,int a4){append("test_move;");return (boolean)opts[319];}
void pay_for_damage(const char * a0,boolean a1){append("pay_for_damage;");}
void transient_light_cleanup(){append("transient_light_cleanup;");}
int xytodir(int a0,int a1){append("xytodir;");return (int)opts[322];}
boolean throwit_mon_hit(struct obj * a0,struct monst * a1){append("throwit_mon_hit;");return (boolean)opts[323];}
int dmgval(struct obj * a0,struct monst * a1){append("dmgval;");return (int)opts[324];}
int thitu(int a0,int a1,struct obj ** a2,const char * a3){append("thitu;");return (int)opts[325];}
void endmultishot(boolean a0){append("endmultishot;");}
void wake_nearto(coordxy a0,coordxy a1,int a2){append("wake_nearto;");}
boolean defended(struct monst * a0,int a1){append("defended;");return (boolean)opts[328];}
boolean Resists_Elem(struct monst * a0,int a1){append("Resists_Elem;");return (boolean)opts[329];}
void acid_damage(struct obj * a0){append("acid_damage;");}
void erode_armor(struct monst * a0,int a1){append("erode_armor;");}
int disintegrate_arm(struct obj * a0){append("disintegrate_arm;");return (int)opts[332];}
void poisoned(const char * a0,int a1,const char * a2,int a3,boolean a4){append("poisoned;");}
const char * hliquid(const char * a0){append("hliquid;");return "hliquid";}
char * death_inflicted_by(char * a0,const char * a1,struct monst * a2){append("death_inflicted_by;");return "death_inflicted_by";}
void useupf(struct obj * a0,long a1){append("useupf;");}
struct obj * mlifesaver(struct monst * a0){append("mlifesaver;");return 0;}
boolean is_quest_artifact(struct obj * a0){append("is_quest_artifact;");return (boolean)opts[338];}
void extract_from_minvent(struct monst * a0,struct obj * a1,boolean a2,boolean a3){append("extract_from_minvent;");}
int zapdir_to_glyph(int a0,int a1,int a2){append("zapdir_to_glyph;");return (int)opts[340];}
boolean unmap_invisible(coordxy a0,coordxy a1){append("unmap_invisible;");return (boolean)opts[341];}
boolean mon_reflects(struct monst * a0,const char * a1){append("mon_reflects;");return (boolean)opts[342];}
boolean disguised_as_non_mon(struct monst * a0){append("disguised_as_non_mon;");return (boolean)opts[343];}
void nomul(int a0){append("nomul;");}
void pline_dir(int a0,const char * a1,...){char b[8192];va_list ap;va_start(ap,a1);vsnprintf(b,sizeof b,a1,ap);va_end(ap);append("pline_dir:%s;",b);callback(1);}
boolean ureflects(const char * a0,const char * a1){append("ureflects;");return (boolean)opts[346];}
void stop_occupation(){append("stop_occupation;");}
void spot_stop_timers(coordxy a0,coordxy a1,short a2){append("spot_stop_timers;");}
void trap_ice_effects(coordxy a0,coordxy a1,boolean a2){append("trap_ice_effects;");}
void obj_ice_effects(coordxy a0,coordxy a1,boolean a2){append("obj_ice_effects;");}
void unearth_objs(int a0,int a1){append("unearth_objs;");}
void vision_recalc(int a0){append("vision_recalc;");}
boolean boulder_hits_pool(struct obj * a0,coordxy a1,coordxy a2,boolean a3){append("boulder_hits_pool;");return (boolean)opts[353];}
void spoteffects(boolean a0){append("spoteffects;");}
int minliquid(struct monst * a0){append("minliquid;");return (int)opts[355];}
anything * long_to_any(long a0){any.a_long=a0;return &any;}
boolean delfloortrap(struct trap * a0){append("delfloortrap;");return (boolean)opts[357];}
NhRegion * create_gas_cloud(coordxy a0,coordxy a1,int a2,int a3){append("create_gas_cloud;");return 0;}
struct trap * maketrap(coordxy a0,coordxy a1,int a2){trap.ttyp=a2;trap.tx=a0;trap.ty=a1;return &trap;}
int mintrap(struct monst * a0,unsigned int a1){append("mintrap;");return (int)opts[360];}
void dryup(coordxy a0,coordxy a1,boolean a2){append("dryup;");}
boolean is_moat(coordxy a0,coordxy a1){append("is_moat;");return (boolean)opts[362];}
const char * waterbody_name(coordxy a0,coordxy a1){append("waterbody_name;");return "waterbody_name";}
void fix_wall_spines(coordxy a0,coordxy a1,coordxy a2,coordxy a3){append("fix_wall_spines;");}
void bury_objs(int a0,int a1){append("bury_objs;");}
void set_uinwater(int a0){append("set_uinwater;");}
void docrt(){append("docrt;");}
void reset_utrap(boolean a0){append("reset_utrap;");}
void set_utrap(unsigned int a0,unsigned int a1){append("set_utrap;");}
long spot_time_left(coordxy a0,coordxy a1,short a2){append("spot_time_left;");return (long)opts[370];}
void dissolve_bars(coordxy a0,coordxy a1){append("dissolve_bars;");}
boolean picking_at(coordxy a0,coordxy a1){append("picking_at;");return (boolean)opts[372];}
void reset_pick(){append("reset_pick;");}
boolean billable(struct monst ** a0,struct obj * a1,char a2,boolean a3){append("billable;");return (boolean)opts[374];}
char * shkname(struct monst * a0){append("shkname;");return "shkname";}
int breakobj(struct obj * a0,coordxy a1,coordxy a2,boolean a3,boolean a4){append("breakobj;");return (int)opts[376];}
void dealloc_oextra(struct obj * a0){append("dealloc_oextra;");}
const char * cloak_simple_name(struct obj * a0){append("cloak_simple_name;");return "cloak_simple_name";}
const char * suit_simple_name(struct obj * a0){append("suit_simple_name;");return "suit_simple_name";}
const char * shirt_simple_name(struct obj * a0){append("shirt_simple_name;");return "shirt_simple_name";}
const char * helm_simple_name(struct obj * a0){append("helm_simple_name;");return "helm_simple_name";}
const char * gloves_simple_name(struct obj * a0){append("gloves_simple_name;");return "gloves_simple_name";}
const char * boots_simple_name(struct obj * a0){append("boots_simple_name;");return "boots_simple_name";}
const char * shield_simple_name(struct obj * a0){append("shield_simple_name;");return "shield_simple_name";}
char * simpleonames(struct obj * a0){append("simpleonames;");return "simpleonames";}
const char * hcolor(const char * a0){append("hcolor;");return "hcolor";}
void recharge(struct obj * a0,int a1){append("recharge;");}
void potionbreathe(struct obj * a0){append("potionbreathe;");}
void Ring_gone(struct obj * a0){append("Ring_gone;");}
void setnotworn(struct obj * a0){append("setnotworn;");}
void add_menu(winid a0,const glyph_info * a1,const union any * a2,char a3,char a4,int a5,int a6,const char * a7,unsigned int a8){append("add_menu;");}
int select_menu(winid a0,int a1,menu_item ** a2){append("select:%d:%d;",a0,a1);*a2=0;if(opts[13]>0){*a2=malloc(sizeof **a2);memset(*a2,0,sizeof **a2);(*a2)[0].item.a_int=opts[13];return 1;}return opts[13];}
void getlin(const char * a0,char * a1){append("getlin:%s;",a0);strcpy(a1,buffers[6]);buffers[6][0]=0;}
struct obj * readobjnam(char * a0,struct obj * a1){append("wish:%s;",a0?a0:"[NULL]");if(!a0)return &items[0];if(!strcmp(a0,"nothing"))return a1;if(!strcmp(a0,"terrain"))return &hands_obj;return opts[10]?0:&items[0];}
void artifact_origin(struct obj * a0,unsigned int a1){append("artifact_origin;");}
char * doname(struct obj * a0){return "object";}
boolean u_safe_from_fatal_corpse(struct obj * a0,int a1){append("u_safe_from_fatal_corpse;");return (boolean)opts[397];}
char * aobjnam(struct obj * a0,const char * a1){append("aobjnam;");return "aobjnam";}
struct obj * hold_another_object(struct obj * a0,const char * a1,const char * a2,const char * a3){append("hold:%ld:%s;",oid(a0),a1);return a0;}
const char * rnd_hallublast(){append("rnd_hallublast;");return "rnd_hallublast";}
static winid wincreate(int n){append("create:%d;",n);return 7;}static void winput(winid w,int a,const char*s){append("put:%d:%d:%s;",w,a,s);}static void windestroy(winid w){append("destroy:%d;",w);}static void windisplay(winid w,boolean b){append("display:%d:%d;",w,b);}static void winstart(winid w,unsigned long b){append("menu:%d:%lu;",w,b);}static void winend(winid w,const char*s){append("endmenu:%d:%s;",w,s?s:"[NULL]");}static void delay(void){append("delay;");}
#ifdef TELEPORT_REFERENCE_TU
#include "../nethack-c/upstream/src/zap.c"

#else
extern int teleport_zap_test_zaptype(int);
#define zaptype teleport_zap_test_zaptype
extern void teleport_zap_test_probe_objchain(struct obj *);
#define probe_objchain teleport_zap_test_probe_objchain
extern boolean teleport_zap_test_zombie_can_dig(coordxy,coordxy);
#define zombie_can_dig teleport_zap_test_zombie_can_dig
extern void teleport_zap_test_revive_egg(struct obj *);
#define revive_egg teleport_zap_test_revive_egg
extern void teleport_zap_test_polyuse(struct obj *,int,int);
#define polyuse teleport_zap_test_polyuse
extern void teleport_zap_test_create_polymon(struct obj *,int);
#define create_polymon teleport_zap_test_create_polymon
extern int teleport_zap_test_stone_to_flesh_obj(struct obj *);
#define stone_to_flesh_obj teleport_zap_test_stone_to_flesh_obj
extern void teleport_zap_test_backfire(struct obj *);
#define backfire teleport_zap_test_backfire
extern int teleport_zap_test_zap_ok(struct obj *);
#define zap_ok teleport_zap_test_zap_ok
extern void teleport_zap_test_boxlock_invent(struct obj *);
#define boxlock_invent teleport_zap_test_boxlock_invent
extern boolean teleport_zap_test_zap_steed(struct obj *);
#define zap_steed teleport_zap_test_zap_steed
extern boolean teleport_zap_test_zap_updown(struct obj *);
#define zap_updown teleport_zap_test_zap_updown
extern int teleport_zap_test_spell_hit_bonus(int);
#define spell_hit_bonus teleport_zap_test_spell_hit_bonus
extern void teleport_zap_test_skiprange(int,int *,int *);
#define skiprange teleport_zap_test_skiprange
extern void teleport_zap_test_maybe_explode_trap(struct trap *,struct obj *,boolean *);
#define maybe_explode_trap teleport_zap_test_maybe_explode_trap
extern void teleport_zap_test_zap_map(coordxy,coordxy,struct obj *);
#define zap_map teleport_zap_test_zap_map
extern void teleport_zap_test_zhitu(int,int,const char *,coordxy,coordxy);
#define zhitu teleport_zap_test_zhitu
extern void teleport_zap_test_bounce_dir(coordxy,coordxy,int *,int *,int);
#define bounce_dir teleport_zap_test_bounce_dir
extern int teleport_zap_test_zap_hit(int,int);
#define zap_hit teleport_zap_test_zap_hit
extern void teleport_zap_test_disintegrate_mon(struct monst *,int,const char *);
#define disintegrate_mon teleport_zap_test_disintegrate_mon
extern boolean teleport_zap_test_destroyable(struct obj *,int);
#define destroyable teleport_zap_test_destroyable
extern int teleport_zap_test_adtyp_to_prop(int);
#define adtyp_to_prop teleport_zap_test_adtyp_to_prop
extern int teleport_zap_test_maybe_destroy_item(struct monst *,struct obj *,int);
#define maybe_destroy_item teleport_zap_test_maybe_destroy_item
extern void teleport_zap_test_wishcmdassist(int);
#define wishcmdassist teleport_zap_test_wishcmdassist
extern void teleport_zap_test_wish_history_menu(char *);
#define wish_history_menu teleport_zap_test_wish_history_menu
#endif
unsigned probe_layout_count(void){return SIZE(zap_layout);}const char*probe_layout_name(unsigned i){return zap_layout[i].name;}size_t probe_layout_value(unsigned i){return zap_layout[i].value;}
size_t probe_stack(void){return emscripten_stack_get_current();}void*probe_buffer(int i){return buffers[i];}void*probe_obj(int i){return &items[i];}void*probe_mon(int i){return i<0?&gy.youmonst:&monsters[i];}void*probe_pm(int i){return &mons[i];}int probe_type_class(int i){return objects[i].oc_class;}void*probe_ints(void){return integers;}void*probe_any(void){return &any;}void*probe_trap(void){return &trap;}
const char*probe_trace(void){return trace;}const char*probe_result(void){return result;}uintptr_t probe_return(void){return returned;}
void probe_level(int which,int assigned,int match){d_level *p=which==0?&svd.dungeon_topology.d_air_level:which==1?&svd.dungeon_topology.d_water_level:&svd.dungeon_topology.d_rogue_level;p->dnum=assigned?(match?u.uz.dnum:2):0;p->dlevel=assigned?(match?u.uz.dlevel:2):0;}
void probe_option(int i,int v){opts[i]=v;}void probe_seed(unsigned v){rng=v;}void probe_clear(void){trace[0]=result[0]=0;returned=0;}
void probe_item(int i,int typ,long q,int spe){items[i].otyp=typ;items[i].oclass=objects[typ].oc_class;items[i].quan=q;items[i].spe=spe;}
void probe_property(int i,long in,long ex,long blocked){u.uprops[i].intrinsic=in;u.uprops[i].extrinsic=ex;u.uprops[i].blocked=blocked;}
void probe_map(int x,int y,int typ,int flags){levl[x][y].typ=typ;levl[x][y].flags=flags;}
void probe_link(int i,int next,int where,int x,int y){items[i].nobj=next<0?0:&items[next];items[i].nexthere=items[i].nobj;items[i].where=where;items[i].ox=x;items[i].oy=y;if(where==OBJ_MINVENT)items[i].ocarry=&monsters[0];else if(where==OBJ_CONTAINED)items[i].ocontainer=&items[1];}
void probe_grid(int x,int y,int obj,int mon){svl.level.objects[x][y]=obj<0?0:&items[obj];svl.level.monsters[x][y]=mon<0?0:&monsters[mon];}
void probe_scalar(int i,long v){switch(i){case 0:flags.debug=v;break;case 1:u.dx=v;break;case 2:u.dy=v;break;case 3:u.dz=v;break;case 4:items[0].blessed=v;break;case 5:items[0].cursed=v;break;case 6:items[0].oeroded=v;break;case 7:items[0].oeroded2=v;break;case 8:items[0].known=v;break;case 9:items[0].dknown=v;break;case 10:items[0].norevive=v;break;case 11:items[0].corpsenm=v;break;case 12:items[0].age=v;break;case 13:items[0].owornmask=v;break;case 14:monsters[0].mcan=v;break;case 15:monsters[0].mpeaceful=v;break;case 16:monsters[0].msleeping=v;break;case 17:monsters[0].mhp=v;break;case 18:monsters[0].m_lev=v;break;case 19:monsters[0].mtame=v;break;case 20:u.uswallow=v;u.ustuck=v?&monsters[0]:0;break;case 21:u.usteed=v?&monsters[0]:0;break;case 22:iflags.menu_requested=v;break;case 23:iflags.cmdassist=v;break;case 24:iflags.term_gone=v;break;case 25:items[0].recharged=v;break;case 26:u.ulevel=v;break;case 27:monsters[0].minvent=v<0?0:&items[v];break;case 28:gi.invent=v<0?0:&items[v];break;case 29:items[0].in_use=v;break;case 30:items[0].oartifact=v;break;case 31:monsters[0].minvis=v;break;case 32:monsters[0].mstrategy=(unsigned long)v;break;case 33:monsters[0].seen_resistance=(unsigned long)v;break;case 34:gm.multi=v;break;}}
void probe_reset(void){memset((void*)&u,0,sizeof u);memset((void*)&gu,0,sizeof gu);memset((void*)&gn,0,sizeof gn);memset((void*)&gb,0,sizeof gb);memset((void*)&gv,0,sizeof gv);memset((void*)&svc,0,sizeof svc);memset((void*)&gy,0,sizeof gy);memset((void*)&svq,0,sizeof svq);memset((void*)&sysopt,0,sizeof sysopt);memset((void*)&svl,0,sizeof svl);memset((void*)&iflags,0,sizeof iflags);memset((void*)&gi,0,sizeof gi);memset((void*)&disp,0,sizeof disp);memset((void*)&uleft,0,sizeof uleft);memset((void*)&uright,0,sizeof uright);memset((void*)&uarmh,0,sizeof uarmh);memset((void*)&uarmg,0,sizeof uarmg);memset((void*)&uball,0,sizeof uball);memset((void*)&uchain,0,sizeof uchain);memset((void*)&svm,0,sizeof svm);memset((void*)&go,0,sizeof go);memset((void*)&gp,0,sizeof gp);memset((void*)&uskin,0,sizeof uskin);memset((void*)&svb,0,sizeof svb);memset((void*)&uarms,0,sizeof uarms);memset((void*)&uwep,0,sizeof uwep);memset((void*)&uswapwep,0,sizeof uswapwep);memset((void*)&flags,0,sizeof flags);memset((void*)&gz,0,sizeof gz);memset((void*)&WIN_MESSAGE,0,sizeof WIN_MESSAGE);memset((void*)&windowprocs,0,sizeof windowprocs);memset((void*)&gc,0,sizeof gc);memset((void*)&uarmc,0,sizeof uarmc);memset((void*)&svk,0,sizeof svk);memset((void*)&gs,0,sizeof gs);memset((void*)&svd,0,sizeof svd);memset((void*)&gt,0,sizeof gt);memset((void*)&uarm,0,sizeof uarm);memset((void*)&uarmu,0,sizeof uarmu);memset((void*)&uarmf,0,sizeof uarmf);memset((void*)&uamul,0,sizeof uamul);memset((void*)&ublindf,0,sizeof ublindf);memset((void*)&gm,0,sizeof gm);if(growth){free(growth);growth=0;}memset(opts,0,sizeof opts);memset(items,0,sizeof items);memset(extras,0,sizeof extras);memset(monsters,0,sizeof monsters);memset(mextras,0,sizeof mextras);memset(&u,0,sizeof u);memset(&svl,0,sizeof svl);memset(&svc,0,sizeof svc);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(buffers,0,sizeof buffers);memset(integers,0,sizeof integers);memset(&trap,0,sizeof trap);memset(&any,0,sizeof any);objects_globals_init();monst_globals_init();u.ux=10;u.uy=10;u.ulevel=10;u.uhp=u.uhpmax=100;u.umonnum=u.umonster=PM_HUMAN;u.ulycn=NON_PM;gy.youmonst.data=&mons[PM_HUMAN];gy.youmonst.mhp=100;u.uz.dnum=0;u.uz.dlevel=1;for(int i=0;i<8;i++){items[i].otyp=LONG_SWORD;items[i].oclass=WEAPON_CLASS;items[i].quan=1;items[i].o_id=i+1;items[i].corpsenm=PM_NEWT;items[i].ox=10;items[i].oy=10;}for(int i=0;i<4;i++){monsters[i].data=&mons[PM_NEWT];monsters[i].mnum=PM_NEWT;monsters[i].mhp=monsters[i].mhpmax=100;monsters[i].mcanmove=1;monsters[i].mx=11+i;monsters[i].my=10;monsters[i].m_id=i+1;monsters[i].mextra=&mextras[i];}for(int y=0;y<ROWNO;y++){visrows[y]=visibility[y];for(int x=0;x<COLNO;x++){visibility[y][x]=3;levl[x][y].typ=ROOM;}}gv.viz_array=visrows;svm.moves=100;windowprocs.win_create_nhwindow=wincreate;windowprocs.win_putstr=winput;windowprocs.win_destroy_nhwindow=windestroy;windowprocs.win_display_nhwindow=windisplay;windowprocs.win_start_menu=winstart;windowprocs.win_end_menu=winend;windowprocs.win_delay_output=delay;rng=1;probe_clear();}
const char*probe_snapshot(void){snprintf(snap,sizeof snap,"rng%u;hero:%d:%d:%d:%d:%d:%d:%ld:%u;beam:%d:%d;",rng,u.ux,u.uy,u.uhp,u.uhpmax,u.uswallow,u.uinwater,(long)u.ublesscnt,u.uconduct.wishes,gb.bhitpos.x,gb.bhitpos.y);for(int i=0;i<8;i++){char b[512];snprintf(b,sizeof b,"o%d:%d:%ld:%d:%u:%u:%u:%u:%u:%ld:%ld:%d:%d:%d;",i,items[i].otyp,items[i].quan,items[i].spe,items[i].known,items[i].dknown,items[i].blessed,items[i].cursed,items[i].recharged,items[i].age,items[i].owornmask,items[i].ox,items[i].oy,items[i].where);strcat(snap,b);}for(int i=0;i<4;i++){char b[256];snprintf(b,sizeof b,"m%d:%d:%d:%d:%d:%u:%u:%u:%u;",i,monsters[i].mx,monsters[i].my,monsters[i].mhp,monsters[i].mhpmax,monsters[i].mcan,monsters[i].mcanmove,monsters[i].msleeping,monsters[i].minvis);strcat(snap,b);snprintf(b,sizeof b,"flags:%lu:%lu;",monsters[i].mstrategy,monsters[i].seen_resistance);strcat(snap,b);}for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++){char b[128];snprintf(b,sizeof b,"t:%d:%u:%u:%u;",levl[x][y].typ,levl[x][y].flags,levl[x][y].horizontal,levl[x][y].lit);strcat(snap,b);}for(int p=0;p<LAST_PROP+1;p++){char b[128];snprintf(b,sizeof b,"p:%ld:%ld:%ld;",u.uprops[p].intrinsic,u.uprops[p].extrinsic,u.uprops[p].blocked);strcat(snap,b);}return snap;}
uintptr_t probe_invoke(int id,uintptr_t a0,uintptr_t a1,uintptr_t a2,uintptr_t a3,uintptr_t a4,uintptr_t a5,uintptr_t a6,uintptr_t a7,uintptr_t a8){probe_clear();switch(id){
case 0:{int v=zaptype((int)a0);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 1:{learnwand((struct obj *)a0);strcpy(result,"void");returned=0;break;}
case 2:{int v=bhitm((struct monst *)a0,(struct obj *)a1);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 3:{release_hold();strcpy(result,"void");returned=0;break;}
case 4:{probe_objchain((struct obj *)a0);strcpy(result,"void");returned=0;break;}
case 5:{probe_monster((struct monst *)a0);strcpy(result,"void");returned=0;break;}
case 6:{boolean v=get_obj_location((struct obj *)a0,(coordxy *)a1,(coordxy *)a2,(int)a3);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 7:{boolean v=get_mon_location((struct monst *)a0,(coordxy *)a1,(coordxy *)a2,(int)a3);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 8:{struct monst * v=montraits((struct obj *)a0,(coord *)a1,(boolean)a2);returned=(uintptr_t)v;snprintf(result,sizeof result,"mon:%ld",mid(v));break;}
case 9:{struct monst * v=get_container_location((struct obj *)a0,(int *)a1,(int *)a2);returned=(uintptr_t)v;snprintf(result,sizeof result,"mon:%ld",mid(v));break;}
case 10:{boolean v=zombie_can_dig((coordxy)a0,(coordxy)a1);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 11:{struct monst * v=revive((struct obj *)a0,(boolean)a1);returned=(uintptr_t)v;snprintf(result,sizeof result,"mon:%ld",mid(v));break;}
case 12:{revive_egg((struct obj *)a0);strcpy(result,"void");returned=0;break;}
case 13:{int v=unturn_dead((struct monst *)a0);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 14:{unturn_you();strcpy(result,"void");returned=0;break;}
case 15:{cancel_item((struct obj *)a0);strcpy(result,"void");returned=0;break;}
case 16:{blank_novel((struct obj *)a0);strcpy(result,"void");returned=0;break;}
case 17:{boolean v=drain_item((struct obj *)a0,(boolean)a1);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 18:{boolean v=obj_resists((struct obj *)a0,(int)a1,(int)a2);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 19:{boolean v=obj_shudders((struct obj *)a0);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 20:{polyuse((struct obj *)a0,(int)a1,(int)a2);strcpy(result,"void");returned=0;break;}
case 21:{create_polymon((struct obj *)a0,(int)a1);strcpy(result,"void");returned=0;break;}
case 22:{do_osshock((struct obj *)a0);strcpy(result,"void");returned=0;break;}
case 23:{boolean v=obj_unpolyable((struct obj *)a0);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 24:{struct obj * v=poly_obj((struct obj *)a0,(int)a1);returned=(uintptr_t)v;snprintf(result,sizeof result,"obj:%ld",oid(v));break;}
case 25:{int v=stone_to_flesh_obj((struct obj *)a0);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 26:{int v=bhito((struct obj *)a0,(struct obj *)a1);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 27:{int v=bhitpile((struct obj *)a0,(int (*)(struct obj *, struct obj *))a1,(coordxy)a2,(coordxy)a3,(schar)a4);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 28:{int v=zappable((struct obj *)a0);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 29:{do_enlightenment_effect();strcpy(result,"void");returned=0;break;}
case 30:{zapnodir((struct obj *)a0);strcpy(result,"void");returned=0;break;}
case 31:{backfire((struct obj *)a0);strcpy(result,"void");returned=0;break;}
case 32:{int v=zap_ok((struct obj *)a0);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 33:{int v=dozap();returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 34:{boxlock_invent((struct obj *)a0);strcpy(result,"void");returned=0;break;}
case 35:{int v=zapyourself((struct obj *)a0,(boolean)a1);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 36:{ubreatheu((struct attack *)a0);strcpy(result,"void");returned=0;break;}
case 37:{int v=lightdamage((struct obj *)a0,(boolean)a1,(int)a2);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 38:{boolean v=flashburn((long)a0,(boolean)a1);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 39:{boolean v=zap_steed((struct obj *)a0);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 40:{boolean v=cancel_monst((struct monst *)a0,(struct obj *)a1,(boolean)a2,(boolean)a3,(boolean)a4);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 41:{boolean v=zap_updown((struct obj *)a0);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 42:{zapsetup();strcpy(result,"void");returned=0;break;}
case 43:{zapwrapup();strcpy(result,"void");returned=0;break;}
case 44:{weffects((struct obj *)a0);strcpy(result,"void");returned=0;break;}
case 45:{int v=spell_damage_bonus((int)a0);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 46:{int v=spell_hit_bonus((int)a0);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 47:{const char * v=exclam((int)a0);returned=(uintptr_t)v;snprintf(result,sizeof result,"%s",v?v:"[NULL]");break;}
case 48:{hit((const char *)a0,(struct monst *)a1,(const char *)a2);strcpy(result,"void");returned=0;break;}
case 49:{miss((const char *)a0,(struct monst *)a1);strcpy(result,"void");returned=0;break;}
case 50:{skiprange((int)a0,(int *)a1,(int *)a2);strcpy(result,"void");returned=0;break;}
case 51:{maybe_explode_trap((struct trap *)a0,(struct obj *)a1,(boolean *)a2);strcpy(result,"void");returned=0;break;}
case 52:{zap_map((coordxy)a0,(coordxy)a1,(struct obj *)a2);strcpy(result,"void");returned=0;break;}
case 53:{struct monst * v=bhit((int)a0,(int)a1,(int)a2,(enum bhit_call_types)a3,(int (*)(struct monst *, struct obj *))a4,(int (*)(struct obj *, struct obj *))a5,(struct obj **)a6);returned=(uintptr_t)v;snprintf(result,sizeof result,"mon:%ld",mid(v));break;}
case 54:{struct monst * v=boomhit((struct obj *)a0,(int)a1,(int)a2);returned=(uintptr_t)v;snprintf(result,sizeof result,"mon:%ld",mid(v));break;}
case 55:{int v=zhitm((struct monst *)a0,(int)a1,(int)a2,(struct obj **)a3);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 56:{zhitu((int)a0,(int)a1,(const char *)a2,(coordxy)a3,(coordxy)a4);strcpy(result,"void");returned=0;break;}
case 57:{int v=burn_floor_objects((coordxy)a0,(coordxy)a1,(boolean)a2,(boolean)a3);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 58:{bounce_dir((coordxy)a0,(coordxy)a1,(int *)a2,(int *)a3,(int)a4);strcpy(result,"void");returned=0;break;}
case 59:{int v=zap_hit((int)a0,(int)a1);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 60:{disintegrate_mon((struct monst *)a0,(int)a1,(const char *)a2);strcpy(result,"void");returned=0;break;}
case 61:{ubuzz((int)a0,(int)a1);strcpy(result,"void");returned=0;break;}
case 62:{buzz((int)a0,(int)a1,(coordxy)a2,(coordxy)a3,(int)a4,(int)a5);strcpy(result,"void");returned=0;break;}
case 63:{dobuzz((int)a0,(int)a1,(coordxy)a2,(coordxy)a3,(int)a4,(int)a5,(boolean)a6,(boolean)a7,(boolean)a8);strcpy(result,"void");returned=0;break;}
case 64:{melt_ice((coordxy)a0,(coordxy)a1,(const char *)a2);strcpy(result,"void");returned=0;break;}
case 65:{start_melt_ice_timeout((coordxy)a0,(coordxy)a1,(long)a2);strcpy(result,"void");returned=0;break;}
case 66:{melt_ice_away((anything *)a0,(long)a1);strcpy(result,"void");returned=0;break;}
case 67:{int v=zap_over_floor((coordxy)a0,(coordxy)a1,(int)a2,(boolean *)a3,(boolean)a4,(short)a5);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 68:{mon_spell_hits_spot((struct monst *)a0,(int)a1,(coordxy)a2,(coordxy)a3);strcpy(result,"void");returned=0;break;}
case 69:{fracture_rock((struct obj *)a0);strcpy(result,"void");returned=0;break;}
case 70:{boolean v=break_statue((struct obj *)a0);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 71:{boolean v=destroyable((struct obj *)a0,(int)a1);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 72:{int v=adtyp_to_prop((int)a0);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 73:{int v=u_adtyp_resistance_obj((int)a0);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 74:{boolean v=inventory_resistance_check((int)a0);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 75:{char * v=item_what((int)a0);returned=(uintptr_t)v;snprintf(result,sizeof result,"%s",v?v:"[NULL]");break;}
case 76:{int v=maybe_destroy_item((struct monst *)a0,(struct obj *)a1,(int)a2);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 77:{int v=destroy_items((struct monst *)a0,(int)a1,(int)a2);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 78:{int v=resist((struct monst *)a0,(char)a1,(int)a2,(int)a3);returned=(uintptr_t)v;snprintf(result,sizeof result,"%ld",(long)v);break;}
case 79:{wishcmdassist((int)a0);strcpy(result,"void");returned=0;break;}
case 80:{wish_history_add((char *)a0);strcpy(result,"void");returned=0;break;}
case 81:{wish_history_flush();strcpy(result,"void");returned=0;break;}
case 82:{wish_history_menu((char *)a0);strcpy(result,"void");returned=0;break;}
case 83:{makewish();strcpy(result,"void");returned=0;break;}
case 84:{const char * v=flash_str((int)a0,(boolean)a1);returned=(uintptr_t)v;snprintf(result,sizeof result,"%s",v?v:"[NULL]");break;}
}return returned;}
int probe_option_id(const char*s){if(!strcmp(s,"observe_object"))return 30;if(!strcmp(s,"discover_object"))return 31;if(!strcmp(s,"update_inventory"))return 32;if(!strcmp(s,"resists_magm"))return 33;if(!strcmp(s,"disguised_as_mon"))return 34;if(!strcmp(s,"seemimic"))return 35;if(!strcmp(s,"shieldeff"))return 36;if(!strcmp(s,"pline"))return 37;if(!strcmp(s,"find_mac"))return 38;if(!strcmp(s,"mon_adjust_speed"))return 39;if(!strcmp(s,"check_gear_next_turn"))return 40;if(!strcmp(s,"mon_nam"))return 41;if(!strcmp(s,"You"))return 42;if(!strcmp(s,"expels"))return 43;if(!strcmp(s,"monflee"))return 44;if(!strcmp(s,"shieldeff_mon"))return 45;if(!strcmp(s,"canseemon"))return 46;if(!strcmp(s,"Monnam"))return 47;if(!strcmp(s,"xkilled"))return 48;if(!strcmp(s,"newcham"))return 49;if(!strcmp(s,"sensemon"))return 50;if(!strcmp(s,"newmcorpsenm"))return 51;if(!strcmp(s,"u_teleport_mon"))return 52;if(!strcmp(s,"mon_set_minvis"))return 53;if(!strcmp(s,"knowninvisible"))return 54;if(!strcmp(s,"that_is_a_mimic"))return 55;if(!strcmp(s,"closeholdingtrap"))return 56;if(!strcmp(s,"openholdingtrap"))return 57;if(!strcmp(s,"openfallingtrap"))return 58;if(!strcmp(s,"m_is_steadfast"))return 59;if(!strcmp(s,"mhurtle"))return 60;if(!strcmp(s,"wakeup"))return 61;if(!strcmp(s,"abuse_dog"))return 62;if(!strcmp(s,"which_armor"))return 63;if(!strcmp(s,"distant_name"))return 64;if(!strcmp(s,"An"))return 65;if(!strcmp(s,"surface"))return 66;if(!strcmp(s,"mdrop_obj"))return 67;if(!strcmp(s,"healmon"))return 68;if(!strcmp(s,"mcureblindness"))return 69;if(!strcmp(s,"set_mimic_sym"))return 70;if(!strcmp(s,"newsym"))return 71;if(!strcmp(s,"mimic_hit_msg"))return 72;if(!strcmp(s,"more_experienced"))return 73;if(!strcmp(s,"newexplevel"))return 74;if(!strcmp(s,"adjalign"))return 75;if(!strcmp(s,"flash_hits_mon"))return 76;if(!strcmp(s,"sleep_monst"))return 77;if(!strcmp(s,"slept_monst"))return 78;if(!strcmp(s,"stone_furniture_type"))return 79;if(!strcmp(s,"stone_object_type"))return 80;if(!strcmp(s,"set_msg_xy"))return 81;if(!strcmp(s,"monhp_per_lvl"))return 82;if(!strcmp(s,"resists_drli"))return 83;if(!strcmp(s,"killed"))return 84;if(!strcmp(s,"impossible"))return 85;if(!strcmp(s,"m_respond"))return 86;if(!strcmp(s,"hot_pursuit"))return 87;if(!strcmp(s,"map_invisible"))return 88;if(!strcmp(s,"dmgtype_fromattack"))return 89;if(!strcmp(s,"You_feel"))return 90;if(!strcmp(s,"sticks"))return 91;if(!strcmp(s,"set_ustuck"))return 92;if(!strcmp(s,"unstuck"))return 93;if(!strcmp(s,"mstatusline"))return 94;if(!strcmp(s,"display_minventory"))return 95;if(!strcmp(s,"noit_Monnam"))return 96;if(!strcmp(s,"get_mtraits"))return 97;if(!strcmp(s,"makemon"))return 98;if(!strcmp(s,"dealloc_monst"))return 99;if(!strcmp(s,"dmgtype"))return 100;if(!strcmp(s,"neweshk"))return 101;if(!strcmp(s,"replmon"))return 102;if(!strcmp(s,"restore_cham"))return 103;if(!strcmp(s,"t_at"))return 104;if(!strcmp(s,"xname"))return 105;if(!strcmp(s,"cant_finish_meal"))return 106;if(!strcmp(s,"enexto"))return 107;if(!strcmp(s,"corpse_xname"))return 108;if(!strcmp(s,"cant_revive"))return 109;if(!strcmp(s,"free_omid"))return 110;if(!strcmp(s,"free_omonst"))return 111;if(!strcmp(s,"wary_dog"))return 112;if(!strcmp(s,"splitobj"))return 113;if(!strcmp(s,"costly_spot"))return 114;if(!strcmp(s,"in_rooms"))return 115;if(!strcmp(s,"shop_keeper"))return 116;if(!strcmp(s,"shk_your"))return 117;if(!strcmp(s,"stolen_value"))return 118;if(!strcmp(s,"find_mid"))return 119;if(!strcmp(s,"obj_extract_self"))return 120;if(!strcmp(s,"add_to_minv"))return 121;if(!strcmp(s,"tamedog"))return 122;if(!strcmp(s,"mongone"))return 123;if(!strcmp(s,"christen_monst"))return 124;if(!strcmp(s,"eaten_stat"))return 125;if(!strcmp(s,"useup"))return 126;if(!strcmp(s,"delobj_core"))return 127;if(!strcmp(s,"m_useup"))return 128;if(!strcmp(s,"obfree"))return 129;if(!strcmp(s,"dead_species"))return 130;if(!strcmp(s,"attach_egg_hatch_timeout"))return 131;if(!strcmp(s,"Shk_Your"))return 132;if(!strcmp(s,"mon_pmname"))return 133;if(!strcmp(s,"an"))return 134;if(!strcmp(s,"Amonnam"))return 135;if(!strcmp(s,"encumber_msg"))return 136;if(!strcmp(s,"make_stunned"))return 137;if(!strcmp(s,"costly_alteration"))return 138;if(!strcmp(s,"obj_to_any"))return 139;if(!strcmp(s,"peek_timer"))return 140;if(!strcmp(s,"stop_timer"))return 141;if(!strcmp(s,"start_timer"))return 142;if(!strcmp(s,"unbless"))return 143;if(!strcmp(s,"uncurse"))return 144;if(!strcmp(s,"free_oname"))return 145;if(!strcmp(s,"container_weight"))return 146;if(!strcmp(s,"defends"))return 147;if(!strcmp(s,"defends_when_carried"))return 148;if(!strcmp(s,"bot"))return 149;if(!strcmp(s,"addtobill"))return 150;if(!strcmp(s,"delobj"))return 151;if(!strcmp(s,"a_monnam"))return 152;if(!strcmp(s,"sokoban_guilt"))return 153;if(!strcmp(s,"mkobj"))return 154;if(!strcmp(s,"mksobj"))return 155;if(!strcmp(s,"set_corpsenm"))return 156;if(!strcmp(s,"kill_egg"))return 157;if(!strcmp(s,"weight"))return 158;if(!strcmp(s,"can_be_hatched"))return 159;if(!strcmp(s,"erosion_matters"))return 160;if(!strcmp(s,"is_flammable"))return 161;if(!strcmp(s,"is_rottable"))return 162;if(!strcmp(s,"permapoisoned"))return 163;if(!strcmp(s,"o_unleash"))return 164;if(!strcmp(s,"delete_contents"))return 165;if(!strcmp(s,"rnd_class"))return 166;if(!strcmp(s,"fixup_oil"))return 167;if(!strcmp(s,"replace_object"))return 168;if(!strcmp(s,"freeinv_core"))return 169;if(!strcmp(s,"addinv_core1"))return 170;if(!strcmp(s,"addinv_core2"))return 171;if(!strcmp(s,"wearslot"))return 172;if(!strcmp(s,"remove_worn_item"))return 173;if(!strcmp(s,"setuwep"))return 174;if(!strcmp(s,"set_twoweap"))return 175;if(!strcmp(s,"setuswapwep"))return 176;if(!strcmp(s,"setuqwep"))return 177;if(!strcmp(s,"setworn"))return 178;if(!strcmp(s,"set_wear"))return 179;if(!strcmp(s,"wearmask_to_obj"))return 180;if(!strcmp(s,"does_block"))return 181;if(!strcmp(s,"unblock_point"))return 182;if(!strcmp(s,"is_pool_or_lava"))return 183;if(!strcmp(s,"block_point"))return 184;if(!strcmp(s,"contained_cost"))return 185;if(!strcmp(s,"inhishop"))return 186;if(!strcmp(s,"make_angry_shk"))return 187;if(!strcmp(s,"Shknam"))return 188;if(!strcmp(s,"Norep"))return 189;if(!strcmp(s,"animate_statue"))return 190;if(!strcmp(s,"obj_stop_timers"))return 191;if(!strcmp(s,"pline_The"))return 192;if(!strcmp(s,"place_object"))return 193;if(!strcmp(s,"debugcore"))return 194;if(!strcmp(s,"Tobjnam"))return 195;if(!strcmp(s,"unpunish"))return 196;if(!strcmp(s,"livelog_printf"))return 197;if(!strcmp(s,"boxlock"))return 198;if(!strcmp(s,"hideunder"))return 199;if(!strcmp(s,"the"))return 200;if(!strcmp(s,"rndmonnam"))return 201;if(!strcmp(s,"display_cinventory"))return 202;if(!strcmp(s,"set_cknown_lknown"))return 203;if(!strcmp(s,"You_hear"))return 204;if(!strcmp(s,"breaks"))return 205;if(!strcmp(s,"hero_breaks"))return 206;if(!strcmp(s,"newsym_force"))return 207;if(!strcmp(s,"rloco"))return 208;if(!strcmp(s,"maybe_unhide_at"))return 209;if(!strcmp(s,"corpse_revive_type"))return 210;if(!strcmp(s,"cxname_singular"))return 211;if(!strcmp(s,"noname_monnam"))return 212;if(!strcmp(s,"The"))return 213;if(!strcmp(s,"exercise"))return 214;if(!strcmp(s,"activate_statue_trap"))return 215;if(!strcmp(s,"recreate_pile_at"))return 216;if(!strcmp(s,"fill_pit"))return 217;if(!strcmp(s,"enlightenment"))return 218;if(!strcmp(s,"litroom"))return 219;if(!strcmp(s,"findit"))return 220;if(!strcmp(s,"create_critters"))return 221;if(!strcmp(s,"losehp"))return 222;if(!strcmp(s,"useupall"))return 223;if(!strcmp(s,"check_capacity"))return 224;if(!strcmp(s,"getobj"))return 225;if(!strcmp(s,"check_unpaid"))return 226;if(!strcmp(s,"getdir"))return 227;if(!strcmp(s,"killer_xname"))return 228;if(!strcmp(s,"monstseesu"))return 229;if(!strcmp(s,"monstunseesu"))return 230;if(!strcmp(s,"ugolemeffects"))return 231;if(!strcmp(s,"explode"))return 232;if(!strcmp(s,"burn_away_slime"))return 233;if(!strcmp(s,"burnarmor"))return 234;if(!strcmp(s,"ignite_items"))return 235;if(!strcmp(s,"polyself"))return 236;if(!strcmp(s,"losexp"))return 237;if(!strcmp(s,"yname"))return 238;if(!strcmp(s,"incr_itimeout"))return 239;if(!strcmp(s,"self_invis_message"))return 240;if(!strcmp(s,"speed_up"))return 241;if(!strcmp(s,"fall_asleep"))return 242;if(!strcmp(s,"u_slow_down"))return 243;if(!strcmp(s,"tele"))return 244;if(!strcmp(s,"urgent_pline"))return 245;if(!strcmp(s,"done"))return 246;if(!strcmp(s,"healup"))return 247;if(!strcmp(s,"ustatusline"))return 248;if(!strcmp(s,"polymon"))return 249;if(!strcmp(s,"fix_petrification"))return 250;if(!strcmp(s,"merged"))return 251;if(!strcmp(s,"ansimpleoname"))return 252;if(!strcmp(s,"bare_artifactname"))return 253;if(!strcmp(s,"resists_blnd"))return 254;if(!strcmp(s,"make_blinded"))return 255;if(!strcmp(s,"Your"))return 256;if(!strcmp(s,"resists_blnd_by_arti"))return 257;if(!strcmp(s,"find_ac"))return 258;if(!strcmp(s,"rehumanize"))return 259;if(!strcmp(s,"normal_shape"))return 260;if(!strcmp(s,"monkilled"))return 261;if(!strcmp(s,"ceiling"))return 262;if(!strcmp(s,"update_mapseen_for"))return 263;if(!strcmp(s,"db_under_typ"))return 264;if(!strcmp(s,"display_binventory"))return 265;if(!strcmp(s,"is_db_wall"))return 266;if(!strcmp(s,"find_drawbridge"))return 267;if(!strcmp(s,"open_drawbridge"))return 268;if(!strcmp(s,"on_level"))return 269;if(!strcmp(s,"ok_to_quest"))return 270;if(!strcmp(s,"is_drawbridge_wall"))return 271;if(!strcmp(s,"close_drawbridge"))return 272;if(!strcmp(s,"destroy_drawbridge"))return 273;if(!strcmp(s,"body_part"))return 274;if(!strcmp(s,"hard_helmet"))return 275;if(!strcmp(s,"mksobj_at"))return 276;if(!strcmp(s,"stackobj"))return 277;if(!strcmp(s,"dotrap"))return 278;if(!strcmp(s,"is_ice"))return 279;if(!strcmp(s,"engr_at"))return 280;if(!strcmp(s,"is_pool"))return 281;if(!strcmp(s,"is_lava"))return 282;if(!strcmp(s,"makeplural"))return 283;if(!strcmp(s,"zap_dig"))return 284;if(!strcmp(s,"acurr"))return 285;if(!strcmp(s,"spell_skilltype"))return 286;if(!strcmp(s,"vtense"))return 287;if(!strcmp(s,"deltrap"))return 288;if(!strcmp(s,"del_engr"))return 289;if(!strcmp(s,"random_engraving"))return 290;if(!strcmp(s,"make_engr_at"))return 291;if(!strcmp(s,"rloc_engr"))return 292;if(!strcmp(s,"wipe_engr_at"))return 293;if(!strcmp(s,"glyph_at"))return 294;if(!strcmp(s,"show_map_spot"))return 295;if(!strcmp(s,"cvt_sdoor_to_door"))return 296;if(!strcmp(s,"recalc_block_point"))return 297;if(!strcmp(s,"draft_message"))return 298;if(!strcmp(s,"force_decor"))return 299;if(!strcmp(s,"trapname"))return 300;if(!strcmp(s,"Invocation_lev"))return 301;if(!strcmp(s,"In_mines"))return 302;if(!strcmp(s,"In_hell"))return 303;if(!strcmp(s,"tmp_at"))return 304;if(!strcmp(s,"rn2_on_display_rng"))return 305;if(!strcmp(s,"inside_shop"))return 306;if(!strcmp(s,"shkcatch"))return 307;if(!strcmp(s,"show_transient_light"))return 308;if(!strcmp(s,"hits_bars"))return 309;if(!strcmp(s,"Yname2"))return 310;if(!strcmp(s,"otense"))return 311;if(!strcmp(s,"shade_miss"))return 312;if(!strcmp(s,"unmap_object"))return 313;if(!strcmp(s,"ship_object"))return 314;if(!strcmp(s,"doorlock"))return 315;if(!strcmp(s,"add_damage"))return 316;if(!strcmp(s,"closed_door"))return 317;if(!strcmp(s,"sobj_at"))return 318;if(!strcmp(s,"test_move"))return 319;if(!strcmp(s,"pay_for_damage"))return 320;if(!strcmp(s,"transient_light_cleanup"))return 321;if(!strcmp(s,"xytodir"))return 322;if(!strcmp(s,"throwit_mon_hit"))return 323;if(!strcmp(s,"dmgval"))return 324;if(!strcmp(s,"thitu"))return 325;if(!strcmp(s,"endmultishot"))return 326;if(!strcmp(s,"wake_nearto"))return 327;if(!strcmp(s,"defended"))return 328;if(!strcmp(s,"Resists_Elem"))return 329;if(!strcmp(s,"acid_damage"))return 330;if(!strcmp(s,"erode_armor"))return 331;if(!strcmp(s,"disintegrate_arm"))return 332;if(!strcmp(s,"poisoned"))return 333;if(!strcmp(s,"hliquid"))return 334;if(!strcmp(s,"death_inflicted_by"))return 335;if(!strcmp(s,"useupf"))return 336;if(!strcmp(s,"mlifesaver"))return 337;if(!strcmp(s,"is_quest_artifact"))return 338;if(!strcmp(s,"extract_from_minvent"))return 339;if(!strcmp(s,"zapdir_to_glyph"))return 340;if(!strcmp(s,"unmap_invisible"))return 341;if(!strcmp(s,"mon_reflects"))return 342;if(!strcmp(s,"disguised_as_non_mon"))return 343;if(!strcmp(s,"nomul"))return 344;if(!strcmp(s,"pline_dir"))return 345;if(!strcmp(s,"ureflects"))return 346;if(!strcmp(s,"stop_occupation"))return 347;if(!strcmp(s,"spot_stop_timers"))return 348;if(!strcmp(s,"trap_ice_effects"))return 349;if(!strcmp(s,"obj_ice_effects"))return 350;if(!strcmp(s,"unearth_objs"))return 351;if(!strcmp(s,"vision_recalc"))return 352;if(!strcmp(s,"boulder_hits_pool"))return 353;if(!strcmp(s,"spoteffects"))return 354;if(!strcmp(s,"minliquid"))return 355;if(!strcmp(s,"long_to_any"))return 356;if(!strcmp(s,"delfloortrap"))return 357;if(!strcmp(s,"create_gas_cloud"))return 358;if(!strcmp(s,"maketrap"))return 359;if(!strcmp(s,"mintrap"))return 360;if(!strcmp(s,"dryup"))return 361;if(!strcmp(s,"is_moat"))return 362;if(!strcmp(s,"waterbody_name"))return 363;if(!strcmp(s,"fix_wall_spines"))return 364;if(!strcmp(s,"bury_objs"))return 365;if(!strcmp(s,"set_uinwater"))return 366;if(!strcmp(s,"docrt"))return 367;if(!strcmp(s,"reset_utrap"))return 368;if(!strcmp(s,"set_utrap"))return 369;if(!strcmp(s,"spot_time_left"))return 370;if(!strcmp(s,"dissolve_bars"))return 371;if(!strcmp(s,"picking_at"))return 372;if(!strcmp(s,"reset_pick"))return 373;if(!strcmp(s,"billable"))return 374;if(!strcmp(s,"shkname"))return 375;if(!strcmp(s,"breakobj"))return 376;if(!strcmp(s,"dealloc_oextra"))return 377;if(!strcmp(s,"cloak_simple_name"))return 378;if(!strcmp(s,"suit_simple_name"))return 379;if(!strcmp(s,"shirt_simple_name"))return 380;if(!strcmp(s,"helm_simple_name"))return 381;if(!strcmp(s,"gloves_simple_name"))return 382;if(!strcmp(s,"boots_simple_name"))return 383;if(!strcmp(s,"shield_simple_name"))return 384;if(!strcmp(s,"simpleonames"))return 385;if(!strcmp(s,"hcolor"))return 386;if(!strcmp(s,"recharge"))return 387;if(!strcmp(s,"potionbreathe"))return 388;if(!strcmp(s,"Ring_gone"))return 389;if(!strcmp(s,"setnotworn"))return 390;if(!strcmp(s,"add_menu"))return 391;if(!strcmp(s,"select_menu"))return 392;if(!strcmp(s,"getlin"))return 393;if(!strcmp(s,"readobjnam"))return 394;if(!strcmp(s,"artifact_origin"))return 395;if(!strcmp(s,"doname"))return 396;if(!strcmp(s,"u_safe_from_fatal_corpse"))return 397;if(!strcmp(s,"aobjnam"))return 398;if(!strcmp(s,"hold_another_object"))return 399;if(!strcmp(s,"rnd_hallublast"))return 400;return -1;}
static int mon_callback(struct monst*m,struct obj*o){append("cbmon:%ld:%ld;",mid(m),oid(o));callback(4);return opts[11];}static int obj_callback(struct obj*a,struct obj*b){append("cbobj:%ld:%ld;",oid(a),oid(b));callback(5);return opts[12];}
uintptr_t probe_callback(int i){switch(i){case 0:return(uintptr_t)mon_callback;case 1:return(uintptr_t)obj_callback;case 2:return(uintptr_t)bhitm;case 3:return(uintptr_t)bhito;default:return 0;}}
const char*probe_destroy(int row,int col){return destroy_strings[row][col];}
extern const char *teleport_zap_trap_consumer(const struct obj*,int);
const char*probe_consumer(int row,long quantity){struct obj obj=cg.zeroobj;obj.quan=quantity;return teleport_zap_trap_consumer(&obj,row);}
uintptr_t probe_history(int i){
#ifdef TELEPORT_REFERENCE_TU
return i<0?(uintptr_t)wish_history_idx:(uintptr_t)wish_history[i];
#else
extern uintptr_t teleport_zap_test_history(int);return teleport_zap_test_history(i);
#endif
}
