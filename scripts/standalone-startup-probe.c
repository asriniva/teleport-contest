/* Full source DECL initializers and startup owners, with explicit external
 * abort boundaries supplied by the development builder. */
#include "hack.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
__typeof__(windowprocs) windowprocs;
win_request_info zerowri={0};
static char diagnostics[8192];
void panic(const char *fmt,...){fputs(fmt,stderr);abort();}
void impossible(const char *fmt,...){size_t n=strlen(diagnostics);va_list ap;va_start(ap,fmt);vsnprintf(diagnostics+n,sizeof diagnostics-n,fmt,ap);va_end(ap);}
void pline(const char *fmt,...){abort();}
void raw_printf(const char *fmt,...){abort();}
void error(const char *fmt,...){abort();}
void nh_terminate(int status){abort();}
void probe_startup_init(unsigned long seed){
 program_state_init();decl_globals_init();objects_globals_init();monst_globals_init();sys_early_init();
 setenv("NETHACK_RNGLOG","/rng.log",1);rng_log_init();init_isaac64(seed,(rn2));sf_init();
}
void probe_startup_role_config(int r,int race,int g,int a,const char*name){
 flags.initrole=r;flags.initrace=race;flags.initgend=g;flags.initalign=a;flags.female=0;flags.pantheon=-1;
 memset(svp.plname,0,sizeof svp.plname);memset(svp.pl_character,0,sizeof svp.pl_character);strncpy(svp.plname,name,sizeof svp.plname-1);
}
void probe_startup_role(void){role_init();}
void probe_startup_newgame(void){newgame();}
const volatile void *probe_startup_global(int op){switch(op){case 0:return &flags;case 1:return &gu;case 2:return &svq;case 3:return &svp;case 4:return &gr;case 5:return &gp;case 6:return mons;case 7:return objects;case 8:return &a11y;case 9:return &svc;case 10:return roles;case 11:return races;case 12:return genders;case 13:return aligns;case 14:return &svd;case 15:return &svn;case 16:return &svm;case 17:return &disp;case 18:return &sysopt;case 19:return &program_state;case 20:return &iflags;}return NULL;}
const char *probe_startup_diagnostics(void){return diagnostics;}
