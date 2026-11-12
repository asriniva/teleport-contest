#!/usr/bin/env python3
"""Bind the original MHITU schemas, native calls and format ABI."""
import hashlib,json,re
from pathlib import Path
root=Path(__file__).resolve().parents[1]
schema=json.loads((root/'nethack-c/wasm/tu-fragments/mhitu-schema.json').read_text())
lib=(root/'nethack-c/wasm/tu-libraries/mhitu.js').read_text()
public=json.loads((root/'js/nethack/public-functions.json').read_text())['functions']
calls={}
for name,target in re.findall(r'^\s+(\w+):\([^)]*\)=>(?:Number\()?_(\w+)\(',lib,re.M):
 if target.startswith('teleport_mhitu_'):continue
 if target not in public:raise ValueError('Missing original MHITU foreign prototype '+target)
 calls[name]={'target':target,'prototype':public[target]}
source=(root/'js/ported/mhitu.js').read_text()
exports=[n for n in re.findall(r'^export function (\w+)\(',source,re.M)if n in public]
paths=['scripts/export-standalone-mhitu-abi.py','js/nethack/mhitu.js','js/ported/mhitu.js','js/nethack/bindings/mhitu.js','nethack-c/wasm/tu-fragments/mhitu-schema.json','nethack-c/wasm/tu-fragments/mhitu-support.c','nethack-c/wasm/tu-libraries/mhitu.js','js/nethack/public-functions.json','js/nethack/records.json','js/wasm/tu-layouts.json']
data={'layout':json.loads((root/'js/wasm/tu-layouts.json').read_text())['mhitu'],'schemas':schema['schema'],'globals':schema['globals'],'rngSites':schema['rngSites'],'variadicABI':schema['variadicABI'],'calls':calls,'public':exports,'callbacks':['xname','simpleonames'],'sourceSha256':{p:hashlib.sha256((root/p).read_bytes()).hexdigest()for p in paths}}
(root/'js/nethack/mhitu-abi.json').write_text(json.dumps(data,indent=2)+'\n')
print('Bound original MHITU native schemas, calls, RNG and format ABI.')
