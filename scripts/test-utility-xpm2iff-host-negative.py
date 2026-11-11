from pathlib import Path
import subprocess,json,hashlib
import argparse
parser=argparse.ArgumentParser(description='Reject a wrong-byte XPM2IFF JS control against the original native reference.')
parser.add_argument('--out',required=True,type=Path)
parser.add_argument('--source-root',type=Path,default=Path(__file__).resolve().parent.parent)
args=parser.parse_args();code_root=Path(__file__).resolve().parent.parent;b=args.out.resolve();r=args.source_root.resolve();h=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
core=code_root/'js/ported-utilities/xpm2iff-host.js';runtime=code_root/'js/ported-utilities/xpm2iff-host-runtime.js';test=code_root/'scripts/test-utility-xpm2iff-host.mjs'
assert core.read_text().count('S.fputc((v >>> 16) & 0xff, G.iff_out);')==1
(b/'wrong-core.mjs').write_text(core.read_text().replace('S.fputc((v >>> 16) & 0xff, G.iff_out);','S.fputc((v >>> 8) & 0xff, G.iff_out);',1))
(b/'negative-loader.mjs').write_text("const original="+json.dumps(core.as_uri())+",wrong="+json.dumps((b/'wrong-core.mjs').as_uri())+";export async function resolve(specifier,context,next){const r=await next(specifier,context);return r.url===original?{url:wrong,shortCircuit:true}:r;}\n")
original=core.read_text();wrong=(b/'wrong-core.mjs').read_text();assert wrong==original.replace('S.fputc((v >>> 16) & 0xff, G.iff_out);','S.fputc((v >>> 8) & 0xff, G.iff_out);',1)
argv=[str(r/'.cache/emsdk/node/24.19.0_64bit/bin/node'),'--no-warnings','--loader',str(b/'negative-loader.mjs'),str(test),'--out',str(b),'--case=write-32'];paths=[core,b/'wrong-core.mjs',runtime,test,b/'negative-loader.mjs',b/'artifacts/reference.mjs',b/'artifacts/reference.wasm',b/'artifacts/hybrid.mjs',b/'artifacts/hybrid.wasm'];before={str(p):h(p)for p in paths};p=subprocess.run(argv,cwd=r,stdout=subprocess.PIPE,stderr=subprocess.STDOUT);(b/'logs/wrong-wr32-negative.log').write_bytes(p.stdout);text=p.stdout.decode();assert p.returncode==1 and 'unchanged native wr32 big-endian contract'in text and 'ERR_MODULE'not in text,text;after={str(p):h(p)for p in paths};assert before==after
(b/'negative-result.json').write_text(json.dumps({'status':'EXPECTED_REJECTION','actualExit':p.returncode,'argv':argv,'oneIntentionalJSChange':'wr32 second output byte shifts8 instead of16','referenceAndTestInputsUnchanged':True,'boundInputs':before,'namedAssertion':'unchanged native wr32 big-endian contract','notLoaderOrImportFailure':True},indent=2)+'\n');print('PASS genuine wrong-JS rejection, actualexit',p.returncode)
