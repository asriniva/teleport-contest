#!/usr/bin/env python3
"""Bind the shared EAT hunger table to the original native storage contract."""
import hashlib
import json
import re
from pathlib import Path

root=Path(__file__).resolve().parents[1]
support=root/'nethack-c/wasm/tu-eat-support.inc'
source=root/'js/ported/eat.js'
count=int(re.search(r'extern const char\*const hu_stat\[(\d+)\];',support.read_text())[1])
if 'case 0:return(void*)hu_stat;' not in support.read_text():raise ValueError('Review EAT storage0')
values=json.loads(re.search(r'export const hu_stat = (\[[\s\S]*?\]);',source.read_text())[1])
layouts=json.loads((root/'js/wasm/tu-layouts.json').read_text())
if len(values)!=count or layouts['eat']['pointerSize']!=8:raise ValueError('Review EAT hunger table profile')
paths=[Path(__file__).resolve(),support,source,root/'js/nethack/bindings/eat.js',root/'js/wasm/tu-layouts.json']
data={'pointerSize':8,'count':count,'storageIndex':0,'sourceSha256':{str(p.relative_to(root)):hashlib.sha256(p.read_bytes()).hexdigest()for p in paths}}
(root/'js/nethack/hunger-data-abi.json').write_text(json.dumps(data,indent=2)+'\n')
print('Bound original EAT hunger text pointer table.')
