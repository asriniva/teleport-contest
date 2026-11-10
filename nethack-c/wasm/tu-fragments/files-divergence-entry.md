## PAR08-FILES — complete 68-body private Emscripten first pass; native pending

Location: `js/ported/files{,-runtime}.js`, `nethack-c/wasm/tu-libraries/files.js`,
`scripts/tu-files-{layout.h,probe.c}`, `scripts/test-tu-files.mjs`, owned
`tu-fragments/files-*`, private `.cache/files-first-pass/`.

Exact change: 68 configured original FILES functions (53 public / 15 private)
now have JS source algorithms/control/data, original names/order/parameters and
all block comments. Typed C code handles original struct/header access, callback/
vararg ABI and zero-only storage, with no original-TU C algorithm fallback or
initialized source-table mirror. This is private/unselected until the integration
owner applies its separate registry/runtime/build wiring. No selected98/shared
builder/runtime/support/source or frozen PAGER/other-TU file was edited here.

Provenance: pristine src/files.c SHA256
5295af5df75ed1f67c9898d9d56a2cad6a35da68e511b5e5ab35886db6f9f2a5;
prepared compiled src/files.c SHA256
460967cdbc2c5c73d29e7148efcb8ee4c3a60fe548a152fe3e4a3f5fe549e96d.
The inherited prepared-only __EMSCRIPTEN__ compression dispatch uses external
teleport_compress_file; original fork/exec/wait subprocess code is inactive.
The reference uses the actual prepared profile, not an untouched executable.
No upstream source or native compatibility service was modified by this port.

Behavior/adapters: keep source private static aliases and exact initializers,
source signed8 MAXPASSAGES30 storage despite stale source comments/casts,
LP64 long parameters/counters/clocks, byte and char** pointer scaling, live
windowprocs/function-pointer identities and real file/parser/error cleanup.
Fixed automatic slots are reserved once per source invocation and reused at
original declaration points; recursive/reentrant calls have separate frames.
Native C callback delta checks exposed/corrected the initial lazy filename
reservation and accumulating uid cells. Literal backing is source-derived2145
bytes, with stable non-null empty pointers and distinct mutable hexdigits arrays.
Runtime memory views refresh after growth and reject unsafe pointer addresses/
metadata rather than rounding; unsupported scalar transport rejects explicitly.

Verification actually run: fresh -O2 -g memory64 reference/hybrid links;1,420
checks invoke all68 bodies and compare unchanged original C output, trace,
state, filesystem effects, long64 filecell fields/cursor positions and typed
bones-id alias offsets. Real libc stdio/directory/sscanf/qsort and genuine
hacklib/strutil dependencies are used. Positive sorted-save names,32 save
extractions with constant C-library scan stack delta and6000 tribute output
callbacks prevent null-only or accumulating-buffer claims. Cases include both
logged RNG sites/full filenames, high64 masks/clocks/birthdays/moves/counts,
signed8 passage return, save/bones paths/errors, lock retries/nesting/HUP,
wizkit/symbol callbacks, codec dispatch success/failure cleanup, callback
reentry/growth/mutation/throw and pre-fixture-cleanup bridge frame checks,
static aliases, Module isolation, safe metadata and unsupported types.

Source/config/ABI evidence: actual production basename/forced-native/ncurses
CPP and AST preserve all68 boundaries,377 MemberExpr aliases,47 compound/
increment/decrement records (two pointer += are char* scale1),14 exact qualified
callback signatures,10 JS-owned source static initializers,2 exact RNG origin
sites and Snprintf make_converted_name closing line2151. Source/scope guards,
generic-reference support isolation and actual import audit pass. Reference
has0 JS TU imports; hybrid has68 and excludes original files.c. A direct
TELEPORT_NATIVE_TESTS=1 invocation explicitly rejects before creating Modules.

Wrong-code evidence: three private JS mutations are rejected by the unchanged
C suite/reference Wasm: unsigned signed8 passage reads, Number-rounded long
ll_type, and accumulating uid cells. Exact logs and immutable before/after
reference hashes are in `.cache/files-first-pass/negative-proof.json`.
`coverage-history.json` preserves that the first unsigned-return negative
unexpectedly passed the earlier1,416 checks; an explicit valid C context of
signed0x80 passage slots closed that missing-return coverage, and now rejects
the same wrong variant. No expected normalization, platform waiver or replacement
oracle was introduced. Passing earlier functional counts were not evidence of
that missing negative-control property.

Limits: these are isolated actual Emscripten C comparisons, not native OS,
full-game or public acceptance. Game/config/object/clock/signal/termination/
codec/RNG dependencies are controlled; the codec fixture copies bytes to
observe dispatch/cleanup and does not validate production compression bytes.
Native subprocess behavior, real multiprocess contention, native UID/permissions/
platform stdio/directory order/compiler operand order, complete production
world dependencies and native/full/public gates remain pending. Dereferenceable
runtime pointers must fit exact JS addresses; unsafe64 observation-only pointer
IDs/raw bytes are retained without dereference, while scalar/padding bytes stay
raw. Undefined C behavior is not a portable equivalence claim. A parent bounded
read-only sample review reported no concrete issue, not exhaustive proof.

Integration recipe and exact registry proposal are
`nethack-c/wasm/tu-fragments/files-integration.md` and `files-registry.json`.
Compile support once through nativeStorageSources; fixture already includes it.
No public startup hook/external layouts argument is required. Parent owns
shared application, atomic append of this entry and native/public promotion.
