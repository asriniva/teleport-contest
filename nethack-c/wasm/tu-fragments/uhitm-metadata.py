"""UHITM original source/configured full-body/type/literal/data/ABI guards."""
from pathlib import Path
import hashlib,json,os,re,subprocess
r=Path(__file__).resolve().parents[3];SDK=Path(os.environ.get('EMSDK',str(r/'.cache/emsdk')));w=r/'.cache/uhitm-author';tools=r/'nethack-c/wasm/tu-fragments/tu137-group-a/uhitm-source-tools';outdir=Path(os.environ.get('UHITM_GUARD_WORK',str(r/'.cache/tu137-shadow-work/uhitm-guard'))).resolve();outdir.mkdir(parents=True,exist_ok=True);guard_env={**os.environ,'UHITM_GUARD_WORK':str(outdir)};prepared=r/'.cache/wasm64-build/tree/src/uhitm.c';pristine=r/'nethack-c/upstream/src/uhitm.c'
for path in [prepared,pristine]:assert hashlib.sha256(path.read_bytes()).hexdigest()=='4cc2f8a0ffe0121801a777978a9a555a063db720e0fe972308fb6ab0e96feb12',('UHITM source changed',path)
source=prepared.read_text();core=Path(os.environ.get('UHITM_GUARD_CORE',str(r/'js/ported/uhitm.js'))).read_text();runtime=(r/'js/nethack/bindings/uhitm.js').read_text();support=(r/'nethack-c/wasm/tu-fragments/uhitm-support.inc').read_text()
comments=re.findall(r'/\*.*?\*/',source,re.S);assert len(comments)==783
for comment in set(comments):assert source.count(comment)==core.count(comment),('Original UHITM comment multiplicity',comment)
F=json.loads((w/'functions.json').read_text());names=[f['name']for f in F]
assert len(F)==102 and sum(f.get('storageClass')!='static'for f in F)==65
assert re.findall(r'export function (\w+)\(',core)==names
for f in F:
 params=[p['name']for p in f.get('inner',[])if p.get('kind')=='ParmVarDecl']
 assert re.search(r'export function '+f['name']+r'\(([^)]*)\)',core)[1]==', '.join(params)
defs=json.loads((r/'nethack-c/wasm/compile-defines.json').read_text())
base=[str(SDK/'upstream/emscripten/emcc'),'-sMEMORY64=1',*['-D'+d for d in defs],'-I'+str(r/'.cache/wasm64-build/tree/include')]
macro=subprocess.check_output(base+['-E','-dM','uhitm.c'],cwd=prepared.parent,text=True)
for flag in ['UNIX','DEBUG','MAIL','MAIL_STRUCTURES','STATUS_HILITES']:assert re.search(r'^#define '+flag+r'\b',macro,re.M),('UHITM profile changed',flag)
for empty in ['SetVoice','Soundeffect']:assert re.search(r'^#define '+empty+r'\([^)]*\)\s*$',macro,re.M)
assert 'C.SetVoice('not in core and 'C.Soundeffect('not in core
assert 'C.Hero_playnotes('not in core
fresh=json.loads(subprocess.check_output(base+['-fsyntax-only','-Xclang','-ast-dump=json','uhitm.c'],cwd=prepared.parent,text=True))
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
for old,new in zip(F,actual):assert normalized(old)==normalized(new),('UHITM actual full body/type/literal drift',old['name'])
assert comments==re.findall(r'/\*.*?\*/',core,re.S),'Original783 comment order/multiplicity'
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
  assert values[0]=='"uhitm.c"';assert values[2].strip('"')==fn
  expected.add((int(values[1]),fn))
 for c in n.get('inner',[]):walk(c,fn)
for f in actual:walk(f,f['name'])
observed={(int(m[1]),names[int(m[2])])for m in re.finditer(r'C.rngSource\((\d+), (\d+)\)',core)}
assert observed==expected,('UHITM RNG source origin drift',observed^expected)
assert 'rng_log_set_caller("uhitm.c",line,fn)'in support
assert 'C.Maybe_Half_Phys('not in core and 'C.rn1('not in core
assert 'C.Half_physical_damage ?'in core
assert 'attack_dispatch: while (1)'in core and 'continue attack_dispatch;'in core
assert 'passivedone: {'in core and 'break passivedone;'in core
assert 'atk_done: {'in core and 'break atk_done;'in core
assert not re.search(r'\bgoto \w+;',re.sub(r'/\*.*?\*/','',core,flags=re.S))
assert 'C.fieldRef(hmd, "mdat")'in core and 'C.fieldRef(hmd, "dmg")'in core
assert 'C.arrayRef(sum, i)'in core and 'C.globalRef("uwep")'in core
assert '_test_'not in support,'Production UHITM support has private fixture imports'
aliases=json.loads(re.search(r'const fieldAliases=(\{[^\n]*\});',runtime)[1])
for name,value in aliases.items():assert re.search(r'^#define '+name+' '+re.escape(value)+r'$',macro,re.M),('UHITM field alias drift',name,value)
declaration=next(n for n in fresh['inner']if n.get('kind')=='FunctionDecl'and n.get('name')=='mksobj')
assert any(c.get('kind')=='ReturnsNonNullAttr'for c in declaration.get('inner',[]))
subprocess.check_call(['python3',str(tools/'source-data.py')],cwd=r,env=guard_env)
subprocess.check_call([str(SDK/'node/24.19.0_64bit/bin/node'),str(tools/'source-data.mjs')],cwd=r,env=guard_env)
regenerated=outdir/'regenerated-core.js';subprocess.check_call(['python3',str(tools/'port-core.py')],cwd=r,env={**guard_env,'UHITM_OUTPUT':str(regenerated)})
assert regenerated.read_text()==core,'Readable UHITM source regeneration drift'
print('UHITM metadata PASS:102 full bodies/65 public37 private/783 ordered comments/6 source static objects/'+str(len(expected))+' RNG line+function origins/typed aliases/native automatic refs')
