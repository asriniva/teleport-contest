#!/usr/bin/env python3
"""Bind original MTHROWU native call types and live-memory transport."""
import hashlib,json,re
from pathlib import Path
root=Path(__file__).resolve().parents[1]
lib=(root/'nethack-c/wasm/tu-libraries/mthrowu.js').read_text();runtime=(root/'js/nethack/bindings/mthrowu.js').read_text();source=(root/'js/ported/mthrowu.js').read_text();public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions'];calls={}
for name,target in re.findall(r'^\s*(\w+):\([^)]*\)=>(?:Number\()?_(\w+)\(',lib,re.M):
 if target.startswith('teleport_mthrowu_'):continue
 if target not in public:raise ValueError('Unknown native MTHROWU prototype '+target)
 calls[name]={'target':target,'prototype':public[target]}
globals=re.findall(r"'([^']+)'",runtime.split('const globalNames=[',1)[1].split('];',1)[0])
exports=[n for n in re.findall(r'^export function (\w+)\(',source,re.M)if n in public]
paths=['scripts/export-standalone-mthrowu-abi.py','js/standalone/mthrowu.js','js/ported/mthrowu.js','js/nethack/bindings/mthrowu.js','nethack-c/wasm/tu-libraries/mthrowu.js','nethack-c/wasm/tu-mthrowu-support.inc','scripts/tu-mthrowu-layout.h','js/wasm/tu-layouts.json','js/standalone/records.json','js/standalone/public-functions.json']
data={'layout':json.loads((root/'js/wasm/tu-layouts.json').read_text())['mthrowu'],'calls':calls,'globals':globals,'public':exports,'sourceSha256':{p:hashlib.sha256((root/p).read_bytes()).hexdigest()for p in paths}}
(root/'js/standalone/mthrowu-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound original MTHROWU native calls/globals/layout.')
