#!/usr/bin/env python3
"""Measure configured POTION header values and bind unchanged native seams."""
import hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';header=root/'scripts/tu-potion-layout.h';support=root/'nethack-c/wasm/tu-potion-support.inc';source=tree/'src/potion.c'
layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['potion']
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]];clang=ref/'.cache/emsdk/upstream/bin/clang'
with tempfile.TemporaryDirectory(prefix='standalone-potion-abi-')as scratch:
 probe=Path(scratch)/'probe.c';body='#include '+json.dumps(str(header))+'\n';probe.write_text(body)
 expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(probe)],text=True)
 rows=re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}',re.search(r'teleport_potion_layout\[\]\s*=\s*\{(.*?)\n\};',expanded,re.S)[1],re.S)
 body+='\n'.join('const unsigned long probe_potion_'+str(i)+'=('+expr+');'for i,(_,expr)in enumerate(rows))+'\nvoid probe_common_owner(void){const char *probe_common[]={nothing_happens,nothing_seems_to_happen,Something,vision_clears,You_can_move_again,something,NH_BLACK,NH_ORANGE,NH_LIGHT_BLUE,NH_AMBER,NH_RED};(void)probe_common;}\n';probe.write_text(body)
 ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(probe)],text=True)
 measured={name:int(re.search(r'@probe_potion_'+str(i)+r' = .*?constant i64 (-?\d+)',ir)[1])&((1<<64)-1)for i,(name,_)in enumerate(rows)}
 measured['size']=measured['objSize']
 assert set(measured)==set(layout) and all(measured[k]==(int(v)&((1<<64)-1))for k,v in layout.items()),repr([(k,v,layout.get(k))for k,v in measured.items()if str(layout.get(k))!=str(v)]+[(k,None,v)for k,v in layout.items()if k not in measured])
 expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(probe)],text=True)
 common=[v.strip().split('.')for v in re.search(r'const char \*probe_common\[\]\s*=\s*\{(.*?)\};',expanded,re.S)[1].split(',')]
 assert all(len(v)==2 for v in common),'Review changed POTION common-string macros'
 deps=subprocess.check_output([str(clang),*flags,'-M',str(probe)],text=True);headers=[Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(ref)]
native=support.read_text();all_globals=['u','svc','svm','svl','gy','gv','gm','gn','gi','gp','gu','svd','flags','iflags','disp','mons','objects','genders','obj_descr','cg']
global_body=native.split('void*teleport_potion_global(int i){switch(i){',1)[1].split('default:',1)[0]
seen=[(int(i),re.sub(r'\(void\*\)|&','',expr))for i,expr in re.findall(r'case (\d+):return (.*?);',global_body)]
assert seen==list(enumerate(all_globals)),'Review POTION native root map'
runtime=(root/'js/nethack/bindings/potion.js').read_text();decoder=json.JSONDecoder();schema=decoder.raw_decode(runtime.split('const schema=',1)[1])[0];bits=decoder.raw_decode(runtime.split('bits=',1)[1])[0];types=decoder.raw_decode(runtime.split('const types=',1)[1])[0]
native_bittypes=decoder.raw_decode((root/'nethack-c/wasm/tu-libraries/potion.js').read_text().split('bittypes=',1)[1])[0]
bit_body=native.split('unsigned teleport_potion_bit',1)[1].split('void teleport_potion_set_bit',1)[0]
for index,type in enumerate(native_bittypes):
 row=re.search(r'case '+str(index)+r':\{struct (\w+)\*o=ptr;switch\(i\)\{(.*?)default:',bit_body,re.S)
 assert row and schema[type][0]=='struct '+row[1],'Review POTION packed type'
 assert [(int(i),field)for i,field in re.findall(r'case (\d+):return o->(\w+);',row[2])]==list(enumerate(bits[type])),'Review POTION packed field map'
format_lines=json.loads('['+re.search(r'teleport_potion_format_lines\[\]\s*=\s*\{(.*?)\}',native,re.S)[1]+']');format_functions=json.loads('['+re.search(r'teleport_potion_format_functions\[\]\s*=\s*\{(.*?)\}',native,re.S)[1]+']')
assert len(format_lines)==len(format_functions)
assert '"mon->mhpmax >= mon->mhp","potion.c",2904,"split_mon"'in native
public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions'];names=re.findall(r'^export function (\w+)',(root/'js/ported/potion.js').read_text(),re.M)
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
inputs=[Path(__file__).resolve(),header,support,root/'js/ported/potion.js',root/'js/nethack/bindings/potion.js',root/'nethack-c/wasm/tu-libraries/potion.js',root/'js/standalone/public-functions.json',root/'js/wasm/tu-layouts.json',root/'nethack-c/wasm/compile-defines.json']
data={'layout':layout,'globals':all_globals,'equipment':['uwep','uarm','uarmg','uarmh','uarmf','uarmc','uarmu','ublindf','uamul','uswapwep','uball','uchain'],'schema':schema,'bits':bits,'types':types,'common':common[:6],'colors':common[6:],'formats':[{'function':fn,'line':line}for fn,line in zip(format_functions,format_lines)],'assertion':{'condition':'mon->mhpmax >= mon->mhp','line':2904,'function':'split_mon'},'public':{name:public[name]for name in names if name in public},'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(set(headers+[source]))}}
(root/'js/standalone/potion-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound POTION: '+str(len(names))+' source functions/'+str(len(data['public']))+' public entries; shared native globals and measured header profile.')
