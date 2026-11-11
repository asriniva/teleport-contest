#!/usr/bin/env python3
"""Compiler-declared C function prototypes for the standalone linker."""
import hashlib,json,os,shlex,subprocess
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';out=root/'.cache/standalone-public-functions';out.mkdir(exist_ok=True)
p=out/'headers.c';p.write_text('#include "hack.h"\n#include "sp_lev.h"\n#include "region.h"\n#include "wintty.h"\n')
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+s for s in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
clang=ref/'.cache/emsdk/upstream/bin/clang';ast=json.loads(subprocess.check_output([str(clang),*flags,'-fsyntax-only','-Xclang','-ast-dump=json',str(p)]))
functions={n['name']:n['type']['qualType']for n in ast['inner']if n.get('kind')=='FunctionDecl'and n.get('storageClass')!='static'and not any(c.get('kind')=='CompoundStmt'for c in n.get('inner',[]))}
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
deps=subprocess.check_output([str(clang),*flags,'-M',str(p)],text=True)
headers=[Path(n).resolve()for n in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(n).resolve()!=p.resolve()]
result={'functions':functions,'sourceSha256':{str(Path(__file__).resolve().relative_to(root)):sha(Path(__file__).resolve()),'nethack-c/wasm/compile-defines.json':sha(root/'nethack-c/wasm/compile-defines.json')},'referenceHeaderSha256':{str(header.relative_to(ref)):sha(header)for header in sorted(set(headers))}}
(root/'js/standalone/public-functions.json').write_text(json.dumps(result,indent=2)+'\n');print('Exported '+str(len(functions))+' configured public C prototypes.')
