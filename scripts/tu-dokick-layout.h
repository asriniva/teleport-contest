#ifndef TELEPORT_DOKICK_LAYOUT_H
#define TELEPORT_DOKICK_LAYOUT_H
#include "hack.h"
#include "artifact.h"
#include <stddef.h>
#ifdef EXTRA_SANITY_CHECKS
#error DOKICK remove_monster macro sanity variant requires review
#endif
struct dokick_meta{const char *name;size_t value;};
#define DK_META(k,v) {#k,(size_t)(v)}
static const struct dokick_meta dokick_layout[]={
DK_META(pointerSize,sizeof(void*)),
DK_META(longSize,sizeof(long)),
DK_META(booleanSize,sizeof(boolean)),
DK_META(Trap_Killed_Mon,Trap_Killed_Mon),
DK_META(monsterSize,sizeof(struct monst)),
DK_META(objectSize,sizeof(struct obj)),
DK_META(permonstSize,sizeof(struct permonst)),
DK_META(objectClassSize,sizeof(struct objclass)),
DK_META(mextraSize,sizeof(struct mextra)),
DK_META(oextraSize,sizeof(struct oextra)),
DK_META(eshkSize,sizeof(struct eshk)),
DK_META(propSize,sizeof(struct prop)),
DK_META(coordSize,sizeof(coord)),
DK_META(rmSize,sizeof(struct rm)),
DK_META(attackSize,sizeof(struct attack)),
DK_META(genderSize,sizeof(struct Gender)),
DK_META(vitalSize,sizeof(struct mvitals)),
DK_META(dlevelSize,sizeof(d_level)),
DK_META(stairSize,sizeof(stairway)),
DK_META(mon_nmon,offsetof(struct monst,nmon)),
DK_META(mon_nmon_size,sizeof(((struct monst*)0)->nmon)),
DK_META(mon_data,offsetof(struct monst,data)),
DK_META(mon_data_size,sizeof(((struct monst*)0)->data)),
DK_META(mon_mextra,offsetof(struct monst,mextra)),
DK_META(mon_mextra_size,sizeof(((struct monst*)0)->mextra)),
DK_META(mon_mtame,offsetof(struct monst,mtame)),
DK_META(mon_mtame_size,sizeof(((struct monst*)0)->mtame)),
DK_META(mon_mx,offsetof(struct monst,mx)),
DK_META(mon_mx_size,sizeof(((struct monst*)0)->mx)),
DK_META(mon_my,offsetof(struct monst,my)),
DK_META(mon_my_size,sizeof(((struct monst*)0)->my)),
DK_META(mon_mhp,offsetof(struct monst,mhp)),
DK_META(mon_mhp_size,sizeof(((struct monst*)0)->mhp)),
DK_META(mon_m_ap_type,offsetof(struct monst,m_ap_type)),
DK_META(mon_m_ap_type_size,sizeof(((struct monst*)0)->m_ap_type)),
DK_META(mon_minvent,offsetof(struct monst,minvent)),
DK_META(mon_minvent_size,sizeof(((struct monst*)0)->minvent)),
DK_META(obj_nobj,offsetof(struct obj,nobj)),
DK_META(obj_nobj_size,sizeof(((struct obj*)0)->nobj)),
DK_META(obj_nexthere,offsetof(struct obj,nexthere)),
DK_META(obj_nexthere_size,sizeof(((struct obj*)0)->nexthere)),
DK_META(obj_cobj,offsetof(struct obj,cobj)),
DK_META(obj_cobj_size,sizeof(((struct obj*)0)->cobj)),
DK_META(obj_ocarry,offsetof(struct obj,ocarry)),
DK_META(obj_ocarry_size,sizeof(((struct obj*)0)->ocarry)),
DK_META(obj_oextra,offsetof(struct obj,oextra)),
DK_META(obj_oextra_size,sizeof(((struct obj*)0)->oextra)),
DK_META(obj_otyp,offsetof(struct obj,otyp)),
DK_META(obj_otyp_size,sizeof(((struct obj*)0)->otyp)),
DK_META(obj_oclass,offsetof(struct obj,oclass)),
DK_META(obj_oclass_size,sizeof(((struct obj*)0)->oclass)),
DK_META(obj_oartifact,offsetof(struct obj,oartifact)),
DK_META(obj_oartifact_size,sizeof(((struct obj*)0)->oartifact)),
DK_META(obj_corpsenm,offsetof(struct obj,corpsenm)),
DK_META(obj_corpsenm_size,sizeof(((struct obj*)0)->corpsenm)),
DK_META(obj_migr_species,offsetof(struct obj,migr_species)),
DK_META(obj_migr_species_size,sizeof(((struct obj*)0)->migr_species)),
DK_META(obj_omigr_from_dnum,offsetof(struct obj,omigr_from_dnum)),
DK_META(obj_omigr_from_dnum_size,sizeof(((struct obj*)0)->omigr_from_dnum)),
DK_META(obj_omigr_from_dlevel,offsetof(struct obj,omigr_from_dlevel)),
DK_META(obj_omigr_from_dlevel_size,sizeof(((struct obj*)0)->omigr_from_dlevel)),
DK_META(obj_quan,offsetof(struct obj,quan)),
DK_META(obj_quan_size,sizeof(((struct obj*)0)->quan)),
DK_META(obj_spe,offsetof(struct obj,spe)),
DK_META(obj_spe_size,sizeof(((struct obj*)0)->spe)),
DK_META(obj_where,offsetof(struct obj,where)),
DK_META(obj_where_size,sizeof(((struct obj*)0)->where)),
DK_META(obj_owornmask,offsetof(struct obj,owornmask)),
DK_META(obj_owornmask_size,sizeof(((struct obj*)0)->owornmask)),
DK_META(obj_owt,offsetof(struct obj,owt)),
DK_META(obj_owt_size,sizeof(((struct obj*)0)->owt)),
DK_META(obj_ox,offsetof(struct obj,ox)),
DK_META(obj_ox_size,sizeof(((struct obj*)0)->ox)),
DK_META(obj_oy,offsetof(struct obj,oy)),
DK_META(obj_oy_size,sizeof(((struct obj*)0)->oy)),
DK_META(pm_mflags1,offsetof(struct permonst,mflags1)),
DK_META(pm_mflags1_size,sizeof(((struct permonst*)0)->mflags1)),
DK_META(pm_mflags2,offsetof(struct permonst,mflags2)),
DK_META(pm_mflags2_size,sizeof(((struct permonst*)0)->mflags2)),
DK_META(pm_msize,offsetof(struct permonst,msize)),
DK_META(pm_msize_size,sizeof(((struct permonst*)0)->msize)),
DK_META(pm_mlet,offsetof(struct permonst,mlet)),
DK_META(pm_mlet_size,sizeof(((struct permonst*)0)->mlet)),
DK_META(pm_mmove,offsetof(struct permonst,mmove)),
DK_META(pm_mmove_size,sizeof(((struct permonst*)0)->mmove)),
DK_META(pm_cwt,offsetof(struct permonst,cwt)),
DK_META(pm_cwt_size,sizeof(((struct permonst*)0)->cwt)),
DK_META(pm_mattk,offsetof(struct permonst,mattk)),
DK_META(pm_mattk_size,sizeof(((struct permonst*)0)->mattk)),
DK_META(pm_geno,offsetof(struct permonst,geno)),
DK_META(pm_geno_size,sizeof(((struct permonst*)0)->geno)),
DK_META(pm_pmidx,offsetof(struct permonst,pmidx)),
DK_META(pm_pmidx_size,sizeof(((struct permonst*)0)->pmidx)),
DK_META(cls_oc_cost,offsetof(struct objclass,oc_cost)),
DK_META(cls_oc_cost_size,sizeof(((struct objclass*)0)->oc_cost)),
DK_META(mextra_mgivenname,offsetof(struct mextra,mgivenname)),
DK_META(mextra_mgivenname_size,sizeof(((struct mextra*)0)->mgivenname)),
DK_META(mextra_eshk,offsetof(struct mextra,eshk)),
DK_META(mextra_eshk_size,sizeof(((struct mextra*)0)->eshk)),
DK_META(eshk_robbed,offsetof(struct eshk,robbed)),
DK_META(eshk_robbed_size,sizeof(((struct eshk*)0)->robbed)),
DK_META(eshk_debit,offsetof(struct eshk,debit)),
DK_META(eshk_debit_size,sizeof(((struct eshk*)0)->debit)),
DK_META(eshk_credit,offsetof(struct eshk,credit)),
DK_META(eshk_credit_size,sizeof(((struct eshk*)0)->credit)),
DK_META(eshk_customer,offsetof(struct eshk,customer)),
DK_META(eshk_customer_size,sizeof(((struct eshk*)0)->customer)),
DK_META(oextra_oname,offsetof(struct oextra,oname)),
DK_META(oextra_oname_size,sizeof(((struct oextra*)0)->oname)),
DK_META(u_ux,offsetof(struct you,ux)),
DK_META(u_ux_size,sizeof(((struct you*)0)->ux)),
DK_META(u_uy,offsetof(struct you,uy)),
DK_META(u_uy_size,sizeof(((struct you*)0)->uy)),
DK_META(u_dx,offsetof(struct you,dx)),
DK_META(u_dx_size,sizeof(((struct you*)0)->dx)),
DK_META(u_dy,offsetof(struct you,dy)),
DK_META(u_dy_size,sizeof(((struct you*)0)->dy)),
DK_META(u_ustuck,offsetof(struct you,ustuck)),
DK_META(u_ustuck_size,sizeof(((struct you*)0)->ustuck)),
DK_META(u_usteed,offsetof(struct you,usteed)),
DK_META(u_usteed_size,sizeof(((struct you*)0)->usteed)),
DK_META(u_umonnum,offsetof(struct you,umonnum)),
DK_META(u_umonnum_size,sizeof(((struct you*)0)->umonnum)),
DK_META(u_umonster,offsetof(struct you,umonster)),
DK_META(u_umonster_size,sizeof(((struct you*)0)->umonster)),
DK_META(u_uz,offsetof(struct you,uz)),
DK_META(u_uz_size,sizeof(((struct you*)0)->uz)),
DK_META(u_uprops,offsetof(struct you,uprops)),
DK_META(u_uprops_size,sizeof(((struct you*)0)->uprops)),
DK_META(u_ulevel,offsetof(struct you,ulevel)),
DK_META(u_ulevel_size,sizeof(((struct you*)0)->ulevel)),
DK_META(u_udaminc,offsetof(struct you,udaminc)),
DK_META(u_udaminc_size,sizeof(((struct you*)0)->udaminc)),
DK_META(u_utrap,offsetof(struct you,utrap)),
DK_META(u_utrap_size,sizeof(((struct you*)0)->utrap)),
DK_META(u_utraptype,offsetof(struct you,utraptype)),
DK_META(u_utraptype_size,sizeof(((struct you*)0)->utraptype)),
DK_META(u_urooms,offsetof(struct you,urooms)),
DK_META(u_urooms_size,sizeof(((struct you*)0)->urooms)),
DK_META(u_ushops,offsetof(struct you,ushops)),
DK_META(u_ushops_size,sizeof(((struct you*)0)->ushops)),
DK_META(u_ualign,offsetof(struct you,ualign)),
DK_META(u_ualign_size,sizeof(((struct you*)0)->ualign)),
DK_META(u_uluck,offsetof(struct you,uluck)),
DK_META(u_uluck_size,sizeof(((struct you*)0)->uluck)),
DK_META(u_moreluck,offsetof(struct you,moreluck)),
DK_META(u_moreluck_size,sizeof(((struct you*)0)->moreluck)),
DK_META(align_type,offsetof(align,type)),
DK_META(align_type_size,sizeof(((align*)0)->type)),
DK_META(align_record,offsetof(align,record)),
DK_META(align_record_size,sizeof(((align*)0)->record)),
DK_META(prop_intrinsic,offsetof(struct prop,intrinsic)),
DK_META(prop_intrinsic_size,sizeof(((struct prop*)0)->intrinsic)),
DK_META(prop_extrinsic,offsetof(struct prop,extrinsic)),
DK_META(prop_extrinsic_size,sizeof(((struct prop*)0)->extrinsic)),
DK_META(prop_blocked,offsetof(struct prop,blocked)),
DK_META(prop_blocked_size,sizeof(((struct prop*)0)->blocked)),
DK_META(coord_x,offsetof(coord,x)),
DK_META(coord_x_size,sizeof(((coord*)0)->x)),
DK_META(coord_y,offsetof(coord,y)),
DK_META(coord_y_size,sizeof(((coord*)0)->y)),
DK_META(rm_typ,offsetof(struct rm,typ)),
DK_META(rm_typ_size,sizeof(((struct rm*)0)->typ)),
DK_META(atk_aatyp,offsetof(struct attack,aatyp)),
DK_META(atk_aatyp_size,sizeof(((struct attack*)0)->aatyp)),
DK_META(atk_adtyp,offsetof(struct attack,adtyp)),
DK_META(atk_adtyp_size,sizeof(((struct attack*)0)->adtyp)),
DK_META(atk_damn,offsetof(struct attack,damn)),
DK_META(atk_damn_size,sizeof(((struct attack*)0)->damn)),
DK_META(atk_damd,offsetof(struct attack,damd)),
DK_META(atk_damd_size,sizeof(((struct attack*)0)->damd)),
DK_META(gender_his,offsetof(struct Gender,his)),
DK_META(gender_his_size,sizeof(((struct Gender*)0)->his)),
DK_META(dlevel_dnum,offsetof(d_level,dnum)),
DK_META(dlevel_dnum_size,sizeof(((d_level*)0)->dnum)),
DK_META(dlevel_dlevel,offsetof(d_level,dlevel)),
DK_META(dlevel_dlevel_size,sizeof(((d_level*)0)->dlevel)),
DK_META(stair_tolev,offsetof(stairway,tolev)),
DK_META(stair_tolev_size,sizeof(((stairway*)0)->tolev)),
DK_META(stair_up,offsetof(stairway,up)),
DK_META(stair_up_size,sizeof(((stairway*)0)->up)),
DK_META(stair_isladder,offsetof(stairway,isladder)),
DK_META(stair_isladder_size,sizeof(((stairway*)0)->isladder)),
DK_META(stair_sx,offsetof(stairway,sx)),
DK_META(stair_sx_size,sizeof(((stairway*)0)->sx)),
DK_META(stair_sy,offsetof(stairway,sy)),
DK_META(stair_sy_size,sizeof(((stairway*)0)->sy)),
DK_META(vital_mvflags,offsetof(struct mvitals,mvflags)),
DK_META(vital_mvflags_size,sizeof(((struct mvitals*)0)->mvflags)),
DK_META(youmonst,offsetof(__typeof__(gy),youmonst)),
DK_META(youmonst_size,sizeof(gy.youmonst)),
DK_META(forcefight,offsetof(__typeof__(svc),context.forcefight)),
DK_META(forcefight_size,sizeof(svc.context.forcefight)),
DK_META(context_move,offsetof(__typeof__(svc),context.move)),
DK_META(context_move_size,sizeof(svc.context.move)),
DK_META(bhitpos,offsetof(__typeof__(gb),bhitpos)),
DK_META(bhitpos_size,sizeof(gb.bhitpos)),
DK_META(maploc,offsetof(__typeof__(gm),maploc)),
DK_META(maploc_size,sizeof(gm.maploc)),
DK_META(migrating_objs,offsetof(__typeof__(gm),migrating_objs)),
DK_META(migrating_objs_size,sizeof(gm.migrating_objs)),
DK_META(multi,offsetof(__typeof__(gm),multi)),
DK_META(multi_size,sizeof(gm.multi)),
DK_META(kickedloc,offsetof(__typeof__(gk),kickedloc)),
DK_META(kickedloc_size,sizeof(gk.kickedloc)),
DK_META(kickedobj,offsetof(__typeof__(gk),kickedobj)),
DK_META(kickedobj_size,sizeof(gk.kickedobj)),
DK_META(notonhead,offsetof(__typeof__(gn),notonhead)),
DK_META(notonhead_size,sizeof(gn.notonhead)),
DK_META(nowhere,offsetof(__typeof__(gn),nowhere)),
DK_META(nowhere_size,sizeof(gn.nowhere)),
DK_META(gate_str,offsetof(__typeof__(gg),gate_str)),
DK_META(gate_str_size,sizeof(gg.gate_str)),
DK_META(invent,offsetof(__typeof__(gi),invent)),
DK_META(invent_size,sizeof(gi.invent)),
DK_META(mvitals,offsetof(__typeof__(svm),mvitals)),
DK_META(mvitals_size,sizeof(svm.mvitals)),
DK_META(monsters,offsetof(__typeof__(svl),level.monsters)),
DK_META(monsters_size,sizeof(svl.level.monsters)),
DK_META(floorObjects,offsetof(__typeof__(svl),level.objects)),
DK_META(floorObjects_size,sizeof(svl.level.objects)),
DK_META(locations,offsetof(__typeof__(svl),level.locations)),
DK_META(locations_size,sizeof(svl.level.locations)),
DK_META(killer_name,offsetof(__typeof__(svk),killer.name)),
DK_META(killer_name_size,sizeof(svk.killer.name)),
DK_META(female,offsetof(__typeof__(flags),female)),
DK_META(female_size,sizeof(flags.female)),
DK_META(verbose,offsetof(__typeof__(flags),verbose)),
DK_META(verbose_size,sizeof(flags.verbose)),
DK_META(roleMnum,offsetof(__typeof__(gu),urole.mnum)),
DK_META(roleMnum_size,sizeof(gu.urole.mnum)),
DK_META(plname,offsetof(__typeof__(svp),plname)),
DK_META(plname_size,sizeof(svp.plname)),
DK_META(vizArray,offsetof(__typeof__(gv),viz_array)),
DK_META(vizArray_size,sizeof(gv.viz_array)),
DK_META(qstart_level,offsetof(__typeof__(svd),dungeon_topology.d_qstart_level)),
DK_META(qstart_level_size,sizeof(svd.dungeon_topology.d_qstart_level)),
DK_META(valley_level,offsetof(__typeof__(svd),dungeon_topology.d_valley_level)),
DK_META(valley_level_size,sizeof(svd.dungeon_topology.d_valley_level)),
DK_META(air_level,offsetof(__typeof__(svd),dungeon_topology.d_air_level)),
DK_META(air_level_size,sizeof(svd.dungeon_topology.d_air_level)),
DK_META(water_level,offsetof(__typeof__(svd),dungeon_topology.d_water_level)),
DK_META(water_level_size,sizeof(svd.dungeon_topology.d_water_level)),
DK_META(stronghold,offsetof(__typeof__(svd),dungeon_topology.d_stronghold_level)),
DK_META(stronghold_size,sizeof(svd.dungeon_topology.d_stronghold_level)),
DK_META(astral_level,offsetof(__typeof__(svd),dungeon_topology.d_astral_level)),
DK_META(astral_level_size,sizeof(svd.dungeon_topology.d_astral_level)),
DK_META(AD_DGST,AD_DGST),
DK_META(AIR,AIR),
DK_META(ALTAR,ALTAR),
DK_META(ART_EYES_OF_THE_OVERWORLD,ART_EYES_OF_THE_OVERWORLD),
DK_META(ART_MJOLLNIR,ART_MJOLLNIR),
DK_META(AT_ENGL,AT_ENGL),
DK_META(AT_KICK,AT_KICK),
DK_META(A_CHA,A_CHA),
DK_META(A_CON,A_CON),
DK_META(A_DEX,A_DEX),
DK_META(A_LAWFUL,A_LAWFUL),
DK_META(A_STR,A_STR),
DK_META(A_WIS,A_WIS),
DK_META(BAG_OF_HOLDING,BAG_OF_HOLDING),
DK_META(BAG_OF_TRICKS,BAG_OF_TRICKS),
DK_META(BLINDED,BLINDED),
DK_META(BOULDER,BOULDER),
DK_META(BUFSZ,BUFSZ),
DK_META(CHEST,CHEST),
DK_META(CLOUD,CLOUD),
DK_META(COIN_CLASS,COIN_CLASS),
DK_META(COLNO,COLNO),
DK_META(CORPSE,CORPSE),
DK_META(CORR,CORR),
DK_META(COULD_SEE,COULD_SEE),
DK_META(CXN_PFX_THE,CXN_PFX_THE),
DK_META(DBWALL,DBWALL),
DK_META(DEAF,DEAF),
DK_META(DF_ALL,DF_ALL),
DK_META(DF_RANDOM,DF_RANDOM),
DK_META(DILITHIUM_CRYSTAL,DILITHIUM_CRYSTAL),
DK_META(DOOR,DOOR),
DK_META(DRAWBRIDGE_DOWN,DRAWBRIDGE_DOWN),
DK_META(DRAWBRIDGE_UP,DRAWBRIDGE_UP),
DK_META(D_BROKEN,D_BROKEN),
DK_META(D_CLOSED,D_CLOSED),
DK_META(D_ISOPEN,D_ISOPEN),
DK_META(D_LOCKED,D_LOCKED),
DK_META(D_NODOOR,D_NODOOR),
DK_META(D_TRAPPED,D_TRAPPED),
DK_META(D_WARNED,D_WARNED),
DK_META(ECMD_CANCEL,ECMD_CANCEL),
DK_META(ECMD_FAIL,ECMD_FAIL),
DK_META(ECMD_OK,ECMD_OK),
DK_META(ECMD_TIME,ECMD_TIME),
DK_META(EGG,EGG),
DK_META(ER_NOTHING,ER_NOTHING),
DK_META(EXPENSIVE_CAMERA,EXPENSIVE_CAMERA),
DK_META(FLYING,FLYING),
DK_META(FOOT,FOOT),
DK_META(FOUNTAIN,FOUNTAIN),
DK_META(FUMBLING,FUMBLING),
DK_META(GEM_CLASS,GEM_CLASS),
DK_META(GLASS,GLASS),
DK_META(GLYPH_INVISIBLE,GLYPH_INVISIBLE),
DK_META(GOLD_PIECE,GOLD_PIECE),
DK_META(GRAVE,GRAVE),
DK_META(G_GONE,G_GONE),
DK_META(HALF_PHDAM,HALF_PHDAM),
DK_META(HALLUC,HALLUC),
DK_META(HALLUC_RES,HALLUC_RES),
DK_META(HEAVY_IRON_BALL,HEAVY_IRON_BALL),
DK_META(HOLE,HOLE),
DK_META(ICE,ICE),
DK_META(IN_SIGHT,IN_SIGHT),
DK_META(IRONBARS,IRONBARS),
DK_META(KICKED_WEAPON,KICKED_WEAPON),
DK_META(KICKING_BOOTS,KICKING_BOOTS),
DK_META(KILLED_BY,KILLED_BY),
DK_META(LADDER,LADDER),
DK_META(LARGE_BOX,LARGE_BOX),
DK_META(LAVAWALL,LAVAWALL),
DK_META(LA_DOWN,LA_DOWN),
DK_META(LEG,LEG),
DK_META(LEVITATION,LEVITATION),
DK_META(LOW_PM,LOW_PM),
DK_META(LUCKSTONE,LUCKSTONE),
DK_META(M1_FLY,M1_FLY),
DK_META(M1_NOEYES,M1_NOEYES),
DK_META(M1_NOHANDS,M1_NOHANDS),
DK_META(M1_NOLIMBS,M1_NOLIMBS),
DK_META(M1_SLITHY,M1_SLITHY),
DK_META(M1_THICK_HIDE,M1_THICK_HIDE),
DK_META(M1_TPORT,M1_TPORT),
DK_META(M2_DEMON,M2_DEMON),
DK_META(M2_DWARF,M2_DWARF),
DK_META(M2_ELF,M2_ELF),
DK_META(M2_GIANT,M2_GIANT),
DK_META(M2_GNOME,M2_GNOME),
DK_META(M2_GREEDY,M2_GREEDY),
DK_META(M2_HUMAN,M2_HUMAN),
DK_META(M2_MERC,M2_MERC),
DK_META(M2_ORC,M2_ORC),
DK_META(M2_UNDEAD,M2_UNDEAD),
DK_META(M2_WERE,M2_WERE),
DK_META(MAY_HIT,MAY_HIT),
DK_META(MIGR_LADDER_UP,MIGR_LADDER_UP),
DK_META(MIGR_NOBREAK,MIGR_NOBREAK),
DK_META(MIGR_NOSCATTER,MIGR_NOSCATTER),
DK_META(MIGR_NOWHERE,MIGR_NOWHERE),
DK_META(MIGR_RANDOM,MIGR_RANDOM),
DK_META(MIGR_SSTAIRS,MIGR_SSTAIRS),
DK_META(MIGR_STAIRS_UP,MIGR_STAIRS_UP),
DK_META(MIGR_TO_SPECIES,MIGR_TO_SPECIES),
DK_META(MIGR_WITH_HERO,MIGR_WITH_HERO),
DK_META(MIRROR,MIRROR),
DK_META(MM_ANGRY,MM_ANGRY),
DK_META(MM_FEMALE,MM_FEMALE),
DK_META(MM_MALE,MM_MALE),
DK_META(MM_NOMSG,MM_NOMSG),
DK_META(MOAT,MOAT),
DK_META(MZ_LARGE,MZ_LARGE),
DK_META(MZ_SMALL,MZ_SMALL),
DK_META(M_AP_MONSTER,M_AP_MONSTER),
DK_META(M_AP_TYPMASK,M_AP_TYPMASK),
DK_META(M_ATTK_DEF_DIED,M_ATTK_DEF_DIED),
DK_META(M_ATTK_MISS,M_ATTK_MISS),
DK_META(NATTK,NATTK),
DK_META(NON_PM,NON_PM),
DK_META(NO_TRAP_FLAGS,NO_TRAP_FLAGS),
DK_META(NUMMONS,NUMMONS),
DK_META(OBJ_MIGRATING,OBJ_MIGRATING),
DK_META(OBJ_MINVENT,OBJ_MINVENT),
DK_META(PASSES_WALLS,PASSES_WALLS),
DK_META(PIT,PIT),
DK_META(PL_NSIZ,PL_NSIZ),
DK_META(PM_AMOROUS_DEMON,PM_AMOROUS_DEMON),
DK_META(PM_ARCHEOLOGIST,PM_ARCHEOLOGIST),
DK_META(PM_BABY_PURPLE_WORM,PM_BABY_PURPLE_WORM),
DK_META(PM_BLACK_PUDDING,PM_BLACK_PUDDING),
DK_META(PM_CAPTAIN,PM_CAPTAIN),
DK_META(PM_CHICKATRICE,PM_CHICKATRICE),
DK_META(PM_COCKATRICE,PM_COCKATRICE),
DK_META(PM_FLOATING_EYE,PM_FLOATING_EYE),
DK_META(PM_GRID_BUG,PM_GRID_BUG),
DK_META(PM_HORSE,PM_HORSE),
DK_META(PM_HUMAN,PM_HUMAN),
DK_META(PM_KILLER_BEE,PM_KILLER_BEE),
DK_META(PM_LEPRECHAUN,PM_LEPRECHAUN),
DK_META(PM_LIEUTENANT,PM_LIEUTENANT),
DK_META(PM_MONK,PM_MONK),
DK_META(PM_ORC,PM_ORC),
DK_META(PM_PURPLE_WORM,PM_PURPLE_WORM),
DK_META(PM_RED_DRAGON,PM_RED_DRAGON),
DK_META(PM_SAMURAI,PM_SAMURAI),
DK_META(PM_SASQUATCH,PM_SASQUATCH),
DK_META(PM_SERGEANT,PM_SERGEANT),
DK_META(PM_SHADE,PM_SHADE),
DK_META(PM_SNAKE,PM_SNAKE),
DK_META(PM_SOLDIER,PM_SOLDIER),
DK_META(PM_STONE_GOLEM,PM_STONE_GOLEM),
DK_META(PM_WARHORSE,PM_WARHORSE),
DK_META(PM_WATCHMAN,PM_WATCHMAN),
DK_META(PM_WATCH_CAPTAIN,PM_WATCH_CAPTAIN),
DK_META(PM_WIZARD,PM_WIZARD),
DK_META(POOL,POOL),
DK_META(POT_HEALING,POT_HEALING),
DK_META(PRONOUN_HALLU,PRONOUN_HALLU),
DK_META(P_MARTIAL_ARTS,P_MARTIAL_ARTS),
DK_META(P_NONE,P_NONE),
DK_META(RIGHT_SIDE,RIGHT_SIDE),
DK_META(ROCK,ROCK),
DK_META(ROOM,ROOM),
DK_META(ROWNO,ROWNO),
DK_META(SCORR,SCORR),
DK_META(SDOOR,SDOOR),
DK_META(SEE_INVIS,SEE_INVIS),
DK_META(SHOPBASE,SHOPBASE),
DK_META(SHOP_DOOR_COST,SHOP_DOOR_COST),
DK_META(SINK,SINK),
DK_META(SLT_ENCUMBER,SLT_ENCUMBER),
DK_META(SPIKED_PIT,SPIKED_PIT),
DK_META(STAIRS,STAIRS),
DK_META(STATUE_TRAP,STATUE_TRAP),
DK_META(STONE,STONE),
DK_META(STONE_RES,STONE_RES),
DK_META(S_EEL,S_EEL),
DK_META(S_EYE,S_EYE),
DK_META(S_LDWASHER,S_LDWASHER),
DK_META(S_LIGHT,S_LIGHT),
DK_META(S_LIZARD,S_LIZARD),
DK_META(S_LPUDDING,S_LPUDDING),
DK_META(THRONE,THRONE),
DK_META(TRAPDOOR,TRAPDOOR),
DK_META(TREE,TREE),
DK_META(TREE_LOOTED,TREE_LOOTED),
DK_META(TREE_SWARM,TREE_SWARM),
DK_META(TT_BEARTRAP,TT_BEARTRAP),
DK_META(TT_PIT,TT_PIT),
DK_META(TT_WEB,TT_WEB),
DK_META(T_LOOTED,T_LOOTED),
DK_META(VIS_EFFECTS,VIS_EFFECTS),
DK_META(WATER,WATER),
DK_META(WEB,WEB),
DK_META(WOUNDED_LEGS,WOUNDED_LEGS),
DK_META(W_ARMF,W_ARMF),
};
#undef DK_META
_Static_assert(sizeof(((struct monst*)0)->nmon)==8,"DOKICK mon_nmon width");
_Static_assert(sizeof(((struct monst*)0)->data)==8,"DOKICK mon_data width");
_Static_assert(sizeof(((struct monst*)0)->mextra)==8,"DOKICK mon_mextra width");
_Static_assert(sizeof(((struct monst*)0)->mtame)==1,"DOKICK mon_mtame width");
_Static_assert((((__typeof__(((struct monst*)0)->mtame))-1)<0)==1,"DOKICK mon_mtame signedness");
_Static_assert(sizeof(((struct monst*)0)->mx)==2,"DOKICK mon_mx width");
_Static_assert((((__typeof__(((struct monst*)0)->mx))-1)<0)==1,"DOKICK mon_mx signedness");
_Static_assert(sizeof(((struct monst*)0)->my)==2,"DOKICK mon_my width");
_Static_assert((((__typeof__(((struct monst*)0)->my))-1)<0)==1,"DOKICK mon_my signedness");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4,"DOKICK mon_mhp width");
_Static_assert((((__typeof__(((struct monst*)0)->mhp))-1)<0)==1,"DOKICK mon_mhp signedness");
_Static_assert(sizeof(((struct monst*)0)->m_ap_type)==1,"DOKICK mon_m_ap_type width");
_Static_assert((((__typeof__(((struct monst*)0)->m_ap_type))-1)<0)==0,"DOKICK mon_m_ap_type signedness");
_Static_assert(sizeof(((struct monst*)0)->minvent)==8,"DOKICK mon_minvent width");
_Static_assert(sizeof(((struct obj*)0)->nobj)==8,"DOKICK obj_nobj width");
_Static_assert(sizeof(((struct obj*)0)->nexthere)==8,"DOKICK obj_nexthere width");
_Static_assert(sizeof(((struct obj*)0)->cobj)==8,"DOKICK obj_cobj width");
_Static_assert(sizeof(((struct obj*)0)->ocarry)==8,"DOKICK obj_ocarry width");
_Static_assert(sizeof(((struct obj*)0)->oextra)==8,"DOKICK obj_oextra width");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2,"DOKICK obj_otyp width");
_Static_assert((((__typeof__(((struct obj*)0)->otyp))-1)<0)==1,"DOKICK obj_otyp signedness");
_Static_assert(sizeof(((struct obj*)0)->oclass)==1,"DOKICK obj_oclass width");
_Static_assert((((__typeof__(((struct obj*)0)->oclass))-1)<0)==1,"DOKICK obj_oclass signedness");
_Static_assert(sizeof(((struct obj*)0)->oartifact)==1,"DOKICK obj_oartifact width");
_Static_assert((((__typeof__(((struct obj*)0)->oartifact))-1)<0)==1,"DOKICK obj_oartifact signedness");
_Static_assert(sizeof(((struct obj*)0)->corpsenm)==4,"DOKICK obj_corpsenm width");
_Static_assert((((__typeof__(((struct obj*)0)->corpsenm))-1)<0)==1,"DOKICK obj_corpsenm signedness");
_Static_assert(sizeof(((struct obj*)0)->migr_species)==4,"DOKICK obj_migr_species width");
_Static_assert((((__typeof__(((struct obj*)0)->migr_species))-1)<0)==1,"DOKICK obj_migr_species signedness");
_Static_assert(sizeof(((struct obj*)0)->omigr_from_dnum)==2,"DOKICK obj_omigr_from_dnum width");
_Static_assert((((__typeof__(((struct obj*)0)->omigr_from_dnum))-1)<0)==1,"DOKICK obj_omigr_from_dnum signedness");
_Static_assert(sizeof(((struct obj*)0)->omigr_from_dlevel)==2,"DOKICK obj_omigr_from_dlevel width");
_Static_assert((((__typeof__(((struct obj*)0)->omigr_from_dlevel))-1)<0)==1,"DOKICK obj_omigr_from_dlevel signedness");
_Static_assert(sizeof(((struct obj*)0)->quan)==8,"DOKICK obj_quan width");
_Static_assert((((__typeof__(((struct obj*)0)->quan))-1)<0)==1,"DOKICK obj_quan signedness");
_Static_assert(sizeof(((struct obj*)0)->spe)==1,"DOKICK obj_spe width");
_Static_assert((((__typeof__(((struct obj*)0)->spe))-1)<0)==1,"DOKICK obj_spe signedness");
_Static_assert(sizeof(((struct obj*)0)->where)==1,"DOKICK obj_where width");
_Static_assert((((__typeof__(((struct obj*)0)->where))-1)<0)==1,"DOKICK obj_where signedness");
_Static_assert(sizeof(((struct obj*)0)->owornmask)==8,"DOKICK obj_owornmask width");
_Static_assert((((__typeof__(((struct obj*)0)->owornmask))-1)<0)==1,"DOKICK obj_owornmask signedness");
_Static_assert(sizeof(((struct obj*)0)->owt)==4,"DOKICK obj_owt width");
_Static_assert((((__typeof__(((struct obj*)0)->owt))-1)<0)==0,"DOKICK obj_owt signedness");
_Static_assert(sizeof(((struct obj*)0)->ox)==2,"DOKICK obj_ox width");
_Static_assert((((__typeof__(((struct obj*)0)->ox))-1)<0)==1,"DOKICK obj_ox signedness");
_Static_assert(sizeof(((struct obj*)0)->oy)==2,"DOKICK obj_oy width");
_Static_assert((((__typeof__(((struct obj*)0)->oy))-1)<0)==1,"DOKICK obj_oy signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8,"DOKICK pm_mflags1 width");
_Static_assert((((__typeof__(((struct permonst*)0)->mflags1))-1)<0)==0,"DOKICK pm_mflags1 signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8,"DOKICK pm_mflags2 width");
_Static_assert((((__typeof__(((struct permonst*)0)->mflags2))-1)<0)==0,"DOKICK pm_mflags2 signedness");
_Static_assert(sizeof(((struct permonst*)0)->msize)==1,"DOKICK pm_msize width");
_Static_assert((((__typeof__(((struct permonst*)0)->msize))-1)<0)==0,"DOKICK pm_msize signedness");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1,"DOKICK pm_mlet width");
_Static_assert((((__typeof__(((struct permonst*)0)->mlet))-1)<0)==1,"DOKICK pm_mlet signedness");
_Static_assert(sizeof(((struct permonst*)0)->mmove)==1,"DOKICK pm_mmove width");
_Static_assert((((__typeof__(((struct permonst*)0)->mmove))-1)<0)==1,"DOKICK pm_mmove signedness");
_Static_assert(sizeof(((struct permonst*)0)->cwt)==4,"DOKICK pm_cwt width");
_Static_assert((((__typeof__(((struct permonst*)0)->cwt))-1)<0)==0,"DOKICK pm_cwt signedness");
_Static_assert(sizeof(((struct permonst*)0)->geno)==2,"DOKICK pm_geno width");
_Static_assert((((__typeof__(((struct permonst*)0)->geno))-1)<0)==0,"DOKICK pm_geno signedness");
_Static_assert(sizeof(((struct permonst*)0)->pmidx)==4,"DOKICK pm_pmidx width");
_Static_assert((((__typeof__(((struct permonst*)0)->pmidx))-1)<0)==1,"DOKICK pm_pmidx signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_cost)==2,"DOKICK cls_oc_cost width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_cost))-1)<0)==1,"DOKICK cls_oc_cost signedness");
_Static_assert(sizeof(((struct mextra*)0)->mgivenname)==8,"DOKICK mextra_mgivenname width");
_Static_assert(sizeof(((struct mextra*)0)->eshk)==8,"DOKICK mextra_eshk width");
_Static_assert(sizeof(((struct eshk*)0)->robbed)==8,"DOKICK eshk_robbed width");
_Static_assert((((__typeof__(((struct eshk*)0)->robbed))-1)<0)==1,"DOKICK eshk_robbed signedness");
_Static_assert(sizeof(((struct eshk*)0)->debit)==8,"DOKICK eshk_debit width");
_Static_assert((((__typeof__(((struct eshk*)0)->debit))-1)<0)==1,"DOKICK eshk_debit signedness");
_Static_assert(sizeof(((struct eshk*)0)->credit)==8,"DOKICK eshk_credit width");
_Static_assert((((__typeof__(((struct eshk*)0)->credit))-1)<0)==1,"DOKICK eshk_credit signedness");
_Static_assert(sizeof(((struct oextra*)0)->oname)==8,"DOKICK oextra_oname width");
_Static_assert(sizeof(((struct you*)0)->ux)==2,"DOKICK u_ux width");
_Static_assert((((__typeof__(((struct you*)0)->ux))-1)<0)==1,"DOKICK u_ux signedness");
_Static_assert(sizeof(((struct you*)0)->uy)==2,"DOKICK u_uy width");
_Static_assert((((__typeof__(((struct you*)0)->uy))-1)<0)==1,"DOKICK u_uy signedness");
_Static_assert(sizeof(((struct you*)0)->dx)==4,"DOKICK u_dx width");
_Static_assert((((__typeof__(((struct you*)0)->dx))-1)<0)==1,"DOKICK u_dx signedness");
_Static_assert(sizeof(((struct you*)0)->dy)==4,"DOKICK u_dy width");
_Static_assert((((__typeof__(((struct you*)0)->dy))-1)<0)==1,"DOKICK u_dy signedness");
_Static_assert(sizeof(((struct you*)0)->ustuck)==8,"DOKICK u_ustuck width");
_Static_assert(sizeof(((struct you*)0)->usteed)==8,"DOKICK u_usteed width");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4,"DOKICK u_umonnum width");
_Static_assert((((__typeof__(((struct you*)0)->umonnum))-1)<0)==1,"DOKICK u_umonnum signedness");
_Static_assert(sizeof(((struct you*)0)->umonster)==4,"DOKICK u_umonster width");
_Static_assert((((__typeof__(((struct you*)0)->umonster))-1)<0)==1,"DOKICK u_umonster signedness");
_Static_assert(sizeof(((struct you*)0)->ulevel)==4,"DOKICK u_ulevel width");
_Static_assert((((__typeof__(((struct you*)0)->ulevel))-1)<0)==1,"DOKICK u_ulevel signedness");
_Static_assert(sizeof(((struct you*)0)->udaminc)==1,"DOKICK u_udaminc width");
_Static_assert((((__typeof__(((struct you*)0)->udaminc))-1)<0)==1,"DOKICK u_udaminc signedness");
_Static_assert(sizeof(((struct you*)0)->utrap)==4,"DOKICK u_utrap width");
_Static_assert((((__typeof__(((struct you*)0)->utrap))-1)<0)==0,"DOKICK u_utrap signedness");
_Static_assert(sizeof(((struct you*)0)->utraptype)==4,"DOKICK u_utraptype width");
_Static_assert((((__typeof__(((struct you*)0)->utraptype))-1)<0)==0,"DOKICK u_utraptype signedness");
_Static_assert(sizeof(((struct you*)0)->uluck)==1,"DOKICK u_uluck width");
_Static_assert((((__typeof__(((struct you*)0)->uluck))-1)<0)==1,"DOKICK u_uluck signedness");
_Static_assert(sizeof(((struct you*)0)->moreluck)==1,"DOKICK u_moreluck width");
_Static_assert((((__typeof__(((struct you*)0)->moreluck))-1)<0)==1,"DOKICK u_moreluck signedness");
_Static_assert(sizeof(((align*)0)->type)==1,"DOKICK align_type width");
_Static_assert((((__typeof__(((align*)0)->type))-1)<0)==1,"DOKICK align_type signedness");
_Static_assert(sizeof(((align*)0)->record)==4,"DOKICK align_record width");
_Static_assert((((__typeof__(((align*)0)->record))-1)<0)==1,"DOKICK align_record signedness");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8,"DOKICK prop_intrinsic width");
_Static_assert((((__typeof__(((struct prop*)0)->intrinsic))-1)<0)==1,"DOKICK prop_intrinsic signedness");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8,"DOKICK prop_extrinsic width");
_Static_assert((((__typeof__(((struct prop*)0)->extrinsic))-1)<0)==1,"DOKICK prop_extrinsic signedness");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8,"DOKICK prop_blocked width");
_Static_assert((((__typeof__(((struct prop*)0)->blocked))-1)<0)==1,"DOKICK prop_blocked signedness");
_Static_assert(sizeof(((coord*)0)->x)==2,"DOKICK coord_x width");
_Static_assert((((__typeof__(((coord*)0)->x))-1)<0)==1,"DOKICK coord_x signedness");
_Static_assert(sizeof(((coord*)0)->y)==2,"DOKICK coord_y width");
_Static_assert((((__typeof__(((coord*)0)->y))-1)<0)==1,"DOKICK coord_y signedness");
_Static_assert(sizeof(((struct rm*)0)->typ)==1,"DOKICK rm_typ width");
_Static_assert((((__typeof__(((struct rm*)0)->typ))-1)<0)==1,"DOKICK rm_typ signedness");
_Static_assert(sizeof(((struct attack*)0)->aatyp)==1,"DOKICK atk_aatyp width");
_Static_assert((((__typeof__(((struct attack*)0)->aatyp))-1)<0)==0,"DOKICK atk_aatyp signedness");
_Static_assert(sizeof(((struct attack*)0)->adtyp)==1,"DOKICK atk_adtyp width");
_Static_assert((((__typeof__(((struct attack*)0)->adtyp))-1)<0)==0,"DOKICK atk_adtyp signedness");
_Static_assert(sizeof(((struct attack*)0)->damn)==1,"DOKICK atk_damn width");
_Static_assert((((__typeof__(((struct attack*)0)->damn))-1)<0)==0,"DOKICK atk_damn signedness");
_Static_assert(sizeof(((struct attack*)0)->damd)==1,"DOKICK atk_damd width");
_Static_assert((((__typeof__(((struct attack*)0)->damd))-1)<0)==0,"DOKICK atk_damd signedness");
_Static_assert(sizeof(((struct Gender*)0)->his)==8,"DOKICK gender_his width");
_Static_assert(sizeof(((d_level*)0)->dnum)==2,"DOKICK dlevel_dnum width");
_Static_assert((((__typeof__(((d_level*)0)->dnum))-1)<0)==1,"DOKICK dlevel_dnum signedness");
_Static_assert(sizeof(((d_level*)0)->dlevel)==2,"DOKICK dlevel_dlevel width");
_Static_assert((((__typeof__(((d_level*)0)->dlevel))-1)<0)==1,"DOKICK dlevel_dlevel signedness");
_Static_assert(sizeof(((stairway*)0)->up)==1,"DOKICK stair_up width");
_Static_assert((((__typeof__(((stairway*)0)->up))-1)<0)==1,"DOKICK stair_up signedness");
_Static_assert(sizeof(((stairway*)0)->isladder)==1,"DOKICK stair_isladder width");
_Static_assert((((__typeof__(((stairway*)0)->isladder))-1)<0)==1,"DOKICK stair_isladder signedness");
_Static_assert(sizeof(((stairway*)0)->sx)==2,"DOKICK stair_sx width");
_Static_assert((((__typeof__(((stairway*)0)->sx))-1)<0)==1,"DOKICK stair_sx signedness");
_Static_assert(sizeof(((stairway*)0)->sy)==2,"DOKICK stair_sy width");
_Static_assert((((__typeof__(((stairway*)0)->sy))-1)<0)==1,"DOKICK stair_sy signedness");
_Static_assert(sizeof(((struct mvitals*)0)->mvflags)==1,"DOKICK vital_mvflags width");
_Static_assert((((__typeof__(((struct mvitals*)0)->mvflags))-1)<0)==0,"DOKICK vital_mvflags signedness");
#endif
