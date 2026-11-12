#!/usr/bin/env python3
"""Measure GLYPHS transport and lower only pure configured header expressions."""
import json,hashlib,os,re,shlex,subprocess
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';runtime=root/'js/nethack/bindings/glyphs.js';text=runtime.read_text()
def declaration(n):return json.JSONDecoder().raw_decode(text.split('const '+n+'=',1)[1])[0]
fields=declaration('fields');pointers=declaration('pointers');headers=declaration('headers');globals=declaration('globals')
types=['struct teleport_glyphs_find','struct teleport_glyphs_cache','struct customization_detail','glyph_map','struct unicode_representation','struct symset_customization','struct symsetentry','struct objclass','struct symparse','struct enum_dump','struct objdescr','struct permonst']
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+d for d in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]];clang=str(ref/'.cache/emsdk/upstream/bin/clang');header=root/'scripts/tu-glyphs-layout.h'
lines=['#include '+json.dumps(str(header))]
for i,((kind,fs),t)in enumerate(zip(fields.items(),types,strict=True)):
 lines.append(f'const unsigned long probe_{i}_size=sizeof({t});')
 for j,f in enumerate(fs):
  prefix=f'probe_{i}_{j}';pointer=kind+'.'+f in pointers
  lines.extend([f'const unsigned long {prefix}_offset=offsetof({t},{f});',f'const unsigned long {prefix}_size=sizeof((({t}*)0)->{f});',f'const unsigned long {prefix}_signed='+('0;'if pointer else f'((__typeof__((({t}*)0)->{f}))-1)<0;')])
lines.extend(f'int header_{i}(int glyph){{return {n}(glyph);}}'for i,n in enumerate(headers))
scratch=root/'.cache/glyph-abi.c';scratch.write_text('\n'.join(lines)+'\n');ir=subprocess.check_output([clang,*flags,'-S','-emit-llvm','-O0','-o','-',str(scratch)],text=True)
def value(k):return int(re.search(r'@probe_'+k+r' = .*?constant i64 (\d+)',ir)[1])
rows=[]
for i,((kind,fs),t)in enumerate(zip(fields.items(),types,strict=True)):
 rows.append({'kind':kind,'ctype':t,'size':value(str(i)+'_size'),'fields':[{'name':f,'offset':value(f'{i}_{j}_offset'),'size':value(f'{i}_{j}_size'),'signed':bool(value(f'{i}_{j}_signed')),'pointer':kind+'.'+f in pointers}for j,f in enumerate(fs)]})
ast=json.loads(subprocess.check_output([clang,*flags,'-fsyntax-only','-Xclang','-ast-dump=json',str(scratch)]));enums={}
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
  if name=='glyph':return 'glyph'
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
 raise ValueError('Review GLYPHS header AST '+k)
functions={n['name']:n for n in ast['inner']if n.get('kind')=='FunctionDecl'and n.get('name','').startswith('header_')}
expressions=[]
for i in range(len(headers)):
 f=functions['header_'+str(i)];body=next(n for n in f['inner']if n['kind']=='CompoundStmt');ret=body['inner'][0];assert ret['kind']=='ReturnStmt';expressions.append(lower(ret['inner'][0]))
output=root/'js/nethack/glyph-header-functions.js';output.write_text('// Generated from configured C display.h macros; no GLYPHS policy.\nexport const glyphHeaders=[\n'+',\n'.join(' glyph=>(Number('+e+')|0)'for e in expressions)+'\n];\n')
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();deps=subprocess.check_output([clang,*flags,'-M',str(scratch)],text=True);deps=[Path(p).resolve()for p in shlex.split(deps.split(':',1)[1].replace('\\\n',''))];deps.append(ref/'.cache/emsdk/upstream/emscripten/system/lib/libc/emscripten_syscall_stubs.c')
inputs=[Path(__file__).resolve(),runtime,root/'js/ported/glyphs.js',root/'nethack-c/wasm/tu-fragments/glyphs-support.c',header,root/'nethack-c/wasm/compile-defines.json',output]
data={'fields':rows,'globals':globals,'headers':headers,'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in deps if p.is_relative_to(ref)}}
(root/'js/nethack/glyph-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound GLYPHS fields and'+str(len(headers))+' pure header functions.')
