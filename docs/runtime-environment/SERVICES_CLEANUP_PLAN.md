# Runtime, bindings and dependency separation

Worktree: `/Users/arj/Desktop/nethack_comp/services-cleanup`.
Branch: `cleanup/services-layout`; starting main: e9207d8.

The user explicitly expanded the task to finish the remaining infrastructure
inside `ported/*-runtime.js`, beyond relocating misleading file names.

- Inventory and consolidate stack scopes, scalar conversions and type/environment setup.
- Share descriptor/record construction and global binding factories, keeping distinct transport profiles explicit.
- Centralize NetHack header aliases and preserve property/union semantics.
- Move 59 services to c-runtime, lua, libraries, platform, or nethack.
- Move 128 translation adapters to nethack/bindings; shared C/R/T context to c-runtime and mixed bridge to backends/emscripten.
- Update all live imports, generation/build inventories and source provenance; preserve historical receipts and algorithm bodies.
- Run mechanical/source-boundary audits, focused contracts, all affected component comparisons and original-C game/recording/persistence checks.
- Commit a clean isolated result; do not stop after an intermediate extraction or rename.

Implementation complete:189 file moves and969 AST occurrences across122
bindings. Generic machinery and NetHack declarations have separate owners;
all144 source-shaped policies retain their original bytes after import-literal
normalization. The original source-selection and frozen-input guards remain in
force. All19 source/header guards and672 infrastructure contracts pass.

Final execution covers every moved binding, all dependency checks, source-main
startup/save/restore, ordinary death, depth5 bones and four fresh bones consumers.
Results and retained baseline failures are recorded in
`services-cleanup-validation.json`. No public-score or performance acceptance is
inferred from source cleanup.

Completed:127/128 binding suites (retained baseline LIGHT failure), all41
dependency checks,47-case pager, source main/save/restore/death and four-way
bones. Default Quest eligibility retains its byte-identical baseline failure.
The final whitespace normalization preserves all520 production AST hashes.
