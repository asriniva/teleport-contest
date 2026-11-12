#!/usr/bin/env python3
"""Bind existing MON fields/global transport without policy changes."""
import json,re,hashlib,os
from pathlib import Path
root=Path(__file__).resolve().parents[1];runtime=root/'js/ported/mon-runtime.js';support=root/'nethack-c/wasm/tu-mon-support.inc';text=runtime.read_text();schema=json.JSONDecoder().raw_decode(text.split('const schema=',1)[1])[0];bits=json.JSONDecoder().raw_decode(text.split('bits=',1)[1])[0];body=support.read_text().split('void*teleport_mon_global(int i){switch(i){',1)[1].split('default:',1)[0];rows=[(int(i),n)for i,n in re.findall(r'case (\d+):return\s*(?:\(void\*\))?\s*&?(\w+);',body)]
if [i for i,_ in rows]!=list(range(35)):raise ValueError('Review MON global map')
argumentKinds=json.JSONDecoder().raw_decode(text.split('const env=entry.env,types=',1)[1])[0]
assert len(argumentKinds)==len(re.findall(r'^export function ',(root/'js/ported/mon.js').read_text(),re.M)), 'Review MON entry conversion coverage'
assert {k for kinds in argumentKinds.values() for k in kinds}=={'','callback','raw','mon','pm','obj','mfp','intp','monp'}
ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();align=ref/'.cache/wasm64-build/tree/include/align.h'
assert re.search(r'^#define ALIGNLIM \(10L \+ \(svm.moves / 200L\)\)',align.read_text(),re.M), 'Review native alignment macro'
alignmentSites=[line.strip() for line in (root/'js/ported/mon.js').read_text().splitlines() if 'C.ALIGNLIM' in line]
assert len(alignmentSites)==4 and 'C.int(C.ALIGNLIM)' in alignmentSites[0] and '/ (2)' in alignmentSites[0]
assert all('/ ('+str(divisor)+')' in line for divisor,line in zip([4,8,4],alignmentSites[1:])), 'Review MON alignment observations'
paths=[Path(__file__).resolve(),runtime,support,root/'js/ported/mon.js',root/'nethack-c/wasm/compile-defines.json',root/'js/standalone/monster-lifecycle.js'];sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
(root/'js/standalone/mon-abi.json').write_text(json.dumps({'argumentKinds':argumentKinds,'numericMacros':{'ALIGNLIM':{'definition':'10L + (svm.moves / 200L)','projectionModulus':'34359738368','sourceUses':alignmentSites,'scope':'Signed remainder preserves exactly the four guarded int/cast/division observations for all native signedlong move values; not a general long-valued macro representation.'}},'referenceHeaderSha256':{str(align.relative_to(ref)):hashlib.sha256(align.read_bytes()).hexdigest()},'schema':schema,'bits':bits,'globals':[n for _,n in rows],'sourceSha256':{str(p.relative_to(root)):sha(p)for p in paths}},indent=2)+'\n');print('Bound MON schema and globals.')
