"""Read-only configured GETPOS data/provenance guards; no equivalence claim."""
from pathlib import Path
import ast,json,re,subprocess
root=Path(__file__).resolve().parents[3]
source=(root/'nethack-c/upstream/src/getpos.c').read_text()
assert source==(root/'.cache/wasm64-build/tree/src/getpos.c').read_text(),'Review changed prepared GETPOS source'
core=(root/'js/ported/getpos.js').read_text();library=(root/'nethack-c/wasm/tu-libraries/getpos.js').read_text();support=(root/'nethack-c/wasm/tu-fragments/getpos-support.inc').read_text();runtime=(root/'js/ported/getpos-runtime.js').read_text()
clean=re.sub(r'/\*.*?\*/|//[^\n]*',lambda m:'\n'*m[0].count('\n'),source,flags=re.S)
literals=sorted(set(ast.literal_eval(x) for x in re.findall(r'"(?:\\.|[^"\\])*"',clean)));capacity=sum(len(x.encode())+1 for x in literals)
assert json.loads(re.search(r'var sourceLiterals=new Set\((\[[^\n]*\])\);',library)[1])==literals
assert int(re.search(r'teleport_getpos_literals\[(\d+)\]',support)[1])==capacity
assert '!sourceLiterals.has(v)' in library
# Original seven readonly tables retain all strings/constants and row order.
tables=[]
for m in re.finditer(r'static const char \*const (\w+)(?:\[[^]]*\])+\s*=\s*\{(.*?)\};',clean,re.S):
 name=m[1];expected=ast.literal_eval('['+m[2].replace('{','[').replace('}',']')+']');actual=re.search(r'const '+name+r' = (\[.*?\]);',core,re.S)[1];assert ast.literal_eval(actual)==expected,('Changed original GETPOS table',name);tables.append(name)
for name in ['pick_chars_def','mMoOdDxX_def']:
 if name=='pick_chars_def':c=re.search(r'} const pick_chars_def\[\] = \{(.*?)\};',clean,re.S)[1]
 else:c=re.search(r'static const int mMoOdDxX_def\[\] = \{(.*?)\};',clean,re.S)[1]
 j=re.search(r'const '+name+r' = (\[.*?\]);',core,re.S)[1]
 assert re.findall(r'\b(?:NHKF_\w+|LOOK_\w+)\b',c)==re.findall(r'\b(?:NHKF_\w+|LOOK_\w+)\b',j),('Changed original key map',name);tables.append(name)
assert len(tables)==7,tables
private=re.findall(r'\bstaticfn\s+(?:int QSORTCALLBACK|\w+)\s+(\w+)\([^;]+\)\s*\{',clean)
assert len(private)==14
aliases=set(re.findall(r'teleport_getpos_test_(\w+)__deps',library))
assert aliases==set(private)-{'cmp_coord_distu','gloc_filter_floodfill_matcharea'}
for name in ['cmp_coord_distu','gloc_filter_floodfill_matcharea']:
 assert 'teleport_getpos_'+name+'__deps' in library and 'teleport_getpos_'+name in support
assert 'static char buf[30]' in clean and 'static char screen_fmt[16]' in clean
assert 'teleport_getpos_buf[30],teleport_getpos_screen_fmt[16]' in support
assert '...source.getpos_initial_state' in runtime and 'moduleKey:Module' in library
assert 'getpos_hilitefunc: 0n, getpos_getvalid: 0n, getpos_hilite_state: HiliteNormalMap, defaultHiliteState: HiliteNormalMap' in core
assert not re.search(r'\b(?:rn2|rn1|rnd|d)\(',clean),'Review newly added GETPOS RNG sites'
for name in ['IS_UNEXPLORED_LOC','GLOC_SAME_AREA']:assert 'const '+name+' = ' in core,'Original TU macros stay source-owned JS'
# Actual CPP resolves multiline Snprintf invocations to closing lines280/705.
defines=json.loads((root/'nethack-c/wasm/compile-defines.json').read_text());src=root/'.cache/wasm64-build/tree/src/getpos.c'
cpp=subprocess.check_output([str(root/'.cache/emsdk/upstream/emscripten/emcc'),'-E','-sMEMORY64=1',*[f'-D{x}' for x in defines],'-I'+str(root/'.cache/wasm64-build/tree/include'),str(src)],text=True)
actual=[int(x) for x in re.findall(r'nh_snprintf\(__func__,\s*(\d+),',cpp)]
assert actual==[280,705],('Review changed configured Snprintf origin',actual)
assert re.findall(r'C\.Snprintf\("\w+",\s*(\d+)',core)==list(map(str,actual))
# The configured reference includes the accepted inherited deterministic sort.
header=(root/'.cache/wasm64-build/tree/include/hack.h').read_text();hacklib=(root/'.cache/wasm64-build/tree/src/hacklib.c').read_text()
assert '#define qsort(base, nmemb, size, compar)' in header and 'nh_deterministic_qsort((base), (nmemb), (size), (compar))' in header
assert 'nh_deterministic_qsort(void *base' in hacklib and 'qsort((void *) order' in hacklib
assert 'C.stackRestore(automatic_scope)' in core,'Original per-iteration automatic lifetime must be preserved'
print(f'GETPOS metadata:22 functions/14private,7 readonly tables,{len(literals)} source strings/{capacity} bytes,zero RNG sites,actual CPP origins280/705 and inherited sort provenance verified.')
