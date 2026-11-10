"""Reject deliberate wrong MKLEV JS against unchanged actual original C/Wasm."""
from pathlib import Path
import hashlib,subprocess,os,json
r=Path(__file__).resolve().parents[1];w=r/'.cache/mklev-first-pass';bad=w/'wrong-code';bad.mkdir(exist_ok=True)
paths=[r/'.cache/wasm64-build/tree/src/mklev.c',w/'mklev-reference.wasm'];before={str(p):hashlib.sha256(p.read_bytes()).hexdigest()for p in paths}
core=(r/'js/ported/mklev.js').read_text();needle='if(Number(C.i32(C.field(x,"mkroom","lx").value)<C.i32(C.field(y,"mkroom","lx").value))) return C.i32((-1));';assert core.count(needle)==1
core=core.replace(needle,needle.replace('C.i32((-1))','C.i32(1)')+' /* deliberate wrong-code witness */').replace("from './c-runtime.js'",'from '+json.dumps((r/'js/ported/c-runtime.js').as_uri()))
(bad/'mklev.js').write_text(core)
runtime=(r/'js/ported/mklev-runtime.js').read_text().replace("from './c-runtime.js'",'from '+json.dumps((r/'js/ported/c-runtime.js').as_uri()));(bad/'mklev-runtime.js').write_text(runtime)
p=subprocess.run([str(r/'.cache/emsdk/node/24.19.0_64bit/bin/node'),'scripts/test-tu-mklev.mjs'],env={**os.environ,'MKLEV_RUNTIME':(bad/'mklev-runtime.js').as_uri()},text=True,capture_output=True);(w/'wrong-code-negative.log').write_text(p.stdout+p.stderr)
assert p.returncode!=0 and 'mkroom_cmp result'in p.stderr,(p.returncode,p.stdout,p.stderr[:2000])
assert before=={str(p):hashlib.sha256(p.read_bytes()).hexdigest()for p in paths}
print('PASS: deliberate comparator wrong-code rejected by actual original C; original C source/reference Wasm hashes unchanged')
