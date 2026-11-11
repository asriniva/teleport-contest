#include "config.h"
#include "tile.h"
#include <stddef.h>
#include <stdarg.h>
#include <limits.h>
extern long*alloc(unsigned);
static char extension_buf[256];
static unsigned char code_buf[280];
static int lwz_table[2][1<<12];
static int lwz_stack[(1<<12)*2];
static unsigned char input_code_cell;
void*teleport_gif_static(int i){switch(i){case 0:return extension_buf;case 1:return code_buf;case 2:return lwz_table;case 3:return lwz_stack;case 4:return &input_code_cell;}return NULL;}
size_t teleport_gif_static_size(int i){switch(i){case 0:return sizeof extension_buf;case 1:return sizeof code_buf;case 2:return sizeof lwz_table;case 3:return sizeof lwz_stack;case 4:return sizeof input_code_cell;}return 0;}
static unsigned allocations,frees;static size_t alloc_sizes[4096];static void*alloc_ptrs[4096];static int free_ids[4096];
long*teleport_gif_alloc(unsigned n){long*p=alloc(n);if(allocations<4096){alloc_sizes[allocations]=n;alloc_ptrs[allocations]=p;}allocations++;return p;}
void teleport_gif_free(void*p){if(frees<4096){free_ids[frees]=-1;for(unsigned i=0;i<allocations&&i<4096;i++)if(alloc_ptrs[i]==p){free_ids[frees]=i;break;}}frees++;free(p);}
unsigned teleport_gif_allocations(void){return allocations;}
unsigned teleport_gif_frees(void){return frees;}
size_t teleport_gif_alloc_size(unsigned i){return i<allocations&&i<4096?alloc_sizes[i]:0;}
int teleport_gif_free_id(unsigned i){return i<frees&&i<4096?free_ids[i]:-2;}
void*teleport_gif_literal_alloc(size_t n){return malloc(n);}
size_t teleport_gif_metadata(int i){switch(i){case 0:return TILE_X;case 1:return TILE_Y;case 2:return sizeof(pixel);case 3:return sizeof(void*);case 4:return offsetof(pixel,r);case 5:return offsetof(pixel,g);case 6:return offsetof(pixel,b);case 7:return sizeof(ColorMap[0]);case 8:return EXIT_FAILURE;}return 0;}
void*teleport_gif_colormap(void){return ColorMap;}
int*teleport_gif_colors(void){return &colorsinmap;}
const char*teleport_gif_mode(int i){return i?WRTMODE:RDBMODE;}
FILE*teleport_gif_stderr(void){return stderr;}
FILE*teleport_gif_fopen(const char*a,const char*b){return fopen(a,b);}
int teleport_gif_fclose(FILE*f){return fclose(f);}
size_t teleport_gif_fread(void*out,size_t n,size_t count,FILE*f){return fread(out,n,count,f);}
int teleport_gif_strcmp(const char*a,const char*b){return strcmp(a,b);}
int teleport_gif_strncmp(const char*a,const char*b,size_t n){return strncmp(a,b,n);}
char*teleport_gif_strncpy(char*a,const char*b,size_t n){return strncpy(a,b,n);}
void teleport_gif_exit(int n){exit(n);}
int teleport_gif_format(int kind,FILE*f,char*out,const char*fmt,void*args){va_list ap;memcpy(&ap,&args,sizeof ap);return kind?vsprintf(out,fmt,ap):vfprintf(f,fmt,ap);}
boolean teleport_gif_text_open(const char*f,const char*m){return fopen_text_file(f,m);}
boolean teleport_gif_text_write(pixel(*p)[TILE_X]){return write_text_tile(p);}
int teleport_gif_text_close(void){return fclose_text_file();}
void teleport_gif_init_colormap(void){init_colormap();}
_Static_assert(CHAR_BIT==8&&sizeof(int)==4&&sizeof(void*)==8&&sizeof(va_list)==8,"actual memory64 transport");
