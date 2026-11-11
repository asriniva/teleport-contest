#!/usr/bin/env python3
"""Measure APPLY transport; source decisions remain unchanged."""
import hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';header=root/'scripts/tu-apply-layout.h';support=root/'nethack-c/wasm/tu-fragments/apply-support.inc';library=root/'nethack-c/wasm/tu-libraries/apply.js';runtime=root/'js/ported/apply-runtime.js';layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['apply'];clang=ref/'.cache/emsdk/upstream/bin/clang'
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
with tempfile.TemporaryDirectory(prefix='standalone-apply-abi-')as scratch:
 probe=Path(scratch)/'probe.c';body='#include '+json.dumps(str(header))+'\n';probe.write_text(body)
 expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(probe)],text=True)
 rows=re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}',re.search(r'apply_layout\[\]\s*=\s*\{(.*?)\n\};',expanded,re.S)[1],re.S)
 assert dict(rows)['NH_RED']=='(long long)(c_color_names.c_red)',repr(dict(rows)['NH_RED'])
 rows=[(name,expr)for name,expr in rows if name!='NH_RED']
 constant_probe=re.sub(r'\{\s*"NH_RED"\s*,\s*\(long long\)\(c_color_names.c_red\)\s*\}', '{"NH_RED",0}',expanded)
 assert constant_probe!=expanded
 probe.write_text(constant_probe+'\n'+'\n'.join('const long long probe_apply_'+str(i)+'=('+expr+');'for i,(_,expr)in enumerate(rows)))
 ir=subprocess.check_output([str(clang),*flags[:2],'-x','cpp-output','-S','-emit-llvm','-O0','-o','-',str(probe)],text=True)
 measured={name:int(re.search(r'@probe_apply_'+str(i)+r' = .*?constant i64 (-?\d+)',ir)[1])for i,(name,_)in enumerate(rows)}
 assert set(measured)==set(layout)-{'NH_RED'} and all((measured[k]&((1<<64)-1))==(int(v)&((1<<64)-1))for k,v in layout.items()if k!='NH_RED'),repr({'missing':set(layout)-set(measured),'extra':set(measured)-set(layout),'changed':[(k,measured.get(k),v)for k,v in layout.items()if measured.get(k)!=v]})
 probe.write_text(body)
 deps=subprocess.check_output([str(clang),*flags,'-M',str(probe)],text=True);headers=[Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(ref)]
native=support.read_text();lib=library.read_text();rt=runtime.read_text();decoder=json.JSONDecoder();extract=lambda marker:decoder.raw_decode(rt.split(marker,1)[1])[0]
globals=extract('const globals=');body=native.split('teleport_apply_global',1)[1].split('int teleport_apply_bit',1)[0];seen=[(int(i),name)for i,name in re.findall(r'case (\d+):return\(const void\*\)&(\w+);',body)];assert seen==list(enumerate(globals))
bitbody=native.split('int teleport_apply_bit',1)[1].split('void teleport_apply_set_bit',1)[0];bits=[{'index':int(i),'type':'struct '+t,'field':f}for i,t,f in re.findall(r'case (\d+):return\(\(const struct (\w+)\*\)p\)->(\w+);',bitbody)];assert [b['index']for b in bits]==list(range(34))
public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions'];calls={}
for name,target in re.findall(r'^(\w+):[^\n]*?=>\s*(?:Number\()?_(\w+)\(',lib,re.M):
 if not target.startswith('teleport_apply_'):calls[name]={'target':target,'prototype':public[target]}
callbackIds=decoder.raw_decode(lib.split('var callbackIds=',1)[1])[0];callbacks={}
for name,index in callbackIds.items():
 if name in public:prototype=public[name]
 else:
  match=re.search(r'extern (.*?) teleport_apply_callback_'+name+r'\((.*?)\);',native);assert match,name;prototype=match[1]+' ('+match[2]+')'
 callbacks[name]={'index':index,'prototype':prototype}
formats={}
for name,mapping in re.findall(r'^(\w+):[^\n]*?var fn=(\{[^\n]*?\})\[shape\]',lib,re.M):
 shapes=json.loads(mapping);rows={}
 for shape,target in shapes.items():
  m=re.search(r'^([^\n;{}]+?) '+target+r'\((.*?)\)\{(?:return )?(\w+)\(',native,re.M);assert m,(name,target)
  params=re.sub(r'\brestrict\b','',m[2]);params=re.sub(r'\s+a\d+\b','',params);rows[shape]={'target':m[3],'prototype':m[1]+' ('+params+')'}
 formats[name]=rows
names=re.findall(r'^export function (\w+)',(root/'js/ported/apply.js').read_text(),re.M);inputs=[Path(__file__).resolve(),header,support,library,runtime,root/'js/ported/apply.js',root/'js/standalone/records.json',root/'js/standalone/public-functions.json',root/'js/wasm/tu-layouts.json',root/'nethack-c/wasm/compile-defines.json'];sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
data={'relocations':{'NH_RED':{'global':'c_color_names','record':'struct c_color_names','field':'c_red','expression':'c_color_names.c_red'}},'layout':layout,'globals':list(globals),'bits':bits,'callbacks':callbacks,'calls':calls,'formats':formats,'callers':extract('const CALLER_NAMES='),'public':{n:public[n]for n in names if n in public},'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(set(headers+[tree/'src/apply.c']))}}
(root/'js/standalone/apply-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound APPLY: '+str(len(data['public']))+' public source entries/'+str(len(calls))+' typed foreign calls/'+str(len(callbacks))+' callbacks.')
