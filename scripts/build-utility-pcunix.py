from pathlib import Path
import argparse,subprocess,json,hashlib
p=argparse.ArgumentParser();p.add_argument('--out',type=Path,required=True);p.add_argument('--source-root',type=Path,required=True);a=p.parse_args();w=a.out.resolve();r=a.source_root.resolve();code=Path(__file__).resolve().parents[1];native=code/'nethack-c/wasm/utilities/pcunix'
if w.exists():p.error('--out must not exist')
w.mkdir(parents=True);emcc=r/'.cache/emsdk/upstream/emscripten/emcc';source=r/'nethack-c/upstream/sys/share/pcunix.c';profile=['-O2','-g','-sMEMORY64=1','-DNOTPARMDECL','-DNO_TIMED_DELAY','-I'+str(r/'.cache/wasm64-build/tree/include'),'-I'+str(r/'.cache/ncurses-wasm64-build/include')];rows=[]
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();inputs=[source,native/'probe.c',native/'library.js',code/'js/ported-utilities/pcunix.js',code/'js/ported-utilities/pcunix-runtime.js',code/'js/ported-utilities/pcunix-scope.js',Path(__file__).resolve(),r/'.cache/emsdk/upstream/emscripten/src/jsifier.mjs']+sorted((r/'.cache/wasm64-build/tree/include').glob('*.h'))+sorted((r/'.cache/ncurses-wasm64-build/include').glob('*.h'));before={str(f):sha(f)for f in inputs};(w/'inputs-before.json').write_text(json.dumps(before,indent=2)+'\n')
def run(label,cmd,output=None):
 with(w/(label+'.log')).open('w')as log:
  if output:
   with output.open('w')as out:q=subprocess.run(cmd,stdout=out,stderr=log)
  else:q=subprocess.run(cmd,stdout=log,stderr=subprocess.STDOUT)
 rows.append({'label':label,'argv':cmd,'actualExit':q.returncode});(w/'commands.json').write_text(json.dumps(rows,indent=2)+'\n')
 if q.returncode:raise SystemExit(q.returncode)
for mode in ['reference','hybrid']:
 cmd=[str(emcc),*profile,'-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','--no-entry','-sEXPORTED_RUNTIME_METHODS=HEAP8,HEAPU8','-sEXPORTED_FUNCTIONS=_probe_call,_probe_char_signed,_probe_profile,_malloc,_free',str(native/'probe.c')]
 cmd+=[str(source)]if mode=='reference'else['--js-library',str(native/'library.js')]
 run(mode,cmd+['-o',str(w/(mode+'.mjs'))])
after={f:sha(Path(f))for f in before};assert before==after;(w/'inputs-after.json').write_text(json.dumps(after,indent=2)+'\n');print('PASS actual original/mixed PCUNIX pair')
