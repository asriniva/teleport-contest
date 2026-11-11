#ifdef MIXED_GENERATOR
#include "../common/abi.h"
extern const char *teleport_tm_name(int,int,int);
extern boolean teleport_tm_acceptable(int,int,const char*,const char*);
extern void teleport_tm_precheck(int,const char*);
extern void teleport_tm_add(int,int,int,int,const char*,const char*);
extern void teleport_tm_dump(FILE*);
extern void teleport_tm_free(void);
extern int teleport_gen_main(int,char**);
extern void teleport_gen_init(void);
extern int teleport_gen_state(int);
extern void *tm_storage(int);
const char *tilename(int a,int b,int c){return teleport_tm_name(a,b,c);}
boolean acceptable_tilename(int a,int b,const char*c,const char*d){return teleport_tm_acceptable(a,b,c,d);}
void precheck(int n,const char*s){teleport_tm_precheck(n,s);}
void add_tileref(int n,int g,enum tilesrc s,int e,const char*a,const char*b){teleport_tm_add(n,g,s,e,a,b);}
void dump_tilerefs(FILE*p){teleport_tm_dump(p);}
void free_tilerefs(void){teleport_tm_free();}
void init_tilemap(void){teleport_gen_init();}
int probe_run(int a,char**b){return teleport_gen_main(a,b);}
int probe_state(int i){return teleport_gen_state(i);}
void*probe_map(void){return tm_storage(0);}
void*probe_list(int i){return ((struct tiles_used**)tm_storage(1))[i];}
int probe_offset(int kind,int i){return 0;}
#else
#define main generator_source_main
#ifndef TILEMAP_ORIGINAL_SOURCE
#error "explicit original tilemap source path required"
#endif
#include TILEMAP_ORIGINAL_SOURCE
#undef main
int probe_run(int a,char**b){return generator_source_main(a,b);}
int probe_state(int i){switch(i){case 0:return TILE_corr;case 1:return TILE_stone;case 2:return TILE_unexplored;case 3:return TILE_nothing;case 4:return lastmontile;case 5:return lastobjtile;case 6:return lastothtile;case 7:return laststatuetile;}return -1;}
void*probe_map(void){return tilemap;}
void*probe_list(int i){return tilelist[i];}
int probe_offset(int kind,int i){return kind?expl_offsets[i]:wall_offsets[i];}
#endif
void probe_init_catalogues(void){objects_globals_init();monst_globals_init();}
void probe_init_map(void){init_tilemap();}
void probe_free(void){free_tilerefs();}
