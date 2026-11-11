/* The inherited NetHack API takes int n, unlike the SDK libc size_t API.
 * Isolate only the unused libc declaration; the owned source retains its name. */
#define initstate utility_sdk_libc_initstate
#include <stdlib.h>
#undef initstate
