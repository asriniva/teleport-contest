"""Exact six-file utility/monster-view inverse for immutable source receipts.
Runtime tests execute current production code; no oracle hashes are rewritten.
"""
from pathlib import Path
import argparse,difflib,hashlib,json,subprocess,sys
RECEIPT='docs/runtime-environment/monster-view-source-successors/receipt.json'
ALLOWED={'js/nethack/monster-creation.js', 'js/ported-utilities/sfctool-runtime.js', 'js/c-runtime/record-views.js', 'js/c-runtime/records.js', 'js/ported-utilities/sfctool-helpers.js', 'js/ported-utilities/tile2bmp/runtime.mjs'}
sha=lambda data:hashlib.sha256(data).hexdigest()
def validate_bytes(before,after,patch,row,file):
 assert sha(before)==row['beforeSha256'],'Wrong immutable predecessor: '+file
 assert sha(after)==row['afterSha256'],'Unreviewed source: '+file
 expected=''.join(difflib.unified_diff(before.decode().splitlines(True),after.decode().splitlines(True),fromfile='a/'+file,tofile='b/'+file)).encode()
 assert patch==expected and sha(patch)==row['patchSha256'],'Wrong exact source patch: '+file
 return before
def validate_cohort(root):
 root=Path(root);receipt=json.loads((root/RECEIPT).read_text());assert receipt['base']=='8b5ecaf' and set(receipt['files'])==ALLOWED
 results={}
 for file,row in receipt['files'].items():
  before=subprocess.check_output(['git','show',receipt['base']+':'+file],cwd=root);after=(root/file).read_bytes()
  results[file]=validate_bytes(before,after,(root/row['patch']).read_bytes(),row,file)
 return results
def qualified_before(root,file):
 assert file in ALLOWED,'Unowned source'
 return validate_cohort(root)[file]
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--file');a=p.parse_args();root=Path(__file__).resolve().parents[1]
 if a.file:sys.stdout.buffer.write(qualified_before(root,a.file))
 else:validate_cohort(root);print('PASS exact six-file utility/monster-view source inverse')
