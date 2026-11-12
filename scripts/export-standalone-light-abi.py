#!/usr/bin/env python3
"""Measure original MCASTU headers and bind unchanged native spell transport."""
import hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';header=root/'scripts/tu-light-layout.h';support=root/'nethack-c/wasm/tu-support.c';source=tree/'src/light.c';library=root/'nethack-c/wasm/tu-libraries/light.js';clang=ref/'.cache/emsdk/upstream/bin/clang';layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['light']
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
with tempfile.TemporaryDirectory(prefix='standalone-light-')as scratch:
 p=Path(scratch)/'probe.c';body='#include '+json.dumps(str(header))+'\n';p.write_text(body);expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(p)],text=True);table=re.search(r'light_layout\[\]\s*=\s*\{(.*?)\n\};',expanded,re.S)[1];rows=re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}',table,re.S);assert rows
 body+='\n'.join('const unsigned long light_value_'+str(i)+'=('+expression+');'for i,(_,expression)in enumerate(rows));p.write_text(body);ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(p)],text=True);read=lambda n:int(re.search(r'@'+n+r' = .*?constant i64 (-?\d+)',ir)[1])&((1<<64)-1)
 measured={name:read('light_value_'+str(i))for i,(name,_)in enumerate(rows)}
 if 'size'in layout and 'size'not in measured:measured['size']=measured['lightSourceSize']
 assert set(measured)==set(layout) and all(v==(int(layout[k])&((1<<64)-1))for k,v in measured.items()),repr({'missing':set(layout)-set(measured),'extra':set(measured)-set(layout),'different':[(k,v,layout.get(k))for k,v in measured.items()if v!=(int(layout.get(k,0))&((1<<64)-1))]})
 deps=subprocess.check_output([str(clang),*flags,'-M',str(p)],text=True);headers=[Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(ref)]
native=support.read_text().split('const void *teleport_light_global(int index)',1)[1].split('void teleport_light_free',1)[0]
globals=re.findall(r'(?:case \d+|default): return &?(\w+);',native.split('struct obj *teleport_light_uskin',1)[0]);assert len(globals)==11
globals=[{'circle_data':'vision.circle_data','circle_start':'vision.circle_start'}.get(n,n)for n in globals]
public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions'];names=re.findall(r'^export function (\w+)',(root/'js/ported/light.js').read_text(),re.M)
dependencies=sorted(set(re.findall(r'\b_([a-zA-Z]\w*)\(',library.read_text())));dependencies=[n for n in dependencies if not n.startswith('teleport_')];assert all(n in public for n in dependencies),[n for n in dependencies if n not in public]
assertions=[]
for m in re.finditer(r'assert\((.*?)\);',source.read_text()):
 before=source.read_text()[:m.start()];fn=re.findall(r'\n(\w+)\([^;{}]*?\)\n\{',before)[-1];assertions.append({'condition':m[1],'line':before.count('\n')+1,'function':fn})
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();inputs=[Path(__file__).resolve(),root/'js/standalone/light.js',header,support,library,root/'js/ported/light.js',root/'js/nethack/bindings/light.js',root/'js/wasm/tu-layouts.json',root/'js/standalone/records.json',root/'js/standalone/public-functions.json',root/'nethack-c/wasm/compile-defines.json']
result={'layout':layout,'globals':globals,'objectBits':['lamplit','blessed','cursed'],'monsterBits':['isgd','mtemplit'],'assertions':assertions,'dependencies':{n:public[n]for n in dependencies},'public':{n:public[n]for n in names if n in public},'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(set(headers+[source]))}}
(root/'js/standalone/light-abi.json').write_text(json.dumps(result,indent=2)+'\n');print('Bound original LIGHT configured layout/globals/packed fields/typed source calls/assertions.')
