/* Separate no-LTO caller: exact configured native callback signatures only. */
#include "hack.h"
#include <stdint.h>
_Static_assert(sizeof(void *) == 8 && sizeof(size_t) == 8,
               "NHLUA memory64 callback ABI");
_Static_assert(__builtin_types_compatible_p(lua_Alloc,
               void *(*)(void *, void *, size_t, size_t)),
               "NHLUA allocator callback signature");
_Static_assert(__builtin_types_compatible_p(lua_Hook,
               void (*)(lua_State *, lua_Debug *)),
               "NHLUA debug callback signature");
int probe_consumer_callback(lua_CFunction fn, lua_State *L)
{
    return fn(L);
}
void *probe_consumer_allocator(lua_Alloc fn, void *ud, void *ptr,
                               size_t osize, size_t nsize)
{
    return fn(ud, ptr, osize, nsize);
}
void probe_consumer_hook(lua_Hook fn, lua_State *L, lua_Debug *ar)
{
    fn(L, ar);
}
void probe_consumer_warning(lua_WarnFunction fn, void *ud,
                            const char *fragment, int continued)
{
    fn(ud, fragment, continued);
}
int probe_consumer_table_int(lua_State *L, const char *key)
{
    return get_table_int(L, key);
}
