#include "config.h"
#include <emscripten/stack.h>
#include <emscripten/heap.h>
extern long*teleport_ppm_alloc(unsigned);
extern void teleport_ppm_free(void*);
#ifdef PPM_REFERENCE
#define main teleport_ppm_original_main
#define alloc teleport_ppm_alloc
#define free teleport_ppm_free
#ifndef UTILITY_PPMWRITE_REFERENCE_SOURCE
#error "Explicit absolute original reference source required"
#endif
#include UTILITY_PPMWRITE_REFERENCE_SOURCE
#undef main
#undef alloc
#undef free
#else
#include "tile.h"
extern int teleport_ppm_main(int,char**);
extern boolean teleport_ppm_open(const char*,const char*);
extern boolean teleport_ppm_write(pixel(*)[TILE_X]);
extern int teleport_ppm_close(void);
#endif
static pixel pixels[TILE_Y][TILE_X];
int probe_prepare(int colors){if(!freopen("/stdout","w",stdout))return -1;if(!freopen("/stderr","w",stderr))return -2;colorsinmainmap=colors;for(int c=0;c<3;c++)for(int i=0;i<MAXCOLORMAPSIZE;i++)MainColorMap[c][i]=(c*73+i*91)&255;return 0;}
int probe_open(int mode,int missing){
#ifdef PPM_REFERENCE
return fopen_ppm_file(missing?"/missing/out.ppm":"/out.ppm",mode?"bad":WRBMODE);
#else
return teleport_ppm_open(missing?"/missing/out.ppm":"/out.ppm",mode?"bad":WRBMODE);
#endif
}
void probe_fill(unsigned seed){for(int j=0;j<TILE_Y;j++)for(int i=0;i<TILE_X;i++){pixels[j][i].r=(seed+j*17+i*7)&255;pixels[j][i].g=(seed*3+j*31+i*11)&255;pixels[j][i].b=(seed*5+j*13+i*37)&255;}}
int probe_write(void){
#ifdef PPM_REFERENCE
return write_ppm_tile(pixels);
#else
return teleport_ppm_write(pixels);
#endif
}
int probe_close(void){
#ifdef PPM_REFERENCE
return fclose_ppm_file();
#else
return teleport_ppm_close();
#endif
}
int probe_main(int argc){char*argv[]={"txt2ppm","/other.txt","/out.ppm",NULL};
#ifdef PPM_REFERENCE
return teleport_ppm_original_main(argc,argv);
#else
return teleport_ppm_main(argc,argv);
#endif
}
size_t probe_stack(void){return emscripten_stack_get_current();}

void probe_flush(void){fflush(stdout);fflush(stderr);}

int probe_grow(void){return emscripten_resize_heap(emscripten_get_heap_size()+65536);}
