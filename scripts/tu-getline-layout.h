#include "hack.h"
#include "wintty.h"
#include "func_tab.h"
#include <stddef.h>
#include <limits.h>
#include <stdio.h>

#define GETLINE_LAYOUT(name, value) { #name, value }
#define GETLINE_WIN(field) GETLINE_LAYOUT(win_##field, offsetof(struct WinDesc, field)), GETLINE_LAYOUT(win_##field##_size, sizeof(((struct WinDesc *) 0)->field))
#define GETLINE_DISPLAY(field) GETLINE_LAYOUT(display_##field, offsetof(struct DisplayDesc, field)), GETLINE_LAYOUT(display_##field##_size, sizeof(((struct DisplayDesc *) 0)->field))
#define GETLINE_IFLAG(field) GETLINE_LAYOUT(iflag_##field, offsetof(struct instance_flags, field)), GETLINE_LAYOUT(iflag_##field##_size, sizeof(((struct instance_flags *) 0)->field))
static const struct {
    const char *name;
    size_t value;
} getline_layout[] = {
    GETLINE_LAYOUT(pointerSize, sizeof(void *)), GETLINE_LAYOUT(intSize, sizeof(int)),
    GETLINE_LAYOUT(longSize, sizeof(long)), GETLINE_LAYOUT(charSize, sizeof(char)),
    GETLINE_LAYOUT(charSigned, (char) -1 < 0), GETLINE_LAYOUT(CHAR_BIT, CHAR_BIT),
    GETLINE_LAYOUT(booleanSize, sizeof(boolean)), GETLINE_LAYOUT(booleanSigned, (boolean) -1 < 0),
    GETLINE_LAYOUT(windowSize, sizeof(struct WinDesc)),
    GETLINE_WIN(flags), GETLINE_WIN(maxcol), GETLINE_WIN(maxrow),
    GETLINE_LAYOUT(displaySize, sizeof(struct DisplayDesc)),
    GETLINE_DISPLAY(toplin), GETLINE_DISPLAY(inread), GETLINE_DISPLAY(intr), GETLINE_DISPLAY(dismiss_more),
    GETLINE_IFLAG(term_gone), GETLINE_IFLAG(prevmsg_window), GETLINE_IFLAG(cbreak), GETLINE_IFLAG(extmenu),
    GETLINE_LAYOUT(toplines, offsetof(__typeof__(gt), toplines)), GETLINE_LAYOUT(toplinesSize, sizeof gt.toplines),
    GETLINE_LAYOUT(inDoagain, offsetof(__typeof__(gi), in_doagain)), GETLINE_LAYOUT(inDoagainSize, sizeof gi.in_doagain),
    GETLINE_LAYOUT(doneHup, offsetof(struct sinfo, done_hup)), GETLINE_LAYOUT(doneHupSize, sizeof program_state.done_hup),
    GETLINE_LAYOUT(commandText, offsetof(struct ext_func_tab, ef_txt)),
    GETLINE_LAYOUT(commandTextSize, sizeof(((struct ext_func_tab *) 0)->ef_txt)),
#ifdef TTY_GRAPHICS
    GETLINE_LAYOUT(TTY_GRAPHICS, 1),
#else
    GETLINE_LAYOUT(TTY_GRAPHICS, 0),
#endif
#ifndef MACOS9
    GETLINE_LAYOUT(NEWAUTOCOMP, 1),
#else
    GETLINE_LAYOUT(NEWAUTOCOMP, 0),
#endif
#ifdef EDIT_GETLIN
    GETLINE_LAYOUT(EDIT_GETLIN, 1),
#else
    GETLINE_LAYOUT(EDIT_GETLIN, 0),
#endif
#ifdef DUMPLOG_CORE
    GETLINE_LAYOUT(DUMPLOG_CORE, 1),
#else
    GETLINE_LAYOUT(DUMPLOG_CORE, 0),
#endif
#ifdef HANGUPHANDLING
    GETLINE_LAYOUT(HANGUPHANDLING, 1),
#else
    GETLINE_LAYOUT(HANGUPHANDLING, 0),
#endif
    GETLINE_LAYOUT(MAXWIN, MAXWIN), GETLINE_LAYOUT(BUFSZ, BUFSZ), GETLINE_LAYOUT(COLNO, COLNO),
    GETLINE_LAYOUT(WIN_STOP, WIN_STOP), GETLINE_LAYOUT(TOPLINE_NEED_MORE, TOPLINE_NEED_MORE),
    GETLINE_LAYOUT(TOPLINE_SPECIAL_PROMPT, TOPLINE_SPECIAL_PROMPT), GETLINE_LAYOUT(TOPLINE_NON_EMPTY, TOPLINE_NON_EMPTY),
    GETLINE_LAYOUT(OVERRIDE_MSGTYPE, OVERRIDE_MSGTYPE), GETLINE_LAYOUT(SUPPRESS_HISTORY, SUPPRESS_HISTORY),
    GETLINE_LAYOUT(ECM_NOFLAGS, ECM_NOFLAGS), GETLINE_LAYOUT(ECM_IGNOREAC, ECM_IGNOREAC),
    GETLINE_LAYOUT(ECM_EXACTMATCH, ECM_EXACTMATCH), GETLINE_LAYOUT(EOF, EOF),
};
#undef GETLINE_LAYOUT
#undef GETLINE_WIN
#undef GETLINE_DISPLAY
#undef GETLINE_IFLAG

size_t probe_context_size(void) { return sizeof(struct DisplayDesc); }
int probe_layout_count(void) { return sizeof getline_layout / sizeof getline_layout[0]; }
const char *probe_layout_name(int index) { return getline_layout[index].name; }
size_t probe_layout_value(int index) { return getline_layout[index].value; }
