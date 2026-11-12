"""Exact inverse for historical development audits; never a runtime fallback."""
import hashlib,json,subprocess
from pathlib import Path
from services_layout_successors import ALLOWED,historical_after
ROOT=Path(__file__).resolve().parents[1]
def read_before(path):
 path=Path(path);relative=str(path.resolve().relative_to(ROOT));d=json.loads((ROOT/'docs/runtime-environment/services-layout.json').read_text());row=next((r for r in d['files']if relative in [r['file'],r['destination']]),None)
 if row:
  if hashlib.sha256((ROOT/row['destination']).read_bytes()).hexdigest()!=row['afterSha256']:
   assert row['destination']in ALLOWED,'Relocated input changed '+relative
   historical_after(ROOT,row['destination'],row['afterSha256'])
  b=subprocess.check_output(['git','show',d['baselineCommit']+':'+row['file']],cwd=ROOT);assert hashlib.sha256(b).hexdigest()==row['beforeSha256'];return b
 return historical_after(ROOT,relative)if relative in ALLOWED else path.read_bytes()
def text_before(path):return read_before(path).decode()
def write_before(path,b):
 b=b.encode()if isinstance(b,str)else b
 # Historical generators may reproduce exactly the reviewed baseline, never
 # overwrite relocated sources or live metadata with the obsolete layout.
 assert read_before(path)==b,'Historical output changed; review relocation first: '+str(path)
