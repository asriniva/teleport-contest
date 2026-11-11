from pathlib import Path
import argparse,subprocess,json,hashlib
r0=Path(__file__).resolve().parents[1];q=argparse.ArgumentParser();q.add_argument('--out',required=True,type=Path);q.add_argument('--source-root',type=Path);a=q.parse_args();r=(a.source_root or r0).resolve();p=r0/'nethack-c/wasm/utilities/random';out=a.out.resolve();out.mkdir(parents=True,exist_ok=False)
emcc=str(r/'.cache/emsdk/upstream/emscripten/emcc');flags=['-O2','-g','-sMEMORY64=1','-DRANDOM','-DNOTPARMDECL','-DNO_TIMED_DELAY','-include',str(p/'libc-isolate.h'),'-I'+str(r/'.cache/wasm64-build/tree/include'),'-DRANDOM_ORIGINAL_SOURCE='+json.dumps(str(r/'nethack-c/upstream/sys/share/random.c'))];commands=[]
def run(cmd,log):
 row={'command':cmd};commands.append(row)
 with(out/log).open('w')as f:z=subprocess.run(cmd,stdout=f,stderr=subprocess.STDOUT)
 row['exit']=z.returncode;(out/'commands.json').write_text(json.dumps(commands,indent=2)+'\n');assert z.returncode==0,log
inputs=set()
for mode in ['reference','hybrid']:
 dep=out/(mode+'.d');run([emcc,*flags,*(['-DMIXED_RANDOM']if mode=='hybrid'else[]),'-M','-MT','input','-MF',str(dep),str(p/'probe.c')],mode+'-includes.log');inputs.update(Path(x).resolve()for x in dep.read_text().replace('\\\n',' ').split(':',1)[1].split())
inputs.update(x for x in p.rglob('*')if x.is_file());inputs.update(x for x in(r0/'js/ported-utilities').glob('random*')if x.is_file());inputs.update(x for x in(r0/'scripts').glob('*utility-random*')if x.is_file());ems=r/'.cache/emsdk/upstream/emscripten';inputs.update(x for x in ems.glob('*.py')if x.is_file());inputs.update(x for x in(ems/'tools').rglob('*.py')if x.is_file());inputs.update(x for x in(ems/'src').rglob('*')if x.is_file()and x.suffix in['.js','.mjs','.json']);inputs.update([ems/'emcc',r/'.cache/emsdk/upstream/bin/clang-21',r/'.cache/emsdk/upstream/bin/wasm-ld'])
sha=lambda x:hashlib.file_digest(x.open('rb'),'sha256').hexdigest();pins=lambda:{str(x):sha(x)for x in sorted(inputs)}
before=pins();(out/'inputs-before.json').write_text(json.dumps(before,indent=2)+'\n')
exports=['malloc','free','srandom','initstate','setstate','random','utility_long_size','utility_degree','utility_storage','utility_impossible','probe_scalar','probe_pointer','probe_diag_count','probe_diagnostic']
for mode in ['reference','hybrid']:
 run([emcc,*flags,'-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sSTACK_SIZE=1048576','--no-entry','-sEXPORTED_RUNTIME_METHODS='+json.dumps(['HEAPU8']),'-sEXPORTED_FUNCTIONS='+json.dumps(['_'+n for n in exports]),str(p/'probe.c'),*(['-DMIXED_RANDOM','--js-library',str(p/'library.js')]if mode=='hybrid'else[]),'-o',str(out/(mode+'.mjs'))],mode+'-build.log')
after=pins();(out/'inputs-after.json').write_text(json.dumps(after,indent=2)+'\n');assert before==after;print('PASS actual original/mixed RANDOM four-function pair')
