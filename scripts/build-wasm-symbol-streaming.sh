#!/usr/bin/env bash
set -euo pipefail
repo_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
sdk_root="${EMSDK:-$repo_root/.cache/emsdk}"
python3 "$repo_root/scripts/patch-emscripten-symbol-json.py" --source "$sdk_root/upstream/emscripten/src/jsifier.mjs" --expect candidate
exec bash "$repo_root/nethack-c/build-wasm.sh" "$@"
