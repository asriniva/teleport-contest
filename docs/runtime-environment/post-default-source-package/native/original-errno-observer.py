from pathlib import Path
import re,json,hashlib
p=Path('/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/full-original-c-v1/out/game.wasm');b=p.read_bytes();sym=p.with_name('game.mjs.symbols').read_text();m=re.search(r'^(\d+):__errno_location$',sym,re.M);print('symbol',m[1]if m else None)
def u(at):
 v=0;n=0
 while True:
  c=b[at];at+=1;v|=(c&127)<<n;n+=7
  if c<128:return v,at
at=8;sections={}
while at<len(b):
 ident=b[at];n,q=u(at+1);sections[ident]=(q,q+n);at=q+n
at,end=sections[2];count,at=u(at);imports=0
for i in range(count):
 for j in range(2):n,at=u(at);at+=n
 kind=b[at];at+=1
 if kind==0:imports+=1;_,at=u(at)
 elif kind==1:
  at+=1;flags,at=u(at);_,at=u(at)
  if flags&1:_,at=u(at)
 elif kind==2:
  flags,at=u(at);_,at=u(at)
  if flags&1:_,at=u(at)
 elif kind==3:at+=2
 elif kind==4:at+=1;_,at=u(at)
 else:raise Exception(kind)
at,end=sections[10];count,at=u(at);target=int(m[1])-imports
for i in range(count):
 n,at=u(at);body=b[at:at+n];at+=n
 if i==target:
  assert body[:2]==bytes([0,0x42])and body[-1]==0x0b
  value=0;shift=0
  for c in body[2:-1]:value|=(c&127)<<shift;shift+=7
  assert c<128 and not(c&64)
  data={'scope':'Read-only address from existing original-C __errno_location function body; binary not modified.','functionIndex':int(m[1]),'bodyHex':body.hex(),'errnoAddress':value,'wasmSha256':hashlib.sha256(b).hexdigest(),'symbolSha256':hashlib.sha256(sym.encode()).hexdigest()};Path('/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/window-macro-proof/errno-location.json').write_text(json.dumps(data,indent=2)+'\n');print(data);break
