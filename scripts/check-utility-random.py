"""Fresh actual RANDOM compiler metadata for the original exact source guard."""
from pathlib import Path
import argparse,subprocess,json,sys
q=argparse.ArgumentParser();q.add_argument('--out',required=True,type=Path);q.add_argument('--source-root',type=Path);a=q.parse_args();code=Path(__file__).resolve().parents[1];r=(a.source_root or code).resolve();p=code/'nethack-c/wasm/utilities/random';out=a.out.resolve();out.mkdir(parents=True,exist_ok=False)
base=[str(r/'.cache/emsdk/upstream/emscripten/emcc'),'-sMEMORY64=1','-DRANDOM','-DNOTPARMDECL','-DNO_TIMED_DELAY','-include',str(p/'libc-isolate.h'),'-I'+str(r/'.cache/wasm64-build/tree/include')];source=str(r/'nethack-c/upstream/sys/share/random.c');commands=[]
def run(cmd,file):
 with(out/file).open('w')as f:z=subprocess.run(cmd,stdout=f,stderr=subprocess.PIPE,text=True)
 commands.append({'command':cmd,'exit':z.returncode,'stderr':z.stderr});(out/'commands.json').write_text(json.dumps(commands,indent=2)+'\n');assert z.returncode==0,z.stderr
run([*base,'-Xclang','-ast-dump=json','-fsyntax-only',source],'original.ast.json');run([*base,'-dM','-E',source],'macros.txt')
ast=json.loads((out/'original.ast.json').read_text());names=['srandom','initstate','setstate','random'];defs=[n for n in ast['inner']if n.get('kind')=='FunctionDecl'and n.get('name')in names and any(x.get('kind')=='CompoundStmt'for x in n.get('inner',[]))];assert [x['name']for x in defs]==names
(out/'inventory.json').write_text(json.dumps([{'name':d['name'],'range':d['range'],'params':[x['name']for x in d['inner']if x['kind']=='ParmVarDecl']}for d in defs],indent=2)+'\n')
run([str(r/'.cache/emsdk/node/24.19.0_64bit/bin/node'),str(code/'scripts/guard-utility-random.mjs'),'--source-root',str(r),'--out',str(out)],'guard.log');print('PASS fresh RANDOM profile source guard')
