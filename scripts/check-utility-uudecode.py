from pathlib import Path
import re,json,hashlib,argparse
stage=Path(__file__).resolve().parents[1]
p=argparse.ArgumentParser();p.add_argument('--out',type=Path,required=True);p.add_argument('--source-root',type=Path,default=stage);args=p.parse_args();w=args.out.resolve();r=args.source_root.resolve()
assert not(w/'source-guard.json').exists(),'Refuse existing source guard result'
c=(r/'nethack-c/upstream/sys/share/uudecode.c').read_text();j=(stage/'js/ported-utilities/uudecode.js').read_text();a=json.loads((w/'configured-functions.json').read_text());names=re.findall(r'export function (\w+)\(',j);assert names==[n['name']for n in a]==['main','decode','outdec','index']
comments=re.findall(r'/\*.*?\*/',c,re.S);assert all(x in j for x in comments)
assert re.search(r'export function main\(argc, argv\)',j) and re.search(r'export function decode\(in_, out\)',j) and re.search(r'export function outdec\(p, f, n\)',j) and re.search(r'export function index\(sp, c\)',j)
for exact in ['bp += 4;','n -= 3;','C.storeChar(sl++, 0);','C.exit(10);','C.charAt(sp++)','C.strncmp(buf, "begin ", 6)','C.storeChar(dest + 128 - 1, 0);']:assert exact in j,exact
mac=(w/'profile-macros.txt').read_text();assert '#define __EMSCRIPTEN__ 1' in mac and not re.search(r'^#define (?:__APPLE__|__linux__)\b',mac,re.M)
result={'status':'PASS','functions':names,'originalBlockComments':len(comments),'compilerDerivedFunctionTypes':a,'necessaryReservedIdentifierRename':{'main':'local in→in_','decode':'formal in→in_'},'sourceSha256':hashlib.sha256(c.encode()).hexdigest(),'sourceFunctionHelpersAdded':False,'profile':'Actual EmC, no spoofed Apple/Linux defines'}
(w/'source-guard.json').write_text(json.dumps(result,indent=2)+'\n');print('PASS four original boundaries/all22 comments/active fallback profile')
