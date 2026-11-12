#!/usr/bin/env bash
# Native C is the preferred reference where its fixture ABI matches. Every
# implementation runs as pure JavaScript; remaining C references are isolated.
set -euo pipefail
exec bash "$(dirname "$0")/test-pure-js-tu.sh" "$@"
