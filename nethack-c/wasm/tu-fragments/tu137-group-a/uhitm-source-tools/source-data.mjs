import assert from 'node:assert/strict';import{readFileSync}from'node:fs';import {resolve} from 'node:path';import {pathToFileURL} from 'node:url';
const {parse}=await import(pathToFileURL(resolve(process.env.EMSDK??'.cache/emsdk','upstream/emscripten/node_modules/acorn/dist/acorn.mjs')));
const outputDir=process.env.UHITM_GUARD_WORK??'.cache/uhitm-author';
const outputFile=name=>new URL(name,new URL(outputDir.endsWith('/')?outputDir:outputDir+'/',new URL('../../../../../',import.meta.url)));
const expected=JSON.parse(readFileSync(outputFile('source-data.json'),'utf8')),source=readFileSync('js/ported/uhitm.js','utf8'),runtime=readFileSync(process.env.UHITM_DATA_RUNTIME??'js/nethack/bindings/uhitm.js','utf8'),tree=parse(source,{ecmaVersion:'latest',sourceType:'module'}),actual={};
const readonly=['brief_feeling','from_your_blow','harmlessly_thru'];
function walk(n){if(n.type==='VariableDeclarator'&&readonly.includes(n.id?.name))actual[n.id.name]=n.init.value;for(const v of Object.values(n))if(Array.isArray(v)){for(const c of v)if(c?.type)walk(c);}else if(v?.type)walk(v);}
walk(tree);for(const name of readonly)assert.equal(actual[name],expected[name].initializer,name);
assert.equal(expected.clockwise.initializer,0);assert.equal(expected.msgbuf.initializer,null);assert.equal(expected.msgbuf.type,'char[256]');assert.equal(expected.generic.type,'char[10]');
const bytes=JSON.parse(runtime.match(/new Uint8Array\((\[[\d, ]+\])\),env.mimic_generic/)[1]);assert.deepEqual(bytes,[...expected.generic.initializer].map(c=>c.charCodeAt(0)).concat(0));
assert(runtime.includes("cleave_clockwise',{get:()=>env.byte(persistent(0)).value"));assert(runtime.includes('env.gulpum_msgbuf=persistent(1);env.mimic_generic=persistent(2);'));
const support=readFileSync('nethack-c/wasm/tu-fragments/uhitm-support.inc','utf8');assert(support.includes('static unsigned char teleport_uhitm_persistent_bytes[267];'));assert(support.includes('i==0?0:i==1?1:257'));
console.log('UHITM data PASS:3 readonly strings and native-address persistent clockwise/msgbuf/generic, exact C initializers');

// Check actual configured C body strings against JS expressions, not the binding's
// C-derived sourceLiterals pool. Constant adjacent-string concatenations are folded.
const strings=new Set();function fold(n){if(n.type==='Literal'&&typeof n.value==='string')return n.value;if(n.type==='BinaryExpression'&&n.operator==='+'){const a=fold(n.left),b=fold(n.right);if(a!==undefined&&b!==undefined)return a+b;}}
function stringwalk(n){const v=fold(n);if(v!==undefined)strings.add(v);for(const x of Object.values(n))if(Array.isArray(x)){for(const c of x)if(c?.type)stringwalk(c);}else if(x?.type)stringwalk(x);}
stringwalk(tree);stringwalk(parse(runtime,{ecmaVersion:'latest',sourceType:'module'}));
// generic is source-owned mutable char storage: its JS initializer is the exact
// byte vector checked independently above, rather than a JS string literal.
strings.add(String.fromCharCode(...bytes.slice(0,-1)));
for(const s of JSON.parse(readFileSync(outputFile('body-string-literals.json'),'utf8')))assert(strings.has(s),'actual C body string absent from JS expressions: '+JSON.stringify(s));
console.log('UHITM configured C body string values present in JS expressions; native literal pool excluded from this guard');
