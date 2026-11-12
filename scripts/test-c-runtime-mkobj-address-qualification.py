#!/usr/bin/env python3
import sys as _layout_sys
from pathlib import Path as _LayoutPath
_layout_sys.path.insert(0,str(_LayoutPath(__file__).resolve().parent))
from nethack_layout import historical_cli as _prior_layout_cli
if __name__=='__main__':_prior_layout_cli(__file__)
"""The feature qualification rejects unrelated bytes, even with forged new hashes."""
import copy,difflib,hashlib,importlib.util,json,shutil,subprocess,tempfile
from pathlib import Path
from services_layout_audit import read_before
root=Path(__file__).resolve().parents[1];spec=importlib.util.spec_from_file_location('qualifier',root/'scripts/check-c-runtime-mkobj-address.py');q=importlib.util.module_from_spec(spec);spec.loader.exec_module(q);baseline='c0740becc16e413e0eab9bc55747381841faf80b';original=lambda p:subprocess.check_output(['git','show',baseline+':'+p],cwd=root);sha=lambda b:hashlib.sha256(b).hexdigest();p='js/nethack/address-ports.js';declaration='docs/runtime-environment/c-runtime-mkobj-address-extension.json';proof='docs/runtime-environment/mkobj-address-evidence.json';paths=[p,declaration,proof,'docs/runtime-environment/c-runtime-mkobj-address-extension.patch','scripts/test-standalone-mkroom-mkobj-carriers.mjs','scripts/fixtures/standalone-mkroom-mkobj-carriers.json'];checks=0
with tempfile.TemporaryDirectory(prefix='mkobj-address-qualification-')as d:
 scratch=Path(d)
 for path in paths:(scratch/path).parent.mkdir(parents=True,exist_ok=True);(scratch/path).write_bytes(read_before(root/path))
 q.verify(scratch,baseline,original);checks+=1
 good=(scratch/p).read_bytes();decl=json.loads((scratch/declaration).read_text())
 for modified in [good+b'// unrelated change\n',good.replace(b"if(name==='mkobj')",b"if(name==='mkobj'||name==='mkroom')",1),good.replace(b'environment.address(value)',b'value.address',1)]:
  (scratch/p).write_bytes(modified);forged=copy.deepcopy(decl);forged['afterSha256']=sha(modified);patch=''.join(difflib.unified_diff(original(p).decode().splitlines(keepends=True),modified.decode().splitlines(keepends=True),fromfile='a/'+p,tofile='b/'+p)).encode();(scratch/forged['patch']).write_bytes(patch);forged['patchSha256']=sha(patch);(scratch/declaration).write_text(json.dumps(forged))
  try:q.verify(scratch,baseline,original)
  except AssertionError:checks+=1
  else:raise AssertionError('Accepted unrelated foundation mutation')
assert read_before(root/p)==good
print('PASS exact MKOBJ address qualification',checks,'positive/adversarial cases; live foundation untouched')
