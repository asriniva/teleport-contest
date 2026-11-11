# Standalone JavaScript C environment checkpoint

This is a development harness and a future integration target. It is **not a
selectable game backend**. The mixed game does not import this entry point.
There is no transfer adapter between its memory and this environment's memory.
Future integration must connect a complete dependency group within one JS-owned
memory; registering a function alone does not close its game dependencies.


The [module ledger](ledger.json) contains one row for each of the **138** game
modules currently selected on main. It separates component acceptance, tested
subsets, transport-only adapters, active integration and unconnected modules.
Provider libraries such as Lua/libc/CVFS are outside that denominator. No row's
component status implies full-game recording equivalence.

The latest accepted checkpoint is `9e849bd` on main. Real source `initoptions`
now precedes level/pet/inventory/attribute creation and the initial map/status
render. The 38-check gate passes. The first-display comparison passes 10,881
original-C checks over all13 roles and three seeds, including exact terminal
bytes with initialized symbols/visible hero, complete observed terrain/vision
state and whole-prefix RNG logs. The JS prefix runs with Wasm/network access
forbidden. GLYPHS additionally passes479,795 header/cache/memchr comparisons.
This accepts that prefix, which stops before `u_init_skills_discoveries`.

The separate worktree is continuing through skills, starting equipment, legacy
pager, input/history/messages and DO/SAVE lifecycle transport. Preliminary
skills/equipment prefixes passed39 ordinary cases plus8 targeted blind/nudist/
deaf/pauper cases. Focused armor removal/reapplication and real callback
cancellation cases pass; a wizard-cloak case observes actual resistance-memory
clears and retained64-bit monster state. Broader review fixes and new providers
still await the expanded regression gate; these are not accepted complete
modules or a playable backend.

Remaining major stages are complete startup (including original metadata/date
population, checkpointing and welcome), ALLMAIN turn-loop/preamble (which also
applies starting-gear side effects via `set_wear`), gameplay dependency closure,
level/save/restore/end-game lifecycle, a production entry and full C-versus-JS
game recording acceptance. The module ledger separates committed evidence from
working-tree progress; no count of imported/registered modules is a count of
completed subsystems. Historical component details below retain their specific
fixture limits and do not describe the latest startup boundary.

## Implemented scope

`js/standalone/environment.js` creates an isolated CMemory/CVFS instance and
reuses the existing translated policies and JavaScript dependency services.
It supplies measured memory/record/bitfield access, stack scopes, stable
literals, shared globals, signature-checked function IDs, targeted error
unwinding, bounded libc/stdio, a lazy module registry, and per-instance state.
Production imports no Wasm or host filesystem. Data and environment inputs are
injected. C compilers and C/Wasm oracles are development-only.

| Surface | Checkpoint evidence and limits |
| --- | --- |
| First-level contents and vision startup | `enableLevelContents` connects original TRAP construction, MKROOM coordinate/stair queries, HACK invocation/room lookup, DIG unearthing, ENGRAVE grave/random text, REGION visibility lookup and RUMORS text selection to shared state, including the existing monster-equipment provider. Original `vision_init` runs before `newgame`, matching Unix startup. PASS4,416 original-C comparisons across12 role/seed first-level builds:46 shared roots; complete terrain/door/object/monster/trap/stair/overview/coder records with pointer-graph identities; engraving strings and allocated payloads; timer records; rumor caches;21 accessible VISION workspaces and exact RNG logs. Both actual newgame owners finish `mklev` and stop at the unset `win_cliparound` callback in `u_on_newpos`. Source-defined fields are compared; unspecified coder/timer padding and VM addresses are normalized, function-local VISION colbump is not exported (unused at this phase). Production isolation reaches the same stage and selects actual epitaph text with Wasm/network forbidden. Other levels, active regions, later vision recalculation, window/UI/game loop, hero inventory/skills and full-game recordings remain unfinished. Combined28-check regression gate PASS. |
| Level-generation wiring (in progress) | `enableLevelStartup` connects original level clearing, fixed-seed reseeding, absent-bones branch, rectangles/regions/stairs, map lighting/flood-fill and Lua selection/themed-room calls to one shared heap. Focused original-C RNG/selection witness: PASS56,217 comparisons, including complete core/display ISAAC state and selection fields/maps after geometry/random operations over three seeds. General bones restore, remaining room/trap owners and full level/game closure are unfinished. PASS3,672 connected comparisons over12 role/seed prefixes:42 shared roots (including terrain/rooms), overview/coder records, persistent Lua theme table/function types and exact RNG logs. Both implementations stop at matching `maketrap`/`has_dnstairs` boundaries. Combined27-check regression gate PASS; production isolation reaches trap creation with Wasm/network forbidden. |
| Window color, glyph-map and signal registration | `enableDisplayStartup` connects unchanged WINDOWS has_color and existing DISPLAY reset_glyphmap, plus JS-owned signal/sigaction tables matching configured Emscripten libc. PASS3,981 C comparisons: color masks/capabilities; complete9,624-entry glyph-map bytes and41 state roots over12 actual-newgame role/seed cases; canonical shared-global pointer aliases; handler return identities, errno, all65 action records, arbitrary action masks/flags and scoped explicit callback delivery. The target SIG_IGN is uint64(-2), measured from C; callback identity infrastructure stays unchanged. Both newgame owners reach the explicit mklev boundary. Source static initialization is installed through the existing read-only DISPLAY predicate. Window/terminal lifecycle, general masked/default signal delivery and END handler bodies are not accepted by these tests. |
| Artifact, hero and persistent Lua startup | `enableHeroStartup` connects source artifact role/alignment initialization, U_INIT misc setup via the unchanged adapter, POLYSELF form/intrinsics, ATTRIB HP/abilities, EXPER energy, EAT hunger, BOTL rank size and CALENDAR getnow. Private table layouts are measured from actual C; adapter descriptors are source-bound. PASS58,212 C comparisons over 396 role/race/seed/roleplay configurations, each as a positive owner sequence and actual ALLMAIN newgame prefix: all35 shared roots/catalogues, artifact tables, complete hero/monster-form data, copied24-byte roleplay (including64-bit counters), fixed-input birthday, persistent nhcore.lua registry tables and exact RNG logs. The prefix explicitly requires both JS and C to stop at WINDOWS has_color within DISPLAY reset_glyphmap; this is not display acceptance. Production isolation reaches that same edge with Wasm/network forbidden. Hero inventory/skills, remaining display/map/game-loop owners and full-game recordings remain unfinished. |
| Dungeon and Lua startup | `enableLuaSandbox` reuses unchanged NHLUA/NHLSEL/NHLOBJ table packing and policies, the original SP_LEV des registration, and the existing pure-JS Lua VM. The original configured C dungeon owners plus original Lua5.4.8 pass 2,631 comparisons: 51 role/seed cases, complete 25 shared roots and recursive special-level/branch lists, string payloads, exact RNG logs, and 30 getenv/nh_getenv empty/128/129-character/replacement/removal/recording-epoch checks. Real nhlib.lua/dungeon.lua inputs are hashed in the reference receipt. Standalone isolation executes dungeon generation while Wasm/network are forbidden. Callback registration does not verify every selection/object/des operation; sandbox limit/error branches, hero initialization and full game remain unfinished. |
| Game startup prefix and roles | `enableGameStartup` connects unchanged ROLE table packing/policy, PRAY align_gtitle, UNIXMAIN get_nhuuid and ALLMAIN newgame to the shared heap. Dedicated actual-DECL C reference passes 4,386 comparisons across three seeds, all 13 roles, random/invalid selection and name suffix parsing: complete bytes/string payloads of 21 shared globals/catalogues/tables before/after role initialization or the actual newgame prefix, and exact RNG logs. Both actual newgame owners reach the explicitly unconnected nhl_init boundary; that negative boundary check is not successful startup. Dungeon startup now has the separate evidence above; hero setup/inventory, UI/game loop and full-game recordings remain unfinished. |
| Canonical ISAAC64, allocation, strutil, MD4 | Existing native-C suite: 1,294 comparisons including 6,000 draws and full states. Frozen generator unchanged; bounded rejection wrapper corrects its unusable BigInt/Number helper without replacing the generator. |
| Rectangle | 1,190 original-C states plus memory/scopes/callback/instance/growth probes. Uses the registered RNG when present. |
| DECL, DRAWING, OBJECTS, MONST, SYS | 152 global images and pointer aliases, full catalogue byte comparisons, source initializers, 2,304 drawing lookups and sys initialization. Allocated catalogues retain original zero-before-init behavior. |
| HACKLIB / bounded libc | 132 original-musl qsort results and exact comparator traces, stable source sort, utility/scanner tests. Scanner handles integer/string/character/scanset/count conversions; unsupported conversions reject. This is not a complete libc. |
| RND | 1,500 original-C comparisons, state and log transport; caller must inject entropy for random seeding. |
| SFBASE / SFSTRUCT | 136 original-C comparisons: all 68 historical serializers both directions through real procedure tables, callbacks and files. Full game save/bones/restore closure is unfinished. |
| TRACK | 3,496 original-C movement/equipment/query and historical save/restore comparisons, using shared hero/equipment and serializers. |
| Object startup and name state | `enableObjectState`: 11 unchanged O_INIT functions connected to shared DECL/OBJECTS/DRAWING, canonical RND, two actual DUNGEON ledger functions and SFBASE/SFSTRUCT/CVFS. Combined original-C subsystem passes 6,288 comparisons across four seeds, including full class bytes/ranges/totals, shuffling, description lookup, level gem probabilities, failure diagnostic, exact RNG logs/continued stream and name save/free/restore. Serialized `oc_uname` address slots are compared as null/non-null because allocator addresses differ; every other saved byte and all restored name payloads compare exactly. Discovery/inventory/menu functions remain absent. |
| Object records, ownership and weights | `enableObjectRecords`: 21 MKOBJ functions, two EAT nutrition functions and MON's `dealloc_mextra`, plus the existing ALLOC `dupstr`, connected to shared catalogues/globals/RNG. Combined original-C suite passes 6,184 comparisons: every object type, recursive bags/containers, corpse/statue/partly eaten/glob weights, coin rounding, class/material predicates, nobj/nexthere aliases, buried-list updates, extra/mail/embedded-monster ownership, full cleanup and ID wraparound. Raw object bytes preserve pointer alias identities via address tokens; separately owned extra pointers compare null/non-null, with name/command payloads checked exactly. Source-defined target integer narrowing is retained. Full mksobj generation, merging, inventory/UI, timers/light and invalid-quantity naming remain unlinked. |
| Ordinary item generation and inventory | `enableItemInventory`: initialized/uninitialized `mksobj` plus real inventory add/no-merge/remove/reorder/stack merging/deletion-queue behavior. Three seeds, 2,988 constructors and 669 update callbacks pass 11,970 C comparisons, including full object bytes, pointer identities, roots/IDs/letters, exact RNG logs, nested callback reentry and heap growth. Explicit profile covers 442 ordinary types; 21 special types are excluded from this ordinary-only fixture and checked in the additional groups below. Exposing an entry does not imply every inventory/UI/shop branch is linked. |
| Timer queues and species-backed items | `enableTimers` and `enableMonsterSelection`: 1,350 timer/union/object comparisons plus 9,156 species/biology/growth/difficulty/elemental/hell and special-item comparisons across three seeds. Real queue insertion/duplicates/move/split/stop/attach, sterile egg expiry, opaque uint64 bits, ID wrap and heap growth; four glob constructors; corpse/figurine/egg/statue/tin/candy constructors, nested statue contents, deletion queues and exact RNG logs. Actual source event owners are required; nonsterile hatching, other elapsed events, full monster placement and quest-specific selection remain unfinished. |
| Containers, names and random artifacts | Six container types pass 3,894 comparisons over 1,296 constructors/3,564 contained records across initial inventory, ordinary turns and map generation. `enableItemNaming` adds existing DO_NAME/ARTIFACT functions on the same tables/heap: 11,046 comparisons over 2,760 novel/unique/weapon constructors, including 28 artifacts; complete object/extra/name bytes, existence/origin flags, timer/deletion graphs and exact RNG logs. Naming UI, divine gifts, wielded effects and world interactions remain unaccepted. |
| Monster creation, placement and inventory | `enableMonsterCreation` and `enableMonsterInventory` connect real MAKEMON/STEED/MON/MONDATA/DOG/MINION/PRIEST/VAULT/SHKNAM plus STEAL/WORN/MUSE/DISPLAY/TELEPORT/DO_WEAR dependencies. Two suites each pass 1,299 C comparisons over 432 constructions, 18 species, eight caller flag combinations and three seeds. Full monster/extra/item/name bytes, health/alignment/birth state, map ownership, light records, normal inventory/equipment and exact RNG logs compare. All DECL images are unchanged by enabling construction. These are explicit map-generation/fixed-position component inputs; random placement/groups, visible/world UI, shape changes and complete monster behavior remain unfinished. |
| Terrain and position selection | `enableWorldPosition`: 4,998 original-C comparisons across three seeds cover 12 species, 12 terrain/door/drawbridge inputs, flags, coordinate ring order/shuffling, nearby selection, source debug patterns, mutable engraving bytes/text, boulders and exclusions. Giant-ant random coordinates and groups compare complete monster lists, birth state, map identities and RNG logs. Random species/group selection across the full catalogue, inventory-bearing groups, hero/world transitions and recording remain unfinished. |
| Stdio / persistence | Binary IO, buffering, EOF/error/pushback, seek, close and output contracts; capture/restore/deletion through existing persistence policy. No host device/OS-wide POSIX claim. |
| Lua | Existing JS VM and 83 typed C API dispatch recipes on measured memory; bytecode, callbacks/error unwinding, date/files, userdata growth probes. Full nhlua/nhlobj integration and all standard libraries are unfinished. |
| Terminal | 445 original-C recorder-cell/capture/terminfo comparisons; existing recorder encoding preserved. Window procedures, tty input and game loop are unfinished. The inherited 6,144-byte C recorder buffer bounds captures; larger captures are not accepted by this proof. |
| 13 larger adapters | MKLEV, MKMAZE, PICKUP, SHK, INVENT, DOTHROW, DISPLAY, DUNGEON, MKOBJ, MUSE, PRAY, DETECT, SP_LEV: 23,700 original-C scalar/address/bitfield read/write witnesses. **Transport only**; actual game function dependencies remain unresolved and throw when called. |
| CMD | `isok` geometry only, explicitly registered as `cmd-geometry`. No other CMD surface claimed. |

These are component results, not full-game recording equivalence or acceptance
of all exported functions. There is no playable pure JS build, browser check,
public score or unchanged full-game replay result for this checkpoint.

## Profile and source boundaries

Record metadata targets the configured Emscripten memory64 headers. Exporters
bind actual headers, support sources and existing adapter schemas; production
consumes the checked-in JSON. The historical inventory and plan are retained
unchanged except for their status notice. `scope-baseline.json` instead binds
the 138 translated game policy bodies and frozen files at committed main
`3296b9a3702002e05ce119cd2c865666e2f625fc`, after the requested rebase. This includes
main's NHLSEL addition, adapter optimizations and MON string fix; none of those
ports were edited by this standalone change. The initial 137-module inventory
remains historical.
The base `js/ported/js-runtime.js` changes only its ISAAC provider, replacing the
redundant translation with the canonical generator on JS-owned state views.

There is not yet a single fully accepted platform profile for all libc
services: qsort uses the pinned Emscripten musl implementation; record layouts
use memory64; the earlier base provider's native/Darwin formatting/calendar
choices are inherited. Regex, time and formatting across the entire configured
game are not newly verified here. Do not infer full Emscripten or native-macOS
parity from the individual component tests. No original C, compiler flags,
frozen Terminal/Storage/ISAAC files, game registry, renderer or game defaults
are changed.

## Running the development gate

Use the pinned SDK Node and set `STANDALONE_REFERENCE_ROOT` to a prepared
reference checkout containing the original-C fixtures, SDK, prepared headers
and the host compiler wrapper. From the candidate checkout run:

```sh
STANDALONE_REFERENCE_ROOT=/path/to/reference /path/to/sdk/node scripts/test-standalone.mjs
```

The gate runs source/closure checks, the original base-runtime suite, and nineteen
standalone suites; logs and script hashes go to `.cache/standalone-validation/`.
It requires the existing original native allocation oracle under the candidate's
`.cache/tu-probes/native-oracles/` (alloc-native.node, alloc-full-native-build.json,
alloc-signatures.json); its manifest verifies all bound reference inputs.
To use a separate worktree, copy those three prepared test artifacts there.
The 13 field-helper oracles are built into a fresh directory with:

```sh
python3 scripts/build-standalone-helper-oracles.py --reference-root /path/to/reference --out .cache/standalone-helper-oracles
```

Other C references are the existing prepared fixture directories consumed by
the individual tests. Missing references fail the gate; tests do not silently
skip them. `scripts/test-standalone-isolation.mjs` imports production only after
forbidding WebAssembly and network capabilities. Static closure inspection
independently rejects Wasm/Node/host network imports on that entry point.
The gate is a Node test; browser execution remains unverified.

Build the combined object-state reference into a fresh directory before running
the gate:

```sh
python3 scripts/build-standalone-object-state.py --reference-root /path/to/reference --out .cache/standalone-object-state
```

`STANDALONE_OBJECT_STATE_ORACLE` overrides that output directory in the test.
This oracle compiles original O_INIT, OBJECTS, RND/ISAAC64, ALLOC/STRUTIL/HACKLIB,
SFBASE/SFSTRUCT and the DUNGEON ledger functions together. Its wrappers supply
input globals and expose results; error/UI boundaries abort. It uses actual C
RNG and serializers, with no scripted RNG stream or raw-copy serializer
replacement. The receipt binds compiled sources, included headers and artifacts;
the test refuses changed inputs. No build output is imported by production.

The caller explicitly enables the existing stdio, declarations, drawing,
catalogue, hacklib, serialization and seeded RNG providers, invokes
`objects_globals_init`, then enables
`enableAddressPort('dungeon', {only: ['ledger_no', 'maxledgerno']})` and
`enableObjectState(layouts)`. `call('object-state', 'init_objects')` performs the
original startup policy. Enabling the adapter alone does not initialize the
game or invent a dungeon map. `oinit` reads the actual injected shared dungeon
map. The other O_INIT functions remain unregistered. The read/write source
wrappers use the same JS heap and function registry throughout.

For the object-record group, build a second original-C reference:

```sh
python3 scripts/build-standalone-object-state.py --object-records --reference-root /path/to/reference --out .cache/standalone-object-records
```

`STANDALONE_OBJECT_RECORDS_ORACLE` overrides its test directory. This adds
original MKOBJ, EAT, MON and MONST to the shared startup/RNG/serializer build.
The two C source inclusions expose private functions only to test wrappers;
their original bodies are unchanged. Naming an invalid-quantity object reaches
an aborting test-only UI boundary. Production leaves that owner unresolved.
Input graphs must be valid, acyclic and have live owned pointers; the test does
not claim undefined-input behavior or portable integer-overflow equivalence.
The unsigned C nutrition return is decoded as uint32 at the Wasm test boundary.

After enabling/initializing OBJECTS and MONST and enabling seeded RND, call
`enableObjectRecords(layouts)`. It registers the selected MKOBJ exports under
`mkobj`, EAT's `obj_nutrition`/`eaten_stat` under `object-nutrition`, and MON's
`dealloc_mextra` under `monster-extra`. Memory projections use compiler-measured
fields and bitfields; they contain no nutrition/weight/cleanup algorithms.
The generic address adapter now transports whole-record copies on CMemory.
The isolation gate exercises weights, embedded extras, command bytes and object
cleanup with Wasm/network capabilities forbidden before importing production.

## Item-generation/inventory reference profile

Build its combined original-C reference into a fresh directory:

```sh
python3 scripts/build-standalone-object-state.py --item-inventory --reference-root /path/to/reference --out .cache/standalone-item-inventory
```

`STANDALONE_ITEM_INVENTORY_ORACLE` overrides its test location. This links
original O_INIT/MKOBJ/INVENT and their implemented RNG/catalogue/serialization,
artifact-property, object-name, nutrition, attribute, spell-context, light,
lock, shop, display, pickup and data owners. The component fixture supplies
explicit zero input globals plus identical startup inputs (context ID 2 and
fruit 19); it does not claim complete game startup/configuration. `zerowri`
uses the original all-zero Windows initializer. Actual role, shop, object,
monster and drawing tables come from their original C owners.

The C build records 303 abort-only unconnected function boundaries and 55
zero input globals, with compiler-derived prototypes. These are development
fixture boundaries; none is a production dependency or a successful result
stub. Crossing any function boundary aborts the comparison. Negative controls
actually cross the unfinished `obj_to_any` edge and require a C abort and an
explicit missing-JS-owner error with C scope restored. Source/header/artifact
hashes are bound in the build receipt. This is a component profile with listed
exclusions, not a full original-game executable.

Production uses existing source functions and measured property-style record
projections, source artifact table initialization, the existing adapters and
shared state. Address adapters can add exports without reallocating statics;
callback sites retain declared signatures and pointer-returned JS string
literals get stable C storage. Window procedure storage contains real callback
IDs supplied by the caller; no dummy window implementation is installed.
The original inventory update routine decides when to call the supplied update
callback and how to restore price-suppression state. Full menus/input/window
rendering, unpaid shop paths, special-item constructors and all active eating/
reading/timer/artifact side effects are additional groups, not accepted here.

## Timer and species-backed item profiles

Build two additional original-C references into fresh directories:

```sh
python3 scripts/build-standalone-object-state.py --timers --reference-root /path/to/reference --out .cache/standalone-timers
python3 scripts/build-standalone-object-state.py --monster-selection --reference-root /path/to/reference --out .cache/standalone-special-items
```

`STANDALONE_TIMERS_ORACLE` and `STANDALONE_SPECIAL_ITEMS_ORACLE` override
those directories. The first adds original TIMEOUT/HACK to the prior group;
the second also adds MAKEMON/MONDATA/DO/READ. Their receipts list 332/409
abort-only external function boundaries and 62/67 zero component-input globals,
respectively. These are explicitly incomplete C component executables.

Enable `enableTimers(layouts)` after the item/inventory group. The source
callback table receives signature-checked function IDs which resolve actual
translated event owners on invocation. No successful event substitutes are
installed. `enableMonsterSelection(layouts)` then adds real random species,
biology/growth, tin preparation, candy-wrapper and object-held-state functions.
Tests inject the same valid dungeon inputs on each side; the environment does
not synthesize a dungeon map or substitute a species-selection algorithm.
Timer argument unions preserve all 64 bits, including values outside the JS
safe integer range. Record views retain pointer identity and named header
aliases after memory growth. Four glob constructors and six species-backed/
food constructors are tested; the additional container and naming profiles below
extend the explicit constructor coverage. Elapsed world events, full eating/reading,
quest selection, monster placement/equipment and full-game recording remain
unaccepted. The isolation gate executes the new groups with Wasm and network
globals forbidden before importing the production entry point.

## Container and naming profiles

The container suite reuses the species reference. Build the naming reference:

```sh
python3 scripts/build-standalone-object-state.py --item-naming --reference-root /path/to/reference --out .cache/standalone-item-naming
```

`STANDALONE_ITEM_NAMING_ORACLE` overrides that path. This includes original
ARTIFACT source in the probe translation unit to expose private existence/origin
bytes without editing its policy. Its 409 abort function boundaries and 67 zero
input globals remain explicit. `enableItemNaming(layouts)` requires the existing
item/inventory environment; it extends that environment rather than duplicating
artifact tables. Source title literals, measured record stepping, signed short
arrays, size_t/string transport and shared equipment pointers support oname,
noveltitle, mk_artifact, exist_artifact, artifact_exists and artifact_origin.
The tested random-artifact path uses eight weapon types and A_NONE; divine gifts,
role/race initialization, wielded effects, unpaid naming and the full naming UI
are not accepted. Source-level constructor coverage now includes the 21 special
types excluded from the ordinary fixture, under these explicitly listed inputs;
this does not establish every branch or complete inventory/game integration.

## Monster creation and equipment profiles

Build one larger original-C group into a fresh directory:

```sh
python3 scripts/build-standalone-object-state.py --monster-creation --reference-root /path/to/reference --out .cache/standalone-monster-creation
```

`STANDALONE_MONSTER_CREATION_ORACLE` overrides the directory for both new suites.
The C group adds actual STEED/DOG/MINION/CMD/SOUNDS/PRIEST/VAULT/QUESTPGR/STEAL/
WORN/MUSE/TELEPORT/DO_WEAR/BOTL owners. CMD's command tables require actual
SOUNDS data; DO_WEAR's tables require actual BOTL data. Their presence does not
claim those complete modules are connected in JavaScript. The receipt records
523 compiler-prototyped abort-only external function boundaries and 73 zero
component-input globals; all reached C functions must be real owners.

After the prior item/naming/species groups, enable `enableMonsterCreation(layouts)`
and `enableMonsterInventory(layouts)`. Source header expansions and measured
views support placement, health/alignment, births, all five monster-extra kinds,
light attachment/removal, pickup, item selection, worn masks, extrinsics and
unseen-name buffers. The context loader preserves shared-state accessors; native
layout values such as fmon must never be assigned through the live list setter.
Record views now provide address-only one-past endpoints for record arrays, as
required by original attack-table pointer comparisons, and the oc_armcat header
alias. No attack, equipment or naming algorithm is replaced.

The fixtures explicitly initialize floor cells, valid visibility row storage
with no visible cells, hero alignment/race inputs and dungeon inputs. They use
18 named species, eight sex/anger/asleep/extra/no-count flag combinations, fixed
coordinates and map-generation mode. One suite requests NO_MINVENT; the other
keeps normal inventory generation, pickup and equipment enabled. MM_NOGRP,
MM_NONAME and MM_NOMSG are explicit caller flags on both sides, not forced
production defaults. Raw states include pointer identities, independently owned
extra/name bytes, item graphs and light attachments; whole RNG/caller logs match.
Fixture teardown unlinks the sole map/list owner before real deallocation and
uses real discard_minvent/dobjsfree for items. Full death/migration cleanup,
random placement/groups, shape changes, burning items, saddle attachment,
visible or hallucinated naming/UI, divine equipment effects and full-game
recording remain unfinished. Production isolation constructs an equipped orc
with WebAssembly/network capabilities forbidden before import.

## Terrain and world-position profile

Build the larger position reference:

```sh
python3 scripts/build-standalone-object-state.py --world-position --reference-root /path/to/reference --out .cache/standalone-world-position
```

`STANDALONE_WORLD_POSITION_ORACLE` overrides that directory. This adds original
DBRIDGE/MONMOVE/ENGRAVE/MKMAZE/FILES, including MAKEMON source in the probe to
observe its static group helper without rewriting the function. The reference
has 527 compiler-prototyped abort function boundaries and 77 explicit zero
component-input globals. `STANDALONE_REAL_FILES` removes the older fixture's
nhclose forwarding helper/delete_savefile abort boundary so actual FILES owns
those names in this profile. All seven older object/item/monster references
were rebuilt after adding the conditional; their original policies/flags are
unchanged. Existing source/header/artifact checks reject the stale references.

Enable `enableWorldPosition(layouts)` after monster creation. It connects actual
terrain, accessibility, wall/air, engraving, object-at and exclusion owners to
TELEPORT's goodpos, nearby selection and coordinate collection. The same map
records are used by MAKEMON's random-coordinate and group helpers. Coordinate
arrays/copies and lazy RNG arguments retain measured widths and exact caller
logs. Original rm doormask/wall_info/drawbridgemask aliases share the same bits.

A direct C witness disproved the initial DEBUG-off assumption; that candidate
was rejected. This configured C build has DEBUG enabled. Production now runs
original FILES debugcore/nh_basename with measured address syntax, original
STRUTIL wildcard matching and HACKLIB comparison helpers. Debug message macros
preserve iflags.last_msg and resolve the real pline owner when the source guard
allows output; actual debug printing/UI remains unconnected. No empty success
or disabled-debug implementation is retained. Source engraving creation,
replacement/deletion and all three text buffers are tested with Elbereth,
case variants, future completion times and headstones; active player engraving
and wisdom exercise remain unfinished.

The 4,998-comparison profile includes full ordered/shuffled coordinate bytes,
12-species/12-terrain goodpos matrices, nearby results, explicit object/exclusion
input records, debug file patterns, complete engraving bytes/text and exact RNG
logs across three seeds. Twelve random-coordinate giant-ant creations and
subsequent groups per seed compare every monster byte, catalogue/list/map
identity and birth/vital bytes. These group callers explicitly request
NO_MINVENT/NONAME/NOMSG/NOGRP (the group helper creates each member via its
original body). Full catalogue random spawning, shapechanges, inventory-bearing
groups, active fear/onscary for existing monsters, filter callbacks, hero water/
lava handling, death/migration and full-game recording remain unaccepted.
Production isolation also constructs a random-position group and an engraving
with Wasm/network capabilities forbidden before import.

## Next integration milestone

The first tested level-generation cohort now reaches the window interface after
TRAP/MKROOM and original vision startup. Next connect real window/terminal
initialization and continue the actual newgame path, alongside the remaining
map-generation dependency closure for other levels. Keep comparing the
actual newgame path and complete shared state/RNG against original C as those
edges move. Hero inventory/skills, world transitions, UI/input/game-loop and full
save/restore still require integration. Full-game recording equivalence remains
a required completion gate. Until the full game closure exists, keep the
mixed game as the control and run this harness independently. No cross-heap
transfer or selectable mixed-game route is part of this checkpoint.

Build the level-generation development reference (includes actual configured
CMD/SYMBOLS/SOUNDS/MKMAZE owners required by its source dependencies):

```sh
python3 scripts/build-standalone-level-startup.py --reference-root /path/to/reference --out .cache/standalone-level-startup-v9
```

The reference adds original compression service and original C owners; generated
copies of existing startup fixtures retain the documented DECL/WINDOWS ownership
adjustments. Source headers, compiler inputs, Lua scripts and artifacts are bound
in its receipt. Production instead uses unchanged JS policies, original adapter
views and compiler-exported public function declarations. The latter metadata
binds every transitive declaration header and supplies public function identities
and lazy linkage only for adapters that are explicitly enabled. Private callbacks
remain scoped to their source owner. Missing owners still throw.

Build the next connected level-content reference:

```sh
python3 scripts/build-standalone-level-contents.py --reference-root /path/to/reference --out .cache/standalone-level-contents-v7
```

This profile includes actual original TRAP/MKROOM/ZAP/HACK/DIG/RUMORS and the
original item/inventory/timer/monster/world owners already connected in JS. Its
owned observation fixture includes original vision.c unchanged so accessible
private workspaces can be inspected. Native function-local `vision_recalc`
colbump is deliberately unobserved; only its unused JS initial state is checked.
The profile binds generated epitaph/engrave/rumors/bogusmon/oracles assets as
well as all Lua files; callers inject those inputs into both virtual filesystems.
This accepts the tested first-level cohort through the same null window callback,
not a playable engine or a complete vision/region/trap surface.


Window and Unix terminal startup now use `enableWindowSystem(layouts)` after
existing game/display startup. The original procedure initializers, tty selection,
base-window construction, terminal setup and cursor startup match the connected
C group through the next missing VERSION banner owner. This is a startup prefix;
window lifecycle, text/status/menu/input and full-game recording acceptance remain
unfinished. The independent raw SDK device checks and native-layout policy checks
are distinct. The latter reuse unchanged `services/native-terminal.js` and set
transport scratch to zero in both test fixtures: SDK TCGETS leaves speed fields
untouched. Production scratch behavior is not claimed by that controlled-input
comparison. Three not-yet-initialized DisplayDesc fields and its padding are
excluded; all source-initialized fields, the entire zero-initialized base-window
record and all20 window slots are compared. Foreign callback presence checks do
not verify those foreign bodies. Source-owned/private callbacks use exact names.

```sh
python3 scripts/build-standalone-window-startup.py --reference-root /path/to/reference --out .cache/standalone-window-startup-v8
node scripts/test-standalone-stdio-buffers.mjs
node scripts/test-standalone-window-startup.mjs
```

The reference retains distinct original WINDOWS/WINTTY translation units, adds
actual UNIXTTY/IOCTL/PLINE/getline/topl and configured libtinfo/recorder bridge,
and uses the accepted forced native-terminal header/library. Generated fixture
copies remove exactly the previous owned-storage declarations and four prior
abort/diagnostic message definitions in favor of their original owners. The
receipt binds originals, generated inputs, SDK device/stdio sources and artifacts;
unconnected functions abort with their name. No translated policy is changed.
Stdio passes768 C buffer comparisons; window/terminal startup passes606 focused
comparisons. The expanded30-check regression gate passed; a separate startup fixture also reaches the VERSION boundary with Wasm/network capabilities forbidden. Full-game recording acceptance remains outstanding.


`enableVersionInfo(layouts)` connects the unchanged DATE static initializer and
VERSION adapter. `enableOptions(layouts)` supplies original OPTIONS source tables,
shared globals, typed field calls and scoped callback identities. Together they
let the real tty initialization finish, including its banner. New-game startup
then requires BOTL status initialization. DATE population/MDLIB startup, complete
options handlers/configuration, status, input and game recordings remain unfinished.

```sh
python3 scripts/build-standalone-window-banner.py --reference-root /path/to/reference --out .cache/standalone-window-banner-v3
node scripts/test-standalone-window-banner.mjs
```

The separate development reference adds original DATE/VERSION/MDLIB/POSIXREGEX
and INSIGHT owners and includes original OPTIONS/VERSION in their own observation
translation units. Earlier references stay unchanged. The existing seven private
OPTIONS adapter mirror types are measured with the configured compiler and bound
in options-abi.json together with their original-source enum widths and descriptors.
PASS40,598 comparisons cover completed tty initialization, static DATE values,
VERSION strings/banner/critical sizes/runtime options/feature parsing, and all
option-table fields/pointer identities plus WC/WC2 restrictions. Tests explicitly
copy the original option input table before exercising restrictions; this does
not accept the additional handler lifecycle in allopt_array_init. Number-only
status version cases exclude the unconnected Unix basename owner. Native-layout
terminal tests retain the documented controlled scratch precondition. Full-game
acceptance remains false. The expanded31-check regression gate passed; a separate fixture completes tty/banner/options with Wasm/network globals forbidden and reaches the next BOTL status owner.


`enableStatus(layouts)` connects unchanged BOTL state/data and typed window
callbacks; `enableGameWindows(layouts)` connects original ALLMAIN's pre-game
window routine and the configured original SOUNDS activation. Call the source
`init_sound_disp_gamewindows()` after tty initialization and before `newgame`, as
Unix main does. Otherwise POLYSELF correctly reports status reassessment before
initialization. The real pre-game routine creates message/status/map/inventory
windows, initializes status and clears display buffers. Newgame now reaches the
next unconnected HACK room-entry owner after generating the first level.

```sh
python3 scripts/build-standalone-status-startup.py --reference-root /path/to/reference --out .cache/standalone-status-startup-v2
node scripts/test-standalone-status-startup.mjs
```

This separate C profile includes original BOTL/SOUNDS owners in observation-only
translation units, with existing private-ABI assertions. Three private BOTL adapter
mirror records are compiler measured and source bound. PASS42,005 comparisons
include the earlier40,598 banner/options cohort plus status/game-window state,
constructor preservation of152 DECL roots, reassessment across form/visibility/
hitpoint-bar settings, ownership/identity and cleanup of allocated status values,
complete tty field state, initialized window records/all20 slots, buffered row
lengths/allocation presence, and source no-sound activation. The configured sound
set contains only that original provider; this does not add an audio backend.
The test excludes uninitialized window padding/blanked/menu_ch and text-buffer
tails, and retains the documented controlled terminal scratch inputs. Actual
status rendering, parsing, messages, broader sound and full recordings remain
unfinished. The expanded32-check regression gate passed. A separate fixture runs actual window/status and first-level startup to the room-entry boundary with Wasm/network capabilities forbidden.


`enableMovement(layouts)` connects the unchanged HACK adapter to shared typed
memory, compiler-derived callback identities and its actual source-private weight
record. It reuses the level provider's five-byte in_rooms buffer (or owns that
same named buffer when enabled first), preserving its current image while
installing the remaining once-per-module source data. Public symbols already
owned elsewhere keep their owners; private callbacks remain source scoped.

```sh
python3 scripts/build-standalone-movement-startup.py --reference-root /path/to/reference --out .cache/standalone-movement-startup-v2
node scripts/test-standalone-movement-startup.mjs
```

The separate reference includes original hack.c alone for observations, exports
public functions and an input/observation helper for private move_update, and
retains every original policy body. PASS42,170 comparisons include the prior
42,005 status/window cohort plus room membership/filtering across ordinary/shop
and SHARED/SHARED_PLUS edge cells, all seven room/shop bookkeeping buffers,
new-level clearing and ordinary room entry, temporary union conversion and
rounded division. This accepts those reached paths, not all functions exposed
by the HACK adapter. Special-room greetings/shops, travel/movement/combat and
rendering still need integrated verification. Actual newgame with live windows
now reaches DOG makedog. Full-game and recording acceptance remain outstanding;
the documented native terminal scratch/undefined-field limits still apply. Expanded33-check regression gate PASS; a separate forbidden-capability fixture reaches the makedog boundary through real level/room startup.
