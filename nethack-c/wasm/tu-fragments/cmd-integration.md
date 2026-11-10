# CMD125 / J131 frozen handoff

Status: source implementation and isolated configured Emscripten comparison only.
Native C, production, full-game, and public recording validation remain pending.
Do not report these component results as native equivalence or all-path coverage.
No selected/shared/frozen source or build/harness files were edited by this author.

## Source and ABI

Pristine `nethack-c/upstream/src/cmd.c` equals prepared source byte-for-byte:
191110 bytes /5704 lines, SHA256
a14c0fc8706bd9957f8f4aab7f9e2abbd30eb5f4e43166b90a8bfeb25094a7ce.
Actual production memory64 CPP/AST inventory uses cwd TREE/src, input basename
cmd.c, O2-g, compile-defines.json, prepared and ncurses includes and the forced
native-terminal.h. It confirms148 functions/102public/46static in source order;
all original formals/comments preserved, no name exceptions or function headers.
Two exact source-private anonymous records receive header aliases cmd_misc_key
(original RecordDecl offset74276) and cmd_spkey_bind(offset106464); these are type
aliases, not extra algorithms. The private menucmd enum is copied as a type/constant
header under the hybrid guard. Native helpers contain no CMD algorithm fallback.

56 records/197 actual accessed fields,45 globals;270 fixed dependency names +12
variadic names/131 fixed typed vararg sites;282 total names includes96 initializer-
only names.172 true native function identities (48 source+124dependency) and13
indirect callback types cover119 indirect source callsites; the typed coordxy
predicate designator adds its actual int(coordxy,coordxy) identity.22 logged RNG
expansions preserve function/line/basename provenance; no display RNG.
All1,409 actual JS field accesses checked against197 native typed paths, including
rm.doormask macro ->rm.flags. No untyped alias or generic args.map(ptr) dispatcher.

10 TU data factories plus21 local static initializers remain JS-owned. C backing
is zero-only and uses compiler types/sizeof/fields.681 unique source literals use
exact derived12778-byte storage. Function-pointer arrays are recognized BEFORE
pointers: move_funcs[10][3] is240bytes, each row24, each element8.16 actual
ext_func_tab* increments use sizeof48;9 char* increments scale1. Actual AST has
zero pointer compound +=/-= and zero dereferenced ++/-- operands, guarded.
The2 fixed64 params are set_occupation.xtime and get_count.maxcount; native
get_count.count is long*, not Number. Native time_t/getnow/timet_delta, size_t,
long and callback unsignedlong stay BigInt. do_screen_description's coord is
passed by VALUE through teleport_cmd_screen_description(*coordPointer,...),
never by raw JS pointer to an incompatible C signature. Full queue/union/coord
record copies use native size and real memory, not JS replacement objects.

## Public startup is required

Three PUBLIC objects extcmdlist[171], levltyp[39], unavailcmd[26] are defined ONLY
in separate cmd-public-storage.c, with zero values. This storage TU MUST remain
separate from all readers and MUST NOT use LTO. unavailcmd retains its true const
C declaration and is placed in a writable data section for JS initialization.
Putting const zero storage together with optimized readers can fold zero reads.
No initialized C source table mirror is supplied.

The JS library registers addOnInit to call Module.nethackPorted.initializeCmd
before any Wasm constructors. The pinned SDK preamble initRuntime runs ATINITS
before __wasm_call_ctors. Private cmd-fixture-foreign.c is a separate O2/no-LTO
reader with a real constructor, checking all3 public objects and a function
identity, before ANY original CMD function is invoked. Seven observations plus
first-command text match C. The omitted-init negative fails the SAME comparison
with actual0n versus C35n; ctor is NULL-safe, so this is an assertion, not a crash.

## Runtime integration, unapplied

Use cmd-registry.json as a fragment; it includes required nativeStorageSources.
Do not apply this author-private fixture as production support.
- Main namespace imports original exports as cmd. Import initializeCmd and callCmd
  from cmd-runtime.js. Expose initializeCmd(services) ->initializeCmd(services,
  TU layouts.cmd,cmd) and cmd(services,name,...args)->callCmd(services,TU layouts.cmd,
  cmd,name,...args). No additional generic args.map(ptr): callCmd preserves its
  actual2 long parameters via schema, returning pointer results as BigInt.
- Both methods share the owned runtime WeakMap keyed by stable Module identity.
  The forwarding Proxy stays stable and resolves current services; nested calls
  and throws restore previous services in finally. Initializers run once per
  Module. Do not replace with Object.setPrototypeOf or pin initial services.
- Include cmd-support.c ONCE in production tu-support.c and shared layout writer;
  it includes cmd-types.h and cmd-source-data.h. Compile cmd-public-storage.c
  separately via nativeStorageSources, noLTO. Never duplicate its definitions in
  common support. The actual production cmd.o must be excluded in favor of imports.
- Add layout import/export for scripts/tu-cmd-layout.h /cmd_layout, retaining signed
  uint64 metadata decode for ordinary signed keys; source constants are compiler-
  derived. Source-specific TELEPORT_CMD_REFERENCE_TYPES is ONLY set after including
  actual cmd.c in this fixture. Never use a generic reference macro for its alias.
- Registry configuredFunctions=true /reference=pristine; no shared checker function
  or parameter rename exception is required. Parent owns registration/shared edits.
- Include production library ONLY nethack-c/wasm/tu-libraries/cmd.js, never private
  cmd-fixture-library.js, probe source/foreign ctor, wrap=free flag or fixture deps.

## Private probe integration and reproduction

.cache/cmd-first-pass/build.py compiles BOTH actual O2-g memory64 modes, forced
native-terminal/ncurses profile. Absolute included reference source gets exact
private -fmacro-prefix-map=REPO/scripts/../.cache/wasm64-build/tree/src/=
so __FILE__/RNG names match production cmd.c. No production flag change is needed.
Reference includes unchanged cmd.c; hybrid preprocesses it OUT, imports all148
original functions, links separate public storage and separate foreign reader.
Import audit verifies148 hybrid source imports/0reference imports, no fixture
or private observer import. Ordinary true dependencies are controlled C fixtures,
not original CMD algorithms. Source algorithms only execute unchanged C or JS.

Build exports are exactly .cache/cmd-first-pass/exports.json. To integrate shared
probes add that export list, -DHYBRID_CMD=1 only hybrid, and link the foreign reader
in BOTH modes /public storage ONLYhybrid as independent O2/nonLTO objects. This
self-supported fixture must be excluded from generic common support/auto-library
compilation. The private library is derived from the production library changing
ONLY free:(a0)=>_free(pointer(a0)) to ___wrap_free(pointer(a0)), adding its dependency;
-Wl,--wrap=free is used BOTHmodes. Wrappers record exact ownership and call real
__real_free. No prefree bytes or post-free/UAF payload claim is made.

Reproduce with build.py then TELEPORT_NATIVE_TESTS=0 CMD_PROBE_DIR=.cache/cmd-first-pass
SDKnode scripts/test-tu-cmd.mjs. Emscripten is an EXPLICIT diagnostic choice; default
referenceBackend('cmd',...) is strict native and does NOT fall back on absence.
No native oracle was built or run here. Adapter support/host va_list differences
and native callback/constructor/wrapping must be implemented and measured later.

## Verified scope and observation limits

Final current component:1562 comparisons,148/148 configured entry points reached
with defined controlled callers. This is entry/boundary coverage, NOT every path.
Positive cases include parameterized binding Snprintf/ownership, queue record
copy/pop/reverse/free, function identities/movement table strides, >2^53 counts,
menu/goto retry/cancel, original coordinate by-value copy under mutation by a
separate opaque C callback, positive dolookaround dependency return, native window
callback growth/reentry, service changes/restoration after nested exceptions,
independent Modules, unknownpointer64/scalar-address observer controls.

Critical source limitation: handler_rebind_keys_add declares uninitialized
cmdstr and Strcat reads it on ordinary/unbind branches. Source storage/control
remains UNCHANGED; no zeroing, Cflag, expected waiver or pass claim for those
undefined paths. Defined cancellation and CMD_PARAM+positive getlin/Snprintf paths
are exercised. No original loop is capped or simplified. Lua routines/window
choices/savelev/map/world dependencies are controlled fixtures; real Lua game
state, save/restore worlds, arbitrary bindings, hangup recovery and all menus/
world combinations remain unproven. Null/positive get_freeing_nhfile/stairway
contracts use typed pointers; tests are not independent dependency algorithms.

Trace observation of add_menu records the ACTUAL union a_ulong and its flags/
characters/text, rather than raw stack addresses of temporary union/glyph objects.
Comparison uses typed pointer-field normalization only: null, actual fixture pool
+offset, live/freed allocation identity+offset, actual global/data object+offset,
172 native function IDs and18 exact fixture native callback IDs. Char content is
bounded only in declared fixture literal/string/input regions or source literal
backing. reset_commands' actual dirchars/alphadirchars assignments identify its
source-declared11-byte char-array regions; extcmds_match's actual int** output
identifies its171-int retmatchlist and its ENTIRE684 bytes are compared. No generic
static-memory region or blanket byte scanning. Source head-reachable Cmd_bind
nodes are observed with Cmd_bind schema; other32-byte allocated queue records
use _cmd_queue schema. Every still-live allocation's full bytes are compared with
known typed-pointer slots normalized; actual frees/order and aliases remain exact.
Unknown pointers retain exact BigUint64 decimal AND raw8 bytes before any Number
conversion. Unsafe0x20000000000001 vs+2 mismatch is required without dereference.
Actual scalar long bytes equal to a fixture address stay RAW and a+1 fails.

Real native callback ->imported isok ->JS throw was tested at callCmd's JS entry
boundary, whose finally owns the complete callback stack. A diagnostic through
raw exported C probe_action left its separate16-byte native caller frame after
JS unwinding; preserved native-export-unwind-diagnostic.log is NOT a source
behavior discrepancy or automatic native-C caller resumability proof. No oracle,
source algorithm or compiler flags were changed for this instrumentation boundary.

Guards passed: original inventory/order/formals/comments;11 lexical scope tooling
fixtures; exactsource/102header+profile hashes; source/data/width/type/prototype/
macro provenance; actual native pointer AST audits; all1,409 JS field accesses;
actual linked Wasm import audit. Two unchanged-suite controls fail as required:
wrong JS omission of reset_pick fails reset_occupations trace; omitted eager init
fails foreign O2 constructor0. negative-inputs.json records6 exact before/after
source/test/reference hashes unchanged. Logs and hashes are retained, not waived.

Run guards: fragment cmd-check-source.py, SDKnode cmd-check-members.mjs;
.cache/check-cmd-source.py cmd (standardchecker logic using the recorded actual
production configured.c), SDKnode .cache/check-cmd-scope.mjs cmd; check-imports.mjs;
negative.py. Freeze manifest is .cache/cmd-first-pass/verified-inputs.json, captured
post-gate; no unavailable earlier pre/post unchanged snapshot is claimed.

## Exact parent register append text

PAR08-CMD source-faithful148/102public46static functions implemented preserving
original names/order/formals/comments/algorithms/control; no parameter exceptions.
56records197fields45globals,282deps including96 initializer-only,172 native designator
identities/13callbacktypes/119calls,22loggedRNG,10TU+21localJSinitializers12778literalbytes;
2 anonymous type aliases exact source offsets;16 structptrincrements/native48,
row24/whole240 functionarray,2fixedlongargs/native64typedABI.3public source tables
use REQUIRED separate nonLTO zero backing with eager addOnInit BEFORE optimized
foreign constructors; omitted-init unchanged check rejects0vs35. Current actual
O2-g memory64 C/importhybrid proof1562 comparisons/all148 defined entry points,
source/scope/member/import/width/data/prototype/CPP guards pass;wrongJS omission
fails unchanged reference trace with before/after6source/test/reference hashes.
Parameterizedbindings/queuecopies/frees/largecounts/byvaluecoord/nativecallback
reentry/growth/throw service-restoration/newservices/Module/raw64/scalar observers
pass within controlleddependency limits. Source's uninitializedcmdstr ordinary/
unbind branches remain untouched UNPROVEN; definedcancel/CMD_PARAM exercised.
RawexportedC caller resume after arbitraryJSthrow UNPROVEN, preserved diagnostic;
callCmd boundary finally tested. No native/fullgame/public/production claim or
selected/shared/frozen edits; final manifest records exact inputs/artifacts.
