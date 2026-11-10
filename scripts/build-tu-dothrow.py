"""Unique isolated DOTHROW original/hybrid build, no shared registry changes."""
from pathlib import Path
import subprocess,json,hashlib
r=Path(__file__).resolve().parents[1];w=r/'.cache/dothrow-first-pass';w.mkdir(exist_ok=True,parents=True)
base=[str(r/'.cache/emsdk/upstream/emscripten/emcc'),'-O2','-g','-I../include',*['-D'+d for d in json.loads((r/'nethack-c/wasm/compile-defines.json').read_text())],'-sMEMORY64=1','-I'+str(r/'.cache/ncurses-wasm64-build/include'),'-include',str(r/'nethack-c/wasm/native-terminal.h')]
exports=['action','trace','clear','draws','error','errno','seed','option','pointer','coord','map','grid','count','alloc_pointer','alloc_size','reset','growth','global_size','identity','pointer_offset','constant','queue_count','queue_identity','queue_run','source_literal']
symbols=['_probe_'+n for n in exports]+['_teleport_dothrow_'+n for n in ['global','read','write','address','layout','storage']]
base+=['-Wl,--wrap=malloc','-Wl,--wrap=free','-fmacro-prefix-map='+str(r/'.cache/wasm64-build/tree/src')+'/=','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sSTACK_SIZE=4194304','--no-entry','-sEXPORTED_RUNTIME_METHODS='+json.dumps(['HEAPU8','stringToUTF8','lengthBytesUTF8','stackSave','stackRestore','stackAlloc','UTF8ToString']),'-sEXPORTED_FUNCTIONS='+json.dumps(symbols),str(r/'scripts/tu-dothrow-probe.c'),str(r/'nethack-c/wasm/tu-fragments/dothrow-support.c')]
for mode in ['reference','hybrid']:
 extra=['-DHYBRID_DOTHROW=1','--js-library',str(r/'nethack-c/wasm/tu-libraries/dothrow.js')]if mode=='hybrid'else[]
 p=subprocess.run(base+extra+['-o',str(w/('dothrow-'+mode+'.mjs'))],cwd=r/'.cache/wasm64-build/tree/src',capture_output=True,text=True);(w/('build-'+mode+'.log')).write_text(p.stdout+p.stderr);print(mode,p.returncode,(p.stdout+p.stderr)[-15000:])
 if p.returncode:raise SystemExit(p.returncode)
