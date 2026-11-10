#ifndef TELEPORT_TOPL_LAYOUT_H
#define TELEPORT_TOPL_LAYOUT_H
#include "hack.h"
#include "tcap.h"
#include "wintty.h"
#include <stddef.h>
#if !defined(UNIX) || !defined(DEBUG) || !defined(TTY_GRAPHICS) || !defined(NOMUX_CAPTURE) || !defined(DUMPLOG_CORE) || defined(WIN32CON)
#error Review changed TOPL configured profile
#endif

struct topl_layout_entry {const char *name;long long value;};
#define TOPL_META(k,v) {#k,(long long)(v)}
static const struct topl_layout_entry topl_layout[]={
TOPL_META(pointerSize,sizeof(void*)),
TOPL_META(longSize,sizeof(long)),
TOPL_META(booleanSize,sizeof(boolean)),
TOPL_META(intSize,sizeof(int)),
TOPL_META(charMin,CHAR_MIN),
TOPL_META(charMax,CHAR_MAX),
TOPL_META(R0_size,sizeof(struct instance_flags)),
TOPL_META(R0_F0,offsetof(struct instance_flags,prevmsg_window)),
TOPL_META(R0_F0_size,sizeof(((struct instance_flags*)0)->prevmsg_window)),
TOPL_META(R0_F1,offsetof(struct instance_flags,debug_fuzzer)),
TOPL_META(R0_F1_size,sizeof(((struct instance_flags*)0)->debug_fuzzer)),
TOPL_META(R1_size,sizeof(struct DisplayDesc)),
TOPL_META(R1_F0,offsetof(struct DisplayDesc,inread)),
TOPL_META(R1_F0_size,sizeof(((struct DisplayDesc*)0)->inread)),
TOPL_META(R1_F1,offsetof(struct DisplayDesc,dismiss_more)),
TOPL_META(R1_F1_size,sizeof(((struct DisplayDesc*)0)->dismiss_more)),
TOPL_META(R1_F2,offsetof(struct DisplayDesc,toplin)),
TOPL_META(R1_F2_size,sizeof(((struct DisplayDesc*)0)->toplin)),
TOPL_META(R1_F3,offsetof(struct DisplayDesc,topl_utf8)),
TOPL_META(R1_F3_size,sizeof(((struct DisplayDesc*)0)->topl_utf8)),
TOPL_META(R1_F4,offsetof(struct DisplayDesc,mixed)),
TOPL_META(R1_F4_size,sizeof(((struct DisplayDesc*)0)->mixed)),
TOPL_META(R1_F5,offsetof(struct DisplayDesc,curx)),
TOPL_META(R1_F5_size,sizeof(((struct DisplayDesc*)0)->curx)),
TOPL_META(R1_F6,offsetof(struct DisplayDesc,cury)),
TOPL_META(R1_F6_size,sizeof(((struct DisplayDesc*)0)->cury)),
TOPL_META(R1_F7,offsetof(struct DisplayDesc,inmore)),
TOPL_META(R1_F7_size,sizeof(((struct DisplayDesc*)0)->inmore)),
TOPL_META(R1_F8,offsetof(struct DisplayDesc,intr)),
TOPL_META(R1_F8_size,sizeof(((struct DisplayDesc*)0)->intr)),
TOPL_META(R2_size,sizeof(struct window_procs)),
TOPL_META(R2_F0,offsetof(struct window_procs,win_create_nhwindow)),
TOPL_META(R2_F0_size,sizeof(((struct window_procs*)0)->win_create_nhwindow)),
TOPL_META(R2_F1,offsetof(struct window_procs,win_putstr)),
TOPL_META(R2_F1_size,sizeof(((struct window_procs*)0)->win_putstr)),
TOPL_META(R2_F2,offsetof(struct window_procs,win_display_nhwindow)),
TOPL_META(R2_F2_size,sizeof(((struct window_procs*)0)->win_display_nhwindow)),
TOPL_META(R2_F3,offsetof(struct window_procs,win_destroy_nhwindow)),
TOPL_META(R2_F3_size,sizeof(((struct window_procs*)0)->win_destroy_nhwindow)),
TOPL_META(R3_size,sizeof(struct WinDesc)),
TOPL_META(R3_F0,offsetof(struct WinDesc,maxcol)),
TOPL_META(R3_F0_size,sizeof(((struct WinDesc*)0)->maxcol)),
TOPL_META(R3_F1,offsetof(struct WinDesc,maxrow)),
TOPL_META(R3_F1_size,sizeof(((struct WinDesc*)0)->maxrow)),
TOPL_META(R3_F2,offsetof(struct WinDesc,data)),
TOPL_META(R3_F2_size,sizeof(((struct WinDesc*)0)->data)),
TOPL_META(R3_F3,offsetof(struct WinDesc,rows)),
TOPL_META(R3_F3_size,sizeof(((struct WinDesc*)0)->rows)),
TOPL_META(R3_F4,offsetof(struct WinDesc,flags)),
TOPL_META(R3_F4_size,sizeof(((struct WinDesc*)0)->flags)),
TOPL_META(R3_F5,offsetof(struct WinDesc,curx)),
TOPL_META(R3_F5_size,sizeof(((struct WinDesc*)0)->curx)),
TOPL_META(R3_F6,offsetof(struct WinDesc,cury)),
TOPL_META(R3_F6_size,sizeof(((struct WinDesc*)0)->cury)),
TOPL_META(R3_F7,offsetof(struct WinDesc,datlen)),
TOPL_META(R3_F7_size,sizeof(((struct WinDesc*)0)->datlen)),
TOPL_META(R4_size,sizeof(struct instance_globals_t)),
TOPL_META(R4_F0,offsetof(struct instance_globals_t,toplines)),
TOPL_META(R4_F0_size,sizeof(((struct instance_globals_t*)0)->toplines)),
TOPL_META(R4_F0_stride,sizeof(((struct instance_globals_t*)0)->toplines[0])),
TOPL_META(R4_F1,offsetof(struct instance_globals_t,tc_gbl_data)),
TOPL_META(R4_F1_size,sizeof(((struct instance_globals_t*)0)->tc_gbl_data)),
TOPL_META(R5_size,sizeof(struct sinfo)),
TOPL_META(R5_F0,offsetof(struct sinfo,in_checkpoint)),
TOPL_META(R5_F0_size,sizeof(((struct sinfo*)0)->in_checkpoint)),
TOPL_META(R6_size,sizeof(struct tc_gbl_data)),
TOPL_META(R6_F0,offsetof(struct tc_gbl_data,tc_CO)),
TOPL_META(R6_F0_size,sizeof(((struct tc_gbl_data*)0)->tc_CO)),
TOPL_META(R7_size,sizeof(struct flag)),
TOPL_META(R7_F0,offsetof(struct flag,standout)),
TOPL_META(R7_F0_size,sizeof(((struct flag*)0)->standout)),
TOPL_META(R8_size,sizeof(struct instance_globals_s)),
TOPL_META(R8_F0,offsetof(struct instance_globals_s,saved_pline_index)),
TOPL_META(R8_F0_size,sizeof(((struct instance_globals_s*)0)->saved_pline_index)),
TOPL_META(BUFSZ,BUFSZ),
TOPL_META(MAXWIN,MAXWIN),
TOPL_META(NHW_MENU,NHW_MENU),
TOPL_META(OVERRIDE_MSGTYPE,OVERRIDE_MSGTYPE),
TOPL_META(QBUFSZ,QBUFSZ),
TOPL_META(SUPPRESS_HISTORY,SUPPRESS_HISTORY),
TOPL_META(TBUFSZ,TBUFSZ),
TOPL_META(TOPLINE_EMPTY,TOPLINE_EMPTY),
TOPL_META(TOPLINE_NEED_MORE,TOPLINE_NEED_MORE),
TOPL_META(TOPLINE_NON_EMPTY,TOPLINE_NON_EMPTY),
TOPL_META(TOPLINE_SPECIAL_PROMPT,TOPLINE_SPECIAL_PROMPT),
TOPL_META(WIN_ERR,WIN_ERR),
TOPL_META(WIN_LOCKHISTORY,WIN_LOCKHISTORY),
TOPL_META(WIN_NOSTOP,WIN_NOSTOP),
TOPL_META(WIN_STOP,WIN_STOP),
};
#undef TOPL_META
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(boolean)==1,"TOPL native widths");
_Static_assert(sizeof(coordxy)==2 && (coordxy)-1<0,"TOPL coord width/sign");
_Static_assert(CHAR_MIN==-128 && CHAR_MAX==127,"TOPL signed char contract");
_Static_assert(sizeof(((struct instance_flags*)0)->prevmsg_window)==1,"TOPL field width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->prevmsg_window))-1)<0)==1,"TOPL field sign");
_Static_assert(sizeof(((struct instance_flags*)0)->debug_fuzzer)==1,"TOPL field width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->debug_fuzzer))-1)<0)==1,"TOPL field sign");
_Static_assert(sizeof(((struct DisplayDesc*)0)->inread)==4,"TOPL field width");
_Static_assert((((__typeof__(((struct DisplayDesc*)0)->inread))-1)<0)==1,"TOPL field sign");
_Static_assert(sizeof(((struct DisplayDesc*)0)->dismiss_more)==1,"TOPL field width");
_Static_assert((((__typeof__(((struct DisplayDesc*)0)->dismiss_more))-1)<0)==1,"TOPL field sign");
_Static_assert(sizeof(((struct DisplayDesc*)0)->toplin)==4,"TOPL field width");
_Static_assert((((__typeof__(((struct DisplayDesc*)0)->toplin))-1)<0)==1,"TOPL field sign");
_Static_assert(sizeof(((struct DisplayDesc*)0)->topl_utf8)==4,"TOPL field width");
_Static_assert((((__typeof__(((struct DisplayDesc*)0)->topl_utf8))-1)<0)==1,"TOPL field sign");
_Static_assert(sizeof(((struct DisplayDesc*)0)->mixed)==4,"TOPL field width");
_Static_assert((((__typeof__(((struct DisplayDesc*)0)->mixed))-1)<0)==1,"TOPL field sign");
_Static_assert(sizeof(((struct DisplayDesc*)0)->curx)==2,"TOPL field width");
_Static_assert((((__typeof__(((struct DisplayDesc*)0)->curx))-1)<0)==1,"TOPL field sign");
_Static_assert(sizeof(((struct DisplayDesc*)0)->cury)==2,"TOPL field width");
_Static_assert((((__typeof__(((struct DisplayDesc*)0)->cury))-1)<0)==1,"TOPL field sign");
_Static_assert(sizeof(((struct DisplayDesc*)0)->inmore)==4,"TOPL field width");
_Static_assert((((__typeof__(((struct DisplayDesc*)0)->inmore))-1)<0)==1,"TOPL field sign");
_Static_assert(sizeof(((struct DisplayDesc*)0)->intr)==4,"TOPL field width");
_Static_assert((((__typeof__(((struct DisplayDesc*)0)->intr))-1)<0)==1,"TOPL field sign");
_Static_assert(sizeof(((struct WinDesc*)0)->maxcol)==8,"TOPL field width");
_Static_assert((((__typeof__(((struct WinDesc*)0)->maxcol))-1)<0)==1,"TOPL field sign");
_Static_assert(sizeof(((struct WinDesc*)0)->maxrow)==8,"TOPL field width");
_Static_assert((((__typeof__(((struct WinDesc*)0)->maxrow))-1)<0)==1,"TOPL field sign");
_Static_assert(sizeof(((struct WinDesc*)0)->rows)==8,"TOPL field width");
_Static_assert((((__typeof__(((struct WinDesc*)0)->rows))-1)<0)==1,"TOPL field sign");
_Static_assert(sizeof(((struct WinDesc*)0)->flags)==4,"TOPL field width");
_Static_assert((((__typeof__(((struct WinDesc*)0)->flags))-1)<0)==1,"TOPL field sign");
_Static_assert(sizeof(((struct WinDesc*)0)->curx)==8,"TOPL field width");
_Static_assert((((__typeof__(((struct WinDesc*)0)->curx))-1)<0)==1,"TOPL field sign");
_Static_assert(sizeof(((struct WinDesc*)0)->cury)==8,"TOPL field width");
_Static_assert((((__typeof__(((struct WinDesc*)0)->cury))-1)<0)==1,"TOPL field sign");
_Static_assert(sizeof(((struct sinfo*)0)->in_checkpoint)==4,"TOPL field width");
_Static_assert((((__typeof__(((struct sinfo*)0)->in_checkpoint))-1)<0)==1,"TOPL field sign");
_Static_assert(sizeof(((struct tc_gbl_data*)0)->tc_CO)==4,"TOPL field width");
_Static_assert((((__typeof__(((struct tc_gbl_data*)0)->tc_CO))-1)<0)==1,"TOPL field sign");
_Static_assert(sizeof(((struct flag*)0)->standout)==1,"TOPL field width");
_Static_assert((((__typeof__(((struct flag*)0)->standout))-1)<0)==1,"TOPL field sign");
_Static_assert(sizeof(((struct instance_globals_s*)0)->saved_pline_index)==4,"TOPL field width");
_Static_assert((((__typeof__(((struct instance_globals_s*)0)->saved_pline_index))-1)<0)==0,"TOPL field sign");
#endif
