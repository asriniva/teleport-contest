# U_INIT first-pass handoff

Frozen source delivery: all **17 configured functions** in original order with
original parameters, comments, control flow and local arrays. All40 file-scope
catalogues (445 rows,1432 scalar cells) remain JS authoritative. The actual
prepared source, not untouched upstream, is the reference: its inherited
birthday patch replaces time(&ubirthday) with getnow(). The read-only source
guard accepts exactly that adaptation and rejects other provenance drift.

## Integration recipe

Registry:

    {"name":"u_init","source":"src/u_init.c",
     "javascript":"js/ported/u_init.js",
     "library":"nethack-c/wasm/tu-libraries/u_init.js",
     "configuredFunctions":true,"reference":"prepared"}

Import `createUInitBridge` from './u_init-runtime.js'. Inside
createPortedRuntime create `const callUInit=layouts.u_init ?
createUInitBridge(layouts.u_init) : undefined;`. Add this actual dispatcher name
(the binding invokes `u_init`, including its underscore):

    u_init(services,name,...args) {
        if (!callUInit) throw new Error('Missing U_INIT layout');
        return callUInit(services,name,...args);
    }

One bridge per runtime, keyed by actual `services.moduleKey` (Module). It scopes
C and restores its ABI stack in finally. Typed scalar helpers perform all
compiler narrowing and bitfield access. Signed64 birthday/time_t, long quantity,
umoney0, moves and roleplay counters remain BigInt. Masks use BigInt. Current
time_t is long long64 and long is64: sizes are compiler metadata and checked.
Pointers are memory64 addresses, transported as BigInt at C boundaries.

Include `#include "tu-fragments/u_init-support.c"` once from main tu-support.c.
No startup hook or public table linker symbols are required: all40 original
arrays are private. Zero-only exact-size fixed C backing supplies addresses
for C dependencies and pointer traversal. Before the first original routine,
the bridge copies the JS-owned data once per Module. It finishes that copy
before invoking any callback-capable dependency; first-call reentry is tested.
No lazy malloc for private static storage, original C initializer, fallback C
algorithm, custom RNG, or new feature-disable flag is present.

Public original imports (3): `u_init_misc u_init_inventory_attrs
u_init_skills_discoveries`.14 private aliases begin
`teleport_u_init_test_` and should dead-strip from the actual game. The probe
keeps them to exercise all17 original routines. Exclude original u_init.o
through the registry; do not retain it for any path.

Metadata is the flat `_probe_layout_name/value` dictionary over
`_probe_layout_count`, exposed as `layouts.u_init`; values return signed long.
No separate strings table. Include layout, support, core/runtime/library and
source checker in build input hashes. Run
`node nethack-c/wasm/tu-fragments/u_init-source-check.mjs` as a source/data gate.
It checks provenance, all catalogue data, three local arrays, all26 RNG source
sites (including the header ROLL_FROM expansion), exact9 source-derived
literals/130 bytes, fixed zero-only storage and source-static size guards.
Only the actual U_INIT reference fixture defines TELEPORT_U_INIT_VALIDATE_SOURCE
after including original u_init.c. Shared TELEPORT_REFERENCE_TU alone must not
enable private-source assertions in other TUs. This U_INIT-specific gate
asserts actual original private struct field types,
offsets, sizes and each original array's sizeof against the mirror backing.

Probe exports (`_probe_` prefix, plus malloc/free):
`clear reset role option flags clock long money roll sequence skill object
align trop call trace snapshot stack layout_count layout_name layout_value
table_count table_rows table_value`.

Both isolated modes compile ONLY scripts/tu-u_init-probe.c under current
compile-defines.json, memory64, forced native-terminal.h. It includes the real
prepared objects.c catalogue as an external-TU dependency. Reference adds
TELEPORT_REFERENCE_TU and includes prepared u_init.c once; hybrid links the
own TU library and never compiles u_init.c. The fixture includes its support
fragment, so do not link main tu-support.c as well. Add U_INIT to the builder's
source-inclusion exception list if necessary to avoid duplicate source inclusion.
No dependency name-remap compiler flags are needed. Native execution will need
a native-compatible fixture throw/stack/heap adapter; it is not claimed here.

## Representation and evidence

Inventory/skill/substitution rows are exact symbolic JS values resolved using
compiler constants. All rows stay in source positions with exact comments.
`M_spell`/`trotyp` source static arrays have no externally observable array
address; each selected table address remains Module-local. The local Instrument
and dummy object/roleplay copies use scoped ABI stack backing. Struct assignment
copies bytes instead of aliasing views. All scalar views call typed C accessors
again after callbacks, so heap growth cannot stale a cached buffer.

The one header macro `rn1` retains its caller-before-draw expansion in typed
support; RNG itself remains a dependency.26 source locations use **prepared**
lines; the birthday patch shifts later lines relative to pristine. No source
macro algorithm was moved out of its owning function. Original class/gear
macros, spell power macro and field access remain header ABI dependencies.

Isolated `.cache/u_init-first-pass/build.py` builds -O2 actual-C and mixed
memory64 modules. scripts/test-tu-u_init.mjs currently passes **5,463**
configured EmC/JS comparisons, including:

- every original routine and every cell in all40 catalogues;
- 13 roles ×5 races ×3 seeds, repeated inventory resets and discovery passes;
- pauper/nudist/blind/discovery paths, all skill lists and pauper credits;
- filtering bans,1001-retry pancake fallback, racial substitutions and the
  source nudist-continue pending-quantity behavior;
- charged rings/markers/container/armor/weapon/quiver/spell discovery paths,
  merge-return pointer identity, original RNG bounds/callsite/caller order;
- signed64 birthday (both sign limits and >53 bits), money/quantity, moves and
  copied roleplay counters; explicit BigInt reads in the actual callback;
- heap growth, C reentry including the first original call, per-Module state,
  normal-return ABI stack and dependency environment cleanup after exceptions.

A controlled EM_JS exception bypasses the outer C probe frame's normal epilogue;
its post-throw C stack pointer is not asserted equal. The bridge's own finally
restores its saved stack and dependency environment. This is a fixture limit,
not a rewritten expected game result. Normal-return stack checks remain strict.

The unchanged differential suite rejects a separate negative JS copy replacing
`ubirthday=getnow()` with `ubirthday=Number(getnow())`: at9007199254740997 the
C snapshot keeps9007199254740997 and faulty JS produces9007199254740996.
`negative.py` and `negative.log` preserve this proof without altering delivered
sources or expected checks.

Source/order/parameter/all-comment and lexical scope checks pass independently.
Compiler AST/signature evidence, commands, complete input hashes, Wasm imports,
artifact hashes and logs live under `.cache/u_init-first-pass`.

All external character/inventory/skill/HP/energy/hunger/weight/magic/name/debug/
allocation dependencies except libc and the real object catalogue are controlled
fixtures. These checks establish this TU's behavior under those inputs. Actual
foreign dependency integration, complete game/public recording parity and native
macOS parity are **pending**. Do not describe first-pass completion as native or
production equivalence, and do not amend expectations to hide future differences.

Frozen artifacts: prepared u_init.c SHA256
`1b638944fdc482b8d8dc7cfedf0586c8b6c671992e673f4b94104aa3c0ca4660`;
reference Wasm `515bd21b5a6edad84ba0066ee0dbf8dd9fb82cfe712f40bb8c72e8a39c93a6f3`;
hybrid Wasm `cd5e8b69f0ca2876caee457087888658e2786e36dc75d53254d41d7d522030b6`.
`input-hashes.json` captures152 source/header/adapter inputs.
`import-proof.json` verifies all17 original-function JS imports in the real
hybrid Wasm. Its compiler dependency file excludes original u_init.c.

Shared-reference correction: the initial generic TELEPORT_REFERENCE_TU guard
incorrectly exposed private-source assertions to unrelated reference probes.
It is replaced by the fixture-only TELEPORT_U_INIT_VALIDATE_SOURCE gate above.
The unchanged5,463 suite passes again; generic-reference support-only syntax
passes without original u_init.c visible, and a separate wrong8-row Archeologist
backing is compiler-rejected against the actual9-row source. Proof:
`.cache/u_init-first-pass/private-guard-proof.log`. Wasm hashes remain unchanged.
