/* Original DO_WEAR owner, included alone to observe private callback identities.
 * These helpers assign test inputs; they do not replace source algorithms. */
#include "do_wear.c"
#include <stdint.h>
#include <stdlib.h>

uintptr_t probe_equipment_callback(int i)
{
    switch (i) {
#include "armor-callbacks.inc"
    default:
        abort();
    }
}

void probe_equipment_after(int i)
{
    if (i < 0) {
        ga.afternmv = NULL;
    } else {
        /* Source callbacks 0..13 all have the actual int(void) signature. */
        if (i > 13)
            abort();
        ga.afternmv = (int (*)(void)) probe_equipment_callback(i);
    }
}
