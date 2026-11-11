"""Compile original-C and imported-JS NHLSEL fixtures in the real repository.

The original C is unmodified, including its documented unary alias UAF.
This builds comparison artifacts; it neither runs tests nor copies sources.
"""
from pathlib import Path
import argparse, hashlib, json, os, subprocess, sys
from golden_emscripten_profile import c_flags as golden_c_flags

ROOT = Path(__file__).resolve().parents[1]
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--out', type=Path, default=ROOT / '.cache/tu-probes')
args = parser.parse_args()
out = args.out.resolve()
out.mkdir(parents=True, exist_ok=True)
sdk = Path(os.environ.get('EMSDK', ROOT / '.cache/emsdk')).resolve()
tree = ROOT / '.cache/wasm64-build/tree'
subprocess.run([sys.executable, '-B', str(ROOT / 'scripts/check-golden-emscripten-profile.py')], check=True)
subprocess.run([sys.executable, '-B', str(ROOT / 'nethack-c/wasm/tu-fragments/nhlsel-metadata.py')], check=True)
defines = golden_c_flags(ROOT)
probe = ROOT / 'scripts/tu-nhlsel-probe.c'
support = ROOT / 'nethack-c/wasm/tu-fragments/nhlsel-support.inc'
library = ROOT / 'nethack-c/wasm/tu-libraries/nhlsel.js'
dependencies = [tree / 'src' / name for name in ['selvar.c', 'rect.c', 'sp_lev.c', 'nhlua.c', 'hacklib.c', 'alloc.c', 'strutil.c']]
lua = sorted(path for path in (tree / 'lib/lua-5.4.8/src').glob('*.c') if path.name not in ['lua.c', 'luac.c', 'onelua.c'])
assert lua, 'Prepared Lua sources are required'
archive = ROOT / '.cache/wasm64-build/liblua-wasm64.a'
assert archive.is_file(), 'Build the existing C Lua reference archive first'
inputs = [archive, ROOT / 'nethack-c/wasm/golden-emscripten-profile.json', ROOT / 'scripts/golden_emscripten_profile.py', ROOT / 'scripts/check-golden-emscripten-profile.py', ROOT / 'nethack-c/wasm/native-terminal.h', ROOT / 'nethack-c/wasm/compile-defines.json', probe, support, library, tree / 'src/nhlsel.c', ROOT / 'nethack-c/upstream/src/nhlsel.c', ROOT / 'scripts/tu-nhlsel-layout.h', ROOT / 'js/ported/nhlsel.js', ROOT / 'js/ported/nhlsel-runtime.js', Path(__file__), *dependencies, *lua, *sorted((tree / 'include').glob('*.h'))]
sha = lambda path: hashlib.sha256(path.read_bytes()).hexdigest()
before = {str(path.relative_to(ROOT)): sha(path) for path in inputs}
exports = ['_probe_' + name for name in ['reset', 'input', 'clear_trace', 'trace', 'snapshot', 'run', 'option', 'origin', 'room', 'cell', 'alias', 'helper', 'state', 'stack', 'layout_count', 'layout_name', 'layout_value']]
base = [str(sdk / 'upstream/emscripten/emcc'), '-O2', '-sMEMORY64=1', '-sMODULARIZE=1', '-sENVIRONMENT=node,web', '-sALLOW_MEMORY_GROWTH=1', '--no-entry', '-sEXPORTED_RUNTIME_METHODS=HEAPU8', '-Wl,--wrap=free', '-Wl,--wrap=dupstr', '-Wl,--wrap=get_location_coord', '-Wl,--wrap=nhl_pcall_handle', '-I' + str(tree / 'include'), *defines, '-sEXPORTED_FUNCTIONS=' + json.dumps(exports), str(probe), *map(str, dependencies), str(archive), '--js-library', str(ROOT / 'nethack-c/wasm/native-libc-library.js')]
commands = []
for mode in ['reference', 'hybrid']:
    command = base.copy()
    command += ['-DTELEPORT_REFERENCE_TU'] if mode == 'reference' else ['-x', 'c', str(support), '--js-library', str(library)]
    command += ['-o', str(out / ('nhlsel-' + mode + '.mjs'))]
    print('Building NHLSEL ' + mode, flush=True)
    result = subprocess.run(command, cwd=ROOT)
    commands.append({'mode': mode, 'command': command, 'exit': result.returncode})
    (out / 'nhlsel-build-commands.json').write_text(json.dumps(commands, indent=2) + '\n')
    result.check_returncode()
assert before == {str(path.relative_to(ROOT)): sha(path) for path in inputs}, 'Build inputs changed during compilation'
artifacts = {path.name: sha(path) for path in out.glob('nhlsel-*') if path.suffix in ['.mjs', '.wasm']}
(out / 'nhlsel-build.json').write_text(json.dumps({'sourceProfile': 'golden44 Emscripten compiler profile; original NHLSEL C; unary alias UAF unchanged', 'inputHashes': before, 'artifactHashes': artifacts, 'commands': commands}, indent=2) + '\n')
print('Built NHLSEL original-C/imported-JS pair; no tests executed.', flush=True)
