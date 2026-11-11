# UNIXMAIN138/J144 — private handoff

Status: FROZEN. Final734 checks pass across182 differential cases/all15 bodies,
13 real callMain scenarios plus independent direct-entry ExitStatus proof.
Four wrong-JS variants reject the unchanged original C/source/fixture/suite.
Source/CPP/comment/data/metadata/scope/import/ABI/strict-native guards pass.
Integration is unapplied. No native executable,
full-game or public score verification is claimed. The standalone test rejects
anything except TELEPORT_NATIVE_TESTS=0 BEFORE runtime/factory imports. Undefined
means native required; explicit1 also rejects, rather than mislabeling EmC.

## Exact source and configuration

Reference is PREPARED sys/unix/unixmain.c, not pristine. Prepared SHA256:
c029938f38987424493931fb7719abdb43a6deb82289a393c2bd94fa74c41bfa.
Pristine SHA256:
9c8a9a498acaffee6ce62d44a5e07977d2ec4852f29a77a1fbabdea0fd9f2165.
Production Make rule988-989 compiles input ../sys/unix/unixmain.c from TREE/src,
with -O2 -g memory64, current compile-defines.json, forced native-terminal.h and
actual ncurses headers. This is NOT input basename unixmain.c. Configured CPP
SHA256 e0f9655beb4f60600187f472ad1cdf47dda9d005cc8984faa19a0c7c6ec088d3.
The owned fresh CPP guard checks this exact profile/input, active and inactive
macros, complete104 prepared/101 pristine comments,15 original function names,
source order and formal names. No reserved-name exception is needed.

Configured15 functions (12 public/3 static): main,process_options,chdirx,whoami,
sethanguphandler,authorize_wizard_mode,authorize_explore_mode,wd_message,
append_slash,check_user_string,get_unix_pw,get_login_name,sys_random_seed,
get_nhuuid,free_nhuuid. PANICTRACE remains active despite NOPANICTRACE flag;
SA_RESTART/SIGXCPU24/HANGUPHANDLING/CHDIR/SYSCF/NEWS/MAIL are active.
NHUUID/PORT_HELP/APPLE/Linux/SECURE/DLB/WINCHAIN/TTY_PERM_INVENT are inactive.
get_nhuuid is the original configured empty body; free_nhuuid clears all37 bytes.

Inherited differences retained exactly, never presented as untouched native:
W08 __EMSCRIPTEN__ virtual root account uid/gid0,/home/player,/bin/sh; native
getuid/getpwnam/getpwuid/account-cache code remains in JS after the unconditional
return and is unexecuted in this profile. R01 NETHACK_SEED strtoul(base10) early
return and its strong-flag preservation remain. R03 rng_log_init startup call
remains. Actual native-host account/terminal/signal/entropy policies are unproved.
No host account shortcut, seed normalization, termination cap or policy fix added.

## Root integration recipe (no shared files changed by author)

Use unixmain-registry.json proposal, source sys/unix/unixmain.c, reference prepared,
configuredFunctions true, probeContext false. Install central dispatcher before
factory execution:
`import {callUnixmain} from './unixmain-runtime.js';`
`unixmain(services,name,...args){return callUnixmain(services,name,...args);}`
Layout writer entry `unixmain: []`: runtime decodes compiler-indexed helpers,
checks LP64/signed-char and exact safe Number layout conversion itself. Every
source C.key/field/size/static/literal/callback index has compiler metadata or an
explicit transport helper;69 distinct foreign names=65 ordinary+4 vararg targets
(config_error_add,pline,You,error),13 typed vararg sites,5 window callbacks and
2 typed native function identities (done1,hangup). No args.map(ptr).

Compile unixmain-support.c ONCE as separate nativeStorageSources object; do not
include it again in common tu-support.c. Compile unixmain-entry.c ONCE hybrid/game
only as second nativeStorageSources object. Remove original unixmain.o from
HOBJ, using registry source stem as normal. Support contains typed field/global,
header __isspace, callback/vararg ABI and ZERO-only private/literal backing.
No original TU algorithm or initialized C mirror is linked in hybrid. The source
private locals are invisible after their function boundaries: actual source/CPP/
initializer guards anchor sizes/data; standard passwd48/sigaction152/header type
asserts are compiler-derived. Generic TELEPORT_REFERENCE_TU support-only compile
passes without original source; no private assertions leak into unrelated TUs.

The entry shell is exactly `main(argc,argv) -> teleport_unixmain_main(argc,argv)`.
The latter is a typed JS import selecting source JS main. This shell contains no
startup policy. Direct JS __main_argc_argv import linked, but Emscripten
HAS_MAIN only recognizes WASM_EXPORTS (tools/emscripten.py128); its factory then
threw `ReferenceError: callMain is not defined`. Immutable original log:
.cache/unixmain-first-pass/direct-js-entry-failure.log SHA256
6e6e753126a2cd444b15d8edca1ed52162c8428d50a8a2fdabda9ec05dba2ecb.
The first direct-alias binaries were overwritten before preservation; their
hashes are unavailable, and no old binary identity is claimed. Parent announced
and recorded the conditional one-call ABI-shell seam before its implementation.
Keep _main exported, normal callMain/argv/ExitStatus generation, INVOKE_RUN0 and
EXIT_RUNTIME1, with existing production runtime.js quit behavior. Native/public
entry compatibility is pending root integration, not inferred from this fixture.

No eager owned-public-storage startup: all3 original statics are private.
Per-Module JS initializes fixed native zero backing once: passwd48, pointer8,
get_login_name.buf256. Original root/home/shell data and all42 literals (672
source-derived UTF8 bytes incl NULs) are JS-owned. Independent separately compiled
O2 C consumer reads and mutates passwd through typed fields, proves stable
record/login-buffer aliases, uint32 UID/GID widths and Module independence.
Stable per-Module forwarding and call-scoped finally restoration handle nested
service objects, callback reentry and throws. Each automatic frame (including
source-local calls) restores its stack; original normal-only source restores
remain normal-only. main argc32/argv64 and dir pointer have native address cells;
early_options can replace all3, while gh.hname/ARGV0 keep original argv[0].
Every actual main/options caller validates argc excludes NULL, argv[argc]==NULL,
and non-NULL arguments before invocation. Native live snapshots independently
validate original argv[0] aliases before entry exits. Both backward restore joins
are uncapped and keep startup outside the retry region.

## Exact private build/test setup

Private build script .cache/unixmain-first-pass/build.py uses actual O2-g reference
source and hybrid exclusion, true libc and genuine separately compiled hacklib/
strutil; independent unixmain-consumer.c is fixture-only, not production storage.
Fixture defines controlled typed foreign game/window functions; real setenv/
unsetenv/getenv,chdir,chmod,umask,stdio,strtoul,free/exit remain actual SDK libc.
Signals are recorded typed callbacks, not real OS delivery. moveloop is a returning
controlled dependency so actual exit0 can be observed. Error callback intentionally
throws; real main ExitStatus and callMain status handling are also tested.

Both private modes ONLY add -sTABLE_BASE=2 to reserve raw signal sentinel1.
At default table base1 the tiny reference assigned hangup function index1, which
collided with SIG_IGN1 in the observer; it is not a production flag change or an
expected-result waiver. Immutable collision log SHA256:
9ba81add83db67c8d827f5deaf4d420974f794cc695f232ed0f3d1599db71431.
All signal handler comparisons classify known typed identities and zero ONLY
their8 pointer bytes; full remaining144 bytes are compared exactly. Unknown
64-bit pointers are retained exactly and never dereferenced. Raw colliding-Number
pair0x20000000000000/1 and exact decimal/8bytes reject Number-first rounding;
seed scalar equal to address bits remains a scalar. No broad raw-byte masking.

Shared probe builder must use the exact build.py recipe, export _main plus its
listed probe exports, FS/ENV/callMain/stackSave/stackRestore/HEAPU8, actual forced
native/ncurses profile, genuine deps and consumer separately compiled. Reference
includes source only; hybrid adds entry shell and owned JS library. Probe itself
includes support once: do not also add support.o to those fixture links. Shared
wrapper MUST set UNIXMAIN_PROBE_DIR=.cache/tu-probes and TELEPORT_NATIVE_TESTS=0
explicitly; otherwise the standalone diagnostic uses its private directory and
would not prove the shared pair. Reproduce using:
`python3 .cache/unixmain-first-pass/build.py --reuse-deps`
`TELEPORT_NATIVE_TESTS=0 UNIXMAIN_EVIDENCE_PATH=.cache/unixmain-first-pass/behavior-evidence.json .cache/emsdk/node/24.19.0_64bit/bin/node scripts/test-tu-unixmain.mjs`
Run owned source-check.py, check-metadata.mjs, private check-scope.mjs unixmain,
audit.mjs, check-abi.py, check-native-guard.py and negative-controls.py as recorded.

## Evidence corrections and limitations

The initial202-check corpus changed Module.ENV after libc environ initialization;
its USER/seed labels overclaimed branch coverage. Preserved superseded evidence
is superseded-env202-evidence.json. Final fixtures call genuine setenv/unsetenv
and independently verify actual C getenv before each environment-dependent case.
Exact C/JS comparisons plus independent original branch witnesses cover absent/
empty seed, strtoul overflow and >53bit values, empty/short/full fread files,
missing-file fallback, signed pid and full64 unsigned multiply, strong flags and
actual call order. No environmental result is normalized.

callMain mutates its args list by prepending thisProgram; the paired test now
clones caller arrays. Post-exit argv strings are no longer dereferenced: native
snapshots are copied while entry objects are alive. Those earlier observer errors
are preserved in shared-argv-postexit-lifetime-diagnostic.log. The pre-final615
snapshot pre-valid-argc-fix preserves both binaries/fixture/core/test/hashes:
one alternate early_options fixture counted terminal NULL in argc. Corrected
fixture excludes it and checks valid argv in native C and JS before invocation.
Original C, JS source algorithms and expected results were not changed.

Unreachable native account branches, real OS signal delivery, uncontrolled entropy
devices, full terminal/game startup/moveloop, foreign game policies, actual native
compiler and full/public game checks remain pending. Controlled dependency tests
do not prove those worlds or erase inherited W08/R01/R03 differences. No native
expectation waivers or platform-dependent pass rules were introduced.

## Frozen receipts

Final evidence: .cache/unixmain-first-pass/final-proof.json; full observation
corpus behavior-evidence.json; four rejected variants negative-controls.json;
source/metadata/import/ABI/native-guard logs and proofs in the same directory.
Correct actual compiler-input provenance includes160 inputs with prepared source
explicitly present; original88-input receipt remains unchanged and its omission
is recorded. Final hashes.json receipt covers all owned files, private histories,
actual inputs and compiled oracle pairs. Selected final SHA256 values:

js/ported/unixmain.js
b820cf47e52916feaa8cba5203714913fe9e6a4dee8a608b551b3311dd1b5e6a

js/ported/unixmain-runtime.js
ad26be79117ad1ea9c872eb693e50e39fc28c1164f8a5382e30b54c694f3a10e

nethack-c/wasm/tu-libraries/unixmain.js
a40b8a9c57070da2b0268d4e51e7100ad056738e03f24dd056fd8856619ce2aa

nethack-c/wasm/tu-fragments/unixmain-entry.c
315d89039a6bb3cc40f730da217156cd0899049a862706b4f047aba01ebcd2eb

scripts/tu-unixmain-probe.c
97df59b9637acd75969c6bcc126d40ea254f62945d463612961ae43cb9cd6a04

scripts/test-tu-unixmain.mjs
fa8e99004c240c29eca355263586a3da2d76a04b1c06815cabdc556c2a00c68f

.cache/unixmain-first-pass/unixmain-reference.wasm
b4f910a75a74d972d75e98cd90c7181e59b7409dd83e7183d53dec6619a67291

.cache/unixmain-first-pass/unixmain-hybrid.wasm
eae655485f61a6783d6ef4676fee4050475c82fdf4699ecb9ec25c0831dc63e5

