#include "hack.h"
#include <stddef.h>
#include <limits.h>

#define EXTRA_LAYOUT(name, value) { #name, value }
#define EXTRA_ROGUE_FIELD(field) EXTRA_LAYOUT(r_##field, offsetof(struct rogueroom, field)), EXTRA_LAYOUT(r_##field##_size, sizeof(((struct rogueroom *) 0)->field))
static const struct {
    const char *name;
    size_t value;
} extralev_layout[] = {
    EXTRA_LAYOUT(pointerSize, sizeof(void *)), EXTRA_LAYOUT(intSize, sizeof(int)),
    EXTRA_LAYOUT(longSize, sizeof(long)), EXTRA_LAYOUT(CHAR_BIT, CHAR_BIT),
    EXTRA_LAYOUT(booleanSize, sizeof(boolean)), EXTRA_LAYOUT(booleanSigned, (boolean) -1 < 0),
    EXTRA_LAYOUT(coordxySize, sizeof(coordxy)), EXTRA_LAYOUT(coordxySigned, (coordxy) -1 < 0),
    EXTRA_LAYOUT(rogueSize, sizeof(struct rogueroom)),
    EXTRA_ROGUE_FIELD(rlx), EXTRA_ROGUE_FIELD(rly), EXTRA_ROGUE_FIELD(dx), EXTRA_ROGUE_FIELD(dy),
    EXTRA_ROGUE_FIELD(real), EXTRA_ROGUE_FIELD(doortable), EXTRA_ROGUE_FIELD(nroom),
    EXTRA_LAYOUT(rOffset, offsetof(__typeof__(gr), r)),
    EXTRA_LAYOUT(rColumns, sizeof gr.r / sizeof gr.r[0]),
    EXTRA_LAYOUT(rRows, sizeof gr.r[0] / sizeof gr.r[0][0]),
    EXTRA_LAYOUT(nroomOffset, offsetof(__typeof__(svn), nroom)),
    EXTRA_LAYOUT(nroomSize, sizeof svn.nroom),
    EXTRA_LAYOUT(smeqOffset, offsetof(__typeof__(gs), smeq)),
    EXTRA_LAYOUT(smeqSize, sizeof gs.smeq[0]),
    EXTRA_LAYOUT(smeqCount, sizeof gs.smeq / sizeof gs.smeq[0]),
    EXTRA_LAYOUT(roomsOffset, offsetof(__typeof__(svr), rooms)),
    EXTRA_LAYOUT(roomSize, sizeof(struct mkroom)),
    EXTRA_LAYOUT(roomCount, sizeof svr.rooms / sizeof svr.rooms[0]),
    EXTRA_LAYOUT(levlOffset, offsetof(__typeof__(svl), level.locations)),
    EXTRA_LAYOUT(terrainSize, sizeof(struct rm)),
    EXTRA_LAYOUT(terrainType, offsetof(struct rm, typ)),
    EXTRA_LAYOUT(terrainTypeSize, sizeof(((struct rm *) 0)->typ)),
    EXTRA_LAYOUT(permonstSize, sizeof(struct permonst)),
    EXTRA_LAYOUT(monsterSize, sizeof(struct monst)),
    EXTRA_LAYOUT(objectSize, sizeof(struct obj)),
    EXTRA_LAYOUT(objectQuan, offsetof(struct obj, quan)),
    EXTRA_LAYOUT(objectQuanSize, sizeof(((struct obj *) 0)->quan)),
    EXTRA_LAYOUT(objectWeight, offsetof(struct obj, owt)),
    EXTRA_LAYOUT(objectWeightSize, sizeof(((struct obj *) 0)->owt)),
    EXTRA_LAYOUT(objectSpe, offsetof(struct obj, spe)),
    EXTRA_LAYOUT(objectSpeSize, sizeof(((struct obj *) 0)->spe)),
    EXTRA_LAYOUT(COLNO, COLNO), EXTRA_LAYOUT(ROWNO, ROWNO), EXTRA_LAYOUT(NUMMONS, NUMMONS),
    EXTRA_LAYOUT(DBWALL, DBWALL), EXTRA_LAYOUT(D_NODOOR, D_NODOOR),
    EXTRA_LAYOUT(OROOM, OROOM), EXTRA_LAYOUT(CORR, CORR), EXTRA_LAYOUT(SCORR, SCORR),
    EXTRA_LAYOUT(PM_GHOST, PM_GHOST), EXTRA_LAYOUT(NO_MM_FLAGS, NO_MM_FLAGS),
    EXTRA_LAYOUT(FOOD_RATION, FOOD_RATION), EXTRA_LAYOUT(MACE, MACE),
    EXTRA_LAYOUT(TWO_HANDED_SWORD, TWO_HANDED_SWORD), EXTRA_LAYOUT(BOW, BOW), EXTRA_LAYOUT(ARROW, ARROW),
    EXTRA_LAYOUT(RING_MAIL, RING_MAIL), EXTRA_LAYOUT(PLATE_MAIL, PLATE_MAIL),
    EXTRA_LAYOUT(FAKE_AMULET_OF_YENDOR, FAKE_AMULET_OF_YENDOR),
};
#undef EXTRA_LAYOUT
#undef EXTRA_ROGUE_FIELD

size_t probe_context_size(void) { return sizeof(struct rogueroom); }
int probe_layout_count(void) { return sizeof extralev_layout / sizeof extralev_layout[0]; }
const char *probe_layout_name(int index) { return extralev_layout[index].name; }
size_t probe_layout_value(int index) { return extralev_layout[index].value; }
