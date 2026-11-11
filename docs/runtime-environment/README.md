# Standalone JavaScript C environment checkpoint

This is a development harness and a future integration target. It is **not a
selectable game backend**. The mixed game does not import this entry point.
There is no transfer adapter between its memory and this environment's memory.
Future integration must connect a complete dependency group within one JS-owned
memory; registering a function alone does not close its game dependencies.

## Implemented scope

`js/standalone/environment.js` creates an isolated CMemory/CVFS instance and
reuses the existing translated policies and JavaScript dependency services.
It supplies measured memory/record/bitfield access, stack scopes, stable
literals, shared globals, signature-checked function IDs, targeted error
unwinding, bounded libc/stdio, a lazy module registry, and per-instance state.
Production imports no Wasm or host filesystem. Data and environment inputs are
injected. C compilers and C/Wasm oracles are development-only.

| Surface | Checkpoint evidence and limits |
| --- | --- |
| Canonical ISAAC64, allocation, strutil, MD4 | Existing native-C suite: 1,294 comparisons including 6,000 draws and full states. Frozen generator unchanged; bounded rejection wrapper corrects its unusable BigInt/Number helper without replacing the generator. |
| Rectangle | 1,190 original-C states plus memory/scopes/callback/instance/growth probes. Uses the registered RNG when present. |
| DECL, DRAWING, OBJECTS, MONST, SYS | 152 global images and pointer aliases, full catalogue byte comparisons, source initializers, 2,304 drawing lookups and sys initialization. Allocated catalogues retain original zero-before-init behavior. |
| HACKLIB / bounded libc | 132 original-musl qsort results and exact comparator traces, stable source sort, utility/scanner tests. Scanner handles integer/string/character/scanset/count conversions; unsupported conversions reject. This is not a complete libc. |
| RND | 1,500 original-C comparisons, state and log transport; caller must inject entropy for random seeding. |
| SFBASE / SFSTRUCT | 136 original-C comparisons: all 68 historical serializers both directions through real procedure tables, callbacks and files. Full game save/bones/restore closure is unfinished. |
| TRACK | 3,496 original-C movement/equipment/query and historical save/restore comparisons, using shared hero/equipment and serializers. |
| Object startup and name state | `enableObjectState`: 11 unchanged O_INIT functions connected to shared DECL/OBJECTS/DRAWING, canonical RND, two actual DUNGEON ledger functions and SFBASE/SFSTRUCT/CVFS. Combined original-C subsystem passes 6,288 comparisons across four seeds, including full class bytes/ranges/totals, shuffling, description lookup, level gem probabilities, failure diagnostic, exact RNG logs/continued stream and name save/free/restore. Serialized `oc_uname` address slots are compared as null/non-null because allocator addresses differ; every other saved byte and all restored name payloads compare exactly. Discovery/inventory/menu functions remain absent. |
| Stdio / persistence | Binary IO, buffering, EOF/error/pushback, seek, close and output contracts; capture/restore/deletion through existing persistence policy. No host device/OS-wide POSIX claim. |
| Lua | Existing JS VM and 83 typed C API dispatch recipes on measured memory; bytecode, callbacks/error unwinding, date/files, userdata growth probes. Full nhlua/nhlobj integration and all standard libraries are unfinished. |
| Terminal | 445 original-C recorder-cell/capture/terminfo comparisons; existing recorder encoding preserved. Window procedures, tty input and game loop are unfinished. The inherited 6,144-byte C recorder buffer bounds captures; larger captures are not accepted by this proof. |
| 13 larger adapters | MKLEV, MKMAZE, PICKUP, SHK, INVENT, DOTHROW, DISPLAY, DUNGEON, MKOBJ, MUSE, PRAY, DETECT, SP_LEV: 23,700 original-C scalar/address/bitfield read/write witnesses. **Transport only**; actual game function dependencies remain unresolved and throw when called. |
| CMD | `isok` geometry only, explicitly registered as `cmd-geometry`. No other CMD surface claimed. |

These are component results, not full-game recording equivalence or acceptance
of all exported functions. There is no playable pure JS build, browser check,
public score or unchanged full-game replay result for this checkpoint.

## Profile and source boundaries

Record metadata targets the configured Emscripten memory64 headers. Exporters
bind actual headers, support sources and existing adapter schemas; production
consumes the checked-in JSON. The historical inventory and plan are retained
unchanged except for their status notice. `scope-baseline.json` instead binds
the 137 translated game policy bodies and frozen files at committed main
`bc368be81594d240ee035028d8a5ebe1a167929e`. They are unchanged by this work.
The base `js/ported/js-runtime.js` changes only its ISAAC provider, replacing the
redundant translation with the canonical generator on JS-owned state views.

There is not yet a single fully accepted platform profile for all libc
services: qsort uses the pinned Emscripten musl implementation; record layouts
use memory64; the earlier base provider's native/Darwin formatting/calendar
choices are inherited. Regex, time and formatting across the entire configured
game are not newly verified here. Do not infer full Emscripten or native-macOS
parity from the individual component tests. No original C, compiler flags,
frozen Terminal/Storage/ISAAC files, game registry, renderer or game defaults
are changed.

## Running the development gate

Use the pinned SDK Node and set `STANDALONE_REFERENCE_ROOT` to a prepared
reference checkout containing the original-C fixtures, SDK, prepared headers
and the host compiler wrapper. From the candidate checkout run:

```sh
STANDALONE_REFERENCE_ROOT=/path/to/reference /path/to/sdk/node scripts/test-standalone.mjs
```

The gate runs source/closure checks, the original base-runtime suite, and ten
standalone suites; logs and script hashes go to `.cache/standalone-validation/`.
It requires the existing original native allocation oracle under the candidate's
`.cache/tu-probes/native-oracles/` (alloc-native.node, alloc-full-native-build.json,
alloc-signatures.json); its manifest verifies all bound reference inputs.
To use a separate worktree, copy those three prepared test artifacts there.
The 13 field-helper oracles are built into a fresh directory with:

```sh
python3 scripts/build-standalone-helper-oracles.py --reference-root /path/to/reference --out .cache/standalone-helper-oracles
```

Other C references are the existing prepared fixture directories consumed by
the individual tests. Missing references fail the gate; tests do not silently
skip them. `scripts/test-standalone-isolation.mjs` imports production only after
forbidding WebAssembly and network capabilities. Static closure inspection
independently rejects Wasm/Node/host network imports on that entry point.
The gate is a Node test; browser execution remains unverified.

Build the combined object-state reference into a fresh directory before running
the gate:

```sh
python3 scripts/build-standalone-object-state.py --reference-root /path/to/reference --out .cache/standalone-object-state
```

`STANDALONE_OBJECT_STATE_ORACLE` overrides that output directory in the test.
This oracle compiles original O_INIT, OBJECTS, RND/ISAAC64, ALLOC/STRUTIL/HACKLIB,
SFBASE/SFSTRUCT and the DUNGEON ledger functions together. Its wrappers supply
input globals and expose results; error/UI boundaries abort. It uses actual C
RNG and serializers, with no scripted RNG stream or raw-copy serializer
replacement. The receipt binds compiled sources, included headers and artifacts;
the test refuses changed inputs. No build output is imported by production.

The caller explicitly enables the existing stdio, declarations, drawing,
catalogue, hacklib, serialization and seeded RNG providers, invokes
`objects_globals_init`, then enables
`enableAddressPort('dungeon', {only: ['ledger_no', 'maxledgerno']})` and
`enableObjectState(layouts)`. `call('object-state', 'init_objects')` performs the
original startup policy. Enabling the adapter alone does not initialize the
game or invent a dungeon map. `oinit` reads the actual injected shared dungeon
map. The other O_INIT functions remain unregistered. The read/write source
wrappers use the same JS heap and function registry throughout.

## Next integration milestone

Object startup/name persistence is the first additional connected group after
the checkpoint. Next connect a larger group, including all its reachable game
owners, and compare complete inputs, state, outputs and recording bytes with
original C. Terminal/input/game-loop and full
save/restore are later groups. Until the full game closure exists, keep the
mixed game as the control and run this harness independently. No cross-heap
transfer or selectable mixed-game route is part of this checkpoint.
