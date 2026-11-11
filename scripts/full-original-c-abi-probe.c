/* Compiled with the SAME native header as the game, without game policy. */
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <regex.h>
#include <stdint.h>
#include <signal.h>
static unsigned char buffer[128];
void *full_abi_buffer(int fill){memset(buffer,fill,sizeof buffer);return buffer;}
int full_abi_errno(int value){int old=errno;errno=value;return old;}
int full_abi_op(int op,int fd,int action){switch(op){case 0:return tcgetattr(fd,(struct termios*)buffer);case 1:return tcsetattr(fd,action,(struct termios*)buffer);case 2:return ioctl(fd,TIOCGWINSZ,buffer);default:abort();}}
int full_abi_regex(const char *pattern,const char *text,int flags){regex_t re;int s=regcomp(&re,pattern,flags);if(!s)s=regexec(&re,text,0,NULL,0);regfree(&re);return s;}
size_t full_abi_native_size(void){return sizeof(struct termios);}
intptr_t full_abi_signal(int sig,intptr_t fn){return (intptr_t)signal(sig,(void(*)(int))fn);}
