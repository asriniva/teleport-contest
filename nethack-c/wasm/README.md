# Deterministic wasm64 build

**Local development build, not an eligible contest submission:** the
[contest rules](https://github.com/davidbau/teleport-contest#rules) require
plain JavaScript and explicitly prohibit Wasm. This also rules out a Wasm
terminal dependency in an otherwise pure-JS submission. The build and scores
below are local implementation-comparison tools.

See the [complete upstream divergence register](../../UPSTREAM_DIVERGENCES.md)
for every inherited patch, additional source change, build setting, compatibility
replacement and known limitation. The reference submodule is unedited, but the
source copy used to build the executable is modified.

**Current change:** all three frozen file copies, canonical PRNG/VFS use, and
scoring overlays remain restored. The extra screen conversion has been reverted:
input and animation snapshots again use the original recorder shadow encoding,
without DEC-to-Unicode conversion or canonical Terminal reserialization. Ghostty
remains removed from the active game adapter. Verified public result: **44/44
sessions**, **11,405/11,405 screens and cursors**, **792,838/792,838 RNG calls**,
**1,483/1,483 animation frames**, no runtime errors. Recorder/profile checks and
timezone/macOS/bones integration pass. The 25/44 result belongs to the reverted
FR03 path. The default build now uses JavaScript terminfo, compression and regex;
the remaining mixed Wasm engine is still required. See
[FR01–FR05](../../UPSTREAM_DIVERGENCES.md#active-frozen-infrastructure-restoration-fr01fr04).

From the repository root:

```sh
bash nethack-c/setup-wasm.sh
bash nethack-c/build-wasm.sh
bash scripts/test-wasm.sh
bash scripts/score-wasm.sh
# Or just one public session:
bash scripts/score-wasm.sh sessions/seed8000-tourist-starter.session.json
```

Setup downloads Emscripten and Lua into `.cache/`. It does not install global
packages or change shell startup files. `EMSDK` can point to another SDK checkout.
The native data generators require Clang 21, GNU make, and a host SDK/development
headers. On macOS the script uses the installed Command Line Tools directly.
On Linux, install Clang 21 and the ncurses development headers first.
Python 3.12+ is required for the build driver.

The recorder script requires Clang but does **not** pin a frontend version.
This build pins Emscripten **4.0.10**, whose frontend reports **Clang 21.0.0git**
(LLVM revision `8f7e57485ee73205e108d74abb5565d5c63beaca`). Native data generators
use host Clang 21 (Apple Clang 21.0.0 on the development machine); that is the
same major frontend version, not an identical Apple/LLVM revision. Emscripten's
bundled Clang has only the WebAssembly backend and cannot build host tools.

The remaining NetHack C and Lua API transport are compiled and linked with
`-sMEMORY64=1`, true
64-bit WebAssembly with 64-bit pointers and longs. Compile-time assertions in
`bridge.c` enforce the LP64 layout. The SDK supplies Node 24 for execution;
Node 22's default runtime does not enable memory64. The scoring wrapper selects
the SDK runtime, including for scorer child processes.

The build verifies upstream commit `16ff59115315917b93185d026aeefea06db9b0f4`,
applies the existing six recorder patches, and pins `SOURCE_DATE_EPOCH` to
`1777723200`. It first builds the native recorder and data generators, then
builds the mixed NetHack game for wasm64. The optional `--c-lua` reference
selects compiled Lua5.4.8. Clean builds retain a C Lua archive for independent
quest test fixtures; it is omitted from the default game link. The default Lua
algorithms are JavaScript. All work happens in `.cache/wasm64-build/`;
the upstream submodule is never edited. The generated module and Wasm binary
live under `js/wasm/`; `build.json` records the compiler and binary checksum.
Run the default build for a clean rebuild; `--resume` is a development shortcut
after the native preparation stage has already succeeded.

The terminal path keeps NetHack's original capability queries and tty logic.
The default JavaScript terminfo service implements the configured ncurses 6.5
interfaces against the same pinned entry copied from this Mac's native database.
Real ncurses headers are still built for the C callers and reference tests;
its library is omitted from the default game link. LINES/COLUMNS specify 24/80.
Native macOS reports ncurses 6.0; historical database/library identity is unverified.
See [dependency provenance and build options](terminfo/README.md). Replay keys
and shadow snapshots cross the C/JS callbacks at existing recorder boundaries.
Shadow capture is the default. NetHack is compiled with `MACOS` game features, including its apple
message, option layout, mail feature descriptions and MacOS version banner.
The compiler target remains wasm64; Apple host-system macros are not defined.
Crash-report hashing uses portable MD4 instead of CommonCrypto. Native stack
walkers and debugger paths are disabled, and paste-buffer writes stay in the
module rather than launching `pbcopy`. A virtual root
account replaces Emscripten's unsupported Unix account lookup, while retaining
NetHack's normal sysconf authorization checks.
The game combines translated JavaScript units with the remaining patched C
implementation; the default Lua algorithms are JavaScript behind typed C API
transport. Data files are
embedded in the Wasm artifact. Each segment gets a fresh module and MEMFS;
changed files are serialized through the frozen storage API. The transient-file
filter preserves bones; the JavaScript ncompress-compatible service provides
native-compatible .Z compression. All public save/bones sequences and
RNG traces match. Module
termination does not change the host scoring process's exit status.

`js/jsmain.js` exports this engine through the original `runSegment` contract.
The existing JS skeleton remains available as `runJsSegment`; browser UI code
still uses its `NethackGame` class. The frozen scorer and comparator are
unchanged. There is no native subprocess, network, or host filesystem write
inside the engine adapter. No recorded answers are passed to the engine.

The generated `.mjs`/`.wasm` artifacts are ignored by Git: build them before
scoring or package them when preparing a runnable submission. Local score
results are also written to `.cache/session-results.json` by the scorer.

## Timezone and replay dates

The engine honors the Node process's `TZ`. Emscripten's time functions use
JavaScript `Date`, and the adapter exposes the same timezone in the module's
C environment. It does not change the host process timezone. If `TZ` is absent,
the engine uses the host's normal timezone.

The scoring script defaults the process to `America/New_York`, matching
`scripts/record-session.mjs`, and preserves an explicit override:

```sh
TZ=UTC bash scripts/score-wasm.sh
TZ=America/Los_Angeles bash scripts/score-wasm.sh
```

The fixed-date parser reproduces the recorder's inherited DST flag using an
explicit recording-clock snapshot, rather than the current execution season.
`TELEPORT_RECORDING_EPOCH` specifies that clock in Unix seconds; the default is
`1777723200`, the contest's pinned build epoch (May 2, 2026 at 12:00 UTC).
The exact historical capture clock is not in session metadata; using the build
clock is a documented compatibility assumption supported by winter-name replay
diagnostics. The module exposes it as NETHACK_RECORDING_EPOCH. Its localtime in
the process TZ supplies the parser's inherited DST flag; replay datetime strings
are unchanged. This replaces the prior tm_isdst=-1 adaptation. A different
recording clock can be selected for other recording environments. Browser
execution uses browser local time and has no process environment override.

Shadow snapshots now also use the recorder's final screen encoder, including
attribute-blind long-space compression. Bones with numeric suffixes are retained
between segments; compression now uses the in-process .Z service described below.

`bash scripts/test-wasm.sh` checks New York, Los Angeles and UTC in independent
processes, compares each replay under simulated winter and summer clocks, and
checks the macOS apple message, option layout, corpse prompt and version/help
features. The full public suite still checks the unchanged frozen comparator.

## Historical terminal backend

Ghostty's implementation and setup script remain as standalone development
artifacts. The active game adapter no longer selects it, including when
`TELEPORT_TERMINAL=ghostty` is set. All scoring screens use the restored recorder
shadow encoding. `node scripts/test-terminal.mjs` can still exercise the emulator
separately after its dependency is installed.

`bash scripts/test-wasm.sh` checks native/Wasm terminfo, recorder screen
encoding, and timezone/macOS regressions. The frozen harness and recordings
remain unchanged. Browser integration is unverified.

## JavaScript dependencies and runtime migration

The regular build selects JavaScript compression, terminfo, regex and configured Lua. Its
manifest records service hashes, ABI flags and `dependencyBackend: javascript`.
The Wasm link omits ncompress, libtinfo, musl's TRE regex algorithms and liblua. Small
C forwarders still adapt native pointers, varargs and tty callbacks; they are
needed while C game callers remain. The adapter supplies per-segment services,
input boundaries, recorder snapshots, profile setup and save/bones transport.
`js/services/game-files.js` now owns the unchanged filesystem-independent
`{files, deleted}` persistence format. Screen capture and encoding are unchanged.

The integrated path passes all **44/44 public recordings**, including all
**11,405 screens/cursors**, **792,838 RNG calls** and **1,483 animation frames**.
Focused checks cover actual wasm64 service calls, heap growth/reentry, codec
errors and statuses, save/bones restoration, timezones, profiles and version
commands. Public recordings establish that corpus only. Browser execution is
unverified. An earlier unoptimized two-service candidate hit one replay timeout;
the session passed alone, and both the optimized three-service candidate and
regular build subsequently passed the full unchanged suite.

Scope remains explicit: terminfo uses the pinned entry, without full ncurses
terminal discovery, baud padding or TTY timing. Regex implements the configured
`REG_EXTENDED | REG_NOSUB` byte/C-locale interface; other compile flags, capture
offsets and Unicode locales are unsupported. The numeric tparm shim preserves
the existing wasm64 caller/library varargs behavior, including packed-int quirks;
it is not a generic string-varargs interface. Narrow bridges do not remove Wasm.

Independent runtime work is available in `js/ported/js-runtime.js`: ordinary
JavaScript-owned byte memory, scoped allocation, a bounded libc subset, calendar
services and `CVFS` regular files/directories. Existing alloc, strutil, ISAAC64,
MD4, calendar and regex-wrapper translations execute through this provider without Module or
Wasm. Save/bones payloads match actual MEMFS, including binary data and deletion.
This provider is not yet the game backend. Its filesystem excludes symlinks,
devices, sockets and mounts; time follows the configured host-Date/DST policy;
libc includes tested native-compatible integer and floating formatting.

The configured JavaScript Lua implementation has all83 Lua5.4.8 opcodes,
an incremental reader/compiler with exact native instructions/debug metadata,
binary chunks, incremental/generational GC, weak tables/finalizers/close,
native table layout and a typed memory64 C-API callback/error provider.
The frozen final candidate passes the complete dependency suite, all44 public
recordings,126 original level scripts at three seeds (378 actual loads), and
wizard OS/debug probes. Native allocator gates cover131 original sources,
binary chunks, startup, exact diagnostics, callback-visible memory counts,
allocation refusal and cleanup. Its46 production/36 test inputs remain fixed.
The normal builder defaults to JavaScript Lua. The accepted110-TU game passes
full integration with the original30-second worker limits and all44 recordings
exactly under the original45-second session limits, without diagnostic loaders
or timeout overrides. Its683 declared artifact/source hashes and the same1,322
inputs for both gates remain unchanged; scorer metadata was included before
testing. Accepted evidence is `.cache/tu110-warn-fixed-gate-snapshot/acceptance.json`;
the full build manifest SHA256 is `5e402d6f8a7620da484a121e7c7d348ed458899a0fa7abb84cfc98816be9e001`.
Acorn AST traversal resolves298 literal local module dependencies in that copy;
configured SDK/tooling and dynamic file access remain outside that closure.
The earlier98-TU acceptance and its later public metadata supplement remain
separate historical evidence. The110-TU batch has57 first-pass native checks
pending;53 historical native suites do not establish fresh aggregate native parity.
Later staged ports need fresh component and full-game gates.
All46 selected Lua production hashes match the final private freeze.
`--c-lua` retains compiled Lua for comparisons, while
`--c-dependencies` selects it unless `--js-lua` is explicit. The manifest records
the actual selected backend and Lua source hashes. Historical private candidates
remain separate from the final `.cache/js-lua-game-final/acceptance.json` evidence.

Wizard OS functions use JS native-macOS calendar, IANA2026c timezone data and
C-locale strftime, including historical and extreme-year behavior. Native
strftime notices are preserved: this software was developed by the University
of California, Berkeley. Clock/current time and file operations remain injected
platform services. Original NetHack NEVER filters still remove process, locale,
environment and debug-hook facilities; inactive package/io libraries and general
C continuations are outside the configured replacement scope.

After setup and a regular build, run the standalone oracle suites with:

```sh
npm run test:dependencies
python3 -B scripts/audit-js-dependencies.py --check
```

Production services use no Node imports, host files, subprocesses, network or
Wasm. Development tests compile reference C and use native tools. The isolation
test disables those capabilities while executing production modules. The runner
uses the SDK's memory64 Node for configured C oracles; `DEPENDENCY_TEST_NODE`
can separately select Node22 for standalone tests. For the previous compiled
dependency path, `bash nethack-c/build-wasm.sh --resume --c-dependencies` selects
an explicit diagnostic build; that alternate selection
has not been rebuilt/revalidated in this migration. Rebuild normally to restore
the default. Candidate tooling stages its own build and frozen scorer under
`.cache/` and does not alter the active game outputs.

Remaining work is migrating the other game translation units, expanding
ordinary-memory struct/global/libc coverage and moving remaining filesystem
calls/startup onto that runtime. Replace each native pointer/callback seam as
its callers move, then remove the corresponding Emscripten code. Rerun the same
recording gates at each step.
The adapter contract remains useful after Wasm removal; its Emscripten-specific
pointer and module portions should disappear as their callers migrate.

## Native C parity coverage

`npm run test:native` (or `bash scripts/test-native-tu.sh`) now runs the
**existing `test-tu-*.mjs` cases** with native C selected as their reference.
Use `bash scripts/test-native-tu.sh were rnd` to select suites. The same files
use native C by default. `TELEPORT_NATIVE_TESTS=0` explicitly selects the
Emscripten-C diagnostic; its libc differences are not alternative expected JS
behavior. `test:wasm` requires native parity and the three-way library gate.
The smaller hand-written scenarios from the earlier implementation are retired
from the main test path. Their historical 50/50 result did **not** establish
native coverage of every existing case.

**Current validation:** all **53 native suites completed and passed**, with
**1,496,451 assertions and zero failures**. All original case loops compare
directly with native C, including native terminal/layout bytes, regex diagnostics
and complete sorting callback traces. The native reference is unchanged; fixes
are in JS/runtime/ABI code. The earlier 32-pass/19-fail run exposed these defects;
later reports that accepted platform-specific results were rejected and are
superseded. Current evidence is
`.cache/native-existing-runs/29670-1794291036512/results.json`.
The final run's exact completion/pass/failure counts are also recorded in
`.cache/native-existing-results.json`; per-run logs and results are isolated
under `.cache/native-existing-runs/<run-id>/`. Assertion reports distinguish a
suite that finished its cases and found mismatches from one that crashed,
failed to load, or stopped before completion.

The same built game passes integration and all 44 unchanged public recordings:
792,838 RNG calls, 11,405 screens/cursors/cells and 1,483 animation frames match.
`scripts/test-native-library-differences.mjs` separately executes 14 native-C,
Emscripten-C and JS cases covering pointer formatting, overflowing bribe scans,
ERE parsing/errors/matches and calendar limits. It requires JS=native and
explicitly retains each observed SDK difference; ordinary shared cases must
match in all three. The native terminal transport test checks both compilers'
actual layout descriptors and OS-boundary conversion. Both tests run in the
full native command. This is the tested configured macOS C behavior, not a
claim of full native OS or arbitrary locale/TZ emulation.

The native backend uses host Clang, libc and ABI through a test-only Node-API
library. It calls the original probe methods and reads/writes actual native
memory; it does not implement NetHack algorithms. Each instance loads a private
library copy so native globals remain isolated. Generated bindings preserve
64-bit integer bit patterns and translate their exported wire representation,
without translating native behavioral results. Source/header hashes reject
stale native binaries. Build commands and provenance are saved in each
`*-full-native-build.json` file.

The case loops, input tables and behavioral assertions remain in the existing
test files. Native mode collects assertion failures and exits nonzero after
later cases execute; Emscripten mode retains the original fail-fast assertions.
Native assertions, failed assertions, completed suites, and passed suites are
separate report fields. Calendar/date workers retain all five existing timezones.

Architecture-specific checks have explicit counterparts rather than simulated
Wasm behavior: native allocation requests are measured while the same allocation
operations execute, and the native stack pointer is checked before/after each C
call. Native address zero cannot be inspected as a Wasm guard page; the existing
NULL-output case instead verifies that the native call returns safely. The
version fixture's intentionally mutable regex identifier uses writable native
storage. Its NULL banner case calls the upstream function indirectly so the
probe can observe the return without its `NONNULL` annotation removing the
caller's guard; this is invalid game metadata, not a claim about a valid live
game state. The native clock fixture follows the test's simulated clock.

Native log files use an isolated directory under `.cache/native-fs/`, retaining
host stdio behavior. The HACKLIB device tests use the existing controlled device
callbacks around the real native C copy algorithm; ordinary descriptors still
use host syscalls. Exper's intentional assertion cases are captured through the
host's assertion entry point as well as Emscripten's. These are fixture changes,
not game changes.

The full native reference shares the prepared configuration headers and the
existing controlled dependencies. Most algorithm sources are byte-identical to
upstream; calendar/date/RNG/terminal setup and the newly ported deterministic
sort retain their documented recorder changes. Full native logging/recording
cases therefore target the **native patched recorder**, not a pristine whole
game. The older supplemental pristine-source checks for four TUs remain
historical additional evidence and do not cover every full-suite case.

Representative unresolved differences include native vs Emscripten pointer
formatting, calendar parsing/DST, regex diagnostics and terminal ABI/constants,
overflowing bribe input, and some property/callback branches. These results
require investigation; a failing suite is not automatically a single port bug.
No new full-game recording score is claimed.

## Compression service and recording profile

The default build calls `js/services/unix-compress.js` through the dependency
bridge and MEMFS file adapter. NetHack retains its `.Z` filename handling,
cleanup, failure prompts and statuses 0/1/2. Configured encoding is byte-identical
to pinned ncompress 5.0, and native compress/uncompress interoperate. The original
vendored codec remains available for diagnostic C builds and reference tests;
see [vendor/ncompress](vendor/ncompress/README.md). .Z has no checksum, so not
every damaged stream is detectable.

`js/recording-profile.js` centralizes virtual HOME and sysconf values. Defaults
use the contest-documented recording HOME, WIZARDS=* and no SUPPORT override.
The wizard default is inferred from observed debug access/no named contact list,
not verified historical configuration. It permits any virtual user to debug;
the host account and virtual UID/GID are unchanged. NetHack reads the real
virtual .nethackrc/sysconf and generates its own text and pagination.

| Override | Meaning |
|---|---|
| TELEPORT_RECORDING_HOME | Absolute virtual HOME containing .nethackrc |
| TELEPORT_RECORDING_WIZARDS | NetHack sysconf WIZARDS value; default * |
| TELEPORT_RECORDING_SUPPORT | Optional NetHack sysconf SUPPORT text; empty omits it |
| TELEPORT_RECORDING_EPOCH | Recording clock for inherited DST policy, described above |

All 44 public sessions now pass. Additional codec, profile and prior regressions
run through `bash scripts/test-wasm.sh`. The frozen harness is unchanged;
passing public tests does not prove arbitrary or hidden-case equivalence.
