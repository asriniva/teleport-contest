#!/usr/bin/env python3
"""Isolated guard fixtures only: not native gameplay acceptance evidence."""
import copy,importlib.util,json,tempfile,os,shutil,subprocess
from pathlib import Path
from unittest.mock import patch
spec=importlib.util.spec_from_file_location('qualified_layout',Path(__file__).with_name('services_layout_successors.py'));q=importlib.util.module_from_spec(spec);spec.loader.exec_module(q)
checks=0
with tempfile.TemporaryDirectory(prefix='services-layout-qualification-')as directory:
 root=Path(directory);history={p:('historical '+p+'\n').encode()for p in q.ALLOWED};after={p:b+b'qualified later native boundary\n'for p,b in history.items()};proof_path='docs/runtime-environment/native-proof.json';proof={'complete':True,'qualifiedSourceSha256':{p:q.sha(b)for p,b in after.items()},'scope':'Synthetic adversarial guard fixture, not native acceptance.'};(root/proof_path).parent.mkdir(parents=True);(root/proof_path).write_text(json.dumps(proof));d={'version':1,'cleanupCommit':q.CLEANUP_COMMIT,'files':{}}
 for i,p in enumerate(sorted(q.ALLOWED)):
  (root/p).parent.mkdir(parents=True,exist_ok=True);(root/p).write_bytes(after[p]);artifact='docs/runtime-environment/patch-'+str(i)+'.patch';pb=q.canonical_patch(p,history[p],after[p]);(root/artifact).write_bytes(pb);d['files'][p]={'beforeSha256':q.sha(history[p]),'afterSha256':q.sha(after[p]),'patch':artifact,'patchSha256':q.sha(pb),'nativeProof':proof_path,'nativeProofSha256':q.sha((root/proof_path).read_bytes())}
 def restore():
  (root/q.DECLARATION).write_text(json.dumps(d));(root/proof_path).write_text(json.dumps(proof))
  for p,b in after.items():(root/p).write_bytes(b);(root/d['files'][p]['patch']).write_bytes(q.canonical_patch(p,history[p],b))
 restore()
 with patch.object(q,'_git_bytes',side_effect=lambda r,p:history[p]):
  for p in sorted(q.ALLOWED):assert q.historical_after(root,p,q.sha(history[p]))==history[p];checks+=1
  expected={p:q.sha(b)for p,b in history.items()}
  assert q.validate_cohort(root,expected)==history;checks+=1
  try:q.validate_cohort(root,expected,write=True)
  except AssertionError as error:
   assert 'Refusing to overwrite qualified post-cleanup feature'in str(error);checks+=1
  else:raise AssertionError('Relocation --write accepted a qualified feature')
  assert all((root/p).read_bytes()==b for p,b in after.items());checks+=1
  p=sorted(q.ALLOWED)[0]
  assert q.verify_historical_output(root,p,history[p])==history[p];checks+=1
  try:q.verify_historical_output(root,p,history[p]+b'changed pinned output')
  except AssertionError as error:
   assert 'Pinned390 cleanup output differs'in str(error);checks+=1
  else:raise AssertionError('Accepted changed historical cleanup output')
  def reject(label):
   global checks
   try:q.historical_after(root,p,q.sha(history[p]))
   except(AssertionError,KeyError,FileNotFoundError):checks+=1
   else:raise AssertionError('Accepted '+label)
  (root/p).write_bytes(after[p]+b'unreviewed');reject('unreviewed source');restore()
  bad=copy.deepcopy(d);bad['files'][p]['beforeSha256']='0'*64;(root/q.DECLARATION).write_text(json.dumps(bad));reject('new historical baseline');restore()
  bad=copy.deepcopy(d);bad['files']['js/unreviewed.js']=bad['files'][p];(root/q.DECLARATION).write_text(json.dumps(bad));reject('seventh path');restore()
  bad=copy.deepcopy(d);del bad['files'][sorted(q.ALLOWED)[-1]];(root/q.DECLARATION).write_text(json.dumps(bad));reject('incomplete cohort');restore()
  (root/d['files'][p]['patch']).write_bytes(b'forged patch');reject('nonexact patch');restore()
  (root/proof_path).write_text(json.dumps({**proof,'complete':False}));bad=copy.deepcopy(d)
  for row in bad['files'].values():row['nativeProofSha256']=q.sha((root/proof_path).read_bytes())
  (root/q.DECLARATION).write_text(json.dumps(bad));reject('unaccepted proof with matching hash');restore()
  modified=after[p]+b'forged later source\n';(root/p).write_bytes(modified);bad=copy.deepcopy(d);row=bad['files'][p];row['afterSha256']=q.sha(modified);pb=q.canonical_patch(p,history[p],modified);(root/row['patch']).write_bytes(pb);row['patchSha256']=q.sha(pb);(root/q.DECLARATION).write_text(json.dumps(bad));reject('forged source/hash/patch reusing native proof');restore()
  bad=copy.deepcopy(d);bad['files'][p]['nativeProof']='docs/runtime-environment/../../secret.json';(root/q.DECLARATION).write_text(json.dumps(bad));reject('artifact traversal');restore()
  try:q.historical_after(root,'js/unreviewed.js')
  except AssertionError:checks+=1
  else:raise AssertionError('Accepted path outside finite set')
  # Exercise the real JS API and Python qualifier CLI in a tiny isolated
  # repository fixture. Only Git's object reader is mocked; no game is run.
  restore()
  scripts=root/'scripts';scripts.mkdir(exist_ok=True)
  source_root=Path(__file__).resolve().parents[1]
  for file in ['services-layout-audit.mjs','services_layout_audit.py','services_layout_successors.py']:
   shutil.copyfile(source_root/'scripts'/file,scripts/file)
  row_path='js/standalone/level-startup.js';prior=b'pre-cleanup '+history[row_path];fixture_recipe={'baselineCommit':'fixture-before-cleanup','moves':{},'files':[{'file':row_path,'destination':row_path,'beforeSha256':q.sha(prior),'afterSha256':q.sha(history[row_path])}]};(root/'docs/runtime-environment/services-layout.json').write_text(json.dumps(fixture_recipe))
  (root/'history.json').write_text(json.dumps({p:b.decode()for p,b in history.items()}))
  bindir=root/'bin';bindir.mkdir();git=bindir/'git'
  git.write_text('#!/usr/bin/env python3\nimport json,sys,pathlib\nassert sys.argv[1]=="show"\ncommit,path=sys.argv[2].split(":",1)\nassert commit in ['+repr(q.CLEANUP_COMMIT)+',"fixture-before-cleanup"]\nsys.stdout.write(("pre-cleanup "if commit=="fixture-before-cleanup"else"")+json.loads((pathlib.Path(__file__).parent.parent/"history.json").read_text())[path])\n');git.chmod(0o755)
  node=source_root/'.cache/emsdk/node/24.19.0_64bit/bin/node'
  code='import fs from "node:fs";import assert from "node:assert/strict";import{pathToFileURL}from "node:url";const api=await import(pathToFileURL(process.cwd()+"/scripts/services-layout-audit.mjs")),file="js/standalone/pager-target-header-functions.js",actual=fs.readFileSync(file),historical=api.readBeforeLayout(file);assert.notDeepEqual(actual,historical);assert.throws(()=>api.writeBeforeLayout(file,historical),/Refusing to overwrite qualified post-cleanup feature/);assert.deepEqual(fs.readFileSync(file),actual);assert.equal(api.readBeforeLayout("js/standalone/level-startup.js","utf8"),"pre-cleanup historical js/standalone/level-startup.js\\n");console.log("PASS JS row inverse/nonrecipe historical-write refusal; no mutation");'
  run=subprocess.run([str(node),'--input-type=module','-e',code],cwd=root,env={**os.environ,'PATH':str(bindir)+os.pathsep+os.environ.get('PATH','')},capture_output=True,text=True)
  assert run.returncode==0,run.stdout+run.stderr
  checks+=4
  python_code='import sys;from pathlib import Path;sys.path.insert(0,"scripts");from services_layout_audit import read_before,write_before;p=Path("js/standalone/pager-target-header-functions.js");actual=p.read_bytes();old=read_before(p);assert old!=actual;write_before(p,old);assert p.read_bytes()==actual;assert read_before(Path("js/standalone/level-startup.js"))==b"pre-cleanup historical js/standalone/level-startup.js\\n"'
  run=subprocess.run([os.sys.executable,'-c',python_code],cwd=root,env={**os.environ,'PATH':str(bindir)+os.pathsep+os.environ.get('PATH','')},capture_output=True,text=True)
  assert run.returncode==0,run.stdout+run.stderr
  checks+=3
  # Unmodified original bytes need no later declaration and remain exact.
  (root/q.DECLARATION).unlink();(root/p).write_bytes(history[p]);assert q.historical_after(root,p,q.sha(history[p]))==history[p];checks+=1
print('PASS exact post-layout qualifier',checks,'isolated positive/adversarial cases; no native acceptance claimed')
