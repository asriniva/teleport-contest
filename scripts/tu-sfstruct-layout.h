#ifndef TELEPORT_TU_SFSTRUCT_LAYOUT_H
#define TELEPORT_TU_SFSTRUCT_LAYOUT_H
#include "hack.h"
#include "sfprocs.h"
#include <stddef.h>
extern void historical_sfo_arti_info(NHFILE *, struct arti_info *, const char *);
extern void historical_sfi_arti_info(NHFILE *, struct arti_info *, const char *);
extern void historical_sfo_nhrect(NHFILE *, struct nhrect *, const char *);
extern void historical_sfi_nhrect(NHFILE *, struct nhrect *, const char *);
extern void historical_sfo_branch(NHFILE *, struct branch *, const char *);
extern void historical_sfi_branch(NHFILE *, struct branch *, const char *);
extern void historical_sfo_bubble(NHFILE *, struct bubble *, const char *);
extern void historical_sfi_bubble(NHFILE *, struct bubble *, const char *);
extern void historical_sfo_cemetery(NHFILE *, struct cemetery *, const char *);
extern void historical_sfi_cemetery(NHFILE *, struct cemetery *, const char *);
extern void historical_sfo_context_info(NHFILE *, struct context_info *, const char *);
extern void historical_sfi_context_info(NHFILE *, struct context_info *, const char *);
extern void historical_sfo_nhcoord(NHFILE *, struct nhcoord *, const char *);
extern void historical_sfi_nhcoord(NHFILE *, struct nhcoord *, const char *);
extern void historical_sfo_damage(NHFILE *, struct damage *, const char *);
extern void historical_sfi_damage(NHFILE *, struct damage *, const char *);
extern void historical_sfo_dest_area(NHFILE *, struct dest_area *, const char *);
extern void historical_sfi_dest_area(NHFILE *, struct dest_area *, const char *);
extern void historical_sfo_dgn_topology(NHFILE *, struct dgn_topology *, const char *);
extern void historical_sfi_dgn_topology(NHFILE *, struct dgn_topology *, const char *);
extern void historical_sfo_dungeon(NHFILE *, struct dungeon *, const char *);
extern void historical_sfi_dungeon(NHFILE *, struct dungeon *, const char *);
extern void historical_sfo_d_level(NHFILE *, struct d_level *, const char *);
extern void historical_sfi_d_level(NHFILE *, struct d_level *, const char *);
extern void historical_sfo_ebones(NHFILE *, struct ebones *, const char *);
extern void historical_sfi_ebones(NHFILE *, struct ebones *, const char *);
extern void historical_sfo_edog(NHFILE *, struct edog *, const char *);
extern void historical_sfi_edog(NHFILE *, struct edog *, const char *);
extern void historical_sfo_egd(NHFILE *, struct egd *, const char *);
extern void historical_sfi_egd(NHFILE *, struct egd *, const char *);
extern void historical_sfo_emin(NHFILE *, struct emin *, const char *);
extern void historical_sfi_emin(NHFILE *, struct emin *, const char *);
extern void historical_sfo_engr(NHFILE *, struct engr *, const char *);
extern void historical_sfi_engr(NHFILE *, struct engr *, const char *);
extern void historical_sfo_epri(NHFILE *, struct epri *, const char *);
extern void historical_sfi_epri(NHFILE *, struct epri *, const char *);
extern void historical_sfo_eshk(NHFILE *, struct eshk *, const char *);
extern void historical_sfi_eshk(NHFILE *, struct eshk *, const char *);
extern void historical_sfo_fe(NHFILE *, struct fe *, const char *);
extern void historical_sfi_fe(NHFILE *, struct fe *, const char *);
extern void historical_sfo_flag(NHFILE *, struct flag *, const char *);
extern void historical_sfi_flag(NHFILE *, struct flag *, const char *);
extern void historical_sfo_fruit(NHFILE *, struct fruit *, const char *);
extern void historical_sfi_fruit(NHFILE *, struct fruit *, const char *);
extern void historical_sfo_gamelog_line(NHFILE *, struct gamelog_line *, const char *);
extern void historical_sfi_gamelog_line(NHFILE *, struct gamelog_line *, const char *);
extern void historical_sfo_kinfo(NHFILE *, struct kinfo *, const char *);
extern void historical_sfi_kinfo(NHFILE *, struct kinfo *, const char *);
extern void historical_sfo_levelflags(NHFILE *, struct levelflags *, const char *);
extern void historical_sfi_levelflags(NHFILE *, struct levelflags *, const char *);
extern void historical_sfo_ls_t(NHFILE *, struct ls_t *, const char *);
extern void historical_sfi_ls_t(NHFILE *, struct ls_t *, const char *);
extern void historical_sfo_linfo(NHFILE *, struct linfo *, const char *);
extern void historical_sfi_linfo(NHFILE *, struct linfo *, const char *);
extern void historical_sfo_mapseen_feat(NHFILE *, struct mapseen_feat *, const char *);
extern void historical_sfi_mapseen_feat(NHFILE *, struct mapseen_feat *, const char *);
extern void historical_sfo_mapseen_flags(NHFILE *, struct mapseen_flags *, const char *);
extern void historical_sfi_mapseen_flags(NHFILE *, struct mapseen_flags *, const char *);
extern void historical_sfo_mapseen_rooms(NHFILE *, struct mapseen_rooms *, const char *);
extern void historical_sfi_mapseen_rooms(NHFILE *, struct mapseen_rooms *, const char *);
extern void historical_sfo_mkroom(NHFILE *, struct mkroom *, const char *);
extern void historical_sfi_mkroom(NHFILE *, struct mkroom *, const char *);
extern void historical_sfo_monst(NHFILE *, struct monst *, const char *);
extern void historical_sfi_monst(NHFILE *, struct monst *, const char *);
extern void historical_sfo_mvitals(NHFILE *, struct mvitals *, const char *);
extern void historical_sfi_mvitals(NHFILE *, struct mvitals *, const char *);
extern void historical_sfo_obj(NHFILE *, struct obj *, const char *);
extern void historical_sfi_obj(NHFILE *, struct obj *, const char *);
extern void historical_sfo_objclass(NHFILE *, struct objclass *, const char *);
extern void historical_sfi_objclass(NHFILE *, struct objclass *, const char *);
extern void historical_sfo_q_score(NHFILE *, struct q_score *, const char *);
extern void historical_sfi_q_score(NHFILE *, struct q_score *, const char *);
extern void historical_sfo_rm(NHFILE *, struct rm *, const char *);
extern void historical_sfi_rm(NHFILE *, struct rm *, const char *);
extern void historical_sfo_spell(NHFILE *, struct spell *, const char *);
extern void historical_sfi_spell(NHFILE *, struct spell *, const char *);
extern void historical_sfo_stairway(NHFILE *, struct stairway *, const char *);
extern void historical_sfi_stairway(NHFILE *, struct stairway *, const char *);
extern void historical_sfo_s_level(NHFILE *, struct s_level *, const char *);
extern void historical_sfi_s_level(NHFILE *, struct s_level *, const char *);
extern void historical_sfo_trap(NHFILE *, struct trap *, const char *);
extern void historical_sfi_trap(NHFILE *, struct trap *, const char *);
extern void historical_sfo_you(NHFILE *, struct you *, const char *);
extern void historical_sfi_you(NHFILE *, struct you *, const char *);
extern void historical_sfo_any(NHFILE *, union any *, const char *);
extern void historical_sfi_any(NHFILE *, union any *, const char *);
extern void historical_sfo_aligntyp(NHFILE *, aligntyp *, const char *);
extern void historical_sfi_aligntyp(NHFILE *, aligntyp *, const char *);
extern void historical_sfo_boolean(NHFILE *, boolean *, const char *);
extern void historical_sfi_boolean(NHFILE *, boolean *, const char *);
extern void historical_sfo_coordxy(NHFILE *, coordxy *, const char *);
extern void historical_sfi_coordxy(NHFILE *, coordxy *, const char *);
extern void historical_sfo_int(NHFILE *, int *, const char *);
extern void historical_sfi_int(NHFILE *, int *, const char *);
extern void historical_sfo_int16(NHFILE *, int16 *, const char *);
extern void historical_sfi_int16(NHFILE *, int16 *, const char *);
extern void historical_sfo_int32(NHFILE *, int32 *, const char *);
extern void historical_sfi_int32(NHFILE *, int32 *, const char *);
extern void historical_sfo_int64(NHFILE *, int64 *, const char *);
extern void historical_sfi_int64(NHFILE *, int64 *, const char *);
extern void historical_sfo_long(NHFILE *, long *, const char *);
extern void historical_sfi_long(NHFILE *, long *, const char *);
extern void historical_sfo_schar(NHFILE *, schar *, const char *);
extern void historical_sfi_schar(NHFILE *, schar *, const char *);
extern void historical_sfo_short(NHFILE *, short *, const char *);
extern void historical_sfi_short(NHFILE *, short *, const char *);
extern void historical_sfo_size_t(NHFILE *, size_t *, const char *);
extern void historical_sfi_size_t(NHFILE *, size_t *, const char *);
extern void historical_sfo_time_t(NHFILE *, time_t *, const char *);
extern void historical_sfi_time_t(NHFILE *, time_t *, const char *);
extern void historical_sfo_uchar(NHFILE *, uchar *, const char *);
extern void historical_sfi_uchar(NHFILE *, uchar *, const char *);
extern void historical_sfo_uint16(NHFILE *, uint16 *, const char *);
extern void historical_sfi_uint16(NHFILE *, uint16 *, const char *);
extern void historical_sfo_uint32(NHFILE *, uint32 *, const char *);
extern void historical_sfi_uint32(NHFILE *, uint32 *, const char *);
extern void historical_sfo_uint64(NHFILE *, uint64 *, const char *);
extern void historical_sfi_uint64(NHFILE *, uint64 *, const char *);
extern void historical_sfo_ulong(NHFILE *, ulong *, const char *);
extern void historical_sfi_ulong(NHFILE *, ulong *, const char *);
extern void historical_sfo_unsigned(NHFILE *, unsigned *, const char *);
extern void historical_sfi_unsigned(NHFILE *, unsigned *, const char *);
extern void historical_sfo_ushort(NHFILE *, ushort *, const char *);
extern void historical_sfi_ushort(NHFILE *, ushort *, const char *);
extern void historical_sfo_xint16(NHFILE *, xint16 *, const char *);
extern void historical_sfi_xint16(NHFILE *, xint16 *, const char *);
extern void historical_sfo_xint8(NHFILE *, xint8 *, const char *);
extern void historical_sfi_xint8(NHFILE *, xint8 *, const char *);
extern void historical_sfo_version_info(NHFILE *, struct version_info *, const char *);
extern void historical_sfi_version_info(NHFILE *, struct version_info *, const char *);
extern void historical_sfo_char(NHFILE *, char *, const char *, int);
extern void historical_sfi_char(NHFILE *, char *, const char *, int);
extern void historical_sfo_genericptr_t(NHFILE *, genericptr_t *, const char *);
extern void historical_sfi_genericptr_t(NHFILE *, genericptr_t *, const char *);
extern void historical_sfo_bitfield(NHFILE *, uint8_t *, const char *, int);
extern void historical_sfi_bitfield(NHFILE *, uint8_t *, const char *, int);
struct teleport_sfstruct_meta { const char *name; size_t value; };
#define SF_META(k,v) {#k,(size_t)(v)}
static const struct teleport_sfstruct_meta teleport_sfstruct_layout[]={
SF_META(pointerSize,sizeof(void*)),
SF_META(intSize,sizeof(int)),
SF_META(longSize,sizeof(long)),
SF_META(unsignedSize,sizeof(unsigned)),
SF_META(booleanSize,sizeof(boolean)),
SF_META(nhfileSize,sizeof(NHFILE)),
SF_META(nhf_fd,offsetof(NHFILE,fd)),
SF_META(nhf_eof,offsetof(NHFILE,eof)),
SF_META(restoreSize,sizeof(struct restore_info)),
SF_META(restore_name,offsetof(struct restore_info,name)),
SF_META(restore_flags,offsetof(struct restore_info,mread_flags)),
SF_META(program_hup,offsetof(__typeof__(program_state),done_hup)),
SF_META(program_bones,offsetof(__typeof__(program_state),reading_bonesfile)),
SF_META(program_restoring,offsetof(__typeof__(program_state),restoring)),
SF_META(procsSize,sizeof(struct sf_structlevel_procs)),
SF_META(procs_ext,offsetof(struct sf_structlevel_procs,ext)),
SF_META(procs_fn,offsetof(struct sf_structlevel_procs,fn)),
SF_META(MAXFD,5),
SF_META(NOFLG,0),
SF_META(NOSLOT,1),
SF_META(EOF,EOF),
SF_META(EXIT_FAILURE,EXIT_FAILURE),
SF_META(type_arti_info_size,sizeof(struct arti_info)),
SF_META(type_nhrect_size,sizeof(struct nhrect)),
SF_META(type_branch_size,sizeof(struct branch)),
SF_META(type_bubble_size,sizeof(struct bubble)),
SF_META(type_cemetery_size,sizeof(struct cemetery)),
SF_META(type_context_info_size,sizeof(struct context_info)),
SF_META(type_nhcoord_size,sizeof(struct nhcoord)),
SF_META(type_damage_size,sizeof(struct damage)),
SF_META(type_dest_area_size,sizeof(struct dest_area)),
SF_META(type_dgn_topology_size,sizeof(struct dgn_topology)),
SF_META(type_dungeon_size,sizeof(struct dungeon)),
SF_META(type_d_level_size,sizeof(struct d_level)),
SF_META(type_ebones_size,sizeof(struct ebones)),
SF_META(type_edog_size,sizeof(struct edog)),
SF_META(type_egd_size,sizeof(struct egd)),
SF_META(type_emin_size,sizeof(struct emin)),
SF_META(type_engr_size,sizeof(struct engr)),
SF_META(type_epri_size,sizeof(struct epri)),
SF_META(type_eshk_size,sizeof(struct eshk)),
SF_META(type_fe_size,sizeof(struct fe)),
SF_META(type_flag_size,sizeof(struct flag)),
SF_META(type_fruit_size,sizeof(struct fruit)),
SF_META(type_gamelog_line_size,sizeof(struct gamelog_line)),
SF_META(type_kinfo_size,sizeof(struct kinfo)),
SF_META(type_levelflags_size,sizeof(struct levelflags)),
SF_META(type_ls_t_size,sizeof(struct ls_t)),
SF_META(type_linfo_size,sizeof(struct linfo)),
SF_META(type_mapseen_feat_size,sizeof(struct mapseen_feat)),
SF_META(type_mapseen_flags_size,sizeof(struct mapseen_flags)),
SF_META(type_mapseen_rooms_size,sizeof(struct mapseen_rooms)),
SF_META(type_mkroom_size,sizeof(struct mkroom)),
SF_META(type_monst_size,sizeof(struct monst)),
SF_META(type_mvitals_size,sizeof(struct mvitals)),
SF_META(type_obj_size,sizeof(struct obj)),
SF_META(type_objclass_size,sizeof(struct objclass)),
SF_META(type_q_score_size,sizeof(struct q_score)),
SF_META(type_rm_size,sizeof(struct rm)),
SF_META(type_spell_size,sizeof(struct spell)),
SF_META(type_stairway_size,sizeof(struct stairway)),
SF_META(type_s_level_size,sizeof(struct s_level)),
SF_META(type_trap_size,sizeof(struct trap)),
SF_META(type_you_size,sizeof(struct you)),
SF_META(type_any_size,sizeof(union any)),
SF_META(type_aligntyp_size,sizeof(aligntyp)),
SF_META(type_boolean_size,sizeof(boolean)),
SF_META(type_coordxy_size,sizeof(coordxy)),
SF_META(type_int_size,sizeof(int)),
SF_META(type_int16_size,sizeof(int16)),
SF_META(type_int32_size,sizeof(int32)),
SF_META(type_int64_size,sizeof(int64)),
SF_META(type_long_size,sizeof(long)),
SF_META(type_schar_size,sizeof(schar)),
SF_META(type_short_size,sizeof(short)),
SF_META(type_size_t_size,sizeof(size_t)),
SF_META(type_time_t_size,sizeof(time_t)),
SF_META(type_uchar_size,sizeof(uchar)),
SF_META(type_uint16_size,sizeof(uint16)),
SF_META(type_uint32_size,sizeof(uint32)),
SF_META(type_uint64_size,sizeof(uint64)),
SF_META(type_ulong_size,sizeof(ulong)),
SF_META(type_unsigned_size,sizeof(unsigned)),
SF_META(type_ushort_size,sizeof(ushort)),
SF_META(type_xint16_size,sizeof(xint16)),
SF_META(type_xint8_size,sizeof(xint8)),
SF_META(type_version_info_size,sizeof(struct version_info)),
SF_META(type_char_size,sizeof(char)),
SF_META(type_genericptr_t_size,sizeof(genericptr_t)),
SF_META(type_bitfield_size,sizeof(uint8_t)),
SF_META(proc_arti_info,offsetof(struct sf_structlevel_procs,fn.sf_arti_info)),
SF_META(proc_nhrect,offsetof(struct sf_structlevel_procs,fn.sf_nhrect)),
SF_META(proc_branch,offsetof(struct sf_structlevel_procs,fn.sf_branch)),
SF_META(proc_bubble,offsetof(struct sf_structlevel_procs,fn.sf_bubble)),
SF_META(proc_cemetery,offsetof(struct sf_structlevel_procs,fn.sf_cemetery)),
SF_META(proc_context_info,offsetof(struct sf_structlevel_procs,fn.sf_context_info)),
SF_META(proc_nhcoord,offsetof(struct sf_structlevel_procs,fn.sf_nhcoord)),
SF_META(proc_damage,offsetof(struct sf_structlevel_procs,fn.sf_damage)),
SF_META(proc_dest_area,offsetof(struct sf_structlevel_procs,fn.sf_dest_area)),
SF_META(proc_dgn_topology,offsetof(struct sf_structlevel_procs,fn.sf_dgn_topology)),
SF_META(proc_dungeon,offsetof(struct sf_structlevel_procs,fn.sf_dungeon)),
SF_META(proc_d_level,offsetof(struct sf_structlevel_procs,fn.sf_d_level)),
SF_META(proc_ebones,offsetof(struct sf_structlevel_procs,fn.sf_ebones)),
SF_META(proc_edog,offsetof(struct sf_structlevel_procs,fn.sf_edog)),
SF_META(proc_egd,offsetof(struct sf_structlevel_procs,fn.sf_egd)),
SF_META(proc_emin,offsetof(struct sf_structlevel_procs,fn.sf_emin)),
SF_META(proc_engr,offsetof(struct sf_structlevel_procs,fn.sf_engr)),
SF_META(proc_epri,offsetof(struct sf_structlevel_procs,fn.sf_epri)),
SF_META(proc_eshk,offsetof(struct sf_structlevel_procs,fn.sf_eshk)),
SF_META(proc_fe,offsetof(struct sf_structlevel_procs,fn.sf_fe)),
SF_META(proc_flag,offsetof(struct sf_structlevel_procs,fn.sf_flag)),
SF_META(proc_fruit,offsetof(struct sf_structlevel_procs,fn.sf_fruit)),
SF_META(proc_gamelog_line,offsetof(struct sf_structlevel_procs,fn.sf_gamelog_line)),
SF_META(proc_kinfo,offsetof(struct sf_structlevel_procs,fn.sf_kinfo)),
SF_META(proc_levelflags,offsetof(struct sf_structlevel_procs,fn.sf_levelflags)),
SF_META(proc_ls_t,offsetof(struct sf_structlevel_procs,fn.sf_ls_t)),
SF_META(proc_linfo,offsetof(struct sf_structlevel_procs,fn.sf_linfo)),
SF_META(proc_mapseen_feat,offsetof(struct sf_structlevel_procs,fn.sf_mapseen_feat)),
SF_META(proc_mapseen_flags,offsetof(struct sf_structlevel_procs,fn.sf_mapseen_flags)),
SF_META(proc_mapseen_rooms,offsetof(struct sf_structlevel_procs,fn.sf_mapseen_rooms)),
SF_META(proc_mkroom,offsetof(struct sf_structlevel_procs,fn.sf_mkroom)),
SF_META(proc_monst,offsetof(struct sf_structlevel_procs,fn.sf_monst)),
SF_META(proc_mvitals,offsetof(struct sf_structlevel_procs,fn.sf_mvitals)),
SF_META(proc_obj,offsetof(struct sf_structlevel_procs,fn.sf_obj)),
SF_META(proc_objclass,offsetof(struct sf_structlevel_procs,fn.sf_objclass)),
SF_META(proc_q_score,offsetof(struct sf_structlevel_procs,fn.sf_q_score)),
SF_META(proc_rm,offsetof(struct sf_structlevel_procs,fn.sf_rm)),
SF_META(proc_spell,offsetof(struct sf_structlevel_procs,fn.sf_spell)),
SF_META(proc_stairway,offsetof(struct sf_structlevel_procs,fn.sf_stairway)),
SF_META(proc_s_level,offsetof(struct sf_structlevel_procs,fn.sf_s_level)),
SF_META(proc_trap,offsetof(struct sf_structlevel_procs,fn.sf_trap)),
SF_META(proc_version_info,offsetof(struct sf_structlevel_procs,fn.sf_version_info)),
SF_META(proc_you,offsetof(struct sf_structlevel_procs,fn.sf_you)),
SF_META(proc_any,offsetof(struct sf_structlevel_procs,fn.sf_any)),
SF_META(proc_aligntyp,offsetof(struct sf_structlevel_procs,fn.sf_aligntyp)),
SF_META(proc_boolean,offsetof(struct sf_structlevel_procs,fn.sf_boolean)),
SF_META(proc_coordxy,offsetof(struct sf_structlevel_procs,fn.sf_coordxy)),
SF_META(proc_genericptr_t,offsetof(struct sf_structlevel_procs,fn.sf_genericptr)),
SF_META(proc_int,offsetof(struct sf_structlevel_procs,fn.sf_int)),
SF_META(proc_int16,offsetof(struct sf_structlevel_procs,fn.sf_int16)),
SF_META(proc_int32,offsetof(struct sf_structlevel_procs,fn.sf_int32)),
SF_META(proc_int64,offsetof(struct sf_structlevel_procs,fn.sf_int64)),
SF_META(proc_long,offsetof(struct sf_structlevel_procs,fn.sf_long)),
SF_META(proc_schar,offsetof(struct sf_structlevel_procs,fn.sf_schar)),
SF_META(proc_short,offsetof(struct sf_structlevel_procs,fn.sf_short)),
SF_META(proc_size_t,offsetof(struct sf_structlevel_procs,fn.sf_size_t)),
SF_META(proc_time_t,offsetof(struct sf_structlevel_procs,fn.sf_time_t)),
SF_META(proc_uchar,offsetof(struct sf_structlevel_procs,fn.sf_uchar)),
SF_META(proc_uint16,offsetof(struct sf_structlevel_procs,fn.sf_uint16)),
SF_META(proc_uint32,offsetof(struct sf_structlevel_procs,fn.sf_uint32)),
SF_META(proc_uint64,offsetof(struct sf_structlevel_procs,fn.sf_uint64)),
SF_META(proc_ulong,offsetof(struct sf_structlevel_procs,fn.sf_ulong)),
SF_META(proc_unsigned,offsetof(struct sf_structlevel_procs,fn.sf_unsigned)),
SF_META(proc_ushort,offsetof(struct sf_structlevel_procs,fn.sf_ushort)),
SF_META(proc_xint16,offsetof(struct sf_structlevel_procs,fn.sf_xint16)),
SF_META(proc_xint8,offsetof(struct sf_structlevel_procs,fn.sf_xint8)),
SF_META(proc_char,offsetof(struct sf_structlevel_procs,fn.sf_char)),
SF_META(proc_bitfield,offsetof(struct sf_structlevel_procs,fn.sf_bitfield)),
};
#undef SF_META
_Static_assert(sizeof(((NHFILE*)0)->fd)==4,"sfstruct fd int32");
_Static_assert(sizeof(((NHFILE*)0)->eof)==1,"sfstruct eof boolean8");
size_t probe_context_size(void){return sizeof(NHFILE);}
int probe_layout_count(void){return sizeof teleport_sfstruct_layout/sizeof teleport_sfstruct_layout[0];}
const char *probe_layout_name(int i){return teleport_sfstruct_layout[i].name;}
size_t probe_layout_value(int i){return teleport_sfstruct_layout[i].value;}
#endif
