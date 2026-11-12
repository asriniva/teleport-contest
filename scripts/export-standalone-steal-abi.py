#!/usr/bin/env python3
"""Bind original STEAL layout, live shared fields, native calls and RNG sites."""
import ast,hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ.get('STANDALONE_REFERENCE_ROOT',root)).resolve();tree=ref/'.cache/wasm64-build/tree';header=root/'scripts/tu-steal-layout.h';support=root/'nethack-c/wasm/tu-support.c';lib=root/'nethack-c/wasm/tu-libraries/steal.js';native=support.read_text().split('void *teleport_steal_global',1)[1].split('/*',1)[0];layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['steal'];public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions'];clang=ref/'.cache/emsdk/upstream/bin/clang'
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
globals=[v.strip().lstrip('&')for _,v in re.findall(r'case (\d+): return (.*?);',native.split('struct obj *teleport_steal_equipment',1)[0])]+['gv'];assert len(globals)==17 and 'default: return &gv;'in native
equipment=[v for _,v in re.findall(r'case (\d+): return (.*?);',native.split('struct obj *teleport_steal_equipment',1)[1].split('int teleport_steal_object_bit',1)[0])]+['uright'];assert len(equipment)==15
packed={}
for kind,begin,end,prefix in [('object','int teleport_steal_object_bit','void teleport_steal_set_object_bit','obj->'),('monster','int teleport_steal_monster_bit','void teleport_steal_set_monster_bit','mon->'),('hero','int teleport_steal_hero_bit','int teleport_steal_class_bit','u.')]:
 section=native.split(begin,1)[1].split(end,1)[0];rows=re.findall(r'case (\d+): return '+re.escape(prefix)+r'(.*?);',section);assert [int(i)for i,_ in rows]==list(range(len(rows)));packed[kind]=[p for _,p in rows]+[re.search(r'default: return '+re.escape(prefix)+r'(.*?);',section)[1]]
callers=ast.literal_eval('['+re.search(r'teleport_steal_callers\[\] = \{(.*?)\};',native,re.S)[1]+']')
body='#include '+json.dumps(str(header))+'\n#define S_(x) #x\n#define S(x) S_(x)\n'+'\n'.join('const char*proof_'+kind+'_'+str(i)+'=S('+({'object':'obj->','monster':'mon->','hero':'u.'}[kind])+p+');'for kind,paths in packed.items()for i,p in enumerate(paths))+'\n#ifdef NDEBUG\nconst int proof_assertEnabled=0;\n#else\nconst int proof_assertEnabled=1;\n#endif\n'
with tempfile.TemporaryDirectory(prefix='steal-abi-')as d:
 p=Path(d)/'p.c';p.write_text(body);cpp=subprocess.check_output([str(clang),*flags,'-E','-P',str(p)],text=True);expressions={k:json.loads('"'+v+'"')for k,v in re.findall(r'const char\s*\*proof_(\w+)\s*=\s*"((?:\\.|[^"\\])*)";',cpp)}
 rows=re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}',re.search(r'steal_layout\[\]\s*=\s*\{(.*?)\n\};',cpp,re.S)[1],re.S);p.write_text(body+'\n'+'\n'.join('const unsigned long long proof_l_'+str(i)+'=('+ (e or '0') +');'for i,(_,e)in enumerate(rows)));ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(p)],text=True)
 measured={n:int(re.search(r'@proof_l_'+str(i)+r' = .*?constant i64 (-?\d+)',ir)[1])&((1<<64)-1)for i,(n,_)in enumerate(rows)};measured['size']=measured['objectSize'];assert set(measured)==set(layout)and all(v==(int(layout[k])&((1<<64)-1))for k,v in measured.items()),repr({'extra':set(measured)-set(layout),'missing':set(layout)-set(measured),'changed':[(k,v,layout.get(k))for k,v in measured.items()if k not in layout or v!=(int(layout[k])&((1<<64)-1))]})
 deps=subprocess.check_output([str(clang),*flags,'-M',str(p)],text=True);headers=[Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(ref)]
original=(root/'nethack-c/upstream/src/steal.c').read_text();assert original==(tree/'src/steal.c').read_text(),'Review configured STEAL source changes';clean=re.sub(r'/\*.*?\*/|//[^\n]*',lambda m:'\n'*m[0].count('\n'),original,flags=re.S);sites=[]
for call in re.finditer(r'\b(rn2|rnd|d|rn1|ROLL_FROM)\(',clean):
 depth=1;end=call.end()
 while depth:
  if clean[end]=='(':depth+=1
  if clean[end]==')':depth-=1
  end+=1
 fn=list(re.finditer(r'^(somegold|stealgold|steal|stealamulet)\(',clean[:call.start()],re.M))[-1][1];sites.append(['rn2' if call[1]in ['ROLL_FROM','rn1']else call[1],clean[:end].count('\n')+1,fn])
js=(root/'js/ported/steal.js').read_text();observed=[]
for call in re.finditer(r'\bC\.(rn2|rnd)\(',js):
 depth=1;end=call.end()
 while depth:
  if js[end]=='(':depth+=1
  if js[end]==')':depth-=1
  end+=1
 match=re.search(r',\s*(\d+)\s*,\s*(\d+)\s*$',js[call.end():end-1]);assert match,'Missing STEAL RNG provenance';observed.append([call[1],int(match[1]),callers[int(match[2])]])
assert observed==sites,repr((observed,sites))
assertions=list(re.finditer(r'\bassert\((.*?)\);',clean,re.S));assert len(assertions)==1;assertion={'condition':assertions[0][1],'file':'steal.c','line':clean[:assertions[0].start()].count('\n')+1,'function':'steal','enabled':int(re.search(r'@proof_assertEnabled = .*?constant i32 (\d+)',ir)[1])};assert assertion['condition']=='uball != NULL && uball->where == OBJ_FLOOR';assert assertion['enabled']==1
private={'stealarm':'int (void)','unstolenarm':'int (void)'};assert all(re.search(r'staticfn int\s+'+n+r'\(void\)',original)for n in private)
runtime=root/'js/backends/emscripten/runtime.js';adapter=runtime.read_text().split('        steal(services, name, ...args)',1)[1].split('        get selvarState()',1)[0];viewargs=[]
for values,index,kind in re.findall(r'if \(\[([^\]]+)\]\.includes\(name\)\) args\[(\d+)\] = environment\.(\w+)\(args\[\d+\]\);',adapter,re.S):
 viewargs.append({'names':ast.literal_eval('['+values+']'),'index':int(index),'kind':kind})
for name,index,kind in re.findall(r"if \(name === '([^']+)'\) args\[(\d+)\] = environment\.(\w+)\(args\[\d+\]\);",adapter):viewargs.append({'names':[name],'index':int(index),'kind':kind})
assert len(viewargs)==3
names=re.findall(r'^export function (\w+)',js,re.M);deps=ast.literal_eval(re.search(r'__deps: (\[[^\n]+\])',lib.read_text())[1]);deps={n:public[n]for n in deps if n in public};sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();inputs=[Path(__file__).resolve(),runtime,header,support,lib,root/'nethack-c/upstream/src/steal.c',root/'js/ported/steal.js',root/'js/nethack/bindings/steal.js',root/'js/standalone/records.json',root/'js/standalone/public-functions.json',root/'js/wasm/tu-layouts.json',root/'nethack-c/wasm/compile-defines.json'];data={'layout':layout,'globals':globals,'packed':packed,'expressions':expressions,'private':private,'assertion':assertion,'equipment':equipment,'viewArgs':viewargs,'rngSites':sites,'rngCallers':callers,'dependencies':deps,'public':{n:public[n]for n in names if n in public},'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(set(headers+[tree/'src/steal.c']))}}
(root/'js/standalone/steal-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound STEAL',len(data['public']),'public entries',len(deps),'typed dependencies',len(sites),'RNG sites')
