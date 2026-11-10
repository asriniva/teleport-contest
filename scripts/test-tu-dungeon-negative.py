"""Unchanged original C rejects a deliberate private pick_level wrong body."""
from pathlib import Path
import hashlib,json,subprocess
r=Path(__file__).resolve().parents[1];w=r/'.cache/dungeon-first-pass/wrong-code';w.mkdir(exist_ok=True,parents=True)
paths=[r/'nethack-c/upstream/src/dungeon.c',r/'.cache/wasm64-build/tree/src/dungeon.c',r/'.cache/dungeon-first-pass/dungeon-reference.wasm',r/'js/ported/dungeon.js']
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();before={str(p):sha(p)for p in paths}
s=paths[-1].read_text();start=s.index('export function pick_level(');end=s.index('\nexport function ',start+1);block=s[start:end];assert block.count('return i;')==1;wrong=s[:start]+block.replace('return i;','return C.i16(i+1);')+s[end:];assert wrong!=s
(w/'dungeon.js').write_text(wrong);(w/'dungeon-runtime.js').write_text((r/'js/ported/dungeon-runtime.js').read_text());(w/'c-runtime.js').write_text('export{C,withCEnvironment}from'+json.dumps((r/'js/ported/c-runtime.js').as_uri())+';\n')
focus="""import assert from 'node:assert/strict';
import refFactory from REF;
import hybridFactory from HYBRID;
import{callDungeon}from'./dungeon-runtime.js';
const ref=await refFactory(),hybrid=await hybridFactory();hybrid.nethackPorted={dungeon:callDungeon};const result=[];
for(const m of[ref,hybrid]){m._probe_reset();const p=Number(m._probe_pointer(0));m.HEAPU8.fill(0,p,p+33);m.HEAPU8[p+1]=1;const sp=m.stackSave();result.push(m._probe_action(INDEX,BigInt(p),0n,0n,0n,0n,0n,0n,0n,0n,0n));assert.equal(m.stackSave(),sp);}
assert.equal(result[0],1n,'unchanged original C witness');assert.equal(result[1],result[0],'unchanged C must reject wrong pick_level index');
""".replace('REF',json.dumps((r/'.cache/dungeon-first-pass/dungeon-reference.mjs').as_uri())).replace('HYBRID',json.dumps((r/'.cache/dungeon-first-pass/dungeon-hybrid.mjs').as_uri())).replace('INDEX',str([f['name']for f in json.loads((r/'.cache/dungeon-first-pass/functions.json').read_text())].index('pick_level')))
(w/'negative.mjs').write_text(focus);p=subprocess.run([str(r/'.cache/emsdk/node/24.19.0_64bit/bin/node'),str(w/'negative.mjs')],capture_output=True,text=True);(w/'actual-assertion.log').write_text(p.stdout+p.stderr)
assert p.returncode!=0 and 'AssertionError'in p.stderr and 'unchanged C must reject wrong pick_level index'in p.stderr,(p.returncode,p.stdout,p.stderr)
assert {str(p):sha(p)for p in paths}==before;(w/'unchanged-oracle-hashes.json').write_text(json.dumps(before,indent=2)+'\n')
print('PASS deliberate private wrong pick_level index rejected by actual unchanged C AssertionError; original/prepared/referenceWasm/authoredJS hashes unchanged')
