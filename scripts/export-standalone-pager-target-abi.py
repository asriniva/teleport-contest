#!/usr/bin/env python3
"""Lower original PAGER native header/global expressions; no description policy."""
import hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';support=root/'nethack-c/wasm/tu-fragments/pager-support.c';native=support.read_text();clang=ref/'.cache/emsdk/upstream/bin/clang'
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
getbody=native.split('long teleport_pager_get',1)[1].split('void teleport_pager_set',1)[0];herobody=native.split('long teleport_pager_hero',1)[1].split('void*teleport_pager_array',1)[0];addressbody=native.split('void*teleport_pager_address',1)[1].split('long teleport_pager_hero',1)[0];setbody=native.split('void teleport_pager_set',1)[1].split('void*teleport_pager_address',1)[0]
getrows=re.findall(r'case (\d+):return\(long\)(.*?);',getbody);herorows=re.findall(r'case (\d+):return\(long\)(.*?);',herobody);addressrows=re.findall(r'case (\d+):return\(void\*\)(.*?);',addressbody);setrows=re.findall(r'case (\d+):(.*?);return;',setbody)
assert len(getrows)==37 and len(herorows)==15 and len(addressrows)==8 and len(setrows)==34
with tempfile.TemporaryDirectory(prefix='pager-target-')as scratch:
 p=Path(scratch)/'probe.c';parts=['#include "hack.h"','#include "dlb.h"'];parts += ['long ph_get_'+i+'(void){return(long)('+e+');}'for i,e in getrows];parts += ['long ph_hero_'+i+'(void){return(long)('+e+');}'for i,e in herorows];parts += ['void* ph_address_'+i+'(void){return(void*)('+e+');}'for i,e in addressrows];parts += ['void ph_set_'+i+'(long value){'+e+';}'for i,e in setrows]
 helpers=re.findall(r'^([^\n]+? teleport_pager_dep_\w+\([^\n]*\)\{[^\n]*\})$',native,re.M);assert len(helpers)==167
 parts += [v.replace('teleport_pager_dep_','ph_dep_') for v in helpers];p.write_text('\n'.join(parts));ast=json.loads(subprocess.check_output([str(clang),*flags,'-fsyntax-only','-Xclang','-ast-dump=json',str(p)]));deps=subprocess.check_output([str(clang),*flags,'-M',str(p)],text=True);headers=[Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(ref)]
enums={};roots={};functions=set()
def walk(n):
 if n.get('kind')=='EnumDecl':
  last=-1
  def value(x):
   if x.get('kind')=='ConstantExpr'and'value'in x:return int(x['value'])
   for y in x.get('inner',[]):
    v=value(y)
    if v is not None:return v
  for e in n.get('inner',[]):
   if e.get('kind')=='EnumConstantDecl':
    v=value(e);last=last+1 if v is None else v;enums[e['name']]=last
 for c in n.get('inner',[]):walk(c)
walk(ast)
def convert(t,e):
 t=t.replace('const ','').strip()
 if '*'in t:return e
 if t in ['long','long long','unsigned long','unsigned long long']:return 'BigInt.as'+('Uint'if t.startswith('unsigned')else'Int')+'N(64,B('+e+'))'
 if t in ['int','unsigned int']:return '(Number('+e+')'+('>>>0)'if t.startswith('unsigned')else'|0)')
 if t in ['short','unsigned short','char','signed char','unsigned char']:return 'Number(BigInt.as'+('Uint'if t.startswith('unsigned')else'Int')+'N('+('16'if'short'in t else'8')+',B('+e+')))'
 return e
def lower(n):
 k=n['kind'];cs=n.get('inner',[]);t=n.get('type',{}).get('qualType','')
 if k in ['ParenExpr','ImplicitCastExpr','CStyleCastExpr','ConstantExpr']:
  e=lower(cs[-1]);return convert(t,e)if n.get('castKind')in ['IntegralCast','PointerToIntegral','IntegralToPointer']else e
 if k in ['IntegerLiteral','CharacterLiteral']:return str(n['value'])+('n'if'long'in t else'')
 if k=='StringLiteral':return 'N.literal('+json.dumps(json.loads(n['value']))+')'
 if k=='DeclRefExpr':
  d=n['referencedDecl'];name=d['name']
  if d['kind']=='EnumConstantDecl':return str(enums[name])
  if d['kind']=='ParmVarDecl':
   if name=='value':return 'value'
   assert re.fullmatch(r'a\d+',name),name;return 'A['+name[1:]+']'
  if d['kind']=='FunctionDecl':functions.add(name);return 'N.'+name
  assert d['kind']=='VarDecl',d;roots[name]=d['type']['qualType'];return 'G.'+name
 if k=='MemberExpr':
  base=lower(cs[0])
  if n.get('isArrow'):
   pointer=cs[0]['type'].get('desugaredQualType',cs[0]['type']['qualType']);assert pointer.rstrip().endswith('*'),pointer
   base='N.deref('+json.dumps(pointer.rstrip()[:-1].strip())+','+base+')'
  return '('+base+').'+n['name']
 if k=='ArraySubscriptExpr':return 'N.index('+json.dumps(t)+','+lower(cs[0])+','+lower(cs[1])+')'
 if k=='UnaryOperator':
  op=n['opcode'];e=lower(cs[0])
  if op=='&':return '(('+e+').address??'+e+')'
  if op=='*':return e if '('in t else 'N.deref('+json.dumps(t)+','+e+')'
  assert op in ['!','~','-','+'],op;return '('+op+e+')'
 if k=='BinaryOperator':
  op=n['opcode'];a,b=map(lower,cs);assert op in ['+','-','*','/','%','<','<=','>','>=','==','!=','&&','||','&','|','^','<<','>>','='],op
  if op in ['&&','||']:return 'Number(Boolean('+a+')'+op+'Boolean('+b+'))'
  e='('+a+op+b+')';return convert(t,e)if op in ['+','-','*','/','%','&','|','^','<<','>>']else e
 if k=='ConditionalOperator':return '('+lower(cs[0])+'?'+lower(cs[1])+':'+lower(cs[2])+')'
 if k=='CallExpr':
  callee=cs[0]
  while callee['kind']in ['ParenExpr','ImplicitCastExpr','CStyleCastExpr']:callee=callee['inner'][-1]
  if callee['kind']=='DeclRefExpr'and callee['referencedDecl']['kind']=='FunctionDecl':return lower(callee)+'('+','.join(map(lower,cs[1:]))+')'
  return 'N.indirect('+json.dumps(cs[0]['type']['qualType'])+','+lower(cs[0])+','+','.join(map(lower,cs[1:]))+')'
 raise ValueError('Review PAGER native expression '+k)
rows={};helperParameters={}
for n in ast['inner']:
 if n.get('kind')!='FunctionDecl'or not n.get('name','').startswith('ph_'):continue
 _,kind,index=n['name'].split('_',2);body=next(c for c in n['inner']if c['kind']=='CompoundStmt')['inner'][0];expr=lower(body['inner'][0]if body['kind']=='ReturnStmt'else body);rows.setdefault(kind,{})[index if kind=='dep'else int(index)]=expr
 if kind=='dep':helperParameters[index]=[c['type'].get('desugaredQualType',c['type']['qualType'])for c in n['inner']if c['kind']=='ParmVarDecl']
out=root/'js/nethack/pager-target-header-functions.js';lines=['// Generated original native PAGER header/global transport, not description policy.','const B=v=>BigInt(v?.address??v??0);']
for kind,rs in rows.items():lines.append('export const pagerNative'+kind.title()+'={'+','.join((json.dumps(i)if kind=='dep'else str(i))+':(G,N,'+('A'if kind=='dep'else'value')+')=>'+expr for i,expr in sorted(rs.items()))+'};')
out.write_text('\n'.join(lines)+'\n');sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();inputs=[Path(__file__).resolve(),out,support,root/'js/nethack/pager-lookup.js',root/'js/ported/pager.js',root/'js/nethack/bindings/pager.js',root/'nethack-c/wasm/tu-libraries/pager.js',root/'js/nethack/records.json',root/'nethack-c/wasm/compile-defines.json']
(root/'js/nethack/pager-target-abi.json').write_text(json.dumps({'roots':roots,'helperParameters':helperParameters,'functions':sorted(functions),'getCount':len(getrows),'heroCount':len(herorows),'addressCount':len(addressrows),'setIndices':[int(i)for i,_ in setrows],'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(set(headers+[tree/'src/pager.c']))}},indent=2)+'\n');print('Bound original PAGER header getters/setters/address/hero transport.')
