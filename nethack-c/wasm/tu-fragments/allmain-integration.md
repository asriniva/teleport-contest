# ALLMAIN frozen first pass —16 source functions

All16 configured original functions/order/parameters/comments/control flow are
in js/ported/allmain.js. Actual prepared/pristine allmain.c are byte-identical
(1003source lines). Both original file statics retain their names and0 initial
values as JS data; mutable values live once per actual Module in the bridge.
No original ALLMAIN C body or initialized static algorithm/data fallback remains.

## Exact promotion recipe

Registry:

    {"name":"allmain","source":"src/allmain.c",
     "javascript":"js/ported/allmain.js",
     "library":"nethack-c/wasm/tu-libraries/allmain.js",
     "configuredFunctions":true,"reference":"prepared"}

Import `createAllmainBridge` from './allmain-runtime.js'. Within
createPortedRuntime instantiate `const callAllmain=layouts.allmain ?
createAllmainBridge(layouts.allmain) : undefined;`. Add the dispatcher actually
called by this binding:

    allmain(services,name,...args) {
        if (!callAllmain) throw new Error('Missing ALLMAIN layout');
        return callAllmain(services,name,...args);
    }

One bridge per runtime; state WeakMap uses actual services.moduleKey (Module).
The bridge preserves C scope and saves/restores its own ABI stack in finally.
No startup hook is required. early_init initializes normal C globals through
its original dependencies; it does not reset the original separate file statics.
All state views are live typed calls, so decl_globals_init/reentry/memory growth
cannot leave a cached field/buffer value stale.

Include `#include "tu-fragments/allmain-support.c"` once from shared tu-support.c.
It contains typed field/header/printf/RNG/function-pointer/dependency ABI only,
and exact zero-only literal backing; no ALLMAIN algorithm. The3 original
U_CAN_REGEN uses are expanded inside regen_hp itself. No private-source assertions
use generic TELEPORT_REFERENCE_TU: this helper contains no private source types.
Exclude original allmain.o through the registry. No terminal/native backend,
Lua implementation, source compiler flags or frozen harness changes belong here.

Public original imports9:
`early_init moveloop_core moveloop stop_occupation init_sound_disp_gamewindows
newgame welcome timet_to_seconds timet_delta`.
Private test aliases7, prefixed `teleport_allmain_test_`:
`moveloop_preamble u_calc_moveamt maybe_generate_rnd_mon maybe_do_tutorial
regen_pw regen_hp interrupt_multi`.
The aliases should dead-strip in the actual game. Each original body stays JS.

Layout is the flat `_probe_layout_name/value` dictionary across
`_probe_layout_count` as layouts.allmain; values are signed long. Source strings
are a guarded exact31-string/636-byte corpus; NEWS remains a header-provided
string pointer. Window IDs and all98 actual global paths stay live C fields.
181 typed services include actual header/dependency calls, with no guessed
C structure offsets. Runtime core/bridge/library/helper/layout/source checker
must be build-hash inputs.

Probe exports (`_probe_` prefix, plus malloc/free):
`clear reset fields field_name field option roll clock caps poly occupation
steed sex lua role prop prop_count prop_id time call trace snapshot stack
layout_count layout_name layout_value`.

Compile ONLY scripts/tu-allmain-probe.c in both modes with existing
compile-defines.json, memory64 and forced native-terminal.h. Reference adds
TELEPORT_REFERENCE_TU and includes prepared allmain.c once; hybrid links only
its typed JS library, without compiling allmain.c. The fixture includes this
support, so do not add main tu-support.c as well. Add ALLMAIN to the probe
builder's source-inclusion exceptions to avoid duplicate inclusion. No dependency
rename flags. Private isolated build recipe: .cache/allmain-first-pass/build.py.
The fixture uses emscripten heap/stack/EM_JS controlled throws and needs a native
fixture adapter before native execution. It never sends OS messages or signals;
signal, window, mail, Lua, tutorial and game-event dependencies are fixtures.

Run `node nethack-c/wasm/tu-fragments/allmain-source-check.mjs` as an additional
source/configuration gate. It freshly checks actual compiler macros and rejects
changed profiles: CRASHREPORT/SAFERHANGUP/STATUS_HILITES/MAIL/CLIPPING/NEWS/
INSURANCE are active; POSITIONBAR/MICRO/WIN32/WIN32CON/CHANGE_COLOR/
TTY_PERM_INVENT/MACOS9/NO_SIGNAL/SOUNDLIB/SOUNDS/USER_SOUNDS are inactive.
No facility is newly disabled by this translation. Inactive source comments
are retained as documentation, not claimed as translated configured functions.

## C widths, call order and evidence

Movement division truncates like original C. Scalar writes use actual C lvalues,
including signed-short hero/monster movement, enum/bitfield narrowing and the
source integer/boolean promotions in health regeneration.12 compiler-audited
long/time fields remain BigInt, including hilite_delta, u.usleep and the unsigned
tribute.tributesz size_t field; the latter decodes as unsigned64. C compile-time
size/signedness assertions and actual callback reads guard these distinctions.

Time conversion calls actual libc difftime with full signed64 time_t arguments,
then performs the original double→long cast in a typed C helper. It does not
subtract rounded JS timestamps. Float→long outside the representable range is
original C undefined behavior; portable equivalence there is not claimed.

All16 RNG sites retain source caller and actual compiler closing-line origins.
The multiline random-monster call uses line166, rather than its opening164.
Bound expressions are deferred until after original caller logging; depth,
night and ACURR may call dependencies which consume RNG/change the logger.
This order is explicitly exercised with RNG-consuming bound callbacks.

The original occupation callback remains a C function pointer invoked through
its exact signature. Monster/level views retain actual addresses, including
interior tutorial/hero level pointers. Fixed-source printf wrappers pass actual
string pointers to C formatting; welcome's original BUFSZ buffer remains on
the ABI stack, with original eos/append/control order. Its direct call from
newgame uses callLocal with stackSave/finallyRestore, releasing the callee's
buffer before subsequent source callbacks. An actual callback-SP regression
checks this boundary; a separate wrong unscoped copy fails that unchanged test
with a retained256-byte buffer (negative-scope.py/log). No U_INIT lifetime
changes are included in this handoff.

Current isolated test result: **4,975 configured Emscripten-C/JS comparisons**.
All16 source routines are invoked, including infinite moveloop terminated by a
controlled event callback. Tests cover movement/encumbrance/fast/steed and short
narrowing; normal/polymorph/eel/regeneration/sleep/energy matrices; preamble
calendar/resume/fuzzer/inventory behavior; occupation callbacks; window IDs and
unsigned64 capability masks; tutorial/startup/newgame/reroll/welcome; long counters,
C difftime near >53-bit inputs; turn-loop branches, Lua callback ABI, billion-turn
cap; callback reentry, actual heap growth, normal stack restoration, environment
cleanup and separate actual Modules sharing one runtime bridge.

The unchanged suite rejects a separate wrong-JS copy converting difftime inputs
to Number: at9007199254740997-9007199254740996, actual original C returns1 and
faulty JS returns0. Delivered source and expected checks stay unchanged. Proof:
.cache/allmain-first-pass/negative.py and negative.log.

Source/function/order/parameter/all-comment and lexical checks pass. The source
guard checks2JS-owned statics,3 owning-function regen macro expansions,16RNG
sites,12 compiler64bit fields, exact literals/backing and current feature profile.
The AST/type audit and all build/test/proof/input hashes live under
.cache/allmain-first-pass. Actual hybrid import/dependency proof excludes the
original TU and preserves16 original-function JS imports.

Limits: game/startup/UI/mail/sound/calendar/monster/HP/energy/occupation/Lua/
signal/assert/termination/string-helper dependencies are controlled fixtures.
Actual libc difftime/string-format/allocation dependencies remain linked. This
is not a real full-game run, actual Lua callback execution, OS signal test,
public recording result or native-macOS proof. Those gates remain pending.
A controlled EM_JS throw bypasses the outer C probe frame epilogue; post-throw
C SP equality is not asserted. Normal-return stack checks stay strict, and the
bridge always restores its own saved stack/C environment. No expected-result
normalization is added for platform or test differences.

Frozen proof:151 captured source/header/adapter inputs in input-hashes.json;
generic TELEPORT_REFERENCE_TU support-only syntax passes without original
allmain.c visible (shared-support-proof.log). Prepared source SHA256
`6ce44a662ad3d180b9dcbf7660a1899b8d1356c8ef83e7787b21b39c6b2a35e4`;
reference Wasm `e87154e547c510f7f5ca777601e00d3260577b71ae38c6c071015f59f058b24f`;
hybrid Wasm `7a8dcffa4fe6f45609cc2a2f4fd96c1114646b2c4197f551a4d6dd05219d1185`.

Scoped fixture correction: the duplicate ;flags: snapshot third slot now uses
%ld for actual long64 u.usleep (previous %d truncated it). Four independent
raw-snapshot witnesses retain2147483648,-2147483649,9007199254740997 and
-9007199254740997 in each actual C/JS Module, adding12checks. Production core,
runtime, binding and support remain unchanged. Both negative controls are
revalidated with the corrected fixture; source guard enforces the exact format.
Earlier4,963 artifact hashes are historical; current hashes above are fresh.
