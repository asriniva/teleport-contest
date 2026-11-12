#!/usr/bin/env python3
"""Measure original SPELL headers and bind unchanged native spell transport."""
import hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';header=root/'scripts/tu-spell-layout.h';support=root/'nethack-c/wasm/tu-spell-support.inc';source=tree/'src/spell.c';library=root/'nethack-c/wasm/tu-libraries/spell.js';clang=ref/'.cache/emsdk/upstream/bin/clang';layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['spell']
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
with tempfile.TemporaryDirectory(prefix='standalone-spell-')as scratch:
 p=Path(scratch)/'probe.c';body='#include '+json.dumps(str(header))+'\nunsigned spell_door_probe(struct rm*p){return p->doormask;}\n';p.write_text(body);expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(p)],text=True);table=re.search(r'spell_layout\[\]\s*=\s*\{(.*?)\n\};',expanded,re.S)[1];rows=re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}',table,re.S);assert rows
 doorfield=re.search(r'spell_door_probe\(struct rm\*p\)\{return p->(\w+);',expanded)[1]
 body+='\n'.join('const unsigned long spell_value_'+str(i)+'=('+expression+');'for i,(_,expression)in enumerate(rows));p.write_text(body);ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(p)],text=True);read=lambda n:int(re.search(r'@'+n+r' = .*?constant i64 (-?\d+)',ir)[1])&((1<<64)-1)
 measured={name:read('spell_value_'+str(i))for i,(name,_)in enumerate(rows)}
 if 'size'in layout and 'size'not in measured:measured['size']=measured['spellSize']
 assert set(measured)==set(layout) and all(v==(int(layout[k])&((1<<64)-1))for k,v in measured.items()),repr({'missing':set(layout)-set(measured),'extra':set(measured)-set(layout),'different':[(k,v,layout.get(k))for k,v in measured.items()if v!=(int(layout.get(k,0))&((1<<64)-1))]})
 deps=subprocess.check_output([str(clang),*flags,'-M',str(p)],text=True);headers=[Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(ref)]
 wrapper=re.search(r'void teleport_spell_qsort\([^\n]+',support.read_text())[0]
 p.write_text('#include "hack.h"\n#include <stdlib.h>\nextern int teleport_spell_compare(const void*,const void*);\n'+wrapper+'\n')
 sortIR=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(p)],text=True)
 functionIR=re.search(r'define[^\n]*@teleport_spell_qsort\([^{]+{(.*?)^}',sortIR,re.S|re.M)[1]
 targets=re.findall(r'call void @(\w+)\(',functionIR)
 assert targets==['nh_deterministic_qsort'],('Review configured SPELL sorter',targets)
 qsortDispatch={'target':targets[0],'wrapperSha256':hashlib.sha256(wrapper.encode()).hexdigest(),'nativeComparator':'teleport_spell_compare','llvmCall':'call void @nh_deterministic_qsort'}
native=support.read_text();lib=library.read_text();public=json.loads((root/'js/nethack/public-functions.json').read_text())['functions']
globals=re.findall(r'case \d+:return &?(\w+);',native.split('teleport_spell_global',1)[1].split('void *teleport_spell_equipment',1)[0]);assert len(globals)==26
equipment=re.findall(r'case \d+:return (\w+);',native.split('teleport_spell_equipment',1)[1].split('unsigned teleport_spell_monster_bit',1)[0]);assert len(equipment)==8
bits={}
for kind in ['monster','object','class','terrain']:
 body=native.split('unsigned teleport_spell_'+kind+'_bit',1)[1].split('void teleport_spell_set_'+kind+'_bit',1)[0];bits[kind]=re.findall(r'case \d+:return p->(\w+);',body);assert bits[kind],kind
assert bits['terrain']==['doormask'];bits['terrain']=[doorfield]
hero=re.findall(r'case \d+:return u\.([\w.]+);',native.split('unsigned teleport_spell_hero_bit',1)[1].split('void teleport_spell_set_hero_bit',1)[0]);assert len(hero)==9
calls={}
for name,target in re.findall(r'^   (\w+):[^\n]*?=>\s*(?:Number\()?_(\w+)\(',lib,re.M):
 if not target.startswith('teleport_spell_'):calls[name]={'target':target,'prototype':public[target]}
assert re.search(r'set_occupation:\(fn,s,t\)=>_set_occupation\(',lib)
calls['set_occupation']={'target':'set_occupation','prototype':public['set_occupation']}
callbacks={}
for result,name,params in re.findall(r'extern (.*?) teleport_spell_callback_(\w+)\((.*?)\);',native):callbacks[name]=result+' ('+params+')'
formats={}
for name,line in re.findall(r'^   (\w+):([^\n]+)',lib,re.M):
 for shape,target in re.findall(r'case "([^"]*)":return _(teleport_spell_\w+)\(',line):
  m=re.search(r'^([^\n]+?) '+target+r'\((.*?)\)\{(?:return )?(\w+)\(',native,re.M);assert m,(name,target)
  params=[re.sub(r'\b\w+$','',v).strip() for v in m[2].split(',')]
  formats.setdefault(name,{})[shape]={'target':m[3],'prototype':m[1]+' ('+', '.join(params)+')'}
assert set(callbacks)=={'learn','deadbook_pacify_undead','spell_cmp','display_spell_target_positions','can_center_spell_location','spell_aim_step'}
names=re.findall(r'^export function (\w+)',(root/'js/ported/spell.js').read_text(),re.M)
ported=(root/'js/ported/spell.js').read_text();sites=re.findall(r'C\.Snprintf\([^\n]+,\s*(\d+),\s*"(\w+)"\);',ported);assert len(sites)==1
line,caller=sites[0];assert 'Snprintf(' in source.read_text().splitlines()[int(line)-1] and re.search(r'\b'+caller+r'\(',source.read_text())
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();inputs=[Path(__file__).resolve(),root/'js/nethack/spell.js',header,support,library,root/'js/ported/spell.js',root/'js/nethack/bindings/spell.js',root/'js/wasm/tu-layouts.json',root/'js/nethack/records.json',root/'js/nethack/public-functions.json',root/'nethack-c/wasm/compile-defines.json']
result={'qsortDispatch':qsortDispatch,'snprintfSite':{'line':int(line),'function':caller},'layout':layout,'globals':globals,'equipment':equipment,'bits':bits,'heroBits':hero,'callbacks':callbacks,'calls':calls,'formats':formats,'public':{n:public[n]for n in names if n in public},'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(set(headers+[source]))}}
(root/'js/nethack/spell-abi.json').write_text(json.dumps(result,indent=2)+'\n');print('Bound original SPELL header, globals, callbacks, fields and native format/call prototypes.')
