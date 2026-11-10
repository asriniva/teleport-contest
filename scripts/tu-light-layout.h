#include "hack.h"
#include <stddef.h>
extern const coordxy circle_data[], circle_start[];
#define LIGHT_META(name,value) { #name, value }
static const struct { const char *name; size_t value; } light_layout[] = {
    LIGHT_META(pointerSize, sizeof(void*)),
    LIGHT_META(longSize, sizeof(long)),
    LIGHT_META(intSize, sizeof(int)),
    LIGHT_META(charSize, sizeof(char)),
    LIGHT_META(charSigned, (char)-1 < 0),
    LIGHT_META(booleanSize, sizeof(boolean)),
    LIGHT_META(booleanSigned, (boolean)-1 < 0),
    LIGHT_META(coordxySize, sizeof(coordxy)),
    LIGHT_META(coordxySigned, (coordxy)-1 < 0),
    LIGHT_META(shortSize, sizeof(short)),
    LIGHT_META(shortSigned, (short)-1 < 0),
    LIGHT_META(lightSourceSize, sizeof(light_source)),
    LIGHT_META(anythingSize, sizeof(anything)),
    LIGHT_META(monsterSize, sizeof(struct monst)),
    LIGHT_META(objectSize, sizeof(struct obj)),
    LIGHT_META(coordSize, sizeof(coord)),
    LIGHT_META(seenSize, sizeof(seenV)),
    LIGHT_META(seenSigned, (seenV)-1 < 0),
    LIGHT_META(circleElementSize, sizeof(circle_data[0])),
    LIGHT_META(nhfileSize, sizeof(NHFILE)),
    LIGHT_META(terrainSize, sizeof(struct rm)),
    LIGHT_META(ls_next, offsetof(light_source,next)),
    LIGHT_META(ls_next_size, sizeof(((light_source*)0)->next)),
    LIGHT_META(ls_x, offsetof(light_source,x)),
    LIGHT_META(ls_x_size, sizeof(((light_source*)0)->x)),
    LIGHT_META(ls_y, offsetof(light_source,y)),
    LIGHT_META(ls_y_size, sizeof(((light_source*)0)->y)),
    LIGHT_META(ls_range, offsetof(light_source,range)),
    LIGHT_META(ls_range_size, sizeof(((light_source*)0)->range)),
    LIGHT_META(ls_flags, offsetof(light_source,flags)),
    LIGHT_META(ls_flags_size, sizeof(((light_source*)0)->flags)),
    LIGHT_META(ls_type, offsetof(light_source,type)),
    LIGHT_META(ls_type_size, sizeof(((light_source*)0)->type)),
    LIGHT_META(ls_id, offsetof(light_source,id)),
    LIGHT_META(ls_id_size, sizeof(((light_source*)0)->id)),
    LIGHT_META(obj_o_id, offsetof(struct obj,o_id)),
    LIGHT_META(obj_o_id_size, sizeof(((struct obj*)0)->o_id)),
    LIGHT_META(obj_otyp, offsetof(struct obj,otyp)),
    LIGHT_META(obj_otyp_size, sizeof(((struct obj*)0)->otyp)),
    LIGHT_META(obj_spe, offsetof(struct obj,spe)),
    LIGHT_META(obj_spe_size, sizeof(((struct obj*)0)->spe)),
    LIGHT_META(obj_where, offsetof(struct obj,where)),
    LIGHT_META(obj_where_size, sizeof(((struct obj*)0)->where)),
    LIGHT_META(obj_quan, offsetof(struct obj,quan)),
    LIGHT_META(obj_quan_size, sizeof(((struct obj*)0)->quan)),
    LIGHT_META(mon_nmon, offsetof(struct monst,nmon)),
    LIGHT_META(mon_nmon_size, sizeof(((struct monst*)0)->nmon)),
    LIGHT_META(mon_m_id, offsetof(struct monst,m_id)),
    LIGHT_META(mon_m_id_size, sizeof(((struct monst*)0)->m_id)),
    LIGHT_META(mon_mx, offsetof(struct monst,mx)),
    LIGHT_META(mon_mx_size, sizeof(((struct monst*)0)->mx)),
    LIGHT_META(mon_my, offsetof(struct monst,my)),
    LIGHT_META(mon_my_size, sizeof(((struct monst*)0)->my)),
    LIGHT_META(mon_mhp, offsetof(struct monst,mhp)),
    LIGHT_META(mon_mhp_size, sizeof(((struct monst*)0)->mhp)),
    LIGHT_META(coord_x, offsetof(coord,x)),
    LIGHT_META(coord_x_size, sizeof(((coord*)0)->x)),
    LIGHT_META(coord_y, offsetof(coord,y)),
    LIGHT_META(coord_y_size, sizeof(((coord*)0)->y)),
    LIGHT_META(nhf_mode, offsetof(NHFILE,mode)),
    LIGHT_META(nhf_mode_size, sizeof(((NHFILE*)0)->mode)),
    LIGHT_META(any_a_obj, offsetof(anything,a_obj)),
    LIGHT_META(any_a_obj_size, sizeof(((anything*)0)->a_obj)),
    LIGHT_META(any_a_monst, offsetof(anything,a_monst)),
    LIGHT_META(any_a_monst_size, sizeof(((anything*)0)->a_monst)),
    LIGHT_META(any_a_void, offsetof(anything,a_void)),
    LIGHT_META(any_a_void_size, sizeof(((anything*)0)->a_void)),
    LIGHT_META(any_a_uint, offsetof(anything,a_uint)),
    LIGHT_META(any_a_uint_size, sizeof(((anything*)0)->a_uint)),
    LIGHT_META(lightBase, offsetof(__typeof__(gl),light_base)),
    LIGHT_META(lightBase_size, sizeof gl.light_base),
    LIGHT_META(visionRecalc, offsetof(__typeof__(gv),vision_full_recalc)),
    LIGHT_META(visionRecalc_size, sizeof gv.vision_full_recalc),
    LIGHT_META(zeroany, offsetof(__typeof__(cg),zeroany)),
    LIGHT_META(zeroany_size, sizeof cg.zeroany),
    LIGHT_META(youmonst, offsetof(__typeof__(gy),youmonst)),
    LIGHT_META(youmonst_size, sizeof gy.youmonst),
    LIGHT_META(fmon, offsetof(__typeof__(svl),level.monlist)),
    LIGHT_META(fmon_size, sizeof svl.level.monlist),
    LIGHT_META(migratingMons, offsetof(__typeof__(gm),migrating_mons)),
    LIGHT_META(migratingMons_size, sizeof gm.migrating_mons),
    LIGHT_META(mydogs, offsetof(__typeof__(gm),mydogs)),
    LIGHT_META(mydogs_size, sizeof gm.mydogs),
    LIGHT_META(bhitpos, offsetof(__typeof__(gb),bhitpos)),
    LIGHT_META(bhitpos_size, sizeof gb.bhitpos),
    LIGHT_META(terrain, offsetof(__typeof__(svl),level.locations)),
    LIGHT_META(terrain_size, sizeof svl.level.locations),
    LIGHT_META(u_ux, offsetof(struct you,ux)),
    LIGHT_META(u_ux_size, sizeof(((struct you*)0)->ux)),
    LIGHT_META(u_uy, offsetof(struct you,uy)),
    LIGHT_META(u_uy_size, sizeof(((struct you*)0)->uy)),
    LIGHT_META(OBJ_FLOOR, OBJ_FLOOR),
    LIGHT_META(OBJ_BURIED, OBJ_BURIED),
    LIGHT_META(OBJ_INVENT, OBJ_INVENT),
    LIGHT_META(PM_HUMAN, PM_HUMAN),
    LIGHT_META(BRASS_LANTERN, BRASS_LANTERN),
    LIGHT_META(BUFSZ, BUFSZ),
    LIGHT_META(CANDELABRUM_OF_INVOCATION, CANDELABRUM_OF_INVOCATION),
    LIGHT_META(COLNO, COLNO),
    LIGHT_META(COULD_SEE, COULD_SEE),
    LIGHT_META(COUNTING, COUNTING),
    LIGHT_META(ECMD_OK, ECMD_OK),
    LIGHT_META(FM_EVERYWHERE, FM_EVERYWHERE),
    LIGHT_META(FM_FMON, FM_FMON),
    LIGHT_META(FM_MIGRATE, FM_MIGRATE),
    LIGHT_META(FM_MYDOGS, FM_MYDOGS),
    LIGHT_META(FM_YOU, FM_YOU),
    LIGHT_META(FREEING, FREEING),
    LIGHT_META(GOLD_DRAGON_SCALE_MAIL, GOLD_DRAGON_SCALE_MAIL),
    LIGHT_META(LS_MONSTER, LS_MONSTER),
    LIGHT_META(LS_NONE, LS_NONE),
    LIGHT_META(LS_OBJECT, LS_OBJECT),
    LIGHT_META(MAGIC_LAMP, MAGIC_LAMP),
    LIGHT_META(MAX_RADIUS, MAX_RADIUS),
    LIGHT_META(NHW_MENU, NHW_MENU),
    LIGHT_META(OBJ_FREE, OBJ_FREE),
    LIGHT_META(OIL_LAMP, OIL_LAMP),
    LIGHT_META(POT_OIL, POT_OIL),
    LIGHT_META(RANGE_GLOBAL, RANGE_GLOBAL),
    LIGHT_META(RANGE_LEVEL, RANGE_LEVEL),
    LIGHT_META(ROWNO, ROWNO),
    LIGHT_META(TALLOW_CANDLE, TALLOW_CANDLE),
    LIGHT_META(TEMP_LIT, TEMP_LIT),
    LIGHT_META(WAX_CANDLE, WAX_CANDLE),
    LIGHT_META(WIN_ERR, WIN_ERR),
    LIGHT_META(WRITING, WRITING),
#ifdef SFCTOOL
    LIGHT_META(config_SFCTOOL, 1),
#else
    LIGHT_META(config_SFCTOOL, 0),
#endif
#ifdef NDEBUG
    LIGHT_META(config_NDEBUG, 1),
#else
    LIGHT_META(config_NDEBUG, 0),
#endif
};
#undef LIGHT_META
size_t probe_context_size(void) { return sizeof(light_source); }
int probe_layout_count(void) { return sizeof light_layout / sizeof light_layout[0]; }
const char *probe_layout_name(int index) { return light_layout[index].name; }
size_t probe_layout_value(int index) { return light_layout[index].value; }

/* The adapter intentionally supports this configured native ABI. */
_Static_assert((sizeof(void*)) == 8, "light ABI pointerSize");
_Static_assert((sizeof(long)) == 8, "light ABI longSize");
_Static_assert((sizeof(int)) == 4, "light ABI intSize");
_Static_assert((sizeof(char)) == 1, "light ABI charSize");
_Static_assert(((char)-1 < 0) == 1, "light ABI charSigned");
_Static_assert((sizeof(boolean)) == 1, "light ABI booleanSize");
_Static_assert(((boolean)-1 < 0) == 1, "light ABI booleanSigned");
_Static_assert((sizeof(coordxy)) == 2, "light ABI coordxySize");
_Static_assert(((coordxy)-1 < 0) == 1, "light ABI coordxySigned");
_Static_assert((sizeof(short)) == 2, "light ABI shortSize");
_Static_assert(((short)-1 < 0) == 1, "light ABI shortSigned");
_Static_assert((sizeof(anything)) == 8, "light ABI anythingSize");
_Static_assert((sizeof(seenV)) == 1, "light ABI seenSize");
_Static_assert(((seenV)-1 < 0) == 0, "light ABI seenSigned");
_Static_assert((sizeof(circle_data[0])) == 2, "light ABI circleElementSize");
_Static_assert((sizeof(((light_source*)0)->next)) == 8, "light ABI ls_next_size");
_Static_assert((sizeof(((light_source*)0)->x)) == 2, "light ABI ls_x_size");
_Static_assert((sizeof(((light_source*)0)->y)) == 2, "light ABI ls_y_size");
_Static_assert((sizeof(((light_source*)0)->range)) == 2, "light ABI ls_range_size");
_Static_assert((sizeof(((light_source*)0)->flags)) == 2, "light ABI ls_flags_size");
_Static_assert((sizeof(((light_source*)0)->type)) == 2, "light ABI ls_type_size");
_Static_assert((sizeof(((light_source*)0)->id)) == 8, "light ABI ls_id_size");
_Static_assert((sizeof(((struct obj*)0)->o_id)) == 4, "light ABI obj_o_id_size");
_Static_assert((sizeof(((struct obj*)0)->otyp)) == 2, "light ABI obj_otyp_size");
_Static_assert((sizeof(((struct obj*)0)->spe)) == 1, "light ABI obj_spe_size");
_Static_assert((sizeof(((struct obj*)0)->where)) == 1, "light ABI obj_where_size");
_Static_assert((sizeof(((struct obj*)0)->quan)) == 8, "light ABI obj_quan_size");
_Static_assert((sizeof(((struct monst*)0)->nmon)) == 8, "light ABI mon_nmon_size");
_Static_assert((sizeof(((struct monst*)0)->m_id)) == 4, "light ABI mon_m_id_size");
_Static_assert((sizeof(((struct monst*)0)->mx)) == 2, "light ABI mon_mx_size");
_Static_assert((sizeof(((struct monst*)0)->my)) == 2, "light ABI mon_my_size");
_Static_assert((sizeof(((struct monst*)0)->mhp)) == 4, "light ABI mon_mhp_size");
_Static_assert((sizeof(((coord*)0)->x)) == 2, "light ABI coord_x_size");
_Static_assert((sizeof(((coord*)0)->y)) == 2, "light ABI coord_y_size");
_Static_assert((sizeof(((NHFILE*)0)->mode)) == 4, "light ABI nhf_mode_size");
_Static_assert((sizeof(((anything*)0)->a_obj)) == 8, "light ABI any_a_obj_size");
_Static_assert((sizeof(((anything*)0)->a_monst)) == 8, "light ABI any_a_monst_size");
_Static_assert((sizeof(((anything*)0)->a_void)) == 8, "light ABI any_a_void_size");
_Static_assert((sizeof(((anything*)0)->a_uint)) == 4, "light ABI any_a_uint_size");
_Static_assert((sizeof gl.light_base) == 8, "light ABI lightBase_size");
_Static_assert((sizeof gv.vision_full_recalc) == 1, "light ABI visionRecalc_size");
_Static_assert((sizeof cg.zeroany) == 8, "light ABI zeroany_size");
_Static_assert((sizeof svl.level.monlist) == 8, "light ABI fmon_size");
_Static_assert((sizeof gm.migrating_mons) == 8, "light ABI migratingMons_size");
_Static_assert((sizeof gm.mydogs) == 8, "light ABI mydogs_size");
_Static_assert((sizeof(((struct you*)0)->ux)) == 2, "light ABI u_ux_size");
_Static_assert((sizeof(((struct you*)0)->uy)) == 2, "light ABI u_uy_size");
_Static_assert((((__typeof__(((light_source*)0)->x)) -1) < 0) == 1, "light signedness light_source.x");
_Static_assert((((__typeof__(((light_source*)0)->y)) -1) < 0) == 1, "light signedness light_source.y");
_Static_assert((((__typeof__(((light_source*)0)->range)) -1) < 0) == 1, "light signedness light_source.range");
_Static_assert((((__typeof__(((light_source*)0)->flags)) -1) < 0) == 1, "light signedness light_source.flags");
_Static_assert((((__typeof__(((light_source*)0)->type)) -1) < 0) == 1, "light signedness light_source.type");
_Static_assert((((__typeof__(((struct obj*)0)->o_id)) -1) < 0) == 0, "light signedness struct obj.o_id");
_Static_assert((((__typeof__(((struct obj*)0)->otyp)) -1) < 0) == 1, "light signedness struct obj.otyp");
_Static_assert((((__typeof__(((struct obj*)0)->spe)) -1) < 0) == 1, "light signedness struct obj.spe");
_Static_assert((((__typeof__(((struct obj*)0)->where)) -1) < 0) == 1, "light signedness struct obj.where");
_Static_assert((((__typeof__(((struct obj*)0)->quan)) -1) < 0) == 1, "light signedness struct obj.quan");
_Static_assert((((__typeof__(((struct monst*)0)->m_id)) -1) < 0) == 0, "light signedness struct monst.m_id");
_Static_assert((((__typeof__(((struct monst*)0)->mx)) -1) < 0) == 1, "light signedness struct monst.mx");
_Static_assert((((__typeof__(((struct monst*)0)->my)) -1) < 0) == 1, "light signedness struct monst.my");
_Static_assert((((__typeof__(((struct monst*)0)->mhp)) -1) < 0) == 1, "light signedness struct monst.mhp");
_Static_assert((((__typeof__(((coord*)0)->x)) -1) < 0) == 1, "light signedness coord.x");
_Static_assert((((__typeof__(((coord*)0)->y)) -1) < 0) == 1, "light signedness coord.y");
_Static_assert((((__typeof__(((NHFILE*)0)->mode)) -1) < 0) == 1, "light signedness NHFILE.mode");
_Static_assert((((__typeof__(((anything*)0)->a_uint)) -1) < 0) == 0, "light signedness anything.a_uint");
_Static_assert(offsetof(anything,a_obj) == 0, "light union member a_obj");
_Static_assert(offsetof(anything,a_monst) == 0, "light union member a_monst");
_Static_assert(offsetof(anything,a_void) == 0, "light union member a_void");
_Static_assert(offsetof(anything,a_uint) == 0, "light union member a_uint");
_Static_assert((((__typeof__(gv.vision_full_recalc)) -1) < 0), "light signedness vision_full_recalc");
_Static_assert((((__typeof__(circle_data[0])) -1) < 0) && (((__typeof__(circle_start[0])) -1) < 0), "light circle signedness");
