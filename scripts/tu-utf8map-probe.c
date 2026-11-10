#include "hack.h"
#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include "tu-utf8map-layout.h"

glyph_map glyphmap[MAX_GLYPH];
__typeof__(gg) gg;
__typeof__(gs) gs;
__typeof__(gc) gc;
const char hexdd[33] = "00112233445566778899aAbBcCdDeEfF";
const glyph_info nul_glyphinfo = { 0 };
static char trace[8192];
static int apply_enabled;
void panic(const char *format, ...) { abort(); }
static void append(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(trace + strlen(trace), sizeof(trace) - strlen(trace), format, args);
    va_end(args);
}
int decode_glyph(const char *text, int *glyph)
{
    int i, value = 0;
    append("decode;");
    if (strncmp(text, "ABCD", 4)) return 0;
    for (i = 4; i < 8; i++) {
        const char *p;
        if (!text[i] || !(p = strchr(hexdd, text[i]))) return 0;
        value = value * 16 + (int) (p - hexdd) / 2;
    }
    if (value >= MAX_GLYPH) return 0;
    *glyph = value; return 8;
}
void map_glyphinfo(coordxy x, coordxy y, int glyph, unsigned flags, glyph_info *out)
{
    append("map:%d:%d:%d:%u;", x, y, glyph, flags);
    *out = nul_glyphinfo; out->gm = glyphmap[glyph];
}
struct customization_detail *find_matching_customization(const char *name,
    enum customization_types type, enum graphics_sets which)
{
    struct symset_customization *custom = &gs.sym_customizations[which][type];
    append("find:%s:%d:%d;", name, type, which);
    return custom->customization_name && !strcmp(custom->customization_name, name) ? custom->details : NULL;
}
int probe_gbuf_count(void)
{
    int count = 0, x, y;
    for (y = 0; y < ROWNO; y++) for (x = 0; x < COLNO; x++)
        count += gg.gbuf[y][x].glyphinfo.gm.u != NULL;
    return count;
}
void apply_customizations(enum graphics_sets which, enum do_customizations type)
{
    append("apply:%d:%d:live=%d;", which, type, probe_gbuf_count());
    if (apply_enabled) set_map_u(&glyphmap[7], 0x2603, (const uint8 *) "SNOW");
}
void probe_clear_trace(void) { trace[0] = '\0'; }
const char *probe_trace(void) { return trace; }
int probe_unicode(const char *text) { return unicode_val(text); }
int probe_set(int index, uint32 value, const uint8 *text)
{
    return set_map_u(index < 0 ? NULL : &glyphmap[index], value, text);
}
void probe_free(void) { free_all_glyphmap_u(); }
void *probe_map_u(int index) { return glyphmap[index].u; }
uint32 probe_map_code(int index) { return glyphmap[index].u ? glyphmap[index].u->utf32ch : 0; }
const uint8 *probe_map_text(int index) { return glyphmap[index].u ? glyphmap[index].u->utf8str : NULL; }
void probe_null_text(int index)
{
    if (glyphmap[index].u && glyphmap[index].u->utf8str) {
        free(glyphmap[index].u->utf8str); glyphmap[index].u->utf8str = NULL;
    }
}
void probe_gbuf(int x, int y, int index)
{
    gg.gbuf[y][x].glyphinfo.gm.u = glyphmap[index].u;
}
void probe_fallback(int index, int symbol)
{
    glyphmap[index].sym.symidx = index % SIZE(gs.showsyms);
    gs.showsyms[glyphmap[index].sym.symidx] = symbol;
}
char *probe_mixed(char *out, size_t size, const char *in, int *flags)
{
    return mixed_to_utf8(out, size, in, flags);
}
int probe_custom(const char *name, int glyph, uint32 value, const uint8 *text, int which)
{
    return add_custom_urep_entry(name, glyph, value, text, which);
}
const char *probe_custom_name(int which) { return gs.sym_customizations[which][custom_ureps].customization_name; }
int probe_custom_count(int which) { return gs.sym_customizations[which][custom_ureps].count; }
int probe_custom_type(int which) { return gs.sym_customizations[which][custom_ureps].custtype; }
struct customization_detail *probe_custom_head(int which) { return gs.sym_customizations[which][custom_ureps].details; }
struct customization_detail *probe_custom_end(int which) { return gs.sym_customizations[which][custom_ureps].details_end; }
struct customization_detail *probe_detail_next(struct customization_detail *detail) { return detail->next; }
int probe_detail_glyph(struct customization_detail *detail) { return detail->content.urep.glyphidx; }
uint32 probe_detail_code(struct customization_detail *detail) { return detail->content.urep.u.utf32ch; }
const uint8 *probe_detail_text(struct customization_detail *detail) { return detail->content.urep.u.utf8str; }
void probe_reset(int which, int enabled)
{
    gc.currentgraphics = which; apply_enabled = enabled; reset_customsymbols();
}
void probe_cleanup(void)
{
    int which;
    free_all_glyphmap_u();
    for (which = 0; which < NUM_GRAPHICS; which++) {
        struct symset_customization *custom = &gs.sym_customizations[which][custom_ureps];
        struct customization_detail *detail = custom->details;
        while (detail) {
            struct customization_detail *next = detail->next;
            free(detail->content.urep.u.utf8str); free(detail); detail = next;
        }
        free((void *) custom->customization_name); memset(custom, 0, sizeof *custom);
    }
    trace[0] = '\0';
}
size_t probe_stack(void) { return emscripten_stack_get_current(); }
