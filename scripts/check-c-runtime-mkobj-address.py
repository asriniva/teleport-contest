#!/usr/bin/env python3
import sys as _layout_sys
from pathlib import Path as _LayoutPath
_layout_sys.path.insert(0,str(_LayoutPath(__file__).resolve().parent))
from nethack_layout import historical_cli as _prior_layout_cli
if __name__=='__main__':_prior_layout_cli(__file__)
"""Qualify one exact post-foundation MKOBJ native-pointer boundary extension."""
import difflib,hashlib,json,subprocess
from pathlib import Path
from services_layout_audit import ROOT as LAYOUT_ROOT,read_before
def audited_bytes(path):
 return read_before(path)if path.resolve().is_relative_to(LAYOUT_ROOT)else path.read_bytes()

def verify(root,baseline,original):
 sha=lambda b:hashlib.sha256(b).hexdigest()
 p='js/nethack/address-ports.js'
 declaration=json.loads((root/'docs/runtime-environment/c-runtime-mkobj-address-extension.json').read_text())
 assert declaration['baselineCommit']==baseline=='c0740becc16e413e0eab9bc55747381841faf80b'
 assert declaration['file']==p
 anchor="    const bind=key=>(...args)=>{\n"
 addition="        // The native MKOBJ public entries receive addresses, not record carriers.\n        if(name==='mkobj'){const prototype=schema.functionTypes?.[key];if(!prototype)throw new Error('Missing MKOBJ native prototype '+key);const match=prototype.match(/\\((.*)\\)$/);if(!match)throw new Error('Unknown MKOBJ native prototype '+key);const params=match[1].split(',').map(type=>ctypes.canonical(type.trim()));args=args.map((value,i)=>params[i]?.includes('*')?(typeof value==='string'&&/char\\s*\\*/.test(params[i])?services.literal(value):environment.address(value)):value);}\n"
 before=original(p);assert before.count(anchor.encode())==1
 expected=before.replace(anchor.encode(),(anchor+addition).encode(),1)
 current=audited_bytes(root/p);assert current==expected,'Unreviewed post-foundation address adapter change'
 assert sha(before)==declaration['beforeSha256'] and sha(current)==declaration['afterSha256']
 patch=''.join(difflib.unified_diff(before.decode().splitlines(keepends=True),current.decode().splitlines(keepends=True),fromfile='a/'+p,tofile='b/'+p)).encode()
 assert declaration['patch']=='docs/runtime-environment/c-runtime-mkobj-address-extension.patch'
 assert (root/declaration['patch']).read_bytes()==patch and sha(patch)==declaration['patchSha256']
 assert declaration['evidence']=='docs/runtime-environment/mkobj-address-evidence.json'
 proof=(root/declaration['evidence']).read_bytes();assert sha(proof)==declaration['evidenceSha256']
 evidence=json.loads(proof);assert evidence['complete'] is True and evidence['mode']=='paired' and evidence['assemblyProvenanceStable'] is True
 assert evidence['checks']==17 and evidence['hashes']==786 and evidence['fullGameAccepted'] is False
 pins=evidence['productionProvenance'];assert pins['sourceSha256'][p]==sha(current)
 for file in ['scripts/test-standalone-mkroom-mkobj-carriers.mjs','scripts/fixtures/standalone-mkroom-mkobj-carriers.json']:
  assert sha(audited_bytes(root/file))==pins['sourceSha256'][file],'Changed MKOBJ proof input '+file
 assert pins['referenceReceiptSha256']==declaration['originalCReceiptSha256']
 assert len(evidence['cases'])==1 and evidence['cases'][0]['id']=='court-and-deallocation-1'
 assert evidence['cases'][0]['inputBoundaries']==6 and evidence['cases'][0]['frames']==6
 return declaration

if __name__=='__main__':
 root=Path(__file__).resolve().parents[1];baseline='c0740becc16e413e0eab9bc55747381841faf80b'
 verify(root,baseline,lambda p:subprocess.check_output(['git','show',baseline+':'+p],cwd=root))
 print('PASS exact MKOBJ native-pointer extension; original foundation bytes remain reproducible')
