from pathlib import Path
import subprocess,json,hashlib,time,shlex
import argparse,sys
parser=argparse.ArgumentParser(description='Build original C and mixed JavaScript XPM2IFF HOST utility pairs; requires fresh --out.')
parser.add_argument('--out',required=True,type=Path)
parser.add_argument('--source-root',type=Path,default=Path(__file__).resolve().parent.parent)
args=parser.parse_args();code_root=Path(__file__).resolve().parent.parent;root=args.source_root.resolve();out_arg=args.out.expanduser().absolute();b=out_arg.resolve();abi=code_root/'nethack-c/wasm/utilities/xpm2iff-host';emcc=root/'.cache/emsdk/upstream/emscripten/emcc'
if out_arg.exists() or out_arg.is_symlink() or b.exists():parser.error('--out must not already exist')
if not emcc.is_file():parser.error('the source repository must provide the existing local Emscripten SDK')
subprocess.run([sys.executable,str(code_root/'scripts/prepare-utility-xpm2iff-host.py'),'--out',str(b),'--source-root',str(root)],check=True)
exports=['probe_capture','probe_flush','probe_fail','probe_attempts','probe_run','probe_call','probe_global','probe_layout','probe_literal','probe_input','probe_output','probe_close','t_fopen','t_fclose','t_fgets','t_fputc','t_fwrite','t_scan_dimensions','t_scan_color','t_fprintf_p','t_fprintf_ii','t_printf5','t_isspace','t_stderr','t_malloc','t_calloc','t_free','t_memset','t_perror']
base=[str(emcc),'-O2','-g','-sMEMORY64=1','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sFORCE_FILESYSTEM=1','--no-entry','-sSTACK_SIZE=1048576','-sINITIAL_MEMORY=16777216','-sEXPORTED_RUNTIME_METHODS=FS,HEAPU8,stringToUTF8,lengthBytesUTF8,UTF8ToString,stackSave,stackRestore,stackAlloc','-sEXPORTED_FUNCTIONS='+json.dumps(['_'+x for x in exports]),'-I'+str(b),'-Wl,--wrap=malloc','-Wl,--wrap=calloc',str(abi/'probe.c'),str(abi/'transport.c')]
commands=[]
# Bracket final links with actual preprocessor-discovered file closure, no SDK copies.
prior=[]
if (b/'build-commands.json').exists():prior=json.loads((b/'build-commands.json').read_text())
if not (b/'prior-build-commands.json').exists():(b/'prior-build-commands.json').write_text(json.dumps(prior,indent=2)+'\n')
paths=set()
for name,source,extra in [('reference',abi/'probe.c',[]),('hybrid',abi/'probe.c',['-DHYBRID_XPM2IFF=1']),('transport',abi/'transport.c',[])]:
 argv=[str(emcc),'-sMEMORY64=1','-I'+str(b),'-M',*extra,str(source)]
 q=subprocess.run(argv,cwd=b,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
 (b/'logs'/('dependencies-'+name+'.d')).write_bytes(q.stdout);(b/'logs'/('dependencies-'+name+'.stderr.log')).write_bytes(q.stderr)
 assert q.returncode==0,q.stderr.decode()
 tokens=shlex.split(q.stdout.decode().replace('\\\n',' '));paths.update(Path(x).resolve() for x in tokens[1:])
 commands.append({'name':'dependencies-'+name,'argv':argv,'cwd':str(b),'exit':q.returncode})
paths.update([emcc,root/'.cache/emsdk/upstream/bin/clang',root/'AGENTS.md',code_root/'js/ported-utilities/xpm2iff-host.js',code_root/'js/ported-utilities/xpm2iff-host-runtime.js',abi/'library.js',Path(__file__).resolve(),code_root/'scripts/test-utility-xpm2iff-host.mjs',code_root/'scripts/prepare-utility-xpm2iff-host.py'])
inputhashes={str(p):hashlib.sha256(p.read_bytes()).hexdigest() for p in sorted(paths)}
(b/'final-link-inputs-before.json').write_text(json.dumps(inputhashes,indent=2)+'\n')
for name in ['reference','hybrid']:
 argv=base+(['-DHYBRID_XPM2IFF=1','--js-library',str(abi/'library.js')]if name=='hybrid'else[])+['-o',str(b/'artifacts'/f'{name}.mjs')]
 started=time.time();p=subprocess.run(argv,cwd=b,stdout=subprocess.PIPE,stderr=subprocess.STDOUT);(b/'logs'/f'build-{name}.log').write_bytes(p.stdout);commands.append({'name':name,'argv':argv,'cwd':str(b),'exit':p.returncode,'seconds':time.time()-started});(b/'build-commands.json').write_text(json.dumps(commands,indent=2)+'\n');print(name,p.returncode,flush=True)
 if p.returncode:raise SystemExit(p.returncode)
for name,args in [('source-cpp',['-E','-P']),('source-ast',['-fsyntax-only','-Xclang','-ast-dump=json'])]:
 argv=[str(emcc),'-sMEMORY64=1',*args,str(b/'source/xpm2iff_host.c')];p=subprocess.run(argv,cwd=b,stdout=subprocess.PIPE,stderr=subprocess.PIPE);(b/f'{name}.txt').write_bytes(p.stdout);(b/'logs'/f'{name}.stderr.log').write_bytes(p.stderr);commands.append({'name':name,'argv':argv,'cwd':str(b),'exit':p.returncode});(b/'build-commands.json').write_text(json.dumps(commands,indent=2)+'\n');print(name,p.returncode,flush=True)
 if p.returncode:raise SystemExit(p.returncode)

after={str(p):hashlib.sha256(p.read_bytes()).hexdigest() for p in sorted(paths)}
assert after==inputhashes,'final link input drift'
(b/'final-link-inputs-after.json').write_text(json.dumps(after,indent=2)+'\n')
print('final link inputs unchanged',len(after),flush=True)
