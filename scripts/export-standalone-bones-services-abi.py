#!/usr/bin/env python3
"""Bind BONES service coercions to its unchanged original native adapter."""
import hashlib,json,re
from pathlib import Path
root=Path(__file__).resolve().parents[1]
library=root/'nethack-c/wasm/tu-libraries/bones.js'
public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions']
calls={}
for name,number,target,args in re.findall(r'^\s*(\w+):\([^)]*\)=>(Number\()?_(\w+)\(([^\n]*)',library.read_text(),re.M):
    if target.startswith('teleport_bones_'):continue
    assert target in public,target
    coercions=[]
    for match in re.finditer(r'\b(pointer|text|byte|coord|long)\(a(\d+)\)|Number\(a(\d+)\)',args):
        coercions.append((match[1]or'integer',int(match[2]or match[3])))
    assert [i for _,i in coercions]==list(range(len(coercions))),(name,args)
    calls[name]={'target':target,'number':bool(number),'coercions':[kind for kind,_ in coercions],'prototype':public[target]}
source=root/'js/ported/bones.js'
names=re.findall(r'^export function (\w+)\(',source.read_text(),re.M)
paths=[Path(__file__).resolve(),library,source,root/'js/ported/bones-runtime.js',root/'nethack-c/wasm/tu-fragments/bones-support.c',root/'js/standalone/bones-services.js',root/'js/standalone/public-functions.json']
data={'calls':calls,'public':{name:public[name]for name in names if name in public},'sourceSha256':{str(p.relative_to(root)):hashlib.sha256(p.read_bytes()).hexdigest()for p in paths}}
(root/'js/standalone/bones-services-abi.json').write_text(json.dumps(data,indent=2)+'\n')
print(f'Bound BONES: {len(calls)} native calls/{len(data["public"])} public entries')
