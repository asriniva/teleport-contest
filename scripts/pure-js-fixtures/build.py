"""Lower ONLY isolated fixture/ABI support C into executable JavaScript.
Game translation units are deliberately excluded. Runtime imports must resolve
against production JS policies/services; generated code never loads Wasm.
"""
from pathlib import Path
import subprocess,json,re,sys,hashlib,ast
ROOT=Path(__file__).resolve().parents[2]
SDK=ROOT/'.cache/emsdk/upstream'
NAME=sys.argv[1]
OUT=ROOT/'.cache/pure-js-fixtures'/NAME
OUT.mkdir(parents=True,exist_ok=True)
ports=json.loads((ROOT/'nethack-c/wasm/tu-ports.json').read_text())
port=next(p for p in ports if p['name']==NAME)
# First candidate uses the shared, declared ABI-support fixture. Source files
# under upstream/src or the prepared game tree are never compilation inputs.
sources=[ROOT/f'scripts/tu-{NAME}-probe.c']
common=ROOT/'nethack-c/wasm/tu-support.c'
extra=OUT/'extra-abi.c'
extra.write_text('#include '+json.dumps(str(ROOT/'.cache/tu-probes/tu-source-locations.h'))+'\n'+ ('#include '+json.dumps(str(ROOT/'nethack-c/wasm/tu-do_name-support.inc'))+'\n' if NAME=='were' else ''))
extra.write_text(extra.read_text()+'#include <stdio.h>\n#include <stdint.h>\n')
wire_storage=OUT/'runtime-storage.c';wire_storage.write_text('#include <stdio.h>\n#include <stdint.h>\nFILE *const stdin=0,*const stdout=0,*const stderr=0;\nuintptr_t __THREW__; int __threwValue;\n')
sources.append(wire_storage)
sources.append(extra)
fixture=OUT/'fixture.c'
original=sources[0]
removed_catalogues=[]
fixture_text=original.read_text()
if NAME=='earlyarg':
 fixture_text=re.sub(r'#include \"[^\"]*/src/options.c\"', '/* Production JS OPTIONS supplies match_optname. */',fixture_text)
 extra.write_text(extra.read_text()+'#include \"hack.h\"\n#include '+json.dumps(str(ROOT/'nethack-c/wasm/tu-fragments/options-support.c'))+'\n')
if NAME in ['glyphs','u_init']:
 def catalogue_include(match):
  removed_catalogues.append(Path(match[1]).stem)
  return '/* Existing production JS catalogue initializer replaces the C dependency. */'
 fixture_text=re.sub(r'#include \"([^\"]*/src/(?:objects|monst).c)\"',catalogue_include,fixture_text)
# Resolve quoted includes relative to the original fixture location.
fixture_text=re.sub(r'(#include\s+")([^"]+)(")',lambda m:m[1]+str((original.parent/m[2]).resolve())+m[3] if (original.parent/m[2]).exists() else m[0],fixture_text)
fixture_text,lua_library_cases=re.subn(r'\bluaL_openlibs\s*\(', 'teleport_fixture_open_lua_libraries(',fixture_text)
fixture_text='extern void teleport_fixture_open_lua_libraries(void *);\n'+fixture_text
fixture_text,growth_cases=re.subn(r'malloc\(emscripten_get_heap_size\(\)\s*\+\s*(?:16777216|(?:8|16)UL\*1024\*1024)\)', 'teleport_fixture_grow()',fixture_text)
fixture.write_text('extern void *teleport_fixture_grow(void);\n'+fixture_text)
sources[0]=fixture
# Typed ABI helpers are added only when the fixture did not already include them.
extra_support=[ROOT/x for x in port.get('adapterSources',[]) if x.endswith(('-support.c','-support.inc')) and not x.endswith('/tu-support.c')]



dependencies={NAME,'alloc','strutil','hacklib',*removed_catalogues}
for dependency in ['objects','monst']:
 if re.search(r'\b'+dependency+r'_globals_init\s*\(',fixture_text):dependencies.add(dependency)
group_recipes=json.loads((ROOT/'nethack-c/wasm/tu-fragments/tu137-group-a-probes.json').read_text())
group=group_recipes.get(NAME,{})
for dependency in group.get('dependenciesBothModes',[]):
 if dependency.startswith('prepared/src/'):dependencies.add(Path(dependency).stem)
recipe=ROOT/f'.cache/tu-probes/native-oracles/{NAME}-build.json'
if not recipe.exists():recipe=ROOT/f'.cache/tu-probes/native-oracles/{NAME}-full-native-build.json'
if recipe.exists():
 for arg in json.loads(recipe.read_text()).get('hybridCommand',json.loads(recipe.read_text()).get('command',[])):
  if '/src/' in arg and arg.endswith('.c'): dependencies.add(Path(arg).stem)
# Preserve C reference dependency recipes while selecting only their JS ports.
recipe_source=ROOT/'scripts/build-tu-probes.py'
known={p['name']for p in ports};recipe_renames=set()
def selected_name(test):
 if isinstance(test,ast.Compare)and isinstance(test.left,ast.Name)and test.left.id=='name'and len(test.ops)==1:
  try:value=ast.literal_eval(test.comparators[0])
  except (ValueError,TypeError):return False
  if isinstance(test.ops[0],ast.Eq):return NAME==value
  if isinstance(test.ops[0],ast.In):return NAME in value
 return False
for branch in ast.walk(ast.parse(recipe_source.read_text())):
 if not isinstance(branch,ast.If)or not selected_name(branch.test):continue
 for statement in branch.body:
  for node in ast.walk(statement):
   if isinstance(node,ast.Constant)and isinstance(node.value,str)and re.fullmatch(r'-D(?:free|malloc|realloc|calloc)=teleport_probe_\w+',node.value):recipe_renames.add(node.value)
   if isinstance(node,ast.ListComp)and '/src'in ast.unparse(node.elt):
    for generator in node.generators:
     try:parts=ast.literal_eval(generator.iter)
     except (ValueError,TypeError):continue
     if isinstance(parts,list):dependencies.update(Path(p).stem for p in parts if isinstance(p,str)and Path(p).stem in known)
   if isinstance(node,ast.BinOp):
    literals=[v.value for v in ast.walk(node)if isinstance(v,ast.Constant)and isinstance(v.value,str)]
    if any('/src'in v for v in literals):
     dependencies.update(Path(v).stem for v in literals if v.endswith('.c')and Path(v).stem in known)
if NAME in ['potion','monmove','dig']:dependencies.add('cmd')
if NAME=='dig':dependencies.add('hack')
if NAME=='earlyarg':dependencies.add('options')
if NAME=='were':dependencies.add('do_name')
if NAME in ['worn','wield']:dependencies.update(['mondata','worn'])
if NAME=='coloratt':dependencies.add('posixregex')
if NAME in ['topten','options','botl']:dependencies.add('role')
if NAME=='options':dependencies.update(['drawing','posixregex'])
if NAME=='windows':dependencies.add('drawing')
if NAME=='report':dependencies.add('nhmd4')
if NAME in ['questpgr','nhlobj']:dependencies.add('nhlua')
if NAME in ['symbols','weapon','do','pager','invent','zap']:dependencies.add('drawing')
if NAME=='pager':dependencies.update(['glyphs','utf8map','coloratt','posixregex'])
if NAME=='sp_lev':dependencies.update(['nhlua','nhlsel','selvar','rect'])
if NAME=='wintty':dependencies.update(['termcap','topl'])
if NAME=='nhlsel':dependencies.update(['selvar','rect','sp_lev','nhlua'])
if NAME=='nhlobj':dependencies.update(['objects','monst','hack','cmd','sp_lev','drawing'])
if NAME=='getpos':dependencies.update(['glyphs','utf8map','coloratt','posixregex'])
if NAME=='glyphs':dependencies.update(['utf8map','coloratt','posixregex'])
for p in ports:
 if p['name'] in dependencies:
  extra_support.extend(ROOT/x for x in p.get('adapterSources',[]) if x.endswith(('-support.c','-support.inc')) and not x.endswith('/tu-support.c') and ROOT/x not in extra_support)
# NHLUA forwards public functions; keep its definitions separate from helper
# callers so the original fixture's linker-wrap observers still interpose.
nhlua_support=ROOT/'nethack-c/wasm/tu-fragments/nhlua-support.c'
if NAME=='nhlsel' and nhlua_support in extra_support:
 extra_support.remove(nhlua_support);sources.append(nhlua_support)
libraries=[ROOT/p['library'] for p in ports if p['name'] in dependencies]
probe_library=ROOT/f'nethack-c/wasm/tu-fragments/{NAME}-probe-library.js'
if probe_library.exists():libraries.append(probe_library)
for file in ([ROOT/'.cache/tu-probes/trap-fixture-library.js'] if NAME=='trap' else [ROOT/'.cache/tu-probes/sp_lev-fixture-library.js'] if NAME=='sp_lev' else []):libraries.append(file)
# Match the original linker's strong policy definitions over weak fixture mocks.
policy_symbols=set()
for library in libraries:
 policy_symbols.update(re.findall(r'^\s*(\w+)__(?:deps|sig):',library.read_text(),re.M))
weak_replacements=[]
for match in reversed(list(re.finditer(r'__attribute__\(\(weak\)\)\s+([^;{]+)\{',fixture_text))):
 declaration=match[1].strip();name_match=re.search(r'(\w+)\s*\([^)]*\)\s*$',declaration)
 if not name_match or name_match[1] not in policy_symbols:continue
 depth=1;end=match.end()
 while depth:
  if fixture_text[end]=='{':depth+=1
  elif fixture_text[end]=='}':depth-=1
  end+=1
 weak_replacements.append(name_match[1]);fixture_text=fixture_text[:match.start()]+'extern '+declaration+';'+fixture_text[end:]
fixture.write_text('extern void *teleport_fixture_grow(void);\n'+fixture_text)
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(SDK/'emscripten/cache/sysroot'),'-O1','-fno-stack-protector','-ffunction-sections','-fdata-sections','-DTELEPORT_ISOLATED_PROBE','-I'+str(ROOT/'.cache/wasm64-build/tree/include'),'-I'+str(ROOT/'scripts'),'-I'+str(ROOT/'nethack-c/wasm'),'-I'+str(ROOT/'nethack-c/wasm/tu-fragments'),'-I'+str(ROOT/'.cache/wasm64-build/tree/src'),'-I'+str(ROOT/'.cache/wasm64-build/tree/lib/lua-5.4.8/src'),'-I'+str(ROOT/'.cache/tu-probes'),'-I'+str(ROOT/'.cache/ncurses-wasm64-build/include'),'-include',str(ROOT/'nethack-c/wasm/native-terminal.h')]
if NAME=='unixmain':flags+=['-Dmain=teleport_fixture_main']
if NAME=='end':
 at=flags.index('-include');del flags[at:at+2]
flags+=['-D'+d for d in group.get('hybridDefines',[])]
flags+=['-DHYBRID_'+NAME.upper()+'=1']
flags+=['-D'+x for x in json.loads((ROOT/'nethack-c/wasm/compile-defines.json').read_text())]
renames={
 'earlyarg':['free'], 'coloratt':['free'], 'getline':['fflush'],
 'iactions':['free','__assert_fail'], 'exper':['__assert_fail'], 'priest':['free'], 'worm':['free'],
 'o_init':['free'], 'shknam':['free'],
 'rumors':['fopen','fclose','fseek','fgets','ftell','free'],
 'sfstruct':['read','write','fdopen','fwrite','fflush','fclose','close'],
 'unixtty':['tcgetattr','tcsetattr','cfgetospeed','fpathconf','perror','vprintf','putchar','exit'],
 'ioctl':['tcgetattr','tcsetattr','signal','kill','ioctl'],
}
renames.update({
 'windows':['free','puts','fopen','fgets','fclose','fputs','fprintf'],
 'topten':['free'],'glyphs':['free','fprintf'],'engrave':['free'],'role':['free'],
 'getpos':['free'],'vault':['free'],'weapon':['free'],'region':['free'],'dog':['free'],
 'pline':['fork','waitpid','getgid','getuid','setgid','setuid','execv','perror','fprintf','free'],
 'mail':['free'],'do_wear':['free'],'questpgr':['free'],'symbols':['malloc','free'],
 'report':['readlink','open','read','write','close','fork','execve','waitpid','signal','exit'],
 'restore':['free'],
})
flags+=['-D'+n+'=teleport_probe_'+n.removeprefix('__') for n in renames.get(NAME,[])]
flags+=sorted(recipe_renames-set(flags))
if NAME=='mail':flags+=['-Dgetuid=teleport_probe_getuid','-Dgetpwuid=teleport_probe_getpwuid','-Dstat(a,b)=teleport_probe_stat(a,b)']
if NAME=='mkroom':flags+=['-DTELEPORT_REFERENCE_DRAWING','-DTELEPORT_REFERENCE_SHKNAM']
if 'nhlua' in dependencies or re.search(r'\bsetjmp\s*\(',fixture_text):flags+=['-mllvm','-enable-emscripten-sjlj']
flags+=['-fmacro-prefix-map='+str(ROOT/'scripts')+'/../.cache/wasm64-build/tree/src/=']
wraps={'version':['datamodel'],'o_init':['nh_deterministic_qsort'],'topten':['fclose'],'getpos':['nh_deterministic_qsort'],'cfgfiles':['free'],'mkmaze':['free'],'mklev':['malloc','free'],'dothrow':['malloc','free'],'dungeon':['malloc','free'],'display':['malloc','free'],'cmd':['free'],'mkobj':['free'],'files':['fcntl','sscanf'],'invent':[]}
for flag in group.get('flags',[]):
 if flag.startswith('-Wl,--wrap='):wraps.setdefault(NAME,[]).append(flag.split('=',1)[1])
for dependency in group.get('dependenciesBothModes',[]):
 if dependency.startswith('nethack-c/wasm/') and dependency.endswith('.c') and not dependency.endswith('-support.c'):sources.append(ROOT/dependency)
consumers={'nhlua':['scripts/tu-nhlua-probe-consumer.c'],'decl':['scripts/tu-decl-probe-consumer.c'],'windows':['nethack-c/wasm/tu-fragments/windows-probe-consumer.c'],'pager':['nethack-c/wasm/tu-fragments/pager-probe-consumer.c'],'invent':['nethack-c/wasm/tu-fragments/invent-probe-consumer.c'],'display':['scripts/tu-display-early-reader.c'],'cmd':['nethack-c/wasm/tu-fragments/cmd-fixture-foreign.c'],'dig':[],'trap':['scripts/tu-trap-probe-consumer.c'],'wintty':['scripts/tu-wintty-consumer.c'],'zap':['scripts/tu-zap-consumer.c'],'unixmain':['nethack-c/wasm/tu-fragments/unixmain-consumer.c','nethack-c/wasm/tu-fragments/unixmain-entry.c']}
storage_flags={}
for row in [row for provider in ports if provider['name'] in dependencies for row in provider.get('nativeStorageSources',[])]:
 source=ROOT/row['source'];sources.append(source);storage_flags[source]=['-D'+d for d in row.get('defines',[])]
for source in consumers.get(NAME,[]):
 if (ROOT/source).exists():sources.append(ROOT/source)
objects=[]
input_dependencies=set()
# Compile fixture first, then optional typed support, then common ABI helpers.
sources=[fixture]+[x for x in sources if x not in [fixture,wire_storage,extra,common]]+[wire_storage,extra,common]
for i,source in enumerate(sources):
 if source in input_dependencies:continue
 if source==extra:
  missing=[x for x in extra_support if x not in input_dependencies and x.name not in extra.read_text()]
  if NAME=='mon':extra.write_text(extra.read_text()+'#include \"hack.h\"\nextern void teleport_mon_fixture_free(void*);\n#define free teleport_mon_fixture_free\n')
  if NAME=='eat':extra.write_text(extra.read_text()+'#include "hack.h"\nextern void teleport_eat_fixture_free(void*);\n#define free teleport_eat_fixture_free\n')
  if NAME=='mail':extra.write_text(extra.read_text()+'#include <unistd.h>\nextern int teleport_probe_execl(const char*,const char*,char*);\n#define execl(a,b,c) teleport_probe_execl(a,b,c)\n')
  prior=set()
  for object in objects:prior.update(re.findall(r' [A-Za-z] (\w+)$',subprocess.check_output([str(SDK/'bin/llvm-nm'),'--defined-only','--extern-only',str(object)],text=True),re.M))
  extra.write_text(''.join('#pragma weak '+x+'\n' for x in prior)+extra.read_text())
  if missing:extra.write_text(extra.read_text()+'#include \"hack.h\"\n#include \"display.h\"\n#include \"sp_lev.h\"\n'+''.join('#include '+json.dumps(str(x))+'\n' for x in missing))
 if source==common:
  prior=set()
  for object in objects:prior.update(re.findall(r' [A-Za-z] (\w+)$',subprocess.check_output([str(SDK/'bin/llvm-nm'),'--defined-only','--extern-only',str(object)],text=True),re.M))
  wrapper=OUT/'common-abi.c'
  common_text=common.read_text()
  def common_include(match):
   include=(common.parent/match[1]).resolve()
   if include in input_dependencies or (include.name.endswith('attrib-support.inc') and 'attrname' in prior):return '/* ABI helpers already supplied by original fixture. */'
   return '#include '+json.dumps(str(include)) if include.exists() else match[0]
  common_text=re.sub(r'#include\s+"([^"]+)"',common_include,common_text)
  wrapper.write_text(''.join('#pragma weak '+x+'\n' for x in prior)+common_text);source=wrapper
 assert source.is_relative_to(ROOT/'scripts') or source==ROOT/'nethack-c/wasm/tu-support.c' or source in [extra,fixture,wire_storage,OUT/'common-abi.c'] or source.is_relative_to(ROOT/'nethack-c/wasm')
 obj=OUT/f'fixture-{i}.o';subprocess.run([str(SDK/'bin/clang'),*flags,*storage_flags.get(source,[]),*(['-mllvm','-enable-emscripten-sjlj'] if source in [extra,nhlua_support] and 'nhlua' in dependencies else ['-mllvm','-enable-emscripten-sjlj=false'] if source!=fixture else []),'-MD','-MF',str(OUT/f'fixture-{i}.d'),'-c',str(source),'-o',str(obj)],check=True,cwd=ROOT,stderr=(OUT/f'compile-{i}.log').open('w'));objects.append(obj)
 dependency_text=(OUT/f'fixture-{i}.d').read_text().replace('\\\n',' ')
 for item in dependency_text.split(':',1)[1].split():
  dependency=Path(item).resolve()
  if dependency.suffix=='.c' and ('/nethack-c/upstream/' in str(dependency) or '/wasm64-build/tree/' in str(dependency)):raise RuntimeError('Forbidden game policy source in pure JS fixture: '+str(dependency))
  input_dependencies.add(dependency)
symbols=subprocess.check_output([str(SDK/'bin/llvm-nm'),'--defined-only','--extern-only',str(objects[0])],text=True)
exports=set(re.findall(r'\b(probe_\w+)',symbols))
exports.update(x.removeprefix('_')for x in port.get('probeExtraExports',[]))
helpers=set()
for library in libraries:
 text=library.read_text();helpers.update(re.findall(r'\b_(\w+)\s*\(',text));helpers.update(re.findall(r"['\"](teleport_\w+)['\"]",text))
defined=set()
for obj in objects:
 defined.update(re.findall(r' [A-Za-z] (\w+)$',subprocess.check_output([str(SDK/'bin/llvm-nm'),'--defined-only','--extern-only',str(obj)],text=True),re.M))
exports.update(helpers&defined)
exports.update(x for x in defined if x.startswith(('probe_','__wrap_','teleport_probe_')))
wraps[NAME]=sorted(set(wraps.get(NAME,[]))|{x.removeprefix('__wrap_')for x in defined if x.startswith('__wrap_')})
if NAME=='unixmain':exports.add('teleport_fixture_main')
exports.update(['stdin','stdout','stderr','__THREW__','__threwValue'])
command=[str(SDK/'bin/wasm-ld'),'-mwasm64','--no-entry','--allow-undefined','--import-memory','--export-table','--table-base=2','--global-base=1048576','-z','stack-size=1048576','--export=__wasm_call_ctors','--export=__heap_base','--export=__stack_pointer',*['--wrap='+n for n in wraps.get(NAME,[])],*[f'--export-if-defined={x}'for x in sorted(exports)],*map(str,objects),'-o',str(OUT/'fixture.wasm')]
subprocess.run(command,check=True,cwd=ROOT)
subprocess.run([str(SDK/'bin/wasm-dis'),str(OUT/'fixture.wasm'),'-o',str(OUT/'fixture.wat')],check=True)
# Export each genuine C fixture callback through the legalized interface.
wat=(OUT/'fixture.wat').read_text()
callbacks={}
for row in re.finditer(r'\(elem[^\n]*?\(i64.const (\d+)\) ([^\n]+)\)',wat):
 index=int(row[1])
 for symbol in re.findall(r'\$([^\s()]+)',row[2]):
  callbacks[index]=symbol;index+=1
wat=wat.rstrip()[:-1]+''.join('\n (export "__fixture_callback_'+str(i)+'" (func $'+symbol+'))'for i,symbol in callbacks.items())+'\n)\n'
(OUT/'fixture.wat').write_text(wat)
subprocess.run([str(SDK/'bin/wasm-as'),str(OUT/'fixture.wat'),'--all-features','-o',str(OUT/'fixture.wasm')],check=True)
def signature(text):return {'params':re.findall(r'\b(?:i32|i64|f32|f64)\b',' '.join(re.findall(r'\(param ([^)]*)\)',text))),'result':(re.search(r'\(result (\w+)\)',text).group(1) if re.search(r'\(result (\w+)\)',text) else 'void')}
headers={};imports={};exports={}
for line in wat.splitlines():
 match=re.match(r' \(func \$([^\s()]+)(.*)',line)
 if match:headers[match[1]]=signature(match[2])
 match=re.match(r' \(import "env" "([^"]+)" \(func \$([^\s()]+)(.*)',line)
 if match:imports[match[1]]=signature(match[3]);headers[match[2]]=signature(match[3])
 match=re.match(r' \(export "([^"]+)" \(func \$([^\s()]+)\)\)',line)
 if match:exports[match[1]]=match[2]
heap_symbol=re.search(r'\(export "__heap_base" \(global \$([^\s()]+)\)\)',wat)[1]
heap_base=int(re.search(r'\(global \$'+re.escape(heap_symbol)+r' i64 \(i64.const (\d+)\)\)',wat)[1])
emjs={}
input_dependencies.update([recipe_source,ROOT/'nethack-c/wasm/tu-ports.json',ROOT/'nethack-c/wasm/tu-fragments/tu137-group-a-probes.json'])
for source in input_dependencies|{original}:
 if not source.is_relative_to(ROOT/'scripts') and not source.is_relative_to(ROOT/'nethack-c/wasm'):continue
 for match in re.finditer(r'\bEM_JS\s*\(\s*(\w+)\s*,\s*(\w+)\s*,\s*\((.*?)\)\s*,\s*(\{.*?\})\s*\)',source.read_text(),re.S):
  emjs[match[2]]={'parameters':[p.strip().split()[-1].lstrip('*') for p in match[3].split(',') if p.strip()!='void'],'body':match[4]}
(OUT/'abi.json').write_text(json.dumps({'headers':headers,'imports':imports,'exports':exports,'heapBase':heap_base,'callbacks':callbacks,'emJs':emjs},indent=2)+'\n')
subprocess.run([str(SDK/'bin/wasm-opt'),str(OUT/'fixture.wasm'),'--all-features','--llvm-nontrapping-fptoint-lowering','--memory64-lowering','--legalize-js-interface','-o',str(OUT/'fixture-lowered.wasm')],check=True)
subprocess.run([str(SDK/'bin/wasm2js'),str(OUT/'fixture-lowered.wasm'),'--all-features','-O','-o',str(OUT/'fixture.js')],check=True)
manifest={'name':NAME,'platformProfile':'sdk' if NAME=='end' else 'pinned-native-terminal','builderSha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'sources':[str(p.relative_to(ROOT))for p in sources],'dependencies':sorted(dependencies),'libraries':[str(p.relative_to(ROOT))for p in libraries],'fixtureChanges':{'weakPolicyDefinitionsReplaced':sorted(weak_replacements),'luaLibraryCases':lua_library_cases,'luaLibraries':['base','coroutine','table','string','math','utf8','os','debug','io'],'growthCases':growth_cases,'effect':'Grow actual JS heap by 16MiB instead of repeated geometric full-heap allocations; all original growth assertions remain.'},'sourceSha256':{str(p.relative_to(ROOT)):hashlib.sha256(p.read_bytes()).hexdigest()for p in set(sources+libraries+[original])|input_dependencies},'outputSha256':{file:hashlib.sha256((OUT/file).read_bytes()).hexdigest()for file in ['fixture.js','abi.json']},'gameTranslationUnitsCompiled':[],'runtimeWasmRequired':False,'scope':'Fixture setup/ABI only; every production policy must resolve to existing JS.'}
(OUT/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
if '--keep-intermediates' not in sys.argv:
 for file in OUT.iterdir():
  if file.suffix in ['.o','.d','.wasm','.wat']:file.unlink()
print(OUT)
