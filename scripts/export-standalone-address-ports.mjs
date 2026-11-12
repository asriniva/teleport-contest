// Freeze actual C constants plus the existing adapters' own transport schemas.
import fs from 'node:fs';
import crypto from 'node:crypto';
import {pathToFileURL} from 'node:url';
const root=process.env.STANDALONE_REFERENCE_ROOT;
if(!root)throw new Error('STANDALONE_REFERENCE_ROOT is required');
const ports={};
const savedLayouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
for(const name of ['mklev','mkmaze','pickup','shk','invent','dothrow','display','dungeon','mkobj','muse','pray','detect','sp_lev']) {
    const path=`js/nethack/bindings/${name}.js`,source=fs.readFileSync(path,'utf8');
    const line=source.split('\n').find(line=>line.startsWith('const schema='));
    if(!line||!line.endsWith(';'))throw new Error('Unexpected source schema boundary '+name);
    const schema=JSON.parse(line.slice('const schema='.length,-1));
    const fragmentPath=`nethack-c/wasm/tu-fragments/${name}-schema.json`,fragment=fs.readFileSync(fragmentPath);
    schema.dependencies=JSON.parse(fragment).dependencies;
    const {default:factory}=await import(pathToFileURL(root+`/.cache/tu-probes/${name}-reference.mjs`)),reference=await factory();
    const getter=reference[`_teleport_${name}_layout`]??(['shk','invent'].includes(name)?reference._probe_layout:null);
    if(schema.layoutKeys&&typeof getter!=='function')throw new Error('Original C layout getter not exported for '+name);
    const layout=schema.layoutKeys?schema.layoutKeys.map((key,i)=>{const value=getter(i);return typeof value==='bigint'?value.toString():String(value);}):savedLayouts[name];
    ports[name]={schema,layout,sourceSha256:crypto.createHash('sha256').update(source).digest('hex'),fragmentSha256:crypto.createHash('sha256').update(fragment).digest('hex'),referenceSha256:Object.fromEntries(['mjs','wasm'].map(ext=>[ext,crypto.createHash('sha256').update(fs.readFileSync(root+`/.cache/tu-probes/${name}-reference.${ext}`)).digest('hex')]))};
}
fs.writeFileSync('js/standalone/address-ports.json',JSON.stringify({
    scope:'Existing typed address adapters, with constants measured by their original C development fixtures. This is transport metadata, not proof that all their game dependencies are resolved.',ports},null,2)+'\n');
console.log(`Exported ${Object.keys(ports).length} address-port schemas and actual C layout vectors`);
