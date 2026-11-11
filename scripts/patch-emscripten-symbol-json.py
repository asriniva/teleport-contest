#!/usr/bin/env python3
"""Check, explicitly apply, or restore the pinned SDK symbol-JSON patch."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import stat
import tempfile

root = Path(__file__).resolve().parents[1]
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--source', type=Path,
                    default=root / '.cache/emsdk/upstream/emscripten/src/jsifier.mjs')
actions = parser.add_mutually_exclusive_group()
actions.add_argument('--apply', action='store_true')
actions.add_argument('--restore', action='store_true')
parser.add_argument('--expect', choices=['original', 'candidate', 'either'], default='either')
args = parser.parse_args()
contract = json.loads((root / 'scripts/patches/emscripten-4.0.10-symbol-json.json').read_text())
digest = lambda data: hashlib.sha256(data).hexdigest()
source = args.source.resolve()
before = source.read_bytes()
state = next((name for name in ['original', 'candidate']
              if digest(before) == contract[name + 'Sha256']), None)
if state is None or args.expect not in ['either', state]:
    parser.error('SDK source hash does not match the reviewed required state')
target = 'candidate' if args.apply else 'original' if args.restore else state
replacement = before
if target != state:
    old = contract['old' if state == 'original' else 'candidate'].encode()
    new = contract['candidate' if target == 'candidate' else 'old'].encode()
    if before.count(old) != 1:
        parser.error('Expected exactly one reviewed serialization region')
    replacement = before.replace(old, new, 1)
    if digest(replacement) != contract[target + 'Sha256']:
        parser.error('Patch result does not match the reviewed complete source')
    temporary = None
    try:
        with tempfile.NamedTemporaryFile(dir=source.parent, prefix='.symbol-json-', delete=False) as stream:
            temporary = Path(stream.name)
            stream.write(replacement)
            stream.flush()
            os.fsync(stream.fileno())
        os.chmod(temporary, stat.S_IMODE(source.stat().st_mode))
        os.replace(temporary, source)
        temporary = None
    finally:
        if temporary is not None:
            temporary.unlink(missing_ok=True)
if source.read_bytes() != replacement:
    raise RuntimeError('SDK verification after action failed')
print(json.dumps(dict(state=target, changed=target != state,
                      beforeSha256=digest(before), afterSha256=digest(replacement))))
