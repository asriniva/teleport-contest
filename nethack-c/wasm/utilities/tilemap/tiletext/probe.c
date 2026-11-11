#ifdef MIXED_TM
#include "../common/abi.h"
extern const char *teleport_tm_name(int,int,int);
extern boolean teleport_tm_acceptable(int,int,const char*,const char*);
extern void teleport_tm_precheck(int,const char*);
extern void teleport_tm_add(int,int,int,int,const char*,const char*);
extern void teleport_tm_dump(FILE*);
extern void teleport_tm_free(void);
const char *tilename(int a,int b,int c){return teleport_tm_name(a,b,c);}
boolean acceptable_tilename(int a,int b,const char*c,const char*d){return teleport_tm_acceptable(a,b,c,d);}
void precheck(int n,const char*s){teleport_tm_precheck(n,s);}
void add_tileref(int n,int g,enum tilesrc s,int e,const char*a,const char*b){teleport_tm_add(n,g,s,e,a,b);}
void dump_tilerefs(FILE*p){teleport_tm_dump(p);}
void free_tilerefs(void){teleport_tm_free();}
const char *probe_name(int a,int b,int c){return tilename(a,b,c);}
boolean probe_acceptable(int a,int b,const char*c,const char*d){return acceptable_tilename(a,b,c,d);}
void probe_precheck(int n,const char*s){precheck(n,s);}
void probe_add(int n,int g,int s,int e,const char*a,const char*b){add_tileref(n,g,s,e,a,b);}
void probe_dump(FILE*p){dump_tilerefs(p);}
void probe_free(void){free_tilerefs();}
extern void *tm_storage(int);
void *probe_list(int n){return ((struct tiles_used**)tm_storage(1))[n];}
void probe_set_map(int i,short n){((struct utility_tilemap*)tm_storage(0))[i].tilenum=n;}
int probe_table_count(int i){return 0;}
const char*probe_table_string(int i,int row,int field){return 0;}
int probe_table_int(int i,int row,int field){return 0;}
#else
#define TILETEXT
#ifndef TILEMAP_ORIGINAL_SOURCE
#error "explicit original tilemap source path required"
#endif
#include TILEMAP_ORIGINAL_SOURCE
const char *probe_name(int a,int b,int c){return tilename(a,b,c);}
boolean probe_acceptable(int a,int b,const char*c,const char*d){return acceptable_tilename(a,b,c,d);}
void probe_precheck(int n,const char*s){precheck(n,s);}
void probe_add(int n,int g,int s,int e,const char*a,const char*b){add_tileref(n,g,s,e,a,b);}
void probe_dump(FILE*p){dump_tilerefs(p);}
void probe_free(void){free_tilerefs();}
void *probe_list(int n){return tilelist[n];}
void probe_set_map(int i,short n){tilemap[i].tilenum=n;}
int probe_table_count(int i){switch(i){case 0:return SIZE(altlabels);case 1:return SIZE(conditionals);case 2:return SIZE(altar_text);case 3:return SIZE(wall_texts);case 4:return SIZE(walldesc);case 5:return SIZE(expl_texts);case 6:return SIZE(zap_texts);case 7:return SIZE(tilesrc_texts);}return -1;}
const char*probe_table_string(int i,int row,int field){switch(i){case 0:return field?altlabels[row].expectedlabel:altlabels[row].tilelabel;case 1:return conditionals[row].name;case 2:return altar_text[row];case 3:return wall_texts[row];case 4:return walldesc[row];case 5:return expl_texts[row];case 6:return zap_texts[row];case 7:return tilesrc_texts[row];}return 0;}
int probe_table_int(int i,int row,int field){return i==0?altlabels[row].idx:field?conditionals[row].predecessor:conditionals[row].sequence;}
#endif
void probe_init(void){objects_globals_init();monst_globals_init();}
FILE*probe_open(void){return tmpfile();}
long probe_len(FILE*p){fflush(p);return ftell(p);}
size_t probe_read(FILE*p,char*b,size_t n){rewind(p);return fread(b,1,n,p);}
void probe_close(FILE*p){fclose(p);}

#include "tile.h"
static pixel reader_pixels[TILE_Y][TILE_X];
boolean probe_text_open(const char*p){return fopen_text_file(p,RDTMODE);}
boolean probe_text_read(void){return read_text_tile(reader_pixels);}
int probe_text_close(void){return fclose_text_file();}
void *probe_text_pixels(void){return reader_pixels;}
