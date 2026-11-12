#!/usr/bin/env python3
"""Bind unchanged HACK descriptors and measure original private data/callbacks."""
import json,hashlib,os,re,shlex,subprocess
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';runtime=root/'js/nethack/bindings/hack.js';text=runtime.read_text();source=tree/'src/hack.c'
def declaration(name):return json.JSONDecoder().raw_decode(text.split('const '+name+'=',1)[1])[0]
schemas=declaration('schemas');globals=declaration('globals');functions=declaration('functions');known=json.loads((root/'js/nethack/records.json').read_text())['records'];private={k:v for k,v in schemas.items()if v['ctype'].removeprefix('struct ').removeprefix('union ')not in known}
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+d for d in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]];clang=ref/'.cache/emsdk/upstream/bin/clang'
probes=[]
for i,(name,row)in enumerate(private.items()):
 t=row['ctype'];probes+=['const unsigned long probe_'+str(i)+'_size=sizeof('+t+');','const unsigned long probe_'+str(i)+'_align=_Alignof('+t+');']
 for j,f in enumerate(row['fields']):
  if f['bit']:raise ValueError('Review HACK private bitfield')
  probes.append('const unsigned long probe_'+str(i)+'_'+str(j)+'=offsetof('+t+','+f['name']+');')
scratch=root/'.cache/hack-abi.c';scratch.write_text('#include '+json.dumps(str(source))+'\n#include <stddef.h>\n'+'\n'.join(probes)+'\n');ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(scratch)],text=True);value=lambda key:int(re.search(r'@probe_'+key+r' = .*?constant i64 (\d+)',ir)[1]);records={}
for i,(name,row)in enumerate(private.items()):records[row['ctype'].removeprefix('struct ')]={'size':value(str(i)+'_size'),'alignment':value(str(i)+'_align'),'fields':{f['name']:{'offset':value(str(i)+'_'+str(j)),'ctype':f['ctype']+' '+f['name']}for j,f in enumerate(row['fields'])}}
ast=json.loads(subprocess.check_output([str(clang),*flags,'-fsyntax-only','-Xclang','-ast-dump=json',str(source)]));callbacks={n['name']:{'result':n['type']['qualType'].split('(',1)[0].strip(),'parameters':[p['type']['qualType']for p in n.get('inner',[])if p['kind']=='ParmVarDecl']}for n in ast['inner']if n.get('kind')=='FunctionDecl'and n.get('name')in functions and any(c['kind']=='CompoundStmt'for c in n.get('inner',[]))}
if set(functions)!=callbacks.keys():raise ValueError('Review effective HACK functions '+str(set(functions)-callbacks.keys()))
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();deps=subprocess.check_output([str(clang),*flags,'-M',str(scratch)],text=True);headers=sorted(set(Path(p).resolve()for p in shlex.split(deps.split(':',1)[1].replace('\\\n',''))))
inputs=[Path(__file__).resolve(),runtime,root/'js/ported/hack.js',root/'nethack-c/wasm/compile-defines.json',root/'nethack-c/wasm/tu-fragments/hack-support.c',root/'js/nethack/movement.js',root/'nethack-c/wasm/tu-libraries/hack.js']
rngCallers=[(int(line),caller)for line,caller in re.findall(r'C\.rngCaller\((\d+),\s*"([^"]+)"\)',(root/'js/ported/hack.js').read_text())]
assert rngCallers,'Missing original HACK RNG call sites'
data={'rngCallers':rngCallers,'schemas':schemas,'globals':globals,'functions':functions,'callbacks':callbacks,'records':records,'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in headers if p.is_relative_to(ref)}}
(root/'js/nethack/hack-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Exported original HACK descriptors, private record and callback prototypes.')
