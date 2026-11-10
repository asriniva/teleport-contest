from pathlib import Path
import json,hashlib,re
r=Path(__file__).resolve().parents[3];w=r/'.cache/cmd-first-pass';src=(r/'.cache/wasm64-build/tree/src/cmd.c').read_bytes();h=hashlib.sha256(src).hexdigest();assert h=='a14c0fc8706bd9957f8f4aab7f9e2abbd30eb5f4e43166b90a8bfeb25094a7ce'
assert (r/'nethack-c/upstream/src/cmd.c').read_bytes()==src
j=json.load(open(r/'nethack-c/wasm/tu-fragments/cmd-schema.json'));provenance=json.load(open(r/'nethack-c/wasm/tu-fragments/cmd-provenance.json'));F=provenance['functions'];
for path,expected in provenance['headerHashes'].items():assert hashlib.sha256((r/path).read_bytes()).hexdigest()==expected,('changed profile header',path)
core=(r/'js/ported/cmd.js').read_text();runtime=(r/'js/ported/cmd-runtime.js').read_text();support=(r/'nethack-c/wasm/tu-fragments/cmd-support.c').read_text();lib=(r/'nethack-c/wasm/tu-libraries/cmd.js').read_text()
assert re.findall(r'^export function (\w+)\(',core,re.M)==[f['name']for f in F];assert len(F)==148
for f in F:
 ps=[p['name']for p in f['parameters']];m=re.search(r'^export function '+f['name']+r'\(([^)]*)\)',core,re.M);assert m.group(1).split(',')==ps if ps else m.group(1)==''
assert len(j['dependencies'])==270 and len(j['variadics'])==131 and len(j['functionPointers'])==172
assert len(j['schema'])==56 and sum(len(v['fields'])for v in j['schema'].values())==197
assert len(j['data'])==10 and len(j['localStatics'])==21
assert j['data']['move_funcs']['type']=='int (*[10][3])(void)'
assert 'sizeof(int(*[3])(void))==24' in support and 'sizeof(int(*[10][3])(void))==240' in support
assert j['sourceParameters']['set_occupation'][2]['canonical']=='long' and j['sourceParameters']['get_count'][2]['canonical']=='long'
assert 'do_screen_description(*value,looked,sym,buf,first,pm)'in support
assert 'do_screen_description:(a0,a1,a2,a3,a4,a5)=>_teleport_cmd_screen_description' in lib
assert 'addOnInit(() => Module.nethackPorted.initializeCmd(teleportCmdServices()))' in lib
assert 'Object.setPrototypeOf'not in runtime and 'new Proxy(Object.create(null)'in runtime and 'state.services=previous'in runtime
assert '_teleport_cmd_screen_description' not in core
paths=re.findall(r'C.field\([^\n]*?,"([^"]+)","([^"]+)"\)',core)
for k,f in paths:assert k in j['schema']and f in {x['name']for x in j['schema'][k]['fields']},(k,f)
# Assert all referenced exact typed paths using a balanced quote-level regexp, no rm aliases guessed.
for k,f in re.findall(r',"([^"]+)","([^"]+)"\)\.(?:value|address)',core):
 if k in j['schema']:assert f in {x['name']for x in j['schema'][k]['fields']},(k,f)
assert len(provenance['pointerCompoundAssignments'])==0 and len(provenance['dereferencedIncrements'])==0 and len(provenance['pointerIncrements'])==25
assert sum('ext_func_tab'in n['type']for n in provenance['pointerIncrements'])==16
# Original comments, including inactive conditional comments, occur in exact source order.
comments=re.findall(rb'/\*[\s\S]*?\*/|//[^\n]*',src);cursor=0
for c in comments:
 at=core.find(c.decode(),cursor)
 assert at>=0,('missing source comment',c[:100]);cursor=at+len(c.decode())
# True public storage is separate zero-only data; no source algorithm or reader in its TU.
storage=(r/'nethack-c/wasm/tu-fragments/cmd-public-storage.c').read_text();assert all(n in storage for n in ['unavailcmd[26]','levltyp[39]','extcmdlist[171]']);assert 'Unavailable'not in storage and 'ef_funct'not in storage
assert sum(len(s.encode())+1 for s in j['literals'])==12778
assert len(j['literals'])==681
print('CMD source/ABI/data/member guards PASS;148 functions,197 fields,172 native identities,25 pointer increments,0 pointer compound/0 deref increment; all source comments ordered')
