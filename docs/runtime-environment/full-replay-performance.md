# Full replay performance

These measurements bind commit `29ab502` before integration with newer main.
The combined runtime passes44/44 strictly in617.308s with747 unchanged inputs;
see `full-replay-merge-validation.json`. This absolute validation run is not a
paired performance comparison. The 6.52% result
is not a new measurement against main `3b6db96`.

The final transport change reduces paired replay time across all 44 public
sessions from **670.166 to 626.475 seconds (6.52%)**. Both versions pass every
strict output check; **42 of 44 sessions are faster**. An independent ordinary
44-session batch completes in **529.182 seconds**, also 44/44 strict, with all
747 scoring inputs unchanged. That separate batch is an absolute validation run,
not a causal comparison against the earlier sampled baseline.

Work is on `perf/full-replay-verified`, based on main `25ce012`, pulled on
November 12, 2026. Timing uses Node 22.23.5 on the same Mac. Game tests and builds
are excluded from timed runs. The runtime changes are confined to three files;
the other 744 scoring inputs match main.

## Complete-corpus comparison

Every complete session runs through the unchanged frozen scorer on both source
snapshots. The first version alternates between sessions, pairing identical work
close in time to reduce order and host-load effects. CPU sampling is disabled.
Strict output and telemetry checks run after every session/version. Source
fingerprints remain identical within each version across all 88 invocations.

| Complete-corpus measure | Baseline | Final | Reduction |
| --- | ---: | ---: | ---: |
| Reported replay seconds, all 44 sessions | 670.166 | 626.475 | 6.52% |
| Summed scorer wall seconds, all 44 sessions | 678.558 | 634.792 | 6.45% |
| Child process CPU seconds | 951.954 | 902.334 | 5.21% |

These are sums of independent complete-session scorer invocations, including
repeated parent startup; they are not one continuous batch's wall time. The
independent normal full-batch run above verifies the ordinary scoring path.
A single pair per session reduces but does not eliminate host timing variation.

The four sessions that have failed recent CI deadlines all improve:

| Session | Baseline replay seconds | Final replay seconds | Reduction |
| --- | ---: | ---: | ---: |
| Fountain exploration | 59.67 | 53.30 | 10.67% |
| Ten diverse deaths | 80.06 | 73.66 | 8.00% |
| Wizard world tour | 81.82 | 76.38 | 6.65% |
| Knight coverage | 52.27 | 49.42 | 5.46% |

The two regressions are retained: healer-newmoon (`seed0016`) rises 0.59%
(32.88 ms), and valk-lamp-ration (`seed0105`) rises 2.81% (125.56 ms).
The complete per-session table is in the evidence JSON, including these results.

## Measured costs and implementation

The unchanged-source CPU baseline profiles every public worker at 1 ms intervals.
Nearest-translated-routine attribution assigns each sample once, including that
routine's transport helpers but excluding other translated callees. GC has no
caller and remains separate. The baseline samples terminal capture at 58.38s
(7.86% of worker samples), the largest individual routine; GC is 63.57s (8.56%).
Display `show_glyph` and `reset_glyphmap` account for another 4.56% and 4.03%.

An additional baseline fountain allocation trace matches its recording and all
source hashes. It samples approximately 25.14 GB of cumulative allocation churn,
including subsequently collected objects; this is not peak RAM. Record proxy
reads account for 1.219 GB, including 0.937 GB below capture. Capture's array
lookup and cell getters account for another 0.398 and 0.408 GB.

The final change targets that complete transport path:

- `js/c-runtime/adapter-factories.js`: known HACK/TERMCAP fields use ordinary
  prototype accessors. A fallback proxy retains numeric pointer indexing and
  strict unknown-field errors. Explicit fixed arrays can retain inline aggregate
  address projections; scalar and pointer values remain fresh loads.
- `js/c-runtime/records.js`: optional non-enumerable indexed accessors bypass
  numeric-index proxy dispatch for fixed inline storage. Unusual indices and
  checked bounds retain their previous behavior.
- `js/nethack/bindings/termcap.js`: only the fixed NOMUX screen grid opts in.
  Scalar read/write methods are selected once per cell record type. Every access
  still refreshes the current memory view, so characters, colors and attributes
  remain live after heap replacement.

Fixed indices become own non-enumerable properties on private transport objects;
reflected-property equivalence is not claimed. No translated policy, C source,
asset, compiler option, frozen dependency, scoring rule or deadline is changed.

The final four-session CPU run passes all four strictly, with 13 segments, 1,084
animation cursor triples and all 747 inputs unchanged. Capture transport samples
across those sessions fall from **29.887 to 19.927 seconds (33.3%)**. This is
sampled attribution under varying host conditions; the unprofiled paired corpus
establishes the reported overall gain.

## Verification and limits

The final ordinary full batch matches 792,838 RNG calls, 11,405 screens and cursor
triples, 1,483 animation frames and cursor triples, and 56 game segments. Storage
traffic, exact per-step counts, zero pending animations and zero forbidden
capability attempts are checked. All 747 input hashes match after the run.

Original-C component comparisons pass 426 HACK cases / 4,338 checks across 95
routines and 223 TERMCAP cases / 2,472 checks across 56 routines. These use
isolated configured Emscripten memory64 C routine fixtures with controlled test
worlds and Wasm-denied JavaScript implementations. They are not native-host or
exhaustive full-game equivalence claims. All 229 reference fixture inputs are
hash-verified.

Focused contracts cover all 1,920 cells, aggregate copying, unusual indices,
checked bounds, fresh scalar loads, aliases, heap growth, module/frame isolation,
dynamic service replacement and exceptions. The current runtime dependency graph
passes its 33-file host/game/Wasm boundary check; the predecessor layout audit
passes 593 transitions. Eleven controls test the exact three-file historical
source projection and reject unrelated source/patch edits. That development
projection preserves old audit receipts and is not current-game acceptance.

These local validation runs disable worker deadlines. They do not certify the
45-second CI gate, held-out sessions, or the hosted judge's 900-second budget.

## Reproduction and evidence

```sh
# Profile the normal complete public batch.
python3 scripts/profile-public-recorder.py REPOSITORY --node NODE22 --output RUN
ln -s REPOSITORY RUN/score-repo
NODE22 scripts/score-standalone.mjs --summarize RUN
python3 scripts/profile-recorder-cpu.py RUN
python3 scripts/analyze-replay-hotpaths.py RUN --output RUN/hotpaths.json

# Pair the entire public corpus without sampling.
python3 scripts/compare-paired-replay-corpus.py BASELINE FINAL --node NODE22 --output PAIR

# Independently time the ordinary complete scorer.
python3 scripts/time-public-recorder.py FINAL --node NODE22 --output NORMAL
ln -s FINAL NORMAL/score-repo
NODE22 scripts/score-standalone.mjs --summarize NORMAL
```

`time-public-recorder.py --cpu-profile --session NAME` profiles selected complete
sessions through the frozen runner, checking the canonical infrastructure bytes
and the actual completed target set. `verify-selected-replay.mjs` checks strict
recording telemetry for each selected run.

The source hashes, complete timings and evidence hashes are in
`full-replay-performance-validation.json` and `full-replay-performance-evidence/`.
Raw CPU/allocation traces and each authoritative per-session scorer bundle remain
under `.cache/`, with exact baseline/final source snapshots in
`.cache/source-baseline/` and `.cache/source-final/`.

## Rejected and invalid diagnostics

The earlier cross-call HACK retention experiment passed 44/44 strict but took
907.280s versus 750.064s for the sampled baseline; this did not establish useful
whole-run improvement. It was removed. `bindings/hack.js` matches main. The
known-field accessor part is evaluated only as part of the final transport path,
with no independent speed claim. Preserve `.cache/full-run-candidate/` and
`.cache/first-variant-comparison.json`.

The first attempt was invalidated by concurrent changes to four unrelated runtime
sources, causing 19 module-load failures after 25 passes. Its 413s elapsed time
is not performance evidence. Only owned changes were transferred to a new
worktree; the unrelated edits remain in the original. Preserve
`.cache/invalidated-concurrent-run/`.

An early selected-session wrapper forwarded only its first target. That attempt
is preserved in `.cache/final-slow-cpu-first-target-only/` and is not the accepted
four-session result. The corrected driver checks the exact completed target set.
