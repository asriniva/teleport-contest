/* Controlled external-world callbacks; original projectile policy remains in unchanged C or JS. */
#include "hack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <emscripten/stack.h>
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/mthrowu.c"
#else
extern boolean teleport_mthrowu_test_drop_throw(struct obj *,boolean,coordxy,coordxy);
#define drop_throw teleport_mthrowu_test_drop_throw
extern int teleport_mthrowu_test_monmulti(struct monst *,struct obj *,struct obj *);
#define monmulti teleport_mthrowu_test_monmulti
extern void teleport_mthrowu_test_monshoot(struct monst *,struct obj *,struct obj *);
#define monshoot teleport_mthrowu_test_monshoot
extern boolean teleport_mthrowu_test_ucatchgem(struct obj *,struct monst *);
#define ucatchgem teleport_mthrowu_test_ucatchgem
extern boolean teleport_mthrowu_test_u_catch_thrown_obj(struct obj *);
#define u_catch_thrown_obj teleport_mthrowu_test_u_catch_thrown_obj
extern void teleport_mthrowu_test_return_from_mtoss(struct monst *,struct obj *,boolean);
#define return_from_mtoss teleport_mthrowu_test_return_from_mtoss
extern const char * teleport_mthrowu_test_breathwep_name(int);
#define breathwep_name teleport_mthrowu_test_breathwep_name
extern boolean teleport_mthrowu_test_blocking_terrain(coordxy,coordxy);
#define blocking_terrain teleport_mthrowu_test_blocking_terrain
extern int teleport_mthrowu_test_m_lined_up(struct monst *,struct monst *);
#define m_lined_up teleport_mthrowu_test_m_lined_up
#endif
#include "tu-mthrowu-layout.h"
__typeof__(gy) gy;__typeof__(gm) gm;__typeof__(gt) gt;__typeof__(gb) gb;__typeof__(gn) gn;__typeof__(gv) gv;__typeof__(gi) gi;__typeof__(gu) gu;__typeof__(svc) svc;__typeof__(svm) svm;__typeof__(svl) svl;__typeof__(go) go;struct you u;struct flag flags;struct instance_flags iflags;__typeof__(windowprocs) windowprocs;
const struct c_common_strings c_common_strings={.c_something="something",.c_Something="Something",.c_vision_clears="vision clears."};
const struct Gender genders[]={{"male","he","him","his","Mal"},{"female","she","her","her","Fem"},{"neuter","it","it","its","Ntr"},{"group","they","them","their","Grp"}};
struct obj *uwep,*uarmg,*uswapwep,*uquiver;
static struct monst monsters[8];static struct mextra extras[8];static struct edog dogs[8];static struct obj*pool[64],*pointers[8];static struct attack attk_pool[8];static struct throw_and_return_weapon returning;
static char tracebuf[2097152],snapbuf[1048576],names[64][BUFSZ];static int ti,ni;static long opts[512];static int configured[512],rolls[16384],nr,ri;static unsigned seed;static const char *callerfile,*callerfunc;static int callerline;static int growth_stage,reenter_stage;static void*grown;static int frees;
static void append(const char*f,...){va_list ap;va_start(ap,f);ti+=vsnprintf(tracebuf+ti,sizeof tracebuf-ti,f,ap);va_end(ap);}
static int oid(struct obj*o){if(!o)return -1;for(int i=0;i<64;i++)if(pool[i]==o)return i;return -99;}
static int mid(struct monst*m){if(m==&gy.youmonst)return -2;if(!m)return -1;for(int i=0;i<8;i++)if(m==&monsters[i])return i;return -99;}
static void callback(int stage){if(growth_stage==stage){growth_stage=0;grown=malloc(48*1024*1024);append("grow:%d;",stage);}if(reenter_stage==stage){reenter_stage=0;append("reenter:%d;",lined_up(&monsters[7]));}}
static void unlink_obj(struct obj**head,struct obj*o){while(*head&&*head!=o)head=&(*head)->nobj;if(*head)*head=o->nobj;}
static char*namebuf(const char*s){char*b=names[ni++%64];snprintf(b,BUFSZ,"%s",s?s:"(null)");return b;}
static void message(const char*tag,const char*f,va_list ap){char b[4096];vsnprintf(b,sizeof b,f,ap);append("%s:%s;",tag,b);}
static const char *dep_names[]={"Monnam","Resists_Elem","The","Tobjnam","You","You_hear","Your","acurr","acurrstr","add_to_minv","an","artifact_hit","autoreturn_weapon","body_part","breaks","calc_capacity","can_blnd","canseemon","clear_dknown","clear_path","closed_door","cvt_adtyp_to_mseenres","delobj","discover_object","dissolve_bars","distant_name","dmgval","dobuzz","doname","down_gate","dropy","exclam","exercise","extract_from_minvent","find_mac","flooreffects","freehand","get_atkdam_type","harmless_missile","hates_silver","hero_breaks","hit","hliquid","hold_another_object","impossible","is_art","is_flammable","is_lava","is_pool","is_waterwall","isok","killer_xname","losehp","make_blinded","make_stoned","makeplural","mbodypart","minstapetrify","miss","mksobj","mon_hates_silver","mon_nam","mon_wield_item","mondied","monkilled","monstseesu","monstunseesu","mshot_xname","mswings_verb","multishot_class_bonus","munstone","mwelded","newsym","nomul","obfree","obj_extract_self","obj_is_pname","obj_sheds_light","observe_object","omon_adj","otense","panic","passive_obj","permapoisoned","place_object","pline","pline_The","pline_mon","poisoned","poly_when_stoned","polymon","potionhit","pronoun_gender","rn2","rn2_on_display_rng","rnd","rounddiv","seemimic","select_rwep","sensemon","set_msg_xy","setmangry","setmnotwielded","shade_miss","ship_object","should_mulch_missile","simpleonames","singular","snuff_candle","sobj_at","some_mon_nam","spec_abon","splitobj","stackobj","stop_occupation","the","tmp_at","vtense","wake_nearto","weight","xkilled","xname"};
enum { DEP_Monnam=0,DEP_Resists_Elem=1,DEP_The=2,DEP_Tobjnam=3,DEP_You=4,DEP_You_hear=5,DEP_Your=6,DEP_acurr=7,DEP_acurrstr=8,DEP_add_to_minv=9,DEP_an=10,DEP_artifact_hit=11,DEP_autoreturn_weapon=12,DEP_body_part=13,DEP_breaks=14,DEP_calc_capacity=15,DEP_can_blnd=16,DEP_canseemon=17,DEP_clear_dknown=18,DEP_clear_path=19,DEP_closed_door=20,DEP_cvt_adtyp_to_mseenres=21,DEP_delobj=22,DEP_discover_object=23,DEP_dissolve_bars=24,DEP_distant_name=25,DEP_dmgval=26,DEP_dobuzz=27,DEP_doname=28,DEP_down_gate=29,DEP_dropy=30,DEP_exclam=31,DEP_exercise=32,DEP_extract_from_minvent=33,DEP_find_mac=34,DEP_flooreffects=35,DEP_freehand=36,DEP_get_atkdam_type=37,DEP_harmless_missile=38,DEP_hates_silver=39,DEP_hero_breaks=40,DEP_hit=41,DEP_hliquid=42,DEP_hold_another_object=43,DEP_impossible=44,DEP_is_art=45,DEP_is_flammable=46,DEP_is_lava=47,DEP_is_pool=48,DEP_is_waterwall=49,DEP_isok=50,DEP_killer_xname=51,DEP_losehp=52,DEP_make_blinded=53,DEP_make_stoned=54,DEP_makeplural=55,DEP_mbodypart=56,DEP_minstapetrify=57,DEP_miss=58,DEP_mksobj=59,DEP_mon_hates_silver=60,DEP_mon_nam=61,DEP_mon_wield_item=62,DEP_mondied=63,DEP_monkilled=64,DEP_monstseesu=65,DEP_monstunseesu=66,DEP_mshot_xname=67,DEP_mswings_verb=68,DEP_multishot_class_bonus=69,DEP_munstone=70,DEP_mwelded=71,DEP_newsym=72,DEP_nomul=73,DEP_obfree=74,DEP_obj_extract_self=75,DEP_obj_is_pname=76,DEP_obj_sheds_light=77,DEP_observe_object=78,DEP_omon_adj=79,DEP_otense=80,DEP_panic=81,DEP_passive_obj=82,DEP_permapoisoned=83,DEP_place_object=84,DEP_pline=85,DEP_pline_The=86,DEP_pline_mon=87,DEP_poisoned=88,DEP_poly_when_stoned=89,DEP_polymon=90,DEP_potionhit=91,DEP_pronoun_gender=92,DEP_rn2=93,DEP_rn2_on_display_rng=94,DEP_rnd=95,DEP_rounddiv=96,DEP_seemimic=97,DEP_select_rwep=98,DEP_sensemon=99,DEP_set_msg_xy=100,DEP_setmangry=101,DEP_setmnotwielded=102,DEP_shade_miss=103,DEP_ship_object=104,DEP_should_mulch_missile=105,DEP_simpleonames=106,DEP_singular=107,DEP_snuff_candle=108,DEP_sobj_at=109,DEP_some_mon_nam=110,DEP_spec_abon=111,DEP_splitobj=112,DEP_stackobj=113,DEP_stop_occupation=114,DEP_the=115,DEP_tmp_at=116,DEP_vtense=117,DEP_wake_nearto=118,DEP_weight=119,DEP_xkilled=120,DEP_xname=121 };
boolean Resists_Elem(struct monst * a0,int a1){append("Resists_Elem:%d:%ld;",mid(a0),(long)a1);callback(DEP_Resists_Elem);return configured[DEP_Resists_Elem]?opts[DEP_Resists_Elem]:0;}
schar acurr(int a0){append("acurr:%ld;",(long)a0);callback(DEP_acurr);return configured[DEP_acurr]?opts[DEP_acurr]:0;}
schar acurrstr(void){append("acurrstr;");callback(DEP_acurrstr);return configured[DEP_acurrstr]?opts[DEP_acurrstr]:0;}
boolean artifact_hit(struct monst * a0,struct monst * a1,struct obj * a2,int * a3,int a4){append("artifact_hit:%d:%d:%d:ptr:%ld;",mid(a0),mid(a1),oid(a2),(long)a4);callback(DEP_artifact_hit);return configured[DEP_artifact_hit]?opts[DEP_artifact_hit]:0;}
int calc_capacity(int a0){append("calc_capacity:%ld;",(long)a0);callback(DEP_calc_capacity);return configured[DEP_calc_capacity]?opts[DEP_calc_capacity]:0;}
boolean can_blnd(struct monst * a0,struct monst * a1,uchar a2,struct obj * a3){append("can_blnd:%d:%d:%ld:%d;",mid(a0),mid(a1),(long)a2,oid(a3));callback(DEP_can_blnd);return configured[DEP_can_blnd]?opts[DEP_can_blnd]:0;}
boolean closed_door(coordxy a0,coordxy a1){append("closed_door:%ld:%ld;",(long)a0,(long)a1);callback(DEP_closed_door);return configured[DEP_closed_door]?opts[DEP_closed_door]:0;}
unsigned long cvt_adtyp_to_mseenres(uchar a0){append("cvt_adtyp_to_mseenres:%ld;",(long)a0);callback(DEP_cvt_adtyp_to_mseenres);return configured[DEP_cvt_adtyp_to_mseenres]?opts[DEP_cvt_adtyp_to_mseenres]:0;}
void dissolve_bars(coordxy a0,coordxy a1){append("dissolve_bars:%ld:%ld;",(long)a0,(long)a1);callback(DEP_dissolve_bars);}
void dobuzz(int a0,int a1,coordxy a2,coordxy a3,int a4,int a5,boolean a6,boolean a7,boolean a8){append("dobuzz:%ld:%ld:%ld:%ld:%ld:%ld:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2,(long)a3,(long)a4,(long)a5,(long)a6,(long)a7,(long)a8);callback(DEP_dobuzz);}
schar down_gate(coordxy a0,coordxy a1){append("down_gate:%ld:%ld;",(long)a0,(long)a1);callback(DEP_down_gate);return configured[DEP_down_gate]?opts[DEP_down_gate]:-1;}
const char * exclam(int a0){append("exclam:%ld;",(long)a0);callback(DEP_exclam);return namebuf("value");}
void exercise(int a0,boolean a1){append("exercise:%ld:%ld;",(long)a0,(long)a1);callback(DEP_exercise);}
int freehand(void){append("freehand;");callback(DEP_freehand);return configured[DEP_freehand]?opts[DEP_freehand]:0;}
boolean harmless_missile(struct obj * a0){append("harmless_missile:%d;",oid(a0));callback(DEP_harmless_missile);return configured[DEP_harmless_missile]?opts[DEP_harmless_missile]:0;}
boolean hates_silver(struct permonst * a0){append("hates_silver:ptr;");callback(DEP_hates_silver);return configured[DEP_hates_silver]?opts[DEP_hates_silver]:0;}
void hit(const char * a0,struct monst * a1,const char * a2){append("hit:%s:%d:%s;",a0,mid(a1),a2);callback(DEP_hit);}
const char * hliquid(const char * a0){append("hliquid:%s;",a0);callback(DEP_hliquid);return namebuf("value");}
boolean is_flammable(struct obj * a0){append("is_flammable:%d;",oid(a0));callback(DEP_is_flammable);return configured[DEP_is_flammable]?opts[DEP_is_flammable]:0;}
boolean is_lava(coordxy a0,coordxy a1){append("is_lava:%ld:%ld;",(long)a0,(long)a1);callback(DEP_is_lava);return configured[DEP_is_lava]?opts[DEP_is_lava]:0;}
boolean is_pool(coordxy a0,coordxy a1){append("is_pool:%ld:%ld;",(long)a0,(long)a1);callback(DEP_is_pool);return configured[DEP_is_pool]?opts[DEP_is_pool]:0;}
boolean is_waterwall(coordxy a0,coordxy a1){append("is_waterwall:%ld:%ld;",(long)a0,(long)a1);callback(DEP_is_waterwall);return configured[DEP_is_waterwall]?opts[DEP_is_waterwall]:0;}
void miss(const char * a0,struct monst * a1){append("miss:%s:%d;",a0,mid(a1));callback(DEP_miss);}
boolean mon_hates_silver(struct monst * a0){append("mon_hates_silver:%d;",mid(a0));callback(DEP_mon_hates_silver);return configured[DEP_mon_hates_silver]?opts[DEP_mon_hates_silver]:0;}
int mon_wield_item(struct monst * a0){append("mon_wield_item:%d;",mid(a0));callback(DEP_mon_wield_item);return configured[DEP_mon_wield_item]?opts[DEP_mon_wield_item]:0;}
void monstseesu(unsigned long a0){append("monstseesu:%ld;",(long)a0);callback(DEP_monstseesu);}
void monstunseesu(unsigned long a0){append("monstunseesu:%ld;",(long)a0);callback(DEP_monstunseesu);}
const char * mswings_verb(struct obj * a0,boolean a1){append("mswings_verb:%d:%ld;",oid(a0),(long)a1);callback(DEP_mswings_verb);return namebuf("value");}
int multishot_class_bonus(int a0,struct obj * a1,struct obj * a2){append("multishot_class_bonus:%ld:%d:%d;",(long)a0,oid(a1),oid(a2));callback(DEP_multishot_class_bonus);return configured[DEP_multishot_class_bonus]?opts[DEP_multishot_class_bonus]:0;}
boolean munstone(struct monst * a0,boolean a1){append("munstone:%d:%ld;",mid(a0),(long)a1);callback(DEP_munstone);return configured[DEP_munstone]?opts[DEP_munstone]:0;}
boolean mwelded(struct obj * a0){append("mwelded:%d;",oid(a0));callback(DEP_mwelded);return configured[DEP_mwelded]?opts[DEP_mwelded]:0;}
void newsym(coordxy a0,coordxy a1){append("newsym:%ld:%ld;",(long)a0,(long)a1);callback(DEP_newsym);}
boolean obj_is_pname(struct obj * a0){append("obj_is_pname:%d;",oid(a0));callback(DEP_obj_is_pname);return configured[DEP_obj_is_pname]?opts[DEP_obj_is_pname]:0;}
boolean obj_sheds_light(struct obj * a0){append("obj_sheds_light:%d;",oid(a0));callback(DEP_obj_sheds_light);return configured[DEP_obj_sheds_light]?opts[DEP_obj_sheds_light]:0;}
void observe_object(struct obj * a0){append("observe_object:%d;",oid(a0));callback(DEP_observe_object);}
int omon_adj(struct monst * a0,struct obj * a1,boolean a2){append("omon_adj:%d:%d:%ld;",mid(a0),oid(a1),(long)a2);callback(DEP_omon_adj);return configured[DEP_omon_adj]?opts[DEP_omon_adj]:0;}
void passive_obj(struct monst * a0,struct obj * a1,struct attack * a2){append("passive_obj:%d:%d:ptr;",mid(a0),oid(a1));callback(DEP_passive_obj);}
boolean permapoisoned(struct obj * a0){append("permapoisoned:%d;",oid(a0));callback(DEP_permapoisoned);return configured[DEP_permapoisoned]?opts[DEP_permapoisoned]:0;}
void poisoned(const char * a0,int a1,const char * a2,int a3,boolean a4){append("poisoned:%s:%ld:%s:%ld:%ld;",a0,(long)a1,a2,(long)a3,(long)a4);callback(DEP_poisoned);}
boolean poly_when_stoned(struct permonst * a0){append("poly_when_stoned:ptr;");callback(DEP_poly_when_stoned);return configured[DEP_poly_when_stoned]?opts[DEP_poly_when_stoned]:0;}
int polymon(int a0){append("polymon:%ld;",(long)a0);callback(DEP_polymon);return configured[DEP_polymon]?opts[DEP_polymon]:0;}
int rounddiv(long a0,int a1){append("rounddiv:%ld:%ld;",(long)a0,(long)a1);callback(DEP_rounddiv);return configured[DEP_rounddiv]?opts[DEP_rounddiv]:0;}
void seemimic(struct monst * a0){append("seemimic:%d;",mid(a0));callback(DEP_seemimic);}
void set_msg_xy(coordxy a0,coordxy a1){append("set_msg_xy:%ld:%ld;",(long)a0,(long)a1);callback(DEP_set_msg_xy);}
boolean shade_miss(struct monst * a0,struct monst * a1,struct obj * a2,boolean a3,boolean a4){append("shade_miss:%d:%d:%d:%ld:%ld;",mid(a0),mid(a1),oid(a2),(long)a3,(long)a4);callback(DEP_shade_miss);return configured[DEP_shade_miss]?opts[DEP_shade_miss]:0;}
boolean should_mulch_missile(struct obj * a0){append("should_mulch_missile:%d;",oid(a0));callback(DEP_should_mulch_missile);return configured[DEP_should_mulch_missile]?opts[DEP_should_mulch_missile]:0;}
boolean snuff_candle(struct obj * a0){append("snuff_candle:%d;",oid(a0));callback(DEP_snuff_candle);return configured[DEP_snuff_candle]?opts[DEP_snuff_candle]:0;}
struct obj * sobj_at(int a0,coordxy a1,coordxy a2){append("sobj_at:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2);callback(DEP_sobj_at);return 0;}
int spec_abon(struct obj * a0,struct monst * a1){append("spec_abon:%d:%d;",oid(a0),mid(a1));callback(DEP_spec_abon);return configured[DEP_spec_abon]?opts[DEP_spec_abon]:0;}
void stackobj(struct obj * a0){append("stackobj:%d;",oid(a0));callback(DEP_stackobj);}
void stop_occupation(void){append("stop_occupation;");callback(DEP_stop_occupation);}
void tmp_at(coordxy a0,coordxy a1){append("tmp_at:%ld:%ld;",(long)a0,(long)a1);callback(DEP_tmp_at);}
void wake_nearto(coordxy a0,coordxy a1,int a2){append("wake_nearto:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2);callback(DEP_wake_nearto);}
static void kill_object(struct obj*o){if(!o)return;int at=oid(o);obj_extract_self(o);if(at>=0){pool[at]=0;free(o);frees++;}}
void panic(const char*s,...){abort();}
void pline(const char*f,...){va_list a;va_start(a,f);message("pline",f,a);va_end(a);}
void pline_The(const char*f,...){va_list a;va_start(a,f);message("The",f,a);va_end(a);}
void You(const char*f,...){va_list a;va_start(a,f);message("You",f,a);va_end(a);}
void Your(const char*f,...){va_list a;va_start(a,f);message("Your",f,a);va_end(a);}
void You_hear(const char*f,...){va_list a;va_start(a,f);message("hear",f,a);va_end(a);}
void pline_mon(struct monst*m,const char*f,...){va_list a;va_start(a,f);append("pline_mon:%d;",mid(m));message("mon",f,a);va_end(a);}
void impossible(const char*f,...){va_list a;va_start(a,f);message("impossible",f,a);va_end(a);}
boolean rng_log_enabled(void){return !configured[500];}
void rng_log_set_caller(const char*f,int line,const char*fn){callerfile=strrchr(f,'/');callerfile=callerfile?callerfile+1:f;callerline=line;callerfunc=fn;}
static int draw(const char*fn,int n){if(n<=0)abort();seed=seed*1664525U+1013904223U;int r=(unsigned)(ri<nr?rolls[ri]:seed)%(unsigned)n;ri++;append("rng:%s:%d:%d",fn,n,r);if(rng_log_enabled())append(":%s:%d:%s",callerfile,callerline,callerfunc);append(";");return r;}
int (rn2)(int n){return draw("rn2",n);}
int (rnd)(int n){return draw("rnd",n)+1;}
int rn2_on_display_rng(int n){append("display:%d;",n);return (unsigned)(ri<nr?rolls[ri++]:0)%(unsigned)n;}
char*xname(struct obj*o){append("xname:%d;",oid(o));callback(DEP_xname);return namebuf(o->quan>1?"projectiles":"projectile");}
char*mshot_xname(struct obj*o){append("mshot:%d;",oid(o));return namebuf("projectile");}
char*simpleonames(struct obj*o){append("simple:%d;",oid(o));return namebuf("projectile");}
char*killer_xname(struct obj*o){append("killer:%d;",oid(o));return namebuf("a projectile");}
char*doname(struct obj*o){append("doname:%d;",oid(o));return namebuf("projectile");}
static char*prefix(const char*tag,const char*pre,const char*s){append("%s:%s;",tag,s?s:"(null)");char*b=names[ni++%64];snprintf(b,BUFSZ,"%s%s",pre,s?s:"(null)");return b;}
char*an(const char*s){return prefix("an","a ",s);}
char*the(const char*s){return prefix("the","the ",s);}
char*The(const char*s){return prefix("The","The ",s);}
char*Tobjnam(struct obj*o,const char*v){append("Tobj:%d:%s;",oid(o),v?v:"(null)");char*b=names[ni++%64];snprintf(b,BUFSZ,"Projectile %s",v?v:"");return b;}
char*mon_nam(struct monst*m){append("mon_nam:%d;",mid(m));return namebuf("creature");}
char*Monnam(struct monst*m){append("Monnam:%d;",mid(m));return namebuf("Creature");}
char*some_mon_nam(struct monst*m){append("some:%d;",mid(m));return namebuf("creature");}
char*makeplural(const char*s){append("plural:%s;",s);char*b=names[ni++%64];snprintf(b,BUFSZ,"%ss",s);return b;}
char*otense(struct obj*o,const char*v){append("otense:%d:%s;",oid(o),v);return namebuf(v);}
char*vtense(const char*s,const char*v){append("vtense:%s:%s;",s,v);return namebuf(v);}
const char*body_part(int p){append("body:%d;",p);return "hand";}
const char*mbodypart(struct monst*m,int p){append("mbody:%d:%d;",mid(m),p);return "hand";}
const char*singular(struct obj*o,char*(*fn)(struct obj*)){append("singular:%d:%d;",oid(o),fn==xname?0:1);return fn(o);}
char*distant_name(struct obj*o,char*(*fn)(struct obj*)){append("distant:%d:%d;",oid(o),fn==xname?0:1);return fn(o);}
int isok(coordxy x,coordxy y){return x>0&&x<COLNO&&y>=0&&y<ROWNO;}
int get_atkdam_type(int n){append("atkdam:%d;",n);return configured[DEP_get_atkdam_type]?opts[DEP_get_atkdam_type]:n;}
int canseemon(struct monst*m){append("canseemon:%d;",mid(m));return configured[DEP_canseemon]?opts[DEP_canseemon]:1;}
int sensemon(struct monst*m){append("sensemon:%d;",mid(m));return configured[DEP_sensemon]?opts[DEP_sensemon]:0;}
boolean clear_path(int ax,int ay,int bx,int by){append("path:%d,%d:%d,%d;",ax,ay,bx,by);return configured[DEP_clear_path]?opts[DEP_clear_path]:1;}
boolean is_art(struct obj*o,int id){append("art:%d:%d;",oid(o),id);return o&&o->oartifact==id;}
int pronoun_gender(struct monst*m,unsigned flagsarg){append("pronoun:%d:%u;",mid(m),flagsarg);return configured[DEP_pronoun_gender]?opts[DEP_pronoun_gender]:0;}
void clear_dknown(struct obj*o){append("clear_dknown:%d;",oid(o));o->dknown=0;}
void discover_object(int t,boolean a,boolean b,boolean c){append("discover:%d:%d:%d:%d;",t,a,b,c);objects[t].oc_name_known=1;}
void obj_extract_self(struct obj*o){append("extract:%d;",oid(o));unlink_obj(&gi.invent,o);unlink_obj(&fobj,o);for(int i=0;i<8;i++)unlink_obj(&monsters[i].minvent,o);for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++){struct obj**p=&svl.level.objects[x][y];while(*p&&*p!=o)p=&(*p)->nexthere;if(*p)*p=o->nexthere;}o->nobj=o->nexthere=0;o->where=OBJ_FREE;callback(DEP_obj_extract_self);}
void place_object(struct obj*o,coordxy x,coordxy y){append("place:%d:%d,%d;",oid(o),x,y);o->where=OBJ_FLOOR;o->ox=x;o->oy=y;o->nobj=fobj;fobj=o;o->nexthere=svl.level.objects[x][y];svl.level.objects[x][y]=o;callback(DEP_place_object);}
void obfree(struct obj*o,struct obj*other){append("obfree:%d:%d;",oid(o),oid(other));kill_object(o);}
void delobj(struct obj*o){append("delobj:%d;",oid(o));kill_object(o);}
struct obj*splitobj(struct obj*o,long n){int at=32;while(at<64&&pool[at])at++;if(at==64||n<=0||n>=o->quan)abort();struct obj*c=pool[at]=malloc(sizeof*c);memcpy(c,o,sizeof*c);c->o_id=100+at;c->quan=n;o->quan-=n;c->nobj=o->nobj;o->nobj=c;append("split:%d:%ld:%d;",oid(o),n,at);callback(DEP_splitobj);return c;}
int add_to_minv(struct monst*m,struct obj*o){append("add_minv:%d:%d;",mid(m),oid(o));o->nobj=m->minvent;m->minvent=o;o->where=OBJ_MINVENT;o->ocarry=m;callback(DEP_add_to_minv);return 0;}
void extract_from_minvent(struct monst*m,struct obj*o,boolean a,boolean b){append("extract_minv:%d:%d:%d:%d;",mid(m),oid(o),a,b);obj_extract_self(o);}
void setmnotwielded(struct monst*m,struct obj*o){append("unwield:%d:%d;",mid(m),oid(o));if(m->mw==o)m->mw=0;}
int weight(struct obj*o){append("weight:%d;",oid(o));return configured[DEP_weight]?opts[DEP_weight]:10;}
int find_mac(struct monst*m){append("mac:%d;",mid(m));return configured[DEP_find_mac]?opts[DEP_find_mac]:0;}
int dmgval(struct obj*o,struct monst*m){append("dmg:%d:%d;",oid(o),mid(m));callback(DEP_dmgval);return configured[DEP_dmgval]?opts[DEP_dmgval]:7;}
struct obj*select_rwep(struct monst*m){append("select:%d;",mid(m));callback(DEP_select_rwep);return configured[DEP_select_rwep]?(opts[DEP_select_rwep]<0?0:pool[opts[DEP_select_rwep]]):m->minvent;}
struct obj*mksobj(int type,boolean init,boolean art){int at=32;while(at<64&&pool[at])at++;if(at==64)abort();struct obj*o=pool[at]=calloc(1,sizeof*o);o->otyp=type;o->oclass=objects[type].oc_class;o->quan=1;o->o_id=100+at;o->dknown=1;o->where=OBJ_FREE;append("mksobj:%d:%d:%d:%d;",type,init,art,at);callback(DEP_mksobj);return o;}
const struct throw_and_return_weapon*autoreturn_weapon(struct obj*o){append("autoreturn:%d;",oid(o));return configured[DEP_autoreturn_weapon]&&opts[DEP_autoreturn_weapon]?&returning:0;}
void potionhit(struct monst*m,struct obj*o,int flagsarg){append("potion:%d:%d:%d;",mid(m),oid(o),flagsarg);kill_object(o);}
void losehp(int n,const char*s,schar k){append("losehp:%d:%s:%d;",n,s,k);u.uhp-=n;if(configured[DEP_losehp]&&opts[DEP_losehp]){u.umortality++;u.uhp=20;}callback(DEP_losehp);}
void make_blinded(long n,boolean b){append("blind:%ld:%d;",n,b);u.uprops[BLINDED].intrinsic=n;}
void make_stoned(long n,const char*s,int k,const char*death){append("stoned:%ld:%s:%d:%s;",n,s?s:"(null)",k,death);u.uprops[STONED].intrinsic=n;}
void nomul(int n){append("nomul:%d;",n);gm.multi=n;}
void setmangry(struct monst*m,boolean b){append("angry:%d:%d;",mid(m),b);m->mpeaceful=0;}
void mondied(struct monst*m){append("mondied:%d;",mid(m));if(configured[DEP_mondied]&&opts[DEP_mondied])m->mhp=1;}
void monkilled(struct monst*m,const char*s,int type){append("monkilled:%d:%s:%d;",mid(m),s?s:"(null)",type);if(configured[DEP_monkilled]&&opts[DEP_monkilled])m->mhp=1;}
void xkilled(struct monst*m,int k){append("xkilled:%d:%d;",mid(m),k);if(configured[DEP_xkilled]&&opts[DEP_xkilled])m->mhp=1;}
void minstapetrify(struct monst*m,boolean b){append("petrify:%d:%d;",mid(m),b);m->mhp=0;}
struct obj*hold_another_object(struct obj*o,const char*f,const char*name,const char*drop){append("hold:%d:%s:%s:%s;",oid(o),f,name,drop);o->nobj=gi.invent;gi.invent=o;o->where=OBJ_INVENT;return o;}
void dropy(struct obj*o){append("dropy:%d;",oid(o));place_object(o,u.ux,u.uy);}
static void delay(void){append("delay;");}
void probe_reset(void){for(int i=0;i<64;i++){if(pool[i])free(pool[i]);pool[i]=0;}if(grown){free(grown);grown=0;}memset(&u,0,sizeof u);memset(&gy,0,sizeof gy);memset(&gm,0,sizeof gm);memset(&gt,0,sizeof gt);memset(&gb,0,sizeof gb);memset(&gn,0,sizeof gn);memset(&gv,0,sizeof gv);memset(&gi,0,sizeof gi);memset(&gu,0,sizeof gu);memset(&svc,0,sizeof svc);memset(&svl,0,sizeof svl);memset(&go,0,sizeof go);memset(&iflags,0,sizeof iflags);memset(&flags,0,sizeof flags);memset(opts,0,sizeof opts);memset(configured,0,sizeof configured);memset(monsters,0,sizeof monsters);memset(extras,0,sizeof extras);memset(dogs,0,sizeof dogs);memset(pointers,0,sizeof pointers);memset(attk_pool,0,sizeof attk_pool);memset(&returning,0,sizeof returning);monst_globals_init();objects_globals_init();for(int i=0;i<32;i++){struct obj*o=pool[i]=calloc(1,sizeof*o);o->otyp=DAGGER;o->oclass=objects[DAGGER].oc_class;o->quan=1;o->owt=10;o->o_id=100+i;o->where=OBJ_FREE;o->dknown=1;}u.ux=u.ux0=10;u.uy=u.uy0=10;u.uhp=u.uhpmax=100;u.umonnum=u.umonster=PM_HUMAN;u.ulycn=NON_PM;gy.youmonst.data=&mons[PM_HUMAN];gy.youmonst.mhp=100;gy.youmonst.mx=u.ux;gy.youmonst.my=u.uy;gu.urole.mnum=PM_ARCHEOLOGIST;flags.verbose=1;for(int i=0;i<8;i++){struct monst*m=&monsters[i];m->m_id=i+1;m->cham=NON_PM;m->data=&mons[PM_HUMAN];m->mx=15+i;m->my=10;m->mux=u.ux;m->muy=u.uy;m->mhp=m->mhpmax=100;m->m_lev=10;m->mcansee=m->mcanmove=1;m->mextra=&extras[i];extras[i].edog=&dogs[i];dogs[i].hungrytime=1000;svl.level.monsters[m->mx][m->my]=m;m->nmon=i<7?&monsters[i+1]:0;}fmon=monsters;for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++)svl.level.locations[x][y].typ=ROOM;static uchar rows[ROWNO][COLNO];static uchar*rowptrs[ROWNO];for(int y=0;y<ROWNO;y++){memset(rows[y],IN_SIGHT|COULD_SEE,COLNO);rowptrs[y]=rows[y];}gv.viz_array=rowptrs;windowprocs.win_delay_output=delay;svm.moves=1000;growth_stage=reenter_stage=-1;seed=1;nr=ri=ni=0;ti=tracebuf[0]=0;frees=0;returning.range=8;}
int probe_dep_count(void){return (int)(sizeof dep_names/sizeof dep_names[0]);}
const char*probe_dep_name(int i){return dep_names[i];}
void probe_option(int i,long v){configured[i]=1;opts[i]=v;}
void probe_roll(int n){rolls[nr++]=n;}
void probe_seed(unsigned n){seed=n;}
void probe_callback(int grow,int reenter){growth_stage=grow;reenter_stage=reenter;}
void *probe_pointer(int kind,int n){switch(kind){case 0:return pool[n];case 1:return &monsters[n];case 2:return &pointers[n];case 3:return &attk_pool[n];case 4:return &u;case 5:return &gy.youmonst;case 6:return &dogs[n];}return 0;}
void probe_object(int i,int field,long v){struct obj*o=pool[i];switch(field){case 0:o->otyp=v;o->oclass=objects[v].oc_class;break;case 1:o->quan=v;break;case 2:o->spe=v;break;case 3:o->cursed=v;break;case 4:o->greased=v;break;case 5:o->known=v;break;case 6:o->opoisoned=v;break;case 7:o->otrapped=v;break;case 8:o->dknown=v;break;case 9:o->corpsenm=v;break;case 10:o->oartifact=v;break;case 11:o->owornmask=v;break;case 12:o->owt=v;break;case 13:o->oclass=v;break;case 14:o->ox=v;break;case 15:o->oy=v;break;}}
void probe_set_monster(int i,int field,long v){struct monst*m=i<0?&gy.youmonst:&monsters[i];switch(field){case 0:m->data=&mons[v];break;case 1:m->mhp=v;break;case 2:m->m_lev=v;break;case 3:m->mconf=v;break;case 4:m->mstun=v;break;case 5:m->mblinded=v;break;case 6:m->mcansee=v;break;case 7:m->mcan=v;break;case 8:m->mflee=v;break;case 9:m->mspec_used=v;break;case 10:m->mtame=v;break;case 11:m->isminion=v;break;case 12:m->mux=v;break;case 13:m->muy=v;break;case 14:m->weapon_check=v;break;case 15:m->m_ap_type=v;break;case 16:m->mappearance=v;break;case 17:m->seen_resistance=v;break;case 18:EDOG(m)->hungrytime=v;break;}}
void probe_position(int i,int x,int y){struct monst*m=&monsters[i];if(isok(m->mx,m->my)&&svl.level.monsters[m->mx][m->my]==m)svl.level.monsters[m->mx][m->my]=0;m->mx=x;m->my=y;if(isok(x,y))svl.level.monsters[x][y]=m;}
void probe_hero(int field,long v){switch(field){case 0:u.uac=v;break;case 1:u.ux=v;break;case 2:u.uy=v;break;case 3:u.ux0=v;break;case 4:u.uy0=v;break;case 5:svm.moves=v;break;case 6:u.uroleplay.deaf=v;break;case 7:u.uinwater=v;break;case 8:svc.context.mon_moving=v;break;case 9:gu.urole.mnum=v;break;case 10:u.uundetected=v;break;case 11:u.umonnum=v;break;case 12:gm.multi=v;break;case 13:flags.verbose=v;break;case 14:gm.marcher=v<0?0:&monsters[v];break;case 15:gm.mtarget=v<0?0:&monsters[v];break;case 16:returning.tethered=v;break;case 17:returning.range=v;break;}}
void probe_property(int n,int field,long v){if(field==0)u.uprops[n].intrinsic=v;else if(field==1)u.uprops[n].extrinsic=v;else u.uprops[n].blocked=v;}
void probe_terrain(int x,int y,int typ,int flagsarg){svl.level.locations[x][y].typ=typ;svl.level.locations[x][y].flags=flagsarg;}
void probe_vision(int x,int y,int bits){gv.viz_array[y][x]=bits;}
void probe_attach(int i,int mon,int weapon){struct obj*o=pool[i];if(mon<0){o->nobj=gi.invent;gi.invent=o;o->where=OBJ_INVENT;}else{o->nobj=monsters[mon].minvent;monsters[mon].minvent=o;o->ocarry=&monsters[mon];o->where=OBJ_MINVENT;if(weapon)monsters[mon].mw=o;}}
void probe_output(int slot,int object){pointers[slot]=object<0?0:pool[object];}
void probe_attack(int n,int ad,int dice){attk_pool[n].adtyp=ad;attk_pool[n].damn=dice;}
void probe_bhit(int x,int y){gb.bhitpos.x=x;gb.bhitpos.y=y;}
static boolean line_callback(coordxy x,coordxy y){append("line_callback:%d,%d;",x,y);callback(499);return x==opts[498]&&y==opts[497];}
const char*probe_table(int table,int i){
#ifdef TELEPORT_REFERENCE_TU
return table?hallublasts[i]:breathwep[i];
#else
return 0;
#endif
}
long probe_action(int op,int a,int b,int c,int d,int e,int f,int g){switch(op){case 0:{const char*s=rnd_hallublast();append("hallu:%s;",s);break;}case 1:return m_has_launcher_and_ammo(&monsters[a]);case 2:return thitu(a,b,c<0?0:&pointers[c],d?"the named object":0);case 3:return drop_throw(pool[a],b,c,d);case 4:return monmulti(&monsters[a],pool[b],c<0?0:pool[c]);case 5:monshoot(&monsters[a],pool[b],c<0?0:pool[c]);break;case 6:return ohitmon(&monsters[a],pool[b],c,d);case 7:return ucatchgem(pool[a],&monsters[b]);case 8:return u_catch_thrown_obj(pool[a]);case 9:m_throw(&monsters[a],b,c,d,e,f,pool[g]);break;case 10:return_from_mtoss(&monsters[a],b<0?0:pool[b],c);break;case 11:return thrwmm(&monsters[a],&monsters[b]);case 12:return spitmm(&monsters[a],&attk_pool[b],c<0?&gy.youmonst:&monsters[c]);case 13:{const char*s=breathwep_name(a);append("breath:%s;",s);break;}case 14:return breamm(&monsters[a],&attk_pool[b],c<0?&gy.youmonst:&monsters[c]);case 15:m_useupall(&monsters[a],pool[b]);break;case 16:m_useup(&monsters[a],pool[b]);break;case 17:thrwmu(&monsters[a]);break;case 18:return spitmu(&monsters[a],&attk_pool[b]);case 19:return breamu(&monsters[a],&attk_pool[b]);case 20:return blocking_terrain(a,b);case 21:return linedup_callback(a,b,c,d,line_callback);case 22:return linedup(a,b,c,d,e);case 23:return m_lined_up(a<0?&gy.youmonst:&monsters[a],&monsters[b]);case 24:return lined_up(&monsters[a]);case 25:return oid(m_carrying(a<0?&gy.youmonst:&monsters[a],b));case 26:hit_bars(&pointers[a],b,c,d,e,f);break;case 27:return hits_bars(&pointers[a],b,c,d,e,f,g);}return 0;}
const char*probe_trace(void){return tracebuf;}
int probe_frees(void){return frees;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
const char*probe_snapshot(void){char*p=snapbuf;p+=sprintf(p,"global:%d,%d:%d,%d:%d:%d:%d:%ld:%d:%d:%d:%u:%d:%ld:%ld:%ld:%d:%d:%d,%d,%d,%d:%d:%d;",u.ux,u.uy,gt.tbx,gt.tby,oid(gt.thrownobj),mid(gm.marcher),mid(gm.mtarget),gm.multi,gm.mesg_given,u.uhp,u.umortality,u.ucreamed,u.uundetected,u.uprops[BLINDED].intrinsic,u.uprops[STONED].intrinsic,svm.moves,gn.notonhead,gv.vision_full_recalc,gm.m_shot.n,gm.m_shot.i,gm.m_shot.o,gm.m_shot.s,go.otg_temp,oid(go.otg_otmp));for(int i=0;i<64;i++){struct obj*o=pool[i];if(o)p+=sprintf(p,"o%d:%u:%d:%d:%ld:%u:%d:%d:%d,%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%lx;",i,o->o_id,o->otyp,o->oclass,o->quan,o->owt,o->spe,o->where,o->ox,o->oy,oid(o->nobj),oid(o->nexthere),o->corpsenm,o->oartifact,o->cursed,o->greased,o->known,o->opoisoned,o->otrapped,(unsigned long)o->owornmask);}for(int i=0;i<8;i++)p+=sprintf(p,"m%d:%d:%d,%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%lu:%ld:%d:%d;",i,monsndx(monsters[i].data),monsters[i].mx,monsters[i].my,monsters[i].mhp,monsters[i].m_lev,monsters[i].mtame,monsters[i].mconf,monsters[i].mstun,monsters[i].mblinded,monsters[i].mcansee,monsters[i].mcan,monsters[i].mspec_used,monsters[i].weapon_check,monsters[i].seen_resistance,dogs[i].hungrytime,oid(monsters[i].mw),oid(monsters[i].minvent));for(int i=0;i<8;i++)p+=sprintf(p,"ptr%d:%d;",i,oid(pointers[i]));for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++){if(svl.level.objects[x][y])p+=sprintf(p,"floor:%d,%d:%d;",x,y,oid(svl.level.objects[x][y]));if(svl.level.locations[x][y].typ!=ROOM||svl.level.locations[x][y].flags)p+=sprintf(p,"terrain:%d,%d:%d:%u;",x,y,svl.level.locations[x][y].typ,svl.level.locations[x][y].flags);}return snapbuf;}

int breaks(struct obj*o,coordxy x,coordxy y){append("breaks:%d:%d:%d;",oid(o),x,y);callback(DEP_breaks);int r=configured[DEP_breaks]?opts[DEP_breaks]:0;if(r)kill_object(o);return r;}
int hero_breaks(struct obj*o,coordxy x,coordxy y,unsigned flagsarg){append("hero_breaks:%d:%d:%d:%u;",oid(o),x,y,flagsarg);callback(DEP_hero_breaks);int r=configured[DEP_hero_breaks]?opts[DEP_hero_breaks]:0;if(r)kill_object(o);return r;}
boolean flooreffects(struct obj*o,coordxy x,coordxy y,const char*s){append("flooreffects:%d:%d:%d:%s;",oid(o),x,y,s);callback(DEP_flooreffects);int r=configured[DEP_flooreffects]?opts[DEP_flooreffects]:0;if(r)kill_object(o);return r;}
boolean ship_object(struct obj*o,coordxy x,coordxy y,boolean shop){append("ship_object:%d:%d:%d:%d;",oid(o),x,y,shop);callback(DEP_ship_object);int r=configured[DEP_ship_object]?opts[DEP_ship_object]:0;if(r){obj_extract_self(o);o->where=OBJ_MIGRATING;}return r;}
