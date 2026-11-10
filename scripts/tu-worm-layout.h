#include "hack.h"
#include <stddef.h>
struct teleport_worm_segment { struct teleport_worm_segment *nseg; coordxy wx, wy; };
#ifdef TELEPORT_REFERENCE_TU
_Static_assert(sizeof(struct wseg)==sizeof(struct teleport_worm_segment), "worm segment size must match original");
_Static_assert(offsetof(struct wseg,nseg)==offsetof(struct teleport_worm_segment,nseg), "worm segment nseg must match original");
_Static_assert(offsetof(struct wseg,wx)==offsetof(struct teleport_worm_segment,wx), "worm segment wx must match original");
_Static_assert(offsetof(struct wseg,wy)==offsetof(struct teleport_worm_segment,wy), "worm segment wy must match original");
#endif
#define WORM_META(name,value) { #name, value }
static const struct { const char *name; size_t value; } worm_layout[] = {
    WORM_META(pointerSize, sizeof(void*)),
    WORM_META(longSize, sizeof(long)),
    WORM_META(intSize, sizeof(int)),
    WORM_META(booleanSize, sizeof(boolean)),
    WORM_META(coordxySize, sizeof(coordxy)),
    WORM_META(segmentSize, sizeof(struct teleport_worm_segment)),
    WORM_META(monsterSize, sizeof(struct monst)),
    WORM_META(permonstSize, sizeof(struct permonst)),
    WORM_META(propSize, sizeof(struct prop)),
    WORM_META(nhfileSize, sizeof(NHFILE)),
    WORM_META(booleanSigned, (boolean)-1<0),
    WORM_META(coordxySigned, (coordxy)-1<0),
    WORM_META(seg_nseg, offsetof(struct teleport_worm_segment,nseg)),
    WORM_META(seg_nseg_size, sizeof(((struct teleport_worm_segment*)0)->nseg)),
    WORM_META(seg_wx, offsetof(struct teleport_worm_segment,wx)),
    WORM_META(seg_wx_size, sizeof(((struct teleport_worm_segment*)0)->wx)),
    WORM_META(seg_wy, offsetof(struct teleport_worm_segment,wy)),
    WORM_META(seg_wy_size, sizeof(((struct teleport_worm_segment*)0)->wy)),
    WORM_META(mon_data, offsetof(struct monst,data)),
    WORM_META(mon_data_size, sizeof(((struct monst*)0)->data)),
    WORM_META(mon_mx, offsetof(struct monst,mx)),
    WORM_META(mon_mx_size, sizeof(((struct monst*)0)->mx)),
    WORM_META(mon_my, offsetof(struct monst,my)),
    WORM_META(mon_my_size, sizeof(((struct monst*)0)->my)),
    WORM_META(mon_mhp, offsetof(struct monst,mhp)),
    WORM_META(mon_mhp_size, sizeof(((struct monst*)0)->mhp)),
    WORM_META(mon_mhpmax, offsetof(struct monst,mhpmax)),
    WORM_META(mon_mhpmax_size, sizeof(((struct monst*)0)->mhpmax)),
    WORM_META(mon_m_lev, offsetof(struct monst,m_lev)),
    WORM_META(mon_m_lev_size, sizeof(((struct monst*)0)->m_lev)),
    WORM_META(mon_mtame, offsetof(struct monst,mtame)),
    WORM_META(mon_mtame_size, sizeof(((struct monst*)0)->mtame)),
    WORM_META(mon_mextra, offsetof(struct monst,mextra)),
    WORM_META(mon_mextra_size, sizeof(((struct monst*)0)->mextra)),
    WORM_META(mextra_mcorpsenm, offsetof(struct mextra,mcorpsenm)),
    WORM_META(mextra_mcorpsenm_size, sizeof(((struct mextra*)0)->mcorpsenm)),
    WORM_META(u_ux, offsetof(struct you,ux)),
    WORM_META(u_ux_size, sizeof(((struct you*)0)->ux)),
    WORM_META(u_uy, offsetof(struct you,uy)),
    WORM_META(u_uy_size, sizeof(((struct you*)0)->uy)),
    WORM_META(u_uprops, offsetof(struct you,uprops)),
    WORM_META(u_uprops_size, sizeof(((struct you*)0)->uprops)),
    WORM_META(prop_intrinsic, offsetof(struct prop,intrinsic)),
    WORM_META(prop_intrinsic_size, sizeof(((struct prop*)0)->intrinsic)),
    WORM_META(prop_extrinsic, offsetof(struct prop,extrinsic)),
    WORM_META(prop_extrinsic_size, sizeof(((struct prop*)0)->extrinsic)),
    WORM_META(prop_blocked, offsetof(struct prop,blocked)),
    WORM_META(prop_blocked_size, sizeof(((struct prop*)0)->blocked)),
    WORM_META(nhf_mode, offsetof(NHFILE,mode)),
    WORM_META(nhf_mode_size, sizeof(((NHFILE*)0)->mode)),
    WORM_META(nhf_structlevel, offsetof(NHFILE,structlevel)),
    WORM_META(nhf_structlevel_size, sizeof(((NHFILE*)0)->structlevel)),
    WORM_META(nhf_fnidx, offsetof(NHFILE,fnidx)),
    WORM_META(nhf_fnidx_size, sizeof(((NHFILE*)0)->fnidx)),
    WORM_META(floorMonsters, offsetof(__typeof__(svl),level.monsters)),
    WORM_META(floorMonsters_size, sizeof svl.level.monsters),
    WORM_META(moves, offsetof(__typeof__(svm),moves)),
    WORM_META(moves_size, sizeof svm.moves),
    WORM_META(monMoving, offsetof(__typeof__(svc),context.mon_moving)),
    WORM_META(monMoving_size, sizeof svc.context.mon_moving),
    WORM_META(vizArray, offsetof(__typeof__(gv),viz_array)),
    WORM_META(vizArray_size, sizeof gv.viz_array),
    WORM_META(COLNO, COLNO),
    WORM_META(COUNTING, COUNTING),
    WORM_META(FEMALE, FEMALE),
    WORM_META(FREEING, FREEING),
    WORM_META(GLYPH_DETECT_FEM_OFF, GLYPH_DETECT_FEM_OFF),
    WORM_META(GLYPH_DETECT_MALE_OFF, GLYPH_DETECT_MALE_OFF),
    WORM_META(GLYPH_MON_FEM_OFF, GLYPH_MON_FEM_OFF),
    WORM_META(GLYPH_MON_MALE_OFF, GLYPH_MON_MALE_OFF),
    WORM_META(GLYPH_PET_FEM_OFF, GLYPH_PET_FEM_OFF),
    WORM_META(GLYPH_PET_MALE_OFF, GLYPH_PET_MALE_OFF),
    WORM_META(HALLUC, HALLUC),
    WORM_META(HALLUC_RES, HALLUC_RES),
    WORM_META(IN_SIGHT, IN_SIGHT),
    WORM_META(MALE, MALE),
    WORM_META(MAX_NUM_WORMS, MAX_NUM_WORMS),
    WORM_META(MHPMAX, MHPMAX),
    WORM_META(NON_PM, NON_PM),
    WORM_META(NORMAL_SPEED, NORMAL_SPEED),
    WORM_META(NUMMONS, NUMMONS),
    WORM_META(PM_LONG_WORM, PM_LONG_WORM),
    WORM_META(PM_LONG_WORM_TAIL, PM_LONG_WORM_TAIL),
    WORM_META(ROWNO, ROWNO),
    WORM_META(WRITING, WRITING),
    WORM_META(PM_HUMAN, PM_HUMAN),
    WORM_META(READING, READING),
#ifdef SFCTOOL
    WORM_META(config_SFCTOOL,1),
#else
    WORM_META(config_SFCTOOL,0),
#endif
#ifdef EXTRA_SANITY_CHECKS
    WORM_META(config_EXTRA_SANITY_CHECKS,1),
#else
    WORM_META(config_EXTRA_SANITY_CHECKS,0),
#endif
};
size_t probe_context_size(void) { return sizeof(struct teleport_worm_segment); }
int probe_layout_count(void) { return (int)(sizeof worm_layout / sizeof worm_layout[0]); }
const char *probe_layout_name(int i) { return worm_layout[i].name; }
size_t probe_layout_value(int i) { return worm_layout[i].value; }
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(int)==4 && sizeof(coordxy)==2 && (coordxy)-1<0 && sizeof(boolean)==1 && (boolean)-1<0, "review worm memory64 ABI");
_Static_assert(sizeof(((struct teleport_worm_segment*)0)->wx)==2 && (((__typeof__(((struct teleport_worm_segment*)0)->wx))-1<0)==1), "review worm scalar ((struct teleport_worm_segment*)0)->wx");
_Static_assert(sizeof(((struct teleport_worm_segment*)0)->wy)==2 && (((__typeof__(((struct teleport_worm_segment*)0)->wy))-1<0)==1), "review worm scalar ((struct teleport_worm_segment*)0)->wy");
_Static_assert(sizeof(((struct monst*)0)->mx)==2 && (((__typeof__(((struct monst*)0)->mx))-1<0)==1), "review worm scalar ((struct monst*)0)->mx");
_Static_assert(sizeof(((struct monst*)0)->my)==2 && (((__typeof__(((struct monst*)0)->my))-1<0)==1), "review worm scalar ((struct monst*)0)->my");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4 && (((__typeof__(((struct monst*)0)->mhp))-1<0)==1), "review worm scalar ((struct monst*)0)->mhp");
_Static_assert(sizeof(((struct monst*)0)->mhpmax)==4 && (((__typeof__(((struct monst*)0)->mhpmax))-1<0)==1), "review worm scalar ((struct monst*)0)->mhpmax");
_Static_assert(sizeof(((struct monst*)0)->m_lev)==1 && (((__typeof__(((struct monst*)0)->m_lev))-1<0)==0), "review worm scalar ((struct monst*)0)->m_lev");
_Static_assert(sizeof(((struct monst*)0)->mtame)==1 && (((__typeof__(((struct monst*)0)->mtame))-1<0)==1), "review worm scalar ((struct monst*)0)->mtame");
_Static_assert(sizeof(((struct mextra*)0)->mcorpsenm)==4 && (((__typeof__(((struct mextra*)0)->mcorpsenm))-1<0)==1), "review worm scalar ((struct mextra*)0)->mcorpsenm");
_Static_assert(sizeof(u.ux)==2 && (((__typeof__(u.ux))-1<0)==1), "review worm scalar u.ux");
_Static_assert(sizeof(u.uy)==2 && (((__typeof__(u.uy))-1<0)==1), "review worm scalar u.uy");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8 && (((__typeof__(((struct prop*)0)->intrinsic))-1<0)==1), "review worm scalar ((struct prop*)0)->intrinsic");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8 && (((__typeof__(((struct prop*)0)->extrinsic))-1<0)==1), "review worm scalar ((struct prop*)0)->extrinsic");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8 && (((__typeof__(((struct prop*)0)->blocked))-1<0)==1), "review worm scalar ((struct prop*)0)->blocked");
_Static_assert(sizeof(((NHFILE*)0)->mode)==4 && (((__typeof__(((NHFILE*)0)->mode))-1<0)==1), "review worm scalar ((NHFILE*)0)->mode");
_Static_assert(sizeof(((NHFILE*)0)->structlevel)==1 && (((__typeof__(((NHFILE*)0)->structlevel))-1<0)==1), "review worm scalar ((NHFILE*)0)->structlevel");
_Static_assert(sizeof(((NHFILE*)0)->fnidx)==4 && (((__typeof__(((NHFILE*)0)->fnidx))-1<0)==1), "review worm scalar ((NHFILE*)0)->fnidx");
_Static_assert(sizeof(svm.moves)==8 && (((__typeof__(svm.moves))-1<0)==1), "review worm scalar svm.moves");
_Static_assert(sizeof(svc.context.mon_moving)==1 && (((__typeof__(svc.context.mon_moving))-1<0)==1), "review worm scalar svc.context.mon_moving");
