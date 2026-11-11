#include "config.h"
#include <emscripten/stack.h>
extern long*teleport_gif_alloc(unsigned);
extern void teleport_gif_free(void*);
#ifdef GIF_REFERENCE
#define main teleport_gif_original_main
#define alloc teleport_gif_alloc
#define free teleport_gif_free
#include UTILITY_GIFREAD_REFERENCE_SOURCE
#undef main
#undef alloc
#undef free
#else
#include "tile.h"
extern int teleport_gif_main(int,char**);
extern boolean teleport_gif_fopen_gif_file(const char*,const char*),teleport_gif_read_gif_tile(pixel(*)[TILE_X]);
extern int teleport_gif_fclose_gif_file(void);
extern void teleport_gif_read_header(FILE*),teleport_gif_DoExtension(FILE*,int);
extern int teleport_gif_GetDataBlock(FILE*,unsigned char*),teleport_gif_ReadColorMap(FILE*,int),teleport_gif_GetCode(FILE*,int,int);
#endif
static pixel pixels[TILE_Y][TILE_X];static unsigned char block[256];
int probe_prepare(void){if(!freopen("/stdout","w",stdout))return-1;if(!freopen("/stderr","w",stderr))return-2;return 0;}
int probe_open(int badmode,int missing){
#ifdef GIF_REFERENCE
return fopen_gif_file(missing?"/missing":"/input.gif",badmode?"bad":RDBMODE);
#else
return teleport_gif_fopen_gif_file(missing?"/missing":"/input.gif",badmode?"bad":RDBMODE);
#endif
}
int probe_read(void){
#ifdef GIF_REFERENCE
return read_gif_tile(pixels);
#else
return teleport_gif_read_gif_tile(pixels);
#endif
}
int probe_close(void){
#ifdef GIF_REFERENCE
return fclose_gif_file();
#else
return teleport_gif_fclose_gif_file();
#endif
}
void*probe_pixels(void){return pixels;}void*probe_palette(void){return ColorMap;}int probe_colors(void){return colorsinmap;}void*probe_block(void){return block;}
int probe_helper(int op,int value){FILE*f=fopen("/helper","r");int result=0;
#ifdef GIF_REFERENCE
switch(op){case 0:result=GetDataBlock(f,block);break;case 1:result=ReadColorMap(f,value);break;case 2:DoExtension(f,value);break;case 3:read_header(f);break;case 4:result=GetCode(f,0,TRUE);break;}
#else
switch(op){case 0:result=teleport_gif_GetDataBlock(f,block);break;case 1:result=teleport_gif_ReadColorMap(f,value);break;case 2:teleport_gif_DoExtension(f,value);break;case 3:teleport_gif_read_header(f);break;case 4:result=teleport_gif_GetCode(f,0,TRUE);break;}
#endif
fclose(f);return result;}
int probe_main(int argc){char*argv[]={"gif2txt","/input.gif","/other.txt",NULL};
#ifdef GIF_REFERENCE
return teleport_gif_original_main(argc,argv);
#else
return teleport_gif_main(argc,argv);
#endif
}
void probe_flush(void){fflush(stdout);fflush(stderr);}size_t probe_stack(void){return emscripten_stack_get_current();}

#ifndef GIF_REFERENCE
extern int teleport_gif_probe_state(int);
#endif
int probe_state(int i){
#ifdef GIF_REFERENCE
switch(i){case 0:return GifScreen.Width;case 1:return GifScreen.Height;case 2:return GifScreen.Colors;case 3:return GifScreen.ColorResolution;case 4:return GifScreen.Background;case 5:return GifScreen.AspectRatio;case 6:return GifScreen.Interlace;case 7:return Gif89.transparent;case 8:return Gif89.delayTime;case 9:return Gif89.inputFlag;case 10:return Gif89.disposal;case 11:return ZeroDataBlock;case 12:return input_code_size;}
return -999;
#else
return teleport_gif_probe_state(i);
#endif
}
