#include "config.h"
#include "tile.h"
#include <stddef.h>
#include <limits.h>
void*teleport_ppm_literal_alloc(size_t n){return malloc(n);}
size_t teleport_ppm_metadata(int i){switch(i){case 0:return TILE_X;case 1:return TILE_Y;case 2:return sizeof(pixel);case 3:return sizeof(void*);case 4:return offsetof(pixel,r);case 5:return offsetof(pixel,g);case 6:return offsetof(pixel,b);case 7:return CM_RED;case 8:return CM_GREEN;case 9:return CM_BLUE;case 10:return MAXCOLORMAPSIZE;case 11:return (char)-1<0;case 12:return EXIT_SUCCESS;case 13:return EXIT_FAILURE;}return 0;}
const char*teleport_ppm_mode(int i){return i?RDTMODE:WRBMODE;}
FILE*teleport_ppm_stderr(void){return stderr;}
int teleport_ppm_colors(void){return colorsinmainmap;}
void*teleport_ppm_colormap(void){return MainColorMap;}
FILE*teleport_ppm_fopen(const char*f,const char*m){return fopen(f,m);}
int teleport_ppm_fputc(int c,FILE*f){return fputc(c,f);}
int teleport_ppm_fclose(FILE*f){return fclose(f);}
void teleport_ppm_rewind(FILE*f){rewind(f);}
int teleport_ppm_strcmp(const char*a,const char*b){return strcmp(a,b);}
void teleport_ppm_exit(int n){exit(n);}
int teleport_ppm_header(FILE*f,const char*fmt,int w,int h){return fprintf(f,fmt,w,h);}
int teleport_ppm_message(FILE*f,const char*fmt,const char*a){return fprintf(f,fmt,a);}
boolean teleport_ppm_text_open(const char*f,const char*m){return fopen_text_file(f,m);}
boolean teleport_ppm_text_read(pixel(*p)[TILE_X]){return read_text_tile(p);}
int teleport_ppm_text_close(void){return fclose_text_file();}
void teleport_ppm_init_colormap(void){init_colormap();}
_Static_assert(CHAR_BIT==8 && sizeof(void*)==8 && sizeof(unsigned)==4 && sizeof(boolean)==1,"actual utility ABI");
_Static_assert(sizeof(pixval)==1 && (pixval)-1>0,"unsigned byte pixel components");
