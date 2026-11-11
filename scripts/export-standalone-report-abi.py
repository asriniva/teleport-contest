#!/usr/bin/env python3
"""Bind original configured REPORT/NHMD4 transport and source input hashes."""
import hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1]
ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree'
layouts=json.loads((root/'js/wasm/tu-layouts.json').read_text())
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+d for d in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
clang=ref/'.cache/emsdk/upstream/bin/clang';header=root/'scripts/tu-report-layout.h'
with tempfile.TemporaryDirectory(prefix='standalone-report-abi-')as scratch:
 probe=Path(scratch)/'probe.c';body='#include '+json.dumps(str(header))+'\n';probe.write_text(body)
 expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(probe)],text=True)
 rows=re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}',re.search(r'report_layout\[\]\s*=\s*\{(.*?)\n\};',expanded,re.S)[1],re.S)
 body+='const unsigned long probe_sysopt_size=sizeof(struct sysopt_s);\n'+'\n'.join('const unsigned long probe_layout_'+str(i)+'=('+expr+');'for i,(_,expr)in enumerate(rows))+'\n'
 for field in layouts['nhmd4']:
  expr='sizeof(NHMD4_CTX)'if field=='size'else'offsetof(NHMD4_CTX,'+field+')'
  body+='const unsigned long probe_md4_'+field+'='+expr+';\n'
 body+='const char *probe_CRASHREPORT=CRASHREPORT;\nconst char *probe_DEVTEAM_URL=DEVTEAM_URL;\n';probe.write_text(body)
 ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(probe)],text=True)
 value=lambda key:int(re.search(r'@probe_'+key+r' = .*?constant i64 (-?\d+)',ir)[1])
 measured={name:value('layout_'+str(i))for i,(name,_)in enumerate(rows)}
 measured['size']=value('sysopt_size')
 assert measured=={k:v for k,v in layouts['report'].items()if k!='strings'},'REPORT configuration changed'
 for field,expected in layouts['nhmd4'].items():assert value('md4_'+field)==expected,'NHMD4 layout changed: '+field
 expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(probe)],text=True)
 strings={key:''.join(json.loads(s)for s in re.findall(r'"(?:\\.|[^"\\])*"',re.search(r'const char \*probe_'+key+r'\s*=\s*(.*?);',expanded)[1]))for key in ['CRASHREPORT','DEVTEAM_URL']}
 assert strings==layouts['report']['strings'],'REPORT configured strings changed'
 deps=subprocess.check_output([str(clang),*flags,'-M',str(probe)],text=True)
 headers=[Path(p).resolve()for p in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(p).resolve().is_relative_to(ref)]
support=root/'nethack-c/wasm/tu-fragments/report.support.c'
bindings=re.findall(r'case (\d+): return (.*?);',support.read_text().split('default:',1)[0])
expected=['&gc.crash_urlmax','&gc.crash_name','&gc.crash_email','&sysopt.crashreporturl','&gs.saved_pline_index','gs.saved_plines','teleport_report_storage.bid','teleport_report_storage.url']
assert bindings==[(str(i),v)for i,v in enumerate(expected)],'REPORT native global map changed'
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
inputs=[Path(__file__).resolve(),root/'js/ported/report.js',root/'js/ported/report-runtime.js',root/'js/ported/nhmd4.js',root/'nethack-c/wasm/tu-libraries/report.js',support,header,root/'nethack-c/wasm/tu-fragments/report.storage.h',root/'nethack-c/wasm/compile-defines.json',root/'js/wasm/tu-layouts.json']
data={'report':layouts['report'],'nhmd4':layouts['nhmd4'],'globalMap':expected,'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(set(headers))}}
(root/'js/standalone/report-abi.json').write_text(json.dumps(data,indent=2)+'\n')
print('Bound original REPORT configuration, eight native globals and NHMD4 context.')
