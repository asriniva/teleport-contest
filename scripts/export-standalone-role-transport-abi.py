#!/usr/bin/env python3
"""Bind ROLE assertion and checked string-length sites to native source helpers."""
import hashlib
import json
import os
import re
from pathlib import Path

root=Path(__file__).resolve().parents[1]
ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve()
support=root/'nethack-c/wasm/tu-role-support.inc'
text=support.read_text()
asserts=[(int(i),{'expression':expression,'file':file,'line':int(line),'function':function})for i,expression,file,line,function in re.findall(r'case (\d+):__assert_fail\("([^"]*)","([^"]*)",(\d+),"([^"]*)"\);break;',text)]
lengths=[(int(i),{'function':function,'line':int(line)})for i,function,line in re.findall(r'case (\d+):return Strlen_\(s,"([^"]*)",(\d+)\);',text)]
if [i for i,_ in asserts]!=list(range(5)) or [i for i,_ in lengths]!=list(range(6)):raise ValueError('Review ROLE source helper sites')
paths=[Path(__file__).resolve(),support,root/'nethack-c/wasm/tu-libraries/role.js',root/'js/ported/role.js',root/'js/ported/role-runtime.js']
headers=[ref/'.cache/wasm64-build/tree/include'/name for name in ['winprocs.h','extern.h']]
winprocs=headers[0].read_text()
for name in ['create_nhwindow','start_menu','end_menu','destroy_nhwindow','putstr','askname']:
 if not re.search(r'#define\s+'+name+r'\s+\(\*windowprocs.win_'+name+r'\)',winprocs):raise ValueError('Review ROLE window macro '+name)
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
data={'assertSites':[row for _,row in asserts],'strlenSites':[row for _,row in lengths],'sourceSha256':{str(p.relative_to(root)):sha(p)for p in paths},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in headers}}
(root/'js/standalone/role-transport-abi.json').write_text(json.dumps(data,indent=2)+'\n')
print('Bound original ROLE assertion and checked string-length sites.')
