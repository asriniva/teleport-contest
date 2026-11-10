/* MON compiler-derived ABI fields only, no source policy. */
#ifndef TELEPORT_MON_LAYOUT_H
#define TELEPORT_MON_LAYOUT_H
#include "hack.h"
#include "mfndpos.h"
#include "region.h"
#include <stddef.h>
#define MON_META(k,v) {#k,(size_t)(v)}
static const struct{const char*name;size_t value;}teleport_mon_layout[]={
MON_META(pointerSize,sizeof(void*)),
MON_META(intSize,sizeof(int)),
MON_META(longSize,sizeof(long)),
MON_META(coordxySize,sizeof(coordxy)),
MON_META(booleanSize,sizeof(boolean)),
MON_META(monSize,sizeof(struct monst)),
MON_META(mon_cham,offsetof(struct monst,cham)),
MON_META(mon_cham_size,sizeof(((struct monst*)0)->cham)),
MON_META(mon_data,offsetof(struct monst,data)),
MON_META(mon_data_size,sizeof(((struct monst*)0)->data)),
MON_META(mon_m_ap_type,offsetof(struct monst,m_ap_type)),
MON_META(mon_m_ap_type_size,sizeof(((struct monst*)0)->m_ap_type)),
MON_META(mon_m_id,offsetof(struct monst,m_id)),
MON_META(mon_m_id_size,sizeof(((struct monst*)0)->m_id)),
MON_META(mon_m_lev,offsetof(struct monst,m_lev)),
MON_META(mon_m_lev_size,sizeof(((struct monst*)0)->m_lev)),
MON_META(mon_malign,offsetof(struct monst,malign)),
MON_META(mon_malign_size,sizeof(((struct monst*)0)->malign)),
MON_META(mon_mappearance,offsetof(struct monst,mappearance)),
MON_META(mon_mappearance_size,sizeof(((struct monst*)0)->mappearance)),
MON_META(mon_meating,offsetof(struct monst,meating)),
MON_META(mon_meating_size,sizeof(((struct monst*)0)->meating)),
MON_META(mon_mextra,offsetof(struct monst,mextra)),
MON_META(mon_mextra_size,sizeof(((struct monst*)0)->mextra)),
MON_META(mon_mhp,offsetof(struct monst,mhp)),
MON_META(mon_mhp_size,sizeof(((struct monst*)0)->mhp)),
MON_META(mon_mhpmax,offsetof(struct monst,mhpmax)),
MON_META(mon_mhpmax_size,sizeof(((struct monst*)0)->mhpmax)),
MON_META(mon_mintrinsics,offsetof(struct monst,mintrinsics)),
MON_META(mon_mintrinsics_size,sizeof(((struct monst*)0)->mintrinsics)),
MON_META(mon_minvent,offsetof(struct monst,minvent)),
MON_META(mon_minvent_size,sizeof(((struct monst*)0)->minvent)),
MON_META(mon_misc_worn_check,offsetof(struct monst,misc_worn_check)),
MON_META(mon_misc_worn_check_size,sizeof(((struct monst*)0)->misc_worn_check)),
MON_META(mon_mlstmv,offsetof(struct monst,mlstmv)),
MON_META(mon_mlstmv_size,sizeof(((struct monst*)0)->mlstmv)),
MON_META(mon_mnum,offsetof(struct monst,mnum)),
MON_META(mon_mnum_size,sizeof(((struct monst*)0)->mnum)),
MON_META(mon_movement,offsetof(struct monst,movement)),
MON_META(mon_movement_size,sizeof(((struct monst*)0)->movement)),
MON_META(mon_mspec_used,offsetof(struct monst,mspec_used)),
MON_META(mon_mspec_used_size,sizeof(((struct monst*)0)->mspec_used)),
MON_META(mon_mstate,offsetof(struct monst,mstate)),
MON_META(mon_mstate_size,sizeof(((struct monst*)0)->mstate)),
MON_META(mon_mstrategy,offsetof(struct monst,mstrategy)),
MON_META(mon_mstrategy_size,sizeof(((struct monst*)0)->mstrategy)),
MON_META(mon_mtame,offsetof(struct monst,mtame)),
MON_META(mon_mtame_size,sizeof(((struct monst*)0)->mtame)),
MON_META(mon_mtrapseen,offsetof(struct monst,mtrapseen)),
MON_META(mon_mtrapseen_size,sizeof(((struct monst*)0)->mtrapseen)),
MON_META(mon_mux,offsetof(struct monst,mux)),
MON_META(mon_mux_size,sizeof(((struct monst*)0)->mux)),
MON_META(mon_muy,offsetof(struct monst,muy)),
MON_META(mon_muy_size,sizeof(((struct monst*)0)->muy)),
MON_META(mon_mw,offsetof(struct monst,mw)),
MON_META(mon_mw_size,sizeof(((struct monst*)0)->mw)),
MON_META(mon_mx,offsetof(struct monst,mx)),
MON_META(mon_mx_size,sizeof(((struct monst*)0)->mx)),
MON_META(mon_my,offsetof(struct monst,my)),
MON_META(mon_my_size,sizeof(((struct monst*)0)->my)),
MON_META(mon_nmon,offsetof(struct monst,nmon)),
MON_META(mon_nmon_size,sizeof(((struct monst*)0)->nmon)),
MON_META(mon_weapon_check,offsetof(struct monst,weapon_check)),
MON_META(mon_weapon_check_size,sizeof(((struct monst*)0)->weapon_check)),
MON_META(youSize,sizeof(struct you)),
MON_META(you_acurr,offsetof(struct you,acurr)),
MON_META(you_acurr_size,sizeof(((struct you*)0)->acurr)),
MON_META(you_mh,offsetof(struct you,mh)),
MON_META(you_mh_size,sizeof(((struct you*)0)->mh)),
MON_META(you_mhmax,offsetof(struct you,mhmax)),
MON_META(you_mhmax_size,sizeof(((struct you*)0)->mhmax)),
MON_META(you_ualign,offsetof(struct you,ualign)),
MON_META(you_ualign_size,sizeof(((struct you*)0)->ualign)),
MON_META(you_ublessed,offsetof(struct you,ublessed)),
MON_META(you_ublessed_size,sizeof(((struct you*)0)->ublessed)),
MON_META(you_uconduct,offsetof(struct you,uconduct)),
MON_META(you_uconduct_size,sizeof(((struct you*)0)->uconduct)),
MON_META(you_uevent,offsetof(struct you,uevent)),
MON_META(you_uevent_size,sizeof(((struct you*)0)->uevent)),
MON_META(you_ugallop,offsetof(struct you,ugallop)),
MON_META(you_ugallop_size,sizeof(((struct you*)0)->ugallop)),
MON_META(you_ugangr,offsetof(struct you,ugangr)),
MON_META(you_ugangr_size,sizeof(((struct you*)0)->ugangr)),
MON_META(you_uhp,offsetof(struct you,uhp)),
MON_META(you_uhp_size,sizeof(((struct you*)0)->uhp)),
MON_META(you_uhpmax,offsetof(struct you,uhpmax)),
MON_META(you_uhpmax_size,sizeof(((struct you*)0)->uhpmax)),
MON_META(you_ulevel,offsetof(struct you,ulevel)),
MON_META(you_ulevel_size,sizeof(((struct you*)0)->ulevel)),
MON_META(you_umonnum,offsetof(struct you,umonnum)),
MON_META(you_umonnum_size,sizeof(((struct you*)0)->umonnum)),
MON_META(you_umonster,offsetof(struct you,umonster)),
MON_META(you_umonster_size,sizeof(((struct you*)0)->umonster)),
MON_META(you_uprops,offsetof(struct you,uprops)),
MON_META(you_uprops_size,sizeof(((struct you*)0)->uprops)),
MON_META(you_uroleplay,offsetof(struct you,uroleplay)),
MON_META(you_uroleplay_size,sizeof(((struct you*)0)->uroleplay)),
MON_META(you_ushops,offsetof(struct you,ushops)),
MON_META(you_ushops_size,sizeof(((struct you*)0)->ushops)),
MON_META(you_usteed,offsetof(struct you,usteed)),
MON_META(you_usteed_size,sizeof(((struct you*)0)->usteed)),
MON_META(you_ustuck,offsetof(struct you,ustuck)),
MON_META(you_ustuck_size,sizeof(((struct you*)0)->ustuck)),
MON_META(you_uswldtim,offsetof(struct you,uswldtim)),
MON_META(you_uswldtim_size,sizeof(((struct you*)0)->uswldtim)),
MON_META(you_utotype,offsetof(struct you,utotype)),
MON_META(you_utotype_size,sizeof(((struct you*)0)->utotype)),
MON_META(you_utrap,offsetof(struct you,utrap)),
MON_META(you_utrap_size,sizeof(((struct you*)0)->utrap)),
MON_META(you_ux,offsetof(struct you,ux)),
MON_META(you_ux_size,sizeof(((struct you*)0)->ux)),
MON_META(you_uy,offsetof(struct you,uy)),
MON_META(you_uy_size,sizeof(((struct you*)0)->uy)),
MON_META(you_uz,offsetof(struct you,uz)),
MON_META(you_uz_size,sizeof(((struct you*)0)->uz)),
MON_META(propSize,sizeof(struct prop)),
MON_META(prop_blocked,offsetof(struct prop,blocked)),
MON_META(prop_blocked_size,sizeof(((struct prop*)0)->blocked)),
MON_META(prop_extrinsic,offsetof(struct prop,extrinsic)),
MON_META(prop_extrinsic_size,sizeof(((struct prop*)0)->extrinsic)),
MON_META(prop_intrinsic,offsetof(struct prop,intrinsic)),
MON_META(prop_intrinsic_size,sizeof(((struct prop*)0)->intrinsic)),
MON_META(objSize,sizeof(struct obj)),
MON_META(obj_age,offsetof(struct obj,age)),
MON_META(obj_age_size,sizeof(((struct obj*)0)->age)),
MON_META(obj_cobj,offsetof(struct obj,cobj)),
MON_META(obj_cobj_size,sizeof(((struct obj*)0)->cobj)),
MON_META(obj_corpsenm,offsetof(struct obj,corpsenm)),
MON_META(obj_corpsenm_size,sizeof(((struct obj*)0)->corpsenm)),
MON_META(obj_nexthere,offsetof(struct obj,nexthere)),
MON_META(obj_nexthere_size,sizeof(((struct obj*)0)->nexthere)),
MON_META(obj_nobj,offsetof(struct obj,nobj)),
MON_META(obj_nobj_size,sizeof(((struct obj*)0)->nobj)),
MON_META(obj_o_id,offsetof(struct obj,o_id)),
MON_META(obj_o_id_size,sizeof(((struct obj*)0)->o_id)),
MON_META(obj_oartifact,offsetof(struct obj,oartifact)),
MON_META(obj_oartifact_size,sizeof(((struct obj*)0)->oartifact)),
MON_META(obj_oclass,offsetof(struct obj,oclass)),
MON_META(obj_oclass_size,sizeof(((struct obj*)0)->oclass)),
MON_META(obj_otyp,offsetof(struct obj,otyp)),
MON_META(obj_otyp_size,sizeof(((struct obj*)0)->otyp)),
MON_META(obj_owt,offsetof(struct obj,owt)),
MON_META(obj_owt_size,sizeof(((struct obj*)0)->owt)),
MON_META(obj_ox,offsetof(struct obj,ox)),
MON_META(obj_ox_size,sizeof(((struct obj*)0)->ox)),
MON_META(obj_oy,offsetof(struct obj,oy)),
MON_META(obj_oy_size,sizeof(((struct obj*)0)->oy)),
MON_META(obj_quan,offsetof(struct obj,quan)),
MON_META(obj_quan_size,sizeof(((struct obj*)0)->quan)),
MON_META(obj_spe,offsetof(struct obj,spe)),
MON_META(obj_spe_size,sizeof(((struct obj*)0)->spe)),
MON_META(obj_where,offsetof(struct obj,where)),
MON_META(obj_where_size,sizeof(((struct obj*)0)->where)),
MON_META(iflagsSize,sizeof(struct instance_flags)),
MON_META(iflags_debug_fuzzer,offsetof(struct instance_flags,debug_fuzzer)),
MON_META(iflags_debug_fuzzer_size,sizeof(((struct instance_flags*)0)->debug_fuzzer)),
MON_META(iflags_getpos_coords,offsetof(struct instance_flags,getpos_coords)),
MON_META(iflags_getpos_coords_size,sizeof(((struct instance_flags*)0)->getpos_coords)),
MON_META(iflags_last_msg,offsetof(struct instance_flags,last_msg)),
MON_META(iflags_last_msg_size,sizeof(((struct instance_flags*)0)->last_msg)),
MON_META(iflags_mon_polycontrol,offsetof(struct instance_flags,mon_polycontrol)),
MON_META(iflags_mon_polycontrol_size,sizeof(((struct instance_flags*)0)->mon_polycontrol)),
MON_META(iflags_mon_telecontrol,offsetof(struct instance_flags,mon_telecontrol)),
MON_META(iflags_mon_telecontrol_size,sizeof(((struct instance_flags*)0)->mon_telecontrol)),
MON_META(iflags_purge_monsters,offsetof(struct instance_flags,purge_monsters)),
MON_META(iflags_purge_monsters_size,sizeof(((struct instance_flags*)0)->purge_monsters)),
MON_META(iflags_returning_missile,offsetof(struct instance_flags,returning_missile)),
MON_META(iflags_returning_missile_size,sizeof(((struct instance_flags*)0)->returning_missile)),
MON_META(iflags_sad_feeling,offsetof(struct instance_flags,sad_feeling)),
MON_META(iflags_sad_feeling_size,sizeof(((struct instance_flags*)0)->sad_feeling)),
MON_META(iflags_sanity_check,offsetof(struct instance_flags,sanity_check)),
MON_META(iflags_sanity_check_size,sizeof(((struct instance_flags*)0)->sanity_check)),
MON_META(stringsSize,sizeof(struct c_common_strings)),
MON_META(strings_c_Something,offsetof(struct c_common_strings,c_Something)),
MON_META(strings_c_Something_size,sizeof(((struct c_common_strings*)0)->c_Something)),
MON_META(strings_c_thats_enough_tries,offsetof(struct c_common_strings,c_thats_enough_tries)),
MON_META(strings_c_thats_enough_tries_size,sizeof(((struct c_common_strings*)0)->c_thats_enough_tries)),
MON_META(conductSize,sizeof(struct u_conduct)),
MON_META(conduct_killer,offsetof(struct u_conduct,killer)),
MON_META(conduct_killer_size,sizeof(((struct u_conduct*)0)->killer)),
MON_META(flagsSize,sizeof(struct flag)),
MON_META(flags_debug,offsetof(struct flag,debug)),
MON_META(flags_debug_size,sizeof(((struct flag*)0)->debug)),
MON_META(flags_female,offsetof(struct flag,female)),
MON_META(flags_female_size,sizeof(((struct flag*)0)->female)),
MON_META(flags_sparkle,offsetof(struct flag,sparkle)),
MON_META(flags_sparkle_size,sizeof(((struct flag*)0)->sparkle)),
MON_META(flags_verbose,offsetof(struct flag,verbose)),
MON_META(flags_verbose_size,sizeof(((struct flag*)0)->verbose)),
MON_META(topologySize,sizeof(struct dgn_topology)),
MON_META(topology_d_air_level,offsetof(struct dgn_topology,d_air_level)),
MON_META(topology_d_air_level_size,sizeof(((struct dgn_topology*)0)->d_air_level)),
MON_META(topology_d_astral_level,offsetof(struct dgn_topology,d_astral_level)),
MON_META(topology_d_astral_level_size,sizeof(((struct dgn_topology*)0)->d_astral_level)),
MON_META(topology_d_earth_level,offsetof(struct dgn_topology,d_earth_level)),
MON_META(topology_d_earth_level_size,sizeof(((struct dgn_topology*)0)->d_earth_level)),
MON_META(topology_d_knox_level,offsetof(struct dgn_topology,d_knox_level)),
MON_META(topology_d_knox_level_size,sizeof(((struct dgn_topology*)0)->d_knox_level)),
MON_META(topology_d_rogue_level,offsetof(struct dgn_topology,d_rogue_level)),
MON_META(topology_d_rogue_level_size,sizeof(((struct dgn_topology*)0)->d_rogue_level)),
MON_META(topology_d_sokoban_dnum,offsetof(struct dgn_topology,d_sokoban_dnum)),
MON_META(topology_d_sokoban_dnum_size,sizeof(((struct dgn_topology*)0)->d_sokoban_dnum)),
MON_META(topology_d_stronghold_level,offsetof(struct dgn_topology,d_stronghold_level)),
MON_META(topology_d_stronghold_level_size,sizeof(((struct dgn_topology*)0)->d_stronghold_level)),
MON_META(topology_d_water_level,offsetof(struct dgn_topology,d_water_level)),
MON_META(topology_d_water_level_size,sizeof(((struct dgn_topology*)0)->d_water_level)),
MON_META(gvSize,sizeof(struct instance_globals_v)),
MON_META(gv_vamp_rise_msg,offsetof(struct instance_globals_v,vamp_rise_msg)),
MON_META(gv_vamp_rise_msg_size,sizeof(((struct instance_globals_v*)0)->vamp_rise_msg)),
MON_META(gv_vision_full_recalc,offsetof(struct instance_globals_v,vision_full_recalc)),
MON_META(gv_vision_full_recalc_size,sizeof(((struct instance_globals_v*)0)->vision_full_recalc)),
MON_META(gv_viz_array,offsetof(struct instance_globals_v,viz_array)),
MON_META(gv_viz_array_size,sizeof(((struct instance_globals_v*)0)->viz_array)),
MON_META(svmSize,sizeof(struct instance_globals_saved_m)),
MON_META(svm_moves,offsetof(struct instance_globals_saved_m,moves)),
MON_META(svm_moves_size,sizeof(((struct instance_globals_saved_m*)0)->moves)),
MON_META(svm_mvitals,offsetof(struct instance_globals_saved_m,mvitals)),
MON_META(svm_mvitals_size,sizeof(((struct instance_globals_saved_m*)0)->mvitals)),
MON_META(roleSize,sizeof(struct Role)),
MON_META(role_guardnum,offsetof(struct Role,guardnum)),
MON_META(role_guardnum_size,sizeof(((struct Role*)0)->guardnum)),
MON_META(role_mnum,offsetof(struct Role,mnum)),
MON_META(role_mnum_size,sizeof(((struct Role*)0)->mnum)),
MON_META(clsSize,sizeof(struct objclass)),
MON_META(cls_oc_color,offsetof(struct objclass,oc_color)),
MON_META(cls_oc_color_size,sizeof(((struct objclass*)0)->oc_color)),
MON_META(cls_oc_descr_idx,offsetof(struct objclass,oc_descr_idx)),
MON_META(cls_oc_descr_idx_size,sizeof(((struct objclass*)0)->oc_descr_idx)),
MON_META(cls_oc_subtyp,offsetof(struct objclass,oc_subtyp)),
MON_META(cls_oc_subtyp_size,sizeof(((struct objclass*)0)->oc_subtyp)),
MON_META(cls_oc_weight,offsetof(struct objclass,oc_weight)),
MON_META(cls_oc_weight_size,sizeof(((struct objclass*)0)->oc_weight)),
MON_META(pmSize,sizeof(struct permonst)),
MON_META(pm_cwt,offsetof(struct permonst,cwt)),
MON_META(pm_cwt_size,sizeof(((struct permonst*)0)->cwt)),
MON_META(pm_difficulty,offsetof(struct permonst,difficulty)),
MON_META(pm_difficulty_size,sizeof(((struct permonst*)0)->difficulty)),
MON_META(pm_geno,offsetof(struct permonst,geno)),
MON_META(pm_geno_size,sizeof(((struct permonst*)0)->geno)),
MON_META(pm_maligntyp,offsetof(struct permonst,maligntyp)),
MON_META(pm_maligntyp_size,sizeof(((struct permonst*)0)->maligntyp)),
MON_META(pm_mattk,offsetof(struct permonst,mattk)),
MON_META(pm_mattk_size,sizeof(((struct permonst*)0)->mattk)),
MON_META(pm_mflags1,offsetof(struct permonst,mflags1)),
MON_META(pm_mflags1_size,sizeof(((struct permonst*)0)->mflags1)),
MON_META(pm_mflags2,offsetof(struct permonst,mflags2)),
MON_META(pm_mflags2_size,sizeof(((struct permonst*)0)->mflags2)),
MON_META(pm_mflags3,offsetof(struct permonst,mflags3)),
MON_META(pm_mflags3_size,sizeof(((struct permonst*)0)->mflags3)),
MON_META(pm_mlet,offsetof(struct permonst,mlet)),
MON_META(pm_mlet_size,sizeof(((struct permonst*)0)->mlet)),
MON_META(pm_mlevel,offsetof(struct permonst,mlevel)),
MON_META(pm_mlevel_size,sizeof(((struct permonst*)0)->mlevel)),
MON_META(pm_mmove,offsetof(struct permonst,mmove)),
MON_META(pm_mmove_size,sizeof(((struct permonst*)0)->mmove)),
MON_META(pm_mresists,offsetof(struct permonst,mresists)),
MON_META(pm_mresists_size,sizeof(((struct permonst*)0)->mresists)),
MON_META(pm_msize,offsetof(struct permonst,msize)),
MON_META(pm_msize_size,sizeof(((struct permonst*)0)->msize)),
MON_META(pm_msound,offsetof(struct permonst,msound)),
MON_META(pm_msound_size,sizeof(((struct permonst*)0)->msound)),
MON_META(pm_pmidx,offsetof(struct permonst,pmidx)),
MON_META(pm_pmidx_size,sizeof(((struct permonst*)0)->pmidx)),
MON_META(pm_pmnames,offsetof(struct permonst,pmnames)),
MON_META(pm_pmnames_size,sizeof(((struct permonst*)0)->pmnames)),
MON_META(vitalSize,sizeof(struct mvitals)),
MON_META(vital_died,offsetof(struct mvitals,died)),
MON_META(vital_died_size,sizeof(((struct mvitals*)0)->died)),
MON_META(vital_mvflags,offsetof(struct mvitals,mvflags)),
MON_META(vital_mvflags_size,sizeof(((struct mvitals*)0)->mvflags)),
MON_META(gpSize,sizeof(struct instance_globals_p)),
MON_META(gmSize,sizeof(struct instance_globals_m)),
MON_META(gm_migrating_mons,offsetof(struct instance_globals_m,migrating_mons)),
MON_META(gm_migrating_mons_size,sizeof(((struct instance_globals_m*)0)->migrating_mons)),
MON_META(gm_migrating_objs,offsetof(struct instance_globals_m,migrating_objs)),
MON_META(gm_migrating_objs_size,sizeof(((struct instance_globals_m*)0)->migrating_objs)),
MON_META(gm_mswallower,offsetof(struct instance_globals_m,mswallower)),
MON_META(gm_mswallower_size,sizeof(((struct instance_globals_m*)0)->mswallower)),
MON_META(gm_multi,offsetof(struct instance_globals_m,multi)),
MON_META(gm_multi_size,sizeof(((struct instance_globals_m*)0)->multi)),
MON_META(attribsSize,sizeof(struct attribs)),
MON_META(levelSize,sizeof(struct d_level)),
MON_META(level_dlevel,offsetof(struct d_level,dlevel)),
MON_META(level_dlevel_size,sizeof(((struct d_level*)0)->dlevel)),
MON_META(level_dnum,offsetof(struct d_level,dnum)),
MON_META(level_dnum_size,sizeof(((struct d_level*)0)->dnum)),
MON_META(rmSize,sizeof(struct rm)),
MON_META(rm_glyph,offsetof(struct rm,glyph)),
MON_META(rm_glyph_size,sizeof(((struct rm*)0)->glyph)),
MON_META(rm_typ,offsetof(struct rm,typ)),
MON_META(rm_typ_size,sizeof(((struct rm*)0)->typ)),
MON_META(svlSize,sizeof(struct instance_globals_saved_l)),
MON_META(svl_level,offsetof(struct instance_globals_saved_l,level)),
MON_META(svl_level_size,sizeof(((struct instance_globals_saved_l*)0)->level)),
MON_META(descrSize,sizeof(struct objdescr)),
MON_META(skillSize,sizeof(struct skills)),
MON_META(roleplaySize,sizeof(struct u_roleplay)),
MON_META(roleplay_deaf,offsetof(struct u_roleplay,deaf)),
MON_META(roleplay_deaf_size,sizeof(((struct u_roleplay*)0)->deaf)),
MON_META(gnSize,sizeof(struct instance_globals_n)),
MON_META(gn_notonhead,offsetof(struct instance_globals_n,notonhead)),
MON_META(gn_notonhead_size,sizeof(((struct instance_globals_n*)0)->notonhead)),
MON_META(genderSize,sizeof(struct Gender)),
MON_META(gender_he,offsetof(struct Gender,he)),
MON_META(gender_he_size,sizeof(((struct Gender*)0)->he)),
MON_META(gender_him,offsetof(struct Gender,him)),
MON_META(gender_him_size,sizeof(((struct Gender*)0)->him)),
MON_META(gender_his,offsetof(struct Gender,his)),
MON_META(gender_his_size,sizeof(((struct Gender*)0)->his)),
MON_META(stairSize,sizeof(struct stairway)),
MON_META(stair_sx,offsetof(struct stairway,sx)),
MON_META(stair_sx_size,sizeof(((struct stairway*)0)->sx)),
MON_META(stair_sy,offsetof(struct stairway,sy)),
MON_META(stair_sy_size,sizeof(((struct stairway*)0)->sy)),
MON_META(alignSize,sizeof(struct align)),
MON_META(align_abuse,offsetof(struct align,abuse)),
MON_META(align_abuse_size,sizeof(((struct align*)0)->abuse)),
MON_META(align_record,offsetof(struct align,record)),
MON_META(align_record_size,sizeof(((struct align*)0)->record)),
MON_META(align_type,offsetof(struct align,type)),
MON_META(align_type_size,sizeof(((struct align*)0)->type)),
MON_META(contextSize,sizeof(struct context_info)),
MON_META(context_achieveo,offsetof(struct context_info,achieveo)),
MON_META(context_achieveo_size,sizeof(((struct context_info*)0)->achieveo)),
MON_META(context_bypasses,offsetof(struct context_info,bypasses)),
MON_META(context_bypasses_size,sizeof(((struct context_info*)0)->bypasses)),
MON_META(context_forcefight,offsetof(struct context_info,forcefight)),
MON_META(context_forcefight_size,sizeof(((struct context_info*)0)->forcefight)),
MON_META(context_lifelist,offsetof(struct context_info,lifelist)),
MON_META(context_lifelist_size,sizeof(((struct context_info*)0)->lifelist)),
MON_META(context_mon_moving,offsetof(struct context_info,mon_moving)),
MON_META(context_mon_moving_size,sizeof(((struct context_info*)0)->mon_moving)),
MON_META(context_mv,offsetof(struct context_info,mv)),
MON_META(context_mv_size,sizeof(((struct context_info*)0)->mv)),
MON_META(context_polearm,offsetof(struct context_info,polearm)),
MON_META(context_polearm_size,sizeof(((struct context_info*)0)->polearm)),
MON_META(context_startingpet_mid,offsetof(struct context_info,startingpet_mid)),
MON_META(context_startingpet_mid_size,sizeof(((struct context_info*)0)->startingpet_mid)),
MON_META(context_startingpet_typ,offsetof(struct context_info,startingpet_typ)),
MON_META(context_startingpet_typ_size,sizeof(((struct context_info*)0)->startingpet_typ)),
MON_META(gySize,sizeof(struct instance_globals_y)),
MON_META(gy_youmonst,offsetof(struct instance_globals_y,youmonst)),
MON_META(gy_youmonst_size,sizeof(((struct instance_globals_y*)0)->youmonst)),
MON_META(guSize,sizeof(struct instance_globals_u)),
MON_META(gu_urace,offsetof(struct instance_globals_u,urace)),
MON_META(gu_urace_size,sizeof(((struct instance_globals_u*)0)->urace)),
MON_META(gu_urole,offsetof(struct instance_globals_u,urole)),
MON_META(gu_urole_size,sizeof(((struct instance_globals_u*)0)->urole)),
MON_META(svdSize,sizeof(struct instance_globals_saved_d)),
MON_META(svd_dungeon_topology,offsetof(struct instance_globals_saved_d,dungeon_topology)),
MON_META(svd_dungeon_topology_size,sizeof(((struct instance_globals_saved_d*)0)->dungeon_topology)),
MON_META(cgSize,sizeof(struct const_globals)),
MON_META(cg_zeromonst,offsetof(struct const_globals,zeromonst)),
MON_META(cg_zeromonst_size,sizeof(((struct const_globals*)0)->zeromonst)),
MON_META(haveSize,sizeof(struct u_have)),
MON_META(dispSize,sizeof(struct display_hints)),
MON_META(disp_botl,offsetof(struct display_hints,botl)),
MON_META(disp_botl_size,sizeof(((struct display_hints*)0)->botl)),
MON_META(raceSize,sizeof(struct Race)),
MON_META(race_mnum,offsetof(struct Race,mnum)),
MON_META(race_mnum_size,sizeof(((struct Race*)0)->mnum)),
MON_META(race_selfmask,offsetof(struct Race,selfmask)),
MON_META(race_selfmask_size,sizeof(((struct Race*)0)->selfmask)),
MON_META(giSize,sizeof(struct instance_globals_i)),
MON_META(gi_in_mklev,offsetof(struct instance_globals_i,in_mklev)),
MON_META(gi_in_mklev_size,sizeof(((struct instance_globals_i*)0)->in_mklev)),
MON_META(gi_invent,offsetof(struct instance_globals_i,invent)),
MON_META(gi_invent_size,sizeof(((struct instance_globals_i*)0)->invent)),
MON_META(attackSize,sizeof(struct attack)),
MON_META(attack_aatyp,offsetof(struct attack,aatyp)),
MON_META(attack_aatyp_size,sizeof(((struct attack*)0)->aatyp)),
MON_META(attack_adtyp,offsetof(struct attack,adtyp)),
MON_META(attack_adtyp_size,sizeof(((struct attack*)0)->adtyp)),
MON_META(attack_damd,offsetof(struct attack,damd)),
MON_META(attack_damd_size,sizeof(((struct attack*)0)->damd)),
MON_META(attack_damn,offsetof(struct attack,damn)),
MON_META(attack_damn_size,sizeof(((struct attack*)0)->damn)),
MON_META(coordSize,sizeof(struct nhcoord)),
MON_META(coord_x,offsetof(struct nhcoord,x)),
MON_META(coord_x_size,sizeof(((struct nhcoord*)0)->x)),
MON_META(coord_y,offsetof(struct nhcoord,y)),
MON_META(coord_y_size,sizeof(((struct nhcoord*)0)->y)),
MON_META(killerSize,sizeof(struct kinfo)),
MON_META(killer_name,offsetof(struct kinfo,name)),
MON_META(killer_name_size,sizeof(((struct kinfo*)0)->name)),
MON_META(mextraSize,sizeof(struct mextra)),
MON_META(mextra_ebones,offsetof(struct mextra,ebones)),
MON_META(mextra_ebones_size,sizeof(((struct mextra*)0)->ebones)),
MON_META(mextra_edog,offsetof(struct mextra,edog)),
MON_META(mextra_edog_size,sizeof(((struct mextra*)0)->edog)),
MON_META(mextra_egd,offsetof(struct mextra,egd)),
MON_META(mextra_egd_size,sizeof(((struct mextra*)0)->egd)),
MON_META(mextra_emin,offsetof(struct mextra,emin)),
MON_META(mextra_emin_size,sizeof(((struct mextra*)0)->emin)),
MON_META(mextra_epri,offsetof(struct mextra,epri)),
MON_META(mextra_epri_size,sizeof(((struct mextra*)0)->epri)),
MON_META(mextra_eshk,offsetof(struct mextra,eshk)),
MON_META(mextra_eshk_size,sizeof(((struct mextra*)0)->eshk)),
MON_META(mextra_mcorpsenm,offsetof(struct mextra,mcorpsenm)),
MON_META(mextra_mcorpsenm_size,sizeof(((struct mextra*)0)->mcorpsenm)),
MON_META(mextra_mgivenname,offsetof(struct mextra,mgivenname)),
MON_META(mextra_mgivenname_size,sizeof(((struct mextra*)0)->mgivenname)),
MON_META(edogSize,sizeof(struct edog)),
MON_META(edog_droptime,offsetof(struct edog,droptime)),
MON_META(edog_droptime_size,sizeof(((struct edog*)0)->droptime)),
MON_META(edog_whistletime,offsetof(struct edog,whistletime)),
MON_META(edog_whistletime_size,sizeof(((struct edog*)0)->whistletime)),
MON_META(eshkSize,sizeof(struct eshk)),
MON_META(eshk_shoptype,offsetof(struct eshk,shoptype)),
MON_META(eshk_shoptype_size,sizeof(((struct eshk*)0)->shoptype)),
MON_META(epriSize,sizeof(struct epri)),
MON_META(eminSize,sizeof(struct emin)),
MON_META(egdSize,sizeof(struct egd)),
MON_META(ebonesSize,sizeof(struct ebones)),
MON_META(levelflagsSize,sizeof(struct levelflags)),
MON_META(mfpSize,sizeof(struct mfndposdata)),
MON_META(mfp_cnt,offsetof(struct mfndposdata,cnt)),
MON_META(mfp_cnt_size,sizeof(((struct mfndposdata*)0)->cnt)),
MON_META(mfp_info,offsetof(struct mfndposdata,info)),
MON_META(mfp_info_size,sizeof(((struct mfndposdata*)0)->info)),
MON_META(mfp_poss,offsetof(struct mfndposdata,poss)),
MON_META(mfp_poss_size,sizeof(((struct mfndposdata*)0)->poss)),
MON_META(trapSize,sizeof(struct trap)),
MON_META(trap_launch,offsetof(struct trap,launch)),
MON_META(trap_launch_size,sizeof(((struct trap*)0)->launch)),
MON_META(engrSize,sizeof(struct engr)),
MON_META(classsymSize,sizeof(struct class_sym)),
MON_META(classsym_sym,offsetof(struct class_sym,sym)),
MON_META(classsym_sym_size,sizeof(((struct class_sym*)0)->sym)),
MON_META(shclassSize,sizeof(struct shclass)),
MON_META(shclass_name,offsetof(struct shclass,name)),
MON_META(shclass_name_size,sizeof(((struct shclass*)0)->name)),
MON_META(sinfoSize,sizeof(struct sinfo)),
MON_META(sinfo_done_hup,offsetof(struct sinfo,done_hup)),
MON_META(sinfo_done_hup_size,sizeof(((struct sinfo*)0)->done_hup)),
MON_META(gbSize,sizeof(struct instance_globals_b)),
MON_META(gb_bhitpos,offsetof(struct instance_globals_b,bhitpos)),
MON_META(gb_bhitpos_size,sizeof(((struct instance_globals_b*)0)->bhitpos)),
MON_META(svqSize,sizeof(struct instance_globals_saved_q)),
MON_META(svq_quest_status,offsetof(struct instance_globals_saved_q,quest_status)),
MON_META(svq_quest_status_size,sizeof(((struct instance_globals_saved_q*)0)->quest_status)),
MON_META(q_scoreSize,sizeof(struct q_score)),
MON_META(q_score_leader_m_id,offsetof(struct q_score,leader_m_id)),
MON_META(q_score_leader_m_id_size,sizeof(((struct q_score*)0)->leader_m_id)),
MON_META(lifelistsSize,sizeof(struct lifelists)),
MON_META(lifelists_total_photographed,offsetof(struct lifelists,total_photographed)),
MON_META(lifelists_total_photographed_size,sizeof(((struct lifelists*)0)->total_photographed)),
MON_META(lifelists_total_seen_upclose,offsetof(struct lifelists,total_seen_upclose)),
MON_META(lifelists_total_seen_upclose_size,sizeof(((struct lifelists*)0)->total_seen_upclose)),
MON_META(gzSize,sizeof(struct instance_globals_z)),
MON_META(gz_zombify,offsetof(struct instance_globals_z,zombify)),
MON_META(gz_zombify_size,sizeof(((struct instance_globals_z*)0)->zombify)),
MON_META(svkSize,sizeof(struct instance_globals_saved_k)),
MON_META(svk_killer,offsetof(struct instance_globals_saved_k,killer)),
MON_META(svk_killer_size,sizeof(((struct instance_globals_saved_k*)0)->killer)),
MON_META(gtSize,sizeof(struct instance_globals_t)),
MON_META(gt_thrownobj,offsetof(struct instance_globals_t,thrownobj)),
MON_META(gt_thrownobj_size,sizeof(((struct instance_globals_t*)0)->thrownobj)),
MON_META(gaSize,sizeof(struct instance_globals_a)),
MON_META(ga_animal_list,offsetof(struct instance_globals_a,animal_list)),
MON_META(ga_animal_list_size,sizeof(((struct instance_globals_a*)0)->animal_list)),
MON_META(ga_animal_list_count,offsetof(struct instance_globals_a,animal_list_count)),
MON_META(ga_animal_list_count_size,sizeof(((struct instance_globals_a*)0)->animal_list_count)),
MON_META(gsSize,sizeof(struct instance_globals_s)),
MON_META(gs_somebody_can_move,offsetof(struct instance_globals_s,somebody_can_move)),
MON_META(gs_somebody_can_move_size,sizeof(((struct instance_globals_s*)0)->somebody_can_move)),
MON_META(gs_stealmid,offsetof(struct instance_globals_s,stealmid)),
MON_META(gs_stealmid_size,sizeof(((struct instance_globals_s*)0)->stealmid)),
MON_META(gs_stoned,offsetof(struct instance_globals_s,stoned)),
MON_META(gs_stoned_size,sizeof(((struct instance_globals_s*)0)->stoned)),
MON_META(achievement_trackingSize,sizeof(struct achievement_tracking)),
MON_META(achievement_tracking_mines_prize_oid,offsetof(struct achievement_tracking,mines_prize_oid)),
MON_META(achievement_tracking_mines_prize_oid_size,sizeof(((struct achievement_tracking*)0)->mines_prize_oid)),
MON_META(achievement_tracking_soko_prize_oid,offsetof(struct achievement_tracking,soko_prize_oid)),
MON_META(achievement_tracking_soko_prize_oid_size,sizeof(((struct achievement_tracking*)0)->soko_prize_oid)),
MON_META(polearm_infoSize,sizeof(struct polearm_info)),
MON_META(polearm_info_hitmon,offsetof(struct polearm_info,hitmon)),
MON_META(polearm_info_hitmon_size,sizeof(((struct polearm_info*)0)->hitmon)),
MON_META(glSize,sizeof(struct instance_globals_l)),
MON_META(gl_last_hider,offsetof(struct instance_globals_l,last_hider)),
MON_META(gl_last_hider_size,sizeof(((struct instance_globals_l*)0)->last_hider)),
MON_META(gdSize,sizeof(struct instance_globals_d)),
MON_META(gd_disintegested,offsetof(struct instance_globals_d,disintegested)),
MON_META(gd_disintegested_size,sizeof(((struct instance_globals_d*)0)->disintegested)),
MON_META(u_eventSize,sizeof(struct u_event)),
MON_META(svcSize,sizeof(struct instance_globals_saved_c)),
MON_META(svc_context,offsetof(struct instance_globals_saved_c,context)),
MON_META(svc_context_size,sizeof(((struct instance_globals_saved_c*)0)->context)),
MON_META(regionSize,sizeof(NhRegion)),
MON_META(region_glyph,offsetof(NhRegion,glyph)),
MON_META(region_glyph_size,sizeof(((NhRegion*)0)->glyph)),
MON_META(dlevelSize,sizeof(__typeof__(svl.level))),
MON_META(dlevel_buriedobjlist,offsetof(__typeof__(svl.level),buriedobjlist)),
MON_META(dlevel_buriedobjlist_size,sizeof(((__typeof__(svl.level)*)0)->buriedobjlist)),
MON_META(dlevel_flags,offsetof(__typeof__(svl.level),flags)),
MON_META(dlevel_flags_size,sizeof(((__typeof__(svl.level)*)0)->flags)),
MON_META(dlevel_locations,offsetof(__typeof__(svl.level),locations)),
MON_META(dlevel_locations_size,sizeof(((__typeof__(svl.level)*)0)->locations)),
MON_META(dlevel_monlist,offsetof(__typeof__(svl.level),monlist)),
MON_META(dlevel_monlist_size,sizeof(((__typeof__(svl.level)*)0)->monlist)),
MON_META(dlevel_monsters,offsetof(__typeof__(svl.level),monsters)),
MON_META(dlevel_monsters_size,sizeof(((__typeof__(svl.level)*)0)->monsters)),
MON_META(dlevel_objects,offsetof(__typeof__(svl.level),objects)),
MON_META(dlevel_objects_size,sizeof(((__typeof__(svl.level)*)0)->objects)),
MON_META(dlevel_objlist,offsetof(__typeof__(svl.level),objlist)),
MON_META(dlevel_objlist_size,sizeof(((__typeof__(svl.level)*)0)->objlist)),
MON_META(ACH_MEDU,ACH_MEDU),
MON_META(ACID_RES,ACID_RES),
MON_META(AD_COLD,AD_COLD),
MON_META(AD_CORR,AD_CORR),
MON_META(AD_DCAY,AD_DCAY),
MON_META(AD_DGST,AD_DGST),
MON_META(AD_DRST,AD_DRST),
MON_META(AD_ELEC,AD_ELEC),
MON_META(AD_FIRE,AD_FIRE),
MON_META(AD_POLY,AD_POLY),
MON_META(AD_RBRE,AD_RBRE),
MON_META(AD_RUST,AD_RUST),
MON_META(AD_SEDU,AD_SEDU),
MON_META(AD_SPEL,AD_SPEL),
MON_META(AD_SSEX,AD_SSEX),
MON_META(AD_STCK,AD_STCK),
MON_META(ALLOW_ALL,ALLOW_ALL),
MON_META(ALLOW_BARS,ALLOW_BARS),
MON_META(ALLOW_DIG,ALLOW_DIG),
MON_META(ALLOW_M,ALLOW_M),
MON_META(ALLOW_MDISP,ALLOW_MDISP),
MON_META(ALLOW_ROCK,ALLOW_ROCK),
MON_META(ALLOW_SANCT,ALLOW_SANCT),
MON_META(ALLOW_SSM,ALLOW_SSM),
MON_META(ALLOW_TM,ALLOW_TM),
MON_META(ALLOW_TRAPS,ALLOW_TRAPS),
MON_META(ALLOW_U,ALLOW_U),
MON_META(ALLOW_WALL,ALLOW_WALL),
MON_META(AMULET_OF_LIFE_SAVING,AMULET_OF_LIFE_SAVING),
MON_META(AMULET_OF_STRANGULATION,AMULET_OF_STRANGULATION),
MON_META(AM_CHAOTIC,AM_CHAOTIC),
MON_META(AM_LAWFUL,AM_LAWFUL),
MON_META(AM_MASK,AM_MASK),
MON_META(AM_NEUTRAL,AM_NEUTRAL),
MON_META(AM_SANCTUM,AM_SANCTUM),
MON_META(ARTICLE_A,ARTICLE_A),
MON_META(ARTICLE_NONE,ARTICLE_NONE),
MON_META(ARTICLE_THE,ARTICLE_THE),
MON_META(ARTICLE_YOUR,ARTICLE_YOUR),
MON_META(AT_BOOM,AT_BOOM),
MON_META(AT_BREA,AT_BREA),
MON_META(AT_ENGL,AT_ENGL),
MON_META(AT_EXPL,AT_EXPL),
MON_META(AT_GAZE,AT_GAZE),
MON_META(AT_HUGS,AT_HUGS),
MON_META(AT_MAGC,AT_MAGC),
MON_META(AT_WEAP,AT_WEAP),
MON_META(AUGMENT_IT,AUGMENT_IT),
MON_META(AXE,AXE),
MON_META(A_CHAOTIC,A_CHAOTIC),
MON_META(A_MAX,A_MAX),
MON_META(A_NONE,A_NONE),
MON_META(BATTLE_AXE,BATTLE_AXE),
MON_META(BELL_OF_OPENING,BELL_OF_OPENING),
MON_META(BLINDED,BLINDED),
MON_META(BOLT_LIM,BOLT_LIM),
MON_META(BOOMERANG,BOOMERANG),
MON_META(BOULDER,BOULDER),
MON_META(BUFSZ,BUFSZ),
MON_META(BULLWHIP,BULLWHIP),
MON_META(BUSTDOOR,BUSTDOOR),
MON_META(CARROT,CARROT),
MON_META(CLOVE_OF_GARLIC,CLOVE_OF_GARLIC),
MON_META(CLUB,CLUB),
MON_META(COIN_CLASS,COIN_CLASS),
MON_META(COLD_RES,COLD_RES),
MON_META(COLNO,COLNO),
MON_META(CONFLICT,CONFLICT),
MON_META(CONFUSION,CONFUSION),
MON_META(CORPSE,CORPSE),
MON_META(CORPSTAT_BURIED,CORPSTAT_BURIED),
MON_META(CORPSTAT_FEMALE,CORPSTAT_FEMALE),
MON_META(CORPSTAT_HISTORIC,CORPSTAT_HISTORIC),
MON_META(CORPSTAT_INIT,CORPSTAT_INIT),
MON_META(CORPSTAT_MALE,CORPSTAT_MALE),
MON_META(CORPSTAT_NONE,CORPSTAT_NONE),
MON_META(COULD_SEE,COULD_SEE),
MON_META(DEAF,DEAF),
MON_META(DISINT_RES,DISINT_RES),
MON_META(DISMOUNT_GENERIC,DISMOUNT_GENERIC),
MON_META(DISPLACED,DISPLACED),
MON_META(DOOR,DOOR),
MON_META(DWARVISH_MATTOCK,DWARVISH_MATTOCK),
MON_META(D_BROKEN,D_BROKEN),
MON_META(D_CLOSED,D_CLOSED),
MON_META(D_LOCKED,D_LOCKED),
MON_META(D_NODOOR,D_NODOOR),
MON_META(D_TRAPPED,D_TRAPPED),
MON_META(EGG,EGG),
MON_META(ELVEN_SPEAR,ELVEN_SPEAR),
MON_META(EXACT_NAME,EXACT_NAME),
MON_META(EXPL_FIERY,EXPL_FIERY),
MON_META(FAST,FAST),
MON_META(FIGURINE,FIGURINE),
MON_META(FIRE_RES,FIRE_RES),
MON_META(FIRST_GLASS_GEM,FIRST_GLASS_GEM),
MON_META(FLYING,FLYING),
MON_META(FOOD_CLASS,FOOD_CLASS),
MON_META(FOOD_RATION,FOOD_RATION),
MON_META(FOUNTAIN,FOUNTAIN),
MON_META(FREE_ACTION,FREE_ACTION),
MON_META(FROMOUTSIDE,FROMOUTSIDE),
MON_META(FUMBLING,FUMBLING),
MON_META(GEM_CLASS,GEM_CLASS),
MON_META(GLIB,GLIB),
MON_META(GLOB_OF_BLACK_PUDDING,GLOB_OF_BLACK_PUDDING),
MON_META(GLOB_OF_GREEN_SLIME,GLOB_OF_GREEN_SLIME),
MON_META(GLYPH_ALTAR_OFF,GLYPH_ALTAR_OFF),
MON_META(GLYPH_CMAP_A_OFF,GLYPH_CMAP_A_OFF),
MON_META(GLYPH_CMAP_B_OFF,GLYPH_CMAP_B_OFF),
MON_META(GLYPH_CMAP_C_OFF,GLYPH_CMAP_C_OFF),
MON_META(GLYPH_CMAP_GEH_OFF,GLYPH_CMAP_GEH_OFF),
MON_META(GLYPH_CMAP_KNOX_OFF,GLYPH_CMAP_KNOX_OFF),
MON_META(GLYPH_CMAP_MAIN_OFF,GLYPH_CMAP_MAIN_OFF),
MON_META(GLYPH_CMAP_MINES_OFF,GLYPH_CMAP_MINES_OFF),
MON_META(GLYPH_CMAP_SOKO_OFF,GLYPH_CMAP_SOKO_OFF),
MON_META(GLYPH_CMAP_STONE_OFF,GLYPH_CMAP_STONE_OFF),
MON_META(GLYPH_INVISIBLE,GLYPH_INVISIBLE),
MON_META(GLYPH_MON_FEM_OFF,GLYPH_MON_FEM_OFF),
MON_META(GLYPH_MON_MALE_OFF,GLYPH_MON_MALE_OFF),
MON_META(GOLD,GOLD),
MON_META(GOLD_PIECE,GOLD_PIECE),
MON_META(GPCOORDS_MAP,GPCOORDS_MAP),
MON_META(GPCOORDS_NONE,GPCOORDS_NONE),
MON_META(GRAPPLING_HOOK,GRAPPLING_HOOK),
MON_META(GRAY_DRAGON_SCALES,GRAY_DRAGON_SCALES),
MON_META(GRAY_DRAGON_SCALE_MAIL,GRAY_DRAGON_SCALE_MAIL),
MON_META(G_FREQ,G_FREQ),
MON_META(G_GENOD,G_GENOD),
MON_META(G_NOCORPSE,G_NOCORPSE),
MON_META(G_UNIQ,G_UNIQ),
MON_META(HALF_PHDAM,HALF_PHDAM),
MON_META(HALF_SPDAM,HALF_SPDAM),
MON_META(HALLUC,HALLUC),
MON_META(HALLUC_RES,HALLUC_RES),
MON_META(HIGH_PM,HIGH_PM),
MON_META(ICE_BOX,ICE_BOX),
MON_META(INTRINSIC,INTRINSIC),
MON_META(INVIS,INVIS),
MON_META(IN_SIGHT,IN_SIGHT),
MON_META(IRON,IRON),
MON_META(IRONBARS,IRONBARS),
MON_META(IRON_CHAIN,IRON_CHAIN),
MON_META(I_SPECIAL,I_SPECIAL),
MON_META(KILLED_BY_AN,KILLED_BY_AN),
MON_META(LARGEST_INT,LARGEST_INT),
MON_META(LAST_PROP,LAST_PROP),
MON_META(LAVAPOOL,LAVAPOOL),
MON_META(LAVAWALL,LAVAWALL),
MON_META(LEASH,LEASH),
MON_META(LEATHER_ARMOR,LEATHER_ARMOR),
MON_META(LEATHER_CLOAK,LEATHER_CLOAK),
MON_META(LEAVESTATUE,LEAVESTATUE),
MON_META(LEVITATION,LEVITATION),
MON_META(LL_ACHIEVE,LL_ACHIEVE),
MON_META(LL_CONDUCT,LL_CONDUCT),
MON_META(LL_KILLEDPET,LL_KILLEDPET),
MON_META(LL_UMONST,LL_UMONST),
MON_META(LONG_SWORD,LONG_SWORD),
MON_META(LOW_PM,LOW_PM),
MON_META(LS_MONSTER,LS_MONSTER),
MON_META(M1_ACID,M1_ACID),
MON_META(M1_AMORPHOUS,M1_AMORPHOUS),
MON_META(M1_AMPHIBIOUS,M1_AMPHIBIOUS),
MON_META(M1_ANIMAL,M1_ANIMAL),
MON_META(M1_BREATHLESS,M1_BREATHLESS),
MON_META(M1_CLING,M1_CLING),
MON_META(M1_CONCEAL,M1_CONCEAL),
MON_META(M1_FLY,M1_FLY),
MON_META(M1_HIDE,M1_HIDE),
MON_META(M1_HUMANOID,M1_HUMANOID),
MON_META(M1_MINDLESS,M1_MINDLESS),
MON_META(M1_NEEDPICK,M1_NEEDPICK),
MON_META(M1_NOEYES,M1_NOEYES),
MON_META(M1_NOHANDS,M1_NOHANDS),
MON_META(M1_NOHEAD,M1_NOHEAD),
MON_META(M1_NOLIMBS,M1_NOLIMBS),
MON_META(M1_NOTAKE,M1_NOTAKE),
MON_META(M1_OVIPAROUS,M1_OVIPAROUS),
MON_META(M1_REGEN,M1_REGEN),
MON_META(M1_SEE_INVIS,M1_SEE_INVIS),
MON_META(M1_SWIM,M1_SWIM),
MON_META(M1_TPORT,M1_TPORT),
MON_META(M1_TPORT_CNTRL,M1_TPORT_CNTRL),
MON_META(M1_TUNNEL,M1_TUNNEL),
MON_META(M1_UNSOLID,M1_UNSOLID),
MON_META(M1_WALLWALK,M1_WALLWALK),
MON_META(M2_COLLECT,M2_COLLECT),
MON_META(M2_DEMON,M2_DEMON),
MON_META(M2_DWARF,M2_DWARF),
MON_META(M2_ELF,M2_ELF),
MON_META(M2_FEMALE,M2_FEMALE),
MON_META(M2_GIANT,M2_GIANT),
MON_META(M2_GNOME,M2_GNOME),
MON_META(M2_HOSTILE,M2_HOSTILE),
MON_META(M2_HUMAN,M2_HUMAN),
MON_META(M2_JEWELS,M2_JEWELS),
MON_META(M2_MALE,M2_MALE),
MON_META(M2_MINION,M2_MINION),
MON_META(M2_NEUTER,M2_NEUTER),
MON_META(M2_NOPOLY,M2_NOPOLY),
MON_META(M2_ORC,M2_ORC),
MON_META(M2_ROCKTHROW,M2_ROCKTHROW),
MON_META(M2_SHAPESHIFTER,M2_SHAPESHIFTER),
MON_META(M2_STRONG,M2_STRONG),
MON_META(M2_UNDEAD,M2_UNDEAD),
MON_META(M2_WERE,M2_WERE),
MON_META(M3_COVETOUS,M3_COVETOUS),
MON_META(M3_DISPLACES,M3_DISPLACES),
MON_META(MAGICAL_BREATHING,MAGICAL_BREATHING),
MON_META(MAXMONNO,MAXMONNO),
MON_META(MAXTCHARS,MAXTCHARS),
MON_META(MAX_CARR_CAP,MAX_CARR_CAP),
MON_META(MFAST,MFAST),
MON_META(MIGR_APPROX_XY,MIGR_APPROX_XY),
MON_META(MIGR_RANDOM,MIGR_RANDOM),
MON_META(MITHRIL,MITHRIL),
MON_META(MOAT,MOAT),
MON_META(MON_DETACH,MON_DETACH),
MON_META(MON_ENDGAME_FREE,MON_ENDGAME_FREE),
MON_META(MON_ENDGAME_MIGR,MON_ENDGAME_MIGR),
MON_META(MON_FLOOR,MON_FLOOR),
MON_META(MON_LIMBO,MON_LIMBO),
MON_META(MON_MIGRATING,MON_MIGRATING),
MON_META(MON_OBLITERATE,MON_OBLITERATE),
MON_META(MON_OFFMAP,MON_OFFMAP),
MON_META(MR_STONE,MR_STONE),
MON_META(MSLOW,MSLOW),
MON_META(MS_GUARDIAN,MS_GUARDIAN),
MON_META(MS_LEADER,MS_LEADER),
MON_META(MS_NEMESIS,MS_NEMESIS),
MON_META(MS_SHRIEK,MS_SHRIEK),
MON_META(MZ_HUMAN,MZ_HUMAN),
MON_META(MZ_LARGE,MZ_LARGE),
MON_META(MZ_SMALL,MZ_SMALL),
MON_META(MZ_TINY,MZ_TINY),
MON_META(M_AP_FURNITURE,M_AP_FURNITURE),
MON_META(M_AP_MONSTER,M_AP_MONSTER),
MON_META(M_AP_NOTHING,M_AP_NOTHING),
MON_META(M_AP_OBJECT,M_AP_OBJECT),
MON_META(M_AP_TYPMASK,M_AP_TYPMASK),
MON_META(M_POISONGAS_BAD,M_POISONGAS_BAD),
MON_META(M_POISONGAS_MINOR,M_POISONGAS_MINOR),
MON_META(M_POISONGAS_OK,M_POISONGAS_OK),
MON_META(NATTK,NATTK),
MON_META(NC_SHOW_MSG,NC_SHOW_MSG),
MON_META(NC_VIA_WAND_OR_SPELL,NC_VIA_WAND_OR_SPELL),
MON_META(NEUTRAL,NEUTRAL),
MON_META(NOGARLIC,NOGARLIC),
MON_META(NON_PM,NON_PM),
MON_META(NORMAL_SPEED,NORMAL_SPEED),
MON_META(NOTONL,NOTONL),
MON_META(NO_GLYPH,NO_GLYPH),
MON_META(NO_MM_FLAGS,NO_MM_FLAGS),
MON_META(NO_NC_FLAGS,NO_NC_FLAGS),
MON_META(NO_WEAPON_WANTED,NO_WEAPON_WANTED),
MON_META(NUMMONS,NUMMONS),
MON_META(NUM_GLASS_GEMS,NUM_GLASS_GEMS),
MON_META(NUM_OBJECTS,NUM_OBJECTS),
MON_META(OBJ_BURIED,OBJ_BURIED),
MON_META(OBJ_FLOOR,OBJ_FLOOR),
MON_META(OBJ_FREE,OBJ_FREE),
MON_META(OBJ_INVENT,OBJ_INVENT),
MON_META(OBJ_MINVENT,OBJ_MINVENT),
MON_META(ONAME_NO_FLAGS,ONAME_NO_FLAGS),
MON_META(OPENDOOR,OPENDOOR),
MON_META(PICK_AXE,PICK_AXE),
MON_META(PIT,PIT),
MON_META(PLNMSG_GROWL,PLNMSG_GROWL),
MON_META(PLNMSG_HIDE_UNDER,PLNMSG_HIDE_UNDER),
MON_META(PM_ABBOT,PM_ABBOT),
MON_META(PM_ACOLYTE,PM_ACOLYTE),
MON_META(PM_AIR_ELEMENTAL,PM_AIR_ELEMENTAL),
MON_META(PM_APPRENTICE,PM_APPRENTICE),
MON_META(PM_ARCHEOLOGIST,PM_ARCHEOLOGIST),
MON_META(PM_ARCHON,PM_ARCHON),
MON_META(PM_ASMODEUS,PM_ASMODEUS),
MON_META(PM_ATTENDANT,PM_ATTENDANT),
MON_META(PM_BABY_GOLD_DRAGON,PM_BABY_GOLD_DRAGON),
MON_META(PM_BABY_PURPLE_WORM,PM_BABY_PURPLE_WORM),
MON_META(PM_BALROG,PM_BALROG),
MON_META(PM_BARBARIAN,PM_BARBARIAN),
MON_META(PM_BLACK_DRAGON,PM_BLACK_DRAGON),
MON_META(PM_BLACK_LIGHT,PM_BLACK_LIGHT),
MON_META(PM_BLACK_PUDDING,PM_BLACK_PUDDING),
MON_META(PM_BLACK_UNICORN,PM_BLACK_UNICORN),
MON_META(PM_BLUE_DRAGON,PM_BLUE_DRAGON),
MON_META(PM_BROWN_PUDDING,PM_BROWN_PUDDING),
MON_META(PM_CAVE_DWELLER,PM_CAVE_DWELLER),
MON_META(PM_CHAMELEON,PM_CHAMELEON),
MON_META(PM_CHICKATRICE,PM_CHICKATRICE),
MON_META(PM_CHIEFTAIN,PM_CHIEFTAIN),
MON_META(PM_CLAY_GOLEM,PM_CLAY_GOLEM),
MON_META(PM_CLERIC,PM_CLERIC),
MON_META(PM_COCKATRICE,PM_COCKATRICE),
MON_META(PM_DEATH,PM_DEATH),
MON_META(PM_DISPATER,PM_DISPATER),
MON_META(PM_DOPPELGANGER,PM_DOPPELGANGER),
MON_META(PM_DWARF,PM_DWARF),
MON_META(PM_DWARF_MUMMY,PM_DWARF_MUMMY),
MON_META(PM_DWARF_ZOMBIE,PM_DWARF_ZOMBIE),
MON_META(PM_ELF,PM_ELF),
MON_META(PM_ELF_MUMMY,PM_ELF_MUMMY),
MON_META(PM_ELF_ZOMBIE,PM_ELF_ZOMBIE),
MON_META(PM_ERINYS,PM_ERINYS),
MON_META(PM_ETTIN,PM_ETTIN),
MON_META(PM_ETTIN_MUMMY,PM_ETTIN_MUMMY),
MON_META(PM_ETTIN_ZOMBIE,PM_ETTIN_ZOMBIE),
MON_META(PM_FAMINE,PM_FAMINE),
MON_META(PM_FIRE_ELEMENTAL,PM_FIRE_ELEMENTAL),
MON_META(PM_FIRE_VORTEX,PM_FIRE_VORTEX),
MON_META(PM_FLAMING_SPHERE,PM_FLAMING_SPHERE),
MON_META(PM_FLESH_GOLEM,PM_FLESH_GOLEM),
MON_META(PM_FLOATING_EYE,PM_FLOATING_EYE),
MON_META(PM_FOG_CLOUD,PM_FOG_CLOUD),
MON_META(PM_GARGOYLE,PM_GARGOYLE),
MON_META(PM_GELATINOUS_CUBE,PM_GELATINOUS_CUBE),
MON_META(PM_GHOST,PM_GHOST),
MON_META(PM_GHOUL,PM_GHOUL),
MON_META(PM_GIANT,PM_GIANT),
MON_META(PM_GIANT_EEL,PM_GIANT_EEL),
MON_META(PM_GIANT_MIMIC,PM_GIANT_MIMIC),
MON_META(PM_GIANT_MUMMY,PM_GIANT_MUMMY),
MON_META(PM_GIANT_ZOMBIE,PM_GIANT_ZOMBIE),
MON_META(PM_GLASS_GOLEM,PM_GLASS_GOLEM),
MON_META(PM_GNOME,PM_GNOME),
MON_META(PM_GNOME_MUMMY,PM_GNOME_MUMMY),
MON_META(PM_GNOME_ZOMBIE,PM_GNOME_ZOMBIE),
MON_META(PM_GOLD_DRAGON,PM_GOLD_DRAGON),
MON_META(PM_GOLD_GOLEM,PM_GOLD_GOLEM),
MON_META(PM_GRAY_DRAGON,PM_GRAY_DRAGON),
MON_META(PM_GRAY_OOZE,PM_GRAY_OOZE),
MON_META(PM_GRAY_UNICORN,PM_GRAY_UNICORN),
MON_META(PM_GREEN_DRAGON,PM_GREEN_DRAGON),
MON_META(PM_GREEN_SLIME,PM_GREEN_SLIME),
MON_META(PM_GREMLIN,PM_GREMLIN),
MON_META(PM_GRID_BUG,PM_GRID_BUG),
MON_META(PM_GUIDE,PM_GUIDE),
MON_META(PM_HEALER,PM_HEALER),
MON_META(PM_HEZROU,PM_HEZROU),
MON_META(PM_HIGH_CLERIC,PM_HIGH_CLERIC),
MON_META(PM_HORNED_DEVIL,PM_HORNED_DEVIL),
MON_META(PM_HUMAN,PM_HUMAN),
MON_META(PM_HUMAN_MUMMY,PM_HUMAN_MUMMY),
MON_META(PM_HUMAN_WEREJACKAL,PM_HUMAN_WEREJACKAL),
MON_META(PM_HUMAN_WERERAT,PM_HUMAN_WERERAT),
MON_META(PM_HUMAN_WEREWOLF,PM_HUMAN_WEREWOLF),
MON_META(PM_HUMAN_ZOMBIE,PM_HUMAN_ZOMBIE),
MON_META(PM_HUNTER,PM_HUNTER),
MON_META(PM_IRON_GOLEM,PM_IRON_GOLEM),
MON_META(PM_JABBERWOCK,PM_JABBERWOCK),
MON_META(PM_JELLYFISH,PM_JELLYFISH),
MON_META(PM_KILLER_BEE,PM_KILLER_BEE),
MON_META(PM_KNIGHT,PM_KNIGHT),
MON_META(PM_KOBOLD,PM_KOBOLD),
MON_META(PM_KOBOLD_MUMMY,PM_KOBOLD_MUMMY),
MON_META(PM_KOBOLD_ZOMBIE,PM_KOBOLD_ZOMBIE),
MON_META(PM_LARGE_MIMIC,PM_LARGE_MIMIC),
MON_META(PM_LEATHER_GOLEM,PM_LEATHER_GOLEM),
MON_META(PM_LIZARD,PM_LIZARD),
MON_META(PM_LONG_WORM,PM_LONG_WORM),
MON_META(PM_LONG_WORM_TAIL,PM_LONG_WORM_TAIL),
MON_META(PM_MAIL_DAEMON,PM_MAIL_DAEMON),
MON_META(PM_MANES,PM_MANES),
MON_META(PM_MEDUSA,PM_MEDUSA),
MON_META(PM_MINOTAUR,PM_MINOTAUR),
MON_META(PM_MONK,PM_MONK),
MON_META(PM_NEANDERTHAL,PM_NEANDERTHAL),
MON_META(PM_NURSE,PM_NURSE),
MON_META(PM_ORANGE_DRAGON,PM_ORANGE_DRAGON),
MON_META(PM_ORC,PM_ORC),
MON_META(PM_ORCUS,PM_ORCUS),
MON_META(PM_ORC_MUMMY,PM_ORC_MUMMY),
MON_META(PM_ORC_ZOMBIE,PM_ORC_ZOMBIE),
MON_META(PM_OWLBEAR,PM_OWLBEAR),
MON_META(PM_PAGE,PM_PAGE),
MON_META(PM_PAPER_GOLEM,PM_PAPER_GOLEM),
MON_META(PM_PESTILENCE,PM_PESTILENCE),
MON_META(PM_PONY,PM_PONY),
MON_META(PM_PURPLE_WORM,PM_PURPLE_WORM),
MON_META(PM_PYROLISK,PM_PYROLISK),
MON_META(PM_QUEEN_BEE,PM_QUEEN_BEE),
MON_META(PM_RANGER,PM_RANGER),
MON_META(PM_RED_DRAGON,PM_RED_DRAGON),
MON_META(PM_ROGUE,PM_ROGUE),
MON_META(PM_ROPE_GOLEM,PM_ROPE_GOLEM),
MON_META(PM_ROSHI,PM_ROSHI),
MON_META(PM_ROTHE,PM_ROTHE),
MON_META(PM_RUST_MONSTER,PM_RUST_MONSTER),
MON_META(PM_SALAMANDER,PM_SALAMANDER),
MON_META(PM_SAMURAI,PM_SAMURAI),
MON_META(PM_SANDESTIN,PM_SANDESTIN),
MON_META(PM_SCORPION,PM_SCORPION),
MON_META(PM_SCORPIUS,PM_SCORPIUS),
MON_META(PM_SHOCKING_SPHERE,PM_SHOCKING_SPHERE),
MON_META(PM_SHRIEKER,PM_SHRIEKER),
MON_META(PM_SILVER_DRAGON,PM_SILVER_DRAGON),
MON_META(PM_SKELETON,PM_SKELETON),
MON_META(PM_SMALL_MIMIC,PM_SMALL_MIMIC),
MON_META(PM_STALKER,PM_STALKER),
MON_META(PM_STEAM_VORTEX,PM_STEAM_VORTEX),
MON_META(PM_STONE_GOLEM,PM_STONE_GOLEM),
MON_META(PM_STRAW_GOLEM,PM_STRAW_GOLEM),
MON_META(PM_STUDENT,PM_STUDENT),
MON_META(PM_THUG,PM_THUG),
MON_META(PM_TOURIST,PM_TOURIST),
MON_META(PM_VALKYRIE,PM_VALKYRIE),
MON_META(PM_VAMPIRE,PM_VAMPIRE),
MON_META(PM_VAMPIRE_BAT,PM_VAMPIRE_BAT),
MON_META(PM_VAMPIRE_LEADER,PM_VAMPIRE_LEADER),
MON_META(PM_VIOLET_FUNGUS,PM_VIOLET_FUNGUS),
MON_META(PM_VLAD_THE_IMPALER,PM_VLAD_THE_IMPALER),
MON_META(PM_VROCK,PM_VROCK),
MON_META(PM_WARRIOR,PM_WARRIOR),
MON_META(PM_WATCHMAN,PM_WATCHMAN),
MON_META(PM_WATCH_CAPTAIN,PM_WATCH_CAPTAIN),
MON_META(PM_WEREJACKAL,PM_WEREJACKAL),
MON_META(PM_WERERAT,PM_WERERAT),
MON_META(PM_WEREWOLF,PM_WEREWOLF),
MON_META(PM_WHITE_DRAGON,PM_WHITE_DRAGON),
MON_META(PM_WHITE_UNICORN,PM_WHITE_UNICORN),
MON_META(PM_WINGED_GARGOYLE,PM_WINGED_GARGOYLE),
MON_META(PM_WIZARD,PM_WIZARD),
MON_META(PM_WIZARD_OF_YENDOR,PM_WIZARD_OF_YENDOR),
MON_META(PM_WOLF,PM_WOLF),
MON_META(PM_WOOD_GOLEM,PM_WOOD_GOLEM),
MON_META(PM_WRAITH,PM_WRAITH),
MON_META(PM_XORN,PM_XORN),
MON_META(PM_YEENOGHU,PM_YEENOGHU),
MON_META(PM_YELLOW_DRAGON,PM_YELLOW_DRAGON),
MON_META(POISON_RES,POISON_RES),
MON_META(POOL,POOL),
MON_META(POTION_CLASS,POTION_CLASS),
MON_META(POT_HEALING,POT_HEALING),
MON_META(PRONOUN_HALLU,PRONOUN_HALLU),
MON_META(PROT_FROM_SHAPE_CHANGERS,PROT_FROM_SHAPE_CHANGERS),
MON_META(P_AXE,P_AXE),
MON_META(P_PICK_AXE,P_PICK_AXE),
MON_META(QBUFSZ,QBUFSZ),
MON_META(QUARTERSTAFF,QUARTERSTAFF),
MON_META(RANDOM_CLASS,RANDOM_CLASS),
MON_META(RIN_SLOW_DIGESTION,RIN_SLOW_DIGESTION),
MON_META(RLOC_MSG,RLOC_MSG),
MON_META(RLOC_NOMSG,RLOC_NOMSG),
MON_META(ROCK,ROCK),
MON_META(ROCK_CLASS,ROCK_CLASS),
MON_META(ROOM,ROOM),
MON_META(ROWNO,ROWNO),
MON_META(SADDLE,SADDLE),
MON_META(SCROLL_CLASS,SCROLL_CLASS),
MON_META(SCR_BLANK_PAPER,SCR_BLANK_PAPER),
MON_META(SCR_MAIL,SCR_MAIL),
MON_META(SCR_SCARE_MONSTER,SCR_SCARE_MONSTER),
MON_META(SEE_INVIS,SEE_INVIS),
MON_META(SHOCK_RES,SHOCK_RES),
MON_META(SHOPBASE,SHOPBASE),
MON_META(SICK,SICK),
MON_META(SICK_RES,SICK_RES),
MON_META(SILVER,SILVER),
MON_META(SLEEP_RES,SLEEP_RES),
MON_META(SLIMED,SLIMED),
MON_META(SMALL_SHIELD,SMALL_SHIELD),
MON_META(SPECIAL_PM,SPECIAL_PM),
MON_META(SPE_EXTRA_HEALING,SPE_EXTRA_HEALING),
MON_META(SPE_HEALING,SPE_HEALING),
MON_META(SPIKED_PIT,SPIKED_PIT),
MON_META(STATUE,STATUE),
MON_META(STOMACH,STOMACH),
MON_META(STONE,STONE),
MON_META(STONED,STONED),
MON_META(STONE_RES,STONE_RES),
MON_META(STRANGLED,STRANGLED),
MON_META(STRAT_WAITFORU,STRAT_WAITFORU),
MON_META(STRAT_WAITMASK,STRAT_WAITMASK),
MON_META(STUNNED,STUNNED),
MON_META(SUPPRESS_HALLUCINATION,SUPPRESS_HALLUCINATION),
MON_META(SUPPRESS_INVISIBLE,SUPPRESS_INVISIBLE),
MON_META(SUPPRESS_IT,SUPPRESS_IT),
MON_META(SUPPRESS_NAME,SUPPRESS_NAME),
MON_META(SUPPRESS_SADDLE,SUPPRESS_SADDLE),
MON_META(SWIMMING,SWIMMING),
MON_META(S_BAT,S_BAT),
MON_META(S_BLOB,S_BLOB),
MON_META(S_DOG,S_DOG),
MON_META(S_DRAGON,S_DRAGON),
MON_META(S_EEL,S_EEL),
MON_META(S_ELEMENTAL,S_ELEMENTAL),
MON_META(S_EYE,S_EYE),
MON_META(S_FUNGUS,S_FUNGUS),
MON_META(S_GHOST,S_GHOST),
MON_META(S_GIANT,S_GIANT),
MON_META(S_GNOME,S_GNOME),
MON_META(S_GOLEM,S_GOLEM),
MON_META(S_HUMAN,S_HUMAN),
MON_META(S_HUMANOID,S_HUMANOID),
MON_META(S_JELLY,S_JELLY),
MON_META(S_KOBOLD,S_KOBOLD),
MON_META(S_KOP,S_KOP),
MON_META(S_LICH,S_LICH),
MON_META(S_LIGHT,S_LIGHT),
MON_META(S_MIMIC,S_MIMIC),
MON_META(S_NYMPH,S_NYMPH),
MON_META(S_ORC,S_ORC),
MON_META(S_TROLL,S_TROLL),
MON_META(S_UNICORN,S_UNICORN),
MON_META(S_VAMPIRE,S_VAMPIRE),
MON_META(S_VORTEX,S_VORTEX),
MON_META(S_ZOMBIE,S_ZOMBIE),
MON_META(S_altar,S_altar),
MON_META(S_arrow_trap,S_arrow_trap),
MON_META(S_digbeam,S_digbeam),
MON_META(S_goodpos,S_goodpos),
MON_META(S_grave,S_grave),
MON_META(S_hcdoor,S_hcdoor),
MON_META(S_ndoor,S_ndoor),
MON_META(S_poisoncloud,S_poisoncloud),
MON_META(S_stone,S_stone),
MON_META(S_tree,S_tree),
MON_META(S_trwall,S_trwall),
MON_META(S_vcdoor,S_vcdoor),
MON_META(S_vwall,S_vwall),
MON_META(TAINT_AGE,TAINT_AGE),
MON_META(TELEPAT,TELEPAT),
MON_META(TELEP_TRAP,TELEP_TRAP),
MON_META(TEMPLE,TEMPLE),
MON_META(TIMEOUT,TIMEOUT),
MON_META(TIN,TIN),
MON_META(TOOL_CLASS,TOOL_CLASS),
MON_META(TRAPNUM,TRAPNUM),
MON_META(TREE,TREE),
MON_META(TRUE,TRUE),
MON_META(UNICORN_HORN,UNICORN_HORN),
MON_META(UNLOCKDOOR,UNLOCKDOOR),
MON_META(VOMITING,VOMITING),
MON_META(WATER,WATER),
MON_META(WEAPON_CLASS,WEAPON_CLASS),
MON_META(WOOD,WOOD),
MON_META(WORM_TOOTH,WORM_TOOTH),
MON_META(WOUNDED_LEGS,WOUNDED_LEGS),
MON_META(WT_HUMAN,WT_HUMAN),
MON_META(W_AMUL,W_AMUL),
MON_META(W_ARM,W_ARM),
MON_META(W_ARMG,W_ARMG),
MON_META(W_ARMS,W_ARMS),
MON_META(W_ART,W_ART),
MON_META(W_ARTI,W_ARTI),
MON_META(W_NONDIGGABLE,W_NONDIGGABLE),
MON_META(W_SADDLE,W_SADDLE),
MON_META(XKILL_GIVEMSG,XKILL_GIVEMSG),
MON_META(XKILL_NOCONDUCT,XKILL_NOCONDUCT),
MON_META(XKILL_NOCORPSE,XKILL_NOCORPSE),
MON_META(XKILL_NOMSG,XKILL_NOMSG),
MON_META(YELLOW_DRAGON_SCALES,YELLOW_DRAGON_SCALES),
MON_META(YELLOW_DRAGON_SCALE_MAIL,YELLOW_DRAGON_SCALE_MAIL),
MON_META(altar_chaotic,altar_chaotic),
MON_META(altar_lawful,altar_lawful),
MON_META(altar_neutral,altar_neutral),
MON_META(altar_other,altar_other),
MON_META(altar_unaligned,altar_unaligned),
};
_Static_assert(sizeof(void*)==8&&sizeof(long)==8&&sizeof(int)==4&&sizeof(coordxy)==2&&sizeof(boolean)==1,"MON ABI widths");
_Static_assert(sizeof(((struct monst*)0)->cham)==2,"mon_cham width");
_Static_assert(((__typeof__(((struct monst*)0)->cham))-1 < 0),"mon_cham signedness");
_Static_assert(sizeof(((struct monst*)0)->data)==8,"mon_data pointer width");
_Static_assert(sizeof(((struct monst*)0)->m_ap_type)==1,"mon_m_ap_type width");
_Static_assert(((__typeof__(((struct monst*)0)->m_ap_type))-1 > 0),"mon_m_ap_type signedness");
_Static_assert(sizeof(((struct monst*)0)->m_id)==4,"mon_m_id width");
_Static_assert(((__typeof__(((struct monst*)0)->m_id))-1 > 0),"mon_m_id signedness");
_Static_assert(sizeof(((struct monst*)0)->m_lev)==1,"mon_m_lev width");
_Static_assert(((__typeof__(((struct monst*)0)->m_lev))-1 > 0),"mon_m_lev signedness");
_Static_assert(sizeof(((struct monst*)0)->malign)==1,"mon_malign width");
_Static_assert(((__typeof__(((struct monst*)0)->malign))-1 < 0),"mon_malign signedness");
_Static_assert(sizeof(((struct monst*)0)->mappearance)==4,"mon_mappearance width");
_Static_assert(((__typeof__(((struct monst*)0)->mappearance))-1 > 0),"mon_mappearance signedness");
_Static_assert(sizeof(((struct monst*)0)->meating)==4,"mon_meating width");
_Static_assert(((__typeof__(((struct monst*)0)->meating))-1 < 0),"mon_meating signedness");
_Static_assert(sizeof(((struct monst*)0)->mextra)==8,"mon_mextra pointer width");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4,"mon_mhp width");
_Static_assert(((__typeof__(((struct monst*)0)->mhp))-1 < 0),"mon_mhp signedness");
_Static_assert(sizeof(((struct monst*)0)->mhpmax)==4,"mon_mhpmax width");
_Static_assert(((__typeof__(((struct monst*)0)->mhpmax))-1 < 0),"mon_mhpmax signedness");
_Static_assert(sizeof(((struct monst*)0)->mintrinsics)==2,"mon_mintrinsics width");
_Static_assert(((__typeof__(((struct monst*)0)->mintrinsics))-1 > 0),"mon_mintrinsics signedness");
_Static_assert(sizeof(((struct monst*)0)->minvent)==8,"mon_minvent pointer width");
_Static_assert(sizeof(((struct monst*)0)->misc_worn_check)==8,"mon_misc_worn_check width");
_Static_assert(((__typeof__(((struct monst*)0)->misc_worn_check))-1 < 0),"mon_misc_worn_check signedness");
_Static_assert(sizeof(((struct monst*)0)->mlstmv)==8,"mon_mlstmv width");
_Static_assert(((__typeof__(((struct monst*)0)->mlstmv))-1 < 0),"mon_mlstmv signedness");
_Static_assert(sizeof(((struct monst*)0)->mnum)==2,"mon_mnum width");
_Static_assert(((__typeof__(((struct monst*)0)->mnum))-1 < 0),"mon_mnum signedness");
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
_Static_assert(sizeof(((struct monst*)0)->mtrapseen)==8,"mon_mtrapseen width");
_Static_assert(((__typeof__(((struct monst*)0)->mtrapseen))-1 < 0),"mon_mtrapseen signedness");
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
_Static_assert(sizeof(((struct you*)0)->mh)==4,"you_mh width");
_Static_assert(((__typeof__(((struct you*)0)->mh))-1 < 0),"you_mh signedness");
_Static_assert(sizeof(((struct you*)0)->mhmax)==4,"you_mhmax width");
_Static_assert(((__typeof__(((struct you*)0)->mhmax))-1 < 0),"you_mhmax signedness");
_Static_assert(sizeof(((struct you*)0)->ublessed)==4,"you_ublessed width");
_Static_assert(((__typeof__(((struct you*)0)->ublessed))-1 < 0),"you_ublessed signedness");
_Static_assert(sizeof(((struct you*)0)->ugallop)==8,"you_ugallop width");
_Static_assert(((__typeof__(((struct you*)0)->ugallop))-1 < 0),"you_ugallop signedness");
_Static_assert(sizeof(((struct you*)0)->ugangr)==4,"you_ugangr width");
_Static_assert(((__typeof__(((struct you*)0)->ugangr))-1 < 0),"you_ugangr signedness");
_Static_assert(sizeof(((struct you*)0)->uhp)==4,"you_uhp width");
_Static_assert(((__typeof__(((struct you*)0)->uhp))-1 < 0),"you_uhp signedness");
_Static_assert(sizeof(((struct you*)0)->uhpmax)==4,"you_uhpmax width");
_Static_assert(((__typeof__(((struct you*)0)->uhpmax))-1 < 0),"you_uhpmax signedness");
_Static_assert(sizeof(((struct you*)0)->ulevel)==4,"you_ulevel width");
_Static_assert(((__typeof__(((struct you*)0)->ulevel))-1 < 0),"you_ulevel signedness");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4,"you_umonnum width");
_Static_assert(((__typeof__(((struct you*)0)->umonnum))-1 < 0),"you_umonnum signedness");
_Static_assert(sizeof(((struct you*)0)->umonster)==4,"you_umonster width");
_Static_assert(((__typeof__(((struct you*)0)->umonster))-1 < 0),"you_umonster signedness");
_Static_assert(sizeof((((struct you*)0)->uprops))/sizeof((((struct you*)0)->uprops)[0])==69,"you_uprops extent0");
_Static_assert(sizeof((((struct you*)0)->ushops))/sizeof((((struct you*)0)->ushops)[0])==5,"you_ushops extent0");
_Static_assert(sizeof((((struct you*)0)->ushops)[0])==1&&((__typeof__((((struct you*)0)->ushops)[0]))-1 < 0),"you_ushops element ABI");
_Static_assert(sizeof(((struct you*)0)->usteed)==8,"you_usteed pointer width");
_Static_assert(sizeof(((struct you*)0)->ustuck)==8,"you_ustuck pointer width");
_Static_assert(sizeof(((struct you*)0)->uswldtim)==4,"you_uswldtim width");
_Static_assert(((__typeof__(((struct you*)0)->uswldtim))-1 > 0),"you_uswldtim signedness");
_Static_assert(sizeof(((struct you*)0)->utotype)==1,"you_utotype width");
_Static_assert(((__typeof__(((struct you*)0)->utotype))-1 > 0),"you_utotype signedness");
_Static_assert(sizeof(((struct you*)0)->utrap)==4,"you_utrap width");
_Static_assert(((__typeof__(((struct you*)0)->utrap))-1 > 0),"you_utrap signedness");
_Static_assert(sizeof(((struct you*)0)->ux)==2,"you_ux width");
_Static_assert(((__typeof__(((struct you*)0)->ux))-1 < 0),"you_ux signedness");
_Static_assert(sizeof(((struct you*)0)->uy)==2,"you_uy width");
_Static_assert(((__typeof__(((struct you*)0)->uy))-1 < 0),"you_uy signedness");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8,"prop_blocked width");
_Static_assert(((__typeof__(((struct prop*)0)->blocked))-1 < 0),"prop_blocked signedness");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8,"prop_extrinsic width");
_Static_assert(((__typeof__(((struct prop*)0)->extrinsic))-1 < 0),"prop_extrinsic signedness");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8,"prop_intrinsic width");
_Static_assert(((__typeof__(((struct prop*)0)->intrinsic))-1 < 0),"prop_intrinsic signedness");
_Static_assert(sizeof(((struct obj*)0)->age)==8,"obj_age width");
_Static_assert(((__typeof__(((struct obj*)0)->age))-1 < 0),"obj_age signedness");
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
_Static_assert(sizeof(((struct obj*)0)->owt)==4,"obj_owt width");
_Static_assert(((__typeof__(((struct obj*)0)->owt))-1 > 0),"obj_owt signedness");
_Static_assert(sizeof(((struct obj*)0)->ox)==2,"obj_ox width");
_Static_assert(((__typeof__(((struct obj*)0)->ox))-1 < 0),"obj_ox signedness");
_Static_assert(sizeof(((struct obj*)0)->oy)==2,"obj_oy width");
_Static_assert(((__typeof__(((struct obj*)0)->oy))-1 < 0),"obj_oy signedness");
_Static_assert(sizeof(((struct obj*)0)->quan)==8,"obj_quan width");
_Static_assert(((__typeof__(((struct obj*)0)->quan))-1 < 0),"obj_quan signedness");
_Static_assert(sizeof(((struct obj*)0)->spe)==1,"obj_spe width");
_Static_assert(((__typeof__(((struct obj*)0)->spe))-1 < 0),"obj_spe signedness");
_Static_assert(sizeof(((struct obj*)0)->where)==1,"obj_where width");
_Static_assert(((__typeof__(((struct obj*)0)->where))-1 < 0),"obj_where signedness");
_Static_assert(sizeof(((struct instance_flags*)0)->debug_fuzzer)==1,"iflags_debug_fuzzer width");
_Static_assert(((__typeof__(((struct instance_flags*)0)->debug_fuzzer))-1 < 0),"iflags_debug_fuzzer signedness");
_Static_assert(sizeof(((struct instance_flags*)0)->getpos_coords)==4,"iflags_getpos_coords width");
_Static_assert(((__typeof__(((struct instance_flags*)0)->getpos_coords))-1 < 0),"iflags_getpos_coords signedness");
_Static_assert(sizeof(((struct instance_flags*)0)->last_msg)==4,"iflags_last_msg width");
_Static_assert(((__typeof__(((struct instance_flags*)0)->last_msg))-1 < 0),"iflags_last_msg signedness");
_Static_assert(sizeof(((struct instance_flags*)0)->mon_polycontrol)==1,"iflags_mon_polycontrol width");
_Static_assert(((__typeof__(((struct instance_flags*)0)->mon_polycontrol))-1 < 0),"iflags_mon_polycontrol signedness");
_Static_assert(sizeof(((struct instance_flags*)0)->mon_telecontrol)==1,"iflags_mon_telecontrol width");
_Static_assert(((__typeof__(((struct instance_flags*)0)->mon_telecontrol))-1 < 0),"iflags_mon_telecontrol signedness");
_Static_assert(sizeof(((struct instance_flags*)0)->purge_monsters)==4,"iflags_purge_monsters width");
_Static_assert(((__typeof__(((struct instance_flags*)0)->purge_monsters))-1 < 0),"iflags_purge_monsters signedness");
_Static_assert(sizeof(((struct instance_flags*)0)->returning_missile)==8,"iflags_returning_missile pointer width");
_Static_assert(sizeof(((struct instance_flags*)0)->sad_feeling)==1,"iflags_sad_feeling width");
_Static_assert(((__typeof__(((struct instance_flags*)0)->sad_feeling))-1 < 0),"iflags_sad_feeling signedness");
_Static_assert(sizeof(((struct instance_flags*)0)->sanity_check)==1,"iflags_sanity_check width");
_Static_assert(((__typeof__(((struct instance_flags*)0)->sanity_check))-1 < 0),"iflags_sanity_check signedness");
_Static_assert(sizeof(((struct c_common_strings*)0)->c_Something)==8,"strings_c_Something pointer width");
_Static_assert(sizeof(((struct c_common_strings*)0)->c_thats_enough_tries)==8,"strings_c_thats_enough_tries pointer width");
_Static_assert(sizeof(((struct u_conduct*)0)->killer)==8,"conduct_killer width");
_Static_assert(((__typeof__(((struct u_conduct*)0)->killer))-1 < 0),"conduct_killer signedness");
_Static_assert(sizeof(((struct flag*)0)->debug)==1,"flags_debug width");
_Static_assert(((__typeof__(((struct flag*)0)->debug))-1 < 0),"flags_debug signedness");
_Static_assert(sizeof(((struct flag*)0)->female)==1,"flags_female width");
_Static_assert(((__typeof__(((struct flag*)0)->female))-1 < 0),"flags_female signedness");
_Static_assert(sizeof(((struct flag*)0)->sparkle)==1,"flags_sparkle width");
_Static_assert(((__typeof__(((struct flag*)0)->sparkle))-1 < 0),"flags_sparkle signedness");
_Static_assert(sizeof(((struct flag*)0)->verbose)==1,"flags_verbose width");
_Static_assert(((__typeof__(((struct flag*)0)->verbose))-1 < 0),"flags_verbose signedness");
_Static_assert(sizeof(((struct dgn_topology*)0)->d_sokoban_dnum)==2,"topology_d_sokoban_dnum width");
_Static_assert(((__typeof__(((struct dgn_topology*)0)->d_sokoban_dnum))-1 < 0),"topology_d_sokoban_dnum signedness");
_Static_assert(sizeof(((struct instance_globals_v*)0)->vamp_rise_msg)==1,"gv_vamp_rise_msg width");
_Static_assert(((__typeof__(((struct instance_globals_v*)0)->vamp_rise_msg))-1 < 0),"gv_vamp_rise_msg signedness");
_Static_assert(sizeof(((struct instance_globals_v*)0)->vision_full_recalc)==1,"gv_vision_full_recalc width");
_Static_assert(((__typeof__(((struct instance_globals_v*)0)->vision_full_recalc))-1 < 0),"gv_vision_full_recalc signedness");
_Static_assert(sizeof(((struct instance_globals_v*)0)->viz_array)==8,"gv_viz_array pointer width");
_Static_assert(sizeof(((struct instance_globals_saved_m*)0)->moves)==8,"svm_moves width");
_Static_assert(((__typeof__(((struct instance_globals_saved_m*)0)->moves))-1 < 0),"svm_moves signedness");
_Static_assert(sizeof((((struct instance_globals_saved_m*)0)->mvitals))/sizeof((((struct instance_globals_saved_m*)0)->mvitals)[0])==383,"svm_mvitals extent0");
_Static_assert(sizeof(((struct Role*)0)->guardnum)==2,"role_guardnum width");
_Static_assert(((__typeof__(((struct Role*)0)->guardnum))-1 < 0),"role_guardnum signedness");
_Static_assert(sizeof(((struct Role*)0)->mnum)==2,"role_mnum width");
_Static_assert(((__typeof__(((struct Role*)0)->mnum))-1 < 0),"role_mnum signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_color)==1,"cls_oc_color width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_color))-1 > 0),"cls_oc_color signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_descr_idx)==2,"cls_oc_descr_idx width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_descr_idx))-1 < 0),"cls_oc_descr_idx signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_subtyp)==1,"cls_oc_subtyp width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_subtyp))-1 < 0),"cls_oc_subtyp signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_weight)==4,"cls_oc_weight width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_weight))-1 > 0),"cls_oc_weight signedness");
_Static_assert(sizeof(((struct permonst*)0)->cwt)==4,"pm_cwt width");
_Static_assert(((__typeof__(((struct permonst*)0)->cwt))-1 > 0),"pm_cwt signedness");
_Static_assert(sizeof(((struct permonst*)0)->difficulty)==1,"pm_difficulty width");
_Static_assert(((__typeof__(((struct permonst*)0)->difficulty))-1 > 0),"pm_difficulty signedness");
_Static_assert(sizeof(((struct permonst*)0)->geno)==2,"pm_geno width");
_Static_assert(((__typeof__(((struct permonst*)0)->geno))-1 > 0),"pm_geno signedness");
_Static_assert(sizeof(((struct permonst*)0)->maligntyp)==1,"pm_maligntyp width");
_Static_assert(((__typeof__(((struct permonst*)0)->maligntyp))-1 < 0),"pm_maligntyp signedness");
_Static_assert(sizeof((((struct permonst*)0)->mattk))/sizeof((((struct permonst*)0)->mattk)[0])==6,"pm_mattk extent0");
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
_Static_assert(sizeof(((struct permonst*)0)->mresists)==1,"pm_mresists width");
_Static_assert(((__typeof__(((struct permonst*)0)->mresists))-1 > 0),"pm_mresists signedness");
_Static_assert(sizeof(((struct permonst*)0)->msize)==1,"pm_msize width");
_Static_assert(((__typeof__(((struct permonst*)0)->msize))-1 > 0),"pm_msize signedness");
_Static_assert(sizeof(((struct permonst*)0)->msound)==1,"pm_msound width");
_Static_assert(((__typeof__(((struct permonst*)0)->msound))-1 > 0),"pm_msound signedness");
_Static_assert(sizeof(((struct permonst*)0)->pmidx)==4,"pm_pmidx width");
_Static_assert(((__typeof__(((struct permonst*)0)->pmidx))-1 < 0),"pm_pmidx signedness");
_Static_assert(sizeof((((struct permonst*)0)->pmnames))/sizeof((((struct permonst*)0)->pmnames)[0])==3,"pm_pmnames extent0");
_Static_assert(sizeof(((struct mvitals*)0)->died)==1,"vital_died width");
_Static_assert(((__typeof__(((struct mvitals*)0)->died))-1 > 0),"vital_died signedness");
_Static_assert(sizeof(((struct mvitals*)0)->mvflags)==1,"vital_mvflags width");
_Static_assert(((__typeof__(((struct mvitals*)0)->mvflags))-1 > 0),"vital_mvflags signedness");
_Static_assert(sizeof(((struct instance_globals_m*)0)->migrating_mons)==8,"gm_migrating_mons pointer width");
_Static_assert(sizeof(((struct instance_globals_m*)0)->migrating_objs)==8,"gm_migrating_objs pointer width");
_Static_assert(sizeof(((struct instance_globals_m*)0)->mswallower)==8,"gm_mswallower pointer width");
_Static_assert(sizeof(((struct instance_globals_m*)0)->multi)==8,"gm_multi width");
_Static_assert(((__typeof__(((struct instance_globals_m*)0)->multi))-1 < 0),"gm_multi signedness");
_Static_assert(sizeof(((struct d_level*)0)->dlevel)==2,"level_dlevel width");
_Static_assert(((__typeof__(((struct d_level*)0)->dlevel))-1 < 0),"level_dlevel signedness");
_Static_assert(sizeof(((struct d_level*)0)->dnum)==2,"level_dnum width");
_Static_assert(((__typeof__(((struct d_level*)0)->dnum))-1 < 0),"level_dnum signedness");
_Static_assert(sizeof(((struct rm*)0)->glyph)==4,"rm_glyph width");
_Static_assert(((__typeof__(((struct rm*)0)->glyph))-1 < 0),"rm_glyph signedness");
_Static_assert(sizeof(((struct rm*)0)->typ)==1,"rm_typ width");
_Static_assert(((__typeof__(((struct rm*)0)->typ))-1 < 0),"rm_typ signedness");
_Static_assert(sizeof(((struct u_roleplay*)0)->deaf)==1,"roleplay_deaf width");
_Static_assert(((__typeof__(((struct u_roleplay*)0)->deaf))-1 < 0),"roleplay_deaf signedness");
_Static_assert(sizeof(((struct instance_globals_n*)0)->notonhead)==1,"gn_notonhead width");
_Static_assert(((__typeof__(((struct instance_globals_n*)0)->notonhead))-1 < 0),"gn_notonhead signedness");
_Static_assert(sizeof(((struct Gender*)0)->he)==8,"gender_he pointer width");
_Static_assert(sizeof(((struct Gender*)0)->him)==8,"gender_him pointer width");
_Static_assert(sizeof(((struct Gender*)0)->his)==8,"gender_his pointer width");
_Static_assert(sizeof(((struct stairway*)0)->sx)==2,"stair_sx width");
_Static_assert(((__typeof__(((struct stairway*)0)->sx))-1 < 0),"stair_sx signedness");
_Static_assert(sizeof(((struct stairway*)0)->sy)==2,"stair_sy width");
_Static_assert(((__typeof__(((struct stairway*)0)->sy))-1 < 0),"stair_sy signedness");
_Static_assert(sizeof(((struct align*)0)->abuse)==4,"align_abuse width");
_Static_assert(((__typeof__(((struct align*)0)->abuse))-1 > 0),"align_abuse signedness");
_Static_assert(sizeof(((struct align*)0)->record)==4,"align_record width");
_Static_assert(((__typeof__(((struct align*)0)->record))-1 < 0),"align_record signedness");
_Static_assert(sizeof(((struct align*)0)->type)==1,"align_type width");
_Static_assert(((__typeof__(((struct align*)0)->type))-1 < 0),"align_type signedness");
_Static_assert(sizeof(((struct context_info*)0)->bypasses)==1,"context_bypasses width");
_Static_assert(((__typeof__(((struct context_info*)0)->bypasses))-1 < 0),"context_bypasses signedness");
_Static_assert(sizeof(((struct context_info*)0)->forcefight)==1,"context_forcefight width");
_Static_assert(((__typeof__(((struct context_info*)0)->forcefight))-1 < 0),"context_forcefight signedness");
_Static_assert(sizeof(((struct context_info*)0)->mon_moving)==1,"context_mon_moving width");
_Static_assert(((__typeof__(((struct context_info*)0)->mon_moving))-1 < 0),"context_mon_moving signedness");
_Static_assert(sizeof(((struct context_info*)0)->mv)==1,"context_mv width");
_Static_assert(((__typeof__(((struct context_info*)0)->mv))-1 < 0),"context_mv signedness");
_Static_assert(sizeof(((struct context_info*)0)->startingpet_mid)==4,"context_startingpet_mid width");
_Static_assert(((__typeof__(((struct context_info*)0)->startingpet_mid))-1 > 0),"context_startingpet_mid signedness");
_Static_assert(sizeof(((struct context_info*)0)->startingpet_typ)==4,"context_startingpet_typ width");
_Static_assert(((__typeof__(((struct context_info*)0)->startingpet_typ))-1 < 0),"context_startingpet_typ signedness");
_Static_assert(sizeof(((struct display_hints*)0)->botl)==1,"disp_botl width");
_Static_assert(((__typeof__(((struct display_hints*)0)->botl))-1 < 0),"disp_botl signedness");
_Static_assert(sizeof(((struct Race*)0)->mnum)==2,"race_mnum width");
_Static_assert(((__typeof__(((struct Race*)0)->mnum))-1 < 0),"race_mnum signedness");
_Static_assert(sizeof(((struct Race*)0)->selfmask)==2,"race_selfmask width");
_Static_assert(((__typeof__(((struct Race*)0)->selfmask))-1 < 0),"race_selfmask signedness");
_Static_assert(sizeof(((struct instance_globals_i*)0)->in_mklev)==1,"gi_in_mklev width");
_Static_assert(((__typeof__(((struct instance_globals_i*)0)->in_mklev))-1 < 0),"gi_in_mklev signedness");
_Static_assert(sizeof(((struct instance_globals_i*)0)->invent)==8,"gi_invent pointer width");
_Static_assert(sizeof(((struct attack*)0)->aatyp)==1,"attack_aatyp width");
_Static_assert(((__typeof__(((struct attack*)0)->aatyp))-1 > 0),"attack_aatyp signedness");
_Static_assert(sizeof(((struct attack*)0)->adtyp)==1,"attack_adtyp width");
_Static_assert(((__typeof__(((struct attack*)0)->adtyp))-1 > 0),"attack_adtyp signedness");
_Static_assert(sizeof(((struct attack*)0)->damd)==1,"attack_damd width");
_Static_assert(((__typeof__(((struct attack*)0)->damd))-1 > 0),"attack_damd signedness");
_Static_assert(sizeof(((struct attack*)0)->damn)==1,"attack_damn width");
_Static_assert(((__typeof__(((struct attack*)0)->damn))-1 > 0),"attack_damn signedness");
_Static_assert(sizeof(((struct nhcoord*)0)->x)==2,"coord_x width");
_Static_assert(((__typeof__(((struct nhcoord*)0)->x))-1 < 0),"coord_x signedness");
_Static_assert(sizeof(((struct nhcoord*)0)->y)==2,"coord_y width");
_Static_assert(((__typeof__(((struct nhcoord*)0)->y))-1 < 0),"coord_y signedness");
_Static_assert(sizeof((((struct kinfo*)0)->name))/sizeof((((struct kinfo*)0)->name)[0])==256,"killer_name extent0");
_Static_assert(sizeof((((struct kinfo*)0)->name)[0])==1&&((__typeof__((((struct kinfo*)0)->name)[0]))-1 < 0),"killer_name element ABI");
_Static_assert(sizeof(((struct mextra*)0)->ebones)==8,"mextra_ebones pointer width");
_Static_assert(sizeof(((struct mextra*)0)->edog)==8,"mextra_edog pointer width");
_Static_assert(sizeof(((struct mextra*)0)->egd)==8,"mextra_egd pointer width");
_Static_assert(sizeof(((struct mextra*)0)->emin)==8,"mextra_emin pointer width");
_Static_assert(sizeof(((struct mextra*)0)->epri)==8,"mextra_epri pointer width");
_Static_assert(sizeof(((struct mextra*)0)->eshk)==8,"mextra_eshk pointer width");
_Static_assert(sizeof(((struct mextra*)0)->mcorpsenm)==4,"mextra_mcorpsenm width");
_Static_assert(((__typeof__(((struct mextra*)0)->mcorpsenm))-1 < 0),"mextra_mcorpsenm signedness");
_Static_assert(sizeof(((struct mextra*)0)->mgivenname)==8,"mextra_mgivenname pointer width");
_Static_assert(sizeof(((struct edog*)0)->droptime)==8,"edog_droptime width");
_Static_assert(((__typeof__(((struct edog*)0)->droptime))-1 < 0),"edog_droptime signedness");
_Static_assert(sizeof(((struct edog*)0)->whistletime)==8,"edog_whistletime width");
_Static_assert(((__typeof__(((struct edog*)0)->whistletime))-1 < 0),"edog_whistletime signedness");
_Static_assert(sizeof(((struct eshk*)0)->shoptype)==4,"eshk_shoptype width");
_Static_assert(((__typeof__(((struct eshk*)0)->shoptype))-1 < 0),"eshk_shoptype signedness");
_Static_assert(sizeof(((struct mfndposdata*)0)->cnt)==4,"mfp_cnt width");
_Static_assert(((__typeof__(((struct mfndposdata*)0)->cnt))-1 < 0),"mfp_cnt signedness");
_Static_assert(sizeof((((struct mfndposdata*)0)->info))/sizeof((((struct mfndposdata*)0)->info)[0])==9,"mfp_info extent0");
_Static_assert(sizeof((((struct mfndposdata*)0)->info)[0])==8&&((__typeof__((((struct mfndposdata*)0)->info)[0]))-1 < 0),"mfp_info element ABI");
_Static_assert(sizeof((((struct mfndposdata*)0)->poss))/sizeof((((struct mfndposdata*)0)->poss)[0])==9,"mfp_poss extent0");
_Static_assert(sizeof(((struct class_sym*)0)->sym)==1,"classsym_sym width");
_Static_assert(((__typeof__(((struct class_sym*)0)->sym))-1 < 0),"classsym_sym signedness");
_Static_assert(sizeof(((struct shclass*)0)->name)==8,"shclass_name pointer width");
_Static_assert(sizeof(((struct sinfo*)0)->done_hup)==4,"sinfo_done_hup width");
_Static_assert(((__typeof__(((struct sinfo*)0)->done_hup))-1 < 0),"sinfo_done_hup signedness");
_Static_assert(sizeof(((struct q_score*)0)->leader_m_id)==4,"q_score_leader_m_id width");
_Static_assert(((__typeof__(((struct q_score*)0)->leader_m_id))-1 > 0),"q_score_leader_m_id signedness");
_Static_assert(sizeof(((struct lifelists*)0)->total_photographed)==8,"lifelists_total_photographed width");
_Static_assert(((__typeof__(((struct lifelists*)0)->total_photographed))-1 < 0),"lifelists_total_photographed signedness");
_Static_assert(sizeof(((struct lifelists*)0)->total_seen_upclose)==8,"lifelists_total_seen_upclose width");
_Static_assert(((__typeof__(((struct lifelists*)0)->total_seen_upclose))-1 < 0),"lifelists_total_seen_upclose signedness");
_Static_assert(sizeof(((struct instance_globals_z*)0)->zombify)==1,"gz_zombify width");
_Static_assert(((__typeof__(((struct instance_globals_z*)0)->zombify))-1 < 0),"gz_zombify signedness");
_Static_assert(sizeof(((struct instance_globals_t*)0)->thrownobj)==8,"gt_thrownobj pointer width");
_Static_assert(sizeof(((struct instance_globals_a*)0)->animal_list)==8,"ga_animal_list pointer width");
_Static_assert(sizeof(((struct instance_globals_a*)0)->animal_list_count)==4,"ga_animal_list_count width");
_Static_assert(((__typeof__(((struct instance_globals_a*)0)->animal_list_count))-1 < 0),"ga_animal_list_count signedness");
_Static_assert(sizeof(((struct instance_globals_s*)0)->somebody_can_move)==1,"gs_somebody_can_move width");
_Static_assert(((__typeof__(((struct instance_globals_s*)0)->somebody_can_move))-1 < 0),"gs_somebody_can_move signedness");
_Static_assert(sizeof(((struct instance_globals_s*)0)->stealmid)==4,"gs_stealmid width");
_Static_assert(((__typeof__(((struct instance_globals_s*)0)->stealmid))-1 > 0),"gs_stealmid signedness");
_Static_assert(sizeof(((struct instance_globals_s*)0)->stoned)==1,"gs_stoned width");
_Static_assert(((__typeof__(((struct instance_globals_s*)0)->stoned))-1 < 0),"gs_stoned signedness");
_Static_assert(sizeof(((struct achievement_tracking*)0)->mines_prize_oid)==4,"achievement_tracking_mines_prize_oid width");
_Static_assert(((__typeof__(((struct achievement_tracking*)0)->mines_prize_oid))-1 > 0),"achievement_tracking_mines_prize_oid signedness");
_Static_assert(sizeof(((struct achievement_tracking*)0)->soko_prize_oid)==4,"achievement_tracking_soko_prize_oid width");
_Static_assert(((__typeof__(((struct achievement_tracking*)0)->soko_prize_oid))-1 > 0),"achievement_tracking_soko_prize_oid signedness");
_Static_assert(sizeof(((struct polearm_info*)0)->hitmon)==8,"polearm_info_hitmon pointer width");
_Static_assert(sizeof(((struct instance_globals_l*)0)->last_hider)==4,"gl_last_hider width");
_Static_assert(((__typeof__(((struct instance_globals_l*)0)->last_hider))-1 > 0),"gl_last_hider signedness");
_Static_assert(sizeof(((struct instance_globals_d*)0)->disintegested)==1,"gd_disintegested width");
_Static_assert(((__typeof__(((struct instance_globals_d*)0)->disintegested))-1 < 0),"gd_disintegested signedness");
_Static_assert(sizeof(((NhRegion*)0)->glyph)==4,"region_glyph width");
_Static_assert(((__typeof__(((NhRegion*)0)->glyph))-1 < 0),"region_glyph signedness");
_Static_assert(sizeof(((__typeof__(svl.level)*)0)->buriedobjlist)==8,"dlevel_buriedobjlist pointer width");
_Static_assert(sizeof((((__typeof__(svl.level)*)0)->locations))/sizeof((((__typeof__(svl.level)*)0)->locations)[0])==80,"dlevel_locations extent0");
_Static_assert(sizeof((((__typeof__(svl.level)*)0)->locations)[0])/sizeof((((__typeof__(svl.level)*)0)->locations)[0][0])==21,"dlevel_locations extent1");
_Static_assert(sizeof(((__typeof__(svl.level)*)0)->monlist)==8,"dlevel_monlist pointer width");
_Static_assert(sizeof((((__typeof__(svl.level)*)0)->monsters))/sizeof((((__typeof__(svl.level)*)0)->monsters)[0])==80,"dlevel_monsters extent0");
_Static_assert(sizeof((((__typeof__(svl.level)*)0)->monsters)[0])/sizeof((((__typeof__(svl.level)*)0)->monsters)[0][0])==21,"dlevel_monsters extent1");
_Static_assert(sizeof((((__typeof__(svl.level)*)0)->objects))/sizeof((((__typeof__(svl.level)*)0)->objects)[0])==80,"dlevel_objects extent0");
_Static_assert(sizeof((((__typeof__(svl.level)*)0)->objects)[0])/sizeof((((__typeof__(svl.level)*)0)->objects)[0][0])==21,"dlevel_objects extent1");
_Static_assert(sizeof(((__typeof__(svl.level)*)0)->objlist)==8,"dlevel_objlist pointer width");
_Static_assert(__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__,"MON little endian ABI");
#if !defined(DEBUG)||!defined(SAFERHANGUP)||!defined(MAIL_STRUCTURES)||defined(EDIT_GETLIN)||defined(SND_LIB_INTEGRATED)||NH_DEVEL_STATUS!=NH_STATUS_RELEASED
#error Review configured MON profile
#endif
size_t probe_context_size(void){return sizeof(struct monst);}
int probe_layout_count(void){return sizeof teleport_mon_layout/sizeof teleport_mon_layout[0];}
const char*probe_layout_name(int i){return teleport_mon_layout[i].name;}
size_t probe_layout_value(int i){return teleport_mon_layout[i].value;}
#endif
