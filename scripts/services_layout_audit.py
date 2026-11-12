"""Exact inverse for historical development audits; never a runtime fallback."""
import hashlib,json,subprocess
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
def read_before(path):
 path=Path(path);relative=str(path.resolve().relative_to(ROOT));d=json.loads((ROOT/'docs/runtime-environment/services-layout.json').read_text());row=next((r for r in d['files']if relative in [r['file'],r['destination']]),None)
 if row:
  assert hashlib.sha256((ROOT/row['destination']).read_bytes()).hexdigest()==row['afterSha256'],'Relocated input changed '+relative
  b=subprocess.check_output(['git','show',d['baselineCommit']+':'+row['file']],cwd=ROOT);assert hashlib.sha256(b).hexdigest()==row['beforeSha256'];return b
 return path.read_bytes()
def text_before(path):return read_before(path).decode()
def write_before(path,b):
 b=b.encode()if isinstance(b,str)else b
 # Historical generators may reproduce exactly the reviewed baseline, never
 # overwrite relocated sources or live metadata with the obsolete layout.
 assert read_before(path)==b,'Historical output changed; review relocation first: '+str(path)
