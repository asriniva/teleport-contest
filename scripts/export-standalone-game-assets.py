#!/usr/bin/env python3
"""Package exact sealed original-C game data, without executable/oracle artifacts."""
import argparse,base64,hashlib,json,stat
from pathlib import Path
root=Path(__file__).resolve().parents[1]
parser=argparse.ArgumentParser();parser.add_argument('--reference',type=Path,default=root/'.cache/full-original-c-v1');parser.add_argument('--check',action='store_true');args=parser.parse_args();reference=args.reference.resolve();receipt_path=reference/'receipt.json';receipt=json.loads(receipt_path.read_text());assets=reference/'assets';sha=lambda b:hashlib.sha256(b).hexdigest()
assert receipt['gameTranslationUnits']==140 and receipt['luaTranslationUnits']==32 and not receipt['syntheticGameGlobals'] and not receipt['abortBoundaries'] and not receipt['portedTranslationUnits'],'Require full sealed original-C recipe'
sealed={p.split('/assets/',1)[1]:h for p,h in receipt['sourceSha256'].items()if '/assets/'in p}
files=sorted(p for p in assets.rglob('*')if p.is_file());assert len(files)==len(sealed)==157,'Review source asset manifest'
assert {p.relative_to(assets).as_posix()for p in files}==set(sealed),'Exact sealed asset names'
entries=[];manifest=[]
for p in files:
 name=p.relative_to(assets).as_posix();assert not p.is_symlink() and not name.startswith('/') and '..'not in p.relative_to(assets).parts
 assert p.suffix.lower()not in {'.wasm','.mjs','.js','.json','.so','.dylib','.dll','.exe','.o','.a'},'No runtime/oracle/session artifacts'
 data=p.read_bytes();digest=sha(data);assert digest==sealed[name],f'Changed original asset {name}'
 mode=stat.S_IMODE(p.stat().st_mode);assert mode in [0o600,0o644],f'Review asset mode {name}'
 entries.append({'path':name,'mode':mode,'base64':base64.b64encode(data).decode('ascii')});manifest.append({'path':name,'mode':mode,'bytes':len(data),'sha256':digest})
assert next(e for e in entries if e['path']=='license')['base64']==base64.b64encode((assets/'license').read_bytes()).decode()
for name in ['record','perm','livelog','logfile','xlogfile']:assert (assets/name).stat().st_size==0,'Baseline writable game files only; no recording state'
difference=reference/'prepared-pristine-differences.json';difference_hash=next(h for p,h in receipt['sourceSha256'].items()if p.endswith('/prepared-pristine-differences.json'));assert sha(difference.read_bytes())==difference_hash
builder_hash=next(h for p,h in receipt['sourceSha256'].items()if p.endswith('/scripts/build-full-original-c.py'));assert sha((root/'scripts/build-full-original-c.py').read_bytes())==builder_hash,'Original sealed builder changed'
bundle={'version':1,'root':'/nethack','entries':entries};bundle_bytes=(json.dumps(bundle,separators=(',',':'),ensure_ascii=True)+'\n').encode()
metadata={'version':1,'files':manifest,'fileCount':len(entries),'totalBytes':sum(e['bytes']for e in manifest),'bundleSha256':sha(bundle_bytes),'provenance':{'source':'Exact assets embedded by the sealed complete prepared original-C reference; prepared configured data, not a claim of pristine upstream bytes.','upstream':receipt['upstream'],'profile':receipt['profile'],'buildEnvironment':receipt['buildEnvironment'],'referenceReceiptSha256':sha(receipt_path.read_bytes()),'preparedPristineDifferencesSha256':difference_hash,'exporterSha256':sha(Path(__file__).read_bytes()),'originalCBuilderSha256':builder_hash,'loaderSha256':sha((root/'js/nethack/game-assets.js').read_bytes())},'licenses':{'NetHack':'Verbatim original game license is both the /nethack/license bundle member and game-assets.LICENSE.','terminfo':'Pinned compiled xterm-256color entry; nethack-c/wasm/terminfo/README.md and LICENSE.ncurses remain unchanged.'},'scope':'Game data only: exact157 filenames/bytes/source modes, including five empty600 baseline files. No Wasm, compiled runtime, expected session output, saved games or engine policies. Loader/default selection is a separate gated change.'}
outputs={root/'js/nethack/game-assets.json':bundle_bytes,root/'js/nethack/game-assets-manifest.json':(json.dumps(metadata,indent=2)+'\n').encode(),root/'js/nethack/game-assets.LICENSE':(assets/'license').read_bytes()}
for p,data in outputs.items():
 if args.check:assert p.read_bytes()==data,f'Regenerate {p.relative_to(root)}'
 else:p.write_bytes(data)
print(('Checked'if args.check else'Packaged')+f' {len(entries)} sealed game assets, {metadata["totalBytes"]} logical bytes; {len(bundle_bytes)} bundle bytes.')
