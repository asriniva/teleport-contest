"""UNIXUNIX configured source/profile/control/data/ABI obligations; no behavior claim."""
from pathlib import Path
import json,re,hashlib,subprocess,argparse
r=Path(__file__).resolve().parents[1];w=r/'.cache/unixunix-first-pass'
load=lambda p:json.loads((r/p).read_text())
m=load('nethack-c/wasm/tu-fragments/unixunix-source-metadata.json');s=load('nethack-c/wasm/tu-fragments/unixunix-schema.json');meta=json.loads((w/'core-meta.json').read_text())
c=(r/'.cache/wasm64-build/tree/sys/unix/unixunix.c').read_text();pristine=(r/'nethack-c/upstream/sys/unix/unixunix.c').read_text();j=(r/'js/ported/unixunix.js').read_text();abi=(r/'nethack-c/wasm/tu-fragments/unixunix-support.c').read_text();lib=(r/'nethack-c/wasm/tu-libraries/unixunix.js').read_text();runtime=(r/'js/ported/unixunix-runtime.js').read_text()
sha=lambda b:hashlib.sha256(b).hexdigest()
assert sha(c.encode())==m['sourceSHA256']=='42b526bbed87ae89acdd655cb08426bdf66d1b7d138d16be4e63b8592bab8ecd'
assert sha(pristine.encode())==m['pristineSHA256']=='0a434dc320dadf31c1bdf40e086386032918b65157799155abfe77ca6edc4784'
assert pristine.replace('if (!isatty(0))','if (!isatty(0) && !getenv("NOMUX_MARKERS"))')==c
assert sha((w/'inventory-notes.txt').read_bytes())==m['inventorySHA256']
# Exact already-reviewed builder inverse; no input-pin refresh or broad exclusion.
for p,h in m['compilerInputHashes'].items():
 if p=='nethack-c/wasm/build.py':
  from importlib.util import spec_from_file_location,module_from_spec
  reviewed_spec=spec_from_file_location('unixunix_reviewed_build',r/'scripts/reviewed_build_provenance.py')
  reviewed=module_from_spec(reviewed_spec);reviewed_spec.loader.exec_module(reviewed)
  input_bytes=reviewed.nhlua_transport_baseline(r,h)
 elif p=='.cache/wasm64-build/tree/src/Makefile':
  from importlib.util import spec_from_file_location,module_from_spec
  make_spec=spec_from_file_location('unixunix_reviewed_makefile',r/'nethack-c/wasm/tu-fragments/unixunix-reviewed-makefile.py')
  make_review=module_from_spec(make_spec);make_spec.loader.exec_module(make_review)
  input_bytes=make_review.reviewed_unixunix_makefile(r,h)
 else:input_bytes=(r/p).read_bytes()
 assert sha(input_bytes)==h,p
f=m['functions'];assert len(f)==8 and sum(x['linkage']=='static'for x in f)==2
assert re.findall(r'^export function (\w+)\(([^)]*)\)',j,re.M)==[(x['name'],','.join(p['name']for p in x['parameters']))for x in f]
comments=re.findall(r'/\*[\s\S]*?\*/',c);assert len(comments)==62 and all(x in j for x in comments)
for x in f:assert s['functionTypes'][x['name']]==x['type']['qualType'];assert ('teleport_unixunix_'if x['linkage']=='static'else'')+x['name']+'__sig:'in lib
assert len(s['statics'])==3 and not any(x['public']for x in s['statics'])
assert [(x['sourceName'],x['type'])for x in s['statics']]==[('buf','struct stat'),('destroy_old_game_prompt','char[72]'),('Instead_prompt','char[26]')]
for row in s['statics']:assert row['js']in j
assert not m['sourceEnums'];assert j.count('/* original goto gotlock */')==5 and j.count('gotlock: {')==1
assert j.count('const __old=')==2 and not re.search(r'\bC\.(?:rn2|rnd|rn1|rng_\w+)\(',j)
assert len(s['dependencies'])==35 and len(s['variadics'])==21 and len(s['callbackCalls'])==7
assert s['nativeFunctionPointers']==['done1']and not s['ownedFunctionPointers']
assert meta['dependencyReturns']['teleport_native_signal']=='void (*)(int)'
assert 'uintptr_t teleport_unixunix_dep_signal(int a0,void (* a1)(int))'in abi or 'teleport_unixunix_dep_signal(int' in abi
assert 'volatile struct window_procs*p=at' in abi
assert not re.search(r'\bstatic\b[^;\n]*=',abi)and not re.search(r'\b(?:for|while|do)\s*[({]',abi)
assert 'unixunix.c'not in abi and 'state.env=createUnixunixEnvironment(forwarding)'in runtime and 'finally{state.services=previous;}'in runtime and 'finally{services.stackRestore(stackFrame);}'in runtime
assert 'Object.setPrototypeOf'not in runtime
helper={'ptr','sizes','cell','field','global','staticAddress','local','copy','initialize','literal','variadic','indirect','ownedFunctionPointer','nativeFunctionPointer','dynamicVariadic','stackAlloc','stackSave','stackRestore','heap','i8','u8','i16','u16','i32','u32','i64','u64'}
internal={'abiRead','abiWrite','abiAddress','abiGlobal','abiLayout','abiStorage'}
deps=set(s['dependencies']);assert not (helper|internal)&deps,sorted((helper|internal)&deps)
core=re.sub(r'/\*[\s\S]*?\*/','',j);provided=helper|set(s['layoutKeys'])|{g['name']for g in s['globals']}|deps
assert not set(re.findall(r'\bC\.(\w+)',core))-provided
assert not re.search(r'\bC\s*\[',core)
for name in deps|internal:assert name+':'in lib,name
for name in internal:assert 'services.'+name+'('in runtime,name
assert 'services.read('not in runtime and 'services.write('not in runtime
assert 'C.read('in j and 'C.write('in j
A=json.loads((w/'ast.json').read_text());bodies=[n for n in A['inner']if n.get('kind')=='FunctionDecl'and n.get('name')in {x['name']for x in f}and not n.get('loc',{}).get('includedFrom')and any(x.get('kind')=='CompoundStmt'for x in n.get('inner',[]))]
def walk(n):
 yield n
 for x in n.get('inner',[]):yield from walk(x)
allnodes=[n for b in bodies for n in walk(b)]
assert len(bodies)==8 and sum(n.get('kind')=='GotoStmt'for n in allnodes)==5
assert sum(n.get('kind')=='LabelStmt'for n in allnodes)==1
assert not any(n.get('kind')=='CompoundAssignOperator'for n in allnodes)
assert sum(n.get('kind')=='UnaryOperator'and n.get('opcode')=='++'for n in allnodes)==2
# Actual initialized/uninitialized VarDecl distinction controls cell writes.
addressed=set(meta['addressed']);autos=[n for n in allnodes if n.get('kind')=='VarDecl'and n['id']in addressed]
assert [(n['name'],n.get('init'),n['type']['qualType'])for n in autos]==[('date',None,'time_t'),('lockedpid',None,'int'),('sb',None,'struct stat')]
assert 'sb=C.stackAlloc(C.sizes["struct stat"]);'in j
assert 'date=C.local("long long");'in j and 'lockedpid=C.local("int");'in j
assert 'C.local("long long",0)'not in j and 'C.local("int",0)'not in j
assert 'env.local=(t,...initial)'in runtime and 'if(initial.length)cell.value=initial[0];'in runtime
test=(r/'scripts/test-tu-unixunix.mjs').read_text()
assert 'UNIXUNIX_PROBE_DIR' in test and "../.cache/tu-probes"in test
assert 'fixture-regions.json'not in test

test=(r/'scripts/test-tu-unixunix.mjs').read_text();gate="if(process.env.TELEPORT_NATIVE_TESTS!=='0') throw Error('UNIXUNIX has no native reference fixture; Emscripten results cannot be labeled native.');"
assert gate in test and test.index(gate)<test.index('await import(pathToFileURL(')
assert not re.search(r'^import .*Factory',test,re.M)
builder=(r/'scripts/build-tu-unixunix.py').read_text();assert builder.count("'-sTABLE_BASE=2'")==1 and '--table-base'not in builder
p=argparse.ArgumentParser();p.add_argument('--captured',action='store_true');a=p.parse_args();command=json.loads((w/'command.json').read_text());base=command['args'][:-1];source=command['args'][-1]
macros=(w/'macros.txt').read_bytes()if a.captured else subprocess.check_output(base+['-dM','-E',source],cwd=command['cwd'])
assert macros==(w/'macros.txt').read_bytes(),'whole macros changed';text=macros.decode()
for name in m['activeCPP']:assert re.search(r'^#define '+name+r'\b',text,re.M),name
for name in m['inactiveCPP']:assert not re.search(r'^#define '+name+r'\b',text,re.M),name
for alias,canonical in m['aliases'].items():assert re.search(r'^#define '+alias+r'(?:\s|\().*'+re.escape(canonical),text,re.M),(alias,canonical)
assert ',"st_mtim").address,"timespec","tv_sec")'in j and ',"flag","debug")'in j and 'C.teleport_native_signal('in j
if not a.captured:assert subprocess.check_output(base+['-E',source],cwd=command['cwd'])==(w/'configured.c').read_bytes(),'whole CPP changed'
print('PASS UNIXUNIX8 exact names/order/formals/62comments/3JS-private statics202bytes/0RNG/5goto1join/2unaries/0compound/aliases/volatile callbacks/native fnptr-return/ALL ABI-dependency namespaces disjoint; '+('captured'if a.captured else'fresh')+' CPP+input hashes. Behavior and native-host proof separate.')
