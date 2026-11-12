"""Exact inverse for historical development audits; never a runtime fallback."""
import hashlib,json,subprocess
from pathlib import Path
from services_layout_successors import ALLOWED,historical_after
from post_default_successors import ALLOWED as POST_DEFAULT,qualified_before,refuse_write
from monmove_source_successors import ALLOWED as MONMOVE,qualified_before as monmove_before,refuse_write as monmove_refuse_write
from window_headers_source_successors import ALLOWED as WINDOW_HEADERS,qualified_before as window_headers_before,refuse_write as window_headers_refuse_write
ROOT=Path(__file__).resolve().parents[1]
def read_before(path):
 path=Path(path);relative=str(path.resolve().relative_to(ROOT));d=json.loads((ROOT/'docs/runtime-environment/services-layout.json').read_text());row=next((r for r in d['files']if relative in [r['file'],r['destination']]),None)
 if row:
  actual=window_headers_before(ROOT,row['destination'])if row['destination']in WINDOW_HEADERS else monmove_before(ROOT,row['destination'])if row['destination']in MONMOVE else qualified_before(ROOT,row['destination'])if row['destination']in POST_DEFAULT else(ROOT/row['destination']).read_bytes()
  assert actual is not None,'Historically absent relocated source '+relative
  if hashlib.sha256(actual).hexdigest()!=row['afterSha256']:
   assert row['destination']in ALLOWED,'Relocated input changed '+relative
   historical_after(ROOT,row['destination'],row['afterSha256'])
  b=subprocess.check_output(['git','show',d['baselineCommit']+':'+row['file']],cwd=ROOT);assert hashlib.sha256(b).hexdigest()==row['beforeSha256'];return b
 if relative in WINDOW_HEADERS:return window_headers_before(ROOT,relative)
 if relative in MONMOVE:return monmove_before(ROOT,relative)
 if relative in POST_DEFAULT:
  old=qualified_before(ROOT,relative)
  if old is None:raise FileNotFoundError('Historically absent post-default source: '+relative)
  return old
 return historical_after(ROOT,relative)if relative in ALLOWED else path.read_bytes()
def text_before(path):return read_before(path).decode()
def write_before(path,b):
 b=b.encode()if isinstance(b,str)else b
 # Historical generators may reproduce exactly the reviewed baseline, never
 # overwrite relocated sources or live metadata with the obsolete layout.
 assert read_before(path)==b,'Historical output changed; review relocation first: '+str(path)
 relative=str(Path(path).resolve().relative_to(ROOT))
 if relative in WINDOW_HEADERS:window_headers_refuse_write(ROOT,relative,b)
 if relative in MONMOVE:monmove_refuse_write(ROOT,relative,b)
 if relative in POST_DEFAULT:refuse_write(ROOT,relative,b)
