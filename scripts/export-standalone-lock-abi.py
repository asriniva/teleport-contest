#!/usr/bin/env python3
"""Bind unchanged LOCK native global, packed-field and callback transport."""
import hashlib,json,re
from pathlib import Path
root=Path(__file__).resolve().parents[1];lib=(root/'nethack-c/wasm/tu-libraries/lock.js').read_text();support=(root/'nethack-c/wasm/tu-support.c').read_text().split('/* LOCK:',1)[1].split('static char teleport_lock_literals',1)[0];public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions'];calls={}
for name,target in re.findall(r'^      (\w+):[^\n]*?=> (?:Number\()?_(\w+)\(',lib,re.M):
 if not target.startswith('teleport_lock_'):calls[name]={'target':target,'prototype':public[target]}
glob=support.split('struct obj *teleport_lock_equipment',1)[0];obj=support.split('int teleport_lock_object_bit',1)[1].split('void teleport_lock_set_object_bit',1)[0]
paths=['scripts/export-standalone-lock-abi.py','js/standalone/lock.js','js/ported/lock.js','js/ported/lock-runtime.js','nethack-c/wasm/tu-libraries/lock.js','nethack-c/wasm/tu-support.c','scripts/tu-lock-layout.h','js/wasm/tu-layouts.json','js/standalone/public-functions.json','js/standalone/records.json']
data={'layout':json.loads((root/'js/wasm/tu-layouts.json').read_text())['lock'],'globals':re.findall(r'case \d+: return &?(\w+);',glob),'objectBits':re.findall(r'case \d+: return obj->(\w+);',obj),'monsterBits':['mpeaceful','isshk'],'callbacks':['picklock','forcelock'],'calls':calls,'public':{n:public[n]for n in re.findall(r'^export function (\w+)',(root/'js/ported/lock.js').read_text(),re.M)if n in public},'sourceSha256':{p:hashlib.sha256((root/p).read_bytes()).hexdigest()for p in paths}}
assert len(data['globals'])==16 and len(data['objectBits'])==9
(root/'js/standalone/lock-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound original LOCK storage, packed fields, typed calls and occupation callbacks.')
