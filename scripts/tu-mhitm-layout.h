#ifndef TELEPORT_MHITM_LAYOUT_H
#define TELEPORT_MHITM_LAYOUT_H
#include "hack.h"
#include "artifact.h"
#include <stddef.h>
#ifdef EXTRA_SANITY_CHECKS
#error Review MHITM remove_monster debug macro before enabling this configuration
#endif
_Static_assert(sizeof(seenV)==1,"MHITM visibility byte width");
struct mhitm_meta {const char *name;size_t value;};
#define MHITM_META(k,v) {#k,(size_t)(v)}
static const struct mhitm_meta mhitm_layout[]={
MHITM_META(pointerSize,sizeof(void*)),
MHITM_META(longSize,sizeof(long)),
MHITM_META(intSize,sizeof(int)),
MHITM_META(booleanSize,sizeof(boolean)),
MHITM_META(monsterSize,sizeof(struct monst)),
MHITM_META(objectSize,sizeof(struct obj)),
MHITM_META(permonstSize,sizeof(struct permonst)),
MHITM_META(objectClassSize,sizeof(struct objclass)),
MHITM_META(attackSize,sizeof(struct attack)),
MHITM_META(mhitmSize,sizeof(struct mhitm_data)),
MHITM_META(rmSize,sizeof(struct rm)),
MHITM_META(propSize,sizeof(struct prop)),
MHITM_META(coordSize,sizeof(coord)),
MHITM_META(genderSize,sizeof(struct Gender)),
MHITM_META(mon_nmon,offsetof(struct monst,nmon)),
MHITM_META(mon_nmon_size,sizeof(((struct monst*)0)->nmon)),
MHITM_META(mon_data,offsetof(struct monst,data)),
MHITM_META(mon_data_size,sizeof(((struct monst*)0)->data)),
MHITM_META(mon_minvent,offsetof(struct monst,minvent)),
MHITM_META(mon_minvent_size,sizeof(((struct monst*)0)->minvent)),
MHITM_META(mon_mw,offsetof(struct monst,mw)),
MHITM_META(mon_mw_size,sizeof(((struct monst*)0)->mw)),
MHITM_META(mon_mhp,offsetof(struct monst,mhp)),
MHITM_META(mon_mhp_size,sizeof(((struct monst*)0)->mhp)),
MHITM_META(mon_mhpmax,offsetof(struct monst,mhpmax)),
MHITM_META(mon_mhpmax_size,sizeof(((struct monst*)0)->mhpmax)),
MHITM_META(mon_mx,offsetof(struct monst,mx)),
MHITM_META(mon_mx_size,sizeof(((struct monst*)0)->mx)),
MHITM_META(mon_my,offsetof(struct monst,my)),
MHITM_META(mon_my_size,sizeof(((struct monst*)0)->my)),
MHITM_META(mon_movement,offsetof(struct monst,movement)),
MHITM_META(mon_movement_size,sizeof(((struct monst*)0)->movement)),
MHITM_META(mon_mtame,offsetof(struct monst,mtame)),
MHITM_META(mon_mtame_size,sizeof(((struct monst*)0)->mtame)),
MHITM_META(mon_mstrategy,offsetof(struct monst,mstrategy)),
MHITM_META(mon_mstrategy_size,sizeof(((struct monst*)0)->mstrategy)),
MHITM_META(mon_mlstmv,offsetof(struct monst,mlstmv)),
MHITM_META(mon_mlstmv_size,sizeof(((struct monst*)0)->mlstmv)),
MHITM_META(mon_m_lev,offsetof(struct monst,m_lev)),
MHITM_META(mon_m_lev_size,sizeof(((struct monst*)0)->m_lev)),
MHITM_META(mon_m_id,offsetof(struct monst,m_id)),
MHITM_META(mon_m_id_size,sizeof(((struct monst*)0)->m_id)),
MHITM_META(mon_weapon_check,offsetof(struct monst,weapon_check)),
MHITM_META(mon_weapon_check_size,sizeof(((struct monst*)0)->weapon_check)),
MHITM_META(mon_mspec_used,offsetof(struct monst,mspec_used)),
MHITM_META(mon_mspec_used_size,sizeof(((struct monst*)0)->mspec_used)),
MHITM_META(mon_meating,offsetof(struct monst,meating)),
MHITM_META(mon_meating_size,sizeof(((struct monst*)0)->meating)),
MHITM_META(mon_cham,offsetof(struct monst,cham)),
MHITM_META(mon_cham_size,sizeof(((struct monst*)0)->cham)),
MHITM_META(mon_m_ap_type,offsetof(struct monst,m_ap_type)),
MHITM_META(mon_m_ap_type_size,sizeof(((struct monst*)0)->m_ap_type)),
MHITM_META(mon_mstate,offsetof(struct monst,mstate)),
MHITM_META(mon_mstate_size,sizeof(((struct monst*)0)->mstate)),
MHITM_META(mon_misc_worn_check,offsetof(struct monst,misc_worn_check)),
MHITM_META(mon_misc_worn_check_size,sizeof(((struct monst*)0)->misc_worn_check)),
MHITM_META(obj_nobj,offsetof(struct obj,nobj)),
MHITM_META(obj_nobj_size,sizeof(((struct obj*)0)->nobj)),
MHITM_META(obj_otyp,offsetof(struct obj,otyp)),
MHITM_META(obj_otyp_size,sizeof(((struct obj*)0)->otyp)),
MHITM_META(obj_oclass,offsetof(struct obj,oclass)),
MHITM_META(obj_oclass_size,sizeof(((struct obj*)0)->oclass)),
MHITM_META(obj_oartifact,offsetof(struct obj,oartifact)),
MHITM_META(obj_oartifact_size,sizeof(((struct obj*)0)->oartifact)),
MHITM_META(obj_quan,offsetof(struct obj,quan)),
MHITM_META(obj_quan_size,sizeof(((struct obj*)0)->quan)),
MHITM_META(pm_mlet,offsetof(struct permonst,mlet)),
MHITM_META(pm_mlet_size,sizeof(((struct permonst*)0)->mlet)),
MHITM_META(pm_msize,offsetof(struct permonst,msize)),
MHITM_META(pm_msize_size,sizeof(((struct permonst*)0)->msize)),
MHITM_META(pm_mflags1,offsetof(struct permonst,mflags1)),
MHITM_META(pm_mflags1_size,sizeof(((struct permonst*)0)->mflags1)),
MHITM_META(pm_mflags2,offsetof(struct permonst,mflags2)),
MHITM_META(pm_mflags2_size,sizeof(((struct permonst*)0)->mflags2)),
MHITM_META(pm_mlevel,offsetof(struct permonst,mlevel)),
MHITM_META(pm_mlevel_size,sizeof(((struct permonst*)0)->mlevel)),
MHITM_META(pm_geno,offsetof(struct permonst,geno)),
MHITM_META(pm_geno_size,sizeof(((struct permonst*)0)->geno)),
MHITM_META(pm_pmidx,offsetof(struct permonst,pmidx)),
MHITM_META(pm_pmidx_size,sizeof(((struct permonst*)0)->pmidx)),
MHITM_META(pm_mattk,offsetof(struct permonst,mattk)),
MHITM_META(pm_mattk_size,sizeof(((struct permonst*)0)->mattk)),
MHITM_META(cls_oc_skill,offsetof(struct objclass,oc_skill)),
MHITM_META(cls_oc_skill_size,sizeof(((struct objclass*)0)->oc_skill)),
MHITM_META(atk_aatyp,offsetof(struct attack,aatyp)),
MHITM_META(atk_aatyp_size,sizeof(((struct attack*)0)->aatyp)),
MHITM_META(atk_adtyp,offsetof(struct attack,adtyp)),
MHITM_META(atk_adtyp_size,sizeof(((struct attack*)0)->adtyp)),
MHITM_META(atk_damn,offsetof(struct attack,damn)),
MHITM_META(atk_damn_size,sizeof(((struct attack*)0)->damn)),
MHITM_META(atk_damd,offsetof(struct attack,damd)),
MHITM_META(atk_damd_size,sizeof(((struct attack*)0)->damd)),
MHITM_META(mhm_damage,offsetof(struct mhitm_data,damage)),
MHITM_META(mhm_damage_size,sizeof(((struct mhitm_data*)0)->damage)),
MHITM_META(mhm_hitflags,offsetof(struct mhitm_data,hitflags)),
MHITM_META(mhm_hitflags_size,sizeof(((struct mhitm_data*)0)->hitflags)),
MHITM_META(mhm_done,offsetof(struct mhitm_data,done)),
MHITM_META(mhm_done_size,sizeof(((struct mhitm_data*)0)->done)),
MHITM_META(mhm_permdmg,offsetof(struct mhitm_data,permdmg)),
MHITM_META(mhm_permdmg_size,sizeof(((struct mhitm_data*)0)->permdmg)),
MHITM_META(mhm_specialdmg,offsetof(struct mhitm_data,specialdmg)),
MHITM_META(mhm_specialdmg_size,sizeof(((struct mhitm_data*)0)->specialdmg)),
MHITM_META(mhm_dieroll,offsetof(struct mhitm_data,dieroll)),
MHITM_META(mhm_dieroll_size,sizeof(((struct mhitm_data*)0)->dieroll)),
MHITM_META(u_ux,offsetof(struct you,ux)),
MHITM_META(u_ux_size,sizeof(((struct you*)0)->ux)),
MHITM_META(u_uy,offsetof(struct you,uy)),
MHITM_META(u_uy_size,sizeof(((struct you*)0)->uy)),
MHITM_META(u_ulycn,offsetof(struct you,ulycn)),
MHITM_META(u_ulycn_size,sizeof(((struct you*)0)->ulycn)),
MHITM_META(u_umonnum,offsetof(struct you,umonnum)),
MHITM_META(u_umonnum_size,sizeof(((struct you*)0)->umonnum)),
MHITM_META(u_usteed,offsetof(struct you,usteed)),
MHITM_META(u_usteed_size,sizeof(((struct you*)0)->usteed)),
MHITM_META(u_ustuck,offsetof(struct you,ustuck)),
MHITM_META(u_ustuck_size,sizeof(((struct you*)0)->ustuck)),
MHITM_META(u_uprops,offsetof(struct you,uprops)),
MHITM_META(u_uprops_size,sizeof(((struct you*)0)->uprops)),
MHITM_META(prop_intrinsic,offsetof(struct prop,intrinsic)),
MHITM_META(prop_intrinsic_size,sizeof(((struct prop*)0)->intrinsic)),
MHITM_META(prop_extrinsic,offsetof(struct prop,extrinsic)),
MHITM_META(prop_extrinsic_size,sizeof(((struct prop*)0)->extrinsic)),
MHITM_META(prop_blocked,offsetof(struct prop,blocked)),
MHITM_META(prop_blocked_size,sizeof(((struct prop*)0)->blocked)),
MHITM_META(rm_typ,offsetof(struct rm,typ)),
MHITM_META(rm_typ_size,sizeof(((struct rm*)0)->typ)),
MHITM_META(coord_x,offsetof(coord,x)),
MHITM_META(coord_x_size,sizeof(((coord*)0)->x)),
MHITM_META(coord_y,offsetof(coord,y)),
MHITM_META(coord_y_size,sizeof(((coord*)0)->y)),
MHITM_META(gender_his,offsetof(struct Gender,his)),
MHITM_META(gender_his_size,sizeof(((struct Gender*)0)->his)),
MHITM_META(far_noise,offsetof(__typeof__(gf),far_noise)),
MHITM_META(far_noise_size,sizeof(gf.far_noise)),
MHITM_META(moves,offsetof(__typeof__(svm),moves)),
MHITM_META(moves_size,sizeof(svm.moves)),
MHITM_META(noisetime,offsetof(__typeof__(gn),noisetime)),
MHITM_META(noisetime_size,sizeof(gn.noisetime)),
MHITM_META(notonhead,offsetof(__typeof__(gn),notonhead)),
MHITM_META(notonhead_size,sizeof(gn.notonhead)),
MHITM_META(vis,offsetof(__typeof__(gv),vis)),
MHITM_META(vis_size,sizeof(gv.vis)),
MHITM_META(vizArray,offsetof(__typeof__(gv),viz_array)),
MHITM_META(vizArray_size,sizeof(gv.viz_array)),
MHITM_META(bhitpos,offsetof(__typeof__(gb),bhitpos)),
MHITM_META(bhitpos_size,sizeof(gb.bhitpos)),
MHITM_META(skipdrin,offsetof(__typeof__(gs),skipdrin)),
MHITM_META(skipdrin_size,sizeof(gs.skipdrin)),
MHITM_META(last_hider,offsetof(__typeof__(gl),last_hider)),
MHITM_META(last_hider_size,sizeof(gl.last_hider)),
MHITM_META(last_msg,offsetof(__typeof__(iflags),last_msg)),
MHITM_META(last_msg_size,sizeof(iflags.last_msg)),
MHITM_META(verbose,offsetof(__typeof__(flags),verbose)),
MHITM_META(verbose_size,sizeof(flags.verbose)),
MHITM_META(youmonst,offsetof(__typeof__(gy),youmonst)),
MHITM_META(youmonst_size,sizeof(gy.youmonst)),
MHITM_META(multi,offsetof(__typeof__(gm),multi)),
MHITM_META(multi_size,sizeof(gm.multi)),
MHITM_META(mswallower,offsetof(__typeof__(gm),mswallower)),
MHITM_META(mswallower_size,sizeof(gm.mswallower)),
MHITM_META(norevive,offsetof(__typeof__(gm),mkcorpstat_norevive)),
MHITM_META(norevive_size,sizeof(gm.mkcorpstat_norevive)),
MHITM_META(zombify,offsetof(__typeof__(gz),zombify)),
MHITM_META(zombify_size,sizeof(gz.zombify)),
MHITM_META(monsters,offsetof(__typeof__(svl),level.monsters)),
MHITM_META(monsters_size,sizeof(svl.level.monsters)),
MHITM_META(locations,offsetof(__typeof__(svl),level.locations)),
MHITM_META(locations_size,sizeof(svl.level.locations)),
MHITM_META(fmon,offsetof(__typeof__(svl),level.monlist)),
MHITM_META(fmon_size,sizeof(svl.level.monlist)),
MHITM_META(ACID_RES,ACID_RES),
MHITM_META(AD_ACID,AD_ACID),
MHITM_META(AD_BLND,AD_BLND),
MHITM_META(AD_COLD,AD_COLD),
MHITM_META(AD_CORR,AD_CORR),
MHITM_META(AD_DGST,AD_DGST),
MHITM_META(AD_DRIN,AD_DRIN),
MHITM_META(AD_ELEC,AD_ELEC),
MHITM_META(AD_ENCH,AD_ENCH),
MHITM_META(AD_FIRE,AD_FIRE),
MHITM_META(AD_PHYS,AD_PHYS),
MHITM_META(AD_PLYS,AD_PLYS),
MHITM_META(AD_RBRE,AD_RBRE),
MHITM_META(AD_RUST,AD_RUST),
MHITM_META(AD_SLEE,AD_SLEE),
MHITM_META(AD_STCK,AD_STCK),
MHITM_META(AD_STON,AD_STON),
MHITM_META(AD_STUN,AD_STUN),
MHITM_META(AD_WRAP,AD_WRAP),
MHITM_META(ANTIMAGIC,ANTIMAGIC),
MHITM_META(ARTICLE_A,ARTICLE_A),
MHITM_META(ARTICLE_NONE,ARTICLE_NONE),
MHITM_META(ARTICLE_THE,ARTICLE_THE),
MHITM_META(ART_SNICKERSNEE,ART_SNICKERSNEE),
MHITM_META(ART_TROLLSBANE,ART_TROLLSBANE),
MHITM_META(AT_BITE,AT_BITE),
MHITM_META(AT_BOOM,AT_BOOM),
MHITM_META(AT_BREA,AT_BREA),
MHITM_META(AT_BUTT,AT_BUTT),
MHITM_META(AT_CLAW,AT_CLAW),
MHITM_META(AT_ENGL,AT_ENGL),
MHITM_META(AT_EXPL,AT_EXPL),
MHITM_META(AT_GAZE,AT_GAZE),
MHITM_META(AT_HUGS,AT_HUGS),
MHITM_META(AT_KICK,AT_KICK),
MHITM_META(AT_MAGC,AT_MAGC),
MHITM_META(AT_NONE,AT_NONE),
MHITM_META(AT_SPIT,AT_SPIT),
MHITM_META(AT_STNG,AT_STNG),
MHITM_META(AT_TENT,AT_TENT),
MHITM_META(AT_TUCH,AT_TUCH),
MHITM_META(AT_WEAP,AT_WEAP),
MHITM_META(BLINDED,BLINDED),
MHITM_META(BUFSZ,BUFSZ),
MHITM_META(COLD_RES,COLD_RES),
MHITM_META(COLNO,COLNO),
MHITM_META(CONFLICT,CONFLICT),
MHITM_META(DAGGER,DAGGER),
MHITM_META(DEAF,DEAF),
MHITM_META(EF_GREASE,EF_GREASE),
MHITM_META(EF_VERBOSE,EF_VERBOSE),
MHITM_META(ERODE_BURN,ERODE_BURN),
MHITM_META(ERODE_CORRODE,ERODE_CORRODE),
MHITM_META(ERODE_NONE,ERODE_NONE),
MHITM_META(ERODE_RUST,ERODE_RUST),
MHITM_META(FIRE_RES,FIRE_RES),
MHITM_META(G_UNIQ,G_UNIQ),
MHITM_META(IN_SIGHT,IN_SIGHT),
MHITM_META(IRON,IRON),
MHITM_META(IRONBARS,IRONBARS),
MHITM_META(LOW_PM,LOW_PM),
MHITM_META(M1_AMORPHOUS,M1_AMORPHOUS),
MHITM_META(M1_NOEYES,M1_NOEYES),
MHITM_META(M1_SEE_INVIS,M1_SEE_INVIS),
MHITM_META(M1_TPORT,M1_TPORT),
MHITM_META(M1_UNSOLID,M1_UNSOLID),
MHITM_META(M1_WALLWALK,M1_WALLWALK),
MHITM_META(M2_ELF,M2_ELF),
MHITM_META(M2_ORC,M2_ORC),
MHITM_META(METAL,METAL),
MHITM_META(MM_IGNOREWATER,MM_IGNOREWATER),
MHITM_META(MON_FLOOR,MON_FLOOR),
MHITM_META(MZ_HUGE,MZ_HUGE),
MHITM_META(M_AP_FURNITURE,M_AP_FURNITURE),
MHITM_META(M_AP_MONSTER,M_AP_MONSTER),
MHITM_META(M_AP_NOTHING,M_AP_NOTHING),
MHITM_META(M_AP_OBJECT,M_AP_OBJECT),
MHITM_META(M_AP_TYPMASK,M_AP_TYPMASK),
MHITM_META(M_ATTK_AGR_DIED,M_ATTK_AGR_DIED),
MHITM_META(M_ATTK_AGR_DONE,M_ATTK_AGR_DONE),
MHITM_META(M_ATTK_DEF_DIED,M_ATTK_DEF_DIED),
MHITM_META(M_ATTK_HIT,M_ATTK_HIT),
MHITM_META(M_ATTK_MISS,M_ATTK_MISS),
MHITM_META(NATTK,NATTK),
MHITM_META(NC_SHOW_MSG,NC_SHOW_MSG),
MHITM_META(NEED_HTH_WEAPON,NEED_HTH_WEAPON),
MHITM_META(NEED_WEAPON,NEED_WEAPON),
MHITM_META(NON_PM,NON_PM),
MHITM_META(NORMAL_SPEED,NORMAL_SPEED),
MHITM_META(NOTELL,NOTELL),
MHITM_META(NO_NC_FLAGS,NO_NC_FLAGS),
MHITM_META(NO_TRAP_FLAGS,NO_TRAP_FLAGS),
MHITM_META(NUMMONS,NUMMONS),
MHITM_META(PASSES_WALLS,PASSES_WALLS),
MHITM_META(PLNMSG_HIDE_UNDER,PLNMSG_HIDE_UNDER),
MHITM_META(PM_AIR_ELEMENTAL,PM_AIR_ELEMENTAL),
MHITM_META(PM_ARCHON,PM_ARCHON),
MHITM_META(PM_BLACK_PUDDING,PM_BLACK_PUDDING),
MHITM_META(PM_BROWN_PUDDING,PM_BROWN_PUDDING),
MHITM_META(PM_CHICKATRICE,PM_CHICKATRICE),
MHITM_META(PM_COCKATRICE,PM_COCKATRICE),
MHITM_META(PM_DEATH,PM_DEATH),
MHITM_META(PM_FAMINE,PM_FAMINE),
MHITM_META(PM_FIRE_ELEMENTAL,PM_FIRE_ELEMENTAL),
MHITM_META(PM_FIRE_VORTEX,PM_FIRE_VORTEX),
MHITM_META(PM_FLAMING_SPHERE,PM_FLAMING_SPHERE),
MHITM_META(PM_FLOATING_EYE,PM_FLOATING_EYE),
MHITM_META(PM_GREEN_SLIME,PM_GREEN_SLIME),
MHITM_META(PM_GRID_BUG,PM_GRID_BUG),
MHITM_META(PM_HUMAN,PM_HUMAN),
MHITM_META(PM_MEDUSA,PM_MEDUSA),
MHITM_META(PM_NURSE,PM_NURSE),
MHITM_META(PM_PESTILENCE,PM_PESTILENCE),
MHITM_META(PM_SALAMANDER,PM_SALAMANDER),
MHITM_META(PM_SHADE,PM_SHADE),
MHITM_META(PM_STEAM_VORTEX,PM_STEAM_VORTEX),
MHITM_META(PM_VAMPIRE,PM_VAMPIRE),
MHITM_META(PM_VAMPIRE_LEADER,PM_VAMPIRE_LEADER),
MHITM_META(PM_VLAD_THE_IMPALER,PM_VLAD_THE_IMPALER),
MHITM_META(PM_WRAITH,PM_WRAITH),
MHITM_META(POLY_NOFLAGS,POLY_NOFLAGS),
MHITM_META(POOL,POOL),
MHITM_META(PRONOUN_HALLU,PRONOUN_HALLU),
MHITM_META(P_LANCE,P_LANCE),
MHITM_META(P_POLEARMS,P_POLEARMS),
MHITM_META(RLOC_MSG,RLOC_MSG),
MHITM_META(ROOM,ROOM),
MHITM_META(ROWNO,ROWNO),
MHITM_META(SHOCK_RES,SHOCK_RES),
MHITM_META(SILVER,SILVER),
MHITM_META(SILVER_SABER,SILVER_SABER),
MHITM_META(SLEEP_RES,SLEEP_RES),
MHITM_META(SPEAR,SPEAR),
MHITM_META(STONE,STONE),
MHITM_META(STONE_RES,STONE_RES),
MHITM_META(STRAT_WAITFORU,STRAT_WAITFORU),
MHITM_META(STRAT_WAITMASK,STRAT_WAITMASK),
MHITM_META(SUPPRESS_INVISIBLE,SUPPRESS_INVISIBLE),
MHITM_META(SUPPRESS_IT,SUPPRESS_IT),
MHITM_META(SUPPRESS_NAME,SUPPRESS_NAME),
MHITM_META(S_GHOST,S_GHOST),
MHITM_META(S_MIMIC,S_MIMIC),
MHITM_META(S_TROLL,S_TROLL),
MHITM_META(S_VORTEX,S_VORTEX),
MHITM_META(TELL,TELL),
MHITM_META(TOOL_CLASS,TOOL_CLASS),
MHITM_META(TREE,TREE),
MHITM_META(Trap_Killed_Mon,Trap_Killed_Mon),
MHITM_META(UNCHANGING,UNCHANGING),
MHITM_META(WAND_CLASS,WAND_CLASS),
MHITM_META(WEAPON_CLASS,WEAPON_CLASS),
MHITM_META(W_ARMC,W_ARMC),
MHITM_META(W_ARMF,W_ARMF),
MHITM_META(W_ARMG,W_ARMG),
MHITM_META(W_ARMH,W_ARMH),
MHITM_META(XKILL_GIVEMSG,XKILL_GIVEMSG),
MHITM_META(XKILL_NOCORPSE,XKILL_NOCORPSE),
};
_Static_assert(sizeof(((struct monst*)0)->nmon)==8,"MHITM mon_nmon width");
_Static_assert(sizeof(((struct monst*)0)->data)==8,"MHITM mon_data width");
_Static_assert(sizeof(((struct monst*)0)->minvent)==8,"MHITM mon_minvent width");
_Static_assert(sizeof(((struct monst*)0)->mw)==8,"MHITM mon_mw width");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4,"MHITM mon_mhp width");
_Static_assert((((__typeof__(((struct monst*)0)->mhp))-1)<0)==1,"MHITM mon_mhp signedness");
_Static_assert(sizeof(((struct monst*)0)->mhpmax)==4,"MHITM mon_mhpmax width");
_Static_assert((((__typeof__(((struct monst*)0)->mhpmax))-1)<0)==1,"MHITM mon_mhpmax signedness");
_Static_assert(sizeof(((struct monst*)0)->mx)==2,"MHITM mon_mx width");
_Static_assert((((__typeof__(((struct monst*)0)->mx))-1)<0)==1,"MHITM mon_mx signedness");
_Static_assert(sizeof(((struct monst*)0)->my)==2,"MHITM mon_my width");
_Static_assert((((__typeof__(((struct monst*)0)->my))-1)<0)==1,"MHITM mon_my signedness");
_Static_assert(sizeof(((struct monst*)0)->movement)==2,"MHITM mon_movement width");
_Static_assert((((__typeof__(((struct monst*)0)->movement))-1)<0)==1,"MHITM mon_movement signedness");
_Static_assert(sizeof(((struct monst*)0)->mtame)==1,"MHITM mon_mtame width");
_Static_assert((((__typeof__(((struct monst*)0)->mtame))-1)<0)==1,"MHITM mon_mtame signedness");
_Static_assert(sizeof(((struct monst*)0)->mstrategy)==8,"MHITM mon_mstrategy width");
_Static_assert((((__typeof__(((struct monst*)0)->mstrategy))-1)<0)==0,"MHITM mon_mstrategy signedness");
_Static_assert(sizeof(((struct monst*)0)->mlstmv)==8,"MHITM mon_mlstmv width");
_Static_assert((((__typeof__(((struct monst*)0)->mlstmv))-1)<0)==1,"MHITM mon_mlstmv signedness");
_Static_assert(sizeof(((struct monst*)0)->m_lev)==1,"MHITM mon_m_lev width");
_Static_assert((((__typeof__(((struct monst*)0)->m_lev))-1)<0)==0,"MHITM mon_m_lev signedness");
_Static_assert(sizeof(((struct monst*)0)->m_id)==4,"MHITM mon_m_id width");
_Static_assert((((__typeof__(((struct monst*)0)->m_id))-1)<0)==0,"MHITM mon_m_id signedness");
_Static_assert(sizeof(((struct monst*)0)->weapon_check)==2,"MHITM mon_weapon_check width");
_Static_assert((((__typeof__(((struct monst*)0)->weapon_check))-1)<0)==1,"MHITM mon_weapon_check signedness");
_Static_assert(sizeof(((struct monst*)0)->mspec_used)==4,"MHITM mon_mspec_used width");
_Static_assert((((__typeof__(((struct monst*)0)->mspec_used))-1)<0)==1,"MHITM mon_mspec_used signedness");
_Static_assert(sizeof(((struct monst*)0)->meating)==4,"MHITM mon_meating width");
_Static_assert((((__typeof__(((struct monst*)0)->meating))-1)<0)==1,"MHITM mon_meating signedness");
_Static_assert(sizeof(((struct monst*)0)->cham)==2,"MHITM mon_cham width");
_Static_assert((((__typeof__(((struct monst*)0)->cham))-1)<0)==1,"MHITM mon_cham signedness");
_Static_assert(sizeof(((struct monst*)0)->m_ap_type)==1,"MHITM mon_m_ap_type width");
_Static_assert((((__typeof__(((struct monst*)0)->m_ap_type))-1)<0)==0,"MHITM mon_m_ap_type signedness");
_Static_assert(sizeof(((struct monst*)0)->mstate)==8,"MHITM mon_mstate width");
_Static_assert((((__typeof__(((struct monst*)0)->mstate))-1)<0)==1,"MHITM mon_mstate signedness");
_Static_assert(sizeof(((struct monst*)0)->misc_worn_check)==8,"MHITM mon_misc_worn_check width");
_Static_assert((((__typeof__(((struct monst*)0)->misc_worn_check))-1)<0)==1,"MHITM mon_misc_worn_check signedness");
_Static_assert(sizeof(((struct obj*)0)->nobj)==8,"MHITM obj_nobj width");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2,"MHITM obj_otyp width");
_Static_assert((((__typeof__(((struct obj*)0)->otyp))-1)<0)==1,"MHITM obj_otyp signedness");
_Static_assert(sizeof(((struct obj*)0)->oclass)==1,"MHITM obj_oclass width");
_Static_assert((((__typeof__(((struct obj*)0)->oclass))-1)<0)==1,"MHITM obj_oclass signedness");
_Static_assert(sizeof(((struct obj*)0)->oartifact)==1,"MHITM obj_oartifact width");
_Static_assert((((__typeof__(((struct obj*)0)->oartifact))-1)<0)==1,"MHITM obj_oartifact signedness");
_Static_assert(sizeof(((struct obj*)0)->quan)==8,"MHITM obj_quan width");
_Static_assert((((__typeof__(((struct obj*)0)->quan))-1)<0)==1,"MHITM obj_quan signedness");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1,"MHITM pm_mlet width");
_Static_assert((((__typeof__(((struct permonst*)0)->mlet))-1)<0)==1,"MHITM pm_mlet signedness");
_Static_assert(sizeof(((struct permonst*)0)->msize)==1,"MHITM pm_msize width");
_Static_assert((((__typeof__(((struct permonst*)0)->msize))-1)<0)==0,"MHITM pm_msize signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8,"MHITM pm_mflags1 width");
_Static_assert((((__typeof__(((struct permonst*)0)->mflags1))-1)<0)==0,"MHITM pm_mflags1 signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8,"MHITM pm_mflags2 width");
_Static_assert((((__typeof__(((struct permonst*)0)->mflags2))-1)<0)==0,"MHITM pm_mflags2 signedness");
_Static_assert(sizeof(((struct permonst*)0)->mlevel)==1,"MHITM pm_mlevel width");
_Static_assert((((__typeof__(((struct permonst*)0)->mlevel))-1)<0)==1,"MHITM pm_mlevel signedness");
_Static_assert(sizeof(((struct permonst*)0)->geno)==2,"MHITM pm_geno width");
_Static_assert((((__typeof__(((struct permonst*)0)->geno))-1)<0)==0,"MHITM pm_geno signedness");
_Static_assert(sizeof(((struct permonst*)0)->pmidx)==4,"MHITM pm_pmidx width");
_Static_assert((((__typeof__(((struct permonst*)0)->pmidx))-1)<0)==1,"MHITM pm_pmidx signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_skill)==1,"MHITM cls_oc_skill width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_skill))-1)<0)==1,"MHITM cls_oc_skill signedness");
_Static_assert(sizeof(((struct attack*)0)->aatyp)==1,"MHITM atk_aatyp width");
_Static_assert((((__typeof__(((struct attack*)0)->aatyp))-1)<0)==0,"MHITM atk_aatyp signedness");
_Static_assert(sizeof(((struct attack*)0)->adtyp)==1,"MHITM atk_adtyp width");
_Static_assert((((__typeof__(((struct attack*)0)->adtyp))-1)<0)==0,"MHITM atk_adtyp signedness");
_Static_assert(sizeof(((struct attack*)0)->damn)==1,"MHITM atk_damn width");
_Static_assert((((__typeof__(((struct attack*)0)->damn))-1)<0)==0,"MHITM atk_damn signedness");
_Static_assert(sizeof(((struct attack*)0)->damd)==1,"MHITM atk_damd width");
_Static_assert((((__typeof__(((struct attack*)0)->damd))-1)<0)==0,"MHITM atk_damd signedness");
_Static_assert(sizeof(((struct mhitm_data*)0)->damage)==4,"MHITM mhm_damage width");
_Static_assert((((__typeof__(((struct mhitm_data*)0)->damage))-1)<0)==1,"MHITM mhm_damage signedness");
_Static_assert(sizeof(((struct mhitm_data*)0)->hitflags)==4,"MHITM mhm_hitflags width");
_Static_assert((((__typeof__(((struct mhitm_data*)0)->hitflags))-1)<0)==1,"MHITM mhm_hitflags signedness");
_Static_assert(sizeof(((struct mhitm_data*)0)->done)==1,"MHITM mhm_done width");
_Static_assert((((__typeof__(((struct mhitm_data*)0)->done))-1)<0)==1,"MHITM mhm_done signedness");
_Static_assert(sizeof(((struct mhitm_data*)0)->permdmg)==1,"MHITM mhm_permdmg width");
_Static_assert((((__typeof__(((struct mhitm_data*)0)->permdmg))-1)<0)==1,"MHITM mhm_permdmg signedness");
_Static_assert(sizeof(((struct mhitm_data*)0)->specialdmg)==4,"MHITM mhm_specialdmg width");
_Static_assert((((__typeof__(((struct mhitm_data*)0)->specialdmg))-1)<0)==1,"MHITM mhm_specialdmg signedness");
_Static_assert(sizeof(((struct mhitm_data*)0)->dieroll)==4,"MHITM mhm_dieroll width");
_Static_assert((((__typeof__(((struct mhitm_data*)0)->dieroll))-1)<0)==1,"MHITM mhm_dieroll signedness");
_Static_assert(sizeof(((struct you*)0)->ux)==2,"MHITM u_ux width");
_Static_assert((((__typeof__(((struct you*)0)->ux))-1)<0)==1,"MHITM u_ux signedness");
_Static_assert(sizeof(((struct you*)0)->uy)==2,"MHITM u_uy width");
_Static_assert((((__typeof__(((struct you*)0)->uy))-1)<0)==1,"MHITM u_uy signedness");
_Static_assert(sizeof(((struct you*)0)->ulycn)==4,"MHITM u_ulycn width");
_Static_assert((((__typeof__(((struct you*)0)->ulycn))-1)<0)==1,"MHITM u_ulycn signedness");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4,"MHITM u_umonnum width");
_Static_assert((((__typeof__(((struct you*)0)->umonnum))-1)<0)==1,"MHITM u_umonnum signedness");
_Static_assert(sizeof(((struct you*)0)->usteed)==8,"MHITM u_usteed width");
_Static_assert(sizeof(((struct you*)0)->ustuck)==8,"MHITM u_ustuck width");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8,"MHITM prop_intrinsic width");
_Static_assert((((__typeof__(((struct prop*)0)->intrinsic))-1)<0)==1,"MHITM prop_intrinsic signedness");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8,"MHITM prop_extrinsic width");
_Static_assert((((__typeof__(((struct prop*)0)->extrinsic))-1)<0)==1,"MHITM prop_extrinsic signedness");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8,"MHITM prop_blocked width");
_Static_assert((((__typeof__(((struct prop*)0)->blocked))-1)<0)==1,"MHITM prop_blocked signedness");
_Static_assert(sizeof(((struct rm*)0)->typ)==1,"MHITM rm_typ width");
_Static_assert((((__typeof__(((struct rm*)0)->typ))-1)<0)==1,"MHITM rm_typ signedness");
_Static_assert(sizeof(((coord*)0)->x)==2,"MHITM coord_x width");
_Static_assert((((__typeof__(((coord*)0)->x))-1)<0)==1,"MHITM coord_x signedness");
_Static_assert(sizeof(((coord*)0)->y)==2,"MHITM coord_y width");
_Static_assert((((__typeof__(((coord*)0)->y))-1)<0)==1,"MHITM coord_y signedness");
_Static_assert(sizeof(((struct Gender*)0)->his)==8,"MHITM gender_his width");
_Static_assert(sizeof(gf.far_noise)==1,"MHITM far_noise width");
_Static_assert(sizeof(svm.moves)==8,"MHITM moves width");
_Static_assert(sizeof(gn.noisetime)==8,"MHITM noisetime width");
_Static_assert(sizeof(gn.notonhead)==1,"MHITM notonhead width");
_Static_assert(sizeof(gv.vis)==1,"MHITM vis width");
_Static_assert(sizeof(gs.skipdrin)==1,"MHITM skipdrin width");
_Static_assert(sizeof(gl.last_hider)==4,"MHITM last_hider width");
_Static_assert(sizeof(iflags.last_msg)==4,"MHITM last_msg width");
_Static_assert(sizeof(flags.verbose)==1,"MHITM verbose width");
_Static_assert(sizeof(gm.multi)==8,"MHITM multi width");
_Static_assert(sizeof(gm.mkcorpstat_norevive)==1,"MHITM norevive width");
_Static_assert(sizeof(gz.zombify)==1,"MHITM zombify width");
#undef MHITM_META
#endif
