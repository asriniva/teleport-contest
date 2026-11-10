// Read-only source/typed-key guard; compiler metadata is the authority.
import assert from 'node:assert/strict';
import {readFile,writeFile} from 'node:fs/promises';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
const root=process.cwd(),{parse}=await import(pathToFileURL(resolve(root,'.cache/emsdk/upstream/emscripten/node_modules/acorn/dist/acorn.mjs')).href);
const schema=JSON.parse(await readFile(resolve(root,'nethack-c/wasm/tu-fragments/shk-schema.json'),'utf8'));
const inventory=JSON.parse(await readFile(resolve(root,'.cache/shk-first-pass/schema.json'),'utf8'));
const core=await readFile(resolve(root,'js/ported/shk.js'),'utf8'),tree=parse(core,{ecmaVersion:'latest',sourceType:'module'});
const walk=function*(n){if(!n||typeof n!=='object')return;yield n;for(const[k,v]of Object.entries(n))if(k!=='parent'){if(Array.isArray(v))for(const x of v)yield*walk(x);else if(v&&typeof v==='object')yield*walk(v);}};
const exports=tree.body.filter(n=>n.type==='ExportNamedDeclaration'&&n.declaration?.type==='FunctionDeclaration').map(n=>n.declaration);
assert.deepEqual(exports.map(n=>n.id.name),schema.names);assert.equal(exports.length,137);assert.equal(schema.private.length,64);
for(const f of exports)assert.deepEqual(f.params.map(p=>p.name),schema.functionParameters[f.id.name].map(p=>p.name),'exact source formal names: '+f.id.name);
const helpers='ptr i8 u8 i16 u16 i32 u32 i64 u64 cell global staticAddress functionAddress field zero copy automatic enterAutomatic leaveAutomatic stackSave stackRestore local variadic callback initialize literal sizes'.split(' ');
const keys=new Set([...helpers,...schema.layoutKeys,...schema.globals.map(g=>g.name),...Object.keys(schema.dependencies)]),observed=new Set();
for(const n of walk(tree))if(n.type==='MemberExpression'&&n.object.type==='Identifier'&&n.object.name==='C'){
 assert.equal(n.computed,false,'source C environment uses literal named metadata/helper keys');const key=n.property.name;assert.ok(keys.has(key),'missing compiler metadata/runtime helper C.'+key);observed.add(key);
}
for(const n of walk(tree))if(n.type==='CallExpression'&&n.callee.type==='MemberExpression'&&n.callee.object.name==='C'){
 const key=n.callee.property.name,args=n.arguments;
 if(key==='field'){const rec=args[1].value,name=args[2].value;assert.ok(schema.schema[rec]?.fields.some(f=>f.name===name),'actual field '+rec+'.'+name);}
 if(key==='variadic')assert.ok(schema.variadics[args[0].value]);
 if(key==='callback')assert.ok(schema.callbacks[args[0].value]);
 if(key==='staticAddress')assert.ok(schema.statics.some(s=>s.name===args[0].value));
 if(key==='functionAddress')assert.ok(schema.functionAddresses.includes(args[0].value));
 if(key==='literal')assert.ok(schema.literals.includes(args[0].value));
}
for(const n of walk(tree))if(n.type==='MemberExpression'&&n.computed&&n.object.type==='MemberExpression'&&n.object.object.name==='C'&&n.object.property.name==='sizes')assert.ok(schema.layoutKeys.includes('size:'+n.property.value),'actual size '+n.property.value);
const variadicTargets=[...new Set(schema.variadics.map(v=>v.function))].sort();assert.equal(variadicTargets.length,15);assert.equal(Object.keys(schema.dependencies).length,149);
assert.deepEqual([...new Set([...Object.keys(schema.dependencies),...variadicTargets])].sort(),inventory.externalCalls,'164 inventory foreign names =149 ordinary dependency names +15 distinct variadic targets');
const result={functions:137,public:73,private:64,exactFormalNames:true,observedCKeys:[...observed].sort(),allKeysHaveTypedMetadataOrExplicitRuntimeHelper:true,ordinaryDependencyNames:149,variadicTargets,inventoryForeignNames:164,nativeFunctionIdentities:schema.functionAddresses.length,typedVarargSites:schema.variadics.length,callbackSites:schema.callbacks.length};
if(process.env.SHK_WRITE_GUARD==='1')await writeFile(resolve(root,'.cache/shk-first-pass/metadata-key-proof.json'),JSON.stringify(result,null,2)+'\n');
console.log('SHK137 metadata/formal/field/size/literal/callback guard passed; foreign names164=149+15.');
