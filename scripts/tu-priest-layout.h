#include "hack.h"
#include "mfndpos.h"
#include <stddef.h>
#define PRIEST_META(name,value) { #name, value }
static const struct { const char *name; size_t value; } priest_layout[] = {
    PRIEST_META(pointerSize, sizeof(void*)),
    PRIEST_META(longSize, sizeof(long)),
    PRIEST_META(intSize, sizeof(int)),
    PRIEST_META(charSize, sizeof(char)),
    PRIEST_META(charSigned, (char)-1 < 0),
    PRIEST_META(booleanSize, sizeof(boolean)),
    PRIEST_META(booleanSigned, (boolean)-1 < 0),
    PRIEST_META(coordxySize, sizeof(coordxy)),
    PRIEST_META(coordxySigned, (coordxy)-1 < 0),
    PRIEST_META(monsterSize, sizeof(struct monst)),
    PRIEST_META(permonstSize, sizeof(struct permonst)),
    PRIEST_META(epriSize, sizeof(struct epri)),
    PRIEST_META(eminSize, sizeof(struct emin)),
    PRIEST_META(eshkSize, sizeof(struct eshk)),
    PRIEST_META(roomSize, sizeof(struct mkroom)),
    PRIEST_META(coordSize, sizeof(coord)),
    PRIEST_META(levelSize, sizeof(d_level)),
    PRIEST_META(propSize, sizeof(struct prop)),
    PRIEST_META(terrainSize, sizeof(struct rm)),
    PRIEST_META(mvitalSize, sizeof(struct mvitals)),
    PRIEST_META(genderSize, sizeof(struct Gender)),
    PRIEST_META(mfndposSize, sizeof(struct mfndposdata)),
    PRIEST_META(mfndposCount, sizeof(((struct mfndposdata*)0)->poss)/sizeof(coord)),
    PRIEST_META(mon_nmon, offsetof(struct monst,nmon)),
    PRIEST_META(mon_nmon_size, sizeof(((struct monst*)0)->nmon)),
    PRIEST_META(mon_data, offsetof(struct monst,data)),
    PRIEST_META(mon_data_size, sizeof(((struct monst*)0)->data)),
    PRIEST_META(mon_m_id, offsetof(struct monst,m_id)),
    PRIEST_META(mon_m_id_size, sizeof(((struct monst*)0)->m_id)),
    PRIEST_META(mon_mx, offsetof(struct monst,mx)),
    PRIEST_META(mon_mx_size, sizeof(((struct monst*)0)->mx)),
    PRIEST_META(mon_my, offsetof(struct monst,my)),
    PRIEST_META(mon_my_size, sizeof(((struct monst*)0)->my)),
    PRIEST_META(mon_mhp, offsetof(struct monst,mhp)),
    PRIEST_META(mon_mhp_size, sizeof(((struct monst*)0)->mhp)),
    PRIEST_META(mon_mtame, offsetof(struct monst,mtame)),
    PRIEST_META(mon_mtame_size, sizeof(((struct monst*)0)->mtame)),
    PRIEST_META(mon_mextra, offsetof(struct monst,mextra)),
    PRIEST_META(mon_mextra_size, sizeof(((struct monst*)0)->mextra)),
    PRIEST_META(mon_minvent, offsetof(struct monst,minvent)),
    PRIEST_META(mon_minvent_size, sizeof(((struct monst*)0)->minvent)),
    PRIEST_META(pm_maligntyp, offsetof(struct permonst,maligntyp)),
    PRIEST_META(pm_maligntyp_size, sizeof(((struct permonst*)0)->maligntyp)),
    PRIEST_META(pm_mflags1, offsetof(struct permonst,mflags1)),
    PRIEST_META(pm_mflags1_size, sizeof(((struct permonst*)0)->mflags1)),
    PRIEST_META(pm_mflags2, offsetof(struct permonst,mflags2)),
    PRIEST_META(pm_mflags2_size, sizeof(((struct permonst*)0)->mflags2)),
    PRIEST_META(epri_parentmid, offsetof(struct epri,parentmid)),
    PRIEST_META(epri_parentmid_size, sizeof(((struct epri*)0)->parentmid)),
    PRIEST_META(epri_shralign, offsetof(struct epri,shralign)),
    PRIEST_META(epri_shralign_size, sizeof(((struct epri*)0)->shralign)),
    PRIEST_META(epri_shroom, offsetof(struct epri,shroom)),
    PRIEST_META(epri_shroom_size, sizeof(((struct epri*)0)->shroom)),
    PRIEST_META(epri_shrpos, offsetof(struct epri,shrpos)),
    PRIEST_META(epri_shrpos_size, sizeof(((struct epri*)0)->shrpos)),
    PRIEST_META(epri_shrlevel, offsetof(struct epri,shrlevel)),
    PRIEST_META(epri_shrlevel_size, sizeof(((struct epri*)0)->shrlevel)),
    PRIEST_META(epri_cheapskate_count, offsetof(struct epri,cheapskate_count)),
    PRIEST_META(epri_cheapskate_count_size, sizeof(((struct epri*)0)->cheapskate_count)),
    PRIEST_META(epri_intone_time, offsetof(struct epri,intone_time)),
    PRIEST_META(epri_intone_time_size, sizeof(((struct epri*)0)->intone_time)),
    PRIEST_META(epri_enter_time, offsetof(struct epri,enter_time)),
    PRIEST_META(epri_enter_time_size, sizeof(((struct epri*)0)->enter_time)),
    PRIEST_META(epri_hostile_time, offsetof(struct epri,hostile_time)),
    PRIEST_META(epri_hostile_time_size, sizeof(((struct epri*)0)->hostile_time)),
    PRIEST_META(epri_peaceful_time, offsetof(struct epri,peaceful_time)),
    PRIEST_META(epri_peaceful_time_size, sizeof(((struct epri*)0)->peaceful_time)),
    PRIEST_META(emin_min_align, offsetof(struct emin,min_align)),
    PRIEST_META(emin_min_align_size, sizeof(((struct emin*)0)->min_align)),
    PRIEST_META(emin_renegade, offsetof(struct emin,renegade)),
    PRIEST_META(emin_renegade_size, sizeof(((struct emin*)0)->renegade)),
    PRIEST_META(eshk_following, offsetof(struct eshk,following)),
    PRIEST_META(eshk_following_size, sizeof(((struct eshk*)0)->following)),
    PRIEST_META(mextra_epri, offsetof(struct mextra,epri)),
    PRIEST_META(mextra_epri_size, sizeof(((struct mextra*)0)->epri)),
    PRIEST_META(mextra_emin, offsetof(struct mextra,emin)),
    PRIEST_META(mextra_emin_size, sizeof(((struct mextra*)0)->emin)),
    PRIEST_META(mextra_eshk, offsetof(struct mextra,eshk)),
    PRIEST_META(mextra_eshk_size, sizeof(((struct mextra*)0)->eshk)),
    PRIEST_META(room_rtype, offsetof(struct mkroom,rtype)),
    PRIEST_META(room_rtype_size, sizeof(((struct mkroom*)0)->rtype)),
    PRIEST_META(room_lx, offsetof(struct mkroom,lx)),
    PRIEST_META(room_lx_size, sizeof(((struct mkroom*)0)->lx)),
    PRIEST_META(room_hx, offsetof(struct mkroom,hx)),
    PRIEST_META(room_hx_size, sizeof(((struct mkroom*)0)->hx)),
    PRIEST_META(room_ly, offsetof(struct mkroom,ly)),
    PRIEST_META(room_ly_size, sizeof(((struct mkroom*)0)->ly)),
    PRIEST_META(room_hy, offsetof(struct mkroom,hy)),
    PRIEST_META(room_hy_size, sizeof(((struct mkroom*)0)->hy)),
    PRIEST_META(coord_x, offsetof(coord,x)),
    PRIEST_META(coord_x_size, sizeof(((coord*)0)->x)),
    PRIEST_META(coord_y, offsetof(coord,y)),
    PRIEST_META(coord_y_size, sizeof(((coord*)0)->y)),
    PRIEST_META(level_dnum, offsetof(d_level,dnum)),
    PRIEST_META(level_dnum_size, sizeof(((d_level*)0)->dnum)),
    PRIEST_META(level_dlevel, offsetof(d_level,dlevel)),
    PRIEST_META(level_dlevel_size, sizeof(((d_level*)0)->dlevel)),
    PRIEST_META(prop_intrinsic, offsetof(struct prop,intrinsic)),
    PRIEST_META(prop_intrinsic_size, sizeof(((struct prop*)0)->intrinsic)),
    PRIEST_META(prop_extrinsic, offsetof(struct prop,extrinsic)),
    PRIEST_META(prop_extrinsic_size, sizeof(((struct prop*)0)->extrinsic)),
    PRIEST_META(prop_blocked, offsetof(struct prop,blocked)),
    PRIEST_META(prop_blocked_size, sizeof(((struct prop*)0)->blocked)),
    PRIEST_META(terrain_typ, offsetof(struct rm,typ)),
    PRIEST_META(terrain_typ_size, sizeof(((struct rm*)0)->typ)),
    PRIEST_META(mvital_born, offsetof(struct mvitals,born)),
    PRIEST_META(mvital_born_size, sizeof(((struct mvitals*)0)->born)),
    PRIEST_META(gender_his, offsetof(struct Gender,his)),
    PRIEST_META(gender_his_size, sizeof(((struct Gender*)0)->his)),
    PRIEST_META(mfp_cnt, offsetof(struct mfndposdata,cnt)),
    PRIEST_META(mfp_cnt_size, sizeof(((struct mfndposdata*)0)->cnt)),
    PRIEST_META(mfp_poss, offsetof(struct mfndposdata,poss)),
    PRIEST_META(mfp_poss_size, sizeof(((struct mfndposdata*)0)->poss)),
    PRIEST_META(mfp_info, offsetof(struct mfndposdata,info)),
    PRIEST_META(mfp_info_size, sizeof(((struct mfndposdata*)0)->info)),
    PRIEST_META(floorMonsters, offsetof(__typeof__(svl),level.monsters)),
    PRIEST_META(floorMonsters_size, sizeof svl.level.monsters),
    PRIEST_META(terrain, offsetof(__typeof__(svl),level.locations)),
    PRIEST_META(terrain_size, sizeof svl.level.locations),
    PRIEST_META(fmon, offsetof(__typeof__(svl),level.monlist)),
    PRIEST_META(fmon_size, sizeof svl.level.monlist),
    PRIEST_META(rooms, offsetof(__typeof__(svr),rooms)),
    PRIEST_META(rooms_size, sizeof svr.rooms),
    PRIEST_META(moves, offsetof(__typeof__(svm),moves)),
    PRIEST_META(moves_size, sizeof svm.moves),
    PRIEST_META(mvitals, offsetof(__typeof__(svm),mvitals)),
    PRIEST_META(mvitals_size, sizeof svm.mvitals),
    PRIEST_META(sanctumLevel, offsetof(__typeof__(svd),dungeon_topology.d_sanctum_level)),
    PRIEST_META(sanctumLevel_size, sizeof svd.dungeon_topology.d_sanctum_level),
    PRIEST_META(astralLevel, offsetof(__typeof__(svd),dungeon_topology.d_astral_level)),
    PRIEST_META(astralLevel_size, sizeof svd.dungeon_topology.d_astral_level),
    PRIEST_META(invent, offsetof(__typeof__(gi),invent)),
    PRIEST_META(invent_size, sizeof gi.invent),
    PRIEST_META(verbose, offsetof(__typeof__(flags),verbose)),
    PRIEST_META(verbose_size, sizeof flags.verbose),
    PRIEST_META(wizard, offsetof(__typeof__(flags),debug)),
    PRIEST_META(wizard_size, sizeof flags.debug),
    PRIEST_META(gameover, offsetof(__typeof__(program_state),gameover)),
    PRIEST_META(gameover_size, sizeof program_state.gameover),
    PRIEST_META(multiReason, offsetof(__typeof__(gm),multi_reason)),
    PRIEST_META(multiReason_size, sizeof gm.multi_reason),
    PRIEST_META(nomovemsg, offsetof(__typeof__(gn),nomovemsg)),
    PRIEST_META(nomovemsg_size, sizeof gn.nomovemsg),
    PRIEST_META(currentWand, offsetof(__typeof__(gc),current_wand)),
    PRIEST_META(currentWand_size, sizeof gc.current_wand),
    PRIEST_META(buzzer, offsetof(__typeof__(gb),buzzer)),
    PRIEST_META(buzzer_size, sizeof gb.buzzer),
    PRIEST_META(tbx, offsetof(__typeof__(gt),tbx)),
    PRIEST_META(tbx_size, sizeof gt.tbx),
    PRIEST_META(tby, offsetof(__typeof__(gt),tby)),
    PRIEST_META(tby_size, sizeof gt.tby),
    PRIEST_META(vizArray, offsetof(__typeof__(gv),viz_array)),
    PRIEST_META(vizArray_size, sizeof gv.viz_array),
    PRIEST_META(u_ux, offsetof(struct you,ux)),
    PRIEST_META(u_ux_size, sizeof(((struct you*)0)->ux)),
    PRIEST_META(u_uy, offsetof(struct you,uy)),
    PRIEST_META(u_uy_size, sizeof(((struct you*)0)->uy)),
    PRIEST_META(u_uz, offsetof(struct you,uz)),
    PRIEST_META(u_uz_size, sizeof(((struct you*)0)->uz)),
    PRIEST_META(u_ualign, offsetof(struct you,ualign)),
    PRIEST_META(u_ualign_size, sizeof(((struct you*)0)->ualign)),
    PRIEST_META(u_urooms, offsetof(struct you,urooms)),
    PRIEST_META(u_urooms_size, sizeof(((struct you*)0)->urooms)),
    PRIEST_META(u_urooms0, offsetof(struct you,urooms0)),
    PRIEST_META(u_urooms0_size, sizeof(((struct you*)0)->urooms0)),
    PRIEST_META(u_uconduct, offsetof(struct you,uconduct)),
    PRIEST_META(u_uconduct_size, sizeof(((struct you*)0)->uconduct)),
    PRIEST_META(u_ulevelpeak, offsetof(struct you,ulevelpeak)),
    PRIEST_META(u_ulevelpeak_size, sizeof(((struct you*)0)->ulevelpeak)),
    PRIEST_META(u_ublessed, offsetof(struct you,ublessed)),
    PRIEST_META(u_ublessed_size, sizeof(((struct you*)0)->ublessed)),
    PRIEST_META(u_ucleansed, offsetof(struct you,ucleansed)),
    PRIEST_META(u_ucleansed_size, sizeof(((struct you*)0)->ucleansed)),
    PRIEST_META(u_uprops, offsetof(struct you,uprops)),
    PRIEST_META(u_uprops_size, sizeof(((struct you*)0)->uprops)),
    PRIEST_META(u_alignType, offsetof(struct you,ualign.type)),
    PRIEST_META(u_alignType_size, sizeof(((struct you*)0)->ualign.type)),
    PRIEST_META(u_alignRecord, offsetof(struct you,ualign.record)),
    PRIEST_META(u_alignRecord_size, sizeof(((struct you*)0)->ualign.record)),
    PRIEST_META(u_gnostic, offsetof(struct you,uconduct.gnostic)),
    PRIEST_META(u_gnostic_size, sizeof(((struct you*)0)->uconduct.gnostic)),
    PRIEST_META(ALTAR, ALTAR),
    PRIEST_META(AM_CHAOTIC, AM_CHAOTIC),
    PRIEST_META(CORR, CORR),
    PRIEST_META(DOOR, DOOR),
    PRIEST_META(PM_HUMAN, PM_HUMAN),
    PRIEST_META(ROOM, ROOM),
    PRIEST_META(ACH_TMPL, ACH_TMPL),
    PRIEST_META(AD_ELEC, AD_ELEC),
    PRIEST_META(AD_MAGM, AD_MAGM),
    PRIEST_META(ALLOW_M, ALLOW_M),
    PRIEST_META(ALLOW_ROCK, ALLOW_ROCK),
    PRIEST_META(ALL_TRAPS, ALL_TRAPS),
    PRIEST_META(AMULET_OF_YENDOR, AMULET_OF_YENDOR),
    PRIEST_META(AM_LAWFUL, AM_LAWFUL),
    PRIEST_META(AM_MASK, AM_MASK),
    PRIEST_META(AM_SHRINE, AM_SHRINE),
    PRIEST_META(ARTICLE_A, ARTICLE_A),
    PRIEST_META(ARTICLE_NONE, ARTICLE_NONE),
    PRIEST_META(ARTICLE_THE, ARTICLE_THE),
    PRIEST_META(ARTICLE_YOUR, ARTICLE_YOUR),
    PRIEST_META(A_CHAOTIC, A_CHAOTIC),
    PRIEST_META(A_LAWFUL, A_LAWFUL),
    PRIEST_META(A_NEUTRAL, A_NEUTRAL),
    PRIEST_META(A_NONE, A_NONE),
    PRIEST_META(A_WIS, A_WIS),
    PRIEST_META(BLINDED, BLINDED),
    PRIEST_META(BUFSZ, BUFSZ),
    PRIEST_META(CLAIRVOYANT, CLAIRVOYANT),
    PRIEST_META(COLNO, COLNO),
    PRIEST_META(CONFLICT, CONFLICT),
    PRIEST_META(COULD_SEE, COULD_SEE),
    PRIEST_META(DEAF, DEAF),
    PRIEST_META(DISPLACED, DISPLACED),
    PRIEST_META(FROMOUTSIDE, FROMOUTSIDE),
    PRIEST_META(HALLUC, HALLUC),
    PRIEST_META(HALLUC_RES, HALLUC_RES),
    PRIEST_META(INTRINSIC, INTRINSIC),
    PRIEST_META(INVIS, INVIS),
    PRIEST_META(IN_SIGHT, IN_SIGHT),
    PRIEST_META(LL_CONDUCT, LL_CONDUCT),
    PRIEST_META(M1_SEE_INVIS, M1_SEE_INVIS),
    PRIEST_META(M2_MINION, M2_MINION),
    PRIEST_META(MM_ADJACENTOK, MM_ADJACENTOK),
    PRIEST_META(MM_EMIN, MM_EMIN),
    PRIEST_META(MM_EPRI, MM_EPRI),
    PRIEST_META(MM_NOMSG, MM_NOMSG),
    PRIEST_META(NOTONL, NOTONL),
    PRIEST_META(NUMMONS, NUMMONS),
    PRIEST_META(NUM_OBJECTS, NUM_OBJECTS),
    PRIEST_META(N_DIRS, N_DIRS),
    PRIEST_META(PM_ALIGNED_CLERIC, PM_ALIGNED_CLERIC),
    PRIEST_META(PM_ANGEL, PM_ANGEL),
    PRIEST_META(PM_DEATH, PM_DEATH),
    PRIEST_META(PM_FAMINE, PM_FAMINE),
    PRIEST_META(PM_GHOST, PM_GHOST),
    PRIEST_META(PM_HIGH_CLERIC, PM_HIGH_CLERIC),
    PRIEST_META(PM_PESTILENCE, PM_PESTILENCE),
    PRIEST_META(PRONOUN_HALLU, PRONOUN_HALLU),
    PRIEST_META(PROTECTION, PROTECTION),
    PRIEST_META(RLOC_NOMSG, RLOC_NOMSG),
    PRIEST_META(ROOMOFFSET, ROOMOFFSET),
    PRIEST_META(ROWNO, ROWNO),
    PRIEST_META(SPBOOK_no_NOVEL, SPBOOK_no_NOVEL),
    PRIEST_META(SPINE, SPINE),
    PRIEST_META(TEMPLE, TEMPLE),
    PRIEST_META(W_ARMC, W_ARMC),
#ifdef EXTRA_SANITY_CHECKS
    PRIEST_META(config_EXTRA_SANITY_CHECKS, 1),
#else
    PRIEST_META(config_EXTRA_SANITY_CHECKS, 0),
#endif
#ifdef SND_LIB_INTEGRATED
    PRIEST_META(config_SND_LIB_INTEGRATED, 1),
#else
    PRIEST_META(config_SND_LIB_INTEGRATED, 0),
#endif
#ifdef NDEBUG
    PRIEST_META(config_NDEBUG, 1),
#else
    PRIEST_META(config_NDEBUG, 0),
#endif
};
#undef PRIEST_META
size_t probe_context_size(void) { return sizeof(struct epri); }
int probe_layout_count(void) { return sizeof priest_layout / sizeof priest_layout[0]; }
const char *probe_layout_name(int index) { return priest_layout[index].name; }
size_t probe_layout_value(int index) { return priest_layout[index].value; }

/* The adapter intentionally supports this configured native ABI. */
_Static_assert((sizeof(void*)) == 8, "priest ABI pointerSize");
_Static_assert((sizeof(long)) == 8, "priest ABI longSize");
_Static_assert((sizeof(int)) == 4, "priest ABI intSize");
_Static_assert((sizeof(char)) == 1, "priest ABI charSize");
_Static_assert(((char)-1 < 0) == 1, "priest ABI charSigned");
_Static_assert((sizeof(boolean)) == 1, "priest ABI booleanSize");
_Static_assert(((boolean)-1 < 0) == 1, "priest ABI booleanSigned");
_Static_assert((sizeof(coordxy)) == 2, "priest ABI coordxySize");
_Static_assert(((coordxy)-1 < 0) == 1, "priest ABI coordxySigned");
_Static_assert((sizeof(((struct monst*)0)->nmon)) == 8, "priest ABI mon_nmon_size");
_Static_assert((sizeof(((struct monst*)0)->data)) == 8, "priest ABI mon_data_size");
_Static_assert((sizeof(((struct monst*)0)->m_id)) == 4, "priest ABI mon_m_id_size");
_Static_assert((sizeof(((struct monst*)0)->mx)) == 2, "priest ABI mon_mx_size");
_Static_assert((sizeof(((struct monst*)0)->my)) == 2, "priest ABI mon_my_size");
_Static_assert((sizeof(((struct monst*)0)->mhp)) == 4, "priest ABI mon_mhp_size");
_Static_assert((sizeof(((struct monst*)0)->mtame)) == 1, "priest ABI mon_mtame_size");
_Static_assert((sizeof(((struct monst*)0)->mextra)) == 8, "priest ABI mon_mextra_size");
_Static_assert((sizeof(((struct monst*)0)->minvent)) == 8, "priest ABI mon_minvent_size");
_Static_assert((sizeof(((struct permonst*)0)->maligntyp)) == 1, "priest ABI pm_maligntyp_size");
_Static_assert((sizeof(((struct permonst*)0)->mflags1)) == 8, "priest ABI pm_mflags1_size");
_Static_assert((sizeof(((struct permonst*)0)->mflags2)) == 8, "priest ABI pm_mflags2_size");
_Static_assert((sizeof(((struct epri*)0)->parentmid)) == 4, "priest ABI epri_parentmid_size");
_Static_assert((sizeof(((struct epri*)0)->shralign)) == 1, "priest ABI epri_shralign_size");
_Static_assert((sizeof(((struct epri*)0)->shroom)) == 1, "priest ABI epri_shroom_size");
_Static_assert((sizeof(((struct epri*)0)->cheapskate_count)) == 4, "priest ABI epri_cheapskate_count_size");
_Static_assert((sizeof(((struct epri*)0)->intone_time)) == 8, "priest ABI epri_intone_time_size");
_Static_assert((sizeof(((struct epri*)0)->enter_time)) == 8, "priest ABI epri_enter_time_size");
_Static_assert((sizeof(((struct epri*)0)->hostile_time)) == 8, "priest ABI epri_hostile_time_size");
_Static_assert((sizeof(((struct epri*)0)->peaceful_time)) == 8, "priest ABI epri_peaceful_time_size");
_Static_assert((sizeof(((struct emin*)0)->min_align)) == 1, "priest ABI emin_min_align_size");
_Static_assert((sizeof(((struct emin*)0)->renegade)) == 1, "priest ABI emin_renegade_size");
_Static_assert((sizeof(((struct eshk*)0)->following)) == 1, "priest ABI eshk_following_size");
_Static_assert((sizeof(((struct mextra*)0)->epri)) == 8, "priest ABI mextra_epri_size");
_Static_assert((sizeof(((struct mextra*)0)->emin)) == 8, "priest ABI mextra_emin_size");
_Static_assert((sizeof(((struct mextra*)0)->eshk)) == 8, "priest ABI mextra_eshk_size");
_Static_assert((sizeof(((struct mkroom*)0)->rtype)) == 1, "priest ABI room_rtype_size");
_Static_assert((sizeof(((struct mkroom*)0)->lx)) == 2, "priest ABI room_lx_size");
_Static_assert((sizeof(((struct mkroom*)0)->hx)) == 2, "priest ABI room_hx_size");
_Static_assert((sizeof(((struct mkroom*)0)->ly)) == 2, "priest ABI room_ly_size");
_Static_assert((sizeof(((struct mkroom*)0)->hy)) == 2, "priest ABI room_hy_size");
_Static_assert((sizeof(((coord*)0)->x)) == 2, "priest ABI coord_x_size");
_Static_assert((sizeof(((coord*)0)->y)) == 2, "priest ABI coord_y_size");
_Static_assert((sizeof(((d_level*)0)->dnum)) == 2, "priest ABI level_dnum_size");
_Static_assert((sizeof(((d_level*)0)->dlevel)) == 2, "priest ABI level_dlevel_size");
_Static_assert((sizeof(((struct prop*)0)->intrinsic)) == 8, "priest ABI prop_intrinsic_size");
_Static_assert((sizeof(((struct prop*)0)->extrinsic)) == 8, "priest ABI prop_extrinsic_size");
_Static_assert((sizeof(((struct prop*)0)->blocked)) == 8, "priest ABI prop_blocked_size");
_Static_assert((sizeof(((struct rm*)0)->typ)) == 1, "priest ABI terrain_typ_size");
_Static_assert((sizeof(((struct mvitals*)0)->born)) == 1, "priest ABI mvital_born_size");
_Static_assert((sizeof(((struct Gender*)0)->his)) == 8, "priest ABI gender_his_size");
_Static_assert((sizeof(((struct mfndposdata*)0)->cnt)) == 4, "priest ABI mfp_cnt_size");
_Static_assert((sizeof svm.moves) == 8, "priest ABI moves_size");
_Static_assert((sizeof gi.invent) == 8, "priest ABI invent_size");
_Static_assert((sizeof flags.verbose) == 1, "priest ABI verbose_size");
_Static_assert((sizeof flags.debug) == 1, "priest ABI wizard_size");
_Static_assert((sizeof program_state.gameover) == 4, "priest ABI gameover_size");
_Static_assert((sizeof gm.multi_reason) == 8, "priest ABI multiReason_size");
_Static_assert((sizeof gn.nomovemsg) == 8, "priest ABI nomovemsg_size");
_Static_assert((sizeof gc.current_wand) == 8, "priest ABI currentWand_size");
_Static_assert((sizeof gb.buzzer) == 8, "priest ABI buzzer_size");
_Static_assert((sizeof gt.tbx) == 1, "priest ABI tbx_size");
_Static_assert((sizeof gt.tby) == 1, "priest ABI tby_size");
_Static_assert((sizeof gv.viz_array) == 8, "priest ABI vizArray_size");
_Static_assert((sizeof(((struct you*)0)->ux)) == 2, "priest ABI u_ux_size");
_Static_assert((sizeof(((struct you*)0)->uy)) == 2, "priest ABI u_uy_size");
_Static_assert((sizeof(((struct you*)0)->ulevelpeak)) == 4, "priest ABI u_ulevelpeak_size");
_Static_assert((sizeof(((struct you*)0)->ublessed)) == 4, "priest ABI u_ublessed_size");
_Static_assert((sizeof(((struct you*)0)->ucleansed)) == 8, "priest ABI u_ucleansed_size");
_Static_assert((sizeof(((struct you*)0)->ualign.type)) == 1, "priest ABI u_alignType_size");
_Static_assert((sizeof(((struct you*)0)->ualign.record)) == 4, "priest ABI u_alignRecord_size");
_Static_assert((sizeof(((struct you*)0)->uconduct.gnostic)) == 8, "priest ABI u_gnostic_size");
_Static_assert((((__typeof__(((struct monst*)0)->m_id)) -1) < 0) == 0, "priest signedness struct monst.m_id");
_Static_assert((((__typeof__(((struct monst*)0)->mx)) -1) < 0) == 1, "priest signedness struct monst.mx");
_Static_assert((((__typeof__(((struct monst*)0)->my)) -1) < 0) == 1, "priest signedness struct monst.my");
_Static_assert((((__typeof__(((struct monst*)0)->mhp)) -1) < 0) == 1, "priest signedness struct monst.mhp");
_Static_assert((((__typeof__(((struct monst*)0)->mtame)) -1) < 0) == 1, "priest signedness struct monst.mtame");
_Static_assert((((__typeof__(((struct permonst*)0)->maligntyp)) -1) < 0) == 1, "priest signedness struct permonst.maligntyp");
_Static_assert((((__typeof__(((struct permonst*)0)->mflags1)) -1) < 0) == 0, "priest signedness struct permonst.mflags1");
_Static_assert((((__typeof__(((struct permonst*)0)->mflags2)) -1) < 0) == 0, "priest signedness struct permonst.mflags2");
_Static_assert((((__typeof__(((struct epri*)0)->parentmid)) -1) < 0) == 0, "priest signedness struct epri.parentmid");
_Static_assert((((__typeof__(((struct epri*)0)->shralign)) -1) < 0) == 1, "priest signedness struct epri.shralign");
_Static_assert((((__typeof__(((struct epri*)0)->shroom)) -1) < 0) == 1, "priest signedness struct epri.shroom");
_Static_assert((((__typeof__(((struct epri*)0)->cheapskate_count)) -1) < 0) == 0, "priest signedness struct epri.cheapskate_count");
_Static_assert((((__typeof__(((struct epri*)0)->intone_time)) -1) < 0) == 1, "priest signedness struct epri.intone_time");
_Static_assert((((__typeof__(((struct epri*)0)->enter_time)) -1) < 0) == 1, "priest signedness struct epri.enter_time");
_Static_assert((((__typeof__(((struct epri*)0)->hostile_time)) -1) < 0) == 1, "priest signedness struct epri.hostile_time");
_Static_assert((((__typeof__(((struct epri*)0)->peaceful_time)) -1) < 0) == 1, "priest signedness struct epri.peaceful_time");
_Static_assert((((__typeof__(((struct emin*)0)->min_align)) -1) < 0) == 1, "priest signedness struct emin.min_align");
_Static_assert((((__typeof__(((struct emin*)0)->renegade)) -1) < 0) == 1, "priest signedness struct emin.renegade");
_Static_assert((((__typeof__(((struct eshk*)0)->following)) -1) < 0) == 1, "priest signedness struct eshk.following");
_Static_assert((((__typeof__(((struct mkroom*)0)->rtype)) -1) < 0) == 1, "priest signedness struct mkroom.rtype");
_Static_assert((((__typeof__(((struct mkroom*)0)->lx)) -1) < 0) == 1, "priest signedness struct mkroom.lx");
_Static_assert((((__typeof__(((struct mkroom*)0)->hx)) -1) < 0) == 1, "priest signedness struct mkroom.hx");
_Static_assert((((__typeof__(((struct mkroom*)0)->ly)) -1) < 0) == 1, "priest signedness struct mkroom.ly");
_Static_assert((((__typeof__(((struct mkroom*)0)->hy)) -1) < 0) == 1, "priest signedness struct mkroom.hy");
_Static_assert((((__typeof__(((coord*)0)->x)) -1) < 0) == 1, "priest signedness coord.x");
_Static_assert((((__typeof__(((coord*)0)->y)) -1) < 0) == 1, "priest signedness coord.y");
_Static_assert((((__typeof__(((d_level*)0)->dnum)) -1) < 0) == 1, "priest signedness d_level.dnum");
_Static_assert((((__typeof__(((d_level*)0)->dlevel)) -1) < 0) == 1, "priest signedness d_level.dlevel");
_Static_assert((((__typeof__(((struct prop*)0)->intrinsic)) -1) < 0) == 1, "priest signedness struct prop.intrinsic");
_Static_assert((((__typeof__(((struct prop*)0)->extrinsic)) -1) < 0) == 1, "priest signedness struct prop.extrinsic");
_Static_assert((((__typeof__(((struct prop*)0)->blocked)) -1) < 0) == 1, "priest signedness struct prop.blocked");
_Static_assert((((__typeof__(((struct rm*)0)->typ)) -1) < 0) == 1, "priest signedness struct rm.typ");
_Static_assert((((__typeof__(((struct mvitals*)0)->born)) -1) < 0) == 0, "priest signedness struct mvitals.born");
_Static_assert((((__typeof__(((struct mfndposdata*)0)->cnt)) -1) < 0) == 1, "priest signedness struct mfndposdata.cnt");
_Static_assert((((__typeof__(((struct you*)0)->ux)) -1) < 0) == 1, "priest signedness struct you.ux");
_Static_assert((((__typeof__(((struct you*)0)->uy)) -1) < 0) == 1, "priest signedness struct you.uy");
_Static_assert((((__typeof__(((struct you*)0)->ulevelpeak)) -1) < 0) == 1, "priest signedness struct you.ulevelpeak");
_Static_assert((((__typeof__(((struct you*)0)->ublessed)) -1) < 0) == 1, "priest signedness struct you.ublessed");
_Static_assert((((__typeof__(((struct you*)0)->ucleansed)) -1) < 0) == 1, "priest signedness struct you.ucleansed");
_Static_assert((((__typeof__(((struct you*)0)->ualign.type)) -1) < 0) == 1, "priest signedness struct you.ualign.type");
_Static_assert((((__typeof__(((struct you*)0)->ualign.record)) -1) < 0) == 1, "priest signedness struct you.ualign.record");
_Static_assert((((__typeof__(((struct you*)0)->uconduct.gnostic)) -1) < 0) == 1, "priest signedness struct you.uconduct.gnostic");
_Static_assert((((__typeof__(svm.moves)) -1) < 0) == 1, "priest signedness svm.moves");
_Static_assert((((__typeof__(flags.verbose)) -1) < 0) == 1, "priest signedness flags.verbose");
_Static_assert((((__typeof__(flags.debug)) -1) < 0) == 1, "priest signedness flags.debug");
_Static_assert((((__typeof__(program_state.gameover)) -1) < 0) == 1, "priest signedness program_state.gameover");
_Static_assert((((__typeof__(gt.tbx)) -1) < 0) == 1, "priest signedness gt.tbx");
_Static_assert((((__typeof__(gt.tby)) -1) < 0) == 1, "priest signedness gt.tby");
_Static_assert((((__typeof__(((struct mfndposdata*)0)->info[0])) -1) < 0), "priest signedness mfndposdata.info");
_Static_assert(sizeof(((struct mfndposdata*)0)->info[0]) == 8, "priest mfndposdata.info width");
