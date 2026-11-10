#!/usr/bin/env bash
# Targeted EmC/JS differential stage; native parity and game scoring are separate.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
EMSDK="${EMSDK:-$ROOT/.cache/emsdk}"
if [[ $# -eq 0 ]]; then
    echo 'Usage: bash scripts/test-tu-first-pass.sh TU [TU ...]' >&2
    exit 2
fi
source "$EMSDK/emsdk_env.sh" >/dev/null 2>&1
cd "$ROOT"
probe_args=()
for tu in "$@"; do probe_args+=(--only "$tu"); done
python3 -B scripts/build-tu-probes.py --emscripten-only "${probe_args[@]}"
node scripts/write-tu-layouts.mjs
for tu in "$@"; do
    node_options=()
    if [[ "$tu" == mkobj ]]; then node_options+=(--experimental-loader "$ROOT/scripts/test-tu-mkobj-dispatch-loader.mjs"); fi
    MKOBJ_PROBE_DIR="$ROOT/.cache/tu-probes" TELEPORT_READ_PROBE_DIR="$ROOT/.cache/tu-probes/read" TELEPORT_APPLY_PROBE_DIR="$ROOT/.cache/tu-probes/apply" PRAY_PROBE_DIR="$ROOT/.cache/tu-probes" DOTHROW_PROBE_DIR="$ROOT/.cache/tu-probes" PAGER_PROBE_DIR="$ROOT/.cache/tu-probes" MUSE_PROBE_DIR="$ROOT/.cache/tu-probes" DUNGEON_PROBE_DIR="$ROOT/.cache/tu-probes" TELEPORT_MAKEMON_PROBE_DIR="$ROOT/.cache/tu-probes/makemon" MHITU_PROBE_DIR="$ROOT/.cache/tu-probes" ARTIFACT_PROBE_DIR="$ROOT/.cache/tu-probes" DECL_PROBE_DIR="$ROOT/.cache/tu-probes" POLYSELF_PROBE_DIR="$ROOT/.cache/tu-probes" WIZCMDS_PROBE_DIR="$ROOT/.cache/tu-probes" TELEPORT_END_PROBE_DIR="$ROOT/.cache/tu-probes/end" MKLEV_PROBE_DIR="$ROOT/.cache/tu-probes" TELEPORT_PROBE_DIR="$ROOT/.cache/tu-probes" MKMAZE_PROBE_DIR="$ROOT/.cache/tu-probes" WINDOWS_PROBE_DIR="$ROOT/.cache/tu-probes" CFGFILES_PROBE_DIR="$ROOT/.cache/tu-probes" TELEPORT_NATIVE_TESTS=0 node "${node_options[@]}" "scripts/test-tu-$tu.mjs"
done
