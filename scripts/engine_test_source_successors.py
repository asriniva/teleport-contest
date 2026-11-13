"""Finite inverse for test-only post-consolidation source corrections/exports."""
from pathlib import Path
import hashlib,json,sys
ROOT=Path(__file__).resolve().parents[1]
ALLOWED={'scripts/test-standalone-game-assets.mjs','scripts/test-standalone-mon-assert.mjs','scripts/test-tu-display.mjs','scripts/test-tu-shk.mjs'}
def qualified_before(root,file):
 data=json.loads((root/'docs/engine-test-source-successors.json').read_text())['files']
 assert set(data)==ALLOWED,'Unexpected engine-test successor membership'
 row=data[file];source=(root/file).read_bytes();sha=lambda value:hashlib.sha256(value).hexdigest()
 assert sha(source)==row['afterSha256'],'Unreviewed engine-test source: '+file
 text=source.decode()
 for edit in reversed(row['replacements']):
  assert text.count(edit['after'])==1,'Ambiguous engine-test inverse'
  text=text.replace(edit['after'],edit['before'])
 before=text.encode();assert sha(before)==row['beforeSha256'],'Engine-test inverse mismatch'
 return before
if __name__=='__main__':
 if len(sys.argv)==3 and sys.argv[1]=='--file':
  assert sys.argv[2] in ALLOWED;sys.stdout.buffer.write(qualified_before(ROOT,sys.argv[2]))
 else:
  for file in sorted(ALLOWED):qualified_before(ROOT,file)
  print('PASS4 exact test-only source inverses; historical expected bytes unchanged')
