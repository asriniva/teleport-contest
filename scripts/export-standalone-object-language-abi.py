#!/usr/bin/env python3
"""Bind unchanged OBJNAM transport descriptors; no naming policy translation."""
import json,hashlib,re
from pathlib import Path
root=Path(__file__).resolve().parents[1];runtime=root/'js/nethack/bindings/objnam.js';text=runtime.read_text()
def declaration(n):return json.JSONDecoder().raw_decode(text[re.search(r'const\s+'+n+r'\s*=\s*',text).end():])[0]
schema=declaration('schema');bits=declaration('bitIndices');ordered=[None]*len(bits)
for key,i in bits.items():ordered[i]=key.rsplit('.',1)
support=root/'nethack-c/wasm/tu-objnam-support.inc';library=root/'nethack-c/wasm/tu-libraries/objnam.js';mapping=json.JSONDecoder().raw_decode(library.read_text().split('staticStorage:name=>{const index=',1)[1])[0];line=next(l for l in support.read_text().splitlines()if l.startswith('static char objnam_and_contents'));sizes=[int(n)for n in re.findall(r'objnam_\w+\[(\d+)\]',line)];assert sorted(mapping.values())==list(range(len(sizes)))
paths=[library,Path(__file__).resolve(),runtime,root/'js/ported/objnam.js',root/'nethack-c/wasm/compile-defines.json',root/'nethack-c/wasm/tu-objnam-support.inc'];sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
(root/'js/standalone/object-language-abi.json').write_text(json.dumps({'globals':list(schema['globals']),'bits':ordered,'staticBuffers':{name:sizes[i]for name,i in mapping.items()},'sourceSha256':{str(p.relative_to(root)):sha(p)for p in paths}},indent=2)+'\n');print('Bound OBJNAM globals and packed fields.')
