#!/usr/bin/env python3
"""Bind unchanged TOPL globals and source-private persistent cells."""
import ast
import hashlib
import json
import re
from pathlib import Path

root = Path(__file__).resolve().parents[1]
runtime = root / 'js/ported/topl-runtime.js'
support = root / 'nethack-c/wasm/tu-fragments/topl-support.inc'
text = runtime.read_text()
declaration = lambda name: json.JSONDecoder().raw_decode(text.split('const ' + name + '=', 1)[1])[0]
globals_ = declaration('globals')
native = support.read_text()
body = native.split('const void*teleport_topl_global(int i){switch(i){', 1)[1].split('default:', 1)[0]
rows = [(int(i), name) for i, name in re.findall(r'case (\d+):return\(const void\*\)&(\w+);', body)]
if rows != list(enumerate(globals_)):
    raise ValueError('Review changed TOPL native/JS global map')
cells = re.search(r'for\(const\[name,type,i\]of(\[\[.*?\]\])\)Object\.defineProperty', text)
if not cells:
    raise ValueError('Review changed TOPL persistent descriptors')
persistent = ast.literal_eval(cells[1])
native_cells = re.findall(r'case (\d+):return &teleport_topl_persistent_bytes\.(\w+);', native)
if [(int(i), name) for i, name in native_cells] != [(i, name) for name, _, i in persistent]:
    raise ValueError('Review changed TOPL persistent cell map')
paths = [Path(__file__).resolve(), runtime, support,
         root / 'js/ported/topl.js', root / 'nethack-c/wasm/tu-libraries/topl.js',
         root / 'scripts/tu-topl-layout.h', root / 'nethack-c/wasm/compile-defines.json',
         root / 'js/wasm/tu-layouts.json']
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
data = {'globals': globals_, 'persistent': [{'name': name, 'type': typ, 'index': i} for name, typ, i in persistent],
        'sourceSha256': {str(p.relative_to(root)): sha(p) for p in paths}}
(root / 'js/standalone/terminal-messages-abi.json').write_text(json.dumps(data, indent=2) + '\n')
print('Bound original TOPL shared globals and persistent source cells.')
