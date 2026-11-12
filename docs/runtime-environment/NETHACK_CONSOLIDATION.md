# Consolidated NetHack runtime

The worktree branch `codex/consolidate-nethack-runtime` was rebased onto main `e61e34c`.
All 230 former `js/standalone` files now belong to `js/nethack`. One forwarding
wrapper, `standalone/address-ports.js`, is removed because its implementation was
already `nethack/address-ports.js`. No compatibility directory remains.

`js/nethack` owns game assembly, startup, lifecycle, globals, subsystem integration,
measured ABI declarations and `bindings/`. General C behavior remains in
`js/c-runtime`; translated algorithms remain in `js/ported`. Existing public
function and command names, including standalone-named APIs, remain compatible.

Current imports, build paths and test consumers use the consolidated directory.
The checked recipe changes paths and imports, plus the source-audit routing needed
to retain earlier immutable receipts. It does not change game-policy bodies,
C/compiler inputs, ABI data or frozen harnesses. Original JSON metadata remains
byte-identical even when its file moves.

Run `npm run test:layout`. The check independently reproduces every transition
from the pinned base, verifies unchanged sources and evidence, resolves current
relative imports, initializes the consolidated environment with Wasm denied,
and rejects source changes beyond the relocation.

Older source audits run in a separately labeled read-only prior-layout view under
`.cache/nethack-layout`. The current relocation is verified first. That view is
used for source/evidence checks, never as the implementation under test. Runtime
and integration tests execute the current modules under `js/nethack`. Existing
source-hash assertions retain their expected values and accept a predecessor only
when its exact current path transformation has been independently verified.

The [validation record](nethack-layout-validation.json) distinguishes current
runtime tests from historical source-audit reproduction. It also records the
subset rerun for this layout change. The previous 138-suite migration receipt
remains historical; it is not relabeled as a new complete test run.

No recorder sessions are run by this consolidation.
