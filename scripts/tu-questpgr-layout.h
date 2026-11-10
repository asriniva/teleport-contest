#ifndef TELEPORT_QUESTPGR_LAYOUT_H
#define TELEPORT_QUESTPGR_LAYOUT_H
#include "hack.h"
#include <stddef.h>
struct teleport_questpgr_meta {const char *name; size_t value;};
#define QUESTPGR_META(k,v) {#k,(size_t)(v)}
static const struct teleport_questpgr_meta questpgr_layout[]={
QUESTPGR_META(pointerSize,sizeof(void*)),
QUESTPGR_META(intSize,sizeof(int)),
QUESTPGR_META(longSize,sizeof(long)),
QUESTPGR_META(shortSize,sizeof(short)),
QUESTPGR_META(roleSize,sizeof(struct Role)),
QUESTPGR_META(role_questarti,offsetof(struct Role,questarti)),
QUESTPGR_META(role_questarti_size,sizeof(((struct Role*)0)->questarti)),
QUESTPGR_META(role_ldrnum,offsetof(struct Role,ldrnum)),
QUESTPGR_META(role_ldrnum_size,sizeof(((struct Role*)0)->ldrnum)),
QUESTPGR_META(role_neminum,offsetof(struct Role,neminum)),
QUESTPGR_META(role_neminum_size,sizeof(((struct Role*)0)->neminum)),
QUESTPGR_META(role_guardnum,offsetof(struct Role,guardnum)),
QUESTPGR_META(role_guardnum_size,sizeof(((struct Role*)0)->guardnum)),
QUESTPGR_META(role_enemy1num,offsetof(struct Role,enemy1num)),
QUESTPGR_META(role_enemy1num_size,sizeof(((struct Role*)0)->enemy1num)),
QUESTPGR_META(role_enemy2num,offsetof(struct Role,enemy2num)),
QUESTPGR_META(role_enemy2num_size,sizeof(((struct Role*)0)->enemy2num)),
QUESTPGR_META(role_enemy1sym,offsetof(struct Role,enemy1sym)),
QUESTPGR_META(role_enemy1sym_size,sizeof(((struct Role*)0)->enemy1sym)),
QUESTPGR_META(role_enemy2sym,offsetof(struct Role,enemy2sym)),
QUESTPGR_META(role_enemy2sym_size,sizeof(((struct Role*)0)->enemy2sym)),
QUESTPGR_META(role_mnum,offsetof(struct Role,mnum)),
QUESTPGR_META(role_mnum_size,sizeof(((struct Role*)0)->mnum)),
QUESTPGR_META(role_filecode,offsetof(struct Role,filecode)),
QUESTPGR_META(role_filecode_size,sizeof(((struct Role*)0)->filecode)),
QUESTPGR_META(role_homebase,offsetof(struct Role,homebase)),
QUESTPGR_META(role_homebase_size,sizeof(((struct Role*)0)->homebase)),
QUESTPGR_META(role_intermed,offsetof(struct Role,intermed)),
QUESTPGR_META(role_intermed_size,sizeof(((struct Role*)0)->intermed)),
QUESTPGR_META(role_name_m,offsetof(struct Role,name.m)),
QUESTPGR_META(role_name_m_size,sizeof(((struct Role*)0)->name.m)),
QUESTPGR_META(role_name_f,offsetof(struct Role,name.f)),
QUESTPGR_META(role_name_f_size,sizeof(((struct Role*)0)->name.f)),
QUESTPGR_META(objSize,sizeof(struct obj)),
QUESTPGR_META(obj_nobj,offsetof(struct obj,nobj)),
QUESTPGR_META(obj_nobj_size,sizeof(((struct obj*)0)->nobj)),
QUESTPGR_META(obj_cobj,offsetof(struct obj,cobj)),
QUESTPGR_META(obj_cobj_size,sizeof(((struct obj*)0)->cobj)),
QUESTPGR_META(obj_oartifact,offsetof(struct obj,oartifact)),
QUESTPGR_META(obj_oartifact_size,sizeof(((struct obj*)0)->oartifact)),
QUESTPGR_META(monSize,sizeof(struct monst)),
QUESTPGR_META(mon_nmon,offsetof(struct monst,nmon)),
QUESTPGR_META(mon_nmon_size,sizeof(((struct monst*)0)->nmon)),
QUESTPGR_META(mon_minvent,offsetof(struct monst,minvent)),
QUESTPGR_META(mon_minvent_size,sizeof(((struct monst*)0)->minvent)),
QUESTPGR_META(mon_mhp,offsetof(struct monst,mhp)),
QUESTPGR_META(mon_mhp_size,sizeof(((struct monst*)0)->mhp)),
QUESTPGR_META(pmSize,sizeof(struct permonst)),
QUESTPGR_META(pm_pmnames,offsetof(struct permonst,pmnames)),
QUESTPGR_META(pm_pmnames_size,sizeof(((struct permonst*)0)->pmnames)),
QUESTPGR_META(pm_mflags2,offsetof(struct permonst,mflags2)),
QUESTPGR_META(pm_mflags2_size,sizeof(((struct permonst*)0)->mflags2)),
QUESTPGR_META(genderSize,sizeof(struct Gender)),
QUESTPGR_META(gender_he,offsetof(struct Gender,he)),
QUESTPGR_META(gender_he_size,sizeof(((struct Gender*)0)->he)),
QUESTPGR_META(gender_him,offsetof(struct Gender,him)),
QUESTPGR_META(gender_him_size,sizeof(((struct Gender*)0)->him)),
QUESTPGR_META(gender_his,offsetof(struct Gender,his)),
QUESTPGR_META(gender_his_size,sizeof(((struct Gender*)0)->his)),
QUESTPGR_META(uSize,sizeof(struct you)),
QUESTPGR_META(u_ulevel,offsetof(struct you,ulevel)),
QUESTPGR_META(u_ulevel_size,sizeof(((struct you*)0)->ulevel)),
QUESTPGR_META(u_ualignbase,offsetof(struct you,ualignbase)),
QUESTPGR_META(u_ualignbase_size,sizeof(((struct you*)0)->ualignbase)),
QUESTPGR_META(u_ualign_type,offsetof(struct you,ualign.type)),
QUESTPGR_META(u_ualign_type_size,sizeof(((struct you*)0)->ualign.type)),
QUESTPGR_META(u_uprops,offsetof(struct you,uprops)),
QUESTPGR_META(u_uprops_size,sizeof(((struct you*)0)->uprops)),
QUESTPGR_META(propSize,sizeof(struct prop)),
QUESTPGR_META(prop_intrinsic,offsetof(struct prop,intrinsic)),
QUESTPGR_META(prop_intrinsic_size,sizeof(((struct prop*)0)->intrinsic)),
QUESTPGR_META(prop_extrinsic,offsetof(struct prop,extrinsic)),
QUESTPGR_META(prop_extrinsic_size,sizeof(((struct prop*)0)->extrinsic)),
QUESTPGR_META(prop_blocked,offsetof(struct prop,blocked)),
QUESTPGR_META(prop_blocked_size,sizeof(((struct prop*)0)->blocked)),
QUESTPGR_META(vitalSize,sizeof(struct mvitals)),
QUESTPGR_META(vital_mvflags,offsetof(struct mvitals,mvflags)),
QUESTPGR_META(vital_mvflags_size,sizeof(((struct mvitals*)0)->mvflags)),
QUESTPGR_META(dungeonSize,sizeof(dungeon)),
QUESTPGR_META(dungeon_dname,offsetof(dungeon,dname)),
QUESTPGR_META(dungeon_dname_size,sizeof(((dungeon*)0)->dname)),
QUESTPGR_META(sandboxSize,sizeof(nhl_sandbox_info)),
QUESTPGR_META(sandbox_flags,offsetof(nhl_sandbox_info,flags)),
QUESTPGR_META(sandbox_flags_size,sizeof(((nhl_sandbox_info*)0)->flags)),
QUESTPGR_META(sandbox_memlimit,offsetof(nhl_sandbox_info,memlimit)),
QUESTPGR_META(sandbox_memlimit_size,sizeof(((nhl_sandbox_info*)0)->memlimit)),
QUESTPGR_META(sandbox_steps,offsetof(nhl_sandbox_info,steps)),
QUESTPGR_META(sandbox_steps_size,sizeof(((nhl_sandbox_info*)0)->steps)),
QUESTPGR_META(sandbox_perpcall,offsetof(nhl_sandbox_info,perpcall)),
QUESTPGR_META(sandbox_perpcall_size,sizeof(((nhl_sandbox_info*)0)->perpcall)),
QUESTPGR_META(urole,offsetof(__typeof__(gu),urole)),
QUESTPGR_META(urole_size,sizeof(gu.urole)),
QUESTPGR_META(nambuf,offsetof(__typeof__(gn),nambuf)),
QUESTPGR_META(nambuf_size,sizeof(gn.nambuf)),
QUESTPGR_META(invent,offsetof(__typeof__(gi),invent)),
QUESTPGR_META(invent_size,sizeof(gi.invent)),
QUESTPGR_META(floorObjects,offsetof(__typeof__(svl),level.objlist)),
QUESTPGR_META(floorObjects_size,sizeof(svl.level.objlist)),
QUESTPGR_META(floorMonsters,offsetof(__typeof__(svl),level.monlist)),
QUESTPGR_META(floorMonsters_size,sizeof(svl.level.monlist)),
QUESTPGR_META(buried,offsetof(__typeof__(svl),level.buriedobjlist)),
QUESTPGR_META(buried_size,sizeof(svl.level.buriedobjlist)),
QUESTPGR_META(migrating_mons,offsetof(__typeof__(gm),migrating_mons)),
QUESTPGR_META(migrating_mons_size,sizeof(gm.migrating_mons)),
QUESTPGR_META(migrating_objs,offsetof(__typeof__(gm),migrating_objs)),
QUESTPGR_META(migrating_objs_size,sizeof(gm.migrating_objs)),
QUESTPGR_META(cvt_buf,offsetof(__typeof__(gc),cvt_buf)),
QUESTPGR_META(cvt_buf_size,sizeof(gc.cvt_buf)),
QUESTPGR_META(plname,offsetof(__typeof__(svp),plname)),
QUESTPGR_META(plname_size,sizeof(svp.plname)),
QUESTPGR_META(dungeons,offsetof(__typeof__(svd),dungeons)),
QUESTPGR_META(dungeons_size,sizeof(svd.dungeons)),
QUESTPGR_META(mvitals,offsetof(__typeof__(svm),mvitals)),
QUESTPGR_META(mvitals_size,sizeof(svm.mvitals)),
QUESTPGR_META(female,offsetof(__typeof__(flags),female)),
QUESTPGR_META(female_size,sizeof(flags.female)),
QUESTPGR_META(wizkit_wishing,offsetof(__typeof__(program_state),wizkit_wishing)),
QUESTPGR_META(wizkit_wishing_size,sizeof(program_state.wizkit_wishing)),
QUESTPGR_META(lev_message,offsetof(__typeof__(gl),lev_message)),
QUESTPGR_META(lev_message_size,sizeof(gl.lev_message)),
QUESTPGR_META(BUFSZ,BUFSZ),
QUESTPGR_META(CVT_BUF_SIZE,CVT_BUF_SIZE),
QUESTPGR_META(MS_LEADER,MS_LEADER),
QUESTPGR_META(MS_NEMESIS,MS_NEMESIS),
QUESTPGR_META(MS_GUARDIAN,MS_GUARDIAN),
QUESTPGR_META(NEUTRAL,NEUTRAL),
QUESTPGR_META(MIN_QUEST_LEVEL,MIN_QUEST_LEVEL),
QUESTPGR_META(A_ORIGINAL,A_ORIGINAL),
QUESTPGR_META(A_LAWFUL,A_LAWFUL),
QUESTPGR_META(A_CHAOTIC,A_CHAOTIC),
QUESTPGR_META(A_NEUTRAL,A_NEUTRAL),
QUESTPGR_META(OBJ_INVENT,OBJ_INVENT),
QUESTPGR_META(OBJ_FLOOR,OBJ_FLOOR),
QUESTPGR_META(OBJ_MINVENT,OBJ_MINVENT),
QUESTPGR_META(OBJ_MIGRATING,OBJ_MIGRATING),
QUESTPGR_META(OBJ_BURIED,OBJ_BURIED),
QUESTPGR_META(M2_PNAME,M2_PNAME),
QUESTPGR_META(NON_PM,NON_PM),
QUESTPGR_META(G_GENOD,G_GENOD),
QUESTPGR_META(NHL_SB_SAFE,NHL_SB_SAFE),
QUESTPGR_META(NHW_MENU,NHW_MENU),
QUESTPGR_META(NHW_TEXT,NHW_TEXT),
QUESTPGR_META(LUA_TTABLE,LUA_TTABLE),
QUESTPGR_META(BLINDED,BLINDED),
QUESTPGR_META(PM_HUMAN,PM_HUMAN),
QUESTPGR_META(PM_MEDUSA,PM_MEDUSA),
QUESTPGR_META(PM_WIZARD_OF_YENDOR,PM_WIZARD_OF_YENDOR),
QUESTPGR_META(PM_SOLDIER,PM_SOLDIER),
QUESTPGR_META(PM_GIANT_ANT,PM_GIANT_ANT),
QUESTPGR_META(ART_ORB_OF_DETECTION,ART_ORB_OF_DETECTION),
};
#undef QUESTPGR_META
_Static_assert(sizeof(((struct Role*)0)->questarti)==2,"role_questarti width");
_Static_assert(((__typeof__(((struct Role*)0)->questarti))-1 < 0),"role_questarti signedness");
_Static_assert(sizeof(((struct Role*)0)->ldrnum)==2,"role_ldrnum width");
_Static_assert(((__typeof__(((struct Role*)0)->ldrnum))-1 < 0),"role_ldrnum signedness");
_Static_assert(sizeof(((struct Role*)0)->neminum)==2,"role_neminum width");
_Static_assert(((__typeof__(((struct Role*)0)->neminum))-1 < 0),"role_neminum signedness");
_Static_assert(sizeof(((struct Role*)0)->guardnum)==2,"role_guardnum width");
_Static_assert(((__typeof__(((struct Role*)0)->guardnum))-1 < 0),"role_guardnum signedness");
_Static_assert(sizeof(((struct Role*)0)->enemy1num)==2,"role_enemy1num width");
_Static_assert(((__typeof__(((struct Role*)0)->enemy1num))-1 < 0),"role_enemy1num signedness");
_Static_assert(sizeof(((struct Role*)0)->enemy2num)==2,"role_enemy2num width");
_Static_assert(((__typeof__(((struct Role*)0)->enemy2num))-1 < 0),"role_enemy2num signedness");
_Static_assert(sizeof(((struct Role*)0)->enemy1sym)==1,"role_enemy1sym width");
_Static_assert(((__typeof__(((struct Role*)0)->enemy1sym))-1 < 0),"role_enemy1sym signedness");
_Static_assert(sizeof(((struct Role*)0)->enemy2sym)==1,"role_enemy2sym width");
_Static_assert(((__typeof__(((struct Role*)0)->enemy2sym))-1 < 0),"role_enemy2sym signedness");
_Static_assert(sizeof(((struct Role*)0)->mnum)==2,"role_mnum width");
_Static_assert(((__typeof__(((struct Role*)0)->mnum))-1 < 0),"role_mnum signedness");
_Static_assert(sizeof(((struct Role*)0)->filecode)==8,"role_filecode width");
_Static_assert(sizeof(((struct Role*)0)->homebase)==8,"role_homebase width");
_Static_assert(sizeof(((struct Role*)0)->intermed)==8,"role_intermed width");
_Static_assert(sizeof(((struct Role*)0)->name.m)==8,"role_name_m width");
_Static_assert(sizeof(((struct Role*)0)->name.f)==8,"role_name_f width");
_Static_assert(sizeof(((struct obj*)0)->nobj)==8,"obj_nobj width");
_Static_assert(sizeof(((struct obj*)0)->cobj)==8,"obj_cobj width");
_Static_assert(sizeof(((struct obj*)0)->oartifact)==1,"obj_oartifact width");
_Static_assert(((__typeof__(((struct obj*)0)->oartifact))-1 < 0),"obj_oartifact signedness");
_Static_assert(sizeof(((struct monst*)0)->nmon)==8,"mon_nmon width");
_Static_assert(sizeof(((struct monst*)0)->minvent)==8,"mon_minvent width");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4,"mon_mhp width");
_Static_assert(((__typeof__(((struct monst*)0)->mhp))-1 < 0),"mon_mhp signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8,"pm_mflags2 width");
_Static_assert(((__typeof__(((struct permonst*)0)->mflags2))-1 > 0),"pm_mflags2 signedness");
_Static_assert(sizeof(((struct Gender*)0)->he)==8,"gender_he width");
_Static_assert(sizeof(((struct Gender*)0)->him)==8,"gender_him width");
_Static_assert(sizeof(((struct Gender*)0)->his)==8,"gender_his width");
_Static_assert(sizeof(((struct you*)0)->ulevel)==4,"u_ulevel width");
_Static_assert(((__typeof__(((struct you*)0)->ulevel))-1 < 0),"u_ulevel signedness");
_Static_assert(sizeof(((struct you*)0)->ualign.type)==1,"u_ualign_type width");
_Static_assert(((__typeof__(((struct you*)0)->ualign.type))-1 < 0),"u_ualign_type signedness");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8,"prop_intrinsic width");
_Static_assert(((__typeof__(((struct prop*)0)->intrinsic))-1 < 0),"prop_intrinsic signedness");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8,"prop_extrinsic width");
_Static_assert(((__typeof__(((struct prop*)0)->extrinsic))-1 < 0),"prop_extrinsic signedness");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8,"prop_blocked width");
_Static_assert(((__typeof__(((struct prop*)0)->blocked))-1 < 0),"prop_blocked signedness");
_Static_assert(sizeof(((struct mvitals*)0)->mvflags)==1,"vital_mvflags width");
_Static_assert(((__typeof__(((struct mvitals*)0)->mvflags))-1 > 0),"vital_mvflags signedness");
_Static_assert(sizeof(((nhl_sandbox_info*)0)->flags)==4,"sandbox_flags width");
_Static_assert(((__typeof__(((nhl_sandbox_info*)0)->flags))-1 > 0),"sandbox_flags signedness");
_Static_assert(sizeof(((nhl_sandbox_info*)0)->memlimit)==4,"sandbox_memlimit width");
_Static_assert(((__typeof__(((nhl_sandbox_info*)0)->memlimit))-1 > 0),"sandbox_memlimit signedness");
_Static_assert(sizeof(((nhl_sandbox_info*)0)->steps)==4,"sandbox_steps width");
_Static_assert(((__typeof__(((nhl_sandbox_info*)0)->steps))-1 > 0),"sandbox_steps signedness");
_Static_assert(sizeof(((nhl_sandbox_info*)0)->perpcall)==4,"sandbox_perpcall width");
_Static_assert(((__typeof__(((nhl_sandbox_info*)0)->perpcall))-1 > 0),"sandbox_perpcall signedness");
_Static_assert(sizeof(flags.female)==1 && (__typeof__(flags.female))-1 < 0,"female signed8");
_Static_assert(sizeof(program_state.wizkit_wishing)==4,"wizkit integer32");
_Static_assert((char)-1<0,"source plain char signed8");
_Static_assert(sizeof(u.ualignbase[0])==1 && (__typeof__(u.ualignbase[0]))-1<0,"alignment bases signed8");
_Static_assert(sizeof(gc.cvt_buf)==CVT_BUF_SIZE && sizeof(gn.nambuf)==CVT_BUF_SIZE,"conversion buffers");
size_t probe_context_size(void){return sizeof(struct Role);}
int probe_layout_count(void){return sizeof questpgr_layout/sizeof questpgr_layout[0];}
const char*probe_layout_name(int i){return questpgr_layout[i].name;}
size_t probe_layout_value(int i){return questpgr_layout[i].value;}
#endif
