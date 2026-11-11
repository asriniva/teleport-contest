#!/usr/bin/env python3
"""Bind unchanged PLINE field transport and source per-module initial state."""
import hashlib
import json
import os
import re
from pathlib import Path

root = Path(__file__).resolve().parents[1]
ref = Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve()
runtime = root / 'js/ported/pline-runtime.js'
support = root / 'nethack-c/wasm/tu-fragments/pline-support.c'
text = runtime.read_text()
fields = json.JSONDecoder().raw_decode(text.split('const fields=', 1)[1])[0]
body = support.read_text().split('void *teleport_pline_global(int field)', 1)[1].split('default:', 1)[0]
native = [(int(i), path) for i, path in re.findall(r'case (\d+):\s*return \(void \*\)&([\w.]+);', body)]
if native != [(i, path) for i, (path, _) in enumerate(fields)]:
    raise ValueError('Review changed PLINE global/field map')
state = re.search(r'state=\{in_pline:(\d+),use_pline_handler:(\d+)\}', text)
if not state:
    raise ValueError('Review changed PLINE private initial state')
headers = [ref / '.cache/wasm64-build/tree/include/hack.h', ref / '.cache/wasm64-build/tree/include/youprop.h']
email = re.search(r'^#define DEVTEAM_EMAIL\s+("[^"\n]*")', headers[0].read_text(), re.M)
if not email:
    raise ValueError('Review changed PLINE development-team macro')
paths = [Path(__file__).resolve(), runtime, support, root / 'js/ported/pline.js',
         root / 'nethack-c/wasm/tu-libraries/pline.js', root / 'scripts/tu-pline-layout.h',
         root / 'nethack-c/wasm/tu-fragments/pline-source-data.h',
         root / 'nethack-c/wasm/compile-defines.json', root / 'js/wasm/tu-layouts.json',
         root / 'js/standalone/records.json']
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
data = {'fields': fields, 'initialState': {'in_pline': int(state[1]), 'use_pline_handler': int(state[2])},
        'devteamEmail': json.loads(email[1]),
        'sourceSha256': {str(p.relative_to(root)): sha(p) for p in paths},
        'referenceHeaderSha256': {str(p.relative_to(ref)): sha(p) for p in headers}}
(root / 'js/standalone/messages-abi.json').write_text(json.dumps(data, indent=2) + '\n')
print('Bound original PLINE field/state/header transport.')
