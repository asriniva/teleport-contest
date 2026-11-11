#!/usr/bin/env python3
"""Strict full-original-C VAULT observation profile, sealed base never modified."""
import hashlib,json,os,pathlib,re,subprocess
root=pathlib.Path(__file__).resolve().parents[1];base=root/'.cache/full-original-c-v1';out=root/'.cache/standalone-vault-full-v1';sha=lambda p:hashlib.sha256(pathlib.Path(p).read_bytes()).hexdigest();receipt=json.loads((base/'receipt.json').read_text())
assert receipt['gameTranslationUnits']==140 and receipt['luaTranslationUnits']==32
for k in ['abortBoundaries','portedTranslationUnits','syntheticGameGlobals']:assert receipt[k]==[]
for p,h in receipt['sourceSha256'].items():assert sha(p)==h,p
for p,h in receipt['artifactSha256'].items():assert sha(base/p)==h,p
commands=json.loads((base/'commands.json').read_text());link=next(c for c in commands if c[0].endswith('/emcc') and str(base/'out/game.mjs')in c);compile=next(c for c in commands if '-c'in c and str(base/'obj/vault.o')in c)
(out/'proof').mkdir(parents=True,exist_ok=True);(out/'out').mkdir(exist_ok=True);env={**os.environ,**receipt['buildEnvironment']};done=[]
def run(command):done.append(command);subprocess.run(command,cwd=root,env=env,check=True)
proof=link.copy();proof[proof.index('-o')+1]=str(out/'proof/game.mjs');run(proof);assert sha(out/'proof/game.wasm')==receipt['artifactSha256']['out/game.wasm'],'Unsealed objects failed identical original relink; reuse rejected'
probe=root/'scripts/standalone-vault-native.c';support=root/'nethack-c/wasm/tu-fragments/vault-support.inc';replacement=compile.copy();replacement[replacement.index('-c')+1]=str(probe);replacement[replacement.index('-o')+1]=str(out/'vault.o');run(replacement)
final=[str(out/'vault.o')if p==str(base/'obj/vault.o')else p for p in link];exports=re.findall(r'\b(teleport_vault_\w+)\([^;{}]*\)\s*\{',support.read_text())
for i,p in enumerate(final):
 if p.startswith('-sEXPORTED_FUNCTIONS='):final[i]='-sEXPORTED_FUNCTIONS='+json.dumps(sorted(set(json.loads(p.split('=',1)[1])+['_'+n for n in exports])))
final[final.index('-o')+1]=str(out/'out/game.mjs');run(final)
result={'profile':'strict complete original C VAULT native observation; identical sealed-base relink prerequisite','baseReceipt':str(base/'receipt.json'),'baseReceiptSha256':sha(base/'receipt.json'),'baseWasmSha256':sha(out/'proof/game.wasm'),'gameTranslationUnits':140,'luaTranslationUnits':32,'abortBoundaries':[],'portedTranslationUnits':[],'syntheticGameGlobals':[],'buildEnvironment':receipt['buildEnvironment'],'sourceSha256':{**receipt['sourceSha256'],str(pathlib.Path(__file__).resolve()):sha(__file__),str(probe):sha(probe),str(support):sha(support)},'artifactSha256':{p:sha(out/p)for p in ['out/game.mjs','out/game.wasm']},'objectSha256':{p:sha(p)for p in final if p.endswith('.o')}}
(out/'commands.json').write_text(json.dumps(done,indent=2)+'\n');(out/'receipt.json').write_text(json.dumps(result,indent=2)+'\n');print('PASS: identical sealed base and full original VAULT observer profile',out)
