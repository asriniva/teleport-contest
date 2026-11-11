#!/usr/bin/env python3
"""Measure original GETPOS headers and bind unchanged native spell transport."""
import hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';header=root/'scripts/tu-getpos-layout.h';support=root/'nethack-c/wasm/tu-fragments/getpos-support.inc';source=tree/'src/getpos.c';library=root/'nethack-c/wasm/tu-libraries/getpos.js';clang=ref/'.cache/emsdk/upstream/bin/clang';layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['getpos']
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
with tempfile.TemporaryDirectory(prefix='standalone-getpos-')as scratch:
 p=Path(scratch)/'probe.c';body='#include '+json.dumps(str(header))+'\n';p.write_text(body);expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(p)],text=True);table=re.search(r'getpos_layout\[\]\s*=\s*\{(.*?)\n\};',expanded,re.S)[1];rows=re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}',table,re.S);assert rows
 body+='\n'.join('const unsigned long getpos_value_'+str(i)+'=('+expression+');'for i,(_,expression)in enumerate(rows));p.write_text(body);ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(p)],text=True);read=lambda n:int(re.search(r'@'+n+r' = .*?constant i64 (-?\d+)',ir)[1])&((1<<64)-1)
 measured={name:read('getpos_value_'+str(i))for i,(name,_)in enumerate(rows)}
 if 'size'in layout and 'size'not in measured:measured['size']=measured['coordStructSize']
 assert set(measured)==set(layout) and all(v==(int(layout[k])&((1<<64)-1))for k,v in measured.items()),repr({'missing':set(layout)-set(measured),'extra':set(measured)-set(layout),'different':[(k,v,layout.get(k))for k,v in measured.items()if v!=(int(layout.get(k,0))&((1<<64)-1))]})
 deps=subprocess.check_output([str(clang),*flags,'-M',str(p)],text=True);headers=[Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(ref)]
headerNames=['glyph_is_cmap','glyph_is_monster','glyph_is_object','glyph_is_nothing','glyph_is_unexplored','is_cmap_room','is_cmap_furniture','is_cmap_wall','is_cmap_corr','is_cmap_water','is_cmap_lava','is_cmap_door','is_cmap_drawbridge','is_cmap_trap','is_cmap_engraving']
with tempfile.TemporaryDirectory(prefix='getpos-header-')as scratch:
 p=Path(scratch)/'probe.c';p.write_text('#include "hack.h"\n'+'\n'.join('int header_'+str(i)+'(int glyph){return '+n+'(glyph);}'for i,n in enumerate(headerNames))+'\nint header_mon(int n,int gender){return monnum_to_glyph(n,gender); }\nint header_obj(int n){return objnum_to_glyph(n); }\n')
 ast=json.loads(subprocess.check_output([clang,*flags,'-fsyntax-only','-Xclang','-ast-dump=json',str(p)]));enums={}
 def walk(n):
  if n.get('kind')=='EnumDecl':
   last=-1
   for e in n.get('inner',[]):
    if e.get('kind')=='EnumConstantDecl':
     def constant(x):
      if x.get('kind')=='ConstantExpr'and'value'in x:return int(x['value'])
      for y in x.get('inner',[]):
       found=constant(y)
       if found is not None:return found
     v=constant(e);last=last+1 if v is None else v;enums[e['name']]=last
  for c in n.get('inner',[]):walk(c)
 walk(ast)
 def lower(n):
  k=n['kind'];cs=n.get('inner',[])
  if k in ['ParenExpr','ImplicitCastExpr','CStyleCastExpr','ConstantExpr']:
   expr=lower(cs[-1]);typ=n.get('type',{}).get('qualType')
   if k in ['ImplicitCastExpr','CStyleCastExpr']and n.get('castKind')=='IntegralCast':
    if typ=='int':return '('+expr+'|0)'
    if typ=='unsigned int':return '('+expr+'>>>0)'
   return expr
  if k=='IntegerLiteral':return str(int(n['value']))
  if k=='DeclRefExpr':
   name=n['referencedDecl']['name']
   if name in ['glyph','n','gender']:return name
   if name in enums:return str(enums[name])
   raise ValueError('Nonconstant header reference '+name)
  if k=='BinaryOperator':
   op=n['opcode'];a,b=map(lower,cs)
   if op=='/':return '(Math.trunc(('+a+')/('+b+'))|0)'
   if op not in ['+','-','*','%','<','<=','>','>=','==','!=','&&','||','&','|','^','<<','>>']:raise ValueError('Header operator '+op)
   expr=('Number(Boolean('+a+op+b+'))')if op in ['&&','||']else '('+a+op+b+')'
   if op in ['+','-','*','%']and n.get('type',{}).get('qualType')in ['int','unsigned int']:expr='('+expr+('>>>0)'if n['type']['qualType']=='unsigned int'else '|0)')
   return expr
  if k=='UnaryOperator':
   if n['opcode']not in ['!','~','-','+']:raise ValueError('Header unary')
   return '('+n['opcode']+lower(cs[0])+')'
  if k=='ConditionalOperator':return '('+lower(cs[0])+'?'+lower(cs[1])+':'+lower(cs[2])+')'
  raise ValueError('Review GETPOS header AST '+k)
 functions={n['name']:n for n in ast['inner']if n.get('kind')=='FunctionDecl'and n.get('name','').startswith('header_')}
 expressions=[]
 for i in [*map(str,range(len(headerNames))),'mon','obj']:
  f=functions['header_'+i];stmt=next(n for n in f['inner']if n['kind']=='CompoundStmt');expressions.append(lower(stmt['inner'][0]['inner'][0]))
 output=root/'js/standalone/getpos-header-functions.js';output.write_text('// Generated configured C display.h expressions; no targeting policies.\nexport const getposGlyphHeaders=[\n'+',\n'.join('glyph=>(Number('+e+')|0)'for e in expressions[:-2])+'\n];\nexport const getposMonGlyph=(n,gender)=>(Number('+expressions[-2]+')|0);\nexport const getposObjGlyph=n=>(Number('+expressions[-1]+')|0);\n')
native=support.read_text();lib=library.read_text();public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions']
globals={int(i):v for i,v in re.findall(r'case (\d+):return (.*?);',native.split('teleport_getpos_global',1)[1].split('int teleport_getpos_flag',1)[0])};assert len(globals)==13
commands=re.findall(r'case \d+:return (\w+);',native.split('teleport_getpos_command_token',1)[1].split('char teleport_getpos_cmd_from_func',1)[0]);assert len(commands)==10
calls={}
for name,target in re.findall(r'^      (\w+):[^\n]*?=>\s*(?:Number\()?_(\w+)\(',lib,re.M):
 if not target.startswith('teleport_getpos_'):calls[name]={'target':target,'prototype':public[target]}
callbacks={'cmp_coord_distu':'int (const void *, const void *)','gloc_filter_floodfill_matcharea':'int (coordxy, coordxy)'}
names=re.findall(r'^export function (\w+)',(root/'js/ported/getpos.js').read_text(),re.M)
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();inputs=[Path(__file__).resolve(),root/'js/standalone/getpos.js',root/'js/standalone/getpos-header-functions.js',header,support,library,root/'js/ported/getpos.js',root/'js/ported/getpos-runtime.js',root/'js/wasm/tu-layouts.json',root/'js/standalone/records.json',root/'js/standalone/public-functions.json',root/'nethack-c/wasm/compile-defines.json']
result={'layout':layout,'globals':globals,'commands':commands,'callbacks':callbacks,'calls':calls,'public':{n:public[n]for n in names if n in public},'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(set(headers+[source]))}}
(root/'js/standalone/getpos-abi.json').write_text(json.dumps(result,indent=2)+'\n');print('Bound original GETPOS header/native typed targeting ABI.')
