#!/usr/bin/env python3
"""Bind unchanged SAVE schemas, shared roots, serializers and native header ABI."""
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
runtime = root / 'js/ported/save-runtime.js'
source = tree / 'src/save.c'
support = root / 'nethack-c/wasm/tu-fragments/save-support.c'
source_data = root / 'nethack-c/wasm/tu-fragments/save-source-data.h'
library = root / 'nethack-c/wasm/tu-libraries/save.js'
header = root / 'scripts/tu-save-layout.h'
decoder = json.JSONDecoder()
text = runtime.read_text()
declaration = lambda name: decoder.raw_decode(text.split('const ' + name + '=', 1)[1])[0]
schemas, globals_ = declaration('schemas'), declaration('globals')
known = json.loads((root / 'js/standalone/records.json').read_text())['records']
for name, row in schemas.items():
    key = row['ctype'].removeprefix('struct ').removeprefix('union ')
    if key not in known:
        raise ValueError('Measure new private SAVE record before use: ' + name)
body = support.read_text().split('void *teleport_save_global(int index){switch(index){', 1)[1].split('default:', 1)[0]
rows = [(int(i), name) for i, name in re.findall(r'case (\d+):return (?:\(void\*\))?&(\w+);', body)]
expected = list(enumerate([row['name'] for row in globals_] + ['save_zerotrap', 'save_zerofruit']))
if rows != expected:
    raise ValueError('SAVE source/native global map mismatch')
serializers = dict(re.findall(r'^\s*(Sf[io]_\w+):[^\n]*?=>_(\w+)\(', library.read_text(), re.M))
if not serializers or any(name.lower() != target for name, target in serializers.items()):
    raise ValueError('Review SAVE native serializer aliases')
data_text = source_data.read_text()
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
if sha(source) != re.search(r'#define SAVE_SOURCE_SHA256 "([0-9a-f]+)"', data_text)[1]:
    raise ValueError('SAVE source changed relative to original native source bindings')
integer = lambda key: int(re.search(r'#define ' + key + r' (\d+)', data_text)[1])
source_file = re.search(r'#define SAVE_SOURCE_FILE "([^"]+)"', data_text)[1]
flags = ['--target=wasm64-unknown-emscripten',
         '--sysroot=' + str(ref / '.cache/emsdk/upstream/emscripten/cache/sysroot'),
         '-include', str(ref / 'nethack-c/wasm/native-terminal.h'),
         '-I' + str(tree / 'include'), '-I' + str(ref / '.cache/ncurses-wasm64-build/include'),
         *['-D' + d for d in json.loads((root / 'nethack-c/wasm/compile-defines.json').read_text())]]
clang = ref / '.cache/emsdk/upstream/bin/clang'
probe_text = '\n'.join('#include ' + json.dumps(str(p)) for p in [source, support, header]) + '''
const unsigned long probe_save_zerotrap=sizeof(save_zerotrap);
const unsigned long probe_save_zerofruit=sizeof(save_zerofruit);
const unsigned long probe_save_sig_ign=(uintptr_t)SIG_IGN;
'''
with tempfile.TemporaryDirectory(prefix='standalone-save-abi-') as scratch:
    probe = Path(scratch) / 'probe.c'
    probe.write_text(probe_text)
    ir = subprocess.check_output([str(clang), *flags, '-S', '-emit-llvm', '-O0', '-o', '-', str(probe)], text=True)
    value = lambda key: int(re.search(r'@probe_save_' + key + r' = .*?constant i64 (-?\d+)', ir)[1])
    sizes = {'save_zerotrap': value('zerotrap'), 'save_zerofruit': value('zerofruit')}
    sig_ign = str(value('sig_ign') & ((1 << 64) - 1))
    deps = subprocess.check_output([str(clang), *flags, '-M', str(probe)], text=True)
    headers = sorted(set(Path(p).resolve() for p in shlex.split(deps.split(':', 1)[1].replace('\\\n', ''))))

inputs = [Path(__file__).resolve(), runtime, root / 'js/ported/save.js', support,
          source_data, library, header, root / 'nethack-c/wasm/compile-defines.json',
          root / 'js/standalone/records.json', root / 'js/standalone/public-functions.json']
data = {'schemas': schemas, 'globals': globals_, 'zeroStorage': sizes,
        'serializers': serializers, 'SIG_IGN': sig_ign, 'sourceFile': source_file,
        'snprintfLine': integer('SAVE_SNPRINTF_LINE'), 'assertLine': integer('SAVE_ASSERT_LINE'),
        'strlenSites': [{'function': name, 'line': integer('SAVE_STRLEN_LINE' + str(i))}
                        for i, name in enumerate(['save_gamelog', 'save_msghistory'])],
        'sourceSha256': {str(p.relative_to(root)): sha(p) for p in inputs},
        'referenceHeaderSha256': {str(p.relative_to(ref)): sha(p) for p in headers if p.is_relative_to(ref)}}
(root / 'js/standalone/save-lifecycle-abi.json').write_text(json.dumps(data, indent=2) + '\n')
print('Bound SAVE lifecycle: %d schemas, %d shared roots, two measured zero records and %d serializer aliases.'
      % (len(schemas), len(globals_), len(serializers)))
