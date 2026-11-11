from pathlib import Path
import json,re,ast
import argparse
parser=argparse.ArgumentParser();parser.add_argument('--out',required=True,type=Path);parser.add_argument('--source-root',type=Path);args=parser.parse_args();code_root=Path(__file__).resolve().parents[1];w=args.out.resolve();r=(args.source_root or code_root).resolve();src=(r/'nethack-c/upstream/util/sfexpasc.c').read_text();root=json.loads((w/'compiler-ast.json').read_text());infos=json.loads((w/'configured-functions.json').read_text());names={x['name']:x['name']for x in infos};tables=set();globals=set();nodes=[];decls={};sizes=set();fields=set();calls=set();staticbufs={};cells=set();localids=set()
def walk(n):
 yield n
 for x in n.get('inner',[]):yield from walk(x)
def loc(n,end=False):
 p=n.get('range',{}).get('end'if end else'begin',{});p=p.get('expansionLoc',p);return p.get('offset',0)+(p.get('tokLen',0)if end else 0)
def owner(n):
 l=n.get('loc',{});l=l.get('expansionLoc',l);o=l.get('offset',-1);return not l.get('includedFrom')and 0<=o<len(src)and (n.get('name') in names or n.get('kind')=='VarDecl')
for n in root['inner']:
 if n.get('kind')=='FunctionDecl'and n.get('name')in names and any(x.get('kind')=='CompoundStmt'for x in n.get('inner',[]))and owner(n):nodes.append(n)
 if n.get('kind')=='VarDecl'and owner(n):globals.add(n['name']);decls[n['id']]=n
for f in nodes:
 for n in walk(f):
  if n.get('kind')in['VarDecl','ParmVarDecl']:decls[n['id']]=n;localids.add(n['id'])
  if n.get('kind')=='UnaryOperator'and n.get('opcode')=='&':
   z=n['inner'][0]
   while z.get('kind')=='ParenExpr':z=z['inner'][0]
   if z.get('kind')=='DeclRefExpr'and z['referencedDecl']['id']in decls:cells.add(z['referencedDecl']['id'])
# All original static scalar cells are per actual Module, initialized once.
for fn in nodes:
 for node in walk(fn):
  if node.get('kind')=='VarDecl' and node.get('storageClass')=='static' and '['not in node['type']['qualType']:cells.add(node['id'])

def typ(n):return n.get('type',{}).get('desugaredQualType',n.get('type',{}).get('qualType','int'))
def fmt(t):
 t=re.sub(r'\b(?:const|volatile|restrict)\s*','',t).strip()
 node=next((x for x in root['inner']if x.get('kind')=='TypedefDecl'and x.get('name')==t),None)
 if node:t=node['type'].get('desugaredQualType',node['type']['qualType'])
 if '*'in t:return'Pointer'
 if t in ['boolean','signed char','schar','xint8','char']:return'Int8'
 if t in ['unsigned char','uchar','uint8_t']:return'Uint8'
 if t in ['short','short int','int16_t','coordxy','xint16']:return'Int16'
 if t in ['unsigned short','uint16_t']:return'Uint16'
 if t in ['long','long long','time_t','int64_t']:return'BigInt64'
 if t in ['unsigned long','unsigned long long','size_t','uint64_t']:return'BigUint64'
 return'Uint32'if'unsigned'in t or t=='uint'else'Int32'
def size(t):
 t=re.sub(r'^const ','',t)
 for node in root['inner']:
  if node.get('kind')=='TypedefDecl':
   alias=node['name'];target=node['type'].get('desugaredQualType',node['type']['qualType']);t=re.sub(r'\b'+alias+r'\b',lambda m:target,t)
 m=re.match(r'(.*?)\[(\d+)\]$',t)
 if m:return'('+size(m[1])+' * '+m[2]+')'
 if'*'in t:return'8'
 f=fmt(t)
 if t.startswith('struct ')or t.startswith('union '):sizes.add(t);return'C.sizes['+json.dumps(t)+']'
 return str({'Int8':1,'Uint8':1,'Int16':2,'Uint16':2,'Int32':4,'Uint32':4,'BigInt64':8,'BigUint64':8}[f])
def narrow(t,x):
 if'*'in t or'['in t or t.startswith('struct '):return x
 return'C.cast('+json.dumps(fmt(t))+', '+x+')'
def name(n):return n+'_ 'if n in['in','out','var','let','const','new','class','default']else n
# No reserved identifiers occur in this configured source.
def ref(n):
 d=n['referencedDecl'];i=d['id'];v=d['name'];v=names.get(v,v)
 if d['kind']=='FunctionDecl':return v if v in names.values()else'C.'+v
 a='C.'+v if i not in localids else v
 return a+'.value'if i in cells else a

def unwrap(n):
 while n.get('kind')in['ParenExpr','ImplicitCastExpr','CStyleCastExpr']and n.get('inner'):n=n['inner'][0]
 return n

def address(n):
 u=unwrap(n);k=u.get('kind')
 if k=='DeclRefExpr':
  d=u['referencedDecl'];v=('C.'if d['id']not in localids else'')+d['name'];return v+'.address'if d['id']in cells else v
 if k=='UnaryOperator'and u['opcode']=='*':return e(u['inner'][0])
 if k=='ArraySubscriptExpr':return arrayaddr(u)
 if k=='MemberExpr':
  base=u['inner'][0];t=typ(base).replace(' *','').replace('*','');fields.add((t,u['name']));return'C.fieldAddress('+e(base)+', '+json.dumps(t)+', '+json.dumps(u['name'])+')'
 raise Exception(('address',k))
def arrayaddr(n):
 b,i=n['inner'];return'('+e(b)+' + Number('+e(i)+') * '+size(typ(n))+')'
def istable(n):
 u=unwrap(n)
 return u.get('kind')=='DeclRefExpr'and u['referencedDecl']['name']in tables

def assign(n,v):
 u=unwrap(n);k=u.get('kind');t=typ(u);v=narrow(t,v)
 if k=='UnaryOperator'and u['opcode']=='*':return'C.store('+json.dumps(fmt(t))+', '+e(u['inner'][0])+', '+v+')'
 if t.startswith('struct ')and'*'not in t:return'C.copy('+address(u)+', '+evalue(v)+', '+size(t)+')'
 if k=='ArraySubscriptExpr'and not istable(u['inner'][0]):return'C.store('+json.dumps(fmt(t))+', '+arrayaddr(u)+', '+v+')'
 return'('+e(u)+' = '+v+')'
def evalue(x):return x

def e(n):
 k=n.get('kind');a=n.get('inner',[]);t=typ(n)
 if not k:return''
 if k in['ParenExpr','ConstantExpr','ExprWithCleanups']:return'('+e(a[0])+')'
 if k in['ImplicitCastExpr','CStyleCastExpr']:
  x=e(a[0]);ck=n.get('castKind');return narrow(t,x)if ck in['IntegralCast','IntegralToBoolean','BooleanToSignedIntegral']else x
 if k=='IntegerLiteral':return n['value']+('n'if fmt(t)in['BigInt64','BigUint64']else'')
 if k=='CharacterLiteral':return str(n['value'])
 if k=='StringLiteral':
  p=n['range']['begin'];q=n['range']['end'];p=p.get('spellingLoc',p);q=q.get('spellingLoc',q);raw=src[p.get('offset',0):q.get('offset',0)+q.get('tokLen',0)]
  try:v=''.join(ast.literal_eval(z)for z in re.findall(r'"(?:\\.|[^"\\])*"',raw));assert raw.lstrip().startswith('"')
  except:v=json.loads(n['value'])
  return'C.literal('+json.dumps(v)+')'
 if k=='PredefinedExpr':return'C.literal('+json.dumps(current)+')'
 if k=='DeclRefExpr':return ref(n)
 if k=='MemberExpr':
  base=a[0];u=unwrap(base)
  if u.get('kind')=='DeclRefExpr' and u['referencedDecl'].get('name')in['GifScreen','Gif89']:return e(base)+'.'+n['name']
  if u.get('kind')=='ArraySubscriptExpr'and istable(u['inner'][0]):return e(base)+'.'+n['name']
  bt=typ(base).replace(' *','').replace('*','');fields.add((bt,n['name']));return'C.record('+e(base)+', '+json.dumps(bt)+').'+n['name']
 if k=='ArraySubscriptExpr':
  if istable(a[0]):return e(a[0])+'[Number('+e(a[1])+')]'
  ad=arrayaddr(n)
  if '['in t or t.startswith('struct '):return ad
  return'C.load('+json.dumps(fmt(t))+', '+ad+')'
 if k=='UnaryExprOrTypeTraitExpr':
  tt=n.get('argType',{}).get('desugaredQualType',n.get('argType',{}).get('qualType'))or typ(a[0]);return'BigInt('+size(tt)+')'
 if k=='UnaryOperator':
  op=n['opcode'];x=e(a[0]);u=unwrap(a[0])
  if op=='&':return address(a[0])
  if op=='*':
   if t.startswith('struct ')or'['in t:return x
   return'C.load('+json.dumps(fmt(t))+', '+x+')'
  if op in['++','--']:
   delta=size(typ(a[0]).rsplit('*',1)[0].strip())if'*'in typ(a[0])else('1n'if fmt(typ(a[0]))in['BigInt64','BigUint64']else'1')
   if u.get('kind')in['DeclRefExpr','MemberExpr']:
    if delta in['1','1n']:return('('+x+op+')'if n.get('isPostfix')else'('+op+x+')')
    value='('+x+(' += 'if op=='++'else' -= ')+delta+')'
    return'('+value+(' - 'if op=='++'else' + ')+delta+')'if n.get('isPostfix')else value
   # Dereferenced and indexed scalar updates retain postfix old result.
   return'C.update('+json.dumps(fmt(typ(a[0])))+', '+address(a[0])+', '+('1'if op=='++'else'-1')+', '+str(bool(n.get('isPostfix'))).lower()+')'
  if op=='!':return'Number(!('+x+'))'
  return'('+op+x+')'
 if k in['BinaryOperator','CompoundAssignOperator']:
  op=n['opcode'];l=e(a[0]);rr=e(a[1])
  if op=='=':return assign(a[0],rr)
  if op.endswith('=')and k=='CompoundAssignOperator':return assign(a[0],binary(op[:-1],a[0],a[1],n.get('computeResultType',{}).get('qualType',t)))
  return binary(op,a[0],a[1],t)
 if k=='ConditionalOperator':return'('+e(a[0])+' ? '+e(a[1])+' : '+e(a[2])+')'
 if k=='CallExpr':
  fn=unwrap(a[0]);nm=fn.get('referencedDecl',{}).get('name');args=[e(x)for x in a[1:]]
  if nm=='__assert_fail':return'C.assertFail('+', '.join(args)+')'
  if nm in names:
   target=names[nm];return'C.callLocal('+target+(' , '+', '.join(args)if args else'')+')'
  calls.add(nm)
  fixed={'printf':1,'fprintf':2,'sprintf':2,'snprintf':3,'nh_snprintf':5}
  if nm in fixed:
   k=fixed[nm];tail=['['+json.dumps(fmt(typ(x)))+', '+e(x)+']'for x in a[1+k:]];args=args[:k]+['C.va('+', '.join(tail)+')']
  return'C.'+nm+'('+', '.join(args)+')'
 raise Exception(('expr',k,str(n)[:150]))
def binary(op,a,b,t):
 l=e(a);rr=e(b)
 if op in['&&','||']:return'Number(!!('+l+') '+op+' !!('+rr+'))'
 if op in['==','!=','<','>','<=','>=']:return'Number('+l+' '+op+' '+rr+')'
 if op in['+','-']and'*'in typ(a)and'*'not in typ(b):return'('+l+' '+op+' Number('+rr+') * '+size(typ(a).rsplit('*',1)[0].strip())+')'
 if op=='-'and'*'in typ(a)and'*'in typ(b):return'BigInt(Math.trunc(('+l+' - '+rr+') / '+size(typ(a).rsplit('*',1)[0].strip())+'))'
 x='('+l+' '+op+' '+rr+')'
 if op=='/'and fmt(t)not in['BigInt64','BigUint64']:x='Math.trunc('+x+')'
 if fmt(t)=='BigUint64'and op in['+','-','*','/','%']:x='C.cast(\"BigUint64\", '+x+')'
 return x

comments=list(re.finditer(r'/\*[\s\S]*?\*/',src));usedcomments=set()
def before(n,indent):
 pos=loc(n);out=''
 for i,c in enumerate(comments):
  if i not in usedcomments and fstart<=c.start()<pos and c.end()<=fend:
   out+=' '*indent+c[0]+'\n';usedcomments.add(i)
 return out

def statement(n,ind=0):
 k=n.get('kind');a=n.get('inner',[]);pad=' '*ind;pre=before(n,ind)
 if k=='CompoundStmt':return pre+pad+'{\n'+''.join(statement(x,ind+4)for x in a)+pad+'}\n'
 if k=='DeclStmt':return pre+''.join(declaration(x,ind)for x in a)
 if k=='IfStmt':return pre+pad+'if ('+e(a[0])+')\n'+statement(a[1],ind+4)+(pad+'else\n'+statement(a[2],ind+4)if len(a)>2 else'')
 if k=='WhileStmt':return pre+pad+('fini: 'if current=='ReadInterleavedImage'else'')+'while ('+e(a[0])+')\n'+statement(a[1],ind+4)
 if k=='DoStmt':return pre+pad+'do\n'+statement(a[0],ind+4)+pad+'while ('+e(a[1])+');\n'
 if k=='SwitchStmt':return pre+pad+'switch ('+e(a[0])+')\n'+statement(a[1],ind)
 if k=='CaseStmt':return pre+pad+'case '+e(a[0])+':\n'+statement(a[-1],ind+4)
 if k=='DefaultStmt':return pre+pad+'default:\n'+statement(a[-1],ind+4)
 if k=='GotoStmt':return pre+pad+'break fini;\n'
 if k=='LabelStmt':return pre+statement(a[-1],ind)
 if k=='ForStmt':
  init,_,cond,inc,body=a;ii=declaration(init['inner'][0],0).strip().rstrip(';')if init.get('kind')=='DeclStmt'else e(init)
  return pre+pad+'for ('+ii+'; '+e(cond)+'; '+e(inc)+')\n'+statement(body,ind+4)
 if k=='ReturnStmt':return pre+pad+'return'+(' '+e(a[0])if a else'')+';\n'
 if k in['BreakStmt','ContinueStmt','NullStmt']:return pre+pad+{'BreakStmt':'break;','ContinueStmt':'continue;','NullStmt':';'}[k]+'\n'
 return pre+pad+e(n)+';\n'
def declaration(n,ind):
 v=n['name'];t=typ(n);a=[x for x in n.get('inner',[])if x.get('kind')not in['FullComment']];init=a[0]if a else None;pad=' '*ind
 if '['in t:
  if n.get('storageClass')=='static':staticbufs[current+'.'+v]=size(t);value='C.staticBuffer('+json.dumps(current+'.'+v)+', '+size(t)+')'
  else:value='C.stackAlloc('+size(t)+')'
  return pad+'const '+v+' = '+value+';\n'
 if n.get('storageClass')=='static' and n['id']in cells:return pad+'const '+v+' = C.staticCell('+json.dumps(current+'.'+v)+', '+json.dumps(fmt(t))+(', '+e(init)if init else'')+');\n'
 if n['id']in cells:return pad+'const '+v+' = C.cell('+json.dumps(fmt(t))+(', '+e(init)if init else'')+');\n'
 return pad+'let '+v+(' = '+narrow(t,e(init))if init else'')+';\n'
out="import {C} from '../../ported/c-runtime.js';\n\n"

for f in nodes:
 current=names[f['name']];body=next(x for x in f['inner']if x.get('kind')=='CompoundStmt');fstart=loc(f);fend=loc(f,True);params=[x['name']for x in f['inner']if x.get('kind')=='ParmVarDecl'];out+='export function '+current+'('+', '.join(params)+')\n'+statement(body)+'\n'
# Retain source-inactive historical comments verbatim; active statement comments stay in original boundaries.
for i,c in enumerate(comments):
 if i not in usedcomments:out+=c[0]+'\n'
(w/'candidate').mkdir(exist_ok=True);(w/'candidate/sfexpasc.js').write_text(out)
(w/'lower-contract.json').write_text(json.dumps({'calls':sorted(calls),'fields':sorted(fields),'sizes':sorted(sizes),'staticBuffers':staticbufs,'globals':sorted(globals),'cells':[decls[x]['name']for x in cells]},indent=2)+'\n')
print(len(nodes),'configured functions',len(out),'JS bytes')
