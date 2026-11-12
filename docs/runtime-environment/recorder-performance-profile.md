The pure-JavaScript baseline passes all 44 public recorder sessions, including strict counts, screens, RNG, animation cursor triples and persistence telemetry. Replay deadlines were disabled. Seven sessions took more than the frozen harness’s default 45 seconds during profiling; passing recordings is not timeout acceptance.

Measurement: Node24.19.0, V8 CPU sampling every 1ms, unmodified normal scorer/engine/frozen harness, one profile per recorder worker. All744 pre-run inputs remained unchanged and match current main. Total run wall time: 1,311 seconds. Profiles include worker startup and scorer comparison as well as gameplay. Sampling adds overhead; the contest’s Node22 timing is not established.

| Area (self samples) | Share |
| --- | ---: |
| C environment | 64.79% |
| C binding adapters | 11.80% |
| translated game modules | 8.03% |
| V8/native/anonymous | 5.90% |
| garbage collection | 3.89% |
| standalone services | 3.55% |
| Node internals | 1.02% |

| Function (self samples) | Share |
| --- | ---: |
| `js/c-runtime/types.js:16` `record` | 21.32% |
| `js/c-runtime/types.js:6` `canonical` | 12.43% |
| `js/c-runtime/heap.js:46` `malloc` | 6.84% |
| `:0` `(garbage collector)` | 3.89% |
| `js/nethack/bindings/sfbase.js:19` `table` | 1.93% |

The turn loop accounts for64.15% of worker samples, new-game creation10.10%, other replay/startup18.45%, and program construction1.14%. Frozen scoring/comparison itself is small. The frozen affine timing fit is9,644ms +77.22ms/move (R²0.693); it is descriptive across different commands and segment counts, not a direct startup measurement. The segment-aware fit produces a negative segment coefficient, so its coefficients must not be interpreted as causal costs.

First fix: cache immutable declaration-derived type normalization/size information per C environment and stop constructing/catching an exception to discover that a scalar is not a record. Keep strict unknown-record errors, memory bounds checks and growth behavior. `record()` and `canonical()` alone consume33.75% of worker self samples.

Second fix: remove per-character temporary heap allocations for buffered `fgetc`/`fputc`. The allocation call stacks lead chiefly to `stdio.js:131` and`:133`; configuration parsing is the largest game caller. Preserve EOF/error flags, pushback, user buffers, line flushing and unbuffered/slow paths, verified against original C.

Then repeat the profile, recording comparison and commit/push cycle; optimize the next measured bottleneck. Do not edit frozen dependencies or translated game policies. Final time-limit acceptance requires an unprofiled run on the target Node/runtime with the actual deadline.

Detailed sampled functions, callers, phases, per-session timings, source integrity and hashes of44 retained raw worker profiles are in `recorder-performance-baseline.json`. Raw profiles remain in `.cache/sounds-runtime-20261112-r9/.cache/recorder-cpu-profile/profiles/`. Reproduce with `scripts/profile-public-recorder.py` and analyze with `scripts/profile-recorder-cpu.py`.
