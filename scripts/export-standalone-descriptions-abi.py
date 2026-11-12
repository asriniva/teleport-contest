#!/usr/bin/env python3
"""Measure original INSIGHT alignment constants and bind unchanged helper inputs."""
import hashlib,json,os,re,shlex,subprocess
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree'
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
names=['A_CHAOTIC','A_NEUTRAL','A_LAWFUL','A_NONE'];scratch=root/'.cache/descriptions-abi.c';scratch.write_text('#include '+json.dumps(str(tree/'src/insight.c'))+'\n'+'\n'.join('const long probe_'+name+'='+name+';'for name in names)+'\n')
clang=ref/'.cache/emsdk/upstream/bin/clang';ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(scratch)],text=True)
constants={name:int(re.search(r'@probe_'+name+r' = .*?constant i64 (-?\d+)',ir)[1])for name in names}
paths=[Path(__file__).resolve(),root/'js/ported/insight.js',root/'js/nethack/bindings/insight.js',root/'nethack-c/wasm/tu-libraries/insight.js',root/'nethack-c/wasm/compile-defines.json',root/'js/wasm/tu-layouts.json'];sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
deps=subprocess.check_output([str(clang),*flags,'-M',str(scratch)],text=True);headers=sorted(set(Path(p).resolve()for p in shlex.split(deps.split(':',1)[1].replace('\\\n',''))))
(root/'js/standalone/descriptions-abi.json').write_text(json.dumps({'constants':constants,'sourceSha256':{str(p.relative_to(root)):sha(p)for p in paths},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in headers if p.is_relative_to(ref)}},indent=2)+'\n')
print('Bound original alignment-description scalar helper.')
