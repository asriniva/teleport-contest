"""Build the two actual TILEMAP utility profiles, with fresh isolated outputs."""
from pathlib import Path
import argparse, hashlib, json, subprocess
parser=argparse.ArgumentParser()
parser.add_argument('--profile',required=True,choices=['tiletext','generator'])
parser.add_argument('--out',required=True,type=Path)
parser.add_argument('--source-root',type=Path)
a=parser.parse_args();code=Path(__file__).resolve().parents[1]
r=(a.source_root or code).resolve();out=a.out.resolve()
out.mkdir(parents=True,exist_ok=False)
p=code/'nethack-c/wasm/utilities/tilemap'; common=p/'common'; profile=p/a.profile
emcc=str(r/'.cache/emsdk/upstream/emscripten/emcc')
incs=['-DNOTPARMDECL','-DNO_TIMED_DELAY','-I'+str(r/'.cache/wasm64-build/tree/include'),'-I'+str(r/'nethack-c/upstream/win/share'),'-DTILEMAP_ORIGINAL_SOURCE='+json.dumps(str(r/'nethack-c/upstream/win/share/tilemap.c'))]
exports={'tiletext': ['probe_text_open', 'probe_text_read', 'probe_text_close', 'probe_text_pixels', 'probe_set_map', 'malloc', 'free', 'strcmp', 'strlen', 'probe_name', 'probe_acceptable', 'probe_precheck', 'probe_add', 'probe_dump', 'probe_free', 'probe_list', 'probe_table_count', 'probe_table_string', 'probe_table_int', 'probe_init', 'probe_open', 'probe_len', 'probe_read', 'probe_close', 'tm_storage', 'tm_stderr', 'tm_layout', 'tm_sprintf0', 'tm_sprintfp', 'tm_sprintfpp', 'tm_sprintfi', 'tm_sprintfii', 'tm_sprintfpii', 'tm_print0', 'tm_printp', 'tm_printz', 'tm_printlist', 'tm_exit', 'def_char_to_objclass', 'tm_snprintf0', 'tm_snprintf1', 'tm_snprintf2', 'tm_snprintf3', 'tm_snprintf4', 'tm_snprintf5', 'tm_snprintf6', 'tm_snprintf7', 'tm_snprintf8'], 'generator': ['malloc', 'free', 'strcmp', 'strlen', 'objects_globals_init', 'monst_globals_init', 'probe_run', 'probe_state', 'probe_map', 'probe_list', 'probe_offset', 'probe_init_catalogues', 'probe_init_map', 'probe_free', 'tm_storage', 'tm_stderr', 'tm_layout', 'tm_sprintf0', 'tm_sprintfp', 'tm_sprintfpp', 'tm_sprintfi', 'tm_sprintfii', 'tm_sprintfpii', 'tm_print0', 'tm_printp', 'tm_printz', 'tm_printlist', 'tm_exit', 'def_char_to_objclass', 'gen_constant', 'gen_layout', 'gen_fopen', 'gen_fclose', 'gen_perror', 'gen_unlink', 'tm_snprintf0', 'tm_snprintf1', 'tm_snprintf2', 'tm_snprintf3', 'tm_snprintf4', 'tm_snprintf5', 'tm_snprintf6', 'tm_snprintf7', 'tm_snprintf8', 'gen_snprintf0', 'gen_snprintf1', 'gen_snprintf2', 'gen_snprintf3', 'gen_snprintf4', 'gen_snprintf5', 'gen_snprintf6', 'gen_snprintf7', 'gen_snprintf8', 'gen_snprintf9', 'gen_snprintf10', 'gen_snprintf11', 'gen_snprintf12', 'gen_snprintf13', 'gen_snprintf14', 'gen_snprintf15', 'gen_snprintf16', 'gen_snprintf17', 'gen_snprintf18', 'gen_snprintf19', 'gen_snprintf20', 'gen_snprintf21', 'gen_snprintf22', 'gen_snprintf23', 'gen_snprintf24', 'gen_snprintf25', 'gen_snprintf26', 'gen_snprintf27', 'gen_snprintf28', 'gen_snprintf29', 'gen_snprintf30', 'gen_sprintf0', 'gen_sprintf1', 'gen_sprintf2', 'gen_sprintf3', 'gen_fprintf0', 'gen_fprintf1', 'gen_fprintf2', 'gen_fprintf3', 'gen_fprintf4', 'gen_fprintf5', 'gen_fprintf6', 'gen_fprintf7', 'gen_fprintf8', 'gen_fprintf9', 'gen_fprintf10', 'gen_fprintf11', 'gen_fprintf12', 'gen_fprintf13', 'gen_fprintf14', 'gen_fprintf15', 'gen_fprintf16', 'gen_fprintf17', 'gen_fprintf18', 'gen_fprintf19', 'gen_fprintf20', 'gen_fprintf21', 'gen_fprintf22', 'gen_fprintf23', 'gen_fprintf24', 'gen_fprintf25', 'gen_fprintf26', 'gen_fprintf27', 'gen_fprintf28', 'gen_fprintf29', 'gen_fprintf30', 'gen_fprintf31', 'gen_fprintf32', 'gen_fprintf33', 'gen_fprintf34', 'gen_fprintf35', 'gen_fprintf36', 'gen_fprintf37', 'gen_fprintf38', 'gen_fprintf39', 'gen_fprintf40', 'gen_fprintf41', 'gen_fprintf42', 'gen_fprintf43', 'gen_fprintf44', 'gen_fprintf45', 'gen_fprintf46', 'gen_fprintf47', 'gen_fprintf48', 'gen_fprintf49', 'gen_fprintf50', 'gen_fprintf51', 'gen_fprintf52', 'gen_fprintf53', 'gen_fprintf54', 'gen_fprintf55', 'gen_fprintf56', 'gen_fprintf57', 'gen_fprintf58', 'gen_fprintf59', 'gen_fprintf60', 'gen_fprintf61', 'gen_fprintf62', 'gen_fprintf63', 'gen_fprintf64', 'gen_fprintf65', 'gen_fprintf66', 'gen_fprintf67', 'gen_fprintf68', 'gen_fprintf69', 'gen_fprintf70', 'gen_fprintf71', 'gen_fprintf72', 'gen_fprintf73', 'gen_fprintf74', 'gen_fprintf75', 'gen_fprintf76', 'gen_fprintf77', 'gen_fprintf78', 'gen_fprintf79', 'gen_fprintf80', 'gen_fprintf81', 'gen_fprintf82', 'gen_fprintf83', 'gen_fprintf84', 'gen_fprintf85', 'gen_fprintf86', 'gen_fprintf87', 'gen_fprintf88', 'gen_fprintf89', 'gen_fprintf90', 'gen_fprintf91']}[a.profile]
files=(['win/share/tiletext.c'] if a.profile=='tiletext' else [])+['src/drawing.c','src/monst.c','src/objects.c','src/alloc.c','util/panic.c','src/hacklib.c']
support=[common/'support.c']+([profile/'support.c'] if a.profile=='generator' else [])
flag='-DMIXED_TM' if a.profile=='tiletext' else '-DMIXED_GENERATOR'
commands=[]
def run(cmd,log):
 row={'command':cmd};commands.append(row)
 (out/'commands.json').write_text(json.dumps(commands,indent=2)+'\n')
 with (out/log).open('w') as f:z=subprocess.run(cmd,stdout=f,stderr=subprocess.STDOUT)
 row['exit']=z.returncode
 (out/'commands.json').write_text(json.dumps(commands,indent=2)+'\n')
 if z.returncode:raise SystemExit('failed '+log)
inputs=set()
units=[(r/'nethack-c/upstream'/f,[]) for f in files]+[(profile/'probe.c',[]),(profile/'probe.c',[flag])]+[(s,[]) for s in support]
for i,(source,flags) in enumerate(units):
 dep=out/('unit-'+str(i)+'.d')
 run([emcc,'-O2','-sMEMORY64=1',*incs,*flags,'-M','-MT','utility_input','-MF',str(dep),str(source)],'dependency-'+str(i)+'.log')
 inputs.update(Path(s).resolve() for s in dep.read_text().replace('\\\n',' ').split(':',1)[1].split())
inputs.update(x for x in (code/'js/ported-utilities').glob('tilemap-*') if x.is_file())
inputs.update(x for x in p.rglob('*') if x.is_file())
inputs.update(x for x in (code/'scripts').glob('*utility-tilemap*') if x.is_file())
ems=r/'.cache/emsdk/upstream/emscripten'
inputs.update(x for x in ems.glob('*.py') if x.is_file())
inputs.update(x for x in (ems/'tools').rglob('*.py') if x.is_file())
inputs.update(x for x in (ems/'src').rglob('*') if x.is_file() and x.suffix in ['.js','.mjs','.json'])
inputs.update([ems/'emcc',r/'.cache/emsdk/upstream/bin/clang-21',r/'.cache/emsdk/upstream/bin/wasm-ld'])
def pins():
 return {str(x):hashlib.file_digest(open(x,'rb'),'sha256').hexdigest() for x in sorted(inputs)}
before=pins();(out/'inputs-before.json').write_text(json.dumps(before,indent=2)+'\n')
objs=[]
for file in files:
 obj=out/(Path(file).stem+'.o')
 run([emcc,'-O2','-sMEMORY64=1',*incs,'-c',str(r/'nethack-c/upstream'/file),'-o',str(obj)],Path(file).stem+'-build.log');objs.append(str(obj))
for mode in ['reference','hybrid']:
 libs=['--js-library',str(common/'library.js')]
 if a.profile=='generator':libs+=['--js-library',str(profile/'library.js')]
 cmd=[emcc,'-O2','-g','-sMEMORY64=1','-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sSTACK_SIZE=4194304','--no-entry','-sFORCE_FILESYSTEM=1','-sEXIT_RUNTIME=1','-sEXPORTED_RUNTIME_METHODS='+json.dumps(['FS','HEAPU8','stackSave','stackRestore','stackAlloc']),'-sEXPORTED_FUNCTIONS='+json.dumps(['_'+s for s in exports]),*incs,str(profile/'probe.c'),*map(str,support),*objs,*([flag,*libs] if mode=='hybrid' else []),'-o',str(out/(mode+'.mjs'))]
 run(cmd,mode+'-build.log')
after=pins();(out/'inputs-after.json').write_text(json.dumps(after,indent=2)+'\n');assert before==after
print('PASS original/mixed TILEMAP '+a.profile+' pair')
