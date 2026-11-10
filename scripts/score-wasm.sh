#!/usr/bin/env bash
# Use the pinned SDK's Node runtime, which supports true memory64.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
EMSDK="${EMSDK:-$ROOT/.cache/emsdk}"
if [[ ! -f "$ROOT/js/wasm/nethack.wasm" ]]; then
    echo 'Build first: bash nethack-c/setup-wasm.sh && bash nethack-c/build-wasm.sh' >&2
    exit 1
fi
if [[ -f "$EMSDK/emsdk_env.sh" ]]; then
    source "$EMSDK/emsdk_env.sh" >/dev/null 2>&1
fi
if ! command -v node >/dev/null; then
    echo 'Node.js with memory64 support is required (the pinned SDK supplies it).' >&2
    exit 1
fi
# Match the recorder default, while honoring an explicit process timezone.
export TZ="${TZ:-America/New_York}"
cd "$ROOT"
exec bash frozen/score.sh "$@"
