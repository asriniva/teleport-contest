#!/usr/bin/env python3
"""Measure unchanged UNIXUNIX/UNIXMAIN boundaries and configured SDK syscalls."""
import json,hashlib,os,re,shlex,subprocess
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';sdk=ref/'.cache/emsdk/upstream/emscripten'
known=json.loads((root/'js/standalone/records.json').read_text())['records']
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(sdk/'cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+d for d in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]];clang=ref/'.cache/emsdk/upstream/bin/clang'
data={'ports':{},'records':{},'aliases':{}};inputs=[Path(__file__).resolve(),root/'js/standalone/unix-platform.js',root/'js/standalone/unix-platform-syscalls.js',root/'nethack-c/wasm/compile-defines.json'];headers=set()
for name in ['unixunix','unixmain']:
 runtime=root/f'js/ported/{name}-runtime.js';text=runtime.read_text();schema=json.JSONDecoder().raw_decode(text.split('const schema=',1)[1])[0]
 support=root/f'nethack-c/wasm/tu-fragments/{name}-support.c';body=support.read_text().split('uint64_t teleport_'+name+'_layout(int index){switch(index){',1)[1].split('default:abort();}}',1)[0]
 expressions=re.findall(r'case (\d+):return\(uint64_t\)\((.*?)\);',body);assert [int(i)for i,_ in expressions]==list(range(len(schema['layoutKeys'])))
 private={k:v for k,v in schema['schema'].items()if v['ctype'].removeprefix('struct ').removeprefix('union ')not in known}
 probes=['const unsigned long probe_layout_'+i+'=('+expr+');'for i,expr in expressions]
 for i,(key,row)in enumerate(private.items()):
  probes+=['const unsigned long probe_'+str(i)+'_size=sizeof('+row['ctype']+');','const unsigned long probe_'+str(i)+'_align=_Alignof('+row['ctype']+');']
  for j,f in enumerate(row['fields']):
   assert not f['bit'];probes.append('const unsigned long probe_'+str(i)+'_'+str(j)+'=offsetof('+row['ctype']+','+f['name']+');')
 source=tree/f'sys/unix/{name}.c';scratch=root/f'.cache/{name}-standalone-abi.c'
 scratch.write_text('#include '+json.dumps(str(source))+'\n#include <stddef.h>\n#include <errno.h>\n#undef sa_handler\n'+'\n'.join(probes)+'\n')
 ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(scratch)],text=True);value=lambda key:int(re.search(r'@probe_'+key+r' = .*?constant i64 (\d+)',ir)[1])
 for i,(key,row)in enumerate(private.items()):
  ctype=row['ctype'];recordkey=ctype.removeprefix('struct ').removeprefix('union ')
  if recordkey.startswith('__typeof__'):recordkey='unix_platform_'+key;data['aliases'][ctype]=recordkey
  data['records'][recordkey]={'size':value(str(i)+'_size'),'alignment':value(str(i)+'_align'),'fields':{f['name']:{'offset':value(str(i)+'_'+str(j)),'ctype':f['ctype']+' '+f['name']}for j,f in enumerate(row['fields'])}}
 fullpath=root/f'nethack-c/wasm/tu-fragments/{name}-schema.json';full=json.loads(fullpath.read_text());inputs.append(fullpath)
 data['ports'][name]={'schema':{**full,**schema},'layout':[value('layout_'+str(i))for i in range(len(schema['layoutKeys']))]}
 deps=subprocess.check_output([str(clang),*flags,'-M',str(scratch)],text=True);headers.update(Path(p).resolve()for p in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(p).resolve()!=scratch)
 inputs += [runtime,root/f'js/ported/{name}.js',support,root/f'nethack-c/wasm/tu-libraries/{name}.js',source]
errors=sdk/'system/lib/libc/musl/src/errno/__strerror.h';rows=re.findall(r'E\((\w+),\s*("[^"\n]*")\)',errors.read_text())
extra=root/'.cache/unix-platform-sdk-abi.c';extra.write_text('#include <errno.h>\n#include <fcntl.h>\n#include <sys/stat.h>\n#include <stddef.h>\n'+''.join('const unsigned long probe_errno_'+name+'='+name+';\n'for name,_ in rows)+'const unsigned long probe_flock_type=offsetof(struct flock,l_type);\n'+''.join('const unsigned long probe_'+name+'='+name+';\n'for name in ['F_GETFD','F_SETFD','F_GETLK','F_SETLK','F_SETLKW']))
ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(extra)],text=True);value=lambda key:int(re.search(r'@probe_'+key+r' = .*?constant i64 (\d+)',ir)[1])
data['errors']={str(value('errno_'+name)):json.loads(message)for name,message in rows};data['fcntl']={key:value(key)for key in ['F_GETFD','F_SETFD','F_GETLK','F_SETLK','F_SETLKW','flock_type']}
inputs += [sdk/'src/lib/libsyscall.js',sdk/'system/lib/libc/emscripten_syscall_stubs.c',errors,sdk/'system/lib/libc/musl/src/stdio/perror.c',sdk/'system/lib/libc/musl/src/errno/strerror.c']
inputs.append(sdk/'system/lib/libc/musl/src/unistd/getlogin.c')
inputs.append(sdk/'system/lib/libc/musl/src/unistd/isatty.c')
early=tree/'src/earlyarg.c';earlytext=early.read_text();site=earlytext.index('Snprintf(');end=earlytext.index(');',site)+2;data['earlyargSnprintfLine']=earlytext.count('\n',0,end)+1
data['usageHelp']=re.search(r'#define USAGEHELP\s+"([^"]+)"',(tree/'include/global.h').read_text())[1]
inputs += [early,root/'js/ported/earlyarg.js',root/'js/ported/earlyarg-runtime.js',root/'nethack-c/wasm/tu-libraries/earlyarg.js',root/'nethack-c/wasm/tu-earlyarg-support.inc',root/'scripts/write-tu-source-metadata.py']
inputs += [root/'js/ported/mail.js',root/'js/ported/mail-runtime.js',root/'nethack-c/wasm/tu-libraries/mail.js',root/'nethack-c/wasm/tu-mail-support.inc',tree/'src/mail.c',root/'js/wasm/tu-layouts.json',root/'js/standalone/window-system.js']
inputs += [root/'js/standalone/records.json',root/'js/standalone/c-types.js',root/'js/standalone/address-ports.js',root/'js/standalone/stdio.js',root/'js/services/c-vfs.js']
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();data['sourceSha256']={str(p):sha(p)for p in sorted(set(inputs)|headers)}
(root/'js/standalone/unix-platform-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound UNIXUNIX/UNIXMAIN and SDK stat/locking boundaries')
