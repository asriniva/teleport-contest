"""Compile the same behavioral scenario as a host executable and two Wasm modules.

Native compilation uses the host libc/ABI and never Emscripten's compiler or JS
libraries. NetHack headers/configuration and isolated dependency fixtures are
shared intentionally; these are TU oracles, not a second complete game build.
"""
import json
import os
from pathlib import Path
import subprocess
import sys


def build_oracle(root, work, name, mode, args):
    oracle = work / 'native-oracles'
    oracle.mkdir(exist_ok=True)
    driver = oracle / (name + '.c')
    driver.write_text('#define ORACLE_' + name.upper() + ' 1\n#include ' +
                      json.dumps(str(root / ('scripts/tu-' + name + '-probe.c'))) +
                      '\n#include ' + json.dumps(str(root / 'scripts/native-tu-cases.h')) + '\n')
    probe = root / ('scripts/tu-' + name + '-probe.c')
    wasm_args = [driver if arg == probe else arg for arg in args
                 if not str(arg).startswith('-sEXPORTED_FUNCTIONS=')]
    wasm_args += ['-sEXPORTED_FUNCTIONS=_probe_native_oracle', '-sEXIT_RUNTIME=1']
    env = {**os.environ, 'SOURCE_DATE_EPOCH': '1777723200'}
    subprocess.run(list(map(str, wasm_args + ['-o', oracle / (name + '-' + mode + '.mjs')])), check=True, env=env)
    if mode != 'reference':
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
    wraps = []
    for arg in args[1:]:
        value = str(arg)
        if value.startswith('-s') or value == '--no-entry':
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
