#!/usr/bin/env python3
"""Bind original EXPER factory and native shared/format boundary inputs."""
import hashlib,json,re
from pathlib import Path
root=Path(__file__).resolve().parents[1];public=json.loads((root/'js/nethack/public-functions.json').read_text())['functions'];lib=(root/'nethack-c/wasm/tu-libraries/exper.js').read_text();support=(root/'nethack-c/wasm/tu-support.c').read_text().split('void *teleport_exper_global',1)[1].split('/* Cave map',1)[0];calls={}
for name,target in re.findall(r'^      (\w+):[^\n]*?=> (?:Number\()?_(\w+)\(',lib,re.M):
 if not target.startswith('teleport_exper_'):calls[name]={'target':target,'prototype':public[target]}
paths=['scripts/export-standalone-exper-abi.py','js/nethack/exper.js','js/ported/exper.js','js/nethack/bindings/exper.js','nethack-c/wasm/tu-libraries/exper.js','nethack-c/wasm/tu-support.c','scripts/tu-exper-layout.h','js/wasm/tu-layouts.json','js/nethack/public-functions.json','js/nethack/records.json']
names=re.findall(r'^export function (\w+)',(root/'js/ported/exper.js').read_text(),re.M)
data={'layout':json.loads((root/'js/wasm/tu-layouts.json').read_text())['exper'],'globals':re.findall(r'case \d+: return &(\w+);',support)+['mons'],'bits':['mrevived','mcloned'],'calls':calls,'public':{n:public[n]for n in names if n in public},'assertion':{'condition':'u.ulevel >= 0 && u.ulevel < MAXULEV','line':247,'function':'losexp'},'sourceSha256':{p:hashlib.sha256((root/p).read_bytes()).hexdigest()for p in paths}}
assert data['globals']==['u','gu','gy','flags','disp','svk','mons']
(root/'js/nethack/exper-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound original EXPER live globals, signatures, formats and assertion site.')
