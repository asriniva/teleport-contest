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
  if row['destination']=='js/nethack/game-windows.js':
   from sounds_source_successors import qualified_before as sounds_before
   actual=sounds_before(ROOT,row['destination'])
  else:actual=window_headers_before(ROOT,row['destination'])if row['destination']in WINDOW_HEADERS else monmove_before(ROOT,row['destination'])if row['destination']in MONMOVE else qualified_before(ROOT,row['destination'])if row['destination']in POST_DEFAULT else(ROOT/row['destination']).read_bytes()
  assert actual is not None,'Historically absent relocated source '+relative
  if hashlib.sha256(actual).hexdigest()!=row['afterSha256']:
   node=ROOT/'.cache/emsdk/node/24.19.0_64bit/bin/node'
   program="import {migrationFiles,qualifiedHistorical} from './scripts/pure-js-fixtures/qualification.mjs';const [p,h]=process.argv.slice(1);if(migrationFiles.has(p))qualifiedHistorical(p,h);else process.exit(2);"
   result=subprocess.run([str(node),'--input-type=module','-e',program,row['destination'],row['afterSha256']],cwd=ROOT,capture_output=True)
   if result.returncode==2:
    assert row['destination']in ALLOWED,'Relocated input changed '+relative
    historical_after(ROOT,row['destination'],row['afterSha256'])
   else:assert result.returncode==0,result.stderr.decode()
  b=subprocess.check_output(['git','show',d['baselineCommit']+':'+row['file']],cwd=ROOT);assert hashlib.sha256(b).hexdigest()==row['beforeSha256'];return b
 if relative in WINDOW_HEADERS:return window_headers_before(ROOT,relative)
 if relative in MONMOVE:return monmove_before(ROOT,relative)
 if relative in POST_DEFAULT:
  old=qualified_before(ROOT,relative)
  if old is None:raise FileNotFoundError('Historically absent post-default source: '+relative)
  return old
 if relative in ALLOWED:return historical_after(ROOT,relative)
 migration=ROOT/'docs/runtime-environment/pure-js-source-changes.json'
 if migration.exists()and relative in json.loads(migration.read_bytes())['files']:
  node=ROOT/'.cache/emsdk/node/24.19.0_64bit/bin/node'
  program="import {qualifiedHistorical} from './scripts/pure-js-fixtures/qualification.mjs';process.stdout.write(qualifiedHistorical(process.argv[1]));"
  return subprocess.check_output([str(node),'--input-type=module','-e',program,relative],cwd=ROOT)
 return path.read_bytes()
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
