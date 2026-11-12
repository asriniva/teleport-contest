#!/usr/bin/env python3
"""Bind unchanged RESTORE schemas, private bucket ABI and native call seams."""
import hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree'
runtime=root/'js/nethack/bindings/restore.js';source=tree/'src/restore.c';support=root/'nethack-c/wasm/tu-restore-support.inc';types=root/'nethack-c/wasm/tu-restore-types.h';library=root/'nethack-c/wasm/tu-libraries/restore.js';header=root/'scripts/tu-restore-layout.h'
text=runtime.read_text();decode=json.JSONDecoder();decl=lambda name:decode.raw_decode(text.split('const '+name+'=',1)[1])[0];schemas,globals_=decl('schemas'),decl('globals')
known=json.loads((root/'js/nethack/records.json').read_text())['records'];private={name:row for name,row in schemas.items()if row['ctype'].removeprefix('struct ').removeprefix('union ')not in known}
if set(private)!={'bucket','restore_id_pair'}:raise ValueError('Review changed RESTORE private records')
body=support.read_text().split('void *teleport_restore_global(int index){switch(index){',1)[1].split('default:',1)[0];rows=[(int(i),name)for i,name in re.findall(r'case (\d+):return \(void\*\)&(\w+);',body)]
if rows!=list(enumerate(row['name']for row in globals_)):raise ValueError('RESTORE source/native global map mismatch')
serializers=dict(re.findall(r'^\s*(Sfi_\w+):[^\n]*?=>_(\w+)\(',library.read_text(),re.M))
if not serializers or any(k.lower()!=v for k,v in serializers.items()):raise ValueError('Review RESTORE serializer aliases')
assertions=[{'index':int(i),'expression':expr,'file':file,'line':int(line),'function':fn}for i,expr,file,line,fn in re.findall(r'case (\d+):__assert_fail\("([^"]+)","([^"]+)",(\d+),"([^"]+)"\)',support.read_text())]
if [r['index']for r in assertions]!=[0,1]:raise ValueError('Review RESTORE assertions')
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),'-I'+str(root/'nethack-c/wasm'),*['-D'+d for d in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
clang=ref/'.cache/emsdk/upstream/bin/clang'
probe='#define TELEPORT_RESTORE_REFERENCE_LAYOUT 1\n'+''.join('#include '+json.dumps(str(p))+'\n'for p in [source,types,header])+'\n'
for i,(name,row)in enumerate(private.items()):
 t=row['ctype'];probe+='const unsigned long probe_'+str(i)+'_size=sizeof('+t+');\nconst unsigned long probe_'+str(i)+'_align=_Alignof('+t+');\n'
 for j,f in enumerate(row['fields']):
  if f['bit']:raise ValueError('Review private RESTORE bitfield')
  probe+='const unsigned long probe_'+str(i)+'_'+str(j)+'=offsetof('+t+','+f['name']+');\n'
with tempfile.TemporaryDirectory(prefix='standalone-restore-abi-')as tmp:
 p=Path(tmp)/'probe.c';p.write_text(probe);ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(p)],text=True);value=lambda k:int(re.search(r'@probe_'+k+r' = .*?constant i64 (\d+)',ir)[1]);records={}
 for i,(name,row)in enumerate(private.items()):
  key='teleport_restore_bucket'if name=='bucket'else name;records[key]={'size':value(str(i)+'_size'),'alignment':value(str(i)+'_align'),'fields':{f['name']:{'offset':value(str(i)+'_'+str(j)),'ctype':f['ctype']+' '+f['name']}for j,f in enumerate(row['fields'])}}
 deps=subprocess.check_output([str(clang),*flags,'-M',str(p)],text=True);headers=sorted(set(Path(q).resolve()for q in shlex.split(deps.split(':',1)[1].replace('\\\n',''))))
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();inputs=[Path(__file__).resolve(),runtime,root/'js/ported/restore.js',support,types,library,header,root/'nethack-c/wasm/compile-defines.json',root/'js/wasm/tu-layouts.json',root/'js/nethack/records.json',root/'js/nethack/public-functions.json']
data={'schemas':schemas,'globals':globals_,'records':records,'recordTypes':{name:('restore_id_pair'if name=='restore_id_pair'else row['ctype'])for name,row in schemas.items()},'serializers':serializers,'assertions':assertions,'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in headers if p.is_relative_to(ref)}}
(root/'js/nethack/restore-lifecycle-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound RESTORE schemas, shared globals, private bucket ABI and serializer/assertion transport.')
