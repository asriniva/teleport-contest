#!/usr/bin/env python3
"""Bind original TELEPORT native transport, header expressions and storage paths."""
import hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';header=root/'scripts/tu-teleport-layout.h';support=root/'nethack-c/wasm/tu-fragments/teleport-support.c';runtime=root/'js/nethack/bindings/teleport.js';lib=root/'nethack-c/wasm/tu-libraries/teleport.js';decoder=json.JSONDecoder();meta=decoder.raw_decode(runtime.read_text().split('const meta=',1)[1])[0];layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['teleport'];native=support.read_text();clang=ref/'.cache/emsdk/upstream/bin/clang';public=json.loads((root/'js/nethack/public-functions.json').read_text())['functions']
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
body='#include '+json.dumps(str(header))+'\n#define PROOF_STR_(x) #x\n#define PROOF_STR(x) PROOF_STR_(x)\n'
bindings=[]
for k,(kind,(type,fields))in enumerate(meta['records'].items()):
 for i,field in enumerate(fields):bindings.append(('r_'+str(k)+'_'+str(i),'((('+type+'*)0)->'+field+')'))
for i,field in enumerate(meta['globalfields']):bindings.append(('g_'+str(i),field))
address_body=native.split('void*teleport_teleport_address',1)[1].split('long teleport_teleport_hero',1)[0];address_expr=[]
for i,expr in re.findall(r'case (\d+):return\(void\*\)(.*?);',address_body):
 address_expr.append({'address':expr.startswith('&'),'expression':expr.lstrip('&')});bindings.append(('a_'+i,expr.lstrip('&')))
assert len(address_expr)==len(meta['addresses'])
body+='\n'.join('const char*proof_'+name+'=PROOF_STR('+expr+');'for name,expr in bindings)+'\n'
body+='const char*proof_setVoice=PROOF_STR(SetVoice(p,a,b,c));\n'
body+='\n'.join('long proof_hero_'+name+'(void){return !!('+name+');}'for name in meta['hero'])+'\n'
# Stringify each exact native header helper body, retaining function arguments.
helper_bodies={}
for name in meta['dependencies']:
 if name not in public:
  m=re.search(r'^[^\n]+ teleport_teleport_dep_'+name+r'\((.*?)\)\{(?:return )?(.*?);\}',native,re.M)
  assert m,name;helper_bodies[name]={'parameters':m[1],'expression':m[2]}
  # Parameters need declarations for preprocessor only, not evaluation.
  body+='const char*proof_h_'+name+'=PROOF_STR('+m[2]+');\n'
with tempfile.TemporaryDirectory(prefix='standalone-teleport-abi-')as scratch:
 probe=Path(scratch)/'probe.c';probe.write_text(body)
 cpp=subprocess.check_output([str(clang),*flags,'-E','-P',str(probe)],text=True)
 strings={name:json.loads('"'+value+'"')for name,value in re.findall(r'const char\s*\*proof_(\w+)\s*=\s*"((?:\\.|[^"\\])*)";',cpp)}
 hero={name:re.search(r'long proof_hero_'+name+r'\(void\)\{return !!\((.*?)\);\}',cpp,re.S)[1]for name in meta['hero']}
 rows=re.findall(r'\{\s*"([^"]+)"\s*,\s*(.*?)\s*\}',re.search(r'teleport_teleport_layout\[\]\s*=\s*\{(.*?)\n\};',cpp,re.S)[1],re.S)
 # Include header-only enum constants used by configured expression macros.
 extras=sorted(set(re.findall(r'\b[A-Z][A-Z_0-9]+\b',' '.join(list(hero.values())+[strings['h_'+n]for n in helper_bodies]))) - set(layout))
 probe.write_text(body+'\n'.join('const long long proof_layout_'+str(i)+'=('+expr+');'for i,(_,expr)in enumerate(rows))+'\n'+'\n'.join('const long long proof_extra_'+name+'=('+name+');'for name in extras))
 ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(probe)],text=True)
 measured={name:int(re.search(r'@proof_layout_'+str(i)+r' = .*?constant i64 (-?\d+)',ir)[1])for i,(name,_)in enumerate(rows)}
 assert set(measured)==set(layout) and all((v&((1<<64)-1))==(int(layout[k])&((1<<64)-1))for k,v in measured.items()),'Review TELEPORT layout'
 constants={name:int(re.search(r'@proof_extra_'+name+r' = .*?constant i64 (-?\d+)',ir)[1])for name in extras}
 deps=subprocess.check_output([str(clang),*flags,'-M',str(probe)],text=True);headers=[Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(ref)]
record_paths=[]
for k,(kind,(type,fields))in enumerate(meta['records'].items()):
 record_paths.append({'type':type,'fields':[strings['r_'+str(k)+'_'+str(i)].split('->',1)[1].rstrip(')')for i in range(len(fields))]})
for i,row in enumerate(address_expr):row['path']=strings['a_'+str(i)]
for n,row in helper_bodies.items():row['expanded']=strings['h_'+n]
inputs=[Path(__file__).resolve(),header,support,runtime,lib,root/'js/ported/teleport.js',root/'nethack-c/wasm/tu-fragments/teleport-source-data.h',root/'nethack-c/wasm/tu-fragments/teleport-source-data.json',root/'js/nethack/records.json',root/'js/nethack/public-functions.json',root/'js/wasm/tu-layouts.json',root/'nethack-c/wasm/compile-defines.json'];sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();names=re.findall(r'^export function (\w+)',(root/'js/ported/teleport.js').read_text(),re.M)
data={'setVoiceExpansion':strings['setVoice'],'layout':layout,'constants':constants,'meta':meta,'recordPaths':record_paths,'globalPaths':[strings['g_'+str(i)]for i in range(len(meta['globalfields']))],'addresses':address_expr,'heroExpressions':hero,'headerHelpers':helper_bodies,'public':{n:public[n]for n in names if n in public},'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(set(headers+[tree/'src/teleport.c']))}}
(root/'js/nethack/teleport-abi.json').write_text(json.dumps(data,indent=2)+'\n');print('Bound TELEPORT '+str(len(data['public']))+' public entries/'+str(len(meta['dependencies']))+' typed dependencies/'+str(len(constants))+' extra header constants.')
