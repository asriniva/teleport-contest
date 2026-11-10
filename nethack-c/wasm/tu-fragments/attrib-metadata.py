"""Read-only guards for ATTRIB source-owned arrays, literals and RNG sites."""
from pathlib import Path
import ast,json,re
root=Path(__file__).resolve().parents[3]
source=(root/'nethack-c/upstream/src/attrib.c').read_text()
assert source==(root/'.cache/wasm64-build/tree/src/attrib.c').read_text(),'Review changed prepared ATTRIB source'
core=(root/'js/ported/attrib.js').read_text()
support=(root/'nethack-c/wasm/tu-fragments/attrib-support.inc').read_text()
library=(root/'nethack-c/wasm/tu-libraries/attrib.js').read_text()
clean=re.sub(r'/\*.*?\*/|//[^\n]*',lambda m:'\n'*m[0].count('\n'),source,flags=re.S)
coreclean=re.sub(r'/\*.*?\*/|//[^\n]*','',core,flags=re.S)
literals=sorted(set(ast.literal_eval(x) for x in re.findall(r'"(?:\\.|[^"\\])*"',clean)))
capacity=sum(len(x.encode())+1 for x in literals)
actual=json.loads(re.search(r'var sourceLiterals=new Set\((\[[^\n]*\])\);',library)[1])
assert actual==literals,'Review changed ATTRIB source literal corpus'
assert int(re.search(r'teleport_attrib_literals\[(\d+)\]',support)[1])==capacity
# Match every original innate row, preserving both the table and row order.
cs=re.search(r'} arc_abil\[\](.*?)staticfn void exerper',source,re.S)[0]
ctables={}
for match in re.finditer(r'(\w+_abil)\[\]\s*=\s*\{',cs):
 start=match.end();depth=1;end=start
 while depth:
  depth+=(cs[end]=='{')-(cs[end]=='}');end+=1
 rows=[]
 for row in re.findall(r'\{([^{}]+)\}',cs[start:end-1]):
  m=re.fullmatch(r'\s*(\d+)\s*,\s*(?:&\(?\s*(H\w+)\s*\)?|0)\s*,\s*("(?:\\.|[^"\\])*"|0)\s*,\s*("(?:\\.|[^"\\])*"|0)\s*',row)
  assert m,('Review original innate row',row)
  rows.append([int(m[1]),m[2] or 0,ast.literal_eval(m[3]),ast.literal_eval(m[4])])
 ctables[match[1]]=rows
jstables={name:json.loads(value) for name,value in re.findall(r'export const (\w+_abil) = (\[.*?\]);',core,re.S)}
assert list(jstables)==list(ctables),'Review innate table declaration order'
assert jstables==ctables,'Review original innate row/data/pointer symbols'
count=sum(map(len,ctables.values()))
assert int(re.search(r'teleport_attrib_tables\[(\d+)\]',support)[1])==count
# The three attribute name arrays retain all exact original strings and order.
for name in ['plusattr','minusattr','attrname']:
 c=re.search(r'\*const '+name+r'\[\]\s*=\s*\{([^}]+)\}',source,re.S)[1]
 expected=[ast.literal_eval(x) for x in re.findall(r'"(?:\\.|[^"\\])*"',c)]
 actual=json.loads(re.search(r'\b'+name+r' = (\[[^]]+\])',core,re.S)[1])
 assert actual==expected,('Changed attribute strings',name)
# Source-owned poison-delivery and exercise text catalogue values/order.
poison=re.search(r'} poiseff\[\] = \{(.*?)\n};',source,re.S)[1]
expected=re.findall(r'\{\s*(You_feel|Your|You),\s*("[^"]*")\s*\}',poison)
actual=re.findall(r'\{ delivery_func: "(\w+)", effect_msg: ("[^"]*") \}',core)
assert actual==expected,'Changed poison-effect delivery policy'
exercise=re.search(r'exertext\[A_MAX\]\[2\] = \{(.*?)\n};',clean,re.S)[1]
expected=[re.findall(r'"[^"]*"|\b0\b',row) for row in re.findall(r'\{([^{}]+)\}',exercise)]
actual=re.search(r'export const exertext = (\[.*?\]);',coreclean,re.S)[1]
actual=[[json.dumps(s) if isinstance(s,str) else str(s) for s in row] for row in ast.literal_eval(actual)]
assert actual==expected,'Changed exercise/abuse catalogue'
# All original source RNG calls preserve the file basename, line and function.
functions=re.findall(r'export function (\w+)\(',core);current='';sites=[]
for line,txt in enumerate(clean.splitlines(),1):
 m=re.match(r'^(\w+)\(',txt)
 if m and m[1] in functions:current=m[1]
 for call in re.finditer(r'\b(rn2|rn1|rnd|d)\(',txt):sites.append((call[1],line,current))
js_sites=[]
for call in re.finditer(r'\bC\.(rn2|rn1|rnd|d)\(',core):
 depth=1;end=call.end()
 while depth:
  depth+=(core[end]=='(')-(core[end]==')');end+=1
 m=re.search(r',\s*(\d+)\s*,\s*"([^"]+)"\s*$',core[call.end():end-1])
 assert m,('Missing original ATTRIB RNG provenance',call[1])
 js_sites.append((call[1],int(m[1]),m[2]))
assert sites==js_sites,('Changed original ATTRIB RNG sites',sites,js_sites)
callers=re.findall(r'"(\w+)"',re.search(r'teleport_attrib_callers\[\]=\{([^}]+)\}',support)[1])
assert callers==list(dict.fromkeys(site[2] for site in sites))
assert 'debugcore("attrib.c",TRUE)' in support,'debugpline must use original showdebug default'
assert ',1204,"acurr"' in support and source.splitlines()[1203].strip()=='assert(chridx >= 0 && chridx < A_MAX);'
assert '$teleportAttribInit__postset' in library and 'addOnInit(() => teleportAttribInit());' in library and "initializeAttrib(teleportAttribServices())" in library,'Public attrname requires actual module startup initialization'
assert 'teleport_attrib_names[6] __asm__("attrname")' in support,'Public attrname must alias zero-only mutable storage'
print(f'ATTRIB metadata: {len(ctables)} innate tables/{count} rows; {len(literals)} source strings/{capacity} bytes; {len(sites)} RNG sites verified.')
