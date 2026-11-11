#!/usr/bin/env python3
"""Compile original C object startup + RNG + serializers as one test oracle."""
import argparse,hashlib,json,shlex,subprocess
from pathlib import Path
parser=argparse.ArgumentParser()
parser.add_argument('--reference-root',type=Path,required=True)
parser.add_argument('--out',type=Path,required=True)
parser.add_argument('--object-records',action='store_true',help='Include real MKOBJ/EAT/MON object-record dependency group')
args=parser.parse_args()
root=Path(__file__).resolve().parents[1]
reference=args.reference_root.resolve();out=args.out.resolve()
if out.exists():raise SystemExit('Use a fresh output directory')
out.mkdir(parents=True)
tree=reference/'.cache/wasm64-build/tree'
names=['objects','rnd','isaac64','alloc','strutil','hacklib','sfbase','sfstruct','dungeon']
if args.object_records:names+=['monst','eat','mon']
probe='standalone-object-records-probe.c' if args.object_records else 'standalone-object-state-probe.c'
sources=[root/'scripts'/probe,*[tree/f'src/{name}.c' for name in names]]
flags=['-O2','-g','-sMEMORY64=1','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sEXPORTED_RUNTIME_METHODS=HEAPU8,FS','--no-entry',
       *['-D'+d for d in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())],
       '-DSTANDALONE_O_INIT_SOURCE='+json.dumps(str(tree/'src/o_init.c')),
       '-I'+str(tree/'include'),'-I'+str(reference/'.cache/ncurses-wasm64-build/include'),'-I'+str(root/'scripts'),
       '-fmacro-prefix-map='+str(tree/'src')+'/=']
if args.object_records:flags+=['-DSTANDALONE_MKOBJ_SOURCE='+json.dumps(str(tree/'src/mkobj.c'))]
exports=['malloc','free',*['probe_'+name for name in ['init','action','low','high','pointer','name','get_name','descr','save','restore','next','diagnostics','layout_count','layout_name','layout_value']]]
if args.object_records:exports+=['probe_record_prepare','probe_record_new','probe_record_at','probe_record_head','probe_record_global','probe_record_op','probe_record_mail','obj_nutrition','eaten_stat','dealloc_mextra']
cmd=[str(reference/'.cache/emsdk/upstream/emscripten/emcc'),*flags,'-sEXPORTED_FUNCTIONS='+json.dumps(['_'+name for name in exports]),*[str(s) for s in sources],'-o',str(out/'reference.mjs')]
result=subprocess.run(cmd,capture_output=True,text=True)
(out/'build.log').write_text(result.stdout+result.stderr)
(out/'command.json').write_text(json.dumps(cmd,indent=2)+'\n')
if result.returncode:raise SystemExit(result.stderr[-6000:])
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
inputs=[*sources,tree/'src/o_init.c',root/'scripts/tu-o_init-layout.h',root/'nethack-c/wasm/compile-defines.json']
for source in sources:
    deps=subprocess.run([cmd[0],*flags,'-M',str(source)],capture_output=True,text=True,check=True)
    inputs.extend(Path(p).resolve() for p in shlex.split(deps.stdout.split(':',1)[1].replace('\\\n','')))
profile='Configured Emscripten memory64 original C startup + real RNG + SFBASE/SFSTRUCT'
if args.object_records:profile+=' + MKOBJ/EAT/MON object records and real monster catalogue'
(out/'receipt.json').write_text(json.dumps({'sourceSha256':{str(p):sha(p) for p in sorted(set(inputs))},'artifactSha256':{p.name:sha(p) for p in [out/'reference.mjs',out/'reference.wasm']},'compilerSha256':sha(reference/'.cache/emsdk/upstream/bin/clang'),'profile':profile+'; error/UI boundaries abort.'},indent=2)+'\n')
print('Built original-C '+('object-records' if args.object_records else 'object-state')+' subsystem oracle: '+str(out))
