#!/usr/bin/env python3
"""Fresh actual pinned-SDK fscanf reference; no custom scanf implementation."""
import argparse,hashlib,json,shlex,subprocess
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--reference-root',type=Path,required=True);p.add_argument('--out',type=Path,required=True);a=p.parse_args();root=Path(__file__).resolve().parents[1];ref=a.reference_root.resolve();sdk=ref/'.cache/emsdk/upstream/emscripten';out=a.out.resolve()
if out.exists():raise SystemExit('Use a fresh scanf reference directory')
out.mkdir(parents=True);source=root/'scripts/standalone-scanf-probe.c'
names=['scanf_open','scanf_close','scanf_break_fd','scanf_run','scanf_string','scanf_errno','scanf_outputs','scanf_getc','scanf_unget','scanf_flags','scanf_position','scanf_getline','scanf_line','scanf_constant','malloc','free']
flags=['-O2','-g','-sMEMORY64=1','-sFORCE_FILESYSTEM=1','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sEXPORTED_RUNTIME_METHODS=HEAPU8,FS','--no-entry']
cmd=[str(sdk/'emcc'),*flags,'-sEXPORTED_FUNCTIONS='+json.dumps(['_'+n for n in names]),str(source),'-o',str(out/'reference.mjs')];result=subprocess.run(cmd,capture_output=True,text=True);(out/'build.log').write_text(result.stdout+result.stderr);(out/'command.json').write_text(json.dumps(cmd,indent=2)+'\n')
if result.returncode:raise SystemExit(result.stderr)
deps=subprocess.check_output([str(sdk/'emcc'),*flags,'-M',str(source)],text=True)
inputs=[Path(__file__).resolve(),source,*[Path(p).resolve()for p in shlex.split(deps.split(':',1)[1].replace('\\\n',''))]]
inputs += list((sdk/'system/lib/libc/musl/src/stdio').glob('*.c'))
inputs += [sdk/'system/lib/libc/musl/src/internal'/p for p in ['intscan.c','shgetc.c','shgetc.h']]
inputs += [sdk/'src/lib'/p for p in ['libfs.js','libtty.js','libsyscall.js','libwasi.js']]
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
(out/'receipt.json').write_text(json.dumps({'profile':'Original pinned SDK narrow fscanf, real FILE and filesystem','sourceSha256':{str(p):sha(p)for p in sorted(set(inputs))},'artifactSha256':{p.name:sha(p)for p in [out/'reference.mjs',out/'reference.wasm']}},indent=2)+'\n');print('Built actual SDK fscanf reference:',out)
