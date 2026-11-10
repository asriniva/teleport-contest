#ifndef TELEPORT_SPELL_LAYOUT_H
#define TELEPORT_SPELL_LAYOUT_H
#include "hack.h"
#include "artifact.h"
#include <stddef.h>
struct teleport_spell_zap { uchar dir;coordxy x,y;char strength;};
struct teleport_spell_queue {struct teleport_spell_zap q[100];int head,tail,displayed_beam;};
struct spell_meta {const char *name;size_t value;};
#define SP_META(k,v) {#k,(size_t)(v)}
static const struct spell_meta spell_layout[]={
SP_META(pointerSize,sizeof(void*)),
SP_META(intSize,sizeof(int)),
SP_META(longSize,sizeof(long)),
SP_META(booleanSize,sizeof(boolean)),
SP_META(monsterSize,sizeof(struct monst)),
SP_META(objectSize,sizeof(struct obj)),
SP_META(permonstSize,sizeof(struct permonst)),
SP_META(objectClassSize,sizeof(struct objclass)),
SP_META(coordSize,sizeof(coord)),
SP_META(rmSize,sizeof(struct rm)),
SP_META(spellSize,sizeof(struct spell)),
SP_META(commandSize,sizeof(struct _cmd_queue)),
SP_META(propSize,sizeof(struct prop)),
SP_META(menuSize,sizeof(menu_item)),
SP_META(anythingSize,sizeof(anything)),
SP_META(roleSize,sizeof(struct Role)),
SP_META(skillSize,sizeof(struct skills)),
SP_META(dlevelSize,sizeof(d_level)),
SP_META(objdescrSize,sizeof(struct objdescr)),
SP_META(genderSize,sizeof(struct Gender)),
SP_META(zapSize,sizeof(struct teleport_spell_zap)),
SP_META(queueSize,sizeof(struct teleport_spell_queue)),
SP_META(mon_nmon,offsetof(struct monst,nmon)),
SP_META(mon_nmon_size,sizeof(((struct monst*)0)->nmon)),
SP_META(mon_data,offsetof(struct monst,data)),
SP_META(mon_data_size,sizeof(((struct monst*)0)->data)),
SP_META(mon_mx,offsetof(struct monst,mx)),
SP_META(mon_mx_size,sizeof(((struct monst*)0)->mx)),
SP_META(mon_my,offsetof(struct monst,my)),
SP_META(mon_my_size,sizeof(((struct monst*)0)->my)),
SP_META(mon_mhp,offsetof(struct monst,mhp)),
SP_META(mon_mhp_size,sizeof(((struct monst*)0)->mhp)),
SP_META(mon_mintrinsics,offsetof(struct monst,mintrinsics)),
SP_META(mon_mintrinsics_size,sizeof(((struct monst*)0)->mintrinsics)),
SP_META(mon_mextrinsics,offsetof(struct monst,mextrinsics)),
SP_META(mon_mextrinsics_size,sizeof(((struct monst*)0)->mextrinsics)),
SP_META(mon_mtame,offsetof(struct monst,mtame)),
SP_META(mon_mtame_size,sizeof(((struct monst*)0)->mtame)),
SP_META(mon_cham,offsetof(struct monst,cham)),
SP_META(mon_cham_size,sizeof(((struct monst*)0)->cham)),
SP_META(obj_nobj,offsetof(struct obj,nobj)),
SP_META(obj_nobj_size,sizeof(((struct obj*)0)->nobj)),
SP_META(obj_otyp,offsetof(struct obj,otyp)),
SP_META(obj_otyp_size,sizeof(((struct obj*)0)->otyp)),
SP_META(obj_o_id,offsetof(struct obj,o_id)),
SP_META(obj_o_id_size,sizeof(((struct obj*)0)->o_id)),
SP_META(obj_spe,offsetof(struct obj,spe)),
SP_META(obj_spe_size,sizeof(((struct obj*)0)->spe)),
SP_META(obj_spestudied,offsetof(struct obj,spestudied)),
SP_META(obj_spestudied_size,sizeof(((struct obj*)0)->spestudied)),
SP_META(obj_novelidx,offsetof(struct obj,novelidx)),
SP_META(obj_novelidx_size,sizeof(((struct obj*)0)->novelidx)),
SP_META(obj_quan,offsetof(struct obj,quan)),
SP_META(obj_quan_size,sizeof(((struct obj*)0)->quan)),
SP_META(obj_age,offsetof(struct obj,age)),
SP_META(obj_age_size,sizeof(((struct obj*)0)->age)),
SP_META(pm_mflags1,offsetof(struct permonst,mflags1)),
SP_META(pm_mflags1_size,sizeof(((struct permonst*)0)->mflags1)),
SP_META(pm_mflags2,offsetof(struct permonst,mflags2)),
SP_META(pm_mflags2_size,sizeof(((struct permonst*)0)->mflags2)),
SP_META(pm_mlet,offsetof(struct permonst,mlet)),
SP_META(pm_mlet_size,sizeof(((struct permonst*)0)->mlet)),
SP_META(pm_maligntyp,offsetof(struct permonst,maligntyp)),
SP_META(pm_maligntyp_size,sizeof(((struct permonst*)0)->maligntyp)),
SP_META(pm_pmidx,offsetof(struct permonst,pmidx)),
SP_META(pm_pmidx_size,sizeof(((struct permonst*)0)->pmidx)),
SP_META(cls_oc_level,offsetof(struct objclass,oc_level)),
SP_META(cls_oc_level_size,sizeof(((struct objclass*)0)->oc_level)),
SP_META(cls_oc_delay,offsetof(struct objclass,oc_delay)),
SP_META(cls_oc_delay_size,sizeof(((struct objclass*)0)->oc_delay)),
SP_META(cls_oc_skill,offsetof(struct objclass,oc_skill)),
SP_META(cls_oc_skill_size,sizeof(((struct objclass*)0)->oc_skill)),
SP_META(cls_oc_name_idx,offsetof(struct objclass,oc_name_idx)),
SP_META(cls_oc_name_idx_size,sizeof(((struct objclass*)0)->oc_name_idx)),
SP_META(cls_oc_weight,offsetof(struct objclass,oc_weight)),
SP_META(cls_oc_weight_size,sizeof(((struct objclass*)0)->oc_weight)),
SP_META(coord_x,offsetof(coord,x)),
SP_META(coord_x_size,sizeof(((coord*)0)->x)),
SP_META(coord_y,offsetof(coord,y)),
SP_META(coord_y_size,sizeof(((coord*)0)->y)),
SP_META(rm_typ,offsetof(struct rm,typ)),
SP_META(rm_typ_size,sizeof(((struct rm*)0)->typ)),
SP_META(spell_sp_id,offsetof(struct spell,sp_id)),
SP_META(spell_sp_id_size,sizeof(((struct spell*)0)->sp_id)),
SP_META(spell_sp_lev,offsetof(struct spell,sp_lev)),
SP_META(spell_sp_lev_size,sizeof(((struct spell*)0)->sp_lev)),
SP_META(spell_sp_know,offsetof(struct spell,sp_know)),
SP_META(spell_sp_know_size,sizeof(((struct spell*)0)->sp_know)),
SP_META(cmd_typ,offsetof(struct _cmd_queue,typ)),
SP_META(cmd_typ_size,sizeof(((struct _cmd_queue*)0)->typ)),
SP_META(cmd_key,offsetof(struct _cmd_queue,key)),
SP_META(cmd_key_size,sizeof(((struct _cmd_queue*)0)->key)),
SP_META(prop_intrinsic,offsetof(struct prop,intrinsic)),
SP_META(prop_intrinsic_size,sizeof(((struct prop*)0)->intrinsic)),
SP_META(prop_extrinsic,offsetof(struct prop,extrinsic)),
SP_META(prop_extrinsic_size,sizeof(((struct prop*)0)->extrinsic)),
SP_META(prop_blocked,offsetof(struct prop,blocked)),
SP_META(prop_blocked_size,sizeof(((struct prop*)0)->blocked)),
SP_META(menu_item,offsetof(menu_item,item)),
SP_META(menu_item_size,sizeof(((menu_item*)0)->item)),
SP_META(any_a_int,offsetof(anything,a_int)),
SP_META(any_a_int_size,sizeof(((anything*)0)->a_int)),
SP_META(role_mnum,offsetof(struct Role,mnum)),
SP_META(role_mnum_size,sizeof(((struct Role*)0)->mnum)),
SP_META(role_spelbase,offsetof(struct Role,spelbase)),
SP_META(role_spelbase_size,sizeof(((struct Role*)0)->spelbase)),
SP_META(role_spelheal,offsetof(struct Role,spelheal)),
SP_META(role_spelheal_size,sizeof(((struct Role*)0)->spelheal)),
SP_META(role_spelshld,offsetof(struct Role,spelshld)),
SP_META(role_spelshld_size,sizeof(((struct Role*)0)->spelshld)),
SP_META(role_spelarmr,offsetof(struct Role,spelarmr)),
SP_META(role_spelarmr_size,sizeof(((struct Role*)0)->spelarmr)),
SP_META(role_spelstat,offsetof(struct Role,spelstat)),
SP_META(role_spelstat_size,sizeof(((struct Role*)0)->spelstat)),
SP_META(role_spelspec,offsetof(struct Role,spelspec)),
SP_META(role_spelspec_size,sizeof(((struct Role*)0)->spelspec)),
SP_META(role_spelsbon,offsetof(struct Role,spelsbon)),
SP_META(role_spelsbon_size,sizeof(((struct Role*)0)->spelsbon)),
SP_META(u_ux,offsetof(struct you,ux)),
SP_META(u_ux_size,sizeof(((struct you*)0)->ux)),
SP_META(u_uy,offsetof(struct you,uy)),
SP_META(u_uy_size,sizeof(((struct you*)0)->uy)),
SP_META(u_dx,offsetof(struct you,dx)),
SP_META(u_dx_size,sizeof(((struct you*)0)->dx)),
SP_META(u_dy,offsetof(struct you,dy)),
SP_META(u_dy_size,sizeof(((struct you*)0)->dy)),
SP_META(u_dz,offsetof(struct you,dz)),
SP_META(u_dz_size,sizeof(((struct you*)0)->dz)),
SP_META(u_ualign,offsetof(struct you,ualign)),
SP_META(u_ualign_size,sizeof(((struct you*)0)->ualign)),
SP_META(u_uz,offsetof(struct you,uz)),
SP_META(u_uz_size,sizeof(((struct you*)0)->uz)),
SP_META(u_uprops,offsetof(struct you,uprops)),
SP_META(u_uprops_size,sizeof(((struct you*)0)->uprops)),
SP_META(u_weapon_skills,offsetof(struct you,weapon_skills)),
SP_META(u_weapon_skills_size,sizeof(((struct you*)0)->weapon_skills)),
SP_META(u_ustuck,offsetof(struct you,ustuck)),
SP_META(u_ustuck_size,sizeof(((struct you*)0)->ustuck)),
SP_META(u_umonnum,offsetof(struct you,umonnum)),
SP_META(u_umonnum_size,sizeof(((struct you*)0)->umonnum)),
SP_META(u_umonster,offsetof(struct you,umonster)),
SP_META(u_umonster_size,sizeof(((struct you*)0)->umonster)),
SP_META(u_ulevel,offsetof(struct you,ulevel)),
SP_META(u_ulevel_size,sizeof(((struct you*)0)->ulevel)),
SP_META(u_uen,offsetof(struct you,uen)),
SP_META(u_uen_size,sizeof(((struct you*)0)->uen)),
SP_META(u_uenmax,offsetof(struct you,uenmax)),
SP_META(u_uenmax_size,sizeof(((struct you*)0)->uenmax)),
SP_META(u_uenpeak,offsetof(struct you,uenpeak)),
SP_META(u_uenpeak_size,sizeof(((struct you*)0)->uenpeak)),
SP_META(u_uhunger,offsetof(struct you,uhunger)),
SP_META(u_uhunger_size,sizeof(((struct you*)0)->uhunger)),
SP_META(u_uac,offsetof(struct you,uac)),
SP_META(u_uac_size,sizeof(((struct you*)0)->uac)),
SP_META(u_uspellprot,offsetof(struct you,uspellprot)),
SP_META(u_uspellprot_size,sizeof(((struct you*)0)->uspellprot)),
SP_META(u_uspmtime,offsetof(struct you,uspmtime)),
SP_META(u_uspmtime_size,sizeof(((struct you*)0)->uspmtime)),
SP_META(u_usptime,offsetof(struct you,usptime)),
SP_META(u_usptime_size,sizeof(((struct you*)0)->usptime)),
SP_META(u_udg_cnt,offsetof(struct you,udg_cnt)),
SP_META(u_udg_cnt_size,sizeof(((struct you*)0)->udg_cnt)),
SP_META(u_uconduct,offsetof(struct you,uconduct)),
SP_META(u_uconduct_size,sizeof(((struct you*)0)->uconduct)),
SP_META(gender_him,offsetof(struct Gender,him)),
SP_META(gender_him_size,sizeof(((struct Gender*)0)->him)),
SP_META(align_type,offsetof(align,type)),
SP_META(align_type_size,sizeof(((align*)0)->type)),
SP_META(skill_skill,offsetof(struct skills,skill)),
SP_META(skill_skill_size,sizeof(((struct skills*)0)->skill)),
SP_META(dlevel_dnum,offsetof(d_level,dnum)),
SP_META(dlevel_dnum_size,sizeof(((d_level*)0)->dnum)),
SP_META(dlevel_dlevel,offsetof(d_level,dlevel)),
SP_META(dlevel_dlevel_size,sizeof(((d_level*)0)->dlevel)),
SP_META(descr_oc_name,offsetof(struct objdescr,oc_name)),
SP_META(descr_oc_name_size,sizeof(((struct objdescr*)0)->oc_name)),
SP_META(zap_dir,offsetof(struct teleport_spell_zap,dir)),
SP_META(zap_dir_size,sizeof(((struct teleport_spell_zap*)0)->dir)),
SP_META(zap_x,offsetof(struct teleport_spell_zap,x)),
SP_META(zap_x_size,sizeof(((struct teleport_spell_zap*)0)->x)),
SP_META(zap_y,offsetof(struct teleport_spell_zap,y)),
SP_META(zap_y_size,sizeof(((struct teleport_spell_zap*)0)->y)),
SP_META(zap_strength,offsetof(struct teleport_spell_zap,strength)),
SP_META(zap_strength_size,sizeof(((struct teleport_spell_zap*)0)->strength)),
SP_META(queue_q,offsetof(struct teleport_spell_queue,q)),
SP_META(queue_q_size,sizeof(((struct teleport_spell_queue*)0)->q)),
SP_META(queue_head,offsetof(struct teleport_spell_queue,head)),
SP_META(queue_head_size,sizeof(((struct teleport_spell_queue*)0)->head)),
SP_META(queue_tail,offsetof(struct teleport_spell_queue,tail)),
SP_META(queue_tail_size,sizeof(((struct teleport_spell_queue*)0)->tail)),
SP_META(queue_displayed_beam,offsetof(struct teleport_spell_queue,displayed_beam)),
SP_META(queue_displayed_beam_size,sizeof(((struct teleport_spell_queue*)0)->displayed_beam)),
SP_META(youmonst,offsetof(__typeof__(gy),youmonst)),
SP_META(youmonst_size,sizeof(gy.youmonst)),
SP_META(spbook,offsetof(__typeof__(svc),context.spbook)),
SP_META(spbook_size,sizeof(svc.context.spbook)),
SP_META(book,offsetof(__typeof__(svc),context.spbook.book)),
SP_META(book_size,sizeof(svc.context.spbook.book)),
SP_META(book_oid,offsetof(__typeof__(svc),context.spbook.o_id)),
SP_META(book_oid_size,sizeof(svc.context.spbook.o_id)),
SP_META(book_delay,offsetof(__typeof__(svc),context.spbook.delay)),
SP_META(book_delay_size,sizeof(svc.context.spbook.delay)),
SP_META(forcefight,offsetof(__typeof__(svc),context.forcefight)),
SP_META(forcefight_size,sizeof(svc.context.forcefight)),
SP_META(occupation,offsetof(__typeof__(go),occupation)),
SP_META(occupation_size,sizeof(go.occupation)),
SP_META(multi,offsetof(__typeof__(gm),multi)),
SP_META(multi_size,sizeof(gm.multi)),
SP_META(multi_reason,offsetof(__typeof__(gm),multi_reason)),
SP_META(multi_reason_size,sizeof(gm.multi_reason)),
SP_META(nomovemsg,offsetof(__typeof__(gn),nomovemsg)),
SP_META(nomovemsg_size,sizeof(gn.nomovemsg)),
SP_META(notonhead,offsetof(__typeof__(gn),notonhead)),
SP_META(notonhead_size,sizeof(gn.notonhead)),
SP_META(invent,offsetof(__typeof__(gi),invent)),
SP_META(invent_size,sizeof(gi.invent)),
SP_META(moves,offsetof(__typeof__(svm),moves)),
SP_META(moves_size,sizeof(svm.moves)),
SP_META(spl_book,offsetof(__typeof__(svs),spl_book)),
SP_META(spl_book_size,sizeof(svs.spl_book)),
SP_META(spl_orderindx,offsetof(__typeof__(gs),spl_orderindx)),
SP_META(spl_orderindx_size,sizeof(gs.spl_orderindx)),
SP_META(spl_sortmode,offsetof(__typeof__(gs),spl_sortmode)),
SP_META(spl_sortmode_size,sizeof(gs.spl_sortmode)),
SP_META(bases,offsetof(__typeof__(svb),bases)),
SP_META(bases_size,sizeof(svb.bases)),
SP_META(you_role,offsetof(__typeof__(gu),urole)),
SP_META(you_role_size,sizeof(gu.urole)),
SP_META(bhitpos,offsetof(__typeof__(gb),bhitpos)),
SP_META(bhitpos_size,sizeof(gb.bhitpos)),
SP_META(zeroany,offsetof(__typeof__(cg),zeroany)),
SP_META(zeroany_size,sizeof(cg.zeroany)),
SP_META(menu_style,offsetof(__typeof__(flags),menu_style)),
SP_META(menu_style_size,sizeof(flags.menu_style)),
SP_META(menu_tab_sep,offsetof(__typeof__(iflags),menu_tab_sep)),
SP_META(menu_tab_sep_size,sizeof(iflags.menu_tab_sep)),
SP_META(wizard,offsetof(__typeof__(flags),debug)),
SP_META(wizard_size,sizeof(flags.debug)),
SP_META(botl,offsetof(__typeof__(disp),botl)),
SP_META(botl_size,sizeof(disp.botl)),
SP_META(locations,offsetof(__typeof__(svl),level.locations)),
SP_META(locations_size,sizeof(svl.level.locations)),
SP_META(monsters,offsetof(__typeof__(svl),level.monsters)),
SP_META(monsters_size,sizeof(svl.level.monsters)),
SP_META(vizArray,offsetof(__typeof__(gv),viz_array)),
SP_META(vizArray_size,sizeof(gv.viz_array)),
SP_META(literate,offsetof(__typeof__(u),uconduct.literate)),
SP_META(literate_size,sizeof(u.uconduct.literate)),
SP_META(female,offsetof(__typeof__(flags),female)),
SP_META(female_size,sizeof(flags.female)),
SP_META(water_level,offsetof(__typeof__(svd),dungeon_topology.d_water_level)),
SP_META(water_level_size,sizeof(svd.dungeon_topology.d_water_level)),
SP_META(ACH_INVK,ACH_INVK),
SP_META(ACH_NOVL,ACH_NOVL),
SP_META(AD_ELEC,AD_ELEC),
SP_META(AD_WRAP,AD_WRAP),
SP_META(ANTIMAGIC,ANTIMAGIC),
SP_META(ATR_NONE,ATR_NONE),
SP_META(AT_ENGL,AT_ENGL),
SP_META(A_INT,A_INT),
SP_META(A_STR,A_STR),
SP_META(A_WIS,A_WIS),
SP_META(BELL_OF_OPENING,BELL_OF_OPENING),
SP_META(BLINDED,BLINDED),
SP_META(BUFSZ,BUFSZ),
SP_META(CANDELABRUM_OF_INVOCATION,CANDELABRUM_OF_INVOCATION),
SP_META(CLAIRVOYANT,CLAIRVOYANT),
SP_META(CLOUD,CLOUD),
SP_META(CMDQ_KEY,CMDQ_KEY),
SP_META(COLNO,COLNO),
SP_META(CONFUSION,CONFUSION),
SP_META(COPPER,COPPER),
SP_META(CORNUTHAUM,CORNUTHAUM),
SP_META(COULD_SEE,COULD_SEE),
SP_META(CQ_REPEAT,CQ_REPEAT),
SP_META(DBWALL,DBWALL),
SP_META(DISP_BEAM,DISP_BEAM),
SP_META(DISP_CHANGE,DISP_CHANGE),
SP_META(DISP_END,DISP_END),
SP_META(DOOR,DOOR),
SP_META(DRAWBRIDGE_UP,DRAWBRIDGE_UP),
SP_META(D_CLOSED,D_CLOSED),
SP_META(D_ISOPEN,D_ISOPEN),
SP_META(D_LOCKED,D_LOCKED),
SP_META(ECMD_FAIL,ECMD_FAIL),
SP_META(ECMD_OK,ECMD_OK),
SP_META(ECMD_TIME,ECMD_TIME),
SP_META(EF_GREASE,EF_GREASE),
SP_META(EF_VERBOSE,EF_VERBOSE),
SP_META(ERODE_CORRODE,ERODE_CORRODE),
SP_META(EXPL_FIERY,EXPL_FIERY),
SP_META(EXPL_FROSTY,EXPL_FROSTY),
SP_META(EYE,EYE),
SP_META(FACE,FACE),
SP_META(GAUNTLETS_OF_POWER,GAUNTLETS_OF_POWER),
SP_META(GLYPH_CMAP_C_OFF,GLYPH_CMAP_C_OFF),
SP_META(GLYPH_CMAP_OFF,GLYPH_CMAP_OFF),
SP_META(GOLD,GOLD),
SP_META(HALF_PHDAM,HALF_PHDAM),
SP_META(HALLUC,HALLUC),
SP_META(HALLUC_RES,HALLUC_RES),
SP_META(HEAD,HEAD),
SP_META(HELMET,HELMET),
SP_META(IN_SIGHT,IN_SIGHT),
SP_META(IRON,IRON),
SP_META(IRON_SHOES,IRON_SHOES),
SP_META(KILLED_BY_AN,KILLED_BY_AN),
SP_META(LARGE_SHIELD,LARGE_SHIELD),
SP_META(LAVAPOOL,LAVAPOOL),
SP_META(LENSES,LENSES),
SP_META(LL_CONDUCT,LL_CONDUCT),
SP_META(M1_ANIMAL,M1_ANIMAL),
SP_META(M1_HUMANOID,M1_HUMANOID),
SP_META(M1_NOEYES,M1_NOEYES),
SP_META(M2_UNDEAD,M2_UNDEAD),
SP_META(MAXSPELL,MAXSPELL),
SP_META(MAX_SPELL_STUDY,MAX_SPELL_STUDY),
SP_META(MENU_BEHAVE_STANDARD,MENU_BEHAVE_STANDARD),
SP_META(MENU_ITEMFLAGS_NONE,MENU_ITEMFLAGS_NONE),
SP_META(MENU_ITEMFLAGS_SELECTED,MENU_ITEMFLAGS_SELECTED),
SP_META(MENU_TRADITIONAL,MENU_TRADITIONAL),
SP_META(METAL,METAL),
SP_META(MITHRIL,MITHRIL),
SP_META(MOAT,MOAT),
SP_META(MR_ELEC,MR_ELEC),
SP_META(NHW_MENU,NHW_MENU),
SP_META(NODIR,NODIR),
SP_META(NO_COLOR,NO_COLOR),
SP_META(NO_KILLER_PREFIX,NO_KILLER_PREFIX),
SP_META(NO_MINVENT,NO_MINVENT),
SP_META(NO_SPELL,NO_SPELL),
SP_META(NUMMONS,NUMMONS),
SP_META(N_DIRS,N_DIRS),
SP_META(PICK_NONE,PICK_NONE),
SP_META(PICK_ONE,PICK_ONE),
SP_META(PLATE_MAIL,PLATE_MAIL),
SP_META(PLATINUM,PLATINUM),
SP_META(PM_AIR_ELEMENTAL,PM_AIR_ELEMENTAL),
SP_META(PM_CYCLOPS,PM_CYCLOPS),
SP_META(PM_FLOATING_EYE,PM_FLOATING_EYE),
SP_META(PM_FOG_CLOUD,PM_FOG_CLOUD),
SP_META(PM_HUMAN,PM_HUMAN),
SP_META(PM_KNIGHT,PM_KNIGHT),
SP_META(PM_MASTER_LICH,PM_MASTER_LICH),
SP_META(PM_MONK,PM_MONK),
SP_META(PM_NALFESHNEE,PM_NALFESHNEE),
SP_META(PM_VAMPIRE,PM_VAMPIRE),
SP_META(PM_VAMPIRE_LEADER,PM_VAMPIRE_LEADER),
SP_META(PM_VLAD_THE_IMPALER,PM_VLAD_THE_IMPALER),
SP_META(PM_WIZARD,PM_WIZARD),
SP_META(POISON_RES,POISON_RES),
SP_META(POOL,POOL),
SP_META(P_ATTACK_SPELL,P_ATTACK_SPELL),
SP_META(P_BASIC,P_BASIC),
SP_META(P_CLERIC_SPELL,P_CLERIC_SPELL),
SP_META(P_DIVINATION_SPELL,P_DIVINATION_SPELL),
SP_META(P_ENCHANTMENT_SPELL,P_ENCHANTMENT_SPELL),
SP_META(P_ESCAPE_SPELL,P_ESCAPE_SPELL),
SP_META(P_EXPERT,P_EXPERT),
SP_META(P_GRAND_MASTER,P_GRAND_MASTER),
SP_META(P_HEALING_SPELL,P_HEALING_SPELL),
SP_META(P_ISRESTRICTED,P_ISRESTRICTED),
SP_META(P_MASTER,P_MASTER),
SP_META(P_MATTER_SPELL,P_MATTER_SPELL),
SP_META(P_NONE,P_NONE),
SP_META(P_SKILLED,P_SKILLED),
SP_META(P_UNSKILLED,P_UNSKILLED),
SP_META(QBUFSZ,QBUFSZ),
SP_META(QUARTERSTAFF,QUARTERSTAFF),
SP_META(ROBE,ROBE),
SP_META(ROOM,ROOM),
SP_META(ROWNO,ROWNO),
SP_META(SHOCK_RES,SHOCK_RES),
SP_META(SICK,SICK),
SP_META(SILVER,SILVER),
SP_META(SLEEP_RES,SLEEP_RES),
SP_META(SLIMED,SLIMED),
SP_META(SMALL_SHIELD,SMALL_SHIELD),
SP_META(SPBOOK_CLASS,SPBOOK_CLASS),
SP_META(SPE_BLANK_PAPER,SPE_BLANK_PAPER),
SP_META(SPE_BOOK_OF_THE_DEAD,SPE_BOOK_OF_THE_DEAD),
SP_META(SPE_CANCELLATION,SPE_CANCELLATION),
SP_META(SPE_CAUSE_FEAR,SPE_CAUSE_FEAR),
SP_META(SPE_CHAIN_LIGHTNING,SPE_CHAIN_LIGHTNING),
SP_META(SPE_CHARM_MONSTER,SPE_CHARM_MONSTER),
SP_META(SPE_CLAIRVOYANCE,SPE_CLAIRVOYANCE),
SP_META(SPE_CONE_OF_COLD,SPE_CONE_OF_COLD),
SP_META(SPE_CONFUSE_MONSTER,SPE_CONFUSE_MONSTER),
SP_META(SPE_CREATE_FAMILIAR,SPE_CREATE_FAMILIAR),
SP_META(SPE_CREATE_MONSTER,SPE_CREATE_MONSTER),
SP_META(SPE_CURE_BLINDNESS,SPE_CURE_BLINDNESS),
SP_META(SPE_CURE_SICKNESS,SPE_CURE_SICKNESS),
SP_META(SPE_DETECT_FOOD,SPE_DETECT_FOOD),
SP_META(SPE_DETECT_MONSTERS,SPE_DETECT_MONSTERS),
SP_META(SPE_DETECT_TREASURE,SPE_DETECT_TREASURE),
SP_META(SPE_DETECT_UNSEEN,SPE_DETECT_UNSEEN),
SP_META(SPE_DIG,SPE_DIG),
SP_META(SPE_DRAIN_LIFE,SPE_DRAIN_LIFE),
SP_META(SPE_EXTRA_HEALING,SPE_EXTRA_HEALING),
SP_META(SPE_FINGER_OF_DEATH,SPE_FINGER_OF_DEATH),
SP_META(SPE_FIREBALL,SPE_FIREBALL),
SP_META(SPE_FORCE_BOLT,SPE_FORCE_BOLT),
SP_META(SPE_HASTE_SELF,SPE_HASTE_SELF),
SP_META(SPE_HEALING,SPE_HEALING),
SP_META(SPE_IDENTIFY,SPE_IDENTIFY),
SP_META(SPE_INVISIBILITY,SPE_INVISIBILITY),
SP_META(SPE_JUMPING,SPE_JUMPING),
SP_META(SPE_KNOCK,SPE_KNOCK),
SP_META(SPE_LEVITATION,SPE_LEVITATION),
SP_META(SPE_LIGHT,SPE_LIGHT),
SP_META(SPE_MAGIC_MAPPING,SPE_MAGIC_MAPPING),
SP_META(SPE_MAGIC_MISSILE,SPE_MAGIC_MISSILE),
SP_META(SPE_NOVEL,SPE_NOVEL),
SP_META(SPE_POLYMORPH,SPE_POLYMORPH),
SP_META(SPE_PROTECTION,SPE_PROTECTION),
SP_META(SPE_REMOVE_CURSE,SPE_REMOVE_CURSE),
SP_META(SPE_RESTORE_ABILITY,SPE_RESTORE_ABILITY),
SP_META(SPE_SLEEP,SPE_SLEEP),
SP_META(SPE_SLOW_MONSTER,SPE_SLOW_MONSTER),
SP_META(SPE_STONE_TO_FLESH,SPE_STONE_TO_FLESH),
SP_META(SPE_TELEPORT_AWAY,SPE_TELEPORT_AWAY),
SP_META(SPE_TURN_UNDEAD,SPE_TURN_UNDEAD),
SP_META(SPE_WIZARD_LOCK,SPE_WIZARD_LOCK),
SP_META(SPINE,SPINE),
SP_META(STONE,STONE),
SP_META(STUNNED,STUNNED),
SP_META(S_EYE,S_EYE),
SP_META(S_LIGHT,S_LIGHT),
SP_META(S_VORTEX,S_VORTEX),
SP_META(S_digbeam,S_digbeam),
SP_META(S_goodpos,S_goodpos),
SP_META(TIMEOUT,TIMEOUT),
SP_META(TREE,TREE),
SP_META(UNKNOWN_SPELL,UNKNOWN_SPELL),
SP_META(XKILL_GIVEMSG,XKILL_GIVEMSG),
SP_META(spe_Forgotten,spe_Forgotten),
SP_META(spe_Fresh,spe_Fresh),
SP_META(spe_GoingStale,spe_GoingStale),
SP_META(spe_Unknown,spe_Unknown),
};
#undef SP_META
_Static_assert(sizeof(((struct monst*)0)->nmon)==8,"SPELL mon_nmon width");
_Static_assert(sizeof(((struct monst*)0)->data)==8,"SPELL mon_data width");
_Static_assert(sizeof(((struct monst*)0)->mx)==2,"SPELL mon_mx width");
_Static_assert((((__typeof__(((struct monst*)0)->mx))-1)<0)==1,"SPELL mon_mx signedness");
_Static_assert(sizeof(((struct monst*)0)->my)==2,"SPELL mon_my width");
_Static_assert((((__typeof__(((struct monst*)0)->my))-1)<0)==1,"SPELL mon_my signedness");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4,"SPELL mon_mhp width");
_Static_assert((((__typeof__(((struct monst*)0)->mhp))-1)<0)==1,"SPELL mon_mhp signedness");
_Static_assert(sizeof(((struct monst*)0)->mintrinsics)==2,"SPELL mon_mintrinsics width");
_Static_assert((((__typeof__(((struct monst*)0)->mintrinsics))-1)<0)==0,"SPELL mon_mintrinsics signedness");
_Static_assert(sizeof(((struct monst*)0)->mextrinsics)==2,"SPELL mon_mextrinsics width");
_Static_assert((((__typeof__(((struct monst*)0)->mextrinsics))-1)<0)==0,"SPELL mon_mextrinsics signedness");
_Static_assert(sizeof(((struct monst*)0)->mtame)==1,"SPELL mon_mtame width");
_Static_assert((((__typeof__(((struct monst*)0)->mtame))-1)<0)==1,"SPELL mon_mtame signedness");
_Static_assert(sizeof(((struct monst*)0)->cham)==2,"SPELL mon_cham width");
_Static_assert((((__typeof__(((struct monst*)0)->cham))-1)<0)==1,"SPELL mon_cham signedness");
_Static_assert(sizeof(((struct obj*)0)->nobj)==8,"SPELL obj_nobj width");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2,"SPELL obj_otyp width");
_Static_assert((((__typeof__(((struct obj*)0)->otyp))-1)<0)==1,"SPELL obj_otyp signedness");
_Static_assert(sizeof(((struct obj*)0)->o_id)==4,"SPELL obj_o_id width");
_Static_assert((((__typeof__(((struct obj*)0)->o_id))-1)<0)==0,"SPELL obj_o_id signedness");
_Static_assert(sizeof(((struct obj*)0)->spe)==1,"SPELL obj_spe width");
_Static_assert((((__typeof__(((struct obj*)0)->spe))-1)<0)==1,"SPELL obj_spe signedness");
_Static_assert(sizeof(((struct obj*)0)->spestudied)==4,"SPELL obj_spestudied width");
_Static_assert((((__typeof__(((struct obj*)0)->spestudied))-1)<0)==1,"SPELL obj_spestudied signedness");
_Static_assert(sizeof(((struct obj*)0)->novelidx)==4,"SPELL obj_novelidx width");
_Static_assert((((__typeof__(((struct obj*)0)->novelidx))-1)<0)==1,"SPELL obj_novelidx signedness");
_Static_assert(sizeof(((struct obj*)0)->quan)==8,"SPELL obj_quan width");
_Static_assert((((__typeof__(((struct obj*)0)->quan))-1)<0)==1,"SPELL obj_quan signedness");
_Static_assert(sizeof(((struct obj*)0)->age)==8,"SPELL obj_age width");
_Static_assert((((__typeof__(((struct obj*)0)->age))-1)<0)==1,"SPELL obj_age signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8,"SPELL pm_mflags1 width");
_Static_assert((((__typeof__(((struct permonst*)0)->mflags1))-1)<0)==0,"SPELL pm_mflags1 signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8,"SPELL pm_mflags2 width");
_Static_assert((((__typeof__(((struct permonst*)0)->mflags2))-1)<0)==0,"SPELL pm_mflags2 signedness");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1,"SPELL pm_mlet width");
_Static_assert((((__typeof__(((struct permonst*)0)->mlet))-1)<0)==1,"SPELL pm_mlet signedness");
_Static_assert(sizeof(((struct permonst*)0)->maligntyp)==1,"SPELL pm_maligntyp width");
_Static_assert((((__typeof__(((struct permonst*)0)->maligntyp))-1)<0)==1,"SPELL pm_maligntyp signedness");
_Static_assert(sizeof(((struct permonst*)0)->pmidx)==4,"SPELL pm_pmidx width");
_Static_assert((((__typeof__(((struct permonst*)0)->pmidx))-1)<0)==1,"SPELL pm_pmidx signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_level)==1,"SPELL cls_oc_level width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_level))-1)<0)==1,"SPELL cls_oc_level signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_delay)==1,"SPELL cls_oc_delay width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_delay))-1)<0)==1,"SPELL cls_oc_delay signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_skill)==1,"SPELL cls_oc_skill width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_skill))-1)<0)==1,"SPELL cls_oc_skill signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_name_idx)==2,"SPELL cls_oc_name_idx width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_name_idx))-1)<0)==1,"SPELL cls_oc_name_idx signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_weight)==4,"SPELL cls_oc_weight width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_weight))-1)<0)==0,"SPELL cls_oc_weight signedness");
_Static_assert(sizeof(((coord*)0)->x)==2,"SPELL coord_x width");
_Static_assert((((__typeof__(((coord*)0)->x))-1)<0)==1,"SPELL coord_x signedness");
_Static_assert(sizeof(((coord*)0)->y)==2,"SPELL coord_y width");
_Static_assert((((__typeof__(((coord*)0)->y))-1)<0)==1,"SPELL coord_y signedness");
_Static_assert(sizeof(((struct rm*)0)->typ)==1,"SPELL rm_typ width");
_Static_assert((((__typeof__(((struct rm*)0)->typ))-1)<0)==1,"SPELL rm_typ signedness");
_Static_assert(sizeof(((struct spell*)0)->sp_id)==2,"SPELL spell_sp_id width");
_Static_assert((((__typeof__(((struct spell*)0)->sp_id))-1)<0)==1,"SPELL spell_sp_id signedness");
_Static_assert(sizeof(((struct spell*)0)->sp_lev)==2,"SPELL spell_sp_lev width");
_Static_assert((((__typeof__(((struct spell*)0)->sp_lev))-1)<0)==1,"SPELL spell_sp_lev signedness");
_Static_assert(sizeof(((struct spell*)0)->sp_know)==4,"SPELL spell_sp_know width");
_Static_assert((((__typeof__(((struct spell*)0)->sp_know))-1)<0)==1,"SPELL spell_sp_know signedness");
_Static_assert(sizeof(((struct _cmd_queue*)0)->typ)==4,"SPELL cmd_typ width");
_Static_assert((((__typeof__(((struct _cmd_queue*)0)->typ))-1)<0)==1,"SPELL cmd_typ signedness");
_Static_assert(sizeof(((struct _cmd_queue*)0)->key)==1,"SPELL cmd_key width");
_Static_assert((((__typeof__(((struct _cmd_queue*)0)->key))-1)<0)==1,"SPELL cmd_key signedness");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8,"SPELL prop_intrinsic width");
_Static_assert((((__typeof__(((struct prop*)0)->intrinsic))-1)<0)==1,"SPELL prop_intrinsic signedness");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8,"SPELL prop_extrinsic width");
_Static_assert((((__typeof__(((struct prop*)0)->extrinsic))-1)<0)==1,"SPELL prop_extrinsic signedness");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8,"SPELL prop_blocked width");
_Static_assert((((__typeof__(((struct prop*)0)->blocked))-1)<0)==1,"SPELL prop_blocked signedness");
_Static_assert(sizeof(((anything*)0)->a_int)==4,"SPELL any_a_int width");
_Static_assert((((__typeof__(((anything*)0)->a_int))-1)<0)==1,"SPELL any_a_int signedness");
_Static_assert(sizeof(((struct Role*)0)->mnum)==2,"SPELL role_mnum width");
_Static_assert((((__typeof__(((struct Role*)0)->mnum))-1)<0)==1,"SPELL role_mnum signedness");
_Static_assert(sizeof(((struct Role*)0)->spelbase)==4,"SPELL role_spelbase width");
_Static_assert((((__typeof__(((struct Role*)0)->spelbase))-1)<0)==1,"SPELL role_spelbase signedness");
_Static_assert(sizeof(((struct Role*)0)->spelheal)==4,"SPELL role_spelheal width");
_Static_assert((((__typeof__(((struct Role*)0)->spelheal))-1)<0)==1,"SPELL role_spelheal signedness");
_Static_assert(sizeof(((struct Role*)0)->spelshld)==4,"SPELL role_spelshld width");
_Static_assert((((__typeof__(((struct Role*)0)->spelshld))-1)<0)==1,"SPELL role_spelshld signedness");
_Static_assert(sizeof(((struct Role*)0)->spelarmr)==4,"SPELL role_spelarmr width");
_Static_assert((((__typeof__(((struct Role*)0)->spelarmr))-1)<0)==1,"SPELL role_spelarmr signedness");
_Static_assert(sizeof(((struct Role*)0)->spelstat)==4,"SPELL role_spelstat width");
_Static_assert((((__typeof__(((struct Role*)0)->spelstat))-1)<0)==1,"SPELL role_spelstat signedness");
_Static_assert(sizeof(((struct Role*)0)->spelspec)==4,"SPELL role_spelspec width");
_Static_assert((((__typeof__(((struct Role*)0)->spelspec))-1)<0)==1,"SPELL role_spelspec signedness");
_Static_assert(sizeof(((struct Role*)0)->spelsbon)==4,"SPELL role_spelsbon width");
_Static_assert((((__typeof__(((struct Role*)0)->spelsbon))-1)<0)==1,"SPELL role_spelsbon signedness");
_Static_assert(sizeof(((struct you*)0)->ux)==2,"SPELL u_ux width");
_Static_assert((((__typeof__(((struct you*)0)->ux))-1)<0)==1,"SPELL u_ux signedness");
_Static_assert(sizeof(((struct you*)0)->uy)==2,"SPELL u_uy width");
_Static_assert((((__typeof__(((struct you*)0)->uy))-1)<0)==1,"SPELL u_uy signedness");
_Static_assert(sizeof(((struct you*)0)->dx)==4,"SPELL u_dx width");
_Static_assert((((__typeof__(((struct you*)0)->dx))-1)<0)==1,"SPELL u_dx signedness");
_Static_assert(sizeof(((struct you*)0)->dy)==4,"SPELL u_dy width");
_Static_assert((((__typeof__(((struct you*)0)->dy))-1)<0)==1,"SPELL u_dy signedness");
_Static_assert(sizeof(((struct you*)0)->dz)==4,"SPELL u_dz width");
_Static_assert((((__typeof__(((struct you*)0)->dz))-1)<0)==1,"SPELL u_dz signedness");
_Static_assert(sizeof(((struct you*)0)->ustuck)==8,"SPELL u_ustuck width");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4,"SPELL u_umonnum width");
_Static_assert((((__typeof__(((struct you*)0)->umonnum))-1)<0)==1,"SPELL u_umonnum signedness");
_Static_assert(sizeof(((struct you*)0)->umonster)==4,"SPELL u_umonster width");
_Static_assert((((__typeof__(((struct you*)0)->umonster))-1)<0)==1,"SPELL u_umonster signedness");
_Static_assert(sizeof(((struct you*)0)->ulevel)==4,"SPELL u_ulevel width");
_Static_assert((((__typeof__(((struct you*)0)->ulevel))-1)<0)==1,"SPELL u_ulevel signedness");
_Static_assert(sizeof(((struct you*)0)->uen)==4,"SPELL u_uen width");
_Static_assert((((__typeof__(((struct you*)0)->uen))-1)<0)==1,"SPELL u_uen signedness");
_Static_assert(sizeof(((struct you*)0)->uenmax)==4,"SPELL u_uenmax width");
_Static_assert((((__typeof__(((struct you*)0)->uenmax))-1)<0)==1,"SPELL u_uenmax signedness");
_Static_assert(sizeof(((struct you*)0)->uenpeak)==4,"SPELL u_uenpeak width");
_Static_assert((((__typeof__(((struct you*)0)->uenpeak))-1)<0)==1,"SPELL u_uenpeak signedness");
_Static_assert(sizeof(((struct you*)0)->uhunger)==4,"SPELL u_uhunger width");
_Static_assert((((__typeof__(((struct you*)0)->uhunger))-1)<0)==1,"SPELL u_uhunger signedness");
_Static_assert(sizeof(((struct you*)0)->uac)==1,"SPELL u_uac width");
_Static_assert((((__typeof__(((struct you*)0)->uac))-1)<0)==1,"SPELL u_uac signedness");
_Static_assert(sizeof(((struct you*)0)->uspellprot)==1,"SPELL u_uspellprot width");
_Static_assert((((__typeof__(((struct you*)0)->uspellprot))-1)<0)==0,"SPELL u_uspellprot signedness");
_Static_assert(sizeof(((struct you*)0)->uspmtime)==1,"SPELL u_uspmtime width");
_Static_assert((((__typeof__(((struct you*)0)->uspmtime))-1)<0)==0,"SPELL u_uspmtime signedness");
_Static_assert(sizeof(((struct you*)0)->usptime)==1,"SPELL u_usptime width");
_Static_assert((((__typeof__(((struct you*)0)->usptime))-1)<0)==0,"SPELL u_usptime signedness");
_Static_assert(sizeof(((struct you*)0)->udg_cnt)==4,"SPELL u_udg_cnt width");
_Static_assert((((__typeof__(((struct you*)0)->udg_cnt))-1)<0)==0,"SPELL u_udg_cnt signedness");
_Static_assert(sizeof(((struct Gender*)0)->him)==8,"SPELL gender_him width");
_Static_assert(sizeof(((align*)0)->type)==1,"SPELL align_type width");
_Static_assert((((__typeof__(((align*)0)->type))-1)<0)==1,"SPELL align_type signedness");
_Static_assert(sizeof(((struct skills*)0)->skill)==2,"SPELL skill_skill width");
_Static_assert((((__typeof__(((struct skills*)0)->skill))-1)<0)==1,"SPELL skill_skill signedness");
_Static_assert(sizeof(((d_level*)0)->dnum)==2,"SPELL dlevel_dnum width");
_Static_assert((((__typeof__(((d_level*)0)->dnum))-1)<0)==1,"SPELL dlevel_dnum signedness");
_Static_assert(sizeof(((d_level*)0)->dlevel)==2,"SPELL dlevel_dlevel width");
_Static_assert((((__typeof__(((d_level*)0)->dlevel))-1)<0)==1,"SPELL dlevel_dlevel signedness");
_Static_assert(sizeof(((struct objdescr*)0)->oc_name)==8,"SPELL descr_oc_name width");
_Static_assert(sizeof(((struct teleport_spell_zap*)0)->dir)==1,"SPELL zap_dir width");
_Static_assert((((__typeof__(((struct teleport_spell_zap*)0)->dir))-1)<0)==0,"SPELL zap_dir signedness");
_Static_assert(sizeof(((struct teleport_spell_zap*)0)->x)==2,"SPELL zap_x width");
_Static_assert((((__typeof__(((struct teleport_spell_zap*)0)->x))-1)<0)==1,"SPELL zap_x signedness");
_Static_assert(sizeof(((struct teleport_spell_zap*)0)->y)==2,"SPELL zap_y width");
_Static_assert((((__typeof__(((struct teleport_spell_zap*)0)->y))-1)<0)==1,"SPELL zap_y signedness");
_Static_assert(sizeof(((struct teleport_spell_zap*)0)->strength)==1,"SPELL zap_strength width");
_Static_assert((((__typeof__(((struct teleport_spell_zap*)0)->strength))-1)<0)==1,"SPELL zap_strength signedness");
_Static_assert(sizeof(((struct teleport_spell_queue*)0)->head)==4,"SPELL queue_head width");
_Static_assert((((__typeof__(((struct teleport_spell_queue*)0)->head))-1)<0)==1,"SPELL queue_head signedness");
_Static_assert(sizeof(((struct teleport_spell_queue*)0)->tail)==4,"SPELL queue_tail width");
_Static_assert((((__typeof__(((struct teleport_spell_queue*)0)->tail))-1)<0)==1,"SPELL queue_tail signedness");
_Static_assert(sizeof(((struct teleport_spell_queue*)0)->displayed_beam)==4,"SPELL queue_displayed_beam width");
_Static_assert((((__typeof__(((struct teleport_spell_queue*)0)->displayed_beam))-1)<0)==1,"SPELL queue_displayed_beam signedness");
_Static_assert(sizeof(svc.context.spbook.book)==8,"SPELL global book width");
_Static_assert(sizeof(svc.context.spbook.o_id)==4,"SPELL global book_oid width");
_Static_assert((((__typeof__(svc.context.spbook.o_id))-1)<0)==0,"SPELL global book_oid signedness");
_Static_assert(sizeof(svc.context.spbook.delay)==1,"SPELL global book_delay width");
_Static_assert((((__typeof__(svc.context.spbook.delay))-1)<0)==1,"SPELL global book_delay signedness");
_Static_assert(sizeof(svc.context.forcefight)==1,"SPELL global forcefight width");
_Static_assert((((__typeof__(svc.context.forcefight))-1)<0)==1,"SPELL global forcefight signedness");
_Static_assert(sizeof(go.occupation)==8,"SPELL global occupation width");
_Static_assert(sizeof(gm.multi)==8,"SPELL global multi width");
_Static_assert((((__typeof__(gm.multi))-1)<0)==1,"SPELL global multi signedness");
_Static_assert(sizeof(gm.multi_reason)==8,"SPELL global multi_reason width");
_Static_assert(sizeof(gn.nomovemsg)==8,"SPELL global nomovemsg width");
_Static_assert(sizeof(gn.notonhead)==1,"SPELL global notonhead width");
_Static_assert((((__typeof__(gn.notonhead))-1)<0)==1,"SPELL global notonhead signedness");
_Static_assert(sizeof(gi.invent)==8,"SPELL global invent width");
_Static_assert(sizeof(svm.moves)==8,"SPELL global moves width");
_Static_assert((((__typeof__(svm.moves))-1)<0)==1,"SPELL global moves signedness");
_Static_assert(sizeof(gs.spl_orderindx)==8,"SPELL global spl_orderindx width");
_Static_assert(sizeof(gs.spl_sortmode)==4,"SPELL global spl_sortmode width");
_Static_assert((((__typeof__(gs.spl_sortmode))-1)<0)==1,"SPELL global spl_sortmode signedness");
_Static_assert(sizeof(flags.menu_style)==1,"SPELL global menu_style width");
_Static_assert((((__typeof__(flags.menu_style))-1)<0)==1,"SPELL global menu_style signedness");
_Static_assert(sizeof(iflags.menu_tab_sep)==1,"SPELL global menu_tab_sep width");
_Static_assert((((__typeof__(iflags.menu_tab_sep))-1)<0)==1,"SPELL global menu_tab_sep signedness");
_Static_assert(sizeof(flags.debug)==1,"SPELL global wizard width");
_Static_assert((((__typeof__(flags.debug))-1)<0)==1,"SPELL global wizard signedness");
_Static_assert(sizeof(disp.botl)==1,"SPELL global botl width");
_Static_assert((((__typeof__(disp.botl))-1)<0)==1,"SPELL global botl signedness");
_Static_assert(sizeof(u.uconduct.literate)==8,"SPELL global literate width");
_Static_assert((((__typeof__(u.uconduct.literate))-1)<0)==1,"SPELL global literate signedness");
_Static_assert(sizeof(flags.female)==1,"SPELL global female width");
_Static_assert((((__typeof__(flags.female))-1)<0)==1,"SPELL global female signedness");
#endif
