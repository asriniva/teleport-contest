"""Exact NOMUX typed-view predecessor for historical audits, NOT acceptance.

Production and parity tests always execute the current code. The inverse checks
both runtime files and their complete canonical patches, and measured shared heap views.
"""
import argparse,difflib,hashlib,subprocess
from pathlib import Path
BASE_COMMIT='f58b27e92880b3ffd61d992a1a1d14994f2cec4a'
FILES={'js/nethack/bindings/termcap.js': {'existed': True, 'beforeSha256': '7b5292e9b7acf326647a7740c5f727164eb92ef89ac92e5060db4625a3cb4ff0', 'afterSha256': 'cc7817560bb908d90f9af5e6792428a7a0a89ddac2229f458b157f6da942e151', 'patch': 'docs/runtime-environment/shadow-screen-source-successors/js_nethack_bindings_termcap.js.patch', 'patchSha256': '110761a7dad7ca9bedc4227d3a944ba6fae60e20bb71aa94f10f2ca3a5f5d715'}, 'js/ported/termcap.js': {'existed': True, 'beforeSha256': '9a4ba8198229378df99b5659356a65556fa3859a0a34ea7b6f211c880eff1da0', 'afterSha256': '629ef0890a81cf0ebfcd04599ef84962ed27edfac9d9f18ec1b99667ded96778', 'patch': 'docs/runtime-environment/shadow-screen-source-successors/js_ported_termcap.js.patch', 'patchSha256': '83da9dc81c49d9c2a77b6f1f580bff4ec1ed33140ed3efc51953ebe462841d74'}}
sha=lambda b:hashlib.sha256(b).hexdigest()
def validate_cohort(root):
 root=Path(root);images={}
 for file,row in FILES.items():
  before=subprocess.check_output(['git','show',BASE_COMMIT+':'+file],cwd=root) if row['existed'] else b''
  after=(root/file).read_bytes();patch=(root/row['patch']).read_bytes()
  canonical=''.join(difflib.unified_diff(before.decode().splitlines(True),after.decode().splitlines(True),fromfile='a/'+file,tofile='b/'+file)).encode()
  assert sha(before)==row['beforeSha256'],'Wrong NOMUX predecessor: '+file
  assert sha(after)==row['afterSha256'],'Unknown NOMUX source change: '+file
  assert sha(patch)==row['patchSha256'] and patch==canonical,'Wrong NOMUX source patch: '+file
  images[file]=before
 return images
def qualified_before(root,file):
 assert file in FILES,'Undeclared NOMUX source projection'
 return validate_cohort(root)[file]
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--file');a=p.parse_args();root=Path(__file__).resolve().parents[1]
 if a.file:
  import sys;sys.stdout.buffer.write(qualified_before(root,a.file))
 else:validate_cohort(root);print('PASS exact NOMUX typed-view predecessor; not game acceptance')
