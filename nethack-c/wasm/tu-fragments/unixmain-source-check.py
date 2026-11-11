"""UNIXMAIN exact configured source/data/profile guard; no shared mutations."""
from pathlib import Path
import hashlib,json,re,subprocess
R=Path(__file__).resolve().parents[3];W=R/'.cache/unixmain-first-pass';tree=R/'.cache/wasm64-build/tree';src=(tree/'sys/unix/unixmain.c').read_text();pristine=(R/'nethack-c/upstream/sys/unix/unixmain.c').read_text();core=(R/'js/ported/unixmain.js').read_text();I=json.loads((R/'nethack-c/wasm/tu-fragments/unixmain-source-inventory.json').read_text());S=json.loads((R/'nethack-c/wasm/tu-fragments/unixmain-schema.json').read_text());support=(R/'nethack-c/wasm/tu-fragments/unixmain-support.c').read_text();runtime=(R/'js/ported/unixmain-runtime.js').read_text()
sha=lambda s:hashlib.sha256(s.encode()).hexdigest()
assert sha(src)==I['sourceSha256']=='c029938f38987424493931fb7719abdb43a6deb82289a393c2bd94fa74c41bfa'
assert sha(pristine)==I['pristineSha256']=='9c8a9a498acaffee6ce62d44a5e07977d2ec4852f29a77a1fbabdea0fd9f2165' and src!=pristine
assert len(I['functions'])==15 and sum(f['linkage']=='static'for f in I['functions'])==3
assert re.findall(r'^export function (\w+)\(([^)]*)\)',core,re.M)==[(f['name'],','.join(p['name']for p in f['parameters']))for f in I['functions']]
for text in [src,pristine]:
 for comment in re.findall(r'/\*[\s\S]*?\*/|//[^\n]*',text):assert core.count(comment)>=text.count(comment),comment
assert len(S['statics'])==3 and [s['name']for s in S['statics']]==['get_unix_pw.virtual_user','get_unix_pw.pw','get_login_name.buf']
assert S['statics'][0]['js']=='[C.literal("root"),0,C.u32(0),C.u32(0),0,C.literal("/home/player"),C.literal("/bin/sh")]'
assert S['statics'][1]['js']=='0' and S['statics'][2]['type']=='char[256]' and S['statics'][2]['js'] is None
for row in S['statics']:
 assert 'name:'+json.dumps(row['name']) in core
 if row['js'] is not None:assert row['js'] in core
assert len(I['members'])==92 and len(I['pointerOperations'])==9
assert sum(p['type']['qualType']=='char **'for p in I['pointerOperations'])==4
assert 'argc=C.local("main.argc@'in core and 'argv=C.local("main.argv@'in core
assert 'argc.address,argv.address,dir.address'in core and core.count('continue attempt_restore;')==2
assert 'C.callback(0,(C.field(C.windowprocs,"window_procs","win_init_nhwindows").value),argc.address,argv.value)'in core
assert 'UNIXMAIN unsafe pointer dereference'in runtime and 'UNIXMAIN inexact Number pointer'in runtime
assert 'new Proxy(Object.create(null)'in runtime and 'finally{state.services=previous;}'in runtime
assert '#ifdef TELEPORT_REFERENCE_TU'not in support and 'sys/unix/unixmain.c'not in support
assert not re.search(r'\bstatic\b[^;\n]*=',support),'source data must not be initialized in C support'
entry=(R/'nethack-c/wasm/tu-fragments/unixmain-entry.c').read_text()
assert re.search(r'int main\(int argc, char \*\*argv\) \{ return teleport_unixmain_main\(argc, argv\); \}',entry)
assert I['defines']==json.loads((R/'nethack-c/wasm/compile-defines.json').read_text())
base=[str(R/'.cache/emsdk/upstream/emscripten/emcc'),'-O2','-g','-I../include',*['-D'+x for x in I['defines']],'-sMEMORY64=1','-I'+str(R/'.cache/ncurses-wasm64-build/include'),'-include',str(R/'nethack-c/wasm/native-terminal.h')]
cpp=subprocess.check_output([*base,'-E','../sys/unix/unixmain.c'],cwd=tree/'src',text=True);active=False;selected=[]
for line in cpp.splitlines():
 m=re.match(r'^# \d+ "([^"]+)"',line)
 if m:active=m[1]=='../sys/unix/unixmain.c'
 elif active:selected.append(line)
assert sha('\n'.join(selected))==I['configuredSha256']=='e0f9655beb4f60600187f472ad1cdf47dda9d005cc8984faa19a0c7c6ec088d3'
macros=subprocess.check_output([*base,'-E','-dM','../sys/unix/unixmain.c'],cwd=tree/'src',text=True)
for name,fact in I['flags'].items():assert bool(re.search(r'^#define '+re.escape(name)+r'\b',macros,re.M))==fact['active'],name
assert re.search(r'^#define sa_handler\s+__sa_handler.sa_handler\b',macros,re.M)
assert re.search(r'^#define signal\s+teleport_native_signal\b',macros,re.M)
# Every actual input captured from compiler cwd, including previously omitted prepared source.
P=json.loads((W/'compiler-input-hashes.json').read_text())
assert '.cache/wasm64-build/tree/sys/unix/unixmain.c'in P['sha256']
for name,expected in P['sha256'].items():assert hashlib.sha256((R/name).read_bytes()).hexdigest()==expected,name
print('UNIXMAIN15 source/CPP,104 prepared+101 pristine comments,3 private initializers,92 members,9 pointer ops,entry ABI and signal alias guards passed')
