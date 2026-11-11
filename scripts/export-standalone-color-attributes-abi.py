#!/usr/bin/env python3
"""Bind original COLORATT/POSIXREGEX contexts and existing measured layouts."""
import hashlib,json,os,re,subprocess
from pathlib import Path
root=Path(__file__).resolve().parents[1]
paths=['scripts/export-standalone-color-attributes-abi.py','js/standalone/color-attributes.js','js/ported/coloratt.js','js/ported/coloratt-runtime.js','js/ported/posixregex.js','js/ported/posixregex-runtime.js','js/services/wasm-dependency-runtime.js','js/services/posix-regex.js','nethack-c/wasm/tu-support.c','nethack-c/wasm/native-terminal.h','nethack-c/wasm/full-original-c-native.c','nethack-c/wasm/tu-libraries/coloratt.js','nethack-c/wasm/tu-libraries/posixregex.js','scripts/tu-coloratt-layout.h','scripts/tu-posixregex-layout.h','js/wasm/tu-layouts.json','js/standalone/records.json']
ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree'
source=tree/'sys/share/posixregex.c';header=ref/'.cache/emsdk/upstream/emscripten/cache/sysroot/include/regex.h'
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
expressions={'size':'sizeof(struct nhregex)','NhregexSize':'sizeof(struct nhregex)','re':'offsetof(struct nhregex,re)','err':'offsetof(struct nhregex,err)','regexSize':'sizeof(regex_t)','intSize':'sizeof(int)','pointerSize':'sizeof(void*)','BUFSZ':'BUFSZ','REG_EXTENDED':'REG_EXTENDED','REG_NOSUB':'REG_NOSUB','REG_NOMATCH':'REG_NOMATCH','identifierSize':'sizeof regex_id','boolSize':'sizeof(boolean)','boolSigned':'((boolean)-1<0)'}
probe=root/'.cache/color-posixregex-abi.c';probe.write_text('#include '+json.dumps(str(source))+'\n#include <stddef.h>\n'+'\n'.join('const unsigned long probe_'+k+'=('+v+');'for k,v in expressions.items())+'\n')
ir=subprocess.check_output([str(ref/'.cache/emsdk/upstream/bin/clang'),*flags,'-S','-emit-llvm','-O0','-o','-',str(probe)],text=True)
native={k:int(re.search(r'@probe_'+k+r' = .*?constant i64 (\d+)',ir)[1])for k in expressions}
layouts=json.loads((root/'js/wasm/tu-layouts.json').read_text())
data={'layout':{'coloratt':layouts['coloratt'],'posixregex':native},'sourceSha256':{p:hashlib.sha256((root/p).read_bytes()).hexdigest()for p in paths},'referenceHeaderSha256':{str(p.relative_to(ref)):hashlib.sha256(p.read_bytes()).hexdigest()for p in [source,header]},'scope':'Original native storage/view transport; cleanup/regex source policy unchanged; original-C connected acceptance is separate.'}
(root/'js/standalone/color-attributes-abi.json').write_text(json.dumps(data,indent=2)+'\n')
print('Bound original COLORATT/POSIXREGEX storage and measured ABI.')
