#!/usr/bin/env python3
"""Bind original END killer-list ABI and serializer/debug input contracts."""
import hashlib,json,os,shlex,subprocess
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
paths=[Path(__file__).resolve(),root/'js/standalone/killer-state.js',root/'js/ported/end.js',root/'js/nethack/bindings/end.js',root/'nethack-c/wasm/tu-libraries/end.js',root/'nethack-c/wasm/tu-fragments/end-support.inc',root/'scripts/tu-end-layout.h',root/'js/wasm/tu-layouts.json',root/'js/standalone/records.json',root/'nethack-c/wasm/compile-defines.json']
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+d for d in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
deps=subprocess.check_output([str(ref/'.cache/emsdk/upstream/bin/clang'),*flags,'-M',str(tree/'src/end.c')],text=True);headers=sorted(set(Path(p).resolve()for p in shlex.split(deps.split(':',1)[1].replace('\\\n',''))))
(root/'js/standalone/killer-state-abi.json').write_text(json.dumps({'sourceSha256':{str(p.relative_to(root)):sha(p)for p in paths},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in headers if p.is_relative_to(ref)}},indent=2)+'\n');print('Bound original END killer list, native record and source profile inputs.')
