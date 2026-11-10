# DETECT staged handoff (not registered)

All 42 configured original detect.c functions (24 external,18 static) are in
js/ported/detect.js, in original order, retaining source function boundaries,
original fixed parameters except the two narrow reserved-name mappings below,
all original block comments, branches, loops, arrays and algorithms. The five
forward gotos join explicit labeled blocks: four outgoldmap jumps and two paths
into one implode tail (one source goto plus one normal branch). The shared tail
still performs original Tobjnam/useup/obj** clearing once. No source C algorithm
fallback or initialized C table mirror exists in the hybrid.

Pristine/prepared are byte-identical:85,268 bytes/2,418lines, SHA256
`d2b923635909fd59d4731ce59094a575a688f4421ff2056f9cb1759cb853c9e7`.
No shared registry, builder, metadata writer, runtime, support, selected/frozen TU,
Lua subsystem, default, native service, game or public artifact was changed.
The following recipe is UNAPPLIED and requires the coordinator's integration.

## Actual verification and limits

Actual final original-C and imported-JS hybrid **-O2 -g memory64** links pass
**1,267 comparisons**; all42 bodies are directly selected through the C caller/
real import ABI. Hybrid excludes detect.c and uses its JS library; actual Wasm
imports verify all42 source routines. Both modes force production native-terminal.h
plus actual terminfo includes. Source/order/parameter/comment and11-fixture
lexical scope checks pass. Fresh production AST/CPP/type/data guard passes42 body
fingerprints,38 records/133 accessed fields,239 macro definitions,22 logged RNG
expansions and2,688 literal bytes. Actual-JS-member guard covers1,708 accesses/
133 unique typed fields and rejects unchecked raw C aliases; exact native helper
read/write/address indices are checked too. Support compiles206 static type/
sign/width/prototype assertions. Final build emits only the SDK's two expected
DWARF/limited Binaryen optimization warnings from the actual -g profile.
The final proper suite,guards and negative control were rerun after the
unreachable-return cleanup,explicit volatile preservation and fixture tightening.
Earlier1,225 pre-cleanup checks are retained historical evidence,not the frozen
input proof. Final hashes are .cache/detect-first-pass/verified-inputs.json.

A wrong-code negative control zeroes only the rm.flags read result in a private
copy of the import library. The unchanged original reference and test suite fail
at openone trace:wrong JS emits `newsym:10:10;uninvis:10:10;drawbridge:10:10;`,
while C emits `newsym:10:10;uninvis:10:10;unblock_point:10:10;newsym:10:10;`.
No test expectation changes/waivers. Failure is retained in
.cache/detect-first-pass/negative-flags/failure.log. The proper library is intact.

Covered witnesses:normal/underwater/buried/swallowed map state and getpos outref;
recursive containers/class/material; nobj and nexthere aliases; all tested door
flag combinations/secret-door candig; trapped boxes/location scalar outrefs and
found counters; two coordinate parameter mutations through find_drawbridge;
trap callback short circuit; object** destruction/clearing through both implode
paths and explosion; lazy Maybe_Half_Phys consumes rnd(30) once; all five
impairment branches; source crystal-ball command dispatch and live level table;
signed distance narrowing;canonical long-worm pointer identity;
persistent trap unused fields and uchar counter wrap; display RNG versus unlogged bare-rn2 identities;
find/open native callback pointers/counter storage; search rnl sites;
complete synthetic object copies from a deliberately nonzero const seed;
complete rm save/restore despite helper mutation; saved64-bit detection status;
heap growth/reentry; JS throw stack/context cleanup; independent Modules.

Dependencies are controlled fixture worlds, not all game subsystems. RNG has a
controlled stream and records kind,bound,result,full filename,line,function;
it is not proof of real-game RNG backends. Display,region,monster/glyph/vision,
name formatting,object location,useup/charge/health and trap services are
controlled implementations which expose calls/selected real state mutations.
C libc sprintf/strcpy/strcat/strchr/memset and compiler varargs are real.
No complete level generation,all monster traits/regions/vision,all object
ownership/free paths,real game save/load,all malformed callers,all branches or
all inputs are claimed. The JS throw case tests adapter cleanup, not native C
foreign-exception unwinding. Native-host,mixed-game,full-world,production and
public behavior validation were not run here and remain pending. Default tests
still use strict referenceBackend; explicit TELEPORT_NATIVE_TESTS=0 selects this
EmC-only diagnostic, never a native pass.

Initial implementation defects caught before freeze:assignable const-char-pointer
slots were mistakenly treated as read-only; native typed writes now distinguish
pointee const from a const pointer slot. Initial shallow fixtures were tightened
to pass an actual sobj to gold_detect and provide real viz row storage, avoiding
Wasm's zero memory as a substitute for valid native caller state. These shallow
results are superseded, not evidence of native validity. A bounded read-only
review found no further defect in shared implode/copy/outref paths; a duplicate
unreachable emitter return was removed and the final exact run passes as above.

## Representation and ownership precision

Every source pointer is an exact checked address in actual Module memory.
Native typed C fields supply real bitfield/narrow/typedef semantics;
windowprocs field access explicitly retains the actual global volatile qualifier. Reads create
fresh heap views; no cached detached record views. Six obj/rm whole-record
assignments and two coord copies call the copy-only memcpy seam; automatic
records/buffers and address-taken locals/parameters use native stack storage,
with original C pass-by-value parameter semantics and finally stackRestore.
The six original char buffers retain their original256-byte capacities.
C logical &&/|| short circuit and yield explicit0/1. long/size_t transports stay
BigInt; no64-bit source scalar is routed through Number. Four original function
designators are native addresses,rn2_on_display_rng/rn2/findone/openone, including
identity comparisons and callbacks into imported JS source bodies.

The private persistent dummytrap has mutable zero-only native backing and is
not reset at each source entry. The four level_detects rows are JS-authoritative
with original strings and live embedded dungeon-topology d_level addresses.
The actual original C table is used only by the reference fixture. No constzero
C catalogue is initialized by JS then read by an optimized same-TU C consumer.
Literal storage capacity is the exact UTF8 source corpus+NULs,2,688 bytes;
unknown extra source strings trigger capacity review rather than silent growth.

The suite compares ordered calls/arguments/strings/results,full80x21 rm map
bytes,full8 object records and captured synthetic records,full4 monster/trap
records,original persistent dummytrap,found-record bytes,int outrefs and slot
ownership. Source pointer returns compare null and actual known pool/global
range+offset; char* strings compare actual content. It does not compare unrelated
absolute addresses between separately linked Modules.

Only actual compiler-backed pointer fields are canonicalized in whole-record
comparisons:all accessed pointer fields in the object/monster/trap schema,
plus specifically obj.v.v_nexthere at its native field address. Exact mapping:
obj.nobj,obj.cobj,obj.v.v_nexthere;monst.nmon,monst.data,monst.minvent,
monst.mextra;trap.ntrap. Offsets are obtained from the native typed address seam,
not guessed/scanned bytes. Null stays0;
known native pool/global ranges retain allocation kind+exact offset, preserving
aliases/distinct objects/slices; unknown pointers remain raw and can fail.
Unaccessed pointer fields stay raw; the fixture seeds them as zero. There is no
blanket byte scanning. All remaining bytes,including scalar fields/padding,stay
raw. A regression writes scalar quan bytes equal to a real object-pool address
and explicitly injects a one-unit scalar mismatch and verifies it remains visible,
even if future module pool addresses happen to coincide.
Trace pointer arguments use only declared pointer parameter types and actual
pool/global ranges+offsets; unknown pointers remain raw. Character arguments
are strings by their declared type; scalar arguments are never normalized.

## Production profile, guards and reserved names

Production compiles cwd TREE/src,input basename detect.c,-O2,memory64,current
compile-defines.json,forced native-terminal.h and ncurses-wasm64 include. Fresh
CPP proves original `rng_log_set_caller("detect.c",line,__func__)`. Only the
PRIVATE fixture,whose #include spelling differs,uses exact
`-fmacro-prefix-map=<root>/scripts/../.cache/wasm64-build/tree/src/=`.
No production flag change or filename trace normalization.

The source guard is self-contained via detect-provenance.json and schema.json;
it rewrites only the recorded workspace root when copied and reruns actual
production compiler AST/CPP. It checks original function and private-data ASTs,
field types/bit widths,dependency prototypes,macro definitions,at-use macros
subsequently undefined,22 logged RNG expansions (including duplicate lazy
Maybe_Half_Phys branches),bare RNG designators,the exact literal corpus and
all native helper indices versus emitted JS paths. No generic reference macro
exposes source-private validation to unrelated probes; support type assertions
use its unique type-only header and true dependency declarations only.

ONLY object_detect's original int parameter `class` becomes `class_` (params
remain detector,class_). ONLY use_crystal_ball's original block-local int
`class` becomes `class_`; original local `i` and scope/lifetime remain intact.
The two distinct original declIDs,owners,kinds,types,offsets and mappings are
recorded and freshly guarded. Parent must add ONLY the object_detect fixed
parameter checker exception; the local rename needs no shared parameter waiver.
No general renamer exception,skipped function or weakened expected comparison.

## Integration contract (coordinator only; unapplied)

Registry fragment:tu-fragments/detect-registry.json. Add the entry and exclude
original wasm/detect.o from hybrid/game links. All42 source imports use original
public names or teleport_detect_+original static name. No header-generated bodies
or configuredFunctionHeaders are needed. The four source/designator pointer
getters keep findone/openone imports reachable; do not claim all private aliases
are dead-stripped. The library invokes central `nethackPorted.detect`.

Include tu-fragments/detect-support.c exactly once in common production support,
or compile it separately,never both. Retain adjacent detect-types.h and
source-data.h. The controlled fixture includes support directly after reference
source or hybrid aliases,so DO NOT also link shared support into this probe.
Add DETECT to the builder's custom owned-source/include-support exceptions,
hybrid auto-library exclusion list and both-mode forced-native-header list.
Reference fixture includes unchanged source once; hybrid excludes it and links
only owned library. No other TU source algorithm dependency is needed.

Metadata:include scripts/tu-detect-layout.h and emit detect_layout via ordinary
probe_layout_count/name/value as layouts.detect. Preserve signed64 bits before
Number for ordinary keys; current values fit exactly,including negative NON_PM.
No pointers/raw64sentinels are serialized to JSON. Runtime embeds exact schema.

Main runtime imports namespace *detect and createDetectEnvironment. Cache one
environment per services.moduleKey in WeakMap. Mirror tested miniature dispatcher
runtime.detect from scripts/test-tu-detect.mjs:require layouts.detect,create env,
stackSave,withCEnvironment(env,detect[name],...args.map(env.ptr)),finally restore.
All42 fixed source parameters are pointer/int/char/short/boolean/unsigned; core
narrows original scalar parameters. Only o_in,o_material,level_distance return
pointers:convert their result to BigInt; other results retain original type.
No observation-only private dispatcher is required for DETECT.

Probe exports are listed exactly in .cache/detect-first-pass/exports.json and
private build.py (30 names). Runtime exports:HEAPU8,stringToUTF8,lengthBytesUTF8,
stackAlloc/stackSave/stackRestore. The registry fragment includes typed helper
exports; add listed probe_* names to the shared custom probe export list.
No malloc/free exports,regex bridge,Lua,extra C TUs or new production flags.

Source checks:run detect-check-source.py and SDK Node detect-check-members.mjs;
standard source checker requires only registry+the single object_detect fixed
parameter exception; standard scope checker requires registry. Private checks
are .cache/detect-first-pass/check-source.py and .cache/check-detect-scope.mjs.
Run actual private build.py then tests with DETECT_PROBE_DIR=.cache/detect-first-pass
and TELEPORT_NATIVE_TESTS=0. Full/native/public gates remain separately pending.

## Parent register append text

PAR08-DETECT implements42 configured source bodies with original names/order/
comments/control/data; only documented decl-ID-scoped object_detect parameter
and use_crystal_ball local int class→class_ mappings. Four-row JS live d_level
table,zero-only persistent trap backing,native typed widths/aliases/outrefs/
record copies and actual callback identities retain source structure. Actual
O2-g memory64 original/import comparison1,267 checks/all42 direct bodies; source/
scope/profile/AST/data/type/macro/alias/prototype guards pass on the final
cleanup/volatile-preserving source and actual hybrid imports all42 source bodies. An
unchanged-oracle wrong-rm.flags control fails the door/open path. Exact source
filename and private-only map are documented. No C detection fallback/shared/
frozen/default/native/public artifact edit. Controlled dependency and typed-
pointer normalization limits are explicit; native/mixed/production/public/full-
world pending,not passed or waived. Final manifest:.cache/detect-first-pass/verified-inputs.json.
