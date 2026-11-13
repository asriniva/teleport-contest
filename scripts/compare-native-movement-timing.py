"""Compare candidate replay to an existing unprofiled reference; never run a baseline."""
import argparse,hashlib,json,math,pathlib,statistics
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('reference',type=pathlib.Path)
p.add_argument('candidate',type=pathlib.Path)
p.add_argument('output',type=pathlib.Path)
a=p.parse_args()
def read_bundle(file):
 text=file.read_text()
 return json.loads(text.rsplit('__RESULTS_JSON__',1)[1])
r,c=read_bundle(a.reference),read_bundle(a.candidate)
rrows={x['session']:x for x in r['results']};crows={x['session']:x for x in c['results']}
assert rrows.keys()==crows.keys(),'Exact same recording set required'
rows=[]
for name,after in crows.items():
 before=rrows[name];assert before['passed'] and after['passed'],name+' equivalence failed'
 assert before['time']['moves']==after['time']['moves'],name+' input count differs'
 for metric,value in after['metrics'].items():
  assert value['matched']==value['total'],name+' '+metric+' mismatch'
 bm,am=before['time']['ms'],after['time']['ms']
 rows.append(dict(session=name,referenceMs=bm,candidateMs=am,speedup=bm/am,moves=after['time']['moves']))
rt=sum(x['referenceMs'] for x in rows);ct=sum(x['candidateMs'] for x in rows)
result=dict(reference=str(a.reference.resolve()),candidate=str(a.candidate.resolve()),
 sourceLogSha256={str(f.resolve()):hashlib.sha256(f.read_bytes()).hexdigest() for f in [a.reference,a.candidate]},
 sessions=len(rows),strictPassed=len(rows),referenceTotalMs=rt,candidateTotalMs=ct,
 totalSpeedup=rt/ct,timeReductionPercent=100*(1-ct/rt),
 geometricMeanSessionSpeedup=math.exp(statistics.mean(math.log(x['speedup']) for x in rows)),
 referenceFit=r.get('speed'),candidateFit=c.get('speed'),rows=rows,
 limits='Historical same-host unprofiled reference versus current candidate; not a fresh paired causal estimate. No baseline run or baseline CPU profiling performed. Target 20x is not established.')
a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps({k:v for k,v in result.items() if k not in ['rows','sourceLogSha256']}))
