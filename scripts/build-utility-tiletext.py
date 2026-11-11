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
native=code_root/'nethack-c/wasm/utilities/tiletext'
source=r/'nethack-c/upstream/win/share/tiletext.c'
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
readonly={}
for n in ast['inner']:
 if n.get('kind')=='VarDecl'and n.get('name')in['graymappings','text_sets']:
  values=[]
  def collect(x):
   if x.get('kind')in['IntegerLiteral','StringLiteral']:values.append(x['value'])
   for child in x.get('inner',[]):collect(child)
  collect(n);readonly[n['name']]=values
(w/'readonly-data.json').write_text(json.dumps(readonly,indent=2)+'\n')
exports=['utility_tile_foreign_read','utility_tile_state','set_grayscale','fopen_text_file','read_text_tile','write_text_tile','fclose_text_file','init_colormap','merge_colormap','utility_tile_storage','utility_tile_layout','utility_tile_private','utility_tile_name_count','utility_tile_name_value','utility_tile_fopen','utility_tile_stderr','utility_tile_fgetc','utility_tile_ungetc','utility_tile_fgets','utility_tile_fputc','utility_tile_fclose','utility_tile_scan_palette','utility_tile_scan_tile','utility_tile_print','utility_tile_dependency_init','utility_tilename','acceptable_tilename','malloc','free','strncmp','strcmp','strstr','strchr','strrchr','strlen','memcmp'];commands=[];results=[]
for mode in ['reference','hybrid']:
 cmd=[str(r/'.cache/emsdk/upstream/emscripten/emcc'),'-O2','-g','-sMEMORY64=1','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','--no-entry','-sEXPORTED_RUNTIME_METHODS=FS,HEAPU8,stringToUTF8,lengthBytesUTF8,UTF8ToString,stackSave,stackRestore,stackAlloc','-sEXPORTED_FUNCTIONS='+','.join('_'+x for x in exports),'-DNOTPARMDECL','-DNO_TIMED_DELAY','-DUTILITY_TILETEXT_REFERENCE_SOURCE="'+str(r/'nethack-c/upstream/win/share/tiletext.c')+'"','-I'+str(r/'.cache/wasm64-build/tree/include'),'-I'+str(r/'.cache/ncurses-wasm64-build/include'),'-I'+str(r/'nethack-c/upstream/win/share'),'-I'+str(r/'.cache/wasm64-build/tree/lib/lua'),str(native/'support.c'),str(native/'test-foreign.c'),*[str(r/'nethack-c/upstream'/p)for p in ['win/share/tiletxt.c','src/drawing.c','src/monst.c','src/objects.c','src/alloc.c','util/panic.c','src/hacklib.c']]]
 if mode=='reference':cmd+=['-DREFERENCE_TILETEXT']
 else:cmd+=['--js-library',str(native/'library.js')]
 cmd+=['-o',str(w/(mode+'.mjs'))];commands.append(cmd);(w/'build-commands.json').write_text(json.dumps(commands,indent=2)+'\n')
 with(w/(mode+'-build.log')).open('w')as f:p=subprocess.run(cmd,stdout=f,stderr=subprocess.STDOUT)
 results.append({'mode':mode,'actualExit':p.returncode});(w/'build-results.json').write_text(json.dumps(results,indent=2)+'\n');print(mode,p.returncode,flush=True)
 if p.returncode:raise SystemExit(p.returncode)
