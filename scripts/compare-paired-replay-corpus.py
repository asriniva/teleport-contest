#!/usr/bin/env python3
"""Replay every public session on both sources, alternating the first version.

Each invocation uses the unchanged frozen scorer and a complete session. Raw
per-session results remain authoritative; totals are sums of independent scorer
invocations, not a single continuous batch. No synthetic game timing is used.
"""
import argparse
import json
import math
import pathlib
import statistics
import subprocess
import sys
import time

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('baseline', type=pathlib.Path)
parser.add_argument('candidate', type=pathlib.Path)
parser.add_argument('--node', required=True, type=pathlib.Path)
parser.add_argument('--output', required=True, type=pathlib.Path)
args = parser.parse_args()
tool_root = pathlib.Path(__file__).resolve().parents[1]
sources = dict(baseline=args.baseline.resolve(), candidate=args.candidate.resolve())
node, output = args.node.resolve(), args.output.resolve()
assert not output.exists(), 'Use a fresh output directory'
sessions = sorted(p.name for p in (sources['baseline'] / 'sessions').glob('*.session.json'))
assert len(sessions) == 44
assert sessions == sorted(p.name for p in (sources['candidate'] / 'sessions').glob('*.session.json'))
output.mkdir(parents=True)
rows, pins = [], {}
started = time.monotonic()
for index, session in enumerate(sessions):
    order = ['baseline', 'candidate'] if index % 2 == 0 else ['candidate', 'baseline']
    versions = {}
    for version in order:
        run = output / f'{index:02d}-{version}'
        with (output / f'{index:02d}-{version}-launcher.log').open('w') as log:
            subprocess.run([sys.executable, str(tool_root / 'scripts/time-public-recorder.py'),
                            str(sources[version]), '--node', str(node), '--output', str(run),
                            '--session', session], cwd=tool_root, stdout=log, stderr=subprocess.STDOUT, check=True)
            subprocess.run([str(node), str(tool_root / 'scripts/verify-selected-replay.mjs'),
                            str(sources[version]), str(run)], cwd=tool_root, stdout=log,
                           stderr=subprocess.STDOUT, check=True)
        pre = json.loads((run / 'pre-run-manifest.json').read_text())
        post = json.loads((run / 'post-run-integrity.json').read_text())
        strict = json.loads((run / 'selected-summary.json').read_text())
        assert strict['strictAllMetricsPassed'] == 1 and post['sessionSelectionMatched']
        assert pre['samplingIntervalUs'] == 0
        if version in pins:
            assert pins[version] == pre['sourceSha256'], 'Source changes across session pairs'
        else:
            pins[version] = pre['sourceSha256']
        timing = strict['timings'][0]
        assert timing['session'] == session
        versions[version] = dict(replayMs=timing['ms'], recordedInputs=timing['moves'],
                                 scorerWallSeconds=post['wallSeconds'],
                                 childCpuSeconds=post['childUserSeconds'] + post['childSystemSeconds'])
    assert versions['baseline']['recordedInputs'] == versions['candidate']['recordedInputs']
    row = dict(session=session, order=order, **versions,
               ratio=versions['candidate']['replayMs'] / versions['baseline']['replayMs'])
    rows.append(row)
    (output / 'progress.json').write_text(json.dumps(dict(complete=False, completedPairs=len(rows), sessions=rows), indent=2) + '\n')
    print(json.dumps(dict(completedPairs=len(rows), session=session, baselineMs=versions['baseline']['replayMs'],
                          candidateMs=versions['candidate']['replayMs'], ratio=row['ratio'])), flush=True)

for prefix in ['frozen/', 'sessions/']:
    assert {k: v for k, v in pins['baseline'].items() if k.startswith(prefix)} == {
        k: v for k, v in pins['candidate'].items() if k.startswith(prefix)}, 'Different ' + prefix
totals = {version: {key: sum(row[version][key] for row in rows)
                    for key in ['replayMs', 'scorerWallSeconds', 'childCpuSeconds']}
          for version in sources}
result = dict(version=1, complete=True, strictPublicPassed=dict(baseline=44, candidate=44),
              method=__doc__.strip(), samplingIntervalUs=0,
              elapsedSeconds=time.monotonic() - started, totals=totals,
              replayRatio=totals['candidate']['replayMs'] / totals['baseline']['replayMs'],
              scorerWallRatio=totals['candidate']['scorerWallSeconds'] / totals['baseline']['scorerWallSeconds'],
              geometricMeanSessionRatio=math.exp(sum(math.log(row['ratio']) for row in rows) / len(rows)),
              medianSessionRatio=statistics.median(row['ratio'] for row in rows),
              fasterSessions=sum(row['ratio'] < 1 for row in rows),
              changedInputs=[k for k in sorted(pins['baseline'].keys() | pins['candidate'].keys())
                             if pins['baseline'].get(k) != pins['candidate'].get(k)],
              sessions=rows,
              limits=['One pair per session; alternating order reduces but does not eliminate host-load effects.',
                      'Summed independent full-session scorer invocations include repeated parent startup.',
                      'Public44 only; no hosted-judge or held-out deadline acceptance.'])
(output / 'comparison.json').write_text(json.dumps(result, indent=2) + '\n')
print(json.dumps({k: v for k, v in result.items() if k not in ['sessions', 'limits', 'method']}, indent=2))
