"""Independent configured C-AST extraction of all six source static objects."""
from pathlib import Path
import ast,json,os
R=Path(__file__).resolve().parents[5];w=R/'.cache/uhitm-author';outdir=Path(os.environ.get('UHITM_GUARD_WORK',str(w)));outdir.mkdir(parents=True,exist_ok=True);A=json.loads((w/'ast.json').read_text());names={n['name']for n in json.loads((w/'boundary-inventory.json').read_text())['staticVariables']};out={}
def value(n):
 if n['kind']=='StringLiteral':return ast.literal_eval(n['value'])
 if n['kind']=='IntegerLiteral':return int(n['value'])
 if len(n.get('inner',[]))==1:return value(n['inner'][0])
 raise ValueError(n)
def walk(n):
 if n.get('kind')=='VarDecl'and n.get('name')in names and n.get('storageClass')=='static':out[n['name']]={'type':n['type']['qualType'],'initializer':value(n['inner'][-1])if n.get('init')else None}
 for c in n.get('inner',[]):walk(c)
walk(A);assert set(out)==names;assert len(out)==6
(outdir/'source-data.json').write_text(json.dumps(out,indent=2)+'\n');print('UHITM C data:6 static declarations,3 readonly strings,3 persistent mutable objects')

F=json.loads((w/'functions.json').read_text());strings=set()
def literals(n):
 if n.get('kind')=='StringLiteral':strings.add(ast.literal_eval(n['value']))
 for c in n.get('inner',[]):literals(c)
for f in F:literals(f)
(outdir/'body-string-literals.json').write_text(json.dumps(sorted(strings),indent=2)+'\n')
