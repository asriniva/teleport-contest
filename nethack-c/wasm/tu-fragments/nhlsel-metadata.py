"""Read-only configured NHLSEL source/data/CPP/ABI guards, not equivalence proof."""
from pathlib import Path
import ast,json,re,subprocess
root=Path(__file__).resolve().parents[3];pristine=root/'nethack-c/upstream/src/nhlsel.c';prepared=root/'.cache/wasm64-build/tree/src/nhlsel.c';source=pristine.read_text();assert pristine.read_bytes()==prepared.read_bytes(),'Review changed prepared NHLSEL source'
core=(root/'js/ported/nhlsel.js').read_text();runtime=(root/'js/ported/nhlsel-runtime.js').read_text();library=(root/'nethack-c/wasm/tu-libraries/nhlsel.js').read_text();support=(root/'nethack-c/wasm/tu-fragments/nhlsel-support.inc').read_text();probe=(root/'scripts/tu-nhlsel-probe.c').read_text()
for c in set(re.findall(r'/\*.*?\*/',source,re.S)):assert source.count(c)==core.count(c),('Original comment multiplicity changed',c)
clean=lambda s:re.sub(r'/\*.*?\*/|//[^\n]*','',s,flags=re.S)
c=clean(source);j=clean(core);literals=sorted(set(ast.literal_eval(x) for x in re.findall(r'"(?:\\.|[^"\\])*"',c)));capacity=sum(len(x.encode())+1 for x in literals)
assert json.loads(re.search(r'var sourceLiterals=new Set\((\[[^\n]*\])\);',library)[1])==literals
assert int(re.search(r'teleport_nhlsel_literals\[(\d+)\]',support)[1])==capacity
assert '!sourceLiterals.has(v)' in library
for name,length in [('growdirs',7),('gradtypes',3)]:
 a=re.search(name+r'\[\] = \{(.*?)\};',c,re.S)[1];b=re.search(r'const '+name+r' = \[(.*?)\];',j,re.S)[1]
 norm=lambda t:[ast.literal_eval(s) if s.startswith('"') else 0 for s in re.findall(r'"(?:\\.|[^"\\])*"|NULL|\b0\b',t)]
 assert norm(a)==norm(b) and len(norm(a))==length,('Changed source string options',name)
for name in ['growdirs2i','gradtypes2i']:
 a=re.search(name+r'\[\] = \{(.*?)\};',c,re.S)[1];b=re.search(r'const '+name+r' = \[(.*?)\];',j,re.S)[1]
 assert re.sub(r'\s+','',a)==re.sub(r'\s+','',b.replace('C.','')),('Changed source option values',name)
configured_callbacks=set()
for name,length in [('l_selection_methods',25),('l_selection_meta',9)]:
 a=re.search(name+r'\[\] = \{(.*?)\n};',c,re.S)[1];b=re.search(r'export const '+name+r' = \[(.*?)\n];',j,re.S)[1]
 expected=[(ast.literal_eval(k) if k!='NULL' else 0,f if f!='NULL' else 0) for k,f in re.findall(r'\{\s*("[^"]*"|NULL),\s*(\w+)\s*}',a)]
 actual=[(ast.literal_eval(k) if k!='0' else 0,f if f!='0' else 0) for k,f in re.findall(r'\[\s*("[^"]*"|0),\s*(\w+)\s*]',b)]
 assert expected==actual and len(actual)==length,('Changed source Lua catalogue',name)
 configured_callbacks|={f for k,f in actual if f}
assert len(configured_callbacks)==28
assert not re.search(r'\b(?:rn2|rnd|rn1|d)\(',c),'Review newly introduced source RNG calls'
import sys
sys.path.insert(0,str(root/'scripts'))
from golden_emscripten_profile import c_flags
base=[str(root/'.cache/emsdk/upstream/emscripten/emcc'),*c_flags(root)]
macros=subprocess.check_output([*base,'-E','-dM',str(prepared)],text=True)
for text in ['#define LUA_VERSION_NUM 504','#define LUA_VERSION_RELEASE "8"','#define LUA_INTEGER long long','#define LUA_NUMBER double','#define SP_COORD_PACK(x,y) (((x) & 0xff) + (((y) & 0xff) << 16))','#define SP_COORD_PACK_RANDOM(f) (SP_COORD_IS_RANDOM | (f))','#define SP_COORD_IS_RANDOM 0x01000000L','#define lua_newuserdata(L,s) lua_newuserdatauv(L,s,1)','#define lua_pop(L,n) lua_settop(L, -(n)-1)','#define lua_remove(L,idx) (lua_rotate(L, (idx), -1), lua_pop(L, 1))','#define luaL_checkstring(L,n) (luaL_checklstring(L, (n), NULL))','#define luaL_getmetatable(L,n) (lua_getfield(L, LUA_REGISTRYINDEX, (n)))','#define luaL_newlib(L,l) (luaL_checkversion(L), luaL_newlibtable(L,l), luaL_setfuncs(L,l,0))','#define luaL_newlibtable(L,l) lua_createtable(L, 0, sizeof(l)/sizeof((l)[0]) - 1)']:assert text in macros,('Changed header/Lua macro',text)
a=json.loads(subprocess.check_output([*base,'-fsyntax-only','-Xclang','-ast-dump=json',str(prepared)],text=True));functions=[];types={};records={}
for n in a['inner']:
 if n.get('kind')=='TypedefDecl' and n.get('name') in ['coordxy','boolean','lua_Integer','lua_Number']:types[n['name']]=n['type'].get('desugaredQualType',n['type']['qualType'])
 if n.get('kind')=='RecordDecl':records[n.get('name')]={i['name']:i['type']['qualType'] for i in n.get('inner',[]) if i.get('kind')=='FieldDecl' and i.get('name')}
 if n.get('kind')=='FunctionDecl' and n.get('loc',{}).get('includedFrom') is None and any(i.get('kind')=='CompoundStmt' for i in n.get('inner',[])):
  off=n['loc'].get('offset',-1)
  if off>=0 and source[off:off+len(n['name'])]==n['name']:functions.append(n)
assert types=={'coordxy':'short','boolean':'signed char','lua_Number':'double','lua_Integer':'long long'},types
for name,expected in {'selectionvar':{'wid':'int','hei':'int','bounds_dirty':'boolean','bounds':'NhRect','map':'char *'},'nhrect':{'lx':'coordxy','ly':'coordxy','hx':'coordxy','hy':'coordxy'},'mkroom':{'lx':'coordxy','ly':'coordxy'},'rm':{'typ':'schar'},'luaL_Reg':{'name':'const char *','func':'lua_CFunction'},'sp_coder':{'croom':'struct mkroom *'}}.items():
 for field,t in expected.items():assert records[name][field]==t,('Changed native field type',name,field)
assert len(functions)==33 and [n['name'] for n in functions]==re.findall(r'export function (\w+)\(',core)
assert sum(n.get('storageClass')=='static' for n in functions)==30
callbacks=[n['name'] for n in functions if n.get('storageClass')=='static' and n['type']['qualType']=='int (lua_State *)'];assert set(callbacks)==configured_callbacks
assert json.loads(re.search(r'export const callbackNames = (\[[^\n]*\]);',core)[1])==callbacks
for name in callbacks:assert f'extern int teleport_nhlsel_{name}(lua_State *);' in support and f'teleport_nhlsel_{name}__sig:\'ip\'' in library
for name in ['l_selection_push_new','params_sel_2coords']:assert f'teleport_nhlsel_test_{name}__deps' in library
assert 'static luaL_Reg teleport_nhlsel_methods[25],teleport_nhlsel_meta[9];' in support
assert 'source[k]===fn' in runtime and 'services.luaL_setfuncs(state,p,0)' in runtime
assert 'withRefs' in runtime and 'finally{services.stackRestore(saved);}' in runtime
assert 'NHLSEL_VALIDATE_REFERENCE' in probe
assert 'TELEPORT_NATIVE_TESTS' in (root/'scripts/test-tu-nhlsel.mjs').read_text()
print(f'NHLSEL metadata:33 bodies/3 public/30 private,28 active callback identities,25+9 registration rows,7+3 option rows,98 comments,{len(literals)} source literals/{capacity} bytes,zero TU RNG,actual Lua5.4.8 macros and field/typedef widths verified; unary UAF parity remains unresolved.')
