#!/usr/bin/env python3
"""Original full DECL/data/role/startup owners; no production C dependency."""
import argparse,hashlib,json,shlex,subprocess,sys
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--reference-root',type=Path,required=True);p.add_argument('--out',type=Path,required=True);a=p.parse_args()
root=Path(__file__).resolve().parents[1];ref=a.reference_root.resolve();out=a.out.resolve();tree=ref/'.cache/wasm64-build/tree'
if out.exists():raise SystemExit('Use a fresh output directory')
out.mkdir(parents=True)
names=['objects','monst','role','isaac64','alloc','strutil','hacklib','dungeon','sys','objnam','o_init','sfbase','sfstruct','allmain','pray','drawing','nhlua','nhlsel','nhlobj','sp_lev','selvar','files','mkmap','display','options','attrib','exper','polyself','eat','botl','mondata','calendar','light','mon','shknam','windows','mklev','bones','rect','region','stairs','dbridge','cmd','symbols','sounds','mkmaze','trap','mkroom','zap','hack','mkobj','invent','spell','lock','shk','pickup','do_name','timeout','makemon','do','read','steed','dog','minion','priest','vault','questpgr','steal','worn','muse','teleport','do_wear','monmove','engrave','rumors','dig']
fixtures=[]
for name in ['standalone-startup-probe.c','standalone-dungeon-startup-probe.c','standalone-hero-startup-probe.c','standalone-display-startup-probe.c','standalone-level-startup-probe.c','standalone-level-rng-probe.c','standalone-level-contents-probe.c']:
 source=root/'scripts'/name;body=source.read_text()
 if name=='standalone-startup-probe.c':
  declarations='__typeof__(windowprocs) windowprocs;\nwin_request_info zerowri={0};\n'
  if body.count(declarations)!=1:raise SystemExit('Review changed callback fixture declaration')
  body=body.replace(declarations,'/* Actual WINDOWS owns windowprocs and zerowri in this profile. */\n#include "decl.c"\n')
 if name=='standalone-display-startup-probe.c':
  decl=json.loads((root/'js/nethack/decl-storage.json').read_text())['globals']
  body+='\nconst volatile void *probe_decl_global(int i){switch(i){'+''.join('case '+str(i)+':return &'+row['name']+';' for i,row in enumerate(decl))+'}return NULL;}\n'
 target=out/name;target.write_text(body);fixtures.append(source)
sources=[out/'standalone-level-contents-probe.c',out/'standalone-level-rng-probe.c',*[tree/f'src/{n}.c' for n in names],tree/'sys/unix/unixmain.c',tree/'win/tty/wintty.c',tree/'win/tty/termcap.c',ref/'nethack-c/wasm/compress-service.c']
sources.extend(p for p in sorted((tree/'lib/lua-5.4.8/src').glob('*.c')) if p.stem not in ['lua','luac','onelua'])
flags=['-I'+str(root/'scripts'),'-I'+str(root/'nethack-c/wasm/tu-fragments'),'-I'+str(tree/'src'),'-I'+str(tree/'lib/lua-5.4.8/src'),'-O2','-g','-sMEMORY64=1','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sEXPORTED_RUNTIME_METHODS=HEAPU8,FS','--no-entry','-Wl,--error-limit=0',
 *['-D'+d for d in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())],'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),'-fmacro-prefix-map='+str(tree/'src')+'/=']
exports=['malloc','free','probe_startup_init','probe_startup_role_config','probe_startup_role','probe_startup_newgame','probe_startup_global','probe_startup_diagnostics','probe_startup_dungeons','probe_dungeon_global','nh_getenv','getenv','setenv','unsetenv','probe_hero_init','probe_hero_global','probe_hero_layout','probe_hero_roleplay','lua_getglobal','lua_getfield','lua_type','lua_settop','lua_tolstring','lua_tointegerx','has_color','probe_display_reset','probe_display_global','probe_display_layout','probe_display_config','probe_signal_pointer','probe_signal_set','probe_signal_reset','probe_signal_seen','probe_signal_errno','probe_decl_global','probe_signal_global','probe_signal_set_token','sigaction','signal','raise','probe_level_init','probe_level_rng_pointer','probe_level_reseed','probe_level_rng_state','probe_level_rng_initialized','probe_level_rng_layout','rn2','rn2_on_display_rng','sys_random_seed','mklev','getbones']
exports.extend(['vision_init','probe_vision_storage','probe_vision_storage_size'])
exports.extend(['probe_contents_layout_count','probe_contents_layout_name','probe_contents_layout_value'])
exports.extend(['probe_contents_trap','probe_contents_traps','probe_contents_room_query'])
exports.extend(['selection_new','selection_free','selection_clear','selection_clone','selection_getbounds','selection_getpoint','selection_setpoint','selection_not','selection_filter_percent','selection_rndcoord','selection_do_grow','selection_do_line','selection_do_randline','selection_do_ellipse','selection_do_gradient','selection_from_mkroom'])
cmd=[str(ref/'.cache/emsdk/upstream/emscripten/emcc'),*flags,'-sEXPORTED_FUNCTIONS='+json.dumps(['_'+n for n in exports]),*[str(s) for s in sources],'-o',str(out/'reference.mjs')]
sys.dont_write_bytecode=True
from standalone_c_boundaries import build
result,cmd,boundaries=build(cmd,flags,sources,root,ref,out,headers=("sp_lev.h","region.h","wintty.h"))
(out/'build.log').write_text(result.stdout+result.stderr);(out/'command.json').write_text(json.dumps(cmd,indent=2)+'\n')
if result.returncode:raise SystemExit(result.stderr[-6000:])
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
inputs=[Path(__file__).resolve(),root/'scripts/standalone_c_boundaries.py',root/'js/nethack/decl-storage.json',*fixtures,*sources,ref/'.cache/emsdk/upstream/emscripten/system/lib/libc/sigaction.c',ref/'.cache/emsdk/upstream/emscripten/system/lib/libc/raise.c',ref/'.cache/emsdk/upstream/emscripten/system/lib/libc/musl/src/signal/signal.c',root/'nethack-c/wasm/compile-defines.json',tree/'dat/nhlib.lua',tree/'dat/dungeon.lua',tree/'dat/nhcore.lua',*sorted((tree/'dat').glob('*.lua')),*[tree/'dat'/name for name in ['epitaph','engrave','rumors','bogusmon','oracles']]]
for source in sources:
 deps=subprocess.run([cmd[0],*flags,'-M',str(source)],capture_output=True,text=True,check=True)
 inputs.extend(Path(p).resolve() for p in shlex.split(deps.stdout.split(':',1)[1].replace('\\\n','')))
(out/'receipt.json').write_text(json.dumps({'sourceSha256':{str(p):sha(p)for p in sorted(set(inputs))},'artifactSha256':{p.name:sha(p)for p in [out/'reference.mjs',out/'reference.wasm']},'externalBoundaries':boundaries,'profile':'Original configured memory64 VISION (included original owner) /TRAP/MKROOM/ZAP/MKLEV/BONES/RECT/REGION/STAIRS/RND plus WINDOWS/DISPLAY/signals/hero/attributes/energy/form/hunger/clock startup plus DECL/role/dungeon/NHLUA/NHLSEL/NHLOBJ/SP_LEV/SELVAR/FILES plus original Lua5.4.8 source; WINDOWS owns original default callback storage; unconnected function boundaries abort.'},indent=2)+'\n')
print('Built original-C level contents reference: '+str(out))
