/* Test-only real original Lua table accessors; only world/source hooks are controlled. */
#define nhl_init teleport_questpgr_unused_init
#define nhl_loadlua teleport_questpgr_unused_load
#define nhl_done teleport_questpgr_unused_done
#include "../.cache/wasm64-build/tree/src/nhlua.c"
