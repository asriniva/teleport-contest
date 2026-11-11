#!/usr/bin/env python3
"""Small original SDK passwd/process oracle, independent of the full game build."""
import argparse,hashlib,json,shlex,subprocess
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--reference-root',required=True,type=Path);p.add_argument('--out',required=True,type=Path);a=p.parse_args();root=Path(__file__).resolve().parents[1];ref=a.reference_root.resolve();out=a.out.resolve()
if out.exists():raise SystemExit('Use a fresh output directory')
out.mkdir(parents=True);sdk=ref/'.cache/emsdk/upstream/emscripten';source=root/'scripts/mail-sdk-probe.c'
exports=['malloc','free','probe_getpwuid','probe_passwd_text','probe_passwd_number','probe_passwd_layout','probe_errno','probe_fork','probe_execl','probe_getuid']
cmd=[str(sdk/'emcc'),str(source),'-O2','-g','-sMEMORY64=1','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sEXPORTED_RUNTIME_METHODS=HEAPU8,FS','--no-entry','-sEXPORTED_FUNCTIONS='+json.dumps(['_'+n for n in exports]),'-o',str(out/'reference.mjs')]
r=subprocess.run(cmd,capture_output=True,text=True);(out/'build.log').write_text(r.stdout+r.stderr);(out/'command.json').write_text(json.dumps(cmd,indent=2)+'\n')
if r.returncode:raise SystemExit(r.stderr)
paths=[Path(__file__).resolve(),source,*[sdk/p for p in ['system/lib/libc/musl/include/pwd.h','system/lib/libc/musl/src/passwd/getpwent.c','system/lib/libc/musl/src/passwd/getpw_a.c','system/lib/libc/musl/src/passwd/getpwent_a.c','system/lib/libc/musl/src/passwd/nscd_query.c','system/lib/libc/musl/src/process/execl.c','system/lib/libc/emscripten_libc_stubs.c','src/lib/libsockfs.js']]]
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
(out/'receipt.json').write_text(json.dumps({'sourceSha256':{str(p):sha(p)for p in paths},'artifactSha256':{p.name:sha(p)for p in [out/'reference.mjs',out/'reference.wasm']},'profile':'Unmodified pinned SDK libc passwd lookup plus actual SDK fork/exec failure, memory64; observer wrappers only.'},indent=2)+'\n');print('Built original SDK mail identity/process oracle: '+str(out))
