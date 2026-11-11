#!/usr/bin/env python3
"""Measure DOKICK native field/macro/callback boundaries; policies unchanged."""
import hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ.get('STANDALONE_REFERENCE_ROOT',root)).resolve();tree=ref/'.cache/wasm64-build/tree';clang=ref/'.cache/emsdk/upstream/bin/clang';header=root/'scripts/tu-dokick-layout.h';support=root/'nethack-c/wasm/tu-dokick-support.inc';library=root/'nethack-c/wasm/tu-libraries/dokick.js';runtime=root/'js/ported/dokick-runtime.js';source=root/'js/ported/dokick.js';layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['dokick']
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
with tempfile.TemporaryDirectory(prefix='standalone-dokick-abi-')as scratch:
 probe=Path(scratch)/'probe.c';probe.write_text('#include '+json.dumps(str(header))+'\n')
 expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(probe)],text=True)
 body=re.search(r'dokick_layout\[\]\s*=\s*\{(.*?)\n\};',expanded,re.S)[1]
 rows=re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}',body,re.S)
 probe.write_text(expanded+'\n'+'\n'.join('const long long probe_dk_'+str(i)+'=('+expr+');'for i,(_,expr)in enumerate(rows)))
 ir=subprocess.check_output([str(clang),*flags[:2],'-x','cpp-output','-S','-emit-llvm','-O0','-o','-',str(probe)],text=True)
 measured={name:int(re.search(r'@probe_dk_'+str(i)+r' = .*?constant i64 (-?\d+)',ir)[1])for i,(name,_)in enumerate(rows)}
 assert set(measured)==set(layout) and all((measured[k]&((1<<64)-1))==(int(v)&((1<<64)-1))for k,v in layout.items()),'Changed native DOKICK layout'
 probe.write_text('#include '+json.dumps(str(support))+'\n');expanded_support=subprocess.check_output([str(clang),*flags,'-E','-P',str(probe)],text=True)
 deps=subprocess.check_output([str(clang),*flags,'-M',str(probe)],text=True);headers=[Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(ref)]
native=support.read_text();lib=library.read_text();public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions']
globals=[n for _,n in re.findall(r'case (\d+):return\s*&?(\w+);',native.split('teleport_dokick_global',1)[1].split('default:',1)[0])];assert len(globals)==21
bits={}
for kind,typ in [('monster','struct monst'),('object','struct obj'),('terrain','struct rm'),('trap','struct trap')]:
 body=expanded_support.split('teleport_dokick_'+kind+'_bit',1)[1].split('default:',1)[0]
 rows=[(int(i),name)for i,name in re.findall(r'case (\d+):return p->(\w+);',body)];assert [i for i,_ in rows]==list(range(len(rows))) and rows,kind
 bits[kind]={'type':typ,'fields':[n for _,n in rows]}
body=expanded_support.split('teleport_dokick_class_bit',1)[1].split('}',1)[0];m=re.search(r'return i\?p->(\w+):p->(\w+);',body);assert m
bits['class']={'type':'struct objclass','fields':[m[2],m[1]]}
calls={}
for name,target,args in re.findall(r'^\s*(\w+):\([^)]*\)=>(?:Number\()?_(\w+)\(([^\n]*)',lib,re.M):
 if target.startswith('teleport_dokick_'):continue
 assert target in public,target
 coercions=[(k,int(i))for k,i in re.findall(r'\b(pointer|integer|byte|coord|long|text|size)\(a(\d+)\)',args)]
 assert [i for _,i in coercions]==list(range(len(coercions))),(name,args)
 calls[name]={'target':target,'prototype':public[target],'coercions':[k for k,_ in coercions]}
formats={}
for name,shape,params,target in re.findall(r'^(?:void|int) teleport_dokick_(\w+)_([a-z]+)\(([^)]*)\)\{(?:return )?(\w+)\(',native,re.M):
 if 'const char *fmt'not in params:continue
 types=[re.sub(r'\s*\b(?:fmt|out|a\d+)\s*$','',t).strip()for t in params.split(',')]
 prefix=2 if name in ['Sprintf','mon_yells']else 1
 assert (''if shape=='none'else shape)==''.join('p'if '*'in t else'l'if'long'in t else'i'for t in types[prefix:]),(name,shape,types)
 formats.setdefault(name,{})[''if shape=='none'else shape]={'target':target,'types':types,'prefix':prefix}
assert len(formats)==11,len(formats)
names=re.findall(r'^export function (\w+)\(',source.read_text(),re.M)
paths=[Path(__file__).resolve(),root/'js/standalone/dokick.js',header,support,library,runtime,source,root/'js/ported/wasm-runtime.js',root/'js/standalone/records.json',root/'js/standalone/public-functions.json',root/'js/wasm/tu-layouts.json',root/'nethack-c/wasm/compile-defines.json'];sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
data={'layout':layout,'globals':globals,'bits':bits,'calls':calls,'formats':formats,'public':{n:public[n]for n in names if n in public},'sourceSha256':{str(p.relative_to(root)):sha(p)for p in paths},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(set(headers+[tree/'src/dokick.c']))}}
(root/'js/standalone/dokick-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound original DOKICK: '+str(len(data['public']))+' public entries/'+str(len(calls))+' foreign calls/'+str(len(layout))+' native values.')
