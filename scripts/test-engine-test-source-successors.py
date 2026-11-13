from pathlib import Path
import json,tempfile
from engine_test_source_successors import ROOT,ALLOWED,qualified_before
checks=0
with tempfile.TemporaryDirectory(prefix='engine-test-inverse-') as directory:
 root=Path(directory);(root/'docs').mkdir();data=(ROOT/'docs/engine-test-source-successors.json').read_text()
 (root/'docs/engine-test-source-successors.json').write_text(data)
 for name in sorted(ALLOWED):
  file=root/name;file.parent.mkdir(exist_ok=True);actual=(ROOT/name).read_bytes();file.write_bytes(actual)
  assert qualified_before(root,name)==qualified_before(ROOT,name);checks+=1
  file.write_bytes(actual+b'\n')
  try:qualified_before(root,name)
  except AssertionError:checks+=1
  else:raise AssertionError('Unreviewed test edit accepted')
  file.write_bytes(actual)
 changed=json.loads(data);changed['files']['extra.py']=changed['files'][next(iter(ALLOWED))]
 (root/'docs/engine-test-source-successors.json').write_text(json.dumps(changed))
 try:qualified_before(root,next(iter(ALLOWED)))
 except AssertionError:checks+=1
 else:raise AssertionError('Unexpected test membership accepted')
print('PASS',checks,'test-source inverse/mutation/membership controls')
