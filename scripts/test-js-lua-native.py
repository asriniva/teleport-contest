"""Build only the private Lua5.4.8 comparison oracle from the pinned archive."""
import hashlib
from pathlib import Path
import subprocess
import sys
import tarfile

root = Path(__file__).resolve().parents[1]
scratch = root / '.cache/js-dependency-lua'
scratch.mkdir(exist_ok=True, parents=True)
archive = root / '.cache/lua-5.4.8.tar.gz'
assert hashlib.sha256(archive.read_bytes()).hexdigest() == '4f18ddae154e793e46eeab727c59ef1c0c0c2b744e7b94219710d76f530629ae'
with tarfile.open(archive) as packed:
    packed.extractall(scratch, filter='data')
source = scratch / 'lua-5.4.8/src'
compiler = root / '.cache/wasm64-build/host-cc'
inputs = sorted(str(path) for path in source.glob('*.c') if path.name not in ('lua.c', 'luac.c'))
stem = sys.argv[1] if len(sys.argv) > 1 else 'oracle'
assert stem in ('oracle', 'oracle-api', 'oracle-gc', 'oracle-memory')
subprocess.run([str(compiler) if compiler.exists() else 'cc', '-O2', '-I' + str(source), str(scratch / (stem + '.c')), *inputs, '-lm', '-o', str(scratch / stem)], check=True)
print('Built private native Lua5.4.8 oracle from checksum-verified archive.')
