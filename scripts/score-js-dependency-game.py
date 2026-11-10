#!/usr/bin/env python3
"""Score the isolated dependency candidate with an unchanged frozen harness.

The staging copy changes only the adapter's module factory import. Active game
sources, generated binaries and frozen files are never overwritten.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess

ROOT = Path(__file__).resolve().parents[1]


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--build-dir', type=Path, default=ROOT / '.cache/js-dependency-game')
    parser.add_argument('--session', help='One session filename, or omit to score all public sessions.')
    args = parser.parse_args()
    build = args.build_dir.resolve()
    if not (build / 'game.mjs').is_file():
        raise SystemExit('Build first: python3 scripts/build-js-dependency-game.py')
    stage = build / 'score-repo'
    stage.mkdir(exist_ok=True)
    shutil.copytree(ROOT / 'frozen', stage / 'frozen', dirs_exist_ok=True)
    shutil.copytree(ROOT / 'sessions', stage / 'sessions', dirs_exist_ok=True)
    shutil.copytree(build / 'snapshot/js', stage / 'js', dirs_exist_ok=True,
                    ignore=shutil.ignore_patterns('nethack.mjs', 'nethack.wasm', 'vendor'))
    shutil.copytree(ROOT / '.teleport', stage / '.teleport', dirs_exist_ok=True)
    (stage / 'package.json').write_text('{"type":"module"}\n')
    (stage / 'js/jsmain.js').write_text('export { runWasmSegment as runSegment } from "./wasm-adapter.js";\n')
    adapter = build / 'snapshot/js/wasm-adapter.js'
    source = adapter.read_text()
    original = "await import('./wasm/nethack.mjs')"
    if source.count(original) != 1:
        raise SystemExit('Adapter factory import changed; review staging transformation.')
    factory = os.path.relpath(build / 'game.mjs', stage / 'js').replace(os.sep, '/')
    if not factory.startswith('.'): factory = './' + factory
    (stage / 'js/wasm-adapter.js').write_text(source.replace(original, 'await import(' + json.dumps(factory) + ')'))
    sdk = Path(os.environ.get('EMSDK', ROOT / '.cache/emsdk'))
    nodes = sorted(sdk.glob('node/*/bin/node'))
    if not nodes:
        raise SystemExit('The SDK Node runtime with memory64 support is required.')
    env = dict(os.environ, TZ=os.environ.get('TZ', 'America/New_York'))
    env['PATH'] = str(nodes[-1].parent) + os.pathsep + env.get('PATH', '')
    command = ['bash', 'frozen/score.sh']
    if args.session: command.append(str(stage / 'sessions' / args.session))
    stem = 'single-session' if args.session else 'public'
    stdout = build / (stem + '.stdout.txt')
    stderr = build / (stem + '.stderr.txt')
    inputs = {'adapter_source_sha256': digest(adapter),
              'candidate_factory_sha256': digest(build / 'game.mjs'),
              'candidate_wasm_sha256': digest(build / 'nethack.wasm'),
              'frozen_harness_sha256': digest(stage / 'frozen/ps_test_runner.mjs'),
              'terminal_source': 'frozen/terminal.js', 'storage_source': 'frozen/storage.js',
              'game_factory': str(build / 'game.mjs'), 'node': str(nodes[-1]),
              'session': args.session, 'timezone': env['TZ']}
    (build / (stem + '-inputs.json')).write_text(json.dumps(inputs, indent=2) + '\n')
    with stdout.open('w') as out, stderr.open('w') as err:
        result = subprocess.run(command, cwd=stage, env=env, stdout=out, stderr=err)
    raw = stdout.read_text()
    marker = '__RESULTS_JSON__'
    if marker not in raw:
        raise SystemExit(f'No scoring result (exit {result.returncode}); inspect {stderr}')
    bundle = json.loads(raw.rsplit(marker, 1)[1])
    rows = bundle['results']
    metrics = {}
    for row in rows:
        for name, value in row.get('metrics', {}).items():
            target = metrics.setdefault(name, {'matched': 0, 'total': 0})
            for field in target: target[field] += value[field]
    summary = {'passed': sum(row['passed'] for row in rows), 'total': len(rows),
               'metrics': metrics, 'errors': [{'session': row['session'], 'error': row['error']}
                                             for row in rows if row.get('error')]}
    (build / (stem + '-summary.json')).write_text(json.dumps(summary, indent=2) + '\n')
    print(json.dumps(summary, indent=2))
    raise SystemExit(0 if summary['passed'] == summary['total'] and result.returncode == 0 else 1)


if __name__ == '__main__':
    main()
