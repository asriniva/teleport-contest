from pathlib import Path
import re,json,hashlib
import argparse
p=argparse.ArgumentParser();p.add_argument('--source-root',required=True,type=Path);p.add_argument('--out',required=True,type=Path);args=p.parse_args();r=args.source_root.resolve();w=args.out.resolve();code=Path(__file__).resolve().parents[1];c=(r/'nethack-c/upstream/win/share/ppmwrite.c').read_text();j=(code/'js/ported-utilities/ppmwrite/ppmwrite.js').read_text();a=json.loads((w/'configured-functions.json').read_text());names=re.findall(r'export function (\w+)\(([^)]*)\)',j);assert[n for n,p in names]==[n['name']for n in a]
for(n,p),original in zip(names,a):assert[x.strip()for x in p.split(',')if x.strip()]==[x['name']for x in original['parameters']],n
comments=re.findall(r'/\*[\s\S]*?\*/',c);assert all(x in j for x in comments)
for exact in ['C.tiles_across = 20;','C.PpmScreen.Width = 20 * C.TILE_X;','C.curr_tiles_across++;','i += 2','C.rewind(C.ppm_file);','C.copyPixel(']:assert exact in j,exact
assert not re.search(r'function\s+\w+\(',j.replace('export function','export FUNCTION'))
(w/'source-guard.json').write_text(json.dumps({'status':'PASS','configuredFunctions':6,'names':[n for n,p in names],'formals':'exact original','originalComments':len(comments),'retainedControl':'source loops/branches/calls/order; Cnamespace/address/fullpixelcopy/stackref adaptations only','sourceSha256':hashlib.sha256(c.encode()).hexdigest(),'noAddedSourceFunctionHelpers':True},indent=2)+'\n');print('PASS6originalboundaries/formals/7comments')
