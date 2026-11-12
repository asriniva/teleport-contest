#define _GNU_SOURCE
#include <signal.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
static int called,last_sig,info_zero,context_null;
static void simple(int sig){called++;last_sig=sig;}
static void detailed(int sig,siginfo_t *info,void *context){called++;last_sig=sig;info_zero=1;for(size_t i=0;i<sizeof *info;i++)if(((unsigned char*)info)[i])info_zero=0;context_null=context==NULL;}
int probe_observe(int i){return i==0?called:i==1?last_sig:i==2?info_zero:context_null;}
void probe_reset(void){called=last_sig=info_zero=context_null=0;}
uintptr_t probe_handler(int which){return (uintptr_t)(which?(void*)detailed:(void*)simple);}
uintptr_t probe_install(int sig,int mode){if(mode==0)return (uintptr_t)signal(sig,SIG_DFL);if(mode==1)return (uintptr_t)signal(sig,SIG_IGN);if(mode==2)return (uintptr_t)signal(sig,simple);struct sigaction a={0},old={0};a.sa_sigaction=detailed;a.sa_flags=SA_SIGINFO;sigaction(sig,&a,&old);return (uintptr_t)old.sa_handler;}
int probe_errno(int set){if(set!=-999)errno=set;return errno;}
unsigned long probe_layout(int i){switch(i){case 0:return sizeof(siginfo_t);case 1:return sizeof(sigset_t);case 2:return sizeof(struct sigaction);case 3:return offsetof(struct sigaction,sa_mask);case 4:return offsetof(struct sigaction,sa_flags);case 5:return offsetof(struct sigaction,sa_restorer);case 6:return _NSIG;case 7:return SA_SIGINFO;case 8:return SA_RESTART;case 9:return SIG_BLOCK;case 10:return SIG_UNBLOCK;case 11:return SIG_SETMASK;case 12:return (uintptr_t)SIG_IGN;case 13:return (uintptr_t)SIG_ERR;case 14:return SIGKILL;case 15:return SIGSTOP;default:return sizeof(long);}}

int probe_signum(int i){const int v[]={SIGABRT,SIGALRM,SIGBUS,SIGFPE,SIGHUP,SIGILL,SIGINT,SIGKILL,SIGPIPE,SIGQUIT,SIGSEGV,SIGTERM,SIGUSR1,SIGUSR2,SIGPOLL,SIGPROF,SIGSYS,SIGTRAP,SIGVTALRM,SIGXCPU,SIGXFSZ};return v[i];}
