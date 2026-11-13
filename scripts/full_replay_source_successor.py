"""Exact full-replay transport inverse for historical audits, NOT acceptance.

The current game and recording tests execute production sources. This development
projection checks all three complete current files and patches before returning the
pinned main predecessor. It cannot qualify an unrelated source modification.
"""
import argparse,difflib,hashlib,subprocess
from pathlib import Path
BASE_COMMIT='25ce0121f6f011b59ec201652d2eadae320d0baf'
FILES={'js/c-runtime/adapter-factories.js': {'beforeSha256': 'a12022a1380216d383393dac72dd6c945089185803026d722bc1e529ab3ed1e4', 'afterSha256': 'b1d2880f501c399a3421b6cbbdfd548d7a6fbbdcd08b090a385f84ea68252b1b', 'patch': 'docs/runtime-environment/full-replay-source-successors/adapter-factories.js.patch', 'patchSha256': 'a68984d510b7f49bfdccecd9a897c785f7a501defa6b52e6cc2ac9473bce1bf8'}, 'js/c-runtime/records.js': {'beforeSha256': '3fa3684e7ac4a35a644aa9521b0427438c3e8f01974c181744608452d4fd77fa', 'afterSha256': '518a6f5d2ddf7affaf3b02866a6a783916cb1c94ac1521bccc2e2990f2a5dd31', 'patch': 'docs/runtime-environment/full-replay-source-successors/records.js.patch', 'patchSha256': '7b7c50e7f595dc56492f70d2b54dc84860ab1024e5667c3cd06a74a8b4526a57'}, 'js/nethack/bindings/termcap.js': {'beforeSha256': '88f4d9523be6241ca538a0ff0afe51702f93955591fa3c49119851088766c764', 'afterSha256': '7b5292e9b7acf326647a7740c5f727164eb92ef89ac92e5060db4625a3cb4ff0', 'patch': 'docs/runtime-environment/full-replay-source-successors/termcap.js.patch', 'patchSha256': 'fca698061c6a03b689c0fd383a4c5c3da713d29d1f62401558a5c2741f3e896d'}}
sha=lambda b:hashlib.sha256(b).hexdigest()
def validate_cohort(root):
 root=Path(root);result={}
 for file,row in FILES.items():
  before=subprocess.check_output(['git','show',BASE_COMMIT+':'+file],cwd=root)
  after=(root/file).read_bytes();patch=(root/row['patch']).read_bytes()
  expected=''.join(difflib.unified_diff(before.decode().splitlines(True),after.decode().splitlines(True),fromfile='a/'+file,tofile='b/'+file)).encode()
  assert sha(before)==row['beforeSha256'],'Wrong full-replay predecessor: '+file
  assert sha(after)==row['afterSha256'],'Unknown full-replay source change: '+file
  assert sha(patch)==row['patchSha256'] and patch==expected,'Wrong full-replay patch: '+file
  result[file]=before
 return result
def qualified_before(root,file):
 assert file in FILES,'Only the exact three full-replay transport files are qualified'
 return validate_cohort(root)[file]
def current_before(root,file):
 return qualified_before(root,file) if file in FILES else (Path(root)/file).read_bytes()
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--file');a=p.parse_args();root=Path(__file__).resolve().parents[1]
 if a.file:
  import sys;sys.stdout.buffer.write(qualified_before(root,a.file))
 else:validate_cohort(root);print('PASS exact full-replay source inverse; not C or recording acceptance')
