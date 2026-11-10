/* Native metadata only; monster spell policy and tables live in mcastu.js. */
#include "hack.h"
#include <stddef.h>
#ifndef TELEPORT_REFERENCE_TU
#define MCASTU_ENUM
enum mcast_spells {
#include "mcastu.h"
};
#undef MCASTU_ENUM
#endif
struct mcastu_meta {const char*name;size_t value;};
#define MCASTU_META(k,v) {#k,(size_t)(v)}
static const struct mcastu_meta mcastu_layout[] = {
MCASTU_META(pointerSize,sizeof(void*)),
MCASTU_META(longSize,sizeof(long)),
MCASTU_META(intSize,sizeof(int)),
MCASTU_META(coordSize,sizeof(coordxy)),
MCASTU_META(booleanSize,sizeof(boolean)),
MCASTU_META(monsterSize,sizeof(struct monst)),
MCASTU_META(permonstSize,sizeof(struct permonst)),
MCASTU_META(attackSize,sizeof(struct attack)),
MCASTU_META(coordStructSize,sizeof(coord)),
MCASTU_META(propSize,sizeof(struct prop)),
MCASTU_META(genderSize,sizeof(struct Gender)),
MCASTU_META(mon_data,offsetof(struct monst,data)),
MCASTU_META(mon_data_size,sizeof(((struct monst*)0)->data)),
MCASTU_META(mon_mx,offsetof(struct monst,mx)),
MCASTU_META(mon_mx_size,sizeof(((struct monst*)0)->mx)),
MCASTU_META(mon_my,offsetof(struct monst,my)),
MCASTU_META(mon_my_size,sizeof(((struct monst*)0)->my)),
MCASTU_META(mon_mux,offsetof(struct monst,mux)),
MCASTU_META(mon_mux_size,sizeof(((struct monst*)0)->mux)),
MCASTU_META(mon_muy,offsetof(struct monst,muy)),
MCASTU_META(mon_muy_size,sizeof(((struct monst*)0)->muy)),
MCASTU_META(mon_mhp,offsetof(struct monst,mhp)),
MCASTU_META(mon_mhp_size,sizeof(((struct monst*)0)->mhp)),
MCASTU_META(mon_mhpmax,offsetof(struct monst,mhpmax)),
MCASTU_META(mon_mhpmax_size,sizeof(((struct monst*)0)->mhpmax)),
MCASTU_META(mon_m_lev,offsetof(struct monst,m_lev)),
MCASTU_META(mon_m_lev_size,sizeof(((struct monst*)0)->m_lev)),
MCASTU_META(mon_mspec_used,offsetof(struct monst,mspec_used)),
MCASTU_META(mon_mspec_used_size,sizeof(((struct monst*)0)->mspec_used)),
MCASTU_META(mon_mtame,offsetof(struct monst,mtame)),
MCASTU_META(mon_mtame_size,sizeof(((struct monst*)0)->mtame)),
MCASTU_META(mon_cham,offsetof(struct monst,cham)),
MCASTU_META(mon_cham_size,sizeof(((struct monst*)0)->cham)),
MCASTU_META(mon_seen_resistance,offsetof(struct monst,seen_resistance)),
MCASTU_META(mon_seen_resistance_size,sizeof(((struct monst*)0)->seen_resistance)),
MCASTU_META(mon_mappearance,offsetof(struct monst,mappearance)),
MCASTU_META(mon_mappearance_size,sizeof(((struct monst*)0)->mappearance)),
MCASTU_META(mon_m_ap_type,offsetof(struct monst,m_ap_type)),
MCASTU_META(mon_m_ap_type_size,sizeof(((struct monst*)0)->m_ap_type)),
MCASTU_META(pm_mlet,offsetof(struct permonst,mlet)),
MCASTU_META(pm_mlet_size,sizeof(((struct permonst*)0)->mlet)),
MCASTU_META(pm_mflags1,offsetof(struct permonst,mflags1)),
MCASTU_META(pm_mflags1_size,sizeof(((struct permonst*)0)->mflags1)),
MCASTU_META(pm_mflags2,offsetof(struct permonst,mflags2)),
MCASTU_META(pm_mflags2_size,sizeof(((struct permonst*)0)->mflags2)),
MCASTU_META(atk_adtyp,offsetof(struct attack,adtyp)),
MCASTU_META(atk_adtyp_size,sizeof(((struct attack*)0)->adtyp)),
MCASTU_META(atk_damn,offsetof(struct attack,damn)),
MCASTU_META(atk_damn_size,sizeof(((struct attack*)0)->damn)),
MCASTU_META(atk_damd,offsetof(struct attack,damd)),
MCASTU_META(atk_damd_size,sizeof(((struct attack*)0)->damd)),
MCASTU_META(u_ux,offsetof(struct you,ux)),
MCASTU_META(u_ux_size,sizeof(((struct you*)0)->ux)),
MCASTU_META(u_uy,offsetof(struct you,uy)),
MCASTU_META(u_uy_size,sizeof(((struct you*)0)->uy)),
MCASTU_META(u_mh,offsetof(struct you,mh)),
MCASTU_META(u_mh_size,sizeof(((struct you*)0)->mh)),
MCASTU_META(u_uhp,offsetof(struct you,uhp)),
MCASTU_META(u_uhp_size,sizeof(((struct you*)0)->uhp)),
MCASTU_META(u_uhpmax,offsetof(struct you,uhpmax)),
MCASTU_META(u_uhpmax_size,sizeof(((struct you*)0)->uhpmax)),
MCASTU_META(u_umonnum,offsetof(struct you,umonnum)),
MCASTU_META(u_umonnum_size,sizeof(((struct you*)0)->umonnum)),
MCASTU_META(u_umonster,offsetof(struct you,umonster)),
MCASTU_META(u_umonster_size,sizeof(((struct you*)0)->umonster)),
MCASTU_META(u_uprops,offsetof(struct you,uprops)),
MCASTU_META(u_uprops_size,sizeof(((struct you*)0)->uprops)),
MCASTU_META(prop_intrinsic,offsetof(struct prop,intrinsic)),
MCASTU_META(prop_intrinsic_size,sizeof(((struct prop*)0)->intrinsic)),
MCASTU_META(prop_extrinsic,offsetof(struct prop,extrinsic)),
MCASTU_META(prop_extrinsic_size,sizeof(((struct prop*)0)->extrinsic)),
MCASTU_META(prop_blocked,offsetof(struct prop,blocked)),
MCASTU_META(prop_blocked_size,sizeof(((struct prop*)0)->blocked)),
MCASTU_META(coord_x,offsetof(coord,x)),
MCASTU_META(coord_x_size,sizeof(((coord*)0)->x)),
MCASTU_META(coord_y,offsetof(coord,y)),
MCASTU_META(coord_y_size,sizeof(((coord*)0)->y)),
MCASTU_META(gender_he,offsetof(struct Gender,he)),
MCASTU_META(gender_he_size,sizeof(((struct Gender*)0)->he)),
MCASTU_META(youmonst,(char*)&gy.youmonst-(char*)&gy),
MCASTU_META(moves,(char*)&svm.moves-(char*)&svm),
MCASTU_META(noOfWizards,(char*)&svc.context.no_of_wizards-(char*)&svc),
MCASTU_META(killerFormat,(char*)&svk.killer.format-(char*)&svk),
MCASTU_META(killerName,(char*)&svk.killer.name-(char*)&svk),
MCASTU_META(invent,(char*)&gi.invent-(char*)&gi),
MCASTU_META(multi,(char*)&gm.multi-(char*)&gm),
MCASTU_META(multiReason,(char*)&gm.multi_reason-(char*)&gm),
MCASTU_META(nomovemsg,(char*)&gn.nomovemsg-(char*)&gn),
MCASTU_META(buzzer,(char*)&gb.buzzer-(char*)&gb),
MCASTU_META(tbx,(char*)&gt.tbx-(char*)&gt),
MCASTU_META(tby,(char*)&gt.tby-(char*)&gt),
MCASTU_META(vizArray,(char*)&gv.viz_array-(char*)&gv),
MCASTU_META(lastMsg,(char*)&iflags.last_msg-(char*)&iflags),
MCASTU_META(AD_SPEL,AD_SPEL),
MCASTU_META(AD_PHYS,AD_PHYS),
MCASTU_META(PM_HORNED_DEVIL,PM_HORNED_DEVIL),
MCASTU_META(AD_CLRC,AD_CLRC),
MCASTU_META(AD_FIRE,AD_FIRE),
MCASTU_META(AD_COLD,AD_COLD),
MCASTU_META(AD_MAGM,AD_MAGM),
MCASTU_META(AD_ELEC,AD_ELEC),
MCASTU_META(AD_SPC2,AD_SPC2),
MCASTU_META(M_ATTK_MISS,M_ATTK_MISS),
MCASTU_META(M_ATTK_HIT,M_ATTK_HIT),
MCASTU_META(HEAD,HEAD),
MCASTU_META(EYE,EYE),
MCASTU_META(A_DEX,A_DEX),
MCASTU_META(KILLED_BY,KILLED_BY),
MCASTU_META(DIED,DIED),
MCASTU_META(M_SEEN_FIRE,M_SEEN_FIRE),
MCASTU_META(M_SEEN_COLD,M_SEEN_COLD),
MCASTU_META(M_SEEN_MAGR,M_SEEN_MAGR),
MCASTU_META(M_SEEN_REFL,M_SEEN_REFL),
MCASTU_META(M_SEEN_ELEC,M_SEEN_ELEC),
MCASTU_META(MM_ANGRY,MM_ANGRY),
MCASTU_META(MM_NOMSG,MM_NOMSG),
MCASTU_META(S_ANT,S_ANT),
MCASTU_META(S_SNAKE,S_SNAKE),
MCASTU_META(S_GOLEM,S_GOLEM),
MCASTU_META(S_VORTEX,S_VORTEX),
MCASTU_META(MFAST,MFAST),
MCASTU_META(STRANGE_OBJECT,STRANGE_OBJECT),
MCASTU_META(M_AP_OBJECT,M_AP_OBJECT),
MCASTU_META(M_AP_TYPMASK,M_AP_TYPMASK),
MCASTU_META(PRONOUN_HALLU,PRONOUN_HALLU),
MCASTU_META(BUFSZ,BUFSZ),
MCASTU_META(QBUFSZ,QBUFSZ),
MCASTU_META(TIMEOUT,TIMEOUT),
MCASTU_META(NUMMONS,NUMMONS),
MCASTU_META(LOW_PM,LOW_PM),
MCASTU_META(PM_MANES,PM_MANES),
MCASTU_META(PM_CYCLOPS,PM_CYCLOPS),
MCASTU_META(PM_FLOATING_EYE,PM_FLOATING_EYE),
MCASTU_META(M1_SEE_INVIS,M1_SEE_INVIS),
MCASTU_META(M1_NOEYES,M1_NOEYES),
MCASTU_META(M2_PNAME,M2_PNAME),
MCASTU_META(M2_UNDEAD,M2_UNDEAD),
MCASTU_META(M2_DEMON,M2_DEMON),
MCASTU_META(BLINDED,BLINDED),
MCASTU_META(FIRE_RES,FIRE_RES),
MCASTU_META(COLD_RES,COLD_RES),
MCASTU_META(SHOCK_RES,SHOCK_RES),
MCASTU_META(ANTIMAGIC,ANTIMAGIC),
MCASTU_META(STUNNED,STUNNED),
MCASTU_META(CONFUSION,CONFUSION),
MCASTU_META(HALLUC,HALLUC),
MCASTU_META(HALLUC_RES,HALLUC_RES),
MCASTU_META(SEE_INVIS,SEE_INVIS),
MCASTU_META(DETECT_MONSTERS,DETECT_MONSTERS),
MCASTU_META(INVIS,INVIS),
MCASTU_META(DISPLACED,DISPLACED),
MCASTU_META(HALF_SPDAM,HALF_SPDAM),
MCASTU_META(HALF_PHDAM,HALF_PHDAM),
MCASTU_META(FREE_ACTION,FREE_ACTION),
MCASTU_META(DEAF,DEAF),
MCASTU_META(IN_SIGHT,IN_SIGHT),
MCASTU_META(COULD_SEE,COULD_SEE),
MCASTU_META(PM_HUMAN,PM_HUMAN),
MCASTU_META(PM_LICH,PM_LICH),
MCASTU_META(PM_WIZARD_OF_YENDOR,PM_WIZARD_OF_YENDOR),
MCASTU_META(PM_GHOST,PM_GHOST),
MCASTU_META(PM_GIANT_ANT,PM_GIANT_ANT),
MCASTU_META(PM_WATER_MOCCASIN,PM_WATER_MOCCASIN),
MCASTU_META(MCF_NONE,MCF_NONE),
MCASTU_META(MCF_INDIRECT,MCF_INDIRECT),
MCASTU_META(MCF_SIGHT,MCF_SIGHT),
MCASTU_META(MCF_HOSTILE,MCF_HOSTILE),
MCASTU_META(MCAST_PSI_BOLT,MCAST_PSI_BOLT),
MCASTU_META(MCAST_OPEN_WOUNDS,MCAST_OPEN_WOUNDS),
MCASTU_META(MCAST_CURE_SELF,MCAST_CURE_SELF),
MCASTU_META(MCAST_HASTE_SELF,MCAST_HASTE_SELF),
MCASTU_META(MCAST_CONFUSE_YOU,MCAST_CONFUSE_YOU),
MCASTU_META(MCAST_STUN_YOU,MCAST_STUN_YOU),
MCASTU_META(MCAST_DISAPPEAR,MCAST_DISAPPEAR),
MCASTU_META(MCAST_PARALYZE,MCAST_PARALYZE),
MCASTU_META(MCAST_BLIND_YOU,MCAST_BLIND_YOU),
MCASTU_META(MCAST_WEAKEN_YOU,MCAST_WEAKEN_YOU),
MCASTU_META(MCAST_DESTRY_ARMR,MCAST_DESTRY_ARMR),
MCASTU_META(MCAST_INSECTS,MCAST_INSECTS),
MCASTU_META(MCAST_CURSE_ITEMS,MCAST_CURSE_ITEMS),
MCASTU_META(MCAST_LIGHTNING,MCAST_LIGHTNING),
MCASTU_META(MCAST_FIRE_PILLAR,MCAST_FIRE_PILLAR),
MCASTU_META(MCAST_GEYSER,MCAST_GEYSER),
MCASTU_META(MCAST_AGGRAVATION,MCAST_AGGRAVATION),
MCASTU_META(MCAST_SUMMON_MONS,MCAST_SUMMON_MONS),
MCASTU_META(MCAST_CLONE_WIZ,MCAST_CLONE_WIZ),
MCASTU_META(MCAST_DEATH_TOUCH,MCAST_DEATH_TOUCH),
#ifdef DEBUG
MCASTU_META(config_DEBUG,1),
#else
MCASTU_META(config_DEBUG,0),
#endif
#ifdef SND_LIB_INTEGRATED
MCASTU_META(config_SOUND,1),
#else
MCASTU_META(config_SOUND,0),
#endif
};
size_t probe_context_size(void){return sizeof(struct monst);}
int probe_layout_count(void){return (int)(sizeof mcastu_layout/sizeof mcastu_layout[0]);}
const char*probe_layout_name(int i){return mcastu_layout[i].name;}
size_t probe_layout_value(int i){return mcastu_layout[i].value;}
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(int)==4 && sizeof(coordxy)==2 && (coordxy)-1<0 && sizeof(boolean)==1 && (boolean)-1<0,"review MCASTU ABI");
_Static_assert(sizeof(((struct monst*)0)->data)==8,"review MCASTU mon.data");
_Static_assert(sizeof(((struct monst*)0)->mx)==2 && (((__typeof__(((struct monst*)0)->mx))-1<0)==1),"review MCASTU mon.mx");
_Static_assert(sizeof(((struct monst*)0)->my)==2 && (((__typeof__(((struct monst*)0)->my))-1<0)==1),"review MCASTU mon.my");
_Static_assert(sizeof(((struct monst*)0)->mux)==2 && (((__typeof__(((struct monst*)0)->mux))-1<0)==1),"review MCASTU mon.mux");
_Static_assert(sizeof(((struct monst*)0)->muy)==2 && (((__typeof__(((struct monst*)0)->muy))-1<0)==1),"review MCASTU mon.muy");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4 && (((__typeof__(((struct monst*)0)->mhp))-1<0)==1),"review MCASTU mon.mhp");
_Static_assert(sizeof(((struct monst*)0)->mhpmax)==4 && (((__typeof__(((struct monst*)0)->mhpmax))-1<0)==1),"review MCASTU mon.mhpmax");
_Static_assert(sizeof(((struct monst*)0)->m_lev)==1 && (((__typeof__(((struct monst*)0)->m_lev))-1<0)==0),"review MCASTU mon.m_lev");
_Static_assert(sizeof(((struct monst*)0)->mspec_used)==4 && (((__typeof__(((struct monst*)0)->mspec_used))-1<0)==1),"review MCASTU mon.mspec_used");
_Static_assert(sizeof(((struct monst*)0)->mtame)==1 && (((__typeof__(((struct monst*)0)->mtame))-1<0)==1),"review MCASTU mon.mtame");
_Static_assert(sizeof(((struct monst*)0)->cham)==2 && (((__typeof__(((struct monst*)0)->cham))-1<0)==1),"review MCASTU mon.cham");
_Static_assert(sizeof(((struct monst*)0)->seen_resistance)==8 && (((__typeof__(((struct monst*)0)->seen_resistance))-1<0)==0),"review MCASTU mon.seen_resistance");
_Static_assert(sizeof(((struct monst*)0)->mappearance)==4 && (((__typeof__(((struct monst*)0)->mappearance))-1<0)==0),"review MCASTU mon.mappearance");
_Static_assert(sizeof(((struct monst*)0)->m_ap_type)==1 && (((__typeof__(((struct monst*)0)->m_ap_type))-1<0)==0),"review MCASTU mon.m_ap_type");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1 && (((__typeof__(((struct permonst*)0)->mlet))-1<0)==1),"review MCASTU pm.mlet");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8 && (((__typeof__(((struct permonst*)0)->mflags1))-1<0)==0),"review MCASTU pm.mflags1");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8 && (((__typeof__(((struct permonst*)0)->mflags2))-1<0)==0),"review MCASTU pm.mflags2");
_Static_assert(sizeof(((struct attack*)0)->adtyp)==1 && (((__typeof__(((struct attack*)0)->adtyp))-1<0)==0),"review MCASTU atk.adtyp");
_Static_assert(sizeof(((struct attack*)0)->damn)==1 && (((__typeof__(((struct attack*)0)->damn))-1<0)==0),"review MCASTU atk.damn");
_Static_assert(sizeof(((struct attack*)0)->damd)==1 && (((__typeof__(((struct attack*)0)->damd))-1<0)==0),"review MCASTU atk.damd");
_Static_assert(sizeof(((struct you*)0)->ux)==2 && (((__typeof__(((struct you*)0)->ux))-1<0)==1),"review MCASTU u.ux");
_Static_assert(sizeof(((struct you*)0)->uy)==2 && (((__typeof__(((struct you*)0)->uy))-1<0)==1),"review MCASTU u.uy");
_Static_assert(sizeof(((struct you*)0)->mh)==4 && (((__typeof__(((struct you*)0)->mh))-1<0)==1),"review MCASTU u.mh");
_Static_assert(sizeof(((struct you*)0)->uhp)==4 && (((__typeof__(((struct you*)0)->uhp))-1<0)==1),"review MCASTU u.uhp");
_Static_assert(sizeof(((struct you*)0)->uhpmax)==4 && (((__typeof__(((struct you*)0)->uhpmax))-1<0)==1),"review MCASTU u.uhpmax");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4 && (((__typeof__(((struct you*)0)->umonnum))-1<0)==1),"review MCASTU u.umonnum");
_Static_assert(sizeof(((struct you*)0)->umonster)==4 && (((__typeof__(((struct you*)0)->umonster))-1<0)==1),"review MCASTU u.umonster");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8 && (((__typeof__(((struct prop*)0)->intrinsic))-1<0)==1),"review MCASTU prop.intrinsic");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8 && (((__typeof__(((struct prop*)0)->extrinsic))-1<0)==1),"review MCASTU prop.extrinsic");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8 && (((__typeof__(((struct prop*)0)->blocked))-1<0)==1),"review MCASTU prop.blocked");
_Static_assert(sizeof(((coord*)0)->x)==2 && (((__typeof__(((coord*)0)->x))-1<0)==1),"review MCASTU coord.x");
_Static_assert(sizeof(((coord*)0)->y)==2 && (((__typeof__(((coord*)0)->y))-1<0)==1),"review MCASTU coord.y");
_Static_assert(sizeof(((struct Gender*)0)->he)==8,"review MCASTU gender.he");
_Static_assert(sizeof(svm.moves)==8 && (((__typeof__(svm.moves))-1<0)==1),"review MCASTU svm.moves");
_Static_assert(sizeof(svc.context.no_of_wizards)==4 && (((__typeof__(svc.context.no_of_wizards))-1<0)==0),"review MCASTU svc.context.no_of_wizards");
_Static_assert(sizeof(svk.killer.format)==4 && (((__typeof__(svk.killer.format))-1<0)==1),"review MCASTU svk.killer.format");
_Static_assert(sizeof(gm.multi)==8 && (((__typeof__(gm.multi))-1<0)==1),"review MCASTU gm.multi");
_Static_assert(sizeof(gt.tbx)==1 && (((__typeof__(gt.tbx))-1<0)==1),"review MCASTU gt.tbx");
_Static_assert(sizeof(gt.tby)==1 && (((__typeof__(gt.tby))-1<0)==1),"review MCASTU gt.tby");
_Static_assert(sizeof(iflags.last_msg)==4 && (((__typeof__(iflags.last_msg))-1<0)==1),"review MCASTU iflags.last_msg");
