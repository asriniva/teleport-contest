/* ZAP typed native ABI only. All naming, grammar and wish policy is JS. */
#include "hack.h"
#include <stdint.h>
#include <stdlib.h>
extern const char *const destroy_strings[7][3];
static char zap_writing_vanishes[36],zap_your[5],zap_whatbuf[50],zap_preserve_wishless[43],zap_retry_info[56],zap_retry_too[40],zap_suppress_cmdassist[64],zap_too_many[9],zap_fltxt[BUFSZ];
static char zap_charged_objs[4];
void *teleport_zap_storage(int i){return i==0?(void*)destroy_strings:i==1?zap_charged_objs:0;}
void *teleport_zap_static_storage(int i){switch(i){case 0:return zap_writing_vanishes;case 1:return zap_your;case 2:return zap_whatbuf;case 3:return zap_preserve_wishless;case 4:return zap_retry_info;case 5:return zap_retry_too;case 6:return zap_suppress_cmdassist;case 7:return zap_too_many;case 8:return zap_fltxt;default:return 0;}}
static char zap_literals[TELEPORT_ZAP_LITERAL_CAPACITY];
void *teleport_zap_literal_storage(void){return zap_literals;}
size_t teleport_zap_literal_capacity(void){return sizeof zap_literals;}
extern int teleport_zap_callback_zap_ok(struct obj*);
uintptr_t teleport_zap_callback_pointer(int i){switch(i){case 0:return(uintptr_t)bhitm;case 1:return(uintptr_t)bhito;case 2:return(uintptr_t)rn2;case 3:return(uintptr_t)rn2_on_display_rng;case 4:return(uintptr_t)xname;case 5:return(uintptr_t)teleport_zap_callback_zap_ok;default:return 0;}}
const void *teleport_zap_global(int i){switch(i){case 0:return &objects;case 1:return &u;case 2:return &gu;case 3:return &gn;case 4:return &gb;case 5:return &gv;case 6:return &mons;case 7:return &svc;case 8:return &gy;case 9:return &svq;case 10:return &sysopt;case 11:return &svl;case 12:return &iflags;case 13:return &gi;case 14:return &disp;case 15:return &uleft;case 16:return &uright;case 17:return &uarmh;case 18:return &uarmg;case 19:return &uball;case 20:return &uchain;case 21:return &svm;case 22:return &go;case 23:return &gp;case 24:return &uskin;case 25:return &svb;case 26:return &uarms;case 27:return &uwep;case 28:return &uswapwep;case 29:return &genders;case 30:return &flags;case 31:return &gz;case 32:return &WIN_MESSAGE;case 33:return &windowprocs;case 34:return &c_common_strings;case 35:return &gc;case 36:return &uarmc;case 37:return &svk;case 38:return &gs;case 39:return &svd;case 40:return &xdir;case 41:return &ydir;case 42:return &gt;case 43:return &uarm;case 44:return &uarmu;case 45:return &defsyms;case 46:return &uarmf;case 47:return &uamul;case 48:return &ublindf;case 49:return &destroy_strings;case 50:return &gm;case 51:return &cg;case 52:return &nul_glyphinfo;case 53:return &hands_obj;default:return 0;}}
unsigned teleport_zap_get_bit(const void*p,int i){switch(i){case 0:return((const struct obj*)p)->dknown;case 1:return((const struct obj*)p)->blessed;case 2:return((const struct obj*)p)->lknown;case 3:return((const struct obj*)p)->cknown;case 4:return((const struct obj*)p)->known;case 5:return((const struct obj*)p)->olocked;case 6:return((const struct obj*)p)->oeroded2;case 7:return((const struct obj*)p)->unpaid;case 8:return((const struct obj*)p)->no_charge;case 9:return((const struct obj*)p)->cursed;case 10:return((const struct obj*)p)->oeroded;case 11:return((const struct obj*)p)->bypass;case 12:return((const struct obj*)p)->obroken;case 13:return((const struct obj*)p)->recharged;case 14:return((const struct obj*)p)->oerodeproof;case 15:return((const struct obj*)p)->otrapped;case 16:return((const struct obj*)p)->tknown;case 17:return((const struct obj*)p)->in_use;case 18:return((const struct obj*)p)->lamplit;case 19:return((const struct obj*)p)->bknown;case 20:return((const struct obj*)p)->rknown;case 21:return((const struct objclass*)p)->oc_name_known;case 22:return((const struct objclass*)p)->oc_magic;case 23:return((const struct objclass*)p)->oc_charged;case 24:return((const struct objclass*)p)->oc_material;case 25:return((const struct objclass*)p)->oc_merge;case 26:return((const struct objclass*)p)->oc_big;case 27:return((const struct objclass*)p)->oc_dir;case 28:return((const struct objclass*)p)->oc_uses_known;case 29:return((const struct you*)p)->uswallow;case 30:return((const struct you*)p)->uundetected;case 31:return((const struct you*)p)->uinwater;case 32:return((const struct you*)p)->uhandedness;case 33:return((const struct u_have*)p)->questart;case 34:return((const struct monst*)p)->minvis;case 35:return((const struct monst*)p)->mpeaceful;case 36:return((const struct monst*)p)->isshk;case 37:return((const struct monst*)p)->mburied;case 38:return((const struct monst*)p)->wormno;case 39:return((const struct monst*)p)->mflee;case 40:return((const struct monst*)p)->mundetected;case 41:return((const struct monst*)p)->mfleetim;case 42:return((const struct monst*)p)->mrevived;case 43:return((const struct monst*)p)->mavenge;case 44:return((const struct monst*)p)->mleashed;case 45:return((const struct monst*)p)->mtrapped;case 46:return((const struct monst*)p)->msleeping;case 47:return((const struct monst*)p)->mfrozen;case 48:return((const struct monst*)p)->mcanmove;case 49:return((const struct monst*)p)->mcan;case 50:return((const struct monst*)p)->mcansee;case 51:return((const struct monst*)p)->mblinded;case 52:return((const struct monst*)p)->mstun;case 53:return((const struct monst*)p)->mconf;case 54:return((const struct monst*)p)->isminion;case 55:return((const struct q_score*)p)->leader_is_dead;case 56:return((const struct rm*)p)->flags;case 57:return((const struct trap*)p)->ttyp;case 58:return((const struct trap*)p)->tseen;case 59:return((const struct levelflags*)p)->sokoban_rules;default:return 0;}}
void teleport_zap_set_bit(void*p,int i,unsigned v){switch(i){case 0:((struct obj*)p)->dknown=v;break;case 1:((struct obj*)p)->blessed=v;break;case 2:((struct obj*)p)->lknown=v;break;case 3:((struct obj*)p)->cknown=v;break;case 4:((struct obj*)p)->known=v;break;case 5:((struct obj*)p)->olocked=v;break;case 6:((struct obj*)p)->oeroded2=v;break;case 7:((struct obj*)p)->unpaid=v;break;case 8:((struct obj*)p)->no_charge=v;break;case 9:((struct obj*)p)->cursed=v;break;case 10:((struct obj*)p)->oeroded=v;break;case 11:((struct obj*)p)->bypass=v;break;case 12:((struct obj*)p)->obroken=v;break;case 13:((struct obj*)p)->recharged=v;break;case 14:((struct obj*)p)->oerodeproof=v;break;case 15:((struct obj*)p)->otrapped=v;break;case 16:((struct obj*)p)->tknown=v;break;case 17:((struct obj*)p)->in_use=v;break;case 18:((struct obj*)p)->lamplit=v;break;case 19:((struct obj*)p)->bknown=v;break;case 20:((struct obj*)p)->rknown=v;break;case 21:((struct objclass*)p)->oc_name_known=v;break;case 22:((struct objclass*)p)->oc_magic=v;break;case 23:((struct objclass*)p)->oc_charged=v;break;case 24:((struct objclass*)p)->oc_material=v;break;case 25:((struct objclass*)p)->oc_merge=v;break;case 26:((struct objclass*)p)->oc_big=v;break;case 27:((struct objclass*)p)->oc_dir=v;break;case 28:((struct objclass*)p)->oc_uses_known=v;break;case 29:((struct you*)p)->uswallow=v;break;case 30:((struct you*)p)->uundetected=v;break;case 31:((struct you*)p)->uinwater=v;break;case 32:((struct you*)p)->uhandedness=v;break;case 33:((struct u_have*)p)->questart=v;break;case 34:((struct monst*)p)->minvis=v;break;case 35:((struct monst*)p)->mpeaceful=v;break;case 36:((struct monst*)p)->isshk=v;break;case 37:((struct monst*)p)->mburied=v;break;case 38:((struct monst*)p)->wormno=v;break;case 39:((struct monst*)p)->mflee=v;break;case 40:((struct monst*)p)->mundetected=v;break;case 41:((struct monst*)p)->mfleetim=v;break;case 42:((struct monst*)p)->mrevived=v;break;case 43:((struct monst*)p)->mavenge=v;break;case 44:((struct monst*)p)->mleashed=v;break;case 45:((struct monst*)p)->mtrapped=v;break;case 46:((struct monst*)p)->msleeping=v;break;case 47:((struct monst*)p)->mfrozen=v;break;case 48:((struct monst*)p)->mcanmove=v;break;case 49:((struct monst*)p)->mcan=v;break;case 50:((struct monst*)p)->mcansee=v;break;case 51:((struct monst*)p)->mblinded=v;break;case 52:((struct monst*)p)->mstun=v;break;case 53:((struct monst*)p)->mconf=v;break;case 54:((struct monst*)p)->isminion=v;break;case 55:((struct q_score*)p)->leader_is_dead=v;break;case 56:((struct rm*)p)->flags=v;break;case 57:((struct trap*)p)->ttyp=v;break;case 58:((struct trap*)p)->tseen=v;break;case 59:((struct levelflags*)p)->sokoban_rules=v;break;}}
int teleport_zap_indirect_0(uintptr_t fn ,int a0){return ((int (*)(int))fn)(a0);}
int teleport_zap_indirect_1(uintptr_t fn ,struct monst * a0,struct obj * a1){return ((int (*)(struct monst *, struct obj *))fn)(a0,a1);}
int teleport_zap_indirect_2(uintptr_t fn ,struct obj * a0,struct obj * a1){return ((int (*)(struct obj *, struct obj *))fn)(a0,a1);}
void teleport_zap_indirect_3(uintptr_t fn){((void (*)(void))fn)();}
void teleport_zap_indirect_4(uintptr_t fn ,winid a0){((void (*)(winid))fn)(a0);}
void teleport_zap_indirect_5(uintptr_t fn ,winid a0,boolean a1){((void (*)(winid, boolean))fn)(a0,a1);}
void teleport_zap_indirect_6(uintptr_t fn ,winid a0,const char * a1){((void (*)(winid, const char *))fn)(a0,a1);}
void teleport_zap_indirect_7(uintptr_t fn ,winid a0,int a1,const char * a2){((void (*)(winid, int, const char *))fn)(a0,a1,a2);}
void teleport_zap_indirect_8(uintptr_t fn ,winid a0,unsigned long a1){((void (*)(winid, unsigned long))fn)(a0,a1);}
winid teleport_zap_indirect_9(uintptr_t fn ,int a0){return ((winid (*)(int))fn)(a0);}
int teleport_zap_dep_abs(int a0){return abs(a0);}
void teleport_zap_dep_observe_object(struct obj * a0){observe_object(a0);}
void teleport_zap_dep_discover_object(int a0,boolean a1,boolean a2,boolean a3){discover_object(a0,a1,a2,a3);}
void teleport_zap_dep_update_inventory(){update_inventory();}
boolean teleport_zap_dep_resists_magm(struct monst * a0){return resists_magm(a0);}
boolean teleport_zap_dep_disguised_as_mon(struct monst * a0){return disguised_as_mon(a0);}
void teleport_zap_dep_seemimic(struct monst * a0){seemimic(a0);}
void teleport_zap_dep_shieldeff(coordxy a0,coordxy a1){shieldeff(a0,a1);}
void teleport_zap_fmt_pline_none(const char * a0){pline(a0);}
void teleport_zap_fmt_pline_i(const char * a0,int a1){pline(a0,a1);}
void teleport_zap_fmt_pline_iii(const char * a0,int a1,int a2,int a3){pline(a0,a1,a2,a3);}
void teleport_zap_fmt_pline_lp(const char * a0,long a1,const char* a2){pline(a0,a1,a2);}
void teleport_zap_fmt_pline_p(const char * a0,const char* a1){pline(a0,a1);}
void teleport_zap_fmt_pline_pp(const char * a0,const char* a1,const char* a2){pline(a0,a1,a2);}
void teleport_zap_fmt_pline_ppp(const char * a0,const char* a1,const char* a2,const char* a3){pline(a0,a1,a2,a3);}
void teleport_zap_fmt_pline_pppp(const char * a0,const char* a1,const char* a2,const char* a3,const char* a4){pline(a0,a1,a2,a3,a4);}
void teleport_zap_fmt_pline_ppppp(const char * a0,const char* a1,const char* a2,const char* a3,const char* a4,const char* a5){pline(a0,a1,a2,a3,a4,a5);}
boolean teleport_zap_dep_rng_log_enabled(){return rng_log_enabled();}
void teleport_zap_dep_rng_log_set_caller(const char * a0,int a1,const char * a2){rng_log_set_caller(a0,a1,a2);}
int teleport_zap_dep_rnd(int a0){return (rnd)(a0);}
int teleport_zap_dep_find_mac(struct monst * a0){return find_mac(a0);}
int teleport_zap_dep_d(int a0,int a1){return (d)(a0,a1);}
void teleport_zap_dep_mon_adjust_speed(struct monst * a0,int a1,struct obj * a2){mon_adjust_speed(a0,a1,a2);}
void teleport_zap_dep_check_gear_next_turn(struct monst * a0){check_gear_next_turn(a0);}
char * teleport_zap_dep_mon_nam(struct monst * a0){return mon_nam(a0);}
void teleport_zap_fmt_You_none(const char * a0){You(a0);}
void teleport_zap_fmt_You_p(const char * a0,const char* a1){You(a0,a1);}
void teleport_zap_fmt_You_pi(const char * a0,const char* a1,int a2){You(a0,a1,a2);}
void teleport_zap_fmt_You_pp(const char * a0,const char* a1,const char* a2){You(a0,a1,a2);}
void teleport_zap_dep_expels(struct monst * a0,struct permonst * a1,boolean a2){expels(a0,a1,a2);}
void teleport_zap_dep_monflee(struct monst * a0,int a1,boolean a2,boolean a3){monflee(a0,a1,a2,a3);}
void teleport_zap_dep_shieldeff_mon(struct monst * a0){shieldeff_mon(a0);}
int teleport_zap_dep_canseemon(struct monst * a0){return canseemon(a0);}
void teleport_zap_dep_bypass_obj(struct obj * a0){bypass_obj(a0);}
int teleport_zap_dep_rn2(int a0){return (rn2)(a0);}
char * teleport_zap_dep_Monnam(struct monst * a0){return Monnam(a0);}
void teleport_zap_dep_xkilled(struct monst * a0,int a1){xkilled(a0,a1);}
int teleport_zap_dep_newcham(struct monst * a0,struct permonst * a1,unsigned int a2){return newcham(a0,a1,a2);}
int teleport_zap_dep_sensemon(struct monst * a0){return sensemon(a0);}
void teleport_zap_dep_newmcorpsenm(struct monst * a0){newmcorpsenm(a0);}
boolean teleport_zap_dep_u_teleport_mon(struct monst * a0,boolean a1){return u_teleport_mon(a0,a1);}
char * teleport_zap_dep_strcpy(char * a0,const char * a1){return strcpy(a0,a1);}
void teleport_zap_dep_mon_set_minvis(struct monst * a0,boolean a1){mon_set_minvis(a0,a1);}
int teleport_zap_dep_knowninvisible(struct monst * a0){return knowninvisible(a0);}
void teleport_zap_dep_that_is_a_mimic(struct monst * a0,unsigned int a1){that_is_a_mimic(a0,a1);}
boolean teleport_zap_dep_closeholdingtrap(struct monst * a0,boolean * a1){return closeholdingtrap(a0,a1);}
boolean teleport_zap_dep_openholdingtrap(struct monst * a0,boolean * a1){return openholdingtrap(a0,a1);}
boolean teleport_zap_dep_openfallingtrap(struct monst * a0,boolean a1,boolean * a2){return openfallingtrap(a0,a1,a2);}
boolean teleport_zap_dep_m_is_steadfast(struct monst * a0){return m_is_steadfast(a0);}
void teleport_zap_dep_mhurtle(struct monst * a0,int a1,int a2,int a3){mhurtle(a0,a1,a2,a3);}
void teleport_zap_dep_wakeup(struct monst * a0,boolean a1){wakeup(a0,a1);}
void teleport_zap_dep_abuse_dog(struct monst * a0){abuse_dog(a0);}
struct obj * teleport_zap_dep_which_armor(struct monst * a0,long a1){return which_armor(a0,a1);}
char * teleport_zap_dep_s_suffix(const char * a0){return s_suffix(a0);}
char * teleport_zap_dep_distant_name(struct obj * a0,char *(*a1)(struct obj *)){return distant_name(a0,a1);}
int teleport_zap_fmt_sprintf_p(char *restrict a0,const char *restrict a1,const char* a2){return sprintf(a0,a1,a2);}
int teleport_zap_fmt_sprintf_pp(char *restrict a0,const char *restrict a1,const char* a2,const char* a3){return sprintf(a0,a1,a2,a3);}
int teleport_zap_fmt_sprintf_ppp(char *restrict a0,const char *restrict a1,const char* a2,const char* a3,const char* a4){return sprintf(a0,a1,a2,a3,a4);}
char * teleport_zap_dep_An(const char * a0){return An(a0);}
const char * teleport_zap_dep_surface(coordxy a0,coordxy a1){return surface(a0,a1);}
void teleport_zap_dep_mdrop_obj(struct monst * a0,struct obj * a1,boolean a2){mdrop_obj(a0,a1,a2);}
int teleport_zap_dep_healmon(struct monst * a0,int a1,int a2){return healmon(a0,a1,a2);}
void teleport_zap_dep_mcureblindness(struct monst * a0,boolean a1){mcureblindness(a0,a1);}
void teleport_zap_dep_set_mimic_sym(struct monst * a0){set_mimic_sym(a0);}
void teleport_zap_dep_newsym(coordxy a0,coordxy a1){newsym(a0,a1);}
void teleport_zap_dep_mimic_hit_msg(struct monst * a0,short a1){mimic_hit_msg(a0,a1);}
void teleport_zap_dep_more_experienced(int a0,int a1){more_experienced(a0,a1);}
void teleport_zap_dep_newexplevel(){newexplevel();}
int teleport_zap_dep_sgn(int a0){return sgn(a0);}
void teleport_zap_dep_adjalign(int a0){adjalign(a0);}
int teleport_zap_dep_flash_hits_mon(struct monst * a0,struct obj * a1){return flash_hits_mon(a0,a1);}
int teleport_zap_dep_sleep_monst(struct monst * a0,int a1,int a2){return sleep_monst(a0,a1,a2);}
void teleport_zap_dep_slept_monst(struct monst * a0){slept_monst(a0);}
boolean teleport_zap_dep_stone_furniture_type(unsigned int a0){return stone_furniture_type(a0);}
boolean teleport_zap_dep_stone_object_type(unsigned int a0){return stone_object_type(a0);}
void teleport_zap_dep_set_msg_xy(coordxy a0,coordxy a1){set_msg_xy(a0,a1);}
int teleport_zap_dep_monhp_per_lvl(struct monst * a0){return monhp_per_lvl(a0);}
boolean teleport_zap_dep_resists_drli(struct monst * a0){return resists_drli(a0);}
void teleport_zap_dep_killed(struct monst * a0){killed(a0);}
void teleport_zap_fmt_impossible_none(const char * a0){impossible(a0);}
void teleport_zap_fmt_impossible_i(const char * a0,int a1){impossible(a0,a1);}
void teleport_zap_fmt_impossible_p(const char * a0,const char* a1){impossible(a0,a1);}
void teleport_zap_dep_m_respond(struct monst * a0){m_respond(a0);}
void teleport_zap_dep_hot_pursuit(struct monst * a0){hot_pursuit(a0);}
void teleport_zap_dep_map_invisible(coordxy a0,coordxy a1){map_invisible(a0,a1);}
struct attack * teleport_zap_dep_dmgtype_fromattack(struct permonst * a0,int a1,int a2){return dmgtype_fromattack(a0,a1,a2);}
void teleport_zap_fmt_You_feel_none(const char * a0){You_feel(a0);}
void teleport_zap_fmt_You_feel_p(const char * a0,const char* a1){You_feel(a0,a1);}
boolean teleport_zap_dep_sticks(struct permonst * a0){return sticks(a0);}
void teleport_zap_dep_set_ustuck(struct monst * a0){set_ustuck(a0);}
void teleport_zap_dep_unstuck(struct monst * a0){unstuck(a0);}
void teleport_zap_dep_mstatusline(struct monst * a0){mstatusline(a0);}
struct obj * teleport_zap_dep_display_minventory(struct monst * a0,int a1,char * a2){return display_minventory(a0,a1,a2);}
char * teleport_zap_dep_noit_Monnam(struct monst * a0){return noit_Monnam(a0);}
struct monst * teleport_zap_dep_get_mtraits(struct obj * a0,boolean a1){return get_mtraits(a0,a1);}
struct monst * teleport_zap_dep_makemon(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){return makemon(a0,a1,a2,a3);}
void teleport_zap_dep_dealloc_monst(struct monst * a0){dealloc_monst(a0);}
boolean teleport_zap_dep_dmgtype(struct permonst * a0,int a1){return dmgtype(a0,a1);}
void teleport_zap_dep_neweshk(struct monst * a0){neweshk(a0);}
void teleport_zap_dep_replmon(struct monst * a0,struct monst * a1){replmon(a0,a1);}
void teleport_zap_dep_restore_cham(struct monst * a0){restore_cham(a0);}
int teleport_zap_dep_isok(coordxy a0,coordxy a1){return isok(a0,a1);}
struct trap * teleport_zap_dep_t_at(coordxy a0,coordxy a1){return t_at(a0,a1);}
char * teleport_zap_dep_xname(struct obj * a0){return xname(a0);}
void teleport_zap_dep_cant_finish_meal(struct obj * a0){cant_finish_meal(a0);}
boolean teleport_zap_dep_enexto(coord * a0,coordxy a1,coordxy a2,struct permonst * a3){return enexto(a0,a1,a2,a3);}
char * teleport_zap_dep_corpse_xname(struct obj * a0,const char * a1,unsigned int a2){return corpse_xname(a0,a1,a2);}
char * teleport_zap_dep_upstart(char * a0){return upstart(a0);}
boolean teleport_zap_dep_cant_revive(int * a0,boolean a1,struct obj * a2){return cant_revive(a0,a1,a2);}
void teleport_zap_dep_free_omid(struct obj * a0){free_omid(a0);}
void teleport_zap_dep_free_omonst(struct obj * a0){free_omonst(a0);}
void teleport_zap_dep_wary_dog(struct monst * a0,boolean a1){wary_dog(a0,a1);}
struct obj * teleport_zap_dep_splitobj(struct obj * a0,long a1){return splitobj(a0,a1);}
boolean teleport_zap_dep_costly_spot(coordxy a0,coordxy a1){return costly_spot(a0,a1);}
char * teleport_zap_dep_in_rooms(coordxy a0,coordxy a1,int a2){return in_rooms(a0,a1,a2);}
struct monst * teleport_zap_dep_shop_keeper(char a0){return shop_keeper(a0);}
char * teleport_zap_dep_eos(char * a0){return eos(a0);}
char * teleport_zap_dep_shk_your(char * a0,struct obj * a1){return shk_your(a0,a1);}
char * teleport_zap_dep_strcat(char * a0,const char * a1){return strcat(a0,a1);}
long teleport_zap_dep_stolen_value(struct obj * a0,coordxy a1,coordxy a2,boolean a3,boolean a4){return stolen_value(a0,a1,a2,a3,a4);}
struct monst * teleport_zap_dep_find_mid(unsigned int a0,unsigned int a1){return find_mid(a0,a1);}
void teleport_zap_dep_obj_extract_self(struct obj * a0){obj_extract_self(a0);}
int teleport_zap_dep_add_to_minv(struct monst * a0,struct obj * a1){return add_to_minv(a0,a1);}
boolean teleport_zap_dep_tamedog(struct monst * a0,struct obj * a1,boolean a2){return tamedog(a0,a1,a2);}
void teleport_zap_dep_mongone(struct monst * a0){mongone(a0);}
struct monst * teleport_zap_dep_christen_monst(struct monst * a0,const char * a1){return christen_monst(a0,a1);}
int teleport_zap_dep_eaten_stat(int a0,struct obj * a1){return eaten_stat(a0,a1);}
void teleport_zap_dep_useup(struct obj * a0){useup(a0);}
void teleport_zap_dep_delobj_core(struct obj * a0,boolean a1){delobj_core(a0,a1);}
void teleport_zap_dep_m_useup(struct monst * a0,struct obj * a1){m_useup(a0,a1);}
void teleport_zap_dep_obfree(struct obj * a0,struct obj * a1){obfree(a0,a1);}
void teleport_zap_fmt_panic_i(const char * a0,int a1){panic(a0,a1);}
boolean teleport_zap_dep_dead_species(int a0,boolean a1){return dead_species(a0,a1);}
void teleport_zap_dep_attach_egg_hatch_timeout(struct obj * a0,long a1){attach_egg_hatch_timeout(a0,a1);}
char * teleport_zap_dep_Shk_Your(char * a0,struct obj * a1){return Shk_Your(a0,a1);}
const char * teleport_zap_dep_mon_pmname(struct monst * a0){return mon_pmname(a0);}
char * teleport_zap_dep_an(const char * a0){return an(a0);}
char * teleport_zap_dep_Amonnam(struct monst * a0){return Amonnam(a0);}
void teleport_zap_dep_encumber_msg(){encumber_msg();}
void teleport_zap_dep_make_stunned(long a0,boolean a1){make_stunned(a0,a1);}
void teleport_zap_dep_costly_alteration(struct obj * a0,int a1){costly_alteration(a0,a1);}
anything * teleport_zap_dep_obj_to_any(struct obj * a0){return obj_to_any(a0);}
long teleport_zap_dep_peek_timer(short a0,union any * a1){return peek_timer(a0,a1);}
long teleport_zap_dep_stop_timer(short a0,union any * a1){return stop_timer(a0,a1);}
boolean teleport_zap_dep_start_timer(long a0,short a1,short a2,union any * a3){return start_timer(a0,a1,a2,a3);}
void teleport_zap_dep_unbless(struct obj * a0){unbless(a0);}
void teleport_zap_dep_uncurse(struct obj * a0){uncurse(a0);}
void teleport_zap_dep_free_oname(struct obj * a0){free_oname(a0);}
void teleport_zap_dep_container_weight(struct obj * a0){container_weight(a0);}
boolean teleport_zap_dep_defends(int a0,struct obj * a1){return defends(a0,a1);}
boolean teleport_zap_dep_defends_when_carried(int a0,struct obj * a1){return defends_when_carried(a0,a1);}
void teleport_zap_dep_bot(){bot();}
void teleport_zap_dep_addtobill(struct obj * a0,boolean a1,boolean a2,boolean a3){addtobill(a0,a1,a2,a3);}
void teleport_zap_dep_delobj(struct obj * a0){delobj(a0);}
char * teleport_zap_dep_a_monnam(struct monst * a0){return a_monnam(a0);}
void teleport_zap_dep_sokoban_guilt(){sokoban_guilt();}
struct obj * teleport_zap_dep_mkobj(int a0,boolean a1){return mkobj(a0,a1);}
struct obj * teleport_zap_dep_mksobj(int a0,boolean a1,boolean a2){return mksobj(a0,a1,a2);}
void teleport_zap_dep_set_corpsenm(struct obj * a0,int a1){set_corpsenm(a0,a1);}
void teleport_zap_dep_kill_egg(struct obj * a0){kill_egg(a0);}
int teleport_zap_dep_weight(struct obj * a0){return weight(a0);}
int teleport_zap_dep_can_be_hatched(int a0){return can_be_hatched(a0);}
char * teleport_zap_dep_strchr(const char * a0,int a1){return strchr(a0,a1);}
boolean teleport_zap_dep_erosion_matters(struct obj * a0){return erosion_matters(a0);}
boolean teleport_zap_dep_is_flammable(struct obj * a0){return is_flammable(a0);}
boolean teleport_zap_dep_is_rottable(struct obj * a0){return is_rottable(a0);}
boolean teleport_zap_dep_permapoisoned(struct obj * a0){return permapoisoned(a0);}
void teleport_zap_dep_o_unleash(struct obj * a0){o_unleash(a0);}
void teleport_zap_dep_delete_contents(struct obj * a0){delete_contents(a0);}
int teleport_zap_dep_rnd_class(int a0,int a1){return rnd_class(a0,a1);}
void teleport_zap_dep_fixup_oil(struct obj * a0,struct obj * a1){fixup_oil(a0,a1);}
void teleport_zap_dep_replace_object(struct obj * a0,struct obj * a1){replace_object(a0,a1);}
void teleport_zap_dep_freeinv_core(struct obj * a0){freeinv_core(a0);}
void teleport_zap_dep_addinv_core1(struct obj * a0){addinv_core1(a0);}
void teleport_zap_dep_addinv_core2(struct obj * a0){addinv_core2(a0);}
long teleport_zap_dep_wearslot(struct obj * a0){return wearslot(a0);}
void teleport_zap_dep_remove_worn_item(struct obj * a0,boolean a1){remove_worn_item(a0,a1);}
void teleport_zap_dep_setuwep(struct obj * a0){setuwep(a0);}
void teleport_zap_dep_set_twoweap(boolean a0){set_twoweap(a0);}
void teleport_zap_dep_setuswapwep(struct obj * a0){setuswapwep(a0);}
void teleport_zap_dep_setuqwep(struct obj * a0){setuqwep(a0);}
void teleport_zap_dep_setworn(struct obj * a0,long a1){setworn(a0,a1);}
void teleport_zap_dep_set_wear(struct obj * a0){set_wear(a0);}
struct obj * teleport_zap_dep_wearmask_to_obj(long a0){return wearmask_to_obj(a0);}
int teleport_zap_dep_does_block(int a0,int a1,struct rm * a2){return does_block(a0,a1,a2);}
void teleport_zap_dep_unblock_point(int a0,int a1){unblock_point(a0,a1);}
boolean teleport_zap_dep_is_pool_or_lava(coordxy a0,coordxy a1){return is_pool_or_lava(a0,a1);}
void teleport_zap_dep_block_point(int a0,int a1){block_point(a0,a1);}
long teleport_zap_dep_contained_cost(struct obj * a0,struct monst * a1,long a2,boolean a3,boolean a4){return contained_cost(a0,a1,a2,a3,a4);}
int teleport_zap_dep_inhishop(struct monst * a0){return inhishop(a0);}
void teleport_zap_dep_make_angry_shk(struct monst * a0,coordxy a1,coordxy a2){make_angry_shk(a0,a1,a2);}
char * teleport_zap_dep_Shknam(struct monst * a0){return Shknam(a0);}
void teleport_zap_fmt_Norep_none(const char * a0){Norep(a0);}
void teleport_zap_fmt_Norep_p(const char * a0,const char* a1){Norep(a0,a1);}
void teleport_zap_fmt_Norep_pp(const char * a0,const char* a1,const char* a2){Norep(a0,a1,a2);}
struct monst * teleport_zap_dep_animate_statue(struct obj * a0,coordxy a1,coordxy a2,int a3,int * a4){return animate_statue(a0,a1,a2,a3,a4);}
void teleport_zap_dep_obj_stop_timers(struct obj * a0){obj_stop_timers(a0);}
void teleport_zap_fmt_pline_The_none(const char * a0){pline_The(a0);}
void teleport_zap_fmt_pline_The_p(const char * a0,const char* a1){pline_The(a0,a1);}
void teleport_zap_fmt_pline_The_pp(const char * a0,const char* a1,const char* a2){pline_The(a0,a1,a2);}
void teleport_zap_dep_place_object(struct obj * a0,coordxy a1,coordxy a2){place_object(a0,a1,a2);}
boolean teleport_zap_dep_debugcore(const char * a0,boolean a1){return debugcore(a0,a1);}
char * teleport_zap_dep_Tobjnam(struct obj * a0,const char * a1){return Tobjnam(a0,a1);}
void teleport_zap_dep_unpunish(){unpunish();}
void teleport_zap_fmt_livelog_printf_none(long a0,const char * a1){livelog_printf(a0,a1);}
void teleport_zap_fmt_livelog_printf_p(long a0,const char * a1,const char* a2){livelog_printf(a0,a1,a2);}
void teleport_zap_fmt_livelog_printf_pp(long a0,const char * a1,const char* a2,const char* a3){livelog_printf(a0,a1,a2,a3);}
boolean teleport_zap_dep_boxlock(struct obj * a0,struct obj * a1){return boxlock(a0,a1);}
boolean teleport_zap_dep_hideunder(struct monst * a0){return hideunder(a0);}
char * teleport_zap_dep_the(const char * a0){return the(a0);}
char * teleport_zap_dep_rndmonnam(char * a0){return rndmonnam(a0);}
struct obj * teleport_zap_dep_display_cinventory(struct obj * a0){return display_cinventory(a0);}
void teleport_zap_dep_set_cknown_lknown(struct obj * a0){set_cknown_lknown(a0);}
void teleport_zap_fmt_You_hear_none(const char * a0){You_hear(a0);}
void teleport_zap_fmt_You_hear_p(const char * a0,const char* a1){You_hear(a0,a1);}
int teleport_zap_dep_breaks(struct obj * a0,coordxy a1,coordxy a2){return breaks(a0,a1,a2);}
int teleport_zap_dep_hero_breaks(struct obj * a0,coordxy a1,coordxy a2,unsigned int a3){return hero_breaks(a0,a1,a2,a3);}
void teleport_zap_dep_newsym_force(coordxy a0,coordxy a1){newsym_force(a0,a1);}
boolean teleport_zap_dep_rloco(struct obj * a0){return rloco(a0);}
void teleport_zap_dep_maybe_unhide_at(coordxy a0,coordxy a1){maybe_unhide_at(a0,a1);}
int teleport_zap_dep_corpse_revive_type(struct obj * a0){return corpse_revive_type(a0);}
char * teleport_zap_dep_cxname_singular(struct obj * a0){return cxname_singular(a0);}
char * teleport_zap_dep_noname_monnam(struct monst * a0,int a1){return noname_monnam(a0,a1);}
char * teleport_zap_dep_The(const char * a0){return The(a0);}
void teleport_zap_dep_exercise(int a0,boolean a1){exercise(a0,a1);}
struct monst * teleport_zap_dep_activate_statue_trap(struct trap * a0,coordxy a1,coordxy a2,boolean a3){return activate_statue_trap(a0,a1,a2,a3);}
void teleport_zap_dep_recreate_pile_at(coordxy a0,coordxy a1){recreate_pile_at(a0,a1);}
void teleport_zap_dep_fill_pit(coordxy a0,coordxy a1){fill_pit(a0,a1);}
void teleport_zap_dep_enlightenment(int a0,int a1){enlightenment(a0,a1);}
void teleport_zap_dep_litroom(boolean a0,struct obj * a1){litroom(a0,a1);}
int teleport_zap_dep_findit(){return findit();}
boolean teleport_zap_dep_create_critters(int a0,struct permonst * a1,boolean a2){return create_critters(a0,a1,a2);}
void teleport_zap_dep_losehp(int a0,const char * a1,schar a2){losehp(a0,a1,a2);}
void teleport_zap_dep_useupall(struct obj * a0){useupall(a0);}
boolean teleport_zap_dep_check_capacity(const char * a0){return check_capacity(a0);}
struct obj * teleport_zap_dep_getobj(const char * a0,int (*a1)(struct obj *),unsigned int a2){return getobj(a0,a1,a2);}
void teleport_zap_dep_check_unpaid(struct obj * a0){check_unpaid(a0);}
int teleport_zap_dep_getdir(const char * a0){return getdir(a0);}
char * teleport_zap_dep_killer_xname(struct obj * a0){return killer_xname(a0);}
void teleport_zap_dep_monstseesu(unsigned long a0){monstseesu(a0);}
void teleport_zap_dep_monstunseesu(unsigned long a0){monstunseesu(a0);}
void teleport_zap_dep_ugolemeffects(int a0,int a1){ugolemeffects(a0,a1);}
void teleport_zap_dep_explode(coordxy a0,coordxy a1,int a2,int a3,char a4,int a5){explode(a0,a1,a2,a3,a4,a5);}
void teleport_zap_dep_burn_away_slime(){burn_away_slime();}
boolean teleport_zap_dep_burnarmor(struct monst * a0){return burnarmor(a0);}
void teleport_zap_dep_ignite_items(struct obj * a0){ignite_items(a0);}
void teleport_zap_dep_polyself(int a0){polyself(a0);}
void teleport_zap_dep_losexp(const char * a0){losexp(a0);}
char * teleport_zap_dep_yname(struct obj * a0){return yname(a0);}
void teleport_zap_dep_incr_itimeout(long * a0,int a1){incr_itimeout(a0,a1);}
void teleport_zap_dep_self_invis_message(){self_invis_message();}
void teleport_zap_dep_speed_up(long a0){speed_up(a0);}
void teleport_zap_dep_fall_asleep(int a0,boolean a1){fall_asleep(a0,a1);}
void teleport_zap_dep_u_slow_down(){u_slow_down();}
void teleport_zap_dep_tele(){tele();}
int teleport_zap_dep_dist2(coordxy a0,coordxy a1,coordxy a2,coordxy a3){return dist2(a0,a1,a2,a3);}
void teleport_zap_fmt_urgent_pline_none(const char * a0){urgent_pline(a0);}
void teleport_zap_dep_done(int a0){done(a0);}
void teleport_zap_dep_healup(int a0,int a1,boolean a2,boolean a3){healup(a0,a1,a2,a3);}
void teleport_zap_dep_ustatusline(){ustatusline();}
int teleport_zap_dep_polymon(int a0){return polymon(a0);}
void teleport_zap_dep_fix_petrification(){fix_petrification();}
int teleport_zap_dep_merged(struct obj ** a0,struct obj ** a1){return merged(a0,a1);}
char * teleport_zap_dep_ansimpleoname(struct obj * a0){return ansimpleoname(a0);}
char * teleport_zap_dep_bare_artifactname(struct obj * a0){return bare_artifactname(a0);}
boolean teleport_zap_dep_resists_blnd(struct monst * a0){return resists_blnd(a0);}
void teleport_zap_dep_make_blinded(long a0,boolean a1){make_blinded(a0,a1);}
void teleport_zap_fmt_Your_none(const char * a0){Your(a0);}
void teleport_zap_fmt_Your_p(const char * a0,const char* a1){Your(a0,a1);}
boolean teleport_zap_dep_resists_blnd_by_arti(struct monst * a0){return resists_blnd_by_arti(a0);}
void teleport_zap_dep_find_ac(){find_ac();}
void teleport_zap_dep_rehumanize(){rehumanize();}
void teleport_zap_dep_normal_shape(struct monst * a0){normal_shape(a0);}
void teleport_zap_dep_monkilled(struct monst * a0,const char * a1,int a2){monkilled(a0,a1,a2);}
const char * teleport_zap_dep_ceiling(coordxy a0,coordxy a1){return ceiling(a0,a1);}
int teleport_zap_dep_update_mapseen_for(coordxy a0,coordxy a1){return update_mapseen_for(a0,a1);}
schar teleport_zap_dep_db_under_typ(int a0){return db_under_typ(a0);}
int teleport_zap_dep_display_binventory(coordxy a0,coordxy a1,boolean a2){return display_binventory(a0,a1,a2);}
boolean teleport_zap_dep_is_db_wall(coordxy a0,coordxy a1){return is_db_wall(a0,a1);}
boolean teleport_zap_dep_find_drawbridge(coordxy * a0,coordxy * a1){return find_drawbridge(a0,a1);}
void teleport_zap_dep_open_drawbridge(coordxy a0,coordxy a1){open_drawbridge(a0,a1);}
boolean teleport_zap_dep_on_level(d_level * a0,d_level * a1){return on_level(a0,a1);}
boolean teleport_zap_dep_ok_to_quest(){return ok_to_quest();}
int teleport_zap_dep_is_drawbridge_wall(coordxy a0,coordxy a1){return is_drawbridge_wall(a0,a1);}
void teleport_zap_dep_close_drawbridge(coordxy a0,coordxy a1){close_drawbridge(a0,a1);}
void teleport_zap_dep_destroy_drawbridge(coordxy a0,coordxy a1){destroy_drawbridge(a0,a1);}
const char * teleport_zap_dep_body_part(int a0){return body_part(a0);}
boolean teleport_zap_dep_hard_helmet(struct obj * a0){return hard_helmet(a0);}
struct obj * teleport_zap_dep_mksobj_at(int a0,coordxy a1,coordxy a2,boolean a3,boolean a4){return mksobj_at(a0,a1,a2,a3,a4);}
void teleport_zap_dep_stackobj(struct obj * a0){stackobj(a0);}
void teleport_zap_dep_dotrap(struct trap * a0,unsigned int a1){dotrap(a0,a1);}
boolean teleport_zap_dep_is_ice(coordxy a0,coordxy a1){return is_ice(a0,a1);}
struct engr * teleport_zap_dep_engr_at(coordxy a0,coordxy a1){return engr_at(a0,a1);}
boolean teleport_zap_dep_is_pool(coordxy a0,coordxy a1){return is_pool(a0,a1);}
boolean teleport_zap_dep_is_lava(coordxy a0,coordxy a1){return is_lava(a0,a1);}
char * teleport_zap_dep_makeplural(const char * a0){return makeplural(a0);}
void teleport_zap_dep_zap_dig(){zap_dig();}
schar teleport_zap_dep_acurr(int a0){return acurr(a0);}
int teleport_zap_dep_spell_skilltype(int a0){return spell_skilltype(a0);}
char * teleport_zap_dep_vtense(const char * a0,const char * a1){return vtense(a0,a1);}
void teleport_zap_dep_deltrap(struct trap * a0){deltrap(a0);}
void teleport_zap_dep_del_engr(struct engr * a0){del_engr(a0);}
char * teleport_zap_dep_random_engraving(char * a0,char * a1){return random_engraving(a0,a1);}
void teleport_zap_dep_make_engr_at(coordxy a0,coordxy a1,const char * a2,const char * a3,long a4,int a5){make_engr_at(a0,a1,a2,a3,a4,a5);}
void teleport_zap_dep_rloc_engr(struct engr * a0){rloc_engr(a0);}
void teleport_zap_dep_wipe_engr_at(coordxy a0,coordxy a1,xint16 a2,boolean a3){wipe_engr_at(a0,a1,a2,a3);}
int teleport_zap_dep_glyph_at(coordxy a0,coordxy a1){return glyph_at(a0,a1);}
void teleport_zap_dep_show_map_spot(coordxy a0,coordxy a1,boolean a2){show_map_spot(a0,a1,a2);}
void teleport_zap_dep_cvt_sdoor_to_door(struct rm * a0){cvt_sdoor_to_door(a0);}
void teleport_zap_dep_recalc_block_point(coordxy a0,coordxy a1){recalc_block_point(a0,a1);}
void teleport_zap_dep_draft_message(boolean a0){draft_message(a0);}
void teleport_zap_dep_force_decor(boolean a0){force_decor(a0);}
const char * teleport_zap_dep_trapname(int a0,boolean a1){return trapname(a0,a1);}
boolean teleport_zap_dep_Invocation_lev(d_level * a0){return Invocation_lev(a0);}
boolean teleport_zap_dep_In_mines(d_level * a0){return In_mines(a0);}
boolean teleport_zap_dep_In_hell(d_level * a0){return In_hell(a0);}
void teleport_zap_dep_tmp_at(coordxy a0,coordxy a1){tmp_at(a0,a1);}
int teleport_zap_dep_rn2_on_display_rng(int a0){return rn2_on_display_rng(a0);}
char teleport_zap_dep_inside_shop(coordxy a0,coordxy a1){return inside_shop(a0,a1);}
struct monst * teleport_zap_dep_shkcatch(struct obj * a0,coordxy a1,coordxy a2){return shkcatch(a0,a1,a2);}
void teleport_zap_dep_show_transient_light(struct obj * a0,coordxy a1,coordxy a2){show_transient_light(a0,a1,a2);}
boolean teleport_zap_dep_hits_bars(struct obj ** a0,coordxy a1,coordxy a2,coordxy a3,coordxy a4,int a5,int a6){return hits_bars(a0,a1,a2,a3,a4,a5,a6);}
char * teleport_zap_dep_Yname2(struct obj * a0){return Yname2(a0);}
char * teleport_zap_dep_otense(struct obj * a0,const char * a1){return otense(a0,a1);}
boolean teleport_zap_dep_shade_miss(struct monst * a0,struct monst * a1,struct obj * a2,boolean a3,boolean a4){return shade_miss(a0,a1,a2,a3,a4);}
void teleport_zap_dep_unmap_object(coordxy a0,coordxy a1){unmap_object(a0,a1);}
boolean teleport_zap_dep_ship_object(struct obj * a0,coordxy a1,coordxy a2,boolean a3){return ship_object(a0,a1,a2,a3);}
boolean teleport_zap_dep_doorlock(struct obj * a0,coordxy a1,coordxy a2){return doorlock(a0,a1,a2);}
void teleport_zap_dep_add_damage(coordxy a0,coordxy a1,long a2){add_damage(a0,a1,a2);}
boolean teleport_zap_dep_closed_door(coordxy a0,coordxy a1){return closed_door(a0,a1);}
struct obj * teleport_zap_dep_sobj_at(int a0,coordxy a1,coordxy a2){return sobj_at(a0,a1,a2);}
boolean teleport_zap_dep_test_move(coordxy a0,coordxy a1,coordxy a2,coordxy a3,int a4){return test_move(a0,a1,a2,a3,a4);}
void teleport_zap_dep_pay_for_damage(const char * a0,boolean a1){pay_for_damage(a0,a1);}
void teleport_zap_dep_transient_light_cleanup(){transient_light_cleanup();}
int teleport_zap_dep_xytodir(int a0,int a1){return xytodir(a0,a1);}
boolean teleport_zap_dep_throwit_mon_hit(struct obj * a0,struct monst * a1){return throwit_mon_hit(a0,a1);}
int teleport_zap_dep_dmgval(struct obj * a0,struct monst * a1){return dmgval(a0,a1);}
int teleport_zap_dep_thitu(int a0,int a1,struct obj ** a2,const char * a3){return thitu(a0,a1,a2,a3);}
void teleport_zap_dep_endmultishot(boolean a0){endmultishot(a0);}
void teleport_zap_dep_wake_nearto(coordxy a0,coordxy a1,int a2){wake_nearto(a0,a1,a2);}
boolean teleport_zap_dep_defended(struct monst * a0,int a1){return defended(a0,a1);}
boolean teleport_zap_dep_Resists_Elem(struct monst * a0,int a1){return Resists_Elem(a0,a1);}
void teleport_zap_dep_acid_damage(struct obj * a0){acid_damage(a0);}
void teleport_zap_dep_erode_armor(struct monst * a0,int a1){erode_armor(a0,a1);}
int teleport_zap_dep_disintegrate_arm(struct obj * a0){return disintegrate_arm(a0);}
void teleport_zap_dep_poisoned(const char * a0,int a1,const char * a2,int a3,boolean a4){poisoned(a0,a1,a2,a3,a4);}
const char * teleport_zap_dep_hliquid(const char * a0){return hliquid(a0);}
char * teleport_zap_dep_death_inflicted_by(char * a0,const char * a1,struct monst * a2){return death_inflicted_by(a0,a1,a2);}
char * teleport_zap_dep_strsubst(char * a0,const char * a1,const char * a2){return strsubst(a0,a1,a2);}
void teleport_zap_dep_useupf(struct obj * a0,long a1){useupf(a0,a1);}
struct obj * teleport_zap_dep_mlifesaver(struct monst * a0){return mlifesaver(a0);}
boolean teleport_zap_dep_is_quest_artifact(struct obj * a0){return is_quest_artifact(a0);}
void teleport_zap_dep_extract_from_minvent(struct monst * a0,struct obj * a1,boolean a2,boolean a3){extract_from_minvent(a0,a1,a2,a3);}
int teleport_zap_dep_zapdir_to_glyph(int a0,int a1,int a2){return zapdir_to_glyph(a0,a1,a2);}
boolean teleport_zap_dep_unmap_invisible(coordxy a0,coordxy a1){return unmap_invisible(a0,a1);}
boolean teleport_zap_dep_mon_reflects(struct monst * a0,const char * a1){return mon_reflects(a0,a1);}
boolean teleport_zap_dep_disguised_as_non_mon(struct monst * a0){return disguised_as_non_mon(a0);}
void teleport_zap_dep_nomul(int a0){nomul(a0);}
void teleport_zap_fmt_pline_dir_p(int a0,const char * a1,const char* a2){pline_dir(a0,a1,a2);}
boolean teleport_zap_dep_ureflects(const char * a0,const char * a1){return ureflects(a0,a1);}
void teleport_zap_dep_stop_occupation(){stop_occupation();}
void teleport_zap_dep_spot_stop_timers(coordxy a0,coordxy a1,short a2){spot_stop_timers(a0,a1,a2);}
void teleport_zap_dep_trap_ice_effects(coordxy a0,coordxy a1,boolean a2){trap_ice_effects(a0,a1,a2);}
void teleport_zap_dep_obj_ice_effects(coordxy a0,coordxy a1,boolean a2){obj_ice_effects(a0,a1,a2);}
void teleport_zap_dep_unearth_objs(int a0,int a1){unearth_objs(a0,a1);}
void teleport_zap_dep_vision_recalc(int a0){vision_recalc(a0);}
boolean teleport_zap_dep_boulder_hits_pool(struct obj * a0,coordxy a1,coordxy a2,boolean a3){return boulder_hits_pool(a0,a1,a2,a3);}
void teleport_zap_dep_spoteffects(boolean a0){spoteffects(a0);}
int teleport_zap_dep_minliquid(struct monst * a0){return minliquid(a0);}
anything * teleport_zap_dep_long_to_any(long a0){return long_to_any(a0);}
boolean teleport_zap_dep_delfloortrap(struct trap * a0){return delfloortrap(a0);}
NhRegion * teleport_zap_dep_create_gas_cloud(coordxy a0,coordxy a1,int a2,int a3){return create_gas_cloud(a0,a1,a2,a3);}
struct trap * teleport_zap_dep_maketrap(coordxy a0,coordxy a1,int a2){return maketrap(a0,a1,a2);}
int teleport_zap_dep_mintrap(struct monst * a0,unsigned int a1){return mintrap(a0,a1);}
void teleport_zap_dep_dryup(coordxy a0,coordxy a1,boolean a2){dryup(a0,a1,a2);}
boolean teleport_zap_dep_is_moat(coordxy a0,coordxy a1){return is_moat(a0,a1);}
const char * teleport_zap_dep_waterbody_name(coordxy a0,coordxy a1){return waterbody_name(a0,a1);}
void teleport_zap_dep_fix_wall_spines(coordxy a0,coordxy a1,coordxy a2,coordxy a3){fix_wall_spines(a0,a1,a2,a3);}
void teleport_zap_dep_bury_objs(int a0,int a1){bury_objs(a0,a1);}
void teleport_zap_dep_set_uinwater(int a0){set_uinwater(a0);}
void teleport_zap_dep_docrt(){docrt();}
void teleport_zap_dep_reset_utrap(boolean a0){reset_utrap(a0);}
void teleport_zap_dep_set_utrap(unsigned int a0,unsigned int a1){set_utrap(a0,a1);}
long teleport_zap_dep_spot_time_left(coordxy a0,coordxy a1,short a2){return spot_time_left(a0,a1,a2);}
void teleport_zap_dep_dissolve_bars(coordxy a0,coordxy a1){dissolve_bars(a0,a1);}
boolean teleport_zap_dep_picking_at(coordxy a0,coordxy a1){return picking_at(a0,a1);}
void teleport_zap_dep_reset_pick(){reset_pick();}
unsigned long teleport_zap_dep_strlen(const char * a0){return strlen(a0);}
boolean teleport_zap_dep_billable(struct monst ** a0,struct obj * a1,char a2,boolean a3){return billable(a0,a1,a2,a3);}
char * teleport_zap_dep_shkname(struct monst * a0){return shkname(a0);}
int teleport_zap_dep_breakobj(struct obj * a0,coordxy a1,coordxy a2,boolean a3,boolean a4){return breakobj(a0,a1,a2,a3,a4);}
void teleport_zap_dep_dealloc_oextra(struct obj * a0){dealloc_oextra(a0);}
const char * teleport_zap_dep_cloak_simple_name(struct obj * a0){return cloak_simple_name(a0);}
const char * teleport_zap_dep_suit_simple_name(struct obj * a0){return suit_simple_name(a0);}
const char * teleport_zap_dep_shirt_simple_name(struct obj * a0){return shirt_simple_name(a0);}
const char * teleport_zap_dep_helm_simple_name(struct obj * a0){return helm_simple_name(a0);}
const char * teleport_zap_dep_gloves_simple_name(struct obj * a0){return gloves_simple_name(a0);}
const char * teleport_zap_dep_boots_simple_name(struct obj * a0){return boots_simple_name(a0);}
const char * teleport_zap_dep_shield_simple_name(struct obj * a0){return shield_simple_name(a0);}
char * teleport_zap_dep_simpleonames(struct obj * a0){return simpleonames(a0);}
const char * teleport_zap_dep_hcolor(const char * a0){return hcolor(a0);}
void teleport_zap_dep_recharge(struct obj * a0,int a1){recharge(a0,a1);}
void teleport_zap_dep_potionbreathe(struct obj * a0){potionbreathe(a0);}
void teleport_zap_dep_Ring_gone(struct obj * a0){Ring_gone(a0);}
void teleport_zap_dep_setnotworn(struct obj * a0){setnotworn(a0);}
void teleport_zap_dep_bypass_objlist(struct obj * a0,boolean a1){bypass_objlist(a0,a1);}
struct obj * teleport_zap_dep_nxt_unbypassed_obj(struct obj * a0){return nxt_unbypassed_obj(a0);}
int teleport_zap_dep_strncmpi(const char * a0,const char * a1,int a2){return strncmpi(a0,a1,a2);}
void teleport_zap_dep_free(void * a0){free(a0);}
long * teleport_zap_dep_alloc(unsigned int a0){return alloc(a0);}
void teleport_zap_dep_add_menu(winid a0,const glyph_info * a1,const union any * a2,char a3,char a4,int a5,int a6,const char * a7,unsigned int a8){add_menu(a0,a1,a2,a3,a4,a5,a6,a7,a8);}
int teleport_zap_dep_select_menu(winid a0,int a1,menu_item ** a2){return select_menu(a0,a1,a2);}
void teleport_zap_dep_getlin(const char * a0,char * a1){getlin(a0,a1);}
char * teleport_zap_dep_mungspaces(char * a0){return mungspaces(a0);}
struct obj * teleport_zap_dep_readobjnam(char * a0,struct obj * a1){return readobjnam(a0,a1);}
void teleport_zap_dep_artifact_origin(struct obj * a0,unsigned int a1){artifact_origin(a0,a1);}
char * teleport_zap_dep_doname(struct obj * a0){return doname(a0);}
void teleport_zap_fmt_nh_snprintf_pp(const char * a0,int a1,char * a2,size_t a3,const char * a4,const char* a5,const char* a6){nh_snprintf(a0,a1,a2,a3,a4,a5,a6);}
boolean teleport_zap_dep_u_safe_from_fatal_corpse(struct obj * a0,int a1){return u_safe_from_fatal_corpse(a0,a1);}
char * teleport_zap_dep_aobjnam(struct obj * a0,const char * a1){return aobjnam(a0,a1);}
struct obj * teleport_zap_dep_hold_another_object(struct obj * a0,const char * a1,const char * a2,const char * a3){return hold_another_object(a0,a1,a2,a3);}
const char * teleport_zap_dep_rnd_hallublast(){return rnd_hallublast();}
void teleport_zap_assertion(const char*condition,const char*file,unsigned line,const char*fn){__assert_fail(condition,file,line,fn);}
