from pathlib import Path
import json,tempfile,subprocess
from unittest.mock import patch
from engine_service_source_successors import ROOT,ALLOWED,qualified_before
checks=0
with tempfile.TemporaryDirectory(prefix='engine-service-inverse-') as directory:
 root=Path(directory);(root/'docs').mkdir();data=(ROOT/'docs/engine-service-source-successors.json').read_text()
 (root/'docs/engine-service-source-successors.json').write_text(data)
 base=json.loads(data)['baseCommit']
 for name in sorted(ALLOWED):
  file=root/name;file.parent.mkdir(parents=True,exist_ok=True);actual=(ROOT/name).read_bytes();file.write_bytes(actual)
  assert qualified_before(root,name)==subprocess.check_output(['git','show',base+':'+name],cwd=ROOT);checks+=1
  file.write_bytes(actual+b'\n')
  try:qualified_before(root,name)
  except AssertionError:checks+=1
  else:raise AssertionError('Unreviewed runtime edit accepted')
  file.write_bytes(actual)
 # The MON fix composes with main's earlier pointer-limit layer. Preserve that
 # cohort's pinned source/patch hashes and reject mutations through every entry.
 import pointer_limit_source_successor as pointer
 for name,row in pointer.FILES.items():
  for source in [name,row['patch']]:
   file=root/source;file.parent.mkdir(parents=True,exist_ok=True);file.write_bytes((ROOT/source).read_bytes())
 original={name:subprocess.check_output(['git','show',pointer.BASE_COMMIT+':'+name],cwd=ROOT)for name in pointer.FILES}
 with patch.object(pointer,'baseline_bytes',side_effect=lambda r,p:original[p]):
  assert pointer.validate_cohort(root)==original;checks+=1
  mon=root/'js/nethack/bindings/mon.js';saved=mon.read_bytes();mon.write_bytes(saved+b'\n')
  for name in pointer.FILES:
   try:pointer.qualified_before(root,name)
   except AssertionError:checks+=1
   else:raise AssertionError('Composed inverse accepted unreviewed MON source')
  mon.write_bytes(saved)
 changed=json.loads(data);changed['files']['extra.js']=changed['files'][next(iter(ALLOWED))]
 (root/'docs/engine-service-source-successors.json').write_text(json.dumps(changed))
 try:qualified_before(root,next(iter(ALLOWED)))
 except AssertionError:checks+=1
 else:raise AssertionError('Unexpected runtime membership accepted')
print('PASS',checks,'service-source inverse/mutation/membership controls; exact pinned prior bytes')
