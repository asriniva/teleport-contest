#!/usr/bin/env bash
# Score the pure-JavaScript engine with the unchanged contest harness.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
if ! command -v node >/dev/null; then
    echo 'Node.js 22 or newer is required.' >&2
    exit 1
fi
export TZ="${TZ:-America/New_York}"
# Full recorder verification has no deadline unless explicitly requested.
export SESSION_REPLAY_TIMEOUT_MS="${SESSION_REPLAY_TIMEOUT_MS:-0}"
cd "$ROOT"
exec bash frozen/score.sh "$@"
