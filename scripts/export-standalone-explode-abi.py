#!/usr/bin/env python3
"""Measure EXPLODE transport against the configured original native headers."""
import hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ.get('STANDALONE_REFERENCE_ROOT',root)).resolve();tree=ref/'.cache/wasm64-build/tree';header=root/'scripts/tu-explode-layout.h';support=root/'nethack-c/wasm/tu-fragments/explode-support.inc';lib=root/'nethack-c/wasm/tu-libraries/explode.js';native=support.read_text();layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['explode'];public=json.loads((root/'js/nethack/public-functions.json').read_text())['functions'];clang=ref/'.cache/emsdk/upstream/bin/clang'
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
globals=[v.strip().lstrip('&') for _,v in re.findall(r'case (\d+):return (.*?);',native.split('int teleport_explode_hero_flag',1)[0])];assert len(globals)==21
hero=[v for _,v in re.findall(r'case (\d+):return (.*?);',native.split('int teleport_explode_hero_flag',1)[1].split('void teleport_explode_set_botl',1)[0])]
expressions={}
for category,begin,end in [('monster','int teleport_explode_monster_macro','int teleport_explode_permonst_macro'),('permonst','int teleport_explode_permonst_macro','int teleport_explode_display_macro'),('display','int teleport_explode_display_macro','void teleport_explode_delay')]:
 for i,e in re.findall(r'case (\d+):return (.*?);',native.split(begin,1)[1].split(end,1)[0]):expressions[category+'_'+i]=e
expressions.update({'hero_'+str(i):e for i,e in enumerate(hero)});expressions['odiluted']='o->odiluted';expressions['pronoun']='uhis()';expressions['sound']='Soundeffect(effect,volume)'
body='#include '+json.dumps(str(header))+'\n#define S_(x) #x\n#define S(x) S_(x)\n'+'\n'.join('const char*proof_'+k+'=S('+v+');'for k,v in expressions.items())
with tempfile.TemporaryDirectory(prefix='explode-abi-')as d:
 p=Path(d)/'p.c';p.write_text(body);cpp=subprocess.check_output([str(clang),*flags,'-E','-P',str(p)],text=True)
 expanded={k:json.loads('"'+v+'"')for k,v in re.findall(r'const char\s*\*proof_(\w+)\s*=\s*"((?:\\.|[^"\\])*)";',cpp)}
 rows=re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}',re.search(r'explode_layout\[\]\s*=\s*\{(.*?)\n\};',cpp,re.S)[1],re.S)
 extras=sorted(set(re.findall(r'\b(?:[A-Z][A-Z_0-9]+|S_[a-z_]+|altar_[a-z_]+)\b',' '.join(expanded.values())))-set(layout))
 p.write_text(body+'\n'+'\n'.join('const long long proof_l_'+str(i)+'=('+e+');'for i,(_,e)in enumerate(rows))+'\n'+'\n'.join('const long long proof_c_'+n+'=('+n+');'for n in extras));ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(p)],text=True)
 measured={n:int(re.search(r'@proof_l_'+str(i)+r' = .*?constant i64 (-?\d+)',ir)[1])for i,(n,_)in enumerate(rows)};assert measured==layout
 constants={n:int(re.search(r'@proof_c_'+n+r' = .*?constant i64 (-?\d+)',ir)[1])for n in extras}
 deps=subprocess.check_output([str(clang),*flags,'-M',str(p)],text=True);headers=[Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(ref)]
original=(root/'nethack-c/upstream/src/explode.c').read_text();assert original==(tree/'src/explode.c').read_text(),'Review configured EXPLODE source changes'
clean=re.sub(r'/\*.*?\*/|//[^\n]*',lambda m:'\n'*m[0].count('\n'),original,flags=re.S);current='';sites=[]
for line,text in enumerate(clean.splitlines(),1):
 match=re.match(r'^(explosionmask|engulfer_explosion_msg|explode|scatter|splatter_burning_oil|explode_oil|adtyp_to_expltype|mon_explodes)\(',text)
 if match:current=match[1]
 for call in re.finditer(r'\b(rn2|rnd|d)\(',text):sites.append([call[1],line,current])
js=(root/'js/ported/explode.js').read_text();observed=[]
for call in re.finditer(r'\bC\.(rn2|rnd|d)\(',js):
 depth=1;end=call.end()
 while depth:
  if js[end]=='(':depth+=1
  if js[end]==')':depth-=1
  end+=1
 match=re.search(r",\s*(\d+)\s*,\s*'([^']+)'\s*$",js[call.end():end-1]);assert match,'Missing source RNG provenance';observed.append([call[1],int(match[1]),match[2]])
assert observed==sites,'Review EXPLODE RNG sites'
names=re.findall(r'^export function (\w+)',(root/'js/ported/explode.js').read_text(),re.M);deps=json.loads(re.search(r'__deps:(\[[^\n]+\])',lib.read_text())[1]);deps={n:public[n]for n in deps if n in public};sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();inputs=[Path(__file__).resolve(),header,support,lib,root/'nethack-c/upstream/src/explode.c',root/'js/ported/explode.js',root/'js/nethack/bindings/explode.js',root/'js/nethack/records.json',root/'js/nethack/public-functions.json',root/'js/wasm/tu-layouts.json',root/'nethack-c/wasm/compile-defines.json'];data={'layout':layout,'globals':globals,'expressions':expanded,'constants':constants,'rngSites':sites,'dependencies':deps,'public':{n:public[n]for n in names if n in public},'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(set(headers+[tree/'src/explode.c']))}}
(root/'js/nethack/explode-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound EXPLODE',len(data['public']),'public entries',len(deps),'typed dependencies')
