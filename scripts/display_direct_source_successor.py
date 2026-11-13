"""Exact DISPLAY specialization predecessor for historical audits, NOT acceptance.

Production and parity tests always execute the current code. The inverse checks
all four runtime files and their complete canonical patches, including new files.
"""
import argparse,difflib,hashlib,subprocess
from pathlib import Path
BASE_COMMIT='f58b27e92880b3ffd61d992a1a1d14994f2cec4a'
FILES={'js/nethack/bindings/display.js': {'existed': True, 'beforeSha256': '5e2d0447eaf45485a52d80134c1f3f285452669165f852dd5d4a94b05a127ac1', 'afterSha256': '6628e9a1a0af8fb6e449d61407225d4ae791cf1bdc0efcaaa77b3c4d07a7389d', 'patch': 'docs/runtime-environment/display-direct-source-successors/js_nethack_bindings_display.js.patch', 'patchSha256': 'c448cc3bdeab5fedc8d5ecd1033431dc63c9f5136f864d0247d34bba0b175246'}, 'js/ported/display.js': {'existed': True, 'beforeSha256': '2e26953910d2d81c50d598a8499e4ef3aa7ac092cf6e71d273b3fd7bcf995e62', 'afterSha256': 'e169832b1fe61f03f1955bad4e79a3e856942c527bbdddf456d2a39446460cb5', 'patch': 'docs/runtime-environment/display-direct-source-successors/js_ported_display.js.patch', 'patchSha256': 'be2079446a71f2f4ee3339ba05b393ca9303be838b64bf1e2cc9977d65b15b20'}, 'js/nethack/bindings/display-direct.js': {'existed': False, 'beforeSha256': 'e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855', 'afterSha256': 'edb7569ebaf70dd873c956cfb5db1a1748700473027fecbc5cfb8256c91a61b7', 'patch': 'docs/runtime-environment/display-direct-source-successors/js_nethack_bindings_display-direct.js.patch', 'patchSha256': '5884f05378ebbac269a5c1a189ec2f7ced1510440147c173192b187500cd913c'}, 'js/nethack/display-direct-fields.json': {'existed': False, 'beforeSha256': 'e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855', 'afterSha256': '5a51a67f83c04a56f371e4c56b7f2522dc98013228d42003ef5a6a6d00bb6d28', 'patch': 'docs/runtime-environment/display-direct-source-successors/js_nethack_display-direct-fields.json.patch', 'patchSha256': 'b7478bbbe89442f073daf22768da2ef2d7f213c8d4209b7304a96025149667cd'}}
sha=lambda b:hashlib.sha256(b).hexdigest()
def validate_cohort(root):
 root=Path(root);images={}
 for file,row in FILES.items():
  before=subprocess.check_output(['git','show',BASE_COMMIT+':'+file],cwd=root) if row['existed'] else b''
  after=(root/file).read_bytes();patch=(root/row['patch']).read_bytes()
  canonical=''.join(difflib.unified_diff(before.decode().splitlines(True),after.decode().splitlines(True),fromfile='a/'+file,tofile='b/'+file)).encode()
  assert sha(before)==row['beforeSha256'],'Wrong DISPLAY predecessor: '+file
  assert sha(after)==row['afterSha256'],'Unknown DISPLAY source change: '+file
  assert sha(patch)==row['patchSha256'] and patch==canonical,'Wrong DISPLAY source patch: '+file
  images[file]=before
 return images
def qualified_before(root,file):
 assert file in FILES,'Undeclared DISPLAY source projection'
 return validate_cohort(root)[file]
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--file');a=p.parse_args();root=Path(__file__).resolve().parents[1]
 if a.file:
  import sys;sys.stdout.buffer.write(qualified_before(root,a.file))
 else:validate_cohort(root);print('PASS exact DISPLAY specialization predecessor; not game acceptance')
