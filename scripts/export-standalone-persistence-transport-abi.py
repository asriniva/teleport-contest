#!/usr/bin/env python3
"""Bind shared timestamp/room/timer/light persistence transport inputs."""
import hashlib,json,os,shlex,subprocess
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree'
paths=[Path(__file__).resolve(),root/'nethack-c/wasm/compile-defines.json',root/'nethack-c/wasm/tu-support.c',root/'js/standalone/records.json',root/'js/wasm/tu-layouts.json']
for name in ['timeout','light','mkroom','restore','sfbase','sfstruct']:
 paths.extend([root/('js/ported/'+name+'.js'),root/('js/ported/'+name+'-runtime.js')])
for name in ['timeout','light','mkroom']:paths.extend([root/('nethack-c/wasm/tu-libraries/'+name+'.js'),root/('scripts/tu-'+name+'-layout.h')])
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
headers=set()
for name in ['timeout','light','mkroom','restore','sfbase','sfstruct']:
 source=tree/('src/'+name+'.c');deps=subprocess.check_output([str(ref/'.cache/emsdk/upstream/bin/clang'),*flags,'-M',str(source)],text=True)
 headers.update(Path(p).resolve()for p in shlex.split(deps.split(':',1)[1].replace('\\\n','')))
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
(root/'js/standalone/persistence-transport-abi.json').write_text(json.dumps({'sourceSha256':{str(p.relative_to(root)):sha(p)for p in paths},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(headers)if p.is_relative_to(ref)},'scope':'Source-bound transport provenance only; full checkpoint files, nonempty restore/relink/free and game-recording acceptance remain separate.'},indent=2)+'\n')
print('Bound original timestamp/room/timer/light serialization transport inputs.')
