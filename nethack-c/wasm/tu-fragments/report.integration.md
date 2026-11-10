# REPORT integration handoff (first pass, not promoted)

Files owned here:

- `js/ported/report.js`: all **10** configured original functions/order; all
  original and prepared block comments retained. Inactive comments are archived
  at the end; no inactive algorithm is claimed. `in` becomes `in_` because `in`
  is a reserved JS binding. Forward `goto skip/full` become labeled blocks;
  SWR_ADD's exact statements are expanded at all eight original callsites
  inside the labeled full block; its goto becomes break full. The original
  macro text remains a comment. File-private state remains per module. The
  original static URL cursor is deliberately NOT reset between submissions.
- `js/ported/report-runtime.js`: `createReportBridge(layout)` owns per-Module
  state; returns `(services,name,...args)`. The bridge scopes C, converts ABI
  pointer/int reference arguments, and rejects unimplemented configurations.
  `createReportState` uses fixed zero-only C storage, not allocation. char
  signedness and unsigned saved-message index are preserved. Temporary `chr`
  storage is reused within an invocation, avoiding per-byte stack growth.
- `nethack-c/wasm/tu-libraries/report.js`: memory64 public imports/services;
  stack cleanup in finally, including nested calls/fixture exit exceptions.
- `nethack-c/wasm/tu-fragments/report.support.c`, `report.storage.h`: ONLY typed
  dependency calls, globals/array backing, format ABI adapters. No REPORT
  algorithm or original-report fallback. Include support once from game
  tu-support.c; the isolated probe includes it itself (do not link it twice).
- `scripts/tu-report-layout.h`, `tu-report-probe.c`, `test-tu-report.mjs`:
  compiler metadata, controlled dependencies, actual memory64 differential.

## Shared edits for the integrating owner

Registry entry:

    {"name":"report","source":"src/report.c",
     "javascript":"js/ported/report.js",
     "library":"nethack-c/wasm/tu-libraries/report.js",
     "reference":"prepared","configuredFunctions":true}

Prepared provenance is necessary: inherited patch guards CommonCrypto with
`MACOS && !__EMSCRIPTEN__`, enables nhmd4 with `__linux__ || __EMSCRIPTEN__`, and
excludes the submit stacktrace loop under `__EMSCRIPTEN__`. Pristine and prepared
source are different; source checker must inspect prepared configured bodies
and retain comments from both originals. Add the narrowly named parameter rule:
for REPORT/swr_add_uricoded only, assert original first name is `in`, replace it
with `in_` before comparing JS parameters. No other parameter exceptions.

Runtime import `createReportBridge` from './report-runtime.js'; inside
createPortedRuntime construct `const report = layouts.report ?
createReportBridge(layouts.report) : undefined;`; return property
`report(services,name,...args) { if (!report) throw new Error('Missing REPORT
layout'); return report(services,name,...args); }`. This avoids global state and
supports existing probes that have no REPORT metadata. The binding already
passes `moduleKey:Module`.

Build probe exports (all `_probe_` prefix, plus malloc/free):
`reset option config message index init bidshow encode submit bug libc gdb saved
handler signals trace output clear stack context_size layout_count layout_name
layout_value crashreport devteam`.

- Both modes compile scripts/tu-report-probe.c and the **prepared** nhmd4.c.
  This hash dependency is deliberately C in the isolated oracle comparison;
  actual production already replaces nhmd4 with the JS TU. No original report
  object is compiled in hybrid mode. Reference uses `-DTELEPORT_REFERENCE_TU`
  (probe includes prepared report.c itself); add REPORT to that existing list
  so the builder does NOT add report.c separately.
- Both modes use current compile-defines.json and forced native-terminal.h,
  matching the active game's ABI, including signal constants. Do NOT add
  native-libc-library.js for this isolated probe: its signal/syscall calls are
  controlled typed fixtures. Existing generic linking of it in hybrid may be
  harmless if DCE removes it, but the verified recipe does not need it.
- Both modes redirect `readlink open read write close fork execve waitpid signal
  exit` using `-Dname=teleport_probe_name`. Helpers are compiled under the same
  substitutions; direct JS imports call the typed helpers, not unmocked SDK
  calls. No browser launches or actual signals/forks occur.
- Hybrid adds the REPORT JS library. Do not add main tu-support.c, because the
  probe includes its REPORT-specific helper fragment directly and needs no
  other game support.
- Actual game includes report.support.c once in main tu-support.c, links
  report.js library, and excludes report.o through the registry. No startup
  callback: static ABI storage begins zero, state is instantiated on first use.
- Source hashes/build inputs must include report-runtime.js, helper C, storage
  header, layout header, library and core.

Metadata writer: read probe layout_count/name/value into flat `layouts.report`.
Add `strings:{CRASHREPORT:readCString(_probe_crashreport()),
DEVTEAM_URL:readCString(_probe_devteam())}`. The numeric CRASHREPORT entry is a
feature flag; runtime converts it to path string only in the environment. Guard
rejects current native-libc/GDB/Win32/no-signal/no-stderr branch changes, changed
path '/usr/bin/open', and unexpected memory/array widths. `bidSize` and MAX_URL
come from sizeof the ABI backing arrays (40,8192). Reference-only _Static_asserts
compare those backing sizes to the actual original `sizeof bid`/`sizeof url`
after including report.c, so drift fails compilation. Other values come from the
compiler, including signedness, MD4 context/size, error-prefix sizeof, and signals.

The test imports standard `.cache/tu-probes/report-reference.mjs` and
`report-hybrid.mjs`. Set TELEPORT_REPORT_PROBE_DIR to use isolated output.
It builds its own bridge from actual compiler metadata, so it can run before
shared layouts/registry/runtime changes. It currently always tests Emscripten;
DO NOT count it as native coverage in the native aggregate.

## Verification actually completed

Isolated recipe saved at `.cache/build-report-isolated.py`, output/logs under
`.cache/report-isolated/`, `.cache/report-isolated-build.log` and
`.cache/report-isolated-test.log`.

- Both memory64 modules compiled with -O2, original REPORT excluded in hybrid.
- **410** prepared Emscripten-C/JS comparisons passed: exact buffer+guards,
  pointer/int outputs, rollback boundaries, signed high bytes; saved-message
  ring zero/max/unsigned wrap indices; MD4 chunk/failure/once trace + formatted
  hash; parent fork/wait status; child execve URL/argv/error/exit; URL truncation
  and repeated static-cursor behavior; dobugreport fallback; configured
  panictrace stubs and ordered signal registration; normal stack/C-scope cleanup.
- Source inventory/order/comments checked by `.cache/report-source-check.py`
  (same shared checker plus only reserved `in` parameter rule).
- Lexical scope check `.cache/check-p01-scope.mjs report` passed.
- Node syntax checks passed for core/runtime/library. No full game build,
  production artifact, native oracle, or public replay was run or claimed here.

## Explicit remaining limits

Native macOS REPORT uses CommonCrypto/argv instead of Linux readlink/nhmd4 and
may compile PANICTRACE_LIBC/backtrace code omitted in EmC. This port deliberately
rejects those configurations; no native equality or native backtrace support
is claimed. Metadata mismatch is a failure, never a platform-specific pass.
The fixture's controlled child-exit uses EM_JS and needs a native-compatible
exit-capture adapter before this whole test can run through native-addon.
The current core's child algorithm is compared to original prepared EmC, with
exact URL/error bytes captured before controlled exit(1). Actual OS browser
launch, external signal delivery, executable hashing through the production VFS,
and production mixed game link remain integration gates for the owner.
