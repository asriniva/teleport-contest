#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <emscripten/stack.h>
#ifdef STRIPBS_REFERENCE
#define main teleport_stripbs_original_main
#include "nethack-c/upstream/util/stripbs.c"
#undef main
#else
extern int teleport_stripbs_main(int,char**);
#endif
static int output_fd;
int probe_prepare(int error_stream,int initial_errno){
 if(!freopen("/input",error_stream?"wb":"rb",stdin))return -1;
 if(!freopen("/output","wb",stdout))return -2;
 output_fd=fileno(stdout);errno=initial_errno;return 0;
}
int probe_run(void){
#ifdef STRIPBS_REFERENCE
 return teleport_stripbs_original_main(0,NULL);
#else
 return teleport_stripbs_main(0,NULL);
#endif
}
int probe_errno(void){return errno;}
int probe_eof(void){return feof(stdin);}
int probe_error(void){return ferror(stdin);}
int probe_output_closed(void){int saved=errno,result=fcntl(output_fd,F_GETFD);errno=saved;return result<0;}
long probe_stack(void){return (long)emscripten_stack_get_current();}
