/* Compiler-derived PLINE layout and active feature metadata. */
#include "hack.h"
#include <stdarg.h>
#include <stddef.h>
struct pline_meta {const char *name;size_t value;};
#define PLINE_META(k,v) {#k,(size_t)(v)}
static const struct pline_meta pline_layout[]={
PLINE_META(pointerSize,sizeof(void*)),PLINE_META(intSize,sizeof(int)),PLINE_META(longSize,sizeof(long)),PLINE_META(coordxySize,sizeof(coordxy)),PLINE_META(booleanSize,sizeof(boolean)),PLINE_META(charSigned,(char)-1<0),PLINE_META(vaSize,sizeof(va_list)),PLINE_META(BIGBUFSZ,5*BUFSZ),PLINE_META(gamelogSize,sizeof(struct gamelog_line)),
PLINE_META(BUFSZ,BUFSZ),
PLINE_META(QBUFSZ,QBUFSZ),
PLINE_META(DUMPLOG_MSG_COUNT,DUMPLOG_MSG_COUNT),
PLINE_META(ATR_NONE,ATR_NONE),
PLINE_META(URGENT_MESSAGE,URGENT_MESSAGE),
PLINE_META(WC2_URGENT_MESG,WC2_URGENT_MESG),
PLINE_META(ATR_URGENT,ATR_URGENT),
PLINE_META(SUPPRESS_HISTORY,SUPPRESS_HISTORY),
PLINE_META(WC2_SUPPRESS_HIST,WC2_SUPPRESS_HIST),
PLINE_META(ATR_NOHISTORY,ATR_NOHISTORY),
PLINE_META(PLINE_NOREPEAT,PLINE_NOREPEAT),
PLINE_META(OVERRIDE_MSGTYPE,OVERRIDE_MSGTYPE),
PLINE_META(NO_CURS_ON_U,NO_CURS_ON_U),
PLINE_META(PLINE_VERBALIZE,PLINE_VERBALIZE),
PLINE_META(PLNMSG_UNKNOWN,PLNMSG_UNKNOWN),
PLINE_META(MSGTYP_NORMAL,MSGTYP_NORMAL),
PLINE_META(MSGTYP_NOSHOW,MSGTYP_NOSHOW),
PLINE_META(MSGTYP_NOREP,MSGTYP_NOREP),
PLINE_META(MSGTYP_STOP,MSGTYP_STOP),
PLINE_META(GPCOORDS_NONE,GPCOORDS_NONE),
PLINE_META(GPCOORDS_COMFULL,GPCOORDS_COMFULL),
PLINE_META(FALSE,FALSE),
PLINE_META(TRUE,TRUE),
PLINE_META(fuzzer_impossible_panic,fuzzer_impossible_panic),
PLINE_META(EXIT_FAILURE,EXIT_FAILURE),
PLINE_META(width_0,sizeof gs.saved_pline_index),
PLINE_META(width_1,sizeof gs.saved_plines),
PLINE_META(width_2,sizeof iflags.debug_prevent_pline),
PLINE_META(width_3,sizeof gp.pline_flags),
PLINE_META(width_4,sizeof windowprocs.wincap2),
PLINE_META(width_5,sizeof WIN_MESSAGE),
PLINE_META(width_6,sizeof a11y.msg_loc),
PLINE_META(width_7,sizeof u.ux),
PLINE_META(width_8,sizeof u.uy),
PLINE_META(width_9,sizeof program_state.done_hup),
PLINE_META(width_10,sizeof program_state.wizkit_wishing),
PLINE_META(width_11,sizeof a11y.accessiblemsg),
PLINE_META(width_12,sizeof iflags.getpos_coords),
PLINE_META(width_13,sizeof iflags.window_inited),
PLINE_META(width_14,sizeof iflags.last_msg),
PLINE_META(width_15,sizeof gp.prevmsg),
PLINE_META(width_16,sizeof gv.vision_full_recalc),
PLINE_META(width_17,sizeof gy.you_buf),
PLINE_META(width_18,sizeof gy.you_buf_siz),
PLINE_META(width_19,sizeof gg.gamelog),
PLINE_META(width_20,sizeof svm.moves),
PLINE_META(width_21,sizeof program_state.beyond_savefile_load),
PLINE_META(width_22,sizeof ge.early_raw_messages),
PLINE_META(width_23,sizeof program_state.in_impossible),
PLINE_META(width_24,sizeof iflags.debug_fuzzer),
PLINE_META(width_25,sizeof program_state.in_sanity_check),
PLINE_META(width_26,sizeof program_state.something_worth_saving),
PLINE_META(width_27,sizeof sysopt.support),
PLINE_META(width_28,sizeof sysopt.crashreporturl),
PLINE_META(width_29,sizeof sysopt.msghandler),
PLINE_META(width_30,sizeof flags.acoustics),
PLINE_META(width_31,sizeof gy.youmonst),
PLINE_META(width_32,0),
PLINE_META(coord_x,offsetof(coord,x)),PLINE_META(coord_x_size,sizeof(((coord*)0)->x)),
PLINE_META(coord_y,offsetof(coord,y)),PLINE_META(coord_y_size,sizeof(((coord*)0)->y)),
PLINE_META(monster_mx,offsetof(struct monst,mx)),PLINE_META(monster_mx_size,sizeof(((struct monst*)0)->mx)),
PLINE_META(monster_my,offsetof(struct monst,my)),PLINE_META(monster_my_size,sizeof(((struct monst*)0)->my)),
PLINE_META(gamelog_turn,offsetof(struct gamelog_line,turn)),PLINE_META(gamelog_turn_size,sizeof(((struct gamelog_line*)0)->turn)),
PLINE_META(gamelog_flags,offsetof(struct gamelog_line,flags)),PLINE_META(gamelog_flags_size,sizeof(((struct gamelog_line*)0)->flags)),
PLINE_META(gamelog_text,offsetof(struct gamelog_line,text)),PLINE_META(gamelog_text_size,sizeof(((struct gamelog_line*)0)->text)),
PLINE_META(gamelog_next,offsetof(struct gamelog_line,next)),PLINE_META(gamelog_next_size,sizeof(((struct gamelog_line*)0)->next)),
#ifdef CHRONICLE
PLINE_META(config_CHRONICLE,1),
#else
PLINE_META(config_CHRONICLE,0),
#endif
#ifdef DUMPLOG_CORE
PLINE_META(config_DUMPLOG_CORE,1),
#else
PLINE_META(config_DUMPLOG_CORE,0),
#endif
#ifdef HANGUPHANDLING
PLINE_META(config_HANGUPHANDLING,1),
#else
PLINE_META(config_HANGUPHANDLING,0),
#endif
#ifdef CRASHREPORT
PLINE_META(config_CRASHREPORT,1),
#else
PLINE_META(config_CRASHREPORT,0),
#endif
#ifdef UNIX
PLINE_META(config_UNIX,1),
#else
PLINE_META(config_UNIX,0),
#endif
#ifdef SND_SPEECH
PLINE_META(config_SND_SPEECH,1),
#else
PLINE_META(config_SND_SPEECH,0),
#endif
#ifdef USER_SOUNDS
PLINE_META(config_USER_SOUNDS,1),
#else
PLINE_META(config_USER_SOUNDS,0),
#endif
#ifdef SND_LIB_INTEGRATED
PLINE_META(config_SND_LIB_INTEGRATED,1),
#else
PLINE_META(config_SND_LIB_INTEGRATED,0),
#endif
#ifdef WIN32
PLINE_META(config_WIN32,1),
#else
PLINE_META(config_WIN32,0),
#endif
#ifdef VMS
PLINE_META(config_VMS,1),
#else
PLINE_META(config_VMS,0),
#endif
};
#undef PLINE_META
