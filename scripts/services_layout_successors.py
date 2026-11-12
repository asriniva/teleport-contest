"""Finite, exact post-cleanup source qualification; development audits only.

This does not refresh the cleanup recipe or validate runtime behavior itself.
A separate current-source gate and a hash-bound native proof remain required.
"""
import argparse,difflib,hashlib,json,subprocess
from pathlib import Path
CLEANUP_COMMIT='390281578eb48723c2e6f564b2e2bddd3f15e884'
DECLARATION='docs/runtime-environment/services-layout-successors.json'
ALLOWED=frozenset(['js/nethack/level-startup.js','scripts/export-standalone-pager-target-abi.py','js/nethack/pager-target-header-functions.js','js/nethack/pager-target-abi.json','js/nethack/dbridge-abi.json','js/nethack/region-services-abi.json'])
AUDIT_TOOLS=frozenset(['scripts/relocate-runtime-layout.py','scripts/services-layout-audit.mjs','scripts/services_layout_audit.py'])
def sha(data):return hashlib.sha256(data).hexdigest()
def _git_bytes(root,path):return subprocess.check_output(['git','show',CLEANUP_COMMIT+':'+path],cwd=root)
def canonical_patch(path,before,after):
 return ''.join(difflib.unified_diff(before.decode('utf8').splitlines(keepends=True),after.decode('utf8').splitlines(keepends=True),fromfile='a/'+path,tofile='b/'+path)).encode('utf8')
def _tracked_document(root,value):
 assert isinstance(value,str) and value.startswith('docs/runtime-environment/'),'Qualification artifacts must be repository documentation'
 p=Path(value);assert not p.is_absolute() and '..'not in p.parts,'Noncanonical qualification path'
 assert p.as_posix()==value,'Noncanonical qualification artifact path'
 resolved=(root/p).resolve();assert resolved.is_relative_to((root/'docs/runtime-environment').resolve()),'Qualification artifact escapes documentation'
 return resolved

def historical_after(root,path,expected_after=None):
 """Verify live exact successor and return unchanged post-cleanup bytes."""
 root=Path(root);assert path in ALLOWED,'Unqualified post-layout source path '+path
 before=_git_bytes(root,path)
 if expected_after is not None:assert sha(before)==expected_after,'Cleanup source does not match original after-hash: '+path
 actual=(root/path).read_bytes()
 if actual==before:return before
 d=json.loads((root/DECLARATION).read_text())
 assert d.get('version')==1 and d.get('cleanupCommit')==CLEANUP_COMMIT,'Unreviewed cleanup successor baseline'
 assert isinstance(d.get('files'),dict) and set(d['files'])==ALLOWED,'Only the exact six reviewed source successors are allowed'
 row=d['files'][path];assert row['beforeSha256']==sha(before),'Changed historical successor baseline: '+path
 assert row['afterSha256']==sha(actual),'Unreviewed current source: '+path
 patch=_tracked_document(root,row['patch']).read_bytes()
 assert sha(patch)==row['patchSha256'] and patch==canonical_patch(path,before,actual),'Exact source successor patch differs: '+path
 proof=_tracked_document(root,row['nativeProof']).read_bytes()
 assert sha(proof)==row['nativeProofSha256'],'Native proof hash differs: '+path
 native=json.loads(proof);assert native.get('complete') is True,'Native successor proof is not accepted: '+path
 expected_sources={name:item['afterSha256']for name,item in d['files'].items()}
 assert native.get('qualifiedSourceSha256')==expected_sources,'Native proof does not bind the exact current six-file cohort'
 return before

def validate_cohort(root,layout_after,write=False):
 """Check the finite cohort before any historical relocation can write."""
 before={}
 for path in sorted(ALLOWED):
  before[path]=historical_after(root,path,layout_after.get(path))
  if write and(Path(root)/path).read_bytes()!=before[path]:
   raise AssertionError(('Refusing to overwrite qualified post-cleanup feature',path))
 return before

def verify_historical_output(root,path,reproduced):
 """A historical pass compares reproduced bytes only to pinned cleanup Git."""
 recorded=_git_bytes(Path(root),path)
 assert reproduced==recorded,'Pinned390 cleanup output differs: '+path
 return recorded

def historical_audit_tool(root,path,expected_hash):
 """Reproduce immutable recipe tool/support hashes, not current implementation hashes.

Current audit implementations are independently source-bound and adversarially
checked. They are not added to the six runtime/source qualification paths.
"""
 assert path in AUDIT_TOOLS,'Unexpected historical audit implementation '+path
 before=_git_bytes(Path(root),path);assert sha(before)==expected_hash,'Historical cleanup audit differs: '+path
 return before

if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--file',required=True);p.add_argument('--layout-after');a=p.parse_args()
 root=Path(__file__).resolve().parents[1]
 # stdout is exactly historical file bytes for both JS and Python callers.
 import sys
 sys.stdout.buffer.write(historical_after(root,a.file,a.layout_after))
