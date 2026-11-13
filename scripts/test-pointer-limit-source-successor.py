"""Fail-closed pointer-limit source cohort controls; not runtime acceptance."""
import subprocess,tempfile
from pathlib import Path
from unittest.mock import patch
import pointer_limit_source_successor as q
root=Path(__file__).resolve().parents[1]
before={p:subprocess.check_output(['git','show',q.BASE_COMMIT+':'+p],cwd=root)for p in q.FILES}
checks=0
with tempfile.TemporaryDirectory()as directory:
 target=Path(directory)
 def put(name,data):
  p=target/name;p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(data)
 def restore():
  for file,row in q.FILES.items():
   for name in [file,row['patch']]:put(name,q.current_bytes(root,name))
 def reject(fn):
  global checks
  try:fn()
  except(AssertionError,FileNotFoundError):checks+=1
  else:raise AssertionError('Accepted unknown pointer-limit source cohort')
 restore()
 with patch.object(q,'baseline_bytes',side_effect=lambda r,p:before[p]):
  assert q.validate_cohort(target)==before;checks+=1
  for file in q.FILES:assert q.qualified_before(target,file)==before[file];checks+=1
  for file,row in q.FILES.items():
   put(file,(root/file).read_bytes()+b'\n// unknown source\n')
   for selected in q.FILES:reject(lambda:q.qualified_before(target,selected))
   restore();put(file,before[file])
   for selected in q.FILES:reject(lambda:q.qualified_before(target,selected))
   restore();put(row['patch'],b'wrong patch')
   for selected in q.FILES:reject(lambda:q.qualified_before(target,selected))
   restore();(target/file).unlink();reject(lambda:q.validate_cohort(target))
   restore();(target/row['patch']).unlink();reject(lambda:q.validate_cohort(target));restore()
  for file in ['js/ported/vision.js','../heap.js','js/c-runtime/adapter-factories.js']:reject(lambda:q.qualified_before(target,file))
  with patch.object(q,'baseline_bytes',side_effect=lambda r,p:before[p]+b'wrong predecessor'):reject(lambda:q.validate_cohort(target))
print('PASS',checks,'synthetic pointer-limit source/cohort rejection checks; no runtime acceptance')
