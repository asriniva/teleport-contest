#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
EMSDK="${EMSDK:-$ROOT/.cache/emsdk}"
if [[ -f "$EMSDK/emsdk_env.sh" ]]; then
    source "$EMSDK/emsdk_env.sh" >/dev/null 2>&1
fi
cd "$ROOT"
python3 -B scripts/check-wasm-provenance.py
python3 -B scripts/test-tu-structure.py
node scripts/test-tu-scope.mjs
python3 -B scripts/build-tu-probes.py
python3 -B scripts/build-pure-js-probes.py
node scripts/test-native-existing.mjs
node scripts/test-native-terminal-transport.mjs
node scripts/test-native-library-differences.mjs
node scripts/test-version-bridge.mjs
python3 scripts/test-terminfo.py
node scripts/test-wasm-replay-support.mjs
node scripts/test-compress.mjs
exec node scripts/test-wasm.mjs
