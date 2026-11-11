#!/usr/bin/env python3
"""Bind existing MON fields/global transport without policy changes."""
import json,re,hashlib
from pathlib import Path
root=Path(__file__).resolve().parents[1];runtime=root/'js/ported/mon-runtime.js';support=root/'nethack-c/wasm/tu-mon-support.inc';text=runtime.read_text();schema=json.JSONDecoder().raw_decode(text.split('const schema=',1)[1])[0];bits=json.JSONDecoder().raw_decode(text.split('bits=',1)[1])[0];body=support.read_text().split('void*teleport_mon_global(int i){switch(i){',1)[1].split('default:',1)[0];rows=[(int(i),n)for i,n in re.findall(r'case (\d+):return\s*(?:\(void\*\))?\s*&?(\w+);',body)]
if [i for i,_ in rows]!=list(range(35)):raise ValueError('Review MON global map')
paths=[Path(__file__).resolve(),runtime,support,root/'js/ported/mon.js',root/'nethack-c/wasm/compile-defines.json'];sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
(root/'js/standalone/mon-abi.json').write_text(json.dumps({'schema':schema,'bits':bits,'globals':[n for _,n in rows],'sourceSha256':{str(p.relative_to(root)):sha(p)for p in paths}},indent=2)+'\n');print('Bound MON schema and globals.')
