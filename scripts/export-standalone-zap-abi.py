#!/usr/bin/env python3
"""Measure configured ZAP header values and bind unchanged native seams."""
import hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';header=root/'scripts/tu-zap-layout.h';support=root/'nethack-c/wasm/tu-zap-support.inc';source=tree/'src/zap.c'
layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['zap']
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]];clang=ref/'.cache/emsdk/upstream/bin/clang'
with tempfile.TemporaryDirectory(prefix='standalone-zap-abi-')as scratch:
 probe=Path(scratch)/'probe.c';body='#include '+json.dumps(str(header))+'\n';probe.write_text(body)
 expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(probe)],text=True)
 rows=re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}',re.search(r'zap_layout\[\]\s*=\s*\{(.*?)\n\};',expanded,re.S)[1],re.S)
 body+='\n'.join('const unsigned long probe_zap_'+str(i)+'=('+expr+');'for i,(_,expr)in enumerate(rows))+'\n';
 native=support.read_text();decls=[v for v in re.findall(r'static char zap_[^;]+;',native)if 'zap_literals'not in v];body+='\n'.join(decls)+'\n';
 static_names=re.findall(r'case (\d+):return (zap_\w+);',native.split('void *teleport_zap_static_storage',1)[1].split('default:',1)[0]);
 for i,name in static_names:body+='const unsigned long probe_static_'+i+'=sizeof('+name+');\n'
 body+='const unsigned long probe_destroy=sizeof destroy_strings;\nconst unsigned long probe_charged=sizeof zap_charged_objs;\n';probe.write_text(body)
 ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(probe)],text=True)
 measured={name:int(re.search(r'@probe_zap_'+str(i)+r' = .*?constant i64 (-?\d+)',ir)[1])&((1<<64)-1)for i,(name,_)in enumerate(rows)}
 assert all(k in layout and measured[k]==(int(layout[k])&((1<<64)-1))for k in measured),'Review changed ZAP header profile'
 assert set(layout)-set(measured)<=set(['size']),'Review additional ZAP legacy layout keys'
 storage=[int(re.search(r'@probe_'+k+r' = .*?constant i64 (-?\d+)',ir)[1])for k in ['destroy','charged']]
 static_bytes={name:int(re.search(r'@probe_static_'+i+r' = .*?constant i64 (-?\d+)',ir)[1])for i,name in static_names}
 deps=subprocess.check_output([str(clang),*flags,'-M',str(probe)],text=True);headers=[Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(ref)]
runtime=(root/'js/ported/zap-runtime.js').read_text();decoder=json.JSONDecoder();schema=decoder.raw_decode(runtime.split('const schema = ',1)[1])[0]
native=support.read_text();roots=[name for _,name in re.findall(r'case (\d+):return &(\w+);',native.split('const void *teleport_zap_global',1)[1].split('default:',1)[0])];assert roots==list(schema['globals']),'Review native ZAP root map'
bits=[(int(i),type,field)for i,type,field in re.findall(r'case (\d+):return\(\(const (struct \w+)\*\)p\)->(\w+);',native.split('unsigned teleport_zap_get_bit',1)[1].split('void teleport_zap_set_bit',1)[0])];assert [i for i,_,_ in bits]==list(range(len(bits)))
statics=decoder.raw_decode((root/'nethack-c/wasm/tu-libraries/zap.js').read_text().split('const index=',1)[1])[0]
static_sizes={name:static_bytes[dict(static_names)[str(index)]]for name,index in statics.items()}
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();inputs=[Path(__file__).resolve(),header,support,root/'js/standalone/zap.js',root/'js/ported/zap.js',root/'js/ported/zap-runtime.js',root/'nethack-c/wasm/tu-libraries/zap.js',root/'js/standalone/public-functions.json',root/'js/wasm/tu-layouts.json',root/'nethack-c/wasm/compile-defines.json']
public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions'];names=re.findall(r'^export function (\w+)',(root/'js/ported/zap.js').read_text(),re.M)
assert 'unsigned long teleport_zap_dep_strlen(const char * a0){return strlen(a0);}'in native,'Review native ZAP strlen size_t transport'
data={'nativeTransports':{'strlen':'unsigned long (const char *)'},'public':{name:public[name]for name in names if name in public},'layout':layout,'globals':roots,'storageBytes':storage,'staticBytes':static_sizes,'bits':[{'type':type,'field':field}for _,type,field in bits],'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(set(headers+[source]))},'scope':'Original ZAP factory/storage shared owner; accepted public subset determined by connected tests, not whole-module registration.'}
(root/'js/standalone/zap-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound ZAP native storage/global/packed-field ABI for unchanged source factory.')
