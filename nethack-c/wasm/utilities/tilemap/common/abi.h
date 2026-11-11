#include "hack.h"
enum {MON_GLYPH, OBJ_GLYPH, OTH_GLYPH, TERMINATOR=-1};
enum tilesrc {monsters_file,objects_file,other_file,generated};
struct utility_tilemap {short tilenum;char name[127];int glyph;};
struct tiles_used {int tilenum;enum tilesrc src;int file_entry;char tilenam[256];char references[1024];};
