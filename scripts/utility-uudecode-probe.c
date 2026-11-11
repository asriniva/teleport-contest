#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <emscripten/stack.h>
#ifdef UUDECODE_REFERENCE
#define main teleport_uudecode_original_main
#include "nethack-c/upstream/sys/share/uudecode.c"
#undef main
#else
extern int teleport_uudecode_main(int,char**);
extern void teleport_uudecode_decode(FILE*,FILE*);
extern void teleport_uudecode_outdec(char*,FILE*,int);
extern char*teleport_uudecode_index(char*,int);
#endif
static char *args[]={"uudecode","/input",NULL};
int probe_prepare(void){if(!freopen("/input","r",stdin))return -1;if(!freopen("/stdout","w",stdout))return -2;if(!freopen("/stderr","w",stderr))return -3;return 0;}
int probe_main(int argc,int missing){char*argv[4]={"uudecode",missing?"/missing":"/input","extra",NULL};
#ifdef UUDECODE_REFERENCE
return teleport_uudecode_original_main(argc,argv);
#else
return teleport_uudecode_main(argc,argv);
#endif
}
void probe_decode(void){FILE*out=fopen("/decoded","w");
#ifdef UUDECODE_REFERENCE
decode(stdin,out);
#else
teleport_uudecode_decode(stdin,out);
#endif
fclose(out);}
void probe_outdec(int n){char p[4];FILE*out=fopen("/decoded","w");fread(p,1,4,stdin);
#ifdef UUDECODE_REFERENCE
outdec(p,out,n);
#else
teleport_uudecode_outdec(p,out,n);
#endif
fclose(out);}
int probe_index(int c){char buf[256];fgets(buf,sizeof buf,stdin);char*p;
#ifdef UUDECODE_REFERENCE
p=index(buf,c);
#else
p=teleport_uudecode_index(buf,c);
#endif
return p?(int)(p-buf):-1;}
int probe_mode(const char*path){struct stat st;return stat(path,&st)?-1:st.st_mode&07777;}
int probe_errno(void){return errno;}
size_t probe_stack(void){return emscripten_stack_get_current();}
