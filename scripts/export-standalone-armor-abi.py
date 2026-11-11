#!/usr/bin/env python3
"""Measure existing DO_WEAR private ABI mirrors; bind source descriptors."""
import json,hashlib,os,re,shlex,subprocess
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';source=root/'js/ported/do_wear-runtime.js';text=source.read_text()
def declaration(name):return json.JSONDecoder().raw_decode(text.split('const '+name+'=',1)[1])[0]
schemas=declaration('schemas');globals=declaration('globals');callbacks=declaration('callbackNames');known=json.loads((root/'js/standalone/records.json').read_text())['records'];private={k:v for k,v in schemas.items()if v['ctype'].removeprefix('struct ').removeprefix('union ')not in known}
header=root/'scripts/tu-do_wear-layout.h';flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+d for d in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]];clang=ref/'.cache/emsdk/upstream/bin/clang'
probes=[]
for i,(name,row)in enumerate(private.items()):
 t=row['ctype'];probes+=['const unsigned long probe_'+str(i)+'_size=sizeof('+t+');','const unsigned long probe_'+str(i)+'_align=_Alignof('+t+');']
 for j,f in enumerate(row['fields']):
  if f['bit']:raise ValueError('Review private armor bitfield')
  probes.append('const unsigned long probe_'+str(i)+'_'+str(j)+'=offsetof('+t+','+f['name']+');')
scratch=root/'.cache/armor-abi.c';scratch.write_text('#include '+json.dumps(str(header))+'\n'+'\n'.join(probes)+'\n');ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(scratch)],text=True);value=lambda key:int(re.search(r'@probe_'+key+r' = .*?constant i64 (\d+)',ir)[1]);records={}
for i,(name,row)in enumerate(private.items()):records[row['ctype'].removeprefix('struct ')]={'size':value(str(i)+'_size'),'alignment':value(str(i)+'_align'),'fields':{f['name']:{'offset':value(str(i)+'_'+str(j)),'ctype':f['ctype']+' '+f['name']}for j,f in enumerate(row['fields'])}}
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();deps=subprocess.check_output([str(clang),*flags,'-M',str(scratch)],text=True);headers=sorted(set(Path(p).resolve()for p in shlex.split(deps.split(':',1)[1].replace('\\\n',''))));headers.append(tree/'src/do_wear.c')
inputs=[Path(__file__).resolve(),source,root/'js/ported/do_wear.js',header,root/'nethack-c/wasm/compile-defines.json']
ast=json.loads(subprocess.check_output([str(clang),*flags,'-Xclang','-ast-dump=json','-fsyntax-only',str(tree/'src/do_wear.c')],text=True));callbackTypes={}
def walk(node):
 if node.get('kind')=='FunctionDecl' and node.get('name')in callbacks:callbackTypes[node['name']]=node['type']['qualType']
 for child in node.get('inner',[]):walk(child)
walk(ast);assert set(callbackTypes)==set(callbacks),'Missing original DO_WEAR callback prototype'
bufferBytes=int(re.search(r'static char offdelaybuf\[(\d+)\]',(tree/'src/do_wear.c').read_text())[1]);support=root/'nethack-c/wasm/tu-do_wear-support.inc';assert int(re.search(r'teleport_do_wear_offdelaybuf\[(\d+)\]',support.read_text())[1])==bufferBytes
inputs.append(support)
data={'bufferBytes':bufferBytes,'callbacks':callbacks,'callbackTypes':callbackTypes,'schemas':schemas,'globals':globals,'records':records,'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in headers if p.is_relative_to(ref)}}
(root/'js/standalone/armor-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound DO_WEAR descriptors and measured private records.')
