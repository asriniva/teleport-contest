"""Validate EXPLODE's literal pool, configured RNG provenance and symbol ABI.

This check reads upstream/prepared source and the staged adapter; it does not
rewrite or execute either NetHack implementation. Run before integrating it.
"""
from pathlib import Path
import ast,json,re
root=Path(__file__).resolve().parents[3]
source=(root/'nethack-c/upstream/src/explode.c').read_text()
prepared=(root/'.cache/wasm64-build/tree/src/explode.c').read_text()
assert source==prepared,'Review changed configured EXPLODE source'
clean=re.sub(r'/\*.*?\*/|//[^\n]*',lambda m:'\n'*m[0].count('\n'),source,flags=re.S)
literals=sorted(set(ast.literal_eval(s) for s in re.findall(r'"(?:\\.|[^"\\])*"',clean)))
capacity=sum(len(s.encode())+1 for s in literals)
library=(root/'nethack-c/wasm/tu-libraries/explode.js').read_text()
actual=json.loads(re.search(r'var sourceLiterals=new Set\((\[[^\n]+\])\);',library)[1])
assert actual==literals,'Review changed EXPLODE literal corpus'
support=(root/'nethack-c/wasm/tu-fragments/explode-support.inc').read_text()
assert int(re.search(r'teleport_explode_literals\[(\d+)\]',support)[1])==capacity
# Original line numbers must agree with every JS RNG invocation. The scanner
# excludes comments and strings, so diagnostics and commented calls cannot
# accidentally satisfy a provenance assertion.
core=(root/'js/ported/explode.js').read_text()
current='';sites=[]
for lineno,line in enumerate(clean.splitlines(),1):
 match=re.match(r'^(explosionmask|engulfer_explosion_msg|explode|scatter|splatter_burning_oil|explode_oil|adtyp_to_expltype|mon_explodes)\(',line)
 if match:current=match[1]
 for rng in re.finditer(r'\b(rn2|rnd|d)\(',line):sites.append((rng[1],lineno,current))
js_sites=[]
for rng in re.finditer(r'\bC\.(rn2|rnd|d)\(',core):
 depth=1;end=rng.end()
 while depth:
  if core[end]=='(':depth+=1
  if core[end]==')':depth-=1
  end+=1
 args=core[rng.end():end-1]
 match=re.search(r",\s*(\d+)\s*,\s*'([^']+)'\s*$",args)
 assert match,('Missing EXPLODE RNG source attribution',args)
 js_sites.append((rng[1],int(match[1]),match[2]))
assert js_sites==sites,('Changed original EXPLODE RNG sites',sites,js_sites)
assert re.search(r'teleport_explode_callers\[\]=\{"scatter","splatter_burning_oil","mon_explodes"\}',support)
# Explicitly retain two distinct original nh_snprintf source locations.
for line in [653,658]:assert re.search(r',\s*'+str(line)+r'\);',core)
print(f'EXPLODE metadata: {len(literals)} source strings/{capacity} bytes; {len(sites)} original RNG sites verified.')
