#!/usr/bin/env python3
"""Source-stable all-public verification with unchanged frozen workers, no CPU sampler.

This deliberately disables deadlines to collect complete parity evidence.
The separate regular CI workflow enforces the upstream45-second worker limit.
"""
import argparse,hashlib,json,os,pathlib,subprocess,time
p=argparse.ArgumentParser();p.add_argument('repository',type=pathlib.Path);p.add_argument('--node',type=pathlib.Path,required=True);p.add_argument('--output',type=pathlib.Path,required=True);a=p.parse_args()
root=a.repository.resolve();node=a.node.resolve();out=a.output.resolve()
assert node.is_file(),'Node executable required'
for name in ['STANDALONE_RECORDER_ASSETS','STANDALONE_RECORDER_LAYOUTS','STANDALONE_RECORD_LAYOUTS','NODE_OPTIONS']:
    assert not os.environ.get(name),'Remove inherited override '+name
out.mkdir(parents=True,exist_ok=False)
def manifest():
    paths=[p for name in ['js','frozen','sessions']for p in sorted((root/name).rglob('*'))if p.is_file()]
    paths.extend(root/name for name in ['package.json','scripts/score-js.sh','.teleport/repo-metadata.json'])
    return {str(p.relative_to(root)):hashlib.sha256(p.read_bytes()).hexdigest()for p in paths}
before=manifest();version=subprocess.check_output([str(node),'--version'],text=True).strip()
pre={'sourceSha256':before,'nodeVersion':version,'launcherSha256':hashlib.sha256(pathlib.Path(__file__).read_bytes()).hexdigest(),'effectiveTimeoutMs':0,'normalEntry':True,'jsMainOverlay':False,'assetOverride':False,'layoutOverride':False,'cpuProfiling':False,'command':['bash','scripts/score-js.sh','sessions/']}
(out/'pre-run-manifest.json').write_text(json.dumps(pre,indent=2)+'\n')
env=os.environ.copy();env.update(PATH=str(node.parent)+':'+env['PATH'],TZ='America/New_York',SESSION_REPLAY_TIMEOUT_MS='0',STANDALONE_RECORDER_STATS_DIR=str(out/'stats'))
started=time.time()
with(out/'results.stdout.log').open('wb')as stdout,(out/'results.stderr.log').open('wb')as stderr:
    child=subprocess.Popen(pre['command'],cwd=root,env=env,stdout=stdout,stderr=stderr)
    print(json.dumps({'pid':child.pid,'output':str(out),'cpuProfiling':False}),flush=True)
    code=child.wait()
after=manifest();integrity={'filesChecked':len(before),'changed':[k for k in sorted(set(before)|set(after))if before.get(k)!=after.get(k)],'exitCode':code,'wallSeconds':time.time()-started}
(out/'post-run-integrity.json').write_text(json.dumps(integrity,indent=2)+'\n');print(json.dumps(integrity),flush=True)
if code or integrity['changed']:raise SystemExit(code if code else 1)
(out/'score-repo').symlink_to(root,target_is_directory=True)
subprocess.run([str(node),str(root/'scripts/score-standalone.mjs'),'--summarize',str(out)],cwd=root,check=True)
summary=json.loads((out/'summary.json').read_text())
accepted=summary['sessionCount']==44 and summary['strictAllMetricsPassed']==44
(out/'verification-status.json').write_text(json.dumps({'strictPublicPassed':summary['strictAllMetricsPassed'],'accepted':accepted,'deadlinesEnforced':False},indent=2)+'\n')
assert accepted,'All44 strict public sessions must pass'
