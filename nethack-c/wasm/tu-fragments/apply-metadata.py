"""APPLY original source/configured full-body/type/literal/data/ABI guards."""
from pathlib import Path
import hashlib,json,os,re,subprocess
r=Path(__file__).resolve().parents[3];w=r/'.cache/apply-author';prepared=r/'.cache/wasm64-build/tree/src/apply.c';pristine=r/'nethack-c/upstream/src/apply.c'
for path in [prepared,pristine]:assert hashlib.sha256(path.read_bytes()).hexdigest()=='3599e3ce2ea7ce4dac10730dc1a5496114a363dc951d5c1f0289a8575b40e24b',('APPLY source changed',path)
source=prepared.read_text();core=(r/'js/ported/apply.js').read_text();runtime=(r/'js/nethack/bindings/apply.js').read_text();support=(r/'nethack-c/wasm/tu-fragments/apply-support.inc').read_text()
comments=re.findall(r'/\*.*?\*/',source,re.S);assert len(comments)==371
for comment in set(comments):assert source.count(comment)==core.count(comment),('Original APPLY comment multiplicity',comment)
F=json.loads((w/'functions.json').read_text());names=[f['name']for f in F]
assert len(F)==76 and sum(f.get('storageClass')!='static'for f in F)==28
assert re.findall(r'export function (\w+)\(',core)==names
for f in F:
 params=[p['name']for p in f.get('inner',[])if p.get('kind')=='ParmVarDecl']
 assert re.search(r'export function '+f['name']+r'\(([^)]*)\)',core)[1]==', '.join(params)
defs=json.loads((r/'nethack-c/wasm/compile-defines.json').read_text())
base=[str(r/'.cache/emsdk/upstream/emscripten/emcc'),'-sMEMORY64=1',*['-D'+d for d in defs],'-I'+str(r/'.cache/wasm64-build/tree/include')]
macro=subprocess.check_output(base+['-E','-dM','apply.c'],cwd=prepared.parent,text=True)
for flag in ['UNIX','DEBUG','MAIL','MAIL_STRUCTURES','STATUS_HILITES']:assert re.search(r'^#define '+flag+r'\b',macro,re.M),('APPLY profile changed',flag)
for empty in ['SetVoice','Soundeffect']:assert re.search(r'^#define '+empty+r'\([^)]*\)\s*$',macro,re.M)
assert 'C.SetVoice('not in core and 'C.Soundeffect('not in core
assert 'C.Hero_playnotes('not in core
fresh=json.loads(subprocess.check_output(base+['-fsyntax-only','-Xclang','-ast-dump=json','apply.c'],cwd=prepared.parent,text=True))
actual=[];b=prepared.read_bytes()
for node in fresh['inner']:
 if node.get('kind')!='FunctionDecl'or not any(c.get('kind')=='CompoundStmt'for c in node.get('inner',[])):continue
 at=node.get('loc',{}).get('offset',-1);name=node['name']
 if at>=0 and b[at:at+len(name)]==name.encode():actual.append(node)
assert [f['name']for f in actual]==names
def normalized(node):
 if isinstance(node,list):return[normalized(c)for c in node]
 if not isinstance(node,dict):return '<decl>'if isinstance(node,str)and re.fullmatch(r'0x[0-9a-f]+',node)else node
 return{k:normalized(v)for k,v in node.items()if k not in ['id','loc','range','previousDecl','referencedMemberDecl','typeAliasDeclId','targetLabelDeclId','declId']}
for old,new in zip(F,actual):assert normalized(old)==normalized(new),('APPLY actual full body/type/literal drift',old['name'])
assert comments==re.findall(r'/\*.*?\*/',core,re.S),'Original371 comment order/multiplicity'
def callee(n):
 while n.get('inner'):n=n['inner'][0]
 return n.get('referencedDecl',{}).get('name')
expected=set()
def walk(n,fn):
 if n.get('kind')=='CallExpr'and callee(n['inner'][0])=='rng_log_set_caller':
  values=[]
  def literals(c):
   if c.get('kind')in['StringLiteral','IntegerLiteral']:values.append(c['value'])
   for child in c.get('inner',[]):literals(child)
  for c in n['inner'][1:]:literals(c)
  assert values[0]=='"apply.c"';assert values[2].strip('"')==fn
  expected.add((int(values[1]),fn))
 for c in n.get('inner',[]):walk(c,fn)
for f in actual:walk(f,f['name'])
observed={(int(m[1]),names[int(m[2])])for m in re.finditer(r'C.rngSource\((\d+), (\d+)\)',core)}
assert observed==expected,('APPLY RNG source origin drift',observed^expected)
assert 'rng_log_set_caller("apply.c",line,fn)'in support
assert 'C.Maybe_Half_Phys('not in core and 'C.rn1('not in core
assert 'C.Half_physical_damage ?'in core
assert 'whipattack: {'in core and 'break whipattack;'in core and 'goto whipattack;'not in core
assert 'useup_jelly: {'in core and 'break useup_jelly;'in core and 'goto useup_jelly;'not in core
assert 'C.go.occupation == C.callbackAddress(set_trap)'in core
assert 'C.fieldRef(cc, "x")'in core and 'C.fieldRef(cc, "y")'in core
assert 'C.copyRecord(C.gb.bhitpos, cc)'in core and 'C.copyRecord(pos, mpos)'in core
assert '_test_'not in support,'Production APPLY support has private fixture imports'
aliases=json.loads(re.search(r'const fieldAliases=(\{[^\n]*\});',runtime)[1])
for name,value in [('oc_skill','oc_subtyp'),('oc_armcat','oc_subtyp'),('doormask','flags'),('ocarry','v.v_ocarry')]:
 assert aliases[name]==value;assert re.search(r'^#define '+name+' '+re.escape(value)+r'$',macro,re.M)
declaration=next(n for n in fresh['inner']if n.get('kind')=='FunctionDecl'and n.get('name')=='mksobj')
assert any(c.get('kind')=='ReturnsNonNullAttr'for c in declaration.get('inner',[]))
subprocess.check_call(['python3',str(w/'source-data.py')],cwd=r)
subprocess.check_call([str(r/'.cache/emsdk/node/24.19.0_64bit/bin/node'),str(w/'source-data.mjs')],cwd=r)
regenerated=w/'regenerated-core.js';subprocess.check_call(['python3',str(w/'port-core.py')],cwd=r,env={**os.environ,'APPLY_OUTPUT':str(regenerated)})
assert regenerated.read_bytes()==(r/'js/ported/apply.js').read_bytes(),'Readable APPLY source regeneration drift'
print('APPLY metadata PASS:76full bodies/28public48private/371orderedcomments/13static initializers/'+str(len(expected))+'RNG line+function origin pairs/typed aliases/native automatic refs')
