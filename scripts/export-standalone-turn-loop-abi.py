#!/usr/bin/env python3
"""Bind ALLMAIN transport and lower configured header expressions, never policy."""
import hashlib
import json
import os
import re
import shlex
import subprocess
from pathlib import Path

root=Path(__file__).resolve().parents[1]
reference=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve()
tree=reference/'.cache/wasm64-build/tree'
runtime=root/'js/nethack/bindings/allmain.js'
support=root/'nethack-c/wasm/tu-fragments/allmain-support.c'
text=runtime.read_text()
def declaration(name):
    return json.JSONDecoder().raw_decode(text.split('const '+name+'=',1)[1])[0]
fields=declaration('fields');addresses=declaration('addresses');heroes=declaration('heroNames')
roots=sorted(set(path.split('.')[0]for path in fields+addresses)|{'mons','genders','nhcb_counts','nhcb_name'})
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(reference/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(reference/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(reference/'.cache/ncurses-wasm64-build/include'),*['-D'+d for d in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
clang=str(reference/'.cache/emsdk/upstream/bin/clang')
probes=['#include "hack.h"']
probes += [f'int probe_turn_hero_{i}(void){{return !!({name});}}'for i,name in enumerate(heroes)]
probes += [f'const void *probe_turn_address_{i}(void){{return &({name});}}'for i,name in enumerate(addresses)]
probes += [f'const void *probe_turn_root_{i}(void){{return &({name});}}'for i,name in enumerate(roots)]
probes += ['int probe_turn_window(void){return VIA_WINDOWPORT();}','int probe_turn_ismnum(int n){return ismnum(n);}','void probe_turn_notice_on(void){notice_mon_on();}','void probe_turn_notice_off(void){notice_mon_off();}','const char *probe_turn_news(void){return NEWS;}']
scratch=root/'.cache/turn-loop-headers.c';scratch.write_text('\n'.join(probes)+'\n')
output=subprocess.check_output([clang,*flags,'-fsyntax-only','-Xclang','-ast-dump=json','-Xclang','-ast-dump-filter=probe_turn_',str(scratch)],text=True)
functions={};decoder=json.JSONDecoder();remaining=output.strip()
while remaining:
    node,end=decoder.raw_decode(remaining);remaining=remaining[end:].strip()
    assert node['kind']=='FunctionDecl'
    functions[node['name']]=node
root_types={};enum_names=set()
def scan(node):
    if node.get('kind')=='DeclRefExpr'and node.get('referencedDecl',{}).get('kind')=='EnumConstantDecl':enum_names.add(node['referencedDecl']['name'])
    if node.get('kind')=='DeclRefExpr'and node.get('referencedDecl',{}).get('kind')=='VarDecl':
        item=node['referencedDecl'];typ=item['type']['qualType']
        assert item['name']not in root_types or root_types[item['name']]==typ
        root_types[item['name']]=typ
    for child in node.get('inner',[]):scan(child)
for function in functions.values():scan(function)
scratch.write_text(scratch.read_text()+'\n'+''.join('const unsigned long probe_turn_enum_'+name+'='+name+';\n'for name in sorted(enum_names)))
ir=subprocess.check_output([clang,*flags,'-S','-emit-llvm','-O0','-o','-',str(scratch)],text=True)
enums={name:int(re.search(r'@probe_turn_enum_'+name+r' = .*?constant i64 (\d+)',ir)[1])for name in enum_names}
def cast(expr,typ):
    if 'long'in typ:return 'BigInt.'+('asUintN'if'unsigned'in typ else'asIntN')+'(64,BigInt('+expr+'))'
    if typ=='unsigned int':return '('+expr+'>>>0)'
    if typ=='int':return '('+expr+'|0)'
    if typ in ['signed char','char']:return '('+expr+'<<24>>24)'
    if typ=='unsigned char':return '('+expr+'&255)'
    if typ=='short':return '('+expr+'<<16>>16)'
    if typ=='unsigned short':return '('+expr+'&65535)'
    raise ValueError('Unknown configured header cast '+typ)
def lower(node):
    kind=node['kind'];children=node.get('inner',[]);typ=node.get('type',{}).get('qualType','')
    if kind in ['ParenExpr','ImplicitCastExpr','CStyleCastExpr','ConstantExpr']:
        expr=lower(children[-1])
        if node.get('castKind')=='IntegralCast':return cast(expr,typ)
        return expr
    if kind=='IntegerLiteral':return str(int(node['value']))+('n'if'long'in typ else'')
    if kind=='StringLiteral':return 'C.literal('+json.dumps(json.loads(node['value']))+')'
    if kind=='DeclRefExpr':
        item=node['referencedDecl'];name=item['name']
        if item['kind']in ['VarDecl','FunctionDecl']:return 'C.'+name
        if item['kind']=='ParmVarDecl'and name=='n':return 'n'
        if item['kind']=='EnumConstantDecl':return str(enums[name])
        raise ValueError('Unknown header reference '+name+' '+item['kind'])
    if kind=='MemberExpr':return '('+lower(children[0])+').'+node['name']
    if kind=='ArraySubscriptExpr':return '('+lower(children[0])+')['+lower(children[1])+']'
    if kind=='UnaryOperator':
        op=node['opcode'];expr=lower(children[0])
        if op=='&':return expr # Projected C records/arrays retain their address.
        if op=='!':return 'Number(!('+expr+'))'
        if op in ['++','--']:return '('+(expr+op if node.get('isPostfix')else op+expr)+')'
        if op in ['~','-','+']:
            value='('+op+expr+')'
            return cast(value,typ)if'long'in typ else value
        raise ValueError('Unknown header unary '+op)
    if kind=='BinaryOperator':
        op=node['opcode'];a,b=map(lower,children)
        if op in ['&&','||']:return 'Number(Boolean('+a+')'+op+'Boolean('+b+'))'
        if op not in ['+','-','*','/','%','&','|','^','<<','>>','==','!=','<','<=','>','>=','=']:raise ValueError('Unknown header binary '+op)
        return '('+a+op+b+')'
    if kind=='ConditionalOperator':return '('+lower(children[0])+'?'+lower(children[1])+':'+lower(children[2])+')'
    if kind=='CallExpr':return lower(children[0])+'('+','.join(map(lower,children[1:]))+')'
    raise ValueError('Unsupported configured header AST '+kind)
def statement(node):
    kind=node['kind'];children=node.get('inner',[])
    if kind=='CompoundStmt':return '{'+''.join(map(statement,children))+'}'
    if kind=='ReturnStmt':return 'return '+lower(children[0])+';'
    if kind=='DoStmt':return 'do '+statement(children[0])+'while('+lower(children[1])+');'
    if kind=='IfStmt':return 'if('+lower(children[0])+')'+statement(children[1])+('else '+statement(children[2])if len(children)>2 else'')
    if kind=='NullStmt':return ';'
    return lower(node)+';'
def body(name):return statement(next(item for item in functions[name]['inner']if item['kind']=='CompoundStmt'))
generated=['// BEGIN GENERATED ALLMAIN HEADERS','const heroHeaders=[']
generated += [' C=>'+body('probe_turn_hero_'+str(i))+(','if i+1<len(heroes)else'')for i in range(len(heroes))]
generated += ['];','const addressHeaders=[']
generated += [' C=>'+body('probe_turn_address_'+str(i))+(','if i+1<len(addresses)else'')for i in range(len(addresses))]
generated += ['];','const headerWindow=C=>'+body('probe_turn_window')+';','const headerIsmnum=(C,n)=>'+body('probe_turn_ismnum')+';','const headerNoticeOn=C=>'+body('probe_turn_notice_on')+';','const headerNoticeOff=C=>'+body('probe_turn_notice_off')+';','const headerNews=C=>'+body('probe_turn_news')+';','// END GENERATED ALLMAIN HEADERS']
js=root/'js/standalone/turn-loop.js';current=js.read_text();pattern=r'// BEGIN GENERATED ALLMAIN HEADERS.*?// END GENERATED ALLMAIN HEADERS'
assert len(re.findall(pattern,current,re.S))==1
js.write_text(re.sub(pattern,lambda _: '\n'.join(generated),current,flags=re.S))
def parameters(raw):
    if raw.strip()=='void':return []
    return [re.sub(r'\ba\d+$','',value.strip()).strip()for value in raw.split(',')]
dependencies={}
for ret,name,params in re.findall(r'^([\w\s*]+?)\s+teleport_allmain_dep_(\w+)\(([^)]*)\)\{',support.read_text(),re.M):
    ret=ret.strip();assert '\n'not in ret,(name,ret)
    dependencies[name]={'result':ret,'parameters':parameters(params)}
assert len(dependencies)>100
macros=subprocess.check_output([clang,*flags,'-dM','-E',str(scratch)],text=True)
window_callbacks=json.loads((root/'js/standalone/window-abi.json').read_text())['windows']['callbacks']
window_macros={}
for name,field in re.findall(r'^#define (\w+) \(\*windowprocs\.(\w+)\)$',macros,re.M):
    if name in dependencies:window_macros[name]={'field':field,'type':window_callbacks[field]}
assert 'get_nh_event'in window_macros and 'cliparound'in window_macros
assertion=re.search(r'nhassert_failed\("([^"\n]+)","([^"\n]+)",(\d+)\)',support.read_text());assert assertion
root_bytes={}
incomplete=[name for name,typ in root_types.items()if typ.endswith('[]')]
for owner,names in [('role',['genders']),('decl',['nhcb_counts','nhcb_name'])]:
    names=[name for name in names if name in incomplete]
    probe=root/('.cache/turn-loop-'+owner+'-roots.c');probe.write_text('#include '+json.dumps(str(tree/('src/'+owner+'.c')))+'\n'+''.join('const unsigned long probe_turn_size_'+name+'=sizeof('+name+');\n'for name in names))
    data_ir=subprocess.check_output([clang,*flags,'-S','-emit-llvm','-O0','-o','-',str(probe)],text=True)
    for name in names:root_bytes[name]=int(re.search(r'@probe_turn_size_'+name+r' = .*?constant i64 (\d+)',data_ir)[1])
assert set(root_bytes)==set(incomplete)
sha=lambda path:hashlib.sha256(path.read_bytes()).hexdigest()
deps=subprocess.check_output([clang,*flags,'-M',str(scratch)],text=True)
headers=sorted(set(Path(path).resolve()for path in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(path).resolve().is_relative_to(reference)))
headers.extend(tree/('src/'+name+'.c')for name in ['allmain','role','decl'])
inputs=[Path(__file__).resolve(),js,runtime,support,root/'js/ported/allmain.js',root/'nethack-c/wasm/tu-libraries/allmain.js',root/'nethack-c/wasm/compile-defines.json',root/'js/standalone/window-abi.json']
data={'fields':fields,'addresses':addresses,'heroes':heroes,'roots':root_types,'rootBytes':root_bytes,'windowMacros':window_macros,'dependencies':dependencies,'assertion':{'text':assertion[1],'file':assertion[2],'line':int(assertion[3])},'sourceSha256':{str(path.relative_to(root)):sha(path)for path in inputs},'referenceHeaderSha256':{str(path.relative_to(reference)):sha(path)for path in headers}}
(root/'js/standalone/turn-loop-abi.json').write_text(json.dumps(data,indent=2)+'\n')
print('Bound ALLMAIN turn transport:',len(heroes),'hero headers,',len(root_types),'shared roots,',len(dependencies),'typed dependencies.')
