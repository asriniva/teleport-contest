"""Exact allocator source inverse for historical audits, NOT runtime acceptance."""
import argparse,difflib,hashlib,subprocess
from pathlib import Path
BASE_COMMIT='28ec0f3a921fe472b505242e1bc005aeba44b700'
FILE='js/c-runtime/heap.js'
BEFORE_SHA256='0322705c885350962c95f3a587316725114bd4c334dc85e42466843c30827686'
AFTER_SHA256='7f1694bd3dc090cc19e3c65b71475015b822c15b0936909d50de64bfcfd4d3fa'
PATCH='docs/runtime-environment/free-list-source-successor.patch'
PATCH_SHA256='05026e1c0f242f49c63d7324ae7e49fac6e5421ece476bac64f42cb3dc5c08bb'
sha=lambda b:hashlib.sha256(b).hexdigest()
def baseline_bytes(root):return subprocess.check_output(['git','show',BASE_COMMIT+':'+FILE],cwd=root)
def qualified_before(root,file=FILE):
 assert file==FILE,'Only the exact reviewed allocator file is qualified'
 root=Path(root);before=baseline_bytes(root);after=(root/FILE).read_bytes();patch=(root/PATCH).read_bytes()
 assert sha(before)==BEFORE_SHA256,'Wrong immutable allocator predecessor'
 assert sha(after)==AFTER_SHA256,'Unknown allocator source change'
 expected=''.join(difflib.unified_diff(before.decode().splitlines(True),after.decode().splitlines(True),fromfile='a/'+FILE,tofile='b/'+FILE)).encode()
 assert sha(patch)==PATCH_SHA256 and patch==expected,'Wrong allocator source patch'
 return before
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--file');p.add_argument('--check',action='store_true');a=p.parse_args();root=Path(__file__).resolve().parents[1];before=qualified_before(root,a.file or FILE)
 if a.file:
  import sys;sys.stdout.buffer.write(before)
 else:print('PASS exact allocator source inverse; not native or full-game acceptance')
