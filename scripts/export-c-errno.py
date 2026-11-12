"""Reproduce C-locale strerror data from the pinned SDK headers."""
from pathlib import Path
import hashlib,json,re,subprocess
root=Path(__file__).resolve().parents[1]
sdk=root/'.cache/emsdk/upstream';source=sdk/'emscripten/system/lib/libc/musl/src/errno/__strerror.h'
macros=subprocess.check_output([str(sdk/'bin/clang'),'--target=wasm64-unknown-emscripten','--sysroot='+str(sdk/'emscripten/cache/sysroot'),'-dM','-E','-x','c','-'],input='#include <errno.h>\n',text=True)
defined=set(re.findall(r'^#define (\w+) ',macros,re.M));rows=[(name,json.loads(quoted))for name,quoted in re.findall(r'^E\((\w+),\s*("(?:[^"\\]|\\.)*")\)',source.read_text(),re.M)if name.isdigit()or name in defined]
program='#include <errno.h>\n'+''.join('const long long errno_'+name+'='+name+';\n' for name,_ in rows)
ir=subprocess.check_output([str(sdk/'bin/clang'),'--target=wasm64-unknown-emscripten','--sysroot='+str(sdk/'emscripten/cache/sysroot'),'-S','-emit-llvm','-O0','-o','-','-x','c','-'],input=program,text=True)
values=dict(re.findall(r'@errno_(\w+) = .*?constant i64 (-?\d+)',ir));messages={values[name]:text for name,text in rows}
data={'profile':'Pinned Emscripten musl/WASI C locale','source':str(source.relative_to(root)),'sourceSha256':hashlib.sha256(source.read_bytes()).hexdigest(),'messages':messages}
path=root/'js/c-runtime/errno-messages.json';expected=json.dumps(data,indent=2)+'\n'
if '--check' in __import__('sys').argv:assert path.read_text()==expected,'Errno data differs from pinned source'
else:path.write_text(expected)
print('Bound',len(messages),'original C errno messages.')
