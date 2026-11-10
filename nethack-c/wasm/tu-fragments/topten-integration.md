# TOPTEN staged integration

Frozen private handoff: **24 configured original functions**, pristine/prepared
src/topten.c bytes identical, **9,931 configured Emscripten-C/JS comparisons PASS**.
Counts represent setup/state/trace comparisons, not complete branch coverage.
No shared registry/build/runtime/layout file, frozen harness or production
artifact was edited. Actual mixed-game imports/exclusion, public recordings,
native macOS and real named record/log/xlog IO remain pending.

## Exact owned inputs

- `js/ported/topten.js`: all24 original functions/boundaries/order/names/params,
  all106 original block comments with multiplicity, original ranking/parsing/
  formatting/conduct/achievement/name selection/control flow. TU newttentry and
  dealloc_ttentry macros stay inline JS; done_stopprint/HUP expansions retain
  actual configured program_state fields.
- `js/ported/topten-runtime.js`: fresh typed native views, perModule private
  tt_head, char** argument aliases and complete native record copies.
- `nethack-c/wasm/tu-libraries/topten.js`: memory64 ABI, source-only literal pool,
  compiler-derived fixed printf shapes, actual scanf pointer vectors, exact
  original RNG/Strlen/Snprintf origin and entry stack scope.
- `tu-fragments/topten-support.inc`: typed fields/header/dependency/varargs calls,
  zero-only mutable record/literal backing. No original TOPTEN function fallback
  or ranking/parser/formatting/achievement algorithm is implemented in support.
- `tu-fragments/topten-types.h`: declaration-only configured private record mirror.
- `scripts/tu-topten-layout.h`: compiler field/width/config/constants descriptors
  and reference-only comparison against every actual original private field.
- `scripts/tu-topten-probe.c`, `scripts/test-tu-topten.mjs`: controlled external
  dependencies and actual C stdio differential fixture.
- `tu-fragments/topten-metadata.py`: read-only data/type/actual-CPP/AST guard.
- `tu-fragments/topten-runtime-method.inc`: exact central runtime method.
- `tu-fragments/topten-hashes.json`: owned inputs and actual dependency/header
  profile. Include runtime/support/types/layout/data guard in normal provenance;
  fixture/test hashes belong in test provenance.

Original data remains source-authoritative JS:16 killed_by_prefix strings,
three configured reader formats and four writer formats,29 achievement case
labels and20 ordered conduct entries. Guard verifies their exact values/order,
178source strings/2636NUL-terminated UTF8 bytes,21 actual compiler argument-type
printf shapes and all3 RNG sites. Dynamically formatted strings stay pointers;
only actual original source literals are interned. Prefix and format variables
keep their original local scopes.

Private zerott and retained tt_buf use **mutable** zero-only native record
storage; there is no constzero C initializer or same-TU constant record reader.
The configured typed mirror matches actual original size/offset/field widths
and source signedness. Original fields are signed64 points/dates, signed32
numeric record fields, char arrays4/4/4/4/11/101 and an actual pointer. The source
copy from zerott copies every native byte, including padding. tt_buf retains
its persistent native alias across calls and Modules use separate storage.
No public source-owned table needs a startup hook.

## Exact configuration

Actual current compiler profile: LOGFILE/XLOGFILE/HANGUPHANDLING enabled;
UPDATE_RECORD_IN_PLACE, NO_SCAN_BRACK, DLB, VMS, AMIGA and TOS inactive. NAMSZ10,
DTHSZ100, ROLESZ3 and SCANBUFSZ129. All currently configured original functions
are implemented; the inactive NO_SCAN_BRACK functions are not claimed enabled.
Original inactive comments remain preserved. Runtime/data guards reject changed
profile/width assumptions, rather than silently applying this translation to a
different source configuration.

DLB init/cleanup are actual empty header macros in this profile; runtime keeps
those no-op expansions, not a new resource backend. HUP checks the live native
program_state.done_hup at each original guarded output. time_t/long are signed64,
char is signed and pointers are memory64. Layout values use **signed long long**
returns, preserving EOF/WIN_ERR/NON_PM=-1 instead of a rounded size_t conversion.

## Registry and central runtime

When promoting to the shared gate, add:

```json
{"name":"topten","source":"src/topten.c","javascript":"js/ported/topten.js","library":"nethack-c/wasm/tu-libraries/topten.js","configuredFunctions":true}
```

Include `tu-fragments/topten-support.inc` from shared tu-support.c; its local
include finds topten-types.h. Exclude original topten.o from actual mixed game.
No startup/default library function is required. Import `* as topten` and
createToptenEnvironment into wasm-runtime.js. Create
`const toptenEnvironments = new WeakMap()` inside createPortedRuntime and add
method from topten-runtime-method.inc. Binding calls exactly
`Module.nethackPorted.topten(services,name,...args)`; central API validation must
agree. Preserve withCEnvironment and binding stack save/finally restoration.

Public original imports (7): `formatkiller`, `observable_depth`, `topten`,
`prscore`, `get_rnd_toptenentry`, `tt_oname`, `tt_doppel`.

Private test aliases (17, absent from production):
`teleport_topten_test_topten_print`, `teleport_topten_test_topten_print_bold`,
`teleport_topten_test_discardexcess`, `teleport_topten_test_readentry`,
`teleport_topten_test_writeentry`, `teleport_topten_test_writexlentry`,
`teleport_topten_test_encodexlogflags`, `teleport_topten_test_encodeconduct`,
`teleport_topten_test_encodeachieve`, `teleport_topten_test_add_achieveX`,
`teleport_topten_test_encode_extended_achievements`,
`teleport_topten_test_encode_extended_conducts`,
`teleport_topten_test_free_ttlist`, `teleport_topten_test_outheader`,
`teleport_topten_test_outentry`, `teleport_topten_test_score_wanted`,
`teleport_topten_test_classmon`.

## Probe/layout registration and flags

Descriptor name is `topten`, fields `[]`, probe exports:
`time_action`, `reset`, `load`, `input`, `file`, `text`, `argument`, `argc`,
`option`, `conduct`, `achievement`, `entry`, `entry_text`, `rolls`, `roll_count`,
`action`, `trace`, `snapshot`, `stack`, `layout_count`, `layout_name`,
`layout_value`.

Add `topten: []` to layout writer and compiler-descriptor handling. Convert its
signed64 probe_layout_value return to Number; all metadata values fit exactly.
Preserve signed constants. Production data longs/time/varargs remain BigInt.

Reference defines TELEPORT_REFERENCE_TU; fixture includes original prepared
src/topten.c itself, so do not append original source again. **Only that actual
reference fixture**, after the include, defines TOPTEN_VALIDATE_REFERENCE.
Layout mirror assertions use this TOPTEN-specific macro, never generic
TELEPORT_REFERENCE_TU in shared support. Hybrid uses fixture+new library+typed
support, excluding original TOPTEN source. Both compile actual dependencies:
prepared src/hacklib.c, pristine src/strutil.c and pristine src/role.c. These
supply actual string helpers/Strlen_ and role/race/gender/alignment catalogues/
converters; unrelated functions are linker-discarded. No copied dependency
algorithm or new dependency implementation is required in TOPTEN support.

**Private fixture flags only:** `-Dfree=teleport_probe_free` and
`-Wl,--wrap=fclose`. Apply free define to reference fixture and hybrid support
(and linked actual dependency sources) symmetrically. Tracker calls real libc
free; source-owned list frees are counted. The close wrapper captures complete
actual stream bytes before closing the actual FILE and counts source closes.
The library uses typed `teleport_topten_close(FILE*)` so its actual C call reaches
that same wrapper; directly exporting fclose bypasses linker wrap attribution.
**Production uses neither test flag:** typed free/close shims then call actual
libc free/fclose. Their behavior adds no game IO policy or allocator algorithm.

Fixture fopen_datafile maps controlled record/log/xlog names to actual tmpfile
streams and persists their captured bytes in module-local fixture buffers.
Actual fscanf/sscanf/fgets/fgetc/fprintf/sprintf/nh_snprintf/rewind/fclose perform
stream parsing, consumption and formatting. It does not open or update real
user game score files. Path lookup/lock outcomes and window/world effects are
controlled dependencies, explicitly limited below.

## Verification already performed

Throwaway `.cache/build-topten-isolated.py` writes only
`.cache/topten-first-pass/topten-{reference,hybrid}.{mjs,wasm}`. Both actual growing
memory64 -O2 modules compile/link; hybrid contains no original TOPTEN TU body.

```sh
python3 .cache/build-topten-isolated.py
TELEPORT_TOPTEN_PROBE_DIR=.cache/topten-first-pass .cache/emsdk/node/24.19.0_64bit/bin/node scripts/test-tu-topten.mjs
python3 -B nethack-c/wasm/tu-fragments/topten-metadata.py
python3 -B .cache/check-topten-source.py topten
.cache/emsdk/node/24.19.0_64bit/bin/node .cache/check-topten-scope.mjs topten
```

Latest focused result9,931 comparisons PASS. Logs
`.cache/topten-isolated-build.log`, `.cache/topten-isolated-test.log`.
Source/order/params/all block comments (including multiplicity), lexical scope
(11tooling fixtures), source-data/actual CPP/AST/type guards and all three JS
syntax checks pass. Support/layout/reference-only field assertions compile;
owned whitespace checks pass.

All24 entrypoints exercised. Full static record bytes after next-pointer,
points/dates/fields/padding, exact parsed/written record/log/xlog bytes, FILE
positions/EOF/error flags, input argv pointer offsets/content, source allocations/
frees/opens/closes, object/name/monster state, live relevant flags, RNG state and
ordered lock/IO/window/world traces and formatted text are retained. Cases cover:

- All killer prefixes and sanitization, helpless suffix/truncation; legacy3.2
  role/gender/Y2K conversion, malformed/long/missing-newline records and current
  serialization, large signed64 values above2^53 and LONG_MIN/LONG_MAX formatting.
- All conduct bits/strings and achievement labels/ranks/portable31bit halves;
  exact extended log output and original RNG caller lines1395/1446/1450.
- Role class lookup, random entry fallback/rewind and static alias reuse,
  object/doppel names/female state, sorting-by-file order and score selection.
- Score ranking/personal limits/UID narrowing, entrymax/pointsmin cropping,
  wizard/discovery/panic/hangup/stopprint, logfile/xlog lock/open errors and record
  rewrite failure, all plane/HP/wrapped standout display formatting.
- Union criteria and actual writable argv mutations, initialization/default
  user handling,200record reader lifetime, signed64 time fields, actual callback
  heap growth, C->JS reentry, separate Modules/static buffers and throw cleanup.

Actual compiled Strlen_ retains function/line origin123(formatkiller),
1083(outentry),1208(prscore); actual nh_snprintf gets outentry:1082. Metadata
checks real CPP expansion. C printf shape casts are derived again from actual
compiler argument types; source `%ld`/`%lx` values never pass through Number.

Negative control `.cache/topten-negative-loader.mjs` removes **only internal
readentry function stack restoration** via a read-only module-load transformation.
`.cache/topten-reader-negative.log` rejects unchanged C comparison at named
`many record reader lifetime` with Wasm memory-out-of-bounds. Fixed source and
expected results remain unchanged. The staged suite explicitly throws when
TELEPORT_NATIVE_TESTS=1; it cannot silently count EmC observations as native.

## Necessary adaptations and limits

Source top ten showwin/destroywin forward gotos use labelled blocks and shared
original cleanup tails. Random pickentry retry uses a labelled loop and the
original common fclose/return. No source function is merged/split/replaced by
an algorithm helper. Native char** cells preserve pointer increments and writes
to argv; native record copy preserves all fields/padding. char sanitization and
unsigned siz narrowing stay explicit JS, while long values/masks/times use BigInt.

External entry bindings restore stack in finally. Internal readentry, outentry,
outheader, xlog and rank-buffer helpers restore native automatic storage at
original function return; three local pbuf blocks have their own lifetime scope.
Original private static tt_buf and zero template stay outside these stack scopes.
A200record regression protects readentry's seven129byte automatic buffers from
cumulative stack exhaustion. Callback field reads always refresh current heap.

Controlled path/locking, date conversion/depth/rank/name/game/world/UI effects,
RNG sampling and money/genocide/Sokoban predicates limit this fixture. Actual
libc parsing/formatting/stream operations, string helpers and role catalogues are
compiled dependencies, but their independent algorithms/full-game coupling are
not a complete production proof. Actual named file permissions, durable writes,
concurrent locks/races, disk/full/close failures, game filesystem backend,
exceptional allocator failures, every source path/valid record combination,
other compiler profiles, public recordings and native macOS remain pending.
No source assertions were removed and no host-specific expected-output waiver
is used. C signed-overflow/invalid-pointer/out-of-bounds behavior is not claimed
portable or exhaustively equivalent.

A synthetic JS dependency throw restores C-environment and binding-entry stack
scope. It bypasses the outer C fixture return, so the test verifies the binding
pointer then explicitly resets its own outer frame. This is not general foreign
C exception unwinding or a game recovery guarantee. Existing frozen ports and
shared migration/native-compatibility infrastructure were untouched.
