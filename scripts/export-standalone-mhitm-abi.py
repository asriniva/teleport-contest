#!/usr/bin/env python3
"""Bind unchanged MHITM native transport and configured source sites."""
import hashlib,json,os,re
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ.get('STANDALONE_REFERENCE_ROOT',root.parent/'teleport-contest'));native=root/'nethack-c/wasm/tu-mhitm-support.inc';lib=(root/'nethack-c/wasm/tu-libraries/mhitm.js').read_text();support=native.read_text();public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions'];source=root/'js/ported/mhitm.js';original=ref/'.cache/wasm64-build/tree/src/mhitm.c';c=original.read_text()
calls={}
for name,target in re.findall(r'^   (\w+):\([^\n]*?\)=>(?:Number\()?_(\w+)\(',lib,re.M):
 if not target.startswith('teleport_mhitm_'):
  if target not in public:raise ValueError('Missing native prototype '+target)
  calls[name]={'target':target,'prototype':public[target]}
globals=re.findall(r'case \d+:return &?(\w+);',support.split('unsigned teleport_mhitm_monster_bit',1)[0])
bits=re.findall(r'case \d+:return m->(\w+);',support.split('void teleport_mhitm_set_monster_bit',1)[0])+['mtrapped']
mask=lambda s:re.sub(r'/\*[\s\S]*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"',lambda m:re.sub(r'[^\n]',' ',m[0]),s)
clean=mask(c);sites=[]
for m in re.finditer(r'\bSnprintf\(',clean):
 at=clean.index('(',m.start());depth=1
 while depth:
  at+=1
  if clean[at]=='(':depth+=1
  elif clean[at]==')':depth-=1
 sites.append({'function':'hitmm','line':c[:at].count('\n')+1})
assert len(sites)==8 and len(globals)==17 and len(bits)==12
paths=[Path(__file__).resolve(),root/'js/standalone/mhitm.js',source,root/'js/ported/mhitm-runtime.js',native,root/'nethack-c/wasm/tu-libraries/mhitm.js',root/'scripts/tu-mhitm-layout.h',root/'js/wasm/tu-layouts.json',root/'js/standalone/public-functions.json',root/'js/standalone/records.json']
data={'layout':json.loads((root/'js/wasm/tu-layouts.json').read_text())['mhitm'],'globals':globals,'bits':bits,'calls':calls,'public':{n:public[n]for n in re.findall(r'^export function (\w+)',source.read_text(),re.M)if n in public},'formats':sites,'sourceSha256':{str(p.relative_to(root)):hashlib.sha256(p.read_bytes()).hexdigest()for p in paths},'referenceSourceSha256':{str(original):hashlib.sha256(original.read_bytes()).hexdigest()}}
(root/'js/standalone/mhitm-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound original MHITM globals, packed fields, public/native signatures and original formatting sites.')
