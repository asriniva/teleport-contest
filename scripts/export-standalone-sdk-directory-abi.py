#!/usr/bin/env python3
"""Export actual SDK directory record layouts from the compiled native observer."""
import argparse,hashlib,json,subprocess
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--oracle',type=Path,default=Path('.cache/standalone-sdk-directory-v1'));p.add_argument('--check',action='store_true');a=p.parse_args();root=Path(__file__).resolve().parents[1];oracle=a.oracle.resolve();receipt=json.loads((oracle/'receipt.json').read_text());sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
for name,h in receipt['sourceSha256'].items():assert sha(Path(name))==h,name
for name,h in receipt['artifactSha256'].items():assert sha(oracle/name)==h,name
node=root/'.cache/emsdk/node/24.19.0_64bit/bin/node';code='import f from '+json.dumps((oracle/'reference.mjs').as_uri())+';const c=await f();console.log(JSON.stringify(Array.from({length:13},(_,i)=>Number(c._sdk_dir_layout(i)))));';values=json.loads(subprocess.check_output([str(node),'--input-type=module','-e',code],text=True));names=['size','tell','fd','buf_pos','buf_end','buf','capacity','entrySize','ino','off','reclen','type','name'];data={'layout':dict(zip(names,values)),'profile':receipt['profile'],'sourceSha256':receipt['sourceSha256'],'oracleReceiptSha256':sha(oracle/'receipt.json')};text=json.dumps(data,indent=2)+'\n';target=root/'js/standalone/sdk-directory-abi.json'
if a.check:assert target.read_text()==text,'Regenerate SDK directory ABI'
else:target.write_text(text)
print('SDK directory ABI verified' if a.check else target)
