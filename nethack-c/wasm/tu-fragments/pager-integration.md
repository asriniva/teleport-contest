# PAGER TU103/J109 frozen first-pass handoff

Prepared/pristine src/pager.c are identical, 2,967 lines, SHA256
92d078a4c4e0f81bf91c07b91383e848427eeed37b9877fa34d8564774b8952b.
The core preserves46 configured boundaries (16 public/30 private), original
names/order/parameters/comments, source data, map/help/parser/control paths.
The configured monhealthdescr body is deliberately the original empty health
stub; disabled #if0 health logic, PORT_HELP, DLB and interpreter code are absent.
Native-macOS, full-game/public, and uncontrolled foreign-world parity remain
pending. All present behavior comparisons use actual memory64 Emscripten C.
No shared registry/builder/support/runtime or selected/frozen file was edited.

## Integration-owner changes only

Registry:

    {"name":"pager","source":"src/pager.c",
     "javascript":"js/ported/pager.js",
     "library":"nethack-c/wasm/tu-libraries/pager.js",
     "configuredFunctions":true,"reference":"prepared","probeContext":false,
     "startup":"$teleportPagerInit",
     "nativeStorageSources":[{"source":"nethack-c/wasm/tu-fragments/pager-storage.c",
                              "defines":["TELEPORT_PORT_PAGER_STORAGE"]}]}

Compile pager-storage.c SEPARATELY, no LTO. It has only zero backing for the
public const char what_is_a_location[30], with no initialized C mirror. All
native readers see extern-only storage. JS owns the initializer; the startup
library postset uses addOnInit to run __init before main/normal foreign callers.
Install Module.nethackPorted.pager before factory initialization. This does not
claim initialization before arbitrary earlier Wasm constructors; no configured
constructor consumer of this array was identified. Frozen GETPOS has a real
normal-call extern consumer. A separately optimized fixture consumer reads all30
bytes immediately after factory resolution, before reset or any PAGER body.

Central runtime: import createPagerBridge from './ported/pager-runtime.js',
construct callPager=createPagerBridge(layouts.pager) once after layouts load,
then dispatch pager(services,name,...args){return callPager(services,name,...args)}.
Inline runtime metadata has no JSON-module import. Decode teleport_pager_layout
from scripts/tu-pager-layout.h using compiler-derived name/long64 entries.
There are no parameter-name checker exceptions.

Include tu-fragments/pager-support.c once in shared C support. Its helpers only
expose typed fields/globals/arrays/function pointers/header macros/dependencies,
native copies and zero-only static/literal storage. No PAGER source algorithm or
initialized original table lives in C. No source-private type is exposed under
generic TELEPORT_REFERENCE_TU; the owned probe includes original pager.c only
for the reference, then applies its TU-specific validation/static assertion.
The source-private help function addresses need the library's
teleport_pager_callback_<name> imports; other private aliases are probe entries.
No original pager object may be linked into the hybrid or game.

adapterSources: js/ported/pager-runtime.js, scripts/tu-pager-layout.h,
nethack-c/wasm/tu-fragments/pager-support.c, pager-storage.c,
pager-probe-consumer.c, pager-source-data.json, pager-source-check.py,
pager-abi.json, pager-probe-options.json (last paths share that fragment folder).
Include all these and the core/library/probe/test in provenance.

## ABI and source-evaluation details

Both do_screen_description and private add_cmap_descr take real coord by value.
Actual LLVM ABI is a byval pointer (align2), not packed i32. JS source-local
calls clone compiler-size coord bytes before entering the callee; callbacks can
retain/change the caller's coord without changing the callee's value copy.
The actual configured compiler/AST, signed16 coordinates, signed8 boolean/char,
unsigned8 uchar, unsigned32 flags and signed/unsigned64 fields govern transport.
Unsigned-byte command keys narrow before crossing typed C helper entries; LLVM
assumes the declared narrow argument contract. Properties and quantity/ice time
retain BigInt width. Header symbols remain real current C globals/aliases.

mon_to_glyph(u.ustuck,rn2_on_display_rng) is an actual header expansion in the
typed helper, retaining the LIVE original u.ustuck expression. The eager a0
parameter is deliberately not substituted into that macro. C + operands do not
specify evaluation order: the original and hybrid are compared under the same
actual configured O2 compiler, including a display-RNG callback which changes
u.ustuck. No native-compiler ordering claim is made. Other header macros retain
actual C expansion; fresh source guards record1013 MemberExpr/type/alias uses.
There are zero source-owned logged RNG sites; the true display-RNG callback
and foreign rndmonnam retain their native function identities.

C owns libc formatting and real stdio; JS owns all original file parsing,
prefix/suffix handling, sscanf decisions, loops, errors and ordered cleanup.
Variadic argument areas use the compiler's memory64 slots and restore at the
callee boundary; libc sprintf/sscanf and true nh_snprintf/pline/impossible receive
actual native argument areas. Snprintf forwards exact original function and
closing-line metadata. No C parser/policy helper replaces checkfile.

Original automatic char declarations get keyed native slots within ONE source
invocation, reused across loop iterations; recursive/reentrant invocations get
separate frames. This prevents unbounded checkfile entry_count from retaining a
new tabbuf every line. DUMMY={0} zeros the whole original array. Static pooltype,
look_buf and declared string arrays have fixed zero-only native storage; no lazy
malloc/OOM behavior is introduced. Empty literal pointers remain non-null.
Volatile windowprocs are read by typed C wrappers at each call. Pointer records
retain canonical native identities. Callback growth refreshes heap views.

Actual AST pointer arithmetic has17 += operations (all checkfile char*) and8
++ operations (7 checkfile,1 whatdoes_help, all char*). All have native byte
scale1; no non-byte pointer compound/increment exists. The owned guard rejects
inventory/type changes so future pointer element scaling cannot silently drift.

## Exact standalone fixture build/test wiring

Private build script .cache/pager-first-pass/build.py documents actual flags.
Build the probe with memory64,-O2,-g, forced native-terminal.h, current
compile-defines.json, prepared includes and ncurses includes. Production profile
is cwd TREE/src, input basename pager.c. PRIVATE reference include maps its exact
artificial scripts/../.cache/.../pager.c spelling to pager.c; no production flag
change. Link actual foreign hacklib.c, strutil.c (including genuine pmatch), drawing.c, and actual glyphs.c with
ONLY map_glyphinfo renamed to teleport_pager_unused_map_glyphinfo in that separate
foreign object, so the controlled map-display dependency can be supplied without
a duplicate symbol. Retained glyph_to_cmap is genuine foreign source. The probe
owns controlled naming/world/UI deps, not a second PAGER implementation.

Both modes also compile pager-probe-consumer.c separately at O2. Reference alone
adds TELEPORT_REFERENCE_TU; hybrid alone links the separately compiled storage
object, pager JS library and $teleportPagerInit startup retention. Do not link
storage into reference (the real source defines the public array there).
Standalone probe includes support itself; avoid double inclusion with common
support. Export FS and HEAPU8, use modular Node,1MiB stack and growth.

Exports (all _probe_ prefix): reset clear option input menu buffer pointer record
field tile link property level queue engr trace snapshot layout_count layout_name
layout_value stack call consumer observe observe_offset glyph; additionally malloc/free.
probe_call takes (int,const long*) with12 typed argument slots. Unlike some older
TUs, it is NOT the six-argument probe-call signature. Public coord caller copies
are emitted by actual C signatures. JS direct byval copies are separately tested.

The shared wrapper MUST set PAGER_PROBE_DIR=.cache/tu-probes and
TELEPORT_NATIVE_TESTS=0. Standalone defaults to .cache/pager-first-pass.
TELEPORT_NATIVE_TESTS=1 rejects before Module creation: no native reference
fixture exists. Add owned pager-source-check.py to verification alongside normal
source/comment/parameter/scope validators. Source-data provenance checks actual
production CPP/AST/config/member aliases/types/tables/static data/pointer ops;
it is a change detector, not a proof of equivalence.

## Controlled scope and honest limits

Real MEMFS/libc data/keyhelp files exercise parser success, prefixes, alternate
names, malformed headers/records, indentation, tab expansion and missing files;
actual fopen/fgets/fseek/fclose/sscanf are used. World/monster/object/naming,
command and menu effects are controlled fixture dependencies. No real OS messages
or external contacts are sent. Object storage is fixed fixture memory and
fixture dealloc only records/reset state; complete allocator/world policy is not
claimed. Source-local cleanup remains ordered, with no invented finally fclose
on callback throw. JS automatic stack restoration is measured around the bridge
itself; C caller frames after a JS exception are outside that claim. Original
once assignment behavior after a thrown callback is compared separately.

Only typed pointer outputs are classified. Object/permonst slots are read as
BigUint64 before exact known-address matching. Observation-only unknown pointers
0x20000000000000/1 retain exact decimal and8 raw bytes, with no dereference or
Number conversion; address-shaped scalar bytes remain raw. Declared valid C
string outputs are bounds/termination checked before decoding and do not pass
through the unknown-pointer observer. No blanket pointer-byte zeroing or scalar
address normalization occurs. Source static aliases are tested across overwrites.

## Evidence status

Final actual -O2 -g memory64 builds and unchanged-C/JS suite pass **2,905
comparisons,46/46 configured bodies invoked**. The hybrid has46 original public/
private source imports, reference has zero source imports, and actual hybrid
compiler dependencies exclude src/pager.c. Fresh actual production CPP/AST,
all original names/order/parameters/comments, exact Snprintf owner/closing-line
metadata,1013 member/type/alias records,
17 byte-pointer += and8 byte-pointer ++ uses, static/table/public data and
scope guards pass. Generic TELEPORT_REFERENCE_TU support-only syntax passes
without original private bodies/types. Direct native invocation rejects before
Module creation. No native/full-game/public acceptance is claimed.

Four wrong-code controls reject the same unchanged C oracle/checks: wrong public
initializer (before source entry), removal of true byval coordinate copy,
freezing the live mon_to_glyph pointer, and allocating a fresh line buffer every
loop iteration. The last one is caught by a real native callback stack-delta
witness across all6,000 lines; genuine C and corrected JS stay at constant depth.
Original reference Wasm stays unchanged throughout negative runs. Evidence:
.cache/pager-first-pass/{test.log,negative-proof.json,negative-*.log,
source-guard.log,source-preservation.log,scope.log,generic-support.log,
import-audit.json,native-rejection.log,input-hashes.json}.

Two development coverage gaps are preserved explicitly. Earlier counts up to
2672 included supposed positive parser setups while a generic pmatch fixture
returned FALSE, so they did not establish successful entry rendering. Genuine
foreign strutil.c pmatch now replaces that fixture and original-C success1,
all6000 callbacks, final line and constant stack delta are independently
asserted. A content-only large-entry case also accepted the wrong accumulating
buffer version because overflow touched otherwise-unused fixture BSS. This was
never reported as a successful lifetime negative; the subsequent callback-depth
witness catches it. Preserved diagnostics:
parser-success-coverage-gap.json, superseded-before-real-pmatch-test.log,
automatic-content-only-coverage-gap.json/log in the private cache. Their old
artifact hashes are historical; final artifacts are bound by the final manifest.

The final unknown-pointer witnesses use the Number-colliding pair2^53 and
2^53+1, prove Number(pair0)===Number(pair1), and still retain distinct exact
IDs/raw8bytes without dereference. The scalar offset comes from compiler
offsetof and address-shaped scalar bytes remain raw. Positive and null typed
monster/object/trap/command-queue/engraving/region return paths are exercised
explicitly; no unknown pointer
is projected/dereferenced by the observation-only tests. Both saved static
aliases and fresh-Module once state/reentrant/throw-before-assignment behavior
are exercised. All original PAGER algorithms remain in JS.

Final artifact SHA256:

- Reference Wasm: 449eef5906776f07924eb6337f1ffe326463af8705b190c83a4a29a9cccef1ee
- Hybrid Wasm: ce8a36f11a1530d348e1e199cf333c1ac8742a39b224aedb50f4ee3800db04d7
- Core: 6c13cf9d9e88fd0db37ad0c77c64d3f4bd2389eedbdfc44b1f1dca16cbebd934
- Runtime: 6bf8a2bfc708578490798a30be117d9c7eb7e2798036c1a3cc198cd459922155
- Library: 0100bde0d32f02960fe21df964f32445400d493366eea3f21f1b12a5fce2fbc9

Files are frozen after this handoff. Parent owns shared registration/promotion
and atomic append of pager-divergence-entry.md to the shared divergence register.
