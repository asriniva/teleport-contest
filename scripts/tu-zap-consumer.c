/* Test-only optimized native extern-table consumer. The indexing expression is
 * exactly trap.c4525/4533; this does not copy fire_damage or its policy. */
#include "hack.h"
extern const char *const destroy_strings[][3];
const char *teleport_zap_trap_consumer(const struct obj *obj, int dindx)
{
    return destroy_strings[dindx][(obj->quan > 1L)];
}
