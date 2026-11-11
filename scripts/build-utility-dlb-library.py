"""Build a separate utility reference/mixed pair into mandatory fresh output."""
from pathlib import Path
import argparse,hashlib,json,os,subprocess
parser=argparse.ArgumentParser();parser.add_argument('--out',required=True);parser.add_argument('--source-root');options=parser.parse_args()
code_root=Path(__file__).resolve().parents[1];r=Path(options.source_root).resolve()if options.source_root else code_root
out=Path(options.out).resolve();out.mkdir(parents=True,exist_ok=False)
p=code_root/'nethack-c/wasm/utilities/dlb-library';sdk=Path(os.environ.get('EMSDK',str(r/'.cache/emsdk'))).resolve();emcc=sdk/'upstream/emscripten/emcc'
source=r/'nethack-c/upstream/src/dlb.c';native_extra=[r/'nethack-c/upstream/src/alloc.c',r/'nethack-c/upstream/src/hacklib.c',r/'nethack-c/upstream/util/panic.c'];defines=['-DDLB','-DDLBLIB=','-Dfree=utility_trace_free','-DNOTPARMDECL','-DNO_TIMED_DELAY'];include=['-I'+str(r/'.cache/wasm64-build/tree/include')]
exports=['malloc','free','memset','alloc','probe_action','probe_pointer','utility_library_storage','utility_fits','utility_eos','utility_filename_cmp','utility_fscanf_header','utility_fscanf_entry','utility_fread','utility_fopen_datafile','utility_fclose','utility_fseek','utility_fgets','utility_fgetc','utility_ftell','utility_string','utility_layout','utility_trace_free','utility_free_count']
common=[str(emcc),*['-O2','-g','-sMEMORY64=1','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sSTACK_SIZE=4194304','-sFORCE_FILESYSTEM=1','--no-entry'],*defines,*include,'-sEXPORTED_RUNTIME_METHODS='+json.dumps(['HEAPU8','FS','stackSave','stackRestore','stackAlloc']),'-sEXPORTED_FUNCTIONS='+json.dumps(['_'+s for s in exports]),'-ffile-prefix-map='+str(source.parent)+'/=','-DUTILITY_DLB_ORIGINAL_SOURCE='+json.dumps(str(source)),str(p/'probe.c'),str(p/'support.c'),*map(str,native_extra)]
inputs=[source,*native_extra,p/'probe.c',p/'support.c',p/'library.js',*[p/'layout-schema.json'],*[x for x in (r/'.cache/wasm64-build/tree/include').glob('*.h')],emcc,sdk/'upstream/bin/clang-21',code_root/'js/ported-utilities/dlb-library.mjs',code_root/'js/ported-utilities/dlb-library-runtime.mjs',code_root/'js/ported-utilities/dlb-library-scope.mjs',Path(__file__).resolve()]
def hashes():
 result={}
 for x in inputs:
  with x.open('rb')as stream:result[str(x.resolve())]=hashlib.file_digest(stream,'sha256').hexdigest()
 return result
before=hashes();(out/'build-inputs-before.json').write_text(json.dumps(before,indent=2)+'\n');commands=[]
astcmd=[str(emcc),'-O2','-g','-sMEMORY64=1',*defines,*include,'-Xclang','-ast-dump=json','-fsyntax-only',str(source)]
with(out/'ast.json').open('w')as f:z=subprocess.run(astcmd,stdout=f,stderr=subprocess.PIPE,text=True)
(out/'ast-stderr.log').write_text(z.stderr);commands.append({'mode':'compiler-inventory','command':astcmd,'exit':z.returncode});assert z.returncode==0
text=source.read_text();tree=json.loads((out/'ast.json').read_text());rows=[]
for n in tree['inner']:
 if n.get('kind')!='FunctionDecl'or not any(x.get('kind')=='CompoundStmt'for x in n.get('inner',[])):continue
 loc=n.get('loc',{});offset=loc.get('offset',-1);name=n.get('name','')
 if offset<0 or loc.get('includedFrom')or text[offset:offset+len(name)]!=name:continue
 rows.append({'name':name,'params':[x['name']for x in n.get('inner',[])if x.get('kind')=='ParmVarDecl'],'type':n['type']['qualType']})
assert len(rows)==22,(len(rows),[n['name']for n in rows]);(out/'inventory.json').write_text(json.dumps({'functions':rows,'sourceSha256':hashlib.sha256(source.read_bytes()).hexdigest(),'source':str(source),'count':len(rows)},indent=2)+'\n')
for mode in ['reference','hybrid']:
 cmd=common+(['-DMIXED_LIBRARY','--js-library',str(p/'library.js')] if mode=='hybrid'else[])+['-o',str(out/(mode+'.mjs'))]
 with(out/(mode+'-build.log')).open('w')as f:z=subprocess.run(cmd,stdout=f,stderr=subprocess.STDOUT)
 commands.append({'mode':mode,'command':cmd,'exit':z.returncode});(out/'build-commands.json').write_text(json.dumps(commands,indent=2)+'\n');assert z.returncode==0,(mode,z.returncode)
assert hashes()==before;(out/'build-inputs-after.json').write_text(json.dumps(hashes(),indent=2)+'\n');print('Built dlb-library actual originalC/mixed pair in fresh '+str(out))
