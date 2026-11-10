"""MKOBJ configured-source/profile/ABI/data guard, not native equivalence proof."""
from pathlib import Path
import json,re,hashlib,subprocess,ast
r=Path(__file__).resolve().parents[3];w=r/'.cache/mkobj-first-pass';j=json.load(open(r/'nethack-c/wasm/tu-fragments/mkobj-schema.json'));inv=json.load(open(r/'nethack-c/wasm/tu-fragments/mkobj-provenance.json'));profile=inv['productionProfile'];command=[arg.replace(inv['recordedRoot'],str(r))for arg in profile['command']];cwd=profile['cwd'].replace(inv['recordedRoot'],str(r));source=(r/'.cache/wasm64-build/tree/src/mkobj.c').read_text();js=(r/'js/ported/mkobj.js').read_text()
assert hashlib.sha256(source.encode()).hexdigest()==inv['sourceSHA256']
assert (r/'nethack-c/upstream/src/mkobj.c').read_text()==source
assert command[-1]=='mkobj.c'and Path(cwd)==r/'.cache/wasm64-build/tree/src'
assert [arg[2:]for arg in command if arg.startswith('-D')]==json.load(open(r/'nethack-c/wasm/compile-defines.json'))
assert '-I'+str(r/'.cache/ncurses-wasm64-build/include')in command and '-sMEMORY64=1'in command and '-O2'in command and '-g'in command
assert command[command.index('-include')+1]==str(r/'nethack-c/wasm/native-terminal.h')
A=json.loads(subprocess.check_output(command[:1]+['-Xclang','-ast-dump=json','-fsyntax-only']+command[1:],cwd=cwd,text=True))
def walk(n):
 yield n
 for c in n.get('inner',[]):yield from walk(c)
def stable(n):
 if isinstance(n,list):return[stable(x)for x in n]
 if isinstance(n,dict):return{k:stable(v)for k,v in n.items()if k not in ['id','loc','range','previousDecl','referencedMemberDecl','typeAliasDeclId','targetLabelDeclId','declId']}
 return n
def fingerprint(n):return hashlib.sha256(json.dumps(stable(n),sort_keys=True,separators=(',',':')).encode()).hexdigest()
owner=None;F=[];private={}
for n in A['inner']:
 loc=n.get('loc',{});loc=loc.get('expansionLoc',loc)
 if'file'in loc:owner=loc['file']
 if owner=='mkobj.c':
  if n.get('kind')=='FunctionDecl'and any(c.get('kind')=='CompoundStmt'for c in n.get('inner',[])):F.append(n)
  if n.get('kind')=='VarDecl':private[n['name']]=n
assert [f['name']for f in F]==list(j['functionTypes'])and len(F)==99
assert {f['name']:fingerprint(f)for f in F}==j['functionAstHashes']
assert {n:fingerprint(v)for n,v in private.items()}==j['privateAstHashes']and len(private)==13
assert re.findall(r'^export function (\w+)\(',js,re.M)==[f['name']for f in F]
# Every original comment is retained byte-for-byte, including intended UAF diagnostic.
comments=re.findall(r'/\*.*?\*/|//[^\n]*',source,re.S)
for text in comments:assert text in js,text
for name,row in j['data'].items():assert 'export const '+name+'=C=>'+row['initializer']+';'in js
assert 'export const initializers={'+','.join(j['data'])+'};'in js
assert set(private)==set(j['data'])
localstatics=[];renames=[];postfix=[];rng=[]
for f in F:
 for n in walk(f):
  if n.get('kind')=='VarDecl'and n.get('storageClass')=='static':localstatics.append((f['name'],n['name'],n['type']['qualType']))
  if n.get('kind')in ['ParmVarDecl','VarDecl']and n.get('name')=='let':renames.append((f['name'],n['kind'],'let','let_',n['type']['qualType'],n['loc']['offset']))
  if n.get('kind')=='UnaryOperator'and n.get('isPostfix')and n.get('opcode')in ['++','--']and'*'in n.get('type',{}).get('qualType',''):postfix.append({'owner':f['name'],'type':n['type']['qualType'],'opcode':n['opcode'],'offset':n['range']['begin']['offset']})
  if n.get('kind')=='CallExpr'and any(x.get('referencedDecl',{}).get('name')=='rng_log_set_caller'for x in walk(n['inner'][0])):rng.append([f['name'],int(next(x['value']for x in walk(n['inner'][2])if x.get('kind')=='IntegerLiteral'))])
assert localstatics==[(x['owner'],x['name'],x['type'])for x in j['localStatics']]and len(localstatics)==2
assert renames==[(x['owner'],x['kind'],x['original'],x['javascript'],x['type'],x['offset'])for x in j['reservedBindingMappings']]
assert [(x[0],x[1])for x in renames]==[('mkobj_at','ParmVarDecl'),('mksobj_init','VarDecl'),('mksobj','VarDecl')]
# Reidentify each fresh compiler declID separately; map its references within owner only.
for f in F:
 for n in walk(f):
  if n.get('kind')in ['ParmVarDecl','VarDecl']and n.get('name')=='let':
   assert n['id']not in [q['id']for other in F if other is not f for q in walk(other)if q.get('kind')in ['ParmVarDecl','VarDecl']and q.get('name')=='let']
assert 'export function mkobj_at(let_,x,y,artif)'in js
assert not re.search(r'\b(?:let|const|var)\s+let\b',js)
assert postfix==j['pointerPostfixSites']and len(postfix)==2
assert js.count('iprobs=C.ptr((iprobs+Number(C.sizes["struct icp"])))')==2
assert not[n for f in F for n in walk(f)if n.get('kind')=='CompoundAssignOperator'and n.get('opcode')in ['+=','-=']and'*'in n.get('type',{}).get('desugaredQualType',n.get('type',{}).get('qualType',''))]
assert not[n for f in F for n in walk(f)if n.get('kind')in ['GotoStmt','LabelStmt']]
assert rng==j['rngSites']and len(rng)==79
records={}
for n in walk(A):
 if n.get('kind')=='RecordDecl'and n.get('completeDefinition'):records[n['id']]=n
for n in walk(A):
 if n.get('kind')=='TypedefDecl':
  for c in n.get('inner',[]):
   record=records.get(c.get('ownedTagDecl',{}).get('id'))
   if record and not record.get('name'):record['name']=n['name']
byname={n.get('name'):n for n in records.values()}
for name,s in j['schema'].items():
 actual={f['name']:f for f in byname[name]['inner']if f.get('kind')=='FieldDecl'}
 for f in s['fields']:
  a=actual[f['name']];assert a['type']['qualType']==f['ctype'];assert bool(a.get('isBitfield'))==f['bit'];assert next((n['value']for n in a.get('inner',[])if'value'in n),None)==f['bitWidth']
support=(r/'nethack-c/wasm/tu-fragments/mkobj-support.c').read_text()
for action in ['read','write','address']:
 body=support.split('teleport_mkobj_'+action+'(',1)[1].split('default:abort();}}\n');assert len(body)>=len(j['schema'])+1
 for index,(name,record)in enumerate(j['schema'].items()):
  block=body[index];assert 'case '+str(index)+':{'+record['ctype']+'*p=at;switch(field){'in block
  for field_index,f in enumerate(record['fields']):
   address=f['canonical'].startswith(('struct ','union '))and not f['canonical'].endswith('*')or'['in f['canonical']or f['canonical']=='dlevel_t'
   if action=='read':expected='return(uint64_t)(uintptr_t)('+('&'if address else'')+'p->'+f['name']+');'
   elif action=='address':expected=None if f['bit']else'return(void*)&p->'+f['name']+';'
   else:expected=None if address or f['ctype'].endswith('const')or(f['ctype'].startswith('const ')and not f['canonical'].endswith('*'))else'p->'+f['name']+'=('+f['ctype']+')value;return;'
   if expected is not None:assert 'case '+str(field_index)+':'+expected in block,(action,name,f['name'])
for row in j['backings']:
 match=re.search(r'^static (.+\b'+row['symbol']+r'[^;]*);',support,re.M);assert match and'='not in match[0],row
P={n['name']:n for n in A['inner']if n.get('kind')=='FunctionDecl'}
for n,t in j['allDependencyTypes'].items():assert P[n]['type']['qualType']==t
for f in F:
 assert f['type']['qualType']==j['functionTypes'][f['name']]
 ps=[n for n in f['inner']if n.get('kind')=='ParmVarDecl'];assert [(p['name'],p['type']['qualType'])for p in ps]==[(p['name'],p['ctype'])for p in j['sourceParameters'][f['name']]]
finalcpp=subprocess.check_output(command[:1]+['-E','-dM']+command[1:],cwd=cwd,text=True);macros={m[1]:m[2]for m in re.finditer(r'^#define (\w+)(.*)$',finalcpp,re.M)}
assert {n:macros.get(n)for n in j['configuredMacroDefinitions']}==j['configuredMacroDefinitions']
fullcpp=subprocess.check_output(command[:1]+['-E','-dD']+command[1:],cwd=cwd,text=True);assert re.search(r'rng_log_set_caller\(\s*"mkobj.c"',fullcpp)
assert '#define on_ice recharged'in fullcpp and '#define ocontainer v.v_ocontainer'in fullcpp and '#define nexthere v.v_nexthere'in fullcpp
assert '#define special_corpse(num)'in fullcpp and '#undef ROT_ICE_ADJUSTMENT'in fullcpp
literals={json.loads(m[1])for m in re.finditer(r'C\.literal\(("(?:\\.|[^"\\])*")\)',js)}
assert literals==set(j['literals'])and sum(len(s.encode())+1 for s in literals)==j['literalBytes']==4084
header=(r/'nethack-c/wasm/tu-fragments/mkobj-source-data.h').read_text();assert '#define MKOBJ_LITERAL_CAPACITY 4084'in header and '#define MKOBJ_LOCAL_STATIC_BYTES 176'in header
assert js.count('C.copyRecord(')==9 and js.count('C.staticData(')==2
assert not re.search(r'C\.(?:rn1|min|max|Maybe_Half_Phys)\(',js)
library=(r/'nethack-c/wasm/tu-libraries/mkobj.js').read_text();assert 'attach_egg_hatch_timeout:(a0,a1)=>_attach_egg_hatch_timeout(pointer(a0),i64(a1))'in library
assert 'void (*fn)(const char *, ...)' in support and j['callbackTypes']==['void (const char *, ...)']
assert 'args.map(e.ptr)'not in(r/'scripts/test-tu-mkobj.mjs').read_text()
print('MKOBJ source/profile/AST/data/scope/native-field guarded:99 bodies/13 private data objects/2 local statics/43 records167 fields/79 RNG;179 macros;4084 literal+176 static bytes;5 long params/2 long returns; native pending')
