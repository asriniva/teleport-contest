"""Synthetic exact-source negative controls; not native runtime acceptance."""
import importlib.util,subprocess,tempfile
from pathlib import Path
from unittest.mock import patch
root=Path(__file__).resolve().parents[1];spec=importlib.util.spec_from_file_location('q',root/'scripts/type_metadata_source_successor.py');q=importlib.util.module_from_spec(spec);spec.loader.exec_module(q);checks=0
before={p:subprocess.check_output(['git','show',q.BASE_COMMIT+':'+p],cwd=root)for p in q.FILES}
with tempfile.TemporaryDirectory()as temp:
 target=Path(temp)
 def restore():
  for file,row in q.FILES.items():
   for path in [file,row['patch']]:
    p=target/path;p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes((root/path).read_bytes())
 def rejected(fn):
  global checks
  try:fn()
  except AssertionError:checks+=1
  else:raise AssertionError('Unknown source accepted')
 restore()
 with patch.object(q,'baseline_bytes',side_effect=lambda r,p:before[p]):
  for file in q.FILES:assert q.qualified_before(target,file)==before[file];checks+=1
  for file,row in q.FILES.items():
   (target/file).write_bytes((root/file).read_bytes()+b'\n//unknown drift\n')
   for selected in q.FILES:rejected(lambda:q.qualified_before(target,selected))
   restore();(target/row['patch']).write_bytes(b'wrong patch');rejected(lambda:q.qualified_before(target,file));restore()
  rejected(lambda:q.qualified_before(target,'js/ported/vision.js'))
  with patch.object(q,'baseline_bytes',side_effect=lambda r,p:before[p]+b'wrong predecessor'):rejected(lambda:q.validate_cohort(target))
print('PASS',checks,'synthetic exact metadata source/cohort rejection checks; no native acceptance')
