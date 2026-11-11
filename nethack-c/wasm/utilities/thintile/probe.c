#ifdef MIXED_THIN
extern int teleport_thin_main(int,char**);
int probe_run(int argc,char**argv){return teleport_thin_main(argc,argv);}
#else
#define main thin_source_main
#ifndef UTILITY_THINTILE_REFERENCE_SOURCE
#error "Explicit absolute original reference source required"
#endif
#include UTILITY_THINTILE_REFERENCE_SOURCE
#undef main
int probe_run(int argc,char**argv){return thin_source_main(argc,argv);}
#endif
