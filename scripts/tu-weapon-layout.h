#ifndef TELEPORT_WEAPON_LAYOUT_H
#define TELEPORT_WEAPON_LAYOUT_H
#include "hack.h"
#include <stddef.h>
struct weapon_meta {const char *name;size_t value;};
#define WEAPON_META(k,v) {#k,(size_t)(v)}
static const struct weapon_meta weapon_layout[]={
WEAPON_META(pointerSize,sizeof(void*)),
WEAPON_META(longSize,sizeof(long)),
WEAPON_META(intSize,sizeof(int)),
WEAPON_META(booleanSize,sizeof(boolean)),
WEAPON_META(objectSize,sizeof(struct obj)),
WEAPON_META(permonstSize,sizeof(struct permonst)),
WEAPON_META(objectClassSize,sizeof(struct objclass)),
WEAPON_META(objDescrSize,sizeof(struct objdescr)),
WEAPON_META(skillsSize,sizeof(struct skills)),
WEAPON_META(defSkillSize,sizeof(struct def_skill)),
WEAPON_META(arwSize,sizeof(struct throw_and_return_weapon)),
WEAPON_META(classsymSize,sizeof(struct class_sym)),
WEAPON_META(genderSize,sizeof(struct Gender)),
WEAPON_META(anythingSize,sizeof(anything)),
WEAPON_META(menuSize,sizeof(menu_item)),
WEAPON_META(obj_nobj,offsetof(struct obj,nobj)),
WEAPON_META(obj_nobj_size,sizeof(((struct obj*)0)->nobj)),
WEAPON_META(obj_otyp,offsetof(struct obj,otyp)),
WEAPON_META(obj_otyp_size,sizeof(((struct obj*)0)->otyp)),
WEAPON_META(obj_oclass,offsetof(struct obj,oclass)),
WEAPON_META(obj_oclass_size,sizeof(((struct obj*)0)->oclass)),
WEAPON_META(obj_oartifact,offsetof(struct obj,oartifact)),
WEAPON_META(obj_oartifact_size,sizeof(((struct obj*)0)->oartifact)),
WEAPON_META(obj_spe,offsetof(struct obj,spe)),
WEAPON_META(obj_spe_size,sizeof(((struct obj*)0)->spe)),
WEAPON_META(obj_owt,offsetof(struct obj,owt)),
WEAPON_META(obj_owt_size,sizeof(((struct obj*)0)->owt)),
WEAPON_META(obj_quan,offsetof(struct obj,quan)),
WEAPON_META(obj_quan_size,sizeof(((struct obj*)0)->quan)),
WEAPON_META(obj_owornmask,offsetof(struct obj,owornmask)),
WEAPON_META(obj_owornmask_size,sizeof(((struct obj*)0)->owornmask)),
WEAPON_META(obj_corpsenm,offsetof(struct obj,corpsenm)),
WEAPON_META(obj_corpsenm_size,sizeof(((struct obj*)0)->corpsenm)),
WEAPON_META(obj_where,offsetof(struct obj,where)),
WEAPON_META(obj_where_size,sizeof(((struct obj*)0)->where)),
WEAPON_META(obj_ocarry,offsetof(struct obj,ocarry)),
WEAPON_META(obj_ocarry_size,sizeof(((struct obj*)0)->ocarry)),
WEAPON_META(mon_data,offsetof(struct monst,data)),
WEAPON_META(mon_data_size,sizeof(((struct monst*)0)->data)),
WEAPON_META(mon_minvent,offsetof(struct monst,minvent)),
WEAPON_META(mon_minvent_size,sizeof(((struct monst*)0)->minvent)),
WEAPON_META(mon_mw,offsetof(struct monst,mw)),
WEAPON_META(mon_mw_size,sizeof(((struct monst*)0)->mw)),
WEAPON_META(mon_weapon_check,offsetof(struct monst,weapon_check)),
WEAPON_META(mon_weapon_check_size,sizeof(((struct monst*)0)->weapon_check)),
WEAPON_META(mon_mx,offsetof(struct monst,mx)),
WEAPON_META(mon_mx_size,sizeof(((struct monst*)0)->mx)),
WEAPON_META(mon_my,offsetof(struct monst,my)),
WEAPON_META(mon_my_size,sizeof(((struct monst*)0)->my)),
WEAPON_META(mon_mux,offsetof(struct monst,mux)),
WEAPON_META(mon_mux_size,sizeof(((struct monst*)0)->mux)),
WEAPON_META(mon_muy,offsetof(struct monst,muy)),
WEAPON_META(mon_muy_size,sizeof(((struct monst*)0)->muy)),
WEAPON_META(mon_misc_worn_check,offsetof(struct monst,misc_worn_check)),
WEAPON_META(mon_misc_worn_check_size,sizeof(((struct monst*)0)->misc_worn_check)),
WEAPON_META(pm_mlet,offsetof(struct permonst,mlet)),
WEAPON_META(pm_mlet_size,sizeof(((struct permonst*)0)->mlet)),
WEAPON_META(pm_msize,offsetof(struct permonst,msize)),
WEAPON_META(pm_msize_size,sizeof(((struct permonst*)0)->msize)),
WEAPON_META(pm_mflags1,offsetof(struct permonst,mflags1)),
WEAPON_META(pm_mflags1_size,sizeof(((struct permonst*)0)->mflags1)),
WEAPON_META(pm_mflags2,offsetof(struct permonst,mflags2)),
WEAPON_META(pm_mflags2_size,sizeof(((struct permonst*)0)->mflags2)),
WEAPON_META(cls_oc_name_idx,offsetof(struct objclass,oc_name_idx)),
WEAPON_META(cls_oc_name_idx_size,sizeof(((struct objclass*)0)->oc_name_idx)),
WEAPON_META(cls_oc_skill,offsetof(struct objclass,oc_skill)),
WEAPON_META(cls_oc_skill_size,sizeof(((struct objclass*)0)->oc_skill)),
WEAPON_META(cls_oc_hitbon,offsetof(struct objclass,oc_hitbon)),
WEAPON_META(cls_oc_hitbon_size,sizeof(((struct objclass*)0)->oc_hitbon)),
WEAPON_META(cls_oc_wldam,offsetof(struct objclass,oc_wldam)),
WEAPON_META(cls_oc_wldam_size,sizeof(((struct objclass*)0)->oc_wldam)),
WEAPON_META(cls_oc_wsdam,offsetof(struct objclass,oc_wsdam)),
WEAPON_META(cls_oc_wsdam_size,sizeof(((struct objclass*)0)->oc_wsdam)),
WEAPON_META(cls_oc_weight,offsetof(struct objclass,oc_weight)),
WEAPON_META(cls_oc_weight_size,sizeof(((struct objclass*)0)->oc_weight)),
WEAPON_META(descr_oc_name,offsetof(struct objdescr,oc_name)),
WEAPON_META(descr_oc_name_size,sizeof(((struct objdescr*)0)->oc_name)),
WEAPON_META(u_weapon_slots,offsetof(struct you,weapon_slots)),
WEAPON_META(u_weapon_slots_size,sizeof(((struct you*)0)->weapon_slots)),
WEAPON_META(u_skills_advanced,offsetof(struct you,skills_advanced)),
WEAPON_META(u_skills_advanced_size,sizeof(((struct you*)0)->skills_advanced)),
WEAPON_META(u_skill_record,offsetof(struct you,skill_record)),
WEAPON_META(u_skill_record_size,sizeof(((struct you*)0)->skill_record)),
WEAPON_META(u_weapon_skills,offsetof(struct you,weapon_skills)),
WEAPON_META(u_weapon_skills_size,sizeof(((struct you*)0)->weapon_skills)),
WEAPON_META(u_twoweap,offsetof(struct you,twoweap)),
WEAPON_META(u_twoweap_size,sizeof(((struct you*)0)->twoweap)),
WEAPON_META(u_usteed,offsetof(struct you,usteed)),
WEAPON_META(u_usteed_size,sizeof(((struct you*)0)->usteed)),
WEAPON_META(u_umonnum,offsetof(struct you,umonnum)),
WEAPON_META(u_umonnum_size,sizeof(((struct you*)0)->umonnum)),
WEAPON_META(u_umonster,offsetof(struct you,umonster)),
WEAPON_META(u_umonster_size,sizeof(((struct you*)0)->umonster)),
WEAPON_META(u_ulevel,offsetof(struct you,ulevel)),
WEAPON_META(u_ulevel_size,sizeof(((struct you*)0)->ulevel)),
WEAPON_META(u_ux,offsetof(struct you,ux)),
WEAPON_META(u_ux_size,sizeof(((struct you*)0)->ux)),
WEAPON_META(u_uy,offsetof(struct you,uy)),
WEAPON_META(u_uy_size,sizeof(((struct you*)0)->uy)),
WEAPON_META(u_uroleplay_pauper,offsetof(struct you,uroleplay.pauper)),
WEAPON_META(u_uroleplay_pauper_size,sizeof(((struct you*)0)->uroleplay.pauper)),
WEAPON_META(skill_skill,offsetof(struct skills,skill)),
WEAPON_META(skill_skill_size,sizeof(((struct skills*)0)->skill)),
WEAPON_META(skill_max_skill,offsetof(struct skills,max_skill)),
WEAPON_META(skill_max_skill_size,sizeof(((struct skills*)0)->max_skill)),
WEAPON_META(skill_advance,offsetof(struct skills,advance)),
WEAPON_META(skill_advance_size,sizeof(((struct skills*)0)->advance)),
WEAPON_META(defskill_skill,offsetof(struct def_skill,skill)),
WEAPON_META(defskill_skill_size,sizeof(((struct def_skill*)0)->skill)),
WEAPON_META(defskill_skmax,offsetof(struct def_skill,skmax)),
WEAPON_META(defskill_skmax_size,sizeof(((struct def_skill*)0)->skmax)),
WEAPON_META(arw_otyp,offsetof(struct throw_and_return_weapon,otyp)),
WEAPON_META(arw_otyp_size,sizeof(((struct throw_and_return_weapon*)0)->otyp)),
WEAPON_META(arw_range,offsetof(struct throw_and_return_weapon,range)),
WEAPON_META(arw_range_size,sizeof(((struct throw_and_return_weapon*)0)->range)),
WEAPON_META(classsym_name,offsetof(struct class_sym,name)),
WEAPON_META(classsym_name_size,sizeof(((struct class_sym*)0)->name)),
WEAPON_META(gender_his,offsetof(struct Gender,his)),
WEAPON_META(gender_his_size,sizeof(((struct Gender*)0)->his)),
WEAPON_META(menu_item,offsetof(menu_item,item)),
WEAPON_META(menu_item_size,sizeof(((menu_item*)0)->item)),
WEAPON_META(any_a_int,offsetof(anything,a_int)),
WEAPON_META(any_a_int_size,sizeof(((anything*)0)->a_int)),
WEAPON_META(youmonst,offsetof(__typeof__(gy),youmonst)),
WEAPON_META(youmonst_size,sizeof(gy.youmonst)),
WEAPON_META(propellor,offsetof(__typeof__(gp),propellor)),
WEAPON_META(propellor_size,sizeof(gp.propellor)),
WEAPON_META(roleMnum,offsetof(__typeof__(gu),urole.mnum)),
WEAPON_META(roleMnum_size,sizeof(gu.urole.mnum)),
WEAPON_META(petnum,offsetof(__typeof__(gu),urole.petnum)),
WEAPON_META(petnum_size,sizeof(gu.urole.petnum)),
WEAPON_META(spelspec,offsetof(__typeof__(gu),urole.spelspec)),
WEAPON_META(spelspec_size,sizeof(gu.urole.spelspec)),
WEAPON_META(unweapon,offsetof(__typeof__(gu),unweapon)),
WEAPON_META(unweapon_size,sizeof(gu.unweapon)),
WEAPON_META(invent,offsetof(__typeof__(gi),invent)),
WEAPON_META(invent_size,sizeof(gi.invent)),
WEAPON_META(menu_tab_sep,offsetof(__typeof__(iflags),menu_tab_sep)),
WEAPON_META(menu_tab_sep_size,sizeof(iflags.menu_tab_sep)),
WEAPON_META(tips,offsetof(__typeof__(svc),context.tips)),
WEAPON_META(tips_size,sizeof(svc.context.tips)),
WEAPON_META(zeroany,offsetof(__typeof__(cg),zeroany)),
WEAPON_META(zeroany_size,sizeof(cg.zeroany)),
WEAPON_META(debug,offsetof(__typeof__(flags),debug)),
WEAPON_META(debug_size,sizeof(flags.debug)),
WEAPON_META(vizArray,offsetof(__typeof__(gv),viz_array)),
WEAPON_META(vizArray_size,sizeof(gv.viz_array)),
WEAPON_META(ACID_VENOM,ACID_VENOM),
WEAPON_META(AKLYS,AKLYS),
WEAPON_META(ARROW,ARROW),
WEAPON_META(ART_EYES_OF_THE_OVERWORLD,ART_EYES_OF_THE_OVERWORLD),
WEAPON_META(ART_SNICKERSNEE,ART_SNICKERSNEE),
WEAPON_META(ATHAME,ATHAME),
WEAPON_META(ATR_NONE,ATR_NONE),
WEAPON_META(AT_WEAP,AT_WEAP),
WEAPON_META(AXE,AXE),
WEAPON_META(A_DEX,A_DEX),
WEAPON_META(A_STR,A_STR),
WEAPON_META(BALL_CLASS,BALL_CLASS),
WEAPON_META(BARDICHE,BARDICHE),
WEAPON_META(BATTLE_AXE,BATTLE_AXE),
WEAPON_META(BEC_DE_CORBIN,BEC_DE_CORBIN),
WEAPON_META(BILL_GUISARME,BILL_GUISARME),
WEAPON_META(BOOMERANG,BOOMERANG),
WEAPON_META(BOULDER,BOULDER),
WEAPON_META(BOW,BOW),
WEAPON_META(BROADSWORD,BROADSWORD),
WEAPON_META(BUFSZ,BUFSZ),
WEAPON_META(BULLWHIP,BULLWHIP),
WEAPON_META(CHAIN_CLASS,CHAIN_CLASS),
WEAPON_META(CLUB,CLUB),
WEAPON_META(CORPSE,CORPSE),
WEAPON_META(CREAM_PIE,CREAM_PIE),
WEAPON_META(CROSSBOW,CROSSBOW),
WEAPON_META(CROSSBOW_BOLT,CROSSBOW_BOLT),
WEAPON_META(CRYSKNIFE,CRYSKNIFE),
WEAPON_META(DAGGER,DAGGER),
WEAPON_META(DART,DART),
WEAPON_META(DWARVISH_MATTOCK,DWARVISH_MATTOCK),
WEAPON_META(DWARVISH_SHORT_SWORD,DWARVISH_SHORT_SWORD),
WEAPON_META(DWARVISH_SPEAR,DWARVISH_SPEAR),
WEAPON_META(ECMD_OK,ECMD_OK),
WEAPON_META(EGG,EGG),
WEAPON_META(ELVEN_ARROW,ELVEN_ARROW),
WEAPON_META(ELVEN_BOW,ELVEN_BOW),
WEAPON_META(ELVEN_BROADSWORD,ELVEN_BROADSWORD),
WEAPON_META(ELVEN_DAGGER,ELVEN_DAGGER),
WEAPON_META(ELVEN_SHORT_SWORD,ELVEN_SHORT_SWORD),
WEAPON_META(ELVEN_SPEAR,ELVEN_SPEAR),
WEAPON_META(FAUCHARD,FAUCHARD),
WEAPON_META(FLAIL,FLAIL),
WEAPON_META(FLINT,FLINT),
WEAPON_META(GEM_CLASS,GEM_CLASS),
WEAPON_META(GLAIVE,GLAIVE),
WEAPON_META(GRAPPLING_HOOK,GRAPPLING_HOOK),
WEAPON_META(GUISARME,GUISARME),
WEAPON_META(HALBERD,HALBERD),
WEAPON_META(HAND,HAND),
WEAPON_META(HEAVY_IRON_BALL,HEAVY_IRON_BALL),
WEAPON_META(IRON_CHAIN,IRON_CHAIN),
WEAPON_META(JAVELIN,JAVELIN),
WEAPON_META(KATANA,KATANA),
WEAPON_META(KNIFE,KNIFE),
WEAPON_META(LANCE,LANCE),
WEAPON_META(LEATHER,LEATHER),
WEAPON_META(LOADSTONE,LOADSTONE),
WEAPON_META(LONG_SWORD,LONG_SWORD),
WEAPON_META(LUCERN_HAMMER,LUCERN_HAMMER),
WEAPON_META(LUCKSTONE,LUCKSTONE),
WEAPON_META(M1_ANIMAL,M1_ANIMAL),
WEAPON_META(M1_MINDLESS,M1_MINDLESS),
WEAPON_META(M1_SWIM,M1_SWIM),
WEAPON_META(M1_THICK_HIDE,M1_THICK_HIDE),
WEAPON_META(M1_WALLWALK,M1_WALLWALK),
WEAPON_META(M2_GIANT,M2_GIANT),
WEAPON_META(M2_JEWELS,M2_JEWELS),
WEAPON_META(M2_ROCKTHROW,M2_ROCKTHROW),
WEAPON_META(M2_STRONG,M2_STRONG),
WEAPON_META(MACE,MACE),
WEAPON_META(MAXULEV,MAXULEV),
WEAPON_META(MENU_BEHAVE_STANDARD,MENU_BEHAVE_STANDARD),
WEAPON_META(MENU_ITEMFLAGS_NONE,MENU_ITEMFLAGS_NONE),
WEAPON_META(MORNING_STAR,MORNING_STAR),
WEAPON_META(MZ_LARGE,MZ_LARGE),
WEAPON_META(NEED_AXE,NEED_AXE),
WEAPON_META(NEED_HTH_WEAPON,NEED_HTH_WEAPON),
WEAPON_META(NEED_PICK_AXE,NEED_PICK_AXE),
WEAPON_META(NEED_PICK_OR_AXE,NEED_PICK_OR_AXE),
WEAPON_META(NEED_RANGED_WEAPON,NEED_RANGED_WEAPON),
WEAPON_META(NEED_WEAPON,NEED_WEAPON),
WEAPON_META(NHW_MENU,NHW_MENU),
WEAPON_META(NON_PM,NON_PM),
WEAPON_META(NO_COLOR,NO_COLOR),
WEAPON_META(NO_WEAPON_WANTED,NO_WEAPON_WANTED),
WEAPON_META(OBJ_INVENT,OBJ_INVENT),
WEAPON_META(OBJ_MINVENT,OBJ_MINVENT),
WEAPON_META(ORCISH_ARROW,ORCISH_ARROW),
WEAPON_META(ORCISH_BOW,ORCISH_BOW),
WEAPON_META(ORCISH_DAGGER,ORCISH_DAGGER),
WEAPON_META(ORCISH_SHORT_SWORD,ORCISH_SHORT_SWORD),
WEAPON_META(ORCISH_SPEAR,ORCISH_SPEAR),
WEAPON_META(PARTISAN,PARTISAN),
WEAPON_META(PICK_AXE,PICK_AXE),
WEAPON_META(PICK_NONE,PICK_NONE),
WEAPON_META(PICK_ONE,PICK_ONE),
WEAPON_META(PM_ARCHEOLOGIST,PM_ARCHEOLOGIST),
WEAPON_META(PM_BALROG,PM_BALROG),
WEAPON_META(PM_CHICKATRICE,PM_CHICKATRICE),
WEAPON_META(PM_CLERIC,PM_CLERIC),
WEAPON_META(PM_COCKATRICE,PM_COCKATRICE),
WEAPON_META(PM_EARTH_ELEMENTAL,PM_EARTH_ELEMENTAL),
WEAPON_META(PM_GIANT_EEL,PM_GIANT_EEL),
WEAPON_META(PM_GREMLIN,PM_GREMLIN),
WEAPON_META(PM_HEALER,PM_HEALER),
WEAPON_META(PM_HILL_GIANT,PM_HILL_GIANT),
WEAPON_META(PM_HUMAN,PM_HUMAN),
WEAPON_META(PM_MONK,PM_MONK),
WEAPON_META(PM_PONY,PM_PONY),
WEAPON_META(PM_RED_DRAGON,PM_RED_DRAGON),
WEAPON_META(PM_SAMURAI,PM_SAMURAI),
WEAPON_META(PM_SHADE,PM_SHADE),
WEAPON_META(PM_WIZARD,PM_WIZARD),
WEAPON_META(PM_WOOD_GOLEM,PM_WOOD_GOLEM),
WEAPON_META(PM_XORN,PM_XORN),
WEAPON_META(PRONOUN_HALLU,PRONOUN_HALLU),
WEAPON_META(P_ATTACK_SPELL,P_ATTACK_SPELL),
WEAPON_META(P_AXE,P_AXE),
WEAPON_META(P_BARE_HANDED_COMBAT,P_BARE_HANDED_COMBAT),
WEAPON_META(P_BASIC,P_BASIC),
WEAPON_META(P_BOW,P_BOW),
WEAPON_META(P_CLERIC_SPELL,P_CLERIC_SPELL),
WEAPON_META(P_CROSSBOW,P_CROSSBOW),
WEAPON_META(P_DAGGER,P_DAGGER),
WEAPON_META(P_ENCHANTMENT_SPELL,P_ENCHANTMENT_SPELL),
WEAPON_META(P_EXPERT,P_EXPERT),
WEAPON_META(P_FIRST_H_TO_H,P_FIRST_H_TO_H),
WEAPON_META(P_FIRST_SPELL,P_FIRST_SPELL),
WEAPON_META(P_FIRST_WEAPON,P_FIRST_WEAPON),
WEAPON_META(P_FLAIL,P_FLAIL),
WEAPON_META(P_GRAND_MASTER,P_GRAND_MASTER),
WEAPON_META(P_HEALING_SPELL,P_HEALING_SPELL),
WEAPON_META(P_ISRESTRICTED,P_ISRESTRICTED),
WEAPON_META(P_LAST_H_TO_H,P_LAST_H_TO_H),
WEAPON_META(P_LAST_SPELL,P_LAST_SPELL),
WEAPON_META(P_LAST_WEAPON,P_LAST_WEAPON),
WEAPON_META(P_LONG_SWORD,P_LONG_SWORD),
WEAPON_META(P_MASTER,P_MASTER),
WEAPON_META(P_NONE,P_NONE),
WEAPON_META(P_NUM_SKILLS,P_NUM_SKILLS),
WEAPON_META(P_PICK_AXE,P_PICK_AXE),
WEAPON_META(P_RIDING,P_RIDING),
WEAPON_META(P_SKILLED,P_SKILLED),
WEAPON_META(P_SKILL_LIMIT,P_SKILL_LIMIT),
WEAPON_META(P_SLING,P_SLING),
WEAPON_META(P_SPEAR,P_SPEAR),
WEAPON_META(P_TWO_WEAPON_COMBAT,P_TWO_WEAPON_COMBAT),
WEAPON_META(P_UNSKILLED,P_UNSKILLED),
WEAPON_META(QUARTERSTAFF,QUARTERSTAFF),
WEAPON_META(RANSEUR,RANSEUR),
WEAPON_META(ROCK,ROCK),
WEAPON_META(ROOM,ROOM),
WEAPON_META(RUBBER_HOSE,RUBBER_HOSE),
WEAPON_META(RUNESWORD,RUNESWORD),
WEAPON_META(SCALPEL,SCALPEL),
WEAPON_META(SCIMITAR,SCIMITAR),
WEAPON_META(SHORT_SWORD,SHORT_SWORD),
WEAPON_META(SHURIKEN,SHURIKEN),
WEAPON_META(SILVER,SILVER),
WEAPON_META(SILVER_ARROW,SILVER_ARROW),
WEAPON_META(SILVER_DAGGER,SILVER_DAGGER),
WEAPON_META(SILVER_MACE,SILVER_MACE),
WEAPON_META(SILVER_SABER,SILVER_SABER),
WEAPON_META(SILVER_SPEAR,SILVER_SPEAR),
WEAPON_META(SLING,SLING),
WEAPON_META(SPEAR,SPEAR),
WEAPON_META(SPETUM,SPETUM),
WEAPON_META(SPE_FORCE_BOLT,SPE_FORCE_BOLT),
WEAPON_META(STATUE,STATUE),
WEAPON_META(STONE_RES,STONE_RES),
WEAPON_META(STRANGE_OBJECT,STRANGE_OBJECT),
WEAPON_META(S_DRAGON,S_DRAGON),
WEAPON_META(S_EEL,S_EEL),
WEAPON_META(S_GIANT,S_GIANT),
WEAPON_META(S_JABBERWOCK,S_JABBERWOCK),
WEAPON_META(S_KOP,S_KOP),
WEAPON_META(S_NAGA,S_NAGA),
WEAPON_META(S_SNAKE,S_SNAKE),
WEAPON_META(S_XORN,S_XORN),
WEAPON_META(TIN,TIN),
WEAPON_META(TIN_OPENER,TIN_OPENER),
WEAPON_META(TIP_ENHANCE,TIP_ENHANCE),
WEAPON_META(TOOL_CLASS,TOOL_CLASS),
WEAPON_META(TOUCHSTONE,TOUCHSTONE),
WEAPON_META(TOWEL,TOWEL),
WEAPON_META(TRIDENT,TRIDENT),
WEAPON_META(TSURUGI,TSURUGI),
WEAPON_META(TWO_HANDED_SWORD,TWO_HANDED_SWORD),
WEAPON_META(UNICORN_HORN,UNICORN_HORN),
WEAPON_META(VOULGE,VOULGE),
WEAPON_META(WAR_HAMMER,WAR_HAMMER),
WEAPON_META(WEAPON_CLASS,WEAPON_CLASS),
WEAPON_META(WORM_TOOTH,WORM_TOOTH),
WEAPON_META(WT_IRON_BALL_INCR,WT_IRON_BALL_INCR),
WEAPON_META(W_ARM,W_ARM),
WEAPON_META(W_ARMC,W_ARMC),
WEAPON_META(W_ARMG,W_ARMG),
WEAPON_META(W_ARMS,W_ARMS),
WEAPON_META(W_ARMU,W_ARMU),
WEAPON_META(W_RINGL,W_RINGL),
WEAPON_META(W_RINGR,W_RINGR),
WEAPON_META(W_WEP,W_WEP),
WEAPON_META(YA,YA),
WEAPON_META(YUMI,YUMI),
WEAPON_META(AKLYS_RANGE,(BOLT_LIM/2)*(BOLT_LIM/2)),
};
_Static_assert(sizeof(((struct obj*)0)->nobj)==8,"WEAPON obj_nobj width");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2,"WEAPON obj_otyp width");
_Static_assert((((__typeof__(((struct obj*)0)->otyp))-1)<0)==1,"WEAPON obj_otyp signedness");
_Static_assert(sizeof(((struct obj*)0)->oclass)==1,"WEAPON obj_oclass width");
_Static_assert((((__typeof__(((struct obj*)0)->oclass))-1)<0)==1,"WEAPON obj_oclass signedness");
_Static_assert(sizeof(((struct obj*)0)->oartifact)==1,"WEAPON obj_oartifact width");
_Static_assert((((__typeof__(((struct obj*)0)->oartifact))-1)<0)==1,"WEAPON obj_oartifact signedness");
_Static_assert(sizeof(((struct obj*)0)->spe)==1,"WEAPON obj_spe width");
_Static_assert((((__typeof__(((struct obj*)0)->spe))-1)<0)==1,"WEAPON obj_spe signedness");
_Static_assert(sizeof(((struct obj*)0)->owt)==4,"WEAPON obj_owt width");
_Static_assert((((__typeof__(((struct obj*)0)->owt))-1)<0)==0,"WEAPON obj_owt signedness");
_Static_assert(sizeof(((struct obj*)0)->quan)==8,"WEAPON obj_quan width");
_Static_assert((((__typeof__(((struct obj*)0)->quan))-1)<0)==1,"WEAPON obj_quan signedness");
_Static_assert(sizeof(((struct obj*)0)->owornmask)==8,"WEAPON obj_owornmask width");
_Static_assert((((__typeof__(((struct obj*)0)->owornmask))-1)<0)==1,"WEAPON obj_owornmask signedness");
_Static_assert(sizeof(((struct obj*)0)->corpsenm)==4,"WEAPON obj_corpsenm width");
_Static_assert((((__typeof__(((struct obj*)0)->corpsenm))-1)<0)==1,"WEAPON obj_corpsenm signedness");
_Static_assert(sizeof(((struct obj*)0)->where)==1,"WEAPON obj_where width");
_Static_assert((((__typeof__(((struct obj*)0)->where))-1)<0)==1,"WEAPON obj_where signedness");
_Static_assert(sizeof(((struct obj*)0)->ocarry)==8,"WEAPON obj_ocarry width");
_Static_assert(sizeof(((struct monst*)0)->data)==8,"WEAPON mon_data width");
_Static_assert(sizeof(((struct monst*)0)->minvent)==8,"WEAPON mon_minvent width");
_Static_assert(sizeof(((struct monst*)0)->mw)==8,"WEAPON mon_mw width");
_Static_assert(sizeof(((struct monst*)0)->weapon_check)==2,"WEAPON mon_weapon_check width");
_Static_assert((((__typeof__(((struct monst*)0)->weapon_check))-1)<0)==1,"WEAPON mon_weapon_check signedness");
_Static_assert(sizeof(((struct monst*)0)->mx)==2,"WEAPON mon_mx width");
_Static_assert((((__typeof__(((struct monst*)0)->mx))-1)<0)==1,"WEAPON mon_mx signedness");
_Static_assert(sizeof(((struct monst*)0)->my)==2,"WEAPON mon_my width");
_Static_assert((((__typeof__(((struct monst*)0)->my))-1)<0)==1,"WEAPON mon_my signedness");
_Static_assert(sizeof(((struct monst*)0)->mux)==2,"WEAPON mon_mux width");
_Static_assert((((__typeof__(((struct monst*)0)->mux))-1)<0)==1,"WEAPON mon_mux signedness");
_Static_assert(sizeof(((struct monst*)0)->muy)==2,"WEAPON mon_muy width");
_Static_assert((((__typeof__(((struct monst*)0)->muy))-1)<0)==1,"WEAPON mon_muy signedness");
_Static_assert(sizeof(((struct monst*)0)->misc_worn_check)==8,"WEAPON mon_misc_worn_check width");
_Static_assert((((__typeof__(((struct monst*)0)->misc_worn_check))-1)<0)==1,"WEAPON mon_misc_worn_check signedness");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1,"WEAPON pm_mlet width");
_Static_assert((((__typeof__(((struct permonst*)0)->mlet))-1)<0)==1,"WEAPON pm_mlet signedness");
_Static_assert(sizeof(((struct permonst*)0)->msize)==1,"WEAPON pm_msize width");
_Static_assert((((__typeof__(((struct permonst*)0)->msize))-1)<0)==0,"WEAPON pm_msize signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8,"WEAPON pm_mflags1 width");
_Static_assert((((__typeof__(((struct permonst*)0)->mflags1))-1)<0)==0,"WEAPON pm_mflags1 signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8,"WEAPON pm_mflags2 width");
_Static_assert((((__typeof__(((struct permonst*)0)->mflags2))-1)<0)==0,"WEAPON pm_mflags2 signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_name_idx)==2,"WEAPON cls_oc_name_idx width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_name_idx))-1)<0)==1,"WEAPON cls_oc_name_idx signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_skill)==1,"WEAPON cls_oc_skill width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_skill))-1)<0)==1,"WEAPON cls_oc_skill signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_hitbon)==1,"WEAPON cls_oc_hitbon width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_hitbon))-1)<0)==1,"WEAPON cls_oc_hitbon signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_wldam)==1,"WEAPON cls_oc_wldam width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_wldam))-1)<0)==1,"WEAPON cls_oc_wldam signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_wsdam)==1,"WEAPON cls_oc_wsdam width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_wsdam))-1)<0)==1,"WEAPON cls_oc_wsdam signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_weight)==4,"WEAPON cls_oc_weight width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_weight))-1)<0)==0,"WEAPON cls_oc_weight signedness");
_Static_assert(sizeof(((struct objdescr*)0)->oc_name)==8,"WEAPON descr_oc_name width");
_Static_assert(sizeof(((struct you*)0)->weapon_slots)==4,"WEAPON u_weapon_slots width");
_Static_assert((((__typeof__(((struct you*)0)->weapon_slots))-1)<0)==1,"WEAPON u_weapon_slots signedness");
_Static_assert(sizeof(((struct you*)0)->skills_advanced)==4,"WEAPON u_skills_advanced width");
_Static_assert((((__typeof__(((struct you*)0)->skills_advanced))-1)<0)==1,"WEAPON u_skills_advanced signedness");
_Static_assert(sizeof(((struct you*)0)->twoweap)==1,"WEAPON u_twoweap width");
_Static_assert((((__typeof__(((struct you*)0)->twoweap))-1)<0)==1,"WEAPON u_twoweap signedness");
_Static_assert(sizeof(((struct you*)0)->usteed)==8,"WEAPON u_usteed width");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4,"WEAPON u_umonnum width");
_Static_assert((((__typeof__(((struct you*)0)->umonnum))-1)<0)==1,"WEAPON u_umonnum signedness");
_Static_assert(sizeof(((struct you*)0)->umonster)==4,"WEAPON u_umonster width");
_Static_assert((((__typeof__(((struct you*)0)->umonster))-1)<0)==1,"WEAPON u_umonster signedness");
_Static_assert(sizeof(((struct you*)0)->ulevel)==4,"WEAPON u_ulevel width");
_Static_assert((((__typeof__(((struct you*)0)->ulevel))-1)<0)==1,"WEAPON u_ulevel signedness");
_Static_assert(sizeof(((struct you*)0)->ux)==2,"WEAPON u_ux width");
_Static_assert((((__typeof__(((struct you*)0)->ux))-1)<0)==1,"WEAPON u_ux signedness");
_Static_assert(sizeof(((struct you*)0)->uy)==2,"WEAPON u_uy width");
_Static_assert((((__typeof__(((struct you*)0)->uy))-1)<0)==1,"WEAPON u_uy signedness");
_Static_assert(sizeof(((struct you*)0)->uroleplay.pauper)==1,"WEAPON u_uroleplay_pauper width");
_Static_assert((((__typeof__(((struct you*)0)->uroleplay.pauper))-1)<0)==1,"WEAPON u_uroleplay_pauper signedness");
_Static_assert(sizeof(((struct skills*)0)->skill)==2,"WEAPON skill_skill width");
_Static_assert((((__typeof__(((struct skills*)0)->skill))-1)<0)==1,"WEAPON skill_skill signedness");
_Static_assert(sizeof(((struct skills*)0)->max_skill)==2,"WEAPON skill_max_skill width");
_Static_assert((((__typeof__(((struct skills*)0)->max_skill))-1)<0)==1,"WEAPON skill_max_skill signedness");
_Static_assert(sizeof(((struct skills*)0)->advance)==2,"WEAPON skill_advance width");
_Static_assert((((__typeof__(((struct skills*)0)->advance))-1)<0)==0,"WEAPON skill_advance signedness");
_Static_assert(sizeof(((struct def_skill*)0)->skill)==2,"WEAPON defskill_skill width");
_Static_assert((((__typeof__(((struct def_skill*)0)->skill))-1)<0)==1,"WEAPON defskill_skill signedness");
_Static_assert(sizeof(((struct def_skill*)0)->skmax)==2,"WEAPON defskill_skmax width");
_Static_assert((((__typeof__(((struct def_skill*)0)->skmax))-1)<0)==1,"WEAPON defskill_skmax signedness");
_Static_assert(sizeof(((struct throw_and_return_weapon*)0)->otyp)==2,"WEAPON arw_otyp width");
_Static_assert((((__typeof__(((struct throw_and_return_weapon*)0)->otyp))-1)<0)==1,"WEAPON arw_otyp signedness");
_Static_assert(sizeof(((struct throw_and_return_weapon*)0)->range)==4,"WEAPON arw_range width");
_Static_assert((((__typeof__(((struct throw_and_return_weapon*)0)->range))-1)<0)==1,"WEAPON arw_range signedness");
_Static_assert(sizeof(((struct class_sym*)0)->name)==8,"WEAPON classsym_name width");
_Static_assert(sizeof(((struct Gender*)0)->his)==8,"WEAPON gender_his width");
_Static_assert(sizeof(((anything*)0)->a_int)==4,"WEAPON any_a_int width");
_Static_assert((((__typeof__(((anything*)0)->a_int))-1)<0)==1,"WEAPON any_a_int signedness");
_Static_assert(sizeof(gu.urole.mnum)==2,"WEAPON roleMnum width");
_Static_assert(sizeof(gu.urole.petnum)==2,"WEAPON petnum width");
_Static_assert(sizeof(gu.urole.spelspec)==4,"WEAPON spelspec width");
_Static_assert(sizeof(gu.unweapon)==1,"WEAPON unweapon width");
_Static_assert(sizeof(iflags.menu_tab_sep)==1,"WEAPON menu_tab_sep width");
_Static_assert(sizeof(svc.context.tips)==8,"WEAPON tips width");
_Static_assert(sizeof(flags.debug)==1,"WEAPON debug width");
#undef WEAPON_META
#endif
