# WINDOWS frozen first-pass handoff — 73 configured functions

Final actual -O2 memory64 original-C/hybrid suite passes **9,209 comparisons**,
all73 bodies invoked. Source/comment/parameter/order/scope/CPP/data guards pass.
Exact production filename is now verified: fresh CPP runs in TREE/src with input
`windows.c`; owned source-data header agrees; PRIVATE fixture uses an exact
macro-prefix-map of its artificial include path to that production basename.
Both rebuilt Wasm binaries contain exactly `windows.c`; full filename trace
compares without basename normalization. Evidence:
`.cache/windows-first-pass/debug-origin-proof.json`.

Historical coverage gap is retained: the earlier9209 suite logged only basename,
while old raw reference embedded `scripts/../.cache/.../windows.c` and old hybrid
used canonical absolute path. Raw strings/hashes and explicit limitation remain
in debug-origin-coverage-gap.json. That diagnostic is superseded by the rebuilt
full-filename proof, not reclassified as original exact-origin coverage.
No production compiler flags changed. Parent integration remains unapplied.

## Exact integration contract (root-owned shared edits)

Registry:

    {"name":"windows","source":"src/windows.c",
     "javascript":"js/ported/windows.js",
     "library":"nethack-c/wasm/tu-libraries/windows.js",
     "configuredFunctions":true,"reference":"prepared"}

Import `callWindows` from './windows-runtime.js'. The actual binding dispatcher
and its startup callback both require this exact central method:

    windows(services,name,...args) {
        if (!layouts.windows) throw new Error('Missing WINDOWS layout');
        return callWindows(services,layouts.windows,name,...args);
    }

The owned library already includes `$teleportWindowsInit` and its addOnInit
postset calling `Module.nethackPorted.windows(teleportWindowsServices(),
'initialize')`. Link dependency is retained by every `$teleportWindowsCall`.
Install the central dispatcher before instantiating the Module. Initialization
runs before main/normal C callers; do not rely only on first WINDOWS entry.
`initializeWindows(services,layout)` is exported for explicit hosts; initialization
is once per actual Module (WeakMap), including repeated calls/reentry.
A separate optimized C consumer copies `zerowri` exactly like invent.c and
reads shared tty status arrays. Test reads NO_COLOR immediately after Module
resolves, BEFORE explicit initialization or any original WINDOWS body.
The startup hook follows the existing addOnInit contract; it does not claim to
initialize data before arbitrary foreign Wasm constructors which might precede
addOnInit. No such zerowri consumer was identified in the configured source.

Include `#include "tu-fragments/windows-support.c"` once in common tu-support.c.
Its source-data header guards the actual production debug filename. It defines
mutable ZERO-ONLY public symbols windowprocs (volatile), status_fieldnm,
status_fieldfmt,status_vals,status_activefields and zerowri, retaining original
C symbol addresses. Public definitions are excluded for generic reference
probes; private-source assertions use **TELEPORT_WINDOWS_VALIDATE_SOURCE only**,
immediately after actual original windows.c in the WINDOWS reference fixture.
Do not leak private struct win_choices checks into other reference probes.
All initialized source tables/data are JS, with fixed mutable zero-only storage
for two choices,HUP/backup tables,20-byte encbuf and43 literals/662bytes.
`zerowri` is actually mutable in wintype.h; no separate const storage TU/noLTO
exception is needed. Typed volatile struct assignment preserves complete proc
copies before undo/init/previous-interface callbacks. No initialized C mirror,
WINDOWS parser/status/menu/hangup fallback or original windows.o in hybrid.

Flat `_probe_layout_name/value` through `_probe_layout_count` becomes
layouts.windows. It contains actual compiler constants/sizes; runtime uses
actual typed C field access instead of guessed layout offsets.91 services,
51 proc fields/46 callback signatures,18 live global paths, other typed records,
unsigned64 capabilities/menu behavior and signed64 status flags/time/counts.
Actual source bool/char/coordxy narrowing remains in typed ABI; has_color's
C logical expression keeps short circuit and converts final value to0/1.
Internal JS-to-JS C calls materialize literal strings, including empty strings,
as stable nonnull C pointers and release original callee automatic storage.

Source checker exception: ONLY genl_message_menu parameter0 C `let` maps to JS
`let_`; parameters1/2 remain how/mesg. Add this exact named exception to the shared
source checker; no general parameter-renaming waiver. Original compiler linkage
is35 public/38 private; hup_ctrl_nhwindow inherits static from its prototype.
Every configured original function/name/order/comments/control remains JS.

Public original35:
`genl_can_suspend_no genl_can_suspend_yes check_tty_wincap check_tty_wincap2
choose_windows genl_message_menu genl_preference_update genl_getmsghistory
genl_putmsghistory nhwindows_hangup genl_status_init genl_status_finish
genl_status_enablefield genl_status_update dump_open_log dump_close_log
dump_forward_putstr dump_redirect has_color glyph2ttychar glyph2symidx encglyph
decode_glyph decode_mixed genl_putmixed genl_display_file menuitem_invert_test
mixed_to_glyphinfo choose_classes_menu adjust_menu_promptstyle add_menu
add_menu_heading add_menu_str select_menu getlin`.
Private C aliases use `teleport_windows_callback_` plus original name (38).
`teleport_windows_initialize` is the explicit startup ABI alias. Function-address
metadata intentionally makes all73 entries addressable; do not claim private
aliases dead-strip. Original bodies remain JS even when referenced by C tables.

Probe exports `_probe_` plus malloc/free:
`initialize clear reset buffer option field queue menucolor storage consumer
dump call trace snapshot stack layout_count layout_name layout_value callback_id
null_status_format enc_alias`.

Both modes compile scripts/tu-windows-probe.c plus actual prepared drawing.c,
hacklib.c and `tu-fragments/windows-probe-consumer.c` as a separate optimized C
TU (noLTO). No ordinary windows.c source argument: reference fixture includes
it once with TELEPORT_REFERENCE_TU, hybrid excludes it and uses owned JS library.
Fixture includes support itself, so add WINDOWS to common-support/source-include
exceptions rather than link shared support twice. Headers include actual
ncurses-wasm64-build/include for configured wintty.h. Flags: current
compile-defines.json, memory64, forced native-terminal.h,1MiB stack,heap growth,
`-Dfree=teleport_probe_free -Dputs=teleport_probe_puts
-Dfopen=teleport_probe_fopen -Dfgets=teleport_probe_fgets
-Dfclose=teleport_probe_fclose -Dfputs=teleport_probe_fputs
-Dfprintf=teleport_probe_fprintf`. Exact private-only source map:
`-fmacro-prefix-map=<absolute root>/scripts/../.cache/wasm64-build/tree/src/windows.c=windows.c`.
Optional private `-DWINDOWS_SOURCE_FILE="windows.c"` agrees with guarded header.
No prefix map or new flag belongs in production. Exact private build script:
`.cache/windows-first-pass/build.py`.
Run shared proof explicitly with `WINDOWS_PROBE_DIR=.cache/tu-probes
TELEPORT_NATIVE_TESTS=0 node scripts/test-tu-windows.mjs`; private reproduction
uses WINDOWS_PROBE_DIR=.cache/windows-first-pass (also the default).
TELEPORT_NATIVE_TESTS=1 is rejected before Module creation: no native fixture
backend exists. Do not let shared proof silently reuse the private default. Guard source: windows-source-check.mjs plus existing source/
comment/parameter/order and lexical gates. Include all owned source/data/ABI/
probe consumer/guard files in provenance. No shared artifacts were edited here.

## Evidence, diagnostics and limitations

9,209 final original -O2 memory64 C↔JS comparisons/all73 functions, including
exact full production debug filename after the targeted recheck. All46 callbacks/identity after choose,hup and dump copies;
previous exit/history preservation; public status fields,condition masks,layout
orders and valid array alias mutation;64bit capabilities and external zerowri
copy; glyph encode/decode/mixed escapes,static buffer alias; class menus/colors,
select pointers/counts,actual CMDQ_KEY queue ownership; controlled file/errors,
1,200-entry real C callback-relative SP lifetime; memory growth/reentry/foreign
throws/environment restoration; distinct Module state are exercised.

Source/data guard passes73 function inventory,51 fields/46 callbacks,two exact
choices,HUP initializer,5x15 fieldorder,source zerowri,four public status arrays,
20-byte encbuf,18 complete globals,43 exact literals/662bytes,actual profile.
TTY_GRAPHICS/HANGUPHANDLING/STATUS_HILITES/CLIPPING/SYSCF/SAFERHANGUP/
ENHANCED_SYMBOLS/ALTMETA/DEBUG active; WINCHAIN/DUMPLOG/DUMPHTML/other graphics/
POSITIONBAR/CHANGE_COLOR/TTY_PERM_INVENT/DLB/TERMLIB/NO_TERMS inactive.
The dump wrappers remain configured; dump_open_log is correctly a no-op with
DUMPLOG off. Tests inject a controlled private FILE pointer for dump wrappers;
this is not a claim of enabled DUMPLOG/DUMPHTML support. Header dlb aliases map
to ordinary stdio because DLB is off. No RNG sites occur in this TU.

Wrong-JS startup initializer NO_COLOR→0 fails unchanged C/foreign consumer:
0 versus8, BEFORE any original body. Wrong internal callee stack restoration
fails unchanged C trace: first delta0 then -32,-64,... versus original0 each.
Wrong private choice record size compile-rejected; generic reference support-only
syntax passes without original private types. Both startup and scope negatives were repeated against the final rebuilt C
artifacts and unchanged final suite; both reject the faulty JS copies.

An intentionally invalid fmt=NULL call to genl_status_enablefield is NOT a valid
parity case: configured extern.h applies NONNULLPTRS to its pointer arguments2/3;
actual Clang AST shows inherited NonNullAttr (no explicit indices means all
pointer parameters), and direct NULL argument3 is rejected by -Werror=nonnull.
The original O2 discrepancy (empty versus x) remains in invalid-null-enablefield.log;
nonnull-compile.log and nonnull-ast.log prove the contract. A separate valid test
calls enablefield with nonnull arguments, then mutates public status_fieldfmt
through its C alias toNULL and compares update's original fallback. It is not
reported as null-enablefield-call coverage. No C oracle or expectation is waived.

Remaining: native-host,production
mixed game/public recordings,foreign tty/invent end-to-end behavior and all
malformed inputs/OOM are not verified. True foreign drawing/hacklib C is linked;
window callbacks,regex results,map_glyphinfo,queue,allocator and stdio are
controlled fixtures. No real terminal/OS messages are sent. Foreign JS throws
are diagnostic fault injection, not a portable native C exception claim.
Final input/artifact hashes are in `.cache/windows-first-pass/input-hashes.json`.
Reference Wasm99e63d3f901e3b854c4e00521445369de11fb47e262af0a482454ab26b164281;
hybridaf82ec608792211153a518c95eb245c4f408b749b5e942ab3a8fb2d84fc9d0fe.
Historical
native53 evidence does not cover this TU. No selected/frozen files were edited.
