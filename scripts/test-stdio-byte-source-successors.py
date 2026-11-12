#!/usr/bin/env python3
"""Synthetic fail-closed source qualification/API tests, not native acceptance."""
import copy,importlib.util,json,os,shutil,subprocess,tempfile
from pathlib import Path
from unittest.mock import patch
source=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('stdio_byte_qualification',source/'scripts/stdio_byte_source_successors.py');q=importlib.util.module_from_spec(spec);spec.loader.exec_module(q)
checks=0
with tempfile.TemporaryDirectory(prefix='stdio_byte-source-qualification-')as directory:
 root=Path(directory);before={p:('base '+p+'\n').encode()for p in q.ALLOWED};after={p:b+b'exact reviewed transport\n'for p,b in before.items()};target='js/c-runtime/stdio.js';sibling=target;rawpath='docs/runtime-environment/synthetic-native.json';raw=b'{"syntheticOnly":true}\n'
 proof={'complete':True,'originalNativeCompared':True,'baseCommit':q.BASE_COMMIT,'qualifiedSourceSha256':{p:q.sha(b)for p,b in after.items()},'rawProofs':{rawpath:q.sha(raw)}}
 declaration={'version':1,'baseCommit':q.BASE_COMMIT,'nativeProof':q.PROOF,'files':{p:{'beforeSha256':q.sha(before[p]),'afterSha256':q.sha(after[p]),'patch':'docs/runtime-environment/stdio-byte-source-successors/'+Path(p).name+'.patch','patchSha256':q.sha(q.canonical_patch(p,before[p],after[p]))}for p in q.ALLOWED}}
 def put(p,b):
  p=root/p;p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(b)
 def declare(d=declaration,p=proof):
  d=copy.deepcopy(d);b=json.dumps(p).encode();put(q.PROOF,b);d['nativeProofSha256']=q.sha(b);put(q.DECLARATION,json.dumps(d).encode())
 def restore():
  for p,b in after.items():put(p,b);put(declaration['files'][p]['patch'],q.canonical_patch(p,before[p],b))
  put(rawpath,raw);declare()
 def reject(label,fn=lambda:q.qualified_before(root,target)):
  global checks
  try:fn()
  except(AssertionError,KeyError,ValueError,FileNotFoundError):checks+=1
  else:raise AssertionError('Accepted '+label)
 restore()
 with patch.object(q,'baseline_bytes',side_effect=lambda r,p:before[p]):
  assert q.validate_cohort(root)==before;checks+=1
  for p,b in before.items():assert q.qualified_before(root,p)==b;checks+=1
  for p in [target,sibling]:put(p,after[p]+b'unknown');reject('source drift '+p);restore()
  for field,value in [('complete',False),('originalNativeCompared',False),('baseCommit','0'*40),('rawProofs',{}),('qualifiedSourceSha256',{target:'0'*64})]:declare(p={**proof,field:value});reject('wrong native '+field);restore()
  bad=copy.deepcopy(declaration);bad['baseCommit']='0'*40;declare(bad);reject('wrong original commit');restore()
  bad=copy.deepcopy(declaration);bad['files'][target]['beforeSha256']='0'*64;declare(bad);reject('wrong original bytes');restore()
  bad=copy.deepcopy(declaration);bad['files']['js/extra.js']=bad['files'][target];declare(bad);reject('extra qualified source');restore()
  bad=copy.deepcopy(declaration);del bad['files'][target];declare(bad);reject('missing qualified source');restore()
  put(rawpath,raw+b'changed');reject('changed native receipt');restore()
  bad=copy.deepcopy(declaration);put(bad['files'][target]['patch'],b'forged patch');bad['files'][target]['patchSha256']=q.sha(b'forged patch');declare(bad);reject('hash-matching noncanonical patch');restore()
  bad=copy.deepcopy(declaration);new=after[target]+b'changed implementation';put(target,new);pb=q.canonical_patch(target,before[target],new);put(bad['files'][target]['patch'],pb);bad['files'][target].update(afterSha256=q.sha(new),patchSha256=q.sha(pb));declare(bad);reject('old native proof reused for new implementation');restore()
  bad=copy.deepcopy(declaration);bad['files'][target]['patch']='docs/runtime-environment/../../escape.patch';declare(bad);reject('escaping evidence path');restore()
  reject('unknown source',lambda:q.qualified_before(root,'js/unreviewed.js'))
  reject('overwriting current feature',lambda:q.refuse_write(root,target,before[target]));assert(root/target).read_bytes()==after[target];checks+=1

print('PASS',checks,'synthetic STDIO byte qualification rejection checks; no native acceptance claimed')
