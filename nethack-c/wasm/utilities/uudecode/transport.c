#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <sys/stat.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
_Static_assert(sizeof(void*)==8 && sizeof(size_t)==8 && CHAR_BIT==8 && sizeof(unsigned)==4,"actual memory64 utility ABI");
FILE* teleport_uudecode_stdin(void){return stdin;}
FILE* teleport_uudecode_stderr(void){return stderr;}
FILE* teleport_uudecode_fopen(const char*a,const char*b){return fopen(a,b);}
void teleport_uudecode_perror(const char*a){perror(a);}
void teleport_uudecode_exit(int n){exit(n);}
int teleport_uudecode_printf(const char*f){return printf(f);}
int teleport_uudecode_fprintf(FILE*out,const char*f,const char*a){return fprintf(out,f,a);}
char*teleport_uudecode_fgets(char*out,int n,FILE*f){return fgets(out,n,f);}
int teleport_uudecode_strncmp(const char*a,const char*b,size_t n){return strncmp(a,b,n);}
int teleport_uudecode_strcmp(const char*a,const char*b){return strcmp(a,b);}
size_t teleport_uudecode_strlen(const char*a){return strlen(a);}
int teleport_uudecode_sscanf(const char*a,const char*f,unsigned*mode,char*dest){return sscanf(a,f,mode,dest);}
char*teleport_uudecode_strchr(const char*a,int c){return strchr(a,c);}
struct passwd*teleport_uudecode_getpwnam(const char*a){return getpwnam(a);}
char*teleport_uudecode_pw_dir(struct passwd*p){return p->pw_dir;}
char*teleport_uudecode_strcpy(char*a,const char*b){return strcpy(a,b);}
char*teleport_uudecode_strcat(char*a,const char*b){return strcat(a,b);}
int teleport_uudecode_chmod(const char*a,unsigned mode){return chmod(a,mode);}
int teleport_uudecode_putc(int ch,FILE*f){return putc(ch,f);}
int teleport_uudecode_charsigned(void){return (char)-1<0;}
