#!/usr/bin/env python3
"""Build an isolated original SDK terminal/errno reference, preserving v6."""
import argparse,hashlib,json,shlex,subprocess
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--reference-root',type=Path,required=True);p.add_argument('--out',type=Path,required=True);a=p.parse_args()
root=Path(__file__).resolve().parents[1];ref=a.reference_root.resolve();sdk=ref/'.cache/emsdk/upstream/emscripten';out=a.out.resolve()
if out.exists():raise SystemExit('Use a fresh reference output directory')
out.mkdir(parents=True)
source=root/'scripts/standalone-terminal-errno-probe.c'
exports=['probe_terminal_buffer','probe_terminal_errno','probe_terminal_op','probe_terminal_constant','probe_terminal_size','malloc','free','open','close','mkdir']
flags=['-O2','-g','-sMEMORY64=1','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sEXPORTED_RUNTIME_METHODS=HEAPU8,FS','--no-entry']
cmd=[str(sdk/'emcc'),*flags,'-sEXPORTED_FUNCTIONS='+json.dumps(['_'+name for name in exports]),str(source),'-o',str(out/'reference.mjs')]
result=subprocess.run(cmd,capture_output=True,text=True);(out/'build.log').write_text(result.stdout+result.stderr);(out/'command.json').write_text(json.dumps(cmd,indent=2)+'\n')
if result.returncode:raise SystemExit(result.stderr)
deps=subprocess.check_output([str(sdk/'emcc'),*flags,'-M',str(source)],text=True)
inputs=[Path(__file__).resolve(),source,*[Path(p).resolve()for p in shlex.split(deps.split(':',1)[1].replace('\\\n',''))],*[sdk/p for p in ['src/lib/libsyscall.js','src/lib/libwasi.js','src/lib/libtty.js','src/lib/libfs.js','system/lib/libc/musl/src/unistd/isatty.c','system/lib/libc/musl/src/termios/tcgetattr.c','system/lib/libc/musl/src/termios/tcsetattr.c','system/lib/libc/musl/src/misc/ioctl.c']]]
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
(out/'receipt.json').write_text(json.dumps({'sourceSha256':{str(p):sha(p)for p in sorted(set(inputs))},'artifactSha256':{p.name:sha(p)for p in [out/'reference.mjs',out/'reference.wasm']}},indent=2)+'\n')
print('Built original SDK terminal errno reference:',out)
