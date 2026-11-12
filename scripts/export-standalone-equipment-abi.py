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
inputs=[Path(__file__).resolve(),root/'js/standalone/hero-equipment.js',root/'js/standalone/records.json',root/'nethack-c/wasm/tu-libraries/weapon.js',root/'nethack-c/wasm/tu-libraries/wield.js',support,weapon,root/'nethack-c/wasm/compile-defines.json',*[root/('js/ported/'+n+suffix)for n in ['weapon','worn','wield']for suffix in ['.js','-runtime.js']]]
# Native source/library and measured window record bind this macro dispatch.
fields=json.loads((root/'js/standalone/records.json').read_text())['records']['window_procs']['fields']
windows={'create_nhwindow':('win_create_nhwindow','ii'),'start_menu':('win_start_menu','vij'),'end_menu':('win_end_menu','vip'),'destroy_nhwindow':('win_destroy_nhwindow','vi')}
data['weapon']['windows']={name:{'field':field,'signature':sig,'nativeType':fields[field]['ctype']}for name,(field,sig)in windows.items()}
header=root/'.cache/wasm64-build/tree/include/hack.h'
assert "#define ynq(query) yn_function(query, ynqchars, 'q', TRUE)" in header.read_text()
assert "#define y_n(query) yn_function(query, ynchars, 'n', TRUE)" in header.read_text()
assert 'char teleport_weapon_y_n(const char *prompt) { return y_n(prompt); }'in weapon.read_text()
data['weapon']['y_n']={'target':'yn_function','choices':'ynchars','default':110,'logging':1}
inputs.append(header)
colors=root/'.cache/wasm64-build/tree/include/decl.h'
for macro,field in [('BLACK','black'),('BLUE','blue'),('AMBER','amber')]:assert '#define NH_'+macro+' c_color_names.c_'+field in colors.read_text()
inputs.append(colors)
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
data['sourceSha256']={str(p.relative_to(root)):sha(p)for p in inputs}
(root/'js/standalone/equipment-abi.json').write_text(json.dumps(data,indent=2)+'\n')
print('Bound equipment global/cell maps to unchanged original transport.')
