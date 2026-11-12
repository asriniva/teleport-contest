#!/usr/bin/env python3
"""Read V8 CPU profiles from unmodified public recorder workers; never runs games."""
import argparse, collections, gzip, hashlib, json, pathlib, re, time
p=argparse.ArgumentParser();p.add_argument('directory',type=pathlib.Path);p.add_argument('--partial',action='store_true');a=p.parse_args();out=a.directory.resolve()
load=lambda p:json.loads(gzip.open(p,'rt').read() if str(p).endswith('.gz') else p.read_text())
stats=[load(p) for p in (out/'stats').glob('*.json')]; workers=collections.defaultdict(list)
for s in stats:workers[s['pid']].append(s)
selftime=collections.Counter();inclusive=collections.Counter();groups=collections.Counter();phases=collections.Counter();phase_functions=collections.defaultdict(collections.Counter);hot_callers=collections.defaultdict(collections.Counter);hot_owners=collections.defaultdict(collections.Counter);rows=[];profilehash={}
def identity(f):
 u=f['url']; i=u.find('/js/'); u=u[i+1:] if i>=0 else u
 if '/frozen/' in u:u='frozen/'+u.split('/frozen/',1)[1]
 return (u,f['functionName'],f['lineNumber']+1,f['columnNumber']+1)
def group(f):
 u,n,_,_=f
 if n=='(garbage collector)':return 'garbage collection'
 if u.startswith('js/c-runtime/'):return 'C environment'
 if u.startswith('js/nethack/'):return 'C binding adapters'
 if u.startswith('js/ported/'):return 'translated game modules'
 if u.startswith('js/standalone/'):return 'standalone services'
 if u.startswith('js/lua') or '/lua/' in u:return 'Lua'
 if u.startswith('frozen/') or 'wasm-replay-support' in u:return 'recorder harness'
 if u.startswith('node:'):return 'Node internals'
 if u.startswith('js/'):return 'other JavaScript'
 return 'V8/native/anonymous'
files=sorted((out/'profiles').glob('*.cpuprofile*')); seen=set()
for file in files:
 match=re.search(r'CPU\.\d+\.\d+\.(\d+)\.',file.name)
 if not match or int(match[1]) not in workers:continue
 pid=int(match[1])
 if a.partial and (not file.name.endswith('.gz') or time.time()-file.stat().st_mtime<3):continue
 try:data=load(file)
 except (FileNotFoundError,EOFError,json.JSONDecodeError):
  if a.partial:continue
  raise
 assert pid not in seen,'Duplicate worker profile '+str(pid)
 seen.add(pid)
 nodes={n['id']:n for n in data['nodes']};parents={c:n['id'] for n in data['nodes'] for c in n.get('children',[])};cache={};tot=0;local=collections.Counter();localphase=collections.Counter()
 def stack(n):
  if n not in cache:
   path=[];q=n
   while q in nodes:path.append(identity(nodes[q]['callFrame']));q=parents.get(q)
   cache[n]=path
  return cache[n]
 for sample,dt in zip(data['samples'],data['timeDeltas']):
  frames=stack(sample);leaf=frames[0];tot+=dt;selftime[leaf]+=dt;local[leaf]+=dt;groups[group(leaf)]+=dt
  for f in set(frames):inclusive[f]+=dt
  for target_file,target_name in [('js/c-runtime/types.js','record'),('js/c-runtime/types.js','canonical'),('js/c-runtime/heap.js','malloc')]:
   index=next((i for i,f in enumerate(frames) if f[0]==target_file and f[1]==target_name),None)
   if index is not None:
    caller=next((f for f in frames[index+1:] if f[0]!=target_file),None)
    if caller:hot_callers[target_file+':'+target_name][caller]+=dt
    owner=next((f for f in frames[index+1:] if f[0].startswith('js/ported/')),None)
    if owner:hot_owners[target_file+':'+target_name][owner]+=dt
  if any(u=='js/ported/allmain.js' and n=='moveloop_core' for u,n,_,_ in frames):phase='turn loop'
  elif any(u=='js/ported/allmain.js' and n=='newgame' for u,n,_,_ in frames):phase='new game'
  elif any(u=='js/ported/restore.js' and ('restore' in n or n=='dorecover') for u,n,_,_ in frames):phase='restore'
  elif any(n=='createStandaloneProgram' for _,n,_,_ in frames):phase='program construction'
  elif any(u=='js/standalone-recorder-adapter.js' and n=='runSegment' for u,n,_,_ in frames):phase='other replay/startup'
  elif leaf[1]=='(garbage collector)':phase='GC (caller unavailable)'
  else:phase='outside replay/unattributed'
  phases[phase]+=dt;localphase[phase]+=dt;phase_functions[phase][leaf]+=dt
 segments=workers[pid];rows.append({'session':segments[0]['session'],'pid':pid,'segments':len(segments),'keys':sum(s['consumedKeys'] for s in segments),'sampledMs':round(tot/1000,3),'profileDurationMs':round((data['endTime']-data['startTime'])/1000,3),'phaseMs':{k:round(v/1000,3) for k,v in localphase.items()},'topSelf':[[*k,round(v/1000,3)] for k,v in local.most_common(8)],'profile':file.name});profilehash[file.name]=hashlib.sha256(file.read_bytes()).hexdigest()
total=sum(selftime.values())
def ranked(c,n=30):return [{'file':k[0],'function':k[1],'line':k[2],'column':k[3],'sampledMs':round(v/1000,3),'percent':round(v*100/total,3) if total else 0} for k,v in c.most_common(n)]
result={'version':1,'complete':len(rows)==44,'workerProfiles':len(rows),'sampledMs':round(total/1000,3),'method':{'nodeVersion':load(out/'pre-run-manifest.json').get('nodeVersion','unknown'),'intervalUs':1000,'timeoutsMs':0,'instrumentation':'NODE_OPTIONS V8 --cpu-prof; no engine or frozen-harness instrumentation','phaseAttribution':'Stack sampling; GC has no caller. Inclusive percentages overlap; self percentages partition worker samples. Whole worker profiles include module loading and scorer comparison outside official timed replay. CPU sampling is an estimate and includes profiler overhead.'},'selfGroups':[{'group':k,'sampledMs':round(v/1000,3),'percent':round(v*100/total,3)} for k,v in groups.most_common()],'phases':[{'phase':k,'sampledMs':round(v/1000,3),'percent':round(v*100/total,3)} for k,v in phases.most_common()],'topSelf':ranked(selftime),'topInclusive':ranked(inclusive),'phaseHotspots':{k:ranked(v,12) for k,v in phase_functions.items()},'hotspotCallers':{k:ranked(v,10) for k,v in hot_callers.items()},'hotspotGameOwners':{k:ranked(v,12) for k,v in hot_owners.items()},'sessions':sorted(rows,key=lambda r:-r['sampledMs']),'profileSha256':profilehash}
stdout=out/'results.stdout.log'
if stdout.exists() and '__RESULTS_JSON__' in stdout.read_text():
 official=json.loads(stdout.read_text().rsplit('__RESULTS_JSON__',1)[1]);result['officialSpeedFit']=official.get('speed');result['profiledSessionsAboveDefault45Seconds']=[r['session'] for r in official['results'] if r.get('time',{}).get('ms',0)>45000];result['officialPassed']=sum(r['passed'] for r in official['results']);result['officialTimings']=[{'session':r['session'],'passed':r['passed'],**r.get('time',{})} for r in official['results']]
if 'officialTimings' in result:
 points=[([1,next(r['segments'] for r in rows if r['session']==t['session']),t['moves']],t['ms']) for t in result['officialTimings'] if 'ms' in t and any(r['session']==t['session'] for r in rows)]
 if len(points)>=3:
  matrix=[[sum(x[i]*x[j] for x,y in points) for j in range(3)]+[sum(x[i]*y for x,y in points)] for i in range(3)]
  try:
   for i in range(3):
    pivot=max(range(i,3),key=lambda k:abs(matrix[k][i]));matrix[i],matrix[pivot]=matrix[pivot],matrix[i];v=matrix[i][i]
    if abs(v)<1e-9:raise ValueError('singular')
    matrix[i]=[n/v for n in matrix[i]]
    for j in range(3):
     if j!=i:
      v=matrix[j][i];matrix[j]=[a-v*b for a,b in zip(matrix[j],matrix[i])]
   coefficients=[r[-1] for r in matrix];mean=sum(y for x,y in points)/len(points);residual=sum((y-sum(a*b for a,b in zip(x,coefficients)))**2 for x,y in points);total_variation=sum((y-mean)**2 for x,y in points)
   result['segmentAwareTimingFit']={'model':'ms = worker intercept + segment coefficient * segments + move coefficient * moves','workerInterceptMs':round(coefficients[0],3),'segmentCoefficientMs':round(coefficients[1],3),'perMoveCoefficientMs':round(coefficients[2],4),'r2':round(1-residual/total_variation,4) if total_variation else 0,'sessions':len(points),'limitation':'Descriptive cross-session fit, not direct phase timing or causal startup measurement; different games/commands have different costs and profiling adds overhead.'}
  except ValueError:pass
if not a.partial:
 assert result['complete'],'All 44 worker profiles required'
 assert len({r['session'] for r in rows})==44,'Exactly one worker profile per session'
 assert 'officialTimings' in result,'Completed official result bundle required'
 assert {r['session'] for r in rows}=={r['session'] for r in result['officialTimings']},'Profile/official session identity'
 integrity=load(out/'post-run-integrity.json');assert integrity['exitCode']==0 and not integrity['changed'],'Successful unmodified run required'
 result['inputIntegrity']=integrity
(out/('profile-summary-partial.json' if a.partial else 'profile-summary.json')).write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps({k:result[k] for k in ['complete','workerProfiles','sampledMs','selfGroups','phases']},indent=2))
