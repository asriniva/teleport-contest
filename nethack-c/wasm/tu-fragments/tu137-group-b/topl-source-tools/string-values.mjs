import{readFileSync}from'node:fs';import assert from'node:assert/strict';import {resolve as resolveSdkPath} from 'node:path';import {pathToFileURL as sdkFileURL,fileURLToPath as sdkURLPath} from 'node:url';
const toplSourceRoot=sdkURLPath(new URL('../../../../../',import.meta.url));
const {parse}=await import(sdkFileURL(resolveSdkPath(process.env.EMSDK??resolveSdkPath(toplSourceRoot,'.cache/emsdk'),'upstream/emscripten/node_modules/acorn/dist/acorn.mjs')));
const values=new Set();function visit(n){if(n.type==='Literal'&&typeof n.value==='string')values.add(n.value);for(const v of Object.values(n))if(Array.isArray(v)){for(const c of v)if(c?.type)visit(c);}else if(v?.type)visit(v);}
for(const f of[process.env.TOPL_GUARD_CORE??'js/ported/topl.js',process.env.TOPL_GUARD_RUNTIME??'js/nethack/bindings/topl.js'])visit(parse(readFileSync(f,'utf8'),{ecmaVersion:'latest',sourceType:'module'}));
for(const s of JSON.parse(readFileSync(process.env.TOPL_GUARD_STRINGS??'.cache/tu-probes/topl-guard/string-values.json','utf8')))assert(values.has(s),'actual C TOPL body string missing from JS expression: '+JSON.stringify(s));
console.log('TOPL actual body strings present in JS expressions; C-derived literal pool excluded');
