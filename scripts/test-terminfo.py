"""Compare real native and Wasm terminfo, including parameter expansion."""
import difflib
import os
from pathlib import Path
import subprocess

root = Path(__file__).resolve().parents[1]
sdk = Path(os.environ.get('EMSDK', root / '.cache/emsdk'))
build = root / '.cache/ncurses-wasm64-build'
probe = root / 'scripts/terminfo-probe.c'
host_cc = root / '.cache/wasm64-build/host-cc'
native = build / 'probe-native'
wasm = build / 'probe.mjs'
entry = root / 'nethack-c/wasm/terminfo'
subprocess.run([host_cc, probe, '-lncurses', '-o', native], check=True)
env = {**os.environ, 'TERMINFO': str(entry), 'TERM': 'xterm-256color',
       'LINES': '24', 'COLUMNS': '80'}
expected = subprocess.check_output([native], env=env, text=True)
env['TERMINFO'] = '/nethack/terminfo'
# CLI Emscripten doesn't inherit process.env into C automatically; inject pre-JS.
pre = build / 'probe-env.js'
pre.write_text("Module.preRun = [() => { ENV.TERMINFO='/nethack/terminfo'; ENV.TERM='xterm-256color'; ENV.LINES='24'; ENV.COLUMNS='80'; }];\n")
subprocess.run([sdk / 'upstream/emscripten/emcc', '-O2', '-sMEMORY64=1',
                '-sENVIRONMENT=node', '-I' + str(build / 'include'), probe,
                build / 'lib/libtinfo.a', '--embed-file', str(entry / 'x') + '@/nethack/terminfo/x',
                '--pre-js', pre, '-o', wasm], check=True)
runner = build / 'probe-runner.mjs'
runner.write_text("import createProbe from './probe.mjs'; await createProbe();\n")
actual = subprocess.check_output(['node', runner], env=env, text=True)
if expected != actual:
    raise SystemExit(''.join(difflib.unified_diff(expected.splitlines(True), actual.splitlines(True),
                                                fromfile='native ncurses', tofile='wasm64 ncurses')))
print('PASS: native/wasm64 terminfo capabilities, 256 colors, cursor expansion, RGB and tputs; unknown terminal rejected.')
