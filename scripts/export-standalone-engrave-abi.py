#!/usr/bin/env python3
"""Measure original ENGRAVE header carriers and bind its unchanged native bridge."""
import hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ.get('STANDALONE_REFERENCE_ROOT',root)).resolve();tree=ref/'.cache/wasm64-build/tree';clang=ref/'.cache/emsdk/upstream/bin/clang';header=root/'scripts/tu-engrave-layout.h';nativefile=root/'nethack-c/wasm/tu-engrave-support.inc';native=nativefile.read_text();lib=root/'nethack-c/wasm/tu-libraries/engrave.js';layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['engrave'];public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions']
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(root/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
bits={'object':['cursed','known'],'class':['oc_name_known','oc_tough','oc_bimanual'],'engr':['guardobjects','nowipeout','eread','erevealed'],'terrain':['disturbed','drawbridgemask']}
with tempfile.TemporaryDirectory(prefix='engrave-abi-')as d:
 p=Path(d)/'p.c';body='#include '+json.dumps(str(header))+'\n';p.write_text(body);cpp=subprocess.check_output([str(clang),*flags,'-E','-P',str(p)],text=True);table=re.search(r'engrave_layout\[\]\s*=\s*\{(.*?)\n\};',cpp,re.S)[1];rows=re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}',table,re.S);p.write_text(body+'\n'.join('const unsigned long p'+str(i)+'=('+e+');'for i,(_,e)in enumerate(rows)));ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(p)],text=True);measured={n:int(re.search(r'@p'+str(i)+r' = .*?constant i64 (-?\d+)',ir)[1])&((1<<64)-1)for i,(n,_)in enumerate(rows)}
 expected={k:v for k,v in layout.items()if k not in ['strings','ENGRAVEFILE','EPITAPHFILE']};assert set(measured)==set(expected)and all(v==(int(expected[k])&((1<<64)-1))for k,v in measured.items()),repr({'missing':set(expected)-set(measured),'extra':set(measured)-set(expected),'different':[(k,v,expected.get(k))for k,v in measured.items()if k in expected and v!=(int(expected[k])&((1<<64)-1))]})
 p.write_text(body+'\nconst char *engrave_file=ENGRAVEFILE;\nconst char *epitaph_file=EPITAPHFILE;');expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(p)],text=True)
 for var,key in [('engrave_file','ENGRAVEFILE'),('epitaph_file','EPITAPHFILE')]:assert json.loads(re.search(var+r'\s*=\s*("[^"]*")',expanded)[1])==layout[key]
 deps=subprocess.check_output([str(clang),*flags,'-M',str(p)],text=True);headers=[Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(ref)]
 # Expand actual native field aliases through configured headers.
 p.write_text(body+'\n#define S_(x) #x\n#define S(x) S_(x)\n'+'\n'.join('const char *alias_'+kind+'_'+str(i)+'=S(p->'+n+');'for kind,ns in bits.items()for i,n in enumerate(ns)));cpp=subprocess.check_output([str(clang),*flags,'-E','-P',str(p)],text=True)
 for kind,ns in bits.items():bits[kind]=[re.search(r'alias_'+kind+'_'+str(i)+r'\s*=\s*"p->(\w+)"',cpp)[1]for i in range(len(ns))]
globals=re.findall(r'case \d+:return &?(\w+);',native.split('const void *teleport_engrave_global',1)[1].split('void *teleport_engrave_head',1)[0]);assert len(globals)==14
names=re.findall(r'^export function (\w+)',(root/'js/ported/engrave.js').read_text(),re.M);dependencies=sorted(set(re.findall(r'\b_([A-Za-z]\w*)\(',lib.read_text())));dependencies=[n for n in dependencies if not n.startswith('teleport_')];assert all(n in public for n in dependencies),[n for n in dependencies if n not in public]
metadata=(root/'scripts/write-tu-source-metadata.py').read_text();lines=[int(v)for v in re.search(r'TELEPORT_ENGRAVE_STRLEN_LINES \{([^}]+)\}',metadata)[1].split(',')];functions=re.findall(r'"(\w+)"',re.search(r'TELEPORT_ENGRAVE_STRLEN_FUNCTIONS \{([^}]+)\}',metadata)[1]);assert len(lines)==len(functions)==3
rng=[]
text=(root/'js/ported/engrave.js').read_text()
for m in re.finditer(r'C\.(rn2|rn1|rnd)\(',text):
 depth=1;end=m.end()
 while depth:
  if text[end]=='(':depth+=1
  elif text[end]==')':depth-=1
  end+=1
 label=re.search(r", (\d+), '(\w+)'\)$",text[m.start():end]);assert label
 rng.append({'kind':m[1],'line':int(label[1]),'caller':label[2]})

inputs=[Path(__file__).resolve(),root/'js/standalone/engrave.js',header,nativefile,root/'nethack-c/wasm/tu-engrave-support.h',root/'scripts/write-tu-source-metadata.py',lib,root/'js/ported/engrave.js',root/'js/ported/engrave-runtime.js',root/'js/standalone/records.json',root/'js/standalone/public-functions.json',root/'nethack-c/wasm/compile-defines.json'];sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
result={'layout':layout,'globals':globals,'bits':bits,'strlenSites':[{'line':line,'function':fn}for line,fn in zip(lines,functions)],'rngSites':rng,'dependencies':{n:public[n]for n in dependencies},'public':{n:public[n]for n in names if n in public},'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(set(headers+[tree/'src/engrave.c']))}}
(root/'js/standalone/engrave-abi.json').write_text(json.dumps(result,indent=2)+'\n');print('Bound original ENGRAVE native transport.')
