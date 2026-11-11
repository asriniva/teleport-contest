#!/usr/bin/env python3
"""Bind ATTRIB public/dependency transport additions to unchanged native helpers."""
import hashlib
import json
import os
import re
from pathlib import Path

root=Path(__file__).resolve().parents[1]
ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve()
support=root/'nethack-c/wasm/tu-fragments/attrib-support.inc'
library=root/'nethack-c/wasm/tu-libraries/attrib.js'
text=support.read_text()
body=text.split('int teleport_attrib_object_bit(struct obj*o,int i){switch(i){',1)[1].split('default:',1)[0]
rows=[(int(i),name)for i,name in re.findall(r'case (\d+):return o->(\w+);',body)]
if [i for i,_ in rows]!=list(range(3)):raise ValueError('Review ATTRIB object packed fields')
for name in ['debug0','debug1_int','debug1_long','debug2','debug3']:
 body=text.split('void teleport_attrib_'+name+'(',1)[1].split('\n',1)[0]
 if 'if(debugcore("attrib.c",TRUE)){int saved=iflags.last_msg;'not in body or 'iflags.last_msg=saved;'not in body:raise ValueError('Review ATTRIB debug guard '+name)
if "debugpline1:(format,a)=>format.includes('%ld')?"not in library.read_text():raise ValueError('Review ATTRIB debug scalar width')
paths=[Path(__file__).resolve(),support,library,root/'js/ported/attrib.js',root/'js/ported/attrib-runtime.js',root/'js/standalone/public-functions.json',root/'scripts/tu-attrib-layout.h',root/'js/wasm/tu-layouts.json',root/'js/standalone/records.json',root/'nethack-c/wasm/compile-defines.json']
headers=[ref/'.cache/wasm64-build/tree/include'/name for name in ['lint.h','mondata.h','dungeon.h','global.h','decl.h']]
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
data={'objectBits':[name for _,name in rows],'debugSource':'attrib.c','sourceSha256':{str(p.relative_to(root)):sha(p)for p in paths},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in headers}}
(root/'js/standalone/attribute-abi.json').write_text(json.dumps(data,indent=2)+'\n')
print('Bound original ATTRIB object fields, debug guard and public prototypes.')
