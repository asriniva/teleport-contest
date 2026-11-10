"""Configured-source/ABI/macro guard; not a behavior-equivalence proof."""
from pathlib import Path
import re,json,subprocess,hashlib
R=Path(__file__).resolve().parents[3];F=Path(__file__).parent;D=json.loads((F/'teleport-source-data.json').read_text());tree=R/'.cache/wasm64-build/tree';source=tree/'src/teleport.c';js=(R/'js/ported/teleport.js').read_text()
assert source.read_bytes()==(R/'nethack-c/upstream/src/teleport.c').read_bytes(),'prepared/pristine provenance changed'
assert hashlib.sha256(source.read_bytes()).hexdigest()==D['sourceSha256'],'source changed: review every source-owned body/data'
base=[str(R/'.cache/emsdk/upstream/emscripten/emcc'),'-sMEMORY64=1','-I'+str(tree/'include'),'-I'+str(R/'.cache/ncurses-wasm64-build/include'),'-include',str(R/'nethack-c/wasm/native-terminal.h')]+['-D'+x for x in json.loads((R/'nethack-c/wasm/compile-defines.json').read_text())]+['teleport.c']
p=subprocess.check_output(base+['-E'],cwd=tree/'src',text=True);active=False;lines=[]
for line in p.splitlines():
 m=re.match(r'^# \d+ "([^"]+)"',line)
 if m:active=m[1]=='teleport.c'
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
rng=[]
for m in re.finditer(r'rng_log_set_caller\("teleport.c", (\d+), __func__\)',cpp):
 owner=max(( (re.search(r'\n'+n+r'\(',cpp).start(),n)for n in names if re.search(r'\n'+n+r'\(',cpp).start()<m.start()))[1];rng.append([int(m[1]),owner])
assert rng==D['rngSites'],'actual full-filename RNG origin inventory changed'
# Lazy source RNG calls must carry those exact origin records.
jsrng=[[int(m[1]),m[2]]for m in re.finditer(r'C\.(?:rn2|rnd|rnl|rn1)\([^;]*?, (\d+), "(\w+)"\)',clean)]
assert jsrng==rng,'JS RNG caller/closing-line metadata changed'
tports=re.search(r'const tports = C.staticData\("dotelecmd.tports", \(\)=>\[([\s\S]*?)\n        \]\);',js)[1]
actualtable=[[int(m[1]),json.loads(m[2])]for m in re.finditer(r'menulet: (\d+), menudesc: ("(?:\\.|[^"\\])*")',tports)]
assert actualtable==D['tports'],'source-owned menu table changed'
assert 'const get_there_from = C.literal('+json.dumps(D['getThere'])+');' in js
assert len(D['getThere'].encode())+1==19
assert 'static char teleport_teleport_literals[' in (F/'teleport-support.c').read_text()
print('TELEPORT source guard: 37 functions, all original comments, 1108 configured MemberExpr/alias/width records, 22 full-origin RNG sites, menu/static data and CPP provenance passed.')
