#!/usr/bin/env python3
"""Measure original DIG headers and bind unchanged native spell transport."""
import hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';header=root/'scripts/tu-dig-layout.h';support=root/'nethack-c/wasm/tu-dig-support.inc';source=tree/'src/dig.c';library=root/'nethack-c/wasm/tu-libraries/dig.js';clang=ref/'.cache/emsdk/upstream/bin/clang';layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['dig']
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
with tempfile.TemporaryDirectory(prefix='standalone-dig-')as scratch:
 p=Path(scratch)/'probe.c';body='#include '+json.dumps(str(tree/'src/decl.c'))+'\n#include '+json.dumps(str(header))+'\nunsigned dig_class_probe(struct objclass*p){return p->oc_bimanual;}\n';p.write_text(body);expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(p)],text=True);table=re.search(r'teleport_dig_layout\[\]\s*=\s*\{(.*?)\n\};',expanded,re.S)[1];rows=re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}',table,re.S);assert rows
 classfield=re.search(r'dig_class_probe\(struct objclass\*p\)\{return p->(\w+);',expanded)[1]
 body+='\n'.join('const unsigned long dig_value_'+str(i)+'=('+expression+');'for i,(_,expression)in enumerate(rows))+'\nconst unsigned long dig_deaf=__builtin_offsetof(__typeof__(u),uroleplay.deaf);';p.write_text(body);ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(p)],text=True);read=lambda n:int(re.search(r'@'+n+r' = .*?constant i64 (-?\d+)',ir)[1])&((1<<64)-1)
 measured={name:read('dig_value_'+str(i))for i,(name,_)in enumerate(rows)}
 if 'size'in layout and 'size'not in measured:measured['size']=measured['diggingSize']
 assert set(measured)==set(layout) and all(v==(int(layout[k])&((1<<64)-1))for k,v in measured.items()),repr({'missing':set(layout)-set(measured),'extra':set(measured)-set(layout),'different':[(k,v,layout.get(k))for k,v in measured.items()if v!=(int(layout.get(k,0))&((1<<64)-1))]})
 deaf=read('dig_deaf');deps=subprocess.check_output([str(clang),*flags,'-M',str(p)],text=True);headers=[Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(ref)]
deaf=read('dig_deaf')
native=support.read_text();lib=library.read_text();public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions']
globals=[v.strip().replace('(void*)','').replace('&','')for v in re.findall(r'case \d+:return (.*?);',native.split('teleport_dig_global',1)[1].split('struct obj*teleport_dig_equipment',1)[0])];assert len(globals)==21
bits={}
for kind in ['mon','obj','cls','trap']:
 body=native.split('unsigned teleport_dig_'+kind+'_bit',1)[1].split('void teleport_dig_set_'+kind+'_bit',1)[0];bits[kind]=re.findall(r'case \d+:return o->(\w+);',body);assert bits[kind],kind
assert bits['cls'][0]=='oc_bimanual';bits['cls'][0]=classfield
hero=re.findall(r'case \d+:return u\.(\w+);',native.split('unsigned teleport_dig_hero_bit',1)[1].split('void teleport_dig_set_hero_bit',1)[0]);level=re.findall(r'case \d+:return svl.level.flags\.(\w+);',native.split('unsigned teleport_dig_level_bit',1)[1].split('void teleport_dig_set_level_bit',1)[0]);terrain=re.findall(r'case \d+:return levl\[x\]\[y\]\.(\w+);',native.split('unsigned teleport_dig_terrain_bit',1)[1].split('void teleport_dig_set_terrain_bit',1)[0])
calls={}
for name,target in re.findall(r'^(\w+):[^\n]*?=>\s*(?:Number\()?_(\w+)\(',lib,re.M):
 if not target.startswith('teleport_dig_'):calls[name]={'target':target,'prototype':public[target]}
for n in ['set_occupation','get_iter_mons','cmdq_add_ec']:calls[n]={'target':n,'prototype':public[n]}
shapes=json.loads(re.search(r'var shapes=(\[[^;]+?\]),callers=',lib)[1]);callers=json.loads(re.search(r'callers=(\[[^;]+?\]);',lib)[1]);assert len(shapes)==12 and len(callers)==10
callbacks={'dig':'int (void)','watchman_canseeu':'boolean (struct monst *)'}
names=re.findall(r'^export function (\w+)',(root/'js/ported/dig.js').read_text(),re.M);sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();inputs=[Path(__file__).resolve(),root/'js/standalone/dig.js',header,support,library,root/'js/ported/dig.js',root/'js/nethack/bindings/dig.js',root/'js/wasm/tu-layouts.json',root/'js/standalone/records.json',root/'js/standalone/public-functions.json',root/'nethack-c/wasm/compile-defines.json']
result={'layout':layout,'globals':globals,'bits':bits,'heroBits':hero,'levelBits':level,'terrainBits':terrain,'roleplayDeafOffset':deaf,'callers':callers,'shapes':shapes,'callbacks':callbacks,'calls':calls,'public':{n:public[n]for n in names if n in public},'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(set(headers+[source]))}}
(root/'js/standalone/dig-abi.json').write_text(json.dumps(result,indent=2)+'\n');print('Bound original DIG header/global/bit/callback/typed-call/format ABI.')
