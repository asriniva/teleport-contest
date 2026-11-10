#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
EMSDK="${EMSDK:-$ROOT/.cache/emsdk}"
if [[ -f "$EMSDK/emsdk_env.sh" ]]; then
    source "$EMSDK/emsdk_env.sh" >/dev/null 2>&1
fi
cd "$ROOT"
selection=()
for name in "$@"; do selection+=(--only "$name"); done
if (( $# )); then
    python3 -B scripts/build-tu-probes.py --native-only "${selection[@]}"
else
    python3 -B scripts/build-tu-probes.py --native-only
fi
node scripts/test-native-existing.mjs "$@"
