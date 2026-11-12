"""Actual configured PICKUP source/data/type/CPP/alias/RNG/control guard."""
from pathlib import Path
import json,re,hashlib,subprocess,argparse
r=Path(__file__).resolve().parents[1];w=r/'.cache/pickup-first-pass';m=json.loads((r/'nethack-c/wasm/tu-fragments/pickup-source-metadata.json').read_text());s=json.loads((r/'nethack-c/wasm/tu-fragments/pickup-schema.json').read_text());c=(r/'nethack-c/upstream/src/pickup.c').read_text();j=(r/'js/ported/pickup.js').read_text();abi=(r/'nethack-c/wasm/tu-fragments/pickup-support.c').read_text();lib=(r/'nethack-c/wasm/tu-libraries/pickup.js').read_text();runtime=(r/'js/nethack/bindings/pickup.js').read_text()
assert c==(r/'.cache/wasm64-build/tree/src/pickup.c').read_text();assert hashlib.sha256(c.encode()).hexdigest()==m['sourceSHA256']=='915da0f8fce16461cc42a0035f7ef3e9847fc8f8ee3708a7f017ad6587383134'
# Preserve historical pins through the exact already-reviewed builder inverse only.
for p,h in m['compilerInputHashes'].items():
 if p=='nethack-c/wasm/build.py':
  from importlib.util import spec_from_file_location,module_from_spec
  reviewed_path=r/'scripts/reviewed_build_provenance.py'
  assert hashlib.sha256(reviewed_path.read_bytes()).hexdigest()=='3bfff734265ce4ab4abc578ce25d01a6d5c0ef92f9d5ad471024644cc3ca5b1b','Unreviewed builder provenance helper'
  reviewed_spec=spec_from_file_location('pickup_reviewed_build',reviewed_path)
  reviewed=module_from_spec(reviewed_spec);reviewed_spec.loader.exec_module(reviewed)
  input_bytes=reviewed.nhlua_transport_baseline(r,h)
 else:input_bytes=(r/p).read_bytes()
 assert hashlib.sha256(input_bytes).hexdigest()==h,p
assert hashlib.sha256((w/'inventory-notes.txt').read_bytes()).hexdigest()==m['inventorySHA256']=='967f63706dcc7eb2973dc58a9eaf73350560d5a2cadff9d3404dda3ef6d1b544'
f=m['functions'];assert len(f)==66 and sum(x['linkage']=='static'for x in f)==35
assert re.findall(r'^export function (\w+)\(([^)]*)\)',j,re.M)==[(x['name'],','.join(p['name']for p in x['parameters']))for x in f]
comments=re.findall(r'/\*[\s\S]*?\*/',c);assert len(comments)==478 and all(x in j for x in comments)
for x in f:assert s['functionTypes'][x['name']]==x['type']['qualType'];assert ('teleport_pickup_'if x['linkage']=='static'else'')+x['name']+'__sig:'in lib
assert len(s['statics'])==10 and not any(x['public']for x in s['statics'])
for row in s['statics']:assert row['js']in j
assert [x['sourceName']for x in s['statics']]==['slightloadpfx','moderateloadpfx','nearloadpfx','overloadpfx','vmc_count','costly','sc','explaintext','lootchars','abc_chars']
assert next(x for x in s['statics']if x['sourceName']=='explaintext')['type']=='char *[14]'
assert m['sourceEnums']==[{'name':'tipping_check_values','offset':131662,'values':{'TIPCHECK_OK':0,'TIPCHECK_LOCKED':1,'TIPCHECK_TRAPPED':2,'TIPCHECK_CANNOT':3,'TIPCHECK_EMPTY':4}}]
assert 'export const TIPCHECK_OK=0,TIPCHECK_LOCKED=1,TIPCHECK_TRAPPED=2,TIPCHECK_CANNOT=3,TIPCHECK_EMPTY=4;'in j
assert 'TIPCHECK_'not in abi and not re.search(r'\bstatic\b[^;\n]*=',abi) and not re.search(r'\b(?:for|while|do)\s*[({]',abi)
assert 'pickup.c'not in abi and 'initializePickup'not in lib
assert j.count('/* original goto ')==11 and j.count('/* original label ')==8
for name in ['ask_again','menu_pickup','end_query','pickupdone','query_done','lootcont','lootmon','containerdone']:assert '/* original label '+name+' */'in j
assert j.count('function menu_pickup(){')==1 and 'ask_again: for(;;)'in j and 'loot_cycle: for(;;)'in j
for name,count in {'rng_log_set_caller':13,'rng_log_enabled':13,'rn2':16,'rnd':6,'d':4,'rn2_on_display_rng':5}.items():assert len(re.findall(r'C\.'+name+r'\(',j))==count,(name,count)
assert len(s['dependencies'])==186 and len(s['variadics'])==120 and len(s['callbackCalls'])==42 and not s['dynamicVariadics']
assert s['ownedFunctionPointers']==['all_but_uchain','allow_all','allow_category','ck_bag','in_container','n_or_more','out_container','stash_ok','tip_ok']
assert s['nativeFunctionPointers']==['Yname2','Ysimple_name2','ansimpleoname','doforce','doname','is_worn','yname','ysimple_name']
assert j.count('const __old=')==61 and 'C.sizes["struct mi"]'in j and 'C.sizes["struct sortloot_item"]'in j
assert 'const states=new WeakMap()'in runtime and 'finally{services.stackRestore(stackFrame);}'in runtime
assert 'const forwarding=new Proxy(Object.create(null)'in runtime and 'state.env=createPickupEnvironment(forwarding)'in runtime and 'finally{state.services=previous;}'in runtime
assert 'Object.setPrototypeOf'not in runtime and 'initializePickup'not in runtime
# Compiler computation types govern compound operations independently of the
# stored lvalue type. Audit every configured body, not a text-only int/long seam.
ast=json.loads((w/'ast.json').read_text());compound=[]
def compound_walk(n,owner=None):
 if n.get('kind')=='FunctionDecl'and n.get('name')in {f['name']for f in m['functions']}and not n.get('loc',{}).get('includedFrom'):owner=n['name']
 if owner and n.get('kind')=='CompoundAssignOperator':compound.append({'owner':owner,'op':n['opcode'],'stored':n['type']['qualType'],'lhs':n['computeLHSType']['qualType'],'result':n['computeResultType']['qualType']})
 for c in n.get('inner',[]):compound_walk(c,owner)
compound_walk(ast)
assert len(compound)==31
assert [x for x in compound if x['stored']!=x['lhs']or x['stored']!=x['result']]==[{'owner':'carry_count','op':'-=','stored':'int','lhs':'long','result':'long'}]
assert j.count('(wt=C.i32(C.i64(wt)-')==1
# Address-of obligations: actual nonlocal DeclRef operands are record storage,
# not scalar globals. The one addressed ParmVarDecl needs an initialized cell.
address_rows=[]
def address_walk(n,owner=None,local_ids=None):
 if n.get('kind')=='FunctionDecl'and n.get('name')in {f['name']for f in m['functions']}and not n.get('loc',{}).get('includedFrom'):
  owner=n['name'];local_ids=set()
  def local_walk(x):
   if x.get('kind')in ['VarDecl','ParmVarDecl']:local_ids.add(x['id'])
   for child in x.get('inner',[]):local_walk(child)
  local_walk(n)
 if owner and n.get('kind')=='UnaryOperator'and n.get('opcode')=='&':
  child=n['inner'][0]
  while child.get('kind')in ['ParenExpr','ImplicitCastExpr']:child=child['inner'][0]
  if child.get('kind')=='DeclRefExpr':
   d=child['referencedDecl'];address_rows.append((owner,d['name'],d['kind'],child['type']['qualType'],d['id']in local_ids))
 for child in n.get('inner',[]):address_walk(child,owner,local_ids)
address_walk(ast)
assert len(address_rows)==109
assert {(name,t)for owner,name,kind,t,local in address_rows if not local}=={('nul_glyphinfo','const glyph_info')}
assert [(owner,name,t)for owner,name,kind,t,local in address_rows if kind=='ParmVarDecl']==[('pickup_object','count','long')]
assert 'count=C.local("long",count);'in j
# Every statically named C-environment lookup must be supplied by the actual
# compiler metadata or the unique typed adapter, including unexercised branches.
core_without_comments=re.sub(r'/\*[\s\S]*?\*/','',j)
helper_keys={'ptr','sizes','cell','field','global','staticAddress','local','copy','initialize','literal','variadic','indirect','ownedFunctionPointer','nativeFunctionPointer','dynamicVariadic','stackAlloc','stackSave','stackRestore','heap','i8','u8','i16','u16','i32','u32','i64','u64'}
provided=helper_keys|set(s['layoutKeys'])|{g['name']for g in s['globals']}|set(s['dependencies'])
lookups=set(re.findall(r'\bC\.([A-Za-z_]\w*)',core_without_comments));assert not lookups-provided,('missing typed environment keys',sorted(lookups-provided))
assert not re.search(r'\bC\s*\[',core_without_comments),'review dynamic environment key'
for name in s['dependencies']:assert name+':'in lib or name+' function'in lib or name+'__sig:'in lib,name
p=argparse.ArgumentParser();p.add_argument('--captured',action='store_true');a=p.parse_args();command=json.loads((w/'command.json').read_text());base=command['args'][:-1]
macros=(w/'macros.txt').read_bytes()if a.captured else subprocess.check_output(base+['-dM','-E','pickup.c'],cwd=command['cwd'])
assert macros==(w/'macros.txt').read_bytes(),'whole configured macros changed';text=macros.decode()
for name in m['activeCPP']:assert re.search(r'^#define '+name+r'\b',text,re.M),name
for name in m['inactiveCPP']:assert not re.search(r'^#define '+name+r'\b',text,re.M),name
for alias,canonical in m['aliases'].items():
 assert re.search(r'(?:->|\.)\s*'+alias+r'\b',c)
 assert re.search(r'^#define '+alias+r'\s+'+re.escape(canonical)+r'\s*$',text,re.M)
 assert ',"'+canonical.split('.')[-1]+'")'in j,canonical
if not a.captured:assert subprocess.check_output(base+['-E','pickup.c'],cwd=command['cwd'])==(w/'configured.c').read_bytes(),'whole CPP changed'
print('PASS PICKUP66 exact order/formals/types/478comments/10JS-private statics/source-enum5/13primary+5display RNG/6aliases/11gotos8sharedlabels/9owned8native identities/42typed callbacks/24byte menu/61unary lvalues/zeroABI; '+('captured'if a.captured else'fresh whole')+' CPP+input hashes. Behavioral equivalence separate.')
