#ifdef MIXED_TB
#include "abi.h"
extern int teleport_tb_main(int,char**);
extern int teleport_tb_path(const char*,const char*,char*,size_t);
extern short teleport_tb_short(short);
extern int32_t teleport_tb_long(int32_t);
int probe_run(int n,char**p){return teleport_tb_main(n,p);}
int probe_path(const char*a,const char*b,char*c,size_t d){return teleport_tb_path(a,b,c,d);}
short probe_short(short n){return teleport_tb_short(n);}
int32_t probe_long(int32_t n){return teleport_tb_long(n);}
#else
#define main tb_source_main
#include UTILITY_TILE2BMP_REFERENCE_SOURCE
#undef main
int probe_run(int n,char**p){return tb_source_main(n,p);}
int probe_path(const char*a,const char*b,char*c,size_t d){return set_tilefile_path(a,b,c,d);}
short probe_short(short n){return leshort(n);}
int32_t probe_long(int32_t n){return lelong(n);}
#endif
