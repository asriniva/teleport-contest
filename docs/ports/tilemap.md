# TILEMAP utility profiles

This source package ports `win/share/tilemap.c` in two explicit utility profiles.
It is separate from game registration. The TILETEXT profile owns six functions;
the plain generator composes those exact six bodies with `init_tilemap` and
`main`. The real C drawing, monster, object, allocation, panic and hacklib
sources remain dependencies. TILETEXT also links the real C tiletext reader for
native-to-JS naming callback tests.

Build into a new directory (existing output directories are refused):

```
python3 scripts/build-utility-tilemap.py --profile tiletext --out /fresh/tiletext
python3 scripts/build-utility-tilemap.py --profile generator --out /fresh/generator
python3 scripts/check-utility-tilemap.py --out /fresh/source-guards
.cache/emsdk/node/24.19.0_64bit/bin/node scripts/test-utility-tilemap-tiletext.mjs --out /fresh/tiletext
.cache/emsdk/node/24.19.0_64bit/bin/node scripts/test-utility-tilemap-generator.mjs --out /fresh/generator
```

An explicit `--source-root` may select the project containing the pristine C,
configured headers and SDK; source candidates and imported JS remain beside
these scripts. The C reference source is an explicit absolute preprocessor
macro, never an incidental include-directory lookup. Build receipts capture
transitive compiler includes, compiler/link implementation inputs, source and
runtime inputs before and after compilation. Guards obtain fresh Clang AST and
macro output and compare source boundaries, names, formals, comments, control
counts, strings and initializer data; generated initializer projections are
check inputs only, never a runtime fallback.

The six-function profile tests initialized real catalogues and aliases, native
pointer lifetimes, allocation/free ownership, reader callbacks, growth and
separate Modules. Source-invalid negative OTH indexes, NULL input strings,
overflow and allocation failure are outside the defined fixture corpus.

The plain generator compares complete generated C and listing files, exit
status, stdout/stderr, native map records and owned-list cleanup for normal,
ignored arguments, missing output directory, direct initialization and growth
cases. **The inherited overlapping `nh_snprintf` destination and `%s` input is
preserved at the same native address. Whole generator output parity is an
observation of the actual Emscripten implementation, not portable defined C
behavior.** These proofs do not claim native-host, game, public replay or other
statue/configuration profile acceptance. Native dependency fixture initialization
is explicit and does not insert new initialization into the original main body.
