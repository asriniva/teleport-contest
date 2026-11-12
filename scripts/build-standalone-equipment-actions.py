#!/usr/bin/env python3
"""Original equipment startup and post-startup armor/callback observations."""
import argparse,hashlib,json,shlex,subprocess,sys
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--reference-root',type=Path,required=True);p.add_argument('--out',type=Path,required=True);a=p.parse_args()
root=Path(__file__).resolve().parents[1];ref=a.reference_root.resolve();out=a.out.resolve();tree=ref/'.cache/wasm64-build/tree'
if out.exists():raise SystemExit('Use a fresh output directory')
out.mkdir(parents=True)
names=['objects','monst','role','isaac64','alloc','strutil','hacklib','dungeon','sys','objnam','o_init','sfbase','sfstruct','allmain','pray','drawing','nhlua','nhlsel','nhlobj','sp_lev','selvar','files','mkmap','display','attrib','exper','polyself','eat','mondata','calendar','light','mon','shknam','mklev','bones','rect','region','stairs','dbridge','cmd','symbols','mkmaze','trap','mkroom','zap','mkobj','invent','spell','lock','shk','pickup','do_name','timeout','makemon','do','read','steed','dog','minion','priest','vault','questpgr','steal','worn','muse','teleport','monmove','engrave','rumors','dig','pline','date','mdlib','insight','cfgfiles','glyphs','earlyarg','end','weapon','wield']
fixtures=[]
for name in ['standalone-startup-probe.c','standalone-dungeon-startup-probe.c','standalone-hero-startup-probe.c','standalone-display-startup-probe.c','standalone-level-startup-probe.c','standalone-level-rng-probe.c','standalone-level-contents-probe.c','standalone-window-startup-probe.c','standalone-windows-native.c','standalone-wintty-native.c','standalone-banner-version-native.c','standalone-banner-options-native.c','standalone-status-native.c','standalone-status-sounds-native.c','standalone-movement-native.c','standalone-inventory-startup-probe.c','standalone-equipment-startup-probe.c','standalone-armor-actions-native.c']:
 source=root/'scripts'/name;body=source.read_text()
 if name=='standalone-startup-probe.c':
  for line in ['void nh_terminate(int status){abort();}\n','void panic(const char *fmt,...){fputs(fmt,stderr);abort();}\n']:
   if body.count(line)!=1:raise SystemExit('Review changed fatal fixture')
   body=body.replace(line,'/* Actual END owns this fatal entry in this profile. */\n')
  declarations='__typeof__(windowprocs) windowprocs;\nwin_request_info zerowri={0};\n'
  if body.count(declarations)!=1:raise SystemExit('Review changed callback fixture declaration')
  body=body.replace(declarations,'/* Actual WINDOWS owns windowprocs and zerowri in this profile. */\n#include "decl.c"\n')
 if name=='standalone-startup-probe.c':
  error='void error(const char *fmt,...){abort();}\n'
  if body.count(error)!=1:raise SystemExit('Review changed fatal-entry fixture')
  body=body.replace(error,'/* Actual UNIXTTY owns error in this profile. */\n')
 if name=='standalone-startup-probe.c':
  for line in ['void pline(const char *fmt,...){abort();}\n','void raw_printf(const char *fmt,...){abort();}\n','void impossible(const char *fmt,...){size_t n=strlen(diagnostics);va_list ap;va_start(ap,fmt);vsnprintf(diagnostics+n,sizeof diagnostics-n,fmt,ap);va_end(ap);}\n']:
   if body.count(line)!=1:raise SystemExit('Review changed message fixture')
   body=body.replace(line,'/* Actual PLINE owns this entry in this profile. */\n')
 if name=='standalone-display-startup-probe.c':
  decl=json.loads((root/'js/nethack/decl-storage.json').read_text())['globals']
  body+='\nconst volatile void *probe_decl_global(int i){switch(i){'+''.join('case '+str(i)+':return &'+row['name']+';' for i,row in enumerate(decl))+'}return NULL;}\n'
 target=out/name;target.write_text(body);fixtures.append(source)
sources=[out/'standalone-armor-actions-native.c',out/'standalone-equipment-startup-probe.c',out/'standalone-inventory-startup-probe.c',out/'standalone-window-startup-probe.c',out/'standalone-level-rng-probe.c',out/'standalone-windows-native.c',out/'standalone-wintty-native.c',out/'standalone-banner-version-native.c',out/'standalone-banner-options-native.c',out/'standalone-status-native.c',out/'standalone-status-sounds-native.c',out/'standalone-movement-native.c',tree/'sys/share/posixregex.c',*[tree/f'src/{n}.c' for n in names],tree/'sys/unix/unixmain.c',tree/'win/tty/termcap.c',tree/'win/tty/getline.c',tree/'win/tty/topl.c',tree/'sys/share/unixtty.c',tree/'sys/share/ioctl.c',ref/'nethack-c/wasm/compress-service.c',ref/'nethack-c/wasm/bridge.c']
sources.extend(p for p in sorted((tree/'lib/lua-5.4.8/src').glob('*.c')) if p.stem not in ['lua','luac','onelua'])
window=json.loads((root/'js/nethack/window-abi.json').read_text())
for module in ['windows','wintty']:
 names_cb=sorted(window['callbacks'][module]);(out/(module+'-callbacks.inc')).write_text(''.join('case '+str(i)+':return (uintptr_t)('+name+');\n'for i,name in enumerate(names_cb)))
 (out/(module+'-callbacks.json')).write_text(json.dumps(names_cb,indent=2)+'\n')
globals=list(window['wintty']['schema']['globals']);owned=set(window['wintty']['dataTypes'])|set(window['wintty']['zeroStorage'])
(out/'wintty-globals.inc').write_text(''.join('case '+str(i)+':return &'+name+';\n'for i,name in enumerate(globals)))
(out/'wintty-sizes.inc').write_text(''.join('case '+str(i)+':return sizeof('+name+');\n'for i,name in enumerate(globals)if name in owned))
movement=json.loads((root/'js/nethack/hack-abi.json').read_text())
(out/'movement-callbacks.inc').write_text(''.join('case '+str(i)+':return (uintptr_t)('+name+');\n'for i,name in enumerate(movement['functions'])))
options=json.loads((root/'nethack-c/wasm/tu-fragments/options-schema.json').read_text())
(out/'options-functions.inc').write_text(''.join('case '+str(i)+':return (uintptr_t)('+name+');\n'for i,name in enumerate(options['functionAddresses'])))
armor_path=root/'js/nethack/armor-abi.json'
armor_snapshot=armor_path.read_bytes();armor=json.loads(armor_snapshot)
assert len(armor['callbacks'])>=14
for name in armor['callbacks'][:14]:
 assert armor['callbackTypes'][name]=='int (void)',name
(out/'armor-callbacks.inc').write_text(''.join('case '+str(i)+':return (uintptr_t)('+name+');\n'for i,name in enumerate(armor['callbacks'])))
flags=['-Wl,--wrap=com_pager','-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(out),'-I'+str(tree/'win/tty'),'-I'+str(root/'scripts'),'-I'+str(root/'nethack-c/wasm'),'-I'+str(root/'nethack-c/wasm/tu-fragments'),'-I'+str(tree/'src'),'-I'+str(tree/'lib/lua-5.4.8/src'),'-O2','-g','-sMEMORY64=1','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sEXPORTED_RUNTIME_METHODS=HEAPU8,FS','--no-entry','-Wl,--error-limit=0',
 *['-D'+d for d in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())],'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),'-fmacro-prefix-map='+str(tree/'src')+'/=']
exports=['probe_equipment_callback','probe_equipment_after','setworn','setnotworn','wearslot','welded','mwelded','wearmask_to_obj','wornmask_to_armcat','armcat_to_wornmask','cancel_doff','reset_remarm','u_init_skills_discoveries','find_ac','skill_init','weapon_type','initoptions','probe_first_display_matrix','vision_recalc','vision_reset','do_light_sources','can_reach_floor','sticks','probe_inventory_macro','u_init_inventory_attrs','init_attr','vary_init_attr','hidden_gold','makedog','initedog','set_apparxy','see_monster_closeup','acurr','probe_movement_callback','probe_movement_room','probe_movement_cell','probe_movement_update','check_special_room','in_rooms','in_town','rounddiv','uint_to_any','long_to_any','monst_to_any','obj_to_any','weight_cap','inv_weight','calc_capacity','near_capacity','max_capacity','inv_cnt','money_cnt','init_sound_disp_gamewindows','status_initialize','status_finish','probe_status_storage','probe_status_size','probe_status_callback','probe_status_sound','probe_banner_options_copy','probe_banner_options_function','probe_version_storage','probe_banner_options_storage','copyright_banner_line','version_string','getversionstring','status_version','get_critical_size_count','get_feature_notice_ver','get_current_feature_ver','set_wc2_option_mod_status','set_wc_option_mod_status','set_option_mod_status','gettty','setftty','intron','introff','getwindowsz','getioctls','setioctls','tty_utf8graphics_fixup','probe_unix_terminal_storage','probe_tty_speed','probe_tty_pathconf','probe_tty_errno','probe_window_select','probe_window_init','probe_window_table','probe_windows_callback','probe_windows_storage','probe_wintty_callback','probe_wintty_global','probe_wintty_owned_size','probe_buffer_open','probe_buffer_capacity','probe_buffer_pending','probe_buffer_put','probe_buffer_write','probe_buffer_flush','probe_buffer_close','probe_tty_attr','probe_tty_setattr','probe_tty_winsize','malloc','free','probe_startup_init','probe_startup_role_config','probe_startup_role','probe_startup_newgame','probe_startup_global','probe_startup_diagnostics','probe_startup_dungeons','probe_dungeon_global','nh_getenv','getenv','setenv','unsetenv','probe_hero_init','probe_hero_global','probe_hero_layout','probe_hero_roleplay','lua_getglobal','lua_getfield','lua_type','lua_settop','lua_tolstring','lua_tointegerx','has_color','probe_display_reset','probe_display_global','probe_display_layout','probe_display_config','probe_signal_pointer','probe_signal_set','probe_signal_reset','probe_signal_seen','probe_signal_errno','probe_decl_global','probe_signal_global','probe_signal_set_token','sigaction','signal','raise','probe_level_init','probe_level_rng_pointer','probe_level_reseed','probe_level_rng_state','probe_level_rng_initialized','probe_level_rng_layout','rn2','rn2_on_display_rng','sys_random_seed','mklev','getbones']
exports.extend(['vision_init','probe_vision_storage','probe_vision_storage_size'])
exports.extend(['probe_contents_layout_count','probe_contents_layout_name','probe_contents_layout_value'])
exports.extend(['probe_contents_trap','probe_contents_traps','probe_contents_room_query'])
exports.extend(['selection_new','selection_free','selection_clear','selection_clone','selection_getbounds','selection_getpoint','selection_setpoint','selection_not','selection_filter_percent','selection_rndcoord','selection_do_grow','selection_do_line','selection_do_randline','selection_do_ellipse','selection_do_gradient','selection_from_mkroom'])
cmd=[str(ref/'.cache/emsdk/upstream/emscripten/emcc'),*flags,'--js-library',str(ref/'nethack-c/wasm/native-libc-library.js'),'-sEXPORTED_FUNCTIONS='+json.dumps(['_'+n for n in exports]),*[str(s) for s in sources],str(ref/'.cache/ncurses-wasm64-build/lib/libtinfo.a'),'-o',str(out/'reference.mjs')]
sys.dont_write_bytecode=True
from standalone_c_boundaries import build
result,cmd,boundaries=build(cmd,flags,sources,root,ref,out,headers=("sp_lev.h","region.h","wintty.h"))
(out/'build.log').write_text(result.stdout+result.stderr);(out/'command.json').write_text(json.dumps(cmd,indent=2)+'\n')
if result.returncode:raise SystemExit(result.stderr[-6000:])
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
assert armor_path.read_bytes()==armor_snapshot,'Armor ABI changed while generating callback reference'
inputs=[armor_path,out/'armor-callbacks.inc',root/'js/nethack/hack-abi.json',root/'nethack-c/wasm/tu-fragments/options-schema.json',ref/'nethack-c/wasm/native-terminal.h',ref/'nethack-c/wasm/native-libc-library.js',root/'js/platform/darwin/terminal.js',root/'js/platform/darwin/terminal-abi.json',*[ref/'.cache/emsdk/upstream/emscripten'/p for p in ['src/lib/libtty.js','src/lib/libsyscall.js','system/lib/libc/musl/src/stdio/setvbuf.c','system/lib/libc/musl/src/stdio/setbuf.c','system/lib/libc/musl/src/stdio/fwrite.c','system/lib/libc/musl/src/stdio/__stdio_write.c','system/lib/libc/musl/src/termios/cfgetospeed.c','system/lib/libc/musl/src/termios/tcgetattr.c','system/lib/libc/musl/src/termios/tcsetattr.c','system/lib/libc/musl/src/conf/fpathconf.c']],ref/'.cache/ncurses-wasm64-build/lib/libtinfo.a',Path(__file__).resolve(),root/'scripts/standalone_c_boundaries.py',root/'js/nethack/decl-storage.json',root/'js/nethack/window-abi.json',*fixtures,*sources,ref/'.cache/emsdk/upstream/emscripten/system/lib/libc/sigaction.c',ref/'.cache/emsdk/upstream/emscripten/system/lib/libc/raise.c',ref/'.cache/emsdk/upstream/emscripten/system/lib/libc/musl/src/signal/signal.c',root/'nethack-c/wasm/compile-defines.json',ref/'.cache/wasm64-build/assets/sysconf',tree/'dat/nhlib.lua',tree/'dat/dungeon.lua',tree/'dat/nhcore.lua',*sorted((tree/'dat').glob('*.lua')),*[tree/'dat'/name for name in ['epitaph','engrave','rumors','bogusmon','oracles']]]
for source in sources:
 deps=subprocess.run([cmd[0],*flags,'-M',str(source)],capture_output=True,text=True,check=True)
 inputs.extend(Path(p).resolve() for p in shlex.split(deps.stdout.split(':',1)[1].replace('\\\n','')))
(out/'receipt.json').write_text(json.dumps({'sourceSha256':{str(p):sha(p)for p in sorted(set(inputs))},'artifactSha256':{p.name:sha(p)for p in [out/'reference.mjs',out/'reference.wasm',out/'windows-callbacks.json',out/'wintty-callbacks.json',out/'armor-callbacks.inc']},'externalBoundaries':boundaries,'observationBoundary':'Link wrapper aborts at original ALLMAIN call to com_pager, after original u_init_skills_discoveries (including gear, skills, discovery and armor class). The wrapped function does not run; no C policy body changes. Observer flushes stdout on both sides.', 'equipmentActions':'Original DO_WEAR included alone in its native observation owner, exposing actual private callback identities; callback assignment helper accepts null or source int(void) callbacks0..13. Public WORN/WIELD/DO_WEAR operations execute unchanged C bodies.','profile':'Original configured memory64 VISION (included original owner) /TRAP/MKROOM/ZAP/MKLEV/BONES/RECT/REGION/STAIRS/RND plus WINDOWS/DISPLAY/signals/hero/attributes/energy/form/hunger/clock startup plus DECL/role/dungeon/NHLUA/NHLSEL/NHLOBJ/SP_LEV/SELVAR/FILES plus original Lua5.4.8 source; WINDOWS owns original default callback storage; unconnected function boundaries abort.'},indent=2)+'\n')
print('Built original-C equipment-actions reference: '+str(out))
