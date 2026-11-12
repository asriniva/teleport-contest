"""Exact post-default feature qualification for historical development audits.

This layer restores the pinned pre-feature bytes before the original layout
inverse runs. It is not current-source or complete-game acceptance.
"""
import argparse,difflib,hashlib,json,subprocess
from pathlib import Path

BASE_COMMIT='8e0fc6ade5256f180d443835a1a8d7f4e761ddf2'
DECLARATION='docs/runtime-environment/post-default-source-successors.json'
PROOF='docs/runtime-environment/post-default-native-evidence.json'
ALLOWED=frozenset([
 'js/c-runtime/stdio.js','js/platform/darwin/terminal.js',
 'js/standalone/display-startup.js','js/standalone/environment.js',
 'js/standalone/monster-creation.js','js/standalone/monster-selection.js',
 'js/standalone/program.js','js/standalone/sdk-boundary.js',
 'js/standalone/signals.js','js/standalone/unix-platform.js',
 'js/standalone/unix-terminal.js','js/standalone/version-info.js',
 'js/standalone/makemon-private-abi.json','js/standalone/makemon-public-abi.json',
 'js/standalone/persistence-transport-abi.json','js/standalone/scanf-abi.json',
 'js/standalone/sdk-boundary-abi.json','js/standalone/unix-platform-abi.json',
 'js/standalone/signal-delivery-abi.json',
])
NEW_FILES=frozenset(['js/standalone/signal-delivery-abi.json'])

def sha(data):return hashlib.sha256(data).hexdigest()
def baseline_bytes(root,path):
 names=subprocess.check_output(['git','ls-tree','--full-tree','--name-only',BASE_COMMIT,'--',path],cwd=root,text=True).splitlines()
 assert names in [[],[path]],'Unexpected pinned source membership: '+path
 return subprocess.check_output(['git','show',BASE_COMMIT+':'+path],cwd=root)if names else None
def canonical_patch(path,before,after):
 return ''.join(difflib.unified_diff((before or b'').decode().splitlines(keepends=True),after.decode().splitlines(keepends=True),fromfile='/dev/null'if before is None else'a/'+path,tofile='b/'+path)).encode()
def document(root,path):
 assert isinstance(path,str),'Qualification artifact must have a path'
 p=Path(path)
 assert not p.is_absolute()and'..'not in p.parts and p.as_posix()==path,'Noncanonical qualification artifact'
 assert path.startswith('docs/runtime-environment/'),'Qualification artifact must be repository documentation'
 resolved=(root/p).resolve()
 assert resolved.is_relative_to((root/'docs/runtime-environment').resolve()),'Qualification artifact escapes documentation'
 return resolved

def validate_cohort(root):
 root=Path(root).resolve()
 d=json.loads((root/DECLARATION).read_bytes())
 assert d.get('version')==1 and d.get('baseCommit')==BASE_COMMIT,'Unreviewed post-default baseline'
 assert isinstance(d.get('files'),dict)and set(d['files'])==ALLOWED,'Only the exact post-default cohort is allowed'
 assert d.get('nativeProof')==PROOF,'Unexpected post-default native proof'
 proof_bytes=document(root,d['nativeProof']).read_bytes()
 assert sha(proof_bytes)==d.get('nativeProofSha256'),'Post-default native proof hash differs'
 proof=json.loads(proof_bytes)
 assert proof.get('complete')is True and proof.get('originalNativeCompared')is True,'Current native feature proof is incomplete'
 assert proof.get('baseCommit')==BASE_COMMIT,'Native proof has a different base'
 expected={p:r['afterSha256']for p,r in d['files'].items()}
 assert proof.get('qualifiedSourceSha256')==expected,'Native proof does not bind the exact current cohort'
 raw=proof.get('rawProofs')
 assert isinstance(raw,dict)and raw,'Native feature proof must bind raw comparison receipts'
 for path,digest in raw.items():assert sha(document(root,path).read_bytes())==digest,'Native raw proof hash differs: '+path
 before={}
 for path,row in sorted(d['files'].items()):
  old=baseline_bytes(root,path);before[path]=old
  assert(old is None)==(path in NEW_FILES),'Unexpected historically absent source: '+path
  assert row.get('beforeSha256')==(None if old is None else sha(old)),'Post-default baseline source differs: '+path
  actual=(root/path).read_bytes()
  if (root/"docs/runtime-environment/allocation-cli-source-successors.json").is_file():
   from allocation_cli_source_successors import ALLOWED as ALLOCATION_CLI,qualified_before as allocation_cli_before
   if path in ALLOCATION_CLI:actual=allocation_cli_before(root,path)
  if sha(actual)!=row['afterSha256']:
   # The separately exact-qualified migration can extend a committed feature.
   # Keep this native proof bound to its original bytes, without accepting drift.
   node=root/'.cache/emsdk/node/24.19.0_64bit/bin/node'
   program="import {qualifiedHistorical} from './scripts/pure-js-fixtures/qualification.mjs';qualifiedHistorical(process.argv[1]);"
   subprocess.check_call([str(node),'--input-type=module','-e',program,path],cwd=root)
   actual=subprocess.check_output(['git','show','8b834cd2b94a10bc1a96336de0bd91f90d3adf2b:'+path],cwd=root)
  assert sha(actual)==row['afterSha256'],'Unqualified current post-default source: '+path
  patch_path=row['patch']
  assert patch_path.startswith('docs/runtime-environment/post-default-source-successors/')and patch_path.endswith('.patch'),'Unexpected post-default patch path'
  patch=document(root,patch_path).read_bytes()
  assert sha(patch)==row['patchSha256']and patch==canonical_patch(path,old,actual),'Exact post-default patch differs: '+path
 return before

def qualified_before(root,path):
 assert path in ALLOWED,'Unqualified post-default path: '+path
 return validate_cohort(root)[path]
def refuse_write(root,path,value):
 """Historical generators cannot retire a later feature, including new files."""
 old=qualified_before(root,path)
 assert old is not None,'Historically absent post-default source: '+path
 assert value==old,'Historical post-default output differs: '+path
 assert(Path(root)/path).read_bytes()==value,'Refusing to overwrite qualified post-default feature: '+path

if __name__=='__main__':
 p=argparse.ArgumentParser();g=p.add_mutually_exclusive_group(required=True);g.add_argument('--file');g.add_argument('--check',action='store_true');p.add_argument('--exists',action='store_true');a=p.parse_args()
 if a.check:
  assert not a.exists,'--exists requires --file'
  validate_cohort(Path(__file__).resolve().parents[1]);print('PASS exact post-default native/source qualification; historical projection only, not complete-game acceptance')
  raise SystemExit
 old=qualified_before(Path(__file__).resolve().parents[1],a.file)
 import sys
 if a.exists:sys.stdout.write('0'if old is None else'1')
 else:
  if old is None:raise FileNotFoundError('Historically absent post-default source: '+a.file)
  sys.stdout.buffer.write(old)
