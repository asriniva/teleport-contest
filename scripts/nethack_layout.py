"""CLI adapter for immutable historical source audits after consolidation."""
from pathlib import Path
import subprocess,sys
ROOT=Path(__file__).resolve().parents[1]
def historical_cli(file):
 if not(ROOT/'docs/runtime-environment/nethack-layout.json').exists():return
 node=ROOT/'.cache/emsdk/node/24.19.0_64bit/bin/node'
 result=subprocess.run([str(node),str(ROOT/'scripts/nethack-layout.mjs'),'--historical',str(Path(file).resolve().relative_to(ROOT)),*sys.argv[1:]],cwd=ROOT)
 raise SystemExit(result.returncode)
