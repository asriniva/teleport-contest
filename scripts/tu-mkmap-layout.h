#include "hack.h"
#include "sp_lev.h"
#include <stddef.h>
#include <limits.h>

#define MAP_LAYOUT(name, value) { #name, value }
#define MAP_ROOM(field) MAP_LAYOUT(room_##field, offsetof(struct mkroom, field)), MAP_LAYOUT(room_##field##_size, sizeof(((struct mkroom *) 0)->field))
#define MAP_INIT(field) MAP_LAYOUT(init_##field, offsetof(lev_init, field)), MAP_LAYOUT(init_##field##_size, sizeof(((lev_init *) 0)->field))
#define MAP_BOUND(field) MAP_LAYOUT(bound_##field, offsetof(__typeof__(gm), field)), MAP_LAYOUT(bound_##field##_size, sizeof gm.field)
static const struct {
    const char *name;
    size_t value;
} mkmap_layout[] = {
    MAP_LAYOUT(STONE, STONE), MAP_LAYOUT(CORR, CORR), MAP_LAYOUT(HWALL, HWALL),
    MAP_LAYOUT(pointerSize, sizeof(void *)), MAP_LAYOUT(intSize, sizeof(int)),
    MAP_LAYOUT(longSize, sizeof(long)), MAP_LAYOUT(shortSize, sizeof(short)),
    MAP_LAYOUT(charSize, sizeof(char)), MAP_LAYOUT(charSigned, (char) -1 < 0),
    MAP_LAYOUT(CHAR_BIT, CHAR_BIT), MAP_LAYOUT(booleanSize, sizeof(boolean)),
    MAP_LAYOUT(booleanSigned, (boolean) -1 < 0),
    MAP_LAYOUT(coordxySize, sizeof(coordxy)), MAP_LAYOUT(coordxySigned, (coordxy) -1 < 0),
    MAP_LAYOUT(terrainSize, sizeof(struct rm)), MAP_LAYOUT(terrainType, offsetof(struct rm, typ)),
    MAP_LAYOUT(terrainTypeSize, sizeof(((struct rm *) 0)->typ)),
    MAP_LAYOUT(levlOffset, offsetof(__typeof__(svl), level.locations)),
    MAP_LAYOUT(newLocations, offsetof(__typeof__(gn), new_locations)),
    MAP_LAYOUT(newLocationsSize, sizeof gn.new_locations),
    MAP_LAYOUT(nsubroom, offsetof(__typeof__(gn), nsubroom)), MAP_LAYOUT(nsubroomSize, sizeof gn.nsubroom),
    MAP_LAYOUT(nLocFilled, offsetof(__typeof__(gn), n_loc_filled)), MAP_LAYOUT(nLocFilledSize, sizeof gn.n_loc_filled),
    MAP_BOUND(min_rx), MAP_BOUND(max_rx), MAP_BOUND(min_ry), MAP_BOUND(max_ry),
    MAP_LAYOUT(nroom, offsetof(__typeof__(svn), nroom)), MAP_LAYOUT(nroomSize, sizeof svn.nroom),
    MAP_LAYOUT(rooms, offsetof(__typeof__(svr), rooms)),
    MAP_LAYOUT(roomCount, sizeof svr.rooms / sizeof svr.rooms[0]),
    MAP_LAYOUT(subrooms, offsetof(__typeof__(gs), subrooms)), MAP_LAYOUT(subroomsPointerSize, sizeof gs.subrooms),
    MAP_LAYOUT(roomSize, sizeof(struct mkroom)),
    MAP_ROOM(lx), MAP_ROOM(hx), MAP_ROOM(ly), MAP_ROOM(hy), MAP_ROOM(rlit), MAP_ROOM(irregular),
    MAP_LAYOUT(coordSize, sizeof(coord)), MAP_LAYOUT(coordX, offsetof(coord, x)), MAP_LAYOUT(coordY, offsetof(coord, y)),
    MAP_LAYOUT(initSize, sizeof(lev_init)),
    MAP_INIT(bg), MAP_INIT(fg), MAP_INIT(smoothed), MAP_INIT(joined), MAP_INIT(lit), MAP_INIT(walled), MAP_INIT(icedpools),
    MAP_LAYOUT(heroLevel, offsetof(struct you, uz)),
    MAP_LAYOUT(levelDnum, offsetof(d_level, dnum)), MAP_LAYOUT(levelDlevel, offsetof(d_level, dlevel)),
    MAP_LAYOUT(levelFieldSize, sizeof(((d_level *) 0)->dnum)),
    MAP_LAYOUT(COLNO, COLNO), MAP_LAYOUT(ROWNO, ROWNO),
    MAP_LAYOUT(WIDTH, COLNO - 2), MAP_LAYOUT(HEIGHT, ROWNO - 1),
    MAP_LAYOUT(ROOM, ROOM), MAP_LAYOUT(DBWALL, DBWALL), MAP_LAYOUT(DOOR, DOOR), MAP_LAYOUT(POOL, POOL),
    MAP_LAYOUT(NO_ROOM, NO_ROOM), MAP_LAYOUT(SHARED, SHARED), MAP_LAYOUT(SDOOR, SDOOR),
    MAP_LAYOUT(ROOMOFFSET, ROOMOFFSET), MAP_LAYOUT(OROOM, OROOM), MAP_LAYOUT(MAXNROFROOMS, MAXNROFROOMS),
    MAP_LAYOUT(TREE, TREE), MAP_LAYOUT(LAVAPOOL, LAVAPOOL), MAP_LAYOUT(ICE, ICE),
    MAP_LAYOUT(ICED_POOL, ICED_POOL), MAP_LAYOUT(ICED_MOAT, ICED_MOAT),
};
#undef MAP_LAYOUT
#undef MAP_ROOM
#undef MAP_INIT
#undef MAP_BOUND

size_t probe_context_size(void) { return sizeof(struct mkroom); }
int probe_layout_count(void) { return sizeof mkmap_layout / sizeof mkmap_layout[0]; }
const char *probe_layout_name(int index) { return mkmap_layout[index].name; }
size_t probe_layout_value(int index) { return mkmap_layout[index].value; }
