"""Configured DUNGEON source/data/control/ABI guard; no shared writes."""
from pathlib import Path
from reviewed_build_provenance import nhlua_transport_baseline
import json,re,hashlib,subprocess,argparse
r=Path(__file__).resolve().parents[1];w=r/'.cache/dungeon-first-pass'
def read(name):return (r/name).read_text()
m=json.loads(read('nethack-c/wasm/tu-fragments/dungeon-source-metadata.json'));s=json.loads(read('nethack-c/wasm/tu-fragments/dungeon-schema.json'))
c=read('nethack-c/upstream/src/dungeon.c');js=read('js/ported/dungeon.js');rt=read('js/ported/dungeon-runtime.js');abi=read('nethack-c/wasm/tu-fragments/dungeon-support.c');lib=read('nethack-c/wasm/tu-libraries/dungeon.js')
assert c==read('.cache/wasm64-build/tree/src/dungeon.c')
assert hashlib.sha256(c.encode()).hexdigest()==m['sourceSHA256']=='4b3e7b2a8afa70fc442a99fd79551982836def70864f738085926f3f326906e9'
for path,digest in m['compilerInputHashes'].items():
 if path=='nethack-c/wasm/build.py':nhlua_transport_baseline(r,digest)
 else:assert hashlib.sha256((r/path).read_bytes()).hexdigest()==digest,path
f=m['functions'];assert len(f)==110 and sum(x['linkage']=='static'for x in f)==44
assert re.findall(r'^export function (\w+)\(([^)]*)\)',js,re.M)==[(x['name'],','.join(p['name']for p in x['parameters']))for x in f]
comments=re.findall(r'/\*[\s\S]*?\*/',c);assert len(comments)==331
for comment in comments:assert comment in js,comment
for x in f:
 assert s['functionTypes'][x['name']]==x['type']['qualType']
 assert ('teleport_dungeon_'if x['linkage']=='static'else'')+x['name']+'__sig:'in lib
rng=re.findall(r'C\.rng_log_set_caller\(C\.literal\("dungeon.c"\),(\d+),\(C\.literal\("([^"]+)"\)\)\)',js)
assert [(int(line),fn)for line,fn in rng]==[(x['line'],x['function'])for x in m['rng']] and len(rng)==11
assert [x['name']for x in s['statics']]==['branch_id','level_map','flagstrs','flagstrs2i','dgnaligns','dgnaligns2i','brdirstr','brdirstr2i','brtypes','brtypes2i']
for row in s['statics']:assert row['js']in js
assert s['statics'][1]['type']=='struct level_map[27]' and s['statics'][0]['js']=='0'
assert len(s['callbackCalls'])==25 and len(s['dynamicVariadics'])==1 and len(s['variadics'])==114
assert all('const char *'in row['type']for row in s['callbackCalls']if row['site']in [2,5,6,7,9,10,11,12,13,14,15,18,19,20,23])
assert not s['ownedFunctionPointers'] and not s['nativeFunctionPointers']
assert len(s['globals'])==25 and 'shtypes'in [x['name']for x in s['globals']] and 'tune'not in [x['name']for x in s['globals']]
assert 'let shtypes'not in js and 'extern const struct shclass shtypes[];'in abi
assert 'C.copy(save_uz,C.field(C.u,"you","uz").address,C.sizes["struct d_level"]);'in js
assert 'C.initialize(sbi,"struct nhl_sandbox_info"'in js and 'let map=C.stackAlloc((1*33));'in js
assert 'original goto'not in js
assert js.count('const stackFrame=C.stackSave();')==js.count('finally {C.stackRestore(stackFrame); }')
assert 'const states=new WeakMap()'in rt and 'finally{services.stackRestore(stackFrame);}'in rt
assert 'dungeon.c'not in abi and not re.search(r'\bstatic\b[^;\n]*=',abi)
assert not re.search(r'\b(?:for|while|do)\s*[({]',abi)
for name in ['proto_dungeon','lchoice','level_map']:assert 'struct '+name+' {'in abi
a=argparse.ArgumentParser();a.add_argument('--captured',action='store_true');args=a.parse_args()
base=[str(r/'.cache/emsdk/upstream/emscripten/emcc'),'-O2','-g','-I../include',*['-D'+d for d in m['defines']],'-sMEMORY64=1','-I'+str(r/'.cache/ncurses-wasm64-build/include'),'-include',str(r/'nethack-c/wasm/native-terminal.h')]
macros=(w/'macros.txt').read_text()if args.captured else subprocess.check_output(base+['-dM','-E','dungeon.c'],cwd=r/'.cache/wasm64-build/tree/src',text=True)
for name in m['activeCPP']:assert re.search(r'^#define '+name+r'\b',macros,re.M),name
for name in m['inactiveCPP']:assert not re.search(r'^#define '+name+r'\b',macros,re.M),name
for alias,canonical in m['aliases'].items():
 assert re.search(r'(?:\.|->)'+alias+r'\b',c)
 assert re.search(r'^#define '+alias+r'\s+'+canonical+r'\b',macros,re.M)
 assert re.search(r'C\.field\([^\n]+,"rm","'+canonical+r'"\)',js)
 assert not re.search(r'\.\s*'+alias+r'\b',re.sub(r'/\*[\s\S]*?\*/','',js))
print('PASS DUNGEON110 ordered names/formals/prototypes,331comments,10statics,11RNG origins,rawrm alias,25globals/25window+dynamic native targets,recursive scratch/aggregatecopy,type-only/zero ABI; '+('captured'if args.captured else'fresh')+' CPP/input hashes; behavior proof recorded separately')
