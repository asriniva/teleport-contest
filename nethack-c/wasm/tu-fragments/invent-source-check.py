"""Configured INVENT source/CPP/AST/data ABI guards; not a behavioral proof."""
from pathlib import Path
import subprocess,json,re,hashlib,ast,os
R=Path(__file__).resolve().parents[3];W=R/'.cache/invent-first-pass';tree=R/'.cache/wasm64-build/tree';src=tree/'src/invent.c';pristine=R/'nethack-c/upstream/src/invent.c';schema=json.load(open(R/'nethack-c/wasm/tu-fragments/invent-schema.json'));baseline=json.load(open(R/'nethack-c/wasm/tu-fragments/invent-source-inventory.json'));names=[f['name']for f in baseline['functions']]
assert hashlib.sha256(src.read_bytes()).hexdigest()=='0b93d6ce1abb5b63ed7ea07c26a57e1016c6cef0fc2ef0e4016e6622054524b5','prepared invent.c changed: review source provenance'
assert hashlib.sha256(pristine.read_bytes()).hexdigest()=='0b93d6ce1abb5b63ed7ea07c26a57e1016c6cef0fc2ef0e4016e6622054524b5','pristine invent.c changed'
flags=['-sMEMORY64=1','-I'+str(tree/'include'),'-I'+str(R/'.cache/ncurses-wasm64-build/include'),'-include',str(R/'nethack-c/wasm/native-terminal.h')]+['-D'+v for v in json.load(open(R/'nethack-c/wasm/compile-defines.json'))]
cc=[str(R/'.cache/emsdk/upstream/emscripten/emcc'),*flags,'invent.c'];cwd=tree/'src'
A=json.loads(subprocess.check_output([*cc,'-fsyntax-only','-Xclang','-ast-dump=json'],cwd=cwd,text=True));pre=subprocess.check_output([*cc,'-E'],cwd=cwd,text=True);macros=subprocess.check_output([*cc,'-E','-dM'],cwd=cwd,text=True)
def nodes(n):
 yield n
 for c in n.get('inner',[]):yield from nodes(c)
def stable(v):
 if isinstance(v,dict):return{k:stable(x)for k,x in v.items()if k not in ['id','typeAliasDeclId']}
 if isinstance(v,list):return[stable(x)for x in v]
 return v
def shape(n):
 o={k:n[k]for k in ['kind','name','opcode','castKind','value','valueCategory','isPostfix','isArrow','computeLHSType','computeResultType','isBitfield','variadic']if k in n}
 if 'type'in n:o['type']={k:n['type'][k]for k in ['qualType','desugaredQualType']if k in n['type']}
 if 'referencedDecl'in n:o['referencedDecl']={k:n['referencedDecl'][k]for k in ['kind','name','type']if k in n['referencedDecl']}
 if 'inner'in n:o['inner']=[shape(c)for c in n['inner']]
 return stable(o)
F=[f for f in A['inner']if f.get('kind')=='FunctionDecl'and f.get('name')in names and any(c.get('kind')=='CompoundStmt'for c in f.get('inner',[]))]
assert[shape(f)for f in F]==baseline['functions'],'configured source tree/width/macro/control signature changed'
assert len(F)==119 and sum(f.get('storageClass')=='static'for f in F)==32
fields=[{'owner':f['name'],'member':n['name'],'type':stable(n['type']),'arrow':n.get('isArrow',False),'expansion':n['range']['begin'].get('expansionLoc',n['range']['begin'])}for f in F for n in nodes(f)if n.get('kind')=='MemberExpr'];assert fields==baseline['members'],'actual configured MemberExpr alias changed'
ops=[{'owner':f['name'],'kind':n['kind'],'opcode':n['opcode'],'type':stable(n['inner'][0]['type']),'pointer':n['inner'][0]['type'].get('qualType','').endswith('*'),'range':n.get('range')}for f in F for n in nodes(f)if n.get('kind')=='CompoundAssignOperator'or n.get('kind')=='UnaryOperator'and n.get('opcode')in ['++','--']];assert ops==baseline['pointerOperations']
compound=[x for x in ops if x['kind']=='CompoundAssignOperator'and x['pointer']];assert len(compound)==1 and all(x['type']['qualType']=='char *'and x['opcode']=='+='for x in compound),'review non-byte pointer compound scaling'
active=set(re.findall(r'^#define (\w+)',macros,re.M))
for n in ['MAIL_STRUCTURES','ENHANCED_SYMBOLS','DUMPLOG_CORE','ALTMETA','UNIX','TTY_GRAPHICS','HANGUPHANDLING','DEBUG','NODIAG','MACOS','INSURANCE','SAFERHANGUP','__EMSCRIPTEN__']:assert n in active,n
for n in ['TTY_PERM_INVENT','DUMPLOG','OBSOLETE_HANDLING','CORE_INVENT','DLB','DLBLIB','DLBRSRC','WIN32','VMS']:assert n not in active,n
rngsites=re.findall(r'rng_log_set_caller\("invent.c", (\d+), __func__\)',pre);assert rngsites==['1550','1700'],rngsites
snprintfsites=re.findall(r'nh_snprintf\(__func__, (\d+),',pre);assert snprintfsites==['1975','2886'],snprintfsites
assert len(re.findall(r'obj_to_glyph\(otmp, rn2_on_display_rng\)',src.read_text()))==3
loot_increments=[x for x in ops if x['pointer'] and x['opcode']=='++'and x['type']['qualType']=='Loot *'];assert len(loot_increments)==2
def unwrap(n):
 while n.get('kind')in ['ImplicitCastExpr','ParenExpr','CStyleCastExpr']and n.get('inner'):n=n['inner'][0]
 return n
callbacks=[]
for f in F:
 for n in nodes(f):
  if n.get('kind')!='CallExpr':continue
  cs=n.get('inner',[]);callee=unwrap(cs[0])
  if callee.get('kind')=='DeclRefExpr'and callee.get('referencedDecl',{}).get('kind')=='FunctionDecl':continue
  callbacks.append({'site':len(callbacks),'type':cs[0]['type']['qualType'],'ret':n['type']['qualType'],'types':[x['type']['qualType']for x in cs[1:]]})
assert callbacks==schema['callbacks'],'typed callback qualifier/signature changed'
source_literals=set()
for f in F:
 for n in nodes(f):
  if n.get('kind')=='StringLiteral':source_literals.add(ast.literal_eval(n['value']))
for n in A['inner']:
 if n.get('kind')=='VarDecl'and n.get('storageClass')=='static'and not n.get('loc',{}).get('includedFrom'):
  for c in nodes(n):
   if c.get('kind')=='StringLiteral':source_literals.add(ast.literal_eval(c['value']))
assert sorted(source_literals)==schema['literals'],'source literal corpus changed'
assert sum(len(x.encode())+1 for x in source_literals)==schema['literalBytes'],'source literal backing capacity drift'
source=src.read_text();core=(R/'js/ported/invent.js').read_text();support=(R/'nethack-c/wasm/tu-fragments/invent-support.c').read_text()
for comment in re.findall(r'/\*[\s\S]*?\*/',source)+re.findall(r'/\*[\s\S]*?\*/',pristine.read_text()):assert comment in core,'original block comment missing'
assert re.findall(r'export function (\w+)\(',core)==names,'source boundaries/order changed'
assert 'C.enterAutomatic(['in core and 'C.zero(buf,(1*256))'in core
assert 'C.copy(C.staticAddress("wri_info"),C.zerowri,C.sizes["struct win_request_info_t"])'in core
assert 'let let_;'in core and 'function xprname(obj,txt,let_,dot,cost,quan)'in core
assert 'TELEPORT_INVENT_VALIDATE_ORIGINAL'in support and '#ifdef TELEPORT_REFERENCE_TU'not in support,'private assertions leaked into unrelated reference fixture'
# The source-private mirror exists only to type ABI/storage; every backing/literal
# declaration is zero-only. No initialized C source table or algorithm mirror.
for declaration in re.findall(r'static [^;]+(?:invent_backing_\d+|invent_literals)[^;]*;',support):assert '='not in declaration,declaration
# Independently evaluate original static initializers, then compare JS-owned rows.
enumvalues={}
def val(n):
 k=n['kind'];cs=n.get('inner',[])
 if k=='StringLiteral':return ast.literal_eval(n['value'])
 if k in ['IntegerLiteral','CharacterLiteral','ConstantExpr']and'value'in n:return int(n['value'])
 if k=='DeclRefExpr':return enumvalues[n['referencedDecl']['name']]
 if k=='ImplicitValueInitExpr':return 0
 if k=='InitListExpr':return[val(c)for c in n.get('array_filler',[None,*cs])[1:]]if'array_filler'in n else[val(c)for c in cs]
 if k=='UnaryOperator':return -val(cs[0])if n['opcode']=='-'else val(cs[0])
 if cs:return val(cs[0])
 raise AssertionError(('initializer',k))
for n in nodes(A):
 if n.get('kind')=='EnumDecl':
  current=-1
  for e in n.get('inner',[]):
   if e.get('kind')=='EnumConstantDecl':current=val(e['inner'][0])if e.get('inner')else current+1;enumvalues[e['name']]=current
statics=[]
for n in A['inner']:
 if n.get('kind')=='VarDecl'and n.get('storageClass')=='static'and not n.get('loc',{}).get('includedFrom'):
  statics.append((n['name'],n))
for f in F:
 for n in nodes(f):
  if n.get('kind')=='VarDecl'and n.get('storageClass')=='static':statics.append((f['name']+'.'+n['name'],n))
expected={name:val(n['inner'][-1])if n.get('inner')else None for name,n in statics}
script="import {inventStaticInitializers} from '"+(R/'js/ported/invent.js').as_uri()+"';import factory from '"+(W/'invent-reference.mjs').as_uri()+"';const m=await factory();const keys="+json.dumps(schema['layoutKeys'])+";const layout=Object.fromEntries(keys.map((k,i)=>[k,Number(m._probe_layout(i))]));const C={...layout,literal:s=>s,sizes:Object.fromEntries(Object.entries(layout).filter(([k])=>k.startsWith('size:')).map(([k,v])=>[k.slice(5),v])),i8:Number,i16:Number,i32:Number};console.log(JSON.stringify(Object.fromEntries(inventStaticInitializers(C).map(x=>[x.name,x.values]))));"
observed=json.loads(subprocess.check_output([str(R/'.cache/emsdk/node/24.19.0_64bit/bin/node'),'--input-type=module','-e',script],text=True));assert observed==expected,('JS static data differs from original initializer',observed,expected)
assert len(expected)==23
# Support must remain independent of original private declarations in unrelated probes.
subprocess.run([str(R/'.cache/emsdk/upstream/emscripten/emcc'),*flags,'-DTELEPORT_REFERENCE_TU','-fsyntax-only',str(R/'nethack-c/wasm/tu-fragments/invent-support.c')],check=True)
print(f'INVENT source guard passed: {len(F)} functions / 87 public / 32 private; {len(fields)} canonical MemberExprs; {len(ops)} compound/inc/dec; 1 char-pointer compound / 2 Loot* increments; 2 exact logged RNG origins / 3 source display-glyph sites; 2 Snprintf closing lines; all23 JS-owned persistent initializers; generic reference support isolation. Native/full-game/public pending.')

addressed_parms=[]
for f in F:
 for n in nodes(f):
  if n.get('kind')!='UnaryOperator'or n.get('opcode')!='&':continue
  d=unwrap(n['inner'][0]);ref=d.get('referencedDecl',{})
  if d.get('kind')=='DeclRefExpr'and ref.get('kind')=='ParmVarDecl':addressed_parms.append((f['name'],ref['name']))
from collections import Counter
assert Counter(addressed_parms)==Counter({('addinv_core0','obj'):2,('stackobj','obj'):1,('doorganize_core','obj'):5})
for owner in ['addinv_core0','stackobj','doorganize_core']:
 assert 'obj=C.local("'+owner+'.obj","struct obj *",obj);'in core
assert 'merged(C.global("uquiver").address,obj.address)'in core
print('PASS corrected source cell guard: all8 addressed-formal expressions/3 real cells, actual &uquiver variable address')
