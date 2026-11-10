### PAR08-TELEPORT — frozen isolated first-pass implementation (TU95/J101)

Scope was announced/documented before edits. All37 actual configured functions
(28 public,9 private) retain original names/order/parameters/block comments in
`js/ported/teleport.js`; `teleport-runtime.js`, the typed JS library, layout,
teleport-support/source-data/ABI metadata, controlled C probe and differential
test are the unique associated artifacts. No shared registry/builder/layout
writer/common support/central runtime/production artifact or frozen port was
edited by this author; integration remains owner-controlled. Completion text is
provided here for the integration owner's atomic register append, honoring the
current no-shared-writes instruction.

Prepared/pristine src/teleport.c are identical2,294 lines, SHA256
`e1d9d4255ac148caa4618dc4f275ddf5417d2a2830beca738c3821cf7678e5c8`.
The actual reference is the prepared memory64 Emscripten production profile with
compile-defines.json, forced native-terminal.h and ncurses headers, production
cwd TREE/src input basename teleport.c. PRIVATE reference-fixture macro-prefix
mapping aligns its absolute include spelling to that actual production basename;
full filename/closing-line/function RNG traces are compared, never basename-only
normalized. No production compiler flag was changed.

JS owns NEW_ENEXTO collection/shuffling/search/goto/control, source tports4 table,
static get_there_from19 and per-Module trap recursion guard. Native backing is
typed automatic storage and exact-source-corpus zero-only static byte storage;
C exposes header/field/dependency/function-pointer/varargs ABI, not TELEPORT
algorithms or initialized data mirrors. Canonical live address wrappers preserve
monster/object/level/stair aliases; C widths include signed16 coordinates,
signed8 booleans, unsigned32 flags and actual signed/unsigned64 fields. Observed
C logical values are canonical0/1. Header debug timing was corrected before
freeze: debugcore→save last_msg→lazy args→typed print→restore only on normal
return. An independent read-only review found no further concrete issue, and the
actual C callback mutation case rejects the old eager adapter. No #line state
leaks into later common-support fragments.

Fresh -O2 -g original/hybrid links pass2,910 unchanged-oracle comparisons; all37
bodies andall22 RNG sites execute. C snapshots/consumers read actual native
buffers/scalars,64bit fields, coordinate tails and zero-monster bytes including
padding. Cases cover geometry/RNG/filter/iterator/window callbacks, growth,
reentry/live callback replacement, menus/static data, both Modules sharing one
bridge, traps/guard persistence after throw, prompt/goto paths, long timeouts,
controlled inventory/billing/revival, repeated buffers and stack restoration.
The hybrid imports all37 JS source bodies and actual compiler dependencies
exclude original teleport.c; reference imports none. Source/order/parameters/all
comments, lexical scope, fresh CPP/profile/signature/linkage,1108 MemberExpr/type/
member-macro alias records, source literals/table/static data and exact22 origin
guards pass. Generic-reference support-only syntax passes without private source
scope. TELEPORT_NATIVE_TESTS=1 rejects before Module creation.

Two negative controls fail the unchanged C suite: discarded collect_coords RNG
fails configured enexto full trace; eager debug arguments fail debug macro
argument ordering full trace. No original/expected output, comparison granularity
or failures were normalized, waived or amended to pass.

Evidence/recipe: `nethack-c/wasm/tu-fragments/teleport-integration.md` and
`.cache/teleport-first-pass/{test.log,source-data.log,build.log,import-proof.json,
negative.log,negative-debug.log,negative-summary.log,input-hashes.json}`. Final
reference Wasm SHA256
`4de730a8e5db5afcdc7d697e1667d8e4fbf5e9a7574201b63151361fa9572c94`;
hybrid `8092dac0f065efc41a5d8b39f6b6a895726112aba34de734e246c142fccdf6d9`.
Clang -O2 is active; -g causes the compiler's documented limited Binaryen postlink
optimization warning. Earlier no-g -O2 passed the then-current2,220 checks; that
smaller historical run is not the expanded final corpus.

Limitations: isolated Emscripten-C first pass only. Native-macOS/full-game/public
TELEPORT acceptance is pending. Foreign UI/placement/room/spell/AI/death/shop/
level/object effects are controlled fixtures; no real OS UI is sent, traps/
objects use static fixture storage, and actual world deallocation/complete world
integration/all branches are unverified. Callback-throw tests establish original
persistent guard semantics, not arbitrary C nonlocal-exit cleanup parity. No
pristine-native equivalence or full playable-world support is claimed.
