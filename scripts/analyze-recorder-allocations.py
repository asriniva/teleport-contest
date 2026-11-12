#!/usr/bin/env python3
"""Summarize V8 sampled allocation sites, including collected objects."""
import argparse,collections,gzip,json,pathlib,hashlib
p=argparse.ArgumentParser();p.add_argument('profile',type=pathlib.Path);p.add_argument('--out',required=True,type=pathlib.Path);a=p.parse_args();d=json.load(gzip.open(a.profile,'rt'));own=collections.Counter();inclusive=collections.Counter();total=0

def key(frame):
 u=frame['url'];i=u.find('/js/');u=u[i+1:] if i>=0 else u
 if '/frozen/' in u:u='frozen/'+u.split('/frozen/',1)[1]
 return(u,frame['functionName'],frame['lineNumber']+1,frame['columnNumber']+1)
stack=[(d['profile']['head'],[])]
while stack:
 n,parents=stack.pop();k=key(n['callFrame']);size=n['selfSize'];total+=size;own[k]+=size
 for frame in set(parents+[k]):inclusive[frame]+=size
 stack.extend((c,parents+[k]) for c in n.get('children',[]))
def rows(c):return[{'file':k[0],'function':k[1],'line':k[2],'column':k[3],'estimatedBytes':v,'percent':round(v*100/total,3)} for k,v in c.most_common(40)]
result={'version':1,'nodeVersion':d['nodeVersion'],'wallMs':d['wallMs'],'parameters':d['parameters'],'toolSha256':d['toolSha256'],'rawSha256':hashlib.sha256(a.profile.read_bytes()).hexdigest(),'estimatedAllocatedBytes':total,'topSelf':rows(own),'topInclusive':rows(inclusive),'limits':['Poisson-sampled estimated allocation bytes, not retained heap size or exact allocation counts.','Both collected and live objects included; allocation sampling adds overhead.','One recorded workload is evidence for allocation sites, not44-session performance or deadline acceptance.']};a.out.write_text(json.dumps(result,indent=2)+'\n');print(json.dumps({'estimatedBytes':total,'topSelf':result['topSelf'][:5]},indent=2))
