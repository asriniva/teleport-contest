#ifdef MIXED_BMP
#include "abi.h"
extern int teleport_bmp_main(int,char**);
extern int teleport_bmp_distance(const RGB*,const RGB*);
extern int teleport_bmp_nearest(const RGB*,const RGB*,int);
int probe_run(int argc,char**argv){return teleport_bmp_main(argc,argv);}
int probe_distance(const RGB*a,const RGB*b){return teleport_bmp_distance(a,b);}
int probe_nearest(const RGB*c,const RGB*pal,int n){return teleport_bmp_nearest(c,pal,n);}
#else
#define main bmp_source_main
#ifndef UTILITY_BMP_ORIGINAL_SOURCE
#error "Pass the explicit original source path from the utility build script"
#endif
#include UTILITY_BMP_ORIGINAL_SOURCE
#undef main
int probe_run(int argc,char**argv){return bmp_source_main(argc,argv);}
int probe_distance(const RGB*a,const RGB*b){return coldist(a,b);}
int probe_nearest(const RGB*c,const RGB*pal,int n){return nearest(c,pal,n);}
#endif
