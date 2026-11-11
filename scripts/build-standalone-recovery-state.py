#!/usr/bin/env python3
"""Strict full-original-C recovery observer profile; never mutates sealed base."""
import hashlib,json,os,pathlib,subprocess
root=pathlib.Path(__file__).resolve().parents[1]
base=root/'.cache/full-original-c-v1'; out=root/'.cache/recovery-state-full-v1'
sha=lambda p:hashlib.sha256(pathlib.Path(p).read_bytes()).hexdigest()
receipt=json.loads((base/'receipt.json').read_text())
assert receipt['gameTranslationUnits']==140 and receipt['luaTranslationUnits']==32
assert not receipt['abortBoundaries'] and not receipt['portedTranslationUnits'] and not receipt['syntheticGameGlobals']
for p,h in receipt['sourceSha256'].items():assert sha(p)==h,p
for p,h in receipt['artifactSha256'].items():assert sha(base/p)==h,p
commands=json.loads((base/'commands.json').read_text())
link=next(c for c in commands if c[0].endswith('/emcc') and str(base/'out/game.mjs') in c)
compile=next(c for c in commands if '-c' in c and str(base/'obj/restore.o') in c)
(out/'proof').mkdir(parents=True,exist_ok=True);(out/'out').mkdir(exist_ok=True)
env={**os.environ,**receipt['buildEnvironment']};done=[]
def run(c):
 done.append(c);subprocess.run(c,cwd=root,env=env,check=True)
proof=link.copy();proof[proof.index('-o')+1]=str(out/'proof/game.mjs');run(proof)
assert sha(out/'proof/game.wasm')==receipt['artifactSha256']['out/game.wasm'],'Base relink not identical; object reuse rejected'
probe=root/'scripts/standalone-recovery-state-native.c'
replacement=compile.copy();replacement[replacement.index('-c')+1]=str(probe);replacement[replacement.index('-o')+1]=str(out/'restore.o');run(replacement)
saveprobe=root/'scripts/standalone-recovery-save-native.c'
savecompile=next(c for c in commands if '-c' in c and str(base/'obj/save.o') in c).copy()
savecompile[savecompile.index('-c')+1]=str(saveprobe);savecompile[savecompile.index('-o')+1]=str(out/'save.o');run(savecompile)
final=[str(out/'restore.o') if p==str(base/'obj/restore.o') else str(out/'save.o') if p==str(base/'obj/save.o') else p for p in link]
exports=['recovery_seed','recovery_mons','recovery_saveobjchn','recovery_savemonchn','recovery_newobj','recovery_newmonst','recovery_add_id','recovery_clear_ids','recovery_restobjchn','recovery_restmonchn','recovery_bucket','recovery_id_count','recovery_bucket_width','recovery_bucket_size']
for i,p in enumerate(final):
 if p.startswith('-sEXPORTED_FUNCTIONS='):
  v=json.loads(p.split('=',1)[1]);final[i]='-sEXPORTED_FUNCTIONS='+json.dumps(sorted(set(v+['_'+n for n in exports])))
final[final.index('-o')+1]=str(out/'out/game.mjs');run(final)
result={'profile':'strict complete original C recovery-private observer; base reproducible relink required','baseReceipt':str(base/'receipt.json'),'baseReceiptSha256':sha(base/'receipt.json'),'baseWasmSha256':sha(out/'proof/game.wasm'),'gameTranslationUnits':140,'luaTranslationUnits':32,'abortBoundaries':[],'buildEnvironment':receipt['buildEnvironment'],'sourceSha256':{**receipt['sourceSha256'],str(pathlib.Path(__file__).resolve()):sha(__file__),str(probe):sha(probe),str(saveprobe):sha(saveprobe)},'artifactSha256':{p:sha(out/p) for p in ['out/game.mjs','out/game.wasm']},'objectSha256':{p:sha(p) for p in final if p.endswith('.o')}}
(out/'commands.json').write_text(json.dumps(done,indent=2)+'\n');(out/'receipt.json').write_text(json.dumps(result,indent=2)+'\n');print('PASS: identical sealed-base relink and strict full C recovery observer build',out)
