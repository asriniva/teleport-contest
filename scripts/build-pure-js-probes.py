"""Build JavaScript-only subsystem fixtures; never execute a recorder session."""
from pathlib import Path
import subprocess,json,sys,concurrent.futures,hashlib
root=Path(__file__).resolve().parents[1]
ports=json.loads((root/'nethack-c/wasm/tu-ports.json').read_text())
selected=sys.argv[1:]
assert all(any(p['name']==n for p in ports)for n in selected),'Unknown subsystem'
names=[p['name']for p in ports if (not selected or p['name']in selected) and 'pure-js-fixtures/'in(root/f'scripts/test-tu-{p["name"]}.mjs').read_text()]
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
builder_hash=sha(root/'scripts/pure-js-fixtures/build.py')
def build(name):
 out=root/'.cache/pure-js-fixtures'/name;out.mkdir(parents=True,exist_ok=True)
 manifest=out/'manifest.json'
 if manifest.exists():
  try:
   record=json.loads(manifest.read_text())
   if record['builderSha256']==builder_hash and not record['gameTranslationUnitsCompiled']and record['runtimeWasmRequired']is False and all((root/p).is_file()and sha(root/p)==h for p,h in record['sourceSha256'].items())and all((out/p).is_file()and sha(out/p)==h for p,h in record['outputSha256'].items()):return name,0,'CACHED'
  except (OSError,ValueError,KeyError):pass
 with (out/'build.log').open('w')as log:result=subprocess.run([sys.executable,'-B',str(root/'scripts/pure-js-fixtures/build.py'),name],cwd=root,stdout=log,stderr=log)
 return name,result.returncode,'BUILT'
failed=[]
with concurrent.futures.ThreadPoolExecutor(max_workers=3)as pool:
 for name,status,label in pool.map(build,names):
  print(('FAIL 'if status else label+' ')+name,flush=True)
  if status:failed.append(name)
if failed:raise SystemExit('Fixture build failed; inspect .cache/pure-js-fixtures/<name>/build.log: '+', '.join(failed))
