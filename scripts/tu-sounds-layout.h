#ifndef TELEPORT_SOUNDS_LAYOUT_H
#define TELEPORT_SOUNDS_LAYOUT_H
#include "hack.h"
#include <stddef.h>
#ifdef USER_SOUNDS
#define TELEPORT_SOUNDS_USER 1
#else
#define TELEPORT_SOUNDS_USER 0
#endif
#ifdef SND_SPEECH
#define TELEPORT_SOUNDS_SPEECH 1
#else
#define TELEPORT_SOUNDS_SPEECH 0
#endif
#ifdef SND_SOUNDEFFECTS_AUTOMAP
#define TELEPORT_SOUNDS_AUTOMAP 1
#else
#define TELEPORT_SOUNDS_AUTOMAP 0
#endif
#ifdef SND_LIB_INTEGRATED
#define TELEPORT_SOUNDS_INTEGRATED 1
#else
#define TELEPORT_SOUNDS_INTEGRATED 0
#endif
struct teleport_sounds_meta {const char*name;size_t value;};
#define SOUNDS_META(k,v) {#k,(size_t)(v)}
static const struct teleport_sounds_meta sounds_layout[]={
SOUNDS_META(configUserSounds,TELEPORT_SOUNDS_USER),
SOUNDS_META(configSpeech,TELEPORT_SOUNDS_SPEECH),
SOUNDS_META(configAutoMap,TELEPORT_SOUNDS_AUTOMAP),
SOUNDS_META(configIntegrated,TELEPORT_SOUNDS_INTEGRATED),
SOUNDS_META(configSoundlibCount,soundlib_notused),
SOUNDS_META(suffixSize,sizeof ".wav"),
SOUNDS_META(pointerSize,sizeof(void*)),
SOUNDS_META(intSize,sizeof(int)),
SOUNDS_META(longSize,sizeof(long)),
SOUNDS_META(monSize,sizeof(struct monst)),
SOUNDS_META(mon_data,offsetof(struct monst,data)),
SOUNDS_META(mon_data_size,sizeof(((struct monst*)0)->data)),
SOUNDS_META(mon_nmon,offsetof(struct monst,nmon)),
SOUNDS_META(mon_nmon_size,sizeof(((struct monst*)0)->nmon)),
SOUNDS_META(mon_mextra,offsetof(struct monst,mextra)),
SOUNDS_META(mon_mextra_size,sizeof(((struct monst*)0)->mextra)),
SOUNDS_META(mon_m_id,offsetof(struct monst,m_id)),
SOUNDS_META(mon_m_id_size,sizeof(((struct monst*)0)->m_id)),
SOUNDS_META(mon_mtame,offsetof(struct monst,mtame)),
SOUNDS_META(mon_mtame_size,sizeof(((struct monst*)0)->mtame)),
SOUNDS_META(mon_mx,offsetof(struct monst,mx)),
SOUNDS_META(mon_mx_size,sizeof(((struct monst*)0)->mx)),
SOUNDS_META(mon_my,offsetof(struct monst,my)),
SOUNDS_META(mon_my_size,sizeof(((struct monst*)0)->my)),
SOUNDS_META(mon_mhp,offsetof(struct monst,mhp)),
SOUNDS_META(mon_mhp_size,sizeof(((struct monst*)0)->mhp)),
SOUNDS_META(mon_mhpmax,offsetof(struct monst,mhpmax)),
SOUNDS_META(mon_mhpmax_size,sizeof(((struct monst*)0)->mhpmax)),
SOUNDS_META(mon_meating,offsetof(struct monst,meating)),
SOUNDS_META(mon_meating_size,sizeof(((struct monst*)0)->meating)),
SOUNDS_META(mon_mstrategy,offsetof(struct monst,mstrategy)),
SOUNDS_META(mon_mstrategy_size,sizeof(((struct monst*)0)->mstrategy)),
SOUNDS_META(mon_m_ap_type,offsetof(struct monst,m_ap_type)),
SOUNDS_META(mon_m_ap_type_size,sizeof(((struct monst*)0)->m_ap_type)),
SOUNDS_META(mon_cham,offsetof(struct monst,cham)),
SOUNDS_META(mon_cham_size,sizeof(((struct monst*)0)->cham)),
SOUNDS_META(pmSize,sizeof(struct permonst)),
SOUNDS_META(pm_msound,offsetof(struct permonst,msound)),
SOUNDS_META(pm_msound_size,sizeof(((struct permonst*)0)->msound)),
SOUNDS_META(pm_mlet,offsetof(struct permonst,mlet)),
SOUNDS_META(pm_mlet_size,sizeof(((struct permonst*)0)->mlet)),
SOUNDS_META(pm_mlevel,offsetof(struct permonst,mlevel)),
SOUNDS_META(pm_mlevel_size,sizeof(((struct permonst*)0)->mlevel)),
SOUNDS_META(pm_mflags1,offsetof(struct permonst,mflags1)),
SOUNDS_META(pm_mflags1_size,sizeof(((struct permonst*)0)->mflags1)),
SOUNDS_META(pm_mflags2,offsetof(struct permonst,mflags2)),
SOUNDS_META(pm_mflags2_size,sizeof(((struct permonst*)0)->mflags2)),
SOUNDS_META(pm_mflags3,offsetof(struct permonst,mflags3)),
SOUNDS_META(pm_mflags3_size,sizeof(((struct permonst*)0)->mflags3)),
SOUNDS_META(pm_pmidx,offsetof(struct permonst,pmidx)),
SOUNDS_META(pm_pmidx_size,sizeof(((struct permonst*)0)->pmidx)),
SOUNDS_META(objSize,sizeof(struct obj)),
SOUNDS_META(obj_otyp,offsetof(struct obj,otyp)),
SOUNDS_META(obj_otyp_size,sizeof(((struct obj*)0)->otyp)),
SOUNDS_META(obj_oclass,offsetof(struct obj,oclass)),
SOUNDS_META(obj_oclass_size,sizeof(((struct obj*)0)->oclass)),
SOUNDS_META(obj_novelidx,offsetof(struct obj,novelidx)),
SOUNDS_META(obj_novelidx_size,sizeof(((struct obj*)0)->novelidx)),
SOUNDS_META(extraSize,sizeof(struct mextra)),
SOUNDS_META(extra_epri,offsetof(struct mextra,epri)),
SOUNDS_META(extra_epri_size,sizeof(((struct mextra*)0)->epri)),
SOUNDS_META(extra_emin,offsetof(struct mextra,emin)),
SOUNDS_META(extra_emin_size,sizeof(((struct mextra*)0)->emin)),
SOUNDS_META(extra_edog,offsetof(struct mextra,edog)),
SOUNDS_META(extra_edog_size,sizeof(((struct mextra*)0)->edog)),
SOUNDS_META(edogSize,sizeof(struct edog)),
SOUNDS_META(edog_hungrytime,offsetof(struct edog,hungrytime)),
SOUNDS_META(edog_hungrytime_size,sizeof(((struct edog*)0)->hungrytime)),
SOUNDS_META(epriSize,sizeof(struct epri)),
SOUNDS_META(epri_shroom,offsetof(struct epri,shroom)),
SOUNDS_META(epri_shroom_size,sizeof(((struct epri*)0)->shroom)),
SOUNDS_META(epri_shralign,offsetof(struct epri,shralign)),
SOUNDS_META(epri_shralign_size,sizeof(((struct epri*)0)->shralign)),
SOUNDS_META(epri_shrpos,offsetof(struct epri,shrpos)),
SOUNDS_META(epri_shrpos_size,sizeof(((struct epri*)0)->shrpos)),
SOUNDS_META(eminSize,sizeof(struct emin)),
SOUNDS_META(emin_renegade,offsetof(struct emin,renegade)),
SOUNDS_META(emin_renegade_size,sizeof(((struct emin*)0)->renegade)),
SOUNDS_META(roomSize,sizeof(struct mkroom)),
SOUNDS_META(room_lx,offsetof(struct mkroom,lx)),
SOUNDS_META(room_lx_size,sizeof(((struct mkroom*)0)->lx)),
SOUNDS_META(room_hx,offsetof(struct mkroom,hx)),
SOUNDS_META(room_hx_size,sizeof(((struct mkroom*)0)->hx)),
SOUNDS_META(room_ly,offsetof(struct mkroom,ly)),
SOUNDS_META(room_ly_size,sizeof(((struct mkroom*)0)->ly)),
SOUNDS_META(room_hy,offsetof(struct mkroom,hy)),
SOUNDS_META(room_hy_size,sizeof(((struct mkroom*)0)->hy)),
SOUNDS_META(room_rtype,offsetof(struct mkroom,rtype)),
SOUNDS_META(room_rtype_size,sizeof(((struct mkroom*)0)->rtype)),
SOUNDS_META(coordSize,sizeof(coord)),
SOUNDS_META(coord_x,offsetof(coord,x)),
SOUNDS_META(coord_x_size,sizeof(((coord*)0)->x)),
SOUNDS_META(coord_y,offsetof(coord,y)),
SOUNDS_META(coord_y_size,sizeof(((coord*)0)->y)),
SOUNDS_META(levelSize,sizeof(d_level)),
SOUNDS_META(level_dnum,offsetof(d_level,dnum)),
SOUNDS_META(level_dnum_size,sizeof(((d_level*)0)->dnum)),
SOUNDS_META(level_dlevel,offsetof(d_level,dlevel)),
SOUNDS_META(level_dlevel_size,sizeof(((d_level*)0)->dlevel)),
SOUNDS_META(uSize,sizeof(struct you)),
SOUNDS_META(u_ux,offsetof(struct you,ux)),
SOUNDS_META(u_ux_size,sizeof(((struct you*)0)->ux)),
SOUNDS_META(u_uy,offsetof(struct you,uy)),
SOUNDS_META(u_uy_size,sizeof(((struct you*)0)->uy)),
SOUNDS_META(u_dx,offsetof(struct you,dx)),
SOUNDS_META(u_dx_size,sizeof(((struct you*)0)->dx)),
SOUNDS_META(u_dy,offsetof(struct you,dy)),
SOUNDS_META(u_dy_size,sizeof(((struct you*)0)->dy)),
SOUNDS_META(u_dz,offsetof(struct you,dz)),
SOUNDS_META(u_dz_size,sizeof(((struct you*)0)->dz)),
SOUNDS_META(u_umonnum,offsetof(struct you,umonnum)),
SOUNDS_META(u_umonnum_size,sizeof(((struct you*)0)->umonnum)),
SOUNDS_META(u_umonster,offsetof(struct you,umonster)),
SOUNDS_META(u_umonster_size,sizeof(((struct you*)0)->umonster)),
SOUNDS_META(u_usteed,offsetof(struct you,usteed)),
SOUNDS_META(u_usteed_size,sizeof(((struct you*)0)->usteed)),
SOUNDS_META(u_uz,offsetof(struct you,uz)),
SOUNDS_META(u_uz_size,sizeof(((struct you*)0)->uz)),
SOUNDS_META(u_uprops,offsetof(struct you,uprops)),
SOUNDS_META(u_uprops_size,sizeof(((struct you*)0)->uprops)),
SOUNDS_META(u_urooms,offsetof(struct you,urooms)),
SOUNDS_META(u_urooms_size,sizeof(((struct you*)0)->urooms)),
SOUNDS_META(u_ushops,offsetof(struct you,ushops)),
SOUNDS_META(u_ushops_size,sizeof(((struct you*)0)->ushops)),
SOUNDS_META(propSize,sizeof(struct prop)),
SOUNDS_META(prop_intrinsic,offsetof(struct prop,intrinsic)),
SOUNDS_META(prop_intrinsic_size,sizeof(((struct prop*)0)->intrinsic)),
SOUNDS_META(prop_extrinsic,offsetof(struct prop,extrinsic)),
SOUNDS_META(prop_extrinsic_size,sizeof(((struct prop*)0)->extrinsic)),
SOUNDS_META(prop_blocked,offsetof(struct prop,blocked)),
SOUNDS_META(prop_blocked_size,sizeof(((struct prop*)0)->blocked)),
SOUNDS_META(soundSize,sizeof(struct sound_procs)),
SOUNDS_META(sound_soundname,offsetof(struct sound_procs,soundname)),
SOUNDS_META(sound_soundname_size,sizeof(((struct sound_procs*)0)->soundname)),
SOUNDS_META(sound_soundlib_id,offsetof(struct sound_procs,soundlib_id)),
SOUNDS_META(sound_soundlib_id_size,sizeof(((struct sound_procs*)0)->soundlib_id)),
SOUNDS_META(sound_sound_triggers,offsetof(struct sound_procs,sound_triggers)),
SOUNDS_META(sound_sound_triggers_size,sizeof(((struct sound_procs*)0)->sound_triggers)),
SOUNDS_META(sound_sound_init_nhsound,offsetof(struct sound_procs,sound_init_nhsound)),
SOUNDS_META(sound_sound_init_nhsound_size,sizeof(((struct sound_procs*)0)->sound_init_nhsound)),
SOUNDS_META(sound_sound_exit_nhsound,offsetof(struct sound_procs,sound_exit_nhsound)),
SOUNDS_META(sound_sound_exit_nhsound_size,sizeof(((struct sound_procs*)0)->sound_exit_nhsound)),
SOUNDS_META(sound_sound_achievement,offsetof(struct sound_procs,sound_achievement)),
SOUNDS_META(sound_sound_achievement_size,sizeof(((struct sound_procs*)0)->sound_achievement)),
SOUNDS_META(sound_sound_soundeffect,offsetof(struct sound_procs,sound_soundeffect)),
SOUNDS_META(sound_sound_soundeffect_size,sizeof(((struct sound_procs*)0)->sound_soundeffect)),
SOUNDS_META(sound_sound_hero_playnotes,offsetof(struct sound_procs,sound_hero_playnotes)),
SOUNDS_META(sound_sound_hero_playnotes_size,sizeof(((struct sound_procs*)0)->sound_hero_playnotes)),
SOUNDS_META(sound_sound_play_usersound,offsetof(struct sound_procs,sound_play_usersound)),
SOUNDS_META(sound_sound_play_usersound_size,sizeof(((struct sound_procs*)0)->sound_play_usersound)),
SOUNDS_META(sound_sound_ambience,offsetof(struct sound_procs,sound_ambience)),
SOUNDS_META(sound_sound_ambience_size,sizeof(((struct sound_procs*)0)->sound_ambience)),
SOUNDS_META(sound_sound_verbal,offsetof(struct sound_procs,sound_verbal)),
SOUNDS_META(sound_sound_verbal_size,sizeof(((struct sound_procs*)0)->sound_verbal)),
SOUNDS_META(genderSize,sizeof(struct Gender)),
SOUNDS_META(gender_his,offsetof(struct Gender,his)),
SOUNDS_META(gender_his_size,sizeof(((struct Gender*)0)->his)),
SOUNDS_META(terrainSize,sizeof(struct rm)),
SOUNDS_META(terrain_typ,offsetof(struct rm,typ)),
SOUNDS_META(terrain_typ_size,sizeof(((struct rm*)0)->typ)),
SOUNDS_META(clsSize,sizeof(struct objclass)),
SOUNDS_META(cls_oc_skill,offsetof(struct objclass,oc_skill)),
SOUNDS_META(cls_oc_skill_size,sizeof(((struct objclass*)0)->oc_skill)),
SOUNDS_META(terrain,offsetof(__typeof__(svl),level.locations)),
SOUNDS_META(terrain_size,sizeof(svl.level.locations)),
SOUNDS_META(rooms,offsetof(__typeof__(svr),rooms)),
SOUNDS_META(rooms_size,sizeof(svr.rooms)),
SOUNDS_META(floorMonsters,offsetof(__typeof__(svl),level.monsters)),
SOUNDS_META(floorMonsters_size,sizeof(svl.level.monsters)),
SOUNDS_META(floorObjects,offsetof(__typeof__(svl),level.objects)),
SOUNDS_META(floorObjects_size,sizeof(svl.level.objects)),
SOUNDS_META(lastseentyp,offsetof(__typeof__(svl),lastseentyp)),
SOUNDS_META(lastseentyp_size,sizeof(svl.lastseentyp)),
SOUNDS_META(context_run,offsetof(__typeof__(svc),context.run)),
SOUNDS_META(context_run_size,sizeof(svc.context.run)),
SOUNDS_META(leader_m_id,offsetof(__typeof__(svq),quest_status.leader_m_id)),
SOUNDS_META(leader_m_id_size,sizeof(svq.quest_status.leader_m_id)),
SOUNDS_META(guardnum,offsetof(__typeof__(gu),urole.guardnum)),
SOUNDS_META(guardnum_size,sizeof(gu.urole.guardnum)),
SOUNDS_META(mnum,offsetof(__typeof__(gu),urole.mnum)),
SOUNDS_META(mnum_size,sizeof(gu.urole.mnum)),
SOUNDS_META(race_mnum,offsetof(__typeof__(gu),urace.mnum)),
SOUNDS_META(race_mnum_size,sizeof(gu.urace.mnum)),
SOUNDS_META(race_f,offsetof(__typeof__(gu),urace.individual.f)),
SOUNDS_META(race_f_size,sizeof(gu.urace.individual.f)),
SOUNDS_META(race_m,offsetof(__typeof__(gu),urace.individual.m)),
SOUNDS_META(race_m_size,sizeof(gu.urace.individual.m)),
SOUNDS_META(race_noun,offsetof(__typeof__(gu),urace.noun)),
SOUNDS_META(race_noun_size,sizeof(gu.urace.noun)),
SOUNDS_META(youmonst,offsetof(__typeof__(gy),youmonst)),
SOUNDS_META(youmonst_size,sizeof(gy.youmonst)),
SOUNDS_META(invent,offsetof(__typeof__(gi),invent)),
SOUNDS_META(invent_size,sizeof(gi.invent)),
SOUNDS_META(active_soundlib,offsetof(__typeof__(ga),active_soundlib)),
SOUNDS_META(active_soundlib_size,sizeof(ga.active_soundlib)),
SOUNDS_META(chosen_soundlib,offsetof(__typeof__(gc),chosen_soundlib)),
SOUNDS_META(chosen_soundlib_size,sizeof(gc.chosen_soundlib)),
SOUNDS_META(nomovemsg,offsetof(__typeof__(gn),nomovemsg)),
SOUNDS_META(nomovemsg_size,sizeof(gn.nomovemsg)),
SOUNDS_META(multi_reason,offsetof(__typeof__(gm),multi_reason)),
SOUNDS_META(multi_reason_size,sizeof(gm.multi_reason)),
SOUNDS_META(female,offsetof(__typeof__(flags),female)),
SOUNDS_META(female_size,sizeof(flags.female)),
SOUNDS_META(acoustics,offsetof(__typeof__(flags),acoustics)),
SOUNDS_META(acoustics_size,sizeof(flags.acoustics)),
SOUNDS_META(moonphase,offsetof(__typeof__(flags),moonphase)),
SOUNDS_META(moonphase_size,sizeof(flags.moonphase)),
SOUNDS_META(last_msg,offsetof(__typeof__(iflags),last_msg)),
SOUNDS_META(last_msg_size,sizeof(iflags.last_msg)),
SOUNDS_META(astral,offsetof(__typeof__(svd),dungeon_topology.d_astral_level)),
SOUNDS_META(astral_size,sizeof(svd.dungeon_topology.d_astral_level)),
SOUNDS_META(sanctum,offsetof(__typeof__(svd),dungeon_topology.d_sanctum_level)),
SOUNDS_META(sanctum_size,sizeof(svd.dungeon_topology.d_sanctum_level)),
SOUNDS_META(oracle,offsetof(__typeof__(svd),dungeon_topology.d_oracle_level)),
SOUNDS_META(oracle_size,sizeof(svd.dungeon_topology.d_oracle_level)),
SOUNDS_META(sysopt_seduce,offsetof(__typeof__(sysopt),seduce)),
SOUNDS_META(sysopt_seduce_size,sizeof(sysopt.seduce)),
SOUNDS_META(moves,offsetof(__typeof__(svm),moves)),
SOUNDS_META(moves_size,sizeof(svm.moves)),
SOUNDS_META(viz_array,offsetof(__typeof__(gv),viz_array)),
SOUNDS_META(viz_array_size,sizeof(gv.viz_array)),
SOUNDS_META(fmon,offsetof(__typeof__(svl),level.monlist)),
SOUNDS_META(fmon_size,sizeof(svl.level.monlist)),
SOUNDS_META(ANY_SHOP,ANY_SHOP),
SOUNDS_META(A_LAWFUL,A_LAWFUL),
SOUNDS_META(BARRACKS,BARRACKS),
SOUNDS_META(BEEHIVE,BEEHIVE),
SOUNDS_META(BLINDED,BLINDED),
SOUNDS_META(BLOOD,BLOOD),
SOUNDS_META(BOLT_LIM,BOLT_LIM),
SOUNDS_META(BUFSZ,BUFSZ),
SOUNDS_META(CONFLICT,CONFLICT),
SOUNDS_META(COULD_SEE,COULD_SEE),
SOUNDS_META(COURT,COURT),
SOUNDS_META(DBWALL,DBWALL),
SOUNDS_META(DEAF,DEAF),
SOUNDS_META(ECMD_CANCEL,ECMD_CANCEL),
SOUNDS_META(ECMD_OK,ECMD_OK),
SOUNDS_META(ECMD_TIME,ECMD_TIME),
SOUNDS_META(FEMALE,FEMALE),
SOUNDS_META(FULL_MOON,FULL_MOON),
SOUNDS_META(GLYPH_DETECT_FEM_OFF,GLYPH_DETECT_FEM_OFF),
SOUNDS_META(GLYPH_DETECT_MALE_OFF,GLYPH_DETECT_MALE_OFF),
SOUNDS_META(GLYPH_INVISIBLE,GLYPH_INVISIBLE),
SOUNDS_META(GLYPH_MON_FEM_OFF,GLYPH_MON_FEM_OFF),
SOUNDS_META(GLYPH_MON_MALE_OFF,GLYPH_MON_MALE_OFF),
SOUNDS_META(GLYPH_MON_OFF,GLYPH_MON_OFF),
SOUNDS_META(GLYPH_PET_FEM_OFF,GLYPH_PET_FEM_OFF),
SOUNDS_META(GLYPH_PET_MALE_OFF,GLYPH_PET_MALE_OFF),
SOUNDS_META(GLYPH_RIDDEN_FEM_OFF,GLYPH_RIDDEN_FEM_OFF),
SOUNDS_META(GLYPH_RIDDEN_MALE_OFF,GLYPH_RIDDEN_MALE_OFF),
SOUNDS_META(GLYPH_STATUE_FEM_OFF,GLYPH_STATUE_FEM_OFF),
SOUNDS_META(GLYPH_STATUE_FEM_PILETOP_OFF,GLYPH_STATUE_FEM_PILETOP_OFF),
SOUNDS_META(GLYPH_STATUE_MALE_OFF,GLYPH_STATUE_MALE_OFF),
SOUNDS_META(GLYPH_STATUE_MALE_PILETOP_OFF,GLYPH_STATUE_MALE_PILETOP_OFF),
SOUNDS_META(HAIR,HAIR),
SOUNDS_META(HALLUC,HALLUC),
SOUNDS_META(HALLUC_RES,HALLUC_RES),
SOUNDS_META(HEAD,HEAD),
SOUNDS_META(HELMET,HELMET),
SOUNDS_META(INVIS,INVIS),
SOUNDS_META(IN_SIGHT,IN_SIGHT),
SOUNDS_META(IRONBARS,IRONBARS),
SOUNDS_META(M1_ANIMAL,M1_ANIMAL),
SOUNDS_META(M1_CARNIVORE,M1_CARNIVORE),
SOUNDS_META(M1_FLY,M1_FLY),
SOUNDS_META(M1_HERBIVORE,M1_HERBIVORE),
SOUNDS_META(M1_HUMANOID,M1_HUMANOID),
SOUNDS_META(M1_NOEYES,M1_NOEYES),
SOUNDS_META(M1_SEE_INVIS,M1_SEE_INVIS),
SOUNDS_META(M2_DWARF,M2_DWARF),
SOUNDS_META(M2_ELF,M2_ELF),
SOUNDS_META(M2_GNOME,M2_GNOME),
SOUNDS_META(M2_LORD,M2_LORD),
SOUNDS_META(M2_MAGIC,M2_MAGIC),
SOUNDS_META(M2_MERC,M2_MERC),
SOUNDS_META(M2_MINION,M2_MINION),
SOUNDS_META(M2_PRINCE,M2_PRINCE),
SOUNDS_META(M2_UNDEAD,M2_UNDEAD),
SOUNDS_META(MALE,MALE),
SOUNDS_META(MORGUE,MORGUE),
SOUNDS_META(MS_ANIMAL,MS_ANIMAL),
SOUNDS_META(MS_ARREST,MS_ARREST),
SOUNDS_META(MS_BARK,MS_BARK),
SOUNDS_META(MS_BELLOW,MS_BELLOW),
SOUNDS_META(MS_BOAST,MS_BOAST),
SOUNDS_META(MS_BONES,MS_BONES),
SOUNDS_META(MS_BRIBE,MS_BRIBE),
SOUNDS_META(MS_BURBLE,MS_BURBLE),
SOUNDS_META(MS_BUZZ,MS_BUZZ),
SOUNDS_META(MS_CHIRP,MS_CHIRP),
SOUNDS_META(MS_CUSS,MS_CUSS),
SOUNDS_META(MS_DJINNI,MS_DJINNI),
SOUNDS_META(MS_GROAN,MS_GROAN),
SOUNDS_META(MS_GROWL,MS_GROWL),
SOUNDS_META(MS_GRUNT,MS_GRUNT),
SOUNDS_META(MS_GUARD,MS_GUARD),
SOUNDS_META(MS_GUARDIAN,MS_GUARDIAN),
SOUNDS_META(MS_GURGLE,MS_GURGLE),
SOUNDS_META(MS_HISS,MS_HISS),
SOUNDS_META(MS_HUMANOID,MS_HUMANOID),
SOUNDS_META(MS_IMITATE,MS_IMITATE),
SOUNDS_META(MS_LAUGH,MS_LAUGH),
SOUNDS_META(MS_LEADER,MS_LEADER),
SOUNDS_META(MS_MEW,MS_MEW),
SOUNDS_META(MS_MOO,MS_MOO),
SOUNDS_META(MS_MUMBLE,MS_MUMBLE),
SOUNDS_META(MS_NEIGH,MS_NEIGH),
SOUNDS_META(MS_NEMESIS,MS_NEMESIS),
SOUNDS_META(MS_NURSE,MS_NURSE),
SOUNDS_META(MS_ORACLE,MS_ORACLE),
SOUNDS_META(MS_ORC,MS_ORC),
SOUNDS_META(MS_PRIEST,MS_PRIEST),
SOUNDS_META(MS_RIDER,MS_RIDER),
SOUNDS_META(MS_ROAR,MS_ROAR),
SOUNDS_META(MS_SEDUCE,MS_SEDUCE),
SOUNDS_META(MS_SELL,MS_SELL),
SOUNDS_META(MS_SHRIEK,MS_SHRIEK),
SOUNDS_META(MS_SILENT,MS_SILENT),
SOUNDS_META(MS_SOLDIER,MS_SOLDIER),
SOUNDS_META(MS_SPELL,MS_SPELL),
SOUNDS_META(MS_SQAWK,MS_SQAWK),
SOUNDS_META(MS_SQEEK,MS_SQEEK),
SOUNDS_META(MS_TRUMPET,MS_TRUMPET),
SOUNDS_META(MS_VAMPIRE,MS_VAMPIRE),
SOUNDS_META(MS_WAIL,MS_WAIL),
SOUNDS_META(MS_WERE,MS_WERE),
SOUNDS_META(M_AP_FURNITURE,M_AP_FURNITURE),
SOUNDS_META(M_AP_OBJECT,M_AP_OBJECT),
SOUNDS_META(M_AP_TYPMASK,M_AP_TYPMASK),
SOUNDS_META(NECK,NECK),
SOUNDS_META(NUMMONS,NUMMONS),
SOUNDS_META(NUM_OBJECTS,NUM_OBJECTS),
SOUNDS_META(OROOM,OROOM),
SOUNDS_META(PLNMSG_GROWL,PLNMSG_GROWL),
SOUNDS_META(PM_ALIGNED_CLERIC,PM_ALIGNED_CLERIC),
SOUNDS_META(PM_ARCHEOLOGIST,PM_ARCHEOLOGIST),
SOUNDS_META(PM_BABY_SILVER_DRAGON,PM_BABY_SILVER_DRAGON),
SOUNDS_META(PM_DEATH,PM_DEATH),
SOUNDS_META(PM_DINGO,PM_DINGO),
SOUNDS_META(PM_DOG,PM_DOG),
SOUNDS_META(PM_ELF,PM_ELF),
SOUNDS_META(PM_GECKO,PM_GECKO),
SOUNDS_META(PM_GHOST,PM_GHOST),
SOUNDS_META(PM_GIANT,PM_GIANT),
SOUNDS_META(PM_GNOME,PM_GNOME),
SOUNDS_META(PM_HEALER,PM_HEALER),
SOUNDS_META(PM_HOBBIT,PM_HOBBIT),
SOUNDS_META(PM_HUMAN,PM_HUMAN),
SOUNDS_META(PM_HUMAN_WERERAT,PM_HUMAN_WERERAT),
SOUNDS_META(PM_KILLER_BEE,PM_KILLER_BEE),
SOUNDS_META(PM_LEPRECHAUN,PM_LEPRECHAUN),
SOUNDS_META(PM_LONG_WORM,PM_LONG_WORM),
SOUNDS_META(PM_NURSE,PM_NURSE),
SOUNDS_META(PM_ORACLE,PM_ORACLE),
SOUNDS_META(PM_PRISONER,PM_PRISONER),
SOUNDS_META(PM_RAVEN,PM_RAVEN),
SOUNDS_META(PM_SILVER_DRAGON,PM_SILVER_DRAGON),
SOUNDS_META(PM_SOLDIER,PM_SOLDIER),
SOUNDS_META(PM_TOURIST,PM_TOURIST),
SOUNDS_META(PM_VAMPIRE,PM_VAMPIRE),
SOUNDS_META(PM_VAMPIRE_LEADER,PM_VAMPIRE_LEADER),
SOUNDS_META(PM_VLAD_THE_IMPALER,PM_VLAD_THE_IMPALER),
SOUNDS_META(PM_WATCHMAN,PM_WATCHMAN),
SOUNDS_META(PM_WATER_DEMON,PM_WATER_DEMON),
SOUNDS_META(PM_WINTER_WOLF,PM_WINTER_WOLF),
SOUNDS_META(PM_WINTER_WOLF_CUB,PM_WINTER_WOLF_CUB),
SOUNDS_META(PM_WIZARD,PM_WIZARD),
SOUNDS_META(PM_WOLF,PM_WOLF),
SOUNDS_META(PRONOUN_HALLU,PRONOUN_HALLU),
SOUNDS_META(P_NONE,P_NONE),
SOUNDS_META(ROOM,ROOM),
SOUNDS_META(ROOMOFFSET,ROOMOFFSET),
SOUNDS_META(ROWNO,ROWNO),
SOUNDS_META(SDOOR,SDOOR),
SOUNDS_META(SHOPBASE,SHOPBASE),
SOUNDS_META(STATUE,STATUE),
SOUNDS_META(STRANGLED,STRANGLED),
SOUNDS_META(STRAT_WAITMASK,STRAT_WAITMASK),
SOUNDS_META(SWAMP,SWAMP),
SOUNDS_META(S_ANT,S_ANT),
SOUNDS_META(S_CENTAUR,S_CENTAUR),
SOUNDS_META(S_EEL,S_EEL),
SOUNDS_META(S_GHOST,S_GHOST),
SOUNDS_META(S_HUMAN,S_HUMAN),
SOUNDS_META(S_NYMPH,S_NYMPH),
SOUNDS_META(TEMPLE,TEMPLE),
SOUNDS_META(TOOL_CLASS,TOOL_CLASS),
SOUNDS_META(VAULT,VAULT),
SOUNDS_META(WEAPON_CLASS,WEAPON_CLASS),
SOUNDS_META(W_ARMH,W_ARMH),
SOUNDS_META(ZOO,ZOO),
SOUNDS_META(se_avian_screak,se_avian_screak),
SOUNDS_META(se_canine_whine,se_canine_whine),
SOUNDS_META(se_canine_yelp,se_canine_yelp),
SOUNDS_META(se_feline_yelp,se_feline_yelp),
SOUNDS_META(se_squeal,se_squeal),
SOUNDS_META(se_wail,se_wail),
SOUNDS_META(se_yelp,se_yelp),
SOUNDS_META(sff_base_only,sff_base_only),
SOUNDS_META(sff_baseknown_add_rest,sff_baseknown_add_rest),
SOUNDS_META(sff_havedir_append_rest,sff_havedir_append_rest),
SOUNDS_META(soundlib_nosound,soundlib_nosound),
};
#undef SOUNDS_META
_Static_assert(sizeof(((struct monst*)0)->data)==8,"mon_data width");
_Static_assert(sizeof(((struct monst*)0)->nmon)==8,"mon_nmon width");
_Static_assert(sizeof(((struct monst*)0)->mextra)==8,"mon_mextra width");
_Static_assert(sizeof(((struct monst*)0)->m_id)==4,"mon_m_id width");
_Static_assert(((__typeof__(((struct monst*)0)->m_id))-1 > 0),"mon_m_id signedness");
_Static_assert(sizeof(((struct monst*)0)->mtame)==1,"mon_mtame width");
_Static_assert(((__typeof__(((struct monst*)0)->mtame))-1 < 0),"mon_mtame signedness");
_Static_assert(sizeof(((struct monst*)0)->mx)==2,"mon_mx width");
_Static_assert(((__typeof__(((struct monst*)0)->mx))-1 < 0),"mon_mx signedness");
_Static_assert(sizeof(((struct monst*)0)->my)==2,"mon_my width");
_Static_assert(((__typeof__(((struct monst*)0)->my))-1 < 0),"mon_my signedness");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4,"mon_mhp width");
_Static_assert(((__typeof__(((struct monst*)0)->mhp))-1 < 0),"mon_mhp signedness");
_Static_assert(sizeof(((struct monst*)0)->mhpmax)==4,"mon_mhpmax width");
_Static_assert(((__typeof__(((struct monst*)0)->mhpmax))-1 < 0),"mon_mhpmax signedness");
_Static_assert(sizeof(((struct monst*)0)->meating)==4,"mon_meating width");
_Static_assert(((__typeof__(((struct monst*)0)->meating))-1 < 0),"mon_meating signedness");
_Static_assert(sizeof(((struct monst*)0)->mstrategy)==8,"mon_mstrategy width");
_Static_assert(((__typeof__(((struct monst*)0)->mstrategy))-1 > 0),"mon_mstrategy signedness");
_Static_assert(sizeof(((struct monst*)0)->m_ap_type)==1,"mon_m_ap_type width");
_Static_assert(((__typeof__(((struct monst*)0)->m_ap_type))-1 > 0),"mon_m_ap_type signedness");
_Static_assert(sizeof(((struct monst*)0)->cham)==2,"mon_cham width");
_Static_assert(((__typeof__(((struct monst*)0)->cham))-1 < 0),"mon_cham signedness");
_Static_assert(sizeof(((struct permonst*)0)->msound)==1,"pm_msound width");
_Static_assert(((__typeof__(((struct permonst*)0)->msound))-1 > 0),"pm_msound signedness");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1,"pm_mlet width");
_Static_assert(((__typeof__(((struct permonst*)0)->mlet))-1 < 0),"pm_mlet signedness");
_Static_assert(sizeof(((struct permonst*)0)->mlevel)==1,"pm_mlevel width");
_Static_assert(((__typeof__(((struct permonst*)0)->mlevel))-1 < 0),"pm_mlevel signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8,"pm_mflags1 width");
_Static_assert(((__typeof__(((struct permonst*)0)->mflags1))-1 > 0),"pm_mflags1 signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8,"pm_mflags2 width");
_Static_assert(((__typeof__(((struct permonst*)0)->mflags2))-1 > 0),"pm_mflags2 signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags3)==2,"pm_mflags3 width");
_Static_assert(((__typeof__(((struct permonst*)0)->mflags3))-1 > 0),"pm_mflags3 signedness");
_Static_assert(sizeof(((struct permonst*)0)->pmidx)==4,"pm_pmidx width");
_Static_assert(((__typeof__(((struct permonst*)0)->pmidx))-1 < 0),"pm_pmidx signedness");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2,"obj_otyp width");
_Static_assert(((__typeof__(((struct obj*)0)->otyp))-1 < 0),"obj_otyp signedness");
_Static_assert(sizeof(((struct obj*)0)->oclass)==1,"obj_oclass width");
_Static_assert(((__typeof__(((struct obj*)0)->oclass))-1 < 0),"obj_oclass signedness");
_Static_assert(sizeof(((struct obj*)0)->novelidx)==4,"obj_novelidx width");
_Static_assert(((__typeof__(((struct obj*)0)->novelidx))-1 < 0),"obj_novelidx signedness");
_Static_assert(sizeof(((struct mextra*)0)->epri)==8,"extra_epri width");
_Static_assert(sizeof(((struct mextra*)0)->emin)==8,"extra_emin width");
_Static_assert(sizeof(((struct mextra*)0)->edog)==8,"extra_edog width");
_Static_assert(sizeof(((struct edog*)0)->hungrytime)==8,"edog_hungrytime width");
_Static_assert(((__typeof__(((struct edog*)0)->hungrytime))-1 < 0),"edog_hungrytime signedness");
_Static_assert(sizeof(((struct epri*)0)->shroom)==1,"epri_shroom width");
_Static_assert(((__typeof__(((struct epri*)0)->shroom))-1 < 0),"epri_shroom signedness");
_Static_assert(sizeof(((struct epri*)0)->shralign)==1,"epri_shralign width");
_Static_assert(((__typeof__(((struct epri*)0)->shralign))-1 < 0),"epri_shralign signedness");
_Static_assert(sizeof(((struct emin*)0)->renegade)==1,"emin_renegade width");
_Static_assert(((__typeof__(((struct emin*)0)->renegade))-1 < 0),"emin_renegade signedness");
_Static_assert(sizeof(((struct mkroom*)0)->lx)==2,"room_lx width");
_Static_assert(((__typeof__(((struct mkroom*)0)->lx))-1 < 0),"room_lx signedness");
_Static_assert(sizeof(((struct mkroom*)0)->hx)==2,"room_hx width");
_Static_assert(((__typeof__(((struct mkroom*)0)->hx))-1 < 0),"room_hx signedness");
_Static_assert(sizeof(((struct mkroom*)0)->ly)==2,"room_ly width");
_Static_assert(((__typeof__(((struct mkroom*)0)->ly))-1 < 0),"room_ly signedness");
_Static_assert(sizeof(((struct mkroom*)0)->hy)==2,"room_hy width");
_Static_assert(((__typeof__(((struct mkroom*)0)->hy))-1 < 0),"room_hy signedness");
_Static_assert(sizeof(((struct mkroom*)0)->rtype)==1,"room_rtype width");
_Static_assert(((__typeof__(((struct mkroom*)0)->rtype))-1 < 0),"room_rtype signedness");
_Static_assert(sizeof(((coord*)0)->x)==2,"coord_x width");
_Static_assert(((__typeof__(((coord*)0)->x))-1 < 0),"coord_x signedness");
_Static_assert(sizeof(((coord*)0)->y)==2,"coord_y width");
_Static_assert(((__typeof__(((coord*)0)->y))-1 < 0),"coord_y signedness");
_Static_assert(sizeof(((d_level*)0)->dnum)==2,"level_dnum width");
_Static_assert(((__typeof__(((d_level*)0)->dnum))-1 < 0),"level_dnum signedness");
_Static_assert(sizeof(((d_level*)0)->dlevel)==2,"level_dlevel width");
_Static_assert(((__typeof__(((d_level*)0)->dlevel))-1 < 0),"level_dlevel signedness");
_Static_assert(sizeof(((struct you*)0)->ux)==2,"u_ux width");
_Static_assert(((__typeof__(((struct you*)0)->ux))-1 < 0),"u_ux signedness");
_Static_assert(sizeof(((struct you*)0)->uy)==2,"u_uy width");
_Static_assert(((__typeof__(((struct you*)0)->uy))-1 < 0),"u_uy signedness");
_Static_assert(sizeof(((struct you*)0)->dx)==4,"u_dx width");
_Static_assert(((__typeof__(((struct you*)0)->dx))-1 < 0),"u_dx signedness");
_Static_assert(sizeof(((struct you*)0)->dy)==4,"u_dy width");
_Static_assert(((__typeof__(((struct you*)0)->dy))-1 < 0),"u_dy signedness");
_Static_assert(sizeof(((struct you*)0)->dz)==4,"u_dz width");
_Static_assert(((__typeof__(((struct you*)0)->dz))-1 < 0),"u_dz signedness");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4,"u_umonnum width");
_Static_assert(((__typeof__(((struct you*)0)->umonnum))-1 < 0),"u_umonnum signedness");
_Static_assert(sizeof(((struct you*)0)->umonster)==4,"u_umonster width");
_Static_assert(((__typeof__(((struct you*)0)->umonster))-1 < 0),"u_umonster signedness");
_Static_assert(sizeof(((struct you*)0)->usteed)==8,"u_usteed width");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8,"prop_intrinsic width");
_Static_assert(((__typeof__(((struct prop*)0)->intrinsic))-1 < 0),"prop_intrinsic signedness");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8,"prop_extrinsic width");
_Static_assert(((__typeof__(((struct prop*)0)->extrinsic))-1 < 0),"prop_extrinsic signedness");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8,"prop_blocked width");
_Static_assert(((__typeof__(((struct prop*)0)->blocked))-1 < 0),"prop_blocked signedness");
_Static_assert(sizeof(((struct sound_procs*)0)->soundname)==8,"sound_soundname width");
_Static_assert(sizeof(((struct sound_procs*)0)->soundlib_id)==4,"sound_soundlib_id width");
_Static_assert(((__typeof__(((struct sound_procs*)0)->soundlib_id))-1 > 0),"sound_soundlib_id signedness");
_Static_assert(sizeof(((struct sound_procs*)0)->sound_triggers)==8,"sound_sound_triggers width");
_Static_assert(((__typeof__(((struct sound_procs*)0)->sound_triggers))-1 > 0),"sound_sound_triggers signedness");
_Static_assert(sizeof(((struct sound_procs*)0)->sound_init_nhsound)==8,"sound_sound_init_nhsound width");
_Static_assert(sizeof(((struct sound_procs*)0)->sound_exit_nhsound)==8,"sound_sound_exit_nhsound width");
_Static_assert(sizeof(((struct sound_procs*)0)->sound_achievement)==8,"sound_sound_achievement width");
_Static_assert(sizeof(((struct sound_procs*)0)->sound_soundeffect)==8,"sound_sound_soundeffect width");
_Static_assert(sizeof(((struct sound_procs*)0)->sound_hero_playnotes)==8,"sound_sound_hero_playnotes width");
_Static_assert(sizeof(((struct sound_procs*)0)->sound_play_usersound)==8,"sound_sound_play_usersound width");
_Static_assert(sizeof(((struct sound_procs*)0)->sound_ambience)==8,"sound_sound_ambience width");
_Static_assert(sizeof(((struct sound_procs*)0)->sound_verbal)==8,"sound_sound_verbal width");
_Static_assert(sizeof(((struct Gender*)0)->his)==8,"gender_his width");
_Static_assert(sizeof(((struct rm*)0)->typ)==1,"terrain_typ width");
_Static_assert(((__typeof__(((struct rm*)0)->typ))-1 < 0),"terrain_typ signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_skill)==1,"cls_oc_skill width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_skill))-1 < 0),"cls_oc_skill signedness");
// Independent guards for global scalar views used by sounds-runtime.js.
_Static_assert(sizeof(svc.context.run)==4,"svc.context.run width");
_Static_assert(((__typeof__(svc.context.run))-1 > 0),"svc.context.run signedness");
_Static_assert(sizeof(svq.quest_status.leader_m_id)==4,"svq.quest_status.leader_m_id width");
_Static_assert(((__typeof__(svq.quest_status.leader_m_id))-1 > 0),"svq.quest_status.leader_m_id signedness");
_Static_assert(sizeof(gu.urole.guardnum)==2,"gu.urole.guardnum width");
_Static_assert(((__typeof__(gu.urole.guardnum))-1 < 0),"gu.urole.guardnum signedness");
_Static_assert(sizeof(gu.urole.mnum)==2,"gu.urole.mnum width");
_Static_assert(((__typeof__(gu.urole.mnum))-1 < 0),"gu.urole.mnum signedness");
_Static_assert(sizeof(gu.urace.mnum)==2,"gu.urace.mnum width");
_Static_assert(((__typeof__(gu.urace.mnum))-1 < 0),"gu.urace.mnum signedness");
_Static_assert(sizeof(ga.active_soundlib)==4,"ga.active_soundlib width");
_Static_assert(((__typeof__(ga.active_soundlib))-1 > 0),"ga.active_soundlib signedness");
_Static_assert(sizeof(gc.chosen_soundlib)==4,"gc.chosen_soundlib width");
_Static_assert(((__typeof__(gc.chosen_soundlib))-1 > 0),"gc.chosen_soundlib signedness");
_Static_assert(sizeof(flags.acoustics)==1,"flags.acoustics width");
_Static_assert(((__typeof__(flags.acoustics))-1 < 0),"flags.acoustics signedness");
_Static_assert(sizeof(flags.female)==1,"flags.female width");
_Static_assert(((__typeof__(flags.female))-1 < 0),"flags.female signedness");
_Static_assert(sizeof(flags.moonphase)==4,"flags.moonphase width");
_Static_assert(((__typeof__(flags.moonphase))-1 > 0),"flags.moonphase signedness");
_Static_assert(sizeof(iflags.last_msg)==4,"iflags.last_msg width");
_Static_assert(((__typeof__(iflags.last_msg))-1 < 0),"iflags.last_msg signedness");
_Static_assert(sizeof(svm.moves)==8,"svm.moves width");
_Static_assert(((__typeof__(svm.moves))-1 < 0),"svm.moves signedness");
_Static_assert(sizeof(sysopt.seduce)==4,"sysopt.seduce width");
_Static_assert(((__typeof__(sysopt.seduce))-1 < 0),"sysopt.seduce signedness");
_Static_assert(sizeof(svl.lastseentyp[0][0])==1,"svl.lastseentyp[0][0] width");
_Static_assert(((__typeof__(svl.lastseentyp[0][0]))-1 < 0),"svl.lastseentyp[0][0] signedness");
_Static_assert(sizeof(gu.urace.individual.f)==8,"gu.urace.individual.f pointer width");
_Static_assert(sizeof(gu.urace.individual.m)==8,"gu.urace.individual.m pointer width");
_Static_assert(sizeof(gu.urace.noun)==8,"gu.urace.noun pointer width");
_Static_assert(sizeof(gi.invent)==8,"gi.invent pointer width");
_Static_assert(sizeof(gn.nomovemsg)==8,"gn.nomovemsg pointer width");
_Static_assert(sizeof(gm.multi_reason)==8,"gm.multi_reason pointer width");
_Static_assert(sizeof(gv.viz_array)==8,"gv.viz_array pointer width");
_Static_assert(sizeof(svl.level.monlist)==8,"svl.level.monlist pointer width");
size_t probe_context_size(void){return sizeof(struct sound_procs);}
int probe_layout_count(void){return sizeof sounds_layout/sizeof sounds_layout[0];}
const char*probe_layout_name(int i){return sounds_layout[i].name;}
size_t probe_layout_value(int i){return sounds_layout[i].value;}
#endif
