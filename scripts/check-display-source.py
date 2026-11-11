"""Configured DISPLAY source/storage/terminal scope/typed ABI preservation guard."""
from pathlib import Path
import json,re,hashlib,subprocess,argparse
r=Path(__file__).resolve().parents[1];w=r/'.cache/display-first-pass'
def read(p):return (r/p).read_text()
m=json.loads(read('nethack-c/wasm/tu-fragments/display-source-metadata.json'));s=json.loads(read('nethack-c/wasm/tu-fragments/display-schema.json'))
a=argparse.ArgumentParser();a.add_argument('--captured',action='store_true');a.add_argument('--current-profile',action='store_true');args=a.parse_args()
c=read('nethack-c/upstream/src/display.c');js=read('js/ported/display.js');rt=read('js/ported/display-runtime.js');abi=read('nethack-c/wasm/tu-fragments/display-support.c');lib=read('nethack-c/wasm/tu-libraries/display.js');storage=read('nethack-c/wasm/tu-fragments/display-storage.c')
assert c==read('.cache/wasm64-build/tree/src/display.c')
assert hashlib.sha256(c.encode()).hexdigest()==m['sourceSHA256']=='c40bea2174713159eb7aa7b3b443f176a48282866c31d658449a1b2092145423'
for path,digest in m['compilerInputHashes'].items():
 actual=hashlib.sha256((r/path).read_bytes()).hexdigest()
 if args.current_profile and path=='nethack-c/wasm/build.py':
  assert digest=='7dc84c8a838a44495394b4da450ca1ca372ea01357ecd92f9590e315ee3621f6'
  import sys
  sys.path.insert(0,str(r/'scripts'))
  from reviewed_build_provenance import nhlua_transport_baseline
  baseline_bytes=nhlua_transport_baseline(r,'7f7d2856ecc84c0ee4a4c402b8145e178c9fa05f73baae2761167bf2ebfb3a0d')
  initial=(w/'build-initial-captured-reconstructed.py').read_text();assert hashlib.sha256(initial.encode()).hexdigest()==digest
  current=initial.replace('import ast\n','',1);extra="if any(port['name'] == 'do' for port in ports):\n    node_command = ast.literal_eval(subprocess.check_output([str(SDK / 'upstream/emscripten/em-config'), 'NODE_JS'], text=True))\n    assert isinstance(node_command, list) and all(isinstance(part, str) for part in node_command)\n    run([*node_command, ROOT / 'scripts/check-do-data.mjs'], cwd=ROOT)\n"
  assert current.replace(extra,'',1)==baseline_bytes.decode('utf8')
 else:assert actual==digest,path
f=m['functions'];assert len(f)==71 and sum(x['linkage']=='static'for x in f)==17
assert re.findall(r'^export function (\w+)\(([^)]*)\)',js,re.M)==[(x['name'],','.join(p['name']for p in x['parameters']))for x in f]
comments=re.findall(r'/\*[\s\S]*?\*/',c);assert len(comments)==323
for comment in comments:assert comment in js,comment
for x in f:
 assert s['functionTypes'][x['name']]==x['type']['qualType']
 assert ('teleport_display_'if x['linkage']=='static'else'')+x['name']+'__sig:'in lib
assert len(s['statics'])==23 and sum(x['public']for x in s['statics'])==7
assert [x['sourceName']for x in s['statics']if x['public']]==m['publicObjects']
assert len({x['name']for x in s['statics']})==23
for row in s['statics']:assert row['js']in js
for name in ['swallowed.lastx','swallowed.lasty','under_water.lastx','under_water.lasty','under_water.dela','under_ground.dela']:assert 'C.staticAddress("'+name+'")'in js
gm=next(x for x in s['statics']if x['name']=='glyphmap');assert gm['type']=='struct glyph_map_entry[9624]' and gm['js'].startswith('[[0,[8,0]')
assert not re.search(r'\bstatic\b[^;\n]*=',abi) and not re.search(r'\b(?:for|while|do)\s*[({]',abi)
assert 'display.c'not in abi
assert not re.search(r'\b(?:for|while|do|return)\b|=',storage)
for row in s['statics']:
 if row['public']:
  assert re.search(r'\b'+row['sourceName']+r'(?:\[.*?\])?;',storage)
  assert re.search(r'extern [^;]+\b'+row['sourceName']+r'(?:\[.*?\])?;',abi)
assert js.count('/* original goto ')==13
for name in ['show_mem','do_twall','horiz','do_crwall']:assert js.count('function '+name+'(')==1
assert 'post_map: {'in js
assert len(re.findall(r'C\.rn2_on_display_rng\(',js))==24 and not re.search(r'C\.rng_log_set_caller\(',js)
assert len(s['callbackCalls'])==10 and len(s['dynamicVariadics'])==1 and len(s['variadics'])==21
assert s['ownedFunctionPointers']==['mimic_light_blocking'] and not s['nativeFunctionPointers']
assert 'C.ownedFunctionPointer("mimic_light_blocking")'in js
for row in s['callbackCalls']:
 if 'glyph_info'in row['type']:assert row['type'].count('const glyph_info *')==2
assert s['dependencies']['do_screen_description']['byValueParameters']==[0]
assert 'teleport_display_dep_do_screen_description'in abi and '(do_screen_description)(*a0,'in abi
assert 'initializeDisplay'in rt and 'const states=new WeakMap()'in rt
assert 'addOnInit(() => Module.nethackPorted.initializeDisplay(teleportDisplayServices()))'in lib
assert lib.count('"$teleportDisplayInit"],')==71
# Initial aggregate scalar writes go directly through JS DataView/cells, including const data.
assert 'else env.cell(env.field(at,key,f.name).address,f.canonical).value=v;'in rt
assert js.count('const stackFrame=C.stackSave();')==js.count('finally {C.stackRestore(stackFrame); }')
base=[str(r/'.cache/emsdk/upstream/emscripten/emcc'),'-O2','-g','-I../include',*['-D'+x for x in m['defines']],'-sMEMORY64=1','-I'+str(r/'.cache/ncurses-wasm64-build/include'),'-include',str(r/'nethack-c/wasm/native-terminal.h')]
macros=(w/'macros.txt').read_text()if args.captured else subprocess.check_output(base+['-dM','-E','display.c'],cwd=r/'.cache/wasm64-build/tree/src',text=True)
for name in m['activeCPP']:assert re.search(r'^#define '+name+r'\b',macros,re.M),name
for name in m['inactiveCPP']:assert not re.search(r'^#define '+name+r'\b',macros,re.M),name
for alias,canonical in m['aliases'].items():
 assert re.search(r'(?:\.|->)'+alias+r'\b',c)
 assert re.search(r'^#define '+alias+r'\s+'+canonical+r'\b',macros,re.M)
 assert re.search(r'C\.field\([^\n]+,"'+canonical+r'"\)',js),canonical
 assert not re.search(r'\.\s*'+alias+r'\b',re.sub(r'/\*[\s\S]*?\*/','',js))
print('PASS DISPLAY71 ordered names/formals/prototypes,323comments,23JS storage/7public/9624row partial-init,24displayRNG,7aliases,13goto5joins,typed native callbacks/4byte coord-by-value,JS const init and eager hook,zero-only ABI; '+('captured'if args.captured else'fresh')+' CPP/input hashes. Behavior/startup proof separate.')
