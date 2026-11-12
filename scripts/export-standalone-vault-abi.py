#!/usr/bin/env python3
"""Measure source-native VAULT globals/header/bit transport, no policy changes."""
import hashlib,json,os,re,shlex,subprocess,tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[1];ref=Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve();tree=ref/'.cache/wasm64-build/tree';header=root/'scripts/tu-vault-layout.h';support=root/'nethack-c/wasm/tu-fragments/vault-support.inc';clang=ref/'.cache/emsdk/upstream/bin/clang';layout=json.loads((root/'js/wasm/tu-layouts.json').read_text())['vault']
flags=['--target=wasm64-unknown-emscripten','--sysroot='+str(ref/'.cache/emsdk/upstream/emscripten/cache/sysroot'),'-include',str(ref/'nethack-c/wasm/native-terminal.h'),'-I'+str(tree/'include'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+v for v in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]]
extra=['INVIS','M1_SEE_INVIS','COULD_SEE','PRONOUN_HALLU','PRONOUN_NO_IT']
with tempfile.TemporaryDirectory(prefix='standalone-vault-')as scratch:
 p=Path(scratch)/'probe.c';p.write_text('#include '+json.dumps(str(support))+'\n');native=subprocess.check_output([str(clang),*flags,'-E','-P',str(p)],text=True)
 terrain_body=native.split('teleport_vault_terrain_bit(',1)[1].split('void teleport_vault_set_terrain_bit',1)[0];terrain_bits=[field for _,field in re.findall(r'case (\d+):return [^;]*\.(\w+);',terrain_body)];assert len(terrain_bits)==5
 gb=native.split('teleport_vault_global(int i){switch(i){',1)[1].split('default:',1)[0];global_rows=[]
 for i,expression in re.findall(r'case (\d+):return (.*?);',gb):
  expression=re.sub(r'^&','',expression).strip();parts=expression.split('.',1);rootname=parts[0];path=parts[1]if len(parts)>1 else '';global_rows.append({'index':int(i),'name':rootname,'path':path})
 assert [r['index']for r in global_rows]==list(range(18))
 body='#include '+json.dumps(str(header))+'\n';p.write_text(body);expanded=subprocess.check_output([str(clang),*flags,'-E','-P',str(p)],text=True)
 rows=re.findall(r'\{\s*"([^"]+)"\s*,\s*\(size_t\)\((.*?)\)\s*\}',expanded,re.S);assert rows
 body+='\n'.join('const unsigned long vault_value_'+str(i)+'=('+e+');'for i,(_,e)in enumerate(rows))+'\n'
 body+='\n'.join('const unsigned long vault_global_'+str(r['index'])+'='+('__builtin_offsetof(__typeof__('+r['name']+'),'+r['path']+')'if r['path']else'0')+';'for r in global_rows)+'\n'
 body+='\n'.join('const unsigned long vault_extra_'+str(i)+'=('+n+');'for i,n in enumerate(extra))+'\n';p.write_text(body);ir=subprocess.check_output([str(clang),*flags,'-S','-emit-llvm','-O0','-o','-',str(p)],text=True)
 read=lambda name:int(re.search(r'@'+name+r' = .*?constant i64 (-?\d+)',ir)[1])&((1<<64)-1)
 measured={name:read('vault_value_'+str(i))for i,(name,_)in enumerate(rows)}
 assert set(measured)==set(layout) and all(v==(int(layout[k])&((1<<64)-1))for k,v in measured.items()),repr({'extraFrozen':set(layout)-set(measured),'extraMeasured':set(measured)-set(layout),'different':[(k,v,layout.get(k))for k,v in measured.items()if v!=(int(layout.get(k,0))&((1<<64)-1))]})
 for r in global_rows:r['offset']=read('vault_global_'+str(r['index']))
 extras={name:read('vault_extra_'+str(i))for i,name in enumerate(extra)}
 deps=subprocess.check_output([str(clang),*flags,'-M',str(p)],text=True);headers=[Path(v).resolve()for v in shlex.split(deps.split(':',1)[1].replace('\\\n',''))if Path(v).resolve().is_relative_to(ref)]
source=(root/'js/ported/vault.js').read_text();public=json.loads((root/'js/nethack/public-functions.json').read_text())['functions'];names=re.findall(r'^export function (\w+)',source,re.M)
# Exact original support maps are bound along with all configured header inputs.
original=support.read_text();assert 'case 0:return m->isgd;case 1:return m->mpeaceful;case 2:return m->mcansee;'in original
assert 'return i?e->witness:e->gddone;'in original and 'return i?u.uundetected:u.uswallow;'in original
assert 'case 0:return levl[x][y].flags;case 1:return levl[x][y].lit;case 2:return levl[x][y].waslit;case 3:return levl[x][y].wall_info;case 4:return levl[x][y].doormask;'in original
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();inputs=[Path(__file__).resolve(),root/'js/nethack/vault.js',header,support,root/'js/ported/vault.js',root/'js/nethack/bindings/vault.js',root/'nethack-c/wasm/tu-libraries/vault.js',root/'nethack-c/wasm/tu-fragments/vault-runtime-method.inc',root/'js/wasm/tu-layouts.json',root/'js/nethack/records.json',root/'js/nethack/public-functions.json',root/'nethack-c/wasm/compile-defines.json']
result={'layout':layout,'globals':global_rows,'extra':extras,'monsterBits':['isgd','mpeaceful','mcansee'],'egdBits':['gddone','witness'],'heroBits':['uswallow','uundetected'],'terrainBits':terrain_bits,'public':{n:public[n]for n in names if n in public},'sourceSha256':{str(p.relative_to(root)):sha(p)for p in inputs},'referenceHeaderSha256':{str(p.relative_to(ref)):sha(p)for p in sorted(set(headers+[tree/'src/vault.c']))}}
(root/'js/nethack/vault-abi.json').write_text(json.dumps(result,indent=2)+'\n');print('Bound original VAULT '+str(len(names))+' source functions/'+str(len(result['public']))+' public entries,18 globals and configured header/packed transport.')
