#!/usr/bin/env python3
"""Bind the full ARTIFACT factory transport without replacing source policies."""
import hashlib,json,re
from pathlib import Path
root=Path(__file__).resolve().parents[1];runtime=root/'js/ported/artifact-runtime.js';library=root/'nethack-c/wasm/tu-libraries/artifact.js';support=root/'nethack-c/wasm/tu-fragments/artifact-support.c';r=runtime.read_text();lib=library.read_text();dec=json.JSONDecoder()
schemas=dec.raw_decode(r.split('const schemas=',1)[1])[0];globals=dec.raw_decode(r.split('const globals=',1)[1])[0];functions=dec.raw_decode(r.split('const functions=',1)[1])[0]
conversions={}
for name,body in re.findall(r'if\(name===\"(\w+)\"\)\{([^\n]+)\}',r):
 rows=[]
 for index,method,quote,typ in re.findall(r'args\[(\d+)\]=env\.(view|scalarPointer)\(([\'\"])(.+?)\3,args\[\d+\]\)',body):rows.append({'index':int(index),'method':method,'type':typ})
 if rows:conversions[name]=rows
calls={}
for name,params,expression in re.findall(r'^\s+(\w+):\(([^)]*)\)=>([^\n]+)',lib,re.M):
 expression=expression.rstrip(',')
 if expression.startswith('pointerResult('):expression=expression[14:-1]
 match=re.fullmatch(r'_(\w+)\((.*)\)',expression)
 if not match:continue
 target,args=match.groups();params=params.split(',')if params else[]
 args=args.replace('),',')\x1f').split('\x1f')if args else[];convs=[]
 for i,arg in enumerate(args):
  v=params[i]
  if arg=='(Number('+v+')|0)':conv='int'
  elif arg=='(Number('+v+')>>>0)':conv='uint'
  else:
   m=re.fullmatch(r'(\w+)\('+v+r'\)',arg)
   if not m:raise ValueError('Review ARTIFACT native argument '+name+':'+arg)
   conv=m[1]
  if conv not in ['pointer','text','int','uint','byte','ubyte','short','ushort','long','ulong']:raise ValueError('Review ARTIFACT converter '+conv)
  convs.append(conv)
 if len(convs)!=len(params):raise ValueError('Review ARTIFACT argument count '+name)
 if target.startswith('teleport_artifact_'):
  family=target[len('teleport_artifact_'):]
  if not re.search(r'_[pij]+$',family):continue
  target=family.rsplit('_',1)[0]
 calls[name]={'target':target,'arguments':convs}
owned={int(i):functions[int(i)]for i in re.findall(r'case (\d+):return\(uintptr_t\)&teleport_artifact_callback_\w+;',support.read_text())}
foreign={int(i):n for i,n in re.findall(r'case (\d+):return\(uintptr_t\)&(\w+);',support.read_text().split('uintptr_t teleport_artifact_foreign_function_pointer',1)[1].split('default:',1)[0])}
paths=[Path(__file__).resolve(),runtime,library,support,root/'nethack-c/wasm/tu-fragments/artifact-schema.json',root/'js/ported/artifact.js',root/'js/standalone/public-functions.json',root/'js/wasm/tu-layouts.json',root/'js/standalone/records.json']
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
data={'schemas':schemas,'globals':globals,'argumentViews':conversions,'calls':calls,'callbacks':owned,'foreignCallbacks':foreign,'resbufBytes':int(re.search(r'static char teleport_artifact_resbuf\[(\d+)\]',support.read_text())[1]),'sourceSha256':{str(p.relative_to(root)):sha(p)for p in paths}}
(root/'js/standalone/artifact-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound ARTIFACT source views, global aliases and typed native calls.')
