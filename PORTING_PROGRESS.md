# Translation-unit migration

Reference: NetHack `16ff59115315917b93185d026aeefea06db9b0f4` plus the six
contest patches and documented platform adaptations. Full divergence inventory:
[UPSTREAM_DIVERGENCES.md](UPSTREAM_DIVERGENCES.md).

Each C function retains one JS function with the same name and boundaries.
Keep comments, names and control flow; record necessary C/JS differences.
Bindings, layout access and test helpers belong outside the translated file.
Proceed sequentially: original-C differential checks → real mixed C/JS link →
full public tests. A failing gate blocks the next TU.

| Order | C TU | JS replacement | State | Validation |
|---|---|---|---|---|
| 1 | src/isaac64.c | js/ported/isaac64.js | Passed | 39,830 C/hybrid output/state comparisons; actual C object excluded and JS imports verified; 44/44 public sessions; integration suite passed |
| 2 | src/nhmd4.c | js/ported/nhmd4.js | Passed | Four identical function boundaries; 1,287 C/hybrid state/digest checks including RFC vectors; actual C object excluded and all three public JS imports verified; 44/44 public sessions; integration suite passed |
| 3 | src/strutil.c | js/ported/strutil.js | Passed | Nine original functions/comments preserved; 8,352 C/hybrid buffer/pattern/guard comparisons; clean build with C object excluded and active JS imports verified; 44/44 public sessions; integration suite passed |
| 4 | src/rect.c | js/ported/rect.js | Passed | Ten original functions/comments; 3,644 C/hybrid geometry/state/pointer/RNG comparisons; mixed link excludes C object and uses active JS imports; 44/44 public sessions; integration suite passed |
| 5 | src/track.c | js/ported/track.js | Passed | Six original functions/comments; 11,835 C/hybrid ring/state/pointer/save comparisons; C object excluded and all six game JS imports verified; 44/44 public sessions; integration suite passed |
| 6 | src/calendar.c | js/ported/calendar.js | Passed | Eleven original functions/comments; 9,116 effective-C/hybrid comparisons in five zones; mixed link excludes C object; 44/44 public sessions; integration suite passed |
| 7 | src/stairs.c | js/ported/stairs.js | Passed | Seventeen original functions/comments; 3,830 C/hybrid list/pointer/placement/description comparisons; all17 game JS imports verified and C object excluded; 44/44 public sessions; integration suite passed |

| 8 | src/sys.c | js/ported/sys.js | Passed | Three original functions/comments; 183 C/hybrid configuration/environment/cleanup comparisons; all three JS imports verified, C object excluded; 44/44 public sessions; integration suite passed |

| 9 | src/rip.c | js/ported/rip.js | Passed | Two original functions/comments; 501 byte-exact C/hybrid tombstone/callback/cleanup comparisons; game imports genl_outrip and excludes rip.o; 44/44 public sessions; integration suite passed |

| 10 | src/date.c | js/ported/date.js | Passed | JS-authoritative 12-field initializer and two unchanged functions fully revalidated (J22). Two original functions/comments; 2,645 effective-C/hybrid comparisons in five zones; both game JS imports verified and separate DATE_O excluded; 44/44 public sessions; integration suite passed |

| 11 | src/alloc.c | js/ported/alloc.js | Passed | Six configured functions/comments; 201 C/hybrid allocation/failure/cast/pointer-pool checks incl nested scopes; C object excluded, five live game imports (unused FITSuint_ tested in probe); 44/44 public sessions; integration suite passed |

| 12 | src/utf8map.c | js/ported/utf8map.js | Passed | Six original functions/comments; 817 C/hybrid parser/byte/map/list/callback checks; all six game imports verified, C object excluded; 44/44 public sessions; integration suite passed |

| 13 | src/drawing.c | js/ported/drawing.js | Passed | Three original functions/comments and five JS-authoritative tables; 3,226 C/hybrid startup/data/alias/lookup checks; all three game imports verified, drawing.o excluded; 44/44 public sessions; integration suite passed |

| 14 | sys/share/posixregex.c | js/ported/posixregex.js | Passed | Five original functions/parameters/comments and JS engine identifier; 967 C/hybrid native-regex/error/lifecycle checks; all five game imports verified, C object excluded; 44/44 public sessions; integration suite passed |

| 15 | src/rnd.c | js/ported/rnd.js | Passed | Twenty effective functions/parameters/comments incl inherited recorder logger; 962 full-state/log/operation C/hybrid comparisons incl 50k logged shuffle; rnd.o excluded, 14 live game imports (remaining APIs tested in probes); 44/44 public sessions; integration suite passed |

| 16 | sys/share/ioctl.c | js/ported/ioctl.js | Passed | Four configured functions/parameters/comments; 314 C/hybrid termios/order/auth/signal checks; all four game imports verified, ioctl.o excluded; 44/44 public sessions; integration suite passed |

| 17 | sys/share/unixtty.c | js/ported/unixtty.js | Passed | Nine effective configured functions/parameters and 52 comments; 1,279 terminal-byte/order/variadic/nested-cleanup C/hybrid comparisons; all seven external game JS imports verified, unixtty.o excluded; 44/44 public sessions; integration suite passed |

| 18 | src/were.c | js/ported/were.js | Passed | Eight original functions/parameters/comments; 11,206 C/hybrid mapping/state/property/summoning/callback/RNG-site comparisons; all eight game imports verified, were.o excluded; 44/44 public sessions; full integration suite passed (11,176 checks before final edge-case additions, latest direct suite 11,206) |

| 19 | src/extralev.c | js/ported/extralev.js | Passed | Six original functions/parameters and 18 comments; 1,221 C/hybrid full-grid/terrain/room/corridor/ghost/RNG comparisons; two live game imports verified, extralev.o and private test imports excluded; 44/44 public sessions; full integration suite passed |

| 20 | src/mplayer.c | js/ported/mplayer.js | Passed | Six original functions/parameters and 31 comments; 58 authoritative names, six messages; 10,310 C/hybrid naming/equipment/copy/retry/talk/RNG checks; all three game imports verified, mplayer.o/test imports excluded; clean rebuild identical to incremental; 44/44 public sessions; full integration suite passed |

| 21 | src/exper.c | js/ported/exper.js | Passed | Nine original functions/parameters and 48 comments; 9,344 C/hybrid threshold/energy/XP/level/assert/RNG comparisons; all eight game imports verified, exper.o/private test import excluded; 44/44 public sessions; full integration suite passed |


| 22 | src/mkmap.c | js/ported/mkmap.js | Passed | Fourteen original functions/parameters and 42 comments; 807 C/hybrid terrain/buffer/flood/room-copy/lighting/RNG comparisons; three live game imports verified, mkmap.o/private test imports excluded; 44/44 public sessions; full integration suite passed incl latest 9,412-check exper suite |

| 23 | win/tty/getline.c | js/ported/getline.js | Passed | Five configured functions and 40 comments; 930 C/hybrid input/completion/history/wait/state comparisons including 6,000 hooks in one request; three game imports verified, getline.o/private test imports excluded; 44/44 public sessions; full integration suite passed |

| 24 | src/write.c | js/ported/write.js | Passed | Four original functions/parameters/comments; 3,553 C/hybrid cost/selection/naming/ink/knowledge/conduct/trace comparisons; game imports dowrite and private callback bridge, write.o/test imports excluded; 44/44 public sessions; full integration suite passed at 3,283 comparisons before final knowledge-matrix addition |

| 25 | src/mdlib.c | js/ported/mdlib.js | Passed | Thirteen configured functions and all authoritative metadata tables; 1,214 C/hybrid table/version/wrapping/lifecycle/native-format comparisons; four live game imports verified, mdlib.o/test imports excluded; shared game/probe/source-check defines aligned; clean rebuild matches incremental exactly; 44/44 public sessions; full integration suite passed |

| 26 | src/quest.c | js/ported/quest.js | Passed | Twenty-two original functions/parameters/comments; 10,992 C/hybrid state/dispatch/dialogue/portal/cloud/monster/RNG comparisons; ten live game imports verified, quest.o/private test imports excluded; 44/44 public sessions; full integration suite passed |

| 27 | src/minion.c | js/ported/minion.js | Passed | Fourteen original functions/parameters/28 comments and authoritative elemental table; 8,142 C/hybrid extension/summon/bribe/scanf/guardian/RNG comparisons; eleven live game imports verified, minion.o excluded; 44/44 public sessions; full integration suite passed |

| 28 | src/iactions.c | js/ported/iactions.js | Passed | Five original functions/84 comments and authoritative action/naming constants; 12,451 C/hybrid catalogue/menu/ownership/command/growth comparisons; one live game import, iactions.o/private test imports excluded; 44/44 public sessions; full integration passed |

| 29 | src/selvar.c | js/ported/selvar.js | Passed | Twenty-six original functions/comments; 4,781 C/hybrid map/bounds/geometry/float32/callback/RNG comparisons; 23 active game imports, selvar.o/private test imports excluded; 44/44 public sessions; full integration passed |

| 30 | src/steal.c | js/ported/steal.js | Passed | Sixteen original functions/comments; 6,612 C/hybrid inventory/equipment/ownership/gold/callback/RNG comparisons; 15 active game imports, steal.o/private test imports excluded; 44/44 public sessions; full integration passed |

| 31 | src/sit.c | js/ported/sit.js | Passed | Seven original functions/comments; 4,190 C/hybrid throne/terrain/egg/property/curse/RNG comparisons; four active game imports, sit.o/private test imports excluded; 44/44 public sessions; full integration and lexical-scope checks passed |

| 32 | src/fountain.c | js/ported/fountain.js | Passed | Sixteen original functions/comments; 6,766 C/hybrid fountain/sink/callback/inventory/RNG comparisons; ten public plus two callback imports, fountain.o/private tests excluded; 44/44 public sessions; full integration passed |

| 33 | src/objects.c | js/ported/objects.js | Passed | One original function/two native copies; 482 authoritative JS data rows; 16,882 C/hybrid field/string/padding/reset/isolation comparisons; objects.o excluded, import verified; 44/44 public sessions; full integration passed |

| 34 | src/monst.c | js/ported/monst.js | Passed | One original function/copy/return; 384 authoritative JS rows and both static attack tables; 17,683 C/hybrid startup/fields/flags/padding/reset/isolation comparisons; monst.o excluded, import verified; 44/44 public sessions; full integration passed |

| 35 | src/shknam.c | js/ported/shknam.js | Passed | Seventeen configured functions/all tables/comments; 23,507 C/hybrid names/stock/geometry/true-free/RNG/lifetime comparisons; eight live imports, shknam.o/private tests excluded; 44/44 public sessions; full integration passed |

| 36 | src/rumors.c | js/ported/rumors.js | Passed | Seventeen configured functions/comments; 2,178 C/hybrid native-file/oracle/consultation/cache/ownership/RNG comparisons; nine live imports, rumors.o/private tests excluded; 44/44 public sessions; full integration passed |

| 37 | src/music.c | js/ported/music.js | Passed | Fourteen configured functions/comments; 5,687 C/hybrid monster/pit/quake/instrument/tune/RNG comparisons; two live imports, music.o/private tests excluded; 44/44 public sessions; full integration passed |

| 38 | src/version.c | js/ported/version.js | Passed | Eighteen configured functions/comments; 80 JS-owned critical-size rows; 6,513 C/hybrid startup/string/header/validation comparisons; 12 live imports, version.o/private test excluded; real clipboard copy/show integration; 44/44 public sessions; full integration passed |

| 39 | src/coloratt.c | js/ported/coloratt.js | Passed | Twenty-four configured functions/comments; four JS-owned catalogues; 7,753 C/hybrid data/parser/POSIX/menu/ownership/RGB comparisons; 18 live imports, coloratt.o excluded; 44/44 public sessions; full integration passed |

| 40 | src/priest.c | js/ported/priest.js | Passed | Twenty-three configured functions/comments; 9,358 C/hybrid extension/movement/temple/donation/ownership/RNG comparisons; 20 live imports, priest.o/private test imports excluded; 44/44 public sessions; full integration passed |

| 41 | src/light.c | js/ported/light.js | Passed | Twenty-nine configured functions/comments; 2,576 C/hybrid list/map/union/save/relink/ownership/callback comparisons; 22 live imports, light.o/six private imports excluded; 44/44 public sessions; full integration passed |

| 42 | src/lock.c | js/ported/lock.js | Passed | Twenty configured functions/comments; 5,687 C/hybrid lock/door/occupation/RNG/ownership/callback comparisons; 15 public plus two occupation imports, lock.o/five private aliases excluded; 44/44 public sessions; full integration passed |

| 43 | src/steed.c | js/ported/steed.js | Passed | Fifteen configured functions/comments; 7,474 C/hybrid saddle/riding/dismount/grid/property/RNG/callback comparisons; 12 live imports, steed.o/two private aliases excluded; 44/44 public sessions; full integration passed |

| 44 | src/wizard.c | js/ported/wizard.js | Passed | Twenty-one configured functions/four JS tables; 4,800 C/hybrid comparisons; 14 live imports, wizard.o/seven private imports excluded; 44/44 public sessions; full integration passed |

| 45 | src/worm.c | js/ported/worm.js | Passed | Twenty-seven configured functions; 2,995 C/hybrid segment/grid/ownership/serialization/callback comparisons; 24 live imports, worm.o/six private test hooks excluded; 44/44 public sessions; full integration passed |

| 46 | src/o_init.c | js/ported/o_init.js | Passed | Twenty-seven configured functions/five private tables; 6,636 C/hybrid catalogue/name/menu/sort/serialization/callback comparisons; 15 public plus comparator imports, o_init.o/11 private aliases excluded; 44/44 public sessions; full integration passed |

| 47 | src/ball.c | js/ported/ball.js | Passed | Seventeen configured functions; 4,339 C/hybrid placement/drag/fall/restriction/alias/callback comparisons; all12 public imports, ball.o/six test hooks excluded; 44/44 public sessions; full integration passed |

The user requested continuous work up to 1,000 TUs. Inventory: 306 pristine
upstream C source files, 130 under src; the checkout cannot supply 1,000
distinct original C files. Continue through the available inventory without
stopping at milestone counts. Source files for inactive targets are not
claimed as completed game TUs merely because they exist.

| 48 | src/mcastu.c | js/ported/mcastu.js | Passed | Twenty-six configured functions/three source tables; 5,406 C/hybrid spell/damage/status/summoning/RNG/callback comparisons; all4 public imports, mcastu.o/22 private aliases excluded; 44/44 public sessions; full integration passed |

| 49 | src/dbridge.c | js/ported/dbridge.js | Passed | Twenty-eight configured functions; 11,669 C/hybrid terrain/entity/alias/transition/RNG/callback comparisons; all14 public imports, dbridge.o/14 private aliases excluded; 44/44 public sessions; full integration passed |

| 50 | src/mondata.c | js/ported/mondata.js | In progress | Fifty-nine configured monster-data/predicate/name functions and original source tables; gates pending |

Forty-nine configured game TUs have passed. The runtime still
contains the remaining NetHack C, Lua, ncurses and compression code.

Reproduce from the prepared SDK: `bash nethack-c/build-wasm.sh`, then
`bash scripts/test-wasm.sh` and `bash scripts/score-wasm.sh`. The TU probes use
the original C as their oracle and C callers to invoke JS through the real ABI.
A full clean build passed again at TU 25 and reproduced the incremental Wasm
hash exactly. Both public and integration suites passed again on that artifact.
All completed JS replacements remain excluded from the game link; C versions
are used by native utilities and differential probes.
Per-build evidence lives in `js/wasm/build.json` (source hashes) and
`js/wasm/link-objects.txt` (actual game HOBJ list). Last logs:
`.cache/build-wasm-dbridge.log`, `.cache/test-wasm-dbridge.log`,
`.cache/dbridge-public.stderr.txt`. Latest validated Wasm SHA-256:
`a62a9eafa669c48aef3d8fee5847ec4078313f9a24f060e1504af449c358b405`.

