#!/usr/bin/env python3
"""Bind exact helper extraction and dependency metadata; never refresh unrelated pins."""
import argparse,copy,hashlib,importlib.util,json,re,subprocess
from pathlib import Path
from services_layout_audit import read_before,text_before,write_before
root=Path(__file__).resolve().parents[1]
parser=argparse.ArgumentParser();parser.add_argument('--write',action='store_true');parser.add_argument('--audit-successors',action='store_true');args=parser.parse_args()
receipt=json.loads(text_before(root/'docs/runtime-environment/c-runtime-helper-extraction.json'));baseline=receipt['baselineCommit']
sha=lambda b:hashlib.sha256(b).hexdigest()
original=lambda p:subprocess.check_output(['git','show',baseline+':'+p],cwd=root)
changes={row['file']:row for row in receipt['files']}
for path,row in changes.items():
 assert sha(original(path))==row['beforeSha256'],path
 assert sha(read_before(root/path))==row['afterSha256'],path
helper=receipt['helperFile'];assert sha(read_before(root/helper))==receipt['helperSha256']
registry_path='nethack-c/wasm/tu-ports.json';registry_before=original(registry_path)
rows=json.loads(registry_before);new_rows=copy.deepcopy(rows)
for row in new_rows:
 runtime='js/ported/'+row['name']+'-runtime.js'
 if runtime in changes:
  sources=row.setdefault('adapterSources',[])
  if runtime not in sources:sources.append(runtime)
  assert helper not in sources,row['name']
  sources.append(helper)
assert [(r['name'],r['source'])for r in rows]==[(r['name'],r['source'])for r in new_rows]
registry_after=(json.dumps(new_rows,indent=2)+'\n').encode()
# Only the selected adapters gain one declared JS source dependency.
reverse=copy.deepcopy(new_rows)
for row,before in zip(reverse,rows):
 if 'js/ported/'+row['name']+'-runtime.js' in changes:
  assert row['adapterSources'][-1]==helper
  if 'adapterSources'in before:row['adapterSources']=copy.deepcopy(before['adapterSources'])
  else:del row['adapterSources']
assert reverse==rows
profile_path='nethack-c/wasm/tu-fragments/unixunix-reviewed-makefile.py';profile_before=original(profile_path)
# Execute the immutable baseline profile definitions, not the edited worktree.
namespace={};exec(compile(profile_before,profile_path,'exec'),namespace)
old_profiles=namespace['PROFILES'];aliases={}
for name,profile in old_profiles.items():
 if profile['registrySha256']==sha(registry_before):
  row=copy.deepcopy(profile);row['registrySha256']=sha(registry_after)
  assert row['orderedSourceProjection']==[(r['name'],r['source'])for r in rows]
  row['qualification']='Exact helper-dependency-only registry update; ordered C selection, Makefile bytes and historical inverse unchanged. Fresh command/macros/CPP obligations remain.'
  aliases[name+'-shared-c-runtime']=row
assert len(aliases)==2,'Review changed finite-profile inventory'
insertion="\n# Reviewed dependency-only registry aliases; all existing profiles stay exact.\nPROFILES.update("+repr(aliases)+")\n"
profile_after=profile_before.replace(b'\ndef reviewed_unixunix_makefile',insertion.encode()+b'\ndef reviewed_unixunix_makefile',1)
assert profile_after.replace(insertion.encode(),b'',1)==profile_before
namespace_after={};exec(compile(profile_after,profile_path,'exec'),namespace_after)
assert {k:v for k,v in namespace_after['PROFILES'].items()if k not in aliases}==old_profiles
outputs={registry_path:registry_after,profile_path:profile_after}
# Replace only proven old hashes, starting from original live declaration JSON.
# Re-evaluate from the originals to propagate changed metadata hashes exactly.
# Reproduce the original cleanup against its original owned JSON inventory.
# Later declarations have their own current compiler/source checks.
paths=[p for p in subprocess.check_output(['git','ls-tree','--full-tree','-r','--name-only',baseline,'--','js/standalone'],cwd=root,text=True).splitlines()if p.endswith('.json')]
originals={p:original(p)for p in paths};bases={p:json.loads(b)for p,b in originals.items()}
base_hashes={**{p:sha(b)for p,b in originals.items()},registry_path:sha(registry_before),profile_path:sha(profile_before),**{p:r['beforeSha256']for p,r in changes.items()}}
helper_updates={p:r['afterSha256']for p,r in changes.items()}
# The foundation move predates this recipe, but one live persistence pin still
# names its original libc implementation. Prove the complete moved factory,
# including the sole documented getpid extraction, before migrating that pin.
foundation_baseline='df33dd4d8cbb9ea2268b51385c37c4ad5cdd3a31'
libc_path='js/standalone/libc.js'
libc_before=subprocess.check_output(['git','show',foundation_baseline+':'+libc_path],cwd=root)
libc_after=original(libc_path)
assert read_before(root/libc_path)==libc_after
signature=b'export function createStandaloneLibc(memory,libc,transport,functions) {'
getpid=b'        // Match the configured SDK single-process syscall profile.\n        getpid:()=>42,\n'
assert libc_before.count(signature)==1 and libc_before.count(getpid)==1
assert read_before(root/'js/c-runtime/libc.js').split(signature,1)[1]==libc_before.split(signature,1)[1].replace(getpid,b'',1)
base_hashes[libc_path]=sha(libc_before);helper_updates[libc_path]=sha(libc_after)
# New main's DETECT receipt also binds the pre-foundation address adapter.
# Bind the exact already-reviewed foundation package, not an arbitrary current
# file hash. Its original-C transport comparisons remain a separate gate.
address_path='js/standalone/address-ports.js'
address_before=subprocess.check_output(['git','show',foundation_baseline+':'+address_path],cwd=root)
address_package=[address_path,'js/nethack/address-ports.js','js/c-runtime/address-bindings.js']
address_hashes={}
for path in address_package:
 if read_before(root/path)!=original(path):
  assert path=='js/nethack/address-ports.js','Changed foundation address binding '+path
  spec=importlib.util.spec_from_file_location('qualified_mkobj_address',root/'scripts/check-c-runtime-mkobj-address.py')
  qualifier=importlib.util.module_from_spec(spec);spec.loader.exec_module(qualifier)
  qualifier.verify(root,baseline,original)
 # Reproduce the ORIGINAL package receipt, never substitute later feature bytes.
 address_hashes[path]=sha(original(path))
base_hashes[address_path]=sha(address_before);helper_updates[address_path]=address_hashes[address_path]
# Bring the targeted guard into agreement with main's canonical scope guard.
# Verify the complete script is only these two exact edits before rebinding
# its self-pin in the special-interactions receipt.
guard_path='scripts/check-standalone-special-interactions.mjs'
guard_before=original(guard_path)
old_guard="const baseline=read('docs/runtime-environment/scope-baseline.json');for(const[p,h]of Object.entries(baseline.sha256))assert.equal(sha(p),h,p);"
new_guard="""const baseline=read('docs/runtime-environment/scope-baseline.json');
const corrections=read('docs/runtime-environment/authorized-port-corrections.json').corrections;
assert.deepEqual(corrections.map(row=>row.file),['js/ported/vision.js'],'Only main\\'s explicitly approved correction is allowed');
for(const row of corrections){assert.equal(baseline.sha256[row.file],row.baselineSha256);assert.notEqual(row.correctedSha256,row.baselineSha256);}
const corrected=new Map(corrections.map(row=>[row.file,row.correctedSha256]));
for(const[p,h]of Object.entries(baseline.sha256))assert.equal(sha(p),corrected.get(p)??h,p);"""
guard_edits=[(old_guard,new_guard),('policyFiles:baseline.policyCount,frozenFiles:3','policyFiles:baseline.policyCount,unchangedPolicyFiles:baseline.policyCount-corrections.length,approvedCorrections:corrections.map(row=>row.file),frozenFiles:3')]
guard_after=guard_before.decode()
for before,after in guard_edits:
 assert guard_after.count(before)==1
 guard_after=guard_after.replace(before,after,1)
assert text_before(root/guard_path)==guard_after,'Unreviewed targeted guard edit'
base_hashes[guard_path]=sha(guard_before);helper_updates[guard_path]=sha(guard_after.encode())
pruning=json.loads(text_before(root/'docs/runtime-environment/c-runtime-shim-pruning.json'))
assert pruning['baselineCommit']==baseline
consumer_updates={}
for row in pruning['consumers']:
 assert sha(original(row['file']))==row['beforeSha256']
 assert sha(read_before(root/row['file']))==row['afterSha256']
 base_hashes[row['file']]=row['beforeSha256'];consumer_updates[row['file']]=row['afterSha256']
removed={row['file']:row['beforeSha256']for row in pruning['removed']}
for path,h in removed.items():assert sha(original(path))==h and not(root/path).exists()
def compute(initial_updates,removed_sources):
 updates=dict(initial_updates)
 for iteration in range(30):
  hash_map={base_hashes[p]:h for p,h in updates.items()if p in base_hashes and h!=base_hashes[p]}
  def transform(value,trail):
   if isinstance(value,str):return hash_map.get(value,value)
   if isinstance(value,list):return[transform(v,trail+[str(i)])for i,v in enumerate(value)]
   if isinstance(value,dict):
    result={}
    for key,child in value.items():
     # Retire only this exact forwarding-file pin, never an older stale pin.
     if isinstance(child,str)and any((key==p or key.endswith('/'+p))and child==h for p,h in removed_sources.items()):continue
     newkey=key
     if isinstance(child,str)and child in hash_map and key.startswith('/'):
      matches=[p for p in updates if key.endswith('/'+p)]
      if len(matches)==1:newkey=matches[0]
     assert newkey not in result,'Colliding normalized source pin '+newkey
     result[newkey]=transform(child,trail+[key])
    return result
   return value
  next_outputs={registry_path:registry_after,profile_path:profile_after}
  for p,data in bases.items():
   changed=transform(data,[])
   if changed!=data:next_outputs[p]=(json.dumps(changed,indent=2)+'\n').encode()
  next_updates={**initial_updates,**{p:sha(b)for p,b in next_outputs.items()}}
  if next_updates==updates:return next_outputs
  updates=next_updates
 raise AssertionError('Metadata dependency cycle or unstable rewrite')
intermediate=compute(helper_updates,{})
outputs=compute({**helper_updates,**consumer_updates},removed)
prior_path=root/'docs/runtime-environment/c-runtime-provenance-update.json'
prior=json.loads(text_before(prior_path))if prior_path.exists()else{}
assert prior.get('baselineCommit',baseline)==baseline
prior_hashes={row['file']:row['afterSha256']for row in prior.get('files',[])if row['beforeSha256']==sha(original(row['file']))}
successor_path=root/'docs/runtime-environment/c-runtime-metadata-successors.json'
successors=json.loads(successor_path.read_text())if successor_path.exists()else {'files':{}}
assert not successors.get('baselineCommit')or successors['baselineCommit']==baseline
records=[];audited=[]
for p,expected in outputs.items():
 before=originals.get(p,registry_before if p==registry_path else profile_before)
 actual=read_before(root/p)
 if args.write:
  assert actual in [before,intermediate.get(p,before),expected]or sha(actual)==prior_hashes.get(p),'Refusing unrelated edits '+p
 elif actual!=expected:
  assert p.startswith('js/standalone/')and p.endswith('.json'),'Only declaration metadata may have a qualified successor '+p
  older=json.loads(expected);newer=json.loads(actual)
  for key,value in older.items():
   if key not in ['sourceSha256','referenceHeaderSha256','scope']:
    expected_value=value
    # Only these exact additive native transport descriptions are qualified;
    # every historical callback index/prototype and weapon field stays equal.
    if p=='js/standalone/apply-abi.json' and key=='callbacks':
     source=(root/'js/ported/apply.js').read_text()
     expected_value={name:{**row,'sourceOwner':'apply'if re.search(r'^export function '+re.escape(name)+r'\b',source,re.M)else'foreign'}for name,row in value.items()}
    elif p=='js/standalone/equipment-abi.json' and key=='weapon':
     fields=json.loads((root/'js/standalone/records.json').read_text())['records']['window_procs']['fields']
     windows={'create_nhwindow':('win_create_nhwindow','ii'),'start_menu':('win_start_menu','vij'),'end_menu':('win_end_menu','vip'),'destroy_nhwindow':('win_destroy_nhwindow','vi')}
     assert 'windows'not in value
     assert "#define y_n(query) yn_function(query, ynchars, 'n', TRUE)"in(root/'.cache/wasm64-build/tree/include/hack.h').read_text()
     expected_value={**value,'windows':{name:{'field':field,'signature':sig,'nativeType':fields[field]['ctype']}for name,(field,sig)in windows.items()},'y_n':{'target':'yn_function','choices':'ynchars','default':110,'logging':1}}
    assert newer.get(key)==expected_value,'Changed historical measured declaration '+p+':'+key
  for key,value in older.get('referenceHeaderSha256',{}).items():
   assert newer.get('referenceHeaderSha256',{}).get(key)==value,'Changed original native header '+p+':'+key
  row=successors['files'].get(p)
  audited.append({'file':p,'beforeSha256':sha(expected),'afterSha256':sha(actual),'historicalMeasuredDeclarationsPreserved':True,'addedTopLevelKeys':sorted(set(newer)-set(older))})
  if not args.audit_successors:
   assert row and row['beforeSha256']==sha(expected)and row['afterSha256']==sha(actual),'Unreviewed later provenance change '+p
   assert row['reason']and row['verification'],'Missing successor qualification '+p
 records.append({'file':p,'beforeSha256':sha(before),'afterSha256':sha(expected)})
if args.audit_successors:
 print(json.dumps({'complete':False,'scope':'Read-only candidate inventory; not an acceptance or write operation','baselineCommit':baseline,'files':audited},indent=2));raise SystemExit(0)
# Preserve the historical receipt ordering as well as its exact contents.
if prior.get('files'):
 order={row['file']:i for i,row in enumerate(prior['files'])}
 assert set(order)=={row['file']for row in records},'Changed historical provenance output inventory'
 records.sort(key=lambda row:order[row['file']])
if args.write:
 assert not any(read_before(root/p)!=expected and p in successors['files']for p,expected in outputs.items()),'Use the current feature exporters; do not overwrite qualified successor declarations'
 for p,expected in outputs.items():write_before(root/p,expected)
result={'baselineCommit':baseline,'helperSha256':receipt['helperSha256'],'shimRecipeSha256':sha(read_before(root/'docs/runtime-environment/c-runtime-shim-pruning.json')),'foundationLibcMove':{'baselineCommit':foundation_baseline,'file':libc_path,'beforeSha256':sha(libc_before),'afterSha256':sha(libc_after),'factoryBodyUnchangedExceptGetpid':True},'foundationAddressMove':{'originalBaselineCommit':foundation_baseline,'reviewedFoundationCommit':baseline,'file':address_path,'beforeSha256':sha(address_before),'packageSha256':address_hashes},'targetedScopeGuard':{'file':guard_path,'beforeSha256':sha(guard_before),'afterSha256':sha(guard_after.encode()),'onlyExactApprovedCorrectionAndReportingEdits':True},'registrySourceSelectionUnchanged':True,'existingMakefileProfilesUnchanged':True,'newFiniteProfiles':list(aliases),'files':records,'limitations':'Only proven extraction/pruning/relocation dependencies and their transitive metadata hashes change. Historical aggregate scope/persistence pin failures are not waived.'}
target=root/'docs/runtime-environment/c-runtime-provenance-update.json';expected=json.dumps(result,indent=2)+'\n'
if args.write:write_before(target,expected)
else:assert text_before(target)==expected
print('PASS:',len(records),'owned dependency/provenance files;',len(aliases),'strict finite-profile aliases; C selection unchanged')
