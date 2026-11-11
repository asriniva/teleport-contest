/* TERMCAP native storage, exact fields and typed dependency transport only. */
#include "hack.h"
#include "wintty.h"
#include "tcap.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "termcap-source-data.h"
_Static_assert(sizeof(void*)==8&&sizeof(long)==8&&sizeof(int)==4,"TERMCAP memory64 ABI");
_Static_assert(sizeof(boolean)==1&&(boolean)-1<0,"TERMCAP signed boolean");
extern boolean HE_resets_AS;
extern void (*decgraphics_mode_callback)(void);
extern void (*utf8graphics_mode_callback)(void);
extern void teleport_capture(const char * a0,int a1,int a2,int a3);
void teleport_termcap_capture(const char *screen,int x,int y,int animation){teleport_capture(screen,x,y,animation);}
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_termcap_capture),void (*)(const char *,int,int,int)),"TERMCAP capture transport");
#ifndef TELEPORT_REFERENCE_TU
struct tc_lcl_data tc_lcl_data;
static char * teleport_termcap_nh_VI;
static char * teleport_termcap_nh_VE;
static char * teleport_termcap_nh_Ic;
static char * teleport_termcap_HO;
static char * teleport_termcap_CL;
static char * teleport_termcap_CE;
static char * teleport_termcap_UP;
static char * teleport_termcap_XD;
static char * teleport_termcap_BC;
static char * teleport_termcap_SO;
static char * teleport_termcap_SE;
static char * teleport_termcap_TI;
static char * teleport_termcap_TE;
static char * teleport_termcap_VS;
static char * teleport_termcap_VE;
static char * teleport_termcap_ME;
static char * teleport_termcap_MR;
static char * teleport_termcap_MB;
static char * teleport_termcap_MH;
static char * teleport_termcap_MD;
static char * teleport_termcap_ZH;
static char * teleport_termcap_ZR;
signed char dynamic_HIHE;
static int teleport_termcap_SG;
static char teleport_termcap_PC;
static char teleport_termcap_tbuf[512];
char * hilites[16];
static char * teleport_termcap_KS;
static char * teleport_termcap_KE;
static char teleport_termcap_nullstr[1];
static char teleport_termcap_tty_standout_on[16];
static char teleport_termcap_tty_standout_off[16];
static int teleport_termcap_nomux_seq;
int nomux_anim_id;
nomux_cell nomux_buf[24][80];
static unsigned char teleport_termcap_nomux_fg_cur;
static unsigned char teleport_termcap_nomux_attr_cur;
static unsigned char teleport_termcap_nomux_decgfx_cur;
static char teleport_termcap_nomux_out[6144];
static int teleport_termcap_nomux_raw_active;
static int teleport_termcap_nomux_raw_row;
static int teleport_termcap_nomux_raw_col;
static short teleport_termcap_tmspc10[15];
struct teleport_termcap_ti_map_entry ti_map[6];
static char teleport_termcap_nilstring[1];
static char teleport_termcap_nulstr[1];
#endif
void*teleport_termcap_global(int i){switch(i){
#ifdef TELEPORT_REFERENCE_TU
case 0:return(void*)&tbuf;
#else
case 0:return(void*)&teleport_termcap_tbuf;
#endif
case 1:return(void*)&flags;
#ifdef TELEPORT_REFERENCE_TU
case 2:return(void*)&PC;
#else
case 2:return(void*)&teleport_termcap_PC;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 3:return(void*)&BC;
#else
case 3:return(void*)&teleport_termcap_BC;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 4:return(void*)&HO;
#else
case 4:return(void*)&teleport_termcap_HO;
#endif
case 5:return(void*)&gt;
case 6:return(void*)&tc_lcl_data;
#ifdef TELEPORT_REFERENCE_TU
case 7:return(void*)&CE;
#else
case 7:return(void*)&teleport_termcap_CE;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 8:return(void*)&UP;
#else
case 8:return(void*)&teleport_termcap_UP;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 9:return(void*)&XD;
#else
case 9:return(void*)&teleport_termcap_XD;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 10:return(void*)&SO;
#else
case 10:return(void*)&teleport_termcap_SO;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 11:return(void*)&SE;
#else
case 11:return(void*)&teleport_termcap_SE;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 12:return(void*)&ZH;
#else
case 12:return(void*)&teleport_termcap_ZH;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 13:return(void*)&ZR;
#else
case 13:return(void*)&teleport_termcap_ZR;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 14:return(void*)&SG;
#else
case 14:return(void*)&teleport_termcap_SG;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 15:return(void*)&nullstr;
#else
case 15:return(void*)&teleport_termcap_nullstr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 16:return(void*)&TI;
#else
case 16:return(void*)&teleport_termcap_TI;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 17:return(void*)&TE;
#else
case 17:return(void*)&teleport_termcap_TE;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 18:return(void*)&VS;
#else
case 18:return(void*)&teleport_termcap_VS;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 19:return(void*)&VE;
#else
case 19:return(void*)&teleport_termcap_VE;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 20:return(void*)&KS;
#else
case 20:return(void*)&teleport_termcap_KS;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 21:return(void*)&KE;
#else
case 21:return(void*)&teleport_termcap_KE;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 22:return(void*)&MR;
#else
case 22:return(void*)&teleport_termcap_MR;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 23:return(void*)&MB;
#else
case 23:return(void*)&teleport_termcap_MB;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 24:return(void*)&MD;
#else
case 24:return(void*)&teleport_termcap_MD;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 25:return(void*)&MH;
#else
case 25:return(void*)&teleport_termcap_MH;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 26:return(void*)&ME;
#else
case 26:return(void*)&teleport_termcap_ME;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 27:return(void*)&nh_VI;
#else
case 27:return(void*)&teleport_termcap_nh_VI;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 28:return(void*)&nh_VE;
#else
case 28:return(void*)&teleport_termcap_nh_VE;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 29:return(void*)&nh_Ic;
#else
case 29:return(void*)&teleport_termcap_nh_Ic;
#endif
case 30:return(void*)&dynamic_HIHE;
#ifdef TELEPORT_REFERENCE_TU
case 31:return(void*)&CL;
#else
case 31:return(void*)&teleport_termcap_CL;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 32:return(void*)&tty_standout_on;
#else
case 32:return(void*)&teleport_termcap_tty_standout_on;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 33:return(void*)&tty_standout_off;
#else
case 33:return(void*)&teleport_termcap_tty_standout_off;
#endif
case 34:return(void*)&gs;
case 35:return(void*)&gc;
case 36:return(void*)&HE_resets_AS;
case 37:return(void*)&decgraphics_mode_callback;
case 38:return(void*)&utf8graphics_mode_callback;
case 39:return(void*)&ttyDisplay;
case 40:return(void*)&BASE_WINDOW;
case 41:return(void*)&stdout;
#ifdef TELEPORT_REFERENCE_TU
case 42:return(void*)&nomux_seq;
#else
case 42:return(void*)&teleport_termcap_nomux_seq;
#endif
case 43:return(void*)&nomux_anim_id;
case 44:return(void*)&nomux_buf;
#ifdef TELEPORT_REFERENCE_TU
case 45:return(void*)&nomux_fg_cur;
#else
case 45:return(void*)&teleport_termcap_nomux_fg_cur;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 46:return(void*)&nomux_attr_cur;
#else
case 46:return(void*)&teleport_termcap_nomux_attr_cur;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 47:return(void*)&nomux_decgfx_cur;
#else
case 47:return(void*)&teleport_termcap_nomux_decgfx_cur;
#endif
case 48:return(void*)&iflags;
#ifdef TELEPORT_REFERENCE_TU
case 49:return(void*)&nomux_out;
#else
case 49:return(void*)&teleport_termcap_nomux_out;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 50:return(void*)&nomux_raw_active;
#else
case 50:return(void*)&teleport_termcap_nomux_raw_active;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 51:return(void*)&nomux_raw_row;
#else
case 51:return(void*)&teleport_termcap_nomux_raw_row;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 52:return(void*)&nomux_raw_col;
#else
case 52:return(void*)&teleport_termcap_nomux_raw_col;
#endif
case 53:return(void*)&ospeed;
#ifdef TELEPORT_REFERENCE_TU
case 54:return(void*)&tmspc10;
#else
case 54:return(void*)&teleport_termcap_tmspc10;
#endif
case 55:return(void*)&hilites;
#ifdef TELEPORT_REFERENCE_TU
case 56:return(void*)&nilstring;
#else
case 56:return(void*)&teleport_termcap_nilstring;
#endif
case 57:return(void*)&ti_map;
#ifdef TELEPORT_REFERENCE_TU
case 58:return(void*)&nulstr;
#else
case 58:return(void*)&teleport_termcap_nulstr;
#endif
default:abort();}}
static char teleport_termcap_buffer_0[2];
static char teleport_termcap_buffer_1[2];
static char teleport_termcap_buffer_2[3];
static char teleport_termcap_buffer_3[3];
static char teleport_termcap_buffer_4[128];
static char teleport_termcap_buffer_5[128];
void*teleport_termcap_static_buffer(int i){switch(i){
case 0:return teleport_termcap_buffer_0;
case 1:return teleport_termcap_buffer_1;
case 2:return teleport_termcap_buffer_2;
case 3:return teleport_termcap_buffer_3;
case 4:return teleport_termcap_buffer_4;
case 5:return teleport_termcap_buffer_5;
default:abort();}}
uint64_t teleport_termcap_read(int kind,void*at,int field){switch(kind){
case 0:{struct flag*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->null);
case 1:return (uint64_t)(uintptr_t)(p->silent);
default:abort();}}
case 1:{struct tc_gbl_data*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->tc_CO);
case 1:return (uint64_t)(uintptr_t)(p->tc_LI);
case 2:return (uint64_t)(uintptr_t)(p->tc_AS);
case 3:return (uint64_t)(uintptr_t)(p->tc_AE);
default:abort();}}
case 2:{struct instance_globals_t*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->tc_gbl_data);
default:abort();}}
case 3:{struct tc_lcl_data*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->tc_ND);
case 1:return (uint64_t)(uintptr_t)(p->tc_ul_hack);
case 2:return (uint64_t)(uintptr_t)(p->tc_CM);
case 3:return (uint64_t)(uintptr_t)(p->tc_US);
case 4:return (uint64_t)(uintptr_t)(p->tc_UE);
case 5:return (uint64_t)(uintptr_t)(p->tc_HI);
case 6:return (uint64_t)(uintptr_t)(p->tc_HE);
case 7:return (uint64_t)(uintptr_t)(p->tc_CD);
default:abort();}}
case 4:{struct symsetentry*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->handling);
default:abort();}}
case 5:{struct instance_globals_s*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->symset);
default:abort();}}
case 6:{struct instance_globals_c*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->currentgraphics);
case 1:return (uint64_t)(uintptr_t)(&p->Cmd);
default:abort();}}
case 7:{struct cmd*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->num_pad);
default:abort();}}
case 8:{struct DisplayDesc*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->cury);
case 1:return (uint64_t)(uintptr_t)(p->curx);
default:abort();}}
case 9:{nomux_cell*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ch);
case 1:return (uint64_t)(uintptr_t)(p->fg);
case 2:return (uint64_t)(uintptr_t)(p->attr);
case 3:return (uint64_t)(uintptr_t)(p->decgfx);
default:abort();}}
case 10:{struct instance_flags*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->wc2_darkgray);
case 1:return (uint64_t)(uintptr_t)(p->debug_fuzzer);
case 2:return (uint64_t)(uintptr_t)(p->colorcount);
default:abort();}}
case 11:{TELEPORT_TERMCAP_TI_MAP_TYPE*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->nh_color);
case 1:return (uint64_t)(uintptr_t)(p->nh_bright_color);
case 2:return (uint64_t)(uintptr_t)(p->ti_color);
default:abort();}}
default:abort();}}
void teleport_termcap_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct flag*p=at;switch(field){
case 0:p->null=value;return;
case 1:p->silent=value;return;
default:abort();}}
case 1:{struct tc_gbl_data*p=at;switch(field){
case 0:p->tc_CO=value;return;
case 1:p->tc_LI=value;return;
case 2:p->tc_AS=(void*)(uintptr_t)value;return;
case 3:p->tc_AE=(void*)(uintptr_t)value;return;
default:abort();}}
case 2:{struct instance_globals_t*p=at;switch(field){
case 0:memmove(&p->tc_gbl_data,(void*)(uintptr_t)value,sizeof p->tc_gbl_data);return;
default:abort();}}
case 3:{struct tc_lcl_data*p=at;switch(field){
case 0:p->tc_ND=(void*)(uintptr_t)value;return;
case 1:p->tc_ul_hack=value;return;
case 2:p->tc_CM=(void*)(uintptr_t)value;return;
case 3:p->tc_US=(void*)(uintptr_t)value;return;
case 4:p->tc_UE=(void*)(uintptr_t)value;return;
case 5:p->tc_HI=(void*)(uintptr_t)value;return;
case 6:p->tc_HE=(void*)(uintptr_t)value;return;
case 7:p->tc_CD=(void*)(uintptr_t)value;return;
default:abort();}}
case 4:{struct symsetentry*p=at;switch(field){
case 0:p->handling=value;return;
default:abort();}}
case 5:{struct instance_globals_s*p=at;switch(field){
default:abort();}}
case 6:{struct instance_globals_c*p=at;switch(field){
case 0:p->currentgraphics=value;return;
case 1:memmove(&p->Cmd,(void*)(uintptr_t)value,sizeof p->Cmd);return;
default:abort();}}
case 7:{struct cmd*p=at;switch(field){
case 0:p->num_pad=value;return;
default:abort();}}
case 8:{struct DisplayDesc*p=at;switch(field){
case 0:p->cury=value;return;
case 1:p->curx=value;return;
default:abort();}}
case 9:{nomux_cell*p=at;switch(field){
case 0:p->ch=value;return;
case 1:p->fg=value;return;
case 2:p->attr=value;return;
case 3:p->decgfx=value;return;
default:abort();}}
case 10:{struct instance_flags*p=at;switch(field){
case 0:p->wc2_darkgray=value;return;
case 1:p->debug_fuzzer=value;return;
case 2:p->colorcount=value;return;
default:abort();}}
case 11:{TELEPORT_TERMCAP_TI_MAP_TYPE*p=at;switch(field){
#ifndef TELEPORT_REFERENCE_TU
case 0:p->nh_color=value;return;
#endif
#ifndef TELEPORT_REFERENCE_TU
case 1:p->nh_bright_color=value;return;
#endif
#ifndef TELEPORT_REFERENCE_TU
case 2:p->ti_color=value;return;
#endif
default:abort();}}
default:abort();}}
void* teleport_termcap_address(int kind,void*at,int field){switch(kind){
case 0:{struct flag*p=at;switch(field){
case 0:return (void*)&p->null;
case 1:return (void*)&p->silent;
default:abort();}}
case 1:{struct tc_gbl_data*p=at;switch(field){
case 0:return (void*)&p->tc_CO;
case 1:return (void*)&p->tc_LI;
case 2:return (void*)&p->tc_AS;
case 3:return (void*)&p->tc_AE;
default:abort();}}
case 2:{struct instance_globals_t*p=at;switch(field){
case 0:return (void*)&p->tc_gbl_data;
default:abort();}}
case 3:{struct tc_lcl_data*p=at;switch(field){
case 0:return (void*)&p->tc_ND;
case 1:return (void*)&p->tc_ul_hack;
case 2:return (void*)&p->tc_CM;
case 3:return (void*)&p->tc_US;
case 4:return (void*)&p->tc_UE;
case 5:return (void*)&p->tc_HI;
case 6:return (void*)&p->tc_HE;
case 7:return (void*)&p->tc_CD;
default:abort();}}
case 4:{struct symsetentry*p=at;switch(field){
case 0:return (void*)&p->handling;
default:abort();}}
case 5:{struct instance_globals_s*p=at;switch(field){
case 0:return (void*)&p->symset;
default:abort();}}
case 6:{struct instance_globals_c*p=at;switch(field){
case 0:return (void*)&p->currentgraphics;
case 1:return (void*)&p->Cmd;
default:abort();}}
case 7:{struct cmd*p=at;switch(field){
case 0:return (void*)&p->num_pad;
default:abort();}}
case 8:{struct DisplayDesc*p=at;switch(field){
case 0:return (void*)&p->cury;
case 1:return (void*)&p->curx;
default:abort();}}
case 9:{nomux_cell*p=at;switch(field){
case 0:return (void*)&p->ch;
case 1:return (void*)&p->fg;
case 2:return (void*)&p->attr;
case 3:return (void*)&p->decgfx;
default:abort();}}
case 10:{struct instance_flags*p=at;switch(field){
case 0:return (void*)&p->wc2_darkgray;
case 1:return (void*)&p->debug_fuzzer;
case 2:return (void*)&p->colorcount;
default:abort();}}
case 11:{TELEPORT_TERMCAP_TI_MAP_TYPE*p=at;switch(field){
case 0:return (void*)&p->nh_color;
case 1:return (void*)&p->nh_bright_color;
case 2:return (void*)&p->ti_color;
default:abort();}}
default:abort();}}
static char termcap_literals[TERMCAP_LITERAL_CAPACITY];
char*teleport_termcap_literal_storage(void){return termcap_literals;}
size_t teleport_termcap_literal_capacity(void){return sizeof termcap_literals;}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
void teleport_termcap_error_p(char * a0){(error)(a0);}
void teleport_termcap_error_pp(char * a0,char * a1){(error)(a0,a1);}
int teleport_termcap_fprintf_pppiiiij(struct _IO_FILE * a0,char * a1,char * a2,int a3,int a4,int a5,int a6,unsigned long a7){return (fprintf)(a0,a1,a2,a3,a4,a5,a6,a7);}
int teleport_termcap_sprintf_pp(char * a0,char * a1){return (sprintf)(a0,a1);}
int teleport_termcap_sprintf_ppi(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
char * teleport_termcap_tparm_pi(char * a0,int a1){return (tparm)(a0,a1);}
void teleport_termcap_nh_snprintf_pipjpjjj(char * a0,int a1,char * a2,unsigned long a3,char * a4,long a5,long a6,long a7){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6,a7);}
void teleport_termcap_nh_snprintf_pipjpi(char * a0,int a1,char * a2,unsigned long a3,char * a4,int a5){(nh_snprintf)(a0,a1,a2,a3,a4,a5);}
#pragma clang diagnostic pop
#ifdef TELEPORT_REFERENCE_TU
#define teleport_termcap_callback_tty_decgraphics_termcap_fixup tty_decgraphics_termcap_fixup
#else
extern void teleport_termcap_callback_tty_decgraphics_termcap_fixup();
#endif
uintptr_t teleport_termcap_function_pointer(int kind){switch(kind){
case 3:return(uintptr_t)&teleport_termcap_callback_tty_decgraphics_termcap_fixup;
case 8:return(uintptr_t)&xputc;
default:abort();}}
uintptr_t teleport_termcap_foreign_function_pointer(int kind){switch(kind){
case 0:return(uintptr_t)&tty_utf8graphics_fixup;
default:abort();}}
_Static_assert(__builtin_types_compatible_p(__typeof__(&getenv),char * (*)(const char *)),"TERMCAP dependency getenv");
_Static_assert(__builtin_types_compatible_p(__typeof__(&error),void (*)(const char *,...)),"TERMCAP dependency error");
_Static_assert(__builtin_types_compatible_p(__typeof__(&alloc),long * (*)(unsigned int)),"TERMCAP dependency alloc");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strncmp),int (*)(const char *,const char *,size_t)),"TERMCAP dependency strncmp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&tgetent),int (*)(char *,const char *)),"TERMCAP dependency tgetent");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strncpy),char * (*)(char *restrict,const char *restrict,size_t)),"TERMCAP dependency strncpy");
_Static_assert(__builtin_types_compatible_p(__typeof__(&tgetstr),char * (*)(const char *,char **)),"TERMCAP dependency tgetstr");
_Static_assert(__builtin_types_compatible_p(__typeof__(&tgetnum),int (*)(const char *)),"TERMCAP dependency tgetnum");
_Static_assert(__builtin_types_compatible_p(__typeof__(&setclipped),void (*)(void)),"TERMCAP dependency setclipped");
_Static_assert(__builtin_types_compatible_p(__typeof__(&tgetflag),int (*)(const char *)),"TERMCAP dependency tgetflag");
_Static_assert(__builtin_types_compatible_p(__typeof__(&tty_raw_print),void (*)(const char *)),"TERMCAP dependency tty_raw_print");
_Static_assert(__builtin_types_compatible_p(__typeof__(&tty_wait_synch),void (*)(void)),"TERMCAP dependency tty_wait_synch");
_Static_assert(__builtin_types_compatible_p(__typeof__(&digit),boolean (*)(char)),"TERMCAP dependency digit");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dupstr),char * (*)(const char *)),"TERMCAP dependency dupstr");
_Static_assert(__builtin_types_compatible_p(__typeof__(&free),void (*)(void *)),"TERMCAP dependency free");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strlen),unsigned long (*)(const char *)),"TERMCAP dependency strlen");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcpy),char * (*)(char *restrict,const char *restrict)),"TERMCAP dependency strcpy");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strstr),char * (*)(const char *,const char *)),"TERMCAP dependency strstr");
_Static_assert(__builtin_types_compatible_p(__typeof__(&tty_utf8graphics_fixup),void (*)(void)),"TERMCAP dependency tty_utf8graphics_fixup");
_Static_assert(__builtin_types_compatible_p(__typeof__(&tty_curs),void (*)(winid,int,int)),"TERMCAP dependency tty_curs");
_Static_assert(__builtin_types_compatible_p(__typeof__(&tgoto),char * (*)(const char *,int,int)),"TERMCAP dependency tgoto");
_Static_assert(__builtin_types_compatible_p(__typeof__(&putchar),int (*)(int)),"TERMCAP dependency putchar");
_Static_assert(__builtin_types_compatible_p(__typeof__(&fflush),int (*)(FILE *)),"TERMCAP dependency fflush");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_capture),void (*)(const char *,int,int,int)),"TERMCAP dependency teleport_capture");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcmp),int (*)(const char *,const char *)),"TERMCAP dependency strcmp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&fprintf),int (*)(FILE *restrict,const char *restrict,...)),"TERMCAP dependency fprintf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&fwrite),unsigned long (*)(const void *restrict,size_t,size_t,FILE *restrict)),"TERMCAP dependency fwrite");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sprintf),int (*)(char *restrict,const char *restrict,...)),"TERMCAP dependency sprintf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&tputs),int (*)(const char *,int,int (*)(int))),"TERMCAP dependency tputs");
_Static_assert(__builtin_types_compatible_p(__typeof__(&erase_tty_screen),void (*)(void)),"TERMCAP dependency erase_tty_screen");
_Static_assert(__builtin_types_compatible_p(__typeof__(&tparm),char * (*)(const char *,...)),"TERMCAP dependency tparm");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcat),char * (*)(char *restrict,const char *restrict)),"TERMCAP dependency strcat");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nh_snprintf),void (*)(const char *,int,char *,size_t,const char *,...)),"TERMCAP dependency nh_snprintf");
