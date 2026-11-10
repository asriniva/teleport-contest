"""Unique PICKUP actual original/imported-JS links, separate optimized reader."""
from pathlib import Path
import subprocess,json
r=Path(__file__).resolve().parents[1];w=r/'.cache/pickup-first-pass';w.mkdir(exist_ok=True,parents=True)
base=[str(r/'.cache/emsdk/upstream/emscripten/emcc'),'-O2','-g','-I../include',*['-D'+d for d in json.loads((r/'nethack-c/wasm/compile-defines.json').read_text())],'-sMEMORY64=1','-I'+str(r/'.cache/ncurses-wasm64-build/include'),'-include',str(r/'nethack-c/wasm/native-terminal.h')]
exports=['action','trace','clear','draws','error','errno','seed','option','input','answer','choice','pointer','grid','region_size','count','alloc_pointer','alloc_size','alloc_kind','alloc_live','growth','event_count','event_kind','newobj','floor','inventory','reset','global_size','constant','identity','queue_count','queue_identity','queue_run','literal','prefix','extra_offset','borrow_count','borrow_pointer','borrow_kind','choice2','choicewide']
symbols=['_probe_'+n for n in exports]+['_teleport_pickup_'+n for n in ['global','read','write','address','layout','storage']]
base+=['-Wl,--wrap=malloc','-Wl,--wrap=free','-fmacro-prefix-map='+str(r/'.cache/wasm64-build/tree/src')+'/=','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sSTACK_SIZE=4194304','--no-entry','-sEXPORTED_RUNTIME_METHODS='+json.dumps(['HEAPU8','stringToUTF8','lengthBytesUTF8','stackSave','stackRestore','stackAlloc','UTF8ToString']),'-sEXPORTED_FUNCTIONS='+json.dumps(symbols),str(r/'scripts/tu-pickup-probe.c'),str(r/'nethack-c/wasm/tu-fragments/pickup-support.c')]
for mode in ['reference','hybrid']:
 extra=['-DHYBRID_PICKUP=1','--js-library',str(r/'nethack-c/wasm/tu-libraries/pickup.js')]if mode=='hybrid'else['-DREFERENCE_PICKUP=1']
 p=subprocess.run(base+extra+['-o',str(w/('pickup-'+mode+'.mjs'))],cwd=r/'.cache/wasm64-build/tree/src',capture_output=True,text=True);(w/('build-'+mode+'.log')).write_text(p.stdout+p.stderr);print(mode,p.returncode,(p.stdout+p.stderr)[-15000:])
 if p.returncode:raise SystemExit(p.returncode)
