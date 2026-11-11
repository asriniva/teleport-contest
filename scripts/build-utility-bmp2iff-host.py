"""Build a separate utility reference/mixed pair into mandatory fresh output."""
from pathlib import Path
import argparse,hashlib,json,os,subprocess
parser=argparse.ArgumentParser();parser.add_argument('--out',required=True);parser.add_argument('--source-root');options=parser.parse_args()
code_root=Path(__file__).resolve().parents[1];r=Path(options.source_root).resolve()if options.source_root else code_root
out=Path(options.out).resolve();out.mkdir(parents=True,exist_ok=False)
p=code_root/'nethack-c/wasm/utilities/bmp2iff-host';sdk=Path(os.environ.get('EMSDK',str(r/'.cache/emsdk'))).resolve();emcc=sdk/'upstream/emscripten/emcc'
source=r/'nethack-c/upstream/sys/amiga/bmp2iff_host.c';native_extra=[];defines=[];include=[]
exports=['malloc','calloc','free','memset','memcpy','strcmp','atoi','probe_run','probe_distance','probe_nearest','bmp_fopen','bmp_fclose','bmp_fread','bmp_fwrite','bmp_fputc','bmp_ftell','bmp_fseek','bmp_perror','bmp_error0','bmp_error_int','bmp_error_ptr','bmp_summary','bmp_layout']
common=[str(emcc),*['-O2','-g','-sMEMORY64=1','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sSTACK_SIZE=4194304','-sFORCE_FILESYSTEM=1','--no-entry'],*defines,*include,'-sEXPORTED_RUNTIME_METHODS='+json.dumps(['HEAPU8','FS','stackSave','stackRestore','stackAlloc']),'-sEXPORTED_FUNCTIONS='+json.dumps(['_'+s for s in exports]),'-ffile-prefix-map='+str(source.parent)+'/=','-DUTILITY_BMP_ORIGINAL_SOURCE='+json.dumps(str(source)),str(p/'probe.c'),str(p/'support.c'),*map(str,native_extra)]
inputs=[source,*native_extra,p/'probe.c',p/'support.c',p/'library.js',*[p/'abi.h'],*[],emcc,sdk/'upstream/bin/clang-21',code_root/'js/ported-utilities/bmp2iff-host.mjs',code_root/'js/ported-utilities/bmp2iff-host-runtime.mjs',code_root/'js/ported-utilities/bmp2iff-host-scope.mjs',Path(__file__).resolve()]
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
 rows.append({'name':name,'parameters':[x['name']for x in n.get('inner',[])if x.get('kind')=='ParmVarDecl'],'type':n['type']['qualType']})
assert len(rows)==8,(len(rows),[n['name']for n in rows]);(out/'inventory.json').write_text(json.dumps({'functions':rows,'sourceSha256':hashlib.sha256(source.read_bytes()).hexdigest(),'source':str(source),'count':len(rows)},indent=2)+'\n')
for mode in ['reference','hybrid']:
 cmd=common+(['-DMIXED_BMP=1','--js-library',str(p/'library.js')] if mode=='hybrid'else[])+['-o',str(out/(mode+'.mjs'))]
 with(out/(mode+'-build.log')).open('w')as f:z=subprocess.run(cmd,stdout=f,stderr=subprocess.STDOUT)
 commands.append({'mode':mode,'command':cmd,'exit':z.returncode});(out/'build-commands.json').write_text(json.dumps(commands,indent=2)+'\n');assert z.returncode==0,(mode,z.returncode)
assert hashes()==before;(out/'build-inputs-after.json').write_text(json.dumps(hashes(),indent=2)+'\n');print('Built bmp2iff-host actual originalC/mixed pair in fresh '+str(out))
