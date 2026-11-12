#!/usr/bin/env python3
"""Bind full EAT transport to native maps and unchanged runtime schemas."""
import hashlib,json,os,re
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve()
support=root/'nethack-c/wasm/tu-eat-support.inc';library=root/'nethack-c/wasm/tu-libraries/eat.js';runtime=root/'js/nethack/bindings/eat.js'
s=support.read_text();lib=library.read_text();rt=runtime.read_text();dec=json.JSONDecoder()
schema=dec.raw_decode(rt.split('const schema=',1)[1])[0]
def indexed(pattern,text):
 rows=[(int(i),v)for i,v in re.findall(pattern,text)]
 if [i for i,_ in rows]!=list(range(len(rows))):raise ValueError('Review native map')
 return [v for _,v in rows]
def body(name):return s.split(name,1)[1].split('\n',1)[0]
globals=indexed(r'case (\d+):return (?:\(void\*\))?&?(\w+);',body('void*teleport_eat_global(int i)'))
equipment=indexed(r'case (\d+):return (\w+);',body('struct obj*teleport_eat_equipment(int i)'))
common=indexed(r'case (\d+):return ((?:\(const char\*\))?\w+);',body('const char*teleport_eat_common(int i)'))
colors=indexed(r'case (\d+):return (\w+);',body('const char*teleport_eat_color(int i)'))
bitbody=s.split('unsigned teleport_eat_bit',1)[1].split('void teleport_eat_set_bit',1)[0]
bits={}
for typ,fields in re.findall(r'case \d+:\{(struct \w+)\*o=ptr;switch\(i\)\{(.*?)default:',bitbody):bits[typ]=indexed(r'case (\d+):return o->(\w+);',fields)
bitkeys=json.loads(re.search(r'bittypes=(\[[^;]+?\]);',lib)[1]);bittypes=re.findall(r'case \d+:\{(struct \w+)\*o=ptr;',bitbody)
if len(bitkeys)!=len(bittypes) or len(globals)!=26:raise ValueError('Review EAT map sizes')
header=ref/'.cache/wasm64-build/tree/include/decl.h';h=header.read_text()
def commonfield(name):
 name=re.sub(r'^\(const char\*\)','',name)
 return re.search(r'#define\s+'+name+r'\s+c_common_strings\.(\w+)',h)[1] if name not in ['ynchars','ynqchars'] else name
calls={}
for name,params,expression in re.findall(r'^(\w+):\(([^)]*)\)=>([^\n]+)',lib,re.M):
 expression=expression.rstrip(',')
 if expression.startswith('Number('):expression=expression[7:-1]
 match=re.fullmatch(r'_(\w+)\((.*)\)',expression)
 if not match:continue
 target,args=match.groups()
 if target.startswith('teleport_'):continue
 if name!=target:raise ValueError('Review EAT native alias '+name)
 params=params.split(',')if params else[];converters=[]
 for i,arg in enumerate(re.findall(r'(\w+)\((a\d+)\)',args)):
  conv,param=arg
  if param!=params[i] or conv not in ['pointer','text','int','uint','byte','ubyte','short','long','ulong']:raise ValueError('Review EAT native argument')
  converters.append(conv)
 if len(converters)!=len(params):raise ValueError('Review EAT native call '+name)
 calls[name]=converters
lines=json.loads(re.search(r'teleport_eat_format_lines\[\]=(\[[^;]+\])',s.replace('{','[').replace('}',']'))[1])
functions=json.loads(re.search(r'teleport_eat_format_functions\[\]=(\[[^;]+\])',s.replace('{','[').replace('}',']'))[1])
paths=[Path(__file__).resolve(),support,library,runtime,root/'js/ported/eat.js',root/'js/standalone/public-functions.json',root/'js/wasm/tu-layouts.json']
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
data={'globals':globals,'equipment':equipment,'bits':{k:{'type':t,'fields':bits[t]}for k,t in zip(bitkeys,bittypes)},'commonFields':[commonfield(n)for n in common],'colorFields':[re.search(r'#define\s+'+n+r'\s+c_color_names\.(\w+)',h)[1]for n in colors],'calls':calls,'formatSites':[{'function':f,'line':l}for f,l in zip(functions,lines)],'callbacks':['eatmdone','eatfood','opentin','unfaint','Hear_again','Finish_digestion'],'getobjCallbacks':['tinopen_ok','eat_ok','offer_ok','tin_ok'],'shapes':json.loads(re.search(r'var shapes=(\[[^;]+?\]),callers=',lib)[1]),'sourceSha256':{str(p.relative_to(root)):sha(p)for p in paths},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in [header,ref/'.cache/wasm64-build/tree/include/hack.h']}}
(root/'js/standalone/eat-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound full EAT native storage, fields and typed calls.')
