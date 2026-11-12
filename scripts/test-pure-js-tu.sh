#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
python3 -B scripts/pure-js-fixtures/build-references.py --ensure "$@"
python3 -B scripts/build-pure-js-probes.py "$@"
node_path=.cache/emsdk/node/24.19.0_64bit/bin/node
if [[ ! -x "$node_path" ]]; then node_path=node; fi
exec "$node_path" scripts/test-native-existing.mjs "$@"
