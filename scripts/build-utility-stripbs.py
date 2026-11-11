from pathlib import Path
import argparse,subprocess,json,hashlib,os,sys
stage=Path(__file__).resolve().parents[1]
parser=argparse.ArgumentParser(description='Build actual original/hybrid stripbs utility pair into a fresh directory')
parser.add_argument('--out',type=Path,required=True)
parser.add_argument('--source-root',type=Path,default=stage,help='Real repository containing original C and existing SDK; staging remains this script root')
args=parser.parse_args();source_root=args.source_root.resolve();w=args.out.resolve()
if w.exists():parser.error('--out must not exist; preserve prior builds')
w.mkdir(parents=True)
sdk=Path(os.environ.get('EMSDK',source_root/'.cache/emsdk')).resolve();emcc=sdk/'upstream/emscripten/emcc';commands=[]
source=source_root/'nethack-c/upstream/util/stripbs.c'
assert source.is_file(),source
metadata=[]
for label,flags in [('profile-macros',['-dM','-E']),('compiler-ast',['-Xclang','-ast-dump=json','-fsyntax-only'])]:
 cmd=[str(emcc),'-O2','-sMEMORY64=1','-I',str(source_root),*flags,str(source)]
 result=subprocess.run(cmd,cwd=stage,capture_output=True,text=True)
 (w/(label+'.log')).write_text(result.stderr)
 metadata.append({'label':label,'args':cmd,'cwd':str(stage),'exit':result.returncode,'stdoutSha256':hashlib.sha256(result.stdout.encode()).hexdigest(),'stdoutBytes':len(result.stdout.encode())})
 (w/'metadata-commands.json').write_text(json.dumps(metadata,indent=2)+'\n')
 assert result.returncode==0,(label,result.stderr)
 if label=='profile-macros':(w/'profile-macros.txt').write_text(result.stdout)
 else:
  data=json.loads(result.stdout);functions=[]
  for node in data['inner']:
   loc=node.get('loc',{})
   if node.get('kind')!='FunctionDecl' or not any(n.get('kind')=='CompoundStmt'for n in node.get('inner',[])) or 'includedFrom'in loc:continue
   if loc.get('file') and Path(loc['file']).resolve()!=source:continue
   functions.append({'name':node['name'],'type':node['type'],'loc':loc,'parameters':[{'name':n.get('name'),'type':n['type']}for n in node.get('inner',[])if n.get('kind')=='ParmVarDecl']})
  (w/'configured-functions.json').write_text(json.dumps(functions,indent=2)+'\n')
guard=subprocess.run([sys.executable,'-B',str(stage/'scripts/check-utility-stripbs.py'),'--out',str(w),'--source-root',str(source_root)],cwd=stage,capture_output=True,text=True)
(w/'source-guard.log').write_text(guard.stdout+guard.stderr);assert guard.returncode==0,guard.stdout+guard.stderr
base=[str(emcc),'-O2','-sMEMORY64=1','-sMODULARIZE=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sINITIAL_MEMORY=2097152','-sSTACK_SIZE=65536','--no-entry','-sEXPORTED_RUNTIME_METHODS=FS,HEAPU8','-sEXPORTED_FUNCTIONS='+','.join('_'+n for n in ['probe_prepare','probe_run','probe_errno','probe_eof','probe_error','probe_output_closed','probe_stack','teleport_stripbs_metadata'])]
for mode in ['reference','hybrid']:
 cmd=base+['-I',str(source_root),str(stage/'scripts/utility-stripbs-probe.c'),str(stage/'nethack-c/wasm/utilities/stripbs/transport.c')]+(['-DSTRIPBS_REFERENCE']if mode=='reference'else['--js-library',str(stage/'nethack-c/wasm/utilities/stripbs/library.js')])+['-o',str(w/(mode+'.mjs'))]
 commands.append({'mode':mode,'args':cmd,'cwd':str(stage)})
 with (w/(mode+'-build.log')).open('w')as log:result=subprocess.run(cmd,cwd=stage,stdout=log,stderr=subprocess.STDOUT)
 commands[-1]['exit']=result.returncode;(w/'build-commands.json').write_text(json.dumps(commands,indent=2)+'\n');assert result.returncode==0,(mode,result.returncode)
print('Both actual original and hybrid memory64 builds PASS')
