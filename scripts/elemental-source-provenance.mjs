// Read-only complete local import/resource closure for the elemental test harnesses.
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import{builtinModules}from'node:module';
import{elementalApprovedCorrection}from'./elemental-approved-correction.mjs';
export function elementalSourceSnapshot(directory,entries,resources=[]){
 const root=process.cwd(),files=new Set(),external=new Set(),builtins=new Set(builtinModules),hash=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
 const visit=file=>{file=path.resolve(file);if(files.has(file))return;assertFile(file);files.add(file);if(!/\.m?js$/.test(file))return;const source=fs.readFileSync(file,'utf8'),imports=new Set();
  for(const pattern of[/(?:^|[;\n])\s*(?:import|export)\b\s*[\w${},*\s]+?\bfrom\s*['"]([^'"]+)['"]/g,/(?:^|[;\n])\s*import\s*['"]([^'"]+)['"]/g,/\bimport\s*\(\s*['"]([^'"]+)['"]/g])for(const m of source.matchAll(pattern))imports.add(m[1]);
  for(const specifier of imports)if(specifier.startsWith('.'))visit(path.resolve(path.dirname(file),specifier));else{if(!specifier.startsWith('node:')&&!builtins.has(specifier))throw Error('Unbound elemental test external module '+specifier);external.add(specifier);}
  for(const m of source.matchAll(/new\s+URL\s*\(\s*['"](\.[^'"]+)['"]\s*,\s*import\.meta\.url/g)){const resource=path.resolve(path.dirname(file),m[1]);if(fs.existsSync(resource)&&fs.statSync(resource).isFile())visit(resource);}
 };
 function assertFile(p){if(!fs.statSync(p).isFile())throw Error('Expected elemental source file '+p);}
 entries.forEach(visit);const assets=[];function walk(dir){for(const n of fs.readdirSync(dir)){const p=path.join(dir,n);if(fs.statSync(p).isDirectory())walk(p);else assets.push(p);}}walk(path.resolve(directory,'assets'));
 return{approvedCorrection:elementalApprovedCorrection(directory),sourceSha256:Object.fromEntries([...files].sort().map(p=>[path.relative(root,p),hash(p)])),assetSha256:Object.fromEntries(assets.sort().map(p=>[path.relative(path.resolve(directory,'assets'),p),hash(p)])),referenceReceiptSha256:hash(path.resolve(directory,'receipt.json')),resourceSha256:Object.fromEntries(resources.filter(p=>fs.existsSync(p)).map(p=>[path.relative(root,path.resolve(p)),hash(p)])),externalImports:[...external].sort()};
}
