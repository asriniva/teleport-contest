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

**Current change:** shadow capture is again the default. The build retains
NetHack's TERMINFO/TERMLIB path and links real wasm64 ncurses terminfo, using a
pinned macOS xterm-256color database entry. The earlier ANSI shortcut and custom
tputs stub are removed. Public results after recorder encoding, bones and recording-clock fixes:
**44/44 sessions**, **11,405/11,405 screens**, **792,838/792,838 RNG calls**,
**1,483/1,483 animation frames**; no
runtime errors. Capability parity and timezone/macOS checks pass. The historical
22/44 shadow+ANSI and 0/44 Ghostty+ANSI scores describe the earlier builds.
See [active changes N01–N05](../../UPSTREAM_DIVERGENCES.md#current-status-shadow-capture-and-real-terminfo).

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

## Temporary terminal backend

Ghostty is retained only for explicit diagnostic use; it is no longer the
default or downloaded by normal setup. To enable it:

```sh
bash nethack-c/setup-terminal.sh
TELEPORT_TERMINAL=ghostty bash scripts/score-wasm.sh
```

The existing `write(bytes)`, `writeByte(byte)`, `snapshot()` and `dispose()`
interface remains available for replacing this optional emulator with pure JS.
Its Unix tty LF conversion, G1 initialization and serialization choices are
listed under G01–G08 in the register. They are not used by shadow capture.

`bash scripts/test-wasm.sh` compares the actual native and wasm64 terminfo API
results, verifies default shadow capture, and runs timezone/macOS regressions.
With explicit Ghostty mode it additionally runs the emulator's focused checks.
The frozen harness and recordings remain unchanged. Browser integration is
unverified.

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
