#!/usr/bin/env bash
# Standalone dependency checks; the active game build is not changed.
set -euo pipefail

dependency_root="$(cd "$(dirname "$0")/.." && pwd)"
dependency_sdk="${EMSDK:-$dependency_root/.cache/emsdk}"
dependency_node="${DEPENDENCY_TEST_NODE:-}"
if [[ -z "$dependency_node" ]]; then
    if command -v node >/dev/null 2>&1; then
        dependency_node="$(command -v node)"
    else
        for dependency_candidate in "$dependency_sdk"/node/*/bin/node; do
            if [[ -x "$dependency_candidate" ]]; then
                dependency_node="$dependency_candidate"
                break
            fi
        done
    fi
fi
if [[ -z "$dependency_node" ]]; then
    echo 'Node is required; set DEPENDENCY_TEST_NODE to its executable.' >&2
    exit 1
fi

cd "$dependency_root"
"$dependency_node" scripts/test-js-compress.mjs
"$dependency_node" scripts/test-js-terminfo.mjs
"$dependency_node" scripts/test-js-dependency-isolation.mjs
