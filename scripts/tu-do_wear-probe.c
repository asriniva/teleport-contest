/* Controlled native dependency fixture; every do_wear function body remains
 * original prepared C or its original-boundary JS translation. */
#include "hack.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <setjmp.h>
#include <emscripten/stack.h>
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/do_wear.c"
#else
extern void teleport_do_wear_test_on_msg(struct obj *);
#define on_msg teleport_do_wear_test_on_msg
extern void teleport_do_wear_test_toggle_stealth(struct obj *,long,boolean);
#define toggle_stealth teleport_do_wear_test_toggle_stealth
extern int teleport_do_wear_test_Cloak_on(void);
#define Cloak_on teleport_do_wear_test_Cloak_on
extern int teleport_do_wear_test_Helmet_on(void);
#define Helmet_on teleport_do_wear_test_Helmet_on
extern int teleport_do_wear_test_Gloves_on(void);
#define Gloves_on teleport_do_wear_test_Gloves_on
extern int teleport_do_wear_test_Shield_on(void);
#define Shield_on teleport_do_wear_test_Shield_on
extern int teleport_do_wear_test_Shirt_on(void);
#define Shirt_on teleport_do_wear_test_Shirt_on
extern void teleport_do_wear_test_dragon_armor_handling(struct obj *,boolean,boolean);
#define dragon_armor_handling teleport_do_wear_test_dragon_armor_handling
extern int teleport_do_wear_test_Armor_on(void);
#define Armor_on teleport_do_wear_test_Armor_on
extern void teleport_do_wear_test_Amulet_on(struct obj *);
#define Amulet_on teleport_do_wear_test_Amulet_on
extern void teleport_do_wear_test_learnring(struct obj *,boolean);
#define learnring teleport_do_wear_test_learnring
extern void teleport_do_wear_test_adjust_attrib(struct obj *,int,int);
#define adjust_attrib teleport_do_wear_test_adjust_attrib
extern void teleport_do_wear_test_Ring_off_or_gone(struct obj *,boolean);
#define Ring_off_or_gone teleport_do_wear_test_Ring_off_or_gone
extern void teleport_do_wear_test_count_worn_stuff(struct obj **,boolean);
#define count_worn_stuff teleport_do_wear_test_count_worn_stuff
extern int teleport_do_wear_test_armor_or_accessory_off(struct obj *);
#define armor_or_accessory_off teleport_do_wear_test_armor_or_accessory_off
extern void teleport_do_wear_test_already_wearing(const char *);
#define already_wearing teleport_do_wear_test_already_wearing
extern void teleport_do_wear_test_already_wearing2(const char *,const char *);
#define already_wearing2 teleport_do_wear_test_already_wearing2
extern int teleport_do_wear_test_accessory_or_armor_on(struct obj *);
#define accessory_or_armor_on teleport_do_wear_test_accessory_or_armor_on
extern int teleport_do_wear_test_select_off(struct obj *);
#define select_off teleport_do_wear_test_select_off
extern struct obj * teleport_do_wear_test_do_takeoff(void);
#define do_takeoff teleport_do_wear_test_do_takeoff
extern int teleport_do_wear_test_take_off(void);
#define take_off teleport_do_wear_test_take_off
extern boolean teleport_do_wear_test_better_not_take_that_off(struct obj *);
#define better_not_take_that_off teleport_do_wear_test_better_not_take_that_off
extern int teleport_do_wear_test_menu_remarm(int);
#define menu_remarm teleport_do_wear_test_menu_remarm
extern void teleport_do_wear_test_wornarm_destroyed(struct obj *);
#define wornarm_destroyed teleport_do_wear_test_wornarm_destroyed
extern struct obj * teleport_do_wear_test_maybe_destroy_armor(struct obj *,struct obj *,boolean *);
#define maybe_destroy_armor teleport_do_wear_test_maybe_destroy_armor
extern int teleport_do_wear_test_obj_erode_type(struct obj *);
#define obj_erode_type teleport_do_wear_test_obj_erode_type
extern int teleport_do_wear_test_equip_ok(struct obj *,boolean,boolean);
#define equip_ok teleport_do_wear_test_equip_ok
extern int teleport_do_wear_test_puton_ok(struct obj *);
#define puton_ok teleport_do_wear_test_puton_ok
extern int teleport_do_wear_test_remove_ok(struct obj *);
#define remove_ok teleport_do_wear_test_remove_ok
extern int teleport_do_wear_test_wear_ok(struct obj *);
#define wear_ok teleport_do_wear_test_wear_ok
extern int teleport_do_wear_test_takeoff_ok(struct obj *);
#define takeoff_ok teleport_do_wear_test_takeoff_ok
#endif
#include "tu-do_wear-layout.h"
#undef free
extern void free(void*);
__typeof__(flags) flags;
__typeof__(iflags) iflags;
__typeof__(condtests) condtests;
const char rightleftchars[]="rl";
__typeof__(uarm) uarm;
__typeof__(uarmc) uarmc;
__typeof__(uarmh) uarmh;
__typeof__(uarms) uarms;
__typeof__(uarmg) uarmg;
__typeof__(uarmf) uarmf;
__typeof__(uarmu) uarmu;
__typeof__(uskin) uskin;
__typeof__(uamul) uamul;
__typeof__(uleft) uleft;
__typeof__(uright) uright;
__typeof__(ublindf) ublindf;
__typeof__(uwep) uwep;
__typeof__(uswapwep) uswapwep;
__typeof__(uquiver) uquiver;
__typeof__(uball) uball;
__typeof__(u) u;
__typeof__(disp) disp;
__typeof__(ga) ga;
__typeof__(gi) gi;
__typeof__(gm) gm;
__typeof__(gn) gn;
__typeof__(gu) gu;
__typeof__(gw) gw;
__typeof__(gy) gy;
__typeof__(svc) svc;
__typeof__(svd) svd;
__typeof__(program_state) program_state;
__typeof__(cg) cg;
const struct c_color_names c_color_names={.c_black="black",.c_amber="amber",.c_silver="silver",.c_white="white"};
const struct c_common_strings c_common_strings={.c_something="something",.c_Something="Something",.c_the_your={"the","your"}};
const char ynchars[]="yn";
static struct obj*pool[32];static struct monst monsters[4];static seenV vision[ROWNO][COLNO];static seenV*visionrows[ROWNO];
static char traces[4194304],snapshot[262144],names[128][BUFSZ];static int policy_frees,menu_frees,command_frees;static void*last_menu,*last_command;
static int ti,ni,rolls[8192],nr,ri,frees;static unsigned seed;static int opts[1024],configured[1024],growth_stage,reenter_stage;static void*grown;static const char*callerfile,*callerfn;static int callerline;
static int(*occupation)(void);static jmp_buf bail;static int guarding,panic_code;
static void append(const char*f,...){va_list ap;va_start(ap,f);int n=vsnprintf(traces+ti,sizeof traces-ti,f,ap);va_end(ap);if(n<0||ti+n>=sizeof traces)abort();ti+=n;}
static int oid(struct obj*o){if(!o)return-1;for(int i=0;i<32;i++)if(pool[i]==o)return i;return-99;}
static int mid(struct monst*m){if(!m)return-1;if(m==&gy.youmonst)return-2;for(int i=0;i<4;i++)if(m==monsters+i)return i;return-99;}
static void mutate_equipment(int);
static uintptr_t stack_min,stack_max;
static void callback(int stage){volatile char marker;uintptr_t sp=(uintptr_t)&marker;if(!stack_min||sp<stack_min)stack_min=sp;if(sp>stack_max)stack_max=sp;mutate_equipment(stage);if(stage==growth_stage){growth_stage=-1;grown=malloc(48*1024*1024);if(!grown)abort();append("growth:%d;",stage);}if(stage==reenter_stage){reenter_stage=-1;append("reentry:%d;",count_worn_armor());}}
static void dispose(struct obj*);
static char*namebuf(const char*s){char*b=names[ni++%128];snprintf(b,BUFSZ,"%s",s?s:"(null)");return b;}
static void message(const char*tag,const char*f,va_list ap){char b[4096];vsnprintf(b,sizeof b,f,ap);append("%s:%s;",tag,b);}
static const char*dep_names[]={"Norep","There","Tobjnam","Yname2","You","You_cant","You_feel","You_hear","You_see","Your","acurr","add_valid_menu_class","allow_all","allow_category","an","ansimpleoname","any_obj_ok","arti_light_description","artifact_light","begin_burn","body_part","boots_simple_name","breakarm","can_be_strangled","canletgo","carrying_stoning_corpse","change_luck","change_sex","cloak_simple_name","cmdq_clear","cmdq_peek","cmdq_pop","corpse_xname","curse","debugcore","discover_object","doname","dropx","drown","empty_handed","encumber_msg","end_burn","erode_obj","erosion_matters","extremeattr","float_down","float_up","float_vs_flight","getobj","ggetobj","gloves_simple_name","gulp_blnd_check","has_ceiling","hcolor","helm_simple_name","hliquid","impossible","incr_itimeout","instapetrify","is_flammable","is_lava","is_pool","is_pool_or_lava","is_rottable","is_worn","is_worn_by_type","killer_xname","livelog_newform","make_blinded","make_glib","make_hallucinated","make_slimed","makeplural","makesingular","menu_class_present","newsym","nomul","num_horns","obj_is_pname","obj_pmname","obj_resists","observe_object","on_level","otense","panic","paranoid_ynq","pline","pline_The","poly_gender","prinv","query_category","query_objlist","racial_exception","region_danger","remove_worn_item","rescham","restartcham","retouch_object","rn2","rn2_on_display_rng","rnd","rng_log_enabled","rng_log_set_caller","safe_typename","see_monsters","self_invis_message","selftouch","set_bc","set_bknown","set_itimeout","set_mimic_blocking","set_occupation","setnotworn","setuqwep","setuswapwep","setuwep","setworn","shield_simple_name","shirt_simple_name","shk_your","silly_thing","simpleonames","sliparm","spoteffects","stop_occupation","strncpy","suit_simple_name","surface","the","thesimpleoname","toggle_blindness","trycall","u_safe_from_fatal_corpse","uchangealign","unmul","update_inventory","urgent_pline","useup","vtense","weapon_descr","wearing_armor","welded","which_armor","x_monnam","xname","yn_function","yname"};
enum{DEP_Norep=0,DEP_There=1,DEP_Tobjnam=2,DEP_Yname2=3,DEP_You=4,DEP_You_cant=5,DEP_You_feel=6,DEP_You_hear=7,DEP_You_see=8,DEP_Your=9,DEP_acurr=10,DEP_add_valid_menu_class=11,DEP_allow_all=12,DEP_allow_category=13,DEP_an=14,DEP_ansimpleoname=15,DEP_any_obj_ok=16,DEP_arti_light_description=17,DEP_artifact_light=18,DEP_begin_burn=19,DEP_body_part=20,DEP_boots_simple_name=21,DEP_breakarm=22,DEP_can_be_strangled=23,DEP_canletgo=24,DEP_carrying_stoning_corpse=25,DEP_change_luck=26,DEP_change_sex=27,DEP_cloak_simple_name=28,DEP_cmdq_clear=29,DEP_cmdq_peek=30,DEP_cmdq_pop=31,DEP_corpse_xname=32,DEP_curse=33,DEP_debugcore=34,DEP_discover_object=35,DEP_doname=36,DEP_dropx=37,DEP_drown=38,DEP_empty_handed=39,DEP_encumber_msg=40,DEP_end_burn=41,DEP_erode_obj=42,DEP_erosion_matters=43,DEP_extremeattr=44,DEP_float_down=45,DEP_float_up=46,DEP_float_vs_flight=47,DEP_getobj=48,DEP_ggetobj=49,DEP_gloves_simple_name=50,DEP_gulp_blnd_check=51,DEP_has_ceiling=52,DEP_hcolor=53,DEP_helm_simple_name=54,DEP_hliquid=55,DEP_impossible=56,DEP_incr_itimeout=57,DEP_instapetrify=58,DEP_is_flammable=59,DEP_is_lava=60,DEP_is_pool=61,DEP_is_pool_or_lava=62,DEP_is_rottable=63,DEP_is_worn=64,DEP_is_worn_by_type=65,DEP_killer_xname=66,DEP_livelog_newform=67,DEP_make_blinded=68,DEP_make_glib=69,DEP_make_hallucinated=70,DEP_make_slimed=71,DEP_makeplural=72,DEP_makesingular=73,DEP_menu_class_present=74,DEP_newsym=75,DEP_nomul=76,DEP_num_horns=77,DEP_obj_is_pname=78,DEP_obj_pmname=79,DEP_obj_resists=80,DEP_observe_object=81,DEP_on_level=82,DEP_otense=83,DEP_panic=84,DEP_paranoid_ynq=85,DEP_pline=86,DEP_pline_The=87,DEP_poly_gender=88,DEP_prinv=89,DEP_query_category=90,DEP_query_objlist=91,DEP_racial_exception=92,DEP_region_danger=93,DEP_remove_worn_item=94,DEP_rescham=95,DEP_restartcham=96,DEP_retouch_object=97,DEP_rn2=98,DEP_rn2_on_display_rng=99,DEP_rnd=100,DEP_rng_log_enabled=101,DEP_rng_log_set_caller=102,DEP_safe_typename=103,DEP_see_monsters=104,DEP_self_invis_message=105,DEP_selftouch=106,DEP_set_bc=107,DEP_set_bknown=108,DEP_set_itimeout=109,DEP_set_mimic_blocking=110,DEP_set_occupation=111,DEP_setnotworn=112,DEP_setuqwep=113,DEP_setuswapwep=114,DEP_setuwep=115,DEP_setworn=116,DEP_shield_simple_name=117,DEP_shirt_simple_name=118,DEP_shk_your=119,DEP_silly_thing=120,DEP_simpleonames=121,DEP_sliparm=122,DEP_spoteffects=123,DEP_stop_occupation=124,DEP_strncpy=125,DEP_suit_simple_name=126,DEP_surface=127,DEP_the=128,DEP_thesimpleoname=129,DEP_toggle_blindness=130,DEP_trycall=131,DEP_u_safe_from_fatal_corpse=132,DEP_uchangealign=133,DEP_unmul=134,DEP_update_inventory=135,DEP_urgent_pline=136,DEP_useup=137,DEP_vtense=138,DEP_weapon_descr=139,DEP_wearing_armor=140,DEP_welded=141,DEP_which_armor=142,DEP_x_monnam=143,DEP_xname=144,DEP_yn_function=145,DEP_yname=146};
char * Tobjnam(struct obj * a0,const char * a1){append("Tobjnam:%d:%s;",oid(a0),a1?a1:"(null)");callback(DEP_Tobjnam);return namebuf("value");}
char * Yname2(struct obj * a0){append("Yname2:%d;",oid(a0));callback(DEP_Yname2);return namebuf("value");}
schar acurr(int a0){append("acurr:%d;",a0);callback(DEP_acurr);return configured[DEP_acurr]?opts[DEP_acurr]:u.acurr.a[a0]+u.abon.a[a0];}
void add_valid_menu_class(int a0){append("add_valid_menu_class:%ld;",(long)a0);callback(DEP_add_valid_menu_class);}
char * an(const char * a0){append("an:%s;",a0?a0:"(null)");callback(DEP_an);return namebuf("value");}
char * ansimpleoname(struct obj * a0){append("ansimpleoname:%d;",oid(a0));callback(DEP_ansimpleoname);return namebuf("value");}
const char * arti_light_description(struct obj * a0){append("arti_light_description:%d;",oid(a0));callback(DEP_arti_light_description);return namebuf("value");}
boolean artifact_light(struct obj * a0){append("artifact_light:%d;",oid(a0));callback(DEP_artifact_light);return configured[DEP_artifact_light]?opts[DEP_artifact_light]:0;}
void begin_burn(struct obj * a0,boolean a1){append("begin_burn:%d:%ld;",oid(a0),(long)a1);callback(DEP_begin_burn);}
const char * body_part(int a0){append("body_part:%ld;",(long)a0);callback(DEP_body_part);return namebuf("value");}
const char * boots_simple_name(struct obj * a0){append("boots_simple_name:%d;",oid(a0));callback(DEP_boots_simple_name);return namebuf("value");}
boolean breakarm(struct permonst * a0){append("breakarm:ptr;");callback(DEP_breakarm);return configured[DEP_breakarm]?opts[DEP_breakarm]:0;}
boolean can_be_strangled(struct monst * a0){append("can_be_strangled:%d;",mid(a0));callback(DEP_can_be_strangled);return configured[DEP_can_be_strangled]?opts[DEP_can_be_strangled]:0;}
boolean canletgo(struct obj * a0,const char * a1){append("canletgo:%d:%s;",oid(a0),a1);callback(DEP_canletgo);return configured[DEP_canletgo]?opts[DEP_canletgo]:0;}
struct obj * carrying_stoning_corpse(void){append("carrying_stoning_corpse;");callback(DEP_carrying_stoning_corpse);return 0;}
void change_luck(schar a0){append("change_luck:%ld;",(long)a0);callback(DEP_change_luck);}
void change_sex(void){append("change_sex;");callback(DEP_change_sex);}
const char * cloak_simple_name(struct obj * a0){append("cloak_simple_name:%d;",oid(a0));callback(DEP_cloak_simple_name);return namebuf("value");}
void cmdq_clear(int a0){append("cmdq_clear:%ld;",(long)a0);callback(DEP_cmdq_clear);}
struct _cmd_queue * cmdq_peek(int a0){append("cmdq_peek:%ld;",(long)a0);callback(DEP_cmdq_peek);return 0;}
struct _cmd_queue * cmdq_pop(void){append("cmdq_pop;");if(!opts[DEP_cmdq_pop])return 0;struct _cmd_queue*q=malloc(sizeof*q);memset(q,0xa5,sizeof*q);q->typ=opts[513]?opts[513]:CMDQ_KEY;q->key=opts[514]?opts[514]:'-';q->next=0;last_command=q;callback(DEP_cmdq_pop);return q;}
char * corpse_xname(struct obj * a0,const char * a1,unsigned int a2){append("corpse_xname:%d:%s:%ld;",oid(a0),a1?a1:"(null)",(long)a2);callback(DEP_corpse_xname);return namebuf("value");}
void curse(struct obj * a0){append("curse:%d;",oid(a0));a0->cursed=1;a0->blessed=0;callback(DEP_curse);}
char * doname(struct obj * a0){append("doname:%d;",oid(a0));callback(DEP_doname);return namebuf("value");}
void dropx(struct obj * a0){append("dropx:%d;",oid(a0));callback(DEP_dropx);}
boolean drown(void){append("drown;");callback(DEP_drown);return configured[DEP_drown]?opts[DEP_drown]:0;}
const char * empty_handed(void){append("empty_handed;");callback(DEP_empty_handed);return namebuf("value");}
void encumber_msg(void){append("encumber_msg;");callback(DEP_encumber_msg);}
void end_burn(struct obj * a0,boolean a1){append("end_burn:%d:%ld;",oid(a0),(long)a1);callback(DEP_end_burn);}
int erode_obj(struct obj * a0,const char * a1,int a2,int a3){append("erode_obj:%d:%s:%ld:%ld;",oid(a0),a1?a1:"(null)",(long)a2,(long)a3);callback(DEP_erode_obj);return configured[DEP_erode_obj]?opts[DEP_erode_obj]:0;}
boolean erosion_matters(struct obj * a0){append("erosion_matters:%d;",oid(a0));callback(DEP_erosion_matters);return configured[DEP_erosion_matters]?opts[DEP_erosion_matters]:0;}
boolean extremeattr(int a0){append("extremeattr:%ld;",(long)a0);callback(DEP_extremeattr);return configured[DEP_extremeattr]?opts[DEP_extremeattr]:0;}
int float_down(long a0,long a1){append("float_down:%ld:%ld;",(long)a0,(long)a1);callback(DEP_float_down);return configured[DEP_float_down]?opts[DEP_float_down]:0;}
void float_up(void){append("float_up;");callback(DEP_float_up);}
void float_vs_flight(void){append("float_vs_flight;");callback(DEP_float_vs_flight);}
const char * gloves_simple_name(struct obj * a0){append("gloves_simple_name:%d;",oid(a0));callback(DEP_gloves_simple_name);return namebuf("value");}
boolean gulp_blnd_check(void){append("gulp_blnd_check;");callback(DEP_gulp_blnd_check);return configured[DEP_gulp_blnd_check]?opts[DEP_gulp_blnd_check]:0;}
boolean has_ceiling(d_level * a0){append("has_ceiling:ptr;");callback(DEP_has_ceiling);return configured[DEP_has_ceiling]?opts[DEP_has_ceiling]:0;}
const char * hcolor(const char * a0){append("hcolor:%s;",a0?a0:"(null)");callback(DEP_hcolor);return namebuf("value");}
const char * helm_simple_name(struct obj * a0){append("helm_simple_name:%d;",oid(a0));callback(DEP_helm_simple_name);return namebuf("value");}
const char * hliquid(const char * a0){append("hliquid:%s;",a0?a0:"(null)");callback(DEP_hliquid);return namebuf("value");}
void instapetrify(const char * a0){append("instapetrify:%s;",a0?a0:"(null)");callback(DEP_instapetrify);}
boolean is_flammable(struct obj * a0){append("is_flammable:%d;",oid(a0));callback(DEP_is_flammable);return configured[DEP_is_flammable]?opts[DEP_is_flammable]:0;}
boolean is_lava(coordxy a0,coordxy a1){append("is_lava:%ld:%ld;",(long)a0,(long)a1);callback(DEP_is_lava);return configured[DEP_is_lava]?opts[DEP_is_lava]:0;}
boolean is_pool(coordxy a0,coordxy a1){append("is_pool:%ld:%ld;",(long)a0,(long)a1);callback(DEP_is_pool);return configured[DEP_is_pool]?opts[DEP_is_pool]:0;}
boolean is_pool_or_lava(coordxy a0,coordxy a1){append("is_pool_or_lava:%ld:%ld;",(long)a0,(long)a1);callback(DEP_is_pool_or_lava);return configured[DEP_is_pool_or_lava]?opts[DEP_is_pool_or_lava]:0;}
boolean is_rottable(struct obj * a0){append("is_rottable:%d;",oid(a0));callback(DEP_is_rottable);return configured[DEP_is_rottable]?opts[DEP_is_rottable]:0;}
boolean is_worn(struct obj * a0){append("is_worn:%d;",oid(a0));callback(DEP_is_worn);return configured[DEP_is_worn]?opts[DEP_is_worn]:0;}
boolean is_worn_by_type(struct obj * a0){append("is_worn_by_type:%d;",oid(a0));callback(DEP_is_worn_by_type);return configured[DEP_is_worn_by_type]?opts[DEP_is_worn_by_type]:0;}
char * killer_xname(struct obj * a0){append("killer_xname:%d;",oid(a0));callback(DEP_killer_xname);return namebuf("value");}
void livelog_newform(boolean a0,int a1,int a2){append("livelog_newform:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2);callback(DEP_livelog_newform);}
void make_glib(int a0){append("glib:%d;",a0);u.uprops[GLIB].intrinsic=a0;callback(DEP_make_glib);}
boolean make_hallucinated(long a0,boolean a1,long a2){append("halluc:%ld:%d:%ld;",a0,a1,a2);u.uprops[HALLUC].intrinsic=a0;callback(DEP_make_hallucinated);return opts[DEP_make_hallucinated];}
void make_slimed(long a0,const char * a1){append("slimed:%ld;",a0);u.uprops[SLIMED].intrinsic=a0;callback(DEP_make_slimed);}
char * makeplural(const char * a0){append("makeplural:%s;",a0?a0:"(null)");callback(DEP_makeplural);return namebuf("value");}
char * makesingular(const char * a0){append("makesingular:%s;",a0?a0:"(null)");callback(DEP_makesingular);return namebuf("value");}
boolean menu_class_present(int a0){append("menu_class_present:%ld;",(long)a0);callback(DEP_menu_class_present);return configured[DEP_menu_class_present]?opts[DEP_menu_class_present]:0;}
void newsym(coordxy a0,coordxy a1){append("newsym:%ld:%ld;",(long)a0,(long)a1);callback(DEP_newsym);}
int num_horns(struct permonst * a0){append("num_horns:ptr;");callback(DEP_num_horns);return configured[DEP_num_horns]?opts[DEP_num_horns]:0;}
boolean obj_is_pname(struct obj * a0){append("obj_is_pname:%d;",oid(a0));callback(DEP_obj_is_pname);return configured[DEP_obj_is_pname]?opts[DEP_obj_is_pname]:0;}
const char * obj_pmname(struct obj * a0){append("obj_pmname:%d;",oid(a0));callback(DEP_obj_pmname);return namebuf("value");}
boolean obj_resists(struct obj * a0,int a1,int a2){append("obj_resists:%d:%ld:%ld;",oid(a0),(long)a1,(long)a2);callback(DEP_obj_resists);return configured[DEP_obj_resists]?opts[DEP_obj_resists]:0;}
void observe_object(struct obj * a0){append("observe_object:%d;",oid(a0));callback(DEP_observe_object);}
boolean on_level(d_level * a0,d_level * a1){append("on_level:ptr:ptr;");callback(DEP_on_level);return configured[DEP_on_level]?opts[DEP_on_level]:0;}
char * otense(struct obj * a0,const char * a1){append("otense:%d:%s;",oid(a0),a1);callback(DEP_otense);return namebuf("value");}
char paranoid_ynq(boolean a0,const char * a1,boolean a2){append("paranoid_ynq:%ld:%s:%ld;",(long)a0,a1?a1:"(null)",(long)a2);callback(DEP_paranoid_ynq);return configured[DEP_paranoid_ynq]?opts[DEP_paranoid_ynq]:0;}
int poly_gender(void){append("poly_gender;");callback(DEP_poly_gender);return configured[DEP_poly_gender]?opts[DEP_poly_gender]:0;}
void prinv(const char * a0,struct obj * a1,long a2){append("prinv:%s:%d:%ld;",a0?a0:"(null)",oid(a1),(long)a2);callback(DEP_prinv);}
int racial_exception(struct monst * a0,struct obj * a1){append("racial_exception:%d:%d;",mid(a0),oid(a1));callback(DEP_racial_exception);return configured[DEP_racial_exception]?opts[DEP_racial_exception]:0;}
boolean region_danger(void){append("region_danger;");callback(DEP_region_danger);return configured[DEP_region_danger]?opts[DEP_region_danger]:0;}
void remove_worn_item(struct obj * a0,boolean a1){append("remove_worn:%d:%d;",oid(a0),a1);setnotworn(a0);callback(DEP_remove_worn_item);}
void rescham(void){append("rescham;");callback(DEP_rescham);}
void restartcham(void){append("restartcham;");callback(DEP_restartcham);}
char * safe_typename(int a0){append("safe_typename:%ld;",(long)a0);callback(DEP_safe_typename);return namebuf("value");}
void see_monsters(void){append("see_monsters;");callback(DEP_see_monsters);}
void self_invis_message(void){append("self_invis_message;");callback(DEP_self_invis_message);}
void selftouch(const char * a0){append("selftouch:%s;",a0);callback(DEP_selftouch);}
void set_bc(int a0){append("set_bc:%ld;",(long)a0);callback(DEP_set_bc);}
void set_bknown(struct obj * a0,unsigned int a1){append("bknown:%d:%u;",oid(a0),a1);if(oid(a0)==-99)append("dummyzero:%d;",!memcmp(a0,&cg.zeroobj,sizeof* a0));a0->bknown=a1;callback(DEP_set_bknown);}
void set_mimic_blocking(void){append("set_mimic_blocking;");callback(DEP_set_mimic_blocking);}
const char * shield_simple_name(struct obj * a0){append("shield_simple_name:%d;",oid(a0));callback(DEP_shield_simple_name);return namebuf("value");}
const char * shirt_simple_name(struct obj * a0){append("shirt_simple_name:%d;",oid(a0));callback(DEP_shirt_simple_name);return namebuf("value");}
char * shk_your(char*a0,struct obj*a1){strcpy(a0,"your");append("shk_your:%d;",oid(a1));callback(DEP_shk_your);return a0;}
void silly_thing(const char * a0,struct obj * a1){append("silly_thing:%s:%d;",a0,oid(a1));callback(DEP_silly_thing);}
char * simpleonames(struct obj * a0){append("simpleonames:%d;",oid(a0));callback(DEP_simpleonames);return namebuf("value");}
boolean sliparm(struct permonst * a0){append("sliparm:ptr;");callback(DEP_sliparm);return configured[DEP_sliparm]?opts[DEP_sliparm]:0;}
void spoteffects(boolean a0){append("spoteffects:%ld;",(long)a0);callback(DEP_spoteffects);}
void stop_occupation(void){append("stop_occupation;");callback(DEP_stop_occupation);}
char * strncpy(char *restrict a0,const char *restrict a1,size_t a2){append("strncpy:%s:%s:%ld;",a0?a0:"(null)",a1?a1:"(null)",(long)a2);callback(DEP_strncpy);return namebuf("value");}
const char * suit_simple_name(struct obj * a0){append("suit_simple_name:%d;",oid(a0));callback(DEP_suit_simple_name);return namebuf("value");}
const char * surface(coordxy a0,coordxy a1){append("surface:%ld:%ld;",(long)a0,(long)a1);callback(DEP_surface);return namebuf("value");}
char * the(const char * a0){append("the:%s;",a0?a0:"(null)");callback(DEP_the);return namebuf("value");}
char * thesimpleoname(struct obj * a0){append("thesimpleoname:%d;",oid(a0));callback(DEP_thesimpleoname);return namebuf("value");}
void toggle_blindness(void){append("toggle_blindness;");callback(DEP_toggle_blindness);}
void trycall(struct obj * a0){append("trycall:%d;",oid(a0));callback(DEP_trycall);}
boolean u_safe_from_fatal_corpse(struct obj * a0,int a1){append("u_safe_from_fatal_corpse:%d:%ld;",oid(a0),(long)a1);callback(DEP_u_safe_from_fatal_corpse);return configured[DEP_u_safe_from_fatal_corpse]?opts[DEP_u_safe_from_fatal_corpse]:0;}
void uchangealign(int a0,int a1){append("align:%d:%d;",a0,a1);u.ualign.type=a0;callback(DEP_uchangealign);}
void useup(struct obj * a0){append("useup:%d;",oid(a0));dispose(a0);}
char * vtense(const char * a0,const char * a1){append("vtense:%s:%s;",a0?a0:"(null)",a1);callback(DEP_vtense);return namebuf("value");}
const char * weapon_descr(struct obj * a0){append("weapon_descr:%d;",oid(a0));callback(DEP_weapon_descr);return namebuf("value");}
boolean wearing_armor(void){append("wearing_armor;");callback(DEP_wearing_armor);return configured[DEP_wearing_armor]?opts[DEP_wearing_armor]:0;}
int welded(struct obj * a0){append("welded:%d;",oid(a0));callback(DEP_welded);return configured[DEP_welded]?opts[DEP_welded]:0;}
struct obj * which_armor(struct monst * a0,long a1){append("which_armor:%d:%ld;",mid(a0),(long)a1);callback(DEP_which_armor);return 0;}
char * x_monnam(struct monst * a0,int a1,const char * a2,int a3,boolean a4){append("x_monnam:%d:%ld:%s:%ld:%ld;",mid(a0),(long)a1,a2?a2:"(null)",(long)a3,(long)a4);callback(DEP_x_monnam);return namebuf("value");}
char * xname(struct obj * a0){append("xname:%d;",oid(a0));callback(DEP_xname);return namebuf("value");}
char yn_function(const char * a0,const char * a1,char a2,boolean a3){append("yn_function:%s:%s:%ld:%ld;",a0?a0:"(null)",a1?a1:"(null)",(long)a2,(long)a3);callback(DEP_yn_function);return configured[DEP_yn_function]?opts[DEP_yn_function]:0;}
char * yname(struct obj * a0){append("yname:%d;",oid(a0));callback(DEP_yname);return namebuf("value");}

static struct obj**slots[]={&uarm,&uarmc,&uarmh,&uarms,&uarmg,&uarmf,&uarmu,&uleft,&uright,&uwep,&uswapwep,&uquiver,&uamul,&ublindf,&uball,0,&uskin};
static const long masks[]={W_ARM,W_ARMC,W_ARMH,W_ARMS,W_ARMG,W_ARMF,W_ARMU,W_RINGL,W_RINGR,W_WEP,W_SWAPWEP,W_QUIVER,W_AMUL,W_TOOL,W_BALL,W_CHAIN,0};
static int mutation_stage=-1,mutation_slot,mutation_obj;
static void mutate_equipment(int stage){if(stage==mutation_stage){mutation_stage=-1;*slots[mutation_slot]=mutation_obj<0?0:pool[mutation_obj];append("mutate:%d:%d;",mutation_slot,mutation_obj);}}
void probe_mutation(int stage,int slot,int obj){mutation_stage=stage;mutation_slot=slot;mutation_obj=obj;}
static void dispose(struct obj*o){int i=oid(o);append("dispose:%d;",i);struct obj**h=&gi.invent;while(*h&&*h!=o)h=&(*h)->nobj;if(*h)*h=o->nobj;for(int k=0;k<17;k++)if(slots[k]&&*slots[k]==o)*slots[k]=0;if(i>=0){pool[i]=0;free(o);frees++;}}
static int draw(int bound){int v=nr?rolls[ri++%nr]:(int)((seed=seed*1664525U+1013904223U)>>1);if(bound<=0){append("badbound:%d;",bound);return 0;}return(unsigned)v%(unsigned)bound;}
boolean rng_log_enabled(void){return !opts[500];}
void rng_log_set_caller(const char * a0,int a1,const char * a2){callerfile=a0;callerline=a1;callerfn=a2;append("caller:%s:%d:%s;",a0,a1,a2);}
int (rn2)(int a0){int v=draw(a0);append("rn2:%d:%d;",a0,v);callback(DEP_rn2);return v;}
int (rnd)(int a0){int v=draw(a0)+1;append("rnd:%d:%d;",a0,v);callback(DEP_rnd);return v;}
int rn2_on_display_rng(int a0){int v=draw(a0);append("display:%d:%d;",a0,v);return v;}
boolean debugcore(const char * a0,boolean a1){const char*b=strrchr(a0,'/');append("debug:%s:%d;",b?b+1:a0,a1);return opts[DEP_debugcore];}
struct obj * getobj(const char * a0,int (*a1)(struct obj *),unsigned int a2){append("getobj:%s:%u:%d;",a0,a2,a1(pool[opts[501]]));callback(DEP_getobj);return opts[510]?0:pool[opts[501]];}
int ggetobj(const char * a0,int (*a1)(struct obj *),int a2,boolean a3,unsigned int * a4){append("ggetobj:%s:%d:%d;",a0,a2,a3);if(a4)*a4=opts[DEP_ggetobj];callback(DEP_ggetobj);return opts[502]?a1(pool[opts[501]]):opts[DEP_ggetobj];}
boolean allow_all(struct obj * a0){return TRUE;}
boolean allow_category(struct obj * a0){append("allow:%d;",oid(a0));return !opts[DEP_allow_category];}
int any_obj_ok(struct obj * a0){return a0?GETOBJ_SUGGEST:GETOBJ_EXCLUDE;}
void set_occupation(int (*a0)(void),const char * a1,cmdcount_nht a2){append("occupation:%s:%ld;",a1,a2);occupation=a0;callback(DEP_set_occupation);}
int retouch_object(struct obj ** a0,boolean a1){append("retouch:%d:%d;",oid(*a0),a1);if(opts[511]) *a0=opts[511]<0?0:pool[opts[511]-1];callback(DEP_retouch_object);return !opts[DEP_retouch_object];}
void nomul(int a0){append("nomul:%d;",a0);gm.multi=a0;callback(DEP_nomul);}
void unmul(const char * a0){append("unmul:%s;",a0?a0:"(null)");if(ga.afternmv){int(*fn)(void)=ga.afternmv;ga.afternmv=0;append("after:%d;",fn());}gm.multi=0;callback(DEP_unmul);}
void update_inventory(void){append("update_inventory;");callback(DEP_update_inventory);}
void discover_object(int a0,boolean a1,boolean a2,boolean a3){append("discover:%d:%d:%d:%d;",a0,a1,a2,a3);objects[a0].oc_name_known=a1;callback(DEP_discover_object);}
void set_itimeout(long * a0,long a1){append("settimeout:%ld;",a1);*a0=(*a0&~TIMEOUT)|(a1&TIMEOUT);callback(DEP_set_itimeout);}
void incr_itimeout(long * a0,int a1){append("inctimeout:%d;",a1);*a0=(*a0&~TIMEOUT)|((*a0+a1)&TIMEOUT);callback(DEP_incr_itimeout);}
void make_blinded(long a0,boolean a1){append("blind:%ld:%d;",a0,a1);u.uprops[BLINDED].intrinsic=a0;callback(DEP_make_blinded);}
void setworn(struct obj * a0,long a1){append("setworn:%d:%ld;",oid(a0),a1);for(int k=0;k<16;k++)if(slots[k]&&(a1&masks[k])){if(*slots[k])(*slots[k])->owornmask&=~masks[k];*slots[k]=a0;if(a0)a0->owornmask|=masks[k];}callback(DEP_setworn);}
void setnotworn(struct obj * a0){append("setnotworn:%d;",oid(a0));for(int k=0;k<17;k++)if(slots[k]&&*slots[k]==a0)*slots[k]=0;a0->owornmask=0;callback(DEP_setnotworn);}
void setuwep(struct obj * a0){append("setuwep:%d;",oid(a0));uwep=a0;callback(DEP_setuwep);}
void setuswapwep(struct obj * a0){append("setuswapwep:%d;",oid(a0));uswapwep=a0;callback(DEP_setuswapwep);}
void setuqwep(struct obj * a0){append("setuqwep:%d;",oid(a0));uquiver=a0;callback(DEP_setuqwep);}
void Norep(const char * a0,...){va_list ap;va_start(ap,a0);message("Norep",a0,ap);va_end(ap);callback(DEP_Norep);}
void There(const char * a0,...){va_list ap;va_start(ap,a0);message("There",a0,ap);va_end(ap);callback(DEP_There);}
void You(const char * a0,...){va_list ap;va_start(ap,a0);message("You",a0,ap);va_end(ap);callback(DEP_You);}
void You_cant(const char * a0,...){va_list ap;va_start(ap,a0);message("You_cant",a0,ap);va_end(ap);callback(DEP_You_cant);}
void You_feel(const char * a0,...){va_list ap;va_start(ap,a0);message("You_feel",a0,ap);va_end(ap);callback(DEP_You_feel);}
void You_hear(const char * a0,...){va_list ap;va_start(ap,a0);message("You_hear",a0,ap);va_end(ap);callback(DEP_You_hear);}
void You_see(const char * a0,...){va_list ap;va_start(ap,a0);message("You_see",a0,ap);va_end(ap);callback(DEP_You_see);}
void Your(const char * a0,...){va_list ap;va_start(ap,a0);message("Your",a0,ap);va_end(ap);callback(DEP_Your);}
void urgent_pline(const char * a0,...){va_list ap;va_start(ap,a0);message("urgent_pline",a0,ap);va_end(ap);callback(DEP_urgent_pline);}
void pline(const char * a0,...){va_list ap;va_start(ap,a0);message("pline",a0,ap);va_end(ap);callback(DEP_pline);}
void pline_The(const char * a0,...){va_list ap;va_start(ap,a0);message("pline_The",a0,ap);va_end(ap);callback(DEP_pline_The);}
void impossible(const char * a0,...){va_list ap;va_start(ap,a0);message("impossible",a0,ap);va_end(ap);callback(DEP_impossible);}
void panic(const char * a0,...){va_list ap;va_start(ap,a0);message("panic",a0,ap);va_end(ap);panic_code=1;if(guarding)longjmp(bail,1);abort();}
int query_category(const char * a0,struct obj * a1,int a2,menu_item ** a3,int a4){append("query_category:%s:%d:%d;",a0,a2,a4);*a3=0;callback(DEP_query_category);int n=opts[DEP_query_category];if(n>0){*a3=malloc(n*sizeof**a3);last_menu=*a3;for(int i=0;i<n;i++){(*a3)[i].item.a_int=opts[503];(*a3)[i].count=1;}}return n;}
int query_objlist(const char * a0,struct obj ** a1,int a2,menu_item ** a3,int a4,boolean (*a5)(struct obj *)){append("query_objlist:%s:%d:%d;",a0,a2,a4);*a3=0;callback(DEP_query_objlist);int n=opts[DEP_query_objlist];if(n>0){*a3=malloc(n*sizeof**a3);last_menu=*a3;for(int i=0;i<n;i++){(*a3)[i].item.a_obj=pool[opts[501]];append("filter:%d;",a5(pool[opts[501]]));(*a3)[i].count=1;}}return n;}

static char input_text[2][BUFSZ],result_text[BUFSZ];static long cells[4];static boolean boolcells[4];static struct obj*objcell;
static int unrelated_after(void){append("unrelated_after;");return 7;}
static uintptr_t callback_pointer(int i){
#ifdef TELEPORT_REFERENCE_TU
 switch(i){
case 0:return(uintptr_t)Armor_on;
case 1:return(uintptr_t)Shirt_on;
case 2:return(uintptr_t)Cloak_on;
case 3:return(uintptr_t)Boots_on;
case 4:return(uintptr_t)Helmet_on;
case 5:return(uintptr_t)Gloves_on;
case 6:return(uintptr_t)Shield_on;
case 7:return(uintptr_t)Armor_off;
case 8:return(uintptr_t)Shirt_off;
case 9:return(uintptr_t)Cloak_off;
case 10:return(uintptr_t)Boots_off;
case 11:return(uintptr_t)Helmet_off;
case 12:return(uintptr_t)Gloves_off;
case 13:return(uintptr_t)Shield_off;
case 14:return(uintptr_t)take_off;
case 15:return(uintptr_t)select_off;
case 16:return(uintptr_t)puton_ok;
case 17:return(uintptr_t)remove_ok;
case 18:return(uintptr_t)wear_ok;
case 19:return(uintptr_t)takeoff_ok;
case 20:return(uintptr_t)any_worn_armor_ok;
case 21:return(uintptr_t)is_worn;
case 22:return(uintptr_t)is_worn_by_type;
case 23:return(uintptr_t)allow_all;
case 24:return(uintptr_t)allow_category;
case 25:return(uintptr_t)do_reqmenu;
default:return(uintptr_t)unrelated_after;}
#else
 extern uintptr_t teleport_do_wear_callback_pointer(int);return i<26?teleport_do_wear_callback_pointer(i):(uintptr_t)unrelated_after;
#endif
}
static int afterid(void){if(!ga.afternmv)return -1;for(int i=0;i<26;i++)if((uintptr_t)ga.afternmv==callback_pointer(i))return i;return 99;}
int probe_counter(int i,int value,int set){
#ifdef TELEPORT_REFERENCE_TU
 int*p=i?&Naccessories:&Narmorpieces;if(set)*p=value;return*p;
#else
 extern int teleport_do_wear_test_counter(int,int,int);return teleport_do_wear_test_counter(i,value,set);
#endif
}
void probe_text(int which,const char*t){snprintf(input_text[which],BUFSZ,"%s",t?t:"");}
int probe_context_size(void){return sizeof(struct obj);}
int probe_layout_count(void){return sizeof teleport_do_wear_layout/sizeof*teleport_do_wear_layout;}
const char*probe_layout_name(int i){return teleport_do_wear_layout[i].name;}
size_t probe_layout_value(int i){return teleport_do_wear_layout[i].value;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
const char*probe_trace(void){return traces;}
int probe_dep_count(void){return sizeof dep_names/sizeof*dep_names;}
const char*probe_dep_name(int i){return dep_names[i];}
void probe_option(int i,int value){opts[i]=value;configured[i]=1;}
void probe_roll(int n,int value){if(n<0){nr=ri=0;return;}rolls[n]=value;if(n>=nr)nr=n+1;}
void probe_callback(int grow,int enter){growth_stage=grow;reenter_stage=enter;}
void probe_clear(void){stack_min=stack_max=0;ti=0;traces[0]=0;ri=0;}
void probe_reset(unsigned value){
 for(int i=0;i<32;i++){free(pool[i]);pool[i]=0;}free(grown);grown=0;
memset(&flags,0,sizeof flags);
memset(&iflags,0,sizeof iflags);
memset(&condtests,0,sizeof condtests);
memset(&uarm,0,sizeof uarm);
memset(&uarmc,0,sizeof uarmc);
memset(&uarmh,0,sizeof uarmh);
memset(&uarms,0,sizeof uarms);
memset(&uarmg,0,sizeof uarmg);
memset(&uarmf,0,sizeof uarmf);
memset(&uarmu,0,sizeof uarmu);
memset(&uskin,0,sizeof uskin);
memset(&uamul,0,sizeof uamul);
memset(&uleft,0,sizeof uleft);
memset(&uright,0,sizeof uright);
memset(&ublindf,0,sizeof ublindf);
memset(&uwep,0,sizeof uwep);
memset(&uswapwep,0,sizeof uswapwep);
memset(&uquiver,0,sizeof uquiver);
memset(&uball,0,sizeof uball);
memset(&u,0,sizeof u);
memset(&disp,0,sizeof disp);
memset(&ga,0,sizeof ga);
memset(&gi,0,sizeof gi);
memset(&gm,0,sizeof gm);
memset(&gn,0,sizeof gn);
memset(&gu,0,sizeof gu);
memset(&gw,0,sizeof gw);
memset(&gy,0,sizeof gy);
memset(&svc,0,sizeof svc);
memset(&svd,0,sizeof svd);
memset(&program_state,0,sizeof program_state);
memset(opts,0,sizeof opts);memset(configured,0,sizeof configured);memset(monsters,0,sizeof monsters);memset(cells,0,sizeof cells);memset(boolcells,0,sizeof boolcells);objcell=0;
objects_globals_init();monst_globals_init();u.ux=u.uy=10;u.umonnum=u.umonster=PM_HUMAN;u.uz.dnum=2;u.uz.dlevel=3;u.ulevel=10;u.uhp=u.uhpmax=100;for(int i=0;i<A_MAX;i++)u.acurr.a[i]=u.amax.a[i]=12;
gy.youmonst.data=&mons[PM_HUMAN];gy.youmonst.mhp=gy.youmonst.mhpmax=100;for(int i=0;i<4;i++){monsters[i].data=&mons[PM_HUMAN];monsters[i].mhp=monsters[i].mhpmax=100;monsters[i].mx=20+i;monsters[i].my=10;}
svd.dungeon_topology.d_air_level.dnum=10;svd.dungeon_topology.d_air_level.dlevel=1;svd.dungeon_topology.d_water_level.dnum=11;svd.dungeon_topology.d_water_level.dlevel=1;
flags.verbose=1;strcpy(input_text[0],"take off");input_text[1][0]=0;result_text[0]=0;occupation=0;frees=nr=ri=0;policy_frees=menu_frees=command_frees=0;last_menu=last_command=0;mutation_stage=-1;seed=value;growth_stage=reenter_stage=-1;panic_code=0;ti=ni=0;traces[0]=0;callerfile=callerfn="";callerline=0;probe_counter(0,0,1);probe_counter(1,0,1);
}
void probe_object(int i,int typ,long count){if(pool[i])dispose(pool[i]);struct obj*o=pool[i]=calloc(1,sizeof*o);o->o_id=i+1;o->otyp=typ;o->oclass=objects[typ].oc_class;o->quan=count;o->owt=(unsigned)(count*7);o->ox=o->oy=10;o->corpsenm=PM_HUMAN;o->where=OBJ_INVENT;o->nobj=gi.invent;gi.invent=o;}
void probe_objfield(int i,int key,int64_t value){struct obj*o=pool[i];switch(key){case 0:o->cursed=value;break;case 1:o->blessed=value;break;case 2:o->owornmask=value;break;case 3:o->bknown=value;break;case 4:o->known=value;break;case 5:o->dknown=value;break;case 6:o->spe=value;break;case 7:o->oeroded=value;break;case 8:o->oeroded2=value;break;case 9:o->oerodeproof=value;break;case 10:o->unpaid=value;break;case 11:o->corpsenm=value;break;case 12:o->oartifact=value;break;case 13:o->nobj=value<0?0:pool[value];break;case 14:o->where=value;break;default:abort();}}
void probe_equipment(int slot,int obj){if(!slots[slot])return;*slots[slot]=obj<0?0:pool[obj];if(obj>=0)pool[obj]->owornmask|=masks[slot];}
void probe_property(int key,int field,int64_t v){if(field==0)u.uprops[key].intrinsic=v;else if(field==1)u.uprops[key].extrinsic=v;else u.uprops[key].blocked=v;}
void probe_hero(int key,int64_t value){switch(key){case 0:flags.verbose=value;break;case 1:gi.initial_don=value;break;case 2:u.umonnum=value;gy.youmonst.data=&mons[value];break;case 3:u.uhandedness=value;break;case 4:u.uinwater=value;break;case 5:u.utrap=value;break;case 6:u.utraptype=value;break;case 7:u.usteed=value<0?0:monsters+value;break;case 8:u.utotype=value;break;case 9:svc.context.takeoff.mask=value;break;case 10:svc.context.takeoff.what=value;break;case 11:svc.context.takeoff.delay=value;break;case 12:ga.afternmv=value<0?0:(int(*)(void))callback_pointer(value);break;case 13:gm.multi=value;break;case 14:u.ualign.type=value;break;case 15:u.ualign.record=value;break;case 16:u.uroleplay.deaf=value;break;case 17:gu.urole.mnum=value;break;case 18:iflags.menu_requested=value;break;case 19:flags.menu_style=value;break;case 20:flags.female=value;break;case 21:iflags.cmdassist=value;break;case 22:u.ublessed=value;break;default:abort();}}
int probe_occupation(void){return occupation?occupation():-1;}
int probe_after(void){if(!ga.afternmv)return-1;return ga.afternmv();}
uintptr_t probe_pointer(int kind,int i){if(kind==0)return(uintptr_t)pool[i];if(kind==1)return(uintptr_t)&pool[i]->owornmask;if(kind==2)return(uintptr_t)&u.uprops[i];if(kind==3)return(uintptr_t)gn.nomovemsg;return 0;}
void probe_poison(void){volatile unsigned char a[8192];for(int i=0;i<8192;i++)a[i]=0xa5;}
static const char*fn_names[]={"fingers_or_gloves","off_msg","on_msg","toggle_stealth","toggle_displacement","Boots_on","Boots_off","Cloak_on","Cloak_off","Helmet_on","Helmet_off","hard_helmet","Gloves_on","wielding_corpse","Gloves_off","Shield_on","Shield_off","Shirt_on","Shirt_off","dragon_armor_handling","Armor_on","Armor_off","Armor_gone","Amulet_on","Amulet_off","learnring","adjust_attrib","Ring_on","Ring_off_or_gone","Ring_off","Ring_gone","Blindf_on","Blindf_off","set_wear","donning","doffing","cancel_doff","cancel_don","stop_donning","count_worn_stuff","armor_or_accessory_off","dotakeoff","ia_dotakeoff","doremring","cursed","armoroff","already_wearing","already_wearing2","canwearobj","accessory_or_armor_on","dowear","doputon","find_ac","glibr","some_armor","stuck_ring","unchanger","select_off","do_takeoff","take_off","better_not_take_that_off","reset_remarm","doddoremarm","remarm_swapwep","menu_remarm","wornarm_destroyed","maybe_destroy_armor","disintegrate_arm","obj_erode_type","destroy_arm","adj_abon","inaccessible_equipment","equip_ok","puton_ok","remove_ok","wear_ok","takeoff_ok","any_worn_armor_ok","count_worn_armor"};
const char*probe_function_name(int i){return fn_names[i];}
int64_t probe_action(int op,int64_t a,int64_t b,int64_t c,int64_t d){int64_t v[]={a,b,c,d};int64_t result=0;guarding=1;panic_code=0;result_text[0]=0;if(setjmp(bail)){guarding=0;return INT64_MIN;}switch(op){
case 0:{const char*p=fingers_or_gloves(v[0]);snprintf(result_text,sizeof result_text,"%s",p?p:"");result=p!=0;}break;
case 1:{off_msg((v[0]<0?0:pool[v[0]]));}break;
case 2:{on_msg((v[0]<0?0:pool[v[0]]));}break;
case 3:{toggle_stealth((v[0]<0?0:pool[v[0]]),v[1],v[2]);}break;
case 4:{toggle_displacement((v[0]<0?0:pool[v[0]]),v[1],v[2]);}break;
case 5:{result=Boots_on();}break;
case 6:{result=Boots_off();}break;
case 7:{result=Cloak_on();}break;
case 8:{result=Cloak_off();}break;
case 9:{result=Helmet_on();}break;
case 10:{result=Helmet_off();}break;
case 11:{result=hard_helmet((v[0]<0?0:pool[v[0]]));}break;
case 12:{result=Gloves_on();}break;
case 13:{wielding_corpse((v[0]<0?0:pool[v[0]]),(v[1]<0?0:pool[v[1]]),v[2]);}break;
case 14:{result=Gloves_off();}break;
case 15:{result=Shield_on();}break;
case 16:{result=Shield_off();}break;
case 17:{result=Shirt_on();}break;
case 18:{result=Shirt_off();}break;
case 19:{dragon_armor_handling((v[0]<0?0:pool[v[0]]),v[1],v[2]);}break;
case 20:{result=Armor_on();}break;
case 21:{result=Armor_off();}break;
case 22:{result=Armor_gone();}break;
case 23:{Amulet_on((v[0]<0?0:pool[v[0]]));}break;
case 24:{Amulet_off();}break;
case 25:{learnring((v[0]<0?0:pool[v[0]]),v[1]);}break;
case 26:{adjust_attrib((v[0]<0?0:pool[v[0]]),v[1],v[2]);}break;
case 27:{Ring_on((v[0]<0?0:pool[v[0]]));}break;
case 28:{Ring_off_or_gone((v[0]<0?0:pool[v[0]]),v[1]);}break;
case 29:{Ring_off((v[0]<0?0:pool[v[0]]));}break;
case 30:{Ring_gone((v[0]<0?0:pool[v[0]]));}break;
case 31:{Blindf_on((v[0]<0?0:pool[v[0]]));}break;
case 32:{Blindf_off((v[0]<0?0:pool[v[0]]));}break;
case 33:{set_wear((v[0]<0?0:pool[v[0]]));}break;
case 34:{result=donning((v[0]<0?0:pool[v[0]]));}break;
case 35:{result=doffing((v[0]<0?0:pool[v[0]]));}break;
case 36:{cancel_doff((v[0]<0?0:pool[v[0]]),v[1]);}break;
case 37:{cancel_don();}break;
case 38:{result=stop_donning((v[0]<0?0:pool[v[0]]));}break;
case 39:{count_worn_stuff(&objcell,v[1]);}break;
case 40:{result=armor_or_accessory_off((v[0]<0?0:pool[v[0]]));}break;
case 41:{result=dotakeoff();}break;
case 42:{result=ia_dotakeoff();}break;
case 43:{result=doremring();}break;
case 44:{result=cursed((v[0]<0?0:pool[v[0]]));}break;
case 45:{result=armoroff((v[0]<0?0:pool[v[0]]));}break;
case 46:{already_wearing((v[0]<0?0:input_text[0]));}break;
case 47:{already_wearing2((v[0]<0?0:input_text[0]),(v[1]<0?0:input_text[0]));}break;
case 48:{result=canwearobj((v[0]<0?0:pool[v[0]]),cells+v[1],v[2]);}break;
case 49:{result=accessory_or_armor_on((v[0]<0?0:pool[v[0]]));}break;
case 50:{result=dowear();}break;
case 51:{result=doputon();}break;
case 52:{find_ac();}break;
case 53:{glibr();}break;
case 54:{result=oid(some_armor((v[0]==-2?&gy.youmonst:v[0]<0?0:monsters+v[0])));}break;
case 55:{result=oid(stuck_ring((v[0]<0?0:pool[v[0]]),v[1]));}break;
case 56:{result=oid(unchanger());}break;
case 57:{result=select_off((v[0]<0?0:pool[v[0]]));}break;
case 58:{result=oid(do_takeoff());}break;
case 59:{result=take_off();}break;
case 60:{result=better_not_take_that_off((v[0]<0?0:pool[v[0]]));}break;
case 61:{reset_remarm();}break;
case 62:{result=doddoremarm();}break;
case 63:{result=remarm_swapwep();}break;
case 64:{result=menu_remarm(v[0]);}break;
case 65:{wornarm_destroyed((v[0]<0?0:pool[v[0]]));}break;
case 66:{result=oid(maybe_destroy_armor((v[0]<0?0:pool[v[0]]),(v[1]<0?0:pool[v[1]]),boolcells+v[2]));}break;
case 67:{result=disintegrate_arm((v[0]<0?0:pool[v[0]]));}break;
case 68:{result=obj_erode_type((v[0]<0?0:pool[v[0]]));}break;
case 69:{result=destroy_arm();}break;
case 70:{adj_abon((v[0]<0?0:pool[v[0]]),v[1]);}break;
case 71:{result=inaccessible_equipment((v[0]<0?0:pool[v[0]]),(v[1]<0?0:input_text[0]),v[2]);}break;
case 72:{result=equip_ok((v[0]<0?0:pool[v[0]]),v[1],v[2]);}break;
case 73:{result=puton_ok((v[0]<0?0:pool[v[0]]));}break;
case 74:{result=remove_ok((v[0]<0?0:pool[v[0]]));}break;
case 75:{result=wear_ok((v[0]<0?0:pool[v[0]]));}break;
case 76:{result=takeoff_ok((v[0]<0?0:pool[v[0]]));}break;
case 77:{result=any_worn_armor_ok((v[0]<0?0:pool[v[0]]));}break;
case 78:{result=count_worn_armor();}break;
default:abort();}guarding=0;return result;}
const char*probe_snapshot(void){size_t n=0;
#define P(...) do{n+=snprintf(snapshot+n,sizeof snapshot-n,__VA_ARGS__);if(n>=sizeof snapshot)abort();}while(0)
P("hero:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%ld;",u.ux,u.uy,u.umonnum,u.uhp,u.uhpmax,u.uac,u.ulevel,u.uinwater,u.ualign.type,u.ualign.record,u.ublessed,gm.multi);
P("context:%ld,%ld,%d,%d,%s;",svc.context.takeoff.mask,svc.context.takeoff.what,svc.context.takeoff.delay,svc.context.takeoff.cancelled_don,svc.context.takeoff.disrobing);
P("globals:%d,%d,%d,%d,%d,%d,%d,%s;",afterid(),disp.botl,gi.initial_don,probe_counter(0,0,0),probe_counter(1,0,0),frees,oid(objcell),gn.nomovemsg?gn.nomovemsg:"");
for(int k=0;k<17;k++)P("slot:%d,%d;",k,slots[k]?oid(*slots[k]):-1);
for(int i=0;i<A_MAX;i++)P("attr:%d,%d,%d,%d,%d;",i,u.acurr.a[i],u.amax.a[i],u.abon.a[i],u.atemp.a[i]);
for(int i=0;i<4;i++)P("cell:%d,%ld,%d;",i,cells[i],boolcells[i]);
for(int i=0;i<=LAST_PROP;i++)P("p:%d,%ld,%ld,%ld;",i,u.uprops[i].intrinsic,u.uprops[i].extrinsic,u.uprops[i].blocked);
for(int i=0;i<32;i++){struct obj*o=pool[i];if(!o){P("o:%d:null;",i);continue;}P("o:%d,%d,%ld,%ld,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d;",i,o->otyp,o->quan,o->owornmask,o->spe,o->cursed,o->blessed,o->known,o->dknown,o->bknown,o->in_use,o->oeroded,o->oeroded2,o->unpaid,oid(o->nobj));}
for(int i=0;i<NUM_OBJECTS;i++)if(objects[i].oc_name_known||objects[i].oc_uname)P("known:%d,%d,%s;",i,objects[i].oc_name_known,objects[i].oc_uname?objects[i].oc_uname:"");
P("result:%s;",result_text);
P("policyfree:%d,%d,%d;",policy_frees,menu_frees,command_frees);
P("scalar:flags.female:%llu;", (unsigned long long)((flags).female));
P("scalar:flags.verbose:%llu;", (unsigned long long)((flags).verbose));
P("scalar:flags.paranoia_bits:%llu;", (unsigned long long)((flags).paranoia_bits));
P("scalar:flags.menu_style:%llu;", (unsigned long long)((flags).menu_style));
P("scalar:iflags.in_lava_effects:%llu;", (unsigned long long)((iflags).in_lava_effects));
P("scalar:condtests[0].enabled:%llu;", (unsigned long long)(((condtests)[0]).enabled));
P("scalar:condtests[1].enabled:%llu;", (unsigned long long)(((condtests)[1]).enabled));
P("scalar:condtests[2].enabled:%llu;", (unsigned long long)(((condtests)[2]).enabled));
P("scalar:condtests[3].enabled:%llu;", (unsigned long long)(((condtests)[3]).enabled));
P("scalar:condtests[4].enabled:%llu;", (unsigned long long)(((condtests)[4]).enabled));
P("scalar:condtests[5].enabled:%llu;", (unsigned long long)(((condtests)[5]).enabled));
P("scalar:condtests[6].enabled:%llu;", (unsigned long long)(((condtests)[6]).enabled));
P("scalar:condtests[7].enabled:%llu;", (unsigned long long)(((condtests)[7]).enabled));
P("scalar:condtests[8].enabled:%llu;", (unsigned long long)(((condtests)[8]).enabled));
P("scalar:condtests[9].enabled:%llu;", (unsigned long long)(((condtests)[9]).enabled));
P("scalar:condtests[10].enabled:%llu;", (unsigned long long)(((condtests)[10]).enabled));
P("scalar:condtests[11].enabled:%llu;", (unsigned long long)(((condtests)[11]).enabled));
P("scalar:condtests[12].enabled:%llu;", (unsigned long long)(((condtests)[12]).enabled));
P("scalar:condtests[13].enabled:%llu;", (unsigned long long)(((condtests)[13]).enabled));
P("scalar:condtests[14].enabled:%llu;", (unsigned long long)(((condtests)[14]).enabled));
P("scalar:condtests[15].enabled:%llu;", (unsigned long long)(((condtests)[15]).enabled));
P("scalar:condtests[16].enabled:%llu;", (unsigned long long)(((condtests)[16]).enabled));
P("scalar:condtests[17].enabled:%llu;", (unsigned long long)(((condtests)[17]).enabled));
P("scalar:condtests[18].enabled:%llu;", (unsigned long long)(((condtests)[18]).enabled));
P("scalar:condtests[19].enabled:%llu;", (unsigned long long)(((condtests)[19]).enabled));
P("scalar:condtests[20].enabled:%llu;", (unsigned long long)(((condtests)[20]).enabled));
P("scalar:condtests[21].enabled:%llu;", (unsigned long long)(((condtests)[21]).enabled));
P("scalar:condtests[22].enabled:%llu;", (unsigned long long)(((condtests)[22]).enabled));
P("scalar:condtests[23].enabled:%llu;", (unsigned long long)(((condtests)[23]).enabled));
P("scalar:condtests[24].enabled:%llu;", (unsigned long long)(((condtests)[24]).enabled));
P("scalar:condtests[25].enabled:%llu;", (unsigned long long)(((condtests)[25]).enabled));
P("scalar:condtests[26].enabled:%llu;", (unsigned long long)(((condtests)[26]).enabled));
P("scalar:condtests[27].enabled:%llu;", (unsigned long long)(((condtests)[27]).enabled));
P("scalar:condtests[28].enabled:%llu;", (unsigned long long)(((condtests)[28]).enabled));
P("scalar:condtests[29].enabled:%llu;", (unsigned long long)(((condtests)[29]).enabled));
P("scalar:u.ux:%llu;", (unsigned long long)((u).ux));
P("scalar:u.uy:%llu;", (unsigned long long)((u).uy));
P("scalar:u.uz.dnum:%llu;", (unsigned long long)(((u).uz).dnum));
P("scalar:u.uz.dlevel:%llu;", (unsigned long long)(((u).uz).dlevel));
P("scalar:u.utrap:%llu;", (unsigned long long)((u).utrap));
P("scalar:u.utraptype:%llu;", (unsigned long long)((u).utraptype));
P("scalar:u.uprops[0].extrinsic:%llu;", (unsigned long long)((((u).uprops)[0]).extrinsic));
P("scalar:u.uprops[0].blocked:%llu;", (unsigned long long)((((u).uprops)[0]).blocked));
P("scalar:u.uprops[0].intrinsic:%llu;", (unsigned long long)((((u).uprops)[0]).intrinsic));
P("scalar:u.uprops[1].extrinsic:%llu;", (unsigned long long)((((u).uprops)[1]).extrinsic));
P("scalar:u.uprops[1].blocked:%llu;", (unsigned long long)((((u).uprops)[1]).blocked));
P("scalar:u.uprops[1].intrinsic:%llu;", (unsigned long long)((((u).uprops)[1]).intrinsic));
P("scalar:u.uprops[2].extrinsic:%llu;", (unsigned long long)((((u).uprops)[2]).extrinsic));
P("scalar:u.uprops[2].blocked:%llu;", (unsigned long long)((((u).uprops)[2]).blocked));
P("scalar:u.uprops[2].intrinsic:%llu;", (unsigned long long)((((u).uprops)[2]).intrinsic));
P("scalar:u.uprops[3].extrinsic:%llu;", (unsigned long long)((((u).uprops)[3]).extrinsic));
P("scalar:u.uprops[3].blocked:%llu;", (unsigned long long)((((u).uprops)[3]).blocked));
P("scalar:u.uprops[3].intrinsic:%llu;", (unsigned long long)((((u).uprops)[3]).intrinsic));
P("scalar:u.uprops[4].extrinsic:%llu;", (unsigned long long)((((u).uprops)[4]).extrinsic));
P("scalar:u.uprops[4].blocked:%llu;", (unsigned long long)((((u).uprops)[4]).blocked));
P("scalar:u.uprops[4].intrinsic:%llu;", (unsigned long long)((((u).uprops)[4]).intrinsic));
P("scalar:u.uprops[5].extrinsic:%llu;", (unsigned long long)((((u).uprops)[5]).extrinsic));
P("scalar:u.uprops[5].blocked:%llu;", (unsigned long long)((((u).uprops)[5]).blocked));
P("scalar:u.uprops[5].intrinsic:%llu;", (unsigned long long)((((u).uprops)[5]).intrinsic));
P("scalar:u.uprops[6].extrinsic:%llu;", (unsigned long long)((((u).uprops)[6]).extrinsic));
P("scalar:u.uprops[6].blocked:%llu;", (unsigned long long)((((u).uprops)[6]).blocked));
P("scalar:u.uprops[6].intrinsic:%llu;", (unsigned long long)((((u).uprops)[6]).intrinsic));
P("scalar:u.uprops[7].extrinsic:%llu;", (unsigned long long)((((u).uprops)[7]).extrinsic));
P("scalar:u.uprops[7].blocked:%llu;", (unsigned long long)((((u).uprops)[7]).blocked));
P("scalar:u.uprops[7].intrinsic:%llu;", (unsigned long long)((((u).uprops)[7]).intrinsic));
P("scalar:u.uprops[8].extrinsic:%llu;", (unsigned long long)((((u).uprops)[8]).extrinsic));
P("scalar:u.uprops[8].blocked:%llu;", (unsigned long long)((((u).uprops)[8]).blocked));
P("scalar:u.uprops[8].intrinsic:%llu;", (unsigned long long)((((u).uprops)[8]).intrinsic));
P("scalar:u.uprops[9].extrinsic:%llu;", (unsigned long long)((((u).uprops)[9]).extrinsic));
P("scalar:u.uprops[9].blocked:%llu;", (unsigned long long)((((u).uprops)[9]).blocked));
P("scalar:u.uprops[9].intrinsic:%llu;", (unsigned long long)((((u).uprops)[9]).intrinsic));
P("scalar:u.uprops[10].extrinsic:%llu;", (unsigned long long)((((u).uprops)[10]).extrinsic));
P("scalar:u.uprops[10].blocked:%llu;", (unsigned long long)((((u).uprops)[10]).blocked));
P("scalar:u.uprops[10].intrinsic:%llu;", (unsigned long long)((((u).uprops)[10]).intrinsic));
P("scalar:u.uprops[11].extrinsic:%llu;", (unsigned long long)((((u).uprops)[11]).extrinsic));
P("scalar:u.uprops[11].blocked:%llu;", (unsigned long long)((((u).uprops)[11]).blocked));
P("scalar:u.uprops[11].intrinsic:%llu;", (unsigned long long)((((u).uprops)[11]).intrinsic));
P("scalar:u.uprops[12].extrinsic:%llu;", (unsigned long long)((((u).uprops)[12]).extrinsic));
P("scalar:u.uprops[12].blocked:%llu;", (unsigned long long)((((u).uprops)[12]).blocked));
P("scalar:u.uprops[12].intrinsic:%llu;", (unsigned long long)((((u).uprops)[12]).intrinsic));
P("scalar:u.uprops[13].extrinsic:%llu;", (unsigned long long)((((u).uprops)[13]).extrinsic));
P("scalar:u.uprops[13].blocked:%llu;", (unsigned long long)((((u).uprops)[13]).blocked));
P("scalar:u.uprops[13].intrinsic:%llu;", (unsigned long long)((((u).uprops)[13]).intrinsic));
P("scalar:u.uprops[14].extrinsic:%llu;", (unsigned long long)((((u).uprops)[14]).extrinsic));
P("scalar:u.uprops[14].blocked:%llu;", (unsigned long long)((((u).uprops)[14]).blocked));
P("scalar:u.uprops[14].intrinsic:%llu;", (unsigned long long)((((u).uprops)[14]).intrinsic));
P("scalar:u.uprops[15].extrinsic:%llu;", (unsigned long long)((((u).uprops)[15]).extrinsic));
P("scalar:u.uprops[15].blocked:%llu;", (unsigned long long)((((u).uprops)[15]).blocked));
P("scalar:u.uprops[15].intrinsic:%llu;", (unsigned long long)((((u).uprops)[15]).intrinsic));
P("scalar:u.uprops[16].extrinsic:%llu;", (unsigned long long)((((u).uprops)[16]).extrinsic));
P("scalar:u.uprops[16].blocked:%llu;", (unsigned long long)((((u).uprops)[16]).blocked));
P("scalar:u.uprops[16].intrinsic:%llu;", (unsigned long long)((((u).uprops)[16]).intrinsic));
P("scalar:u.uprops[17].extrinsic:%llu;", (unsigned long long)((((u).uprops)[17]).extrinsic));
P("scalar:u.uprops[17].blocked:%llu;", (unsigned long long)((((u).uprops)[17]).blocked));
P("scalar:u.uprops[17].intrinsic:%llu;", (unsigned long long)((((u).uprops)[17]).intrinsic));
P("scalar:u.uprops[18].extrinsic:%llu;", (unsigned long long)((((u).uprops)[18]).extrinsic));
P("scalar:u.uprops[18].blocked:%llu;", (unsigned long long)((((u).uprops)[18]).blocked));
P("scalar:u.uprops[18].intrinsic:%llu;", (unsigned long long)((((u).uprops)[18]).intrinsic));
P("scalar:u.uprops[19].extrinsic:%llu;", (unsigned long long)((((u).uprops)[19]).extrinsic));
P("scalar:u.uprops[19].blocked:%llu;", (unsigned long long)((((u).uprops)[19]).blocked));
P("scalar:u.uprops[19].intrinsic:%llu;", (unsigned long long)((((u).uprops)[19]).intrinsic));
P("scalar:u.uprops[20].extrinsic:%llu;", (unsigned long long)((((u).uprops)[20]).extrinsic));
P("scalar:u.uprops[20].blocked:%llu;", (unsigned long long)((((u).uprops)[20]).blocked));
P("scalar:u.uprops[20].intrinsic:%llu;", (unsigned long long)((((u).uprops)[20]).intrinsic));
P("scalar:u.uprops[21].extrinsic:%llu;", (unsigned long long)((((u).uprops)[21]).extrinsic));
P("scalar:u.uprops[21].blocked:%llu;", (unsigned long long)((((u).uprops)[21]).blocked));
P("scalar:u.uprops[21].intrinsic:%llu;", (unsigned long long)((((u).uprops)[21]).intrinsic));
P("scalar:u.uprops[22].extrinsic:%llu;", (unsigned long long)((((u).uprops)[22]).extrinsic));
P("scalar:u.uprops[22].blocked:%llu;", (unsigned long long)((((u).uprops)[22]).blocked));
P("scalar:u.uprops[22].intrinsic:%llu;", (unsigned long long)((((u).uprops)[22]).intrinsic));
P("scalar:u.uprops[23].extrinsic:%llu;", (unsigned long long)((((u).uprops)[23]).extrinsic));
P("scalar:u.uprops[23].blocked:%llu;", (unsigned long long)((((u).uprops)[23]).blocked));
P("scalar:u.uprops[23].intrinsic:%llu;", (unsigned long long)((((u).uprops)[23]).intrinsic));
P("scalar:u.uprops[24].extrinsic:%llu;", (unsigned long long)((((u).uprops)[24]).extrinsic));
P("scalar:u.uprops[24].blocked:%llu;", (unsigned long long)((((u).uprops)[24]).blocked));
P("scalar:u.uprops[24].intrinsic:%llu;", (unsigned long long)((((u).uprops)[24]).intrinsic));
P("scalar:u.uprops[25].extrinsic:%llu;", (unsigned long long)((((u).uprops)[25]).extrinsic));
P("scalar:u.uprops[25].blocked:%llu;", (unsigned long long)((((u).uprops)[25]).blocked));
P("scalar:u.uprops[25].intrinsic:%llu;", (unsigned long long)((((u).uprops)[25]).intrinsic));
P("scalar:u.uprops[26].extrinsic:%llu;", (unsigned long long)((((u).uprops)[26]).extrinsic));
P("scalar:u.uprops[26].blocked:%llu;", (unsigned long long)((((u).uprops)[26]).blocked));
P("scalar:u.uprops[26].intrinsic:%llu;", (unsigned long long)((((u).uprops)[26]).intrinsic));
P("scalar:u.uprops[27].extrinsic:%llu;", (unsigned long long)((((u).uprops)[27]).extrinsic));
P("scalar:u.uprops[27].blocked:%llu;", (unsigned long long)((((u).uprops)[27]).blocked));
P("scalar:u.uprops[27].intrinsic:%llu;", (unsigned long long)((((u).uprops)[27]).intrinsic));
P("scalar:u.uprops[28].extrinsic:%llu;", (unsigned long long)((((u).uprops)[28]).extrinsic));
P("scalar:u.uprops[28].blocked:%llu;", (unsigned long long)((((u).uprops)[28]).blocked));
P("scalar:u.uprops[28].intrinsic:%llu;", (unsigned long long)((((u).uprops)[28]).intrinsic));
P("scalar:u.uprops[29].extrinsic:%llu;", (unsigned long long)((((u).uprops)[29]).extrinsic));
P("scalar:u.uprops[29].blocked:%llu;", (unsigned long long)((((u).uprops)[29]).blocked));
P("scalar:u.uprops[29].intrinsic:%llu;", (unsigned long long)((((u).uprops)[29]).intrinsic));
P("scalar:u.uprops[30].extrinsic:%llu;", (unsigned long long)((((u).uprops)[30]).extrinsic));
P("scalar:u.uprops[30].blocked:%llu;", (unsigned long long)((((u).uprops)[30]).blocked));
P("scalar:u.uprops[30].intrinsic:%llu;", (unsigned long long)((((u).uprops)[30]).intrinsic));
P("scalar:u.uprops[31].extrinsic:%llu;", (unsigned long long)((((u).uprops)[31]).extrinsic));
P("scalar:u.uprops[31].blocked:%llu;", (unsigned long long)((((u).uprops)[31]).blocked));
P("scalar:u.uprops[31].intrinsic:%llu;", (unsigned long long)((((u).uprops)[31]).intrinsic));
P("scalar:u.uprops[32].extrinsic:%llu;", (unsigned long long)((((u).uprops)[32]).extrinsic));
P("scalar:u.uprops[32].blocked:%llu;", (unsigned long long)((((u).uprops)[32]).blocked));
P("scalar:u.uprops[32].intrinsic:%llu;", (unsigned long long)((((u).uprops)[32]).intrinsic));
P("scalar:u.uprops[33].extrinsic:%llu;", (unsigned long long)((((u).uprops)[33]).extrinsic));
P("scalar:u.uprops[33].blocked:%llu;", (unsigned long long)((((u).uprops)[33]).blocked));
P("scalar:u.uprops[33].intrinsic:%llu;", (unsigned long long)((((u).uprops)[33]).intrinsic));
P("scalar:u.uprops[34].extrinsic:%llu;", (unsigned long long)((((u).uprops)[34]).extrinsic));
P("scalar:u.uprops[34].blocked:%llu;", (unsigned long long)((((u).uprops)[34]).blocked));
P("scalar:u.uprops[34].intrinsic:%llu;", (unsigned long long)((((u).uprops)[34]).intrinsic));
P("scalar:u.uprops[35].extrinsic:%llu;", (unsigned long long)((((u).uprops)[35]).extrinsic));
P("scalar:u.uprops[35].blocked:%llu;", (unsigned long long)((((u).uprops)[35]).blocked));
P("scalar:u.uprops[35].intrinsic:%llu;", (unsigned long long)((((u).uprops)[35]).intrinsic));
P("scalar:u.uprops[36].extrinsic:%llu;", (unsigned long long)((((u).uprops)[36]).extrinsic));
P("scalar:u.uprops[36].blocked:%llu;", (unsigned long long)((((u).uprops)[36]).blocked));
P("scalar:u.uprops[36].intrinsic:%llu;", (unsigned long long)((((u).uprops)[36]).intrinsic));
P("scalar:u.uprops[37].extrinsic:%llu;", (unsigned long long)((((u).uprops)[37]).extrinsic));
P("scalar:u.uprops[37].blocked:%llu;", (unsigned long long)((((u).uprops)[37]).blocked));
P("scalar:u.uprops[37].intrinsic:%llu;", (unsigned long long)((((u).uprops)[37]).intrinsic));
P("scalar:u.uprops[38].extrinsic:%llu;", (unsigned long long)((((u).uprops)[38]).extrinsic));
P("scalar:u.uprops[38].blocked:%llu;", (unsigned long long)((((u).uprops)[38]).blocked));
P("scalar:u.uprops[38].intrinsic:%llu;", (unsigned long long)((((u).uprops)[38]).intrinsic));
P("scalar:u.uprops[39].extrinsic:%llu;", (unsigned long long)((((u).uprops)[39]).extrinsic));
P("scalar:u.uprops[39].blocked:%llu;", (unsigned long long)((((u).uprops)[39]).blocked));
P("scalar:u.uprops[39].intrinsic:%llu;", (unsigned long long)((((u).uprops)[39]).intrinsic));
P("scalar:u.uprops[40].extrinsic:%llu;", (unsigned long long)((((u).uprops)[40]).extrinsic));
P("scalar:u.uprops[40].blocked:%llu;", (unsigned long long)((((u).uprops)[40]).blocked));
P("scalar:u.uprops[40].intrinsic:%llu;", (unsigned long long)((((u).uprops)[40]).intrinsic));
P("scalar:u.uprops[41].extrinsic:%llu;", (unsigned long long)((((u).uprops)[41]).extrinsic));
P("scalar:u.uprops[41].blocked:%llu;", (unsigned long long)((((u).uprops)[41]).blocked));
P("scalar:u.uprops[41].intrinsic:%llu;", (unsigned long long)((((u).uprops)[41]).intrinsic));
P("scalar:u.uprops[42].extrinsic:%llu;", (unsigned long long)((((u).uprops)[42]).extrinsic));
P("scalar:u.uprops[42].blocked:%llu;", (unsigned long long)((((u).uprops)[42]).blocked));
P("scalar:u.uprops[42].intrinsic:%llu;", (unsigned long long)((((u).uprops)[42]).intrinsic));
P("scalar:u.uprops[43].extrinsic:%llu;", (unsigned long long)((((u).uprops)[43]).extrinsic));
P("scalar:u.uprops[43].blocked:%llu;", (unsigned long long)((((u).uprops)[43]).blocked));
P("scalar:u.uprops[43].intrinsic:%llu;", (unsigned long long)((((u).uprops)[43]).intrinsic));
P("scalar:u.uprops[44].extrinsic:%llu;", (unsigned long long)((((u).uprops)[44]).extrinsic));
P("scalar:u.uprops[44].blocked:%llu;", (unsigned long long)((((u).uprops)[44]).blocked));
P("scalar:u.uprops[44].intrinsic:%llu;", (unsigned long long)((((u).uprops)[44]).intrinsic));
P("scalar:u.uprops[45].extrinsic:%llu;", (unsigned long long)((((u).uprops)[45]).extrinsic));
P("scalar:u.uprops[45].blocked:%llu;", (unsigned long long)((((u).uprops)[45]).blocked));
P("scalar:u.uprops[45].intrinsic:%llu;", (unsigned long long)((((u).uprops)[45]).intrinsic));
P("scalar:u.uprops[46].extrinsic:%llu;", (unsigned long long)((((u).uprops)[46]).extrinsic));
P("scalar:u.uprops[46].blocked:%llu;", (unsigned long long)((((u).uprops)[46]).blocked));
P("scalar:u.uprops[46].intrinsic:%llu;", (unsigned long long)((((u).uprops)[46]).intrinsic));
P("scalar:u.uprops[47].extrinsic:%llu;", (unsigned long long)((((u).uprops)[47]).extrinsic));
P("scalar:u.uprops[47].blocked:%llu;", (unsigned long long)((((u).uprops)[47]).blocked));
P("scalar:u.uprops[47].intrinsic:%llu;", (unsigned long long)((((u).uprops)[47]).intrinsic));
P("scalar:u.uprops[48].extrinsic:%llu;", (unsigned long long)((((u).uprops)[48]).extrinsic));
P("scalar:u.uprops[48].blocked:%llu;", (unsigned long long)((((u).uprops)[48]).blocked));
P("scalar:u.uprops[48].intrinsic:%llu;", (unsigned long long)((((u).uprops)[48]).intrinsic));
P("scalar:u.uprops[49].extrinsic:%llu;", (unsigned long long)((((u).uprops)[49]).extrinsic));
P("scalar:u.uprops[49].blocked:%llu;", (unsigned long long)((((u).uprops)[49]).blocked));
P("scalar:u.uprops[49].intrinsic:%llu;", (unsigned long long)((((u).uprops)[49]).intrinsic));
P("scalar:u.uprops[50].extrinsic:%llu;", (unsigned long long)((((u).uprops)[50]).extrinsic));
P("scalar:u.uprops[50].blocked:%llu;", (unsigned long long)((((u).uprops)[50]).blocked));
P("scalar:u.uprops[50].intrinsic:%llu;", (unsigned long long)((((u).uprops)[50]).intrinsic));
P("scalar:u.uprops[51].extrinsic:%llu;", (unsigned long long)((((u).uprops)[51]).extrinsic));
P("scalar:u.uprops[51].blocked:%llu;", (unsigned long long)((((u).uprops)[51]).blocked));
P("scalar:u.uprops[51].intrinsic:%llu;", (unsigned long long)((((u).uprops)[51]).intrinsic));
P("scalar:u.uprops[52].extrinsic:%llu;", (unsigned long long)((((u).uprops)[52]).extrinsic));
P("scalar:u.uprops[52].blocked:%llu;", (unsigned long long)((((u).uprops)[52]).blocked));
P("scalar:u.uprops[52].intrinsic:%llu;", (unsigned long long)((((u).uprops)[52]).intrinsic));
P("scalar:u.uprops[53].extrinsic:%llu;", (unsigned long long)((((u).uprops)[53]).extrinsic));
P("scalar:u.uprops[53].blocked:%llu;", (unsigned long long)((((u).uprops)[53]).blocked));
P("scalar:u.uprops[53].intrinsic:%llu;", (unsigned long long)((((u).uprops)[53]).intrinsic));
P("scalar:u.uprops[54].extrinsic:%llu;", (unsigned long long)((((u).uprops)[54]).extrinsic));
P("scalar:u.uprops[54].blocked:%llu;", (unsigned long long)((((u).uprops)[54]).blocked));
P("scalar:u.uprops[54].intrinsic:%llu;", (unsigned long long)((((u).uprops)[54]).intrinsic));
P("scalar:u.uprops[55].extrinsic:%llu;", (unsigned long long)((((u).uprops)[55]).extrinsic));
P("scalar:u.uprops[55].blocked:%llu;", (unsigned long long)((((u).uprops)[55]).blocked));
P("scalar:u.uprops[55].intrinsic:%llu;", (unsigned long long)((((u).uprops)[55]).intrinsic));
P("scalar:u.uprops[56].extrinsic:%llu;", (unsigned long long)((((u).uprops)[56]).extrinsic));
P("scalar:u.uprops[56].blocked:%llu;", (unsigned long long)((((u).uprops)[56]).blocked));
P("scalar:u.uprops[56].intrinsic:%llu;", (unsigned long long)((((u).uprops)[56]).intrinsic));
P("scalar:u.uprops[57].extrinsic:%llu;", (unsigned long long)((((u).uprops)[57]).extrinsic));
P("scalar:u.uprops[57].blocked:%llu;", (unsigned long long)((((u).uprops)[57]).blocked));
P("scalar:u.uprops[57].intrinsic:%llu;", (unsigned long long)((((u).uprops)[57]).intrinsic));
P("scalar:u.uprops[58].extrinsic:%llu;", (unsigned long long)((((u).uprops)[58]).extrinsic));
P("scalar:u.uprops[58].blocked:%llu;", (unsigned long long)((((u).uprops)[58]).blocked));
P("scalar:u.uprops[58].intrinsic:%llu;", (unsigned long long)((((u).uprops)[58]).intrinsic));
P("scalar:u.uprops[59].extrinsic:%llu;", (unsigned long long)((((u).uprops)[59]).extrinsic));
P("scalar:u.uprops[59].blocked:%llu;", (unsigned long long)((((u).uprops)[59]).blocked));
P("scalar:u.uprops[59].intrinsic:%llu;", (unsigned long long)((((u).uprops)[59]).intrinsic));
P("scalar:u.uprops[60].extrinsic:%llu;", (unsigned long long)((((u).uprops)[60]).extrinsic));
P("scalar:u.uprops[60].blocked:%llu;", (unsigned long long)((((u).uprops)[60]).blocked));
P("scalar:u.uprops[60].intrinsic:%llu;", (unsigned long long)((((u).uprops)[60]).intrinsic));
P("scalar:u.uprops[61].extrinsic:%llu;", (unsigned long long)((((u).uprops)[61]).extrinsic));
P("scalar:u.uprops[61].blocked:%llu;", (unsigned long long)((((u).uprops)[61]).blocked));
P("scalar:u.uprops[61].intrinsic:%llu;", (unsigned long long)((((u).uprops)[61]).intrinsic));
P("scalar:u.uprops[62].extrinsic:%llu;", (unsigned long long)((((u).uprops)[62]).extrinsic));
P("scalar:u.uprops[62].blocked:%llu;", (unsigned long long)((((u).uprops)[62]).blocked));
P("scalar:u.uprops[62].intrinsic:%llu;", (unsigned long long)((((u).uprops)[62]).intrinsic));
P("scalar:u.uprops[63].extrinsic:%llu;", (unsigned long long)((((u).uprops)[63]).extrinsic));
P("scalar:u.uprops[63].blocked:%llu;", (unsigned long long)((((u).uprops)[63]).blocked));
P("scalar:u.uprops[63].intrinsic:%llu;", (unsigned long long)((((u).uprops)[63]).intrinsic));
P("scalar:u.uprops[64].extrinsic:%llu;", (unsigned long long)((((u).uprops)[64]).extrinsic));
P("scalar:u.uprops[64].blocked:%llu;", (unsigned long long)((((u).uprops)[64]).blocked));
P("scalar:u.uprops[64].intrinsic:%llu;", (unsigned long long)((((u).uprops)[64]).intrinsic));
P("scalar:u.uprops[65].extrinsic:%llu;", (unsigned long long)((((u).uprops)[65]).extrinsic));
P("scalar:u.uprops[65].blocked:%llu;", (unsigned long long)((((u).uprops)[65]).blocked));
P("scalar:u.uprops[65].intrinsic:%llu;", (unsigned long long)((((u).uprops)[65]).intrinsic));
P("scalar:u.uprops[66].extrinsic:%llu;", (unsigned long long)((((u).uprops)[66]).extrinsic));
P("scalar:u.uprops[66].blocked:%llu;", (unsigned long long)((((u).uprops)[66]).blocked));
P("scalar:u.uprops[66].intrinsic:%llu;", (unsigned long long)((((u).uprops)[66]).intrinsic));
P("scalar:u.uprops[67].extrinsic:%llu;", (unsigned long long)((((u).uprops)[67]).extrinsic));
P("scalar:u.uprops[67].blocked:%llu;", (unsigned long long)((((u).uprops)[67]).blocked));
P("scalar:u.uprops[67].intrinsic:%llu;", (unsigned long long)((((u).uprops)[67]).intrinsic));
P("scalar:u.uprops[68].extrinsic:%llu;", (unsigned long long)((((u).uprops)[68]).extrinsic));
P("scalar:u.uprops[68].blocked:%llu;", (unsigned long long)((((u).uprops)[68]).blocked));
P("scalar:u.uprops[68].intrinsic:%llu;", (unsigned long long)((((u).uprops)[68]).intrinsic));
P("scalar:u.umonster:%llu;", (unsigned long long)((u).umonster));
P("scalar:u.umonnum:%llu;", (unsigned long long)((u).umonnum));
P("scalar:u.uswallow:%llu;", (unsigned long long)((u).uswallow));
P("scalar:u.uinwater:%llu;", (unsigned long long)((u).uinwater));
P("scalar:u.uhandedness:%llu;", (unsigned long long)((u).uhandedness));
P("scalar:u.uroleplay.blind:%llu;", (unsigned long long)(((u).uroleplay).blind));
P("scalar:u.acurr.a[0]:%llu;", (unsigned long long)((((u).acurr).a)[0]));
P("scalar:u.acurr.a[1]:%llu;", (unsigned long long)((((u).acurr).a)[1]));
P("scalar:u.acurr.a[2]:%llu;", (unsigned long long)((((u).acurr).a)[2]));
P("scalar:u.acurr.a[3]:%llu;", (unsigned long long)((((u).acurr).a)[3]));
P("scalar:u.acurr.a[4]:%llu;", (unsigned long long)((((u).acurr).a)[4]));
P("scalar:u.acurr.a[5]:%llu;", (unsigned long long)((((u).acurr).a)[5]));
P("scalar:u.abon.a[0]:%llu;", (unsigned long long)((((u).abon).a)[0]));
P("scalar:u.abon.a[1]:%llu;", (unsigned long long)((((u).abon).a)[1]));
P("scalar:u.abon.a[2]:%llu;", (unsigned long long)((((u).abon).a)[2]));
P("scalar:u.abon.a[3]:%llu;", (unsigned long long)((((u).abon).a)[3]));
P("scalar:u.abon.a[4]:%llu;", (unsigned long long)((((u).abon).a)[4]));
P("scalar:u.abon.a[5]:%llu;", (unsigned long long)((((u).abon).a)[5]));
P("scalar:u.atemp.a[0]:%llu;", (unsigned long long)((((u).atemp).a)[0]));
P("scalar:u.atemp.a[1]:%llu;", (unsigned long long)((((u).atemp).a)[1]));
P("scalar:u.atemp.a[2]:%llu;", (unsigned long long)((((u).atemp).a)[2]));
P("scalar:u.atemp.a[3]:%llu;", (unsigned long long)((((u).atemp).a)[3]));
P("scalar:u.atemp.a[4]:%llu;", (unsigned long long)((((u).atemp).a)[4]));
P("scalar:u.atemp.a[5]:%llu;", (unsigned long long)((((u).atemp).a)[5]));
P("scalar:u.ualign.type:%llu;", (unsigned long long)(((u).ualign).type));
P("scalar:u.ualignbase[0]:%llu;", (unsigned long long)(((u).ualignbase)[0]));
P("scalar:u.ualignbase[1]:%llu;", (unsigned long long)(((u).ualignbase)[1]));
P("scalar:u.uhitinc:%llu;", (unsigned long long)((u).uhitinc));
P("scalar:u.udaminc:%llu;", (unsigned long long)((u).udaminc));
P("scalar:u.uac:%llu;", (unsigned long long)((u).uac));
P("scalar:u.uspellprot:%llu;", (unsigned long long)((u).uspellprot));
P("scalar:u.ublessed:%llu;", (unsigned long long)((u).ublessed));
P("scalar:u.twoweap:%llu;", (unsigned long long)((u).twoweap));
P("scalar:disp.botl:%llu;", (unsigned long long)((disp).botl));
P("scalar:gi.initial_don:%llu;", (unsigned long long)((gi).initial_don));
P("scalar:gi.item_action_in_progress:%llu;", (unsigned long long)((gi).item_action_in_progress));
P("scalar:gm.multi:%llu;", (unsigned long long)((gm).multi));
P("scalar:gu.urole.mnum:%llu;", (unsigned long long)(((gu).urole).mnum));
P("scalar:gw.wasinwater:%llu;", (unsigned long long)((gw).wasinwater));
P("scalar:svc.context.mon_moving:%llu;", (unsigned long long)(((svc).context).mon_moving));
P("scalar:svc.context.takeoff.mask:%llu;", (unsigned long long)((((svc).context).takeoff).mask));
P("scalar:svc.context.takeoff.what:%llu;", (unsigned long long)((((svc).context).takeoff).what));
P("scalar:svc.context.takeoff.delay:%llu;", (unsigned long long)((((svc).context).takeoff).delay));
P("scalar:svc.context.takeoff.cancelled_don:%llu;", (unsigned long long)((((svc).context).takeoff).cancelled_don));
P("scalar:svc.context.takeoff.disrobing[0]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[0]));
P("scalar:svc.context.takeoff.disrobing[1]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[1]));
P("scalar:svc.context.takeoff.disrobing[2]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[2]));
P("scalar:svc.context.takeoff.disrobing[3]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[3]));
P("scalar:svc.context.takeoff.disrobing[4]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[4]));
P("scalar:svc.context.takeoff.disrobing[5]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[5]));
P("scalar:svc.context.takeoff.disrobing[6]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[6]));
P("scalar:svc.context.takeoff.disrobing[7]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[7]));
P("scalar:svc.context.takeoff.disrobing[8]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[8]));
P("scalar:svc.context.takeoff.disrobing[9]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[9]));
P("scalar:svc.context.takeoff.disrobing[10]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[10]));
P("scalar:svc.context.takeoff.disrobing[11]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[11]));
P("scalar:svc.context.takeoff.disrobing[12]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[12]));
P("scalar:svc.context.takeoff.disrobing[13]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[13]));
P("scalar:svc.context.takeoff.disrobing[14]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[14]));
P("scalar:svc.context.takeoff.disrobing[15]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[15]));
P("scalar:svc.context.takeoff.disrobing[16]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[16]));
P("scalar:svc.context.takeoff.disrobing[17]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[17]));
P("scalar:svc.context.takeoff.disrobing[18]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[18]));
P("scalar:svc.context.takeoff.disrobing[19]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[19]));
P("scalar:svc.context.takeoff.disrobing[20]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[20]));
P("scalar:svc.context.takeoff.disrobing[21]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[21]));
P("scalar:svc.context.takeoff.disrobing[22]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[22]));
P("scalar:svc.context.takeoff.disrobing[23]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[23]));
P("scalar:svc.context.takeoff.disrobing[24]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[24]));
P("scalar:svc.context.takeoff.disrobing[25]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[25]));
P("scalar:svc.context.takeoff.disrobing[26]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[26]));
P("scalar:svc.context.takeoff.disrobing[27]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[27]));
P("scalar:svc.context.takeoff.disrobing[28]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[28]));
P("scalar:svc.context.takeoff.disrobing[29]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[29]));
P("scalar:svc.context.takeoff.disrobing[30]:%llu;", (unsigned long long)(((((svc).context).takeoff).disrobing)[30]));
P("scalar:svd.dungeon_topology.d_water_level.dnum:%llu;", (unsigned long long)((((svd).dungeon_topology).d_water_level).dnum));
P("scalar:svd.dungeon_topology.d_water_level.dlevel:%llu;", (unsigned long long)((((svd).dungeon_topology).d_water_level).dlevel));
P("scalar:svd.dungeon_topology.d_air_level.dnum:%llu;", (unsigned long long)((((svd).dungeon_topology).d_air_level).dnum));
P("scalar:svd.dungeon_topology.d_air_level.dlevel:%llu;", (unsigned long long)((((svd).dungeon_topology).d_air_level).dlevel));
P("scalar:svd.dungeon_topology.d_qstart_level.dnum:%llu;", (unsigned long long)((((svd).dungeon_topology).d_qstart_level).dnum));
P("scalar:svd.dungeon_topology.d_qstart_level.dlevel:%llu;", (unsigned long long)((((svd).dungeon_topology).d_qstart_level).dlevel));
P("scalar:program_state.restoring:%llu;", (unsigned long long)((program_state).restoring));
for(int raw_i=0;raw_i<32;raw_i++)if(pool[raw_i]){
P("scalar:object.o_id:%llu;", (unsigned long long)(pool[raw_i]->o_id));
P("scalar:object.otyp:%llu;", (unsigned long long)(pool[raw_i]->otyp));
P("scalar:object.quan:%llu;", (unsigned long long)(pool[raw_i]->quan));
P("scalar:object.spe:%llu;", (unsigned long long)(pool[raw_i]->spe));
P("scalar:object.oclass:%llu;", (unsigned long long)(pool[raw_i]->oclass));
P("scalar:object.cursed:%llu;", (unsigned long long)(pool[raw_i]->cursed));
P("scalar:object.unpaid:%llu;", (unsigned long long)(pool[raw_i]->unpaid));
P("scalar:object.lamplit:%llu;", (unsigned long long)(pool[raw_i]->lamplit));
P("scalar:object.known:%llu;", (unsigned long long)(pool[raw_i]->known));
P("scalar:object.dknown:%llu;", (unsigned long long)(pool[raw_i]->dknown));
P("scalar:object.bknown:%llu;", (unsigned long long)(pool[raw_i]->bknown));
P("scalar:object.oeroded:%llu;", (unsigned long long)(pool[raw_i]->oeroded));
P("scalar:object.oeroded2:%llu;", (unsigned long long)(pool[raw_i]->oeroded2));
P("scalar:object.oerodeproof:%llu;", (unsigned long long)(pool[raw_i]->oerodeproof));
P("scalar:object.in_use:%llu;", (unsigned long long)(pool[raw_i]->in_use));
P("scalar:object.corpsenm:%llu;", (unsigned long long)(pool[raw_i]->corpsenm));
P("scalar:object.owornmask:%llu;", (unsigned long long)(pool[raw_i]->owornmask));
}
#undef P
return snapshot;}
int do_reqmenu(void){append("do_reqmenu;");return ECMD_OK;}

void teleport_probe_free(void*p){policy_frees++;if(p&&p==last_menu){menu_frees++;last_menu=0;append("free:menu;");}else if(p&&p==last_command){command_frees++;last_command=0;append("free:command;");}else append("free:%s;",p?"other":"null");free(p);}
long probe_macro(int i){switch(i){case 0:return Blind_telepat;case 1:return Fast;case 2:return Very_fast;case 3:return Breathless;case 4:return Levitation;case 5:return Flying;case 6:return Swimming;case 7:return Invis;case 8:return Invisible;case 9:return Unchanging;case 10:return Blind;case 11:return Unblind_telepat;default:abort();}}
long probe_table(int i){
#ifdef TELEPORT_REFERENCE_TU
 return takeoff_order[i];
#else
 (void)i;return 0;
#endif
}

void probe_set_monster(int i,int pm){monsters[i].data=&mons[pm];}

unsigned probe_stack_span(void){return(unsigned)(stack_max-stack_min); }
