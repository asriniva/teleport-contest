"""Actual compiler settings from the accepted golden 110 Emscripten build."""
from pathlib import Path
import hashlib,json

def c_flags(root):
    root=Path(root)
    profile=json.loads((root/'nethack-c/wasm/golden-emscripten-profile.json').read_text())
    sdk=root/'.cache/emsdk/upstream/emscripten/emscripten-version.txt'
    assert json.loads(sdk.read_text())==profile['emscripten'], 'Emscripten version differs from golden44'
    definitions=root/'nethack-c/wasm/compile-defines.json'
    header=root/profile['forcedInclude']
    sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
    assert sha(definitions)==profile['compileDefinesSha256'], 'Compiler definitions differ from golden44'
    assert sha(header)==profile['forcedIncludeSha256'], 'ABI header differs from golden44'
    assert json.loads(definitions.read_text())==profile['defines']
    return [*profile['flags'], '-I'+str(root/'.cache/wasm64-build/tree/include'),
            *['-D'+value for value in profile['defines']],
            '-sMEMORY64='+str(profile['memory64']),
            '-I'+str(root/profile['terminfoInclude']), '-include', str(header)]
