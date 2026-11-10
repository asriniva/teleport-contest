"""Configured FILES source/CPP/AST/data ABI guards; not a behavioral proof."""
from pathlib import Path
import subprocess,json,re,hashlib,ast,os
R=Path(__file__).resolve().parents[3];W=R/'.cache/files-first-pass';tree=R/'.cache/wasm64-build/tree';src=tree/'src/files.c';pristine=R/'nethack-c/upstream/src/files.c';schema=json.load(open(R/'nethack-c/wasm/tu-fragments/files-schema.json'));baseline=json.load(open(R/'nethack-c/wasm/tu-fragments/files-source-inventory.json'));names=[f['name']for f in baseline['functions']]
assert hashlib.sha256(src.read_bytes()).hexdigest()=='460967cdbc2c5c73d29e7148efcb8ee4c3a60fe548a152fe3e4a3f5fe549e96d','prepared files.c changed: review inherited codec dispatch'
assert hashlib.sha256(pristine.read_bytes()).hexdigest()=='5295af5df75ed1f67c9898d9d56a2cad6a35da68e511b5e5ab35886db6f9f2a5','pristine files.c changed'
flags=['-sMEMORY64=1','-I'+str(tree/'include'),'-I'+str(R/'.cache/ncurses-wasm64-build/include'),'-include',str(R/'nethack-c/wasm/native-terminal.h')]+['-D'+v for v in json.load(open(R/'nethack-c/wasm/compile-defines.json'))]
cc=[str(R/'.cache/emsdk/upstream/emscripten/emcc'),*flags,'files.c'];cwd=tree/'src'
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
assert len(F)==68 and sum(f.get('storageClass')=='static'for f in F)==15
fields=[{'owner':f['name'],'member':n['name'],'type':stable(n['type']),'arrow':n.get('isArrow',False),'expansion':n['range']['begin'].get('expansionLoc',n['range']['begin'])}for f in F for n in nodes(f)if n.get('kind')=='MemberExpr'];assert fields==baseline['members'],'actual configured MemberExpr alias changed'
ops=[{'owner':f['name'],'kind':n['kind'],'opcode':n['opcode'],'type':stable(n['inner'][0]['type']),'pointer':n['inner'][0]['type'].get('qualType','').endswith('*'),'range':n.get('range')}for f in F for n in nodes(f)if n.get('kind')=='CompoundAssignOperator'or n.get('kind')=='UnaryOperator'and n.get('opcode')in ['++','--']];assert ops==baseline['pointerOperations']
compound=[x for x in ops if x['kind']=='CompoundAssignOperator'and x['pointer']];assert len(compound)==2 and all(x['type']['qualType']=='char *'and x['opcode']=='+='for x in compound),'review non-byte pointer compound scaling'
active=set(re.findall(r'^#define (\w+)',macros,re.M))
for n in ['COMPRESS','COMPRESS_EXTENSION','SELECTSAVED','NO_FILE_LINKS','USE_FCNTL','INSURANCE','SAFERHANGUP','LIVELOG','DUMPLOG_CORE','ALTMETA','UNIX','TTY_GRAPHICS','HANGUPHANDLING','DEBUG','NODIAG','MACOS','__EMSCRIPTEN__']:assert n in active,n
for n in ['ZLIB_COMP','PREFIXES_IN_USE','SFCTOOL','DLB','DLBLIB','DLBRSRC','WIN32','VMS']:assert n not in active,n
rngsites=re.findall(r'rng_log_set_caller\("files.c", (\d+), __func__\)',pre);assert rngsites==['3461','3468'],rngsites
snprintfsites=re.findall(r'nh_snprintf\(__func__, (\d+),',pre);assert snprintfsites==['2151'],snprintfsites
assert 'childstatus = teleport_compress_file(filename, cfn, uncomp);'in pre and 'f = fork();'not in pre,'actual prepared compression dispatch changed'
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
source=src.read_text();core=(R/'js/ported/files.js').read_text();support=(R/'nethack-c/wasm/tu-fragments/files-support.c').read_text()
for comment in re.findall(r'/\*[\s\S]*?\*/',source)+re.findall(r'/\*[\s\S]*?\*/',pristine.read_text()):assert comment in core,'original block comment missing'
assert re.findall(r'export function (\w+)\(',core)==names,'source boundaries/order changed'
assert 'C.enterAutomatic(['in core and 'C.local("get_saved_games.uid","int")'in core
assert 'TELEPORT_FILES_VALIDATE_ORIGINAL'in support and '#ifdef TELEPORT_REFERENCE_TU'not in support,'private assertions leaked into unrelated reference fixture'
# The source-private mirror exists only to type ABI/storage; every backing/literal
# declaration is zero-only. No initialized C source table or algorithm mirror.
for declaration in re.findall(r'static [^;]+(?:files_backing_\d+|files_literals)[^;]*;',support):assert '='not in declaration,declaration
# Independently evaluate original static initializers, then compare JS-owned rows.
def val(n):
 k=n['kind'];cs=n.get('inner',[])
 if k in ['StringLiteral']:return ast.literal_eval(n['value'])
 if k in ['IntegerLiteral','CharacterLiteral']:return int(n['value'])
 if k=='InitListExpr':return[val(c)for c in cs]
 if k=='UnaryOperator':return -val(cs[0])if n['opcode']=='-'else val(cs[0])
 if cs:return val(cs[0])
 raise AssertionError(('initializer',k))
statics=[]
for n in A['inner']:
 if n.get('kind')=='VarDecl'and n.get('storageClass')=='static'and not n.get('loc',{}).get('includedFrom'):
  statics.append((n['name'],n))
for f in F:
 for n in nodes(f):
  if n.get('kind')=='VarDecl'and n.get('storageClass')=='static':statics.append((f['name']+'.'+n['name'],n))
expected={name:val(n['inner'][-1])if n.get('inner')else None for name,n in statics}
script="import {filesStaticInitializers} from '"+(R/'js/ported/files.js').as_uri()+"';const C={literal:s=>s,sizes:{'struct sfstatus_to_msg':16,'struct flock':32},i8:Number,i16:Number,i32:Number};console.log(JSON.stringify(Object.fromEntries(filesStaticInitializers(C).map(x=>[x.name,x.values]))));"
observed=json.loads(subprocess.check_output([str(R/'.cache/emsdk/node/24.19.0_64bit/bin/node'),'--input-type=module','-e',script],text=True));assert observed==expected,('JS static data differs from original initializer',observed,expected)
# Support must remain independent of original private declarations in unrelated probes.
subprocess.run([str(R/'.cache/emsdk/upstream/emscripten/emcc'),*flags,'-DTELEPORT_REFERENCE_TU','-fsyntax-only',str(R/'nethack-c/wasm/tu-fragments/files-support.c')],check=True)
print(f'FILES source guard passed: {len(F)} functions / 53 public / 15 private, {len(fields)} actual MemberExpr aliases, {len(ops)} pointer/compound/inc/dec records, 2 byte-pointer compounds, 2 exact RNG origins, 1 exact Snprintf owner/closing-line site, 10 JS-owned static initializers, generic reference support isolation; native subprocess branch inactive/unverified.')
