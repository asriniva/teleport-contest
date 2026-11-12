"""Run deliberately wrong JS against unchanged configured original C binary."""
from pathlib import Path
from test_module_imports import rebase_test_module
import hashlib,subprocess,os,json
r=Path(__file__).resolve().parents[1];w=r/'.cache/mkmaze-first-pass';bad=w/'wrong-code';bad.mkdir(exist_ok=True)
paths=[r/'.cache/wasm64-build/tree/src/mkmaze.c',w/'mkmaze-reference.wasm'];before={str(p):hashlib.sha256(p.read_bytes()).hexdigest()for p in paths}
core=(r/'js/ported/mkmaze.js').read_text();needle='if(Number(!(C.isok(x,y)))) return 0;';assert core.count(needle)==1
core=core.replace(needle,'if(Number(!(C.isok(x,y)))) return 1; /* deliberate wrong-code witness */')
core=core
(bad/'mkmaze.js').write_text(rebase_test_module(core,r/'js/ported/mkmaze.js'))
runtime=(r/'js/nethack/bindings/mkmaze.js').read_text()
(bad/'mkmaze-runtime.js').write_text(rebase_test_module(runtime,r/'js/nethack/bindings/mkmaze.js',{(r/'js/ported/mkmaze.js').resolve():(bad/'mkmaze.js').as_uri()}))
p=subprocess.run([str(r/'.cache/emsdk/node/24.19.0_64bit/bin/node'),'scripts/test-tu-mkmaze.mjs'],env={**os.environ,'MKMAZE_RUNTIME':(bad/'mkmaze-runtime.js').as_uri()},text=True,capture_output=True)
(w/'wrong-code-negative.log').write_text(p.stdout+p.stderr)
assert p.returncode!=0 and 'iswall result'in p.stderr,(p.returncode,p.stdout,p.stderr[:1000])
assert before=={str(p):hashlib.sha256(p.read_bytes()).hexdigest()for p in paths}
print('PASS: deliberately wrong iswall rejected by actual-C result comparison; original C source and reference Wasm hashes unchanged')
