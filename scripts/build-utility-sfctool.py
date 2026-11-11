"""Fresh isolated original-C/mixed-JS SFCTOOL pair; never writes the source tree."""
from pathlib import Path
import argparse,subprocess,json,hashlib,re
p=argparse.ArgumentParser();p.add_argument('--out',required=True,type=Path);p.add_argument('--source-root',type=Path);p.add_argument('--metadata-root',required=True,type=Path);p.add_argument('--test-observers',action='store_true',help='Enable bounded allocation-ID observation only for paired tests');a=p.parse_args()
code=Path(__file__).resolve().parents[1];r=(a.source_root or code).resolve();w=a.out.resolve();meta=a.metadata_root.resolve()
if w.exists():p.error('--out must not exist')
for x in ['sfdata.c','sfproto.h']:assert(meta/x).is_file(),x
w.mkdir(parents=True);native=code/'nethack-c/wasm/utilities/sfctool';source=r/'nethack-c/upstream/util/sfctool.c';emcc=r/'.cache/emsdk/upstream/emscripten/emcc';sha=lambda f:hashlib.sha256(f.read_bytes()).hexdigest();rows=[]
profile=['-O2','-g','-sMEMORY64=1','-DNOTPARMDECL','-DNO_TIMED_DELAY','-DSFCTOOL','-DNOPANICTRACE','-DNOCRASHREPORT','-DNO_CHRONICLE','-I'+str(meta),'-I'+str(r/'.cache/wasm64-build/tree/include'),'-I'+str(r/'.cache/ncurses-wasm64-build/include')]
def run(label,cmd,output=None):
 with(w/(label+'.log')).open('w')as log:
  if output:
   with output.open('w')as out:status=subprocess.run(cmd,stdout=out,stderr=log)
  else:status=subprocess.run(cmd,stdout=log,stderr=subprocess.STDOUT)
 rows.append({'label':label,'argv':cmd,'actualExit':status.returncode});(w/'commands.json').write_text(json.dumps(rows,indent=2)+'\n')
 if status.returncode:raise SystemExit(status.returncode)
run('inventory',[str(emcc),*profile,'-Xclang','-ast-dump=json','-fsyntax-only',str(source)],w/'compiler-ast.json')
ast=json.loads((w/'compiler-ast.json').read_text());functions=[{'name':n['name'],'line':n['loc'].get('line'),'parameters':[v['name']for v in n.get('inner',[])if v.get('kind')=='ParmVarDecl']}for n in ast['inner']if n.get('kind')=='FunctionDecl'and not n.get('loc',{}).get('includedFrom')and any(v.get('kind')=='CompoundStmt'for v in n.get('inner',[]))];assert len(functions)==50
(w/'inventory.json').write_text(json.dumps(functions,indent=2)+'\n')
files=['src/'+x+'.c'for x in ['alloc','cfgfiles','date','artifact','calendar','decl','dungeon','end','engrave','files','light','mdlib','mkmaze','mkroom','monst','nhlua','objects','o_init','region','restore','rumors','sfbase','sfstruct','strutil','sys','timeout','track','version','worm','hacklib']]+['util/panic.c','util/sfexpasc.c']
inputs=[r/'nethack-c/upstream'/x for x in files]+[source,meta/'sfdata.c',meta/'sfproto.h'];inputs+=sorted((r/'.cache/wasm64-build/tree/include').glob('*.h'));inputs+=list(native.glob('*'));inputs+=list((code/'js/ported-utilities').glob('sfctool*'));inputs+=[r/'.cache/emsdk/upstream/emscripten/src/jsifier.mjs',Path(__file__).resolve()]
before={str(x):sha(x)for x in inputs if x.is_file()};(w/'input-hashes-before.json').write_text(json.dumps(before,indent=2)+'\n')
objects=[]
for i,f in enumerate(inputs[:len(files)]+[meta/'sfdata.c']):
 obj=w/(f.stem+'.o');run('dependency-'+str(i),[str(emcc),*profile,'-c',str(f),'-o',str(obj)]);objects.append(str(obj))
exports=(['utility_log','utility_allocation']if a.test_observers else[])+sorted(set(re.findall(r'\b(utility_\w+)\([^;{}]*\)\s*\{',(native/'probe-transport.c').read_text())))+['malloc','free']
for mode in ['reference','hybrid']:
 cmd=[str(emcc),*profile,'-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','--no-entry','-sFORCE_FILESYSTEM=1','-sEXPORTED_RUNTIME_METHODS=FS,HEAPU8,stringToUTF8,lengthBytesUTF8,UTF8ToString,stackSave,stackRestore,stackAlloc','-sEXPORTED_FUNCTIONS='+','.join('_'+x for x in exports),'-DUTILITY_SFCTOOL_SOURCE="'+str(source)+'"',str(native/'probe-transport.c'),*(['-DUTILITY_SFCTOOL_TEST_OBSERVERS',str(native/'test-observer.c')]if a.test_observers else[]),*objects]
 cmd+=['-DREFERENCE_SFCTOOL']if mode=='reference'else['--js-library',str(native/'library.js')]
 run(mode,cmd+['-o',str(w/(mode+'-full.mjs'))])
after={x:sha(Path(x))for x in before};assert before==after,'source/tool inputs changed during build';(w/'input-hashes-after.json').write_text(json.dumps(after,indent=2)+'\n');(w/'build-result.json').write_text(json.dumps({'status':'PASS','configuredFunctions':50,'actualOriginalAndMixed':True,'sourceRoot':str(r),'metadataRoot':str(meta),'compiler':'Emscripten4.0.10/Clang21/MEMORY64','jsifierSha256':sha(r/'.cache/emsdk/upstream/emscripten/src/jsifier.mjs'),'testObserversEnabled':a.test_observers},indent=2)+'\n');print('Original/mixed SFCTOOL pair PASS')
