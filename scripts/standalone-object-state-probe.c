/* Development-only reference: original startup/RNG/serialization policies.
 * These wrappers set inputs and expose bytes; they do not implement policy. */
#include "hack.h"
#include "sfprocs.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>
__typeof__(svb) svb;
__typeof__(svd) svd;
__typeof__(go) go;
__typeof__(iflags) iflags;
__typeof__(flags) flags;
__typeof__(program_state) program_state;
__typeof__(cg) cg;
__typeof__(gu) gu;
__typeof__(svc) svc;
__typeof__(svn) svn;
__typeof__(windowprocs) windowprocs;
__typeof__(has_strong_rngseed) has_strong_rngseed;
struct you u;
winid WIN_MESSAGE;
static NHFILE file;
static int low,high;
static char diagnostics[8192];
static void message(const char *fmt,va_list ap){size_t n=strlen(diagnostics);vsnprintf(diagnostics+n,sizeof diagnostics-n,fmt,ap);}
void panic(const char *fmt,...){abort();}
void impossible(const char *fmt,...){va_list ap;va_start(ap,fmt);message(fmt,ap);va_end(ap);}
void pline(const char *fmt,...){abort();}
void raw_printf(const char *fmt,...){abort();}
void error(const char *fmt,...){abort();}
void nh_terminate(int status){abort();}
int delete_savefile(void){abort();}
int nhclose(int fd){return close(fd);}
unsigned long sys_random_seed(void){abort();}
#include STANDALONE_O_INIT_SOURCE
#include "tu-o_init-layout.h"
void probe_init(unsigned long seed){
 objects_globals_init();memset(&svb,0,sizeof svb);memset(&svd,0,sizeof svd);memset(&go,0,sizeof go);
 memset(&iflags,0,sizeof iflags);memset(&flags,0,sizeof flags);memset(&program_state,0,sizeof program_state);
 memset(&u,0,sizeof u);memset(&file,0,sizeof file);diagnostics[0]=0;
 setenv("NETHACK_RNGLOG","/rng.log",1);rng_log_init();init_isaac64(seed,(rn2));sf_init();
 svn.n_dgns=2;svd.dungeons[0].ledger_start=0;svd.dungeons[0].num_dunlevs=30;
 svd.dungeons[1].ledger_start=30;svd.dungeons[1].num_dunlevs=20;u.uz.dnum=0;u.uz.dlevel=1;
}
void probe_action(int op,int a,int b,int c){switch(op){
 case 0:init_objects();break;case 1:init_oclass_probs();break;case 2:shuffle_all();break;
 case 3:randomize_gem_colors();break;case 4:shuffle(a,b,c);break;
 case 5:obj_shuffle_range(a,&low,&high);break;case 6:oinit();break;
 case 7:setgemprobs(NULL);break;case 8:u.uz.dnum=a;u.uz.dlevel=b;break;
 case 9:objects[a].oc_prob=b;break;case 10:objects[a].oc_name_known=b;break;
 case 11:objects[a].oc_material=b;break;case 12:objects[a].oc_tough=b;break;
 }}
int probe_low(void){return low;} int probe_high(void){return high;}
void *probe_pointer(int kind){switch(kind){case 0:return objects;case 1:return svb.bases;case 2:return svd.disco;case 3:return go.oclass_prob_totals;}return NULL;}
void probe_name(int type,const char *text){if(objects[type].oc_uname)free(objects[type].oc_uname);objects[type].oc_uname=text?dupstr(text):NULL;}
const char *probe_get_name(int type){return objects[type].oc_uname;}
int probe_descr(int type,const char *text){struct obj item={0};item.otyp=type;return objdescr_is(type<0?NULL:&item,text);}
void probe_save(int mode){memset(&file,0,sizeof file);file.fd=open("/names",O_RDWR|O_CREAT|O_TRUNC,0600);if(file.fd<0)abort();file.mode=mode;file.structlevel=TRUE;file.fnidx=historical;savenames(&file);bclose(file.fd);}
void probe_restore(void){memset(&file,0,sizeof file);file.fd=open("/names",O_RDONLY);if(file.fd<0)abort();file.structlevel=TRUE;file.fnidx=historical;restnames(&file);bclose(file.fd);}
int probe_next(int n){return (rn2)(n);}
const char *probe_diagnostics(void){return diagnostics;}
