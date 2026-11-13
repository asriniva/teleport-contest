"""Exact immutable-selector cohort inverse for historical audits, NOT acceptance.

Runtime/native/recorder checks execute production sources. Each requested inverse
validates all three current files and exact patches before projecting pinned bytes.
"""
import argparse,difflib,hashlib,subprocess
from pathlib import Path
BASE_COMMIT='d9c2321e4799679f0b52c19722db6e2423119b07'
FILES={'js/c-runtime/adapter-factories.js': {'beforeSha256': '0b202c0ab92ab9eca26cbf5f4ad92af9a69f6d93a256c6a0051bc1a1f7d21b81', 'afterSha256': 'a12022a1380216d383393dac72dd6c945089185803026d722bc1e529ab3ed1e4', 'patch': 'docs/runtime-environment/immutable-selectors-source-successors/adapter-factories.js.patch', 'patchSha256': 'bbd1bbaa2f1110ddee1a9ba7f0e5fa28e0e7a64019c52306fefa02d27aafbdde'}, 'js/nethack/bindings/display.js': {'beforeSha256': 'd79c4aea1974ea4dc6a24f6eb5b3c31bb1687def0be7ae7137f191dcd0bbf0a1', 'afterSha256': '5e2d0447eaf45485a52d80134c1f3f285452669165f852dd5d4a94b05a127ac1', 'patch': 'docs/runtime-environment/immutable-selectors-source-successors/display.js.patch', 'patchSha256': '64baf3f8d0d864f9a575d359bcb3b19b6798e6b108347e0e5ab9b59c66796b45'}, 'js/nethack/bindings/invent.js': {'beforeSha256': '1b65cddfea7ae583e5f931676d6cad2c8d83cf19df22220570c5d7f5a354ba9d', 'afterSha256': '9e98d300495e5f5e24d4cd1af171084b4a11e4822e612dd27c05217e485f17ad', 'patch': 'docs/runtime-environment/immutable-selectors-source-successors/invent.js.patch', 'patchSha256': '2e432611297e4529ed0060131eaed9f79bb0f38df6359d78f134fe08c4aa90a1'}}
sha=lambda b:hashlib.sha256(b).hexdigest()
def baseline_bytes(root,file):return subprocess.check_output(['git','show',BASE_COMMIT+':'+file],cwd=root)
def canonical_patch(file,before,after):return ''.join(difflib.unified_diff(before.decode().splitlines(True),after.decode().splitlines(True),fromfile='a/'+file,tofile='b/'+file)).encode()
def validate_cohort(root):
 root=Path(root);before_images={}
 for file,row in FILES.items():
  before=baseline_bytes(root,file);after=(root/file).read_bytes();patch=(root/row['patch']).read_bytes()
  assert sha(before)==row['beforeSha256'],'Wrong immutable-selector predecessor: '+file
  assert sha(after)==row['afterSha256'],'Unknown immutable-selector source change: '+file
  assert sha(patch)==row['patchSha256']and patch==canonical_patch(file,before,after),'Wrong immutable-selector source patch: '+file
  before_images[file]=before
 return before_images
def qualified_before(root,file):
 assert file in FILES,'Only the exact three immutable-selector files are qualified'
 return validate_cohort(root)[file]
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--file');p.add_argument('--check',action='store_true');a=p.parse_args();root=Path(__file__).resolve().parents[1]
 if a.file:
  import sys;sys.stdout.buffer.write(qualified_before(root,a.file))
 else:validate_cohort(root);print('PASS exact three-file immutable-selector source inverse; not native or game acceptance')
