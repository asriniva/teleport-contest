"""Read-only source data, RNG provenance and private-boundary guards for VAULT."""
from pathlib import Path
import ast,json,re
root=Path(__file__).resolve().parents[3]
source=(root/'nethack-c/upstream/src/vault.c').read_text()
assert source==(root/'.cache/wasm64-build/tree/src/vault.c').read_text(),'Review changed prepared VAULT source'
core=(root/'js/ported/vault.js').read_text()
support=(root/'nethack-c/wasm/tu-fragments/vault-support.inc').read_text()
library=(root/'nethack-c/wasm/tu-libraries/vault.js').read_text()
layout=(root/'scripts/tu-vault-layout.h').read_text()
runtime=(root/'js/ported/vault-runtime.js').read_text()
clean=re.sub(r'/\*.*?\*/|//[^\n]*',lambda m:'\n'*m[0].count('\n'),source,flags=re.S)
literals=sorted(set(ast.literal_eval(x) for x in re.findall(r'"(?:\\.|[^"\\])*"',clean)))
capacity=sum(len(x.encode())+1 for x in literals)
actual=json.loads(re.search(r'var sourceLiterals=new Set\((\[[^\n]*\])\);',library)[1])
assert actual==literals,'Review changed VAULT source literal corpus'
assert int(re.search(r'teleport_vault_literals\[(\d+)\]',support)[1])==capacity
assert '!sourceLiterals.has(value)' in library,'Only actual source literals may be interned'
# vault.c owns no file-scope or static-local array initializers in this profile.
# Arrays accessed through EGD, global grids and local automatic buffers retain
# typed ABI backing; new source-owned arrays require an explicit port review.
assert not re.search(r'\bstatic(?:fn)?\s+[^;{}]*\[[^]]*\]\s*=',clean),'Review new source-owned VAULT array'
functions=re.findall(r'export function (\w+)\(',core)
assert len(functions)==25
private=re.findall(r'\bstaticfn\s+\w+\s+(\w+)\([^;]+\)\s*\{',clean)
assert len(private)==12
assert set(re.findall(r'teleport_vault_test_(\w+)__deps',library))==set(private),'Review private alias inventory'
current='';sites=[]
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
 assert m,('Missing original VAULT RNG provenance',call[1])
 js_sites.append((call[1],int(m[1]),m[2]))
assert sites==js_sites,('Changed original VAULT RNG sites',sites,js_sites)
callers=re.findall(r'"(\w+)"',re.search(r'teleport_vault_callers\[\]=\{([^}]+)\}',support)[1])
assert callers==list(dict.fromkeys(site[2] for site in sites))
assert 'debugcore("vault.c",TRUE)' in support
assert 'config_SOUND:0' in runtime and 'SetVoice(){}' in runtime and 'VAULT_META(config_SOUND,1)' in layout,'Review changed SetVoice configuration'
assert 'typ = C.uchar(crm.typ)' in core and 'typ = C.uchar((crm = C.levl[nx][ny]).typ)' in core,'Source uchar local requires explicit narrowing'
for field in ['parentmid','m_id','mappearance','m_ap_type']:
 assert field in runtime
print(f'VAULT metadata: {len(functions)} functions/{len(private)} private; {len(literals)} source strings/{capacity} bytes; {len(sites)} RNG sites verified; no source-owned static arrays.')
