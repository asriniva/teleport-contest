#ifndef TELEPORT_SYMBOLS_SUPPORT_H
#define TELEPORT_SYMBOLS_SUPPORT_H
#include "hack.h"
#include <stddef.h>
struct teleport_saved_sym {char *name;char *val;int which_set;struct teleport_saved_sym *next;};
struct _savedsym;
extern struct _savedsym *saved_symbols;
extern const char *const known_handling[7],*const known_restrictions[3];
extern const struct symparse loadsyms[197];
extern void (*decgraphics_mode_callback)(void),(*utf8graphics_mode_callback)(void);
#endif
