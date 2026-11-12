#!/usr/bin/env python3
"""Measure UTF8MAP against the existing golden configured Emscripten headers."""
import hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';clang=ref/'.cache/emsdk/upstream/bin/clang'
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
fields={'gbuf':('gg','struct instance_globals_g','gbuf'),'showsyms':('gs','struct instance_globals_s','showsyms'),'customizations':('gs','struct instance_globals_s','sym_customizations'),'currentgraphics':('gc','struct instance_globals_c','currentgraphics')}
with tempfile.TemporaryDirectory(prefix='utf8map-abi-')as tmp:
 probe=Path(tmp)/'abi.c';include='#include '+json.dumps(str(root/'scripts/tu-utf8map-layout.h'))+'\n';probe.write_text(include)
 expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(probe)],text=True)
 table=re.search(r'utf8map_layout\[\]\s*=\s*\{(.*?)\n\};',expanded,re.S);assert table
 expressions=dict(re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}',table[1],re.S))
 for name,(_,typ,key)in fields.items():expressions['field_'+name]='offsetof('+typ+','+key+')'
 probe.write_text(include+'\n'.join('const unsigned long probe_'+key+'=('+expr+');'for key,expr in expressions.items()))
 ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(probe)],text=True)
 values={key:int(re.search(r'@probe_'+key+r' = .*?constant i64 (-?\d+)',ir)[1])&((1<<64)-1)for key in expressions}
 layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['utf8map']
 assert set(layout)-{'size'}==set(values)-{'field_'+n for n in fields},(set(layout),set(values))
 for key,value in layout.items():
  if key!='size':assert value==values[key],key
 deps=subprocess.check_output([str(clang),*flags,'-M',str(probe)],text=True)
 headers={Path(p).resolve()for p in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(p).resolve().is_relative_to(ref)}
public=json.loads((root/'js/nethack/public-functions.json').read_text())['functions'];names=re.findall(r'^export function (\w+)',(root/'js/ported/utf8map.js').read_text(),re.M);assert len(names)==6
paths=['scripts/test-standalone-utf8map.mjs','scripts/check-standalone-utf8map.mjs','scripts/export-standalone-utf8map-abi.py','js/nethack/utf8map.js','js/ported/utf8map.js','js/nethack/bindings/utf8.js','scripts/tu-utf8map-layout.h','nethack-c/wasm/tu-libraries/utf8map.js','nethack-c/wasm/tu-support.c','nethack-c/wasm/compile-defines.json','js/nethack/records.json','js/nethack/public-functions.json','js/wasm/tu-layouts.json']
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
data={'layout':layout,'fields':{name:{'global':g,'type':typ,'field':key,'offset':values['field_'+name]}for name,(g,typ,key)in fields.items()},'public':{name:public[name]for name in names},'sourceSha256':{p:sha(root/p)for p in paths},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(headers)}}
(root/'js/nethack/utf8map-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Measured original UTF8MAP layout and shared record fields.')
