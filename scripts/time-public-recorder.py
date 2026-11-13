#!/usr/bin/env python3
"""Time full public replays, or profile explicitly selected complete sessions."""
import argparse
import gzip
import hashlib
import json
import os
import pathlib
import resource
import subprocess
import time

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('repository', type=pathlib.Path)
parser.add_argument('--node', required=True, type=pathlib.Path)
parser.add_argument('--output', required=True, type=pathlib.Path)
parser.add_argument('--session', action='append', help='Public session basename; repeat to select complete sessions')
parser.add_argument('--cpu-profile', action='store_true', help='Collect V8 CPU samples at 1 ms')
args = parser.parse_args()
root, node, output = args.repository.resolve(), args.node.resolve(), args.output.resolve()
assert not output.exists(), 'Use a new evidence directory'
for key in ['STANDALONE_RECORDER_ASSETS', 'STANDALONE_RECORDER_LAYOUTS', 'STANDALONE_RECORD_LAYOUTS', 'NODE_OPTIONS']:
    assert not os.environ.get(key), 'Remove inherited override ' + key
output.mkdir(parents=True)

def manifest():
    paths = [p for d in ['js', 'frozen', 'sessions'] for p in sorted((root / d).rglob('*')) if p.is_file()]
    paths += [root / p for p in ['package.json', 'scripts/score-js.sh', '.teleport/repo-metadata.json']]
    return {str(p.relative_to(root)): hashlib.sha256(p.read_bytes()).hexdigest() for p in paths}

before = manifest()
targets = ['sessions/']
if args.session:
    assert len(set(args.session)) == len(args.session), 'Duplicate session selection'
    assert all(pathlib.Path(name).name == name and (root / 'sessions' / name).is_file() for name in args.session)
    targets = ['sessions/' + name for name in args.session]
command = ['bash', 'scripts/score-js.sh', *targets]
if args.session:
    # score.sh accepts only its first argument. The frozen runner accepts all
    # explicit targets; require the same canonical infrastructure overlay first.
    for name in ['isaac64.js', 'terminal.js', 'storage.js']:
        assert (root / 'js' / name).read_bytes() == (root / 'frozen' / name).read_bytes()
    command = [str(node), 'frozen/ps_test_runner.mjs', *targets]
(output / 'pre-run-manifest.json').write_text(json.dumps(dict(
    sourceSha256=before, effectiveTimeoutMs=0, normalEntry=True,
    jsMainOverlay=False, assetOverride=False, layoutOverride=False,
    samplingIntervalUs=1000 if args.cpu_profile else 0,
    selectedSessions=args.session, nodeVersion=subprocess.check_output([str(node), '--version'], text=True).strip(),
    timeoutPolicy='SESSION_REPLAY_TIMEOUT_MS=0 disables frozen worker deadlines', command=command), indent=2))
env = {**os.environ, 'PATH': str(node.parent) + ':' + os.environ['PATH'],
       'TZ': 'America/New_York', 'SESSION_REPLAY_TIMEOUT_MS': '0',
       'STANDALONE_RECORDER_STATS_DIR': str(output / 'stats')}
if args.cpu_profile:
    (output / 'profiles').mkdir()
    env['NODE_OPTIONS'] = f'--cpu-prof --cpu-prof-dir={output / "profiles"} --cpu-prof-interval=1000'
print(json.dumps(dict(output=str(output), sampling=args.cpu_profile, sessions=args.session or 'all44')), flush=True)
prior_usage = resource.getrusage(resource.RUSAGE_CHILDREN)
started = time.perf_counter()
with (output / 'results.stdout.log').open('wb') as stdout, (output / 'results.stderr.log').open('wb') as stderr:
    completed = subprocess.run(command, cwd=root, env=env, stdout=stdout, stderr=stderr)
elapsed = time.perf_counter() - started
usage = resource.getrusage(resource.RUSAGE_CHILDREN)
after = manifest()
text = (output / 'results.stdout.log').read_text()
bundle = json.loads(text.rsplit('__RESULTS_JSON__', 1)[1]) if '__RESULTS_JSON__' in text else None
expected_sessions = sorted(args.session or [p.name for p in (root / 'sessions').glob('*.session.json')])
selection_matches = bundle is not None and sorted(row['session'] for row in bundle['results']) == expected_sessions
receipt = dict(filesChecked=len(before), changed=[k for k in sorted(before.keys() | after.keys()) if before.get(k) != after.get(k)],
               exitCode=completed.returncode, wallSeconds=elapsed,
               sessionSelectionMatched=selection_matches,
               childUserSeconds=usage.ru_utime - prior_usage.ru_utime,
               childSystemSeconds=usage.ru_stime - prior_usage.ru_stime)
(output / 'post-run-integrity.json').write_text(json.dumps(receipt, indent=2) + '\n')
print(json.dumps(receipt), flush=True)
if args.cpu_profile:
    for file in (output / 'profiles').glob('*.cpuprofile'):
        data = file.read_bytes()
        json.loads(data)
        with gzip.open(str(file) + '.gz', 'wb', compresslevel=3) as stream:
            stream.write(data)
        file.unlink()
assert not receipt['changed'], 'Scoring inputs changed during replay'
assert selection_matches, 'Frozen runner did not complete the exact requested session set'
raise SystemExit(completed.returncode)
