#!/usr/bin/env python3
"""Measure original DO_NAME header carriers and bind its unchanged native bridge."""
import hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ.get('STANDALONE_REFERENCE_ROOT',root)).resolve();tree=ref/'.cache/wasm64-build/tree';clang=ref/'.cache/emsdk/upstream/bin/clang';header=root/'scripts/tu-do_name-layout.h';nativefile=root/'nethack-c/wasm/tu-do_name-support.inc';native=nativefile.read_text();lib=root/'nethack-c/wasm/tu-libraries/do_name.js';layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['do_name'];public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions']
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(root/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
bits={}
for kind,begin,end in [('object','unsigned teleport_do_name_object_bit','void teleport_do_name_set_object_bit'),('monster','unsigned teleport_do_name_monster_bit','void teleport_do_name_set_monster_bit')]:bits[kind]=re.findall(r'case \d+:return p->(\w+);',native.split(begin,1)[1].split(end,1)[0])
with tempfile.TemporaryDirectory(prefix='do-name-abi-')as d:
 p=Path(d)/'p.c';body='#include '+json.dumps(str(header))+'\n';p.write_text(body);cpp=subprocess.check_output([str(clang),*flags,'-E','-P',str(p)],text=True);table=re.search(r'do_name_layout\[\]\s*=\s*\{(.*?)\n\};',cpp,re.S)[1];rows=re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}',table,re.S);p.write_text(body+'\n'.join('const unsigned long p'+str(i)+'=('+e+');'for i,(_,e)in enumerate(rows)));ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(p)],text=True);measured={n:int(re.search(r'@p'+str(i)+r' = .*?constant i64 (-?\d+)',ir)[1])&((1<<64)-1)for i,(n,_)in enumerate(rows)}
 expected={k:v for k,v in layout.items()if k!='strings'};assert set(measured)==set(expected)and all(v==(int(expected[k])&((1<<64)-1))for k,v in measured.items()),'Review DO_NAME header layout'
 deps=subprocess.check_output([str(clang),*flags,'-M',str(p)],text=True);headers=[Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(ref)]
 # Expand actual native field aliases through configured headers.
 p.write_text(body+'\n#define S_(x) #x\n#define S(x) S_(x)\n'+'\n'.join('const char *alias_'+kind+'_'+str(i)+'=S(p->'+n+');'for kind,ns in bits.items()for i,n in enumerate(ns)));cpp=subprocess.check_output([str(clang),*flags,'-E','-P',str(p)],text=True)
 for kind,ns in bits.items():bits[kind]=[re.search(r'alias_'+kind+'_'+str(i)+r'\s*=\s*"p->(\w+)"',cpp)[1]for i in range(len(ns))]
globals=re.findall(r'case \d+:return &?(\w+);',native.split('const void *teleport_do_name_global',1)[1].split('void *teleport_do_name_equipment',1)[0]);assert len(globals)==15
names=re.findall(r'^export function (\w+)',(root/'js/ported/do_name.js').read_text(),re.M);dependencies=sorted(set(re.findall(r'\b_([A-Za-z]\w*)\(',lib.read_text())));dependencies=[n for n in dependencies if not n.startswith('teleport_')];assert all(n in public for n in dependencies),[n for n in dependencies if n not in public]
source=(tree/'src/do_name.c').read_text();site=re.search(r'assert\(aname != 0\)',source);assert site;line=source[:site.start()].count('\n')+1
rng=[]
text=(root/'js/ported/do_name.js').read_text()
for m in re.finditer(r'C\.(rn2|rn1)\(',text):
 depth=1;end=m.end()
 while depth:
  if text[end]=='(':depth+=1
  elif text[end]==')':depth-=1
  end+=1
 label=re.search(r", (\d+), '(\w+)'\)$",text[m.start():end]);assert label
 rng.append({'kind':m[1],'line':int(label[1]),'caller':label[2]})

inputs=[Path(__file__).resolve(),root/'js/standalone/do-name.js',header,nativefile,lib,root/'js/ported/do_name.js',root/'js/nethack/bindings/do_name.js',root/'js/standalone/records.json',root/'js/standalone/public-functions.json',root/'nethack-c/wasm/compile-defines.json'];sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
result={'layout':layout,'globals':globals,'bits':bits,'assertion':{'condition':'aname != 0','file':'do_name.c','line':line,'function':'do_oname'},'rngSites':rng,'dependencies':{n:public[n]for n in dependencies},'public':{n:public[n]for n in names if n in public},'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(set(headers+[tree/'src/do_name.c']))}}
(root/'js/standalone/do-name-abi.json').write_text(json.dumps(result,indent=2)+'\n');print('Bound original DO_NAME native transport.')
