#!/usr/bin/env python3
"""Record typed dispatch recipes from the existing C Lua transport wrappers."""
import hashlib,json,re
from pathlib import Path
source=Path('nethack-c/wasm/lua-bridge.c')
rows={}
for line in source.read_text().splitlines():
    head=re.match(r'^(.*?)\b(lua(?:L)?_\w+|luaopen_\w+)\(([^)]*)\) \{(.*)\}$',line)
    if not head:
        continue
    ret,name,params,body=head.groups()
    dispatch=re.search(r'\bD([0-5])\(',body)
    if not dispatch:
        continue
    start=dispatch.end();depth=1;end=start
    while depth:
        if body[end]=='(':depth+=1
        elif body[end]==')':depth-=1
        end+=1
    args=[v.strip() for v in body[start:end-1].split(',')]
    operation=args[1].strip('"')
    if operation!=name:
        raise ValueError('Unexpected Lua operation '+name)
    names=[re.search(r'(\w+)(?:\[\])?$',p.strip())[1] for p in params.split(',') if p.strip()!='void']
    recipe=[]
    for arg in [args[0],*args[2:]]:
        number=re.fullmatch(r'number_bits\((\w+)\)',arg)
        value=number[1] if number else arg
        recipe.append({'index':None if value=='NULL' else names.index(value),'number':bool(number)})
    if len(recipe)!=int(dispatch[1])+1:
        raise ValueError('Wrong Lua recipe arity '+name)
    rows[name]={'return':ret.strip(),'arguments':recipe}
Path('js/nethack/lua-api.json').write_text(json.dumps({'source':str(source),'sha256':hashlib.sha256(source.read_bytes()).hexdigest(),'functions':rows},indent=2)+'\n')
print(f'Exported {len(rows)} typed Lua dispatch recipes')
