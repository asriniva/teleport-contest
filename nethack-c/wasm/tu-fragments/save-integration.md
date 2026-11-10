# SAVE frozen staged handoff

All **26** configured original `src/save.c` functions are implemented in
`js/ported/save.js`. Original names, order, parameters, block comments and control
flow are retained. The original forward cleanup labels are represented by JS
labeled blocks; entry `xint8` conversions retain original signed-byte parameters.
Prepared SAVE source equals pinned pristine source. No shared registry, build,
main runtime, frozen source or expectation file was edited for this handoff.

## Owned files

- `js/ported/save.js`: all26 original bodies, with JS algorithms only.
- `js/ported/save-runtime.js`: canonical per-Module typed live views, local/native
  reference cells, embedded-struct copies and original header macro expansions.
- `nethack-c/wasm/tu-libraries/save.js`: memory64 import/dependency ABI.
- `scripts/tu-save-layout.h`: active-compiler sizes, widths and constants.
- `scripts/tu-save-probe.c`, `scripts/test-tu-save.mjs`: controlled differential
  fixture and unchanged comparison assertions.
- `nethack-c/wasm/tu-fragments/save-support.c`: typed global/field/address access,
  original-size zero static backing and typed file/window/format/callback seams.
- `save-source-data.h`: source-derived1651-byte literal capacity, one original
  Snprintf site, two Strlen sites and original assert source/line provenance.
- `save-schema.json`: compiler-derived74 record schemas,170 accessed fields,
  live global descriptors and exact dependency prototype strings.
- `save-source-check.mjs`: source/configuration/schema/prototype/site guards.

There is no original SAVE C algorithm fallback in the hybrid. The C reference
fixture intentionally includes the original source; its hybrid branch excludes
it and imports the JS bodies. Static zero trap/fruit backing in support is
separate per Wasm instance, retains original compiled sizes and remains live.

## Actual evidence and limits

Final isolated **-O1 memory64** reference and imported-JS builds succeed via
`.cache/save-first-pass/build.py`. The final build log has no warning. The suite
invokes all26 bodies and passes **2,023** EmC/JS byte-stream, state, ownership,
callback, return and stack comparisons. Logs are in `.cache/save-first-pass/`.
Final source/input/artifact hashes are in `verified-inputs.json` there.

Tested scenarios include all COUNTING/WRITING/FREEING bit combinations, empty
and nested object/monster lists, inventory/context pointer aliases, saved
victual/tin/spbook/polearm/stuck/steed IDs, object extensions including a nested
monster and all six monster extension structures, fruit filtering, cemetery/
damage/stair/trap/level/gamelog lists, relative stair/trap levels, dog/level timestamps and restored
level fields, live mode changes, local serializer-reference mutation, checkpoint
pid refs/mismatch/missing/open/create errors, save cancellation/create failure
and an empty-world successful dosave0, original player-name/playmode slots,
>32bit and >2^53 long/time_t values, original function/line string provenance,
callback memory growth, combined growth/reentry/ref mutation and distinct Module
views/static sentinel backing. The user-ID case caught a real unsigned32 return
transport bug; its Wasm result is now explicitly zero-extended before the
original unsigned-long cast. Signed-byte conversion on internal level calls is
also preserved, including a ledger128 input regression.

Every byte passed to the controlled `sfo_*` callbacks is compared, including
padding initialized by this fixture. The callbacks are dependency witnesses;
they do **not** run production SFBASE/SFSTRUCT serializers or write real save
files. `free`/deallocation dependencies record pointer identities/state/order
without releasing fixture-owned static allocations. The state snapshot records
saving/notices/freeing/worth flags, current/saved levels, inventory/migrating
heads, remaining list presence, realtime fields, saved context IDs and saved
stuck/steed IDs. Deallocation callbacks additionally record the exact object
cleanup fields/freeing state and monster chain termination. This is not a
comparison of every global or every unaccessed record field after every call.

Pointer addresses differ between independently linked modules. Only the typed
pointer-field slots listed below are normalized; recursion descends into
schema-selected embedded records/arrays, and never follows a pointer. A known
fixture allocation pointer becomes `(regionId << 48) + byteOffset`, preserving
null, distinct regions, aliases and interior offsets. Region IDs1..21 are,
respectively, objpool/oextras/monsters/mextras/dogs/species/traps/fruits/cemeteries/
damages/stairs/levels/logs/names/guards/priests/shops/minions/bones/doors/file.
Unknown pointers remain byte-for-byte raw. Fields outside the partial typed
schema also remain raw; a nonzero unregistered pointer there can fail a test,
not silently become a pass. Scalar and padding bytes are never scanned for
pointer-like values and never mapped. In particular an actual `obj.owornmask`
containing a real fixture pool address is asserted to remain that exact scalar
value. Deliberately mismatched scalar and unknown-pointer fixtures are rejected
by the same comparison function. Known pool/null/interior aliases are checked.

One external **unchanged-suite negative control** removes only unsigned-getuid
zero extension from a separate hybrid library/build. The unchanged suite fails
at byte34 of the UID record: actual `98badcfeffffffff`, original C
`98badcfe00000000`. Exact log:
`.cache/save-first-pass/negative-uid/test.log`; orchestration log:
`.cache/save-first-pass/negative-control.log`. No expectation or comparison was
changed to accept that difference.

Native macOS, mixed production-game activation and public recordings are
**pending**. Full real-world save/restore ownership, actual filesystem/short-I/O
behavior, populated cross-level getlev/copy loops, signal/hangup delivery,
terminal successful `dosave`/sound/nh_terminate, fatal panic/assert process paths
and every dependency callback combination are unverified. `done(TRICKED)` is a
controlled returning dependency here, modeling its wizard-return path. No
native difference is waived or labeled passing. A bounded parent source review
found no further concrete issue in the reviewed alias/struct-copy/time seams;
this is not all-path or native equivalence proof.

## Exact shared integration recipe (integration owner applies)

1. Add registry entry:

   ```json
   {
     "name":"save",
     "source":"src/save.c",
     "javascript":"js/ported/save.js",
     "library":"nethack-c/wasm/tu-libraries/save.js",
     "configuredFunctions":true,
     "adapterSources":[
       "js/ported/save-runtime.js",
       "nethack-c/wasm/tu-fragments/save-support.c",
       "nethack-c/wasm/tu-fragments/save-source-data.h",
       "nethack-c/wasm/tu-fragments/save-schema.json",
       "nethack-c/wasm/tu-fragments/save-source-check.mjs"
     ]
   }
   ```

   Standard source exclusion must remove original `save.o`. No configured
   function-header extension is required: all26 bodies are owned by save.c.
2. Compile `save-support.c` once OR include it once in shared `tu-support.c`,
   never both. Helpers are uniquely prefixed; no generic TELEPORT_REFERENCE_TU
   condition controls their existence. The support can be included by unrelated
   reference probes. Its source guards reject changed configured platforms:
   DEBUG/UNIX/MAIL/HANGUPHANDLING/INSURANCE/FREE_ALL_MEMORY/DUMPLOG_CORE enabled;
   NO_SIGNAL/MICRO/TOS/VMS/USER_SOUNDS/SFCTOOL disabled. Static width/sign and
   dependency-prototype assertions are active. Core/runtime metadata additionally
   checks pointer/long/time_t64, int32, signed char and little-endian target.
3. Import the SAVE namespace and `createSaveEnvironment`. Cache one environment
   per actual `services.moduleKey`/Module, never globally across instances. Each
   public/private entry uses existing `stackSave`/finally-`stackRestore` and
   `withCEnvironment`. The tested miniature dispatcher is in test-tu-save.mjs.
   Argument conversion is exactly:
   - Every `nhfp` argument: `env.view('nh_file', rawPointer)`;0 remains0.
   - savecemetery arg1: `env.pointerCell('cemetery', rawPointerToPointer)`.
   - saveobjchn arg1: `env.pointerCell('obj', rawPointerToPointer)`.
   - saveobj arg1: `env.view('obj', rawPointer)`.
   - savemon/savemonchn arg1: `env.view('monst', rawPointer)`.
   - savetrapchn arg1: `env.view('trap', rawPointer)`.
   - tricked_fileremoved arg1 whynot: raw Number pointer.
   - savelev/savelev_core/save_bubbles arg1: Number; their original xint8 entry
     narrowing is in the core and therefore also applies to internal calls.
   Remaining functions have only nhfp or no parameters. Return values are the
   source int/boolean or void. All 26 imported/public/static symbol signatures
   are present in the library; private exports use `teleport_save_` prefixes.
4. Keep the binding's signed/unsigned64 argument and result paths intact.
   `getnow`, time_t parameters to timet_delta/yyyymmddhhmmss, long realtime/
   timestamp values, uid's unsignedlong cast and size_t use BigInt. getuid's
   unsigned32 result MUST use `>>>0`, not signed Number. strlen alone converts
   its bounded Wasm memory length to Number. SIG_IGN is obtained as raw uintptr_t
   BigInt from the actual compiler; its configured -2 sentinel must never pass
   through an imprecise JSON/Number conversion. Window/sound callback pointers
   route through original typed C ABI; canonical object/monster view caching
   is required for source pointer `==`. Embedded `gu.uz_save=u.uz` assignments
   invoke native byte copies rather than view alias assignment.
5. All local serializer refs initialize an actual native stack cell, call the
   genuine dependency, copy back through a fresh heap view in finally, then
   restore stack. Do not replace reference objects with copied values or stale
   DataViews. Runtime macros release_data/update_file, notice_mon and VIA_WINDOWPORT
   stay JS. debugpline's decision stays JS and its C seam calls original
   debugcore with the SAVE source filename rather than the support fragment.
   Header Strlen sites retain original __func__/CPP-expanded lines245 and1041;
   Snprintf uses store_plname_in_file/line1010 (closing multiline call line).
   Assert's original expression, function, source pathname and line1017 are
   frozen from actual inspected preprocessing. An integration compile using a
   different source pathname must regenerate/check that diagnostic provenance;
   the current source-guard invocation uses `.cache/wasm64-build/tree/src/save.c`.
6. Add `save:[]` to layout writer: fixture metadata has dynamic layout_count/
   name/value, all sizes/field widths and constants, no terminal override.
   Add pre-build `node nethack-c/wasm/tu-fragments/save-source-check.mjs` using
   the SDK Node. It verifies pristine/prepared equality, source hash, all26
   names/order/params/comments,74 record/170 field types/bitwidths, live globals,
   dependency prototypes, exact1651 source-literal bytes, one formatter/two
   Strlen sites, two original zero sentinels and absence of RNG sites. An
   inventory mutation is rejected. No arbitrary-capacity storage or runtime
   original-C parsing is used.
7. Probe builder both modes: compile `scripts/tu-save-probe.c` and support once.
   Reference's probe source already includes original prepared save.c: do NOT
   add it again as a separate input. Hybrid sets `-DHYBRID_SAVE=1`, adds SAVE
   library and omits original C. This is a controlled dependency fixture;
   production C dependencies are not supplied by these fixture witnesses.
   Export with underscore prefix:
   `probe_disp_freemem,probe_reset,probe_pointer,probe_option,probe_action,probe_snapshot,probe_trace,
   probe_stack,probe_layout_count,probe_layout_name,probe_layout_value,
   teleport_save_global,teleport_save_read,teleport_save_write,
   teleport_save_address`.
   Test expects `save-reference.mjs` and `save-hybrid.mjs` under standard
   `.cache/tu-probes` or private SAVE_PROBE_DIR. Current isolated command:
   `TELEPORT_NATIVE_TESTS=0 SAVE_PROBE_DIR=.cache/save-first-pass node scripts/test-tu-save.mjs`.
   Root owns subsequent native registration/production/public checks.

## PAR03-SAVE exact register text for integration owner

PAR03-SAVE staged implementation: all26 configured original save.c functions are
JS, retaining original boundaries/order/parameters/comments/control flow and
signed xint8 entry conversions. Prepared source equals pristine. Native compiled
live fields, canonical per-Module object/monster aliases, copied embedded level
structs, pointer-to-pointer and local serializer refs, actual time_t/long/size_t64
BigInt transport, compiler SIG_IGN and typed callback/file/varargs dependencies
are isolated in save-runtime.js, its Wasm library and SAVE-specific ABI/data
fragments. There is no original SAVE C fallback. Actual compiler source/config,
record/bitfield/prototype/width/sign/endianness checks guard74 records/170 accessed
fields,38 globals,1651 source-literal bytes, two original zero sentinels, one
Snprintf/two Strlen function-line sites and zero RNG sites. Isolated -O1 memory64
reference/hybrid builds pass2,023 byte-stream/state/alias/ownership/ref/callback/
stack comparisons invoking all26 bodies. Controlled serializer callbacks compare
all passed bytes with normalization ONLY of explicitly typed pointer fields to
known fixture region+offset identities; scalar/padding bytes and unknown pointers
remain raw. Scalar-equals-pointer and deliberately mismatched scalar/unknownptr
regressions verify comparison precision. A separate unchanged-suite negative
control reintroducing signed getuid return transport fails UID bytes as required;
the binding now explicitly zero-extends unsigned32 before source unsignedlong
conversion. Fixture serializers/free/file/error witnesses do not prove production
serialization/I/O, actual heap release, populated cross-level getlev, signal/
terminal/fatal paths or full world saves. Native macOS, actual mixed production
activation and recordings remain pending. No native discrepancy was waived and
no existing correction, source patch or expected result was changed.

## Exact typed pointer mapping coverage

The following is generated from `save-schema.json` and matches `normalize_*`
functions in the probe; additional unselected pointer fields are not mapped.

- `stairway`: `next`.

- `trap`: `ntrap`.

- `window_procs`: `win_exit_nhwindows`, `win_clear_nhwindow`, `win_display_nhwindow`, `win_mark_synch`, `win_getmsghistory`.

- `sound_procs`: `sound_exit_nhsound`.

- `oextra`: `oname`, `omonst`, `omailcmd`.

- `s_level`: `next`.

- `tin_info`: `tin`.

- `book_info`: `book`.

- `obj`: `nobj`, `cobj`, `oextra`.

- `victual_info`: `piece`.

- `polearm_info`: `hitmon`.

- `monst`: `nmon`, `data`, `minvent`, `mextra`.

- `fruit`: `nextf`.

- `instance_globals_b`: `billobjs`.

- `mextra`: `mgivenname`, `egd`, `epri`, `eshk`, `emin`, `edog`, `ebones`.

- `Role`: `filecode`.

- `instance_flags`: `wc_tile_file`, `wc_font_map`, `wc_font_message`, `wc_font_status`, `wc_font_menu`, `wc_font_text`.

- `instance_globals_f`: `ftrap`, `ffruit`.

- `Race`: `filecode`.

- `instance_globals_g`: `gamelog`.

- `Gender`: `filecode`.

- `instance_globals_i`: `invent`.

- `instance_globals_l`: `looseball`, `loosechain`.

- `Align`: `filecode`.

- `damage`: `next`.

- `cemetery`: `next`.

- `you`: `ustuck`, `usteed`.

- `gamelog_line`: `text`, `next`.

- `instance_globals_m`: `migrating_objs`, `mydogs`, `migrating_mons`.

- `dlevel_t`: `objlist`, `buriedobjlist`, `monlist`, `damagelist`, `bonesinfo`.

- `instance_globals_o`: `objs_deleted`.

- `instance_globals_s`: `stairs`.

- `instance_globals_saved_d`: `doors`.

- `nh_file`: `fplog`.

- `instance_globals_saved_s`: `sp_levchn`.


## Authorized signed-metadata/cleanup-observation follow-up

The existing accepted EmC module already returned **-8n** for DISP_FREEMEM:
Wasm exports expose i64 bits as signed BigInt even though its C metadata carrier
is size_t. Therefore its original Number(raw) yielded -8 and the real JS binding
sent -8. An earlier static-analysis report of an observed -8-to0 game defect was
**incorrect**; direct inspection disproved it. This follow-up does not establish
or claim an existing production/native cleanup failure.

The narrow authorized change leaves SAVE's core, runtime, library and support
fragment byte-identical to the accepted handoff. It changes only the fixture,
private metadata decoder, source guard and these notes. The fixture's real
`tmp_at` dependency now records BOTH coordxy arguments. Its compiled
`probe_disp_freemem()` returns original DISP_FREEMEM directly, without duplicating
the constant in a test expectation. Private metadata uses BigInt.asIntN(64)
BEFORE Number and checks both signed and unsigned64 carriers against that actual
compiler constant; this avoids rounding if a native/other transport reports
unsigned64 bits. A dedicated freedynamicdata test asserts the real trace event
`tmp_at:-8:0`. The final count is 2,023 comparisons. Root owns shared layout writer
normalization/regeneration; these owned files do not change accepted production
snapshots or the central writer.

Full negative ordinary metadata inventory from the actual private module:
**DISP_FREEMEM only**, signed -8, raw bits 0xfffffffffffffff8. All current other
SAVE ordinary metadata values are nonnegative exact small integers. SIG_IGN is
NOT in this metadata table: its typed uintptr_t helper remains raw BigInt,
configured bits 0xfffffffffffffffe, and must never pass through Number. There
are no current high-bit unsigned64 ordinary layout values requiring another
exception. Future such values require an explicit lossless representation.

A second separate **unchanged-suite negative control** changes only the first
argument of SAVE's tmp_at binding to 0 in an isolated library copy. The unchanged
comparison rejects actual `tmp_at:0:0` versus original-C `tmp_at:-8:0`; exact log
`.cache/save-first-pass/negative-tmp-coord/test.log`. This proves the newly
observed coord is checked. It is an injected regression, not a claim that the
accepted production binding sent 0. The earlier unsigned-getuid negative control
also remains active. Original 2,007-check evidence/input hashes are preserved in
`verified-inputs-before-signed-metadata.json`; new inputs/artifacts are frozen in
`verified-inputs.json` after verification.

Shared integration additionally exports `probe_disp_freemem` for the SAVE
fixture and reconstructs signed ordinary SAVE metadata before Number. Keep
SIG_IGN's existing raw64 exception (if emitted elsewhere); the current support
obtains it through its typed helper rather than this table.

Register text for root: SAVE validation follow-up preserves all four production
implementation files byte-for-byte. Actual accepted EmC metadata already yielded
DISP_FREEMEM=-8n; the earlier apparent -8-to0 defect inference was disproved and
must not be presented as an observed game regression. Fixture tmp_at now records
both coordinates and its compiler-constant getter anchors the expected signed
value without copying the constant. Private decoding reconstructs signed64 before
Number for both signed/unsigned64 carriers. 2,023 comparisons pass; an injected
first-coordinate0 binding is rejected by unchanged C/JS comparison, as is the
existing unsigned getuid regression. Shared layout normalization/regeneration is
owned by root. Native/production/public/full-world limitations remain unchanged.
