# EXPLODE staged integration

Status: all eight configured original functions generated. Isolated memory64
reference-C/JS fixture passes **9,095 comparisons**. Production registration,
actual game link with `explode.o` excluded, public recordings and native macOS
validation have **not** been performed for this TU. Do not mark it promoted.
Prepared `src/explode.c` is byte-identical to pristine upstream.

## Files

- `js/ported/explode.js`: all eight original functions, in original order with
  original parameter names and every block comment. The original column-first
  explosion matrix uses the compiler-checked symbol values 96 through 104.
- `js/ported/explode-runtime.js`: fresh heap views, struct/global/bitfield
  adapters and configured header macros. C long quantities use BigInt;
  int products use `Math.imul`; coord/char writes preserve native widths.
- `nethack-c/wasm/tu-libraries/explode.js`: typed Emscripten import library.
- `nethack-c/wasm/tu-fragments/explode-support.inc`: typed global/bitfield/header
  macro, printf and RNG attribution ABI. It contains no original TU function.
- `scripts/tu-explode-layout.h`: compiler-produced field widths/offsets and
  configured constants; the scatter-chain ABI uses a separate identical type.
- `scripts/tu-explode-probe.c`: controlled dependency fixture; only reference
  mode includes original explode.c. Hybrid mode contains no C TU algorithm.
- `scripts/test-tu-explode.mjs`: explicitly first-pass EmC/JS differential gate.
- `nethack-c/wasm/tu-fragments/explode-metadata.py`: read-only check of exact
  source literal set/capacity, all eight source RNG call sites and both original
  nh_snprintf source line numbers. Run it before builds and source validation.

## Shared integration recipe (owned by migration root)

1. Add registry entry:

   ```json
   {"name":"explode","source":"src/explode.c","javascript":"js/ported/explode.js","library":"nethack-c/wasm/tu-libraries/explode.js","configuredFunctions":true}
   ```

   Production public imports: `explode`, `scatter`, `splatter_burning_oil`,
   `explode_oil`, `adtyp_to_expltype`, `mon_explodes`. Test-only imports:
   `teleport_explode_test_explosionmask`,
   `teleport_explode_test_engulfer_explosion_msg`.

2. Include `tu-fragments/explode-support.inc` from `tu-support.c` and account
   for this fragment and metadata checker in build manifest input hashes.
   No separate object containing original `src/explode.c` may remain linked.

3. Add `explode` probe descriptor with fields `[]` and exports:
   `layout_count`, `layout_name`, `layout_value`, `reset`, `option`, `prop`,
   `cell`, `action`, `trace`, `snapshot`, `pointer`, `stack`.
   Add `explode` to the reference-includes-original-TU list; do not separately
   append original explode.c in reference mode (the fixture includes it).
   Hybrid requires the new library and support, with no other original TU
   sources: the fixture supplies its controlled dependency boundary itself.
   Existing common support may be linked with section GC as for other probes.

4. Add `explode: []` and `explode` to the compiler-layout descriptor handling
   in `write-tu-layouts.mjs`. All new metadata values are ordinary Numbers.
   Runtime validates every scalar width used and the nine explosion symbols.

5. Import `* as explode` and `createExplodeEnvironment` into wasm-runtime.js,
   add `const explodeEnvironments = new WeakMap()` per runtime, and add the
   runtime method from `explode-runtime-method.inc` alongside existing methods.
   Keep the normal binding's stack save/restore wrapper.

6. Run the metadata checker, source/scope checks and differential test, then
   the actual game mixed-link gate. Native defaults should only be enabled
   for this TU after adding its actual native oracle; the current test clearly
   declares EmC first-pass coverage. Preserve failures when comparing native.

## Reproduction of isolated checks

The throwaway build script `.cache/build-explode-isolated.py` builds outputs
only under `.cache/explode-first-pass` using the configured memory64 compiler,
all normal compile-defines, no additional C gameplay TUs, original inclusion
only for reference, and the new support/library only for hybrid.

```sh
python3 .cache/build-explode-isolated.py
TELEPORT_EXPLODE_PROBE_DIR=.cache/explode-first-pass .cache/emsdk/node/24.19.0_64bit/bin/node scripts/test-tu-explode.mjs
python3 -B nethack-c/wasm/tu-fragments/explode-metadata.py
python3 -B .cache/check-p01-source.py explode
.cache/emsdk/node/24.19.0_64bit/bin/node .cache/check-p01-scope.mjs explode
```

All three JS files and the test pass `node --check`; reference/hybrid fixture,
metadata and support compile; the isolated link and 9,095 comparisons pass.
Logs: `.cache/explode-isolated-build.log`, `.cache/explode-isolated-test.log`.

## Verified scope and remaining limits

Comparisons retain complete emitted message/event traces and object/hero/
monster/killer/RNG snapshots. They cover shield selection, all damage-type
mapping cases including invalid diagnostics, both engulfer message families,
visible/invisible animation and glyph coordinates, floor/inventory order,
monster resist/death attribution, role-dependent wand damage, oil dilution and
extinguishing, monster explosion dice, quantity splits, chain motion, fracture/
destruction, collisions, shop billing, fatal naming, engulf/grab/poly and
invulnerability, real heap growth during dependency callbacks, 32-bit noise
multiplication, signed rm.typ to unsigned local uchar conversion (0x7f/0x80/0xff terrain), boundaries and empty lists. Fixture RNG traces normalize only
`__FILE__` directory prefixes to the basename, retaining every line/function/
call/value; the production helper uses the original `explode.c` basename.

Not verified: full real-game dependency behavior, production/public recordings,
native macOS C, recursive explosion callbacks/reentry, the hallucinated name
retry-limit paths, invisible personal-name killer text under recursion,
boulder-restacking with several preexisting objects, all lifesave/bones
interactions, and all permutations of shop/trap/equipment mutation. Fixtures
control existing dependencies and do not prove their independent algorithms.

SOUNDLIBONLY is inactive and the original Soundeffect macro is a configured
no-op; runtime rejects an integrated sound build instead of silently omitting
sound. All other external game dependencies remain the existing C/JS routines.
The literal pool is exactly the 63 unique original C source strings, including
its header filename, requiring 945 UTF-8 bytes including NULs. The JS binding
rejects non-source dynamic strings; formatted names remain C-memory pointers.

A negative control that removes only the unsigned terrain conversion fails the
new `unsigned terrain local` scenario; the corrected translation passes. This
confirms the new case detects the reviewed width defect. Log:
`.cache/explode-uchar-negative.log`.
