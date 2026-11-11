# DLB archive library utility profile

Separate utility source, not game registry selection, default or acceptance. Readable original policy is js/ported-utilities/dlb-library.mjs; runtime/nativeABI provide actual libc and compiler-derived native memory only. Perutility dlb-library-scope.mjs is a distinct synchronous dependency scope; neither utility shares a mutable game scope. Scope helper body matches the reviewed original synchronous C/R/T restoration helper.

Build/test/guard from repository root (fresh directory required):

    python3 scripts/build-utility-dlb-library.py --out /absolute/fresh/run
    node scripts/check-utility-dlb-library.mjs --out /absolute/fresh/run
    node scripts/test-utility-dlb-library.mjs --out /absolute/fresh/run

Optional --source-root /absolute/project for allthree scripts allows candidate code to remain staged elsewhere while actual originalC/configuredheaders/SDK are read under that explicit source root. EMSDK environment overrides only the compiler/tool location. Build requires --out and refuses an existing directory before writing. It emits actual compilerAST/inventory, commands/exits, matching reference/hybrid modules and sourcehashes; no downloaded/copiedSDK. Source reference include is an explicit compiler macro with the absolute originalC path, not an unrelated include-search fallback. Tests/guards consume the specified actual fresh pair/output directory; no frozen evidence paths or game artifacts.

Actual source-owned policy expectations: 22functions/42comments/9procedure references;2067assertions across native/library API states. Header/layout data come from real compiler sizeof/offsetof; arrays/record fields read current native memory, originalinitialized/noinit cells and stack lifetime retained. All algorithms stay in original JS boundaries and formal names; no C policy fallback. Guards retain originalcomments/formals/control-node counts/catalogue projections and their existing negative controls, not a general semantic proof. Unit code/assertions are path-adapted versions of the original frozen suite with no case/expected changes.

Currentgame DLB remains disabled. Separate explicit DLB/emptyDLBLIB archive profile with actualalloc/FITSuint_/panic/hacklib. Fixture fopen_datafile forwards MEMFSfopen and ignores prefix; sourcepath search belongs to callers. Malformed archive buffer/length overflow, invalidhandles/OOM/undefined reads excluded. Archive end-relative seek subtractspos and archivefgetc signextendschar; retain both sourcequirks.

Experimental profile is actual EmC4.0.10/Clang21 MEMORY64 -O2-g, original utility-specific defines, growth and4MiBstack/MEMFS. Actual command log is authoritative; host platform Makefile behavior and nativeMac/Amiga execution are not asserted equivalent. No game/public/terminal/defaultdeadline/timing claim. No Makefile is changed or installed CLI silently substituted. Historical separate proof package .cache/utility-dlb-library-port remains immutable; it is provenance, not an active runtime import/output path.
