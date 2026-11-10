import assert from 'node:assert/strict';import{readFileSync}from'node:fs';import{resolve}from'node:path';import{fileURLToPath}from'node:url';
const artifactDir=resolve(process.env.UNIXUNIX_PROBE_DIR??fileURLToPath(new URL('../.cache/tu-probes',import.meta.url)));
const metadata=JSON.parse(readFileSync(new URL('../nethack-c/wasm/tu-fragments/unixunix-source-metadata.json',import.meta.url))),names=metadata.functions.map(f=>(f.linkage==='static'?'teleport_unixunix_':'')+f.name);
for(const mode of ['reference','hybrid']){const mod=new WebAssembly.Module(readFileSync(resolve(artifactDir,'unixunix-'+mode+'.wasm'))),imports=WebAssembly.Module.imports(mod).map(x=>x.name);for(const name of names)assert.equal(imports.includes(name),mode==='hybrid',mode+' '+name);}
console.log('PASS UNIXUNIX8 exact imported JS functions; unchanged-C reference owns bodies, hybrid excludes original bodies. Native-host proof separate.');
