#!/usr/bin/env python3
"""Bind native address-adapter function-address tables and C prototypes."""
import hashlib,json
from pathlib import Path
root=Path(__file__).resolve().parents[1];metadata=json.loads((root/'js/standalone/address-ports.json').read_text());ports={};paths=[Path(__file__).resolve(),root/'js/standalone/address-ports.json',root/'js/standalone/public-functions.json']
for name,row in metadata['ports'].items():
 source=root/('nethack-c/wasm/tu-fragments/'+name+'-schema.json');fragment=json.loads(source.read_text());addresses=row['schema'].get('functionAddresses',[])
 if not addresses:continue
 if addresses!=fragment.get('functionAddresses'):raise ValueError('Changed native function-address map '+name)
 prototypes={key:fragment['functionTypes'][key]for key in addresses if key in fragment.get('functionTypes',{})}
 public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions']
 if any(key not in prototypes and key not in public and key!='rn2_on_display_rng'for key in addresses):raise ValueError('Missing native callback type '+name)
 ports[name]={'functionAddresses':addresses,'functionTypes':prototypes};paths.extend([source,root/('js/ported/'+name+'-runtime.js'),root/('nethack-c/wasm/tu-libraries/'+name+'.js')])
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();(root/'js/standalone/callback-address-abi.json').write_text(json.dumps({'ports':ports,'sourceSha256':{str(p.relative_to(root)):sha(p)for p in paths}},indent=2)+'\n');print('Bound native callback-address prototypes for',len(ports),'existing address adapters.')
