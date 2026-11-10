# FILES TU115/J121 first-pass handoff (private only)

Status: final checks and hash manifest are recorded in `.cache/files-first-pass/`.
All 68 configured original source bodies are present (53 public / 15 private),
with original names/order/parameters/block comments, source data/control,
widths, pointer operations and callbacks. Source algorithms/data are JavaScript.
No selected/shared registry, builder, runtime, support, prepared source, native
compatibility service, frozen PAGER or other frozen TU was edited by this author.
Only this TU's unique sources/fragments and private cache were written.
Native OS execution, native subprocess behavior, full-game/public and uncontrolled
foreign-dependency compatibility remain pending; these are Emscripten C checks.

## Provenance and active configuration

Pristine files.c SHA256:
`5295af5df75ed1f67c9898d9d56a2cad6a35da68e511b5e5ab35886db6f9f2a5`.
Prepared compiled files.c SHA256:
`460967cdbc2c5c73d29e7148efcb8ee4c3a60fe548a152fe3e4a3f5fe549e96d`.
The inherited prepared-only patch inside docompress_file dispatches to external
teleport_compress_file under __EMSCRIPTEN__; the pristine/native fork/exec/wait/
signal subprocess arm is under the else and inactive here. This port preserves
the actual prepared dispatch; it does not claim the executable is pristine.
Private `prepared-vs-pristine.diff` records the exact inherited change.

Actual production inventory profile is memory64, current compile-defines.json,
forced native-terminal.h, prepared includes, ncurses includes, cwd TREE/src,
input basename files.c. COMPRESS=/usr/bin/compress, extension=.Z, SELECTSAVED,
NO_FILE_LINKS, USE_FCNTL, INSURANCE, SAFERHANGUP, LIVELOG, DUMPLOG_CORE, ALTMETA,
UNIX, TTY_GRAPHICS, HANGUPHANDLING, DEBUG, NODIAG, MACOS and __EMSCRIPTEN__ are
active. PREFIXES_IN_USE, ZLIB_COMP, SFCTOOL, DLB/backends, Windows/VMS paths are
inactive. SAVE_EXTENSION is the original empty string. fqname and prefix
validation retain their original configured simple bodies; doconvert_file
retains the original configured return-TRUE stub. No inactive implementation
was invented, enabled, counted or silently substituted.

## Integration-owner edits only

The exact registry proposal is `files-registry.json` in this folder. Use
reference:prepared and configuredFunctions:true. There are no parameter-name
checker exceptions and no source-owned public initialized globals. No startup
hook is required: zero-only private backings are initialized by JS before the
first FILES source entry, separately per Module, with no malloc/OOM path.
All initialization helper calls are typed/storage-only and cannot reenter.

Central runtime: import `{callFiles}` from `./files-runtime.js` and dispatch
`files(services,name,...args){return callFiles(services,name,...args);}`.
Install that dispatcher in Module.nethackPorted before any source call.
Runtime metadata is inline, with no JSON-module import and no external layouts
argument. Add `files: []` to the layout-writer's fields mapping; no special
layout decoding is needed. The runtime queries the compiler's indexed
teleport_files_layout helper and checks exact Number conversion, LP64,
signed char and little endian. The guard rejects unconfigured scalar types.

Compile `files-support.c` ONCE as its own production storage/ABI object through
the existing nativeStorageSources contract, alongside JS imports and excluding
original files.c. It holds only typed fields/globals/function addresses,
actual variadic/callback ABI invocations and zero-only fixed backings/literals.
Do not also include it in common tu-support.c. There are no initialized C
source table mirrors and no FILES algorithm fallback. Its sfstatus_to_msg
mirror is a type-only two-field ABI declaration; actual reference source size
checks use TELEPORT_FILES_VALIDATE_ORIGINAL only AFTER that original source
include, not the generic TELEPORT_REFERENCE_TU flag. Support-only generic
reference syntax validation passes independently of private declarations.

Only three source callback identities are needed: true proc_symset_line,
public proc_wizkit_line and private strcmp_wrap. The latter uses the native
teleport_files_strcmp_wrap JS import with its original const-void-pointer
signature; all other private aliases are available for fixture entry checks.
Callback helpers retain actual Clang-qualified function-pointer signatures,
including nested const, rather than a guessed canonical pointer prototype.

Standalone shared builder: add probes['files']=([], ['call', 'reset', 'clear', 'option', 'buffer', 'env', 'pointer', 'open', 'record', 'trace', 'stack', 'uid', 'snapshot', 'nhfile', 'global', 'layout', 'address', 'write', 'read', 'close_stream', 'attach', 'observe', 'offset', 'position']).
Add FILES to the self-contained hybrid list which excludes common native-libc-
library injection for this private fixture, and to the reference list defining
TELEPORT_REFERENCE_TU instead of adding original files.c as a second object.
This fixture includes original prepared files.c only in reference mode and
includes its support itself in both modes; DO NOT append support separately
for these standalone links. The fixture supplies private reference wrappers.

Use forced native-terminal.h, ncurses includes, -O2 -g memory64, 1MiB stack,
modular Node, growth, and exports HEAPU8,FS,stackSave,stackRestore. Link genuine
prepared hacklib.c and strutil.c dependency objects. Both modes use
-Wl,--wrap=fcntl and -Wl,--wrap=sscanf for explicit error/SP observations;
wrappers forward ordinary operations to real libc fcntl/vsscanf. Test sleeps
are a controlled dependency and do not actually wait. Exact reference-only
artificial include path macro map is:
`-fmacro-prefix-map=${ROOT}/scripts/../.cache/wasm64-build/tree/src/files.c=files.c`.
Production compilation stays basename files.c with no changed production flag.
The map preserves full actual RNG origins files.c:3461/3468:choose_passage;
Snprintf retains make_converted_name and closing line2151.

Invoke shared standalone comparison with
`FILES_PROBE_DIR=.cache/tu-probes <SDK node> scripts/test-tu-files.mjs`.
Without that explicit env, the owned test defaults to `.cache/files-first-pass`;
do not accidentally reuse private artifacts when reporting a shared proof.
The test reads all inventory/ABI metadata from owned files-schema.json, not
private schema cache. TELEPORT_NATIVE_TESTS=1 rejects before creating Modules
because a native fixture is absent. Do not add referenceBackend:native or
present these checks as native. Include all owned sources/fragments/probe/test
and actual compiler dependency inputs in integration provenance.

## ABI, scope and pointer details

Function entry/implicit casts use actual configured scalar widths: signed8
boolean/char/xint8, signed16 xint16, int/unsigned32, LP64 signed/unsigned64.
ll_type, clocks/birthday/moves, object worn masks and NHFILE rcount/wcount keep
BigInt width. Source `%` after unsigned birthday conversion preserves C's
low32 behavior. Compound assignments honor computeLHSType (including unsigned
ln += size_t strlen), not only destination width. char** indexing and pointer
increments scale by8; the two source pointer += sites are char* scale1.
Valued logical operators short-circuit and canonicalize C int0/1.

Original source frame slots are reserved once at each function entry, and
source declarations refer to the exact keyed slot; original initialization
stays at the original point. This matches the fixed-frame C-library sscanf
stack-delta witness instead of reserving filename[BUFSZ] on first matching save
or allocating uid repeatedly. Reentrant/recursive entries have distinct Maps
and native frames, with finally restoration. This is not a claim that every
optimized C stack byte/address or undefined/uninitialized value is identical.

Static nh_basename.basebuf, two distinct mutable hexdigits arrays, bei, sf2msg,
conversion filenames/cvtinit, lockfd and flock have zero-only fixed C backing;
JS owns exact original initializer decisions/data. Public pointer/output
parameters retain original native identities. Nullable Is_special/readobjnam
returns stay raw typed addresses; field accesses call exact C projections.
Every callback/windowprocs field is read live. Heap views refresh after growth.
Empty source literal addresses are stable and non-null. Source-local JS calls
retain function scope and native pointer alias behavior.

Observation-only unsafe pointer witnesses use the colliding Number pair
2^53 and 2^53+1: typed BigUint64 read precedes classification, preserving exact
decimal/raw8 bytes for unknown values without dereferencing. Address-shaped
scalar bytes and padding remain raw. Bones-id output is independently checked
to alias the actual typed bones array at its original offset before decoding.
Runtime dereferenceable pointers reject values beyond the exact JS integer range;
no >53-bit linear-memory dereference is claimed. Native C helpers snapshot full long64 NHFILE counts and actual fd/FILE cursor
positions; the rewind fixture starts both cursor styles at3.

## Evidence and limits

The final unchanged-C suite passes 1,420 checks and invokes every configured
source body, using real libc filesystem/stdio, directory enumeration, sscanf,
fd/FILE rewinds, qsort/private callback, output/error cleanup and genuine
hacklib/strutil functions. A positive sorted-save-name assertion prevents a
null-only directory test from masquerading as parser/comparator coverage.
Real tribute rendering performs6000 C output callbacks with constant stack
delta; directory parsing performs32 positive save extractions/scans and qsort.
Other cases cover encode/decode capacities and signed bytes, save/bones paths,
LP64 extremes, signed8 passage return, all original RNG origins, codec boundary
statuses, locks/retries/nesting/HUP, wizkit/symbol config callbacks, logs,
callback growth/reentry/mutation/throws (the bridge checks its own frame before
the external fixture cleanup checkpoint), static alias overwrites and Module
isolation. Unsupported scalar and unsafe metadata inputs reject explicitly.
Source checks preserve all original/prepared comments and boundaries; fresh
production CPP/AST guards cover377 MemberExpr aliases,47 compound/inc/dec nodes,
actual callback qualifiers,10 static initializers and2145 literal bytes.
Import audit proves0 TU JS imports in actual reference and68 in hybrid, with
original source present only in reference dependency inputs.

Three private wrong-JS controls fail the unchanged original expectations and
reference Wasm: unsigned signed8 passage read; Number-rounded long ll_type;
accumulating uid automatic cells. Exact diagnostic logs and before/after
reference hashes are in negative-proof.json. coverage-history.json records
that the initial unsigned-return negative unexpectedly passed the earlier
1,416 checks, then a valid explicit native signed8 context closed the coverage
gap; earlier functional counts were not negative-proof claims. No expected
output normalization, platform waiver or substituted oracle was introduced.

The fixture controls game/config/object/clock/signal/termination/codec/RNG foreign
boundaries. The codec fixture copies bytes to witness dispatch/cleanup and
injects status codes; it does NOT validate production compression bytes.
The native subprocess arm, real multi-process lock contention, native UID/
permissions/platform stdio, native directory ordering, native compiler operand
ordering, full native executable, production build and public/full-game
behavior remain untested here. Calls violating declared nonnull contracts,
out-of-bounds files, undefined signed overflow/uninitialized reads and other C
UB are not portable equivalence claims. The bounded independent parent review
reported no concrete issue in sampled functions/boundaries, not an exhaustive
proof. Parent owns promotion and all shared/native/public gates.
