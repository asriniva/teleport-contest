# Engine branch tests (in progress)

This work does **not** establish complete branch coverage. The current subsystem
tests have many unexecuted decisions even when they enter every exported function.
The new gate keeps these outcomes visible and fails until they are covered.
The runner excludes recorder sessions and tests which read session-file prefixes.

## Running

Use the configured SDK Node executable if Node is unavailable on PATH:

```sh
.cache/emsdk/node/24.19.0_64bit/bin/node scripts/run-engine-branch-coverage.mjs
```

The command runs the instrumentation checks, measured-field/callback audit,
production engulf regression and expanded matrix, 17 production window bindings
across seven owners, literal production-service resolution, additional UHITM/MHITM/MHITU
original-C comparisons and a seeded TRAP sweep, the existing 138 subsystem suites, dependency contracts,
production CLI/allocator tests and original-C versus production-main integration
tests (including LIGHT). It requires the same
prepared original-C fixture caches as the existing subsystem tests. The
implementation fixtures deny Wasm; the original C oracle runs separately.
The existing default test command and historical source qualifications are
unchanged.

`--report-only` produces diagnostics without failing solely on coverage gaps;
it still fails for a failed test group. It is never branch acceptance. Optional
subsystem names select a smaller diagnostic corpus, while the inventory still
includes the entire engine scope. No recorder is invoked by either mode.

Each run writes logs, execution receipts, a compressed inventory and compressed
per-process coverage records under `.cache/engine-branch-coverage/RUN/`.
The compressed final report lists every outcome by source file, line, owning
function, kind, hit count and status. Each covered outcome can also name a
successful source-bound process receipt as a witness; failed, changed-source and
unknown-exit processes cannot supply witnesses. `latest.json` points to the last completed
run. To regenerate a report against current source:

```sh
node scripts/branch-coverage/report.mjs RAW_DIRECTORY OUTPUT.json.gz
```

Source changes cause a hard error. Legacy records without process exit status
remain diagnostic and cannot establish passing-process acceptance. Failed
processes contribute no hits. The process receipt also records the entry test's
source hash before execution and rejects changes during execution; this does not
pin its entire dependency tree.

## What is measured

The scope is all JS in `js/ported`, `js/nethack`, `js/c-runtime`, `js/lua`,
`js/platform`, `js/libraries`, and `js/ported-utilities`, plus the active root
runtime/terminal/storage/recorder-adapter helpers listed in `loader.mjs`.
There are currently 510 modules. The obsolete mixed-engine root modules and
vendor/reference backends are outside this scope. All scoped files are inventoried,
including modules which no test loads. The original-C reference worker is excluded
from hit collection. Dynamically generated user-program code and cached fixture
support are outside this static source inventory; the code generators themselves
are included. No claim is made about every possible Lua input program.

The inventory includes function entry; both outcomes of `if`, conditional and
loop tests; logical short circuiting; optional member/call decisions; switch
case-body entry and implicit no-match; iterator continuation/completion; default
initializers; catch entry and explicit throws. Function entry is an additional
obligation, not a substitute for testing a function's decisions. Summary outcome
counts include function entry and therefore are not a standard branch percentage.
Switch body entry includes fallthrough.

Parameter defaults record initializer execution directly. A conservative lower
bound for supplied arguments is derived per process from completed function calls
minus all initializer executions. Calls which throw during parameter setup can
reduce this bound; they cannot manufacture a positive supplied-argument hit.
Anonymous default functions/classes retain their inferred names. Old records
without default-tracking registration cannot contribute this inferred outcome.
Local destructuring declarations use the same conservative bound from completed
declarations. Initializer failures cannot manufacture supplied-value hits.

Member logical assignments retain their native operator and use a forwarding
receiver to observe the original getter, preserve setter receivers and evaluate
computed keys once. For-in tracks actual body entry and normal empty completion;
enumeration failures cannot count as empty iteration.

Future unsupported constructs remain failing gaps: defaults in unsupported binding
contexts, async iteration, and super/private optional calls or logical assignments.
These are not silently excluded. Direct literal conditions and private functions
whose complete call graph supplies a closed immutable parameter value get
explicit unreachable-outcome proofs. Exports, aliases, writes, eval, unknown
calls and contradictory hit evidence reject these parameter proofs. Exception possibilities in
arbitrary expressions are not claimed as a comprehensive exception inventory.

Instrumentation operates in a test-only loader. Production JS and C are untouched.
It preserves operands and evaluation order; dedicated equivalence cases check
getters, receivers, frozen objects, iterator closing, exceptions, inferred names,
generators and short circuiting. Every transformed module is parsed again.

## Correctness checks and limits

The field audit validates literal measured record fields and window/sound
callback names/signatures using the measured C metadata. It follows local typed
helper functions and simple aliases, including literal templates and escaped
strings. Dynamic names are reported as outstanding runtime obligations.

The expanded engulf test uses the production UHITM window provider and all eight
visibility/digestion/enfolding combinations. It checks event order, both delay
boundaries, display-RNG callback identity, and replacing the window callback
between delays. Its other services remain controlled test doubles; this is not
full-game C equivalence or proof that the leaderboard deadline is satisfied.

The production window-binding test checks 60 real dispatches across UHITM, APPLY,
ENGRAVE, LIGHT and COLORATT services. It validates live callback replacement,
integer/boolean narrowing, full-width menu flags, pointer forwarding and stack
depth, verified heap growth between callbacks and 30 null/incompatible-pointer
rejections, while restoring every replaced table entry. These are boundary contracts,
not game-policy C comparisons.

The supplemental combat matrices compare original C with the pure-JS bindings:
UHITM covers 102 routines across 32 seeds plus5,148 damage-dispatch cases over39
handled damage types,11 defender species, three roles and four seeds, plus7,020
property cases over15 intrinsic/equipment/blocked/high-bit properties and three
roles; MHITM covers 22 routines across 32
seeds plus 12 attack configurations; MHITU covers 30 routines across 32 seeds.
A further TRAP matrix covers 4,452 comparisons across 21 trap effects, hero and
monster subjects, 16 baseline seeds, seven intrinsic/extrinsic/blocked property
variants, all eight configured trap flags and their union, and eight original
monster catalogue forms. Another11,400 entry/dispatch cases cover selector/default
diagnostics, all23 valid trap types, trapped/free and seen/unseen states, hero
property/force combinations and all46 species named by the configured source.
It checks the declared scalar/property/species fixture
snapshot and complete per-case RNG/dependency trace.
They check return values, complete fixture state/trace, pointer identities where
applicable, and restored stack/context/module-static state. Fixture dependencies
remain controlled. These inputs supplement the existing hand-authored subsystem
cases and do not claim that all combat decisions are exercised.

Coverage is execution evidence. The gate also requires passing test groups and
known successful coverage-process exits. Neither instrumentation nor a hit count
provides a behavior oracle; original-C comparisons and specific assertions remain
required. Full-engine branch acceptance is unfinished.

## Production-world corpus and evidence

`run-production-world-branches.mjs` discovers the independent full-original-C
versus pure-JS main-world tests. Selection audits static/dynamic literal imports,
reexports and transitive script dependencies for session readers and recorder
drivers, with negative controls for hidden and cyclic dependencies. Currently98
scripts qualify, including new engulf and level-teleport cases; the four required optional-interaction
modes expand these to101 cases. The private monster-movement original-C build is
included explicitly; native assertion and bundled-assets contracts run separately.
Files referenced through computed
paths are not a general static-analysis guarantee; source review remains required.
Two children run concurrently, with individual logs, source hashes, exit statuses,
timeouts and signal forwarding. Native C retains its reference Wasm runtime;
existing per-call guards deny Wasm/network to the JS implementation. Unused lazy
network globals are removed before loading the tests, avoiding Node's Undici
initialization during temporary guard restoration.

Reference-side calls to the shared screen/clock/file normalization utilities use
a test-only synchronous counter exclusion. Production imports retain normal
counting. Nested/throwing observer controls verify restoration; original return
values and exceptions are preserved. Screen encoding is a normalization utility,
not a recorder driver. Asynchronous observer work is not supported by this scope.

The new engulf test begins at a genuine MAIN input callback, invokes original
`polymon`, `movecmd`, `makemon`, `do_attack` and `dmonsfree`, and compares each
setup/combat world, both complete RNG states/logs, terminal bytes and all frames.
The real message/delay functions are observed and delegated, never stubbed.
Positive assertions require native `gulpum` execution plus swallow/two-delay
ordering. Only the selected purple-worm/troll scenario is claimed here; the
controlled matrix covers the other visibility/digestion/enfolding combinations.

An initial overly broad selection accidentally ran the233-key public APPLY
prefix test before it was identified and the batch stopped. That result is not
part of the non-session corpus or acceptance evidence. The restarted batch
excludes all18 identified session-input tests. A further frozen wizard-victory
replay is excluded; its metadata preflight failed before gameplay. Failed/aborted
receipts are kept.

Old DOGMOVE/DOKICK ABI metadata pins the reference-adapter source preceding
5031c28's two pointer-format edits. A narrowly checked inverse verifies the exact
current hash, reconstructs the exact pinned predecessor and rejects any other
source. The immutable original ABI hashes are unchanged. This is historical
provenance, not a claim that caller/native formatting are equivalent; production
tests execute the current JS owners and original C oracle. A second exact inverse
qualifies the historical RUMORS source before5031c28's line-buffer initialization
fix. That fix changes malformed/truncated-input behavior; no equivalence for such
inputs is asserted. WERE also needs the exact one-line inverse for5031c28's
addition of explicit libc options to `createCStdlib`; default and explicit profiles
are not declared equivalent. All three inverses have mutation rejection controls.

Two preexisting tests needed additional post-consolidation corrections: MON
assertion provenance resolves old metadata paths through `currentLayoutPath`, and
the bundled-assets test verifies the relocated exporter through the exact source
inverse. `layoutSourceSha` hashes typed byte buffers directly without using an
expected value or source-path projection. Exact test-only inverses are recorded
in `engine-test-source-successors.json` and validated by the existing relocation
checker, with mutation/membership controls. DISPLAY and SHK additionally export
their existing comparison helpers, preserving their original cases byte-for-byte.
New matrices reuse those helpers; SHK uses its existing supported one-case setup
mode before the additional cases. Historical relocation and native
receipts are unchanged. The corrected original assets test passes real MAIN with
Wasm/network unavailable;157 additional asset byte/mode witnesses match original-C
assets and two malformed JS bundle contracts pass. All35 native MON assertion
checks pass. The failed pre-fix receipts remain diagnostic evidence.

Supplemental small-policy tests add66 original-C STAIRS/RECT cases,252 original-C
WERE/MPLAYER/WRITE cases,64 leader-inventory cases and80 original-C calendar cases across a full Metonic
cycle. Explicit JS fault/provider contracts are reported separately. The isolated
calendar reference profile omits the inherited recording-clock parser patch;
those clock-adaptation branches use explicit JS dependency contracts instead.
Additional suites pass168 DISPLAY cases/672 full comparisons,3,840 nonfatal ZAP
beam/property cases and3,338 shop-pricing cases. Fatal ZAP death/poison paths are
not claimed by that fixture; separate real-MAIN fatal cases are described below.
The ABI rejection matrix passes5,583 invalid
single-field contracts across17 eligible production owners, checking exact error
messages, stack/context restoration and no heap growth. Those are explicit JS
boundary contracts, separate from C policy cases.

The assembled-program audit reproduced three missing bindings: TELEPORT tried
to resolve the header macro `You1` as a function, SHKNAM tried to resolve a window
callback as a public symbol, and O_INIT did the same for `wait_synch`. Their fixes
expand `You1` exactly as `hack.h` defines it and dispatch the measured window
callbacks. The 451 literal lookup checks resolve deferred symbols too; three
guarded optional process/filesystem providers remain explicit obligations.
Window tests now pass68 dispatches and34 invalid-pointer/signature rejections
across17 bindings/seven owners. Percent-bearing macro text is checked literally.
Eight actual MAIN-world level-teleport calls match C worlds, RNG logs, TTY and
frames, including two real source `You1` branches. No recorded input is used.
`engine-service-source-successors.json` records exact inverses for these three
fixes, plus the MON fix below, with13 pinned-byte/mutation/membership controls. Historical native
receipts are retained; changed formerly failing paths are not claimed equivalent.
The earlier aggregate (133,699 hit /78,582 unhit outcomes) predates these fixes;
its source-bound records cannot certify the changed files. A fresh full run is
required, and all-branch acceptance remains unfinished.

The new MON movement test found `W_NONDIGGABLE` incorrectly represented as a
BigInt. The shared MON factory now preserves its native integer type and keeps
all seven equipment masks as BigInts. Production header contracts and MAIN-created
rust-monster comparisons cover actual source-derived movement permissions and
both nondiggable states beside iron bars. The complete position matrix contains
21,831 cases (383 species ×19 masks ×3 terrain patterns); its7,277 rooms-only
subset passed before the fix. All21,831 cases subsequently passed from ordinary
source, before rebasing onto238be60. Rebased-source validation is separate.

`test-display-darkroom-branches.mjs` adds40 full-map cases/80 comparisons over
five dungeon contexts, dark/color/rogue toggles,29 glyphs and1659 cells.
`test-engine-fatal-zap-branches.mjs` runs death rays, disintegration and a direct
fatal ATTRIB poison call. It compares consumed input boundaries, surviving worlds,
both RNG logs, TTY, frames, all file paths and every persisted byte. The one C-only
author-trigger boundary is checked and excluded explicitly. The reference's
initial lazy-file permissions differ from JS disk modes; modes are not claimed
equivalent here. Direct poison-handler coverage does not establish ZAP caller
coverage. The three scenarios require actual native termination and death text.

A fresh full run after the first three fixes passed its matrix groups and47
subsystems, then was stopped when the fourth defect superseded its source. Its
interruption receipt and partial results remain explicit, not a complete pass.
The362 records from the older diagnostic run were losslessly archived to
`raw-archive.tar.xz` with `raw-archive-index.json` and restore notes in that run's
cache directory. Every original gzip was proven byte-exactly reconstructible,
and every archive member was verified before redundant copies were removed.

The complete138-suite subsystem run passed19,509,189 assertions. Dependency
contracts passed after restoring the pinned missing Lua archive link. Production
world cases pass across the initial batch and targeted recoveries, not a single
immutable all-green run. The quest fixture's default aging scenario dies in
original C; the runner explicitly selects its existing controlled safety sweep,
retaining positive quest-assignment assertions and C/JS comparison. Eight fresh
generated keyboard scenarios across two roles/four seeds pass87 comparisons
without recorded input. Exact receipts remain in the worktree cache; no
complete-engine or leaderboard acceptance is established.

The worktree was rebased onto238be60 before the requested commit. The four
source inverses preserve that main snapshot and compose with its pointer-limit
layer;13 composition/mutation controls and41 original pointer-limit controls
pass without changing historical hashes. Selection now distinguishes actual
recording-directory readers from ordinary test prose:12 previously excluded
independent tests are retained. Public session readers and frozen replay receipts
remain outside this corpus. Recorder CI is separately permitted for the requested
main push. Whole-engine branch acceptance remains unfinished.

Rebased238be60 verification: all21,831 MON position cases pass from ordinary
source, all14 targeted production/engulf/teleport/fatal/assets/assertion checks
pass, and71 instrumentation,35 gate,19 closed-parameter controls plus510-module
syntax and measured-callback audits pass. All2203 current source/evidence hashes
qualify. The full138-suite/all-world corpus was not rerun after this rebase;
earlier complete/partial runs above remain historical, and full branch readiness
is not established. Normal recorder CI is permitted for the requested push.
