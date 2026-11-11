#!/usr/bin/env python3
"""Measure configured MDLIB/DATE metadata without generating production C code."""
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
md_source, date_source = tree / 'src/mdlib.c', tree / 'src/date.c'
header = root / 'scripts/tu-mdlib-layout.h'
build = root / 'nethack-c/wasm/build.py'
epochs = set(re.findall(r"os\.environ\['SOURCE_DATE_EPOCH'\] = '(\d+)'", build.read_text()))
if len(epochs) != 1:
    raise ValueError('Review configured build epoch before binding date macros')
epoch = next(iter(epochs))
compiler_env = {**os.environ, 'SOURCE_DATE_EPOCH': epoch, 'TZ': 'UTC'}
flags = ['--target=wasm64-unknown-emscripten',
         '--sysroot=' + str(ref / '.cache/emsdk/upstream/emscripten/cache/sysroot'),
         '-include', str(ref / 'nethack-c/wasm/native-terminal.h'),
         '-I' + str(tree / 'include'), '-I' + str(ref / '.cache/ncurses-wasm64-build/include'),
         *['-D' + d for d in json.loads((root / 'nethack-c/wasm/compile-defines.json').read_text())]]
clang = ref / '.cache/emsdk/upstream/bin/clang'
layouts = json.loads((root / 'js/wasm/tu-layouts.json').read_text())
date_layout = layouts['date']
records = json.loads((root / 'js/standalone/records.json').read_text())['records']
tm = records['tm']
probe_text = '\n'.join('#include ' + json.dumps(str(p)) for p in [header, md_source, date_source]) + '''
const char probe_BUILD_DATE_TIME[]=__DATE__ " " __TIME__;
'''
for name in ['NETHACK_GIT_SHA', 'NETHACK_GIT_BRANCH', 'NETHACK_GIT_PREFIX']:
    probe_text += '#ifdef ' + name + '\nconst char *probe_' + name + '=' + name + ';\n#else\nconst char *probe_' + name + '=0;\n#endif\n'
probe_text += 'const unsigned long probe_date_size=sizeof(struct nomakedefs_s);\nconst unsigned long probe_tm_size=sizeof(struct tm);\n'
for name in date_layout['fields']:
    probe_text += 'const unsigned long probe_date_' + name + '=offsetof(struct nomakedefs_s,' + name + ');\n'
    probe_text += 'const unsigned long probe_date_width_' + name + '=sizeof(((struct nomakedefs_s*)0)->' + name + ');\n'
for name in date_layout['versionFields']:
    probe_text += 'const unsigned long probe_version_' + name + '=offsetof(struct version_info,' + name + ');\n'
    probe_text += 'const unsigned long probe_version_width_' + name + '=sizeof(((struct version_info*)0)->' + name + ');\n'
for name in tm['fields']:
    probe_text += 'const unsigned long probe_tm_' + name + '=offsetof(struct tm,' + name + ');\n'
    probe_text += 'const unsigned long probe_tm_width_' + name + '=sizeof(((struct tm*)0)->' + name + ');\n'
probe_text += 'const unsigned long probe_optbuf=sizeof(optbuf);\nconst unsigned long probe_version=sizeof(version);\nconst unsigned long probe_compat=sizeof(save_bones_compat_buf);\n'

def cstring(expression):
    expression = expression.strip()
    if expression == '0':
        return None
    pieces = re.findall(r'"(?:\\.|[^"\\])*"', expression)
    if not pieces or re.sub(r'"(?:\\.|[^"\\])*"', '', expression).strip():
        raise ValueError('Unrecognized configured C string ' + expression)
    return ''.join(json.loads(piece) for piece in pieces)

with tempfile.TemporaryDirectory(prefix='standalone-runtime-info-abi-') as scratch:
    probe = Path(scratch) / 'probe.c'
    probe.write_text(probe_text)
    expanded = subprocess.check_output([str(clang), *flags, '-E', '-P', str(probe)], text=True, env=compiler_env)
    body = re.search(r'mdlib_layout\[\]\s*=\s*\{(.*?)\n\};', expanded, re.S)[1]
    rows = re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}', body, re.S)
    if not rows or len({name for name, _ in rows}) != len(rows):
        raise ValueError('Review configured MDLIB layout initializer')
    probe.write_text(probe_text + '\n'.join('const unsigned long probe_layout_' + str(i) + '=(' + expr + ');' for i, (_, expr) in enumerate(rows)))
    ir = subprocess.check_output([str(clang), *flags, '-S', '-emit-llvm', '-O0', '-o', '-', str(probe)], text=True, env=compiler_env)
    value = lambda key: int(re.search(r'@probe_' + key + r' = .*?constant i64 (-?\d+)', ir)[1])
    mdlib_layout = {name: value('layout_' + str(i)) for i, (name, _) in enumerate(rows)}
    strings_body = re.search(r'mdlib_strings\[\]\s*=\s*\{(.*?)\n\};', expanded, re.S)[1]
    mdlib_layout['strings'] = {name: cstring(expr) for name, expr in re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}', strings_body, re.S)}
    for key, expected in mdlib_layout.items():
        if layouts['mdlib'].get(key) != expected:
            raise ValueError('Configured MDLIB layout changed: ' + key)
    date_strings = {'BUILD_DATE_TIME': cstring(re.search(r'const char probe_BUILD_DATE_TIME\[\]\s*=\s*(.*?);', expanded)[1])}
    for name in ['NETHACK_GIT_SHA', 'NETHACK_GIT_BRANCH', 'NETHACK_GIT_PREFIX']:
        date_strings[name] = cstring(re.search(r'const char \*probe_' + name + r'\s*=\s*(.*?);', expanded)[1])
    if date_strings != date_layout['strings']:
        raise ValueError('Configured DATE build/git strings changed from frozen layout')
    if value('date_size') != date_layout['size'] or value('tm_size') != tm['size']:
        raise ValueError('Configured DATE/tm extent changed')
    for name, field in date_layout['fields'].items():
        if value('date_' + name) != field['offset'] or value('date_width_' + name) != field['size']:
            raise ValueError('Configured DATE field moved/resized: ' + name)
    for name, field in date_layout['versionFields'].items():
        if value('version_' + name) != field['offset'] or value('version_width_' + name) != field['size']:
            raise ValueError('Configured version field moved/resized: ' + name)
    for name, field in tm['fields'].items():
        expected_width = 8 if '*' in field['ctype'] or field['ctype'].startswith('long ') else 4 if field['ctype'].startswith('int ') else None
        if value('tm_' + name) != field['offset'] or value('tm_width_' + name) != expected_width:
            raise ValueError('Configured tm field moved/resized: ' + name)
    storage = [value('optbuf'), value('version'), value('compat')]
    ast = json.loads(subprocess.check_output([str(clang), *flags, '-Xclang', '-ast-dump=json', '-fsyntax-only', str(probe)], text=True, env=compiler_env))
    exported = set(re.findall(r'^export function (\w+)\(', (root / 'js/ported/mdlib.js').read_text(), re.M))
    function_types = {}
    def visit(node):
        if node.get('kind') == 'FunctionDecl' and node.get('name') in exported and node.get('storageClass') != 'static':
            function_types[node['name']] = node['type']['qualType']
        for child in node.get('inner', []):
            visit(child)
    visit(ast)
    deps = subprocess.check_output([str(clang), *flags, '-M', str(probe)], text=True, env=compiler_env)
    headers = sorted(set(Path(p).resolve() for p in shlex.split(deps.split(':', 1)[1].replace('\\\n', ''))))

def closing_line(source, needle):
    lines = source.read_text().splitlines()
    starts = [i for i, line in enumerate(lines) if needle in line]
    if len(starts) != 1:
        raise ValueError('Review original format call site ' + needle)
    return next(i + 1 for i in range(starts[0], len(lines)) if ');' in lines[i])

inputs = [Path(__file__).resolve(), header, build, root / 'nethack-c/wasm/compile-defines.json',
          root / 'js/wasm/tu-layouts.json', root / 'js/standalone/records.json',
          root / 'js/ported/mdlib.js', root / 'js/ported/mdlib-runtime.js',
          root / 'js/ported/date.js', root / 'js/ported/date-runtime.js', root / 'js/ported/allmain.js',
          root / 'nethack-c/wasm/tu-support.c', root / 'nethack-c/wasm/tu-libraries/mdlib.js',
          root / 'nethack-c/wasm/tu-libraries/date.js']
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
headers.append(tree / 'src/allmain.c')
data = {'mdlib': mdlib_layout, 'date': date_layout, 'tm': tm,
        'storageBytes': storage, 'mdlibFunctions': function_types, 'sourceDateEpoch': epoch,
        'formatLines': {'date': closing_line(date_source, 'Snprintf(tmpbuf1, sizeof tmpbuf1,'),
                        'version': closing_line(md_source, 'Snprintf(outbuf, bufsz, "%s NetHack'),
                        'banner': closing_line(md_source, 'Snprintf(outbuf, bufsz, "         Version')},
        'sourceSha256': {str(p.relative_to(root)): sha(p) for p in inputs},
        'referenceHeaderSha256': {str(p.relative_to(ref)): sha(p) for p in headers if p.is_relative_to(ref)}}
(root / 'js/standalone/runtime-info-abi.json').write_text(json.dumps(data, indent=2) + '\n')
print('Bound MDLIB/DATE configured layouts, source function visibility, build macros/epoch and shared tm transport.')
