/* Real WINDOWS/DISPLAY owners, with source-private hero initialization data. */
#include "standalone-hero-startup-probe.c"
#include <signal.h>
#include <errno.h>
extern glyph_map glyphmap[MAX_GLYPH];
void probe_display_reset(int trigger){reset_glyphmap((enum glyphmap_change_triggers)trigger);}
const volatile void *probe_display_global(int op){switch(op){case 0:return glyphmap;case 1:return &gg;case 2:return &windowprocs;case 3:return &gc;case 4:return &gs;case 5:return &go;}return NULL;}
unsigned long probe_display_layout(int op){const unsigned long sizes[]={sizeof(struct sigaction),offsetof(struct sigaction,sa_handler),offsetof(struct sigaction,sa_mask),sizeof(sigset_t),offsetof(struct sigaction,sa_flags),offsetof(struct sigaction,sa_restorer),_NSIG,SA_RESTART,EINVAL,MAX_GLYPH,sizeof(glyph_map),SIGINT};return sizes[op];}
void probe_display_config(int use,int named,unsigned long caps,unsigned mask,int graphics,int handling,int nocolor){iflags.use_color=use;windowprocs.name=named?"standalone-test":NULL;windowprocs.wincap=caps;for(int i=0;i<16;i++)windowprocs.has_color[i]=!!(mask&(1U<<i));gc.currentgraphics=graphics;gs.symset[graphics].handling=handling;gs.symset[graphics].nocolor=nocolor;}
static int signal_seen;
static void signal_first(int sig){signal_seen=100+sig;}
static void signal_second(int sig){signal_seen=200+sig;}
void *probe_signal_pointer(int i){return i==0?(void*)SIG_DFL:i==1?(void*)SIG_IGN:i==2?(void*)signal_first:i==3?(void*)signal_second:(void*)done1;}
void *probe_signal_set(int sig,int choice){return (void*)signal(sig,(void(*)(int))probe_signal_pointer(choice));}
void probe_signal_reset(void){signal_seen=0;errno=0;}
int probe_signal_seen(void){return signal_seen;}
int probe_signal_errno(void){return errno;}

extern struct sigaction __sig_actions[_NSIG];
const void *probe_signal_global(void){return __sig_actions;}
int probe_signal_set_token(int sig,int choice){void *p=probe_signal_set(sig,choice);if(p==(void*)SIG_ERR)return -1;for(int i=0;i<5;i++)if(p==probe_signal_pointer(i))return i;return -2;}
