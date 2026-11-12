#!/usr/bin/env python3
"""Bind unchanged FILES descriptors and measure original private data/callbacks."""
import json,hashlib,os,re,shlex,subprocess
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';runtime=root/'js/nethack/bindings/files.js';text=runtime.read_text();source=tree/'src/files.c'
def declaration(name):return json.JSONDecoder().raw_decode(text.split('const '+name+'=',1)[1])[0]
schema=declaration('schema');schemas=schema['schema'];known=json.loads((root/'js/nethack/records.json').read_text())['records'];private={k:v for k,v in schemas.items()if v['ctype'].removeprefix('struct ').removeprefix('union ')not in known}
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+d for d in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]];clang=ref/'.cache/emsdk/upstream/bin/clang'
support=root/'nethack-c/wasm/tu-fragments/files-support.c'
layout_body=support.read_text().split('uint64_t teleport_files_layout(int index){switch(index){',1)[1].split('default:abort();}}',1)[0]
layout_expressions=re.findall(r'case (\d+):return\(uint64_t\)\((.*?)\);',layout_body)
assert [int(i)for i,_ in layout_expressions]==list(range(len(schema['layoutKeys'])))
probes=['const unsigned long probe_layout_'+i+'=('+expr+');'for i,expr in layout_expressions]
for i,(name,row)in enumerate(private.items()):
 t=row['ctype'];probes+=['const unsigned long probe_'+str(i)+'_size=sizeof('+t+');','const unsigned long probe_'+str(i)+'_align=_Alignof('+t+');']
 for j,f in enumerate(row['fields']):
  if f['bit']:raise ValueError('Review FILES private bitfield')
  probes.append('const unsigned long probe_'+str(i)+'_'+str(j)+'=offsetof('+t+','+f['name']+');')
scratch=root/'.cache/files-abi.c';scratch.write_text('#include '+json.dumps(str(source))+'\n#include <stddef.h>\n'+'\n'.join(probes)+'\n');ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(scratch)],text=True);value=lambda key:int(re.search(r'@probe_'+key+r' = .*?constant i64 (\d+)',ir)[1]);records={}
for i,(name,row)in enumerate(private.items()):records[row['ctype'].removeprefix('struct ')]={'size':value(str(i)+'_size'),'alignment':value(str(i)+'_align'),'fields':{f['name']:{'offset':value(str(i)+'_'+str(j)),'ctype':f['ctype']+' '+f['name']}for j,f in enumerate(row['fields'])}}
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();deps=subprocess.check_output([str(clang),*flags,'-M',str(scratch)],text=True);headers=sorted(set(Path(p).resolve()for p in shlex.split(deps.split(':',1)[1].replace('\\\n',''))))
inputs=[Path(__file__).resolve(),runtime,root/'js/ported/files.js',root/'nethack-c/wasm/compile-defines.json',support,root/'js/nethack/files.js']
(root/'js/nethack/files-abi.json').write_text(json.dumps({'schema':schema,'layout':[value('layout_'+str(i))for i in range(len(schema['layoutKeys']))],'records':records,'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in headers if p.is_relative_to(ref)}},indent=2)+'\n');print('Bound FILES descriptors/private records.')
