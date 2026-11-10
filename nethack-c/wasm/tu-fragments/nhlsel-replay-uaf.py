"""Replay frozen ordinary-allocator unary mismatch; expected exit status is 1."""
from pathlib import Path
import hashlib,json,os,subprocess
root=Path(__file__).resolve().parents[3];replay=root/'.cache/nhlsel-uaf-replay';manifest=json.loads((replay/'replay-input-hashes.json').read_text())
for path,expected in manifest.items():assert hashlib.sha256((replay/path).read_bytes()).hexdigest()==expected,('Replay input changed',path)
env=os.environ.copy();env.update(TELEPORT_NHLSEL_PROBE_DIR=str(replay/'.cache/nhlsel-first-pass'),TELEPORT_NHLSEL_UAF_WITNESS='1',TELEPORT_NHLSEL_DIAGNOSTICS_DIR=str(replay))
with (replay/'replay.log').open('w') as log:result=subprocess.run([str(root/'.cache/emsdk/node/24.19.0_64bit/bin/node'),str(replay/'scripts/test-tu-nhlsel.mjs')],cwd=root,env=env,stdout=log,stderr=subprocess.STDOUT)
raw=json.loads((replay/'upstream-uaf-raw.json').read_text());assert result.returncode!=0;assert raw['label']=='unresolved upstream unary alias use-after-free:state';assert raw['reference']!=raw['hybrid'];assert raw['referenceTrace']==raw['hybridTrace'];assert 'free:argalias1:map11:map21;dupstr:argalias1:map11:map21:after-free1;' in raw['referenceTrace']
print('Reproduced unresolved ordinary-allocator C/JS unary mismatch, with identical actual alias/free-before-dupstr events. This is failing-path evidence, not parity acceptance. See',replay/'replay.log')
raise SystemExit(result.returncode)
