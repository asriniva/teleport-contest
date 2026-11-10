/* Separate no-LTO typed caller. It owns no trap policy. */
#include "hack.h"
int probe_trap_consumer(coordxy x, coordxy y, unsigned flags)
{
    struct trap *t = t_at(x, y);
    if (!t)
        return 0;
    dotrap(t, flags);
    return t_at(x, y) != NULL;
}
int probe_trap_obj_consumer(int (*callback)(struct obj *), struct obj *object)
{
    return callback(object);
}
