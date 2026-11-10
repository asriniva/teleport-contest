# TU92 / J98 END private integration handoff

Frozen first pass: **29 configured original functions**, **1,094 exact original
EmC-C/hybrid comparisons PASS**, plus one separate binding-only foreign-JS-error
cleanup witness. Every original entrypoint is reached; this is not complete
branch/profile coverage. Native-host, mixed-game/public recordings and actual
production process/signal/browser/backtrace shutdown behavior remain pending.
No shared registry/build/runtime/default, frozen harness, upstream/prepared game
source, previous port or Lua46 file was edited by this author.

## Original and configured source

- Prepared `.cache/wasm64-build/tree/src/end.c`: 1,962 lines, SHA256
  `9190178742d65ea579645cfa365573a1c3f59cff7a5504856631c42a0c169296`.
- Pristine `nethack-c/upstream/src/end.c`: 1,948 lines, SHA256
  `86076b732d630a31f1c596548631f1af8d033f2aa8bb5987daa53eb0bc02a424`.
- Inherited prepared patches add wintty declarations, suppress the tricky-wizard
  replay message, and emit the final NOMUX_CAPTURE boundary before teardown.
  The JS retains these prepared behaviors. They are not new policy changes.
- Actual compiler CPP/AST: 15 public +14 private bodies. DUMPLOG/SFCTOOL/NO_SIGNAL
  inactive; UNIX/HANGUPHANDLING/SYSCF/PANICTRACE/CRASHREPORT/NOMUX_CAPTURE/DEBUG
  active. `dump_everything` is the actual nhUse-only body, and `dump_plines` plus
  disabled `odds_and_ends` are not counted or enabled. All231 original block
  comments remain, including those belonging to inactive source branches.
- All original function names/order/parameters/local algorithms/control flow
  remain in `js/ported/end.js`. Only reserved JS identifier `in` is spelled `in_`
  in the two affected scopes. Source has no goto. Source deaths16/ends16 and
  death_fixups2 stay authoritative JS data. The fixup `why` symbols resolve via
  actual compiler constants at use, avoiding access to a transient C environment
  during module loading. No endgame policy or original-body fallback lives in C.

## Owned production and development files

- `js/ported/end.js`, `js/ported/end-runtime.js`.
- `nethack-c/wasm/tu-libraries/end.js`.
- `nethack-c/wasm/tu-fragments/end-support.inc`, `end-metadata.py`,
  `end-runtime-method.inc`, this `end-integration.md`, and `end-hashes.json`.
- `scripts/tu-end-layout.h`, `scripts/tu-end-probe.c`, `scripts/test-tu-end.mjs`.
- Private repro/generation inputs, actual commands/logs/artifacts/summaries:
  `.cache/end-author/`. Initial pre-edit divergence declaration and exact actual
  compiler inventory are `divergence-handoff.md` and `inventory.json` there.

`end-hashes.json` separates production, test, prepared dependency and private
reproduction hashes. The author changes only the paths above. Root owns shared
promotion and the public divergence register.

## ABI and source semantics

The adapter uses54 compiler-derived record schemas,16 native bitfield accessors,
40 native global addresses and fresh views after native calls/memory growth.
Native layout/type assertions retain signed char8, short16/coord16, int32,
long64/time_t64, unsigned IDs/masks and pointer64. Source `emptygrave` accesses
exactly rm.flags; done_stopprint accesses program_state.stopprint. Header
property/paranoia/Role/Race/container/file-mode/ctype/string macros are expanded
with actual configured semantics. Value-producing logical operators are
canonicalized where required, preserving short-circuit/single evaluation.

- Native automatic buffers and local char/unsigned cells remain actual scoped
  stack storage; recursive original calls with automatic storage use callLocal
  save/finally scopes. No global buffer substitutes for original automatic data.
- Char** arguments and fields remain live aliases. Sort copies every native
  valuable_data byte, including padding, into/out of an actual automatic record.
- Killer nodes allocate/free real native memory; linked references, callback
  writes and serializer out-parameters stay live. Readonly source strings use
  a derived perModule zero-only2682-byte pool (150 source/compiler literals,
  including actual production __FILE__ spelling end.c). No dynamic strings are
  substituted or admitted into that literal corpus.
- Schroedingers_cat and NH_abort's recursive aborting static have independent
  perModule state. Source catalogue arrays are readonly JS-owned source data.
- Panic receives its actual native va_list pointer and invokes real vsnprintf;
  other varargs use11 actual compiler-promoted argument shapes. Formatting stays
  with native libc, preserving `%ld`, native pointer/string aliases and widths.
- Native signal callback trampolines point to the same original JS done1,
  done_intr and done_hangup functions. Unknown callback identities are rejected.
  cmdq_add_ec preserves actual wiz_makemap identity. Sound callback invocation,
  signal registration, exit/abort and external report/backtrace functions remain
  typed dependency boundaries.
- All7 configured direct RNG origins retain actual source function/line metadata.
  Strlen's physical origin remains really_done:1317. Actual production C is
  preprocessed from cwd TREE/src using basename end.c. The private original-C
  include has an exact directory→empty prefix map solely to match that spelling;
  fixture records complete raw filenames, with no basename normalization.

## Parent-only registry/build/runtime integration

Add the TU entry with configured function discovery:

```json
{"name":"end","source":"src/end.c","javascript":"js/ported/end.js","library":"nethack-c/wasm/tu-libraries/end.js","configuredFunctions":true}
```

Include `tu-fragments/end-support.inc` from shared tu-support.c. Extend the shared
layout export with the `end_layout` rows from `scripts/tu-end-layout.h` (entries
are signed long long, not size_t). Exclude original end.o from the hybrid link.
Import `callEnd` from `./end-runtime.js` in wasm-runtime.js and add the exact
method in `end-runtime-method.inc`; library dispatch is
`Module.nethackPorted.end(services,name,...args)`. No initialization hook or
source-data startup is needed because all original source-owned tables are
private and statics are lazily Module-owned.

Public original imports15: done1, done2, done_in_by, panic, done_object_cleanup,
done, container_contents, nh_terminate, delayed_killer, find_delayed_killer,
dealloc_killer, save_killers, restore_killers, build_english_list, NH_abort.
Panic has the native variadic ABI signature vpp; other signatures come from the
actual original compiler types.

Private native callback imports required in production support:
`teleport_end_private_done_intr(int)`,
`teleport_end_private_done_hangup(int)`. These are ABI trampolines into the same
original JS functions, not alternate algorithms. Fourteen
`teleport_end_test_<original-private-name>` aliases exist for the private fixture;
normal linking need not retain otherwise-unused private test aliases.

The production support must keep actual signal/process/report dependencies.
Only the isolated fixture overrides exit/abort/signal; none of those test
interceptors belongs in production shared support.

## Reproduction and exact evidence

From repository root, with the configured SDK already installed:

```sh
python3 .cache/end-author/build.py
.cache/emsdk/node/24.19.0_64bit/bin/node scripts/test-tu-end.mjs
python3 nethack-c/wasm/tu-fragments/end-metadata.py
.cache/emsdk/node/24.19.0_64bit/bin/node .cache/end-author/scope.mjs
```

The private builder compiles actual prepared END once as original C and excludes
it from the hybrid. Both link actual prepared objects.c/monst.c catalogue data
and actual libc/malloc, at -O2/memory64 with memory growth and protected C fixture
longjmp. Actual commands are reference-command.json/hybrid-command.json. The
unit compares result values, global/property/object/linked-killer state,
serialized bytes, valuable_data padding digest, messages/dependency ordering,
RNG and native stack restoration. It covers all29 entrypoints, exact disclosure
output/default bytes, saturating signed64 scores, recursive valuables/artifacts,
limbo cleanup, life-saving/fuzzer/quit/endgame paths, original monster/mimic
catalogue fields, multi-node restore and serializer callback writes, real heap
growth with reentry/automatic-buffer rereads, separateModule cat/abort state and
captured termination sequencing. `summary.json` reports reachability separately
from incomplete branch coverage; `unit.log` records the PASS count.

A read-only loader changes only JS wordcount's initial count0→1. The unchanged
unit rejects empty-list return1 versus original-C0 (`wrong-core-negative.log`,
`negative-summary.json`). It changes no oracle, expectation, selected source or
C build. The metadata guard independently checks source/profile/function/order/
parameter/comment/data/literal/type/macro/origin assumptions; the Acorn scope
check passes all tooling fixtures and the original END core.

## Explicit limits

Foreign gameplay/world, naming functions, windows, IO serialization hooks,
process termination, signal registration, sound exit and browser/backtrace
functions are controlled observable fixture dependencies. Their independent
production behavior, real OS signals/exit/error paths and complete cross-TU
world interaction are not certified by this component fixture. Literal libC,
actual catalogue source, native allocation/records and memory growth are real.
The fixture does not execute the real process exit, abort or browser launch.

All entrypoints are reached; all branches, configuration profiles, allocator
failures, invalid pointers, source undefined behavior and full gameplay are not
exhaustively tested. In particular the source debug diagnostic after freeing a
killer is not repaired or claimed safe for invalid dangling-pointer use. The
binding-only synthetic JS error proves C/R/T and inner binding stack restoration;
its interrupted outer C fixture instance is discarded and is not a general
native unwind/catch guarantee. TELEPORT_NATIVE_TESTS=1 explicitly rejects this
staged EmC fixture. Native-host/shared game/public recording gates remain with
root before production promotion.
