#!/usr/bin/env bash
# Fetch the real terminfo implementation into the local cache.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
mkdir -p "$ROOT/.cache"
ARCHIVE="$ROOT/.cache/ncurses-6.5.tar.gz"
if [[ ! -f "$ARCHIVE" ]]; then
    curl -fL https://ftp.gnu.org/gnu/ncurses/ncurses-6.5.tar.gz -o "$ARCHIVE"
fi
python3 - "$ARCHIVE" <<'PY'
import hashlib, sys
assert hashlib.sha256(open(sys.argv[1], 'rb').read()).hexdigest() == '136d91bc269a9a5785e5f9e980bc76ab57428f604ce3e5a5a90cebc767971cc6', 'ncurses checksum mismatch'
PY
