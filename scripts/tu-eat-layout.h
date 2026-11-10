/* EAT compiler-derived fields and ABI guards; no eat policy. */
#ifndef TELEPORT_EAT_LAYOUT_H
#define TELEPORT_EAT_LAYOUT_H
#include "hack.h"
#include <stddef.h>
#define EAT_META(k,v) {#k,(size_t)(v)}
static const struct {const char*name;size_t value;}teleport_eat_layout[]={
EAT_META(pointerSize,sizeof(void*)),
EAT_META(intSize,sizeof(int)),
EAT_META(longSize,sizeof(long)),
EAT_META(coordxySize,sizeof(coordxy)),
EAT_META(booleanSize,sizeof(boolean)),
EAT_META(objSize,sizeof(struct obj)),
EAT_META(victualSize,sizeof(struct victual_info)),
EAT_META(monSize,sizeof(struct monst)),
EAT_META(mon_data,offsetof(struct monst,data)),
EAT_META(mon_data_size,sizeof(((struct monst*)0)->data)),
EAT_META(mon_m_ap_type,offsetof(struct monst,m_ap_type)),
EAT_META(mon_m_ap_type_size,sizeof(((struct monst*)0)->m_ap_type)),
EAT_META(mon_mappearance,offsetof(struct monst,mappearance)),
EAT_META(mon_mappearance_size,sizeof(((struct monst*)0)->mappearance)),
EAT_META(mon_mextra,offsetof(struct monst,mextra)),
EAT_META(mon_mextra_size,sizeof(((struct monst*)0)->mextra)),
EAT_META(mon_mhp,offsetof(struct monst,mhp)),
EAT_META(mon_mhp_size,sizeof(((struct monst*)0)->mhp)),
EAT_META(mon_mtame,offsetof(struct monst,mtame)),
EAT_META(mon_mtame_size,sizeof(((struct monst*)0)->mtame)),
EAT_META(mon_mx,offsetof(struct monst,mx)),
EAT_META(mon_mx_size,sizeof(((struct monst*)0)->mx)),
EAT_META(mon_my,offsetof(struct monst,my)),
EAT_META(mon_my_size,sizeof(((struct monst*)0)->my)),
EAT_META(youSize,sizeof(struct you)),
EAT_META(you_acurr,offsetof(struct you,acurr)),
EAT_META(you_acurr_size,sizeof(((struct you*)0)->acurr)),
EAT_META(you_aexe,offsetof(struct you,aexe)),
EAT_META(you_aexe_size,sizeof(((struct you*)0)->aexe)),
EAT_META(you_amax,offsetof(struct you,amax)),
EAT_META(you_amax_size,sizeof(((struct you*)0)->amax)),
EAT_META(you_atemp,offsetof(struct you,atemp)),
EAT_META(you_atemp_size,sizeof(((struct you*)0)->atemp)),
EAT_META(you_mh,offsetof(struct you,mh)),
EAT_META(you_mh_size,sizeof(((struct you*)0)->mh)),
EAT_META(you_mhmax,offsetof(struct you,mhmax)),
EAT_META(you_mhmax_size,sizeof(((struct you*)0)->mhmax)),
EAT_META(you_ualign,offsetof(struct you,ualign)),
EAT_META(you_ualign_size,sizeof(((struct you*)0)->ualign)),
EAT_META(you_ublessed,offsetof(struct you,ublessed)),
EAT_META(you_ublessed_size,sizeof(((struct you*)0)->ublessed)),
EAT_META(you_uconduct,offsetof(struct you,uconduct)),
EAT_META(you_uconduct_size,sizeof(((struct you*)0)->uconduct)),
EAT_META(you_ucreamed,offsetof(struct you,ucreamed)),
EAT_META(you_ucreamed_size,sizeof(((struct you*)0)->ucreamed)),
EAT_META(you_udaminc,offsetof(struct you,udaminc)),
EAT_META(you_udaminc_size,sizeof(((struct you*)0)->udaminc)),
EAT_META(you_uen,offsetof(struct you,uen)),
EAT_META(you_uen_size,sizeof(((struct you*)0)->uen)),
EAT_META(you_uenmax,offsetof(struct you,uenmax)),
EAT_META(you_uenmax_size,sizeof(((struct you*)0)->uenmax)),
EAT_META(you_uenpeak,offsetof(struct you,uenpeak)),
EAT_META(you_uenpeak_size,sizeof(((struct you*)0)->uenpeak)),
EAT_META(you_uhave,offsetof(struct you,uhave)),
EAT_META(you_uhave_size,sizeof(((struct you*)0)->uhave)),
EAT_META(you_uhitinc,offsetof(struct you,uhitinc)),
EAT_META(you_uhitinc_size,sizeof(((struct you*)0)->uhitinc)),
EAT_META(you_uhp,offsetof(struct you,uhp)),
EAT_META(you_uhp_size,sizeof(((struct you*)0)->uhp)),
EAT_META(you_uhpmax,offsetof(struct you,uhpmax)),
EAT_META(you_uhpmax_size,sizeof(((struct you*)0)->uhpmax)),
EAT_META(you_uhs,offsetof(struct you,uhs)),
EAT_META(you_uhs_size,sizeof(((struct you*)0)->uhs)),
EAT_META(you_uhunger,offsetof(struct you,uhunger)),
EAT_META(you_uhunger_size,sizeof(((struct you*)0)->uhunger)),
EAT_META(you_ulycn,offsetof(struct you,ulycn)),
EAT_META(you_ulycn_size,sizeof(((struct you*)0)->ulycn)),
EAT_META(you_umonnum,offsetof(struct you,umonnum)),
EAT_META(you_umonnum_size,sizeof(((struct you*)0)->umonnum)),
EAT_META(you_umonster,offsetof(struct you,umonster)),
EAT_META(you_umonster_size,sizeof(((struct you*)0)->umonster)),
EAT_META(you_uprops,offsetof(struct you,uprops)),
EAT_META(you_uprops_size,sizeof(((struct you*)0)->uprops)),
EAT_META(you_uroleplay,offsetof(struct you,uroleplay)),
EAT_META(you_uroleplay_size,sizeof(((struct you*)0)->uroleplay)),
EAT_META(you_usteed,offsetof(struct you,usteed)),
EAT_META(you_usteed_size,sizeof(((struct you*)0)->usteed)),
EAT_META(you_ustuck,offsetof(struct you,ustuck)),
EAT_META(you_ustuck_size,sizeof(((struct you*)0)->ustuck)),
EAT_META(you_utrap,offsetof(struct you,utrap)),
EAT_META(you_utrap_size,sizeof(((struct you*)0)->utrap)),
EAT_META(you_utraptype,offsetof(struct you,utraptype)),
EAT_META(you_utraptype_size,sizeof(((struct you*)0)->utraptype)),
EAT_META(you_ux,offsetof(struct you,ux)),
EAT_META(you_ux_size,sizeof(((struct you*)0)->ux)),
EAT_META(you_uy,offsetof(struct you,uy)),
EAT_META(you_uy_size,sizeof(((struct you*)0)->uy)),
EAT_META(you_uz,offsetof(struct you,uz)),
EAT_META(you_uz_size,sizeof(((struct you*)0)->uz)),
EAT_META(propSize,sizeof(struct prop)),
EAT_META(prop_blocked,offsetof(struct prop,blocked)),
EAT_META(prop_blocked_size,sizeof(((struct prop*)0)->blocked)),
EAT_META(prop_extrinsic,offsetof(struct prop,extrinsic)),
EAT_META(prop_extrinsic_size,sizeof(((struct prop*)0)->extrinsic)),
EAT_META(prop_intrinsic,offsetof(struct prop,intrinsic)),
EAT_META(prop_intrinsic_size,sizeof(((struct prop*)0)->intrinsic)),
EAT_META(obj_age,offsetof(struct obj,age)),
EAT_META(obj_age_size,sizeof(((struct obj*)0)->age)),
EAT_META(obj_cobj,offsetof(struct obj,cobj)),
EAT_META(obj_cobj_size,sizeof(((struct obj*)0)->cobj)),
EAT_META(obj_corpsenm,offsetof(struct obj,corpsenm)),
EAT_META(obj_corpsenm_size,sizeof(((struct obj*)0)->corpsenm)),
EAT_META(obj_invlet,offsetof(struct obj,invlet)),
EAT_META(obj_invlet_size,sizeof(((struct obj*)0)->invlet)),
EAT_META(obj_nexthere,offsetof(struct obj,nexthere)),
EAT_META(obj_nexthere_size,sizeof(((struct obj*)0)->nexthere)),
EAT_META(obj_nobj,offsetof(struct obj,nobj)),
EAT_META(obj_nobj_size,sizeof(((struct obj*)0)->nobj)),
EAT_META(obj_o_id,offsetof(struct obj,o_id)),
EAT_META(obj_o_id_size,sizeof(((struct obj*)0)->o_id)),
EAT_META(obj_oartifact,offsetof(struct obj,oartifact)),
EAT_META(obj_oartifact_size,sizeof(((struct obj*)0)->oartifact)),
EAT_META(obj_oclass,offsetof(struct obj,oclass)),
EAT_META(obj_oclass_size,sizeof(((struct obj*)0)->oclass)),
EAT_META(obj_oeaten,offsetof(struct obj,oeaten)),
EAT_META(obj_oeaten_size,sizeof(((struct obj*)0)->oeaten)),
EAT_META(obj_otyp,offsetof(struct obj,otyp)),
EAT_META(obj_otyp_size,sizeof(((struct obj*)0)->otyp)),
EAT_META(obj_owornmask,offsetof(struct obj,owornmask)),
EAT_META(obj_owornmask_size,sizeof(((struct obj*)0)->owornmask)),
EAT_META(obj_owt,offsetof(struct obj,owt)),
EAT_META(obj_owt_size,sizeof(((struct obj*)0)->owt)),
EAT_META(obj_ox,offsetof(struct obj,ox)),
EAT_META(obj_ox_size,sizeof(((struct obj*)0)->ox)),
EAT_META(obj_oy,offsetof(struct obj,oy)),
EAT_META(obj_oy_size,sizeof(((struct obj*)0)->oy)),
EAT_META(obj_quan,offsetof(struct obj,quan)),
EAT_META(obj_quan_size,sizeof(((struct obj*)0)->quan)),
EAT_META(obj_spe,offsetof(struct obj,spe)),
EAT_META(obj_spe_size,sizeof(((struct obj*)0)->spe)),
EAT_META(obj_timed,offsetof(struct obj,timed)),
EAT_META(obj_timed_size,sizeof(((struct obj*)0)->timed)),
EAT_META(obj_where,offsetof(struct obj,where)),
EAT_META(obj_where_size,sizeof(((struct obj*)0)->where)),
EAT_META(colorsSize,sizeof(struct c_color_names)),
EAT_META(colors_c_green,offsetof(struct c_color_names,c_green)),
EAT_META(colors_c_green_size,sizeof(((struct c_color_names*)0)->c_green)),
EAT_META(iflagsSize,sizeof(struct instance_flags)),
EAT_META(iflags_debug_hunger,offsetof(struct instance_flags,debug_hunger)),
EAT_META(iflags_debug_hunger_size,sizeof(((struct instance_flags*)0)->debug_hunger)),
EAT_META(iflags_last_msg,offsetof(struct instance_flags,last_msg)),
EAT_META(iflags_last_msg_size,sizeof(((struct instance_flags*)0)->last_msg)),
EAT_META(iflags_menu_requested,offsetof(struct instance_flags,menu_requested)),
EAT_META(iflags_menu_requested_size,sizeof(((struct instance_flags*)0)->menu_requested)),
EAT_META(iflags_override_ID,offsetof(struct instance_flags,override_ID)),
EAT_META(iflags_override_ID_size,sizeof(((struct instance_flags*)0)->override_ID)),
EAT_META(stringsSize,sizeof(struct c_common_strings)),
EAT_META(strings_c_You_can_move_again,offsetof(struct c_common_strings,c_You_can_move_again)),
EAT_META(strings_c_You_can_move_again_size,sizeof(((struct c_common_strings*)0)->c_You_can_move_again)),
EAT_META(strings_c_something,offsetof(struct c_common_strings,c_something)),
EAT_META(strings_c_something_size,sizeof(((struct c_common_strings*)0)->c_something)),
EAT_META(strings_c_vision_clears,offsetof(struct c_common_strings,c_vision_clears)),
EAT_META(strings_c_vision_clears_size,sizeof(((struct c_common_strings*)0)->c_vision_clears)),
EAT_META(conductSize,sizeof(struct u_conduct)),
EAT_META(conduct_food,offsetof(struct u_conduct,food)),
EAT_META(conduct_food_size,sizeof(((struct u_conduct*)0)->food)),
EAT_META(conduct_literate,offsetof(struct u_conduct,literate)),
EAT_META(conduct_literate_size,sizeof(((struct u_conduct*)0)->literate)),
EAT_META(conduct_polyselfs,offsetof(struct u_conduct,polyselfs)),
EAT_META(conduct_polyselfs_size,sizeof(((struct u_conduct*)0)->polyselfs)),
EAT_META(conduct_unvegan,offsetof(struct u_conduct,unvegan)),
EAT_META(conduct_unvegan_size,sizeof(((struct u_conduct*)0)->unvegan)),
EAT_META(conduct_unvegetarian,offsetof(struct u_conduct,unvegetarian)),
EAT_META(conduct_unvegetarian_size,sizeof(((struct u_conduct*)0)->unvegetarian)),
EAT_META(flagsSize,sizeof(struct flag)),
EAT_META(flags_acoustics,offsetof(struct flag,acoustics)),
EAT_META(flags_acoustics_size,sizeof(((struct flag*)0)->acoustics)),
EAT_META(flags_female,offsetof(struct flag,female)),
EAT_META(flags_female_size,sizeof(((struct flag*)0)->female)),
EAT_META(flags_paranoia_bits,offsetof(struct flag,paranoia_bits)),
EAT_META(flags_paranoia_bits_size,sizeof(((struct flag*)0)->paranoia_bits)),
EAT_META(flags_verbose,offsetof(struct flag,verbose)),
EAT_META(flags_verbose_size,sizeof(((struct flag*)0)->verbose)),
EAT_META(topologySize,sizeof(struct dgn_topology)),
EAT_META(topology_d_air_level,offsetof(struct dgn_topology,d_air_level)),
EAT_META(topology_d_air_level_size,sizeof(((struct dgn_topology*)0)->d_air_level)),
EAT_META(topology_d_astral_level,offsetof(struct dgn_topology,d_astral_level)),
EAT_META(topology_d_astral_level_size,sizeof(((struct dgn_topology*)0)->d_astral_level)),
EAT_META(topology_d_water_level,offsetof(struct dgn_topology,d_water_level)),
EAT_META(topology_d_water_level_size,sizeof(((struct dgn_topology*)0)->d_water_level)),
EAT_META(gvSize,sizeof(struct instance_globals_v)),
EAT_META(gv_vision_full_recalc,offsetof(struct instance_globals_v,vision_full_recalc)),
EAT_META(gv_vision_full_recalc_size,sizeof(((struct instance_globals_v*)0)->vision_full_recalc)),
EAT_META(gv_viz_array,offsetof(struct instance_globals_v,viz_array)),
EAT_META(gv_viz_array_size,sizeof(((struct instance_globals_v*)0)->viz_array)),
EAT_META(svmSize,sizeof(struct instance_globals_saved_m)),
EAT_META(svm_moves,offsetof(struct instance_globals_saved_m,moves)),
EAT_META(svm_moves_size,sizeof(((struct instance_globals_saved_m*)0)->moves)),
EAT_META(roleSize,sizeof(struct Role)),
EAT_META(role_mnum,offsetof(struct Role,mnum)),
EAT_META(role_mnum_size,sizeof(((struct Role*)0)->mnum)),
EAT_META(role_name,offsetof(struct Role,name)),
EAT_META(role_name_size,sizeof(((struct Role*)0)->name)),
EAT_META(clsSize,sizeof(struct objclass)),
EAT_META(cls_oc_delay,offsetof(struct objclass,oc_delay)),
EAT_META(cls_oc_delay_size,sizeof(((struct objclass*)0)->oc_delay)),
EAT_META(cls_oc_nutrition,offsetof(struct objclass,oc_nutrition)),
EAT_META(cls_oc_nutrition_size,sizeof(((struct objclass*)0)->oc_nutrition)),
EAT_META(cls_oc_oprop,offsetof(struct objclass,oc_oprop)),
EAT_META(cls_oc_oprop_size,sizeof(((struct objclass*)0)->oc_oprop)),
EAT_META(cls_oc_skill,offsetof(struct objclass,oc_skill)),
EAT_META(cls_oc_skill_size,sizeof(((struct objclass*)0)->oc_skill)),
EAT_META(pmSize,sizeof(struct permonst)),
EAT_META(pm_cnutrit,offsetof(struct permonst,cnutrit)),
EAT_META(pm_cnutrit_size,sizeof(((struct permonst*)0)->cnutrit)),
EAT_META(pm_cwt,offsetof(struct permonst,cwt)),
EAT_META(pm_cwt_size,sizeof(((struct permonst*)0)->cwt)),
EAT_META(pm_geno,offsetof(struct permonst,geno)),
EAT_META(pm_geno_size,sizeof(((struct permonst*)0)->geno)),
EAT_META(pm_mattk,offsetof(struct permonst,mattk)),
EAT_META(pm_mattk_size,sizeof(((struct permonst*)0)->mattk)),
EAT_META(pm_mconveys,offsetof(struct permonst,mconveys)),
EAT_META(pm_mconveys_size,sizeof(((struct permonst*)0)->mconveys)),
EAT_META(pm_mflags1,offsetof(struct permonst,mflags1)),
EAT_META(pm_mflags1_size,sizeof(((struct permonst*)0)->mflags1)),
EAT_META(pm_mflags2,offsetof(struct permonst,mflags2)),
EAT_META(pm_mflags2_size,sizeof(((struct permonst*)0)->mflags2)),
EAT_META(pm_mflags3,offsetof(struct permonst,mflags3)),
EAT_META(pm_mflags3_size,sizeof(((struct permonst*)0)->mflags3)),
EAT_META(pm_mlet,offsetof(struct permonst,mlet)),
EAT_META(pm_mlet_size,sizeof(((struct permonst*)0)->mlet)),
EAT_META(pm_mlevel,offsetof(struct permonst,mlevel)),
EAT_META(pm_mlevel_size,sizeof(((struct permonst*)0)->mlevel)),
EAT_META(pm_mmove,offsetof(struct permonst,mmove)),
EAT_META(pm_mmove_size,sizeof(((struct permonst*)0)->mmove)),
EAT_META(pm_msize,offsetof(struct permonst,msize)),
EAT_META(pm_msize_size,sizeof(((struct permonst*)0)->msize)),
EAT_META(pm_pmidx,offsetof(struct permonst,pmidx)),
EAT_META(pm_pmidx_size,sizeof(((struct permonst*)0)->pmidx)),
EAT_META(pm_pmnames,offsetof(struct permonst,pmnames)),
EAT_META(pm_pmnames_size,sizeof(((struct permonst*)0)->pmnames)),
EAT_META(vitalSize,sizeof(struct mvitals)),
EAT_META(gpSize,sizeof(struct instance_globals_p)),
EAT_META(gmSize,sizeof(struct instance_globals_m)),
EAT_META(gm_multi,offsetof(struct instance_globals_m,multi)),
EAT_META(gm_multi_size,sizeof(((struct instance_globals_m*)0)->multi)),
EAT_META(gm_multi_reason,offsetof(struct instance_globals_m,multi_reason)),
EAT_META(gm_multi_reason_size,sizeof(((struct instance_globals_m*)0)->multi_reason)),
EAT_META(attribsSize,sizeof(struct attribs)),
EAT_META(attribs_a,offsetof(struct attribs,a)),
EAT_META(attribs_a_size,sizeof(((struct attribs*)0)->a)),
EAT_META(levelSize,sizeof(struct d_level)),
EAT_META(level_dlevel,offsetof(struct d_level,dlevel)),
EAT_META(level_dlevel_size,sizeof(((struct d_level*)0)->dlevel)),
EAT_META(level_dnum,offsetof(struct d_level,dnum)),
EAT_META(level_dnum_size,sizeof(((struct d_level*)0)->dnum)),
EAT_META(rmSize,sizeof(struct rm)),
EAT_META(rm_typ,offsetof(struct rm,typ)),
EAT_META(rm_typ_size,sizeof(((struct rm*)0)->typ)),
EAT_META(svlSize,sizeof(struct instance_globals_saved_l)),
EAT_META(svl_level,offsetof(struct instance_globals_saved_l,level)),
EAT_META(svl_level_size,sizeof(((struct instance_globals_saved_l*)0)->level)),
EAT_META(descrSize,sizeof(struct objdescr)),
EAT_META(descr_oc_descr,offsetof(struct objdescr,oc_descr)),
EAT_META(descr_oc_descr_size,sizeof(((struct objdescr*)0)->oc_descr)),
EAT_META(skillSize,sizeof(struct skills)),
EAT_META(roleplaySize,sizeof(struct u_roleplay)),
EAT_META(roleplay_deaf,offsetof(struct u_roleplay,deaf)),
EAT_META(roleplay_deaf_size,sizeof(((struct u_roleplay*)0)->deaf)),
EAT_META(gnSize,sizeof(struct instance_globals_n)),
EAT_META(gn_nomovemsg,offsetof(struct instance_globals_n,nomovemsg)),
EAT_META(gn_nomovemsg_size,sizeof(((struct instance_globals_n*)0)->nomovemsg)),
EAT_META(svcSize,sizeof(struct instance_globals_saved_c)),
EAT_META(svc_context,offsetof(struct instance_globals_saved_c,context)),
EAT_META(svc_context_size,sizeof(((struct instance_globals_saved_c*)0)->context)),
EAT_META(genderSize,sizeof(struct Gender)),
EAT_META(gender_he,offsetof(struct Gender,he)),
EAT_META(gender_he_size,sizeof(((struct Gender*)0)->he)),
EAT_META(gender_him,offsetof(struct Gender,him)),
EAT_META(gender_him_size,sizeof(((struct Gender*)0)->him)),
EAT_META(stairSize,sizeof(struct stairway)),
EAT_META(alignSize,sizeof(struct align)),
EAT_META(align_type,offsetof(struct align,type)),
EAT_META(align_type_size,sizeof(((struct align*)0)->type)),
EAT_META(contextSize,sizeof(struct context_info)),
EAT_META(context_current_fruit,offsetof(struct context_info,current_fruit)),
EAT_META(context_current_fruit_size,sizeof(((struct context_info*)0)->current_fruit)),
EAT_META(context_digging,offsetof(struct context_info,digging)),
EAT_META(context_digging_size,sizeof(((struct context_info*)0)->digging)),
EAT_META(context_tin,offsetof(struct context_info,tin)),
EAT_META(context_tin_size,sizeof(((struct context_info*)0)->tin)),
EAT_META(context_victual,offsetof(struct context_info,victual)),
EAT_META(context_victual_size,sizeof(((struct context_info*)0)->victual)),
EAT_META(gySize,sizeof(struct instance_globals_y)),
EAT_META(gy_youmonst,offsetof(struct instance_globals_y,youmonst)),
EAT_META(gy_youmonst_size,sizeof(((struct instance_globals_y*)0)->youmonst)),
EAT_META(guSize,sizeof(struct instance_globals_u)),
EAT_META(gu_urace,offsetof(struct instance_globals_u,urace)),
EAT_META(gu_urace_size,sizeof(((struct instance_globals_u*)0)->urace)),
EAT_META(gu_urole,offsetof(struct instance_globals_u,urole)),
EAT_META(gu_urole_size,sizeof(((struct instance_globals_u*)0)->urole)),
EAT_META(svdSize,sizeof(struct instance_globals_saved_d)),
EAT_META(svd_dungeon_topology,offsetof(struct instance_globals_saved_d,dungeon_topology)),
EAT_META(svd_dungeon_topology_size,sizeof(((struct instance_globals_saved_d*)0)->dungeon_topology)),
EAT_META(cgSize,sizeof(struct const_globals)),
EAT_META(haveSize,sizeof(struct u_have)),
EAT_META(dispSize,sizeof(struct display_hints)),
EAT_META(disp_botl,offsetof(struct display_hints,botl)),
EAT_META(disp_botl_size,sizeof(((struct display_hints*)0)->botl)),
EAT_META(raceSize,sizeof(struct Race)),
EAT_META(race_attrmax,offsetof(struct Race,attrmax)),
EAT_META(race_attrmax_size,sizeof(((struct Race*)0)->attrmax)),
EAT_META(race_attrmin,offsetof(struct Race,attrmin)),
EAT_META(race_attrmin_size,sizeof(((struct Race*)0)->attrmin)),
EAT_META(race_mnum,offsetof(struct Race,mnum)),
EAT_META(race_mnum_size,sizeof(((struct Race*)0)->mnum)),
EAT_META(race_noun,offsetof(struct Race,noun)),
EAT_META(race_noun_size,sizeof(((struct Race*)0)->noun)),
EAT_META(race_selfmask,offsetof(struct Race,selfmask)),
EAT_META(race_selfmask_size,sizeof(((struct Race*)0)->selfmask)),
EAT_META(giSize,sizeof(struct instance_globals_i)),
EAT_META(gi_invent,offsetof(struct instance_globals_i,invent)),
EAT_META(gi_invent_size,sizeof(((struct instance_globals_i*)0)->invent)),
EAT_META(attackSize,sizeof(struct attack)),
EAT_META(attack_aatyp,offsetof(struct attack,aatyp)),
EAT_META(attack_aatyp_size,sizeof(((struct attack*)0)->aatyp)),
EAT_META(attack_adtyp,offsetof(struct attack,adtyp)),
EAT_META(attack_adtyp_size,sizeof(((struct attack*)0)->adtyp)),
EAT_META(attack_damd,offsetof(struct attack,damd)),
EAT_META(attack_damd_size,sizeof(((struct attack*)0)->damd)),
EAT_META(attack_damn,offsetof(struct attack,damn)),
EAT_META(attack_damn_size,sizeof(((struct attack*)0)->damn)),
EAT_META(coordSize,sizeof(struct nhcoord)),
EAT_META(coord_x,offsetof(struct nhcoord,x)),
EAT_META(coord_x_size,sizeof(((struct nhcoord*)0)->x)),
EAT_META(coord_y,offsetof(struct nhcoord,y)),
EAT_META(coord_y_size,sizeof(((struct nhcoord*)0)->y)),
EAT_META(killerSize,sizeof(struct kinfo)),
EAT_META(killer_format,offsetof(struct kinfo,format)),
EAT_META(killer_format_size,sizeof(((struct kinfo*)0)->format)),
EAT_META(killer_name,offsetof(struct kinfo,name)),
EAT_META(killer_name_size,sizeof(((struct kinfo*)0)->name)),
EAT_META(victual_nmod,offsetof(struct victual_info,nmod)),
EAT_META(victual_nmod_size,sizeof(((struct victual_info*)0)->nmod)),
EAT_META(victual_o_id,offsetof(struct victual_info,o_id)),
EAT_META(victual_o_id_size,sizeof(((struct victual_info*)0)->o_id)),
EAT_META(victual_piece,offsetof(struct victual_info,piece)),
EAT_META(victual_piece_size,sizeof(((struct victual_info*)0)->piece)),
EAT_META(victual_reqtime,offsetof(struct victual_info,reqtime)),
EAT_META(victual_reqtime_size,sizeof(((struct victual_info*)0)->reqtime)),
EAT_META(victual_usedtime,offsetof(struct victual_info,usedtime)),
EAT_META(victual_usedtime_size,sizeof(((struct victual_info*)0)->usedtime)),
EAT_META(tinSize,sizeof(struct tin_info)),
EAT_META(tin_o_id,offsetof(struct tin_info,o_id)),
EAT_META(tin_o_id_size,sizeof(((struct tin_info*)0)->o_id)),
EAT_META(tin_reqtime,offsetof(struct tin_info,reqtime)),
EAT_META(tin_reqtime_size,sizeof(((struct tin_info*)0)->reqtime)),
EAT_META(tin_tin,offsetof(struct tin_info,tin)),
EAT_META(tin_tin_size,sizeof(((struct tin_info*)0)->tin)),
EAT_META(tin_usedtime,offsetof(struct tin_info,usedtime)),
EAT_META(tin_usedtime_size,sizeof(((struct tin_info*)0)->usedtime)),
EAT_META(geSize,sizeof(struct instance_globals_e)),
EAT_META(ge_eatmbuf,offsetof(struct instance_globals_e,eatmbuf)),
EAT_META(ge_eatmbuf_size,sizeof(((struct instance_globals_e*)0)->eatmbuf)),
EAT_META(gaSize,sizeof(struct instance_globals_a)),
EAT_META(ga_afternmv,offsetof(struct instance_globals_a,afternmv)),
EAT_META(ga_afternmv_size,sizeof(((struct instance_globals_a*)0)->afternmv)),
EAT_META(goSize,sizeof(struct instance_globals_o)),
EAT_META(go_occupation,offsetof(struct instance_globals_o,occupation)),
EAT_META(go_occupation_size,sizeof(((struct instance_globals_o*)0)->occupation)),
EAT_META(gcSize,sizeof(struct instance_globals_c)),
EAT_META(gc_corpsenm_digested,offsetof(struct instance_globals_c,corpsenm_digested)),
EAT_META(gc_corpsenm_digested_size,sizeof(((struct instance_globals_c*)0)->corpsenm_digested)),
EAT_META(gfSize,sizeof(struct instance_globals_f)),
EAT_META(gf_force_save_hs,offsetof(struct instance_globals_f,force_save_hs)),
EAT_META(gf_force_save_hs_size,sizeof(((struct instance_globals_f*)0)->force_save_hs)),
EAT_META(svkSize,sizeof(struct instance_globals_saved_k)),
EAT_META(svk_killer,offsetof(struct instance_globals_saved_k,killer)),
EAT_META(svk_killer_size,sizeof(((struct instance_globals_saved_k*)0)->killer)),
EAT_META(edogSize,sizeof(struct edog)),
EAT_META(edog_hungrytime,offsetof(struct edog,hungrytime)),
EAT_META(edog_hungrytime_size,sizeof(((struct edog*)0)->hungrytime)),
EAT_META(mextraSize,sizeof(struct mextra)),
EAT_META(mextra_edog,offsetof(struct mextra,edog)),
EAT_META(mextra_edog_size,sizeof(((struct mextra*)0)->edog)),
EAT_META(digSize,sizeof(struct dig_info)),
EAT_META(dig_chew,offsetof(struct dig_info,chew)),
EAT_META(dig_chew_size,sizeof(((struct dig_info*)0)->chew)),
EAT_META(dig_level,offsetof(struct dig_info,level)),
EAT_META(dig_level_size,sizeof(((struct dig_info*)0)->level)),
EAT_META(dig_pos,offsetof(struct dig_info,pos)),
EAT_META(dig_pos_size,sizeof(((struct dig_info*)0)->pos)),
EAT_META(rolenameSize,sizeof(struct RoleName)),
EAT_META(rolename_m,offsetof(struct RoleName,m)),
EAT_META(rolename_m_size,sizeof(((struct RoleName*)0)->m)),
EAT_META(dlevelSize,sizeof(__typeof__(svl.level))),
EAT_META(dlevel_locations,offsetof(__typeof__(svl.level),locations)),
EAT_META(dlevel_locations_size,sizeof(((__typeof__(svl.level)*)0)->locations)),
EAT_META(dlevel_monlist,offsetof(__typeof__(svl.level),monlist)),
EAT_META(dlevel_monlist_size,sizeof(((__typeof__(svl.level)*)0)->monlist)),
EAT_META(dlevel_monsters,offsetof(__typeof__(svl.level),monsters)),
EAT_META(dlevel_monsters_size,sizeof(((__typeof__(svl.level)*)0)->monsters)),
EAT_META(dlevel_objects,offsetof(__typeof__(svl.level),objects)),
EAT_META(dlevel_objects_size,sizeof(((__typeof__(svl.level)*)0)->objects)),
EAT_META(ACID_RES,ACID_RES),
EAT_META(AD_ACID,AD_ACID),
EAT_META(AD_BLND,AD_BLND),
EAT_META(AD_DISE,AD_DISE),
EAT_META(AD_HALU,AD_HALU),
EAT_META(AD_POLY,AD_POLY),
EAT_META(AD_STUN,AD_STUN),
EAT_META(AGGRAVATE_MONSTER,AGGRAVATE_MONSTER),
EAT_META(ALTAR,ALTAR),
EAT_META(AMULET_CLASS,AMULET_CLASS),
EAT_META(AMULET_OF_CHANGE,AMULET_OF_CHANGE),
EAT_META(AMULET_OF_FLYING,AMULET_OF_FLYING),
EAT_META(AMULET_OF_GUARDING,AMULET_OF_GUARDING),
EAT_META(AMULET_OF_LIFE_SAVING,AMULET_OF_LIFE_SAVING),
EAT_META(AMULET_OF_REFLECTION,AMULET_OF_REFLECTION),
EAT_META(AMULET_OF_RESTFUL_SLEEP,AMULET_OF_RESTFUL_SLEEP),
EAT_META(AMULET_OF_STRANGULATION,AMULET_OF_STRANGULATION),
EAT_META(AMULET_OF_UNCHANGING,AMULET_OF_UNCHANGING),
EAT_META(AMULET_OF_YENDOR,AMULET_OF_YENDOR),
EAT_META(ANTIMAGIC,ANTIMAGIC),
EAT_META(APPLE,APPLE),
EAT_META(ARMOR_CLASS,ARMOR_CLASS),
EAT_META(ARM_BOOTS,ARM_BOOTS),
EAT_META(ARM_GLOVES,ARM_GLOVES),
EAT_META(ART_EYES_OF_THE_OVERWORLD,ART_EYES_OF_THE_OVERWORLD),
EAT_META(ART_ORB_OF_DETECTION,ART_ORB_OF_DETECTION),
EAT_META(ATHAME,ATHAME),
EAT_META(AT_BREA,AT_BREA),
EAT_META(AT_ENGL,AT_ENGL),
EAT_META(AT_MAGC,AT_MAGC),
EAT_META(AXE,AXE),
EAT_META(A_CHA,A_CHA),
EAT_META(A_CON,A_CON),
EAT_META(A_DEX,A_DEX),
EAT_META(A_INT,A_INT),
EAT_META(A_LAWFUL,A_LAWFUL),
EAT_META(A_MAX,A_MAX),
EAT_META(A_STR,A_STR),
EAT_META(A_WIS,A_WIS),
EAT_META(BALL_CLASS,BALL_CLASS),
EAT_META(BEARTRAP,BEARTRAP),
EAT_META(BEAR_TRAP,BEAR_TRAP),
EAT_META(BLINDED,BLINDED),
EAT_META(BONE,BONE),
EAT_META(BUFSZ,BUFSZ),
EAT_META(BY_COOKIE,BY_COOKIE),
EAT_META(CANDY_BAR,CANDY_BAR),
EAT_META(CARROT,CARROT),
EAT_META(CHAIN_CLASS,CHAIN_CLASS),
EAT_META(CHOKING,CHOKING),
EAT_META(CLOVE_OF_GARLIC,CLOVE_OF_GARLIC),
EAT_META(COIN_CLASS,COIN_CLASS),
EAT_META(COLD_RES,COLD_RES),
EAT_META(COLNO,COLNO),
EAT_META(CONFLICT,CONFLICT),
EAT_META(CONFUSION,CONFUSION),
EAT_META(COPPER,COPPER),
EAT_META(CORPSE,CORPSE),
EAT_META(COST_BITE,COST_BITE),
EAT_META(COST_DSTROY,COST_DSTROY),
EAT_META(COST_OPEN,COST_OPEN),
EAT_META(COULD_SEE,COULD_SEE),
EAT_META(CRAM_RATION,CRAM_RATION),
EAT_META(CREAM_PIE,CREAM_PIE),
EAT_META(CRYSKNIFE,CRYSKNIFE),
EAT_META(CXN_NORMAL,CXN_NORMAL),
EAT_META(CXN_PFX_THE,CXN_PFX_THE),
EAT_META(CXN_SINGULAR,CXN_SINGULAR),
EAT_META(C_RATION,C_RATION),
EAT_META(DAGGER,DAGGER),
EAT_META(DEAF,DEAF),
EAT_META(DETECT_MONSTERS,DETECT_MONSTERS),
EAT_META(DIED,DIED),
EAT_META(DISINT_RES,DISINT_RES),
EAT_META(DISMOUNT_FELL,DISMOUNT_FELL),
EAT_META(DISPLACED,DISPLACED),
EAT_META(DRAGON_HIDE,DRAGON_HIDE),
EAT_META(ECMD_CANCEL,ECMD_CANCEL),
EAT_META(ECMD_OK,ECMD_OK),
EAT_META(ECMD_TIME,ECMD_TIME),
EAT_META(EGG,EGG),
EAT_META(ELVEN_DAGGER,ELVEN_DAGGER),
EAT_META(ENORMOUS_MEATBALL,ENORMOUS_MEATBALL),
EAT_META(EUCALYPTUS_LEAF,EUCALYPTUS_LEAF),
EAT_META(EXPL_FIERY,EXPL_FIERY),
EAT_META(FAINTED,FAINTED),
EAT_META(FAINTING,FAINTING),
EAT_META(FAKE_AMULET_OF_YENDOR,FAKE_AMULET_OF_YENDOR),
EAT_META(FAST,FAST),
EAT_META(FIRE_RES,FIRE_RES),
EAT_META(FIXED_ABIL,FIXED_ABIL),
EAT_META(FLESH,FLESH),
EAT_META(FLINT,FLINT),
EAT_META(FLYING,FLYING),
EAT_META(FOOD_CLASS,FOOD_CLASS),
EAT_META(FOOD_RATION,FOOD_RATION),
EAT_META(FORTUNE_COOKIE,FORTUNE_COOKIE),
EAT_META(FOUNTAIN,FOUNTAIN),
EAT_META(FREE_ACTION,FREE_ACTION),
EAT_META(FROMFORM,FROMFORM),
EAT_META(FROMOUTSIDE,FROMOUTSIDE),
EAT_META(FUMBLING,FUMBLING),
EAT_META(GD_EATGOLD,GD_EATGOLD),
EAT_META(GEM_CLASS,GEM_CLASS),
EAT_META(GETOBJ_DOWNPLAY,GETOBJ_DOWNPLAY),
EAT_META(GETOBJ_EXCLUDE,GETOBJ_EXCLUDE),
EAT_META(GETOBJ_EXCLUDE_NONINVENT,GETOBJ_EXCLUDE_NONINVENT),
EAT_META(GETOBJ_EXCLUDE_SELECTABLE,GETOBJ_EXCLUDE_SELECTABLE),
EAT_META(GETOBJ_NOFLAGS,GETOBJ_NOFLAGS),
EAT_META(GETOBJ_SUGGEST,GETOBJ_SUGGEST),
EAT_META(GLASS,GLASS),
EAT_META(GLIB,GLIB),
EAT_META(GLOB_OF_GREEN_SLIME,GLOB_OF_GREEN_SLIME),
EAT_META(GOLD_PIECE,GOLD_PIECE),
EAT_META(HALF_PHDAM,HALF_PHDAM),
EAT_META(HALF_SPDAM,HALF_SPDAM),
EAT_META(HALLUC,HALLUC),
EAT_META(HALLUC_RES,HALLUC_RES),
EAT_META(HEALTHY_TIN,HEALTHY_TIN),
EAT_META(HOMEMADE_TIN,HOMEMADE_TIN),
EAT_META(HUNGER,HUNGER),
EAT_META(HUNGRY,HUNGRY),
EAT_META(INFRAVISION,INFRAVISION),
EAT_META(INTRINSIC,INTRINSIC),
EAT_META(INVIS,INVIS),
EAT_META(IN_SIGHT,IN_SIGHT),
EAT_META(IRON,IRON),
EAT_META(IRONBARS,IRONBARS),
EAT_META(I_SPECIAL,I_SPECIAL),
EAT_META(KILLED_BY,KILLED_BY),
EAT_META(KILLED_BY_AN,KILLED_BY_AN),
EAT_META(KNIFE,KNIFE),
EAT_META(K_RATION,K_RATION),
EAT_META(LAST_PROP,LAST_PROP),
EAT_META(LEASH,LEASH),
EAT_META(LEATHER,LEATHER),
EAT_META(LEMBAS_WAFER,LEMBAS_WAFER),
EAT_META(LENSES,LENSES),
EAT_META(LEVITATION,LEVITATION),
EAT_META(LIFESAVED,LIFESAVED),
EAT_META(LIGHT_HEADED,LIGHT_HEADED),
EAT_META(LL_CONDUCT,LL_CONDUCT),
EAT_META(LONG_SWORD,LONG_SWORD),
EAT_META(LOW_PM,LOW_PM),
EAT_META(LUMP_OF_ROYAL_JELLY,LUMP_OF_ROYAL_JELLY),
EAT_META(M1_ACID,M1_ACID),
EAT_META(M1_AMORPHOUS,M1_AMORPHOUS),
EAT_META(M1_AMPHIBIOUS,M1_AMPHIBIOUS),
EAT_META(M1_BREATHLESS,M1_BREATHLESS),
EAT_META(M1_CARNIVORE,M1_CARNIVORE),
EAT_META(M1_CLING,M1_CLING),
EAT_META(M1_FLY,M1_FLY),
EAT_META(M1_HERBIVORE,M1_HERBIVORE),
EAT_META(M1_HUMANOID,M1_HUMANOID),
EAT_META(M1_METALLIVORE,M1_METALLIVORE),
EAT_META(M1_MINDLESS,M1_MINDLESS),
EAT_META(M1_NOEYES,M1_NOEYES),
EAT_META(M1_NOHANDS,M1_NOHANDS),
EAT_META(M1_NOHEAD,M1_NOHEAD),
EAT_META(M1_NOLIMBS,M1_NOLIMBS),
EAT_META(M1_POIS,M1_POIS),
EAT_META(M1_REGEN,M1_REGEN),
EAT_META(M1_SEE_INVIS,M1_SEE_INVIS),
EAT_META(M1_SWIM,M1_SWIM),
EAT_META(M1_TPORT,M1_TPORT),
EAT_META(M1_TPORT_CNTRL,M1_TPORT_CNTRL),
EAT_META(M1_UNSOLID,M1_UNSOLID),
EAT_META(M1_WALLWALK,M1_WALLWALK),
EAT_META(M2_DEMON,M2_DEMON),
EAT_META(M2_DWARF,M2_DWARF),
EAT_META(M2_ELF,M2_ELF),
EAT_META(M2_GIANT,M2_GIANT),
EAT_META(M2_GNOME,M2_GNOME),
EAT_META(M2_HUMAN,M2_HUMAN),
EAT_META(M2_MINION,M2_MINION),
EAT_META(M2_ORC,M2_ORC),
EAT_META(M2_PNAME,M2_PNAME),
EAT_META(M2_STRONG,M2_STRONG),
EAT_META(M2_UNDEAD,M2_UNDEAD),
EAT_META(M2_WERE,M2_WERE),
EAT_META(MAGICAL_BREATHING,MAGICAL_BREATHING),
EAT_META(MEATBALL,MEATBALL),
EAT_META(MEAT_RING,MEAT_RING),
EAT_META(MEAT_STICK,MEAT_STICK),
EAT_META(MITHRIL,MITHRIL),
EAT_META(MR_ACID,MR_ACID),
EAT_META(MR_COLD,MR_COLD),
EAT_META(MR_DISINT,MR_DISINT),
EAT_META(MR_ELEC,MR_ELEC),
EAT_META(MR_FIRE,MR_FIRE),
EAT_META(MR_POISON,MR_POISON),
EAT_META(MR_SLEEP,MR_SLEEP),
EAT_META(MR_STONE,MR_STONE),
EAT_META(MS_SILENT,MS_SILENT),
EAT_META(MZ_SMALL,MZ_SMALL),
EAT_META(M_AP_NOTHING,M_AP_NOTHING),
EAT_META(M_AP_OBJECT,M_AP_OBJECT),
EAT_META(M_AP_TYPMASK,M_AP_TYPMASK),
EAT_META(M_ATTK_AGR_DIED,M_ATTK_AGR_DIED),
EAT_META(M_ATTK_HIT,M_ATTK_HIT),
EAT_META(M_ATTK_MISS,M_ATTK_MISS),
EAT_META(NEUTRAL,NEUTRAL),
EAT_META(NON_PM,NON_PM),
EAT_META(NOSE,NOSE),
EAT_META(NOT_HUNGRY,NOT_HUNGRY),
EAT_META(NO_KILLER_PREFIX,NO_KILLER_PREFIX),
EAT_META(NO_PART,NO_PART),
EAT_META(NUMMONS,NUMMONS),
EAT_META(NUM_OBJECTS,NUM_OBJECTS),
EAT_META(OBJ_DELETED,OBJ_DELETED),
EAT_META(OBJ_FLOOR,OBJ_FLOOR),
EAT_META(OBJ_FREE,OBJ_FREE),
EAT_META(OBJ_INVENT,OBJ_INVENT),
EAT_META(ORANGE,ORANGE),
EAT_META(ORCISH_DAGGER,ORCISH_DAGGER),
EAT_META(PANCAKE,PANCAKE),
EAT_META(PAPER,PAPER),
EAT_META(PARANOID_EATING,PARANOID_EATING),
EAT_META(PEAR,PEAR),
EAT_META(PICK_AXE,PICK_AXE),
EAT_META(PM_ACID_BLOB,PM_ACID_BLOB),
EAT_META(PM_BAT,PM_BAT),
EAT_META(PM_BLACK_PUDDING,PM_BLACK_PUDDING),
EAT_META(PM_CAVE_DWELLER,PM_CAVE_DWELLER),
EAT_META(PM_CHAMELEON,PM_CHAMELEON),
EAT_META(PM_CHICKATRICE,PM_CHICKATRICE),
EAT_META(PM_COCKATRICE,PM_COCKATRICE),
EAT_META(PM_CYCLOPS,PM_CYCLOPS),
EAT_META(PM_DEATH,PM_DEATH),
EAT_META(PM_DISENCHANTER,PM_DISENCHANTER),
EAT_META(PM_DISPLACER_BEAST,PM_DISPLACER_BEAST),
EAT_META(PM_DJINNI,PM_DJINNI),
EAT_META(PM_DOG,PM_DOG),
EAT_META(PM_DOPPELGANGER,PM_DOPPELGANGER),
EAT_META(PM_DWARF,PM_DWARF),
EAT_META(PM_ELF,PM_ELF),
EAT_META(PM_FAMINE,PM_FAMINE),
EAT_META(PM_FIRE_ELEMENTAL,PM_FIRE_ELEMENTAL),
EAT_META(PM_FIRE_VORTEX,PM_FIRE_VORTEX),
EAT_META(PM_FLAMING_SPHERE,PM_FLAMING_SPHERE),
EAT_META(PM_FLESH_GOLEM,PM_FLESH_GOLEM),
EAT_META(PM_FLOATING_EYE,PM_FLOATING_EYE),
EAT_META(PM_GELATINOUS_CUBE,PM_GELATINOUS_CUBE),
EAT_META(PM_GENETIC_ENGINEER,PM_GENETIC_ENGINEER),
EAT_META(PM_GHOST,PM_GHOST),
EAT_META(PM_GHOUL,PM_GHOUL),
EAT_META(PM_GIANT_BAT,PM_GIANT_BAT),
EAT_META(PM_GIANT_MIMIC,PM_GIANT_MIMIC),
EAT_META(PM_GREEN_SLIME,PM_GREEN_SLIME),
EAT_META(PM_GREMLIN,PM_GREMLIN),
EAT_META(PM_HOUSECAT,PM_HOUSECAT),
EAT_META(PM_HUMAN,PM_HUMAN),
EAT_META(PM_HUMAN_WEREJACKAL,PM_HUMAN_WEREJACKAL),
EAT_META(PM_HUMAN_WERERAT,PM_HUMAN_WERERAT),
EAT_META(PM_HUMAN_WEREWOLF,PM_HUMAN_WEREWOLF),
EAT_META(PM_IRON_GOLEM,PM_IRON_GOLEM),
EAT_META(PM_KILLER_BEE,PM_KILLER_BEE),
EAT_META(PM_KITTEN,PM_KITTEN),
EAT_META(PM_KNIGHT,PM_KNIGHT),
EAT_META(PM_LARGE_CAT,PM_LARGE_CAT),
EAT_META(PM_LARGE_DOG,PM_LARGE_DOG),
EAT_META(PM_LARGE_MIMIC,PM_LARGE_MIMIC),
EAT_META(PM_LEATHER_GOLEM,PM_LEATHER_GOLEM),
EAT_META(PM_LICHEN,PM_LICHEN),
EAT_META(PM_LITTLE_DOG,PM_LITTLE_DOG),
EAT_META(PM_LIZARD,PM_LIZARD),
EAT_META(PM_MASTER_MIND_FLAYER,PM_MASTER_MIND_FLAYER),
EAT_META(PM_MEDUSA,PM_MEDUSA),
EAT_META(PM_MIND_FLAYER,PM_MIND_FLAYER),
EAT_META(PM_MONK,PM_MONK),
EAT_META(PM_NEWT,PM_NEWT),
EAT_META(PM_NURSE,PM_NURSE),
EAT_META(PM_ORC,PM_ORC),
EAT_META(PM_PESTILENCE,PM_PESTILENCE),
EAT_META(PM_PYROLISK,PM_PYROLISK),
EAT_META(PM_QUANTUM_MECHANIC,PM_QUANTUM_MECHANIC),
EAT_META(PM_QUEEN_BEE,PM_QUEEN_BEE),
EAT_META(PM_RAVEN,PM_RAVEN),
EAT_META(PM_RED_DRAGON,PM_RED_DRAGON),
EAT_META(PM_RUST_MONSTER,PM_RUST_MONSTER),
EAT_META(PM_SALAMANDER,PM_SALAMANDER),
EAT_META(PM_SANDESTIN,PM_SANDESTIN),
EAT_META(PM_SCORPION,PM_SCORPION),
EAT_META(PM_SMALL_MIMIC,PM_SMALL_MIMIC),
EAT_META(PM_STALKER,PM_STALKER),
EAT_META(PM_STONE_GOLEM,PM_STONE_GOLEM),
EAT_META(PM_TIGER,PM_TIGER),
EAT_META(PM_VALKYRIE,PM_VALKYRIE),
EAT_META(PM_VAMPIRE,PM_VAMPIRE),
EAT_META(PM_VAMPIRE_LEADER,PM_VAMPIRE_LEADER),
EAT_META(PM_VIOLET_FUNGUS,PM_VIOLET_FUNGUS),
EAT_META(PM_VLAD_THE_IMPALER,PM_VLAD_THE_IMPALER),
EAT_META(PM_WEREJACKAL,PM_WEREJACKAL),
EAT_META(PM_WERERAT,PM_WERERAT),
EAT_META(PM_WEREWOLF,PM_WEREWOLF),
EAT_META(PM_WIZARD,PM_WIZARD),
EAT_META(PM_WRAITH,PM_WRAITH),
EAT_META(PM_YELLOW_LIGHT,PM_YELLOW_LIGHT),
EAT_META(POISONING,POISONING),
EAT_META(POISON_RES,POISON_RES),
EAT_META(POLY_NOFLAGS,POLY_NOFLAGS),
EAT_META(POOL,POOL),
EAT_META(POTION_CLASS,POTION_CLASS),
EAT_META(POT_ACID,POT_ACID),
EAT_META(POT_BOOZE,POT_BOOZE),
EAT_META(POT_EXTRA_HEALING,POT_EXTRA_HEALING),
EAT_META(POT_FULL_HEALING,POT_FULL_HEALING),
EAT_META(POT_GAIN_LEVEL,POT_GAIN_LEVEL),
EAT_META(POT_HEALING,POT_HEALING),
EAT_META(POT_OIL,POT_OIL),
EAT_META(POT_POLYMORPH,POT_POLYMORPH),
EAT_META(POT_SICKNESS,POT_SICKNESS),
EAT_META(POT_WATER,POT_WATER),
EAT_META(PRONOUN_HALLU,PRONOUN_HALLU),
EAT_META(PROTECTION,PROTECTION),
EAT_META(PROT_FROM_SHAPE_CHANGERS,PROT_FROM_SHAPE_CHANGERS),
EAT_META(P_BOW,P_BOW),
EAT_META(P_CROSSBOW,P_CROSSBOW),
EAT_META(P_NONE,P_NONE),
EAT_META(P_SHURIKEN,P_SHURIKEN),
EAT_META(QBUFSZ,QBUFSZ),
EAT_META(REGENERATION,REGENERATION),
EAT_META(RING_CLASS,RING_CLASS),
EAT_META(RIN_ADORNMENT,RIN_ADORNMENT),
EAT_META(RIN_FREE_ACTION,RIN_FREE_ACTION),
EAT_META(RIN_GAIN_CONSTITUTION,RIN_GAIN_CONSTITUTION),
EAT_META(RIN_GAIN_STRENGTH,RIN_GAIN_STRENGTH),
EAT_META(RIN_INCREASE_ACCURACY,RIN_INCREASE_ACCURACY),
EAT_META(RIN_INCREASE_DAMAGE,RIN_INCREASE_DAMAGE),
EAT_META(RIN_INVISIBILITY,RIN_INVISIBILITY),
EAT_META(RIN_LEVITATION,RIN_LEVITATION),
EAT_META(RIN_PROTECTION,RIN_PROTECTION),
EAT_META(RIN_PROTECTION_FROM_SHAPE_CHAN,RIN_PROTECTION_FROM_SHAPE_CHAN),
EAT_META(RIN_SEE_INVISIBLE,RIN_SEE_INVISIBLE),
EAT_META(RIN_SLOW_DIGESTION,RIN_SLOW_DIGESTION),
EAT_META(RIN_SUSTAIN_ABILITY,RIN_SUSTAIN_ABILITY),
EAT_META(ROOM,ROOM),
EAT_META(ROTTEN_TIN,ROTTEN_TIN),
EAT_META(ROWNO,ROWNO),
EAT_META(SATIATED,SATIATED),
EAT_META(SCROLL_CLASS,SCROLL_CLASS),
EAT_META(SCR_MAIL,SCR_MAIL),
EAT_META(SCR_SCARE_MONSTER,SCR_SCARE_MONSTER),
EAT_META(SEE_INVIS,SEE_INVIS),
EAT_META(SELL_DONTSELL,SELL_DONTSELL),
EAT_META(SELL_NORMAL,SELL_NORMAL),
EAT_META(SHOCK_RES,SHOCK_RES),
EAT_META(SICK,SICK),
EAT_META(SICK_ALL,SICK_ALL),
EAT_META(SICK_RES,SICK_RES),
EAT_META(SICK_VOMITABLE,SICK_VOMITABLE),
EAT_META(SILVER_DAGGER,SILVER_DAGGER),
EAT_META(SINK,SINK),
EAT_META(SLEEPY,SLEEPY),
EAT_META(SLEEP_RES,SLEEP_RES),
EAT_META(SLIMED,SLIMED),
EAT_META(SLIME_MOLD,SLIME_MOLD),
EAT_META(SLOW_DIGESTION,SLOW_DIGESTION),
EAT_META(SLT_ENCUMBER,SLT_ENCUMBER),
EAT_META(SPINACH_TIN,SPINACH_TIN),
EAT_META(SPRIG_OF_WOLFSBANE,SPRIG_OF_WOLFSBANE),
EAT_META(STARVED,STARVED),
EAT_META(STARVING,STARVING),
EAT_META(STILETTO,STILETTO),
EAT_META(STOMACH,STOMACH),
EAT_META(STONED,STONED),
EAT_META(STONE_RES,STONE_RES),
EAT_META(STONING,STONING),
EAT_META(STRANGLED,STRANGLED),
EAT_META(STUNNED,STUNNED),
EAT_META(SWIMMING,SWIMMING),
EAT_META(S_BLOB,S_BLOB),
EAT_META(S_ELEMENTAL,S_ELEMENTAL),
EAT_META(S_EYE,S_EYE),
EAT_META(S_FUNGUS,S_FUNGUS),
EAT_META(S_GHOST,S_GHOST),
EAT_META(S_GOLEM,S_GOLEM),
EAT_META(S_JELLY,S_JELLY),
EAT_META(S_LIGHT,S_LIGHT),
EAT_META(S_MIMIC,S_MIMIC),
EAT_META(S_PUDDING,S_PUDDING),
EAT_META(S_VORTEX,S_VORTEX),
EAT_META(TELEPAT,TELEPAT),
EAT_META(TELEPORT,TELEPORT),
EAT_META(TELEPORT_CONTROL,TELEPORT_CONTROL),
EAT_META(TIMEOUT,TIMEOUT),
EAT_META(TIN,TIN),
EAT_META(TIN_OPENER,TIN_OPENER),
EAT_META(TOOL_CLASS,TOOL_CLASS),
EAT_META(TOWEL,TOWEL),
EAT_META(TRIDENT,TRIDENT),
EAT_META(TRIPE_RATION,TRIPE_RATION),
EAT_META(TT_BEARTRAP,TT_BEARTRAP),
EAT_META(UNCHANGING,UNCHANGING),
EAT_META(VOMITING,VOMITING),
EAT_META(WARN_OF_MON,WARN_OF_MON),
EAT_META(WAX,WAX),
EAT_META(WEAK,WEAK),
EAT_META(WEAPON_CLASS,WEAPON_CLASS),
EAT_META(WOOD,WOOD),
EAT_META(WOUNDED_LEGS,WOUNDED_LEGS),
EAT_META(WWALKING,WWALKING),
EAT_META(W_AMUL,W_AMUL),
EAT_META(W_ARMOR,W_ARMOR),
EAT_META(W_ART,W_ART),
EAT_META(W_ARTI,W_ARTI),
EAT_META(W_NONDIGGABLE,W_NONDIGGABLE),
EAT_META(W_RING,W_RING),
EAT_META(W_RINGL,W_RINGL),
EAT_META(W_RINGR,W_RINGR),
EAT_META(W_SADDLE,W_SADDLE),
EAT_META(W_TOOL,W_TOOL),
EAT_META(W_WEP,W_WEP),
EAT_META(invlet_basic,invlet_basic),
EAT_META(COST_UNCURS,COST_UNCURS),
EAT_META(COST_UNBLSS,COST_UNBLSS),
EAT_META(COST_NUTRLZ,COST_NUTRLZ),
};
_Static_assert(sizeof(void*)==8&&sizeof(long)==8&&sizeof(int)==4&&sizeof(coordxy)==2&&sizeof(boolean)==1,"EAT ABI widths");
_Static_assert(sizeof(((struct monst*)0)->data)==8,"mon_data pointer width");
_Static_assert(sizeof(((struct monst*)0)->m_ap_type)==1,"mon_m_ap_type width");
_Static_assert(((__typeof__(((struct monst*)0)->m_ap_type))-1 > 0),"mon_m_ap_type signedness");
_Static_assert(sizeof(((struct monst*)0)->mappearance)==4,"mon_mappearance width");
_Static_assert(((__typeof__(((struct monst*)0)->mappearance))-1 > 0),"mon_mappearance signedness");
_Static_assert(sizeof(((struct monst*)0)->mextra)==8,"mon_mextra pointer width");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4,"mon_mhp width");
_Static_assert(((__typeof__(((struct monst*)0)->mhp))-1 < 0),"mon_mhp signedness");
_Static_assert(sizeof(((struct monst*)0)->mtame)==1,"mon_mtame width");
_Static_assert(((__typeof__(((struct monst*)0)->mtame))-1 < 0),"mon_mtame signedness");
_Static_assert(sizeof(((struct monst*)0)->mx)==2,"mon_mx width");
_Static_assert(((__typeof__(((struct monst*)0)->mx))-1 < 0),"mon_mx signedness");
_Static_assert(sizeof(((struct monst*)0)->my)==2,"mon_my width");
_Static_assert(((__typeof__(((struct monst*)0)->my))-1 < 0),"mon_my signedness");
_Static_assert(sizeof(((struct you*)0)->mh)==4,"you_mh width");
_Static_assert(((__typeof__(((struct you*)0)->mh))-1 < 0),"you_mh signedness");
_Static_assert(sizeof(((struct you*)0)->mhmax)==4,"you_mhmax width");
_Static_assert(((__typeof__(((struct you*)0)->mhmax))-1 < 0),"you_mhmax signedness");
_Static_assert(sizeof(((struct you*)0)->ublessed)==4,"you_ublessed width");
_Static_assert(((__typeof__(((struct you*)0)->ublessed))-1 < 0),"you_ublessed signedness");
_Static_assert(sizeof(((struct you*)0)->ucreamed)==4,"you_ucreamed width");
_Static_assert(((__typeof__(((struct you*)0)->ucreamed))-1 > 0),"you_ucreamed signedness");
_Static_assert(sizeof(((struct you*)0)->udaminc)==1,"you_udaminc width");
_Static_assert(((__typeof__(((struct you*)0)->udaminc))-1 < 0),"you_udaminc signedness");
_Static_assert(sizeof(((struct you*)0)->uen)==4,"you_uen width");
_Static_assert(((__typeof__(((struct you*)0)->uen))-1 < 0),"you_uen signedness");
_Static_assert(sizeof(((struct you*)0)->uenmax)==4,"you_uenmax width");
_Static_assert(((__typeof__(((struct you*)0)->uenmax))-1 < 0),"you_uenmax signedness");
_Static_assert(sizeof(((struct you*)0)->uenpeak)==4,"you_uenpeak width");
_Static_assert(((__typeof__(((struct you*)0)->uenpeak))-1 < 0),"you_uenpeak signedness");
_Static_assert(sizeof(((struct you*)0)->uhitinc)==1,"you_uhitinc width");
_Static_assert(((__typeof__(((struct you*)0)->uhitinc))-1 < 0),"you_uhitinc signedness");
_Static_assert(sizeof(((struct you*)0)->uhp)==4,"you_uhp width");
_Static_assert(((__typeof__(((struct you*)0)->uhp))-1 < 0),"you_uhp signedness");
_Static_assert(sizeof(((struct you*)0)->uhpmax)==4,"you_uhpmax width");
_Static_assert(((__typeof__(((struct you*)0)->uhpmax))-1 < 0),"you_uhpmax signedness");
_Static_assert(sizeof(((struct you*)0)->uhs)==4,"you_uhs width");
_Static_assert(((__typeof__(((struct you*)0)->uhs))-1 > 0),"you_uhs signedness");
_Static_assert(sizeof(((struct you*)0)->uhunger)==4,"you_uhunger width");
_Static_assert(((__typeof__(((struct you*)0)->uhunger))-1 < 0),"you_uhunger signedness");
_Static_assert(sizeof(((struct you*)0)->ulycn)==4,"you_ulycn width");
_Static_assert(((__typeof__(((struct you*)0)->ulycn))-1 < 0),"you_ulycn signedness");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4,"you_umonnum width");
_Static_assert(((__typeof__(((struct you*)0)->umonnum))-1 < 0),"you_umonnum signedness");
_Static_assert(sizeof(((struct you*)0)->umonster)==4,"you_umonster width");
_Static_assert(((__typeof__(((struct you*)0)->umonster))-1 < 0),"you_umonster signedness");
_Static_assert(sizeof((((struct you*)0)->uprops))/sizeof((((struct you*)0)->uprops)[0])==69,"you_uprops extent0");
_Static_assert(sizeof(((struct you*)0)->usteed)==8,"you_usteed pointer width");
_Static_assert(sizeof(((struct you*)0)->ustuck)==8,"you_ustuck pointer width");
_Static_assert(sizeof(((struct you*)0)->utrap)==4,"you_utrap width");
_Static_assert(((__typeof__(((struct you*)0)->utrap))-1 > 0),"you_utrap signedness");
_Static_assert(sizeof(((struct you*)0)->utraptype)==4,"you_utraptype width");
_Static_assert(((__typeof__(((struct you*)0)->utraptype))-1 > 0),"you_utraptype signedness");
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
_Static_assert(sizeof(((struct obj*)0)->oeaten)==4,"obj_oeaten width");
_Static_assert(((__typeof__(((struct obj*)0)->oeaten))-1 > 0),"obj_oeaten signedness");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2,"obj_otyp width");
_Static_assert(((__typeof__(((struct obj*)0)->otyp))-1 < 0),"obj_otyp signedness");
_Static_assert(sizeof(((struct obj*)0)->owornmask)==8,"obj_owornmask width");
_Static_assert(((__typeof__(((struct obj*)0)->owornmask))-1 < 0),"obj_owornmask signedness");
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
_Static_assert(sizeof(((struct obj*)0)->timed)==2,"obj_timed width");
_Static_assert(((__typeof__(((struct obj*)0)->timed))-1 < 0),"obj_timed signedness");
_Static_assert(sizeof(((struct obj*)0)->where)==1,"obj_where width");
_Static_assert(((__typeof__(((struct obj*)0)->where))-1 < 0),"obj_where signedness");
_Static_assert(sizeof(((struct c_color_names*)0)->c_green)==8,"colors_c_green pointer width");
_Static_assert(sizeof(((struct instance_flags*)0)->debug_hunger)==1,"iflags_debug_hunger width");
_Static_assert(((__typeof__(((struct instance_flags*)0)->debug_hunger))-1 < 0),"iflags_debug_hunger signedness");
_Static_assert(sizeof(((struct instance_flags*)0)->last_msg)==4,"iflags_last_msg width");
_Static_assert(((__typeof__(((struct instance_flags*)0)->last_msg))-1 < 0),"iflags_last_msg signedness");
_Static_assert(sizeof(((struct instance_flags*)0)->menu_requested)==1,"iflags_menu_requested width");
_Static_assert(((__typeof__(((struct instance_flags*)0)->menu_requested))-1 < 0),"iflags_menu_requested signedness");
_Static_assert(sizeof(((struct instance_flags*)0)->override_ID)==4,"iflags_override_ID width");
_Static_assert(((__typeof__(((struct instance_flags*)0)->override_ID))-1 < 0),"iflags_override_ID signedness");
_Static_assert(sizeof(((struct c_common_strings*)0)->c_You_can_move_again)==8,"strings_c_You_can_move_again pointer width");
_Static_assert(sizeof(((struct c_common_strings*)0)->c_something)==8,"strings_c_something pointer width");
_Static_assert(sizeof(((struct c_common_strings*)0)->c_vision_clears)==8,"strings_c_vision_clears pointer width");
_Static_assert(sizeof(((struct u_conduct*)0)->food)==8,"conduct_food width");
_Static_assert(((__typeof__(((struct u_conduct*)0)->food))-1 < 0),"conduct_food signedness");
_Static_assert(sizeof(((struct u_conduct*)0)->literate)==8,"conduct_literate width");
_Static_assert(((__typeof__(((struct u_conduct*)0)->literate))-1 < 0),"conduct_literate signedness");
_Static_assert(sizeof(((struct u_conduct*)0)->polyselfs)==8,"conduct_polyselfs width");
_Static_assert(((__typeof__(((struct u_conduct*)0)->polyselfs))-1 < 0),"conduct_polyselfs signedness");
_Static_assert(sizeof(((struct u_conduct*)0)->unvegan)==8,"conduct_unvegan width");
_Static_assert(((__typeof__(((struct u_conduct*)0)->unvegan))-1 < 0),"conduct_unvegan signedness");
_Static_assert(sizeof(((struct u_conduct*)0)->unvegetarian)==8,"conduct_unvegetarian width");
_Static_assert(((__typeof__(((struct u_conduct*)0)->unvegetarian))-1 < 0),"conduct_unvegetarian signedness");
_Static_assert(sizeof(((struct flag*)0)->acoustics)==1,"flags_acoustics width");
_Static_assert(((__typeof__(((struct flag*)0)->acoustics))-1 < 0),"flags_acoustics signedness");
_Static_assert(sizeof(((struct flag*)0)->female)==1,"flags_female width");
_Static_assert(((__typeof__(((struct flag*)0)->female))-1 < 0),"flags_female signedness");
_Static_assert(sizeof(((struct flag*)0)->paranoia_bits)==4,"flags_paranoia_bits width");
_Static_assert(((__typeof__(((struct flag*)0)->paranoia_bits))-1 > 0),"flags_paranoia_bits signedness");
_Static_assert(sizeof(((struct flag*)0)->verbose)==1,"flags_verbose width");
_Static_assert(((__typeof__(((struct flag*)0)->verbose))-1 < 0),"flags_verbose signedness");
_Static_assert(sizeof(((struct instance_globals_v*)0)->vision_full_recalc)==1,"gv_vision_full_recalc width");
_Static_assert(((__typeof__(((struct instance_globals_v*)0)->vision_full_recalc))-1 < 0),"gv_vision_full_recalc signedness");
_Static_assert(sizeof(((struct instance_globals_v*)0)->viz_array)==8,"gv_viz_array pointer width");
_Static_assert(sizeof(((struct instance_globals_saved_m*)0)->moves)==8,"svm_moves width");
_Static_assert(((__typeof__(((struct instance_globals_saved_m*)0)->moves))-1 < 0),"svm_moves signedness");
_Static_assert(sizeof(((struct Role*)0)->mnum)==2,"role_mnum width");
_Static_assert(((__typeof__(((struct Role*)0)->mnum))-1 < 0),"role_mnum signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_delay)==1,"cls_oc_delay width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_delay))-1 < 0),"cls_oc_delay signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_nutrition)==2,"cls_oc_nutrition width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_nutrition))-1 > 0),"cls_oc_nutrition signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_oprop)==1,"cls_oc_oprop width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_oprop))-1 > 0),"cls_oc_oprop signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_skill)==1,"cls_oc_skill width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_skill))-1 < 0),"cls_oc_skill signedness");
_Static_assert(sizeof(((struct permonst*)0)->cnutrit)==2,"pm_cnutrit width");
_Static_assert(((__typeof__(((struct permonst*)0)->cnutrit))-1 > 0),"pm_cnutrit signedness");
_Static_assert(sizeof(((struct permonst*)0)->cwt)==4,"pm_cwt width");
_Static_assert(((__typeof__(((struct permonst*)0)->cwt))-1 > 0),"pm_cwt signedness");
_Static_assert(sizeof(((struct permonst*)0)->geno)==2,"pm_geno width");
_Static_assert(((__typeof__(((struct permonst*)0)->geno))-1 > 0),"pm_geno signedness");
_Static_assert(sizeof((((struct permonst*)0)->mattk))/sizeof((((struct permonst*)0)->mattk)[0])==6,"pm_mattk extent0");
_Static_assert(sizeof(((struct permonst*)0)->mconveys)==1,"pm_mconveys width");
_Static_assert(((__typeof__(((struct permonst*)0)->mconveys))-1 > 0),"pm_mconveys signedness");
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
_Static_assert(sizeof(((struct permonst*)0)->pmidx)==4,"pm_pmidx width");
_Static_assert(((__typeof__(((struct permonst*)0)->pmidx))-1 < 0),"pm_pmidx signedness");
_Static_assert(sizeof((((struct permonst*)0)->pmnames))/sizeof((((struct permonst*)0)->pmnames)[0])==3,"pm_pmnames extent0");
_Static_assert(sizeof(((struct instance_globals_m*)0)->multi)==8,"gm_multi width");
_Static_assert(((__typeof__(((struct instance_globals_m*)0)->multi))-1 < 0),"gm_multi signedness");
_Static_assert(sizeof(((struct instance_globals_m*)0)->multi_reason)==8,"gm_multi_reason pointer width");
_Static_assert(sizeof((((struct attribs*)0)->a))/sizeof((((struct attribs*)0)->a)[0])==6,"attribs_a extent0");
_Static_assert(sizeof((((struct attribs*)0)->a)[0])==1&&((__typeof__((((struct attribs*)0)->a)[0]))-1 < 0),"attribs_a element ABI");
_Static_assert(sizeof(((struct d_level*)0)->dlevel)==2,"level_dlevel width");
_Static_assert(((__typeof__(((struct d_level*)0)->dlevel))-1 < 0),"level_dlevel signedness");
_Static_assert(sizeof(((struct d_level*)0)->dnum)==2,"level_dnum width");
_Static_assert(((__typeof__(((struct d_level*)0)->dnum))-1 < 0),"level_dnum signedness");
_Static_assert(sizeof(((struct rm*)0)->typ)==1,"rm_typ width");
_Static_assert(((__typeof__(((struct rm*)0)->typ))-1 < 0),"rm_typ signedness");
_Static_assert(sizeof(((struct objdescr*)0)->oc_descr)==8,"descr_oc_descr pointer width");
_Static_assert(sizeof(((struct u_roleplay*)0)->deaf)==1,"roleplay_deaf width");
_Static_assert(((__typeof__(((struct u_roleplay*)0)->deaf))-1 < 0),"roleplay_deaf signedness");
_Static_assert(sizeof(((struct instance_globals_n*)0)->nomovemsg)==8,"gn_nomovemsg pointer width");
_Static_assert(sizeof(((struct Gender*)0)->he)==8,"gender_he pointer width");
_Static_assert(sizeof(((struct Gender*)0)->him)==8,"gender_him pointer width");
_Static_assert(sizeof(((struct align*)0)->type)==1,"align_type width");
_Static_assert(((__typeof__(((struct align*)0)->type))-1 < 0),"align_type signedness");
_Static_assert(sizeof(((struct context_info*)0)->current_fruit)==4,"context_current_fruit width");
_Static_assert(((__typeof__(((struct context_info*)0)->current_fruit))-1 < 0),"context_current_fruit signedness");
_Static_assert(sizeof(((struct display_hints*)0)->botl)==1,"disp_botl width");
_Static_assert(((__typeof__(((struct display_hints*)0)->botl))-1 < 0),"disp_botl signedness");
_Static_assert(sizeof((((struct Race*)0)->attrmax))/sizeof((((struct Race*)0)->attrmax)[0])==6,"race_attrmax extent0");
_Static_assert(sizeof((((struct Race*)0)->attrmax)[0])==2&&((__typeof__((((struct Race*)0)->attrmax)[0]))-1 < 0),"race_attrmax element ABI");
_Static_assert(sizeof((((struct Race*)0)->attrmin))/sizeof((((struct Race*)0)->attrmin)[0])==6,"race_attrmin extent0");
_Static_assert(sizeof((((struct Race*)0)->attrmin)[0])==2&&((__typeof__((((struct Race*)0)->attrmin)[0]))-1 < 0),"race_attrmin element ABI");
_Static_assert(sizeof(((struct Race*)0)->mnum)==2,"race_mnum width");
_Static_assert(((__typeof__(((struct Race*)0)->mnum))-1 < 0),"race_mnum signedness");
_Static_assert(sizeof(((struct Race*)0)->noun)==8,"race_noun pointer width");
_Static_assert(sizeof(((struct Race*)0)->selfmask)==2,"race_selfmask width");
_Static_assert(((__typeof__(((struct Race*)0)->selfmask))-1 < 0),"race_selfmask signedness");
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
_Static_assert(sizeof((((struct kinfo*)0)->name))/sizeof((((struct kinfo*)0)->name)[0])==256,"killer_name extent0");
_Static_assert(sizeof((((struct kinfo*)0)->name)[0])==1&&((__typeof__((((struct kinfo*)0)->name)[0]))-1 < 0),"killer_name element ABI");
_Static_assert(sizeof(((struct victual_info*)0)->nmod)==4,"victual_nmod width");
_Static_assert(((__typeof__(((struct victual_info*)0)->nmod))-1 < 0),"victual_nmod signedness");
_Static_assert(sizeof(((struct victual_info*)0)->o_id)==4,"victual_o_id width");
_Static_assert(((__typeof__(((struct victual_info*)0)->o_id))-1 > 0),"victual_o_id signedness");
_Static_assert(sizeof(((struct victual_info*)0)->piece)==8,"victual_piece pointer width");
_Static_assert(sizeof(((struct victual_info*)0)->reqtime)==4,"victual_reqtime width");
_Static_assert(((__typeof__(((struct victual_info*)0)->reqtime))-1 < 0),"victual_reqtime signedness");
_Static_assert(sizeof(((struct victual_info*)0)->usedtime)==4,"victual_usedtime width");
_Static_assert(((__typeof__(((struct victual_info*)0)->usedtime))-1 < 0),"victual_usedtime signedness");
_Static_assert(sizeof(((struct tin_info*)0)->o_id)==4,"tin_o_id width");
_Static_assert(((__typeof__(((struct tin_info*)0)->o_id))-1 > 0),"tin_o_id signedness");
_Static_assert(sizeof(((struct tin_info*)0)->reqtime)==4,"tin_reqtime width");
_Static_assert(((__typeof__(((struct tin_info*)0)->reqtime))-1 < 0),"tin_reqtime signedness");
_Static_assert(sizeof(((struct tin_info*)0)->tin)==8,"tin_tin pointer width");
_Static_assert(sizeof(((struct tin_info*)0)->usedtime)==4,"tin_usedtime width");
_Static_assert(((__typeof__(((struct tin_info*)0)->usedtime))-1 < 0),"tin_usedtime signedness");
_Static_assert(sizeof(((struct instance_globals_e*)0)->eatmbuf)==8,"ge_eatmbuf pointer width");
_Static_assert(sizeof(((struct instance_globals_a*)0)->afternmv)==8,"ga_afternmv pointer width");
_Static_assert(sizeof(((struct instance_globals_o*)0)->occupation)==8,"go_occupation pointer width");
_Static_assert(sizeof(((struct instance_globals_c*)0)->corpsenm_digested)==2,"gc_corpsenm_digested width");
_Static_assert(((__typeof__(((struct instance_globals_c*)0)->corpsenm_digested))-1 < 0),"gc_corpsenm_digested signedness");
_Static_assert(sizeof(((struct instance_globals_f*)0)->force_save_hs)==1,"gf_force_save_hs width");
_Static_assert(((__typeof__(((struct instance_globals_f*)0)->force_save_hs))-1 < 0),"gf_force_save_hs signedness");
_Static_assert(sizeof(((struct edog*)0)->hungrytime)==8,"edog_hungrytime width");
_Static_assert(((__typeof__(((struct edog*)0)->hungrytime))-1 < 0),"edog_hungrytime signedness");
_Static_assert(sizeof(((struct mextra*)0)->edog)==8,"mextra_edog pointer width");
_Static_assert(sizeof(((struct dig_info*)0)->chew)==1,"dig_chew width");
_Static_assert(((__typeof__(((struct dig_info*)0)->chew))-1 < 0),"dig_chew signedness");
_Static_assert(sizeof(((struct RoleName*)0)->m)==8,"rolename_m pointer width");
_Static_assert(sizeof((((__typeof__(svl.level)*)0)->locations))/sizeof((((__typeof__(svl.level)*)0)->locations)[0])==80,"dlevel_locations extent0");
_Static_assert(sizeof((((__typeof__(svl.level)*)0)->locations)[0])/sizeof((((__typeof__(svl.level)*)0)->locations)[0][0])==21,"dlevel_locations extent1");
_Static_assert(sizeof(((__typeof__(svl.level)*)0)->monlist)==8,"dlevel_monlist pointer width");
_Static_assert(sizeof((((__typeof__(svl.level)*)0)->monsters))/sizeof((((__typeof__(svl.level)*)0)->monsters)[0])==80,"dlevel_monsters extent0");
_Static_assert(sizeof((((__typeof__(svl.level)*)0)->monsters)[0])/sizeof((((__typeof__(svl.level)*)0)->monsters)[0][0])==21,"dlevel_monsters extent1");
_Static_assert(sizeof((((__typeof__(svl.level)*)0)->objects))/sizeof((((__typeof__(svl.level)*)0)->objects)[0])==80,"dlevel_objects extent0");
_Static_assert(sizeof((((__typeof__(svl.level)*)0)->objects)[0])/sizeof((((__typeof__(svl.level)*)0)->objects)[0][0])==21,"dlevel_objects extent1");
_Static_assert(__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__,"EAT little endian ABI");
#if !defined(DEBUG)||defined(SND_LIB_INTEGRATED)||!defined(MACOS)||!defined(UNIX)||!defined(MAIL_STRUCTURES)
#error Review EAT configured profile
#endif
size_t probe_context_size(void){return sizeof(struct obj);}
int probe_layout_count(void){return sizeof teleport_eat_layout/sizeof teleport_eat_layout[0];}
const char*probe_layout_name(int i){return teleport_eat_layout[i].name;}
size_t probe_layout_value(int i){return teleport_eat_layout[i].value;}
#endif
