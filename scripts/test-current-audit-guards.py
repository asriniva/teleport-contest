#!/usr/bin/env python3
import sys as _layout_sys
from pathlib import Path as _LayoutPath
_layout_sys.path.insert(0,str(_LayoutPath(__file__).resolve().parent))
from nethack_layout import historical_cli as _prior_layout_cli
if __name__=='__main__':_prior_layout_cli(__file__)
"""Small synthetic guard fixtures only; no source/native gameplay acceptance."""
import argparse,hashlib,json,os,shutil,subprocess,tempfile
from pathlib import Path

parser=argparse.ArgumentParser();parser.add_argument('--source',type=Path,default=Path(__file__).resolve().parents[1]);args=parser.parse_args()
source=args.source.resolve();candidate=Path(__file__).resolve().parent
node=source/'.cache/emsdk/node/24.19.0_64bit/bin/node';checks=0
sha=lambda b:hashlib.sha256(b.encode()if isinstance(b,str)else b).hexdigest()
def put(root,path,text):
 p=root/path;p.parent.mkdir(parents=True,exist_ok=True);p.write_text(text)
def fixture_tools(root,history,git_history,tracked):
 put(root,'history.json',json.dumps(history));put(root,'git-history.json',json.dumps(git_history));put(root,'tracked.json',json.dumps(tracked))
 put(root,'scripts/services-layout-audit.mjs','import fs from "node:fs";export function readBeforeLayout(p,e){const h=JSON.parse(fs.readFileSync("history.json"));if(!Object.hasOwn(h,p))throw Error("No historical bytes for "+p);const b=Buffer.from(h[p]);return e?b.toString(e):b;}export const existsBeforeLayout=p=>fs.existsSync(p);export function writeBeforeLayout(){throw Error("Synthetic guard is read-only");}\n')
 put(root,'bin/git','#!/usr/bin/env python3\nimport json,sys\nif sys.argv[1]=="ls-files":print("\\n".join(json.load(open("tracked.json"))))\nelse:\n assert sys.argv[1]=="show";h=json.load(open("git-history.json"));assert sys.argv[2]in h,sys.argv;sys.stdout.write(h[sys.argv[2]])\n')
 (root/'bin/git').chmod(0o755)
def run(root,script):
 return subprocess.run([str(node),'scripts/'+script],cwd=root,env={**os.environ,'PATH':str(root/'bin')+os.pathsep+os.environ.get('PATH',''),'STANDALONE_REFERENCE_ROOT':str(source)},text=True,capture_output=True)
with tempfile.TemporaryDirectory(prefix='current-pruning-guard-')as directory:
 root=Path(directory);baseline=json.loads((source/'docs/runtime-environment/c-runtime-helper-extraction.json').read_text())['baselineCommit']
 removals=['js/nethack/bitfields.js','js/nethack/environment-inputs.js','js/nethack/qsort.js','js/nethack/scanf.js','js/nethack/stdio.js','js/ported/js-runtime.js']
 rules=[['js/nethack/object-state.js','../ported/js-runtime.js','../nethack/runtime.js'],*[[f'scripts/{name}.mjs','../js/ported/js-runtime.js','../js/nethack/runtime.js']for name in ['test-js-game-files','test-js-runtime-regex','test-js-time','test-js-runtime']],['scripts/export-standalone-were-abi.py',"'js/ported/js-runtime.js',",''],['scripts/export-standalone-scanf-abi.py',"'js/nethack/scanf.js',",''],['scripts/export-standalone-scanf-abi.py',"'js/nethack/stdio.js',",''],['scripts/test-standalone-scanf.mjs','js/nethack/scanf.js','js/c-runtime/scanf.js'],['scripts/test-standalone-scanf.mjs','js/nethack/stdio.js','js/c-runtime/stdio.js']]
 files=set(removals+[r[0]for r in rules]);old={p:subprocess.check_output(['git','show',baseline+':'+p],cwd=source,text=True)for p in files};outputs={};edits=[]
 for p,b,a in rules:
  text=outputs.get(p,old[p]);assert text.count(b)==1;outputs[p]=text.replace(b,a);edits.append({'file':p,'before':b,'after':a})
 receipt={'baselineCommit':baseline,'removed':[{'file':p,'beforeSha256':sha(old[p])}for p in removals],'consumers':[{'file':p,'beforeSha256':sha(old[p]),'afterSha256':sha(s),'edits':[r for r in edits if r['file']==p]}for p,s in outputs.items()]}
 history={**outputs,'docs/runtime-environment/c-runtime-helper-extraction.json':json.dumps({'baselineCommit':baseline}),'docs/runtime-environment/c-runtime-shim-pruning.json':json.dumps(receipt,indent=2)+'\n'}
 fixture_tools(root,history,{baseline+':'+p:s for p,s in old.items()},list(outputs))
 for p,s in outputs.items():put(root,p,s)
 shutil.copyfile(candidate/'prune-c-runtime-shims.mjs',root/'scripts/prune-c-runtime-shims.mjs')
 put(root,'scripts/original-prune.mjs',subprocess.check_output(['git','show','8e0fc6ade5256f180d443835a1a8d7f4e761ddf2:scripts/prune-c-runtime-shims.mjs'],cwd=source,text=True))
 result=run(root,'prune-c-runtime-shims.mjs');assert result.returncode==0,result.stdout+result.stderr;checks+=1
 # Existing consumer's historical inverse still passes, but its actual current
 # source has a newly added import. The old outputs.get scan hides this import.
 p='scripts/test-js-time.mjs';before=(root/p).read_bytes();put(root,p,outputs[p]+"\nimport {muslQsort} "+"from '../js/nethack/qsort.js';\n")
 original=run(root,'original-prune.mjs');assert original.returncode==0,original.stdout+original.stderr;checks+=1
 result=run(root,'prune-c-runtime-shims.mjs');assert result.returncode!=0 and'Active consumer of deleted shim'in result.stderr,result.stdout+result.stderr;checks+=1
 assert(root/p).read_text().endswith("qsort.js';\n");checks+=1
 (root/p).write_bytes(before)
 # A new tracked tool has no historical inverse. It must be read directly,
 # and an import expression targeting a retired shim must also be rejected.
 p='scripts/new-current-tool.mjs';put(root,p,'export const safe = true;\n');put(root,'tracked.json',json.dumps(list(outputs)+[p]))
 result=run(root,'prune-c-runtime-shims.mjs');assert result.returncode==0,result.stdout+result.stderr;checks+=1
 put(root,p,"export const load=()=>import('../js/nethack/qsort.js');\n")
 result=run(root,'prune-c-runtime-shims.mjs');assert result.returncode!=0 and'Active consumer of deleted shim'in result.stderr,result.stdout+result.stderr;checks+=1
with tempfile.TemporaryDirectory(prefix='current-integration-base-guard-')as directory:
 root=Path(directory);integration='8cf4880d8cf7fb9104635f068564a5de87523fe7';history={};old={}
 moves=[('functions','createFunctions'),('bitfields','createBitfields'),('stdio','createStdio'),('qsort','muslQsort'),('scanf','scanFormatted'),('environment-inputs','createEnvironmentInputs')]
 for p,n in moves:
  s=f'export function {n}(){{return 1;}}\n';history['js/c-runtime/'+p+'.js']=s;old['df33dd4:js/nethack/'+p+'.js']=s
 for new,prior,name in [('js/nethack/runtime.js','js/ported/js-runtime.js','createJsRuntime'),('js/c-runtime/libc.js','js/nethack/libc.js','createStandaloneLibc'),('js/c-runtime/types.js','js/nethack/c-types.js','createCTypes')]:
  s=f'export function {name}(){{return 1;}}\n';history[new]=s;old['df33dd4:'+prior]=s
 for n in ['scanf-abi','were-abi']:
  p='js/nethack/'+n+'.json';history[p]=json.dumps({'sourceSha256':{}});old['df33dd4:'+p]=history[p]
 vision='js/ported/vision.js';base='synthetic baseline';corrected='synthetic approved correction';correction='docs/runtime-environment/authorized-port-corrections.json'
 history[vision]=corrected;history['docs/runtime-environment/scope-baseline.json']=json.dumps({'sha256':{vision:sha(base)}});history[correction]=json.dumps({'corrections':[{'file':vision,'baselineSha256':sha(base),'correctedSha256':sha(corrected)}]});old[integration+':'+correction]=history[correction]
 for n in ['isaac64','terminal','storage']:history['js/'+n+'.js']=history['frozen/'+n+'.js']='synthetic frozen '+n
 fixture_tools(root,history,old,[])
 put(root,'scripts/check-sdk-runtime-extension.mjs','export const sdkRuntimeExtensionBaseline=()=>null;\n')
 shutil.copyfile(candidate/'check-c-runtime-relocation.mjs',root/'scripts/check-c-runtime-relocation.mjs')
 manifest='docs/runtime-environment/c-runtime-manifest.json';put(root,manifest,json.dumps({'integrationBaseCommit':integration,'sha256':{'new-current-feature':'not-historical'}}))
 result=run(root,'check-c-runtime-relocation.mjs');assert result.returncode==0,result.stdout+result.stderr;checks+=1
 before=(root/manifest).read_bytes();put(root,manifest,json.dumps({'integrationBaseCommit':'unreviewed-base'}))
 result=run(root,'check-c-runtime-relocation.mjs');assert result.returncode!=0 and'Changed runtime integration base'in result.stderr,result.stdout+result.stderr;checks+=1
 assert(root/manifest).read_text()==json.dumps({'integrationBaseCommit':'unreviewed-base'});checks+=1
print('PASS',checks,'synthetic current-source/historical-guard checks; no native or gameplay acceptance claimed')
