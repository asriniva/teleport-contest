#ifndef TELEPORT_DOG_LAYOUT_H
#define TELEPORT_DOG_LAYOUT_H
#include "hack.h"
#include <stddef.h>
#if defined(DEBUG) || NH_DEVEL_STATUS != NH_STATUS_RELEASED
#define TELEPORT_DOG_DEVELOPMENT 1
#else
#define TELEPORT_DOG_DEVELOPMENT 0
#endif
#ifdef NDEBUG
#define TELEPORT_DOG_ASSERTIONS 0
#else
#define TELEPORT_DOG_ASSERTIONS 1
#endif
struct teleport_dog_meta {const char*name;size_t value;};
#define DOG_META(k,v) {#k,(size_t)(v)}
static const struct teleport_dog_meta dog_layout[]={
DOG_META(configDevelopmentDiagnostics,TELEPORT_DOG_DEVELOPMENT),
DOG_META(configAssertions,TELEPORT_DOG_ASSERTIONS),
DOG_META(pointerSize,sizeof(void*)),
DOG_META(intSize,sizeof(int)),
DOG_META(longSize,sizeof(long)),
DOG_META(shortSize,sizeof(short)),
DOG_META(roomSize,sizeof(struct mkroom)),
DOG_META(monSize,sizeof(struct monst)),
DOG_META(mon_data,offsetof(struct monst,data)),
DOG_META(mon_data_size,sizeof(((struct monst*)0)->data)),
DOG_META(mon_nmon,offsetof(struct monst,nmon)),
DOG_META(mon_nmon_size,sizeof(((struct monst*)0)->nmon)),
DOG_META(mon_minvent,offsetof(struct monst,minvent)),
DOG_META(mon_minvent_size,sizeof(((struct monst*)0)->minvent)),
DOG_META(mon_mextra,offsetof(struct monst,mextra)),
DOG_META(mon_mextra_size,sizeof(((struct monst*)0)->mextra)),
DOG_META(mon_m_id,offsetof(struct monst,m_id)),
DOG_META(mon_m_id_size,sizeof(((struct monst*)0)->m_id)),
DOG_META(mon_mtame,offsetof(struct monst,mtame)),
DOG_META(mon_mtame_size,sizeof(((struct monst*)0)->mtame)),
DOG_META(mon_mhp,offsetof(struct monst,mhp)),
DOG_META(mon_mhp_size,sizeof(((struct monst*)0)->mhp)),
DOG_META(mon_mhpmax,offsetof(struct monst,mhpmax)),
DOG_META(mon_mhpmax_size,sizeof(((struct monst*)0)->mhpmax)),
DOG_META(mon_mx,offsetof(struct monst,mx)),
DOG_META(mon_mx_size,sizeof(((struct monst*)0)->mx)),
DOG_META(mon_my,offsetof(struct monst,my)),
DOG_META(mon_my_size,sizeof(((struct monst*)0)->my)),
DOG_META(mon_mux,offsetof(struct monst,mux)),
DOG_META(mon_mux_size,sizeof(((struct monst*)0)->mux)),
DOG_META(mon_muy,offsetof(struct monst,muy)),
DOG_META(mon_muy_size,sizeof(((struct monst*)0)->muy)),
DOG_META(mon_mlstmv,offsetof(struct monst,mlstmv)),
DOG_META(mon_mlstmv_size,sizeof(((struct monst*)0)->mlstmv)),
DOG_META(mon_mstate,offsetof(struct monst,mstate)),
DOG_META(mon_mstate_size,sizeof(((struct monst*)0)->mstate)),
DOG_META(mon_migflags,offsetof(struct monst,migflags)),
DOG_META(mon_migflags_size,sizeof(((struct monst*)0)->migflags)),
DOG_META(mon_mstrategy,offsetof(struct monst,mstrategy)),
DOG_META(mon_mstrategy_size,sizeof(((struct monst*)0)->mstrategy)),
DOG_META(mon_mspec_used,offsetof(struct monst,mspec_used)),
DOG_META(mon_mspec_used_size,sizeof(((struct monst*)0)->mspec_used)),
DOG_META(mon_meating,offsetof(struct monst,meating)),
DOG_META(mon_meating_size,sizeof(((struct monst*)0)->meating)),
DOG_META(mon_weapon_check,offsetof(struct monst,weapon_check)),
DOG_META(mon_weapon_check_size,sizeof(((struct monst*)0)->weapon_check)),
DOG_META(mon_mtrack,offsetof(struct monst,mtrack)),
DOG_META(mon_mtrack_size,sizeof(((struct monst*)0)->mtrack)),
DOG_META(mon_cham,offsetof(struct monst,cham)),
DOG_META(mon_cham_size,sizeof(((struct monst*)0)->cham)),
DOG_META(objSize,sizeof(struct obj)),
DOG_META(obj_nobj,offsetof(struct obj,nobj)),
DOG_META(obj_nobj_size,sizeof(((struct obj*)0)->nobj)),
DOG_META(obj_cobj,offsetof(struct obj,cobj)),
DOG_META(obj_cobj_size,sizeof(((struct obj*)0)->cobj)),
DOG_META(obj_oextra,offsetof(struct obj,oextra)),
DOG_META(obj_oextra_size,sizeof(((struct obj*)0)->oextra)),
DOG_META(obj_age,offsetof(struct obj,age)),
DOG_META(obj_age_size,sizeof(((struct obj*)0)->age)),
DOG_META(obj_corpsenm,offsetof(struct obj,corpsenm)),
DOG_META(obj_corpsenm_size,sizeof(((struct obj*)0)->corpsenm)),
DOG_META(obj_spe,offsetof(struct obj,spe)),
DOG_META(obj_spe_size,sizeof(((struct obj*)0)->spe)),
DOG_META(obj_otyp,offsetof(struct obj,otyp)),
DOG_META(obj_otyp_size,sizeof(((struct obj*)0)->otyp)),
DOG_META(obj_oclass,offsetof(struct obj,oclass)),
DOG_META(obj_oclass_size,sizeof(((struct obj*)0)->oclass)),
DOG_META(obj_ox,offsetof(struct obj,ox)),
DOG_META(obj_ox_size,sizeof(((struct obj*)0)->ox)),
DOG_META(obj_oy,offsetof(struct obj,oy)),
DOG_META(obj_oy_size,sizeof(((struct obj*)0)->oy)),
DOG_META(obj_where,offsetof(struct obj,where)),
DOG_META(obj_where_size,sizeof(((struct obj*)0)->where)),
DOG_META(obj_owornmask,offsetof(struct obj,owornmask)),
DOG_META(obj_owornmask_size,sizeof(((struct obj*)0)->owornmask)),
DOG_META(oextraSize,sizeof(struct oextra)),
DOG_META(oextra_oname,offsetof(struct oextra,oname)),
DOG_META(oextra_oname_size,sizeof(((struct oextra*)0)->oname)),
DOG_META(extraSize,sizeof(struct mextra)),
DOG_META(extra_edog,offsetof(struct mextra,edog)),
DOG_META(extra_edog_size,sizeof(((struct mextra*)0)->edog)),
DOG_META(extra_eshk,offsetof(struct mextra,eshk)),
DOG_META(extra_eshk_size,sizeof(((struct mextra*)0)->eshk)),
DOG_META(extra_epri,offsetof(struct mextra,epri)),
DOG_META(extra_epri_size,sizeof(((struct mextra*)0)->epri)),
DOG_META(extra_egd,offsetof(struct mextra,egd)),
DOG_META(extra_egd_size,sizeof(((struct mextra*)0)->egd)),
DOG_META(edogSize,sizeof(struct edog)),
DOG_META(edog_parentmid,offsetof(struct edog,parentmid)),
DOG_META(edog_parentmid_size,sizeof(((struct edog*)0)->parentmid)),
DOG_META(edog_droptime,offsetof(struct edog,droptime)),
DOG_META(edog_droptime_size,sizeof(((struct edog*)0)->droptime)),
DOG_META(edog_dropdist,offsetof(struct edog,dropdist)),
DOG_META(edog_dropdist_size,sizeof(((struct edog*)0)->dropdist)),
DOG_META(edog_apport,offsetof(struct edog,apport)),
DOG_META(edog_apport_size,sizeof(((struct edog*)0)->apport)),
DOG_META(edog_whistletime,offsetof(struct edog,whistletime)),
DOG_META(edog_whistletime_size,sizeof(((struct edog*)0)->whistletime)),
DOG_META(edog_hungrytime,offsetof(struct edog,hungrytime)),
DOG_META(edog_hungrytime_size,sizeof(((struct edog*)0)->hungrytime)),
DOG_META(edog_ogoal,offsetof(struct edog,ogoal)),
DOG_META(edog_ogoal_size,sizeof(((struct edog*)0)->ogoal)),
DOG_META(edog_abuse,offsetof(struct edog,abuse)),
DOG_META(edog_abuse_size,sizeof(((struct edog*)0)->abuse)),
DOG_META(edog_revivals,offsetof(struct edog,revivals)),
DOG_META(edog_revivals_size,sizeof(((struct edog*)0)->revivals)),
DOG_META(edog_mhpmax_penalty,offsetof(struct edog,mhpmax_penalty)),
DOG_META(edog_mhpmax_penalty_size,sizeof(((struct edog*)0)->mhpmax_penalty)),
DOG_META(eshkSize,sizeof(struct eshk)),
DOG_META(eshk_dismiss_kops,offsetof(struct eshk,dismiss_kops)),
DOG_META(eshk_dismiss_kops_size,sizeof(((struct eshk*)0)->dismiss_kops)),
DOG_META(eshk_shoplevel,offsetof(struct eshk,shoplevel)),
DOG_META(eshk_shoplevel_size,sizeof(((struct eshk*)0)->shoplevel)),
DOG_META(epriSize,sizeof(struct epri)),
DOG_META(epri_shrlevel,offsetof(struct epri,shrlevel)),
DOG_META(epri_shrlevel_size,sizeof(((struct epri*)0)->shrlevel)),
DOG_META(egdSize,sizeof(struct egd)),
DOG_META(egd_gdlevel,offsetof(struct egd,gdlevel)),
DOG_META(egd_gdlevel_size,sizeof(((struct egd*)0)->gdlevel)),
DOG_META(pmSize,sizeof(struct permonst)),
DOG_META(pm_mflags1,offsetof(struct permonst,mflags1)),
DOG_META(pm_mflags1_size,sizeof(((struct permonst*)0)->mflags1)),
DOG_META(pm_mflags2,offsetof(struct permonst,mflags2)),
DOG_META(pm_mflags2_size,sizeof(((struct permonst*)0)->mflags2)),
DOG_META(pm_mflags3,offsetof(struct permonst,mflags3)),
DOG_META(pm_mflags3_size,sizeof(((struct permonst*)0)->mflags3)),
DOG_META(pm_mlet,offsetof(struct permonst,mlet)),
DOG_META(pm_mlet_size,sizeof(((struct permonst*)0)->mlet)),
DOG_META(pm_msize,offsetof(struct permonst,msize)),
DOG_META(pm_msize_size,sizeof(((struct permonst*)0)->msize)),
DOG_META(clsSize,sizeof(struct objclass)),
DOG_META(coordSize,sizeof(coord)),
DOG_META(coord_x,offsetof(coord,x)),
DOG_META(coord_x_size,sizeof(((coord*)0)->x)),
DOG_META(coord_y,offsetof(coord,y)),
DOG_META(coord_y_size,sizeof(((coord*)0)->y)),
DOG_META(levelSize,sizeof(d_level)),
DOG_META(level_dnum,offsetof(d_level,dnum)),
DOG_META(level_dnum_size,sizeof(((d_level*)0)->dnum)),
DOG_META(level_dlevel,offsetof(d_level,dlevel)),
DOG_META(level_dlevel_size,sizeof(((d_level*)0)->dlevel)),
DOG_META(stairSize,sizeof(stairway)),
DOG_META(stair_sx,offsetof(stairway,sx)),
DOG_META(stair_sx_size,sizeof(((stairway*)0)->sx)),
DOG_META(stair_sy,offsetof(stairway,sy)),
DOG_META(stair_sy_size,sizeof(((stairway*)0)->sy)),
DOG_META(trapSize,sizeof(struct trap)),
DOG_META(trap_ntrap,offsetof(struct trap,ntrap)),
DOG_META(trap_ntrap_size,sizeof(((struct trap*)0)->ntrap)),
DOG_META(trap_tx,offsetof(struct trap,tx)),
DOG_META(trap_tx_size,sizeof(((struct trap*)0)->tx)),
DOG_META(trap_ty,offsetof(struct trap,ty)),
DOG_META(trap_ty_size,sizeof(((struct trap*)0)->ty)),
DOG_META(vitalSize,sizeof(struct mvitals)),
DOG_META(vital_mvflags,offsetof(struct mvitals,mvflags)),
DOG_META(vital_mvflags_size,sizeof(((struct mvitals*)0)->mvflags)),
DOG_META(skillSize,sizeof(struct skills)),
DOG_META(skill_skill,offsetof(struct skills,skill)),
DOG_META(skill_skill_size,sizeof(((struct skills*)0)->skill)),
DOG_META(genderSize,sizeof(struct Gender)),
DOG_META(gender_his,offsetof(struct Gender,his)),
DOG_META(gender_his_size,sizeof(((struct Gender*)0)->his)),
DOG_META(propSize,sizeof(struct prop)),
DOG_META(prop_intrinsic,offsetof(struct prop,intrinsic)),
DOG_META(prop_intrinsic_size,sizeof(((struct prop*)0)->intrinsic)),
DOG_META(prop_extrinsic,offsetof(struct prop,extrinsic)),
DOG_META(prop_extrinsic_size,sizeof(((struct prop*)0)->extrinsic)),
DOG_META(prop_blocked,offsetof(struct prop,blocked)),
DOG_META(prop_blocked_size,sizeof(((struct prop*)0)->blocked)),
DOG_META(uSize,sizeof(struct you)),
DOG_META(u_ux,offsetof(struct you,ux)),
DOG_META(u_ux_size,sizeof(((struct you*)0)->ux)),
DOG_META(u_uy,offsetof(struct you,uy)),
DOG_META(u_uy_size,sizeof(((struct you*)0)->uy)),
DOG_META(u_uz,offsetof(struct you,uz)),
DOG_META(u_uz_size,sizeof(((struct you*)0)->uz)),
DOG_META(u_uz0,offsetof(struct you,uz0)),
DOG_META(u_uz0_size,sizeof(((struct you*)0)->uz0)),
DOG_META(u_usteed,offsetof(struct you,usteed)),
DOG_META(u_usteed_size,sizeof(((struct you*)0)->usteed)),
DOG_META(u_ustuck,offsetof(struct you,ustuck)),
DOG_META(u_ustuck_size,sizeof(((struct you*)0)->ustuck)),
DOG_META(u_umonnum,offsetof(struct you,umonnum)),
DOG_META(u_umonnum_size,sizeof(((struct you*)0)->umonnum)),
DOG_META(u_umonster,offsetof(struct you,umonster)),
DOG_META(u_umonster_size,sizeof(((struct you*)0)->umonster)),
DOG_META(u_uprops,offsetof(struct you,uprops)),
DOG_META(u_uprops_size,sizeof(((struct you*)0)->uprops)),
DOG_META(u_weapon_skills,offsetof(struct you,weapon_skills)),
DOG_META(u_weapon_skills_size,sizeof(((struct you*)0)->weapon_skills)),
DOG_META(u_uconduct_pets,offsetof(struct you,uconduct.pets)),
DOG_META(u_uconduct_pets_size,sizeof(((struct you*)0)->uconduct.pets)),
DOG_META(moves,offsetof(__typeof__(svm),moves)),
DOG_META(moves_size,sizeof(svm.moves)),
DOG_META(mvitals,offsetof(__typeof__(svm),mvitals)),
DOG_META(mvitals_size,sizeof(svm.mvitals)),
DOG_META(petnum,offsetof(__typeof__(gu),urole.petnum)),
DOG_META(petnum_size,sizeof(gu.urole.petnum)),
DOG_META(mnum,offsetof(__typeof__(gu),urole.mnum)),
DOG_META(mnum_size,sizeof(gu.urole.mnum)),
DOG_META(preferred_pet,offsetof(__typeof__(gp),preferred_pet)),
DOG_META(preferred_pet_size,sizeof(gp.preferred_pet)),
DOG_META(petname_used,offsetof(__typeof__(gp),petname_used)),
DOG_META(petname_used_size,sizeof(gp.petname_used)),
DOG_META(startingpet_typ,offsetof(__typeof__(svc),context.startingpet_typ)),
DOG_META(startingpet_typ_size,sizeof(svc.context.startingpet_typ)),
DOG_META(startingpet_mid,offsetof(__typeof__(svc),context.startingpet_mid)),
DOG_META(startingpet_mid_size,sizeof(svc.context.startingpet_mid)),
DOG_META(dogname,offsetof(__typeof__(gd),dogname)),
DOG_META(dogname_size,sizeof(gd.dogname)),
DOG_META(catname,offsetof(__typeof__(gc),catname)),
DOG_META(catname_size,sizeof(gc.catname)),
DOG_META(horsename,offsetof(__typeof__(gh),horsename)),
DOG_META(horsename_size,sizeof(gh.horsename)),
DOG_META(bhitpos,offsetof(__typeof__(gb),bhitpos)),
DOG_META(bhitpos_size,sizeof(gb.bhitpos)),
DOG_META(notonhead,offsetof(__typeof__(gn),notonhead)),
DOG_META(notonhead_size,sizeof(gn.notonhead)),
DOG_META(migrating_mons,offsetof(__typeof__(gm),migrating_mons)),
DOG_META(migrating_mons_size,sizeof(gm.migrating_mons)),
DOG_META(mydogs,offsetof(__typeof__(gm),mydogs)),
DOG_META(mydogs_size,sizeof(gm.mydogs)),
DOG_META(migrating_objs,offsetof(__typeof__(gm),migrating_objs)),
DOG_META(migrating_objs_size,sizeof(gm.migrating_objs)),
DOG_META(ftrap,offsetof(__typeof__(gf),ftrap)),
DOG_META(ftrap_size,sizeof(gf.ftrap)),
DOG_META(updest_lx,offsetof(__typeof__(svu),updest.lx)),
DOG_META(updest_lx_size,sizeof(svu.updest.lx)),
DOG_META(updest_hx,offsetof(__typeof__(svu),updest.hx)),
DOG_META(updest_hx_size,sizeof(svu.updest.hx)),
DOG_META(updest_ly,offsetof(__typeof__(svu),updest.ly)),
DOG_META(updest_ly_size,sizeof(svu.updest.ly)),
DOG_META(updest_hy,offsetof(__typeof__(svu),updest.hy)),
DOG_META(updest_hy_size,sizeof(svu.updest.hy)),
DOG_META(rooms,offsetof(__typeof__(svr),rooms)),
DOG_META(rooms_size,sizeof(svr.rooms)),
DOG_META(leader_m_id,offsetof(__typeof__(svq),quest_status.leader_m_id)),
DOG_META(leader_m_id_size,sizeof(svq.quest_status.leader_m_id)),
DOG_META(youmonst,offsetof(__typeof__(gy),youmonst)),
DOG_META(youmonst_size,sizeof(gy.youmonst)),
DOG_META(astral,offsetof(__typeof__(svd),dungeon_topology.d_astral_level)),
DOG_META(astral_size,sizeof(svd.dungeon_topology.d_astral_level)),
DOG_META(qstart,offsetof(__typeof__(svd),dungeon_topology.d_qstart_level)),
DOG_META(qstart_size,sizeof(svd.dungeon_topology.d_qstart_level)),
DOG_META(fmon,offsetof(__typeof__(svl),level.monlist)),
DOG_META(fmon_size,sizeof(svl.level.monlist)),
DOG_META(floorMonsters,offsetof(__typeof__(svl),level.monsters)),
DOG_META(floorMonsters_size,sizeof(svl.level.monsters)),
DOG_META(moonphase,offsetof(__typeof__(flags),moonphase)),
DOG_META(moonphase_size,sizeof(flags.moonphase)),
DOG_META(female,offsetof(__typeof__(flags),female)),
DOG_META(female_size,sizeof(flags.female)),
DOG_META(debug_fuzzer,offsetof(__typeof__(iflags),debug_fuzzer)),
DOG_META(debug_fuzzer_size,sizeof(iflags.debug_fuzzer)),
DOG_META(in_moveloop,offsetof(__typeof__(program_state),in_moveloop)),
DOG_META(in_moveloop_size,sizeof(program_state.in_moveloop)),
DOG_META(viz_array,offsetof(__typeof__(gv),viz_array)),
DOG_META(viz_array_size,sizeof(gv.viz_array)),
DOG_META(ACCFOOD,ACCFOOD),
DOG_META(ACID_RES,ACID_RES),
DOG_META(AD_POLY,AD_POLY),
DOG_META(AGGRAVATE_MONSTER,AGGRAVATE_MONSTER),
DOG_META(AMULET_OF_STRANGULATION,AMULET_OF_STRANGULATION),
DOG_META(APPLE,APPLE),
DOG_META(APPORT,APPORT),
DOG_META(AT_WEAP,AT_WEAP),
DOG_META(A_CHA,A_CHA),
DOG_META(BAG_OF_HOLDING,BAG_OF_HOLDING),
DOG_META(BALL_CLASS,BALL_CLASS),
DOG_META(BANANA,BANANA),
DOG_META(BUFSZ,BUFSZ),
DOG_META(CADAVER,CADAVER),
DOG_META(CARROT,CARROT),
DOG_META(CHAIN_CLASS,CHAIN_CLASS),
DOG_META(CLOVE_OF_GARLIC,CLOVE_OF_GARLIC),
DOG_META(COLNO,COLNO),
DOG_META(CONFLICT,CONFLICT),
DOG_META(COPPER,COPPER),
DOG_META(CORPSE,CORPSE),
DOG_META(CORPSTAT_FEMALE,CORPSTAT_FEMALE),
DOG_META(CORPSTAT_GENDER,CORPSTAT_GENDER),
DOG_META(CORPSTAT_MALE,CORPSTAT_MALE),
DOG_META(DAGGER,DAGGER),
DOG_META(DF_ALL,DF_ALL),
DOG_META(DISMOUNT_GENERIC,DISMOUNT_GENERIC),
DOG_META(DISMOUNT_THROWN,DISMOUNT_THROWN),
DOG_META(DOGFOOD,DOGFOOD),
DOG_META(EGG,EGG),
DOG_META(ENORMOUS_MEATBALL,ENORMOUS_MEATBALL),
DOG_META(EXPENSIVE_CAMERA,EXPENSIVE_CAMERA),
DOG_META(EYE,EYE),
DOG_META(FIGURINE,FIGURINE),
DOG_META(FOOD_CLASS,FOOD_CLASS),
DOG_META(FULL_MOON,FULL_MOON),
DOG_META(GLOB_OF_GREEN_SLIME,GLOB_OF_GREEN_SLIME),
DOG_META(GOLD,GOLD),
DOG_META(G_EXTINCT,G_EXTINCT),
DOG_META(HALLUC,HALLUC),
DOG_META(HALLUC_RES,HALLUC_RES),
DOG_META(IN_SIGHT,IN_SIGHT),
DOG_META(IRON,IRON),
DOG_META(LARGEST_INT,LARGEST_INT),
DOG_META(LEATHER,LEATHER),
DOG_META(LL_CONDUCT,LL_CONDUCT),
DOG_META(LOW_PM,LOW_PM),
DOG_META(LS_MONSTER,LS_MONSTER),
DOG_META(LUMP_OF_ROYAL_JELLY,LUMP_OF_ROYAL_JELLY),
DOG_META(M1_ACID,M1_ACID),
DOG_META(M1_CARNIVORE,M1_CARNIVORE),
DOG_META(M1_HERBIVORE,M1_HERBIVORE),
DOG_META(M1_HUMANOID,M1_HUMANOID),
DOG_META(M1_METALLIVORE,M1_METALLIVORE),
DOG_META(M1_NOEYES,M1_NOEYES),
DOG_META(M1_POIS,M1_POIS),
DOG_META(M1_REGEN,M1_REGEN),
DOG_META(M2_DEMON,M2_DEMON),
DOG_META(M2_DOMESTIC,M2_DOMESTIC),
DOG_META(M2_ELF,M2_ELF),
DOG_META(M2_HUMAN,M2_HUMAN),
DOG_META(M2_PNAME,M2_PNAME),
DOG_META(M2_ROCKTHROW,M2_ROCKTHROW),
DOG_META(M2_STRONG,M2_STRONG),
DOG_META(M2_UNDEAD,M2_UNDEAD),
DOG_META(M2_WERE,M2_WERE),
DOG_META(M3_COVETOUS,M3_COVETOUS),
DOG_META(M3_WANTSARTI,M3_WANTSARTI),
DOG_META(MAGIC_PORTAL,MAGIC_PORTAL),
DOG_META(MANFOOD,MANFOOD),
DOG_META(MAXMONNO,MAXMONNO),
DOG_META(MAX_EGG_HATCH_TIME,MAX_EGG_HATCH_TIME),
DOG_META(MAX_NUM_WORMS,MAX_NUM_WORMS),
DOG_META(MEATBALL,MEATBALL),
DOG_META(MEAT_RING,MEAT_RING),
DOG_META(MEAT_STICK,MEAT_STICK),
DOG_META(METAL,METAL),
DOG_META(MIGR_APPROX_XY,MIGR_APPROX_XY),
DOG_META(MIGR_EXACT_XY,MIGR_EXACT_XY),
DOG_META(MIGR_LADDER_DOWN,MIGR_LADDER_DOWN),
DOG_META(MIGR_LADDER_UP,MIGR_LADDER_UP),
DOG_META(MIGR_LEFTOVERS,MIGR_LEFTOVERS),
DOG_META(MIGR_PORTAL,MIGR_PORTAL),
DOG_META(MIGR_RANDOM,MIGR_RANDOM),
DOG_META(MIGR_SSTAIRS,MIGR_SSTAIRS),
DOG_META(MIGR_STAIRS_DOWN,MIGR_STAIRS_DOWN),
DOG_META(MIGR_STAIRS_UP,MIGR_STAIRS_UP),
DOG_META(MIGR_WITH_HERO,MIGR_WITH_HERO),
DOG_META(MITHRIL,MITHRIL),
DOG_META(MM_EDOG,MM_EDOG),
DOG_META(MM_FEMALE,MM_FEMALE),
DOG_META(MM_IGNOREWATER,MM_IGNOREWATER),
DOG_META(MM_MALE,MM_MALE),
DOG_META(MM_NOMSG,MM_NOMSG),
DOG_META(MON_LIMBO,MON_LIMBO),
DOG_META(MON_MIGRATING,MON_MIGRATING),
DOG_META(MON_STILL_ARRIVING,MON_STILL_ARRIVING),
DOG_META(NEED_HTH_WEAPON,NEED_HTH_WEAPON),
DOG_META(NON_PM,NON_PM),
DOG_META(NO_MINVENT,NO_MINVENT),
DOG_META(NO_TRAP_FLAGS,NO_TRAP_FLAGS),
DOG_META(NUMMONS,NUMMONS),
DOG_META(NUM_OBJECTS,NUM_OBJECTS),
DOG_META(OBJ_FREE,OBJ_FREE),
DOG_META(OBJ_INVENT,OBJ_INVENT),
DOG_META(PLATINUM,PLATINUM),
DOG_META(PM_ANGEL,PM_ANGEL),
DOG_META(PM_BABY_GOLD_DRAGON,PM_BABY_GOLD_DRAGON),
DOG_META(PM_BARBARIAN,PM_BARBARIAN),
DOG_META(PM_CAVE_DWELLER,PM_CAVE_DWELLER),
DOG_META(PM_CHICKATRICE,PM_CHICKATRICE),
DOG_META(PM_COCKATRICE,PM_COCKATRICE),
DOG_META(PM_DEATH,PM_DEATH),
DOG_META(PM_DOG,PM_DOG),
DOG_META(PM_FAMINE,PM_FAMINE),
DOG_META(PM_FIRE_ELEMENTAL,PM_FIRE_ELEMENTAL),
DOG_META(PM_FIRE_VORTEX,PM_FIRE_VORTEX),
DOG_META(PM_FLAMING_SPHERE,PM_FLAMING_SPHERE),
DOG_META(PM_FLESH_GOLEM,PM_FLESH_GOLEM),
DOG_META(PM_FLOATING_EYE,PM_FLOATING_EYE),
DOG_META(PM_GELATINOUS_CUBE,PM_GELATINOUS_CUBE),
DOG_META(PM_GHOUL,PM_GHOUL),
DOG_META(PM_GIANT,PM_GIANT),
DOG_META(PM_GOBLIN,PM_GOBLIN),
DOG_META(PM_GOLD_DRAGON,PM_GOLD_DRAGON),
DOG_META(PM_GRAY_DRAGON,PM_GRAY_DRAGON),
DOG_META(PM_GREEN_SLIME,PM_GREEN_SLIME),
DOG_META(PM_HORSE,PM_HORSE),
DOG_META(PM_HUMAN,PM_HUMAN),
DOG_META(PM_KILLER_BEE,PM_KILLER_BEE),
DOG_META(PM_KITTEN,PM_KITTEN),
DOG_META(PM_LEATHER_GOLEM,PM_LEATHER_GOLEM),
DOG_META(PM_LICHEN,PM_LICHEN),
DOG_META(PM_LITTLE_DOG,PM_LITTLE_DOG),
DOG_META(PM_LIZARD,PM_LIZARD),
DOG_META(PM_LONG_WORM,PM_LONG_WORM),
DOG_META(PM_MEDUSA,PM_MEDUSA),
DOG_META(PM_PESTILENCE,PM_PESTILENCE),
DOG_META(PM_PONY,PM_PONY),
DOG_META(PM_PYROLISK,PM_PYROLISK),
DOG_META(PM_QUEEN_BEE,PM_QUEEN_BEE),
DOG_META(PM_RANGER,PM_RANGER),
DOG_META(PM_RUST_MONSTER,PM_RUST_MONSTER),
DOG_META(PM_SALAMANDER,PM_SALAMANDER),
DOG_META(PM_SAMURAI,PM_SAMURAI),
DOG_META(PM_SHOCKING_SPHERE,PM_SHOCKING_SPHERE),
DOG_META(PM_STALKER,PM_STALKER),
DOG_META(PM_STEAM_VORTEX,PM_STEAM_VORTEX),
DOG_META(PM_VAMPIRE,PM_VAMPIRE),
DOG_META(PM_VAMPIRE_LEADER,PM_VAMPIRE_LEADER),
DOG_META(PM_VLAD_THE_IMPALER,PM_VLAD_THE_IMPALER),
DOG_META(POISON,POISON),
DOG_META(POISON_RES,POISON_RES),
DOG_META(RIN_SLOW_DIGESTION,RIN_SLOW_DIGESTION),
DOG_META(RLOC_NOMSG,RLOC_NOMSG),
DOG_META(ROCK_CLASS,ROCK_CLASS),
DOG_META(ROOMOFFSET,ROOMOFFSET),
DOG_META(ROWNO,ROWNO),
DOG_META(SCROLL_CLASS,SCROLL_CLASS),
DOG_META(SILVER,SILVER),
DOG_META(SLIME_MOLD,SLIME_MOLD),
DOG_META(SPBOOK_CLASS,SPBOOK_CLASS),
DOG_META(SPE_CHARM_MONSTER,SPE_CHARM_MONSTER),
DOG_META(SPE_CREATE_FAMILIAR,SPE_CREATE_FAMILIAR),
DOG_META(STONE_RES,STONE_RES),
DOG_META(STRAT_ARRIVE,STRAT_ARRIVE),
DOG_META(STRAT_WAITFORU,STRAT_WAITFORU),
DOG_META(S_BLOB,S_BLOB),
DOG_META(S_DOG,S_DOG),
DOG_META(S_ELEMENTAL,S_ELEMENTAL),
DOG_META(S_FUNGUS,S_FUNGUS),
DOG_META(S_GHOST,S_GHOST),
DOG_META(S_GOLEM,S_GOLEM),
DOG_META(S_JELLY,S_JELLY),
DOG_META(S_KOBOLD,S_KOBOLD),
DOG_META(S_LIGHT,S_LIGHT),
DOG_META(S_OGRE,S_OGRE),
DOG_META(S_ORC,S_ORC),
DOG_META(S_VORTEX,S_VORTEX),
DOG_META(S_YETI,S_YETI),
DOG_META(TABU,TABU),
DOG_META(TIN,TIN),
DOG_META(TRIPE_RATION,TRIPE_RATION),
DOG_META(UNDEF,UNDEF),
DOG_META(WOOD,WOOD),
};
#undef DOG_META
_Static_assert(sizeof(((struct monst*)0)->data)==8,"mon_data width");
_Static_assert(sizeof(((struct monst*)0)->nmon)==8,"mon_nmon width");
_Static_assert(sizeof(((struct monst*)0)->minvent)==8,"mon_minvent width");
_Static_assert(sizeof(((struct monst*)0)->mextra)==8,"mon_mextra width");
_Static_assert(sizeof(((struct monst*)0)->m_id)==4,"mon_m_id width");
_Static_assert(((__typeof__(((struct monst*)0)->m_id))-1 > 0),"mon_m_id signedness");
_Static_assert(sizeof(((struct monst*)0)->mtame)==1,"mon_mtame width");
_Static_assert(((__typeof__(((struct monst*)0)->mtame))-1 < 0),"mon_mtame signedness");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4,"mon_mhp width");
_Static_assert(((__typeof__(((struct monst*)0)->mhp))-1 < 0),"mon_mhp signedness");
_Static_assert(sizeof(((struct monst*)0)->mhpmax)==4,"mon_mhpmax width");
_Static_assert(((__typeof__(((struct monst*)0)->mhpmax))-1 < 0),"mon_mhpmax signedness");
_Static_assert(sizeof(((struct monst*)0)->mx)==2,"mon_mx width");
_Static_assert(((__typeof__(((struct monst*)0)->mx))-1 < 0),"mon_mx signedness");
_Static_assert(sizeof(((struct monst*)0)->my)==2,"mon_my width");
_Static_assert(((__typeof__(((struct monst*)0)->my))-1 < 0),"mon_my signedness");
_Static_assert(sizeof(((struct monst*)0)->mux)==2,"mon_mux width");
_Static_assert(((__typeof__(((struct monst*)0)->mux))-1 < 0),"mon_mux signedness");
_Static_assert(sizeof(((struct monst*)0)->muy)==2,"mon_muy width");
_Static_assert(((__typeof__(((struct monst*)0)->muy))-1 < 0),"mon_muy signedness");
_Static_assert(sizeof(((struct monst*)0)->mlstmv)==8,"mon_mlstmv width");
_Static_assert(((__typeof__(((struct monst*)0)->mlstmv))-1 < 0),"mon_mlstmv signedness");
_Static_assert(sizeof(((struct monst*)0)->mstate)==8,"mon_mstate width");
_Static_assert(((__typeof__(((struct monst*)0)->mstate))-1 < 0),"mon_mstate signedness");
_Static_assert(sizeof(((struct monst*)0)->migflags)==8,"mon_migflags width");
_Static_assert(((__typeof__(((struct monst*)0)->migflags))-1 < 0),"mon_migflags signedness");
_Static_assert(sizeof(((struct monst*)0)->mstrategy)==8,"mon_mstrategy width");
_Static_assert(((__typeof__(((struct monst*)0)->mstrategy))-1 > 0),"mon_mstrategy signedness");
_Static_assert(sizeof(((struct monst*)0)->mspec_used)==4,"mon_mspec_used width");
_Static_assert(((__typeof__(((struct monst*)0)->mspec_used))-1 < 0),"mon_mspec_used signedness");
_Static_assert(sizeof(((struct monst*)0)->meating)==4,"mon_meating width");
_Static_assert(((__typeof__(((struct monst*)0)->meating))-1 < 0),"mon_meating signedness");
_Static_assert(sizeof(((struct monst*)0)->weapon_check)==2,"mon_weapon_check width");
_Static_assert(((__typeof__(((struct monst*)0)->weapon_check))-1 < 0),"mon_weapon_check signedness");
_Static_assert(sizeof(((struct monst*)0)->cham)==2,"mon_cham width");
_Static_assert(((__typeof__(((struct monst*)0)->cham))-1 < 0),"mon_cham signedness");
_Static_assert(sizeof(((struct obj*)0)->nobj)==8,"obj_nobj width");
_Static_assert(sizeof(((struct obj*)0)->cobj)==8,"obj_cobj width");
_Static_assert(sizeof(((struct obj*)0)->oextra)==8,"obj_oextra width");
_Static_assert(sizeof(((struct obj*)0)->age)==8,"obj_age width");
_Static_assert(((__typeof__(((struct obj*)0)->age))-1 < 0),"obj_age signedness");
_Static_assert(sizeof(((struct obj*)0)->corpsenm)==4,"obj_corpsenm width");
_Static_assert(((__typeof__(((struct obj*)0)->corpsenm))-1 < 0),"obj_corpsenm signedness");
_Static_assert(sizeof(((struct obj*)0)->spe)==1,"obj_spe width");
_Static_assert(((__typeof__(((struct obj*)0)->spe))-1 < 0),"obj_spe signedness");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2,"obj_otyp width");
_Static_assert(((__typeof__(((struct obj*)0)->otyp))-1 < 0),"obj_otyp signedness");
_Static_assert(sizeof(((struct obj*)0)->oclass)==1,"obj_oclass width");
_Static_assert(((__typeof__(((struct obj*)0)->oclass))-1 < 0),"obj_oclass signedness");
_Static_assert(sizeof(((struct obj*)0)->ox)==2,"obj_ox width");
_Static_assert(((__typeof__(((struct obj*)0)->ox))-1 < 0),"obj_ox signedness");
_Static_assert(sizeof(((struct obj*)0)->oy)==2,"obj_oy width");
_Static_assert(((__typeof__(((struct obj*)0)->oy))-1 < 0),"obj_oy signedness");
_Static_assert(sizeof(((struct obj*)0)->where)==1,"obj_where width");
_Static_assert(((__typeof__(((struct obj*)0)->where))-1 < 0),"obj_where signedness");
_Static_assert(sizeof(((struct obj*)0)->owornmask)==8,"obj_owornmask width");
_Static_assert(((__typeof__(((struct obj*)0)->owornmask))-1 < 0),"obj_owornmask signedness");
_Static_assert(sizeof(((struct oextra*)0)->oname)==8,"oextra_oname width");
_Static_assert(sizeof(((struct mextra*)0)->edog)==8,"extra_edog width");
_Static_assert(sizeof(((struct mextra*)0)->eshk)==8,"extra_eshk width");
_Static_assert(sizeof(((struct mextra*)0)->epri)==8,"extra_epri width");
_Static_assert(sizeof(((struct mextra*)0)->egd)==8,"extra_egd width");
_Static_assert(sizeof(((struct edog*)0)->parentmid)==4,"edog_parentmid width");
_Static_assert(((__typeof__(((struct edog*)0)->parentmid))-1 > 0),"edog_parentmid signedness");
_Static_assert(sizeof(((struct edog*)0)->droptime)==8,"edog_droptime width");
_Static_assert(((__typeof__(((struct edog*)0)->droptime))-1 < 0),"edog_droptime signedness");
_Static_assert(sizeof(((struct edog*)0)->dropdist)==4,"edog_dropdist width");
_Static_assert(((__typeof__(((struct edog*)0)->dropdist))-1 > 0),"edog_dropdist signedness");
_Static_assert(sizeof(((struct edog*)0)->apport)==4,"edog_apport width");
_Static_assert(((__typeof__(((struct edog*)0)->apport))-1 < 0),"edog_apport signedness");
_Static_assert(sizeof(((struct edog*)0)->whistletime)==8,"edog_whistletime width");
_Static_assert(((__typeof__(((struct edog*)0)->whistletime))-1 < 0),"edog_whistletime signedness");
_Static_assert(sizeof(((struct edog*)0)->hungrytime)==8,"edog_hungrytime width");
_Static_assert(((__typeof__(((struct edog*)0)->hungrytime))-1 < 0),"edog_hungrytime signedness");
_Static_assert(sizeof(((struct edog*)0)->abuse)==4,"edog_abuse width");
_Static_assert(((__typeof__(((struct edog*)0)->abuse))-1 < 0),"edog_abuse signedness");
_Static_assert(sizeof(((struct edog*)0)->revivals)==4,"edog_revivals width");
_Static_assert(((__typeof__(((struct edog*)0)->revivals))-1 < 0),"edog_revivals signedness");
_Static_assert(sizeof(((struct edog*)0)->mhpmax_penalty)==4,"edog_mhpmax_penalty width");
_Static_assert(((__typeof__(((struct edog*)0)->mhpmax_penalty))-1 < 0),"edog_mhpmax_penalty signedness");
_Static_assert(sizeof(((struct eshk*)0)->dismiss_kops)==1,"eshk_dismiss_kops width");
_Static_assert(((__typeof__(((struct eshk*)0)->dismiss_kops))-1 < 0),"eshk_dismiss_kops signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8,"pm_mflags1 width");
_Static_assert(((__typeof__(((struct permonst*)0)->mflags1))-1 > 0),"pm_mflags1 signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8,"pm_mflags2 width");
_Static_assert(((__typeof__(((struct permonst*)0)->mflags2))-1 > 0),"pm_mflags2 signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags3)==2,"pm_mflags3 width");
_Static_assert(((__typeof__(((struct permonst*)0)->mflags3))-1 > 0),"pm_mflags3 signedness");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1,"pm_mlet width");
_Static_assert(((__typeof__(((struct permonst*)0)->mlet))-1 < 0),"pm_mlet signedness");
_Static_assert(sizeof(((struct permonst*)0)->msize)==1,"pm_msize width");
_Static_assert(((__typeof__(((struct permonst*)0)->msize))-1 > 0),"pm_msize signedness");
_Static_assert(sizeof(((coord*)0)->x)==2,"coord_x width");
_Static_assert(((__typeof__(((coord*)0)->x))-1 < 0),"coord_x signedness");
_Static_assert(sizeof(((coord*)0)->y)==2,"coord_y width");
_Static_assert(((__typeof__(((coord*)0)->y))-1 < 0),"coord_y signedness");
_Static_assert(sizeof(((d_level*)0)->dnum)==2,"level_dnum width");
_Static_assert(((__typeof__(((d_level*)0)->dnum))-1 < 0),"level_dnum signedness");
_Static_assert(sizeof(((d_level*)0)->dlevel)==2,"level_dlevel width");
_Static_assert(((__typeof__(((d_level*)0)->dlevel))-1 < 0),"level_dlevel signedness");
_Static_assert(sizeof(((stairway*)0)->sx)==2,"stair_sx width");
_Static_assert(((__typeof__(((stairway*)0)->sx))-1 < 0),"stair_sx signedness");
_Static_assert(sizeof(((stairway*)0)->sy)==2,"stair_sy width");
_Static_assert(((__typeof__(((stairway*)0)->sy))-1 < 0),"stair_sy signedness");
_Static_assert(sizeof(((struct trap*)0)->ntrap)==8,"trap_ntrap width");
_Static_assert(sizeof(((struct trap*)0)->tx)==2,"trap_tx width");
_Static_assert(((__typeof__(((struct trap*)0)->tx))-1 < 0),"trap_tx signedness");
_Static_assert(sizeof(((struct trap*)0)->ty)==2,"trap_ty width");
_Static_assert(((__typeof__(((struct trap*)0)->ty))-1 < 0),"trap_ty signedness");
_Static_assert(sizeof(((struct mvitals*)0)->mvflags)==1,"vital_mvflags width");
_Static_assert(((__typeof__(((struct mvitals*)0)->mvflags))-1 > 0),"vital_mvflags signedness");
_Static_assert(sizeof(((struct skills*)0)->skill)==2,"skill_skill width");
_Static_assert(((__typeof__(((struct skills*)0)->skill))-1 < 0),"skill_skill signedness");
_Static_assert(sizeof(((struct Gender*)0)->his)==8,"gender_his width");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8,"prop_intrinsic width");
_Static_assert(((__typeof__(((struct prop*)0)->intrinsic))-1 < 0),"prop_intrinsic signedness");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8,"prop_extrinsic width");
_Static_assert(((__typeof__(((struct prop*)0)->extrinsic))-1 < 0),"prop_extrinsic signedness");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8,"prop_blocked width");
_Static_assert(((__typeof__(((struct prop*)0)->blocked))-1 < 0),"prop_blocked signedness");
_Static_assert(sizeof(((struct you*)0)->ux)==2,"u_ux width");
_Static_assert(((__typeof__(((struct you*)0)->ux))-1 < 0),"u_ux signedness");
_Static_assert(sizeof(((struct you*)0)->uy)==2,"u_uy width");
_Static_assert(((__typeof__(((struct you*)0)->uy))-1 < 0),"u_uy signedness");
_Static_assert(sizeof(((struct you*)0)->usteed)==8,"u_usteed width");
_Static_assert(sizeof(((struct you*)0)->ustuck)==8,"u_ustuck width");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4,"u_umonnum width");
_Static_assert(((__typeof__(((struct you*)0)->umonnum))-1 < 0),"u_umonnum signedness");
_Static_assert(sizeof(((struct you*)0)->umonster)==4,"u_umonster width");
_Static_assert(((__typeof__(((struct you*)0)->umonster))-1 < 0),"u_umonster signedness");
_Static_assert(sizeof(((struct you*)0)->uconduct.pets)==8,"u_uconduct_pets width");
_Static_assert(((__typeof__(((struct you*)0)->uconduct.pets))-1 < 0),"u_uconduct_pets signedness");
_Static_assert(sizeof(gu.urole.petnum)==2 && (__typeof__(gu.urole.petnum))-1 < 0,"gu.urole.petnum ABI");
_Static_assert(sizeof(gu.urole.mnum)==2 && (__typeof__(gu.urole.mnum))-1 < 0,"gu.urole.mnum ABI");
_Static_assert(sizeof(gp.preferred_pet)==1 && (__typeof__(gp.preferred_pet))-1 < 0,"gp.preferred_pet ABI");
_Static_assert(sizeof(gp.petname_used)==4 && (__typeof__(gp.petname_used))-1 < 0,"gp.petname_used ABI");
_Static_assert(sizeof(svc.context.startingpet_typ)==4 && (__typeof__(svc.context.startingpet_typ))-1 < 0,"svc.context.startingpet_typ ABI");
_Static_assert(sizeof(svc.context.startingpet_mid)==4 && (__typeof__(svc.context.startingpet_mid))-1 > 0,"svc.context.startingpet_mid ABI");
_Static_assert(sizeof(gn.notonhead)==1 && (__typeof__(gn.notonhead))-1 < 0,"gn.notonhead ABI");
_Static_assert(sizeof(svu.updest.lx)==2 && (__typeof__(svu.updest.lx))-1 < 0,"svu.updest.lx ABI");
_Static_assert(sizeof(svu.updest.hx)==2 && (__typeof__(svu.updest.hx))-1 < 0,"svu.updest.hx ABI");
_Static_assert(sizeof(svu.updest.ly)==2 && (__typeof__(svu.updest.ly))-1 < 0,"svu.updest.ly ABI");
_Static_assert(sizeof(svu.updest.hy)==2 && (__typeof__(svu.updest.hy))-1 < 0,"svu.updest.hy ABI");
_Static_assert(sizeof(svq.quest_status.leader_m_id)==4 && (__typeof__(svq.quest_status.leader_m_id))-1 > 0,"svq.quest_status.leader_m_id ABI");
_Static_assert(sizeof(flags.moonphase)==4 && (__typeof__(flags.moonphase))-1 > 0,"flags.moonphase ABI");
_Static_assert(sizeof(flags.female)==1 && (__typeof__(flags.female))-1 < 0,"flags.female ABI");
_Static_assert(sizeof(iflags.debug_fuzzer)==1 && (__typeof__(iflags.debug_fuzzer))-1 < 0,"iflags.debug_fuzzer ABI");
_Static_assert(sizeof(program_state.in_moveloop)==4 && (__typeof__(program_state.in_moveloop))-1 < 0,"program_state.in_moveloop ABI");
size_t probe_context_size(void){return sizeof(struct edog);}
int probe_layout_count(void){return sizeof dog_layout/sizeof dog_layout[0];}
const char*probe_layout_name(int i){return dog_layout[i].name;}
size_t probe_layout_value(int i){return dog_layout[i].value;}
#endif
