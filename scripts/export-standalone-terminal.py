#!/usr/bin/env python3
"""Extract transport descriptors; original TERMCAP policy stays unchanged."""
import ast,hashlib,json,re
from pathlib import Path
source=Path('js/ported/termcap-runtime.js')
text=source.read_text()
values={}
for name in ['schemas','globals','functions','foreignCallbacks','bufferKeys']:
    tail=text.split('const '+name+'=',1)[1]
    if name in ['schemas','globals']:
        value=json.JSONDecoder().raw_decode(tail)[0]
    else:
        value=ast.literal_eval(tail[:tail.index(']')+1])
    values[name]=value
library=Path('nethack-c/wasm/tu-libraries/termcap.js')
values['signatures']=dict(re.findall(r'\b(\w+)__sig\s*:\s*[\'"]([^\'"]+)',library.read_text()))
for name,signature in list(values['signatures'].items()):
    for prefix in ['teleport_termcap_test_','teleport_termcap_callback_']:
        if name.startswith(prefix):
            original=name[len(prefix):]
            if original in values['signatures'] and values['signatures'][original]!=signature:raise ValueError('Conflicting terminal callback ABI '+original)
            values['signatures'][original]=signature
for name in values['functions']:
    if name not in values['signatures']:raise ValueError('Missing original terminal callback ABI '+name)
support=Path('nethack-c/wasm/tu-fragments/termcap-support.c')
header=Path('nethack-c/wasm/tu-fragments/termcap-source-data.h')
values['typeAliases']=dict(re.findall(r'^#define (TELEPORT_TERMCAP_TI_MAP_TYPE) (struct \w+)$',header.read_text(),re.M))
values['bufferSizes']=[int(n) for _,n in re.findall(r'static char teleport_termcap_buffer_(\d+)\[(\d+)\];',support.read_text())]
if len(values['bufferSizes'])!=len(values['bufferKeys']):raise ValueError('Terminal static buffer ABI mismatch')
values['sourceSha256']={str(p):hashlib.sha256(p.read_bytes()).hexdigest() for p in [Path(__file__).relative_to(Path.cwd()),source,Path('js/standalone/terminal.js'),library,support,header]}
Path('js/standalone/terminal-metadata.json').write_text(json.dumps(values,indent=2)+'\n')
print('Exported terminal storage, callback signatures and buffer descriptors')
