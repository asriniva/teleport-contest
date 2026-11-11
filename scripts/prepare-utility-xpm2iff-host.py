from pathlib import Path
import re,json,hashlib
import argparse,shutil
parser=argparse.ArgumentParser(description='Prepare this one XPM2IFF HOST utility in a fresh output directory.')
parser.add_argument('--out',required=True,type=Path)
parser.add_argument('--source-root',type=Path,default=Path(__file__).resolve().parent.parent)
args=parser.parse_args();code_root=Path(__file__).resolve().parent.parent;source_root=args.source_root.resolve();out_arg=args.out.expanduser().absolute();b=out_arg.resolve();abi=code_root/'nethack-c/wasm/utilities/xpm2iff-host'
if out_arg.exists() or out_arg.is_symlink() or b.exists():parser.error('--out must not already exist')
source=source_root/'nethack-c/upstream/sys/amiga/xpm2iff_host.c';grave=source_root/'nethack-c/upstream/sys/amiga/grave16.xpm'
expected=json.loads((abi/'source-mapping.json').read_text());s=source.read_text()
if hashlib.sha256(s.encode()).hexdigest()!=expected['sourceSha256']:parser.error('actual C source differs from the ported source mapping')
if not grave.is_file():parser.error('actual grave16.xpm source fixture is missing')
b.mkdir(parents=True,exist_ok=False)
for name in ['source','generated','artifacts','logs']:(b/name).mkdir()
shutil.copyfile(source,b/'source/xpm2iff_host.c');shutil.copyfile(grave,b/'source/grave16.xpm')
initial=[source_root/'AGENTS.md',source,grave,source_root/'nethack-c/upstream/sys/amiga/README.amiga',source_root/'nethack-c/upstream/outdated/sys/amiga/Makefile.agc',source_root/'nethack-c/upstream/outdated/sys/amiga/Makefile.ami',source_root/'.cache/emsdk/upstream/emscripten/emcc',source_root/'.cache/emsdk/upstream/bin/clang']
(b/'before-hashes.json').write_text(json.dumps({str(p):hashlib.sha256(p.read_bytes()).hexdigest()for p in initial},indent=2)+'\n')
(b/'build-context.json').write_text(json.dumps({'codeRoot':str(code_root),'sourceRoot':str(source_root),'out':str(b),'sourceSha256':expected['sourceSha256']},indent=2)+'\n')
patterns=[('xpmgetline',r'static char \*\nxpmgetline\(void\)'),('fopen_xpm_file',r'static int\nfopen_xpm_file\(const char \*fn\)'),('conv_image',r'static void\nconv_image\(int nplanes\)'),('wr32',r'static void\nwr32\(uint32_t v\)'),('write_chunk',r'static void\nwrite_chunk\(const char \*id, const void \*data, uint32_t size\)'),('main',r'int\nmain\(int argc, char \*\*argv\)')]
entries=[];mixed=s
for name,pattern in patterns:
 m=re.search(pattern,s);assert m,name
 start=s.index('{',m.end());depth=1;i=start+1;quote=None
 while depth:
  c=s[i]
  if quote:
   if c=='\\':i+=2;continue
   if c==quote:quote=None
  elif s.startswith('/*',i):i=s.index('*/',i+2)+2;continue
  elif c in '\"\'':quote=c
  elif c=='{':depth+=1
  elif c=='}':depth-=1
  i+=1
 signature=m.group();decl='extern '+signature.removeprefix('static ')+';'
 old=s[m.start():i];mixed=mixed.replace(old,decl)
 entries.append({'name':name,'signature':signature,'startLine':s.count('\n',0,m.start())+1,'endLine':s.count('\n',0,i)+1,'sourceSliceSha256':hashlib.sha256(old.encode()).hexdigest()})
(b/'generated/mixed.c').write_text(mixed)
strings=[];i=0
while i<len(s):
 if s.startswith('/*',i):i=s.index('*/',i+2)+2;continue
 if s[i] in '\"\'':
  quote=s[i];a=i;i+=1
  while i<len(s):
   if s[i]=='\\':i+=2;continue
   if s[i]==quote:break
   i+=1
  text=s[a:i+1];i+=1
  if quote=='\"':
   value=json.loads(text)
   if value not in [v for _,v in strings]:strings.append((text,value))
 else:i+=1
(b/'literals.json').write_text(json.dumps([v for _,v in strings],indent=2)+'\n')
(b/'generated/literal-data.h').write_text('static const char *utility_literals[]={\n'+',\n'.join(t for t,_ in strings)+'\n};\n')
(b/'inventory.json').write_text(json.dumps({'sourceSha256':hashlib.sha256(s.encode()).hexdigest(),'functionCount':len(entries),'functions':entries,'comments':len(re.findall(r'/\*.*?\*/',s,re.S)),'sourceLiteralCount':len(strings),'mixedNativeOriginalFunctionBodies':0,'profile':'private portable POSIX libc utility; EmCC4.0.10 Clang21 wasm64, O2-g MEMORY64, no game defines'},indent=2)+'\n')
print('prepared',len(entries),'functions',len(strings),'literals')

assert (b/'literals.json').read_bytes()==(abi/'literals.json').read_bytes(),'source-derived literal metadata drift'
assert (b/'generated/literal-data.h').read_bytes()==(abi/'literal-data.h').read_bytes(),'source-derived C literal table drift'
assert json.loads((b/'inventory.json').read_text())==expected,'actual source mapping drift'
