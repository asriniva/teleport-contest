# TELEPORT frozen first-pass integration recipe

Reserved TU95/J101. Unique sources only; no registry, shared builders/support,
layout writers, central runtime, selected/frozen ports, or production artifacts
were modified by this author. Prepared/pristine `src/teleport.c` are identical
(2,294 lines; SHA256 e1d9d4255ac148caa4618dc4f275ddf5417d2a2830beca738c3821cf7678e5c8).

The core owns all37 configured original function names/order/parameters/comments,
NEW_ENEXTO ring collection/shuffling/control, source tports4 menu table, static
get_there_from19 string and per-Module in_tele_trap recursion guard. Header macros,
true foreign dependencies, typed field/address/function-pointer/varargs access
and zero-only literal backing are C ABI helpers; no original TELEPORT fallback,
initialized C catalogue mirror or algorithm replacement is linked in hybrid.
Native-macOS, full-game, public recordings, and uncontrolled foreign-world
behavior remain pending. This is actual memory64 Emscripten-C differential work.

## Integration changes for the integration owner only

- Add registry entry name `teleport`, source `src/teleport.c`, javascript
  `js/ported/teleport.js`, library `nethack-c/wasm/tu-libraries/teleport.js`,
  configuredFunctions true, reference prepared, probeContext false.
- adapterSources: `js/ported/teleport-runtime.js`, `scripts/tu-teleport-layout.h`,
  `nethack-c/wasm/tu-fragments/teleport-support.c`, `teleport-source-data.h`,
  `teleport-source-data.json`, `teleport-source-check.py`, `teleport-abi.json`,
  `teleport-probe-options.json` (the latter paths share that fragment directory).
- Include teleport-support.c once in common C support. It must not be included
  twice when building the standalone owned fixture, which includes it itself.
  Its source-private callback address conditional uses only the TU-specific
  TELEPORT_TELEPORT_VALIDATE_SOURCE, defined AFTER actual source include in the
  original reference fixture. Generic TELEPORT_REFERENCE_TU does not leak source
  private declarations into unrelated reference probes.
- Central runtime: import createTeleportBridge from `./ported/teleport-runtime.js`,
  construct `const callTeleport=createTeleportBridge(layouts.teleport)`, dispatch
  `teleport(services,name,...args){return callTeleport(services,name,...args);}`.
  No startup hook or public source storage is needed: only private static source
  data/state is initialized by its owning function, per Module.
- Decode metadata table `teleport_teleport_layout` in tu-teleport-layout.h using
  long64 name/value entries, same mechanism as other ports; include the resulting
  `layouts.teleport`. Constants with observed long operations I_SPECIAL, TIMEOUT,
  STRAT_APPEARMSG are converted to BigInt in the runtime. Typed fields retain C
  signedness; coordinate params and locals narrow signed16, boolean signed8,
  mmflags/rloc/cc/tr flags unsigned32, properties/moves/stasis/mstate signed64,
  species flags and mstrategy unsigned64.
- Build fixtures from `scripts/tu-teleport-probe.c` alone: it defines controlled
  foreign world/dependencies and includes original teleport.c only for reference.
  Add TELEPORT_REFERENCE_TU for original; add teleport.js JS library for hybrid.
  The hybrid never compiles/includes original teleport.c. There are28 original
  public imports and9 private `teleport_teleport_callback_<name>` aliases for the
  standalone probe. The private m_blocks_teleporting alias is also a real game
  callback address used by get_iter_mons; remaining private aliases are probe
  entry points, while source-local calls remain direct JS inside scoped wrappers.
  No source-checker parameter exception is needed.
- Use actual production profile: memory64, -O2 -g, compile-defines.json, forced
  native-terminal.h, prepared include and ncurses include directories. Production
  is make cwd TREE/src input basename teleport.c. PRIVATE fixture only needs
  exact macro-prefix-map `<root>/scripts/../.cache/wasm64-build/tree/src/teleport.c`
  to `teleport.c`; no shared/production compiler flag changes. Header debug
  adapters use the actual basename teleport.c and fixed typed varargs output.
  Runtime preserves lint.h ifdebug ordering: debugcore, save last_msg, evaluate
  thunked formatting arguments, print, restore last_msg on normal return only.
  debug0 uses fixed `%s` ABI adaptation for its sole literal without directives.
  All RNG traces compare full filename, exact original closing line and owner,
  and log caller BEFORE evaluating callback-capable bound expressions.
- Probe exports: reset clear option input menu pointer record field link trap
  dest level stair role debug vision objlevel dungeon tile property trace snapshot
  layout_count layout_name layout_value stack call (all `_probe_` prefix), plus
  malloc/free. Use1MiB stack, memory growth, modular node, HEAPU8 runtime export.
- Shared test wrapper must explicitly set TELEPORT_PROBE_DIR=.cache/tu-probes and
  TELEPORT_NATIVE_TESTS=0. Standalone defaults to private.cache/teleport-first-pass;
  TELEPORT_NATIVE_TESTS=1 rejects BEFORE Module creation, since no native backend
  exists. Never claim this test executed native C.
- Run owned source guard `python3 nethack-c/wasm/tu-fragments/teleport-source-check.py`
  in source verification, plus existing source/scope validators after registration.
  It checks actual fresh production-basename CPP/AST, 1108 MemberExpr/typedef/member
  macro records (including teledest→launch and oc_level→oc_oc2), profile, source
  hash/provenance,37 boundaries/order/params/all comments,22 RNG origins and source
  table/static data. This is a change detector, not an equivalence proof.

## Controlled fixture contract and limitations

The fixture initializes typed real monster/object/trap/level/terrain/vision/menu
storage. ABI helpers and original C read/write that same storage. Coordinate
arrays are true native stack buffers; callbacks can invoke native filters,
reenter and grow memory. Raw C snapshots read coordinate entries, signed/unsigned
long fields, properties and state; zero-monster byte consumer includes padding
before foreign set_mon_data. Pointer-return canonicalization is restricted to
exact known stair objects; pointer values are not normalized in scalar fields.

Foreign helpers are explicit controlled world services (placement, terrain,
rooms, UI, spell, migration, death/life-saving, messages, shop and object effects),
not a full playable world. Trap/object storage is static fixture memory; actual
world deallocation, complete monster AI/region/shop/level scheduling and real OS
UI are not integration evidence. Callback exceptions verify original persistent
trap-guard behavior; they do not claim arbitrary C nonlocal-exit cleanup parity.

## Frozen evidence and limits

Actual fresh -O2 -g memory64 original/hybrid builds pass2,910 unchanged-C/JS
comparisons, all37 configured bodies invoked, with execution witnesses for all22
configured RNG origins. The hybrid has all37 expected source imports and excludes
teleport.c from actual compiler dependencies; reference has zero source imports.
Fresh source/order/parameters/all-comments/lexical-scope guards pass; fresh actual
production-basename CPP/AST verifies signatures/linkage,1108 MemberExpr/type/member
macro records, source data and exact22 RNG origins. Generic
-DTELEPORT_REFERENCE_TU support-only syntax succeeds without original source.
Direct TELEPORT_NATIVE_TESTS=1 invocation rejects before creating a Module.

Tests cover whole-map coordinates/tail guards, ring flags/filter/reentry/growth,
signed-short extremes/narrowing, all native RNG calls/full original origins,
terrain/hero/species checks, source callback address, signed/unsigned64 state and
raw C snapshots, zero-monster raw bytes including padding, menu4/static data,
first-call menu reentry/live volatile callback replacement, both Modules sharing
one bridge, trap recursion and original persistent guard after callback throw,
level prompt/goto paths, long timeout arguments, inventory/billing/revival paths,
repeated automatic native buffers and stack restoration. Foreign-world limits
above remain material; every original branch is not claimed covered.

Wrong-code controls use the EXACT unchanged original-C test suite: removing the
collect_coords draw fails `configured enexto full trace`; eager debug argument
reads fail `debug macro argument ordering full trace`. Originals, expectations,
comparison granularity and failing outcomes were not normalized or waived.

Header debug timing was corrected before freeze: debugcore executes before
last_msg capture and lazy argument reads; only normal completion restores the
message state. The independent source review and the actual callback mutation
witness both support this path. No #line directive leaks from common support.
The compiler reports limited Binaryen postlink optimization because -g was
requested; Clang -O2 is active. Earlier no-g -O2 runs passed the then-current2,220
checks; that earlier smaller run is not the final expanded corpus.

Evidence: `.cache/teleport-first-pass/{test.log,source-data.log,build.log,
import-proof.json,negative.log,negative-debug.log,negative-summary.log,
native-unsupported.log,input-hashes.json}`. The manifest lists exact source,
adapter, compiler-captured header and Wasm hashes. Native/full-game/public
TELEPORT acceptance remains pending; this frozen handoff is isolated EmC only.

Private reproducible authoring/proof scripts are preserved under
`.cache/teleport-first-pass/{inventory.py,generate.py,generate-abi.py,
generate-probe.py,generate-guards.py,build.py,negative.py,evidence.py}`. Do not
rerun generators without reviewing the frozen artifacts and exact source guards.
