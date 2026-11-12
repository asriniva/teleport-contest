#!/usr/bin/env python3
"""Bind exact helper extraction and dependency metadata; never refresh unrelated pins."""
import argparse,copy,hashlib,importlib.util,json,subprocess
from pathlib import Path
root=Path(__file__).resolve().parents[1]
parser=argparse.ArgumentParser();parser.add_argument('--write',action='store_true');args=parser.parse_args()
receipt=json.loads((root/'docs/runtime-environment/c-runtime-helper-extraction.json').read_text());baseline=receipt['baselineCommit']
sha=lambda b:hashlib.sha256(b).hexdigest()
original=lambda p:subprocess.check_output(['git','show',baseline+':'+p],cwd=root)
changes={row['file']:row for row in receipt['files']}
for path,row in changes.items():
 assert sha(original(path))==row['beforeSha256'],path
 assert sha((root/path).read_bytes())==row['afterSha256'],path
helper=receipt['helperFile'];assert sha((root/helper).read_bytes())==receipt['helperSha256']
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
paths=[str(p.relative_to(root))for p in (root/'js/standalone').glob('*.json')]
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
assert (root/libc_path).read_bytes()==libc_after
signature=b'export function createStandaloneLibc(memory,libc,transport,functions) {'
getpid=b'        // Match the configured SDK single-process syscall profile.\n        getpid:()=>42,\n'
assert libc_before.count(signature)==1 and libc_before.count(getpid)==1
assert (root/'js/c-runtime/libc.js').read_bytes().split(signature,1)[1]==libc_before.split(signature,1)[1].replace(getpid,b'',1)
base_hashes[libc_path]=sha(libc_before);helper_updates[libc_path]=sha(libc_after)
# New main's DETECT receipt also binds the pre-foundation address adapter.
# Bind the exact already-reviewed foundation package, not an arbitrary current
# file hash. Its original-C transport comparisons remain a separate gate.
address_path='js/standalone/address-ports.js'
address_before=subprocess.check_output(['git','show',foundation_baseline+':'+address_path],cwd=root)
address_package=[address_path,'js/nethack/address-ports.js','js/c-runtime/address-bindings.js']
address_hashes={}
for path in address_package:
 assert (root/path).read_bytes()==original(path),'Changed foundation address binding '+path
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
assert (root/guard_path).read_text()==guard_after,'Unreviewed targeted guard edit'
base_hashes[guard_path]=sha(guard_before);helper_updates[guard_path]=sha(guard_after.encode())
pruning=json.loads((root/'docs/runtime-environment/c-runtime-shim-pruning.json').read_text())
assert pruning['baselineCommit']==baseline
consumer_updates={}
for row in pruning['consumers']:
 assert sha(original(row['file']))==row['beforeSha256']
 assert sha((root/row['file']).read_bytes())==row['afterSha256']
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
prior=json.loads(prior_path.read_text())if prior_path.exists()else{}
assert prior.get('baselineCommit',baseline)==baseline
prior_hashes={row['file']:row['afterSha256']for row in prior.get('files',[])if row['beforeSha256']==sha(original(row['file']))}
records=[]
for p,expected in outputs.items():
 before=originals.get(p,registry_before if p==registry_path else profile_before)
 actual=(root/p).read_bytes()
 if args.write:
  assert actual in [before,intermediate.get(p,before),expected]or sha(actual)==prior_hashes.get(p),'Refusing unrelated edits '+p
 else:assert actual==expected,'Provenance differs '+p
 records.append({'file':p,'beforeSha256':sha(before),'afterSha256':sha(expected)})
if args.write:
 for p,expected in outputs.items():(root/p).write_bytes(expected)
result={'baselineCommit':baseline,'helperSha256':receipt['helperSha256'],'shimRecipeSha256':sha((root/'docs/runtime-environment/c-runtime-shim-pruning.json').read_bytes()),'foundationLibcMove':{'baselineCommit':foundation_baseline,'file':libc_path,'beforeSha256':sha(libc_before),'afterSha256':sha(libc_after),'factoryBodyUnchangedExceptGetpid':True},'foundationAddressMove':{'originalBaselineCommit':foundation_baseline,'reviewedFoundationCommit':baseline,'file':address_path,'beforeSha256':sha(address_before),'packageSha256':address_hashes},'targetedScopeGuard':{'file':guard_path,'beforeSha256':sha(guard_before),'afterSha256':sha(guard_after.encode()),'onlyExactApprovedCorrectionAndReportingEdits':True},'registrySourceSelectionUnchanged':True,'existingMakefileProfilesUnchanged':True,'newFiniteProfiles':list(aliases),'files':records,'limitations':'Only proven extraction/pruning/relocation dependencies and their transitive metadata hashes change. Historical aggregate scope/persistence pin failures are not waived.'}
target=root/'docs/runtime-environment/c-runtime-provenance-update.json';expected=json.dumps(result,indent=2)+'\n'
if args.write:target.write_text(expected)
else:assert target.read_text()==expected
print('PASS:',len(records),'owned dependency/provenance files;',len(aliases),'strict finite-profile aliases; C selection unchanged')
