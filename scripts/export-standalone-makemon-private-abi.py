#!/usr/bin/env python3
"""Measure the original lazy MAKEMON selection tables, without generation policy."""
import hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';source=tree/'src/makemon.c';clang=ref/'.cache/emsdk/upstream/bin/clang'
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
headerMacros={'nhUse':re.search(r'^\s*#\s*define\s+nhUse\(arg\)\s+(.+)$',(tree/'include/lint.h').read_text(),re.M)[1]}
assert re.sub(r'\s+','',headerMacros['nhUse'])=='((void)(arg))','Review native nhUse macro'
declarations=[]
for name in ['mongen_order','mclass_maxf','mongen_order_init']:
 matches=re.findall(r'^static [^;\n]*\b'+name+r'\b[^;\n]*;',source.read_text(),re.M);assert len(matches)==1,(name,matches);declarations+=matches
with tempfile.TemporaryDirectory(prefix='standalone-mongen-')as scratch:
 p=Path(scratch)/'probe.c';p.write_text('#include "hack.h"\n'+'\n'.join(declarations)+'\n'+''.join('const unsigned long probe_'+name+'=sizeof('+name+');\n'for name in ['mongen_order','mclass_maxf','mongen_order_init'])+'const unsigned long probe_count=NUMMONS;\nconst unsigned long probe_classes=MAXMCLASSES;\n')
 ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(p)],text=True);read=lambda name:int(re.search(r'@probe_'+name+r' = .*?constant i64 (\d+)',ir)[1]);storage={name:read(name)for name in ['mongen_order','mclass_maxf','mongen_order_init']};constants={'NUMMONS':read('count'),'MAXMCLASSES':read('classes')};assert storage=={'mongen_order':4*constants['NUMMONS'],'mclass_maxf':constants['MAXMCLASSES'],'mongen_order_init':1}
 deps=subprocess.check_output([str(clang),*flags,'-M',str(p)],text=True);headers={Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(ref)};headers.add(source)
paths=[Path(__file__).resolve(),root/'js/nethack/monster-selection.js',root/'js/nethack/monster-creation.js',root/'js/ported/makemon.js',root/'js/nethack/bindings/makemon.js',root/'nethack-c/wasm/tu-fragments/makemon-support.inc',root/'js/wasm/tu-layouts.json'];sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
(root/'js/nethack/makemon-private-abi.json').write_text(json.dumps({'headerMacros':headerMacros,'storageBytes':storage,'constants':constants,'originalDeclarations':declarations,'sourceSha256':{str(p.relative_to(root)):sha(p)for p in paths},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(headers)},'scope':'Original zero-initialized source-private table/flag storage and discarded-value header helper; original init_mongen_order and comparator/qsort policies execute unchanged.'},indent=2)+'\n');print('Measured original persistent MAKEMON table sizes and lazy initializer flag.')
