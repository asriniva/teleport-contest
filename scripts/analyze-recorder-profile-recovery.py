#!/usr/bin/env python3
"""Join an explicitly failed profile with a source-identical single-worker retry.

The uninterrupted original replay supplies all official timings and acceptance.
The recovered worker supplies samples only, with its different interval reported.
No raw evidence is overwritten and no failed profile is silently discarded.
"""
import argparse,gzip,hashlib,json,pathlib,re,subprocess,sys

p=argparse.ArgumentParser();p.add_argument('main',type=pathlib.Path);p.add_argument('recovery',type=pathlib.Path);a=p.parse_args()
main=a.main.resolve();recovery=a.recovery.resolve();view=main/'recovered-profile-view'
load=lambda p:json.loads(gzip.open(p,'rt').read()if str(p).endswith('.gz')else p.read_text())
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
pre=load(main/'pre-run-manifest.json');retry_pre=load(recovery/'pre-run-manifest.json')
assert pre['sourceSha256']==retry_pre['sourceSha256'],'Recovery production inputs differ'
assert pre['nodeVersion']==retry_pre['nodeVersion'],'Recovery Node version differs'
for root in [main,recovery]:
    integrity=load(root/'post-run-integrity.json')
    assert integrity['exitCode']==0 and integrity['changed']==[],integrity
    assert load(root/'pre-run-manifest.json')['effectiveTimeoutMs']==0
official=load(main/'official-results.json')
assert len(official['results'])==44 and all(r['passed']for r in official['results'])
retry=json.loads((recovery/'results.stdout.log').read_text().rsplit('__RESULT_ONE__',1)[1])
expected=next(r for r in official['results']if r['session']==retry['session'])
assert retry['passed']and retry['metrics']==expected['metrics'],'Recovery scoring differs'
stats={load(p)['pid']:load(p)['session']for p in(main/'stats').glob('*.json')}
retry_stats=list((recovery/'stats').glob('*.json'));assert len(retry_stats)==1
retry_stat=load(retry_stats[0]);assert retry_stat['session']==retry['session']
old_stats=[load(p)for p in(main/'stats').glob('*.json')if load(p)['session']==retry['session']]
assert len(old_stats)==1
for key in ['inputKeys','consumedKeys','rngCalls','screens','cursors','animationSteps','animationFrames','animationCursors','pendingAnimationFrames','forbiddenAttempts','error']:
    assert old_stats[0][key]==retry_stat[key],key
valid=[];failed=[]
for file in sorted((main/'profiles').glob('*.cpuprofile*')):
    match=re.search(r'CPU\.\d+\.\d+\.(\d+)\.',file.name)
    if not match or int(match[1])not in stats:continue
    try:load(file);valid.append(file)
    except(json.JSONDecodeError,EOFError):
        assert file.stat().st_size==0 and stats[int(match[1])]==retry['session'],'Unexpected invalid profile'
        failed.append({'file':str(file),'sha256':sha(file),'session':retry['session']})
assert len(failed)==1 and len(valid)==43,'Exactly one failed profile must be recovered'
replacement=list((recovery/'profiles').glob('*.cpuprofile*'));assert len(replacement)==1
load(replacement[0]);assert str(retry_stat['pid'])in replacement[0].name
assert not view.exists(),'Use a fresh analysis view'
(view/'profiles').mkdir(parents=True);(view/'stats').mkdir()
for file in [*valid,*replacement]:(view/'profiles'/file.name).symlink_to(file)
for file in(main/'stats').glob('*.json'):
    if load(file)['session']!=retry['session']:(view/'stats'/file.name).symlink_to(file)
(view/'stats'/retry_stats[0].name).symlink_to(retry_stats[0])
for name in ['results.stdout.log','pre-run-manifest.json','post-run-integrity.json']:(view/name).symlink_to(main/name)
subprocess.run([sys.executable,str(pathlib.Path(__file__).with_name('profile-recorder-cpu.py')),str(view)],check=True,stdout=subprocess.DEVNULL)
result=load(view/'profile-summary.json')
result['profileRecovery']={'uninterrupted44Replay':str(main),'singleWorkerRetry':str(recovery),'failedProfilesRetained':failed,'replacementSha256':sha(replacement[0]),'originalIntervalUs':pre['samplingIntervalUs'],'replacementIntervalUs':retry_pre['samplingIntervalUs'],'scope':'43 original profiles plus one independently replayed worker. Weighted by measured timeDeltas; official timings/acceptance remain the uninterrupted44-session run. Not one complete uninterrupted profile collection.'}
result['method']['intervalUs']={'original':pre['samplingIntervalUs'],'replacement':retry_pre['samplingIntervalUs']}
result['documentedJudgeDeadline']={'sessionMs':900000,'enforcedInThisRun':False,'scope':'Observed public timings, not held-out or judge-host acceptance.'}
result['profiledSessionsAboveDocumentedJudge900Seconds']=[r['session']for r in result['officialTimings']if r.get('ms',0)>900000]
target=main/'profile-summary-recovered.json';target.write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps({'workerProfiles':result['workerProfiles'],'recoveredSession':retry['session'],'topSelf':result['topSelf'][:8],'report':str(target)},indent=2))
