"""Read-only TOPTEN configured source/table/ABI/provenance guards."""
from pathlib import Path
import ast,json,re,subprocess
root=Path(__file__).resolve().parents[3]
source=(root/'nethack-c/upstream/src/topten.c').read_text();prepared=root/'.cache/wasm64-build/tree/src/topten.c'
assert source==prepared.read_text(),'Review changed prepared TOPTEN source'
core=(root/'js/ported/topten.js').read_text();library=(root/'nethack-c/wasm/tu-libraries/topten.js').read_text();support=(root/'nethack-c/wasm/tu-fragments/topten-support.inc').read_text();runtime=(root/'js/ported/topten-runtime.js').read_text();layout=(root/'scripts/tu-topten-layout.h').read_text();probe=(root/'scripts/tu-topten-probe.c').read_text()
clean=re.sub(r'/\*.*?\*/|//[^\n]*',lambda m:'\n'*m[0].count('\n'),source,flags=re.S)
for comment in set(re.findall(r'/\*.*?\*/',source,re.S)):
 assert source.count(comment)==core.count(comment),('Original comment multiplicity changed',comment)
js_clean=re.sub(r'/\*.*?\*/|//[^\n]*','',core,flags=re.S)
literals=sorted(set(ast.literal_eval(x) for x in re.findall(r'"(?:\\.|[^"\\])*"',clean)));capacity=sum(len(x.encode())+1 for x in literals)
assert json.loads(re.search(r'var sourceLiterals=new Set\((\[[^\n]*\])\);',library)[1])==literals
assert int(re.search(r'teleport_topten_literals\[(\d+)\]',support)[1])==capacity
assert '!sourceLiterals.has(v)' in library
# Preserve exact source prefix strings and every configured static parse/print fmt.
c=re.search(r'killed_by_prefix\[\] = \{(.*?)\};',clean,re.S)[1]
j=re.search(r'const killed_by_prefix = (\[.*?\]);',js_clean,re.S)[1]
assert [ast.literal_eval(x) for x in re.findall(r'"(?:\\.|[^"\\])*"',c)]==ast.literal_eval(j)
defs=json.loads((root/'nethack-c/wasm/compile-defines.json').read_text());base=[str(root/'.cache/emsdk/upstream/emscripten/emcc'),'-sMEMORY64=1',*[f'-D{x}' for x in defs],'-I'+str(root/'.cache/wasm64-build/tree/include')]
cpp=subprocess.check_output([*base,'-E',str(prepared)],text=True);macros=subprocess.check_output([*base,'-E','-dM',str(prepared)],text=True)
for name,value in {'LOGFILE':1,'XLOGFILE':1,'HANGUPHANDLING':1,'UPDATE_RECORD_IN_PLACE':0,'NO_SCAN_BRACK':0,'DLB':0,'AMIGA':0,'VMS':0,'TOS':0}.items():assert bool(re.search(r'^#define '+name+r'\b',macros,re.M))==bool(value),('Review changed configured TOPTEN profile',name)
assert re.search(r'^#define NAMSZ 10$',macros,re.M),'Review configured name width'
header=(root/'.cache/wasm64-build/tree/include/hack.h').read_text()
assert '#define rn1(x, y) (rn2(x) + (y))' in header,'Review changed rn1 header expansion'
active=False;lines=[]
for line in cpp.splitlines():
 m=re.match(r'^# \d+ "([^"\n]+)"',line)
 if m:active=m[1]==str(prepared)
 elif active:lines.append(line)
configured='\n'.join(lines)
functions=re.findall(r'export function (\w+)\(',core);assert len(functions)==24
# Delimit functions by the actual original name followed by its complete body.
def cbody(name):
 m=re.search(r'\b'+name+r'\([^;{}]*\)\s*\{',configured,re.S);assert m,name
 pos=m.end();depth=1;quoted=False;escaped=False
 while depth:
  ch=configured[pos]
  if quoted:
   if escaped:escaped=False
   elif ch=='\\':escaped=True
   elif ch==quoted:quoted=False
  elif ch in ['"',"'"]:quoted=ch
  else:depth+=(ch=='{')-(ch=='}')
  pos+=1
 return configured[m.end():pos-1]
def jsbody(name):
 i=js_clean.index('export function '+name+'(');end=js_clean.find('export function ',i+1);return js_clean[i:end if end>=0 else len(js_clean)]
fmt_count=0
for name in ['readentry','writeentry']:
 expected=[(n,ast.literal_eval(s)) for n,s in re.findall(r'static const char (fmt\w*)\[\]\s*=\s*("(?:\\.|[^"\\])*");',cbody(name))]
 actual=[(n,ast.literal_eval(s)) for n,s in re.findall(r'const (fmt\w*)\s*=\s*("(?:\\.|[^"\\])*");',jsbody(name))]
 assert actual==expected,('Changed configured record formats',name,expected,actual);fmt_count+=len(expected)
assert fmt_count==7
expected_cases=re.findall(r'case (ACH_\w+):',cbody('encode_extended_achievements'));actual_cases=re.findall(r'case C\.(ACH_\w+):',jsbody('encode_extended_achievements'));assert actual_cases==expected_cases
expected_values=re.findall(r'achievement\s*=\s*("[^"]*")',cbody('encode_extended_achievements'));actual_values=re.findall(r'achievement\s*=\s*("[^"]*")',jsbody('encode_extended_achievements'));assert actual_values==expected_values
expected_conducts=re.findall(r'add_achieveX\(buf,\s*("[^"]*"),\s*([^;]+)\);',cbody('encode_extended_conducts'));actual_conducts=re.findall(r'add_achieveX\(buf,\s*("[^"]*"),\s*([^;]+)\);',jsbody('encode_extended_conducts'))
normalize=lambda s:re.sub(r'\s+','',s.replace('C.',''))
assert [(a,normalize(b)) for a,b in actual_conducts]==[(a,normalize(b)) for a,b in expected_conducts]
# Actual compiler __func__/__LINE__ expansion, including source header macros.
assert re.findall(r'nh_snprintf\(__func__,\s*(\d+),',configured)==['1082']
assert 'C.Snprintf(1082,' in core
origins=re.findall(r'Strlen_\([^;\n]*__func__,\s*(\d+)\)',configured)
assert origins==['123','1083','1208'],origins
assert re.findall(r'C\.Strlen\([^\n]*?,\s*(\d+),\s*"(\w+)"\)',core)==[('123','formatkiller'),('1083','outentry'),('1208','prscore')]
assert 'return Strlen_(s,names[fn],line)' in support
# Preserve all original RNG sites: rn1 header expansion is actual rn2+base.
current='';sites=[]
for line,text in enumerate(clean.splitlines(),1):
 m=re.match(r'^(\w+)\(',text)
 if m and m[1] in functions:current=m[1]
 for call in re.finditer(r'\b(rnd|rn1|rn2)\(',text):sites.append((call[1],line,current))
actual=[]
for m in re.finditer(r'\bC\.(rnd|rn1|rn2)\(',core):
 pos=m.end();depth=1
 while depth:depth+=(core[pos]=='(')-(core[pos]==')');pos+=1
 origin=re.search(r',\s*(\d+),\s*"(\w+)"\s*$',core[m.end():pos-1]);assert origin
 actual.append((m[1],int(origin[1]),origin[2]))
assert actual==sites
assert 'default:return(rn2)(n)+base' in support
# Derive fixed printf ABI shapes from actual configured compiler argument types.
a=json.loads(subprocess.check_output([*base,'-fsyntax-only','-Xclang','-ast-dump=json',str(prepared)],text=True));shapes=[''];private=[]
records=[x for x in a['inner'] if x.get('kind')=='RecordDecl' and x.get('name')=='toptenentry' and x.get('completeDefinition')]
assert len(records)==1
actual_fields={x['name']:x['type']['qualType'] for x in records[0]['inner'] if x.get('kind')=='FieldDecl'}
expected_fields={'tt_next':'struct toptenentry *','points':'long',**{n:'int' for n in 'deathdnum deathlev maxlvl hp maxhp deaths ver_major ver_minor patchlevel uid'.split()},'deathdate':'long','birthdate':'long',**{n:'char[4]' for n in 'plrole plrace plgend plalign'.split()},'name':'char[11]','death':'char[101]'}
assert actual_fields==expected_fields,('Review changed original record signedness/types',actual_fields)
for fn in a['inner']:
 if fn.get('kind')!='FunctionDecl' or fn.get('name') not in functions or not any(x.get('kind')=='CompoundStmt' for x in fn.get('inner',[])):continue
 off=fn.get('loc',{}).get('offset',-1)
 if off<0 or source[off:off+len(fn['name'])]!=fn['name']:continue
 if fn.get('storageClass')=='static':private.append(fn['name'])
 def walk(node):
  if node.get('kind')=='CallExpr':
   callee=node.get('inner',[{}])[0]
   while callee.get('inner'):callee=callee['inner'][0]
   name=callee.get('referencedDecl',{}).get('name');skips={'sprintf':2,'fprintf':2,'raw_printf':1,'impossible':1,'nh_snprintf':5}
   if name in skips:
    types=[x.get('type',{}).get('qualType') for x in node['inner'][1:]];shape=''.join('p' if '*' in t else 'j' if t in ['long','unsigned long','time_t'] else 'i' for t in types[skips[name]:])
    if shape not in shapes:shapes.append(shape)
  for child in node.get('inner',[]):walk(child)
 walk(fn)
assert json.loads(re.search(r'var shapes=(\[[^\n]*\]);',library)[1])==shapes
for i,shape in enumerate(shapes):
 values=[f'((const char*)(uintptr_t)args[{j}])' if k=='p' else f'((long)args[{j}])' if k=='j' else f'((int)args[{j}])' for j,k in enumerate(shape)] or ['(char*)0']
 assert f'case {i}:TOPTEN_ABI_OUTPUT('+','.join(values)+');break;' in support,('Review typed native varargs shape',shape)
assert len(private)==17
assert set(re.findall(r'teleport_topten_test_(\w+)__deps',library))==set(private)
assert '#ifdef TOPTEN_VALIDATE_REFERENCE' in layout and 'TELEPORT_REFERENCE_TU' not in layout
assert probe.index('#define TOPTEN_VALIDATE_REFERENCE')>probe.index('#include "../.cache/wasm64-build/tree/src/topten.c"')
assert 'static struct teleport_toptenentry teleport_topten_zero,teleport_topten_buffer;' in support,'Private mutable native record storage must not become constzero'
assert 'C.callLocal(readentry,' in core and core.count('C.stackRestore(automatic_scope)')==3
assert 'tt_head:0' in runtime and 'moduleKey:Module' in library
print(f'TOPTEN metadata:24 functions/17private,16prefixes/7record formats/{len(expected_cases)}achievement cases/{len(expected_conducts)}conducts,{len(literals)}strings/{capacity}bytes,{len(shapes)}typed printf shapes,{len(sites)}RNG sites and actual CPP origins verified.')
