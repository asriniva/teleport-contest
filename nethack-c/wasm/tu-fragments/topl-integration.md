# TU137/J143 TOPL private handoff — not selected

This replaces only actual configured `win/tty/topl.c`: **15 original bodies,10 public/5 private,80 prepared comments,738 lines/23995 bytes**. Prepared source SHA256 is `d355faebfb41d9e61e784f1ef29050a55c5ca45cd066f2f47688c6b7b7cee566`; pristine is `7abe4855c351b90048261752bab6bcc329f6fa236da1cca0cc48e362b6ff5d6d`. Their sole difference is the inherited eight-line NOMUX_CAPTURE block in topl_putsym, including one comment; pristine has79 comments. The added block saves curx, decrements it for nomux_putch, then restores it. Its exact diff is `.cache/topl-author/prepared-vs-pristine.diff`. This author preserves that prepared behavior and all original names/formals/order/comments/data/control/algorithms in JS. Original licensing notices remain.

Scope was inventoried and approved before implementation; `.cache/topl-author/pre-edit-handoff.json` SHA256 `df20554751eb3ac119ead9a789c276c5d63b64b6aac98c5e2b8c0f61131de45f`. Only the eleven proposed TOPL production/test paths and `.cache/topl-author` changed. No selected registry/build/default, terminal emulator, harness, earlier frozen port or Lua82 edit is included. Parent maintains the shared divergence register.

## Unapplied integration

1. Register `topl`: C source `win/tty/topl.c`, JS `js/ported/topl.js`, library `nethack-c/wasm/tu-libraries/topl.js`, `configuredFunctions: true`. Preserve actual profile/function selection.
2. Include `topl-support.inc` in the typed bridge with actual prepared hack/tcap/wintty headers. Include `scripts/tu-topl-layout.h`, and transport its `topl_layout` rows as signed64 layout values. It provides9 canonical records,15 foreign globals,29 field/type pairs,0 bitfields and existing constants. Sizes/offsets/strides come from the compiler; no TTY/message decision is in C.
3. Import `callTopl` from `js/ported/topl-runtime.js`; add exactly `topl-runtime-method.inc`; bind `layouts.topl` to those actual layout rows. Exclude only `topl.o`. Retain true foreign libc, tty/input/capability/dump-log/window routines and globals.
4. Preserve stdout/capability/shadow routing. C helpers call actual foreign putchar/home/cl_end/backsp/g_putch/end_glyphout/standout/readchar/dumplogmsg/nomux_putch and live volatile windowprocs callbacks. No ANSI substitute, shadow emulator, input shortcut or native TOPL policy fallback is supplied.
5. Require zero `_test_` imports in the linked production Wasm. The five private aliases exist only for direct-entry fixtures. The separate production replay positively detects all5 in the hybrid before requiring none in production.
6. Production cwd is **TREE/src**, input **../win/tty/topl.c** per the actual Makefile. Preserve that filename in __FILE__/nhassert traces. The private reference's exact directory→../win/tty prefix map matches production spelling; outputs are never basename-normalized.

## Source/ABI/lifetime details

Actual profile enables TTY_GRAPHICS,NOMUX_CAPTURE,DUMPLOG_CORE,DEBUG,MACOS; WIN32CON and DUMPLOG are absent. DUMPLOG_CORE is active independently of DUMPLOG, so all3 dumplogmsg sites and saved_pline_index reset remain. No branch was omitted based on a guessed macro. Native compiler inventory captures91 ABI constants, pointer/long8, int4,short2,char/boolean1, signed char[-128,127], WinDesc144 and DisplayDesc60. Four volatile window fields supply21 indirect calls; actual source has116 direct calls,33 distinct true foreign FunctionDecl dependencies,6 char-pointer arithmetic sites,one goto/label and no RNG or enum expressions.

- Original clean_up becomes a labelled block exiting into one original cleanup tail; unrestricted-response and normal response paths share the same original formatting/state updates.
- AppendLongDigit retains the exact signed64 threshold/overflow test with `9223372036854775807n`, checked against the actual compiler constant. Its source arguments are scalar locals. C typed local conversions56/native long promotions20 and2 stored/argument logical canonicalizations preserve C results. The long numeric divide uses BigInt truncation. All6 pointer arithmetic sites use actual char stride1, including tl+=CO-1; raw character pointers never become copied JS strings.
- CO is a live getter for gt.tc_gbl_data.tc_CO, not a captured constant. Record views cache canonical type/address within an invocation and use fresh heap views. Short display cursors, long window counters, signed char keystrokes and unsigned uchar key2txt conversion retain actual C narrowing. Global/window pointers can be reread after native callbacks.
- Source-owned snapshot_mesgs(char**),nxtidx(int),initd(boolean) live in Module-owned native typed storage; JS owns their original zero/FALSE initializers. Snapshot arrays and message buffers use actual alloc/free. Passive locking preserves exact old pointers; destructive snapshots transfer ownership, restore old/new message order, then free transferred buffers and snapshot storage. Returned char* addresses retain native alias/lifetime.
- rtmp40,prompt256,respbuf128,digit_string2 use real native stack storage at their original lexical points. Internal calls and reentrant public calls restore stack/C/R/T environment; source-visible state is not artificially rolled back on a native nonlocal unwind. Nested tty_yn_function with suspended outer prompt buffers and memory growth is tested.
- Native ABI helpers contain layout/global/field/storage/varargs and true foreign forwarding only. Public functions remain C-callable through actual signatures; four TTY window-proc public callbacks are invoked indirectly through a volatile native table. Actual alloc/eos nonnull contracts remain: the fixture never returns artificial NULL from them.

## Final bounded evidence

**1826 exact original-C/imported-JS comparisons**, all15 entrypoints. Separate production-only replay: **1792 comparisons**, all10 public entrypoints,4 typed native public callbacks,0 `_test_` imports, with5 positive hybrid detector imports. Returns, full foreign-call/output/shadow/input/dump traces, native state, actual pointer aliases and allocation/free identities are compared. Both no-build modes verify all178 transitive/production inputs before and after replay; actual C preprocessing enumerates149 reference/148 hybrid/production input paths including SDK system headers.

Cases cover response/default/escape/hidden/uppercase/control-P behavior; backspace/erase/cancel/invalid input; zero/leading-zero/numeric/LONG_MAX/overflow; message append/death/STOP/NOSTOP/LOCK/checkpoint/more guards; wrapping/long tokens/graphics and signed high bytes; active dump history; passive locking/retained pointers/native C writes; destructive restore/free over1,2,3,6,8 rows; source unavailable-window guards and controlled panic/assert recovery; live volatile window callback retargeting; actual40MB native heap growth/reentry/alias mutation; nested prompt-buffer lifetime; separate Modules with suspended snapshots; native nonlocal unwind both from a window call and between shadow decrement/restore. Entrypoint reachability is distinct from complete branch coverage.

Both source diagnostics are bound to actual CPP arguments. The single-line assertion reports317; the multiline assertion beginning719 reports**720**. An initial719 opener-line guess failed the raw native comparison; it was corrected from the captured actual AST, not by normalizing outputs. Raw failure `failure-1794325002479.json` remains in the private history.

Source guards check prepared/pristine hashes, fresh full configured AST bodies/types/literals, original function/formal order, all80 ordered comments, all3 source statics/initializers,91 exact fresh ABI constants, CO alias,active dumplog/nomux,actual filename contexts,body strings independently of the binding literal pool and readable regeneration. Lexical scope passes. Five memset target types are recursively checked for true const subobjects; original const quitchars and mutable defmorestr initializers are retained. Native writes through returned message pointers require a tracked live writable allocation. No original game catalogue is initialized or substituted in this fixture.

Four negatives preserve original source/C oracle/built artifacts/expectations: read-only module loaders change only LONG_MAX or omit only the shadow decrement; unchanged C rejects both by execution. Scratch overrides remove one original comment or change initd's initializer; guards reject both. Before/after hashes prove original inputs unchanged.

Successful reference/hybrid/production builds have one format-nonliteral forwarding warning and one Emscripten limited-postlink-optimization warning because production-style `-g` is retained. No type/nonnull/noreturn warning remains. Panic/assert/input exhaustion/unwind are controlled setjmp/longjmp fixture paths; they never exit the real host process.

**Not proven here:** native-host execution, real terminal/OS/input/capability/stdio failure behavior, selected full-game/public recordings, complete branch coverage, production allocator refusal schedules or every possible callback/reentry point. The production projection uses the real library/import boundary with a controlled C foreign environment; it is not a real-terminal integration test. Allocations/TTY/world callbacks are controlled; actual libc string/memory operations and native owned storage are used. Pointer trace IDs map actual tracked allocation+offset/global addresses rather than asserting identical layouts between distinct builds; positive alias witnesses compare actual native addresses inside each Module. No full-game/native-host equivalence claim is made.

## Reproduction / no-build review

Bundled Node: `.cache/emsdk/node/24.19.0_64bit/bin/node`.

- `node scripts/test-tu-topl.mjs` — no build; original-C/hybrid replay.
- `TOPL_PRODUCTION=1 node scripts/test-tu-topl.mjs` — no build; independent production replay/import audit.
- `python3 nethack-c/wasm/tu-fragments/topl-metadata.py`
- `python3 .cache/topl-author/storage-audit.py`
- `node .cache/topl-author/scope.mjs`
- `python3 .cache/topl-author/run-negative.py`

Rebuild only if wanted: `python3 .cache/topl-author/dependencies.py` then `python3 .cache/topl-author/build.py reference hybrid production`. Prepared dependencies, transitive SDK headers, successful commands/results, private generators and raw failed attempts are bound by `topl-hashes.json`, excluding the manifest itself. Historical failed attempts are investigation history, not passing gates.
