#!/usr/bin/env python3
"""Bind unchanged WERE source/native transport and configured record metadata."""
import hashlib,json,re
from pathlib import Path
root=Path(__file__).resolve().parents[1]
lib=(root/'nethack-c/wasm/tu-libraries/were.js').read_text()
support=(root/'nethack-c/wasm/tu-support.c').read_text().split('/* Shared were.c',1)[1].split('/* Rogue level',1)[0]
globals=re.findall(r'case \d+: return &?(\w+);',support.split('int teleport_were_monster_bit',1)[0])+['gm']
bits=re.findall(r'case \d+: return mon->(\w+);',support)+re.findall(r'default: return mon->(\w+);',support)
public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions']
calls={}
for name,params,target,args in re.findall(r'^      (\w+): (\w+|\([^)]*\)) => (?:Number\()?_(\w+)\((.*?)\)\)?[,]?$',lib,re.M):
 if target.startswith('teleport_were_'):continue
 calls[name]=target
paths=['scripts/export-standalone-were-abi.py','js/standalone/were.js','js/ported/were.js','js/nethack/bindings/were.js','js/nethack/runtime.js','js/ported/calendar.js','nethack-c/wasm/tu-libraries/were.js','nethack-c/wasm/tu-support.c','scripts/tu-were-layout.h','js/wasm/tu-layouts.json','js/standalone/records.json','js/standalone/public-functions.json']
data={'layout':json.loads((root/'js/wasm/tu-layouts.json').read_text())['were'],'globals':globals,'bits':bits,'calls':calls,'public':{name:public[name]for name in re.findall(r'^export function (\w+)',(root/'js/ported/were.js').read_text(),re.M)},'sourceSha256':{p:hashlib.sha256((root/p).read_bytes()).hexdigest()for p in paths}}
assert globals==['mons','u','flags','gw','svc','gy','gm']
assert bits==['msleeping','mfrozen','mcanmove','mpeaceful']
(root/'js/standalone/were-abi.json').write_text(json.dumps(data,indent=2)+'\n')
print('Bound original WERE source, native bridge, live globals and configured ABI.')
