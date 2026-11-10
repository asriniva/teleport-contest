#ifndef TELEPORT_ENGRAVE_LAYOUT_H
#define TELEPORT_ENGRAVE_LAYOUT_H
#include "../nethack-c/wasm/tu-engrave-support.h"
#include <stddef.h>
struct engrave_meta {const char *name;size_t value;};
#define EMETA(k,v) {#k,(size_t)(v)}
static const struct engrave_meta engrave_layout[]={
EMETA(pointerSize,sizeof(void*)),
EMETA(longSize,sizeof(long)),
EMETA(booleanSize,sizeof(boolean)),
EMETA(EngrSize,sizeof(struct engr)),
EMETA(ContextSize,sizeof(struct teleport_engrave_context)),
EMETA(ReadPrefixSize,sizeof "You feel the words: \"\"."),
EMETA(objectSize,sizeof(struct obj)),
EMETA(objectClassSize,sizeof(struct objclass)),
EMETA(permonstSize,sizeof(struct permonst)),
EMETA(propSize,sizeof(struct prop)),
EMETA(rmSize,sizeof(struct rm)),
EMETA(skillSize,sizeof(struct skills)),
EMETA(engr_nxt_engr,offsetof(struct engr,nxt_engr)),
EMETA(engr_nxt_engr_size,sizeof(((struct engr*)0)->nxt_engr)),
EMETA(engr_engr_txt,offsetof(struct engr,engr_txt)),
EMETA(engr_engr_txt_size,sizeof(((struct engr*)0)->engr_txt)),
EMETA(engr_engr_x,offsetof(struct engr,engr_x)),
EMETA(engr_engr_x_size,sizeof(((struct engr*)0)->engr_x)),
EMETA(engr_engr_y,offsetof(struct engr,engr_y)),
EMETA(engr_engr_y_size,sizeof(((struct engr*)0)->engr_y)),
EMETA(engr_engr_szeach,offsetof(struct engr,engr_szeach)),
EMETA(engr_engr_szeach_size,sizeof(((struct engr*)0)->engr_szeach)),
EMETA(engr_engr_alloc,offsetof(struct engr,engr_alloc)),
EMETA(engr_engr_alloc_size,sizeof(((struct engr*)0)->engr_alloc)),
EMETA(engr_engr_time,offsetof(struct engr,engr_time)),
EMETA(engr_engr_time_size,sizeof(((struct engr*)0)->engr_time)),
EMETA(engr_engr_type,offsetof(struct engr,engr_type)),
EMETA(engr_engr_type_size,sizeof(((struct engr*)0)->engr_type)),
EMETA(ctx_dengr,offsetof(struct teleport_engrave_context,dengr)),
EMETA(ctx_dengr_size,sizeof(((struct teleport_engrave_context*)0)->dengr)),
EMETA(ctx_doblind,offsetof(struct teleport_engrave_context,doblind)),
EMETA(ctx_doblind_size,sizeof(((struct teleport_engrave_context*)0)->doblind)),
EMETA(ctx_doknown,offsetof(struct teleport_engrave_context,doknown)),
EMETA(ctx_doknown_size,sizeof(((struct teleport_engrave_context*)0)->doknown)),
EMETA(ctx_eow,offsetof(struct teleport_engrave_context,eow)),
EMETA(ctx_eow_size,sizeof(((struct teleport_engrave_context*)0)->eow)),
EMETA(ctx_jello,offsetof(struct teleport_engrave_context,jello)),
EMETA(ctx_jello_size,sizeof(((struct teleport_engrave_context*)0)->jello)),
EMETA(ctx_ptext,offsetof(struct teleport_engrave_context,ptext)),
EMETA(ctx_ptext_size,sizeof(((struct teleport_engrave_context*)0)->ptext)),
EMETA(ctx_teleengr,offsetof(struct teleport_engrave_context,teleengr)),
EMETA(ctx_teleengr_size,sizeof(((struct teleport_engrave_context*)0)->teleengr)),
EMETA(ctx_zapwand,offsetof(struct teleport_engrave_context,zapwand)),
EMETA(ctx_zapwand_size,sizeof(((struct teleport_engrave_context*)0)->zapwand)),
EMETA(ctx_disprefresh,offsetof(struct teleport_engrave_context,disprefresh)),
EMETA(ctx_disprefresh_size,sizeof(((struct teleport_engrave_context*)0)->disprefresh)),
EMETA(ctx_frosted,offsetof(struct teleport_engrave_context,frosted)),
EMETA(ctx_frosted_size,sizeof(((struct teleport_engrave_context*)0)->frosted)),
EMETA(ctx_adding,offsetof(struct teleport_engrave_context,adding)),
EMETA(ctx_adding_size,sizeof(((struct teleport_engrave_context*)0)->adding)),
EMETA(ctx_ret,offsetof(struct teleport_engrave_context,ret)),
EMETA(ctx_ret_size,sizeof(((struct teleport_engrave_context*)0)->ret)),
EMETA(ctx_type,offsetof(struct teleport_engrave_context,type)),
EMETA(ctx_type_size,sizeof(((struct teleport_engrave_context*)0)->type)),
EMETA(ctx_oetype,offsetof(struct teleport_engrave_context,oetype)),
EMETA(ctx_oetype_size,sizeof(((struct teleport_engrave_context*)0)->oetype)),
EMETA(ctx_otmp,offsetof(struct teleport_engrave_context,otmp)),
EMETA(ctx_otmp_size,sizeof(((struct teleport_engrave_context*)0)->otmp)),
EMETA(ctx_oep,offsetof(struct teleport_engrave_context,oep)),
EMETA(ctx_oep_size,sizeof(((struct teleport_engrave_context*)0)->oep)),
EMETA(ctx_buf,offsetof(struct teleport_engrave_context,buf)),
EMETA(ctx_buf_size,sizeof(((struct teleport_engrave_context*)0)->buf)),
EMETA(ctx_ebuf,offsetof(struct teleport_engrave_context,ebuf)),
EMETA(ctx_ebuf_size,sizeof(((struct teleport_engrave_context*)0)->ebuf)),
EMETA(ctx_fbuf,offsetof(struct teleport_engrave_context,fbuf)),
EMETA(ctx_fbuf_size,sizeof(((struct teleport_engrave_context*)0)->fbuf)),
EMETA(ctx_qbuf,offsetof(struct teleport_engrave_context,qbuf)),
EMETA(ctx_qbuf_size,sizeof(((struct teleport_engrave_context*)0)->qbuf)),
EMETA(ctx_post_engr_text,offsetof(struct teleport_engrave_context,post_engr_text)),
EMETA(ctx_post_engr_text_size,sizeof(((struct teleport_engrave_context*)0)->post_engr_text)),
EMETA(ctx_writer,offsetof(struct teleport_engrave_context,writer)),
EMETA(ctx_writer_size,sizeof(((struct teleport_engrave_context*)0)->writer)),
EMETA(ctx_everb,offsetof(struct teleport_engrave_context,everb)),
EMETA(ctx_everb_size,sizeof(((struct teleport_engrave_context*)0)->everb)),
EMETA(ctx_eloc,offsetof(struct teleport_engrave_context,eloc)),
EMETA(ctx_eloc_size,sizeof(((struct teleport_engrave_context*)0)->eloc)),
EMETA(ctx_len,offsetof(struct teleport_engrave_context,len)),
EMETA(ctx_len_size,sizeof(((struct teleport_engrave_context*)0)->len)),
EMETA(obj_nobj,offsetof(struct obj,nobj)),
EMETA(obj_nobj_size,sizeof(((struct obj*)0)->nobj)),
EMETA(obj_otyp,offsetof(struct obj,otyp)),
EMETA(obj_otyp_size,sizeof(((struct obj*)0)->otyp)),
EMETA(obj_oclass,offsetof(struct obj,oclass)),
EMETA(obj_oclass_size,sizeof(((struct obj*)0)->oclass)),
EMETA(obj_oartifact,offsetof(struct obj,oartifact)),
EMETA(obj_oartifact_size,sizeof(((struct obj*)0)->oartifact)),
EMETA(obj_spe,offsetof(struct obj,spe)),
EMETA(obj_spe_size,sizeof(((struct obj*)0)->spe)),
EMETA(obj_owornmask,offsetof(struct obj,owornmask)),
EMETA(obj_owornmask_size,sizeof(((struct obj*)0)->owornmask)),
EMETA(obj_quan,offsetof(struct obj,quan)),
EMETA(obj_quan_size,sizeof(((struct obj*)0)->quan)),
EMETA(cls_oc_skill,offsetof(struct objclass,oc_skill)),
EMETA(cls_oc_skill_size,sizeof(((struct objclass*)0)->oc_skill)),
EMETA(cls_oc_armcat,offsetof(struct objclass,oc_armcat)),
EMETA(cls_oc_armcat_size,sizeof(((struct objclass*)0)->oc_armcat)),
EMETA(mon_data,offsetof(struct monst,data)),
EMETA(mon_data_size,sizeof(((struct monst*)0)->data)),
EMETA(pm_mflags1,offsetof(struct permonst,mflags1)),
EMETA(pm_mflags1_size,sizeof(((struct permonst*)0)->mflags1)),
EMETA(pm_mflags2,offsetof(struct permonst,mflags2)),
EMETA(pm_mflags2_size,sizeof(((struct permonst*)0)->mflags2)),
EMETA(pm_msize,offsetof(struct permonst,msize)),
EMETA(pm_msize_size,sizeof(((struct permonst*)0)->msize)),
EMETA(pm_mlet,offsetof(struct permonst,mlet)),
EMETA(pm_mlet_size,sizeof(((struct permonst*)0)->mlet)),
EMETA(u_ux,offsetof(struct you,ux)),
EMETA(u_ux_size,sizeof(((struct you*)0)->ux)),
EMETA(u_uy,offsetof(struct you,uy)),
EMETA(u_uy_size,sizeof(((struct you*)0)->uy)),
EMETA(u_uz,offsetof(struct you,uz)),
EMETA(u_uz_size,sizeof(((struct you*)0)->uz)),
EMETA(u_ustuck,offsetof(struct you,ustuck)),
EMETA(u_ustuck_size,sizeof(((struct you*)0)->ustuck)),
EMETA(u_usteed,offsetof(struct you,usteed)),
EMETA(u_usteed_size,sizeof(((struct you*)0)->usteed)),
EMETA(u_uprops,offsetof(struct you,uprops)),
EMETA(u_uprops_size,sizeof(((struct you*)0)->uprops)),
EMETA(u_weapon_skills,offsetof(struct you,weapon_skills)),
EMETA(u_weapon_skills_size,sizeof(((struct you*)0)->weapon_skills)),
EMETA(prop_intrinsic,offsetof(struct prop,intrinsic)),
EMETA(prop_intrinsic_size,sizeof(((struct prop*)0)->intrinsic)),
EMETA(prop_extrinsic,offsetof(struct prop,extrinsic)),
EMETA(prop_extrinsic_size,sizeof(((struct prop*)0)->extrinsic)),
EMETA(prop_blocked,offsetof(struct prop,blocked)),
EMETA(prop_blocked_size,sizeof(((struct prop*)0)->blocked)),
EMETA(rm_typ,offsetof(struct rm,typ)),
EMETA(rm_typ_size,sizeof(((struct rm*)0)->typ)),
EMETA(coord_x,offsetof(coord,x)),
EMETA(coord_x_size,sizeof(((coord*)0)->x)),
EMETA(coord_y,offsetof(coord,y)),
EMETA(coord_y_size,sizeof(((coord*)0)->y)),
EMETA(dlevel_dnum,offsetof(d_level,dnum)),
EMETA(dlevel_dnum_size,sizeof(((d_level*)0)->dnum)),
EMETA(dlevel_dlevel,offsetof(d_level,dlevel)),
EMETA(dlevel_dlevel_size,sizeof(((d_level*)0)->dlevel)),
EMETA(occupation_text,offsetof(struct engrave_info,text)),
EMETA(occupation_text_size,sizeof(((struct engrave_info*)0)->text)),
EMETA(occupation_nextc,offsetof(struct engrave_info,nextc)),
EMETA(occupation_nextc_size,sizeof(((struct engrave_info*)0)->nextc)),
EMETA(occupation_stylus,offsetof(struct engrave_info,stylus)),
EMETA(occupation_stylus_size,sizeof(((struct engrave_info*)0)->stylus)),
EMETA(occupation_type,offsetof(struct engrave_info,type)),
EMETA(occupation_type_size,sizeof(((struct engrave_info*)0)->type)),
EMETA(occupation_pos,offsetof(struct engrave_info,pos)),
EMETA(occupation_pos_size,sizeof(((struct engrave_info*)0)->pos)),
EMETA(occupation_actionct,offsetof(struct engrave_info,actionct)),
EMETA(occupation_actionct_size,sizeof(((struct engrave_info*)0)->actionct)),
EMETA(nhfile_mode,offsetof(NHFILE,mode)),
EMETA(nhfile_mode_size,sizeof(((NHFILE*)0)->mode)),
EMETA(skill_skill,offsetof(struct skills,skill)),
EMETA(skill_skill_size,sizeof(((struct skills*)0)->skill)),
EMETA(literate,offsetof(__typeof__(u),uconduct.literate)),
EMETA(literate_size,sizeof(u.uconduct.literate)),
EMETA(engraving,offsetof(__typeof__(svc),context.engraving)),
EMETA(engraving_size,sizeof(svc.context.engraving)),
EMETA(run,offsetof(__typeof__(svc),context.run)),
EMETA(run_size,sizeof(svc.context.run)),
EMETA(invent,offsetof(__typeof__(gi),invent)),
EMETA(invent_size,sizeof(gi.invent)),
EMETA(in_mklev,offsetof(__typeof__(gi),in_mklev)),
EMETA(in_mklev_size,sizeof(gi.in_mklev)),
EMETA(youmonst,offsetof(__typeof__(gy),youmonst)),
EMETA(youmonst_size,sizeof(gy.youmonst)),
EMETA(moves,offsetof(__typeof__(svm),moves)),
EMETA(moves_size,sizeof(svm.moves)),
EMETA(multi,offsetof(__typeof__(gm),multi)),
EMETA(multi_size,sizeof(gm.multi)),
EMETA(nomovemsg,offsetof(__typeof__(gn),nomovemsg)),
EMETA(nomovemsg_size,sizeof(gn.nomovemsg)),
EMETA(last_msg,offsetof(__typeof__(iflags),last_msg)),
EMETA(last_msg_size,sizeof(iflags.last_msg)),
EMETA(verbose,offsetof(__typeof__(flags),verbose)),
EMETA(verbose_size,sizeof(flags.verbose)),
EMETA(locations,offsetof(__typeof__(svl),level.locations)),
EMETA(locations_size,sizeof(svl.level.locations)),
EMETA(air_level,offsetof(__typeof__(svd),dungeon_topology.d_air_level)),
EMETA(air_level_size,sizeof(svd.dungeon_topology.d_air_level)),
EMETA(water_level,offsetof(__typeof__(svd),dungeon_topology.d_water_level)),
EMETA(water_level_size,sizeof(svd.dungeon_topology.d_water_level)),
EMETA(AIR,AIR),
EMETA(ALTAR,ALTAR),
EMETA(AMULET_CLASS,AMULET_CLASS),
EMETA(ARMOR_CLASS,ARMOR_CLASS),
EMETA(ARM_BOOTS,ARM_BOOTS),
EMETA(ART_FIRE_BRAND,ART_FIRE_BRAND),
EMETA(ATHAME,ATHAME),
EMETA(AT_HUGS,AT_HUGS),
EMETA(A_WIS,A_WIS),
EMETA(BALL_CLASS,BALL_CLASS),
EMETA(BLINDED,BLINDED),
EMETA(BLINDFOLD,BLINDFOLD),
EMETA(BLINDING_VENOM,BLINDING_VENOM),
EMETA(BOULDER,BOULDER),
EMETA(BUFSZ,BUFSZ),
EMETA(BURN,BURN),
EMETA(CHAIN_CLASS,CHAIN_CLASS),
EMETA(CLOUD,CLOUD),
EMETA(COIN_CLASS,COIN_CLASS),
EMETA(COLNO,COLNO),
EMETA(CONFUSION,CONFUSION),
EMETA(COUNTING,COUNTING),
EMETA(DAGGER,DAGGER),
EMETA(DEAF,DEAF),
EMETA(DIAMOND,DIAMOND),
EMETA(DOOR,DOOR),
EMETA(DRAWBRIDGE_DOWN,DRAWBRIDGE_DOWN),
EMETA(DRAWBRIDGE_UP,DRAWBRIDGE_UP),
EMETA(DUST,DUST),
EMETA(ECMD_CANCEL,ECMD_CANCEL),
EMETA(ECMD_FAIL,ECMD_FAIL),
EMETA(ECMD_OK,ECMD_OK),
EMETA(ECMD_TIME,ECMD_TIME),
EMETA(ENGRAVE,ENGRAVE),
EMETA(ENGR_BLOOD,ENGR_BLOOD),
EMETA(FINGERTIP,FINGERTIP),
EMETA(FLYING,FLYING),
EMETA(FOOD_CLASS,FOOD_CLASS),
EMETA(FOOD_RATION,FOOD_RATION),
EMETA(FOUNTAIN,FOUNTAIN),
EMETA(FREEING,FREEING),
EMETA(GEM_CLASS,GEM_CLASS),
EMETA(GETOBJ_DOWNPLAY,GETOBJ_DOWNPLAY),
EMETA(GETOBJ_PROMPT,GETOBJ_PROMPT),
EMETA(GETOBJ_SUGGEST,GETOBJ_SUGGEST),
EMETA(GRAVE,GRAVE),
EMETA(HALLUC,HALLUC),
EMETA(HALLUC_RES,HALLUC_RES),
EMETA(HAND,HAND),
EMETA(HEADSTONE,HEADSTONE),
EMETA(ILLOBJ_CLASS,ILLOBJ_CLASS),
EMETA(IN_SIGHT,IN_SIGHT),
EMETA(LEVITATION,LEVITATION),
EMETA(LL_CONDUCT,LL_CONDUCT),
EMETA(LOW_BOOTS,LOW_BOOTS),
EMETA(M1_ANIMAL,M1_ANIMAL),
EMETA(M1_CLING,M1_CLING),
EMETA(M1_FLY,M1_FLY),
EMETA(M1_HIDE,M1_HIDE),
EMETA(M1_NOHANDS,M1_NOHANDS),
EMETA(M2_DEMON,M2_DEMON),
EMETA(MAGIC_MARKER,MAGIC_MARKER),
EMETA(MARK,MARK),
EMETA(MD_PAD_RUMORS,MD_PAD_RUMORS),
EMETA(MZ_HUGE,MZ_HUGE),
EMETA(MZ_SMALL,MZ_SMALL),
EMETA(MZ_TINY,MZ_TINY),
EMETA(NO_MM_FLAGS,NO_MM_FLAGS),
EMETA(N_ENGRAVE,N_ENGRAVE),
EMETA(PLATE_MAIL,PLATE_MAIL),
EMETA(PM_AIR_ELEMENTAL,PM_AIR_ELEMENTAL),
EMETA(PM_GHOUL,PM_GHOUL),
EMETA(PM_GIANT_SPIDER,PM_GIANT_SPIDER),
EMETA(PM_HUMAN,PM_HUMAN),
EMETA(POTION_CLASS,POTION_CLASS),
EMETA(P_BASIC,P_BASIC),
EMETA(P_DAGGER,P_DAGGER),
EMETA(P_RIDING,P_RIDING),
EMETA(P_SABER,P_SABER),
EMETA(RANDOM_CLASS,RANDOM_CLASS),
EMETA(RING_CLASS,RING_CLASS),
EMETA(ROCK_CLASS,ROCK_CLASS),
EMETA(ROOM,ROOM),
EMETA(ROWNO,ROWNO),
EMETA(SCROLL_CLASS,SCROLL_CLASS),
EMETA(SCR_BLANK_PAPER,SCR_BLANK_PAPER),
EMETA(SPBOOK_CLASS,SPBOOK_CLASS),
EMETA(STONE,STONE),
EMETA(STUNNED,STUNNED),
EMETA(S_MIMIC,S_MIMIC),
EMETA(S_VAMPIRE,S_VAMPIRE),
EMETA(S_VORTEX,S_VORTEX),
EMETA(TOOL_CLASS,TOOL_CLASS),
EMETA(TOWEL,TOWEL),
EMETA(VENOM_CLASS,VENOM_CLASS),
EMETA(WAND_BACKFIRE_CHANCE,WAND_BACKFIRE_CHANCE),
EMETA(WAND_CLASS,WAND_CLASS),
EMETA(WAN_CANCELLATION,WAN_CANCELLATION),
EMETA(WAN_COLD,WAN_COLD),
EMETA(WAN_CREATE_MONSTER,WAN_CREATE_MONSTER),
EMETA(WAN_DEATH,WAN_DEATH),
EMETA(WAN_DIGGING,WAN_DIGGING),
EMETA(WAN_ENLIGHTENMENT,WAN_ENLIGHTENMENT),
EMETA(WAN_FIRE,WAN_FIRE),
EMETA(WAN_LIGHT,WAN_LIGHT),
EMETA(WAN_LIGHTNING,WAN_LIGHTNING),
EMETA(WAN_LOCKING,WAN_LOCKING),
EMETA(WAN_MAGIC_MISSILE,WAN_MAGIC_MISSILE),
EMETA(WAN_MAKE_INVISIBLE,WAN_MAKE_INVISIBLE),
EMETA(WAN_NOTHING,WAN_NOTHING),
EMETA(WAN_OPENING,WAN_OPENING),
EMETA(WAN_POLYMORPH,WAN_POLYMORPH),
EMETA(WAN_PROBING,WAN_PROBING),
EMETA(WAN_SECRET_DOOR_DETECTION,WAN_SECRET_DOOR_DETECTION),
EMETA(WAN_SLEEP,WAN_SLEEP),
EMETA(WAN_SLOW_MONSTER,WAN_SLOW_MONSTER),
EMETA(WAN_SPEED_MONSTER,WAN_SPEED_MONSTER),
EMETA(WAN_STASIS,WAN_STASIS),
EMETA(WAN_STRIKING,WAN_STRIKING),
EMETA(WAN_TELEPORTATION,WAN_TELEPORTATION),
EMETA(WAN_UNDEAD_TURNING,WAN_UNDEAD_TURNING),
EMETA(WAN_WISHING,WAN_WISHING),
EMETA(WEAPON_CLASS,WEAPON_CLASS),
EMETA(WRITING,WRITING),
EMETA(actual_text,actual_text),
EMETA(pristine_text,pristine_text),
EMETA(remembered_text,remembered_text),
EMETA(text_states,text_states),
#ifdef DEBUG
EMETA(config_DEBUG,1),
#else
EMETA(config_DEBUG,0),
#endif
};
_Static_assert(sizeof(((struct engr*)0)->nxt_engr)==8,"ENGRAVE engr_nxt_engr width");
_Static_assert(sizeof(((struct engr*)0)->engr_x)==2,"ENGRAVE engr_engr_x width");
_Static_assert((((__typeof__(((struct engr*)0)->engr_x))-1)<0)==1,"ENGRAVE engr_engr_x signedness");
_Static_assert(sizeof(((struct engr*)0)->engr_y)==2,"ENGRAVE engr_engr_y width");
_Static_assert((((__typeof__(((struct engr*)0)->engr_y))-1)<0)==1,"ENGRAVE engr_engr_y signedness");
_Static_assert(sizeof(((struct engr*)0)->engr_szeach)==4,"ENGRAVE engr_engr_szeach width");
_Static_assert((((__typeof__(((struct engr*)0)->engr_szeach))-1)<0)==0,"ENGRAVE engr_engr_szeach signedness");
_Static_assert(sizeof(((struct engr*)0)->engr_alloc)==4,"ENGRAVE engr_engr_alloc width");
_Static_assert((((__typeof__(((struct engr*)0)->engr_alloc))-1)<0)==0,"ENGRAVE engr_engr_alloc signedness");
_Static_assert(sizeof(((struct engr*)0)->engr_time)==8,"ENGRAVE engr_engr_time width");
_Static_assert((((__typeof__(((struct engr*)0)->engr_time))-1)<0)==1,"ENGRAVE engr_engr_time signedness");
_Static_assert(sizeof(((struct engr*)0)->engr_type)==1,"ENGRAVE engr_engr_type width");
_Static_assert((((__typeof__(((struct engr*)0)->engr_type))-1)<0)==1,"ENGRAVE engr_engr_type signedness");
_Static_assert(sizeof(((struct teleport_engrave_context*)0)->dengr)==1,"ENGRAVE ctx_dengr width");
_Static_assert((((__typeof__(((struct teleport_engrave_context*)0)->dengr))-1)<0)==1,"ENGRAVE ctx_dengr signedness");
_Static_assert(sizeof(((struct teleport_engrave_context*)0)->doblind)==1,"ENGRAVE ctx_doblind width");
_Static_assert((((__typeof__(((struct teleport_engrave_context*)0)->doblind))-1)<0)==1,"ENGRAVE ctx_doblind signedness");
_Static_assert(sizeof(((struct teleport_engrave_context*)0)->doknown)==1,"ENGRAVE ctx_doknown width");
_Static_assert((((__typeof__(((struct teleport_engrave_context*)0)->doknown))-1)<0)==1,"ENGRAVE ctx_doknown signedness");
_Static_assert(sizeof(((struct teleport_engrave_context*)0)->eow)==1,"ENGRAVE ctx_eow width");
_Static_assert((((__typeof__(((struct teleport_engrave_context*)0)->eow))-1)<0)==1,"ENGRAVE ctx_eow signedness");
_Static_assert(sizeof(((struct teleport_engrave_context*)0)->jello)==1,"ENGRAVE ctx_jello width");
_Static_assert((((__typeof__(((struct teleport_engrave_context*)0)->jello))-1)<0)==1,"ENGRAVE ctx_jello signedness");
_Static_assert(sizeof(((struct teleport_engrave_context*)0)->ptext)==1,"ENGRAVE ctx_ptext width");
_Static_assert((((__typeof__(((struct teleport_engrave_context*)0)->ptext))-1)<0)==1,"ENGRAVE ctx_ptext signedness");
_Static_assert(sizeof(((struct teleport_engrave_context*)0)->teleengr)==1,"ENGRAVE ctx_teleengr width");
_Static_assert((((__typeof__(((struct teleport_engrave_context*)0)->teleengr))-1)<0)==1,"ENGRAVE ctx_teleengr signedness");
_Static_assert(sizeof(((struct teleport_engrave_context*)0)->zapwand)==1,"ENGRAVE ctx_zapwand width");
_Static_assert((((__typeof__(((struct teleport_engrave_context*)0)->zapwand))-1)<0)==1,"ENGRAVE ctx_zapwand signedness");
_Static_assert(sizeof(((struct teleport_engrave_context*)0)->disprefresh)==1,"ENGRAVE ctx_disprefresh width");
_Static_assert((((__typeof__(((struct teleport_engrave_context*)0)->disprefresh))-1)<0)==1,"ENGRAVE ctx_disprefresh signedness");
_Static_assert(sizeof(((struct teleport_engrave_context*)0)->frosted)==1,"ENGRAVE ctx_frosted width");
_Static_assert((((__typeof__(((struct teleport_engrave_context*)0)->frosted))-1)<0)==1,"ENGRAVE ctx_frosted signedness");
_Static_assert(sizeof(((struct teleport_engrave_context*)0)->adding)==1,"ENGRAVE ctx_adding width");
_Static_assert((((__typeof__(((struct teleport_engrave_context*)0)->adding))-1)<0)==1,"ENGRAVE ctx_adding signedness");
_Static_assert(sizeof(((struct teleport_engrave_context*)0)->ret)==4,"ENGRAVE ctx_ret width");
_Static_assert((((__typeof__(((struct teleport_engrave_context*)0)->ret))-1)<0)==1,"ENGRAVE ctx_ret signedness");
_Static_assert(sizeof(((struct teleport_engrave_context*)0)->type)==4,"ENGRAVE ctx_type width");
_Static_assert((((__typeof__(((struct teleport_engrave_context*)0)->type))-1)<0)==1,"ENGRAVE ctx_type signedness");
_Static_assert(sizeof(((struct teleport_engrave_context*)0)->oetype)==4,"ENGRAVE ctx_oetype width");
_Static_assert((((__typeof__(((struct teleport_engrave_context*)0)->oetype))-1)<0)==1,"ENGRAVE ctx_oetype signedness");
_Static_assert(sizeof(((struct teleport_engrave_context*)0)->otmp)==8,"ENGRAVE ctx_otmp width");
_Static_assert(sizeof(((struct teleport_engrave_context*)0)->oep)==8,"ENGRAVE ctx_oep width");
_Static_assert(sizeof(((struct teleport_engrave_context*)0)->writer)==8,"ENGRAVE ctx_writer width");
_Static_assert(sizeof(((struct teleport_engrave_context*)0)->everb)==8,"ENGRAVE ctx_everb width");
_Static_assert(sizeof(((struct teleport_engrave_context*)0)->eloc)==8,"ENGRAVE ctx_eloc width");
_Static_assert(sizeof(((struct teleport_engrave_context*)0)->len)==8,"ENGRAVE ctx_len width");
_Static_assert((((__typeof__(((struct teleport_engrave_context*)0)->len))-1)<0)==0,"ENGRAVE ctx_len signedness");
_Static_assert(sizeof(((struct obj*)0)->nobj)==8,"ENGRAVE obj_nobj width");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2,"ENGRAVE obj_otyp width");
_Static_assert((((__typeof__(((struct obj*)0)->otyp))-1)<0)==1,"ENGRAVE obj_otyp signedness");
_Static_assert(sizeof(((struct obj*)0)->oclass)==1,"ENGRAVE obj_oclass width");
_Static_assert((((__typeof__(((struct obj*)0)->oclass))-1)<0)==1,"ENGRAVE obj_oclass signedness");
_Static_assert(sizeof(((struct obj*)0)->oartifact)==1,"ENGRAVE obj_oartifact width");
_Static_assert((((__typeof__(((struct obj*)0)->oartifact))-1)<0)==1,"ENGRAVE obj_oartifact signedness");
_Static_assert(sizeof(((struct obj*)0)->spe)==1,"ENGRAVE obj_spe width");
_Static_assert((((__typeof__(((struct obj*)0)->spe))-1)<0)==1,"ENGRAVE obj_spe signedness");
_Static_assert(sizeof(((struct obj*)0)->owornmask)==8,"ENGRAVE obj_owornmask width");
_Static_assert((((__typeof__(((struct obj*)0)->owornmask))-1)<0)==1,"ENGRAVE obj_owornmask signedness");
_Static_assert(sizeof(((struct obj*)0)->quan)==8,"ENGRAVE obj_quan width");
_Static_assert((((__typeof__(((struct obj*)0)->quan))-1)<0)==1,"ENGRAVE obj_quan signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_skill)==1,"ENGRAVE cls_oc_skill width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_skill))-1)<0)==1,"ENGRAVE cls_oc_skill signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_armcat)==1,"ENGRAVE cls_oc_armcat width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_armcat))-1)<0)==1,"ENGRAVE cls_oc_armcat signedness");
_Static_assert(sizeof(((struct monst*)0)->data)==8,"ENGRAVE mon_data width");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8,"ENGRAVE pm_mflags1 width");
_Static_assert((((__typeof__(((struct permonst*)0)->mflags1))-1)<0)==0,"ENGRAVE pm_mflags1 signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8,"ENGRAVE pm_mflags2 width");
_Static_assert((((__typeof__(((struct permonst*)0)->mflags2))-1)<0)==0,"ENGRAVE pm_mflags2 signedness");
_Static_assert(sizeof(((struct permonst*)0)->msize)==1,"ENGRAVE pm_msize width");
_Static_assert((((__typeof__(((struct permonst*)0)->msize))-1)<0)==0,"ENGRAVE pm_msize signedness");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1,"ENGRAVE pm_mlet width");
_Static_assert((((__typeof__(((struct permonst*)0)->mlet))-1)<0)==1,"ENGRAVE pm_mlet signedness");
_Static_assert(sizeof(((struct you*)0)->ux)==2,"ENGRAVE u_ux width");
_Static_assert((((__typeof__(((struct you*)0)->ux))-1)<0)==1,"ENGRAVE u_ux signedness");
_Static_assert(sizeof(((struct you*)0)->uy)==2,"ENGRAVE u_uy width");
_Static_assert((((__typeof__(((struct you*)0)->uy))-1)<0)==1,"ENGRAVE u_uy signedness");
_Static_assert(sizeof(((struct you*)0)->ustuck)==8,"ENGRAVE u_ustuck width");
_Static_assert(sizeof(((struct you*)0)->usteed)==8,"ENGRAVE u_usteed width");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8,"ENGRAVE prop_intrinsic width");
_Static_assert((((__typeof__(((struct prop*)0)->intrinsic))-1)<0)==1,"ENGRAVE prop_intrinsic signedness");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8,"ENGRAVE prop_extrinsic width");
_Static_assert((((__typeof__(((struct prop*)0)->extrinsic))-1)<0)==1,"ENGRAVE prop_extrinsic signedness");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8,"ENGRAVE prop_blocked width");
_Static_assert((((__typeof__(((struct prop*)0)->blocked))-1)<0)==1,"ENGRAVE prop_blocked signedness");
_Static_assert(sizeof(((struct rm*)0)->typ)==1,"ENGRAVE rm_typ width");
_Static_assert((((__typeof__(((struct rm*)0)->typ))-1)<0)==1,"ENGRAVE rm_typ signedness");
_Static_assert(sizeof(((coord*)0)->x)==2,"ENGRAVE coord_x width");
_Static_assert((((__typeof__(((coord*)0)->x))-1)<0)==1,"ENGRAVE coord_x signedness");
_Static_assert(sizeof(((coord*)0)->y)==2,"ENGRAVE coord_y width");
_Static_assert((((__typeof__(((coord*)0)->y))-1)<0)==1,"ENGRAVE coord_y signedness");
_Static_assert(sizeof(((d_level*)0)->dnum)==2,"ENGRAVE dlevel_dnum width");
_Static_assert((((__typeof__(((d_level*)0)->dnum))-1)<0)==1,"ENGRAVE dlevel_dnum signedness");
_Static_assert(sizeof(((d_level*)0)->dlevel)==2,"ENGRAVE dlevel_dlevel width");
_Static_assert((((__typeof__(((d_level*)0)->dlevel))-1)<0)==1,"ENGRAVE dlevel_dlevel signedness");
_Static_assert(sizeof(((struct engrave_info*)0)->nextc)==8,"ENGRAVE occupation_nextc width");
_Static_assert(sizeof(((struct engrave_info*)0)->stylus)==8,"ENGRAVE occupation_stylus width");
_Static_assert(sizeof(((struct engrave_info*)0)->type)==1,"ENGRAVE occupation_type width");
_Static_assert((((__typeof__(((struct engrave_info*)0)->type))-1)<0)==1,"ENGRAVE occupation_type signedness");
_Static_assert(sizeof(((struct engrave_info*)0)->actionct)==4,"ENGRAVE occupation_actionct width");
_Static_assert((((__typeof__(((struct engrave_info*)0)->actionct))-1)<0)==1,"ENGRAVE occupation_actionct signedness");
_Static_assert(sizeof(((NHFILE*)0)->mode)==4,"ENGRAVE nhfile_mode width");
_Static_assert((((__typeof__(((NHFILE*)0)->mode))-1)<0)==1,"ENGRAVE nhfile_mode signedness");
_Static_assert(sizeof(((struct skills*)0)->skill)==2,"ENGRAVE skill_skill width");
_Static_assert((((__typeof__(((struct skills*)0)->skill))-1)<0)==1,"ENGRAVE skill_skill signedness");
_Static_assert(sizeof(u.weapon_skills[0])==sizeof(struct skills),"ENGRAVE actual hero skill element");
_Static_assert(sizeof(u.uconduct.literate)==8,"ENGRAVE literate long64");
_Static_assert(sizeof(svc.context.run)==4,"ENGRAVE run int32");
_Static_assert(sizeof(gi.in_mklev)==1,"ENGRAVE mklev bool8");
_Static_assert(sizeof(svm.moves)==8&&sizeof(gm.multi)==8,"ENGRAVE clock64");
#undef EMETA
#endif
