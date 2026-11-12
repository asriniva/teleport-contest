"""Exact one-file scalar load inverse for historical audits, NOT native acceptance.

Current tests execute actual production code. Only these reviewed source bytes
can project their immutable predecessor; no historical receipt is regenerated.
"""
import argparse,difflib,hashlib,subprocess
from pathlib import Path
BASE_COMMIT='819d16fb5bcb59c96065a3519aa643a117cfc601'
FILES={'js/c-runtime/types.js': {'beforeSha256': 'da05a56c3bc624b880f88303bd7a089b74832bd2e91d3748ac53c4da6a46b8b4', 'afterSha256': '543ffd41017343044456f297959f8f8b576c25911c40d9c7db7943367f2b1391', 'patch': 'docs/runtime-environment/scalar-load-source-successors/types.js.patch', 'patchSha256': 'd587b3733040d0bbcb19fb5dcddb8049df99a6b1e5d2d8b6d3c371815c2df791'}}
sha=lambda b:hashlib.sha256(b).hexdigest()
def baseline_bytes(root,file):return subprocess.check_output(['git','show',BASE_COMMIT+':'+file],cwd=root)
def canonical_patch(file,before,after):return ''.join(difflib.unified_diff(before.decode().splitlines(True),after.decode().splitlines(True),fromfile='a/'+file,tofile='b/'+file)).encode()
def validate_cohort(root):
 root=Path(root);before_images={}
 for file,row in FILES.items():
  before=baseline_bytes(root,file);after=(root/file).read_bytes();patch=(root/row['patch']).read_bytes()
  assert sha(before)==row['beforeSha256'],'Wrong immutable C scalar load predecessor'
  assert sha(after)==row['afterSha256'],'Unknown C scalar load source change'
  assert sha(patch)==row['patchSha256']and patch==canonical_patch(file,before,after),'Wrong C scalar load source patch'
  before_images[file]=before
 return before_images
def qualified_before(root,file):
 assert file in FILES,'Only the reviewed scalar load file is qualified'
 return validate_cohort(root)[file]
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--file');p.add_argument('--check',action='store_true');a=p.parse_args();root=Path(__file__).resolve().parents[1]
 if a.file:
  import sys;sys.stdout.buffer.write(qualified_before(root,a.file))
 else:
  for file in FILES:qualified_before(root,file)
  print('PASS exact one-file scalar load source inverse; no native or complete-game acceptance claimed')
