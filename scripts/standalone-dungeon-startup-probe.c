/* Actual original-C dungeon startup with the original Lua interpreter. */
#include "standalone-startup-probe.c"
void probe_startup_dungeons(void){init_dungeons();}
const volatile void *probe_dungeon_global(int op){switch(op){case 0:return &svs;case 1:return &gl;case 2:return &svb;case 3:return &svt;}return NULL;}
