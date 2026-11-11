#!/usr/bin/env python3
"""Original full DECL/data/role/startup owners; no production C dependency."""
import argparse,hashlib,json,shlex,subprocess,sys
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--reference-root',type=Path,required=True);p.add_argument('--out',type=Path,required=True);a=p.parse_args()
root=Path(__file__).resolve().parents[1];ref=a.reference_root.resolve();out=a.out.resolve();tree=ref/'.cache/wasm64-build/tree'
if out.exists():raise SystemExit('Use a fresh output directory')
out.mkdir(parents=True)
names=['decl','objects','monst','role','rnd','isaac64','alloc','strutil','hacklib','dungeon','sys','objnam','o_init','sfbase','sfstruct','allmain','pray','drawing','nhlua','nhlsel','nhlobj','sp_lev','selvar','files','mkmap','display','options','attrib','exper','polyself','eat','botl','mondata','calendar','light','mon','shknam']
sources=[root/'scripts/standalone-hero-startup-probe.c',*[tree/f'src/{n}.c' for n in names],tree/'sys/unix/unixmain.c']
sources.extend(p for p in sorted((tree/'lib/lua-5.4.8/src').glob('*.c')) if p.stem not in ['lua','luac','onelua'])
flags=['-I'+str(tree/'src'),'-I'+str(tree/'lib/lua-5.4.8/src'),'-O2','-g','-sMEMORY64=1','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sEXPORTED_RUNTIME_METHODS=HEAPU8,FS','--no-entry','-Wl,--error-limit=0',
 *['-D'+d for d in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())],'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),'-fmacro-prefix-map='+str(tree/'src')+'/=']
exports=['malloc','free','probe_startup_init','probe_startup_role_config','probe_startup_role','probe_startup_newgame','probe_startup_global','probe_startup_diagnostics','probe_startup_dungeons','probe_dungeon_global','nh_getenv','getenv','setenv','unsetenv','probe_hero_init','probe_hero_global','probe_hero_layout','probe_hero_roleplay','lua_getglobal','lua_getfield','lua_type','lua_settop','lua_tolstring','lua_tointegerx']
cmd=[str(ref/'.cache/emsdk/upstream/emscripten/emcc'),*flags,'-sEXPORTED_FUNCTIONS='+json.dumps(['_'+n for n in exports]),*[str(s) for s in sources],'-o',str(out/'reference.mjs')]
sys.dont_write_bytecode=True
from standalone_c_boundaries import build
result,cmd,boundaries=build(cmd,flags,sources,root,ref,out,headers=("sp_lev.h",))
(out/'build.log').write_text(result.stdout+result.stderr);(out/'command.json').write_text(json.dumps(cmd,indent=2)+'\n')
if result.returncode:raise SystemExit(result.stderr[-6000:])
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
inputs=[Path(__file__).resolve(),root/'scripts/standalone_c_boundaries.py',*sources,root/'nethack-c/wasm/compile-defines.json',tree/'dat/nhlib.lua',tree/'dat/dungeon.lua',tree/'dat/nhcore.lua']
for source in sources:
 deps=subprocess.run([cmd[0],*flags,'-M',str(source)],capture_output=True,text=True,check=True)
 inputs.extend(Path(p).resolve() for p in shlex.split(deps.stdout.split(':',1)[1].replace('\\\n','')))
(out/'receipt.json').write_text(json.dumps({'sourceSha256':{str(p):sha(p)for p in sorted(set(inputs))},'artifactSha256':{p.name:sha(p)for p in [out/'reference.mjs',out/'reference.wasm']},'externalBoundaries':boundaries,'profile':'Original configured memory64 hero/attributes/energy/form/hunger/clock startup plus DECL/role/dungeon/NHLUA/NHLSEL/NHLOBJ/SP_LEV/SELVAR/FILES plus original Lua5.4.8 source; window callback storage is explicit zero input, unconnected function boundaries abort.'},indent=2)+'\n')
print('Built original-C hero startup reference: '+str(out))
