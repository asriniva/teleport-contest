# TU101/J107 MAKEMON — frozen private integration handoff

Original source: `src/makemon.c`, prepared/pristine identical SHA256
`04bb46b793cb7a724544ed5860f57116e4661ce5d052a1321d90dc0167d3ffc3`.
Actual profile has 41 bodies (28 public, 13 private), 279 block comments.
`check_mongen_order` is inactive in this compiler profile and is not counted.
MAIL_STRUCTURES and MAIL are active; the maildaemon rejection remains present.
DEBUG/UNIX/DEBUG_MIGRATING_MONS are
active; SPECIALIZATION/HPUX/DGUX are absent. The metadata guard re-derives the
actual compiler bodies, complete AST types/literals and header field aliases.

Final exact-artifact run: **8,794 original configured EmC-C/hybrid comparisons
PASS; all 41 entrypoints reached**. Both final builds, complete source/CPP/AST/
type/data/origin guards, lexical scope check, const-storage audit and unchanged-
oracle wrong-code rejection pass. This is a private EmC first pass; native-host,
shared-game/public and complete branch/profile coverage remain pending.

Ownership stays private: original generation/equipment/inventory/selection/
growth/mimic/summon bodies are in `js/ported/makemon.js`; typed fields, native
callback/header transport and original TU storage are in its unique adapter.
`class` is spelled `class_` for JavaScript. Four forward gotos use labelled
block exits with one original shared tail. Struct assignment copies complete
native bytes. Automatic buffers/records use native stack allocation, restored
at every original function boundary. All RNG sites set the compiler-derived
caller before evaluating arguments; nested calls retain original macro order.
Lazy ifdebug expansion checks showdebug before evaluating its message arguments
and restores native last_msg after the callback. Stored logical results use
canonical numeric 0/1 without changing short-circuit or single evaluation.
Assignment-expression results read back narrowed native fields, including
uchar level increment wrap and worm-number bitfield writes. The adapter retains
raw production filename makemon.c, assert locations and Snprintf's actual
compiler-expanded closing-macro line; no trace basename normalization occurs.

`mongen_order`, `mclass_maxf`, their initialized flag, zero mextra template,
and `align_shift`'s oldmoves/lev cache have per-Module native-backed lifetime.
The JS source initializes/orders/selects; C support supplies only storage and
transport. Deterministic qsort is an existing prepared foreign dependency;
its comparison remains the original JS function via a typed callback.
Readonly class tables in the private fixture come from exact original source.
All 47 record schemas, 24 global addresses and 39 bitfield accessors come from
actual configured compiler types. Native pointer64/long64/int32/coord16/char8
and enum width/sign assertions remain visible. opoisoned, oc_skill and a_ac use
actual compiler-resolved aliases otrapped, oc_subtyp and oc_oc1. Pointer outputs
and int* bag visibility outputs are live aliases; fresh memory views are used
after native memory growth and callback reentry. Is_special returns a typed
s_level view; tamedog retains its actual boolean return type.

Source macros retain native evaluation ordering: all 188 RNG source origins
are compiler-derived, caller logging precedes RNG-argument evaluation, rn1's
actual six offset expressions are constants, and configured min/max operands
are pure reads. No Maybe_Half_Phys occurrence exists in this source. The
private macro-audit.json records these source-specific observations.

Fixture reset targets were recursively checked against actual record fields:
none of its 21 memset target types contains a true const subobject. Readonly
c_common_strings, genders and def_monsyms use original source initializers;
they are never reset or cast writable. The true const permonst.pmidx field is
not directly written by the fixture; unchanged original monst_globals_init
provides the inherited source initialization, just as original dump_mongen
calls it. Pointer-ID diagnostics compare integer uintptr_t addresses rather
than performing relational comparisons between unrelated C pointers.

Private first-pass commands, only outside coordinator quiet windows:

1. `python3 .cache/makemon-author/build.py`
2. `.cache/emsdk/node/24.19.0_64bit/bin/node scripts/test-tu-makemon.mjs`
3. `python3 nethack-c/wasm/tu-fragments/makemon-metadata.py`
4. `.cache/emsdk/node/24.19.0_64bit/bin/node .cache/makemon-author/scope.mjs`
5. `python3 .cache/makemon-author/storage-audit.py`
6. `python3 .cache/makemon-author/run-negative.py`
7. `python3 .cache/makemon-author/freeze.py`

Exact commands, final logs, artifact input hashes and results are frozen in
makemon-hashes.json and the private reproduction directory. The fixture links
actual original C/monster/object tables and libc for the reference, imports
all configured JS functions for the hybrid, and controls foreign dungeon,
world, naming, UI and allocation outcomes. Entrypoint reachability is distinct
from actual branch coverage. Native-host, shared integration/public recordings,
production allocation/exit/abort boundaries and broad complete-world behavior
are separate unclaimed gates. No registry/build/default/Lua46 edits are made.

The test reaches every configured original entrypoint and compares original
result values, full selected state and traces, native RNG order/origins, messages,
callbacks and stack restoration. Directed cases include all 383 actual species,
equipment/inventory classes/seeds, elemental-level survival/HP, generation
caches, limits/alignment, mimic shop/object shared tails, growth field narrowing,
corpse state cleanup, callback writes, true memory growth, C-to-JS reentry and
separate Modules. Controlled C longjmp provides a bounded interrupted-call
witness; it does not certify every production native unwind or assertion.
The read-only wrong-code loader changes only JS iron-golem HP120 to121 and must
be rejected by the unchanged oracle. The manifest binds the exact successful
artifact inputs, current source/guards/results and preserved raw failure history.

Parent-only integration recipe, after reviewing the frozen handoff:

```json
{"name":"makemon","source":"src/makemon.c","javascript":"js/ported/makemon.js","library":"nethack-c/wasm/tu-libraries/makemon.js","configuredFunctions":true}
```

Include tu-fragments/makemon-support.inc in shared tu-support.c. Expose the
signed-long-long makemon_layout rows from scripts/tu-makemon-layout.h through
the shared layout export. Remove only original makemon.o from the hybrid link.
Import callMakemon from ./makemon-runtime.js in the shared JS runtime and add
the exact makemon-runtime-method.inc method. Library dispatch is
Module.nethackPorted.makemon(services,name,...args). No startup hook is needed;
source-owned arrays/caches have original per-Module static zero lifetime.
Keep original monster/object catalogues and actual prepared deterministic
qsort dependency linked. The comparator enters the same original JS
cmp_init_mongen_order body through its typed trampoline. Public signatures
and private callback imports are compiler-derived in the unique library/support;
private test aliases need not be retained by ordinary linking.

No controlled world/naming/UI callbacks, seed generator, process interceptor or
test-only original MAKEMON include belongs in production. Native-host, complete
world interactions, allocator-refusal schedules, invalid pointers, real
process/abort/assert behavior, all source branches/profiles and mixed-game/public
recording equivalence remain separate gates. This fixture is intentionally
rejected when TELEPORT_NATIVE_TESTS=1. Source and translated bodies retain the
original NetHack license/provenance; prepared deterministic sort is an inherited
dependency and is not claimed as new JS MAKEMON policy.
