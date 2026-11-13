"""Compare a completed candidate against an existing saved baseline; runs no games."""
import argparse,hashlib,json,math,pathlib,statistics
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--baseline',type=pathlib.Path,required=True)
p.add_argument('--candidate',type=pathlib.Path,required=True)
p.add_argument('--output',type=pathlib.Path,required=True)
p.add_argument('--baseline-label',default='saved baseline')
a=p.parse_args()
b=json.loads((a.baseline/'official-results.json').read_text())
c=json.loads((a.candidate/'official-results.json').read_text())
bs=json.loads((a.baseline/'summary.json').read_text());cs=json.loads((a.candidate/'summary.json').read_text())
assert bs['strictAllMetricsPassed']==cs['strictAllMetricsPassed']==44
bm=json.loads((a.baseline/'pre-run-manifest.json').read_text())['sourceSha256']
cm=json.loads((a.candidate/'pre-run-manifest.json').read_text())['sourceSha256']
bi=json.loads((a.baseline/'post-run-integrity.json').read_text());ci=json.loads((a.candidate/'post-run-integrity.json').read_text())
assert not bi['changed'] and not ci['changed']
assert bi['exitCode']==ci['exitCode']==0
br={r['session']:r for r in b['results']};cr={r['session']:r for r in c['results']}
assert br.keys()==cr.keys() and len(br)==44
rows=[]
for name in sorted(br):
 old,new=br[name],cr[name]
 assert old['passed'] and new['passed'] and old['metrics']==new['metrics']
 assert old['time']['moves']==new['time']['moves']
 rows.append(dict(session=name,baselineMs=old['time']['ms'],candidateMs=new['time']['ms'],ratio=new['time']['ms']/old['time']['ms']))
btotal=sum(r['baselineMs'] for r in rows);ctotal=sum(r['candidateMs'] for r in rows)
result=dict(strictPassed=dict(baseline=44,candidate=44),baselineSpeed=b['speed'],candidateSpeed=c['speed'],baselineReplaySeconds=btotal/1000,candidateReplaySeconds=ctotal/1000,replayReductionPercent=100*(1-ctotal/btotal),medianSessionRatio=statistics.median(r['ratio'] for r in rows),geometricMeanSessionRatio=math.exp(statistics.mean(math.log(r['ratio']) for r in rows)),fasterSessions=sum(r['ratio']<1 for r in rows),sourceChanges=[name for name in sorted(bm.keys()|cm.keys()) if bm.get(name)!=cm.get(name)],candidateSourceStable=not ci['changed'],candidateIntegrity=ci,metrics=cs['metrics'],animationCursorCoverage=cs['animationCursorCoverage'],sessions=rows,limits=['Uses the existing '+a.baseline_label+', not a freshly paired run.','Same-host absolute timings may differ with host load and Node patch version; original-C component tests overlap part of the candidate run.','Diagnostic deadlines disabled; public44 only, no hosted or held-out acceptance.'])
a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps({k:v for k,v in result.items() if k not in ['sessions','metrics','animationCursorCoverage']}))
