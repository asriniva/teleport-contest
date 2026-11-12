#!/usr/bin/env python3
"""Bind unchanged GETLINE native global/scalar transport maps."""
import hashlib
import json
import re
from pathlib import Path

root = Path(__file__).resolve().parents[1]
support = root / 'nethack-c/wasm/tu-support.c'
source = support.read_text()
def mapping(name, count):
    body = source.split(name + '(int index)', 1)[1].split('\n}', 1)[0]
    rows = [(int(i), value) for i, value in re.findall(r'case (\d+):\s*return\s*&?(\w+);', body)]
    if [i for i, _ in rows] != list(range(count - 1)):
        raise ValueError('Review changed GETLINE map: ' + name)
    last = re.search(r'default:\s*return\s*&?(\w+);', body)
    if not last:
        raise ValueError('Review changed GETLINE default: ' + name)
    return [value for _, value in rows] + [last[1]]
globals_ = mapping('teleport_getline_global', 6)
scalars = mapping('teleport_getline_scalar', 3)
setter = source.split('void teleport_getline_set_scalar(int index, int value)', 1)[1].split('\n}', 1)[0]
assignments = [(int(i), value) for i, value in re.findall(r'case (\d+):\s*(\w+) = value;', setter)]
last = re.search(r'default:\s*(\w+) = value;', setter)
if assignments != list(enumerate(scalars[:-1])) or not last or last[1] != scalars[-1]:
    raise ValueError('Review changed GETLINE scalar write map')
paths = [Path(__file__).resolve(), support,
         root / 'nethack-c/wasm/tu-libraries/getline.js', root / 'scripts/tu-getline-layout.h',
         root / 'js/ported/getline.js', root / 'js/nethack/bindings/getline.js',
         root / 'nethack-c/wasm/compile-defines.json', root / 'js/wasm/tu-layouts.json']
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
data = {'globals': globals_, 'scalars': scalars,
        'sourceSha256': {str(p.relative_to(root)): sha(p) for p in paths}}
(root / 'js/nethack/terminal-input-abi.json').write_text(json.dumps(data, indent=2) + '\n')
print('Bound original GETLINE globals and shared scalar cells.')
