#!/usr/bin/env python3
"""Bind original MPLAYER layout, live shared fields, native calls and RNG sites."""
import ast,hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ.get('STANDALONE_REFERENCE_ROOT',root)).resolve();tree=ref/'.cache/wasm64-build/tree';header=root/'scripts/tu-mplayer-layout.h';support=root/'nethack-c/wasm/tu-support.c';lib=root/'nethack-c/wasm/tu-libraries/mplayer.js';native=support.read_text().split('/* Player-monster shared storage',1)[1].split('/* Experience shared addresses',1)[0];layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['mplayer'];public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions'];clang=ref/'.cache/emsdk/upstream/bin/clang'
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
globals=['mons','objects','svl','u','gu','cg','svd'];assert [(int(i),v.strip().replace('(void *) ','').lstrip('&'))for i,v in re.findall(r'case (\d+): return (.*?);',native.split('int teleport_mplayer_monster_bit',1)[0])]==list(enumerate(globals[:6]));assert 'default: return &svd;'in native
packed={'monster':['female','mpeaceful'],'object':['oeroded','oeroded2','greased','oerodeproof']}
assert 'index == 0 ? mon->female : mon->mpeaceful'in native
assert all('object->'+v in native for v in packed['object']);assert 'return type->oc_merge;'in native
body='#include '+json.dumps(str(header))+'\n#define S_(x) #x\n#define S(x) S_(x)\n'+'\n'.join('const char*proof_'+kind+'_'+str(i)+'=S('+('mon->' if kind=='monster'else 'object->')+p+');'for kind,paths in packed.items()for i,p in enumerate(paths))+'\nconst char*proof_voice=S(SetVoice(m,0,80,0));'
with tempfile.TemporaryDirectory(prefix='mplayer-abi-')as d:
 p=Path(d)/'p.c';p.write_text(body);cpp=subprocess.check_output([str(clang),*flags,'-E','-P',str(p)],text=True);expressions={k:json.loads('"'+v+'"')for k,v in re.findall(r'const char\s*\*proof_(\w+)\s*=\s*"((?:\\.|[^"\\])*)";',cpp)}
 rows=re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}',re.search(r'mplayer_layout\[\]\s*=\s*\{(.*?)\n\};',cpp,re.S)[1],re.S);p.write_text(body+'\n'+'\n'.join('const unsigned long long proof_l_'+str(i)+'=('+ (e or '0') +');'for i,(_,e)in enumerate(rows)));ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(p)],text=True)
 measured={n:int(re.search(r'@proof_l_'+str(i)+r' = .*?constant i64 (-?\d+)',ir)[1])&((1<<64)-1)for i,(n,_)in enumerate(rows)};measured['size']=measured['monsterSize'];assert set(measured)==set(layout)and all(v==(int(layout[k])&((1<<64)-1))for k,v in measured.items()),repr({'extra':set(measured)-set(layout),'missing':set(layout)-set(measured),'changed':[(k,v,layout.get(k))for k,v in measured.items()if k not in layout or v!=(int(layout[k])&((1<<64)-1))]})
 deps=subprocess.check_output([str(clang),*flags,'-M',str(p)],text=True);headers=[Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(ref)]
original=(root/'nethack-c/upstream/src/mplayer.c').read_text();assert original==(tree/'src/mplayer.c').read_text(),'Review configured MPLAYER source changes';clean=re.sub(r'/\*.*?\*/|//[^\n]*',lambda m:'\n'*m[0].count('\n'),original,flags=re.S);sites=[]
for call in re.finditer(r'\b(rn2|rnd|rn1|d)\(',clean):
 depth=1;end=call.end()
 while depth:
  if clean[end]=='(':depth+=1
  if clean[end]==')':depth-=1
  end+=1
 fn=list(re.finditer(r'^(dev_name|get_mplname|mk_mplayer_armor|mk_mplayer|create_mplayers|mplayer_talk)\(',clean[:call.start()],re.M))[-1][1];sites.append([call[1],clean[:end].count('\n')+1,fn])
js=(root/'js/ported/mplayer.js').read_text();observed=[]
for call in re.finditer(r'\bC\.(rn2|rnd|rn1|d)\(',js):
 depth=1;end=call.end()
 while depth:
  if js[end]=='(':depth+=1
  if js[end]==')':depth-=1
  end+=1
 match=re.search(r',\s*(\d+)\s*,\s*[\'"]([^\'"]+)[\'"]\s*$',js[call.end():end-1]);assert match,'Missing MPLAYER RNG provenance';observed.append([call[1],int(match[1]),match[2]])
assert observed==sites,repr((observed,sites))
names=re.findall(r'^export function (\w+)',js,re.M);deps=ast.literal_eval(re.search(r'__deps: (\[[^\n]+\])',lib.read_text())[1]);deps={n:public[n]for n in deps if n in public};sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();inputs=[Path(__file__).resolve(),header,support,lib,root/'nethack-c/upstream/src/mplayer.c',root/'js/ported/mplayer.js',root/'js/ported/mplayer-runtime.js',root/'js/standalone/records.json',root/'js/standalone/public-functions.json',root/'js/wasm/tu-layouts.json',root/'nethack-c/wasm/compile-defines.json'];data={'layout':layout,'globals':globals,'packed':packed,'expressions':expressions,'rngSites':sites,'dependencies':deps,'public':{n:public[n]for n in names if n in public},'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(set(headers+[tree/'src/mplayer.c']))}}
(root/'js/standalone/mplayer-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound MPLAYER',len(data['public']),'public entries',len(deps),'typed dependencies',len(sites),'RNG sites')
