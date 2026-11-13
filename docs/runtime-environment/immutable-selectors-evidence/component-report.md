# Per-selector owned bucket state

This supersedes the last-selector experiments, which are discarded after measured DISPLAY/INVENT repeat rates of3.447%/.620%. All files remain cache-only, pinned to d9c2321. Production, binding modules and Git index were not edited.

Candidate: `selector-state-factories.js`; review diff: `selector-state-immutable-fields.patch`. It uses the same get-only immutable snapshot helper and private WeakMap ownership registry documented in REPORT.md. For each owned snapshot, adapter construction clones its private Maps into name→field→{metadata,bucket:null}. It does not reread schema or field getters. Each final selector has distinct frozen metadata, so this preserves the original bucket ownership without a metadata→bucket Map. Generic mutable Map/custom/proxy callers retain the original branch verbatim.

Owned field access performs two selector Map lookups, reports missing fields before ptr, invokes ptr(at), then reads selector.bucket. A pointer coercion which reenters and creates or changes the same bucket is therefore observed. Bucket creation, accessor prototypes/identity, zero-address behavior,128-entry eviction and live provider reads/writes are unchanged. There are no last-name checks, negative caches, code generation or game names.

The added setup cost is one state object and selector Map entry per final field plus one row Map per record. Actual pinned schemas contain DISPLAY51 rows/175 fields and INVENT52 rows/212 fields. Each adapter owns its states; metadata returned through readonly facades never exposes or acquires mutable bucket properties.

## Behavior evidence

`selector-state-test.mjs` passes19 deep comparisons/assertions with code generation from strings disabled. In addition to the prior construction-order, readonly, mutable-Map, pointer-reentry, eviction, accessor identity and live-provider checks, it verifies no schema reread during adapter initialization, independent buckets across adapters, proxy-facade fallback, and all387 actual DISPLAY/INVENT fields at three addresses (1161 field/address/value comparisons). Pinned schema fixtures are in schema-display.json/schema-invent.json. No native-C or recorder validation was run for this diagnostic.

## Component performance

`benchmark.json` records fresh-process Node22.23.5 ABBA then BAAB runs of actual env.field(...).value through the scalar adapter. Identical call sites use precreated selector strings, three records/twelve int fields and a64-address working set. Each case has500000 calls per sample, warmup and three repetitions. Setup cost is excluded. Services return numeric values; this does not reproduce actual bridge/memory-read costs. Parent jobs were active, so no whole-game timing claim is justified.

Candidate/baseline CPU ratios (per-round ratios):

| Workload | Ratio |
| --- | ---: |
| Same selector/address | .799 (.813/.785) |
| Same selector/64 addresses | .818 (.850/.786) |
| Alternating selectors | .889 (.892/.885) |
| Uniform12 selectors | .905 (.895/.915) |
| 80%-favored selector | .852 (.890/.813) |

The readonly-facade-only control ranged1.003–1.137 in the same experiment; the slowest cases showed substantial host drift. Unlike the discarded last-selector cache, the state strategy improves both alternating and uniform mixtures in both rounds. These results support a separate actual-game experiment, not production adoption by themselves.

Current benchmark.json is the selector-state run; earlier variant raw artifacts are retained with .reference/.post-pointer/.allocated-names suffixes. Its top-level scope prose was corrected from copied reader-experiment text after the run; unchanged timings, checksums and source hashes are preserved, and the uncorrected JSON is retained. Raw worker rows already describe the actual field/value workload accurately.

## Next action

Parent review and an isolated bridge integration should preserve the helper's smaller-than-Map API assumptions and owned-only optimization. Then run native/44-session behavior gates and paired game performance checks, including setup/allocation effects. The measured3.157% field self-share bounds the opportunity; the component reduction is not a promised total-game improvement.
