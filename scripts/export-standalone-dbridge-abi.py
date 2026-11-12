#!/usr/bin/env python3
"""Measure native DBRIDGE transport; original policies and existing owner retained."""
import hashlib,json,re,subprocess,tempfile,shlex
from pathlib import Path
root=Path(__file__).resolve().parents[1];tree=root/'.cache/wasm64-build/tree';clang=root/'.cache/emsdk/upstream/bin/clang';header=root/'scripts/tu-dbridge-layout.h';support=root/'nethack-c/wasm/tu-support.c';library=root/'nethack-c/wasm/tu-libraries/dbridge.js';source=root/'js/ported/dbridge.js'
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(root/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(root/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(root/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
with tempfile.TemporaryDirectory(prefix='standalone-dbridge-abi-')as tmp:
 p=Path(tmp)/'probe.c';p.write_text('#include '+json.dumps(str(header))+'\n');expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(p)],text=True);body=re.search(r'dbridge_layout\[\]\s*=\s*\{(.*?)\n\};',expanded,re.S)[1];rows=re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}',body,re.S)
 p.write_text(expanded+'\n'+'\n'.join('const long long probe_db_'+str(i)+'=('+expr+');'for i,(_,expr)in enumerate(rows)));ir=subprocess.check_output([str(clang),*flags[:2],'-x','cpp-output','-S','-emit-llvm','-O0','-o','-',str(p)],text=True);measured={n:int(re.search(r'@probe_db_'+str(i)+r' = .*?constant i64 (-?\d+)',ir)[1])for i,(n,_)in enumerate(rows)}
 layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['dbridge'];assert set(layout)-{'size'}==set(measured)and all((v&((1<<64)-1))==(int(str(layout[k]),0)&((1<<64)-1))for k,v in measured.items()),('Changed DBRIDGE layout',set(layout)-set(measured),set(measured)-set(layout),[(k,v,layout.get(k))for k,v in measured.items()if (v&((1<<64)-1))!=(int(str(layout.get(k,0)),0)&((1<<64)-1))])
 assert layout['size']==measured['entitySize'],'DBRIDGE native context size'
 p.write_text('#include "hack.h"\n'+''.join('unsigned db_terrain_'+k+'(struct rm *r){return r->'+k+';}\n'for k in ['drawbridgemask','doormask','wall_info','horizontal','icedpool']))
 expanded_alias=subprocess.check_output([str(clang),*flags,'-E','-P',str(p)],text=True);aliases={k:re.search(r'db_terrain_'+k+r'\(struct rm \*r\)\{return r->(\w+);\}',expanded_alias)[1]for k in ['drawbridgemask','doormask','wall_info','horizontal','icedpool']}
 p.write_text('#include '+json.dumps(str(header))+'\n')
 deps=subprocess.check_output([str(clang),*flags,'-M',str(p)],text=True);headers=[Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(root)]
# Bind the existing MKROOM owner leaves required by actual Castle generation.
room_header=root/'scripts/tu-mkroom-layout.h'
with tempfile.TemporaryDirectory(prefix='standalone-castle-room-abi-')as tmp:
 p=Path(tmp)/'room.c';p.write_text('#include '+json.dumps(str(room_header))+'\nint db_SPACE_POS(int t){return SPACE_POS(t);}\nint db_IS_THRONE(int t){return IS_THRONE(t);}')
 expanded_room=subprocess.check_output([str(clang),*flags,'-E','-P',str(p)],text=True)
 macro_expansions={n:re.search(r'int db_'+n+r'\(int t\)\{return (.*?);\}',expanded_room)[1]for n in ['SPACE_POS','IS_THRONE']}
 body=re.search(r'mkroom_layout\[\]\s*=\s*\{(.*?)\n\};',expanded_room,re.S)[1];rr=re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}',body,re.S)
 p.write_text(expanded_room+'\n'+'\n'.join('const long long probe_room_'+str(i)+'=('+expr+');'for i,(_,expr)in enumerate(rr)))
 ir=subprocess.check_output([str(clang),*flags[:2],'-x','cpp-output','-S','-emit-llvm','-O0','-o','-',str(p)],text=True)
 room_measured={n:int(re.search(r'@probe_room_'+str(i)+r' = .*?constant i64 (-?\d+)',ir)[1])for i,(n,_)in enumerate(rr)};room_layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['mkroom']
 assert set(room_layout)-{'size'}==set(room_measured)and all((v&((1<<64)-1))==(int(str(room_layout[k]),0)&((1<<64)-1))for k,v in room_measured.items()),'Changed MKROOM native layout'
 assert room_layout['size']==room_layout['roomSize']
 p.write_text('#include '+json.dumps(str(room_header))+'\n');deps=subprocess.check_output([str(clang),*flags,'-M',str(p)],text=True);headers.extend(Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(root))
native=support.read_text().split('const void *teleport_dbridge_global',1)[1].split('#define TELEPORT_DBRIDGE_LITERAL_CAPACITY',1)[0];globals=[n for _,n in re.findall(r'case (\d+): return &(\w+);',native.split('int teleport_dbridge_monster_bit',1)[0])];assert len(globals)==12
bits={}
for name,kind in [('monster','mon'),('terrain','levl\\[x\\]\\[y\\]')]:
 section=native.split('int teleport_dbridge_'+name+'_bit',1)[1].split('default:',1)[0];bits[name]=[n for _,n in re.findall(r'case (\d+): return '+kind+r'(?:->|\.)(\w+);',section)]
assert len(bits['monster'])==5 and len(bits['terrain'])==5
callers=re.findall(r'"([^"]+)"',native.split('teleport_dbridge_callers[] = {',1)[1].split('}',1)[0]);assert callers==['e_missed','e_jumps','destroy_drawbridge']
calls={}
for line in library.read_text().splitlines():
 m=re.match(r'\s*(\w+):([^=]+)=>(Number\()?_(\w+)\((.*)',line)
 if not m or m[4].startswith('teleport_'):continue
 name,params,number,target,args=m.groups();assert args.endswith(')),')if number else args.endswith('),');args=args[:-(3 if number else 2)];params=params.strip('()').split(',')if params.strip('()')else[];coercions=[]
 for a in args.split(',')if args else[]:
  a=a.strip();found=None
  for i,p in enumerate(params):
   for kind,pattern in [('pointer','pointer('+p+')'),('text','text('+p+')'),('char','byte('+p+')'),('short','coord('+p+')'),('int',p+'|0'),('uint','Number('+p+')>>>0'),('int',p)]:
    if a==pattern:found=[kind,i]
  assert found,(name,a,params);coercions.append(found)
 calls[name]={'target':target,'number':bool(number),'coercions':coercions}
public=json.loads((root/'js/standalone/public-functions.json').read_text())['functions'];names=re.findall(r'^export function (\w+)\(',source.read_text(),re.M);sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();paths=[Path(__file__).resolve(),header,support,library,source,root/'js/nethack/bindings/dbridge.js',root/'js/standalone/dbridge.js',root/'js/standalone/level-contents.js',root/'js/nethack/address-ports.js',root/'js/standalone/level-startup.js',root/'js/ported/mkmap.js',root/'js/nethack/bindings/mkmap.js',root/'nethack-c/wasm/tu-mkroom-support.inc',root/'nethack-c/wasm/tu-libraries/mkroom.js',root/'js/ported/mkroom.js',root/'js/nethack/bindings/mkroom.js',room_header,root/'js/standalone/records.json',root/'js/wasm/tu-layouts.json',root/'js/standalone/public-functions.json']
data={'layout':layout,'roomClosure':{'layout':room_layout,'macros':macro_expansions,'leaves':['fill_zoo','cmap_to_type','antholemon','courtmon','mkundead'],'mapLeaf':'remove_rooms on existing map-lighting; native copyRoom uses measured struct mkroom extent','sourceTable':'mkroom.squadprob mapped to measured PM constants'},'globals':globals,'bits':bits,'terrainAliases':aliases,'callers':callers,'calls':calls,'public':{n:public[n]for n in names if n in public},'sourceSha256':{str(p.relative_to(root)):sha(p)for p in paths},'referenceHeaderSha256':{str(p.relative_to(root)):sha(p)for p in sorted(set(headers+[tree/'src/dbridge.c',tree/'src/mkroom.c',tree/'src/mkmap.c']))}}
(root/'js/standalone/dbridge-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('DBRIDGE',len(layout),'nativevalues',len(calls),'nativecalls',len(data['public']),'publicfunctions')
