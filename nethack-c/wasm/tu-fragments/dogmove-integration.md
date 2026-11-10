# DOGMOVE frozen staged handoff

All **20** configured original `src/dogmove.c` functions are implemented in
`js/ported/dogmove.js`, in original order, with original names, parameters and
all block comments. Prepared source and pinned pristine source have identical
bytes (1,547 lines; SHA256 d6b80a15c36009ea34974179033fff53475400c39910ff74da4eac2b64e8cb40).
Source pet algorithms remain JS. This handoff changes no shared registry, build,
main runtime, native services, frozen TU or public artifact.

## Evidence and limits

Actual isolated **-O2 memory64** original-C reference and imported-JS hybrid builds
succeed via `.cache/dogmove-first-pass/build.py`; hybrid excludes original
`dogmove.c`. No build warnings were emitted. The unchanged differential suite
passes **2,429** return/state/trace/pointer/long64/callback/stack comparisons and
invokes all 20 configured function bodies. Actual execution includes native
C record layouts and memory; source-preservation checks are additional guards,
not a proof that every algorithm branch was reached.

The suite covers droppable weapon/tool/artifact preferences and object chains;
all four source nofetch bytes and all nine four-field qm rows; nutrition by body
size, corpses and partially eaten food; gold long/unsignedlong casts above2^53
and near signedlong limits; hunger/starvation; food splitting/rust/jelly/unpaid
price64 paths; inventory pickup/drop/eating; reachability; target/friend and
priest/minion/vampire positive scoring; movement candidates, original forward
joins, attack/displacement status results and minion/steed/conflict state;
quickmimic/leash/render paths; live callback ref copyback and same-TU reentry;
RNG logging that mutates a bound before evaluation and grows Wasm memory;
canonical pointer aliases and independent Module storage.

World dependency routines are controlled fixtures, including distance/vision,
map searching, damage/attacks, object consume/split/drop, names/display and
ownership witnesses. They record arguments/state and provide selected results;
they do not prove those separate upstream algorithms. The fixture uses a shared
controlled LCG input stream to compare call order/bounds/results; this is not a
proof of real game RNG backend equivalence. Traversal branches and return paths
not selected by this corpus, full level/world interactions, actual allocation/
deallocation services, real curses rendering and complete pet AI gameplay remain
unverified. **Native C, full-game, production and public checks were not run and
remain pending the integration owner.** No expectation waiver or native pass is
implied by these EmC-first results.

Source/scope guards pass: original configured names/order/parameters/comments;
42 runtime records/140 accessed fields; original bit widths/canonical typedefs;
84 original dependency prototypes and all20 source prototypes;152 relevant
configured macro definitions;4 nofetch entries/9 qm rows;25 original RNG kind/
line/function sites with lazy argument evaluation;487-byte exact source literal
corpus; original assert line417 and filename.164 compile-time width/sign/ABI/
prototype assertions additionally pass at O2. Inventory mutation is rejected.

An actual separate unchanged-suite negative control changes only the RNG-site
argument in an isolated copy of the binding. It fails after1,083 checks:
JS reports `dogmove.c:447:dog_invent` for the rn2(20) call; original C reports
`dogmove.c:446:dog_invent`. Exact failure and surrounding raw traces are in
`.cache/dogmove-first-pass/negative-rng-site/test.log`. Correct owned files remain
unchanged. The suite also deliberately changes a real hungrytime scalar whose
bytes equal a fixture-pool address and verifies that unchanged state comparison
rejects it. This guards against masking scalar differences as pointer identity.

## Files and ABI

- `js/ported/dogmove.js`:20 original bodies, nofetch[4], qm[9] and original macros.
- `js/ported/dogmove-runtime.js`: Module-local canonical live record/array views,
  exact scalar widths, native stack locals/ref cells and JS header macros.
- `nethack-c/wasm/tu-libraries/dogmove.js`: typed imports/dependencies and only
  transport/format/literal/cache seams.
- `scripts/tu-dogmove-layout.h`: compiler-derived constants, record sizes,
  non-bitfield widths and seenV byte size.
- `scripts/tu-dogmove-probe.c`, `scripts/test-tu-dogmove.mjs`: unchanged comparison
  fixture and corpus.
- `nethack-c/wasm/tu-fragments/dogmove-support.c`: typed global/field/address reads,
  writes, embedded copies, typed varargs/window/callback/dependency ABI and zero
  private backing. There are no pet algorithms or original C fallback bodies.
- `dogmove-source-data.h`: exact literal capacity, array counts, RNG provenance,
  assert provenance and source fingerprint.
- `dogmove-schema.json`: exact source-derived schemas, globals, literal corpus,
  RNG sites, glyph expressions, field/prototype/macro facts.
- `dogmove-source-check.mjs`: development compiler/source/data/type guards.

Original goto newdogpos/nxti/dognext joins are labeled JS blocks/loop continues.
Source DDIST/GDIST and thresholds remain JS. Long score/time/price and unsigned
quantity values use BigInt; source int-to-long promotion of rnd(5) is explicit.
C-width narrowing takes place before conversion to Number. Original coordinate
short and boolean signed-byte parameter conversions remain at core boundaries.

Canonical views cache by type+address **per Module**, preserving source pointer
`==` (mon/data/youmonst/objects) through distinct aliases. Embedded struct
assignment performs an actual native byte copy. Heap DataViews are recreated
for every access after callbacks, memory growth or reentry. The do_clear_area
ref initializes a native int stack cell, supplies the original callback, then
copies back through a fresh view in finally before restoring the stack. The
wantdoor callback receives the raw cell address, not a pointer to a monster.

nofetch is filled by JS into mutable zero char storage; qm rows are authoritative
JS objects, never a C constzero catalogue read back after filling. The persistent
native-size dummy object is mutable zero backing and copied from existing
cg.zeroobj on EVERY original droppables call. O2 therefore cannot fold reads of
a same-TU constzero table. Each Wasm Module has separate storage. Literals have
exact source-derived487-byte capacity, with per-Module bounded memoization;
adding runtime-generated strings requires explicit review/source-data update.

RNG site order, line numbers and owner function names are compiler/source
validated. Runtime calls rngCaller BEFORE evaluating lazy bound expressions,
matching rng_log_enabled/rng_log_set_caller macro ordering. Source sites sharing
one line remain separate. The actual underlying `(rn2)/(rnd)` dependencies are
called through typed seams. Assertion uses actual filename/line/function.

## Exact shared integration recipe (owner only)

1. Add registry entry below; exclude original dogmove.o in hybrid links. All20
   bodies belong to dogmove.c; no configuredFunctionHeaders extension is needed.

   ```json
   {
     "name":"dogmove",
     "source":"src/dogmove.c",
     "javascript":"js/ported/dogmove.js",
     "library":"nethack-c/wasm/tu-libraries/dogmove.js",
     "configuredFunctions":true,
     "probeContext":false,
     "probeExtraExports":["_probe_clear_area","_probe_qm","_probe_nofetch","_teleport_dogmove_global","_teleport_dogmove_read","_teleport_dogmove_write","_teleport_dogmove_address"],
     "adapterSources":[
       "js/ported/dogmove-runtime.js",
       "nethack-c/wasm/tu-fragments/dogmove-support.c",
       "nethack-c/wasm/tu-fragments/dogmove-source-data.h",
       "nethack-c/wasm/tu-fragments/dogmove-schema.json",
       "nethack-c/wasm/tu-fragments/dogmove-source-check.mjs",
       "scripts/tu-dogmove-layout.h"
     ]
   }
   ```

2. Compile support exactly once OR include it once in shared tu-support.c, never
   both. Keep source-data header next to it. Helpers/static storage have unique
   dogmove prefixes; no generic TELEPORT_REFERENCE_TU condition or source-private
   assertion leaks into unrelated references. Configured MAIL_STRUCTURES must be
   defined, SFCTOOL disabled. Keep the typed prototype/width assertions.
3. Add layout include and write `dogmove.json` from dogmove_layout array, using
   original names/values (A_NONE=-128 is a negative ordinary constant). Runtime
   requires pointer8/long8/int4/signedchar/littleEndian and seenVSize1. Preserve
   signed integer metadata before Number conversion if transport supplies raw
   unsigned64 bits. Current constants/sizes are all exactly representable once
   signed; raw pointer/function fields are NOT JSON numeric constants.
4. Import namespace dogmove and createDogmoveEnvironment; cache one environment
   per actual services.moduleKey/Module. Wrap every public/private dispatch in
   stackSave/try/finally stackRestore and withCEnvironment. Test's miniature
   dispatcher is executable reference for argument conversion. Explicit mapping:

   ```javascript
   const types={droppables:['monst'],cursed_object_at:['int','int'],dog_nutrition:['monst','obj'],dog_eat:['monst','obj','int','int','int'],dog_starve:['monst'],dog_hunger:['monst','edog'],dog_invent:['monst','edog','int'],dog_goal:['monst','edog','int','int','int'],find_targ:['monst','int','int','int'],find_friends:['monst','monst','int'],score_targ:['monst','monst'],best_target:['monst','int'],pet_ranged_attk:['monst','int'],dog_move:['monst','int'],could_reach_item:['monst','int','int'],can_reach_location:['monst','int','int','int','int'],wantdoor:['int','int','int'],finish_meating:['monst'],mnum_leashable:['int'],quickmimic:['monst']};
   ```

   Every int-marked argument becomes Number; others use env.view(kind,pointer).
   Source core then narrows original int/short/boolean parameters. wantdoor third argument (index2)
   is raw Number native int-cell address. Return droppables/find_targ/best_target
   as `.address ??0`; score_targ returns signed long BigInt (signature jpp).
   Preserve library private-symbol prefixes/callback import; all20 are present.
5. Add probe to build/test lists. Full fixture export list used in proof:

   ```text
   probe_clear_area, probe_reset, probe_vision, probe_pointer, probe_map, probe_option, probe_action, probe_snapshot, probe_trace, probe_qm, probe_nofetch, probe_stack, probe_layout_count, probe_layout_name, probe_layout_value, teleport_dogmove_global, teleport_dogmove_read, teleport_dogmove_write, teleport_dogmove_address
   ```

   Standard exports plus probe_qm, probe_nofetch, probe_clear_area are all required.
   Keep reference original source include and hybrid source exclusion as written.
6. Add source guard to integration validation. Existing checkers need only the
   new registry entry; no shared source-checker logic change is needed. Run owned
   sourceguard using SDK Node, core/scope checks and unchanged differential test.
   Private proof uses TELEPORT_NATIVE_TESTS=0 and DOGMOVE_PROBE_DIR=.cache/dogmove-first-pass;
   no native backend was supplied or fabricated.

## Snapshot representation precision

The fixture compares action return values and raw byte snapshots of objpool[16],
monsters[8], edogs[8], mextras[8], u, gy.youmonst and entire svl.level, plus listed
goal/bhit/notonhead/suppress-price state and dependency/RNG/format traces. It does
not compare an entire game address space or serialization stream. Initialized
padding and all scalar bytes remain raw. Only original compiler-typed selected
pointer fields below are canonicalized recursively, before comparison.

Known regions map to regionID<<48 plus exact byte offset: mons1,objpool2,mpool3,
mextras4,dogs5,priests6,minions7,names8,u9,gy.youmonst10,tracks11,traps12. Null stays0;
unknown pointers stay their raw bits and can fail the comparison. There is no
blanket byte scanning. Aliases/offsets/distinct pools retain their relationships;
nonpointer scalars equal to an address remain raw (negative regression present).
Unused/unselected pointer fields remain raw rather than being guessed.

Exact generated selected-pointer field inventory (recursive snapshots use only
records reached from the snapshot roots; source AST types are in schema):

- vptrs: v_nexthere.
- trap: ntrap.
- window_procs: win_display_nhwindow.
- symdef: explanation.
- obj: nobj.
- monst: minvent, mw, mextra.
- objdescr: oc_name, oc_descr.
- c_common_strings: c_something.
- mextra: epri, emin, edog.
- instance_globals_f: ftrap.
- Gender: his.
- instance_globals_i: invent.
- you: usteed.
- dlevel_t: monsters[i0][i1], objlist.
- instance_globals_v: viz_array.

## Register append text for parent

PAR04-DOGMOVE staged implementation preserves all20 configured original source
bodies/order/parameters/block comments, nofetch[4], qm[9], original control flow
and25 original RNG sites. Typed support contains no pet algorithm fallback;
mutable private backing avoids constzero read folding at O2. Isolated real
Emscripten-C versus imported-JS memory64 O2 comparison passes2,429 checks with
all20 invoked, controlled world/RNG/dependency fixtures. Source/configuration/
data/type/prototype/scope guards pass. Unchanged-suite injected RNG-site control
fails at1,083 checks with wrong447 versus original446; real scalar-address byte
regression is also rejected. Typed pointer-field mapping preserves aliases and
offsets and leaves all scalar/unselected/unknown data raw, documented above.
No shared/default/native/public/production artifacts were changed or tested.
Native/full-world/production/public remain pending, not passed or waived. Final
input/artifact hashes are .cache/dogmove-first-pass/verified-inputs.json.
