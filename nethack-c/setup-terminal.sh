#!/usr/bin/env bash
# Temporary development-only terminal dependency; not contest-eligible Wasm.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
DEST="$ROOT/js/vendor/libghostty"
mkdir -p "$DEST" "$ROOT/.cache/libghostty"
ARTIFACT="$DEST/ghostty-vt-1.0.0.wasm"
if [[ ! -f "$ARTIFACT" ]]; then
    curl -fL https://release.files.ghostty.org/libghostty-vt/1.0.0/ghostty-vt-1.0.0.wasm -o "$ARTIFACT"
fi
python3 - "$ARTIFACT" <<'PY'
import hashlib, sys
expected = '7b428fee6d0677bc81279458f8f9a3335454834123a9ff47efb3fd177f6da5a8'
assert hashlib.sha256(open(sys.argv[1], 'rb').read()).hexdigest() == expected, 'libghostty checksum mismatch'
PY
