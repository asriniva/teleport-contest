# TU128/J134 UHITM private handoff — not selected

This replaces only the actual configured `src/uhitm.c` translation unit. Prepared and pristine source are identical: SHA256 `4cc2f8a0ffe0121801a777978a9a555a063db720e0fe972308fb6ab0e96feb12`, 6447 lines/240440 bytes. All 102 original body names, formals and order (65 public/37 private), all 783 comments byte-exact and ordered, all six static declarations/initializers, and configured source algorithms remain in JavaScript. The original licensing notices remain. Initial read-only scope is `.cache/uhitm-author/pre-edit-handoff.json`, SHA256 `0a30d4428cba0e546d7efb3ca323bc302f6de6643dfdf19116c261c326bff816`.

Only unique UHITM files and `.cache/uhitm-author` are part of this author change. No selected registry/build/default/game, earlier frozen port, or Lua82 edit is included. Parent maintains the shared divergence register. This is an EmC first-pass handoff; native-host and selected full-game evidence are pending.

## Unapplied integration recipe

1. Add a TU registry entry `uhitm`: C `src/uhitm.c`, JavaScript `js/ported/uhitm.js`, library `nethack-c/wasm/tu-libraries/uhitm.js`, `configuredFunctions: true`. Keep the actual compilation profile/function-selection machinery.
2. Include `uhitm-support.inc` in the typed bridge with actual prepared headers. Include `scripts/tu-uhitm-layout.h` and transport its `uhitm_layout` rows as signed 64-bit layout values. There are 54 canonical records (including a sizeof-only `struct mkroom`), 46 live globals and 37 bitfields. Layout rows are actual compiler sizes, offsets, strides, types and existing constants; there is no C combat decision.
3. Import `callUhitm` from `js/ported/uhitm-runtime.js` and add exactly `uhitm-runtime-method.inc`. Bind `layouts.uhitm` to those actual layout rows. Do not add startup world initialization.
4. Exclude only `uhitm.o`; retain actual foreign TUs, native object/monster catalogues, globals, headers and window callbacks. All 102 original UHITM bodies execute in JavaScript. Native helpers provide typed calls/layout/fields/globals/bitfields/varargs/window transport/actual callback addresses and source-owned native storage only. They never call an original UHITM body as fallback.
5. Require zero `_test_` imports in the linked production Wasm. Private `teleport_uhitm_test_*` aliases exist solely for direct-entry fixtures; the separate production projection uses none. Its import audit positively detects those names in the hybrid build before asserting their absence in production.
6. Preserve production cwd `TREE/src`, basename `uhitm.c`. RNG locations use original `uhitm.c`, line and function. The fixture's exact directory-to-empty prefix map matches this production spelling; outputs are never basename-normalized.

## Source and lifetime transformations

- The actual CPP/AST contains 316 distinct true foreign FunctionDecl dependencies plus indirect `windowprocs`, 274 field/type pairs, 47 globals including TU-owned immutable `brief_feeling`, 33 automatic record/array declarations, and the sole pointer-arithmetic site `char *p++` in `do_attack`. Field macros resolve from actual headers; pointer-to-record typedefs are canonicalized before field access. `struct mkroom` retains real array stride even though the core only passes its address.
- Automatic records, arrays, writable scalar/pointer cells and addresses use native stack storage, restored on return/reentry/unwind. `&hmd->mdat`, `&hmd->dmg`, `&sum[i]`, `&uwep`, `&uarmg` and permonst double-pointer aliases remain actual native locations. Struct copies preserve target identity. Record views cache canonical type/address within an invocation and refresh heap views after native memory growth.
- Source-local persistent `clockwise`, `gulpum.msgbuf[256]` and `that_is_a_mimic.generic[10]` have Module-owned native storage; their initializers remain JS-owned. `gulpum.msgbuf` may escape and remain readable/writable after return. Literal storage and writable state are independent across Modules.
- Function-value targets `xname` and `Finish_digestion` keep actual native C identity; `rn2_on_display_rng` also uses its actual typed native callback identity. The three are foreign dependencies, not JS implementations of their bodies. Native C indirect invocation and stored after-movement callback execution are tested.
- Configured header expression macros remain readable JS. Erased Soundeffect/SetVoice/Hero_playnotes arguments remain erased. `rn1` evaluates RNG before its offset, `Maybe_Half_Phys` tests the property before its argument, and min/max preserve selected-operand repetition. In this source the active rn1 offsets and min/max operands introduce no hidden RNG argument. RNG token attribution precedes argument evaluation and preserves 158 distinct original line/function pairs, including nested/conditional expansions and display RNG.
- C stored/returned logical values are canonical 0/1 at 31 sites; 22 integral division sites truncate; actual native long promotions use BigInt. Unsigned32 `owt+99` wraps before dividing, `10-owt/10` narrows at the C int conversion, and unsigned `cwt>>8` zero-fills. The actual enum used is signed `monnums` with negative sentinel; no unsigned-long multiplication/division or pointer compound-assignment site exists here. Bitfield compound addition uses Clang's int compute type before native bitfield narrowing.
- Source gotos become labelled/dispatch CFG joins retaining one original tail. `hmonas` uses an outer attack loop and one original weapon arm/passive tail, with source use_weapon/passivedone edges; it does not duplicate the policy body. Other shared tails in do_attack/do_stone_mon/mhitm disease/death/pestilence/famine paths likewise remain single original tails. All original comments, including the disabled poly_when_stoned explanation, retain original order.

## Current evidence and explicit limits

The original-C reference, imported-JS hybrid and independent production-only projection compile with memory64 at O2. The hybrid contains no original UHITM bodies. Final successful builds have ten format-nonliteral forwarding warnings only; no incompatible-type, nonnull or noreturn warning remains. Panic/assert/end control is caught with fixture setjmp/longjmp and never exits the real host process.

The canonical controlled gate passes **7858 exact original-C/hybrid comparisons**, reaching all 102 entrypoints. Separate production projection passes **204 comparisons**, all 65 public entrypoints, all three actual native callback targets, and zero `_test_` imports. The comparison observes full foreign-call/RNG/message traces, returns and native state snapshots, not only success status.

Coverage includes every original static object catalogue type through hmon_hitmon, attack/effect/species/hero-role/polymorph paths; seven hmonas attack dispatcher joins with real alternate-attack outparam copying; 64-bit properties above JS exact Number precision; unsigned weight boundaries in the actual default TOWEL arm; positive second-room address stride and char pointer iteration; native minvent obj** reordering; artifact int* mutation; permonst** retarget/death; retained digestion message/native C writes; all 18 record-return adapter positive native-address/cache-identity witnesses and writable-field rereads; thirteen legal nullable cases; actual 40MB native heap growth with synchronous reentry/alias mutation; separate Modules; and controlled C longjmp with native stack and C/R/T environment restoration. Entrypoint reachability and these directed branches are not complete branch coverage.

The nullable matrix is explicit in `record-projections.json`. `mksobj` keeps its actual ReturnsNonNullAttr and is positive-only. `addinv`, `getmattk`, `hold_another_object`, and `splitobj` are also positive-only because a null return would violate or risk their normal contracts; no universal NULL claim is made. The fixture recursively audits all 13 memset target types against actual const subobjects; original readonly initializers remain unchanged. PerMonster pmidx is a true const subobject: fixture calls the unchanged original `monst_globals_init` catalogue-copy boundary, never directly resets/writes pmidx. This inherited native memcpy initialization is stated separately from fixture-safe mutable instance reset.

Catalogue coverage uses original `monst_globals_init` and `objects_globals_init`, copying their static original catalogues. It does **not** call `init_objects`, description/probability shuffling or full game initialization. Object/monster instance weights, HP, equipment and callback results are controlled; getmattk's attack input is controlled. This is real static catalogue data with a synthetic foreign world, not the full foreign engine.

Guards verify fresh actual configured CPP/AST bodies/types/literals, source/formal/function order, all 783 comments, six static initializers, body string values independently of the C-derived literal pool, source regeneration, field aliases and RNG origins; lexical scope passes. Read-only negatives remove only JS uint32 weight wrapping (unchanged C rejects at UINT boundary), corrupt only a scratch mutable initializer (data guard rejects), and remove one scratch original comment (metadata guard rejects). Original source, C oracle, expectations and built artifacts remain unchanged.

**Pending:** native-host validation, shared selected full-game/public replay, complete branch coverage, production allocator failure schedules, every callback/reentry point and actual OS/window/foreign algorithm boundaries. No full-game/native-host equivalence claim is made. Historical invalid/failed compiler/probe/assertion attempts are preserved and explicitly not passing evidence.

## Reproduction

Use bundled Node `.cache/emsdk/node/24.19.0_64bit/bin/node`.

- `python3 nethack-c/wasm/tu-fragments/uhitm-metadata.py`
- `python3 .cache/uhitm-author/storage-audit.py`
- `node .cache/uhitm-author/scope.mjs`
- `python3 .cache/uhitm-author/build.py reference hybrid production`
- `node scripts/test-tu-uhitm.mjs`
- `node .cache/uhitm-author/production-projection.mjs`
- `python3 .cache/uhitm-author/run-negative.py`

`uhitm-hashes.json` binds the exact production/test/guard inputs, prepared dependencies, private generators, raw failures and successful commands/results. It excludes itself. The shared selected build is untouched.
