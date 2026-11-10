#include "hack.h"
#include <stddef.h>
struct teleport_version_critical_layout { uchar ucsize; const char *nm; };
struct teleport_version_rt_layout { const char *token, *value; };
#define VERSION_META(name,value) { #name, value }
static const struct { const char *name; size_t value; } version_layout[] = {
    VERSION_META(pointerSize, sizeof(void*)),
    VERSION_META(longSize, sizeof(long)),
    VERSION_META(intSize, sizeof(int)),
    VERSION_META(charSize, sizeof(char)),
    VERSION_META(charSigned, (char)-1 < 0),
    VERSION_META(booleanSize, sizeof(boolean)),
    VERSION_META(booleanSigned, (boolean)-1 < 0),
    VERSION_META(criticalCount, 80),
    VERSION_META(CRITICAL_COUNT, 80),
    VERSION_META(rtOptCount, 3),
    VERSION_META(criticalSize, sizeof(struct teleport_version_critical_layout)),
    VERSION_META(critical_ucsize, offsetof(struct teleport_version_critical_layout,ucsize)),
    VERSION_META(critical_nm, offsetof(struct teleport_version_critical_layout,nm)),
    VERSION_META(rtOptSize, sizeof(struct teleport_version_rt_layout)),
    VERSION_META(rt_token, offsetof(struct teleport_version_rt_layout,token)),
    VERSION_META(rt_value, offsetof(struct teleport_version_rt_layout,value)),
    VERSION_META(versionSize, sizeof(struct version_info)),
    VERSION_META(nhfileSize, sizeof(NHFILE)),
    VERSION_META(version_incarnation, offsetof(struct version_info,incarnation)),
    VERSION_META(version_feature_set, offsetof(struct version_info,feature_set)),
    VERSION_META(version_entity_count, offsetof(struct version_info,entity_count)),
    VERSION_META(nom_version_string, offsetof(struct nomakedefs_s,version_string)),
    VERSION_META(nom_version_string_size, sizeof(((struct nomakedefs_s*)0)->version_string)),
    VERSION_META(nom_version_id, offsetof(struct nomakedefs_s,version_id)),
    VERSION_META(nom_version_id_size, sizeof(((struct nomakedefs_s*)0)->version_id)),
    VERSION_META(nom_git_sha, offsetof(struct nomakedefs_s,git_sha)),
    VERSION_META(nom_git_sha_size, sizeof(((struct nomakedefs_s*)0)->git_sha)),
    VERSION_META(nom_git_branch, offsetof(struct nomakedefs_s,git_branch)),
    VERSION_META(nom_git_branch_size, sizeof(((struct nomakedefs_s*)0)->git_branch)),
    VERSION_META(nom_git_prefix, offsetof(struct nomakedefs_s,git_prefix)),
    VERSION_META(nom_git_prefix_size, sizeof(((struct nomakedefs_s*)0)->git_prefix)),
    VERSION_META(nom_copyright_banner_c, offsetof(struct nomakedefs_s,copyright_banner_c)),
    VERSION_META(nom_copyright_banner_c_size, sizeof(((struct nomakedefs_s*)0)->copyright_banner_c)),
    VERSION_META(nom_version_number, offsetof(struct nomakedefs_s,version_number)),
    VERSION_META(nom_version_number_size, sizeof(((struct nomakedefs_s*)0)->version_number)),
    VERSION_META(nom_version_features, offsetof(struct nomakedefs_s,version_features)),
    VERSION_META(nom_version_features_size, sizeof(((struct nomakedefs_s*)0)->version_features)),
    VERSION_META(nom_ignored_features, offsetof(struct nomakedefs_s,ignored_features)),
    VERSION_META(nom_ignored_features_size, sizeof(((struct nomakedefs_s*)0)->ignored_features)),
    VERSION_META(nom_version_sanity1, offsetof(struct nomakedefs_s,version_sanity1)),
    VERSION_META(nom_version_sanity1_size, sizeof(((struct nomakedefs_s*)0)->version_sanity1)),
    VERSION_META(versinfo, offsetof(__typeof__(flags),versinfo)),
    VERSION_META(versinfo_size, sizeof flags.versinfo),
    VERSION_META(menu_requested, offsetof(__typeof__(iflags),menu_requested)),
    VERSION_META(menu_requested_size, sizeof iflags.menu_requested),
    VERSION_META(hname, offsetof(__typeof__(gh),hname)),
    VERSION_META(hname_size, sizeof gh.hname),
    VERSION_META(lua_ver, offsetof(__typeof__(gl),lua_ver)),
    VERSION_META(lua_ver_size, sizeof gl.lua_ver),
    VERSION_META(lua_copyright, offsetof(__typeof__(gl),lua_copyright)),
    VERSION_META(lua_copyright_size, sizeof gl.lua_copyright),
    VERSION_META(converted, offsetof(__typeof__(gc),converted_savefile_loaded)),
    VERSION_META(converted_size, sizeof gc.converted_savefile_loaded),
    VERSION_META(nhf_fd, offsetof(NHFILE,fd)),
    VERSION_META(nhf_fd_size, sizeof(((NHFILE*)0)->fd)),
    VERSION_META(nhf_mode, offsetof(NHFILE,mode)),
    VERSION_META(nhf_mode_size, sizeof(((NHFILE*)0)->mode)),
    VERSION_META(nhf_fnidx, offsetof(NHFILE,fnidx)),
    VERSION_META(nhf_fnidx_size, sizeof(((NHFILE*)0)->fnidx)),
    VERSION_META(nhf_structlevel, offsetof(NHFILE,structlevel)),
    VERSION_META(nhf_structlevel_size, sizeof(((NHFILE*)0)->structlevel)),
    VERSION_META(nhf_fieldlevel, offsetof(NHFILE,fieldlevel)),
    VERSION_META(nhf_fieldlevel_size, sizeof(((NHFILE*)0)->fieldlevel)),
    VERSION_META(sizeof_aligntyp, sizeof(aligntyp)),
    VERSION_META(sizeof_anything, sizeof(anything)),
    VERSION_META(sizeof_boolean, sizeof(boolean)),
    VERSION_META(sizeof_coordxy, sizeof(coordxy)),
    VERSION_META(sizeof_genericptr_t, sizeof(genericptr_t)),
    VERSION_META(sizeof_int, sizeof(int)),
    VERSION_META(sizeof_int16, sizeof(int16)),
    VERSION_META(sizeof_int32, sizeof(int32)),
    VERSION_META(sizeof_int64, sizeof(int64)),
    VERSION_META(sizeof_long, sizeof(long)),
    VERSION_META(sizeof_long_long, sizeof(long long)),
    VERSION_META(sizeof_schar, sizeof(schar)),
    VERSION_META(sizeof_short, sizeof(short)),
    VERSION_META(sizeof_size_t, sizeof(size_t)),
    VERSION_META(sizeof_struct_arti_info, sizeof(struct arti_info)),
    VERSION_META(sizeof_struct_branch, sizeof(struct branch)),
    VERSION_META(sizeof_struct_bubble, sizeof(struct bubble)),
    VERSION_META(sizeof_struct_cemetery, sizeof(struct cemetery)),
    VERSION_META(sizeof_struct_context_info, sizeof(struct context_info)),
    VERSION_META(sizeof_struct_d_level, sizeof(struct d_level)),
    VERSION_META(sizeof_struct_damage, sizeof(struct damage)),
    VERSION_META(sizeof_struct_dest_area, sizeof(struct dest_area)),
    VERSION_META(sizeof_struct_dgn_topology, sizeof(struct dgn_topology)),
    VERSION_META(sizeof_struct_dungeon, sizeof(struct dungeon)),
    VERSION_META(sizeof_struct_ebones, sizeof(struct ebones)),
    VERSION_META(sizeof_struct_edog, sizeof(struct edog)),
    VERSION_META(sizeof_struct_egd, sizeof(struct egd)),
    VERSION_META(sizeof_struct_emin, sizeof(struct emin)),
    VERSION_META(sizeof_struct_engr, sizeof(struct engr)),
    VERSION_META(sizeof_struct_epri, sizeof(struct epri)),
    VERSION_META(sizeof_struct_eshk, sizeof(struct eshk)),
    VERSION_META(sizeof_struct_fe, sizeof(struct fe)),
    VERSION_META(sizeof_struct_flag, sizeof(struct flag)),
    VERSION_META(sizeof_struct_fruit, sizeof(struct fruit)),
    VERSION_META(sizeof_struct_gamelog_line, sizeof(struct gamelog_line)),
    VERSION_META(sizeof_struct_kinfo, sizeof(struct kinfo)),
    VERSION_META(sizeof_struct_levelflags, sizeof(struct levelflags)),
    VERSION_META(sizeof_struct_linfo, sizeof(struct linfo)),
    VERSION_META(sizeof_struct_ls_t, sizeof(struct ls_t)),
    VERSION_META(sizeof_struct_mapseen_feat, sizeof(struct mapseen_feat)),
    VERSION_META(sizeof_struct_mapseen_flags, sizeof(struct mapseen_flags)),
    VERSION_META(sizeof_struct_mapseen_rooms, sizeof(struct mapseen_rooms)),
    VERSION_META(sizeof_struct_mextra, sizeof(struct mextra)),
    VERSION_META(sizeof_struct_mkroom, sizeof(struct mkroom)),
    VERSION_META(sizeof_struct_monst, sizeof(struct monst)),
    VERSION_META(sizeof_struct_mvitals, sizeof(struct mvitals)),
    VERSION_META(sizeof_struct_nhcoord, sizeof(struct nhcoord)),
    VERSION_META(sizeof_struct_nhrect, sizeof(struct nhrect)),
    VERSION_META(sizeof_struct_obj, sizeof(struct obj)),
    VERSION_META(sizeof_struct_objclass, sizeof(struct objclass)),
    VERSION_META(sizeof_struct_oextra, sizeof(struct oextra)),
    VERSION_META(sizeof_struct_q_score, sizeof(struct q_score)),
    VERSION_META(sizeof_struct_rm, sizeof(struct rm)),
    VERSION_META(sizeof_struct_s_level, sizeof(struct s_level)),
    VERSION_META(sizeof_struct_spell, sizeof(struct spell)),
    VERSION_META(sizeof_struct_stairway, sizeof(struct stairway)),
    VERSION_META(sizeof_struct_trap, sizeof(struct trap)),
    VERSION_META(sizeof_struct_version_info, sizeof(struct version_info)),
    VERSION_META(sizeof_uchar, sizeof(uchar)),
    VERSION_META(sizeof_uint16, sizeof(uint16)),
    VERSION_META(sizeof_uint32, sizeof(uint32)),
    VERSION_META(sizeof_uint64, sizeof(uint64)),
    VERSION_META(sizeof_ulong, sizeof(ulong)),
    VERSION_META(sizeof_unsigned, sizeof(unsigned)),
    VERSION_META(sizeof_ushort, sizeof(ushort)),
    VERSION_META(sizeof_xint16, sizeof(xint16)),
    VERSION_META(sizeof_xint8, sizeof(xint8)),
    VERSION_META(you_HI, (sizeof(struct you) & 0xff00) >> 8),
    VERSION_META(you_LO, sizeof(struct you) & 0xff),
    VERSION_META(BUFSZ, BUFSZ),
    VERSION_META(COLNO, COLNO),
    VERSION_META(ECMD_OK, ECMD_OK),
    VERSION_META(NHW_TEXT, NHW_TEXT),
    VERSION_META(PATCHLEVEL, PATCHLEVEL),
    VERSION_META(SFCTOOL_BIT, SFCTOOL_BIT),
    VERSION_META(SF_CRITICAL_BYTE_COUNT_MISMATCH, SF_CRITICAL_BYTE_COUNT_MISMATCH),
    VERSION_META(SF_DM_I32LP64_ON_IL32LLP64, SF_DM_I32LP64_ON_IL32LLP64),
    VERSION_META(SF_DM_I32LP64_ON_ILP32LL64, SF_DM_I32LP64_ON_ILP32LL64),
    VERSION_META(SF_DM_IL32LLP64_ON_I32LP64, SF_DM_IL32LLP64_ON_I32LP64),
    VERSION_META(SF_DM_IL32LLP64_ON_ILP32LL64, SF_DM_IL32LLP64_ON_ILP32LL64),
    VERSION_META(SF_DM_ILP32LL64_ON_I32LP64, SF_DM_ILP32LL64_ON_I32LP64),
    VERSION_META(SF_DM_ILP32LL64_ON_IL32LLP64, SF_DM_ILP32LL64_ON_IL32LLP64),
    VERSION_META(SF_DM_MISMATCH, SF_DM_MISMATCH),
    VERSION_META(SF_OUTDATED, SF_OUTDATED),
    VERSION_META(SF_UPTODATE, SF_UPTODATE),
    VERSION_META(UTD_CHECKFIELDCOUNTS, UTD_CHECKFIELDCOUNTS),
    VERSION_META(UTD_CHECKSIZES, UTD_CHECKSIZES),
    VERSION_META(UTD_QUIETLY, UTD_QUIETLY),
    VERSION_META(UTD_SKIP_SANITY1, UTD_SKIP_SANITY1),
    VERSION_META(UTD_WITHOUT_WAITSYNCH_PERFILE, UTD_WITHOUT_WAITSYNCH_PERFILE),
    VERSION_META(VERSION_MAJOR, VERSION_MAJOR),
    VERSION_META(VERSION_MINOR, VERSION_MINOR),
    VERSION_META(VI_BRANCH, VI_BRANCH),
    VERSION_META(VI_NAME, VI_NAME),
    VERSION_META(VI_NUMBER, VI_NUMBER),
    VERSION_META(WIN_ERR, WIN_ERR),
    VERSION_META(WRITING, WRITING),
    VERSION_META(exportascii, exportascii),
#ifdef SFCTOOL
    VERSION_META(config_SFCTOOL, 1),
#else
    VERSION_META(config_SFCTOOL, 0),
#endif
#ifdef MINIMAL_FOR_RECOVER
    VERSION_META(config_MINIMAL_FOR_RECOVER, 1),
#else
    VERSION_META(config_MINIMAL_FOR_RECOVER, 0),
#endif
#ifdef SF_INCLUDE_SUBSTRUCTS
    VERSION_META(config_SF_INCLUDE_SUBSTRUCTS, 1),
#else
    VERSION_META(config_SF_INCLUDE_SUBSTRUCTS, 0),
#endif
#ifdef MICRO
    VERSION_META(config_MICRO, 1),
#else
    VERSION_META(config_MICRO, 0),
#endif
#ifdef RUNTIME_PORT_ID
    VERSION_META(config_RUNTIME_PORT_ID, 1),
#else
    VERSION_META(config_RUNTIME_PORT_ID, 0),
#endif
#ifdef EXTRA_SANITY_CHECKS
    VERSION_META(config_EXTRA_SANITY_CHECKS, 1),
#else
    VERSION_META(config_EXTRA_SANITY_CHECKS, 0),
#endif
#ifdef VERS_GAME_NAME
    VERSION_META(config_VERS_GAME_NAME, 1),
#else
    VERSION_META(config_VERS_GAME_NAME, 0),
#endif
#ifdef RUNTIME_PASTEBUF_SUPPORT
    VERSION_META(config_RUNTIME_PASTEBUF_SUPPORT, 1),
#else
    VERSION_META(config_RUNTIME_PASTEBUF_SUPPORT, 0),
#endif
#ifdef DLB
    VERSION_META(config_DLB, 1),
#else
    VERSION_META(config_DLB, 0),
#endif
#ifdef LIBNH
    VERSION_META(config_LIBNH, 1),
#else
    VERSION_META(config_LIBNH, 0),
#endif
#ifdef VERSION_COMPATIBILITY
    VERSION_META(config_VERSION_COMPATIBILITY, 1),
#else
    VERSION_META(config_VERSION_COMPATIBILITY, 0),
#endif
#ifdef AMIGA
    VERSION_META(config_AMIGA, 1),
#else
    VERSION_META(config_AMIGA, 0),
#endif
    VERSION_META(NH_DEVEL_STATUS, NH_DEVEL_STATUS),
    VERSION_META(NH_STATUS_RELEASED, NH_STATUS_RELEASED),
};
#undef VERSION_META
size_t probe_context_size(void) { return sizeof(struct version_info); }
int probe_layout_count(void) { return sizeof version_layout / sizeof version_layout[0]; }
const char *probe_layout_name(int index) { return version_layout[index].name; }
size_t probe_layout_value(int index) { return version_layout[index].value; }
static const struct { const char *name, *value; } version_strings[] = {
    { "COPYRIGHT_BANNER_A", COPYRIGHT_BANNER_A },
    { "COPYRIGHT_BANNER_B", COPYRIGHT_BANNER_B },
    { "COPYRIGHT_BANNER_D", COPYRIGHT_BANNER_D },
    { "OPTIONS_USED", OPTIONS_USED },
};
int probe_string_count(void) { return sizeof version_strings / sizeof version_strings[0]; }
const char *probe_string_name(int index) { return version_strings[index].name; }
const char *probe_string_value(int index) { return version_strings[index].value; }
