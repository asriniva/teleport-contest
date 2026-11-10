#!/usr/bin/env bash
# Download only into .cache; no global toolchain or shell-profile changes.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
EMSDK="${EMSDK:-$ROOT/.cache/emsdk}"
SDK_COMMIT=1693ce7359fc9694f198694f902a2cc061239b86
mkdir -p "$ROOT/.cache"
if [[ ! -d "$EMSDK/.git" ]]; then
    git clone https://github.com/emscripten-core/emsdk.git "$EMSDK"
fi
git -C "$EMSDK" checkout "$SDK_COMMIT"
"$EMSDK/emsdk" install 4.0.10
"$EMSDK/emsdk" activate 4.0.10
if [[ ! -f "$ROOT/.cache/lua-5.4.8.tar.gz" ]]; then
    curl -fL https://www.lua.org/ftp/lua-5.4.8.tar.gz -o "$ROOT/.cache/lua-5.4.8.tar.gz"
fi
python3 - "$ROOT/.cache/lua-5.4.8.tar.gz" <<'PY'
import hashlib, sys
assert hashlib.sha256(open(sys.argv[1], 'rb').read()).hexdigest() == '4f18ddae154e793e46eeab727c59ef1c0c0c2b744e7b94219710d76f530629ae', 'Lua checksum mismatch'
PY
git -C "$ROOT" submodule update --init nethack-c/upstream

bash "$ROOT/nethack-c/setup-terminfo.sh"
