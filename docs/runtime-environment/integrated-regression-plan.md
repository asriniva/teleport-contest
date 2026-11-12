# Fixed-assembly integration regression

Status (2026-11-12): **23/23 named jobs passed** on the unchanged `cc8ef80` game implementation. [Pinned results and individual receipts](integrated-core-validation.json) retain both execution manifests. The first run passed12 jobs, then a stale VISION import hash stopped the first plane check before gameplay. A test-only guard correction verifies the exact reviewed import relocation and still rejects every additional policy change. The remaining12 executions passed, including the repeated `main` producer dependency. All production/reference-source, asset and native-reference hashes agree across both runs.

This is bounded integration acceptance; `fullGameAccepted: false` remains. Additional terminal/exit/signal and diagnostic bindings and deferred interactions remain separate work. Natural Quest/item acquisition and an ordinary winning journey are not established by these controlled fixtures. Start future batches only after their implementation and inputs are frozen.

Current follow-up: the terminal/signal/exit and CLI/RNG startup candidate also
passes all23 jobs. [Extended receipts](extended-core-validation.json) retain the
13-job first run, the host snapshot-write ENOSPC interruption, and the11-job
resumption (including repeated MAIN). Its runtime sources are identical across
both runs; only two audit-tool guards changed between them. All44 strict public
recordings also pass on the same combined production code.

From the repository root, using the pinned development Node:

```sh
.cache/emsdk/node/24.19.0_64bit/bin/node scripts/run-standalone-integrated-checks.mjs --list
.cache/emsdk/node/24.19.0_64bit/bin/node scripts/run-standalone-integrated-checks.mjs --preflight
.cache/emsdk/node/24.19.0_64bit/bin/node scripts/run-standalone-integrated-checks.mjs --run
```

The default invocation lists the plan. Execution requires `--run`. `--only id,id` selects jobs and their prerequisites; for example:

```sh
.cache/emsdk/node/24.19.0_64bit/bin/node scripts/run-standalone-integrated-checks.mjs --run --only main,ordinary-commands,stairs
.cache/emsdk/node/24.19.0_64bit/bin/node scripts/run-standalone-integrated-checks.mjs --run --only bones-four-way
```

Do not run another copy or an overlapping test concurrently: several existing tests have fixed cache destinations. The aggregate executes sequentially and archives each completed evidence receipt immediately.

| Jobs | Required positive profile and evidence |
| --- | --- |
| `main` | Actual MAIN startup, first wait, real initial C/JS saves and four fresh save-stream consumers. Produces the saves used below. |
| `ordinary-commands` | Default full cohort: inventory, completed eating occupation, wield, takeoff/wear, drop/pickup, combined save and four resumed consumers. Historical count: 253 comparisons; current assertions remain authoritative. |
| `restored-world`, `stairs` | Eight initial-save live-world cases, then four cross-fed ordinary down/up/down runs. Final real level2/move62 and identity-checked graphs remain required. |
| `positive-quit` | Ordinary D2 travel and genuine positive-score quit, followed by four fresh score-file combinations. |
| `d5-death` | Frozen literal Samurai fixture `.cache/native-deeper-bones-sam3/input.json`: 2,376 moves/2,752 consumed keys and genuine compressed bones. Uses the custom-fixture proof, without post-cleanup heap claims. |
| `bones-four-way` | Explicitly sets **both** `STANDALONE_BONES_PRODUCER` and `STANDALONE_BONES_CONSUMER_OUTPUT`. Uses the preceding fresh producer in this aggregate directory, not the old default cache. The current JS producer was historically 5,027 bytes; actual bytes/hashes are inventoried anew, and four fresh C/JS consumers establish semantics. Binary size is not used to mask differences. |
| `quest-portals`, `quest-leader` | Corrected connected-terminal fixtures, with declared raw stdin and exact consumed input. Deprecated EOF/`term_gone=1` proofs are excluded. Source-created approaches precede real MAIN portal travel/dialogue. |
| `quest-assignment`, `quest-return` | Fresh consumers of the SHA-pinned original-C eligible save `.cache/quest-eligible-bootstrap-save/c-result.json`. The full return profile explicitly enables source-controlled nemesis/relic actions. No native-only producer/discovery run replaces paired acceptance. |
| `invocation` | Source-created ritual items/site, then real MAIN invocation. Existing terminal and ritual assertions stay intact. |
| `water-turns`, `air-turns` | Existing frozen literal recipes, original source level30/Amulet/plane setup, real bubble turns and connected dual input carriers. |
| `water-save`, `air-save` | Fresh source-created-plane saves through actual MAIN; prerequisites for the corresponding four-way consumers. |
| `water-restore`, `air-restore` | Four fresh consumers of the saves generated in this run. Source-defined active bubble extents, inventoried inactive tails and the one approved visibility correction remain explicit. |
| `water-portal`, `air-portal` | Positive original Water→Astral and Air→Fire portal crossings through MAIN, using frozen literal recipes. |
| `astral-zero`, `astral-positive` | Real MAIN offering/ascension after controlled source-created endgame setup. Both the zero-score first-turn fixture and four fresh ordinary-D2-save consumers with native 100-point ranking remain separate proofs. |
| `wizard-victory` | A separate **continuous debug MAIN journey**: unchanged 147 literal keys from new startup to actual winning exit, only legitimate wizard commands and ordinary offering; no policy setup callbacks or game/RNG writes. Four read-only live worlds, complete per-input RNG/TTY/frames/final files, 100 source points and correctly empty wizard ranking. Explicitly not ordinary progression. |

## Frozen inputs and execution guarantees

Preflight requires the sealed complete original-C reference, native D5 producer/consumer fixtures, pinned eligible Quest save, four frozen elemental recipes, and the frozen 147-key wizard fixture/native replay receipt. It checks the original reference shape (140 game TUs, 32 Lua TUs, no observation cuts, translated TUs or synthetic game globals) and existing native fixture receipts.

The runner removes inherited diagnostic/profile environment flags, including native-only, key discovery/generation and case-selection overrides. Each job receives only its explicit positive mode. Existing test source and assertions are unchanged. Individual suites continue to enforce exact inputs, RNG, terminal output, recorder frames, terminal connectivity and their stated world/state comparisons.

At execution start, the runner hashes JS source/data, test/helper source, native support source, required frozen fixtures, reference receipt and assets. It checks the same snapshot after every job. A nonzero child result, incomplete evidence or source/asset drift fails the aggregate. Logs, per-job archived receipts and a live aggregate receipt are written under `.cache/integrated-checks` (override with `--out`). The live receipt marks the running/verifying/passed/failed job.

## Acceptance boundaries

This is an aggregate of bounded proofs, not exhaustive game completion. Ordinary input-driven play and controlled source fixtures are separately labeled. Quest, invocation, elemental and Astral fixtures do not prove natural item acquisition or a natural winning journey. Opaque compiled regex internals, source-uninitialized inactive bubble tails and compressed pointer bytes retain their existing explicit comparison limits; the runner adds no new exclusions. Post-cleanup heap traversal is not inferred from exit/log equality. All policy-public names resolving is connection evidence, not behavior acceptance.
