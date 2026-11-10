# CFGFILES staged frozen handoff

All **92** configured original src/cfgfiles.c bodies (23 external/69 static) are
implemented in js/ported/cfgfiles.js, retaining original names, order, fixed
parameters, block comments, loops, branches, parser state and source algorithms.
The native variadic carrier uses the existing source-checker convention:
config_error_add(str,...the_args), retaining original va_list local name and
va_start/va_end operations. The sole goto gi_error shares the original switch
backslash/default body through explicit fallthrough. No original C algorithm
fallback or initialized C handler table exists in the hybrid.

Pinned pristine and prepared source are byte-identical: 54,661 bytes/2,076 lines,
SHA256 02b8a704da0e0fa86fd085ef0ce81bd7c60edde0d70ae937a9411de07e95ab47.
No shared registry/builder/runtime/support/defaults, Lua subsystem, selected or
frozen other TU, native service or public artifact was edited for this handoff.
Root owns later shared registration; this is an UNAPPLIED integration recipe.

## Verified evidence and limits

Actual isolated **-O2 memory64** unchanged original C and imported-JS hybrid
builds succeed. The hybrid excludes original cfgfiles.c. Latest build log is
empty. The unchanged suite passes **5,054** comparisons and directly exercises
**all 92** configured bodies, including genuine FILE* and native va_list routes.
Both actual fixture compile modes force the production native-terminal.h and
terminfo include, matching the source/metadata profile. Source/scope checks,
syntax checks and compiler guards also pass. Logs and final
input/artifact hashes are in .cache/cfgfiles-first-pass/verified-inputs.json.

Coverage includes all configured directive handlers and every59-table row,
length/flags/function alias; unsigned character parsing/wrap and modifying input;
section trimming/random selection/sliced return pointers; filtering and aliases;
continuations/comments/empty/too-long lines; nested/secure/error frames; Lua error
list traversal and ownership; full signedlong/unsignedsize_t formatted arguments
above2^53; real libc stdio/read/write/close and file contents; actual partial
fwrite through a controlled short-writing virtual device; function callbacks;
nested parsing/error reentry; heap growth during parser and Lua callbacks; live
locals versus a newly prepended error-list head; function-local stack cleanup,
throw cleanup and independent Modules.

The reference and hybrid both use real libc/stdio/heap/va_list formatting. NetHack
option parsing, bindings, symbols, role matching, display/wait, debug selection,
list formatting, allocation observation, trim/mung/match helpers and Lua API
calls are controlled dependency fixtures. Lua calls record ABI/values and can
reenter source code; this is not a real Lua interpreter/table implementation or
a Lua subsystem replacement. RNG uses a controlled stream and records original
kind/bound/result/filename/line/function, not a real-game RNG backend proof.
Fatal exit/showpaths, every filesystem/permission/close-error path, actual Lua GC,
all malformed/uninitialized caller inputs and complete game configuration flows
remain unverified. Throw cleanup is a JS adapter test, not a native C foreign-
exception unwinding claim. Native C, mixed-game, production and public validation
were **not run** here and remain pending. All92 direct coverage is not an all-
branches or all-inputs equivalence claim.

A separate unchanged-suite negative control removes only the free dependency
call in an isolated copy of the binding. The same comparison fails at4,468
checks during config_error_done: actual ends `;wait;`, while original C emits
`;wait;free:49:1304;`. Exact failure:
.cache/cfgfiles-first-pass/negative-missing-free/test.log. The proper binding
remains unchanged. This demonstrates that removing a real free is visible even
when final roots/pointer values would otherwise match; no expected result was
waived or amended for that injected wrong code.

## Exact source/data/type guards

The source guard reruns the actual production-profile compiler preprocessing and
AST from TREE/src with input spelling cfgfiles.c, current compile-defines,
terminfo include and forced native-terminal.h. It checks all92 original function
signatures/parameters/comments and normalized AST fingerprints;15 native records/
68 accessed native fields plus5 JS-only table fields;65 fixed dependency and6
variadic prototype types;103 configuration macro facts;59 handler row identities;
all8 source statics; original buffer sizes; one original RNG site (line480,
choose_random_part); exact2,237-byte native literal corpus and filename. Compiler
support has **112** static ABI/width/sign/prototype assertions. Source-inventory
mutation is rejected. Every emitted native field path is also checked against
the actual AST-backed schema and native read index; raw untyped alias properties
are rejected. Header member macros are fully expanded into these explicit paths. These guards detect drift; they do not replace behavior
comparison or review.

The eight source statics are JS-authoritative: ignore_errors_on_unmatched,
ignore_statement_errors, default_configfile, configfile, config_line_stmt[59],
disregarded_config_lines[59], config_error_data and config_error_msg. configfile
has a mutable zero-only native256-byte buffer for its original pointer API.
The handler table is a JS factory with original function identities, including
aliases; its original string literals populate bounded native literal storage.
No same-TU constzero C catalogue is filled by JS and then read through optimized
C. Private struct declarations in cfgfiles-types.h are ABI types only, not data
or parser replacements. Automatic buffer sizes remain original256/256/105/1024/
128/1280 bytes. Native struct locals use compiler sizeof metadata and each
function restores its local stack frame in finally, including internal calls.

All source pointer values are exact checked memory addresses, not detached
copies. Field reads/writes use native compiler types/addresses; every direct
memory access creates a fresh heap view. Scalar narrowing and unsigned wrap
follow the actual AST promotions. long/size_t/lua_Integer64 values remain
BigInt; pointer conversion rejects an inexact address. Real memory64 va_list
packing is produced by43 per-call typed C bridges to actual variadic callees;
there is no guessed argument encoder or formatting implementation. The source
config_error_add import receives the compiler's native varargs pointer, carries
it through ...the_args, and source va_start yields that exact live pointer.

## Production filename provenance and initial failure history

Production build.py127-131 sets flags without prefix-map; build.py224 invokes
Make cwd TREE/src. Makefile512 compiles $<; line1201's prerequisite is cfgfiles.c.
Therefore production __FILE__ is exactly **cfgfiles.c**. Independent fresh
production-profile CPP/AST proves debugcore("cfgfiles.c",...) and original RNG
caller filename cfgfiles.c. Exact command/profile is recorded in
.cache/cfgfiles-first-pass/production-cpp-command.json.

The first private fixture included the source through an absolute scripts/../
path, while the first JS AST was compiled with a .cache/... relative path. The
unchanged full debugcore filename comparison correctly failed at3,309 checks.
Raw failure, initial source/runtime/library/schema/support/probe/CPP/AST inputs
and hashes are preserved in path-provenance-initial/. The original compiled
module artifacts were subsequently rebuilt; that archive does not claim to
preserve those earlier binaries. A transient private map to the JS-relative
spelling was built, not used to claim a passing test, and discarded after the
production path was verified. Both final sides use actual production basename;
no trace normalization or expectation waiver was applied.

Only the PRIVATE reference/hybrid fixture build adds this exact macro prefix map
because its #include spelling differs from the real source-unit invocation:

```text
-fmacro-prefix-map=<root>/scripts/../.cache/wasm64-build/tree/src/=
```

It leaves cfgfiles.c unchanged as the suffix. Production requires no new map.
The full debugcore filename remains observed/compared. Root owns shared flags.
The initial isolated fixture omitted the forced terminal header while the
production AST/guard included it; this profile distinction was caught before
freeze. BOTH final compiled fixture modes now force the actual production
header and terminfo include; the unchanged suite, guard and negative control
were rerun on that exact profile. No exemption or expected waiver was used.

## Comparison representation precision

The suite compares source return values, original table names/length/flags/
handler identities, selected live state, linked frame/message fields and ordered
traces. It also compares ALL256 configfile bytes and ALL8,192 fixture input bytes,
including tails and parser mutations; uchar output bytes are compared directly.
There is **no blanket byte scanning or pointer-field canonicalization**.

Absolute pointer addresses in two separately linked modules are not compared.
Known char* return APIs are compared by content; choose_random_part,
is_config_section and find_optparam additionally compare exact returned offsets
within the actual input buffer, preserving null and slice identity. FILE* return
checks compare null/non-null and subsequent actual stdio operations/contents;
they do not compare raw FILE struct padding. Frame/message state follows actual
linked pointers and emits fields/strings, not entire native record padding.

Real source allocations use a controlled observing malloc/dupstr seam. Each gets
its actual allocation sequence ID and size; __wrap_free matches the actual live
pointer before calling __real_free and records that ID/size. This preserves
allocation/reuse/ownership order instead of comparing unrelated absolute heap
addresses. Only the fixture enables --wrap=free; production's typed free seam
calls real free directly. Dependencies' unrelated libc allocations are excluded
from this witness. Resetting fixture world globals is not a global leak detector.
The reentrant Lua-list case retains original C behavior when a callback prepends
a new message after the local old head was saved; source later clears its root.
No changed ownership policy or all-heap/all-padding equality is claimed.

## Shared integration recipe (UNAPPLIED; root owner only)

1. Add registry entry and exclude original wasm/cfgfiles.o in hybrid links:

```json
{
  "name":"cfgfiles",
  "source":"src/cfgfiles.c",
  "javascript":"js/ported/cfgfiles.js",
  "library":"nethack-c/wasm/tu-libraries/cfgfiles.js",
  "configuredFunctions":true,
  "probeContext":false,
  "probeExtraExports":["_probe_open","_probe_close","_probe_vformat","_probe_private","_probe_contents","_probe_file","_probe_callback","_probe_table_name","_probe_table_value","_teleport_cfgfiles_global","_teleport_cfgfiles_read","_teleport_cfgfiles_write","_teleport_cfgfiles_address"],
  "adapterSources":[
    "js/ported/cfgfiles-runtime.js",
    "nethack-c/wasm/tu-fragments/cfgfiles-support.c",
    "nethack-c/wasm/tu-fragments/cfgfiles-types.h",
    "nethack-c/wasm/tu-fragments/cfgfiles-source-data.h",
    "nethack-c/wasm/tu-fragments/cfgfiles-schema.json",
    "nethack-c/wasm/tu-fragments/cfgfiles-source-check.mjs",
    "scripts/tu-cfgfiles-layout.h"
  ]
}
```

No configuredFunctionHeaders is needed. All92 original bodies are in cfgfiles.c.
Existing shared source/scope check logic passes unchanged, including its exact
variadic local convention; do not add a waived function or source-check skip.

2. Compile fragments/cfgfiles-support.c exactly once OR include that actual file
once in shared tu-support.c, never both. Keep cfgfiles-types.h/source-data.h next
to it or add the fragments include path if relocating contents. Private C types
have a unique header guard; fixture includes source types only in hybrid and
skips duplicate private definitions after including original source in reference.
There is no generic TELEPORT_REFERENCE_TU-dependent behavior or C-private data
assert leaking into unrelated reference probes. No production --wrap=free flag.

3. Add scripts/tu-cfgfiles-layout.h to the metadata writer; emit cfgfiles_layout
as cfgfiles.json with exact keys. It includes compiler EIO for the partial-device
test, scalar sizes/sign/endianness, native sizeof keys `size:<C type>` and source
enums. Preserve signed64 bits before Number for ordinary metadata; all current
values fit exactly. Runtime embeds the exact guarded schema, so it needs no new
browser JSON import/resource URL. No pointer/sentinel is serialized through JSON.

4. Import namespace *cfgfiles and createCfgfilesEnvironment in main runtime.
Cache one environment per services.moduleKey in a WeakMap. The tested miniature
dispatcher is scripts/test-tu-cfgfiles.mjs runtime.cfgfiles. Pass every native
argument through exact env.ptr, including the extra native va_list carrier for
config_error_add; core retains its original fixed argument narrowing. Callback
proc arguments may be raw native function pointers or same-TU JS functions.
Return get_configfile/get_default_configfile/fopen_config_file/choose_random_part/
is_config_section/find_optparam as BigInt(rawPointer); all other source returns
are original int/boolean/void. Use withCEnvironment and per-entry stackSave with
finally stackRestore; retain original automatic local frame cleanup internally.
The observation-only runtime.cfgfilesPrivate bridge is needed by this fixture,
not the production API. Map indices0..5 to its source statics and100..158 to
source disregarded flags as in the executable miniature dispatcher.

5. Add fixture to probe build/test lists with the exact exports in
.cache/cfgfiles-first-pass/build.py (25 exports). Besides ordinary exports it
requires probe_open/close/vformat/private/contents/file/callback/table_name/
table_value and four teleport_cfgfiles field/global accessors. Runtime exports
used by the unit are HEAPU8, FS, stringToUTF8, lengthBytesUTF8 and stackAlloc/
stackSave/stackRestore. BOTH private fixture modes require --wrap=free and the
exact macro-prefix map above. Use actual -O2 memory64 C and JS-library links;
reference includes unchanged prepared source, hybrid excludes it. BOTH modes
   must force nethack-c/wasm/native-terminal.h and the actual terminfo include,
   as in private build.py. Add CFG to the builder both-mode native-header list
   and hybrid auto-library exclusion list, preserving the exact private profile;
   this fixture does not use the generic native-libc-library regex bridge. No shared or
production flags are implicitly authorized by this recipe.

6. Add sourceguard invocation with SDK Node:
nethack-c/wasm/tu-fragments/cfgfiles-source-check.mjs. It recreates the actual
production cwd/input spelling and forced native-terminal profile. Source/scope
checkers need only the registry entry. Private verification uses
TELEPORT_NATIVE_TESTS=0 and CFGFILES_PROBE_DIR=.cache/cfgfiles-first-pass; that
explicitly describes EmC-only evidence and must not suppress a native mismatch.
Run strict native/mixed/public gates separately when the owner authorizes them.

## Register append text for parent

PAR07-CFGFILES staged implementation preserves92 configured original bodies,
fixed parameters/order/comments,59-row JS handler table/aliases,8 source statics,
original parser control and original buffer/RNG provenance. Typed C contains
only actual ABI/global/field/file/varargs/callback/zero backing seams, no parser
or C-body fallback. Isolated real O2 memory64 C/imported-JS comparison passes
5,054 checks, all92 bodies directly exercised, with real stdio/short writes/
heap free witnesses/full-width varargs, callback/Lua-list reentry/growth, pointer
slices/full source buffer bytes, stack cleanup and independent Modules. Source/
scope/compiler/data/type/prototype guards pass. An unchanged-suite injected
missing-free regression is rejected at4,468 checks. Initial full-filename failure
is retained; actual production basename cfgfiles.c is proven by fresh matching
CPP/profile and used on both sides without trace normalization. Private-only
fixture macro map/wrap flags and controlled dependency/pointer observation limits
are documented above. No shared/production/default/native/public artifact was
changed or validated. Native/mixed-game/full-world/public remain pending, not
passed or waived. Hash manifest: .cache/cfgfiles-first-pass/verified-inputs.json.
