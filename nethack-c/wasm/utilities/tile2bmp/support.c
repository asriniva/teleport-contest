#include "abi.h"
#include <stddef.h>
static struct tagBMP utility_bmp;
static pixel utility_pixels[TILE_Y][TILE_X];
static char utility_bmpname[128];
void *tb_storage(int i){switch(i){case 0:return &utility_bmp;case 1:return utility_pixels;case 2:return utility_bmpname;case 3:return ColorMap;case 4:return &colorsinmap;}return 0;}
FILE *tb_stderr(void){return stderr;}
const char *tb_mode(void){return RDTMODE;}
long tb_layout(int i){static const long v[]={sizeof(struct tagBMP),sizeof(BITMAPFILEHEADER),sizeof(BITMAPINFOHEADER),sizeof(RGBQUAD),sizeof(pixel),sizeof(void*),sizeof(int),sizeof(utility_bmpname),TILE_X,TILE_Y,RGBQUAD_COUNT,CM_RED,CM_GREEN,CM_BLUE,MAXCOLORMAPSIZE,EXIT_SUCCESS,EXIT_FAILURE,offsetof(struct tagBMP,bmfh),offsetof(struct tagBMP,bmih),offsetof(struct tagBMP,bmaColors),offsetof(struct tagBMP,packtile),offsetof(BITMAPFILEHEADER,bfType),offsetof(BITMAPFILEHEADER,bfSize),offsetof(BITMAPFILEHEADER,bfReserved1),offsetof(BITMAPFILEHEADER,bfReserved2),offsetof(BITMAPFILEHEADER,bfOffBits),offsetof(BITMAPINFOHEADER,biSize),offsetof(BITMAPINFOHEADER,biWidth),offsetof(BITMAPINFOHEADER,biHeight),offsetof(BITMAPINFOHEADER,biPlanes),offsetof(BITMAPINFOHEADER,biBitCount),offsetof(BITMAPINFOHEADER,biCompression),offsetof(BITMAPINFOHEADER,biSizeImage),offsetof(BITMAPINFOHEADER,biXPelsPerMeter),offsetof(BITMAPINFOHEADER,biYPelsPerMeter),offsetof(BITMAPINFOHEADER,biClrUsed),offsetof(BITMAPINFOHEADER,biClrImportant),offsetof(RGBQUAD,rgbBlue),offsetof(RGBQUAD,rgbGreen),offsetof(RGBQUAD,rgbRed),offsetof(RGBQUAD,rgbReserved),offsetof(pixel,r),offsetof(pixel,g),offsetof(pixel,b)};return i>=0&&i<sizeof(v)/sizeof(v[0])?v[i]:-1;}
FILE *tb_fopen(const char*p,const char*m){return fopen(p,m);}
int tb_fclose(FILE*f){return fclose(f);}
char *tb_fgets(char*p,int n,FILE*f){return fgets(p,n,f);}
size_t tb_fwrite(const void*p,size_t a,size_t b,FILE*f){return fwrite(p,a,b,f);}
int tb_print0(FILE*f,const char*s){return fprintf(f,s);}
int tb_printi(FILE*f,const char*s,int i){return fprintf(f,s,i);}
int tb_printp(FILE*f,const char*s,const char*p){return fprintf(f,s,p);}
int tb_printppi(FILE*f,const char*s,const char*a,const char*b,int c){return fprintf(f,s,a,b,c);}
int tb_printiip(FILE*f,const char*s,int a,int b,const char*c){return fprintf(f,s,a,b,c);}
int tb_printipii(FILE*f,const char*s,int a,const char*b,int c,int d){return fprintf(f,s,a,b,c,d);}
int tb_printfii(const char*s,int a,int b){return printf(s,a,b);}
int tb_printfp(const char*s,const char*p){return printf(s,p);}
int tb_fputs(const char*s,FILE*f){return fputs(s,f);}
void tb_exit(int n){exit(n);}
