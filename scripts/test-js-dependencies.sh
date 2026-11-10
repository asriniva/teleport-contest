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
dependency_memory64_node="${DEPENDENCY_MEMORY64_NODE:-}"
if [[ -z "$dependency_memory64_node" ]]; then
    for dependency_candidate in "$dependency_sdk"/node/*/bin/node; do
        if [[ -x "$dependency_candidate" ]]; then
            dependency_memory64_node="$dependency_candidate"
            break
        fi
    done
fi
if [[ -z "$dependency_memory64_node" ]]; then
    echo 'Configured C-oracle checks require the memory64 SDK runtime; run setup or set DEPENDENCY_MEMORY64_NODE.' >&2
    exit 1
fi

cd "$dependency_root"
"$dependency_node" scripts/test-js-compress.mjs
"$dependency_node" scripts/test-js-terminfo.mjs
"$dependency_memory64_node" scripts/test-js-posix-regex.mjs --wasm-cross-check
"$dependency_node" scripts/test-js-runtime.mjs
"$dependency_node" scripts/test-js-c-float.mjs
"$dependency_memory64_node" scripts/test-js-time.mjs
"$dependency_memory64_node" scripts/test-js-runtime-regex.mjs
"$dependency_node" scripts/test-js-vfs.mjs
"$dependency_node" scripts/test-js-game-files.mjs
"$dependency_node" scripts/test-js-lua.mjs
"$dependency_node" scripts/test-js-lua-api.mjs
"$dependency_node" scripts/test-js-lua-memory.mjs
"$dependency_node" scripts/test-js-lua-source-memory.mjs
"$dependency_node" scripts/test-js-lua-incremental-codegen.mjs
"$dependency_node" scripts/test-js-lua-incremental.mjs
"$dependency_node" scripts/test-js-lua-reader.mjs
"$dependency_node" scripts/test-js-lua-reader-runtime.mjs
"$dependency_node" scripts/test-js-lua-randomseed.mjs
"$dependency_node" scripts/test-js-lua-aux-memory.mjs
"$dependency_node" scripts/test-js-lua-format-utf8-errors.mjs
"$dependency_node" scripts/test-js-lua-buffer.mjs
"$dependency_node" scripts/test-js-lua-consumer-memory.mjs
"$dependency_node" scripts/test-js-lua-format-memory.mjs
"$dependency_node" scripts/test-js-lua-utf8-memory.mjs
"$dependency_node" scripts/test-js-lua-pack-os-memory.mjs
"$dependency_node" scripts/test-js-lua-dump.mjs
"$dependency_node" scripts/test-js-lua-gc.mjs
"$dependency_memory64_node" scripts/test-js-lua-gc-scheduler.mjs
"$dependency_memory64_node" scripts/test-js-lua-strings.mjs
"$dependency_node" scripts/test-js-lua-sort.mjs
"$dependency_node" scripts/test-js-lua-sort-memory.mjs
"$dependency_node" scripts/test-js-lua-debug.mjs
"$dependency_node" scripts/test-js-lua-debug-library.mjs
"$dependency_node" scripts/test-js-lua-bytecode.mjs
"$dependency_node" scripts/test-js-lua-codegen.mjs
"$dependency_memory64_node" scripts/test-js-lua-abi.mjs --bytecode
"$dependency_memory64_node" scripts/test-js-lua-os.mjs
"$dependency_node" scripts/test-js-timezone-info.mjs
"$dependency_node" scripts/test-js-lua-calendar.mjs
"$dependency_node" scripts/test-js-lua-strftime.mjs
"$dependency_node" scripts/test-js-dependency-isolation.mjs
