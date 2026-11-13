"""Exact pointer-limit cohort inverse for historical audits, NOT acceptance.

Runtime/native/recorder checks execute production sources. Each requested inverse
validates all three current files and exact patches before projecting pinned bytes.
"""
import argparse,difflib,hashlib,subprocess
from pathlib import Path
BASE_COMMIT='b65bb00d46b4eaceb05e099bf61f946ea33956d2'
FILES={'js/nethack/bindings/hack.js': {'beforeSha256': '3a6326e2db69108f77466a168d211e486c1c79e0004b6c330d0fcebea223dfa6', 'afterSha256': '0b0641bb09b28421176dc279ce28364cbdd96fdb4826a54e2d912733a61eefb5', 'patch': 'docs/runtime-environment/pointer-limit-source-successors/hack.js.patch', 'patchSha256': '5aa1ef027e5daa4484862cf17a975dc8d1c85b0ee8ab7a362b9b0f252a98116d'}, 'js/nethack/bindings/mon.js': {'beforeSha256': 'e419fa0eab1f2317bf2665393237d8413961ea6200fad2ec67784ec2528c585a', 'afterSha256': '1ba65ed250d94871359b1f33c5ad1f6c0df345dc0631f9436a1697f829a16563', 'patch': 'docs/runtime-environment/pointer-limit-source-successors/mon.js.patch', 'patchSha256': '3c521d10ce28ebaeb61dd59110595e222555bf3c77d3154f80a117a3d834a050'}, 'js/nethack/bindings/wintty.js': {'beforeSha256': '17015390be8a1043082c7727ce3c1840f218c599fdc0512c9f9b7145c23d43f7', 'afterSha256': '4fcf1fa3ee2e2e1fe75fa8a1b2e2a215bacd6223cfc43fa277aa5059fcab1ebd', 'patch': 'docs/runtime-environment/pointer-limit-source-successors/wintty.js.patch', 'patchSha256': 'ecbda20edc6df7f0a9021c5e152b97c71881bc19855f0b3d2310370ee7c58e4e'}}
sha=lambda b:hashlib.sha256(b).hexdigest()
def baseline_bytes(root,file):return subprocess.check_output(['git','show',BASE_COMMIT+':'+file],cwd=root)
def canonical_patch(file,before,after):return ''.join(difflib.unified_diff(before.decode().splitlines(True),after.decode().splitlines(True),fromfile='a/'+file,tofile='b/'+file)).encode()
def current_bytes(root,file):
 # The later integer-wall-flag fix has its own exact source inverse. Apply
 # that layer before checking this immutable pointer-limit cohort.
 if file=='js/nethack/bindings/mon.js'and(root/'docs/engine-service-source-successors.json').exists():
  from engine_service_source_successors import qualified_before
  return qualified_before(root,file)
 return(root/file).read_bytes()
def validate_cohort(root):
 root=Path(root);before_images={}
 for file,row in FILES.items():
  before=baseline_bytes(root,file);after=current_bytes(root,file);patch=(root/row['patch']).read_bytes()
  assert sha(before)==row['beforeSha256'],'Wrong pointer-limit predecessor: '+file
  assert sha(after)==row['afterSha256'],'Unknown pointer-limit source change: '+file
  assert sha(patch)==row['patchSha256']and patch==canonical_patch(file,before,after),'Wrong pointer-limit source patch: '+file
  before_images[file]=before
 return before_images
def qualified_before(root,file):
 assert file in FILES,'Only the exact three pointer-limit files are qualified'
 return validate_cohort(root)[file]
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--file');p.add_argument('--check',action='store_true');a=p.parse_args();root=Path(__file__).resolve().parents[1]
 if a.file:
  import sys;sys.stdout.buffer.write(qualified_before(root,a.file))
 else:validate_cohort(root);print('PASS exact three-file pointer-limit source inverse; not native or game acceptance')
