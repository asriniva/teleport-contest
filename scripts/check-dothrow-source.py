"""Configured DOTHROW source/data/type/control/native ABI preservation guard."""
from pathlib import Path
import json,re,hashlib,subprocess,argparse
r=Path(__file__).resolve().parents[1];w=r/'.cache/dothrow-first-pass';m=json.loads((r/'nethack-c/wasm/tu-fragments/dothrow-source-metadata.json').read_text());s=json.loads((r/'nethack-c/wasm/tu-fragments/dothrow-schema.json').read_text());c=(r/'nethack-c/upstream/src/dothrow.c').read_text();js=(r/'js/ported/dothrow.js').read_text();rt=(r/'js/ported/dothrow-runtime.js').read_text();abi=(r/'nethack-c/wasm/tu-fragments/dothrow-support.c').read_text();lib=(r/'nethack-c/wasm/tu-libraries/dothrow.js').read_text()
assert c==(r/'.cache/wasm64-build/tree/src/dothrow.c').read_text()
for path,digest in m['compilerInputHashes'].items():assert hashlib.sha256((r/path).read_bytes()).hexdigest()==digest,path+' configured compiler input changed'
assert hashlib.sha256(c.encode()).hexdigest()==m['sourceSHA256']=='1fb4be7ca03d4d4256a7637fcaab3ec3048f7c71928a4b5577ab6477ed28bc06'
f=m['functions'];assert re.findall(r'^export function (\w+)\(([^)]*)\)',js,re.M)==[(x['name'],','.join(p['name']for p in x['parameters']))for x in f]
assert len(f)==39 and sum(x['linkage']=='static'for x in f)==16
comments=re.findall(r'/\*[\s\S]*?\*/',c);assert len(comments)==333
for comment in comments:assert comment in js,comment
for x in f:
 assert s['functionTypes'][x['name']]==x['type']['qualType']
 assert ('teleport_dothrow_'if x['linkage']=='static'else'')+x['name']+'__sig:'in lib
rng=re.findall(r'C\.rng_log_set_caller\(C\.literal\("dothrow.c"\),(\d+),\(C\.literal\("([^"]+)"\)\)\)',js)
assert [(int(line),fn)for line,fn in rng]==[(x['line'],x['function'])for x in m['rng']] and len(rng)==33
assert len(s['statics'])==5 and [x['name']for x in s['statics']]==['nogood','acceptgift','maybeluck','noluck','addluck']
for x in s['statics']:assert x['js']in js
assert 'C.copy(save_osplit,C.field(C.field(C.svc,'in js and 'C.sizes["struct obj_split"]);'in js
assert 'range=C.local("int",range);'in js and 'obj=C.local("struct obj *",obj);'in js and 'obj.address)'in js
assert js.count('/* original goto ')==9
for label in ['unsplit_stack','petrify','nopick']:assert label+': {'in js and 'break '+label+';'in js
assert js.count('C.literal("elementary physics")')==1
assert js.count('export function ')==39 and js.count('finally {C.stackRestore(stackFrame); }')==js.count('const stackFrame=C.stackSave();')
assert 'const states=new WeakMap()'in rt and 'finally{services.stackRestore(stackFrame);}'in rt
assert s['ownedFunctionPointers']==['dofire','hurtle_step','mhurtle_step','throw_ok'] and s['nativeFunctionPointers']==['doswapweapon','dowield','xname']
for name in s['ownedFunctionPointers']:assert 'C.ownedFunctionPointer("'+name+'")'in js
for name in s['nativeFunctionPointers']:assert 'C.nativeFunctionPointer("'+name+'")'in js
assert len(s['callbackCalls'])==6 and len(s['variadics'])==81 and not s['dynamicVariadics']
assert 'dothrow.c'not in abi and not re.search(r'\bstatic\b[^;\n]*=',abi)
assert not re.search(r'\b(?:for|while|do)\s*[({]',abi),'C transport must not own source loops'
for forbidden in ['nogood','acceptgift','maybeluck','noluck','addluck','save_osplit','unsplit_stack']:assert forbidden not in abi
assert 'Mklev'not in rt+lib and 'mklev'not in rt+lib
# Check current actual flags, forced native ABI and inherited header member aliases.
a=argparse.ArgumentParser();a.add_argument('--captured',action='store_true');args=a.parse_args()
base=[str(r/'.cache/emsdk/upstream/emscripten/emcc'),'-O2','-g','-I../include',*['-D'+d for d in m['defines']],'-sMEMORY64=1','-I'+str(r/'.cache/ncurses-wasm64-build/include'),'-include',str(r/'nethack-c/wasm/native-terminal.h')]
macros=(w/'macros.txt').read_text()if args.captured else subprocess.check_output(base+['-dM','-E','dothrow.c'],cwd=r/'.cache/wasm64-build/tree/src',text=True)
for name in m['activeCPP']:assert re.search(r'^#define '+name+r'\b',macros,re.M),name
for name in m['inactiveCPP']:assert not re.search(r'^#define '+name+r'\b',macros,re.M),name
for alias,canonical in m['aliases'].items():
 assert re.search(r'(?:\.|->)'+alias+r'\b',c)
 assert re.search(r'^#define '+alias+r'\s+'+re.escape(canonical)+r'\b',macros,re.M),(alias,canonical)
 if alias=='ocarry':assert '"vptrs","v_ocarry"'in js and '"obj","v"'in js
 else:assert re.search(r'C\.field\([^\n]+,"'+canonical+r'"\)',js),canonical
 assert not re.search(r'\.\s*'+alias+r'\b',re.sub(r'/\*[\s\S]*?\*/','',js))
print('PASS DOTHROW source:39 ordered names/formals/prototypes,333 comments,5 JS statics,33 RNG origins,3 aliases,9goto/3joins,8byte struct init-copy,addressed parameters,native callback identity families/general indirect calls,zero-only C ABI; '+('captured'if args.captured else'fresh')+' CPP/input hashes')
