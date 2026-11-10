"""Unique isolated MKLEV original/hybrid build, no shared registry changes."""
from pathlib import Path
import subprocess,json,hashlib
r=Path(__file__).resolve().parents[1];w=r/'.cache/mklev-first-pass';w.mkdir(exist_ok=True,parents=True)
base=[str(r/'.cache/emsdk/upstream/emscripten/emcc'),'-O2','-g','-I../include',*['-D'+d for d in json.loads((r/'nethack-c/wasm/compile-defines.json').read_text())],'-sMEMORY64=1','-I'+str(r/'.cache/ncurses-wasm64-build/include'),'-include',str(r/'nethack-c/wasm/native-terminal.h')]
h=(r/'.cache/wasm64-build/tree/src/hacklib.c').read_text();prefix=h[:h.index('/*=')];dep=w/'deterministic-sort-dependency.c';dep.write_text(prefix)
(w/'sort-dependency-provenance.json').write_text(json.dumps({'sourceSHA256':hashlib.sha256(h.encode()).hexdigest(),'prefixSHA256':hashlib.sha256(prefix.encode()).hexdigest(),'purpose':'actual configured external deterministic qsort, not a MKLEV fallback'},indent=2)+'\n')
exports=['action','trace','clear','draws','error','seed','option','pointer','coord','map','grid','count','alloc_pointer','alloc_size','reset','growth','region_size','global_size','identity','pointer_offset','constant','alloc_kind']
symbols=['_probe_'+n for n in exports]+['_teleport_mklev_'+n for n in ['global','read','write','address','layout','storage']]
base+=['-Wl,--wrap=malloc','-Wl,--wrap=free','-fmacro-prefix-map='+str(r/'.cache/wasm64-build/tree/src')+'/=','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sSTACK_SIZE=4194304','--no-entry','-sEXPORTED_RUNTIME_METHODS='+json.dumps(['HEAPU8','stringToUTF8','lengthBytesUTF8','stackSave','stackRestore','stackAlloc','UTF8ToString']),'-sEXPORTED_FUNCTIONS='+json.dumps(symbols),str(r/'scripts/tu-mklev-probe.c'),str(r/'nethack-c/wasm/tu-fragments/mklev-support.c'),str(dep)]
for mode in ['reference','hybrid']:
 extra=['-DHYBRID_MKLEV=1','--js-library',str(r/'nethack-c/wasm/tu-libraries/mklev.js')]if mode=='hybrid'else[]
 p=subprocess.run(base+extra+['-o',str(w/('mklev-'+mode+'.mjs'))],cwd=r/'.cache/wasm64-build/tree/src',capture_output=True,text=True);(w/('build-'+mode+'.log')).write_text(p.stdout+p.stderr);print(mode,p.returncode,(p.stdout+p.stderr)[-15000:])
 if p.returncode:raise SystemExit(p.returncode)
