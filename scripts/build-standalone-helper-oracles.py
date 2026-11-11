#!/usr/bin/env python3
"""Build unchanged C field helpers as development oracles with owned scratch."""
import argparse,json,subprocess
from pathlib import Path
parser=argparse.ArgumentParser()
parser.add_argument('--reference-root',type=Path,required=True)
parser.add_argument('--out',type=Path,required=True)
args=parser.parse_args()
root=Path(__file__).resolve().parents[1]
reference=args.reference_root.resolve()
out=args.out.resolve()
if out.exists():raise SystemExit('Use a fresh helper-oracle output directory')
out.mkdir(parents=True)
sdk=reference/'.cache/emsdk'
flags=['-O2','-sMEMORY64=1','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','--no-entry','-sEXPORTED_RUNTIME_METHODS=HEAPU8',
       *['-D'+d for d in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())],
       '-I'+str(reference/'.cache/wasm64-build/tree/include'),'-I'+str(reference/'.cache/wasm64-build/tree/lib/lua-5.4.8/src'),
       '-I'+str(reference/'.cache/ncurses-wasm64-build/include'),'-I'+str(reference/'.cache/tu-probes')]
for name in json.loads((root/'js/standalone/address-ports.json').read_text())['ports']:
    exports=['_malloc','_free',*['_teleport_'+name+'_'+suffix for suffix in ['read','write','address']]]
    cmd=[str(sdk/'upstream/emscripten/emcc'),*flags,'-sEXPORTED_FUNCTIONS='+json.dumps(exports),
         str(root/f'nethack-c/wasm/tu-fragments/{name}-support.c'),'-o',str(out/f'{name}-reference.mjs')]
    result=subprocess.run(cmd,capture_output=True,text=True)
    (out/f'{name}.log').write_text(result.stdout+result.stderr)
    if result.returncode:raise SystemExit(f'{name} helper oracle failed: {result.stderr[-2000:]}')
    print(name+' helper oracle built',flush=True)
