"""Pinned, out-of-tree native helper + wasm64 build; no upstream edits."""
import hashlib
import json
import os
from pathlib import Path
import platform
import shlex
import shutil
import subprocess
import sys
import tarfile

from build_terminfo import build_terminfo, ENTRY_SHA256, NCURSES_SHA256

ROOT = Path(__file__).resolve().parents[2]
SDK = Path(os.environ['EMSDK'])
BUILD = ROOT / '.cache/wasm64-build'
TREE = BUILD / 'tree'
OUT = ROOT / 'js/wasm'
PIN = '16ff59115315917b93185d026aeefea06db9b0f4'
MAKE = shutil.which('gmake') or shutil.which('make')
JOBS = str(min(os.cpu_count() or 2, 8))
C_DEPENDENCIES = '--c-dependencies' in sys.argv
if '--js-lua' in sys.argv and '--c-lua' in sys.argv:
    raise SystemExit('Choose only one of --js-lua and --c-lua')
JS_LUA = '--c-lua' not in sys.argv and (not C_DEPENDENCIES or '--js-lua' in sys.argv)
EMSCRIPTEN_ONLY_PROBES = '--emscripten-only-probes' in sys.argv
DEPENDENCY_BACKEND = 'c' if C_DEPENDENCIES else 'javascript'


def run(args, cwd=TREE, **kw):
    print('+', shlex.join(map(str, args)), flush=True)
    return subprocess.run(list(map(str, args)), cwd=cwd, check=True, **kw)


def replace(file, old, new):
    p = TREE / file
    text = p.read_text()
    assert old in text, (file, old)
    p.write_text(text.replace(old, new))


assert subprocess.check_output(['git', '-C', str(ROOT / 'nethack-c/upstream'), 'rev-parse', 'HEAD'], text=True).strip() == PIN
codec_source = ROOT / 'nethack-c/wasm/vendor/ncompress/compress.c'
codec_source_hash = hashlib.sha256(codec_source.read_bytes()).hexdigest()
assert codec_source_hash == '41f593dcc4e21a3d2686010a554687231a498291268791c8db412bf5b5e5087f'
assert hashlib.sha256((codec_source.parent / 'patchlevel.h').read_bytes()).hexdigest() == '222354c13eb9c345feaf8d692f897f8ad05e12c10468f0693c56491d1ad35692'
compiler = subprocess.check_output([str(SDK / 'upstream/bin/clang'), '--version'], text=True)
assert 'clang version 21.0.0' in compiler, compiler
assets = BUILD / 'assets'
if '--resume' not in sys.argv:
    if BUILD.exists():
        shutil.rmtree(BUILD)
    BUILD.mkdir(parents=True)
    shutil.copytree(ROOT / 'nethack-c/upstream', TREE, ignore=shutil.ignore_patterns('.git'))
    run(['git', 'init', '-q'])
    run(['git', 'add', '-A'])
    for patch in sorted((ROOT / 'nethack-c/patches').glob('*.patch')):
        run(['git', 'apply', '--recount', patch])
    shutil.rmtree(TREE / '.git')
    archive = ROOT / '.cache/lua-5.4.8.tar.gz'
    assert hashlib.sha256(archive.read_bytes()).hexdigest() == '4f18ddae154e793e46eeab727c59ef1c0c0c2b744e7b94219710d76f530629ae'
    with tarfile.open(archive) as t:
        t.extractall(TREE / 'lib', filter='data')
    
    # Native data generators use host Clang 21. The SDK Clang build contains
    # only the WebAssembly backend; it cannot compile these host executables.
    host_flags = []
    host_compiler = shutil.which('clang')
    if platform.system() == 'Darwin':
        clt = Path('/Library/Developer/CommandLineTools')
        mac_sdk = clt / 'SDKs/MacOSX.sdk'
        assert mac_sdk.exists(), 'Install Xcode command line tools'
        host_compiler = str(clt / 'usr/bin/clang')
        host_flags = ['-isysroot', str(mac_sdk), '-B' + str(clt / 'usr/bin')]
    host_version = subprocess.check_output([host_compiler, '--version'], text=True)
    assert 'clang version 21.' in host_version, 'Host data generators require Clang 21: ' + host_version
    host_cc = BUILD / 'host-cc'
    host_cc.write_text('#!/bin/sh\nexec ' + shlex.join([host_compiler, *host_flags]) + ' "$@"\n')
    host_cc.chmod(0o755)
    # Explicitly use GNU make for recursive and Lua make invocations too.
    bin_dir = BUILD / 'bin'
    bin_dir.mkdir()
    (bin_dir / 'make').symlink_to(MAKE)
    os.environ['PATH'] = str(bin_dir) + os.pathsep + (str(clt / 'usr/bin') + os.pathsep if platform.system() == 'Darwin' else '') + os.environ['PATH']
    os.environ['CC'] = str(host_cc)
    os.environ['SOURCE_DATE_EPOCH'] = '1777723200'
    os.environ['TZ'] = 'UTC'
    install = BUILD / 'install'
    hints = (ROOT / 'nethack-c/macosx-minimal').read_text().replace('__NETHACK_PREFIX__', str(install))
    hints += f'\nCC={host_cc}\nSYSCFLAGS=-DLUA_USE_POSIX\n'
    (TREE / 'sys/unix/hints/teleport-host').write_text(hints)
    run(['sh', 'sys/unix/setup.sh', 'sys/unix/hints/teleport-host'])
    run([MAKE, '-j' + JOBS, 'install'])
    assets = BUILD / 'assets'
    shutil.copytree(install / 'games/lib/nethackdir', assets)
    for name in ['nethack', 'recover']:
        (assets / name).unlink(missing_ok=True)
    
    # Keep TERMINFO/TERMLIB and all native termcap logic unchanged.
    # Adapt only replay input and capture transport here.
    replace('include/unixconf.h', '#define tgetch getchar', '#ifdef __EMSCRIPTEN__\nextern int teleport_getch(void);\n#define tgetch teleport_getch\n#else\n#define tgetch getchar\n#endif')
    replace('win/tty/termcap.c', '#include "tcap.h"', '#include "tcap.h"\n#ifdef __EMSCRIPTEN__\nextern void teleport_capture(const char *, int, int, int);\n#endif')
    replace('win/tty/termcap.c', 'nomux_get_cursor(&cx, &cy);\n        fprintf', 'nomux_get_cursor(&cx, &cy);\n#ifdef __EMSCRIPTEN__\n        fflush(NULL);\n        teleport_capture(scr, cx, cy, !strcmp(kind, "anim"));\n        return;\n#endif\n        fprintf')
    replace('sys/unix/unixmain.c', 'get_unix_pw(void)\n{\n', 'get_unix_pw(void)\n{\n#ifdef __EMSCRIPTEN__\n    /* Emscripten passwd lookups are ENOENT stubs. Supply the virtual\n     * Unix account used by the recorder; keep sysconf authorization. */\n    static struct passwd virtual_user = { .pw_name = "root", .pw_uid = 0,\n        .pw_gid = 0, .pw_dir = "/home/player", .pw_shell = "/bin/sh" };\n    return &virtual_user;\n#endif\n')
    replace('src/calendar.c', '(void) time((TIME_type) &now);\n        lt = localtime((LOCALTIME_type) &now);', '(void) time((TIME_type) &now);\n#ifdef __EMSCRIPTEN__\n        /* Reproduce the recorder parser using a fixed recording clock,\n         * retaining its inherited DST flag and the process timezone. */\n        const char *recording_epoch = nh_getenv("NETHACK_RECORDING_EPOCH");\n        if (recording_epoch && *recording_epoch)\n            now = (time_t) strtoll(recording_epoch, (char **) 0, 10);\n#endif\n        lt = localtime((LOCALTIME_type) &now);')
    replace('include/global.h', '#ifdef __APPLE__\n#define PORT_ID "MacOS"', '#if defined(__APPLE__) || (defined(__EMSCRIPTEN__) && defined(MACOS))\n#define PORT_ID "MacOS"')
    replace('include/global.h', '/* Supply nethack_enter macro if not supplied by port */', '#ifdef __EMSCRIPTEN__\n/* Keep the feature/UI while disabling unavailable native stack walkers. */\n#undef PANICTRACE_LIBC\n#undef PANICTRACE_GDB\n#endif\n\n/* Supply nethack_enter macro if not supplied by port */')
    replace('src/report.c', '# ifdef MACOS\n#include <CommonCrypto/CommonDigest.h>', '# if defined(MACOS) && !defined(__EMSCRIPTEN__)\n#include <CommonCrypto/CommonDigest.h>')
    replace('src/report.c', '# ifdef __linux__', '# if defined(__linux__) || defined(__EMSCRIPTEN__)')
    replace('src/report.c', '# else\n        void *bt[SWR_FRAMES];', '# elif !defined(__EMSCRIPTEN__)\n        void *bt[SWR_FRAMES];')
    # Keep NetHack's configured .Z format and existing success/failure cleanup.
    # Replace only process creation/waiting with the in-process codec status.
    replace('src/files.c', '    f = fork();', '#ifdef __EMSCRIPTEN__\n    extern int teleport_compress_file(const char *, const char *, int);\n    childstatus = teleport_compress_file(filename, cfn, uncomp);\n#else\n    f = fork();')
    replace('src/files.c', '    if (childstatus == 0) {', '#endif /* native subprocess / in-process Wasm codec */\n    if (childstatus == 0) {')
    # Match macOS game features; native-only APIs are adapted in bridge.c.
os.environ['PATH'] = str(BUILD / 'bin') + os.pathsep + ('/Library/Developer/CommandLineTools/usr/bin:' if platform.system() == 'Darwin' else '') + os.environ['PATH']
os.environ['SOURCE_DATE_EPOCH'] = '1777723200'
os.environ['TZ'] = 'UTC'
# Native debugger paths are not applicable to a Wasm module. Keep all other
# sysconf defaults, including the macOS-visible options and authorization.
sysconf = (TREE / 'sys/unix/sysconf').read_text()
sysconf = '\n'.join('# wasm: ' + line if line.startswith(('GDBPATH=', 'GREPPATH=')) else line for line in sysconf.split('\n'))
(assets / 'sysconf').write_text(sysconf)
terminfo_include, terminfo_library = build_terminfo(ROOT, SDK, BUILD / 'host-cc', MAKE, JOBS)
shutil.copytree(ROOT / 'nethack-c/wasm/terminfo/x', assets / 'terminfo/x', dirs_exist_ok=True)
defines = json.loads((ROOT / 'nethack-c/wasm/compile-defines.json').read_text())
flags = '-O2 -g -I../include ' + ' '.join('-D' + name for name in defines) + ' -sMEMORY64=1'
flags += ' -I' + shlex.quote(str(terminfo_include))
flags += ' -include ' + shlex.quote(str(ROOT/'nethack-c/wasm/native-terminal.h'))
native_abi_hash=hashlib.sha256((ROOT/'nethack-c/wasm/native-terminal.h').read_bytes()).hexdigest()
native_abi_stamp=BUILD/'native-abi.sha256'
if not native_abi_stamp.exists() or native_abi_stamp.read_text().strip()!=native_abi_hash:
    # All game objects depend on this common header. A changed forced ABI
    # include must invalidate objects built with the previous SDK types.
    os.utime(TREE/'include/global.h',None)
emcc = SDK / 'upstream/emscripten/emcc'
emar = SDK / 'upstream/emscripten/emar'
lua = TREE / 'lib/lua-5.4.8/src'
wasm_lua = BUILD / 'liblua-wasm64.a'
# Original-C quest fixtures need an independent Lua archive even when the
# selected game uses JavaScript Lua. It is not a game link input in that mode.
if not JS_LUA or not wasm_lua.exists():
    run([MAKE, 'clean'], cwd=lua)
    run([MAKE, '-j' + JOBS, 'a', f'CC={emcc}', f'AR={emar} rcu', f'RANLIB={SDK}/upstream/emscripten/emranlib', 'MYCFLAGS=-O2 -sMEMORY64=1', 'SYSCFLAGS=-DLUA_USE_POSIX'], cwd=lua)
    shutil.copy2(lua / 'liblua.a', wasm_lua)
(TREE / 'src/wasm').mkdir(exist_ok=True)
bridge = TREE / 'src/wasm/bridge.o'
run([emcc, '-O2', '-sMEMORY64=1', '-c', ROOT / 'nethack-c/wasm/bridge.c', '-o', bridge])
dependency_objects = []
if JS_LUA:
    lua_bridge = TREE / 'src/wasm/lua-bridge.o'
    run([emcc, '-O2', '-g', '-std=gnu17', '-sMEMORY64=1', '-I' + str(lua),
         '-c', ROOT / 'nethack-c/wasm/lua-bridge.c', '-o', lua_bridge])
    dependency_objects.append(lua_bridge)
os.environ['TELEPORT_JS_REGEX'] = '0' if C_DEPENDENCIES else '1'
if C_DEPENDENCIES:
    codec = TREE / 'src/wasm/compress-service.o'
    run([emcc, '-O2', '-std=gnu17', '-sMEMORY64=1', '-c', ROOT / 'nethack-c/wasm/compress-service.c', '-o', codec])
    dependency_objects.append(codec)
else:
    # Keep ncurses' real headers/configuration. Only the linked implementation
    # changes: byte/string algorithms are JS, with narrowly scoped C ABI shims.
    dependency_bridge = TREE / 'src/wasm/dependency-bridge.o'
    run([emcc, '-O2', '-g', '-std=gnu17', '-sMEMORY64=1', '-DTELEPORT_JS_REGEX=1',
         '-c', ROOT / 'nethack-c/wasm/dependency-bridge.c', '-o', dependency_bridge])
    dependency_objects.append(dependency_bridge)
OUT.mkdir(exist_ok=True)
ports = json.loads((ROOT / 'nethack-c/wasm/tu-ports.json').read_text())
nhlua_transport_flags = (['-I'+str(ROOT/'scripts'), '-I'+str(ROOT/'nethack-c/wasm/tu-fragments'), '-sSUPPORT_LONGJMP=emscripten'] if any(port['name']=='nhlua' for port in ports) else [])
tu_support = TREE / 'src/wasm/tu-support.o'
run([sys.executable, '-B', ROOT / 'scripts/write-tu-source-metadata.py'], cwd=ROOT)
run([emcc, *shlex.split(flags), *nhlua_transport_flags, '-I' + str(TREE / 'include'), '-I' + str(ROOT / '.cache/tu-probes'), '-c', ROOT / 'nethack-c/wasm/tu-support.c', '-o', tu_support])
dependency_mode = BUILD / 'dependency-mode.js'
link_flags = shlex.join([str(bridge), *map(str, dependency_objects), str(tu_support), '-O2', '-g', '-sMEMORY64=1', '-sMODULARIZE=1', '-sEXPORT_ES6=1', '-sENVIRONMENT=node,web', '-sINVOKE_RUN=0', '-sEXIT_RUNTIME=1', '-sALLOW_MEMORY_GROWTH=1', '-sSTACK_SIZE=4194304', '-sEXPORTED_RUNTIME_METHODS=FS,ENV,callMain', '--emit-symbol-map', '--post-js', str(ROOT / 'nethack-c/wasm/runtime.js'), '--post-js', str(dependency_mode), '--embed-file', str(assets) + '@/nethack'])
if not C_DEPENDENCIES:
    link_flags += ' --js-library ' + shlex.quote(str(ROOT / 'nethack-c/wasm/dependency-library.js'))
if JS_LUA:
    link_flags += ' --js-library ' + shlex.quote(str(ROOT / 'nethack-c/wasm/lua-library.js'))
link_flags += ' --js-library ' + shlex.quote(str(ROOT / 'nethack-c/wasm/native-libc-library.js'))
if nhlua_transport_flags:
    link_flags += ' -sSUPPORT_LONGJMP=emscripten'
if 'wasm/hacklib.a: wasm/hacklib.o' not in (TREE / 'src/Makefile').read_text():
    with (TREE / 'src/Makefile').open('a') as f:
        f.write('\nwasm/hacklib.a: wasm/hacklib.o\n\t' + str(emar) + ' rcs $@ $<\n')
# Sequentially gated whole-TU ports. The excluded object has no C fallback.
# The registry was read before compiling source-owned typed transport.
# Keep JS-initialized const storage separate from every C reader. Otherwise
# frontend optimization can fold zero fields before JavaScript initialization.
for port in ports:
    for storage in port.get('nativeStorageSources', []):
        assert not any(flag.startswith('-flto') for flag in shlex.split(flags)), 'JS-initialized const backing requires separate non-LTO storage'
        storage_object = TREE / 'src/wasm' / (Path(storage['source']).stem + '.o')
        run([emcc, *shlex.split(flags), *['-D' + define for define in storage.get('defines', [])],
             '-I' + str(TREE / 'include'), '-c', ROOT / storage['source'], '-o', storage_object])
        link_flags += ' ' + shlex.quote(str(storage_object))
regex_transport = ('ported-posixregex-direct-js' if any(port['name'] == 'posixregex' for port in ports)
                   else 'compiled-libc' if C_DEPENDENCIES else 'wasm-libc-js-bridge')
dependency_mode.write_text("Module['nethackDependencyBackend'] = " + json.dumps(DEPENDENCY_BACKEND)
                           + ";\nModule['nethackRegexTransport'] = " + json.dumps(regex_transport)
                           + ";\nModule['nethackLuaBackend'] = " + json.dumps('javascript' if JS_LUA else 'c') + ';\n')
makefile = TREE / 'src/Makefile'
text = makefile.read_text()
start, end = '# BEGIN JAVASCRIPT TUS', '# END JAVASCRIPT TUS'
if start in text:
    before, _, tail = text.partition(start)
    _, _, after = tail.partition(end)
    text = before + after
objects = ' '.join('$(TARGETPFX)' + Path(port['source']).stem + '.o' for port in ports)
archive_exclusions = 'TARGET_HACKLIB :=\n' if any(port['name'] == 'hacklib' for port in ports) else ''
text += f'\n{start}\nifeq ($(TARGETPFX),wasm/)\nHOBJ := $(filter-out {objects},$(HOBJ))\nDATE_O := $(filter-out {objects},$(DATE_O))\n{archive_exclusions}endif\n.PHONY: teleport-link-objects\nteleport-link-objects:\n\t@$(foreach obj,$(HOBJ) $(DATE_O) $(TARGET_HACKLIB),echo $(obj);)\n{end}\n'
makefile.write_text(text)
run([sys.executable, '-B', ROOT / 'scripts/build-tu-probes.py',
     *(['--emscripten-only'] if EMSCRIPTEN_ONLY_PROBES else [])], cwd=ROOT)
run(['node', ROOT / 'scripts/write-tu-layouts.mjs'], cwd=ROOT)
startups = [port['startup'] for port in ports if port.get('startup')]
if startups:
    link_flags += ' ' + shlex.quote('-sDEFAULT_LIBRARY_FUNCS_TO_INCLUDE=' + json.dumps(startups).replace('$', '$$'))
for port in ports:
    link_flags += ' --js-library ' + shlex.quote(str(ROOT / port['library']))
link_objects = run([MAKE, '-s', 'teleport-link-objects', 'TARGETPFX=wasm/'], cwd=TREE / 'src', capture_output=True, text=True).stdout
for port in ports:
    assert 'wasm/' + Path(port['source']).stem + '.o' not in link_objects.splitlines()
    if port['name'] == 'hacklib':
        assert 'wasm/hacklib.a' not in link_objects.splitlines()
(OUT / 'link-objects.txt').write_text(link_objects)
# Component probes retain every original library entry. Before the normal link,
# compile its current C inputs so pruning checks their actual undefined symbols.
link_targets = link_objects.splitlines()
assert link_targets and all(target.startswith('wasm/') and target.endswith(('.o', '.a')) for target in link_targets)
run([MAKE, '-j' + JOBS, *link_targets, 'TARGETPFX=wasm/',
     f'TARGET_CC={emcc}', f'TARGET_CFLAGS={flags}'], cwd=TREE / 'src')
library_pruning = BUILD / 'production-library-pruning'
library_pruning.mkdir(exist_ok=True)
library_tokens = shlex.split(link_flags)
library_inputs = [library_tokens[i + 1] for i, token in enumerate(library_tokens) if token == '--js-library']
library_input_file = library_pruning / 'inputs.json'
library_input_file.write_text(json.dumps(library_inputs, indent=2) + '\n')
native_inputs = [str(TREE / 'src' / target) for target in link_targets]
native_inputs += [token for token in library_tokens if not token.startswith('-') and token.endswith(('.o', '.a'))]
if not JS_LUA:
    native_inputs.append(str(wasm_lua))
if C_DEPENDENCIES:
    native_inputs.append(str(terminfo_library))
native_inputs = list(dict.fromkeys(native_inputs))
assert all(Path(path).is_absolute() and Path(path).is_file() for path in native_inputs), 'Missing current normal-link native input'
native_input_file = library_pruning / 'native-inputs.json'
native_input_file.write_text(json.dumps(native_inputs, indent=2) + '\n')
run(['node', ROOT / 'scripts/write-game-library-pruner.mjs',
     '--libraries-json', library_input_file, '--native-inputs-json', native_input_file,
     '--output-dir', library_pruning], cwd=ROOT)
link_flags += ' --js-library ' + shlex.quote(str(library_pruning / 'normal-link-pruner.js'))
library_pruning_manifest = json.loads((library_pruning / 'normal-link-pruner-manifest.json').read_text())
assert library_pruning_manifest['nativeDemand']['verified'] is True
assert library_pruning_manifest['nativeDemand']['inputs'] == native_inputs
assert library_pruning_manifest['nativeDemand']['requiredRemoved'] == []
(TREE / 'src/Sysunix').unlink(missing_ok=True)
run([MAKE, '-j' + JOBS, 'nethack', 'TARGETPFX=wasm/', f'TARGET_CC={emcc}', f'TARGET_CFLAGS={flags}', f'TARGET_LINK={emcc}', f'TARGET_LFLAGS={link_flags}', f'GAMEBIN={OUT}/nethack.mjs', f'LUALIBS={"" if JS_LUA else wasm_lua} -lm', f'WINLIB={terminfo_library if C_DEPENDENCIES else ""}', 'TARGET_LIBS=', 'AUTOLIBS='], cwd=TREE / 'src')
lua_sources = sorted({str(path.relative_to(ROOT)) for path in (ROOT / 'js/lua').rglob('*.js')}
                     | {'js/c-runtime/float-format.js', 'nethack-c/wasm/lua-library.js', 'js/platform/darwin/strftime.js', 'js/platform/timezone/tzdb.js', 'nethack-c/wasm/lua-bridge.c', 'js/platform/darwin/calendar.js', 'js/platform/timezone/info.js'})
dependency_sources = [
    'js/libraries/compress/unix-z.js', 'js/libraries/terminfo/index.js', 'js/libraries/terminfo/data.js',
    'js/libraries/regex/posix.js', 'js/c-runtime/library-bindings.js',
    'js/platform/darwin/compat.js', 'js/c-runtime/regex-abi.js',
    'js/platform/darwin/qsort.js', 'js/c-runtime/time.js',
    'js/backends/emscripten/runtime.js', 'js/ported/posixregex.js',
    'js/nethack/bindings/posixregex.js', 'js/wasm-adapter.js',
    'nethack-c/wasm/tu-libraries/calendar.js',
    'nethack-c/wasm/tu-libraries/posixregex.js',
    'nethack-c/wasm/native-libc-library.js',
    'js/platform/darwin/terminal.js','js/platform/darwin/terminal-abi.json',
    'nethack-c/wasm/native-terminal.h',
    'nethack-c/wasm/dependency-library.js', 'nethack-c/wasm/dependency-bridge.c',
]
regex_backend = ('compiled-musl-TRE-ERE-C-locale' if regex_transport == 'compiled-libc'
                 else 'javascript-native-macos-compatible-ERE-C-locale')
regex_reference = ('Emscripten musl TRE; REG_EXTENDED|REG_NOSUB; C locale'
                   if regex_transport == 'compiled-libc'
                   else 'Native macOS ERE behavior; REG_EXTENDED|REG_NOSUB; C locale')
# C-dependency debug builds can still select the separately translated regex TU.
# Record its active JS implementation without claiming JS terminfo/compression.
regex_sources = [
    'js/libraries/regex/posix.js', 'js/c-runtime/regex-abi.js',
    'js/backends/emscripten/runtime.js', 'js/ported/posixregex.js',
    'js/nethack/bindings/posixregex.js', 'js/wasm-adapter.js',
    'nethack-c/wasm/tu-libraries/posixregex.js',
    'nethack-c/wasm/native-libc-library.js',
]
c_debug_regex_dependencies = ({
    'sourceSha256': {path: hashlib.sha256((ROOT / path).read_bytes()).hexdigest() for path in regex_sources},
    'regexReference': regex_reference,
    'bridge': 'direct NetHack JS regex wrappers; opaque per-Module regex handles',
} if regex_transport == 'ported-posixregex-direct-js' else {})
manifest = {
    'normalGameLibraryPruning': {
        'scope': 'Normal final link only; original component libraries and source policy unchanged',
        'manifest': str((library_pruning / 'normal-link-pruner-manifest.json').relative_to(ROOT)),
        'removedEntries': library_pruning_manifest['removedEntries'],
        'sourceSha256': {
            **library_pruning_manifest['sourceSha256'],
            **{str(path.relative_to(ROOT)): hashlib.sha256(path.read_bytes()).hexdigest() for path in [
                ROOT / 'scripts/write-game-library-pruner.mjs', ROOT / 'scripts/reviewed_build_provenance.py',
                ROOT / 'nethack-c/wasm/build.py', library_input_file, native_input_file,
                library_pruning / 'normal-link-pruner.js', library_pruning / 'normal-link-pruner-manifest.json']},
        },
    },
    'probeBuildBackends': ['emscripten-reference', 'emscripten-hybrid']
        + ([] if EMSCRIPTEN_ONLY_PROBES else ['native-c']),
    'nativeAbiSha256': native_abi_hash,
    'upstream': PIN, 'emscripten': '4.0.10', 'clang': compiler.strip(), 'memory64': 1,
    'dependencyBackend': DEPENDENCY_BACKEND,
    'lua': 'javascript-lua-5.4.8-bytecode' if JS_LUA else 'compiled-c-lua-5.4.8',
    'luaBackend': 'javascript' if JS_LUA else 'c',
    'javascriptLua': {'sourceSha256': {path: hashlib.sha256((ROOT / path).read_bytes()).hexdigest() for path in lua_sources},
                      'reference': 'Native macOS Lua 5.4.8; original NetHack sandbox policy and C callbacks',
                      'abi': 'memory64 C stack/callback transport; algorithms in JavaScript'} if JS_LUA else None,
    'terminalCapabilities': 'ncurses-6.5-terminfo' if C_DEPENDENCIES else 'javascript-terminfo-pinned-entry',
    'ncursesSha256': NCURSES_SHA256,
    'ncursesRole': 'runtime-library' if C_DEPENDENCIES else 'headers-and-reference-only',
    'terminfoEntrySha256': ENTRY_SHA256,
    'compression': 'ncompress-5.0-in-process-LZW-Z' if C_DEPENDENCIES else 'javascript-ncompress-5.0-LZW-Z',
    'compressionSourceSha256': codec_source_hash,
    'compressionSourceRole': 'compiled-runtime' if C_DEPENDENCIES else 'reference-only',
    'regex': regex_backend,
    'regexTransport': regex_transport,
    'javascriptDependencies': c_debug_regex_dependencies if C_DEPENDENCIES else {
        'sourceSha256': {path: hashlib.sha256((ROOT / path).read_bytes()).hexdigest() for path in dependency_sources},
        'compressionReference': 'public-domain ncompress 5.0, block-mode 16-bit .Z',
        'terminfoReference': 'ncurses 6.5 termcap API; unchanged pinned xterm-256color entry',
        'regexReference': regex_reference,
        'abiCompileFlags': ['-std=gnu17', '-sMEMORY64=1', '-DTELEPORT_JS_REGEX=1'],
        'linkEnvironment': {'TELEPORT_JS_REGEX': '1'},
        'bridge': 'numeric tparm intptr_t ABI; batched C tputs callbacks; opaque regex_t handles; MEMFS codec adapter',
    },
    'removedCompiledDependencies': ([] if C_DEPENDENCIES else ['ncompress codec', 'ncurses libtinfo', 'musl TRE regex algorithms'])
        + (['Lua interpreter/compiler/standard libraries'] if JS_LUA else []),
    'gamePlatform': 'MacOS', 'replayDst': 'inherit-native-parser-clock',
    'defaultRecordingEpoch': '1777723200', 'recordingProfile': 'public-recordings-with-environment-overrides',
    'javascriptTranslationUnits': [{**port, **({'nativeStorageSourceSha256': {storage['source']: hashlib.sha256((ROOT / storage['source']).read_bytes()).hexdigest() for storage in port['nativeStorageSources']}} if port.get('nativeStorageSources') else {}), **({'javascriptDataSha256': {path: hashlib.sha256((ROOT / path).read_bytes()).hexdigest() for path in port['data']}} if port.get('data') else {}), 'adapterSourceSha256': {path: hashlib.sha256((ROOT / path).read_bytes()).hexdigest() for path in port.get('adapterSources', [])}, 'sha256': hashlib.sha256((ROOT / port['javascript']).read_bytes()).hexdigest(), 'abiLibrarySha256': hashlib.sha256((ROOT / port['library']).read_bytes()).hexdigest(), 'preparedCSourceSha256': hashlib.sha256((TREE / port['source']).read_bytes()).hexdigest()} for port in ports],
    'sourceDateEpoch': os.environ['SOURCE_DATE_EPOCH'],
    'wasmSha256': hashlib.sha256((OUT / 'nethack.wasm').read_bytes()).hexdigest(),
}
(OUT / 'build.json').write_text(json.dumps(manifest, indent=2) + '\n')
run([sys.executable, '-B', ROOT / 'scripts/check-wasm-provenance.py'], cwd=ROOT)
native_abi_stamp.write_text(native_abi_hash+'\n')
print('Built', OUT / 'nethack.mjs')
