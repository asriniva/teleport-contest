from pathlib import Path
import re,json,subprocess,hashlib,collections
import argparse
parser=argparse.ArgumentParser();parser.add_argument('--out',required=True,type=Path);parser.add_argument('--source-root',type=Path);args=parser.parse_args();code_root=Path(__file__).resolve().parents[1];w=args.out.resolve();r=(args.source_root or code_root).resolve();c=(r/'nethack-c/upstream/util/sfexpasc.c').read_text();p=code_root/'js/ported-utilities/sfexpasc/sfexpasc.js';j=p.read_text();fs=json.loads((w/'configured-functions.json').read_text());found=re.findall(r'export function (\w+)\(([^)]*)\)',j)
def check(s):
 f=re.findall(r'export function (\w+)\(([^)]*)\)',s);assert[n for n,a in f]==[n['name']for n in fs]
 for(n,a),original in zip(f,fs):assert[x.strip()for x in a.split(',')if x.strip()]==[v['name']for v in original['parameters']],n
 comments=lambda text:collections.Counter(re.findall(r'/\*[\s\S]*?\*/',text));assert comments(c)==comments(s)
 for k,v in json.loads((w/'source-procedure-tables.json').read_text()).items():assert json.loads(re.search('export const '+k+r' = (.*?);\n',s)[1])==v
 return True
check(j);before=hashlib.sha256(p.read_bytes()).hexdigest();subprocess.run(['python3',str(code_root/'scripts/regenerate-utility-sfexpasc.py'),'--out',str(w),'--source-root',str(r)],check=True,stdout=subprocess.DEVNULL);assert hashlib.sha256((w/'candidate/sfexpasc.js').read_bytes()).hexdigest()==before
for wrong in[j.replace('exportascii_sfo_any(nhfp,','exportascii_sfo_any(nhfp_changed,',1),j.replace('/* avoid the global.h define */','/* changed */',1),j.replace('"exportascii"','"changed"',1)]:
 try:check(wrong)
 except AssertionError:pass
 else:raise AssertionError('guard mutation was accepted')
(w/'guard-results.json').write_text(json.dumps({'status':'PASS','configuredOriginalFunctions':len(fs),'expandedEmptyFunctions':sum(f['emptyBody']for f in fs),'commentsExact':len(re.findall(r'/\*[\s\S]*?\*/',c)),'allNamesFormalsExact':True,'sourceProcedureSelectorsExact':True,'exactRegenerationSha256':before,'guardNegatives':3},indent=2)+'\n');print('PASS139 source/formals/comments/procedureselectors/exactregeneration/3negatives')
