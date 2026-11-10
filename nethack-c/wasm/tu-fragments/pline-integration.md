# PLINE handoff — first pass, not production promotion

All **31 configured original functions** are in `js/ported/pline.js`, in source
order with original parameters. Each of the19 original variadic functions keeps
its named `...the_args` binding. Five original private functions are preserved;
C-only test aliases are separate imports. No original PLINE algorithm is left
in production C. Prepared pline.c is currently byte-identical to pristine; the
source-data guard rejects a provenance change. Headers/platform flags remain
the current prepared game's documented configuration.

Owned files:

- js/ported/pline.js and pline-runtime.js
- nethack-c/wasm/tu-libraries/pline.js
- nethack-c/wasm/tu-fragments/pline-support.c, pline-source-data.h,
  pline-source-check.mjs, this document
- scripts/tu-pline-probe.c, tu-pline-layout.h, test-tu-pline.mjs

## Exact shared integration recipe

Registry (reference selected to match the probe's actual prepared include):

    {"name":"pline","source":"src/pline.c",
     "javascript":"js/ported/pline.js",
     "library":"nethack-c/wasm/tu-libraries/pline.js",
     "reference":"prepared","configuredFunctions":true}

Runtime: import `createPlineBridge` from './pline-runtime.js'. Inside
createPortedRuntime, instantiate `const callPline=layouts.pline ?
createPlineBridge(layouts.pline) : undefined;`. Returned entry:

    pline(services,name,...args) {
        if (!callPline) throw new Error('Missing PLINE layout');
        return callPline(services,name,...args);
    }

The bridge already scopes C and saves/restores the ABI stack in finally. It
maps the monster parameter, preserves signed64 long parameters, and wraps the
last incoming argument of every variadic public entry as an opaque va_list
packet. Do not flatten that packet into JS values or cast it to32 bits.
Non-variadic private vpline/vraw_printf test entry arguments are also handled.
Use one bridge per runtime; WeakMap state is keyed by Module and tested across
several actual modules using the same bridge. Private in_pline and
use_pline_handler are JS state, initialized0/TRUE exactly once per module.

Include `#include "tu-fragments/pline-support.c"` once in game tu-support.c.
The helper includes its exact source-derived data header from its own directory.
No startup callback. gy.you_buf and all history/log state stay in the actual
shared C globals; original functions own all allocation/reuse/free decisions.
Exclude pline.o through the registry and link this JS library. Actual-game
private test aliases should be dead-stripped; audit their absence after link.
The source guard `node nethack-c/wasm/tu-fragments/pline-source-check.mjs` belongs
in the integration/build check alongside the other TU data guards. Source hashes
must include core/runtime/library, helper, metadata/data headers and checker.

Probe exports (`_probe_` prefix, plus malloc/free):
`caps reset clear option field input argument trace snapshot message direct
context_size stack layout_count layout_name layout_value`.

Both probe modes compile ONLY scripts/tu-pline-probe.c with current
compile-defines.json, memory64, and forced native-terminal.h, matching the active
ABI. The probe includes the PLINE helper itself; do not link main tu-support.c
as well. Reference adds TELEPORT_REFERENCE_TU and includes prepared pline.c
itself; add pline to the builder's source-inclusion list to avoid adding that C
file twice. Hybrid links its JS library and never compiles pline.c.

Both modes redirect `fork waitpid getgid getuid setgid setuid execv perror
fprintf free` with `-Dname=teleport_probe_name`. The fixture locally undefines
free only around its actual allocator release; translated free uses a typed C
helper so the same fixture sees frees. Controlled child/panic/termination uses
EM_JS exceptions, so no real process handler is executed. The current fixture
needs a native-compatible exit adapter before native-addon execution.

Layout writer: flat dictionary of `_probe_layout_name/value` across
`_probe_layout_count` as layouts.pline; there is no separate strings table.
DEVTEAM_EMAIL is a typed C macro-string getter. WIN_MESSAGE is its actual live
winid global. All global-field widths, coord/monster/gamelog layouts, private
buffer bounds, source constants and feature branches come from C metadata.
Gamelog flags and turn are both original **signed long64**, not unsigned.
Window capability word is **unsigned long64**, masked as BigInt in JS.

## Varargs and source-preserving representations

Source public `...the_args` receives an opaque marker representing the actual
compiler-created memory64 packet, not the host JS rest array's bytes. The
single-%s fast path loads its first pointer directly from the checked SDK ABI.
All other external formatting goes through typed `vsnprintf` with the original
packet. That helper calls only libc and contains no PLINE algorithm. Source
internal calls have only four original format shapes; their exact strings/
strings/int are passed by a guarded typed snprintf helper. No general JS printf
parser or guessed integer packing is introduced. The current pointer va_list
ABI is guarded by C sizeof and runtime features; Native va_list layout/packing needs independent verification and any necessary
transport adaptation later, not an expected-pass exception.

Original YouPrefix/YouMessage macros expand inside their original owning
functions.13 expansions retain source literal sizeof lengths and evaluation
order. The source checker checks them and rejects a deliberate size mutation.
Three BIGBUFSZ arrays, gamelog's2*BUFSZ array, QBUFSZ/BUFSZ temps and handler's
three-pointer array stay ABI-stack temporaries. The original forward
pline_done gotos are breaks from a labeled block, with one original decrement
at the end. Accessibility coord assignment copies fields rather than aliasing
its mutable global view. All original active block comments remain at their
source positions; inactive platform comments are retained in a footer.

The exact36 source strings require563 bytes of zero-only static ABI storage;
source-derived allowlist and capacity guards reject drift. No arbitrary pool
or allocation is introduced for literals. Macro/property views obtain fresh
memory after callbacks grow the heap. There are no original RNG sites.
SoundSpeak/USER_SOUNDS/SPEECH-specific behavior is compiled out in this actual
configuration and rejected if enabled; no additional sound support is claimed.

## Evidence and outstanding gates

Isolated recipe `.cache/pline-first-pass/build.py` builds -O2 reference/hybrid
memory64 modules. `.cache/pline-first-pass/build.log` and `test.log` record:

- **1,620** configured Emscripten-C/JS comparisons pass.
- Real C variadic packets:19 public wrappers, mixed string/int/long beyond53 bits/
  float/precision/width/hex/pointer formatting, literal percent and raw byte data.
- Ring wrap, unknown-command exclusion, grow/shrink/reuse/free ownership; all
  sensory prefixes, directional/xy/monster accessibility prefixes and signed
  coordinate narrowing; suppression/history/urgent/override/cursor flags and
  unsigned64 window capabilities, including bit63.
- Original truncation with tail preservation versus raw truncation; controlled
  oversized pline panic; original two early_raw_messages increments;
  gamelog/livelog signed64 flags/time and tab replacement; impossible/report
  feedback, developer/local support, and original error/assert paths.
- Actual heap growth during putstr, UI and vision C→JS reentry, normal stack
  restoration and environment cleanup, several actual modules sharing one
  bridge, controlled handler parent/fork-failure/child exec/termination paths.
- Wasm import audit:29 original public/private C entry points are real JS
  imports. The two other private bodies (vpline/vraw_printf) execute within JS.
- Inventory/order/parameters/all block comments and lexical checks pass using
  existing checker logic restricted to this one staged port. No parameter-name
  exception is required. Source-data checks and syntax checks pass.

The fixture controls outside-world dependencies; its strNsubst implements only
the actual one-byte tab-to-underscore call shape, and production uses the real
existing HACKLIB dependency. Header-property macro evaluation stays in typed
helpers. No native equality, actual mixed game link, real handler child process,
public replay, or whole-game behavior is claimed. Those remain integrating
owner gates. Native libc formatting/va_list differences must be reported and
fixed explicitly later under the current first-pass staging instruction.
