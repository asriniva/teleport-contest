from pathlib import Path
import subprocess,json,argparse,hashlib
parser=argparse.ArgumentParser()
parser.add_argument('--out',required=True,type=Path)
parser.add_argument('--source-root',type=Path)
args=parser.parse_args()
code_root=Path(__file__).resolve().parents[1]
r=(args.source_root or code_root).resolve()
w=args.out.resolve()
if w.exists():parser.error('--out must not exist')
w.mkdir(parents=True)
native=code_root/'nethack-c/wasm/utilities/ppmwrite'
source=r/'nethack-c/upstream/win/share/ppmwrite.c'
if not source.is_file():raise SystemExit('Missing original source; use --source-root')
profile=['-DNOTPARMDECL','-DNO_TIMED_DELAY','-I'+str(r/'.cache/wasm64-build/tree/include'),'-I'+str(r/'nethack-c/upstream/win/share')]
emcc=r/'.cache/emsdk/upstream/emscripten/emcc'
jsifier=r/'.cache/emsdk/upstream/emscripten/src/jsifier.mjs'
(w/'sdk-jsifier-sha256.txt').write_text(hashlib.sha256(jsifier.read_bytes()).hexdigest()+'\n')
inventory_cmd=[str(emcc),'-O2','-sMEMORY64=1',*profile,'-Xclang','-ast-dump=json','-fsyntax-only',str(source)]
with(w/'compiler-ast.json').open('w')as out,(w/'inventory.log').open('w')as err:status=subprocess.run(inventory_cmd,stdout=out,stderr=err)
(w/'inventory-command.json').write_text(json.dumps({'argv':inventory_cmd,'actualExit':status.returncode},indent=2)+'\n')
if status.returncode:raise SystemExit(status.returncode)
ast=json.loads((w/'compiler-ast.json').read_text());functions=[]
for n in ast['inner']:
 if n.get('kind')=='FunctionDecl'and n['name']!='__isspace'and any(i.get('kind')=='CompoundStmt'for i in n.get('inner',[])):
  functions.append({'name':n['name'],'parameters':[{'name':i['name']}for i in n['inner']if i.get('kind')=='ParmVarDecl']})
(w/'configured-functions.json').write_text(json.dumps(functions,indent=2)+'\n')
inc=profile+['-DUTILITY_PPMWRITE_REFERENCE_SOURCE=\"'+str(source)+'\"'];commands=[]
files=['win/share/tiletext.c','win/share/tiletxt.c','src/drawing.c','src/monst.c','src/objects.c','src/alloc.c','util/panic.c','src/hacklib.c'];objs=[]
for file in files:
 obj=w/(Path(file).stem+'.o');cmd=[str(emcc),'-O2','-sMEMORY64=1',*inc,'-c',str(r/'nethack-c/upstream'/file),'-o',str(obj)];res=subprocess.run(cmd,stdout=(w/(Path(file).stem+'-build.log')).open('w'),stderr=subprocess.STDOUT);commands.append({'args':cmd,'exit':res.returncode});assert res.returncode==0,file;objs.append(str(obj))
exports=['probe_prepare','probe_open','probe_fill','probe_write','probe_close','probe_main','probe_stack','teleport_ppm_metadata','teleport_ppm_allocations','teleport_ppm_frees','teleport_ppm_alloc_size','teleport_ppm_free_id','probe_flush','probe_grow']
for mode in ['reference','hybrid']:
 cmd=[str(emcc),'-O2','-sMEMORY64=1','-sMODULARIZE=1','-sENVIRONMENT=node','-sEXIT_RUNTIME=1','-sALLOW_MEMORY_GROWTH=1','-sINITIAL_MEMORY=4194304','-sSTACK_SIZE=131072','--no-entry','-sEXPORTED_RUNTIME_METHODS=FS,HEAPU8','-sEXPORTED_FUNCTIONS='+','.join('_'+x for x in exports),*inc,str(native/'probe.c'),str(native/'transport.c'),str(native/'test-alloc.c'),*objs,*(['-DPPM_REFERENCE']if mode=='reference'else['--js-library',str(native/'library.js')]),'-o',str(w/(mode+'.mjs'))];res=subprocess.run(cmd,stdout=(w/(mode+'-build.log')).open('w'),stderr=subprocess.STDOUT);commands.append({'args':cmd,'exit':res.returncode});(w/'build-commands.json').write_text(json.dumps(commands,indent=2)+'\n');assert res.returncode==0,mode
print('Actual original+hybrid memory64 pair PASS')
