"""Exact full-replay transport inverse for historical audits, NOT acceptance.

The current game and recording tests execute production sources. This development
projection checks all three complete current files and patches before returning the
pinned main predecessor. It cannot qualify an unrelated source modification.
"""
import argparse,difflib,hashlib,subprocess
from pathlib import Path
BASE_COMMIT='3b6db964b55ec253e6f624f524c351d75d5ea6c5'
FILES={'js/c-runtime/adapter-factories.js': {'beforeSha256': '84b32a1e910f43c97ae8cbebc5d0aa4d8e1f50db7b7b094fb94ffda1bb603a93', 'afterSha256': 'cf982699d7dc1a30902aa9543550d6a9c1dd7b8a9af5e537dcd1b78824ed8498', 'patch': 'docs/runtime-environment/full-replay-source-successors/adapter-factories.js.patch', 'patchSha256': 'aa78062463d6ff855ff83b303554d3d65834e7b8a857406b1ad111d48984608c'}, 'js/c-runtime/records.js': {'beforeSha256': 'a3ee9c8b18f283bbc540bc546a68ea7c470c25a3641f74a56336207adbdef328', 'afterSha256': 'aaa628dc6bc3b41d3e69b03d29a25673319bc0b26274d67320dfdd9a60dbea3f', 'patch': 'docs/runtime-environment/full-replay-source-successors/records.js.patch', 'patchSha256': '72fe601aeebeac6cb8a31b9053c99c18fbd39c7ebca7d077fe45de728cf572ac'}, 'js/nethack/bindings/termcap.js': {'beforeSha256': '88f4d9523be6241ca538a0ff0afe51702f93955591fa3c49119851088766c764', 'afterSha256': '7b5292e9b7acf326647a7740c5f727164eb92ef89ac92e5060db4625a3cb4ff0', 'patch': 'docs/runtime-environment/full-replay-source-successors/termcap.js.patch', 'patchSha256': 'fca698061c6a03b689c0fd383a4c5c3da713d29d1f62401558a5c2741f3e896d'}}
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
