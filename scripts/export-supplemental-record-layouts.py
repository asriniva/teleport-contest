#!/usr/bin/env python3
"""Measure missing anonymous records and opaque alignment storage with configured clang."""
import argparse,hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1]
p=argparse.ArgumentParser();p.add_argument('--check',action='store_true');p.add_argument('--reference-root',type=Path,default=Path(os.environ.get('STANDALONE_REFERENCE_ROOT',root)));args=p.parse_args();ref=args.reference_root.resolve()
raw=json.loads((root/'js/nethack/records.json').read_text());clang=ref/'.cache/emsdk/upstream/bin/clang';sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(root/'nethack-c/wasm/native-terminal.h'),'-I'+str(ref/'.cache/wasm64-build/tree/include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),'-I'+str(ref/'.cache/wasm64-build/tree/lib/lua-5.4.8/src')]+['-D'+x for x in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]
def canonical(t):
 t=re.sub(r'\b(?:const|volatile|restrict)\b','',t).strip();seen=set()
 while t in raw['aliases'] and t not in seen:seen.add(t);t=raw['aliases'][t]
 m=re.match(r'^(?:struct|union) (?:\w+::)?\(unnamed(?: struct| union)? at .*/([^/]+):(\d+):(\d+)\)$',t)
 return '@'+':'.join(m.groups()) if m else re.sub(r'^(?:struct|union) ','',t)
def anonymous_refs(t):return re.findall(r'(?:struct|union) (?:\w+::)?\(unnamed(?: struct| union)? at [^)]*\)',t)
with tempfile.TemporaryDirectory(prefix='record-fields-')as d:
 source=Path(d)/'measure.c';source.write_text('#include "hack.h"\n#include <signal.h>\n#include <stddef.h>\n#include "lstate.h"\n#include "lauxlib.h"\nconst unsigned long opaque_size=sizeof(long double),opaque_alignment=_Alignof(long double);\n')
 public=Path(d)/'public.c';public.write_text('#include "hack.h"\n#include "wintty.h"\n#include <sys/wait.h>\nconst unsigned long bool_size=sizeof(bool),bool_alignment=_Alignof(bool),bool_negative=(bool)-1;\nconst unsigned long idtype_size=sizeof(idtype_t),idtype_signed=((idtype_t)-1)<0;\n')
 dump=subprocess.check_output([str(clang),*flags,'-Xclang','-fdump-record-layouts-complete','-fsyntax-only',str(source)],text=True)
 ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(source)],text=True)
 ir+=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(public)],text=True)
 scalar={key:int(re.search('@opaque_'+key+r' = .*?constant i64 (\d+)',ir)[1])for key in ['size','alignment']}
 boolean={key:int(re.search('@bool_'+key+r' = .*?constant i64 (\d+)',ir)[1])for key in ['size','alignment','negative']}
 enum={key:int(re.search('@idtype_'+key+r' = .*?constant i64 (\d+)',ir)[1])for key in ['size','signed']}
 assert boolean=={'size':1,'alignment':1,'negative':1},'Review configured bool representation'
 known={};paths={}
 for block in dump.split('*** Dumping AST Record Layout'):
  name=re.search(r'^\s*0 \| (.+)$',block,re.M);size=re.search(r'\[sizeof=(\d+), align=(\d+)\]',block)
  if not name or not size:continue
  key=canonical(name[1]);fields={}
  for m in re.finditer(r'^\s*(\d+)(?::(\d+)-(\d+))? \|   (\S.*)$',block,re.M):
   text=m[4];field=re.search(r'\b(\w+)\s*$',text)[1]
   for tag in anonymous_refs(text):
    path=re.search(r' at (.*):\d+:\d+\)',tag)[1];paths[canonical(tag)]=Path(path).resolve();text=text.replace(tag,canonical(tag))
   row={'offset':int(m[1]),'ctype':text}
   if m[2]is not None:row.update(shift=int(m[2]),bits=int(m[3])-int(m[2])+1)
   fields[field]=row
  value={'size':int(size[1]),'alignment':int(size[2]),'fields':fields}
  if key in known:assert known[key]==value,'Ambiguous anonymous record '+key
  known[key]=value
  for tag in anonymous_refs(name[1]):paths[key]=Path(re.search(r' at (.*):\d+:\d+\)',tag)[1]).resolve()
 pending=[];parents=set()
 for parent,row in raw['records'].items():
  for f in row['fields'].values():
   targets=[canonical(t)for t in anonymous_refs(f['ctype'])];pending.extend(targets)
   if any(t not in raw['records']for t in targets):parents.add(parent)
 for parent in parents:
  old=raw['records'][parent];actual=known[parent]
  assert (old['size'],old['alignment'])==(actual['size'],actual['alignment']),parent
  for field,f in old['fields'].items():
   assert field in actual['fields']and all(f.get(k)==actual['fields'][field].get(k)for k in ['offset','bits','shift']),parent+'.'+field
 records={}
 while pending:
  key=pending.pop()
  if key in raw['records'] or key in records:continue
  assert key in known,'No compiler definition '+key
  row=known[key];records[key]=row
  for field,f in row['fields'].items():
   declared=re.sub(r'\b'+re.escape(field)+r'$','',f['ctype']).strip()
   for candidate in re.findall(r'@[\w.]+:\d+:\d+',declared):
    if candidate not in raw['records']:pending.append(candidate)
  assert all(f['offset']<=row['size']for f in row['fields'].values())
 headers={}
 for unit in [source,public]:
  deps=subprocess.check_output([str(clang),*flags,'-M',str(unit)],text=True)
  for name in shlex.split(deps.split(':',1)[1].replace(chr(92)+chr(10),'')):
   header=Path(name).resolve()
   if header in [source.resolve(),public.resolve()]:continue
   if header.is_relative_to(ref):key='reference/'+str(header.relative_to(ref))
   elif header.is_relative_to(root):key='project/'+str(header.relative_to(root))
   else:raise AssertionError('Untracked compiler header '+str(header))
   headers[key]=sha(header)
 result={'profile':raw['profile'],'compilerSha256':sha(clang),'definesSha256':sha(root/'nethack-c/wasm/compile-defines.json'),'sourceSha256':dict(sorted(headers.items())),'records':dict(sorted(records.items())),'parentLayoutsChecked':len(parents),'scalarLayouts':{'bool':boolean},'enums':{'enum idtype_t':{'size':enum['size'],'signed':bool(enum['signed'])}},'opaqueScalars':{'long double':{**scalar,'purpose':'Byte-preserving alignment storage only; no floating arithmetic or numeric conversions.'}}}
 target=root/'js/nethack/supplemental-record-layouts.json'
 if args.check:assert json.loads(target.read_text())==result,'Changed measured supplemental record layouts'
 else:target.write_text(json.dumps(result,indent=2)+'\n')
 print(json.dumps({'records':len(records),'fields':sum(len(v['fields'])for v in records.values()),'opaqueScalars':scalar,'checked':args.check}))
