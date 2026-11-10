/* PLINE typed ABI/global/dependency calls only; no messaging algorithms. */
#include "hack.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "pline-source-data.h"
void *teleport_pline_global(int field) {
 switch(field){
 case 0: return (void *)&gs.saved_pline_index;
 case 1: return (void *)&gs.saved_plines;
 case 2: return (void *)&iflags.debug_prevent_pline;
 case 3: return (void *)&gp.pline_flags;
 case 4: return (void *)&windowprocs.wincap2;
 case 5: return (void *)&WIN_MESSAGE;
 case 6: return (void *)&a11y.msg_loc;
 case 7: return (void *)&u.ux;
 case 8: return (void *)&u.uy;
 case 9: return (void *)&program_state.done_hup;
 case 10: return (void *)&program_state.wizkit_wishing;
 case 11: return (void *)&a11y.accessiblemsg;
 case 12: return (void *)&iflags.getpos_coords;
 case 13: return (void *)&iflags.window_inited;
 case 14: return (void *)&iflags.last_msg;
 case 15: return (void *)&gp.prevmsg;
 case 16: return (void *)&gv.vision_full_recalc;
 case 17: return (void *)&gy.you_buf;
 case 18: return (void *)&gy.you_buf_siz;
 case 19: return (void *)&gg.gamelog;
 case 20: return (void *)&svm.moves;
 case 21: return (void *)&program_state.beyond_savefile_load;
 case 22: return (void *)&ge.early_raw_messages;
 case 23: return (void *)&program_state.in_impossible;
 case 24: return (void *)&iflags.debug_fuzzer;
 case 25: return (void *)&program_state.in_sanity_check;
 case 26: return (void *)&program_state.something_worth_saving;
 case 27: return (void *)&sysopt.support;
 case 28: return (void *)&sysopt.crashreporturl;
 case 29: return (void *)&sysopt.msghandler;
 case 30: return (void *)&flags.acoustics;
 case 31: return (void *)&gy.youmonst;
 case 32: return (void *)&ynchars;
 default: abort();}
}
int teleport_pline_vsnprintf(char *out,size_t size,const char *format,void *args) {
    va_list ap=(va_list)args;
    return vsnprintf(out,size,format,ap);
}
int teleport_pline_format3(char *out,size_t size,const char *format,const char *a,const char *b,int c) { return snprintf(out,size,format,a,b,c); }
void teleport_pline_putstr(int window,int attr,const char *text) { putstr(window,attr,text); }
void teleport_pline_raw(const char *text) { raw_print(text); }
void teleport_pline_display(int window,boolean block) { display_nhwindow(window,block); }
void teleport_pline_panic(int kind,const char *text,int count) {
    switch(kind){case 0:panic("pline attempting to print %d characters!",count);break;case 1:panic("impossible called impossible");break;case 2:panic("%s",text);break;default:abort();}
}
int teleport_pline_hero_flag(int kind) {switch(kind){case 0:return !!Unaware;case 1:return !!Deaf;case 2:return !!Underwater;case 3:return !!Blind;default:abort();}}
FILE *teleport_pline_stderr(void) {return stderr;}
void teleport_pline_handler_error(FILE *stream,const char *format,const char *handler) {(void)fprintf(stream,format,handler);}
int teleport_pline_fork(void) {return fork();}
int teleport_pline_waitpid(int pid,int *status,int flags) {return waitpid(pid,status,flags);}
unsigned teleport_pline_getgid(void) {return getgid();}
unsigned teleport_pline_getuid(void) {return getuid();}
int teleport_pline_setgid(unsigned id) {return setgid(id);}
int teleport_pline_setuid(unsigned id) {return setuid(id);}
int teleport_pline_execv(const char *path,char *const *args) {return execv(path,args);}
void teleport_pline_perror(const char *text) {perror(text);}
static char teleport_pline_literals[TELEPORT_PLINE_LITERAL_CAPACITY];
void *teleport_pline_literal_storage(void) {return teleport_pline_literals;}
size_t teleport_pline_literal_capacity(void) {return sizeof teleport_pline_literals;}
_Static_assert(sizeof(va_list)==sizeof(void *),"Review PLINE variadic ABI");

void teleport_pline_free(void *value) {free(value);}
const char *teleport_pline_devteam_email(void) {return DEVTEAM_EMAIL;}
