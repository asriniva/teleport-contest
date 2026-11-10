/* DECL layout comes from separately compiled typed metadata, not guessed constants. */
#ifndef TELEPORT_DECL_LAYOUT_H
#define TELEPORT_DECL_LAYOUT_H
#include <stdint.h>
extern int teleport_decl_layout_count(void);
extern const char*teleport_decl_layout_name(int);
extern uint64_t teleport_decl_layout_value(int);
#endif
