"""Fail-closed immutable-selector cohort controls; not runtime acceptance."""
import subprocess,tempfile
from pathlib import Path
from unittest.mock import patch
import immutable_selectors_source_successor as q
import numeric_guards_source_successor as numeric
import record_index_source_successor as upper
root=Path(__file__).resolve().parents[1]
before={p:subprocess.check_output(['git','show',q.BASE_COMMIT+':'+p],cwd=root)for p in q.FILES}
numeric_before=subprocess.check_output(['git','show',numeric.BASE_COMMIT+':'+numeric.FILE],cwd=root)
upper_before=subprocess.check_output(['git','show',upper.BASE_COMMIT+':'+upper.FILE],cwd=root)
checks=0
with tempfile.TemporaryDirectory()as directory:
 target=Path(directory)
 def put(name,data):
  p=target/name;p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(data)
 def restore():
  for file,row in q.FILES.items():
   for name in [file,row['patch']]:put(name,(root/name).read_bytes())
  for name in ['scripts/immutable_selectors_source_successor.py',numeric.PATCH,upper.PATCH]:put(name,(root/name).read_bytes())
 def reject(fn):
  global checks
  try:fn()
  except(AssertionError,FileNotFoundError):checks+=1
  else:raise AssertionError('Accepted unknown immutable-selector cohort')
 restore()
 with patch.object(q,'baseline_bytes',side_effect=lambda r,p:before[p]),patch.object(numeric,'baseline_bytes',return_value=numeric_before),patch.object(upper,'baseline_bytes',return_value=upper_before):
  assert q.validate_cohort(target)==before;checks+=1
  for file in q.FILES:assert q.qualified_before(target,file)==before[file];checks+=1
  assert numeric.qualified_before(target)==numeric_before;checks+=1
  for file,row in q.FILES.items():
   # Every requested inverse must reject drift in every sibling source/patch.
   put(file,(root/file).read_bytes()+b'\n// unknown source\n')
   for selected in q.FILES:reject(lambda:q.qualified_before(target,selected))
   reject(lambda:numeric.qualified_before(target));restore()
   put(file,before[file])
   for selected in q.FILES:reject(lambda:q.qualified_before(target,selected))
   reject(lambda:numeric.qualified_before(target));restore()
   put(row['patch'],b'wrong patch')
   for selected in q.FILES:reject(lambda:q.qualified_before(target,selected))
   reject(lambda:numeric.qualified_before(target));restore()
   (target/file).unlink();reject(lambda:q.validate_cohort(target));restore()
   (target/row['patch']).unlink();reject(lambda:q.validate_cohort(target));restore()
  for file in ['js/ported/vision.js','../heap.js','js/c-runtime/types.js']:reject(lambda:q.qualified_before(target,file))
  with patch.object(q,'baseline_bytes',side_effect=lambda r,p:before[p]+b'wrong predecessor'):reject(lambda:q.validate_cohort(target))
print('PASS',checks,'synthetic immutable-selector cohort/composition rejection checks; no runtime acceptance')
