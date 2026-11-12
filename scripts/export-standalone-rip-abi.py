#!/usr/bin/env python3
"""Bind unchanged RIP bridge/native ABI and Clang-measured shared fields."""
import hashlib,json,re
from pathlib import Path
root=Path(__file__).resolve().parents[1]
records=json.loads((root/'js/standalone/records.json').read_text())['records']
layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['rip']
support=(root/'nethack-c/wasm/tu-support.c').read_text()
expected={'teleport_rip_head_pointer':'return &gr.rip;', 'teleport_rip_name':'return svp.plname;', 'teleport_rip_money':'return gd.done_money;'}
for name,body in expected.items():
 found=re.search(r'\b'+name+r'\([^)]*\)\s*\{([^}]+)\}',support)
 assert found and found[1].strip()==body,name
formats={'%.*s':['int','pointer'],'%ld Au':['long'],'%4d':['int']}
for fmt in formats:assert '"'+fmt+'"' in support
fields={}
for name,typ,glob,field in [('head','struct instance_globals_r','gr','rip'),('name','struct instance_globals_saved_p','svp','plname'),('money','struct instance_globals_d','gd','done_money')]:
 record=records[typ.removeprefix('struct ')];row=record['fields'][field]
 fields[name]={'type':typ,'global':glob,'field':field,'offset':row['offset'],'ctype':row['ctype']}
paths=['scripts/export-standalone-rip-abi.py','js/standalone/rip.js','js/ported/rip.js','js/backends/emscripten/runtime.js','nethack-c/wasm/tu-libraries/rip.js','nethack-c/wasm/tu-support.c','nethack-c/wasm/compile-defines.json','js/wasm/tu-layouts.json','js/standalone/records.json']
data={'layout':layout,'fields':fields,'formats':formats,'sourceSha256':{p:hashlib.sha256((root/p).read_bytes()).hexdigest()for p in paths}}
(root/'js/standalone/rip-abi.json').write_text(json.dumps(data,indent=2)+'\n')
print('Bound original RIP bridge, global fields and format transport.')
