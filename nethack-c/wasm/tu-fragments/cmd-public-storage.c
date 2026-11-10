/* CMD zero-only public storage. Compile separately at -O2 without LTO. */
#include "cmd-types.h"
#if defined(__APPLE__) && !defined(__EMSCRIPTEN__)
#define CMD_WRITABLE_DATA __attribute__((section("__DATA,__data")))
#else
#define CMD_WRITABLE_DATA __attribute__((section(".data")))
#endif
const char unavailcmd[26] CMD_WRITABLE_DATA = {0};
const char*levltyp[39];
struct ext_func_tab extcmdlist[171];
#undef CMD_WRITABLE_DATA
