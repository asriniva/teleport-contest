#!/usr/bin/env python3
"""Bind the source-addressed NHLUA configuration callback to its native C type."""
import hashlib,json,os,re,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ.get('STANDALONE_REFERENCE_ROOT',root));tree=ref/'.cache/wasm64-build/tree';clang=ref/'.cache/emsdk/upstream/bin/clang';support=root/'nethack-c/wasm/tu-fragments/nhlua-support.c';library=root/'nethack-c/wasm/tu-libraries/nhlua.js';public=json.loads((root/'js/nethack/public-functions.json').read_text());name='parse_config_line';assert public['functions'][name]=='boolean (char *)'
index=int(re.search(r'case (\d+):return \(uintptr_t\)&'+name+r';',support.read_text())[1]);names=json.loads(re.search(r'functionPointer:name=>\{var i=(\[[^\n]+?\])\.indexOf',library.read_text())[1]);assert names[index]==name
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
with tempfile.TemporaryDirectory(prefix='nhlua-callback-')as tmp:
 p=Path(tmp)/'probe.c';p.write_text('#include "hack.h"\nboolean (*probe_callback)(char *)=&parse_config_line;\nconst unsigned long probe_bool=sizeof(boolean),probe_ptr=sizeof(char *);\n');ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(p)],text=True);sizes={n:int(re.search('@probe_'+n+r' = .*?constant i64 (\d+)',ir)[1])for n in ['bool','ptr']};assert sizes=={'bool':1,'ptr':8}
# Same-owner NHLOBJ packed fields are native helper maps, never Lua policy.
object_support=root/'nethack-c/wasm/tu-nhlobj-support.inc';object_runtime=root/'js/nethack/bindings/nhlobj.js';object_native=object_support.read_text();object_js=object_runtime.read_text()
def native_bits(function):
 body=object_native.split(function+'(',1)[1].split('default:',1)[0]
 pairs=[(int(i),name)for i,name in re.findall(r'case (\d+):return o->(\w+);',body)]
 assert [i for i,_ in pairs]==list(range(len(pairs)))
 return[name for _,name in pairs]
object_bits=native_bits('teleport_nhlobj_object_bit');class_bits=native_bits('teleport_nhlobj_class_bit')
assert object_bits==json.loads(re.search(r'objbits=(\[[^\n]+?\]),clsbits=',object_js)[1])
assert class_bits==json.loads(re.search(r'clsbits=(\[[^\n]+?\]);',object_js)[1])
setter=object_native.split('teleport_nhlobj_set_object_bit(',1)[1].split('default:',1)[0]
assert[(int(i),name)for i,name in re.findall(r'case (\d+):o->(\w+)=v;break;',setter)]==list(enumerate(object_bits))
assert '#define odiluted oeroded' in (tree/'include/obj.h').read_text()
assert '#define opoisoned otrapped' in (tree/'include/obj.h').read_text()
record_data=json.loads((root/'js/nethack/records.json').read_text())['records'];aliases={'opoisoned':'otrapped','odiluted':'oeroded'}
for field_name in object_bits:assert record_data['obj']['fields'][aliases.get(field_name,field_name)]['bits']>0
for field_name in class_bits:assert record_data['objclass']['fields'][field_name]['bits']>0
paths=[Path(__file__).resolve(),root/'js/nethack/lua-sandbox.js',support,library,root/'js/nethack/public-functions.json',root/'nethack-c/wasm/compile-defines.json',object_support,object_runtime,root/'js/nethack/records.json'];sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();data={'callbacks':{name:{'prototype':public['functions'][name],'return':'i8','args':[{'pointer':'char'}],'signature':'ip','nativeIndex':index}},'sizes':sizes,'nhlobj':{'objectBits':object_bits,'classBits':class_bits,'aliases':aliases},'sourceSha256':{str(p.relative_to(root)):sha(p)for p in paths},'referenceHeaderSha256':public['referenceHeaderSha256'],'scope':'Exact original source-addressed callback transport; no Lua/configuration policy changes. Tutorial execution is a separate C comparison.'};(root/'js/nethack/lua-callbacks-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound native NHLUA parse_config_line callback',index,sizes)
