// Compiler-measured adapter layout, consumed as data by production.
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import {pathToFileURL} from 'node:url';
const directory=path.resolve(process.env.STANDALONE_LEVEL_CONTENTS_ORACLE||'.cache/standalone-level-contents-v7'),sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex'),receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json')));
for(const [p,h]of Object.entries(receipt.sourceSha256))if(sha(p)!==h)throw new Error('Changed reference source '+p);
for(const [p,h]of Object.entries(receipt.artifactSha256))if(sha(path.join(directory,p))!==h)throw new Error('Changed reference artifact '+p);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs'))),ref=await factory();
const text=p=>{let end=Number(p);while(ref.HEAPU8[end])end++;return Buffer.from(ref.HEAPU8.slice(Number(p),end)).toString('latin1');};
const layout=Object.fromEntries(Array.from({length:Number(ref._probe_contents_layout_count())},(_,i)=>[text(ref._probe_contents_layout_name(BigInt(i))),Number(ref._probe_contents_layout_value(BigInt(i)))]));
const sources=['scripts/export-standalone-trap-abi.mjs','scripts/tu-trap-layout.h','nethack-c/wasm/tu-fragments/trap-support.h','js/nethack/bindings/trap.js'];
fs.writeFileSync('js/nethack/trap-abi.json',JSON.stringify({layout,sourceSha256:Object.fromEntries(sources.map(p=>[p,sha(p)])),referenceArtifactSha256:receipt.artifactSha256},null,2)+'\n');
console.log('Exported '+Object.keys(layout).length+' original-C trap layout facts.');
