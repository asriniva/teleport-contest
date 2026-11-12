"""Reject deliberate wrong MKLEV JS against unchanged actual original C/Wasm."""
from pathlib import Path
from test_module_imports import rebase_test_module
import hashlib,subprocess,os,json
r=Path(__file__).resolve().parents[1];w=r/'.cache/mklev-first-pass';bad=w/'wrong-code';bad.mkdir(exist_ok=True)
paths=[r/'.cache/wasm64-build/tree/src/mklev.c',w/'mklev-reference.wasm'];before={str(p):hashlib.sha256(p.read_bytes()).hexdigest()for p in paths}
core=(r/'js/ported/mklev.js').read_text();needle='if(Number(C.i32(C.field(x,"mkroom","lx").value)<C.i32(C.field(y,"mkroom","lx").value))) return C.i32((-1));';assert core.count(needle)==1
core=core.replace(needle,needle.replace('C.i32((-1))','C.i32(1)')+' /* deliberate wrong-code witness */')
(bad/'mklev.js').write_text(rebase_test_module(core,r/'js/ported/mklev.js'))
runtime=(r/'js/nethack/bindings/mklev.js').read_text();(bad/'mklev-runtime.js').write_text(rebase_test_module(runtime,r/'js/nethack/bindings/mklev.js',{(r/'js/ported/mklev.js').resolve():(bad/'mklev.js').as_uri()}))
p=subprocess.run([str(r/'.cache/emsdk/node/24.19.0_64bit/bin/node'),'scripts/test-tu-mklev.mjs'],env={**os.environ,'MKLEV_RUNTIME':(bad/'mklev-runtime.js').as_uri()},text=True,capture_output=True);(w/'wrong-code-negative.log').write_text(p.stdout+p.stderr)
assert p.returncode!=0 and 'mkroom_cmp result'in p.stderr,(p.returncode,p.stdout,p.stderr[:2000])
assert before=={str(p):hashlib.sha256(p.read_bytes()).hexdigest()for p in paths}
print('PASS: deliberate comparator wrong-code rejected by actual original C; original C source/reference Wasm hashes unchanged')
