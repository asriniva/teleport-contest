#include "abi.h"
FILE *bmp_fopen(const char*p,const char*m){return fopen(p,m);}
int bmp_fclose(FILE*f){return fclose(f);}
size_t bmp_fread(void*p,size_t a,size_t b,FILE*f){return fread(p,a,b,f);}
size_t bmp_fwrite(const void*p,size_t a,size_t b,FILE*f){return fwrite(p,a,b,f);}
int bmp_fputc(int c,FILE*f){return fputc(c,f);}
long bmp_ftell(FILE*f){return ftell(f);}
int bmp_fseek(FILE*f,long o,int w){return fseek(f,o,w);}
void bmp_perror(const char*s){perror(s);}
void bmp_error0(const char*f){fprintf(stderr,f);}
void bmp_error_int(const char*f,int n){fprintf(stderr,f,n);}
void bmp_error_ptr(const char*f,const char*p){fprintf(stderr,f,p);}
void bmp_summary(const char*f,const char*p,int w,int h,int c,int n,int t){printf(f,p,w,h,c,n,t);}
long bmp_layout(int i){switch(i){
case 0:return sizeof(BMPFILEHEADER);case 1:return sizeof(BMPINFOHEADER);case 2:return sizeof(RGB);case 3:return sizeof(void*);case 4:return sizeof(long);
case 5:return offsetof(BMPFILEHEADER,bfType);case 6:return offsetof(BMPFILEHEADER,bfOffBits);
case 7:return offsetof(BMPINFOHEADER,biWidth);case 8:return offsetof(BMPINFOHEADER,biHeight);case 9:return offsetof(BMPINFOHEADER,biBitCount);case 10:return offsetof(BMPINFOHEADER,biClrUsed);
case 11:return SEEK_SET;case 12:return SEEK_END;
}return -1;}
