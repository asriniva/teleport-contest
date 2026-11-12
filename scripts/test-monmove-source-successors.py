#!/usr/bin/env python3
import sys as _layout_sys
from pathlib import Path as _LayoutPath
_layout_sys.path.insert(0,str(_LayoutPath(__file__).resolve().parent))
from nethack_layout import historical_cli as _prior_layout_cli
if __name__=='__main__':_prior_layout_cli(__file__)
"""Synthetic fail-closed source qualification/API tests, not native acceptance."""
import copy,importlib.util,json,os,shutil,subprocess,tempfile
from pathlib import Path
from unittest.mock import patch
source=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('monmove_qualification',source/'scripts/monmove_source_successors.py');q=importlib.util.module_from_spec(spec);spec.loader.exec_module(q)
checks=0
with tempfile.TemporaryDirectory(prefix='monmove-source-qualification-')as directory:
 root=Path(directory);before={p:('base '+p+'\n').encode()for p in q.ALLOWED};after={p:b+b'exact reviewed transport\n'for p,b in before.items()};target='js/nethack/monster-movement.js';sibling='js/nethack/monmove-abi.json';rawpath='docs/runtime-environment/synthetic-native.json';raw=b'{"syntheticOnly":true}\n'
 proof={'complete':True,'originalNativeCompared':True,'baseCommit':q.BASE_COMMIT,'qualifiedSourceSha256':{p:q.sha(b)for p,b in after.items()},'rawProofs':{rawpath:q.sha(raw)}}
 declaration={'version':1,'baseCommit':q.BASE_COMMIT,'nativeProof':q.PROOF,'files':{p:{'beforeSha256':q.sha(before[p]),'afterSha256':q.sha(after[p]),'patch':'docs/runtime-environment/monmove-source-successors/'+Path(p).name+'.patch','patchSha256':q.sha(q.canonical_patch(p,before[p],after[p]))}for p in q.ALLOWED}}
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
 # Exercise real layered JavaScript/Python readers with an isolated read-only Git shim.
 for name in ['services-layout-audit.mjs','services_layout_audit.py','services_layout_successors.py','post_default_successors.py','monmove_source_successors.py','window_headers_source_successors.py']:
  (root/'scripts').mkdir(exist_ok=True);shutil.copyfile(source/'scripts'/name,root/'scripts'/name)
 (root/'scripts/pure-js-fixtures').mkdir();shutil.copyfile(source/'scripts/pure-js-fixtures/qualification.mjs',root/'scripts/pure-js-fixtures/qualification.mjs')
 put('history.json',json.dumps({p:b.decode()for p,b in before.items()}).encode())
 put('docs/runtime-environment/services-layout.json',json.dumps({'baselineCommit':'fixture-layout','moves':{},'files':[{'file':sibling,'destination':sibling,'beforeSha256':q.sha(b'pre-layout '+before[sibling]),'afterSha256':q.sha(before[sibling])}]}).encode())
 put('bin/git',('#!/usr/bin/env python3\nimport json,sys,pathlib\nh=json.loads((pathlib.Path(__file__).parent.parent/"history.json").read_text())\nif sys.argv[1]=="ls-tree":\n assert sys.argv[4]=="'+q.BASE_COMMIT+'";print(sys.argv[-1])\nelse:\n assert sys.argv[1]=="show";c,p=sys.argv[2].split(":",1);assert c in ["'+q.BASE_COMMIT+'","fixture-layout"];sys.stdout.write(("pre-layout "if c=="fixture-layout"else"")+h[p])\n').encode());(root/'bin/git').chmod(0o755)
 env={**os.environ,'PATH':str(root/'bin')+os.pathsep+os.environ.get('PATH','')};node=source/'.cache/emsdk/node/24.19.0_64bit/bin/node'
 js='import fs from "node:fs";import assert from "node:assert/strict";import{readBeforeLayout as read,writeBeforeLayout as write,existsBeforeLayout as exists}from "./scripts/services-layout-audit.mjs";const p="'+target+'",r="'+sibling+'",a=fs.readFileSync(p);assert.equal(read(p,"utf8"),"base '+target+'\\n");assert.equal(read(r,"utf8"),"pre-layout base '+sibling+'\\n");assert.equal(exists(p),true);assert.throws(()=>write(p,read(p)),/Refusing to overwrite qualified MONMOVE/);assert.deepEqual(fs.readFileSync(p),a);'
 run=subprocess.run([str(node),'--input-type=module','-e',js],cwd=root,env=env,text=True,capture_output=True);assert run.returncode==0,run.stdout+run.stderr;checks+=5
 py='from pathlib import Path;from services_layout_audit import read_before,write_before;p=Path("'+target+'");a=p.read_bytes();assert read_before(p)==b"base '+target+'\\n";assert read_before(Path("'+sibling+'"))==b"pre-layout base '+sibling+'\\n"\ntry:write_before(p,read_before(p))\nexcept AssertionError:pass\nelse:raise AssertionError("accepted overwrite")\nassert p.read_bytes()==a'
 run=subprocess.run([os.sys.executable,'-c','import sys;sys.path.insert(0,"scripts");'+py],cwd=root,env=env,text=True,capture_output=True);assert run.returncode==0,run.stdout+run.stderr;checks+=4
print('PASS',checks,'synthetic MONMOVE qualification and real layered API checks; no native acceptance claimed')
