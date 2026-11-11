"""Exact reviewed NHLUA transport delta; preserve historical compiler-input pins."""
from pathlib import Path
import hashlib

BASELINE = '7f7d2856ecc84c0ee4a4c402b8145e178c9fa05f73baae2761167bf2ebfb3a0d'
NHLUA_TRANSPORT = '11455212641a79b8ad9f895d9ec9d679e39114a198c3d32af7a1a6948be77662'
NORMAL_GAME_TEST_PRUNING = '54e28fa9c1ac419b39decd18da160fe4534fd4aa54803bad034c3afae7337e95'
PRUNING_EDITS = [('', "# Component probes retain every original library entry. Before the normal link,\n# compile its current C inputs so pruning checks their actual undefined symbols.\nlink_targets = link_objects.splitlines()\nassert link_targets and all(target.startswith('wasm/') and target.endswith(('.o', '.a')) for target in link_targets)\nrun([MAKE, '-j' + JOBS, *link_targets, 'TARGETPFX=wasm/',\n     f'TARGET_CC={emcc}', f'TARGET_CFLAGS={flags}'], cwd=TREE / 'src')\nlibrary_pruning = BUILD / 'production-library-pruning'\nlibrary_pruning.mkdir(exist_ok=True)\nlibrary_tokens = shlex.split(link_flags)\nlibrary_inputs = [library_tokens[i + 1] for i, token in enumerate(library_tokens) if token == '--js-library']\nlibrary_input_file = library_pruning / 'inputs.json'\nlibrary_input_file.write_text(json.dumps(library_inputs, indent=2) + '\\n')\nnative_inputs = [str(TREE / 'src' / target) for target in link_targets]\nnative_inputs += [token for token in library_tokens if not token.startswith('-') and token.endswith(('.o', '.a'))]\nif not JS_LUA:\n    native_inputs.append(str(wasm_lua))\nif C_DEPENDENCIES:\n    native_inputs.append(str(terminfo_library))\nnative_inputs = list(dict.fromkeys(native_inputs))\nassert all(Path(path).is_absolute() and Path(path).is_file() for path in native_inputs), 'Missing current normal-link native input'\nnative_input_file = library_pruning / 'native-inputs.json'\nnative_input_file.write_text(json.dumps(native_inputs, indent=2) + '\\n')\nrun(['node', ROOT / 'scripts/write-game-library-pruner.mjs',\n     '--libraries-json', library_input_file, '--native-inputs-json', native_input_file,\n     '--output-dir', library_pruning], cwd=ROOT)\nlink_flags += ' --js-library ' + shlex.quote(str(library_pruning / 'normal-link-pruner.js'))\nlibrary_pruning_manifest = json.loads((library_pruning / 'normal-link-pruner-manifest.json').read_text())\nassert library_pruning_manifest['nativeDemand']['verified'] is True\nassert library_pruning_manifest['nativeDemand']['inputs'] == native_inputs\nassert library_pruning_manifest['nativeDemand']['requiredRemoved'] == []\n"), ('', "    'normalGameLibraryPruning': {\n        'scope': 'Normal final link only; original component libraries and source policy unchanged',\n        'manifest': str((library_pruning / 'normal-link-pruner-manifest.json').relative_to(ROOT)),\n        'removedEntries': library_pruning_manifest['removedEntries'],\n        'sourceSha256': {\n            **library_pruning_manifest['sourceSha256'],\n            **{str(path.relative_to(ROOT)): hashlib.sha256(path.read_bytes()).hexdigest() for path in [\n                ROOT / 'scripts/write-game-library-pruner.mjs', ROOT / 'scripts/reviewed_build_provenance.py',\n                ROOT / 'nethack-c/wasm/build.py', library_input_file, native_input_file,\n                library_pruning / 'normal-link-pruner.js', library_pruning / 'normal-link-pruner-manifest.json']},\n        },\n    },\n")]
# (historical text, reviewed replacement); no generic exclusions or hash refresh.
EDITS = [('', "ports = json.loads((ROOT / 'nethack-c/wasm/tu-ports.json').read_text())\nnhlua_transport_flags = (['-I'+str(ROOT/'scripts'), '-I'+str(ROOT/'nethack-c/wasm/tu-fragments'), '-sSUPPORT_LONGJMP=emscripten'] if any(port['name']=='nhlua' for port in ports) else [])\n"), ("run([emcc, *shlex.split(flags), '-I' + str(TREE / 'include'), '-I' + str(ROOT / '.cache/tu-probes'), '-c', ROOT / 'nethack-c/wasm/tu-support.c', '-o', tu_support])\n", "run([emcc, *shlex.split(flags), *nhlua_transport_flags, '-I' + str(TREE / 'include'), '-I' + str(ROOT / '.cache/tu-probes'), '-c', ROOT / 'nethack-c/wasm/tu-support.c', '-o', tu_support])\n"), ('', "if nhlua_transport_flags:\n    link_flags += ' -sSUPPORT_LONGJMP=emscripten'\n"), ("ports = json.loads((ROOT / 'nethack-c/wasm/tu-ports.json').read_text())\n", '# The registry was read before compiling source-owned typed transport.\n')]

def nhlua_transport_baseline(root, expected):
    assert expected == BASELINE, 'Unreviewed historical build-script pin'
    current = (Path(root) / 'nethack-c/wasm/build.py').read_bytes()
    actual = hashlib.sha256(current).hexdigest()
    if actual == NORMAL_GAME_TEST_PRUNING:
        text = current.decode('utf8')
        for before, after in reversed(PRUNING_EDITS):
            assert after and text.count(after) == 1, 'Normal game pruning delta anchor changed'
            text = text.replace(after, before, 1)
        current = text.encode('utf8')
        assert hashlib.sha256(current).hexdigest() == NHLUA_TRANSPORT, 'Changes outside reviewed normal game pruning'
        actual = NHLUA_TRANSPORT
    if actual == expected:
        return current
    assert actual == NHLUA_TRANSPORT, 'Unreviewed build-script revision'
    text = current.decode('utf8')
    # Reverse bottom-up: moving the registry read creates a duplicate old line.
    for before, after in reversed(EDITS):
        assert after and text.count(after) == 1, 'NHLUA transport delta anchor changed'
        text = text.replace(after, before, 1)
    restored = text.encode('utf8')
    assert hashlib.sha256(restored).hexdigest() == expected, 'Build changes outside reviewed NHLUA transport'
    return restored
