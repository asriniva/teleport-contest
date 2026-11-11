#include "config.h"
#include "tile.h"
static char utility_pixels[TILE_Y][TILE_X], utility_comment[BUFSZ];
void *thin_storage(int i){return i ? (void*)utility_comment : (void*)utility_pixels;}
long thin_layout(int i){switch(i){case 0:return TILE_X;case 1:return TILE_Y;case 2:return BUFSZ;case 3:return sizeof(void*);case 4:return sizeof(int);case 5:return EXIT_SUCCESS;}return -1;}
const char *thin_mode(int i){return i?WRTMODE:RDTMODE;}
FILE *thin_stderr(void){return stderr;}
FILE *thin_fopen(const char*p,const char*m){return fopen(p,m);}
int thin_fclose(FILE*f){return fclose(f);}
int thin_scan4(FILE*f,const char*s,void*a,void*b,void*c,void*d){return fscanf(f,s,a,b,c,d);}
int thin_scan3(FILE*f,const char*s,void*a,void*b,void*c){return fscanf(f,s,a,b,c);}
int thin_scan1(FILE*f,const char*s,void*a){return fscanf(f,s,a);}
int thin_print0(FILE*f,const char*s){return fprintf(f,s);}
int thin_printp(FILE*f,const char*s,const char*p){return fprintf(f,s,p);}
int thin_print4(FILE*f,const char*s,int a,int b,int c,int d){return fprintf(f,s,a,b,c,d);}
int thin_printf1(const char*s,int a){return printf(s,a);}
int thin_printf2(const char*s,int a,const char*b){return printf(s,a,b);}
int thin_sprintf(char*out,const char*s,int a,const char*b){return sprintf(out,s,a,b);}
int thin_fputc(int c,FILE*f){return fputc(c,f);}
void thin_exit(int n){exit(n);}
