#include "hack.h"
#include <stddef.h>

#ifndef ENHANCED_SYMBOLS
#error "The utf8map JS adapter requires ENHANCED_SYMBOLS"
#endif

/* Compiler-derived ABI metadata, outside the original translation unit. */
static const struct {
    const char *name;
    size_t value;
} utf8map_layout[] = {
    { "pointerSize", sizeof(void *) },
    { "intSize", sizeof(int) },
    { "ENHANCED_SYMBOLS", 1 },
    { "UnicodeSize", sizeof(struct unicode_representation) },
    { "unicodeUtf32ch", offsetof(struct unicode_representation, utf32ch) },
    { "unicodeUtf8str", offsetof(struct unicode_representation, utf8str) },
    { "GlyphMapSize", sizeof(glyph_map) },
    { "glyphMapU", offsetof(glyph_map, u) },
    { "glyphMapSymidx", offsetof(glyph_map, sym.symidx) },
    { "GlyphInfoSize", sizeof(glyph_info) },
    { "glyphInfoGm", offsetof(glyph_info, gm) },
    { "GbufEntrySize", sizeof(gbuf_entry) },
    { "gbufGlyphinfo", offsetof(gbuf_entry, glyphinfo) },
    { "DetailSize", sizeof(struct customization_detail) },
    { "detailGlyphidx", offsetof(struct customization_detail, content.urep.glyphidx) },
    { "detailUnicode", offsetof(struct customization_detail, content.urep.u) },
    { "detailNext", offsetof(struct customization_detail, next) },
    { "CustomizationSize", sizeof(struct symset_customization) },
    { "customName", offsetof(struct symset_customization, customization_name) },
    { "customCount", offsetof(struct symset_customization, count) },
    { "customType", offsetof(struct symset_customization, custtype) },
    { "customDetails", offsetof(struct symset_customization, details) },
    { "customDetailsEnd", offsetof(struct symset_customization, details_end) },
    { "MAX_GLYPH", MAX_GLYPH },
    { "COLNO", COLNO },
    { "ROWNO", ROWNO },
    { "NUM_GRAPHICS", NUM_GRAPHICS },
    { "PRIMARYSET", PRIMARYSET },
    { "ROGUESET", ROGUESET },
    { "UNICODESET", UNICODESET },
    { "custom_count", custom_count },
    { "custom_ureps", custom_ureps },
    { "do_custom_symbols", do_custom_symbols },
};

size_t probe_context_size(void) { return sizeof(glyph_map); }
int probe_layout_count(void)
{
    return sizeof utf8map_layout / sizeof utf8map_layout[0];
}
const char *probe_layout_name(int index) { return utf8map_layout[index].name; }
size_t probe_layout_value(int index) { return utf8map_layout[index].value; }
