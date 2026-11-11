#!/usr/bin/env python3
"""Bind optional interactions to original transports and measured C layouts."""
import hashlib,json,os,re,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';ports=['rumors','fountain','sit','music','write'];support=root/'nethack-c/wasm/tu-support.c';native=support.read_text();frozen=json.loads((root/'js/wasm/tu-layouts.json').read_text());public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions'];clang=ref/'.cache/emsdk/upstream/bin/clang'
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
def braces(text,start):
 depth=0;quote=None;escape=False
 for i in range(start,len(text)):
  c=text[i]
  if quote:
   if escape:escape=False
   elif c=='\\':escape=True
   elif c==quote:quote=None
  elif c in "\"'`":quote=c
  elif c=='{':depth+=1
  elif c=='}':
   depth-=1
   if depth==0:return i
 raise ValueError('Unclosed block')
def function(name):
 m=re.search(r'\b'+name+r'\s*\([^;{}]*\)\s*\{',native);assert m,name;start=native.index('{',m.start());return native[start+1:braces(native,start)]
result={};generated=[];inputs=[Path(__file__).resolve(),root/'scripts/test-standalone-special-interactions.mjs',root/'scripts/check-standalone-special-interactions.mjs',support,root/'js/ported/wasm-runtime.js',root/'js/standalone/special-interactions.js',root/'js/standalone/vision.js',root/'js/wasm/tu-layouts.json',root/'nethack-c/wasm/compile-defines.json',root/'js/standalone/public-functions.json'];headers=set()
with tempfile.TemporaryDirectory(prefix='special-interaction-layout-')as tmp:
 for port in ports:
  header=root/('scripts/tu-'+port+'-layout.h');probe=Path(tmp)/(port+'.c');body='#include '+json.dumps(str(header))+'\n';probe.write_text(body)
  expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(probe)],text=True);table=re.search(port+r'_layout\[\]\s*=\s*\{(.*?)\n\};',expanded,re.S);assert table,port
  rows=re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}',table[1],re.S);assert rows
  probe.write_text(body+'\n'.join('const unsigned long interaction_'+str(i)+'=('+expr+');'for i,(_,expr)in enumerate(rows)))
  ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(probe)],text=True)
  measured={key:int(re.search(r'@interaction_'+str(i)+r' = .*?constant i64 (-?\d+)',ir)[1])&((1<<64)-1)for i,(key,_)in enumerate(rows)}
  assert set(frozen[port])-set(measured)<={'size','strings'},(port,set(frozen[port])-set(measured))
  if 'strings' in frozen[port]:
   macros=subprocess.check_output([str(clang),*flags,'-E','-dM',str(probe)],text=True)
   for name,value in frozen[port]['strings'].items():assert json.loads(re.search(r'^#define '+name+r' (\"[^\"]*\")$',macros,re.M)[1])==value,name
  assert all((int(frozen[port][key])&((1<<64)-1))==value for key,value in measured.items()),port
  globals_body=function('teleport_'+port+'_global');roots=[]
  for i,expr in re.findall(r'case (\d+):\s*return ([^;]+);',globals_body):
   assert int(i)==len(roots);roots.append(re.sub(r'\([^)]*\)|[&\s]','',expr))
  roots.append(re.sub(r'\([^)]*\)|[&\s]','',re.search(r'default:\s*return ([^;]+);',globals_body)[1]));assert all(re.fullmatch(r'\w+',s)for s in roots)
  macros=subprocess.check_output([str(clang),*flags,'-E','-dM',str(probe)],text=True)
  aliases={key:re.search(r'^#define '+key+r' (\w+)$',macros,re.M)[1]for key in ['doormask','looted','blessedftn']if re.search(r'^#define '+key+r' (\w+)$',macros,re.M)}
  source=root/('js/ported/'+port+'.js');runtime=root/('js/ported/'+port+'-runtime.js');library=root/('nethack-c/wasm/tu-libraries/'+port+'.js');inputs += [header,source,runtime,library]
  names=re.findall(r'^export function (\w+)',source.read_text(),re.M)
  callers=re.search(r'teleport_'+port+r'_callers\[\]\s*=\s*\{([^}]+)\}',native,re.S)
  result[port]={'fieldAliases':aliases,'globals':roots,'public':{name:public[name]for name in names if name in public},'layout':frozen[port],'callers':re.findall(r'"([^"]+)"',callers[1])if callers else ['dowrite']}
  text=library.read_text();foreign=set(re.findall(r'\b_([A-Za-z]\w*)\s*\(',text));result[port]['foreign']={name:public[name]for name in sorted(foreign)if name in public};start=re.search(r'\$teleport'+port.capitalize()+r'Services:\s*function\(\)\s*\{',text);assert start,port;at=text.index('{',start.start());factory=text[at+1:braces(text,at)]
  factory=re.sub(r'\s*var (state|cache) = Module\[[^\n]+\n','\n',factory,count=1)
  literal=re.search(r'var literal\s*=\s*\w+\s*=>\s*\{',factory);assert literal,port;la=factory.index('{',literal.start());end=braces(factory,la);factory=factory[:literal.start()]+'var literal=value=>environment.services.literal(value);'+factory[end+2:]
  factory=factory.replace('moduleKey: state','moduleKey: environment').replace('moduleKey: cache','moduleKey: environment').replace('HEAPU8','environment.memory.HEAPU8')
  factory=re.sub(r'\b_([A-Za-z]\w*)\s*\(',r'native.\1(',factory)
  factory=re.sub(r'\bstackAlloc\(',r'environment.transport.stackAlloc(',factory)
  factory=re.sub(r'\bstackSave\(\)',r'environment.transport.stackSave()',factory);factory=re.sub(r'\bstackRestore\(',r'environment.transport.stackRestore(',factory)
  assert not re.search(r'\b(Module|WebAssembly|HEAPU8)\b',factory.replace('environment.memory.HEAPU8','')),port
  generated.append('export function create'+port.capitalize()+'Services(environment,native){'+factory+'\n}\n')
  deps=subprocess.check_output([str(clang),*flags,'-M',str(probe)],text=True)
  import shlex
  headers.update(Path(p).resolve()for p in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(p).resolve().is_relative_to(ref))
# The following contains ABI wrappers only, derived mechanically from existing factories.
generated_path=root/'js/standalone/special-interaction-services.js';generated_path.write_text('// Generated ABI wrappers; no Wasm calls or game policy. Regenerate with export-standalone-special-interactions.py.\n'+''.join(generated));inputs.append(generated_path)
headers.add(tree/'src/rumors.c');rumor_source=(tree/'src/rumors.c').read_text();assertions={}
for name,expr,fn in [('assert','CapMons != 0','CapitalMon'),('nhassert','filechunksize <= INT_MAX','get_rnd_line')]:
 match=re.search(r'\b'+name+r'\('+re.escape(expr)+r'\);',rumor_source);assert match
 assertions[name]={'expression':expr,'file':'rumors.c','line':rumor_source[:match.start()].count('\n')+1,'function':fn}
name_source=tree/'src/do_name.c';headers.add(name_source);bogon_codes=json.loads(re.search(r'const char bogon_codes\[\] = ("[^"]*")',name_source.read_text())[1])
common={name:dict(zip(['owner','field'],re.search(r'^#define '+name+r' (\w+)\.(\w+)$',macros,re.M).groups()))for name in ['Never_mind','NH_BLACK','something','nothing_seems_to_happen']}
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();data={'ports':result,'commonStrings':common,'assertions':assertions,'bogonCodes':bogon_codes,'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(headers)}}
(root/'js/standalone/special-interactions-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Measured five original layouts and bound original global/caller maps and ABI factories.')
