/* Reference-only native ABI conversion. Algorithms stay in SDK libc/TRE.
 * Compile this file WITHOUT native-terminal.h so its calls use the SDK ABI. */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <regex.h>
#include "full-original-c-native-tables.h"
_Static_assert(sizeof(void*)==8 && sizeof(long)==8,"reference LP64");
_Static_assert(sizeof(struct termios)==ABI_WIRE_SIZE,"changed SDK termios");
typedef void (*handler_t)(int);
typedef struct {int re_magic;size_t re_nsub;const char *re_endp;void *re_g;} native_regex;
_Static_assert(sizeof(native_regex)==32,"changed native regex envelope");
struct terminal_state {int fd;unsigned char native[ABI_NATIVE_SIZE];struct termios wire;struct terminal_state *next;};
static struct terminal_state *terminals;
static handler_t virtual_handlers[32];
static struct terminal_state *terminal(int fd){
 struct terminal_state *p;for(p=terminals;p;p=p->next)if(p->fd==fd)return p;
 p=calloc(1,sizeof *p);if(!p)abort();p->fd=fd;p->next=terminals;terminals=p;return p;
}
static uint64_t load(const unsigned char *p,int n){uint64_t v=0;memcpy(&v,p,n);return v;}
static void store(unsigned char *p,int n,uint64_t v){memcpy(p,&v,n);}
static void convert(const unsigned char *source,int from,unsigned char *dest,int to){
 for(int field=0;field<4;field++){
  uint64_t input=load(source+abi_offsets[from][field],abi_width[from]);
  uint64_t value=load(dest+abi_offsets[to][field],abi_width[to]);
  for(size_t i=0;i<sizeof abi_bits/sizeof *abi_bits;i++)if(abi_bits[i].field==field){
   uint64_t a=abi_bits[i].value[from],b=abi_bits[i].value[to];value=(value&~b)|((input&a)?b:0);
  }
  for(size_t i=0;i<sizeof abi_multi/sizeof *abi_multi;i++)if(abi_multi[i].field==field){
   value&=~abi_multi[i].mask[to];
   for(int j=0;j<abi_multi[i].count;j++)if((input&abi_multi[i].mask[from])==abi_multi[i].value[j][from]){value|=abi_multi[i].value[j][to];break;}
  }
  store(dest+abi_offsets[to][field],abi_width[to],value);
 }
 for(size_t i=0;i<sizeof abi_control/sizeof *abi_control;i++)dest[abi_cc[to]+abi_control[i][to]]=source[abi_cc[from]+abi_control[i][from]];
 for(int i=0;i<2;i++){
  uint64_t speed=load(source+abi_size[from]-(2-i)*abi_speed_width[from],abi_speed_width[from]);
  for(size_t j=0;j<sizeof abi_baud/sizeof *abi_baud;j++)if(speed==abi_baud[j][from]){speed=abi_baud[j][to];break;}
  store(dest+abi_size[to]-(2-i)*abi_speed_width[to],abi_speed_width[to],speed);
 }
}
int teleport_native_tcgetattr(int fd,void *out){
 struct terminal_state *s=terminal(fd);
 /* Defined scratch input: SDK leaves c_line/padding/speeds unwritten. */
 struct termios wire={0};int status=tcgetattr(fd,&wire);
 if(!status){s->wire=wire;convert((unsigned char*)&wire,1,s->native,0);memcpy(out,s->native,sizeof s->native);}return status;
}
int teleport_native_tcsetattr(int fd,int action,const void *in){
 struct terminal_state *s=terminal(fd);struct termios wire=s->wire;convert(in,0,(unsigned char*)&wire,1);
 int status=tcsetattr(fd,action,&wire);if(!status){memcpy(s->native,in,sizeof s->native);s->wire=wire;}return status;
}
uint64_t teleport_native_cfgetospeed(const void *in){return load((const unsigned char*)in+ABI_NATIVE_SIZE-8,8);}
long teleport_native_fpathconf(int fd,int name){return fpathconf(fd,name==ABI_NATIVE_VDISABLE?ABI_WIRE_VDISABLE:name);}
int teleport_native_ioctl(int fd,unsigned long request,...){va_list ap;va_start(ap,request);void *arg=va_arg(ap,void*);va_end(ap);return ioctl(fd,request==0x40087468UL?TIOCGWINSZ:(int)request,arg);}
static const int signal_map[]={0,1,2,3,4,5,6,-1,8,9,7,11,31,13,14,15,23,19,20,18,17,21,22,29,24,25,26,27,28,-1,10,12};
handler_t teleport_native_signal(int sig,handler_t fn){
 if(sig<0||sig>=32){errno=EINVAL;return (handler_t)(intptr_t)-1;}
 if(signal_map[sig]<0){handler_t old=virtual_handlers[sig];virtual_handlers[sig]=fn;return old;}
 handler_t old=signal(signal_map[sig],fn==(handler_t)1?SIG_IGN:fn);return old==SIG_IGN?(handler_t)1:old;
}
int teleport_native_kill(int pid,int sig){
 if(sig<0||sig>=32){errno=EINVAL;return -1;}
 if(signal_map[sig]<0){handler_t fn=virtual_handlers[sig];if(pid||!fn||fn==(handler_t)(intptr_t)-1)abort();if(fn!=(handler_t)1)fn(sig);return 0;}
 return kill(pid,signal_map[sig]);
}
int teleport_native_regcomp(native_regex *out,const char *pattern,int flags){
 regex_t *re=calloc(1,sizeof *re);if(!re)return REG_ESPACE;
 memset(out,0,sizeof *out);out->re_g=re;
 int mapped=(flags&~12)|((flags&4)?8:0)|((flags&8)?4:0),status=regcomp(re,pattern,mapped);
 if(!status)out->re_nsub=re->re_nsub;else{free(re);out->re_g=NULL;}return status;
}
int teleport_native_regexec(const native_regex *in,const char *text,size_t count,regmatch_t *matches,int flags){return regexec(in->re_g,text,count,matches,flags);}
size_t teleport_native_regerror(int status,const native_regex *in,char *out,size_t size){return regerror(status,in?(const regex_t*)in->re_g:NULL,out,size);}
void teleport_native_regfree(native_regex *in){if(in->re_g){regfree(in->re_g);free(in->re_g);}memset(in,0,sizeof *in);}
/* Independent raw SDK endpoint for transport-only comparison. */
int full_sdk_regex(const char *pattern,const char *text,int flags){regex_t re;int s=regcomp(&re,pattern,flags);if(!s){s=regexec(&re,text,0,NULL,0);regfree(&re);}return s;}
intptr_t full_sdk_signal(int sig,intptr_t fn){return (intptr_t)signal(sig,(handler_t)fn);}
