Diagnostic reproduction of the public knight session

Base commit: 25ce0121f6f011b59ec201652d2eadae320d0baf.
Node: locally pinned v22.23.4, Darwin arm64.
Working directory: `/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/apply-invoke-diagnostic-25ce012/image`.

The image was created with Python shutil.copytree (independent files) from current main's js/, frozen/, and .teleport/; package.json and scripts/score-js.sh were copied. The session file was copied into image/sessions/. No worktree or production source was modified. diagnostic.patch changes only image/js/nethack/apply.js. image-integrity.json confirms that all other image js/ and frozen/ bytes matched current production at the same commit.

Exact launcher command (frozen worker invoked through unchanged frozen/score.sh and frozen/ps_test_runner.mjs):

```sh
env PATH=/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/node-v22.23.4-darwin-arm64/bin:/usr/bin:/bin \
  TZ=America/New_York \
  SESSION_REPLAY_TIMEOUT_MS=0 \
  APPLY_DIAGNOSTIC_FILE=/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/apply-invoke-diagnostic-25ce012/counts.json \
  STANDALONE_RECORDER_STATS_DIR=/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/apply-invoke-diagnostic-25ce012/stats \
  bash scripts/score-js.sh sessions/seed4500-knight-coverage.session.json \
  > ../stdout.log 2> ../stderr.log
```

The shell launcher delegates to `bash frozen/score.sh`, which overlays the unchanged frozen ISAAC64/terminal/storage files then executes `node frozen/ps_test_runner.mjs sessions/seed4500-knight-coverage.session.json`. The launcher supplied no asset/layout override or NODE_OPTIONS and enabled no CPU profiling. Its only gameplay-source instrumentation was diagnostic.patch. The frozen runner then spawns `process.execPath frozen/ps_test_runner.mjs --worker-session=<absolute session path>` with cwd=image, timeout=0, UTF-8 encoding, and a 64 MiB output buffer. The worker inherits the launch environment. The requested stats directory was not emitted by this normal-entry path; the raw authoritative result is stdout.log.

Instrumentation counts APPLY foreign invocations by target, current/maximum nesting, and consecutive equal target/primitive-argument signatures. The original invoke body is preserved as invokeOriginal; the wrapper calls it once and decrements nesting in finally. It writes counts every 4096 calls and on process exit. It does not log returned values or game-state snapshots; equal arguments are not a non-progress assertion. Diagnostic writes, call wrapping, and signature construction add overhead.

Result: exit code 0; all recorded strict metrics pass, including 108275 RNG entries, 1814 screens/cursors, and 37 animation frames. Frozen-worker time 79135.37 ms for 1813 moves. Total APPLY calls 21729, maximum nesting 3, exit nesting 0. isok 17359 and dist2 4050 dominate calls, consistent with getpos validity sweeps. No infinite interaction reproduced.

This was a public-session reproduction only; it does not reproduce a hidden leaderboard session or establish the cause of its timeout. Timeout was disabled to collect a complete result. Simultaneous parent main44 validation and diagnostic overhead mean the recorded time is not a clean performance comparison. The runner's optional speed/commit discovery emitted an Xcode-license message after the pass; it did not affect the strict result.

Evidence: counts.json, summary.json, stdout.log, stderr.log, source.json, image-integrity.json, diagnostic.patch.
