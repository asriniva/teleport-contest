"""Read-only MAKEMON configured inventory/provenance/source/header/ABI guards."""
from pathlib import Path
import hashlib,json,re,subprocess,os
r=Path(__file__).resolve().parents[3];w=r/'.cache/makemon-author';prepared=r/'.cache/wasm64-build/tree/src/makemon.c';pristine=r/'nethack-c/upstream/src/makemon.c';source=prepared.read_text();core=(r/'js/ported/makemon.js').read_text();runtime=(r/'js/ported/makemon-runtime.js').read_text();library=(r/'nethack-c/wasm/tu-libraries/makemon.js').read_text();support=(r/'nethack-c/wasm/tu-fragments/makemon-support.inc').read_text()
for path in [prepared,pristine]:assert hashlib.sha256(path.read_bytes()).hexdigest()=='04bb46b793cb7a724544ed5860f57116e4661ce5d052a1321d90dc0167d3ffc3',('Review MAKEMON source change',path)
comments=re.findall(r'/\*.*?\*/',source,re.S);assert len(comments)==279
for c in set(comments):assert source.count(c)==core.count(c),('Original MAKEMON comment multiplicity',c)
F=json.loads((w/'functions.json').read_text());names=[f['name']for f in F];assert len(names)==41 and sum(f.get('storageClass')!='static'for f in F)==28
assert re.findall(r'export function (\w+)\(',core)==names
for f in F:
 expected=[x['name']for x in f.get('inner',[])if x.get('kind')=='ParmVarDecl'];expected=['class_'if n=='class'else n for n in expected];assert re.search(r'export function '+f['name']+r'\(([^)]*)\)',core)[1]==', '.join(expected),('MAKEMON parameters',f['name'])
def callee(n):
 while n.get('inner'):n=n['inner'][0]
 return n.get('referencedDecl',{}).get('name')
def logs(n,out):
 if n.get('kind')=='CallExpr'and callee(n['inner'][0])=='rng_log_set_caller':
  v=[]
  def values(c):
   if c.get('kind')in ['StringLiteral','IntegerLiteral']:v.append(c['value'])
   for q in c.get('inner',[]):values(q)
  for c in n['inner'][1:]:values(c)
  out.append((int(v[1]),v[2].strip('"')))
 for c in n.get('inner',[]):logs(c,out)
expected=[]
for f in F:logs(f,expected)
assert [(int(m[1]),m[2])for m in re.finditer(r'C.rngSource\((\d+), "(\w+)"\)',core)]==expected
assert len(re.findall(r'\bC\.(?:rn2|rn1|rnd|d)\(',re.sub(r'/\*.*?\*/|//[^\n]*','',core,flags=re.S)))==len(expected)
assert re.search(r'C\.rngSource\(\d+, "\w+"\), C\.(rn2|rnd|d|rn1)\(',core)
assert 'rng_log_set_caller("makemon.c",line,fn)'in support
assert 'return(rn2)(n)'in support and 'rng_log'not in re.search(r'int teleport_makemon_rn2\([^}]+}',support)[0]
assert 'gotgood: {'in core and 'assign_sym: {'in core and 'goto gotgood;'not in core and 'goto assign_sym;'not in core
assert 'C.copyRecord(m2, mon, C.monsterSize)'in core
assert 'C.copyRecord(C.EMIN(m2), C.EMIN(mon), C.eminSize)'in core
assert 'C.copyRecord(C.EDOG(m2), C.EDOG(mon), C.edogSize)'in core
assert 'C.copyRecord(mex, C.zeromextra, C.mextraSize)'in core
assert 'C.callLocal('in core and 'finally{services.stackRestore(saved);}'in runtime
for logical in ['!C.is_male(ptr) && !C.is_neuter(ptr)', '!C.is_female(ptr) && !C.is_neuter(ptr)', 'C.wizard && !neverask', 'C.In_endgame(C.u.uz) && !C.Is_astralevel(C.u.uz)']:
 assert 'Number(Boolean('+logical+'))'in core,('Stored C logical-result canonicalization',logical)
assert 'if (C.showdebug("makemon.c"))'in core and 'C.debugpline'not in core
assert "'opoisoned':"not in runtime # JSON aliases use exact compiler macro field names, below
aliases=json.loads(re.search(r'const fieldAliases=(\{[^\n]*\});',runtime)[1]);assert aliases['opoisoned']=='otrapped'and aliases['oc_skill']=='oc_subtyp'and aliases['a_ac']=='oc_oc1'
assert 'static int teleport_makemon_mongen_order[NUMMONS]'in support and 'static xint8 teleport_makemon_mclass_maxf[MAXMCLASSES]'in support
assert 'cmp_init_mongen_order('not in support.replace('teleport_makemon_private_cmp cmp_init_mongen_order','')
# Re-run actual compiler inventory from production cwd+basename; no filename normalization.
defs=json.loads((r/'nethack-c/wasm/compile-defines.json').read_text());base=[str(r/'.cache/emsdk/upstream/emscripten/emcc'),'-sMEMORY64=1',*['-D'+x for x in defs],'-I'+str(r/'.cache/wasm64-build/tree/include')]
macros=subprocess.check_output([*base,'-E','-dM','makemon.c'],cwd=prepared.parent,text=True)
for key in ['DEBUG','UNIX','DEBUG_MIGRATING_MONS','MAIL_STRUCTURES']:assert re.search(r'^#define '+key+r'\b',macros,re.M),('Changed MAKEMON profile',key)
for key,val in {'opoisoned':'otrapped','oc_skill':'oc_subtyp','a_ac':'oc_oc1'}.items():assert re.search(r'^#define '+key+r' '+val+r'$',macros,re.M),('Changed field macro',key)
assert '#define qsort(base,nmemb,size,compar) nh_deterministic_qsort((base), (nmemb), (size), (compar))'in macros
cpp=subprocess.check_output([*base,'-E','makemon.c'],cwd=prepared.parent,text=True);assert '"makemon.c"'in cpp
A=json.loads(subprocess.check_output([*base,'-fsyntax-only','-Xclang','-ast-dump=json','makemon.c'],cwd=prepared.parent,text=True));actual=[];b=prepared.read_bytes()
for n in A['inner']:
 if n.get('kind')!='FunctionDecl'or not any(c.get('kind')=='CompoundStmt'for c in n.get('inner',[])):continue
 name=n['name'];offset=n.get('loc',{}).get('offset',-1)
 if offset<0 or b[offset:offset+len(name)]!=name.encode():continue
 actual.append(name)
assert actual==names,('Changed configured MAKEMON bodies',actual)
def normalized(node):
 if isinstance(node,list):return [normalized(c)for c in node]
 if not isinstance(node,dict):return '<decl>'if isinstance(node,str)and re.fullmatch(r'0x[0-9a-f]+',node)else node
 return {k:normalized(v)for k,v in node.items()if k not in ['id','loc','range','previousDecl','referencedMemberDecl','typeAliasDeclId','targetLabelDeclId','declId']}
fresh={n['name']:n for n in A['inner']if n.get('kind')=='FunctionDecl'and n.get('name')in names and any(c.get('kind')=='CompoundStmt'for c in n.get('inner',[]))}
for f in F:assert normalized(fresh[f['name']])==normalized(f),('Changed configured MAKEMON complete body/types/literals',f['name'])
assert re.search(r'^#define NH_DEVEL_STATUS NH_STATUS_RELEASED$',macros,re.M)
for key in ['SPECIALIZATION','HPUX','DGUX']:assert not re.search(r'^#define '+key+r'\b',macros,re.M),('Changed MAKEMON branch',key)
assert 'C.samePtr(ptr, C.mons[C.PM_MAIL_DAEMON])'in core

assert 'check_mongen_order'not in actual
regenerated=w/'regenerated-core.js';subprocess.check_call(['python3',str(w/'port-core.py')],cwd=r,env={**os.environ,'MAKEMON_OUTPUT':str(regenerated)});assert regenerated.read_bytes()==(r/'js/ported/makemon.js').read_bytes(),'MAKEMON readable source regeneration drift'
print(f'MAKEMON metadata PASS:41 bodies/28public+13private/279 comments/{len(expected)} exact compiler RNG origins; source/profile/aliases/data/automatic lifetime guarded.')
