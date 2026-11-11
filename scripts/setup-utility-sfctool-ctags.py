"""Private auxiliary tool recipe; not independently replayed in this handoff.

This does not install, accept licenses, change developer-directory settings,
or alter the NetHack Emscripten frontend.  Use --archive to avoid network.
"""
from pathlib import Path
import argparse,hashlib,io,json,os,subprocess,tarfile,urllib.request
p=argparse.ArgumentParser();p.add_argument('--out',type=Path,required=True);p.add_argument('--archive',type=Path);p.add_argument('--jobs',type=int,default=2);a=p.parse_args()
out=a.out.resolve()
if out.exists():p.error('--out must not exist')
if a.jobs<1 or a.jobs>4:p.error('--jobs must be1..4')
url='https://codeload.github.com/universal-ctags/ctags/tar.gz/refs/tags/v6.2.1'
expected='f56829e9a576025e98955597ee967099a871987b3476fbd8dbbc2b9dc921f824'
archive=a.archive.read_bytes()if a.archive else urllib.request.urlopen(url,timeout=60).read()
assert hashlib.sha256(archive).hexdigest()==expected,'official archive digest mismatch'
out.mkdir(parents=True)
with tarfile.open(fileobj=io.BytesIO(archive),mode='r:gz')as t:
 for m in t.getmembers():
  dest=(out/m.name).resolve();assert dest.is_relative_to(out),'archive path escape'
  if m.issym():assert(dest.parent/m.linkname).resolve().is_relative_to(out),'symlink escape'
  if m.islnk():assert(out/m.linkname).resolve().is_relative_to(out),'hardlink escape'
 t.extractall(out,filter='data')
source=out/'ctags-6.2.1'
tools={'CC':'/Library/Developer/CommandLineTools/usr/bin/clang','AR':'/Library/Developer/CommandLineTools/usr/bin/ar','RANLIB':'/Library/Developer/CommandLineTools/usr/bin/ranlib','MAKE':'/opt/homebrew/bin/gmake'}
for path in tools.values():assert Path(path).is_file(),path
sdk='/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk';assert Path(sdk).is_dir()
env={**os.environ,**tools,'SDKROOT':sdk,'PATH':'/opt/homebrew/bin:/Library/Developer/CommandLineTools/usr/bin:/usr/bin:/bin'}
rows=[]
for label,cmd in [('autogen',['./autogen.sh']),('configure',['./configure','--prefix='+str(out/'install'),'--disable-shared','--disable-json','--disable-yaml','--disable-xml','--disable-iconv']),('build',[tools['MAKE'],'-j'+str(a.jobs),'AR='+tools['AR'],'RANLIB='+tools['RANLIB']]),('version',[str(source/'ctags'),'--version'])]:
 with(out/(label+'.log')).open('w')as log:status=subprocess.run(cmd,cwd=source,env=env,stdout=log,stderr=subprocess.STDOUT)
 rows.append({'step':label,'argv':cmd,'actualExit':status.returncode});(out/'commands.json').write_text(json.dumps(rows,indent=2)+'\n')
 if status.returncode:raise SystemExit(status.returncode)
receipt={'url':url,'release':'https://github.com/universal-ctags/ctags/releases/tag/v6.2.1','archiveSha256':expected,'archiveSource':str(a.archive.resolve())if a.archive else'official URL','tools':tools,'SDKROOT':sdk,'binary':str(source/'ctags'),'binarySha256':hashlib.sha256((source/'ctags').read_bytes()).hexdigest(),'systemInstallationChanged':False,'licenseAcceptanceOrSettingsChanged':False,'qualification':'Auxiliary host tool only; NetHack frontend stays Emscripten4.0.10/Clang21 MEMORY64. --disable-shared is retained from the original root recipe and may emit an unrecognized-option warning. New output paths/debug paths need not reproduce the existing binary byte hash.'}
(out/'receipt.json').write_text(json.dumps(receipt,indent=2)+'\n');print(json.dumps(receipt))
