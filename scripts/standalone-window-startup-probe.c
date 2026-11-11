/* Original startup fixture; only input and observation helpers are added. */
#include "standalone-level-contents-probe.c"
#include <stdio_ext.h>
#include <termios.h>
#include <sys/ioctl.h>
void probe_window_select(const char *name){choose_windows(name);}
void probe_window_init(void){int argc=1;char name[]="nethack";char *argv[]={name,NULL};(*windowprocs.win_init_nhwindows)(&argc,argv);}
void *probe_window_table(void){return (void*)&windowprocs;}
static FILE *probe_buffer_file;
static unsigned char *probe_buffer_bytes;
void *probe_buffer_open(int mode,unsigned long size,int use_setbuf){
 probe_buffer_file=fopen("/stdio-buffer","w+");if(!probe_buffer_file)abort();
 probe_buffer_bytes=malloc(size+32);if(!probe_buffer_bytes)abort();memset(probe_buffer_bytes,0xa5,size+32);
 if(use_setbuf)setbuf(probe_buffer_file,(char*)probe_buffer_bytes+16);else if(setvbuf(probe_buffer_file,(char*)probe_buffer_bytes+16,mode,size))abort();
 return probe_buffer_bytes;
}
unsigned long probe_buffer_capacity(void){return __fbufsize(probe_buffer_file);}
unsigned long probe_buffer_pending(void){return __fpending(probe_buffer_file);}
int probe_buffer_put(int c){return fputc(c,probe_buffer_file);}
unsigned long probe_buffer_write(const void *p,unsigned long n){return fwrite(p,1,n,probe_buffer_file);}
int probe_buffer_flush(void){return fflush(probe_buffer_file);}
void probe_buffer_close(void){if(fclose(probe_buffer_file))abort();free(probe_buffer_bytes);}
/* Observe the underlying SDK independently of the game's compatibility ABI. */
#undef tcgetattr
#undef tcsetattr
#undef cfgetospeed
#undef fpathconf
#undef ioctl
int probe_tty_attr(int fd,void *p){return tcgetattr(fd,p);}
int probe_tty_setattr(int fd,int action,void *p){return tcsetattr(fd,action,p);}
int probe_tty_winsize(int fd,void *p){return ioctl(fd,0x5413,p);}

#include <errno.h>
extern struct termios inittyb,curttyb,termio;
extern short ospeed;
extern char erase_char,kill_char,intr_char;
const void *probe_unix_terminal_storage(int i){switch(i){case 0:return &inittyb;case 1:return &curttyb;case 2:return &termio;case 3:return &ospeed;case 4:return &erase_char;case 5:return &kill_char;case 6:return &intr_char;}return NULL;}
unsigned long probe_tty_speed(const void *p){return cfgetospeed(p);}
long probe_tty_pathconf(int fd,int name){return fpathconf(fd,name);}
int probe_tty_errno(int value){int old=errno;errno=value;return old;}
