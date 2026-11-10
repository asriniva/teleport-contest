/* MONMOVE compiler-derived layout and independent field ABI guards only. */
#ifndef TELEPORT_MONMOVE_LAYOUT_H
#define TELEPORT_MONMOVE_LAYOUT_H
#include "hack.h"
#include "mfndpos.h"
#include <stddef.h>
#define MONMOVE_META(k,v) {#k,(size_t)(v)}
static const struct {const char*name;size_t value;}teleport_monmove_layout[]={
MONMOVE_META(pointerSize,sizeof(void*)),
MONMOVE_META(intSize,sizeof(int)),
MONMOVE_META(longSize,sizeof(long)),
MONMOVE_META(coordxySize,sizeof(coordxy)),
MONMOVE_META(booleanSize,sizeof(boolean)),
MONMOVE_META(mtrackSize,sizeof(((struct monst*)0)->mtrack)),
MONMOVE_META(locations,offsetof(__typeof__(svl),level.locations)),
MONMOVE_META(floorObjects,offsetof(__typeof__(svl),level.objects)),
MONMOVE_META(floorMonsters,offsetof(__typeof__(svl),level.monsters)),
MONMOVE_META(monlist,offsetof(__typeof__(svl),level.monlist)),
MONMOVE_META(levelFlags,offsetof(__typeof__(svl),level.flags)),
MONMOVE_META(rogueLevel,offsetof(__typeof__(svd),dungeon_topology.d_rogue_level)),
MONMOVE_META(astralLevel,offsetof(__typeof__(svd),dungeon_topology.d_astral_level)),
MONMOVE_META(objSize,sizeof(struct obj)),
MONMOVE_META(obj_cobj,offsetof(struct obj,cobj)),
MONMOVE_META(obj_cobj_size,sizeof(((struct obj*)0)->cobj)),
MONMOVE_META(obj_corpsenm,offsetof(struct obj,corpsenm)),
MONMOVE_META(obj_corpsenm_size,sizeof(((struct obj*)0)->corpsenm)),
MONMOVE_META(obj_nexthere,offsetof(struct obj,nexthere)),
MONMOVE_META(obj_nexthere_size,sizeof(((struct obj*)0)->nexthere)),
MONMOVE_META(obj_nobj,offsetof(struct obj,nobj)),
MONMOVE_META(obj_nobj_size,sizeof(((struct obj*)0)->nobj)),
MONMOVE_META(obj_o_id,offsetof(struct obj,o_id)),
MONMOVE_META(obj_o_id_size,sizeof(((struct obj*)0)->o_id)),
MONMOVE_META(obj_oartifact,offsetof(struct obj,oartifact)),
MONMOVE_META(obj_oartifact_size,sizeof(((struct obj*)0)->oartifact)),
MONMOVE_META(obj_oclass,offsetof(struct obj,oclass)),
MONMOVE_META(obj_oclass_size,sizeof(((struct obj*)0)->oclass)),
MONMOVE_META(obj_otyp,offsetof(struct obj,otyp)),
MONMOVE_META(obj_otyp_size,sizeof(((struct obj*)0)->otyp)),
MONMOVE_META(obj_ox,offsetof(struct obj,ox)),
MONMOVE_META(obj_ox_size,sizeof(((struct obj*)0)->ox)),
MONMOVE_META(obj_oy,offsetof(struct obj,oy)),
MONMOVE_META(obj_oy_size,sizeof(((struct obj*)0)->oy)),
MONMOVE_META(obj_quan,offsetof(struct obj,quan)),
MONMOVE_META(obj_quan_size,sizeof(((struct obj*)0)->quan)),
MONMOVE_META(obj_where,offsetof(struct obj,where)),
MONMOVE_META(obj_where_size,sizeof(((struct obj*)0)->where)),
MONMOVE_META(monSize,sizeof(struct monst)),
MONMOVE_META(mon_cham,offsetof(struct monst,cham)),
MONMOVE_META(mon_cham_size,sizeof(((struct monst*)0)->cham)),
MONMOVE_META(mon_data,offsetof(struct monst,data)),
MONMOVE_META(mon_data_size,sizeof(((struct monst*)0)->data)),
MONMOVE_META(mon_m_ap_type,offsetof(struct monst,m_ap_type)),
MONMOVE_META(mon_m_ap_type_size,sizeof(((struct monst*)0)->m_ap_type)),
MONMOVE_META(mon_m_lev,offsetof(struct monst,m_lev)),
MONMOVE_META(mon_m_lev_size,sizeof(((struct monst*)0)->m_lev)),
MONMOVE_META(mon_mappearance,offsetof(struct monst,mappearance)),
MONMOVE_META(mon_mappearance_size,sizeof(((struct monst*)0)->mappearance)),
MONMOVE_META(mon_meating,offsetof(struct monst,meating)),
MONMOVE_META(mon_meating_size,sizeof(((struct monst*)0)->meating)),
MONMOVE_META(mon_mextra,offsetof(struct monst,mextra)),
MONMOVE_META(mon_mextra_size,sizeof(((struct monst*)0)->mextra)),
MONMOVE_META(mon_mgoal,offsetof(struct monst,mgoal)),
MONMOVE_META(mon_mgoal_size,sizeof(((struct monst*)0)->mgoal)),
MONMOVE_META(mon_mhp,offsetof(struct monst,mhp)),
MONMOVE_META(mon_mhp_size,sizeof(((struct monst*)0)->mhp)),
MONMOVE_META(mon_mhpmax,offsetof(struct monst,mhpmax)),
MONMOVE_META(mon_mhpmax_size,sizeof(((struct monst*)0)->mhpmax)),
MONMOVE_META(mon_minvent,offsetof(struct monst,minvent)),
MONMOVE_META(mon_minvent_size,sizeof(((struct monst*)0)->minvent)),
MONMOVE_META(mon_movement,offsetof(struct monst,movement)),
MONMOVE_META(mon_movement_size,sizeof(((struct monst*)0)->movement)),
MONMOVE_META(mon_mspec_used,offsetof(struct monst,mspec_used)),
MONMOVE_META(mon_mspec_used_size,sizeof(((struct monst*)0)->mspec_used)),
MONMOVE_META(mon_mstate,offsetof(struct monst,mstate)),
MONMOVE_META(mon_mstate_size,sizeof(((struct monst*)0)->mstate)),
MONMOVE_META(mon_mstrategy,offsetof(struct monst,mstrategy)),
MONMOVE_META(mon_mstrategy_size,sizeof(((struct monst*)0)->mstrategy)),
MONMOVE_META(mon_mtame,offsetof(struct monst,mtame)),
MONMOVE_META(mon_mtame_size,sizeof(((struct monst*)0)->mtame)),
MONMOVE_META(mon_mtrack,offsetof(struct monst,mtrack)),
MONMOVE_META(mon_mtrack_size,sizeof(((struct monst*)0)->mtrack)),
MONMOVE_META(mon_mux,offsetof(struct monst,mux)),
MONMOVE_META(mon_mux_size,sizeof(((struct monst*)0)->mux)),
MONMOVE_META(mon_muy,offsetof(struct monst,muy)),
MONMOVE_META(mon_muy_size,sizeof(((struct monst*)0)->muy)),
MONMOVE_META(mon_mw,offsetof(struct monst,mw)),
MONMOVE_META(mon_mw_size,sizeof(((struct monst*)0)->mw)),
MONMOVE_META(mon_mx,offsetof(struct monst,mx)),
MONMOVE_META(mon_mx_size,sizeof(((struct monst*)0)->mx)),
MONMOVE_META(mon_my,offsetof(struct monst,my)),
MONMOVE_META(mon_my_size,sizeof(((struct monst*)0)->my)),
MONMOVE_META(mon_nmon,offsetof(struct monst,nmon)),
MONMOVE_META(mon_nmon_size,sizeof(((struct monst*)0)->nmon)),
MONMOVE_META(mon_weapon_check,offsetof(struct monst,weapon_check)),
MONMOVE_META(mon_weapon_check_size,sizeof(((struct monst*)0)->weapon_check)),
MONMOVE_META(pmSize,sizeof(struct permonst)),
MONMOVE_META(pm_geno,offsetof(struct permonst,geno)),
MONMOVE_META(pm_geno_size,sizeof(((struct permonst*)0)->geno)),
MONMOVE_META(pm_mattk,offsetof(struct permonst,mattk)),
MONMOVE_META(pm_mattk_size,sizeof(((struct permonst*)0)->mattk)),
MONMOVE_META(pm_mflags1,offsetof(struct permonst,mflags1)),
MONMOVE_META(pm_mflags1_size,sizeof(((struct permonst*)0)->mflags1)),
MONMOVE_META(pm_mflags2,offsetof(struct permonst,mflags2)),
MONMOVE_META(pm_mflags2_size,sizeof(((struct permonst*)0)->mflags2)),
MONMOVE_META(pm_mflags3,offsetof(struct permonst,mflags3)),
MONMOVE_META(pm_mflags3_size,sizeof(((struct permonst*)0)->mflags3)),
MONMOVE_META(pm_mlet,offsetof(struct permonst,mlet)),
MONMOVE_META(pm_mlet_size,sizeof(((struct permonst*)0)->mlet)),
MONMOVE_META(pm_mlevel,offsetof(struct permonst,mlevel)),
MONMOVE_META(pm_mlevel_size,sizeof(((struct permonst*)0)->mlevel)),
MONMOVE_META(pm_mmove,offsetof(struct permonst,mmove)),
MONMOVE_META(pm_mmove_size,sizeof(((struct permonst*)0)->mmove)),
MONMOVE_META(pm_msize,offsetof(struct permonst,msize)),
MONMOVE_META(pm_msize_size,sizeof(((struct permonst*)0)->msize)),
MONMOVE_META(pm_msound,offsetof(struct permonst,msound)),
MONMOVE_META(pm_msound_size,sizeof(((struct permonst*)0)->msound)),
MONMOVE_META(pm_pmidx,offsetof(struct permonst,pmidx)),
MONMOVE_META(pm_pmidx_size,sizeof(((struct permonst*)0)->pmidx)),
MONMOVE_META(attackSize,sizeof(struct attack)),
MONMOVE_META(attack_aatyp,offsetof(struct attack,aatyp)),
MONMOVE_META(attack_aatyp_size,sizeof(((struct attack*)0)->aatyp)),
MONMOVE_META(attack_adtyp,offsetof(struct attack,adtyp)),
MONMOVE_META(attack_adtyp_size,sizeof(((struct attack*)0)->adtyp)),
MONMOVE_META(attack_damd,offsetof(struct attack,damd)),
MONMOVE_META(attack_damd_size,sizeof(((struct attack*)0)->damd)),
MONMOVE_META(attack_damn,offsetof(struct attack,damn)),
MONMOVE_META(attack_damn_size,sizeof(((struct attack*)0)->damn)),
MONMOVE_META(youSize,sizeof(struct you)),
MONMOVE_META(you_dx,offsetof(struct you,dx)),
MONMOVE_META(you_dx_size,sizeof(((struct you*)0)->dx)),
MONMOVE_META(you_dy,offsetof(struct you,dy)),
MONMOVE_META(you_dy_size,sizeof(((struct you*)0)->dy)),
MONMOVE_META(you_mh,offsetof(struct you,mh)),
MONMOVE_META(you_mh_size,sizeof(((struct you*)0)->mh)),
MONMOVE_META(you_uhp,offsetof(struct you,uhp)),
MONMOVE_META(you_uhp_size,sizeof(((struct you*)0)->uhp)),
MONMOVE_META(you_umonnum,offsetof(struct you,umonnum)),
MONMOVE_META(you_umonnum_size,sizeof(((struct you*)0)->umonnum)),
MONMOVE_META(you_umonster,offsetof(struct you,umonster)),
MONMOVE_META(you_umonster_size,sizeof(((struct you*)0)->umonster)),
MONMOVE_META(you_uprops,offsetof(struct you,uprops)),
MONMOVE_META(you_uprops_size,sizeof(((struct you*)0)->uprops)),
MONMOVE_META(you_uroleplay,offsetof(struct you,uroleplay)),
MONMOVE_META(you_uroleplay_size,sizeof(((struct you*)0)->uroleplay)),
MONMOVE_META(you_ustuck,offsetof(struct you,ustuck)),
MONMOVE_META(you_ustuck_size,sizeof(((struct you*)0)->ustuck)),
MONMOVE_META(you_ux,offsetof(struct you,ux)),
MONMOVE_META(you_ux_size,sizeof(((struct you*)0)->ux)),
MONMOVE_META(you_ux0,offsetof(struct you,ux0)),
MONMOVE_META(you_ux0_size,sizeof(((struct you*)0)->ux0)),
MONMOVE_META(you_uy,offsetof(struct you,uy)),
MONMOVE_META(you_uy_size,sizeof(((struct you*)0)->uy)),
MONMOVE_META(you_uy0,offsetof(struct you,uy0)),
MONMOVE_META(you_uy0_size,sizeof(((struct you*)0)->uy0)),
MONMOVE_META(you_uz,offsetof(struct you,uz)),
MONMOVE_META(you_uz_size,sizeof(((struct you*)0)->uz)),
MONMOVE_META(levelSize,sizeof(struct d_level)),
MONMOVE_META(level_dlevel,offsetof(struct d_level,dlevel)),
MONMOVE_META(level_dlevel_size,sizeof(((struct d_level*)0)->dlevel)),
MONMOVE_META(level_dnum,offsetof(struct d_level,dnum)),
MONMOVE_META(level_dnum_size,sizeof(((struct d_level*)0)->dnum)),
MONMOVE_META(coordSize,sizeof(struct nhcoord)),
MONMOVE_META(coord_x,offsetof(struct nhcoord,x)),
MONMOVE_META(coord_x_size,sizeof(((struct nhcoord*)0)->x)),
MONMOVE_META(coord_y,offsetof(struct nhcoord,y)),
MONMOVE_META(coord_y_size,sizeof(((struct nhcoord*)0)->y)),
MONMOVE_META(propSize,sizeof(struct prop)),
MONMOVE_META(prop_blocked,offsetof(struct prop,blocked)),
MONMOVE_META(prop_blocked_size,sizeof(((struct prop*)0)->blocked)),
MONMOVE_META(prop_extrinsic,offsetof(struct prop,extrinsic)),
MONMOVE_META(prop_extrinsic_size,sizeof(((struct prop*)0)->extrinsic)),
MONMOVE_META(prop_intrinsic,offsetof(struct prop,intrinsic)),
MONMOVE_META(prop_intrinsic_size,sizeof(((struct prop*)0)->intrinsic)),
MONMOVE_META(mfpSize,sizeof(struct mfndposdata)),
MONMOVE_META(mfp_cnt,offsetof(struct mfndposdata,cnt)),
MONMOVE_META(mfp_cnt_size,sizeof(((struct mfndposdata*)0)->cnt)),
MONMOVE_META(mfp_info,offsetof(struct mfndposdata,info)),
MONMOVE_META(mfp_info_size,sizeof(((struct mfndposdata*)0)->info)),
MONMOVE_META(mfp_poss,offsetof(struct mfndposdata,poss)),
MONMOVE_META(mfp_poss_size,sizeof(((struct mfndposdata*)0)->poss)),
MONMOVE_META(a11ySize,sizeof(struct accessibility_data)),
MONMOVE_META(a11y_mon_movement,offsetof(struct accessibility_data,mon_movement)),
MONMOVE_META(a11y_mon_movement_size,sizeof(((struct accessibility_data*)0)->mon_movement)),
MONMOVE_META(contextSize,sizeof(struct context_info)),
MONMOVE_META(context_achieveo,offsetof(struct context_info,achieveo)),
MONMOVE_META(context_achieveo_size,sizeof(((struct context_info*)0)->achieveo)),
MONMOVE_META(context_digging,offsetof(struct context_info,digging)),
MONMOVE_META(context_digging_size,sizeof(((struct context_info*)0)->digging)),
MONMOVE_META(diggingSize,sizeof(struct dig_info)),
MONMOVE_META(digging_pos,offsetof(struct dig_info,pos)),
MONMOVE_META(digging_pos_size,sizeof(((struct dig_info*)0)->pos)),
MONMOVE_META(achieveSize,sizeof(struct achievement_tracking)),
MONMOVE_META(achieve_mines_prize_oid,offsetof(struct achievement_tracking,mines_prize_oid)),
MONMOVE_META(achieve_mines_prize_oid_size,sizeof(((struct achievement_tracking*)0)->mines_prize_oid)),
MONMOVE_META(achieve_soko_prize_oid,offsetof(struct achievement_tracking,soko_prize_oid)),
MONMOVE_META(achieve_soko_prize_oid_size,sizeof(((struct achievement_tracking*)0)->soko_prize_oid)),
MONMOVE_META(rmSize,sizeof(struct rm)),
MONMOVE_META(rm_typ,offsetof(struct rm,typ)),
MONMOVE_META(rm_typ_size,sizeof(((struct rm*)0)->typ)),
MONMOVE_META(clsSize,sizeof(struct objclass)),
MONMOVE_META(cls_oc_skill,offsetof(struct objclass,oc_skill)),
MONMOVE_META(cls_oc_skill_size,sizeof(((struct objclass*)0)->oc_skill)),
MONMOVE_META(cls_oc_subtyp,offsetof(struct objclass,oc_subtyp)),
MONMOVE_META(cls_oc_subtyp_size,sizeof(((struct objclass*)0)->oc_subtyp)),
MONMOVE_META(trapSize,sizeof(struct trap)),
MONMOVE_META(edogSize,sizeof(struct edog)),
MONMOVE_META(edog_hungrytime,offsetof(struct edog,hungrytime)),
MONMOVE_META(edog_hungrytime_size,sizeof(((struct edog*)0)->hungrytime)),
MONMOVE_META(mextraSize,sizeof(struct mextra)),
MONMOVE_META(mextra_edog,offsetof(struct mextra,edog)),
MONMOVE_META(mextra_edog_size,sizeof(((struct mextra*)0)->edog)),
MONMOVE_META(engrSize,sizeof(struct engr)),
MONMOVE_META(stairSize,sizeof(struct stairway)),
MONMOVE_META(stair_sx,offsetof(struct stairway,sx)),
MONMOVE_META(stair_sx_size,sizeof(((struct stairway*)0)->sx)),
MONMOVE_META(stair_sy,offsetof(struct stairway,sy)),
MONMOVE_META(stair_sy_size,sizeof(((struct stairway*)0)->sy)),
MONMOVE_META(stair_up,offsetof(struct stairway,up)),
MONMOVE_META(stair_up_size,sizeof(((struct stairway*)0)->up)),
MONMOVE_META(arwSize,sizeof(struct throw_and_return_weapon)),
MONMOVE_META(arw_range,offsetof(struct throw_and_return_weapon,range)),
MONMOVE_META(arw_range_size,sizeof(((struct throw_and_return_weapon*)0)->range)),
MONMOVE_META(genderSize,sizeof(struct Gender)),
MONMOVE_META(gender_his,offsetof(struct Gender,his)),
MONMOVE_META(gender_his_size,sizeof(((struct Gender*)0)->his)),
MONMOVE_META(vitalSize,sizeof(struct mvitals)),
MONMOVE_META(vital_mvflags,offsetof(struct mvitals,mvflags)),
MONMOVE_META(vital_mvflags_size,sizeof(((struct mvitals*)0)->mvflags)),
MONMOVE_META(flagsSize,sizeof(struct flag)),
MONMOVE_META(flags_verbose,offsetof(struct flag,verbose)),
MONMOVE_META(flags_verbose_size,sizeof(((struct flag*)0)->verbose)),
MONMOVE_META(levelFlagsSize,sizeof(struct levelflags)),
MONMOVE_META(svmSize,sizeof(struct instance_globals_saved_m)),
MONMOVE_META(svm_moves,offsetof(struct instance_globals_saved_m,moves)),
MONMOVE_META(svm_moves_size,sizeof(((struct instance_globals_saved_m*)0)->moves)),
MONMOVE_META(svm_mvitals,offsetof(struct instance_globals_saved_m,mvitals)),
MONMOVE_META(svm_mvitals_size,sizeof(((struct instance_globals_saved_m*)0)->mvitals)),
MONMOVE_META(svlSize,sizeof(struct instance_globals_saved_l)),
MONMOVE_META(svl_level,offsetof(struct instance_globals_saved_l,level)),
MONMOVE_META(svl_level_size,sizeof(((struct instance_globals_saved_l*)0)->level)),
MONMOVE_META(svcSize,sizeof(struct instance_globals_saved_c)),
MONMOVE_META(svc_context,offsetof(struct instance_globals_saved_c,context)),
MONMOVE_META(svc_context_size,sizeof(((struct instance_globals_saved_c*)0)->context)),
MONMOVE_META(svdSize,sizeof(struct instance_globals_saved_d)),
MONMOVE_META(svd_dungeon_topology,offsetof(struct instance_globals_saved_d,dungeon_topology)),
MONMOVE_META(svd_dungeon_topology_size,sizeof(((struct instance_globals_saved_d*)0)->dungeon_topology)),
MONMOVE_META(topologySize,sizeof(struct dgn_topology)),
MONMOVE_META(topology_d_astral_level,offsetof(struct dgn_topology,d_astral_level)),
MONMOVE_META(topology_d_astral_level_size,sizeof(((struct dgn_topology*)0)->d_astral_level)),
MONMOVE_META(topology_d_rogue_level,offsetof(struct dgn_topology,d_rogue_level)),
MONMOVE_META(topology_d_rogue_level_size,sizeof(((struct dgn_topology*)0)->d_rogue_level)),
MONMOVE_META(gmSize,sizeof(struct instance_globals_m)),
MONMOVE_META(gm_multi,offsetof(struct instance_globals_m,multi)),
MONMOVE_META(gm_multi_size,sizeof(((struct instance_globals_m*)0)->multi)),
MONMOVE_META(goSize,sizeof(struct instance_globals_o)),
MONMOVE_META(go_occupation,offsetof(struct instance_globals_o,occupation)),
MONMOVE_META(go_occupation_size,sizeof(((struct instance_globals_o*)0)->occupation)),
MONMOVE_META(gnSize,sizeof(struct instance_globals_n)),
MONMOVE_META(gn_notonhead,offsetof(struct instance_globals_n,notonhead)),
MONMOVE_META(gn_notonhead_size,sizeof(((struct instance_globals_n*)0)->notonhead)),
MONMOVE_META(gvSize,sizeof(struct instance_globals_v)),
MONMOVE_META(gv_viz_array,offsetof(struct instance_globals_v,viz_array)),
MONMOVE_META(gv_viz_array_size,sizeof(((struct instance_globals_v*)0)->viz_array)),
MONMOVE_META(gySize,sizeof(struct instance_globals_y)),
MONMOVE_META(gy_youmonst,offsetof(struct instance_globals_y,youmonst)),
MONMOVE_META(gy_youmonst_size,sizeof(((struct instance_globals_y*)0)->youmonst)),
MONMOVE_META(giSize,sizeof(struct instance_globals_i)),
MONMOVE_META(gi_invent,offsetof(struct instance_globals_i,invent)),
MONMOVE_META(gi_invent_size,sizeof(((struct instance_globals_i*)0)->invent)),
MONMOVE_META(gkSize,sizeof(struct instance_globals_k)),
MONMOVE_META(gk_kickedloc,offsetof(struct instance_globals_k,kickedloc)),
MONMOVE_META(gk_kickedloc_size,sizeof(((struct instance_globals_k*)0)->kickedloc)),
MONMOVE_META(gbSize,sizeof(struct instance_globals_b)),
MONMOVE_META(gb_bhitpos,offsetof(struct instance_globals_b,bhitpos)),
MONMOVE_META(gb_bhitpos_size,sizeof(((struct instance_globals_b*)0)->bhitpos)),
MONMOVE_META(roleplaySize,sizeof(struct u_roleplay)),
MONMOVE_META(roleplay_deaf,offsetof(struct u_roleplay,deaf)),
MONMOVE_META(roleplay_deaf_size,sizeof(((struct u_roleplay*)0)->deaf)),
MONMOVE_META(dlevelSize,sizeof(__typeof__(svl.level))),
MONMOVE_META(dlevel_flags,offsetof(__typeof__(svl.level),flags)),
MONMOVE_META(dlevel_flags_size,sizeof(((__typeof__(svl.level)*)0)->flags)),
MONMOVE_META(dlevel_locations,offsetof(__typeof__(svl.level),locations)),
MONMOVE_META(dlevel_locations_size,sizeof(((__typeof__(svl.level)*)0)->locations)),
MONMOVE_META(dlevel_monlist,offsetof(__typeof__(svl.level),monlist)),
MONMOVE_META(dlevel_monlist_size,sizeof(((__typeof__(svl.level)*)0)->monlist)),
MONMOVE_META(dlevel_monsters,offsetof(__typeof__(svl.level),monsters)),
MONMOVE_META(dlevel_monsters_size,sizeof(((__typeof__(svl.level)*)0)->monsters)),
MONMOVE_META(dlevel_objects,offsetof(__typeof__(svl.level),objects)),
MONMOVE_META(dlevel_objects_size,sizeof(((__typeof__(svl.level)*)0)->objects)),
MONMOVE_META(ACCFOOD,ACCFOOD),
MONMOVE_META(AD_CLRC,AD_CLRC),
MONMOVE_META(AD_CORR,AD_CORR),
MONMOVE_META(AD_DRIN,AD_DRIN),
MONMOVE_META(AD_RUST,AD_RUST),
MONMOVE_META(AD_SPEL,AD_SPEL),
MONMOVE_META(AGGRAVATE_MONSTER,AGGRAVATE_MONSTER),
MONMOVE_META(ALLOW_M,ALLOW_M),
MONMOVE_META(ALLOW_MDISP,ALLOW_MDISP),
MONMOVE_META(ALLOW_ROCK,ALLOW_ROCK),
MONMOVE_META(ALLOW_U,ALLOW_U),
MONMOVE_META(ALTAR,ALTAR),
MONMOVE_META(AMULET_CLASS,AMULET_CLASS),
MONMOVE_META(ARM,ARM),
MONMOVE_META(ARMOR_CLASS,ARMOR_CLASS),
MONMOVE_META(ARM_CLOAK,ARM_CLOAK),
MONMOVE_META(ARM_GLOVES,ARM_GLOVES),
MONMOVE_META(ARM_SHIRT,ARM_SHIRT),
MONMOVE_META(ARROW,ARROW),
MONMOVE_META(ART_SNICKERSNEE,ART_SNICKERSNEE),
MONMOVE_META(AT_MAGC,AT_MAGC),
MONMOVE_META(AT_WEAP,AT_WEAP),
MONMOVE_META(A_LAWFUL,A_LAWFUL),
MONMOVE_META(BAG_OF_HOLDING,BAG_OF_HOLDING),
MONMOVE_META(BAG_OF_TRICKS,BAG_OF_TRICKS),
MONMOVE_META(BALL_CLASS,BALL_CLASS),
MONMOVE_META(BLINDED,BLINDED),
MONMOVE_META(BLINDFOLD,BLINDFOLD),
MONMOVE_META(BOLT_LIM,BOLT_LIM),
MONMOVE_META(BOOMERANG,BOOMERANG),
MONMOVE_META(BOULDER,BOULDER),
MONMOVE_META(BUFSZ,BUFSZ),
MONMOVE_META(CANDY_BAR,CANDY_BAR),
MONMOVE_META(COIN_CLASS,COIN_CLASS),
MONMOVE_META(COLNO,COLNO),
MONMOVE_META(CONFLICT,CONFLICT),
MONMOVE_META(CORPSE,CORPSE),
MONMOVE_META(CORR,CORR),
MONMOVE_META(COULD_SEE,COULD_SEE),
MONMOVE_META(CREDIT_CARD,CREDIT_CARD),
MONMOVE_META(CRYSKNIFE,CRYSKNIFE),
MONMOVE_META(DAGGER,DAGGER),
MONMOVE_META(DBWALL,DBWALL),
MONMOVE_META(DEAF,DEAF),
MONMOVE_META(DIR_ERR,DIR_ERR),
MONMOVE_META(DISPLACED,DISPLACED),
MONMOVE_META(DOOR,DOOR),
MONMOVE_META(DRAWBRIDGE_UP,DRAWBRIDGE_UP),
MONMOVE_META(D_BROKEN,D_BROKEN),
MONMOVE_META(D_CLOSED,D_CLOSED),
MONMOVE_META(D_ISOPEN,D_ISOPEN),
MONMOVE_META(D_LOCKED,D_LOCKED),
MONMOVE_META(D_NODOOR,D_NODOOR),
MONMOVE_META(D_TRAPPED,D_TRAPPED),
MONMOVE_META(D_WARNED,D_WARNED),
MONMOVE_META(FEDORA,FEDORA),
MONMOVE_META(FLYING,FLYING),
MONMOVE_META(FOOD_CLASS,FOOD_CLASS),
MONMOVE_META(FORTUNE_COOKIE,FORTUNE_COOKIE),
MONMOVE_META(FOUNTAIN,FOUNTAIN),
MONMOVE_META(GEMSTONE,GEMSTONE),
MONMOVE_META(GEM_CLASS,GEM_CLASS),
MONMOVE_META(GOLD_PIECE,GOLD_PIECE),
MONMOVE_META(GRAVE,GRAVE),
MONMOVE_META(G_GENOD,G_GENOD),
MONMOVE_META(G_UNIQ,G_UNIQ),
MONMOVE_META(HALF_SPDAM,HALF_SPDAM),
MONMOVE_META(HALLUC,HALLUC),
MONMOVE_META(HALLUC_RES,HALLUC_RES),
MONMOVE_META(HEAD,HEAD),
MONMOVE_META(INVIS,INVIS),
MONMOVE_META(IN_SIGHT,IN_SIGHT),
MONMOVE_META(IRONBARS,IRONBARS),
MONMOVE_META(I_SPECIAL,I_SPECIAL),
MONMOVE_META(KILLED_BY_AN,KILLED_BY_AN),
MONMOVE_META(LADDER,LADDER),
MONMOVE_META(LARGE_BOX,LARGE_BOX),
MONMOVE_META(LAST_PROP,LAST_PROP),
MONMOVE_META(LAVAPOOL,LAVAPOOL),
MONMOVE_META(LEASH,LEASH),
MONMOVE_META(LEATHER_JACKET,LEATHER_JACKET),
MONMOVE_META(LEMBAS_WAFER,LEMBAS_WAFER),
MONMOVE_META(LEVITATION,LEVITATION),
MONMOVE_META(LOCK_PICK,LOCK_PICK),
MONMOVE_META(LONG_SWORD,LONG_SWORD),
MONMOVE_META(LUMP_OF_ROYAL_JELLY,LUMP_OF_ROYAL_JELLY),
MONMOVE_META(M1_AMORPHOUS,M1_AMORPHOUS),
MONMOVE_META(M1_ANIMAL,M1_ANIMAL),
MONMOVE_META(M1_CLING,M1_CLING),
MONMOVE_META(M1_CONCEAL,M1_CONCEAL),
MONMOVE_META(M1_FLY,M1_FLY),
MONMOVE_META(M1_METALLIVORE,M1_METALLIVORE),
MONMOVE_META(M1_MINDLESS,M1_MINDLESS),
MONMOVE_META(M1_NEEDPICK,M1_NEEDPICK),
MONMOVE_META(M1_NOHANDS,M1_NOHANDS),
MONMOVE_META(M1_NOLIMBS,M1_NOLIMBS),
MONMOVE_META(M1_REGEN,M1_REGEN),
MONMOVE_META(M1_SEE_INVIS,M1_SEE_INVIS),
MONMOVE_META(M1_TPORT,M1_TPORT),
MONMOVE_META(M1_TUNNEL,M1_TUNNEL),
MONMOVE_META(M1_UNSOLID,M1_UNSOLID),
MONMOVE_META(M1_WALLWALK,M1_WALLWALK),
MONMOVE_META(M2_COLLECT,M2_COLLECT),
MONMOVE_META(M2_DEMON,M2_DEMON),
MONMOVE_META(M2_GREEDY,M2_GREEDY),
MONMOVE_META(M2_JEWELS,M2_JEWELS),
MONMOVE_META(M2_MAGIC,M2_MAGIC),
MONMOVE_META(M2_MERC,M2_MERC),
MONMOVE_META(M2_MINION,M2_MINION),
MONMOVE_META(M2_ROCKTHROW,M2_ROCKTHROW),
MONMOVE_META(M2_WANDER,M2_WANDER),
MONMOVE_META(M3_COVETOUS,M3_COVETOUS),
MONMOVE_META(M3_INFRAVISIBLE,M3_INFRAVISIBLE),
MONMOVE_META(M3_INFRAVISION,M3_INFRAVISION),
MONMOVE_META(MAGIC_MARKER,MAGIC_MARKER),
MONMOVE_META(MAGIC_WHISTLE,MAGIC_WHISTLE),
MONMOVE_META(MANFOOD,MANFOOD),
MONMOVE_META(MINERAL,MINERAL),
MONMOVE_META(MMOVE_DIED,MMOVE_DIED),
MONMOVE_META(MMOVE_DONE,MMOVE_DONE),
MONMOVE_META(MMOVE_MOVED,MMOVE_MOVED),
MONMOVE_META(MMOVE_NOMOVES,MMOVE_NOMOVES),
MONMOVE_META(MMOVE_NOTHING,MMOVE_NOTHING),
MONMOVE_META(MOAT,MOAT),
MONMOVE_META(MON_FLOOR,MON_FLOOR),
MONMOVE_META(MON_MIGRATING,MON_MIGRATING),
MONMOVE_META(MS_BRIBE,MS_BRIBE),
MONMOVE_META(MS_CUSS,MS_CUSS),
MONMOVE_META(MS_LEADER,MS_LEADER),
MONMOVE_META(MTSZ,MTSZ),
MONMOVE_META(MZ_SMALL,MZ_SMALL),
MONMOVE_META(M_AP_FURNITURE,M_AP_FURNITURE),
MONMOVE_META(M_AP_MONSTER,M_AP_MONSTER),
MONMOVE_META(M_AP_NOTHING,M_AP_NOTHING),
MONMOVE_META(M_AP_OBJECT,M_AP_OBJECT),
MONMOVE_META(M_AP_TYPMASK,M_AP_TYPMASK),
MONMOVE_META(M_ATTK_AGR_DIED,M_ATTK_AGR_DIED),
MONMOVE_META(M_ATTK_DEF_DIED,M_ATTK_DEF_DIED),
MONMOVE_META(M_ATTK_HIT,M_ATTK_HIT),
MONMOVE_META(NATTK,NATTK),
MONMOVE_META(NC_SHOW_MSG,NC_SHOW_MSG),
MONMOVE_META(NEED_AXE,NEED_AXE),
MONMOVE_META(NEED_HTH_WEAPON,NEED_HTH_WEAPON),
MONMOVE_META(NEED_PICK_AXE,NEED_PICK_AXE),
MONMOVE_META(NEED_PICK_OR_AXE,NEED_PICK_OR_AXE),
MONMOVE_META(NEED_WEAPON,NEED_WEAPON),
MONMOVE_META(NON_PM,NON_PM),
MONMOVE_META(NORMAL_SPEED,NORMAL_SPEED),
MONMOVE_META(NOTONL,NOTONL),
MONMOVE_META(NO_NC_FLAGS,NO_NC_FLAGS),
MONMOVE_META(NO_TRAP_FLAGS,NO_TRAP_FLAGS),
MONMOVE_META(NUMMONS,NUMMONS),
MONMOVE_META(NUM_OBJECTS,NUM_OBJECTS),
MONMOVE_META(N_DIRS,N_DIRS),
MONMOVE_META(OBJ_FLOOR,OBJ_FLOOR),
MONMOVE_META(OBJ_FREE,OBJ_FREE),
MONMOVE_META(OBJ_INVENT,OBJ_INVENT),
MONMOVE_META(OBJ_MINVENT,OBJ_MINVENT),
MONMOVE_META(OILSKIN_SACK,OILSKIN_SACK),
MONMOVE_META(PANCAKE,PANCAKE),
MONMOVE_META(PIT,PIT),
MONMOVE_META(PM_ALIGNED_CLERIC,PM_ALIGNED_CLERIC),
MONMOVE_META(PM_ANGEL,PM_ANGEL),
MONMOVE_META(PM_BABY_PURPLE_WORM,PM_BABY_PURPLE_WORM),
MONMOVE_META(PM_CAVE_SPIDER,PM_CAVE_SPIDER),
MONMOVE_META(PM_CHICKATRICE,PM_CHICKATRICE),
MONMOVE_META(PM_COCKATRICE,PM_COCKATRICE),
MONMOVE_META(PM_DEATH,PM_DEATH),
MONMOVE_META(PM_DISPLACER_BEAST,PM_DISPLACER_BEAST),
MONMOVE_META(PM_DOG,PM_DOG),
MONMOVE_META(PM_ETTIN,PM_ETTIN),
MONMOVE_META(PM_FAMINE,PM_FAMINE),
MONMOVE_META(PM_FLOATING_EYE,PM_FLOATING_EYE),
MONMOVE_META(PM_FOG_CLOUD,PM_FOG_CLOUD),
MONMOVE_META(PM_GELATINOUS_CUBE,PM_GELATINOUS_CUBE),
MONMOVE_META(PM_GHOST,PM_GHOST),
MONMOVE_META(PM_GHOUL,PM_GHOUL),
MONMOVE_META(PM_GIANT_BAT,PM_GIANT_BAT),
MONMOVE_META(PM_GIANT_SPIDER,PM_GIANT_SPIDER),
MONMOVE_META(PM_GREMLIN,PM_GREMLIN),
MONMOVE_META(PM_HEZROU,PM_HEZROU),
MONMOVE_META(PM_HUMAN,PM_HUMAN),
MONMOVE_META(PM_JABBERWOCK,PM_JABBERWOCK),
MONMOVE_META(PM_KILLER_BEE,PM_KILLER_BEE),
MONMOVE_META(PM_LEPRECHAUN,PM_LEPRECHAUN),
MONMOVE_META(PM_LICH,PM_LICH),
MONMOVE_META(PM_LONG_WORM,PM_LONG_WORM),
MONMOVE_META(PM_MAIL_DAEMON,PM_MAIL_DAEMON),
MONMOVE_META(PM_MASTER_MIND_FLAYER,PM_MASTER_MIND_FLAYER),
MONMOVE_META(PM_MIND_FLAYER,PM_MIND_FLAYER),
MONMOVE_META(PM_MINOTAUR,PM_MINOTAUR),
MONMOVE_META(PM_PESTILENCE,PM_PESTILENCE),
MONMOVE_META(PM_PIRANHA,PM_PIRANHA),
MONMOVE_META(PM_PURPLE_WORM,PM_PURPLE_WORM),
MONMOVE_META(PM_QUEEN_BEE,PM_QUEEN_BEE),
MONMOVE_META(PM_RED_DRAGON,PM_RED_DRAGON),
MONMOVE_META(PM_SHOPKEEPER,PM_SHOPKEEPER),
MONMOVE_META(PM_SMALL_MIMIC,PM_SMALL_MIMIC),
MONMOVE_META(PM_STALKER,PM_STALKER),
MONMOVE_META(PM_STEAM_VORTEX,PM_STEAM_VORTEX),
MONMOVE_META(PM_STONE_GOLEM,PM_STONE_GOLEM),
MONMOVE_META(PM_TENGU,PM_TENGU),
MONMOVE_META(PM_VAMPIRE,PM_VAMPIRE),
MONMOVE_META(PM_VAMPIRE_LEADER,PM_VAMPIRE_LEADER),
MONMOVE_META(PM_VLAD_THE_IMPALER,PM_VLAD_THE_IMPALER),
MONMOVE_META(PM_VROCK,PM_VROCK),
MONMOVE_META(PM_WATCHMAN,PM_WATCHMAN),
MONMOVE_META(PM_WATCH_CAPTAIN,PM_WATCH_CAPTAIN),
MONMOVE_META(PM_WHITE_UNICORN,PM_WHITE_UNICORN),
MONMOVE_META(PM_XORN,PM_XORN),
MONMOVE_META(POOL,POOL),
MONMOVE_META(POTION_CLASS,POTION_CLASS),
MONMOVE_META(POT_HEALING,POT_HEALING),
MONMOVE_META(PRONOUN_HALLU,PRONOUN_HALLU),
MONMOVE_META(PROT_FROM_SHAPE_CHANGERS,PROT_FROM_SHAPE_CHANGERS),
MONMOVE_META(P_AXE,P_AXE),
MONMOVE_META(P_LANCE,P_LANCE),
MONMOVE_META(P_PICK_AXE,P_PICK_AXE),
MONMOVE_META(P_POLEARMS,P_POLEARMS),
MONMOVE_META(RING_CLASS,RING_CLASS),
MONMOVE_META(RLOC_MSG,RLOC_MSG),
MONMOVE_META(ROCK,ROCK),
MONMOVE_META(ROCK_CLASS,ROCK_CLASS),
MONMOVE_META(ROOM,ROOM),
MONMOVE_META(ROWNO,ROWNO),
MONMOVE_META(SACK,SACK),
MONMOVE_META(SCORR,SCORR),
MONMOVE_META(SCROLL_CLASS,SCROLL_CLASS),
MONMOVE_META(SCR_IDENTIFY,SCR_IDENTIFY),
MONMOVE_META(SCR_SCARE_MONSTER,SCR_SCARE_MONSTER),
MONMOVE_META(SDOOR,SDOOR),
MONMOVE_META(SHOPBASE,SHOPBASE),
MONMOVE_META(SINK,SINK),
MONMOVE_META(SKELETON_KEY,SKELETON_KEY),
MONMOVE_META(SLING,SLING),
MONMOVE_META(SPBOOK_CLASS,SPBOOK_CLASS),
MONMOVE_META(SPIKED_PIT,SPIKED_PIT),
MONMOVE_META(STAIRS,STAIRS),
MONMOVE_META(STEALTH,STEALTH),
MONMOVE_META(STETHOSCOPE,STETHOSCOPE),
MONMOVE_META(STONE,STONE),
MONMOVE_META(STRANGE_OBJECT,STRANGE_OBJECT),
MONMOVE_META(STRAT_ARRIVE,STRAT_ARRIVE),
MONMOVE_META(STRAT_CLOSE,STRAT_CLOSE),
MONMOVE_META(STRAT_WAITFORU,STRAT_WAITFORU),
MONMOVE_META(STRAT_WAITMASK,STRAT_WAITMASK),
MONMOVE_META(S_BAT,S_BAT),
MONMOVE_META(S_DOG,S_DOG),
MONMOVE_META(S_EEL,S_EEL),
MONMOVE_META(S_EYE,S_EYE),
MONMOVE_META(S_HUMAN,S_HUMAN),
MONMOVE_META(S_LEPRECHAUN,S_LEPRECHAUN),
MONMOVE_META(S_LIGHT,S_LIGHT),
MONMOVE_META(S_NYMPH,S_NYMPH),
MONMOVE_META(S_UNICORN,S_UNICORN),
MONMOVE_META(S_VAMPIRE,S_VAMPIRE),
MONMOVE_META(TALLOW_CANDLE,TALLOW_CANDLE),
MONMOVE_META(TELEPAT,TELEPAT),
MONMOVE_META(THRONE,THRONE),
MONMOVE_META(TIMEOUT,TIMEOUT),
MONMOVE_META(TIN_OPENER,TIN_OPENER),
MONMOVE_META(TIN_WHISTLE,TIN_WHISTLE),
MONMOVE_META(TOOL_CLASS,TOOL_CLASS),
MONMOVE_META(TOWEL,TOWEL),
MONMOVE_META(TRAPPED_DOOR,TRAPPED_DOOR),
MONMOVE_META(TREE,TREE),
MONMOVE_META(Trap_Caught_Mon,Trap_Caught_Mon),
MONMOVE_META(Trap_Killed_Mon,Trap_Killed_Mon),
MONMOVE_META(Trap_Moved_Mon,Trap_Moved_Mon),
MONMOVE_META(VENOM_CLASS,VENOM_CLASS),
MONMOVE_META(WAND_CLASS,WAND_CLASS),
MONMOVE_META(WATER,WATER),
MONMOVE_META(WAX_CANDLE,WAX_CANDLE),
MONMOVE_META(WEAPON_CLASS,WEAPON_CLASS),
MONMOVE_META(WEB,WEB),
MONMOVE_META(WOOD,WOOD),
MONMOVE_META(W_NONDIGGABLE,W_NONDIGGABLE),
MONMOVE_META(MON_POLE_DIST,MON_POLE_DIST),
};
_Static_assert(sizeof(void*)==8&&sizeof(int)==4&&sizeof(long)==8&&sizeof(coordxy)==2&&sizeof(boolean)==1,"MONMOVE configured ABI");
_Static_assert(sizeof(((struct obj*)0)->cobj)==8,"obj_cobj pointer width");
_Static_assert(sizeof(((struct obj*)0)->corpsenm)==4,"obj_corpsenm width");
_Static_assert(((__typeof__(((struct obj*)0)->corpsenm))-1 < 0),"obj_corpsenm signedness");
_Static_assert(sizeof(((struct obj*)0)->nexthere)==8,"obj_nexthere pointer width");
_Static_assert(sizeof(((struct obj*)0)->nobj)==8,"obj_nobj pointer width");
_Static_assert(sizeof(((struct obj*)0)->o_id)==4,"obj_o_id width");
_Static_assert(((__typeof__(((struct obj*)0)->o_id))-1 > 0),"obj_o_id signedness");
_Static_assert(sizeof(((struct obj*)0)->oartifact)==1,"obj_oartifact width");
_Static_assert(((__typeof__(((struct obj*)0)->oartifact))-1 < 0),"obj_oartifact signedness");
_Static_assert(sizeof(((struct obj*)0)->oclass)==1,"obj_oclass width");
_Static_assert(((__typeof__(((struct obj*)0)->oclass))-1 < 0),"obj_oclass signedness");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2,"obj_otyp width");
_Static_assert(((__typeof__(((struct obj*)0)->otyp))-1 < 0),"obj_otyp signedness");
_Static_assert(sizeof(((struct obj*)0)->ox)==2,"obj_ox width");
_Static_assert(((__typeof__(((struct obj*)0)->ox))-1 < 0),"obj_ox signedness");
_Static_assert(sizeof(((struct obj*)0)->oy)==2,"obj_oy width");
_Static_assert(((__typeof__(((struct obj*)0)->oy))-1 < 0),"obj_oy signedness");
_Static_assert(sizeof(((struct obj*)0)->quan)==8,"obj_quan width");
_Static_assert(((__typeof__(((struct obj*)0)->quan))-1 < 0),"obj_quan signedness");
_Static_assert(sizeof(((struct obj*)0)->where)==1,"obj_where width");
_Static_assert(((__typeof__(((struct obj*)0)->where))-1 < 0),"obj_where signedness");
_Static_assert(sizeof(((struct monst*)0)->cham)==2,"mon_cham width");
_Static_assert(((__typeof__(((struct monst*)0)->cham))-1 < 0),"mon_cham signedness");
_Static_assert(sizeof(((struct monst*)0)->data)==8,"mon_data pointer width");
_Static_assert(sizeof(((struct monst*)0)->m_ap_type)==1,"mon_m_ap_type width");
_Static_assert(((__typeof__(((struct monst*)0)->m_ap_type))-1 > 0),"mon_m_ap_type signedness");
_Static_assert(sizeof(((struct monst*)0)->m_lev)==1,"mon_m_lev width");
_Static_assert(((__typeof__(((struct monst*)0)->m_lev))-1 > 0),"mon_m_lev signedness");
_Static_assert(sizeof(((struct monst*)0)->mappearance)==4,"mon_mappearance width");
_Static_assert(((__typeof__(((struct monst*)0)->mappearance))-1 > 0),"mon_mappearance signedness");
_Static_assert(sizeof(((struct monst*)0)->meating)==4,"mon_meating width");
_Static_assert(((__typeof__(((struct monst*)0)->meating))-1 < 0),"mon_meating signedness");
_Static_assert(sizeof(((struct monst*)0)->mextra)==8,"mon_mextra pointer width");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4,"mon_mhp width");
_Static_assert(((__typeof__(((struct monst*)0)->mhp))-1 < 0),"mon_mhp signedness");
_Static_assert(sizeof(((struct monst*)0)->mhpmax)==4,"mon_mhpmax width");
_Static_assert(((__typeof__(((struct monst*)0)->mhpmax))-1 < 0),"mon_mhpmax signedness");
_Static_assert(sizeof(((struct monst*)0)->minvent)==8,"mon_minvent pointer width");
_Static_assert(sizeof(((struct monst*)0)->movement)==2,"mon_movement width");
_Static_assert(((__typeof__(((struct monst*)0)->movement))-1 < 0),"mon_movement signedness");
_Static_assert(sizeof(((struct monst*)0)->mspec_used)==4,"mon_mspec_used width");
_Static_assert(((__typeof__(((struct monst*)0)->mspec_used))-1 < 0),"mon_mspec_used signedness");
_Static_assert(sizeof(((struct monst*)0)->mstate)==8,"mon_mstate width");
_Static_assert(((__typeof__(((struct monst*)0)->mstate))-1 < 0),"mon_mstate signedness");
_Static_assert(sizeof(((struct monst*)0)->mstrategy)==8,"mon_mstrategy width");
_Static_assert(((__typeof__(((struct monst*)0)->mstrategy))-1 > 0),"mon_mstrategy signedness");
_Static_assert(sizeof(((struct monst*)0)->mtame)==1,"mon_mtame width");
_Static_assert(((__typeof__(((struct monst*)0)->mtame))-1 < 0),"mon_mtame signedness");
_Static_assert(sizeof(((struct monst*)0)->mux)==2,"mon_mux width");
_Static_assert(((__typeof__(((struct monst*)0)->mux))-1 < 0),"mon_mux signedness");
_Static_assert(sizeof(((struct monst*)0)->muy)==2,"mon_muy width");
_Static_assert(((__typeof__(((struct monst*)0)->muy))-1 < 0),"mon_muy signedness");
_Static_assert(sizeof(((struct monst*)0)->mw)==8,"mon_mw pointer width");
_Static_assert(sizeof(((struct monst*)0)->mx)==2,"mon_mx width");
_Static_assert(((__typeof__(((struct monst*)0)->mx))-1 < 0),"mon_mx signedness");
_Static_assert(sizeof(((struct monst*)0)->my)==2,"mon_my width");
_Static_assert(((__typeof__(((struct monst*)0)->my))-1 < 0),"mon_my signedness");
_Static_assert(sizeof(((struct monst*)0)->nmon)==8,"mon_nmon pointer width");
_Static_assert(sizeof(((struct monst*)0)->weapon_check)==2,"mon_weapon_check width");
_Static_assert(((__typeof__(((struct monst*)0)->weapon_check))-1 < 0),"mon_weapon_check signedness");
_Static_assert(sizeof(((struct permonst*)0)->geno)==2,"pm_geno width");
_Static_assert(((__typeof__(((struct permonst*)0)->geno))-1 > 0),"pm_geno signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8,"pm_mflags1 width");
_Static_assert(((__typeof__(((struct permonst*)0)->mflags1))-1 > 0),"pm_mflags1 signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8,"pm_mflags2 width");
_Static_assert(((__typeof__(((struct permonst*)0)->mflags2))-1 > 0),"pm_mflags2 signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags3)==2,"pm_mflags3 width");
_Static_assert(((__typeof__(((struct permonst*)0)->mflags3))-1 > 0),"pm_mflags3 signedness");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1,"pm_mlet width");
_Static_assert(((__typeof__(((struct permonst*)0)->mlet))-1 < 0),"pm_mlet signedness");
_Static_assert(sizeof(((struct permonst*)0)->mlevel)==1,"pm_mlevel width");
_Static_assert(((__typeof__(((struct permonst*)0)->mlevel))-1 < 0),"pm_mlevel signedness");
_Static_assert(sizeof(((struct permonst*)0)->mmove)==1,"pm_mmove width");
_Static_assert(((__typeof__(((struct permonst*)0)->mmove))-1 < 0),"pm_mmove signedness");
_Static_assert(sizeof(((struct permonst*)0)->msize)==1,"pm_msize width");
_Static_assert(((__typeof__(((struct permonst*)0)->msize))-1 > 0),"pm_msize signedness");
_Static_assert(sizeof(((struct permonst*)0)->msound)==1,"pm_msound width");
_Static_assert(((__typeof__(((struct permonst*)0)->msound))-1 > 0),"pm_msound signedness");
_Static_assert(sizeof(((struct permonst*)0)->pmidx)==4,"pm_pmidx width");
_Static_assert(((__typeof__(((struct permonst*)0)->pmidx))-1 < 0),"pm_pmidx signedness");
_Static_assert(sizeof(((struct attack*)0)->aatyp)==1,"attack_aatyp width");
_Static_assert(((__typeof__(((struct attack*)0)->aatyp))-1 > 0),"attack_aatyp signedness");
_Static_assert(sizeof(((struct attack*)0)->adtyp)==1,"attack_adtyp width");
_Static_assert(((__typeof__(((struct attack*)0)->adtyp))-1 > 0),"attack_adtyp signedness");
_Static_assert(sizeof(((struct attack*)0)->damd)==1,"attack_damd width");
_Static_assert(((__typeof__(((struct attack*)0)->damd))-1 > 0),"attack_damd signedness");
_Static_assert(sizeof(((struct attack*)0)->damn)==1,"attack_damn width");
_Static_assert(((__typeof__(((struct attack*)0)->damn))-1 > 0),"attack_damn signedness");
_Static_assert(sizeof(((struct you*)0)->dx)==4,"you_dx width");
_Static_assert(((__typeof__(((struct you*)0)->dx))-1 < 0),"you_dx signedness");
_Static_assert(sizeof(((struct you*)0)->dy)==4,"you_dy width");
_Static_assert(((__typeof__(((struct you*)0)->dy))-1 < 0),"you_dy signedness");
_Static_assert(sizeof(((struct you*)0)->mh)==4,"you_mh width");
_Static_assert(((__typeof__(((struct you*)0)->mh))-1 < 0),"you_mh signedness");
_Static_assert(sizeof(((struct you*)0)->uhp)==4,"you_uhp width");
_Static_assert(((__typeof__(((struct you*)0)->uhp))-1 < 0),"you_uhp signedness");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4,"you_umonnum width");
_Static_assert(((__typeof__(((struct you*)0)->umonnum))-1 < 0),"you_umonnum signedness");
_Static_assert(sizeof(((struct you*)0)->umonster)==4,"you_umonster width");
_Static_assert(((__typeof__(((struct you*)0)->umonster))-1 < 0),"you_umonster signedness");
_Static_assert(sizeof(((struct you*)0)->ustuck)==8,"you_ustuck pointer width");
_Static_assert(sizeof(((struct you*)0)->ux)==2,"you_ux width");
_Static_assert(((__typeof__(((struct you*)0)->ux))-1 < 0),"you_ux signedness");
_Static_assert(sizeof(((struct you*)0)->ux0)==2,"you_ux0 width");
_Static_assert(((__typeof__(((struct you*)0)->ux0))-1 < 0),"you_ux0 signedness");
_Static_assert(sizeof(((struct you*)0)->uy)==2,"you_uy width");
_Static_assert(((__typeof__(((struct you*)0)->uy))-1 < 0),"you_uy signedness");
_Static_assert(sizeof(((struct you*)0)->uy0)==2,"you_uy0 width");
_Static_assert(((__typeof__(((struct you*)0)->uy0))-1 < 0),"you_uy0 signedness");
_Static_assert(sizeof(((struct d_level*)0)->dlevel)==2,"level_dlevel width");
_Static_assert(((__typeof__(((struct d_level*)0)->dlevel))-1 < 0),"level_dlevel signedness");
_Static_assert(sizeof(((struct d_level*)0)->dnum)==2,"level_dnum width");
_Static_assert(((__typeof__(((struct d_level*)0)->dnum))-1 < 0),"level_dnum signedness");
_Static_assert(sizeof(((struct nhcoord*)0)->x)==2,"coord_x width");
_Static_assert(((__typeof__(((struct nhcoord*)0)->x))-1 < 0),"coord_x signedness");
_Static_assert(sizeof(((struct nhcoord*)0)->y)==2,"coord_y width");
_Static_assert(((__typeof__(((struct nhcoord*)0)->y))-1 < 0),"coord_y signedness");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8,"prop_blocked width");
_Static_assert(((__typeof__(((struct prop*)0)->blocked))-1 < 0),"prop_blocked signedness");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8,"prop_extrinsic width");
_Static_assert(((__typeof__(((struct prop*)0)->extrinsic))-1 < 0),"prop_extrinsic signedness");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8,"prop_intrinsic width");
_Static_assert(((__typeof__(((struct prop*)0)->intrinsic))-1 < 0),"prop_intrinsic signedness");
_Static_assert(sizeof(((struct mfndposdata*)0)->cnt)==4,"mfp_cnt width");
_Static_assert(((__typeof__(((struct mfndposdata*)0)->cnt))-1 < 0),"mfp_cnt signedness");
_Static_assert(sizeof(((struct accessibility_data*)0)->mon_movement)==1,"a11y_mon_movement width");
_Static_assert(((__typeof__(((struct accessibility_data*)0)->mon_movement))-1 < 0),"a11y_mon_movement signedness");
_Static_assert(sizeof(((struct achievement_tracking*)0)->mines_prize_oid)==4,"achieve_mines_prize_oid width");
_Static_assert(((__typeof__(((struct achievement_tracking*)0)->mines_prize_oid))-1 > 0),"achieve_mines_prize_oid signedness");
_Static_assert(sizeof(((struct achievement_tracking*)0)->soko_prize_oid)==4,"achieve_soko_prize_oid width");
_Static_assert(((__typeof__(((struct achievement_tracking*)0)->soko_prize_oid))-1 > 0),"achieve_soko_prize_oid signedness");
_Static_assert(sizeof(((struct rm*)0)->typ)==1,"rm_typ width");
_Static_assert(((__typeof__(((struct rm*)0)->typ))-1 < 0),"rm_typ signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_skill)==1,"cls_oc_skill width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_skill))-1 < 0),"cls_oc_skill signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_subtyp)==1,"cls_oc_subtyp width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_subtyp))-1 < 0),"cls_oc_subtyp signedness");
_Static_assert(sizeof(((struct edog*)0)->hungrytime)==8,"edog_hungrytime width");
_Static_assert(((__typeof__(((struct edog*)0)->hungrytime))-1 < 0),"edog_hungrytime signedness");
_Static_assert(sizeof(((struct mextra*)0)->edog)==8,"mextra_edog pointer width");
_Static_assert(sizeof(((struct stairway*)0)->sx)==2,"stair_sx width");
_Static_assert(((__typeof__(((struct stairway*)0)->sx))-1 < 0),"stair_sx signedness");
_Static_assert(sizeof(((struct stairway*)0)->sy)==2,"stair_sy width");
_Static_assert(((__typeof__(((struct stairway*)0)->sy))-1 < 0),"stair_sy signedness");
_Static_assert(sizeof(((struct stairway*)0)->up)==1,"stair_up width");
_Static_assert(((__typeof__(((struct stairway*)0)->up))-1 < 0),"stair_up signedness");
_Static_assert(sizeof(((struct throw_and_return_weapon*)0)->range)==4,"arw_range width");
_Static_assert(((__typeof__(((struct throw_and_return_weapon*)0)->range))-1 < 0),"arw_range signedness");
_Static_assert(sizeof(((struct Gender*)0)->his)==8,"gender_his pointer width");
_Static_assert(sizeof(((struct mvitals*)0)->mvflags)==1,"vital_mvflags width");
_Static_assert(((__typeof__(((struct mvitals*)0)->mvflags))-1 > 0),"vital_mvflags signedness");
_Static_assert(sizeof(((struct flag*)0)->verbose)==1,"flags_verbose width");
_Static_assert(((__typeof__(((struct flag*)0)->verbose))-1 < 0),"flags_verbose signedness");
_Static_assert(sizeof(((struct instance_globals_saved_m*)0)->moves)==8,"svm_moves width");
_Static_assert(((__typeof__(((struct instance_globals_saved_m*)0)->moves))-1 < 0),"svm_moves signedness");
_Static_assert(sizeof(((struct instance_globals_m*)0)->multi)==8,"gm_multi width");
_Static_assert(((__typeof__(((struct instance_globals_m*)0)->multi))-1 < 0),"gm_multi signedness");
_Static_assert(sizeof(((struct instance_globals_o*)0)->occupation)==8,"go_occupation pointer width");
_Static_assert(sizeof(((struct instance_globals_n*)0)->notonhead)==1,"gn_notonhead width");
_Static_assert(((__typeof__(((struct instance_globals_n*)0)->notonhead))-1 < 0),"gn_notonhead signedness");
_Static_assert(sizeof(((struct instance_globals_v*)0)->viz_array)==8,"gv_viz_array pointer width");
_Static_assert(sizeof(((struct instance_globals_i*)0)->invent)==8,"gi_invent pointer width");
_Static_assert(sizeof(((struct u_roleplay*)0)->deaf)==1,"roleplay_deaf width");
_Static_assert(((__typeof__(((struct u_roleplay*)0)->deaf))-1 < 0),"roleplay_deaf signedness");
_Static_assert(sizeof(((__typeof__(svl.level)*)0)->monlist)==8,"dlevel_monlist pointer width");
#if !defined(DEBUG)||defined(SND_LIB_INTEGRATED)||!defined(MAIL_STRUCTURES)||defined(NO_HIDING_UNDER_STATUES)
#error Review MONMOVE configured profile
#endif
_Static_assert(__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__,"MONMOVE little endian ABI");
size_t probe_context_size(void){return sizeof(struct monst);}
int probe_layout_count(void){return sizeof teleport_monmove_layout/sizeof teleport_monmove_layout[0];}
const char*probe_layout_name(int i){return teleport_monmove_layout[i].name;}
size_t probe_layout_value(int i){return teleport_monmove_layout[i].value;}
#endif
