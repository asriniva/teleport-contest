/* Original UNIXUNIX owner alone; observers expose actual private state. */
#include "unixunix.c"
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
int probe_unix_platform_veryold(int fd){return veryold(fd);}
int probe_unix_platform_eraseoldlocks(void){return eraseoldlocks();}
const void *probe_unix_platform_stat(void){return &buf;}
void probe_unix_platform_inputs(const char *name,int slots)
{ strcpy(svp.plname,name);gl.locknum=slots;svh.hackpid=getpid(); }
int probe_unix_platform_pid(void){return getpid();}
int probe_unix_platform_errno(int value){int previous=errno;errno=value;return previous;}
int probe_unix_platform_fcntl(int fd,int command,void *arg){return fcntl(fd,command,arg);}
int probe_unix_platform_fstat(int fd,void *out){return fstat(fd,out);}
int probe_unix_platform_stat_path(const char *path,void *out){return stat(path,out);}
