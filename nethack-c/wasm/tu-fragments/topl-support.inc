/* TOPL typed header/field/storage/callback/varargs transport; no combat policy. */
#include "hack.h"
#include "tcap.h"
#include "wintty.h"
#include <stdint.h>
#include <stddef.h>
extern char erase_char;
#include <stdio.h>
void teleport_topl_native_free(void*p){free(p); }
static struct {char **snapshot_mesgs;int nxtidx;boolean initd;}teleport_topl_persistent_bytes;void*teleport_topl_persistent(int i){switch(i){case 0:return &teleport_topl_persistent_bytes.snapshot_mesgs;case 1:return &teleport_topl_persistent_bytes.nxtidx;case 2:return &teleport_topl_persistent_bytes.initd;default:abort();}}
const void*teleport_topl_global(int i){switch(i){case 0:return(const void*)&wins;case 1:return(const void*)&WIN_MESSAGE;case 2:return(const void*)&iflags;case 3:return(const void*)&ttyDisplay;case 4:return(const void*)&windowprocs;case 5:return(const void*)&gt;case 6:return(const void*)&morc;case 7:return(const void*)&program_state;case 8:return(const void*)&BASE_WINDOW;case 9:return(const void*)&flags;case 10:return(const void*)&defmorestr;case 11:return(const void*)&yn_number;case 12:return(const void*)&quitchars;case 13:return(const void*)&erase_char;case 14:return(const void*)&gs;default:return 0;}}
int teleport_topl_bit(int kind,const void*p){switch(kind){default:abort();}}
void teleport_topl_set_bit(int kind,void*p,unsigned n){switch(kind){default:abort();}}
void*teleport_topl_callback(int i){switch(i){default:return 0;}}
winid teleport_topl_window_create_nhwindow(int a0){return create_nhwindow(a0);}
void teleport_topl_window_putstr(winid a0,int a1,const char * a2){putstr(a0,a1,a2);}
void teleport_topl_window_display_nhwindow(winid a0,boolean a1){display_nhwindow(a0,a1);}
void teleport_topl_window_destroy_nhwindow(winid a0){destroy_nhwindow(a0);}
int teleport_topl_v_0(char *restrict a0,const char *restrict a1,const char * a2){return sprintf(a0,a1,a2);}
int teleport_topl_v_1(char *restrict a0,const char *restrict a1,int a2){return sprintf(a0,a1,a2);}
int teleport_topl_v_2(char *restrict a0,const char *restrict a1,long a2){return sprintf(a0,a1,a2);}
int teleport_topl_v_3(char *restrict a0,const char *restrict a1,const char * a2,const char * a3){return sprintf(a0,a1,a2,a3);}
void teleport_topl_v_5(const char * a0){panic(a0);}
void teleport_topl_v_7(unsigned int a0,const char * a1,const char * a2){custompline(a0,a1,a2);}
static char teleport_topl_literals[433];void*teleport_topl_literal_storage(void){return teleport_topl_literals;}size_t teleport_topl_literal_capacity(void){return sizeof teleport_topl_literals;}
