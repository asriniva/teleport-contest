#!/usr/bin/env bash
# Profile both pinned images with the same tools and the selected order.
set -euo pipefail
PAIR_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
PAIR_NODE="$(command -v node)"
case "${COMPARISON_ORDER:-baseline-first}" in
  baseline-first) phases=(baseline candidate) ;;
  candidate-first) phases=(candidate baseline) ;;
  *) echo 'Invalid comparison order' >&2; exit 2 ;;
esac
for phase in "${phases[@]}"; do
  unset STANDALONE_RECORDER_ASSETS STANDALONE_RECORDER_LAYOUTS STANDALONE_RECORD_LAYOUTS NODE_OPTIONS
  image="$RUNNER_TEMP/runtime-$phase"
  output="$RUNNER_TEMP/profile-$phase"
  python3 "$PAIR_ROOT/scripts/profile-public-recorder.py" "$image" \
    --node "$PAIR_NODE" --output "$output"
  ln -s "$image" "$output/score-repo"
  "$PAIR_NODE" "$PAIR_ROOT/scripts/score-standalone.mjs" --summarize "$output"
  python3 "$PAIR_ROOT/scripts/profile-recorder-cpu.py" "$output"
done
