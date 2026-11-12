"""Reject deliberately wrong JavaScript against unchanged original C/Wasm."""
from pathlib import Path
from test_module_imports import rebase_test_module
import hashlib,subprocess,os,json
r=Path(__file__).resolve().parents[1];w=r/'.cache/dothrow-first-pass';bad=w/'wrong-code';bad.mkdir(exist_ok=True)
paths=[r/'.cache/wasm64-build/tree/src/dothrow.c',w/'dothrow-reference.wasm'];before={str(p):hashlib.sha256(p.read_bytes()).hexdigest()for p in paths}
core=(r/'js/ported/dothrow.js').read_text();needle='let multishot=0;';assert core.count(needle)==1
core=core.replace(needle,'let multishot=1; /* deliberate wrong-code witness */');(bad/'dothrow.js').write_text(rebase_test_module(core,r/'js/ported/dothrow.js'))
runtime=(r/'js/nethack/bindings/dothrow.js').read_text();(bad/'dothrow-runtime.js').write_text(rebase_test_module(runtime,r/'js/nethack/bindings/dothrow.js',{(r/'js/ported/dothrow.js').resolve():(bad/'dothrow.js').as_uri()}))
p=subprocess.run([str(r/'.cache/emsdk/node/24.19.0_64bit/bin/node'),'scripts/test-tu-dothrow.mjs'],env={**os.environ,'DOTHROW_RUNTIME':(bad/'dothrow-runtime.js').as_uri()},text=True,capture_output=True);(w/'wrong-code-negative.log').write_text(p.stdout+p.stderr)
assert p.returncode!=0 and 'multishot_class_bonus result'in p.stderr,(p.returncode,p.stdout,p.stderr[:2000])
assert before=={str(p):hashlib.sha256(p.read_bytes()).hexdigest()for p in paths}
print('PASS: deliberately wrong multishot rejected by actual-C result comparison; original C source/reference Wasm hashes unchanged')
