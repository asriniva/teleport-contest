"""Exact load plan source inverse for historical audits, NOT runtime acceptance."""
import argparse,difflib,hashlib,subprocess
from pathlib import Path
BASE_COMMIT='ec9917ff365eb631b51269fb728cb16c28fc5fb6'
FILE='js/c-runtime/types.js'
BEFORE_SHA256='543ffd41017343044456f297959f8f8b576c25911c40d9c7db7943367f2b1391'
AFTER_SHA256='21a3ca97e98fcf85032458a6a737e496d4c54fff1bb1d32822d3da305ae18ac5'
PATCH='docs/runtime-environment/load-plan-source-successor.patch'
PATCH_SHA256='89329dd475779451ff583548b35c9e9869a1dd4a71fb122d1268671979e8b532'
sha=lambda b:hashlib.sha256(b).hexdigest()
def baseline_bytes(root):return subprocess.check_output(['git','show',BASE_COMMIT+':'+FILE],cwd=root)
def qualified_before(root,file=FILE):
 assert file==FILE,'Only the exact reviewed load plan file is qualified'
 root=Path(root);before=baseline_bytes(root);after=(root/FILE).read_bytes();patch=(root/PATCH).read_bytes()
 assert sha(before)==BEFORE_SHA256,'Wrong immutable load plan predecessor'
 assert sha(after)==AFTER_SHA256,'Unknown load plan source change'
 expected=''.join(difflib.unified_diff(before.decode().splitlines(True),after.decode().splitlines(True),fromfile='a/'+FILE,tofile='b/'+FILE)).encode()
 assert sha(patch)==PATCH_SHA256 and patch==expected,'Wrong load plan source patch'
 return before
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--file');p.add_argument('--check',action='store_true');a=p.parse_args();root=Path(__file__).resolve().parents[1];before=qualified_before(root,a.file or FILE)
 if a.file:
  import sys;sys.stdout.buffer.write(before)
 else:print('PASS exact load plan source inverse; not native or full-game acceptance')
