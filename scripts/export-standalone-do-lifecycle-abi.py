#!/usr/bin/env python3
"""Bind original DO descriptors, native maps and configured source ABI inputs."""
import hashlib
import json
import os
import re
import shlex
import subprocess
import tempfile
from pathlib import Path

root = Path(__file__).resolve().parents[1]
ref = Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve()
tree = ref / '.cache/wasm64-build/tree'
runtime = root / 'js/nethack/bindings/do.js'
source = tree / 'src/do.c'
support = root / 'nethack-c/wasm/tu-do-support.inc'
varargs = root / 'nethack-c/wasm/tu-do-varargs.inc'
library = root / 'nethack-c/wasm/tu-libraries/do.js'
header = root / 'scripts/tu-do-layout.h'
text = runtime.read_text()
decoder = json.JSONDecoder()
declaration = lambda name: decoder.raw_decode(text.split('const ' + name + '=', 1)[1])[0]
schemas, globals_ = declaration('schemas'), declaration('globals')
known = json.loads((root / 'js/nethack/records.json').read_text())['records']
for name, row in schemas.items():
    key = row['ctype'].removeprefix('struct ').removeprefix('union ')
    if key not in known:
        raise ValueError('Measure new private DO record before use: ' + name)

global_body = support.read_text().split('void *teleport_do_global(int index){switch(index){', 1)[1].split('default:', 1)[0]
global_rows = [(int(i), name) for i, name in re.findall(r'case (\d+):return \(void\*\)&(\w+);', global_body)]
if global_rows != list(enumerate(row['name'] for row in globals_)):
    raise ValueError('DO source descriptor/native global map mismatch')

callback_body = varargs.read_text().split('uintptr_t teleport_do_callback_pointer(int i){switch(i){', 1)[1].split('default:', 1)[0]
callback_rows = [(int(i), name) for i, name in re.findall(r'case (\d+):return\(uintptr_t\)(\w+);', callback_body)]
if [i for i, _ in callback_rows] != list(range(9)):
    raise ValueError('Review changed DO callback map')
aliases = {'teleport_do_drop_callback': 'drop', 'teleport_do_wipe_callback': 'wipeoff'}
public = json.loads((root / 'js/nethack/public-functions.json').read_text())['functions']
private = {'drop': 'int (struct obj *)', 'wipeoff': 'int (void)'}
callbacks = [{'name': aliases.get(name, name), 'native': name,
              'prototype': private.get(aliases.get(name, name), public.get(name))}
             for _, name in callback_rows]
if any(not row['prototype'] for row in callbacks):
    raise ValueError('Missing original DO callback prototype')
sites = decoder.raw_decode(library.read_text().split('var sites=', 1)[1])[0]
if [row['id'] for row in sites] != list(range(len(sites))):
    raise ValueError('Review changed DO variadic site indexing')

flags = ['--target=wasm64-unknown-emscripten',
         '--sysroot=' + str(ref / '.cache/emsdk/upstream/emscripten/cache/sysroot'),
         '-include', str(ref / 'nethack-c/wasm/native-terminal.h'),
         '-I' + str(tree / 'include'), '-I' + str(ref / '.cache/ncurses-wasm64-build/include'),
         *['-D' + d for d in json.loads((root / 'nethack-c/wasm/compile-defines.json').read_text())]]
clang = ref / '.cache/emsdk/upstream/bin/clang'
body = '\n'.join('#include ' + json.dumps(str(p)) for p in [source, support, header]) + '''
_Static_assert(__builtin_types_compatible_p(__typeof__(&drop),int(*)(struct obj*)),"DO drop callback prototype");
_Static_assert(__builtin_types_compatible_p(__typeof__(&wipeoff),int(*)(void)),"DO wipeoff callback prototype");
const unsigned long probe_do_buffer_size=sizeof(teleport_do_wipebuf);
'''
with tempfile.TemporaryDirectory(prefix='standalone-do-abi-') as scratch:
    probe = Path(scratch) / 'probe.c'
    probe.write_text(body)
    ir = subprocess.check_output([str(clang), *flags, '-S', '-emit-llvm', '-O0', '-o', '-', str(probe)], text=True)
    buffer_size = int(re.search(r'@probe_do_buffer_size = .*?constant i64 (\d+)', ir)[1])
    deps = subprocess.check_output([str(clang), *flags, '-M', str(probe)], text=True)
    headers = sorted(set(Path(p).resolve() for p in shlex.split(deps.split(':', 1)[1].replace('\\\n', ''))))

inputs = [Path(__file__).resolve(), runtime, root / 'js/ported/do.js', support, varargs,
          library, header, root / 'nethack-c/wasm/compile-defines.json',
          root / 'js/nethack/records.json', root / 'js/nethack/public-functions.json']
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
data = {'schemas': schemas, 'globals': globals_, 'callbackMap': callbacks,
        'bufferBytes': buffer_size, 'variadicSites': sites,
        'sourceSha256': {str(p.relative_to(root)): sha(p) for p in inputs},
        'referenceHeaderSha256': {str(p.relative_to(ref)): sha(p) for p in headers if p.is_relative_to(ref)}}
(root / 'js/nethack/do-lifecycle-abi.json').write_text(json.dumps(data, indent=2) + '\n')
print('Bound DO lifecycle: %d record schemas, %d shared globals, %d callbacks, %d variadic sites and %d-byte buffer.'
      % (len(schemas), len(globals_), len(callbacks), len(sites), buffer_size))
