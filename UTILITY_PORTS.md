# Standalone utility C-to-JavaScript ports

These profiles are separate from the game registry. They use Emscripten4.0.10/Clang21 in memory64 mode, retaining native libc/layout/dependency transport. Original policy bodies remain in the C reference; the mixed build replaces the named TU with JavaScript. Native macOS parity is deferred.

| Utility | JS source | Build/check scripts | Staged checks | Limits |
|---|---|---|---|---|
| RECOVER | `js/ported-utilities/recover/recover.js` | `scripts/build-utility-recover.py`, `scripts/check-utility-recover.cjs`, `scripts/test-utility-recover.mjs` |113 /47 cases |Actual original MINIMAL_FOR_RECOVER version and hacklib copy dependency; isolated fixture files only; undefined malformed input excluded. |
| DLB_MAIN | `js/ported-utilities/dlb-main/dlb_main.js` | `scripts/build-utility-dlb-main.py`, `scripts/check-utility-dlb-main.cjs`, `scripts/test-utility-dlb-main.mjs` |78 /42 cases |Explicit DLB/DLBLIB utility profile; original C library/alloc/panic/hacklib dependencies in this individual pair. Separate both-JS library integration proof passes78/42. Game DLB stays disabled. |
| PANIC | `js/ported-utilities/panic/panic.js` | `scripts/build-utility-panic.py`, `scripts/check-utility-panic.cjs`, `scripts/test-utility-panic.mjs` |196 /12 paired configurations |Actual native va_list/stdio/abort; isolated FORCE_FILESYSTEM transport. Source stream bytes compared; generated runtime stacks differ and are retained. No native-host core-dump equivalence or post-abort recovery claim. |

Each utility has its own runtime/scope and ABI files under `nethack-c/wasm/utilities/`. Policy source, comments and function boundaries match its active original profile; RECOVER uses a verified formatting-only revision. No shared utility framework was introduced.

Run a builder with `--out /absolute/fresh/output`; an existing directory is refused. `--source-root /absolute/repository` is optional when the code and original sources share a repository. Prepared headers and the installed pinned SDK are prerequisites from the normal build setup. Use that SDK's Node executable for the checker and test script; their documented output-directory arguments select the fresh pair. The explicit reference-source macro resolves original C without incidental include search.

Exact file/receipt/command bindings: `.cache/utility-root-staging/source-promotion-a.json` and `.cache/utility-production-candidates-a/README.md`. Frozen proof packages remain immutable. Tests after source-path promotion are tracked in the divergence/progress registers; staged success is not a game or native-host acceptance claim.

Additional installed profiles: BMP2IFF_HOST (`bmp2iff-host.mjs`,8 functions;67+6 staged checks), DLB_LIBRARY (`dlb-library.mjs`,22;2067), STRIPBS (`stripbs.js`,1;612/102) and UUDECODE (`uudecode.js`,4;189/64), all under `js/ported-utilities/`. Use matching individual build/check/test scripts with explicit fresh output and source arguments. Full BMP/DLB recipes are in `docs/ports/`; source binding `.cache/utility-root-staging/source-promotion-bc.json`. Native-Mac parity is deferred. UUDECODE actual passwd stub and exit-flush behavior, STRIPBS original errno quirk/inconclusive mutant, DLB isolated fixture and original undefined-input limits are retained.

RECOVER113/47, DLB_MAIN78/42 and PANIC196/12 have now passed actual final-path rebuild/guard/suite replay. Their checker requires both `--source-root /absolute/repository` and `--out /absolute/output`; only the builder defaults source-root. Corrected replay and initial command-line failures are retained.

All seven installed profiles now pass actual final repository-path pairs and unchanged suites, including BMP67+6, DLB2067, STRIPBS612/102 and UUDECODE189/64. STRIPBS/UUDECODE builders execute their source guards; a second guard correctly refuses overwriting its result. Full command/terminal logs: `.cache/utility-root-staging/live-replay-bc/`.

XPM2IFF_HOST is installed (`js/ported-utilities/xpm2iff-host.js`,6 functions); reproduction/limits in `nethack-c/wasm/utilities/xpm2iff-host/README.md`. Staged54cases/56assertions split21 defined,32 empirical scanf-ABI and1 two-Module case; full native/undefined-input equivalence is unclaimed. Root source receipt `.cache/utility-root-staging/source-promotion-xpm.json`.

XPM final repository-path pair and all5 guard/test/import/ABI/negative checks pass54cases/56assertions: `.cache/utility-root-staging/live-replay-xpm-results.json`. The empirical scanf qualification remains.

Installed tile profiles: TILETEXT (`tiletext/tiletext.js`,12 functions), PPMWRITE (`ppmwrite/ppmwrite.js`,6), THINTILE (`thintile/thintile.mjs`,4). Individual fresh-output build/check/test scripts retain original native naming/catalogue dependencies and bounded isolated-file contexts. Staged54/39,515/16 and21 complete comparisons pass; final-path replay follows. Exact inverse and SDK24b binding: `.cache/utility-root-staging/source-promotion-tiles.json`.

TILETEXT54/39, PPMWRITE515/16 and THINTILE21 have now passed actual final repository-path builds, source guards and unchanged suites with current SDK24b. Logs: `.cache/utility-root-staging/live-replay-tiles/results.json`. This brings installed standalone profiles to eleven; game registry stays137 and full accepted checkpoint stays110.


GIFREAD12 functions and TILE2BMP8 now installed in normal source paths (21 new text files), including readable JS/runtime, native ABI transport and individual build/check/test/fixture tooling. Root reviewed154 package hashes and19 exact plumbing inverses before byte-exact promotion; original policy/assertions unchanged. Staged GIF33 scenarios/59 dispatches split26 defined+7 empirical; original GetCode negative-index firstdecode read remains, so whole-decode agreement is empirical EmC only. TILE2BMP28 complete outputs+40 helpers pass staged;8 sourcefunctions/13 comments retained. No original C, game registry, terminal, harness or native-Mac acceptance changes. Final repository-path replay next. `.cache/utility-root-staging/source-promotion-gifread-tile2bmp.json`; per-profile README files contain exact commands/limits.


GIFREAD and TILE2BMP actual final repository-path builds, fixtures/source guards and unchanged comparisons all exit0: GIF26 defined+7 empirical/33scenarios/59dispatches; TILE2BMP28 complete outputs+40 helpers. Thirteen standalone utility profiles now pass final-path checks. `.cache/utility-root-staging/live-replay-gifread-tile2bmp-results.json`. No assertion or original C changes; GIF inherited UB/nativeMac/game limitations remain.


TILEMAP is installed in23 new source/recipe texts, two explicit profiles of ONE original win/share/tilemap.c: TILETEXT six functions and generator same six plus init_tilemap/main. Root rehashed142 candidate-package files, original206+159 frozen files and17 exact path-only source/runtime/native/test inverses; staged2697 and5060 checks/source-data guards pass. Original native catalogues/reader/stdio remain typed dependencies. Same-address overlapping nh_snprintf input/destination is preserved; generator output parity is empirical EmC, not portable defined-C or native-Mac evidence. Individual scripts/docs/ports/tilemap.md are reproducible; final repository-path replay pending. Game registry/terminal/harness unchanged. `.cache/utility-root-staging/source-promotion-tilemap.json`.


TILEMAP actual final repository-path original/mixed pairs, both fresh AST/data/source guards and unchanged suites all pass: TILETEXT2697 checks and generator5060 checks. Fifteen installed standalone profiles now pass, representing14 distinct utility/source TUs (two TILEMAP profiles count once). Original generator overlapping snprintf remains qualified. `.cache/utility-root-staging/live-replay-tilemap-results.json`.


SFEXPASC installed as12 new source/ABI/build/check/test texts after root134file rehash and10 full byte inverses. All139 configured functions (86 macro-expanded empty+53 handwritten),40comments and2 procedure tables retained; actual staged18commands0, unchanged197 comparisons+278catalogue/foreign checks, exact regeneration/3guardnegatives and wrong-long+1 rejection pass. Requires explicit genuine original-C-generated sfdata/sfproto directory; no padded/fabricated headers. Separate JS SFTAGS genuine run FAIL (four field types differ) remains OPEN, not a serializer waiver. Final repository-path replay next. `.cache/utility-root-staging/source-promotion-sfexpasc.json`, per-source README. No original C/game/harness/terminal/nativeMac changes.


SFEXPASC actual final repository-path pair, strict byte-regeneration/sourceguard and both unchanged suites PASS:197 comparisons/all139 functions and278 catalogue/foreign checks. Sixteen standalone profiles representing15 distinct utility/source TUs now pass final-path checks. Genuine JS SFTAGS four-type mismatch remains OPEN and separate. `.cache/utility-root-staging/live-replay-sfexpasc-results.json`.
