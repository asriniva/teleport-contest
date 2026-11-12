#!/usr/bin/env python3
"""Measure configured TIMEOUT header values and bind unchanged native seams."""
import hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';header=root/'scripts/tu-timeout-layout.h';support=root/'nethack-c/wasm/tu-timeout-support.inc';source=tree/'src/timeout.c'
layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['timeout']
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]];clang=ref/'.cache/emsdk/upstream/bin/clang'
with tempfile.TemporaryDirectory(prefix='standalone-timeout-abi-')as scratch:
 probe=Path(scratch)/'probe.c';body='#include '+json.dumps(str(header))+'\n';probe.write_text(body)
 expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(probe)],text=True)
 rows=re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}',re.search(r'timeout_layout\[\]\s*=\s*\{(.*?)\n\};',expanded,re.S)[1],re.S)
 body+='\n'.join('const unsigned long probe_timeout_'+str(i)+'=('+expr+');'for i,(_,expr)in enumerate(rows))+'\nvoid probe_common_owner(void){const char *probe_common[]={You_can_move_again,something,NH_BLUE,NH_GOLDEN,NH_GREEN};(void)probe_common;}\n';probe.write_text(body)
 ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(probe)],text=True)
 measured={name:int(re.search(r'@probe_timeout_'+str(i)+r' = .*?constant i64 (-?\d+)',ir)[1])&((1<<64)-1)for i,(name,_)in enumerate(rows)}
 assert set(measured)==set(layout) and all(measured[k]==(int(v)&((1<<64)-1))for k,v in layout.items()),'Review changed TIMEOUT frozen header profile'
 expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(probe)],text=True)
 common=[v.strip().split('.')for v in re.search(r'const char \*probe_common\[\]\s*=\s*\{(.*?)\};',expanded,re.S)[1].split(',')]
 assert all(len(v)==2 for v in common),'Review changed TIMEOUT common-string macros'
 deps=subprocess.check_output([str(clang),*flags,'-M',str(probe)],text=True);headers=[Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(ref)]
native=support.read_text();globals_=[name for _,name in re.findall(r'case (\d+):return &(\w+);',native.split('void *teleport_timeout_equipment',1)[0])]
all_globals=['u','gy','gm','gn','svk','svm','svq','svc','svl','svt','gt','gb','cg','gi','flags','iflags','disp','mons','gv','gu','svd','genders']
expected='const void *teleport_timeout_global(int i){switch(i){'+''.join('case '+str(i)+':return '+(''if name in ['mons','genders']else'&')+name+';'for i,name in enumerate(all_globals))+'default:return 0;}}'
assert expected in native,'Review changed TIMEOUT native global map'
text=source.read_text();assertions=[]
for m in re.finditer(r'assert\((.*?)\);',text,re.S):assertions.append({'condition':' '.join(m[1].split()),'line':text.count('\n',0,m.start())+1,'function':'timer_sanity_check'})
assert len(assertions)==2,'Review TIMEOUT assertions'
public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions'];names=re.findall(r'^export function (\w+)',(root/'js/ported/timeout.js').read_text(),re.M)
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
inputs=[Path(__file__).resolve(),root/'js/standalone/timers.js',root/'js/standalone/timeout-transport.js',root/'js/standalone/record-views.js',root/'js/c-runtime/record-views.js',root/'js/nethack/declarations.js',header,support,root/'js/ported/timeout.js',root/'js/ported/timeout-runtime.js',root/'nethack-c/wasm/tu-libraries/timeout.js',root/'js/standalone/public-functions.json',root/'js/wasm/tu-layouts.json',root/'nethack-c/wasm/compile-defines.json']
data={'layout':layout,'globals':all_globals,'equipment':['uwep','uswapwep','uarmh','uarmf','uamul'],'common':common,'foreign':['rot_organic','rot_corpse','revive_mon','zombify_mon','fig_transform','shrink_glob','melt_ice_away'],'assertions':assertions,'public':{name:public[name]for name in names if name in public},'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(set(headers+[source]))}}
(root/'js/standalone/timeout-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound TIMEOUT: '+str(len(names))+' source functions/'+str(len(data['public']))+' public entries; shared native globals and measured header profile.')
