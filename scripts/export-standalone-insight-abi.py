#!/usr/bin/env python3
"""Bind source-native INSIGHT globals, storage, fields and formatter metadata."""
import hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';header=root/'scripts/tu-insight-layout.h';support=root/'nethack-c/wasm/tu-insight-support.inc';runtime=root/'js/ported/insight-runtime.js';clang=ref/'.cache/emsdk/upstream/bin/clang';layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['insight'];decoder=json.JSONDecoder()
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
with tempfile.TemporaryDirectory(prefix='standalone-insight-')as scratch:
 p=Path(scratch)/'probe.c';body='#include '+json.dumps(str(header))+'\n';p.write_text(body);expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(p)],text=True)
 rows=re.findall(r'\{\s*"([^"]+)"\s*,\s*\(size_t\)\((.*?)\)\s*\}',expanded,re.S);assert rows
 body+='extern const char *const vanqorders[NUM_VANQ_ORDER_MODES][3];\nconst unsigned long insight_public_table_size=sizeof vanqorders;\nvoid proof_insight_qsort(void *p,size_t n,size_t z,int(*cmp)(const void*,const void*)){qsort(p,n,z,cmp); }\n';body+='\n'.join('const unsigned long insight_value_'+str(i)+'=('+expression+');'for i,(_,expression)in enumerate(rows))+'\nconst unsigned long insight_table_size=NUM_VANQ_ORDER_MODES*3*sizeof(void*);\n';p.write_text(body);ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(p)],text=True)
 read=lambda key:int(re.search(r'@'+key+r' = .*?constant i64 (-?\d+)',ir)[1])&((1<<64)-1)
 measured={name:read('insight_value_'+str(i))for i,(name,_)in enumerate(rows)}
 assert set(measured)==set(layout) and all(v==(int(layout[k])&((1<<64)-1))for k,v in measured.items()),repr({'extraFrozen':set(layout)-set(measured),'extraMeasured':set(measured)-set(layout),'different':[(k,v,layout.get(k))for k,v in measured.items()if v!=(int(layout.get(k,0))&((1<<64)-1))]})
 assert read('insight_public_table_size')==read('insight_table_size');assert re.search(r'call void @nh_deterministic_qsort\(',ir),'Review configured INSIGHT qsort macro';storage=[read('insight_table_size'),40,32,7];deps=subprocess.check_output([str(clang),*flags,'-M',str(p)],text=True);headers=[Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(ref)]
text=runtime.read_text();schema=decoder.raw_decode(text.split('const schema = ',1)[1])[0];bitindex=decoder.raw_decode(text.split('const bitIndex=',1)[1])[0];native=support.read_text();gb=native.split('teleport_insight_global(int i){switch(i){',1)[1].split('default:',1)[0];assert [expr.replace('&','')for _,expr in re.findall(r'case (\d+):return (.*?);',gb)]==list(schema['globals'])
bits=[None]*len(bitindex)
for key,index in bitindex.items():
 type,field=key.split(':');bits[index]=[type,field];assert f'case {index}:return((const {type}*)p)->{field};'in native and f'case {index}:(({type}*)p)->{field}=v;break;'in native
assert 'static char insight_sizebuf[40],insight_piousbuf[32],insight_punctclasses[7];'in native
source=(tree/'src/insight.c').read_text();clean=re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',lambda m:re.sub(r'[^\n]',' ',m[0]),source,flags=re.S);defs=[(m.start(),m[1])for m in re.finditer(r'^(\w+)\([^;{}]*\)\s*\{',clean,re.M)];formats=[]
for m in re.finditer(r'\bSnprintf\s*\(',clean):
 i=clean.index('(',m.start());depth=1;j=i+1
 while depth:
  if clean[j]=='(':depth+=1
  elif clean[j]==')':depth-=1
  j+=1
 formats.append({'line':clean[:j].count('\n')+1,'function':[name for at,name in defs if at<m.start()][-1]})
assert len(formats)==10
assertion=re.search(r'\bassert\((.*?)\);',source);assert assertion and assertion[1]=='u.ustuck != NULL'
assert re.search(r'size_str\(int msize\)\s*\{\s*static char outbuf\[40\];',source) and re.search(r'piousness\([^)]*\)\s*\{\s*static char buf\[32\];',source)
public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions'];names=re.findall(r'^export function (\w+)',(root/'js/ported/insight.js').read_text(),re.M);records=json.loads((root/'js/standalone/records.json').read_text())['records'];windows={name:row['ctype']for name,row in records['window_procs']['fields'].items()if name.startswith('win_')}
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();inputs=[Path(__file__).resolve(),root/'js/standalone/insight.js',runtime,header,support,root/'js/ported/insight.js',root/'nethack-c/wasm/tu-libraries/insight.js',root/'js/wasm/tu-layouts.json',root/'js/standalone/records.json',root/'js/standalone/public-functions.json',root/'nethack-c/wasm/compile-defines.json']
assert 'void teleport_insight_qsort(void*p,size_t n,size_t z){qsort(p,n,z,insight_comparator);}'in native
assert 'extern const char *const vanqorders[NUM_VANQ_ORDER_MODES][3];'in native
result={'publicStorage':{'vanqorders':0},'qsort':{'target':'nh_deterministic_qsort','prototype':public['nh_deterministic_qsort'],'sourceHelper':'teleport_insight_qsort','callback':'vanqsort_cmp','callbackSignature':'ipp'},'layout':layout,'schema':schema,'bits':bits,'storageSizes':storage,'formats':formats,'assertion':{'expression':assertion[1],'line':source[:assertion.start()].count('\n')+1,'function':'status_enlightenment'},'windows':windows,'public':{name:public[name]for name in names if name in public},'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(set(headers+[tree/'src/insight.c']))}}
(root/'js/standalone/insight-abi.json').write_text(json.dumps(result,indent=2)+'\n');print('Bound original INSIGHT '+str(len(names))+' source functions/'+str(len(result['public']))+' public entries; shared globals,35packed fields, original storage and10format sites.')
