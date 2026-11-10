"""SP_LEV exact source/CPP/AST/data/typed-field guards, not a semantic proof."""
from pathlib import Path
import ast,collections,hashlib,json,re,subprocess
r=Path(__file__).resolve().parents[3];w=r/'.cache/sp-lev-first-pass'
load=lambda p:json.loads(p.read_text())
inv=load(w/'inventory.json');old=load(w/'sp_lev-ast.json');F=load(w/'functions.json');extra=load(w/'inventory-extra.json');schema=load(r/'nethack-c/wasm/tu-fragments/sp_lev-schema.json');meta=load(w/'core-meta.json')
source=(r/'.cache/wasm64-build/tree/src/sp_lev.c').read_bytes();assert hashlib.sha256(source).hexdigest()==inv['sourceSHA256'];assert source==(r/'nethack-c/upstream/src/sp_lev.c').read_bytes()
cmd=inv['productionProfile']['command'];assert cmd[-1]=='sp_lev.c'and cmd[1:4]==['-O2','-g','-sMEMORY64=1'];assert cmd[cmd.index('-include')+1]==str(r/'nethack-c/wasm/native-terminal.h')
with (w/'guard-ast.json').open('w')as out:subprocess.run(cmd[:1]+['-Xclang','-ast-dump=json','-fsyntax-only']+cmd[1:],cwd=inv['productionProfile']['cwd'],stdout=out,check=True)
fresh=load(w/'guard-ast.json')
def normalized(tree):
 def visit(n):
  if isinstance(n,list):return [visit(x)for x in n]
  if isinstance(n,dict):return {k:visit(v)for k,v in n.items()if k not in ['id','previousDecl','typeAliasDeclId','referencedMemberDecl','targetLabelDeclId','declId']}
  if isinstance(n,str)and re.fullmatch('0x[0-9a-f]+',n):return '<compiler-decl-id>'
  return n
 return visit(tree)
assert normalized(fresh)==normalized(old),'Actual production compiler AST changed; refresh/review source metadata'
js=(r/'js/ported/sp_lev.js').read_text();assert re.findall(r'export function (\w+)\(',js)==[f['name']for f in F]
for f in F:
 ps=[p['name']for p in f.get('inner',[])if p['kind']=='ParmVarDecl'];m=re.search(r'export function '+f['name']+r'\(([^)]*)\)',js);assert m
 assert [p.strip()for p in m[1].split(',')if p.strip()]==ps,(f['name'],ps,m[1])
for c in set(re.findall(rb'/\*.*?\*/',source,re.S)):assert c.decode()in js,c
assert len(F)==142 and len(meta['usedFieldIds'])==376 and len(extra['actualRecords'])==80
assert len(schema['schema'])==82 and sum(len(s['fields'])for s in schema['schema'].values())==386
nodes={};records={};fieldmap={}
def walk(n):
 yield n
 for x in n.get('inner',[]):yield from walk(x)
for n in walk(old):
 if 'id'in n and n.get('range'):nodes[n['id']]=n
 if n.get('kind')=='RecordDecl'and n.get('completeDefinition'):
  records[n['id']]=n
  for f in n.get('inner',[]):
   if f.get('kind')=='FieldDecl':fieldmap[f['id']]=(n,f)
for n in walk(old):
 if n.get('kind')=='TypedefDecl':
  for child in n.get('inner',[]):
   rec=records.get(child.get('ownedTagDecl',{}).get('id'))
   if rec and not rec.get('name'):rec['name']=n['name']
# Only the two declaration-scoped reserved locals are renamed.
renamed=[('create_monster',60085,'0x927685d48'),('find_objtype',108327,'0x926fc1d18')]
for owner,offset,id in renamed:
 f=next(f for f in F if f['name']==owner);d=next(n for n in walk(f)if n.get('kind')=='VarDecl'and n.get('name')=='class');assert d['id']==id and d['range']['begin']['offset']==offset and d['type']['qualType']=='char'
 assert re.search(r'\blet class_\b',js[js.index('export function '+owner+'('):])
assert not re.search(r'\b(let|const) class\b',re.sub(r'/\*.*?\*/','',js,flags=re.S))
# Exact used C field declaration IDs and all JS C.field member paths must exist.
used={(rec.get('name'),f['name'])for id in meta['usedFieldIds']for rec,f in [fieldmap[id]]}
actual=set(re.findall(r',"([A-Za-z_][A-Za-z_0-9]*)","([A-Za-z_][A-Za-z_0-9]*)"\)',js))
for kind,name in actual:assert kind in schema['schema']and any(f['name']==name for f in schema['schema'][kind]['fields']),(kind,name)
# Full native declaration order is mandatory for each aggregate initializer.
for t in meta['recordInitializers']:
 candidates=[(name,s)for name,s in schema['schema'].items()if s['ctype']==t or s['ctype']=='sp_lev_objclasspfx'and t=='sp_lev_objclasspfx'];assert len(candidates)==1,(t,candidates)
 name,s=candidates[0];rec=next(rec for rec in records.values()if rec.get('name')==name or name=='sp_lev_room_type'and rec.get('range',{}).get('begin',{}).get('offset')==124387 or name=='sp_lev_trap_type'and rec.get('range',{}).get('begin',{}).get('offset')==135018)
 assert [f['name']for f in s['fields']]==[f['name']for f in rec['inner']if f.get('kind')=='FieldDecl'],name
assert {f['name']for f in schema['schema']['object']['fields']}>=set(['x','y','invis'])
assert {f['name']for f in schema['schema']['str_or_len']['fields']}=={'str','len'}
assert [(f['name'],f['canonical'])for f in schema['schema']['objclasspfx']['fields']]==[('prefix','char *'),('class','char')]
strings=set()
for n in [*F,*inv['topLevelVariables']]:
 for v in walk(n):
  if v.get('kind')=='StringLiteral':strings.add(ast.literal_eval(v['value']))
assert sorted(strings)==schema['literals']and sum(len(s.encode())+1 for s in strings)==4698==schema['literalBytes']
assert len(meta['localStatics'])==50 and len(meta['data'])==11 and len(schema['backings'])==61 and not schema['publicData']
assert len(meta['functionPointers'])==40 and len(schema['dependencies'])==206 and len(meta['variadics'])==34
rng=re.findall(r'C\.rng_log_set_caller\(C\.literal\("sp_lev\.c"\),(\d+),\(C\.literal\("(\w+)"\)\)\)',js)
assert collections.Counter((int(line),name)for line,name in rng)==collections.Counter((row['line'],row['owner'])for row in inv['rngSites'])and len(rng)==73
# Actual source-width hazards remain in the configured AST, not inferred text.
assert len(extra['pointerIncrements'])==4 and len(extra['dereferencedIncrements'])==2
assert len(extra['addressedSourceParameters'])==4
assert not [n for f in F for n in walk(f)if n.get('kind')=='CompoundAssignOperator'and n['inner'][0]['type']['qualType'].endswith('*')]
# Addressed automatic scalars reserve native bytes without an invented initializer.
# Explicit C initializers and formal argument cells must still write their value.
auto_audit=[]
for index,fn in enumerate(F):
 local={n['id']:n for n in walk(fn)if n.get('kind')in ['VarDecl','ParmVarDecl']};addressed={}
 for n in walk(fn):
  if n.get('kind')=='UnaryOperator'and n.get('opcode')=='&':
   x=n['inner'][0]
   while x.get('kind')in ['ParenExpr','ImplicitCastExpr','CStyleCastExpr']and x.get('inner'):x=x['inner'][0]
   if x.get('kind')=='DeclRefExpr':
    d=local.get(x['referencedDecl']['id']);t=x['type'].get('desugaredQualType',x['type']['qualType'])
    if d and d.get('storageClass')!='static'and ('*'in t or not(t.startswith(('struct ','union '))or '['in t)and t not in schema['schema']):addressed[d['id']]=d
 start=js.index('export function '+fn['name']+'(');end=js.index('export function '+F[index+1]['name']+'(',start)if index+1<len(F)else len(js);body=js[start:end]
 for d in addressed.values():
  name=d['name']+'Address';formal=d['kind']=='ParmVarDecl';initialized=bool(d.get('init'));lines=[line for line in body.splitlines()if re.search(r'\b(?:let|const) '+name+r'=C\.stackAlloc\(',line)];assert lines,(fn['name'],name)
  writes=[line for line in lines if 'C.cell('+name+','in line and '.value='in line]
  same=[v for v in addressed.values()if v['name']==d['name']];expected=sum(v['kind']=='ParmVarDecl'or bool(v.get('init'))for v in same)
  assert len(writes)==expected,(fn['name'],name,writes,expected)
  auto_audit.append({'owner':fn['name'],'kind':d['kind'],'name':d['name'],'offset':d['range']['begin']['offset'],'type':d['type']['qualType'],'explicitInitializer':initialized,'formalArgumentWrite':formal,'emission':'reserve+initialize'if initialized or formal else'reserve-only'})
(w/'uninitialized-auto-audit.json').write_text(json.dumps(auto_audit,indent=2)+'\n')
lib=(r/'nethack-c/wasm/tu-libraries/sp_lev.js').read_text();assert 'teleport_sp_lev_get_unpacked_coord__sig:"vpji"'in lib
assert 'TELEPORT_REFERENCE_TU'not in (r/'nethack-c/wasm/tu-fragments/sp_lev-support.c').read_text()
for n in schema['dependencies']:assert re.search(r'^'+re.escape(n)+r':',lib,re.M),n
for row in schema['backings']:
 line=next(line for line in (r/'nethack-c/wasm/tu-fragments/sp_lev-support.c').read_text().splitlines()if line.startswith('static ')and row['symbol']in line);assert '='not in line,line
subprocess.run(['python3','-B',str(w/'check-boundaries.py')],cwd=r,check=True)
subprocess.run([str(r/'.cache/emsdk/node/24.19.0_64bit/bin/node'),str(w/'check-scope.mjs'),'sp_lev'],cwd=r,check=True)
print('SP_LEV actual production AST/CPP,142 boundaries/comments/formals,82 ordered schemas/386 fields,61 zero backings,40 identities,73 RNG/literal/source/width/scope guards PASS')
