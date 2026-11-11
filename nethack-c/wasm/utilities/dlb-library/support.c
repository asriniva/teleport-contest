#include "config.h"
#include "dlb.h"
#include <stddef.h>
extern unsigned FITSuint_(unsigned long long,const char*,int);
extern char *eos(char*);
static library dlb_zero_storage[4];
void *utility_library_storage(void){return dlb_zero_storage;}
unsigned utility_fits(unsigned long long n,int line){return FITSuint_(n,"readlibdir",line);}
char *utility_eos(char*p){return eos(p);}
int utility_filename_cmp(const char*a,const char*b){return FILENAME_CMP(a,b);}
int utility_fscanf_header(FILE*f,const char*fmt,long*a,long*b,long*c,long*d,long*e){return fscanf(f,fmt,a,b,c,d,e);}
int utility_fscanf_entry(FILE*f,const char*fmt,char*a,char*b,long*c){return fscanf(f,fmt,a,b,c);}
size_t utility_fread(void*p,size_t s,size_t n,FILE*f){return fread(p,s,n,f);}
FILE *utility_fopen_datafile(const char*p,const char*m,int prefix){(void)prefix;return fopen(p,m);}
int utility_fclose(FILE*f){return fclose(f);}
int utility_fseek(FILE*f,long p,int w){return fseek(f,p,w);}
char *utility_fgets(char*p,int n,FILE*f){return fgets(p,n,f);}
int utility_fgetc(FILE*f){return fgetc(f);}
long utility_ftell(FILE*f){return ftell(f);}
const char *utility_string(int n){return n?RDBMODE:DLBFILE;}
#ifdef free
#undef free
#endif
extern void free(void*);
static unsigned utility_free_calls;
void utility_trace_free(void*p){if(p)utility_free_calls++;free(p);}
unsigned utility_free_count(void){return utility_free_calls;}
long utility_layout(int n){switch(n){
case 0:return sizeof(library);
case 1:return sizeof(libdir);
case 2:return sizeof(dlb);
case 3:return sizeof(void*);
case 4:return sizeof(long);
case 5:return sizeof(boolean);
case 6:return ((char)-1)<0;
case 7:return SEEK_SET;
case 8:return SEEK_CUR;
case 9:return SEEK_END;
case 10:return EOF;
case 11:return offsetof(library,fdata);
case 12:return offsetof(library,fmark);
case 13:return offsetof(library,dir);
case 14:return offsetof(library,sspace);
case 15:return offsetof(library,nentries);
case 16:return offsetof(library,rev);
case 17:return offsetof(library,strsize);
case 18:return offsetof(libdir,fname);
case 19:return offsetof(libdir,foffset);
case 20:return offsetof(libdir,fsize);
case 21:return offsetof(libdir,handling);
case 22:return offsetof(dlb,fp);
case 23:return offsetof(dlb,lib);
case 24:return offsetof(dlb,start);
case 25:return offsetof(dlb,size);
case 26:return offsetof(dlb,mark);
}return -1;}
