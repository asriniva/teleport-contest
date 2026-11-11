# Extend the JavaScript C environment

Historical implementation plan, 2026-11-10. The original inventory below is
retained at its starting revision. See [README.md](README.md) for the implemented
checkpoint, current evidence and remaining integration work. This plan's full
game completion criteria have not been met.

## Baseline and findings

Worktree: `/Users/arj/Desktop/nethack_comp/runtime-environment`, branch
`runtime-environment-plan`, starting at `ddc6f24e62924f846ed9f847dfb87b1791c3113d`.
The live checkout has ongoing uncommitted repairs. They were not copied or
modified. `baseline.json` records differing inventoried inputs (calendar,
LIGHT adapter, MON policy, and shared Wasm runtime). Before implementation of
each affected area, review those repairs and bring over the relevant completed
change explicitly; do not accidentally resurrect this checkpoint's known MON
defect or conflicting platform behavior. The baseline is not a claim that the
current live artifacts match these sources.

The existing `js/ported/js-runtime.js` is a small provider for allocation,
strutil, MD4, calendar, regex wrapper, and a redundant ISAAC translation. It
owns an ArrayBuffer allocator and an independent CVFS. Its libc is a bounded
subset. This establishes useful machinery, not game-wide runtime coverage.

The AST inventory covers all 137 game registry entries and 131 `*-runtime.js`
files, binding 272 input files by SHA256. The registry includes ISAAC64's
historical source: the game already uses the frozen generator, so 137 entries
must not be described as 137 newly implemented algorithms. Standalone utility
profiles are outside this initial game-registry inventory.

Among conventionally named module adapters, 125 request a heap, 109 request
global storage, 97 request stack allocation, 92 request stack save/restore,
68 request instance identity, and 62 request literal strings. These are direct
AST references, not missing-feature counts. Many services already exist inside
adapters; some adapters have other filenames or reside in wasm-runtime.js.
Dynamic member access, aliases, helper dependencies and cycles need further
resolution before declaring any module supported. See `inventory.json`.

## Implementation rules

- Preserve translated NetHack policy bodies. Put transport and environment
  changes in providers/adapters; document every behavioral divergence.
- Use frozen `js/isaac64.js`, `js/storage.js` and `js/terminal.js` contracts.
  Replace the standalone runtime's redundant ISAAC import with an adapter to the
  supplied generator. Retain exact seed, state and RNG logging behavior.
- Keep explicit C memory semantics for these source-shaped ports. Replacing
  pointers with unrelated JavaScript objects would break aliases, struct copies,
  pointer-to-pointer output arguments and serializers.
- Reuse existing module adapters when they are independent of Wasm. Expose
  `heap()` and an opaque per-instance identity where an adapter currently calls
  it `moduleKey`; this identity need not be an Emscripten Module.
- Separate runtime primitives from game dependencies. `makemon`, `canseemon`,
  map access, messages and equipment are not libc. Route them to their real
  translated owners. Fail explicitly on an unresolved dependency; never supply
  success-returning placeholders to claim coverage.
- Choose the compiled reference profile explicitly. Current native-Darwin and
  Emscripten behavior differ in time, formatting, regex, sort, signal and tty
  details. Preserve both comparisons where appropriate; do not silently carry
  Darwin defaults into the configured Emscripten game target.

## Stages and completion criteria

### 1. Make the provider compatible with existing adapters

Add a common services facade around CMemory: fresh heap views, integer/pointer
loads and stores, explicit signed-width conversions, stable literal allocation,
scoped temporaries, and nested `stackSave/stackAlloc/stackRestore` semantics.
CMemory already supplies allocation, copying and growth; extend it only for
actually missing contracts. Stack lifetime must survive nested calls and unwind
on exceptions without freeing persistent allocations or other instances' data.

Add a layout/record service for arrays, nested records, unions, pointer cells,
whole-struct assignment and overlapping fields. Reuse measured layout/schema
data and existing adapter validation. Bitfields currently read/written through
C helpers require explicit measured bit locations/masks, not guessed offsets.
Record views must consult current memory after growth, preserve nulls, aliasing,
signedness and by-value snapshots. A shared record service can be introduced
incrementally rather than replacing every existing adapter at once.

Use a reproducible, compiler-measured schema export as development input;
production must consume checked-in data without a compiler or Wasm. A claim to
support a profile requires its sizes, alignments, offsets and bit masks to be
verified against original C, not merely copied from another platform's numbers.

Acceptance: genuine C layout/byte witnesses; aliases, struct copies, overlapping
fields, truncation, pointer output cells, heap growth, nested cleanup and two
isolated instances. Canonical ISAAC seed/draw/state comparisons must remain
exact; no independent generator algorithm in the standalone execution path.

### 2. Expand libc and wire smaller modules

Inventory actual missing calls rather than attempting all POSIX libc. Add the
needed scanning, varargs/format packets, numeric conversions, byte-string APIs,
errno propagation and comparator callbacks. Existing formatting code rejects
some formats and defaults to Darwin float policy; select and verify the target
policy explicitly. C qsort callback order and ties are observable in current
tests, so a generic JavaScript sort is not automatically equivalent.

Start with dependency-small modules: rect, drawing/date initialization, rnd,
then hacklib and track. This is an ordering proposal, not a support claim:
rect needs coordinate views, scoped locals and canonical rn2; rnd needs its
real per-instance state and logging I/O; hacklib needs the comparator/varargs
contracts; track's full API also needs hero/equipment state and serialization.
Enable only complete exported surfaces, or explicitly label any tested subset.

Acceptance: unchanged policy functions called through the new provider, outputs
and mutated bytes compared with original C, including failures. Resolve all
reachable dependencies for each enabled surface before adding a coverage mark.

### 3. Own static data and game globals

Allocate and initialize declarations, catalogues, symbols, flags, hero state,
map cells and linked object/monster records in JS-owned memory. Existing DECL
packing and module initializers are reusable starting points. Replace native
`global`, `storage`, `data`, getter/setter, catalogue and bitfield helper access
with actual JS storage and source-derived initializers.

Build a module registry that resolves translated function owners and startup
hooks, including cycles. Initialize shared data before consumers, preserve
one-time initialization and reset semantics, and preserve static addresses.
Group interdependent modules (objects/monsters/hero/map) rather than pretending
they can each be enabled by adding another libc function.

Acceptance: original initialized byte images/values, pointer relocations, state
mutation across module boundaries, repeated initialization, reset and independent
game instances. No native backing global or hidden Wasm helper may remain for
a surface claimed to run independently.

### 4. Replace function-pointer and nonlocal-control transport

Implement per-instance function IDs, signature-aware callbacks, indirect calls,
varargs packets and reentry using the real translated functions. Preserve ID
identity where it is compared or stored in structures. Port remaining C macro
helpers only where they implement required behavior; do not reimplement game
algorithms as provider shortcuts. Model setjmp/longjmp/error/termination scopes
with targeted unwind behavior so unrelated JS errors are not swallowed.

Acceptance: direct/indirect parity, nested JS callbacks, error unwinding,
callback registration lifetime, two instances, and no native function table.

### 5. Integrate file/stdio and serialization

Connect C pointer-backed buffers and FILE/descriptor services to CVFS. Add the
actually required fread/fwrite/fgets/fprintf/seek/EOF/error/flush operations,
descriptor ownership, close rules and errno semantics. CVFS's existence alone
does not supply these C ABI services. Preserve actual binary bytes and deletion
through the frozen storage contract; reuse compression and game-files services.

Wire sfbase/sfstruct procedure tables, record serializers, track save/restore,
then save/bones/restore dependency groups. Preserve format bytes and relocation
rules; do not serialize raw JS object graphs or assume allocator addresses match
native addresses. Data assets must be injected, not read from the host filesystem.

Acceptance: original C binary outputs and failure statuses, EOF/seek/short I/O,
ownership, save/restore round trips, deletion, chained sessions and bones.

### 6. Attach Lua, terminal, input and the game loop

Reuse JavaScript Lua, regex, terminfo and compression algorithms. Adapt their
memory, callback, allocation/error and userdata boundaries to this provider;
their existing Wasm bridges are not proof of JS-owned-memory integration.
Bring nhlua/nhlobj/sp_lev, window procedures, tty transport, command/input and
allmain through the same dependency registry. Audit any remaining unported C
callee separately: a JS environment cannot supply missing NetHack algorithms.

Keep terminal capabilities, byte transport, recorder shadow capture, terminal
emulation and snapshot encoding separate. Preserve the reference recording
behavior and frozen Terminal contract; do not introduce a new renderer or
screen conversion as an incidental runtime change.

Acceptance: no production Module/WebAssembly/native/host-filesystem dependency
on the enabled path, actual original level loads, callback/error probes and
full unchanged integration/public gates under original time limits. Browser
execution requires a separate browser check before claiming it works.

## Validation and reporting

Keep a per-module ledger with: declared exports, layout/profile identity,
required services, translated owner of each game dependency, unresolved native
edges, test evidence and status. Distinguish inventoried, callable subset,
fully independent component and full-game accepted. The generated AST inventory
is the input to that ledger, not an execution or closure proof.

Development C oracles may use the pinned compiler. Production JS must not load
those artifacts. Add meaningful tests for memory, byte-layout and cross-module
behavior as each stage lands. Reuse original fixtures/expectations; include
negative checks that would catch a native fallback or a missing dependency.
Run full game gates when a coherent runnable path exists, not on every small
provider edit. Component passes never imply recording equivalence.

First implementation batch: services facade + stack/record foundations,
canonical ISAAC wiring, and rect as the first additional complete component.
Then expand in the order above based on measured closure. This plan does not
promise that one provider patch can run all 137 entries.

## Reproduce the inventory

Run `scripts/inventory-js-environment.mjs OUTPUT.json` with the pinned SDK's
Node, setting `EMSDK` to its location. The script reads Acorn from that SDK;
it neither compiles nor changes the SDK. Compare a fresh output byte-for-byte
with `inventory.json` when the audited sources have not changed.
