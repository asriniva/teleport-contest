"""Exact record-index regexp inverse for historical audits, NOT acceptance."""
import argparse,difflib,hashlib,subprocess
from pathlib import Path
BASE_COMMIT='7732c2a2d8e09c38fd3215f2173490c424e8e9aa'
FILE='js/c-runtime/adapter-factories.js'
BEFORE_SHA256='a12022a1380216d383393dac72dd6c945089185803026d722bc1e529ab3ed1e4'
AFTER_SHA256='84b32a1e910f43c97ae8cbebc5d0aa4d8e1f50db7b7b094fb94ffda1bb603a93'
PATCH='docs/runtime-environment/record-index-source-successor.patch'
PATCH_SHA256='8e72724ca4ba727c59166d9f12160b9b7dd0b9e5b903683035e7eab7e9314448'
sha=lambda b:hashlib.sha256(b).hexdigest()
def baseline_bytes(root):return subprocess.check_output(['git','show',BASE_COMMIT+':'+FILE],cwd=root)
def qualified_before(root,file=FILE):
 assert file==FILE,'Only the exact reviewed record-index file is qualified'
 root=Path(root);before=baseline_bytes(root);after=(root/FILE).read_bytes();patch=(root/PATCH).read_bytes()
 if sha(after)!=AFTER_SHA256:
  from full_replay_source_successor import current_before
  after=current_before(root,FILE)
 assert sha(before)==BEFORE_SHA256,'Wrong immutable record-index predecessor'
 assert sha(after)==AFTER_SHA256,'Unknown record-index source change'
 expected=''.join(difflib.unified_diff(before.decode().splitlines(True),after.decode().splitlines(True),fromfile='a/'+FILE,tofile='b/'+FILE)).encode()
 assert sha(patch)==PATCH_SHA256 and patch==expected,'Wrong record-index source patch'
 return before
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--file');p.add_argument('--check',action='store_true');a=p.parse_args();root=Path(__file__).resolve().parents[1];before=qualified_before(root,a.file or FILE)
 if a.file:
  import sys;sys.stdout.buffer.write(before)
 else:print('PASS exact record-index source inverse; not native or full-game acceptance')
