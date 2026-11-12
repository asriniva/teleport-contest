#!/usr/bin/env python3
"""Snapshot the built mixed game and relink selected external dependencies.

Does not run make, rebuild game TUs, or write active game outputs. The manifest
records every copied input; the pending TU registry is deliberately ignored.
"""
import hashlib
import argparse
import json
import os
from pathlib import Path
import shutil
import subprocess

ROOT = Path(__file__).resolve().parents[1]
WORK = ROOT / '.cache/js-dependency-game'
SNAPSHOT = WORK / 'snapshot'
BUILT = ROOT / '.cache/wasm64-build'
SDK = Path(os.environ.get('EMSDK', ROOT / '.cache/emsdk')).resolve()


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    global WORK, SNAPSHOT
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--regex', action='store_true', help='Replace configured musl regex with the JS service too')
    parser.add_argument('--lua', action='store_true', help='Experimental JS Lua; implies --regex and omits liblua')
    parser.add_argument('--base-root', type=Path, help='Read-only coherent checkout/build to snapshot instead of the active checkout')
    parser.add_argument('--lua-snapshot', type=Path, help='Frozen Lua service/ABI overlay checkout (default: current checkout)')
    parser.add_argument('--output', type=Path, help='Distinct output directory (default depends on --regex)')
    args = parser.parse_args()
    source_root = (args.base_root or ROOT).resolve()
    lua_root = (args.lua_snapshot or ROOT).resolve()
    for path in [source_root,lua_root]:
        assert path == ROOT or ROOT in path.parents, 'Input checkout must be inside this workspace'
    built = source_root / '.cache/wasm64-build'
    if args.lua:
        args.regex = True
    WORK = (args.output or ROOT / ('.cache/js-lua-game' if args.lua else '.cache/js-dependency-game-regex' if args.regex else '.cache/js-dependency-game')).resolve()
    assert WORK != ROOT and ROOT in WORK.parents, 'Output must be a separate directory inside the checkout'
    SNAPSHOT = WORK / 'snapshot'
    WORK.mkdir(parents=True, exist_ok=True)
    manifest_path = source_root / 'js/wasm/build.json'
    original_manifest = manifest_path.read_bytes()
    active = json.loads(original_manifest)
    ports = active['javascriptTranslationUnits']
    for port in ports:
        assert digest(source_root / port['javascript']) == port['sha256'], f"Built JS has changed: {port['name']}"
        assert digest(built / 'tree' / port['source']) == port['preparedCSourceSha256'], f"Prepared source changed: {port['name']}"
    for relative, expected in active.get('javascriptDependencies', {}).get('sourceSha256', {}).items():
        assert digest(source_root / relative) == expected, f'Built dependency/ABI source has changed: {relative}; wait for a consistent active build'
    inputs = {}

    def copy(source, destination):
        source, destination = Path(source), Path(destination)
        before = digest(source)
        destination.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(source, destination)
        assert digest(source) == before == digest(destination), f'Concurrent source edit: {source}'
        inputs[str(source.relative_to(ROOT))] = before

    # Preserve the complete prepared source/object tree as evidence, never
    # invoke its makefiles. No hard links: another build may replace objects.
    for source in sorted((built / 'tree').rglob('*')):
        if source.is_file():
            copy(source, SNAPSHOT / 'prepared' / source.relative_to(built / 'tree'))
    for source in sorted((built / 'assets').rglob('*')):
        if source.is_file():
            copy(source, SNAPSHOT / 'assets' / source.relative_to(built / 'assets'))
    for source in sorted((source_root / 'js').glob('*.js')):
        copy(source, SNAPSHOT / 'js' / source.name)
    for directory in ['ported', 'services']:
        for source in sorted((source_root / 'js' / directory).rglob('*')):
            if source.is_file():
                copy(source, SNAPSHOT / 'js' / directory / source.relative_to(source_root / 'js' / directory))
    for port in ports:
        copy(source_root / port['library'], SNAPSHOT / port['library'])
        for data in port.get('data', []):
            copy(source_root / data, SNAPSHOT / data)
    for file in ['js/wasm/build.json', 'js/wasm/link-objects.txt', 'js/wasm/tu-layouts.json', 'js/wasm/drawing-constants.json',
                 'nethack-c/wasm/runtime.js', 'nethack-c/wasm/compile-defines.json',
                 'nethack-c/wasm/dependency-library.js', 'nethack-c/wasm/dependency-bridge.c']:
        copy(source_root / file, SNAPSHOT / file)
    copy(ROOT / 'scripts/build-js-dependency-game.py', SNAPSHOT / 'scripts/build-js-dependency-game.py')
    copy(built / 'liblua-wasm64.a', SNAPSHOT / 'liblua-wasm64.a')
    # Preserve additional ABI libraries selected by the actual built manifest,
    # including concurrent native-libc compatibility work. Their algorithms
    # and selection are independent of this Lua migration.
    extra_libraries = []
    for relative, expected in active.get('javascriptDependencies', {}).get('sourceSha256', {}).items():
        if relative.startswith('nethack-c/wasm/') and relative.endswith('-library.js') and relative != 'nethack-c/wasm/dependency-library.js':
            assert digest(source_root / relative) == expected, f'Built ABI library changed: {relative}'
            copy(source_root / relative, SNAPSHOT / relative)
            extra_libraries.append(relative)
    if args.lua:
        for directory in ['js/lua']:
            for source in sorted((lua_root / directory).rglob('*.js')):
                copy(source, SNAPSHOT / source.relative_to(lua_root))
        for relative in ['js/c-runtime/float-format.js','js/platform/timezone/info.js','js/platform/timezone/tzdb.js','js/platform/darwin/calendar.js','js/platform/darwin/strftime.js']:
            copy(lua_root / relative, SNAPSHOT / relative)
        for file in ['nethack-c/wasm/lua-bridge.c', 'nethack-c/wasm/lua-library.js']:
            copy(lua_root / file, SNAPSHOT / file)
    # Retain the exact original executable for same-baseline performance tests.
    assert digest(source_root / 'js/wasm/nethack.wasm') == active['wasmSha256']
    for filename in ['nethack.mjs', 'nethack.wasm']:
        copy(source_root / 'js/wasm' / filename, SNAPSHOT / 'base-wasm' / filename)
    assert manifest_path.read_bytes() == original_manifest, 'Active build changed while snapshotting; retry after completion'
    for relative, sha256 in inputs.items():
        assert digest(ROOT / relative) == sha256, f'Concurrent input edit: {relative}'
    objects = (SNAPSHOT / 'js/wasm/link-objects.txt').read_text().splitlines()
    assert objects and all(name.endswith(('.o', '.a')) and '..' not in name for name in objects)
    assert not any('compress-service' in name or 'libtinfo' in name for name in objects)
    tree = SNAPSHOT / 'prepared'
    link_inputs = [tree / 'src' / name for name in objects]
    link_inputs += [tree / 'src/wasm/bridge.o', tree / 'src/wasm/tu-support.o']
    assert all(path.is_file() for path in link_inputs)
    for port in ports:
        assert 'wasm/' + Path(port['source']).stem + '.o' not in objects
    environment = dict(os.environ)
    node_bin = SDK / 'node/24.19.0_64bit/bin'
    environment['PATH'] = str(node_bin) + os.pathsep + environment.get('PATH', '')
    environment['EMSDK'] = str(SDK)
    environment['TELEPORT_JS_REGEX'] = '1' if args.regex else '0'
    emcc = SDK / 'upstream/emscripten/emcc'
    bridge = WORK / 'dependency-bridge.o'
    subprocess.run([str(emcc), '-O2', '-g', '-std=gnu17', '-sMEMORY64=1',
                    *(['-DTELEPORT_JS_REGEX=1'] if args.regex else []), '-c',
                    str(SNAPSHOT / 'nethack-c/wasm/dependency-bridge.c'), '-o', str(bridge)],
                   cwd=WORK, env=environment, check=True)
    output = WORK / 'nethack.mjs'
    lua_inputs = [SNAPSHOT / 'liblua-wasm64.a']
    if args.lua:
        lua_bridge = WORK / 'lua-bridge.o'
        subprocess.run([str(emcc), '-O2', '-g', '-std=gnu17', '-sMEMORY64=1',
                        '-I' + str(tree / 'lib/lua-5.4.8/src'), '-c',
                        str(SNAPSHOT / 'nethack-c/wasm/lua-bridge.c'), '-o', str(lua_bridge)],
                       cwd=WORK, env=environment, check=True)
        lua_inputs = [lua_bridge]
    command = [str(emcc), *map(str, link_inputs), str(bridge), *map(str, lua_inputs), '-lm',
               '-O2', '-g', '-sMEMORY64=1', '-sMODULARIZE=1', '-sEXPORT_ES6=1',
               '-sENVIRONMENT=node,web', '-sINVOKE_RUN=0', '-sEXIT_RUNTIME=1',
               '-sALLOW_MEMORY_GROWTH=1', '-sSTACK_SIZE=4194304',
               '-sEXPORTED_RUNTIME_METHODS=FS,ENV,callMain', '--emit-symbol-map',
               '--post-js', str(SNAPSHOT / 'nethack-c/wasm/runtime.js'),
               '--embed-file', str(SNAPSHOT / 'assets') + '@/nethack',
               '--js-library', str(SNAPSHOT / 'nethack-c/wasm/dependency-library.js')]
    if args.lua:
        command += ['--js-library', str(SNAPSHOT / 'nethack-c/wasm/lua-library.js')]
    for relative in extra_libraries:
        command += ['--js-library', str(SNAPSHOT / relative)]
    startups = [port['startup'] for port in ports if port.get('startup')]
    if startups:
        command += ['-sDEFAULT_LIBRARY_FUNCS_TO_INCLUDE=' + json.dumps(startups)]
    for port in ports:
        command += ['--js-library', str(SNAPSHOT / port['library'])]
    command += ['-o', str(output)]
    (WORK / 'link-command.json').write_text(json.dumps(command, indent=2) + '\n')
    result = subprocess.run(command, cwd=WORK, env=environment)
    if result.returncode:
        raise SystemExit(f'Candidate link failed (exit {result.returncode}); exact command: {WORK / "link-command.json"}')
    wrapper = """// Experimental dependency build; active build and adapter are unchanged.
import createBase from './nethack.mjs';
import { createPortedRuntime } from './snapshot/js/backends/emscripten/runtime.js';
import { createLibraryBindings } from './snapshot/js/c-runtime/library-bindings.js';
LUA_IMPORT
import layouts from './snapshot/js/wasm/tu-layouts.json' with { type: 'json' };
export default async function createNethack(options = {}) {
  const dependencies = createLibraryBindings({ regex: REGEX_ENABLED });
  const module = await createBase({ ...options,
    nethackPorted: createPortedRuntime(layouts), nethackDependencies: dependencies LUA_OPTIONS });
  module.nethackDependencyCalls = dependencies.calls;
  return module;
}
"""
    (WORK / 'game.mjs').write_text(wrapper.replace('REGEX_ENABLED', 'true' if args.regex else 'false')
        .replace('LUA_IMPORT', "import { createLuaAbi } from './snapshot/js/lua/abi.js';\nimport { createLuaBytecodeVM } from './snapshot/js/lua/bytecode-vm.js';" if args.lua else '')
        .replace('LUA_OPTIONS', ', nethackLua: createLuaAbi({vmFactory:createLuaBytecodeVM})' if args.lua else ''))
    (WORK / 'base-game.mjs').write_text("""import createBase from './snapshot/base-wasm/nethack.mjs';
import { createPortedRuntime } from './snapshot/js/backends/emscripten/runtime.js';
import { createLibraryBindings } from './snapshot/js/c-runtime/library-bindings.js';
import layouts from './snapshot/js/wasm/tu-layouts.json' with { type: 'json' };
export default options => createBase({ ...options, nethackPorted: createPortedRuntime(layouts), nethackDependencies: createLibraryBindings({regex:true}) });
""")
    evidence = {
        'status': 'experimental-not-active', 'baseRoot': str(source_root.relative_to(ROOT)),
        'luaSnapshot': str(lua_root.relative_to(ROOT)) if args.lua else None, 'baseBuild': active,
        'javascriptTranslationUnits': len(ports), 'inputSha256': inputs,
        'linkedInputs': [str(path.relative_to(WORK)) for path in link_inputs] + ['dependency-bridge.o'] + [str(path.relative_to(WORK)) for path in lua_inputs],
        'removedLinkInputs': ['compress-service.o', 'libtinfo.a'] + (['liblua-wasm64.a'] if args.lua else []),
        'dependencyImplementation': {'compression': 'pure-js-ncompress-5.0', 'terminfo': 'pure-js-pinned-entry',
                                     'regex': active.get('regex') if active.get('regexTransport') == 'ported-posixregex-direct-js'
                                              else 'pure-js-musl-ERE-C-locale-flags9' if args.regex else 'compiled-musl',
                                     'lua': 'experimental-javascript-lua54' if args.lua else 'compiled-lua54'},
        'regex': args.regex,
        'wasmSha256': digest(WORK / 'nethack.wasm'), 'factory': 'game.mjs',
        'limitations': ['mixed C/Wasm game remains', 'Lua lifecycle/hooks/compiler integration requires independent validation' if args.lua else 'compiled Lua remains', 'numeric tparm ABI for configured NetHack callers',
                        'no public recording equivalence claimed by build alone'],
    }
    (WORK / 'build.json').write_text(json.dumps(evidence, indent=2) + '\n')
    print(f'Built isolated JS-dependency factory: {WORK / "game.mjs"} ({len(ports)} snapshotted JS TUs)')


if __name__ == '__main__':
    main()
