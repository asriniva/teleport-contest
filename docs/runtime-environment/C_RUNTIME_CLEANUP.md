# Common-runtime cleanup

Isolated worktree: `/Users/arj/Desktop/nethack_comp/c-runtime-cleanup`.
Branch: `cleanup/c-runtime-rect`. Original baseline: `df33dd4`.
Rebased again onto `origin/main` at `8cf4880d8cf7fb9104635f068564a5de87523fe7`.
The earlier integration baseline was `059e175`; its validation remains historical.
The latest rebased foundation commits are `11dbceb`, `04bfe3b` and `c0740be`;
this document covers their continuation.
No other worktree's source or shared cached oracle is written by this work.

## Resulting structure

```text
source-shaped js/ported/*.js
           |
NetHack declarations, header aliases and module bindings (js/nethack)
           |
shared memory / records / callbacks / linker / libc (js/c-runtime)
           |
JavaScript buffers and injected filesystem, time and I/O services
```

The generic runtime is independent of NetHack. The standalone composition root
uses its per-instance factory and linker. Both record-view APIs share one cached
record/indexed-view implementation, preserving their explicit compatibility
policies. Address-based modules consume schema-driven bindings instead of the
standalone module wiring reimplementing C field/global/callback operations.

The extracted library/callback/type factories retain their prior bodies;
`getpid` is explicitly supplied by the configured platform wrapper and typedefs
are injected from NetHack declarations. The old JavaScript runtime provider
moved out of `ported` to `nethack/runtime.js`. Its compatibility re-export was
subsequently retired after all known consumers moved to the canonical entry.
The game algorithm files, original C, compiler flags, terminal capabilities,
input/output transport, shadow recorder, snapshot serialization and frozen
contest files are unchanged. No missing dependency is replaced with a stub.

The six remaining compatibility files in `standalone` are intentional entries. They
allow other integration branches to keep their current imports. Specialized
translation adapters and the existing synchronous C scope facade stay available
for both providers. They may carry NetHack-specific declarations/header behavior;
those are not generic C logic to hide in this runtime. Mixed-backend deletion
is a later acceptance-dependent removal, not part of this cleanup.

## Provenance

`c-runtime-manifest.json` binds the shared sources, NetHack binding layer,
compatibility entries, scanner/provider declarations, relevant tools and tests.
`write-c-runtime-manifest.mjs --check` rejects changed inputs. The scanner exporter
was extended to bind its relocated implementations and libc profile, then rerun
against the real existing compiled C oracle. Its measured values and reference
receipt did not change. The WERE exporter now binds the relocated NetHack base
provider; its now-unused compatibility source pin was retired. Its declarations
did not change.
The relocation check independently verifies both declarations excluding only
source hashes. Historical oracle receipts and policy baselines are not rewritten.

Oracle directories used for broader checks are independent clone copies. A
second selection matches every recorded source hash before choosing among
versioned caches; no stale-reference hash is waived. The worktree's `.cache`
contains the original failed attempts and actual rerun results.

## Validation status

After rebasing, all14 focused runtime/component checks pass: boundary and
relocation audits; memory and linker contracts; base runtime; RECT;13-module
address transport (23,700 checks); native libc; scanner (1,189 comparisons);
stdio buffering; Lua/I/O; serialization; terminal and production isolation.
Main's targeted special-interaction scope guard also passes138 policy/3 frozen
checks and528 production closure files. Genuine-main startup, first wait turn,
initial save exit and all four C/JS save-producer/restore-consumer combinations
through the first restored prompt pass. That last test explicitly does not
accept complete saved-state semantic equivalence or resumed gameplay.

Pre-rebase connected tests also passed hero/display/level startup and generation,
first-level contents, windows, status, movement/pets/inventory, inventory
attributes, glyph cache and first display (10,881 comparisons). Ten initially
missing/stale-reference checks passed on independently copied source-matching
oracles. Equipment startup's first bounded attempt hit the development driver's
300-second cap; the unchanged unbounded component rerun passes14,241 comparisons
across47 cases in308.32s. Equipment actions, runtime info, WORM, report and
attribute-state checks passed. The pager matrix likewise reached that driver
cap on its earlier attempt. The final unbounded rerun now passes14,805 checks
across47 cases in240.968s. The earlier level-persistence run stopped on a stale
source pin; after the rebase and owned provenance correction, the final run
passes852 connected comparisons without changing its assertions or oracle. The broad run was stopped at user request
before rebasing, including its active child; it is not an aggregate acceptance.
Historical bounded/failed logs remain under `.cache/c-runtime-cleanup/`.
Complete pure-JS game acceptance and mixed-backend retirement are outside this
refactor's acceptance; it changes architecture without claiming new gameplay.

Earlier attempts failed on an absolute `runtime-environment/js/standalone/stdio.js`
pin (expected `65866af8`, observed `051933cd`); the unchanged baseline checker
reproduced that failure at the time. Those failed logs remain historical evidence.
The final aggregate source-scope check now passes all138 policy/3 frozen checks
and528 production imports. The cleanup's exact pruning recipe retires only pins
for its six deleted forwarding files; unrelated pins are not refreshed. Some
inherited ABI receipts still name absolute external reference paths, so this
passing check remains dependent on those source-matching reference inputs.

The final audit also caught a libc pin missed in the foundation move. The
provenance updater now verifies the complete original libc factory against
`df33dd4`, excluding only the documented platform `getpid` extraction, and binds
the unchanged new wrapper before migrating that one old pin. This closes an
owned provenance gap rather than waiving its assertion.

## Completed shared-adapter and dead-code sweep

132 identical helper bodies across58 translation adapters delegate to18 shared
functions in `js/c-runtime/adapter-memory.js`. The operations cover integer
conversions/cells; descriptor reads/writes/decoding and pointer arithmetic;
scalar/pointer properties; indexed/pointer arrays; aggregate initialization;
type sizes and vararg-format shapes. No NetHack header decisions moved into the
generic runtime. Game-specific alias/declaration code stays with its bindings.
Each adapter keeps its local signatures and source-specific conventions and
uses one `Crt` namespace import. The extraction tool checks all132 body hashes,
all occurrence/formal inventories, receiver independence, JavaScript syntax and
complete source inverses before mutation. The candidate set is preflighted.

Six obsolete forwarding files were removed: standalone bitfields, environment
inputs, qsort, scanf and stdio, plus the old ported base-provider path. Eight
consumer/tool files changed only at declared import/evidence/source-list points.
The pruning audit checks all tracked literal imports for references to deleted
paths. Required compatibility APIs remain; no active bridge is deleted.

The helper and affected adapters are declared build inputs, including previously
implicit runtime adapters. Ordered C-unit selection is unchanged. The strict
Makefile guard retains every old profile and adds exactly two complete
registry/Makefile pairs for this metadata-only change. Tests reproduce the actual
historical inverse and reject a one-byte change in either input. The58 live
provenance files change only reviewed dependencies and their transitive hashes;
known stale, unrelated pins are not refreshed. Actual address/scanner/WERE
exporters reproduce the projected declarations and provenance.

TOPL's original178 compiled-input pins remain immutable. Its checker accepts
only the reviewed adapter's exact inverse to its original compiled hash, binds
the shared helper and recipe, then snapshots all actual replay inputs. Every
original C/header/compiler input still requires its raw original hash. The
existing behavior/coverage assertions and actual fixtures are unchanged. Its
summary separately records original compiled pins and actual replay hashes;
it does not call the migrated adapter an unchanged compiled input.

The final component run and integration results are recorded in the companion
validation record. LIGHT's diagnostic difference is explicitly an existing
failure, not a passing component or a platform waiver. A test-only loader using
the exact pre-extraction LIGHT adapter produces byte-identical failure output
(`id=null` versus the C diagnostic's `id=0`). No expected result changed.

The initial expanded generator had a parenthesized-arrow syntax defect. Its
output was corrected and all candidate modules now parse before any write.
The failure and corrected-attempt logs remain in the worktree cache. An
unnecessary selected-probe rebuild attempt stopped before compilation on the
existing missing `.cache/uhitm-author/ast.json`; the current central INVENT pair
already passes its original assertions. No guard was disabled to build it.

## Final acceptance and size

The pre-completion cleanup is complete; the individual steps and evidence are
listed in `C_RUNTIME_CLEANUP_PLAN.md`, with machine-readable outcomes in
`c-runtime-validation.json`. No original C input, game policy or compiler flag
changed because of the cleanup. Main's explicit VISION correction is preserved. The final game checks include actual startup/save/restore and a genuine
2,028-turn starvation death:3,576 inputs,3,731 frames and204,539 terminal bytes
match the original-C recording, along with its asserted RNG and world state.
That fixture does not establish arbitrary complete-game or native-host parity.

Against pinned rebased main `059e17579a72ec6325e7b4d7e7fd7eead577d79b`, all
production `js/**/*.js` files total5,491 fewer UTF-8 bytes,163 more physical lines
and15 more files. The shared runtime adds explicit ownership boundaries while
removing repeated implementations. These are raw-source measurements, not
bundle-size or performance results. Later unrelated main features are excluded
from the comparison. Nothing was pushed or merged into main by this work.

The audit tools use exact historical git objects, including the pre-helper
foundation commit `c0740becc16e413e0eab9bc55747381841faf80b`. Integration must
preserve those commits in history; a squash or cherry-pick requires separately
reviewing how the exact baseline inputs will remain available. Production has
no git dependency. Main has advanced since the recorded rebase baseline; this
branch's evidence and size comparison name that baseline explicitly.

The remaining provider-consumer checks pass:770 configured original-C regex
comparisons,996 calendar/runtime comparisons in each of five timezones, and
actual MEMFS-vs-JS save/bones payload comparisons including1MB binary data.
The filesystem test initially lacked its local oracle files; independent CoW
copies of the existing reference mjs/Wasm artifacts supplied those exact inputs,
with no shared artifact edit. That failed attempt is retained alongside its
passing rerun. TOPL's final result-summary-only change was separately rerun and
passed; the final198-source manifest and aggregate source scope were rechecked.

## Latest-main rebase and push validation

The user requested rebasing again, resolving conflicts, rerunning checks and
pushing the cleanup to main. The fetched integration target is `8cf4880`.
All newer standalone subsystem composition and the approved VISION correction
are retained. FILES and HACK generated provenance conflicts preserve main's
new declarations/exporter dependencies and update only the extracted adapters'
source hashes. The complete main divergence register is retained; a truncated
conflict-marker edit was detected and replaced from the exact rebased base
before validation. No register history was intentionally retired.

All58 adapter source baselines are byte-identical before and after rebasing.
The recipes now name reachable rebased foundation `c0740be`, and regeneration
updates72 exact dependency/provenance outputs. Main's new DETECT receipt also
binds the original address adapter; its migration verifies the exact reviewed
three-file foundation binding package, not an arbitrary current hash.
The complete source manifest now binds215 inputs, including main's correction
declaration and the targeted interaction guard.

The cleanup relocation audit verifies that the approved correction declaration
is byte-identical to the integration base. The targeted interaction guard now
applies the same single-file exception as main's canonical scope guard and
reports137 unchanged policies plus1 approved correction. The original baseline,
all other policy checks, three frozen files and forbidden-dependency checks
remain intact. Its own source pin is migrated only after reconstructing the
complete script from exactly two declared validation/reporting edits.
The canonical aggregate source check passes558 production imports.

Latest execution outcomes are recorded separately in
`c-runtime-rebase-validation.json`; `c-runtime-validation.json` is the historical
pre-rebase run. The latest source-size comparison still totals5,491 fewer
production-JS bytes,163 additional lines and15 additional files versus8cf4880.
This remains a raw-source measurement, not a bundle-size or speed result.

The expanded latest-main run additionally exercises LIGHT, GETPOS, MONDATA,
MINION, MPLAYER, STEAL, WIZARD, DOKICK, DETECT, BALL, alignment, WIZCMDS,
invocation, ranged gameplay, Quest travel, elemental planes and Astral victory.
Quest-completion's scenario assertion and any other non-passing attempts are
reported explicitly in the latest validation record, rather than treated as
cleanup equivalence. The DOKICK test initially lacked its native replay receipt;
copying the exact existing receipt (with fixture hash verified) made its original
assertions pass. All copied fixtures are independent worktree-owned files.

Quest-completion failure characterization: the default eligibility scenario
exits instead of reaching the asserted input boundary on original C. An exact
untouched8cf4880 archive with an independent CoW original-C cache fails the same
assertion. Both complete57,628,854-byte result files (C and JS) are byte-identical
between main and cleanup, including2,985 frames per result. This is an existing
scenario/acceptance failure, not a passing Quest-completion proof. No expectation,
input, native behavior or production policy was changed to accommodate it.

Final deep-path checks pass: the source-main depth5 starvation recording reaches
2,376 moves with2,752 input boundaries and2,945 exact frames. It produces actual
compressed bones (C5,078 bytes; JS5,032 bytes). All four fresh C/JS bones
producer/consumer combinations compare complete recordings and live normalized
world graphs successfully. Raw pointerful bones-byte identity is not claimed.
The first consumer attempt lacked its local native replay receipt; its exact
independent copy and passing rerun are both recorded. All215 owned inputs and
all59 component adapter/helper inputs stayed stable through their batches.
The final fetch still identifies8cf4880; publication is fast-forward-only.
