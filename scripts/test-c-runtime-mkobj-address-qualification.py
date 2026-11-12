#!/usr/bin/env python3
"""The feature qualification rejects unrelated bytes, even with forged new hashes."""
import copy,difflib,hashlib,importlib.util,json,shutil,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];spec=importlib.util.spec_from_file_location('qualifier',root/'scripts/check-c-runtime-mkobj-address.py');q=importlib.util.module_from_spec(spec);spec.loader.exec_module(q);baseline='c0740becc16e413e0eab9bc55747381841faf80b';original=lambda p:subprocess.check_output(['git','show',baseline+':'+p],cwd=root);sha=lambda b:hashlib.sha256(b).hexdigest();p='js/nethack/address-ports.js';declaration='docs/runtime-environment/c-runtime-mkobj-address-extension.json';proof='docs/runtime-environment/mkobj-address-evidence.json';paths=[p,declaration,proof,'docs/runtime-environment/c-runtime-mkobj-address-extension.patch','scripts/test-standalone-mkroom-mkobj-carriers.mjs','scripts/fixtures/standalone-mkroom-mkobj-carriers.json'];checks=0
with tempfile.TemporaryDirectory(prefix='mkobj-address-qualification-')as d:
 scratch=Path(d)
 for path in paths:(scratch/path).parent.mkdir(parents=True,exist_ok=True);shutil.copyfile(root/path,scratch/path)
 q.verify(scratch,baseline,original);checks+=1
 good=(scratch/p).read_bytes();decl=json.loads((scratch/declaration).read_text())
 for modified in [good+b'// unrelated change\n',good.replace(b"if(name==='mkobj')",b"if(name==='mkobj'||name==='mkroom')",1),good.replace(b'environment.address(value)',b'value.address',1)]:
  (scratch/p).write_bytes(modified);forged=copy.deepcopy(decl);forged['afterSha256']=sha(modified);patch=''.join(difflib.unified_diff(original(p).decode().splitlines(keepends=True),modified.decode().splitlines(keepends=True),fromfile='a/'+p,tofile='b/'+p)).encode();(scratch/forged['patch']).write_bytes(patch);forged['patchSha256']=sha(patch);(scratch/declaration).write_text(json.dumps(forged))
  try:q.verify(scratch,baseline,original)
  except AssertionError:checks+=1
  else:raise AssertionError('Accepted unrelated foundation mutation')
assert (root/p).read_bytes()==good
print('PASS exact MKOBJ address qualification',checks,'positive/adversarial cases; live foundation untouched')
