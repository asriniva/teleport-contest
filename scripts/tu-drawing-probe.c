#include "hack.h"
#include <stddef.h>
#include <emscripten/stack.h>
#include "tu-drawing-layout.h"

extern const struct class_sym def_monsyms[MAXMCLASSES];
extern const uchar def_r_oc_syms[MAXOCLASSES];

/* Read through external C declarations in a separate TU. This observes the
 * linked storage before lookup calls and cannot fold the hybrid zero data. */
int probe_table_count(int table)
{
    switch (table) {
    case 0: return MAXOCLASSES;
    case 1: return MAXMCLASSES;
    case 2: return WARNCOUNT;
    case 3: return MAXPCHARS + 1;
    case 4: return MAXOCLASSES;
    }
    return 0;
}
const void *probe_table_pointer(int table)
{
    switch (table) {
    case 0: return def_oc_syms;
    case 1: return def_monsyms;
    case 2: return def_warnsyms;
    case 3: return defsyms;
    case 4: return def_r_oc_syms;
    }
    return NULL;
}
int probe_table_symbol(int table, int index)
{
    switch (table) {
    case 0: return def_oc_syms[index].sym;
    case 1: return def_monsyms[index].sym;
    case 2: return def_warnsyms[index].sym;
    case 3: return defsyms[index].sym;
    case 4: return def_r_oc_syms[index];
    }
    return 0;
}
const char *probe_table_name(int table, int index)
{
    switch (table) {
    case 0: return def_oc_syms[index].name;
    case 1: return def_monsyms[index].name;
    }
    return NULL;
}
const char *probe_table_explanation(int table, int index)
{
    switch (table) {
    case 0: return def_oc_syms[index].explain;
    case 1: return def_monsyms[index].explain;
    case 2: return def_warnsyms[index].explanation;
    case 3: return defsyms[index].explanation;
    }
    return NULL;
}
int probe_table_color(int table, int index)
{
    switch (table) {
    case 2: return def_warnsyms[index].color;
    case 3: return defsyms[index].color;
    }
    return -1;
}
int probe_object(int character) { return def_char_to_objclass((char) character); }
int probe_monclass(int character) { return def_char_to_monclass((char) character); }
int probe_furniture(int character) { return def_char_is_furniture((char) character); }
int probe_char_signed(void) { return (char) -1 < 0; }
size_t probe_stack(void) { return emscripten_stack_get_current(); }
