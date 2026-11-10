"""Unique DISPLAY actual original/imported-JS links, separate optimized reader."""
from pathlib import Path
import subprocess,json
r=Path(__file__).resolve().parents[1];w=r/'.cache/display-first-pass';w.mkdir(exist_ok=True,parents=True)
base=[str(r/'.cache/emsdk/upstream/emscripten/emcc'),'-O2','-g','-I../include',*['-D'+d for d in json.loads((r/'nethack-c/wasm/compile-defines.json').read_text())],'-sMEMORY64=1','-I'+str(r/'.cache/ncurses-wasm64-build/include'),'-include',str(r/'nethack-c/wasm/native-terminal.h')]
exports=['action','trace','clear','draws','error','errno','seed','option','pointer','grid','map','count','alloc_pointer','alloc_size','alloc_live','growth','startup','startup_size','startup_calls','coord','coord_call','wallcolor','reset','global_size','region_size','alloc','public_size','private','private_size','glyph_events']
symbols=['_probe_'+n for n in exports]+['_teleport_display_'+n for n in ['global','read','write','address','layout','storage','dep_do_screen_description']]
base+=['-Wl,--wrap=malloc','-Wl,--wrap=free','-fmacro-prefix-map='+str(r/'.cache/wasm64-build/tree/src')+'/=','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sSTACK_SIZE=4194304','--no-entry','-sEXPORTED_RUNTIME_METHODS='+json.dumps(['HEAPU8','stringToUTF8','lengthBytesUTF8','stackSave','stackRestore','stackAlloc','UTF8ToString']),'-sEXPORTED_FUNCTIONS='+json.dumps(symbols),str(r/'scripts/tu-display-probe.c'),str(r/'nethack-c/wasm/tu-fragments/display-support.c'),str(w/'early-reader.c')]
for mode in ['reference','hybrid']:
 extra=[str(r/'nethack-c/wasm/tu-fragments/display-storage.c'),'-DHYBRID_DISPLAY=1','--js-library',str(r/'nethack-c/wasm/tu-libraries/display.js')]if mode=='hybrid'else['-DREFERENCE_DISPLAY=1']
 p=subprocess.run(base+extra+['-o',str(w/('display-'+mode+'.mjs'))],cwd=r/'.cache/wasm64-build/tree/src',capture_output=True,text=True);(w/('build-'+mode+'.log')).write_text(p.stdout+p.stderr);print(mode,p.returncode,(p.stdout+p.stderr)[-15000:])
 if p.returncode:raise SystemExit(p.returncode)
