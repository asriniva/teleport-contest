# GLYPHS frozen first pass — 27 configured source functions

Prepared `.cache/wasm64-build/tree/src/glyphs.c` and pristine
`nethack-c/upstream/src/glyphs.c` are byte-identical (1,324 lines).
All27 configured source functions, original names/order/parameters/comments,
control flow and source-owned algorithms reside in `js/ported/glyphs.js`.
Actual memory64 preprocessing enables ENHANCED_SYMBOLS, leaves TEST_GLYPHNAMES
inactive and excludes the source's older #if0 shuffle implementation. No native
algorithm has been newly enabled/disabled. Those inactive comments remain.

## Exact integration recipe

Registry entry:

    {"name":"glyphs","source":"src/glyphs.c",
     "javascript":"js/ported/glyphs.js",
     "library":"nethack-c/wasm/tu-libraries/glyphs.js",
     "configuredFunctions":true,"reference":"prepared"}

Import `createGlyphsBridge` from './glyphs-runtime.js' and instantiate one bridge
per runtime when layouts.glyphs exists. Add the actual binding dispatcher:

    const callGlyphs=layouts.glyphs ? createGlyphsBridge(layouts.glyphs) : undefined;
    glyphs(services,name,...args) {
        if (!callGlyphs) throw new Error('Missing GLYPHS layout');
        return callGlyphs(services,name,...args);
    }

Use the flat `_probe_layout_name/value` dictionary through `_probe_layout_count`
as layouts.glyphs. No startup hook: the bridge initializes its original private
state once per Module before invoking source code. JS owns zero_find's fields,
cache pointer/size/logsize, enum values, nonzero_black expression, two nag statics,
and all original text/offset/temporary arrays. Cache allocations remain the
source's original alloc/dupstr/free sequence. Fixed source records use three
mutable, zero-only C backing records; there is no initialized const C mirror.
Actual optimized C reads of the source's private records compare with JS writes,
including nonzero val/color/callback. Independent signed32 write/read witnesses
exercise optimized backing. Both Modules retain separate original static state.

Include `#include "tu-fragments/glyphs-support.c"` once in common tu-support.c.
Typed helpers expose12 record kinds/41 fields,5 global paths,8 external arrays,
header glyph macros, exact callback signatures, dependency/formatting calls and
91 source literal strings in909 zero-only bytes. They contain no GLYPHS parser,
cache/hash/shuffle/color algorithm or initialized catalogue fallback.
**TELEPORT_GLYPHS_VALIDATE_SOURCE is defined only by the actual GLYPHS reference
fixture, immediately after including original glyphs.c.** Never define it in
common support or unrelated reference probes. It validates actual source-private
record sizes/offsets/field widths/enum signedness/enum values. Generic
TELEPORT_REFERENCE_TU support-only syntax passes without original private types.
A deliberately widened mirror val field is rejected by actual-source assertions.

Exclude glyphs.o from the game link through the registry. Public imports17:
`glyphrep_to_custom_map_entries glyph_to_cmap fill_glyphid_cache
free_glyphid_cache glyphid_cache_status match_glyph glyphrep
add_custom_nhcolor_entry apply_customizations maybe_shuffle_customizations
find_matching_customization purge_all_custom_entries purge_custom_entries
dump_all_glyphids wizcustom_glyphids clear_all_glyphmap_colors reset_customcolors`.
The active source-private callback address is the JS alias
`teleport_glyphs_to_custom_callback` (original JS name remains
`to_custom_symset_entry_callback`). Its address can be stored/invoked by real C
callbacks and preserves function pointer identity. Nine other private aliases
`teleport_glyphs_test_` cover fix_glyphname,glyph_find_core,init_glyph_cache,
add_glyph_to_cache,find_glyph_in_cache,find_glyphid_in_cache_by_glyphnum,glyph_hash,
shuffle_customizations,parse_id; these should dead-strip in the game.

Probe exports `_probe_` prefix plus malloc/free:
`clear reset input option symset flags request description glyph custom call
color trace dump snapshot stack layout_count layout_name layout_value
loadsyms_count loadsyms_name loadsyms_range private backing`.

Both modes compile ONLY scripts/tu-glyphs-probe.c plus actual prepared
`utf8map.c coloratt.c hacklib.c`, with compile-defines.json, memory64, forced
native-terminal.h, `-Dfree=teleport_probe_free`,
`-Dfprintf=teleport_probe_fprintf`,1MiB stack and heap growth. Reference adds
TELEPORT_REFERENCE_TU, includes prepared glyphs.c exactly once; hybrid uses the
GLYPHS JS library and never compiles/includes original glyphs.c. Both fixture
modes already include glyphs-support.c, so do not link common tu-support.c again.
The fixture includes actual objects.c/monst.c and actual source-derived loadsyms
and monsdump/objdump data in glyphs-fixture-data.h; do not add those TUs a second
time. Add GLYPHS to builder source-inclusion/common-support exceptions. Private
exact build command is `.cache/glyphs-first-pass/build.py`.

GETPOS's frozen fixture currently links original glyphs.c as an external C
dependency. Keep its oracle unchanged for this first-pass promotion; resolving
that separate fixture's integration belongs to the integration owner. This
handoff does not edit GETPOS or claim it exercised JS glyphs as a dependency.

Run `node nethack-c/wasm/tu-fragments/glyphs-source-check.mjs` with source/comment/
parameter/order and lexical checks. Guard: actual fresh CPP profile and8
Snprintf closing-line origins;5 exact text arrays,2 offsets,6 UTF8 bytes;
91 literals/909bytes and exact extracted external loadsyms/mon/obj enum data;
unsigned32 hash/logical rotation, signed char, size_t64,
private mutable backing, source enums and internal callee stack lifetime.
Core/bridge/binding/layout/helper/source guard/fixture data must be build hashes.

## Evidence and limits

Private actual `-O2` memory64 reference/hybrid suite: **41,354 comparisons**,
all27 configured original bodies invoked. It compares returns, full snapshots,
allocation/dup/free ordering and identities, callbacks/diagnostics/dump text,
input mutation, stack restoration and C-environment cleanup. Complete glyph
cmap domain; complete generated-name dump and cache lookups; original duplicate
name lookup behavior; selected inverse glyph lookups/uncached parsing; every
actual loadsyms name; signed-char and long unsigned hash rotation; empty/missing/
repeated cache operations; symbol/glyph Unicode/RGB parsing; two symsets and
color/symbol/UTF8 gates; update/purge/reset; shuffled and duplicate object
description Unicode allocation ownership; controlled wizard-list callback exit;
actual memory growth, callback reentry and separate Module state are covered.

Negative control: copy only the JS source/runtime into private negative directory,
change unsigned hash rotation `hash >>> 31` to arithmetic `hash >> 31`, and run
**the same suite against unchanged original C**. It rejects the long glyph hash:
C3120682645 versus wrongJS4294967180. No oracle/expected behavior was normalized
or waived. Evidence `.cache/glyphs-first-pass/negative-hash.log`.

The suite uses real prepared Unicode/color/hacklib functions and actual original
monster/object/symbol catalogues. Configuration messages, assertions/panic,
allocator tracking, dump output and wizard UI callbacks are controlled fixtures;
there is no real window/OS interaction. Full wizard enumeration is callback-
terminated after its first delivered entry; the complete naming/dump/cache
paths are separately compared. Cache exhaustion/OOM and every malformed-input
combination are not exhausted. No native-host, mixed game, public recording,
foreign-caller or production-artifact parity is claimed. These remain later
integration/native gates; the historical53-suite native result does not cover
this TU. Build success/source guards are not equivalence proofs.

Logs and final SHA256 manifest: `.cache/glyphs-first-pass/{build.log,test.log,
source-check.log,source-preservation.log,scope-check.log,
generic-reference-support.log,negative-private-assert.log,negative-hash.log,
input-hashes.json}`. No shared registry/build/layout/runtime/artifact was edited
by this owner.
