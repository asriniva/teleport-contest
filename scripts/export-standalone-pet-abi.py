#!/usr/bin/env python3
"""Bind DOG's existing native global map and unchanged adapter/source."""
import json,hashlib,re
from pathlib import Path
root=Path(__file__).resolve().parents[1];support=root/'nethack-c/wasm/tu-dog-support.inc';text=support.read_text().split('void*teleport_dog_global(int i){switch(i){',1)[1].split('default:',1)[0]
rows=[(int(i),name)for i,name in re.findall(r'case (\d+):return\s*(?:\(void\*\))?\s*&?(\w+);',text)]
if [i for i,_ in rows]!=list(range(25)):raise ValueError('Review DOG global map')
paths=[Path(__file__).resolve(),support,root/'js/ported/dog.js',root/'js/nethack/bindings/dog.js',root/'nethack-c/wasm/compile-defines.json'];sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
(root/'js/standalone/pet-abi.json').write_text(json.dumps({'globals':[n for _,n in rows],'sourceSha256':{str(p.relative_to(root)):sha(p)for p in paths}},indent=2)+'\n');print('Bound DOG globals and adapter/source transport.')
