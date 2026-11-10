/* Native END fields/header/varargs/dependency ABI only. No endgame algorithms. */
#include "hack.h"
#include "wintty.h"
#include "dlb.h"
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
const void*teleport_end_global(int i){switch(i){case 0:return &iflags;case 1:return &flags;case 2:return &windowprocs;case 3:return &WIN_MESSAGE;case 4:return &gm;case 5:return &u;case 6:return &svd;case 7:return &ynchars;case 8:return &ynqchars;case 9:return &soundprocs;case 10:return &program_state;case 11:return &mons;case 12:return &svk;case 13:return &gu;case 14:return &svm;case 15:return &gb;case 16:return &sysopt;case 17:return &disclosure_options;case 18:return &gi;case 19:return &gn;case 20:return &svc;case 21:return &disp;case 22:return &gy;case 23:return &ga;case 24:return &gg;case 25:return &gt;case 26:return &gk;case 27:return &uchain;case 28:return &obj_descr;case 29:return &objects;case 30:return &gd;case 31:return &gh;case 32:return &uamul;case 33:return &urealtime;case 34:return &svl;case 35:return &svp;case 36:return &WIN_INVEN;case 37:return &WIN_MAP;case 38:return &WIN_STATUS;case 39:return &gv;default:return 0;}}
int teleport_end_bit(int kind,const void*p){switch(kind){case 0:return((const struct you*)p)->uinvulnerable;case 1:return((const struct you*)p)->uswallow;case 2:return((const struct you*)p)->mfemale;case 3:return((const struct monst*)p)->ispriest;case 4:return((const struct monst*)p)->minvis;case 5:return((const struct monst*)p)->isshk;case 6:return((const struct monst*)p)->female;case 7:return((const struct monst*)p)->isminion;case 8:return((const struct obj*)p)->known;case 9:return((const struct obj*)p)->dknown;case 10:return((const struct obj*)p)->bknown;case 11:return((const struct obj*)p)->rknown;case 12:return((const struct obj*)p)->cknown;case 13:return((const struct obj*)p)->lknown;case 14:return((const struct rm*)p)->flags;case 15:return((const struct u_have*)p)->amulet;default:abort();}}
void teleport_end_set_bit(int kind,void*p,unsigned n){switch(kind){case 0:((struct you*)p)->uinvulnerable=n;return;case 1:((struct you*)p)->uswallow=n;return;case 2:((struct you*)p)->mfemale=n;return;case 3:((struct monst*)p)->ispriest=n;return;case 4:((struct monst*)p)->minvis=n;return;case 5:((struct monst*)p)->isshk=n;return;case 6:((struct monst*)p)->female=n;return;case 7:((struct monst*)p)->isminion=n;return;case 8:((struct obj*)p)->known=n;return;case 9:((struct obj*)p)->dknown=n;return;case 10:((struct obj*)p)->bknown=n;return;case 11:((struct obj*)p)->rknown=n;return;case 12:((struct obj*)p)->cknown=n;return;case 13:((struct obj*)p)->lknown=n;return;case 14:((struct rm*)p)->flags=n;return;case 15:((struct u_have*)p)->amulet=n;return;default:abort();}}

const char*teleport_end_header_string(int i){return i==0?WIZARD_NAME:i==1?plur(1):plur(2);}
void teleport_end_free(void*p){free(p);}
void teleport_end_exit(int status){nethack_exit(status);}
void teleport_end_abort(void){abort();}
int teleport_end_vsnprintf(char*out,size_t cap,const char*fmt,void*args){return vsnprintf(out,cap,fmt,(va_list)args);}
int teleport_end_scan(const char*s,const char*fmt,unsigned*id,char*c){return sscanf(s,fmt,id,c);}
winid teleport_end_create_window(int type){return create_nhwindow(type);}
void teleport_end_clear_window(winid w){clear_nhwindow(w);}
void teleport_end_display_window(winid w,boolean b){display_nhwindow(w,b);}
void teleport_end_destroy_window(winid w){destroy_nhwindow(w);}
void teleport_end_exit_windows(const char*s){exit_nhwindows(s);}
void teleport_end_putstr(winid w,int attr,const char*s){putstr(w,attr,s);}
void teleport_end_raw_print(const char*s){raw_print(s);}
void teleport_end_mark_synch(void){mark_synch();}
void teleport_end_wait_synch(void){wait_synch();}
void teleport_end_outrip(winid w,int how,time_t when){outrip(w,how,when);}
void teleport_end_sound_exit(const char*s){(*soundprocs.sound_exit_nhsound)(s);}
void teleport_end_cmdq_add_ec(int q){cmdq_add_ec(q,wiz_makemap);}
#ifdef TELEPORT_REFERENCE_TU
#define teleport_end_private_done_intr done_intr
#define teleport_end_private_done_hangup done_hangup
#else
extern void teleport_end_private_done_intr(int),teleport_end_private_done_hangup(int);
#endif
static void teleport_end_intr_callback(int n){teleport_end_private_done_intr(n);}
static void teleport_end_hangup_callback(int n){teleport_end_private_done_hangup(n);}
void teleport_end_signal(int sig,int which){signal(sig,which==-1?SIG_IGN:which==0?done1:which==1?teleport_end_intr_callback:teleport_end_hangup_callback);}
void teleport_end_hangup(int which){sethanguphandler(which==-1?SIG_IGN:teleport_end_hangup_callback);}
int teleport_end_rng(int kind,int n,int count,int line,int caller){static const char*const callers[]={"fuzzer_savelife","really_done"};if(rng_log_enabled())rng_log_set_caller("end.c",line,callers[caller]);return kind?(d)(n,count):(rn2)(n);}
unsigned teleport_end_Strlen(const char*s,int line){return Strlen_(s,"really_done",line);}

#define END_OUTPUT(...) do {switch(kind){case 0:sprintf((char*)target,fmt,##__VA_ARGS__);break;case 1:You(fmt,##__VA_ARGS__);break;case 2:Your(fmt,##__VA_ARGS__);break;case 3:You_feel(fmt,##__VA_ARGS__);break;case 4:pline(fmt,##__VA_ARGS__);break;case 5:pline_The(fmt,##__VA_ARGS__);break;case 6:raw_printf(fmt,##__VA_ARGS__);break;case 7:impossible(fmt,##__VA_ARGS__);break;case 8:livelog_printf(((long)target),fmt,##__VA_ARGS__);break;}}while(0)
void teleport_end_output(int kind,int shape,void*target,const char*fmt,const uint64_t*args){switch(shape){
case 0:END_OUTPUT();break;
case 1:END_OUTPUT(((const char*)(uintptr_t)args[0]));break;
case 2:END_OUTPUT(((const char*)(uintptr_t)args[0]),((const char*)(uintptr_t)args[1]));break;
case 3:END_OUTPUT(((int)args[0]),((int)args[1]));break;
case 4:END_OUTPUT(((int)args[0]));break;
case 5:END_OUTPUT(((const char*)(uintptr_t)args[0]),((const char*)(uintptr_t)args[1]),((long)args[2]),((const char*)(uintptr_t)args[3]),((long)args[4]));break;
case 6:END_OUTPUT(((const char*)(uintptr_t)args[0]),((const char*)(uintptr_t)args[1]),((const char*)(uintptr_t)args[2]));break;
case 7:END_OUTPUT(((const char*)(uintptr_t)args[0]),((long)args[1]),((const char*)(uintptr_t)args[2]));break;
case 8:END_OUTPUT(((long)args[0]),((const char*)(uintptr_t)args[1]),((long)args[2]),((const char*)(uintptr_t)args[3]));break;
case 9:END_OUTPUT(((long)args[0]),((const char*)(uintptr_t)args[1]));break;
case 10:END_OUTPUT(((int)args[0]),((int)args[1]),((const char*)(uintptr_t)args[2]),((const char*)(uintptr_t)args[3]));break;
}}
#undef END_OUTPUT
static char teleport_end_literals[2682];
void*teleport_end_literal_storage(void){return teleport_end_literals;}
size_t teleport_end_literal_capacity(void){return sizeof teleport_end_literals;}
