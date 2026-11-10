#include "hack.h"
#include "dlb.h"
#include <stddef.h>
#include <limits.h>
#define RUMORS_META(name,value) { #name, value }
static const struct { const char *name; size_t value; } rumors_layout[] = {
    RUMORS_META(MD_PAD_BOGONS, MD_PAD_BOGONS),
    RUMORS_META(pointerSize, sizeof(void *)),
    RUMORS_META(longSize, sizeof(long)),
    RUMORS_META(intSize, sizeof(int)),
    RUMORS_META(uintSize, sizeof(unsigned)),
    RUMORS_META(charSize, sizeof(char)),
    RUMORS_META(charSigned, (char)-1 < 0),
    RUMORS_META(booleanSize, sizeof(boolean)),
    RUMORS_META(booleanSigned, (boolean)-1 < 0),
    RUMORS_META(CHAR_BIT, CHAR_BIT),
    RUMORS_META(monsterSize, sizeof(struct monst)),
    RUMORS_META(permonstSize, sizeof(struct permonst)),
    RUMORS_META(objectSize, sizeof(struct obj)),
    RUMORS_META(propSize, sizeof(struct prop)),
    RUMORS_META(nhfileSize, sizeof(NHFILE)),
    RUMORS_META(u_ulevel, offsetof(struct you, ulevel)),
    RUMORS_META(u_ulevel_size, sizeof(((struct you *)0)->ulevel)),
    RUMORS_META(u_uprops, offsetof(struct you, uprops)),
    RUMORS_META(u_uprops_size, sizeof(((struct you *)0)->uprops)),
    RUMORS_META(mon_data, offsetof(struct monst, data)),
    RUMORS_META(mon_data_size, sizeof(((struct monst *)0)->data)),
    RUMORS_META(pm_pmnames, offsetof(struct permonst, pmnames)),
    RUMORS_META(pm_pmnames_size, sizeof(((struct permonst *)0)->pmnames)),
    RUMORS_META(pm_geno, offsetof(struct permonst, geno)),
    RUMORS_META(pm_geno_size, sizeof(((struct permonst *)0)->geno)),
    RUMORS_META(prop_intrinsic, offsetof(struct prop, intrinsic)),
    RUMORS_META(prop_intrinsic_size, sizeof(((struct prop *)0)->intrinsic)),
    RUMORS_META(prop_extrinsic, offsetof(struct prop, extrinsic)),
    RUMORS_META(prop_extrinsic_size, sizeof(((struct prop *)0)->extrinsic)),
    RUMORS_META(prop_blocked, offsetof(struct prop, blocked)),
    RUMORS_META(prop_blocked_size, sizeof(((struct prop *)0)->blocked)),
    RUMORS_META(nhfile_mode, offsetof(NHFILE, mode)),
    RUMORS_META(nhfile_mode_size, sizeof(((NHFILE *)0)->mode)),
    RUMORS_META(inventory, offsetof(__typeof__(gi), invent)),
    RUMORS_META(inventory_size, sizeof gi.invent),
    RUMORS_META(inMklev, offsetof(__typeof__(gi), in_mklev)),
    RUMORS_META(inMklev_size, sizeof gi.in_mklev),
    RUMORS_META(true_rumor_size, offsetof(__typeof__(gt), true_rumor_size)),
    RUMORS_META(true_rumor_size_size, sizeof gt.true_rumor_size),
    RUMORS_META(true_rumor_start, offsetof(__typeof__(gt), true_rumor_start)),
    RUMORS_META(true_rumor_start_size, sizeof gt.true_rumor_start),
    RUMORS_META(true_rumor_end, offsetof(__typeof__(gt), true_rumor_end)),
    RUMORS_META(true_rumor_end_size, sizeof gt.true_rumor_end),
    RUMORS_META(false_rumor_size, offsetof(__typeof__(gf), false_rumor_size)),
    RUMORS_META(false_rumor_size_size, sizeof gf.false_rumor_size),
    RUMORS_META(false_rumor_start, offsetof(__typeof__(gf), false_rumor_start)),
    RUMORS_META(false_rumor_start_size, sizeof gf.false_rumor_start),
    RUMORS_META(false_rumor_end, offsetof(__typeof__(gf), false_rumor_end)),
    RUMORS_META(false_rumor_end_size, sizeof gf.false_rumor_end),
    RUMORS_META(oracle_cnt, offsetof(__typeof__(svo), oracle_cnt)),
    RUMORS_META(oracle_cnt_size, sizeof svo.oracle_cnt),
    RUMORS_META(oracle_loc, offsetof(__typeof__(svo), oracle_loc)),
    RUMORS_META(oracle_loc_size, sizeof svo.oracle_loc),
    RUMORS_META(oracle_flg, offsetof(__typeof__(go), oracle_flg)),
    RUMORS_META(oracle_flg_size, sizeof go.oracle_flg),
    RUMORS_META(multi, offsetof(__typeof__(gm), multi)),
    RUMORS_META(multi_size, sizeof gm.multi),
    RUMORS_META(botl, offsetof(__typeof__(disp), botl)),
    RUMORS_META(botl_size, sizeof disp.botl),
    RUMORS_META(worthSaving, offsetof(__typeof__(program_state), something_worth_saving)),
    RUMORS_META(worthSaving_size, sizeof program_state.something_worth_saving),
    RUMORS_META(debugFuzzer, offsetof(__typeof__(iflags), debug_fuzzer)),
    RUMORS_META(debugFuzzer_size, sizeof iflags.debug_fuzzer),
    RUMORS_META(wizard, offsetof(__typeof__(flags), debug)),
    RUMORS_META(wizard_size, sizeof flags.debug),
    RUMORS_META(ACH_ORCL, ACH_ORCL),
    RUMORS_META(A_WIS, A_WIS),
    RUMORS_META(BLINDED, BLINDED),
    RUMORS_META(BUFSZ, BUFSZ),
    RUMORS_META(BY_COOKIE, BY_COOKIE),
    RUMORS_META(BY_ORACLE, BY_ORACLE),
    RUMORS_META(BY_PAPER, BY_PAPER),
    RUMORS_META(COLNO, COLNO),
    RUMORS_META(COUNTING, COUNTING),
    RUMORS_META(ECMD_OK, ECMD_OK),
    RUMORS_META(ECMD_TIME, ECMD_TIME),
    RUMORS_META(FREEING, FREEING),
    RUMORS_META(G_UNIQ, G_UNIQ),
    RUMORS_META(INT_MAX, INT_MAX),
    RUMORS_META(LOW_PM, LOW_PM),
    RUMORS_META(MALE, MALE),
    RUMORS_META(MD_PAD_RUMORS, MD_PAD_RUMORS),
    RUMORS_META(NHW_TEXT, NHW_TEXT),
    RUMORS_META(NUMMONS, NUMMONS),
    RUMORS_META(NUM_MGENDERS, NUM_MGENDERS),
    RUMORS_META(QBUFSZ, QBUFSZ),
    RUMORS_META(SEEK_CUR, SEEK_CUR),
    RUMORS_META(SEEK_END, SEEK_END),
    RUMORS_META(SEEK_SET, SEEK_SET),
    RUMORS_META(WIN_ERR, WIN_ERR),
    RUMORS_META(WRITING, WRITING),
#ifdef DEBUG
    RUMORS_META(DEBUG, 1),
#else
    RUMORS_META(DEBUG, 0),
#endif
#ifdef DLB
    RUMORS_META(DLB, 1),
#else
    RUMORS_META(DLB, 0),
#endif
#ifdef SFCTOOL
    RUMORS_META(SFCTOOL, 1),
#else
    RUMORS_META(SFCTOOL, 0),
#endif
#ifdef SND_LIB_INTEGRATED
    RUMORS_META(SND_LIB_INTEGRATED, 1),
#else
    RUMORS_META(SND_LIB_INTEGRATED, 0),
#endif
#ifdef NDEBUG
    RUMORS_META(ASSERT_ENABLED, 0),
#else
    RUMORS_META(ASSERT_ENABLED, 1),
#endif
};
#undef RUMORS_META
static const struct { const char *name; const char *value; } rumors_strings[] = {
    { "RUMORFILE", RUMORFILE },
    { "ENGRAVEFILE", ENGRAVEFILE },
    { "EPITAPHFILE", EPITAPHFILE },
    { "BOGUSMONFILE", BOGUSMONFILE },
    { "ORACLEFILE", ORACLEFILE },
};
size_t probe_context_size(void) { return sizeof(NHFILE); }
int probe_layout_count(void) { return sizeof rumors_layout / sizeof rumors_layout[0]; }
const char *probe_layout_name(int index) { return rumors_layout[index].name; }
size_t probe_layout_value(int index) { return rumors_layout[index].value; }
int probe_string_count(void) { return sizeof rumors_strings / sizeof rumors_strings[0]; }
const char *probe_string_name(int index) { return rumors_strings[index].name; }
const char *probe_string_value(int index) { return rumors_strings[index].value; }
