/* Controlled DO world dependencies. Drop, floor, level, revival and wounded-leg
 * policy is the unchanged original C oracle or its original-boundary JS port. */
#include "hack.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <emscripten/stack.h>
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/do.c"
#else
extern void teleport_do_test_dosinkring(struct obj*);
#define dosinkring teleport_do_test_dosinkring
extern boolean teleport_do_test_teleport_sink(void);
#define teleport_sink teleport_do_test_teleport_sink
extern int teleport_do_test_drop(struct obj *);
#define drop teleport_do_test_drop
extern boolean teleport_do_test_engulfer_digests_food(struct obj *);
#define engulfer_digests_food teleport_do_test_engulfer_digests_food
extern boolean teleport_do_test_better_not_try_to_drop_that(struct obj *);
#define better_not_try_to_drop_that teleport_do_test_better_not_try_to_drop_that
extern int teleport_do_test_menudrop_split(struct obj *,long);
#define menudrop_split teleport_do_test_menudrop_split
extern int teleport_do_test_menu_drop(int);
#define menu_drop teleport_do_test_menu_drop
extern boolean teleport_do_test_u_stuck_cannot_go(const char *);
#define u_stuck_cannot_go teleport_do_test_u_stuck_cannot_go
extern NHFILE * teleport_do_test_currentlevel_rewrite(void);
#define currentlevel_rewrite teleport_do_test_currentlevel_rewrite
extern void teleport_do_test_familiar_level_msg(void);
#define familiar_level_msg teleport_do_test_familiar_level_msg
extern void teleport_do_test_temperature_change_msg(schar);
#define temperature_change_msg teleport_do_test_temperature_change_msg
extern void teleport_do_test_final_level(void);
#define final_level teleport_do_test_final_level
extern boolean teleport_do_test_danger_uprops(void);
#define danger_uprops teleport_do_test_danger_uprops
extern int teleport_do_test_wipeoff(void);
#define wipeoff teleport_do_test_wipeoff
#endif
#include "tu-do-layout.h"
__typeof__(flags) flags;
__typeof__(iflags) iflags;
__typeof__(a11y) a11y;
__typeof__(windowprocs) windowprocs;
__typeof__(uwep) uwep;
__typeof__(uswapwep) uswapwep;
__typeof__(uquiver) uquiver;
__typeof__(uchain) uchain;
__typeof__(uball) uball;
__typeof__(u) u;
__typeof__(disp) disp;
__typeof__(ga) ga;
__typeof__(gb) gb;
__typeof__(gd) gd;
__typeof__(gf) gf;
__typeof__(gi) gi;
__typeof__(gl) gl;
__typeof__(gm) gm;
__typeof__(gu) gu;
__typeof__(gv) gv;
__typeof__(gy) gy;
__typeof__(svc) svc;
__typeof__(svd) svd;
__typeof__(svh) svh;
__typeof__(svl) svl;
__typeof__(svm) svm;
__typeof__(svn) svn;
__typeof__(svp) svp;
__typeof__(svq) svq;
__typeof__(svu) svu;
__typeof__(program_state) program_state;
const struct c_color_names c_color_names={.c_black="black",.c_amber="amber",.c_silver="silver",.c_white="white"};
const struct c_common_strings c_common_strings={.c_something="something",.c_Something="Something",.c_the_your={"the","your"}};
const char ynchars[]="yn";const char*const nhcb_name[4]={"none","start","level","turn"};int nhcb_counts[4];
static struct obj *pool[32];static struct monst monsters[8];static struct trap traps[4];static seenV vision[ROWNO][COLNO];static seenV*visionrows[ROWNO];static NHFILE file;
static char traces[4194304],snapshot[262144],names[64][BUFSZ];static int ti,ni,rolls[8192],nr,ri,frees;static unsigned seed;static int opts[512],configured[512],growth_stage,reenter_stage;static void*grown;static const char*callerfile,*callerfn;static int callerline;
static int(*occupation)(void);static uintptr_t observed_stack_min,observed_stack_max;
static void append(const char*f,...) __attribute__((format(printf,1,2)));
static void append(const char*f,...){va_list ap;va_start(ap,f);int n=vsnprintf(traces+ti,sizeof traces-ti,f,ap);va_end(ap);if(n<0||ti+n>=sizeof traces)abort();ti+=n;}
static int oid(struct obj*o){if(!o)return-1;for(int i=0;i<32;i++)if(pool[i]==o)return i;return-99;}
static int mid(struct monst*m){if(!m)return-1;if(m==&gy.youmonst)return-2;for(int i=0;i<8;i++)if(m==monsters+i)return i;return-99;}
static const char*nullable(const char*s){return s?s:"(null)";}
static void callback(int stage){if(opts[507]==stage+1){uintptr_t sp=emscripten_stack_get_current();if(!observed_stack_min)observed_stack_min=observed_stack_max=sp;else{if(sp<observed_stack_min)observed_stack_min=sp;if(sp>observed_stack_max)observed_stack_max=sp;}}if(stage==growth_stage){growth_stage=0;grown=malloc(48*1024*1024);if(!grown)abort();append("growth:%d;",stage);}if(stage==reenter_stage){reenter_stage=0;append("reentry:%d;",danger_uprops());}}
static char*namebuf(const char*s){char*b=names[ni++%64];snprintf(b,BUFSZ,"%s",s?s:"(null)");return b;}
static void message(const char*tag,const char*f,va_list ap){char b[4096];vsnprintf(b,sizeof b,f,ap);append("%s:%s;",tag,b);}
static const char*dep_names[]={"Adjmonnam","Amonnam","Can_fall_thru","Doname2","In_W_tower","In_hell","In_mines","In_quest","Monnam","Norep","On_W_tower_level","The","There","Tobjnam","You","You_cant","You_feel","You_hear","You_see","Your","add_to_buried","add_valid_menu_class","allow_all","allow_category","an","any_obj_ok","artifact_has_invprop","assign_graphics","assign_level","assign_rnd_level","at_dgn_entrance","ballfall","ballrelease","body_part","bones_include_name","breakobj","bufon","builds_up","buried_ball_to_punishment","burn_away_slime","bury_objs","bypass_objlist","can_reach_floor","canseemon","canspotmon","check_gold_symbol","check_special_room","clamp_hole_destination","climb_pit","close_nhfile","cmd_from_func","com_pager","container_impact_dmg","corpse_xname","costly_alteration","count_justpicked","create_levelfile","create_mplayers","d","delete_levelfile","delfloortrap","deliver_splev_message","delobj","deltrap","depth","describe_level","discard_migrations","dismount_steed","dmgtype","dmgtype_fromattack","dmgval","do_reqmenu","docall","docrt","doname","done","dotrap","drag_down","drop_ball","dunlev","dunlevs_in_dungeon","dupstr","encumber_msg","enexto","engr_at","error","fill_pit","find_justpicked","finesse_ahriman","fix_shop_damage","float_down","floating_above","free_luathemes","free_omid","free_omonst","freeinv","fruitname","fumaroles","gain_guardian_angel","get_container_location","get_obj_location","getlev","getobj","ggetobj","glyph_to_cmap","goto_hell","grow_up","gulp_blnd_check","hcolor","healmon","hitfloor","hliquid","hmon","impact_disturbs_zombies","impact_drop","impossible","in_out_region","incr_itimeout","is_lava","is_pool","is_pool_or_lava","is_unpaid","isok","iter_mons","keepdogs","kill_genocided_monsters","lava_damage","ledger_no","ledger_to_dnum","level_difficulty","livelog_printf","locomotion","losedogs","losehp","lua_getglobal","lua_pushstring","lua_settop","m_in_air","m_into_limbo","make_blinded","make_grave","makeplural","maketrap","map_background","map_object","maxledgerno","maybe_reset_pick","mbodypart","mcureblindness","minstapetrify","mklev","mnexto","mon_nam","mondied","monster_nearby","more_experienced","movebubbles","mpickobj","near_capacity","newcham","newexplevel","newsym","next_level","next_to_u","nhl_pcall_handle","nomul","notice_all_mons","nxt_unbypassed_obj","obfree","obj_delivery","obj_extract_self","obj_has_timer","obj_meld","obj_nexto_xy","obj_pmname","obj_resists","oinit","ok_to_quest","olfaction","on_level","onquest","open_levelfile","otense","panic","paranoid_ynq","pickup","place_object","placebc","pline","pline_The","pm_to_cham","pooleffects","prev_level","print_level_annotation","pudding_merge_message","query_category","query_objlist","recalc_block_point","recalc_mapseen","recbranch_mapseen","record_achievement","reglyph_darkroom","remdun_mapseen","reseed_random","reset_glyphmap","reset_hostility","reset_occupations","reset_trapset","reset_utrap","resurrect","revive","rider_revival_time","rloc","rn2","rn2_on_display_rng","rnd","rndmonnam","rng_log_enabled","rng_log_set_caller","rnz","rot_corpse","run_timers","safe_teleds","savelev","savestateinlock","seetrap","selftouch","sellobj","sellobj_state","sensemon","set_bknown","set_corpsenm","set_itimeout","set_levltyp","set_move_cmd","set_occupation","set_uinwater","set_ustuck","setuqwep","setuswapwep","setuwep","ship_object","splitobj","stackobj","stairway_at","stairway_find_from","stairway_free_all","start_timer","sticks","stolen_value","strchr","stucksteed","surface","t_at","the","tricked_fileremoved","tutorial","u_locomotion","u_on_dnstairs","u_on_newpos","u_on_rndspot","u_on_sstairs","u_on_upstairs","u_rooted","u_safe_from_fatal_corpse","uescaped_shaft","undiscovered_artifact","unplacebc","update_mlstmv","use_pick_axe2","useup","useupf","uteetering_at_seen_pit","vision_recalc","vision_reset","vtense","wake_nearto","water_damage","waterbody_name","weight","welded","weldmsg","xname","y_monnam","yn_function","yname","yobjnam","zombie_form"};
enum{DEP_Adjmonnam=0,DEP_Amonnam=1,DEP_Can_fall_thru=2,DEP_Doname2=3,DEP_In_W_tower=4,DEP_In_hell=5,DEP_In_mines=6,DEP_In_quest=7,DEP_Monnam=8,DEP_Norep=9,DEP_On_W_tower_level=10,DEP_The=11,DEP_There=12,DEP_Tobjnam=13,DEP_You=14,DEP_You_cant=15,DEP_You_feel=16,DEP_You_hear=17,DEP_You_see=18,DEP_Your=19,DEP_add_to_buried=20,DEP_add_valid_menu_class=21,DEP_allow_all=22,DEP_allow_category=23,DEP_an=24,DEP_any_obj_ok=25,DEP_artifact_has_invprop=26,DEP_assign_graphics=27,DEP_assign_level=28,DEP_assign_rnd_level=29,DEP_at_dgn_entrance=30,DEP_ballfall=31,DEP_ballrelease=32,DEP_body_part=33,DEP_bones_include_name=34,DEP_breakobj=35,DEP_bufon=36,DEP_builds_up=37,DEP_buried_ball_to_punishment=38,DEP_burn_away_slime=39,DEP_bury_objs=40,DEP_bypass_objlist=41,DEP_can_reach_floor=42,DEP_canseemon=43,DEP_canspotmon=44,DEP_check_gold_symbol=45,DEP_check_special_room=46,DEP_clamp_hole_destination=47,DEP_climb_pit=48,DEP_close_nhfile=49,DEP_cmd_from_func=50,DEP_com_pager=51,DEP_container_impact_dmg=52,DEP_corpse_xname=53,DEP_costly_alteration=54,DEP_count_justpicked=55,DEP_create_levelfile=56,DEP_create_mplayers=57,DEP_d=58,DEP_delete_levelfile=59,DEP_delfloortrap=60,DEP_deliver_splev_message=61,DEP_delobj=62,DEP_deltrap=63,DEP_depth=64,DEP_describe_level=65,DEP_discard_migrations=66,DEP_dismount_steed=67,DEP_dmgtype=68,DEP_dmgtype_fromattack=69,DEP_dmgval=70,DEP_do_reqmenu=71,DEP_docall=72,DEP_docrt=73,DEP_doname=74,DEP_done=75,DEP_dotrap=76,DEP_drag_down=77,DEP_drop_ball=78,DEP_dunlev=79,DEP_dunlevs_in_dungeon=80,DEP_dupstr=81,DEP_encumber_msg=82,DEP_enexto=83,DEP_engr_at=84,DEP_error=85,DEP_fill_pit=86,DEP_find_justpicked=87,DEP_finesse_ahriman=88,DEP_fix_shop_damage=89,DEP_float_down=90,DEP_floating_above=91,DEP_free_luathemes=92,DEP_free_omid=93,DEP_free_omonst=94,DEP_freeinv=95,DEP_fruitname=96,DEP_fumaroles=97,DEP_gain_guardian_angel=98,DEP_get_container_location=99,DEP_get_obj_location=100,DEP_getlev=101,DEP_getobj=102,DEP_ggetobj=103,DEP_glyph_to_cmap=104,DEP_goto_hell=105,DEP_grow_up=106,DEP_gulp_blnd_check=107,DEP_hcolor=108,DEP_healmon=109,DEP_hitfloor=110,DEP_hliquid=111,DEP_hmon=112,DEP_impact_disturbs_zombies=113,DEP_impact_drop=114,DEP_impossible=115,DEP_in_out_region=116,DEP_incr_itimeout=117,DEP_is_lava=118,DEP_is_pool=119,DEP_is_pool_or_lava=120,DEP_is_unpaid=121,DEP_isok=122,DEP_iter_mons=123,DEP_keepdogs=124,DEP_kill_genocided_monsters=125,DEP_lava_damage=126,DEP_ledger_no=127,DEP_ledger_to_dnum=128,DEP_level_difficulty=129,DEP_livelog_printf=130,DEP_locomotion=131,DEP_losedogs=132,DEP_losehp=133,DEP_lua_getglobal=134,DEP_lua_pushstring=135,DEP_lua_settop=136,DEP_m_in_air=137,DEP_m_into_limbo=138,DEP_make_blinded=139,DEP_make_grave=140,DEP_makeplural=141,DEP_maketrap=142,DEP_map_background=143,DEP_map_object=144,DEP_maxledgerno=145,DEP_maybe_reset_pick=146,DEP_mbodypart=147,DEP_mcureblindness=148,DEP_minstapetrify=149,DEP_mklev=150,DEP_mnexto=151,DEP_mon_nam=152,DEP_mondied=153,DEP_monster_nearby=154,DEP_more_experienced=155,DEP_movebubbles=156,DEP_mpickobj=157,DEP_near_capacity=158,DEP_newcham=159,DEP_newexplevel=160,DEP_newsym=161,DEP_next_level=162,DEP_next_to_u=163,DEP_nhl_pcall_handle=164,DEP_nomul=165,DEP_notice_all_mons=166,DEP_nxt_unbypassed_obj=167,DEP_obfree=168,DEP_obj_delivery=169,DEP_obj_extract_self=170,DEP_obj_has_timer=171,DEP_obj_meld=172,DEP_obj_nexto_xy=173,DEP_obj_pmname=174,DEP_obj_resists=175,DEP_oinit=176,DEP_ok_to_quest=177,DEP_olfaction=178,DEP_on_level=179,DEP_onquest=180,DEP_open_levelfile=181,DEP_otense=182,DEP_panic=183,DEP_paranoid_ynq=184,DEP_pickup=185,DEP_place_object=186,DEP_placebc=187,DEP_pline=188,DEP_pline_The=189,DEP_pm_to_cham=190,DEP_pooleffects=191,DEP_prev_level=192,DEP_print_level_annotation=193,DEP_pudding_merge_message=194,DEP_query_category=195,DEP_query_objlist=196,DEP_recalc_block_point=197,DEP_recalc_mapseen=198,DEP_recbranch_mapseen=199,DEP_record_achievement=200,DEP_reglyph_darkroom=201,DEP_remdun_mapseen=202,DEP_reseed_random=203,DEP_reset_glyphmap=204,DEP_reset_hostility=205,DEP_reset_occupations=206,DEP_reset_trapset=207,DEP_reset_utrap=208,DEP_resurrect=209,DEP_revive=210,DEP_rider_revival_time=211,DEP_rloc=212,DEP_rn2=213,DEP_rn2_on_display_rng=214,DEP_rnd=215,DEP_rndmonnam=216,DEP_rng_log_enabled=217,DEP_rng_log_set_caller=218,DEP_rnz=219,DEP_rot_corpse=220,DEP_run_timers=221,DEP_safe_teleds=222,DEP_savelev=223,DEP_savestateinlock=224,DEP_seetrap=225,DEP_selftouch=226,DEP_sellobj=227,DEP_sellobj_state=228,DEP_sensemon=229,DEP_set_bknown=230,DEP_set_corpsenm=231,DEP_set_itimeout=232,DEP_set_levltyp=233,DEP_set_move_cmd=234,DEP_set_occupation=235,DEP_set_uinwater=236,DEP_set_ustuck=237,DEP_setuqwep=238,DEP_setuswapwep=239,DEP_setuwep=240,DEP_ship_object=241,DEP_splitobj=242,DEP_stackobj=243,DEP_stairway_at=244,DEP_stairway_find_from=245,DEP_stairway_free_all=246,DEP_start_timer=247,DEP_sticks=248,DEP_stolen_value=249,DEP_strchr=250,DEP_stucksteed=251,DEP_surface=252,DEP_t_at=253,DEP_the=254,DEP_tricked_fileremoved=255,DEP_tutorial=256,DEP_u_locomotion=257,DEP_u_on_dnstairs=258,DEP_u_on_newpos=259,DEP_u_on_rndspot=260,DEP_u_on_sstairs=261,DEP_u_on_upstairs=262,DEP_u_rooted=263,DEP_u_safe_from_fatal_corpse=264,DEP_uescaped_shaft=265,DEP_undiscovered_artifact=266,DEP_unplacebc=267,DEP_update_mlstmv=268,DEP_use_pick_axe2=269,DEP_useup=270,DEP_useupf=271,DEP_uteetering_at_seen_pit=272,DEP_vision_recalc=273,DEP_vision_reset=274,DEP_vtense=275,DEP_wake_nearto=276,DEP_water_damage=277,DEP_waterbody_name=278,DEP_weight=279,DEP_welded=280,DEP_weldmsg=281,DEP_xname=282,DEP_y_monnam=283,DEP_yn_function=284,DEP_yname=285,DEP_yobjnam=286,DEP_zombie_form=287};
char * Adjmonnam(struct monst * a0,const char * a1){append("Adjmonnam:%d:%s;",mid(a0),nullable(a1));callback(DEP_Adjmonnam);return namebuf("value");}
char * Amonnam(struct monst * a0){append("Amonnam:%d;",mid(a0));callback(DEP_Amonnam);return namebuf("value");}
boolean Can_fall_thru(d_level * a0){append("Can_fall_thru:ptr;");callback(DEP_Can_fall_thru);return configured[DEP_Can_fall_thru]?opts[DEP_Can_fall_thru]:0;}
char * Doname2(struct obj * a0){append("Doname2:%d;",oid(a0));callback(DEP_Doname2);return namebuf("value");}
boolean In_W_tower(coordxy a0,coordxy a1,d_level * a2){append("In_W_tower:%ld:%ld:ptr;",(long)a0,(long)a1);callback(DEP_In_W_tower);return configured[DEP_In_W_tower]?opts[DEP_In_W_tower]:0;}
boolean In_hell(d_level * a0){append("In_hell:ptr;");callback(DEP_In_hell);return configured[DEP_In_hell]?opts[DEP_In_hell]:0;}
boolean In_mines(d_level * a0){append("In_mines:ptr;");callback(DEP_In_mines);return configured[DEP_In_mines]?opts[DEP_In_mines]:0;}
boolean In_quest(d_level * a0){append("In_quest:ptr;");callback(DEP_In_quest);return configured[DEP_In_quest]?opts[DEP_In_quest]:0;}
char * Monnam(struct monst * a0){append("Monnam:%d;",mid(a0));callback(DEP_Monnam);return namebuf("value");}
boolean On_W_tower_level(d_level * a0){append("On_W_tower_level:ptr;");callback(DEP_On_W_tower_level);return configured[DEP_On_W_tower_level]?opts[DEP_On_W_tower_level]:0;}
char * The(const char * a0){append("The:%s;",nullable(a0));callback(DEP_The);return namebuf("value");}
char * Tobjnam(struct obj * a0,const char * a1){append("Tobjnam:%d:%s;",oid(a0),nullable(a1));callback(DEP_Tobjnam);return namebuf("value");}
void add_to_buried(struct obj * a0){append("add_to_buried:%d;",oid(a0));callback(DEP_add_to_buried);}
void add_valid_menu_class(int a0){append("add_valid_menu_class:%ld;",(long)a0);callback(DEP_add_valid_menu_class);}
char * an(const char * a0){append("an:%s;",nullable(a0));callback(DEP_an);return namebuf("value");}
boolean artifact_has_invprop(struct obj * a0,uchar a1){append("artifact_has_invprop:%d:%ld;",oid(a0),(long)a1);callback(DEP_artifact_has_invprop);return configured[DEP_artifact_has_invprop]?opts[DEP_artifact_has_invprop]:0;}
void assign_graphics(int a0){append("assign_graphics:%ld;",(long)a0);callback(DEP_assign_graphics);}
void assign_rnd_level(d_level * a0,d_level * a1,int a2){append("assign_rnd_level:ptr:ptr:%ld;",(long)a2);callback(DEP_assign_rnd_level);}
boolean at_dgn_entrance(const char * a0){append("at_dgn_entrance:%s;",nullable(a0));callback(DEP_at_dgn_entrance);return configured[DEP_at_dgn_entrance]?opts[DEP_at_dgn_entrance]:0;}
void ballfall(void){append("ballfall;");callback(DEP_ballfall);}
void ballrelease(boolean a0){append("ballrelease:%ld;",(long)a0);callback(DEP_ballrelease);}
const char * body_part(int a0){append("body_part:%ld;",(long)a0);callback(DEP_body_part);return namebuf("value");}
boolean bones_include_name(const char * a0){append("bones_include_name:%s;",nullable(a0));callback(DEP_bones_include_name);return configured[DEP_bones_include_name]?opts[DEP_bones_include_name]:0;}
int breakobj(struct obj * a0,coordxy a1,coordxy a2,boolean a3,boolean a4){append("breakobj:%d:%ld:%ld:%ld:%ld;",oid(a0),(long)a1,(long)a2,(long)a3,(long)a4);callback(DEP_breakobj);return configured[DEP_breakobj]?opts[DEP_breakobj]:0;}
void bufon(int a0){append("bufon:%ld;",(long)a0);callback(DEP_bufon);}
boolean builds_up(d_level * a0){append("builds_up:ptr;");callback(DEP_builds_up);return configured[DEP_builds_up]?opts[DEP_builds_up]:0;}
void buried_ball_to_punishment(void){append("buried_ball_to_punishment;");callback(DEP_buried_ball_to_punishment);}
void burn_away_slime(void){append("burn_away_slime;");callback(DEP_burn_away_slime);}
void bury_objs(int a0,int a1){append("bury_objs:%ld:%ld;",(long)a0,(long)a1);callback(DEP_bury_objs);}
void check_gold_symbol(void){append("check_gold_symbol;");callback(DEP_check_gold_symbol);}
void check_special_room(boolean a0){append("check_special_room:%ld;",(long)a0);callback(DEP_check_special_room);}
d_level * clamp_hole_destination(d_level * a0){append("clamp_hole_destination:ptr;");callback(DEP_clamp_hole_destination);return 0;}
void climb_pit(void){append("climb_pit;");callback(DEP_climb_pit);}
void com_pager(const char * a0){append("com_pager:%s;",nullable(a0));callback(DEP_com_pager);}
void container_impact_dmg(struct obj * a0,coordxy a1,coordxy a2){append("container_impact_dmg:%d:%ld:%ld;",oid(a0),(long)a1,(long)a2);callback(DEP_container_impact_dmg);}
char * corpse_xname(struct obj * a0,const char * a1,unsigned int a2){append("corpse_xname:%d:%s:%ld;",oid(a0),nullable(a1),(long)a2);callback(DEP_corpse_xname);return namebuf("value");}
void costly_alteration(struct obj * a0,int a1){append("costly_alteration:%d:%ld;",oid(a0),(long)a1);callback(DEP_costly_alteration);}
int count_justpicked(struct obj * a0){append("count_justpicked:%d;",oid(a0));callback(DEP_count_justpicked);return configured[DEP_count_justpicked]?opts[DEP_count_justpicked]:0;}
void create_mplayers(int a0,boolean a1){append("create_mplayers:%ld:%ld;",(long)a0,(long)a1);callback(DEP_create_mplayers);}
void delete_levelfile(int a0){append("delete_levelfile:%ld;",(long)a0);callback(DEP_delete_levelfile);}
void deliver_splev_message(void){append("deliver_splev_message;");callback(DEP_deliver_splev_message);}
int describe_level(char*b,int flags){append("describe_level:%d;",flags);strcpy(b,"Controlled level");callback(DEP_describe_level);return configured[DEP_describe_level]?opts[DEP_describe_level]:1;}
void discard_migrations(void){append("discard_migrations;");callback(DEP_discard_migrations);}
void dismount_steed(int a0){append("dismount_steed:%ld;",(long)a0);callback(DEP_dismount_steed);}
boolean dmgtype(struct permonst * a0,int a1){append("dmgtype:ptr:%ld;",(long)a1);callback(DEP_dmgtype);return configured[DEP_dmgtype]?opts[DEP_dmgtype]:0;}
int dmgval(struct obj * a0,struct monst * a1){append("dmgval:%d:%d;",oid(a0),mid(a1));callback(DEP_dmgval);return configured[DEP_dmgval]?opts[DEP_dmgval]:0;}
void docall(struct obj * a0){append("docall:%d;",oid(a0));callback(DEP_docall);}
void docrt(void){append("docrt;");callback(DEP_docrt);}
char * doname(struct obj * a0){append("doname:%d;",oid(a0));callback(DEP_doname);return namebuf("value");}
void dotrap(struct trap * a0,unsigned int a1){append("dotrap:ptr:%ld;",(long)a1);callback(DEP_dotrap);}
void drag_down(void){append("drag_down;");callback(DEP_drag_down);}
void drop_ball(coordxy a0,coordxy a1){append("drop_ball:%ld:%ld;",(long)a0,(long)a1);callback(DEP_drop_ball);}
void fill_pit(coordxy a0,coordxy a1){append("fill_pit:%ld:%ld;",(long)a0,(long)a1);callback(DEP_fill_pit);}
struct obj * find_justpicked(struct obj * a0){append("find_justpicked:%d;",oid(a0));callback(DEP_find_justpicked);return 0;}
boolean finesse_ahriman(struct obj * a0){append("finesse_ahriman:%d;",oid(a0));callback(DEP_finesse_ahriman);return configured[DEP_finesse_ahriman]?opts[DEP_finesse_ahriman]:0;}
void fix_shop_damage(void){append("fix_shop_damage;");callback(DEP_fix_shop_damage);}
void floating_above(const char * a0){append("floating_above:%s;",nullable(a0));callback(DEP_floating_above);}
void free_luathemes(enum lua_theme_group a0){append("free_luathemes:%ld;",(long)a0);callback(DEP_free_luathemes);}
void free_omid(struct obj * a0){append("free_omid:%d;",oid(a0));callback(DEP_free_omid);}
void free_omonst(struct obj * a0){append("free_omonst:%d;",oid(a0));callback(DEP_free_omonst);}
char * fruitname(boolean a0){append("fruitname:%ld;",(long)a0);callback(DEP_fruitname);return namebuf("value");}
void fumaroles(void){append("fumaroles;");callback(DEP_fumaroles);}
void gain_guardian_angel(void){append("gain_guardian_angel;");callback(DEP_gain_guardian_angel);}
int glyph_to_cmap(int a0){append("glyph_to_cmap:%ld;",(long)a0);callback(DEP_glyph_to_cmap);return configured[DEP_glyph_to_cmap]?opts[DEP_glyph_to_cmap]:0;}
void goto_hell(boolean a0,boolean a1){append("goto_hell:%ld:%ld;",(long)a0,(long)a1);callback(DEP_goto_hell);}
boolean gulp_blnd_check(void){append("gulp_blnd_check;");callback(DEP_gulp_blnd_check);return configured[DEP_gulp_blnd_check]?opts[DEP_gulp_blnd_check]:0;}
const char * hcolor(const char * a0){append("hcolor:%s;",nullable(a0));callback(DEP_hcolor);return namebuf("value");}
int healmon(struct monst * a0,int a1,int a2){append("healmon:%d:%ld:%ld;",mid(a0),(long)a1,(long)a2);callback(DEP_healmon);return configured[DEP_healmon]?opts[DEP_healmon]:0;}
void hitfloor(struct obj * a0,boolean a1){append("hitfloor:%d:%ld;",oid(a0),(long)a1);callback(DEP_hitfloor);}
const char * hliquid(const char * a0){append("hliquid:%s;",nullable(a0));callback(DEP_hliquid);return namebuf("value");}
void impact_disturbs_zombies(struct obj * a0,boolean a1){append("impact_disturbs_zombies:%d:%ld;",oid(a0),(long)a1);callback(DEP_impact_disturbs_zombies);}
void impact_drop(struct obj * a0,coordxy a1,coordxy a2,xint16 a3){append("impact_drop:%d:%ld:%ld:%ld;",oid(a0),(long)a1,(long)a2,(long)a3);callback(DEP_impact_drop);}
boolean in_out_region(coordxy a0,coordxy a1){append("in_out_region:%ld:%ld;",(long)a0,(long)a1);callback(DEP_in_out_region);return configured[DEP_in_out_region]?opts[DEP_in_out_region]:0;}
boolean is_unpaid(struct obj * a0){append("is_unpaid:%d;",oid(a0));callback(DEP_is_unpaid);return configured[DEP_is_unpaid]?opts[DEP_is_unpaid]:0;}
void keepdogs(boolean a0){append("keepdogs:%ld;",(long)a0);callback(DEP_keepdogs);}
void kill_genocided_monsters(void){append("kill_genocided_monsters;");callback(DEP_kill_genocided_monsters);}
boolean lava_damage(struct obj * a0,coordxy a1,coordxy a2){append("lava_damage:%d:%ld:%ld;",oid(a0),(long)a1,(long)a2);callback(DEP_lava_damage);return configured[DEP_lava_damage]?opts[DEP_lava_damage]:0;}
xint16 ledger_to_dnum(xint16 a0){append("ledger_to_dnum:%ld;",(long)a0);callback(DEP_ledger_to_dnum);return configured[DEP_ledger_to_dnum]?opts[DEP_ledger_to_dnum]:0;}
xint16 level_difficulty(void){append("level_difficulty;");callback(DEP_level_difficulty);return configured[DEP_level_difficulty]?opts[DEP_level_difficulty]:0;}
const char * locomotion(const struct permonst * a0,const char * a1){append("locomotion:ptr:%s;",nullable(a1));callback(DEP_locomotion);return namebuf("value");}
void losedogs(void){append("losedogs;");callback(DEP_losedogs);}
void losehp(int a0,const char * a1,schar a2){append("losehp:%ld:%s:%ld;",(long)a0,nullable(a1),(long)a2);callback(DEP_losehp);}
boolean m_in_air(struct monst * a0){append("m_in_air:%d;",mid(a0));callback(DEP_m_in_air);return configured[DEP_m_in_air]?opts[DEP_m_in_air]:0;}
void m_into_limbo(struct monst * a0){append("m_into_limbo:%d;",mid(a0));callback(DEP_m_into_limbo);}
void make_grave(coordxy a0,coordxy a1,const char * a2){append("make_grave:%ld:%ld:%s;",(long)a0,(long)a1,nullable(a2));callback(DEP_make_grave);}
char * makeplural(const char * a0){append("makeplural:%s;",nullable(a0));callback(DEP_makeplural);return namebuf("value");}
struct trap * maketrap(coordxy a0,coordxy a1,int a2){append("maketrap:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2);callback(DEP_maketrap);return 0;}
void map_background(coordxy a0,coordxy a1,int a2){append("map_background:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2);callback(DEP_map_background);}
void map_object(struct obj * a0,int a1){append("map_object:%d:%ld;",oid(a0),(long)a1);callback(DEP_map_object);}
xint16 maxledgerno(void){append("maxledgerno;");callback(DEP_maxledgerno);return configured[DEP_maxledgerno]?opts[DEP_maxledgerno]:0;}
void maybe_reset_pick(struct obj * a0){append("maybe_reset_pick:%d;",oid(a0));callback(DEP_maybe_reset_pick);}
const char * mbodypart(struct monst * a0,int a1){append("mbodypart:%d:%ld;",mid(a0),(long)a1);callback(DEP_mbodypart);return namebuf("value");}
void mcureblindness(struct monst * a0,boolean a1){append("mcureblindness:%d:%ld;",mid(a0),(long)a1);callback(DEP_mcureblindness);}
void minstapetrify(struct monst * a0,boolean a1){append("minstapetrify:%d:%ld;",mid(a0),(long)a1);callback(DEP_minstapetrify);}
void mklev(void){append("mklev;");callback(DEP_mklev);}
void mnexto(struct monst * a0,unsigned int a1){append("mnexto:%d:%ld;",mid(a0),(long)a1);callback(DEP_mnexto);}
char * mon_nam(struct monst * a0){append("mon_nam:%d;",mid(a0));callback(DEP_mon_nam);return namebuf("value");}
void mondied(struct monst * a0){append("mondied:%d;",mid(a0));callback(DEP_mondied);}
int monster_nearby(void){append("monster_nearby;");callback(DEP_monster_nearby);return configured[DEP_monster_nearby]?opts[DEP_monster_nearby]:0;}
void more_experienced(int a0,int a1){append("more_experienced:%ld:%ld;",(long)a0,(long)a1);callback(DEP_more_experienced);}
void movebubbles(void){append("movebubbles;");callback(DEP_movebubbles);}
int mpickobj(struct monst*m,struct obj*o){append("mpickobj:%d:%d;",mid(m),oid(o));o->where=OBJ_MINVENT;o->ocarry=m;o->nobj=m->minvent;m->minvent=o;callback(DEP_mpickobj);return 0;}
int newcham(struct monst * a0,struct permonst * a1,unsigned int a2){append("newcham:%d:ptr:%ld;",mid(a0),(long)a2);callback(DEP_newcham);return configured[DEP_newcham]?opts[DEP_newcham]:0;}
void newexplevel(void){append("newexplevel;");callback(DEP_newexplevel);}
void next_level(boolean a0){append("next_level:%ld;",(long)a0);callback(DEP_next_level);}
boolean next_to_u(void){append("next_to_u;");callback(DEP_next_to_u);return configured[DEP_next_to_u]?opts[DEP_next_to_u]:0;}
void notice_all_mons(boolean a0){append("notice_all_mons:%ld;",(long)a0);callback(DEP_notice_all_mons);}
void obj_delivery(boolean a0){append("obj_delivery:%ld;",(long)a0);callback(DEP_obj_delivery);}
boolean obj_has_timer(struct obj * a0,short a1){append("obj_has_timer:%d:%ld;",oid(a0),(long)a1);callback(DEP_obj_has_timer);return configured[DEP_obj_has_timer]?opts[DEP_obj_has_timer]:0;}
const char * obj_pmname(struct obj * a0){append("obj_pmname:%d;",oid(a0));callback(DEP_obj_pmname);return namebuf("value");}
boolean obj_resists(struct obj * a0,int a1,int a2){append("obj_resists:%d:%ld:%ld;",oid(a0),(long)a1,(long)a2);callback(DEP_obj_resists);return configured[DEP_obj_resists]?opts[DEP_obj_resists]:0;}
void oinit(void){append("oinit;");callback(DEP_oinit);}
boolean ok_to_quest(void){append("ok_to_quest;");callback(DEP_ok_to_quest);return configured[DEP_ok_to_quest]?opts[DEP_ok_to_quest]:0;}
boolean olfaction(struct permonst * a0){append("olfaction:ptr;");callback(DEP_olfaction);return configured[DEP_olfaction]?opts[DEP_olfaction]:0;}
void onquest(void){append("onquest;");callback(DEP_onquest);}
char * otense(struct obj * a0,const char * a1){append("otense:%d:%s;",oid(a0),nullable(a1));callback(DEP_otense);return namebuf("value");}
char paranoid_ynq(boolean a0,const char * a1,boolean a2){append("paranoid_ynq:%ld:%s:%ld;",(long)a0,nullable(a1),(long)a2);callback(DEP_paranoid_ynq);return configured[DEP_paranoid_ynq]?opts[DEP_paranoid_ynq]:0;}
int pickup(int a0){append("pickup:%ld;",(long)a0);callback(DEP_pickup);return configured[DEP_pickup]?opts[DEP_pickup]:0;}
void placebc(void){append("placebc;");callback(DEP_placebc);}
int pm_to_cham(int a0){append("pm_to_cham:%ld;",(long)a0);callback(DEP_pm_to_cham);return configured[DEP_pm_to_cham]?opts[DEP_pm_to_cham]:NON_PM;}
boolean pooleffects(boolean a0){append("pooleffects:%ld;",(long)a0);callback(DEP_pooleffects);return configured[DEP_pooleffects]?opts[DEP_pooleffects]:0;}
void prev_level(boolean a0){append("prev_level:%ld;",(long)a0);callback(DEP_prev_level);}
void print_level_annotation(void){append("print_level_annotation;");callback(DEP_print_level_annotation);}
void pudding_merge_message(struct obj * a0,struct obj * a1){append("pudding_merge_message:%d:%d;",oid(a0),oid(a1));callback(DEP_pudding_merge_message);}
void recalc_block_point(coordxy a0,coordxy a1){append("recalc_block_point:%ld:%ld;",(long)a0,(long)a1);callback(DEP_recalc_block_point);}
void recalc_mapseen(void){append("recalc_mapseen;");callback(DEP_recalc_mapseen);}
void recbranch_mapseen(d_level * a0,d_level * a1){append("recbranch_mapseen:ptr:ptr;");callback(DEP_recbranch_mapseen);}
void record_achievement(schar a0){append("record_achievement:%ld;",(long)a0);callback(DEP_record_achievement);}
void reglyph_darkroom(void){append("reglyph_darkroom;");callback(DEP_reglyph_darkroom);}
void remdun_mapseen(int a0){append("remdun_mapseen:%ld;",(long)a0);callback(DEP_remdun_mapseen);}
void reseed_random(int (*a0)(int)){append("reseed_random:ptr;");callback(DEP_reseed_random);}
void reset_glyphmap(enum glyphmap_change_triggers a0){append("reset_glyphmap:%ld;",(long)a0);callback(DEP_reset_glyphmap);}
void reset_hostility(struct monst * a0){append("reset_hostility:%d;",mid(a0));callback(DEP_reset_hostility);}
void reset_trapset(void){append("reset_trapset;");callback(DEP_reset_trapset);}
void resurrect(void){append("resurrect;");callback(DEP_resurrect);}
long rider_revival_time(struct obj * a0,boolean a1){append("rider_revival_time:%d:%ld;",oid(a0),(long)a1);callback(DEP_rider_revival_time);return configured[DEP_rider_revival_time]?opts[DEP_rider_revival_time]:0;}
boolean rloc(struct monst * a0,unsigned int a1){append("rloc:%d:%ld;",mid(a0),(long)a1);callback(DEP_rloc);return configured[DEP_rloc]?opts[DEP_rloc]:0;}
char * rndmonnam(char * a0){append("rndmonnam:%s;",nullable(a0));callback(DEP_rndmonnam);return namebuf("value");}
void rot_corpse(union any * a0,long a1){append("rot_corpse:ptr:%ld;",(long)a1);callback(DEP_rot_corpse);}
void run_timers(void){append("run_timers;");callback(DEP_run_timers);}
boolean safe_teleds(int a0){append("safe_teleds:%ld;",(long)a0);callback(DEP_safe_teleds);return configured[DEP_safe_teleds]?opts[DEP_safe_teleds]:0;}
void savestateinlock(void){append("savestateinlock;");callback(DEP_savestateinlock);}
void seetrap(struct trap * a0){append("seetrap:ptr;");callback(DEP_seetrap);}
void selftouch(const char * a0){append("selftouch:%s;",nullable(a0));callback(DEP_selftouch);}
void sellobj(struct obj * a0,coordxy a1,coordxy a2){append("sellobj:%d:%ld:%ld;",oid(a0),(long)a1,(long)a2);callback(DEP_sellobj);}
void sellobj_state(int a0){append("sellobj_state:%ld;",(long)a0);callback(DEP_sellobj_state);}
int sensemon(struct monst * a0){append("sensemon:%d;",mid(a0));callback(DEP_sensemon);return configured[DEP_sensemon]?opts[DEP_sensemon]:0;}
void set_bknown(struct obj * a0,unsigned int a1){append("set_bknown:%d:%ld;",oid(a0),(long)a1);callback(DEP_set_bknown);}
void set_corpsenm(struct obj * a0,int a1){append("set_corpsenm:%d:%ld;",oid(a0),(long)a1);callback(DEP_set_corpsenm);}
boolean ship_object(struct obj * a0,coordxy a1,coordxy a2,boolean a3){append("ship_object:%d:%ld:%ld:%ld;",oid(a0),(long)a1,(long)a2,(long)a3);callback(DEP_ship_object);return configured[DEP_ship_object]?opts[DEP_ship_object]:0;}
void stackobj(struct obj * a0){append("stackobj:%d;",oid(a0));callback(DEP_stackobj);}
stairway * stairway_at(coordxy a0,coordxy a1){append("stairway_at:%ld:%ld;",(long)a0,(long)a1);callback(DEP_stairway_at);return 0;}
stairway * stairway_find_from(d_level * a0,boolean a1){append("stairway_find_from:ptr:%ld;",(long)a1);callback(DEP_stairway_find_from);return 0;}
void stairway_free_all(void){append("stairway_free_all;");callback(DEP_stairway_free_all);}
boolean start_timer(long a0,short a1,short a2,union any * a3){append("start_timer:%ld:%ld:%ld:ptr;",(long)a0,(long)a1,(long)a2);callback(DEP_start_timer);return configured[DEP_start_timer]?opts[DEP_start_timer]:0;}
boolean sticks(struct permonst * a0){append("sticks:ptr;");callback(DEP_sticks);return configured[DEP_sticks]?opts[DEP_sticks]:0;}
long stolen_value(struct obj * a0,coordxy a1,coordxy a2,boolean a3,boolean a4){append("stolen_value:%d:%ld:%ld:%ld:%ld;",oid(a0),(long)a1,(long)a2,(long)a3,(long)a4);callback(DEP_stolen_value);return configured[DEP_stolen_value]?opts[DEP_stolen_value]:0;}
char * strchr(const char * a0,int a1){append("strchr:%s:%ld;",nullable(a0),(long)a1);callback(DEP_strchr);return namebuf("value");}
boolean stucksteed(boolean a0){append("stucksteed:%ld;",(long)a0);callback(DEP_stucksteed);return configured[DEP_stucksteed]?opts[DEP_stucksteed]:0;}
const char * surface(coordxy a0,coordxy a1){append("surface:%ld:%ld;",(long)a0,(long)a1);callback(DEP_surface);return namebuf("value");}
char * the(const char * a0){append("the:%s;",nullable(a0));callback(DEP_the);return namebuf("value");}
void tutorial(boolean a0){append("tutorial:%ld;",(long)a0);callback(DEP_tutorial);}
const char * u_locomotion(const char * a0){append("u_locomotion:%s;",nullable(a0));callback(DEP_u_locomotion);return namebuf("value");}
void u_on_dnstairs(void){append("u_on_dnstairs;");callback(DEP_u_on_dnstairs);}
void u_on_rndspot(int a0){append("u_on_rndspot:%ld;",(long)a0);callback(DEP_u_on_rndspot);}
void u_on_sstairs(int a0){append("u_on_sstairs:%ld;",(long)a0);callback(DEP_u_on_sstairs);}
void u_on_upstairs(void){append("u_on_upstairs;");callback(DEP_u_on_upstairs);}
boolean u_safe_from_fatal_corpse(struct obj * a0,int a1){append("u_safe_from_fatal_corpse:%d:%ld;",oid(a0),(long)a1);callback(DEP_u_safe_from_fatal_corpse);return configured[DEP_u_safe_from_fatal_corpse]?opts[DEP_u_safe_from_fatal_corpse]:0;}
boolean uescaped_shaft(struct trap * a0){append("uescaped_shaft:ptr;");callback(DEP_uescaped_shaft);return configured[DEP_uescaped_shaft]?opts[DEP_uescaped_shaft]:0;}
boolean undiscovered_artifact(xint16 a0){append("undiscovered_artifact:%ld;",(long)a0);callback(DEP_undiscovered_artifact);return configured[DEP_undiscovered_artifact]?opts[DEP_undiscovered_artifact]:0;}
void unplacebc(void){append("unplacebc;");callback(DEP_unplacebc);}
void update_mlstmv(void){append("update_mlstmv;");callback(DEP_update_mlstmv);}
int use_pick_axe2(struct obj * a0){append("use_pick_axe2:%d;",oid(a0));callback(DEP_use_pick_axe2);return configured[DEP_use_pick_axe2]?opts[DEP_use_pick_axe2]:0;}
boolean uteetering_at_seen_pit(struct trap * a0){append("uteetering_at_seen_pit:ptr;");callback(DEP_uteetering_at_seen_pit);return configured[DEP_uteetering_at_seen_pit]?opts[DEP_uteetering_at_seen_pit]:0;}
void vision_recalc(int a0){append("vision_recalc:%ld;",(long)a0);callback(DEP_vision_recalc);}
void vision_reset(void){append("vision_reset;");callback(DEP_vision_reset);}
char * vtense(const char * a0,const char * a1){append("vtense:%s:%s;",nullable(a0),nullable(a1));callback(DEP_vtense);return namebuf("value");}
void wake_nearto(coordxy a0,coordxy a1,int a2){append("wake_nearto:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2);callback(DEP_wake_nearto);}
int water_damage(struct obj * a0,const char * a1,boolean a2){append("water_damage:%d:%s:%ld;",oid(a0),nullable(a1),(long)a2);callback(DEP_water_damage);return configured[DEP_water_damage]?opts[DEP_water_damage]:0;}
const char * waterbody_name(coordxy a0,coordxy a1){append("waterbody_name:%ld:%ld;",(long)a0,(long)a1);callback(DEP_waterbody_name);return namebuf("value");}
int welded(struct obj * a0){append("welded:%d;",oid(a0));callback(DEP_welded);return configured[DEP_welded]?opts[DEP_welded]:0;}
void weldmsg(struct obj * a0){append("weldmsg:%d;",oid(a0));callback(DEP_weldmsg);}
char * xname(struct obj * a0){append("xname:%d;",oid(a0));callback(DEP_xname);return namebuf("value");}
char * y_monnam(struct monst * a0){append("y_monnam:%d;",mid(a0));callback(DEP_y_monnam);return namebuf("value");}
char * yname(struct obj * a0){append("yname:%d;",oid(a0));callback(DEP_yname);return namebuf("value");}
char * yobjnam(struct obj * a0,const char * a1){append("yobjnam:%d:%s;",oid(a0),nullable(a1));callback(DEP_yobjnam);return namebuf("value");}

#include <setjmp.h>
static jmp_buf bail;static int guarding,panic_code;
static void unlink_obj(struct obj**head,struct obj*o){while(*head&&*head!=o)head=&(*head)->nobj;if(*head)*head=o->nobj;}
static void dispose(struct obj*o){int i=oid(o);append("dispose:%d;",i);unlink_obj(&gi.invent,o);if(o->where==OBJ_FLOOR){struct obj**h=&svl.level.objects[o->ox][o->oy];while(*h&&*h!=o)h=&(*h)->nexthere;if(*h)*h=o->nexthere;}if(i>=0){pool[i]=0;free(o);frees++;}}
static void grow_or_enter(int stage){callback(stage);}
static int draw(int bound){int v=nr?rolls[ri++%nr]:(int)((seed=seed*1664525U+1013904223U)>>1);if(bound<=0){append("badbound:%d;",bound);return 0;}return(unsigned)v%(unsigned)bound;}
boolean rng_log_enabled(void){return !opts[500];}
void rng_log_set_caller(const char * a0,int a1,const char * a2){callerfile=a0;callerline=a1;callerfn=a2;append("caller:%s:%d:%s;",a0,a1,a2);}
int (rn2)(int a0){int v=draw(a0);append("rn2:%d:%d;",a0,v);callback(DEP_rn2);return v;}
int (rnd)(int a0){int v=draw(a0)+1;if(opts[506]){u.uprops[HALF_PHDAM].intrinsic=opts[506]==1?1:0;opts[506]=0;append("half-flip:%ld;",u.uprops[HALF_PHDAM].intrinsic);}append("rnd:%d:%d;",a0,v);callback(DEP_rnd);return v;}
int (d)(int a0,int a1){int v=0;for(int i=0;i<a0;i++)v+=draw(a1)+1;append("d:%d:%d:%d;",a0,a1,v);callback(DEP_d);return v;}
int (rnz)(int a0){int v=a0+draw(a0);append("rnz:%d:%d;",a0,v);callback(DEP_rnz);return v;}
int rn2_on_display_rng(int a0){int v=draw(a0);append("display:%d:%d;",a0,v);return v;}
void pline(const char * a0,...){va_list ap;va_start(ap,a0);message("pline",a0,ap);va_end(ap);callback(DEP_pline);}
void pline_The(const char * a0,...){va_list ap;va_start(ap,a0);message("pline_The",a0,ap);va_end(ap);callback(DEP_pline_The);}
void There(const char * a0,...){va_list ap;va_start(ap,a0);message("There",a0,ap);va_end(ap);callback(DEP_There);}
void Norep(const char * a0,...){va_list ap;va_start(ap,a0);message("Norep",a0,ap);va_end(ap);callback(DEP_Norep);}
void You(const char * a0,...){va_list ap;va_start(ap,a0);message("You",a0,ap);va_end(ap);callback(DEP_You);}
void Your(const char * a0,...){va_list ap;va_start(ap,a0);message("Your",a0,ap);va_end(ap);callback(DEP_Your);}
void You_feel(const char * a0,...){va_list ap;va_start(ap,a0);message("You_feel",a0,ap);va_end(ap);callback(DEP_You_feel);}
void You_see(const char * a0,...){va_list ap;va_start(ap,a0);message("You_see",a0,ap);va_end(ap);callback(DEP_You_see);}
void You_hear(const char * a0,...){va_list ap;va_start(ap,a0);message("You_hear",a0,ap);va_end(ap);callback(DEP_You_hear);}
void You_cant(const char * a0,...){va_list ap;va_start(ap,a0);message("You_cant",a0,ap);va_end(ap);callback(DEP_You_cant);}
void impossible(const char * a0,...){va_list ap;va_start(ap,a0);message("impossible",a0,ap);va_end(ap);callback(DEP_impossible);}
void panic(const char * a0,...){va_list ap;va_start(ap,a0);message("panic",a0,ap);va_end(ap);panic_code=1;if(guarding)longjmp(bail,1);abort();}
void error(const char * a0,...){va_list ap;va_start(ap,a0);message("error",a0,ap);va_end(ap);panic_code=1;if(guarding)longjmp(bail,1);abort();}
void livelog_printf(long a0,const char * a1,...){append("logtype:%ld;",a0);va_list ap;va_start(ap,a1);message("log",a1,ap);va_end(ap);}
void done(int a0){append("done:%d;",a0);panic_code=2;if(guarding)longjmp(bail,1);abort();}
int canseemon(struct monst * a0){append("canseemon:%d;",mid(a0));callback(DEP_canseemon);return !opts[DEP_canseemon];}
boolean can_reach_floor(boolean a0){append("reach:%d;",a0);callback(DEP_can_reach_floor);return !opts[DEP_can_reach_floor];}
int isok(coordxy a0,coordxy a1){return a0>=1&&a0<COLNO&&a1>=0&&a1<ROWNO;}
boolean is_pool(coordxy a0,coordxy a1){int t=levl[a0][a1].typ;return t==POOL||t==MOAT||t==WATER;}
boolean is_lava(coordxy a0,coordxy a1){return levl[a0][a1].typ==LAVAPOOL;}
boolean is_pool_or_lava(coordxy a0,coordxy a1){return is_pool(a0,a1)||is_lava(a0,a1);}
boolean on_level(d_level * a0,d_level * a1){return a0->dnum==a1->dnum&&a0->dlevel==a1->dlevel;}
void assign_level(d_level * a0,d_level * a1){append("assign:%d:%d;",a1->dnum,a1->dlevel);*a0=*a1;}
struct trap * t_at(coordxy a0,coordxy a1){for(int i=0;i<4;i++)if(traps[i].ttyp&&traps[i].tx==a0&&traps[i].ty==a1)return traps+i;return 0;}
struct engr * engr_at(coordxy a0,coordxy a1){return opts[DEP_engr_at]?(struct engr*)(uintptr_t)1:0;}
void newsym(coordxy a0,coordxy a1){append("newsym:%d:%d:%d;",a0,a1,levl[a0][a1].typ);callback(DEP_newsym);}
boolean set_levltyp(coordxy a0,coordxy a1,schar a2){append("terrain:%d:%d:%d;",a0,a1,a2);levl[a0][a1].typ=a2;callback(DEP_set_levltyp);return TRUE;}
void deltrap(struct trap * a0){append("deltrap:%ld;",(long)(a0-traps));a0->ttyp=0;callback(DEP_deltrap);}
boolean delfloortrap(struct trap * a0){append("delfloortrap:%ld;",(long)(a0-traps));a0->ttyp=0;callback(DEP_delfloortrap);return TRUE;}
void place_object(struct obj * a0,coordxy a1,coordxy a2){append("place:%d:%d:%d;",oid(a0),a1,a2);a0->where=OBJ_FLOOR;a0->ox=a1;a0->oy=a2;a0->nexthere=svl.level.objects[a1][a2];svl.level.objects[a1][a2]=a0;callback(DEP_place_object);}
void obj_extract_self(struct obj * a0){append("extract:%d;",oid(a0));unlink_obj(&gi.invent,a0);a0->nobj=0;a0->where=OBJ_FREE;callback(DEP_obj_extract_self);}
void freeinv(struct obj * a0){append("freeinv:%d;",oid(a0));unlink_obj(&gi.invent,a0);a0->nobj=0;a0->where=OBJ_FREE;callback(DEP_freeinv);}
void useup(struct obj * a0){append("useup:%d;",oid(a0));dispose(a0);}
void useupf(struct obj * a0,long a1){append("useupf:%d:%ld;",oid(a0),a1);dispose(a0);}
void delobj(struct obj * a0){append("delobj:%d;",oid(a0));dispose(a0);}
void obfree(struct obj * a0,struct obj * a1){append("obfree:%d:%d;",oid(a0),oid(a1));dispose(a0);}
int weight(struct obj * a0){append("weight:%d;",oid(a0));return(unsigned)(a0->quan*7);}
struct obj * splitobj(struct obj * a0,long a1){int i;for(i=0;i<32&&pool[i];i++){}if(i==32)abort();pool[i]=malloc(sizeof*pool[i]);memcpy(pool[i],a0,sizeof*a0);pool[i]->quan=a1;a0->quan-=a1;pool[i]->nobj=a0->nobj;a0->nobj=pool[i];append("split:%d:%ld:%d;",oid(a0),a1,i);callback(DEP_splitobj);return pool[i];}
int any_obj_ok(struct obj * a0){return a0?GETOBJ_SUGGEST:GETOBJ_EXCLUDE;}
boolean allow_all(struct obj * a0){return TRUE;}
boolean allow_category(struct obj * a0){append("allow:%d;",oid(a0));return !opts[DEP_allow_category];}
struct obj * getobj(const char * a0,int (*a1)(struct obj *),unsigned int a2){append("getobj:%s:%u:%d;",a0,a2,a1(pool[opts[501]]));callback(DEP_getobj);return pool[opts[501]];}
int ggetobj(const char * a0,int (*a1)(struct obj *),int a2,boolean a3,unsigned int * a4){append("ggetobj:%s:%d:%d;",a0,a2,a3);if(a4)*a4=opts[DEP_ggetobj];callback(DEP_ggetobj);return opts[502]?a1(pool[opts[501]]):opts[DEP_ggetobj];}
int query_category(const char * a0,struct obj * a1,int a2,menu_item ** a3,int a4){append("query_category:%s:%d:%d;",a0,a2,a4);callback(DEP_query_category);int n=opts[DEP_query_category];*a3=0;if(n>0){*a3=malloc(n*sizeof**a3);for(int i=0;i<n;i++){(*a3)[i].item.a_int=opts[503];(*a3)[i].count=opts[504]?opts[504]:1;}}return n;}
int query_objlist(const char * a0,struct obj ** a1,int a2,menu_item ** a3,int a4,boolean (*a5)(struct obj *)){append("query_objlist:%s:%d:%d;",a0,a2,a4);callback(DEP_query_objlist);int n=opts[DEP_query_objlist];*a3=0;if(n>0){*a3=malloc(n*sizeof**a3);for(int i=0;i<n;i++){(*a3)[i].item.a_obj=pool[opts[501]];append("filter:%d;",a5(pool[opts[501]]));(*a3)[i].count=opts[504]?opts[504]:1;}}return n;}
void set_occupation(int (*a0)(void),const char * a1,cmdcount_nht a2){append("occupation:%s:%ld;",a1,a2);occupation=a0;callback(DEP_set_occupation);}
void setuwep(struct obj * a0){append("setuwep:%d;",oid(a0));uwep=a0;callback(DEP_setuwep);}
void setuqwep(struct obj * a0){append("setuqwep:%d;",oid(a0));uquiver=a0;callback(DEP_setuqwep);}
void setuswapwep(struct obj * a0){append("setuswapwep:%d;",oid(a0));uswapwep=a0;callback(DEP_setuswapwep);}
void set_itimeout(long * a0,long a1){append("settimeout:%ld;",a1);*a0=(*a0&~TIMEOUT)|(a1&TIMEOUT);callback(DEP_set_itimeout);}
void incr_itimeout(long * a0,int a1){append("inctimeout:%d;",a1);*a0=(*a0&~TIMEOUT)|((*a0+a1)&TIMEOUT);callback(DEP_incr_itimeout);}
void make_blinded(long a0,boolean a1){append("blind:%ld:%d;",a0,a1);u.uprops[BLINDED].intrinsic=a0;callback(DEP_make_blinded);}
void set_uinwater(int a0){append("inwater:%d;",a0);u.uinwater=a0;}
void set_ustuck(struct monst * a0){append("ustuck:%d;",mid(a0));u.ustuck=a0;}
void set_move_cmd(int a0,int a1){append("move:%d:%d;",a0,a1);}
void reset_utrap(boolean a0){append("resettrap:%d;",a0);u.utrap=u.utraptype=0;}
void reset_occupations(void){append("resetoccupation;");occupation=0;}
NHFILE * create_levelfile(int a0,char * a1){append("createfile:%d;",a0);if(opts[DEP_create_levelfile]){a1[0]=0;file.mode=WRITING;file.fd=7;file.structlevel=opts[505];return &file;}strcpy(a1,"controlled unavailable file");return 0;}
void close_nhfile(NHFILE * a0){append("closefile;");}
NHFILE * open_levelfile(int a0,char * a1){append("openfile:%d;",a0);return opts[DEP_open_levelfile]?&file:0;}
boolean tricked_fileremoved(NHFILE * a0,char * a1){append("fileremoved;");return opts[DEP_tricked_fileremoved];}
void savelev(NHFILE * a0,xint8 a1){append("savelev:%d:%d;",a1,a0->mode);callback(DEP_savelev);}
void getlev(NHFILE * a0,int a1,xint8 a2){append("getlev:%d:%d;",a1,a2);callback(DEP_getlev);}
int near_capacity(void){return opts[DEP_near_capacity];}
void encumber_msg(void){append("encumber;");}
char cmd_from_func(int (*a0)(void)){append("command:%d;",a0==do_reqmenu);return 109;}
int do_reqmenu(void){return ECMD_OK;}
boolean get_obj_location(struct obj * a0,coordxy * a1,coordxy * a2,int a3){append("objlocation:%d:%d;",oid(a0),a3);*a1=a0->ox;*a2=a0->oy;return !opts[DEP_get_obj_location];}
struct monst * get_container_location(struct obj * a0,int * a1,int * a2){append("containerlocation:%d;",oid(a0));*a1=opts[DEP_get_container_location];if(a2)*a2=1;return a0->where==OBJ_MINVENT?a0->ocarry:0;}
struct monst * revive(struct obj * a0,boolean a1){append("revive:%d:%d;",oid(a0),a1);callback(DEP_revive);if(!opts[DEP_revive])return 0;struct monst*m=monsters;m->data=&mons[a0->corpsenm];m->mx=a0->ox;m->my=a0->oy;dispose(a0);return m;}
struct permonst * grow_up(struct monst * a0,struct monst * a1){append("grow:%d:%d;",mid(a0),mid(a1));return a0->data;}
int zombie_form(struct permonst * a0){append("zombie:%d;",monsndx(a0));return configured[DEP_zombie_form]?opts[DEP_zombie_form]:NON_PM;}
int float_down(long a0,long a1){append("floatdown:%ld:%ld;",a0,a1);u.uprops[LEVITATION].intrinsic=0;u.uprops[LEVITATION].extrinsic=0;callback(DEP_float_down);return opts[DEP_float_down];}
boolean u_rooted(void){append("rooted;");return opts[DEP_u_rooted];}
char yn_function(const char * a0,const char * a1,char a2,boolean a3){append("yn:%s:%s:%d:%d;",a0,a1,a2,a3);return opts[DEP_yn_function]?opts[DEP_yn_function]:121;}
int nhl_pcall_handle(lua_State * a0,int a1,int a2,const char * a3,NHL_pcall_action a4){append("luacall:%d:%d:%s:%d;",a1,a2,a3,a4);return 0;}
int lua_getglobal(lua_State * a0,const char * a1){append("luaget:%s;",a1);return 0;}
const char * lua_pushstring(lua_State * a0,const char * a1){append("luastring:%s;",a1);return a1;}
void lua_settop(lua_State * a0,int a1){append("luatop:%d;",a1);}

static d_level destinations[4];static char input_text[2][BUFSZ];static int cells[4];
void probe_text(int which,const char*s){snprintf(input_text[which],BUFSZ,"%s",s?s:"");}
int probe_context_size(void){return sizeof(struct obj);}
int probe_layout_count(void){return sizeof teleport_do_layout/sizeof*teleport_do_layout;}
const char*probe_layout_name(int i){return teleport_do_layout[i].name;}
size_t probe_layout_value(int i){return teleport_do_layout[i].value;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
const char*probe_trace(void){return traces;}
int probe_dep_count(void){return sizeof dep_names/sizeof*dep_names;}
const char*probe_dep_name(int i){return dep_names[i];}
void probe_option(int i,int value){opts[i]=value;configured[i]=1;}
void probe_roll(int n,int value){if(n<0){nr=ri=0;return;}rolls[n]=value;if(n>=nr)nr=n+1;}
void probe_callback(int grow,int enter){growth_stage=grow;reenter_stage=enter;}
void probe_clear(void){ti=0;traces[0]=0;ri=0;}
static void mark_witness(void){append("mark;\n");}
void flush_screen(int n){append("flush:%d;",n);}
void probe_reset(unsigned value){
 for(int i=0;i<32;i++){free(pool[i]);pool[i]=0;}free(grown);grown=0;
 memset(&u,0,sizeof u);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&a11y,0,sizeof a11y);memset(&disp,0,sizeof disp);memset(&program_state,0,sizeof program_state);
 memset(&ga,0,sizeof ga);memset(&gb,0,sizeof gb);memset(&gd,0,sizeof gd);memset(&gf,0,sizeof gf);memset(&gi,0,sizeof gi);memset(&gl,0,sizeof gl);memset(&gm,0,sizeof gm);memset(&gu,0,sizeof gu);memset(&gv,0,sizeof gv);memset(&gy,0,sizeof gy);
 memset(&svc,0,sizeof svc);memset(&svd,0,sizeof svd);memset(&svh,0,sizeof svh);memset(&svl,0,sizeof svl);memset(&svm,0,sizeof svm);memset(&svn,0,sizeof svn);memset(&svp,0,sizeof svp);memset(&svq,0,sizeof svq);memset(&svu,0,sizeof svu);
 memset(opts,0,sizeof opts);memset(configured,0,sizeof configured);memset(monsters,0,sizeof monsters);memset(traps,0,sizeof traps);memset(cells,0,sizeof cells);memset(&file,0,sizeof file);memset(nhcb_counts,0,sizeof nhcb_counts);
 objects_globals_init();monst_globals_init();windowprocs.win_mark_synch=mark_witness;u.ux=u.uy=10;u.umonnum=u.umonster=PM_HUMAN;u.uz.dnum=2;u.uz.dlevel=3;u.uz0=u.uz;u.utolev=u.uz;
 for(int i=0;i<4;i++){destinations[i].dnum=2+i;destinations[i].dlevel=4+i;}
 svd.dungeon_topology.d_astral_level.dnum=12;svd.dungeon_topology.d_astral_level.dlevel=1;svd.dungeon_topology.d_water_level.dnum=11;svd.dungeon_topology.d_water_level.dlevel=1;svd.dungeon_topology.d_air_level.dnum=10;svd.dungeon_topology.d_air_level.dlevel=1;
 gy.youmonst.data=&mons[PM_HUMAN];gy.youmonst.mhp=gy.youmonst.mhpmax=100;for(int i=0;i<8;i++){monsters[i].data=&mons[PM_HUMAN];monsters[i].mhp=monsters[i].mhpmax=100;monsters[i].mx=20+i;monsters[i].my=10;}
 for(int y=0;y<ROWNO;y++){visionrows[y]=vision[y];for(int x=0;x<COLNO;x++){vision[y][x]=IN_SIGHT|COULD_SEE;levl[x][y].typ=ROOM;}}gv.viz_array=visionrows;
 flags.verbose=1;strcpy(input_text[0],"drop");input_text[1][0]=0;occupation=0;uwep=uswapwep=uquiver=uball=uchain=0;svm.moves=200;frees=nr=ri=0;seed=value;observed_stack_min=observed_stack_max=0;growth_stage=reenter_stage=-1;panic_code=0;ti=ni=0;traces[0]=0;callerfile=callerfn="";callerline=0;
}
void probe_object(int i,int typ,long count,int where){if(pool[i])dispose(pool[i]);struct obj*o=pool[i]=calloc(1,sizeof*o);o->otyp=typ;o->oclass=objects[typ].oc_class;o->quan=count;o->owt=(unsigned)(count*7);o->ox=o->oy=10;o->corpsenm=PM_HUMAN;o->where=where;if(where==OBJ_INVENT){o->nobj=gi.invent;gi.invent=o;}else if(where==OBJ_FLOOR){o->nexthere=svl.level.objects[10][10];svl.level.objects[10][10]=o;}}
void probe_objfield(int i,int key,int64_t value){struct obj*o=pool[i];switch(key){case 0:o->cursed=value;break;case 1:o->blessed=value;break;case 2:o->owornmask=value;break;case 3:o->bknown=value;break;case 4:o->oerodeproof=value;break;case 5:o->globby=value;break;case 6:o->corpsenm=value;break;case 7:o->age=value;break;case 8:o->spe=value;break;case 9:o->leashmon=value;break;case 10:o->cobj=value<0?0:pool[value];break;case 11:o->nobj=value<0?0:pool[value];break;case 12:o->ocontainer=value<0?0:pool[value];break;case 13:o->ocarry=value<0?0:monsters+value;break;case 14:o->where=value;break;case 15:o->otyp=value;o->oclass=objects[value].oc_class;break;case 16:o->oeaten=value;break;case 17:o->oartifact=value;break;case 18:o->in_use=value;break;case 19:o->ox=value;break;case 20:o->oy=value;break;case 21:o->bypass=value;break;default:abort();}}
void probe_hero(int key,int64_t value){switch(key){case 0:u.uswallow=value;u.ustuck=value?monsters:0;break;case 1:u.ustuck=value<0?0:monsters+value;break;case 2:u.usteed=value<0?0:monsters+value;break;case 3:u.uinwater=value;break;case 4:u.utrap=value;break;case 5:u.utraptype=value;break;case 6:flags.verbose=value;break;case 7:svc.context.mon_moving=value;break;case 8:program_state.gameover=value;break;case 9:u.uluck=value;break;case 10:u.umonnum=value;gy.youmonst.data=&mons[value];break;case 11:u.uundetected=value;break;case 12:iflags.menu_requested=value;break;case 13:flags.menu_style=value;break;case 14:flags.safe_wait=value;break;case 15:iflags.cmdassist=value;break;case 16:gm.multi=value;break;case 17:u.ucreamed=value;break;case 18:u.uroleplay.deaf=value;break;case 19:flags.ins_chkpt=value;break;case 20:svl.level.flags.temperature=value;break;case 21:svl.level.flags.has_shop=value;break;case 22:u.uconduct.gnostic=value;break;case 23:svm.moves=value;break;case 24:u.ushops[0]=value;break;case 25:u.uz=destinations[value];break;case 26:u.utolev=destinations[value];break;case 27:u.utotype=value;break;case 28:svh.hackpid=value;break;case 29:flags.debug=value;break;case 30:u.ux=value;break;case 31:u.uy=value;break;case 32:gu.urole.mnum=value;break;case 33:levl[u.ux][u.uy].horizontal=value;break;case 34:gb.bhitpos.x=value;break;case 35:gb.bhitpos.y=value;break;default:abort();}}
void probe_equipment(int slot,int obj){struct obj**slots[]={&uwep,&uswapwep,&uquiver,&uball,&uchain};*slots[slot]=obj<0?0:pool[obj];}
void probe_property(int key,int field,int64_t v){if(field==0)u.uprops[key].intrinsic=v;else if(field==1)u.uprops[key].extrinsic=v;else u.uprops[key].blocked=v;}
void probe_tile(int x,int y,int typ,unsigned flags){levl[x][y].typ=typ;levl[x][y].flags=flags;}
void probe_trap(int i,int x,int y,int typ,int seen){traps[i].tx=x;traps[i].ty=y;traps[i].ttyp=typ;traps[i].tseen=seen;}
void probe_set_monster(int i,int pm,int x,int y,int hp,int trapped){struct monst*m=monsters+i;m->data=&mons[pm];m->mx=x;m->my=y;m->mhp=hp;m->mtrapped=trapped;svl.level.monsters[x][y]=m;}
int probe_panic_code(void){return panic_code;}
int probe_occupation(void){if(!occupation)return-1;return occupation();}
static const char*fn_names[]={"dodrop","boulder_hits_pool","flooreffects","doaltarobj","trycall","polymorph_sink","teleport_sink","dosinkring","canletgo","drop","dropx","dropy","dropz","engulfer_digests_food","obj_no_longer_held","doddrop","better_not_try_to_drop_that","menudrop_split","menu_drop","u_stuck_cannot_go","dodown","doup","currentlevel_rewrite","save_currentstate","u_collide_m","familiar_level_msg","goto_level","hellish_smoke_mesg","temperature_change_msg","maybe_lvltport_feedback","final_level","schedule_goto","deferred_goto","revive_corpse","revive_mon","zombify_mon","danger_uprops","cmd_safety_prevention","donull","wipeoff","dowipe","legs_in_no_shape","set_wounded_legs","heal_legs"};
const char*probe_function_name(int i){return fn_names[i];}
int64_t probe_action(int op,int64_t a,int64_t b,int64_t c,int64_t d){int64_t values[]={a,b,c,d};anything arg={0};int64_t result=0;guarding=1;panic_code=0;if(setjmp(bail)){guarding=0;return INT64_MIN;}switch(op){
case 0:result=dodrop();break;
case 1:result=boulder_hits_pool((values[0]<0?0:pool[values[0]]),values[1],values[2],values[3]);break;
case 2:result=flooreffects((values[0]<0?0:pool[values[0]]),values[1],values[2],input_text[1]);break;
case 3:doaltarobj((values[0]<0?0:pool[values[0]]));break;
case 4:trycall((values[0]<0?0:pool[values[0]]));break;
case 5:polymorph_sink();break;
case 6:result=teleport_sink();break;
case 7:dosinkring((values[0]<0?0:pool[values[0]]));break;
case 8:result=canletgo((values[0]<0?0:pool[values[0]]),input_text[0]);break;
case 9:result=drop((values[0]<0?0:pool[values[0]]));break;
case 10:dropx((values[0]<0?0:pool[values[0]]));break;
case 11:dropy((values[0]<0?0:pool[values[0]]));break;
case 12:dropz((values[0]<0?0:pool[values[0]]),values[1]);break;
case 13:result=engulfer_digests_food((values[0]<0?0:pool[values[0]]));break;
case 14:obj_no_longer_held((values[0]<0?0:pool[values[0]]));break;
case 15:result=doddrop();break;
case 16:result=better_not_try_to_drop_that((values[0]<0?0:pool[values[0]]));break;
case 17:result=menudrop_split((values[0]<0?0:pool[values[0]]),values[1]);break;
case 18:result=menu_drop(values[0]);break;
case 19:result=u_stuck_cannot_go(input_text[0]);break;
case 20:result=dodown();break;
case 21:result=doup();break;
case 22:result=currentlevel_rewrite()!=0;break;
case 23:save_currentstate();break;
case 24:u_collide_m((values[0]<0?0:monsters+values[0]));break;
case 25:familiar_level_msg();break;
case 26:goto_level(destinations+values[0],values[1],values[2],values[3]);break;
case 27:hellish_smoke_mesg();break;
case 28:temperature_change_msg(values[0]);break;
case 29:maybe_lvltport_feedback();break;
case 30:final_level();break;
case 31:schedule_goto(destinations+values[0],values[1],input_text[0],input_text[1]);break;
case 32:deferred_goto();break;
case 33:result=revive_corpse((values[0]<0?0:pool[values[0]]));break;
case 34:arg.a_obj=a<0?0:pool[a];revive_mon(&arg,values[1]);break;
case 35:arg.a_obj=a<0?0:pool[a];zombify_mon(&arg,values[1]);break;
case 36:result=danger_uprops();break;
case 37:result=cmd_safety_prevention(input_text[0],input_text[0],input_text[0],cells+values[3]);break;
case 38:result=donull();break;
case 39:result=wipeoff();break;
case 40:result=dowipe();break;
case 41:legs_in_no_shape(input_text[0],values[1]);break;
case 42:set_wounded_legs(values[0],values[1]);break;
case 43:heal_legs(values[0]);break;
default:abort();}guarding=0;return result;}
const char*probe_snapshot(void){size_t n=0;
#define P(...) do{n+=snprintf(snapshot+n,sizeof snapshot-n,__VA_ARGS__);if(n>=sizeof snapshot)abort();}while(0)
 P("hero:%d,%d,%d,%d,%d,%d,%d,%d,%u,%u,%u,%u,%ld,%ld,%ld,%d,%d,%ld;",u.ux,u.uy,u.uz.dnum,u.uz.dlevel,u.utolev.dnum,u.utolev.dlevel,u.utotype,u.umonnum,u.utrap,u.utraptype,u.ucreamed,u.uswallow,u.uconduct.gnostic,u.uprops[WOUNDED_LEGS].intrinsic,u.uprops[WOUNDED_LEGS].extrinsic,u.atemp.a[A_DEX],program_state.in_checkpoint,gm.multi);
 P("globals:%d,%d,%d,%d,%d,%d,%d,%ld,%d,%d,%d,%d,%d,%d,%d;",flags.safe_wait,flags.verbose,flags.ins_chkpt,iflags.menu_requested,disp.botl,svc.context.mon_moving,a11y.mon_notices_blocked,svm.moves,frees,oid(gi.invent),oid(uwep),oid(uswapwep),oid(uquiver),oid(uball),oid(uchain));
 P("bhit:%d,%d;",gb.bhitpos.x,gb.bhitpos.y);
 for(int i=0;i<4;i++)P("cell:%d,%d;",i,cells[i]);
 for(int i=0;i<LAST_PROP+1;i++)P("p:%d,%ld,%ld,%ld;",i,u.uprops[i].intrinsic,u.uprops[i].extrinsic,u.uprops[i].blocked);
 for(int i=0;i<32;i++){struct obj*o=pool[i];if(!o){P("o:%d:null;",i);continue;}P("o:%d,%d,%d,%d,%d,%ld,%u,%ld,%ld,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%d;",i,o->otyp,o->where,o->ox,o->oy,o->quan,o->owt,o->owornmask,o->age,o->spe,o->cursed,o->blessed,o->bknown,o->in_use,o->globby,o->bypass,o->oerodeproof,o->corpsenm,o->how_lost,oid(o->nobj),oid(o->nexthere),oid(o->cobj),o->oeaten,mid(o->ocarry));}
 for(int i=0;i<8;i++){struct monst*m=monsters+i;P("m:%d,%d,%d,%d,%d,%d,%d,%d;",i,m->data?monsndx(m->data):NON_PM,m->mx,m->my,m->mhp,m->mhpmax,m->mtrapped,oid(m->minvent));}
 for(int i=0;i<4;i++)P("trap:%d,%d,%d,%d,%d;",i,traps[i].tx,traps[i].ty,traps[i].ttyp,traps[i].tseen);
 for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++)if(levl[x][y].typ!=ROOM||levl[x][y].flags||levl[x][y].horizontal||svl.level.objects[x][y]||svl.level.monsters[x][y])P("tile:%d,%d,%d,%u,%d,%d,%d;",x,y,levl[x][y].typ,levl[x][y].flags,levl[x][y].horizontal,oid(svl.level.objects[x][y]),mid(svl.level.monsters[x][y]));
 for(int i=0;i<NUM_OBJECTS;i++)if(objects[i].oc_name_known||objects[i].oc_uname)P("known:%d,%d,%s;",i,objects[i].oc_name_known,objects[i].oc_uname?objects[i].oc_uname:"");
 P("messages:%s:%s;",gd.dfr_pre_msg?gd.dfr_pre_msg:"",gd.dfr_post_msg?gd.dfr_post_msg:"");
#undef P
 return snapshot;}

struct attack*dmgtype_fromattack(struct permonst*p,int damage,int attack){append("digest:ptr:%d:%d;",damage,attack);callback(DEP_dmgtype_fromattack);return opts[DEP_dmgtype_fromattack]?(struct attack*)&mons[PM_PURPLE_WORM].mattk[0]:0;}

void iter_mons(void(*fn)(struct monst*)){append("iter:%d;",fn==reset_hostility);for(int i=0;i<2;i++)fn(monsters+i);callback(DEP_iter_mons);}

xint16 ledger_no(d_level*l){append("ledger:%d:%d;",l->dnum,l->dlevel);return 100+l->dlevel;}
xint16 dunlev(d_level*l){return l->dlevel;}
xint16 dunlevs_in_dungeon(d_level*l){return 20;}
schar depth(d_level*l){append("depth:%d:%d;",l->dnum,l->dlevel);return l->dlevel;}

void u_on_newpos(coordxy x,coordxy y){append("newpos:%d:%d;",x,y);u.ux=x;u.uy=y;callback(DEP_u_on_newpos);}
boolean enexto(coord*cc,coordxy x,coordxy y,struct permonst*pm){append("enexto:%d:%d;",x,y);cc->x=x+1;cc->y=y+1;callback(DEP_enexto);return !opts[DEP_enexto];}
boolean hmon(struct monst*m,struct obj*o,int type,int extra){append("hmon:%d:%d:%d:%d:pos:%d:%d;",mid(m),oid(o),type,extra,gb.bhitpos.x,gb.bhitpos.y);callback(DEP_hmon);return configured[DEP_hmon]?opts[DEP_hmon]:0;}

void bypass_objlist(struct obj*list,boolean mark){append("bypass:%d:%d;",oid(list),mark);for(struct obj*o=list;o;o=o->nobj)o->bypass=mark;callback(DEP_bypass_objlist);}
struct obj*nxt_unbypassed_obj(struct obj*list){for(struct obj*o=list;o;o=o->nobj)if(!o->bypass){o->bypass=1;append("nextunbypassed:%d;",oid(o));return o;}return 0;}

uintptr_t probe_stack_span(void){return observed_stack_max-observed_stack_min;}

struct obj*obj_nexto_xy(struct obj*o,coordxy x,coordxy y,boolean more){int choice=opts[DEP_obj_nexto_xy];opts[DEP_obj_nexto_xy]=0;append("nextglob:%d:%d:%d:%d;",oid(o),x,y,more);callback(DEP_obj_nexto_xy);return choice?pool[choice-1]:0;}
struct obj*obj_meld(struct obj**left,struct obj**right){append("meld:%d:%d;",oid(*left),oid(*right));if(opts[DEP_obj_meld]==2){dispose(*left);*left=0;}else{dispose(*right);*right=0;}callback(DEP_obj_meld);return *left?*left:*right;}
