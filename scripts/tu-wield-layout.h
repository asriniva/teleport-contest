#ifndef TELEPORT_TU_WIELD_LAYOUT_H
#define TELEPORT_TU_WIELD_LAYOUT_H
#include "hack.h"
#include <stddef.h>
struct wield_meta {const char *name;size_t value;};
#define WIELD_META(k,v) {#k,(size_t)(v)}
static const struct wield_meta wield_layout[]={
WIELD_META(pointerSize,sizeof(void*)),
WIELD_META(longSize,sizeof(long)),
WIELD_META(intSize,sizeof(int)),
WIELD_META(shortSize,sizeof(short)),
WIELD_META(booleanSize,sizeof(boolean)),
WIELD_META(coordSize,sizeof(coordxy)),
WIELD_META(objectSize,sizeof(struct obj)),
WIELD_META(permonstSize,sizeof(struct permonst)),
WIELD_META(objectClassSize,sizeof(struct objclass)),
WIELD_META(attackSize,sizeof(struct attack)),
WIELD_META(propSize,sizeof(struct prop)),
WIELD_META(oextraSize,sizeof(struct oextra)),
WIELD_META(condtestSize,sizeof(condtests[0])),
WIELD_META(obj_otyp,offsetof(struct obj,otyp)),
WIELD_META(obj_otyp_size,sizeof(((struct obj*)0)->otyp)),
WIELD_META(obj_oclass,offsetof(struct obj,oclass)),
WIELD_META(obj_oclass_size,sizeof(((struct obj*)0)->oclass)),
WIELD_META(obj_oartifact,offsetof(struct obj,oartifact)),
WIELD_META(obj_oartifact_size,sizeof(((struct obj*)0)->oartifact)),
WIELD_META(obj_corpsenm,offsetof(struct obj,corpsenm)),
WIELD_META(obj_corpsenm_size,sizeof(((struct obj*)0)->corpsenm)),
WIELD_META(obj_o_id,offsetof(struct obj,o_id)),
WIELD_META(obj_o_id_size,sizeof(((struct obj*)0)->o_id)),
WIELD_META(obj_quan,offsetof(struct obj,quan)),
WIELD_META(obj_quan_size,sizeof(((struct obj*)0)->quan)),
WIELD_META(obj_owt,offsetof(struct obj,owt)),
WIELD_META(obj_owt_size,sizeof(((struct obj*)0)->owt)),
WIELD_META(obj_owornmask,offsetof(struct obj,owornmask)),
WIELD_META(obj_owornmask_size,sizeof(((struct obj*)0)->owornmask)),
WIELD_META(obj_spe,offsetof(struct obj,spe)),
WIELD_META(obj_spe_size,sizeof(((struct obj*)0)->spe)),
WIELD_META(obj_nobj,offsetof(struct obj,nobj)),
WIELD_META(obj_nobj_size,sizeof(((struct obj*)0)->nobj)),
WIELD_META(obj_oextra,offsetof(struct obj,oextra)),
WIELD_META(obj_oextra_size,sizeof(((struct obj*)0)->oextra)),
WIELD_META(oextra_oname,offsetof(struct oextra,oname)),
WIELD_META(oextra_oname_size,sizeof(((struct oextra*)0)->oname)),
WIELD_META(pm_mflags1,offsetof(struct permonst,mflags1)),
WIELD_META(pm_mflags1_size,sizeof(((struct permonst*)0)->mflags1)),
WIELD_META(pm_mflags2,offsetof(struct permonst,mflags2)),
WIELD_META(pm_mflags2_size,sizeof(((struct permonst*)0)->mflags2)),
WIELD_META(pm_msize,offsetof(struct permonst,msize)),
WIELD_META(pm_msize_size,sizeof(((struct permonst*)0)->msize)),
WIELD_META(pm_mlet,offsetof(struct permonst,mlet)),
WIELD_META(pm_mlet_size,sizeof(((struct permonst*)0)->mlet)),
WIELD_META(pm_mattk,offsetof(struct permonst,mattk)),
WIELD_META(NATTK,NATTK),
WIELD_META(attackCount,sizeof(((struct permonst*)0)->mattk)/sizeof(struct attack)),
WIELD_META(atk_aatyp,offsetof(struct attack,aatyp)),
WIELD_META(atk_aatyp_size,sizeof(((struct attack*)0)->aatyp)),
WIELD_META(cls_oc_skill,offsetof(struct objclass,oc_skill)),
WIELD_META(cls_oc_skill_size,sizeof(((struct objclass*)0)->oc_skill)),
WIELD_META(u_twoweap,offsetof(struct you,twoweap)),
WIELD_META(u_twoweap_size,sizeof(((struct you*)0)->twoweap)),
WIELD_META(u_usteed,offsetof(struct you,usteed)),
WIELD_META(u_usteed_size,sizeof(((struct you*)0)->usteed)),
WIELD_META(u_ux,offsetof(struct you,ux)),
WIELD_META(u_ux_size,sizeof(((struct you*)0)->ux)),
WIELD_META(u_uy,offsetof(struct you,uy)),
WIELD_META(u_uy_size,sizeof(((struct you*)0)->uy)),
WIELD_META(u_umonnum,offsetof(struct you,umonnum)),
WIELD_META(u_umonnum_size,sizeof(((struct you*)0)->umonnum)),
WIELD_META(u_umonster,offsetof(struct you,umonster)),
WIELD_META(u_umonster_size,sizeof(((struct you*)0)->umonster)),
WIELD_META(u_uprops,offsetof(struct you,uprops)),
WIELD_META(prop_intrinsic,offsetof(struct prop,intrinsic)),
WIELD_META(prop_intrinsic_size,sizeof(((struct prop*)0)->intrinsic)),
WIELD_META(prop_extrinsic,offsetof(struct prop,extrinsic)),
WIELD_META(prop_extrinsic_size,sizeof(((struct prop*)0)->extrinsic)),
WIELD_META(prop_blocked,offsetof(struct prop,blocked)),
WIELD_META(prop_blocked_size,sizeof(((struct prop*)0)->blocked)),
WIELD_META(youmonst,offsetof(__typeof__(gy),youmonst)),
WIELD_META(unweapon,offsetof(__typeof__(gu),unweapon)),
WIELD_META(unweapon_size,sizeof(((__typeof__(gu)*)0)->unweapon)),
WIELD_META(roleNameM,offsetof(__typeof__(gu),urole.name.m)),
WIELD_META(roleNameM_size,sizeof(((__typeof__(gu)*)0)->urole.name.m)),
WIELD_META(roleNameF,offsetof(__typeof__(gu),urole.name.f)),
WIELD_META(roleNameF_size,sizeof(((__typeof__(gu)*)0)->urole.name.f)),
WIELD_META(female,offsetof(__typeof__(flags),female)),
WIELD_META(female_size,sizeof(((__typeof__(flags)*)0)->female)),
WIELD_META(verbose,offsetof(__typeof__(flags),verbose)),
WIELD_META(verbose_size,sizeof(((__typeof__(flags)*)0)->verbose)),
WIELD_META(pushweapon,offsetof(__typeof__(flags),pushweapon)),
WIELD_META(pushweapon_size,sizeof(((__typeof__(flags)*)0)->pushweapon)),
WIELD_META(weaponstatus,offsetof(__typeof__(flags),weaponstatus)),
WIELD_META(weaponstatus_size,sizeof(((__typeof__(flags)*)0)->weaponstatus)),
WIELD_META(botl,offsetof(__typeof__(disp),botl)),
WIELD_META(botl_size,sizeof(((__typeof__(disp)*)0)->botl)),
WIELD_META(invent,offsetof(__typeof__(gi),invent)),
WIELD_META(invent_size,sizeof(((__typeof__(gi)*)0)->invent)),
WIELD_META(multi,offsetof(__typeof__(gm),multi)),
WIELD_META(multi_size,sizeof(((__typeof__(gm)*)0)->multi)),
WIELD_META(child_oid,offsetof(__typeof__(svc),context.objsplit.child_oid)),
WIELD_META(child_oid_size,sizeof(((__typeof__(svc)*)0)->context.objsplit.child_oid)),
WIELD_META(parent_oid,offsetof(__typeof__(svc),context.objsplit.parent_oid)),
WIELD_META(parent_oid_size,sizeof(((__typeof__(svc)*)0)->context.objsplit.parent_oid)),
WIELD_META(cond_enabled,offsetof(struct condtests_t,enabled)),
WIELD_META(cond_enabled_size,sizeof(((struct condtests_t*)0)->enabled)),
WIELD_META(AKLYS,AKLYS),
WIELD_META(ART_EYES_OF_THE_OVERWORLD,ART_EYES_OF_THE_OVERWORLD),
WIELD_META(ART_MAGICBANE,ART_MAGICBANE),
WIELD_META(ART_OGRESMASHER,ART_OGRESMASHER),
WIELD_META(ART_SNICKERSNEE,ART_SNICKERSNEE),
WIELD_META(AT_WEAP,AT_WEAP),
WIELD_META(A_DEX,A_DEX),
WIELD_META(BATTLE_AXE,BATTLE_AXE),
WIELD_META(BLINDED,BLINDED),
WIELD_META(BUFSZ,BUFSZ),
WIELD_META(COIN_CLASS,COIN_CLASS),
WIELD_META(CORPSE,CORPSE),
WIELD_META(COST_DECHNT,COST_DECHNT),
WIELD_META(COST_DEGRD,COST_DEGRD),
WIELD_META(CRYSKNIFE,CRYSKNIFE),
WIELD_META(CXN_PFX_THE,CXN_PFX_THE),
WIELD_META(ECMD_CANCEL,ECMD_CANCEL),
WIELD_META(ECMD_FAIL,ECMD_FAIL),
WIELD_META(ECMD_OK,ECMD_OK),
WIELD_META(ECMD_TIME,ECMD_TIME),
WIELD_META(ELVEN_ARROW,ELVEN_ARROW),
WIELD_META(ELVEN_BOW,ELVEN_BOW),
WIELD_META(ELVEN_BROADSWORD,ELVEN_BROADSWORD),
WIELD_META(ELVEN_DAGGER,ELVEN_DAGGER),
WIELD_META(ELVEN_SHORT_SWORD,ELVEN_SHORT_SWORD),
WIELD_META(ELVEN_SPEAR,ELVEN_SPEAR),
WIELD_META(GEM_CLASS,GEM_CLASS),
WIELD_META(GETOBJ_ALLOWCNT,GETOBJ_ALLOWCNT),
WIELD_META(GETOBJ_DOWNPLAY,GETOBJ_DOWNPLAY),
WIELD_META(GETOBJ_EXCLUDE,GETOBJ_EXCLUDE),
WIELD_META(GETOBJ_PROMPT,GETOBJ_PROMPT),
WIELD_META(GETOBJ_SUGGEST,GETOBJ_SUGGEST),
WIELD_META(GLIB,GLIB),
WIELD_META(HALLUC,HALLUC),
WIELD_META(HALLUC_RES,HALLUC_RES),
WIELD_META(HAND,HAND),
WIELD_META(HEAVY_IRON_BALL,HEAVY_IRON_BALL),
WIELD_META(IRON,IRON),
WIELD_META(IRON_CHAIN,IRON_CHAIN),
WIELD_META(M1_HUMANOID,M1_HUMANOID),
WIELD_META(M1_NOHANDS,M1_NOHANDS),
WIELD_META(MZ_SMALL,MZ_SMALL),
WIELD_META(NUMMONS,NUMMONS),
WIELD_META(NUM_OBJECTS,NUM_OBJECTS),
WIELD_META(PM_CHICKATRICE,PM_CHICKATRICE),
WIELD_META(PM_COCKATRICE,PM_COCKATRICE),
WIELD_META(PM_ELF,PM_ELF),
WIELD_META(P_BOOMERANG,P_BOOMERANG),
WIELD_META(P_BOW,P_BOW),
WIELD_META(P_CROSSBOW,P_CROSSBOW),
WIELD_META(P_DART,P_DART),
WIELD_META(P_LANCE,P_LANCE),
WIELD_META(P_NONE,P_NONE),
WIELD_META(P_POLEARMS,P_POLEARMS),
WIELD_META(P_SABER,P_SABER),
WIELD_META(P_SHORT_SWORD,P_SHORT_SWORD),
WIELD_META(P_SLING,P_SLING),
WIELD_META(QBUFSZ,QBUFSZ),
WIELD_META(RIGHT_HANDED,RIGHT_HANDED),
WIELD_META(SCROLL_CLASS,SCROLL_CLASS),
WIELD_META(STONE_RES,STONE_RES),
WIELD_META(STRANGE_OBJECT,STRANGE_OBJECT),
WIELD_META(TIN_OPENER,TIN_OPENER),
WIELD_META(TOOL_CLASS,TOOL_CLASS),
WIELD_META(TOWEL,TOWEL),
WIELD_META(WEAPON_CLASS,WEAPON_CLASS),
WIELD_META(WORM_TOOTH,WORM_TOOTH),
WIELD_META(W_ACCESSORY,W_ACCESSORY),
WIELD_META(W_ARMOR,W_ARMOR),
WIELD_META(W_QUIVER,W_QUIVER),
WIELD_META(W_SADDLE,W_SADDLE),
WIELD_META(W_SWAPWEP,W_SWAPWEP),
WIELD_META(W_WEP,W_WEP),
WIELD_META(bl_bareh,bl_bareh),
WIELD_META(invlet_basic,invlet_basic),
WIELD_META(PM_HUMAN,PM_HUMAN),
WIELD_META(PM_MONK,PM_MONK),
WIELD_META(PM_WIZARD,PM_WIZARD),
WIELD_META(PM_FOG_CLOUD,PM_FOG_CLOUD),
WIELD_META(PM_DOG,PM_DOG),
WIELD_META(PM_MARILITH,PM_MARILITH),
WIELD_META(HELMET,HELMET),
WIELD_META(LEATHER_GLOVES,LEATHER_GLOVES),
WIELD_META(SMALL_SHIELD,SMALL_SHIELD),
WIELD_META(DAGGER,DAGGER),
WIELD_META(LONG_SWORD,LONG_SWORD),
WIELD_META(TWO_HANDED_SWORD,TWO_HANDED_SWORD),
WIELD_META(BOW,BOW),
WIELD_META(ARROW,ARROW),
WIELD_META(DART,DART),
WIELD_META(GOLD_PIECE,GOLD_PIECE),
WIELD_META(PICK_AXE,PICK_AXE),
WIELD_META(LANCE,LANCE),
WIELD_META(MAGIC_MARKER,MAGIC_MARKER),
WIELD_META(SCR_ENCHANT_WEAPON,SCR_ENCHANT_WEAPON),
WIELD_META(ART_SUNSWORD,ART_SUNSWORD),
WIELD_META(OBJ_INVENT,OBJ_INVENT),
WIELD_META(OBJ_FREE,OBJ_FREE),
WIELD_META(OBJ_FLOOR,OBJ_FLOOR),
WIELD_META(W_ARMG,W_ARMG),
WIELD_META(W_ARMS,W_ARMS),
WIELD_META(TELEPAT,TELEPAT),
WIELD_META(mon_data,offsetof(struct monst,data)),
WIELD_META(mon_data_size,sizeof(((struct monst*)0)->data)),
WIELD_META(cls_oc_armcat,offsetof(struct objclass,oc_armcat)),
WIELD_META(cls_oc_armcat_size,sizeof(((struct objclass*)0)->oc_armcat)),
WIELD_META(ARM_GLOVES,ARM_GLOVES),
WIELD_META(ARM_BOOTS,ARM_BOOTS),
WIELD_META(LENSES,LENSES),
WIELD_META(ARMOR_CLASS,ARMOR_CLASS),
};
#undef WIELD_META
_Static_assert(sizeof(((struct obj*)0)->otyp)==2,"obj_otyp width");
_Static_assert(((__typeof__(((struct obj*)0)->otyp))-1 < 0),"obj_otyp signedness");
_Static_assert(sizeof(((struct obj*)0)->oclass)==1,"obj_oclass width");
_Static_assert(((__typeof__(((struct obj*)0)->oclass))-1 < 0),"obj_oclass signedness");
_Static_assert(sizeof(((struct obj*)0)->oartifact)==1,"obj_oartifact width");
_Static_assert(((__typeof__(((struct obj*)0)->oartifact))-1 < 0),"obj_oartifact signedness");
_Static_assert(sizeof(((struct obj*)0)->corpsenm)==4,"obj_corpsenm width");
_Static_assert(((__typeof__(((struct obj*)0)->corpsenm))-1 < 0),"obj_corpsenm signedness");
_Static_assert(sizeof(((struct obj*)0)->o_id)==4,"obj_o_id width");
_Static_assert(((__typeof__(((struct obj*)0)->o_id))-1 > 0),"obj_o_id signedness");
_Static_assert(sizeof(((struct obj*)0)->quan)==8,"obj_quan width");
_Static_assert(((__typeof__(((struct obj*)0)->quan))-1 < 0),"obj_quan signedness");
_Static_assert(sizeof(((struct obj*)0)->owt)==4,"obj_owt width");
_Static_assert(((__typeof__(((struct obj*)0)->owt))-1 > 0),"obj_owt signedness");
_Static_assert(sizeof(((struct obj*)0)->owornmask)==8,"obj_owornmask width");
_Static_assert(((__typeof__(((struct obj*)0)->owornmask))-1 < 0),"obj_owornmask signedness");
_Static_assert(sizeof(((struct obj*)0)->spe)==1,"obj_spe width");
_Static_assert(((__typeof__(((struct obj*)0)->spe))-1 < 0),"obj_spe signedness");
_Static_assert(sizeof(((struct obj*)0)->nobj)==8,"obj_nobj width");
_Static_assert(sizeof(((struct obj*)0)->oextra)==8,"obj_oextra width");
_Static_assert(sizeof(((struct oextra*)0)->oname)==8,"oextra_oname width");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8,"pm_mflags1 width");
_Static_assert(((__typeof__(((struct permonst*)0)->mflags1))-1 > 0),"pm_mflags1 signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8,"pm_mflags2 width");
_Static_assert(((__typeof__(((struct permonst*)0)->mflags2))-1 > 0),"pm_mflags2 signedness");
_Static_assert(sizeof(((struct permonst*)0)->msize)==1,"pm_msize width");
_Static_assert(((__typeof__(((struct permonst*)0)->msize))-1 > 0),"pm_msize signedness");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1,"pm_mlet width");
_Static_assert(((__typeof__(((struct permonst*)0)->mlet))-1 < 0),"pm_mlet signedness");
_Static_assert(sizeof(((struct attack*)0)->aatyp)==1,"atk_aatyp width");
_Static_assert(((__typeof__(((struct attack*)0)->aatyp))-1 > 0),"atk_aatyp signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_skill)==1,"cls_oc_skill width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_skill))-1 < 0),"cls_oc_skill signedness");
_Static_assert(sizeof(((struct you*)0)->twoweap)==1,"u_twoweap width");
_Static_assert(((__typeof__(((struct you*)0)->twoweap))-1 < 0),"u_twoweap signedness");
_Static_assert(sizeof(((struct you*)0)->usteed)==8,"u_usteed width");
_Static_assert(sizeof(((struct you*)0)->ux)==2,"u_ux width");
_Static_assert(((__typeof__(((struct you*)0)->ux))-1 < 0),"u_ux signedness");
_Static_assert(sizeof(((struct you*)0)->uy)==2,"u_uy width");
_Static_assert(((__typeof__(((struct you*)0)->uy))-1 < 0),"u_uy signedness");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4,"u_umonnum width");
_Static_assert(((__typeof__(((struct you*)0)->umonnum))-1 < 0),"u_umonnum signedness");
_Static_assert(sizeof(((struct you*)0)->umonster)==4,"u_umonster width");
_Static_assert(((__typeof__(((struct you*)0)->umonster))-1 < 0),"u_umonster signedness");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8,"prop_intrinsic width");
_Static_assert(((__typeof__(((struct prop*)0)->intrinsic))-1 < 0),"prop_intrinsic signedness");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8,"prop_extrinsic width");
_Static_assert(((__typeof__(((struct prop*)0)->extrinsic))-1 < 0),"prop_extrinsic signedness");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8,"prop_blocked width");
_Static_assert(((__typeof__(((struct prop*)0)->blocked))-1 < 0),"prop_blocked signedness");
_Static_assert(sizeof(((__typeof__(gu)*)0)->unweapon)==1,"unweapon width");
_Static_assert(((__typeof__(((__typeof__(gu)*)0)->unweapon))-1 < 0),"unweapon signedness");
_Static_assert(sizeof(((__typeof__(gu)*)0)->urole.name.m)==8,"roleNameM width");
_Static_assert(sizeof(((__typeof__(gu)*)0)->urole.name.f)==8,"roleNameF width");
_Static_assert(sizeof(((__typeof__(flags)*)0)->female)==1,"female width");
_Static_assert(((__typeof__(((__typeof__(flags)*)0)->female))-1 < 0),"female signedness");
_Static_assert(sizeof(((__typeof__(flags)*)0)->verbose)==1,"verbose width");
_Static_assert(((__typeof__(((__typeof__(flags)*)0)->verbose))-1 < 0),"verbose signedness");
_Static_assert(sizeof(((__typeof__(flags)*)0)->pushweapon)==1,"pushweapon width");
_Static_assert(((__typeof__(((__typeof__(flags)*)0)->pushweapon))-1 < 0),"pushweapon signedness");
_Static_assert(sizeof(((__typeof__(flags)*)0)->weaponstatus)==1,"weaponstatus width");
_Static_assert(((__typeof__(((__typeof__(flags)*)0)->weaponstatus))-1 < 0),"weaponstatus signedness");
_Static_assert(sizeof(((__typeof__(disp)*)0)->botl)==1,"botl width");
_Static_assert(((__typeof__(((__typeof__(disp)*)0)->botl))-1 < 0),"botl signedness");
_Static_assert(sizeof(((__typeof__(gi)*)0)->invent)==8,"invent width");
_Static_assert(sizeof(((__typeof__(gm)*)0)->multi)==8,"multi width");
_Static_assert(((__typeof__(((__typeof__(gm)*)0)->multi))-1 < 0),"multi signedness");
_Static_assert(sizeof(((__typeof__(svc)*)0)->context.objsplit.child_oid)==4,"child_oid width");
_Static_assert(((__typeof__(((__typeof__(svc)*)0)->context.objsplit.child_oid))-1 > 0),"child_oid signedness");
_Static_assert(sizeof(((__typeof__(svc)*)0)->context.objsplit.parent_oid)==4,"parent_oid width");
_Static_assert(((__typeof__(((__typeof__(svc)*)0)->context.objsplit.parent_oid))-1 > 0),"parent_oid signedness");
_Static_assert(sizeof(((struct condtests_t*)0)->enabled)==1,"cond_enabled width");
_Static_assert(((__typeof__(((struct condtests_t*)0)->enabled))-1 < 0),"cond_enabled signedness");
_Static_assert(sizeof(((struct monst*)0)->data)==8,"mon_data width");
_Static_assert(sizeof(((struct objclass*)0)->oc_armcat)==1,"cls_oc_armcat width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_armcat))-1 < 0),"cls_oc_armcat signedness");
size_t probe_context_size(void){return sizeof(struct obj);}
int probe_layout_count(void){return sizeof wield_layout/sizeof wield_layout[0];}
const char *probe_layout_name(int i){return wield_layout[i].name;}
size_t probe_layout_value(int i){return wield_layout[i].value;}
#endif
