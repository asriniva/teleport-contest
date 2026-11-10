// Development-only source/ABI shape guard. Runtime uses original JS source and
// live compiled layouts; this does not substitute generated expected behavior.
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import {createHash} from 'node:crypto';
import {execFileSync} from 'node:child_process';
import {resolve,join} from 'node:path';
import {fileURLToPath,pathToFileURL} from 'node:url';
const root=fileURLToPath(new URL('../../../',import.meta.url));
const sdk=resolve(process.env.EMSDK??join(root,'.cache/emsdk'));
const {parse}=await import(pathToFileURL(join(sdk,'upstream/emscripten/node_modules/acorn/dist/acorn.mjs')).href);
const original=join(root,'.cache/wasm64-build/tree/src/sfbase.c'),macro=join(root,'.cache/wasm64-build/tree/include/sfmacros.h');
const source=readFileSync(original,'utf8'),headerSource=readFileSync(macro,'utf8'),core=readFileSync(join(root,'js/ported/sfbase.js'),'utf8');
const generatedHeader=readFileSync(join(root,'nethack-c/wasm/tu-fragments/sfbase-source-data.h'),'utf8');
for(const [key,text]of [['ORIGINAL',source],['MACROS',headerSource]])assert.equal(createHash('sha256').update(text).digest('hex'),generatedHeader.match(new RegExp('TELEPORT_SFBASE_'+key+'_SHA256 "([a-f0-9]+)"'))?.[1],'Review changed original SFBASE source/header '+key);
const defines=JSON.parse(readFileSync(join(root,'nethack-c/wasm/compile-defines.json'),'utf8')).map(name=>'-D'+name);
const preprocessed=execFileSync(join(sdk,'upstream/emscripten/emcc'),['-E','-sMEMORY64=1',...defines,'-I'+join(root,'.cache/wasm64-build/tree/include'),original],{encoding:'utf8',maxBuffer:16*1024*1024});
const owners=new Set([original,macro]),selected=[];let active=false;
for(const line of preprocessed.split('\n')){const marker=line.match(/^# \d+ "([^"]+)"/);if(marker)active=owners.has(marker[1]);else if(active)selected.push(line);}
const configured=selected.join('\n'),withoutComments=configured.replace(/\/\*[\s\S]*?\*\/|\/\/[^\n]*/g,'');
const definitions=Array.from(withoutComments.matchAll(/\b(\w+)\s*\(([^;{}]*)\)\s*\{/g)).filter(match=>!['if','for','while','switch'].includes(match[1]));
function checkInventory(text){const ast=parse(text,{ecmaVersion:'latest',sourceType:'module'});const functions=ast.body.filter(node=>node.type==='ExportNamedDeclaration'&&node.declaration?.type==='FunctionDeclaration').map(node=>node.declaration);assert.deepEqual(functions.map(fn=>fn.id.name),definitions.map(match=>match[1]),'Original239 configured function inventory/order');for(const [i,fn]of functions.entries()){const params=definitions[i][2].replace(/__attribute__\s*\(\([^)]*\)\)/g,'').trim();const expected=params&&params!=='void'?params.split(',').map(p=>p.trim().match(/(\w+)\s*$/)[1]):[];assert.deepEqual(fn.params.map(p=>p.name),expected,'Original parameters '+fn.id.name);}return functions;}
const functions=checkInventory(core);assert.equal(functions.length,239);assert.throws(()=>checkInventory(core.replace('export function sfo_arti_info','export function missing_sfo_arti_info')),/Original239 configured function inventory/);
for(const text of [source,headerSource])for(const comment of text.match(/\/\*[\s\S]*?\*\//g)??[])assert.ok(core.includes(comment),'Original block comment '+comment);
const strings=new Set();for(const group of withoutComments.matchAll(/(?:"(?:\\.|[^"\\])*"\s*)+/g)){const parts=group[0].match(/"(?:\\.|[^"\\])*"/g);strings.add(parts.map(token=>JSON.parse(token)).join(''));}
const literalBytes=Array.from(strings).reduce((n,text)=>n+Buffer.byteLength(text)+1,0);assert.equal(Number(generatedHeader.match(/TELEPORT_SFBASE_LITERAL_BYTES (\d+)/)?.[1]),literalBytes,'Exact compiler-expanded ABI format/text literal capacity');
const buffers={},sites=[];for(const match of source.matchAll(/\b(?:char\s*\*\s*)?(sfvalue_\w+|complex_dump|bitfield_dump)\([^;{}]*\)\s*\{/g)){const start=match.index+match[0].length,end=source.indexOf('\n}',start),body=source.slice(start,end),size=body.match(/static char buf\[(\d+)\]/);if(size)buffers[match[1]]=Number(size[1]);const call=body.match(/\bSnprintf\(/);if(call)sites.push({name:match[1],line:source.slice(0,start+call.index).split('\n').length});}
const compilerLines=Array.from(withoutComments.matchAll(/nh_snprintf\(__func__,\s*(\d+)\s*,/g),match=>Number(match[1]));assert.equal(compilerLines.length,sites.length);sites.forEach((site,index)=>site.line=compilerLines[index]);
assert.equal(Number(generatedHeader.match(/TELEPORT_SFBASE_BUFFER_BYTES (\d+)/)?.[1]),Object.values(buffers).reduce((a,b)=>a+b,0));
assert.ok(generatedHeader.includes('sfbase_site_names[]={'+sites.map(site=>JSON.stringify(site.name)).join(',')+'}'));assert.ok(generatedHeader.includes('sfbase_site_lines[]={'+sites.map(site=>site.line).join(',')+'}'));
const layout=readFileSync(join(root,'scripts/tu-sfbase-layout.h'),'utf8');for(const [name,size]of Object.entries(buffers))assert.ok(layout.includes('SFBASE_META(buffer_'+name+','+size+'),'),'Original static-buffer size '+name);
for(const [index,site]of sites.entries()){const fn=functions.find(fn=>fn.id.name===site.name),calls=[];function visit(node){if(node?.type==='CallExpression'&&node.callee?.type==='MemberExpression'&&node.callee.object?.name==='C'&&node.callee.property?.name==='Snprintf')calls.push(node);for(const value of Object.values(node??{})){if(Array.isArray(value)){for(const child of value)if(child?.type)visit(child);}else if(value?.type)visit(value);}}visit(fn);assert.equal(calls.length,1);assert.equal(calls[0].arguments.at(-1).value,index,'Original formatter site '+site.name);}
console.log(`SFBASE source guard:239 configured functions/parameters, all comments,${sites.length} format sites,${Object.keys(buffers).length} static buffers/${Object.values(buffers).reduce((a,b)=>a+b,0)} bytes and${literalBytes} literal bytes; inventory mutation rejected`);
