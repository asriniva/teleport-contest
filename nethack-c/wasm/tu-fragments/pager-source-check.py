"""Configured-source/ABI/macro guard; not a behavior-equivalence proof."""
from pathlib import Path
import re,json,subprocess,hashlib
R=Path(__file__).resolve().parents[3];F=Path(__file__).parent;D=json.loads((F/'pager-source-data.json').read_text());tree=R/'.cache/wasm64-build/tree';source=tree/'src/pager.c';js=(R/'js/ported/pager.js').read_text()
assert source.read_bytes()==(R/'nethack-c/upstream/src/pager.c').read_bytes(),'prepared/pristine provenance changed'
assert hashlib.sha256(source.read_bytes()).hexdigest()==D['sourceSha256'],'source changed: review every source-owned body/data'
base=[str(R/'.cache/emsdk/upstream/emscripten/emcc'),'-sMEMORY64=1','-I'+str(tree/'include'),'-I'+str(R/'.cache/ncurses-wasm64-build/include'),'-include',str(R/'nethack-c/wasm/native-terminal.h')]+['-D'+x for x in json.loads((R/'nethack-c/wasm/compile-defines.json').read_text())]+['pager.c']
p=subprocess.check_output(base+['-E'],cwd=tree/'src',text=True);active=False;lines=[]
for line in p.splitlines():
 m=re.match(r'^# \d+ "([^"]+)"',line)
 if m:active=m[1]=='pager.c'
 elif active:lines.append(line)
cpp='\n'.join(lines);a=json.loads(subprocess.check_output(base+['-fsyntax-only','-Xclang','-ast-dump=json'],cwd=tree/'src',text=True));mac=subprocess.check_output(base+['-E','-dM'],cwd=tree/'src',text=True)
for n in D['active']:assert re.search(r'^#define '+n+r'\b',mac,re.M),n+' inactive'
for n in D['inactive']:assert not re.search(r'^#define '+n+r'\b',mac,re.M),n+' active'
clean=re.sub(r'/\*[\s\S]*?\*/|//[^\n]*','',js);names=re.findall(r'export function (\w+)\(',clean);assert names==D['names'],'original function order/boundaries changed'
for n in names:
 params=re.search(r'export function '+n+r'\(([^)]*)\)',clean)[1];assert [s.strip()for s in params.split(',')if s.strip()]==[x[0]for x in D['functions'][n]['args']],n+' parameters changed'
for comment in re.findall(r'/\*[\s\S]*?\*/',source.read_text()):assert comment in js,'original comment missing: '+comment[:100]
for node in a['inner']:
 if node.get('kind')=='FunctionDecl' and node.get('name')in names and any(x.get('kind')=='CompoundStmt'for x in node.get('inner',[])):
  name=node['name'];expected=D['functions'][name]
  assert node['type']['qualType']==expected['type']['qualType'],name+' configured return/signature changed'
  actualparams=[(v.get('name'),{k:v['type'][k]for k in ['qualType','desugaredQualType']if k in v['type']})for v in node.get('inner',[])if v.get('kind')=='ParmVarDecl']
  expectedparams=[(n,{k:t[k]for k in ['qualType','desugaredQualType']if k in t})for n,t in expected['args']]
  assert actualparams==expectedparams,name+' configured parameter typedef/signedness changed'
  assert (node.get('storageClass')=='static')==(name in D['private']),name+' compiler linkage changed'
actual=[]
def walk(n,owner=None):
 if n.get('kind')=='FunctionDecl'and n.get('name')in names and any(x.get('kind')=='CompoundStmt'for x in n.get('inner',[])):owner=n['name']
 if owner and n.get('kind')=='MemberExpr':
  inner=n.get('inner',[]);actual.append([owner,n.get('name'),n.get('type',{}).get('desugaredQualType',n.get('type',{}).get('qualType')),bool(n.get('isArrow')),inner[0].get('type',{}).get('qualType')if inner else''])
 for x in n.get('inner',[]):walk(x,owner)
walk(a);assert sorted(actual,key=str)==D['memberExprs'],'configured MemberExpr/typedef/member-macro alias changed'
snprintfsites=[]
for m in re.finditer(r'nh_snprintf\(__func__, (\d+),',cpp):
 owner=max((re.search(r'\n'+n+r'\(',cpp).start(),n)for n in names if re.search(r'\n'+n+r'\(',cpp).start()<m.start())[1];snprintfsites.append([owner,int(m[1])])
assert snprintfsites==D['snprintfSites'],'original Snprintf closing-line/function metadata changed'
assert [[m[1],int(m[2])]for m in re.finditer(r'C\.Snprintf\("(\w+)", (\d+),',js)]==snprintfsites,'JS Snprintf origin differs from actual CPP'
pointerops=[]
def ptrwalk(n,owner=None):
 if n.get('kind')=='FunctionDecl'and n.get('name')in names and any(x.get('kind')=='CompoundStmt'for x in n.get('inner',[])):owner=n['name']
 if owner and ((n.get('kind')=='CompoundAssignOperator')or(n.get('kind')=='UnaryOperator'and n.get('opcode')in['++','--']))and '*'in n.get('type',{}).get('qualType',''):pointerops.append([owner,n['kind'],n['opcode'],n['type']['qualType']])
 for x in n.get('inner',[]):ptrwalk(x,owner)
ptrwalk(a);assert pointerops==D['pointerOps'],'configured pointer arithmetic changed; review native element scaling'
assert all(x[3]=='char *'for x in pointerops),'PAGER pointer arithmetic now needs nonbyte element scale'
assert re.search(r'^#define DUMMY \{ 0 \}$',mac,re.M),'automatic aggregate initializer changed'
assert 'rng_log_set_caller' not in cpp,'PAGER gained configured source-owned RNG origins'
for n in ['suptext1','suptext2','icetyp']:
 table=re.search(r'const '+n+r' = (?:C.staticStrings\("ice_descr.icetyp", )?\[([\s\S]*?)\n\s*\](?:\))?;',clean)[1]
 actual=[json.loads(x[0])for x in re.finditer(r'"(?:\\.|[^"\\])*"',table)]
 assert actual==D[n],n+' source table changed'
rows=re.search(r'const help_menu_items = \[([\s\S]*?)\n\];',clean)[1]
actual=[[m[1],json.loads(m[2])]for m in re.finditer(r'\{ f: "(\w+)", text: ("(?:\\.|[^"\\])*") \}',rows)]
assert actual==D['helpMenu'],'source help callbacks/text/order changed'
assert re.search(r'export const what_is_a_location = '+re.escape(json.dumps(D['publicInitializer']))+r';',clean),'public initializer changed'
assert 'const char what_is_a_location[30];'in(F/'pager-storage.c').read_text(),'public storage must remain zero-only and separate'
assert not re.search(r'^const char what_is_a_location\[', (F/'pager-support.c').read_text(),re.M),'same-TU public const backing could fold native reads'
for n,v in D['staticStrings'].items():
 if '.'in n:assert 'C.staticString('+json.dumps(n)+', '+json.dumps(v)+')'in js,(n,'declared private static data changed')
 else:assert (json.dumps(v)in(R/'js/nethack/bindings/pager.js').read_text() or repr(v)in(R/'js/nethack/bindings/pager.js').read_text()),n+' initializer missing'
assert 'mon_to_glyph(u.ustuck,a1)'in(F/'pager-support.c').read_text(),'header must retain live original global expression'
assert 'coord cc' in cpp and 'coord cc' in cpp[cpp.index('add_cmap_descr('):],'coord byvalue source profile changed'
print('PAGER configured source guard passed: 46 names/order/params/linkage, all comments, %d MemberExpr/alias/width records, zero logged RNG sites, original tables/static/public data and CPP profile.'%len(D['memberExprs']))
