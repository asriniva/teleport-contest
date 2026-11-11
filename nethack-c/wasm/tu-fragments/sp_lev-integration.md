# SP_LEV131 / J137 unselected handoff

This is a configured **Emscripten C versus JS** component result. No native-host
reference fixture exists. Native, production, JS-Lua, whole-game and public
recording equivalence remain pending. The test rejects undefined or1
TELEPORT_NATIVE_TESTS before dynamic core/factory imports; only explicit0 permits
this diagnostic. Both rejection cases were checked with a nonexistent fixture
directory, proving no fallback to Emscripten. No expectation was relaxed.

Pristine and prepared src/sp_lev.c are identical198220bytes/6504lines, SHA256
91c684ab995f82d4775dcc83576abf36c25be5b2c205cddfaa46445328f4ce25.
142 configured functions (64public/78private) retain original names/order/formals,
all original block comments, source data, algorithms, loops, joins and returns.
No original SP_LEV C object/algorithm fallback, retry cap, inert Lua errors or
initialized C source-table mirror. Only two reserved LOCAL char declarations use
class_: create_monster range60085/name60090 ID0x927685d48 and find_objtype
range108327/name108332 ID0x926fc1d18. There is NO formal-name exception.

The actual production CPP/AST profile is cwd prepared TREE/src, input basename
sp_lev.c, O2-g MEMORY64, current compile-defines, prepared/ncurses headers and forced
native-terminal.h. The private include gets only its exact absolute-included-source
prefix mapped to basename sp_lev.c. No production compiler/profile change.
71 actual non-system compiler dependency headers are hash-bound; this does not
capture an entire external SDK/toolchain. Fresh full compiler AST/CPP guards pass.

80 actual member RecordIDs/376 fields expand to82initializer schemas/386fields.
The two extra native initializer types are luaL_Reg(name,func) and
nhl_sandbox_info(flags,memlimit,steps,perpcall). Full native declaration order is
checked; the four existing-record initializer fields additionally required are
object.x/object.y/object.invis and str_or_len.len (zeroobject at111025–111568).
Type-only source anonymous aliases sp_lev_room_type124387 and
sp_lev_trap_type135018, exact parent-member header aliases sp_lev_corridor_end
(corridor.src/dest), sp_lev_lregion_inarea and sp_lev_lregion_delarea, and the
function-local objclasspfx alias sp_lev_objclasspfx (source108679–108764,
constchar*prefix/charclass,16bytes align8) add no algorithm or initialized data.
Original source record/field/range metadata remains guarded.

33 true external globals;206fixed +4variadic dependency names/34 typed fixed
vararg helpers;40 actual source designator identities/4designator prototypes;
one actual indirect predicate call and its boolean(coordxy,coordxy) typed helper.
73 original logged RNG expansions preserve basename/line/function and expanded
macro order; no source display RNG. Guarded sites are not all dynamically covered.
11 TU+50 local static objects remain JS initialized into mutable compiler-typed
ZERO backing. There is no public source storage or separate public storage TU.
The actual Lua registration callback table is initialized before its C consumer.
395 unique source literals have exact source-derived4698-byte capacity.

The three fixed long inputs are get_unpacked_coord.loc, get_location_coord.crd,
and get_free_room_loc.pos. Native size_t/long/LuaInteger transport stays BigInt;
get_table_int_or_random and get_table_intarray_entry retain64-bit returns.
get_unpacked_coord returns an actual16-byte align4 unpacked_coord VALUE: core
snapshots bytes; binding signature vpji copies into the native sret address.
Actual C callers copy first/second returns and retain the first through subsequent
static writes; nested native callback/reentry also receives a distinct value.
No pointer alias is substituted for the aggregate return.

Addressed formals mapfrag_error.mf (two source sites), set_wall_property.prop and
set_wallprop_in_selection.prop get native argument-initialized cells, with positive
free-local-pointer and wall-bit callback witnesses.133 addressed scalar declarations
were audited:91 no-init automatic cells reserve stack bytes WITHOUT writes,
39 explicit initializers write their actual values, and3 formal cells write the
argument. Aggregate autos without a C initializer likewise reserve without zeroing.
Static zero initialization and explicit aggregates remain distinct. This does
not claim equivalence of arbitrary indeterminate C values. Two (*npoints)++ paths
have real native nonempty corridor counter witnesses. rm*8/mkroom*224 increments,
five u32 stores computed in native long, whole record copies/outrefs and native
aliases remain compiler-derived. Actual pointer-compound-assignment census is0.

## Final private result

Actual original-C/import-only hybrid O2-g memory64 pairs pass2625 comparisons,
all142 direct configured entries. Positive registered Lua callbacks require actual
status0; three expected real Lua errors compare exact messages/status separately
and then recover. Native C Lua+selvar.c+nhlsel.c are linked in BOTH modes; actual
l_selection_register and source l_register_des execute. This is not production
JS-Lua parity. The existing Lua archive is exact-hash-bound in dependency-hashes;
it was NOT freshly rebuilt by this author. Current build.py145 documents its
O2/MEMORY64/LUA_USE_POSIX recipe, but no retained original archive compile receipt
is claimed. External game/catalogue dependencies are explicit controlled fixture
models, including one human species, fixture objects, and a boolean load_lua model.
Mere linking is not presented as upstream catalogue startup or real file loading.

Covered: parser/name prefixes, map bytes/mutations/free ownership, source local
pointer argument copies, all source boundaries, Lua integer >2^53/outrefs, real
registration/predicate/selection/Lua nested callbacks, source record-copy and
sret snapshots, positive native strides/counters, real memory growth, nested
service override restoration, changed services/JS throw finally and separate
Modules. Raw native struct bytes are compared with only declared pointer slots
mapped to actual known regions/identities. Observations are not all world paths.

Pointer observation maps null, exact fixture pool+offset, actual globals/data,
tracked allocation identity+offset and40 actual native function identities.
The exact live lua_State pointer is recognized BEFORE allocation-region lookup;
it can reuse a freed game-block address. Char content is bounded only by explicit
fixture strings/input buffers or source literal storage, never generic static
memory. Unknown pointers use getBigUint64 before ANY Number conversion and retain
both exact decimal identity and raw8bytes; unsafe0x20000000000001 versus+2 differs
without dereference. Unknown char* is also covered. Actual scalar obj.quan bytes
that equal a fixture address stay raw, and+1 is rejected.

All still-live tracked allocations compare their full bytes. Declared object,
monster and mapfragment returns/factories and the gc.coder root identify typed
records; native selection_new/clone wrappers identify selection objects, whose
map pointer offset comes from actual offsetof. Other blocks compare all raw
bytes. Only source-active str_or_len.str contexts are treated as pointers; the
configured source never reads its len variant. This is not generic union guessing
or blanket byte scanning. Lua's internal VM heap/userdata headers are NOT globally
byte-compared. Exact frees/ownership/order are checked, dead payload is omitted;
post-free allocator contents or UAF behavior are not certified. Arbitrary raw C
export resumption after JS throws is not claimed; tested finally owns JS boundary.

Initial fixture diagnostics are retained: compile/type setup, local coord stack-
address trace (mktrap now compares declared coordinate fields), invalid positive
room caller missing required hx<0 sentinel (caller corrected), and the regex
boundary false positive on external rndmonnum(). No source or compiler waiver.
The wrong-code control changes only light_region's JS rm stride8→1 and fails the
UNCHANGED C/reference/hybrid/test state comparison. Nine before/after baseline
hashes remain identical; negative-receipt.json and captured failure log are retained.
Import audit confirms all142 source bodies are imports only in hybrid, and no
fixture observer was accidentally imported as a source function.

The allocator tracker correction was applied prematurely before parent review;
old pre-change binaries were overwritten and are UNAVAILABLE. No old hash or
preservation claim. Raw failure is retained. Parent reviewed actual Lua default
l_alloc/newstate/setallocf, announced/registered narrow scope, then approved it.
The unchanged genuine luaL_newstate retains panic/warning hooks; lua_setallocf
AFTER creation selects the same realloc/free semantics, with interpreter-only
n==0 frees sent to __real_free. Game __wrap_free and strict doublefree rejection
remain intact. Parent-pinned current pair/generator/input/log bytes were copied
before subsequent edits to allocator-reviewed-snapshot/receipt.json. Current
final proof is fresh after review, rather than the earlier provisional2376/138.

## Exact UNAPPLIED integration

1. Use sp_lev-registry.json as the unique registry fragment. It has startup
$teleportSpLevInit, configuredFunctions true, pristine reference, probeContext
false, typed ABI extra exports and adapterSources. Exclude original sp_lev.o.
There is NO nativeStorageSources/public-storage requirement.
2. Include sp_lev-support.c ONCE in normal common support and layout reader. Its
own types/data headers are guarded. Its TELEPORT_SP_LEV_REFERENCE_TYPES is defined
only by its actual self-contained reference fixture AFTER original source include;
never use generic TELEPORT_REFERENCE_TU to select original private SP data types.
Exclude this self-contained probe from generic common-support injection.
3. Main namespace imports `* as spLev from './sp_lev.js'` and initializeSpLev /
callSpLev from sp_lev-runtime.js. Expose
`initializeSpLev(services){return initializeSpLev(services,tuLayouts.sp_lev,spLev);}`
and `sp_lev(services,name,...args){return callSpLev(services,tuLayouts.sp_lev,spLev,name,...args);}`.
No generic argument pointer map. Stable per-Module forwarding + call-scoped current
services/finally is already implemented; fresh live heap/typed reads survive growth.
4. Add scripts/tu-sp_lev-layout.h /sp_lev_layout metadata. Decode signed metadata
with BigInt.asIntN(64,raw) BEFORE Number, reject unsafe round-trips. Source typedef/
anonymous initializer sizes and header alias record sizes are present. Initializers
use compiler declaration order/implicit zeros and tagged active union member.
5. Shared generic source checker needs a NARROW SP_LEV column1 definition option:
`re.finditer(r'^(\w+)\s*\(([^;{}]*)\)\s*\{',clean_c,re.M)` yields exactly142 in
actual production CPP/AST order, avoiding false nested rndmonnum() definition.
There is no arbitrary expected-name filter and no parameter exception. Run owned
sp_lev-check.py too: it checks fresh full production AST, JS exports/formals/all
comments, initializer fields/order, CPP/RNG, widths/source/data/member paths,
zero-only backing and copied unchanged lexical-scope logic/11 fixtures.
6. Shared probe builder can delegate exact private build.py modes with outputs
redirected/copied to its pair directory, or reproduce it byte-for-byte. Actual
exports are .cache/sp-lev-first-pass/exports.json. Link the real selvar/nhlsel
private objects and exact Lua archive in BOTH modes, and -lm; use native-terminal
forced include and the recorded basename map. Fixture-only link wraps free,
selection_new and selection_clone. Private library changes only direct dependency
routing to their native observation wrappers; NEVER use it in production. Use
production tu-libraries/sp_lev.js for game imports. No production C Lua archive,
Lua bridge/service or Lua backend selection change is authorized by this handoff.
7. Run `TELEPORT_NATIVE_TESTS=0 SDKnode scripts/test-tu-sp_lev.mjs`; override
SP_LEV_PROBE_DIR for shared pair location. Do not bypass strict native rejection.
Native-host ABI/stdio/jump/allocator differences require their own real fixture;
this handoff cannot supply a passing native backend. Main/game/public gates remain
root-owned and unrun here. No selected/shared/frozen input was edited by author.

Final commands/proof artifacts: sp_lev-check.py; private check-boundaries.py and
check-scope.mjs invoked by it; SDKnode check-imports.mjs; private negative.py;
explicit0 test.log; native-rejection-{undefined,1}.log. Final freeze manifest is
.cache/sp-lev-first-pass/verified-inputs.json; post-proof input/header/artifact
hash capture, not a nonexistent earlier before/after whole-run receipt.

## Parent register append text

PAR08-SP_LEV131/J137 implemented142 configured original source functions64public/
78static preserving names/order/formals/allcomments/algorithms/loops/joins/data;
only2 exact local char class_ renames, NO formal exception. Source/pristine SHA
91c684ab995f82d4775dcc83576abf36c25be5b2c205cddfaa46445328f4ce25 unchanged.
80member records376fields→82initializer schemas386fields;11TU+50local zero-backed
JS factories4698literalbytes;33extern globals206fixed+4vararg deps/34typed sites,
40native designators/4types/1actualindirect predicate,73loggedRNG. Three long
inputs/LuaInteger64,16byte sret/copied caller values,3formal4address sites,
91uninitialized scalar autos reserve-only,2derefcounter/4scaledptr increments,
5u32-long compute stores guarded. Actual original-C/importhybrid O2-g memory64
proof2625/all142 direct entries +positive status0 realLua callbacks, expectedLua
errors/recovery,nestedcallbacks/growth/newservices/throw/Modules/raw64/scalar/full
livepayload/ownership guards PASS within controlledworld limits. Wrong JSrm8→1
fails unchanged light_region state;9source/test/reference/hybrid hashes unchanged.
Fresh production AST/CPP/source/comment/formal/scope/type/data/member/import guards
PASS, narrow column1 source definition option required. Native fixture ABSENT:
default/1 reject beforefactory, explicit0 diagnostics only. RealC Lua archive is
same hash-bound dependency both sides, not freshly rebuilt or productionJS-Lua proof.
Lua allocator prematureapply/oldbinariesunavailable history retained; parentreviewed
same realloc/free via lua_setallocf after genuine luaL_newstate preservinghooks;
game free tracker unchanged. Initial diagnostics/current-reviewed snapshots kept.
Fullnative/game/public/production/allbranches/LuaVMheap/UAF remains UNPROVEN.
No shared/selected/frozen source/profile/build/oracle/harness changes by author.
