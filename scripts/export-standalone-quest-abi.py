#!/usr/bin/env python3
"""Measure QUEST header transport and bind native shared state/packed fields."""
import hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';header=root/'scripts/tu-quest-layout.h';support=root/'nethack-c/wasm/tu-support.c';library=root/'nethack-c/wasm/tu-libraries/quest.js'
layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['quest'];clang=ref/'.cache/emsdk/upstream/bin/clang'
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
with tempfile.TemporaryDirectory(prefix='standalone-quest-abi-')as scratch:
 probe=Path(scratch)/'probe.c';body='#include '+json.dumps(str(header))+'\n';probe.write_text(body)
 expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(probe)],text=True)
 rows=re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}',re.search(r'quest_layout\[\]\s*=\s*\{(.*?)\n\};',expanded,re.S)[1],re.S)
 probe.write_text(body+'\n'.join('const unsigned long probe_quest_'+str(i)+'=('+expr+');'for i,(_,expr)in enumerate(rows))+'\nconst unsigned long probe_quest_size=sizeof(struct q_score);')
 ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(probe)],text=True)
 measured={name:int(re.search(r'@probe_quest_'+str(i)+r' = .*?constant i64 (-?\d+)',ir)[1])&((1<<64)-1)for i,(name,_)in enumerate(rows)}
 measured['size']=int(re.search(r'@probe_quest_size = .*?constant i64 (\d+)',ir)[1])
 assert set(measured)==set(layout) and all(measured[k]==(int(v)&((1<<64)-1))for k,v in layout.items()),repr({'missing':set(layout)-set(measured),'extra':set(measured)-set(layout),'changed':[(k,measured.get(k),v)for k,v in layout.items()if measured.get(k)!=v]})
 deps=subprocess.check_output([str(clang),*flags,'-M',str(probe)],text=True);headers=[Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(ref)]
native=support.read_text();section=native.split('void *teleport_quest_global',1)[1].split('#ifdef TELEPORT_QUEST_LITERAL_CAPACITY',1)[0]
globals=['u','svq','svd','svc','flags','gi','gf','mons'];assert [(int(i),name)for i,name in re.findall(r'case (\d+): return &(\w+);',section.split('int teleport_quest_bit',1)[0])]==list(enumerate(globals[:7]));assert 'default: return mons;'in section
packed={}
for label,start,end,prefix in [('quest','int teleport_quest_bit','void teleport_quest_set_bit','svq.quest_status.'),('hero','int teleport_quest_hero_bit','void teleport_quest_set_hero_bit','u.'),('monster','int teleport_quest_monster_bit','void teleport_quest_set_monster_bit','monster->')]:
 body=section.split(start,1)[1].split(end,1)[0];entries=[(int(i),field)for i,field in re.findall(r'case (\d+): return '+re.escape(prefix)+r'(\w+(?:\.\w+)?);',body)];assert [i for i,_ in entries]==list(range(len(entries)));default=re.search(r'default: return '+re.escape(prefix)+r'(\w+(?:\.\w+)?);',body)[1];packed[label]=[field for _,field in entries]+[default]
assert 'return trap->ttyp;'in section and 'rng_log_set_caller("quest.c", line, "nemesis_speaks")'in section
public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions'];names=re.findall(r'^export function (\w+)',(root/'js/ported/quest.js').read_text(),re.M)
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();inputs=[Path(__file__).resolve(),header,support,library,root/'js/ported/quest.js',root/'js/ported/quest-runtime.js',root/'js/standalone/records.json',root/'js/standalone/public-functions.json',root/'js/wasm/tu-layouts.json',root/'nethack-c/wasm/compile-defines.json']
data={'layout':layout,'globals':globals,'packed':packed,'rng':{'file':'quest.c','function':'nemesis_speaks'},'public':{name:public[name]for name in names if name in public},'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(set(headers+[tree/'src/quest.c']))}}
(root/'js/standalone/quest-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound QUEST: '+str(len(data['public']))+' public source functions, measured layout/shared globals/packed state.')
