#!/usr/bin/env python3
"""Measure unchanged REGION headers and bind the original native service maps."""
import hashlib,json,re,subprocess,tempfile,shlex
from pathlib import Path
root=Path(__file__).resolve().parents[1];tree=root/'.cache/wasm64-build/tree';clang=root/'.cache/emsdk/upstream/bin/clang';header=root/'scripts/tu-region-layout.h';support=root/'nethack-c/wasm/tu-region-support.inc';library=root/'nethack-c/wasm/tu-libraries/region.js'
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(root/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(root/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(root/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
with tempfile.TemporaryDirectory(prefix='standalone-region-abi-')as scratch:
 p=Path(scratch)/'probe.c';p.write_text('#include '+json.dumps(str(header))+'\n');expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(p)],text=True);body=re.search(r'teleport_region_layout\[\]\s*=\s*\{(.*?)\n\};',expanded,re.S)[1];rows=re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}',body,re.S)
 p.write_text(expanded+'\n'+'\n'.join('const long long probe_rg_'+str(i)+'=('+expr+');'for i,(_,expr)in enumerate(rows))+'\nconst long long probe_rg_context=sizeof(NhRegion);');ir=subprocess.check_output([str(clang),*flags[:2],'-x','cpp-output','-S','-emit-llvm','-O0','-o','-',str(p)],text=True);layout={name:int(re.search(r'@probe_rg_'+str(i)+r' = .*?constant i64 (-?\d+)',ir)[1])for i,(name,_)in enumerate(rows)}
 layout['size']=int(re.search(r'@probe_rg_context = .*?constant i64 (-?\d+)',ir)[1])
 expected=json.loads((root/'js/wasm/tu-layouts.json').read_text())['region'];assert layout==expected,('Changed native REGION layout',{k:(v,expected.get(k))for k,v in layout.items()if expected.get(k)!=v},sorted(set(expected)-set(layout)))
 p.write_text('#include '+json.dumps(str(support))+'\n');native=subprocess.check_output([str(clang),*flags,'-E','-P',str(p)],text=True);deps=subprocess.check_output([str(clang),*flags,'-M',str(p)],text=True);headers=[Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(root)]
public=json.loads((root/'js/nethack/public-functions.json').read_text())['functions'];calls={}
def split(s):
 out=[];depth=0;start=0
 for i,c in enumerate(s):
  if c=='(':depth+=1
  elif c==')':depth-=1
  elif c==','and depth==0:out.append(s[start:i]);start=i+1
 if s:out.append(s[start:])
 return out
for line in library.read_text().splitlines():
 m=re.match(r'(\w+):\(([^)]*)\)=>(Number\()?_(\w+)\((.*)',line)
 if not m or m[4].startswith('teleport_region_'):continue
 name,params,number,target,args=m.groups();assert target in public,target;assert args.endswith(')),')if number else args.endswith('),');args=args[:-(3 if number else 2)];params=params.split(',');coercions=[]
 for arg in split(args):
  arg=arg.strip();found=None
  for i,param in enumerate(params):
   for kind,pattern in [('pointer','ptr('+param+')'),('text','text('+param+')'),('long','BigInt('+param+')'),('char','byte('+param+')'),('short','narrow('+param+')'),('int',param+'|0'),('uint',param+'>>>0')]:
    if arg==pattern:found=[kind,i]
  assert found,(name,arg);coercions.append(found)
 calls[name]={'target':target,'number':bool(number),'coercions':coercions,'prototype':public[target]}
sf={}
for method,target in re.findall(r'void teleport_region_(sf[io]_\w+)\([^)]*\)\s*\{\s*(\w+)\(f,\s*p,\s*s(?:,\s*n)?\);+\s*\}',native):sf[method]=target
assert all(target in public for target in sf.values());assert len(sf)==16,(len(sf),re.findall(r'void teleport_region_sf[io]_long[^}]+}',native))
native_support=support.read_text();globals=[name for _,name in re.findall(r'case (\d+):return (?:\(void\*\))?&?(\w+);',native_support.split('teleport_region_global',1)[1].split('return 0;',1)[0])];assert len(globals)==14
assert 'caller==0?"inside_gas_cloud":caller==1?"create_gas_cloud":"region_safety"'in native_support
messages={int(i):name for i,name in re.findall(r'case (\d+):(\w+)\(fmt,a,b\);',native_support)};assert len(messages)==6
paths=[Path(__file__).resolve(),header,support,library,root/'js/nethack/region-services.js',root/'js/nethack/level-startup.js',root/'js/ported/region.js',root/'js/nethack/bindings/region.js',root/'js/nethack/records.json',root/'js/nethack/public-functions.json',root/'js/wasm/tu-layouts.json'];sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
policyNames=re.findall(r'^export function (\w+)\(', (root/'js/ported/region.js').read_text(),re.M)
data={'layout':layout,'globals':globals,'calls':calls,'sf':sf,'messages':messages,'rngCallers':['inside_gas_cloud','create_gas_cloud','region_safety'],'monsterBits':['mcansee','mblinded'],'heroBits':['uswallow','uinwater'],'public':{n:public[n]for n in policyNames if n in public},'sourceSha256':{str(p.relative_to(root)):sha(p)for p in paths},'referenceHeaderSha256':{str(p.relative_to(root)):sha(p)for p in sorted(set(headers+[tree/'src/region.c']))}}
(root/'js/nethack/region-services-abi.json').write_text(json.dumps(data,indent=2)+'\n');print(f'Bound REGION: {len(layout)} native values/{len(calls)} foreign calls/{len(sf)} SF aliases')
