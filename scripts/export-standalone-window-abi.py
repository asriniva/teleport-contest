#!/usr/bin/env python3
"""Existing window adapter descriptors and original compiler callback types."""
import hashlib,json,os,re,shlex,subprocess
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree'
def declaration(file,name):
 for line in file.read_text().splitlines():
  match=re.match(r'\s*const '+re.escape(name)+r'\s*=\s*(.*);\s*$',line)
  if match:return json.loads(match[1])
 raise RuntimeError('Changed descriptor '+str(file)+':'+name)
w=root/'js/ported/windows-runtime.js';t=root/'js/ported/wintty-runtime.js'
data={'windows':{name:declaration(w,name)for name in ['fields','ptrs','longs','ulongs','globalfields','names','callbacks']},'wintty':{name:declaration(t,name)for name in ['schema','nativeReturns','dataTypes']},'callbacks':{},'enums':{}}
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+d for d in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
clang=ref/'.cache/emsdk/upstream/bin/clang';headers=set()
for module,source in [('windows',tree/'src/windows.c'),('wintty',tree/'win/tty/wintty.c')]:
 ast=json.loads(subprocess.check_output([str(clang),*flags,'-fsyntax-only','-Xclang','-ast-dump=json',str(source)]))
 enum_names=sorted({n['name']for n in ast['inner']if n.get('kind')=='EnumDecl'and n.get('name')and any(c.get('kind')=='EnumConstantDecl'for c in n.get('inner',[]))})
 scratch=root/'.cache/window-abi-enums';scratch.mkdir(exist_ok=True)
 probe=scratch/(module+'.c');probe.write_text('#include '+json.dumps(str(source))+'\n'+''.join('const unsigned long __standalone_enum_'+str(i)+'_size=sizeof(enum '+name+');\nconst unsigned long __standalone_enum_'+str(i)+'_signed=((enum '+name+')-1 < 0);\n'for i,name in enumerate(enum_names)))
 ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(probe)],text=True)
 for i,name in enumerate(enum_names):
  values=[int(re.search(r'@__standalone_enum_'+str(i)+'_'+field+r' = .*?constant i64 (\d+)',ir)[1])for field in ['size','signed']]
  item={'size':values[0],'signed':bool(values[1])}
  if 'enum '+name in data['enums']and data['enums']['enum '+name]!=item:raise RuntimeError('Conflicting enum '+name)
  data['enums']['enum '+name]=item
 own=set(re.findall(r'^export function (\w+)\(', (root/'js/ported'/str(module+'.js')).read_text(),re.M))
 if module=='wintty':
  data['wintty']['zeroStorage']={n['name']:n['type']['qualType']for n in ast['inner']if n.get('kind')=='VarDecl'and n.get('name')in data['wintty']['schema']['globals']and n.get('storageClass')!='extern'and not n.get('init')and not n.get('loc',{}).get('includedFrom')}
 data['callbacks'][module]={n['name']:{'result':n['type']['qualType'].split('(',1)[0].strip(),'parameters':[p['type']['qualType']for p in n.get('inner',[])if p['kind']=='ParmVarDecl']}for n in ast['inner']if n.get('kind')=='FunctionDecl'and n.get('name')in own and any(c['kind']=='CompoundStmt'for c in n.get('inner',[]))}
 deps=subprocess.check_output([str(clang),*flags,'-M',str(source)],text=True);headers.update(Path(p).resolve()for p in shlex.split(deps.split(':',1)[1].replace('\\\n','')))
layouts=subprocess.check_output([str(clang),*flags,'-fsyntax-only','-Xclang','-fdump-record-layouts-complete',str(tree/'src/windows.c')],text=True)
blocks=[b for b in layouts.split('*** Dumping AST Record Layout')[1:]if re.match(r'\s*0 \| struct win_choices\s*\n',b)]
if len(blocks)!=1:raise RuntimeError('Review private win_choices layout')
block=blocks[0];end=re.search(r'\[sizeof=(\d+), align=(\d+)\]',block);fields={}
for line in block.splitlines()[1:]:
 match=re.match(r'\s*(\d+) \|   (\S.*)$',line)
 if match:
  name=re.search(r'\b(\w+)$',match[2]);fields[name[1]]={'offset':int(match[1]),'ctype':match[2]}
data['records']={'win_choices':{'size':int(end[1]),'alignment':int(end[2]),'fields':fields}}
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
paths=[w,t,root/'js/standalone/window-system.js',root/'nethack-c/wasm/tu-libraries/windows.js',Path(__file__).resolve(),root/'nethack-c/wasm/compile-defines.json',root/'nethack-c/wasm/tu-fragments/windows-support.c',root/'nethack-c/wasm/tu-wintty-support.inc']
data['sourceSha256']={str(p.relative_to(root)):sha(p)for p in paths};data['referenceHeaderSha256']={str(p.relative_to(ref)):sha(p)for p in sorted(headers)}
(root/'js/standalone/window-abi.json').write_text(json.dumps(data,indent=2)+'\n')
print('Exported original WINDOWS/WINTTY descriptors and callback prototypes.')
