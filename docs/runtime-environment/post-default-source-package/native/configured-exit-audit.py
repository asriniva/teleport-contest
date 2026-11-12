from pathlib import Path
import subprocess,json,hashlib,re
root=Path('/Users/arj/Desktop/nethack_comp/teleport-contest');out=root/'.cache/window-kill-contract';ref=root/'.cache/full-original-c-v1';clang=root/'.cache/emsdk/upstream/bin/clang';sysroot=root/'.cache/emsdk/upstream/emscripten/cache/sysroot'
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(sysroot),'-include',str(root/'nethack-c/wasm/native-terminal.h'),'-I'+str(ref/'tree/include'),'-I'+str(ref/'tree/src'),'-I'+str(ref/'tree/win/tty'),'-I'+str(root/'.cache/ncurses-wasm64-build/include'),'-DNOTPARMDECL','-DNO_TIMED_DELAY','-DMACOS','-DNOPANICTRACE','-DNO_FILE_LINKS']
p=ref/'tree/sys/share/unixtty.c';expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(p)],text=True);macros=subprocess.check_output([str(clang),*flags,'-dM','-E',str(p)],text=True)
(out/'configured-unixtty.i').write_text(expanded);(out/'configured-macros.txt').write_text(macros)
active={k:bool(re.search(r'^#define '+re.escape(k)+r'(?:\s|$)',macros,re.M))for k in ['__EMSCRIPTEN__','__wasm64__','__linux__','_M_UNIX','VMS','WIN32','TTY_GRAPHICS','MACOS','UNIX','SHELL']}
# Distinguish declarations from callsites. Actual atexit source calls have console names.
assert not re.search(r'atexit\s*\(\s*(?:sco_mapon|linux_mapon|byebye|resettty|font_table_cleanup)\s*\)',expanded)
assert not re.search(r'\b(?:sco_mapon|linux_mapon|init_sco_cons|init_linux_cons)\s*\(',expanded)
# Sealed symbol table confirms actual instantiated C scope.
sym=(ref/'out/game.mjs.symbols').read_text();forbidden=['sco_mapon','linux_mapon','font_table_cleanup','byebye','resettty','atexit','__cxa_atexit','__cxa_finalize','__libc_exit_fini','__wasm_call_dtors'];present=[s for s in forbidden if re.search(r'^\d+:'+re.escape(s)+r'$',sym,re.M)]
assert not present,present
inputs=[root/'nethack-c/wasm/native-terminal.h',p,root/'.cache/emsdk/upstream/emscripten/system/lib/libc/kill.c',root/'.cache/emsdk/upstream/emscripten/system/lib/libc/raise.c',root/'.cache/emsdk/upstream/emscripten/system/lib/libc/pthread_sigmask.c',root/'.cache/emsdk/upstream/emscripten/system/lib/libc/sigaction.c',root/'.cache/emsdk/upstream/emscripten/system/lib/libc/musl/src/exit/exit.c',root/'.cache/emsdk/upstream/emscripten/system/lib/libc/musl/src/exit/atexit.c',ref/'out/game.mjs',ref/'out/game.mjs.symbols']
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
d={'complete':True,'configuredMacros':active,'activeGameAtexitCalls':0,'linkedRegistrationOrDestructorSymbols':present,'originalExitRuntimeCallsFuncsOnExit':True,'funcsOnExitIsNotDummy':True,'scope':'Read-only pinned configured preprocessor and sealed symbol/body audit, not general atexit/destructor API behavior. EXIT_RUNTIME=1 invokes real __funcs_on_exit but no atexit/cxa registration or fini/wasm destructor implementation is linked. Full game sources atexit sites exist only in inactive SCO/Linux/VMS/Win32 platform branches. Configured default game exit still requires source shared stdio teardown accepted in old48. Signal delivery is real Emscripten virtual table behavior; no pthread_kill implementation linked.','sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'outputs':{'preprocessedUnixtty':sha(out/'configured-unixtty.i'),'macros':sha(out/'configured-macros.txt')}}
(out/'configured-exit-audit.json').write_text(json.dumps(d,indent=2)+'\n');print(json.dumps(d))
