#!/usr/bin/env python3
"""Reproduce exact source relocations; preserve immutable historical receipts."""
import argparse,hashlib,json,posixpath,re,subprocess
from functools import lru_cache
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
MAP=ROOT/'docs/runtime-environment/services-layout-map.json'
config=json.loads(MAP.read_text());BASE=config['baselineCommit'];MOVES=config['moves'];NAMES=config['identifiers']
sha=lambda b:hashlib.sha256(b).hexdigest()
# A single local Git object reader avoids thousands of process launches.
objects=subprocess.Popen(['git','cat-file','--batch'],cwd=ROOT,stdin=subprocess.PIPE,stdout=subprocess.PIPE)
@lru_cache(maxsize=None)
def original(p):
 objects.stdin.write((BASE+':'+p+'\n').encode());objects.stdin.flush()
 header=objects.stdout.readline().split();assert len(header)==3 and header[1]==b'blob',('Missing baseline blob',p,header)
 data=objects.stdout.read(int(header[2]));assert objects.stdout.read(1)==b'\n'
 return data
TRACKED=subprocess.check_output(['git','ls-tree','-r','--name-only',BASE],cwd=ROOT,text=True).splitlines();KNOWN=set(TRACKED)
PATCHES=ROOT/'docs/runtime-environment/services-layout-edits.json'
patches=json.loads(PATCHES.read_text()) if PATCHES.exists()else{}
INFRA=ROOT/'docs/runtime-environment/binding-infrastructure.json'
infra_data=json.loads(INFRA.read_text())if INFRA.exists()else{}
infrastructure=infra_data.get('patches',{})
HISTORICAL={'js/wasm/build.json','dependency-inventory.json'}
# These are immutable proof recipes or historical evidence, not live source pins.
def metadata(p):return p.startswith('js/standalone/')and p.endswith('.json')or p in {'docs/runtime-environment/c-runtime-manifest.json','nethack-c/wasm/tu-ports.json'}
def active(p):return p not in HISTORICAL and (p.startswith(('js/','scripts/','nethack-c/'))and Path(p).suffix in {'.js','.mjs','.py','.sh','.html'}or p in {'index.html','dependency-inventory.json'})
LEGACY={'scripts/extract-c-runtime-helpers.mjs','scripts/prune-c-runtime-shims.mjs','scripts/update-c-runtime-provenance.py','scripts/check-c-runtime-relocation.mjs','scripts/check-sdk-runtime-extension.mjs'}
def render_source(p,b):
 s=b.decode();newp=MOVES.get(p,p)
 # Apply AST-owned body replacements at original byte offsets, not by substring.
 if p in infrastructure:
  rows=[r for r in infra_data['records']if r['file']==p]
  replacements={(sha(e['before'].encode()),sha(e['after'].encode())):e['after']for e in infrastructure[p]if not e.get('prepend')}
  for row in sorted(rows,key=lambda r:r['start'],reverse=True):
   assert len(b[:row['end']].decode().encode('utf-16-le'))//2==row['end'],'Non-ASCII AST position requires explicit UTF-16 mapping'
   assert sha(b[row['start']:row['end']])==row['beforeSha256'],('AST source inverse differs',p)
   first,last=row['start'],row['end'];replacement=replacements[row['beforeSha256'],row['afterSha256']]
   # An AST declaration removed from its own line must not leave indentation.
   if not replacement:
    begin=s.rfind('\n',0,first)+1;finish=s.find('\n',last)
    if finish<0:finish=len(s)
    if not s[begin:first].strip()and not s[last:finish].strip():first,last=begin,finish
   s=s[:first]+replacement+s[last:]
 # Keep generated adapter blank lines clean; independently assert full AST equality.
 if p in infrastructure:s=re.sub(r'(?m)^[ \t]+$', '',s)
 # Rebase every resolvable relative source/data reference from its old owner.
 def relative(m):
  spec=m[2];target=posixpath.normpath(posixpath.join(posixpath.dirname(p),spec))
  if target not in KNOWN:return m[0]
  target=MOVES.get(target,target);rel=posixpath.relpath(target,posixpath.dirname(newp))
  if not rel.startswith('.'):rel='./'+rel
  return m[1]+rel+m[1]
 if p not in LEGACY:
  s=re.sub(r'''(['"])(\.[^'"\n]+)\1''',relative,s)
  for old,new in sorted(MOVES.items(),key=lambda x:-len(x[0])):s=s.replace(old,new)
  s=s.replace('js/ported/js-runtime.js','js/nethack/runtime.js')
  # Dynamic TU names in generators, source guards and import templates.
  s=re.sub(r'js/ported/([^\n\'" ]+)-runtime\.js',r'js/nethack/bindings/\1.js',s)
  for old,new in NAMES.items():s=re.sub(r'\b'+re.escape(old)+r'\b',new,s)
 for edit in [e for e in infrastructure.get(p,[])if e.get('prepend')]+patches.get(p,[]):
  before,after=edit['before'],edit['after'];count=edit.get('count',1)
  if edit.get('prepend'):s=after+s;continue
  if edit.get('append'):s=s+after;continue
  assert s.count(before)==count,(p,'Changed explicit edit inventory',before,s.count(before))
  s=s.replace(before,after)
 return s.encode()
def render():
 outputs={};sources={}
 for p in TRACKED:
  if not(active(p)or p in MOVES):continue
  b=original(p);after=render_source(p,b)
  if after!=b or p in MOVES:
   new=MOVES.get(p,p);assert new not in outputs
   outputs[new]=after;sources[p]={'file':p,'destination':new,'beforeSha256':sha(b),'afterSha256':sha(after)}
 # Only migrate source pins whose exact before hash has been proved above.
 meta={p:original(p)for p in TRACKED if metadata(p)}
 def project(value,hashes):
  if isinstance(value,str):return hashes.get(value,MOVES.get(value,value))
  if isinstance(value,list):return[project(v,hashes)for v in value]
  if isinstance(value,dict):
   result={}
   for k,v in value.items():
    newk=k
    if isinstance(v,str)and v in hashes:
     matches=[p for p in sources if(k==p or k.endswith('/'+p))and sources[p]['beforeSha256']==v]
     if len(matches)==1:newk=MOVES.get(matches[0],matches[0])
    assert newk not in result,('Colliding source key',newk)
    result[newk]=project(v,hashes)
   return result
  return value
 current={p:sha(b)for p,b in outputs.items()}
 for p in ['js/c-runtime/adapter-factories.js','js/nethack/header-aliases.js']:current[p]=sha((ROOT/p).read_bytes())
 for iteration in range(40):
  hashes={r['beforeSha256']:current[r['destination']]for r in sources.values()if r['destination']in current}
  next_meta={}
  for p,b in meta.items():
   value=project(json.loads(b),hashes)
   if p=='nethack-c/wasm/tu-ports.json':
    # Track actual transitive adapter infrastructure as build/probe inputs.
    for row in value:
     pending=list(row.get('adapterSources',[]));seen=set(pending);support=set()
     while pending:
      name=pending.pop();body=outputs.get(name)
      if body is None:
       candidate=ROOT/name
       if not candidate.is_file():continue
       body=candidate.read_bytes()
      for spec in re.findall(r'''(?:from\s*|import\s*)['"](\.[^'"]+)['"]''',body.decode()):
       target=posixpath.normpath(posixpath.join(posixpath.dirname(name),spec))
       if target in seen:continue
       seen.add(target)
       if target.startswith('js/c-runtime/')or target=='js/nethack/header-aliases.js':
        support.add(target);pending.append(target)
     if support:row['adapterSources']=list(dict.fromkeys(row.get('adapterSources',[])+sorted(support)))
   if p=='docs/runtime-environment/c-runtime-manifest.json':
    # Match the canonical writer's expanded generic/runtime source inventory.
    for name in ['js/c-runtime/library-bindings.js','js/c-runtime/regex-abi.js','js/c-runtime/context.js','js/nethack/game-files.js','js/c-runtime/adapter-factories.js','js/nethack/header-aliases.js']:
     value['sha256'][name]=current[name]
    value['sha256']=dict(sorted(value['sha256'].items()))
   if value!=json.loads(b):next_meta[p]=(json.dumps(value,indent=2)+'\n').encode()
  registry_path='nethack-c/wasm/tu-ports.json';profile_path='nethack-c/wasm/tu-fragments/unixunix-reviewed-makefile.py'
  registry=next_meta.get(registry_path,original(registry_path));old_registry=original(registry_path)
  assert [(r['name'],r['source'])for r in json.loads(registry)]==[(r['name'],r['source'])for r in json.loads(old_registry)],'C selection changed'
  namespace={};profile_before=original(profile_path);exec(compile(profile_before,profile_path,'exec'),namespace);aliases={}
  for name,profile in namespace['PROFILES'].items():
   if profile['registrySha256']==sha(old_registry):
    row=dict(profile);row['registrySha256']=sha(registry);row['qualification']='Exact reviewed source-layout-only registry update; C selection and Makefile inverse unchanged; shared adapter inputs declared; fresh CPP remains required.';aliases[name+'-separated-bindings']=row
  assert len(aliases)==2,'Changed finite-profile inventory'
  insertion='\n# Exact source-layout registry aliases; existing finite profiles are retained.\nPROFILES.update('+repr(aliases)+')\n'
  profile_after=profile_before.replace(b'\ndef reviewed_unixunix_makefile',insertion.encode()+b'\ndef reviewed_unixunix_makefile',1);assert profile_after.replace(insertion.encode(),b'',1)==profile_before
  next_meta[profile_path]=profile_after
  updates={**outputs,**next_meta}
  for p,b in next_meta.items():
   if p not in sources:sources[p]={'file':p,'destination':p,'beforeSha256':sha(meta[p]if p in meta else original(p)),'afterSha256':sha(b)}
  nxt={p:sha(b)for p,b in updates.items()}
  for p in ['js/c-runtime/adapter-factories.js','js/nethack/header-aliases.js']:nxt[p]=sha((ROOT/p).read_bytes())
  if nxt==current:
   outputs=updates;break
  current=nxt
 else:raise AssertionError('Unstable metadata dependency cycle')
 for p,row in sources.items():row['afterSha256']=sha(outputs[row['destination']])
 return outputs,sources

def main():
 parser=argparse.ArgumentParser();parser.add_argument('--write',action='store_true');args=parser.parse_args()
 outputs,sources=render();receipt_path=ROOT/'docs/runtime-environment/services-layout.json';prior=json.loads(receipt_path.read_text())if receipt_path.exists()else{}
 prior_after={r['destination']:r['afterSha256']for r in prior.get('files',[])}
 # Whole-candidate syntax preflight before any mutation.
 syntax={p:b.decode()for p,b in outputs.items()if p.endswith(('.js','.mjs'))and(p.startswith('js/')or p.startswith('scripts/'))}
 validator="import fs from 'node:fs';import{parse}from './.cache/emsdk/upstream/emscripten/node_modules/acorn/dist/acorn.mjs';for(const[p,s]of Object.entries(JSON.parse(fs.readFileSync(0,'utf8')))){try{parse(s,{ecmaVersion:'latest',sourceType:'module'});}catch(e){throw Error(p+': '+e.message);}}"
 subprocess.run([str(ROOT/'.cache/emsdk/node/24.19.0_64bit/bin/node'),'--input-type=module','-e',validator],input=json.dumps(syntax),text=True,cwd=ROOT,check=True)
 for p in HISTORICAL:assert (ROOT/p).read_bytes()==original(p),('Historical artifact receipt changed',p)
 # Whole-candidate ownership preflight before any mutation.
 for p,b in outputs.items():
  q=ROOT/p
  if q.exists():
   actual=q.read_bytes();old=original(p)if p in KNOWN else None
   if args.write:assert actual in [b,old]or sha(actual)==prior_after.get(p),('Refusing unrelated edit',p)
   else:assert actual==b,('Relocation differs',p)
  else:assert args.write,('Missing relocated source',p)
 for old,new in MOVES.items():
  if(ROOT/old).exists():assert args.write and(ROOT/old).read_bytes()==original(old),('Old or edited source remains',old)
 if args.write:
  for p,b in outputs.items():(ROOT/p).parent.mkdir(parents=True,exist_ok=True);(ROOT/p).write_bytes(b)
  for old in MOVES:
   p=ROOT/old
   if p.exists():p.unlink()
  for p in sorted((ROOT/'js/services').rglob('*'),reverse=True)if(ROOT/'js/services').exists()else[]:
   if p.is_dir():p.rmdir()
  if(ROOT/'js/services').exists():(ROOT/'js/services').rmdir()
 receipt={'baselineCommit':BASE,'historicalReceiptSha256':{p:sha(original(p))for p in sorted(HISTORICAL)},'moves':MOVES,'identifiers':NAMES,'files':list(sources.values()),'mapSha256':sha(MAP.read_bytes()),'editsSha256':sha(PATCHES.read_bytes()),'toolSha256':sha(Path(__file__).read_bytes()),'infrastructureRecipeSha256':sha(INFRA.read_bytes()),'supportSourceSha256':{p:sha((ROOT/p).read_bytes())for p in ['scripts/services-layout-audit.mjs','scripts/services_layout_audit.py','scripts/extract-binding-infrastructure.mjs','js/c-runtime/adapter-factories.js','js/nethack/header-aliases.js','scripts/test-binding-infrastructure.mjs','scripts/check-services-layout.mjs','scripts/test-module-imports.mjs','scripts/test_module_imports.py']},'scope':'Exact source/import/API relocations plus proven source-pin propagation. Historical receipts and compiled artifacts are not refreshed.'}
 text=json.dumps(receipt,indent=2)+'\n'
 if args.write:receipt_path.write_text(text)
 else:assert receipt_path.read_text()==text,'Relocation receipt differs'
 print('PASS:',len(MOVES),'source relocations;',len(sources),'exact changed sources/metadata; original declarations and algorithms retained')
if __name__=='__main__':main()
