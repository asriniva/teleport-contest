/* OBJNAM typed native ABI only. All naming, grammar and wish policy is JS. */
#include "hack.h"
#include <stdint.h>
#include <stdlib.h>
static char objnam_buffers[12][BUFSZ];
static char objnam_and_contents[18],objnam_compound_start[3],objnam_detect[8],objnam_detection[11],objnam_gauntlets[10],objnam_shoes[6];
void *teleport_objnam_storage(int i){return i==0?(void*)objnam_buffers:0;}
void *teleport_objnam_static_storage(int i){switch(i){case 0:return objnam_and_contents;case 1:return objnam_compound_start;case 2:return objnam_detect;case 3:return objnam_detection;case 4:return objnam_gauntlets;case 5:return objnam_shoes;default:return 0;}}
static char objnam_literals[TELEPORT_OBJNAM_LITERAL_CAPACITY];
void *teleport_objnam_literal_storage(void){return objnam_literals;}
size_t teleport_objnam_literal_capacity(void){return sizeof objnam_literals;}
char *teleport_objnam_formatter(uintptr_t fn,struct obj *obj){return ((char *(*)(struct obj*))fn)(obj);}
uintptr_t teleport_objnam_callback_pointer(int i){switch(i){case 0:return(uintptr_t)xname;case 1:return(uintptr_t)cxname;default:return 0;}}
const void *teleport_objnam_global(int i){switch(i){case 0:return &objects;case 1:return &obj_descr;case 2:return &gu;case 3:return &program_state;case 4:return &iflags;case 5:return &u;case 6:return &gv;case 7:return &gd;case 8:return &svp;case 9:return &gf;case 10:return &gx;case 11:return &flags;case 12:return &mons;case 13:return &cg;case 14:return &gm;case 15:return &uskin;case 16:return &uarmg;case 17:return &svm;case 18:return &genders;case 19:return &uwep;case 20:return &gw;case 21:return &vowels;case 22:return &svb;case 23:return &svl;case 24:return &hands_obj;case 25:return &svd;case 26:return &svc;case 27:return &disp;case 28:return &ynchars;case 29:return &c_common_strings;default:return 0;}}
unsigned teleport_objnam_get_bit(const void*p,int i){switch(i){case 0:return((const struct objclass*)p)->oc_name_known;case 1:return((const struct objclass*)p)->oc_material;case 2:return((const struct objclass*)p)->oc_unique;case 3:return((const struct objclass*)p)->oc_uses_known;case 4:return((const struct objclass*)p)->oc_magic;case 5:return((const struct objclass*)p)->oc_charged;case 6:return((const struct objclass*)p)->oc_big;case 7:return((const struct objclass*)p)->oc_nowish;case 8:return((const struct objclass*)p)->oc_merge;case 9:return((const struct obj*)p)->known;case 10:return((const struct obj*)p)->bknown;case 11:return((const struct obj*)p)->dknown;case 12:return((const struct obj*)p)->otrapped;case 13:return((const struct obj*)p)->globby;case 14:return((const struct obj*)p)->oeroded;case 15:return((const struct obj*)p)->blessed;case 16:return((const struct obj*)p)->cursed;case 17:return((const struct obj*)p)->rknown;case 18:return((const struct obj*)p)->oeroded2;case 19:return((const struct obj*)p)->oerodeproof;case 20:return((const struct obj*)p)->cknown;case 21:return((const struct obj*)p)->lknown;case 22:return((const struct obj*)p)->tknown;case 23:return((const struct obj*)p)->obroken;case 24:return((const struct obj*)p)->olocked;case 25:return((const struct obj*)p)->greased;case 26:return((const struct obj*)p)->lamplit;case 27:return((const struct obj*)p)->recharged;case 28:return((const struct obj*)p)->unpaid;case 29:return((const struct obj*)p)->no_charge;case 30:return((const struct you*)p)->uhandedness;case 31:return((const struct you*)p)->uinwater;case 32:return((const struct rm*)p)->flags;case 33:return((const struct rm*)p)->horizontal;case 34:return((const struct trap*)p)->ttyp;default:return 0;}}
void teleport_objnam_set_bit(void*p,int i,unsigned v){switch(i){case 0:((struct objclass*)p)->oc_name_known=v;break;case 1:((struct objclass*)p)->oc_material=v;break;case 2:((struct objclass*)p)->oc_unique=v;break;case 3:((struct objclass*)p)->oc_uses_known=v;break;case 4:((struct objclass*)p)->oc_magic=v;break;case 5:((struct objclass*)p)->oc_charged=v;break;case 6:((struct objclass*)p)->oc_big=v;break;case 7:((struct objclass*)p)->oc_nowish=v;break;case 8:((struct objclass*)p)->oc_merge=v;break;case 9:((struct obj*)p)->known=v;break;case 10:((struct obj*)p)->bknown=v;break;case 11:((struct obj*)p)->dknown=v;break;case 12:((struct obj*)p)->otrapped=v;break;case 13:((struct obj*)p)->globby=v;break;case 14:((struct obj*)p)->oeroded=v;break;case 15:((struct obj*)p)->blessed=v;break;case 16:((struct obj*)p)->cursed=v;break;case 17:((struct obj*)p)->rknown=v;break;case 18:((struct obj*)p)->oeroded2=v;break;case 19:((struct obj*)p)->oerodeproof=v;break;case 20:((struct obj*)p)->cknown=v;break;case 21:((struct obj*)p)->lknown=v;break;case 22:((struct obj*)p)->tknown=v;break;case 23:((struct obj*)p)->obroken=v;break;case 24:((struct obj*)p)->olocked=v;break;case 25:((struct obj*)p)->greased=v;break;case 26:((struct obj*)p)->lamplit=v;break;case 27:((struct obj*)p)->recharged=v;break;case 28:((struct obj*)p)->unpaid=v;break;case 29:((struct obj*)p)->no_charge=v;break;case 30:((struct you*)p)->uhandedness=v;break;case 31:((struct you*)p)->uinwater=v;break;case 32:((struct rm*)p)->flags=v;break;case 33:((struct rm*)p)->horizontal=v;break;case 34:((struct trap*)p)->ttyp=v;break;}}
unsigned long teleport_objnam_dep_strlen(const char * a0){return strlen(a0);}
void teleport_objnam_fmt_impossible_none(const char * a0){impossible(a0);}
void teleport_objnam_fmt_impossible_i(const char * a0,int a1){impossible(a0,a1);}
void teleport_objnam_fmt_impossible_p(const char * a0,const char* a1){impossible(a0,a1);}
void teleport_objnam_fmt_impossible_pu(const char * a0,const char* a1,unsigned a2){impossible(a0,a1,a2);}
void teleport_objnam_fmt_impossible_u(const char * a0,unsigned a1){impossible(a0,a1);}
void teleport_objnam_fmt_impossible_uu(const char * a0,unsigned a1,unsigned a2){impossible(a0,a1,a2);}
void teleport_objnam_fmt_impossible_uuu(const char * a0,unsigned a1,unsigned a2,unsigned a3){impossible(a0,a1,a2,a3);}
void teleport_objnam_dep_copynchars(char * a0,const char * a1,int a2){copynchars(a0,a1,a2);}
char * teleport_objnam_dep_strcpy(char * a0,const char * a1){return strcpy(a0,a1);}
char * teleport_objnam_dep_eos(char * a0){return eos(a0);}
int teleport_objnam_fmt_sprintf_i(char *restrict a0,const char *restrict a1,int a2){return sprintf(a0,a1,a2);}
int teleport_objnam_fmt_sprintf_iii(char *restrict a0,const char *restrict a1,int a2,int a3,int a4){return sprintf(a0,a1,a2,a3,a4);}
int teleport_objnam_fmt_sprintf_ip(char *restrict a0,const char *restrict a1,int a2,const char* a3){return sprintf(a0,a1,a2,a3);}
int teleport_objnam_fmt_sprintf_l(char *restrict a0,const char *restrict a1,long a2){return sprintf(a0,a1,a2);}
int teleport_objnam_fmt_sprintf_lp(char *restrict a0,const char *restrict a1,long a2,const char* a3){return sprintf(a0,a1,a2,a3);}
int teleport_objnam_fmt_sprintf_p(char *restrict a0,const char *restrict a1,const char* a2){return sprintf(a0,a1,a2);}
int teleport_objnam_fmt_sprintf_pip(char *restrict a0,const char *restrict a1,const char* a2,int a3,const char* a4){return sprintf(a0,a1,a2,a3,a4);}
int teleport_objnam_fmt_sprintf_pp(char *restrict a0,const char *restrict a1,const char* a2,const char* a3){return sprintf(a0,a1,a2,a3);}
char * teleport_objnam_dep_strcat(char * a0,const char * a1){return strcat(a0,a1);}
char * teleport_objnam_dep_strstri(const char * a0,const char * a1){return strstri(a0,a1);}
boolean teleport_objnam_dep_get_obj_location(struct obj * a0,coordxy * a1,coordxy * a2,int a3){return get_obj_location(a0,a1,a2,a3);}
int teleport_objnam_dep_dist2(coordxy a0,coordxy a1,coordxy a2,coordxy a3){return dist2(a0,a1,a2,a3);}
int teleport_objnam_dep_strcmp(const char * a0,const char * a1){return strcmp(a0,a1);}
unsigned int teleport_objnam_dep_Strlen_(const char * a0,const char * a1,int a2){return Strlen_(a0,a1,a2);}
int teleport_objnam_dep_strncmp(const char * a0,const char * a1,unsigned long a2){return strncmp(a0,a1,a2);}
char * teleport_objnam_dep_strchr(const char * a0,int a1){return strchr(a0,a1);}
void teleport_objnam_fmt_panic_none(const char * a0){panic(a0);}
void teleport_objnam_fmt_panic_ii(const char * a0,int a1,int a2){panic(a0,a1,a2);}
void teleport_objnam_dep_observe_object(struct obj * a0){observe_object(a0);}
void teleport_objnam_dep_find_artifact(struct obj * a0){find_artifact(a0);}
boolean teleport_objnam_dep_permapoisoned(struct obj * a0){return permapoisoned(a0);}
const char * teleport_objnam_dep_obj_pmname(struct obj * a0){return obj_pmname(a0);}
void teleport_objnam_fmt_nh_snprintf_i(const char * a0,int a1,char * a2,size_t a3,const char * a4,int a5){nh_snprintf(a0,a1,a2,a3,a4,a5);}
void teleport_objnam_fmt_nh_snprintf_ii(const char * a0,int a1,char * a2,size_t a3,const char * a4,int a5,int a6){nh_snprintf(a0,a1,a2,a3,a4,a5,a6);}
void teleport_objnam_fmt_nh_snprintf_ip(const char * a0,int a1,char * a2,size_t a3,const char * a4,int a5,const char* a6){nh_snprintf(a0,a1,a2,a3,a4,a5,a6);}
void teleport_objnam_fmt_nh_snprintf_lp(const char * a0,int a1,char * a2,size_t a3,const char * a4,long a5,const char* a6){nh_snprintf(a0,a1,a2,a3,a4,a5,a6);}
void teleport_objnam_fmt_nh_snprintf_p(const char * a0,int a1,char * a2,size_t a3,const char * a4,const char* a5){nh_snprintf(a0,a1,a2,a3,a4,a5);}
void teleport_objnam_fmt_nh_snprintf_pp(const char * a0,int a1,char * a2,size_t a3,const char * a4,const char* a5,const char* a6){nh_snprintf(a0,a1,a2,a3,a4,a5,a6);}
void teleport_objnam_fmt_nh_snprintf_pppp(const char * a0,int a1,char * a2,size_t a3,const char * a4,const char* a5,const char* a6,const char* a7,const char* a8){nh_snprintf(a0,a1,a2,a3,a4,a5,a6,a7,a8);}
void teleport_objnam_fmt_nh_snprintf_u(const char * a0,int a1,char * a2,size_t a3,const char * a4,unsigned a5){nh_snprintf(a0,a1,a2,a3,a4,a5);}
char * teleport_objnam_dep_strncat(char * a0,const char * a1,unsigned long a2){return strncat(a0,a1,a2);}
void teleport_objnam_dep_tin_details(struct obj * a0,int a1,char * a2){tin_details(a0,a1,a2);}
void * teleport_objnam_dep_memcpy(void * a0,const void * a1,unsigned long a2){return memcpy(a0,a1,a2);}
void teleport_objnam_dep_paniclog(const char * a0,const char * a1){paniclog(a0,a1);}
char * teleport_objnam_dep_tshirt_text(struct obj * a0,char * a1){return tshirt_text(a0,a1);}
char * teleport_objnam_dep_apron_text(struct obj * a0,char * a1){return apron_text(a0,a1);}
const char * teleport_objnam_dep_candy_wrapper_text(struct obj * a0){return candy_wrapper_text(a0);}
char * teleport_objnam_dep_hawaiian_motif(struct obj * a0,char * a1){return hawaiian_motif(a0,a1);}
char teleport_objnam_dep_lowc(char a0){return lowc(a0);}
int teleport_objnam_dep_strncmpi(const char * a0,const char * a1,int a2){return strncmpi(a0,a1,a2);}
const char * teleport_objnam_dep_ordin(int a0){return ordin(a0);}
boolean teleport_objnam_dep_is_flammable(struct obj * a0){return is_flammable(a0);}
boolean teleport_objnam_dep_is_rottable(struct obj * a0){return is_rottable(a0);}
const char * teleport_objnam_dep_artifact_name(const char * a0,short * a1,boolean a2){return artifact_name(a0,a1,a2);}
long teleport_objnam_dep_count_contents(struct obj * a0,boolean a1,boolean a2,boolean a3,boolean a4){return count_contents(a0,a1,a2,a3,a4);}
boolean teleport_objnam_dep_doffing(struct obj * a0){return doffing(a0);}
boolean teleport_objnam_dep_donning(struct obj * a0){return donning(a0);}
boolean teleport_objnam_dep_artifact_light(struct obj * a0){return artifact_light(a0);}
const char * teleport_objnam_dep_arti_light_description(struct obj * a0){return arti_light_description(a0);}
struct monst * teleport_objnam_dep_find_mid(unsigned int a0,unsigned int a1){return find_mid(a0,a1);}
char * teleport_objnam_dep_noit_mon_nam(struct monst * a0){return noit_mon_nam(a0);}
const char * teleport_objnam_dep_mon_pmname(struct monst * a0){return mon_pmname(a0);}
long teleport_objnam_dep_peek_timer(short a0,union any * a1){return peek_timer(a0,a1);}
const char * teleport_objnam_dep_body_part(int a0){return body_part(a0);}
const char * teleport_objnam_dep_glow_verb(int a0,boolean a1){return glow_verb(a0,a1);}
const char * teleport_objnam_dep_glow_color(int a0){return glow_color(a0);}
boolean teleport_objnam_dep_is_unpaid(struct obj * a0){return is_unpaid(a0);}
long teleport_objnam_dep_unpaid_cost(struct obj * a0,uchar a1){return unpaid_cost(a0,a1);}
const char * teleport_objnam_dep_currency(long a0){return currency(a0);}
void teleport_objnam_dep_record_price_quote(int a0,unsigned long a1,boolean a2){record_price_quote(a0,a1,a2);}
long teleport_objnam_dep_get_cost_of_shop_item(struct obj * a0,int * a1){return get_cost_of_shop_item(a0,a1);}
void teleport_objnam_dep_append_price_quote(char * a0,char ** a1,int a2){append_price_quote(a0,a1,a2);}
boolean teleport_objnam_dep_undiscovered_artifact(xint16 a0){return undiscovered_artifact(a0);}
char * teleport_objnam_dep_s_suffix(const char * a0){return s_suffix(a0);}
char * teleport_objnam_dep_mungspaces(char * a0){return mungspaces(a0);}
boolean teleport_objnam_dep_digit(char a0){return digit(a0);}
char * teleport_objnam_dep_strncpy(char * a0,const char * a1,unsigned long a2){return strncpy(a0,a1,a2);}
char teleport_objnam_dep_highc(char a0){return highc(a0);}
boolean teleport_objnam_dep_CapitalMon(const char * a0){return CapitalMon(a0);}
char * teleport_objnam_dep_strrchr(const char * a0,int a1){return strrchr(a0,a1);}
char * teleport_objnam_dep_shk_your(char * a0,struct obj * a1){return shk_your(a0,a1);}
const char * teleport_objnam_dep_artiname(int a0){return artiname(a0);}
char * teleport_objnam_dep_strcasecpy(char * a0,const char * a1){return strcasecpy(a0,a1);}
boolean teleport_objnam_dep_letter(char a0){return letter(a0);}
boolean teleport_objnam_dep_fuzzymatch(const char * a0,const char * a1,const char * a2,boolean a3){return fuzzymatch(a0,a1,a2,a3);}
char * teleport_objnam_dep_strsubst(char * a0,const char * a1,const char * a2){return strsubst(a0,a1,a2);}
boolean teleport_objnam_dep_rng_log_enabled(){return rng_log_enabled();}
void teleport_objnam_dep_rng_log_set_caller(const char * a0,int a1,const char * a2){rng_log_set_caller(a0,a1,a2);}
int teleport_objnam_dep_rn2(int a0){return (rn2)(a0);}
void * teleport_objnam_dep_memset(void * a0,int a1,unsigned long a2){return memset(a0,a1,a2);}
char * teleport_objnam_dep_strstr(const char * a0,const char * a1){return strstr(a0,a1);}
const char * teleport_objnam_dep_trapname(int a0,boolean a1){return trapname(a0,a1);}
boolean teleport_objnam_dep_str_start_is(const char * a0,const char * a1,boolean a2){return str_start_is(a0,a1,a2);}
boolean teleport_objnam_dep_Can_fall_thru(d_level * a0){return Can_fall_thru(a0);}
struct trap * teleport_objnam_dep_maketrap(coordxy a0,coordxy a1,int a2){return maketrap(a0,a1,a2);}
void teleport_objnam_fmt_pline_none(const char * a0){pline(a0);}
void teleport_objnam_fmt_pline_p(const char * a0,const char* a1){pline(a0,a1);}
void teleport_objnam_fmt_pline_pp(const char * a0,const char* a1,const char* a2){pline(a0,a1,a2);}
void teleport_objnam_dep_del_engr_at(coordxy a0,coordxy a1){del_engr_at(a0,a1);}
const char * teleport_objnam_dep_waterbody_name(coordxy a0,coordxy a1){return waterbody_name(a0,a1);}
void teleport_objnam_dep_water_damage_chain(struct obj * a0,boolean a1){water_damage_chain(a0,a1);}
boolean teleport_objnam_dep_pooleffects(boolean a0){return pooleffects(a0);}
int teleport_objnam_dep_fire_damage_chain(struct obj * a0,boolean a1,boolean a2,coordxy a3,coordxy a4){return fire_damage_chain(a0,a1,a2,a3,a4);}
void teleport_objnam_dep_start_melt_ice_timeout(coordxy a0,coordxy a1,long a2){start_melt_ice_timeout(a0,a1,a2);}
char * teleport_objnam_dep_ice_descr(coordxy a0,coordxy a1,char * a2){return ice_descr(a0,a1,a2);}
char * teleport_objnam_dep_upstart(char * a0){return upstart(a0);}
const char * teleport_objnam_dep_align_str(aligntyp a0){return align_str(a0);}
void teleport_objnam_dep_make_grave(coordxy a0,coordxy a1,const char * a2){make_grave(a0,a1,a2);}
boolean teleport_objnam_dep_on_level(d_level * a0,d_level * a1){return on_level(a0,a1);}
int teleport_objnam_dep_isok(coordxy a0,coordxy a1){return isok(a0,a1);}
void teleport_objnam_dep_fix_wall_spines(coordxy a0,coordxy a1,coordxy a2,coordxy a3){fix_wall_spines(a0,a1,a2,a3);}
boolean teleport_objnam_dep_is_pool_or_lava(coordxy a0,coordxy a1){return is_pool_or_lava(a0,a1);}
void teleport_objnam_dep_count_level_features(){count_level_features();}
struct trap * teleport_objnam_dep_t_at(coordxy a0,coordxy a1){return t_at(a0,a1);}
void teleport_objnam_dep_deltrap(struct trap * a0){deltrap(a0);}
void teleport_objnam_dep_feel_newsym(coordxy a0,coordxy a1){feel_newsym(a0,a1);}
boolean teleport_objnam_dep_is_pool(coordxy a0,coordxy a1){return is_pool(a0,a1);}
void teleport_objnam_dep_set_uinwater(int a0){set_uinwater(a0);}
void teleport_objnam_dep_docrt(){docrt();}
boolean teleport_objnam_dep_is_lava(coordxy a0,coordxy a1){return is_lava(a0,a1);}
void teleport_objnam_dep_reset_utrap(boolean a0){reset_utrap(a0);}
void teleport_objnam_dep_recalc_block_point(coordxy a0,coordxy a1){recalc_block_point(a0,a1);}
boolean teleport_objnam_dep_is_ice(coordxy a0,coordxy a1){return is_ice(a0,a1);}
void teleport_objnam_dep_spot_stop_timers(coordxy a0,coordxy a1,short a2){spot_stop_timers(a0,a1,a2);}
void teleport_objnam_dep_switch_terrain(){switch_terrain();}
int teleport_objnam_dep_atoi(const char * a0){return atoi(a0);}
int teleport_objnam_dep_rnd(int a0){return (rnd)(a0);}
int teleport_objnam_dep_abs(int a0){return abs(a0);}
int teleport_objnam_dep_name_to_mon(const char * a0,int * a1){return name_to_mon(a0,a1);}
int teleport_objnam_dep_tin_variety_txt(char * a0,int * a1){return tin_variety_txt(a0,a1);}
int teleport_objnam_dep_name_to_monplus(const char * a0,const char ** a1,int * a2){return name_to_monplus(a0,a1,a2);}
struct obj * teleport_objnam_dep_mksobj(int a0,boolean a1,boolean a2){return mksobj(a0,a1,a2);}
int teleport_objnam_dep_weight(struct obj * a0){return weight(a0);}
int teleport_objnam_dep_def_char_to_objclass(char a0){return def_char_to_objclass(a0);}
struct obj * teleport_objnam_dep_mkobj(int a0,boolean a1){return mkobj(a0,a1);}
char teleport_objnam_dep_yn_function(const char * a0,const char * a1,char a2,boolean a3){return yn_function(a0,a1,a2,a3);}
void teleport_objnam_dep_place_object(struct obj * a0,coordxy a1,coordxy a2){place_object(a0,a1,a2);}
void teleport_objnam_dep_begin_burn(struct obj * a0,boolean a1){begin_burn(a0,a1);}
void teleport_objnam_dep_obj_extract_self(struct obj * a0){obj_extract_self(a0);}
int teleport_objnam_dep_counter_were(int a0){return counter_were(a0);}
boolean teleport_objnam_dep_dead_species(int a0,boolean a1){return dead_species(a0,a1);}
int teleport_objnam_dep_genus(int a0,int a1){return genus(a0,a1);}
void teleport_objnam_dep_set_corpsenm(struct obj * a0,int a1){set_corpsenm(a0,a1);}
int teleport_objnam_dep_zombie_form(struct permonst * a0){return zombie_form(a0);}
anything * teleport_objnam_dep_obj_to_any(struct obj * a0){return obj_to_any(a0);}
boolean teleport_objnam_dep_start_timer(long a0,short a1,short a2,union any * a3){return start_timer(a0,a1,a2,a3);}
int teleport_objnam_dep_can_be_hatched(int a0){return can_be_hatched(a0);}
void teleport_objnam_dep_delete_contents(struct obj * a0){delete_contents(a0);}
void teleport_objnam_dep_curse(struct obj * a0){curse(a0);}
void teleport_objnam_dep_set_tin_variety(struct obj * a0,int a1){set_tin_variety(a0,a1);}
const char * teleport_objnam_dep_lookup_novel(const char * a0,int * a1){return lookup_novel(a0,a1);}
struct obj * teleport_objnam_dep_oname(struct obj * a0,const char * a1,unsigned int a2){return oname(a0,a1,a2);}
boolean teleport_objnam_dep_is_quest_artifact(struct obj * a0){return is_quest_artifact(a0);}
int teleport_objnam_dep_nartifact_exist(){return nartifact_exist();}
const char * teleport_objnam_dep_safe_oname(struct obj * a0){return safe_oname(a0);}
void teleport_objnam_dep_artifact_exists(struct obj * a0,const char * a1,boolean a2,unsigned int a3){artifact_exists(a0,a1,a2,a3);}
void teleport_objnam_dep_obfree(struct obj * a0,struct obj * a1){obfree(a0,a1);}
unsigned int teleport_objnam_dep_obj_nutrition(struct obj * a0){return obj_nutrition(a0);}
void teleport_objnam_dep_consume_oeaten(struct obj * a0,int a1){consume_oeaten(a0,a1);}
boolean teleport_objnam_dep_hard_helmet(struct obj * a0){return hard_helmet(a0);}
void teleport_objnam_assertion(const char*condition,const char*file,unsigned line,const char*fn){__assert_fail(condition,file,line,fn);}
