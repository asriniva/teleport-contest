"""Exact two-file metadata inverse for historical audits, NOT native acceptance.

Current tests execute actual production code. Only these reviewed source bytes
can project their immutable predecessor; no historical receipt is regenerated.
"""
import argparse,difflib,hashlib,subprocess
from pathlib import Path
BASE_COMMIT='a2adb495bee21ccbc2ceb9ead95a8083be342df0'
FILES={'js/c-runtime/types.js': {'beforeSha256': '255b8886f553dfd06e6f56f0cfe417d03e9a8fda48f455fe6a8b94b341d10cc2', 'afterSha256': 'da05a56c3bc624b880f88303bd7a089b74832bd2e91d3748ac53c4da6a46b8b4', 'patch': 'docs/runtime-environment/type-metadata-source-successors/types.js.patch', 'patchSha256': 'a3f1ad3846e3211adf487a68066e6a6c4728a8b8ba3b6feec8724bc6649998f8'}, 'js/c-runtime/address-bindings.js': {'beforeSha256': '356e68eb124886364a45828d5098c919454775c30f42849398f7d0d9e0815cb9', 'afterSha256': '098cc9841e9d10262f5ab36f8c2d005cf2a2f742fd1e7d0cb95edb2427c83c2f', 'patch': 'docs/runtime-environment/type-metadata-source-successors/address-bindings.js.patch', 'patchSha256': 'd82282b6598a75ae95f366167b0413a143373bc36d29ee964f0bc2a3a6126bda'}}
sha=lambda b:hashlib.sha256(b).hexdigest()
def baseline_bytes(root,file):return subprocess.check_output(['git','show',BASE_COMMIT+':'+file],cwd=root)
def canonical_patch(file,before,after):return ''.join(difflib.unified_diff(before.decode().splitlines(True),after.decode().splitlines(True),fromfile='a/'+file,tofile='b/'+file)).encode()
def validate_cohort(root):
 root=Path(root);before_images={}
 for file,row in FILES.items():
  before=baseline_bytes(root,file);after=(root/file).read_bytes();patch=(root/row['patch']).read_bytes()
  if file=='js/c-runtime/types.js'and(root/'scripts/scalar_load_source_successor.py').exists():
   from scalar_load_source_successor import qualified_before as scalar_before
   after=scalar_before(root,file)
  assert sha(before)==row['beforeSha256'],'Wrong immutable C metadata predecessor'
  assert sha(after)==row['afterSha256'],'Unknown C metadata source change'
  assert sha(patch)==row['patchSha256']and patch==canonical_patch(file,before,after),'Wrong C metadata source patch'
  before_images[file]=before
 return before_images
def qualified_before(root,file):
 assert file in FILES,'Only the two reviewed C metadata files are qualified'
 return validate_cohort(root)[file]
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--file');p.add_argument('--check',action='store_true');a=p.parse_args();root=Path(__file__).resolve().parents[1]
 if a.file:
  import sys;sys.stdout.buffer.write(qualified_before(root,a.file))
 else:
  for file in FILES:qualified_before(root,file)
  print('PASS exact two-file metadata source inverse; no native or complete-game acceptance claimed')
