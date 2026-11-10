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
FR03 path. Real ncurses terminfo and the remaining Wasm engine are unchanged. See
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

Both Lua 5.4.8 and NetHack are compiled and linked with `-sMEMORY64=1`, true
64-bit WebAssembly with 64-bit pointers and longs. Compile-time assertions in
`bridge.c` enforce the LP64 layout. The SDK supplies Node 24 for execution;
Node 22's default runtime does not enable memory64. The scoring wrapper selects
the SDK runtime, including for scorer child processes.

The build verifies upstream commit `16ff59115315917b93185d026aeefea06db9b0f4`,
applies the existing six recorder patches, and pins `SOURCE_DATE_EPOCH` to
`1777723200`. It first builds the native recorder and data generators, then
builds Lua and NetHack for wasm64. All work happens in `.cache/wasm64-build/`;
the upstream submodule is never edited. The generated module and Wasm binary
live under `js/wasm/`; `build.json` records the compiler and binary checksum.
Run the default build for a clean rebuild; `--resume` is a development shortcut
after the native preparation stage has already succeeded.

The terminal path keeps NetHack's original terminfo capability lookup and uses
ncurses 6.5 compiled to wasm64. Its real headers and library replace the ANSI
bypass and stub tputs. A pinned entry copied from this Mac's native database is
embedded in MEMFS; TERMINFO points to it and LINES/COLUMNS specify 24/80. Native
macOS reports ncurses 6.0; historical database/library identity is unverified.
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
The game logic and PRNG remain the patched C implementation. Data files are
embedded in the Wasm artifact. Each segment gets a fresh module and MEMFS;
changed files are serialized through the frozen storage API. The transient-file filter preserves bones; an in-process ncompress library
provides native-compatible .Z compression. All public save/bones sequences and
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

## Native C parity coverage

`npm run test:native` (or `bash scripts/test-native-tu.sh`) rebuilds and runs
shared behavioral scenarios for every one of the **50** registered ported C
translation units. To select TUs, use `bash scripts/test-native-tu.sh were rnd`.
The main `test:wasm` command also requires these checks to pass.

Validation on 2026-11-09: **50/50 native scenario groups**, **106,676 observations**,
all four additional pristine-source variants, and **50/50** existing detailed
Emscripten suites pass. An intentionally mutated JS RNG is rejected; source
preservation and lexical-scope checks pass.

Each scenario is compiled three ways: a real host executable using the native
Clang/libc/ABI, Emscripten C, and Emscripten C calling the JavaScript implementation.
The native executable produces fresh expected output. Tests compare results,
string/byte content, fixture callback traces, RNG consumption and selected state;
they never compare process addresses. Missing binaries, crashes, empty output,
mismatches, changed source or stale case files fail the test. Per-TU build
commands/source hashes and mismatch transcripts live under
`.cache/tu-probes/native-oracles/`; `.cache/native-tu-results.json` records results.

The previous `test-tu-*.mjs` suites compared **Emscripten C against JavaScript**.
Their result labels now say so. Native coverage supplements those detailed
suites; it does **not** replay every existing assertion on the host. Existing
full-game recordings came from the native **patched recorder**, not pristine
NetHack. The terminfo and compression interoperability suites already used
native libraries/tools independently.

For 46 TUs, the compiled algorithm source is byte-identical to upstream, checked
at build time. Four TUs also get a separate executable compiled directly from
the pristine upstream algorithm:

| TU | Native upstream check and deliberate recorder distinction |
| --- | --- |
| `calendar` | Explicit-date formatting/parsing matches upstream. A fixed fixture clock makes native execution reproducible. Separately assert that upstream ignores `NETHACK_FIXED_DATETIME` while the recorder honors it. |
| `date` | Version/build metadata matches upstream with compiler build time pinned via `SOURCE_DATE_EPOCH`; the prepared source retains its inherited fixed-banner patch. |
| `rnd` | Seeded core/display draws, dice, luck and scaling match upstream. Upstream has no recorder logging inspectors, so those unused probe inspectors are omitted from its test wrapper, without adding fake logging functions. |
| `unixtty` | Terminal state transitions match upstream with NOMUX disabled. The existing Emscripten suite still tests recorder-only NOMUX synthesis; that path is not a claim of pristine upstream equivalence. |

These are isolated **native algorithm** oracles, sharing the existing fixture
callbacks and prepared NetHack configuration headers. They are not pristine,
independently configured whole-game executables. Native support excludes the
Wasm-to-JavaScript ABI adapter. Two harmless global-storage fixtures remain for
getline/ioctl; version uses the existing controlled metadata/regex dependency.
Native stack/heap helper headers provide a real frame address and a fixture
allocation size only; Wasm linear-memory growth and stack restoration remain
covered by the detailed Emscripten tests.

Host-specific constants are checked semantically: terminal traces validate
`_PC_VDISABLE` before spelling it symbolically, and system initialization checks
both configured `PANICTRACE_LIBC` branches, including preservation when absent.
The native scenarios run in UTC; the existing Emscripten calendar suite retains
its five-timezone coverage. These checks establish only the exercised behavior,
not exhaustive native equivalence or a new full-game score.

## Compression service and recording profile

`compress-service.c` calls pinned ncompress 5.0 in process, compiled for wasm64.
NetHack retains its `.Z` filename handling, cleanup and failure prompts; only
fork/exec/wait is replaced. Codec code is vendored unchanged with checksums and
license in [vendor/ncompress](vendor/ncompress/README.md). Native compress and
uncompress interoperate with it; compressed bytes need not be identical across
implementations. .Z has no checksum, so not every damaged stream is detectable.

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
