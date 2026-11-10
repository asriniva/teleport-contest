# ATTRIB staged integration

Frozen handoff: **34 configured original functions**, source/pristine identical,
**18,224 configured Emscripten-C/JS comparisons pass**. The latest count
supersedes the18,097 checkpoint; additions cover signed-char HP limiting,
unknown roles, unsigned hunger state and dependency-exception cleanup.
No shared build/registry/runtime file or production artifact was edited.
Actual production game linking, recordings and native macOS remain pending.

## Exact staged inputs

- `js/ported/attrib.js`: all34 original function boundaries, order, names,
  parameters, comments and control flow. All18 innate tables/62 rows, six public
  attribute names, plus/minus attribute strings, poison-delivery catalogue,
  exercise text and original local role mapping remain JS authoritative.
- `js/ported/attrib-runtime.js`: compiler-described views, pointers, header
  macros and module initialization. Attribute arrays use signed bytes;
  intrinsic/extrinsic/blocked masks and turn counts use BigInt; hunger/goop
  fields use unsigned32; `newhp` preserves the original signed-char limit.
- `nethack-c/wasm/tu-libraries/attrib.js`: typed ABI, guarded source-literal
  cache and **actual module-startup initialization** through addOnInit.
- `nethack-c/wasm/tu-fragments/attrib-support.inc`: typed globals/fields/header
  macros, printf/RNG/assert ABI, zero-only table/name/static-buffer storage.
  No original ATTRIB function or table initializer remains in C support.
- `scripts/tu-attrib-layout.h`: compiler metadata for every struct field used,
  dimensions, widths, constants and scalar-array assumptions.
- `scripts/tu-attrib-probe.c` and `scripts/test-tu-attrib.mjs`: controlled
  dependency fixture and explicitly labelled first-pass differential gate.
- `nethack-c/wasm/tu-fragments/attrib-metadata.py`: read-only source-data guard
  for all18 tables/62 rows, attribute/poison/exercise strings,125 source
  literals/1650 NUL-terminated UTF8 bytes,26 RNG line/function sites, debug
  default flag, assertion origin and actual startup hook.

Hash the core, runtime, library, support fragment, layout header and source-data
checker as build inputs, in addition to the normal registry/common runtime/
compiler definitions. Test provenance also needs fixture and test hashes.
The integration-method snippet is `attrib-runtime-method.inc`.

## Registry and startup

Add exactly this registry entry when promoting to the next mixed-link gate:

```json
{"name":"attrib","source":"src/attrib.c","javascript":"js/ported/attrib.js","library":"nethack-c/wasm/tu-libraries/attrib.js","configuredFunctions":true,"startup":"$teleportAttribInit"}
```

The startup field is required. Other C TUs may read `attrname[6]` before any
ATTRIB function runs. The import library's `$teleportAttribInit__postset` installs
`addOnInit(() => teleportAttribInit())`; it calls
`Module.nethackPorted.initializeAttrib(teleportAttribServices())` after memory and
C exports exist. It writes JS-owned table/name contents into module-local
zero-only ABI storage. The test reads all six names before reset or any original
ATTRIB function call, and repeats this on a second Module sharing one runtime.

C backing `teleport_attrib_names[6] __asm__("attrname")` is mutable zero storage
with the required public C linker symbol. Its JS initializer supplies the
original names. It avoids writing a C `const` initializer or exposing a compiler
constant-zero definition. Innate entries contain typed pointers into this
Module's live `u.uprops[].intrinsic`; they never cache the property values.

Include `tu-fragments/attrib-support.inc` from shared `tu-support.c`. Keep original
`attrib.o` excluded in the actual game link; no C TU fallback is permitted.

## Runtime registration

Import `* as attrib` and `createAttribEnvironment` into `wasm-runtime.js`. Add
`const attribEnvironments = new WeakMap()` inside `createPortedRuntime` and copy
both methods from `attrib-runtime-method.inc` into its returned API. Startup and
function dispatch must use the same map. Preserve the binding's stack save /
restore and `withCEnvironment` scope. Fresh views after all callbacks are required.

Public original imports (27):
`adjattrib`, `gainstr`, `losestr`, `poison_strdmg`, `poisontell`, `poisoned`,
`change_luck`, `stone_luck`, `set_moreluck`, `restore_attrib`, `exercise`,
`exerchk`, `init_attr`, `redist_attr`, `vary_init_attr`, `is_innate`, `from_what`,
`adjabil`, `newhp`, `minuhpmax`, `setuhpmax`, `adjuhploss`, `acurr`, `acurrstr`,
`extremeattr`, `adjalign`, `uchangealign`.

Private test aliases (7, excluded from production):
`teleport_attrib_test_exerper`, `teleport_attrib_test_rnd_attr`,
`teleport_attrib_test_init_attr_role_redist`, `teleport_attrib_test_postadjabil`,
`teleport_attrib_test_role_abil`, `teleport_attrib_test_check_innate_abil`,
`teleport_attrib_test_innately`.

## Probe/layout registration

Add descriptor `attrib` with fields `[]` and these probe exports:
`reset`, `option`, `attr`, `role_array`, `advance`, `prop`, `object`, `equip`,
`rng_pointer`, `rng_length`, `input`, `action`, `attrname`, `innate`, `trace`,
`result`, `snapshot`, `stack`, `layout_count`, `layout_name`, `layout_value`.

Reference mode must define `TELEPORT_REFERENCE_TU`: the fixture includes original
attrib.c itself; do not append that source again. Hybrid links this fixture,
new library and support; no other gameplay TU implementation is required for
this controlled fixture. Include `$teleportAttribInit` in its default library
functions. All original public/private function calls then reach JS imports.
Add `attrib: []` to the layout writer and its compiler-descriptor handling list;
all metadata values fit Numbers in this profile. Runtime promotes masks/counts
to BigInt explicitly.

Run `attrib-metadata.py` before source validation/builds. It only reads files and
fails when source/table/pool/provenance/startup assumptions change.

The current script deliberately compares configured EmC directly. It **throws
when TELEPORT_NATIVE_TESTS=1** so a future native aggregate cannot silently count
these EmC observations as native passes. Enable its native run only after
integrating the actual native oracle for these same cases. Keep native failures
visible, without host-specific expected outputs or passing waivers.

## Isolated verification already performed

The throwaway `.cache/build-attrib-isolated.py` compiles reference and hybrid
memory64 outputs under `.cache/attrib-first-pass`; it writes no shared probes or
production output. Reference alone includes original attrib.c. Hybrid has only
the controlled fixture plus typed support/library and startup import.

```sh
python3 .cache/build-attrib-isolated.py
TELEPORT_ATTRIB_PROBE_DIR=.cache/attrib-first-pass .cache/emsdk/node/24.19.0_64bit/bin/node scripts/test-tu-attrib.mjs
python3 -B nethack-c/wasm/tu-fragments/attrib-metadata.py
python3 -B .cache/check-p01-source.py attrib
.cache/emsdk/node/24.19.0_64bit/bin/node .cache/check-p01-scope.mjs attrib
```

Latest successful focused result:18,224 comparisons. Logs:
`.cache/attrib-isolated-build.log`, `.cache/attrib-isolated-test.log`.
Source/order/parameter/all-block-comment, lexical scope, data guards and JS syntax
checks pass. The reference/hybrid fixture and support/header compile and link.

Comparisons retain exact state, property longs, messages, debug category,
RNG state and ordered dependency traces. They exercise all34 function entry
points, every role table row, role/race thresholds and intrinsic priority,
attribute/temporary/exercise arithmetic, poison and equipment effects, luckstone
quantities above Number's exact range, HP progression/max/damage, signed-char HP
limiting, alignment changes and descriptions with overlapping string compaction.
Actual heap growth, C→JS reentry, two Modules sharing one runtime and a thrown
JS dependency verify memory refresh, state isolation and both environment /
Wasm-stack cleanup. A negative-control runtime that reads unsigned hunger as
signed fails the added `unsigned hunger field` regression:
`.cache/attrib-unsigned-negative.log`.

## Explicit semantic adaptations and limits

The original forward `goto nextattrib` is represented by a labelled block plus
`break nextattrib`; the common exercise-decay tail remains outside the block.
All original tests/branches/order and the function boundary are retained.

`adjalign` performs signed addition which can overflow in the original C.
Configured Clang -O2 eliminates its overflow guard comparison under signed
non-overflow assumptions; measured reference output for INT_MIN minus9 stores
2147483639 rather than retaining INT_MIN. The JS keeps the temporary mathematical
sum until the typed int32 store, retaining the original branch syntax and
matching that configured compiled behavior. The signed-boundary regression is
retained. Native macOS behavior for these undefined C overflow cases is pending;
this is not evidence of portable C overflow semantics or native equivalence.

Not verified: real full-game dependencies, actual game object exclusion/import
set, public recordings or native macOS. Controlled dependencies are not proof of
their independent game algorithms. All real lifesaving/rehumanization/equipment
retouch and status interactions, every initialization probability distribution,
all exotic callback mutations, unsigned/signed overflow combinations and invalid
attribute indices are not exhaustively tested. Runtime rejects changed ABI /
array widths/char signedness; other compiler profiles need fresh validation.
