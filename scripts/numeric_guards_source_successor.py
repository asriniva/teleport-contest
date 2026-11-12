"""Exact numeric guards source inverse for historical audits, NOT runtime acceptance."""
import argparse,difflib,hashlib,subprocess
from pathlib import Path
BASE_COMMIT='32d7615adb8338891bc29c0f73638fbee3bab830'
FILE='js/c-runtime/adapter-factories.js'
BEFORE_SHA256='3e930880e7597e2fba2e121472767fd0a03b121fb1f186d0eebbdf70a8cca0e3'
AFTER_SHA256='0b202c0ab92ab9eca26cbf5f4ad92af9a69f6d93a256c6a0051bc1a1f7d21b81'
PATCH='docs/runtime-environment/numeric-guards-source-successor.patch'
PATCH_SHA256='6c4a2088863c33cbcb7f1781fbb953018a2f1e475b77cd4eb583d4b512ecb54d'
sha=lambda b:hashlib.sha256(b).hexdigest()
def baseline_bytes(root):return subprocess.check_output(['git','show',BASE_COMMIT+':'+FILE],cwd=root)
def qualified_before(root,file=FILE):
 assert file==FILE,'Only the exact reviewed numeric guards file is qualified'
 root=Path(root);before=baseline_bytes(root);after=(root/FILE).read_bytes();patch=(root/PATCH).read_bytes()
 assert sha(before)==BEFORE_SHA256,'Wrong immutable numeric guards predecessor'
 assert sha(after)==AFTER_SHA256,'Unknown numeric guards source change'
 expected=''.join(difflib.unified_diff(before.decode().splitlines(True),after.decode().splitlines(True),fromfile='a/'+FILE,tofile='b/'+FILE)).encode()
 assert sha(patch)==PATCH_SHA256 and patch==expected,'Wrong numeric guards source patch'
 return before
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--file');p.add_argument('--check',action='store_true');a=p.parse_args();root=Path(__file__).resolve().parents[1];before=qualified_before(root,a.file or FILE)
 if a.file:
  import sys;sys.stdout.buffer.write(before)
 else:print('PASS exact numeric guards source inverse; not native or full-game acceptance')
