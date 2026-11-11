"""Check compilation settings against the accepted 44/44 Emscripten profile."""
from pathlib import Path
import ast, hashlib, json, shlex, subprocess
from golden_emscripten_profile import c_flags
ROOT=Path(__file__).resolve().parents[1]
profile=json.loads((ROOT/'nethack-c/wasm/golden-emscripten-profile.json').read_text())
expected=c_flags(ROOT)
# Read the real build driver's assignments instead of maintaining a second
# interpretation of its flags. Only these three flag-construction statements
# are evaluated; no build/preparation/link operation is invoked.
def driver_flags(source):
    tree=ast.parse(source)
    statements=[n for n in tree.body if (isinstance(n,ast.Assign) and any(isinstance(t,ast.Name)and t.id=='flags'for t in n.targets))or(isinstance(n,ast.AugAssign)and isinstance(n.target,ast.Name)and n.target.id=='flags')]
    assert len(statements)==3,'Review changed build-driver flag construction'
    context={'ROOT':ROOT,'TREE':ROOT/'.cache/wasm64-build/tree','defines':profile['defines'],'terminfo_include':ROOT/profile['terminfoInclude'],'shlex':shlex}
    exec(compile(ast.Module(body=statements,type_ignores=[]),'<build flags>','exec'),context)
    return ['-I'+str(ROOT/'.cache/wasm64-build/tree/include')if x=='-I../include'else x for x in shlex.split(context['flags'])]
actual=driver_flags((ROOT/'nethack-c/wasm/build.py').read_text())
assert actual==expected,(actual,expected)
original=ROOT/'.cache/tu110-warn-fixed-gate-snapshot/nethack-c/wasm/build.py'
if original.exists():
    assert hashlib.sha256(original.read_bytes()).hexdigest()==profile['sourceBuildScriptSha256']
    assert driver_flags(original.read_text())==expected
sdk=ROOT/'.cache/emsdk'
clang=subprocess.check_output([str(sdk/'upstream/bin/clang'),'--version'],text=True).splitlines()[0]
assert clang==profile['clangFirstLine'],(clang,profile['clangFirstLine'])
upstream=subprocess.check_output(['git','-C',str(ROOT/'nethack-c/upstream'),'rev-parse','HEAD'],text=True).strip()
assert upstream==profile['upstream']
print('PASS: current game and comparison compiler flags/header/definitions/LLVM/Emscripten/upstream match the accepted golden44 Emscripten profile.')
