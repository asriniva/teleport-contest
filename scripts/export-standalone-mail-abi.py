#!/usr/bin/env python3
"""Bind MAIL transport and the actual pinned SDK identity/process failures."""
import hashlib,json,os,re
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();sdk=ref/'.cache/emsdk/upstream/emscripten';support=root/'nethack-c/wasm/tu-mail-support.inc';library=root/'nethack-c/wasm/tu-libraries/mail.js';s=support.read_text();lib=library.read_text()
stubs=sdk/'system/lib/libc/emscripten_libc_stubs.c';wasi=sdk/'cache/sysroot/include/wasi/api.h';errnoHeader=sdk/'cache/sysroot/include/bits/errno.h';st=stubs.read_text();eh=errnoHeader.read_text();wh=wasi.read_text()
def errno(name):
 macro=re.search(r'#define\s+'+name+r'\s+(\w+)',eh)[1]
 return int(re.search(r'#define\s+'+macro+r'\s+\(UINT16_C\((\d+)\)\)',wh)[1])
failures={}
for name,function in [('getpwuid','getpwuid'),('fork','fork'),('execl','execve')]:
 body=re.search(r'\b'+function+r'\([^)]*\)\s*\{(.*?)\n\}',st,re.S)[1]
 error=re.search(r'errno = (\w+);',body)[1];result=int(re.search(r'return (-?\d+);',body)[1]);failures[name]={'errno':errno(error),'result':result,'sourceFunction':function}
lines=[int(n)for n in re.search(r'static const int lines\[\]=\{([^}]+)\}',s)[1].split(',')];callers=json.loads('['+re.search(r'static const char \*const callers\[\]=\{([^}]+)\}',s)[1]+']')
calls={}
def splitargs(text):
 out=[];depth=0;start=0
 for i,c in enumerate(text):
  if c=='(':depth+=1
  elif c==')':depth-=1
  elif c==',' and depth==0:out.append(text[start:i]);start=i+1
 if text:out.append(text[start:])
 return out
for name,params,expression in re.findall(r'^\s+(\w+):\(([^)]*)\)=>([^\n]+)',lib,re.M):
 expression=expression.rstrip(',')
 if expression.startswith('Number('):expression=expression[7:-1]
 match=re.fullmatch(r'_(\w+)\((.*)\)',expression)
 if not match:continue
 target,args=match.groups()
 if target.startswith('teleport_mail_'):target={'teleport_mail_stat':'stat','teleport_mail_getuid':'getuid','teleport_mail_getpwuid':'getpwuid','teleport_mail_execl':'execl','teleport_mail_free':'free'}.get(target)
 if not target:continue
 params=params.split(',')if params else[];args=splitargs(args);convs=[]
 for i,arg in enumerate(args):
  v=params[i]
  if arg=='Number('+v+')|0':conv='int'
  elif arg=='Number('+v+')>>>0':conv='uint'
  else:
   m=re.fullmatch(r'(\w+)\('+v+r'\)',arg)
   if not m:raise ValueError('Review MAIL native argument '+name+':'+arg)
   conv=m[1]
  if conv not in ['pointer','text','int','uint','byte','coord']:raise ValueError('Review MAIL conversion '+conv)
  convs.append(conv)
 if len(params)!=len(convs):raise ValueError('Review MAIL argument count '+name)
 if target:calls[name]={'target':target,'arguments':convs}
records=root/'js/standalone/records.json';vision=json.loads(records.read_text())['records']['instance_globals_v']['fields'];layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['mail'];rowPointers=[]
for name,key in [('viz_rmin','rmin'),('viz_rmax','rmax')]:
 field=vision[name]
 if field['ctype']!='coordxy * '+name or field['offset']!=layout[key] or layout['coord_x_size']!=2:raise ValueError('Review MAIL vision row pointer '+name)
 rowPointers.append({'name':name,'offset':field['offset'],'elementSize':layout['coord_x_size']})
paths=[Path(__file__).resolve(),support,library,root/'js/ported/mail.js',root/'js/ported/mail-runtime.js',root/'js/wasm/tu-layouts.json',root/'js/standalone/public-functions.json',records]
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
sdkSources=[sdk/'system/lib/libc/musl/src/string'/name for name in ['strlen.c','strcat.c','strcpy.c','stpcpy.c']]
data={'rngSites':[{'line':line,'function':fn}for line,fn in zip(lines,callers)],'rowPointers':rowPointers,'calls':calls,'sdkFailures':failures,'nullCStringProfile':'MAIL only: observed memory64 compiled-C null dereference/linear-memory reads without SAFE_HEAP; scan actual heap at address zero, never synthesize passwd identity.','sourceSha256':{str(p.relative_to(root)):sha(p)for p in paths},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in [stubs,wasi,errnoHeader,*sdkSources]}}
(root/'js/standalone/mail-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound MAIL services and actual SDK failure boundaries.')
