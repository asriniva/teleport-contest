"""READ original source/configured full-body/type/literal/data/ABI guards."""
from pathlib import Path
import hashlib,json,os,re,subprocess
r=Path(__file__).resolve().parents[3];w=r/'.cache/read-author';prepared=r/'.cache/wasm64-build/tree/src/read.c';pristine=r/'nethack-c/upstream/src/read.c'
for path in [prepared,pristine]:assert hashlib.sha256(path.read_bytes()).hexdigest()=='ec15ad773e50f5d466ddc20515b441c9ddb4e99449abd1f34fa43a14e6a8b2c4',('READ source changed',path)
source=prepared.read_text();core=(r/'js/ported/read.js').read_text();runtime=(r/'js/nethack/bindings/read.js').read_text();support=(r/'nethack-c/wasm/tu-fragments/read-support.inc').read_text()
comments=re.findall(r'/\*.*?\*/',source,re.S);assert len(comments)==367
for comment in set(comments):assert source.count(comment)==core.count(comment),('Original READ comment multiplicity',comment)
F=json.loads((w/'functions.json').read_text());names=[f['name']for f in F]
assert len(F)==62 and sum(f.get('storageClass')!='static'for f in F)==20
assert re.findall(r'export function (\w+)\(',core)==names
for f in F:
 params=[p['name']for p in f.get('inner',[])if p.get('kind')=='ParmVarDecl']
 assert re.search(r'export function '+f['name']+r'\(([^)]*)\)',core)[1]==', '.join(params)
defs=json.loads((r/'nethack-c/wasm/compile-defines.json').read_text())
base=[str(r/'.cache/emsdk/upstream/emscripten/emcc'),'-sMEMORY64=1',*['-D'+d for d in defs],'-I'+str(r/'.cache/wasm64-build/tree/include')]
macro=subprocess.check_output(base+['-E','-dM','read.c'],cwd=prepared.parent,text=True)
for flag in ['UNIX','DEBUG','MAIL','MAIL_STRUCTURES','STATUS_HILITES']:assert re.search(r'^#define '+flag+r'\b',macro,re.M),('READ profile changed',flag)
for empty in ['SetVoice','Soundeffect']:assert re.search(r'^#define '+empty+r'\([^)]*\)\s*$',macro,re.M)
assert 'C.SetVoice('not in core and 'C.Soundeffect('not in core
assert 'export function seffect_mail('in core and 'C.readmail(sobj)'in core
fresh=json.loads(subprocess.check_output(base+['-fsyntax-only','-Xclang','-ast-dump=json','read.c'],cwd=prepared.parent,text=True))
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
for old,new in zip(F,actual):assert normalized(old)==normalized(new),('READ actual full body/type/literal drift',old['name'])
def callee(n):
 while n.get('inner'):n=n['inner'][0]
 return n.get('referencedDecl',{}).get('name')
def origins(n,out):
 if n.get('kind')=='CallExpr'and callee(n['inner'][0])=='rng_log_set_caller':
  v=[]
  def values(c):
   if c.get('kind')in ['StringLiteral','IntegerLiteral']:v.append(c['value'])
   for child in c.get('inner',[]):values(child)
  for c in n['inner'][1:]:values(c)
  out.append((int(v[1]),v[2].strip('"')))
 for c in n.get('inner',[]):origins(c,out)
expected=[]
for f in F:origins(f,expected)
assert [(int(m[1]),m[2])for m in re.finditer(r'C.rngSource\((\d+), "(\w+)"\)',core)]==expected
assert 'rng_log_set_caller("read.c",line,fn)'in support
assert 'C.Snprintf("do_class_genocide", 2657,'in core and 'C.Snprintf("do_genocide", 2861,'in core
assert 'not_chargable: {'in core and 'break not_chargable;'in core and 'goto not_chargable;'not in core
assert 'sobj = C.localScalar("struct obj *", sobj)'in core and 'sobjp.value = 0;'in core
assert 'C.fieldRef(d, "which")'in core and 'C.localScalar("int", C.NEUTRAL)'in core
assert 'const is_lit = C.localScalar("char", 0)'in core
assert 's = C.char(scursed ? -otmp.spe : otmp.spe)'in core
assert 'Number(_teleport_read_data(i))'in(r/'nethack-c/wasm/tu-libraries/read.js').read_text()
assert 'static struct litmon *teleport_read_gremlins;'in support
assert 'returnRecords' in runtime and 'records[target]'in runtime
for name in ['mkobj','mksobj']:
 declaration=next(n for n in fresh['inner']if n.get('kind')=='FunctionDecl'and n.get('name')==name)
 assert any(c.get('kind')=='ReturnsNonNullAttr'for c in declaration.get('inner',[])),('READ record-return contract changed',name)
for name in ['can_center_cloud','display_stinking_cloud_positions','read_ok','set_lit']:
 assert 'teleport_read_callback_'+name in support
assert '_test_'not in support,'Production READ support must not reference private fixture imports'
aliases=json.loads(re.search(r'const fieldAliases=(\{[^\n]*\});',runtime)[1])
for name in ['oc_skill','oc_armcat']:
 assert aliases[name]=='oc_subtyp'
 assert re.search(r'^#define '+name+r' oc_subtyp$',macro,re.M)
subprocess.check_call(['python3',str(w/'source-data.py')],cwd=r)
subprocess.check_call([str(r/'.cache/emsdk/node/24.19.0_64bit/bin/node'),str(w/'source-data.mjs')],cwd=r)
regenerated=w/'regenerated-core.js';subprocess.check_call(['python3',str(w/'port-core.py')],cwd=r,env={**os.environ,'READ_OUTPUT':str(regenerated)})
assert regenerated.read_bytes()==(r/'js/ported/read.js').read_bytes(),'READ readable source regeneration drift'
print('READ metadata PASS:62full configured bodies/20public42private/367comments/7tables148entries/'+str(len(expected))+'exact RNG origins/typed aliases+nativeautomaticrefs')
