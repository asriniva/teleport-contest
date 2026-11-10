# TU120/J126 APPLY private handoff — not selected

Replace only the actual configured `src/apply.c` translation unit. Its prepared and pristine source are byte-identical (SHA256 `3599e3ce2ea7ce4dac10730dc1a5496114a363dc951d5c1f0289a8575b40e24b`), 4558 lines/155854 bytes. The JavaScript keeps all 76 original function names, formals and order (28 public/48 private), all 371 comments byte-exact and in original order, all 13 immutable static initializers including `fadeness[5]`, and the configured algorithms. Original NetHack licensing notices remain in the source.

This author changed only APPLY-specific files and `.cache/apply-author`. No shared registry, selected game, build, READ109, MAKEMON101, END92 or Lua82 change is part of this handoff. Parent maintains the shared divergence register. Initial read-only scope is bound by `.cache/apply-author/pre-edit-handoff.json` (SHA256 `af5a9485117c83615647bd0a57fc20ef4d1ed2187ce3129c8ea0a1f16fd967e7`). Its 320 foreign-callee roots include `windowprocs`, an indirect call root: the precise inventory is 319 distinct direct FunctionDecl dependencies plus configured indirect window callbacks.

## Unapplied integration recipe

1. Add an `apply` entry to the TU registry: C source `src/apply.c`, JavaScript `js/ported/apply.js`, library `nethack-c/wasm/tu-libraries/apply.js`, `configuredFunctions: true`. Preserve existing profile and function selection rules.
2. Include `apply-support.inc` in the typed bridge, with the same actual prepared headers. Include `scripts/tu-apply-layout.h` and expose its `apply_layout` rows as signed 64-bit layout transport. It describes 56 canonical records, 40 globals and 34 bitfields. `APPLY_META` values are existing compiler-derived constants, sizes, offsets and array strides; no game decision is implemented in C.
3. Import `callApply` from `js/ported/apply-runtime.js` and add exactly the method in `apply-runtime-method.inc`. Bind `layouts.apply` to those actual layout rows. There is no startup hook or synthetic world state.
4. Exclude only `apply.o`; retain true foreign TUs, native object/monster catalogues, globals, headers and APIs. All 76 APPLY bodies remain in JavaScript. Typed C forwards call only actual foreign APIs/window function pointers or pass source callback identities; there is no original APPLY body or native APPLY policy fallback.
5. Check actual linked Wasm imports: no `_test_` APPLY import is permitted. The production support references only `teleport_apply_callback_*` for private source callbacks and actual public symbols. Private `teleport_apply_test_*` library aliases exist solely for controlled direct-entry fixtures.
6. Preserve production compilation cwd `TREE/src`, basename `apply.c`. RNG metadata passes the original `apply.c` filename/line/function; native fixture uses an exact directory-to-empty prefix map solely to match production filename spelling. No output basename normalization is allowed.

## Exact transformations and native boundaries

- C automatic buffers, arrays, records, scalar references and object-pointer cells use actual native stack storage with frame restoration. `&cc.x`, `&cc.y` and `&HBlinded` retain real writable native aliases. Struct copies preserve native target identity. Canonical typedef resolution decodes `stairway*`, object/monster/permonst/attack/trap pointers and `anything*`; opaque addresses stay raw.
- Actual header aliases include `oc_skill`/`oc_armcat` → `oc_subtyp`, `doormask` → `flags`, `ocarry` → `v.v_ocarry`. Runtime record access is strict. Views cache by canonical type/address within an invocation and refresh heap views after native memory growth. Each Module owns native globals and literal storage.
- Actual configured header expression macros are readable JavaScript. Property-width and monster flags use native 64-bit integers. C integral divisions truncate correctly; 24 stored/returned logical-expression sites produce C 0/1. Source-local `HowMany`, `TimedTrouble`, `prop_trouble` and glyph predicates preserve their definitions. `Soundeffect`, `SetVoice` and `Hero_playnotes` erase arguments as actual CPP does.
- `Maybe_Half_Phys` checks the property before evaluating its damage argument, including RNG. `rn1` evaluates RNG before its offset. Caller metadata is attached before argument evaluation at original token positions, including nested `rn2(d(...))` and duplicated conditional macro arguments. There are 73 active original RNG calls, represented by 72 distinct line/function pairs (one nested pair shares a line). The one disabled `rn2` is retained only inside original inactive comments/history.
- The source `useup_jelly` forward jumps exit a labelled block into one original tail. `whipattack` uses a three-valued local CFG dispatch to preserve the one original attack body and the no-monster tail in original order. This adds no new game decision. All 371 original comments remain in original order.
- `go.occupation == set_trap` compares the actual native function-pointer identity. All 16 owned function-value targets have real typed production callbacks; 7 additional foreign function-value targets retain native identity. Native helper functions contain typed field/bit/global/callback/varargs/window transport only.

## Evidence and limits

The private original-C reference and imported-JavaScript memory64 fixture each compile without original APPLY bodies in the hybrid. The independently linked production projection also compiles. Current controlled gate: **9183 exact original-C/hybrid comparisons**, all 76 entrypoints reached; **104 production-projection comparisons**, zero `_test_` imports; all 16 owned callback targets actually invoked indirectly by typed C with matching native function-pointer identity.

The cases include the actual object catalogue through five selectors and `doapply`, tool/blessing/charge/seed paths, 64-bit properties, unicorn-horn nested RNG, physical jump traps, two property-before-RNG cases with a C RNG fixture that changes the property inside the argument, real object-pointer replacement, occupation comparison, coordinate/path aliases, pole candidates, 27 typed record-return adapters, native pointer alias/cache identity and native-write rereads, legal nullable return cases, synchronous reentry, actual native heap growth, separate Modules and controlled C longjmp with stack/environment restoration. These are controlled foreign-world fixtures, not full foreign algorithms or complete branch coverage.

`mksobj` keeps its actual ReturnsNonNullAttr; no artificial NULL return is supplied to it. Known non-null or uncertain postconditions are positive-only cases. `activate_statue_trap` receives a real non-null trap argument. An earlier invalid fixture NULL-argument warning/source is retained as explicitly invalid history, not proof. Eleven mutable memset target types were recursively audited to exclude true const subobjects; original const initializers are retained. Ten format-nonliteral warnings are the existing typed varargs forwarding diagnostics; no nonnull or incompatible-type warning remains in the final builds.

Guards compare the actual full configured AST bodies/types/literals, exact prepared/pristine source, function/formal order, all 371 comments, 13 actual C static initializers and aliases/RNG metadata. Readable source regeneration and lexical scope pass. A read-only loader swaps only two JS fadeness entries; the unchanged original C gate rejects it, without changing source, oracle, built artifacts or expectations.

**Still pending:** native-host validation, a shared full-game candidate, unchanged public recordings, complete branch coverage, production allocator-failure schedules, every possible callback reentry point and actual OS/window/foreign engine boundaries. Controlled fixture exits/unwinds never exit the real host process. No full-game or native-host equivalence claim is made.

## Reproduction

Use the bundled Node executable at `.cache/emsdk/node/24.19.0_64bit/bin/node`.

- `python3 nethack-c/wasm/tu-fragments/apply-metadata.py`
- `python3 .cache/apply-author/storage-audit.py`
- `node .cache/apply-author/scope.mjs`
- `python3 .cache/apply-author/build.py reference hybrid production`
- `node scripts/test-tu-apply.mjs`
- `node .cache/apply-author/production-projection.mjs`
- `python3 .cache/apply-author/run-negative.py`

Private generators, captured raw failures, command lines, build logs and successful input hashes are bound in `apply-hashes.json`. Historical failed/invalid attempts are evidence of investigation, not passing gates.
