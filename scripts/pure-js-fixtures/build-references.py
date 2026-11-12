"""Rebuild the five original-C references whose fixture inputs changed.

Uses the existing frozen reference recipes; never executes a mixed IUT or recorder.
Other C references/native addons remain prerequisites of the subsystem setup.
"""
from pathlib import Path
import ast,hashlib,json,subprocess,sys,types
root=Path(__file__).resolve().parents[2]
sdk=root/'.cache/emsdk';work=root/'.cache/tu-probes'
cache=root/'.cache/pure-js-fixtures';cache.mkdir(parents=True,exist_ok=True)
receipt=cache/'reference-builds.json'
targets={'cmd':'.cache/tu-probes/cmd-reference.mjs','options':'.cache/tu-probes/options-reference.mjs','uhitm':'.cache/tu-probes/uhitm/reference.mjs','termcap':'.cache/tu-probes/termcap-reference.mjs','wintty':'.cache/tu-probes/wintty-reference.mjs'}
check='--check'in sys.argv;ensure='--ensure'in sys.argv
selected=[v for v in sys.argv[1:]if not v.startswith('--')]
names=[n for n in targets if not selected or n in selected]
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
common=['scripts/pure-js-fixtures/build-references.py','scripts/build-tu-probes.py','scripts/build-tu137-group-a.py','nethack-c/wasm/tu-fragments/tu137-group-a-probes.json','nethack-c/wasm/tu-fragments/tu137-group-b/b-probe-commands.json','nethack-c/wasm/compile-defines.json','nethack-c/wasm/native-terminal.h','.cache/tu-probes/tu-source-locations.h']
common+=sorted({str(p.relative_to(root))for folder in ['.cache/wasm64-build/tree/src','.cache/wasm64-build/tree/include','.cache/wasm64-build/tree/win/tty','nethack-c/wasm']for p in (root/folder).rglob('*')if p.is_file()and p.suffix in ['.c','.h','.inc']})
common+=['.cache/ncurses-wasm64-build/lib/libtinfo.a']
rows=json.loads(receipt.read_text())if receipt.exists()else{}
commands=[]
def run(command,**kwargs):
 command=list(map(str,command));commands.append({'command':command,'cwd':str(kwargs.get('cwd',root))});return subprocess.run(command,**kwargs)
class ReferenceOnly(ast.NodeTransformer):
 def visit_For(self,node):
  self.generic_visit(node)
  if isinstance(node.target,ast.Name)and node.target.id=='mode':
   try:value=ast.literal_eval(node.iter)
   except (ValueError,TypeError):return node
   if value==['reference','hybrid']:node.iter=ast.List(elts=[ast.Constant('reference')],ctx=ast.Load())
  return node
for name in names:
 source_files=common+[f'scripts/tu-{name}-probe.c']
 hashes={p:sha(root/p)for p in source_files}
 previous=rows.get(name,{})
 valid=previous.get('inputs')==hashes and all((root/p).is_file()and sha(root/p)==h for p,h in previous.get('outputs',{}).items())and bool(previous.get('outputs'))
 if valid and(check or ensure):print('VERIFIED original C '+name,flush=True);continue
 assert not check,('Stale original-C fixture; run build-references.py --ensure',name)
 subprocess.run([sys.executable,'-B',str(root/'scripts/check-golden-emscripten-profile.py')],cwd=root,check=True)
 commands.clear()
 if name=='cmd':
  sys.path.insert(0,str(root/'scripts'))
  from golden_emscripten_profile import c_flags as golden_c_flags
  recipe=ast.parse((root/'scripts/build-tu-probes.py').read_text())
  table=next(n.value for n in recipe.body if isinstance(n,ast.Assign)and any(isinstance(t,ast.Name)and t.id=='probes'for t in n.targets))
  functions=ast.literal_eval(next(v for k,v in zip(table.keys,table.values)if isinstance(k,ast.Constant)and k.value=='cmd'))[1]
  port=next(p for p in json.loads((root/'nethack-c/wasm/tu-ports.json').read_text())if p['name']=='cmd')
  include=root/'.cache/wasm64-build/tree/include';defines=['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]
  flags=['-O2','-g','-sMEMORY64=1',*defines,'-I'+str(include),'-I'+str(root/'scripts'),'-I'+str(root/'.cache/ncurses-wasm64-build/include'),'-include',str(root/'nethack-c/wasm/native-terminal.h')]
  foreign=work/'cmd-reference-foreign.o'
  run([sdk/'upstream/emscripten/emcc',*flags,'-c',root/'nethack-c/wasm/tu-fragments/cmd-fixture-foreign.c','-o',foreign],cwd=root,check=True)
  exports=port.get('probeExtraExports',[])+['_probe_'+n for n in functions]+([]if port.get('probeContext')is False else['_probe_context_size'])
  command=[sdk/'upstream/emscripten/emcc',*golden_c_flags(root),'-sMODULARIZE=1','--js-library',root/'nethack-c/wasm/native-libc-library.js','-DTELEPORT_ISOLATED_PROBE','-sENVIRONMENT=node,web','-sALLOW_MEMORY_GROWTH=1','--no-entry','-I'+str(work),*flags,'-sEXPORTED_FUNCTIONS='+','.join(exports),root/'scripts/tu-cmd-probe.c',foreign,'-fmacro-prefix-map='+str(root/'scripts')+'/../.cache/wasm64-build/tree/src/=','-Wl,--wrap=free','-sEXPORTED_RUNTIME_METHODS=HEAPU8,stringToUTF8,lengthBytesUTF8,stackAlloc,stackSave,stackRestore','-o',root/targets[name]]
  run(command,cwd=root,check=True)
 elif name=='options':
  tree=ast.parse((root/'scripts/build-tu-probes.py').read_text())
  nodes=[n for n in tree.body if isinstance(n,ast.FunctionDef)and n.name in ['c_shadow_flags','c_shadow_compile','build_c_shadow_probes']or isinstance(n,ast.Assign)and any(isinstance(t,ast.Name)and t.id in ['C_SHADOW_EXPORTS','C_SHADOW_NAMES']for t in n.targets)]
  tree=ast.fix_missing_locations(ReferenceOnly().visit(ast.Module(body=nodes,type_ignores=[])))
  scope={'root':root,'sdk':sdk,'work':work,'defines':['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())],'json':json,'subprocess':types.SimpleNamespace(run=run)}
  exec(compile(tree,'original-C-reference-recipes','exec'),scope);scope['build_c_shadow_probes'](name)
 elif name=='uhitm':
  tree=ast.fix_missing_locations(ReferenceOnly().visit(ast.parse((root/'scripts/build-tu137-group-a.py').read_text())))
  scope={};exec(compile(tree,'original-C-group-a-reference','exec'),scope);scope['subprocess']=types.SimpleNamespace(run=run)
  # Metadata copies are mode-independent or already present in the configured setup.
  scope['build_group_a'](root,sdk,work,name)
 else:
  data=json.loads((root/'nethack-c/wasm/tu-fragments/tu137-group-b/b-probe-commands.json').read_text())['commands'][name]
  if name=='termcap':data=data['default']
  command=list(data['reference']['command']);command[command.index('-o')+1]=str(root/targets[name])
  if name=='wintty':command+=['-Wl,--wrap=tgetent','-Wl,--wrap=fclose']
  run(command,cwd=root,check=True)
 output=Path(targets[name]);outputs={str(p):sha(root/p)for p in [output,output.with_suffix('.wasm')]}
 rows[name]={'engine':'original-C','inputs':hashes,'outputs':outputs,'commands':list(commands)}
 temporary=receipt.with_suffix('.tmp');temporary.write_text(json.dumps(rows,indent=2)+'\n');temporary.replace(receipt)
 print('BUILT original C '+name,flush=True)
