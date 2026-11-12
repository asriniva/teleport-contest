#!/usr/bin/env python3
"""Export existing VISION adapter descriptors; measured fields stay in records."""
import hashlib,json
from pathlib import Path
root=Path(__file__).resolve().parents[1];runtime=root/'js/nethack/bindings/vision.js'
def declaration(name):
 line=next(s for s in runtime.read_text().splitlines()if s.startswith('const '+name+'='))
 return json.loads(line[len('const '+name+'='):-1])
paths=[runtime,Path(__file__).resolve(),root/'nethack-c/wasm/tu-vision-support.inc',root/'js/nethack/vision.js',root/'nethack-c/wasm/tu-libraries/vision.js']
data={name:declaration(name)for name in ['schemas','globals','privateStorage']}
data['sourceSha256']={str(p.relative_to(root)):hashlib.sha256(p.read_bytes()).hexdigest()for p in paths}
(root/'js/nethack/vision-abi.json').write_text(json.dumps(data,indent=2)+'\n')
print('Exported VISION adapter descriptors.')
