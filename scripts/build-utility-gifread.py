from pathlib import Path
import subprocess,json,hashlib,argparse
parser=argparse.ArgumentParser();parser.add_argument('--out',required=True,type=Path);parser.add_argument('--source-root',type=Path);args=parser.parse_args();code_root=Path(__file__).resolve().parents[1];r=(args.source_root or code_root).resolve();p=code_root/'nethack-c/wasm/utilities/gifread';out=args.out.resolve();out.mkdir(parents=True,exist_ok=False)
emcc=str(r/'.cache/emsdk/upstream/emscripten/emcc');incs=['-DNOTPARMDECL','-DNO_TIMED_DELAY','-I'+str(r/'.cache/wasm64-build/tree/include'),'-I'+str(r/'nethack-c/upstream/win/share'),'-DUTILITY_GIFREAD_REFERENCE_SOURCE=\"'+str(r/'nethack-c/upstream/win/share/gifread.c')+'\"']
exports=['probe_prepare', 'probe_state', 'probe_open', 'probe_read', 'probe_close', 'probe_main', 'probe_stack', 'probe_helper', 'probe_pixels', 'probe_palette', 'probe_colors', 'probe_block', 'probe_flush', 'teleport_gif_metadata', 'teleport_gif_allocations', 'teleport_gif_frees', 'teleport_gif_alloc_size', 'teleport_gif_free_id']
files=['win/share/tiletext.c','win/share/tiletxt.c','src/drawing.c','src/monst.c','src/objects.c','src/alloc.c','util/panic.c','src/hacklib.c'];commands=[]
def run(cmd,log):
 row={'command':cmd};commands.append(row);(out/'commands.json').write_text(json.dumps(commands,indent=2)+'\n')
 with(out/log).open('w')as f:z=subprocess.run(cmd,stdout=f,stderr=subprocess.STDOUT)
 row['exit']=z.returncode;(out/'commands.json').write_text(json.dumps(commands,indent=2)+'\n');assert z.returncode==0,log
source=r/'nethack-c/upstream/win/share/gifread.c'
inventory=[emcc,'-O2','-sMEMORY64=1',*incs,'-Xclang','-ast-dump=json','-fsyntax-only',str(source)]
with(out/'compiler-ast.json').open('w')as f,(out/'inventory.log').open('w')as err:z=subprocess.run(inventory,stdout=f,stderr=err)
commands.append({'command':inventory,'exit':z.returncode});assert z.returncode==0,'inventory'
ast=json.loads((out/'compiler-ast.json').read_text());functions=[]
for n in ast['inner']:
 if n.get('kind')=='FunctionDecl'and any(v.get('kind')=='CompoundStmt'for v in n.get('inner',[])):
  loc=n.get('loc',{});loc=loc.get('expansionLoc',loc)
  if not loc.get('includedFrom')and n.get('name')!='__isspace':functions.append({'name':n['name'],'parameters':[{'name':v['name']}for v in n.get('inner',[])if v.get('kind')=='ParmVarDecl']})
(out/'configured-functions.json').write_text(json.dumps(functions,indent=2)+'\n')
# Collect every native unit's actual transitive include closure BEFORE compiling.
units=[(r/'nethack-c/upstream'/f,[])for f in files]+[(p/'probe.c',[]),(p/'probe.c',['-DGIF_REFERENCE']),(p/'transport.c',[])]
inputs=set()
for i,(source,flags)in enumerate(units):
 dep=out/('unit-'+str(i)+'.d');run([emcc,'-O2','-sMEMORY64=1',*incs,*flags,'-M','-MT','utility_input','-MF',str(dep),str(source)],'dependency-'+str(i)+'.log')
 for s in dep.read_text().replace('\\\n',' ').split(':',1)[1].split():inputs.add(Path(s).resolve())
assert r/'nethack-c/upstream/win/share/tilemap.c'in inputs,'actual tiletxt transitive policy closure required'
inputs.update(code_root/f for f in ['js/ported-utilities/gifread/runtime.js', 'js/ported-utilities/gifread/gifread.js', 'nethack-c/wasm/utilities/gifread/transport.c', 'nethack-c/wasm/utilities/gifread/library.js', 'nethack-c/wasm/utilities/gifread/probe.c', 'scripts/build-utility-gifread.py', 'scripts/test-utility-gifread.mjs', 'scripts/check-utility-gifread.py', 'scripts/lower-utility-gifread.py', 'scripts/fixtures-utility-gifread.py', 'js/c-runtime/context.js'])
sdk=r/'.cache/emsdk/upstream';ems=sdk/'emscripten'
# No SDK copying; hash implementation source + actual compiler/link tools.
inputs.update(x for x in ems.glob('*.py')if x.is_file())
inputs.update(x for x in (ems/'tools').rglob('*.py')if x.is_file())
inputs.update(x for x in (ems/'src').rglob('*')if x.is_file()and x.suffix in ['.js','.mjs','.json'])
inputs.update([ems/'emcc',sdk/'bin/clang-21',sdk/'bin/wasm-ld'])
inputs.update(x for x in (ems/'cache/sysroot/lib/wasm64-emscripten').glob('*.a')if x.is_file())
sha=lambda x:hashlib.file_digest(open(x,'rb'),'sha256').hexdigest()
def pins():return{str(x):sha(x)for x in sorted(inputs)}
before=pins();assert before[str(ems/'src/jsifier.mjs')].startswith('24b5838f'),'reviewed current SDK serializer required'
(out/'inputs-before.json').write_text(json.dumps(before,indent=2)+'\n');objs=[]
for file in files:
 obj=out/(Path(file).stem+'.o');run([emcc,'-O2','-sMEMORY64=1',*incs,'-c',str(r/'nethack-c/upstream'/file),'-o',str(obj)],Path(file).stem+'-build.log');objs.append(str(obj))
for mode in ['reference','hybrid']:
 cmd=[emcc,'-O2','-g','-sMEMORY64=1','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sINITIAL_MEMORY=4194304','-sSTACK_SIZE=131072','--no-entry','-sFORCE_FILESYSTEM=1','-sEXIT_RUNTIME=1','-sEXPORTED_RUNTIME_METHODS='+json.dumps(['FS','HEAPU8','stackSave','stackRestore','stackAlloc']),'-sEXPORTED_FUNCTIONS='+json.dumps(['_'+s for s in exports]),*incs,str(p/'probe.c'),str(p/'transport.c'),*objs,*(['--js-library',str(p/'library.js')]if mode=='hybrid'else['-DGIF_REFERENCE']),'-o',str(out/(mode+'.mjs'))];run(cmd,mode+'-build.log')
after=pins();(out/'inputs-after.json').write_text(json.dumps(after,indent=2)+'\n');assert before==after,'source/compiler/include closure changed during pair build'
(out/'artifacts.json').write_text(json.dumps({x.name:sha(x)for x in out.iterdir()if x.suffix in ['.mjs','.wasm','.o']},indent=2)+'\n');print('PASS fresh original/mixed  GIFREAD pair; complete unit include closure + reviewed SDK source pins')
