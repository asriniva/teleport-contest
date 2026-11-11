#include "config.h"
#ifndef REFERENCE_TILETEXT
#include "tile.h"
#endif
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
extern const char*tilename(int,int,int);
extern boolean acceptable_tilename(int,int,const char*,const char*);
static int name_trace[4096],name_count;
const char*utility_tilename(int set,int index,int gender){if(name_count+3<=4096){name_trace[name_count++]=set;name_trace[name_count++]=index;name_trace[name_count++]=gender;}return tilename(set,index,gender);}
#ifdef REFERENCE_TILETEXT
#define tilename utility_tilename
#ifndef UTILITY_TILETEXT_REFERENCE_SOURCE
#error "Explicit original source path required"
#endif
#include UTILITY_TILETEXT_REFERENCE_SOURCE
#undef tilename
#else
pixval ColorMap[3][MAXCOLORMAPSIZE],MainColorMap[3][MAXCOLORMAPSIZE];
int colorsinmap,colorsinmainmap;
static short color_index[MAXCOLORMAPSIZE];
static char charcolors[MAXCOLORMAPSIZE],inbuf[BUFSZ];
static pixel placeholder[TILE_Y][TILE_X];
extern void tiletext_js_set_grayscale(int);
extern int tiletext_js_get_next_line(FILE*,boolean);
extern void tiletext_js_read_text_colormap(FILE*);
extern boolean tiletext_js_write_text_colormap(FILE*);
extern boolean tiletext_js_read_txttile(FILE*,pixel(*)[TILE_X]);
extern void tiletext_js_write_txttile(FILE*,pixel(*)[TILE_X]);
extern void tiletext_js_init_colormap(void);
extern void tiletext_js_merge_colormap(void);
extern boolean tiletext_js_fopen_text_file(const char*,const char*);
extern boolean tiletext_js_read_text_tile(pixel(*)[TILE_X]);
extern boolean tiletext_js_write_text_tile(pixel(*)[TILE_X]);
extern int tiletext_js_fclose_text_file(void);
void set_grayscale(int gs){tiletext_js_set_grayscale(gs);}
static int get_next_line(FILE*f,boolean force){return tiletext_js_get_next_line(f,force);}
static void read_text_colormap(FILE*f){tiletext_js_read_text_colormap(f);}
static boolean write_text_colormap(FILE*f){return tiletext_js_write_text_colormap(f);}
static boolean read_txttile(FILE*f,pixel(*p)[TILE_X]){return tiletext_js_read_txttile(f,p);}
static void write_txttile(FILE*f,pixel(*p)[TILE_X]){tiletext_js_write_txttile(f,p);}
void init_colormap(void){tiletext_js_init_colormap();}
void merge_colormap(void){tiletext_js_merge_colormap();}
boolean fopen_text_file(const char*f,const char*t){return tiletext_js_fopen_text_file(f,t);}
boolean read_text_tile(pixel(*p)[TILE_X]){return tiletext_js_read_text_tile(p);}
boolean write_text_tile(pixel(*p)[TILE_X]){return tiletext_js_write_text_tile(p);}
int fclose_text_file(void){return tiletext_js_fclose_text_file();}
#endif
uintptr_t utility_tile_storage(int i){switch(i){case 0:return(uintptr_t)ColorMap;case 1:return(uintptr_t)MainColorMap;case 2:return(uintptr_t)color_index;case 3:return(uintptr_t)charcolors;case 4:return(uintptr_t)placeholder;case 5:return(uintptr_t)inbuf;case 6:return(uintptr_t)&colorsinmap;case 7:return(uintptr_t)&colorsinmainmap;default:abort();}}
uintptr_t utility_tile_layout(int i){switch(i){case 0:return TILE_X;case 1:return TILE_Y;case 2:return MAXCOLORMAPSIZE;case 3:return BUFSZ;case 4:return sizeof(pixel);case 5:return offsetof(pixel,r);case 6:return offsetof(pixel,g);case 7:return offsetof(pixel,b);case 8:return sizeof(placeholder);case 9:return(uintptr_t)RDTMODE;case 10:return(uintptr_t)WRTMODE;case 11:return CM_RED;case 12:return CM_GREEN;case 13:return CM_BLUE;default:abort();}}
long utility_tile_private(int which,FILE*f,pixel(*p)[TILE_X],int force){switch(which){case 0:return get_next_line(f,(boolean)force);case 1:read_text_colormap(f);return 0;case 2:return write_text_colormap(f);case 3:return read_txttile(f,p);case 4:write_txttile(f,p);return 0;default:abort();}}
int utility_tile_name_count(void){return name_count;}
int utility_tile_name_value(int i){return name_trace[i];}
FILE*utility_tile_fopen(const char*a,const char*b){return fopen(a,b);}
FILE*utility_tile_stderr(void){return stderr;}
int utility_tile_fgetc(FILE*f){return fgetc(f);}
int utility_tile_ungetc(int c,FILE*f){return ungetc(c,f);}
char*utility_tile_fgets(char*p,int n,FILE*f){return fgets(p,n,f);}
int utility_tile_fputc(int c,FILE*f){return fputc(c,f);}
int utility_tile_fclose(FILE*f){return fclose(f);}
int utility_tile_scan_palette(const char*s,const char*f,char*c,int*r,int*g,int*b){return sscanf(s,f,c,r,g,b);}
int utility_tile_scan_tile(const char*s,const char*f,char*t,int*i,char*b,char*g){return sscanf(s,f,t,i,b,g);}
void utility_tile_print(FILE*o,const char*f,int shape,long a,long b,long c,long d){switch(shape){case 0:fprintf(o,f);break;case 1:fprintf(o,f,(int)a,(int)b,(int)c,(int)d);break;case 2:fprintf(o,f,(char*)a);break;case 3:fprintf(o,f,(char*)a,(char*)b);break;case 4:fprintf(o,f,(char*)a,(int)b);break;case 5:fprintf(o,f,(int)a,(int)b,(char*)c);break;case 6:fprintf(o,f,(char*)a,(int)b,(char*)c);break;default:abort();}}
extern void objects_globals_init(void),monst_globals_init(void);
void utility_tile_dependency_init(void){objects_globals_init();monst_globals_init();}
#ifdef REFERENCE_TILETEXT
int utility_tile_state(int i){switch(i){case 0:return num_colors;case 1:return placeholder_init;case 2:return tile_set;case 3:return tile_set_indx;case 4:return grayscale;case 5:return tile_file!=0;default:abort();}}
#else
extern int tiletext_js_state(int);
int utility_tile_state(int i){return tiletext_js_state(i);}
#endif
_Static_assert(sizeof(pixel)==3 && sizeof(short)==2 && sizeof(int)==4,"tiletext ABI");
