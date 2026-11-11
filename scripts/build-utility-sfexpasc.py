from pathlib import Path
import argparse,subprocess,json,re,hashlib
parser=argparse.ArgumentParser();parser.add_argument('--out',required=True,type=Path);parser.add_argument('--source-root',type=Path);parser.add_argument('--generated-root',required=True,type=Path);a=parser.parse_args();code=Path(__file__).resolve().parents[1];r=(a.source_root or code).resolve();g=a.generated_root.resolve();out=a.out.resolve();out.mkdir(parents=True,exist_ok=False);native=code/'nethack-c/wasm/utilities/sfexpasc';source=r/'nethack-c/upstream/util/sfexpasc.c';em=r/'.cache/emsdk/upstream/emscripten/emcc';commands=[]
if not all((g/n).is_file()for n in['sfproto.h','sfdata.c']):raise SystemExit('Genuine generated sfproto.h/sfdata.c required; generate with original SFTAGS profile')
flags=['-DNOTPARMDECL','-DNO_TIMED_DELAY','-DSFCTOOL','-DNOPANICTRACE','-DNOCRASHREPORT','-DNO_CHRONICLE','-I'+str(r/'.cache/wasm64-build/tree/include'),'-I'+str(g),'-DUTILITY_SFEXPASC_REFERENCE_SOURCE="'+str(source)+'"']
def run(cmd,log):
 row={'argv':[str(x)for x in cmd]};commands.append(row)
 with(out/log).open('w')as f:z=subprocess.run(row['argv'],stdout=f,stderr=subprocess.STDOUT)
 row['exit']=z.returncode;(out/'commands.json').write_text(json.dumps(commands,indent=2)+'\n');assert z.returncode==0,log
cmd=[str(em),'-O2','-sMEMORY64=1',*flags,'-Xclang','-ast-dump=json','-fsyntax-only',str(source)]
with(out/'compiler-ast.json').open('w')as f,(out/'inventory.log').open('w')as err:z=subprocess.run(cmd,stdout=f,stderr=err)
commands.append({'argv':cmd,'exit':z.returncode});assert z.returncode==0,'inventory'
ast=json.loads((out/'compiler-ast.json').read_text());fs=[]
for n in ast['inner']:
 if n.get('kind')=='FunctionDecl'and any(v.get('kind')=='CompoundStmt'for v in n.get('inner',[])):
  loc=n.get('loc',{});loc=loc.get('expansionLoc',loc)
  if not loc.get('includedFrom'):fs.append({'name':n['name'],'parameters':[{'name':v['name']}for v in n['inner']if v.get('kind')=='ParmVarDecl'],'emptyBody':not next(v for v in n['inner']if v['kind']=='CompoundStmt').get('inner')})
(out/'configured-functions.json').write_text(json.dumps(fs,indent=2)+'\n')
c=source.read_text();tables={}
for name in['exportascii_sfo_procs','exportascii_sfi_procs']:
 b=re.search(r'struct sf_fieldlevel_procs '+name+r' = \{([\s\S]*?)\n\};',c)[1];b=re.sub(r'/\*[\s\S]*?\*/','',b);tables[name]={'ext':re.search(r'"([^"]*)"',b)[1],'fn_x':re.findall(r'\b(?:sfo_x_|sfi_x_|exportascii_sfo_|exportascii_sfi_)\w+',b)}
(out/'source-procedure-tables.json').write_text(json.dumps(tables,indent=2)+'\n');(out/'function-tokens.json').write_text(json.dumps(sorted({x for t in tables.values()for x in t['fn_x']}),indent=2)+'\n')
sources=[r/'nethack-c/upstream'/n for n in['src/sfbase.c','src/calendar.c','src/hacklib.c','src/alloc.c','util/panic.c']]+[g/'sfdata.c'];units=[(s,[])for s in sources]+[(native/'probe.c',[]),(native/'probe.c',['-DSFEXPASC_REFERENCE']),(native/'support.c',[])];inputs=set()
for i,(s,extra)in enumerate(units):
 dep=out/('unit-'+str(i)+'.d');run([em,'-O2','-sMEMORY64=1',*flags,*extra,'-M','-MT','utility_input','-MF',dep,s],'dependency-'+str(i)+'.log')
 inputs.update(Path(v).resolve()for v in dep.read_text().replace('\\\n',' ').split(':',1)[1].split())
inputs.update(p for p in (code/'js/ported-utilities/sfexpasc').glob('*.js'));inputs.update(native.glob('*'));inputs.update(p for p in(code/'scripts').glob('*utility-sfexpasc*')if p.is_file());inputs.add(code/'js/ported/c-runtime.js');sdk=r/'.cache/emsdk/upstream';ems=sdk/'emscripten';inputs.update([em,sdk/'bin/clang-21',sdk/'bin/wasm-ld',ems/'src/jsifier.mjs']);inputs.update(p for p in ems.glob('*.py')if p.is_file());inputs.update(p for p in(ems/'tools').rglob('*.py')if p.is_file());inputs.update(p for p in(ems/'src').rglob('*')if p.is_file()and p.suffix in['.js','.mjs','.json']);inputs.update(p for p in(ems/'cache/sysroot/lib/wasm64-emscripten').glob('*.a')if p.is_file());h=lambda p:hashlib.file_digest(open(p,'rb'),'sha256').hexdigest();pins=lambda:{str(p):h(p)for p in sorted(inputs)};before=pins();assert before[str(ems/'src/jsifier.mjs')].startswith('24b5838f');(out/'inputs-before.json').write_text(json.dumps(before,indent=2)+'\n')
objects=[]
for i,s in enumerate(sources):
 obj=out/('dependency-'+str(i)+'.o');run([em,'-O2','-sMEMORY64=1',*flags,'-c',s,'-o',obj],'compile-'+str(i)+'.log');objects.append(obj)
exports=['probe_prepare','probe_input','probe_finish','probe_data','probe_nhfile','probe_count','probe_eof','probe_call','sx_buffer','sx_meta','sx_literal','sx_format','sx_catalog','sx_catalog_meta','sx_token','probe_catalog','probe_catalog_name','probe_foreign_long']
for mode in['reference','hybrid']:
 run([em,'-O2','-sMEMORY64=1','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sEXIT_RUNTIME=1','--no-entry','-sFORCE_FILESYSTEM=1','-sEXPORTED_RUNTIME_METHODS=FS,HEAPU8,stackSave,stackRestore,stackAlloc','-sEXPORTED_FUNCTIONS='+','.join('_'+n for n in exports),*flags,native/'probe.c',native/'support.c',*objects,*(['-DSFEXPASC_REFERENCE']if mode=='reference'else['--js-library',native/'library.js']),'-o',out/(mode+'.mjs')],mode+'-build.log')
after=pins();(out/'inputs-after.json').write_text(json.dumps(after,indent=2)+'\n');assert before==after,'input closure changed';(out/'artifacts.json').write_text(json.dumps({p.name:h(p)for p in out.iterdir()if p.suffix in['.mjs','.wasm','.o']},indent=2)+'\n');print('PASS fresh original/mixed SFEXPASC pair and actual source/header/tool closure')
