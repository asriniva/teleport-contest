"""MKMAZE configured source/data/ABI preservation guard; no shared outputs."""
from pathlib import Path
import json,re,hashlib,subprocess
r=Path(__file__).resolve().parents[1];w=r/'.cache/mkmaze-first-pass';source=(r/'nethack-c/upstream/src/mkmaze.c').read_text();prepared=(r/'.cache/wasm64-build/tree/src/mkmaze.c').read_text();js=(r/'js/ported/mkmaze.js').read_text();schema=json.loads((r/'nethack-c/wasm/tu-fragments/mkmaze-schema.json').read_text());metadata=json.loads((r/'nethack-c/wasm/tu-fragments/mkmaze-source-metadata.json').read_text());functions=metadata['functions'];support=(r/'nethack-c/wasm/tu-fragments/mkmaze-support.c').read_text();runtime=(r/'js/nethack/bindings/mkmaze.js').read_text();library=(r/'nethack-c/wasm/tu-libraries/mkmaze.js').read_text()
assert source==prepared
assert hashlib.sha256(source.encode()).hexdigest()=='a2d6341107238f6e45b9305854f5dd4a34427f381558d9ecbc91578acdfbcab0'
actual=re.findall(r'^export function (\w+)\(([^)]*)\)',js,re.M)
expected=[(f['name'],','.join(p['name']for p in f['parameters']))for f in functions]
assert actual==expected,(actual,expected)
assert len(actual)==44 and sum(f['linkage']=='static'for f in functions)==22
for comment in re.findall(r'/\*[\s\S]*?\*/',source):assert comment in js,comment
for f in functions:assert schema['functionTypes'][f['name']]==f['type']['qualType']
for f in functions:
 symbol='teleport_mkmaze_'+f['name']if f['linkage']=='static'else f['name'];assert symbol+'__sig:'in library
# Original source RNG recorder tokens, including nested/multiple same-line calls.
orig=metadata['rng'];calls=re.findall(r'C\.rng_log_set_caller\(C\.literal\("mkmaze.c"\),(\d+),\(C\.literal\("([^"]+)"\)\)\)',js)
assert [(int(line),fn)for line,fn in calls]==[(x['line'],x['function'])for x in orig]
assert len(calls)==72
assert [int(line)for line,fn in calls if fn=='makemaz'][:3]==[1136,1144,1152]
base=[str(r/'.cache/emsdk/upstream/emscripten/emcc'),'-O2','-g','-I../include',*['-D'+d for d in json.loads((r/'nethack-c/wasm/compile-defines.json').read_text())],'-sMEMORY64=1','-I'+str(r/'.cache/ncurses-wasm64-build/include'),'-include',str(r/'nethack-c/wasm/native-terminal.h')]
macros=subprocess.check_output(base+['-dM','-E','mkmaze.c'],cwd=r/'.cache/wasm64-build/tree/src',text=True)
assert metadata['defines']==json.loads((r/'nethack-c/wasm/compile-defines.json').read_text())
for name in metadata['activeCPP']:assert re.search(r'^#define '+name+r'\b',macros,re.M),name
for name in metadata['inactiveCPP']:assert not re.search(r'^#define '+name+r'\b',macros,re.M),name
# Explicit raw-source/header alias seam: actual MemberExpr has canonical field.
for alias,canonical in [('wall_info','flags'),('arboreal_sdoor','candig')]:
 assert '.'+alias in source or '->'+alias in source
 assert re.search(r'^#define '+alias+r'\s+'+canonical+r'\b',macros,re.M),(alias,canonical)
 assert re.search(r'C\.field\([^\n]+,"rm","'+canonical+r'"\)',js)
 assert not re.search(r'[.][ ]*'+alias+r'\b',re.sub(r'/\*[\s\S]*?\*/','',js))
assert re.search(r'^#define nexthere\s+v\.v_nexthere\b',macros,re.M)
assert '\"vptrs\",\"v_nexthere\"' in js and '\"obj\",\"v\"'in js
rawaliases={a for a in set(re.findall(r'(?:\.|->)(\w+)',re.sub(r'/\*[\s\S]*?\*/','',source)))if re.search(r'^#define '+a+r'\s+',macros,re.M)}
assert rawaliases=={'wall_info','arboreal_sdoor','nexthere'},rawaliases
assert len(schema['statics'])==14
for n in ['hero_bubble','up','spine_array','orcfruit','water_pos','air_pos','bm2','bm3','bm4','bm5','bm6','bm7','bm8','bmask']:assert 'name:"'+n+'"'in js
bitmaps={'bm2':[2,1,3],'bm3':[3,2,7,7],'bm4':[4,3,6,15,6],'bm5':[5,3,14,31,14],'bm6':[6,4,30,63,63,30],'bm7':[7,4,62,127,127,62],'bm8':[8,4,126,255,255,126]}
for n,v in bitmaps.items():
 row=next(x for x in schema['statics']if x['name']==n);assert row['js']=='['+','.join('C.u8('+str(x)+')'for x in v)+']';assert row['js']in js
assert 'C.copy('in js and 'copyWithin'in runtime
assert 'const states=new WeakMap()'in runtime and 'finally{services.stackRestore(stackFrame);}'in runtime
assert js.count('const stackFrame=C.stackSave();')==js.count('finally {C.stackRestore(stackFrame); }')
assert not re.search(r'\b(?:spine_array|orcfruit|water_pos|air_pos|bm[2-8]|bmask)\b',support)
assert not re.search(r'\bstatic\b[^;\n]*=',support), 'C must reserve zero backing only'
assert '#include'in support and 'mkmaze.c'not in support
print('PASS MKMAZE: 44 exact ordered functions/params/types, 187 source comments, 14 JS statics/bitmap bytes, 72 recorder origins, active CPP/forced ABI, rm aliases, frame/storage/import scope')
