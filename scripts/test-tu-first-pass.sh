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
    tu_node_command=(node)
    if [[ "$tu" == mkobj ]]; then tu_node_command+=(--experimental-loader "$ROOT/scripts/test-tu-mkobj-dispatch-loader.mjs"); fi
    env -u TELEPORT_OPTIONS_AUTHOR -u TELEPORT_BOTL_AUTHOR -u TELEPORT_ZAP_PROBE_DIR -u TELEPORT_MON_PROBES MKOBJ_PROBE_DIR="$ROOT/.cache/tu-probes" TELEPORT_READ_PROBE_DIR="$ROOT/.cache/tu-probes/read" TELEPORT_APPLY_PROBE_DIR="$ROOT/.cache/tu-probes/apply" PRAY_PROBE_DIR="$ROOT/.cache/tu-probes" DOTHROW_PROBE_DIR="$ROOT/.cache/tu-probes" PAGER_PROBE_DIR="$ROOT/.cache/tu-probes" MUSE_PROBE_DIR="$ROOT/.cache/tu-probes" DUNGEON_PROBE_DIR="$ROOT/.cache/tu-probes" TELEPORT_MAKEMON_PROBE_DIR="$ROOT/.cache/tu-probes/makemon" MHITU_PROBE_DIR="$ROOT/.cache/tu-probes" ARTIFACT_PROBE_DIR="$ROOT/.cache/tu-probes" DECL_PROBE_DIR="$ROOT/.cache/tu-probes" FILES_PROBE_DIR="$ROOT/.cache/tu-probes" DISPLAY_PROBE_DIR="$ROOT/.cache/tu-probes" INVENT_PROBE_DIR="$ROOT/.cache/tu-probes" CMD_PROBE_DIR="$ROOT/.cache/tu-probes" POLYSELF_PROBE_DIR="$ROOT/.cache/tu-probes" WIZCMDS_PROBE_DIR="$ROOT/.cache/tu-probes" TELEPORT_END_PROBE_DIR="$ROOT/.cache/tu-probes/end" MKLEV_PROBE_DIR="$ROOT/.cache/tu-probes" TELEPORT_PROBE_DIR="$ROOT/.cache/tu-probes" MKMAZE_PROBE_DIR="$ROOT/.cache/tu-probes" WINDOWS_PROBE_DIR="$ROOT/.cache/tu-probes" CFGFILES_PROBE_DIR="$ROOT/.cache/tu-probes" HACK_PROBE_DIR="$ROOT/.cache/tu-probes" TELEPORT_UHITM_PROBE_DIR="$ROOT/.cache/tu-probes/uhitm" PICKUP_PROBE_DIR="$ROOT/.cache/tu-probes" SHK_PROBE_DIR="$ROOT/.cache/tu-probes" SP_LEV_PROBE_DIR="$ROOT/.cache/tu-probes" TRAP_PROBE_DIR="$ROOT/.cache/tu-probes/trap" TERMCAP_PROBE_DIR="$ROOT/.cache/tu-probes" TELEPORT_TOPL_PROBE_DIR="$ROOT/.cache/tu-probes/topl" TELEPORT_WINTTY_PROBE_DIR="$ROOT/.cache/tu-probes/wintty" UNIXUNIX_PROBE_DIR="$ROOT/.cache/tu-probes" UNIXMAIN_PROBE_DIR="$ROOT/.cache/tu-probes" TELEPORT_NATIVE_TESTS=0 "${tu_node_command[@]}" "scripts/test-tu-$tu.mjs"
done
