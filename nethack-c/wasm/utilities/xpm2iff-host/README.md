# XPM2IFF HOST utility component

The six original `sys/amiga/xpm2iff_host.c` policy functions are in `js/ported-utilities/xpm2iff-host.js`. The per-utility runtime uses actual memory64 static storage and libc FILE/scanf/ctype/memory transports. The mixed pair imports all six original policy bodies; the reference includes the unmodified upstream C. No AmigaOS interface, game registry entry, game count or scorer selection is involved.

Build from the repository root with a fresh output path:

```
python3 scripts/build-utility-xpm2iff-host.py --out /tmp/xpm2iff-host-new
```

`--out` is required and existing paths, including dangling symlinks, are refused. `--source-root /path/to/teleport-contest` optionally identifies the actual repository containing `nethack-c/upstream` and the existing local Emscripten SDK. The default is this script's repository root. Nothing is copied from the SDK. Generated source/metadata, matching reference/hybrid mjs/Wasm and logs remain under the output path. Failed builds retain their diagnostics and require a different fresh output path for retry.

No-build verification of that output:

```
.cache/emsdk/node/24.19.0_64bit/bin/node scripts/test-utility-xpm2iff-host.mjs --out /tmp/xpm2iff-host-new
python3 scripts/guard-utility-xpm2iff-host.py --out /tmp/xpm2iff-host-new
.cache/emsdk/node/24.19.0_64bit/bin/node scripts/check-utility-xpm2iff-host-imports.mjs --out /tmp/xpm2iff-host-new
.cache/emsdk/node/24.19.0_64bit/bin/node scripts/check-utility-xpm2iff-host-abi.mjs --out /tmp/xpm2iff-host-new
python3 scripts/test-utility-xpm2iff-host-negative.py --out /tmp/xpm2iff-host-new
```

The tested profile is Emscripten4.0.10/Clang21 MEMORY64 O2-g with real in-memory libc stdio, not a native-host executable. The 54 cases/56 assertions retain the original defined-helper versus empirical-parser distinction. The original signed `int*` RGB scanf `%x` mismatch remains; color-parser/main comparisons are empirical for this exact ABI, not strict ISO-C equivalence. The one-color CMAP padding/FORM-size discrepancy is preserved. Malformed-input overflow, invalid pointers, short-row uninitialized reads, exhaustive native branch/allocation behavior and native-host or game acceptance are unproved.

`probe.c` contains controlled native callers/storage access and FILE capture, and aliases main solely to avoid real host process exit. The C transport contains no XPM palette, bitplane or IFF policy. Source early-return leaks and pointer cells remain unmodified. Source mapping and all38 comments are guarded. Source changes require an explicit rebase; the builder rejects source bytes that differ from this exact mapping.
