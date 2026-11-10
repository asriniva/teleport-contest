/* POTION compiler-derived fields and ABI guards; no potion policy. */
#ifndef TELEPORT_POTION_LAYOUT_H
#define TELEPORT_POTION_LAYOUT_H
#include "hack.h"
#include <stddef.h>
#define POTION_META(k,v) {#k,(size_t)(v)}
static const struct {const char*name;size_t value;}teleport_potion_layout[]={
POTION_META(pointerSize,sizeof(void*)),
POTION_META(intSize,sizeof(int)),
POTION_META(longSize,sizeof(long)),
POTION_META(coordxySize,sizeof(coordxy)),
POTION_META(booleanSize,sizeof(boolean)),
POTION_META(objSize,sizeof(struct obj)),
POTION_META(dipPromptSize,sizeof "What do you want to dip into? [abdeghjkmnpqstvwyzBCEFHIKLNOQRTUWXZ#-# or ?*] "),
POTION_META(monSize,sizeof(struct monst)),
POTION_META(mon_cham,offsetof(struct monst,cham)),
POTION_META(mon_cham_size,sizeof(((struct monst*)0)->cham)),
POTION_META(mon_data,offsetof(struct monst,data)),
POTION_META(mon_data_size,sizeof(((struct monst*)0)->data)),
POTION_META(mon_m_ap_type,offsetof(struct monst,m_ap_type)),
POTION_META(mon_m_ap_type_size,sizeof(((struct monst*)0)->m_ap_type)),
POTION_META(mon_mappearance,offsetof(struct monst,mappearance)),
POTION_META(mon_mappearance_size,sizeof(((struct monst*)0)->mappearance)),
POTION_META(mon_mhp,offsetof(struct monst,mhp)),
POTION_META(mon_mhp_size,sizeof(((struct monst*)0)->mhp)),
POTION_META(mon_mhpmax,offsetof(struct monst,mhpmax)),
POTION_META(mon_mhpmax_size,sizeof(((struct monst*)0)->mhpmax)),
POTION_META(mon_misc_worn_check,offsetof(struct monst,misc_worn_check)),
POTION_META(mon_misc_worn_check_size,sizeof(((struct monst*)0)->misc_worn_check)),
POTION_META(mon_mx,offsetof(struct monst,mx)),
POTION_META(mon_mx_size,sizeof(((struct monst*)0)->mx)),
POTION_META(mon_my,offsetof(struct monst,my)),
POTION_META(mon_my_size,sizeof(((struct monst*)0)->my)),
POTION_META(youSize,sizeof(struct you)),
POTION_META(you_acurr,offsetof(struct you,acurr)),
POTION_META(you_acurr_size,sizeof(((struct you*)0)->acurr)),
POTION_META(you_aexe,offsetof(struct you,aexe)),
POTION_META(you_aexe_size,sizeof(((struct you*)0)->aexe)),
POTION_META(you_amax,offsetof(struct you,amax)),
POTION_META(you_amax_size,sizeof(((struct you*)0)->amax)),
POTION_META(you_mh,offsetof(struct you,mh)),
POTION_META(you_mh_size,sizeof(((struct you*)0)->mh)),
POTION_META(you_mhmax,offsetof(struct you,mhmax)),
POTION_META(you_mhmax_size,sizeof(((struct you*)0)->mhmax)),
POTION_META(you_mtimedone,offsetof(struct you,mtimedone)),
POTION_META(you_mtimedone_size,sizeof(((struct you*)0)->mtimedone)),
POTION_META(you_ualign,offsetof(struct you,ualign)),
POTION_META(you_ualign_size,sizeof(((struct you*)0)->ualign)),
POTION_META(you_uconduct,offsetof(struct you,uconduct)),
POTION_META(you_uconduct_size,sizeof(((struct you*)0)->uconduct)),
POTION_META(you_ucreamed,offsetof(struct you,ucreamed)),
POTION_META(you_ucreamed_size,sizeof(((struct you*)0)->ucreamed)),
POTION_META(you_uen,offsetof(struct you,uen)),
POTION_META(you_uen_size,sizeof(((struct you*)0)->uen)),
POTION_META(you_uenmax,offsetof(struct you,uenmax)),
POTION_META(you_uenmax_size,sizeof(((struct you*)0)->uenmax)),
POTION_META(you_uenpeak,offsetof(struct you,uenpeak)),
POTION_META(you_uenpeak_size,sizeof(((struct you*)0)->uenpeak)),
POTION_META(you_uexp,offsetof(struct you,uexp)),
POTION_META(you_uexp_size,sizeof(((struct you*)0)->uexp)),
POTION_META(you_uhave,offsetof(struct you,uhave)),
POTION_META(you_uhave_size,sizeof(((struct you*)0)->uhave)),
POTION_META(you_uhp,offsetof(struct you,uhp)),
POTION_META(you_uhp_size,sizeof(((struct you*)0)->uhp)),
POTION_META(you_uhpmax,offsetof(struct you,uhpmax)),
POTION_META(you_uhpmax_size,sizeof(((struct you*)0)->uhpmax)),
POTION_META(you_uhppeak,offsetof(struct you,uhppeak)),
POTION_META(you_uhppeak_size,sizeof(((struct you*)0)->uhppeak)),
POTION_META(you_uhs,offsetof(struct you,uhs)),
POTION_META(you_uhs_size,sizeof(((struct you*)0)->uhs)),
POTION_META(you_uhunger,offsetof(struct you,uhunger)),
POTION_META(you_uhunger_size,sizeof(((struct you*)0)->uhunger)),
POTION_META(you_ulevel,offsetof(struct you,ulevel)),
POTION_META(you_ulevel_size,sizeof(((struct you*)0)->ulevel)),
POTION_META(you_ulevelmax,offsetof(struct you,ulevelmax)),
POTION_META(you_ulevelmax_size,sizeof(((struct you*)0)->ulevelmax)),
POTION_META(you_ulevelpeak,offsetof(struct you,ulevelpeak)),
POTION_META(you_ulevelpeak_size,sizeof(((struct you*)0)->ulevelpeak)),
POTION_META(you_ulycn,offsetof(struct you,ulycn)),
POTION_META(you_ulycn_size,sizeof(((struct you*)0)->ulycn)),
POTION_META(you_umonnum,offsetof(struct you,umonnum)),
POTION_META(you_umonnum_size,sizeof(((struct you*)0)->umonnum)),
POTION_META(you_umonster,offsetof(struct you,umonster)),
POTION_META(you_umonster_size,sizeof(((struct you*)0)->umonster)),
POTION_META(you_uprops,offsetof(struct you,uprops)),
POTION_META(you_uprops_size,sizeof(((struct you*)0)->uprops)),
POTION_META(you_uroleplay,offsetof(struct you,uroleplay)),
POTION_META(you_uroleplay_size,sizeof(((struct you*)0)->uroleplay)),
POTION_META(you_ushops,offsetof(struct you,ushops)),
POTION_META(you_ushops_size,sizeof(((struct you*)0)->ushops)),
POTION_META(you_usteed,offsetof(struct you,usteed)),
POTION_META(you_usteed_size,sizeof(((struct you*)0)->usteed)),
POTION_META(you_ustuck,offsetof(struct you,ustuck)),
POTION_META(you_ustuck_size,sizeof(((struct you*)0)->ustuck)),
POTION_META(you_ux,offsetof(struct you,ux)),
POTION_META(you_ux_size,sizeof(((struct you*)0)->ux)),
POTION_META(you_uy,offsetof(struct you,uy)),
POTION_META(you_uy_size,sizeof(((struct you*)0)->uy)),
POTION_META(you_uz,offsetof(struct you,uz)),
POTION_META(you_uz_size,sizeof(((struct you*)0)->uz)),
POTION_META(you_weapon_skills,offsetof(struct you,weapon_skills)),
POTION_META(you_weapon_skills_size,sizeof(((struct you*)0)->weapon_skills)),
POTION_META(propSize,sizeof(struct prop)),
POTION_META(prop_blocked,offsetof(struct prop,blocked)),
POTION_META(prop_blocked_size,sizeof(((struct prop*)0)->blocked)),
POTION_META(prop_extrinsic,offsetof(struct prop,extrinsic)),
POTION_META(prop_extrinsic_size,sizeof(((struct prop*)0)->extrinsic)),
POTION_META(prop_intrinsic,offsetof(struct prop,intrinsic)),
POTION_META(prop_intrinsic_size,sizeof(((struct prop*)0)->intrinsic)),
POTION_META(obj_age,offsetof(struct obj,age)),
POTION_META(obj_age_size,sizeof(((struct obj*)0)->age)),
POTION_META(obj_cobj,offsetof(struct obj,cobj)),
POTION_META(obj_cobj_size,sizeof(((struct obj*)0)->cobj)),
POTION_META(obj_corpsenm,offsetof(struct obj,corpsenm)),
POTION_META(obj_corpsenm_size,sizeof(((struct obj*)0)->corpsenm)),
POTION_META(obj_invlet,offsetof(struct obj,invlet)),
POTION_META(obj_invlet_size,sizeof(((struct obj*)0)->invlet)),
POTION_META(obj_nexthere,offsetof(struct obj,nexthere)),
POTION_META(obj_nexthere_size,sizeof(((struct obj*)0)->nexthere)),
POTION_META(obj_nobj,offsetof(struct obj,nobj)),
POTION_META(obj_nobj_size,sizeof(((struct obj*)0)->nobj)),
POTION_META(obj_o_id,offsetof(struct obj,o_id)),
POTION_META(obj_o_id_size,sizeof(((struct obj*)0)->o_id)),
POTION_META(obj_oartifact,offsetof(struct obj,oartifact)),
POTION_META(obj_oartifact_size,sizeof(((struct obj*)0)->oartifact)),
POTION_META(obj_oclass,offsetof(struct obj,oclass)),
POTION_META(obj_oclass_size,sizeof(((struct obj*)0)->oclass)),
POTION_META(obj_otyp,offsetof(struct obj,otyp)),
POTION_META(obj_otyp_size,sizeof(((struct obj*)0)->otyp)),
POTION_META(obj_owornmask,offsetof(struct obj,owornmask)),
POTION_META(obj_owornmask_size,sizeof(((struct obj*)0)->owornmask)),
POTION_META(obj_quan,offsetof(struct obj,quan)),
POTION_META(obj_quan_size,sizeof(((struct obj*)0)->quan)),
POTION_META(obj_spe,offsetof(struct obj,spe)),
POTION_META(obj_spe_size,sizeof(((struct obj*)0)->spe)),
POTION_META(obj_where,offsetof(struct obj,where)),
POTION_META(obj_where_size,sizeof(((struct obj*)0)->where)),
POTION_META(colorsSize,sizeof(struct c_color_names)),
POTION_META(colors_c_amber,offsetof(struct c_color_names,c_amber)),
POTION_META(colors_c_amber_size,sizeof(((struct c_color_names*)0)->c_amber)),
POTION_META(colors_c_black,offsetof(struct c_color_names,c_black)),
POTION_META(colors_c_black_size,sizeof(((struct c_color_names*)0)->c_black)),
POTION_META(colors_c_light_blue,offsetof(struct c_color_names,c_light_blue)),
POTION_META(colors_c_light_blue_size,sizeof(((struct c_color_names*)0)->c_light_blue)),
POTION_META(colors_c_orange,offsetof(struct c_color_names,c_orange)),
POTION_META(colors_c_orange_size,sizeof(((struct c_color_names*)0)->c_orange)),
POTION_META(colors_c_red,offsetof(struct c_color_names,c_red)),
POTION_META(colors_c_red_size,sizeof(((struct c_color_names*)0)->c_red)),
POTION_META(iflagsSize,sizeof(struct instance_flags)),
POTION_META(iflags_last_msg,offsetof(struct instance_flags,last_msg)),
POTION_META(iflags_last_msg_size,sizeof(((struct instance_flags*)0)->last_msg)),
POTION_META(iflags_menu_requested,offsetof(struct instance_flags,menu_requested)),
POTION_META(iflags_menu_requested_size,sizeof(((struct instance_flags*)0)->menu_requested)),
POTION_META(stringsSize,sizeof(struct c_common_strings)),
POTION_META(strings_c_Something,offsetof(struct c_common_strings,c_Something)),
POTION_META(strings_c_Something_size,sizeof(((struct c_common_strings*)0)->c_Something)),
POTION_META(strings_c_You_can_move_again,offsetof(struct c_common_strings,c_You_can_move_again)),
POTION_META(strings_c_You_can_move_again_size,sizeof(((struct c_common_strings*)0)->c_You_can_move_again)),
POTION_META(strings_c_nothing_happens,offsetof(struct c_common_strings,c_nothing_happens)),
POTION_META(strings_c_nothing_happens_size,sizeof(((struct c_common_strings*)0)->c_nothing_happens)),
POTION_META(strings_c_nothing_seems_to_happen,offsetof(struct c_common_strings,c_nothing_seems_to_happen)),
POTION_META(strings_c_nothing_seems_to_happen_size,sizeof(((struct c_common_strings*)0)->c_nothing_seems_to_happen)),
POTION_META(strings_c_something,offsetof(struct c_common_strings,c_something)),
POTION_META(strings_c_something_size,sizeof(((struct c_common_strings*)0)->c_something)),
POTION_META(strings_c_the_your,offsetof(struct c_common_strings,c_the_your)),
POTION_META(strings_c_the_your_size,sizeof(((struct c_common_strings*)0)->c_the_your)),
POTION_META(strings_c_vision_clears,offsetof(struct c_common_strings,c_vision_clears)),
POTION_META(strings_c_vision_clears_size,sizeof(((struct c_common_strings*)0)->c_vision_clears)),
POTION_META(conductSize,sizeof(struct u_conduct)),
POTION_META(conduct_polypiles,offsetof(struct u_conduct,polypiles)),
POTION_META(conduct_polypiles_size,sizeof(((struct u_conduct*)0)->polypiles)),
POTION_META(flagsSize,sizeof(struct flag)),
POTION_META(flags_beginner,offsetof(struct flag,beginner)),
POTION_META(flags_beginner_size,sizeof(((struct flag*)0)->beginner)),
POTION_META(flags_female,offsetof(struct flag,female)),
POTION_META(flags_female_size,sizeof(((struct flag*)0)->female)),
POTION_META(flags_pickup_burden,offsetof(struct flag,pickup_burden)),
POTION_META(flags_pickup_burden_size,sizeof(((struct flag*)0)->pickup_burden)),
POTION_META(flags_verbose,offsetof(struct flag,verbose)),
POTION_META(flags_verbose_size,sizeof(((struct flag*)0)->verbose)),
POTION_META(topologySize,sizeof(struct dgn_topology)),
POTION_META(topology_d_air_level,offsetof(struct dgn_topology,d_air_level)),
POTION_META(topology_d_air_level_size,sizeof(((struct dgn_topology*)0)->d_air_level)),
POTION_META(topology_d_earth_level,offsetof(struct dgn_topology,d_earth_level)),
POTION_META(topology_d_earth_level_size,sizeof(((struct dgn_topology*)0)->d_earth_level)),
POTION_META(topology_d_water_level,offsetof(struct dgn_topology,d_water_level)),
POTION_META(topology_d_water_level_size,sizeof(((struct dgn_topology*)0)->d_water_level)),
POTION_META(gvSize,sizeof(struct instance_globals_v)),
POTION_META(gv_vision_full_recalc,offsetof(struct instance_globals_v,vision_full_recalc)),
POTION_META(gv_vision_full_recalc_size,sizeof(((struct instance_globals_v*)0)->vision_full_recalc)),
POTION_META(gv_viz_array,offsetof(struct instance_globals_v,viz_array)),
POTION_META(gv_viz_array_size,sizeof(((struct instance_globals_v*)0)->viz_array)),
POTION_META(svmSize,sizeof(struct instance_globals_saved_m)),
POTION_META(svm_mvitals,offsetof(struct instance_globals_saved_m,mvitals)),
POTION_META(svm_mvitals_size,sizeof(((struct instance_globals_saved_m*)0)->mvitals)),
POTION_META(roleSize,sizeof(struct Role)),
POTION_META(role_mnum,offsetof(struct Role,mnum)),
POTION_META(role_mnum_size,sizeof(((struct Role*)0)->mnum)),
POTION_META(clsSize,sizeof(struct objclass)),
POTION_META(cls_oc_descr_idx,offsetof(struct objclass,oc_descr_idx)),
POTION_META(cls_oc_descr_idx_size,sizeof(((struct objclass*)0)->oc_descr_idx)),
POTION_META(cls_oc_skill,offsetof(struct objclass,oc_skill)),
POTION_META(cls_oc_skill_size,sizeof(((struct objclass*)0)->oc_skill)),
POTION_META(cls_oc_subtyp,offsetof(struct objclass,oc_subtyp)),
POTION_META(cls_oc_subtyp_size,sizeof(((struct objclass*)0)->oc_subtyp)),
POTION_META(cls_oc_uname,offsetof(struct objclass,oc_uname)),
POTION_META(cls_oc_uname_size,sizeof(((struct objclass*)0)->oc_uname)),
POTION_META(pmSize,sizeof(struct permonst)),
POTION_META(pm_geno,offsetof(struct permonst,geno)),
POTION_META(pm_geno_size,sizeof(((struct permonst*)0)->geno)),
POTION_META(pm_mattk,offsetof(struct permonst,mattk)),
POTION_META(pm_mattk_size,sizeof(((struct permonst*)0)->mattk)),
POTION_META(pm_mflags1,offsetof(struct permonst,mflags1)),
POTION_META(pm_mflags1_size,sizeof(((struct permonst*)0)->mflags1)),
POTION_META(pm_mflags2,offsetof(struct permonst,mflags2)),
POTION_META(pm_mflags2_size,sizeof(((struct permonst*)0)->mflags2)),
POTION_META(pm_mflags3,offsetof(struct permonst,mflags3)),
POTION_META(pm_mflags3_size,sizeof(((struct permonst*)0)->mflags3)),
POTION_META(pm_mlet,offsetof(struct permonst,mlet)),
POTION_META(pm_mlet_size,sizeof(((struct permonst*)0)->mlet)),
POTION_META(pm_mlevel,offsetof(struct permonst,mlevel)),
POTION_META(pm_mlevel_size,sizeof(((struct permonst*)0)->mlevel)),
POTION_META(pm_mmove,offsetof(struct permonst,mmove)),
POTION_META(pm_mmove_size,sizeof(((struct permonst*)0)->mmove)),
POTION_META(pm_msize,offsetof(struct permonst,msize)),
POTION_META(pm_msize_size,sizeof(((struct permonst*)0)->msize)),
POTION_META(pm_msound,offsetof(struct permonst,msound)),
POTION_META(pm_msound_size,sizeof(((struct permonst*)0)->msound)),
POTION_META(pm_pmidx,offsetof(struct permonst,pmidx)),
POTION_META(pm_pmidx_size,sizeof(((struct permonst*)0)->pmidx)),
POTION_META(pm_pmnames,offsetof(struct permonst,pmnames)),
POTION_META(pm_pmnames_size,sizeof(((struct permonst*)0)->pmnames)),
POTION_META(vitalSize,sizeof(struct mvitals)),
POTION_META(vital_born,offsetof(struct mvitals,born)),
POTION_META(vital_born_size,sizeof(((struct mvitals*)0)->born)),
POTION_META(vital_mvflags,offsetof(struct mvitals,mvflags)),
POTION_META(vital_mvflags_size,sizeof(((struct mvitals*)0)->mvflags)),
POTION_META(gpSize,sizeof(struct instance_globals_p)),
POTION_META(gp_potion_nothing,offsetof(struct instance_globals_p,potion_nothing)),
POTION_META(gp_potion_nothing_size,sizeof(((struct instance_globals_p*)0)->potion_nothing)),
POTION_META(gp_potion_unkn,offsetof(struct instance_globals_p,potion_unkn)),
POTION_META(gp_potion_unkn_size,sizeof(((struct instance_globals_p*)0)->potion_unkn)),
POTION_META(gmSize,sizeof(struct instance_globals_m)),
POTION_META(gm_mentioned_water,offsetof(struct instance_globals_m,mentioned_water)),
POTION_META(gm_mentioned_water_size,sizeof(((struct instance_globals_m*)0)->mentioned_water)),
POTION_META(gm_multi,offsetof(struct instance_globals_m,multi)),
POTION_META(gm_multi_size,sizeof(((struct instance_globals_m*)0)->multi)),
POTION_META(gm_multi_reason,offsetof(struct instance_globals_m,multi_reason)),
POTION_META(gm_multi_reason_size,sizeof(((struct instance_globals_m*)0)->multi_reason)),
POTION_META(attribsSize,sizeof(struct attribs)),
POTION_META(attribs_a,offsetof(struct attribs,a)),
POTION_META(attribs_a_size,sizeof(((struct attribs*)0)->a)),
POTION_META(levelSize,sizeof(struct d_level)),
POTION_META(level_dlevel,offsetof(struct d_level,dlevel)),
POTION_META(level_dlevel_size,sizeof(((struct d_level*)0)->dlevel)),
POTION_META(level_dnum,offsetof(struct d_level,dnum)),
POTION_META(level_dnum_size,sizeof(((struct d_level*)0)->dnum)),
POTION_META(rmSize,sizeof(struct rm)),
POTION_META(rm_glyph,offsetof(struct rm,glyph)),
POTION_META(rm_glyph_size,sizeof(((struct rm*)0)->glyph)),
POTION_META(rm_typ,offsetof(struct rm,typ)),
POTION_META(rm_typ_size,sizeof(((struct rm*)0)->typ)),
POTION_META(svlSize,sizeof(struct instance_globals_saved_l)),
POTION_META(svl_level,offsetof(struct instance_globals_saved_l,level)),
POTION_META(svl_level_size,sizeof(((struct instance_globals_saved_l*)0)->level)),
POTION_META(descrSize,sizeof(struct objdescr)),
POTION_META(descr_oc_descr,offsetof(struct objdescr,oc_descr)),
POTION_META(descr_oc_descr_size,sizeof(((struct objdescr*)0)->oc_descr)),
POTION_META(skillSize,sizeof(struct skills)),
POTION_META(skill_skill,offsetof(struct skills,skill)),
POTION_META(skill_skill_size,sizeof(((struct skills*)0)->skill)),
POTION_META(roleplaySize,sizeof(struct u_roleplay)),
POTION_META(roleplay_deaf,offsetof(struct u_roleplay,deaf)),
POTION_META(roleplay_deaf_size,sizeof(((struct u_roleplay*)0)->deaf)),
POTION_META(gnSize,sizeof(struct instance_globals_n)),
POTION_META(gn_nomovemsg,offsetof(struct instance_globals_n,nomovemsg)),
POTION_META(gn_nomovemsg_size,sizeof(((struct instance_globals_n*)0)->nomovemsg)),
POTION_META(gn_notonhead,offsetof(struct instance_globals_n,notonhead)),
POTION_META(gn_notonhead_size,sizeof(((struct instance_globals_n*)0)->notonhead)),
POTION_META(svcSize,sizeof(struct instance_globals_saved_c)),
POTION_META(svc_context,offsetof(struct instance_globals_saved_c,context)),
POTION_META(svc_context_size,sizeof(((struct instance_globals_saved_c*)0)->context)),
POTION_META(genderSize,sizeof(struct Gender)),
POTION_META(gender_he,offsetof(struct Gender,he)),
POTION_META(gender_he_size,sizeof(((struct Gender*)0)->he)),
POTION_META(gender_him,offsetof(struct Gender,him)),
POTION_META(gender_him_size,sizeof(((struct Gender*)0)->him)),
POTION_META(gender_his,offsetof(struct Gender,his)),
POTION_META(gender_his_size,sizeof(((struct Gender*)0)->his)),
POTION_META(stairSize,sizeof(struct stairway)),
POTION_META(stair_up,offsetof(struct stairway,up)),
POTION_META(stair_up_size,sizeof(((struct stairway*)0)->up)),
POTION_META(alignSize,sizeof(struct align)),
POTION_META(align_type,offsetof(struct align,type)),
POTION_META(align_type_size,sizeof(((struct align*)0)->type)),
POTION_META(contextSize,sizeof(struct context_info)),
POTION_META(context_mon_moving,offsetof(struct context_info,mon_moving)),
POTION_META(context_mon_moving_size,sizeof(((struct context_info*)0)->mon_moving)),
POTION_META(gySize,sizeof(struct instance_globals_y)),
POTION_META(gy_youmonst,offsetof(struct instance_globals_y,youmonst)),
POTION_META(gy_youmonst_size,sizeof(((struct instance_globals_y*)0)->youmonst)),
POTION_META(guSize,sizeof(struct instance_globals_u)),
POTION_META(gu_urace,offsetof(struct instance_globals_u,urace)),
POTION_META(gu_urace_size,sizeof(((struct instance_globals_u*)0)->urace)),
POTION_META(gu_urole,offsetof(struct instance_globals_u,urole)),
POTION_META(gu_urole_size,sizeof(((struct instance_globals_u*)0)->urole)),
POTION_META(svdSize,sizeof(struct instance_globals_saved_d)),
POTION_META(svd_dungeon_topology,offsetof(struct instance_globals_saved_d,dungeon_topology)),
POTION_META(svd_dungeon_topology_size,sizeof(((struct instance_globals_saved_d*)0)->dungeon_topology)),
POTION_META(cgSize,sizeof(struct const_globals)),
POTION_META(cg_zeroobj,offsetof(struct const_globals,zeroobj)),
POTION_META(cg_zeroobj_size,sizeof(((struct const_globals*)0)->zeroobj)),
POTION_META(haveSize,sizeof(struct u_have)),
POTION_META(dispSize,sizeof(struct display_hints)),
POTION_META(disp_botl,offsetof(struct display_hints,botl)),
POTION_META(disp_botl_size,sizeof(((struct display_hints*)0)->botl)),
POTION_META(raceSize,sizeof(struct Race)),
POTION_META(race_attrmax,offsetof(struct Race,attrmax)),
POTION_META(race_attrmax_size,sizeof(((struct Race*)0)->attrmax)),
POTION_META(race_attrmin,offsetof(struct Race,attrmin)),
POTION_META(race_attrmin_size,sizeof(((struct Race*)0)->attrmin)),
POTION_META(giSize,sizeof(struct instance_globals_i)),
POTION_META(gi_invent,offsetof(struct instance_globals_i,invent)),
POTION_META(gi_invent_size,sizeof(((struct instance_globals_i*)0)->invent)),
POTION_META(attackSize,sizeof(struct attack)),
POTION_META(attack_aatyp,offsetof(struct attack,aatyp)),
POTION_META(attack_aatyp_size,sizeof(((struct attack*)0)->aatyp)),
POTION_META(attack_adtyp,offsetof(struct attack,adtyp)),
POTION_META(attack_adtyp_size,sizeof(((struct attack*)0)->adtyp)),
POTION_META(attack_damd,offsetof(struct attack,damd)),
POTION_META(attack_damd_size,sizeof(((struct attack*)0)->damd)),
POTION_META(attack_damn,offsetof(struct attack,damn)),
POTION_META(attack_damn_size,sizeof(((struct attack*)0)->damn)),
POTION_META(coordSize,sizeof(struct nhcoord)),
POTION_META(coord_x,offsetof(struct nhcoord,x)),
POTION_META(coord_x_size,sizeof(((struct nhcoord*)0)->x)),
POTION_META(coord_y,offsetof(struct nhcoord,y)),
POTION_META(coord_y_size,sizeof(((struct nhcoord*)0)->y)),
POTION_META(killerSize,sizeof(struct kinfo)),
POTION_META(killer_format,offsetof(struct kinfo,format)),
POTION_META(killer_format_size,sizeof(((struct kinfo*)0)->format)),
POTION_META(killer_name,offsetof(struct kinfo,name)),
POTION_META(killer_name_size,sizeof(((struct kinfo*)0)->name)),
POTION_META(dlevelSize,sizeof(__typeof__(svl.level))),
POTION_META(dlevel_locations,offsetof(__typeof__(svl.level),locations)),
POTION_META(dlevel_locations_size,sizeof(((__typeof__(svl.level)*)0)->locations)),
POTION_META(dlevel_monlist,offsetof(__typeof__(svl.level),monlist)),
POTION_META(dlevel_monlist_size,sizeof(((__typeof__(svl.level)*)0)->monlist)),
POTION_META(dlevel_monsters,offsetof(__typeof__(svl.level),monsters)),
POTION_META(dlevel_monsters_size,sizeof(((__typeof__(svl.level)*)0)->monsters)),
POTION_META(dlevel_objects,offsetof(__typeof__(svl.level),objects)),
POTION_META(dlevel_objects_size,sizeof(((__typeof__(svl.level)*)0)->objects)),
POTION_META(ACID_RES,ACID_RES),
POTION_META(AD_ACID,AD_ACID),
POTION_META(AD_DISE,AD_DISE),
POTION_META(AD_PEST,AD_PEST),
POTION_META(ALCHEMY_SMOCK,ALCHEMY_SMOCK),
POTION_META(AMETHYST,AMETHYST),
POTION_META(ANTIMAGIC,ANTIMAGIC),
POTION_META(ARMOR_CLASS,ARMOR_CLASS),
POTION_META(ARM_BOOTS,ARM_BOOTS),
POTION_META(ARM_GLOVES,ARM_GLOVES),
POTION_META(ARTICLE_THE,ARTICLE_THE),
POTION_META(ART_EYES_OF_THE_OVERWORLD,ART_EYES_OF_THE_OVERWORLD),
POTION_META(A_CHAOTIC,A_CHAOTIC),
POTION_META(A_CON,A_CON),
POTION_META(A_DEX,A_DEX),
POTION_META(A_INT,A_INT),
POTION_META(A_LAWFUL,A_LAWFUL),
POTION_META(A_MAX,A_MAX),
POTION_META(A_STR,A_STR),
POTION_META(A_WIS,A_WIS),
POTION_META(BLINDED,BLINDED),
POTION_META(BOLT_LIM,BOLT_LIM),
POTION_META(BUFSZ,BUFSZ),
POTION_META(COIN_CLASS,COIN_CLASS),
POTION_META(COLD_RES,COLD_RES),
POTION_META(COLNO,COLNO),
POTION_META(CONFUSION,CONFUSION),
POTION_META(COPPER,COPPER),
POTION_META(CORPSE,CORPSE),
POTION_META(COULD_SEE,COULD_SEE),
POTION_META(CQ_CANNED,CQ_CANNED),
POTION_META(DEAF,DEAF),
POTION_META(DETECT_MONSTERS,DETECT_MONSTERS),
POTION_META(DISP_ALWAYS,DISP_ALWAYS),
POTION_META(DISP_END,DISP_END),
POTION_META(ECMD_CANCEL,ECMD_CANCEL),
POTION_META(ECMD_FAIL,ECMD_FAIL),
POTION_META(ECMD_OK,ECMD_OK),
POTION_META(ECMD_TIME,ECMD_TIME),
POTION_META(EF_GREASE,EF_GREASE),
POTION_META(ENL_GAMEINPROGRESS,ENL_GAMEINPROGRESS),
POTION_META(ERODE_CORRODE,ERODE_CORRODE),
POTION_META(ER_DESTROYED,ER_DESTROYED),
POTION_META(ER_NOTHING,ER_NOTHING),
POTION_META(EXPL_FIERY,EXPL_FIERY),
POTION_META(EYE,EYE),
POTION_META(FACE,FACE),
POTION_META(FAST,FAST),
POTION_META(FIRE_RES,FIRE_RES),
POTION_META(FIXED_ABIL,FIXED_ABIL),
POTION_META(FLYING,FLYING),
POTION_META(FOOT,FOOT),
POTION_META(FOUNTAIN,FOUNTAIN),
POTION_META(FREE_ACTION,FREE_ACTION),
POTION_META(FROMOUTSIDE,FROMOUTSIDE),
POTION_META(FUMBLING,FUMBLING),
POTION_META(GEM_CLASS,GEM_CLASS),
POTION_META(GETOBJ_DOWNPLAY,GETOBJ_DOWNPLAY),
POTION_META(GETOBJ_EXCLUDE,GETOBJ_EXCLUDE),
POTION_META(GETOBJ_EXCLUDE_INACCESS,GETOBJ_EXCLUDE_INACCESS),
POTION_META(GETOBJ_EXCLUDE_NONINVENT,GETOBJ_EXCLUDE_NONINVENT),
POTION_META(GETOBJ_NOFLAGS,GETOBJ_NOFLAGS),
POTION_META(GETOBJ_PROMPT,GETOBJ_PROMPT),
POTION_META(GETOBJ_SUGGEST,GETOBJ_SUGGEST),
POTION_META(GLIB,GLIB),
POTION_META(GLYPH_INVISIBLE,GLYPH_INVISIBLE),
POTION_META(G_GONE,G_GONE),
POTION_META(HALF_PHDAM,HALF_PHDAM),
POTION_META(HALF_SPDAM,HALF_SPDAM),
POTION_META(HALLUC,HALLUC),
POTION_META(HALLUC_RES,HALLUC_RES),
POTION_META(HAND,HAND),
POTION_META(HEAD,HEAD),
POTION_META(INFRAVISION,INFRAVISION),
POTION_META(INTRINSIC,INTRINSIC),
POTION_META(INVIS,INVIS),
POTION_META(IN_SIGHT,IN_SIGHT),
POTION_META(IRON,IRON),
POTION_META(I_SPECIAL,I_SPECIAL),
POTION_META(KILLED_BY,KILLED_BY),
POTION_META(KILLED_BY_AN,KILLED_BY_AN),
POTION_META(LAST_PROP,LAST_PROP),
POTION_META(LEG,LEG),
POTION_META(LENSES,LENSES),
POTION_META(LEVITATION,LEVITATION),
POTION_META(LL_CONDUCT,LL_CONDUCT),
POTION_META(LONG_SWORD,LONG_SWORD),
POTION_META(LOW_PM,LOW_PM),
POTION_META(M1_AMORPHOUS,M1_AMORPHOUS),
POTION_META(M1_AMPHIBIOUS,M1_AMPHIBIOUS),
POTION_META(M1_BREATHLESS,M1_BREATHLESS),
POTION_META(M1_FLY,M1_FLY),
POTION_META(M1_NOEYES,M1_NOEYES),
POTION_META(M1_NOHANDS,M1_NOHANDS),
POTION_META(M1_NOHEAD,M1_NOHEAD),
POTION_META(M1_NOLIMBS,M1_NOLIMBS),
POTION_META(M1_REGEN,M1_REGEN),
POTION_META(M1_SWIM,M1_SWIM),
POTION_META(M1_UNSOLID,M1_UNSOLID),
POTION_META(M1_WALLWALK,M1_WALLWALK),
POTION_META(M2_DEMON,M2_DEMON),
POTION_META(M2_DWARF,M2_DWARF),
POTION_META(M2_ELF,M2_ELF),
POTION_META(M2_GNOME,M2_GNOME),
POTION_META(M2_HUMAN,M2_HUMAN),
POTION_META(M2_MINION,M2_MINION),
POTION_META(M2_ORC,M2_ORC),
POTION_META(M2_STRONG,M2_STRONG),
POTION_META(M2_UNDEAD,M2_UNDEAD),
POTION_META(M2_WERE,M2_WERE),
POTION_META(MAGICAL_BREATHING,MAGICAL_BREATHING),
POTION_META(MAGICENLIGHTENMENT,MAGICENLIGHTENMENT),
POTION_META(MAGIC_LAMP,MAGIC_LAMP),
POTION_META(MM_NOMSG,MM_NOMSG),
POTION_META(MS_SILENT,MS_SILENT),
POTION_META(MUMMY_WRAPPING,MUMMY_WRAPPING),
POTION_META(M_AP_MONSTER,M_AP_MONSTER),
POTION_META(M_AP_NOTHING,M_AP_NOTHING),
POTION_META(M_AP_TYPMASK,M_AP_TYPMASK),
POTION_META(M_SEEN_SLEEP,M_SEEN_SLEEP),
POTION_META(NEUTRAL,NEUTRAL),
POTION_META(NON_PM,NON_PM),
POTION_META(NOTELL,NOTELL),
POTION_META(NUMMONS,NUMMONS),
POTION_META(NUM_OBJECTS,NUM_OBJECTS),
POTION_META(OBJ_FLOOR,OBJ_FLOOR),
POTION_META(OBJ_FREE,OBJ_FREE),
POTION_META(OBJ_INVENT,OBJ_INVENT),
POTION_META(OIL_LAMP,OIL_LAMP),
POTION_META(PLNMSG_OBJ_GLOWS,PLNMSG_OBJ_GLOWS),
POTION_META(PM_BAT,PM_BAT),
POTION_META(PM_CHICKATRICE,PM_CHICKATRICE),
POTION_META(PM_COCKATRICE,PM_COCKATRICE),
POTION_META(PM_CYCLOPS,PM_CYCLOPS),
POTION_META(PM_DJINNI,PM_DJINNI),
POTION_META(PM_FIRE_ELEMENTAL,PM_FIRE_ELEMENTAL),
POTION_META(PM_FIRE_VORTEX,PM_FIRE_VORTEX),
POTION_META(PM_FLAMING_SPHERE,PM_FLAMING_SPHERE),
POTION_META(PM_FLOATING_EYE,PM_FLOATING_EYE),
POTION_META(PM_GHOST,PM_GHOST),
POTION_META(PM_GREEN_SLIME,PM_GREEN_SLIME),
POTION_META(PM_GREMLIN,PM_GREMLIN),
POTION_META(PM_HEALER,PM_HEALER),
POTION_META(PM_HUMAN,PM_HUMAN),
POTION_META(PM_IRON_GOLEM,PM_IRON_GOLEM),
POTION_META(PM_LICHEN,PM_LICHEN),
POTION_META(PM_PESTILENCE,PM_PESTILENCE),
POTION_META(PM_RED_DRAGON,PM_RED_DRAGON),
POTION_META(PM_SALAMANDER,PM_SALAMANDER),
POTION_META(PM_VAMPIRE,PM_VAMPIRE),
POTION_META(PM_VAMPIRE_LEADER,PM_VAMPIRE_LEADER),
POTION_META(PM_VLAD_THE_IMPALER,PM_VLAD_THE_IMPALER),
POTION_META(POISON_RES,POISON_RES),
POTION_META(POLY_CONTROLLED,POLY_CONTROLLED),
POTION_META(POLY_LOW_CTRL,POLY_LOW_CTRL),
POTION_META(POLY_NOFLAGS,POLY_NOFLAGS),
POTION_META(POOL,POOL),
POTION_META(POTHIT_HERO_THROW,POTHIT_HERO_THROW),
POTION_META(POTHIT_OTHER_THROW,POTHIT_OTHER_THROW),
POTION_META(POTION_CLASS,POTION_CLASS),
POTION_META(POT_ACID,POT_ACID),
POTION_META(POT_BLINDNESS,POT_BLINDNESS),
POTION_META(POT_BOOZE,POT_BOOZE),
POTION_META(POT_CONFUSION,POT_CONFUSION),
POTION_META(POT_ENLIGHTENMENT,POT_ENLIGHTENMENT),
POTION_META(POT_EXTRA_HEALING,POT_EXTRA_HEALING),
POTION_META(POT_FRUIT_JUICE,POT_FRUIT_JUICE),
POTION_META(POT_FULL_HEALING,POT_FULL_HEALING),
POTION_META(POT_GAIN_ABILITY,POT_GAIN_ABILITY),
POTION_META(POT_GAIN_ENERGY,POT_GAIN_ENERGY),
POTION_META(POT_GAIN_LEVEL,POT_GAIN_LEVEL),
POTION_META(POT_HALLUCINATION,POT_HALLUCINATION),
POTION_META(POT_HEALING,POT_HEALING),
POTION_META(POT_INVISIBILITY,POT_INVISIBILITY),
POTION_META(POT_LEVITATION,POT_LEVITATION),
POTION_META(POT_MONSTER_DETECTION,POT_MONSTER_DETECTION),
POTION_META(POT_OBJECT_DETECTION,POT_OBJECT_DETECTION),
POTION_META(POT_OIL,POT_OIL),
POTION_META(POT_PARALYSIS,POT_PARALYSIS),
POTION_META(POT_POLYMORPH,POT_POLYMORPH),
POTION_META(POT_RESTORE_ABILITY,POT_RESTORE_ABILITY),
POTION_META(POT_SEE_INVISIBLE,POT_SEE_INVISIBLE),
POTION_META(POT_SICKNESS,POT_SICKNESS),
POTION_META(POT_SLEEPING,POT_SLEEPING),
POTION_META(POT_SPEED,POT_SPEED),
POTION_META(POT_WATER,POT_WATER),
POTION_META(PRONOUN_HALLU,PRONOUN_HALLU),
POTION_META(PROT_FROM_SHAPE_CHANGERS,PROT_FROM_SHAPE_CHANGERS),
POTION_META(P_BASIC,P_BASIC),
POTION_META(P_BOW,P_BOW),
POTION_META(P_CROSSBOW,P_CROSSBOW),
POTION_META(P_NONE,P_NONE),
POTION_META(P_RIDING,P_RIDING),
POTION_META(P_SHURIKEN,P_SHURIKEN),
POTION_META(QBUFSZ,QBUFSZ),
POTION_META(ROOM,ROOM),
POTION_META(ROWNO,ROWNO),
POTION_META(SEE_INVIS,SEE_INVIS),
POTION_META(SHOCK_RES,SHOCK_RES),
POTION_META(SHOPBASE,SHOPBASE),
POTION_META(SICK,SICK),
POTION_META(SICK_ALL,SICK_ALL),
POTION_META(SICK_RES,SICK_RES),
POTION_META(SINK,SINK),
POTION_META(SLEEP_RES,SLEEP_RES),
POTION_META(SLIMED,SLIMED),
POTION_META(SPBOOK_CLASS,SPBOOK_CLASS),
POTION_META(SPE_DETECT_MONSTERS,SPE_DETECT_MONSTERS),
POTION_META(SPE_DETECT_TREASURE,SPE_DETECT_TREASURE),
POTION_META(SPE_HASTE_SELF,SPE_HASTE_SELF),
POTION_META(SPE_INVISIBILITY,SPE_INVISIBILITY),
POTION_META(SPE_LEVITATION,SPE_LEVITATION),
POTION_META(SPE_RESTORE_ABILITY,SPE_RESTORE_ABILITY),
POTION_META(STONED,STONED),
POTION_META(STRANGE_OBJECT,STRANGE_OBJECT),
POTION_META(STRANGLED,STRANGLED),
POTION_META(STUNNED,STUNNED),
POTION_META(SUPPRESS_IT,SUPPRESS_IT),
POTION_META(SUPPRESS_SADDLE,SUPPRESS_SADDLE),
POTION_META(SWIMMING,SWIMMING),
POTION_META(S_EYE,S_EYE),
POTION_META(S_LIGHT,S_LIGHT),
POTION_META(TELEPAT,TELEPAT),
POTION_META(TIMEOUT,TIMEOUT),
POTION_META(TOOL_CLASS,TOOL_CLASS),
POTION_META(TOWEL,TOWEL),
POTION_META(UNCHANGING,UNCHANGING),
POTION_META(UNICORN_HORN,UNICORN_HORN),
POTION_META(VOMITING,VOMITING),
POTION_META(WARN_OF_MON,WARN_OF_MON),
POTION_META(WEAPON_CLASS,WEAPON_CLASS),
POTION_META(WOUNDED_LEGS,WOUNDED_LEGS),
POTION_META(W_ART,W_ART),
POTION_META(W_ARTI,W_ARTI),
POTION_META(W_SADDLE,W_SADDLE),
POTION_META(W_WEP,W_WEP),
POTION_META(COST_UNCURS,COST_UNCURS),
POTION_META(COST_UNBLSS,COST_UNBLSS),
POTION_META(COST_NUTRLZ,COST_NUTRLZ),
};
_Static_assert(sizeof(void*)==8&&sizeof(long)==8&&sizeof(int)==4&&sizeof(coordxy)==2&&sizeof(boolean)==1,"POTION ABI widths");
_Static_assert(sizeof(((struct monst*)0)->cham)==2,"mon_cham width");
_Static_assert(((__typeof__(((struct monst*)0)->cham))-1 < 0),"mon_cham signedness");
_Static_assert(sizeof(((struct monst*)0)->data)==8,"mon_data pointer width");
_Static_assert(sizeof(((struct monst*)0)->m_ap_type)==1,"mon_m_ap_type width");
_Static_assert(((__typeof__(((struct monst*)0)->m_ap_type))-1 > 0),"mon_m_ap_type signedness");
_Static_assert(sizeof(((struct monst*)0)->mappearance)==4,"mon_mappearance width");
_Static_assert(((__typeof__(((struct monst*)0)->mappearance))-1 > 0),"mon_mappearance signedness");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4,"mon_mhp width");
_Static_assert(((__typeof__(((struct monst*)0)->mhp))-1 < 0),"mon_mhp signedness");
_Static_assert(sizeof(((struct monst*)0)->mhpmax)==4,"mon_mhpmax width");
_Static_assert(((__typeof__(((struct monst*)0)->mhpmax))-1 < 0),"mon_mhpmax signedness");
_Static_assert(sizeof(((struct monst*)0)->misc_worn_check)==8,"mon_misc_worn_check width");
_Static_assert(((__typeof__(((struct monst*)0)->misc_worn_check))-1 < 0),"mon_misc_worn_check signedness");
_Static_assert(sizeof(((struct monst*)0)->mx)==2,"mon_mx width");
_Static_assert(((__typeof__(((struct monst*)0)->mx))-1 < 0),"mon_mx signedness");
_Static_assert(sizeof(((struct monst*)0)->my)==2,"mon_my width");
_Static_assert(((__typeof__(((struct monst*)0)->my))-1 < 0),"mon_my signedness");
_Static_assert(sizeof(((struct you*)0)->mh)==4,"you_mh width");
_Static_assert(((__typeof__(((struct you*)0)->mh))-1 < 0),"you_mh signedness");
_Static_assert(sizeof(((struct you*)0)->mhmax)==4,"you_mhmax width");
_Static_assert(((__typeof__(((struct you*)0)->mhmax))-1 < 0),"you_mhmax signedness");
_Static_assert(sizeof(((struct you*)0)->mtimedone)==4,"you_mtimedone width");
_Static_assert(((__typeof__(((struct you*)0)->mtimedone))-1 < 0),"you_mtimedone signedness");
_Static_assert(sizeof(((struct you*)0)->ucreamed)==4,"you_ucreamed width");
_Static_assert(((__typeof__(((struct you*)0)->ucreamed))-1 > 0),"you_ucreamed signedness");
_Static_assert(sizeof(((struct you*)0)->uen)==4,"you_uen width");
_Static_assert(((__typeof__(((struct you*)0)->uen))-1 < 0),"you_uen signedness");
_Static_assert(sizeof(((struct you*)0)->uenmax)==4,"you_uenmax width");
_Static_assert(((__typeof__(((struct you*)0)->uenmax))-1 < 0),"you_uenmax signedness");
_Static_assert(sizeof(((struct you*)0)->uenpeak)==4,"you_uenpeak width");
_Static_assert(((__typeof__(((struct you*)0)->uenpeak))-1 < 0),"you_uenpeak signedness");
_Static_assert(sizeof(((struct you*)0)->uexp)==8,"you_uexp width");
_Static_assert(((__typeof__(((struct you*)0)->uexp))-1 < 0),"you_uexp signedness");
_Static_assert(sizeof(((struct you*)0)->uhp)==4,"you_uhp width");
_Static_assert(((__typeof__(((struct you*)0)->uhp))-1 < 0),"you_uhp signedness");
_Static_assert(sizeof(((struct you*)0)->uhpmax)==4,"you_uhpmax width");
_Static_assert(((__typeof__(((struct you*)0)->uhpmax))-1 < 0),"you_uhpmax signedness");
_Static_assert(sizeof(((struct you*)0)->uhppeak)==4,"you_uhppeak width");
_Static_assert(((__typeof__(((struct you*)0)->uhppeak))-1 < 0),"you_uhppeak signedness");
_Static_assert(sizeof(((struct you*)0)->uhs)==4,"you_uhs width");
_Static_assert(((__typeof__(((struct you*)0)->uhs))-1 > 0),"you_uhs signedness");
_Static_assert(sizeof(((struct you*)0)->uhunger)==4,"you_uhunger width");
_Static_assert(((__typeof__(((struct you*)0)->uhunger))-1 < 0),"you_uhunger signedness");
_Static_assert(sizeof(((struct you*)0)->ulevel)==4,"you_ulevel width");
_Static_assert(((__typeof__(((struct you*)0)->ulevel))-1 < 0),"you_ulevel signedness");
_Static_assert(sizeof(((struct you*)0)->ulevelmax)==4,"you_ulevelmax width");
_Static_assert(((__typeof__(((struct you*)0)->ulevelmax))-1 < 0),"you_ulevelmax signedness");
_Static_assert(sizeof(((struct you*)0)->ulevelpeak)==4,"you_ulevelpeak width");
_Static_assert(((__typeof__(((struct you*)0)->ulevelpeak))-1 < 0),"you_ulevelpeak signedness");
_Static_assert(sizeof(((struct you*)0)->ulycn)==4,"you_ulycn width");
_Static_assert(((__typeof__(((struct you*)0)->ulycn))-1 < 0),"you_ulycn signedness");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4,"you_umonnum width");
_Static_assert(((__typeof__(((struct you*)0)->umonnum))-1 < 0),"you_umonnum signedness");
_Static_assert(sizeof(((struct you*)0)->umonster)==4,"you_umonster width");
_Static_assert(((__typeof__(((struct you*)0)->umonster))-1 < 0),"you_umonster signedness");
_Static_assert(sizeof(((struct you*)0)->usteed)==8,"you_usteed pointer width");
_Static_assert(sizeof(((struct you*)0)->ustuck)==8,"you_ustuck pointer width");
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
_Static_assert(sizeof(((struct obj*)0)->invlet)==1,"obj_invlet width");
_Static_assert(((__typeof__(((struct obj*)0)->invlet))-1 < 0),"obj_invlet signedness");
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
_Static_assert(sizeof(((struct obj*)0)->owornmask)==8,"obj_owornmask width");
_Static_assert(((__typeof__(((struct obj*)0)->owornmask))-1 < 0),"obj_owornmask signedness");
_Static_assert(sizeof(((struct obj*)0)->quan)==8,"obj_quan width");
_Static_assert(((__typeof__(((struct obj*)0)->quan))-1 < 0),"obj_quan signedness");
_Static_assert(sizeof(((struct obj*)0)->spe)==1,"obj_spe width");
_Static_assert(((__typeof__(((struct obj*)0)->spe))-1 < 0),"obj_spe signedness");
_Static_assert(sizeof(((struct obj*)0)->where)==1,"obj_where width");
_Static_assert(((__typeof__(((struct obj*)0)->where))-1 < 0),"obj_where signedness");
_Static_assert(sizeof(((struct c_color_names*)0)->c_amber)==8,"colors_c_amber pointer width");
_Static_assert(sizeof(((struct c_color_names*)0)->c_black)==8,"colors_c_black pointer width");
_Static_assert(sizeof(((struct c_color_names*)0)->c_light_blue)==8,"colors_c_light_blue pointer width");
_Static_assert(sizeof(((struct c_color_names*)0)->c_orange)==8,"colors_c_orange pointer width");
_Static_assert(sizeof(((struct c_color_names*)0)->c_red)==8,"colors_c_red pointer width");
_Static_assert(sizeof(((struct instance_flags*)0)->last_msg)==4,"iflags_last_msg width");
_Static_assert(((__typeof__(((struct instance_flags*)0)->last_msg))-1 < 0),"iflags_last_msg signedness");
_Static_assert(sizeof(((struct instance_flags*)0)->menu_requested)==1,"iflags_menu_requested width");
_Static_assert(((__typeof__(((struct instance_flags*)0)->menu_requested))-1 < 0),"iflags_menu_requested signedness");
_Static_assert(sizeof(((struct c_common_strings*)0)->c_Something)==8,"strings_c_Something pointer width");
_Static_assert(sizeof(((struct c_common_strings*)0)->c_You_can_move_again)==8,"strings_c_You_can_move_again pointer width");
_Static_assert(sizeof(((struct c_common_strings*)0)->c_nothing_happens)==8,"strings_c_nothing_happens pointer width");
_Static_assert(sizeof(((struct c_common_strings*)0)->c_nothing_seems_to_happen)==8,"strings_c_nothing_seems_to_happen pointer width");
_Static_assert(sizeof(((struct c_common_strings*)0)->c_something)==8,"strings_c_something pointer width");
_Static_assert(sizeof(((struct c_common_strings*)0)->c_vision_clears)==8,"strings_c_vision_clears pointer width");
_Static_assert(sizeof(((struct u_conduct*)0)->polypiles)==8,"conduct_polypiles width");
_Static_assert(((__typeof__(((struct u_conduct*)0)->polypiles))-1 < 0),"conduct_polypiles signedness");
_Static_assert(sizeof(((struct flag*)0)->beginner)==1,"flags_beginner width");
_Static_assert(((__typeof__(((struct flag*)0)->beginner))-1 < 0),"flags_beginner signedness");
_Static_assert(sizeof(((struct flag*)0)->female)==1,"flags_female width");
_Static_assert(((__typeof__(((struct flag*)0)->female))-1 < 0),"flags_female signedness");
_Static_assert(sizeof(((struct flag*)0)->pickup_burden)==4,"flags_pickup_burden width");
_Static_assert(((__typeof__(((struct flag*)0)->pickup_burden))-1 < 0),"flags_pickup_burden signedness");
_Static_assert(sizeof(((struct flag*)0)->verbose)==1,"flags_verbose width");
_Static_assert(((__typeof__(((struct flag*)0)->verbose))-1 < 0),"flags_verbose signedness");
_Static_assert(sizeof(((struct instance_globals_v*)0)->vision_full_recalc)==1,"gv_vision_full_recalc width");
_Static_assert(((__typeof__(((struct instance_globals_v*)0)->vision_full_recalc))-1 < 0),"gv_vision_full_recalc signedness");
_Static_assert(sizeof(((struct instance_globals_v*)0)->viz_array)==8,"gv_viz_array pointer width");
_Static_assert(sizeof(((struct Role*)0)->mnum)==2,"role_mnum width");
_Static_assert(((__typeof__(((struct Role*)0)->mnum))-1 < 0),"role_mnum signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_descr_idx)==2,"cls_oc_descr_idx width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_descr_idx))-1 < 0),"cls_oc_descr_idx signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_skill)==1,"cls_oc_skill width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_skill))-1 < 0),"cls_oc_skill signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_subtyp)==1,"cls_oc_subtyp width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_subtyp))-1 < 0),"cls_oc_subtyp signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_uname)==8,"cls_oc_uname pointer width");
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
_Static_assert(sizeof(((struct mvitals*)0)->born)==1,"vital_born width");
_Static_assert(((__typeof__(((struct mvitals*)0)->born))-1 > 0),"vital_born signedness");
_Static_assert(sizeof(((struct mvitals*)0)->mvflags)==1,"vital_mvflags width");
_Static_assert(((__typeof__(((struct mvitals*)0)->mvflags))-1 > 0),"vital_mvflags signedness");
_Static_assert(sizeof(((struct instance_globals_p*)0)->potion_nothing)==4,"gp_potion_nothing width");
_Static_assert(((__typeof__(((struct instance_globals_p*)0)->potion_nothing))-1 < 0),"gp_potion_nothing signedness");
_Static_assert(sizeof(((struct instance_globals_p*)0)->potion_unkn)==4,"gp_potion_unkn width");
_Static_assert(((__typeof__(((struct instance_globals_p*)0)->potion_unkn))-1 < 0),"gp_potion_unkn signedness");
_Static_assert(sizeof(((struct instance_globals_m*)0)->mentioned_water)==1,"gm_mentioned_water width");
_Static_assert(((__typeof__(((struct instance_globals_m*)0)->mentioned_water))-1 < 0),"gm_mentioned_water signedness");
_Static_assert(sizeof(((struct instance_globals_m*)0)->multi)==8,"gm_multi width");
_Static_assert(((__typeof__(((struct instance_globals_m*)0)->multi))-1 < 0),"gm_multi signedness");
_Static_assert(sizeof(((struct instance_globals_m*)0)->multi_reason)==8,"gm_multi_reason pointer width");
_Static_assert(sizeof(((struct d_level*)0)->dlevel)==2,"level_dlevel width");
_Static_assert(((__typeof__(((struct d_level*)0)->dlevel))-1 < 0),"level_dlevel signedness");
_Static_assert(sizeof(((struct d_level*)0)->dnum)==2,"level_dnum width");
_Static_assert(((__typeof__(((struct d_level*)0)->dnum))-1 < 0),"level_dnum signedness");
_Static_assert(sizeof(((struct rm*)0)->glyph)==4,"rm_glyph width");
_Static_assert(((__typeof__(((struct rm*)0)->glyph))-1 < 0),"rm_glyph signedness");
_Static_assert(sizeof(((struct rm*)0)->typ)==1,"rm_typ width");
_Static_assert(((__typeof__(((struct rm*)0)->typ))-1 < 0),"rm_typ signedness");
_Static_assert(sizeof(((struct objdescr*)0)->oc_descr)==8,"descr_oc_descr pointer width");
_Static_assert(sizeof(((struct skills*)0)->skill)==2,"skill_skill width");
_Static_assert(((__typeof__(((struct skills*)0)->skill))-1 < 0),"skill_skill signedness");
_Static_assert(sizeof(((struct u_roleplay*)0)->deaf)==1,"roleplay_deaf width");
_Static_assert(((__typeof__(((struct u_roleplay*)0)->deaf))-1 < 0),"roleplay_deaf signedness");
_Static_assert(sizeof(((struct instance_globals_n*)0)->nomovemsg)==8,"gn_nomovemsg pointer width");
_Static_assert(sizeof(((struct instance_globals_n*)0)->notonhead)==1,"gn_notonhead width");
_Static_assert(((__typeof__(((struct instance_globals_n*)0)->notonhead))-1 < 0),"gn_notonhead signedness");
_Static_assert(sizeof(((struct Gender*)0)->he)==8,"gender_he pointer width");
_Static_assert(sizeof(((struct Gender*)0)->him)==8,"gender_him pointer width");
_Static_assert(sizeof(((struct Gender*)0)->his)==8,"gender_his pointer width");
_Static_assert(sizeof(((struct stairway*)0)->up)==1,"stair_up width");
_Static_assert(((__typeof__(((struct stairway*)0)->up))-1 < 0),"stair_up signedness");
_Static_assert(sizeof(((struct align*)0)->type)==1,"align_type width");
_Static_assert(((__typeof__(((struct align*)0)->type))-1 < 0),"align_type signedness");
_Static_assert(sizeof(((struct context_info*)0)->mon_moving)==1,"context_mon_moving width");
_Static_assert(((__typeof__(((struct context_info*)0)->mon_moving))-1 < 0),"context_mon_moving signedness");
_Static_assert(sizeof(((struct display_hints*)0)->botl)==1,"disp_botl width");
_Static_assert(((__typeof__(((struct display_hints*)0)->botl))-1 < 0),"disp_botl signedness");
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
_Static_assert(sizeof(((struct kinfo*)0)->format)==4,"killer_format width");
_Static_assert(((__typeof__(((struct kinfo*)0)->format))-1 < 0),"killer_format signedness");
_Static_assert(sizeof(((__typeof__(svl.level)*)0)->monlist)==8,"dlevel_monlist pointer width");
_Static_assert(__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__,"POTION little endian ABI");
#if !defined(DEBUG)||defined(SND_LIB_INTEGRATED)
#error Review POTION configured profile
#endif
size_t probe_context_size(void){return sizeof(struct obj);}
int probe_layout_count(void){return sizeof teleport_potion_layout/sizeof teleport_potion_layout[0];}
const char*probe_layout_name(int i){return teleport_potion_layout[i].name;}
size_t probe_layout_value(int i){return teleport_potion_layout[i].value;}
#endif
