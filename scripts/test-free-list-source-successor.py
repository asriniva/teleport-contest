"""Synthetic finite allocator source-inverse checks, not native acceptance."""
import subprocess,tempfile
from pathlib import Path
from unittest.mock import patch
import free_list_source_successor as q
root=Path(__file__).resolve().parents[1];before=subprocess.check_output(['git','show',q.BASE_COMMIT+':'+q.FILE],cwd=root);checks=0
with tempfile.TemporaryDirectory()as directory:
 target=Path(directory)
 def restore():
  for name in[q.FILE,q.PATCH]:
   p=target/name;p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes((root/name).read_bytes())
 def reject(fn):
  global checks
  try:fn()
  except AssertionError:checks+=1
  else:raise AssertionError('Accepted unknown allocator projection')
 restore()
 with patch.object(q,'baseline_bytes',return_value=before):
  assert q.qualified_before(target)==before;checks+=1
  (target/q.FILE).write_bytes((root/q.FILE).read_bytes()+b'//unknown');reject(lambda:q.qualified_before(target));restore()
  (target/q.PATCH).write_bytes(b'wrong patch');reject(lambda:q.qualified_before(target));restore()
  for name in ['js/ported/vision.js','../heap.js','js/c-runtime/types.js']:reject(lambda:q.qualified_before(target,name))
  with patch.object(q,'baseline_bytes',return_value=before+b'wrong'):reject(lambda:q.qualified_before(target))
print('PASS',checks,'synthetic allocator source-inverse rejection checks; no native acceptance')
