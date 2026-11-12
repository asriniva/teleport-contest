#!/usr/bin/env python3
"""Export existing BONES ABI descriptors, never game algorithms."""
import hashlib,json,re
from pathlib import Path
root=Path(__file__).resolve().parents[1]
runtime=root/'js/nethack/bindings/bones.js';support=root/'nethack-c/wasm/tu-fragments/bones-support.c'
line=next(l for l in runtime.read_text().splitlines()if l.startswith('const schemas = '));schema=json.loads(line[len('const schemas = '):-1])
c=support.read_text().split('void teleport_bones_write',1)[0];types=re.findall(r'case (\d+): \{ (.*?) \*p=at;',c)
assert [int(i)for i,t in types]==list(range(len(schema)))
def declaration(path,name):
 line=next(l for l in path.read_text().splitlines()if l.startswith('const '+name+'='));return json.loads(line[len('const '+name+'='):-1])
decl=declaration(root/'js/nethack/bindings/decl.js','globals');global_types={r['name']:r['d'].get('s')for r in decl}
for i,(number,typ)in enumerate(types):
 match=re.fullmatch(r'__typeof__\((.*)\)',typ)
 if match:typ='dlevel_t'if match[1]=='svl.level'else global_types[match[1]]
 types[i]=typ
lines=json.loads('['+re.search(r'static const int lines\[\]=\{(.*?)\};',support.read_text())[1]+']');callers=json.loads('['+re.search(r'static const char \*const callers\[\]=\{(.*?)\};',support.read_text())[1]+']')
paths=[runtime,support,root/'js/nethack/bindings/decl.js',Path(__file__).resolve()]
(root/'js/standalone/level-abi.json').write_text(json.dumps({'bones':{'schema':schema,'types':types,'globals':global_types,'rngSites':list(zip(lines,callers))},'sourceSha256':{str(p.relative_to(root)):hashlib.sha256(p.read_bytes()).hexdigest()for p in paths}},indent=2)+'\n')
print('Exported original BONES transport descriptors and RNG call sites.')
