/* Original GLYPHS alone, with original transport's ABI assertions enabled. */
#include "glyphs.c"
#define TELEPORT_GLYPHS_VALIDATE_SOURCE 1
#include "tu-fragments/glyphs-support.c"
size_t probe_glyph_cache_count(void){return glyphid_cache_size;}
const void *probe_glyph_cache_entry(size_t i){return &glyphid_cache[i];}
