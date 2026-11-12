/* Original SDK leaves only; observers expose errno and the original FILE. */
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>
#include <emscripten/emscripten.h>
int sdk_errno(int value){int old=errno;if(value>=0)errno=value;return old;}
int sdk_constant(int i){const int v[]={EPERM,ENOSYS,EINVAL,ERANGE,ENOENT,EACCES,EBADF,F_OK,R_OK,W_OK,X_OK,F_SETFL,F_GETFL,O_RDONLY,O_WRONLY,O_RDWR,O_CREAT,O_EXCL,O_TRUNC,O_APPEND,O_CLOEXEC};return v[i];}
int sdk_fcntl(int fd,int cmd,int value){return fcntl(fd,cmd,value);}
void sdk_assert(const char *condition,const char *file,int line,const char *function){__assert_fail(condition,file,line,function);}
double sdk_now(void){return emscripten_get_now();}

FILE *sdk_standard(int i){return i==0?stdin:i==1?stdout:stderr;}
