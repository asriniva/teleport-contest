"""Bounded PRAY source/profile/ABI/data guard, not an equivalence proof."""
from pathlib import Path
import json,re,hashlib,subprocess,ast
r=Path(__file__).resolve().parents[3];w=r/'.cache/pray-first-pass';j=json.load(open(r/'nethack-c/wasm/tu-fragments/pray-schema.json'));inv=json.load(open(r/'nethack-c/wasm/tu-fragments/pray-provenance.json'));profile=inv['productionProfile'];command=[arg.replace(inv['recordedRoot'],str(r))for arg in profile['command']];cwd=profile['cwd'].replace(inv['recordedRoot'],str(r));source=(r/'.cache/wasm64-build/tree/src/pray.c').read_text();js=(r/'js/ported/pray.js').read_text()
assert hashlib.sha256(source.encode()).hexdigest()==inv['sourceSHA256']
assert (r/'nethack-c/upstream/src/pray.c').read_text()==source
# Production uses cwd TREE/src + basename pray.c and a forced terminal header.
assert command[-1]=='pray.c'and Path(cwd)==r/'.cache/wasm64-build/tree/src'
assert [arg[2:]for arg in command if arg.startswith('-D')]==json.load(open(r/'nethack-c/wasm/compile-defines.json'))
assert '-I'+str(r/'.cache/ncurses-wasm64-build/include')in command and '-sMEMORY64=1'in command and '-O2'in command
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
 if 'file'in loc:owner=loc['file']
 if owner=='pray.c':
  if n.get('kind')=='FunctionDecl'and any(c.get('kind')=='CompoundStmt'for c in n.get('inner',[])):F.append(n)
  if n.get('kind')=='VarDecl':private[n['name']]=n
assert [f['name']for f in F]==list(j['functionTypes'])and len(F)==45
assert {f['name']:fingerprint(f)for f in F}==j['functionAstHashes']
assert set(private)=={'Moloch','godvoices','hallu_gods','turn_undead_range','turn_undead_msg_cnt'}
assert {n:fingerprint(v)for n,v in private.items()}==j['privateAstHashes']
localstatics=[]
offset=0
for f in F:
 for n in walk(f):
  if n.get('kind')=='VarDecl'and n.get('storageClass')=='static':
   text=ast.literal_eval(next(x['value']for x in walk(n)if x.get('kind')=='StringLiteral'))
   size=int(re.search(r'\[(\d+)\]',n['type']['qualType'])[1])
   localstatics.append({'owner':f['name'],'name':n['name'],'type':n['type']['qualType'].replace('const ',''),'text':text,'bytes':size,'offset':offset});offset+=size
assert localstatics==j['localStatics'] and len(localstatics)==5 and offset==164
assert not re.search(r'\b(?:let|const|var)\s+(?:class|in)\b',js)
# Re-check native record field types/bit widths, independently of generated IDs.
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
  a=actual[f['name']];assert a['type']['qualType']==f['ctype'];assert bool(a.get('isBitfield'))==f['bit']
  assert next((n['value']for n in a.get('inner',[])if'value'in n),None)==f['bitWidth']
# Audit actual native helper indices against each exact compiler-backed field.
support=(r/'nethack-c/wasm/tu-fragments/pray-support.c').read_text()
for action in ['read','write','address']:
 body=support.split('teleport_pray_'+action+'(',1)[1]
 body=body.split('default:abort();}}\n')
 assert len(body)>=len(j['schema'])+1
 for index,(name,record)in enumerate(j['schema'].items()):
  block=body[index]
  assert 'case '+str(index)+':{'+('volatile 'if name=='window_procs'else'')+record['ctype']+'*p=at;switch(field){'in block
  for field_index,f in enumerate(record['fields']):
   address=f['canonical'].startswith(('struct ','union '))and not f['canonical'].endswith('*')or'['in f['canonical']or f['canonical']=='dlevel_t'
   if action=='read':expected='return(uint64_t)(uintptr_t)('+('&'if address else'')+'p->'+f['name']+');'
   elif action=='address':expected=None if f['bit']else'return(void*)&p->'+f['name']+';'
   else:expected=None if address or f['ctype'].endswith('const')or(f['ctype'].startswith('const ')and not f['canonical'].endswith('*'))else'p->'+f['name']+'=('+f['ctype']+')value;return;'
   if expected is not None:assert 'case '+str(field_index)+':'+expected in block,(action,name,f['name'])

P={n['name']:n for n in A['inner']if n.get('kind')=='FunctionDecl'}
for n,t in j['allDependencyTypes'].items():assert P[n]['type']['qualType']==t
finalcpp=subprocess.check_output(command[:1]+['-E','-dM']+command[1:],cwd=cwd,text=True);macros={m[1]:m[2]for m in re.finditer(r'^#define (\w+)(.*)$',finalcpp,re.M)}
assert {n:macros.get(n)for n in j['configuredMacroDefinitions']}==j['configuredMacroDefinitions']
fullcpp=subprocess.check_output(command[:1]+['-E','-dD']+command[1:],cwd=cwd,text=True)
assert re.search(r'rng_log_set_caller\(\s*"pray.c"',fullcpp)
literals={json.loads(m[1])for m in re.finditer(r'C\.literal\(("(?:\\.|[^"\\])*")\)',js)}
assert literals==set(j['literals']);assert sum(len(s.encode())+1 for s in literals)==j['literalBytes']==6316
assert re.search(r'^#define PRAY_LITERAL_CAPACITY 6316$',(r/'nethack-c/wasm/tu-fragments/pray-source-data.h').read_text(),re.M)
assert re.search(r'^#define PRAY_LOCAL_STATIC_BYTES 164$',(r/'nethack-c/wasm/tu-fragments/pray-source-data.h').read_text(),re.M)
# Source-defined data remains JS-authoritative, checked against the compiler AST.
for name,value in j['data'].items():
 decl=private[name];strings=[ast.literal_eval(x['value'])for x in walk(decl)if x.get('kind')=='StringLiteral']
 assert strings==([value]if isinstance(value,str)else value),(name,strings,value)
 encoded=json.dumps(value,separators=(',',':'))
 expected='export const '+name+'=C=>'+('C.literal('+encoded+')'if isinstance(value,str)else '['+','.join('C.literal('+json.dumps(x)+')'for x in value)+']')+';'
 assert expected in js,(name,expected)
 assert name not in re.findall(r'static[^;]*;',support), 'No initialized private C mirror'
rng=[]
def original_offset(n):
 b=n.get('range',{}).get('begin',{});return b.get('expansionLoc',b).get('offset',-1)
for f in F:
 for n in walk(f):
  if n.get('kind')=='CallExpr':
   names=[d.get('referencedDecl',{}).get('name')for d in walk(n['inner'][0])if d.get('kind')=='DeclRefExpr']
   if names==['rng_log_set_caller']:
    args=n['inner'];line=next(x['value']for x in walk(args[2])if x.get('kind')=='IntegerLiteral');rng.append([f['name'],int(line)])
assert rng==j['rngSites']and len(rng)==31
assert js.count('C.rn2_on_display_rng(')==2
assert 'C.functionPointer("prayer_done")'in js and 'C.functionPointer("maybe_turn_mon_iter")'in js
assert 'switch(C.i64(count))'in js or 'case C.i64((0)):'in js
assert not re.search(r'C\.(?:rn1|min|max|Maybe_Half_Phys)\(',js)
assert js.count('C.staticArray(')==5
print('PRAY source/profile/AST/data/alias metadata guarded: 45 bodies, 45 records/158 fields, '+str(len(j['configuredMacroDefinitions']))+' macros, 31 logged + 2 display RNG expansions, 6316 literal + 164 static bytes; native behavior pending')
