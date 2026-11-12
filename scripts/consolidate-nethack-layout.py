#!/usr/bin/env python3
"""Reproduce the NetHack directory consolidation without changing policy bodies."""
import argparse,hashlib,json,posixpath,re,subprocess
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
BASE='e61e34c926bed5a098cf3142ba50fa6cf56d2b46'
from functools import lru_cache
RECEIPT='docs/runtime-environment/nethack-layout.json'
EXT={'.js','.mjs','.py','.sh','.html'}
sha=lambda b:hashlib.sha256(b).hexdigest()

@lru_cache(maxsize=None)
def inventory():
 return subprocess.check_output(['git','ls-tree','-r','--name-only',BASE],cwd=ROOT,text=True).splitlines()
_objects=None
@lru_cache(maxsize=None)
def original(file):
 global _objects
 if _objects is None:_objects=subprocess.Popen(['git','cat-file','--batch'],cwd=ROOT,stdin=subprocess.PIPE,stdout=subprocess.PIPE)
 _objects.stdin.write((BASE+':'+file+'\n').encode());_objects.stdin.flush()
 header=_objects.stdout.readline().split();assert len(header)==3 and header[1]==b'blob',('Missing baseline blob',file)
 data=_objects.stdout.read(int(header[2]));assert _objects.stdout.read(1)==b'\n';return data
def current(file):
 return 'js/nethack/'+file[len('js/standalone/'):]if file.startswith('js/standalone/')else file

def historical_cli(file):
 if not file.startswith('scripts/'):return False
 name=Path(file).name
 if name=='test-pure-js-source-qualification.mjs':return True
 return bool(re.match(r'(?:check-(?:standalone|c-runtime|services|sdk)|write-c-runtime-manifest|relocate-runtime-layout|extract-|prune-c-runtime|.*source_successors|test-(?:.*source-successors|.*layered-audits|current-audit-guards|post-default-successors|services-layout-successors|c-runtime-mkobj-address-qualification))',name))

def prepend(text,prefix):
 if text.startswith('#!'):
  line,rest=text.split('\n',1);return line+'\n'+prefix+rest
 return prefix+text

def render(file,data,known):
 dest=current(file)
 if file=='package.json':
  value=json.loads(data);value['scripts']['test:layout']='node scripts/test-nethack-layout.mjs';return(json.dumps(value,indent=2)+'\n').encode()
 if Path(file).suffix not in EXT:return data
 text=data.decode()
 def relative(match):
  spec=match[2]
  target=posixpath.normpath(posixpath.join(posixpath.dirname(file),spec))
  if target not in known:return match[0]
  target=current(target)
  result=posixpath.relpath(target,posixpath.dirname(dest))
  if not result.startswith('.'):result='./'+result
  return match[1]+result+match[1]
 text=re.sub(r'''(['"])(\.[^'"\n]+)\1''',relative,text)
 # Current consumers use the new owner. Historical metadata and evidence stay exact.
 text=text.replace('js/standalone/','js/nethack/').replace('js/standalone\'',"js/nethack'").replace('js/standalone"','js/nethack"')
 if file=='scripts/services-layout-audit.mjs':
  text="""// Current paths plus a checked inverse for immutable historical source receipts.
import fs from 'node:fs';
import path from 'node:path';
import {historicalCall,currentLayoutPath} from './nethack-layout.mjs';
export function currentSourcePath(file){const p=path.relative(process.cwd(),path.resolve(file)),d=JSON.parse(fs.readFileSync('docs/runtime-environment/services-layout.json'));return currentLayoutPath(d.moves[p]??p);}
export function readBeforeLayout(file,encoding){return historicalCall('scripts/services-layout-audit.mjs','readBeforeLayout',[file,encoding]);}
export function existsBeforeLayout(file){return historicalCall('scripts/services-layout-audit.mjs','existsBeforeLayout',[file]);}
export function writeBeforeLayout(file,bytes){return historicalCall('scripts/services-layout-audit.mjs','writeBeforeLayout',[file,bytes]);}
"""
 if file=='scripts/c-runtime-compiled-input.mjs':
  text=text.replace('dependencies.set(p,digest(fs.readFileSync(p)))','dependencies.set(currentSourcePath(p),digest(fs.readFileSync(currentSourcePath(p))))')
 # Source receipts keep their immutable hashes even when current module imports move.
 if file.startswith('scripts/')and file.endswith('.mjs')and not historical_cli(file):
  names=set(re.findall(r'\b(sha|digest|hash)\s*=\s*[^;\n]{0,240}fs\.readFileSync',text))
  names.update(re.findall(r'function\s+(sha|digest|hash)\s*\([^)]*\)\s*\{[^;\n]{0,240}fs\.readFileSync',text))
  pattern=r'((?:assert\.(?:equal|strictEqual)|eq)\(\s*)(sha|digest|hash)\(([^()\n]+)\)(\s*,\s*)([A-Za-z_$][\w$]*(?:\.[\w$]+|\[[^()\n]+\])*)(?=\s*[,\)])'
  original_text=text
  text=re.sub(pattern,lambda m:m[1]+'layoutSourceSha('+m[3]+','+m[5]+')'+m[4]+m[5]if m[2]in names else m[0],text)
  count=text!=original_text
  if count:
   helper=posixpath.relpath('scripts/nethack-layout.mjs',posixpath.dirname(dest))
   if not helper.startswith('.'):helper='./'+helper
   text=prepend(text,"import {layoutSourceSha} from '"+helper+"';\n")
 if historical_cli(file)and file.endswith('.mjs'):
  helper=posixpath.relpath('scripts/nethack-layout.mjs',posixpath.dirname(dest))
  if not helper.startswith('.'):helper='./'+helper
  text=prepend(text,"import {runHistoricalCli as runPriorLayoutAudit} from '"+helper+"';\nif(runPriorLayoutAudit(import.meta.url))process.exit(0);\n")
 if historical_cli(file)and file.endswith('.py'):
  # Only CLI execution is projected; ordinary imports remain current tooling.
  prefix="import sys as _layout_sys\nfrom pathlib import Path as _LayoutPath\n_layout_sys.path.insert(0,str(_LayoutPath(__file__).resolve().parent))\nfrom nethack_layout import historical_cli as _prior_layout_cli\nif __name__=='__main__':_prior_layout_cli(__file__)\n"
  # No repository Python source here has a future import; keep shebang first.
  if text.startswith('#!'):
   line,text=text.split('\n',1);text=line+'\n'+prefix+text
  else:text=prefix+text
 return text.encode()

def plan():
 known=set(inventory());rows={}
 for file in sorted(known):
  if file.startswith(('docs/','frozen/','nethack-c/upstream/'))or Path(file).suffix not in EXT and not file.startswith('js/standalone/')and file!='package.json':continue
  before=original(file)
  # The sole collision is an exact one-line forwarder to the implementation kept in nethack.
  if file=='js/standalone/address-ports.js':
   assert before==b"// Compatibility entry for NetHack's declared module bindings.\nexport {enableAddressPort} from '../nethack/address-ports.js';\n"
   rows[file]={'destination':None,'beforeSha256':sha(before),'reason':'Remove forwarding wrapper; existing implementation is js/nethack/address-ports.js.'};continue
  after=render(file,before,known);dest=current(file)
  if dest!=file or after!=before:rows[file]={'destination':dest,'beforeSha256':sha(before),'afterSha256':sha(after),'bytes':after}
 return rows

def qualified_current(file):
 if file in {'js/c-runtime/types.js','js/c-runtime/address-bindings.js'}and(ROOT/'scripts/type_metadata_source_successor.py').exists():
  from type_metadata_source_successor import qualified_before
  return qualified_before(ROOT,file)
 # A separate finite native/source successor precedes the immutable relocation.
 if (ROOT/'docs/runtime-environment/transport-allocation-source-successors.json').exists():
  from transport_allocation_source_successors import ALLOWED,qualified_before
  if file in ALLOWED:return qualified_before(ROOT,file)
 return (ROOT/file).read_bytes()

def main():
 p=argparse.ArgumentParser();p.add_argument('--write',action='store_true');a=p.parse_args();
 assert not any(historical_cli(f)for f in ['scripts/test-native-existing.mjs','scripts/test-tu-light.mjs','scripts/run-standalone-program.mjs','scripts/test-standalone-allocation-cli.mjs']),'Runtime tests cannot use the historical audit view'
 rows=plan()
 if a.write:
  assert not(ROOT/'docs/runtime-environment/transport-allocation-source-successors.json').exists(),'Refusing to overwrite independently qualified transport features; historical layout generation is read-only'
  previous=json.loads((ROOT/RECEIPT).read_bytes())['files']if(ROOT/RECEIPT).exists()else{}
  for old,row in previous.items():
   if old not in rows and row['destination']==old:
    assert sha((ROOT/old).read_bytes())in {row['afterSha256'],sha(original(old))},'Refusing to replace unreviewed work: '+old
    (ROOT/old).write_bytes(original(old))
  for old,row in rows.items():
   if row['destination']is not None:
    dest=ROOT/row['destination'];dest.parent.mkdir(parents=True,exist_ok=True);dest.write_bytes(row['bytes'])
   if row['destination']!=old and(ROOT/old).exists():(ROOT/old).unlink()
  if(ROOT/'js/standalone').exists():(ROOT/'js/standalone').rmdir()
  record={'baseCommit':subprocess.check_output(['git','rev-parse',BASE],cwd=ROOT,text=True).strip(),'scope':'Exact path/import relocation; original metadata hashes retained. Historical audits execute the pinned preceding layout after this layout is verified. Current runtime tests import the consolidated modules.','files':{f:{k:v for k,v in row.items()if k!='bytes'}for f,row in rows.items()}}
  (ROOT/RECEIPT).write_text(json.dumps(record,indent=2)+'\n')
 else:
  record=json.loads((ROOT/RECEIPT).read_bytes());assert record['baseCommit']==subprocess.check_output(['git','rev-parse',BASE],cwd=ROOT,text=True).strip()
  assert record['files']=={f:{k:v for k,v in row.items()if k!='bytes'}for f,row in rows.items()},'Consolidation recipe/receipt differs'
  for old,row in rows.items():
   if row['destination']is not None:assert qualified_current(row['destination'])==row['bytes'],'Changed beyond path relocation: '+row['destination']
  assert not(ROOT/'js/standalone').exists(),'Old production directory remains'
  # Historical evidence, frozen harnesses and C/compiler inputs must not drift.
  for file in inventory():
   if file in rows:continue
   if file.startswith(('js/','scripts/','frozen/','docs/runtime-environment/','nethack-c/'))and Path(file).suffix in {'.js','.mjs','.json','.patch','.c','.h','.inc','.py','.sh'}:
    assert qualified_current(current(file))==original(file),'Unrelated source/evidence change: '+file
  expected={current(f)for f in inventory()if f.startswith('js/')and Path(f).suffix in {'.js','.json'}and f!='js/standalone/address-ports.js'}
  actual={str(p.relative_to(ROOT))for p in(ROOT/'js').rglob('*')if p.is_file()and p.suffix in {'.js','.json'}}
  assert actual==expected,('Unexpected runtime source membership',sorted(actual-expected),sorted(expected-actual))
 print('PASS NetHack layout:230 former standalone files consolidated; one forwarding wrapper removed;',len(rows),'exact path/source transitions.')
if __name__=='__main__':main()
