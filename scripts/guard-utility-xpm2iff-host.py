from pathlib import Path
import json,re,subprocess,hashlib
import argparse
parser=argparse.ArgumentParser(description='Check actual source/comments/control/import declarations for this utility output.')
parser.add_argument('--out',required=True,type=Path)
parser.add_argument('--source-root',type=Path,default=Path(__file__).resolve().parent.parent)
args=parser.parse_args();code_root=Path(__file__).resolve().parent.parent;b=args.out.resolve();r=args.source_root.resolve()
s=(b/'source/xpm2iff_host.c').read_text();core=(code_root/'js/ported-utilities/xpm2iff-host.js').read_text();original=r/'nethack-c/upstream/sys/amiga/xpm2iff_host.c'
assert s.encode()==original.read_bytes()
assert re.findall(r'/\*.*?\*/',s,re.S)==re.findall(r'/\*.*?\*/',core,re.S),'original38 comments/order'
inv=json.loads((b/'inventory.json').read_text());names=[f['name']for f in inv['functions']];ast=json.loads((b/'source-ast.txt').read_text());funcs={n['name']:n for n in ast['inner']if n.get('kind')=='FunctionDecl' and n.get('name')in names and any(x.get('kind')=='CompoundStmt'for x in n.get('inner',[]))};assert list(funcs)==names
kinds=['IfStmt','ForStmt','WhileStmt','DoStmt','ReturnStmt','ContinueStmt']
def walk(n):
 yield n
 for c in n.get('inner',[]):yield from walk(c)
expected={}
for name,n in funcs.items():
 body=next(x for x in n['inner']if x['kind']=='CompoundStmt')
 expected[name]={'params':[x['name']for x in n.get('inner',[])if x.get('kind')=='ParmVarDecl'],'type':n['type']['qualType'],'control':{k:sum(x.get('kind')==k for x in walk(body))for k in kinds}}
(b/'expected-census.json').write_text(json.dumps(expected,indent=2)+'\n')
js=r/'.cache/emsdk/node/24.19.0_64bit/bin/node'
p=subprocess.run([str(js),str(code_root/'scripts/guard-utility-xpm2iff-host.cjs'),'--out',str(b),'--source-root',str(r)],cwd=r,stdout=subprocess.PIPE,stderr=subprocess.STDOUT);(b/'logs/source-guards.log').write_bytes(p.stdout);print(p.stdout.decode());assert p.returncode==0
before=json.loads((b/'before-hashes.json').read_text());after={n:hashlib.sha256((r/n).read_bytes()).hexdigest()for n in before};assert before==after
(b/'after-hashes.json').write_text(json.dumps(after,indent=2)+'\n')
result={'status':'PASS','sourceBytes':len(s.encode()),'originalFunctions':len(names),'allOriginalComments':38,'actualCAndJSFormalsOrderAndControlCounts':True,'nativeMixedPolicyBodyCount':0,'inputHashesUnchanged':len(before),'mixedGeneratedSourceReproducedFromSource':True}
# Mixed body removal is restricted to six exact captured function source slices.
mixed=(b/'generated/mixed.c').read_text()
reproduced=s
for entry in inv['functions']:
 source_slice='\n'.join(s.splitlines()[entry['startLine']-1:entry['endLine']])
 assert hashlib.sha256(source_slice.encode()).hexdigest()==entry['sourceSliceSha256']
 declaration='extern '+entry['signature'].removeprefix('static ')+';'
 assert reproduced.count(source_slice)==1
 reproduced=reproduced.replace(source_slice,declaration,1)
assert mixed==reproduced,'exact source body-removal reproduction'
for n in names:assert re.search(r'extern [^;{}]*\b'+n+r'\([^;{}]*\);',mixed),n
assert not re.search(r'\b(?:'+('|'.join(names))+r')\([^;{}]*\)\s*\{',mixed)
(b/'guard-result.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result))
