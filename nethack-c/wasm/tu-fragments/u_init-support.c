/* Typed state, header macros, dependencies and zero-only ABI backing.
 * All starting values, loops, filtering and initialization decisions are JS. */
#include "../../../scripts/tu-u_init-layout.h"
#include <stdint.h>
static struct teleport_u_init_trobj teleport_u_init_storage_Archeologist[9];
static struct teleport_u_init_trobj teleport_u_init_storage_Barbarian_0[5];
static struct teleport_u_init_trobj teleport_u_init_storage_Barbarian_1[5];
static struct teleport_u_init_trobj teleport_u_init_storage_Cave_man[6];
static struct teleport_u_init_trobj teleport_u_init_storage_Healer[11];
static struct teleport_u_init_trobj teleport_u_init_storage_Knight[9];
static struct teleport_u_init_trobj teleport_u_init_storage_Monk[9];
static struct teleport_u_init_trobj teleport_u_init_storage_Priest[8];
static struct teleport_u_init_trobj teleport_u_init_storage_Ranger[7];
static struct teleport_u_init_trobj teleport_u_init_storage_Rogue[7];
static struct teleport_u_init_trobj teleport_u_init_storage_Samurai[6];
static struct teleport_u_init_trobj teleport_u_init_storage_Tourist[8];
static struct teleport_u_init_trobj teleport_u_init_storage_Valkyrie[5];
static struct teleport_u_init_trobj teleport_u_init_storage_Wizard[10];
static struct teleport_u_init_trobj teleport_u_init_storage_Healing_book[2];
static struct teleport_u_init_trobj teleport_u_init_storage_Protection_book[2];
static struct teleport_u_init_trobj teleport_u_init_storage_Confuse_monster_book[2];
static struct teleport_u_init_trobj teleport_u_init_storage_Tinopener[2];
static struct teleport_u_init_trobj teleport_u_init_storage_Magicmarker[2];
static struct teleport_u_init_trobj teleport_u_init_storage_Lamp[2];
static struct teleport_u_init_trobj teleport_u_init_storage_Blindfold[2];
static struct teleport_u_init_trobj teleport_u_init_storage_Xtra_food[2];
static struct teleport_u_init_trobj teleport_u_init_storage_Leash[2];
static struct teleport_u_init_trobj teleport_u_init_storage_Towel[2];
static struct teleport_u_init_trobj teleport_u_init_storage_Wishing[2];
static struct teleport_u_init_trobj teleport_u_init_storage_Money[2];
static struct teleport_u_init_invsub teleport_u_init_storage_inv_subs[26];
static struct def_skill teleport_u_init_storage_Skill_A[20];
static struct def_skill teleport_u_init_storage_Skill_B[23];
static struct def_skill teleport_u_init_storage_Skill_C[21];
static struct def_skill teleport_u_init_storage_Skill_H[17];
static struct def_skill teleport_u_init_storage_Skill_K[27];
static struct def_skill teleport_u_init_storage_Skill_Mon[13];
static struct def_skill teleport_u_init_storage_Skill_P[22];
static struct def_skill teleport_u_init_storage_Skill_R[24];
static struct def_skill teleport_u_init_storage_Skill_Ran[25];
static struct def_skill teleport_u_init_storage_Skill_S[21];
static struct def_skill teleport_u_init_storage_Skill_T[33];
static struct def_skill teleport_u_init_storage_Skill_V[21];
static struct def_skill teleport_u_init_storage_Skill_W[23];
void *teleport_u_init_table(int index) {switch(index){
case 0:return teleport_u_init_storage_Archeologist;
case 1:return teleport_u_init_storage_Barbarian_0;
case 2:return teleport_u_init_storage_Barbarian_1;
case 3:return teleport_u_init_storage_Cave_man;
case 4:return teleport_u_init_storage_Healer;
case 5:return teleport_u_init_storage_Knight;
case 6:return teleport_u_init_storage_Monk;
case 7:return teleport_u_init_storage_Priest;
case 8:return teleport_u_init_storage_Ranger;
case 9:return teleport_u_init_storage_Rogue;
case 10:return teleport_u_init_storage_Samurai;
case 11:return teleport_u_init_storage_Tourist;
case 12:return teleport_u_init_storage_Valkyrie;
case 13:return teleport_u_init_storage_Wizard;
case 14:return teleport_u_init_storage_Healing_book;
case 15:return teleport_u_init_storage_Protection_book;
case 16:return teleport_u_init_storage_Confuse_monster_book;
case 17:return teleport_u_init_storage_Tinopener;
case 18:return teleport_u_init_storage_Magicmarker;
case 19:return teleport_u_init_storage_Lamp;
case 20:return teleport_u_init_storage_Blindfold;
case 21:return teleport_u_init_storage_Xtra_food;
case 22:return teleport_u_init_storage_Leash;
case 23:return teleport_u_init_storage_Towel;
case 24:return teleport_u_init_storage_Wishing;
case 25:return teleport_u_init_storage_Money;
case 26:return teleport_u_init_storage_inv_subs;
case 27:return teleport_u_init_storage_Skill_A;
case 28:return teleport_u_init_storage_Skill_B;
case 29:return teleport_u_init_storage_Skill_C;
case 30:return teleport_u_init_storage_Skill_H;
case 31:return teleport_u_init_storage_Skill_K;
case 32:return teleport_u_init_storage_Skill_Mon;
case 33:return teleport_u_init_storage_Skill_P;
case 34:return teleport_u_init_storage_Skill_R;
case 35:return teleport_u_init_storage_Skill_Ran;
case 36:return teleport_u_init_storage_Skill_S;
case 37:return teleport_u_init_storage_Skill_T;
case 38:return teleport_u_init_storage_Skill_V;
case 39:return teleport_u_init_storage_Skill_W;
default:return 0;}}
long teleport_u_init_get(int group,int field,void *p) {switch(group){
case 0:switch(field){
case 0:return (long)((struct obj*)p)->otyp;
case 1:return (long)((struct obj*)p)->oclass;
case 2:return (long)((struct obj*)p)->quan;
case 3:return (long)((struct obj*)p)->spe;
case 4:return (long)((struct obj*)p)->known;
case 5:return (long)((struct obj*)p)->dknown;
case 6:return (long)((struct obj*)p)->bknown;
case 7:return (long)((struct obj*)p)->rknown;
case 8:return (long)((struct obj*)p)->cknown;
case 9:return (long)((struct obj*)p)->lknown;
case 10:return (long)((struct obj*)p)->otrapped;
case 11:return (long)((struct obj*)p)->cursed;
case 12:return (long)((struct obj*)p)->opoisoned;
case 13:return (long)((struct obj*)p)->blessed;
case 14:return (long)((struct obj*)p)->owt;
case 15:return (long)(intptr_t)((struct obj*)p)->nobj;
}break;
case 1:switch(field){
case 0:return (long)((struct objclass*)p)->oc_skill;
case 1:return (long)((struct objclass*)p)->oc_class;
case 2:return (long)((struct objclass*)p)->oc_magic;
case 3:return (long)((struct objclass*)p)->oc_level;
case 4:return (long)((struct objclass*)p)->oc_uses_known;
case 5:return (long)((struct objclass*)p)->oc_charged;
case 6:return (long)((struct objclass*)p)->oc_name_idx;
case 7:return (long)((struct objclass*)p)->oc_descr_idx;
}break;
case 2:switch(field){
case 0:return (long)((struct you*)p)->weapon_slots;
case 1:return (long)((struct you*)p)->umoney0;
case 2:return (long)(intptr_t)((struct you*)p)->ustuck;
case 3:return (long)((struct you*)p)->umoved;
case 4:return (long)((struct you*)p)->umortality;
case 5:return (long)((struct you*)p)->ugrave_arise;
case 6:return (long)((struct you*)p)->umonnum;
case 7:return (long)((struct you*)p)->umonster;
case 8:return (long)((struct you*)p)->ulycn;
case 9:return (long)((struct you*)p)->ulevel;
case 10:return (long)((struct you*)p)->uhp;
case 11:return (long)((struct you*)p)->uhpmax;
case 12:return (long)((struct you*)p)->uhppeak;
case 13:return (long)((struct you*)p)->uen;
case 14:return (long)((struct you*)p)->uenmax;
case 15:return (long)((struct you*)p)->uenpeak;
case 16:return (long)((struct you*)p)->uspellprot;
case 17:return (long)((struct you*)p)->ulevelmax;
case 18:return (long)((struct you*)p)->ublesscnt;
case 19:return (long)((struct you*)p)->nv_range;
case 20:return (long)((struct you*)p)->xray_range;
case 21:return (long)((struct you*)p)->unblind_telepat_range;
case 22:return (long)((struct you*)p)->uhandedness;
}break;
case 3:switch(field){
case 0:return (long)((struct u_roleplay*)p)->blind;
case 1:return (long)((struct u_roleplay*)p)->nudist;
case 2:return (long)((struct u_roleplay*)p)->deaf;
case 3:return (long)((struct u_roleplay*)p)->pauper;
case 4:return (long)((struct u_roleplay*)p)->reroll;
case 5:return (long)((struct u_roleplay*)p)->reserved1;
case 6:return (long)((struct u_roleplay*)p)->reserved2;
case 7:return (long)((struct u_roleplay*)p)->reserved3;
case 8:return (long)((struct u_roleplay*)p)->numbones;
case 9:return (long)((struct u_roleplay*)p)->numrerolls;
}break;
case 4:switch(field){
case 0:return (long)((d_level*)p)->dnum;
case 1:return (long)((d_level*)p)->dlevel;
}break;
case 5:switch(field){
case 0:return (long)((struct skills*)p)->skill;
case 1:return (long)((struct skills*)p)->advance;
}break;
case 6:switch(field){
case 0:return (long)((struct def_skill*)p)->skill;
case 1:return (long)((struct def_skill*)p)->skmax;
}break;
case 7:switch(field){
case 0:return (long)((align*)p)->type;
}break;
case 8:switch(field){
case 0:return (long)flags.female;
case 1:return (long)flags.initgend;
case 2:return (long)flags.beginner;
case 3:return (long)flags.initalign;
}break;
case 9:switch(field){
case 0:return (long)gn.nocreate;
case 1:return (long)gn.nocreate2;
case 2:return (long)gn.nocreate3;
case 3:return (long)gn.nocreate4;
}break;
case 10:switch(field){
case 0:return (long)gu.urole.mnum;
case 1:return (long)gu.urace.mnum;
}break;
case 11:switch(field){
case 0:return (long)gl.lastinvnr;
}break;
case 12:switch(field){
case 0:return (long)svm.moves;
}break;
case 13:switch(field){
case 0:return (long)ubirthday;
case 1:return (long)discover;
}break;
case 14:switch(field){
case 0:return (long)((struct teleport_u_init_trobj*)p)->trotyp;
case 1:return (long)((struct teleport_u_init_trobj*)p)->trspe;
case 2:return (long)((struct teleport_u_init_trobj*)p)->trclass;
case 3:return (long)((struct teleport_u_init_trobj*)p)->trquan_min;
case 4:return (long)((struct teleport_u_init_trobj*)p)->trquan_max;
case 5:return (long)((struct teleport_u_init_trobj*)p)->trbless;
}break;
case 15:switch(field){
case 0:return (long)((struct teleport_u_init_invsub*)p)->race_pm;
case 1:return (long)((struct teleport_u_init_invsub*)p)->item_otyp;
case 2:return (long)((struct teleport_u_init_invsub*)p)->subs_otyp;
}break;
}return 0;}
void teleport_u_init_set(int group,int field,void *p,long value) {switch(group){
case 0:switch(field){
case 0:((struct obj*)p)->otyp=value;return;
case 1:((struct obj*)p)->oclass=value;return;
case 2:((struct obj*)p)->quan=value;return;
case 3:((struct obj*)p)->spe=value;return;
case 4:((struct obj*)p)->known=value;return;
case 5:((struct obj*)p)->dknown=value;return;
case 6:((struct obj*)p)->bknown=value;return;
case 7:((struct obj*)p)->rknown=value;return;
case 8:((struct obj*)p)->cknown=value;return;
case 9:((struct obj*)p)->lknown=value;return;
case 10:((struct obj*)p)->otrapped=value;return;
case 11:((struct obj*)p)->cursed=value;return;
case 12:((struct obj*)p)->opoisoned=value;return;
case 13:((struct obj*)p)->blessed=value;return;
case 14:((struct obj*)p)->owt=value;return;
case 15:((struct obj*)p)->nobj=(void*)(intptr_t)value;return;
}break;
case 1:switch(field){
case 0:((struct objclass*)p)->oc_skill=value;return;
case 1:((struct objclass*)p)->oc_class=value;return;
case 2:((struct objclass*)p)->oc_magic=value;return;
case 3:((struct objclass*)p)->oc_level=value;return;
case 4:((struct objclass*)p)->oc_uses_known=value;return;
case 5:((struct objclass*)p)->oc_charged=value;return;
case 6:((struct objclass*)p)->oc_name_idx=value;return;
case 7:((struct objclass*)p)->oc_descr_idx=value;return;
}break;
case 2:switch(field){
case 0:((struct you*)p)->weapon_slots=value;return;
case 1:((struct you*)p)->umoney0=value;return;
case 2:((struct you*)p)->ustuck=(void*)(intptr_t)value;return;
case 3:((struct you*)p)->umoved=value;return;
case 4:((struct you*)p)->umortality=value;return;
case 5:((struct you*)p)->ugrave_arise=value;return;
case 6:((struct you*)p)->umonnum=value;return;
case 7:((struct you*)p)->umonster=value;return;
case 8:((struct you*)p)->ulycn=value;return;
case 9:((struct you*)p)->ulevel=value;return;
case 10:((struct you*)p)->uhp=value;return;
case 11:((struct you*)p)->uhpmax=value;return;
case 12:((struct you*)p)->uhppeak=value;return;
case 13:((struct you*)p)->uen=value;return;
case 14:((struct you*)p)->uenmax=value;return;
case 15:((struct you*)p)->uenpeak=value;return;
case 16:((struct you*)p)->uspellprot=value;return;
case 17:((struct you*)p)->ulevelmax=value;return;
case 18:((struct you*)p)->ublesscnt=value;return;
case 19:((struct you*)p)->nv_range=value;return;
case 20:((struct you*)p)->xray_range=value;return;
case 21:((struct you*)p)->unblind_telepat_range=value;return;
case 22:((struct you*)p)->uhandedness=value;return;
}break;
case 3:switch(field){
case 0:((struct u_roleplay*)p)->blind=value;return;
case 1:((struct u_roleplay*)p)->nudist=value;return;
case 2:((struct u_roleplay*)p)->deaf=value;return;
case 3:((struct u_roleplay*)p)->pauper=value;return;
case 4:((struct u_roleplay*)p)->reroll=value;return;
case 5:((struct u_roleplay*)p)->reserved1=value;return;
case 6:((struct u_roleplay*)p)->reserved2=value;return;
case 7:((struct u_roleplay*)p)->reserved3=value;return;
case 8:((struct u_roleplay*)p)->numbones=value;return;
case 9:((struct u_roleplay*)p)->numrerolls=value;return;
}break;
case 4:switch(field){
case 0:((d_level*)p)->dnum=value;return;
case 1:((d_level*)p)->dlevel=value;return;
}break;
case 5:switch(field){
case 0:((struct skills*)p)->skill=value;return;
case 1:((struct skills*)p)->advance=value;return;
}break;
case 6:switch(field){
case 0:((struct def_skill*)p)->skill=value;return;
case 1:((struct def_skill*)p)->skmax=value;return;
}break;
case 7:switch(field){
case 0:((align*)p)->type=value;return;
}break;
case 8:switch(field){
case 0:flags.female=value;return;
case 1:flags.initgend=value;return;
case 2:flags.beginner=value;return;
case 3:flags.initalign=value;return;
}break;
case 9:switch(field){
case 0:gn.nocreate=value;return;
case 1:gn.nocreate2=value;return;
case 2:gn.nocreate3=value;return;
case 3:gn.nocreate4=value;return;
}break;
case 10:switch(field){
case 0:gu.urole.mnum=value;return;
case 1:gu.urace.mnum=value;return;
}break;
case 11:switch(field){
case 0:gl.lastinvnr=value;return;
}break;
case 12:switch(field){
case 0:svm.moves=value;return;
}break;
case 13:switch(field){
case 0:ubirthday=value;return;
case 1:discover=value;return;
}break;
case 14:switch(field){
case 0:((struct teleport_u_init_trobj*)p)->trotyp=value;return;
case 1:((struct teleport_u_init_trobj*)p)->trspe=value;return;
case 2:((struct teleport_u_init_trobj*)p)->trclass=value;return;
case 3:((struct teleport_u_init_trobj*)p)->trquan_min=value;return;
case 4:((struct teleport_u_init_trobj*)p)->trquan_max=value;return;
case 5:((struct teleport_u_init_trobj*)p)->trbless=value;return;
}break;
case 15:switch(field){
case 0:((struct teleport_u_init_invsub*)p)->race_pm=value;return;
case 1:((struct teleport_u_init_invsub*)p)->item_otyp=value;return;
case 2:((struct teleport_u_init_invsub*)p)->subs_otyp=value;return;
}break;
}}
void *teleport_u_init_address(int index) {switch(index){
case 0:return (void*)&u;
case 1:return (void*)&u.uroleplay;
case 2:return (void*)&u.uz;
case 3:return (void*)&u.uz0;
case 4:return (void*)&u.utolev;
case 5:return (void*)&u.ualign;
case 6:return (void*)&ubirthday;
case 7:return (void*)&urealtime;
case 8:return (void*)&cg.zeroobj;
case 9:return (void*)&flags;
case 10:return (void*)&gn;
case 11:return (void*)&gl;
case 12:return (void*)&svm;
default:return 0;}}
long teleport_u_init_array_get(int kind,int index) {switch(kind){case 0:return svb.bases[index];case 1:return svs.spl_book[index].sp_id;case 2:return u.ualignbase[index];case 3:return u.ueninc[index];case 4:return aligns[index].value;}return 0;}
void teleport_u_init_array_set(int kind,int index,long value){switch(kind){case 0:svb.bases[index]=value;break;case 1:svs.spl_book[index].sp_id=value;break;case 2:u.ualignbase[index]=value;break;case 3:u.ueninc[index]=value;break;}}
void *teleport_u_init_element(int kind,int index) {switch(kind){case 0:return &objects[index];case 1:return &u.weapon_skills[index];}return 0;}
struct obj *teleport_u_init_equipment(int index){switch(index){
case 0:return uarms;
case 1:return uwep;
case 2:return uarmh;
case 3:return uarmg;
case 4:return uarmu;
case 5:return uarmc;
case 6:return uarmf;
case 7:return uarm;
case 8:return uquiver;
case 9:return uswapwep;
default:return 0;}}
struct obj *teleport_u_init_invent(void){return gi.invent;}
long teleport_u_init_intrinsic(int index){return index?HBlinded:HJumping;}
void teleport_u_init_set_intrinsic(int index,long v){if(index)HBlinded=v;else HJumping=v;}
int teleport_u_init_macro(struct obj *obj,int index){switch(index){
case 0:return is_pole(obj);
case 1:return is_launcher(obj);
case 2:return is_ammo(obj);
case 3:return is_spear(obj);
case 4:return Is_container(obj);
case 5:return is_graystone(obj);
case 6:return is_shield(obj);
case 7:return is_helmet(obj);
case 8:return is_gloves(obj);
case 9:return is_shirt(obj);
case 10:return is_cloak(obj);
case 11:return is_boots(obj);
case 12:return is_suit(obj);
case 13:return is_weptool(obj);
case 14:return is_missile(obj);
case 15:return bimanual(obj);
default:return 0;}}
const char *teleport_u_init_objname(int index){return OBJ_NAME(objects[index]);}
const char *teleport_u_init_objdescr(int index){return OBJ_DESCR(objects[index]);}
void teleport_u_init_debug(const char *f,const char *a,const char *b,const char *c){debugpline3(f,a,b,c);}
void teleport_u_init_panic(const char *f){panic("%s",f);}
int teleport_u_init_spell_pw(int n){return SPELL_LEV_PW(n);}
int teleport_u_init_rn2(int n,int line,const char *fn){if(rng_log_enabled())rng_log_set_caller("u_init.c",line,fn);return (rn2)(n);}
int teleport_u_init_rnd(int n,int line,const char *fn){if(rng_log_enabled())rng_log_set_caller("u_init.c",line,fn);return (rnd)(n);}
int teleport_u_init_rn1(int n,int base,int line,const char *fn){if(rng_log_enabled())rng_log_set_caller("u_init.c",line,fn);return (rn2)(n)+base;}
int teleport_u_init_rne(int n,int line,const char *fn){if(rng_log_enabled())rng_log_set_caller("u_init.c",line,fn);return (rne)(n);}
static char teleport_u_init_literals[130];
void *teleport_u_init_literal_storage(void){return teleport_u_init_literals;}
size_t teleport_u_init_literal_capacity(void){return sizeof teleport_u_init_literals;}
#ifdef TELEPORT_U_INIT_VALIDATE_SOURCE
_Static_assert(__builtin_types_compatible_p(__typeof__(((struct trobj*)0)->trotyp),__typeof__(((struct teleport_u_init_trobj*)0)->trotyp)),"trobj.trotyp source field type changed");
_Static_assert(__builtin_types_compatible_p(__typeof__(((struct trobj*)0)->trspe),__typeof__(((struct teleport_u_init_trobj*)0)->trspe)),"trobj.trspe source field type changed");
_Static_assert(__builtin_types_compatible_p(__typeof__(((struct trobj*)0)->trclass),__typeof__(((struct teleport_u_init_trobj*)0)->trclass)),"trobj.trclass source field type changed");
_Static_assert(__builtin_types_compatible_p(__typeof__(((struct trobj*)0)->trquan_min),__typeof__(((struct teleport_u_init_trobj*)0)->trquan_min)),"trobj.trquan_min source field type changed");
_Static_assert(__builtin_types_compatible_p(__typeof__(((struct trobj*)0)->trquan_max),__typeof__(((struct teleport_u_init_trobj*)0)->trquan_max)),"trobj.trquan_max source field type changed");
_Static_assert(__builtin_types_compatible_p(__typeof__(((struct trobj*)0)->trbless),__typeof__(((struct teleport_u_init_trobj*)0)->trbless)),"trobj.trbless source field type changed");
_Static_assert(__builtin_types_compatible_p(__typeof__(((struct inv_sub*)0)->race_pm),__typeof__(((struct teleport_u_init_invsub*)0)->race_pm)),"inv_sub.race_pm source field type changed");
_Static_assert(__builtin_types_compatible_p(__typeof__(((struct inv_sub*)0)->item_otyp),__typeof__(((struct teleport_u_init_invsub*)0)->item_otyp)),"inv_sub.item_otyp source field type changed");
_Static_assert(__builtin_types_compatible_p(__typeof__(((struct inv_sub*)0)->subs_otyp),__typeof__(((struct teleport_u_init_invsub*)0)->subs_otyp)),"inv_sub.subs_otyp source field type changed");
_Static_assert(sizeof(struct trobj)==sizeof(struct teleport_u_init_trobj),"trobj ABI changed");
_Static_assert(sizeof(struct inv_sub)==sizeof(struct teleport_u_init_invsub),"inv_sub ABI changed");
_Static_assert(offsetof(struct trobj,trotyp)==offsetof(struct teleport_u_init_trobj,trotyp),"trobj offset changed");
_Static_assert(offsetof(struct trobj,trspe)==offsetof(struct teleport_u_init_trobj,trspe),"trobj offset changed");
_Static_assert(offsetof(struct trobj,trclass)==offsetof(struct teleport_u_init_trobj,trclass),"trobj offset changed");
_Static_assert(offsetof(struct trobj,trquan_min)==offsetof(struct teleport_u_init_trobj,trquan_min),"trobj offset changed");
_Static_assert(offsetof(struct trobj,trquan_max)==offsetof(struct teleport_u_init_trobj,trquan_max),"trobj offset changed");
_Static_assert(offsetof(struct trobj,trbless)==offsetof(struct teleport_u_init_trobj,trbless),"trobj offset changed");
_Static_assert(sizeof Archeologist==sizeof teleport_u_init_storage_Archeologist,"source Archeologist rows changed");
_Static_assert(sizeof Barbarian_0==sizeof teleport_u_init_storage_Barbarian_0,"source Barbarian_0 rows changed");
_Static_assert(sizeof Barbarian_1==sizeof teleport_u_init_storage_Barbarian_1,"source Barbarian_1 rows changed");
_Static_assert(sizeof Cave_man==sizeof teleport_u_init_storage_Cave_man,"source Cave_man rows changed");
_Static_assert(sizeof Healer==sizeof teleport_u_init_storage_Healer,"source Healer rows changed");
_Static_assert(sizeof Knight==sizeof teleport_u_init_storage_Knight,"source Knight rows changed");
_Static_assert(sizeof Monk==sizeof teleport_u_init_storage_Monk,"source Monk rows changed");
_Static_assert(sizeof Priest==sizeof teleport_u_init_storage_Priest,"source Priest rows changed");
_Static_assert(sizeof Ranger==sizeof teleport_u_init_storage_Ranger,"source Ranger rows changed");
_Static_assert(sizeof Rogue==sizeof teleport_u_init_storage_Rogue,"source Rogue rows changed");
_Static_assert(sizeof Samurai==sizeof teleport_u_init_storage_Samurai,"source Samurai rows changed");
_Static_assert(sizeof Tourist==sizeof teleport_u_init_storage_Tourist,"source Tourist rows changed");
_Static_assert(sizeof Valkyrie==sizeof teleport_u_init_storage_Valkyrie,"source Valkyrie rows changed");
_Static_assert(sizeof Wizard==sizeof teleport_u_init_storage_Wizard,"source Wizard rows changed");
_Static_assert(sizeof Healing_book==sizeof teleport_u_init_storage_Healing_book,"source Healing_book rows changed");
_Static_assert(sizeof Protection_book==sizeof teleport_u_init_storage_Protection_book,"source Protection_book rows changed");
_Static_assert(sizeof Confuse_monster_book==sizeof teleport_u_init_storage_Confuse_monster_book,"source Confuse_monster_book rows changed");
_Static_assert(sizeof Tinopener==sizeof teleport_u_init_storage_Tinopener,"source Tinopener rows changed");
_Static_assert(sizeof Magicmarker==sizeof teleport_u_init_storage_Magicmarker,"source Magicmarker rows changed");
_Static_assert(sizeof Lamp==sizeof teleport_u_init_storage_Lamp,"source Lamp rows changed");
_Static_assert(sizeof Blindfold==sizeof teleport_u_init_storage_Blindfold,"source Blindfold rows changed");
_Static_assert(sizeof Xtra_food==sizeof teleport_u_init_storage_Xtra_food,"source Xtra_food rows changed");
_Static_assert(sizeof Leash==sizeof teleport_u_init_storage_Leash,"source Leash rows changed");
_Static_assert(sizeof Towel==sizeof teleport_u_init_storage_Towel,"source Towel rows changed");
_Static_assert(sizeof Wishing==sizeof teleport_u_init_storage_Wishing,"source Wishing rows changed");
_Static_assert(sizeof Money==sizeof teleport_u_init_storage_Money,"source Money rows changed");
_Static_assert(sizeof inv_subs==sizeof teleport_u_init_storage_inv_subs,"source inv_subs rows changed");
_Static_assert(sizeof Skill_A==sizeof teleport_u_init_storage_Skill_A,"source Skill_A rows changed");
_Static_assert(sizeof Skill_B==sizeof teleport_u_init_storage_Skill_B,"source Skill_B rows changed");
_Static_assert(sizeof Skill_C==sizeof teleport_u_init_storage_Skill_C,"source Skill_C rows changed");
_Static_assert(sizeof Skill_H==sizeof teleport_u_init_storage_Skill_H,"source Skill_H rows changed");
_Static_assert(sizeof Skill_K==sizeof teleport_u_init_storage_Skill_K,"source Skill_K rows changed");
_Static_assert(sizeof Skill_Mon==sizeof teleport_u_init_storage_Skill_Mon,"source Skill_Mon rows changed");
_Static_assert(sizeof Skill_P==sizeof teleport_u_init_storage_Skill_P,"source Skill_P rows changed");
_Static_assert(sizeof Skill_R==sizeof teleport_u_init_storage_Skill_R,"source Skill_R rows changed");
_Static_assert(sizeof Skill_Ran==sizeof teleport_u_init_storage_Skill_Ran,"source Skill_Ran rows changed");
_Static_assert(sizeof Skill_S==sizeof teleport_u_init_storage_Skill_S,"source Skill_S rows changed");
_Static_assert(sizeof Skill_T==sizeof teleport_u_init_storage_Skill_T,"source Skill_T rows changed");
_Static_assert(sizeof Skill_V==sizeof teleport_u_init_storage_Skill_V,"source Skill_V rows changed");
_Static_assert(sizeof Skill_W==sizeof teleport_u_init_storage_Skill_W,"source Skill_W rows changed");
#endif
