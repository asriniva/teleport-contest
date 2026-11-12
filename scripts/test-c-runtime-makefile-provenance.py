#!/usr/bin/env python3
"""Exercise reviewed dependency-only registry aliases and reject unknown bytes."""
from pathlib import Path
import hashlib,importlib.util,json,os,tempfile
root=Path(__file__).resolve().parents[1]
reference=Path(os.environ['STANDALONE_REFERENCE_ROOT'])
spec=importlib.util.spec_from_file_location('reviewed_makefile',root/'nethack-c/wasm/tu-fragments/unixunix-reviewed-makefile.py');module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
registry=(root/'nethack-c/wasm/tu-ports.json').read_bytes();makefile=(reference/'.cache/wasm64-build/tree/src/Makefile').read_bytes()
with tempfile.TemporaryDirectory(prefix='c-runtime-profile-',dir=root/'.cache/c-runtime-cleanup')as directory:
 target=Path(directory);r=target/'nethack-c/wasm/tu-ports.json';r.parent.mkdir(parents=True);r.write_bytes(registry)
 m=target/'.cache/wasm64-build/tree/src/Makefile';m.parent.mkdir(parents=True);m.write_bytes(makefile)
 restored=module.reviewed_unixunix_makefile(target,module.EXPECTED_OLD)
 assert hashlib.sha256(restored).hexdigest()==module.EXPECTED_OLD
 r.write_bytes(registry+b' ')
 try:module.reviewed_unixunix_makefile(target,module.EXPECTED_OLD)
 except AssertionError:pass
 else:raise AssertionError('Unknown registry bytes accepted')
 r.write_bytes(registry);m.write_bytes(makefile+b' ')
 try:module.reviewed_unixunix_makefile(target,module.EXPECTED_OLD)
 except AssertionError:pass
 else:raise AssertionError('Unknown Makefile bytes accepted')
print('PASS: actual registry/Makefile exact inverse and both unknown-byte negative controls; no CPP or full-build claim')
