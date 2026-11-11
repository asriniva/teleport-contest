#!/usr/bin/env python3
"""Bind the unchanged policy/frozen inputs to a committed main checkpoint."""
import argparse,hashlib,json,subprocess
from pathlib import Path
parser=argparse.ArgumentParser()
parser.add_argument('--commit',required=True)
args=parser.parse_args()
root=Path(__file__).resolve().parents[1]
def git(*args):return subprocess.check_output(['git',*args],cwd=root)
commit=git('rev-parse',args.commit).decode().strip()
registry=json.loads(git('show',commit+':nethack-c/wasm/tu-ports.json'))
files=sorted({p['javascript'] for p in registry}|{'js/'+n+'.js' for n in ['isaac64','terminal','storage']})
document={'mainCommit':commit,'policyCount':len(registry),
          'sha256':{file:hashlib.sha256(git('show',commit+':'+file)).hexdigest() for file in files},
          'scope':'Committed main policies and frozen infrastructure only. Uncommitted main work is not imported.'}
(root/'docs/runtime-environment/scope-baseline.json').write_text(json.dumps(document,indent=2)+'\n')
print(f'Bound {len(registry)} unchanged policies to main commit {commit}')
