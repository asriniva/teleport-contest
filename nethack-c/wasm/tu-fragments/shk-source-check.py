"""SHK exact configured source/data/profile guard; no shared writes."""
from pathlib import Path
import hashlib,json,re,subprocess,os
R=Path(__file__).resolve().parents[3];SDK=Path(os.environ.get('EMSDK',str(R/'.cache/emsdk')));W=R/'.cache/shk-first-pass';tree=R/'.cache/wasm64-build/tree';src=(tree/'src/shk.c').read_text();core=(R/'js/ported/shk.js').read_text();I=json.loads((R/'nethack-c/wasm/tu-fragments/shk-source-inventory.json').read_text());S=json.loads((R/'nethack-c/wasm/tu-fragments/shk-schema.json').read_text());A=json.loads((R/'nethack-c/wasm/tu-fragments/shk-source-ast.json').read_text());support=(R/'nethack-c/wasm/tu-fragments/shk-support.c').read_text();runtime=(R/'js/nethack/bindings/shk.js').read_text()
assert src==(R/'nethack-c/upstream/src/shk.c').read_text()
assert hashlib.sha256(src.encode()).hexdigest()==I['sourceSha256']=='b2b5b82934b15c1a4a3c9474a650ff5800a83f0b9634696fdf080d0458f16e1b'
assert len(I['functions'])==len(A['functions'])==137 and sum(f['linkage']=='static'for f in I['functions'])==64
assert re.findall(r'^export function (\w+)\(([^)]*)\)',core,re.M)==[(f['name'],','.join(p['name']for p in f['parameters']))for f in I['functions']]
for comment in re.findall(r'/\*[\s\S]*?\*/|//[^\n]*',src):assert core.count(comment)>=src.count(comment),comment
assert S['statics']==I['statics'] and len(S['statics'])==12
assert len(A['members'])==I['MemberExprCount']==2649 and len(I['pointerOperations'])==21
assert [x['type']['qualType']for x in I['pointerOperations']].count('struct bill_x *')==9
for row in S['statics']:assert 'name:'+json.dumps(row['name'])in core and row['js']in core if row['js']is not None else True
assert core.count('sellobj.qbuf@')==4
for owner in ['add_one_tobill','stolen_container']:assert 'shkp=C.local("'+owner+'.shkp@'in core
assert 'shkp.address'in core and 'return bits<=9007199254740991n?Number(bits):bits;'in runtime
assert 'SHK unsafe pointer dereference'in runtime and 'SHK inexact Number pointer'in runtime
assert '#ifdef TELEPORT_SHK_VALIDATE_ORIGINAL'in support and '#ifdef TELEPORT_REFERENCE_TU'not in support
assert 'shk.c'not in support and not re.search(r'\bstatic\b[^;\n]*=',support)
base=[str(SDK/'upstream/emscripten/emcc'),'-O2','-g','-sMEMORY64=1','-I'+str(tree/'include'),'-I'+str(R/'.cache/ncurses-wasm64-build/include'),'-include',str(R/'nethack-c/wasm/native-terminal.h'),*['-D'+x for x in I['defines']]]
assert I['defines']==json.loads((R/'nethack-c/wasm/compile-defines.json').read_text())
cpp=subprocess.check_output([*base,'-E','shk.c'],cwd=tree/'src',text=True);active=False;selected=[]
for line in cpp.splitlines():
 m=re.match(r'^# \d+ "([^"]+)"',line)
 if m:active=m[1]=='shk.c'
 elif active:selected.append(line)
assert hashlib.sha256('\n'.join(selected).encode()).hexdigest()==I['configuredSha256']=='1aa0218ec7fdb2563ad556e81ac01d25056a4b859e6a68e0c20226dc12c9b8e2'
macros=subprocess.check_output([*base,'-E','-dM','shk.c'],cwd=tree/'src',text=True)
for alias,canonical in [('nexthere','v.v_nexthere'),('ocontainer','v.v_ocontainer'),('ocarry','v.v_ocarry'),('leashmon','corpsenm')]:assert re.search(r'^#define '+alias+r'\s+'+re.escape(canonical)+r'\b',macros,re.M),(alias,canonical)
for name in ['UNIX','SYSV','DEBUG','MACOS','__EMSCRIPTEN__']:assert re.search(r'^#define '+name+r'\b',macros,re.M)
for name in ['TTY_PERM_INVENT','DUMPLOG','OBSOLETE_HANDLING','DLB','__SASC']:assert not re.search(r'^#define '+name+r'\b',macros,re.M)
print('SHK137 source/CPP/complete comments/data/2649 fields/21 pointer ops/DeclID/LP64 guards passed')
