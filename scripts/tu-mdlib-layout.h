#include "hack.h"
#include "patchlevel.h"
#include <stddef.h>
#include <limits.h>

#define MDLIB_LAYOUT(name, value) { #name, value }
static const struct { const char *name; size_t value; } mdlib_layout[] = {
    MDLIB_LAYOUT(pointerSize, sizeof(void *)), MDLIB_LAYOUT(intSize, sizeof(int)),
    MDLIB_LAYOUT(longSize, sizeof(long)), MDLIB_LAYOUT(charSize, sizeof(char)),
    MDLIB_LAYOUT(charSigned, (char) -1 < 0), MDLIB_LAYOUT(CHAR_BIT, CHAR_BIT),
    MDLIB_LAYOUT(booleanSize, sizeof(boolean)), MDLIB_LAYOUT(booleanSigned, (boolean) -1 < 0),
    MDLIB_LAYOUT(MAXOPT, 60), MDLIB_LAYOUT(COLBUFSZ, COLBUFSZ),
    MDLIB_LAYOUT(BUFSZ, BUFSZ), MDLIB_LAYOUT(COLNO, COLNO),
    MDLIB_LAYOUT(versionSize, sizeof(struct version_info)),
    MDLIB_LAYOUT(versionIncarnation, offsetof(struct version_info, incarnation)),
    MDLIB_LAYOUT(versionFeatureSet, offsetof(struct version_info, feature_set)),
    MDLIB_LAYOUT(versionEntityCount, offsetof(struct version_info, entity_count)),
    MDLIB_LAYOUT(versionFieldSize, sizeof(((struct version_info *) 0)->incarnation)),
    MDLIB_LAYOUT(VERSION_MAJOR, VERSION_MAJOR), MDLIB_LAYOUT(VERSION_MINOR, VERSION_MINOR),
    MDLIB_LAYOUT(PATCHLEVEL, PATCHLEVEL), MDLIB_LAYOUT(EDITLEVEL, EDITLEVEL),
    MDLIB_LAYOUT(NH_DEVEL_STATUS, NH_DEVEL_STATUS), MDLIB_LAYOUT(SFCTOOL_BIT, SFCTOOL_BIT),
    MDLIB_LAYOUT(NUM_OBJECTS, NUM_OBJECTS), MDLIB_LAYOUT(NUMMONS, NUMMONS),
#ifdef AMIGA
    MDLIB_LAYOUT(flag_AMIGA, 1),
#else
    MDLIB_LAYOUT(flag_AMIGA, 0),
#endif
#ifdef AMIGA_INTUITION
    MDLIB_LAYOUT(flag_AMIGA_INTUITION, 1),
#else
    MDLIB_LAYOUT(flag_AMIGA_INTUITION, 0),
#endif
#ifdef AMIGA_WBENCH
    MDLIB_LAYOUT(flag_AMIGA_WBENCH, 1),
#else
    MDLIB_LAYOUT(flag_AMIGA_WBENCH, 0),
#endif
#ifdef ANSI_DEFAULT
    MDLIB_LAYOUT(flag_ANSI_DEFAULT, 1),
#else
    MDLIB_LAYOUT(flag_ANSI_DEFAULT, 0),
#endif
#ifdef AZTEC_C
    MDLIB_LAYOUT(flag_AZTEC_C, 1),
#else
    MDLIB_LAYOUT(flag_AZTEC_C, 0),
#endif
#ifdef BEOS_GRAPHICS
    MDLIB_LAYOUT(flag_BEOS_GRAPHICS, 1),
#else
    MDLIB_LAYOUT(flag_BEOS_GRAPHICS, 0),
#endif
#ifdef CLIPPING
    MDLIB_LAYOUT(flag_CLIPPING, 1),
#else
    MDLIB_LAYOUT(flag_CLIPPING, 0),
#endif
#ifdef COMPRESS
    MDLIB_LAYOUT(flag_COMPRESS, 1),
#else
    MDLIB_LAYOUT(flag_COMPRESS, 0),
#endif
#ifdef CRASHREPORT
    MDLIB_LAYOUT(flag_CRASHREPORT, 1),
#else
    MDLIB_LAYOUT(flag_CRASHREPORT, 0),
#endif
#ifdef CURSES_GRAPHICS
    MDLIB_LAYOUT(flag_CURSES_GRAPHICS, 1),
#else
    MDLIB_LAYOUT(flag_CURSES_GRAPHICS, 0),
#endif
#ifdef DEF_PAGER
    MDLIB_LAYOUT(flag_DEF_PAGER, 1),
#else
    MDLIB_LAYOUT(flag_DEF_PAGER, 0),
#endif
#ifdef DEV_RANDOM
    MDLIB_LAYOUT(flag_DEV_RANDOM, 1),
#else
    MDLIB_LAYOUT(flag_DEV_RANDOM, 0),
#endif
#ifdef DLB
    MDLIB_LAYOUT(flag_DLB, 1),
#else
    MDLIB_LAYOUT(flag_DLB, 0),
#endif
#ifdef DUMPLOG
    MDLIB_LAYOUT(flag_DUMPLOG, 1),
#else
    MDLIB_LAYOUT(flag_DUMPLOG, 0),
#endif
#ifdef EDIT_GETLIN
    MDLIB_LAYOUT(flag_EDIT_GETLIN, 1),
#else
    MDLIB_LAYOUT(flag_EDIT_GETLIN, 0),
#endif
#ifdef GEM_GRAPHICS
    MDLIB_LAYOUT(flag_GEM_GRAPHICS, 1),
#else
    MDLIB_LAYOUT(flag_GEM_GRAPHICS, 0),
#endif
#ifdef GNOME_GRAPHICS
    MDLIB_LAYOUT(flag_GNOME_GRAPHICS, 1),
#else
    MDLIB_LAYOUT(flag_GNOME_GRAPHICS, 0),
#endif
#ifdef GNUDOS
    MDLIB_LAYOUT(flag_GNUDOS, 1),
#else
    MDLIB_LAYOUT(flag_GNUDOS, 0),
#endif
#ifdef GRAPHIC_TOMBSTONE
    MDLIB_LAYOUT(flag_GRAPHIC_TOMBSTONE, 1),
#else
    MDLIB_LAYOUT(flag_GRAPHIC_TOMBSTONE, 0),
#endif
#ifdef HANGUPHANDLING
    MDLIB_LAYOUT(flag_HANGUPHANDLING, 1),
#else
    MDLIB_LAYOUT(flag_HANGUPHANDLING, 0),
#endif
#ifdef HAS_NO_MKSTEMP
    MDLIB_LAYOUT(flag_HAS_NO_MKSTEMP, 1),
#else
    MDLIB_LAYOUT(flag_HAS_NO_MKSTEMP, 0),
#endif
#ifdef HOLD_LOCKFILE_OPEN
    MDLIB_LAYOUT(flag_HOLD_LOCKFILE_OPEN, 1),
#else
    MDLIB_LAYOUT(flag_HOLD_LOCKFILE_OPEN, 0),
#endif
#ifdef INSURANCE
    MDLIB_LAYOUT(flag_INSURANCE, 1),
#else
    MDLIB_LAYOUT(flag_INSURANCE, 0),
#endif
#ifdef LIFE
    MDLIB_LAYOUT(flag_LIFE, 1),
#else
    MDLIB_LAYOUT(flag_LIFE, 0),
#endif
#ifdef LIVELOG
    MDLIB_LAYOUT(flag_LIVELOG, 1),
#else
    MDLIB_LAYOUT(flag_LIVELOG, 0),
#endif
#ifdef LOGFILE
    MDLIB_LAYOUT(flag_LOGFILE, 1),
#else
    MDLIB_LAYOUT(flag_LOGFILE, 0),
#endif
#ifdef MACOS9
    MDLIB_LAYOUT(flag_MACOS9, 1),
#else
    MDLIB_LAYOUT(flag_MACOS9, 0),
#endif
#ifdef MAIL
    MDLIB_LAYOUT(flag_MAIL, 1),
#else
    MDLIB_LAYOUT(flag_MAIL, 0),
#endif
#ifdef MAIL_STRUCTURES
    MDLIB_LAYOUT(flag_MAIL_STRUCTURES, 1),
#else
    MDLIB_LAYOUT(flag_MAIL_STRUCTURES, 0),
#endif
#ifdef MICRO
    MDLIB_LAYOUT(flag_MICRO, 1),
#else
    MDLIB_LAYOUT(flag_MICRO, 0),
#endif
#ifdef MONITOR_HEAP
    MDLIB_LAYOUT(flag_MONITOR_HEAP, 1),
#else
    MDLIB_LAYOUT(flag_MONITOR_HEAP, 0),
#endif
#ifdef MOVERLAY
    MDLIB_LAYOUT(flag_MOVERLAY, 1),
#else
    MDLIB_LAYOUT(flag_MOVERLAY, 0),
#endif
#ifdef MSDOS
    MDLIB_LAYOUT(flag_MSDOS, 1),
#else
    MDLIB_LAYOUT(flag_MSDOS, 0),
#endif
#ifdef MSWIN_GRAPHICS
    MDLIB_LAYOUT(flag_MSWIN_GRAPHICS, 1),
#else
    MDLIB_LAYOUT(flag_MSWIN_GRAPHICS, 0),
#endif
#ifdef NEWS
    MDLIB_LAYOUT(flag_NEWS, 1),
#else
    MDLIB_LAYOUT(flag_NEWS, 0),
#endif
#ifdef NO_SIGNAL
    MDLIB_LAYOUT(flag_NO_SIGNAL, 1),
#else
    MDLIB_LAYOUT(flag_NO_SIGNAL, 0),
#endif
#ifdef NO_TERMS
    MDLIB_LAYOUT(flag_NO_TERMS, 1),
#else
    MDLIB_LAYOUT(flag_NO_TERMS, 0),
#endif
#ifdef OVERLAY
    MDLIB_LAYOUT(flag_OVERLAY, 1),
#else
    MDLIB_LAYOUT(flag_OVERLAY, 0),
#endif
#ifdef PANICLOG
    MDLIB_LAYOUT(flag_PANICLOG, 1),
#else
    MDLIB_LAYOUT(flag_PANICLOG, 0),
#endif
#ifdef PANICTRACE
    MDLIB_LAYOUT(flag_PANICTRACE, 1),
#else
    MDLIB_LAYOUT(flag_PANICTRACE, 0),
#endif
#ifdef PORT_SUB_ID
    MDLIB_LAYOUT(flag_PORT_SUB_ID, 1),
#else
    MDLIB_LAYOUT(flag_PORT_SUB_ID, 0),
#endif
#ifdef PREFIXES_IN_USE
    MDLIB_LAYOUT(flag_PREFIXES_IN_USE, 1),
#else
    MDLIB_LAYOUT(flag_PREFIXES_IN_USE, 0),
#endif
#ifdef QT_GRAPHICS
    MDLIB_LAYOUT(flag_QT_GRAPHICS, 1),
#else
    MDLIB_LAYOUT(flag_QT_GRAPHICS, 0),
#endif
#ifdef RANDOM
    MDLIB_LAYOUT(flag_RANDOM, 1),
#else
    MDLIB_LAYOUT(flag_RANDOM, 0),
#endif
#ifdef SAFERHANGUP
    MDLIB_LAYOUT(flag_SAFERHANGUP, 1),
#else
    MDLIB_LAYOUT(flag_SAFERHANGUP, 0),
#endif
#ifdef SCORE_ON_BOTL
    MDLIB_LAYOUT(flag_SCORE_ON_BOTL, 1),
#else
    MDLIB_LAYOUT(flag_SCORE_ON_BOTL, 0),
#endif
#ifdef SCREEN_BIOS
    MDLIB_LAYOUT(flag_SCREEN_BIOS, 1),
#else
    MDLIB_LAYOUT(flag_SCREEN_BIOS, 0),
#endif
#ifdef SCREEN_DJGPPFAST
    MDLIB_LAYOUT(flag_SCREEN_DJGPPFAST, 1),
#else
    MDLIB_LAYOUT(flag_SCREEN_DJGPPFAST, 0),
#endif
#ifdef SCREEN_VGA
    MDLIB_LAYOUT(flag_SCREEN_VGA, 1),
#else
    MDLIB_LAYOUT(flag_SCREEN_VGA, 0),
#endif
#ifdef SELECTSAVED
    MDLIB_LAYOUT(flag_SELECTSAVED, 1),
#else
    MDLIB_LAYOUT(flag_SELECTSAVED, 0),
#endif
#ifdef SFCTOOL
    MDLIB_LAYOUT(flag_SFCTOOL, 1),
#else
    MDLIB_LAYOUT(flag_SFCTOOL, 0),
#endif
#ifdef SHELL
    MDLIB_LAYOUT(flag_SHELL, 1),
#else
    MDLIB_LAYOUT(flag_SHELL, 0),
#endif
#ifdef SHIM_GRAPHICS
    MDLIB_LAYOUT(flag_SHIM_GRAPHICS, 1),
#else
    MDLIB_LAYOUT(flag_SHIM_GRAPHICS, 0),
#endif
#ifdef SHORT_FILENAMES
    MDLIB_LAYOUT(flag_SHORT_FILENAMES, 1),
#else
    MDLIB_LAYOUT(flag_SHORT_FILENAMES, 0),
#endif
#ifdef SND_LIB_FMOD
    MDLIB_LAYOUT(flag_SND_LIB_FMOD, 1),
#else
    MDLIB_LAYOUT(flag_SND_LIB_FMOD, 0),
#endif
#ifdef SND_LIB_MACSOUND
    MDLIB_LAYOUT(flag_SND_LIB_MACSOUND, 1),
#else
    MDLIB_LAYOUT(flag_SND_LIB_MACSOUND, 0),
#endif
#ifdef SND_LIB_MINIAUDIO
    MDLIB_LAYOUT(flag_SND_LIB_MINIAUDIO, 1),
#else
    MDLIB_LAYOUT(flag_SND_LIB_MINIAUDIO, 0),
#endif
#ifdef SND_LIB_OPENAL
    MDLIB_LAYOUT(flag_SND_LIB_OPENAL, 1),
#else
    MDLIB_LAYOUT(flag_SND_LIB_OPENAL, 0),
#endif
#ifdef SND_LIB_PORTAUDIO
    MDLIB_LAYOUT(flag_SND_LIB_PORTAUDIO, 1),
#else
    MDLIB_LAYOUT(flag_SND_LIB_PORTAUDIO, 0),
#endif
#ifdef SND_LIB_QTSOUND
    MDLIB_LAYOUT(flag_SND_LIB_QTSOUND, 1),
#else
    MDLIB_LAYOUT(flag_SND_LIB_QTSOUND, 0),
#endif
#ifdef SND_LIB_SDL_MIXER
    MDLIB_LAYOUT(flag_SND_LIB_SDL_MIXER, 1),
#else
    MDLIB_LAYOUT(flag_SND_LIB_SDL_MIXER, 0),
#endif
#ifdef SND_LIB_SOUND_ESCCODES
    MDLIB_LAYOUT(flag_SND_LIB_SOUND_ESCCODES, 1),
#else
    MDLIB_LAYOUT(flag_SND_LIB_SOUND_ESCCODES, 0),
#endif
#ifdef SND_LIB_VISSOUND
    MDLIB_LAYOUT(flag_SND_LIB_VISSOUND, 1),
#else
    MDLIB_LAYOUT(flag_SND_LIB_VISSOUND, 0),
#endif
#ifdef SND_LIB_WINDSOUND
    MDLIB_LAYOUT(flag_SND_LIB_WINDSOUND, 1),
#else
    MDLIB_LAYOUT(flag_SND_LIB_WINDSOUND, 0),
#endif
#ifdef STATUS_HILITES
    MDLIB_LAYOUT(flag_STATUS_HILITES, 1),
#else
    MDLIB_LAYOUT(flag_STATUS_HILITES, 0),
#endif
#ifdef SUSPEND
    MDLIB_LAYOUT(flag_SUSPEND, 1),
#else
    MDLIB_LAYOUT(flag_SUSPEND, 0),
#endif
#ifdef SYSCF
    MDLIB_LAYOUT(flag_SYSCF, 1),
#else
    MDLIB_LAYOUT(flag_SYSCF, 0),
#endif
#ifdef TERMINFO
    MDLIB_LAYOUT(flag_TERMINFO, 1),
#else
    MDLIB_LAYOUT(flag_TERMINFO, 0),
#endif
#ifdef TERMLIB
    MDLIB_LAYOUT(flag_TERMLIB, 1),
#else
    MDLIB_LAYOUT(flag_TERMLIB, 0),
#endif
#ifdef TIMED_DELAY
    MDLIB_LAYOUT(flag_TIMED_DELAY, 1),
#else
    MDLIB_LAYOUT(flag_TIMED_DELAY, 0),
#endif
#ifdef TTY_GRAPHICS
    MDLIB_LAYOUT(flag_TTY_GRAPHICS, 1),
#else
    MDLIB_LAYOUT(flag_TTY_GRAPHICS, 0),
#endif
#ifdef TTY_TILES_ESCCODES
    MDLIB_LAYOUT(flag_TTY_TILES_ESCCODES, 1),
#else
    MDLIB_LAYOUT(flag_TTY_TILES_ESCCODES, 0),
#endif
#ifdef UNIX
    MDLIB_LAYOUT(flag_UNIX, 1),
#else
    MDLIB_LAYOUT(flag_UNIX, 0),
#endif
#ifdef USER_SOUNDS
    MDLIB_LAYOUT(flag_USER_SOUNDS, 1),
#else
    MDLIB_LAYOUT(flag_USER_SOUNDS, 0),
#endif
#ifdef USE_ISAAC64
    MDLIB_LAYOUT(flag_USE_ISAAC64, 1),
#else
    MDLIB_LAYOUT(flag_USE_ISAAC64, 0),
#endif
#ifdef USE_XPM
    MDLIB_LAYOUT(flag_USE_XPM, 1),
#else
    MDLIB_LAYOUT(flag_USE_XPM, 0),
#endif
#ifdef VERSION_COMPATIBILITY
    MDLIB_LAYOUT(flag_VERSION_COMPATIBILITY, 1),
#else
    MDLIB_LAYOUT(flag_VERSION_COMPATIBILITY, 0),
#endif
#ifdef VERSION_IN_DLB_FILENAME
    MDLIB_LAYOUT(flag_VERSION_IN_DLB_FILENAME, 1),
#else
    MDLIB_LAYOUT(flag_VERSION_IN_DLB_FILENAME, 0),
#endif
#ifdef VISION_TABLES
    MDLIB_LAYOUT(flag_VISION_TABLES, 1),
#else
    MDLIB_LAYOUT(flag_VISION_TABLES, 0),
#endif
#ifdef VROOMM
    MDLIB_LAYOUT(flag_VROOMM, 1),
#else
    MDLIB_LAYOUT(flag_VROOMM, 0),
#endif
#ifdef WIN32
    MDLIB_LAYOUT(flag_WIN32, 1),
#else
    MDLIB_LAYOUT(flag_WIN32, 0),
#endif
#ifdef WIN32CON
    MDLIB_LAYOUT(flag_WIN32CON, 1),
#else
    MDLIB_LAYOUT(flag_WIN32CON, 0),
#endif
#ifdef X11_GRAPHICS
    MDLIB_LAYOUT(flag_X11_GRAPHICS, 1),
#else
    MDLIB_LAYOUT(flag_X11_GRAPHICS, 0),
#endif
#ifdef XLOGFILE
    MDLIB_LAYOUT(flag_XLOGFILE, 1),
#else
    MDLIB_LAYOUT(flag_XLOGFILE, 0),
#endif
#ifdef ZLIB_COMP
    MDLIB_LAYOUT(flag_ZLIB_COMP, 1),
#else
    MDLIB_LAYOUT(flag_ZLIB_COMP, 0),
#endif
#ifdef _MSC_VER
    MDLIB_LAYOUT(flag__MSC_VER, 1),
#else
    MDLIB_LAYOUT(flag__MSC_VER, 0),
#endif
#ifdef __DJGPP__
    MDLIB_LAYOUT(flag___DJGPP__, 1),
#else
    MDLIB_LAYOUT(flag___DJGPP__, 0),
#endif
};
#undef MDLIB_LAYOUT
static const struct { const char *name; const char *value; } mdlib_strings[] = {
    { "PORT_ID", PORT_ID },
    { "DEFAULT_WINDOW_SYS", DEFAULT_WINDOW_SYS },
#ifdef DEV_RANDOM
    { "DEV_RANDOM", DEV_RANDOM },
#endif
#ifdef PORT_SUB_ID
    { "PORT_SUB_ID", PORT_SUB_ID },
#endif
};
size_t probe_context_size(void) { return sizeof(struct version_info); }
int probe_layout_count(void) { return sizeof mdlib_layout / sizeof mdlib_layout[0]; }
const char *probe_layout_name(int index) { return mdlib_layout[index].name; }
size_t probe_layout_value(int index) { return mdlib_layout[index].value; }
int probe_string_count(void) { return sizeof mdlib_strings / sizeof mdlib_strings[0]; }
const char *probe_string_name(int index) { return mdlib_strings[index].name; }
const char *probe_string_value(int index) { return mdlib_strings[index].value; }
