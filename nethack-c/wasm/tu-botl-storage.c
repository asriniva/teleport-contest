/* Separate native storage only: BOTL JavaScript owns every initializer.
 * Keep this object separate/no LTO so foreign const reads cannot fold zeros. */
#include "tu-botl-abi.h"
const char *const enc_stat[6] = {0};
const struct conditions_t conditions[CONDITION_COUNT] = {{0}};
struct condtests_t condtests[CONDITION_COUNT] = {{0}};
int cond_idx[CONDITION_COUNT] = {0};
const char *terrain_descr[47] = {0};
void *teleport_botl_storage(int which)
{
    switch (which) {
    case 0: return (void *) enc_stat;
    case 1: return (void *) conditions;
    case 2: return condtests;
    case 3: return cond_idx;
    case 4: return terrain_descr;
    default: return (void *) 0;
    }
}
