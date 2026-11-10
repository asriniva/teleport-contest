# VAULT staged integration

Frozen handoff: **25 configured original functions**, pristine/prepared source
identical, **3,584 configured Emscripten-C/JS comparisons pass**. This number
counts fixture setup/state/trace comparisons, not complete branch coverage.
No shared registry/build/layout/runtime file or production artifact was edited.
Actual mixed-game link, public recordings and native macOS remain pending.

## Exact staged inputs

- `js/ported/vault.js`: all25 original function boundaries/order/names/parameters
  and every original block comment. All original guard, corridor, geometry,
  movement, ownership, dialogue, gold and cleanup algorithms remain here.
- `js/ported/vault-runtime.js`: compiler-described live typed views and header
  macros, pointer/scalar output aliases, module-local environment construction.
- `nethack-c/wasm/tu-libraries/vault.js`: actual memory64 ABI, perModule guarded
  source literal storage, typed fixed printf/dependency calls, original RNG
  caller/line attribution and entry stack save/finally restoration.
- `nethack-c/wasm/tu-fragments/vault-support.inc`: typed globals/fields/header
  macros, RNG/printf/debug/free ABI and zero-only source-literal buffer. It
  contains no original VAULT algorithm or function fallback.
- `scripts/tu-vault-layout.h`: compiler-derived offsets/widths/dimensions/constants.
- `scripts/tu-vault-probe.c` and `scripts/test-tu-vault.mjs`: controlled external
  dependency fixture and explicitly labelled configured EmC differential gate.
- `vault-metadata.py`: read-only source guard verifies 25function/12private
  inventory, exact80-source-string corpus/1934NUL-terminated UTF8 bytes, six
  original RNG line/function sites, debug default and disabled SetVoice profile.
  Original vault.c owns no static/file-scope initializer arrays in this profile;
  a newly added source-owned static array fails the guard for explicit review.
- `vault-runtime-method.inc`: exact dispatcher method for the central runtime.

Hash core/runtime/library/support/layout/metadata as build inputs along with
normal common-runtime/registry/compiler inputs. Fixture/test hashes belong in
probe provenance. There is no source-owned public data needing startup; all
level, room, monster, object and EGD storage is actual mutable native state.

## Registry and runtime

Add this registry entry only when promoting to the next mixed-link gate:

```json
{"name":"vault","source":"src/vault.c","javascript":"js/ported/vault.js","library":"nethack-c/wasm/tu-libraries/vault.js","configuredFunctions":true}
```

Include `tu-fragments/vault-support.inc` from shared `tu-support.c`; exclude
original `vault.o` from the actual mixed game. No startup entry or public data
initializer is required. Do not add an original-C algorithm fallback.

Import `* as vault` from `./vault.js` and `createVaultEnvironment` from
`./vault-runtime.js` into `wasm-runtime.js`. Create
`const vaultEnvironments = new WeakMap()` inside `createPortedRuntime`; add the
method from `vault-runtime-method.inc` to its API. The binding invokes exactly
`Module.nethackPorted.vault(services,name,...args)`. Its spelling must agree with
central static dispatch validation. Each Module uses its own environment and
literal pool. Typed field reads reacquire current heap views after callbacks.

Public original imports (13): `newegd`, `free_egd`, `grddead`, `findgd`,
`vault_summon_gd`, `vault_occupied`, `uleftvault`, `invault`, `gd_move`, `paygd`,
`hidden_gold`, `gd_sound`, `vault_gd_watching`.

Private test aliases (12, excluded from production):
`teleport_vault_test_clear_fcorr`, `teleport_vault_test_blackout`,
`teleport_vault_test_restfakecorr`, `teleport_vault_test_parkguard`,
`teleport_vault_test_in_fcorridor`, `teleport_vault_test_find_guard_dest`,
`teleport_vault_test_move_gold`, `teleport_vault_test_wallify_vault`,
`teleport_vault_test_gd_mv_monaway`, `teleport_vault_test_gd_pick_corridor_gold`,
`teleport_vault_test_gd_move_cleanup`, `teleport_vault_test_gd_letknow`.

## Probe and layout registration

Add descriptor `vault`, fields `[]`, exports:
`reset`, `option`, `set_monster`, `egd`, `corridor`, `cell`, `object`, `trap`,
`prop`, `rng_pointer`, `rng_length`, `answer`, `action`, `trace`, `snapshot`,
`stack`, `layout_count`, `layout_name`, `layout_value`.

Reference mode defines `TELEPORT_REFERENCE_TU`: the fixture includes original
vault.c itself; do not append the original source a second time. Hybrid links
the fixture, typed support and JS library only. It must not link vault.c.
Add `vault: []` to layout writer and its compiler-descriptor list. All metadata
values fit Number in this profile; actual long arithmetic/pointers use BigInt.

**Controlled-fixture-only allocation instrumentation:** compile the reference
fixture and hybrid support with `-Dfree=teleport_probe_free`. The fixture defines
the tracker and calls real libc free, recording actual frees in both modes. Its
own reset uses the same tracker with counters reset afterward. Reference original
free_egd calls the tracker; hybrid `teleport_vault_free` calls that same tracker.
The production support is compiled normally, without this define, so its typed
wrapper calls actual free. Applying the define only to reference or only to the
fixture would make allocation traces incomplete. No allocator algorithm changes.

Run `vault-metadata.py` before source validation/build. It reads files only.
The staged script **throws when TELEPORT_NATIVE_TESTS=1**. Native integration
must supply the actual native oracle for these same fixture cases before that
restriction can be removed. Keep native differences visible, with no passing
waivers or host-specific JS expected outputs.

## Isolated evidence already obtained

The throwaway builder `.cache/build-vault-isolated.py` writes only
`.cache/vault-first-pass/vault-{reference,hybrid}.{mjs,wasm}`. Both actual memory64
modules compile and link under configured -O2 with growing memory. Reference
alone includes original vault.c; hybrid has no original game TU implementation.

```sh
python3 .cache/build-vault-isolated.py
TELEPORT_VAULT_PROBE_DIR=.cache/vault-first-pass .cache/emsdk/node/24.19.0_64bit/bin/node scripts/test-tu-vault.mjs
python3 -B nethack-c/wasm/tu-fragments/vault-metadata.py
python3 -B .cache/check-vault-source.py vault
.cache/emsdk/node/24.19.0_64bit/bin/node .cache/check-vault-scope.mjs vault
```

Latest result:3,584 comparisons PASS. Logs `.cache/vault-isolated-build.log`,
`.cache/vault-isolated-test.log`. Source/order/parameter/all-block-comment guard,
lexical scope (11tooling fixtures), metadata guard and all three JS syntax checks
pass. Header/support/fixture compile and actual reference/hybrid link succeed.

Every25 original entrypoint is called. Full snapshots retain all4fixture monsters,
all EGD/fakecorr records,24objects, full80x21terrain/flags/visibility/occupancy grid,
traps, allocation/free counts, RNG state, destination outputs and ordered messages/
dependency calls. Cases cover ownership/retained mextra, visibility refusal/force,
restoration/blackout/wall repair, blocker relocation, live list migration,
occupancy/summon cadence/death counts, names/deception/deaf/mimic/engulf states,
hidden/visible gold, moving/carving/warnings/witnesses, cleanup/payment, quantities
above2^53 and signed64 maximum, unsigned m_id->parentmid, signed16 destination
narrowing, signed terrain->uchar conversion and fullbyte corridor flags. Defined
forward-proceed, destination-retry and radius-abandon jumps have explicit cases.
Actual callback heap growth, nested C->JS newegd/gd_sound, two Modules sharing one
runtime and thrown-dependency scope restoration are included.

Negative control `.cache/vault-negative-loader.mjs` removes only the first
`C.uchar(crm.typ)` via a read-only module-load transformation, leaving C and
expected results unchanged. `.cache/vault-uchar-negative.log` fails the signed
terrain regression: broken JS returns1, original C returns-2. Frozen core remains
fixed. No test expectation was amended to accept this mismatch.

## Source adaptations and explicit limits

Original `find_guard_dest` goto incr_radius becomes a label on its radius loop
and continue to that same next-radius point. `gd_move` forward newpos/proceed and
backward nextpos jumps use labelled blocks/loop; one skip_search flag preserves
exactly which original lookaround code is bypassed after the retry label. `paygd`
forward remove_guard goto becomes a labelled block with one shared mongone tail.
No original function is merged/split/replaced by a helper algorithm. Local coord
struct assignment copies both fields instead of aliasing one JS object. Native
stack backing preserves automatic buffer/output parameter addresses. hidden_gold
uses signed64 BigInt narrowing at its original C long assignments; poisoned uchar
terrain conversion is explicit, and live fakecorr aliases preserve signed/unsigned
widths. No native equivalence or portable signed-overflow claim is made.

Dependencies controlling actual world/combat, player input/messages, naming,
movement/relocation, inventory, timers and graves are controlled fixture behavior.
They are real typed production calls in the binding but their independent game
algorithms are not proven by this fixture. Actual source exclusion/import closure,
full-game interactions, public recordings and native macOS are pending. Not all
walls/rooms/traps/monsters/containers, every corridor/gold/visibility/death branch,
all callback mutations, malformed/out-of-range state or FCSIZ overflow panic are
exhaustively exercised. The tests prove observed cases, not complete equivalence.

A JS dependency throw restores the JS C-environment scope and binding-entry Wasm
stack in finally. It bypasses the outer C fixture's normal return, so that C
caller's own stack frame remains. The synthetic throw test verifies the binding
entry pointer, then explicitly restores its test-owned outer frame. It does not
claim general foreign-C exception unwinding or recover a game from such a throw.
Runtime rejects changed memory64/long/coord/char/SOUND assumptions; other compiler
profiles and a non-disabled SetVoice backend require fresh validation.
