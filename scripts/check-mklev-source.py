"""Configured MKLEV source/data/control/native ABI guard, no shared outputs."""
from pathlib import Path
import json,re,hashlib,subprocess,argparse
r=Path(__file__).resolve().parents[1];w=r/'.cache/mklev-first-pass';m=json.loads((r/'nethack-c/wasm/tu-fragments/mklev-source-metadata.json').read_text());s=json.loads((r/'nethack-c/wasm/tu-fragments/mklev-schema.json').read_text());c=(r/'nethack-c/upstream/src/mklev.c').read_text();js=(r/'js/ported/mklev.js').read_text();rt=(r/'js/ported/mklev-runtime.js').read_text();abi=(r/'nethack-c/wasm/tu-fragments/mklev-support.c').read_text();lib=(r/'nethack-c/wasm/tu-libraries/mklev.js').read_text()
assert c==(r/'.cache/wasm64-build/tree/src/mklev.c').read_text()
for path,digest in m['compilerInputHashes'].items():assert hashlib.sha256((r/path).read_bytes()).hexdigest()==digest,path+' configured compiler input changed'
assert hashlib.sha256(c.encode()).hexdigest()==m['sourceSHA256']=='9958b95e15d0a6e27cac80c07a8bb8eac54ef239a51af3992cff303a615731a4'
f=m['functions'];assert re.findall(r'^export function (\w+)\(([^)]*)\)',js,re.M)==[(x['name'],','.join(p['name']for p in x['parameters']))for x in f]
assert len(f)==57 and sum(x['linkage']=='static'for x in f)==37
comments=re.findall(r'/\*[\s\S]*?\*/',c);assert len(comments)==243
for comment in comments:assert comment in js,comment
for x in f:
 assert s['functionTypes'][x['name']]==x['type']['qualType']
 assert ('teleport_mklev_'if x['linkage']=='static'else'')+x['name']+'__sig:'in lib
rng=re.findall(r'C\.rng_log_set_caller\(C\.literal\("mklev.c"\),(\d+),\(C\.literal\("([^"]+)"\)\)\)',js)
assert [(int(line),fn)for line,fn in rng]==[(x['line'],x['function'])for x in m['rng']] and len(rng)==97
assert len(s['statics'])==6
for x in s['statics']:assert x['js']in js
assert 'C.initialize('in js and 'unsigned int[41]'in js and 'nhl_sandbox_info'in js
assert 'break gotit;'in js and 'break skip_nonrogue;'in js and 'break skip0;'in js and 'break fill_vault;'in js
assert js.count('export function ')==57 and js.count('finally {C.stackRestore(stackFrame); }')==js.count('const stackFrame=C.stackSave();')
assert 'const states=new WeakMap()'in rt and 'finally{services.stackRestore(stackFrame);}'in rt
assert s['ownedFunctionPointers']==['mkroom_cmp'] and set(s['nativeFunctionPointers'])=={'rn2','rn2_on_display_rng'}
assert 'C.ownedFunctionPointer("mkroom_cmp")'in js and 'C.nativeFunctionPointer("rn2_on_display_rng")'in js
assert len(s['callbackCalls'])==2 and len(s['dynamicVariadics'])==1
assert 'mklev.c'not in abi and not re.search(r'\bstatic\b[^;\n]*=',abi)
assert not re.search(r'\b(?:for|while|do)\s*[({]',abi),'C transport must not own source loops'
assert 'nh_deterministic_qsort'not in abi and 'nhl_init'not in abi and 'trap_engravings'not in abi
assert 'teleport_mklev_mkroom_cmp' in abi and 'return(rn2)'in abi and 'return(rn2_on_display_rng)'in abi
# --captured avoids a new compiler process during the integration quiet window.
a=argparse.ArgumentParser();a.add_argument('--captured',action='store_true');args=a.parse_args()
base=[str(r/'.cache/emsdk/upstream/emscripten/emcc'),'-O2','-g','-I../include',*['-D'+d for d in m['defines']],'-sMEMORY64=1','-I'+str(r/'.cache/ncurses-wasm64-build/include'),'-include',str(r/'nethack-c/wasm/native-terminal.h')]
macros=(w/'macros.txt').read_text()if args.captured else subprocess.check_output(base+['-dM','-E','mklev.c'],cwd=r/'.cache/wasm64-build/tree/src',text=True)
for name in m['activeCPP']:assert re.search(r'^#define '+name+r'\b',macros,re.M),name
for name in m['inactiveCPP']:assert not re.search(r'^#define '+name+r'\b',macros,re.M),name
for alias,canonical in m['aliases'].items():
 assert re.search(r'(?:\.|->)'+alias+r'\b',c)
 assert re.search(r'^#define '+alias+r'\s+'+canonical+r'\b',macros,re.M),(alias,canonical)
 assert re.search(r'C\.field\([^\n]+,"'+canonical+r'"\)',js),canonical
 assert not re.search(r'\.\s*'+alias+r'\b',re.sub(r'/\*[\s\S]*?\*/','',js))
print('PASS MKLEV source guard: 57 ordered functions/types,243 comments,6 JS statics,97 RNG origins,7 aliases,native callback/RNG identities,source joins/initialized autos/stack frames; '+('captured'if args.captured else'fresh')+' configured CPP')
