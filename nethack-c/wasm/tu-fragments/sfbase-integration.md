# SFBASE frozen staged handoff

SFBASE is independently generated/linked/tested, not promoted into the shared
registry/game. All239 configured original functions retain original names/order,
parameters/block comments and source control flow. Prepared sfbase.c equals
pinned pristine sfbase.c. SFBASE deliberately includes source-defined macro
expansions from include/sfmacros.h; this is required source ownership, not a
function-count waiver. No frozen/upstream/other-TU/runtime-service file changed.

## Owned files

- js/ported/sfbase.js: all239 configured source functions.
- js/ported/sfbase-runtime.js: typed live views, header macros and ABI access.
- nethack-c/wasm/tu-libraries/sfbase.js: typed Wasm64 imports/dependency calls.
- scripts/tu-sfbase-layout.h: compiler metadata/field offsets/sizes/signedness.
- scripts/tu-sfbase-probe.c and scripts/test-tu-sfbase.mjs: differential fixture.
- nethack-c/wasm/tu-fragments/sfbase-support.c: zero backing/typed ABI only.
- nethack-c/wasm/tu-fragments/sfbase-source-data.h: source-derived capacity/sites.
- nethack-c/wasm/tu-fragments/sfbase-source-check.mjs: source/metadata guards.

## Actual checks and evidence

- Actual memory64 configured preprocess/JSON AST identified239 functions:
  136 serializers (130 source-macro generated plus six direct char/genericptr/
  version_info functions),73 original empty norm_ptrs functions and30 direct
  logger/value/table-init/setter functions. No original norm body is disabled;
  those73 functions are already no-ops in the actual original configured C.
- Source checker copied unchanged with only registry input narrowed to SFBASE:
  `.cache/sfbase-first-pass/check-source.py` passes original inventory, order,
  parameters and block comments. It uses configuredFunctionHeaders as below.
- Existing staged lexical checker `.cache/check-p01-scope.mjs sfbase` passes.
- `node nethack-c/wasm/tu-fragments/sfbase-source-check.mjs` passes239 configured
  functions/parameters, ALL original source/header comments,25 actual compiler-
  expanded formatter sites,26 static buffers/650bytes and133 ABI literal bytes;
  an inventory mutation is rejected. No source data/format algorithm is read
  from original C at game runtime.
- Both ABI/metadata files pass actual configured C syntax compilation.
- Isolated -O2 memory64 builds succeed via `.cache/sfbase-first-pass/build.py`.
  Reference links original SFBASE; hybrid excludes it and imports its239 JS
  bodies. Original HACKLIB is a dependency in this fixture, specifically its
  existing nh_snprintf routine, not an SFBASE fallback. In production the
  already-migrated HACKLIB binding supplies that same dependency ABI.
- `TELEPORT_NATIVE_TESTS=0 SFBASE_PROBE_DIR=.cache/sfbase-first-pass node scripts/test-tu-sfbase.mjs`
  passes **10,818** direct EmC/JS comparisons. Final log:
  `.cache/sfbase-first-pass/test.log`; build log in the same folder.
  All239 original functions are invoked. Compared data includes the entire
  32768-byte caller buffer, complete static-buffer bytes/return identity, all
  callback traces, complete log strings, NHFILE state/long counters, EOF and
  short dependency reads/writes, mode/fplog mutation, conversion recursion,
  version feature-set writes, actual descriptor errors, repeated table setters,
  external native zero-template callback changes before sf_init, nested callbacks,
  memory growth during callbacks and independent Module tables/static buffers.
  Signed/unsigned64 formatting and size_t/long logger inputs include >32bit,
  >2^53 and signed/unsigned64 extrema. Original20-byte value-buffer truncation
  remains exactly visible (UINT64_MAX returns its first19 digits).
- Read-only peer review found no further concrete defect in30 direct routines
  and representative SF_A/SF_C/SF_X and direct dispatch templates. This is not
  proof of every production world/dependency combination.
- Exact source and two built-artifact hashes are in
  `.cache/sfbase-first-pass/verified-inputs.json`.

Native macOS, actual mixed production-game activation and public recordings are
pending. No native difference is waived, relabeled as a pass or hidden by an
expected-result amendment. Underlying serialization/short-IO callbacks are
controlled dependencies here; this fixture does not claim to retest every
historical/exportascii serializer implementation or the full savegame pipeline.

The original sfvalue_char copies n bytes without bounding its120-byte buffer;
that original loop is preserved. Inputs n<0 or n>=120, and complex_dump reads
from genuinely smaller-than10-byte allocated objects, have original C undefined
memory behavior and are NOT claimed equivalent. No new clamp or safety policy
was introduced. Original genericptr logging checks its pointer argument itself
rather than dereferencing it; that quirk is likewise preserved and tested.

## Exact shared integration recipe (owner applies)

1. Add a registry entry equivalent to:

   ```json
   {
     "name":"sfbase",
     "source":"src/sfbase.c",
     "javascript":"js/ported/sfbase.js",
     "library":"nethack-c/wasm/tu-libraries/sfbase.js",
     "configuredFunctions":true,
     "configuredFunctionHeaders":["include/sfmacros.h"],
     "adapterSources":[
       "js/ported/sfbase-runtime.js",
       "nethack-c/wasm/tu-fragments/sfbase-support.c",
       "nethack-c/wasm/tu-fragments/sfbase-source-data.h",
       "nethack-c/wasm/tu-fragments/sfbase-source-check.mjs"
     ]
   }
   ```

   Standard registry exclusion must remove sfbase.o from production. It already
   derives that object from the source. Do not add another SFBASE source or C
   algorithm fallback. Source checker already supports configuredFunctionHeaders
   for SFSTRUCT; SFBASE needs exactly the same include/sfmacros.h ownership.
2. Include sfbase-support.c in tu-support.c OR compile it once as another ABI
   source. Never both. It defines only original zero-initialized sfoprocs,
   sfiprocs, sfoflprocs, sfiflprocs and their four zero templates, plus typed
   backing/field/dependency helpers. These native aliases are intentionally LIVE:
   original nonconst external native writes must remain observable. There are
   no native SFBASE decision/serialization/formatting algorithms in this fragment.
   Do not also link original sfbase.o, which would duplicate these symbols.
3. Add imports for core namespace and createSfbaseEnvironment. Cache environment
   PER actual services.moduleKey/Module identity. Wrap each entry with existing
   stackSave/finally-stackRestore and withCEnvironment conventions. Arguments:
   - All sfo_/sfi_ functions: args0 becomes environment.nhfile(args0).
   - sfo_version_info/sfi_version_info: args1 additionally becomes env.version.
   - sf_log: args0 is NHFILE view; args2 MUST remain unsigned64 BigInt size_t.
     Other arguments are Number pointer offsets or int32 values.
   - sfvalue_*, complex_dump, bitfield_dump: pointer args are Numbers; n is int32.
   - sf_setprocs/sf_setflprocs: idx int32 plus raw struct pointer offsets. Their
     original assignments create views inside the core/runtime and memmove the
     actual complete compiled struct; external aliases/function pointers remain.
   - sf_init has no args; all73 norm_ptrs_* get raw Number pointers and no-op.
   Pointer results are Number offsets internally; Emscripten's __sig:'p' wrapper
   performs the pointer return conversion (tested in every value helper). Void
   can normalize to zero if required by the central dispatcher convention.
   The miniature dispatcher in test-tu-sfbase.mjs is a complete tested example;
   preserve raw size_t BEFORE converting other BigInt pointer arguments to Number.
4. Existing SFSTRUCT startup `$teleportSfstructInit` MUST remain retained by the
   shared registry/default startup list. It initializes the JS-authoritative
   historical_sfo_procs/historical_sfi_procs dependency tables before main.
   SFBASE's original sf_init copies these live tables; it does not recreate or
   take over SFSTRUCT's initializer. SFBASE requires no separate startup hook:
   its own original initial native data is all-zero backing.
5. Probe builder entry sfbase:
   - Both modes compile scripts/tu-sfbase-probe.c and owned sfbase-support.c.
   - Reference adds original src/sfbase.c plus `-DSFBASE_REFERENCE=1`, which keeps
     helper declarations but suppresses duplicate zero backing definitions.
   - Hybrid omits original SFBASE and adds `--js-library` owned sfbase.js.
   - Both isolated modes compile original prepared src/hacklib.c as the existing
     nh_snprintf dependency. If shared build uses migrated HACKLIB instead,
     retain its real initializer/runtime and typed variadic interface; do not
     replace formatting with an ad-hoc provider or change test expectations.
   - Do not also include the support fragment through full tu-support.c in this
     probe if separately compiling it; shared owner may choose either form.
   - Add sfbase:[] to write-tu-layouts; dynamic layout_count/name/value contains
     every scalar/offset/format constant. No terminal ABI profile override needed.
   - Export these names with underscore prefix according to builder convention:
     probe_serial_count,probe_serial_name,probe_values_count,probe_values_name,
     probe_norms_count,probe_norms_name,probe_reset,probe_option,probe_file,
     probe_pointer,probe_input,probe_close_log,probe_logs,probe_trace,
     probe_snapshot,probe_table,probe_action,probe_value,probe_norm,probe_log,
     probe_layout_count,probe_layout_name,probe_layout_value,probe_stack,
     teleport_sfbase_global,teleport_sfbase_buffer.
   - Test defaults to shared bones-style directory .cache/tu-probes but uses
     sfbase-reference.mjs/sfbase-hybrid.mjs. SFBASE_PROBE_DIR only selects private
     development artifacts, with identical module names.
6. Run sfbase-source-check.mjs during pre-build/source metadata guards. It reads
   prepared source/header and current compile-defines, asks real compiler for
   configured expansions, and checks239 source boundaries/parameters/comments,
  25 formatter __func__/__LINE__ sites,650-byte static storage shape and133-byte
   literal pool. Original/prepared source hashes are frozen in generated header.
   The helper's formatter line is taken from actual CPP expansion, including
   multiline-call C __LINE__ behavior at the CLOSING call line. Never regenerate
   those lines from the opening Snprintf line. No arbitrary-capacity pool exists.
7. Formatter helper signatures distinguish int,unsigned,int64_t,uint64_t,long,
   unsigned long and strings, and retain existing nh_snprintf(func,line,...)
   routing. Logger uses actual FILE*, long, size_t and int ABI arguments. All
   scalar signedness/widths, little-endian target, pointer/long sizes, SFCTOOL=0,
   VMS=0 and legacy Sfvalue macro selection are compiler-guarded. Keep these
   guards visible; changing build configuration needs a fresh source review.
8. Native-builder/probe registration and actual production mixed-game/public
   checks remain serialized with migration owner. This author ran NO full game,
   aggregate native or public recording build for this staged TU.

## PAR02-SFBASE register text for integration owner

PAR02-SFBASE staged implementation: all239 configured original functions are JS
at js/ported/sfbase.js, including130 source-macro expansions owned by
include/sfmacros.h, six direct serializers,73 already-empty original norm_ptrs
functions and30 value/logger/table routines. Original names/order/parameters,
comments and control flow remain. Live compiled NHFILE/function-table aliases,
zero-only external backing, distinct original static-buffer lifetimes and typed
existing stdio/nh_snprintf/function-pointer dependencies are separated into
sfbase-runtime.js, its Wasm library and unique sfbase-* ABI/data fragments. No
original SFBASE C body is a fallback. Function pointer table copies remain live,
including external mutation of zero templates before sf_init; historical table
initialization remains owned by existing SFSTRUCT startup. Exact scalar widths,
signedness, endianness and configuration are compiler-guarded.25 formatter sites
use original CPP-expanded function/line provenance;26 static buffers total650
bytes and ABI literal storage is source-derived133bytes, both guarded. Isolated
-O2 memory64 original-C and imported-JS modules pass10,818 raw data/static-buffer,
callback/log/state/EOF/shortIO/descriptor-error/table-mutation/conversion/reentry/
growth/Module comparisons and invoke all239 functions. Original source/scope,
metadata C syntax and mutation guards pass; read-only peer review found no
further concrete defect. Native macOS, actual mixed production-game link and
recordings remain pending. Original sfvalue_char's unchecked copy and
complex_dump's10-byte read are preserved; original undefined out-of-object
memory cases are not claimed tested/equivalent. Controlled callback fixtures do
not prove every underlying serializer or full savegame integration. No existing
native correction, frozen/pristine source, recording or expected result changed.
