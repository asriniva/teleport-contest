#!/usr/bin/env python3
"""Attribute replay samples to the nearest translated routine, without overlap.

Unlike inclusive rankings, each sample belongs to exactly one owner. A routine's
cost includes its memory/binding helpers but excludes calls to other translated
routines. GC has no caller and remains unattributed. Never executes a session.
"""
import argparse
import collections
import gzip
import hashlib
import json
import pathlib
import re

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('directory', type=pathlib.Path)
parser.add_argument('--output', type=pathlib.Path, required=True)
args = parser.parse_args()
root = args.directory.resolve()
workers = {}
for file in (root / 'stats').glob('*.json'):
    row = json.loads(file.read_text())
    previous = workers.setdefault(row['pid'], row['session'])
    assert previous == row['session'], 'A worker cannot mix session identities'

def frame(node):
    call = node['callFrame']
    url = call['url']
    if '/js/' in url:
        url = 'js/' + url.split('/js/', 1)[1]
    elif '/frozen/' in url:
        url = 'frozen/' + url.split('/frozen/', 1)[1]
    return (url, call['functionName'], call['lineNumber'] + 1)

def ranked(counter, total, limit=20):
    return [dict(file=k[0], function=k[1], line=k[2],
                 sampledMs=round(v / 1000, 3), percent=round(v * 100 / total, 3))
            for k, v in counter.most_common(limit)]

all_owners = collections.Counter()
sessions = []
seen = set()
for file in sorted((root / 'profiles').glob('*.cpuprofile*')):
    match = re.search(r'CPU\.\d+\.\d+\.(\d+)\.', file.name)
    if not match or int(match[1]) not in workers:
        continue
    pid = int(match[1])
    assert pid not in seen, 'Duplicate worker CPU profile'
    seen.add(pid)
    with (gzip.open(file, 'rt') if file.suffix == '.gz' else file.open()) as stream:
        profile = json.load(stream)
    nodes = {node['id']: node for node in profile['nodes']}
    parents = {child: node['id'] for node in profile['nodes']
               for child in node.get('children', [])}
    stacks = {}
    owners = collections.Counter()
    helpers = collections.defaultdict(collections.Counter)
    for sample, delta in zip(profile['samples'], profile['timeDeltas']):
        if sample not in stacks:
            chain = []
            current = sample
            while current in nodes:
                chain.append(frame(nodes[current]))
                current = parents.get(current)
            stacks[sample] = chain
        chain = stacks[sample]
        owner = next((f for f in chain if f[0].startswith('js/ported/')), chain[0])
        owners[owner] += delta
        helpers[owner][chain[0]] += delta
    total = sum(owners.values())
    all_owners.update(owners)
    sessions.append(dict(session=workers[pid], sampledMs=round(total / 1000, 3),
                         profile=file.name,
                         profileSha256=hashlib.sha256(file.read_bytes()).hexdigest(),
                         owners=[
                             dict(**row, helpers=ranked(helpers[(row['file'], row['function'], row['line'])], total, 12))
                             for row in ranked(owners, total)]))
total = sum(all_owners.values())
result = dict(version=1, method=__doc__.split('\n\n', 1)[1].strip(),
              workerProfiles=len(sessions), sampledMs=round(total / 1000, 3),
              owners=ranked(all_owners, total, 30),
              sessions=sorted(sessions, key=lambda row: -row['sampledMs']))
args.output.write_text(json.dumps(result, indent=2) + '\n')
print(json.dumps(dict(workerProfiles=len(sessions), sampledMs=result['sampledMs'],
                      owners=result['owners'][:10]), indent=2))
