# BONES staged integration handoff

Status: generated and independently tested; NOT promoted to shared registry or
production game. The native-compatibility fixes were not changed. BONES has all
16 configured original functions in original order, with original parameters and
all original block comments. Prepared bones.c currently equals pinned upstream.

Owned files:

- `js/ported/bones.js`: 16 source bodies, no C algorithm fallback.
- `js/ported/bones-runtime.js`: live typed field views, cached pointer identities,
  source header macros, addressable-local copyback and callback scope.
- `nethack-c/wasm/tu-libraries/bones.js`: memory64 scalar/pointer/dependency calls.
- `scripts/tu-bones-layout.h`: compiler sizes/constants/configuration and field IDs.
- `nethack-c/wasm/tu-fragments/bones-support.c`: typed field/global/dependency ABI.
- `nethack-c/wasm/tu-fragments/bones-source-data.h`: derived literal capacity.
- `nethack-c/wasm/tu-fragments/bones-source-check.mjs`: source/RNG/capacity guard.
- `scripts/tu-bones-probe.c`, `scripts/test-tu-bones.mjs`: focused C/JS fixture.

Checks actually run (2026-11-09 local date):

1. Staged original source checker: `python3 -B .cache/check-p01-source.py bones`:
   original inventory/order/parameters and ALL block comments pass.
2. Staged lexical scope checker: SDK Node `.cache/check-p01-scope.mjs bones`: pass.
3. Real compiler preprocess plus JSON AST under actual memory64/configured defines;
   independent support and metadata C syntax compile: pass.
4. `node nethack-c/wasm/tu-fragments/bones-source-check.mjs`: all five original RNG
   sites/callers and 371 literal bytes checked; shifted-line mutation rejected.
5. Isolated `.cache/bones-work/build.py`: reference and actual mixed memory64
   hybrid links succeed. The hybrid compiles `HYBRID_BONES=1`, which excludes
   original bones.c; every invoked bones algorithm resolves through JS bindings.
6. `TELEPORT_NATIVE_TESTS=0 BONES_PROBE_DIR=.cache/bones-work node scripts/test-tu-bones.mjs`:
   **1,465** direct Emscripten-C/JS comparisons pass (state, raw callback traces,
   returns, stack restoration, extension bytes, repeat allocation and ownership,
   plus a C dependency forcing memory growth during addressable-local handling).
   Four explicit time_t dependency transport cases include past2038, negative and
   greater-than-2^53 values; callback traces retain all64 bits.
   Exact final result: `.cache/bones-work/test.log`. Build log is in the same folder.

The harness directly calls 11/16 functions: no_bones_level, goodfruit, resetobjs,
sanitize_name, drop_upon_death, can_make_bones, bones_include_name,
set_ghostly_objlist, fix_ghostly_obj, newebones, free_ebones. give_to_nearby_mon can
be reached indirectly by drop_upon_death; its selecting/carrying branches are not
claimed exhaustively covered. The other unexercised functions are fixuporacle,
remove_mon_from_bones, savebones and getbones. Full file/save/restore/world paths
remain unverified. The fixture explicitly labels 38 inactive dependencies as
controlled boundary witnesses, many returning zero; these are test-only and
must never be presented as save/restore support. Native-C tests, an actual
production game link and public recordings remain pending; no native differences
are waived or claimed fixed by this first-pass result.

## Shared integration recipe (owner to apply)

1. Registry `tu-ports.json`: add name `bones`, source `src/bones.c`, JS core and
   library paths above; exclude `bones.o`; preserve the 16 names/order listed
   below and original parameter identifiers. There are nine public functions:
   sanitize_name, drop_upon_death, can_make_bones, savebones, getbones,
   bones_include_name, fix_ghostly_obj, newebones, free_ebones.
2. Add the core namespace import and createBonesEnvironment import to central
   wasm-runtime.js. Cache the environment PER `services.moduleKey`, because its
   live wrapper identity cache belongs to one module. Wrap each request in
   stackSave/stackRestore and withCEnvironment. Convert argument positions using:

   ```js
   const bonesParameters = {
     no_bones_level:['level'], goodfruit:['int'], resetobjs:['object','boolean'],
     sanitize_name:['pointer'], give_to_nearby_mon:['object','coordxy','coordxy'],
     drop_upon_death:['monster','object','coordxy','coordxy'],
     fixuporacle:['monster'], can_make_bones:[], remove_mon_from_bones:['monster'],
     savebones:['int','long','object'], getbones:[], bones_include_name:['pointer'],
     set_ghostly_objlist:['object'], fix_ghostly_obj:['object'],
     newebones:['monster'], free_ebones:['monster'],
   };
   ```

   object/monster/level use environment wrapper constructors, long is signed64
   BigInt, all remaining parameters are Numbers. Return numeric boolean results
   as Numbers at the scalar ABI boundary, and void as zero if the common runtime
   convention requires it. The standalone runtime used by the test is a complete
   working example with all these argument types.
3. Include bones-support.c from tu-support.c OR compile it as a separate ABI
   source, never both. Its local source-data header resolves alongside it.
   The callback is a distinct import, teleport_bones_remove_mon_callback, which
   targets the JS private remove_mon_from_bones body. This preserves original
   iter_mons mutation/iteration behavior in the existing dependency.
4. Probe builder entry `bones`: compile scripts/tu-bones-probe.c and the support
   fragment in BOTH modes. Do not separately compile bones.c: reference fixture
   already includes the prepared source, hybrid excludes it. Hybrid adds
   `-DHYBRID_BONES=1 --js-library nethack-c/wasm/tu-libraries/bones.js`.
   All remaining configured defines and memory64 options stay standard.
   Export these names (prefix underscores using the builder's convention):
   probe_time_bridge, probe_pointer, probe_reset, probe_option, probe_link, probe_name, probe_omonst,
   probe_pm, probe_known, probe_trap, probe_cemetery, probe_action, probe_trace,
   probe_snapshot, probe_stack, probe_layout_count, probe_layout_name,
   probe_layout_value, teleport_bones_read, teleport_bones_write,
   teleport_bones_global.
5. write-tu-layouts: add `bones:[]`; its dynamic layout_count/name/value API has
   everything required and contains native terminal-independent scalar fields.
   Probe test defaults to shared `bones-reference.mjs`/`bones-hybrid.mjs`; custom
   BONES_PROBE_DIR is only for the isolated development link.
6. Run bones-source-check.mjs during source metadata/pre-build checks. The 371
   byte literal capacity is sum UTF8+NUL over every actual ABI string literal in
   the core (excluding import path/reference-kind labels), plus the pline1 `%s`
   macro format. It is neither an arbitrary headroom allocation nor a runtime
   lookup table. Checker uses AST literals and rejects changed capacity; changing
   ABI literals requires intentionally regenerating bones-source-data.h.
   RNG helper lines/callers are guarded against the prepared original source:
   247 give_to_nearby_mon, 290/296 drop_upon_death, 377 can_make_bones,
   645 getbones. The helper's caller logging occurs BEFORE evaluation of rn2's
   bound. The depth-dependent bound is a thunk solely to retain original C comma
   macro side-effect order; raw callback traces caught and verified this detail.
7. Source metadata/build provenance must include both support/header files, the
   source guard, runtime and binding. No source data arrays were copied into
   JS beyond the original small RNG site ABI table and field schema; catalogues
   stay live existing dependencies. No pristine/frozen/upstream files edited.
8. Register existing native builder and native suite after the first-pass EmC
   gate. Native assertions are not implemented as exceptions here. Run actual
   mixed production link and public recording gate serially with other TU owners.

All16 function order: no_bones_level, goodfruit, resetobjs, sanitize_name,
give_to_nearby_mon, drop_upon_death, fixuporacle, can_make_bones,
remove_mon_from_bones, savebones, getbones, bones_include_name,
set_ghostly_objlist, fix_ghostly_obj, newebones, free_ebones.

## Divergence register text for parent to append with integration

BONES implementation introduces the 16-body JS TU and typed memory64 field/global,
string-format, callback and existing-dependency seams at the locations above.
Original function inventory/order/parameters/block comments/control flow remain;
C pointers become cached live views and addressable scalar locals use stack cells
with finally-copyback. C labels use a labeled block for the single forward
savebones jump; C signed-long fields use BigInt and C integer division truncates.
Source header macros are JS in the runtime, guarded by compiler constants and
scalar widths, signed char, MAIL_STRUCTURES=1 and SFCTOOL=0. Generic C field
accessors perform only typed struct access, including C bitfield assignment
truncation; there is no C bones algorithm fallback. Literal storage is source-
derived371bytes; all five source RNG sites and pre-argument logging are checked.
Verification is precisely the six checks above and focused1,465 EmC/JS checks.
Full production activation, save/getbones/oracle/removal behavior, native-C and
recordings are pending. The staged test fixture's 38 inactive dependency
witnesses are controlled test boundaries, never replacements for production.

Peer read-only review caught and fixed the yyyymmddhhmmss time_t64 bridge: it now
passes BigInt64 rather than Number/int32. An actual compiler-AST typedef audit
found only four64bit dependency interfaces: memset/strncmp size arguments use
BigInt64, strlen returns bounded string length as Number, and yyyymmddhhmmss time
uses BigInt64. Focused real-memory64 regressions cover the time seam. Peer review
found no further concrete save/get/Oracle/removal wiring defect, but those paths
remain unverified behaviorally.
