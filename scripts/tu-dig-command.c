/* Actual cmd.c dependencies; only unrelated controlled world symbols renamed. */
#define set_occupation teleport_dig_dependency_set_occupation
#define cmdq_add_ec teleport_dig_dependency_cmdq_add_ec
#define cmdq_add_key teleport_dig_dependency_cmdq_add_key
#define getdir teleport_dig_dependency_getdir
#define movecmd teleport_dig_dependency_movecmd
#define cmd_from_dir teleport_dig_dependency_cmd_from_dir
#define dxdy_moveok teleport_dig_dependency_dxdy_moveok
#include "cmd.c"
