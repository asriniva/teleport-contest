#!/usr/bin/env python3
"""Bind existing OPTIONS schema and measure its source-private records."""
import hashlib,json,os,re,subprocess,shlex
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';source=tree/'src/options.c';clang=ref/'.cache/emsdk/upstream/bin/clang'
schema_path=root/'nethack-c/wasm/tu-fragments/options-schema.json';schema=json.loads(schema_path.read_text());known=json.loads((root/'js/standalone/records.json').read_text())['records'];missing=set(schema['schema'])-known.keys()
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+d for d in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
header=root/'nethack-c/wasm/tu-options-abi.h';scratch=root/'.cache/options-abi.c'
probes=[]
for i,name in enumerate(sorted(missing)):
 t=schema['schema'][name]['ctype'];probes.extend(['const unsigned long probe_'+str(i)+'_size=sizeof('+t+');','const unsigned long probe_'+str(i)+'_align=_Alignof('+t+');'])
 for j,f in enumerate(schema['schema'][name]['fields']):
  if f['bit']:raise ValueError('Review private OPTIONS bitfield')
  probes.append('const unsigned long probe_'+str(i)+'_'+str(j)+'=offsetof('+t+','+f['name']+');')
enums=sorted(k.removeprefix('enumSigned:')for k in schema['layoutKeys']if k.startswith('enumSigned:'));probes.extend('const unsigned long enum_'+str(i)+'_size=sizeof(enum '+name+');\nconst unsigned long enum_'+str(i)+'_signed=((enum '+name+')-1 < 0);'for i,name in enumerate(enums))
scratch.write_text('#include '+json.dumps(str(source))+'\n#define TELEPORT_OPTIONS_ORIGINAL_INCLUDED\n#include '+json.dumps(str(header))+'\n#include <stddef.h>\n'+'\n'.join(probes)+'\n')
ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(scratch)],text=True)
value=lambda key:int(re.search(r'@probe_'+key+r' = .*?constant i64 (\d+)',ir)[1]);records={}
for i,name in enumerate(sorted(missing)):
 row=schema['schema'][name];record={'size':value(str(i)+'_size'),'alignment':value(str(i)+'_align'),'fields':{f['name']:{'offset':value(str(i)+'_'+str(j)),'ctype':f['canonical']+' '+f['name']}for j,f in enumerate(row['fields'])}}
 records[row['ctype'].removeprefix('struct ')]=record
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();deps=subprocess.check_output([str(clang),*flags,'-M',str(scratch)],text=True);headers=sorted(set(Path(p).resolve()for p in shlex.split(deps.split(':',1)[1].replace('\\\n',''))))
inputs=[Path(__file__).resolve(),schema_path,root/'js/ported/options.js',root/'js/ported/options-runtime.js',root/'nethack-c/wasm/compile-defines.json',header]
enumData={'enum '+name:{'size':int(re.search(r'@enum_'+str(i)+r'_size = .*?constant i64 (\d+)',ir)[1]),'signed':bool(int(re.search(r'@enum_'+str(i)+r'_signed = .*?constant i64 (\d+)',ir)[1]))}for i,name in enumerate(enums)}
data={'enums':enumData,'schema':schema,'records':records,'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in headers if p.is_relative_to(ref)}}
(root/'js/standalone/options-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Exported OPTIONS schema and '+str(len(records))+' private record layouts.')
