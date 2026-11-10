/* Native metadata/header constants only; worn policy and catalogue remain JavaScript. */
#include "hack.h"
#include <stddef.h>
struct worn_meta {const char *name;size_t value;};
#define WORN_META(k,v) {#k,(size_t)(v)}
static const struct worn_meta worn_layout[]={
WORN_META(pointerSize,sizeof(void*)),
WORN_META(intSize,sizeof(int)),
WORN_META(longSize,sizeof(long)),
WORN_META(shortSize,sizeof(short)),
WORN_META(charSize,sizeof(char)),
WORN_META(booleanSize,sizeof(boolean)),
WORN_META(coordSize,sizeof(coordxy)),
WORN_META(objectSize,sizeof(struct obj)),
WORN_META(monsterSize,sizeof(struct monst)),
WORN_META(permonstSize,sizeof(struct permonst)),
WORN_META(objectClassSize,sizeof(struct objclass)),
WORN_META(propSize,sizeof(struct prop)),
WORN_META(lootSize,sizeof(Loot)),
WORN_META(mextraSize,sizeof(struct mextra)),
WORN_META(genderSize,sizeof(genders[0])),
WORN_META(BUFSZ,BUFSZ),
WORN_META(anotherSize,sizeof "another "),
WORN_META(obj_otyp,offsetof(struct obj,otyp)),
WORN_META(obj_otyp_size,sizeof(((struct obj*)0)->otyp)),
WORN_META(obj_oclass,offsetof(struct obj,oclass)),
WORN_META(obj_oclass_size,sizeof(((struct obj*)0)->oclass)),
WORN_META(obj_oartifact,offsetof(struct obj,oartifact)),
WORN_META(obj_oartifact_size,sizeof(((struct obj*)0)->oartifact)),
WORN_META(obj_owornmask,offsetof(struct obj,owornmask)),
WORN_META(obj_owornmask_size,sizeof(((struct obj*)0)->owornmask)),
WORN_META(obj_where,offsetof(struct obj,where)),
WORN_META(obj_where_size,sizeof(((struct obj*)0)->where)),
WORN_META(obj_spe,offsetof(struct obj,spe)),
WORN_META(obj_spe_size,sizeof(((struct obj*)0)->spe)),
WORN_META(obj_nobj,offsetof(struct obj,nobj)),
WORN_META(obj_nobj_size,sizeof(((struct obj*)0)->nobj)),
WORN_META(obj_cobj,offsetof(struct obj,cobj)),
WORN_META(obj_cobj_size,sizeof(((struct obj*)0)->cobj)),
WORN_META(mon_data,offsetof(struct monst,data)),
WORN_META(mon_data_size,sizeof(((struct monst*)0)->data)),
WORN_META(mon_nmon,offsetof(struct monst,nmon)),
WORN_META(mon_nmon_size,sizeof(((struct monst*)0)->nmon)),
WORN_META(mon_minvent,offsetof(struct monst,minvent)),
WORN_META(mon_minvent_size,sizeof(((struct monst*)0)->minvent)),
WORN_META(mon_mw,offsetof(struct monst,mw)),
WORN_META(mon_mw_size,sizeof(((struct monst*)0)->mw)),
WORN_META(mon_mextra,offsetof(struct monst,mextra)),
WORN_META(mon_mextra_size,sizeof(((struct monst*)0)->mextra)),
WORN_META(mon_mhp,offsetof(struct monst,mhp)),
WORN_META(mon_mhp_size,sizeof(((struct monst*)0)->mhp)),
WORN_META(mon_mx,offsetof(struct monst,mx)),
WORN_META(mon_mx_size,sizeof(((struct monst*)0)->mx)),
WORN_META(mon_my,offsetof(struct monst,my)),
WORN_META(mon_my_size,sizeof(((struct monst*)0)->my)),
WORN_META(mon_mextrinsics,offsetof(struct monst,mextrinsics)),
WORN_META(mon_mextrinsics_size,sizeof(((struct monst*)0)->mextrinsics)),
WORN_META(mon_misc_worn_check,offsetof(struct monst,misc_worn_check)),
WORN_META(mon_misc_worn_check_size,sizeof(((struct monst*)0)->misc_worn_check)),
WORN_META(pm_msize,offsetof(struct permonst,msize)),
WORN_META(pm_msize_size,sizeof(((struct permonst*)0)->msize)),
WORN_META(pm_mlet,offsetof(struct permonst,mlet)),
WORN_META(pm_mlet_size,sizeof(((struct permonst*)0)->mlet)),
WORN_META(pm_mmove,offsetof(struct permonst,mmove)),
WORN_META(pm_mmove_size,sizeof(((struct permonst*)0)->mmove)),
WORN_META(pm_ac,offsetof(struct permonst,ac)),
WORN_META(pm_ac_size,sizeof(((struct permonst*)0)->ac)),
WORN_META(pm_mflags1,offsetof(struct permonst,mflags1)),
WORN_META(pm_mflags1_size,sizeof(((struct permonst*)0)->mflags1)),
WORN_META(pm_mflags2,offsetof(struct permonst,mflags2)),
WORN_META(pm_mflags2_size,sizeof(((struct permonst*)0)->mflags2)),
WORN_META(cls_oc_oprop,offsetof(struct objclass,oc_oprop)),
WORN_META(cls_oc_oprop_size,sizeof(((struct objclass*)0)->oc_oprop)),
WORN_META(cls_oc_delay,offsetof(struct objclass,oc_delay)),
WORN_META(cls_oc_delay_size,sizeof(((struct objclass*)0)->oc_delay)),
WORN_META(cls_oc_skill,offsetof(struct objclass,oc_skill)),
WORN_META(cls_oc_skill_size,sizeof(((struct objclass*)0)->oc_skill)),
WORN_META(cls_oc_armcat,offsetof(struct objclass,oc_armcat)),
WORN_META(cls_oc_armcat_size,sizeof(((struct objclass*)0)->oc_armcat)),
WORN_META(cls_a_ac,offsetof(struct objclass,a_ac)),
WORN_META(cls_a_ac_size,sizeof(((struct objclass*)0)->a_ac)),
WORN_META(u_twoweap,offsetof(struct you,twoweap)),
WORN_META(u_twoweap_size,sizeof(((struct you*)0)->twoweap)),
WORN_META(u_umonnum,offsetof(struct you,umonnum)),
WORN_META(u_umonnum_size,sizeof(((struct you*)0)->umonnum)),
WORN_META(u_unblind_telepat_range,offsetof(struct you,unblind_telepat_range)),
WORN_META(u_unblind_telepat_range_size,sizeof(((struct you*)0)->unblind_telepat_range)),
WORN_META(u_uroleplay_nudist,offsetof(struct you,uroleplay.nudist)),
WORN_META(u_uroleplay_nudist_size,sizeof(((struct you*)0)->uroleplay.nudist)),
WORN_META(u_usteed,offsetof(struct you,usteed)),
WORN_META(u_usteed_size,sizeof(((struct you*)0)->usteed)),
WORN_META(u_uprops,offsetof(struct you,uprops)),
WORN_META(u_uprops_size,sizeof(((struct you*)0)->uprops)),
WORN_META(prop_intrinsic,offsetof(struct prop,intrinsic)),
WORN_META(prop_intrinsic_size,sizeof(((struct prop*)0)->intrinsic)),
WORN_META(prop_extrinsic,offsetof(struct prop,extrinsic)),
WORN_META(prop_extrinsic_size,sizeof(((struct prop*)0)->extrinsic)),
WORN_META(prop_blocked,offsetof(struct prop,blocked)),
WORN_META(prop_blocked_size,sizeof(((struct prop*)0)->blocked)),
WORN_META(loot_obj,offsetof(Loot,obj)),
WORN_META(loot_obj_size,sizeof(((Loot*)0)->obj)),
WORN_META(mextra_mcorpsenm,offsetof(struct mextra,mcorpsenm)),
WORN_META(mextra_mcorpsenm_size,sizeof(((struct mextra*)0)->mcorpsenm)),
WORN_META(gender_him,offsetof(struct Gender,him)),
WORN_META(gender_him_size,sizeof(((struct Gender*)0)->him)),
WORN_META(gender_his,offsetof(struct Gender,his)),
WORN_META(gender_his_size,sizeof(((struct Gender*)0)->his)),
WORN_META(youmonst,offsetof(__typeof__(gy),youmonst)),
WORN_META(youmonst_size,sizeof(((__typeof__(gy)*)0)->youmonst)),
WORN_META(invent,offsetof(__typeof__(gi),invent)),
WORN_META(invent_size,sizeof(((__typeof__(gi)*)0)->invent)),
WORN_META(in_mklev,offsetof(__typeof__(gi),in_mklev)),
WORN_META(in_mklev_size,sizeof(((__typeof__(gi)*)0)->in_mklev)),
WORN_META(roleMnum,offsetof(__typeof__(gu),urole.mnum)),
WORN_META(roleMnum_size,sizeof(((__typeof__(gu)*)0)->urole.mnum)),
WORN_META(roleSpelarmr,offsetof(__typeof__(gu),urole.spelarmr)),
WORN_META(roleSpelarmr_size,sizeof(((__typeof__(gu)*)0)->urole.spelarmr)),
WORN_META(verbose,offsetof(__typeof__(flags),verbose)),
WORN_META(verbose_size,sizeof(((__typeof__(flags)*)0)->verbose)),
WORN_META(weaponstatus,offsetof(__typeof__(flags),weaponstatus)),
WORN_META(weaponstatus_size,sizeof(((__typeof__(flags)*)0)->weaponstatus)),
WORN_META(armorstatus,offsetof(__typeof__(flags),armorstatus)),
WORN_META(armorstatus_size,sizeof(((__typeof__(flags)*)0)->armorstatus)),
WORN_META(tux_penalty,offsetof(__typeof__(iflags),tux_penalty)),
WORN_META(tux_penalty_size,sizeof(((__typeof__(iflags)*)0)->tux_penalty)),
WORN_META(botl,offsetof(__typeof__(disp),botl)),
WORN_META(botl_size,sizeof(((__typeof__(disp)*)0)->botl)),
WORN_META(bypasses,offsetof(__typeof__(svc),context.bypasses)),
WORN_META(bypasses_size,sizeof(((__typeof__(svc)*)0)->context.bypasses)),
WORN_META(fmon,offsetof(__typeof__(svl),level.monlist)),
WORN_META(fmon_size,sizeof(((__typeof__(svl)*)0)->level.monlist)),
WORN_META(fobj,offsetof(__typeof__(svl),level.objlist)),
WORN_META(fobj_size,sizeof(((__typeof__(svl)*)0)->level.objlist)),
WORN_META(buriedobjlist,offsetof(__typeof__(svl),level.buriedobjlist)),
WORN_META(buriedobjlist_size,sizeof(((__typeof__(svl)*)0)->level.buriedobjlist)),
WORN_META(migrating_mons,offsetof(__typeof__(gm),migrating_mons)),
WORN_META(migrating_mons_size,sizeof(((__typeof__(gm)*)0)->migrating_mons)),
WORN_META(migrating_objs,offsetof(__typeof__(gm),migrating_objs)),
WORN_META(migrating_objs_size,sizeof(((__typeof__(gm)*)0)->migrating_objs)),
WORN_META(mydogs,offsetof(__typeof__(gm),mydogs)),
WORN_META(mydogs_size,sizeof(((__typeof__(gm)*)0)->mydogs)),
WORN_META(billobjs,offsetof(__typeof__(gb),billobjs)),
WORN_META(billobjs_size,sizeof(((__typeof__(gb)*)0)->billobjs)),
WORN_META(objs_deleted,offsetof(__typeof__(go),objs_deleted)),
WORN_META(objs_deleted_size,sizeof(((__typeof__(go)*)0)->objs_deleted)),
WORN_META(vizArray,offsetof(__typeof__(gv),viz_array)),
WORN_META(vizArray_size,sizeof(((__typeof__(gv)*)0)->viz_array)),
WORN_META(ACID_RES,ACID_RES),
WORN_META(AC_MAX,AC_MAX),
WORN_META(ALCHEMY_SMOCK,ALCHEMY_SMOCK),
WORN_META(AMULET_CLASS,AMULET_CLASS),
WORN_META(AMULET_OF_GUARDING,AMULET_OF_GUARDING),
WORN_META(AMULET_OF_LIFE_SAVING,AMULET_OF_LIFE_SAVING),
WORN_META(AMULET_OF_REFLECTION,AMULET_OF_REFLECTION),
WORN_META(ANTIMAGIC,ANTIMAGIC),
WORN_META(ARMOR_CLASS,ARMOR_CLASS),
WORN_META(ARM_BOOTS,ARM_BOOTS),
WORN_META(ARM_CLOAK,ARM_CLOAK),
WORN_META(ARM_GLOVES,ARM_GLOVES),
WORN_META(ARM_HELM,ARM_HELM),
WORN_META(ARM_SHIELD,ARM_SHIELD),
WORN_META(ARM_SHIRT,ARM_SHIRT),
WORN_META(ARM_SUIT,ARM_SUIT),
WORN_META(ART_EYES_OF_THE_OVERWORLD,ART_EYES_OF_THE_OVERWORLD),
WORN_META(BALL_CLASS,BALL_CLASS),
WORN_META(BLINDED,BLINDED),
WORN_META(BLINDFOLD,BLINDFOLD),
WORN_META(BOLT_LIM,BOLT_LIM),
WORN_META(CHAIN_CLASS,CHAIN_CLASS),
WORN_META(CLAIRVOYANT,CLAIRVOYANT),
WORN_META(COLD_RES,COLD_RES),
WORN_META(CORNUTHAUM,CORNUTHAUM),
WORN_META(COULD_SEE,COULD_SEE),
WORN_META(DAGGER,DAGGER),
WORN_META(DISINT_RES,DISINT_RES),
WORN_META(DISMOUNT_FELL,DISMOUNT_FELL),
WORN_META(DISPLACED,DISPLACED),
WORN_META(DUNCE_CAP,DUNCE_CAP),
WORN_META(ELVEN_BOOTS,ELVEN_BOOTS),
WORN_META(ELVEN_CLOAK,ELVEN_CLOAK),
WORN_META(ELVEN_LEATHER_HELM,ELVEN_LEATHER_HELM),
WORN_META(ELVEN_MITHRIL_COAT,ELVEN_MITHRIL_COAT),
WORN_META(ELVEN_SHIELD,ELVEN_SHIELD),
WORN_META(FAST,FAST),
WORN_META(FIRE_RES,FIRE_RES),
WORN_META(FLYING,FLYING),
WORN_META(FOOD_CLASS,FOOD_CLASS),
WORN_META(FUMBLING,FUMBLING),
WORN_META(GEM_CLASS,GEM_CLASS),
WORN_META(GRAY_DRAGON_SCALES,GRAY_DRAGON_SCALES),
WORN_META(GRAY_DRAGON_SCALE_MAIL,GRAY_DRAGON_SCALE_MAIL),
WORN_META(HELM_OF_OPPOSITE_ALIGNMENT,HELM_OF_OPPOSITE_ALIGNMENT),
WORN_META(INVIS,INVIS),
WORN_META(IN_SIGHT,IN_SIGHT),
WORN_META(I_SPECIAL,I_SPECIAL),
WORN_META(JUMPING,JUMPING),
WORN_META(LEATHER,LEATHER),
WORN_META(LENSES,LENSES),
WORN_META(LEVITATION,LEVITATION),
WORN_META(LONG_SWORD,LONG_SWORD),
WORN_META(M1_ANIMAL,M1_ANIMAL),
WORN_META(M1_HUMANOID,M1_HUMANOID),
WORN_META(M1_MINDLESS,M1_MINDLESS),
WORN_META(M1_NOHANDS,M1_NOHANDS),
WORN_META(M1_SLITHY,M1_SLITHY),
WORN_META(MEAT_RING,MEAT_RING),
WORN_META(MFAST,MFAST),
WORN_META(MSLOW,MSLOW),
WORN_META(MUMMY_WRAPPING,MUMMY_WRAPPING),
WORN_META(MZ_HUGE,MZ_HUGE),
WORN_META(MZ_HUMAN,MZ_HUMAN),
WORN_META(MZ_LARGE,MZ_LARGE),
WORN_META(MZ_SMALL,MZ_SMALL),
WORN_META(NEUTRAL,NEUTRAL),
WORN_META(NON_PM,NON_PM),
WORN_META(OBJ_MINVENT,OBJ_MINVENT),
WORN_META(PM_AIR_ELEMENTAL,PM_AIR_ELEMENTAL),
WORN_META(PM_GRAY_DRAGON,PM_GRAY_DRAGON),
WORN_META(PM_HOBBIT,PM_HOBBIT),
WORN_META(PM_HUMAN,PM_HUMAN),
WORN_META(HAWAIIAN_SHIRT,HAWAIIAN_SHIRT),
WORN_META(HELMET,HELMET),
WORN_META(LEATHER_GLOVES,LEATHER_GLOVES),
WORN_META(MAGIC_MARKER,MAGIC_MARKER),
WORN_META(NUMMONS,NUMMONS),
WORN_META(NUM_OBJECTS,NUM_OBJECTS),
WORN_META(OBJ_FLOOR,OBJ_FLOOR),
WORN_META(OBJ_FREE,OBJ_FREE),
WORN_META(OBJ_INVENT,OBJ_INVENT),
WORN_META(PLATE_MAIL,PLATE_MAIL),
WORN_META(PM_FOG_CLOUD,PM_FOG_CLOUD),
WORN_META(PM_GHOST,PM_GHOST),
WORN_META(PM_GNOME,PM_GNOME),
WORN_META(PM_HORSE,PM_HORSE),
WORN_META(PM_IRON_GOLEM,PM_IRON_GOLEM),
WORN_META(PM_KOBOLD,PM_KOBOLD),
WORN_META(PM_MINOTAUR,PM_MINOTAUR),
WORN_META(PM_PLAINS_CENTAUR,PM_PLAINS_CENTAUR),
WORN_META(TWO_HANDED_SWORD,TWO_HANDED_SWORD),
WORN_META(PM_COCKATRICE,PM_COCKATRICE),
WORN_META(PM_CHICKATRICE,PM_CHICKATRICE),
WORN_META(PM_LONG_WORM,PM_LONG_WORM),
WORN_META(PM_MARILITH,PM_MARILITH),
WORN_META(PM_MONK,PM_MONK),
WORN_META(PM_SKELETON,PM_SKELETON),
WORN_META(PM_WINGED_GARGOYLE,PM_WINGED_GARGOYLE),
WORN_META(PM_WIZARD,PM_WIZARD),
WORN_META(POISON_RES,POISON_RES),
WORN_META(PRONOUN_HALLU,PRONOUN_HALLU),
WORN_META(PROTECTION,PROTECTION),
WORN_META(P_NONE,P_NONE),
WORN_META(REFLECTING,REFLECTING),
WORN_META(RING_CLASS,RING_CLASS),
WORN_META(RUBBER_HOSE,RUBBER_HOSE),
WORN_META(SADDLE,SADDLE),
WORN_META(SEE_INVIS,SEE_INVIS),
WORN_META(SHOCK_RES,SHOCK_RES),
WORN_META(SLEEP_RES,SLEEP_RES),
WORN_META(SPEED_BOOTS,SPEED_BOOTS),
WORN_META(STEALTH,STEALTH),
WORN_META(STONE_RES,STONE_RES),
WORN_META(S_CENTAUR,S_CENTAUR),
WORN_META(S_GHOST,S_GHOST),
WORN_META(S_MUMMY,S_MUMMY),
WORN_META(S_VORTEX,S_VORTEX),
WORN_META(TELEPAT,TELEPAT),
WORN_META(TIN_OPENER,TIN_OPENER),
WORN_META(TOOL_CLASS,TOOL_CLASS),
WORN_META(TOWEL,TOWEL),
WORN_META(WEAPON_CLASS,WEAPON_CLASS),
WORN_META(WWALKING,WWALKING),
WORN_META(W_AMUL,W_AMUL),
WORN_META(W_ARM,W_ARM),
WORN_META(W_ARMC,W_ARMC),
WORN_META(W_ARMF,W_ARMF),
WORN_META(W_ARMG,W_ARMG),
WORN_META(W_ARMH,W_ARMH),
WORN_META(W_ARMOR,W_ARMOR),
WORN_META(W_ARMS,W_ARMS),
WORN_META(W_ARMU,W_ARMU),
WORN_META(W_ART,W_ART),
WORN_META(W_ARTI,W_ARTI),
WORN_META(W_BALL,W_BALL),
WORN_META(W_CHAIN,W_CHAIN),
WORN_META(W_QUIVER,W_QUIVER),
WORN_META(W_RINGL,W_RINGL),
WORN_META(W_RINGR,W_RINGR),
WORN_META(W_SADDLE,W_SADDLE),
WORN_META(W_SWAPWEP,W_SWAPWEP),
WORN_META(W_TOOL,W_TOOL),
WORN_META(W_WEP,W_WEP),
WORN_META(YELLOW_DRAGON_SCALES,YELLOW_DRAGON_SCALES),
WORN_META(YELLOW_DRAGON_SCALE_MAIL,YELLOW_DRAGON_SCALE_MAIL),
#ifdef EXTRA_SANITY_CHECKS
WORN_META(config_EXTRA_SANITY_CHECKS,1),
#else
WORN_META(config_EXTRA_SANITY_CHECKS,0),
#endif
#ifdef SND_LIB_INTEGRATED
WORN_META(config_SND_LIB_INTEGRATED,1),
#else
WORN_META(config_SND_LIB_INTEGRATED,0),
#endif
};
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(int)==4,"worn memory64 widths");
_Static_assert(sizeof(boolean)==1 && (boolean)-1<0,"signed boolean8");
_Static_assert(sizeof(char)==1 && (char)-1<0,"signed char8");
_Static_assert(sizeof(coordxy)==2 && (coordxy)-1<0,"signed coord16");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2,"obj_otyp width");
_Static_assert(((__typeof__(((struct obj*)0)->otyp))-1 < 0),"obj_otyp signedness");
_Static_assert(sizeof(((struct obj*)0)->oclass)==1,"obj_oclass width");
_Static_assert(((__typeof__(((struct obj*)0)->oclass))-1 < 0),"obj_oclass signedness");
_Static_assert(sizeof(((struct obj*)0)->oartifact)==1,"obj_oartifact width");
_Static_assert(((__typeof__(((struct obj*)0)->oartifact))-1 < 0),"obj_oartifact signedness");
_Static_assert(sizeof(((struct obj*)0)->owornmask)==8,"obj_owornmask width");
_Static_assert(((__typeof__(((struct obj*)0)->owornmask))-1 < 0),"obj_owornmask signedness");
_Static_assert(sizeof(((struct obj*)0)->where)==1,"obj_where width");
_Static_assert(((__typeof__(((struct obj*)0)->where))-1 < 0),"obj_where signedness");
_Static_assert(sizeof(((struct obj*)0)->spe)==1,"obj_spe width");
_Static_assert(((__typeof__(((struct obj*)0)->spe))-1 < 0),"obj_spe signedness");
_Static_assert(sizeof(((struct obj*)0)->nobj)==8,"obj_nobj width");
_Static_assert(sizeof(((struct obj*)0)->cobj)==8,"obj_cobj width");
_Static_assert(sizeof(((struct monst*)0)->data)==8,"mon_data width");
_Static_assert(sizeof(((struct monst*)0)->nmon)==8,"mon_nmon width");
_Static_assert(sizeof(((struct monst*)0)->minvent)==8,"mon_minvent width");
_Static_assert(sizeof(((struct monst*)0)->mw)==8,"mon_mw width");
_Static_assert(sizeof(((struct monst*)0)->mextra)==8,"mon_mextra width");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4,"mon_mhp width");
_Static_assert(((__typeof__(((struct monst*)0)->mhp))-1 < 0),"mon_mhp signedness");
_Static_assert(sizeof(((struct monst*)0)->mx)==2,"mon_mx width");
_Static_assert(((__typeof__(((struct monst*)0)->mx))-1 < 0),"mon_mx signedness");
_Static_assert(sizeof(((struct monst*)0)->my)==2,"mon_my width");
_Static_assert(((__typeof__(((struct monst*)0)->my))-1 < 0),"mon_my signedness");
_Static_assert(sizeof(((struct monst*)0)->mextrinsics)==2,"mon_mextrinsics width");
_Static_assert(((__typeof__(((struct monst*)0)->mextrinsics))-1 > 0),"mon_mextrinsics signedness");
_Static_assert(sizeof(((struct monst*)0)->misc_worn_check)==8,"mon_misc_worn_check width");
_Static_assert(((__typeof__(((struct monst*)0)->misc_worn_check))-1 < 0),"mon_misc_worn_check signedness");
_Static_assert(sizeof(((struct permonst*)0)->msize)==1,"pm_msize width");
_Static_assert(((__typeof__(((struct permonst*)0)->msize))-1 > 0),"pm_msize signedness");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1,"pm_mlet width");
_Static_assert(((__typeof__(((struct permonst*)0)->mlet))-1 < 0),"pm_mlet signedness");
_Static_assert(sizeof(((struct permonst*)0)->mmove)==1,"pm_mmove width");
_Static_assert(((__typeof__(((struct permonst*)0)->mmove))-1 < 0),"pm_mmove signedness");
_Static_assert(sizeof(((struct permonst*)0)->ac)==1,"pm_ac width");
_Static_assert(((__typeof__(((struct permonst*)0)->ac))-1 < 0),"pm_ac signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8,"pm_mflags1 width");
_Static_assert(((__typeof__(((struct permonst*)0)->mflags1))-1 > 0),"pm_mflags1 signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8,"pm_mflags2 width");
_Static_assert(((__typeof__(((struct permonst*)0)->mflags2))-1 > 0),"pm_mflags2 signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_oprop)==1,"cls_oc_oprop width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_oprop))-1 > 0),"cls_oc_oprop signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_delay)==1,"cls_oc_delay width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_delay))-1 < 0),"cls_oc_delay signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_skill)==1,"cls_oc_skill width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_skill))-1 < 0),"cls_oc_skill signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_armcat)==1,"cls_oc_armcat width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_armcat))-1 < 0),"cls_oc_armcat signedness");
_Static_assert(sizeof(((struct objclass*)0)->a_ac)==1,"cls_a_ac width");
_Static_assert(((__typeof__(((struct objclass*)0)->a_ac))-1 < 0),"cls_a_ac signedness");
_Static_assert(sizeof(((struct you*)0)->twoweap)==1,"u_twoweap width");
_Static_assert(((__typeof__(((struct you*)0)->twoweap))-1 < 0),"u_twoweap signedness");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4,"u_umonnum width");
_Static_assert(((__typeof__(((struct you*)0)->umonnum))-1 < 0),"u_umonnum signedness");
_Static_assert(sizeof(((struct you*)0)->unblind_telepat_range)==4,"u_unblind_telepat_range width");
_Static_assert(((__typeof__(((struct you*)0)->unblind_telepat_range))-1 < 0),"u_unblind_telepat_range signedness");
_Static_assert(sizeof(((struct you*)0)->uroleplay.nudist)==1,"u_uroleplay_nudist width");
_Static_assert(((__typeof__(((struct you*)0)->uroleplay.nudist))-1 < 0),"u_uroleplay_nudist signedness");
_Static_assert(sizeof(((struct you*)0)->usteed)==8,"u_usteed width");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8,"prop_intrinsic width");
_Static_assert(((__typeof__(((struct prop*)0)->intrinsic))-1 < 0),"prop_intrinsic signedness");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8,"prop_extrinsic width");
_Static_assert(((__typeof__(((struct prop*)0)->extrinsic))-1 < 0),"prop_extrinsic signedness");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8,"prop_blocked width");
_Static_assert(((__typeof__(((struct prop*)0)->blocked))-1 < 0),"prop_blocked signedness");
_Static_assert(sizeof(((Loot*)0)->obj)==8,"loot_obj width");
_Static_assert(sizeof(((struct mextra*)0)->mcorpsenm)==4,"mextra_mcorpsenm width");
_Static_assert(((__typeof__(((struct mextra*)0)->mcorpsenm))-1 < 0),"mextra_mcorpsenm signedness");
_Static_assert(sizeof(((struct Gender*)0)->him)==8,"gender_him width");
_Static_assert(sizeof(((struct Gender*)0)->his)==8,"gender_his width");
_Static_assert(sizeof(((__typeof__(gi)*)0)->invent)==8,"invent width");
_Static_assert(sizeof(((__typeof__(gi)*)0)->in_mklev)==1,"in_mklev width");
_Static_assert(((__typeof__(((__typeof__(gi)*)0)->in_mklev))-1 < 0),"in_mklev signedness");
_Static_assert(sizeof(((__typeof__(gu)*)0)->urole.mnum)==2,"roleMnum width");
_Static_assert(((__typeof__(((__typeof__(gu)*)0)->urole.mnum))-1 < 0),"roleMnum signedness");
_Static_assert(sizeof(((__typeof__(gu)*)0)->urole.spelarmr)==4,"roleSpelarmr width");
_Static_assert(((__typeof__(((__typeof__(gu)*)0)->urole.spelarmr))-1 < 0),"roleSpelarmr signedness");
_Static_assert(sizeof(((__typeof__(flags)*)0)->verbose)==1,"verbose width");
_Static_assert(((__typeof__(((__typeof__(flags)*)0)->verbose))-1 < 0),"verbose signedness");
_Static_assert(sizeof(((__typeof__(flags)*)0)->weaponstatus)==1,"weaponstatus width");
_Static_assert(((__typeof__(((__typeof__(flags)*)0)->weaponstatus))-1 < 0),"weaponstatus signedness");
_Static_assert(sizeof(((__typeof__(flags)*)0)->armorstatus)==1,"armorstatus width");
_Static_assert(((__typeof__(((__typeof__(flags)*)0)->armorstatus))-1 < 0),"armorstatus signedness");
_Static_assert(sizeof(((__typeof__(iflags)*)0)->tux_penalty)==1,"tux_penalty width");
_Static_assert(((__typeof__(((__typeof__(iflags)*)0)->tux_penalty))-1 < 0),"tux_penalty signedness");
_Static_assert(sizeof(((__typeof__(disp)*)0)->botl)==1,"botl width");
_Static_assert(((__typeof__(((__typeof__(disp)*)0)->botl))-1 < 0),"botl signedness");
_Static_assert(sizeof(((__typeof__(svc)*)0)->context.bypasses)==1,"bypasses width");
_Static_assert(((__typeof__(((__typeof__(svc)*)0)->context.bypasses))-1 < 0),"bypasses signedness");
_Static_assert(sizeof(((__typeof__(svl)*)0)->level.monlist)==8,"fmon width");
_Static_assert(sizeof(((__typeof__(svl)*)0)->level.objlist)==8,"fobj width");
_Static_assert(sizeof(((__typeof__(svl)*)0)->level.buriedobjlist)==8,"buriedobjlist width");
_Static_assert(sizeof(((__typeof__(gm)*)0)->migrating_mons)==8,"migrating_mons width");
_Static_assert(sizeof(((__typeof__(gm)*)0)->migrating_objs)==8,"migrating_objs width");
_Static_assert(sizeof(((__typeof__(gm)*)0)->mydogs)==8,"mydogs width");
_Static_assert(sizeof(((__typeof__(gb)*)0)->billobjs)==8,"billobjs width");
_Static_assert(sizeof(((__typeof__(go)*)0)->objs_deleted)==8,"objs_deleted width");
_Static_assert(sizeof(((__typeof__(gv)*)0)->viz_array)==8,"vizArray width");
size_t probe_context_size(void){return sizeof(struct obj);}
int probe_layout_count(void){return sizeof worn_layout/sizeof worn_layout[0];}
const char *probe_layout_name(int i){return worn_layout[i].name;}
size_t probe_layout_value(int i){return worn_layout[i].value;}
