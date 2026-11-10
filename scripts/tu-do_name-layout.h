#ifndef TELEPORT_DO_NAME_LAYOUT_H
#define TELEPORT_DO_NAME_LAYOUT_H
#include "hack.h"
#include "artifact.h"
#include <stddef.h>
#ifdef EDIT_GETLIN
#error DO_NAME EDIT_GETLIN branch requires a separate reviewed port
#endif
#ifdef PMNAME_MACROS
#error DO_NAME PMNAME_MACROS changes original configured function inventory
#endif
struct do_name_meta {const char *name;size_t value;};
#define DN_META(k,v) {#k,(size_t)(v)}
static const struct do_name_meta do_name_layout[]={
DN_META(pointerSize,sizeof(void*)),
DN_META(longSize,sizeof(long)),
DN_META(booleanSize,sizeof(boolean)),
DN_META(OfSize,sizeof " of "),
DN_META(EmptySize,sizeof ""),
DN_META(monsterSize,sizeof(struct monst)),
DN_META(objectSize,sizeof(struct obj)),
DN_META(permonstSize,sizeof(struct permonst)),
DN_META(objectClassSize,sizeof(struct objclass)),
DN_META(objdescrSize,sizeof(struct objdescr)),
DN_META(mextraSize,sizeof(struct mextra)),
DN_META(oextraSize,sizeof(struct oextra)),
DN_META(propSize,sizeof(struct prop)),
DN_META(coordSize,sizeof(coord)),
DN_META(genderSize,sizeof(struct Gender)),
DN_META(commandSize,sizeof(struct _cmd_queue)),
DN_META(menuItemSize,sizeof(menu_item)),
DN_META(anythingSize,sizeof(anything)),
DN_META(mon_data,offsetof(struct monst,data)),
DN_META(mon_data_size,sizeof(((struct monst*)0)->data)),
DN_META(mon_mextra,offsetof(struct monst,mextra)),
DN_META(mon_mextra_size,sizeof(((struct monst*)0)->mextra)),
DN_META(mon_m_id,offsetof(struct monst,m_id)),
DN_META(mon_m_id_size,sizeof(((struct monst*)0)->m_id)),
DN_META(mon_m_lev,offsetof(struct monst,m_lev)),
DN_META(mon_m_lev_size,sizeof(((struct monst*)0)->m_lev)),
DN_META(mon_mappearance,offsetof(struct monst,mappearance)),
DN_META(mon_mappearance_size,sizeof(((struct monst*)0)->mappearance)),
DN_META(mon_misc_worn_check,offsetof(struct monst,misc_worn_check)),
DN_META(mon_misc_worn_check_size,sizeof(((struct monst*)0)->misc_worn_check)),
DN_META(mon_mtame,offsetof(struct monst,mtame)),
DN_META(mon_mtame_size,sizeof(((struct monst*)0)->mtame)),
DN_META(mon_cham,offsetof(struct monst,cham)),
DN_META(mon_cham_size,sizeof(((struct monst*)0)->cham)),
DN_META(mon_mx,offsetof(struct monst,mx)),
DN_META(mon_mx_size,sizeof(((struct monst*)0)->mx)),
DN_META(mon_my,offsetof(struct monst,my)),
DN_META(mon_my_size,sizeof(((struct monst*)0)->my)),
DN_META(mon_mhp,offsetof(struct monst,mhp)),
DN_META(mon_mhp_size,sizeof(((struct monst*)0)->mhp)),
DN_META(mon_m_ap_type,offsetof(struct monst,m_ap_type)),
DN_META(mon_m_ap_type_size,sizeof(((struct monst*)0)->m_ap_type)),
DN_META(obj_nobj,offsetof(struct obj,nobj)),
DN_META(obj_nobj_size,sizeof(((struct obj*)0)->nobj)),
DN_META(obj_otyp,offsetof(struct obj,otyp)),
DN_META(obj_otyp_size,sizeof(((struct obj*)0)->otyp)),
DN_META(obj_oclass,offsetof(struct obj,oclass)),
DN_META(obj_oclass_size,sizeof(((struct obj*)0)->oclass)),
DN_META(obj_oartifact,offsetof(struct obj,oartifact)),
DN_META(obj_oartifact_size,sizeof(((struct obj*)0)->oartifact)),
DN_META(obj_corpsenm,offsetof(struct obj,corpsenm)),
DN_META(obj_corpsenm_size,sizeof(((struct obj*)0)->corpsenm)),
DN_META(obj_quan,offsetof(struct obj,quan)),
DN_META(obj_quan_size,sizeof(((struct obj*)0)->quan)),
DN_META(obj_spe,offsetof(struct obj,spe)),
DN_META(obj_spe_size,sizeof(((struct obj*)0)->spe)),
DN_META(obj_where,offsetof(struct obj,where)),
DN_META(obj_where_size,sizeof(((struct obj*)0)->where)),
DN_META(obj_oextra,offsetof(struct obj,oextra)),
DN_META(obj_oextra_size,sizeof(((struct obj*)0)->oextra)),
DN_META(obj_owt,offsetof(struct obj,owt)),
DN_META(obj_owt_size,sizeof(((struct obj*)0)->owt)),
DN_META(pm_pmnames,offsetof(struct permonst,pmnames)),
DN_META(pm_pmnames_size,sizeof(((struct permonst*)0)->pmnames)),
DN_META(pm_mflags1,offsetof(struct permonst,mflags1)),
DN_META(pm_mflags1_size,sizeof(((struct permonst*)0)->mflags1)),
DN_META(pm_mflags2,offsetof(struct permonst,mflags2)),
DN_META(pm_mflags2_size,sizeof(((struct permonst*)0)->mflags2)),
DN_META(pm_geno,offsetof(struct permonst,geno)),
DN_META(pm_geno_size,sizeof(((struct permonst*)0)->geno)),
DN_META(pm_msound,offsetof(struct permonst,msound)),
DN_META(pm_msound_size,sizeof(((struct permonst*)0)->msound)),
DN_META(pm_mlet,offsetof(struct permonst,mlet)),
DN_META(pm_mlet_size,sizeof(((struct permonst*)0)->mlet)),
DN_META(pm_pmidx,offsetof(struct permonst,pmidx)),
DN_META(pm_pmidx_size,sizeof(((struct permonst*)0)->pmidx)),
DN_META(cls_oc_uname,offsetof(struct objclass,oc_uname)),
DN_META(cls_oc_uname_size,sizeof(((struct objclass*)0)->oc_uname)),
DN_META(cls_oc_class,offsetof(struct objclass,oc_class)),
DN_META(cls_oc_class_size,sizeof(((struct objclass*)0)->oc_class)),
DN_META(cls_oc_descr_idx,offsetof(struct objclass,oc_descr_idx)),
DN_META(cls_oc_descr_idx_size,sizeof(((struct objclass*)0)->oc_descr_idx)),
DN_META(cls_oc_weight,offsetof(struct objclass,oc_weight)),
DN_META(cls_oc_weight_size,sizeof(((struct objclass*)0)->oc_weight)),
DN_META(mextra_mgivenname,offsetof(struct mextra,mgivenname)),
DN_META(mextra_mgivenname_size,sizeof(((struct mextra*)0)->mgivenname)),
DN_META(mextra_ebones,offsetof(struct mextra,ebones)),
DN_META(mextra_ebones_size,sizeof(((struct mextra*)0)->ebones)),
DN_META(oextra_oname,offsetof(struct oextra,oname)),
DN_META(oextra_oname_size,sizeof(((struct oextra*)0)->oname)),
DN_META(descr_oc_name,offsetof(struct objdescr,oc_name)),
DN_META(descr_oc_name_size,sizeof(((struct objdescr*)0)->oc_name)),
DN_META(descr_oc_descr,offsetof(struct objdescr,oc_descr)),
DN_META(descr_oc_descr_size,sizeof(((struct objdescr*)0)->oc_descr)),
DN_META(u_ux,offsetof(struct you,ux)),
DN_META(u_ux_size,sizeof(((struct you*)0)->ux)),
DN_META(u_uy,offsetof(struct you,uy)),
DN_META(u_uy_size,sizeof(((struct you*)0)->uy)),
DN_META(u_ustuck,offsetof(struct you,ustuck)),
DN_META(u_ustuck_size,sizeof(((struct you*)0)->ustuck)),
DN_META(u_usteed,offsetof(struct you,usteed)),
DN_META(u_usteed_size,sizeof(((struct you*)0)->usteed)),
DN_META(u_umonnum,offsetof(struct you,umonnum)),
DN_META(u_umonnum_size,sizeof(((struct you*)0)->umonnum)),
DN_META(u_umonster,offsetof(struct you,umonster)),
DN_META(u_umonster_size,sizeof(((struct you*)0)->umonster)),
DN_META(u_uz,offsetof(struct you,uz)),
DN_META(u_uz_size,sizeof(((struct you*)0)->uz)),
DN_META(u_uprops,offsetof(struct you,uprops)),
DN_META(u_uprops_size,sizeof(((struct you*)0)->uprops)),
DN_META(prop_intrinsic,offsetof(struct prop,intrinsic)),
DN_META(prop_intrinsic_size,sizeof(((struct prop*)0)->intrinsic)),
DN_META(prop_extrinsic,offsetof(struct prop,extrinsic)),
DN_META(prop_extrinsic_size,sizeof(((struct prop*)0)->extrinsic)),
DN_META(prop_blocked,offsetof(struct prop,blocked)),
DN_META(prop_blocked_size,sizeof(((struct prop*)0)->blocked)),
DN_META(coord_x,offsetof(coord,x)),
DN_META(coord_x_size,sizeof(((coord*)0)->x)),
DN_META(coord_y,offsetof(coord,y)),
DN_META(coord_y_size,sizeof(((coord*)0)->y)),
DN_META(gender_he,offsetof(struct Gender,he)),
DN_META(gender_he_size,sizeof(((struct Gender*)0)->he)),
DN_META(gender_him,offsetof(struct Gender,him)),
DN_META(gender_him_size,sizeof(((struct Gender*)0)->him)),
DN_META(gender_his,offsetof(struct Gender,his)),
DN_META(gender_his_size,sizeof(((struct Gender*)0)->his)),
DN_META(command_typ,offsetof(struct _cmd_queue,typ)),
DN_META(command_typ_size,sizeof(((struct _cmd_queue*)0)->typ)),
DN_META(command_key,offsetof(struct _cmd_queue,key)),
DN_META(command_key_size,sizeof(((struct _cmd_queue*)0)->key)),
DN_META(menu_item,offsetof(menu_item,item)),
DN_META(menu_item_size,sizeof(((menu_item*)0)->item)),
DN_META(dlevel_dnum,offsetof(d_level,dnum)),
DN_META(dlevel_dnum_size,sizeof(((d_level*)0)->dnum)),
DN_META(dlevel_dlevel,offsetof(d_level,dlevel)),
DN_META(dlevel_dlevel_size,sizeof(((d_level*)0)->dlevel)),
DN_META(youmonst,offsetof(__typeof__(gy),youmonst)),
DN_META(youmonst_size,sizeof(gy.youmonst)),
DN_META(plname,offsetof(__typeof__(svp),plname)),
DN_META(plname_size,sizeof(svp.plname)),
DN_META(invent,offsetof(__typeof__(gi),invent)),
DN_META(invent_size,sizeof(gi.invent)),
DN_META(literate,offsetof(__typeof__(u),uconduct.literate)),
DN_META(literate_size,sizeof(u.uconduct.literate)),
DN_META(roleNameM,offsetof(__typeof__(gu),urole.name.m)),
DN_META(roleNameM_size,sizeof(gu.urole.name.m)),
DN_META(roleNameF,offsetof(__typeof__(gu),urole.name.f)),
DN_META(roleNameF_size,sizeof(gu.urole.name.f)),
DN_META(roleMnum,offsetof(__typeof__(gu),urole.mnum)),
DN_META(roleMnum_size,sizeof(gu.urole.mnum)),
DN_META(gameover,offsetof(__typeof__(program_state),gameover)),
DN_META(gameover_size,sizeof(program_state.gameover)),
DN_META(female,offsetof(__typeof__(flags),female)),
DN_META(female_size,sizeof(flags.female)),
DN_META(lootabc,offsetof(__typeof__(flags),lootabc)),
DN_META(lootabc_size,sizeof(flags.lootabc)),
DN_META(monsters,offsetof(__typeof__(svl),level.monsters)),
DN_META(monsters_size,sizeof(svl.level.monsters)),
DN_META(vizArray,offsetof(__typeof__(gv),viz_array)),
DN_META(vizArray_size,sizeof(gv.viz_array)),
DN_META(astral_level,offsetof(__typeof__(svd),dungeon_topology.d_astral_level)),
DN_META(astral_level_size,sizeof(svd.dungeon_topology.d_astral_level)),
DN_META(zeroany,offsetof(__typeof__(cg),zeroany)),
DN_META(zeroany_size,sizeof(cg.zeroany)),
DN_META(floorObjects,offsetof(__typeof__(svl),level.objects)),
DN_META(floorObjects_size,sizeof(svl.level.objects)),
DN_META(AMULET_CLASS,AMULET_CLASS),
DN_META(AMULET_OF_YENDOR,AMULET_OF_YENDOR),
DN_META(ARMOR_CLASS,ARMOR_CLASS),
DN_META(ARTICLE_A,ARTICLE_A),
DN_META(ARTICLE_NONE,ARTICLE_NONE),
DN_META(ARTICLE_THE,ARTICLE_THE),
DN_META(ARTICLE_YOUR,ARTICLE_YOUR),
DN_META(ART_EYES_OF_THE_OVERWORLD,ART_EYES_OF_THE_OVERWORLD),
DN_META(ART_STING,ART_STING),
DN_META(ATR_NONE,ATR_NONE),
DN_META(AUGMENT_IT,AUGMENT_IT),
DN_META(BLINDED,BLINDED),
DN_META(BLINDFOLD,BLINDFOLD),
DN_META(BUFSZ,BUFSZ),
DN_META(CLR_MAX,CLR_MAX),
DN_META(CMDQ_KEY,CMDQ_KEY),
DN_META(COIN_CLASS,COIN_CLASS),
DN_META(COLNO,COLNO),
DN_META(CORPSE,CORPSE),
DN_META(CORPSTAT_FEMALE,CORPSTAT_FEMALE),
DN_META(CORPSTAT_GENDER,CORPSTAT_GENDER),
DN_META(CORPSTAT_MALE,CORPSTAT_MALE),
DN_META(CORPSTAT_RANDOM,CORPSTAT_RANDOM),
DN_META(CQ_CANNED,CQ_CANNED),
DN_META(DAGGER,DAGGER),
DN_META(DEAF,DEAF),
DN_META(ECMD_OK,ECMD_OK),
DN_META(EXACT_NAME,EXACT_NAME),
DN_META(FAKE_AMULET_OF_YENDOR,FAKE_AMULET_OF_YENDOR),
DN_META(FEMALE,FEMALE),
DN_META(FIGURINE,FIGURINE),
DN_META(FIRST_OBJECT,FIRST_OBJECT),
DN_META(FOOD_CLASS,FOOD_CLASS),
DN_META(GEM_CLASS,GEM_CLASS),
DN_META(GETOBJ_DOWNPLAY,GETOBJ_DOWNPLAY),
DN_META(GETOBJ_EXCLUDE,GETOBJ_EXCLUDE),
DN_META(GETOBJ_NOFLAGS,GETOBJ_NOFLAGS),
DN_META(GETOBJ_PROMPT,GETOBJ_PROMPT),
DN_META(GETOBJ_SUGGEST,GETOBJ_SUGGEST),
DN_META(GLYPH_BODY_OFF,GLYPH_BODY_OFF),
DN_META(GLYPH_BODY_PILETOP_OFF,GLYPH_BODY_PILETOP_OFF),
DN_META(GLYPH_OBJ_OFF,GLYPH_OBJ_OFF),
DN_META(GLYPH_OBJ_PILETOP_OFF,GLYPH_OBJ_PILETOP_OFF),
DN_META(GLYPH_STATUE_FEM_OFF,GLYPH_STATUE_FEM_OFF),
DN_META(GLYPH_STATUE_FEM_PILETOP_OFF,GLYPH_STATUE_FEM_PILETOP_OFF),
DN_META(GLYPH_STATUE_MALE_OFF,GLYPH_STATUE_MALE_OFF),
DN_META(GLYPH_STATUE_MALE_PILETOP_OFF,GLYPH_STATUE_MALE_PILETOP_OFF),
DN_META(GLYPH_SWALLOW_OFF,GLYPH_SWALLOW_OFF),
DN_META(G_NOGEN,G_NOGEN),
DN_META(G_UNIQ,G_UNIQ),
DN_META(HALLUC,HALLUC),
DN_META(HALLUC_RES,HALLUC_RES),
DN_META(HAND,HAND),
DN_META(HEAVY_IRON_BALL,HEAVY_IRON_BALL),
DN_META(IN_SIGHT,IN_SIGHT),
DN_META(LL_ARTIFACT,LL_ARTIFACT),
DN_META(LL_CONDUCT,LL_CONDUCT),
DN_META(LOW_PM,LOW_PM),
DN_META(M1_ANIMAL,M1_ANIMAL),
DN_META(M1_CONCEAL,M1_CONCEAL),
DN_META(M1_HUMANOID,M1_HUMANOID),
DN_META(M1_MINDLESS,M1_MINDLESS),
DN_META(M2_PNAME,M2_PNAME),
DN_META(MALE,MALE),
DN_META(MD_PAD_BOGONS,MD_PAD_BOGONS),
DN_META(MENU_BEHAVE_STANDARD,MENU_BEHAVE_STANDARD),
DN_META(MENU_ITEMFLAGS_NONE,MENU_ITEMFLAGS_NONE),
DN_META(MS_ANIMAL,MS_ANIMAL),
DN_META(M_AP_FURNITURE,M_AP_FURNITURE),
DN_META(M_AP_MONSTER,M_AP_MONSTER),
DN_META(M_AP_OBJECT,M_AP_OBJECT),
DN_META(M_AP_TYPMASK,M_AP_TYPMASK),
DN_META(NEUTRAL,NEUTRAL),
DN_META(NHW_MENU,NHW_MENU),
DN_META(NON_PM,NON_PM),
DN_META(NO_COLOR,NO_COLOR),
DN_META(NUMMONS,NUMMONS),
DN_META(NUM_MGENDERS,NUM_MGENDERS),
DN_META(NUM_OBJECTS,NUM_OBJECTS),
DN_META(OBJ_FREE,OBJ_FREE),
DN_META(OBJ_INVENT,OBJ_INVENT),
DN_META(ONAME_KNOW_ARTI,ONAME_KNOW_ARTI),
DN_META(ONAME_SKIP_INVUPD,ONAME_SKIP_INVUPD),
DN_META(ONAME_VIA_NAMING,ONAME_VIA_NAMING),
DN_META(PICK_ONE,PICK_ONE),
DN_META(PL_PSIZ,PL_PSIZ),
DN_META(PM_ALIGNED_CLERIC,PM_ALIGNED_CLERIC),
DN_META(PM_ARCHEOLOGIST,PM_ARCHEOLOGIST),
DN_META(PM_CLERIC,PM_CLERIC),
DN_META(PM_DEATH,PM_DEATH),
DN_META(PM_FAMINE,PM_FAMINE),
DN_META(PM_GHOST,PM_GHOST),
DN_META(PM_HIGH_CLERIC,PM_HIGH_CLERIC),
DN_META(PM_HUMAN,PM_HUMAN),
DN_META(PM_JUIBLEX,PM_JUIBLEX),
DN_META(PM_LONG_WORM,PM_LONG_WORM),
DN_META(PM_LONG_WORM_TAIL,PM_LONG_WORM_TAIL),
DN_META(PM_PESTILENCE,PM_PESTILENCE),
DN_META(PM_SHOPKEEPER,PM_SHOPKEEPER),
DN_META(PM_WIZARD,PM_WIZARD),
DN_META(PM_WIZARD_OF_YENDOR,PM_WIZARD_OF_YENDOR),
DN_META(POTION_CLASS,POTION_CLASS),
DN_META(POT_WATER,POT_WATER),
DN_META(PRONOUN_HALLU,PRONOUN_HALLU),
DN_META(QBUFSZ,QBUFSZ),
DN_META(RING_CLASS,RING_CLASS),
DN_META(ROWNO,ROWNO),
DN_META(SCROLL_CLASS,SCROLL_CLASS),
DN_META(SEE_INVIS,SEE_INVIS),
DN_META(SPBOOK_CLASS,SPBOOK_CLASS),
DN_META(SPECIAL_PM,SPECIAL_PM),
DN_META(SPE_NOVEL,SPE_NOVEL),
DN_META(STATUE,STATUE),
DN_META(STRANGE_OBJECT,STRANGE_OBJECT),
DN_META(SUPPRESS_HALLUCINATION,SUPPRESS_HALLUCINATION),
DN_META(SUPPRESS_INVISIBLE,SUPPRESS_INVISIBLE),
DN_META(SUPPRESS_IT,SUPPRESS_IT),
DN_META(SUPPRESS_MAPPEARANCE,SUPPRESS_MAPPEARANCE),
DN_META(SUPPRESS_NAME,SUPPRESS_NAME),
DN_META(SUPPRESS_SADDLE,SUPPRESS_SADDLE),
DN_META(TIN,TIN),
DN_META(TOOL_CLASS,TOOL_CLASS),
DN_META(TOWEL,TOWEL),
DN_META(VENOM_CLASS,VENOM_CLASS),
DN_META(WAND_CLASS,WAND_CLASS),
DN_META(WEAPON_CLASS,WEAPON_CLASS),
DN_META(W_SADDLE,W_SADDLE),
DN_META(W_WEP,W_WEP),
};
#undef DN_META
_Static_assert(sizeof(((struct monst*)0)->data)==8,"DO_NAME mon_data width");
_Static_assert(sizeof(((struct monst*)0)->mextra)==8,"DO_NAME mon_mextra width");
_Static_assert(sizeof(((struct monst*)0)->m_id)==4,"DO_NAME mon_m_id width");
_Static_assert((((__typeof__(((struct monst*)0)->m_id))-1)<0)==0,"DO_NAME mon_m_id sign");
_Static_assert(sizeof(((struct monst*)0)->m_lev)==1,"DO_NAME mon_m_lev width");
_Static_assert((((__typeof__(((struct monst*)0)->m_lev))-1)<0)==0,"DO_NAME mon_m_lev sign");
_Static_assert(sizeof(((struct monst*)0)->mappearance)==4,"DO_NAME mon_mappearance width");
_Static_assert((((__typeof__(((struct monst*)0)->mappearance))-1)<0)==0,"DO_NAME mon_mappearance sign");
_Static_assert(sizeof(((struct monst*)0)->misc_worn_check)==8,"DO_NAME mon_misc_worn_check width");
_Static_assert((((__typeof__(((struct monst*)0)->misc_worn_check))-1)<0)==1,"DO_NAME mon_misc_worn_check sign");
_Static_assert(sizeof(((struct monst*)0)->mtame)==1,"DO_NAME mon_mtame width");
_Static_assert((((__typeof__(((struct monst*)0)->mtame))-1)<0)==1,"DO_NAME mon_mtame sign");
_Static_assert(sizeof(((struct monst*)0)->cham)==2,"DO_NAME mon_cham width");
_Static_assert((((__typeof__(((struct monst*)0)->cham))-1)<0)==1,"DO_NAME mon_cham sign");
_Static_assert(sizeof(((struct monst*)0)->mx)==2,"DO_NAME mon_mx width");
_Static_assert((((__typeof__(((struct monst*)0)->mx))-1)<0)==1,"DO_NAME mon_mx sign");
_Static_assert(sizeof(((struct monst*)0)->my)==2,"DO_NAME mon_my width");
_Static_assert((((__typeof__(((struct monst*)0)->my))-1)<0)==1,"DO_NAME mon_my sign");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4,"DO_NAME mon_mhp width");
_Static_assert((((__typeof__(((struct monst*)0)->mhp))-1)<0)==1,"DO_NAME mon_mhp sign");
_Static_assert(sizeof(((struct monst*)0)->m_ap_type)==1,"DO_NAME mon_m_ap_type width");
_Static_assert((((__typeof__(((struct monst*)0)->m_ap_type))-1)<0)==0,"DO_NAME mon_m_ap_type sign");
_Static_assert(sizeof(((struct obj*)0)->nobj)==8,"DO_NAME obj_nobj width");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2,"DO_NAME obj_otyp width");
_Static_assert((((__typeof__(((struct obj*)0)->otyp))-1)<0)==1,"DO_NAME obj_otyp sign");
_Static_assert(sizeof(((struct obj*)0)->oclass)==1,"DO_NAME obj_oclass width");
_Static_assert((((__typeof__(((struct obj*)0)->oclass))-1)<0)==1,"DO_NAME obj_oclass sign");
_Static_assert(sizeof(((struct obj*)0)->oartifact)==1,"DO_NAME obj_oartifact width");
_Static_assert((((__typeof__(((struct obj*)0)->oartifact))-1)<0)==1,"DO_NAME obj_oartifact sign");
_Static_assert(sizeof(((struct obj*)0)->corpsenm)==4,"DO_NAME obj_corpsenm width");
_Static_assert((((__typeof__(((struct obj*)0)->corpsenm))-1)<0)==1,"DO_NAME obj_corpsenm sign");
_Static_assert(sizeof(((struct obj*)0)->quan)==8,"DO_NAME obj_quan width");
_Static_assert((((__typeof__(((struct obj*)0)->quan))-1)<0)==1,"DO_NAME obj_quan sign");
_Static_assert(sizeof(((struct obj*)0)->spe)==1,"DO_NAME obj_spe width");
_Static_assert((((__typeof__(((struct obj*)0)->spe))-1)<0)==1,"DO_NAME obj_spe sign");
_Static_assert(sizeof(((struct obj*)0)->where)==1,"DO_NAME obj_where width");
_Static_assert((((__typeof__(((struct obj*)0)->where))-1)<0)==1,"DO_NAME obj_where sign");
_Static_assert(sizeof(((struct obj*)0)->oextra)==8,"DO_NAME obj_oextra width");
_Static_assert(sizeof(((struct obj*)0)->owt)==4,"DO_NAME obj_owt width");
_Static_assert((((__typeof__(((struct obj*)0)->owt))-1)<0)==0,"DO_NAME obj_owt sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8,"DO_NAME pm_mflags1 width");
_Static_assert((((__typeof__(((struct permonst*)0)->mflags1))-1)<0)==0,"DO_NAME pm_mflags1 sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8,"DO_NAME pm_mflags2 width");
_Static_assert((((__typeof__(((struct permonst*)0)->mflags2))-1)<0)==0,"DO_NAME pm_mflags2 sign");
_Static_assert(sizeof(((struct permonst*)0)->geno)==2,"DO_NAME pm_geno width");
_Static_assert((((__typeof__(((struct permonst*)0)->geno))-1)<0)==0,"DO_NAME pm_geno sign");
_Static_assert(sizeof(((struct permonst*)0)->msound)==1,"DO_NAME pm_msound width");
_Static_assert((((__typeof__(((struct permonst*)0)->msound))-1)<0)==0,"DO_NAME pm_msound sign");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1,"DO_NAME pm_mlet width");
_Static_assert((((__typeof__(((struct permonst*)0)->mlet))-1)<0)==1,"DO_NAME pm_mlet sign");
_Static_assert(sizeof(((struct permonst*)0)->pmidx)==4,"DO_NAME pm_pmidx width");
_Static_assert((((__typeof__(((struct permonst*)0)->pmidx))-1)<0)==1,"DO_NAME pm_pmidx sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_uname)==8,"DO_NAME cls_oc_uname width");
_Static_assert(sizeof(((struct objclass*)0)->oc_class)==1,"DO_NAME cls_oc_class width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_class))-1)<0)==1,"DO_NAME cls_oc_class sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_descr_idx)==2,"DO_NAME cls_oc_descr_idx width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_descr_idx))-1)<0)==1,"DO_NAME cls_oc_descr_idx sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_weight)==4,"DO_NAME cls_oc_weight width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_weight))-1)<0)==0,"DO_NAME cls_oc_weight sign");
_Static_assert(sizeof(((struct mextra*)0)->mgivenname)==8,"DO_NAME mextra_mgivenname width");
_Static_assert(sizeof(((struct mextra*)0)->ebones)==8,"DO_NAME mextra_ebones width");
_Static_assert(sizeof(((struct oextra*)0)->oname)==8,"DO_NAME oextra_oname width");
_Static_assert(sizeof(((struct objdescr*)0)->oc_name)==8,"DO_NAME descr_oc_name width");
_Static_assert(sizeof(((struct objdescr*)0)->oc_descr)==8,"DO_NAME descr_oc_descr width");
_Static_assert(sizeof(((struct you*)0)->ux)==2,"DO_NAME u_ux width");
_Static_assert((((__typeof__(((struct you*)0)->ux))-1)<0)==1,"DO_NAME u_ux sign");
_Static_assert(sizeof(((struct you*)0)->uy)==2,"DO_NAME u_uy width");
_Static_assert((((__typeof__(((struct you*)0)->uy))-1)<0)==1,"DO_NAME u_uy sign");
_Static_assert(sizeof(((struct you*)0)->ustuck)==8,"DO_NAME u_ustuck width");
_Static_assert(sizeof(((struct you*)0)->usteed)==8,"DO_NAME u_usteed width");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4,"DO_NAME u_umonnum width");
_Static_assert((((__typeof__(((struct you*)0)->umonnum))-1)<0)==1,"DO_NAME u_umonnum sign");
_Static_assert(sizeof(((struct you*)0)->umonster)==4,"DO_NAME u_umonster width");
_Static_assert((((__typeof__(((struct you*)0)->umonster))-1)<0)==1,"DO_NAME u_umonster sign");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8,"DO_NAME prop_intrinsic width");
_Static_assert((((__typeof__(((struct prop*)0)->intrinsic))-1)<0)==1,"DO_NAME prop_intrinsic sign");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8,"DO_NAME prop_extrinsic width");
_Static_assert((((__typeof__(((struct prop*)0)->extrinsic))-1)<0)==1,"DO_NAME prop_extrinsic sign");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8,"DO_NAME prop_blocked width");
_Static_assert((((__typeof__(((struct prop*)0)->blocked))-1)<0)==1,"DO_NAME prop_blocked sign");
_Static_assert(sizeof(((coord*)0)->x)==2,"DO_NAME coord_x width");
_Static_assert((((__typeof__(((coord*)0)->x))-1)<0)==1,"DO_NAME coord_x sign");
_Static_assert(sizeof(((coord*)0)->y)==2,"DO_NAME coord_y width");
_Static_assert((((__typeof__(((coord*)0)->y))-1)<0)==1,"DO_NAME coord_y sign");
_Static_assert(sizeof(((struct Gender*)0)->he)==8,"DO_NAME gender_he width");
_Static_assert(sizeof(((struct Gender*)0)->him)==8,"DO_NAME gender_him width");
_Static_assert(sizeof(((struct Gender*)0)->his)==8,"DO_NAME gender_his width");
_Static_assert(sizeof(((struct _cmd_queue*)0)->typ)==4,"DO_NAME command_typ width");
_Static_assert((((__typeof__(((struct _cmd_queue*)0)->typ))-1)<0)==1,"DO_NAME command_typ sign");
_Static_assert(sizeof(((struct _cmd_queue*)0)->key)==1,"DO_NAME command_key width");
_Static_assert((((__typeof__(((struct _cmd_queue*)0)->key))-1)<0)==1,"DO_NAME command_key sign");
_Static_assert(sizeof(((d_level*)0)->dnum)==2,"DO_NAME dlevel_dnum width");
_Static_assert((((__typeof__(((d_level*)0)->dnum))-1)<0)==1,"DO_NAME dlevel_dnum sign");
_Static_assert(sizeof(((d_level*)0)->dlevel)==2,"DO_NAME dlevel_dlevel width");
_Static_assert((((__typeof__(((d_level*)0)->dlevel))-1)<0)==1,"DO_NAME dlevel_dlevel sign");
#endif
