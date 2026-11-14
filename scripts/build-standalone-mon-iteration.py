#!/usr/bin/env python3
"""Relink the sealed full C oracle, exposing original original MON iteration observers only."""
import argparse,hashlib,json,os,subprocess
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--reference',type=Path,required=True);p.add_argument('--out',type=Path,required=True);a=p.parse_args()
root=Path(__file__).resolve().parents[1];base=a.reference.resolve();out=a.out.resolve()
assert out.is_relative_to(root/'.cache') and not out.exists(),'Use a new private .cache child'
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
receipt=json.loads((base/'receipt.json').read_text())
assert receipt['gameTranslationUnits']==140 and receipt['luaTranslationUnits']==32
for k in ['syntheticGameGlobals','abortBoundaries','portedTranslationUnits']:assert receipt[k]==[]
for name,want in receipt['sourceSha256'].items():assert sha(Path(name))==want,name
for name,want in receipt['artifactSha256'].items():assert sha(base/name)==want,name
commands=json.loads((base/'commands.json').read_text())
compile_cmd=next(c for c in commands if '-c'in c and any(Path(v).name=='mon.c'for v in c))
link_cmd=next(c for c in commands if '-o'in c and any(v.endswith('/out/game.mjs')for v in c))
old_source=compile_cmd[compile_cmd.index('-c')+1];old_object=compile_cmd[compile_cmd.index('-o')+1]
probe=root/'scripts/standalone-mon-iteration-probe.c';new_object=out/'mon.o'
out.mkdir(parents=True);(out/'out').mkdir();(out/'assets').symlink_to(base/'assets',target_is_directory=True)
compile_cmd=[str(probe)if v==old_source else str(new_object)if v==old_object else v for v in compile_cmd]
compile_cmd.insert(1,'-DMON_SOURCE='+json.dumps(old_source))
exports=['_full_mon_iteration','_full_mon_iteration_count','_full_mon_iteration_value','_full_mon_iteration_alloc','_full_mon_iteration_capacity','_full_mon_iteration_storage','_full_mon_visibility','_full_mon_visibility_byte','_full_mon_animal_init','_full_mon_animal_count','_full_mon_animal_value','_full_mon_animal_pick']
new_link=[]
for v in link_cmd:
 if v==old_object:v=str(new_object)
 elif v.endswith('/out/game.mjs'):v=str(out/'out/game.mjs')
 elif v.startswith('-sEXPORTED_FUNCTIONS='):v='-sEXPORTED_FUNCTIONS='+json.dumps(json.loads(v.split('=',1)[1])+exports)
 new_link.append(v)
env={**os.environ,'SOURCE_DATE_EPOCH':'1777723200','TZ':'UTC'}
for tag,cmd in [('compile',compile_cmd),('link',new_link)]:
 result=subprocess.run(cmd,capture_output=True,text=True,env=env);(out/(tag+'.log')).write_text(result.stdout+result.stderr)
 assert result.returncode==0,result.stderr[-4000:]
(out/'commands.json').write_text(json.dumps([compile_cmd,new_link],indent=2)+'\n')
sources={**receipt['sourceSha256']}
for f in [Path(__file__).resolve(),probe,base/'receipt.json',base/'commands.json',out/'commands.json',*map(Path,[v for v in link_cmd if v.endswith(('.o','.a'))])]:sources[str(f)]=sha(f)
new={**receipt,'profile':receipt['profile']+'; original MON iteration observers, no game policy edits','sourceSha256':sources,'artifactSha256':{p:sha(out/p)for p in ['out/game.mjs','out/game.wasm','out/game.mjs.symbols']},'originalReferenceReceiptSha256':sha(base/'receipt.json'),'privateForwardingExports':exports,'changedOriginalSourceFiles':[]}
(out/'receipt.json').write_text(json.dumps(new,indent=2)+'\n');print(out)
