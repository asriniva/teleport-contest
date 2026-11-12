#!/usr/bin/env python3
"""Profile all public recordings without changing engine or frozen harness bytes.

Usage: python3 scripts/profile-public-recorder.py REPO --node /absolute/node
Run profile-recorder-cpu.py on the reported directory after completion.
"""
import os, pathlib, hashlib, json, subprocess, time, gzip, shutil, argparse
parser=argparse.ArgumentParser();parser.add_argument('repository',type=pathlib.Path);parser.add_argument('--node',required=True,type=pathlib.Path);parser.add_argument('--output',type=pathlib.Path);args=parser.parse_args()
candidate=args.repository.resolve(); node=args.node.resolve(); out=(args.output or candidate/'.cache/recorder-cpu-profile').resolve(); out.mkdir(parents=True,exist_ok=True)
assert not (out/'pre-run-manifest.json').exists(),'Use a fresh output directory; existing evidence is never overwritten'
assert node.is_file(),'Node executable is required'
node_version=subprocess.check_output([str(node),'--version'],text=True).strip()
for key in ['STANDALONE_RECORDER_ASSETS','STANDALONE_RECORD_LAYOUTS','NODE_OPTIONS']:
 assert not os.environ.get(key),'Remove inherited override '+key
profiles=out/'profiles'; profiles.mkdir(exist_ok=True)
def manifest():
 paths=[p for d in ['js','frozen','sessions'] for p in sorted((candidate/d).rglob('*')) if p.is_file()]
 paths += [candidate/p for p in ['package.json','scripts/score-js.sh','.teleport/repo-metadata.json']]
 return {str(p.relative_to(candidate)):hashlib.sha256(p.read_bytes()).hexdigest() for p in paths}
pre=manifest(); (out/'pre-run-manifest.json').write_text(json.dumps({'sourceSha256':pre,'effectiveTimeoutMs':0,'normalEntry':True,'jsMainOverlay':False,'assetOverride':False,'layoutOverride':False,'samplingIntervalUs':1000,'nodeVersion':node_version,'timeoutPolicy':'SESSION_REPLAY_TIMEOUT_MS=0 disables frozen worker deadlines','command':['bash','scripts/score-js.sh','sessions/']},indent=2))
env=os.environ.copy(); env['PATH']=str(node.parent)+':'+env['PATH']; env['TZ']='America/New_York'; env['SESSION_REPLAY_TIMEOUT_MS']='0'; env['STANDALONE_RECORDER_STATS_DIR']=str(out/'stats'); env['NODE_OPTIONS']=f'--cpu-prof --cpu-prof-dir={profiles} --cpu-prof-interval=1000'
started=time.time()
with (out/'results.stdout.log').open('wb') as stdout, (out/'results.stderr.log').open('wb') as stderr:
 p=subprocess.Popen(['bash','scripts/score-js.sh','sessions/'],cwd=candidate,env=env,stdout=stdout,stderr=stderr)
 print(json.dumps({'pid':p.pid,'output':str(out)}),flush=True)
 while True:
  code=p.poll()
  for f in profiles.glob('*.cpuprofile'):
   # V8 creates each profile at process exit. Wait until the writer has closed it.
   if time.time()-f.stat().st_mtime<3: continue
   try:
    with f.open('rb') as source, gzip.open(str(f)+'.gz','wb',compresslevel=3) as target: shutil.copyfileobj(source,target)
    with gzip.open(str(f)+'.gz','rt') as check: json.load(check)
    f.unlink()
   except (json.JSONDecodeError,EOFError): pathlib.Path(str(f)+'.gz').unlink(missing_ok=True)
  if code is not None: break
  time.sleep(5)
post=manifest(); (out/'post-run-integrity.json').write_text(json.dumps({'filesChecked':len(pre),'changed':[k for k in pre if pre[k]!=post.get(k)],'exitCode':code,'wallSeconds':time.time()-started},indent=2)); print(json.dumps({'exitCode':code,'wallSeconds':time.time()-started}),flush=True)
raise SystemExit(code)
