#!/usr/bin/env python3
"""Compare completed strict public replays; timing is descriptive, not causal."""
import argparse,json,math,pathlib
p=argparse.ArgumentParser();p.add_argument('baseline',type=pathlib.Path);p.add_argument('candidate',type=pathlib.Path);p.add_argument('--out',type=pathlib.Path,required=True);a=p.parse_args()
load=lambda d,n:json.loads((d/n).read_text())
runs=[]
for directory in [a.baseline,a.candidate]:
    pre=load(directory,'pre-run-manifest.json');post=load(directory,'post-run-integrity.json')
    summary=load(directory,'summary.json');profile=load(directory,'profile-summary.json')
    assert post['exitCode']==0 and post['changed']==[],post
    assert summary['strictAllMetricsPassed']==44 and summary['sessionCount']==44
    assert profile['complete']and profile['workerProfiles']==44
    assert pre['normalEntry']and not pre['jsMainOverlay']and not pre['assetOverride']and not pre['layoutOverride']
    assert pre['effectiveTimeoutMs']==0,'Diagnostic comparison requires uncensored timings'
    runs.append((pre,post,summary,profile))
b,c=runs
assert b[0]['nodeVersion']==c[0]['nodeVersion'],'Node versions differ'
assert b[0]['samplingIntervalUs']==c[0]['samplingIntervalUs'],'Sampling differs'
for prefix in ['frozen/','sessions/']:
    assert {k:v for k,v in b[0]['sourceSha256'].items()if k.startswith(prefix)}=={k:v for k,v in c[0]['sourceSha256'].items()if k.startswith(prefix)},prefix+' inputs differ'
assert b[2]['metrics']==c[2]['metrics']and b[2]['expectedTotals']==c[2]['expectedTotals']
bt={r['session']:r for r in b[3]['officialTimings']};ct={r['session']:r for r in c[3]['officialTimings']}
assert bt.keys()==ct.keys()and len(bt)==44
rows=[]
for session in sorted(bt):
    before,after=bt[session],ct[session]
    assert before['passed']and after['passed']and before['moves']==after['moves']
    rows.append({'session':session,'recordedInputs':before['moves'],'baselineMs':before['ms'],'candidateMs':after['ms'],'ratio':after['ms']/before['ms'],'baselineOver45s':before['ms']>45000,'candidateOver45s':after['ms']>45000})
sources=b[0]['sourceSha256'];changed=[k for k in sorted(set(sources)|set(c[0]['sourceSha256']))if sources.get(k)!=c[0]['sourceSha256'].get(k)]
result={'version':1,'complete':True,'strictPublicPassed':{'baseline':44,'candidate':44},'nodeVersion':b[0]['nodeVersion'],'samplingIntervalUs':b[0]['samplingIntervalUs'],'deadlinesEnforced':False,'changedInputs':changed,'baselineWallSeconds':b[1]['wallSeconds'],'candidateWallSeconds':c[1]['wallSeconds'],'wallRatio':c[1]['wallSeconds']/b[1]['wallSeconds'],'geometricMeanSessionRatio':math.exp(sum(math.log(r['ratio'])for r in rows)/44),'sessionsAbove45Seconds':{'baseline':sum(r['baselineOver45s']for r in rows),'candidate':sum(r['candidateOver45s']for r in rows)},'speedFits':{'baseline':b[3].get('officialSpeedFit'),'candidate':c[3].get('officialSpeedFit')},'topSelf':{'baseline':b[3]['topSelf'][:15],'candidate':c[3]['topSelf'][:15]},'sessions':rows,'limits':['Diagnostic timings with deadlines disabled; regular CI independently enforces upstream45-second per-session cutoff.','One sequential baseline/candidate pair on one host is descriptive; order, CPU frequency and host load may affect the result.','Public44 only; no held-out56 acceptance.','The45-second flags compare official replay durations; actual worker deadlines additionally include process/module overhead.']}
a.out.write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps({k:result[k]for k in ['strictPublicPassed','baselineWallSeconds','candidateWallSeconds','wallRatio','geometricMeanSessionRatio','sessionsAbove45Seconds','changedInputs']},indent=2))
