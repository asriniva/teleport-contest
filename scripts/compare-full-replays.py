#!/usr/bin/env python3
"""Compare complete strict replays with matching instrumentation and inputs."""
import argparse
import json
import math
import pathlib

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('baseline', type=pathlib.Path)
parser.add_argument('candidate', type=pathlib.Path)
parser.add_argument('--output', required=True, type=pathlib.Path)
args = parser.parse_args()

def read_run(directory):
    load = lambda name: json.loads((directory / name).read_text())
    pre, post, summary = (load(name) for name in ['pre-run-manifest.json', 'post-run-integrity.json', 'summary.json'])
    assert post['exitCode'] == 0 and not post['changed'], 'Unsuccessful or changing scoring inputs'
    assert summary['strictAllMetricsPassed'] == summary['sessionCount'] == 44, 'Complete strict parity is required'
    assert pre['effectiveTimeoutMs'] == 0 and pre['normalEntry'], 'Complete normal replays are required'
    assert not any(pre[key] for key in ['jsMainOverlay', 'assetOverride', 'layoutOverride'])
    official = load('official-results.json')
    timings = {row['session']: row['time'] for row in official['results']}
    assert len(timings) == 44 and all(row['ms'] > 0 for row in timings.values())
    return pre, post, summary, timings

before, after = (read_run(directory) for directory in [args.baseline, args.candidate])
assert before[0]['nodeVersion'] == after[0]['nodeVersion'], 'Runtime mismatch'
assert before[0]['samplingIntervalUs'] == after[0]['samplingIntervalUs'], 'Instrumentation mismatch'
assert before[2]['metrics'] == after[2]['metrics'] and before[2]['expectedTotals'] == after[2]['expectedTotals']
for prefix in ['frozen/', 'sessions/']:
    assert {k: v for k, v in before[0]['sourceSha256'].items() if k.startswith(prefix)} == {
        k: v for k, v in after[0]['sourceSha256'].items() if k.startswith(prefix)}, 'Different ' + prefix
assert before[3].keys() == after[3].keys()
sessions = []
for name in before[3]:
    old, new = before[3][name], after[3][name]
    assert old['moves'] == new['moves']
    sessions.append(dict(session=name, recordedInputs=old['moves'], baselineMs=old['ms'],
                         candidateMs=new['ms'], ratio=new['ms'] / old['ms']))
sources, targets = before[0]['sourceSha256'], after[0]['sourceSha256']
result = dict(version=1, complete=True, strictPublicPassed=dict(baseline=44, candidate=44),
              nodeVersion=before[0]['nodeVersion'], samplingIntervalUs=before[0]['samplingIntervalUs'],
              baselineWallSeconds=before[1]['wallSeconds'], candidateWallSeconds=after[1]['wallSeconds'],
              wallRatio=after[1]['wallSeconds'] / before[1]['wallSeconds'],
              geometricMeanSessionRatio=math.exp(sum(math.log(row['ratio']) for row in sessions) / 44),
              changedInputs=[k for k in sorted(sources.keys() | targets.keys()) if sources.get(k) != targets.get(k)],
              sessions=sessions,
              limits=['Sequential same-host timings are affected by run order and host load.',
                      'Public44 only; no hosted-judge or held-out deadline acceptance.'])
args.output.write_text(json.dumps(result, indent=2) + '\n')
print(json.dumps({k: v for k, v in result.items() if k not in ['sessions', 'limits']}, indent=2))
