# NHLSEL integration status — original upstream limitation preserved

The user authorized integrating the staged **33-function** translation while
preserving the original C behavior and its unary alias use-after-free. NHLSEL
is registered as port **138**. DLB and UNIXRES remain disabled and untouched.
The original C source has not been patched to repair unary operators.

Compilation must match the accepted **golden 110 Emscripten build (44/44)**.
`golden-emscripten-profile.json` records that build's actual Emscripten version,
LLVM identity, flags, definitions and forced-header hash; the shared profile
checker compares them with the current game driver. This is the existing
recorder-compatible build, not a new raw-SDK target. Test-only wrappers control
world/callback dependencies or observe actual frees; they do not change ABI or
replace NHLSEL algorithms. The reference Lua archive is built by the existing
game preparation with its original C Lua flags, separately from game C flags.

Reproducible repository-local commands:

```sh
python3 -B scripts/build-nhlsel-probes.py
node scripts/write-tu-layouts.mjs
TELEPORT_NATIVE_TESTS=0 node scripts/test-tu-nhlsel.mjs
TELEPORT_NATIVE_TESTS=0 node scripts/test-tu-nhlsel.mjs --central
node scripts/test-tu-nhlsel-generated.mjs
# Intentionally nonzero: retain the original unary alias UAF failure.
TELEPORT_NATIVE_TESTS=0 TELEPORT_NHLSEL_UAF_WITNESS=1 node scripts/test-tu-nhlsel.mjs --central
# Negative control: intentionally incorrect JS coordinates must be rejected.
TELEPORT_NATIVE_TESTS=0 node --experimental-loader ./scripts/test-tu-nhlsel-negative-loader.mjs scripts/test-tu-nhlsel.mjs --central
```

Use the pinned SDK Node executable (or source its environment) for memory64.
The defined corpus has 734 comparisons, checks all 33 entry points and runs
both directly and through `createPortedRuntime`. The additional generated suite
has 640 C-derived scenarios across 32 seeds and compares complete selection
maps, Lua returns, callback/RNG traces, stack restoration and reentry. It does
not include undefined unary alias behavior in its passing count. That witness
is retained separately and no whole-TU/native equivalence claim is made.

Current results and source/artifact bindings are recorded in
`.cache/nhlsel-current-run/summary.json`. The full 138-port build passed and its
1,053 provenance hashes verified. All 44 public tests ran with the unchanged
45-second deadline: **39 passed; five timed out** (seeds 0002, 0014, 0030, 0360,
4500). Every completed session matched RNG/screens/cursors/animations. Separate
profiled runs of 0002/0360/0030 finished with exact results in 47/96/121 seconds;
these diagnostic results do not convert the official timeouts into passes.
Repeated HACK environment construction dominates healer/ten-deaths profiles;
world-tour has substantial travel/pathfinding and runtime-view overhead.
The original unary alias UAF is still a known non-passing limitation.

## Historical staged handoff and evidence

All **33 configured original bodies** are present. **734 configured
Emscripten-C/JS defined-corpus comparisons pass**, exercising all33 entries;
these are setup/result/state/trace/lifetime comparisons, not branch counts.
**Whole-TU parity is incomplete:** ordinary Lua unary negation (`~s`, and the
same mechanism for `-s`) exposes an original use-after-free. Actual C and JS
follow the same alias/free/duplicate sequence but produce differing corrupted
maps. This path remains a retained failure, excluded from the explicitly named
defined-corpus count. It has no expected-output waiver, repair or normalization.
Native-host, production mixed-game and public recording verification are pending.
Parent alone decides registration/promotion; this handoff is not TU acceptance.

## Exact files and provenance

- `js/ported/nhlsel.js`:33 original functions/order/parameters/boundaries,
  all98 original block comments with multiplicity, all source control flow,
  original local arrays and Lua registration catalogues. The source header
  says nhlua.c, but the actual file is **src/nhlsel.c**,1,051 lines.
- `js/ported/nhlsel-runtime.js`: typed memory/header macro/out-parameter ABI,
  perModule backing/identities and native record copies, fresh heap views.
- `nethack-c/wasm/tu-libraries/nhlsel.js`: memory64 imports and typed dependency
  conversions, fixed actual lua_gc varargs shape, literal guard and entry scope.
- `nethack-c/wasm/tu-fragments/nhlsel-support.inc`: typed fields/globals/header/
  dependency calls and zero-only mutable callback/option/literal storage. No
  original NHLSEL algorithm/function fallback or initialized source table.
- `scripts/tu-nhlsel-layout.h`: compiler-produced widths/offsets/constants,
  signed long long values, original reference-only table row assertions.
- `scripts/tu-nhlsel-probe.c`, `scripts/test-tu-nhlsel.mjs`: real Lua/native
  dependencies with explicitly controlled world/callback-policy boundaries.
- `tu-fragments/nhlsel-metadata.py`: fresh actual CPP/AST/data/type guards.
- `tu-fragments/nhlsel-runtime-method.inc`: exact central dispatcher fragment.
- `tu-fragments/nhlsel-replay-uaf.py`: verifies/replays frozen diagnostic inputs,
  preserving nonzero failure status; no current live NHLSEL source is imported.
- `tu-fragments/nhlsel-hashes.json`: final staged sources, compiler/native
  dependency/header inputs and separate diagnostic/replay provenance.

Pristine/prepared nhlsel.c bytes are identical, SHA256
`ce93cdb316eb18ae4ad32238076ab61cec319973a5cff049ce95289a54239ec5`.
Actual compiler yields3 public/30private bodies. Disabled #if0 l_selection_to
and l_selection_ipairs stay disabled.28private int(lua_State*) callbacks are
active; l_selection_push_new and params_sel_2coords are the two other private
helpers. Registration methods25rows and meta9rows include sentinels. Original
area/fillrect, __add/__bor and __unm/__bnot aliases retain identical native
callback identities. Source growdirs/growdirs2i have7entries, gradtypes/
gradtypes2i3entries.66unique original strings occupy653UTF8+NUL bytes; only
source literal values are interned. There are zero direct NHLSEL RNG calls;
actual compiled selection dependencies retain their own original RNG origins.

Actual headers use Lua5.4.8, signed64 lua_Integer/long/long long, double
lua_Number, memory64 pointers, signedshort16 coordxy/NhRect/room fields,
signedchar8 boolean/rm.typ and int32 selection dimensions. Compiler metadata
uses signed long long -> Number for exactly representable descriptors, retaining
negative W_RANDOM/INVALID_TYPE/LUA_REGISTRYINDEX values. Data longs retain BigInt.
Source explicit and implicit scalar conversions retain original widths.

## Optional parent-only registration recipe

No shared registration/build/runtime/support/native-compatibility file or
selected/frozen TU was edited. The unresolved failure above must accompany any
future staging; registration must not turn this into whole-TU acceptance.

```json
{"name":"nhlsel","source":"src/nhlsel.c","javascript":"js/ported/nhlsel.js","library":"nethack-c/wasm/tu-libraries/nhlsel.js","configuredFunctions":true}
```

Include `tu-fragments/nhlsel-support.inc` in common typed support and exclude
original nhlsel.o from the actual hybrid. Import the namespace and
createNhlselEnvironment into wasm-runtime.js; create
`const nhlselEnvironments = new WeakMap()` inside createPortedRuntime and add the
method from nhlsel-runtime-method.inc. Binding dispatches exactly
`Module.nethackPorted.nhlsel(services,name,...args)` with withCEnvironment and
entry stack save/finally restoration. No startup hook: original source-owned
catalogues are private and populated into mutable zero-only native backing
before the first luaL_setfuncs/luaL_checkoption consumer. Actual foreign Lua reads
of the optimized backing tables are exercised by the fixture. Source tables
remain authoritative JS; no constzero initialized C array or value-reader fold.

Public imports(3): l_selection_check, l_selection_push_copy,
l_selection_register. Production retained callback imports(28) use the exact
`teleport_nhlsel_` prefix followed by each original private int(lua_State*)
function name; callbackNames source catalogue lists all28 in original order.
Typed callback-token switch preserves those actual C function identities.
Two fixture-only aliases, absent from production:
teleport_nhlsel_test_l_selection_push_new and
teleport_nhlsel_test_params_sel_2coords. No original static body is compiled as
fallback for either alias or callback.

Layout writer descriptor `nhlsel: []`; signed64 metadata return -> Number.
Probe exports: reset,input,clear_trace,trace,snapshot,run,option,origin,room,cell,
alias,helper,state,stack,layout_count,layout_name,layout_value.
Reference fixture includes original prepared nhlsel.c itself under
TELEPORT_REFERENCE_TU; do not append original source twice. It defines
**NHLSEL_VALIDATE_REFERENCE only after that actual include**. Source-private
row assertions use this TU-specific macro, never generic TELEPORT_REFERENCE_TU
from unrelated fixtures. Hybrid includes typed support+new library and omits
original NHLSEL source.

Private compilation links actual prepared src/selvar.c, rect.c, sp_lev.c,
nhlua.c, hacklib.c, alloc.c and strutil.c, plus actual prepared
lib/lua-5.4.8/src/*.c except lua.c/luac.c/onelua.c. Actual Lua VM, parser,
userdata/metatable/GC/allocator/string/selection/mapfragment/coordinate/option
helpers execute; original unrelated code is linker-discarded. No Lua subsystem
source or selvar/mapfragment algorithm is changed. This dependency evidence
is not independent proof of every Lua/selection subsystem behavior. Production
may instead supply those already-migrated actual dependency imports; mixed-game
cross-TU execution still requires parent verification.

**Private fixture flags only:** `-Wl,--wrap=get_location_coord`,
`--wrap=nhl_pcall_handle`, `--wrap=free`, `--wrap=dupstr`. The first two supply
controlled world coordinate resolution and callback failure policy (calling
actual Lua lua_pcall); they do not replace Lua stack execution or selection
algorithms. The latter two only observe actual frees/duplicates when diagnostic
option7 is enabled and call __real_free/__real_dupstr immediately. The ordinary
allocator is never quarantined, delayed, repaired or substituted. Typed support
location/pcall/duplicate/free shims make native and JS calls reach exactly those
same linker-wrap boundaries; direct JS exports would bypass wrap attribution.
Production uses none of these four flags; shims then call actual game/libc
functions directly. Do not promote fixture coordinate/callback policies to game
runtime.

## Actual verification

Private builder `.cache/build-nhlsel-isolated.py` writes only
`.cache/nhlsel-first-pass/nhlsel-{reference,hybrid}.{mjs,wasm}`. Both actual -O2
memory64 growing modules compile/link; hybrid excludes original NHLSEL TU.

```sh
python3 .cache/build-nhlsel-isolated.py
TELEPORT_NHLSEL_PROBE_DIR=.cache/nhlsel-first-pass .cache/emsdk/node/24.19.0_64bit/bin/node scripts/test-tu-nhlsel.mjs
python3 -B nethack-c/wasm/tu-fragments/nhlsel-metadata.py
python3 -B .cache/check-nhlsel-source.py nhlsel
.cache/emsdk/node/24.19.0_64bit/bin/node .cache/check-nhlsel-scope.mjs nhlsel
```

Latest defined result734comparisons PASS; logs `.cache/nhlsel-isolated-build.log`
and `.cache/nhlsel-isolated-test.log`. All33 entries exercised; exact complete
selection map bytes/terminator, dimensions/bounds/dirty flag, Lua stack result
types/scalars/strings/table fields, returns, actual RNG state/origins, coordinate
and callback traces are compared. Cases cover deep copies and independent map
mutation, point forms/values/bounds/description, one-argument/no-argument negate,
all binary operators, all line/rectangle forms, random line/growth/percentage,
random removal/empty selections, room selection, actual mapchar/mapfragment/
flood/ellipse/gradient helpers, signed64 Lua extrema above2^53 and signed32/
signed16 casts, signed terrain byte, room/map origins, real Lua error text/GC,
explicit finalizer zeroing, actual callback failure exit, repeated13,272-point
callback lifetime, actual heap growth, nested callbacks, Module isolation and
external/internal out-parameter writes. No raw Lua implementation heap/hash seed
or every allocation byte/padding is claimed captured.

Source inventory/order/params/all comments with multiplicity, lexical scope
(11tooling fixtures), source-data/actual CPP/AST/typedef/field widths, original
reference-only table assertions and three JS syntax checks pass. Configured
header macro expansions for Lua registration/newuserdata/pop/remove and
coordinate packing are verified against actual preprocessing.

Read-only wrong-code loader `.cache/nhlsel-negative-loader.mjs` changes only
getpoint's original x conversion by adding1. Unchanged C comparison rejects it
at `deep copy and point values:trace`:C location5,6/packed393221 versus faulty
JS location6,6/packed393222. `.cache/nhlsel-wrong-point-negative.log` retains
that failure. No implementation or expected output was rewritten for this
negative run.

A synthetic JS dependency throw restores withCEnvironment and binding-entry
stack inside its finally; the test observes that exact restoration through the
same services object. Emscripten's outer Lua invoke wrappers subsequently
restore their own stack frames while propagating the foreign throw, so final
foreign C/Lua frame unwinding is not claimed. The isolated throw-only Module
checks the binding finally boundary and explicitly resets its own outer frame;
it does not continue the interrupted Lua state. This is cleanup evidence, not
native exception semantics or game recovery proof.

## Retained unresolved unary failure and exact frozen replay

Original nhlsel.c:138/142 sets sel=userdata1 and tmp=userdata2; line144 frees
`tmp->map`, line146 duplicates `sel->map`. Lua VM lvm.c:1555/1566 supplies the
same rb operand twice for unary __unm/__bnot. nhlsel.c:270-273 sends those
arguments through clone, so tmp==sel and the duplicate reads freed storage.
The original/JS source sequence is unchanged. Direct extra-argument clone with
aliasing userdata can reach the same defect; such alias combinations are not
claimed supported by the defined-corpus passing count.

Immutable `.cache/nhlsel-uaf-evidence/` contains original failing Lua expression,
raw unnormalized C/JS maps/bounds and both event traces, failing-run.log, actual
ordinary-allocator .mjs/.wasm modules, source-snapshot of8 owned/build inputs,
and177 recorded source/native dependency/header/module/artifact hashes. Parent
independently verified0mismatches. Both actual traces include:

```
free:argalias1:map11:map21;
dupstr:argalias1:map11:map21:after-free1;
```

These flags prove userdata1==userdata2 and both maps equal the pointer actually
freed immediately before actual dupstr. Final raw map bytes/bounds differ and
remain unresolved. Hex bytes may change with ordinary allocator layout; no
particular corrupted byte sequence is a portable expected result.

Verified self-contained replay inputs live separately in
`.cache/nhlsel-uaf-replay/`. Eight sources and four compiled modules were copied
from immutable evidence. A required shared c-runtime.js scope helper was not
in the initial177input manifest; replay explicitly copies/hashes that helper
as an additional input in replay-input-hashes.json. It imports the copied
helper and frozen NHLSEL sources, never evolving live NHLSEL runtime/test files.
No original evidence file was modified. Frozen test prelude and final Lua
expression are retained together in the copied test source; standalone
upstream-uaf-program.lua identifies the triggering final expression.

From repo root, verified command (expected **exit1**, retaining failing status):

```sh
python3 -B nethack-c/wasm/tu-fragments/nhlsel-replay-uaf.py
```

It validates every replay input hash, loads only copied frozen modules/sources,
writes replay.log and upstream-uaf-raw.json outside immutable evidence, and
asserts the differing states plus identical actual alias/free/dupstr witness.
It successfully reproduced the failure after later live defined-corpus edits.
The direct command it executes is:

```sh
TELEPORT_NHLSEL_PROBE_DIR=.cache/nhlsel-uaf-replay/.cache/nhlsel-first-pass TELEPORT_NHLSEL_UAF_WITNESS=1 TELEPORT_NHLSEL_DIAGNOSTICS_DIR=.cache/nhlsel-uaf-replay .cache/emsdk/node/24.19.0_64bit/bin/node .cache/nhlsel-uaf-replay/scripts/test-tu-nhlsel.mjs
```

No upstream algorithm repair is included. No native-host, whole unary path,
whole-TU or mixed/public acceptance follows from734defined comparisons. The
staged test rejects TELEPORT_NATIVE_TESTS=1 instead of counting EmC as native.
