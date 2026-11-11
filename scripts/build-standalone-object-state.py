#!/usr/bin/env python3
"""Compile original C object startup + RNG + serializers as one test oracle."""
import argparse,hashlib,json,shlex,subprocess,sys
from pathlib import Path
parser=argparse.ArgumentParser()
parser.add_argument('--reference-root',type=Path,required=True)
parser.add_argument('--out',type=Path,required=True)
parser.add_argument('--object-records',action='store_true',help='Include real MKOBJ/EAT/MON object-record dependency group')
parser.add_argument('--item-inventory',action='store_true',help='Build the real generation/inventory group with explicit abort-only external boundaries')
parser.add_argument('--timers',action='store_true',help='Add actual timer policies to the item/inventory reference')
parser.add_argument('--monster-selection',action='store_true',help='Add real random species selection and biological helper policies')
parser.add_argument('--item-naming',action='store_true',help='Expose actual artifact static state for naming/generation comparisons')
args=parser.parse_args()
if args.item_naming:args.monster_selection=True
if args.monster_selection:args.timers=True
if args.timers:args.item_inventory=True
root=Path(__file__).resolve().parents[1]
reference=args.reference_root.resolve();out=args.out.resolve()
if out.exists():raise SystemExit('Use a fresh output directory')
out.mkdir(parents=True)
tree=reference/'.cache/wasm64-build/tree'
names=['objects','rnd','isaac64','alloc','strutil','hacklib','sfbase','sfstruct','dungeon']
if args.object_records or args.item_inventory:names+=['monst','eat','mon']
if args.item_inventory:names+=['artifact','objnam','attrib','spell','light','lock','shk','display','pickup','do_name','drawing','role','shknam','sys']
if args.timers:names+=['timeout','hack']
if args.monster_selection:names+=['makemon','mondata','do','read']
if args.item_naming:names.remove('artifact')
probe='standalone-object-records-probe.c' if args.object_records else 'standalone-object-state-probe.c'
if args.item_inventory:probe='standalone-item-inventory-probe.c'
if args.timers:probe='standalone-timers-probe.c'
if args.monster_selection:probe='standalone-special-items-probe.c'
if args.item_naming:probe='standalone-item-naming-probe.c'
sources=[root/'scripts'/probe,*[tree/f'src/{name}.c' for name in names]]
flags=['-O2','-g','-sMEMORY64=1','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sEXPORTED_RUNTIME_METHODS=HEAPU8,FS','--no-entry',
       *['-D'+d for d in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())],
       '-DSTANDALONE_O_INIT_SOURCE='+json.dumps(str(tree/'src/o_init.c')),
       '-I'+str(tree/'include'),'-I'+str(reference/'.cache/ncurses-wasm64-build/include'),'-I'+str(root/'scripts'),
       '-fmacro-prefix-map='+str(tree/'src')+'/=']
if args.object_records or args.item_inventory:flags+=['-DSTANDALONE_MKOBJ_SOURCE='+json.dumps(str(tree/'src/mkobj.c'))]
if args.item_inventory:flags+=['-DSTANDALONE_INVENT_SOURCE='+json.dumps(str(tree/'src/invent.c')),'-Wl,--error-limit=0']
if args.item_naming:flags+=['-DSTANDALONE_ARTIFACT_SOURCE='+json.dumps(str(tree/'src/artifact.c'))]
exports=['malloc','free',*['probe_'+name for name in ['init','action','low','high','pointer','name','get_name','descr','save','restore','next','diagnostics','layout_count','layout_name','layout_value']]]
if args.object_records:exports+=['probe_record_prepare','probe_record_new','probe_record_at','probe_record_head','probe_record_global','probe_record_op','probe_record_mail','obj_nutrition','eaten_stat','dealloc_mextra']
if args.item_inventory:exports+=['probe_item_prepare','probe_item_create','probe_item_at','probe_item_global','probe_item_action','probe_item_flush','probe_item_updates','probe_item_force_growth']
if args.timers:exports+=['probe_timer_arg','probe_timer_global','probe_timer_op','probe_timer_layout','probe_timer_fixup']
if args.monster_selection:exports+=['probe_species_config','probe_species_select','probe_species_biology','probe_special_dispose']
if args.item_naming:exports+=['probe_artifact_data','nartifact_exist']
cmd=[str(reference/'.cache/emsdk/upstream/emscripten/emcc'),*flags,'-sEXPORTED_FUNCTIONS='+json.dumps(['_'+name for name in exports]),*[str(s) for s in sources],'-o',str(out/'reference.mjs')]
boundaries=[]
if args.item_inventory:
    sys.dont_write_bytecode=True
    from standalone_c_boundaries import build
    result,cmd,boundaries=build(cmd,flags,sources,root,reference,out)
else:result=subprocess.run(cmd,capture_output=True,text=True)
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
if args.item_inventory:profile+=' + item generation/inventory; explicit zero component-input globals and abort-only unconnected function boundaries'
if args.timers:profile+=' + real TIMEOUT/HACK queue and anything transport'
if args.monster_selection:profile+=' + real MAKEMON/MONDATA random species and biological policies'
if args.item_naming:profile+=' + original ARTIFACT static-state observation for naming/generation'
(out/'receipt.json').write_text(json.dumps({'sourceSha256':{str(p):sha(p) for p in sorted(set(inputs))},'artifactSha256':{p.name:sha(p) for p in [out/'reference.mjs',out/'reference.wasm']},'compilerSha256':sha(reference/'.cache/emsdk/upstream/bin/clang'),'externalBoundaries':boundaries,'profile':profile+'; error/UI boundaries abort.'},indent=2)+'\n')
print('Built original-C '+('item-naming' if args.item_naming else 'special-items' if args.monster_selection else 'timers' if args.timers else 'item-inventory' if args.item_inventory else 'object-records' if args.object_records else 'object-state')+' subsystem oracle: '+str(out))
