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
native=code_root/'nethack-c/wasm/utilities/thintile'
source=r/'nethack-c/upstream/win/share/thintile.c'
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
exports=['malloc','free','probe_run','thin_storage','thin_layout','thin_mode','thin_stderr','thin_fopen','thin_fclose','thin_scan4','thin_scan3','thin_scan1','thin_print0','thin_printp','thin_print4','thin_printf1','thin_printf2','thin_sprintf','thin_fputc','thin_exit']
base=[str(r/'.cache/emsdk/upstream/emscripten/emcc'),'-O2','-g','-DUTILITY_THINTILE_REFERENCE_SOURCE=\"'+str(source)+'\"','-DNOTPARMDECL','-DNO_TIMED_DELAY','-sMEMORY64=1','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sSTACK_SIZE=4194304','--no-entry','-sFORCE_FILESYSTEM=1','-sEXIT_RUNTIME=1','-sEXPORTED_RUNTIME_METHODS='+json.dumps(['HEAPU8','FS','stackSave','stackRestore','stackAlloc']),'-sEXPORTED_FUNCTIONS='+json.dumps(['_'+s for s in exports]),'-I'+str(r/'.cache/wasm64-build/tree/include'),'-I'+str(r/'nethack-c/upstream/win/share'),'-ffile-prefix-map='+str(r/'nethack-c/upstream/win/share')+'/=',str(native/'probe.c'),str(native/'support.c')]
rows=[]
for mode in ['reference','hybrid']:
 cmd=base+(['-DMIXED_THIN','--js-library',str(native/'library.js')]if mode=='hybrid'else[])+['-o',str(w/(mode+'.mjs'))];row={'mode':mode,'command':cmd};rows.append(row);(w/'commands.json').write_text(json.dumps(rows,indent=2)+'\n')
 with(w/(mode+'-build.log')).open('w')as log:z=subprocess.run(cmd,stdout=log,stderr=subprocess.STDOUT)
 row['exit']=z.returncode;(w/'commands.json').write_text(json.dumps(rows,indent=2)+'\n')
 if z.returncode:raise SystemExit(z.returncode)
