"""Fresh-output reproduction recipe; path-parameterized adapter not replayed here."""
from pathlib import Path
import argparse,hashlib,json,re,subprocess
p=argparse.ArgumentParser();p.add_argument('--out',required=True,type=Path);p.add_argument('--source-root',required=True,type=Path);p.add_argument('--ctags',required=True,type=Path);p.add_argument('--sftags-reference',required=True,type=Path);a=p.parse_args()
w=a.out.resolve();r=a.source_root.resolve();tool=a.ctags.resolve();reference=a.sftags_reference.resolve()
if w.exists():p.error('--out must not exist')
for f in[tool,reference,reference.with_suffix('.wasm')]:assert f.is_file(),str(f)
version=subprocess.run([str(tool),'--version'],capture_output=True,text=True,check=True).stdout;assert 'Universal Ctags 6.2.1'in version
w.mkdir(parents=True);make=(r/'nethack-c/upstream/sys/windows/GNUmakefile').read_text();start=make.index('$(U)sf.tags:');block=make[start:make.index('\n$(OSFC):',start)];commands=[];inputs={}
for line in block.splitlines():
 if not line.startswith('\t$(CTAGSCMD)'):continue
 file=line.split()[-1].replace('$(INCL)/','nethack-c/upstream/include/').replace('$(SRC)/','nethack-c/upstream/src/');inputs[file]=hashlib.sha256((r/file).read_bytes()).hexdigest()
 cmd=[str(tool),'--language-force=c','--sort=no','-DBitfield(x,n)=unsigned x : n','--excmd=pattern']+(['-a']if commands else[])+['-f',str(w/'sf.tags'),file]
 status=subprocess.run(cmd,cwd=r,capture_output=True,text=True);commands.append({'argv':cmd,'exit':status.returncode,'stdout':status.stdout,'stderr':status.stderr});(w/'ctags-commands.json').write_text(json.dumps(commands,indent=2)+'\n')
 if status.returncode:raise SystemExit(status.returncode)
node=r/'.cache/emsdk/node/24.19.0_64bit/bin/node';adapter=Path(__file__).with_name('generate-utility-sfctool-metadata.mjs');cmd=[str(node),str(adapter),str(w),str(reference)]
with(w/'original-sftags.log').open('w')as log:status=subprocess.run(cmd,stdout=log,stderr=subprocess.STDOUT)
receipt={'ctags':str(tool),'ctagsSha256':hashlib.sha256(tool.read_bytes()).hexdigest(),'ctagsVersion':version,'originalSftagsModule':str(reference),'originalSftagsModuleSha256':hashlib.sha256(reference.read_bytes()).hexdigest(),'originalSftagsWasmSha256':hashlib.sha256(reference.with_suffix('.wasm').read_bytes()).hexdigest(),'sourceInputs':inputs,'sfTagsSha256':hashlib.sha256((w/'sf.tags').read_bytes()).hexdigest(),'generatorCommand':cmd,'generatorExit':status.returncode,'paddingOrInputFix':False}
(w/'receipt.json').write_text(json.dumps(receipt,indent=2)+'\n');raise SystemExit(status.returncode)
