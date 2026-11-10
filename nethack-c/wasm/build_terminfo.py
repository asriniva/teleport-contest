"""Build the real ncurses terminfo library for wasm64, without source patches."""
import hashlib
import os
from pathlib import Path
import shlex
import shutil
import subprocess
import tarfile

NCURSES_SHA256 = '136d91bc269a9a5785e5f9e980bc76ab57428f604ce3e5a5a90cebc767971cc6'
ENTRY_SHA256 = 'e2525d133091a1ac38b2ad4eecd8df48eee31789c8fafac0ed99bcd6b746d8ce'


def build_terminfo(root, sdk, host_cc, make, jobs):
    archive = root / '.cache/ncurses-6.5.tar.gz'
    assert archive.exists(), 'Run nethack-c/setup-terminfo.sh first'
    assert hashlib.sha256(archive.read_bytes()).hexdigest() == NCURSES_SHA256
    entry = root / 'nethack-c/wasm/terminfo/x/xterm-256color'
    assert hashlib.sha256(entry.read_bytes()).hexdigest() == ENTRY_SHA256
    source = root / '.cache/ncurses-6.5'
    if not source.exists():
        with tarfile.open(archive) as t:
            t.extractall(root / '.cache', filter='data')
    build = root / '.cache/ncurses-wasm64-build'
    env = os.environ.copy()
    em = sdk / 'upstream/emscripten'
    # Absolute tools also work in recursive make's subdirectories.
    env.update(CC=shlex.join([str(em / 'emcc'), '-sMEMORY64=1']),
               AR=str(em / 'emar'), RANLIB=str(em / 'emranlib'),
               CFLAGS='-O2 -sMEMORY64=1')
    args = [str(em / 'emconfigure'), str(source / 'configure'),
            '--host=wasm64-unknown-emscripten', f'--with-build-cc={host_cc}',
            '--with-termlib', '--without-shared', '--without-debug',
            '--without-ada', '--without-cxx', '--without-cxx-binding',
            '--without-progs', '--without-tests', '--without-manpages',
            '--disable-widec', '--disable-home-terminfo',
            '--with-terminfo-dirs=/nethack/terminfo',
            '--with-default-terminfo-dir=/nethack/terminfo']
    signature = repr((NCURSES_SHA256, str(sdk), args, env['CFLAGS']))
    stamp = build / 'teleport-config.txt'
    if not stamp.exists() or stamp.read_text() != signature:
        if build.exists():
            shutil.rmtree(build)
        build.mkdir()
        subprocess.run(args, cwd=build, env=env, check=True)
        stamp.write_text(signature)
    # Generate the real headers, then build only terminfo, not curses UI libraries.
    subprocess.run([make, '-j' + jobs], cwd=build / 'include', env=env, check=True)
    subprocess.run([make, '-j' + jobs, '../lib/libtinfo.a'],
                   cwd=build / 'ncurses', env=env, check=True)
    library = build / 'lib/libtinfo.a'
    assert library.exists(), library
    return build / 'include', library
