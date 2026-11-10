# GETPOS staged integration

Frozen private handoff: **22 configured original functions**, pristine/prepared
getpos.c bytes identical, **9,241 configured Emscripten-C/JS comparisons PASS**.
This is a setup/state/trace comparison count, not branch coverage. No shared
registry/build/layout/runtime file or production artifact was edited. Actual
mixed-game import/exclusion, full integration, public recordings and native
macOS are pending. The configured reference inherits the existing deterministic
qsort substitution described below; it is not pristine native libc evidence.

## Exact owned inputs

- `js/ported/getpos.js`: all22 original functions, boundaries/order/names/params
  and original block comments. All targeting/filtering/sorting comparator,
  help/menu/cursor/input/formatting decisions remain in these functions.
  Original TU macros IS_UNEXPLORED_LOC/GLOC_SAME_AREA stay inline JS arrows.
- `js/ported/getpos-runtime.js`: fresh typed fields/native buffers/output aliases,
  original header macro access and perModule private callback/enum state.
- `nethack-c/wasm/tu-libraries/getpos.js`: actual memory64 ABI, typed printf shapes,
  source-only literal interning and entry stack/finally restoration.
- `tu-fragments/getpos-support.inc`: typed globals/header/field/indirect calls,
  varargs ABI and zero-only storage for original static30/16byte buffers plus
  source-literal pool. No original GETPOS algorithm or function fallback.
- `scripts/tu-getpos-layout.h`: compiler offsets/sizes/constants.
- `scripts/tu-getpos-probe.c`, `scripts/test-tu-getpos.mjs`: controlled dependency
  fixture, original-C versus imported-JS differential cases.
- `tu-fragments/getpos-probe-dependencies.c`: probe-only actual prepared HACKLIB
  dependency include with unrelated symbol renames; never include in production.
- `tu-fragments/getpos-metadata.py`: read-only source data/CPP/sort provenance guard.
- `tu-fragments/getpos-runtime-method.inc`: exact central dispatcher method.
- `tu-fragments/getpos-hashes.json`: SHA256 owned inputs and actual source/header/
  dependency profile. Add adapters/data checker to normal build provenance too.

Seven readonly source tables remain JS authoritative in their original scopes:
gloc_descr6x4, gloc_filtertxt3, fastmovemode2, dirnames4x2,
pick_chars_def4pairs, mMoOdDxX_def12 and view_filters3. Guard preserves exact
strings/constants/row order;108source strings occupy2272NUL-terminated UTF8 bytes.
Only this source corpus may be interned; dynamically generated names/printf
results stay actual pointers. There are no original GETPOS RNG sites.

No public source-owned data is read by another TU before a GETPOS call, so no
startup hook is required. Private retained hilite/valid raw callback tokens and
HiliteNormalMap/GoodposSymbol/Background states initialize from JS source data in
one environment per Module. Static buffers are zero-only native storage with
original lifetimes and alias identity. They are not automatic stack buffers.

## Registry and runtime

At shared promotion add exactly:

```json
{"name":"getpos","source":"src/getpos.c","javascript":"js/ported/getpos.js","library":"nethack-c/wasm/tu-libraries/getpos.js","configuredFunctions":true}
```

Include `tu-fragments/getpos-support.inc` from shared `tu-support.c`; exclude
original getpos.o. Import `* as getpos` and `createGetposEnvironment` into central
`wasm-runtime.js`. Add `const getposEnvironments = new WeakMap()` inside
createPortedRuntime; add the method from getpos-runtime-method.inc to its API.
The library calls exactly `Module.nethackPorted.getpos(services,name,...args)`;
central static binding validation must agree. No startup method/default import.

Public original imports (8): `getpos_sethilite`, `mapxy_valid`,
`gather_locs_interesting`, `dxdy_to_dist_descr`, `coord_desc`, `auto_describe`,
`getpos_menu`, `getpos`.

**Two production C->JS callback imports** remain active despite original static
linkage: `teleport_getpos_cmp_coord_distu` and
`teleport_getpos_gloc_filter_floodfill_matcharea`. Typed support passes these
stable actual Wasm callback adapters to actual qsort and set_selection_floodfillchk.
Their bodies dispatch to the same original JS functions. Do not mark these two
as test-only imports or replace either algorithm in C. Caller-supplied retained
valid/hilite tokens are kept raw perModule and invoked by typed native helpers.

Private test aliases (12, absent from production):
`teleport_getpos_test_getpos_toggle_hilite_state`,
`teleport_getpos_test_getpos_getvalids_selection`,
`teleport_getpos_test_getpos_help_keyxhelp`, `teleport_getpos_test_getpos_help`,
`teleport_getpos_test_gloc_filter_classify_glyph`,
`teleport_getpos_test_gloc_filter_floodfill`,
`teleport_getpos_test_gloc_filter_init`, `teleport_getpos_test_gloc_filter_done`,
`teleport_getpos_test_known_vibrating_square_at`,
`teleport_getpos_test_gather_locs`, `teleport_getpos_test_truncate_to_map`,
`teleport_getpos_test_getpos_refresh`.

## Exact controlled probe recipe

Add descriptor getpos, fields `[]`, exports:
`private_state`, `cmap`, `reset`, `option`, `cell`, `input`, `queue`, `goal`,
`action`, `trace`, `result`, `snapshot`, `stack`, `layout_count`, `layout_name`,
`layout_value`. Add `getpos: []` and getpos compiler-descriptor handling to layout
writer. All metadata values fit Number in this profile. Actual function pointer
and raw pointer ABI use BigInt; private callback tokens never become Numbers.

Define TELEPORT_REFERENCE_TU only on reference: fixture includes original
getpos.c itself, so do not append it again. Hybrid links fixture, library and
typed support, excluding original getpos.c. Both modes additionally compile
actual pristine `src/glyphs.c` (only required glyph_to_cmap dependency survives)
and getpos-probe-dependencies.c, which includes actual prepared hacklib.c.
The wrapper renames only eos/visctrl/strsubst/nh_snprintf to unused names because
fixture supplies controlled traced versions. Actual sgn and the two inherited
sort functions remain compiled original dependencies, not JS substitutes.

Probe-only flags: `-Dfree=teleport_probe_free` on fixture, support and HACKLIB
wrapper, plus `-Wl,--wrap=nh_deterministic_qsort`. The fixture tracker calls real
libc free, records symmetric actual frees, and resets counts after its setup.
The qsort wrapper logs count/size and every actual comparator argument/result
while calling __real_nh_deterministic_qsort. Both modes use the same actual
sort dependency and comparator trace. **Production uses neither test flag**;
teleport_getpos_free then calls actual libc free. Production retains the existing
configured header's qsort substitution exactly as before this port.

The dependency wrapper include path is relative to the repository-owned fragment
and resolves `.cache/wasm64-build/tree/src/hacklib.c`. A snapshot build relocating
fragments away from its own prepared tree should generate an equivalent wrapper
with an absolute include to that build's actual prepared source; keep all four
renames and hash the included dependency/header bytes. Do not copy sort logic
into GETPOS production support or silently switch to another sort implementation.

Read-only guard verifies actual compiler preprocessing resolves multiline
Snprintf to getpos_help:280 and getpos_menu:705; starts279/704 are not effective
__LINE__ origins. Typed native nh_snprintf retains those exact names/lines.

## Actual provenance and tests

Pristine/prepared getpos.c bytes agree. The configured prepared hack.h already
maps qsort to nh_deterministic_qsort; prepared hacklib.c contains the inherited
stable equal-key index wrapper calling libc qsort internally. This is an
existing accepted contest/platform adaptation, not introduced here. The isolated
reference uses those actual prepared headers and sort dependency. Native macOS
with pristine native libc qsort for these same cases is still pending; do not
infer it from configured EmC comparisons or turn differences into expected passes.

Isolated throwaway builder writes only `.cache/getpos-first-pass/` actual memory64
reference/hybrid modules. Latest commands already run:

```sh
python3 .cache/build-getpos-isolated.py
TELEPORT_GETPOS_PROBE_DIR=.cache/getpos-first-pass .cache/emsdk/node/24.19.0_64bit/bin/node scripts/test-tu-getpos.mjs
python3 -B nethack-c/wasm/tu-fragments/getpos-metadata.py
python3 -B .cache/check-getpos-source.py getpos
.cache/emsdk/node/24.19.0_64bit/bin/node .cache/check-getpos-scope.mjs getpos
```

Result9,241 comparisons PASS; logs `.cache/getpos-isolated-build.log` and
`.cache/getpos-isolated-test.log`. Source/order/parameter/every-block-comment,
lexical scope (11tooling fixtures), data/CPP guards, all three JS syntax checks,
actual support/layout/probe compile/link and diff whitespace checks pass.

All22 entrypoints run. Checks retain exact fullterrain/remembered/shown glyphs,
visibility/area-selection map, live flags/cursor/hero directions, sorted coord
arrays, private highlight enum/callback-install states, allocation/free counts,
static return-buffer content, input/queue state and complete ordered message/menu/
selection/comparator traces. Cases cover callbacks/highlight cycling, help goal
identity and terrain modes, all gloc classes/filter modes, actual glyph conversion,
area/doorway/flood classification, genuine vibrating square, nearest sorting/ties,
clamped signed16/schar movement, distances/coordinate modes, menus/choices,
walk/rush/skip commands, all cursor cycling and cancellation modes, queued/repeat/
mouse inputs,1,658menu iterations,2,000unknown input iterations, retained static
buffer alias, default-null goal help, heap growth during text/output callbacks,
C->JS reentry, Module isolation and thrown dependency cleanup.

Read-only negative loader `.cache/getpos-negative-loader.mjs` removes **only menu
per-iteration stack restoration**. `.cache/getpos-automatic-negative.log` rejects
the large-menu case with Wasm memory-out-of-bounds; unchanged C remains the oracle.
The fixed core and expected outputs are not modified for that negative run.
The staged test throws explicitly when TELEPORT_NATIVE_TESTS=1, preventing its
EmC observations from being counted as native evidence.

## Lifetime/control adaptations and limits

Three scopes reproduce native automatic storage lifetime: external imported
entry bindings save/restore Wasm stack; internal calls to original functions
owning native automatic buffers use typed callLocal save/finally restoration;
menu/input iterations restore their automatic local block storage in finally.
Original bodies and algorithms remain intact. Outparam cells, coord** arrays,
menu_item** and actual anything/command struct copies retain full native backing;
output storage allocated by the caller survives helper returns. The original
static30byte dxdy buffer and16byte screen_fmt stay outside these stack scopes.

Original getpos_help goto into pick instructions becomes a skip_non_mons flag
which bypasses exactly those early nonmonster sections and still executes the
shared target tail. getpos do_rushrun uses a flag preserving short-circuit call
order; nxtc/foundc/exitgetpos become labelled block/loop exits with common tails.
Original source function boundaries, branch order and cleanup remain. TU macros,
readonly tables and comparator stay JS source-owned; C is typed ABI/dependencies.

Window/input, descriptions/names/format diagnostic tracing, selection floodfill,
travel/path predicates, displayed/remembered map content and dungeon placement
are controlled external fixture dependencies. Actual glyph_to_cmap, inherited
sort, sgn and libc memory/formatting are compiled dependencies. This does not
prove independent window/pager/cmd/selection/world algorithms or real player
interaction. Full game source exclusion/import closure, public recordings,
native macOS and every glyph/queue/callback mutation/edge case remain unverified.
Only configured CLIPPING is active; MACOS9 cursor locking remains inactive as in
actual preprocessing. Other ABI/char/coordinate/command layouts need revalidation.

JS dependency throws restore C-environment and binding-entry stack scopes. A
throw skips the outer C fixture caller's normal return, leaving that caller's
frame; the synthetic test verifies entry restoration then explicitly resets its
own outer frame. This is not general foreign-C exception unwinding or a promised
recovery path. Callback reentry into inherited globally stateful deterministic
qsort itself is not claimed safe or altered by this port.
