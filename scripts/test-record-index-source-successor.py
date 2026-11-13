"""Prepared finite record-index/cohort composition controls; not acceptance."""
import subprocess,tempfile
from pathlib import Path
from unittest.mock import patch
import record_index_source_successor as q
import immutable_selectors_source_successor as selectors
import numeric_guards_source_successor as numeric
import full_replay_source_successor as replay
root=Path(__file__).resolve().parents[1]
before=subprocess.check_output(['git','show',q.BASE_COMMIT+':'+q.FILE],cwd=root)
cohort={f:subprocess.check_output(['git','show',selectors.BASE_COMMIT+':'+f],cwd=root)for f in selectors.FILES}
oldest=subprocess.check_output(['git','show',numeric.BASE_COMMIT+':'+numeric.FILE],cwd=root)
checks=0
with tempfile.TemporaryDirectory()as directory:
 target=Path(directory)
 def put(name,data):
  p=target/name;p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(data)
 (target/'.git').write_text('gitdir: '+subprocess.check_output(['git','rev-parse','--absolute-git-dir'],cwd=root,text=True).strip()+'\n')
 def restore():
  for file,row in replay.FILES.items():
   for name in [file,row['patch']]:put(name,(root/name).read_bytes())
  for file,row in selectors.FILES.items():
   for name in[file,row['patch']]:put(name,(root/name).read_bytes())
  for name in[q.PATCH,numeric.PATCH,'scripts/immutable_selectors_source_successor.py']:put(name,(root/name).read_bytes())
 def reject(fn):
  global checks
  try:fn()
  except(AssertionError,FileNotFoundError):checks+=1
  else:raise AssertionError('Accepted unknown record-index projection')
 restore()
 with patch.object(q,'baseline_bytes',return_value=before),patch.object(selectors,'baseline_bytes',side_effect=lambda r,f:cohort[f]),patch.object(numeric,'baseline_bytes',return_value=oldest):
  def composed():
   assert selectors.validate_cohort(target)==cohort
   assert numeric.qualified_before(target)==oldest
  assert q.qualified_before(target)==before;checks+=1
  composed();checks+=1
  for name in[q.FILE,q.PATCH]:
   put(name,(root/name).read_bytes()+b'unknown')
   reject(lambda:q.qualified_before(target));reject(composed);restore()
   (target/name).unlink();reject(lambda:q.qualified_before(target));reject(composed);restore()
  for file,row in selectors.FILES.items():
   for name in[file,row['patch']]:
    put(name,(root/name).read_bytes()+b'unknown')
    for selected in selectors.FILES:reject(lambda:selectors.qualified_before(target,selected))
    reject(lambda:numeric.qualified_before(target));restore()
  put(numeric.PATCH,b'wrong');reject(lambda:numeric.qualified_before(target));restore()
  for name in['js/ported/vision.js','../adapter-factories.js','js/c-runtime/heap.js']:
   reject(lambda:q.qualified_before(target,name));reject(lambda:selectors.qualified_before(target,name))
  with patch.object(q,'baseline_bytes',return_value=before+b'wrong'):
   reject(lambda:q.qualified_before(target));reject(composed)
  # Exact original selector successor stays supported without the new patch.
  put(q.FILE,before);(target/q.PATCH).unlink();composed();checks+=1
  reject(lambda:q.qualified_before(target));restore()
  put(q.FILE,before);reject(lambda:q.qualified_before(target));restore()
print('PASS',checks,'synthetic record-index/cohort controls; no runtime acceptance')
