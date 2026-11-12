"""Preserve existing tests/cases while switching their fixture factory imports."""
from pathlib import Path
import re,json,sys
ROOT=Path(__file__).resolve().parents[2]
def adapt(name,source):
 if name=='cfgfiles':source=source.replace("name==='cnf_line_WARNINGS'?'1 2 3 4 5 6':value","name==='cnf_line_WARNINGS'?'1 2 3 4 5 6':name==='cnf_line_OPTIONS'?'OPTIONS='+value:value")
 source=re.sub(r'WebAssembly\.Module\.imports\(new WebAssembly\.Module\(await readFile\(resolve\(dir,[^\n]*?\)\)\)\)', '(await fixtureImports('+json.dumps(name)+'))',source)
 source=source.replace('WebAssembly.Module.imports(new WebAssembly.Module(wasm))','(await fixtureImports('+json.dumps(name)+'))')

 source=re.sub(r"^import './pure-js-probes/deny-wasm.mjs';\n",'',source,flags=re.M)
 source=re.sub(r"import\s+(\w+)\s+from\s*'([^']*(?:hybrid|reference)[^']*\.mjs)';",lambda m: ('const '+m[1]+'=options=>'+('createProbe' if 'hybrid' in m[2] else 'createReference')+'('+json.dumps(name)+(',' if 'hybrid' in m[2] else ',new URL(')+ ('options);' if 'hybrid' in m[2] else json.dumps(m[2])+',import.meta.url),options);')) if '.cache/' in m[2] else m[0],source)
 # Change import expressions, retaining the complete original URL calculation.
 positions=[]
 for match in re.finditer(r'\bimport\s*\(',source):
  at=match.end();level=1;quote=None;i=at
  while level and i<len(source):
   c=source[i]
   if quote:
    if c=='\\':i+=2;continue
    if c==quote:quote=None
   elif c in "'\"`":quote=c
   elif c=='(':level+=1
   elif c==')':level-=1
   i+=1
  positions.append((match.start(),at))
 for a,b in reversed(positions):source=source[:a]+'loadFixture('+json.dumps(name)+','+source[b:]
 # These old availability guards are superseded by the isolated C reference.
 source=re.sub(r"^.*if\s*\(process\.env\.TELEPORT_NATIVE_TESTS\s*!==?\s*['\"]0['\"]\)\s*throw (?:new )?Error\([^\n]*\);\s*$",'// Original C reference is available through the isolated reference process.',source,flags=re.M)
 types=sorted(set(re.findall(r'\bnew\s+(DataView|(?:Big)?(?:U?Int|Uint|Float)\d+Array)\s*\(',source)))
 for t in types:source=re.sub(r'\bnew\s+'+t+r'\s*\(', 'new Fixture'+t+'(',source)
 header="import './pure-js-probes/deny-wasm.mjs';\nimport {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';\n"
 if types:header+="import {"+','.join(t+' as Fixture'+t for t in types)+"} from './native-test-backend.mjs';\n"
 return header+source
if __name__=='__main__':
 ports=json.loads((ROOT/'nethack-c/wasm/tu-ports.json').read_text())
 names=sys.argv[1:]or[p['name']for p in ports]
 output=ROOT/'.cache/pure-js-fixtures/adapted';output.mkdir(exist_ok=True)
 for name in names:
  original=ROOT/f'scripts/test-tu-{name}.mjs'
  source=original.read_text()
  if "from './pure-js-probes/" in source or "from './pure-js-fixtures/runtime.mjs'" in source:continue
  source=adapt(name,source)
  # Projected copies retain original URL/path resolution for validation.
  source=source.replace('import.meta.url',json.dumps(original.as_uri()))
  source=re.sub(r"(from\s*|import\s+)(['\"])(\.[^'\"]+)\2",lambda m:m[1]+json.dumps((original.parent/m[3]).resolve().as_uri()),source)
  (output/f'{name}.mjs').write_text(source)
  print(name)
