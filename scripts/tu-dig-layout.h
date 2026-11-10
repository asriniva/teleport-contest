/* DIG compiler layout and independent native ABI guards only. */
#ifndef TELEPORT_DIG_LAYOUT_H
#define TELEPORT_DIG_LAYOUT_H
#include "hack.h"
#include <stddef.h>
#if !defined(DEBUG) || defined(SND_LIB_INTEGRATED) || defined(SFCTOOL)
#error "Review DIG configured DEBUG/sound/game profile"
#endif
_Static_assert(__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__,"DIG native little-endian views");
#define DIG_META(k,v) {#k,(size_t)(v)}
static const struct {const char*name;size_t value;} teleport_dig_layout[]={
DIG_META(digbeamGlyph,cmap_to_glyph(S_digbeam)),
DIG_META(pointerSize,sizeof(void*)),
DIG_META(intSize,sizeof(int)),
DIG_META(longSize,sizeof(long)),
DIG_META(coordxySize,sizeof(coordxy)),
DIG_META(booleanSize,sizeof(boolean)),
DIG_META(locations,offsetof(__typeof__(svl),level.locations)),
DIG_META(floorObjects,offsetof(__typeof__(svl),level.objects)),
DIG_META(floorMonsters,offsetof(__typeof__(svl),level.monsters)),
DIG_META(buriedobjlist,offsetof(__typeof__(svl),level.buriedobjlist)),
DIG_META(levelFlags,offsetof(__typeof__(svl),level.flags)),
DIG_META(airLevel,offsetof(__typeof__(svd),dungeon_topology.d_air_level)),
DIG_META(waterLevel,offsetof(__typeof__(svd),dungeon_topology.d_water_level)),
DIG_META(earthLevel,offsetof(__typeof__(svd),dungeon_topology.d_earth_level)),
DIG_META(stronghold,offsetof(__typeof__(svd),dungeon_topology.d_stronghold_level)),
DIG_META(valleyLevel,offsetof(__typeof__(svd),dungeon_topology.d_valley_level)),
DIG_META(youSize,sizeof(struct you)),
DIG_META(you_ux,offsetof(struct you,ux)),
DIG_META(you_ux_size,sizeof(((struct you*)0)->ux)),
DIG_META(you_uy,offsetof(struct you,uy)),
DIG_META(you_uy_size,sizeof(((struct you*)0)->uy)),
DIG_META(you_dx,offsetof(struct you,dx)),
DIG_META(you_dx_size,sizeof(((struct you*)0)->dx)),
DIG_META(you_dy,offsetof(struct you,dy)),
DIG_META(you_dy_size,sizeof(((struct you*)0)->dy)),
DIG_META(you_dz,offsetof(struct you,dz)),
DIG_META(you_dz_size,sizeof(((struct you*)0)->dz)),
DIG_META(you_uz,offsetof(struct you,uz)),
DIG_META(you_uz_size,sizeof(((struct you*)0)->uz)),
DIG_META(you_utrap,offsetof(struct you,utrap)),
DIG_META(you_utrap_size,sizeof(((struct you*)0)->utrap)),
DIG_META(you_utraptype,offsetof(struct you,utraptype)),
DIG_META(you_utraptype_size,sizeof(((struct you*)0)->utraptype)),
DIG_META(you_udaminc,offsetof(struct you,udaminc)),
DIG_META(you_udaminc_size,sizeof(((struct you*)0)->udaminc)),
DIG_META(you_usteed,offsetof(struct you,usteed)),
DIG_META(you_usteed_size,sizeof(((struct you*)0)->usteed)),
DIG_META(you_ustuck,offsetof(struct you,ustuck)),
DIG_META(you_ustuck_size,sizeof(((struct you*)0)->ustuck)),
DIG_META(you_ualign,offsetof(struct you,ualign)),
DIG_META(you_ualign_size,sizeof(((struct you*)0)->ualign)),
DIG_META(you_ushops,offsetof(struct you,ushops)),
DIG_META(you_ushops_size,sizeof(((struct you*)0)->ushops)),
DIG_META(you_uprops,offsetof(struct you,uprops)),
DIG_META(you_uprops_size,sizeof(((struct you*)0)->uprops)),
DIG_META(levelSize,sizeof(d_level)),
DIG_META(level_dnum,offsetof(d_level,dnum)),
DIG_META(level_dnum_size,sizeof(((d_level*)0)->dnum)),
DIG_META(level_dlevel,offsetof(d_level,dlevel)),
DIG_META(level_dlevel_size,sizeof(((d_level*)0)->dlevel)),
DIG_META(coordSize,sizeof(coord)),
DIG_META(coord_x,offsetof(coord,x)),
DIG_META(coord_x_size,sizeof(((coord*)0)->x)),
DIG_META(coord_y,offsetof(coord,y)),
DIG_META(coord_y_size,sizeof(((coord*)0)->y)),
DIG_META(alignSize,sizeof(align)),
DIG_META(align_type,offsetof(align,type)),
DIG_META(align_type_size,sizeof(((align*)0)->type)),
DIG_META(align_record,offsetof(align,record)),
DIG_META(align_record_size,sizeof(((align*)0)->record)),
DIG_META(propSize,sizeof(struct prop)),
DIG_META(prop_intrinsic,offsetof(struct prop,intrinsic)),
DIG_META(prop_intrinsic_size,sizeof(((struct prop*)0)->intrinsic)),
DIG_META(prop_extrinsic,offsetof(struct prop,extrinsic)),
DIG_META(prop_extrinsic_size,sizeof(((struct prop*)0)->extrinsic)),
DIG_META(prop_blocked,offsetof(struct prop,blocked)),
DIG_META(prop_blocked_size,sizeof(((struct prop*)0)->blocked)),
DIG_META(diggingSize,sizeof(struct dig_info)),
DIG_META(digging_effort,offsetof(struct dig_info,effort)),
DIG_META(digging_effort_size,sizeof(((struct dig_info*)0)->effort)),
DIG_META(digging_level,offsetof(struct dig_info,level)),
DIG_META(digging_level_size,sizeof(((struct dig_info*)0)->level)),
DIG_META(digging_pos,offsetof(struct dig_info,pos)),
DIG_META(digging_pos_size,sizeof(((struct dig_info*)0)->pos)),
DIG_META(digging_lastdigtime,offsetof(struct dig_info,lastdigtime)),
DIG_META(digging_lastdigtime_size,sizeof(((struct dig_info*)0)->lastdigtime)),
DIG_META(digging_down,offsetof(struct dig_info,down)),
DIG_META(digging_down_size,sizeof(((struct dig_info*)0)->down)),
DIG_META(digging_chew,offsetof(struct dig_info,chew)),
DIG_META(digging_chew_size,sizeof(((struct dig_info*)0)->chew)),
DIG_META(digging_warned,offsetof(struct dig_info,warned)),
DIG_META(digging_warned_size,sizeof(((struct dig_info*)0)->warned)),
DIG_META(digging_quiet,offsetof(struct dig_info,quiet)),
DIG_META(digging_quiet_size,sizeof(((struct dig_info*)0)->quiet)),
DIG_META(monSize,sizeof(struct monst)),
DIG_META(mon_data,offsetof(struct monst,data)),
DIG_META(mon_data_size,sizeof(((struct monst*)0)->data)),
DIG_META(mon_mx,offsetof(struct monst,mx)),
DIG_META(mon_mx_size,sizeof(((struct monst*)0)->mx)),
DIG_META(mon_my,offsetof(struct monst,my)),
DIG_META(mon_my_size,sizeof(((struct monst*)0)->my)),
DIG_META(mon_mhp,offsetof(struct monst,mhp)),
DIG_META(mon_mhp_size,sizeof(((struct monst*)0)->mhp)),
DIG_META(mon_mw,offsetof(struct monst,mw)),
DIG_META(mon_mw_size,sizeof(((struct monst*)0)->mw)),
DIG_META(objSize,sizeof(struct obj)),
DIG_META(obj_nobj,offsetof(struct obj,nobj)),
DIG_META(obj_nobj_size,sizeof(((struct obj*)0)->nobj)),
DIG_META(obj_nexthere,offsetof(struct obj,nexthere)),
DIG_META(obj_nexthere_size,sizeof(((struct obj*)0)->nexthere)),
DIG_META(obj_cobj,offsetof(struct obj,cobj)),
DIG_META(obj_cobj_size,sizeof(((struct obj*)0)->cobj)),
DIG_META(obj_ocarry,offsetof(struct obj,ocarry)),
DIG_META(obj_ocarry_size,sizeof(((struct obj*)0)->ocarry)),
DIG_META(obj_otyp,offsetof(struct obj,otyp)),
DIG_META(obj_otyp_size,sizeof(((struct obj*)0)->otyp)),
DIG_META(obj_ox,offsetof(struct obj,ox)),
DIG_META(obj_ox_size,sizeof(((struct obj*)0)->ox)),
DIG_META(obj_oy,offsetof(struct obj,oy)),
DIG_META(obj_oy_size,sizeof(((struct obj*)0)->oy)),
DIG_META(obj_spe,offsetof(struct obj,spe)),
DIG_META(obj_spe_size,sizeof(((struct obj*)0)->spe)),
DIG_META(obj_oclass,offsetof(struct obj,oclass)),
DIG_META(obj_oclass_size,sizeof(((struct obj*)0)->oclass)),
DIG_META(obj_invlet,offsetof(struct obj,invlet)),
DIG_META(obj_invlet_size,sizeof(((struct obj*)0)->invlet)),
DIG_META(obj_where,offsetof(struct obj,where)),
DIG_META(obj_where_size,sizeof(((struct obj*)0)->where)),
DIG_META(obj_age,offsetof(struct obj,age)),
DIG_META(obj_age_size,sizeof(((struct obj*)0)->age)),
DIG_META(obj_owornmask,offsetof(struct obj,owornmask)),
DIG_META(obj_owornmask_size,sizeof(((struct obj*)0)->owornmask)),
DIG_META(obj_leashmon,offsetof(struct obj,leashmon)),
DIG_META(obj_leashmon_size,sizeof(((struct obj*)0)->leashmon)),
DIG_META(obj_timed,offsetof(struct obj,timed)),
DIG_META(obj_timed_size,sizeof(((struct obj*)0)->timed)),
DIG_META(obj_quan,offsetof(struct obj,quan)),
DIG_META(obj_quan_size,sizeof(((struct obj*)0)->quan)),
DIG_META(obj_owt,offsetof(struct obj,owt)),
DIG_META(obj_owt_size,sizeof(((struct obj*)0)->owt)),
DIG_META(obj_o_id,offsetof(struct obj,o_id)),
DIG_META(obj_o_id_size,sizeof(((struct obj*)0)->o_id)),
DIG_META(pmSize,sizeof(struct permonst)),
DIG_META(pm_mflags1,offsetof(struct permonst,mflags1)),
DIG_META(pm_mflags1_size,sizeof(((struct permonst*)0)->mflags1)),
DIG_META(pm_mflags2,offsetof(struct permonst,mflags2)),
DIG_META(pm_mflags2_size,sizeof(((struct permonst*)0)->mflags2)),
DIG_META(pm_geno,offsetof(struct permonst,geno)),
DIG_META(pm_geno_size,sizeof(((struct permonst*)0)->geno)),
DIG_META(pm_msize,offsetof(struct permonst,msize)),
DIG_META(pm_msize_size,sizeof(((struct permonst*)0)->msize)),
DIG_META(pm_mlet,offsetof(struct permonst,mlet)),
DIG_META(pm_mlet_size,sizeof(((struct permonst*)0)->mlet)),
DIG_META(pm_mattk,offsetof(struct permonst,mattk)),
DIG_META(pm_mattk_size,sizeof(((struct permonst*)0)->mattk)),
DIG_META(attackSize,sizeof(struct attack)),
DIG_META(attack_aatyp,offsetof(struct attack,aatyp)),
DIG_META(attack_aatyp_size,sizeof(((struct attack*)0)->aatyp)),
DIG_META(attack_adtyp,offsetof(struct attack,adtyp)),
DIG_META(attack_adtyp_size,sizeof(((struct attack*)0)->adtyp)),
DIG_META(attack_damn,offsetof(struct attack,damn)),
DIG_META(attack_damn_size,sizeof(((struct attack*)0)->damn)),
DIG_META(attack_damd,offsetof(struct attack,damd)),
DIG_META(attack_damd_size,sizeof(((struct attack*)0)->damd)),
DIG_META(trapSize,sizeof(struct trap)),
DIG_META(trap_ntrap,offsetof(struct trap,ntrap)),
DIG_META(trap_ntrap_size,sizeof(((struct trap*)0)->ntrap)),
DIG_META(trap_tx,offsetof(struct trap,tx)),
DIG_META(trap_tx_size,sizeof(((struct trap*)0)->tx)),
DIG_META(trap_ty,offsetof(struct trap,ty)),
DIG_META(trap_ty_size,sizeof(((struct trap*)0)->ty)),
DIG_META(trap_conjoined,offsetof(struct trap,conjoined)),
DIG_META(trap_conjoined_size,sizeof(((struct trap*)0)->conjoined)),
DIG_META(rmSize,sizeof(struct rm)),
DIG_META(rm_typ,offsetof(struct rm,typ)),
DIG_META(rm_typ_size,sizeof(((struct rm*)0)->typ)),
DIG_META(rm_seenv,offsetof(struct rm,seenv)),
DIG_META(rm_seenv_size,sizeof(((struct rm*)0)->seenv)),
DIG_META(clsSize,sizeof(struct objclass)),
DIG_META(cls_oc_skill,offsetof(struct objclass,oc_skill)),
DIG_META(cls_oc_skill_size,sizeof(((struct objclass*)0)->oc_skill)),
DIG_META(cls_oc_name_idx,offsetof(struct objclass,oc_name_idx)),
DIG_META(cls_oc_name_idx_size,sizeof(((struct objclass*)0)->oc_name_idx)),
DIG_META(descrSize,sizeof(struct objdescr)),
DIG_META(descr_oc_name,offsetof(struct objdescr,oc_name)),
DIG_META(descr_oc_name_size,sizeof(((struct objdescr*)0)->oc_name)),
DIG_META(stairSize,sizeof(stairway)),
DIG_META(stair_isladder,offsetof(stairway,isladder)),
DIG_META(stair_isladder_size,sizeof(((stairway*)0)->isladder)),
DIG_META(genderSize,sizeof(struct Gender)),
DIG_META(gender_his,offsetof(struct Gender,his)),
DIG_META(gender_his_size,sizeof(((struct Gender*)0)->his)),
DIG_META(contextSize,sizeof(struct context_info)),
DIG_META(context_digging,offsetof(struct context_info,digging)),
DIG_META(context_digging_size,sizeof(((struct context_info*)0)->digging)),
DIG_META(context_mon_moving,offsetof(struct context_info,mon_moving)),
DIG_META(context_mon_moving_size,sizeof(((struct context_info*)0)->mon_moving)),
DIG_META(svcSize,sizeof(__typeof__(svc))),
DIG_META(svc_context,offsetof(__typeof__(svc),context)),
DIG_META(svc_context_size,sizeof(((__typeof__(svc)*)0)->context)),
DIG_META(svmSize,sizeof(__typeof__(svm))),
DIG_META(svm_moves,offsetof(__typeof__(svm),moves)),
DIG_META(svm_moves_size,sizeof(((__typeof__(svm)*)0)->moves)),
DIG_META(gySize,sizeof(__typeof__(gy))),
DIG_META(gy_youmonst,offsetof(__typeof__(gy),youmonst)),
DIG_META(gy_youmonst_size,sizeof(((__typeof__(gy)*)0)->youmonst)),
DIG_META(gdSize,sizeof(__typeof__(gd))),
DIG_META(gd_did_dig_msg,offsetof(__typeof__(gd),did_dig_msg)),
DIG_META(gd_did_dig_msg_size,sizeof(((__typeof__(gd)*)0)->did_dig_msg)),
DIG_META(gvSize,sizeof(__typeof__(gv))),
DIG_META(gv_viz_array,offsetof(__typeof__(gv),viz_array)),
DIG_META(gv_viz_array_size,sizeof(((__typeof__(gv)*)0)->viz_array)),
DIG_META(gv_vision_full_recalc,offsetof(__typeof__(gv),vision_full_recalc)),
DIG_META(gv_vision_full_recalc_size,sizeof(((__typeof__(gv)*)0)->vision_full_recalc)),
DIG_META(gmSize,sizeof(__typeof__(gm))),
DIG_META(gm_multi,offsetof(__typeof__(gm),multi)),
DIG_META(gm_multi_size,sizeof(((__typeof__(gm)*)0)->multi)),
DIG_META(gm_multi_reason,offsetof(__typeof__(gm),multi_reason)),
DIG_META(gm_multi_reason_size,sizeof(((__typeof__(gm)*)0)->multi_reason)),
DIG_META(gnSize,sizeof(__typeof__(gn))),
DIG_META(gn_nomovemsg,offsetof(__typeof__(gn),nomovemsg)),
DIG_META(gn_nomovemsg_size,sizeof(((__typeof__(gn)*)0)->nomovemsg)),
DIG_META(goSize,sizeof(__typeof__(go))),
DIG_META(go_occupation,offsetof(__typeof__(go),occupation)),
DIG_META(go_occupation_size,sizeof(((__typeof__(go)*)0)->occupation)),
DIG_META(flagsSize,sizeof(struct flag)),
DIG_META(flags_verbose,offsetof(struct flag,verbose)),
DIG_META(flags_verbose_size,sizeof(((struct flag*)0)->verbose)),
DIG_META(flags_autodig,offsetof(struct flag,autodig)),
DIG_META(flags_autodig_size,sizeof(((struct flag*)0)->autodig)),
DIG_META(flags_female,offsetof(struct flag,female)),
DIG_META(flags_female_size,sizeof(((struct flag*)0)->female)),
DIG_META(iflagsSize,sizeof(struct instance_flags)),
DIG_META(iflags_last_msg,offsetof(struct instance_flags,last_msg)),
DIG_META(iflags_last_msg_size,sizeof(((struct instance_flags*)0)->last_msg)),
DIG_META(iflags_sanity_check,offsetof(struct instance_flags,sanity_check)),
DIG_META(iflags_sanity_check_size,sizeof(((struct instance_flags*)0)->sanity_check)),
DIG_META(dispSize,sizeof(__typeof__(disp))),
DIG_META(disp_botl,offsetof(__typeof__(disp),botl)),
DIG_META(disp_botl_size,sizeof(((__typeof__(disp)*)0)->botl)),
DIG_META(RoleSize,sizeof(struct Role)),
DIG_META(Role_mnum,offsetof(struct Role,mnum)),
DIG_META(Role_mnum_size,sizeof(((struct Role*)0)->mnum)),
DIG_META(RaceSize,sizeof(struct Race)),
DIG_META(Race_mnum,offsetof(struct Race,mnum)),
DIG_META(Race_mnum_size,sizeof(((struct Race*)0)->mnum)),
DIG_META(guSize,sizeof(__typeof__(gu))),
DIG_META(gu_urole,offsetof(__typeof__(gu),urole)),
DIG_META(gu_urole_size,sizeof(((__typeof__(gu)*)0)->urole)),
DIG_META(gu_urace,offsetof(__typeof__(gu),urace)),
DIG_META(gu_urace_size,sizeof(((__typeof__(gu)*)0)->urace)),
DIG_META(anySize,sizeof(anything)),
DIG_META(any_a_obj,offsetof(anything,a_obj)),
DIG_META(any_a_obj_size,sizeof(((anything*)0)->a_obj)),
DIG_META(AD_DGST,AD_DGST),
DIG_META(ALTAR,ALTAR),
DIG_META(AM_LAWFUL,AM_LAWFUL),
DIG_META(AM_MASK,AM_MASK),
DIG_META(AM_SANCTUM,AM_SANCTUM),
DIG_META(ANTI_MAGIC,ANTI_MAGIC),
DIG_META(APPLE,APPLE),
DIG_META(AT_ENGL,AT_ENGL),
DIG_META(AXE,AXE),
DIG_META(A_CHA,A_CHA),
DIG_META(A_CHAOTIC,A_CHAOTIC),
DIG_META(A_CON,A_CON),
DIG_META(A_DEX,A_DEX),
DIG_META(A_INT,A_INT),
DIG_META(A_LAWFUL,A_LAWFUL),
DIG_META(A_NONE,A_NONE),
DIG_META(A_STR,A_STR),
DIG_META(A_WIS,A_WIS),
DIG_META(BATTLE_AXE,BATTLE_AXE),
DIG_META(BEARTRAP,BEARTRAP),
DIG_META(BEAR_TRAP,BEAR_TRAP),
DIG_META(BLINDED,BLINDED),
DIG_META(BOULDER,BOULDER),
DIG_META(BUFSZ,BUFSZ),
DIG_META(CHEST,CHEST),
DIG_META(COIN_CLASS,COIN_CLASS),
DIG_META(COLNO,COLNO),
DIG_META(CORPSE,CORPSE),
DIG_META(CORR,CORR),
DIG_META(COULD_SEE,COULD_SEE),
DIG_META(CQ_CANNED,CQ_CANNED),
DIG_META(CXN_NO_PFX,CXN_NO_PFX),
DIG_META(DAGGER,DAGGER),
DIG_META(DBWALL,DBWALL),
DIG_META(DB_LAVA,DB_LAVA),
DIG_META(DB_MOAT,DB_MOAT),
DIG_META(DB_UNDER,DB_UNDER),
DIG_META(DEAF,DEAF),
DIG_META(DIGCHECK_FAILED,DIGCHECK_FAILED),
DIG_META(DIGCHECK_FAIL_AIRLEVEL,DIGCHECK_FAIL_AIRLEVEL),
DIG_META(DIGCHECK_FAIL_ALTAR,DIGCHECK_FAIL_ALTAR),
DIG_META(DIGCHECK_FAIL_BOULDER,DIGCHECK_FAIL_BOULDER),
DIG_META(DIGCHECK_FAIL_CANTDIG,DIGCHECK_FAIL_CANTDIG),
DIG_META(DIGCHECK_FAIL_OBJ_POOL_OR_TRAP,DIGCHECK_FAIL_OBJ_POOL_OR_TRAP),
DIG_META(DIGCHECK_FAIL_ONLADDER,DIGCHECK_FAIL_ONLADDER),
DIG_META(DIGCHECK_FAIL_ONSTAIRS,DIGCHECK_FAIL_ONSTAIRS),
DIG_META(DIGCHECK_FAIL_THRONE,DIGCHECK_FAIL_THRONE),
DIG_META(DIGCHECK_FAIL_TOOHARD,DIGCHECK_FAIL_TOOHARD),
DIG_META(DIGCHECK_FAIL_UNDESTROYABLETRAP,DIGCHECK_FAIL_UNDESTROYABLETRAP),
DIG_META(DIGCHECK_FAIL_WATERLEVEL,DIGCHECK_FAIL_WATERLEVEL),
DIG_META(DIGCHECK_PASSED,DIGCHECK_PASSED),
DIG_META(DIGCHECK_PASSED_DESTROY_TRAP,DIGCHECK_PASSED_DESTROY_TRAP),
DIG_META(DIGCHECK_PASSED_PITONLY,DIGCHECK_PASSED_PITONLY),
DIG_META(DIR_E,DIR_E),
DIG_META(DIR_ERR,DIR_ERR),
DIG_META(DIR_W,DIR_W),
DIG_META(DISP_BEAM,DISP_BEAM),
DIG_META(DISP_END,DISP_END),
DIG_META(DOOR,DOOR),
DIG_META(DRAWBRIDGE_DOWN,DRAWBRIDGE_DOWN),
DIG_META(DRAWBRIDGE_UP,DRAWBRIDGE_UP),
DIG_META(DWARVISH_MATTOCK,DWARVISH_MATTOCK),
DIG_META(D_BROKEN,D_BROKEN),
DIG_META(D_CLOSED,D_CLOSED),
DIG_META(D_NODOOR,D_NODOOR),
DIG_META(D_TRAPPED,D_TRAPPED),
DIG_META(ECMD_CANCEL,ECMD_CANCEL),
DIG_META(ECMD_OK,ECMD_OK),
DIG_META(ECMD_TIME,ECMD_TIME),
DIG_META(EGG,EGG),
DIG_META(EXPL_MAGICAL,EXPL_MAGICAL),
DIG_META(FLYING,FLYING),
DIG_META(FOOT,FOOT),
DIG_META(FORCEBUNGLE,FORCEBUNGLE),
DIG_META(FORCETRAP,FORCETRAP),
DIG_META(FOUNTAIN,FOUNTAIN),
DIG_META(FROMOUTSIDE,FROMOUTSIDE),
DIG_META(FUMBLING,FUMBLING),
DIG_META(F_WARNED,F_WARNED),
DIG_META(GRAVE,GRAVE),
DIG_META(G_UNIQ,G_UNIQ),
DIG_META(HALF_PHDAM,HALF_PHDAM),
DIG_META(HALLUC,HALLUC),
DIG_META(HALLUC_RES,HALLUC_RES),
DIG_META(HEAD,HEAD),
DIG_META(HEAVY_IRON_BALL,HEAVY_IRON_BALL),
DIG_META(HOLE,HOLE),
DIG_META(HWALL,HWALL),
DIG_META(ICE,ICE),
DIG_META(INVIS,INVIS),
DIG_META(IN_SIGHT,IN_SIGHT),
DIG_META(IRONBARS,IRONBARS),
DIG_META(IRON_CHAIN,IRON_CHAIN),
DIG_META(KILLED_BY,KILLED_BY),
DIG_META(KILLED_BY_AN,KILLED_BY_AN),
DIG_META(LANDMINE,LANDMINE),
DIG_META(LAND_MINE,LAND_MINE),
DIG_META(LAST_PROP,LAST_PROP),
DIG_META(LAVAPOOL,LAVAPOOL),
DIG_META(LAVAWALL,LAVAWALL),
DIG_META(LEASH,LEASH),
DIG_META(LEVEL_TELEP,LEVEL_TELEP),
DIG_META(LEVITATION,LEVITATION),
DIG_META(LOW_BOOTS,LOW_BOOTS),
DIG_META(M1_CLING,M1_CLING),
DIG_META(M1_CONCEAL,M1_CONCEAL),
DIG_META(M1_FLY,M1_FLY),
DIG_META(M1_SEE_INVIS,M1_SEE_INVIS),
DIG_META(M1_UNSOLID,M1_UNSOLID),
DIG_META(M1_WALLWALK,M1_WALLWALK),
DIG_META(MAGIC_PORTAL,MAGIC_PORTAL),
DIG_META(MAGIC_TRAP,MAGIC_TRAP),
DIG_META(MAXOCLASSES,MAXOCLASSES),
DIG_META(MAX_TYPE,MAX_TYPE),
DIG_META(MIGR_RANDOM,MIGR_RANDOM),
DIG_META(MM_NOMSG,MM_NOMSG),
DIG_META(MOAT,MOAT),
DIG_META(MV_WALK,MV_WALK),
DIG_META(MZ_HUGE,MZ_HUGE),
DIG_META(NATTK,NATTK),
DIG_META(NON_PM,NON_PM),
DIG_META(NO_PART,NO_PART),
DIG_META(NO_TRAP_FLAGS,NO_TRAP_FLAGS),
DIG_META(NUMMONS,NUMMONS),
DIG_META(NUM_OBJECTS,NUM_OBJECTS),
DIG_META(N_DIRS,N_DIRS),
DIG_META(N_DIRS_Z,N_DIRS_Z),
DIG_META(OBJ_BURIED,OBJ_BURIED),
DIG_META(OBJ_CONTAINED,OBJ_CONTAINED),
DIG_META(OBJ_FLOOR,OBJ_FLOOR),
DIG_META(OBJ_FREE,OBJ_FREE),
DIG_META(OBJ_INVENT,OBJ_INVENT),
DIG_META(OBJ_MIGRATING,OBJ_MIGRATING),
DIG_META(OBJ_MINVENT,OBJ_MINVENT),
DIG_META(PICK_AXE,PICK_AXE),
DIG_META(PIT,PIT),
DIG_META(PM_AIR_ELEMENTAL,PM_AIR_ELEMENTAL),
DIG_META(PM_ARCHEOLOGIST,PM_ARCHEOLOGIST),
DIG_META(PM_DWARF,PM_DWARF),
DIG_META(PM_EARTH_ELEMENTAL,PM_EARTH_ELEMENTAL),
DIG_META(PM_ELF,PM_ELF),
DIG_META(PM_HUMAN,PM_HUMAN),
DIG_META(PM_PURPLE_WORM,PM_PURPLE_WORM),
DIG_META(PM_RANGER,PM_RANGER),
DIG_META(PM_SAMURAI,PM_SAMURAI),
DIG_META(PM_WATCHMAN,PM_WATCHMAN),
DIG_META(PM_WATCH_CAPTAIN,PM_WATCH_CAPTAIN),
DIG_META(PM_XORN,PM_XORN),
DIG_META(POLY_TRAP,POLY_TRAP),
DIG_META(POOL,POOL),
DIG_META(POTION_CLASS,POTION_CLASS),
DIG_META(POT_HEALING,POT_HEALING),
DIG_META(POT_OIL,POT_OIL),
DIG_META(P_AXE,P_AXE),
DIG_META(P_PICK_AXE,P_PICK_AXE),
DIG_META(RIGHT_SIDE,RIGHT_SIDE),
DIG_META(RING_CLASS,RING_CLASS),
DIG_META(RLOC_NOMSG,RLOC_NOMSG),
DIG_META(ROCK,ROCK),
DIG_META(ROOM,ROOM),
DIG_META(ROT_ORGANIC,ROT_ORGANIC),
DIG_META(ROWNO,ROWNO),
DIG_META(SCORR,SCORR),
DIG_META(SDOOR,SDOOR),
DIG_META(SHOPBASE,SHOPBASE),
DIG_META(SHOP_DOOR_COST,SHOP_DOOR_COST),
DIG_META(SHOP_PIT_COST,SHOP_PIT_COST),
DIG_META(SHOP_WALL_COST,SHOP_WALL_COST),
DIG_META(SINK,SINK),
DIG_META(SPIKED_PIT,SPIKED_PIT),
DIG_META(STAIRS,STAIRS),
DIG_META(STATUE,STATUE),
DIG_META(STOMACH,STOMACH),
DIG_META(STONE,STONE),
DIG_META(S_EYE,S_EYE),
DIG_META(S_LIGHT,S_LIGHT),
DIG_META(S_MUMMY,S_MUMMY),
DIG_META(S_VORTEX,S_VORTEX),
DIG_META(S_ZOMBIE,S_ZOMBIE),
DIG_META(S_digbeam,S_digbeam),
DIG_META(TAINT_AGE,TAINT_AGE),
DIG_META(TELEP_TRAP,TELEP_TRAP),
DIG_META(THRONE,THRONE),
DIG_META(TIMER_OBJECT,TIMER_OBJECT),
DIG_META(TOOL_CLASS,TOOL_CLASS),
DIG_META(TRAPDOOR,TRAPDOOR),
DIG_META(TRAP_EXPLODE,TRAP_EXPLODE),
DIG_META(TREE,TREE),
DIG_META(TT_BURIEDBALL,TT_BURIEDBALL),
DIG_META(TT_INFLOOR,TT_INFLOOR),
DIG_META(TT_PIT,TT_PIT),
DIG_META(TT_WEB,TT_WEB),
DIG_META(VIBRATING_SQUARE,VIBRATING_SQUARE),
DIG_META(WATER,WATER),
DIG_META(WEAPON_CLASS,WEAPON_CLASS),
DIG_META(WEB,WEB),
DIG_META(WOOD,WOOD),
DIG_META(W_NONDIGGABLE,W_NONDIGGABLE),
};
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(int)==4 && sizeof(coordxy)==2 && sizeof(boolean)==1,"DIG configured ABI");
_Static_assert(sizeof(((struct you*)0)->ux)==2,"you_ux width");
_Static_assert(((__typeof__(((struct you*)0)->ux))-1 < 0),"you_ux signedness");
_Static_assert(sizeof(((struct you*)0)->uy)==2,"you_uy width");
_Static_assert(((__typeof__(((struct you*)0)->uy))-1 < 0),"you_uy signedness");
_Static_assert(sizeof(((struct you*)0)->dx)==4,"you_dx width");
_Static_assert(((__typeof__(((struct you*)0)->dx))-1 < 0),"you_dx signedness");
_Static_assert(sizeof(((struct you*)0)->dy)==4,"you_dy width");
_Static_assert(((__typeof__(((struct you*)0)->dy))-1 < 0),"you_dy signedness");
_Static_assert(sizeof(((struct you*)0)->dz)==4,"you_dz width");
_Static_assert(((__typeof__(((struct you*)0)->dz))-1 < 0),"you_dz signedness");
_Static_assert(sizeof(((struct you*)0)->utrap)==4,"you_utrap width");
_Static_assert(((__typeof__(((struct you*)0)->utrap))-1 > 0),"you_utrap signedness");
_Static_assert(sizeof(((struct you*)0)->utraptype)==4,"you_utraptype width");
_Static_assert(((__typeof__(((struct you*)0)->utraptype))-1 > 0),"you_utraptype signedness");
_Static_assert(sizeof(((struct you*)0)->udaminc)==1,"you_udaminc width");
_Static_assert(((__typeof__(((struct you*)0)->udaminc))-1 < 0),"you_udaminc signedness");
_Static_assert(sizeof(((struct you*)0)->usteed)==8,"you_usteed pointer width");
_Static_assert(sizeof(((struct you*)0)->ustuck)==8,"you_ustuck pointer width");
_Static_assert(sizeof(((d_level*)0)->dnum)==2,"level_dnum width");
_Static_assert(((__typeof__(((d_level*)0)->dnum))-1 < 0),"level_dnum signedness");
_Static_assert(sizeof(((d_level*)0)->dlevel)==2,"level_dlevel width");
_Static_assert(((__typeof__(((d_level*)0)->dlevel))-1 < 0),"level_dlevel signedness");
_Static_assert(sizeof(((coord*)0)->x)==2,"coord_x width");
_Static_assert(((__typeof__(((coord*)0)->x))-1 < 0),"coord_x signedness");
_Static_assert(sizeof(((coord*)0)->y)==2,"coord_y width");
_Static_assert(((__typeof__(((coord*)0)->y))-1 < 0),"coord_y signedness");
_Static_assert(sizeof(((align*)0)->type)==1,"align_type width");
_Static_assert(((__typeof__(((align*)0)->type))-1 < 0),"align_type signedness");
_Static_assert(sizeof(((align*)0)->record)==4,"align_record width");
_Static_assert(((__typeof__(((align*)0)->record))-1 < 0),"align_record signedness");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8,"prop_intrinsic width");
_Static_assert(((__typeof__(((struct prop*)0)->intrinsic))-1 < 0),"prop_intrinsic signedness");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8,"prop_extrinsic width");
_Static_assert(((__typeof__(((struct prop*)0)->extrinsic))-1 < 0),"prop_extrinsic signedness");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8,"prop_blocked width");
_Static_assert(((__typeof__(((struct prop*)0)->blocked))-1 < 0),"prop_blocked signedness");
_Static_assert(sizeof(((struct dig_info*)0)->effort)==4,"digging_effort width");
_Static_assert(((__typeof__(((struct dig_info*)0)->effort))-1 < 0),"digging_effort signedness");
_Static_assert(sizeof(((struct dig_info*)0)->lastdigtime)==8,"digging_lastdigtime width");
_Static_assert(((__typeof__(((struct dig_info*)0)->lastdigtime))-1 < 0),"digging_lastdigtime signedness");
_Static_assert(sizeof(((struct dig_info*)0)->down)==1,"digging_down width");
_Static_assert(((__typeof__(((struct dig_info*)0)->down))-1 < 0),"digging_down signedness");
_Static_assert(sizeof(((struct dig_info*)0)->chew)==1,"digging_chew width");
_Static_assert(((__typeof__(((struct dig_info*)0)->chew))-1 < 0),"digging_chew signedness");
_Static_assert(sizeof(((struct dig_info*)0)->warned)==1,"digging_warned width");
_Static_assert(((__typeof__(((struct dig_info*)0)->warned))-1 < 0),"digging_warned signedness");
_Static_assert(sizeof(((struct dig_info*)0)->quiet)==1,"digging_quiet width");
_Static_assert(((__typeof__(((struct dig_info*)0)->quiet))-1 < 0),"digging_quiet signedness");
_Static_assert(sizeof(((struct monst*)0)->data)==8,"mon_data pointer width");
_Static_assert(sizeof(((struct monst*)0)->mx)==2,"mon_mx width");
_Static_assert(((__typeof__(((struct monst*)0)->mx))-1 < 0),"mon_mx signedness");
_Static_assert(sizeof(((struct monst*)0)->my)==2,"mon_my width");
_Static_assert(((__typeof__(((struct monst*)0)->my))-1 < 0),"mon_my signedness");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4,"mon_mhp width");
_Static_assert(((__typeof__(((struct monst*)0)->mhp))-1 < 0),"mon_mhp signedness");
_Static_assert(sizeof(((struct monst*)0)->mw)==8,"mon_mw pointer width");
_Static_assert(sizeof(((struct obj*)0)->nobj)==8,"obj_nobj pointer width");
_Static_assert(sizeof(((struct obj*)0)->nexthere)==8,"obj_nexthere pointer width");
_Static_assert(sizeof(((struct obj*)0)->cobj)==8,"obj_cobj pointer width");
_Static_assert(sizeof(((struct obj*)0)->ocarry)==8,"obj_ocarry pointer width");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2,"obj_otyp width");
_Static_assert(((__typeof__(((struct obj*)0)->otyp))-1 < 0),"obj_otyp signedness");
_Static_assert(sizeof(((struct obj*)0)->ox)==2,"obj_ox width");
_Static_assert(((__typeof__(((struct obj*)0)->ox))-1 < 0),"obj_ox signedness");
_Static_assert(sizeof(((struct obj*)0)->oy)==2,"obj_oy width");
_Static_assert(((__typeof__(((struct obj*)0)->oy))-1 < 0),"obj_oy signedness");
_Static_assert(sizeof(((struct obj*)0)->spe)==1,"obj_spe width");
_Static_assert(((__typeof__(((struct obj*)0)->spe))-1 < 0),"obj_spe signedness");
_Static_assert(sizeof(((struct obj*)0)->oclass)==1,"obj_oclass width");
_Static_assert(((__typeof__(((struct obj*)0)->oclass))-1 < 0),"obj_oclass signedness");
_Static_assert(sizeof(((struct obj*)0)->invlet)==1,"obj_invlet width");
_Static_assert(((__typeof__(((struct obj*)0)->invlet))-1 < 0),"obj_invlet signedness");
_Static_assert(sizeof(((struct obj*)0)->where)==1,"obj_where width");
_Static_assert(((__typeof__(((struct obj*)0)->where))-1 < 0),"obj_where signedness");
_Static_assert(sizeof(((struct obj*)0)->age)==8,"obj_age width");
_Static_assert(((__typeof__(((struct obj*)0)->age))-1 < 0),"obj_age signedness");
_Static_assert(sizeof(((struct obj*)0)->owornmask)==8,"obj_owornmask width");
_Static_assert(((__typeof__(((struct obj*)0)->owornmask))-1 < 0),"obj_owornmask signedness");
_Static_assert(sizeof(((struct obj*)0)->leashmon)==4,"obj_leashmon width");
_Static_assert(((__typeof__(((struct obj*)0)->leashmon))-1 < 0),"obj_leashmon signedness");
_Static_assert(sizeof(((struct obj*)0)->timed)==2,"obj_timed width");
_Static_assert(((__typeof__(((struct obj*)0)->timed))-1 < 0),"obj_timed signedness");
_Static_assert(sizeof(((struct obj*)0)->quan)==8,"obj_quan width");
_Static_assert(((__typeof__(((struct obj*)0)->quan))-1 < 0),"obj_quan signedness");
_Static_assert(sizeof(((struct obj*)0)->owt)==4,"obj_owt width");
_Static_assert(((__typeof__(((struct obj*)0)->owt))-1 > 0),"obj_owt signedness");
_Static_assert(sizeof(((struct obj*)0)->o_id)==4,"obj_o_id width");
_Static_assert(((__typeof__(((struct obj*)0)->o_id))-1 > 0),"obj_o_id signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8,"pm_mflags1 width");
_Static_assert(((__typeof__(((struct permonst*)0)->mflags1))-1 > 0),"pm_mflags1 signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8,"pm_mflags2 width");
_Static_assert(((__typeof__(((struct permonst*)0)->mflags2))-1 > 0),"pm_mflags2 signedness");
_Static_assert(sizeof(((struct permonst*)0)->geno)==2,"pm_geno width");
_Static_assert(((__typeof__(((struct permonst*)0)->geno))-1 > 0),"pm_geno signedness");
_Static_assert(sizeof(((struct permonst*)0)->msize)==1,"pm_msize width");
_Static_assert(((__typeof__(((struct permonst*)0)->msize))-1 > 0),"pm_msize signedness");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1,"pm_mlet width");
_Static_assert(((__typeof__(((struct permonst*)0)->mlet))-1 < 0),"pm_mlet signedness");
_Static_assert(sizeof(((struct attack*)0)->aatyp)==1,"attack_aatyp width");
_Static_assert(((__typeof__(((struct attack*)0)->aatyp))-1 > 0),"attack_aatyp signedness");
_Static_assert(sizeof(((struct attack*)0)->adtyp)==1,"attack_adtyp width");
_Static_assert(((__typeof__(((struct attack*)0)->adtyp))-1 > 0),"attack_adtyp signedness");
_Static_assert(sizeof(((struct attack*)0)->damn)==1,"attack_damn width");
_Static_assert(((__typeof__(((struct attack*)0)->damn))-1 > 0),"attack_damn signedness");
_Static_assert(sizeof(((struct attack*)0)->damd)==1,"attack_damd width");
_Static_assert(((__typeof__(((struct attack*)0)->damd))-1 > 0),"attack_damd signedness");
_Static_assert(sizeof(((struct trap*)0)->ntrap)==8,"trap_ntrap pointer width");
_Static_assert(sizeof(((struct trap*)0)->tx)==2,"trap_tx width");
_Static_assert(((__typeof__(((struct trap*)0)->tx))-1 < 0),"trap_tx signedness");
_Static_assert(sizeof(((struct trap*)0)->ty)==2,"trap_ty width");
_Static_assert(((__typeof__(((struct trap*)0)->ty))-1 < 0),"trap_ty signedness");
_Static_assert(sizeof(((struct trap*)0)->conjoined)==1,"trap_conjoined width");
_Static_assert(((__typeof__(((struct trap*)0)->conjoined))-1 > 0),"trap_conjoined signedness");
_Static_assert(sizeof(((struct rm*)0)->typ)==1,"rm_typ width");
_Static_assert(((__typeof__(((struct rm*)0)->typ))-1 < 0),"rm_typ signedness");
_Static_assert(sizeof(((struct rm*)0)->seenv)==1,"rm_seenv width");
_Static_assert(((__typeof__(((struct rm*)0)->seenv))-1 > 0),"rm_seenv signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_skill)==1,"cls_oc_skill width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_skill))-1 < 0),"cls_oc_skill signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_name_idx)==2,"cls_oc_name_idx width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_name_idx))-1 < 0),"cls_oc_name_idx signedness");
_Static_assert(sizeof(((struct objdescr*)0)->oc_name)==8,"descr_oc_name pointer width");
_Static_assert(sizeof(((stairway*)0)->isladder)==1,"stair_isladder width");
_Static_assert(((__typeof__(((stairway*)0)->isladder))-1 < 0),"stair_isladder signedness");
_Static_assert(sizeof(((struct Gender*)0)->his)==8,"gender_his pointer width");
_Static_assert(sizeof(((struct context_info*)0)->mon_moving)==1,"context_mon_moving width");
_Static_assert(((__typeof__(((struct context_info*)0)->mon_moving))-1 < 0),"context_mon_moving signedness");
_Static_assert(sizeof(((__typeof__(svm)*)0)->moves)==8,"svm_moves width");
_Static_assert(((__typeof__(((__typeof__(svm)*)0)->moves))-1 < 0),"svm_moves signedness");
_Static_assert(sizeof(((__typeof__(gd)*)0)->did_dig_msg)==1,"gd_did_dig_msg width");
_Static_assert(((__typeof__(((__typeof__(gd)*)0)->did_dig_msg))-1 < 0),"gd_did_dig_msg signedness");
_Static_assert(sizeof(((__typeof__(gv)*)0)->viz_array)==8,"gv_viz_array pointer width");
_Static_assert(sizeof(((__typeof__(gv)*)0)->vision_full_recalc)==1,"gv_vision_full_recalc width");
_Static_assert(((__typeof__(((__typeof__(gv)*)0)->vision_full_recalc))-1 < 0),"gv_vision_full_recalc signedness");
_Static_assert(sizeof(((__typeof__(gm)*)0)->multi)==8,"gm_multi width");
_Static_assert(((__typeof__(((__typeof__(gm)*)0)->multi))-1 < 0),"gm_multi signedness");
_Static_assert(sizeof(((__typeof__(gm)*)0)->multi_reason)==8,"gm_multi_reason pointer width");
_Static_assert(sizeof(((__typeof__(gn)*)0)->nomovemsg)==8,"gn_nomovemsg pointer width");
_Static_assert(sizeof(((__typeof__(go)*)0)->occupation)==8,"go_occupation pointer width");
_Static_assert(sizeof(((struct flag*)0)->verbose)==1,"flags_verbose width");
_Static_assert(((__typeof__(((struct flag*)0)->verbose))-1 < 0),"flags_verbose signedness");
_Static_assert(sizeof(((struct flag*)0)->autodig)==1,"flags_autodig width");
_Static_assert(((__typeof__(((struct flag*)0)->autodig))-1 < 0),"flags_autodig signedness");
_Static_assert(sizeof(((struct flag*)0)->female)==1,"flags_female width");
_Static_assert(((__typeof__(((struct flag*)0)->female))-1 < 0),"flags_female signedness");
_Static_assert(sizeof(((struct instance_flags*)0)->last_msg)==4,"iflags_last_msg width");
_Static_assert(((__typeof__(((struct instance_flags*)0)->last_msg))-1 < 0),"iflags_last_msg signedness");
_Static_assert(sizeof(((struct instance_flags*)0)->sanity_check)==1,"iflags_sanity_check width");
_Static_assert(((__typeof__(((struct instance_flags*)0)->sanity_check))-1 < 0),"iflags_sanity_check signedness");
_Static_assert(sizeof(((__typeof__(disp)*)0)->botl)==1,"disp_botl width");
_Static_assert(((__typeof__(((__typeof__(disp)*)0)->botl))-1 < 0),"disp_botl signedness");
_Static_assert(sizeof(((struct Role*)0)->mnum)==2,"Role_mnum width");
_Static_assert(((__typeof__(((struct Role*)0)->mnum))-1 < 0),"Role_mnum signedness");
_Static_assert(sizeof(((struct Race*)0)->mnum)==2,"Race_mnum width");
_Static_assert(((__typeof__(((struct Race*)0)->mnum))-1 < 0),"Race_mnum signedness");
_Static_assert(sizeof(((anything*)0)->a_obj)==8,"any_a_obj pointer width");
_Static_assert(sizeof xdir[0]==1 && ((__typeof__(xdir[0]))-1<0),"xdir signed8");
_Static_assert(sizeof ydir[0]==1 && ((__typeof__(ydir[0]))-1<0),"ydir signed8");
_Static_assert(sizeof xdir/sizeof xdir[0]==N_DIRS_Z && sizeof ydir/sizeof ydir[0]==N_DIRS_Z,"native direction counts");
size_t probe_context_size(void){return sizeof(struct dig_info);}
int probe_layout_count(void){return sizeof teleport_dig_layout/sizeof teleport_dig_layout[0];}
const char*probe_layout_name(int i){return teleport_dig_layout[i].name;}
size_t probe_layout_value(int i){return teleport_dig_layout[i].value;}
#endif
