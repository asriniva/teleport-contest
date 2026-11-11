# Common-runtime cleanup

Isolated worktree: `/Users/arj/Desktop/nethack_comp/c-runtime-cleanup`.
Branch: `cleanup/c-runtime-rect`. Baseline: `df33dd4`.
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

Final results are recorded alongside this document once the component runs finish.
The runtime's boundary/relocation/contract tests, original-C RECT comparisons,
13-module address transport, native libc and scanner/stdio checks are required.
Full pure-JS game recording and mixed-backend retirement are outside this
refactor's acceptance; it changes architecture without claiming new gameplay.

The original aggregate scope check already fails at baseline on an absolute
`runtime-environment/js/standalone/stdio.js` hash (expected `65866af8`, observed
`051933cd`). Its unchanged HEAD copy reproduces the failure before production
closure traversal. This cleanup does not refresh or suppress that pin. The new
boundary check inspects the generic runtime independently; it does not relabel
the original aggregate scope failure as a pass.
