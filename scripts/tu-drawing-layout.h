#include "hack.h"
#include <stddef.h>
#include <limits.h>

/* Compiler-derived data ABI and constants, outside the original TU. */
static const struct {
    const char *name;
    size_t value;
} drawing_layout[] = {
    { "classSize", sizeof(struct class_sym) },
    { "classSym", offsetof(struct class_sym, sym) },
    { "className", offsetof(struct class_sym, name) },
    { "classExplain", offsetof(struct class_sym, explain) },
    { "classSymSize", sizeof(((struct class_sym *) 0)->sym) },
    { "classSymSigned", (char) -1 < 0 },
    { "symdefSize", sizeof(struct symdef) },
    { "symdefSym", offsetof(struct symdef, sym) },
    { "symdefExplanation", offsetof(struct symdef, explanation) },
    { "symdefColor", offsetof(struct symdef, color) },
    { "symdefSymSize", sizeof(((struct symdef *) 0)->sym) },
    { "symdefColorSize", sizeof(((struct symdef *) 0)->color) },
    { "pointerSize", sizeof(void *) },
    { "CHAR_BIT", CHAR_BIT },
    { "MAXOCLASSES", MAXOCLASSES },
    { "MAXMCLASSES", MAXMCLASSES },
    { "WARNCOUNT", WARNCOUNT },
    { "MAXPCHARS", MAXPCHARS },
};

#define DRAWING_CONSTANT(name) { #name, name }
static const struct {
    const char *name;
    int value;
} drawing_constants[] = {
    DRAWING_CONSTANT(CLR_BLACK), DRAWING_CONSTANT(CLR_RED),
    DRAWING_CONSTANT(CLR_GREEN), DRAWING_CONSTANT(CLR_BROWN),
    DRAWING_CONSTANT(CLR_BLUE), DRAWING_CONSTANT(CLR_MAGENTA),
    DRAWING_CONSTANT(CLR_CYAN), DRAWING_CONSTANT(CLR_GRAY),
    DRAWING_CONSTANT(NO_COLOR), DRAWING_CONSTANT(CLR_ORANGE),
    DRAWING_CONSTANT(CLR_BRIGHT_GREEN), DRAWING_CONSTANT(CLR_YELLOW),
    DRAWING_CONSTANT(CLR_BRIGHT_BLUE), DRAWING_CONSTANT(CLR_BRIGHT_MAGENTA),
    DRAWING_CONSTANT(CLR_BRIGHT_CYAN), DRAWING_CONSTANT(CLR_WHITE),
    DRAWING_CONSTANT(CLR_MAX), DRAWING_CONSTANT(BRIGHT),
    DRAWING_CONSTANT(HI_DOMESTIC), DRAWING_CONSTANT(HI_LORD),
    DRAWING_CONSTANT(HI_OVERLORD), DRAWING_CONSTANT(HI_OBJ),
    DRAWING_CONSTANT(HI_METAL), DRAWING_CONSTANT(HI_COPPER),
    DRAWING_CONSTANT(HI_SILVER), DRAWING_CONSTANT(HI_GOLD),
    DRAWING_CONSTANT(HI_LEATHER), DRAWING_CONSTANT(HI_CLOTH),
    DRAWING_CONSTANT(HI_ORGANIC), DRAWING_CONSTANT(HI_WOOD),
    DRAWING_CONSTANT(HI_PAPER), DRAWING_CONSTANT(HI_GLASS),
    DRAWING_CONSTANT(HI_MINERAL), DRAWING_CONSTANT(DRAGON_SILVER),
    DRAWING_CONSTANT(HI_ZAP),
    DRAWING_CONSTANT(ILLOBJ_SYM), DRAWING_CONSTANT(WEAPON_SYM),
    DRAWING_CONSTANT(ARMOR_SYM), DRAWING_CONSTANT(RING_SYM),
    DRAWING_CONSTANT(AMULET_SYM), DRAWING_CONSTANT(TOOL_SYM),
    DRAWING_CONSTANT(FOOD_SYM), DRAWING_CONSTANT(POTION_SYM),
    DRAWING_CONSTANT(SCROLL_SYM), DRAWING_CONSTANT(SPBOOK_SYM),
    DRAWING_CONSTANT(WAND_SYM), DRAWING_CONSTANT(GOLD_SYM),
    DRAWING_CONSTANT(GEM_SYM), DRAWING_CONSTANT(ROCK_SYM),
    DRAWING_CONSTANT(BALL_SYM), DRAWING_CONSTANT(CHAIN_SYM),
    DRAWING_CONSTANT(VENOM_SYM),
    DRAWING_CONSTANT(MAXOCLASSES), DRAWING_CONSTANT(MAXMCLASSES),
    DRAWING_CONSTANT(WARNCOUNT), DRAWING_CONSTANT(MAXPCHARS),
};
#undef DRAWING_CONSTANT

size_t probe_context_size(void) { return sizeof(struct class_sym); }
int probe_layout_count(void) { return sizeof drawing_layout / sizeof drawing_layout[0]; }
const char *probe_layout_name(int index) { return drawing_layout[index].name; }
size_t probe_layout_value(int index) { return drawing_layout[index].value; }
int probe_constant_count(void)
{
    return sizeof drawing_constants / sizeof drawing_constants[0];
}
const char *probe_constant_name(int index) { return drawing_constants[index].name; }
int probe_constant_value(int index) { return drawing_constants[index].value; }
