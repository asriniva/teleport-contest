"""Readable actual-configured TOPL bodies; comments/formals/order retained."""
from pathlib import Path
import ast,json,re,os,subprocess
r=Path(__file__).resolve().parents[5];tools=Path(__file__).resolve().parent
scratch=Path(os.environ.get('TOPL_GUARD_OUTPUT',str(r/'.cache/tu-probes/topl-guard')));scratch.mkdir(parents=True,exist_ok=True)
w=r/'.cache/topl-author';src=(r/'.cache/wasm64-build/tree/win/tty/topl.c').read_text();F=json.loads((w/'functions.json').read_text());names=[f['name']for f in F];macroset=set(re.findall(r'^#define (\w+)',(w/'macros.txt').read_text(),re.M))
def group(t,at,op='(',cl=')'):
 d=1;at+=1
 while d:d+=(t[at]==op)-(t[at]==cl);at+=1
 return at
# Actual CPP __LINE__ for a multiline macro is not inferred from its opener.
origins={}
def assertion_origin(n):
 if n.get('kind')=='CallExpr':
  callee=n['inner'][0]
  while callee.get('inner'):callee=callee['inner'][0]
  if callee.get('referencedDecl',{}).get('name')=='nhassert_failed':
   values=[]
   def literals(c):
    if c.get('kind')in['StringLiteral','IntegerLiteral']:values.append(c['value'])
    for child in c.get('inner',[]):literals(child)
   for c in n['inner'][1:]:literals(c)
   expression,file,line=ast.literal_eval(values[0]),ast.literal_eval(values[1]),int(values[2]);origins[expression]={'file':file,'line':line}
 for c in n.get('inner',[]):assertion_origin(c)
for f in F:assertion_origin(f)
(scratch/'assert-origins.json').write_text(json.dumps(origins,indent=2)+'\n')
# Carry actual source nhassert token spelling/file/line before removing directives.
for m in list(re.finditer(r'\bnhassert\(',src))[::-1]:
 end=group(src,m.end()-1);expr=src[m.end():end-1];line=origins[' '.join(expr.split())]['line'];assert origins[' '.join(expr.split())]['file']=='../win/tty/topl.c'
 src=src[:m.start()]+'toplAssert('+json.dumps(' '.join(expr.split()))+', '+str(line)+', '+expr+')'+src[end:]
comments=[]
def note(m):comments.append(m[0]);return '/*TOPL_COMMENT_'+str(len(comments)-1)+'*/'
s=re.sub(r'/\*.*?\*/',note,src,flags=re.S);stack=[True];out=[]
for line in s.splitlines(True):
 if(m:=re.match(r'\s*#(ifdef|ifndef)\s+(\w+)',line)):stack.append(stack[-1]and((m[2]in macroset)==(m[1]=='ifdef')))
 elif re.match(r'\s*#endif',line):stack.pop()
 elif re.match(r'\s*#else',line):raise AssertionError('Review new TOPL source conditional')
 elif re.match(r'\s*#',line):pass
 elif stack[-1]:out.append(line);continue
 out.extend(c+'\n'for c in re.findall(r'/\*TOPL_COMMENT_\d+\*/',line))
assert len(stack)==1;s=''.join(out)
s=re.sub(r'(?m)^static void \w+\([^;{}]*\);','',s)
s=re.sub(r'(?m)^extern char erase_char;','',s)
for f in F:
 name=f['name'];pars=[p['name']for p in f.get('inner',[])if p.get('kind')=='ParmVarDecl']
 m=re.search(r'(?m)^(?:static\s+)?(?:int|void|char\s*\*?)\s*\n?'+name+r'\([^{}]*?\)\s*',s);assert m,name
 notes=''.join(re.findall(r'/\*TOPL_COMMENT_\d+\*/',m[0]));s=s[:m.start()]+notes+'\nexport function '+name+'('+', '.join(pars)+')\n'+s[m.end():]
s=re.sub(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',lambda m:str(ord(ast.literal_eval(m[0])))if m[0].startswith("'")else m[0],s)
# Source-owned statics use actual Module-owned native typed storage, with JS-owned initial values.
s=re.sub(r'(?m)^static char \*\*snapshot_mesgs = 0;','',s)
s=re.sub(r'(?m)^\s*static int nxtidx;','',s);s=re.sub(r'(?m)^\s*static boolean initd = FALSE;','',s)
external=set(re.findall(r'^#define (\w+)',(w/'macros.txt').read_text(),re.M))|set(json.loads((w/'boundary-inventory.json').read_text())['globals'])|set(json.loads((w/'boundary-inventory.json').read_text())['foreignFunctions'])|{'nxtidx','initd','toplAssert','pointerSize'}
external-=set(names)
parts=re.split(r'(/\*TOPL_COMMENT_\d+\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\')',s)
for i in range(0,len(parts),2):
 t=parts[i].replace('->','.')
 for name,count in [('rtmp',40),('prompt',256),('respbuf',128),('digit_string',2)]:t=re.sub(r'\b'+name+r'\[(?:BUFSZ|QBUFSZ|'+str(count)+r')\](?=\s*[,;])',name+' = C.stackAlloc('+str(count)+')',t)
 t=re.sub(r'(?m)^(\s*)(?:struct WinDesc\s*\*\s*|const char\s*\*\s*|char\s*\*\s*|winid\s+|unsigned\s+|boolean\s+|int\s+|long\s+|char\s+)',r'\1let ',t)
 t=re.sub(r'(\blet [^;]*?),\s*\*',r'\1, ',t)
 t=t.replace('{ int svx', '{ let svx')
 t=re.sub(r'sizeof\(char\s*\*\)', 'C.pointerSize', t)
 t=re.sub(r'\((?:struct WinDesc\s*\*|const char\s*\*|char\s*\*\s*\*?|genericptr_t|void)\)\s*','',t)
 kinds={'int':'int','unsigned':'uint','long':'long','char':'char','short':'short'}
 while(m:=re.search(r'\((int|unsigned|long|char|short)\)\s*',t)):
  start=at=m.end()
  while t[at]in'!~+-* ':at+=1
  if t[at]=='(':at=group(t,at)
  else:
   n=re.match(r'\w+',t[at:]);assert n,t[at:];at+=len(n[0])
  while at<len(t):
   if t[at]=='.':at+=len(re.match(r'\.\w+',t[at:])[0])
   elif t[at]in'[(':at=group(t,at,t[at],']'if t[at]=='['else')')
   elif t[at:at+2]in['++','--']:at+=2
   else:break
  t=t[:m.start()]+'C.'+kinds[m[1]]+'('+t[start:at]+')'+t[at:]
 t=re.sub(r'\b(\d+)L\b',r'\1n',t)
 for a,b in [('TRUE','1'),('FALSE','0'),('NULL','0')]:t=re.sub(r'\b'+a+r'\b',b,t)
 t=re.sub(r'(?<![\w.])([A-Za-z_]\w*)(?=\()',lambda m:m[0]if m[0]in set(names)|{'if','for','while','switch','function'}else'C.'+m[0],t)
 t=re.sub(r'(?<![\w.])\b[A-Za-z_]\w*\b',lambda m:'C.'+m[0]if m[0]in external and m[0]!='C'else m[0],t)
 # A char pointer dereference is a live signed-byte reference; char* arrays are native pointer vectors.
 t=re.sub(r'(?<![\w])\*\s*(C\.gt\.toplines|str|tl|mesg|rb)(\+\+)?',lambda m:'C.byte('+m[1]+('++'if m[2]else'')+').value',t)
 t=t.replace('C.C.gt.','C.gt.').replace('C.gt.toplines[C.TBUFSZ - 1]','C.byte(C.gt.toplines+C.TBUFSZ-1).value')
 for name in ['prompt','digit_string']:
  t=re.sub(r'\b'+name+r'\[([^]]+)\]',lambda m:'C.byte('+name+'+('+m[1]+')).value',t)
 t=re.sub(r'\bC\.gt\.toplines\[([^]]+)\]',r'C.byte(C.gt.toplines+(\1)).value',t)
 parts[i]=t
s=''.join(parts)
# One original cleanup tail, shared with the source unrestricted-response path.
s=s.replace('    if (resp) {','    clean_up: {\n    if (resp) {',1).replace('goto clean_up;','break clean_up;').replace(' clean_up:\n','    }\n')
# All original source internal calls retain actual automatic C storage frames.
parts=re.split(r'(/\*TOPL_COMMENT_\d+\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\')',s)
for i in range(0,len(parts),2):
 for name in names:parts[i]=re.sub(r'(?<!function )(?<![\w.])'+name+r'\(','C.callLocal('+name+', ',parts[i]).replace('C.callLocal('+name+', )','C.callLocal('+name+')')
s=''.join(parts);s=re.sub(r'/\*TOPL_COMMENT_(\d+)\*/',lambda m:comments[int(m[1])],s)
parts=re.split(r'(/\*.*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\')',s,flags=re.S)
for i in range(1,len(parts),2):
 if parts[i].startswith('"'):parts[i]=re.sub(r'\\([0-7]{1,3})',lambda m:'\\x'+format(int(m[1],8),'02x'),parts[i])
 if parts[i].startswith("'"):v=ast.literal_eval(parts[i]);assert len(v)==1;parts[i]=str(ord(v))
s=''.join(parts);p=Path(os.environ.get('TOPL_OUTPUT',str(scratch/'regenerated-core.js')));p.write_text("import {C} from '../c-runtime/context.js';\n"+s)
print('TOPL translated bodies',len(F),'comments',len(comments))
subprocess.check_call([str(Path(os.environ.get('EMSDK',str(r/'.cache/emsdk')))/'node/24.19.0_64bit/bin/node'),str(tools/'canonical-logicals.mjs'),str(p)])

for tool in ['integer-divisions.mjs','scalar-coercions.mjs','integer-promotions.mjs']:subprocess.check_call([str(Path(os.environ.get('EMSDK',str(r/'.cache/emsdk')))/'node/24.19.0_64bit/bin/node'),str(tools/tool),str(p)])
