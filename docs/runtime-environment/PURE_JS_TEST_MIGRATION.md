# Subsystem tests on pure JavaScript

All 138 registered subsystem test entry points select the pure-JS implementation.
All 138 suites passed against original C with Wasm unavailable to the JS
implementation. The [validation receipt](pure-js-test-validation.json) records
the full cohort and successful targeted reruns for five repaired suites, including
the earlier failures. The final results contain 19,509,153 assertions and zero
assertion failures. No recorder or scoring run belongs to this command.

Run all subsystem tests with `npm test` (`test:native` is an alias), or select names with
`npm run test:pure-js -- light nhlua`. This builds fixtures and runs the original
cases against original C. Corrected CMD, OPTIONS, UHITM, TERMCAP and WINTTY
reference fixtures are rebuilt from their original reference recipes when needed. The configured SDK compiler, Node and existing C
reference builds must be present in `.cache`; this is a development test setup.

The implementation process denies WebAssembly, fetch, Worker, WebSocket and
XMLHttpRequest before importing the tests, and guards each implementation call.
Swallowed forbidden-capability attempts also fail. Native original-C addons
serve as references where their platform contract matches the fixture. Other
original-C references run in separate processes; those processes can use Wasm.
The implementation cannot call reference helpers or use reference memory.

Eighteen fixtures use handwritten JS setup. The other 120 lower only the
existing C test setup and typed ABI helpers to ordinary JavaScript offline.
Their dependency files reject game-engine and Lua-library C implementation
sources. All game policies execute the production JS translations; memory,
libc, stdio, files and Lua execute JS providers. Missing services throw.
Generated source/input/output hashes are checked before loading each fixture.

The original cases, assertions, callback/reentry checks, growth checks and state
comparisons remain. Fixture and observation adaptations remove invalid assumptions:

- CFGFILES supplies the required OPTIONS delimiter in four direct helper inputs.
- MONMOVE gives its corpse a valid species, avoiding `mons[-1]`, and adds a
  small-corpse case.
- PAGER uses a valid monster species for its monster-disguise cases.
- DUNGEON, PICKUP, SP_LEV and CMD canonicalize pointers against live allocations, retaining all live
  bytes and allocation lifetime checks when allocators reuse different addresses.
- MKMAZE gives both engines the same scalar equal to a reference address, so its
  pointer-normalization negative control works across different heap layouts.

- UHITM initializes the object name required by its named-object case; OPTIONS
  supplies its controlled string callback instead of returning NULL to `strcpy`.
- CMD's controlled string-substitution fixture returns its declared buffer pointer,
  and its floodfill trace compares callback identity across different function tables.
- TERMCAP and WINTTY distinguish internal terminal-library calls from direct
  game-policy calls in their dependency observers.

Large ROLE, MKOBJ, BOTL, ARTIFACT, HACK and CMD reference snapshots run the
existing observer inside the original-C child, returning the same bytes and fields
in one message. The implementation receives no reference services or memory.
Getter caching applies only to typed read-only ABI helpers; effectful reads such
as REPORT's file read are excluded and mutations invalidate cached observations.

BOTL uses Node `--jitless` for its large lowered fixture. Its complete cases and
assertions execute, and the reference child uses normal Node. Production runtime
settings and JIT performance are outside this fixture profile.

Growth helpers replace geometric test allocations with real 16MiB heap growth.
The original growth assertions still require buffer replacement. Expected-failure
assertions still throw inside their callbacks; aggregate recovery cannot swallow
the deliberately triggered failures.

SFSTRUCT uses the original SDK C reference because its cases compare exact
private descriptor numbers. END retains its original SDK signal profile because
the composed native-header profile collides with function-table tokens. These
are explicit reference contracts, not native-host parity claims.

The 640 generated selection scenarios and negative controls use the same JS
implementation. `test-tu-light-mixed-diagnostic.mjs` remains an explicitly named
legacy diagnostic. Mixed-engine results do not establish pure-JS readiness.

Passing this subsystem corpus does not establish full-game readiness. Existing
controlled-world coverage limits and the upstream selection unary-alias
use-after-free remain explicit. The 44 recorder sessions have not been run.
Historical source pins remain unchanged; exact reviewed migration patches and
current-source execution receipts qualify the new sources separately.
