#!/usr/bin/env python3
"""Bind unchanged WEAPON/WORN/WIELD global and equipment transport maps."""
import json,hashlib,re
from pathlib import Path
root=Path(__file__).resolve().parents[1]
support=root/'nethack-c/wasm/tu-support.c';weapon=root/'nethack-c/wasm/tu-weapon-support.inc'
def mapping(text,name):
 body=text.split(name+'(int index)',1)[1].split('default:',1)[0]
 rows=[(int(i),v)for i,v in re.findall(r'case (\d+):return\s*(?:\(void\*\))?\s*&?(\w+);',body)]
 assert [i for i,_ in rows]==list(range(len(rows))) and rows,name
 return [v for _,v in rows]
data={}
for name in ['weapon','worn','wield']:
 text=(weapon if name=='weapon' else support).read_text()
 data[name]={'globals':mapping(text,'teleport_'+name+'_global')}
 if name!='weapon':data[name]['equipment']=mapping(text,'teleport_'+name+'_equipment_cell')
inputs=[Path(__file__).resolve(),support,weapon,root/'nethack-c/wasm/compile-defines.json',*[root/('js/ported/'+n+suffix)for n in ['weapon','worn','wield']for suffix in ['.js','-runtime.js']]]
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
data['sourceSha256']={str(p.relative_to(root)):sha(p)for p in inputs}
(root/'js/standalone/equipment-abi.json').write_text(json.dumps(data,indent=2)+'\n')
print('Bound equipment global/cell maps to unchanged original transport.')
