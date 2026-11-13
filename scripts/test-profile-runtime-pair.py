"""Check comparison order, clean overrides, provenance links and fail-fast behavior."""
from pathlib import Path
import json,os,subprocess,sys,tempfile
root=Path(__file__).resolve().parents[1]
checks=0
with tempfile.TemporaryDirectory() as temporary:
 task=Path(temporary);binpath=task/'bin';binpath.mkdir()
 stub='#!'+sys.executable+'\n'+'''import json,os,sys
from pathlib import Path
name=Path(sys.argv[0]).name
args=sys.argv[1:]
for key in ['STANDALONE_RECORDER_ASSETS','STANDALONE_RECORDER_LAYOUTS','STANDALONE_RECORD_LAYOUTS','NODE_OPTIONS']:
 assert key not in os.environ,key
kind='summary' if name=='node' else 'profile' if args[0].endswith('profile-public-recorder.py') else 'cpu'
phase=Path(args[-1]).name.replace('profile-','')
if kind=='profile':
 phase=Path(args[1]).name.replace('runtime-','')
 Path(args[args.index('--output')+1]).mkdir()
with open(os.environ['PAIR_TEST_LOG'],'a')as file:file.write(json.dumps([kind,phase])+'\\n')
if kind=='profile'and os.environ.get('PAIR_TEST_FAIL_PHASE')==phase:sys.exit(7)
'''
 for name in ['python3','node']:
  p=binpath/name;p.write_text(stub);p.chmod(0o755)
 for order,expected in [('baseline-first',['baseline','candidate']),('candidate-first',['candidate','baseline'])]:
  workspace=task/order;workspace.mkdir()
  for phase in ['baseline','candidate']:(workspace/('runtime-'+phase)).mkdir()
  log=workspace/'calls.jsonl';env=os.environ.copy();env.update(PATH=str(binpath)+os.pathsep+env['PATH'],RUNNER_TEMP=str(workspace),COMPARISON_ORDER=order,PAIR_TEST_LOG=str(log))
  for key in ['STANDALONE_RECORDER_ASSETS','STANDALONE_RECORDER_LAYOUTS','STANDALONE_RECORD_LAYOUTS','NODE_OPTIONS']:env[key]='inherited override must be removed'
  subprocess.run(['bash',str(root/'scripts/profile-runtime-pair.sh')],env=env,check=True)
  calls=[json.loads(line)for line in log.read_text().splitlines()]
  assert calls==[[kind,phase]for phase in expected for kind in ['profile','summary','cpu']];checks+=1
  for phase in expected:
   assert (workspace/('profile-'+phase)/'score-repo').resolve()==(workspace/('runtime-'+phase)).resolve();checks+=1
  failure=task/(order+'-failed');failure.mkdir()
  for phase in ['baseline','candidate']:(failure/('runtime-'+phase)).mkdir()
  log=failure/'calls.jsonl';env.update(RUNNER_TEMP=str(failure),PAIR_TEST_LOG=str(log),PAIR_TEST_FAIL_PHASE=expected[0])
  result=subprocess.run(['bash',str(root/'scripts/profile-runtime-pair.sh')],env=env)
  assert result.returncode==7;checks+=1
  assert [json.loads(line)for line in log.read_text().splitlines()]==[['profile',expected[0]]];checks+=1
 invalid=task/'invalid';invalid.mkdir();log=invalid/'calls.jsonl';env.update(RUNNER_TEMP=str(invalid),PAIR_TEST_LOG=str(log),COMPARISON_ORDER='invalid')
 result=subprocess.run(['bash',str(root/'scripts/profile-runtime-pair.sh')],env=env,capture_output=True)
 assert result.returncode==2 and not log.exists();checks+=1
print('PASS',checks,'profiling runner order/provenance/override/failure controls; no game acceptance')
