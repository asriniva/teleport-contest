from pathlib import Path
import json,re
import sys
p=Path(sys.argv[1]).resolve();r=Path.cwd();a=json.loads((p/'tiletext.ast.json').read_text());decls={}
def walk(n):
 if not isinstance(n,dict):return
 if 'id'in n:decls[n['id']]=n
 for x in n.get('inner',[]):walk(x)
walk(a);vals={}
for d in a['inner']:
 if d.get('kind')=='EnumDecl':
  n=-1
  for e in d.get('inner',[]):
   if e.get('kind')=='EnumConstantDecl':
    v=next((x['value']for x in e.get('inner',[])if'value'in x),None);n=int(v)if v is not None else n+1;vals[e['id']]=n

def ev(x):
 k=x['kind'];inner=x.get('inner',[])
 if k=='StringLiteral':return json.loads(x['value'])
 if k in ['IntegerLiteral','ConstantExpr']:return int(x['value'])
 if k=='DeclRefExpr':return vals[x['referencedDecl']['id']]
 if k in ['ImplicitValueInitExpr']:return 0
 if k=='InitListExpr':return [ev(y)for y in inner]
 if k=='UnaryOperator':return -ev(inner[0])if x['opcode']=='-'else ev(inner[0])
 if k=='BinaryOperator':return {'+':lambda a,b:a+b,'-':lambda a,b:a-b,'<<':lambda a,b:a<<b}[x['opcode']](ev(inner[0]),ev(inner[1]))
 if len(inner)==1:return ev(inner[0])
 raise Exception((k,x))
names=['altlabels','conditionals','altar_text','wall_texts','walldesc','expl_texts','zap_texts','tilesrc_texts']
data={}
for n in names:
 d=next(x for x in a['inner']if x.get('kind')=='VarDecl'and x.get('name')==n);data[n]=ev(d['inner'][-1])
for n,keys in [('altlabels',['idx','tilelabel','expectedlabel']),('conditionals',['sequence','predecessor','name'])]:data[n]=[dict(zip(keys,row))for row in data[n]]
(p/'data.json').write_text(json.dumps(data,indent=2)+'\n');(p/'data.mjs').write_text('// Configured original Clang initializer projection; JS authoritative.\n'+'\n'.join('export const '+n+' = '+json.dumps(v,indent=2)+';'for n,v in data.items())+'\n')
# Actual compiled nh_snprintf macro arguments preserve diagnostic metadata.
sites=[]
def scan(n,fn=None):
 if not isinstance(n,dict):return
 if n.get('kind')=='FunctionDecl'and any(x.get('kind')=='CompoundStmt'for x in n.get('inner',[])):fn=n['name']
 if n.get('kind')=='CallExpr':
  def ref(x):
   if x.get('kind')=='DeclRefExpr':return x.get('referencedDecl',{}).get('name')
   return next((v for y in x.get('inner',[])if(v:=ref(y))),None)
  if ref(n.get('inner',[{}])[0])=='nh_snprintf':sites.append({'function':fn,'line':ev(n['inner'][2]),'offset':n['range']['begin'].get('expansionLoc',n['range']['begin'])['offset']})
 for y in n.get('inner',[]):scan(y,fn)
scan(a);(p/'snprintf-sites.json').write_text(json.dumps(sites,indent=2)+'\n')
print('tables',[(k,len(v))for k,v in data.items()],'snprintf',len(sites))
