# Shared JavaScript C runtime

This directory owns reusable C mechanics. The first extraction is memory
transport, used by the standalone provider through its compatibility entry.
It is not yet the complete runtime and does not replace the mixed backend.

## Boundaries

- `memory.js`: numeric addresses, scalar widths, allocation, stack scopes,
  literals, measured record/array views and byte copies. It accepts declarations;
  it must not import NetHack modules or know game field names.
- `../nethack/rect-bindings.js`: the measured NhRect declaration, module state,
  source diagnostics and legacy names required by the unchanged RECT port.
- `../standalone/memory-services.js`: compatibility entry adding NetHack typedef
  aliases (`boolean`, `coordxy`). Existing callers retain their interface.
- `../standalone/environment.js`: composition, registration, RNG injection and
  dependency ownership. It delegates RECT declaration/binding to NetHack's layer.
- `../ported/rect.js`: unchanged source-shaped algorithms. Explicit operations
  that represent C semantics remain visible in translated bodies.

The pre-existing byte allocator remains in `../services/c-memory.js`. The
pre-existing synchronous dependency scope remains in `../ported/c-runtime.js`;
this extraction does not change scope, callbacks or reentry rules.

## First reusable declaration binding

After `defineRecord(name, measuredDefinition)`, `recordType(name)` resolves the
schema once and exposes `size`, `view(address)`, `array(address, length)` and
`local(fieldValues)`. Views remain live across memory growth; array record
assignment copies bytes. A local reserves scoped stack storage, with no implicit
initialization. Optional field values are assigned in declaration order through
typed setters, preserving RECT's previous behavior. This is field initialization,
not a general implementation of arbitrary overlapping struct assignment.

No view escapes its underlying allocation lifetime safely merely because it
is a JavaScript object. Addresses, pointer aliases and explicit ownership remain
part of the port's contract. Invalid accesses do not acquire defined C semantics.

## Incremental follow-up

1. Use unchanged component comparisons to migrate additional declaration
   bindings, retaining existing import paths until consumers have moved.
2. Inventory and consolidate the other record projections against an explicit
   common contract: nulls, array bounds/one-past pointers, object identity,
   embedded records, copying, bitfields, readonly fields and lifetime. Their
   current contracts differ; they have not been silently unified here.
3. Generate repetitive NetHack bindings from existing measured metadata; keep
   translated header macros/game decisions with NetHack, outside this runtime.
4. Consolidate libc/callback/linker mechanics in separately testable steps.
   Inject terminal, filesystem and time at the platform boundary.
5. Retire production Wasm bridges after complete pure-JS game acceptance.

## Validation for this extraction

Use the configured Node runtime. `test-c-runtime-memory.mjs` needs no C oracle.
The existing `test-standalone-environment.mjs` reads RECT's original C oracle
from `STANDALONE_REFERENCE_ROOT`; it passes all 1,190 state comparisons.
Existing TRACK (3,496 comparisons), terminal (445 comparisons), and isolation
checks also pass. Isolation forbids Wasm/network production capabilities.

The full scope/provenance guard is blocked by an existing absolute-path pin for
`runtime-environment/js/standalone/stdio.js`: actual `051933cd…`, expected
`65866af8…`. The unchanged HEAD guard reproduces this before traversing the
production imports. No pin was refreshed or disabled. Therefore no complete
regression-gate, full-game recording, performance or native-host acceptance is
claimed for this cleanup.
