# Common-runtime cleanup

Isolated worktree: `/Users/arj/Desktop/nethack_comp/c-runtime-cleanup`.
Branch: `cleanup/c-runtime-rect`. Original baseline: `df33dd4`.
Rebased onto `origin/main` at `059e17579a72ec6325e7b4d7e7fd7eead577d79b`.
The first slice was committed as `7640708`; this document covers its continuation.
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
moved out of `ported` to `nethack/runtime.js` with a compatibility re-export.
The game algorithm files, original C, compiler flags, terminal capabilities,
input/output transport, shadow recorder, snapshot serialization and frozen
contest files are unchanged. No missing dependency is replaced with a stub.

Compatibility files in `standalone` are intentional forwarding entries. They
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
provider as well as its old compatibility path; its declarations did not change.
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
cap, with no comparison mismatch reported; it remains incomplete. A level-
persistence test stopped on an existing source pin for level-persistence.js,
which this cleanup does not modify. The broad run was stopped at user request
before rebasing, including its active child; it is not an aggregate acceptance.
Historical bounded/failed logs remain under `.cache/c-runtime-cleanup/`.
Full pure-JS game recording and mixed-backend retirement are outside this
refactor's acceptance; it changes architecture without claiming new gameplay.

The original aggregate scope check already fails at baseline on an absolute
`runtime-environment/js/standalone/stdio.js` hash (expected `65866af8`, observed
`051933cd`). Its unchanged HEAD copy reproduces the failure before production
closure traversal. This cleanup does not refresh or suppress that pin. The new
boundary check inspects the generic runtime independently; it does not relabel
the original aggregate scope failure as a pass.
