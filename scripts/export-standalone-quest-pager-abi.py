#!/usr/bin/env python3
"""Bind QUESTPGR's unchanged native global/packed-field transport map."""
import hashlib
import json
import re
from pathlib import Path

root = Path(__file__).resolve().parents[1]
support = root / 'nethack-c/wasm/tu-questpgr-support.inc'
source = support.read_text()
body = source.split('void *teleport_questpgr_global(int i){switch(i){', 1)[1].split('}}', 1)[0]
rows = [(int(i), name) for i, name in re.findall(r'case (\d+):return\s*(?:\(void\*\))?\s*&?(\w+);', body)]
if [i for i, _ in rows] != list(range(15)):
    raise ValueError('Review changed QUESTPGR indexed globals')
fallback = re.search(r'default:return &(\w+);', body)
if not fallback:
    raise ValueError('Review changed QUESTPGR final global')
bits = source.split('unsigned teleport_questpgr_quest_bit(int i){switch(i){', 1)[1].split('}}', 1)[0]
bit_rows = [(int(i), name) for i, name in re.findall(r'case (\d+):return svq.quest_status\.(\w+);', bits)]
if [i for i, _ in bit_rows] != [0, 1]:
    raise ValueError('Review changed QUESTPGR packed fields')
last_bit = re.search(r'default:return svq.quest_status\.(\w+);', bits)
if not last_bit:
    raise ValueError('Review changed QUESTPGR final packed field')
paths = [Path(__file__).resolve(), support,
         root / 'nethack-c/wasm/tu-libraries/questpgr.js',
         root / 'scripts/tu-questpgr-layout.h',
         root / 'js/ported/questpgr.js', root / 'js/nethack/bindings/questpgr.js',
         root / 'nethack-c/wasm/compile-defines.json',
         root / 'js/wasm/tu-layouts.json', root / 'js/standalone/records.json']
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
data = {'globals': [name for _, name in rows] + [fallback[1]],
        'questBits': [name for _, name in bit_rows] + [last_bit[1]],
        'sourceSha256': {str(p.relative_to(root)): sha(p) for p in paths}}
(root / 'js/standalone/quest-pager-abi.json').write_text(json.dumps(data, indent=2) + '\n')
print('Bound original QUESTPGR global/packed-field transport.')
