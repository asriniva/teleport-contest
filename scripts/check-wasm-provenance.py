"""Verify the game artifact and every source hash declared by its manifest."""
import argparse
import hashlib
import json
from pathlib import Path

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[1])
args = parser.parse_args()
root = args.root.resolve()
manifest = json.loads((root / 'js/wasm/build.json').read_text())
expected = {}


def add(path, digest):
    relative = Path(path)
    assert not relative.is_absolute() and '..' not in relative.parts, path
    assert path not in expected or expected[path] == digest, f'Conflicting hashes: {path}'
    expected[path] = digest


def collect(value):
    if isinstance(value, dict):
        for key, child in value.items():
            if key in ['sourceSha256', 'adapterSourceSha256', 'javascriptDataSha256', 'nativeStorageSourceSha256'] and isinstance(child, dict):
                for path, digest in child.items():
                    add(path, digest)
            else:
                collect(child)
    elif isinstance(value, list):
        for child in value:
            collect(child)


collect(manifest)
for field, path in {
    'nativeAbiSha256': 'nethack-c/wasm/native-terminal.h',
    'ncursesSha256': '.cache/ncurses-6.5.tar.gz',
    'terminfoEntrySha256': 'nethack-c/wasm/terminfo/x/xterm-256color',
    'compressionSourceSha256': 'nethack-c/wasm/vendor/ncompress/compress.c',
}.items():
    if field in manifest:
        add(path, manifest[field])
for port in manifest['javascriptTranslationUnits']:
    add(port['javascript'], port['sha256'])
    add(port['library'], port['abiLibrarySha256'])
    add('.cache/wasm64-build/tree/' + port['source'], port['preparedCSourceSha256'])
add('js/wasm/nethack.wasm', manifest['wasmSha256'])
failures = []
for path, digest in expected.items():
    file = root / path
    if not file.is_file():
        failures.append(f'Missing declared input: {path}')
    elif hashlib.sha256(file.read_bytes()).hexdigest() != digest:
        failures.append(f'Stale manifest hash: {path}')
if failures:
    raise SystemExit('\n'.join(failures))
print(f'Wasm provenance verified: {len(expected)} artifact/source hashes, '
      f'{len(manifest["javascriptTranslationUnits"])} TUs.')
