#!/usr/bin/env python3
"""Bind original DOGMOVE views, private backing and native dependencies."""
import hashlib,json,re
from pathlib import Path
root=Path(__file__).resolve().parents[1];schema=json.loads((root/'nethack-c/wasm/tu-fragments/dogmove-schema.json').read_text());lib=(root/'nethack-c/wasm/tu-libraries/dogmove.js').read_text();calls={}
for name,params,target,args in re.findall(r'^      (\w+):\(([^)]*)\)=>(?:Number\()?_(\w+)\((.*?)\)\)?[,]?$',lib,re.M):
 if target.startswith('teleport_dogmove_'):continue
 calls[name]=target
public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions']
paths=['scripts/export-standalone-dogmove-abi.py','js/standalone/dogmove.js','js/ported/dogmove.js','js/nethack/bindings/dogmove.js','js/backends/emscripten/runtime.js','nethack-c/wasm/tu-fragments/dogmove-schema.json','nethack-c/wasm/tu-fragments/dogmove-support.c','nethack-c/wasm/tu-fragments/dogmove-source-data.h','nethack-c/wasm/tu-libraries/dogmove.js','js/standalone/public-functions.json','js/standalone/records.json','js/wasm/tu-layouts.json']
data={'layout':json.loads((root/'js/wasm/tu-layouts.json').read_text())['dogmove'],'schemas':schema['schema'],'globals':schema['globals'],'types':schema['functionTypes'],'dependencies':schema['dependencyTypes'],'calls':calls,'rngSites':schema['rngSites'],'assertion':{'condition':'edog->apport > 0','function':'dog_invent','line':417},'public':[n for n in schema['functionTypes']if n in public],'sourceSha256':{p:hashlib.sha256((root/p).read_bytes()).hexdigest()for p in paths}}
(root/'js/standalone/dogmove-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound original DOGMOVE schemas, signatures, globals, RNG and native support.')
