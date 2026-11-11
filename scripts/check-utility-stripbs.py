from pathlib import Path
import re,json,hashlib,argparse
stage=Path(__file__).resolve().parents[1]
p=argparse.ArgumentParser();p.add_argument('--out',type=Path,required=True);p.add_argument('--source-root',type=Path,default=stage);args=p.parse_args();w=args.out.resolve();r=args.source_root.resolve()
assert not(w/'source-guard.json').exists(),'Refuse existing source guard result'
c=(r/'nethack-c/upstream/util/stripbs.c').read_text();j=(stage/'js/ported-utilities/stripbs.js').read_text();a=json.loads((w/'configured-functions.json').read_text())
assert[n['name']for n in a]==re.findall(r'export function (\w+)\(',j)==['main']
comments=re.findall(r'/\*.*?\*/',c,re.S);assert all(comment in j for comment in comments)
assert 'C.errno != C.EOF'in j and 'return trouble ? C.EXIT_FAILURE : C.EXIT_SUCCESS;'in j
result={'status':'PASS','originalSha256':hashlib.sha256(c.encode()).hexdigest(),'originalBlockComments':len(comments),'singleOriginalBoundary':'main(argc,argv)','compilerDerivedFunctions':a}
(w/'source-guard.json').write_text(json.dumps(result,indent=2)+'\n');print('PASS original main/comments/errno-status policy')
