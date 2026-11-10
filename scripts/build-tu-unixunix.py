"""Unique UNIXUNIX actual original/imported-JS links, separate optimized reader."""
from pathlib import Path
import subprocess,json
r=Path(__file__).resolve().parents[1];w=r/'.cache/unixunix-first-pass';w.mkdir(exist_ok=True,parents=True)
base=[str(r/'.cache/emsdk/upstream/emscripten/emcc'),'-O2','-g','-I../include',*['-D'+d for d in json.loads((r/'nethack-c/wasm/compile-defines.json').read_text())],'-sMEMORY64=1','-I'+str(r/'.cache/ncurses-wasm64-build/include'),'-include',str(r/'nethack-c/wasm/native-terminal.h')]
exports=['action','trace','clear','outcome','errno','option','option_get','now','answer','char','file','open','file_count','fd_count','fd_open','event_count','handler','done_id','handler_raw','signal_run','growth','reset','pointer','region_size','global_size','sourcebuf']
symbols=['_probe_'+n for n in exports]+['_teleport_unixunix_'+n for n in ['global','read','write','address','layout','storage']]
base+=['-fmacro-prefix-map='+str(r/'.cache/wasm64-build/tree/sys/unix')+'/=../sys/unix/','-sTABLE_BASE=2','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sSTACK_SIZE=4194304','--no-entry','-sEXPORTED_RUNTIME_METHODS='+json.dumps(['HEAPU8','stringToUTF8','lengthBytesUTF8','stackSave','stackRestore','stackAlloc','UTF8ToString']),'-sEXPORTED_FUNCTIONS='+json.dumps(symbols),str(r/'scripts/tu-unixunix-probe.c'),str(r/'nethack-c/wasm/tu-fragments/unixunix-support.c')]
for mode in ['reference','hybrid']:
 extra=['-DHYBRID_UNIXUNIX=1','--js-library',str(r/'nethack-c/wasm/tu-libraries/unixunix.js')]if mode=='hybrid'else['-DREFERENCE_UNIXUNIX=1']
 command=base+extra+['-o',str(w/('unixunix-'+mode+'.mjs'))]
 (w/('link-command-'+mode+'.json')).write_text(json.dumps({'cwd':str(r/'.cache/wasm64-build/tree/src'),'args':command},indent=2)+'\n')
 p=subprocess.run(command,cwd=r/'.cache/wasm64-build/tree/src',capture_output=True,text=True);(w/('build-'+mode+'.log')).write_text(p.stdout+p.stderr);print(mode,p.returncode,(p.stdout+p.stderr)[-15000:])
 if p.returncode:raise SystemExit(p.returncode)
