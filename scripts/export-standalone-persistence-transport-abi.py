#!/usr/bin/env python3
"""Bind original shared level persistence transports and configured C inputs."""
import hashlib,json,os,re,shlex,subprocess
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree'
paths=[Path(__file__).resolve(),root/'nethack-c/wasm/compile-defines.json',root/'nethack-c/wasm/tu-support.c',root/'js/standalone/records.json',root/'js/wasm/tu-layouts.json',root/'js/standalone/level-persistence.js',root/'js/standalone/version-info.js',root/'js/standalone/libc.js',root/'js/standalone/random-text.js']
for name in ['timeout','light','mkroom','restore','sfbase','sfstruct','engrave','region','dungeon','track','version','rumors']:
 paths.append(root/('js/ported/'+name+'.js'))
 runtime=root/('js/ported/'+name+'-runtime.js')
 if runtime.exists():paths.append(runtime)
for name in ['timeout','light','mkroom','engrave','region','dungeon','track','version','rumors']:
 library=root/('nethack-c/wasm/tu-libraries/'+name+'.js')
 if library.exists():paths.append(library)
 layout=root/('scripts/tu-'+name+'-layout.h')
 if layout.exists():paths.append(layout)
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
difftime=ref/'.cache/emsdk/upstream/emscripten/system/lib/libc/musl/src/time/difftime.c'
if not re.search(r'return\s+t1\s*-\s*t0\s*;',difftime.read_text()):raise ValueError('Review changed pinned musl difftime body')
headers={difftime}
for name in ['timeout','light','mkroom','restore','sfbase','sfstruct','engrave','region','dungeon','track','version','rumors']:
 source=tree/('src/'+name+'.c');deps=subprocess.check_output([str(ref/'.cache/emsdk/upstream/bin/clang'),*flags,'-M',str(source)],text=True)
 headers.update(Path(p).resolve()for p in shlex.split(deps.split(':',1)[1].replace('\\\n','')))
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
(root/'js/standalone/persistence-transport-abi.json').write_text(json.dumps({'sourceSha256':{str(p.relative_to(root)):sha(p)for p in paths},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(headers)if p.is_relative_to(ref)},'scope':'Source-bound transport provenance; connected nonempty level serializer subset is tested separately. Full checkpoint graph, ghost mapping/relinking and full-game recordings remain unaccepted.'},indent=2)+'\n')
print('Bound original timestamp/room/timer/light serialization transport inputs.')
