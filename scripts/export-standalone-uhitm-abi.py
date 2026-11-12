#!/usr/bin/env python3
"""Bind unchanged UHITM full factory and its native typed boundary corpus."""
import hashlib,json,re
from pathlib import Path
root=Path(__file__).resolve().parents[1];r=(root/'js/nethack/bindings/uhitm.js').read_text();lib=(root/'nethack-c/wasm/tu-libraries/uhitm.js').read_text();support=(root/'nethack-c/wasm/tu-fragments/uhitm-support.inc').read_text();dec=json.JSONDecoder();public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions']
def value(name):return dec.raw_decode(r.split('const '+name+'=',1)[1])[0]
def arguments(s):
 out=[];depth=0;start=0
 for i,c in enumerate(s):
  if c in '([':depth+=1
  elif c in ')]':depth-=1
  elif c==','and depth==0:out.append(s[start:i].strip());start=i+1
 out.append(s[start:].strip());return[x for x in out if x and x!='void']
calls={}
for name,target in re.findall(r'^\s*(\w+):\([^\n]*?\)=>(?:Number\()?_(\w+)\(',lib,re.M):
 if target.startswith('teleport_uhitm_'):continue
 if target=='__assert_fail':proto='void (const char *, const char *, unsigned int, const char *)'
 else:proto=public[target]
 ret,args=proto.split('(',1);calls[name]={'target':target,'return':ret.strip(),'arguments':arguments(args[:-1])}
variadic={}
for ret,name,params,target in re.findall(r'\b(void|int) (teleport_uhitm_v_\d+)\(([^)]*)\)\{(?:return )?(\w+)\(',support):
 variadic[name]={'target':target,'return':ret,'arguments':[re.sub(r'\s*a\d+$','',p).replace('restrict','').strip()for p in arguments(params)]}
dispatch={}
for name,index,table in re.findall(r'^(\w+):\([^\n]*?=>\{var shape=formatShape\(a(\d+)\);var fn=(\{[^\n]*?\})\[shape\];',lib,re.M):dispatch[name]={'formatIndex':int(index),'shapes':json.loads(table)}
assert len(dispatch)==14,(len(dispatch),list(dispatch))
records=value('records');bits={}
for typ,fields in records.items():
 for name,f in fields.items():
  if f.get('bit'):bits[f['bitIndex']]={'type':typ,'field':name}
source=(root/'js/ported/uhitm.js').read_text();names=re.findall(r'^export function (\w+)\(',source,re.M)
paths=['scripts/export-standalone-uhitm-abi.py','js/standalone/uhitm.js','js/ported/uhitm.js','js/nethack/bindings/uhitm.js','nethack-c/wasm/tu-libraries/uhitm.js','nethack-c/wasm/tu-fragments/uhitm-support.inc','nethack-c/wasm/tu-fragments/uhitm-hashes.json','js/standalone/public-functions.json','js/standalone/records.json','js/wasm/tu-layouts.json']
data={'layout':json.loads((root/'js/wasm/tu-layouts.json').read_text())['uhitm'],'globals':value('globals'),'params':value('params'),'records':records,'bits':bits,'calls':calls,'variadic':variadic,'dispatch':dispatch,'public':{n:public[n]for n in names if n in public},'callbacks':value('CALLBACK_NAMES'),'literalCorpus':dec.raw_decode(lib.split('sourceLiterals=new Set(',1)[1])[0],'persistentOffsets':[0,1,257],'persistentBytes':267,'sourceSha256':{p:hashlib.sha256((root/p).read_bytes()).hexdigest()for p in paths}}
(root/'js/standalone/uhitm-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound original UHITM factory records, callbacks, globals, persistence and typed format corpus.')
