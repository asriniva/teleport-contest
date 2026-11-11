#!/usr/bin/env python3
"""Read actual compiled SDK constants and bind the shared scanner sources."""
import argparse,hashlib,json,subprocess
from pathlib import Path
root=Path(__file__).resolve().parents[1];p=argparse.ArgumentParser();p.add_argument('--reference-root',type=Path,default=root.parent/'teleport-contest');p.add_argument('--oracle',type=Path,default=root/'.cache/standalone-scanf-v3');a=p.parse_args();ref=a.reference_root.resolve();oracle=a.oracle.resolve();node=sorted((ref/'.cache/emsdk/node').glob('*/bin/node'))[-1]
program='import factory from '+json.dumps((oracle/'reference.mjs').as_uri())+';const m=await factory();process.stdout.write(JSON.stringify(Array.from({length:6},(_,i)=>Number(m._scanf_constant(i)))));'
values=json.loads(subprocess.check_output([str(node),'--input-type=module','-e',program],text=True));assert values==[28,68,8,8,-1,128],values
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();paths=['scripts/export-standalone-scanf-abi.py','js/standalone/scanf.js','js/standalone/libc.js','js/standalone/stdio.js']
data={'profile':'Pinned SDK musl, memory64 narrow scanf','EINVAL':values[0],'ERANGE':values[1],'longBytes':values[2],'pointerBytes':values[3],'EOF':values[4],'sourceSha256':{p:sha(root/p)for p in paths},'referenceReceiptSha256':sha(oracle/'receipt.json'),'compilerSha256':sha(ref/'.cache/emsdk/upstream/bin/clang')}
(root/'js/standalone/scanf-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound actual compiled SDK scanf constants and shared scanner/stdio sources.')
