/* Real configured SDK libc/device calls; no substituted syscall policies. */
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static _Alignas(16) unsigned char output[128];
void *probe_terminal_buffer(int fill){memset(output,fill,sizeof output);return output;}
int probe_terminal_errno(int value){int previous=errno;errno=value;return previous;}
int probe_terminal_op(int op,int fd,int action)
{
 switch(op){
 case 0:return isatty(fd);
 case 1:return tcgetattr(fd,(struct termios *)output);
 case 2:return tcsetattr(fd,action,(const struct termios *)output);
 case 3:return ioctl(fd,TIOCGWINSZ,output);
 default:abort();
 }
}
int probe_terminal_constant(int i)
{
 const int values[]={ENOTTY,EBADF,EINVAL,TIOCGWINSZ,TCSANOW,TCSADRAIN,TCSAFLUSH};
 if(i<0||i>=(int)(sizeof values/sizeof values[0]))abort();return values[i];
}
int probe_terminal_size(int i)
{return i==0?sizeof(struct termios):i==1?sizeof(struct winsize):sizeof output;}
