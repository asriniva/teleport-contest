# Alternate RANDOM utility/library profile

This standalone profile replaces the four functions of sys/share/random.c.
The normal game's USE_ISAAC64 default and terminfo/terminal paths are untouched.
The source's supported RANDOM define is active despite USE_ISAAC64 remaining in
the configured header. No fake platform flags or C policy fallback are used.

```
python3 scripts/build-utility-random.py --out /fresh/random-pair
python3 scripts/check-utility-random.py --out /fresh/random-metadata
.cache/emsdk/node/24.19.0_64bit/bin/node scripts/test-utility-random.mjs --out /fresh/random-pair
```

Both builders require fresh, non-existing output. Optional --source-root points
to the actual project C/configured headers/SDK while imported JS and ABI files
remain beside the scripts. Original C inclusion is an explicit absolute macro,
not an include-directory fallback. Compiler transitive -M inputs and actual
SDK/compiler/link sources are hashed before/after compilation. Fresh Clang
AST/macro data drive the original exact source/data guard, not runtime policy.

The private forced header renames ONLY the otherwise-unused SDK libc initstate
declaration before including real stdlib.h, then undefines the rename. This
avoids its size_t prototype conflicting with the inherited owned int prototype.
Original function names/formals/bodies stay intact. Native buffer sizing uses
actual sizeof(long)/degree metadata; nominal n selector thresholds are unchanged.
Zero-only native32-long backing is initialized from authoritative JS data;
caller state remains native-owned live memory, with per-Module private aliases.

Tests retain all9,670 comparisons: initialization, five degrees/thresholds,
unsigned seeds, sequences, raw bytes/tails, old-state aliases/same-state restore,
diagnostics, external mutations, growth and separate Modules. Source guards
retain all27 comments/formals/order/control/diagnostics/data and four negative
controls. An optional negative loader changes the31-bit mask; running the same
test with --loader scripts/negative-utility-random-loader.mjs must fail a real
configured-generated-value assertion.

**Signed-long recurrence/addition overflow is inherited undefined C behavior.**
Parity is an observation of actual EmC4/Clang21 MEMORY64 at O2, not portable C
semantics. No -fwrapv, algorithm fix, expected-number table or C fallback is
introduced. Original thresholds assume32-bit long, so fixtures physically
allocate enough long64 cells while retaining nominal selector n. NULL is used
only on size rejection before dereference; corrupt metadata is bounded to safe
allocated addresses. Unsafe/undersized/misaligned/freed pointers, concurrency,
OOM, native-host and game/public acceptance are outside this proof.
