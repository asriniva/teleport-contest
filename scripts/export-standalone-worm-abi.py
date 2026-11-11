#!/usr/bin/env python3
"""Source-bind WORM public boundaries and unchanged original runtime transport."""
import hashlib,json,os,re
from pathlib import Path
root=Path(__file__).resolve().parents[1]
reference=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve()
tree=reference/'.cache/wasm64-build/tree'
library=(root/'nethack-c/wasm/tu-libraries/worm.js').read_text()
public=re.findall(r'^  (\w+)__deps:.*?\1__sig:',library,re.M)
public=[name for name in public if not name.startswith('teleport_')]
assert len(public)==24,public
monster=['initworm','worm_move','worm_nomove','wormgone','wormhitu','cutworm','see_wsegs','detect_wsegs','place_wsegs','sanity_check_worm','remove_worm','place_worm_tail_randomly','size_wseg','count_wsegs','worm_known','wseg_at','flip_worm_segs_vertical','flip_worm_segs_horizontal','redraw_worm']
dependencies={'newsym':['c','c'],'mcalcmove':['p','b'],'mattacku':['p'],'clone_mon':['p','c','c'],'canseemon':['p'],'sensemon':['p'],'s_suffix':['p'],'mon_nam':['p'],'Monnam':['p'],'rn2_on_display_rng':['i'],'show_glyph':['c','c','i'],'fmt_ptr':['p'],'isok':['c','c'],'rnd_nextto_goodpos':['p','p','p'],'dist2':['c','c','c','c'],'distmin':['c','c','c','c']}
for name in dependencies:assert re.search(r'\b'+name+r':',library),name
assert '#define Sfo_coordxy(a,b,c) sfo_int16(a, b, c)' in (tree/'include/savefile.h').read_text()
assert '#define Sfi_coordxy(a,b,c) sfi_int16(a, b, c)' in (tree/'include/savefile.h').read_text()
layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['worm']
local=['js/standalone/worm.js','scripts/export-standalone-worm-abi.py','js/ported/worm.js','js/ported/worm-runtime.js','js/ported/wasm-runtime.js','nethack-c/wasm/tu-libraries/worm.js','nethack-c/wasm/tu-support.c','scripts/tu-worm-layout.h','js/wasm/tu-layouts.json','nethack-c/wasm/compile-defines.json']
refs=[tree/'src/worm.c',*sorted((tree/'include').glob('*.h'))]
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
data={'publicFunctions':public,'monsterArguments':monster,'dependencies':dependencies,'rngCallers':['worm_move','worm_nomove','cutworm'],'layout':layout,'sourceSha256':{str(p):sha(p)for p in [*[root/n for n in local],*refs]}}
(root/'js/standalone/worm-abi.json').write_text(json.dumps(data,indent=2)+'\n')
print('Bound',len(public),'public WORM functions and',len(dependencies),'native dependency boundaries')
