import {readFileSync,writeFileSync} from 'node:fs';
import{resolve}from'node:path';import{pathToFileURL}from'node:url';const i=process.argv.indexOf('--out');if(i<0||!process.argv[i+1])throw Error('--out is required');const out=pathToFileURL(resolve(process.argv[i+1])+'/');
const here=out,names=['xpmgetline','fopen_xpm_file','conv_image','wr32','write_chunk','utility_main'];
const all={};for(const mode of['reference','hybrid']){const m=new WebAssembly.Module(readFileSync(new URL('artifacts/'+mode+'.wasm',here)));all[mode]=WebAssembly.Module.imports(m).filter(x=>names.includes(x.name));}
if(all.reference.length!==0||all.hybrid.length!==6||names.some(n=>!all.hybrid.some(x=>x.name===n&&x.kind==='function')))throw Error('actual six-policy import mismatch');
writeFileSync(new URL('./import-proof.json',here),JSON.stringify({status:'PASS',originalNativePolicyImports:all.reference,hybridAllSixPolicyImports:all.hybrid},null,2)+'\n');console.log(JSON.stringify(all));
