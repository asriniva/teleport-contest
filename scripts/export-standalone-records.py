#!/usr/bin/env python3
"""Export measured record/bitfield metadata; development compiler only."""
import argparse
import hashlib
import json
from pathlib import Path
import re
import shlex
import subprocess

parser=argparse.ArgumentParser()
parser.add_argument('--reference-root',type=Path,required=True)
parser.add_argument('--output',type=Path,required=True)
args=parser.parse_args()
root=Path(__file__).resolve().parents[1]
reference=args.reference_root.resolve()
scratch=root/'.cache/standalone-records'
scratch.mkdir(parents=True,exist_ok=True)
source=scratch/'probe.c'
source.write_text('''#include "hack.h"
#include "timeout.h"
#include "region.h"
#include "lobject.h"
#include "lstate.h"
#include <stddef.h>
const size_t standalone_lua_memory[] = {sizeof(Table),sizeof(Node),sizeof(TValue),offsetof(TString,contents),sizeof(Proto),offsetof(LClosure,upvals),offsetof(CClosure,upvalue),sizeof(UpVal),sizeof(lua_State),sizeof(global_State),sizeof(CallInfo),udatamemoffset(0),udatamemoffset(1)-sizeof(UValue)};
const size_t standalone_lua_debug[] = {sizeof(lua_Debug),offsetof(lua_Debug,event),offsetof(lua_Debug,name),offsetof(lua_Debug,namewhat),offsetof(lua_Debug,what),offsetof(lua_Debug,source),offsetof(lua_Debug,srclen),offsetof(lua_Debug,currentline),offsetof(lua_Debug,linedefined),offsetof(lua_Debug,lastlinedefined),offsetof(lua_Debug,nups),offsetof(lua_Debug,nparams),offsetof(lua_Debug,isvararg),offsetof(lua_Debug,istailcall),offsetof(lua_Debug,ftransfer),offsetof(lua_Debug,ntransfer),offsetof(lua_Debug,short_src),offsetof(lua_Debug,i_ci),LUA_IDSIZE};
const size_t standalone_lua_userdata[] = {udatamemoffset(0),udatamemoffset(1)-sizeof(UValue),sizeof(UValue)};
''')
address_metadata=root/'js/standalone/address-ports.json'
address_ports=json.loads(address_metadata.read_text())['ports']
enum_names=sorted({f['canonical'] for p in address_ports.values() for r in p['schema']['schema'].values() for f in r['fields'] if f['canonical'].startswith('enum ')})
source.write_text(source.read_text()+'\nconst size_t standalone_enum_sizes[] = {'+','.join('sizeof('+t+')' for t in enum_names)+'};\nconst size_t standalone_enum_signed[] = {'+','.join('(('+t+')-1)<0' for t in enum_names)+'};\n')
compiler=reference/'.cache/emsdk/upstream/bin/clang'
defines=root/'nethack-c/wasm/compile-defines.json'
flags=['--target=wasm64-unknown-emscripten',
       '--sysroot='+str(reference/'.cache/emsdk/upstream/emscripten/cache/sysroot'),
       *['-D'+d for d in json.loads(defines.read_text())],
       '-I'+str(reference/'.cache/wasm64-build/tree/include'),
       '-I'+str(reference/'.cache/ncurses-wasm64-build/include'),
       '-I'+str(reference/'.cache/wasm64-build/tree/lib/lua-5.4.8/src')]
result=subprocess.run([str(compiler),*flags,'-fsyntax-only','-Xclang','-fdump-record-layouts-complete',str(source)],capture_output=True,text=True,check=True)
layout_text=result.stdout
support_sources={}
support_names=['mklev','mkmaze','pickup','shk','invent','dothrow','display','termcap','dungeon','mkobj','muse','pray','detect','sp_lev']
for name in support_names:
    support=root/f'nethack-c/wasm/tu-fragments/{name}-support.c'
    extra=subprocess.run([str(compiler),*flags,'-I'+str(reference/'.cache/tu-probes'),'-fsyntax-only','-Xclang','-fdump-record-layouts-complete',str(support)],capture_output=True,text=True)
    if extra.returncode:
        raise RuntimeError(str(support)+': '+extra.stderr)
    layout_text+=extra.stdout
    support_sources[str(support.relative_to(root))]=hashlib.sha256(support.read_bytes()).hexdigest()
(scratch/'layouts.txt').write_text(layout_text)
records={}
anonymous=[]
for block in layout_text.split('*** Dumping AST Record Layout')[1:]:
    lines=block.strip().splitlines()
    head=re.match(r'\s*0 \| (struct|union) ([\w]+)$',lines[0])
    anon=re.match(r'\s*0 \| (struct|union) \(unnamed at (.*):(\d+):(\d+)\)$',lines[0])
    end=re.search(r'\[sizeof=(\d+), align=(\d+)\]',block)
    if (not head and not anon) or not end:
        continue
    fields={}
    for line in lines[1:]:
        field=re.match(r'\s*(\d+)(?::(\d+)-(\d+))? \|   (\S.*)$',line)
        if not field:
            continue
        name=re.search(r'\b([A-Za-z_]\w*)$',field[4])
        if not name:
            continue
        value={'offset':int(field[1]),'ctype':field[4]}
        if field[2] is not None:
            value.update(shift=int(field[2]),bits=int(field[3])-int(field[2])+1)
        fields[name[1]]=value
    definition={'size':int(end[1]),'alignment':int(end[2]),'fields':fields}
    if head:
        if head[2] in records and records[head[2]]!=definition:
            raise ValueError('Conflicting compiler record layouts '+head[2])
        records[head[2]]=definition
    else:
        item=(int(anon[3]),int(anon[4]),definition)
        if item not in anonymous:
            anonymous.append(item)
        location='@'+Path(anon[2]).name+':'+anon[3]+':'+anon[4]
        if location in records and records[location]!=definition:
            raise ValueError('Ambiguous anonymous record location '+location)
        records[location]=definition
for record in records.values():
    for field in record['fields'].values():
        nested=re.match(r'^(?:struct|union) (?:\w+::)?\(unnamed at (.*):(\d+):(\d+)\) \w+$',field['ctype'])
        if nested:
            key='@'+Path(nested[1]).name+':'+nested[2]+':'+nested[3]
            if key in records:
                field['record']=key
# Resolve anonymous typedefs by Clang's declaration identity, source position,
# and complete direct field-name list. Ambiguous matches fail closed.
ast_result=subprocess.run([str(compiler),*flags,'-fsyntax-only','-Xclang','-ast-dump=json',str(source)],capture_output=True,text=True,check=True)
nodes={}
typedefs=[]
def visit(node):
    if node.get('kind')=='RecordDecl' and node.get('completeDefinition'):
        nodes[node['id']]=node
    if node.get('kind')=='TypedefDecl':
        typedefs.append(node)
    for child in node.get('inner',[]):
        visit(child)
visit(json.loads(ast_result.stdout))
aliases={t['name']:t['type']['qualType'] for t in typedefs}
for typedef in typedefs:
    owned=next((n.get('ownedTagDecl') for n in typedef.get('inner',[]) if n.get('ownedTagDecl')),None)
    if not owned or owned.get('name') or owned['id'] not in nodes:
        continue
    record=nodes[owned['id']]
    loc=record['loc']
    names=[n['name'] for n in record.get('inner',[]) if n.get('kind')=='FieldDecl' and n.get('name')]
    matches=[d for line,col,d in anonymous if line==loc.get('line') and col==loc.get('col') and list(d['fields'])==names]
    if len(matches)>1:
        raise ValueError('Ambiguous anonymous typedef '+typedef['name'])
    if matches:
        records[typedef['name']]=matches[0]
# Support files can introduce anonymous private typedef records as well.
for support_name in support_names:
    support_ast=subprocess.run([str(compiler),*flags,'-I'+str(reference/'.cache/tu-probes'),'-fsyntax-only','-Xclang','-ast-dump=json',str(root/f'nethack-c/wasm/tu-fragments/{support_name}-support.c')],capture_output=True,text=True,check=True)
    nodes={}
    typedefs=[]
    visit(json.loads(support_ast.stdout))
    for typedef in typedefs:
        aliases[typedef['name']]=typedef['type']['qualType']
        owned=next((n.get('ownedTagDecl') for n in typedef.get('inner',[]) if n.get('ownedTagDecl')),None)
        if not owned or owned.get('name') or owned['id'] not in nodes:
            continue
        record=nodes[owned['id']]
        loc=record['loc']
        names=[n['name'] for n in record.get('inner',[]) if n.get('kind')=='FieldDecl' and n.get('name')]
        matches=[d for line,col,d in anonymous if line==loc.get('line') and col==loc.get('col') and list(d['fields'])==names]
        if len(matches)>1:
            raise ValueError('Ambiguous support typedef '+typedef['name'])
        if matches:
            records[typedef['name']]=matches[0]
# The DECL projection retains names for anonymous typedef records which the
# textual Clang dump prints only as source locations. Bind that projection and
# keep its measured fields; the original-C DECL byte/image suite checks it.
decl_schema=root/'nethack-c/wasm/tu-fragments/decl-schema.json'
for name,record in json.loads(decl_schema.read_text())['schema'].items():
    if name in records:
        if records[name]['size']!=record['size']:
            raise ValueError('DECL/Clang record size mismatch '+name)
        for field in record['fields']:
            existing=records[name]['fields'].get(field['name'])
            if existing and field['d'].get('s'):
                if existing['offset']!=field['offset']:
                    raise ValueError('DECL/Clang nested field mismatch '+name+'.'+field['name'])
                existing['record']=field['d']['s']
        continue
    fields={}
    for field in record['fields']:
        if not field['name']:
            continue
        value={'offset':field['offset'],'ctype':field['ctype']}
        if field['d'].get('s'):
            value['record']=field['d']['s']
        if field['bits'] is not None:
            value.update(shift=field['bitOffset'],bits=field['bits'])
        fields[field['name']]=value
    records[name]={'size':record['size'],'alignment':record['alignment'],'fields':fields}
ir=subprocess.run([str(compiler),*flags,'-S','-emit-llvm',str(source),'-o','-'],capture_output=True,text=True,check=True).stdout
lua={}
for key in ['memory','debug','userdata']:
    match=re.search(r'@standalone_lua_'+key+r' = .*?\[\d+ x i64\] \[([^\]]+)\]',ir)
    if not match:
        raise RuntimeError('Missing measured Lua '+key)
    lua[key]=[int(v) for v in re.findall(r'i64 (\d+)',match[1])]
enum_values={}
for key in ['sizes','signed']:
    match=re.search(r'@standalone_enum_'+key+r' = .*?\[\d+ x i64\] \[([^\]]+)\]',ir)
    if not match:
        raise RuntimeError('Missing measured enum '+key)
    enum_values[key]=[int(v) for v in re.findall(r'i64 (\d+)',match[1])]
enums={name:{'size':enum_values['sizes'][i],'signed':bool(enum_values['signed'][i])} for i,name in enumerate(enum_names)}
for record in records.values():
    for field in record['fields'].values():
        nested=re.match(r'^(?:struct|union) (?:\w+::)?\(unnamed at (.*):(\d+):(\d+)\) \w+$',field['ctype'])
        if nested:
            key='@'+Path(nested[1]).name+':'+nested[2]+':'+nested[3]
            if key in records:
                field['record']=key
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
inputs={}
local_inputs={}
for input_source in [source,*[root/f'nethack-c/wasm/tu-fragments/{name}-support.c' for name in support_names]]:
    deps=subprocess.run([str(compiler),*flags,'-I'+str(reference/'.cache/tu-probes'),'-M',str(input_source)],capture_output=True,text=True,check=True)
    paths=shlex.split(deps.stdout.split(':',1)[1].replace('\\\n',''))
    for value in paths:
        p=Path(value).resolve()
        if p==input_source:
            continue
        if p.is_relative_to(root):
            local_inputs[str(p.relative_to(root))]=sha(p)
        else:
            inputs[str(p.relative_to(reference)) if p.is_relative_to(reference) else str(p)]=sha(p)
document={'profile':'wasm64-unknown-emscripten, configured NetHack headers',
          'compilerSha256':sha(compiler),'definesSha256':sha(defines),'declSchemaSha256':sha(decl_schema),'supportSourceSha256':support_sources,
          'probeSource':source.read_text(),'headerSha256':inputs,'localHeaderSha256':local_inputs,'records':records,'aliases':aliases,'lua':lua,'enums':enums,'addressMetadataSha256':sha(address_metadata),
          'limitation':'Named records and directly named fields only; anonymous embedded paths need adapter schemas. Offsets and bitfields are measured, not inferred from libc or Darwin.'}
locations=reference/'.cache/tu-probes/tu-source-locations.h'
location_text=locations.read_text()
document['rngSites']={'rect':{'file':re.search(r'^#define TELEPORT_RECT_RNG_FILE "([^"]+)"',location_text,re.M)[1],
                            'line':int(re.search(r'^#define TELEPORT_RECT_RNG_LINE (\d+)',location_text,re.M)[1]),
                            'function':re.search(r'^#define TELEPORT_RECT_RNG_FUNCTION "([^"]+)"',location_text,re.M)[1]}}
document['headerSha256'][str(locations.relative_to(reference))]=sha(locations)
args.output.write_text(json.dumps(document,indent=2)+'\n')
print(f'Exported {len(records)} named records and {len(inputs)} bound headers to {args.output}')
