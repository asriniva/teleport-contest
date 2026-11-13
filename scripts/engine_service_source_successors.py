"""Exact historical inverse for four corrected production service bindings.

This only qualifies historical source provenance. The old failing paths and
their corrected implementations are intentionally not behaviorally equivalent.
"""
from pathlib import Path
import hashlib,json,sys
ROOT=Path(__file__).resolve().parents[1]
ALLOWED={'js/nethack/object-state.js','js/nethack/shknam.js','js/nethack/teleport.js','js/nethack/bindings/mon.js'}
BASE='238be60d445dfdc9f1d47942bc0434b9ea3e6f39'
def qualified_before(root,file):
 data=json.loads((root/'docs/engine-service-source-successors.json').read_text())
 assert data['version']==1 and data['baseCommit']==BASE,'Unreviewed service-fix baseline'
 assert set(data['files'])==ALLOWED,'Unexpected service-fix successor membership'
 assert file in ALLOWED,'Unqualified service-fix source'
 row=data['files'][file];source=(root/file).read_bytes();sha=lambda value:hashlib.sha256(value).hexdigest()
 assert sha(source)==row['afterSha256'],'Unreviewed service-fix source: '+file
 assert len(row['replacements'])==1,'Unexpected service-fix edit count'
 text=source.decode()
 for edit in reversed(row['replacements']):
  assert text.count(edit['after'])==1,'Ambiguous service-fix inverse'
  text=text.replace(edit['after'],edit['before'])
 before=text.encode();assert sha(before)==row['beforeSha256'],'Service-fix inverse mismatch'
 return before
if __name__=='__main__':
 if len(sys.argv)==3 and sys.argv[1]=='--file':sys.stdout.buffer.write(qualified_before(ROOT,sys.argv[2]))
 else:
  for file in sorted(ALLOWED):qualified_before(ROOT,file)
  print('PASS4 exact service-binding source inverses; historical expected bytes unchanged')
