# Pinned macOS terminal data

`x/xterm-256color` is copied verbatim from
`/usr/share/terminfo/78/xterm-256color` on macOS 26.6.2 (25G83).
SHA-256: `e2525d133091a1ac38b2ad4eecd8df48eee31789c8fafac0ed99bcd6b746d8ce`.
`xterm-256color.src` is the human-readable `/usr/bin/infocmp -1` export.
The system infocmp reports ncurses 6.0.20150808. The historical recording
machine's precise database/library version is not established.

The build embeds the compiled entry into MEMFS at
`/nethack/terminfo/x/xterm-256color`. Real ncurses 6.5 terminfo reads it using
`TERMINFO=/nethack/terminfo`; no ANSI fallback table or substitute tparm/tputs
implementation is used. Only xterm-256color is packaged, matching the documented
recording TERM. Other entries can be supplied to the real database reader but
are not currently packaged. LINES=24 and COLUMNS=80 specify the recorded size.

ncurses source: https://ftp.gnu.org/gnu/ncurses/ncurses-6.5.tar.gz
SHA-256: `136d91bc269a9a5785e5f9e980bc76ab57428f604ce3e5a5a90cebc767971cc6`.
`LICENSE.ncurses` preserves the source distribution's license. Source is fetched
into `.cache` by `nethack-c/setup-terminfo.sh`; `build_terminfo.py` configures and
builds its unpatched terminfo library with `-sMEMORY64=1` and the normal binary
database reader enabled. Optional curses UI/programs/tests/C++/Ada are excluded;
wide-character curses support and HOME terminfo search are disabled. These are
library build choices, not modifications to NetHack's capability selection.

`python3 scripts/test-terminfo.py` (with the SDK Node on PATH) compares all
capabilities NetHack queries, color parameter expansion for all 256 indices,
cursor addressing, RGB initialization and tputs against the native ncurses
library using this same entry. It also checks unknown terminals are rejected.
