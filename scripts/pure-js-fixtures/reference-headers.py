"""Materialize exact historical ABI inputs without changing their recorded pins."""
from pathlib import Path
import hashlib,json,shutil
root=Path(__file__).resolve().parents[2]
out=root/'.cache/pure-js-fixtures/reference-headers'
pins={}
for source in (root/'js/nethack').glob('*.json'):
 data=json.loads(source.read_text())
 if not isinstance(data,dict):continue
 for key in (['headerSha256']if source.name=='records.json'else[])+['referenceHeaderSha256']:
  for file,value in data.get(key,{}).items():
   assert file not in pins or pins[file]==value,('Conflicting reference pins',file)
   pins[file]=value
for file,expected in pins.items():
 assert not Path(file).is_absolute()and'..'not in Path(file).parts
 candidates=[root/file,root/'.cache/tu137-shadow-integration/root'/file]
 source=next((p for p in candidates if p.is_file()and hashlib.sha256(p.read_bytes()).hexdigest()==expected),None)
 assert source is not None,('No exact recorded reference bytes',file)
 target=out/file;target.parent.mkdir(parents=True,exist_ok=True);shutil.copyfile(source,target)
 assert hashlib.sha256(target.read_bytes()).hexdigest()==expected
parser='.cache/emsdk/upstream/emscripten/node_modules/acorn/dist/acorn.mjs'
target=out/parser;target.parent.mkdir(parents=True,exist_ok=True)
if target.is_symlink()or target.exists():target.unlink()
target.symlink_to(root/parser)
print(str(out))
print('Verified '+str(len(pins))+' immutable ABI reference inputs; no source/header pins changed.')
