"""Read-only TOPL source/actual-configured-AST/types/data/ABI/filename guards."""
from pathlib import Path
import ast,hashlib,json,os,re,subprocess
r=Path(__file__).resolve().parents[3];w=r/'.cache/topl-author';tools=r/'nethack-c/wasm/tu-fragments/tu137-group-b/topl-source-tools';source=r/'.cache/wasm64-build/tree/win/tty/topl.c';pristine=r/'nethack-c/upstream/win/tty/topl.c'
scratch=Path(os.environ.get('TOPL_GUARD_OUTPUT',str(r/'.cache/tu-probes/topl-guard')));scratch.mkdir(parents=True,exist_ok=True)
sdk=Path(os.environ.get('EMSDK',str(r/'.cache/emsdk')))
def digest(p):return hashlib.sha256(p.read_bytes()).hexdigest()
assert digest(source)=='d355faebfb41d9e61e784f1ef29050a55c5ca45cd066f2f47688c6b7b7cee566';assert digest(pristine)=='7abe4855c351b90048261752bab6bcc329f6fa236da1cca0cc48e362b6ff5d6d'
assert digest(w/'pre-edit-handoff.json')=='df20554751eb3ac119ead9a789c276c5d63b64b6aac98c5e2b8c0f61131de45f'
core=Path(os.environ.get('TOPL_GUARD_CORE',str(r/'js/ported/topl.js'))).read_text();runtime=Path(os.environ.get('TOPL_GUARD_RUNTIME',str(r/'js/nethack/bindings/topl.js'))).read_text();s=source.read_text();comments=re.findall(r'/\*.*?\*/',s,re.S)
assert len(comments)==80 and comments==re.findall(r'/\*.*?\*/',core,re.S),'Original80 TOPL comment order/multiplicity'
F=json.loads((w/'functions.json').read_text());names=[f['name']for f in F];assert len(F)==15 and sum(f.get('storageClass')!='static'for f in F)==10
assert re.findall(r'export function (\w+)\(',core)==names
for f in F:
 expected=', '.join(p['name']for p in f.get('inner',[])if p.get('kind')=='ParmVarDecl');assert re.search(r'export function '+f['name']+r'\(([^)]*)\)',core)[1]==expected
commands=json.loads((w/'commands.json').read_text());cwd=r/'.cache/wasm64-build/tree/src';assert all(c['cwd']==str(cwd)and c['command'][-1]=='../win/tty/topl.c'for c in commands)
macro=subprocess.check_output(commands[0]['command'],cwd=cwd,text=True)
for name in ['TTY_GRAPHICS','NOMUX_CAPTURE','DUMPLOG_CORE','DEBUG','MACOS','NO_TIMED_DELAY']:assert re.search(r'^#define '+name+r'\b',macro,re.M),('Changed TOPL profile',name)
for name in ['WIN32CON','DUMPLOG']:assert not re.search(r'^#define '+name+r'\b',macro,re.M)
assert '#define CO gt.tc_gbl_data.tc_CO' in macro
assert "Object.defineProperty(env,'CO',{get:()=>env.gt.tc_gbl_data.tc_CO});"in runtime
assert "const LONG_MAX=9223372036854775807n;"in runtime
assert 'L<LONG_MAX/10n||(L===LONG_MAX/10n&&D<=LONG_MAX%10n)'in runtime
assert "env.snapshot_mesgs=0;env.nxtidx=0;env.initd=0;"in runtime,"Original TOPL mutable initializers"
assert "[['snapshot_mesgs','char **',0],['nxtidx','int',1],['initd','signed char',2]]"in runtime
assert 'clean_up: {'in core and 'break clean_up;'in core and not re.search(r'\bgoto\s+\w+;',re.sub(r'/\*.*?\*/','',core,flags=re.S))
assert core.count('C.nomux_putch(c);')==1 and 'C.ttyDisplay.curx--; C.nomux_putch(c); C.ttyDisplay.curx = svx;'in core
assert core.count('C.dumplogmsg(')==3 and 'C.gs.saved_pline_index = 0;'in core
fresh=json.loads(subprocess.check_output(commands[2]['command'],cwd=cwd,text=True));b=source.read_bytes();actual=[]
for n in fresh['inner']:
 if n.get('kind')=='FunctionDecl'and any(c.get('kind')=='CompoundStmt'for c in n.get('inner',[])):
  at=n.get('loc',{}).get('offset',-1);name=n['name']
  if at>=0 and b[at:at+len(name)]==name.encode():actual.append(n)
def normalized(n):
 if isinstance(n,list):return[normalized(c)for c in n]
 if not isinstance(n,dict):return'<decl>'if isinstance(n,str)and re.fullmatch(r'0x[0-9a-f]+',n)else n
 return{k:normalized(v)for k,v in n.items()if k not in ['id','loc','range','previousDecl','referencedMemberDecl','typeAliasDeclId','targetLabelDeclId','declId']}
assert [f['name']for f in actual]==names
for old,new in zip(F,actual):assert normalized(old)==normalized(new),('TOPL full body/type/literal drift',old['name'])
# Recompile actual source header layout expressions without replacing captured expected data.
abi=json.loads((w/'layout-inventory.json').read_text());command=abi['command'][:];out=scratch/'fresh-layout.ll';command[command.index('-o')+1]=str(out);subprocess.check_call(command,cwd=cwd)
values={name:int(value)for name,value in re.findall(r'@teleport_topl_inventory_(\w+) =[^\n]*?constant i64 (-?\d+)',out.read_text())};assert values==abi['values'],'TOPL actual ABI layout drift'
assert values['sizeof_pointer']==8 and values['sizeof_long']==8 and values['CHAR_MIN']==-128 and values['CHAR_MAX']==127
assert int(re.search(r'const LONG_MAX=(\d+)n',runtime)[1])==values['LONG_MAX']
# Only raw character/allocation pointers are returned by actual foreign callees.
ptrs=json.loads((w/'boundary-inventory.json').read_text())['pointerReturnContracts'];assert all('char *'in p['type']['qualType']or p['type']['qualType'].startswith('long *')for p in ptrs.values())
source_strings=set()
def strings(n):
 if n.get('kind')=='StringLiteral':source_strings.add(ast.literal_eval(n['value']))
 for child in n.get('inner',[]):strings(child)
for f in actual:strings(f)
(scratch/'string-values.json').write_text(json.dumps(sorted(source_strings))+'\n')
subprocess.check_call([str(sdk/'node/24.19.0_64bit/bin/node'),str(tools/'string-values.mjs')],cwd=r,env={**os.environ,'TOPL_GUARD_STRINGS':str(scratch/'string-values.json'),'TOPL_GUARD_OUTPUT':str(scratch),'TOPL_GUARD_CORE':os.environ.get('TOPL_GUARD_CORE',str(r/'js/ported/topl.js')),'TOPL_GUARD_RUNTIME':os.environ.get('TOPL_GUARD_RUNTIME',str(r/'js/nethack/bindings/topl.js'))})
support=(r/'nethack-c/wasm/tu-fragments/topl-support.inc').read_text();assert '_test_'not in support
for name in ['create_nhwindow','putstr','display_nhwindow','destroy_nhwindow']:assert re.search(r'teleport_topl_window_'+name+r'\([^)]*\)\{(?:return )?'+name+r'\(',support)
assert not any(re.search(r'\b'+name+r'\([^;]*\)\{',support)for name in names),'C source policy fallback forbidden'
regen=scratch/'regenerated-core.js';subprocess.check_call(['python3',str(tools/'port-core.py')],cwd=r,env={**os.environ,'TOPL_OUTPUT':str(regen),'TOPL_GUARD_OUTPUT':str(scratch)})
assert regen.read_text()==core,'TOPL readable source regeneration drift'
print('TOPL metadata PASS:15 full bodies/10public5private/80ordered comments/3mutable source statics/91exact ABI constants/active dumplog+nomux/file origins/char pointers/clean_up join')
