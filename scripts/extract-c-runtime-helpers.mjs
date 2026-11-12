import {runHistoricalCli as runPriorLayoutAudit} from './nethack-layout.mjs';
if(runPriorLayoutAudit(import.meta.url))process.exit(0);
// Reproducible, reversible extraction of identical C adapter mechanics.
// Default is verification. --write accepts only exact baseline or generated files.
import fs from 'node:fs';
import {readBeforeLayout,writeBeforeLayout,existsBeforeLayout} from './services-layout-audit.mjs';
import crypto from 'node:crypto';
import {execFileSync} from 'node:child_process';
import {pathToFileURL} from 'node:url';
import assert from 'node:assert/strict';
const reference=process.env.STANDALONE_REFERENCE_ROOT;
if(!reference)throw new Error('Missing STANDALONE_REFERENCE_ROOT');
const {parse}=await import(pathToFileURL(reference+'/.cache/emsdk/upstream/emscripten/node_modules/acorn/dist/acorn.mjs'));
const baseline="c0740becc16e413e0eab9bc55747381841faf80b";
const specifications=[
  {
    "name": "descriptorArray",
    "bodySha256": "6aa8a047432b533178cabbaae475fb13c3c5bb2947cc88d9557c99cf89a3c6e5",
    "dependencies": [
      "cache",
      "width",
      "read",
      "write"
    ],
    "parameters": [
      "d",
      "at"
    ],
    "expectedOccurrences": 9
  },
  {
    "name": "writeIntegerCell",
    "bodySha256": "394b401bf610c12735d85a2c61d001b00336827d9f5f201673da2d851b40668e",
    "dependencies": [
      "memory",
      "address",
      "bits"
    ],
    "parameters": [
      "v"
    ],
    "expectedOccurrences": 17
  },
  {
    "name": "narrowInteger",
    "bodySha256": "dee6d03090d11754d63e36442cbf352e8ca609ed481e90f61e4b075a20c2387a",
    "dependencies": [
      "signed",
      "bits"
    ],
    "parameters": [
      "v"
    ],
    "expectedOccurrences": 17
  },
  {
    "name": "writeDescriptor",
    "bodySha256": "f974a6cc1362c09bd3b58c0ae72c972e5e5e23f588a9789a332a913ab856f810",
    "dependencies": [
      "services",
      "addr",
      "width",
      "memory",
      "raw"
    ],
    "parameters": [
      "d",
      "at",
      "v"
    ],
    "expectedOccurrences": 9
  },
  {
    "name": "readIntegerCell",
    "bodySha256": "60f41ab5fe568ff3933087168edd7bc3b824b7fd2bcb6511ece361b0240686b8",
    "dependencies": [
      "memory",
      "decode",
      "t",
      "bits",
      "address"
    ],
    "parameters": [],
    "expectedOccurrences": 15
  },
  {
    "name": "scalarMethod",
    "bodySha256": "ac23a515bb1249ccd836106c67fe363892975a936e6ba51085f7e97e6308e5da",
    "dependencies": [],
    "parameters": [
      "t"
    ],
    "expectedOccurrences": 6,
    "expression": true
  },
  {
    "name": "advanceDescriptor",
    "bodySha256": "e0c2d6d58945eed1df5ca63230532cebcfa2c9db4d9c913a4d91f22b2879b9e4",
    "dependencies": [
      "view",
      "addr",
      "layout",
      "array",
      "width",
      "read",
      "write"
    ],
    "parameters": [
      "v",
      "n"
    ],
    "expectedOccurrences": 4
  },
  {
    "name": "defineScalarField",
    "bodySha256": "2d93bfa39a0c7c2879dfc7200a00376fd7f30745808f33fcf540f3a05e1dfd7b",
    "dependencies": [
      "view"
    ],
    "parameters": [
      "obj",
      "key",
      "at",
      "kind"
    ],
    "expectedOccurrences": 7,
    "expression": true
  },
  {
    "name": "pointerSequence",
    "bodySha256": "f442525b229588133b33a347fc21ee0f32ad220f54c6a7426a5edd19e823ad4d",
    "dependencies": [
      "read",
      "write",
      "records",
      "record"
    ],
    "parameters": [
      "p",
      "t",
      "stride"
    ],
    "expectedOccurrences": 6,
    "expression": true
  },
  {
    "name": "definePointerField",
    "bodySha256": "666144a96e370900558cc9d2a35eb2150029928b4fd97cc6c0ff2967195c6c0f",
    "dependencies": [
      "pointer",
      "view",
      "raw"
    ],
    "parameters": [
      "obj",
      "key",
      "at",
      "wrap"
    ],
    "expectedOccurrences": 9,
    "expression": true
  },
  {
    "name": "initializeRecord",
    "bodySha256": "6d8754488682de0efa85aaa2f4211d109f5b8b3c53f1631addc86e6a91e0ea9a",
    "dependencies": [
      "address",
      "services",
      "sizeof",
      "write",
      "fieldInfo",
      "env",
      "initialValue"
    ],
    "parameters": [
      "at",
      "type",
      "value"
    ],
    "expectedOccurrences": 2
  },
  {
    "name": "indexedArray",
    "bodySha256": "fe270d4e1c09a3af83f187bf2f6443c9a78d800834ce7f1095a5f336014dd8d2",
    "dependencies": [],
    "parameters": [
      "length",
      "getter",
      "setter"
    ],
    "expectedOccurrences": 3,
    "expression": true
  },
  {
    "name": "typeSize",
    "bodySha256": "b8d32eb723837485c7153ddce990907ff16cde729ab08179df13c0ae45514d57",
    "dependencies": [
      "types",
      "env",
      "sizeOf"
    ],
    "parameters": [
      "t"
    ],
    "expectedOccurrences": 6
  },
  {
    "name": "formatShape",
    "bodySha256": "88614c96d51964f92c8db17d8bec9f1e566626d86c5626ae82b5ae3c9ea5086f",
    "dependencies": [
      "cString"
    ],
    "parameters": [
      "fmt"
    ],
    "expectedOccurrences": 4
  },
  {
    "name": "readDescriptor",
    "bodySha256": "d2b7c56772e8edbe0d232ee68363e817c50b1af1cbbd6d428d484f1acef82307",
    "dependencies": [
      "decode",
      "memory"
    ],
    "parameters": [
      "d",
      "at"
    ],
    "expectedOccurrences": 5
  },
  {
    "name": "writeTypedValue",
    "bodySha256": "d8fc0abd2541bbc0f9c0902151561be6b3c93e4cb6b8d374d8d404afdd169c73",
    "dependencies": [
      "scalarType",
      "view",
      "raw",
      "literal",
      "services",
      "address",
      "size"
    ],
    "parameters": [
      "t",
      "p",
      "v"
    ],
    "expectedOccurrences": 4
  },
  {
    "name": "decodeDescriptor",
    "bodySha256": "e396e11dbad62401e1a3ca8f974370588fa719d38b47b662fca9c6b674c7120d",
    "dependencies": [
      "view",
      "array",
      "addr"
    ],
    "parameters": [
      "d",
      "v"
    ],
    "expectedOccurrences": 4
  },
  {
    "name": "defineScalarValue",
    "bodySha256": "9800e2f7f077418a79932183f8e46c13bd50eb907a97489f987a6b4f2bb01dbc",
    "dependencies": [
      "view"
    ],
    "parameters": [
      "o",
      "key",
      "at",
      "kind"
    ],
    "expectedOccurrences": 5,
    "expression": true
  }
];
const sha=text=>crypto.createHash('sha256').update(text).digest('hex');
const originals=new Map(),nodes=[];
const files=execFileSync('git',['ls-tree','-r','--name-only',baseline,'--','js/ported'],{encoding:'utf8'}).trim().split('\n').filter(file=>file.endsWith('-runtime.js'));
for(const file of files){
 const source=execFileSync('git',['show',baseline+':'+file],{encoding:'utf8'});originals.set(file,source);
 const ast=parse(source,{ecmaVersion:'latest',sourceType:'module'});
 function walk(node){if(!node||typeof node!=='object')return;
  if(['FunctionDeclaration','FunctionExpression','ArrowFunctionExpression'].includes(node.type)){const body=source.slice(node.body.start,node.body.end);nodes.push({file,node,body,bodySha:sha(body)});}
  for(const[k,v]of Object.entries(node)){if(['start','end'].includes(k))continue;if(Array.isArray(v))v.forEach(walk);else if(v&&typeof v==='object')walk(v);}
 }walk(ast);
}
const helperFile='js/c-runtime/adapter-memory.js',receiptFile='docs/runtime-environment/c-runtime-helper-extraction.json';
function render(specs,{legacyArrowBlocks=false,namespaceImports=true}={}){
 const edits=new Map(),bodies=new Map(),counts=new Map(),byHash=new Map(specs.map(spec=>[spec.bodySha256,spec]));
 assert.equal(byHash.size,specs.length,'Ambiguous helper fingerprints');
 for(const {file,node,body,bodySha}of nodes){
  const spec=byHash.get(bodySha);if(!spec)continue;
  assert.deepEqual(node.params.map(p=>p.type==='AssignmentPattern'?p.left.name:p.name),spec.parameters,'Changed helper parameters '+file);
  assert.equal(node.body.type!=='BlockStatement',Boolean(spec.expression),'Changed expression/block profile '+file);
  assert.ok(!originals.get(file).includes((namespaceImports?'Crt.':'runtime')+spec.name),'Import alias collision '+file);
  bodies.set(spec.name,body);counts.set(spec.name,(counts.get(spec.name)??0)+1);
  const list=edits.get(file)??[];list.push({start:node.body.start,end:node.body.end,helper:spec.name,beforeSha256:sha(body),after:(spec.expression&&!legacyArrowBlocks?(namespaceImports?'Crt.':'runtime')+spec.name+'('+[...spec.dependencies,...spec.parameters].join(',')+')':'{return '+(namespaceImports?'Crt.':'runtime')+spec.name+'('+[...spec.dependencies,...spec.parameters].join(',')+');}')});edits.set(file,list);
 }
 for(const spec of specs)assert.equal(counts.get(spec.name),spec.expectedOccurrences,'Changed occurrence inventory '+spec.name);
 const header=specs.length===5?'// Shared implementations of the existing descriptor-adapter memory profile.\n// Preserve its unchecked pointer-array and integer decoding conventions.\n':'// Shared implementations of the existing C adapter memory profiles.\n// Profiles retain their own array, conversion, initialization and field contracts.\n';
 const helperSource=header+specs.map(spec=>'export function '+spec.name+'('+[...spec.dependencies,...spec.parameters].join(',')+')'+(spec.expression?'{return ('+bodies.get(spec.name)+');}':bodies.get(spec.name))).join('\n\n')+'\n';
 const outputs=new Map([[helperFile,helperSource]]),receipts=[];
 for(const[file,list]of edits){
  const sorted=[...list].sort((a,b)=>a.start-b.start);for(let i=1;i<sorted.length;i++)assert.ok(sorted[i-1].end<=sorted[i].start,'Overlapping helper edits '+file);
  let output=originals.get(file);for(const edit of [...list].sort((a,b)=>b.start-a.start))output=output.slice(0,edit.start)+edit.after+output.slice(edit.end);
  const names=[...new Set(list.map(edit=>edit.helper))].sort();const header=namespaceImports?"import * as Crt from '../c-runtime/adapter-memory.js';\n":'import {'+names.map(name=>name+' as runtime'+name).join(',')+"} from '../c-runtime/adapter-memory.js';\n";
  output=header+output;outputs.set(file,output);
  let inverse=output.slice(header.length);
  for(const edit of sorted){const start=edit.start;assert.equal(inverse.slice(start,start+edit.after.length),edit.after);inverse=inverse.slice(0,start)+originals.get(file).slice(edit.start,edit.end)+inverse.slice(start+edit.after.length);}
  assert.equal(inverse,originals.get(file),'Non-exact inverse '+file);
  receipts.push({file,beforeSha256:sha(originals.get(file)),afterSha256:sha(output),edits:list});
 }
 const receipt={baselineCommit:baseline,helperFile,helperSha256:sha(helperSource),...(namespaceImports?{importStyle:'namespace'}:{}),specifications:specs,files:receipts};outputs.set(receiptFile,JSON.stringify(receipt,null,2)+'\n');
 return {outputs,receipts,counts};
}
const result=render(specifications);
let previous;
if(existsBeforeLayout(receiptFile)){
 const receipt=JSON.parse(readBeforeLayout(receiptFile));
 assert.deepEqual(receipt.specifications,specifications.slice(0,receipt.specifications.length));
 const actual=readBeforeLayout(receiptFile,'utf8');
 for(const namespaceImports of [true,false])for(const legacyArrowBlocks of [false,true]){
  const candidate=render(receipt.specifications,{namespaceImports,legacyArrowBlocks});
  if(actual===candidate.outputs.get(receiptFile))previous=candidate;
 }
 if(!previous)throw new Error('Unrecognized intermediate recipe');
}
// Parse every candidate and verify namespace-call receiver independence before
// checking ownership of the complete set; no file is written during preflight.
for(const[file,source]of result.outputs)if(file.endsWith('.js')){
 const ast=parse(source,{ecmaVersion:'latest',sourceType:'module'});
 if(file===helperFile){const visit=node=>{if(!node||typeof node!=='object')return;assert.notEqual(node.type,'ThisExpression','Helper observes call receiver');if(node.type==='Identifier')assert.notEqual(node.name,'arguments','Helper observes implicit arguments');for(const[k,v]of Object.entries(node)){if(['start','end'].includes(k))continue;if(Array.isArray(v))v.forEach(visit);else if(v&&typeof v==='object')visit(v);}};visit(ast);}
}
for(const[file,expected]of result.outputs){
 const actual=existsBeforeLayout(file)?readBeforeLayout(file,'utf8'):null;
 if(process.argv.includes('--write'))assert.ok(actual===null||actual===expected||actual===originals.get(file)||actual===previous?.outputs.get(file),'Refusing unknown source '+file);
 else assert.equal(actual,expected,'Extraction differs '+file);
}
if(process.argv.includes('--write'))for(const[file,expected]of result.outputs)writeBeforeLayout(file,expected);
console.log('PASS: '+result.receipts.length+' adapters / '+[...result.counts.values()].reduce((a,b)=>a+b,0)+' exact helper extractions, complete byte inverses.');
