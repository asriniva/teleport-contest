"""Compile the same behavioral scenario as a host executable and two Wasm modules.

Native compilation uses the host libc/ABI and never Emscripten's compiler or JS
libraries. NetHack headers/configuration and isolated dependency fixtures are
shared intentionally; these are TU oracles, not a second complete game build.
"""
import json
import hashlib
import os
import re
from pathlib import Path
import subprocess
import sys


def build_oracle(root, work, name, mode, args):
    port = next(port for port in json.loads((root / 'nethack-c/wasm/tu-ports.json').read_text()) if port['name'] == name)
    upstream = root / 'nethack-c/upstream' / port['source']
    prepared = root / '.cache/wasm64-build/tree' / port['source']
    if name == 'hacklib':
        # This inherited contest patch adds two functions; all original utility
        # bodies must remain byte-identical. Apply its exact source hunk in
        # memory instead of granting a general prepared-source exemption.
        patch = (root / 'nethack-c/patches/002-deterministic-qsort.patch').read_text()
        section = patch.split('diff --git a/src/hacklib.c b/src/hacklib.c\n')[1]
        original = upstream.read_text().splitlines(keepends=True)
        expected, cursor = [], 0
        lines = section.splitlines(keepends=True)
        i = 0
        while i < len(lines):
            hunk = re.match(r'^@@ -(\d+)(?:,(\d+))? \+(\d+)(?:,(\d+))? @@', lines[i])
            if not hunk:
                i += 1
                continue
            start = int(hunk[1]) - 1
            assert start >= cursor
            expected.extend(original[cursor:start])
            cursor, i = start, i + 1
            while i < len(lines) and not lines[i].startswith(('@@', 'diff --git')):
                line = lines[i]
                assert line[:1] in [' ', '+', '-'], ('Unexpected inherited patch line', line)
                if line[0] in ' -':
                    assert original[cursor] == line[1:], ('Inherited patch context changed', cursor)
                    cursor += 1
                if line[0] in ' +':
                    expected.append(line[1:])
                i += 1
        expected.extend(original[cursor:])
        assert ''.join(expected).encode() == prepared.read_bytes(), 'Unreviewed hacklib prepared-source difference'
    elif name not in ['calendar', 'date', 'rnd', 'unixtty']:
        assert upstream.read_bytes() == prepared.read_bytes(), ('Unreviewed prepared-source difference', name)
    oracle = work / 'native-oracles'
    oracle.mkdir(exist_ok=True)
    driver = oracle / (name + '.c')
    driver.write_text('#define ORACLE_' + name.upper() + ' 1\n#include ' +
                      json.dumps(str(root / ('scripts/tu-' + name + '-probe.c'))) +
                      '\n#include ' + json.dumps(str(root / 'scripts/native-tu-cases.h')) + '\n')
    probe = root / ('scripts/tu-' + name + '-probe.c')
    wasm_args = [driver if arg == probe else arg for arg in args
                 if not str(arg).startswith('-sEXPORTED_FUNCTIONS=')]
    if name == 'calendar':
        wasm_args += ['-Dtime=teleport_oracle_time']
    wasm_args += ['-sEXPORTED_FUNCTIONS=_probe_native_oracle', '-sEXIT_RUNTIME=1']
    env = {**os.environ, 'SOURCE_DATE_EPOCH': '1777723200'}
    subprocess.run(list(map(str, wasm_args + ['-o', oracle / (name + '-' + mode + '.mjs')])), check=True, env=env)
    if mode != 'reference':
        provenance = json.loads((oracle / (name + '-build.json')).read_text())
        provenance['hybridCommand'] = list(map(str, wasm_args))
        (oracle / (name + '-build.json')).write_text(json.dumps(provenance, indent=2) + '\n')
        return
    compat = oracle / 'include/emscripten'
    compat.mkdir(parents=True, exist_ok=True)
    (compat / 'stack.h').write_text('#pragma once\n#include <stdint.h>\nstatic inline uintptr_t emscripten_stack_get_current(void) { return (uintptr_t)__builtin_frame_address(0); }\n')
    # Only the fixture uses this size to request a large allocation. Native
    # allocation is exercised, but linear-memory growth is Wasm-only coverage.
    (compat / 'heap.h').write_text('#pragma once\n#include <stddef.h>\nstatic inline size_t emscripten_get_heap_size(void) { return 16UL*1024*1024; }\n')
    native_args = [root / '.cache/wasm64-build/host-cc', '-O2', '-ffunction-sections', '-fdata-sections',
                   '-I' + str(compat.parent), '-DTELEPORT_NATIVE_ORACLE']
    native_args += ['-Wl,-dead_strip'] if sys.platform == 'darwin' else ['-Wl,--gc-sections']
    if name == 'calendar':
        native_args += ['-Dtime=teleport_oracle_time']
    wraps = []
    for arg in args[1:]:
        value = str(arg)
        if value.startswith('-s') or value == '--no-entry' or value.endswith('/tu-support.c'):
            continue
        if value.startswith('-Wl,--wrap=') and sys.platform == 'darwin':
            wraps.append(value.split('=', 1)[1])
            continue
        native_args.append(driver if arg == probe else arg)
    # Darwin's linker lacks GNU --wrap. Rename only the real definition;
    # callers still enter the probe's wrapper exactly as on the Wasm side.
    if wraps:
        for symbol in wraps:
            native_args.append('-D' + symbol + '=__wrap_' + symbol)
        for i, arg in enumerate(native_args):
            if isinstance(arg, Path) and arg.name == 'hacklib.c':
                shim = oracle / (name + '-native-hacklib.c')
                shim.write_text(''.join('#undef ' + symbol + '\n#define ' + symbol + ' __real_' + symbol + '\n' for symbol in wraps) +
                                '#include ' + json.dumps(str(arg)) + '\n')
                native_args[i] = shim
    subprocess.run(list(map(str, native_args + ['-o', oracle / (name + '-native')])), check=True, env=env)
    # Four TUs have inherited recorder/platform patches. Also compile their
    # pristine upstream algorithm, sharing only deterministic fixture inputs.
    if name in ['calendar', 'date', 'rnd', 'unixtty']:
        pristine_probe = oracle / (name + '-pristine-probe.c')
        source = probe.read_text()
        source = re.sub(r'#include "../\.cache/wasm64-build/tree/([^"\n]+)"',
                        lambda m: '#include ' + json.dumps(str(root / 'nethack-c/upstream' / m[1])), source)
        if name == 'rnd':
            # These inspectors target instrumentation absent upstream. The
            # shared RNG scenarios never call them; do not invent stub hooks.
            for function in ['log_init', 'enabled', 'count', 'caller', 'log_pointer', 'log_disp',
                             'caller_file', 'caller_line', 'caller_function']:
                match = re.search(r'^.*\bprobe_' + function + r'\([^{}]*\)\s*\{', source, re.M)
                assert match, function
                end, depth = match.end(), 1
                while depth:
                    depth += (source[end] == '{') - (source[end] == '}')
                    end += 1
                source = source[:match.start()] + source[end:]
        pristine_probe.write_text(source)
        pristine_driver = oracle / (name + '-pristine.c')
        pristine_driver.write_text('#define ORACLE_' + name.upper() + ' 1\n#include ' + json.dumps(str(pristine_probe)) +
                                  '\n#include ' + json.dumps(str(root / 'scripts/native-tu-cases.h')) + '\n')
        pristine_args = [pristine_driver if arg == driver else arg for arg in native_args]
        for i, arg in enumerate(pristine_args):
            if isinstance(arg, Path) and str(arg).startswith(str(root / '.cache/wasm64-build/tree/')):
                pristine_args[i] = root / 'nethack-c/upstream' / arg.relative_to(root / '.cache/wasm64-build/tree')
        pristine_args += ['-DTELEPORT_PRISTINE_ORACLE', '-I' + str(root / 'scripts')]
        subprocess.run(list(map(str, pristine_args + ['-o', oracle / (name + '-pristine')])), check=True, env=env)

    provenance = {
        'name': name, 'source': port['source'],
        'upstreamSHA256': hashlib.sha256(upstream.read_bytes()).hexdigest(),
        'preparedSHA256': hashlib.sha256(prepared.read_bytes()).hexdigest(),
        'casesSHA256': hashlib.sha256((root / 'scripts/native-tu-cases.h').read_bytes()).hexdigest(),
        'nativeCommand': list(map(str, native_args)),
        'referenceCommand': list(map(str, wasm_args)),
        'pristineNative': name in ['calendar', 'date', 'rnd', 'unixtty'],
    }
    (oracle / (name + '-build.json')).write_text(json.dumps(provenance, indent=2) + '\n')
