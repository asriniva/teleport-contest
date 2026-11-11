from pathlib import Path
import subprocess,json
import argparse
args_parser=argparse.ArgumentParser()
args_parser.add_argument('--out',required=True)
args_parser.add_argument('--source-root',type=Path)
args=args_parser.parse_args()
code_root=Path(__file__).resolve().parents[1]
r=(args.source_root or code_root).resolve()
w=Path(args.out).resolve()
if w.exists():raise SystemExit('Refusing existing output directory: '+str(w))
w.mkdir(parents=True)
native=code_root/'nethack-c/wasm/utilities/dlb-main'
original=r/'nethack-c/upstream/util/dlb_main.c'
if not original.is_file():raise SystemExit('Original source missing; supply --source-root real repository')
exports=['utility_free','utility_stats','utility_main','utility_private','fopen_datafile','utility_layout','utility_offset','utility_open','utility_read','utility_write','utility_printf_s','utility_printf_sll','utility_printf_lll','utility_sprintf_header','utility_sprintf_entry','utility_fopen','utility_fgets','utility_fread','utility_fseek','utility_fclose','utility_exit','utility_malloc','alloc','dupstr','strlen','eos','strcmp','close','lseek','chdir','open_library','close_library'];commands=[];results=[]
inventory_cmd=[str(r/'.cache/emsdk/upstream/emscripten/emcc'),'-O2','-g','-sMEMORY64=1','-DNOTPARMDECL','-DNO_TIMED_DELAY','-DDLB','-DDLBLIB=','-I'+str(r/'.cache/wasm64-build/tree/include'),'-I'+str(r/'.cache/ncurses-wasm64-build/include'),'-Xclang','-ast-dump=json','-fsyntax-only',str(original)]
with(w/'original.ast.json').open('w')as out,(w/'inventory.log').open('w')as err:status=subprocess.run(inventory_cmd,stdout=out,stderr=err)
if status.returncode:raise SystemExit(status.returncode)
(w/'inventory-command.json').write_text(json.dumps({'argv':inventory_cmd,'actualExit':status.returncode},indent=2)+'\n')
rows=[]
for n in json.loads((w/'original.ast.json').read_text())['inner']:
 if n.get('kind')=='FunctionDecl'and any(i.get('kind')=='CompoundStmt'for i in n.get('inner',[])):
  rows.append({'name':n['name'],'type':n['type']['qualType'],'variadic':n.get('variadic',False),'parameters':[i['name']for i in n['inner']if i.get('kind')=='ParmVarDecl']})
(w/'inventory.json').write_text(json.dumps(rows,indent=2)+'\n')
for mode in ['reference','hybrid']:
 cmd=[str(r/'.cache/emsdk/upstream/emscripten/emcc'),'-O2','-g','-sMEMORY64=1','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','--no-entry','-sEXPORTED_RUNTIME_METHODS=FS,HEAPU8,stringToUTF8,lengthBytesUTF8,UTF8ToString,stackSave,stackRestore,stackAlloc','-sEXPORTED_FUNCTIONS='+','.join('_'+x for x in exports),'-DUTILITY_DLB_MAIN_REFERENCE_SOURCE=\"'+str(original)+'\"','-DNOTPARMDECL','-DNO_TIMED_DELAY','-DDLB','-DDLBLIB=','-Wl,--wrap=malloc','-Wl,--wrap=free','-I'+str(r/'.cache/wasm64-build/tree/include'),'-I'+str(r/'.cache/ncurses-wasm64-build/include'),'-I'+str(r/'.cache/wasm64-build/tree/lib/lua'),str(native/'support.c'),str(r/'nethack-c/upstream/src/dlb.c'),str(r/'nethack-c/upstream/src/alloc.c'),str(r/'nethack-c/upstream/util/panic.c'),str(r/'nethack-c/upstream/src/hacklib.c')]
 if mode=='reference':cmd+=['-DREFERENCE_DLB_MAIN']
 else:cmd+=['--js-library',str(native/'library.js')]
 cmd+=['-o',str(w/(mode+'.mjs'))];commands.append(cmd);(w/'build-commands.json').write_text(json.dumps(commands,indent=2)+'\n')
 with(w/(mode+'-build.log')).open('w')as f:p=subprocess.run(cmd,stdout=f,stderr=subprocess.STDOUT)
 results.append({'mode':mode,'exit':p.returncode});(w/'build-results.json').write_text(json.dumps(results,indent=2)+'\n');print(mode,p.returncode,flush=True)
 if p.returncode:raise SystemExit(p.returncode)
