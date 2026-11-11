#!/usr/bin/env python3
"""Measure original END profile and bind native source maps, without policy edits."""
import hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';header=root/'scripts/tu-end-layout.h';support=root/'nethack-c/wasm/tu-fragments/end-support.inc';runtime=root/'js/ported/end-runtime.js';clang=ref/'.cache/emsdk/upstream/bin/clang';decoder=json.JSONDecoder()
layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['end'];flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
with tempfile.TemporaryDirectory(prefix='standalone-end-')as scratch:
 p=Path(scratch)/'probe.c';body='#include '+json.dumps(str(header))+'\n';p.write_text(body);expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(p)],text=True)
 rows=re.findall(r'\{\s*"([^"]+)"\s*,\s*\(long long\)\((.*?)\)\s*\}',expanded,re.S)
 assert rows,'Missing END measured rows'
 body+='\n'.join('const unsigned long end_value_'+str(i)+'=('+expression+');'for i,(_,expression)in enumerate(rows))+'\nconst char *end_headers[]={WIZARD_NAME,plur(1),plur(2)};\nvoid end_exit_probe(void){nethack_exit(0);}\n';p.write_text(body)
 ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(p)],text=True)
 measured={name:int(re.search(r'@end_value_'+str(i)+r' = .*?constant i64 (-?\d+)',ir)[1])&((1<<64)-1)for i,(name,_)in enumerate(rows)}
 assert set(measured)==set(layout) and all(v==(int(layout[k])&((1<<64)-1))for k,v in measured.items()),repr([(k,v,layout.get(k))for k,v in measured.items()if v!=(int(layout.get(k,0))&((1<<64)-1))])
 headerrow=re.search(r'@end_headers = .*?global \[3 x ptr\] \[(.*?)\]',ir)[1];strings={name:bytes(re.sub(r'\\([0-9A-Fa-f]{2})',lambda m:chr(int(m[1],16)),value),'latin1').rstrip(b'\0').decode('latin1')for name,value in re.findall(r'(@[.\w]+) = .*?constant \[\d+ x i8\] c"(.*?)"',ir)};strings.update({name:''for name in re.findall(r'(@[.\w]+) = .*?constant \[1 x i8\] zeroinitializer',ir)});headers=[strings[name]for name in re.findall(r'ptr (@[.\w]+)',headerrow)]
 assert len(headers)==3
 expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(p)],text=True);assert 'void end_exit_probe(void){exit(0);}'in expanded
 deps=subprocess.check_output([str(clang),*flags,'-M',str(p)],text=True);inputs=[Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(ref)]
text=runtime.read_text();records=decoder.raw_decode(text.split('const records=',1)[1])[0];globals=decoder.raw_decode(text.split('const globals=',1)[1])[0];native=support.read_text();gb=native.split('teleport_end_global(int i){switch(i){',1)[1].split('default:',1)[0];assert [re.sub(r'^&','',v)for _,v in re.findall(r'case (\d+):return (.*?);',gb)]==list(globals)
bits=[]
for type,fields in records.items():
 for field,row in fields.items():
  if row['bit']:bits.append((row['bitIndex'],type,field))
bits.sort();assert [i for i,_,_ in bits]==list(range(len(bits)))
for i,type,field in bits:assert f'case {i}:return((const {type}*)p)->{field};'in native and f'case {i}:(({type}*)p)->{field}=n;return;'in native
public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions'];names=re.findall(r'^export function (\w+)',(root/'js/ported/end.js').read_text(),re.M);sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();sources=[Path(__file__).resolve(),root/'js/standalone/end-lifecycle.js',root/'js/standalone/killer-state.js',runtime,header,support,root/'js/ported/end.js',root/'nethack-c/wasm/tu-libraries/end.js',root/'js/wasm/tu-layouts.json',root/'js/standalone/public-functions.json',root/'nethack-c/wasm/compile-defines.json']
result={'layout':layout,'records':records,'globals':globals,'bits':[[t,f]for _,t,f in bits],'headers':headers,'exitMacro':'exit','public':{n:public[n]for n in names if n in public},'sourceSha256':{str(p.relative_to(root)):sha(p)for p in sources},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(set(inputs+[tree/'src/end.c']))}}
(root/'js/standalone/end-lifecycle-abi.json').write_text(json.dumps(result,indent=2)+'\n');print('Bound END original source/native layout, '+str(len(result['public']))+' public functions, '+str(len(bits))+' packed fields and source header strings.')
