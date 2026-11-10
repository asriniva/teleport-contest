#!/usr/bin/env bash
# Rebuild the deterministic recorder as a wasm64 ES module.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
export EMSDK="${EMSDK:-$ROOT/.cache/emsdk}"
if [[ ! -f "$EMSDK/emsdk_env.sh" ]]; then
    echo 'Run bash nethack-c/setup-wasm.sh first.' >&2
    exit 1
fi
source "$EMSDK/emsdk_env.sh" >/dev/null 2>&1
exec python3 -B "$ROOT/nethack-c/wasm/build.py" "$@"
