"""Fresh compiler metadata and unchanged profile guards; no generated policy fallback."""
from pathlib import Path
import argparse,json,subprocess,sys
q=argparse.ArgumentParser();q.add_argument('--out',required=True,type=Path);q.add_argument('--source-root',type=Path);a=q.parse_args()
code=Path(__file__).resolve().parents[1];r=(a.source_root or code).resolve();out=a.out.resolve();out.mkdir(parents=True,exist_ok=False)
emcc=r/'.cache/emsdk/upstream/emscripten/emcc';node=r/'.cache/emsdk/node/24.19.0_64bit/bin/node'
base=[str(emcc),'-sMEMORY64=1','-DNOTPARMDECL','-DNO_TIMED_DELAY','-I'+str(r/'.cache/wasm64-build/tree/include'),'-I'+str(r/'nethack-c/upstream/win/share')]
source=str(r/'nethack-c/upstream/win/share/tilemap.c');commands=[]
def run(cmd,file):
 with(out/file).open('w')as f:z=subprocess.run(cmd,stdout=f,stderr=subprocess.PIPE,text=True)
 commands.append({'command':cmd,'exit':z.returncode,'stderr':z.stderr});(out/'commands.json').write_text(json.dumps(commands,indent=2)+'\n');assert z.returncode==0,z.stderr
for name,flags in [('tiletext',['-DTILETEXT']),('generator',[])]:run([*base,*flags,'-Xclang','-ast-dump=json','-fsyntax-only',source],name+'.ast.json')
run([*base,'-dM','-E',source],'macros.txt')
ast=json.loads((out/'tiletext.ast.json').read_text());names=['tilename','acceptable_tilename','precheck','add_tileref','dump_tilerefs','free_tilerefs'];rows=[x for x in ast['inner'] if x.get('kind')=='FunctionDecl' and x.get('name') in names and any(y.get('kind')=='CompoundStmt' for y in x.get('inner',[]))];assert [x['name'] for x in rows]==names
(out/'inventory.json').write_text(json.dumps({'tiletext':rows},indent=2)+'\n')
run([sys.executable,str(code/'scripts/project-utility-tilemap.py'),str(out)],'project.log')
for name in ['tiletext','generator']:run([str(node),str(code/('scripts/guard-utility-tilemap-'+name+'.mjs')),'--out',str(out),'--source-root',str(r)],'guard-'+name+'.log')
print('PASS both TILEMAP profile source/data guards')
