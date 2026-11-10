# INVENT TU124/J130 private handoff

Status: FROZEN, private first-pass handoff. Final actual -O2 -g memory64
original-C/hybrid comparison passes 1,337 checks and invokes all119 configured
functions plus all20 native function identities. Fresh source/CPP/data/ABI,
source preservation, lexical scope and import/exclusion guards pass. All four
wrong JS variants fail the unchanged C comparison. Direct native-test mode
rejects before Module creation. No native/full-game/public result is claimed.
All final logs and input-hashes.json are in .cache/invent-first-pass/.

## Source and configuration

Pristine and prepared src/invent.c are identical, SHA256
`0b93d6ce1abb5b63ed7ea07c26a57e1016c6cef0fc2ef0e4016e6622054524b5`.
There are 119 configured bodies: 87 public and 32 private. Their names, order,
original parameters, block comments, source algorithms/data and macro control
flow remain in invent.js. The only formal-name exceptions are original `let`
to `let_` in xprname (third argument) and let_to_name (first argument).
Two declaration-scoped local `let` bindings in adjust_split/doorganize_core
also use let_; member fields named let are unchanged. No generic rename waiver.

The actual production profile is memory64, current compile-defines.json,
forced native-terminal.h, prepared and ncurses includes, cwd TREE/src, input
basename invent.c. MAIL_STRUCTURES, ENHANCED_SYMBOLS, DUMPLOG_CORE, ALTMETA,
UNIX, TTY_GRAPHICS, HANGUPHANDLING, DEBUG, NODIAG, MACOS, INSURANCE,
SAFERHANGUP and __EMSCRIPTEN__ are active. TTY_PERM_INVENT is INACTIVE,
as are DUMPLOG, OBSOLETE_HANDLING, CORE_INVENT and DLB/backends. Configured
permanent-inventory functions remain present; no inactive implementation was
enabled or counted. The initial source-only inference that TTY_PERM_INVENT
was active was corrected using actual CPP before implementation.

Source guards retain the complete configured compiler tree, 1,782 canonical
MemberExprs, 172 compound/inc/dec expressions, one char* += and two Loot* ++
operations. Loot stride is the actual 24 bytes. Two logged RNG origins are
invent.c:1550:currency and invent.c:1700:mime_action. Three obj_to_glyph calls
use the actual configured header expansions and display RNG; repeated operands
and live go.otg_temp/go.otg_otmp state remain JS. Snprintf owner/closing lines
are getobj:1975 and xprname:2886. No production compiler flag is changed.

## Integration-owner changes only

Use the adjacent invent-registry.json proposal (reference:pristine,
configuredFunctions:true). Add only the two exact formal exceptions to the
shared source checker. Add `invent: []` to the layout writer mapping: runtime
metadata is inline and queries its own compiler-indexed teleport_invent_layout
helper, with exact layout Number/LP64/signed-char/little-endian checks.

Import `{callInvent}` from `./invent-runtime.js` in the central runtime and
install `invent(services,name,...args){return callInvent(services,name,...args);}`
in Module.nethackPorted before source calls. Compile invent-support.c ONCE as
a separate production object via the existing nativeStorageSources contract.
Exclude original invent.c and include invent.js's JS library imports. Do NOT
also include this support fragment in common tu-support.c.

All eleven source globals and twelve static locals are private. Fixed native
backings are zero-only; JS owns their exact initializers and first-use choices,
once per Module before its first source entry. No owned public-storage startup
hook, malloc/OOM path, C source data mirror or source-algorithm fallback exists.
Typed/storage initialization calls cannot reenter. Source-private xprnctx is a
type-only ABI declaration in support; actual-original assertions are enabled
only by TELEPORT_INVENT_VALIDATE_ORIGINAL after the original INVENT include.
Generic TELEPORT_REFERENCE_TU never exposes private assertions to another TU.

Foreign WINDOWS zerowri is NOT redefined or initialized by production INVENT.
The already-selected WINDOWS startup and its mutable native 48-byte symbol
remain authoritative. prepare_perminvent performs the original full 48-byte
copy at its original source point, preserving all scalar/padding bytes and
private wri_info address identity. Its subsequent ctrl_nhwindow call reads
the live volatile callback field; returned null/backend/private aliases remain
raw typed native addresses. The fixture uses a separate optimized foreign
writer and an optimized C backend reading every copied byte, including tail
padding and a >53-bit signed-long flag. It does not independently rerun the
frozen WINDOWS startup algorithm.

The typed boundary comprises 52 record types / 212 fields, 53 foreign globals,
175 foreign dependencies, 136 variadic sites and 70 indirect callback sites.
Twenty source-used native function identities have exact C signatures; private
identities import teleport_invent_<name>. Genuine source callback declarations
and nested const qualifiers are retained. Long value formals currency.amount,
prinv.quan, xprname.cost/quan and useupf.numused, long* menu counts, long return
count_contents, object quantities/ages/masks and unsigned-long fields retain
BigInt transport. There is no args.map(ptr) conversion of mixed scalars.

Each JS source function owns its native automatic frame, including direct JS
calls within this TU. Fixed automatic slots are reserved once per invocation;
original initialization remains at its declaration. Only initialized `{0}`
aggregates are fully zeroed. Uninitialized source automatic arrays/scalars
are not generally initialized. Native heap views refresh after growth and
finally restores frame/context on callback throws; ordinary source state
restoration remains at the original normal-return points.

## Standalone builder and comparison

Add probes['invent'] = ([], ['call','reset','clear','option','buffer','record',
'trace','stack','snapshot','global','layout','address','write','read','chain',
'queue','property','foreign','input','callback','function','class','observe',
'offset','held','invoke']). Add INVENT to the self-contained standalone lists:
reference defines TELEPORT_REFERENCE_TU and includes the original source inside
tu-invent-probe.c; hybrid uses the owned JS library. Neither mode appends
original invent.c as another object, common support, or another support copy.

Link genuine prepared hacklib.c, strutil.c, objects.c, monst.c and drawing.c
objects plus invent-probe-consumer.c in BOTH fixture modes. The remaining game,
naming, ownership, command and menu dependencies are explicit controlled native
fixture boundaries, not claims of upstream subsystem equivalence. The original initialized, unshuffled real
catalogues, deterministic qsort, string/character helpers and libc are used.
The inherited prepared hacklib qsort wrapper has its original global comparator
state; arbitrary nested qsort reentry is not certified. Controlled reentry here
uses currency and preserves original source global-state timing.

Use -O2 -g, memory64, forced native-terminal.h/ncurses profile, modular Node,
memory growth, 1MiB stack, HEAPU8,FS,stackSave,stackRestore exports. Export malloc,
free and the probe APIs above. Only private fixture compilation maps the
artificial include spelling to the actual production basename:
`-fmacro-prefix-map=${ROOT}/scripts/../.cache/wasm64-build/tree/src/invent.c=invent.c`.
No production flag or source filename is normalized in observations.

Shared standalone test invocation MUST set INVENT_PROBE_DIR=.cache/tu-probes;
otherwise the owned test defaults to .cache/invent-first-pass. The test reads
owned compiler/schema metadata, not a private inventory cache. Direct
TELEPORT_NATIVE_TESTS=1 rejects before Module creation because no native fixture
exists. Do not add referenceBackend:native or label these EmC results native.

## Evidence and limits

Current functional corpus covers all 119 entrypoints, all 482 actual object
catalogue classifications, ratings/handedness, deterministic sorting/filtering/
nexthere traversal, nonempty object chains, signed64 quantities/ages and all
five long value formals, repeated native menu selection and split joins,
long output counts, logged/display RNG, callback growth/reentry/exceptions,
private static aliases, per-Module state and a 16-item constant stack-delta
witness. Known typed object identities alone are classified; unknown pointer
bits are read as BigUint64 first. A pair that collides under Number retains
different exact decimal IDs and raw eight bytes. Address-shaped scalar bytes
and padding remain raw. No unsafe observation pointer is dereferenced.

The broader corpus caught a parenthesized-pointer increment emitter defect in
tally_BUCX, producing NaN from a scalar treated as a cell. The corrected code
evaluates the actual native lvalue once and returns the original postfix value.
The original failure remains in test-debug.log; the same defect is deliberately
reproduced against the final unchanged reference in negative-loaded-scalar-as-cell.
Another fixture correction replaced literal backslash/octal text in its pack
order with valid native object-class codes; this was controlled-world setup,
not an expected-result or upstream change.

Four wrong-code variants are required to fail the unchanged suite: rounded
signed64 cost, partial 32/48-byte request copy, loaded scalar used as an lvalue
cell, and repeated stack allocation of a fixed automatic. negative-proof.json
records identical reference WASM hashes before/after each run and exact failure
titles. Final negative reproof uses the same reference SHA before/after all four variants;
see negative-proof.json and final-hashes.txt. All final checks ran after explicit
CLEAR. No new heavy job ran during the parent's timing quiet window.

Invoking every function is not exhaustive branch coverage. Native executable,
full game/public tests, arbitrary foreign engine/ownership/naming behavior,
all complex recursive merge/destruction cases, undefined signed overflow,
uninitialized/invalid caller behavior and arbitrary nested sorting reentry
remain unverified. No expected-result waiver or platform mismatch normalization
is introduced. All selected/shared/frozen FILES and other TU files remain intact.
